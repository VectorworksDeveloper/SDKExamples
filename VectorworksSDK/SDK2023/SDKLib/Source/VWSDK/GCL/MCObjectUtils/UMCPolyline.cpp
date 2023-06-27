//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	MiniCad polyline object utility class
	

#include "StdHeaders.h"
#include "GCL/Unclassified.h"
#include "GCL/UMCPolyline.h"
#include "GCL/UMCPolygon.h"
#include "GCL/ULine.h"

#define ROOT2	1.4142
#define COLINEARITY_THRESHOLD 0.999
#define MAX_NUMBER_OF_VERTICES	SHRT_MAX

typedef struct FloatCoordPtStruct
{
	double	x, y, z;
}  FloatCoordPt;


////////////////////////////////////////////////////////////
static short CurveRecursionLevel(short convertRes)
//    convertRes - in - the conversion resolution desired
////////////////////////////////////////////////////////////
{
#if 1
	if (convertRes >= 512)
		return 8;
	else if (convertRes >= 256)
		return 7;
	else if (convertRes >= 128)
		return 6;
	else if (convertRes >= 64)
		return 5;
	else if (convertRes >= 32)
		return 4;
	else if (convertRes >= 16)
		return 3;
	else
		return 2;
#else
	if (convertRes >= 64) {
		return 5;
	}
	else if (convertRes >= 32) {
		return 4;
	}
	else if (convertRes >= 16 ) {
		return 3;
	}	
	else if (convertRes >= 8 ) {
		return 2;
	}
	else {
		return 1;
	}
#endif
}

inline short RecursionLevelToSegments(short level)
	{ return (2 << level); }

GS_API TMCPolyline::TMCPolyline(CallBackPtr cbp, Handle thePolyline)
{
	if (thePolyline && gSDK->GetObjectTypeN ( thePolyline) == polylineNode ) {
		fPolyHandle = thePolyline;
		fNumVerts = GS_CountVertices(cbp, thePolyline);
		fClosed = GS_GetPolyShapeClose(cbp, thePolyline);
		fCBP = cbp;
	}
	else {
		fPolyHandle = nil; 
		fNumVerts = -1; 
		fClosed = false;
		fCBP = nil;
	}

}

void GS_API TMCPolyline::SetVertex(short vertexNum, const WorldPt& vertex, VertexType vType, WorldCoord arcRadius)
{
	::GS_SetVertex(fCBP, PolyHandle(), IndexInRange(vertexNum), vertex, vType, arcRadius);
}

void GS_API TMCPolyline::InsertVertex(const WorldPt& p, short beforeVertex, VertexType vType, WorldCoord arcRadius)
{
	::GS_InsertVertex(fCBP, PolyHandle(), p, IndexInRange(beforeVertex), vType, arcRadius);
	SetNumVerts();;
}

void GS_API TMCPolyline::AddVertex(const WorldPt& p, VertexType vType, WorldCoord arcRadius)
{
	::GS_AddVertex(fCBP, PolyHandle(), p, vType, arcRadius);
	fNumVerts = GS_CountVertices(fCBP,PolyHandle());
}

WorldPt GS_API TMCPolyline::Vector(const short index, const Boolean controlPoint)
{
	WorldPt retVector(0L,0L);
	
	WorldPt v1;
	WorldPt v2;
	VertexType vType = vtCorner;
	WorldCoord radius;

	if (fPolyHandle) { 
		if (controlPoint) {
			GS_GetControlVertex(fCBP, PolyHandle(), IndexInRange(index), v1, vType, radius);
			GS_GetControlVertex(fCBP, PolyHandle(),IndexInRange(index+1), v2, vType, radius);
		}
		else {
			GS_GetVertex(fCBP, PolyHandle(), IndexInRange(index), v1, vType, radius);
			GS_GetVertex(fCBP, PolyHandle(), IndexInRange(index+1) , v2, vType, radius);
		}

		WorldPt p; 
		p.x = v2.x-v1.x;
		p.y = v2.y-v1.y;

		retVector = v2-v1;
	}
	return retVector;
}


WorldPt GS_API TMCPolyline::UnitPerpVector(const short index, const Boolean controlPoint)
{
	WorldPt retVector(-this->UnitVector(this->IndexInRange(index),controlPoint).y,
			this->UnitVector(this->IndexInRange(index),controlPoint).x);
	return retVector;

}


WorldCoord GS_API TMCPolyline::ScalarProjection(const WorldPt vector, const short index, const Boolean /*controlPoint*/)
{
	WorldPt 	v1;
	WorldPt 	v2;
	VertexType vType;
	WorldCoord radius;

	GS_GetVertex(fCBP, fPolyHandle, this->IndexInRange(index), v1, vType, radius);
	GS_GetVertex(fCBP, fPolyHandle, this->IndexInRange(index+1), v2, vType, radius);
	return DotProduct(WorldPt(vector), WorldPt(v2-v1).Normal());
}



WorldPt GS_API TMCPolyline::Vertex(const short index)
{
	WorldPt 	v1(0L,0L);
	VertexType 	vType;
	WorldCoord radius;
	
	if (PolyHandle())
		GS_GetVertex(fCBP, PolyHandle(), IndexInRange(index), v1, vType, radius);
		
	return v1;
}

WorldPt GS_API TMCPolyline::ControlVertex(const short index)
{
	WorldPt 	v1(0L,0L);
	VertexType 	vType;
	WorldCoord radius;
	if (fPolyHandle)
		GS_GetControlVertex(fCBP, fPolyHandle, this->IndexInRange(index), v1, vType, radius);
	return v1;
}

short GS_API TMCPolyline::NearestSegStart(WorldPt pt, WorldCoord& dist)
{
	WorldCoord minPerpDist = 1.0e23;
	WorldCoord currPerpDist;
	WorldCoord currScalarProj;
	short segIndex = 1;

	for (short i = 1; i <= fNumVerts; i++) {
	
		currPerpDist = fabs(this->PerpScalarProjection(WorldPt(VectorFromSegStart(i, pt)), i,false));

		currScalarProj = this->ScalarProjection(WorldPt(VectorFromSegStart(i, pt)), i,false);
		
		if (currPerpDist < minPerpDist && currScalarProj>= 0.0 && 
			currScalarProj <= this->SegLength(i,false)) {
			minPerpDist = currPerpDist;
			segIndex = i;
		}
	}
	dist = minPerpDist;
	return segIndex;
}


WorldPt GS_API TMCPolyline::VectorFromSegStart(const short index, const WorldPt pt)
{
	WorldPt retPt(0L,0L);
	
	if (fPolyHandle && index > 0 && index <= fNumVerts) {
	
		WorldPt vertex = this->Vertex(index);
		
		if (vertex != retPt)
			retPt = pt - vertex;
	}
	
	return retPt;
}


WorldPt GS_API TMCPolyline::VectorFromNearestSegStart(const WorldPt pt)
{
	WorldCoord dist;
	WorldPt retVector(0L,0L);
	
	short startIndex = NearestSegStart(pt, dist);
	WorldPt nearestVertex = this->Vertex(startIndex);
	if (nearestVertex != retVector)
		retVector = pt - nearestVertex;
	return retVector;
}

short GS_API TMCPolyline::NearestSegStart(const WorldPt pt)
{
	WorldCoord dist;
	return NearestSegStart(pt, dist);
}

WorldCoord GS_API TMCPolyline::SumDistToBothVerticies(const short index, const WorldPt pt)
{
	WorldCoord retVal = 1.0e23;
	
	if (fPolyHandle && index > 0 && index <= fNumVerts) {
		WorldPt vectorToNextVertex;
		WorldPt vectorToVertex = VectorFromSegStart(index, pt);
		if (index < fNumVerts) 
			vectorToNextVertex = VectorFromSegStart(index+1, pt);
		else
			vectorToNextVertex = VectorFromSegStart(1, pt);
			
		return ((WorldPt) vectorToNextVertex).Magnitude() + ((WorldPt) vectorToVertex).Magnitude();
	}
	return retVal;
}

WorldCoord GS_API TMCPolyline::MinSumDistToBothVerticies(const WorldPt pt, WorldCoord& index)
{
	WorldCoord retVal = 1.0e23;
	WorldCoord thisVal = 1.0e23;
	short numVerts = this->NumVerts();
	
	index = 1;
	for ( short i = 1 ; i <= numVerts ; i++) {
		thisVal = SumDistToBothVerticies(i, pt);
		retVal = Min(thisVal,retVal);
		if (thisVal == retVal)
			index = i;
	}
	return retVal;
}

WorldCoord GS_API TMCPolyline::MinDistTo(const WorldPt pt, WorldCoord& index, const Boolean /*controlPoint*/)
{
	WorldCoord retVal = 1.0e23;
	WorldCoord thisVal = 1.0e23;
	short numVerts = this->NumVerts();
	if (!fClosed && numVerts > 1) 
		numVerts--;
	
	for ( short i = 1 ; i <= numVerts ; i++) {
		if (PtInSegArea(i, pt)) {
			thisVal = PerpScalarProjection(WorldPt(VectorFromSegStart(i,pt)), i, false);
			//Debug("thisVal : %lf ; retVal %lf\n",thisVal,retVal);
			if (fabs(thisVal) < fabs(retVal)) {
				retVal = thisVal;
				index = i;
			}
		}
	}
	return retVal;
}

void GS_API TMCPolyline::Invert()
{
	WorldPt tempVertex;
	VertexType tempVType = vtCorner;
	WorldCoord tempRadius;
	WorldPt setVertex;
	VertexType setVType = vtCorner;
	WorldCoord setRadius;
	Handle polyHandle = PolyHandle();
	short numVerts = NumVerts();
	if (fPolyHandle) 
		for (short i = 1 ; i <= fNumVerts/2 ; i++) {
			GS_GetVertex(fCBP, polyHandle, i, tempVertex, tempVType, tempRadius);
			GS_GetVertex(fCBP, polyHandle, numVerts+1-i, setVertex, setVType, setRadius);
			SetVertex(i, setVertex, setVType, setRadius);
			SetVertex(numVerts+1-i, tempVertex, tempVType, tempRadius);
		}
}

WorldCoord GS_API TMCPolyline::PathLengthFromStart(const WorldPt pt)
{
	WorldCoord retVal = 0L;
	short index = NearestSegStart(pt);	
	if (index > 1) 
		for (short i = 1 ; i < index ; i++) 
			retVal += WorldCoord(this->SegLength(i,true));
	WorldPt vector = WorldPt(VectorFromSegStart(index, pt));
	retVal += WorldCoord(this->ScalarProjection(vector, index,true));
	
	return retVal;
}


void GS_API TMCPolyline::Rotate(const short index)
{
	WorldPt temp;
	WorldPt vertex;
	VertexType 	tempVType;
	WorldCoord tempRadius;
	VertexType 	vType;
	WorldCoord radius;
	
	if (fPolyHandle) {
		for (Sint32 i = IndexInRange(index); i > 1L;i--) {
			GS_GetVertex(fCBP, fPolyHandle, 1L, temp, tempVType, tempRadius);
			
			for (short j = 2; j <= fNumVerts; j++) {
				GS_GetVertex(fCBP, fPolyHandle, j, vertex, vType, radius);
				SetVertex(j-1, vertex, vType, radius);
			}
			SetVertex(fNumVerts, temp, tempVType, tempRadius);
		}
	}
}

double GS_API TMCPolyline::ATanAngleRad(const short index, const Boolean controlPoint)
{
	if (fPolyHandle && index > 0 && index <= fNumVerts) {
	
		if (this->Vector(index,controlPoint).IsZero())
			return 0.0;
			
		if (this->Vector(index,controlPoint).x == 0L) {
			if (this->Vector(index,controlPoint).y > 0L)
				return PLPi/2.0;
			else
				return -PLPi/2.0;
		}
				
		return atan(this->Vector(index,controlPoint).y / this->Vector(index,controlPoint).x);
	}
	return 0.0;
}

short GS_API TMCPolyline::VectorQuadrant(const short index, const Boolean controlPoint)
{
	if (fPolyHandle && index > 0 && index <= fNumVerts) {
		if (this->Vector(index,controlPoint).IsZero())
			return -1;
			
		if (this->Vector(index,controlPoint).x == 0L) {
			if (this->Vector(index,controlPoint).y > 0L)
				return 90;
			else
				return -90;
		}
				
		if (this->Vector(index,controlPoint).y == 0L) {
			if (this->Vector(index,controlPoint).x > 0L)
				return 0;
			else
				return 180;
		}
			
		if (this->Vector(index,controlPoint).x > 0L) {
			if (this->Vector(index,controlPoint).y > 0L)
				return 1;
			else
				return 4;
		}
		else {	
			if (this->Vector(index,controlPoint).y > 0L)
				return 2;
			else
				return 3;
		}
	}
	return 0;
}

WorldCoord GS_API TMCPolyline::Angle0To2Pi(const short index, const Boolean controlPoint)
{
	short i = this->IndexInRange(index);
	short quadrant = this->VectorQuadrant(i,controlPoint);
	
	switch (quadrant) {
		case 2 : 
		case 3 : {
			return this->ATanAngleRad(i,controlPoint) + PLPi;
		}
		case 4 : {
			return this->ATanAngleRad(i,controlPoint) + 2.0*PLPi;
		}
		case 180 : {
			return PLPi;
		}
		case 90 : {
			return PLPi/2.0;
		}
		case -90 : {
			return 3*PLPi/2.0;
		}
	}
	return this->ATanAngleRad(i,controlPoint);
}

WorldCoord GS_API TMCPolyline::Offset(const WorldPt pt)
{
	WorldCoord index;
	//Debug("offset returned is %lf\n",MinDistTo(pt, index, true));
	return MinDistTo(pt, index, true);	
}

void GS_API TMCPolyline::DrawCoordPoly()
{
	short numVerts = NumVerts();
	for (short i = 1 ; i <= numVerts-1; i++) 
		GS_DrawCoordLine(fCBP,Vertex(i),Vertex(i+1));
	if (Closed()) 
		GS_DrawCoordLine(fCBP,Vertex(numVerts),Vertex(1));
	
}


Boolean GS_API TMCPolyline::GetIntersection(WorldPt *OutputVertex, WorldPt FormerLineStart, 
		WorldPt FormerLineEnd, WorldPt LatterLineStart, WorldPt LatterLineEnd)
{
	WorldCoord	slope1, slope2;

	// If both lines vertical, no intersection possible.
	if (FormerLineEnd.x==FormerLineStart.x && LatterLineEnd.x==LatterLineStart.x) return false;

	if (FormerLineEnd.x==FormerLineStart.x)			// Former line vertical
	{	
		slope2=(LatterLineEnd.y-LatterLineStart.y)/(LatterLineEnd.x-LatterLineStart.x);
		OutputVertex->x=FormerLineEnd.x;
		OutputVertex->y=LatterLineStart.y+slope2*(FormerLineEnd.x-LatterLineStart.x);
	}
	else if (LatterLineEnd.x==LatterLineStart.x)	// Latter line vertical
	{
		slope1=(FormerLineEnd.y-FormerLineStart.y)/(FormerLineEnd.x-FormerLineStart.x);
		OutputVertex->x=LatterLineEnd.x;
		OutputVertex->y=FormerLineStart.y+slope1*(LatterLineEnd.x-FormerLineStart.x);
	}
	else
	{
		slope1=(FormerLineEnd.y-FormerLineStart.y)/(FormerLineEnd.x-FormerLineStart.x);
		slope2=(LatterLineEnd.y-LatterLineStart.y)/(LatterLineEnd.x-LatterLineStart.x);
		if (slope1==slope2) slope2+=0.0001;	// Lines parallel -> no intersection
		if (slope1==slope2) slope2+=0.0001;	// Lines parallel -> no intersection

		OutputVertex->x=(slope2*LatterLineStart.x-LatterLineStart.y-
			slope1*FormerLineStart.x+FormerLineStart.y)/(slope2-slope1);
		OutputVertex->y=slope1*(OutputVertex->x-FormerLineStart.x)+FormerLineStart.y;
	}

	return true;
}

WorldCoord GS_API  TMCPolyline::CityBlockDistance(WorldPt FormerVertex, WorldPt LatterVertex)
{
	WorldCoord	buffer=fabs(FormerVertex.x-LatterVertex.x)+fabs(FormerVertex.y-LatterVertex.y);

	// Check for integer overflow
	if (buffer<0) buffer=2000000000;

	return(buffer);
}

Boolean GS_API  TMCPolyline::DirectionAboutTheSame(WorldPt FormerLineStart, WorldPt FormerLineEnd, 
			WorldPt LatterLineStart, WorldPt LatterLineEnd, WorldCoord threshold)
{
	FloatCoordPt	Vector1, Vector2;
	WorldCoord	DotProduct, Normalizer;

	Vector1.x=(float)(FormerLineEnd.x-FormerLineStart.x)/1000000;
	Vector1.y=(float)(FormerLineEnd.y-FormerLineStart.y)/1000000;
	Vector2.x=(float)(LatterLineEnd.x-LatterLineStart.x)/1000000;
	Vector2.y=(float)(LatterLineEnd.y-LatterLineStart.y)/1000000;


	DotProduct=(Vector1.x*Vector2.x)+(Vector1.y*Vector2.y);
	Normalizer=sqrt((Vector1.x*Vector1.x + Vector1.y*Vector1.y))*
		sqrt((Vector2.x*Vector2.x + Vector2.y*Vector2.y));
	DotProduct/=Normalizer;

	return(DotProduct>threshold);
}

double GS_API  TMCPolyline::EuclideanDistanceSquaredOver10ToThe8th(WorldPt Point1, WorldPt Point2)
{
	double	dx, dy;
	double	distance;

	dx=(Point1.x-Point2.x);
	dy=(Point1.y-Point2.y);

	dx /= 10000;
	dy /= 10000;

	distance=dx*dx+dy*dy;
	return(distance);
}

Boolean GS_API  TMCPolyline::RemoveCrossovers(CallBackPtr fCBP, Handle poly, const WorldCoord offset)
{
	short	numVerts = GS_CountVertices(fCBP, poly), ThisIndex, OtherIndex;
	WorldCoord DistanceThreshold;
	short next, previous;
	WorldPt ThisVertexNoOffset(0L,0L), ThisVertexOffset(0L,0L), Intersection(0L,0L), ThisVertex(0L, 0L);
	WorldPt OtherVertexNoOffset(0L,0L), OtherVertexOffset(0L,0L), PreviousOtherVertexNoOffset;
	VertexType 	vType, CornerType=vtCorner;
	WorldCoord 		radius;
	Boolean	*Discard;
	WorldCoord	FloatOffset=offset, OffsetSquaredOver10ToThe8th;

	OffsetSquaredOver10ToThe8th=(FloatOffset*FloatOffset)/1.0e8;

	Discard=(Boolean *)calloc((numVerts+1), sizeof(Boolean));

	for (ThisIndex=1; ThisIndex<=numVerts; ++ThisIndex)	if (!Discard[ThisIndex])
	{
		  GS_GetVertex(fCBP, poly, ThisIndex, ThisVertexOffset, vType, radius);
		  GS_GetVertex(fCBP,fPolyHandle, ThisIndex , ThisVertexNoOffset, vType, radius);

		  // Drop vertex if it hasn't been offset properly
		  if (ThisVertexOffset.x==ThisVertexNoOffset.x && ThisVertexOffset.y==ThisVertexNoOffset.y)
			  Discard[ThisIndex]=true;

		  else for (OtherIndex=1; OtherIndex<=numVerts; ++OtherIndex) if (OtherIndex!=ThisIndex)
		  {
			  if (OtherIndex==1)
				  GS_GetVertex(fCBP,fPolyHandle, numVerts , PreviousOtherVertexNoOffset, vType, radius);
			  else
			  {
				  PreviousOtherVertexNoOffset.x=OtherVertexNoOffset.x;
				  PreviousOtherVertexNoOffset.y=OtherVertexNoOffset.y;
			  }

			  GS_GetVertex(fCBP, poly, OtherIndex, OtherVertexOffset, vType, radius);
			  GS_GetVertex(fCBP,fPolyHandle, OtherIndex , OtherVertexNoOffset, vType, radius);

			  GetIntersection(&Intersection, ThisVertexNoOffset, ThisVertexOffset, OtherVertexNoOffset, 
				  OtherVertexOffset);
			  Discard[ThisIndex]=(
				  CityBlockDistance(ThisVertexOffset, Intersection)<=
				  CityBlockDistance(ThisVertexOffset, ThisVertexNoOffset) &&
				  CityBlockDistance(OtherVertexOffset, Intersection)<=
				  CityBlockDistance(OtherVertexOffset, OtherVertexNoOffset));
			   
			  if (Discard[ThisIndex]) Discard[ThisIndex]=(
				  (EuclideanDistanceSquaredOver10ToThe8th(ThisVertexNoOffset, Intersection)<=OffsetSquaredOver10ToThe8th &&
				  EuclideanDistanceSquaredOver10ToThe8th(OtherVertexNoOffset, Intersection)<=OffsetSquaredOver10ToThe8th) 
				  );
			   
			  if (Discard[ThisIndex])
			  {
				  Discard[OtherIndex]=true;
				  break;
			  }
			  
			  // See if offset actually crosses original.
			  if (!Discard[ThisIndex] && OtherIndex!=ThisIndex+1) 	
			  {
					GetIntersection(&Intersection, ThisVertexNoOffset, ThisVertexOffset, OtherVertexNoOffset, 
					PreviousOtherVertexNoOffset);
					DistanceThreshold=CityBlockDistance(OtherVertexNoOffset, PreviousOtherVertexNoOffset);
					Discard[ThisIndex]=(
					  CityBlockDistance(OtherVertexNoOffset, Intersection)<=DistanceThreshold &&
					  CityBlockDistance(PreviousOtherVertexNoOffset, Intersection)<=DistanceThreshold
					  );
					if (Discard[ThisIndex]) break;
			  }
		  }
	}

	for (ThisIndex=numVerts; ThisIndex>=1; --ThisIndex)	
		if (Discard[ThisIndex]) GS_DeleteVertex(fCBP, poly, ThisIndex);
		else  // Nodes adjacent to deleted nodes should be set to be corners instead of Beziers
		{
			next=(ThisIndex<numVerts)? ThisIndex+1 : 1;
			previous=(ThisIndex>1)? ThisIndex-1 : numVerts;
			if (Discard[next] || Discard[previous])
			{
				::GS_GetVertex(fCBP, poly, ThisIndex, ThisVertex, vType, radius);
				::GS_SetVertex(fCBP, poly, ThisIndex, ThisVertex, CornerType, radius);
			}
		}


	free(Discard);
	return true;
}

Boolean GS_API  TMCPolyline::RemoveBowTies(CallBackPtr fCBP, Handle poly)
{
	short	numVerts = GS_CountVertices(fCBP, poly), ThisIndex, OtherIndex, ThisPlus2, ThisPlus1, Plugs=0, *PlugIndices, next, previous;
	WorldPt PreviousVertex(0L,0L), ThisVertex(0L,0L), Intersection(0L,0L);
	WorldPt OtherVertex(0L,0L), PreviousOtherVertex(0L,0L), *plugs;
	VertexType 	vType, CornerType=vtCorner;
	WorldCoord 		radius;
	Boolean	*Discard, CrossOver;
	short	forward, back, i, LastOther;

	Discard=(Boolean *)calloc((numVerts+1), sizeof(Boolean));
	PlugIndices=(short *)malloc(numVerts*sizeof(short));
	plugs=(WorldPt *)malloc(numVerts*sizeof(WorldPt));

	for (ThisIndex=1; ThisIndex<=numVerts; ++ThisIndex)	if (!Discard[ThisIndex])
	{
		if (ThisIndex==1)
		{
		  GS_GetVertex(fCBP,poly, numVerts , PreviousVertex, vType, radius);
		  LastOther=numVerts-1;
		}
		else
		  {
			  PreviousVertex.x=ThisVertex.x;
			  PreviousVertex.y=ThisVertex.y;
			  LastOther=numVerts;
		  }
		GS_GetVertex(fCBP, poly, ThisIndex, ThisVertex, vType, radius);

		for (OtherIndex=ThisPlus2=ThisIndex+2, ThisPlus1=ThisIndex+1; OtherIndex<=LastOther; ++OtherIndex) 
		{
			  if (OtherIndex==ThisPlus2)
				  GS_GetVertex(fCBP,poly, ThisPlus1 , PreviousOtherVertex, vType, radius);
			  else
			  {
				  PreviousOtherVertex.x=OtherVertex.x;
				  PreviousOtherVertex.y=OtherVertex.y;
			  }
			  GS_GetVertex(fCBP, poly, OtherIndex, OtherVertex, vType, radius);

			  GetIntersection(&Intersection, PreviousVertex, ThisVertex, PreviousOtherVertex, OtherVertex);
			  CrossOver=(
				  CityBlockDistance(PreviousVertex, Intersection)<=
				  CityBlockDistance(PreviousVertex, ThisVertex) &&
				  CityBlockDistance(ThisVertex, Intersection)<=
				  CityBlockDistance(ThisVertex, PreviousVertex) &&
				  CityBlockDistance(PreviousOtherVertex, Intersection)<
				  CityBlockDistance(PreviousOtherVertex, OtherVertex)  &&
				  CityBlockDistance(OtherVertex, Intersection)<
				  CityBlockDistance(OtherVertex, PreviousOtherVertex)
				  );

			  if (CrossOver)
			  {
				  forward=OtherIndex-ThisIndex;
				  back=numVerts+ThisIndex-OtherIndex;
				  if (forward<back)
				  {
					  for (i=ThisIndex; i<OtherIndex; ++i) Discard[i]=true;
					  PlugIndices[Plugs]=ThisIndex;
				  }
				  else
				  {
					  for (i=OtherIndex; i!=ThisIndex; i=(i<numVerts)? i+1 : 1)	 Discard[i]=true;
					  PlugIndices[Plugs]=ThisIndex;
				  }
				  plugs[Plugs].x=Intersection.x;
				  plugs[Plugs++].y=Intersection.y;
			  }
			   
			  if (Discard[ThisIndex])
			  {
				  Discard[OtherIndex]=true;
				  break;
			  }
		  }
	}
	
	for (ThisIndex=numVerts, --Plugs; ThisIndex>=1; --ThisIndex)
	{
		if (Discard[ThisIndex])
		{
			::GS_DeleteVertex(fCBP, poly, ThisIndex);
			if (ThisIndex==PlugIndices[Plugs])
			{
				::GS_InsertVertex(fCBP, poly, plugs[Plugs--], ThisIndex, CornerType, 0);
			}
		}
		else  // Nodes adjacent to deleted nodes should be set to be corners instead of Beziers
		{
			next=(ThisIndex<numVerts)? ThisIndex+1 : 1;
			previous=(ThisIndex>1)? ThisIndex-1 : numVerts;
			if (Discard[next] || Discard[previous])
			{
				::GS_GetVertex(fCBP, poly, ThisIndex, ThisVertex, vType, radius);
				::GS_SetVertex(fCBP, poly, ThisIndex, ThisVertex, CornerType, radius);
			}
		}
	}

	free(Discard);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////
short GS_API TMCPolyline::CalcMaxCells(Handle thePoly, short cnvrtRes)
//    thePoly - in - the polyline we're converting to segs
//    cnvrtRes - in - how precisely we're subdividing stuff
//
// Returns the maximum number of segments we need to
// represent the given polyline as straight segments
//
// No exceptions, no globals
//
// This function determines the maximum number of line segments
// we need to represent the given poly line with the given
// degree of precision.  A polyline can have straight and
// curved segments.  The straight segments each take a single
// line segment; the curved ones take multiple segments.  We
// add up the total for each segment of our polyline, and 
// return that total.
////////////////////////////////////////////////////////////////////////////////////
{
	short c, cellMax = 0;
	short  CurrentVertexCount = GS_CountVertices(fCBP, thePoly);
	WorldPt 	dummy(0L,0L);	
	VertexType 	vType;
	WorldCoord 		radius;
	//add 2 to the segments to allow for arcs which have extension segments
	short arcSegs = RecursionLevelToSegments(CurveRecursionLevel(cnvrtRes));
	ASSERTN(kRich, thePoly != 0);
	for (c = CurrentVertexCount-1; c >0 ; c--) {
		//estimate the largest possible polygon created
		GS_GetVertex(fCBP, thePoly, c, dummy, vType, radius);
		switch (vType) {
			case vtCorner: {
				cellMax++;
				break;
			}
			case vtBezier:
			case vtCubic:  {
				cellMax += arcSegs;
				break;
			}
			case vtArc: {
				cellMax += arcSegs + 2;
				break;
			}
		}
	}	
	return cellMax;
}

Boolean GS_API TMCPolyline::PolygonalizeByColinearity(Handle poly, short CurrentVertexCount, 
	WorldCoord ColinearityThreshold)
{
	Boolean		*ConvertNode, NearlyColinear;
	short		FirstIndex, MiddleIndex, LastIndex;
	VertexType 	vType, CornerType=vtCorner;
	WorldCoord 		radius;
	WorldPt 	FirstVertex(0L,0L), LastVertex(0L,0L), MiddleVertex(0L,0L);	

	if ((ConvertNode=(Boolean *)calloc((CurrentVertexCount+1), sizeof(Boolean)))==NULL) return false;

	for (FirstIndex=1; FirstIndex<CurrentVertexCount; ++FirstIndex)
	{
		MiddleIndex=FirstIndex+1;
		GS_GetVertex(fCBP, poly, FirstIndex, FirstVertex, vType, radius);
		GS_GetVertex(fCBP, poly, MiddleIndex, MiddleVertex, vType, radius);
		for (NearlyColinear=true, LastIndex=MiddleIndex+1; NearlyColinear;)
		{
			GS_GetVertex(fCBP, poly, LastIndex, LastVertex, vType, radius);
			NearlyColinear=DirectionAboutTheSame(FirstVertex, MiddleVertex, 
						MiddleVertex, LastVertex, ColinearityThreshold);
			if (NearlyColinear) 
			{
				if (LastIndex>=CurrentVertexCount)
				{
					FirstIndex=CurrentVertexCount;
					break;
				}
				ConvertNode[LastIndex++]=true;
			}
			else ConvertNode[LastIndex-1]=false;
		}
		FirstIndex=LastIndex-1;
	}
	for (FirstIndex=CurrentVertexCount-1; FirstIndex>2; --FirstIndex) if (ConvertNode[FirstIndex])	 
	{
		::GS_GetVertex(fCBP, poly, FirstIndex, FirstVertex, vType, radius);
		::GS_SetVertex(fCBP, poly, FirstIndex, FirstVertex, CornerType, radius);
	}
	free(ConvertNode);

	return true;
}


Handle GS_API TMCPolyline::OffsetPoly(const WorldCoord offset)
{
	
	if (PolyHandle()) 
	{
		WorldPt 	newVert, FirstVertex(0L,0L), LastVertex(0L,0L), dummy(0L,0L), MiddleVertex(0L,0L);	
		VertexType 	vType;
		WorldCoord 		radius;
		Handle 		poly;
		short		i, CurrentVertexCount;
		short		cnvrtRes;
		WorldCoord		ColinearityThreshold;

		if ((poly = GS_CreatePolyshape(fCBP)) != nil)
		{			
			GS_SetPolyShapeClose(fCBP, poly, Closed());
			CurrentVertexCount = GS_CountVertices(fCBP, fPolyHandle);
			if (Vertex(CurrentVertexCount) == Vertex(1))
				GS_DeleteVertex(fCBP, poly, CurrentVertexCount--);

			for  (i=1; i <= CurrentVertexCount; ++i) 
			{
				TMCPolyline offPoly(fCBP, poly);
				WorldPt	PreviousPreviousVertex(0L,0L), PreviousVertex(0L,0L);
					
				newVert = OffsetVertex(i,offset,false);

				::GS_GetVertex(fCBP, fPolyHandle, i, dummy, vType, radius);
				::GS_AddVertex(fCBP, poly, newVert, vType, radius);
			}
			CopyAttributes(fCBP,PolyHandle(), poly);

			// Remove bow-ties caused by vertices crossing over each other.
			RemoveCrossovers(fCBP, poly, offset);
			RemoveBowTies(fCBP, poly);
			
			// Ensure that last vertex not the same as the first.
			CurrentVertexCount=GS_CountVertices(fCBP, poly);
			if (CurrentVertexCount>2)
			{
				GS_GetVertex(fCBP, poly, 1, FirstVertex, vType, radius);
				GS_GetVertex(fCBP, poly, CurrentVertexCount, LastVertex, vType, radius);
				if (FirstVertex.x==LastVertex.x && FirstVertex.y==LastVertex.y)
					GS_DeleteVertex(fCBP, poly, CurrentVertexCount--);
			}

			// Remove polyline if not enough vertices.		
			if (GS_CountVertices(fCBP, poly)<3)
			{
				GS_DeleteObject(fCBP, poly, false);
				return nil;
			}

			// Convert bezier points, which are close to being colinear, to corner points
			GS_GetProgramVariable(fCBP, var2DConvertRes, (void *) &cnvrtRes);
			for (ColinearityThreshold=COLINEARITY_THRESHOLD; 
				//Idon't see any case where we can have a poly with number of vertiecs biger than a short so no need to go to Sint32.
				CalcMaxCells(poly, cnvrtRes) == MAX_NUMBER_OF_VERTICES; 
				ColinearityThreshold*=ColinearityThreshold)	
				PolygonalizeByColinearity(poly, CurrentVertexCount, ColinearityThreshold);

			return poly;
		}
	}

	return nil;
}

WorldPt GS_API TMCPolyline::OffsetVertex(const short index, const WorldCoord offset, const Boolean controlPoint)
{
	WorldPt newVert(0L,0L);
	
	if (PolyHandle()) {
	
		WorldPt 	currVert;			
		VertexType 	vType;
		WorldCoord 		radius;
	
		GS_GetVertex(fCBP,fPolyHandle, IndexInRange(index) , newVert, vType, radius);
		newVert += WorldPt(OffsetVector(index, offset, controlPoint));
	}
	return newVert;
}

WorldCoord GS_API TMCPolyline::OffsetRadius(const short index, WorldCoord offset)
{
	
	WorldCoord radius = WorldCoord(ArcRadius(index));
	if (ConcaveOnLeft(index,true)) 
		radius -= offset;
	else 
		radius += offset;
	return radius;
}

WorldCoord GS_API TMCPolyline::AngleBetweenRad(const short index, const Boolean controlPoint)
{
	if (index > 1)
		return acos(DotProduct(WorldPt(Vector(index,controlPoint)).Normal(),
								WorldPt(-Vector(index-1,controlPoint)).Normal()));
	else 
		return acos(DotProduct(WorldPt(this->Vector(index,controlPoint)).Normal(),
								WorldPt(-this->Vector(fNumVerts,controlPoint)).Normal()));
		
}

WorldPt GS_API TMCPolyline::OffsetVector(const short index, const WorldCoord offset, const Boolean controlPoint)
{
	WorldPt offsetVector(0.0,0.0);
	
	if (fPolyHandle) {
		WorldPt u,v;
		WorldCoord halfAngleBtwn;

		u = UnitVector(index-1, controlPoint);
		v = UnitVector(index, controlPoint);
		
		//Debug("u : %lf,%lf\n",u.x,u.y);
		//Debug("v : %lf,%lf\n",v.x,v.y);
		
		halfAngleBtwn = acos(DotProduct(u,v)) / 2.0;

		if (halfAngleBtwn == 90.0 || ((v - u).Normal()).IsZero())
			return offsetVector;
			
		
		if (EndPointVertex(index) ) {
			
// MJH 1/95: #ifdef probably unnecessary here, but it won't compile w/o type cast
#ifndef WINVER
			if (index == 1)											
				offsetVector = offset*UnitPerpVector(index, controlPoint);
			else
				offsetVector = offset*UnitPerpVector(index-1, controlPoint);
#else
			if (index == 1)											
				offsetVector = (double_t)offset*UnitPerpVector(index, controlPoint);
			else
				offsetVector = (double_t)offset*UnitPerpVector(index-1, controlPoint);
#endif
		}
		else {
			if (ConcaveOnLeft(index, controlPoint)) {
				//Debug("vertex # %ld  :  ConcaveOnLeft and offset : %ld\n",index,offset);
				offsetVector = double_gs(offset/cos(halfAngleBtwn)) * (v - u).Normal();	
			}
			else {
				//Debug("NOT ConcaveOnLeft and offset : %ld\n",index,offset);
				offsetVector = double_gs(offset/cos(halfAngleBtwn)) * (u - v).Normal();
			}
		}
	}
	return offsetVector;
}

Boolean GS_API TMCPolyline::PtInSegArea(const short index, const WorldPt pt)
{
	Boolean retVal = false;
	if (fPolyHandle) {
		WorldPt vectorFromSegStartToPt = WorldPt(pt-this->Vertex(this->IndexInRange(index)));
		WorldPt vectorFromSegEndToPt = WorldPt(pt-this->Vertex(this->IndexInRange(index+1)));
		WorldPt startOffsetVector = this->OffsetVector(this->IndexInRange(index),1,true);
		WorldPt endOffsetVector = this->OffsetVector(this->IndexInRange(index+1),1,true);
		
		if (OnLeftOf(vectorFromSegStartToPt,WorldPt(this->Vector(this->IndexInRange(index),true)))) {
			retVal = (!OnLeftOf(vectorFromSegStartToPt,startOffsetVector) &&
					OnLeftOf(vectorFromSegEndToPt,endOffsetVector));
		}
		else {
			retVal = (OnLeftOf(vectorFromSegStartToPt,-startOffsetVector) &&
					!OnLeftOf(vectorFromSegEndToPt,-endOffsetVector));
		}
	}
		return retVal;
}

#ifdef MYBUG
void TMCPolyline::Test()
{
	WorldPt vertexPt,prevCPt,nextCPt,centerPt;
	WorldPt ctrlPt1,ctrlPt2,ctrlPt3;
	//Debug("test\n");
	for (short i = 1 ; i <= NumVerts() ; i++) {
		//Debug("\nvertex # %ld of type %d\n",i,VertType(i));
		//Debug("\nvertex # %ld with ArcRadius %ld returns OffsetRadius %ld\n",i,ArcRadius(i),OffsetRadius(i, 2048));
		//Debug("Vertex : %ld,%ld\n",this->Vertex(i).x,this->Vertex(i).y);
		//Debug("ControlVertex : %ld,%ld\n",this->ControlVertex(i).x,this->ControlVertex(i).y);
		//Debug("Vector : %ld,%ld\n",this->Vector(i,true).x,this->Vector(i,true).y);
		//Debug("ControlVector : %ld,%ld\n",this->Vector(i,false).x,this->Vector(i,false).y);
		//Debug("SegLength : %lf\n",this->SegLength(i,true));
		//Debug("ControlSegLength : %lf\n",this->SegLength(i,false));
		//Debug("UnitVector : %lf,%lf\n",this->UnitVector(i,true).x,this->UnitVector(i,true).y);
		//Debug("ControlUnitVector : %lf,%lf\n",this->UnitVector(i,false).x,this->UnitVector(i,false).y);
		//Debug("UnitPerpVector : %lf,%lf\n",this->UnitPerpVector(i,true).x,this->UnitPerpVector(i,true).y);
		//Debug("ControlUnitPerpVector : %lf,%lf\n",this->UnitPerpVector(i,false).x,this->UnitPerpVector(i,false).y);
		//Debug("ATanAngleDeg : %lf\n",this->ATanAngleDeg(i,true));
		//Debug("ControlATanAngleDeg : %lf\n",this->ATanAngleDeg(i,false));
		//Debug("Angle0To360 : %lf\n",this->Angle0To360(i,true));
		//Debug("ControlAngle0To360 : %lf\n",this->Angle0To360(i,false));
		
		//Debug("ConcaveOnLeft : %ld\n",this->ConcaveOnLeft(i,true));
		//Debug("ControlConcaveOnLeft : %ld\n",this->ConcaveOnLeft(i,false));
		//Debug("OffsetRadius : %ld\n",this->OffsetRadius(i, 2048));
		//Debug("EndPointVertex : %ld\n",this->EndPointVertex(i));
		//Debug("angle between : %lf\n",AngleBetweenDeg(i,true));
		
		/*
		if (ControlNeighborhood(i,prevCPt,vertexPt,nextCPt,centerPt) > -1) { 
			if (VertType(i) != vtCorner) {
				WorldCoord r = Num2Long(WorldPt(nextCPt-centerPt).Magnitude());
				//Debug("r : %ld\n",r);
				
				WorldRect bBox(centerPt.x-r,centerPt.y+r,centerPt.x+r,centerPt.y-r);
				//Handle t = CreateLine(fCBP,centerPt,prevCPt);
				//Handle u = CreateLine(fCBP,centerPt,nextCPt);
				//PlaceCircleAt(fCBP, prevCPt, 100);
				//PlaceCircleAt(fCBP, vertexPt, 300);
				//PlaceCircleAt(fCBP, nextCPt, 200);
				if (VertType(i) == vtArc) {
					//PlaceCircleAt(fCBP, centerPt, 50);
					//Handle h = CreateArc(fCBP,bBox, 0.0,360.0);
					//DrawObject(fCBP, h, true);
				}
				//DrawObject(fCBP, t, true);
				//DrawObject(fCBP, u, true);
			}
		}
		*/
				
	}
}
#endif


VertexType GS_API TMCPolyline::ControlNeighborhood(const short index, 
											WorldPt& prevCtrlPt, WorldPt& cntrlVertex, 
											WorldPt& nextCtrlPt, WorldPt& centerPt)
{
	//Debug("ControlNeighborhood\n");
	
	if (PolyHandle()) {	
		cntrlVertex = ControlVertex(index);
		prevCtrlPt = ControlVertex(index);
		nextCtrlPt = ControlVertex(index);
		centerPt = ControlVertex(index);
		
		VertexType thisVt = VertType(index);
		
		centerPt = cntrlVertex;
		switch (VertType(index-1)) {
			case vtCorner : {
				prevCtrlPt = cntrlVertex + (ControlVertex(index-1) - cntrlVertex);
			 	break;
			}
			case vtArc :
			case vtBezier :
			case vtCubic : {
				prevCtrlPt = cntrlVertex + WorldPt((0.5)*WorldPt(ControlVertex(index-1) - cntrlVertex));
				break;
			}
		}

		switch (VertType(index+1)) {
			case vtCorner : {
				nextCtrlPt = cntrlVertex + (ControlVertex(index+1) - cntrlVertex);
			 	break;
			}
			case vtArc :
			case vtBezier :
			case vtCubic : {
				nextCtrlPt = cntrlVertex + WorldPt((0.5)*WorldPt(ControlVertex(index+1) - cntrlVertex));
				break;
			}
		}

		if (thisVt == vtArc) {

			WorldCoord offsetMag = 0.0;
			WorldCoord arcRadius;
			WorldPt vert;
			VertexType vtType;
			GS_GetVertex(fCBP, PolyHandle(), IndexInRange(index), vert, vtType, arcRadius);

			WorldCoord theta = AngleBetweenRad(index,true)/2.0;
			WorldCoord beta = (PLPi/2.0 - theta);
									
			if (fabs(theta) != PLPi/2.0 && fabs(beta) != PLPi/2.0) {
				WorldCoord xArcRadius = arcRadius;
				//Debug("xArcRadius : %lf\n",xArcRadius);
				if (xArcRadius == 0.0 ) {
					WorldCoord min = Min(	WorldPt(prevCtrlPt-vert).Magnitude(),
										WorldPt(nextCtrlPt-vert).Magnitude());
				 	//Debug("arcRadius == 0L || arcRadius >=  min*tan(theta)\n");
					xArcRadius = min*tan(theta);
					offsetMag = min;
				}	
				else
				{
					offsetMag = fabs(xArcRadius*tan(beta));
				}

				nextCtrlPt = vert + UnitVector(index,true)*offsetMag;
				prevCtrlPt = vert - UnitVector(index-1,true)*offsetMag;
				if (PolyTurnsRight(index))
					xArcRadius *= -1.0;
				centerPt = nextCtrlPt + UnitPerpVector(index,true)*xArcRadius; 
			}
			else {	//180 degrees 
				centerPt = vert;
				nextCtrlPt = vert;
				prevCtrlPt = vert;
			}
		}
		return thisVt;

	}
	return -1;

}


WorldCoord GS_API TMCPolyline::ArcRadius(const short index)
{
	WorldPt p,v,n,c;
	short i = this->IndexInRange(index);
	if (ControlNeighborhood(i, p, v, n, c) == vtArc)
		return WorldPt(p-c).Magnitude();
	else 
		return 0.0;
}


VertexType GS_API TMCPolyline::VertType(const short index)
{
	VertexType 	vType = 0L;
	WorldCoord radius;
	WorldPt vertex;
	
	GS_GetVertex(fCBP, PolyHandle(), IndexInRange(index), vertex, vType, radius);
		
	return vType;
}

WorldCoord GS_API TMCPolyline::MCArcRadius(const short index)
{
	VertexType 	vType = 0L;
	WorldCoord radius;
	WorldPt vertex;
	
	GS_GetVertex(fCBP, PolyHandle(), IndexInRange(index), vertex, vType, radius);
		
	return radius;
}

WorldPt GS_API TMCPolyline::PriorControlPoint(const short index)
{
	WorldPt retVal(0L,0L);
	
	if (!PolyHandle()) 
		return retVal;
		
	WorldPt p,v,n,c;
	(void) ControlNeighborhood(index, p, v, n, c);
	return p;
}


WorldPt GS_API TMCPolyline::NextControlPoint(const short index)
{
	WorldPt retVal(0L,0L);
	
	if (!fPolyHandle) 
		return retVal;
		
	WorldPt p,v,n,c;
	(void) ControlNeighborhood(index, p, v, n, c);
	return n;
}

void GS_API TMCPolyline::AddTMCVertex(WorldPt vertex, VertexType vType, WorldCoord arcRadius)
{
	if (fPolyHandle) {
		AddVertex(vertex, vType, arcRadius);
		fNumVerts = GS_CountVertices(fCBP, fPolyHandle);
	}

}


