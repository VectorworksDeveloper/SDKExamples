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
VWTextureShaderBumpImage::VWTextureShaderBumpImage(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderBumpImage::VWTextureShaderBumpImage(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderBumpImage::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderBumpImage::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderBumpImage::VWTextureShaderBumpImage(const VWTextureShaderBumpImage& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderBumpImage::~VWTextureShaderBumpImage()
{
	fhObject		= nil;
}

VWTextureShaderBumpImage& VWTextureShaderBumpImage::operator=(const VWTextureShaderBumpImage& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderBumpImage::CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpImage& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Bump, kShaderPrototypeBump_Image );
	outValue = VWTextureShaderBumpImage( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderBumpImage::GetShader(MCObjectHandle hTexture, VWTextureShaderBumpImage& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Bump );
	bool result = VWTextureShaderBumpImage::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderBumpImage( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderBumpImage::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Bump
			&&	prototype == kShaderPrototypeBump_Image;
}

MCObjectHandle VWTextureShaderBumpImage::GetImage() const
{
	MCObjectHandle	hExistingTextureBitmap = gSDK->FindAuxObject( fhObject, kTextureBitmapNode );
	MCObjectHandle	hBitmap	= gSDK->FindAuxObject( hExistingTextureBitmap, kPaintNode );
	return hBitmap;
}

void VWTextureShaderBumpImage::SetImage(MCObjectHandle& hBitmapObj) const
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

double VWTextureShaderBumpImage::GetBumpStrength() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderBumpImage::SetBumpStrength(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderBumpImage::GetDisplacementMaxHeight() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderBumpImage::SetDisplacementMaxHeight(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

Sint32 VWTextureShaderBumpImage::GetDisplacementDetail() const
{
	return this->GetShaderRecordLong( 7 );
}

void VWTextureShaderBumpImage::SetDisplacementDetail(Sint32 value)
{
	this->SetShaderRecordLong( 7, value );
}

bool VWTextureShaderBumpImage::GetDisplacementSelfShadow() const
{
	return this->GetShaderRecordBool( 8 );
}

void VWTextureShaderBumpImage::SetDisplacementSelfShadow(bool value)
{
	this->SetShaderRecordBool( 8, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderBumpNoise::VWTextureShaderBumpNoise(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderBumpNoise::VWTextureShaderBumpNoise(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderBumpNoise::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderBumpNoise::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderBumpNoise::VWTextureShaderBumpNoise(const VWTextureShaderBumpNoise& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderBumpNoise::~VWTextureShaderBumpNoise()
{
	fhObject		= nil;
}

VWTextureShaderBumpNoise& VWTextureShaderBumpNoise::operator=(const VWTextureShaderBumpNoise& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderBumpNoise::CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpNoise& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Bump, kShaderPrototypeBump_Noise );
	outValue = VWTextureShaderBumpNoise( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderBumpNoise::GetShader(MCObjectHandle hTexture, VWTextureShaderBumpNoise& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Bump );
	bool result = VWTextureShaderBumpNoise::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderBumpNoise( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderBumpNoise::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Bump
			&&	prototype == kShaderPrototypeBump_Noise;
}

ShaderNoiseType VWTextureShaderBumpNoise::GetPattern() const
{
	return (ShaderNoiseType)this->GetShaderRecordLong( 4 );
}

void VWTextureShaderBumpNoise::SetPattern(ShaderNoiseType value)
{
	this->SetShaderRecordLong( 4, value );
}

CRGBColor VWTextureShaderBumpNoise::GetColor1() const
{
	return this->GetShaderRecordColor( 5 );
}

void VWTextureShaderBumpNoise::SetColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 5, value );
}

CRGBColor VWTextureShaderBumpNoise::GetColor2() const
{
	return this->GetShaderRecordColor( 8 );
}

void VWTextureShaderBumpNoise::SetColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 8, value );
}

bool VWTextureShaderBumpNoise::GetNoiseSolid() const
{
	return this->GetShaderRecordBool( 11 );
}

void VWTextureShaderBumpNoise::SetNoiseSolid(bool value)
{
	this->SetShaderRecordBool( 11, value );
}

double VWTextureShaderBumpNoise::GetGlobalScale() const
{
	return this->GetShaderRecordDouble( 12 );
}

void VWTextureShaderBumpNoise::SetGlobalScale(double value)
{
	this->SetShaderRecordDouble( 12, value );
}

double VWTextureShaderBumpNoise::GetRelativeUScale() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderBumpNoise::SetRelativeUScale(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

double VWTextureShaderBumpNoise::GetRelativeVScale() const
{
	return this->GetShaderRecordDouble( 14 );
}

void VWTextureShaderBumpNoise::SetRelativeVScale(double value)
{
	this->SetShaderRecordDouble( 14, value );
}

double VWTextureShaderBumpNoise::GetRelativeWScale() const
{
	return this->GetShaderRecordDouble( 15 );
}

void VWTextureShaderBumpNoise::SetRelativeWScale(double value)
{
	this->SetShaderRecordDouble( 15, value );
}

double VWTextureShaderBumpNoise::GetLowClip() const
{
	return this->GetShaderRecordDouble( 16 );
}

void VWTextureShaderBumpNoise::SetLowClip(double value)
{
	this->SetShaderRecordDouble( 16, value );
}

double VWTextureShaderBumpNoise::GetHighClip() const
{
	return this->GetShaderRecordDouble( 17 );
}

void VWTextureShaderBumpNoise::SetHighClip(double value)
{
	this->SetShaderRecordDouble( 17, value );
}

double VWTextureShaderBumpNoise::GetDetail() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderBumpNoise::SetDetail(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

double VWTextureShaderBumpNoise::GetCycles() const
{
	return this->GetShaderRecordDouble( 19 );
}

void VWTextureShaderBumpNoise::SetCycles(double value)
{
	this->SetShaderRecordDouble( 19, value );
}

double VWTextureShaderBumpNoise::GetBumpStrength() const
{
	return this->GetShaderRecordDouble( 20 );
}

void VWTextureShaderBumpNoise::SetBumpStrength(double value)
{
	this->SetShaderRecordDouble( 20, value );
}

double VWTextureShaderBumpNoise::GetDisplacementMaxHeight() const
{
	return this->GetShaderRecordDouble( 21 );
}

void VWTextureShaderBumpNoise::SetDisplacementMaxHeight(double value)
{
	this->SetShaderRecordDouble( 21, value );
}

Sint32 VWTextureShaderBumpNoise::GetDisplacementDetail() const
{
	return this->GetShaderRecordLong( 22 );
}

void VWTextureShaderBumpNoise::SetDisplacementDetail(Sint32 value)
{
	this->SetShaderRecordLong( 22, value );
}

bool VWTextureShaderBumpNoise::GetDisplacementSelfShadow() const
{
	return this->GetShaderRecordBool( 23 );
}

void VWTextureShaderBumpNoise::SetDisplacementSelfShadow(bool value)
{
	this->SetShaderRecordBool( 23, value );
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

VWTextureShaderBumpTiles::VWTextureShaderBumpTiles(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderBumpTiles::VWTextureShaderBumpTiles(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderBumpTiles::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderBumpTiles::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderBumpTiles::VWTextureShaderBumpTiles(const VWTextureShaderBumpTiles& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderBumpTiles::~VWTextureShaderBumpTiles()
{
	fhObject		= nil;
}

VWTextureShaderBumpTiles& VWTextureShaderBumpTiles::operator=(const VWTextureShaderBumpTiles& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderBumpTiles::CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpTiles& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Bump, kShaderPrototypeBump_Tiles );
	outValue = VWTextureShaderBumpTiles( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderBumpTiles::GetShader(MCObjectHandle hTexture, VWTextureShaderBumpTiles& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Bump );
	bool result = VWTextureShaderBumpTiles::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderBumpTiles( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderBumpTiles::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Bump
			&&	prototype == kShaderPrototypeBump_Tiles;
}

ShaderTilesType VWTextureShaderBumpTiles::GetPattern() const
{
	return (ShaderTilesType)this->GetShaderRecordLong( 4 );
}

void VWTextureShaderBumpTiles::SetPattern(ShaderTilesType value)
{
	this->SetShaderRecordLong( 4, value );
}

CRGBColor VWTextureShaderBumpTiles::GetGroutColor() const
{
	return this->GetShaderRecordColor( 5 );
}

void VWTextureShaderBumpTiles::SetGroutColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 5, value );
}

CRGBColor VWTextureShaderBumpTiles::GetColor1() const
{
	return this->GetShaderRecordColor( 8 );
}

void VWTextureShaderBumpTiles::SetColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 8, value );
}

CRGBColor VWTextureShaderBumpTiles::GetColor2() const
{
	return this->GetShaderRecordColor( 11 );
}

void VWTextureShaderBumpTiles::SetColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 11, value );
}

CRGBColor VWTextureShaderBumpTiles::GetColor3() const
{
	return this->GetShaderRecordColor( 14 );
}

void VWTextureShaderBumpTiles::SetColor3(const CRGBColor& value)
{
	this->SetShaderRecordColor( 14, value );
}

bool VWTextureShaderBumpTiles::GetRandomizeColor() const
{
	return this->GetShaderRecordBool( 17 );
}

void VWTextureShaderBumpTiles::SetRandomizeColor(bool value)
{
	this->SetShaderRecordBool( 17, value );
}

double VWTextureShaderBumpTiles::GetGroutWidth() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderBumpTiles::SetGroutWidth(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

double VWTextureShaderBumpTiles::GetBevelWidth() const
{
	return this->GetShaderRecordDouble( 19 );
}

void VWTextureShaderBumpTiles::SetBevelWidth(double value)
{
	this->SetShaderRecordDouble( 19, value );
}

bool VWTextureShaderBumpTiles::GetBevel() const
{
	return this->GetShaderRecordBool( 20 );
}

void VWTextureShaderBumpTiles::SetBevel(bool value)
{
	this->SetShaderRecordBool( 20, value );
}

bool VWTextureShaderBumpTiles::GetHorizontalOrientation() const
{
	return this->GetShaderRecordBool( 21 );
}

void VWTextureShaderBumpTiles::SetHorizontalOrientation(bool value)
{
	this->SetShaderRecordBool( 21, value );
}

double VWTextureShaderBumpTiles::GetGlobalScale() const
{
	return this->GetShaderRecordDouble( 22 );
}

void VWTextureShaderBumpTiles::SetGlobalScale(double value)
{
	this->SetShaderRecordDouble( 22, value );
}

double VWTextureShaderBumpTiles::GetRelativeScaleU() const
{
	return this->GetShaderRecordDouble( 23 );
}

void VWTextureShaderBumpTiles::SetRelativeScaleU(double value)
{
	this->SetShaderRecordDouble( 23, value );
}

double VWTextureShaderBumpTiles::GetRelativeScaleV() const
{
	return this->GetShaderRecordDouble( 24 );
}

void VWTextureShaderBumpTiles::SetRelativeScaleV(double value)
{
	this->SetShaderRecordDouble( 24, value );
}

double VWTextureShaderBumpTiles::GetBumpStrength() const
{
	return this->GetShaderRecordDouble( 25 );
}

void VWTextureShaderBumpTiles::SetBumpStrength(double value)
{
	this->SetShaderRecordDouble( 25, value );
}

double VWTextureShaderBumpTiles::GetDisplacementMaxHeight() const
{
	return this->GetShaderRecordDouble( 26 );
}

void VWTextureShaderBumpTiles::SetDisplacementMaxHeight(double value)
{
	this->SetShaderRecordDouble( 26, value );
}

Sint32 VWTextureShaderBumpTiles::GetDisplacementDetail() const
{
	return this->GetShaderRecordLong( 27 );
}

void VWTextureShaderBumpTiles::SetDisplacementDetail(Sint32 value)
{
	this->SetShaderRecordLong( 27, value );
}

bool VWTextureShaderBumpTiles::GetDisplacementSelfShadow() const
{
	return this->GetShaderRecordBool( 28 );
}

void VWTextureShaderBumpTiles::SetDisplacementSelfShadow(bool value)
{
	this->SetShaderRecordBool( 28, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderBumpBricks::VWTextureShaderBumpBricks(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderBumpBricks::VWTextureShaderBumpBricks(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderBumpBricks::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderBumpBricks::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderBumpBricks::VWTextureShaderBumpBricks(const VWTextureShaderBumpBricks& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderBumpBricks::~VWTextureShaderBumpBricks()
{
	fhObject		= nil;
}

VWTextureShaderBumpBricks& VWTextureShaderBumpBricks::operator=(const VWTextureShaderBumpBricks& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderBumpBricks::CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpBricks& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Bump, kShaderPrototypeBump_Bricks );
	outValue = VWTextureShaderBumpBricks( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderBumpBricks::GetShader(MCObjectHandle hTexture, VWTextureShaderBumpBricks& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Bump );
	bool result = VWTextureShaderBumpBricks::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderBumpBricks( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderBumpBricks::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Bump
			&&	prototype == kShaderPrototypeBump_Bricks;
}

double VWTextureShaderBumpBricks::GetScale() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderBumpBricks::SetScale(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

double VWTextureShaderBumpBricks::GetBrickWidth() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderBumpBricks::SetBrickWidth(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderBumpBricks::GetBrickHeight() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderBumpBricks::SetBrickHeight(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

double VWTextureShaderBumpBricks::GetShift() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderBumpBricks::SetShift(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

Sint32 VWTextureShaderBumpBricks::GetHalfBrickRow() const
{
	return this->GetShaderRecordLong( 8 );
}

void VWTextureShaderBumpBricks::SetHalfBrickRow(Sint32 value)
{
	this->SetShaderRecordLong( 8, value );
}

double VWTextureShaderBumpBricks::GetHalfBrickShift() const
{
	return this->GetShaderRecordDouble( 9 );
}

void VWTextureShaderBumpBricks::SetHalfBrickShift(double value)
{
	this->SetShaderRecordDouble( 9, value );
}

double VWTextureShaderBumpBricks::GetGapSize() const
{
	return this->GetShaderRecordDouble( 10 );
}

void VWTextureShaderBumpBricks::SetGapSize(double value)
{
	this->SetShaderRecordDouble( 10, value );
}

double VWTextureShaderBumpBricks::GetGapNoise() const
{
	return this->GetShaderRecordDouble( 11 );
}

void VWTextureShaderBumpBricks::SetGapNoise(double value)
{
	this->SetShaderRecordDouble( 11, value );
}

double VWTextureShaderBumpBricks::GetBrickHeight1() const
{
	return this->GetShaderRecordDouble( 12 );
}

void VWTextureShaderBumpBricks::SetBrickHeight1(double value)
{
	this->SetShaderRecordDouble( 12, value );
}

double VWTextureShaderBumpBricks::GetBrickHeight2() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderBumpBricks::SetBrickHeight2(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

double VWTextureShaderBumpBricks::GetAltHeight1() const
{
	return this->GetShaderRecordDouble( 14 );
}

void VWTextureShaderBumpBricks::SetAltHeight1(double value)
{
	this->SetShaderRecordDouble( 14, value );
}

double VWTextureShaderBumpBricks::GetAltHeight2() const
{
	return this->GetShaderRecordDouble( 15 );
}

void VWTextureShaderBumpBricks::SetAltHeight2(double value)
{
	this->SetShaderRecordDouble( 15, value );
}

double VWTextureShaderBumpBricks::GetGapHeight1() const
{
	return this->GetShaderRecordDouble( 16 );
}

void VWTextureShaderBumpBricks::SetGapHeight1(double value)
{
	this->SetShaderRecordDouble( 16, value );
}

double VWTextureShaderBumpBricks::GetGapHeight2() const
{
	return this->GetShaderRecordDouble( 17 );
}

void VWTextureShaderBumpBricks::SetGapHeight2(double value)
{
	this->SetShaderRecordDouble( 17, value );
}

double VWTextureShaderBumpBricks::GetContrast() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderBumpBricks::SetContrast(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

Sint32 VWTextureShaderBumpBricks::GetAltColorRow() const
{
	return this->GetShaderRecordLong( 19 );
}

void VWTextureShaderBumpBricks::SetAltColorRow(Sint32 value)
{
	this->SetShaderRecordLong( 19, value );
}

Sint32 VWTextureShaderBumpBricks::GetAltColorColumn() const
{
	return this->GetShaderRecordLong( 20 );
}

void VWTextureShaderBumpBricks::SetAltColorColumn(Sint32 value)
{
	this->SetShaderRecordLong( 20, value );
}

double VWTextureShaderBumpBricks::GetBumpStrength() const
{
	return this->GetShaderRecordDouble( 21 );
}

void VWTextureShaderBumpBricks::SetBumpStrength(double value)
{
	this->SetShaderRecordDouble( 21, value );
}

double VWTextureShaderBumpBricks::GetDisplacementMaxHeight() const
{
	return this->GetShaderRecordDouble( 22 );
}

void VWTextureShaderBumpBricks::SetDisplacementMaxHeight(double value)
{
	this->SetShaderRecordDouble( 22, value );
}

Sint32 VWTextureShaderBumpBricks::GetDisplacementDetail() const
{
	return this->GetShaderRecordLong( 23 );
}

void VWTextureShaderBumpBricks::SetDisplacementDetail(Sint32 value)
{
	this->SetShaderRecordLong( 23, value );
}

bool VWTextureShaderBumpBricks::GetDisplacementSelfShadow() const
{
	return this->GetShaderRecordBool( 24 );
}

void VWTextureShaderBumpBricks::SetDisplacementSelfShadow(bool value)
{
	this->SetShaderRecordBool( 24, value );
}

double VWTextureShaderBumpBricks::GetBricksImageBlend() const
{
	return this->GetShaderRecordDouble( 25 );
}

void VWTextureShaderBumpBricks::SetBricksImageBlend(double value)
{
	this->SetShaderRecordDouble( 25, value );
}

double VWTextureShaderBumpBricks::GetGapImageBlend() const
{
	return this->GetShaderRecordDouble( 26 );
}

void VWTextureShaderBumpBricks::SetGapImageBlend(double value)
{
	this->SetShaderRecordDouble( 26, value );
}

double VWTextureShaderBumpBricks::GetAltBricksImageBlend() const
{
	return this->GetShaderRecordDouble( 27 );
}

void VWTextureShaderBumpBricks::SetAltBricksImageBlend(double value)
{
	this->SetShaderRecordDouble( 27, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderBumpPavement::VWTextureShaderBumpPavement(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderBumpPavement::VWTextureShaderBumpPavement(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderBumpPavement::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderBumpPavement::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderBumpPavement::VWTextureShaderBumpPavement(const VWTextureShaderBumpPavement& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderBumpPavement::~VWTextureShaderBumpPavement()
{
	fhObject		= nil;
}

VWTextureShaderBumpPavement& VWTextureShaderBumpPavement::operator=(const VWTextureShaderBumpPavement& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderBumpPavement::CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpPavement& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Bump, kShaderPrototypeBump_Pavement );
	outValue = VWTextureShaderBumpPavement( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderBumpPavement::GetShader(MCObjectHandle hTexture, VWTextureShaderBumpPavement& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Bump );
	bool result = VWTextureShaderBumpPavement::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderBumpPavement( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderBumpPavement::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Bump
			&&	prototype == kShaderPrototypeBump_Pavement;
}

double VWTextureShaderBumpPavement::GetScale() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderBumpPavement::SetScale(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

double VWTextureShaderBumpPavement::GetGapWidth() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderBumpPavement::SetGapWidth(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderBumpPavement::GetSoftness() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderBumpPavement::SetSoftness(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

double VWTextureShaderBumpPavement::GetStoneHeight1() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderBumpPavement::SetStoneHeight1(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

double VWTextureShaderBumpPavement::GetStoneHeight2() const
{
	return this->GetShaderRecordDouble( 8 );
}

void VWTextureShaderBumpPavement::SetStoneHeight2(double value)
{
	this->SetShaderRecordDouble( 8, value );
}

double VWTextureShaderBumpPavement::GetCoarseMarbling() const
{
	return this->GetShaderRecordDouble( 9 );
}

void VWTextureShaderBumpPavement::SetCoarseMarbling(double value)
{
	this->SetShaderRecordDouble( 9, value );
}

double VWTextureShaderBumpPavement::GetFineMarbling() const
{
	return this->GetShaderRecordDouble( 10 );
}

void VWTextureShaderBumpPavement::SetFineMarbling(double value)
{
	this->SetShaderRecordDouble( 10, value );
}

double VWTextureShaderBumpPavement::GetGapHeight1() const
{
	return this->GetShaderRecordDouble( 11 );
}

void VWTextureShaderBumpPavement::SetGapHeight1(double value)
{
	this->SetShaderRecordDouble( 11, value );
}

double VWTextureShaderBumpPavement::GetGapHeight2() const
{
	return this->GetShaderRecordDouble( 12 );
}

void VWTextureShaderBumpPavement::SetGapHeight2(double value)
{
	this->SetShaderRecordDouble( 12, value );
}

double VWTextureShaderBumpPavement::GetGapGrain() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderBumpPavement::SetGapGrain(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

double VWTextureShaderBumpPavement::GetSmudgeHeight1() const
{
	return this->GetShaderRecordDouble( 14 );
}

void VWTextureShaderBumpPavement::SetSmudgeHeight1(double value)
{
	this->SetShaderRecordDouble( 14, value );
}

double VWTextureShaderBumpPavement::GetSmudgeHeight2() const
{
	return this->GetShaderRecordDouble( 15 );
}

void VWTextureShaderBumpPavement::SetSmudgeHeight2(double value)
{
	this->SetShaderRecordDouble( 15, value );
}

double VWTextureShaderBumpPavement::GetSmudgeAmount() const
{
	return this->GetShaderRecordDouble( 16 );
}

void VWTextureShaderBumpPavement::SetSmudgeAmount(double value)
{
	this->SetShaderRecordDouble( 16, value );
}

double VWTextureShaderBumpPavement::GetSmudgeSize() const
{
	return this->GetShaderRecordDouble( 17 );
}

void VWTextureShaderBumpPavement::SetSmudgeSize(double value)
{
	this->SetShaderRecordDouble( 17, value );
}

double VWTextureShaderBumpPavement::GetBumpStrength() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderBumpPavement::SetBumpStrength(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

double VWTextureShaderBumpPavement::GetDisplacementMaxHeight() const
{
	return this->GetShaderRecordDouble( 19 );
}

void VWTextureShaderBumpPavement::SetDisplacementMaxHeight(double value)
{
	this->SetShaderRecordDouble( 19, value );
}

Sint32 VWTextureShaderBumpPavement::GetDisplacementDetail() const
{
	return this->GetShaderRecordLong( 20 );
}

void VWTextureShaderBumpPavement::SetDisplacementDetail(Sint32 value)
{
	this->SetShaderRecordLong( 20, value );
}

bool VWTextureShaderBumpPavement::GetDisplacementSelfShadow() const
{
	return this->GetShaderRecordBool( 21 );
}

void VWTextureShaderBumpPavement::SetDisplacementSelfShadow(bool value)
{
	this->SetShaderRecordBool( 21, value );
}
