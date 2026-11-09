//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//	Declares a wrapper for a VCOM IDrawPad interface.
//
// 

#pragma once

#include "VectorworksSDK.h"

class GSDrawPad
//
//	This is a wrapper class for the IDrawPad service as provided by the VectorWorks Core 
//	and published via VCOM.  Currently this is provided for Internal use only.
//	It is used in OverridednControl.cpp inside the GS_USE_GSDRAWPAD flag
//
{
public:
	GSDrawPad(SintptrT devHandle, void* devDC);
	GSDrawPad(const ViewRect& inViewRect);
	virtual ~GSDrawPad();
	
	void SetCanvasColor(const GSColor& color);
	void SetPen(Sint16 inPenSize, const GSColor& inForeColor, const GSColor& inBackColor, Sint16 inStyle);
	void FillRect(const ViewRect& rect);
	void FrameRect(const ViewRect& rect);
	void SetClipRect(const ViewRect& rect);
	void SetPenFgColor(const GSColor& inColor);
	Uint32 GetTextWidth(const TXString& string);
	void TextMoveTo(Sint16 x, Sint16 y);
	void DrawTextString(const TXString& string); 
	void DPMoveTo(Sint16 x, Sint16 y);
	void DPLineTo(Sint16 x, Sint16 y);
	Uint32 GetCharacterWidth(const char ch);
	void CopyBitsOut(const GSRect32& srcRect, GSDrawPad& ioDestGSDrawPad, const GSRect32& destRect, VectorWorks::EDrawPadTransferMode mode);
	void DrawDashedLine(const ViewPt& m1, const ViewPt& m2, InternalIndex lineStyle, short thickness);
				
	void CreatePoly(GSPolyRef& outPolyRef);
	void AddPolyPt(const GSPolyRef& inPolyRef, const ViewPt& inPt);
	void ReleasePoly(const GSPolyRef& inPolyRef);
	void FillPoly(const GSPolyRef& inPolyRef);
	Bool8 CaptureDevice();
	Bool8 ReleaseDevice();


protected:
	
	VCOMPtr<VectorWorks::IDrawPad>* fpDrawPad;
};

