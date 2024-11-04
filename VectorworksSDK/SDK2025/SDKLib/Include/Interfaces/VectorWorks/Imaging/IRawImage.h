//
//	Copyright 2013 Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "PixelType.h"

namespace VectorWorks
{
    class IDrawPad;

	namespace Imaging
	{
        enum ConvertToDepth {
            kConvertToBestDepth = 0, // whatever is best for the source image
            kConvertTo1bpp		= 1,
            kConvertTo8bpp		= 8,
            kConvertTo16bpp		= 16,
            kConvertTo24bpp		= 24,
            kConvertTo32bpp		= 32
        };
        
        enum RescalingMethod {
            kRescalingNone       = 0,                // Mac => kCGInterpolationNone,    Windows => WICBitmapInterpolationModeNearestNeighbor
            kRescalingLow        = 1,                // Mac => kCGInterpolationLow,     Windows => WICBitmapInterpolationModeLinear
            kRescalingMedium     = 2,                // Mac => kCGInterpolationMedium,  Windows => WICBitmapInterpolationModeCubic
            kRescalingHigh       = 3                 // Mac => kCGInterpolationHigh,    Windows => WICBitmapInterpolationModeFant
        };
        
		struct RawImageDesc {
			Uint32	width;
			Uint32	height;
			PixelType pixelType;
			Uint32	bitsPerPixel;
			Uint32	bytesPerRow;
			double	hRes; // Horizontal dpi 
			double	vRes; // Vertical dpi
			bool	fbHasAlpha;
			bool	fbHasPremultipliedAlpha;
			Sint16			fNumColors;
			GSColorTable	fColorTable;
			Uint32	bufferSizeInBytes;
			void*	bufferPtr;
            RescalingMethod	rescalingMethod;
		};

		class ICompressedImage;

		// ----------------------------------------------------------------------------------------------------
		// {B5976537-B449-42FE-B26A-2489E920661D}
		static const VWIID IID_RawImage = { 0xB5976537, 0xB449, 0x42FE, { 0xB2, 0x6A, 0x24, 0x89, 0xE9, 0x20, 0x66, 0x1D } };

		class DYNAMIC_ATTRIBUTE IRawImage : public IVWUnknown
		{
		public:
			virtual bool VCOM_CALLTYPE IsInitialized() = 0;

			virtual VCOMError VCOM_CALLTYPE	CreateFromBits(const RawImageDesc& inImageDesc) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateFromObject(MCObjectHandle inhBitmapOrImageObj, double inHRes, double inVRes, bool inbHasAlpha) = 0;
			virtual VCOMError VCOM_CALLTYPE CreateFromPreview(InternalIndex inPreviewIndex, Uint32 inWidth, Uint32 inHeight) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateFromCompressedImage(ICompressedImage* pCompressedImage) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateFromCompressedImageEx(ICompressedImage* pCompressedImage, ConvertToDepth inDepth, Uint32 inAdjWidth/*0 == Keep original*/, Uint32 inAdjHeight/*0 == Keep original*/) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateFromDrawPad(IDrawPad* pDrawPad) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateMonochromeFromCompressedImage(ICompressedImage* pCompressedImage, bool useDithering) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetImageDesc(RawImageDesc& outImageDesc) = 0;

			virtual VCOMError VCOM_CALLTYPE CreateBitmapObject(MCObjectHandle& outhObj, bool select=true) = 0;
			virtual VCOMError VCOM_CALLTYPE CreateImageObject(MCObjectHandle& outhObj) = 0;
			virtual VCOMError VCOM_CALLTYPE	UpdateExisting(MCObjectHandle obj, bool doUndo) = 0;
			
			virtual VCOMError VCOM_CALLTYPE InvertMonochrome() = 0;
			virtual VCOMError VCOM_CALLTYPE Flip() = 0;
			
			virtual VCOMError VCOM_CALLTYPE GetPalettePointer(GSColor* &pPalette) = 0;
			
			virtual VCOMError VCOM_CALLTYPE SetResolution(double inhRes, double invRes) = 0;
			virtual VCOMError VCOM_CALLTYPE SetHasAlpha(bool inbHasAlpha) = 0;
			virtual VCOMError VCOM_CALLTYPE ResolveAlphaWithBackgroundColor(const TGSColorV2& inBkColor) = 0;
			virtual VCOMError VCOM_CALLTYPE SetPixelDimensions(const Uint32 inWidth, const Uint32 inHeight, const RescalingMethod rescalingMethod) = 0;
			virtual VCOMError VCOM_CALLTYPE ConvertColorDepth(ConvertToDepth converTo) = 0;

			virtual VCOMError VCOM_CALLTYPE SetExposure(double amount = 0.5) = 0;
			virtual VCOMError VCOM_CALLTYPE SetContrast(double amount = 0.5) = 0;
			virtual VCOMError VCOM_CALLTYPE SetHighlights(double amount = 0.5) = 0;
			virtual VCOMError VCOM_CALLTYPE SetShadows(double amount = 0.5) = 0;
			virtual VCOMError VCOM_CALLTYPE SetSaturation(double amount = 0.5) = 0;
			virtual VCOMError VCOM_CALLTYPE SetTemperature(double amount = 0.5) = 0;
			virtual VCOMError VCOM_CALLTYPE SetBlurAndSharpness(double amount = 0.5) = 0;
			virtual VCOMError VCOM_CALLTYPE SetSepia(double amount = 0) = 0;
			virtual VCOMError VCOM_CALLTYPE SetSoftEdges(double amount = 0) = 0;
			virtual VCOMError VCOM_CALLTYPE AutoLevel() = 0;
			virtual VCOMError VCOM_CALLTYPE InvertColors() = 0;

			virtual VCOMError VCOM_CALLTYPE StartEdit() = 0;
			virtual VCOMError VCOM_CALLTYPE EndEdit() = 0;

			virtual VCOMError VCOM_CALLTYPE BlendWithBackground() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IRawImage>		IRawImagePtr;
	}
}
