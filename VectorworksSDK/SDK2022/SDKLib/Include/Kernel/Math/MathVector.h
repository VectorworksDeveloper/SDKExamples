//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


// *************************************************************
// Coordinate routines
// *************************************************************

Boolean GS_API InclusiveBetween(short a, short b, short c);
Boolean GS_API InclusiveBetween(float a, float b, float c);
inline Boolean GS_API InclusiveBetween(WorldCoord a, WorldCoord b, WorldCoord c)
{
	// replaced WorldCoord1_GT_WorldCoord2(c, b) with c > b, because if c and b are equal, it doesn't
	// matter which case is executed; replaced WorldCoord1_GE_WorldCoord2 and WorldCoord1_LE_WorldCoord2
	// with their code because the compiler was having trouble inlining them [BF 11/5/02]
	return (c > b) ?	
		( ((a > b) || WorldCoordsAreNearlyEqual(a, b)) && ((a < c) || WorldCoordsAreNearlyEqual(a, c)) ) :
		( ((a < b) || WorldCoordsAreNearlyEqual(a, b)) && ((a > c) || WorldCoordsAreNearlyEqual(a, c)) );
}


#define DEFINE_BETWEEN(BaseType) \
	inline Boolean GS_API InclusiveBetween(BaseType a, BaseType b, BaseType c)\
	{\
		return (c > b) ? (a >= b && a <= c) : (a <= b && a >= c);\
	}

DEFINE_BETWEEN(short)
DEFINE_BETWEEN(float)


// *************************************************************
// Vector routines
// *************************************************************

inline WorldCoord GS_API VectorMagnitude(const Vector &p) { return p.Magnitude(); }
inline Vector     GS_API VectorNormal(const Vector &p) { return p.Normal(); }
inline Vector     GS_API VectorSum(const Vector &p1, const Vector &p2) { return(p1+p2); }
inline Vector     GS_API VectorDifference(const Vector &p1, const Vector &p2) 
	{ return(p2-p1); }
inline Vector     GS_API VectorNegative(const Vector &p) { return(-p); }
inline Vector     GS_API VectorAbs(const Vector &p) { return p.Abs(); }
inline Vector     GS_API VectorScalarProduct(const Vector &p, double_param s) // operands different
	{ return(p*s); }
inline Vector     GS_API VectorScalarQuotient(const Vector &p, double_param s)
	{ return(p/s); }


// *************************************************************
// WorldPt & FracPt & FixedPt Routines
// *************************************************************


inline WorldPt    GS_API SetWorldPt(WorldCoord x, WorldCoord y) { return WorldPt(x,y); }
inline WorldPt    GS_API WorldPtCenter(const WorldPt &p1, const WorldPt &p2)
	{ return (p1+p2).Half(); }
inline WorldPt    GS_API WorldPtsXNormal(const WorldPt &p1, const WorldPt &p2)
	{ return WorldPt(p2-p1).Normal(); }
inline WorldPt    GS_API WorldPtSetLength(const WorldPt &dir, WorldCoord length)
	{ return dir.Normal() * length; }
inline WorldPt    GS_API WorldPtDifference(const WorldPt& p1, const WorldPt& p2)
	{ return p2-p1; }
inline WorldPt    GS_API WorldPtSum(const WorldPt& p1, const WorldPt& p2)
	{ return p1+p2; }
inline Boolean    GS_API WorldPtEqual(const WorldPt& p1, const WorldPt& p2)
	{ return p1==p2; }
inline Boolean    GS_API WorldPtBetween(const WorldPt& p, const WorldPt& low, const WorldPt& high) // operands different
	{ return (InclusiveBetween(p.x, low.x, high.x) && InclusiveBetween(p.y, low.y, high.y)); }

inline WorldCoord GS_API WorldPtLength(const WorldPt& p1, const WorldPt& p2)
	{ return((p1-p2).Magnitude()); }
inline double_gs  GS_API WorldPtXLength(const WorldPt& p1, const WorldPt& p2)
	{ return (WorldPt(p1-p2).Magnitude()); } 
inline WorldPt    GS_API WorldPtOffset(const WorldPt& p, const Vector2& dir, WorldCoord dist)
	{ return p + dir * dist; }
inline WorldPt    GS_API WorldPtXOffset( const WorldPt& p, const WorldPt& dir, double_param dist)
	{ return p + WorldPt(dir*dist); }
inline WorldPt    GS_API WorldPtProjectOntoFracPt(const Vector2& onto, const WorldPt& p, const WorldPt& offset)
{
	Vector2 unitOnto = onto.Normal();
	return offset + unitOnto * DotProduct(unitOnto, p);
}
double_gs  GS_API WorldPtXDistanceToLine(const WorldPt& p, const WorldPt& end1, const WorldPt& end2, WorldPt& intersect);
inline WorldPt GS_API WorldPtPerpendicular(const WorldPt& p)
{
	WorldPt						r;

	r.x = p.y;
	r.y = -p.x;
	return r;
}

void       GS_API WorldPtRotate(WorldPt& p, double_param degrees, const WorldPt& origin);
WorldPt    GS_API WorldPtFromXAngle(double_param degrees, WorldCoord length);

inline void       GS_API WorldPtNegative(WorldPt &p) { p = -p; }
inline WorldPt    GS_API WorldPtNormal(const WorldPt &p) { return(p.Normal()); }
inline WorldPt    GS_API WorldPtScalarProduct(const WorldPt &p, double_param s)
	{ return p*s; }


// *************************************************************
// WorldPt3 & FracPt3 Routines
// *************************************************************

inline WorldPt3   GS_API WorldPt3ScalarFracProduct(const WorldPt3 &p, double_param s) // operands different
	{ return p * s; }
inline WorldPt3   GS_API WorldPt3Sum(const WorldPt3 &p1, const WorldPt3 &p2)
	{ return (p1+p2); }
WorldPt3   GS_API WorldPt3Difference(const WorldPt3 &p1, const WorldPt3 &p2);
inline Boolean    GS_API WorldPt3IsZero(const WorldPt3 &p) { return p.IsZero(); }
inline WorldCoord GS_API WorldPt3Magnitude(const WorldPt3 &p) { return p.Magnitude(); }
inline WorldPt3   GS_API SetWorldPt3(WorldCoord x, WorldCoord y, WorldCoord z)
	{ return WorldPt3(x, y, z); }
inline Boolean    GS_API WorldPt3Equal(const WorldPt3 &p1, const WorldPt3 &p2)
	{ return p1 == p2; }
inline WorldPt3   GS_API WorldPt3Center(const WorldPt3 &p1, const WorldPt3 &p2)
	{ return (p1+p2).Half(); }
WorldPt    GS_API WorldPt3CenterPt(const WorldPt3 &p1, const WorldPt3 &p2);
inline WorldPt3   GS_API WorldPt3Negative(const WorldPt3 &p) { return -p; }
inline WorldPt3   GS_API WorldPt3Offset(const WorldPt3& p, const Vector& dir, WorldCoord dist) // operands different
	{ return p + dir * dist; }

// *************************************************************
// Conversion Routines
// *************************************************************

inline WorldPt  WorldPt3ToWorldPt(const WorldPt3 &p)					{ return WorldPt(p.x, p.y); }
inline WorldPt3 WorldPtToWorldPt3(const WorldPt &p, WorldCoord z = 0)	{ return WorldPt3(p.x, p.y, z); }

inline WorldPt3 VectorToWorldPt3(const Vector &p)						{ return p; }
inline Vector   WorldPt3ToVector(const WorldPt3 &p)						{ return p; }


// *************************************************************
// Angle routines
// *************************************************************

Degrees GS_API WorldPtFindFixedAngle(const WorldPt& p1, const WorldPt& p2);
Degrees GS_API FindXAngle(WorldCoord x, WorldCoord y);
short   GS_API FindQuadrant(const Degrees& degrees);
void    GS_API FixedAngleToWorldPt(const Degrees&  degrees, const WorldRect& onRect, WorldPt& p);
inline void    GS_API ShortAngleToWorldPt(short degrees, const WorldRect& onRect, WorldPt& p)
{
	UnknownAngleType newAngle = degrees;
	FixedAngleToWorldPt(newAngle, onRect, p);
}

Degrees GS_API AngleBetweenWorldPt3s(const WorldPt3 &p1, const WorldPt3 &p2);


// *************************************************************
// WorldRect routines
// *************************************************************


Boolean GS_API SegmentCanCross(const WorldRect& r, const WorldPt& p1, const WorldPt& p2);
Boolean GS_API Segment3CanCross(const WorldRect& r, const WorldPt3& p1, const WorldPt3& p2);
inline WorldPt GS_API WorldRectCenter(const WorldRect& r) { return r.Center(); }
inline void    GS_API WorldRectUnionPoint(const WorldPt& p, WorldRect& r) { r.Unite(p); }
inline void    GS_API SetWorldRect(WorldRect& r, WorldCoord left, WorldCoord top, WorldCoord right, WorldCoord bottom)
	{ r.Set(left, top, right, bottom); }
inline void    GS_API WorldRectUnionRect(const WorldRect& r1, const WorldRect& r2, WorldRect& rUnion)
	{ rUnion = r1.Union(r2); }
inline Boolean GS_API WorldRectEqual(const WorldRect& r1, const WorldRect& r2)
	{ return r1 == r2; }
inline void    GS_API WorldRectInset(WorldRect& r, WorldCoord dx, WorldCoord dy)
	{ r.Inset(dx, dy); }
inline void    GS_API WorldRectOffset(WorldRect& r, const WorldPt& p) // operands different
	{ r.Offset(p); }
Boolean GS_API WorldRectIntersect(const WorldRect& r1, const WorldRect& r2, WorldRect& rIntersect);
inline Boolean GS_API WorldRectSurrounded(const WorldRect &r, const WorldRect& surroundedBy)
	{ return (surroundedBy.ContainsPoint(r.TopLeft()) && surroundedBy.ContainsPoint(r.BotRight())); }
inline Boolean GS_API WorldRectIsEmpty(const WorldRect& r) { return r.IsEmpty(); }
inline Boolean GS_API WorldRectIsZero(const WorldRect& r) // Note - this has changed!
	{ return (r == WorldRect(0, 0, 0, 0)); }
inline void    GS_API MakeWorldRectEmpty(WorldRect &r) { r.MakeEmpty(); }
inline void    GS_API WorldRectFromPoints(const WorldPt &p1, const WorldPt &p2, WorldRect &r)
	{ r.Set(p1, p2); }

// *************************************************************
// Cube routines
// *************************************************************


inline WorldCube GS_API SetCube(WorldCoord top, WorldCoord bottom, WorldCoord right, WorldCoord left, WorldCoord front, WorldCoord back)
{
	WorldCube c;
	c.Set(top, bottom, right, left, front, back);
	return c;
}
inline void      GS_API MakeCubeEmpty(WorldCube &c) { c.MakeEmpty(); }
inline void      GS_API SetCubeToZero(WorldCube &c) { c.Set(0L, 0L, 0L, 0L, 0L, 0L); }
inline WorldCube GS_API CubeFromPoints(const WorldPt3 &p1, const WorldPt3 &p2)
{
	WorldCube c;
	c.Set(p1, p2);
	return c;
}
inline Boolean   GS_API CubeIsEmpty(const WorldCube &c) // Note = this has changed! [MAF 2/11/00]
	{ return c.IsEmpty(); }
inline Boolean   GS_API CubeIsZero(const WorldCube &c) { return c.IsZero(); }
inline void      GS_API CubeUnionPoint(const WorldPt3 &p, WorldCube &c) { c.Unite(p); }
inline void      GS_API CubeUnionCube(const WorldCube &c1, const WorldCube &c2, WorldCube &cUnion)
	{ cUnion = c1.Union(c2); }
inline WorldPt3  GS_API CubeCenter(const WorldCube &c) { return(c.Center()); }
inline WorldRect GS_API CubeFrontRect(const WorldCube &c) { return c.FrontWorldRect(); }

// *************************************************************
// Standard Interfaces extension routines
// *************************************************************

#ifdef _MINICAD_

void   RectUnionPoint(ViewPt p, ViewRect& r);
void   ViewRectUnionViewPt(ViewPt p, ViewRect& r);
inline short  ShortLength(ViewPt p1, ViewPt p2)
	{ return Num2Short(sqrt(xpwr2(p1.x - p2.x) + xpwr2(p1.y - p2.y))); }
void   PointToFixedAngle(const ViewRect& bounds, ViewPt mouse, Degrees& myAngle);
ViewPt SetPoint(short h, short v);
ViewPt SetViewPt(short h, short v);
#endif

