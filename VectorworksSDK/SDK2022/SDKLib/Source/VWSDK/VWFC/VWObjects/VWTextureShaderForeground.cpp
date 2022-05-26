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
VWTextureShaderForegroundLitFog::VWTextureShaderForegroundLitFog(VWTextureObj& textureObj)
{
	if ( textureObj.GetShader( *this ) == false )
	{
		textureObj.CreateShader( *this );
		VWFC_ASSERT( fhObject != nil );
	}
}

VWTextureShaderForegroundLitFog::VWTextureShaderForegroundLitFog(MCObjectHandle hShaderRecord)
{
	VWFC_ASSERT( VWTextureShaderForegroundLitFog::IsShaderRecordObject( hShaderRecord ) );
	if ( ! VWTextureShaderForegroundLitFog::IsShaderRecordObject( hShaderRecord ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hShaderRecord;
	VWFC_ASSERT( fhObject != nil );
}

VWTextureShaderForegroundLitFog::VWTextureShaderForegroundLitFog(const VWTextureShaderForegroundLitFog& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderForegroundLitFog::~VWTextureShaderForegroundLitFog()
{
	fhObject		= nil;
}

VWTextureShaderForegroundLitFog& VWTextureShaderForegroundLitFog::operator=(const VWTextureShaderForegroundLitFog& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWTextureShaderForegroundLitFog::CreateShader(MCObjectHandle hTexture, VWTextureShaderForegroundLitFog& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->CreateShaderRecord( hTexture, kShaderFamily_Foreground, kShaderPrototypeForeground_LitFog );
	outValue = VWTextureShaderForegroundLitFog( hShaderRecObj );
	return true;
}

/*static*/ bool VWTextureShaderForegroundLitFog::GetShader(MCObjectHandle hTexture, VWTextureShaderForegroundLitFog& outValue)
{
	MCObjectHandle	hShaderRecObj = gSDK->GetShaderRecord( hTexture, kShaderFamily_Foreground );
	bool result = VWTextureShaderForegroundLitFog::IsShaderRecordObject( hShaderRecObj );
	if ( result )
	{
		outValue = VWTextureShaderForegroundLitFog( hShaderRecObj );
	}

	return result;
}

bool VWTextureShaderForegroundLitFog::IsShaderRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	
	ShaderFamily	family;
	Sint32			prototype;
	return		type == kRecordNode
			&&	VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( hObj, family, prototype )
			&&	family == kShaderFamily_Foreground
			&&	prototype == kShaderPrototypeForeground_LitFog;
}

double VWTextureShaderForegroundLitFog::GetPercent() const
{
	return this->GetShaderRecordDouble( 4 );
}

void VWTextureShaderForegroundLitFog::SetPercent(double value)
{
	 this->SetShaderRecordDouble( 4, value );
}

bool VWTextureShaderForegroundLitFog::GetSmoothNoisy() const
{
	return this->GetShaderRecordBool( 5 );
}

void VWTextureShaderForegroundLitFog::SetSmoothNoisy(bool value)
{
	this->SetShaderRecordBool( 5, value );
}

bool VWTextureShaderForegroundLitFog::GetRcvShadow() const
{
	return this->GetShaderRecordBool( 6 );
}

void VWTextureShaderForegroundLitFog::SetRcvShadow(bool value)
{
	this->SetShaderRecordBool( 6, value );
}

