//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;

#ifdef _DEBUG
# define CHECK_INNERDATA_CONSISTENCY		this->CheckInnerDataConsistency()
#else
# define CHECK_INNERDATA_CONSISTENCY
#endif

VWArc2D::VWArc2D()
{
	fRadius			= 0;
	fStartAngleDeg	= 0;
	fSweepAngleDeg	= 0;
}

VWArc2D::VWArc2D(const VWPoint2D& center, double radius)
{
	this->SetArc( center, radius );
}

VWArc2D::VWArc2D(const VWPoint2D& center, double radius, double startAngleDeg, double sweepAngleDeg)
{
	this->SetArc( center, radius, startAngleDeg, sweepAngleDeg );
}

VWArc2D::VWArc2D(const VWPoint2D& startPT, const VWPoint2D& ptOnArc, const VWPoint2D& endPt)
{
	this->SetArc( startPT, ptOnArc, endPt );
}

VWArc2D::VWArc2D(const VWArc2D& src)
{
	fCenterPt			= src.fCenterPt;
	fStartPt			= src.fStartPt;
	fEndPt				= src.fEndPt;

	fRadius				= src.fRadius;
	fStartAngleDeg		= src.fStartAngleDeg;
	fSweepAngleDeg		= src.fSweepAngleDeg;

	if ( fRadius > 0 ) {
		CHECK_INNERDATA_CONSISTENCY;
	}
}

VWArc2D::~VWArc2D()
{
}

VWArc2D& VWArc2D::operator=(const VWArc2D& src)
{
	fCenterPt			= src.fCenterPt;
	fStartPt			= src.fStartPt;
	fEndPt				= src.fEndPt;

	fRadius				= src.fRadius;
	fStartAngleDeg		= src.fStartAngleDeg;
	fSweepAngleDeg		= src.fSweepAngleDeg;

	return *this;
}

void VWArc2D::SetArc(const VWPoint2D& center, double radius)
{
	this->SetArc( center, radius, 0, 360 );
	CHECK_INNERDATA_CONSISTENCY;
}

void VWArc2D::SetArc(const VWPoint2D& startPt, const VWPoint2D& ptOnArc, const VWPoint2D& endPt)
{
	fStartPt				= startPt;
	fEndPt					= endPt;
	fCenterPt.ThreePtCenter( fStartPt, ptOnArc, fEndPt );

	VWPoint2D	startDir	= fStartPt - fCenterPt;
	VWPoint2D	endDir		= fEndPt - fCenterPt;
	fRadius					= fCenterPt.DistanceTo( fStartPt );
	VWFC_ASSERT( MathUtils::Equalish( fRadius, fCenterPt.DistanceTo( ptOnArc ), 0.0001 ) );
	VWFC_ASSERT( MathUtils::Equalish( fRadius, fCenterPt.DistanceTo( fEndPt ), 0.0001 ) );

	fStartAngleDeg			= startDir.CalcAng360();
	double		endAngDeg	= endDir.CalcAng360();
	if ( endAngDeg < fStartAngleDeg )
		endAngDeg		+= 360;
	fSweepAngleDeg			= endAngDeg - fStartAngleDeg;

	VWFC_ASSERT( fSweepAngleDeg >= 0.0 );	// not expected - must not happen - check.

	// check whether the 'ptOnArc' is exactly in the arc seep (between the start and end angles as defined until now).

	double		ptSweep		= ( ( ptOnArc - fCenterPt ).CalcAng360() - fStartAngleDeg );

	if ( ptSweep < 0 )		ptSweep	+= 360;	// make sure it is positive.

	// accurate check. no epsilon used.
	if ( ptSweep > fSweepAngleDeg )			// 'ptOnArc' is not in the arc sweep.
	{
		fSweepAngleDeg		-= 360;			// invert the sweep.
	}

	CHECK_INNERDATA_CONSISTENCY;
}

void VWArc2D::SetArc(const VWPoint2D& center, double radius, double startAngleDeg, double sweepAngleDeg)
{
	fCenterPt			= center;

	// ensure proper positive [0;360] start angle
	while ( startAngleDeg < 0 )
		startAngleDeg	+= 360;
	while ( MathUtils::GEish( startAngleDeg, 360, VWPoint2D::sEpsilon ) )
		startAngleDeg	-= 360;
	
	VWPoint2D	a, b;
	a.SetAngle( MathUtils::Deg2Rad( startAngleDeg ) );
	b.SetAngle( MathUtils::Deg2Rad( startAngleDeg + sweepAngleDeg ) );

	fStartPt			= fCenterPt + radius * a;
	fEndPt				= fCenterPt + radius * b;

	fRadius				= radius;
	fStartAngleDeg		= startAngleDeg;
	fSweepAngleDeg		= sweepAngleDeg;

	CHECK_INNERDATA_CONSISTENCY;
}

void VWArc2D::GetArc(VWPoint2D& outCenter, double& outRadius) const
{
	outCenter		= fCenterPt;
	outRadius		= fRadius;
}

void VWArc2D::GetArc(VWPoint2D& outCenter, double& outRadius, double& outStartAngleDeg, double& outSweepAngleDeg) const
{
	outCenter			= fCenterPt;
	outRadius			= fRadius;
	outStartAngleDeg	= fStartAngleDeg;
	outSweepAngleDeg	= fSweepAngleDeg;
}

void VWArc2D::GetArc(VWPoint2D& outStartPt, VWPoint2D& outPtOnArc, VWPoint2D& outEndPt) const
{
	outStartPt			= fStartPt;
	outEndPt			= fEndPt;
	outPtOnArc			= this->GetPtOnArc();
}

const VWPoint2D& VWArc2D::GetCenterPt() const
{
	return	( fCenterPt );
}

VWPoint2D& VWArc2D::GetCenterPt()
{
	return	( fCenterPt );
}

const VWPoint2D& VWArc2D::GetStartPt() const
{
	return	( fStartPt );
}

VWPoint2D& VWArc2D::GetStartPt()
{
	return	( fStartPt );
}

const VWPoint2D& VWArc2D::GetEndPt() const
{
	return	( fEndPt );
}

VWPoint2D& VWArc2D::GetEndPt()
{
	return	( fEndPt );
}

VWPoint2D VWArc2D::GetPtOnArc() const
{
	VWPoint2D	dir		= fEndPt - fStartPt;
	dir.SetPoint( -dir.y, dir.x );
	dir.Normalize();

	// check if the found point is on the arc
	VWPoint2D	pt = fCenterPt + dir * fRadius;
	if ( this->IsPtOnArc( pt, VWPoint2D::sEpsilon ) )
		return pt;
	else
		return fCenterPt - dir * fRadius;
}

VWPoint2D VWArc2D::GetPtOnArc(double offset) const
{
	double		ang		= offset / fRadius;
	double		cosAng	= cos( ang );
	double		sinAng	= sin( ang );

	// translate the first point into local coords for rotation
	VWPoint2D	locPt	= fStartPt - fCenterPt;

	// rotate first local point
	VWPoint2D	pt;
	pt.x				= locPt.x * cosAng - locPt.y * sinAng;
	pt.y				= locPt.x * sinAng + locPt.y * cosAng;
	
	// transform back to global coords already rotated point
	pt					+= fCenterPt;

	return pt;
}

VWPoint2D VWArc2D::GetPtOnArcAngle(double angDeg) const
{
	double		ang		= MathUtils::Deg2Rad( angDeg );
	double		cosAng	= cos( ang );
	double		sinAng	= sin( ang );

	// translate the first point into local coords for rotation
	VWPoint2D	locPt	= fStartPt - fCenterPt;

	// rotate first local point
	VWPoint2D	pt;
	pt.x				= locPt.x * cosAng - locPt.y * sinAng;
	pt.y				= locPt.x * sinAng + locPt.y * cosAng;
	
	// transform back to global coords already rotated point
	pt					+= fCenterPt;

	return pt;
}

double VWArc2D::GetRadius() const
{
	return fRadius;
}

double VWArc2D::GetStartAngle() const
{
	return fStartAngleDeg;
}

double VWArc2D::GetSweepAngle() const
{
	return fSweepAngleDeg;
}

double VWArc2D::GetLength() const
{
	return fRadius * MathUtils::Deg2Rad( fSweepAngleDeg );
}

double VWArc2D::GetLength(const VWPoint2D& pt) const
{
	VWPoint2D	vecPt		= pt - fCenterPt;
	VWPoint2D	vecStart	= fStartPt - fCenterPt;
	double		cosAng		= vecPt.Normalize().DotProduct( vecStart.Normalize() );
	double		ang			= acos( cosAng );

	return fRadius * ang;
}

double VWArc2D::CalcSweepAngle(const VWPoint2D& pt) const
{
	VWPoint2D	vecPt		= pt - fCenterPt;
	VWPoint2D	vecStart	= fStartPt - fCenterPt;
	double		ang			= vecPt.CalcAng360() - vecStart.CalcAng360();

	return ang;
}

VWPoint2D VWArc2D::PtPerpArc(const VWPoint2D& pt) const
{
#if 1
	VWPoint2D perpPt = pt - fCenterPt;

	if (pt.Equal(fCenterPt, kNearlyEqualEpsilonForWorldCoords)) {
		perpPt = fStartPt;
	}
	else {
		perpPt.Normalize();
		perpPt *= this->GetRadius();
		perpPt += fCenterPt;
	}
#else
	VWPoint2D	vecPt		= pt - fCenterPt;
	VWPoint2D	vecStart	= fStartPt - fCenterPt;
	double		cosAng		= vecPt.Normalize().DotProduct( vecStart.Normalize() );
	double		sinAng		= (cosAng >= 1.0) ? 0.0 : sqrt( 1 - cosAng * cosAng );

	// translate the first point into local coords for rotation
	VWPoint2D	locPt	= fStartPt - fCenterPt;

	// rotate first local point
	VWPoint2D	perpPt;
	perpPt.x			= locPt.x * cosAng - locPt.y * sinAng;
	perpPt.y			= locPt.x * sinAng + locPt.y * cosAng;
	
	// transform back to global coords already rotated point
	perpPt				+= fCenterPt;
#endif

	return perpPt;
}

// returns the closest point to the arc segment or the closest arc segment end.
VWPoint2D VWArc2D::PtPerpArcSeg(const VWPoint2D& pt) const
{
	// init.
	VWPoint2D			resultPt;

	// check if the point coincides with the arc center.
	if ( pt.Equal( fCenterPt, kNearlyEqualEpsilonForWorldCoords ) )
	{
		resultPt		= fStartPt;
	}
	else
	{
		// get the normalized vector from the arc center to the point.
		VWPoint2D		vecCtoP		= ( pt - fCenterPt );

		// check whether the point sweep angle is between the arc's start and end sweep angles.
		bool			innPtSweep	= false;

		double			angle		= vecCtoP.CalcAng360();
		double			ptSweep		= ( angle - this->GetStartAngle() );

		double			arcSweepAng	= this->GetSweepAngle();

		if ( arcSweepAng >= 0.0 )	// positive sweep.
		{
			// ensure positive point sweep angle.
			if ( ptSweep < 0 )		ptSweep += 360;

			// check if ( 0 <= ptSweep <= arcSweepAng ).
			innPtSweep	= ( ptSweep >= 0.0 && ptSweep <= arcSweepAng );
		}
		else						// negative sweep.
		{
			// ensure negative point sweep angle.
			if ( ptSweep > 0 )		ptSweep -= 360;

			// check if ( 0 >= ptSweep >= arcSweepAng ).
			innPtSweep	= ( ptSweep <= 0.0 && ptSweep >= arcSweepAng );
		}

		if ( innPtSweep )	// good sweep.
		{
			vecCtoP.Normalize();

			resultPt	= ( fCenterPt + ( vecCtoP * this->GetRadius() ) );
		}
		else				// bad sweep (outside).
		{
			// get closest arc ending point.
			VWPoint2D	begArcPt	= this->GetStartPt();
			VWPoint2D	endArcPt	= this->GetEndPt();

			double		sqrDistBeg	= pt.DistanceSquaredTo( begArcPt );
			double		sqrDistEnd	= pt.DistanceSquaredTo( endArcPt );

			if ( sqrDistBeg < sqrDistEnd )	resultPt	= begArcPt;
			else							resultPt	= endArcPt;
		}
	}

	// result.
	return	( resultPt );
}

double VWArc2D::Distance(const VWPoint2D& pt) const
{
	VWPoint2D	ptOnArc	= this->PtPerpArc( pt );
	return pt.DistanceTo( ptOnArc );
}

bool VWArc2D::IsPtOnArc(const VWPoint2D& pt, double dEpsilon) const
{
	double		radius			= fCenterPt.DistanceTo( pt );
	if ( ! MathUtils::Equalish( radius, fRadius, dEpsilon ) )
		return false;
    
	VWPoint2D	ptDir		= pt - fCenterPt;
	double		angle		= ptDir.CalcAng360();
	double		ptSweep		= angle - fStartAngleDeg;

	bool	ptOnArc	= false;
	if ( MathUtils::Greaterish( fSweepAngleDeg, 0, dEpsilon ) ) {
		if ( ptSweep < 0 )		ptSweep += 360;
		// 0 <= ptSweep <= fSweepAngleDeg
		ptOnArc	= MathUtils::GEish( ptSweep, 0, dEpsilon ) && MathUtils::LEish( ptSweep, fSweepAngleDeg, dEpsilon );
	}
	else
	{
		if ( ptSweep > 0 )
		{
			ptSweep -= 360;
		}
		// 0 >= ptSweep >= fSweepAngleDeg
		ptOnArc	= MathUtils::LEish( ptSweep, 0, dEpsilon ) && MathUtils::GEish( ptSweep, fSweepAngleDeg, dEpsilon );
	}

	return ptOnArc;
}

bool VWArc2D::IsPtInOrOnArc(const VWPoint2D& pt, double dEpsilon) const
{
	bool result = false;

	if ( fCenterPt == pt )
	{
		// Fast check, center point is always in the arc
		result = true;
	}
	else if ( fCenterPt.DistanceTo( pt ) < dEpsilon + fRadius )
	{
		// Get the angle between the point and the center
		double angle = VWPoint2D( pt - fCenterPt ).CalcAng360();

		if ( fSweepAngleDeg == 360.0 )
		{
			// This is a circle and the point is closer to the center than the radius -> the point is in the circle
			result = true;
		}
		else if ( fStartAngleDeg + fSweepAngleDeg > 360.0 )
		{
			// Since we are working with values in the range [0, 360] and startAngle + sweepAngle > 360,
			// we have to check that the angle is in the ranges from below
			// Example - startAngle = 330, sweepAngle = 60 -> startAngle + sweepAngle - 360 = 30 -> we check for [330, 360] || [0, 30]
			result = Double1_GE_Double2( angle, fStartAngleDeg ) // [startAngle, 360]
				|| Double1_LE_Double2( angle, fStartAngleDeg + fSweepAngleDeg - 360.0 ); // [0, startAngle + sweepAngle - 360]
		}
		else
		{
			// Check if angle is in the range [startAngle, startAngle + sweepAngle]
			result = Double1_GE_Double2( angle, fStartAngleDeg ) && Double1_LE_Double2( angle, fStartAngleDeg + fSweepAngleDeg );
		}
	}

	return result;
}

bool VWArc2D::IsPtOnArc(const VWPoint2D& pt, double dEpsilon, double& outOffset) const
{
	double		radius			= fCenterPt.DistanceTo( pt );
	if ( ! MathUtils::Equalish( radius, fRadius, dEpsilon ) )
		return false;

	VWPoint2D	ptDir		= pt - fCenterPt;
	double		angle		= ptDir.CalcAng360();
	double		ptSweep		= angle - fStartAngleDeg;

	bool	ptOnArc	= false;
	if ( MathUtils::GEish( ptSweep, 0, dEpsilon ) ) {
		ptOnArc	= MathUtils::Greaterish( fSweepAngleDeg, 0, dEpsilon ) && MathUtils::LEish( ptSweep, fSweepAngleDeg, dEpsilon );
	}
	else {
		ptOnArc	= MathUtils::Lesserish( fSweepAngleDeg, 0, dEpsilon ) && MathUtils::GEish( ptSweep, fSweepAngleDeg, dEpsilon );
	}

	if ( ptOnArc ) {
		outOffset = Abs(ptSweep * kRadiansPerDegree * fRadius);
	}

	return ptOnArc;
}

void VWArc2D::GetPolygon(VWPolygon2D& outPoly, double stepAngleDeg/*=90*/, bool allowArcVerts/*=true*/) const
{
	const VWPoint2D&		cen		= this->GetCenterPt();
	const VWPoint2D&		a		= this->GetStartPt();
	const VWPoint2D&		b		= this->GetEndPt();

	double		rad			= this->GetRadius();
	double		sweepAng	= this->GetSweepAngle();

	outPoly.AddVertex( a );

	// add one set for every 'stepAngleDeg' degrees from the arc.
	size_t		cnt			= (size_t) (Abs(sweepAng) / stepAngleDeg) + 1;

	double		stepLen		= this->GetLength() / double(cnt);
	double		stepAng		= sweepAng / double(cnt);
	VWPoint2D	lastPt		= a;

	for ( size_t i = 0 ; i < cnt ; ++ i )
	{
		VWPoint2D	thisPt;

		if ( i == cnt - 1 )
		{
			thisPt	= b;
		}
		else
		{
			thisPt	= this->GetPtOnArc( double(i + 1) * stepLen );
		}

		if ( allowArcVerts )		// arc vertices allowed.
		{
			VWPoint2D		dir1	= (lastPt - cen).Normalize();
			VWPoint2D		dir2	= (thisPt - cen).Normalize();
			VWPoint2D		dir		= (dir1 + dir2).Normalize();
			double			x		= rad / cos( MathUtils::Deg2Rad( stepAng / 2 ) );

			// add arc vertex in between.
			outPoly.AddVertex( cen + dir * x, eVertexType_Arc, rad );
		}

		outPoly.AddVertex( thisPt );

		lastPt		= thisPt;
	}
}

// adds arc sample points (ordered to form polygon) to the poly.
// note: the 'resolution' is defined by the 'stepAngDeg'.
void VWArc2D::AddArcPolygonizationToPoly(VWPolygon2D& inOutPoly, bool addArcEnds, double stepAngDeg/*=5.0*/) const
{
	const VWPoint2D&			cenPt		= this->GetCenterPt();
	const VWPoint2D&			startPt		= this->GetStartPt();

	if ( addArcEnds )
	{
		inOutPoly.AddVertex( startPt );		// add arc start point.
	}

	double			radius		= this->GetRadius();

	// translate the first point into local coordinates for rotation.
	VWPoint2D		locPt		= ( startPt - cenPt );

	// add one set for every inner 'stepAngDeg' degrees from the this->

	size_t			cnt			= ( (size_t)( abs( this->GetSweepAngle() ) / stepAngDeg ) + 1 );

	double			stepLen		= ( this->GetLength() / cnt );

	-- cnt;

	VWPoint2D		innerPt;	// to store current calculated result.

	for ( size_t i = 0 ; i < cnt ; ++ i )
	{
		double		curAng		= ( ( ( i + 1 ) * stepLen ) / radius );

		double		cosAng		= cos( curAng );
		double		sinAng		= sin( curAng );

		// rotate first local point.
		innerPt.x	= ( locPt.x * cosAng - locPt.y * sinAng );
		innerPt.y	= ( locPt.x * sinAng + locPt.y * cosAng );
		
		// transform back to global coordinates already rotated point.
		innerPt		+= cenPt;

		// add.
		inOutPoly.AddVertex( innerPt );
	}

	if ( addArcEnds )
	{
		inOutPoly.AddVertex( this->GetEndPt() );	// add arc end point.
	}
}


bool VWArc2D::GetLineArcIntersection(const VWPoint2D& pt1, const VWPoint2D& pt2, VWPoint2D& ptSec1, VWPoint2D& ptSec2)
{
	bool		result = false;

	VWPoint2D   ptOnCircle1 = ptSec1;
	VWPoint2D   ptOnCircle2 = ptSec2;
	
	VWPoint2D	center		= this->GetCenterPt();
	double		r			= this->GetRadius();
	
	// https://math.stackexchange.com/questions/311921/get-location-of-vector-circle-intersection

	if ( r > VWPoint2D::sRawEpsilon && pt1.DistanceSquaredTo(pt2) > VWPoint2D::sRawEpsilon )
	{
		double		dx		= pt2.x - pt1.x;
		double		dy		= pt2.y - pt1.y;

		double		a		= dx * dx + dy * dy;
		double		b		= 2 * dx*(pt1.x - center.x) + 2 * dy*(pt1.y - center.y);
		double		c		= (pt1.x - center.x)*(pt1.x - center.x) + (pt1.y - center.y)*(pt1.y - center.y) - r * r;// if c>0 point is outside of the circle
		double		discr	= b * b - 4 * a*c;
		
		if ( discr >= 0 )
		{
			double		t1		= (-b - sqrt(discr)) / (2 * a);
			double		t2		= (-b + sqrt(discr)) / (2 * a);

			VWPoint2D	ptOnCircle1, ptOnCircle2;
			ptOnCircle1.x		= dx * t1 + pt1.x;
			ptOnCircle1.y		= dy * t1 + pt1.y;

			ptOnCircle2.x		= dx * t2 + pt1.x;
			ptOnCircle2.y		= dy * t2 + pt1.y;

			// Get arc
			VWPoint2D	ptA		= this->GetStartPt();
			VWPoint2D	ptB		= this->GetEndPt();

			VWPoint2D	ptDir	= ptB - ptA;

			// condition for point to be on the arc
			VWPoint2D	ptDirPt1 = ptOnCircle1 - ptA;
			VWPoint2D	ptDirPt2 = ptOnCircle2 - ptA;

			if ( this->IsPtOnArc( ptOnCircle1, VWPoint2D::sEpsilon ) )
			{
				ptSec1 = ptOnCircle1;
				ptSec2 = ptOnCircle1;
				result = true;
			}
			if ( this->IsPtOnArc( ptOnCircle2, VWPoint2D::sEpsilon ) )
			{
				if ( result )
					ptSec2 = ptOnCircle2;
				else
				{
					ptSec1 = ptOnCircle2;
					ptSec2 = ptOnCircle2;
					result = true;
				}
			}
		}
	}
	return result;

}

#ifdef _DEBUG
void VWArc2D::CheckInnerDataConsistency()
{
	// CHECK FORWARD
	{
		double		radius			= fCenterPt.DistanceTo( fStartPt );
		VWFC_ASSERT( MathUtils::Equalish( radius, fCenterPt.DistanceTo( fEndPt ), 0.0001 ) );

		VWPoint2D	startDir		= fStartPt - fCenterPt;
		VWPoint2D	endDir			= fEndPt - fCenterPt;

		double		startAngleDeg	= startDir.CalcAng360();
		double		endAngDeg		= endDir.CalcAng360();
		if ( endAngDeg < startAngleDeg )
			endAngDeg		+= 360;
//		double		sweepAngleDeg	= endAngDeg - fStartAngleDeg;


		VWFC_ASSERT( MathUtils::Equalish( radius, fRadius, 0.0001 ) );
		VWFC_ASSERT( MathUtils::Equalish( startAngleDeg, fStartAngleDeg, 0.0001 ) );
		//VWFC_ASSERT( MathUtils::Equalish( sweepAngleDeg, fSweepAngleDeg, 0.0001 ) );
	}

	// CHECK BACKWARD
	{
		VWPoint2D	a, b;
		a.SetAngle( MathUtils::Deg2Rad( fStartAngleDeg ) );
		b.SetAngle( MathUtils::Deg2Rad( fStartAngleDeg + fSweepAngleDeg ) );

		VWPoint2D	startPt		= fCenterPt + fRadius * a;
		VWPoint2D	endPt		= fCenterPt + fRadius * b;

		VWFC_ASSERT( MathUtils::Equalish( startPt, fStartPt, 0.0001 ) );
		VWFC_ASSERT( MathUtils::Equalish( endPt, fEndPt, 0.0001 ) );
	}
}
#endif

/*static*/ void	 VWArc2D::SelfTest()
{

	VWPoint2D	z(0,		0 );
	VWPoint2D	a(-10,		0);
	VWPoint2D	b(0,		-10);
	VWPoint2D	c(7.071,	7.071);
	VWPoint2D	d(-7.071,	-7.071);

	VWArc2D	arc11( z, 10, 180, 90 );	// small arc
	VWArc2D	arc12( z, 10, 270, -90 );

	VWArc2D	arc21( z, 10, 270, 270 );	// big arc
	VWArc2D	arc22( z, 10, 180, -270 );

	VWArc2D	arc31( a, d, b );		// small arc
	VWArc2D	arc32( a, c, b );		// big arc

	ASSERTN( kVStanev, arc11.IsPtOnArc( d, 0.0001 ) );		// small arc
	ASSERTN( kVStanev, arc12.IsPtOnArc( d, 0.0001 ) );
	ASSERTN( kVStanev, arc31.IsPtOnArc( d, 0.0001 ) );

	ASSERTN( kVStanev, ! arc11.IsPtOnArc( c, 0.0001 ) );	// small arc
	ASSERTN( kVStanev, ! arc12.IsPtOnArc( c, 0.0001 ) );
	ASSERTN( kVStanev, ! arc31.IsPtOnArc( c, 0.0001 ) );

	ASSERTN( kVStanev, arc21.IsPtOnArc( c, 0.0001 ) );		// big arc
	ASSERTN( kVStanev, arc22.IsPtOnArc( c, 0.0001 ) );
	ASSERTN( kVStanev, arc32.IsPtOnArc( c, 0.0001 ) );

	ASSERTN( kVStanev, ! arc21.IsPtOnArc( d, 0.0001 ) );	// big arc
	ASSERTN( kVStanev, ! arc22.IsPtOnArc( d, 0.0001 ) );
	ASSERTN( kVStanev, ! arc32.IsPtOnArc( d, 0.0001 ) );
}


