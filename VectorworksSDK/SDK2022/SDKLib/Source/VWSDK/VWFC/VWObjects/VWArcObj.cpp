//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWArcObj::VWArcObj(const VWPoint2D& center, double dRadius)
{
	double		dLeft		= center.x - dRadius;
	double		dRight		= center.x + dRadius;
	double		dTop		= center.y + dRadius;
	double		dBottom		= center.y - dRadius;
	WorldRect	bounds( Min(dLeft,dRight), Max(dTop,dBottom), Max(dLeft,dRight), Min(dTop,dBottom) );
	fhObject				= ::GS_CreateArcN( gCBP, bounds, 0, 360 );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create arc" );
}

VWArcObj::VWArcObj(const VWArc2D& arc)
{
	VWPoint2D	center		= arc.GetCenterPt();
	double		dRadius		= arc.GetRadius();
	double		dLeft		= center.x - dRadius;
	double		dRight		= center.x + dRadius;
	double		dTop		= center.y + dRadius;
	double		dBottom		= center.y - dRadius;
	WorldRect	bounds( Min(dLeft,dRight), Max(dTop,dBottom), Max(dLeft,dRight), Min(dTop,dBottom) );
	fhObject				= ::GS_CreateArcN( gCBP, bounds, arc.GetStartAngle(), arc.GetSweepAngle() );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create arc" );
}

VWArcObj::VWArcObj(MCObjectHandle hArc)
{
	VWFC_ASSERT( VWArcObj::IsArcObject( hArc ) );
	if ( ! VWArcObj::IsArcObject( hArc ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hArc;
	VWFC_ASSERT( fhObject != nil );
}

VWArcObj::VWArcObj(const VWArcObj& src)
{
	fhObject		= src.fhObject;
}

VWArcObj::~VWArcObj()
{
	fhObject	= nil;
}

VWArcObj& VWArcObj::operator=(const VWArcObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

// Return true if the specified object handle is 2D locus
bool VWArcObj::IsArcObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN(hObj );
	return type == kArcNode;
}

void VWArcObj::SetArc(const VWArc2D& arc)
{
	gSDK->SetArc( fhObject, arc.GetCenterPt(), arc.GetRadius(), arc.GetStartAngle(), arc.GetSweepAngle() );
}

void VWArcObj::SetAngles(double dStartAngleDeg, double dSweepAngleDeg)
{
	::GS_SetArcAnglesN( gCBP, fhObject, dStartAngleDeg, dSweepAngleDeg );
}

VWPoint2D VWArcObj::GetCenter() const
{
	double startAngle, sweepAngle, radiusX, radiusY;
	WorldPt	centerPt;
	::GS_GetArcInfoN( gCBP, fhObject, startAngle, sweepAngle, centerPt, radiusX, radiusY );
	return centerPt;
}

void VWArcObj::GetAngles(double& outStartAngleDeg, double& outSweepAngleDeg) const
{
	double radiusX, radiusY;
	WorldPt	centerPt;
	::GS_GetArcInfoN( gCBP, fhObject, outStartAngleDeg, outSweepAngleDeg, centerPt, radiusX, radiusY );
}

double VWArcObj::GetRadius() const
{
	double startAngle, sweepAngle, radiusX, radiusY;
	WorldPt	centerPt;
	::GS_GetArcInfoN( gCBP, fhObject, startAngle, sweepAngle, centerPt, radiusX, radiusY );
	return radiusX;
}

void VWArcObj::GetRadius(double& outRadiusX, double& outRadiusY) const
{
	double startAngle, sweepAngle;
	WorldPt	centerPt;
	::GS_GetArcInfoN( gCBP, fhObject, startAngle, sweepAngle, centerPt, outRadiusX, outRadiusY );
}

void VWArcObj::GetInfo(VWPoint2D& outCenter, double& outStartAngleDeg, double& outSweepAngleDeg, double& outRadiusX, double& outRadiusY) const
{
	WorldPt	centerPt;
	::GS_GetArcInfoN( gCBP, fhObject, outStartAngleDeg, outSweepAngleDeg, centerPt, outRadiusX, outRadiusY );
	outCenter	= centerPt;
}

