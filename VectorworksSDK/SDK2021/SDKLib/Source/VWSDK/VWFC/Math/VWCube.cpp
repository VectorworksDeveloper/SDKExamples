//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;

VWCube::VWCube()
{
	bEmpty		= true;
}

VWCube::VWCube(const VWPoint3D& minPoint, const VWPoint3D& maxPoint)
{
	this->SetCube( minPoint, maxPoint );
}

VWCube::VWCube(const VWPoint3D& minPt, double cx, double cy, double cz)
{
	this->SetCube( minPt, cx, cy, cz );
}

VWCube::VWCube(const VWCube& src)
{
	bEmpty			= src.bEmpty;
	m_maxPoint		= src.m_maxPoint;
	m_minPoint	= src.m_minPoint;
}

VWCube::~VWCube()
{
}

VWCube& VWCube::operator=(const VWCube& src)
{
	bEmpty			= src.bEmpty;
	m_maxPoint		= src.m_maxPoint;
	m_minPoint		= src.m_minPoint;
	return *this;
}

bool VWCube::operator==(const VWCube& that) const
{
	// result.
	return	( bEmpty		== that.bEmpty		&&
			  m_maxPoint	== that.m_maxPoint	&&
			  m_minPoint	== that.m_minPoint	);
}

void VWCube::Clear()
{
	bEmpty		= true;
	m_minPoint.SetPoint( 0, 0, 0 );
	m_maxPoint.SetPoint( 0, 0, 0 );
}

void VWCube::SetCube(const VWPoint3D& minPoint, const VWPoint3D& maxPoint)
{
	bEmpty				= false;
	m_minPoint.x		= maxPoint.x < minPoint.x ? maxPoint.x : minPoint.x;
	m_minPoint.y		= maxPoint.y < minPoint.y ? maxPoint.y : minPoint.y;
	m_minPoint.z		= maxPoint.z < minPoint.z ? maxPoint.z : minPoint.z;
	m_maxPoint.x		= maxPoint.x > minPoint.x ? maxPoint.x : minPoint.x;
	m_maxPoint.y		= maxPoint.y > minPoint.y ? maxPoint.y : minPoint.y;
	m_maxPoint.z		= maxPoint.z > minPoint.z ? maxPoint.z : minPoint.z;
}

void VWCube::SetCube(const VWPoint3D& minPt, double cx, double cy, double cz)
{
	bEmpty				= false;
	m_minPoint			= minPt;
	m_maxPoint.x		= m_minPoint.x + cx;
	m_maxPoint.y		= m_minPoint.y + cy;
	m_maxPoint.z		= m_minPoint.z + cz;
}

bool VWCube::IsEmpty() const
{
	return bEmpty;
}

double VWCube::GetWidth() const
{
	double	width	= m_maxPoint.x - m_minPoint.x;
	return width > 0 ? width : - width;
}

double VWCube::GetDepth() const
{
	double	depth	= m_maxPoint.y - m_minPoint.y;
	return depth > 0 ? depth : - depth;
}

double VWCube::GetHeight() const
{
	double	height	= m_maxPoint.z - m_minPoint.z;
	return height > 0 ? height : - height;
}

const VWPoint3D& VWCube::GetMinPoint() const
{
	return m_minPoint;
}

const VWPoint3D& VWCube::GetMaxPoint() const
{
	return m_maxPoint;
}

void VWCube::Unite(const VWPolygon2D& poly, double z/*=0.0*/)
{
	size_t	len		= poly.GetVertexCount();
	for(size_t i=0; i<len; i++) {
		const VWPoint2D&	pt	= poly.GetVertexAt( i );
		this->Unite( pt.x, pt.y, z );
	}
}

void VWCube::Unite(const TSTLPoints2DArray& points, double z/*=0.0*/)
{
	size_t		cnt			= points.size();

	for ( size_t i = 0 ; i < cnt ; ++ i )
	{
		const VWPoint2D&	pt		= points[ i ];
		this->Unite( pt.x, pt.y, z );
	}
}

void VWCube::Unite(const VWPolygon3D& poly)
{
	size_t	len		= poly.GetVertexCount();
	for(size_t i=0; i<len; i++) {
		const VWPoint3D&	pt	= poly.GetVertexAt( i );
		this->Unite( pt.x, pt.y, pt.z );
	}
}

void VWCube::Unite(const TSTLPoints3DArray& points)
{
	size_t		cnt			= points.size();

	for ( size_t i = 0 ; i < cnt ; ++ i )
	{
		const VWPoint3D&	pt		= points[ i ];
		this->Unite( pt.x, pt.y, pt.z );
	}
}

void VWCube::Unite(double x, double y, double z)
{
	if ( bEmpty ) {
		m_minPoint.x		= x;
		m_minPoint.y		= y;
		m_minPoint.z		= z;
		m_maxPoint.x		= x;
		m_maxPoint.y		= y;
		m_maxPoint.z		= z;
		bEmpty				= false;
	}
	else {
		if ( x < m_minPoint.x )		m_minPoint.x		= x;
		if ( y < m_minPoint.y )		m_minPoint.y		= y;
		if ( z < m_minPoint.z )		m_minPoint.z		= z;
		if ( x > m_maxPoint.x )		m_maxPoint.x		= x;
		if ( y > m_maxPoint.y )		m_maxPoint.y		= y;
		if ( z > m_maxPoint.z )		m_maxPoint.z		= z;
	}
}

void VWCube::Unite(const VWPoint3D& pt)
{
	this->Unite( pt.x, pt.y, pt.z );
}

void VWCube::Unite(const VWCube& cube)
{
	this->Unite( cube.m_minPoint.x, cube.m_minPoint.y, cube.m_minPoint.z );
	this->Unite( cube.m_maxPoint.x, cube.m_maxPoint.y, cube.m_maxPoint.z );
}

bool VWCube::IsPtInside(double x, double y, double z) const
{
	return
		m_minPoint.x < x && x < m_maxPoint.x &&
		m_minPoint.y < y && y < m_maxPoint.y &&
		m_minPoint.z < z && z < m_maxPoint.z;
}

bool VWCube::IsPtInside(const VWPoint3D& pt) const
{
	return this->IsPtInside( pt.x, pt.y, pt.z );
}

// checks if point is inside the cube (using epsilon).
bool VWCube::IsPtInside(double x, double y, double z, double epsilon) const
{
	return	( ( x > m_minPoint.x - epsilon ) &&
			  ( x < m_maxPoint.x + epsilon ) &&
			  ( y > m_minPoint.y - epsilon ) &&
			  ( y < m_maxPoint.y + epsilon ) &&
			  ( z > m_minPoint.z - epsilon ) &&
			  ( z < m_maxPoint.z + epsilon ) );
}

bool VWCube::IsPtInside(const VWPoint3D& pt, double epsilon) const
{
	return this->IsPtInside( pt.x, pt.y, pt.z, epsilon );
}

// checks if cubes do not have common volume.
bool VWCube::IsOutside(const VWCube& that) const
{
	return	( ( that.m_maxPoint.x	< m_minPoint.x		) ||
			  ( m_maxPoint.x		< that.m_minPoint.x	) ||
			  ( that.m_maxPoint.y	< m_minPoint.y		) ||
			  ( m_maxPoint.y		< that.m_minPoint.y	) ||
			  ( that.m_maxPoint.z	< m_minPoint.z		) ||
			  ( m_maxPoint.z		< that.m_minPoint.z	) );
}

// checks if cubes do not have common volume (using epsilon).
bool VWCube::IsOutside(const VWCube& that, double epsilon) const
{
	return	( ( that.m_maxPoint.x	< m_minPoint.x		- epsilon ) ||
			  ( m_maxPoint.x		< that.m_minPoint.x	- epsilon ) ||
			  ( that.m_maxPoint.y	< m_minPoint.y		- epsilon ) ||
			  ( m_maxPoint.y		< that.m_minPoint.y	- epsilon ) ||
			  ( that.m_maxPoint.z	< m_minPoint.z		- epsilon ) ||
			  ( m_maxPoint.z		< that.m_minPoint.z	- epsilon ) );
}

// checks if 'that' cube is inside this cube.
bool VWCube::IsInside(const VWCube& that) const
{
	return	( ( that.m_maxPoint.x <= m_maxPoint.x ) &&
			  ( that.m_minPoint.x >= m_minPoint.x ) &&
			  ( that.m_maxPoint.y <= m_maxPoint.y ) &&
			  ( that.m_minPoint.y >= m_minPoint.y ) &&
			  ( that.m_maxPoint.z <= m_maxPoint.z ) &&
			  ( that.m_minPoint.z >= m_minPoint.z ) );
}

// checks if 'that' cube is inside this cube (using epsilon).
bool VWCube::IsInside(const VWCube& that, double epsilon) const
{
	return	( ( that.m_maxPoint.x <= m_maxPoint.x + epsilon ) &&
			  ( that.m_minPoint.x >= m_minPoint.x - epsilon ) &&
			  ( that.m_maxPoint.y <= m_maxPoint.y + epsilon ) &&
			  ( that.m_minPoint.y >= m_minPoint.y - epsilon ) &&
			  ( that.m_maxPoint.z <= m_maxPoint.z + epsilon ) &&
			  ( that.m_minPoint.z >= m_minPoint.z - epsilon ) );
}