//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

//#include "../../Core/Source/Interfaces/VectorWorks/Filing/ImportReference.h"

namespace VectorWorks
{
	namespace Filing
	{
		enum ERVTImportMode : Sint16
		{
			Normal,
			AsReference = 1,
			Invalid
		};

		// -----------------------------------------------------------------------------------
		enum class EImportSerialization : size_t
		{
			kMinimumLegalValue,
			kActiveViewOnly = kMinimumLegalValue,
			k3DModelView,
			k2DAnd3DViews,
			kNativeObjects,
			kMeshes,
			k3DPolygons,
			kSolids,
			kTextures,
			kMaximumLegalValue
		};

		enum class ERVTElem
		{
			kArcWall,
			kBasicRoof,
			kBasicWall,
			kBuildingPad,
			kFamilyInstance,
			kFloorInterior,
			kFloorExterior,
			kProfileRoof,
			kRamp,
			kTopography,
			kOtherRvtElem
		};

		enum class EVWObj
		{
			kArcWall,
			kRoofRoofFace,
			kWall,
			kHardscape,
			kLandscape,
			kSymbol,
			kSlab,
			kRamp,
			kSideModelSiteModifier,
			kRevitEntity
		};

		// -----------------------------------------------------------------------------------
        static const SImportRefDlgBehavior importRefDlgBehaviorRVT = {
			false,	// fShowOptionsBtnOnEditReference
			true	// fShowUIOnReferenceUpdate
        };
		// -----------------------------------------------------------------------------------
		struct SRevitElementImportOption
		{
			ERVTElem					fRvtElemType;
			bool						fCreate;
			EVWObj						fVWObjectIndex;
		};
		
		struct SRevitImportOptions : public SImportRefDlgSettings
		{
			const SRevitImportOptions&	GetImportOptions() const	{ return *this; }
			SRevitImportOptions&		GetImportOptions()			{ return *this; }
			void						SetImportOptions( const SRevitImportOptions& importOptions )
			{
				*this = importOptions;
			}
			void						SetRefImportOptions( const SImportRefDlgSettings& importOptions )
			{
				SImportRefDlgSettings::operator=( importOptions );
			}

			bool										f3DModel				= true; //Default
			bool										f2DViews	     		= false;
			bool										fUse3DPolygons			= false;
			bool										fUseSolids				= false;
			bool										fUseMeshes				= true;
			bool										fUseTextures			= true;
			bool										fPrefixForClassesCheck	= false;
			TXString									fPrefixForClassesText;
			std::map<Uint32, SRevitElementImportOption>	fRVTElem;

			//ERVTImportMode				fImportMode				= ERVTImportMode::Normal;

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


		// -----------------------------------------------------------------------------------
		// {683D5C26-3B32-40B0-BFD0-A3EE595C8A4B}
		static const VWIID IID_ImportExportRevit = { 0x683d5c26, 0x3b32, 0x40b0, { 0xbf, 0xd0, 0xa3, 0xee, 0x59, 0x5c, 0x8a, 0x4b } }; 

		class DYNAMIC_ATTRIBUTE IImportExportRevit : public IImportReference
		{
		public:
			IImportExportRevit(): IImportReference( importRefDlgBehaviorRVT ) { }

			virtual VCOMError	VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError	VCOM_CALLTYPE	Import(IFileIdentifierPtr& fileID, const bool bShowUI = true, Sint16 importMode = ERVTImportMode::Normal) override = 0;
			virtual VCOMError	VCOM_CALLTYPE	ImportBatch() = 0;
			virtual VCOMError	VCOM_CALLTYPE	ImportSilent(IFileIdentifier* fileID, SRevitImportOptions* importOptions = nullptr) = 0;
			virtual VCOMError	VCOM_CALLTYPE	ImportSilentBatch(SRevitBatchImportOptions* importOptions, SRevitBatchImportResult* importResult = nullptr) = 0;
			virtual VCOMError	VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError	VCOM_CALLTYPE	Export(IFileIdentifier* fileID) = 0;
			virtual VCOMError	VCOM_CALLTYPE	ShowImportOptionsDialog(IFileIdentifier* pFileID) override = 0;
			virtual bool		VCOM_CALLTYPE	IsRevitImport() = 0;

		protected:
			virtual VCOMError	VCOM_CALLTYPE	GetFileWithFileChooser( IFileIdentifierPtr& fileID ) = 0;
			virtual bool		VCOM_CALLTYPE	DetermineSettingsToUse( bool quietly ) = 0;

		public:
			static const OSType kRefRVTDataType = 'RRVT';
        };

		typedef VCOMPtr<IImportExportRevit>		IImportExportRevitPtr;
	}
}
