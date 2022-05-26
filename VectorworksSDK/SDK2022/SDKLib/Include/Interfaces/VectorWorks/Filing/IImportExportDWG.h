//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		struct SExportOptionsForPublish
		{
			Sint16		fWritingMode;					
			Sint16		fFileType;
			Sint16		fVersion;
			Sint16		fDWFFileType;
			Sint16		fDWFVersion;
			bool		fDecompose3DSymsToPolys;
			bool		fExpClassesAsLayers;
			bool		fCreateInvisibleDXFLayers;
			bool		fRescaleLayers;					
			Sint16		fExportLayerHandling;			
			bool		fMapLineWeightsToColors;
			bool		fUseTrueColors;
			bool		fExport2DFills;
			bool		fExportImages;
			bool		fExportImageFills;
			bool		fExportTileFills;
			bool		fPreserveFills;		
			bool		fExportHatches;
			bool		fExportHatchPatternFiles;	
			bool		fExportSolidsAsSAT;				
			bool		fExportHatchesInSeparateLayer;
			bool		fCreateXRefsForDLVPs;			
			bool		fCreateFilesForLayers;
			bool		fViewportsAs2DGraphicsInMS;		
			bool		fGroupsAsAnonymousBlocks;
			bool		fExportSelectedObjects;			
			bool		fExportProjectedObjects;		
			bool		fPreserveMappedFont;			
			bool		fComplexLTsAsBlocks;			
			bool		fPreserveSIADimsTextAppearance;	
			bool		fDlvpClassesAsOneLayer;
			bool		fUseClassOverrides;
			bool		fFilesInSubFolder;
			TXString	fSettingsName;
			TXString	fCLMappingName;
		};

		enum EExportMode
		{
			eExportDWGDXF,
			eExportDWF,
			eBatchExportDWGDXF,
			eBatchExportDWF,
		};

		enum EImportMode 
		{
			eDWGImportNormal,
			eDWGImportBatch,
			eDWGImportAsSymbol,
			eDWGImportAsReference,
			eDWGDoTheReference,
			eDWGCreateSymbolDef
		};

		enum class EDWGSymbolOrigin
		{
			FileOrigin,
			PlanProjectionCenter
		};

		// ----------------------------------------------------------------------------------------------------
		// {263BD4CD-417F-4fc0-8BEE-9CBFF95FDC76}
		static const VWIID IID_IImportExportDWG = { 0x2f790ffd, 0x416d, 0x428b, { 0x93, 0xa0, 0xff, 0xe5, 0x79, 0x8, 0x0, 0x71 } }; 
		
		class DYNAMIC_ATTRIBUTE IImportExportDWG : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID, const bool isSilentDWGImport) = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(EImportMode importMode, IFileIdentifier* pFileID, const bool isSilentDWGImport, MCObjectHandle hSymbolFolder = nullptr, EDWGSymbolOrigin symbolOrigin = EDWGSymbolOrigin::FileOrigin) = 0;
			virtual VCOMError VCOM_CALLTYPE	ImportSelectedFile(IFileIdentifier* pFileID, const bool isSilentDWGImport) = 0;
			virtual VCOMError VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(short exportMode , IFolderIdentifier** pFolderID, const TXString& displayName, SExportOptionsForPublish* ioExportOptions = nullptr) = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsDXFImport(bool& isDXFImport) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsDXFExport(bool& isDXFExport) = 0;
			virtual VCOMError VCOM_CALLTYPE	ShowExportOptionsDialog(EExportMode exportMode, SExportOptionsForPublish* ioExportOptions = nullptr, TXGenericArray<TXString>* inClassNames = nullptr) = 0;
			virtual VCOMError VCOM_CALLTYPE	ShowImportOptionsDialog(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE IsImportExportAborted(bool& outExportAbort) = 0;

			// 2017
			virtual VCOMError VCOM_CALLTYPE	ImportAsSymbolDef(IFileIdentifier* pFileID, const bool isSilentDWGImport, const TXString& progressBarLabel, TXString& outSymbolDefName) = 0;
			virtual VCOMError VCOM_CALLTYPE IsLastImportedFileUnitless(bool& isFileUnitless) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportDWG>		IImportExportDWGPtr;
	}
}
