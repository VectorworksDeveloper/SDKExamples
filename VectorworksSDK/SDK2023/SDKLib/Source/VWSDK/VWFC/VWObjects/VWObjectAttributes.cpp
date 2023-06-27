//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC;
using namespace VWFC::Math;
using namespace VWFC::VWObjects;
using namespace VWFC::Tools;

VWObjectAttr::VWObjectAttr()
{
	fhObject		= NULL;
}

VWObjectAttr::VWObjectAttr(MCObjectHandle h)
{
	fhObject		= h;
}

VWObjectAttr::VWObjectAttr(const VWObjectAttr& src)
{
	this->operator = ( src );
}

VWObjectAttr::~VWObjectAttr()
{
}

VWObjectAttr& VWObjectAttr::operator=(const VWObjectAttr& src)
{
	fhObject	= src.fhObject;
	return *this;
}

void VWObjectAttr::ApplyToObject(MCObjectHandle h) const
{
	VWObjectAttr	destObjAttr( h );

	// it is very important first to set all the properties
	// and then to apply classing
	// setting some attributes might revert classing
	ObjectColorType colors;
	gSDK->GetColor( fhObject, colors );
	gSDK->SetColor( h, colors );
	destObjAttr.SetPenPattern( this->GetPenPattern() );
	destObjAttr.SetFillPattern( this->GetFillPattern() );
	destObjAttr.SetLineWeightInMils( this->GetLineWeightInMils() );
	destObjAttr.SetOpacity( this->GetOpacity() );

	if ( this->GetPenColorByClass() ) {
		destObjAttr.SetPenColorByClass();
	}

	if ( this->GetPenPatternByClass() ) {
		destObjAttr.SetPenPatternByClass();
	}

	if ( this->GetFillColorByClass() ) {
		destObjAttr.SetFillColorByClass();
	}

	if ( this->GetFillPatternByClass() ) {
		destObjAttr.SetFillPatternByClass();
	}

	if ( this->GetLineWeightByClass() ) {
		destObjAttr.SetLineWeightByClass();
	}

	if ( this->GetOpacityByClass() ) {
		destObjAttr.SetOpacityByClass();
	}
}

void VWObjectAttr::SetPenNone()
{
	if ( fhObject ) {
		gSDK->SetPenPatN( fhObject, 0 );

		if ( gSDK->GetObjectTypeN( fhObject ) == kGroupNode ) {
			for(	VWObjectIterator it = VWGroupObj( fhObject ).GetFirstMemberIterator();
					*it;
					++it)
			{
				VWObjectAttr( *it ).SetPenNone();
			}
		}
	}
	else {
		gSDK->SetDefaultPenPatN( 0 );
	}
}

bool VWObjectAttr::GetPenNone() const
{
	bool result = false;
	if ( fhObject )
	{
		result = (gSDK->GetPenPatN( fhObject ) == 0);
	}
	else
	{
		result = (gSDK->GetDefaultPenPatN() == 0);
	}
	return result;
}

void VWObjectAttr::SetPenSolid()
{
	if ( fhObject ) {
		gSDK->SetPenPatN( fhObject, 2 );

		if ( gSDK->GetObjectTypeN( fhObject ) == kGroupNode ) {
			for(	VWObjectIterator it = VWGroupObj( fhObject ).GetFirstMemberIterator();
					*it;
					++it)
			{
				VWObjectAttr( *it ).SetPenSolid();
			}
		}
	}
	else {
		gSDK->SetDefaultPenPatN( 2 );
	}
}

CRGBColor VWObjectAttr::GetPenForeColor() const
{
	ObjectColorType		color;
	if ( fhObject ) {
		gSDK->GetColor( fhObject, color );
	}
	else {
		gSDK->GetDefaultColors( color );
	}

#if _MINICAD_
	return CRGBColor( color.v0.penFore );
#else
	return CRGBColor( color.penFore );
#endif
}

CRGBColor VWObjectAttr::GetPenBackColor() const
{
	ObjectColorType		color;
	if ( fhObject ) {
		gSDK->GetColor( fhObject, color );
	}
	else {
		gSDK->GetDefaultColors( color );
	}

#if _MINICAD_
	return CRGBColor( color.v0.penBack );
#else
	return CRGBColor( color.penBack );
#endif
}

void VWObjectAttr::SetPenForeColor(const CRGBColor& clr)
{
	ObjectColorType		color;
	if ( fhObject ) {
		gSDK->GetColor( fhObject, color );
	}
	else {
		gSDK->GetDefaultColors( color );
	}

#if _MINICAD_
	color.v0.penFore	= clr.GetColorIndex();
#else
	color.penFore		= clr.GetColorIndex();
#endif

	if ( fhObject ) {
		gSDK->SetColor( fhObject, color );
	}
	else {
		gSDK->SetDefaultColors( color );
	}
}

void VWObjectAttr::SetPenBackColor(const CRGBColor& clr)
{
	ObjectColorType		color;
	if ( fhObject ) {
		gSDK->GetColor( fhObject, color );
	}
	else {
		gSDK->GetDefaultColors( color );
	}

#if _MINICAD_
	color.v0.penBack	= clr.GetColorIndex();
#else
	color.penBack		= clr.GetColorIndex();
#endif

	if ( fhObject ) {
		gSDK->SetColor( fhObject, color );
	}
	else {
		gSDK->SetDefaultColors( color );
	}
}

bool VWObjectAttr::GetPenColorByClass() const
{
	if ( fhObject ) {
		return gSDK->GetPColorsByClass( fhObject ) ? true : false;
	}
	else {
		return gSDK->GetDefaultPColorsByClass() ? true : false;
	}
}

void VWObjectAttr::SetPenColorByClass()
{
	if ( fhObject ) {
		gSDK->SetPColorsByClass( fhObject );
	}
	else {
		gSDK->SetDefaultPColorsByClass();
	}
}

VWPattern VWObjectAttr::GetPenPattern() const
{
	if ( fhObject ) {
		return VWPattern( gSDK->GetPenPatN( fhObject ) , false);
	}
	else {
		return VWPattern( gSDK->GetDefaultPenPatN() ,false );
	}
}

void VWObjectAttr::SetPenPattern(const VWPattern& pattern)
{
	if ( fhObject ) {
		gSDK->SetPenPatN( fhObject, pattern );
	}
	else {
		gSDK->SetDefaultPenPatN( pattern );
	}
}

void VWObjectAttr::SetPenPattern(const InternalIndex& dashIndex)
{
#if BUG
	if (dashIndex < 0) {
		auto h = gSDK->InternalIndexToHandle(-dashIndex);
		if (h == NULL || gSDK->GetObjectTypeN(h) != 96)
			DSTOP((kTolu, "Invalid dash style specified"));
	}
#endif

	if ( fhObject ) {
		gSDK->SetPenPatN( fhObject, dashIndex );
	}
	else {
		gSDK->SetDefaultPenPatN( dashIndex );
	}
}

bool VWObjectAttr::GetPenPatternByClass() const
{
	if ( fhObject ) {
		return gSDK->GetPPatByClass( fhObject );
	}
	else {
		return gSDK->GetDefaultPPatByClass();
	}
}

void VWObjectAttr::SetPenPatternByClass()
{
	if ( fhObject ) {
		gSDK->SetPPatByClass( fhObject );
	}
	else {
		gSDK->SetDefaultPPatByClass();
	}
}

void VWObjectAttr::SetFillNone()
{
	if ( fhObject ) {
		gSDK->SetFillPat( fhObject, 0 );

		if ( gSDK->GetObjectTypeN( fhObject ) == kGroupNode ) {
			for(	VWObjectIterator it = VWGroupObj( fhObject ).GetFirstMemberIterator();
					*it;
					++it)
			{
				VWObjectAttr( *it ).SetFillNone();
			}
		}
	}
	else {
		gSDK->SetDefaultFillPat( 0 );
	}
}

bool VWObjectAttr::GetFillNone() const
{
	bool result = false;
	if ( fhObject )
	{
		result = (gSDK->GetFillPat( fhObject ) == 0);
	}
	else
	{
		result = (gSDK->GetDefaultFillPat() == 0);
	}

	return result;
}

void VWObjectAttr::SetFillSolid()
{
	if ( fhObject ) {
		gSDK->SetFillPat( fhObject, 1 );

		if ( gSDK->GetObjectTypeN( fhObject ) == kGroupNode ) {
			for(	VWObjectIterator it = VWGroupObj( fhObject ).GetFirstMemberIterator();
					*it;
					++it)
			{
				VWObjectAttr( *it ).SetFillSolid();
			}
		}
	}
	else {
		gSDK->SetDefaultFillPat( 1 );
	}
}

CRGBColor VWObjectAttr::GetFillForeColor() const
{
	ObjectColorType		color;
	if ( fhObject ) {
		gSDK->GetColor( fhObject, color );
	}
	else {
		gSDK->GetDefaultColors( color );
	}

#if _MINICAD_
	return CRGBColor( color.v0.fillFore );
#else
	return CRGBColor( color.fillFore );
#endif
}

CRGBColor VWObjectAttr::GetFillBackColor() const
{
	ObjectColorType		color;
	if ( fhObject ) {
		gSDK->GetColor( fhObject, color );
	}
	else {
		gSDK->GetDefaultColors( color );
	}

#if _MINICAD_
	return CRGBColor( color.v0.fillBack );
#else
	return CRGBColor( color.fillBack );
#endif
}

void VWObjectAttr::SetFillForeColor(const CRGBColor& clr)
{
	ObjectColorType		color;
	if ( fhObject ) {
		gSDK->GetColor( fhObject, color );
	}
	else {
		gSDK->GetDefaultColors( color );
	}

#if _MINICAD_
	color.v0.fillFore	= clr.GetColorIndex();
#else
	color.fillFore		= clr.GetColorIndex();
#endif

	if ( fhObject ) {
		gSDK->SetColor( fhObject, color );
	}
	else {
		gSDK->SetDefaultColors( color );
	}
}

void VWObjectAttr::SetFillBackColor(const CRGBColor& clr)
{
	ObjectColorType		color;
	if ( fhObject ) {
		gSDK->GetColor( fhObject, color );
	}
	else {
		gSDK->GetDefaultColors( color );
	}

#if _MINICAD_
	color.v0.fillBack	= clr.GetColorIndex();
#else
	color.fillBack		= clr.GetColorIndex();
#endif

	if ( fhObject ) {
		gSDK->SetColor( fhObject, color );
	}
	else {
		gSDK->SetDefaultColors( color );
	}
}

bool VWObjectAttr::GetFillColorByClass() const
{
	if ( fhObject ) {
		return gSDK->GetFColorsByClass( fhObject );
	}
	else {
		return gSDK->GetDefaultFColorsByClass( );
	}
}

void VWObjectAttr::SetFillColorByClass()
{
	if ( fhObject ) {
		gSDK->SetFColorsByClass( fhObject );
	}
	else {
		gSDK->SetDefaultFColorsByClass( );
	}
}

VWPattern VWObjectAttr::GetFillPattern() const
{
	if ( fhObject ) {
		return VWPattern( gSDK->GetFillPat( fhObject ) , true);
	}
	else {
		return VWPattern( gSDK->GetDefaultFillPat(), true );
	}
}

void VWObjectAttr::SetFillPattern(const VWPattern& pattern)
{
	if ( fhObject ) {
		gSDK->SetFillPat( fhObject, pattern );
	}
	else {
		gSDK->SetDefaultFillPat( pattern );
	}
}

bool VWObjectAttr::GetFillPatternByClass() const
{
	if ( fhObject ) {
		return gSDK->GetFPatByClass( fhObject );
	}
	else {
		return gSDK->GetDefaultFPatByClass(  );
	}
}

void VWObjectAttr::SetFillPatternByClass()
{
	if ( fhObject ) {
		gSDK->SetFPatByClass(  fhObject );
	}
	else {
		gSDK->SetDefaultFPatByClass(  );
	}
}

short VWObjectAttr::GetLineWeightInMils() const
{
	if ( fhObject ) {
		return gSDK->GetLineWeight( fhObject );
	}
	else {
		return gSDK->GetDefaultLineWeight( );
	}
}

void VWObjectAttr::SetLineWeightInMils(short mils)
{
	if ( fhObject ) {
		gSDK->SetLineWeight( fhObject, mils );
	}
	else {
		gSDK->SetDefaultLineWeight( mils );
	}
}

bool VWObjectAttr::GetLineWeightByClass() const
{
	if ( fhObject ) {
		return gSDK->GetLWByClass( fhObject );
	}
	else {
		return gSDK->GetDefaultLWByClass(  );
	}
}

void VWObjectAttr::SetLineWeightByClass()
{
	if ( fhObject ) {
		gSDK->SetLWByClass( fhObject );
	}
	else {
		gSDK->SetDefaultLWByClass( );
	}
}

MarkerType VWObjectAttr::GetMarker(short& size, short& angle, bool& start, bool& end) const
{
	MarkerType		style = 0;
	Boolean			innerStart = false, innerEnd = false;
	if ( fhObject ) {
		gSDK->GetMarker( fhObject, style, size, angle, innerStart, innerEnd );
	}
	else {
		DSTOP((kVStanev, "no ISDK function?"));
	}

	start		= innerStart ? true : false;
	end			= innerEnd ? true : false;
	return style;
}

void VWObjectAttr::SetMarker(MarkerType marker,short size, short angle, bool start, bool end)
{
	if ( fhObject ) {
		gSDK->SetMarker( fhObject, marker, size, angle, start, end);
	}
	else {
		DSTOP((kVStanev, "no ISDK function?"));
	}
}

ArrowType VWObjectAttr::GetArrowHeads(bool& starting, bool& ending, short& sizeInPoints)
{
	ArrowType	style;
	Boolean			innerStart, innerEnd;
	if ( fhObject ) {
		gSDK->GetArrowHeads( fhObject, innerStart, innerEnd, style, sizeInPoints );
	}
	else {
		gSDK->GetDefaultArrowHeads( innerStart, innerEnd, style, sizeInPoints );
	}

	starting		= innerStart ? true : false;
	ending			= innerEnd ? true : false;
	return style;
}

ArrowType VWObjectAttr::GetArrowHeads(bool& starting, bool& ending, double_gs& sizeInMilimeters)
{
	ArrowType		style;
	double_gs		sizeInInch;
	Boolean			innerStart, innerEnd;
	if ( fhObject ) {
		gSDK->GetArrowHeadsN( fhObject, innerStart, innerEnd, style, sizeInInch );
	}
	else {
		gSDK->GetDefaultArrowHeadsN( innerStart, innerEnd, style, sizeInInch );
	}

	starting				= innerStart ? true : false;
	ending					= innerEnd ? true : false;
	sizeInMilimeters		= sizeInInch * 25.4;
	return style;
}

void VWObjectAttr::SetArrowHeads(ArrowType type, bool starting, bool ending, short sizeInPoints)
{
	if ( fhObject ) {
		gSDK->SetArrowHeads( fhObject, starting, ending, type, sizeInPoints );
	}
	else {
		gSDK->SetDefaultArrowHeads( starting, ending, type, sizeInPoints );
	}
}

void VWObjectAttr::SetArrowHeads(ArrowType type, bool starting, bool ending, double_gs sizeInMilimeters)
{
	double_gs	sizeInInch	= sizeInMilimeters / 25.4;
	if ( fhObject ) {
		gSDK->SetArrowHeadsN( fhObject, starting, ending, type, sizeInInch );
	}
	else {
		gSDK->SetDefaultArrowHeadsN( starting, ending, type, sizeInInch );
	}
}

bool VWObjectAttr::GetArrowByClass() const
{
	if ( fhObject ) {
		return gSDK->GetArrowByClass( fhObject );
	}
	else {
		return gSDK->GetDefaultArrowByClass(  );
	}
}

void VWObjectAttr::SetArrowByClass()
{
	if ( fhObject ) {
		gSDK->SetArrowByClass( fhObject );
	}
	else {
		gSDK->SetDefaultArrowByClass(  );
	}
}

VWPoint2D VWObjectAttr::GetFillOriginPoint() const
{
	WorldPt		pt;
	if ( fhObject ) {
		VERIFYN( kVStanev, gSDK->GetFillOriginPoint( fhObject, pt ) );
	}
	else {
		DSTOP((kVStanev, "no ISDK function?"));
	}

	return pt;
}

void VWObjectAttr::SetFillOriginPoint(const VWPoint2D& pt)
{
	if ( fhObject ) {
		VERIFYN( kVStanev, gSDK->SetFillOriginPoint( fhObject, pt ) );
	}
	else {
		DSTOP((kVStanev, "no ISDK function?"));
	}
}

VWPoint2D VWObjectAttr::GetFillIAxisEndPoint() const
{
	WorldPt	pt;
	if ( fhObject ) {
		VERIFYN( kVStanev, gSDK->GetFillIAxisEndPoint( fhObject, pt ) );
	}
	else {
		DSTOP((kVStanev, "no ISDK function?"));
	}

	return pt;
}

void VWObjectAttr::SetFillIAxisEndPoint(const VWPoint2D& pt)
{
	if ( fhObject ) {
		VERIFYN( kVStanev, gSDK->SetFillIAxisEndPoint( fhObject, pt ) );
	}
	else {
		DSTOP((kVStanev, "no ISDK function?"));
	}
}

VWPoint2D VWObjectAttr::GetFillJAxisEndPoint() const
{
	WorldPt	pt;
	if ( fhObject ) {
		VERIFYN( kVStanev, gSDK->GetFillJAxisEndPoint( fhObject, pt ) );
	}
	else {
		DSTOP((kVStanev, "no ISDK function?"));
	}

	return pt;
}

void VWObjectAttr::SetFillJAxisEndPoint(const VWPoint2D& pt)
{
	if ( fhObject ) {
		VERIFYN( kVStanev, gSDK->SetFillJAxisEndPoint( fhObject, pt ) );
	}
	else {
		DSTOP((kVStanev, "no ISDK function?"));
	}
}

void VWObjectAttr::GetFillPoints(VWPoint2D& originPoint, VWPoint2D& iAxisEndPoint, VWPoint2D& jAxisEndPoint)
{
	WorldPt			a, b, c;
	if ( fhObject ) {
		VERIFYN( kVStanev, gSDK->GetFillPoints( fhObject, a, b, c ) );
	}
	else {
		DSTOP((kVStanev, "no ISDK function?"));
	}

	originPoint		= a;
	iAxisEndPoint	= b;
	jAxisEndPoint	= c;
}

OpacityRef VWObjectAttr::GetOpacity() const
{
	if ( fhObject ) {
		return gSDK->GetOpacity( fhObject );
	}
	else {
		return gSDK->GetDefaultOpacity(  );
	}
}

void VWObjectAttr::SetOpacity(OpacityRef ref)
{
	if ( fhObject ) {
		gSDK->SetOpacity( fhObject, ref );
	}
	else {
		gSDK->SetDefaultOpacity( ref );
	}
}

bool VWObjectAttr::GetOpacityByClass() const
{
	return gSDK->GetOpacityByClass( fhObject );
}

void VWObjectAttr::SetOpacityByClass()
{
	gSDK->SetOpacityByClass( fhObject );
}

bool VWObjectAttr::FillSpaceMappingExists() const
{
	bool fillSpaceExists	= false;

	TVariableBlock	value;
	gSDK->GetObjectVariable(fhObject, ovIsFillSpaceExisting, value);
	value.GetBoolean(fillSpaceExists);

	return fillSpaceExists;
}

