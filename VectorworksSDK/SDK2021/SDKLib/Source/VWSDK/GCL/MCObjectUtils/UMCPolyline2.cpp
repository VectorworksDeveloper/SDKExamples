//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// MiniCad polyline object utility class
	

#include "StdHeaders.h"
#include "GCL/Unclassified.h"
#include "GCL/UMCPolyline.h"
#include "GCL/UMCPolygon.h"
#include "GCL/ULine.h"


void GS_API TMCPolyline::DrawControlPoints()
{
	for (short i = 1 ; i <= fNumVerts ; i++) {
		
		Handle p = GS_CreateLine(fCBP,this->PriorControlPoint(i),this->ControlVertex(i));
		GS_DrawObject(fCBP,p,true);
		Handle q = GS_CreateLine(fCBP,this->NextControlPoint(i),this->ControlVertex(i));
		GS_DrawObject(fCBP,q,true);
	}
	
}

WorldCoord GS_API TMCPolyline::GetPolyLength()
{
	WorldCoord length = 0.0;
	for (short i = 1 ; i < fNumVerts ; i++) 
		length += this->SegLength(i,true);
	
	if (fClosed) {
		length += this->SegLength(fNumVerts,true);
	}
	
	return length;
}

Handle GS_API TMCPolyline::ControlPolygon()
{
	Handle h = GS_CreatePolyshape(fCBP);
	for (short i = 1 ; i <= NumVerts() ; i++) 
		::GS_AddVertex(fCBP, h, ControlVertex(i), vtCorner, 0L);
	GS_SetPolyShapeClose(fCBP, h, Closed());
	GS_SetFillPat(fCBP,h,0);
	GS_DrawObject(fCBP,h,true);
	
	return h;
}

short GS_API TMCPolyline::AddSplineCntrolPtsAt(const short index)
{
	VertexType vType;
	WorldCoord arcRadius;
	WorldPt oldVertex;
	short numAdded = 0;
	
	short i = IndexInRange(index);
	GS_GetVertex(fCBP, PolyHandle(), i , oldVertex, vType, arcRadius);
	if (vType == vtBezier || vType == vtCubic) {
		WorldPt newCntrlpt1;
		WorldPt newCntrlpt2;
		if (vType == vtBezier) {
			newCntrlpt1 = Vertex(i) + VectorToPriorControlPoint(i) * 0.5;
			newCntrlpt2 = Vertex(i) + VectorToNextControlPoint(i) * 0.5;
		}
		else {									// cubic control vertex	
			WorldPt p1,p2,p3,p4;				// 	1/2 & 3/4 pts of control triangle sides
			p1 = ControlVertex(i) + VectorToPriorControlPoint(i)*0.5;
			p2 = ControlVertex(i) + VectorToPriorControlPoint(i)*0.75;
			p3 = ControlVertex(i) + VectorToNextControlPoint(i)*0.5;
			p4 = ControlVertex(i) + VectorToNextControlPoint(i)*0.75;
			WorldPt v = p3-p1;					
			newCntrlpt1 = MidPoint( p2, p1 + (0.25 * v) );
			newCntrlpt2 = MidPoint( p4, p3 + (-0.25 * v) );
		}
		
		//if (VertType(i-1) != vtCorner) {
		//	InsertVertex(PriorControlPoint(i), i+numAdded+1, vType, arcRadius);
		//	numAdded++;
		//	i++;
		//}
		//if (VertType(i+numAdded+1) != vtCorner) {
		//	InsertVertex(NextControlPoint(i), i+numAdded+1, vType, arcRadius);
		//	numAdded++;
		//}
		
		SetVertex(i, newCntrlpt1, vType, arcRadius);

		InsertVertex(newCntrlpt2, i+1, vType, arcRadius);
		numAdded++;
		
	}
	return numAdded;
}
void GS_API TMCPolyline::AddSplineControlPts()
{
	short i = 1;
	while (i <= NumVerts() ){
		if (VertType(i) == vtBezier || VertType(i) == vtCubic) {
			
			i = + AddSplineCntrolPtsAt(i)+1;
		}
		else
			i++;
	}
}

void GS_API TMCPolyline::SetArcRad(const short index)
{
	WorldPt vertex;
	WorldPt prevPt;
	WorldPt nextPt;
	WorldPt centerPt;
	if ( ControlNeighborhood(index, prevPt, vertex, nextPt, centerPt) == vtArc) {
		SetVertex(index, vertex, VertType(index), (prevPt-centerPt).Magnitude());
	}
}
void GS_API TMCPolyline::AddSplineControlPtsAndSetArcRad()
{
	short i = 1L;
	while (i <= NumVerts() ){
	
		if (VertType(i) == vtBezier || VertType(i) == vtCubic) {
			//Subst3CntrlPts(i);
			i=i+3;
		}
		else if (VertType(i) == vtArc) {
			SetArcRad(i);
			i++;
		}
		else
			i++;
	}
}


void GS_API TMCPolyline::AdjustArcVertex(const short index)
{
	WorldPt vertex, startPt, endPt, centerPt;
	WorldPt arcEndPt1, arcEndPt2;
	
	if (ControlNeighborhood(index, vertex, startPt, endPt, centerPt) == vtArc) {
		arcEndPt1 = startPt;
		arcEndPt2 = endPt;
		WorldCoord radius = (centerPt-endPt).Magnitude();

		if (!IntersectArcWithSeg(fCBP, centerPt, radius, Vertex(index), Vertex(index-1), arcEndPt1)) {
		
			if (!IntersectArcWithSeg(fCBP, centerPt, radius, Vertex(index-1), Vertex(index-2), arcEndPt1)) {
				arcEndPt1 = Vertex(index);
			}
			else 
				SetVertex(index-1, arcEndPt1, VertType(index-1), MCArcRadius(index));
		}
		if (!IntersectArcWithSeg(fCBP, centerPt, radius, Vertex(index), Vertex(index+1), arcEndPt2)) {
		
			if (!IntersectArcWithSeg(fCBP, centerPt, radius, Vertex(index+1), Vertex(index+2), arcEndPt1)) {
				arcEndPt2 = Vertex(index);
			}
			else
				SetVertex(index+1, arcEndPt1, VertType(index-1), MCArcRadius(index));
		}
		WorldPt newArcVertex = GetArcVertex(index,arcEndPt1,centerPt,arcEndPt2);
		SetVertex(index, newArcVertex, vtArc, radius);
	}
}

void GS_API TMCPolyline::AddCornerVertsBetweenCurveVerts()
{
	WorldPt prevPt;
	WorldPt vertex;
	WorldPt nextPt;
	WorldPt centerPt;

	short i = 1;
	
	while (i <= NumVerts()) {
		if (VertType(i+1) != vtCorner &&
			ControlNeighborhood(i, prevPt, vertex, nextPt, centerPt) != vtCorner) {
			InsertVertex(nextPt, i+1, vtCorner, 0L);
			i+=2;
		}
		else
			i++;
	}
	
}

void GS_API TMCPolyline::OffsetControlVerts(const WorldCoord offset)
{
	short numVerts = NumVerts();
	WorldCoord radius;
	VertexType vType;
	
	for (short j = 1 ; j <=  numVerts ; j++) {	
					
		if (VertType(j) == vtArc)
			radius = OffsetRadius(j,offset);
		if (radius <= 0.0)
			vType = vtCorner;
		else 
			vType =  VertType(j);
		//Debug("OffsetControlVerts  vert #%ld has offset  : %ld\n",j,offset);
		WorldPt v = OffsetVertex(j,offset,true);
		SetVertex(j, v , vType, fabs(radius));
	}
}

WorldPt GS_API TMCPolyline::GetArcVertex(const short index, const WorldPt arcCenter, 
									const WorldPt arcBeg, const WorldPt arcEnd)
{
	WorldPt newArcVertex;

	WorldPt u = WorldPt(arcBeg-arcCenter).Normal();
	WorldPt v = WorldPt(arcEnd-arcCenter).Normal();

	WorldCoord angle = (0.5)*::AngleBetweenRad(u,v);
	WorldCoord radius = WorldPt(arcBeg-arcCenter).Magnitude();
	
	if (angle != Pi/2.0) {
		if (ConcaveOnLeft(IndexInRange(index),false) ) {
			newArcVertex = arcCenter + double(radius/cos(angle)) *::UnitVector(v-u);
		}
		else {
			newArcVertex = arcCenter + double(radius/cos(angle)) *::UnitVector(u-v);
		}
	}
	else
		newArcVertex = arcCenter;
		
	return newArcVertex;
}

void GS_API TMCPolyline::AddCurveEndPointsAtVert(const short index)
{
	VertexType vType;
	WorldCoord arcRadius;
	WorldPt oldVertex;
	short i = IndexInRange(index);
	GS_GetVertex(fCBP, PolyHandle(), i , oldVertex, vType, arcRadius);
	if (vType != vtCorner) {
	
		if (VertType(i-1) != vtCorner)
			this->InsertVertex(ControlVertex(i) + VectorToPriorControlPoint(i), i, vtCorner, 0.0);
		if (VertType(i+1) != vtCorner)
			this->InsertVertex(ControlVertex(i) + VectorToNextControlPoint(i), i+1, vtCorner, 0.0);
	}
}

void GS_API TMCPolyline::AddCurveEndPoints()
{
	WorldCoord numVerts = NumVerts();
	for (short i = 1 ; i <= numVerts ; i++) {
		AddCurveEndPointsAtVert(i);
	}
}
