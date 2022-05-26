//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "Interfaces/VectorWorks/IParasolidKernel.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWBodyObj::VWBodyObj()
{
	fhObject		= nil;
	fp				= NULL;
	fpAPI			= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );
}

VWBodyObj::VWBodyObj(const VWBodyObj& src)
{
	fhObject		= nil;
	fp				= NULL;
	fpAPI			= NULL;

	fhObject		= src.fhObject;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );
}

VWBodyObj::VWBodyObj(MCObjectHandle hObj)
{
	fhObject		= nil;
	fp				= NULL;
	fpAPI			= NULL;

	VWFC_ASSERT( VWBodyObj::IsBodyObject( hObj ) );
	if ( ! VWBodyObj::IsBodyObject( hObj ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hObj;
	VWFC_ASSERT( fhObject != nil );

	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );

	if (fpAPI) {
		if (!((IParasolidVWAPI *)fpAPI)->IsValidHandleForBody(fhObject))
			THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );

		if (!((IParasolidVWAPI *)fpAPI)->GetParasolidBodies(fhObject, false, false, false, true, false, fBodies)) {
			fBodies.Clear();
		}
	}
}

VWBodyObj::~VWBodyObj()
{
	fhObject		= nil;
	if ( fpAPI ) {
		fpAPI->Release();
		fpAPI	= NULL;
	}

	if (fp) {
		Sint32 size = (Sint32) fBodies.GetSize();
		PK_ENTITY_delete(size, &fBodies.GetAt( 0 ));
		fp->Release();
		fp	= NULL;
	}
}

VWBodyObj& VWBodyObj::operator=(const VWBodyObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

size_t VWBodyObj::GetBodyCount()
{
	return fBodies.GetSize();
}

bool VWBodyObj::GetBody(size_t index, VWBody& outBody)
{
	if (fBodies.GetSize() > 0 && index < fBodies.GetSize()) {
		outBody = VWBody(fBodies.GetAt(index));
		return true;
	}

	return false;
}

/*static*/ bool VWBodyObj::IsBodyObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );

	if (type == kPieceWiseNurbsCurveNode		||
		type == kSolidNode			|| 
		type == kCSGTreeNode		|| 
		type == kExtrudeNode		||
		type == kSweepNode			||
		type == kMultiExtrudeNode	||
		type == qPolyNode			||
		type == kMeshNode			||
		type == kParametricNode		||
		type == kSymbolNode			||
		type == kSlabNode			||
		type == kNurbsSurfaceNode	||
		type == kWallNode			||
		type == kRoofContainerNode	||
		type == kGroupNode)
		return true;

	return false;
}

void VWBodyObj::AddToolHighlighting(const VWBodyFace& face)
{
	DSTOP((kVStanev, "Not implemented"));
}

void VWBodyObj::AddToolHighlighting(const VWBodyEdge& edge)
{
	DSTOP((kVStanev, "Not implemented"));
}


bool VWBodyObj::IsFaceBelongsToThisObject(const VWBodyFace& face)
{
	bool retVal = false;
	VWBody body = face.GetBody();
	for (size_t i = 0; i < fBodies.GetSize(); i++)
	{
		if (fBodies.Find(body.GetBodyID()) != -1)
			retVal = true;
	}

	return retVal;
}

InternalIndex VWBodyObj::GetFaceTexture(const VWBodyFace& face)
{
	InternalIndex textureRef = 0;
	if (fp && fpAPI)
	{
		if (IsFaceBelongsToThisObject(face))
		{
			textureRef = ((IParasolidVWAPI *)fpAPI)->GetFaceTextureRef(fhObject, face.GetBodyFaceID());
		}
	}

	return textureRef;
}

void VWBodyObj::SetFaceTexture(InternalIndex textureRef, const VWBodyFace& face)
{
	if (fp && fpAPI)
	{
		if (IsFaceBelongsToThisObject(face))
		{
			((IParasolidVWAPI *)fpAPI)->SetFaceTextureRef(fhObject, textureRef, face.GetBodyFaceID());
		}
	}
}

void VWBodyObj::SetFaceTexture(MCObjectHandle hTexture, const VWBodyFace& face)
{
	InternalIndex textureRef = gSDK->GetObjectInternalIndex(hTexture);
	SetFaceTexture(textureRef, face);
}

void VWBodyObj::GetFaceTextureMappingInfo(const VWBodyFace& face, TextureMappingInfoSDK& outMappingInfo)
{
	if (fp && fpAPI)
	{
		if (IsFaceBelongsToThisObject(face))
		{
			((IParasolidVWAPI *)fpAPI)->GetFaceTextureMappingInfo(fhObject, face.GetBodyFaceID(), 0, outMappingInfo);
		}
	}
}

void VWBodyObj::GetFaceTextureMappingInfo(const VWBodyFace& face, Sint32 decalLayerNum, TextureMappingInfoSDK& outMappingInfo)
{
	if (fp && fpAPI)
	{
		if (IsFaceBelongsToThisObject(face))
		{
			((IParasolidVWAPI *)fpAPI)->GetFaceTextureMappingInfo(fhObject, face.GetBodyFaceID(), decalLayerNum, outMappingInfo);
		}
	}
}

void VWBodyObj::SetFaceTextureMappingInfo(const VWBodyFace& face, const TextureMappingInfoSDK& mappingInfo)
{
	if (fp && fpAPI)
	{
		if (IsFaceBelongsToThisObject(face))
		{
			((IParasolidVWAPI *)fpAPI)->SetFaceTextureMappingInfo(fhObject, face.GetBodyFaceID(), 0, mappingInfo);
		}
	}
}

void VWBodyObj::SetFaceTextureMappingInfo(const VWBodyFace& face, Sint32 decalLayerNum, const TextureMappingInfoSDK& mappingInfo)
{
	if (fp && fpAPI)
	{
		if (IsFaceBelongsToThisObject(face))
		{
			((IParasolidVWAPI *)fpAPI)->SetFaceTextureMappingInfo(fhObject, face.GetBodyFaceID(), decalLayerNum, mappingInfo);
		}
	}
}

Sint32 VWBodyObj::GetFaceTextureMappingDecalLayerCount(const VWBodyFace& face)	// number of decal layers on a texture part
{
	Sint32 numTexLayers = 0;
	if (fp && fpAPI)
	{
		if (IsFaceBelongsToThisObject(face))
		{
			numTexLayers = ((IParasolidVWAPI *)fpAPI)->GetNumFaceTextureLayers(fhObject, face.GetBodyFaceID());
		}
	}

	return numTexLayers;
}

