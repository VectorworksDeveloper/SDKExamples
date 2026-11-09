//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		struct SExportPDFOptions
		{
		public:
			SExportPDFOptions()	{}

		public:
			enum TExportRangeKind
			{
				eWholeAreaAsOnePage,
				eAllPages,
				ePageRange,
				eCurrentView
			};
			enum TStandardFormat
			{
				ePDF,
				ePDF_A1B,
				// VW2025
				ePDF_A2B,
				ePDF_A2U,
				ePDF_A3B,
				ePDF_A3U,
				ePDF_A4,
				ePDF_A4E
			};

			size_t				fSizeOf = sizeof(SExportPDFOptions);

			TStandardFormat		fStandardFormat = TStandardFormat::ePDF;

			bool				fExportDesignLayersAsPDFLayers = false;
			bool				fExportClassesAsPDFLayers = false;
			bool				fGrayedLayersInitiallyInvisible = false;
			bool				fGrayedLayersWithNormalAttributes = false;

			Sint32				fResolution = 0;				// dpi
			bool				fExportPatternsAtOnScreenResolution = false;

			bool				fDownsampleImages = false;
			Sint32				fDownsampleResolution = 0;		// dpi
			bool				fApplyJPEG = false;

			bool				fRasterizeText = false;
			bool				fSubsetFonts = false;

			Sint32				fOpacityForTransferModes = 0;	// percent

			bool				fOpenInViewer = false;	// stored in saved settings

			TExportRangeKind	fExportRangeKind = TExportRangeKind::eWholeAreaAsOnePage;
			Sint32				fExportRangeFromPage = 0;
			Sint32				fExportRangeToPage = 0;

			bool				fUpdateViewports = false;
			bool				fResetPluginObjects = false;
			bool				fRecalculateWorksheets = false;
		};


		// ----------------------------------------------------------------------------------------------------
		// {A8C57AB6-01D5-4D4B-8255-47D98C35E42B}
		static const VWIID IID_ExportPDF = { 0xa8c57ab6, 0x1d5, 0x4d4b, { 0x82, 0x55, 0x47, 0xd9, 0x8c, 0x35, 0xe4, 0x2b } };

		class DYNAMIC_ATTRIBUTE IExportPDF : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	OpenPDFDocument(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	ClosePDFDocument() = 0;

			virtual VCOMError VCOM_CALLTYPE	ExportPDFPages(const TXString& name) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetOptions(SExportPDFOptions& outOptions) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetOptions(const SExportPDFOptions& options) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetOptionsWithUI() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetRootMetaData(const TXString& metaData) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IExportPDF>		IExportPDFPtr;
	}
}
