#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		enum EImportModeRef
		{
			// We need to keep these the same as EImportMode in DWG. For compatibility reasons
			Normal,
			Batch,
			AsSymbol,
			AsReference,
			DoTheReference,
			CreateSymbolDef,
			Invalid,

			ConvertNoReference,
			VectorworksCloud,
			VectorworksCloudBatch
		};

		enum EProcessLocation: Sint16
		{
			eLocalComputer,
			eVectorworksCloud
		};

		struct SImportRefDlgBehavior
		{
			//When import options are not file dependent and does not require to load the file first, then show the Options dialog in the Edit Reference dialog
			bool	fShowOptionsBtnOnEditReference	= false; 
			//Do not show Options dialog during Reference Update
			bool	fShowUIOnReferenceUpdate		= true;
		};
		
		// ---------------------------------------------------------------------------------------------------
		struct SImportRefDlgSettings
		{
			bool				fbReferenceCheck		= false;
			bool				fbAbsoluteRefPathRadio	= true;
			bool				fbRelativeRefPathRadio	= false;
			bool				fbSaveCacheCheck		= false;
			bool				fbAutoUpdateCheck		= true;
			TXString			fPSSRelativePath;
			TXString			fPSSTempFilePath;
			EImportModeRef		fImportMode				= EImportModeRef::Normal;
			IFileIdentifierPtr	fpFileID				= nullptr;
			TXString			fSubscribePathname;
		};

		// ---------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IImportReference : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError				VCOM_CALLTYPE	GetGISSupport() { return kVCOMError_NoError; }
			virtual VCOMError				VCOM_CALLTYPE	SetGISSupport() { return kVCOMError_NoError; }

			virtual VCOMError				VCOM_CALLTYPE	Import( IFileIdentifierPtr& fileID, const bool bShowUI, EImportModeRef importMode ) = 0;
			virtual VCOMError				VCOM_CALLTYPE	ImportCloud( IFileIdentifierPtr& fileID, const std::unique_ptr<nlohmann::json>& importSettings ) { return kVCOMError_NotImplemented; };
			virtual VCOMError				VCOM_CALLTYPE	ExportCloud( IFileIdentifierPtr& fileID, const std::unique_ptr<nlohmann::json>& exportSettings ) { return kVCOMError_NotImplemented; };

			virtual VCOMError				VCOM_CALLTYPE	ShowImportOptionsDialog( IFileIdentifier* pFileID ) { return kVCOMError_NotImplemented;	}
			virtual SImportRefDlgBehavior	VCOM_CALLTYPE	GetImportRefDlgBehavior() const						{ return SImportRefDlgBehavior();	}
		};
		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportReference>		IImportReferencePtr;
	}
}
