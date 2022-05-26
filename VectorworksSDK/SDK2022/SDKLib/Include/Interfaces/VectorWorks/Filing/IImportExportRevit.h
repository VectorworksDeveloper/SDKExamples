//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once


namespace VectorWorks
{
	namespace Filing
	{
		struct SRevitImportOptions
		{
			bool						fActiveViewOnly;
			bool						f3DModelView;
			bool						f2DAnd3DViews;
			bool						fUse3DPolygons;
			bool						fUseSolids;
			bool						fUseMeshes;
			bool						fUseTextures;
			bool						fUseNativeObjects;
		};

		struct SRevitBatchImportOptions
		{
			bool						fIsBatchImport;
			bool						fOneOrMoreRFAFiles;
			bool						fAllRFAFilesInFolder;
			bool						fIncludeSubfolders;
			bool						fCurrentFile;
			bool						fNewFileInFolder;
			TXGenericArray<TXString>	fChosenFileNames;
			TXString					fChooseFolderAll;
			TXString					fChooseFolderNew;
		};

		struct SRevitBatchImportResult
		{
			Uint32						fNumFiles;
			Uint32						fNumImported;
			Uint32						fNumNonRFA;
			Uint32						fNumFailure;
		};

		// {683D5C26-3B32-40B0-BFD0-A3EE595C8A4B}
		static const VWIID IID_ImportExportRevit = { 0x683d5c26, 0x3b32, 0x40b0, { 0xbf, 0xd0, 0xa3, 0xee, 0x59, 0x5c, 0x8a, 0x4b } }; 

		class DYNAMIC_ATTRIBUTE IImportExportRevit : public IVWUnknown
		{
		public:

			virtual VCOMError VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* fileID) = 0;
			virtual VCOMError VCOM_CALLTYPE ImportBatch() = 0;
			virtual VCOMError VCOM_CALLTYPE ImportSilent(IFileIdentifier* fileID, SRevitImportOptions* importOptions = nullptr) = 0;
			virtual VCOMError VCOM_CALLTYPE ImportSilentBatch(SRevitBatchImportOptions* importOptions, SRevitBatchImportResult* importResult = nullptr) = 0;
			virtual VCOMError VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(IFileIdentifier* fileID) = 0;
		};

		typedef VCOMPtr<IImportExportRevit>		IImportExportRevitPtr;
	}
}
