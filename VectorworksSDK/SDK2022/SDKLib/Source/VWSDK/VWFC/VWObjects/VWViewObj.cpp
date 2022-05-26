//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VectorWorks;
using namespace VWFC::VWObjects;

const short kKludgeViewMatrix = 7008;

VWViewObj::VWViewObj()
{
	fhViewObj = gSDK->ViewCreateCurrent();
}

VWViewObj::VWViewObj(const VWViewObj& src)
{
	fhViewObj = gSDK->ViewDuplicate( src.fhViewObj );
}

VWViewObj::VWViewObj(MCObjectHandle hView)
{
	VWFC_ASSERT(VWViewObj::IsViewObject(hView));

	if (!VWViewObj::IsViewObject(hView))
		THROW_VWFC_EXCEPTION(VWBadObjectTypeException, 0, "bad handle type when creating");

	fhViewObj = gSDK->DuplicateObject( hView );
	fhObject = fhViewObj;
	VWFC_ASSERT(fhObject != nil);
}

VWViewObj::~VWViewObj()
{
	gSDK->ViewDelete( fhViewObj );
	fhViewObj = NULL;
	fhObject= NULL;
}

VWViewObj& VWViewObj::operator=(const VWViewObj& src)
{
	fhViewObj = gSDK->ViewDuplicate( src.fhViewObj );
	return *this;
}

size_t VWViewObj::GetNumLayers()
{
	return gSDK->ViewGetNumLayers( fhViewObj );
}

void VWViewObj::GetLayerVisibility(size_t index, InternalIndex& outName, ELayerVisibility& outVisibility)
{
	short vis = 0;
	gSDK->ViewGetLayerVisibility( fhViewObj, index, outName, vis );
	outVisibility = (ELayerVisibility) vis;
}

size_t VWViewObj::GetNumClasses()
{
	return gSDK->ViewGetNumClasses( fhViewObj );
}

void VWViewObj::GetClassVisibility(size_t index, InternalIndex& outClassID, EClassVisibility& outVisibility)
{
	short vis = 0;
	gSDK->ViewGetClassVisibility( fhViewObj, index, outClassID, vis );
	outVisibility = (EClassVisibility) vis;
}

TransformMatrix VWViewObj::GetMatrix()
{
	TransformMatrix viewMatrix;
	gSDK->Kludge(kKludgeViewMatrix, fhViewObj, &viewMatrix);
	return viewMatrix;
}

void VWViewObj::StoreView()
{
	gSDK->ViewStore( fhViewObj );
}

void VWViewObj::RestoreView()
{
	gSDK->ViewRestore( fhViewObj );
}

bool VWViewObj::IsViewObject(MCObjectHandle hObj)
{
	short	type = gSDK->GetObjectTypeN(hObj);
	return	(type == saveViewNode);
}
