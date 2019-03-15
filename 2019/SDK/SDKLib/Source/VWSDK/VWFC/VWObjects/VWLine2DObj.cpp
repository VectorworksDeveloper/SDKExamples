//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWLine2DObj::VWLine2DObj(double x1, double y1, double x2, double y2)
{
	WorldPt	a(x1,y1);
	WorldPt	b(x2,y2);

	if ( ! MathUtils::Equalish( a, b, VWPoint2D::sEpsilon ) )
	{
		fhObject		= ::GS_CreateLine( gCBP, a, b );
	}
	else
	{
		fhObject		= NULL;
	}
}

VWLine2DObj::VWLine2DObj(const VWPoint2D& startPt, const VWPoint2D& endPt)
{
	if ( ! MathUtils::Equalish( startPt, endPt, VWPoint2D::sEpsilon ) )
	{
		fhObject		= ::GS_CreateLine( gCBP, startPt, endPt );
	}
	else
	{
		fhObject		= NULL;
	}
}

VWLine2DObj::VWLine2DObj(const VWLine2D& line2DMath)
{
	if ( ! MathUtils::Equalish( line2DMath.GetStart(), line2DMath.GetEnd(), VWPoint2D::sEpsilon ) )
	{
		fhObject		= ::GS_CreateLine( gCBP, line2DMath.GetStart(), line2DMath.GetEnd() );
	}
	else
	{
		fhObject		= NULL;
	}
}

VWLine2DObj::VWLine2DObj(MCObjectHandle hLine2D)
{
	VWFC_ASSERT( VWLine2DObj::IsLine2DObject( hLine2D ) );
//	if ( ! VWLine2DObj::IsLine2DObject( hLine2D ) )
//		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hLine2D;
	VWFC_ASSERT( fhObject != nil );
}

VWLine2DObj::VWLine2DObj(const VWLine2DObj& src)
{
	fhObject	= src.fhObject;
}

VWLine2DObj::~VWLine2DObj()
{
	fhObject		= nil;
}

VWLine2DObj& VWLine2DObj::operator=(const VWLine2DObj& src)
{
	fhObject	= src.fhObject;
	return *this;
}

bool VWLine2DObj::IsLine2DObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kLineNode;
}

void VWLine2DObj::SetStartPoint(const VWPoint2D& pt)
{
	VWFC_ASSERT( fhObject );
	WorldPt			startPt;
	WorldPt			endPt;
	::GS_GetEndPoints( gCBP, fhObject, startPt, endPt );
	::GS_SetEndPoints( gCBP, fhObject, pt, endPt );
}

void VWLine2DObj::SetEndPoint(const VWPoint2D& pt)
{
	VWFC_ASSERT( fhObject );
	WorldPt			startPt;
	WorldPt			endPt;
	::GS_GetEndPoints( gCBP, fhObject, startPt, endPt );
	::GS_SetEndPoints( gCBP, fhObject, startPt, pt );
}

void VWLine2DObj::SetLine(const VWPoint2D& startPt, const VWPoint2D& endPt)
{
	VWFC_ASSERT( fhObject );
	::GS_SetEndPoints( gCBP, fhObject, startPt, endPt );
}

void VWLine2DObj::SetLine(const VWLine2D& line2DMath)
{
	this->SetLine( line2DMath.GetStart(), line2DMath.GetEnd() );
}

void VWLine2DObj::SetLine(const VWLine2DObj& line2D)
{
	VWFC_ASSERT( fhObject );
	WorldPt			startPt;
	WorldPt			endPt;
	::GS_GetEndPoints( gCBP, line2D.fhObject, startPt, endPt );
	::GS_SetEndPoints( gCBP, fhObject, startPt, endPt );
}

VWPoint2D VWLine2DObj::GetStartPoint() const
{
	WorldPt			startPt;
	WorldPt			endPt;
	VWFC_ASSERT( fhObject );
	::GS_GetEndPoints( gCBP, fhObject, startPt, endPt );
	return startPt;
}

VWPoint2D VWLine2DObj::GetEndPoint() const
{
	WorldPt			startPt;
	WorldPt			endPt;
	VWFC_ASSERT( fhObject );
	::GS_GetEndPoints( gCBP, fhObject, startPt, endPt );
	return endPt;
}

void VWLine2DObj::GetLine(VWPoint2D& outStartPt, VWPoint2D& outEndPt)
{
	VWFC_ASSERT( fhObject );
	WorldPt		a, b;
	::GS_GetEndPoints( gCBP, fhObject, a, b );
	outStartPt		= a;
	outEndPt		= b;
}

void VWLine2DObj::GetLine(VWLine2D& outLine2DMath)
{
	this->GetLine( outLine2DMath.GetStart(), outLine2DMath.GetEnd() );
}
