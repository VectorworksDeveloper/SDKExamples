//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFolderIdentifier.h"
#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		enum class ETraverse
		{
			  NonRecursively
			, NonRecursively_IncludeWorkgroupFolders
			, Recursively
			, Recursively_IncludeWorkgroupFolders
		};

		// ----------------------------------------------------------------------------------------------------
		// {CAFEFEEB-3793-11DB-9C35-00508D5E9851}
		static const VWIID IID_ApplicationFolders = { 0xCAFEFEEB, 0x3793, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };

		class DYNAMIC_ATTRIBUTE IApplicationFolders : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	ForEachFileInStandardFolder(IFolderContentListener* pVisitor, EFolderSpecifier folderSpec) = 0;
			virtual VCOMError VCOM_CALLTYPE ForEachFolderInStandardFolderClass(IFolderContentListener* pVisitor, EFolderSpecifier folderSpec) = 0;
			virtual VCOMError VCOM_CALLTYPE ForEachWorkspaceFileWithDuplicates(IWorkspaceFileInfoListener* pVisitor) = 0;
			virtual VCOMError VCOM_CALLTYPE FindFileInStandardFolder(EFolderSpecifier folderSpec, const TXString& fileName, IFileIdentifier** outFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE FindFileInStandardFolder(EFolderSpecifier folderSpec, const TXString& fileName, const TXString& extension, IFileIdentifier** outFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE GetFileInUserRoot(EFolderSpecifier folderSpec, const TXString& fileName, IFileIdentifier** outFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE GetNumFilesInStandardFolder(EFolderSpecifier folderSpec, size_t& outNumberFiles) = 0;
			virtual VCOMError VCOM_CALLTYPE GetStandardFolderInUserRoot(EFolderSpecifier folderSpec, IFolderIdentifier** outFolderID) = 0;
			virtual VCOMError VCOM_CALLTYPE GetStandardFolderInAppRoot(EFolderSpecifier folderSpec, IFolderIdentifier** outFolderID) = 0;
			virtual VCOMError VCOM_CALLTYPE GetApplicationFolder(IFolderIdentifier** outFolderID) = 0;
			virtual VCOMError VCOM_CALLTYPE GetUserFolder(IFolderIdentifier** outFolderID) = 0;
			virtual VCOMError VCOM_CALLTYPE ClearStandardFolderCache(EFolderSpecifier folderSpec) = 0;

			virtual VCOMError VCOM_CALLTYPE GetWorkgroupFolderCount(size_t & outWorkgroupFolderCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetWorkgroupFolder(size_t index, IFolderIdentifier** outFolderID) = 0;
			virtual VCOMError VCOM_CALLTYPE AddWorkgroupFolder(IFolderIdentifier* intFolderID) = 0;

			virtual VCOMError VCOM_CALLTYPE SearchRootFoldersForRelativePath(const TXString& partialPath, IFileIdentifier** outFileID) = 0;

		public:
			virtual VCOMError VCOM_CALLTYPE IsInStandardFolder(EFolderSpecifier folderSpec, IFileIdentifier* pFileID, IFolderIdentifier** ppOutPath) = 0;
			virtual VCOMError VCOM_CALLTYPE FindFileInPluginFolder(const TXString& fileName, IFileIdentifier** ppOutFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE GetFilePathInStandardFolder(EFolderSpecifier folderSpec, const TXString& fileName, IFileIdentifier** ppOutFileID) = 0;
			virtual	VCOMError VCOM_CALLTYPE GetFilePathInUserRoot(EFolderSpecifier folderClass, const TXString& fileName, IFileIdentifier** ppOutFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE GetFolder(EFolderSpecifier inWhichFolder, IFolderIdentifier** ppOutPath, bool bCreateIfMissing = false) = 0;
			virtual VCOMError VCOM_CALLTYPE GetNamedSubFolder(IFolderIdentifier* pParentFolderID, const TXString& partialPath, IFolderIdentifier** ppOutPath) = 0;

		public:
			virtual VCOMError VCOM_CALLTYPE GetStandardFolderName(EFolderSpecifier folderSpec, TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE ForEachFileInStandardFolderN(EFolderSpecifier folderSpec, const TXString& relativePath, ETraverse traverseOption, IFolderContentListener* pVisitor) = 0;

			enum EFileStandardLocation
			{
				eFileStandardLocation_Application,
				eFileStandardLocation_UserFolder,
				eFileStandardLocation_WorkgroupFolder,
			};

			typedef std::function<void(IFileIdentifier* fileID, const EFileStandardLocation& location)>		TFileCallback;
			typedef std::function<void(IFolderIdentifier* folderID, const EFileStandardLocation& location)>	TFolderCallback;

			virtual VCOMError VCOM_CALLTYPE FindFileInStandardFolderN(EFolderSpecifier folderSpec, const TXString& relativeFilePath, IFileIdentifier** outFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE FindFileInStandardFolderN(EFolderSpecifier folderSpec, const TXString& relativeFilePath, IFileIdentifier** outFileID, EFileStandardLocation& outLocation) = 0;

			// use nullptr when a callback is not defined
			virtual VCOMError VCOM_CALLTYPE	ForEachFileInStandardFolder(EFolderSpecifier folderSpec, TFolderContentCallback_Folder folderCallback, TFolderContentCallback_File fileCallback) = 0;
			virtual VCOMError VCOM_CALLTYPE ForEachFileInStandardFolderN(EFolderSpecifier folderSpec, const TXString& relativePath, ETraverse traverseOption, TFolderContentCallback_Folder folderCallback, TFolderContentCallback_File fileCallback) = 0;
			virtual VCOMError VCOM_CALLTYPE ForEachFolderInStandardFolderClass(EFolderSpecifier folderSpec, TFolderContentCallback_Folder folderCallback, TFolderContentCallback_File fileCallback) = 0;

			virtual VCOMError VCOM_CALLTYPE	ForEachFileInStandardFolders(EFolderSpecifier folderSpec, const TXString& relativeFilePath, TFileCallback fileCallback) = 0;

			/// On Windows, return the system temp folder, the bRequiredPersistent flag is unused;
			// On Mac OS, return the system temp folder: returns /private/tmp if required persistent is true, otherwise returns a non presistent location in /var/folders/. Note that temp folders on Mac OS are wiped upon reboot. 
			virtual VCOMError VCOM_CALLTYPE GetOSSystemTemporaryFolder(IFolderIdentifier** outFolderID, bool bRequirePersistent = true) = 0;

			virtual VCOMError VCOM_CALLTYPE	ForEachFolderInStandardFolders(EFolderSpecifier folderSpec, TFolderCallback folderCallback) = 0;

		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IApplicationFolders>		IApplicationFoldersPtr;
	}
}