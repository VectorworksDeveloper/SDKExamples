//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Interfaces/VectorWorks/IDrawPad.h"

#include "Control.h"

#include "CustomCtrlAttrs.h"

namespace VWFC
{
	namespace VWUI
	{
		// ---------------------------------------------------------------------------------------------------------------
		enum ECustomDCPreviewMode
		{
			kCustomDCPreviewMode_PlanMode			= 1,
			kCustomDCPreviewMode_Front				= 3,
			kCustomDCPreviewMode_Back				= 4,
			kCustomDCPreviewMode_Left				= 5,
			kCustomDCPreviewMode_Right				= 6,
			kCustomDCPreviewMode_Top 				= 7,
			kCustomDCPreviewMode_Bottom				= 8,
			kCustomDCPreviewMode_RightIso			= 9,
			kCustomDCPreviewMode_LeftIso 			= 10,
			kCustomDCPreviewMode_RightRearIso		= 11,
			kCustomDCPreviewMode_LeftRearIso 		= 12,
			kCustomDCPreviewMode_BottomRightIso		= 13,
			kCustomDCPreviewMode_BottomLeftIso		= 14,
			kCustomDCPreviewMode_BottomRightRearIso	= 15,
			kCustomDCPreviewMode_BottomLeftRearIso	= 16,
		};

		// ---------------------------------------------------------------------------------------------------------------
		enum ECustomDCRenderMode
		{
			kCustomDCRenderMode_WireFrame				= 0,
			kCustomDCRenderMode_Solid					= 2,
			kCustomDCRenderMode_ShadedSolid				= 3,
			kCustomDCRenderMode_ShadedNoLines			= 4,
			kCustomDCRenderMode_FinalShaded				= 5,
			kCustomDCRenderMode_FinalHiddenLine			= 6,
			kCustomDCRenderMode_DashedHiddenLine		= 7,
			kCustomDCRenderMode_OpenGL					= 11,
			kCustomDCRenderMode_FastRenderWorks			= 12,
			kCustomDCRenderMode_FastShadowRenderWorks  	= 13,
			kCustomDCRenderMode_FinalRenderWorks		= 14,
			kCustomDCRenderMode_CustomRenderWorks		= 15,
			kCustomDCRenderMode_ArtisticRenderWorks 	= 17,
			kCustomDCRenderMode_Sketch					= 18,
		};

		// ---------------------------------------------------------------------------------------------------------------
		class VWCustomCtrl;

		// ---------------------------------------------------------------------------------------------------------------
		class VWCustomCtrlDC
		{
			friend class VWCustomCtrl;
		public:
								VWCustomCtrlDC(ViewCoord width, ViewCoord height);
			virtual				~VWCustomCtrlDC();

			SintptrT			GetOSDevice() const;
			ViewCoord			GetXOffset() const;
			ViewCoord			GetYOffset() const;

		public:
			void				SelectPen(const VWCustomCtrlPen& pen);
			void				SelectBrush(const VWCustomCtrlBrush& brush);
			void				SelectFont(const VWCustomCtrlFont& font);

			VWCustomCtrlPen		GetSelectedPen() const;
			VWCustomCtrlBrush	GetSelectedBrush() const;
			VWCustomCtrlFont	GetSelectedFont() const;

		public:
			void				SetClipRect(const ViewRect& rect);

			void				DrawLine(const ViewPt& fromPt, const ViewPt& toPt);
			void				DrawRect(const ViewRect& rect);
			void				FillRect(const ViewRect& rect);

			Uint32				GetStringWidth(const TXString& string);
			void				DrawString(const ViewPt& pt, const TXString& string);
			void				DrawString(const ViewPt& pt, const TXString& string, Uint8 red, Uint8 green, Uint8 blue);
			// This is temporary funciton to allow us to get rid of 'DrawString' from TXString, whic is not working for Japanese
			// 'DrawString_TXString' function works for Japanese too because it internally translates to unicode
			void				DrawString_TXString(const ViewPt& pt, const TXString& string);
            void				DrawString_TXString(const ViewPt& pt, const TXString& string, Uint8 red, Uint8 green, Uint8 blue);

			Uint32				GetStringWidth(ConstUCStrPtr uniString);
			void				DrawString(const ViewPt& pt, ConstUCStrPtr uniString);
			void				DrawString(const ViewPt& pt, ConstUCStrPtr uniString, Uint8 red, Uint8 green, Uint8 blue);

			void				BitBlt(const ViewRect& destRect, const VWCustomCtrlDC& srcDC, const ViewPt& srcPt, VectorWorks::EDrawPadTransferMode mode = VectorWorks::eDrawPadTransferMode_Copy);
			void				BitBlt(const ViewRect& destRect, const VWCustomCtrlDC& srcDC, const ViewRect& srcRect, VectorWorks::EDrawPadTransferMode mode = VectorWorks::eDrawPadTransferMode_Copy);

			void				PathBegin();
			void				PathMoveTo(Sint16 x, Sint16 y);
			void				PathLineTo(Sint16 x, Sint16 y);
//			void				PathArcTo(Sint16 toX, Sint16 toY, Sint16 centerX, Sint16 centerY);
//			void				PathBezierTo(Sint16 toX, Sint16 toY, Sint16 ctrl1X, Sint16 ctrl1Y, Sint16 ctrl2X, Sint16 ctrl2Y);
			void				PathEndDraw();
			void				PathEndDrawAndFill();
			void				PathEndFill();
			void				PathEndFillAndDraw();

			void				DrawSymbolPreview(	InternalIndex resourceRefNum,
													const ViewRect& destRect,
													ECustomDCPreviewMode viewMode = kCustomDCPreviewMode_PlanMode,
													ECustomDCRenderMode renderMode = kCustomDCRenderMode_WireFrame);

			void				DrawSymbolPreview(	InternalIndex resourceRefNum,
													const ViewRect& destRect,
													ViewRect& outDrawnBounts,
													ECustomDCPreviewMode viewMode = kCustomDCPreviewMode_PlanMode,
													ECustomDCRenderMode renderMode = kCustomDCRenderMode_WireFrame);

			void				DrawIcon(const ViewPt& pt, VectorWorks::UI::IIcon* pIcon);
			void				DrawIcon(const ViewRect& rect, VectorWorks::UI::IIcon* pIcon);

		protected:
								VWCustomCtrlDC(SintptrT devHandle, void* devDC, ViewCoord xOffset, ViewCoord yOffset);
								VWCustomCtrlDC(const ViewRect& inViewRect);
								VWCustomCtrlDC(const VWCustomCtrlDC& scr);
			VWCustomCtrlDC&		operator=(const VWCustomCtrlDC& scr);

		private:
			void				PrepForFrame();
			void				PrepForFrame(Uint8 red, Uint8 green, Uint8 blue);
			void				PrepForFill();

			typedef	VCOMPtr<VectorWorks::IDrawPad>	TDrawPad;
			
			SintptrT				fDevHandle;
			void*					fpDevDC;
			TDrawPad				fpDrawPad;
			ViewCoord				fXOffset;
			ViewCoord				fYOffset;

			VWCustomCtrlPen			fCurrentPen;
			VWCustomCtrlBrush		fCurrentBrush;

			void*					farrPolyPts;
		};
	}
}