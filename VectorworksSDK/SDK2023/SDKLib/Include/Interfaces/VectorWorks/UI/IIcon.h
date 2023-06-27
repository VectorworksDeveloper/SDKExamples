//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

// This is only intended to be made available to the WorkspaceEditor
namespace VectorWorks
{
	namespace UI
	{
		// ----------------------------------------------------------------------------------------------------
		struct IconStream : public VectorWorks::Imaging::ImageStream
		{
			IconStream()
			{
				bufferPtr = nullptr;
				bufferRetinaPtr = nullptr;
				bufferSizeInBytes = 0;
				bufferSizeRetinaInBytes = 0;
				compressionType = VectorWorks::Imaging::eUnsupported;
			}

			~IconStream()
			{
				delete[](Uint8*)bufferPtr;
				delete[](Uint8*)bufferRetinaPtr;
			}
		};

		// ----------------------------------------------------------------------------------------------------
		// {7E8C933D-CC09-4202-B14F-EFFB04FA4423}
		static const VWIID IID_Icon = { 0x7E8C933D, 0xCC09, 0x4202, { 0xB1, 0x4F, 0xEF, 0xFB, 0x04, 0xFA, 0x44, 0x23 } };

		class DYNAMIC_ATTRIBUTE IIcon : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE IsSet(bool& outResult)												= 0;
			virtual VCOMError VCOM_CALLTYPE GetDimensions(Sint16& outWidth, Sint16& outHeight)					= 0;
			virtual VCOMError VCOM_CALLTYPE Deprecated3(Sint16 inResId, Sint16 inWidth, Sint16 inHeight)		= 0;
			virtual VCOMError VCOM_CALLTYPE SetFromPngData(const void* inPngData,
                                                           size_t inPngDataSize,
                                                           const void* inPngDataRetina = 0,
                                                           size_t inPngDataSizeRetina = 0)                      = 0;
			virtual VCOMError VCOM_CALLTYPE GetPngData(void* outPngData,
                                                       size_t& inOutPngDataSize,
                                                       void* outPngDataRetina,
                                                       size_t& inOutPngDataSizeRetina)                          = 0;
			
			/** GetNativeIcon
			 	@param handle on return it will be a NSImage* on Mac OS X, and a HICON on Windows.
			 	@returns kVCOMError_NoError if the operation was successful.
			*/
			virtual VCOMError VCOM_CALLTYPE GetNativeIcon(void*& handle)										= 0;
            virtual VCOMError VCOM_CALLTYPE GetTXImage(void*& outHandle)                                        = 0;
			virtual VCOMError VCOM_CALLTYPE SetFromResourceSpecifier(const TXString& imageSpecifier, Sint16 width = 0, Sint16 height = 0) = 0;
            virtual VCOMError VCOM_CALLTYPE SetFromAbsolutePath(const TXString& path) = 0;
            virtual VCOMError VCOM_CALLTYPE GetScaledNativeIcon(void*& /*handle*/)								= 0;

		// Vectorworks 2020
		public:
			virtual VCOMError VCOM_CALLTYPE GetPngImageStream(IconStream& outStream)							= 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IIcon>		IIconPtr;
	}
}
