//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	General utility routines

#ifndef _UNCLASSIFIED_
#define _UNCLASSIFIED_

// GS_SDKPPC_JAK	Changing "extended" to "double"
const double UCPi = 3.141592653589793;
const double UCRadToDeg = 180.0 / UCPi;		
const double UCDegToRad = UCPi/180.0;		



Boolean GS_API OnLeftOf(const WorldPt onLeftVector,const WorldPt onLeftOfVector);
Boolean GS_API XPtOnOval(const WorldPt, const WorldRect oval, const WorldCoord tollerence);
Boolean GS_API XPtInlineBounds(const WorldPt xPt, const WorldPt startPt, const WorldPt endPt);
inline WorldCoord AngleBetweenRad(const WorldPt vector1, const WorldPt vector2)
	{ return acos(DotProduct(vector1.Normal(), vector2.Normal())); }
inline WorldCoord AngleBetweenDeg(const WorldPt vector1, const WorldPt vector2)
	{ return AngleBetweenRad(vector1, vector2) * UCRadToDeg; }
WorldPt GS_API UnitVectorFromDeg(const WorldCoord DegAngle);
WorldPt GS_API UnitVectorFromRad(const WorldCoord RadAngle);	
WorldCoord GS_API ATanAngleRad(WorldPt vector);
inline WorldCoord ATanAngleDeg(WorldPt vector) { return  ATanAngleRad(vector) * UCRadToDeg; }
WorldCoord GS_API Angle0To2Pi(WorldPt vector);
WorldCoord GS_API PosAngle0To360(WorldCoord angle);
inline WorldCoord Angle0To360(WorldPt vector) {return Angle0To2Pi(vector) * UCRadToDeg; }
short GS_API VectorQuadrant(WorldPt vector);
WorldCoord GS_API PosAngle(WorldCoord angle);
void GS_API PlaceCircleAt(CallBackPtr cbp, WorldPt p, WorldCoord rad);
WorldCoord GS_API ArcSweep(const WorldCoord& startAngle, const WorldCoord& endAngle, const Boolean minorArc);

WorldCoord GS_API AngleTurnDeg(const WorldPt prevVector, const WorldPt turnedVector);

WorldPt GS_API MidPoint(const WorldPt point1, const WorldPt point2);
WorldCoord GS_API TriangleArea(const WorldPt vector1, const WorldPt vector2);
WorldCoord GS_API SignedTriangleArea(const WorldPt point1, const WorldPt point2, const WorldPt point3);
WorldPt GS_API TriangleCentroid(CallBackPtr cbp, const WorldPt point1, const WorldPt point2, const WorldPt point3);

inline WorldPt UnitVector(const WorldPt vector) { return vector.Normal(); }
WorldPt GS_API UnitPerpVector(const WorldPt vector);
WorldCoord GS_API ScalarProjection(const WorldPt vector, const WorldPt ontoVector);
WorldPt GS_API VectorProjection(const WorldPt vector, const WorldPt ontoVector);
WorldCoord GS_API PerpScalarProjection(const WorldPt vector, const WorldPt ontoVector);
WorldPt GS_API PerpVectorProjection(const WorldPt vector, const WorldPt ontoVector);
WorldPt GS_API FulcrumPt(const WorldCoord f1, const WorldPt p1, const WorldCoord f2, const WorldPt p2);
WorldCoord GS_API SplineArea(CallBackPtr cbp,const WorldPt p1, const WorldPt p2, const WorldPt p3, WorldCoord level);
WorldCoord GS_API TrianglePointMoment(CallBackPtr cbp,const WorldPt p1, const WorldPt p2, const WorldPt p3,
							WorldPt point, WorldCoord min, WorldCoord level);
WorldCoord GS_API MaxDisplacementFrom(const WorldPt fromPt, const WorldPt p1, 
								const WorldPt p2, const WorldPt p3);
								
Boolean GS_API IntersectArcWithSeg(CallBackPtr cbp, const WorldPt centerPt, const WorldCoord radius, 
							const WorldPt nearPt, const WorldPt farPt,WorldPt& sect);
void GS_API SplineCntrlTriangles(CallBackPtr cbp,const WorldPt p1, const WorldPt p2, const WorldPt p3,
							WorldCoord level, WorldCoord maxLevel);
Boolean GS_API PtOnOrInsideTri(const WorldPt thePt, const WorldPt p1, const WorldPt p2, const WorldPt p3);							
Boolean GS_API PtOnSpline(CallBackPtr cbp,const WorldPt sP1, const WorldPt sP2, const WorldPt sP3,
					const WorldPt thePt, WorldCoord level, const WorldCoord maxLevel);
void GS_API DrawCoordSpline(CallBackPtr cbp,const WorldPt sP1, const WorldPt sP2, const WorldPt sP3,
						WorldCoord level, const WorldCoord maxLevel);
Boolean GS_API OnObject(CallBackPtr cbp, Handle obj, const WorldPt thePoint);
Boolean GS_API AngleTooSharp(CallBackPtr cbp, Handle poly,const short i, WorldCoord minAngle);					
Boolean GS_API PointOnSegment(CallBackPtr cbp, const WorldPt p, Handle line);
void GS_API CopyAttributes(CallBackPtr cbp, Handle source, Handle dest);

					
#endif
