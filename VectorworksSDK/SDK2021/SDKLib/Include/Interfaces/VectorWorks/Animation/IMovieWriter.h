//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
    namespace Filing
    {
        class IFileIdentifier;
    }
    
    namespace Imaging
    {
        class IRawImage;
        class ICompressedImage;
    }
}
    
namespace Animation
{
    class Animator;

	enum class ESaveOptions {
		LocalStorage,
		VWCloudStorage,
		DropboxStorage
	};
    enum EMovieWriterFormat     // not all movie formats available on all operating system versions
    {
        eMovieWriterFormatMOV = 0,			// ".mov"	 (QuickTime Movie File format -- independent of QT library)
        eMovieWriterFormatMPEG4 = 1,        // ".mp4"    (MPEG4 - Motion Pictures Expert Group v4)
        eMovieWriterFormatM4V = 2,          // ".w4v"    (iTunes)
        eMovieWriterFormatAVI = 3,          // ".avi"    (Audio Video Interleave)
        eMovieWriterFormatWMV = 4           // ".wmv"    (Windows Media Video)
    };

    const double kMovieWriterDefaultFramesPerSecond = 15.0;  // > 0.0
    const double kMovieWriterDefaultQuality = 0.5;    // 0.0 to 1.0

    const VCOMError kVCOMError_MovieWriter_FileNotFound          = 101;   //BUGBUG??   starting error offset
    const VCOMError kVCOMError_MovieWriter_FileAlreadyExists     = 102;
    const VCOMError kVCOMError_MovieWriter_FileNotWritable       = 103;
    const VCOMError kVCOMError_MovieWriter_ImageSizeNotMatch     = 104;
    const VCOMError kVCOMError_MovieWriter_NegativeOrZeroValue   = 105;
    const VCOMError kVCOMError_MovieWriter_FrameNotWritten       = 106;
    const VCOMError kVCOMError_MovieWriter_DependencyNotFound    = 107;    // Windows: Direct Show 'FrameSourceFilter' Not Found or Media Foundation not configured
    const VCOMError kVCOMError_MovieWriter_MovieNotCreated       = 108;
	const VCOMError kVCOMError_MovieWriter_ConfigurationIssue    = 109;
	const VCOMError kVCOMError_MovieWriter_RuntimeIssue			 = 110;


	// ------------------------------------------------------------------------------------------------------------------------------------
	// 1A6C2C14-B1BF-4ACE-9EFC-77C46A814234
	static const VWIID IID_MovieWriter = { 0x1A6C2C14, 0xB1BF, 0x4ACE, { 0x9E, 0xFC, 0x77, 0xC4, 0x6A, 0x81, 0x42, 0x34 } };

	class DYNAMIC_ATTRIBUTE IMovieWriter : public IVWUnknown
	{
	public:
        virtual VCOMError VCOM_CALLTYPE ShowOptions( Animator* animator ) = 0;
        virtual VCOMError VCOM_CALLTYPE ShowOptions( VectorWorks::IDrawPadPtr previewDrawPad, double framesPerSecond, Uint32 framesPerKeyframe ) = 0;   // for scripting interface
        virtual VCOMError VCOM_CALLTYPE GetMovieFormat( EMovieWriterFormat& format, TXString& formatExtension, TXString& formatExtensionDescription ) = 0;
        virtual VCOMError VCOM_CALLTYPE GetMovieFilename( VectorWorks::Filing::IFileIdentifierPtr& pFileID, EMovieWriterFormat& movieFormat, ESaveOptions isSavedOnCloud = ESaveOptions::LocalStorage) = 0;
		virtual VCOMError VCOM_CALLTYPE CreateMovie( VectorWorks::Filing::IFileIdentifierPtr pFileID, Uint32 pixelWidth, Uint32 pixelHeight, EMovieWriterFormat format, bool forceReplace ) = 0;
		virtual VCOMError VCOM_CALLTYPE AdjustFramesPerSecond( double framesPerSecond ) = 0;  // > 0.0
        virtual double	  VCOM_CALLTYPE GetFramesPerSecond() = 0;
		virtual VCOMError VCOM_CALLTYPE AdjustFramesPerKeyFrame( Uint32 framesPerKeyFrame ) = 0;     // for backwards compability with VectorScript
        virtual Uint32    VCOM_CALLTYPE GetFramesPerKeyFrame() = 0;                                  // for backwards compability with VectorScript
		virtual VCOMError VCOM_CALLTYPE AdjustQuality( double quality ) = 0;     // 0.0 to 1.0
        virtual double    VCOM_CALLTYPE GetQuality() = 0;
        virtual VCOMError VCOM_CALLTYPE WriteRawImage( VectorWorks::Imaging::IRawImage* image ) = 0;
		virtual VCOMError VCOM_CALLTYPE WriteCompressedImage( VectorWorks::Imaging::ICompressedImage* image) = 0;
        virtual VCOMError VCOM_CALLTYPE Finalize() = 0;
		virtual VCOMError VCOM_CALLTYPE AdjustFrameSize( Sint32 pixelWidth, Sint32 pixelHeight ) = 0;
		virtual VCOMError VCOM_CALLTYPE GetFrameSize( Sint32& pixelWidth, Sint32& pixelHeight ) = 0;
		virtual VCOMError VCOM_CALLTYPE GetScreenCropSize( ViewRect& screenCropRect ) = 0;
		virtual VCOMError VCOM_CALLTYPE ShowVideoSettings( Animator* animator, bool bDrawCropSize ) = 0;
		//virtual VCOMError VCOM_CALLTYPE ShowVideoSettings( double framesPerSecond, Uint32 framesPerKeyframe, bool bDrawCropSize) = 0;
		virtual VCOMError VCOM_CALLTYPE ShowVideoSettings( double framesPerSecond, Uint32 framesPerKeyframe, Sint32 frameSizeOption, Sint32& pixelWidth, Sint32& pixelHeight, bool bDrawCropSize ) = 0;

    };

    typedef VCOMPtr<IMovieWriter>		IMovieWriterPtr;
}

