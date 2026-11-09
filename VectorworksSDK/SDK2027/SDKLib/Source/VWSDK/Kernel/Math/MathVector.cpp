//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Implements a set of useful vector-math functions and classes.
//

#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-COMMENT LINE.  [DMB, 4/2/96]

#ifndef _MINICAD_
	#define UNDEF_PASCAL 0
#endif

// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE



// *************************************************************
// WorldPt & FracPt & FixedPt Routines
// *************************************************************


double_gs GS_API WorldPtXDistanceToLine(const WorldPt& p, const WorldPt& end1, const WorldPt& end2, WorldPt& intersect)
{
	WorldPt lineVec = end2-end1;
	WorldPt pointVec = p-end1;

	intersect = WorldPtProjectOntoFracPt(lineVec, pointVec, end1);
	return (WorldPt(intersect) - WorldPt(p)).Magnitude();
	
}


void GS_API WorldPtRotate(WorldPt& p, double_param degrees, const WorldPt& origin) 
{
	double_gs					radians = degrees * kRadiansPerDegree;
	double_gs 					angleCos = cos(radians);
	double_gs 					angleSin = sin(radians);
	WorldPt						spinPt;

	spinPt = p - origin;
	p.x = (spinPt.x * angleCos - spinPt.y * angleSin) + origin.x;
	p.y = (spinPt.x * angleSin + spinPt.y * angleCos) + origin.y;
}


WorldPt GS_API WorldPtFromXAngle(double_param degrees, WorldCoord length)
{
	WorldPt r;
	r.SetAngle(degrees * kRadiansPerDegree);
	r *= length;
	return r;
}



// *************************************************************
// WorldPt3 & FracPt3 Routines
// *************************************************************


WorldPt3 GS_API WorldPt3Difference(const WorldPt3 &p1, const WorldPt3 &p2)
{
//buggy
#if 0
	return(p2-p1);
#else
	WorldPt3 r1, r2;
	r1 = p2 - p1;

	r2.x = p2.x - p1.x;
	r2.y = p2.y - p1.y;
	r2.z = p2.z - p1.z;
	
	#ifdef _MINICAD_
	#ifdef BUG
	if (r1 != r2)
		DSTOP((kPaul, brief, "WorldPt3Difference failed!"));
	#endif
	#endif
	
	return r1;
#endif
}


WorldPt GS_API WorldPt3CenterPt(const WorldPt3 &p1, const WorldPt3 &p2)
{
	WorldPt	r;

	r.x = (p1.x + p2.x) / 2.0;
	r.y = (p1.y + p2.y) / 2.0;
	return r;
}


// *************************************************************
// Angle routines
// *************************************************************

// [JDW FP Angle, June 99]

Degrees GS_API WorldPtFindFixedAngle(const WorldPt& p1, const WorldPt& p2)
{
	
	WorldCoord						dx;
	WorldCoord						dy;
	Degrees						angle;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dx == 0) {
		angle = (dy < 0) ? 270.0 : 90.0;
	}
	else {
		angle = atan2(dy, dx) * kDegreesPerRadian;
		if (angle < 0)
			angle += 360.0;
	}
	return angle;
}

Degrees GS_API FindXAngle(WorldCoord x, WorldCoord y)
{
	Degrees					theAngle;

	if (x == 0 && y == 0) theAngle = 0.0;
	else theAngle = kDegreesPerRadian * atan2(y, x);
	
	return theAngle;
}

short GS_API FindQuadrant(const Degrees& degrees)
{
	double_gs angle = degrees;
	
	while (angle < 0.0)
		angle += 360.0;
		
	while (angle > 360.0)
		angle -= 360.0;

	if (angle > 270.0)
		return 4;
	else if (angle > 180.0)
		return 3;
	else if (angle > 90.0)
		return 2;
	else
		return 1;
}


void GS_API FixedAngleToWorldPt(const Degrees& degrees, const WorldRect& onRect, WorldPt& p)
{
	UnknownAngleType						theAng;
	WorldPt						center;
	WorldPt						radius;

	center = onRect.Center();
	radius.x = (onRect.Right() - onRect.Left()) / 2.0;
	radius.y = (onRect.Top() - onRect.Bottom()) / 2.0;

	theAng = degrees * kRadiansPerDegree;
	p.y = center.y + radius.y * cos(theAng);
	p.x = center.x + radius.x * sin(theAng);
}


Degrees GS_API AngleBetweenWorldPt3s(const WorldPt3 &p1, const WorldPt3 &p2)
{

	if (p1.IsZero() || p2.IsZero()) {
		return 0.0;
	}
	else {
		WorldPt3 na, nb;
		na = WorldPt3(p1).Normal();
		nb = WorldPt3(p2).Normal();
		WorldCoord cosine = DotProduct(na, nb);
		cosine = min(max(cosine,-1.0),1.0); ///< Numerical error could produce a dot product slightly outside range
		return kDegreesPerRadian * acos(cosine);
	}
}


// *************************************************************
// WorldRect routines
// *************************************************************


Boolean GS_API WorldRectIntersect(const WorldRect& r1, const WorldRect& r2, WorldRect& rIntersect)
{
/*
	rIntersect.SetLTRB(Max(r1.Left(), r2.Left()),
			Min(r1.Top(), r2.Top()),
			Min(r1.Right(), r2.Right()),
			Max(r1.Bottom(), r2.Bottom()));
	
	return (rIntersect.Top() >= rIntersect.Bottom() && rIntersect.Right() >= rIntersect.Left());
	*/
	rIntersect = r1;
	rIntersect.Intersect(r2);
	return !rIntersect.IsEmpty();
}





// *************************************************************
// WorldRect routines
// *************************************************************

Boolean GS_API SegmentCanCross(const WorldRect& r, const WorldPt& p1, const WorldPt& p2)
{
	if ( r.IsEmpty() )
		return false;
	if (p1.y > r.Top() && p2.y > r.Top()) return false;
	if (p1.y < r.Bottom() && p2.y < r.Bottom()) return false;
	if (p1.x < r.Left() && p2.x < r.Left()) return false;
	if (p1.x > r.Right() && p2.x > r.Right()) return false;
	return true;
}


Boolean GS_API Segment3CanCross(const WorldRect& r, const WorldPt3& p1, const WorldPt3& p2)
/*
 ## Returns true if line can potentially cross box.
*/
{
	if (p1.y > r.Top() && p2.y > r.Top()) return false;
	if (p1.y < r.Bottom() && p2.y < r.Bottom()) return false;
	if (p1.x < r.Left() && p2.x < r.Left()) return false;
	if (p1.x > r.Right() && p2.x > r.Right()) return false;
	return true;
}



// *************************************************************
// Standard Interface extension routines
// *************************************************************

#ifdef _MINICAD_

void RectUnionPoint(ViewPt p, ViewRect& r)
{
	if (p.x > r.Right())
		r.SetRight(p.x);
	else if (p.x < r.Left())
		r.SetLeft(p.x);

	if (p.y < r.Top())
		r.SetTop(p.y);
	else if (p.y > r.Bottom())
		r.SetBottom(p.y);
}

// We should be calling the high-level builtin functions here. [MAF 11/29/00]
void ViewRectUnionViewPt(ViewPt p, ViewRect& r)
{
	if (p.x > r.Right())
		r.SetRight(p.x);
	else if (p.x < r.Left())
		r.SetLeft(p.x);

	if (p.y < r.Top())
		r.SetTop(p.y);
	else if (p.y > r.Bottom())
		r.SetBottom(p.y);
}

void PointToFixedAngle(const ViewRect& bounds, ViewPt p, Degrees& degrees)
{
	degrees = atan2(p.x * 2.0 - (bounds.Right() + bounds.Left()),
					bounds.Top() + bounds.Bottom() - p.y * 2.0)  * kDegreesPerRadian;
	if (degrees < 0) {
		degrees += 360.0;
	}
	if (degrees > 360.0) {
		degrees -= 360.0;
	}
}


ViewPt SetPoint(short h, short v)
{
	ViewPt	r;
	r.x = h;
	r.y = v;
	return r;
}

ViewPt SetViewPt(short x, short y)
{
	ViewPt	r;
	r.x = x;
	r.y = y;
	return r;
}

#endif
