//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Imaging/ICompressedImage.h"

namespace VectorWorks
{
	// EDrawPadTransferMode should be in sync with ETransferMode found in DrawPad.Defs.X.h
	enum EDrawPadTransferMode {
		eDrawPadTransferMode_Copy 								= 0,
		eDrawPadTransferMode_Or 								= 1,
		eDrawPadTransferMode_Xor 								= 2,
		eDrawPadTransferMode_Erase 								= 3,
		eDrawPadTransferMode_NotCopy 							= 4,
		eDrawPadTransferMode_NotOr 								= 5,
		eDrawPadTransferMode_NotXor 							= 6,
		eDrawPadTransferMode_NotErase 							= 7,
		eDrawPadTransferMode_WhiteIsTransparent					= 8,
		eDrawPadTransferMode_kAlphaTransparency					= 9,
		eDrawPadTransferMode_kPremultipliedAlphaTransparency	= 10
	};
	
	// ----------------------------------------------------------------------------------------------------
	// {6eef7e80-90f8-11db-b606-0800200c9a66}
	static const VWIID IID_DrawPad = { 0x6eef7e80, 0x90f8, 0x11db, { 0xb6, 0x06, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 } };
			
	class DYNAMIC_ATTRIBUTE IDrawPad : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE	InitializeInDevice(SintptrT deviceHandle, void* devDC) = 0;
		virtual VCOMError VCOM_CALLTYPE	InitializeInMemory(const ViewRect& rect, bool alphaRequired = false) = 0;
		virtual VCOMError VCOM_CALLTYPE SetBackgroundColor(const GSColor& color, OpacityRef opacity = kMaxOpacity) = 0;
		virtual VCOMError VCOM_CALLTYPE EraseBackground() = 0;

		virtual VCOMError VCOM_CALLTYPE SetPen(Sint16 inPenThicknessPixels, const GSColor& inForeColor,
												const GSColor& inBackColor, Sint16 inStyle, 
												Sint16 inPenThicknessMils = -1) = 0;
		virtual VCOMError VCOM_CALLTYPE SetOpacity(OpacityRef opacity) = 0;
								
		virtual VCOMError VCOM_CALLTYPE FillRect(const ViewRect& rect) = 0;
		virtual VCOMError VCOM_CALLTYPE FrameRect(const ViewRect& rect) = 0;
		
		virtual VCOMError VCOM_CALLTYPE SetClipRect(const ViewRect& rect) = 0;
		virtual VCOMError VCOM_CALLTYPE SetPenFgColor(const GSColor& inColor) = 0;
		virtual VCOMError VCOM_CALLTYPE GetTextWidth(const TXString& string, Uint32& outWidth) = 0;
		virtual VCOMError VCOM_CALLTYPE TextMoveTo(Sint16 x, Sint16 y) = 0;
		virtual VCOMError VCOM_CALLTYPE DrawTextString(const TXString& string) = 0; 
		virtual VCOMError VCOM_CALLTYPE DPMoveTo(Sint16 x, Sint16 y) = 0;
		virtual VCOMError VCOM_CALLTYPE DPLineTo(Sint16 x, Sint16 y) = 0;
		virtual VCOMError VCOM_CALLTYPE GetCharacterWidth(const char ch, Uint32& outWidt) = 0;
		virtual VCOMError VCOM_CALLTYPE CopyBitsOut(const GSRect32& srcRect, IDrawPad* pDestDrawPad, const GSRect32& destRect, EDrawPadTransferMode mode) = 0;
		virtual VCOMError VCOM_CALLTYPE DrawCompressedImage(const ViewPt& tl, Imaging::ICompressedImage* pImage) = 0;
		virtual VCOMError VCOM_CALLTYPE DrawCompressedImage(const ViewRect& rc, Imaging::ICompressedImage* pImage) = 0;
		virtual VCOMError VCOM_CALLTYPE DrawDashedLineN(const ViewPt& m1, const ViewPt& m2, InternalIndex lineStyle, short thickness) = 0;
		
		virtual VCOMError VCOM_CALLTYPE CreatePoly(GSPolyRef& outPolyRef) = 0;
		virtual VCOMError VCOM_CALLTYPE AddPolyPt(const GSPolyRef& inPolyRef, const ViewPt& inPt) = 0;
		virtual VCOMError VCOM_CALLTYPE ReleasePoly(const GSPolyRef& inPolyRef) = 0;
		virtual VCOMError VCOM_CALLTYPE FillPoly(const GSPolyRef& inPolyRef) = 0;
		virtual VCOMError VCOM_CALLTYPE CaptureDevice() = 0;
		virtual VCOMError VCOM_CALLTYPE ReleaseDevice() = 0;

		virtual VCOMError VCOM_CALLTYPE SetTextFont(const DPFont& font) = 0;
		virtual VCOMError VCOM_CALLTYPE SetTextAngle(double textAngle, bool baselineMirror) = 0;
		virtual VCOMError VCOM_CALLTYPE GetTextFont(DPFont& outFont) = 0;
		virtual VCOMError VCOM_CALLTYPE GetTextAngle(double& outTextAngle, bool& outBaselineMirror) = 0;
		virtual VCOMError VCOM_CALLTYPE GetFontMetrics(DPFontMetrics& outMetrics) = 0;
		// Avoid using the following function
		virtual VCOMError VCOM_CALLTYPE SetFontByNumber(Sint32 font) = 0;

		virtual VCOMError VCOM_CALLTYPE GetOSDeviceContext(void* & outDevice) = 0;

		virtual VCOMError VCOM_CALLTYPE GetTextWidthN(ConstUCStrPtr uniString, Uint32& outWidth) = 0;
		virtual VCOMError VCOM_CALLTYPE DrawTextStringN(ConstUCStrPtr uniString) = 0;
		
		virtual VCOMError VCOM_CALLTYPE SetAntiAliasing(bool bEnable) = 0;

		virtual VCOMError VCOM_CALLTYPE SetPenF(double inPenThicknessPixels, const GSColor& inForeColor,
												const GSColor& inBackColor, Sint16 inStyle, 
												Sint16 inPenThicknessMils = -1) = 0;

		virtual VCOMError VCOM_CALLTYPE DrawCompressedImage(const ViewRect& destRect, const ViewRect& srcRect, Imaging::ICompressedImage* pImage) = 0;
	};

	// ----------------------------------------------------------------------------------------------------
	typedef VCOMPtr<IDrawPad>		IDrawPadPtr;
}


