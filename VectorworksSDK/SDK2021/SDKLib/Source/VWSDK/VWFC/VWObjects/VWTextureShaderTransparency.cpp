//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;
using namespace VWFC::Tools;

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderTransparencyPlain::VWTextureShaderTransparencyPlain(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyPlain::VWTextureShaderTransparencyPlain(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyPlain::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyPlain::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyPlain::VWTextureShaderTransparencyPlain(const VWTextureShaderTransparencyPlain& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyPlain::~VWTextureShaderTransparencyPlain()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyPlain& VWTextureShaderTransparencyPlain::operator=(const VWTextureShaderTransparencyPlain& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyPlain::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyPlain& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, 10 /*kShaderPrototypeTransparency_Plain*/ );
	outValue = VWTextureShaderTransparencyPlain( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyPlain::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyPlain& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyPlain::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyPlain( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyPlain::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_Plain;
}

double VWTextureShaderTransparencyPlain::GetOpacity() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderTransparencyPlain::SetOpacity(double value)
{
	this->SetShaderRecordDouble( 4, value );
}


// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderTransparencyColor::VWTextureShaderTransparencyColor(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyColor::VWTextureShaderTransparencyColor(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyColor::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyColor::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyColor::VWTextureShaderTransparencyColor(const VWTextureShaderTransparencyColor& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyColor::~VWTextureShaderTransparencyColor()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyColor& VWTextureShaderTransparencyColor::operator=(const VWTextureShaderTransparencyColor& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyColor::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyColor& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, kShaderPrototypeTransparency_Color );
	outValue = VWTextureShaderTransparencyColor( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyColor::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyColor& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyColor::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyColor( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyColor::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_Color;
}

CRGBColor VWTextureShaderTransparencyColor::GetColor() const
{
	return this->GetShaderRecordColor( 4 );
}

void VWTextureShaderTransparencyColor::SetColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 4, value );
}

double VWTextureShaderTransparencyColor::GetBrightness() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderTransparencyColor::SetBrightness(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderTransparencyImage::VWTextureShaderTransparencyImage(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyImage::VWTextureShaderTransparencyImage(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyImage::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyImage::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyImage::VWTextureShaderTransparencyImage(const VWTextureShaderTransparencyImage& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyImage::~VWTextureShaderTransparencyImage()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyImage& VWTextureShaderTransparencyImage::operator=(const VWTextureShaderTransparencyImage& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyImage::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyImage& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, kShaderPrototypeTransparency_Image );
	outValue = VWTextureShaderTransparencyImage( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyImage::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyImage& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyImage::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyImage( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyImage::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_Image;
}

MCObjectHandle VWTextureShaderTransparencyImage::GetImage() const
{
	MCObjectHandle	hExistingTextureBitmap = gSDK->FindAuxObject( fhObject, kTextureBitmapNode );
	MCObjectHandle	hBitmap	= gSDK->FindAuxObject( hExistingTextureBitmap, kPaintNode );
	return hBitmap;
}

void VWTextureShaderTransparencyImage::SetImage(MCObjectHandle& hBitmapObj) const
{
	MCObjectHandle hExistingTextureBitmap = gSDK->FindAuxObject( fhObject, kTextureBitmapNode );
	if ( hExistingTextureBitmap )
	{
		gSDK->AddBeforeSwapObject(hExistingTextureBitmap);
		gSDK->DeleteObject( hExistingTextureBitmap );
	}

	hExistingTextureBitmap	= gSDK->CreateTextureBitmapFromPaintNode( hBitmapObj );
	
	// make sure the image is compressed
	// otherwise the thumbnails in the resource browser will be black
	MCObjectHandle image = gSDK->FindAuxObject( hExistingTextureBitmap, kImageDefNode );
	if ( image )
	{
		gSDK->CompressTextureImage( image );
	}

	gSDK->AttachAuxObject( hExistingTextureBitmap, fhObject );

	// the parameter cannot be used no more
	hBitmapObj	= NULL;
}

double VWTextureShaderTransparencyImage::GetRefraction() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderTransparencyImage::SetRefraction(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderTransparencyImage::GetTransparencyBlurriness() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderTransparencyImage::SetTransparencyBlurriness(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

CRGBColor VWTextureShaderTransparencyImage::GetAbsorptionColor() const
{
	return this->GetShaderRecordColor( 7 );
}

void VWTextureShaderTransparencyImage::SetAbsorptionColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 7, value );
}

double VWTextureShaderTransparencyImage::GetAbsorptionDistance() const
{
	return this->GetShaderRecordDouble( 10 );
}

void VWTextureShaderTransparencyImage::SetAbsorptionDistance(double value)
{
	this->SetShaderRecordDouble( 10, value);
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderTransparencyGlass::VWTextureShaderTransparencyGlass(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyGlass::VWTextureShaderTransparencyGlass(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyGlass::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyGlass::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyGlass::VWTextureShaderTransparencyGlass(const VWTextureShaderTransparencyGlass& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyGlass::~VWTextureShaderTransparencyGlass()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyGlass& VWTextureShaderTransparencyGlass::operator=(const VWTextureShaderTransparencyGlass& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyGlass::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyGlass& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, kShaderPrototypeTransparency_Glass );
	outValue = VWTextureShaderTransparencyGlass( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyGlass::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyGlass& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyGlass::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyGlass( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyGlass::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_Glass;
}

double VWTextureShaderTransparencyGlass::GetTransmission() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderTransparencyGlass::SetTransmission(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

double VWTextureShaderTransparencyGlass::GetRefraction() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderTransparencyGlass::SetRefraction(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

CRGBColor VWTextureShaderTransparencyGlass::GetColor() const
{
	return this->GetShaderRecordColor( 6 );
}

void VWTextureShaderTransparencyGlass::SetColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 6, value );
}

double VWTextureShaderTransparencyGlass::GetTransparencyBlurriness() const
{
	return this->GetShaderRecordDouble( 9 );
}

void VWTextureShaderTransparencyGlass::SetTransparencyBlurriness(double value)
{
	this->SetShaderRecordDouble( 9, value );
}

CRGBColor VWTextureShaderTransparencyGlass::GetAbsorptionColor() const
{
	return this->GetShaderRecordColor( 10 );
}

void VWTextureShaderTransparencyGlass::SetAbsorptionColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 10, value );
}

double VWTextureShaderTransparencyGlass::GetAbsorptionDistance() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderTransparencyGlass::SetAbsorptionDistance(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderTransparencyNoise::VWTextureShaderTransparencyNoise(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyNoise::VWTextureShaderTransparencyNoise(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyNoise::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyNoise::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyNoise::VWTextureShaderTransparencyNoise(const VWTextureShaderTransparencyNoise& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyNoise::~VWTextureShaderTransparencyNoise()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyNoise& VWTextureShaderTransparencyNoise::operator=(const VWTextureShaderTransparencyNoise& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyNoise::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyNoise& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, kShaderPrototypeTransparency_Noise );
	outValue = VWTextureShaderTransparencyNoise( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyNoise::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyNoise& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyNoise::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyNoise( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyNoise::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_Noise;
}

ShaderNoiseType VWTextureShaderTransparencyNoise::GetPattern() const
{
	return (ShaderNoiseType)this->GetShaderRecordLong( 4 );
}

void VWTextureShaderTransparencyNoise::SetPattern(ShaderNoiseType value)
{
	this->SetShaderRecordLong( 4, value );
}

CRGBColor VWTextureShaderTransparencyNoise::GetColor1() const
{
	return this->GetShaderRecordColor( 5 );
}

void VWTextureShaderTransparencyNoise::SetColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 5, value );
}

CRGBColor VWTextureShaderTransparencyNoise::GetColor2() const
{
	return this->GetShaderRecordColor( 8 );
}

void VWTextureShaderTransparencyNoise::SetColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 8, value );
}

bool VWTextureShaderTransparencyNoise::GetNoiseSolid() const
{
	return this->GetShaderRecordBool( 11 );
}

void VWTextureShaderTransparencyNoise::SetNoiseSolid(bool value)
{
	this->SetShaderRecordBool( 11, value );
}

double VWTextureShaderTransparencyNoise::GetGlobalScale() const
{
	return this->GetShaderRecordDouble( 12 );
}

void VWTextureShaderTransparencyNoise::SetGlobalScale(double value)
{
	this->SetShaderRecordDouble( 12, value );
}

double VWTextureShaderTransparencyNoise::GetRelativeUScale() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderTransparencyNoise::SetRelativeUScale(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

double VWTextureShaderTransparencyNoise::GetRelativeVScale() const
{
	return this->GetShaderRecordDouble( 14 );
}

void VWTextureShaderTransparencyNoise::SetRelativeVScale(double value)
{
	this->SetShaderRecordDouble( 14, value );
}

double VWTextureShaderTransparencyNoise::GetRelativeWScale() const
{
	return this->GetShaderRecordDouble( 15 );
}

void VWTextureShaderTransparencyNoise::SetRelativeWScale(double value)
{
	this->SetShaderRecordDouble( 15, value );
}

double VWTextureShaderTransparencyNoise::GetLowClip() const
{
	return this->GetShaderRecordDouble( 16 );
}

void VWTextureShaderTransparencyNoise::SetLowClip(double value)
{
	this->SetShaderRecordDouble( 16, value );
}

double VWTextureShaderTransparencyNoise::GetHighClip() const
{
	return this->GetShaderRecordDouble( 17 );
}

void VWTextureShaderTransparencyNoise::SetHighClip(double value)
{
	this->SetShaderRecordDouble( 17, value );
}

double VWTextureShaderTransparencyNoise::GetDetail() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderTransparencyNoise::SetDetail(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

double VWTextureShaderTransparencyNoise::GetCycles() const
{
	return this->GetShaderRecordDouble( 19 );
}

void VWTextureShaderTransparencyNoise::SetCycles(double value)
{
	this->SetShaderRecordDouble( 19, value );
}

double VWTextureShaderTransparencyNoise::GetRefraction() const
{
	return this->GetShaderRecordDouble( 20 );
}

void VWTextureShaderTransparencyNoise::SetRefraction(double value)
{
	this->SetShaderRecordDouble( 20, value );
}

double VWTextureShaderTransparencyNoise::GetTransparencyBlurriness() const
{
	return this->GetShaderRecordDouble( 21 );
}

void VWTextureShaderTransparencyNoise::SetTransparencyBlurriness(double value)
{
	this->SetShaderRecordDouble( 21, value );
}

CRGBColor VWTextureShaderTransparencyNoise::GetAbsorptionColor() const
{
	return this->GetShaderRecordColor( 22 );
}

void VWTextureShaderTransparencyNoise::SetAbsorptionColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 22, value );
}

double VWTextureShaderTransparencyNoise::GetAbsorptionDistance() const
{
	return this->GetShaderRecordDouble( 25 );
}

void VWTextureShaderTransparencyNoise::SetAbsorptionDistance(double value)
{
	this->SetShaderRecordDouble( 25, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderTransparencyTiles::VWTextureShaderTransparencyTiles(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyTiles::VWTextureShaderTransparencyTiles(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyTiles::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyTiles::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyTiles::VWTextureShaderTransparencyTiles(const VWTextureShaderTransparencyTiles& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyTiles::~VWTextureShaderTransparencyTiles()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyTiles& VWTextureShaderTransparencyTiles::operator=(const VWTextureShaderTransparencyTiles& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyTiles::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyTiles& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, kShaderPrototypeTransparency_Tiles );
	outValue = VWTextureShaderTransparencyTiles( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyTiles::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyTiles& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyTiles::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyTiles( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyTiles::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_Tiles;
}

ShaderTilesType VWTextureShaderTransparencyTiles::GetPattern() const
{
	return (ShaderTilesType)this->GetShaderRecordLong( 4 );
}

void VWTextureShaderTransparencyTiles::SetPattern(ShaderTilesType value)
{
	this->SetShaderRecordLong( 4, value );
}

CRGBColor VWTextureShaderTransparencyTiles::GetGroutColor() const
{
	return this->GetShaderRecordColor( 5 );
}

void VWTextureShaderTransparencyTiles::SetGroutColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 5, value );
}

CRGBColor VWTextureShaderTransparencyTiles::GetColor1() const
{
	return this->GetShaderRecordColor( 8 );
}

void VWTextureShaderTransparencyTiles::SetColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 8, value );
}

CRGBColor VWTextureShaderTransparencyTiles::GetColor2() const
{
	return this->GetShaderRecordColor( 11 );
}

void VWTextureShaderTransparencyTiles::SetColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 11, value );
}

CRGBColor VWTextureShaderTransparencyTiles::GetColor3() const
{
	return this->GetShaderRecordColor( 14 );
}

void VWTextureShaderTransparencyTiles::SetColor3(const CRGBColor& value)
{
	this->SetShaderRecordColor( 14, value );
}

bool VWTextureShaderTransparencyTiles::GetRandomizeColor() const
{
	return this->GetShaderRecordBool( 17 );
}

void VWTextureShaderTransparencyTiles::SetRandomizeColor(bool value)
{
	this->SetShaderRecordBool( 17, value );
}

double VWTextureShaderTransparencyTiles::GetGroutWidth() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderTransparencyTiles::SetGroutWidth(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

double VWTextureShaderTransparencyTiles::GetBevelWidth() const
{
	return this->GetShaderRecordDouble( 19 );
}

void VWTextureShaderTransparencyTiles::SetBevelWidth(double value)
{
	this->SetShaderRecordDouble( 19, value );
}

bool VWTextureShaderTransparencyTiles::GetBevel() const
{
	return this->GetShaderRecordBool( 20 );
}

void VWTextureShaderTransparencyTiles::SetBevel(bool value)
{
	this->SetShaderRecordBool( 20, value );
}

bool VWTextureShaderTransparencyTiles::GetHorizontalOrientation() const
{
	return this->GetShaderRecordBool( 21 );
}

void VWTextureShaderTransparencyTiles::SetHorizontalOrientation(bool value)
{
	this->SetShaderRecordBool( 21, value );
}

double VWTextureShaderTransparencyTiles::GetGlobalScale() const
{
	return this->GetShaderRecordDouble( 22 );
}

void VWTextureShaderTransparencyTiles::SetGlobalScale(double value)
{
	this->SetShaderRecordDouble( 22, value );
}

double VWTextureShaderTransparencyTiles::GetRelativeScaleU() const
{
	return this->GetShaderRecordDouble( 23 );
}

void VWTextureShaderTransparencyTiles::SetRelativeScaleU(double value)
{
	this->SetShaderRecordDouble( 23, value );
}

double VWTextureShaderTransparencyTiles::GetRelativeScaleV() const
{
	return this->GetShaderRecordDouble( 24 );
}

void VWTextureShaderTransparencyTiles::SetRelativeScaleV(double value)
{
	this->SetShaderRecordDouble( 24, value );
}

double VWTextureShaderTransparencyTiles::GetRefraction() const
{
	return this->GetShaderRecordDouble( 25 );
}

void VWTextureShaderTransparencyTiles::SetRefraction(double value)
{
	this->SetShaderRecordDouble( 25, value );
}

double VWTextureShaderTransparencyTiles::GetTransparencyBlurriness() const
{
	return this->GetShaderRecordDouble( 26 );
}

void VWTextureShaderTransparencyTiles::SetTransparencyBlurriness(double value)
{
	this->SetShaderRecordDouble( 26, value );
}

CRGBColor VWTextureShaderTransparencyTiles::GetAbsorptionColor() const
{
	return this->GetShaderRecordColor( 27 );
}

void VWTextureShaderTransparencyTiles::SetAbsorptionColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 27, value );
}

double VWTextureShaderTransparencyTiles::GetAbsorptionDistance() const
{
	return this->GetShaderRecordDouble( 30 );
}

void VWTextureShaderTransparencyTiles::SetAbsorptionDistance(double value)
{
	this->SetShaderRecordDouble( 30, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderTransparencyBricks::VWTextureShaderTransparencyBricks(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyBricks::VWTextureShaderTransparencyBricks(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyBricks::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyBricks::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyBricks::VWTextureShaderTransparencyBricks(const VWTextureShaderTransparencyBricks& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyBricks::~VWTextureShaderTransparencyBricks()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyBricks& VWTextureShaderTransparencyBricks::operator=(const VWTextureShaderTransparencyBricks& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyBricks::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyBricks& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, kShaderPrototypeTransparency_Bricks );
	outValue = VWTextureShaderTransparencyBricks( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyBricks::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyBricks& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyBricks::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyBricks( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyBricks::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_Bricks;
}

double VWTextureShaderTransparencyBricks::GetScale() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderTransparencyBricks::SetScale(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

double VWTextureShaderTransparencyBricks::GetBrickWidth() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderTransparencyBricks::SetBrickWidth(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderTransparencyBricks::GetBrickHeight() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderTransparencyBricks::SetBrickHeight(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

double VWTextureShaderTransparencyBricks::GetShift() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderTransparencyBricks::SetShift(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

Sint32 VWTextureShaderTransparencyBricks::GetHalfBrickRow() const
{
	return this->GetShaderRecordLong( 8 );
}

void VWTextureShaderTransparencyBricks::SetHalfBrickRow(Sint32 value)
{
	this->SetShaderRecordLong( 8, value );
}

double VWTextureShaderTransparencyBricks::GetHalfBrickShift() const
{
	return this->GetShaderRecordDouble( 9 );
}

void VWTextureShaderTransparencyBricks::SetHalfBrickShift(double value)
{
	this->SetShaderRecordDouble( 9, value );
}

double VWTextureShaderTransparencyBricks::GetGapSize() const
{
	return this->GetShaderRecordDouble( 10 );
}

void VWTextureShaderTransparencyBricks::SetGapSize(double value)
{
	this->SetShaderRecordDouble( 10, value );
}

double VWTextureShaderTransparencyBricks::GetGapNoise() const
{
	return this->GetShaderRecordDouble( 11 );
}

void VWTextureShaderTransparencyBricks::SetGapNoise(double value)
{
	this->SetShaderRecordDouble( 11, value );
}

CRGBColor VWTextureShaderTransparencyBricks::GetBrickColor1() const
{
	return this->GetShaderRecordColor( 12 );
}

void VWTextureShaderTransparencyBricks::SetBrickColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 12, value );
}

CRGBColor VWTextureShaderTransparencyBricks::GetBrickColor2() const
{
	return this->GetShaderRecordColor( 15 );
}

void VWTextureShaderTransparencyBricks::SetBrickColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 15, value );
}

CRGBColor VWTextureShaderTransparencyBricks::GetAltColor1() const
{
	return this->GetShaderRecordColor( 18 );
}

void VWTextureShaderTransparencyBricks::SetAltColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 18, value );
}

CRGBColor VWTextureShaderTransparencyBricks::GetAltColor2() const
{
	return this->GetShaderRecordColor( 21 );
}

void VWTextureShaderTransparencyBricks::SetAltColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 21, value );
}

CRGBColor VWTextureShaderTransparencyBricks::GetGapColor1() const
{
	return this->GetShaderRecordColor( 24 );
}

void VWTextureShaderTransparencyBricks::SetGapColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 24, value );
}

CRGBColor VWTextureShaderTransparencyBricks::GetGapColor2() const
{
	return this->GetShaderRecordColor( 27 );
}

void VWTextureShaderTransparencyBricks::SetGapColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 27, value );
}

double VWTextureShaderTransparencyBricks::GetContrast() const
{
	return this->GetShaderRecordDouble( 30 );
}

void VWTextureShaderTransparencyBricks::SetContrast(double value)
{
	this->SetShaderRecordDouble( 30, value );
}

Sint32 VWTextureShaderTransparencyBricks::GetAltColorRow() const
{
	return this->GetShaderRecordLong( 31 );
}

void VWTextureShaderTransparencyBricks::SetAltColorRow(Sint32 value)
{
	this->SetShaderRecordLong( 31, value );
}

Sint32 VWTextureShaderTransparencyBricks::GetAltColorColumn() const
{
	return this->GetShaderRecordLong( 32 );
}

void VWTextureShaderTransparencyBricks::SetAltColorColumn(Sint32 value)
{
	this->SetShaderRecordLong( 32, value );
}


double VWTextureShaderTransparencyBricks::GetRefraction() const
{
	return this->GetShaderRecordDouble( 33 );
}

void VWTextureShaderTransparencyBricks::SetRefraction(double value)
{
	this->SetShaderRecordDouble( 33, value );
}

double VWTextureShaderTransparencyBricks::GetTransparencyBlurriness() const
{
	return this->GetShaderRecordDouble( 34 );
}

void VWTextureShaderTransparencyBricks::SetTransparencyBlurriness(double value)
{
	this->SetShaderRecordDouble( 34, value );
}

CRGBColor VWTextureShaderTransparencyBricks::GetAbsorptionColor() const
{
	return this->GetShaderRecordColor( 35 );
}

void VWTextureShaderTransparencyBricks::SetAbsorptionColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 35, value );
}

double VWTextureShaderTransparencyBricks::GetAbsorptionDistance() const
{
	return this->GetShaderRecordDouble( 38 );
}

void VWTextureShaderTransparencyBricks::SetAbsorptionDistance(double value)
{
	this->SetShaderRecordDouble( 38, value );
}

double VWTextureShaderTransparencyBricks::GetBricksImageBlend() const
{
	return this->GetShaderRecordDouble( 39 );
}

void VWTextureShaderTransparencyBricks::SetBricksImageBlend(double value)
{
	this->SetShaderRecordDouble( 39, value );
}

double VWTextureShaderTransparencyBricks::GetGapImageBlend() const
{
	return this->GetShaderRecordDouble( 40 );
}

void VWTextureShaderTransparencyBricks::SetGapImageBlend(double value)
{
	this->SetShaderRecordDouble( 40, value );
}

double VWTextureShaderTransparencyBricks::GetAltBricksImageBlend() const
{
	return this->GetShaderRecordDouble( 41 );
}

void VWTextureShaderTransparencyBricks::SetAltBricksImageBlend(double value)
{
	this->SetShaderRecordDouble( 41, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderTransparencyPavement::VWTextureShaderTransparencyPavement(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyPavement::VWTextureShaderTransparencyPavement(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyPavement::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyPavement::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyPavement::VWTextureShaderTransparencyPavement(const VWTextureShaderTransparencyPavement& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyPavement::~VWTextureShaderTransparencyPavement()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyPavement& VWTextureShaderTransparencyPavement::operator=(const VWTextureShaderTransparencyPavement& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyPavement::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyPavement& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, kShaderPrototypeTransparency_Pavement );
	outValue = VWTextureShaderTransparencyPavement( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyPavement::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyPavement& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyPavement::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyPavement( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyPavement::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_Pavement;
}

double VWTextureShaderTransparencyPavement::GetScale() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderTransparencyPavement::SetScale(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

double VWTextureShaderTransparencyPavement::GetGapWidth() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderTransparencyPavement::SetGapWidth(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderTransparencyPavement::GetSoftness() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderTransparencyPavement::SetSoftness(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

CRGBColor VWTextureShaderTransparencyPavement::GetStoneColor1() const
{
	return this->GetShaderRecordColor( 7 );
}

void VWTextureShaderTransparencyPavement::SetStoneColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 7, value );
}

CRGBColor VWTextureShaderTransparencyPavement::GetStoneColor2() const
{
	return this->GetShaderRecordColor( 10 );
}

void VWTextureShaderTransparencyPavement::SetStoneColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 10, value );
}

double VWTextureShaderTransparencyPavement::GetCoarseMarbling() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderTransparencyPavement::SetCoarseMarbling(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

double VWTextureShaderTransparencyPavement::GetFineMarbling() const
{
	return this->GetShaderRecordDouble( 14 );
}

void VWTextureShaderTransparencyPavement::SetFineMarbling(double value)
{
	this->SetShaderRecordDouble( 14, value );
}

CRGBColor VWTextureShaderTransparencyPavement::GetGapColor1() const
{
	return this->GetShaderRecordColor( 15 );
}

void VWTextureShaderTransparencyPavement::SetGapColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 15, value );
}

CRGBColor VWTextureShaderTransparencyPavement::GetGapColor2() const
{
	return this->GetShaderRecordColor( 18 );
}

void VWTextureShaderTransparencyPavement::SetGapColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 18, value );
}

double VWTextureShaderTransparencyPavement::GetGapGrain() const
{
	return this->GetShaderRecordDouble( 21 );
}

void VWTextureShaderTransparencyPavement::SetGapGrain(double value)
{
	this->SetShaderRecordDouble( 21, value );
}

CRGBColor VWTextureShaderTransparencyPavement::GetSmudgeColor1() const
{
	return this->GetShaderRecordColor( 22 );
}

void VWTextureShaderTransparencyPavement::SetSmudgeColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 22, value );
}

CRGBColor VWTextureShaderTransparencyPavement::GetSmudgeColor2() const
{
	return this->GetShaderRecordColor( 25 );
}

void VWTextureShaderTransparencyPavement::SetSmudgeColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 25, value );
}

double VWTextureShaderTransparencyPavement::GetSmudgeAmount() const
{
	return this->GetShaderRecordDouble( 28 );
}

void VWTextureShaderTransparencyPavement::SetSmudgeAmount(double value)
{
	this->SetShaderRecordDouble( 28, value );
}

double VWTextureShaderTransparencyPavement::GetSmudgeSize() const
{
	return this->GetShaderRecordDouble( 29 );
}

void VWTextureShaderTransparencyPavement::SetSmudgeSize(double value)
{
	this->SetShaderRecordDouble( 29, value );
}

double VWTextureShaderTransparencyPavement::GetRefraction() const
{
	return this->GetShaderRecordDouble( 30 );
}

void VWTextureShaderTransparencyPavement::SetRefraction(double value)
{
	this->SetShaderRecordDouble( 30, value );
}

double VWTextureShaderTransparencyPavement::GetTransparencyBlurriness() const
{
	return this->GetShaderRecordDouble( 31 );
}

void VWTextureShaderTransparencyPavement::SetTransparencyBlurriness(double value)
{
	this->SetShaderRecordDouble( 31, value );
}

CRGBColor VWTextureShaderTransparencyPavement::GetAbsorptionColor() const
{
	return this->GetShaderRecordColor( 32 );
}

void VWTextureShaderTransparencyPavement::SetAbsorptionColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 32, value );
}

double VWTextureShaderTransparencyPavement::GetAbsorptionDistance() const
{
	return this->GetShaderRecordDouble( 35 );
}

void VWTextureShaderTransparencyPavement::SetAbsorptionDistance(double value)
{
	this->SetShaderRecordDouble( 35, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderTransparencyRectangularMask::VWTextureShaderTransparencyRectangularMask(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyRectangularMask::VWTextureShaderTransparencyRectangularMask(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyRectangularMask::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyRectangularMask::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyRectangularMask::VWTextureShaderTransparencyRectangularMask(const VWTextureShaderTransparencyRectangularMask& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyRectangularMask::~VWTextureShaderTransparencyRectangularMask()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyRectangularMask& VWTextureShaderTransparencyRectangularMask::operator=(const VWTextureShaderTransparencyRectangularMask& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyRectangularMask::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyRectangularMask& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, kShaderPrototypeTransparency_RectangularMask );
	outValue = VWTextureShaderTransparencyRectangularMask( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyRectangularMask::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyRectangularMask& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyRectangularMask::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyRectangularMask( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyRectangularMask::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_RectangularMask;
}

Sint32 VWTextureShaderTransparencyRectangularMask::GetRepeatH() const
{
	return this->GetShaderRecordLong( 4 );
}

void VWTextureShaderTransparencyRectangularMask::SetRepeatH(Sint32 value)
{
	this->SetShaderRecordLong( 4, value );
}

Sint32 VWTextureShaderTransparencyRectangularMask::GetRepeatV() const
{
	return this->GetShaderRecordLong( 5 );
}

void VWTextureShaderTransparencyRectangularMask::SetRepeatV(Sint32 value)
{
	this->SetShaderRecordLong( 5, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderTransparencyImageMask::VWTextureShaderTransparencyImageMask(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderTransparencyImageMask::VWTextureShaderTransparencyImageMask(MCObjectHandle hShaderTransparency)
{
	VWFC_ASSERT( VWTextureShaderTransparencyImageMask::IsShaderRecordObject( hShaderTransparency ) );
	if ( ! VWTextureShaderTransparencyImageMask::IsShaderRecordObject( hShaderTransparency ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderTransparency;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderTransparencyImageMask::VWTextureShaderTransparencyImageMask(const VWTextureShaderTransparencyImageMask& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderTransparencyImageMask::~VWTextureShaderTransparencyImageMask()
{
	fhObject		= nil;
}

VWTextureShaderTransparencyImageMask& VWTextureShaderTransparencyImageMask::operator=(const VWTextureShaderTransparencyImageMask& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderTransparencyImageMask::CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyImageMask& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Transparency, kShaderPrototypeTransparency_ImageMask );
	outValue = VWTextureShaderTransparencyImageMask( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderTransparencyImageMask::GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyImageMask& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Transparency );
	bool result = VWTextureShaderTransparencyImageMask::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderTransparencyImageMask( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderTransparencyImageMask::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Transparency
			&&	prototype == kShaderPrototypeTransparency_ImageMask;
}


MCObjectHandle VWTextureShaderTransparencyImageMask::GetMask() const
{
	MCObjectHandle	hExistingTextureBitmap = gSDK->FindAuxObject( fhObject, kTextureBitmapNode );
	MCObjectHandle	hBitmap	= gSDK->FindAuxObject( hExistingTextureBitmap, kPaintNode );
	return hBitmap;
}

void VWTextureShaderTransparencyImageMask::SetMaskImage(MCObjectHandle& hBitmapObj) const
{
	MCObjectHandle hExistingTextureBitmap = gSDK->FindAuxObject( fhObject, kTextureBitmapNode );
	if ( hExistingTextureBitmap )
	{
		gSDK->AddBeforeSwapObject(hExistingTextureBitmap);
		gSDK->DeleteObject( hExistingTextureBitmap );
	}

	hExistingTextureBitmap	= gSDK->CreateTextureBitmapFromPaintNode( hBitmapObj );
	
	// make sure the image is compressed
	// otherwise the thumbnails in the resource browser will be black
	MCObjectHandle image = gSDK->FindAuxObject( hExistingTextureBitmap, kImageDefNode );
	if ( image )
	{
		gSDK->CompressTextureImage( image );
	}

	gSDK->AttachAuxObject( hExistingTextureBitmap, fhObject );

	// the parameter cannot be used no more
	hBitmapObj	= NULL;
}

Sint32 VWTextureShaderTransparencyImageMask::GetRepeatH() const
{
	return this->GetShaderRecordLong( 5 );
}

void VWTextureShaderTransparencyImageMask::SetRepeatH(Sint32 value)
{
	this->SetShaderRecordLong( 5, value );
}

Sint32 VWTextureShaderTransparencyImageMask::GetRepeatV() const
{
	return this->GetShaderRecordLong( 6 );
}

void VWTextureShaderTransparencyImageMask::SetRepeatV(Sint32 value)
{
	this->SetShaderRecordLong( 6, value );
}

bool VWTextureShaderTransparencyImageMask::GetAntiAliased() const
{
	return this->GetShaderRecordBool( 7 );
}

void VWTextureShaderTransparencyImageMask::SetAntiAliased(bool value)
{
	this->SetShaderRecordBool( 7, value );
}

void VWTextureShaderTransparencyImageMask::SetMaskImageFromAlphaChannel( MCObjectHandle hImageMask, bool bUseAlpha )
{
	MCObjectHandle hTextureBitmapMask = NULL;
	hTextureBitmapMask = gSDK->CreateImageMaskFromAlphaChannel( hImageMask, bUseAlpha );
	if( hTextureBitmapMask )
	{
		MCObjectHandle image = gSDK->FindAuxObject( hTextureBitmapMask, kImageDefNode );
		if ( image )
		{
			gSDK->CompressTextureImage( image );
		}

		gSDK->AttachAuxObject( hTextureBitmapMask, fhObject );
	}
}
