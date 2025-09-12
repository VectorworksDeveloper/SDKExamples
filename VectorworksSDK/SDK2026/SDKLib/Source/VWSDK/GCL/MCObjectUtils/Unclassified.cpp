//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// General utility routines


#include "StdHeaders.h"
#include "GCL/Unclassified.h"
#include "GCL/ULine.h"
#include "GCL/UMCPolygon.h"
#include "GCL/UArc.h"

const double myPi = 3.141592653589793;
const double myRadToDeg = 180.0 / myPi;		
const double myDegToRad = myPi/180.0;		


Boolean GS_API OnLeftOf(const WorldPt onLeftVector,const WorldPt onLeftOfVector)
{
	WorldPt onLeftVectorPerp(-onLeftVector.y,onLeftVector.x);
	Boolean onLeftProjPos = DotProduct(onLeftVector.Normal(),onLeftOfVector.Normal()) > 0.0;
	Boolean onLeftPerpProjPos = DotProduct(onLeftVectorPerp.Normal(),onLeftOfVector.Normal()) > 0.0;
	
	return ((onLeftProjPos && !onLeftPerpProjPos) || (!onLeftProjPos && !onLeftPerpProjPos));
}

Boolean GS_API XPtOnOval(const WorldPt XPt, const WorldRect oval, const WorldCoord tollerence)
{
	WorldCoord a = (oval.right-oval.left)/2.0;
	WorldCoord b = (oval.top-oval.bottom)/2.0;
	WorldPt v = XPt - oval.Center();
	return xpwr2(v.x)/xpwr2(a) + xpwr2(v.y)/xpwr2(b) - 1.0 <= tollerence;
}

Boolean GS_API XPtInlineBounds(const WorldPt xPt, const WorldPt startPt, const WorldPt endPt)
{ 
	return 	((startPt.x <= xPt.x && xPt.x <= endPt.x) || 
					(endPt.x <= xPt.x && xPt.x <= startPt.x)) &&
			((startPt.y <= xPt.y && xPt.y <= endPt.y) || 
					(endPt.y <= xPt.y && xPt.y <= startPt.y)); 
}


WorldPt GS_API UnitVectorFromDeg(const WorldCoord DegAngle)
{
	WorldPt unitV(cos(DegToRad*DegAngle),sin(DegToRad*DegAngle));
	return unitV;
}
WorldPt GS_API UnitVectorFromRad(const WorldCoord RadAngle)
{
	WorldPt unitV(cos(RadAngle),sin(RadAngle));
	return unitV;
}


WorldCoord GS_API ATanAngleRad(WorldPt vector)
{
	if (vector.IsZero())
		return 0.0;
		
	if (vector.x == 0L) {
		if (vector.y > 0L)
			return myPi;
		else
			return -myPi;
	}
				
	return atan(vector.y/vector.x);
	
}

short GS_API VectorQuadrant(WorldPt vector)
{
	if (vector.IsZero())
		return -1;
		
	if (vector.x == 0L) {
		if (vector.y > 0L)
			return 90;
		else
			return 270;
	}
			
	if (vector.y == 0L) {
		if (vector.x > 0L)
			return 0;
		else
			return 180;
	}
		
	if (vector.x > 0L) {
		if (vector.y > 0L)
			return 1;
		else
			return 4;
	}
	else {	
		if (vector.y > 0L)
			return 2;
		else
			return 3;
	}
	
}

WorldCoord GS_API Angle0To2Pi(WorldPt vector)
{
	switch (VectorQuadrant(vector)) {
		case 2 : 
		case 3 : {
			return ATanAngleRad(vector) + myPi;
		}
		case 4 : {
			return ATanAngleRad(vector) + 2*myPi;
		}
		case 180 : {
			return myPi;
		}
		case 90 : {
			return myPi/2.0;
		}
		case -90 : {
			return 3*myPi/2.0;
		}
	}
	return ATanAngleRad(vector);
}


WorldCoord GS_API PosAngle0To360(WorldCoord angle)
{
	if (fabs(angle) <= 360.0) {
		if (angle > 0.0 ) {
			return angle;
		}
		else {
			return 360.0 + angle;
		}
	}
	else {
		WorldCoord a;
		if (angle >= 0.0) {
			a = fmod(angle, 360) + (angle/360.0 - fmod(angle, 360));
		}
		else {
			a = -( fmod(-angle, 360) + (-angle/360.0 - fmod(-angle, 360)));
		}
		return a;	
	}
	
}

void GS_API PlaceCircleAt(CallBackPtr cbp, WorldPt p, WorldCoord rad)
{
	WorldRect bounds(p.x-rad,p.y+rad,p.x+rad,p.y-rad);
	Handle h = GS_CreateArcN(cbp,bounds, 0.0, 360.0);
	//AddAfterSwapObject(cbp, h);
	GS_SetFillPat(cbp,h,0);
	GS_DrawObject(cbp,h,false);

}
WorldCoord GS_API ArcSweep(const WorldCoord& startAngle, const WorldCoord& endAngle, const Boolean /*minorArc*/)
{
	WorldPt u = UnitVectorFromDeg(startAngle);	
	WorldPt v = UnitVectorFromDeg(endAngle);	
	return AngleBetweenDeg(u, v);
}

WorldPt GS_API MidPoint(const WorldPt point1, const WorldPt point2)
{
	WorldPt mdpt((point1.x+point2.x)/2.0, (point1.y+point2.y)/2.0);
	return mdpt;
}

WorldCoord GS_API TriangleArea(const WorldPt vector1, const WorldPt vector2)
{
	return 0.5*PerpScalarProjection(vector1, vector2)*vector2.Magnitude();
}


WorldCoord GS_API SignedTriangleArea(const WorldPt p1, const WorldPt p2, const WorldPt p3)
{
	WorldPt v2 = p3-p2;
	WorldPt v1 = p2-p1;
	WorldCoord area = TriangleArea(v1, v2);
	//Debug("area : %lf\n",area);
	return (OnLeftOf(v2, v1) ? -area : area);
}

WorldPt GS_API TriangleCentroid(CallBackPtr cbp, const WorldPt p1, const WorldPt p2, const WorldPt p3)
{
	WorldPt centroid(0.0,0.0);
	Boolean onLines, parallel;
	GS_LineLineIntersect(cbp, p1, MidPoint(p2, p3), p2, MidPoint(p1, p3), 
						parallel, onLines, centroid);
	//PlaceCircleAt(cbp,WorldPt(centroid), 100);
	return centroid;
}


WorldPt GS_API UnitPerpVector(const WorldPt vector)
{
	WorldPt retVector;
	retVector.x = -UnitVector(vector).y;
	retVector.y = UnitVector(vector).x;
	return retVector;

}


WorldCoord GS_API ScalarProjection(const WorldPt vector, const WorldPt ontoVector)
{
	if (!ontoVector.IsZero()) {
		return DotProduct(vector, UnitVector(ontoVector));
	}
	return 0.0;
}


WorldPt GS_API VectorProjection(const WorldPt vector, const WorldPt ontoVector)
{
	WorldPt retVector(0.0,0.0);
	
	if (!ontoVector.IsZero()) {
		retVector = DotProduct(vector, UnitVector(ontoVector)) * UnitVector(ontoVector);
	}
	return retVector;
}

WorldCoord GS_API PerpScalarProjection(const WorldPt vector, const WorldPt ontoVector)
{
	if (!ontoVector.IsZero()) {
		return DotProduct(vector, UnitPerpVector(ontoVector));
	}
	return 0.0;
}

WorldPt GS_API PerpVectorProjection(const WorldPt vector, const WorldPt ontoVector)
{
	WorldPt retVector(0.0,0.0);
	
	if (!ontoVector.IsZero()) {
		retVector = DotProduct(vector, UnitPerpVector(ontoVector)) * UnitPerpVector(ontoVector);
	}
	return retVector;
}

WorldPt GS_API FulcrumPt(const WorldCoord f1, const WorldPt p1, const WorldCoord f2, const WorldPt p2)
{
	if ((f2-f1) == 0.0)
		return p1 + (p2-p1).Magnitude()/2.0 * UnitVector(p2-p1);
	else {
		return p1 + (f2*(p2-p1).Magnitude()*UnitVector(p2-p1))/(f2+f1);
	}
	
}
WorldCoord GS_API SplineArea(CallBackPtr cbp, const WorldPt p1, const WorldPt p2, const WorldPt p3, WorldCoord level)
{
	WorldPt m1 = MidPoint(p1, p2);
	WorldPt m3 = MidPoint(p3, p2);
	WorldPt m2 = MidPoint(m1, m3);
	WorldCoord area = TriangleArea(p2-p1,p3-p2);
	//Debug("area : %lf ; level %ld\n",area,level);
	GS_DrawCoordLine(cbp,m1,m3);
	if (level < 3) {
		WorldCoord a = SplineArea(cbp,p1,m1,m2,level+1);
		WorldCoord b = SplineArea(cbp,m2,m3,p3,level+1);
		return a + b;
	}
	else
		return area;
		
}
WorldCoord GS_API MaxDisplacementFrom(const WorldPt fromPt, const WorldPt p1, 
								const WorldPt p2, const WorldPt p3)
{
	return Max(	Max((fromPt-p1).Magnitude(),(fromPt-p2).Magnitude()) , (fromPt-p3).Magnitude());
}
WorldCoord GS_API TrianglePointMoment(CallBackPtr cbp,const WorldPt p1, const WorldPt p2, const WorldPt p3,
							WorldPt point, WorldCoord min, WorldCoord level)
{
	//WorldPt tc = TriangleCentroid(cbp, p1, p2, p3);
	//WorldCoord area = TriangleArea(p2-p1,p3-p1);
	//Debug("level %ld MaxDisp %lf\n",level,MaxDisplacementFrom(tc,p1,p2,p3));
	WorldPt m1 = MidPoint(p1,p2);
	WorldPt m2 = MidPoint(p2,p3);
	WorldPt m3 = MidPoint(p3,p1);
	Handle h = GS_CreateLine(cbp,p1,p2);
	GS_DrawObject(cbp,h,false);
	h = GS_CreateLine(cbp,p3,p2);
	GS_DrawObject(cbp,h,false);
	h = GS_CreateLine(cbp,p1,p3);
	GS_DrawObject(cbp,h,false);
	
	if (level < 5) {
		WorldCoord a = TrianglePointMoment(cbp,m1,p1,m3,point,min,level+1);
		WorldCoord b = TrianglePointMoment(cbp,m1,p2,m2,point,min,level+1);
		WorldCoord c = TrianglePointMoment(cbp,m2,p3,m3,point,min,level+1);
		WorldCoord d = TrianglePointMoment(cbp,m1,m2,m3,point,min,level+1);
		return a+b+c+d;
	}
	else {
		return 1.0;
	} 					
}


Boolean GS_API IntersectArcWithSeg(CallBackPtr cbp, const WorldPt centerPt, const WorldCoord radius, 
							const WorldPt nearPt, const WorldPt farPt,WorldPt& sect)
{
	Sect2Struct sects;
	Boolean sect1 = false, sect2 = false;
	WorldRect r;
	r.Set(WorldPt(centerPt), WorldCoord(radius));
	GS_LineEllipseIntersect(cbp, nearPt, farPt, r, sects);
	sects.legal1 = sects.legal1 && XPtInlineBounds(sects.int1, nearPt, farPt);
	sects.legal2 = sects.legal2 && XPtInlineBounds(sects.int2, nearPt, farPt);
	if (sects.legal1 && sects.legal2) {
		if ((nearPt-sects.int1).Magnitude() < (nearPt-sects.int2).Magnitude() ) {
			sect = sects.int1;
			sect1 = true;
		}
		else {
			sect = sects.int2;
			sect2 = true;
		}
	}
	else if (sects.legal1) {
		sect = sects.int1;
		sect1 = true;
	}
	else if (sects.legal2) {
		sect = sects.int2;
		sect2 = true;
	}
	else {
		return false;
	}
	if (sect1)
		PlaceCircleAt(cbp, sects.int1,200);
	if (sect2)
		PlaceCircleAt(cbp, sects.int2,500);
	
	return true;
}
					


void GS_API SplineCntrlTriangles(CallBackPtr cbp,const WorldPt p1, const WorldPt p2, const WorldPt p3,
							WorldCoord level, WorldCoord maxLevel)
{
	WorldPt m1 = MidPoint(p1,p2);
	WorldPt m2 = MidPoint(p2,p3);
	WorldPt m3 = MidPoint(m1,m2);
	Handle h = GS_CreateLine(cbp,m1,m2);
	GS_DrawObject(cbp,h,false);
	h = GS_CreateLine(cbp,p1,m3);
	GS_DrawObject(cbp,h,false);
	h = GS_CreateLine(cbp,m3,p3);
	GS_DrawObject(cbp,h,false);
	
	if (level < maxLevel) {
		SplineCntrlTriangles(cbp,p1,m1,m3,level+1,maxLevel);
		SplineCntrlTriangles(cbp,m3,m2,p3,level+1,maxLevel);
	}
}


void GS_API DrawCoordSpline(CallBackPtr cbp,const WorldPt sP1, const WorldPt sP2, const WorldPt sP3,
						WorldCoord level, const WorldCoord maxLevel)
{
	WorldPt m1 = MidPoint(sP1,sP2);
	WorldPt m2 = MidPoint(sP2,sP3);
	WorldPt m3 = MidPoint(m1,m2);
	if (level < maxLevel) {
		DrawCoordSpline(cbp,sP1,m1,m3,level+1,maxLevel);
		DrawCoordSpline(cbp,m3,m2,sP3,level+1,maxLevel);
	}
	else
		GS_DrawCoordLine(cbp,m1,m2);

}


Boolean GS_API PtOnOrInsideTri(const WorldPt thePt, const WorldPt p1, const WorldPt p2, const WorldPt p3)
{
	return ( 	( PerpScalarProjection(p2-p1, thePt-p1) * PerpScalarProjection(p3-p2, thePt-p2) >= 0.0) 
				&&
				( PerpScalarProjection(p3-p2, thePt-p2) * PerpScalarProjection(p1-p3, thePt-p3) >= 0.0)
			);
}

Boolean GS_API PtOnSpline(CallBackPtr cbp,const WorldPt sP1, const WorldPt sP2, const WorldPt sP3,
					const WorldPt thePt, WorldCoord level, const WorldCoord maxLevel)
{
	Boolean inLeftTriangle = false;
	Boolean inRightTriangle = false;
	WorldPt m1 = MidPoint(sP1,sP2);
	WorldPt m2 = MidPoint(sP2,sP3);
	WorldPt m3 = MidPoint(m1,m2);
	
	if (level < maxLevel) {
		
		inLeftTriangle = PtOnSpline(cbp,sP1,m1,m3,thePt,level+1,maxLevel);
		inRightTriangle = PtOnSpline(cbp,m3,m2,sP3,thePt,level+1,maxLevel);
		
		//Debug("level : %ld L:%d R:%d\n",level,inLeftTriangle,inRightTriangle);
		return inLeftTriangle || inRightTriangle;
	}
	else
		return PtOnOrInsideTri(thePt, sP1, sP2, sP3);
}

Boolean GS_API OnObject(CallBackPtr cbp, Handle obj, const WorldPt thePoint)
{
	Boolean retVal = false;
	//Debug("GetObjectType(cbp,obj) : %ld\n",GetObjectType(cbp,obj));
	
	switch(gSDK->GetObjectTypeN ( obj)) {
		case lineNode :{
			TLine line(cbp,obj);
			
			retVal =  XPtInlineBounds(thePoint, line.StartPt(), line.EndPt());
			break;
		}
		case arcNode : {
			TMCArc arc(cbp, obj);
			WorldCoord x = thePoint.x-arc.ArcCenter().x;
			WorldCoord y = thePoint.y-arc.ArcCenter().y;
			WorldCoord a = ( (arc.DefBounds()).right - (arc.DefBounds()).left )/2.0;
			WorldCoord b = ( (arc.DefBounds()).top - (arc.DefBounds()).bottom )/2.0;
			if (b!=0.0)
				//Debug("(x*x)/(a*a)+(y*y)/(b*b)  : %lf\n",(x*x)/(a*a)+(y*y)/(b*b));
				//Debug("arc check to zero  : %lf\n",(x*x)/(a*a)+(y*y)/(b*b)-1.0);
				if (fabs((x*x)/(a*a)+(y*y)/(b*b)-1) < 1.0e-3) {
				
					WorldCoord posSweep, negSweep;
					arc.SweepToPoint(thePoint, posSweep, negSweep);
					WorldCoord sweep = arc.SweepAngle();
					if (sweep > 0.0) {
						if (posSweep < sweep)
							retVal = true;;
					}
					else {
						if (negSweep > sweep)
							retVal = true;;
					}
				}
			break;			
		}
		case rBoxNode :
		case boxNode : 
		case polylineNode : {
			Handle h = GS_ConvertToPolygon(cbp, obj, true);
			if (h) {
				TMCPolygon poly(cbp,h);
				retVal = poly.SectPtOn(thePoint);
				GS_DeleteObject(cbp,h, false);
			}
			break;
		}
		case polyNode : {
			TMCPolygon poly(cbp,obj);
			retVal =  poly.SectPtOn(thePoint);
			break;
		}
		case ovalNode : return true; break;
	}
	return retVal;
}
Boolean GS_API AngleTooSharp(CallBackPtr cbp, Handle poly, const short i, WorldCoord minAngle)
{
	TMCPolygon p(cbp, poly);
	return (AngleBetweenDeg(p.Vertex(i-1)-p.Vertex(i), p.Vertex(i)-p.Vertex(i+1)) < minAngle);
}

Boolean GS_API PointOnSegment(CallBackPtr cbp, const WorldPt p, Handle line)
{
	if (gSDK->GetObjectTypeN (  line) == lineNode) {
		WorldPt s,e;	// start and endpoints of line
		GS_GetEndPoints(cbp,line,s,e);
		//Debug("pointonSegment returns %ld\n",(XPtInlineBounds(p,s,e) && AngleBetweenRad(p-s,e-s) < 1));
		return (XPtInlineBounds(p,s,e) && AngleBetweenRad(p-s,e-s) < 1);
	}
	else 
		return false;
}

void GS_API CopyAttributes(CallBackPtr cbp, Handle source, Handle dest)
{
	if ( source && dest ) {
		gSDK->SetPenPatN(dest, gSDK->GetPenPatN(source));
		
		GS_SetFillPat(cbp, dest, GS_GetFillPat(cbp, source));
		//Debug("GetFillPat(cbp, source) : %ld\n",GetFillPat(cbp, source));
		GS_SetLineWeight(cbp, dest, GS_GetLineWeight(cbp, source));
		ObjectColorType colors;
		GS_GetColor(cbp, source, colors);
		GS_SetColor(cbp, dest, colors);

		//OpacityRef	opacity	= ::GS_GetOpacity( cbp, source );
		// ::GS_SetOpacity( cbp, dest, opacity );

		OpacityRef penOpacity, fillOpacity;
		penOpacity = fillOpacity = 100;
		gSDK->GetOpacityN(source, penOpacity, fillOpacity);
		gSDK->SetOpacityN(dest, penOpacity, fillOpacity);

		Boolean penOpacityByClass, fillOpacityByClass;
		penOpacityByClass = fillOpacityByClass = false;

		gSDK->GetOpacityByClassN(source,	penOpacityByClass, fillOpacityByClass );
		gSDK->SetOpacityByClassN(dest,		penOpacityByClass, fillOpacityByClass );

		unsigned char acceptsMarkers = kObjXPropAcceptsMarkersNone;
		GS_GetObjectPropertyChar(cbp, source, kObjXPropAcceptsMarkers, acceptsMarkers);
		if(acceptsMarkers != kObjXPropAcceptsMarkersNone) {
			
			SMarkerStyle startMarker;
			SMarkerStyle endMarker;
			CBBoolean startVis, endVis;
			
			GS_GetObjBeginningMarker(cbp, source, startMarker, startVis);
			GS_GetObjEndMarker(cbp, source, endMarker, endVis);

			GS_SetObjBeginningMarker(cbp, dest, startMarker, startVis);
			GS_SetObjEndMarker(cbp, dest, endMarker, endVis);
		}

		GS_SetObjectClass(cbp, dest, GS_GetObjectClass(cbp, source));

		if (GS_GetFPatByClass(cbp, source))
			GS_SetFPatByClass(cbp, dest);
		if (GS_GetFColorsByClass(cbp, source))
			GS_SetFColorsByClass(cbp, dest);
		if (GS_GetPPatByClass(cbp, source))
			GS_SetPPatByClass(cbp, dest);
		if (GS_GetPColorsByClass(cbp, source))
			GS_SetPColorsByClass(cbp, dest);
		if (GS_GetLWByClass(cbp, source))
			GS_SetLWByClass(cbp, dest);
		if (GS_GetArrowByClass(cbp, source))
			GS_SetArrowByClass(cbp, dest);

		// Copy fill space info
		short type;
		TVariableBlock value;
		GS_GetObjectVariable(cbp, dest, ovFillType, value);
		value.GetSint16(type);
		if (type == kFillHatch || type == kFillGradient || type == kFillImage) {
			Boolean wasEdited;
			GS_GetObjectVariable(cbp, source, ovFillLocalMapping, value);
			value.GetBoolean(wasEdited);
			if (type != kFillHatch || wasEdited) {
				GS_SetObjectVariable(cbp, dest, ovFillLocalMapping, value);
				GS_GetObjectVariable(cbp, source, ovFillMaintainAspectRatio, value);
				GS_SetObjectVariable(cbp, dest, ovFillMaintainAspectRatio, value);
				GS_GetObjectVariable(cbp, source, ovFillOriginPt, value);
				GS_SetObjectVariable(cbp, dest, ovFillOriginPt, value);
				GS_GetObjectVariable(cbp, source, ovFillAngle, value);
				GS_SetObjectVariable(cbp, dest, ovFillAngle, value);
				GS_GetObjectVariable(cbp, source, ovFillIAxisLength, value);
				GS_SetObjectVariable(cbp, dest, ovFillIAxisLength, value);
				GS_GetObjectVariable(cbp, source, ovFillJAxisLength, value);
				GS_SetObjectVariable(cbp, dest, ovFillJAxisLength, value);
				GS_GetObjectVariable(cbp, source, ovFillRepeat, value);
				GS_SetObjectVariable(cbp, dest, ovFillRepeat, value);
				GS_GetObjectVariable(cbp, source, ovFillMirror, value);
				GS_SetObjectVariable(cbp, dest, ovFillMirror, value);
				GS_GetObjectVariable(cbp, source, ovFillFlip, value);
				GS_SetObjectVariable(cbp, dest, ovFillFlip, value);
				GS_GetObjectVariable(cbp, source, ovFillGeometryType, value);
				GS_SetObjectVariable(cbp, dest, ovFillGeometryType, value);
			}
		}

	}
}
