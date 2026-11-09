//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		// predeclare classes
		class IFolderIdentifier;
		class IFileIdentifier;
		
		// ----------------------------------------------------------------------------------------------------
		// {885F311B-3795-11DB-9C35-00508D5E9851}
		static const VWIID IID_FileChooserDialog = { 0x885F311B, 0x3795, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };

		class DYNAMIC_ATTRIBUTE IFileChooserDialog : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	SetTitle(const TXString& title) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetDefaultFile(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetDefaultFileName(const TXString& name) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetDefaultExtension(const TXString& ext) = 0;

			virtual VCOMError VCOM_CALLTYPE	SetInitialFolder(IFolderIdentifier* pFolderID) = 0;

			virtual VCOMError VCOM_CALLTYPE	SetMultiSelect(bool bMultiSelect) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetCheckFileExist(bool bCheckExist) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetCheckFolderExist(bool bCheckExist) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetSelectedFileNamesCount(Uint32& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetSelectedFileName(Uint32 fileIndex, IFileIdentifier** ppOutFileID) = 0;

			virtual VCOMError VCOM_CALLTYPE	ClearFilters() = 0;
			virtual VCOMError VCOM_CALLTYPE	SetAddFileExtInFilter(bool bAddExt) = 0;
			virtual VCOMError VCOM_CALLTYPE	AddFilterAllFiles() = 0;
			virtual VCOMError VCOM_CALLTYPE	AddFilter(const TXString& filterExt, const TXString& filterDesc) = 0;
			virtual VCOMError VCOM_CALLTYPE	AddFilter(const TXStringArray& arrFilterExts, const TXString& filterDesc) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetSelectedFilterIndex(Uint32& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetSelectedFilter(Uint32 index) = 0;

			virtual VCOMError VCOM_CALLTYPE	RunOpenDialog() = 0;
			virtual VCOMError VCOM_CALLTYPE	RunSaveDialog() = 0;

			// VW 2011
			virtual VCOMError VCOM_CALLTYPE SetDescription(const TXString& description) = 0;
			virtual VCOMError VCOM_CALLTYPE SetPermitExtensionHiding(bool canHideExtension) = 0;
			virtual VCOMError VCOM_CALLTYPE AddFileHFSType(Sint32 fileHFSType) = 0;
			virtual VCOMError VCOM_CALLTYPE ShouldExtensionBeHidden(bool& shouldHideExtension) = 0;

			// VW2014
			virtual VCOMError VCOM_CALLTYPE AddFileTypeID(const TXString& inFileTypeIDStr) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IFileChooserDialog>		IFileChooserDialogPtr;
	}
}