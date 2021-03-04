//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// GSDrawPad implements a GSDrawPad wrapper for an IDraPad interface.									
 
#include "StdHeaders.h"	// Must be first non-comment line.  See StdHeaders.h for explanation.


#include "GSDrawPad.h"

using namespace VectorWorks;


// --------------------------------------------------------------------------------------------------------
GSDrawPad::GSDrawPad(SintptrT devHandle, void* devDC)
{
	// GS_MAC
	fpDrawPad = SDK_NEW VCOMPtr<VectorWorks::IDrawPad>(IID_DrawPad);
	if (fpDrawPad && *fpDrawPad) {
		if (!VCOM_SUCCEEDED((*fpDrawPad)->InitializeInDevice(devHandle, devDC))) {
			delete fpDrawPad;
			fpDrawPad = nil;
		}
	}
}


// --------------------------------------------------------------------------------------------------------
GSDrawPad::GSDrawPad(const ViewRect& inViewRect)
{
	fpDrawPad = SDK_NEW VCOMPtr<VectorWorks::IDrawPad>(IID_DrawPad);
	if (fpDrawPad && *fpDrawPad) {
		
		if (!VCOM_SUCCEEDED((*fpDrawPad)->InitializeInMemory(inViewRect))) {
			delete fpDrawPad;
			fpDrawPad = nil;
		}
		else
			(*fpDrawPad)->SetClipRect(inViewRect);
	}
}

// --------------------------------------------------------------------------------------------------------
GSDrawPad::~GSDrawPad()
{
	delete fpDrawPad;
}

#define DRAWPADCALL DSTOPIF(!fpDrawPad || !*fpDrawPad, (kSteve, "Stop\n")); if (fpDrawPad && *fpDrawPad) (*fpDrawPad)

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::SetCanvasColor(const GSColor& color)
{
	DRAWPADCALL->SetBackgroundColor(color);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::SetPen(Sint16 inPenSize, const GSColor& inForeColor, const GSColor& inBackColor, Sint16 inStyle)
{
	DRAWPADCALL->SetPen(inPenSize, inForeColor, inBackColor, inStyle);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::FillRect(const ViewRect& rect)
{
	DRAWPADCALL->FillRect(rect);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::FrameRect(const ViewRect& rect)
{
	DRAWPADCALL->FrameRect(rect);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::SetClipRect(const ViewRect& rect)
{
	DRAWPADCALL->SetClipRect(rect);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::SetPenFgColor(const GSColor& inColor)
{
	DRAWPADCALL->SetPenFgColor(inColor);
}

// --------------------------------------------------------------------------------------------------------
Uint32 GSDrawPad::GetTextWidth(const TXString& string)
{
	Uint32 width = 0;
	DRAWPADCALL->GetTextWidth( string, width );
	return width;
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::TextMoveTo(Sint16 x, Sint16 y)
{
	DRAWPADCALL->TextMoveTo(x, y);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::DrawTextString(const TXString& string)
{
	DRAWPADCALL->DrawTextString( string );
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::DPMoveTo(Sint16 x, Sint16 y)
{
	DRAWPADCALL->DPMoveTo(x, y);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::DPLineTo(Sint16 x, Sint16 y)
{
	DRAWPADCALL->DPLineTo(x, y);
}

// --------------------------------------------------------------------------------------------------------
Uint32 GSDrawPad::GetCharacterWidth(const char ch)
{
	Uint32 width = 0;
	DRAWPADCALL->GetCharacterWidth(ch, width);
	return width;
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::CopyBitsOut(const GSRect32& srcRect, GSDrawPad& ioDestGSDrawPad, const GSRect32& destRect, EDrawPadTransferMode mode)
{
	if (fpDrawPad && *fpDrawPad && ioDestGSDrawPad.fpDrawPad)
		(*fpDrawPad)->CopyBitsOut(srcRect, *ioDestGSDrawPad.fpDrawPad, destRect, mode);
	else
		DSTOP((kSteve, "Stop\n"));
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::DrawDashedLine(const ViewPt& m1, const ViewPt& m2, InternalIndex lineStyle, short thickness)
{

	DRAWPADCALL->DrawDashedLineN(m1, m2, lineStyle, thickness);
}
							
// --------------------------------------------------------------------------------------------------------
void GSDrawPad::CreatePoly(GSPolyRef& outPolyRef)
{
	DRAWPADCALL->CreatePoly(outPolyRef);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::AddPolyPt(const GSPolyRef& inPolyRef, const ViewPt& inPt)
{
	DRAWPADCALL->AddPolyPt(inPolyRef, inPt);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::ReleasePoly(const GSPolyRef& inPolyRef)
{
	DRAWPADCALL->ReleasePoly(inPolyRef);
}

// --------------------------------------------------------------------------------------------------------
void GSDrawPad::FillPoly(const GSPolyRef& inPolyRef)
{
	DRAWPADCALL->FillPoly(inPolyRef);
}

// --------------------------------------------------------------------------------------------------------
Bool8 GSDrawPad::CaptureDevice()
{
	if (fpDrawPad && *fpDrawPad && (*fpDrawPad)->CaptureDevice())
		return true;
	else
		return false;
}

// --------------------------------------------------------------------------------------------------------
Bool8 GSDrawPad::ReleaseDevice()
{
	if (fpDrawPad && *fpDrawPad && (*fpDrawPad)->ReleaseDevice())
		return true;
	else
		return false;
}


#undef DRAWPADCALL