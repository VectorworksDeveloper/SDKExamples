//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "../Filing/IFileIdentifier.h"
#include "PixelType.h"

namespace VectorWorks
{
	class IDrawPad;

	namespace Imaging
	{
		enum CompressionType {
			eUnsupported,
			eJPEG,
			ePNG
		};

		enum EImageFormatType {
			eIFT_Other,
			eIFT_JPEG,	// I/O Mac Win
			eIFT_PNG,	// I/O Mac Win
			eIFT_BMP,	// I/O Mac Win
			eIFT_TIFF,	// I/O Mac Win
			eIFT_GIF,	// I/O Mac Win
			eIFT_ICO,	// I/O Mac Win
			eIFT_WMP,	// I/O     Win
			eIFT_JP2,	// I/O Mac
			eIFT_PSD,	// I/O Mac
			eIFT_TGA,	// I/O Mac
			eIFT_ICNS,	// I/O Mac
			eIFT_EXR,	// I/O Mac
			eIFT_SGI,	// I   Mac
			eIFT_PNTG,	// I   Mac
			eIFT_XBM,	// I   Mac
			eIFT_PDF	//   O Mac
		};

		enum EQualityOptionType {
			eQOT_None,
			eQOT_UnitQuality
		};

		struct TImageEncoderCapabilities {
			bool fbPixelSupport1bppBW;
			bool fbPixelSupport8bppGray;
			bool fbRestrictedSizes;
            bool fbImageSupportAlpha;   // transparency support in image
			EQualityOptionType fQualityOptionType;
		};

		struct ImageStream {
			void*	bufferPtr;
			Uint32	bufferSizeInBytes;
			void*	bufferRetinaPtr;
			Uint32	bufferSizeRetinaInBytes;
			CompressionType	compressionType;
		};

		struct CompressedImageDesc {
			TXString		fImageFormatID;
			Uint32			fWidth;
			Uint32			fHeight;
			PixelType		fPixelType;
			Sint16			fBitsPerPixel;
			Sint16			fBitsPerPixel_IfConvertToRawAtBestDepth;
			double			fHRes;
			double			fVRes;
			bool			fbHasAlpha;
			Sint16			fNumColors;
			GSColorTable	fColorTable;
		};

		class IRawImage;

		// ----------------------------------------------------------------------------------------------------
		// {F1620FEA-3AA4-4E0F-A7FF-715958BE72BD}
		static const VWIID IID_CompressedImage = { 0xF1620FEA, 0x3AA4, 0x4E0F, { 0xA7, 0xFF, 0x71, 0x59, 0x58, 0xBE, 0x72, 0xBD } };

		class DYNAMIC_ATTRIBUTE ICompressedImage : public IVWUnknown
		{
		public:
			virtual bool VCOM_CALLTYPE IsInitialized() = 0;

			virtual VCOMError VCOM_CALLTYPE	CreateFromStream(const ImageStream& inImageStream) = 0;	// use only one stream in 'bufferPtr'
			virtual VCOMError VCOM_CALLTYPE	CreateFromStreamN(const ImageStream& inImageStream) = 0; // use 'bufferPtr' or 'bufferRetinaPtr' depending on the current screen 
			virtual VCOMError VCOM_CALLTYPE	CreateFromFile(Filing::IFileIdentifier* inpFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateFromRAWImage(IRawImage* inpIRawImage, CompressionType inCompressionType) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateFromRAWImageEx(IRawImage* inpIRawImage, const TXString& inFormatIDStr, double inQuality/*0<=Q<=1*/) = 0;
			virtual VCOMError VCOM_CALLTYPE CreateFromObject(MCObjectHandle inImageObj) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateFromDrawPad(IDrawPad* inpIDrawPad, CompressionType inCompressionType) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetImageStream(ImageStream& outImageStream) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetBufferPtr(void** outBufferPtr) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetBufferSize(Uint32& outBufferSize) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetCompressionType(CompressionType& outComp) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetCompressedImageDesc(CompressedImageDesc& outImageDesc) = 0;

			virtual VCOMError VCOM_CALLTYPE	Save(Filing::IFileIdentifier* inpFileID) = 0;

			virtual VCOMError VCOM_CALLTYPE CreateBitmapObject(MCObjectHandle& outhObj, bool inUseAlphaChannel=false, bool select=true) = 0;
			virtual VCOMError VCOM_CALLTYPE CreateImageObject(MCObjectHandle& outhObj) = 0;
			virtual VCOMError VCOM_CALLTYPE	UpdateExisting(MCObjectHandle obj, bool doUndo) = 0;

			virtual VCOMError VCOM_CALLTYPE GetImageFormatIDForType(EImageFormatType inType, TXString& outFormatIDStr) = 0;
			virtual VCOMError VCOM_CALLTYPE GetImageFormatTypeForID(const TXString& inFormatIDStr, EImageFormatType& outType) = 0;

			virtual VCOMError VCOM_CALLTYPE GetImageFormatID_SupportedList(TXStringArray& outFormatIDStrList, bool inbForImportOrExport/*true==import*/) = 0;

			virtual VCOMError VCOM_CALLTYPE GetImageFormatID_LocalizedName(const TXString& inFormatIDStr, TXString& outLocName) = 0;
			virtual VCOMError VCOM_CALLTYPE GetImageFormatID_FileExtensions(const TXString& inFormatIDStr, TXStringArray& outExtensions) = 0;
			virtual VCOMError VCOM_CALLTYPE GetImageFormatID_SupportsResolution(const TXString& inFormatIDStr, bool& outbSupportsResolution) = 0;

			virtual VCOMError VCOM_CALLTYPE GetImageFormatID_EncoderCapabilities(const TXString& inFormatIDStr, TImageEncoderCapabilities& outCaps) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<ICompressedImage>		ICompressedImagePtr;
	}
}

#include "../IDrawPad.h"