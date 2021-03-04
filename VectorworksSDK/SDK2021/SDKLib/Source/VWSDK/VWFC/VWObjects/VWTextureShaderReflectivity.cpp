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
VWTextureShaderReflectivityImage::VWTextureShaderReflectivityImage(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityImage::VWTextureShaderReflectivityImage(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityImage::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityImage::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityImage::VWTextureShaderReflectivityImage(const VWTextureShaderReflectivityImage& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityImage::~VWTextureShaderReflectivityImage()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityImage& VWTextureShaderReflectivityImage::operator=(const VWTextureShaderReflectivityImage& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityImage::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityImage& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Image );
	outValue = VWTextureShaderReflectivityImage( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityImage::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityImage& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityImage::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityImage( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityImage::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Image;
}

MCObjectHandle VWTextureShaderReflectivityImage::GetImage() const
{
	MCObjectHandle	hExistingTextureBitmap = gSDK->FindAuxObject( fhObject, kTextureBitmapNode );
	MCObjectHandle	hBitmap	= gSDK->FindAuxObject( hExistingTextureBitmap, kPaintNode );
	return hBitmap;
}

void VWTextureShaderReflectivityImage::SetImage(MCObjectHandle& hBitmapObj) const
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

double VWTextureShaderReflectivityImage::GetReflection() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderReflectivityImage::SetReflection(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderReflectivityImage::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderReflectivityImage::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityMirror::VWTextureShaderReflectivityMirror(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityMirror::VWTextureShaderReflectivityMirror(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityMirror::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityMirror::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityMirror::VWTextureShaderReflectivityMirror(const VWTextureShaderReflectivityMirror& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityMirror::~VWTextureShaderReflectivityMirror()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityMirror& VWTextureShaderReflectivityMirror::operator=(const VWTextureShaderReflectivityMirror& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityMirror::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityMirror& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Mirror );
	outValue = VWTextureShaderReflectivityMirror( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityMirror::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityMirror& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityMirror::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityMirror( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityMirror::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Mirror;
}

CRGBColor VWTextureShaderReflectivityMirror::GetColor() const
{
	return this->GetShaderRecordColor( 4 );
}

void VWTextureShaderReflectivityMirror::SetColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 4, value );
}

double VWTextureShaderReflectivityMirror::GetReflection() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderReflectivityMirror::SetReflection(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

double VWTextureShaderReflectivityMirror::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 8 );
}

void VWTextureShaderReflectivityMirror::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 8, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityFresnel::VWTextureShaderReflectivityFresnel(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityFresnel::VWTextureShaderReflectivityFresnel(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityFresnel::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityFresnel::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityFresnel::VWTextureShaderReflectivityFresnel(const VWTextureShaderReflectivityFresnel& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityFresnel::~VWTextureShaderReflectivityFresnel()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityFresnel& VWTextureShaderReflectivityFresnel::operator=(const VWTextureShaderReflectivityFresnel& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityFresnel::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityFresnel& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Fresnel );
	outValue = VWTextureShaderReflectivityFresnel( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityFresnel::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityFresnel& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityFresnel::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityFresnel( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityFresnel::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Fresnel;
}

CRGBColor VWTextureShaderReflectivityFresnel::GetEdgeColor() const
{
	return this->GetShaderRecordColor( 4 );
}

void VWTextureShaderReflectivityFresnel::SetEdgeColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 4, value );
}

CRGBColor VWTextureShaderReflectivityFresnel::GetCenterColor() const
{
	return this->GetShaderRecordColor( 7 );
}

void VWTextureShaderReflectivityFresnel::SetCenterColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 7, value );
}

double VWTextureShaderReflectivityFresnel::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 10 );
}

void VWTextureShaderReflectivityFresnel::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 10, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityNoise::VWTextureShaderReflectivityNoise(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityNoise::VWTextureShaderReflectivityNoise(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityNoise::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityNoise::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityNoise::VWTextureShaderReflectivityNoise(const VWTextureShaderReflectivityNoise& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityNoise::~VWTextureShaderReflectivityNoise()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityNoise& VWTextureShaderReflectivityNoise::operator=(const VWTextureShaderReflectivityNoise& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityNoise::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityNoise& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Noise );
	outValue = VWTextureShaderReflectivityNoise( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityNoise::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityNoise& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityNoise::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityNoise( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityNoise::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Noise;
}

ShaderNoiseType VWTextureShaderReflectivityNoise::GetPattern() const
{
	return (ShaderNoiseType)this->GetShaderRecordLong( 4 );
}

void VWTextureShaderReflectivityNoise::SetPattern(ShaderNoiseType value)
{
	this->SetShaderRecordLong( 4, value );
}

CRGBColor VWTextureShaderReflectivityNoise::GetColor1() const
{
	return this->GetShaderRecordColor( 5 );
}

void VWTextureShaderReflectivityNoise::SetColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 5, value );
}

CRGBColor VWTextureShaderReflectivityNoise::GetColor2() const
{
	return this->GetShaderRecordColor( 8 );
}

void VWTextureShaderReflectivityNoise::SetColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 8, value );
}

bool VWTextureShaderReflectivityNoise::GetNoiseSolid() const
{
	return this->GetShaderRecordBool( 11 );
}

void VWTextureShaderReflectivityNoise::SetNoiseSolid(bool value)
{
	this->SetShaderRecordBool( 11, value );
}

double VWTextureShaderReflectivityNoise::GetGlobalScale() const
{
	return this->GetShaderRecordDouble( 12 );
}

void VWTextureShaderReflectivityNoise::SetGlobalScale(double value)
{
	this->SetShaderRecordDouble( 12, value );
}

double VWTextureShaderReflectivityNoise::GetRelativeUScale() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderReflectivityNoise::SetRelativeUScale(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

double VWTextureShaderReflectivityNoise::GetRelativeVScale() const
{
	return this->GetShaderRecordDouble( 14 );
}

void VWTextureShaderReflectivityNoise::SetRelativeVScale(double value)
{
	this->SetShaderRecordDouble( 14, value );
}

double VWTextureShaderReflectivityNoise::GetRelativeWScale() const
{
	return this->GetShaderRecordDouble( 15 );
}

void VWTextureShaderReflectivityNoise::SetRelativeWScale(double value)
{
	this->SetShaderRecordDouble( 15, value );
}

double VWTextureShaderReflectivityNoise::GetLowClip() const
{
	return this->GetShaderRecordDouble( 16 );
}

void VWTextureShaderReflectivityNoise::SetLowClip(double value)
{
	this->SetShaderRecordDouble( 16, value );
}

double VWTextureShaderReflectivityNoise::GetHighClip() const
{
	return this->GetShaderRecordDouble( 17 );
}

void VWTextureShaderReflectivityNoise::SetHighClip(double value)
{
	this->SetShaderRecordDouble( 17, value );
}

double VWTextureShaderReflectivityNoise::GetDetail() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderReflectivityNoise::SetDetail(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

double VWTextureShaderReflectivityNoise::GetCycles() const
{
	return this->GetShaderRecordDouble( 19 );
}

void VWTextureShaderReflectivityNoise::SetCycles(double value)
{
	this->SetShaderRecordDouble( 19, value );
}

double VWTextureShaderReflectivityNoise::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 20 );
}

void VWTextureShaderReflectivityNoise::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 20, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityTiles::VWTextureShaderReflectivityTiles(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityTiles::VWTextureShaderReflectivityTiles(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityTiles::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityTiles::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityTiles::VWTextureShaderReflectivityTiles(const VWTextureShaderReflectivityTiles& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityTiles::~VWTextureShaderReflectivityTiles()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityTiles& VWTextureShaderReflectivityTiles::operator=(const VWTextureShaderReflectivityTiles& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityTiles::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityTiles& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Tiles );
	outValue = VWTextureShaderReflectivityTiles( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityTiles::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityTiles& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityTiles::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityTiles( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityTiles::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Tiles;
}

ShaderTilesType VWTextureShaderReflectivityTiles::GetPattern() const
{
	return (ShaderTilesType)this->GetShaderRecordLong( 4 );
}

void VWTextureShaderReflectivityTiles::SetPattern(ShaderTilesType value)
{
	this->SetShaderRecordLong( 4, value );
}

CRGBColor VWTextureShaderReflectivityTiles::GetGroutColor() const
{
	return this->GetShaderRecordColor( 5 );
}

void VWTextureShaderReflectivityTiles::SetGroutColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 5, value );
}

CRGBColor VWTextureShaderReflectivityTiles::GetColor1() const
{
	return this->GetShaderRecordColor( 8 );
}

void VWTextureShaderReflectivityTiles::SetColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 8, value );
}

CRGBColor VWTextureShaderReflectivityTiles::GetColor2() const
{
	return this->GetShaderRecordColor( 11 );
}

void VWTextureShaderReflectivityTiles::SetColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 11, value );
}

CRGBColor VWTextureShaderReflectivityTiles::GetColor3() const
{
	return this->GetShaderRecordColor( 14 );
}

void VWTextureShaderReflectivityTiles::SetColor3(const CRGBColor& value)
{
	this->SetShaderRecordColor( 14, value );
}

bool VWTextureShaderReflectivityTiles::GetRandomizeColor() const
{
	return this->GetShaderRecordBool( 17 );
}

void VWTextureShaderReflectivityTiles::SetRandomizeColor(bool value)
{
	this->SetShaderRecordBool( 17, value );
}

double VWTextureShaderReflectivityTiles::GetGroutWidth() const
{
	return this->GetShaderRecordDouble( 18 );
}

void VWTextureShaderReflectivityTiles::SetGroutWidth(double value)
{
	this->SetShaderRecordDouble( 18, value );
}

double VWTextureShaderReflectivityTiles::GetBevelWidth() const
{
	return this->GetShaderRecordDouble( 19 );
}

void VWTextureShaderReflectivityTiles::SetBevelWidth(double value)
{
	this->SetShaderRecordDouble( 19, value );
}

bool VWTextureShaderReflectivityTiles::GetBevel() const
{
	return this->GetShaderRecordBool( 20 );
}

void VWTextureShaderReflectivityTiles::SetBevel(bool value)
{
	this->SetShaderRecordBool( 20, value );
}

bool VWTextureShaderReflectivityTiles::GetHorizontalOrientation() const
{
	return this->GetShaderRecordBool( 21 );
}

void VWTextureShaderReflectivityTiles::SetHorizontalOrientation(bool value)
{
	this->SetShaderRecordBool( 21, value );
}

double VWTextureShaderReflectivityTiles::GetGlobalScale() const
{
	return this->GetShaderRecordDouble( 22 );
}

void VWTextureShaderReflectivityTiles::SetGlobalScale(double value)
{
	this->SetShaderRecordDouble( 22, value );
}

double VWTextureShaderReflectivityTiles::GetRelativeScaleU() const
{
	return this->GetShaderRecordDouble( 23 );
}

void VWTextureShaderReflectivityTiles::SetRelativeScaleU(double value)
{
	this->SetShaderRecordDouble( 23, value );
}

double VWTextureShaderReflectivityTiles::GetRelativeScaleV() const
{
	return this->GetShaderRecordDouble( 24 );
}

void VWTextureShaderReflectivityTiles::SetRelativeScaleV(double value)
{
	this->SetShaderRecordDouble( 24, value );
}

double VWTextureShaderReflectivityTiles::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 25 );
}

void VWTextureShaderReflectivityTiles::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 25, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityPlastic::VWTextureShaderReflectivityPlastic(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityPlastic::VWTextureShaderReflectivityPlastic(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityPlastic::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityPlastic::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityPlastic::VWTextureShaderReflectivityPlastic(const VWTextureShaderReflectivityPlastic& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityPlastic::~VWTextureShaderReflectivityPlastic()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityPlastic& VWTextureShaderReflectivityPlastic::operator=(const VWTextureShaderReflectivityPlastic& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityPlastic::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityPlastic& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Plastic );
	outValue = VWTextureShaderReflectivityPlastic( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityPlastic::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityPlastic& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityPlastic::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityPlastic( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityPlastic::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Plastic;
}

CRGBColor VWTextureShaderReflectivityPlastic::GetColor() const
{
	return this->GetShaderRecordColor( 4 );
}

void VWTextureShaderReflectivityPlastic::SetColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 4, value );
}

double VWTextureShaderReflectivityPlastic::GetBrightness() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderReflectivityPlastic::SetBrightness(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

double VWTextureShaderReflectivityPlastic::GetRoughness() const
{
	return this->GetShaderRecordDouble( 8 );
}

void VWTextureShaderReflectivityPlastic::SetRoughness(double value)
{
	this->SetShaderRecordDouble( 8, value );
}

double VWTextureShaderReflectivityPlastic::GetReflection() const
{
	return this->GetShaderRecordDouble( 9 );
}

void VWTextureShaderReflectivityPlastic::SetReflection(double value)
{
	this->SetShaderRecordDouble( 9, value );
}

double VWTextureShaderReflectivityPlastic::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 10 );
}

void VWTextureShaderReflectivityPlastic::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 10, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityBricks::VWTextureShaderReflectivityBricks(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityBricks::VWTextureShaderReflectivityBricks(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityBricks::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityBricks::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityBricks::VWTextureShaderReflectivityBricks(const VWTextureShaderReflectivityBricks& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityBricks::~VWTextureShaderReflectivityBricks()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityBricks& VWTextureShaderReflectivityBricks::operator=(const VWTextureShaderReflectivityBricks& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityBricks::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityBricks& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Bricks );
	outValue = VWTextureShaderReflectivityBricks( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityBricks::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityBricks& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityBricks::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityBricks( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityBricks::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Bricks;
}

double VWTextureShaderReflectivityBricks::GetScale() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderReflectivityBricks::SetScale(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

double VWTextureShaderReflectivityBricks::GetBrickWidth() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderReflectivityBricks::SetBrickWidth(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderReflectivityBricks::GetBrickHeight() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderReflectivityBricks::SetBrickHeight(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

double VWTextureShaderReflectivityBricks::GetShift() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderReflectivityBricks::SetShift(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

Sint32 VWTextureShaderReflectivityBricks::GetHalfBrickRow() const
{
	return this->GetShaderRecordLong( 8 );
}

void VWTextureShaderReflectivityBricks::SetHalfBrickRow(Sint32 value)
{
	this->SetShaderRecordLong( 8, value );
}

double VWTextureShaderReflectivityBricks::GetHalfBrickShift() const
{
	return this->GetShaderRecordDouble( 9 );
}

void VWTextureShaderReflectivityBricks::SetHalfBrickShift(double value)
{
	this->SetShaderRecordDouble( 9, value );
}

double VWTextureShaderReflectivityBricks::GetGapSize() const
{
	return this->GetShaderRecordDouble( 10 );
}

void VWTextureShaderReflectivityBricks::SetGapSize(double value)
{
	this->SetShaderRecordDouble( 10, value );
}

double VWTextureShaderReflectivityBricks::GetGapNoise() const
{
	return this->GetShaderRecordDouble( 11 );
}

void VWTextureShaderReflectivityBricks::SetGapNoise(double value)
{
	this->SetShaderRecordDouble( 11, value );
}

CRGBColor VWTextureShaderReflectivityBricks::GetBrickColor1() const
{
	return this->GetShaderRecordColor( 12 );
}

void VWTextureShaderReflectivityBricks::SetBrickColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 12, value );
}

CRGBColor VWTextureShaderReflectivityBricks::GetBrickColor2() const
{
	return this->GetShaderRecordColor( 15 );
}

void VWTextureShaderReflectivityBricks::SetBrickColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 15, value );
}

CRGBColor VWTextureShaderReflectivityBricks::GetAltColor1() const
{
	return this->GetShaderRecordColor( 18 );
}

void VWTextureShaderReflectivityBricks::SetAltColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 18, value );
}

CRGBColor VWTextureShaderReflectivityBricks::GetAltColor2() const
{
	return this->GetShaderRecordColor( 21 );
}

void VWTextureShaderReflectivityBricks::SetAltColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 21, value );
}

CRGBColor VWTextureShaderReflectivityBricks::GetGapColor1() const
{
	return this->GetShaderRecordColor( 24 );
}

void VWTextureShaderReflectivityBricks::SetGapColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 24, value );
}

CRGBColor VWTextureShaderReflectivityBricks::GetGapColor2() const
{
	return this->GetShaderRecordColor( 27 );
}

void VWTextureShaderReflectivityBricks::SetGapColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 27, value );
}

double VWTextureShaderReflectivityBricks::GetContrast() const
{
	return this->GetShaderRecordDouble( 30 );
}

void VWTextureShaderReflectivityBricks::SetContrast(double value)
{
	this->SetShaderRecordDouble( 30, value );
}

Sint32 VWTextureShaderReflectivityBricks::GetAltColorRow() const
{
	return this->GetShaderRecordLong( 31 );
}

void VWTextureShaderReflectivityBricks::SetAltColorRow(Sint32 value)
{
	this->SetShaderRecordLong( 31, value );
}

Sint32 VWTextureShaderReflectivityBricks::GetAltColorColumn() const
{
	return this->GetShaderRecordLong( 32 );
}

void VWTextureShaderReflectivityBricks::SetAltColorColumn(Sint32 value)
{
	this->SetShaderRecordLong( 32, value );
}

double VWTextureShaderReflectivityBricks::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 33 );
}

void VWTextureShaderReflectivityBricks::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 33, value );
}

double VWTextureShaderReflectivityBricks::GetBricksImageBlend() const
{
	return this->GetShaderRecordDouble( 34 );
}

void VWTextureShaderReflectivityBricks::SetBricksImageBlend(double value)
{
	this->SetShaderRecordDouble( 34, value );
}

double VWTextureShaderReflectivityBricks::GetGapImageBlend() const
{
	return this->GetShaderRecordDouble( 35 );
}

void VWTextureShaderReflectivityBricks::SetGapImageBlend(double value)
{
	this->SetShaderRecordDouble( 35, value );
}

double VWTextureShaderReflectivityBricks::GetAltBricksImageBlend() const
{
	return this->GetShaderRecordDouble( 36 );
}

void VWTextureShaderReflectivityBricks::SetAltBricksImageBlend(double value)
{
	this->SetShaderRecordDouble( 36, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityPavement::VWTextureShaderReflectivityPavement(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityPavement::VWTextureShaderReflectivityPavement(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityPavement::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityPavement::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityPavement::VWTextureShaderReflectivityPavement(const VWTextureShaderReflectivityPavement& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityPavement::~VWTextureShaderReflectivityPavement()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityPavement& VWTextureShaderReflectivityPavement::operator=(const VWTextureShaderReflectivityPavement& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityPavement::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityPavement& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Pavement );
	outValue = VWTextureShaderReflectivityPavement( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityPavement::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityPavement& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityPavement::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityPavement( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityPavement::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Pavement;
}

double VWTextureShaderReflectivityPavement::GetScale() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderReflectivityPavement::SetScale(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

double VWTextureShaderReflectivityPavement::GetGapWidth() const
{
	return this->GetShaderRecordDouble( 5 );
}

void VWTextureShaderReflectivityPavement::SetGapWidth(double value)
{
	this->SetShaderRecordDouble( 5, value );
}

double VWTextureShaderReflectivityPavement::GetSoftness() const
{
	return this->GetShaderRecordDouble( 6 );
}

void VWTextureShaderReflectivityPavement::SetSoftness(double value)
{
	this->SetShaderRecordDouble( 6, value );
}

CRGBColor VWTextureShaderReflectivityPavement::GetStoneColor1() const
{
	return this->GetShaderRecordColor( 7 );
}

void VWTextureShaderReflectivityPavement::SetStoneColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 7, value );
}

CRGBColor VWTextureShaderReflectivityPavement::GetStoneColor2() const
{
	return this->GetShaderRecordColor( 10 );
}

void VWTextureShaderReflectivityPavement::SetStoneColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 10, value );
}

double VWTextureShaderReflectivityPavement::GetCoarseMarbling() const
{
	return this->GetShaderRecordDouble( 13 );
}

void VWTextureShaderReflectivityPavement::SetCoarseMarbling(double value)
{
	this->SetShaderRecordDouble( 13, value );
}

double VWTextureShaderReflectivityPavement::GetFineMarbling() const
{
	return this->GetShaderRecordDouble( 14 );
}

void VWTextureShaderReflectivityPavement::SetFineMarbling(double value)
{
	this->SetShaderRecordDouble( 14, value );
}

CRGBColor VWTextureShaderReflectivityPavement::GetGapColor1() const
{
	return this->GetShaderRecordColor( 15 );
}

void VWTextureShaderReflectivityPavement::SetGapColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 15, value );
}

CRGBColor VWTextureShaderReflectivityPavement::GetGapColor2() const
{
	return this->GetShaderRecordColor( 18 );
}

void VWTextureShaderReflectivityPavement::SetGapColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 18, value );
}

double VWTextureShaderReflectivityPavement::GetGapGrain() const
{
	return this->GetShaderRecordDouble( 21 );
}

void VWTextureShaderReflectivityPavement::SetGapGrain(double value)
{
	this->SetShaderRecordDouble( 21, value );
}

CRGBColor VWTextureShaderReflectivityPavement::GetSmudgeColor1() const
{
	return this->GetShaderRecordColor( 22 );
}

void VWTextureShaderReflectivityPavement::SetSmudgeColor1(const CRGBColor& value)
{
	this->SetShaderRecordColor( 22, value );
}

CRGBColor VWTextureShaderReflectivityPavement::GetSmudgeColor2() const
{
	return this->GetShaderRecordColor( 25 );
}

void VWTextureShaderReflectivityPavement::SetSmudgeColor2(const CRGBColor& value)
{
	this->SetShaderRecordColor( 25, value );
}

double VWTextureShaderReflectivityPavement::GetSmudgeAmount() const
{
	return this->GetShaderRecordDouble( 28 );
}

void VWTextureShaderReflectivityPavement::SetSmudgeAmount(double value)
{
	this->SetShaderRecordDouble( 28, value );
}

double VWTextureShaderReflectivityPavement::GetSmudgeSize() const
{
	return this->GetShaderRecordDouble( 29 );
}

void VWTextureShaderReflectivityPavement::SetSmudgeSize(double value)
{
	this->SetShaderRecordDouble( 29, value );
}

double VWTextureShaderReflectivityPavement::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 30 );
}

void VWTextureShaderReflectivityPavement::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 30, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityGlow::VWTextureShaderReflectivityGlow(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityGlow::VWTextureShaderReflectivityGlow(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityGlow::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityGlow::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityGlow::VWTextureShaderReflectivityGlow(const VWTextureShaderReflectivityGlow& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityGlow::~VWTextureShaderReflectivityGlow()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityGlow& VWTextureShaderReflectivityGlow::operator=(const VWTextureShaderReflectivityGlow& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityGlow::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityGlow& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Glow );
	outValue = VWTextureShaderReflectivityGlow( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityGlow::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityGlow& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityGlow::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityGlow( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityGlow::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Glow;
}

double VWTextureShaderReflectivityGlow::GetGlowBrightness() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderReflectivityGlow::SetGlowBrightness(double value)
{
	this->SetShaderRecordDouble( 4, value );
}

bool VWTextureShaderReflectivityGlow::GetEmitLight() const
{
	return this->GetShaderRecordBool( 5 );
}

void VWTextureShaderReflectivityGlow::SetEmitLight(bool value)
{
	this->SetShaderRecordBool( 5, value );
}

bool VWTextureShaderReflectivityGlow::GetAddMatteReflectivity() const
{
	return this->GetShaderRecordBool( 6 );
}

void VWTextureShaderReflectivityGlow::SetAddMatteReflectivity(bool value)
{
	this->SetShaderRecordBool( 6, value );
}

double VWTextureShaderReflectivityGlow::GetReflection() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderReflectivityGlow::SetReflection(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

double VWTextureShaderReflectivityGlow::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 8 );
}

void VWTextureShaderReflectivityGlow::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 8, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityBacklit::VWTextureShaderReflectivityBacklit(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityBacklit::VWTextureShaderReflectivityBacklit(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityBacklit::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityBacklit::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityBacklit::VWTextureShaderReflectivityBacklit(const VWTextureShaderReflectivityBacklit& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityBacklit::~VWTextureShaderReflectivityBacklit()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityBacklit& VWTextureShaderReflectivityBacklit::operator=(const VWTextureShaderReflectivityBacklit& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityBacklit::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityBacklit& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Backlit );
	outValue = VWTextureShaderReflectivityBacklit( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityBacklit::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityBacklit& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityBacklit::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityBacklit( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityBacklit::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Backlit;
}

CRGBColor VWTextureShaderReflectivityBacklit::GetColor() const
{
	return this->GetShaderRecordColor( 4 );
}

void VWTextureShaderReflectivityBacklit::SetColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 4, value );
}

double VWTextureShaderReflectivityBacklit::GetBrightness() const
{
	return this->GetShaderRecordDouble( 7 );
}

void VWTextureShaderReflectivityBacklit::SetBrightness(double value)
{
	this->SetShaderRecordDouble( 7, value );
}

double VWTextureShaderReflectivityBacklit::GetReflection() const
{
	return this->GetShaderRecordDouble( 8 );
}

void VWTextureShaderReflectivityBacklit::SetReflection(double value)
{
	this->SetShaderRecordDouble( 8, value );
}

double VWTextureShaderReflectivityBacklit::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 9 );
}

void VWTextureShaderReflectivityBacklit::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 9, value );
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
VWTextureShaderReflectivityAnisotropic::VWTextureShaderReflectivityAnisotropic(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderReflectivityAnisotropic::VWTextureShaderReflectivityAnisotropic(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderReflectivityAnisotropic::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderReflectivityAnisotropic::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderReflectivityAnisotropic::VWTextureShaderReflectivityAnisotropic(const VWTextureShaderReflectivityAnisotropic& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderReflectivityAnisotropic::~VWTextureShaderReflectivityAnisotropic()
{
	fhObject		= nil;
}

VWTextureShaderReflectivityAnisotropic& VWTextureShaderReflectivityAnisotropic::operator=(const VWTextureShaderReflectivityAnisotropic& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderReflectivityAnisotropic::CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityAnisotropic& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Reflectivity, kShaderPrototypeReflectivity_Anisotropic );
	outValue = VWTextureShaderReflectivityAnisotropic( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderReflectivityAnisotropic::GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityAnisotropic& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Reflectivity );
	bool result = VWTextureShaderReflectivityAnisotropic::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderReflectivityAnisotropic( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderReflectivityAnisotropic::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Reflectivity
			&&	prototype == kShaderPrototypeReflectivity_Anisotropic;
}

CRGBColor VWTextureShaderReflectivityAnisotropic::GetColor() const
{
	return this->GetShaderRecordColor( 4 );
}

void VWTextureShaderReflectivityAnisotropic::SetColor(const CRGBColor& value)
{
	this->SetShaderRecordColor( 4, value );
}

VWTextureShaderReflectivityAnisotropic::EPattern VWTextureShaderReflectivityAnisotropic::GetPattern() const
{
	return (EPattern)this->GetShaderRecordLong( 7 );
}

void VWTextureShaderReflectivityAnisotropic::SetPattern(EPattern value)
{
	this->SetShaderRecordLong( 7, value );
}

double VWTextureShaderReflectivityAnisotropic::GetReflection() const
{
	return this->GetShaderRecordDouble( 8 );
}

void VWTextureShaderReflectivityAnisotropic::SetReflection(double value)
{
	this->SetShaderRecordDouble( 8, value );
}

double VWTextureShaderReflectivityAnisotropic::GetBlurriness() const
{
	return this->GetShaderRecordDouble( 9 );
}

void VWTextureShaderReflectivityAnisotropic::SetBlurriness(double value)
{
	this->SetShaderRecordDouble( 9, value );
}
