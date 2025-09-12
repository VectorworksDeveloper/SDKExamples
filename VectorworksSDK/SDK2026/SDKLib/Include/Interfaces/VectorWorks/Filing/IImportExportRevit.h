//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Filing
	{
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
			kOtherRvtElem,
			kExtrusion,
			kWindowFamily,
			kDoorFamily,
			kToposolid
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
			kRevitEntity,
			kExtrude,
			kWindow,
			kDoor
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
			int											fFileVersion			= 31; // keep in sync with kCurrentFileRelease
			EProcessLocation							fProcessLocation		= eLocalComputer;
			std::map<Uint32, SRevitElementImportOption>	fRVTElem =
			{
				{ (Uint32) ERVTElem::kArcWall,			{ ERVTElem::kArcWall,			true,	EVWObj::kArcWall				} },
				{ (Uint32) ERVTElem::kBasicRoof,		{ ERVTElem::kBasicRoof,			true,	EVWObj::kRoofRoofFace			} },
				{ (Uint32) ERVTElem::kBasicWall,		{ ERVTElem::kBasicWall,			true,	EVWObj::kWall					} },
				{ (Uint32) ERVTElem::kBuildingPad,		{ ERVTElem::kBuildingPad,		true,	EVWObj::kHardscape				} },
				{ (Uint32) ERVTElem::kFamilyInstance,	{ ERVTElem::kFamilyInstance,	true,	EVWObj::kSymbol					} },
				{ (Uint32) ERVTElem::kFloorInterior,	{ ERVTElem::kFloorInterior,		true,	EVWObj::kSlab					} },
				{ (Uint32) ERVTElem::kFloorExterior,	{ ERVTElem::kFloorExterior,		true,	EVWObj::kSlab					} },
				{ (Uint32) ERVTElem::kProfileRoof,		{ ERVTElem::kProfileRoof,		true,	EVWObj::kRoofRoofFace			} },
				{ (Uint32) ERVTElem::kRamp,				{ ERVTElem::kRamp,				true,	EVWObj::kRamp					} },
				{ (Uint32) ERVTElem::kTopography,		{ ERVTElem::kTopography,		true,	EVWObj::kSideModelSiteModifier	} },
				{ (Uint32) ERVTElem::kToposolid,		{ ERVTElem::kToposolid,		    true,	EVWObj::kSideModelSiteModifier	} },
				{ (Uint32) ERVTElem::kOtherRvtElem,		{ ERVTElem::kOtherRvtElem,		true,	EVWObj::kRevitEntity			} }
			};
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

		struct SRevitExportOptions
		{
			bool						fbIsRvt			= true;
			bool						fbIsRfa			= false;
			Uint16						fRevitVersion	= 2024;
			bool						fbExportOnCloud	= false;
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
			virtual VCOMError	VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError	VCOM_CALLTYPE	Import(IFileIdentifierPtr& fileID, const bool bShowUI = true, EImportModeRef importMode = EImportModeRef::Normal) override = 0;
			virtual VCOMError	VCOM_CALLTYPE	ImportCloud( IFileIdentifierPtr& fileID, const std::unique_ptr<nlohmann::json>& importSettings ) override { return kVCOMError_NotImplemented; };
			virtual VCOMError	VCOM_CALLTYPE	ImportBatch() = 0;
			virtual VCOMError	VCOM_CALLTYPE	ImportSilent(IFileIdentifier* fileID, SRevitImportOptions* importOptions = nullptr) = 0;
			virtual VCOMError	VCOM_CALLTYPE	ImportSilentBatch(SRevitBatchImportOptions* importOptions, SRevitBatchImportResult* importResult = nullptr) = 0;
			virtual VCOMError	VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError	VCOM_CALLTYPE	ExportCloud(IFileIdentifierPtr& fileID, const std::unique_ptr<nlohmann::json>& exportSettings) override { return kVCOMError_NotImplemented; };
			virtual VCOMError	VCOM_CALLTYPE	ShowImportOptionsDialog(IFileIdentifier* pFileID) override = 0;
			virtual bool		VCOM_CALLTYPE	IsRevitImport() = 0;

		public:
			static const OSType kRefRVTDataType = 'RRVT';
        };

		typedef VCOMPtr<IImportExportRevit>		IImportExportRevitPtr;
	}
}
