//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		enum class EExportMode : Sint16
		{
			eDWGDXF			= 0,
			eDWF			= 1,
			eBatchDWGDXF	= 2,
			eBatchDWF		= 3
		};
		
		enum class EDXFExportFileType : Sint16
		{ 
			eDXF	= 0, 
			eBDXF	= 1, 
			eDWG	= 2 
		};

		enum class EDWFExportFileType : Sint16
		{ 
			eDWF	= 0, 
			eBDWF	= 1, 
			eCBDWF	= 2, 
			e3DDWF	= 3, 
			eDWFx	= 4 
		};

		// This is used by the export version menu, 1 = first menu item, always the latest supported version
		enum class EDXFExportVersion : Sint16
		{
			kEV_MinLegalValue	= 1, 
			kEV_2018			= 1,
			kEV_2013			= 2,
			kEV_2011			= 3,
			kEV_2010			= 4,
			kEV_2007			= 5,
			kEV_2004			= 6,
			kEV_2000			= 7,
			kEV_14				= 8,
			kEV_13				= 9,
			kEV_12				= 10,
			kEV_11				= 11,
			kEV_10				= 12,
			kEV_9				= 13,
			kEV_2pt6			= 14,
			kEV_2pt5			= 15,
			kEV_MaxLegalValue	= 15,
		};

		enum class EDWFExportVersion : Sint16
		{
			kEV_42	= 1,
			kEV_55	= 2,
			kEV_600 = 3,
			kEV_601 = 4,
			kEV_602 = 5
		};

		enum class EExportInModelSpaceMode : Sint16
		{
			ePreserveStructure	= 0,
			eClippedGraphics	= 1,
			ePDFLike			= 2,
		};

		struct SExportOptionsForPublish
		{
			EExportMode					fWritingMode;
			EDXFExportFileType			fFileType;
			EDXFExportVersion			fVersion;
			EDWFExportFileType			fDWFFileType;
			EDWFExportVersion			fDWFVersion;
			bool						fDecompose3DSymsToPolys;
			bool						fExpClassesAsLayers;
			bool						fCreateInvisibleDXFLayers;
			bool						fRescaleLayers;					
			Sint16						fExportLayerHandling;			
			bool						fMapLineWeightsToColors;
			bool						fUseTrueColors;
			bool						fExport2DFills;
			bool						fExportImages;
			bool						fExportImageFills;
			bool						fExportTileFills;
			bool						fPreserveFills;		
			bool						fExportHatches;
			bool						fExportHatchPatternFiles;	
			bool						fExportSolidsAsSAT;				
			bool						fExportHatchesInSeparateLayer;
			bool						fCreateXRefsForDLVPs;			
			bool						fCreateFilesForLayers;
			bool						fViewportsAs2DGraphicsInMS;		
			bool						fGroupsAsAnonymousBlocks;
			bool						fExportSelectedObjects;			
			bool						fExportProjectedObjects;		
			bool						fPreserveMappedFont;			
			bool						fComplexLTsAsBlocks;			
			bool						fPreserveSIADimsTextAppearance;	
			bool						fDlvpClassesAsOneLayer;
			bool						fUseClassOverrides;
			bool						fFilesInSubFolder;
			TXString					fSettingsName;
			TXString					fCLMappingName;
			bool						fCreateSeparateFolder;
			bool						fUpdateViewports;
			bool						fResetAllPluginObjects;
			bool						fRecalculateWS;
			bool						fCustomLocation;
			TXString					fDefaultLocationPath;
			bool						fSupportSIADimensions;
			bool						fApproximatePolylineToArcs;
			bool						fPluginsDecomposeAll;	
			Uint32						fPluginsDecomposeIDs;
			EExportInModelSpaceMode		fExportInModelSpaceMode;
			bool						fUseFirstViewportScale;
			double						fUsedScaleForViewportsInSheetLayer;
			bool						fUseObjectVisibilityInViewports;
			bool						fCreateExternalImageFiles;
			bool						fExportRecordFormats;
			bool						fExportRecordFormatsLinkedOnly;
		};

		enum EImportMode 
		{
			eDWGImportNormal,
			eDWGImportBatch,
			eDWGImportAsSymbol,
			eDWGImportAsReference,
			eDWGDoTheReference,
			eDWGCreateSymbolDef,
			eDWGInvalidImportMode
		};

		enum class EDWGSymbolOrigin
		{
			FileOrigin,
			PlanProjectionCenter
		};
		
		// ----------------------------------------------------------------------------------------------------
		// {263BD4CD-417F-4fc0-8BEE-9CBFF95FDC76}
		static const VWIID IID_IImportExportDWG = { 0x2f790ffd, 0x416d, 0x428b, { 0x93, 0xa0, 0xff, 0xe5, 0x79, 0x8, 0x0, 0x71 } }; 
		
		class DYNAMIC_ATTRIBUTE IImportExportDWG : public IImportReference
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID, const bool isSilentDWGImport) = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(EImportMode importMode, IFileIdentifier* pFileID, const bool isSilentDWGImport, MCObjectHandle hSymbolFolder = nullptr, EDWGSymbolOrigin symbolOrigin = EDWGSymbolOrigin::FileOrigin) = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifierPtr& pFileID, const bool bShowUI, EImportModeRef importMode) override = 0;
			virtual VCOMError VCOM_CALLTYPE	ImportSelectedFile(IFileIdentifier* pFileID, const bool isSilentDWGImport) = 0;
			virtual VCOMError VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(short exportMode , IFolderIdentifier** pFolderID, const TXString& displayName, SExportOptionsForPublish* ioExportOptions = nullptr, const bool isSilentExport = false) = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsDXFImport(bool& isDXFImport) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsDXFExport(bool& isDXFExport) = 0;
			virtual VCOMError VCOM_CALLTYPE	ShowExportOptionsDialog(EExportMode exportMode, SExportOptionsForPublish* ioExportOptions = nullptr, TXGenericArray<TXString>* inClassNames = nullptr) = 0;
			virtual VCOMError VCOM_CALLTYPE	ShowImportOptionsDialog(IFileIdentifier* pFileID) override = 0;
			virtual VCOMError VCOM_CALLTYPE IsImportExportAborted(bool& outExportAbort) = 0;

			// 2017
			virtual VCOMError VCOM_CALLTYPE	ImportAsSymbolDef(IFileIdentifier* pFileID, const bool isSilentDWGImport, const TXString& progressBarLabel, TXString& outSymbolDefName, EDWGSymbolOrigin inSymbolOrigin = EDWGSymbolOrigin::FileOrigin) = 0;
			virtual VCOMError VCOM_CALLTYPE IsLastImportedFileUnitless(bool& isFileUnitless) = 0;

			// 2023
			virtual VCOMError VCOM_CALLTYPE InitExportOptions(EExportMode exportMode, SExportOptionsForPublish* ioOptions) = 0;

			//2026
			virtual VCOMError VCOM_CALLTYPE	GetExportMode(EExportMode& exportMode) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportDWG>		IImportExportDWGPtr;
	}
}
