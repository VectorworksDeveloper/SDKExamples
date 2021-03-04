//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWLightObj::VWLightObj(const VWPoint3D& position, EVWLightKind kind, bool isOn, double brightness, const CRGBColor& color, bool castShadows)
{
	WorldPt3	ptColor;
	ptColor.x	= (double) color.GetRed() / 255.0;
	ptColor.y	= (double) color.GetGreen() / 255.0;
	ptColor.z	= (double) color.GetBlue() / 255.0;

	fhObject = gSDK->CreateLightN( position, kind, isOn, brightness, ptColor, castShadows );
	VWFC_ASSERT( fhObject != nil );
}

VWLightObj::VWLightObj(MCObjectHandle hLight)
{
	VWFC_ASSERT( VWLightObj::IsLightObject( hLight ) );
//	if ( ! VWLightObj::IsLine2DObject( hLine2D ) )
//		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hLight;
	VWFC_ASSERT( fhObject != nil );
}

VWLightObj::VWLightObj(const VWLightObj& src)
{
	fhObject	= src.fhObject;
}

VWLightObj::~VWLightObj()
{
	fhObject		= nil;
}

VWLightObj& VWLightObj::operator=(const VWLightObj& src)
{
	fhObject	= src.fhObject;
	return *this;
}

bool VWLightObj::IsLightObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kLightNode;
}

bool VWLightObj::GetIsOn() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightIsOn, value );

	Boolean result;
	return value.GetBoolean( result ) && result;
}


void VWLightObj::SetIsOn(bool inValue)
{
	TVariableBlock	value( (Boolean) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightIsOn, value );
	const CBSignedShort kKludgeRefreshVisualizationPalette = 4305;
	gSDK->Kludge(kKludgeRefreshVisualizationPalette, NULL, NULL);
}

double VWLightObj::GetBrightness() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightBrightness, value );

	Real64	result;
	return value.GetReal64(result) ? result : 0.0;
}

void VWLightObj::SetBrightness(double inValue)
{
	TVariableBlock	value( (Real64) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightBrightness, value );
}

CRGBColor VWLightObj::GetColor() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightColor, value );

	CRGBColor	result;

	WorldPt3	ptColor;
	if ( value.GetWorldPt3( ptColor ) )
	{
		Uint8	r	= (Uint8)( ptColor.x * 255.0 );
		Uint8	g	= (Uint8)( ptColor.y * 255.0 );
		Uint8	b	= (Uint8)( ptColor.z * 255.0 );
		result.SetColor( r, g, b );
	}

	return result;
}

void VWLightObj::SetColor(const CRGBColor& color)
{
	WorldPt3	ptColor;
	ptColor.x	= (double) color.GetRed() / 255.0;
	ptColor.y	= (double) color.GetGreen() / 255.0;
	ptColor.z	= (double) color.GetBlue() / 255.0;

	TVariableBlock	value( ptColor );
	gSDK->SetObjectVariable( fhObject, ovLightColor, value );
}

bool VWLightObj::GetCastShadows() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightCastShadows, value );

	Boolean result;
	return value.GetBoolean( result ) && result;
}

void VWLightObj::SetCastShadows(bool inValue)
{
	TVariableBlock	value( (Boolean) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightCastShadows, value );
}

VWPoint3D VWLightObj::GetPosition() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightPosition, value );

	VWPoint3D	result;

	WorldPt3	pt3;
	if ( value.GetWorldPt3( pt3 ) )
		result = pt3;

	return result;
}

void VWLightObj::SetPosition(const VWPoint3D& pos)
{
	TVariableBlock	value( (const WorldPt3&) pos );
	gSDK->SetObjectVariable( fhObject, ovLightPosition, value );
}

EVWLightKind VWLightObj::GetKind() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightKind, value );

	EVWLightKind	result = eWLightKind_Directional;

	Sint16	selValue;
	if ( value.GetSint16( selValue ) )
	{
		switch ( selValue )
		{
			default:
			case kDirectionalLight	:  result = eWLightKind_Directional	; break;
			case kPointLight		:  result = eWLightKind_Point		; break;
			case kSpotLight			:  result = eWLightKind_Spot		; break;
		}
	}

	return result;
}

void VWLightObj::SetKind(EVWLightKind inValue)
{
	Sint16	selValue;
	switch ( inValue )
	{
		default:
		case eWLightKind_Directional	: selValue = kDirectionalLight	; break;
		case eWLightKind_Point			: selValue = kPointLight		; break;
		case eWLightKind_Spot			: selValue = kSpotLight			; break;
	}

	TVariableBlock	value( selValue );
	gSDK->SetObjectVariable( fhObject, ovLightKind, value );
}


VWPoint3D VWLightObj::GetDirectionVector() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightDirectionVector, value );

	VWPoint3D	result;

	WorldPt3	pt3;
	if ( value.GetWorldPt3( pt3 ) )
		result = pt3;

	return result;
}

void VWLightObj::SetDirectionVector(const VWPoint3D& dir)
{
	TVariableBlock	value( (const WorldPt3&) dir );
	gSDK->SetObjectVariable( fhObject, ovLightDirectionVector, value );
}

double VWLightObj::GetDirectionAngleVertical() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightDirectionVertAngle, value );

	Real64	result;
	return value.GetReal64(result) ? result : 0.0;
}

void VWLightObj::SetDirectionAngleVertical(double inValue)
{
	TVariableBlock	value( (Real64) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightDirectionVertAngle, value );
}

double VWLightObj::GetDirectionAngleHorizontal() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightDirectionHorizAngle, value );

	Real64	result;
	return value.GetReal64(result) ? result : 0.0;
}

void VWLightObj::SetDirectionAngleHorizontal(double inValue)
{
	TVariableBlock	value( (Real64) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightDirectionHorizAngle, value );
}

EVWLightDistanceFalloff VWLightObj::GetDistanceFalloff() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightDistanceFalloff, value );

	EVWLightDistanceFalloff	result = eVWLightDistanceFalloff_None;

	Sint16	selValue;
	if ( value.GetSint16( selValue ) )
	{
		switch ( selValue )
		{
			default:
			case kLightNoFalloff				:  result = eVWLightDistanceFalloff_None			; break;
			case kLightInverseDistance			:  result = eVWLightDistanceFalloff_Inverse			; break;
			case kLightInverseDistanceSquared	:  result = eVWLightDistanceFalloff_InverseSquared	; break;
		}
	}

	return result;
}

void VWLightObj::SetDistanceFalloff(EVWLightDistanceFalloff inValue)
{
	Sint16	selValue;
	switch ( inValue )
	{
		default:
		case eVWLightDistanceFalloff_None			: selValue = kLightNoFalloff				; break;
		case eVWLightDistanceFalloff_Inverse		: selValue = kLightInverseDistance			; break;
		case eVWLightDistanceFalloff_InverseSquared	: selValue = kLightInverseDistanceSquared	; break;
	}

	TVariableBlock	value( selValue );
	gSDK->SetObjectVariable( fhObject, ovLightDistanceFalloff, value );
}

EVWLightAngularFalloff VWLightObj::GetAngularFalloff() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightAngularFalloff, value );

	EVWLightAngularFalloff	result = eVWLightAngularFalloff_None;

	Sint16	selValue;
	if ( value.GetSint16( selValue ) )
	{
		switch ( selValue )
		{
			default:
			case kLightNoFalloff	:  result = eVWLightAngularFalloff_None			; break;
			case kLightLinear		:  result = eVWLightAngularFalloff_Linear		; break;
			case kLightExponential	:  result = eVWLightAngularFalloff_Exponential	; break;
			case kLightCosine		:  result = eVWLightAngularFalloff_Cosine		; break;
		}
	}

	return result;
}

void VWLightObj::SetAngularFalloff(EVWLightAngularFalloff inValue)
{
	Sint16	selValue;
	switch ( inValue )
	{
		default:
		case eVWLightAngularFalloff_None		: selValue = kLightNoFalloff		; break;
		case eVWLightAngularFalloff_Linear		: selValue = kLightLinear			; break;
		case eVWLightAngularFalloff_Exponential	: selValue = kLightExponential		; break;
		case eVWLightAngularFalloff_Cosine		: selValue = kLightCosine			; break;
	}

	TVariableBlock	value( selValue );
	gSDK->SetObjectVariable( fhObject, ovLightAngularFalloff, value );
}

double VWLightObj::GetSpread() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightSpread, value );

	Real64	result;
	return value.GetReal64(result) ? VWFC::Math::MathUtils::Rad2Deg( result ) : 0.0;
}

void VWLightObj::SetSpread(double degValue)
{
	TVariableBlock	value( (Real64) VWFC::Math::MathUtils::Deg2Rad( degValue ) );
	gSDK->SetObjectVariable( fhObject, ovLightSpread, value );
}

double VWLightObj::GetBeam() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightBeam, value );

	Real64	result;
	return value.GetReal64(result) ? VWFC::Math::MathUtils::Rad2Deg( result ) : 0.0;
}

void VWLightObj::SetBeam(double degValue)
{
	TVariableBlock	value( (Real64) VWFC::Math::MathUtils::Deg2Rad( degValue ) );
	gSDK->SetObjectVariable( fhObject, ovLightBeam, value );
}

bool VWLightObj::GetLitFog() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightLitFog, value );

	Boolean result;
	return value.GetBoolean( result ) && result;
}

void VWLightObj::SetLitFog(bool inValue)
{
	TVariableBlock	value( (Boolean) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightLitFog, value );
}

bool VWLightObj::GetSoftShadows() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightSoftShadows, value );

	Boolean result;
	return value.GetBoolean( result ) && result;
}

void VWLightObj::SetSoftShadows(bool inValue)
{
	TVariableBlock	value( (Boolean) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightSoftShadows, value );
}

bool VWLightObj::GetUseEmitter() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightUseEmitter, value );

	Boolean result;
	return value.GetBoolean( result ) && result;
}

void VWLightObj::SetUseEmitter( bool inValue )
{
	TVariableBlock	value( (Boolean) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightUseEmitter, value );
}

double VWLightObj::GetEmitterBrightness() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightEmitterBrightness, value );

	Real64	result;
	return value.GetReal64( result ) ? result : 0.0;
}

void VWLightObj::SetEmitterBrightness( double inValue )
{
	TVariableBlock	value( (Real64) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightEmitterBrightness, value );
}

EVWLightBrightnessUnit VWLightObj::GetBrightnessUnit() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightBrightnessUnit, value );

	Sint16	result;
	return value.GetSint16( result ) ? (EVWLightBrightnessUnit) result : EVWLightBrightnessUnit::eVWLightBrightnessUnit_Lumens;
}

void VWLightObj::SetBrightnessUnit( EVWLightBrightnessUnit inValue )
{
	TVariableBlock	value( (Sint16) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightEmitterBrightness, value );
}

bool VWLightObj::GetUseTemperature() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightUseTemperature, value );

	Boolean result;
	return value.GetBoolean( result ) && result;
}

void VWLightObj::SetUseTemperature( bool inValue )
{
	TVariableBlock	value( (Boolean) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightUseTemperature, value );
}

double VWLightObj::GetTemperature() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightTemperature, value );

	Real64	result;
	return value.GetReal64( result ) ? result : 0.0;
}

void VWLightObj::SetTemperature( double inValue )
{
	TVariableBlock	value( (Real64) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightTemperature, value );
}

bool VWLightObj::GetCausticOnly() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightCausticOnly, value );

	Boolean result;
	return value.GetBoolean( result ) && result;
}

void VWLightObj::SetCausticOnly( bool inValue )
{
	TVariableBlock	value( (Boolean) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightCausticOnly, value );
}

EVWLightCausticPhotons VWLightObj::GetCausticPhotons() const
{
	TVariableBlock	value;
	gSDK->GetObjectVariable( fhObject, ovLightCausticPhotons, value );

	Uint32	result;
	return value.GetUint32( result ) ? (EVWLightCausticPhotons) result : EVWLightCausticPhotons::eVWLightCausticNone;
}

void VWLightObj::SetCausticPhotons( EVWLightCausticPhotons inValue )
{
	TVariableBlock	value( (Uint32) inValue );
	gSDK->SetObjectVariable( fhObject, ovLightCausticPhotons, value );
}