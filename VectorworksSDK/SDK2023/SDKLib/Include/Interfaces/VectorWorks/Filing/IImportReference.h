#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		struct SImportRefDlgBehavior
		{
            SImportRefDlgBehavior(const bool showImportBtnOnEdit = true, const bool showUIOnUpdate = false):
				fShowOptionsBtnOnEditReference( showImportBtnOnEdit ),
				fShowUIOnReferenceUpdate( showUIOnUpdate )
            {}
			//When import options are not file dependent and does not require to load the file first, then show the Options dialog in the Edit Reference dialog
			bool	fShowOptionsBtnOnEditReference; 
			//Do not show Options dialog during Reference Update
			bool	fShowUIOnReferenceUpdate;
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
			Sint16				fImportMode				= 0 /*Normal*/;
			IFileIdentifierPtr	fpFileID				= nullptr;
			TXString			fSubscribePathname;
		};

		// ---------------------------------------------------------------------------------------------------
		// {201692B9-563A-4D99-93F3-28678B7D14C7}
		static const VWIID IID_ImportReferenceSupport = { 0x201692b9, 0x563a, 0x4d99, { 0x93, 0xf3, 0x28, 0x67, 0x8b, 0x7d, 0x14, 0xc7 } };

		/* Utility class with support functions for the file referencing
		 * SetRefDataType must be called right after the object creation
		 */
		class DYNAMIC_ATTRIBUTE IImportReferenceSupport : public VCOMImpl<IVWSingletonUnknown>
		{
		public:
			// must be called right after the object creation
			virtual void		VCOM_CALLTYPE	SetRefDataType( const OSType refDataType ) = 0;

			// must be called before the other getters/setters
			virtual VCOMError	VCOM_CALLTYPE	LoadRefSettings() = 0;
			virtual VCOMError	VCOM_CALLTYPE	SaveRefSettings() = 0;

			virtual void		VCOM_CALLTYPE	GetRefSettingsOut( SImportRefDlgSettings& settings ) const = 0;
			virtual void		VCOM_CALLTYPE	SetRefSettings( const SImportRefDlgSettings& settings ) = 0;
			virtual void		VCOM_CALLTYPE	SetGroupID( const /*TDataIdentifier*/ Uint16 groupID ) = 0;
			virtual VCOMError	VCOM_CALLTYPE	SaveSettings() = 0;
			
			virtual VCOMError	VCOM_CALLTYPE	Import( IFileIdentifierPtr& fileID, const bool bShowUI, Sint16 importMode ) = 0;

			// a set of gets that return success
			virtual bool		VCOM_CALLTYPE	GetValueOut	( bool& outValue,		size_t valueIndex ) const = 0;
			virtual bool		VCOM_CALLTYPE	GetValueOut	( Sint8& outValue,		size_t valueIndex ) const = 0;
			virtual bool		VCOM_CALLTYPE	GetValueOut	( Uint8& outValue,		size_t valueIndex ) const = 0;
			virtual bool		VCOM_CALLTYPE	GetValueOut	( Sint16& outValue,		size_t valueIndex ) const = 0;
			virtual bool		VCOM_CALLTYPE	GetValueOut	( Uint16& outValue,		size_t valueIndex ) const = 0;
			virtual bool		VCOM_CALLTYPE	GetValueOut	( Sint32& outValue,		size_t valueIndex ) const = 0;
			virtual bool		VCOM_CALLTYPE	GetValueOut	( Uint32& outValue,		size_t valueIndex ) const = 0;
			virtual bool		VCOM_CALLTYPE	GetValueOut	( size_t& outValue,		size_t valueIndex ) const = 0;
			virtual bool		VCOM_CALLTYPE	GetValueOut	( double& outValue,		size_t valueIndex ) const = 0;
			virtual bool		VCOM_CALLTYPE	GetValueOut	( TXString& outValue,	size_t valueIndex ) const = 0;

			virtual bool		VCOM_CALLTYPE	GetValueMemory	(std::vector<char>& outValue, size_t valueIndex) const = 0;

			// a set of sets
			virtual void		VCOM_CALLTYPE	SetValue	( bool value,				size_t valueIndex ) = 0;
			virtual void		VCOM_CALLTYPE	SetValue	( Sint8 value,				size_t valueIndex ) = 0;
			virtual void		VCOM_CALLTYPE	SetValue	( Uint8 value,				size_t valueIndex ) = 0;
			virtual void		VCOM_CALLTYPE	SetValue	( Sint16 value,				size_t valueIndex ) = 0;
			virtual void		VCOM_CALLTYPE	SetValue	( Uint16 value,				size_t valueIndex ) = 0;
			virtual void		VCOM_CALLTYPE	SetValue	( Sint32 value,				size_t valueIndex ) = 0;
			virtual void		VCOM_CALLTYPE	SetValue	( Uint32 value,				size_t valueIndex ) = 0;
			virtual void		VCOM_CALLTYPE	SetValue	( size_t value,				size_t valueIndex ) = 0;
			virtual void		VCOM_CALLTYPE	SetValue	( double value,				size_t valueIndex ) = 0;
			virtual void		VCOM_CALLTYPE	SetValue	( const TXString& value,	size_t valueIndex ) = 0;

			virtual void		VCOM_CALLTYPE	SetValueMemory	( const std::vector<char>& value, size_t valueIndex ) = 0;
		};
		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportReferenceSupport>		IImportRefSupportPtr;


		// ---------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IImportReference : public VCOMImpl<IVWSingletonUnknown>
		{
		public:
			IImportReference( const SImportRefDlgBehavior& importRefBehavior ): fImportRefDlgBehavior(importRefBehavior) { }

			virtual VCOMError	VCOM_CALLTYPE	GetGISSupport() { return kVCOMError_NoError; }
			virtual VCOMError	VCOM_CALLTYPE	SetGISSupport() { return kVCOMError_NoError; }

			virtual VCOMError	VCOM_CALLTYPE	Import( IFileIdentifierPtr& fileID, const bool bShowUI, Sint16 importMode ) = 0;
			virtual VCOMError	VCOM_CALLTYPE	ShowImportOptionsDialog( IFileIdentifier* pFileID ) { return kVCOMError_NotImplemented; }

			const SImportRefDlgBehavior			fImportRefDlgBehavior;
			IImportRefSupportPtr				fpImportRefSupport = IImportRefSupportPtr( IID_ImportReferenceSupport );
		};
		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportReference>		IImportReferencePtr;
	}
}
