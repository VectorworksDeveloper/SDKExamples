//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC;
using namespace VWFC::VWObjects;
using namespace VWFC::Tools;

VWClassAttr::VWClassAttr(InternalIndex classIndex)
{
	fClassIndex	= classIndex;
}

VWClassAttr::~VWClassAttr()
{
}

CRGBColor VWClassAttr::GetPenForeColor() const
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	ObjectColorType		color;
	::GS_GetClColor( gCBP, fClassIndex, color );
#if _MINICAD_
	return CRGBColor( color.v0.penFore );
#else
	return CRGBColor( color.penFore );
#endif
}

CRGBColor VWClassAttr::GetPenBackColor() const
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	ObjectColorType		color;
	::GS_GetClColor( gCBP, fClassIndex, color );
#if _MINICAD_
	return CRGBColor( color.v0.penBack );
#else
	return CRGBColor( color.penBack );
#endif
}

void VWClassAttr::SetPenForeColor(const CRGBColor& clr)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	ObjectColorType		color;
	::GS_GetClColor( gCBP, fClassIndex, color );
#if _MINICAD_
	color.v0.penFore	= clr.GetColorIndex();
#else
	color.penFore		= clr.GetColorIndex();
#endif
	::GS_SetClColor( gCBP, fClassIndex, color );
}

void VWClassAttr::SetPenBackColor(const CRGBColor& clr)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	ObjectColorType		color;
	::GS_GetClColor( gCBP, fClassIndex, color );
#if _MINICAD_
	color.v0.penBack	= clr.GetColorIndex();
#else
	color.penBack		= clr.GetColorIndex();
#endif
	::GS_SetClColor( gCBP, fClassIndex, color );
}

CRGBColor VWClassAttr::GetFillForeColor() const
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	ObjectColorType		color;
	::GS_GetClColor( gCBP, fClassIndex, color );
#if _MINICAD_
	return CRGBColor( color.v0.fillFore );
#else
	return CRGBColor( color.fillFore );
#endif
}

CRGBColor VWClassAttr::GetFillBackColor() const
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	ObjectColorType		color;
	::GS_GetClColor( gCBP, fClassIndex, color );
#if _MINICAD_
	return CRGBColor( color.v0.fillBack );
#else
	return CRGBColor( color.fillBack );
#endif
}

void VWClassAttr::SetFillForeColor(const CRGBColor& clr)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	ObjectColorType		color;
	::GS_GetClColor( gCBP, fClassIndex, color );
#if _MINICAD_
	color.v0.fillFore	= clr.GetColorIndex();
#else
	color.fillFore		= clr.GetColorIndex();
#endif
	::GS_SetClColor( gCBP, fClassIndex, color );
}

void VWClassAttr::SetFillBackColor(const CRGBColor& clr)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	ObjectColorType		color;
	::GS_GetClColor( gCBP, fClassIndex, color );
#if _MINICAD_
	color.v0.fillBack	= clr.GetColorIndex();
#else
	color.fillBack		= clr.GetColorIndex();
#endif
	::GS_SetClColor( gCBP, fClassIndex, color );
}

short VWClassAttr::GetLineWeightInMils() const
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	return ::GS_GetClLineWeight( gCBP, fClassIndex );
}

void VWClassAttr::SetLineWeightInMils(short mils)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	::GS_SetClLineWeight( gCBP, fClassIndex, mils );
}

MarkerType VWClassAttr::GetMarker(short& size, short& angle) const
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	MarkerType	style;
	::GS_GetClMarker( gCBP, fClassIndex, style, size, angle );
	return style;
}

void VWClassAttr::SetMarker(MarkerType marker, short size, short angle)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	::GS_SetClMarker( gCBP, fClassIndex, (MarkerType) marker, size, angle );
}

VWPattern VWClassAttr::GetPenPattern() const
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	return VWPattern( ::gSDK->GetClPenPatN( fClassIndex ) , false);
}

void VWClassAttr::SetPenPattern(const VWPattern& pattern)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	gSDK->SetClPenPatN(fClassIndex, pattern );
}

void VWClassAttr::SetPenPattern(const InternalIndex& dashIndex) // legacy function but changed to take InternalIndex
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
#if BUG
	if (dashIndex < 0) {
		auto h = gSDK->InternalIndexToHandle(-dashIndex);
		if (h == NULL || gSDK->GetObjectTypeN(h) != 96)
			DSTOP((kMLieblein, "Invalid dash style specified"));
	}
#endif
	gSDK->SetClPenPatN(fClassIndex, dashIndex );
}

VWPattern VWClassAttr::GetFillPattern() const
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	return VWPattern( ::GS_GetClFillPat( gCBP, fClassIndex ), true );
}

void VWClassAttr::SetFillPattern(const VWPattern& pattern)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	::GS_SetClFillPat( gCBP, fClassIndex, pattern );
}


void VWClassAttr::SetUseGeneralTexture(bool useTexture)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	::GS_SetClUseTexture( gCBP, fClassIndex, useTexture );
}

void VWClassAttr::SetGeneralTexture(InternalIndex texture)
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	::GS_SetClGenTexture( gCBP, fClassIndex, texture );
}

InternalIndex VWClassAttr::GetGeneralTexture() const
{
	VWFC_ASSERT( VWClass::IsValidClassIndex( fClassIndex ) );
	return ::GS_GetClGenTexture( gCBP, fClassIndex );
}





