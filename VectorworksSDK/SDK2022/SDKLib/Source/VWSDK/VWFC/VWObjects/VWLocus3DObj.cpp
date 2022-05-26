//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWLocus3DObj::VWLocus3DObj(const VWPoint3D& pt)
{
	fhObject		= ::GS_CreateLocus3D( gCBP, pt );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create locus3D" );
}

VWLocus3DObj::VWLocus3DObj(MCObjectHandle hLocus3D)
{
	VWFC_ASSERT( VWLocus3DObj::IsLocus3DObject( hLocus3D ) );
	if ( ! VWLocus3DObj::IsLocus3DObject( hLocus3D ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hLocus3D;
	VWFC_ASSERT( fhObject != nil );
}

VWLocus3DObj::VWLocus3DObj(const VWLocus3DObj& src)
{
	fhObject		= src.fhObject;
}

VWLocus3DObj::~VWLocus3DObj()
{
	fhObject		= nil;
}

VWLocus3DObj& VWLocus3DObj::operator=(const VWLocus3DObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

bool VWLocus3DObj::IsLocus3DObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kLocus3DNode;
}

void VWLocus3DObj::SetPoint(const VWPoint3D& pt)
{
	VWFC_ASSERT( fhObject );
	::GS_SetLocus3DPosition( gCBP, fhObject, pt );
}

VWPoint3D VWLocus3DObj::GetPoint() const
{
	VWFC_ASSERT( fhObject );
	WorldPt3		locPos;
	::GS_GetLocus3DPosition( gCBP, fhObject, locPos );
	return locPos;
}

void VWLocus3DObj::GetObjectMatrix(VWTransformMatrix& outMatrix) const
{
	outMatrix.SetIdentity();
}

void VWLocus3DObj::SetObjectMatrix(const VWTransformMatrix& matrix)
{
	VWFC_ASSERT( fhObject );
	WorldPt3		locPos;
	VWPoint3D		thisPt;
	::GS_GetLocus3DPosition( gCBP, fhObject, locPos );
	thisPt.x			= locPos.x;
	thisPt.y			= locPos.y;
	thisPt.z			= locPos.z;
	thisPt				= matrix.PointTransform( thisPt );
	locPos.x			= thisPt.x;
	locPos.y			= thisPt.y;
	locPos.z			= thisPt.z;
	::GS_SetLocus3DPosition( gCBP, fhObject, locPos );
}
