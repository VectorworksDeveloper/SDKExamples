//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;

CRGBColor::CRGBColor()
{
	this->red		= 0;
	this->green		= 0;
	this->blue		= 0;
}

CRGBColor::CRGBColor(Uint8 r, Uint8 g, Uint8 b)
{
	this->red		= (r << 8) | r;
	this->green		= (g << 8) | g;
	this->blue		= (b << 8) | b;
}

CRGBColor::CRGBColor(float cyan, float magenta, float yellow, float key)
{
	this->SetColor( cyan, magenta, yellow, key );
}

CRGBColor::CRGBColor(const TXString& clrString)
{
	this->SetColor( clrString );
}

CRGBColor::CRGBColor(const RGBColor& clr)
{
	this->red		= clr.red;
	this->green		= clr.green;
	this->blue		= clr.blue;
}

CRGBColor::CRGBColor(const CRGBColor& clr)
{
	this->red		= clr.red;
	this->green		= clr.green;
	this->blue		= clr.blue;
}

// create gradient color from 'leftColor' to 'rightColor' using percentage
// 0% = leftColor; 100% = rightColor
CRGBColor::CRGBColor(const CRGBColor& leftColor, const CRGBColor& rightColor, double dPercent)
{

	Uint8	r	= (Uint8) ( (double)( rightColor.GetRed() - leftColor.GetRed() ) * (dPercent/100) + leftColor.GetRed() );
	Uint8	g	= (Uint8) ( (double)( rightColor.GetGreen() - leftColor.GetGreen() ) * (dPercent/100) + leftColor.GetGreen() );
	Uint8	b	= (Uint8) ( (double)( rightColor.GetBlue() - leftColor.GetBlue() ) * (dPercent/100) + leftColor.GetBlue() );

	this->SetColor( r, g, b );
}

CRGBColor::CRGBColor(ColorRef colorIndex)
{
	::GS_ColorIndexToRGB( gCBP, colorIndex, *this );
}

CRGBColor::~CRGBColor()
{
}

CRGBColor& CRGBColor::operator=(const RGBColor& clr)
{
	this->red		= clr.red;
	this->green		= clr.green;
	this->blue		= clr.blue;
	return *this;
}

CRGBColor& CRGBColor::operator=(const CRGBColor& clr)
{
	this->red		= clr.red;
	this->green		= clr.green;
	this->blue		= clr.blue;
	return *this;
}

bool CRGBColor::operator==(const CRGBColor& clr) const
{
	return
		this->red == clr.red &&
		this->green == clr.green &&
		this->blue == clr.blue ;
}

bool CRGBColor::operator!=(const CRGBColor& clr) const
{
	return ! ( this->operator == ( clr ) );
}

Uint8 CRGBColor::GetRed() const
{
	return (this->red >> 8) & 0xFF;
}

void CRGBColor::SetRed(Uint8 red)
{
	this->red		= (red << 8) | red;
}

Uint8 CRGBColor::GetGreen() const
{
	return (this->green >> 8) & 0xFF;
}

void CRGBColor::SetGreen(Uint8 green)
{
	this->green		= (green << 8) | green;
}

Uint8 CRGBColor::GetBlue() const
{
	return (this->blue >> 8) & 0xFF;
}

void CRGBColor::SetBlue(Uint8 blue)
{
	this->blue		= (blue << 8) | blue;
}

void CRGBColor::GetColor(Uint8& r, Uint8& g, Uint8& b) const
{
	r = this->red >> 8;
	g = this->green >> 8;
	b = this->blue >> 8;
}

void CRGBColor::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	this->red		= (r << 8) | r;
	this->green		= (g << 8) | g;
	this->blue		= (b << 8) | b;
}

void CRGBColor::GetColor(float& cyan, float& magenta, float& yellow, float& key)
{
	TGSColorV2	color;
	color.SetRGB16( this->red, this->green, this->blue );
	color.GetCMYK( cyan, magenta, yellow, key );
}

void CRGBColor::SetColor(float cyan, float magenta, float yellow, float key)
{
	TGSColorV2	color;
	color.SetCMYK( cyan, magenta, yellow, key );
	color.GetRGB16( this->red, this->green, this->blue );
}

void CRGBColor::SetColor(ColorRef colorIndex)
{
	::GS_ColorIndexToRGB( gCBP, colorIndex, *this );
}

ColorRef CRGBColor::GetColorIndex(bool bMatchBlackBkgr) const
{
	ColorRef		colorIndex;

	// When in black background, 'GS_RGBToColorIndex' reverses black and white.
	// If the caller doesn't want this reveresal, we need to un-swap black & white.
	bool bReverseBlackAndWhite = false;

	if ( bMatchBlackBkgr ) {
		::GS_GetProgramVariable( gCBP, varBlackBackground, & bReverseBlackAndWhite );
	}

	if ( bReverseBlackAndWhite ) {
		const CRGBColor kRGBWhite(255,255,255);
		const CRGBColor kRGBBlack(0,0,0);

		if (*this == kRGBBlack)
			::GS_RGBToColorIndex( gCBP, kRGBWhite, colorIndex );
		else if (*this == kRGBWhite)
			::GS_RGBToColorIndex( gCBP, kRGBBlack, colorIndex );
		else
			::GS_RGBToColorIndex( gCBP, *this, colorIndex );
	}
	else {
		::GS_RGBToColorIndex( gCBP, *this, colorIndex );
	}

	return colorIndex;
}

// Set black color (white for black background mode)
void CRGBColor::SetFrontColor()
{
	bool bReverseBlackAndWhite = false;
	::GS_GetProgramVariable( gCBP, varBlackBackground, & bReverseBlackAndWhite );
	
	if ( bReverseBlackAndWhite == false ) {
		this->SetColor( 0, 0, 0 );
	}
	else {
		this->SetColor( 255, 255, 255 );
	}
}

// Set white color (black for black background mode)
void CRGBColor::SetBackgroundColor()
{
	bool bReverseBlackAndWhite = false;
	::GS_GetProgramVariable( gCBP, varBlackBackground, & bReverseBlackAndWhite );
	
	if ( bReverseBlackAndWhite == false ) {
		this->SetColor( 255, 255, 255 );
	}
	else {
		this->SetColor( 0, 0, 0 );
	}
}

TXString CRGBColor::GetColor()
{
	TXString	result;
	result.Format( "%d,%d,%d", this->GetRed(), this->GetGreen(), this->GetBlue() );
	return result;
}

bool CRGBColor::SetColor(const TXString& clrString)
{
	TXStringSTLArray	clrTokens;
	TXStringExt::Tokenize( clrString, clrTokens, "," );

	bool	result	= clrTokens.size() >= 3;
	if ( result )
	{
		this->SetRed( clrTokens[0].atoi() );
		this->SetGreen( clrTokens[1].atoi() );
		this->SetBlue( clrTokens[2].atoi() );
	}

	return result;
}

