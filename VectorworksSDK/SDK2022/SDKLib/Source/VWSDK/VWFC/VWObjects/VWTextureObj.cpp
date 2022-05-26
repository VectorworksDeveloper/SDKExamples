//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWTextureObj::VWTextureObj(const TXString& name)
{
	fhObject		= gSDK->CreateTexture();
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create texture" );

	gSDK->SetObjectName( fhObject, name );
}

VWTextureObj::VWTextureObj(MCObjectHandle hTexture)
{
	VWFC_ASSERT( VWTextureObj::IsTextureObject( hTexture ) );
	if ( ! VWTextureObj::IsTextureObject( hTexture ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hTexture;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureObj::VWTextureObj(const VWTextureObj& src)
{
	fhObject		= src.fhObject;
}

VWTextureObj::~VWTextureObj()
{
	fhObject		= nil;
}

VWTextureObj& VWTextureObj::operator=(const VWTextureObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureObj::IsTextureObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kTextureNode;
}

/*static*/ bool VWTextureObj::IsTextureObject(InternalIndex index)
{
	MCObjectHandle	hObj	= gSDK->InternalIndexToHandle( index );
	short			type	= hObj ? gSDK->GetObjectTypeN( hObj ) : 0;
	return type == kTextureNode;
}

InternalIndex VWTextureObj::GetTextureRef() const
{
	InternalIndex textureRef = gSDK->GetObjectInternalIndex( fhObject );
	return textureRef;
}

TXString VWTextureObj::GetName() const
{
	TXString	result;
	gSDK->GetObjectName( fhObject, result );
	return result;
}

void VWTextureObj::SetName(const TXString& name)
{
	gSDK->SetObjectName( fhObject, name );
}

WorldCoord VWTextureObj::GetSize() const
{
	TVariableBlock	varValue;
	gSDK->GetObjectVariable( fhObject, ovMaterialSize, varValue );

	Real64	data;
	return varValue.GetReal64( data ) ? data : 0;
}

void VWTextureObj::SetSize(WorldCoord value)
{
	TVariableBlock	varValue = (Real64)value;
	gSDK->SetObjectVariable( fhObject, ovMaterialSize, varValue );
}

void VWTextureObj::ApplyToObject(MCObjectHandle hObject, TexturePartSDK partID)
{
	InternalIndex textureRef = gSDK->GetObjectInternalIndex( fhObject );
	gSDK->SetTextureRef( hObject, textureRef, partID );
}

void VWTextureObj::UpdateThumbnailPreview()
{
	gSDK->UpdateThumbnailPreview( this->GetTextureRef() );

//	// Generate thumbnail for Resource Browser
//	TVariableBlock varBlock;
//	gSDK->SetObjectVariable( fhObject, ovResetTextureThumbnail, varBlock );
}

WorldCoord	VWTextureObj::GetUVAspectRatio() const
{
	WorldCoord				dAspectRatio = 1;
	if ( this->IsTextureObject( fhObject ) ) 
	{
		TVariableBlock	value;
		MCObjectHandle	hImage	= gSDK->FindAuxObject( fhObject, kImageDefNode );

		VERIFYN( kVStanev, gSDK->GetObjectVariable( hImage, ovTextureBitmapImageDefNode, value ) );
		if ( hImage ) 
		{
			Sint32	imageWidthPixels = 0, imageHeigthPixels = 0;

			VERIFYN( kVStanev, gSDK->GetObjectVariable( hImage, ovImageWidthPixels, value ) );
			VERIFYN( kVStanev, value.GetSint32( imageWidthPixels ) );

			VERIFYN( kVStanev, gSDK->GetObjectVariable( hImage, ovImageHeightPixels, value ) );
			VERIFYN( kVStanev, value.GetSint32( imageHeigthPixels ) );

			dAspectRatio = double( imageHeigthPixels) / double( imageWidthPixels );
		}
	}
	return dAspectRatio;
}
