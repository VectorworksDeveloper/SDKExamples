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
			SExportPDFOptions()			{ fSizeOf = sizeof(SExportPDFOptions); }

		public:
			enum TExportRangeKind
			{
				eWholeAreaAsOnePage,
				eAllPages,
				ePageRange,
				eCurrentView
			};
			enum TStandardFormat {
				ePDF,
				ePDFA_1B
			};

			size_t				fSizeOf;

			TStandardFormat		fStandardFormat;

			bool				fExportDesignLayersAsPDFLayers;
			bool				fExportClassesAsPDFLayers;
			bool				fGrayedLayersInitiallyInvisible;
			bool				fGrayedLayersWithNormalAttributes;

			Sint32				fResolution;				// dpi
			bool				fExportPatternsAtOnScreenResolution;

			bool				fDownsampleImages;
			Sint32				fDownsampleResolution;		// dpi
			bool				fApplyJPEG;

			bool				fRasterizeText;
			bool				fSubsetFonts;

			Sint32				fOpacityForTransferModes;	// percent

			bool				fOpenInViewer;	// stored in saved settings

			TExportRangeKind	fExportRangeKind;
			Sint32				fExportRangeFromPage;
			Sint32				fExportRangeToPage;

			bool				fUpdateViewports;
			bool				fResetPluginObjects;
			bool				fRecalculateWorksheets;
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
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IExportPDF>		IExportPDFPtr;
	}
}
