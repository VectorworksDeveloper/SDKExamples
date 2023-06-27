//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;

VWCircle2D::VWCircle2D()
{
	m_dRadius		= 0;
}

VWCircle2D::VWCircle2D(const VWPoint2D& center, double radius)
{
	m_ptCenter		= center;
	m_dRadius		= radius;
}

VWCircle2D::VWCircle2D(const VWPoint2D& a, const VWPoint2D& b, const VWPoint2D& c)
{
	m_ptCenter.ThreePtCenter( a, b, c );
	m_dRadius		= m_ptCenter.DistanceTo( a );
}

VWCircle2D::VWCircle2D(const VWCircle2D& src)
{
	m_ptCenter		= src.m_ptCenter;
	m_dRadius		= src.m_dRadius;
}

VWCircle2D::~VWCircle2D()
{
}

VWCircle2D&	VWCircle2D::operator=(const VWCircle2D& src)
{
	m_ptCenter		= src.m_ptCenter;
	m_dRadius		= src.m_dRadius;
	return *this;
}

void VWCircle2D::SetCircle(const VWPoint2D& center, double radius)
{
	m_ptCenter		= center;
	m_dRadius		= radius;
}

void VWCircle2D::SetCircle(const VWPoint2D& center)
{
	m_ptCenter		= center;
}

void VWCircle2D::SetCircle(double radius)
{
	m_dRadius		= radius;
}

void VWCircle2D::SetCircle(const VWPoint2D& a, const VWPoint2D& b, const VWPoint2D& c)
{
	m_ptCenter.ThreePtCenter( a, b, c );
	m_dRadius		= m_ptCenter.DistanceTo( a );
}

VWPoint2D VWCircle2D::GetCenter() const
{
	return m_ptCenter;
}

double VWCircle2D::GetRadius() const
{
	return m_dRadius;
}

void VWCircle2D::GetCircle(VWPoint2D& outCenter, double& outRadius)
{
	outCenter		= m_ptCenter;
	outRadius		= m_dRadius;
}

// rotate this point at specified angle in degrees and center point
void VWCircle2D::RotateAtDeg(const VWPoint2D& centerPt, double_gs dDegAngle)
{
	m_ptCenter.RotateAtDeg( centerPt, dDegAngle );
}

// rotate this point at specified angle in radians and center point
void VWCircle2D::RotateAtRad(const VWPoint2D& centerPt, double_gs dRadAngle)
{
	m_ptCenter.RotateAtRad( centerPt, dRadAngle );
}

// move the center of the cirle with specified values
void VWCircle2D::Move(double cx, double cy)
{
	m_ptCenter		+= VWPoint2D( cx, cy );
}

// intersect this circle with a line
bool VWCircle2D::Intersect(const VWLine2D& line, double dEpsilon, WorldPt&/*out*/ outPt1, WorldPt&/*out*/ outPt2) const
{
	VWPoint2D	begPt				= line.GetStart();
	VWPoint2D	endPt				= line.GetEnd();

	bool		bIntersLineCircle	= false;

	if ( Abs( begPt.x - endPt.x ) < dEpsilon )	// Line is vertical
	{
		double_gs	q1	= m_dRadius*m_dRadius - (begPt.x - m_ptCenter.x)*(begPt.x - m_ptCenter.x);

		if ( q1 >= 0.0 )
		{
			if ( q1 < dEpsilon )
			{
				// being here means that it is a degenerate circle (zero-radius) ...
				// ... and its center lies on the line.
				q1	= 0;
			}

			bIntersLineCircle		= true;

			// calculate the square root once.
			double_gs	deltaY		= sqrt( q1 );

			outPt1.x	= begPt.x;
			outPt1.y	= m_ptCenter.y + deltaY;

			outPt2.x	= endPt.x;
			outPt2.y	= m_ptCenter.y - deltaY;
		}
	}
	else		// Line is not vertical
	{
		// copy the circle center.
		VWPoint2D	circCen			= m_ptCenter;

		// get the line slope.
		double_gs	riseOverRun		= ( endPt.y - begPt.y ) / ( endPt.x - begPt.x );

		double_gs	m				= riseOverRun;	// init.

		double_gs	onePlusEps		= ( 1.0 + dEpsilon );
		bool		doFlip			= ( riseOverRun < -onePlusEps || riseOverRun > onePlusEps );

		// note:
		// due to stability reasons, prefer the slope to be closer to horizontal.
		// the bigger is the slope (rise-over-run) the bigger is the chance to get an inaccurate result ...
		// ... using this method, especially if it is approaching a lot the vertical.

		if ( doFlip )				// calculate in a 'flipped' coordinate system.
		{
			// 'flip' the coordinate system, so the line's slope is closer to horizontal.

			m		= ( 1.0 / riseOverRun );

			// 'flip' the coordinate system.
			std::swap( begPt.x, begPt.y );
			std::swap( endPt.x, endPt.y );
			std::swap( circCen.x, circCen.y );
		}

		// y-intercept of the line.
		double_gs	e	= begPt.y - m * begPt.x;
		double_gs	a2	= 2*(1 + m*m);
		double_gs	e1	= (e - circCen.y);
		double_gs	b	= 2*m*e1 - 2*circCen.x;
		double_gs	c	= e1*e1 - m_dRadius*m_dRadius + circCen.x*circCen.x;

		double_gs	q1	= b*b - 2 * a2 * c;

		if ( q1 > -dEpsilon )
		{
			if ( q1 < dEpsilon )
			{
				q1	= 0;
			}

			bIntersLineCircle	= true;

			// calculate the square root once.
			double_gs	d		= sqrt( q1 );

			outPt1.x	= (-b + d) / a2;
			outPt1.y	= m*outPt1.x + e;

			outPt2.x	= (-b - d) / a2;
			outPt2.y	= m*outPt2.x + e;

			if ( doFlip )		// calculated in a 'flipped' coordinate system.
			{
				// 'flip' the result.
				std::swap( outPt1.x, outPt1.y );
				std::swap( outPt2.x, outPt2.y );
			}
		}
	}

	return bIntersLineCircle;
}

// intersect this circle with another circle
bool VWCircle2D::Intersect(const VWCircle2D& circle, double dEpsilon, WorldPt&/*out*/ outPt1, WorldPt&/*out*/ outPt2) const
{
	bool		bIntersCircleCircle;
	double_gs	d					= circle.m_ptCenter.DistanceTo( m_ptCenter );
	if ( d < dEpsilon ) 
		bIntersCircleCircle		= false;
	else //Circles are concentric -- too many intersections.
	if ( (d - dEpsilon) > (m_dRadius + circle.m_dRadius) )
		bIntersCircleCircle		= false;
	else // Circles do not intersect.
	if ( MathUtils::Equalish(d, m_dRadius + circle.m_dRadius, dEpsilon) ) { // Circles are tangent, and intersect at only one point.
		bIntersCircleCircle		= true;
		outPt1	= m_ptCenter + ((circle.m_ptCenter - m_ptCenter) * m_dRadius).Normalize();
		outPt2	= circle.m_ptCenter + ((m_ptCenter - circle.m_ptCenter) * circle.m_dRadius).Normalize();
		outPt1	= (outPt1 + outPt2) / 2;
		outPt2	= outPt1;
	}
	else { // Circles intersect at two points.
		bIntersCircleCircle		= true;

		double_gs a			= (m_dRadius*m_dRadius - circle.m_dRadius*circle.m_dRadius + d*d) / (d * 2);
		double_gs h			= sqrt(max(a*a, m_dRadius*m_dRadius) - min(a*a, m_dRadius*m_dRadius));
		VWPoint2D temp_pt	= m_ptCenter + ((circle.m_ptCenter - m_ptCenter).Normalize() * a);
		VWPoint2D temp_v	= (circle.m_ptCenter - m_ptCenter).Normalize().Perp() * h;
		outPt1				= temp_pt + temp_v;
		outPt2				= temp_pt - temp_v;
	}

	return bIntersCircleCircle;
}
