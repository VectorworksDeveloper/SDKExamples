//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/CustomCtrlAttrs.h"


using namespace VWFC::VWUI;


// ---------------------------------------------------------------------------------------------------------------
VWCustomCtrlPen::VWCustomCtrlPen()
{
//	fStyle	= kCustomCtrlPenStyle_Solid;
	fSize	= 1;
	this->SetColor( 255, 255, 255 );
}

VWCustomCtrlPen::VWCustomCtrlPen(Uint8 red, Uint8 green, Uint8 blue)
{
//	fStyle	= kCustomCtrlPenStyle_Solid;
	fSize	= 1;
	this->SetColor( red, green, blue );
}

VWCustomCtrlPen::VWCustomCtrlPen(Uint8 red, Uint8 green, Uint8 blue, Sint16 size)
{
//	fStyle	= kCustomCtrlPenStyle_Solid;
	fSize	= size;
	this->SetColor( red, green, blue );
}
/*
VWCustomCtrlPen::VWCustomCtrlPen(ECustomCtrlPenStyle style, Uint8 red, Uint8 green, Uint8 blue)
{
	fStyle	= style;
	fSize	= 1;
	fColor.Set16( red, green, blue );
}

VWCustomCtrlPen::VWCustomCtrlPen(ECustomCtrlPenStyle style, Uint8 red, Uint8 green, Uint8 blue, Uint16 size)
{
	fStyle	= style;
	fSize	= size;
	fColor.Set16( red, green, blue );
}
*/
VWCustomCtrlPen::VWCustomCtrlPen(const VWCustomCtrlPen& src)
{
	this->operator = ( src );
}

VWCustomCtrlPen::~VWCustomCtrlPen()
{
}

VWCustomCtrlPen& VWCustomCtrlPen::operator=(const VWCustomCtrlPen& src)
{
	fSize	= src.fSize;
	fColor	= src.fColor;
//	fStyle	= src.fStyle;
	return *this;
}

double VWCustomCtrlPen::GetSize() const
{
	return fSize;
}

void VWCustomCtrlPen::SetSize(double size)
{
	fSize	= size;
}

GSColor VWCustomCtrlPen::GetColor() const
{
	return fColor;
}

void VWCustomCtrlPen::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// This seems wrong but we don't want to promote this to 16bit color,
	// we just want to set the frist 8 bits for the DrawPad. just set the first 8.
	fColor.Set16( red, green, blue );
}


/*
ECustomCtrlPenStyle	VWCustomCtrlPen::GetStyle() const
{
	return fStyle;
}
*/
// ---------------------------------------------------------------------------------------------------------------
VWCustomCtrlBrush::VWCustomCtrlBrush()
{
//	fStyle		= kCustomCtrlBrushStyle_Solid;
	this->SetColor( 0, 0, 0 );
	this->SetBackgroundColor( 255, 255, 255 );
	this->SetPatternIndex(0); // 0=None, 1-71 are patterns
}

VWCustomCtrlBrush::VWCustomCtrlBrush(Uint8 red, Uint8 green, Uint8 blue)
{
//	fStyle		= kCustomCtrlBrushStyle_Solid;
	this->SetColor( red, green, blue );
	this->SetBackgroundColor( 255, 255, 255 );
	this->SetPatternIndex(0); // 0=None, 1-71 are patterns
}

/*
VWCustomCtrlBrush::VWCustomCtrlBrush(ECustomCtrlBrushStyle style, Uint8 red, Uint8 green, Uint8 blue)
{
	fStyle		= style;
	fColor.Set16( red, green, blue );
}*/

VWCustomCtrlBrush::VWCustomCtrlBrush(Uint8 inPatternIndex, Uint8 red, Uint8 green, Uint8 blue, Uint8 backRed, Uint8 backGreen, Uint8 backBlue)
{
	this->SetColor( red, green, blue );
	this->SetBackgroundColor( backRed, backGreen, backBlue );
	this->SetPatternIndex(inPatternIndex);
}

VWCustomCtrlBrush::VWCustomCtrlBrush(const VWCustomCtrlBrush& src)
{
	this->operator = ( src );
}

VWCustomCtrlBrush::~VWCustomCtrlBrush()
{
}

VWCustomCtrlBrush& VWCustomCtrlBrush::operator=(const VWCustomCtrlBrush& src)
{
	fColor	= src.fColor;
//	fStyle	= src.fStyle;
	fColorBackground	= src.fColorBackground;
	fPatternIndex		= src.fPatternIndex;

	return *this;
}

GSColor VWCustomCtrlBrush::GetColor() const
{
	return fColor;
}

void VWCustomCtrlBrush::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// This seems wrong but we don't want to promote this to 16bit color,
	// we just want to set the frist 8 bits for the DrawPad. just set the first 8.
	fColor.Set16( red, green, blue );
}

/*
ECustomCtrlBrushStyle VWCustomCtrlBrush::GetStyle() const
{
	return fStyle;
}*/

GSColor VWCustomCtrlBrush::GetBackgroundColor() const
{
	return fColorBackground;
}

void VWCustomCtrlBrush::SetBackgroundColor(Uint8 red, Uint8 green, Uint8 blue)
{
	fColorBackground.Set16( red, green, blue );
}

Uint8 VWCustomCtrlBrush::GetPatternIndex() const
{
	return fPatternIndex;
}

bool VWCustomCtrlBrush::SetPatternIndex(Uint8 inPatternIndex)
{
	bool outbSuccess = false;

	if (inPatternIndex <= 71) { // 0=None, 1-71 are patterns
		fPatternIndex = inPatternIndex;
		outbSuccess = true;
	}
	else
		fPatternIndex = 0;

	return outbSuccess;
}

// ---------------------------------------------------------------------------------------------------------------
VWCustomCtrlFont::VWCustomCtrlFont()
{
	fFontName			= "Arial";
	fSize				= 12;
	fbBold				= false;
	fbItalic			= false;
	fbUnderlined		= false;
	fbOutline			= false;
	fbShadow			= false;
	fdRotation			= 0;
	fbBaselineMirror	= false;
}

VWCustomCtrlFont::VWCustomCtrlFont(const TXString& fontName, Uint32 size)
{
	fFontName			= fontName;
	fSize				= size;
	fbBold				= false;
	fbItalic			= false;
	fbUnderlined		= false;
	fbOutline			= false;
	fbShadow			= false;
	fdRotation			= 0;
	fbBaselineMirror	= false;
}

VWCustomCtrlFont::VWCustomCtrlFont(const TXString& fontName, Uint32 size, bool bBold, bool bItalic, bool bUnderlined)
{
	fFontName			= fontName;
	fSize				= size;
	fbBold				= bBold;
	fbItalic			= bItalic;
	fbUnderlined		= bUnderlined;
	fbOutline			= false;
	fbShadow			= false;
	fdRotation			= 0;
	fbBaselineMirror	= false;
}

VWCustomCtrlFont::VWCustomCtrlFont(const TXString& fontName, Uint32 size, bool bBold, bool bItalic, bool bUnderlined, bool bOutline, bool bShadow)
{
	fFontName			= fontName;
	fSize				= size;
	fbBold				= bBold;
	fbItalic			= bItalic;
	fbUnderlined		= bUnderlined;
	fbOutline			= bOutline;
	fbShadow			= bShadow;
	fdRotation			= 0;
	fbBaselineMirror	= false;
}

VWCustomCtrlFont::VWCustomCtrlFont(const VWCustomCtrlFont& src)
{
	this->operator = ( src );
}

VWCustomCtrlFont::~VWCustomCtrlFont()
{
}

VWCustomCtrlFont& VWCustomCtrlFont::operator=(const VWCustomCtrlFont& src)
{
	fFontName			= src.fFontName;
	fSize				= src.fSize;
	fbBold				= src.fbBold;
	fbItalic			= src.fbItalic;
	fbUnderlined		= src.fbUnderlined;
	fbOutline			= src.fbOutline;
	fbShadow			= src.fbShadow;
	fdRotation			= src.fdRotation;
	fbBaselineMirror	= src.fbBaselineMirror;
	return *this;
}

TXString VWCustomCtrlFont::GetFontName() const
{
	return fFontName;
}

Uint32 VWCustomCtrlFont::GetFontSize() const
{
	return fSize;
}

void VWCustomCtrlFont::SetFont(const TXString& name, Uint32 size)
{
	fFontName	= name;
	fSize		= size;
}

bool VWCustomCtrlFont::GetBold() const
{
	return fbBold;
}

bool VWCustomCtrlFont::GetItalic() const
{
	return fbItalic;
}

bool VWCustomCtrlFont::GetUnderlined() const
{
	return fbUnderlined;
}

bool VWCustomCtrlFont::GetOutline() const
{
	return fbOutline;
}

bool VWCustomCtrlFont::GetShadow() const
{
	return fbShadow;
}

void VWCustomCtrlFont::SetStyle(bool bold, bool italic, bool underlined)
{
	fbBold			= bold;
	fbItalic		= italic;
	fbUnderlined	= underlined;
}

void VWCustomCtrlFont::SetStyle(bool bold, bool italic, bool underlined, bool outline, bool shadow)
{
	fbBold			= bold;
	fbItalic		= italic;
	fbUnderlined	= underlined;
	fbOutline		= outline;
	fbShadow		= shadow;
}

double VWCustomCtrlFont::GetRotation() const
{
	return fdRotation;
}

void VWCustomCtrlFont::SetRotation(double rot)
{
	fdRotation	= rot;
}

bool VWCustomCtrlFont::GetBaselineMirror() const
{
	return fbBaselineMirror;
}

void VWCustomCtrlFont::SetBaselineMirror(bool mirror)
{
	fbBaselineMirror	= mirror;
}

