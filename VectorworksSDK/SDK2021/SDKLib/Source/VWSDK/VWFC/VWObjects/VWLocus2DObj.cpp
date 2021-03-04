//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWLocus2DObj::VWLocus2DObj(const VWPoint2D& pt)
{
	fhObject		= ::GS_CreateLocus( gCBP, pt );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create locus2D" );
}

VWLocus2DObj::VWLocus2DObj(MCObjectHandle hLocus2D)
{
	VWFC_ASSERT( VWLocus2DObj::IsLocus2DObject( hLocus2D ) );
	if ( ! VWLocus2DObj::IsLocus2DObject( hLocus2D ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hLocus2D;
	VWFC_ASSERT( fhObject != nil );
}

VWLocus2DObj::VWLocus2DObj(const VWLocus2DObj& src)
{
	fhObject		= src.fhObject;
}

VWLocus2DObj::~VWLocus2DObj()
{
	fhObject		= nil;
}

VWLocus2DObj& VWLocus2DObj::operator=(const VWLocus2DObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

bool VWLocus2DObj::IsLocus2DObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kLocusNode;
}

void VWLocus2DObj::SetPoint(const VWPoint2D& pt)
{
	VWFC_ASSERT( fhObject );
	::GS_SetLocusPosition( gCBP, fhObject, pt );
}

VWPoint2D VWLocus2DObj::GetPoint() const
{
	WorldPt		locPos;
	VWFC_ASSERT( fhObject );
	::GS_GetLocusPosition( gCBP, fhObject, locPos );
	return locPos;
}