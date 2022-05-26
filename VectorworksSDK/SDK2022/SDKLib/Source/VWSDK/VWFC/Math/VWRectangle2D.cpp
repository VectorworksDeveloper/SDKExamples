//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;

VWRectangle2D::VWRectangle2D()
{
	m_bIsEmpty	= true;
}

VWRectangle2D::VWRectangle2D(const VWPoint2D& topleft, const VWPoint2D& botRight)
{
	this->SetRect( topleft, botRight );
}

VWRectangle2D::VWRectangle2D(const VWPoint2D& topleft, double cx, double cy)
{
	this->SetRect( topleft, cx, cy );
}

VWRectangle2D::VWRectangle2D(double left, double right, double top, double bottom)
{
	this->SetRect( left, right, top, bottom );
}

VWRectangle2D::VWRectangle2D(const VWRectangle2D& src)
{
	m_topLeft		= src.m_topLeft;
	m_bottomRight	= src.m_bottomRight;
	m_bIsEmpty		= false;
}

VWRectangle2D::~VWRectangle2D()
{
}

VWRectangle2D& VWRectangle2D::operator=(const VWRectangle2D& src)
{
	m_topLeft		= src.m_topLeft;
	m_bottomRight	= src.m_bottomRight;
	m_bIsEmpty		= src.m_bIsEmpty;
	return *this;
}

void VWRectangle2D::SetRect(const VWPoint2D& topleft, const VWPoint2D& botRight)
{
	m_topLeft		= topleft;
	m_bottomRight	= botRight;
	m_bIsEmpty		= false;
}

void VWRectangle2D::SetRect(const VWPoint2D& topleft, double cx, double cy)
{
	m_topLeft		= topleft;
	m_bottomRight.SetPoint( topleft.x + cx, topleft.y + cy );
	m_bIsEmpty		= false;
}

void VWRectangle2D::SetRect(double left, double right, double top, double bottom)
{
	m_topLeft.x			= left < right ? left : right;
	m_topLeft.y			= top > bottom ? top : bottom;

	m_bottomRight.x		= right > left ? right : left;
	m_bottomRight.y		= bottom < top ? bottom : top;
	m_bIsEmpty		= false;
}

VWPoint2D VWRectangle2D::GetCenterLeft() const
{
	return { m_topLeft.x, ( m_topLeft.y + m_bottomRight.y ) / 2 };
}

VWPoint2D VWRectangle2D::GetCenterRight() const
{
	return { m_bottomRight.x, ( m_topLeft.y + m_bottomRight.y ) / 2 };
}

VWPoint2D VWRectangle2D::GetTopCenter() const
{
	return { ( m_topLeft.x + m_bottomRight.x ) / 2, m_topLeft.y };
}

VWPoint2D VWRectangle2D::GetBottomCenter() const
{
	return { ( m_topLeft.x + m_bottomRight.x ) / 2, m_bottomRight.y };
}

VWPoint2D VWRectangle2D::GetTopLeft() const
{
	return m_topLeft;
}

VWPoint2D VWRectangle2D::GetTopRight() const
{
	return { m_bottomRight.x, m_topLeft.y };
}

VWPoint2D VWRectangle2D::GetBottomLeft() const
{
	return { m_topLeft.x, m_bottomRight.y };
}

VWPoint2D VWRectangle2D::GetBottomRight() const
{
	return m_bottomRight;
}

VWPoint2D VWRectangle2D::GetCenter() const
{
	return (m_topLeft + m_bottomRight) / 2;
}

double VWRectangle2D::GetLeft() const
{
	return m_topLeft.x;
}

double VWRectangle2D::GetRight() const
{
	return m_bottomRight.x;
}

double VWRectangle2D::GetTop() const
{
	return m_topLeft.y;
}

double VWRectangle2D::GetBottom() const
{
	return m_bottomRight.y;
}

double VWRectangle2D::GetWidth() const
{
	VWFC_ASSERT( m_bottomRight.x >= m_topLeft.x );
	return m_bottomRight.x - m_topLeft.x;
}

double VWRectangle2D::GetHeight() const
{
	VWFC_ASSERT( m_topLeft.y >= m_bottomRight.y );
	return m_topLeft.y - m_bottomRight.y;
}

double VWRectangle2D::GetDiagonal() const
{
	VWFC_ASSERT( m_bottomRight.x >= m_topLeft.x );
	VWFC_ASSERT( m_topLeft.y >= m_bottomRight.y );
	return m_topLeft.DistanceTo( m_bottomRight );
}

double VWRectangle2D::GetDiagonalSquared() const
{
	VWFC_ASSERT( m_bottomRight.x >= m_topLeft.x );
	VWFC_ASSERT( m_topLeft.y >= m_bottomRight.y );
	return m_topLeft.DistanceSquaredTo( m_bottomRight );
}

bool VWRectangle2D::IsPtInside(double x, double y) const
{
	return
		m_topLeft.x <= x && x <= m_bottomRight.x &&
		m_bottomRight.y <= y && y <= m_topLeft.y;
}

bool VWRectangle2D::IsPtInside(const VWPoint2D& pt) const
{
	return this->IsPtInside( pt.x, pt.y );
}

bool VWRectangle2D::Intersect(const VWRectangle2D& rc) const
{
	bool	bIntersOnX1	=	(m_topLeft.x < rc.m_topLeft.x && rc.m_topLeft.x < m_bottomRight.x) ||
							(m_topLeft.x < rc.m_bottomRight.x && rc.m_bottomRight.x < m_bottomRight.x);
	bool	bIntersOnY1	=	(m_bottomRight.y < rc.m_topLeft.y && rc.m_topLeft.y < m_topLeft.y) ||
							(m_bottomRight.y < rc.m_bottomRight.y && rc.m_bottomRight.y < m_topLeft.y);

	bool	bIntersOnX2	=	(rc.m_topLeft.x < m_topLeft.x && m_topLeft.x < rc.m_bottomRight.x) ||
							(rc.m_topLeft.x < m_bottomRight.x && m_bottomRight.x < rc.m_bottomRight.x);
	bool	bIntersOnY2	=	(rc.m_bottomRight.y < m_topLeft.y && m_topLeft.y < rc.m_topLeft.y) ||
							(rc.m_bottomRight.y < m_bottomRight.y && m_bottomRight.y < rc.m_topLeft.y);

	return	(bIntersOnX1 && bIntersOnY1) ||
			(bIntersOnX2 && bIntersOnY2) ||
			(bIntersOnX1 && bIntersOnY2) ||
			(bIntersOnX2 && bIntersOnY1);
}

// checks if point is inside the rectangle (using epsilon).
bool VWRectangle2D::IsPtInside(double x, double y, double epsilon) const
{
	return	( ( x >= m_topLeft.x	 - epsilon) &&
			  ( x <= m_bottomRight.x + epsilon ) &&
			  ( y >= m_bottomRight.y - epsilon ) &&
			  ( y <= m_topLeft.y	 + epsilon ) );
}

bool VWRectangle2D::IsPtInside(const VWPoint2D& pt, double epsilon) const
{
	return this->IsPtInside( pt.x, pt.y, epsilon );
}

bool VWRectangle2D::IsInside(const VWRectangle2D& rc) const
{
	return	( ( rc.m_topLeft.y		<=	m_topLeft.y		) &&
			  ( rc.m_bottomRight.y	>=	m_bottomRight.y	) &&
			  ( rc.m_topLeft.x		>=	m_topLeft.x		) &&
			  ( rc.m_bottomRight.x	<=	m_bottomRight.x	) );
}

// checks if 'rc' rectangle is inside this rectangle (using epsilon).
bool VWRectangle2D::IsInside(const VWRectangle2D& rc, double epsilon) const
{
	return	( ( rc.m_topLeft.y		<=	m_topLeft.y		+ epsilon ) &&
			  ( rc.m_bottomRight.y	>=	m_bottomRight.y	- epsilon ) &&
			  ( rc.m_topLeft.x		>=	m_topLeft.x		- epsilon ) &&
			  ( rc.m_bottomRight.x	<=	m_bottomRight.x	+ epsilon ) );
}

// check if rectangles do not have common areas.
bool VWRectangle2D::IsOutside(const VWRectangle2D& rc) const
{
	return	( ( rc.m_bottomRight.x	<	m_topLeft.x		) ||
			  ( m_bottomRight.x		<	rc.m_topLeft.x	) ||
			  ( rc.m_bottomRight.y	>	m_topLeft.y		) ||
			  ( m_bottomRight.y		>	rc.m_topLeft.y	) );
}

// check if rectangles do not have common areas (using epsilon).
bool VWRectangle2D::IsOutside(const VWRectangle2D& rc, double epsilon) const
{
	return	( ( rc.m_bottomRight.x	<	m_topLeft.x		- epsilon ) ||
			  ( m_bottomRight.x		<	rc.m_topLeft.x	- epsilon ) ||
			  ( rc.m_bottomRight.y	>	m_topLeft.y		+ epsilon ) ||
			  ( m_bottomRight.y		>	rc.m_topLeft.y	+ epsilon ) );
}

void VWRectangle2D::Unite(double x, double y)
{
	if ( m_bIsEmpty ) {
		m_topLeft.x			= x;
		m_topLeft.y			= y;
		m_bottomRight.x		= x;
		m_bottomRight.y		= y;
		m_bIsEmpty			= false;
	}
	else {
		if ( x < m_topLeft.x )		m_topLeft.x			= x;
		if ( y > m_topLeft.y )		m_topLeft.y			= y;
		if ( x > m_bottomRight.x )	m_bottomRight.x		= x;
		if ( y < m_bottomRight.y )	m_bottomRight.y		= y;
	}
}

void VWRectangle2D::Unite(const VWPoint2D& pt)
{
	this->Unite( pt.x, pt.y );
}

void VWRectangle2D::Unite(const VWPolygon2D& poly)
{
	size_t	len		= poly.GetVertexCount();
	for(size_t i=0; i<len; i++) {
		const VWPoint2D&	pt	= poly.GetVertexAt( i );
		this->Unite( pt.x, pt.y );
	}
}

void VWRectangle2D::Unite(const VWRectangle2D& rect)
{
	this->Unite( rect.m_topLeft.x, rect.m_topLeft.y );
	this->Unite( rect.m_bottomRight.x, rect.m_bottomRight.y );
}

VWPolygon2D	VWRectangle2D::AsPolygon() const
{
	VWPolygon2D	poly( TSTLPoints2DArray( {	m_topLeft,
											{ m_bottomRight.x, m_topLeft.y },
											m_bottomRight,
											{ m_topLeft.x, m_bottomRight.y } } ) );
	poly.SetClosed( true );
	return poly;
}