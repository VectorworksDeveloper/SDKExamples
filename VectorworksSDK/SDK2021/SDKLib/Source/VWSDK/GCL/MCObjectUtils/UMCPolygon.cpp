//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	MiniCad polygon object utility class

#include "StdHeaders.h"
#include "GCL/UMCPolygon.h"
#include "GCL/ULine.h"
#include "GCL/Unclassified.h"
#include "VectorworksSDK.h"


extern "C" void GS_API FEOGetPolySects(Handle selObj, CallBackPtr cbp, void* env);


GS_API TMCPolygon::TMCPolygon(CallBackPtr cbp, Handle thePolygon)
{ 
	if ((thePolygon && gSDK->GetObjectTypeN ( thePolygon) == polyNode) 
			|| gSDK->GetObjectTypeN ( thePolygon) == curveNode) 
	{
		fPolyHandle = thePolygon;
		fNumVerts = GS_CountVertices(cbp, thePolygon);
		fClosed = GS_GetPolyShapeClose(cbp, thePolygon);
		fCBP = cbp;
	}
	else {
		fPolyHandle = nil; 
		fNumVerts = -1; 
		fClosed = false;
		fCBP = nil; 
	} 
 
}  
static WorldPt WorldPtProjectionOnLine(const WorldPt& p, const WorldPt& end1, const WorldPt& end2)
{
	WorldPt lineVec = end2-end1;
	WorldPt pointVec = p-end1;
	WorldPt unitOnto = lineVec.Normal();
	return (end1 + unitOnto * DotProduct(unitOnto, pointVec));
}
static bool WorldPtOnSegment(WorldPt pointProj, WorldPt start, WorldPt end)
{
	if( (pointProj-start).Magnitude() < tolerance) return true;
	if( (pointProj-end).Magnitude() < tolerance) return true;
	WorldCoord distance = (start-end).Magnitude();
	if( (pointProj-end).Magnitude() < distance && (pointProj-start).Magnitude() < distance ) 
		return true;
	else
		return false;
}

WorldCoord TMCPolygon::NearestDistance(WorldPt point)
{
/*	returns the index of start of the poly seg closest to the point pt,
	dist stores the perpendicular distance of the point pt from that seg.
*/
	WorldCoord minPerpDist = 1.0e23;

	WorldCoord currPerpDist;

	WorldPt v1, v2, pointProj;
	bool between = false;
	v1 = Vertex(1);
	if(PolyHandle()) {
	for (short i = 1; i <= fNumVerts; i++) {
			if( i < fNumVerts)
				v2 = Vertex(i+1);
			else if(GS_GetPolyShapeClose(fCBP, PolyHandle()))
				v2 = Vertex(1);

			pointProj = WorldPtProjectionOnLine(point, v1, v2);
			between = WorldPtOnSegment(pointProj, v1, v2);
			if ( /*!(v1 == v2) && */between ) {
					currPerpDist = (pointProj - point).Magnitude();
					if (currPerpDist < minPerpDist ) 
						minPerpDist = currPerpDist;
			}
			v1 = v2;
		}
	}
	return minPerpDist;
}
bool TMCPolygon::SelefIntersectingPolygon()
{
	WorldPt v11, v12, v21, v22, sect;
	Boolean parallel, intersect;
	intersect = false;
	WorldCoord lenght;
	if(!PolyHandle()) return false;
	for (short i = 1; i < fNumVerts && !intersect; i++) {
		v11 = Vertex(i);
		v21 = Vertex(i+1);
		for (short j = i+2; j <= fNumVerts && !intersect; j++) {
				v12 = Vertex(j);
			if( i < fNumVerts)
				v22 = Vertex(j+1);
			else if(GS_GetPolyShapeClose(fCBP, PolyHandle()))
				v22 = Vertex(1);
			GS_LineLineIntersect(fCBP,v11,v21,v12,v22,parallel,intersect,sect);
			if(intersect) {
				lenght = (sect-Vertex(1)).Magnitude();
				if(	(sect-Vertex(1)).Magnitude() < 1e-6 )
					intersect = false;
			}
						
		}
	}
	return intersect;
}

void TMCPolygon::CleanUpPolygon(Handle offsetPolygon, WorldCoord offset)
{
	WorldPt tempVertex;
	VertexType tempVType = vtCorner;
	WorldCoord tempRadius;
	WorldCoord  distance;
	WorldPt point, point1, point2;
	short i, NumVerts;
	offset = fabs(offset);
	
	
	if(offsetPolygon && PolyHandle()) {
		NumVerts = GS_CountVertices(fCBP, offsetPolygon);
		i = 1;
		while(i <= NumVerts) {
			::GS_GetVertex(fCBP, offsetPolygon, i, point, tempVType, tempRadius);
			
			distance = NearestDistance(point);
			if(distance < 0.8*offset) {
				::GS_DeleteVertex(fCBP, offsetPolygon, i);
				NumVerts--;
			}
			else
				i++;		
		}
		i = 1;
		bool deleteFirstVertex = false;
		while(i <= NumVerts) {
			bool outOfLoop = false;
			WorldPt vOff1, vOff2, v1Org, v2Org, sect;
			::GS_GetVertex(fCBP, offsetPolygon, i, vOff1, tempVType, tempRadius);
			if(i < NumVerts)
				::GS_GetVertex(fCBP, offsetPolygon, i+1, vOff2, tempVType, tempRadius);
			else if(GS_GetPolyShapeClose(fCBP, offsetPolygon)){
				deleteFirstVertex = true;
				::GS_GetVertex(fCBP, offsetPolygon, 1, vOff2, tempVType, tempRadius);}
			else {
				outOfLoop = true;
				i++;
			}
			
			short j = 1;
			Boolean intersect, parallel;
			bool doIntersection;
			while(j <= fNumVerts && !outOfLoop) {
				::GS_GetVertex(fCBP, PolyHandle(), j, v1Org, tempVType, tempRadius);
				if(j < fNumVerts) {
					doIntersection = true;
					::GS_GetVertex(fCBP, PolyHandle(), j+1, v2Org, tempVType, tempRadius);
				}
				else if(GS_GetPolyShapeClose(fCBP, PolyHandle())) {
					::GS_GetVertex(fCBP, PolyHandle(), 1, v2Org, tempVType, tempRadius);
					doIntersection = true;
				}
				else
					doIntersection = false;
				if(doIntersection) {
					GS_LineLineIntersect(fCBP,vOff1,vOff2,v1Org,v2Org,parallel,intersect,sect);
					if(intersect) {
						if(deleteFirstVertex)
							::GS_DeleteVertex(fCBP, offsetPolygon, 1);
						else
							::GS_DeleteVertex(fCBP, offsetPolygon, i+1);
						NumVerts--;// = GS_CountVertices(fCBP, offsetPolygon) - 1;
						outOfLoop = true;
					}
					else
						j++;
				}
				else
					j++;
			}
			if(!outOfLoop)
				i++;
		}
			
				
					
	}

}

void GS_API TMCPolygon::SetVertex(short vertexNum, const WorldPt& vertex)
{
	::GS_SetVertex(fCBP, PolyHandle(), IndexInRange(vertexNum), vertex, vtCorner, 0L);
}

void GS_API TMCPolygon::InsertVertex(const WorldPt& p, short beforeVertex)
{
	::GS_InsertVertex(fCBP, PolyHandle(), p, IndexInRange(beforeVertex), vtCorner, 0L);
	SetNumVerts();
}

void GS_API TMCPolygon::AddVertex(const WorldPt& p)
{
	::GS_AddVertex(fCBP, PolyHandle(), p, vtCorner, 0L);
	SetNumVerts();
}

void GS_API TMCPolygon::DeleteVertex(short vertexNum)
{
	::GS_DeleteVertex(fCBP, PolyHandle(), IndexInRange(vertexNum));
	SetNumVerts();
}


void GS_API TMCPolygon::DeleteVertices(const short startIndex, const short endIndex)
{
	if (PolyHandle() && endIndex > startIndex && endIndex <= NumVerts() && startIndex> 0 ) {
	
		for (short i = startIndex ; i <= endIndex ; i++)
			DeleteVertex(startIndex);
	}
}


WorldPt GS_API TMCPolygon::Vector(const short index)
{
	WorldPt retVector(0L,0L);
	
	WorldPt v1;
	WorldPt v2;
	VertexType vType = vtCorner;
	WorldCoord radius;

	GS_GetVertex(fCBP, fPolyHandle, this->IndexInRange(index), v1, vType, radius);
	GS_GetVertex(fCBP, fPolyHandle, this->IndexInRange(index+1) , v2, vType, radius);
	return  v2-v1;
}


WorldPt GS_API TMCPolygon::UnitPerpVector(const short index)
{
	WorldPt retVector(-this->UnitVector(index).y,this->UnitVector(index).x);
	return retVector;
}


WorldCoord GS_API TMCPolygon::ScalarProjection(const WorldPt vector, const short index)
{
	WorldPt 	v1;
	WorldPt 	v2;
	VertexType vType;
	WorldCoord radius;

	GS_GetVertex(fCBP, PolyHandle(), this->IndexInRange(index), v1, vType, radius);
	GS_GetVertex(fCBP, PolyHandle(), this->IndexInRange(index+1), v2, vType, radius);
		
	return DotProduct(WorldPt(vector), WorldPt(v2-v1).Normal());
}



WorldPt GS_API TMCPolygon::Vertex(const short index)
{
	WorldPt 	v1(0L,0L);
	VertexType 	vType;
	WorldCoord radius;
	
	if (PolyHandle())
	
		GS_GetVertex(fCBP, PolyHandle(), this->IndexInRange(index), v1, vType, radius);
		
	return v1;
}

short GS_API TMCPolygon::NearestSegStart(WorldPt pt, WorldCoord& dist)
/*	returns the index of start of the poly seg closest to the point pt,
	dist stores the perpendicular distance of the point pt from that seg.
*/
{
	short segIndex = 1;
	WorldCoord minPerpDist = 1.0e23;

	WorldCoord currPerpDist;
	WorldCoord currScalarProj;

	WorldPt v1, v2;

	v1 = Vertex(1);

	for (short i = 1; i <= fNumVerts; i++) {
		v2 = Vertex(i+1);

		// EJK 00/08/21 - this calculation results in distances of 0 when two consecutive points are identical.
		// This happens if the polygon is closed, because Vertex[1] == Vertex[n].
		// We avoid this case since it produces incorrect results which cripple DupAlongPath, and probably others.
		if ( ! (v1 == v2)) {
			currPerpDist = fabs(this->PerpScalarProjection(WorldPt(VectorFromSegStart(i, pt)), i));

			currScalarProj = this->ScalarProjection(WorldPt(VectorFromSegStart(i, pt)), i);
			
			if (currPerpDist < minPerpDist && currScalarProj>= 0.0 && 
				currScalarProj <= this->SegLength(i)) {
				minPerpDist = currPerpDist;
				segIndex = i;
			}
		}

		v1 = v2;
	}

	dist = minPerpDist;
	return segIndex;
}

short GS_API TMCPolygon::NearestSegStart(const WorldPt pt)
{
	WorldCoord dist;
	return NearestSegStart(pt, dist);
}
WorldPt GS_API TMCPolygon::VectorFromSegStart(const short index, const WorldPt pt)
{
	WorldPt retPt(0L,0L);
	
	if (PolyHandle()) {
	
		WorldPt vertex = Vertex(index);
		
		if (vertex != retPt)
			retPt = pt - vertex;
	}
	
	return retPt;
}

WorldPt GS_API TMCPolygon::VectorFromNearestSegStart(const WorldPt pt)
{
	WorldCoord dist;
	WorldPt retVector(0L,0L);
	
	short startIndex = NearestSegStart(pt, dist);
	WorldPt nearestVertex = this->Vertex(startIndex);
	if (nearestVertex != retVector)
		retVector = pt - nearestVertex;
	return retVector;
}

WorldCoord GS_API TMCPolygon::SumDistToBothVerticies(const short index, const WorldPt pt)
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

WorldCoord GS_API TMCPolygon::MinSumDistToBothVerticies(const WorldPt pt, short& index)
{
	WorldCoord retVal = 1.0e23;
	WorldCoord thisVal = 1.0e23;
	short numVerts = this->NumVerts();
	
	index = 1;
	for (short i = 1 ; i <= numVerts ; i++) {
		thisVal = SumDistToBothVerticies(i, pt);
		retVal = Min(thisVal,retVal);
		if (thisVal == retVal)
			index = i;
	}
	return retVal;
}

WorldCoord GS_API TMCPolygon::MinDistTo(const WorldPt pt, short& index)
{
	WorldCoord retVal = 1.0e23;
	WorldCoord thisVal = 1.0e23;
	short numVerts = this->NumVerts();
	
	for (short i = 1 ; i <= numVerts ; i++) {
		if (PtInSegArea(i, pt)) {
			thisVal = PerpScalarProjection(WorldPt(this->VectorFromSegStart(i,pt)), i);
			
			if (fabs(thisVal) < fabs(retVal)) {
				retVal = thisVal;
				index = i;
			}
		}
	}
	return retVal;
}

void GS_API TMCPolygon::RemoveDuplicateVertices()
{
	short numVerts = this->NumVerts();
	WorldPt lastVert = this->Vertex(numVerts);
	WorldPt thisVert;
	for (short i = 1 ; i <= this->NumVerts() ; i++) {
		thisVert = this->Vertex(i);
		if (thisVert == lastVert) 
			this->DeleteVertex(i);
		else
			lastVert = thisVert;
	}
}


void GS_API TMCPolygon::Invert()
{
	WorldPt tempVertex;
	VertexType tempVType = vtCorner;
	WorldCoord tempRadius;
	WorldPt setVertex;
	VertexType setVType = vtCorner;
	WorldCoord setRadius;
	if (fPolyHandle) 
		for (short i = 1 ; i <= fNumVerts/2 ; i++) {
			::GS_GetVertex(fCBP, fPolyHandle, i, tempVertex, tempVType, tempRadius);
			::GS_GetVertex(fCBP, fPolyHandle, fNumVerts+1-i, setVertex, setVType, setRadius);
			::GS_SetVertex(fCBP, fPolyHandle, i, setVertex, setVType, setRadius);
			::GS_SetVertex(fCBP, fPolyHandle, fNumVerts+1-i, tempVertex, tempVType, tempRadius);
		}
}

WorldCoord GS_API TMCPolygon::PathLengthFromStart(const WorldPt pt)
{
	WorldCoord retVal = 0L;
	
	if (pt == Vertex(1L) && Closed() )
		return GetPolyLength();
		
	short index = NearestSegStart(pt);	
	if (index > 1) 
		for (short i = 1 ; i < index ; i++) 
			retVal += this->SegLength(i);
	WorldPt vector = WorldPt(VectorFromSegStart(index, pt));
	retVal += this->ScalarProjection(vector, index);
	
	return retVal;
}


struct PolyVertexInfo {
	WorldPt		vertex;
	VertexType	vType;
	WorldCoord	radius;
};

void GS_API TMCPolygon::Rotate(const short index)
// this is time consuming
{
	Handle h = PolyHandle();

	if (h) {
		const short bufEntries = 256;
		PolyVertexInfo temp[bufEntries], slide;

		short theNumVerts = NumVerts();

		short count = IndexInRange(index);
		short numMoving, j;

		for (short i = count; i > 1; i-=bufEntries) {

			numMoving = (i-1 > bufEntries ? bufEntries : i-1);

			// move verts from beginning of list into buffer
			for (j = 0; j < numMoving; j++)
				::GS_GetVertex(fCBP, h, IndexInRange(j+1), temp[j].vertex, temp[j].vType, temp[j].radius);
			
			// shuffle the verts downward to fill the vacant space at the beginning of the list
			for (j = numMoving+1; j <= theNumVerts; j++) {
				::GS_GetVertex(fCBP, h, IndexInRange(j), slide.vertex, slide.vType, slide.radius);
				::GS_SetVertex(fCBP, h, IndexInRange(j-numMoving), slide.vertex, slide.vType, slide.radius);
			}

			// move verts from buffer into vacant space at the end of the list
			for (j = 0; j < numMoving; j++)
				::GS_SetVertex(fCBP, h, IndexInRange(theNumVerts-numMoving+j+1), temp[j].vertex, temp[j].vType, temp[j].radius);
		}
	}
}

short GS_API TMCPolygon::SegAtLenFromStart(const WorldCoord pathLength)
{
	WorldCoord tl = 0.0;
	short i = 1;
	while (tl <= pathLength) {
		tl += SegLength(i);
		i++;
	}
	return i-1;
}

void GS_API TMCPolygon::RotateSoPtOn1stSeg(const WorldPt p)
{
	WorldCoord pickPtLen = PathLengthFromStart(p);
	short pickPtIndex = SegAtLenFromStart(pickPtLen);
	Rotate(pickPtIndex-1);
}

double GS_API TMCPolygon::ATanAngleRad(const short index)
{
	if (fPolyHandle && index > 0 && index <= fNumVerts) {
	
		if (this->Vector(index).IsZero())
			return 0.0;
			
		if (this->Vector(index).x == 0L) {
			if (this->Vector(index).y > 0L)
				return PSPi/2.0;
			else
				return -PSPi/2.0;
		}
				
		return atan(this->Vector(index).y / this->Vector(index).x);
	}
	return 0.0;
}

short GS_API TMCPolygon::VectorQuadrant(const short index)
{
	if (fPolyHandle && index > 0 && index <= fNumVerts) {
		if (this->Vector(index).IsZero())
			return -1;
			
		if (this->Vector(index).x == 0L) {
			if (this->Vector(index).y > 0L)
				return 90;
			else
				return -90;
		}
				
		if (this->Vector(index).y == 0L) {
			if (this->Vector(index).x > 0L)
				return 0;
			else
				return 180;
		}
			
		if (this->Vector(index).x > 0L) {
			if (this->Vector(index).y > 0L)
				return 1;
			else
				return 4;
		}
		else {	
			if (this->Vector(index).y > 0L)
				return 2;
			else
				return 3;
		}
	}
	return 0;
}

WorldCoord GS_API TMCPolygon::Angle0To2Pi(const short index)
{
	short i = this->IndexInRange(index);
	short quadrant = this->VectorQuadrant(i);
	
	switch (quadrant) {
		case 2 : 
		case 3 : {
			return this->ATanAngleRad(i) + PSPi;
		}
		case 4 : {
			return this->ATanAngleRad(i) + 2.0*PSPi;
		}
		case 180 : {
			return PSPi;
		}
		case 90 : {
			return PSPi/2.0;
		}
		case -90 : {
			return 3*PSPi/2.0;
		}
	}
	return this->ATanAngleRad(i);
}


WorldCoord GS_API TMCPolygon::Offset(const WorldPt pt)
{
	short index;
	double_t temp = this->MinDistTo(pt, index);
	WorldCoord retVal = WorldCoord(temp);
	return retVal;
}



Handle GS_API TMCPolygon::OffsetPoly(const WorldCoord offset, const Boolean clipCollisions)
{
	if (PolyHandle()) {
	
		WorldPt 	newVert;			
		Handle 		poly;
		
		if (offset != 0L) {
			poly = GS_CreatePolyshape(fCBP);
			
			if (poly) {
			
				GS_SetPolyShapeClose(fCBP, poly, Closed());
				short i = 1;
				short numVerts = NumVerts();

				if (Vertex(numVerts) == Vertex(1)) this->DeleteVertex(numVerts);
				
				numVerts = NumVerts();

				while  (i <= numVerts ) {

					TMCPolygon offPoly(fCBP, poly);
					
					newVert = OffsetVertex(i,offset);

					offPoly.AddVertex(newVert);
					
					if (clipCollisions && i > 2) {	

						short indexPriorToIntersect = offPoly.NumVerts();
						WorldPt sect;
						if (offPoly.LastSegIntersectsSelf(indexPriorToIntersect, sect)) {
						
							short j = offPoly.NumVerts()-1;
							while (indexPriorToIntersect > 0L && j > indexPriorToIntersect) {
								offPoly.DeleteVertex(j);
								j--;

							}	 							
							offPoly.InsertVertex(WorldPt(sect) ,indexPriorToIntersect+1);
						}
						
					}
					
					i++;
				}
			}
			CopyAttributes(fCBP,PolyHandle(), poly);
			return poly;
		}
	}
	return nil;
}


WorldPt GS_API TMCPolygon::OffsetVertex(const short index, const WorldCoord offset)
{
	WorldPt newVert(0L,0L);
	
	if (fPolyHandle) {
	
		WorldPt 	currVert;			
		VertexType 	vType;
		WorldCoord 		radius;
	
		GS_GetVertex(fCBP,fPolyHandle, index , newVert, vType, radius);
		newVert += WorldPt(this->OffsetVector(index,offset));
	}
	return newVert;
}

WorldCoord GS_API TMCPolygon::AngleBetweenRad(const short index)
{
	if (index > 1)
		return acos(DotProduct(WorldPt(this->Vector(index)).Normal(),
								WorldPt(-this->Vector(index-1)).Normal()));
	else 
		return acos(DotProduct(WorldPt(this->Vector(index)).Normal(),
								WorldPt(-this->Vector(fNumVerts)).Normal()));
		
}

#ifdef MYBUG
void TMCPolygon::Test()
{

	WorldPt zero(0.0,0.0);
	for (short i = 1 ; i <= fNumVerts ; i++) {
		//Debug("Vertex : %ld,%ld\n",this->Vertex(i).x,this->Vertex(i).y);
		//Debug("Vector : %ld,%ld\n",this->Vector(i).x,this->Vector(i).y);
		//Debug("SegLength : %lf\n",this->SegLength(i));
		//Debug("UnitVector : %lf,%lf\n",this->UnitVector(i).x,this->UnitVector(i).y);
		//Debug("UnitPerpVector : %lf,%lf\n",this->UnitPerpVector(i).x,this->UnitPerpVector(i).y);
		//Debug("ATanAngleDeg : %lf\n",this->ATanAngleDeg(i));
		//Debug("Angle0To360 : %lf\n",this->Angle0To360(i));
		//Debug("Offsetector : %lf,%lf\n",this->OffsetVector(i,1).x,this->OffsetVector(i,1).y);
		
	}


}
#endif
/*
Boolean TMCPolygon::PtProjInProjRangeMinusOffsets(const short index, const WorldPt pt, 
												const WorldCoord offset)
{
	short i = this->IndexInRange(index);
	WorldCoord ptProj = this->ScalarProjection(WorldPt(pt-fStartPt),i);
	WorldCoord startOffsetProj = this->ScalarProjection(this->OffsetVector(i),i);
	WorldCoord endOffsetProj = this->SegLength(i) + this->ScalarProjection(
							this->OffsetVector(this->IndexInRange(i+1)),i);
								
	return (ptProj >= startOffsetProj && ptProj <= endOffsetProj
	
}
*/


WorldPt GS_API TMCPolygon::OffsetVector(const short index, const WorldCoord offset)
{
	WorldPt offsetVector(0.0,0.0);
	
	if (this->PolyHandle()) {
	
		WorldPt u,v;
		
		this->IndexInRange(index-1);
		
		u = this->UnitVector(this->IndexInRange(index-1));
		
		v = this->UnitVector(this->IndexInRange(index));
		
		double_t dot = DotProduct(u,v);
		
		
		
		if (this->EndPointVertex(index) ) {	
		
			if (index == 1)	{
				
				offsetVector = (double_t)offset*this->UnitPerpVector(index);
			}
			else {
			
				offsetVector = (double_t)offset*this->UnitPerpVector(index-1);
			}
		}
		else {
		
			if (fabs(dot) > 0.999999) {		// parallel
				offsetVector = (double_t)offset*this->UnitPerpVector(index);
			}
			else {
				double_gs halfAngleBtwn = acos(dot) / 2.0;
				
				if (ConcaveOnLeft(index))
					offsetVector = offset/cos(halfAngleBtwn)*(v - u).Normal();	
				else
					offsetVector = offset/cos(halfAngleBtwn)*(u - v).Normal();
			}	
		}
	}
	return offsetVector;
}

Boolean GS_API TMCPolygon::PtInSegArea(const short index, const WorldPt pt)
{
	Boolean retVal = false;
	if (fPolyHandle) {
		WorldPt vectorFromSegStartToPt = WorldPt(pt-this->Vertex(this->IndexInRange(index)));

		WorldPt vectorFromSegEndToPt = WorldPt(pt-this->Vertex(this->IndexInRange(index+1)));

		WorldPt startOffsetVector = this->OffsetVector(this->IndexInRange(index),1);

		WorldPt endOffsetVector = this->OffsetVector(this->IndexInRange(index+1),1);

		
		if (OnLeftOf(vectorFromSegStartToPt,WorldPt(this->Vector(this->IndexInRange(index))))) {
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


WorldCoord GS_API TMCPolygon::GetPolyLength()
{
	WorldCoord length = 0.0;
	for (short i = 1 ; i < fNumVerts ; i++) 
		length += this->SegLength(i);
	
	if (fClosed) {
		length += this->SegLength(fNumVerts);
	}
	
	return length;
}

Boolean GS_API TMCPolygon::NotAVertex(const WorldPt p)
{
	for (short i = 1 ; i < fNumVerts ; i++) 
		if (p == Vertex(i))
			return false;

	return true;
}

Boolean GS_API TMCPolygon::IsAVertex(const WorldPt p, short& index)
{
	for (short i = 1 ; i < fNumVerts ; i++) 
		if (p == Vertex(i)) {
			index = i;
			return true;
		}
	index = 0;
	return false;
}

WorldCoord GS_API TMCPolygon::Area()
{
	WorldCoord area = 0.0;
	WorldPt pt = Vertex(1);
	//Debug("poly area : %lf\n",area);
	for (short i = 2 ; i <= NumVerts() ;i++){
		//Debug("poly area : %lf\n",area);
		area += SignedTriangleArea(pt, Vertex(i), Vertex(i+1));
	}
	return fabs(area);
}


WorldPt GS_API TMCPolygon::Centroid()
{
	
	WorldPt centroid(0.0, 0.0);
	WorldPt pt = Vertex(1);
	WorldCoord centroidArea = 0.0;
	WorldCoord thisArea = 0.0;
	
	centroid = TriangleCentroid(fCBP, pt, Vertex(2), Vertex(3));
	centroidArea = SignedTriangleArea(pt, Vertex(2), Vertex(3) );
	
	for (short i = 3 ; i < NumVerts() ;i++) {
	
		thisArea = SignedTriangleArea(pt, Vertex(i), Vertex(i+1) );
		centroid = FulcrumPt(centroidArea, centroid, 
							thisArea, TriangleCentroid(fCBP, pt, Vertex(i), Vertex(i+1)) );
		centroidArea += thisArea;
	}
	return centroid;
}

Boolean GS_API TMCPolygon::ThisOffVectIntersectsNextOffVect(const short index, const WorldCoord offset)
{
	
	WorldPt a1 = Vertex(index);
	WorldPt a2 = a1+OffsetVector(index, offset);
	
	if (index < NumVerts() || Closed()) {
		WorldPt b1 = Vertex(index+1);
		WorldPt b2 = b1 + OffsetVector(index+1, offset);
		
		Boolean parallel;
		Boolean intOnLines;
		WorldPt sect;
		GS_LineLineIntersect(fCBP,a1,a2,b1,b2,parallel,intOnLines,sect);
		//if (intOnLines) Debug("intOnLines\n");
		return (intOnLines);
	}
	else
		return false;
	
}

Boolean GS_API TMCPolygon::OffsetSegsIntersect(const short a, const short b,
										WorldCoord offset, WorldPt& sect)
{
	if (a > 0 && b <= NumVerts() ) {
		WorldPt a1 = OffsetVertex(a, offset);
		WorldPt a2 = OffsetVertex(a+1, offset);
		WorldPt b1 = OffsetVertex(b, offset);
		WorldPt b2 = OffsetVertex(b+1, offset);
		
		Boolean parallel;
		Boolean intOnLines;
		
		GS_LineLineIntersect(fCBP,a1,a2,b1,b2,parallel,intOnLines,sect);
		return intOnLines;
	}
	return false;
}


void GS_API TMCPolygon::RemoveBadOffsetVerts(Handle poly, const WorldCoord offset)
{

	if (poly) {
		WorldPt 	vert;			
		VertexType 	vType;
		WorldCoord 		radius;		
		
		short polyIndex = 1;
		while (polyIndex <= GS_CountVertices(fCBP,poly) ) {
			short i = 1;
			short numVerts = NumVerts();
			Boolean doDelete = false;
			while (i <= numVerts ) {
				GS_GetVertex(fCBP, poly, polyIndex, vert, vType, radius);
				
				WorldCoord scalProj = ScalarProjection(WorldPt(VectorFromSegStart(i, vert)), i);
				WorldCoord perpScalProj = PerpScalarProjection((VectorFromSegStart(i, vert)), i);
				
				
				if ( scalProj >= 0.0 && scalProj <= SegLength(i) ){
					if ( offset >= 0.0 && perpScalProj >= 0.0) {
						if (perpScalProj < offset-1)
							doDelete = true;
					}
					else if (offset <= 0.0 && perpScalProj <= 0.0) {
						if (perpScalProj > offset+1)
							doDelete = true;
					}
					
					if (doDelete) {
						DeleteVertex(polyIndex); 
						polyIndex--;
						i = numVerts;
					}
				}
				
				i++;
			}
			polyIndex++;
		}
	}
}

Boolean GS_API TMCPolygon::LastSegIntersectsSelf(short& indexPriorToIntersect, WorldPt& sect)
{
	WorldPt a1 = Vertex(NumVerts());
	WorldPt a2 = Vertex(NumVerts()-1);
	Boolean parallel, intOnLines;
	if (PolyHandle() && NumVerts() > 2) {	
		for ( indexPriorToIntersect = NumVerts()-3; indexPriorToIntersect > 0; indexPriorToIntersect--) {
			WorldPt b1 = Vertex(indexPriorToIntersect);
			WorldPt b2 = Vertex(indexPriorToIntersect+1);
			if ((WorldRect(a1, a2).Intersects(WorldRect(b1, b2)))) {
				GS_LineLineIntersect(fCBP,WorldPt(a1),WorldPt(a2),WorldPt(b1),WorldPt(b2), parallel, intOnLines, sect);
				if (intOnLines)
				{
					return true;
				}
			}
		}
	}
	return false;
}

WorldCoord GS_API TMCPolygon::TurnsThroughDeg()
{
	short numVerts = NumVerts();
	WorldCoord val = 0.0;
	for (short i = 2; i< numVerts; i++) {
		if (ConcaveOnLeft(i) )
			val += AngleBetweenDeg(i);
		else
			val -= AngleBetweenDeg(i);
	}
	if (Closed()) {
		if (ConcaveOnLeft(numVerts) )
			val += AngleBetweenDeg(numVerts);
		else
			val -= AngleBetweenDeg(numVerts);
		if (ConcaveOnLeft(1) )
			val += AngleBetweenDeg(1);
		else
			val -= AngleBetweenDeg(1);
	
	}
	return val;
}
void GS_API TMCPolygon::DrawCoordPoly()
{
	short numVerts = NumVerts();
	for (short i = 1 ; i <= numVerts-1; i++) 
		GS_DrawCoordLine(fCBP,Vertex(i),Vertex(i+1));
	if (Closed()) 
		GS_DrawCoordLine(fCBP,Vertex(numVerts),Vertex(1));
	
}

Boolean GS_API TMCPolygon::TooSmall(const short i, const WorldCoord thresh)
{
	if (PolyHandle()) {
		if (SegLength(i+1) != 0.0 && SegLength(i)/SegLength(i+1) < thresh && i > 0  && i < NumVerts()-1  ) {
			return true;
		}
	}
	return false;
}

Boolean GS_API TMCPolygon::SectPtOn(const WorldPt& p)
/*	p is assumed to intersect a segment or (extension of) that defines one of the sides */ 
{	
	short numVerts = Closed() ? NumVerts()+1 : NumVerts();
	WorldRect polyBounds;
	GS_GetObjectBounds(fCBP,PolyHandle(),polyBounds);
	
	for (short i = 1 ; i < numVerts ; i++) {

		WorldRect r(Vertex(i),Vertex(i+1));
		WorldPt vector = p-Vertex(i);
		(void) ScalarProjection(vector,i);
		WorldPt projPt = Vertex(i) + VectorProjection(vector,i);
		
#ifndef WINVER
		if (r.ContainsPoint(WorldPt(p)) && 
			WorldPt(p-projPt).Magnitude() < 1.0)
#else
		WorldPt xp(p-projPt);
		if (r.ContainsPoint(WorldPt(p)) && 
			xp.Magnitude() < 1.0)
#endif
			return true;
	}
	
	
	return false;
}
