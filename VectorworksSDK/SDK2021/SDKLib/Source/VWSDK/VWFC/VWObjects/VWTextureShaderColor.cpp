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
VWTextureShaderColorPlain::VWTextureShaderColorPlain(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderColorPlain::VWTextureShaderColorPlain(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderColorPlain::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderColorPlain::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderColorPlain::VWTextureShaderColorPlain(const VWTextureShaderColorPlain& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderColorPlain::~VWTextureShaderColorPlain()
{
	fhObject		= nil;
}

VWTextureShaderColorPlain& VWTextureShaderColorPlain::operator=(const VWTextureShaderColorPlain& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderColorPlain::CreateShader(MCObjectHandle hTexture, VWTextureShaderColorPlain& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Color, kShaderPrototypeColor_Plain );
	outValue = VWTextureShaderColorPlain( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderColorPlain::GetShader(MCObjectHandle hTexture, VWTextureShaderColorPlain& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Color );
	bool result = VWTextureShaderColorPlain::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderColorPlain( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderColorPlain::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Color
			&&	prototype == kShaderPrototypeColor_Plain;
}

CRGBColor VWTextureShaderColorPlain::GetColor() const
{
	return this->GetShaderRecordColor( 4 );
}

void VWTextureShaderColorPlain::SetColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 4, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderColorImage::VWTextureShaderColorImage(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderColorImage::VWTextureShaderColorImage(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderColorImage::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderColorImage::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderColorImage::VWTextureShaderColorImage(const VWTextureShaderColorImage& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderColorImage::~VWTextureShaderColorImage()
{
	fhObject		= nil;
}

VWTextureShaderColorImage& VWTextureShaderColorImage::operator=(const VWTextureShaderColorImage& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderColorImage::CreateShader(MCObjectHandle hTexture, VWTextureShaderColorImage& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Color, kShaderPrototypeColor_Image );
	outValue = VWTextureShaderColorImage( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderColorImage::GetShader(MCObjectHandle hTexture, VWTextureShaderColorImage& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Color );
	bool result = VWTextureShaderColorImage::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderColorImage( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderColorImage::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Color
			&&	prototype == kShaderPrototypeColor_Image;
}

MCObjectHandle VWTextureShaderColorImage::GetImage() const
{
	MCObjectHandle	hExistingTextureBitmap = gSDK->FindAuxObject( fhObject, kTextureBitmapNode );
	MCObjectHandle	hBitmap	= gSDK->FindAuxObject( hExistingTextureBitmap, kPaintNode );
	return hBitmap;
}

void VWTextureShaderColorImage::SetImage(MCObjectHandle& hBitmapObj) const
{
	MCObjectHandle hExistingTextureBitmap = gSDK->FindAuxObject( fhObject, kTextureBitmapNode );
	if ( hExistingTextureBitmap )
	{
		gSDK->DeleteObject( hExistingTextureBitmap, false );
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

VWTextureShaderColorImage::EColorFilter VWTextureShaderColorImage::GetColorFilter() const
{
	return (EColorFilter) this->GetShaderRecordLong( 5 );
}

void VWTextureShaderColorImage::SetColorFilter(EColorFilter value)
{
	this->SetShaderRecordLong( 5, value );
}

CRGBColor VWTextureShaderColorImage::GetFilterColor() const
{
	return this->GetShaderRecordColor( 6 );
}

void VWTextureShaderColorImage::SetFilterColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 6, value );
}

bool VWTextureShaderColorImage::GetAntiAliased() const
{
	return this->GetShaderRecordBool( 9 );
}

void VWTextureShaderColorImage::SetAntiAliased(bool value)
{
	this->SetShaderRecordBool( 9, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderColorFresnel::VWTextureShaderColorFresnel(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderColorFresnel::VWTextureShaderColorFresnel(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderColorFresnel::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderColorFresnel::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderColorFresnel::VWTextureShaderColorFresnel(const VWTextureShaderColorFresnel& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderColorFresnel::~VWTextureShaderColorFresnel()
{
	fhObject		= nil;
}

VWTextureShaderColorFresnel& VWTextureShaderColorFresnel::operator=(const VWTextureShaderColorFresnel& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderColorFresnel::CreateShader(MCObjectHandle hTexture, VWTextureShaderColorFresnel& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Color, kShaderPrototypeColor_Fresnel );
	outValue = VWTextureShaderColorFresnel( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderColorFresnel::GetShader(MCObjectHandle hTexture, VWTextureShaderColorFresnel& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Color );
	bool result = VWTextureShaderColorFresnel::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderColorFresnel( hShaderRecObj );
	}

	return result;
}

/*static*/ bool VWTextureShaderColorFresnel::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Color
			&&	prototype == kShaderPrototypeColor_Fresnel;
}

CRGBColor VWTextureShaderColorFresnel::GetEdgeColor() const
{
	return this->GetShaderRecordColor( 4 );
}

void VWTextureShaderColorFresnel::SetEdgeColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 4, value );
}

CRGBColor VWTextureShaderColorFresnel::GetCenterColor() const
{
	return this->GetShaderRecordColor( 7 );
}

void VWTextureShaderColorFresnel::SetCenterColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 7, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderColorNoise::VWTextureShaderColorNoise(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderColorNoise::VWTextureShaderColorNoise(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderColorNoise::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderColorNoise::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderColorNoise::VWTextureShaderColorNoise(const VWTextureShaderColorNoise& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderColorNoise::~VWTextureShaderColorNoise()
{
	fhObject		= nil;
}

VWTextureShaderColorNoise& VWTextureShaderColorNoise::operator=(const VWTextureShaderColorNoise& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderColorNoise::CreateShader(MCObjectHandle hTexture, VWTextureShaderColorNoise& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Color, kShaderPrototypeColor_Noise );
	outValue = VWTextureShaderColorNoise( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderColorNoise::GetShader(MCObjectHandle hTexture, VWTextureShaderColorNoise& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Color );
	bool result = VWTextureShaderColorNoise::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderColorNoise( hShaderRecObj );
	}

	return result;
}

/*static*/ bool VWTextureShaderColorNoise::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Color
			&&	prototype == kShaderPrototypeColor_Noise;
}

ShaderNoiseType VWTextureShaderColorNoise::GetPattern() const
{
	return (ShaderNoiseType)this->GetShaderRecordLong( 4 );
}

void VWTextureShaderColorNoise::SetPattern(ShaderNoiseType value)
{
	this->SetShaderRecordLong( 4, value );
}

CRGBColor VWTextureShaderColorNoise::GetColor1() const
{
	return this->GetShaderRecordColor( 5 );
}

void VWTextureShaderColorNoise::SetColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 5, value );
}

CRGBColor VWTextureShaderColorNoise::GetColor2() const
{
	return this->GetShaderRecordColor( 8 );
}

void VWTextureShaderColorNoise::SetColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 8, value );
}

bool VWTextureShaderColorNoise::GetNoiseSolid() const
{
	return this->GetShaderRecordBool( 11 );
}

void VWTextureShaderColorNoise::SetNoiseSolid(bool value)
{
	this->SetShaderRecordBool( 11, value );
}

double VWTextureShaderColorNoise::GetGlobalScale() const
{
	return this->GetShaderRecordDouble( 12 );
}

void VWTextureShaderColorNoise::SetGlobalScale(double value)
{
	this->SetShaderRecordDouble( 12, value );
}

double VWTextureShaderColorNoise::GetRelativeUScale() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderColorNoise::SetRelativeUScale(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

double VWTextureShaderColorNoise::GetRelativeVScale() const
{
	return this->GetShaderRecordDouble( 14 );
}

void VWTextureShaderColorNoise::SetRelativeVScale(double value)
{
	this->SetShaderRecordDouble( 14, value );
}

double VWTextureShaderColorNoise::GetRelativeWScale() const
{
	return this->GetShaderRecordDouble( 15 );
}

void VWTextureShaderColorNoise::SetRelativeWScale(double value)
{
	this->SetShaderRecordDouble( 15, value );
}

double VWTextureShaderColorNoise::GetLowClip() const
{
	return this->GetShaderRecordDouble( 16 );
}

void VWTextureShaderColorNoise::SetLowClip(double value)
{
	this->SetShaderRecordDouble( 16, value );
}

double VWTextureShaderColorNoise::GetHighClip() const
{
	return this->GetShaderRecordDouble( 17 );
}

void VWTextureShaderColorNoise::SetHighClip(double value)
{
	this->SetShaderRecordDouble( 17, value );
}

double VWTextureShaderColorNoise::GetDetail() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderColorNoise::SetDetail(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

double VWTextureShaderColorNoise::GetCycles() const
{
	return this->GetShaderRecordDouble( 19 );
}

void VWTextureShaderColorNoise::SetCycles(double value)
{
	this->SetShaderRecordDouble( 19, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderColorTiles::VWTextureShaderColorTiles(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderColorTiles::VWTextureShaderColorTiles(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderColorTiles::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderColorTiles::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderColorTiles::VWTextureShaderColorTiles(const VWTextureShaderColorTiles& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderColorTiles::~VWTextureShaderColorTiles()
{
	fhObject		= nil;
}

VWTextureShaderColorTiles& VWTextureShaderColorTiles::operator=(const VWTextureShaderColorTiles& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderColorTiles::CreateShader(MCObjectHandle hTexture, VWTextureShaderColorTiles& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Color, kShaderPrototypeColor_Tiles );
	outValue = VWTextureShaderColorTiles( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderColorTiles::GetShader(MCObjectHandle hTexture, VWTextureShaderColorTiles& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Color );
	bool result = VWTextureShaderColorTiles::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderColorTiles( hShaderRecObj );
	}

	return result;
}

/*static*/ bool VWTextureShaderColorTiles::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Color
			&&	prototype == kShaderPrototypeColor_Tiles;
}

ShaderTilesType VWTextureShaderColorTiles::GetPattern() const
{
	return (ShaderTilesType)this->GetShaderRecordLong( 4 );
}

void VWTextureShaderColorTiles::SetPattern(ShaderTilesType value)
{
	this->SetShaderRecordLong( 4, value );
}

CRGBColor VWTextureShaderColorTiles::GetGroutColor() const
{
	return this->GetShaderRecordColor( 5 );
}

void VWTextureShaderColorTiles::SetGroutColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 5, value );
}

CRGBColor VWTextureShaderColorTiles::GetColor1() const
{
	return this->GetShaderRecordColor( 8 );
}

void VWTextureShaderColorTiles::SetColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 8, value );
}

CRGBColor VWTextureShaderColorTiles::GetColor2() const
{
	return this->GetShaderRecordColor( 11 );
}

void VWTextureShaderColorTiles::SetColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 11, value );
}

CRGBColor VWTextureShaderColorTiles::GetColor3() const
{
	return this->GetShaderRecordColor( 14 );
}

void VWTextureShaderColorTiles::SetColor3(const CRGBColor& value)
{
	this->SetShaderRecordColor( 14, value );
}

bool VWTextureShaderColorTiles::GetRandomizeColor() const
{
	return this->GetShaderRecordBool( 17 );
}

void VWTextureShaderColorTiles::SetRandomizeColor(bool value)
{
	this->SetShaderRecordBool( 17, value );
}

double VWTextureShaderColorTiles::GetGroutWidth() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderColorTiles::SetGroutWidth(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

double VWTextureShaderColorTiles::GetBevelWidth() const
{
	return this->GetShaderRecordDouble( 19 );
}

void VWTextureShaderColorTiles::SetBevelWidth(double value)
{
	this->SetShaderRecordDouble( 19, value );
}

bool VWTextureShaderColorTiles::GetBevel() const
{
	return this->GetShaderRecordBool( 20 );
}

void VWTextureShaderColorTiles::SetBevel(bool value)
{
	this->SetShaderRecordBool( 20, value );
}

bool VWTextureShaderColorTiles::GetHorizontalOrientation() const
{
	return this->GetShaderRecordBool( 21 );
}

void VWTextureShaderColorTiles::SetHorizontalOrientation(bool value)
{
	this->SetShaderRecordBool( 21, value );
}

double VWTextureShaderColorTiles::GetGlobalScale() const
{
	return this->GetShaderRecordDouble( 22 );
}

void VWTextureShaderColorTiles::SetGlobalScale(double value)
{
	this->SetShaderRecordDouble( 22, value );
}

double VWTextureShaderColorTiles::GetRelativeScaleU() const
{
	return this->GetShaderRecordDouble( 23 );
}

void VWTextureShaderColorTiles::SetRelativeScaleU(double value)
{
	this->SetShaderRecordDouble( 23, value );
}

double VWTextureShaderColorTiles::GetRelativeScaleV() const
{
	return this->GetShaderRecordDouble( 24 );
}

void VWTextureShaderColorTiles::SetRelativeScaleV(double value)
{
	this->SetShaderRecordDouble( 24, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
VWTextureShaderColorBricks::VWTextureShaderColorBricks(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderColorBricks::VWTextureShaderColorBricks(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderColorBricks::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderColorBricks::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderColorBricks::VWTextureShaderColorBricks(const VWTextureShaderColorBricks& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderColorBricks::~VWTextureShaderColorBricks()
{
	fhObject		= nil;
}

VWTextureShaderColorBricks& VWTextureShaderColorBricks::operator=(const VWTextureShaderColorBricks& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderColorBricks::CreateShader(MCObjectHandle hTexture, VWTextureShaderColorBricks& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Color, kShaderPrototypeColor_Bricks );
	outValue = VWTextureShaderColorBricks( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderColorBricks::GetShader(MCObjectHandle hTexture, VWTextureShaderColorBricks& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Color );
	bool result = VWTextureShaderColorBricks::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderColorBricks( hShaderRecObj );
	}

	return result;
}

/*static*/ bool VWTextureShaderColorBricks::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Color
			&&	prototype == kShaderPrototypeColor_Bricks;
}

double VWTextureShaderColorBricks::GetScale() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderColorBricks::SetScale(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

double VWTextureShaderColorBricks::GetBrickWidth() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderColorBricks::SetBrickWidth(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderColorBricks::GetBrickHeight() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderColorBricks::SetBrickHeight(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

double VWTextureShaderColorBricks::GetShift() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderColorBricks::SetShift(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

Sint32 VWTextureShaderColorBricks::GetHalfBrickRow() const
{
	return this->GetShaderRecordLong( 8 );
}

void VWTextureShaderColorBricks::SetHalfBrickRow(Sint32 value)
{
	this->SetShaderRecordLong( 8, value );
}

double VWTextureShaderColorBricks::GetHalfBrickShift() const
{
	return this->GetShaderRecordDouble( 9 );
}

void VWTextureShaderColorBricks::SetHalfBrickShift(double value)
{
	this->SetShaderRecordDouble( 9, value );
}

double VWTextureShaderColorBricks::GetGapSize() const
{
	return this->GetShaderRecordDouble( 10 );
}

void VWTextureShaderColorBricks::SetGapSize(double value)
{
	this->SetShaderRecordDouble( 10, value );
}

double VWTextureShaderColorBricks::GetGapNoise() const
{
	return this->GetShaderRecordDouble( 11 );
}

void VWTextureShaderColorBricks::SetGapNoise(double value)
{
	this->SetShaderRecordDouble( 11, value );
}

CRGBColor VWTextureShaderColorBricks::GetBrickColor1() const
{
	return this->GetShaderRecordColor( 12 );
}

void VWTextureShaderColorBricks::SetBrickColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 12, value );
}

CRGBColor VWTextureShaderColorBricks::GetBrickColor2() const
{
	return this->GetShaderRecordColor( 15 );
}

void VWTextureShaderColorBricks::SetBrickColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 15, value );
}

CRGBColor VWTextureShaderColorBricks::GetAltColor1() const
{
	return this->GetShaderRecordColor( 18 );
}

void VWTextureShaderColorBricks::SetAltColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 18, value );
}

CRGBColor VWTextureShaderColorBricks::GetAltColor2() const
{
	return this->GetShaderRecordColor( 21 );
}

void VWTextureShaderColorBricks::SetAltColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 21, value );
}

CRGBColor VWTextureShaderColorBricks::GetGapColor1() const
{
	return this->GetShaderRecordColor( 24 );
}

void VWTextureShaderColorBricks::SetGapColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 24, value );
}

CRGBColor VWTextureShaderColorBricks::GetGapColor2() const
{
	return this->GetShaderRecordColor( 27 );
}

void VWTextureShaderColorBricks::SetGapColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 27, value );
}

double VWTextureShaderColorBricks::GetContrast() const
{
	return this->GetShaderRecordDouble( 30 );
}

void VWTextureShaderColorBricks::SetContrast(double value)
{
	this->SetShaderRecordDouble( 30, value );
}

Sint32 VWTextureShaderColorBricks::GetAltColorRow() const
{
	return this->GetShaderRecordLong( 31 );
}

void VWTextureShaderColorBricks::SetAltColorRow(Sint32 value)
{
	this->SetShaderRecordLong( 31, value );
}

Sint32 VWTextureShaderColorBricks::GetAltColorColumn() const
{
	return this->GetShaderRecordLong( 32 );
}

void VWTextureShaderColorBricks::SetAltColorColumn(Sint32 value)
{
	this->SetShaderRecordLong( 32, value );
}

double VWTextureShaderColorBricks::GetBricksImageBlend() const
{
	return this->GetShaderRecordDouble( 33 );
}

void VWTextureShaderColorBricks::SetBricksImageBlend(double value)
{
	this->SetShaderRecordDouble( 33, value );
}

double VWTextureShaderColorBricks::GetGapImageBlend() const
{
	return this->GetShaderRecordDouble( 34 );
}

void VWTextureShaderColorBricks::SetGapImageBlend(double value)
{
	this->SetShaderRecordDouble( 34, value );
}

double VWTextureShaderColorBricks::GetAltBricksImageBlend() const
{
	return this->GetShaderRecordDouble( 35 );
}

void VWTextureShaderColorBricks::SetAltBricksImageBlend(double value)
{
	this->SetShaderRecordDouble( 35, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderColorPavement::VWTextureShaderColorPavement(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderColorPavement::VWTextureShaderColorPavement(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderColorPavement::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderColorPavement::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderColorPavement::VWTextureShaderColorPavement(const VWTextureShaderColorPavement& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderColorPavement::~VWTextureShaderColorPavement()
{
	fhObject		= nil;
}

VWTextureShaderColorPavement& VWTextureShaderColorPavement::operator=(const VWTextureShaderColorPavement& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderColorPavement::CreateShader(MCObjectHandle hTexture, VWTextureShaderColorPavement& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Color, kShaderPrototypeColor_Pavement );
	outValue = VWTextureShaderColorPavement( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderColorPavement::GetShader(MCObjectHandle hTexture, VWTextureShaderColorPavement& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Color );
	bool result = VWTextureShaderColorPavement::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderColorPavement( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderColorPavement::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Color
			&&	prototype == kShaderPrototypeColor_Pavement;
}

double VWTextureShaderColorPavement::GetScale() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderColorPavement::SetScale(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

double VWTextureShaderColorPavement::GetGapWidth() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderColorPavement::SetGapWidth(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderColorPavement::GetSoftness() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderColorPavement::SetSoftness(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

CRGBColor VWTextureShaderColorPavement::GetStoneColor1() const
{
	return this->GetShaderRecordColor( 7 );
}

void VWTextureShaderColorPavement::SetStoneColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 7, value );
}

CRGBColor VWTextureShaderColorPavement::GetStoneColor2() const
{
	return this->GetShaderRecordColor( 10 );
}

void VWTextureShaderColorPavement::SetStoneColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 10, value );
}

double VWTextureShaderColorPavement::GetCoarseMarbling() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderColorPavement::SetCoarseMarbling(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

double VWTextureShaderColorPavement::GetFineMarbling() const
{
	return this->GetShaderRecordDouble( 14 );
}

void VWTextureShaderColorPavement::SetFineMarbling(double value)
{
	this->SetShaderRecordDouble( 14, value );
}

CRGBColor VWTextureShaderColorPavement::GetGapColor1() const
{
	return this->GetShaderRecordColor( 15 );
}

void VWTextureShaderColorPavement::SetGapColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 15, value );
}

CRGBColor VWTextureShaderColorPavement::GetGapColor2() const
{
	return this->GetShaderRecordColor( 18 );
}

void VWTextureShaderColorPavement::SetGapColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 18, value );
}

double VWTextureShaderColorPavement::GetGapGrain() const
{
	return this->GetShaderRecordDouble( 21 );
}

void VWTextureShaderColorPavement::SetGapGrain(double value)
{
	this->SetShaderRecordDouble( 21, value );
}

CRGBColor VWTextureShaderColorPavement::GetSmudgeColor1() const
{
	return this->GetShaderRecordColor( 22 );
}

void VWTextureShaderColorPavement::SetSmudgeColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 22, value );
}

CRGBColor VWTextureShaderColorPavement::GetSmudgeColor2() const
{
	return this->GetShaderRecordColor( 25 );
}

void VWTextureShaderColorPavement::SetSmudgeColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 25, value );
}

double VWTextureShaderColorPavement::GetSmudgeAmount() const
{
	return this->GetShaderRecordDouble( 28 );
}

void VWTextureShaderColorPavement::SetSmudgeAmount(double value)
{
	this->SetShaderRecordDouble( 28, value );
}

double VWTextureShaderColorPavement::GetSmudgeSize() const
{
	return this->GetShaderRecordDouble( 29 );
}

void VWTextureShaderColorPavement::SetSmudgeSize(double value)
{
	this->SetShaderRecordDouble( 29, value );
}

