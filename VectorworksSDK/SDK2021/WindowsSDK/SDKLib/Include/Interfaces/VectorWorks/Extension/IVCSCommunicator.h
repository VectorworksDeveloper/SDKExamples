//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		enum class PreparationResult
		{
			// We can use DCC functionality.
			kSuccess,
			// This likely means the user cancelled the attempt to sign in, but could also mean SSO was unable to login for any other reason.
			kSSONotSignedIn,
			// We couldn't find (or run) DCC in any of the known locations, including the user provided location. 
			kDCCNotRunning,
			// DCC is running, but it's likely not signed-in or it's not responding. This likely means we just started DCC, but it didn't finish loading yet.
			kDCCNotPrepared
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		// 523AB992-63DD-427C-BC3C-FF42AD6A518D

		static const VWIID IID_VCSCommunicator = { 0x523AB992, 0x63DD, 0x427C, { 0xBC, 0x3C, 0xFF, 0x42, 0xAD, 0x6A, 0x51, 0x8D } };


		class DYNAMIC_ATTRIBUTE IVCSCommunicator : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE LaunchDCC() = 0;
			virtual VCOMError VCOM_CALLTYPE GetStorages(TXString& outS3Folder, TXString& outDropBox) = 0;
			virtual VCOMError VCOM_CALLTYPE PublishFiles(const TXString& publishVwx, const  TXString& outputDir, const TXString& publishJson, const  TXString& p4storageType, const bool& deleteTaskFiles, const TXString& activeVWXfile, const TXString& logFileName) = 0;
			virtual VCOMError VCOM_CALLTYPE CreateJSONFile(const TXStringArray& fileList, const TXStringArray& referencesFileList, const TXStringArray& refMissingFileList, const TXString& fileName) = 0;
			virtual VCOMError VCOM_CALLTYPE GetRelativePaths(const TXStringArray& inLocalPathsArray, const TXString& storageType, TXStringArray& outResultArray, TXStringArray& outInvalidResultArray) = 0;
			virtual VCOMError VCOM_CALLTYPE LogIn() = 0;
			virtual VCOMError VCOM_CALLTYPE IsLoggedIn(bool& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE IsDCCRunning(bool& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE IsDropboxRunning(bool& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE DropboxIntegration() = 0;
			virtual VCOMError VCOM_CALLTYPE GetDropboxAccessType(TXString& outAccessType) = 0;
			virtual VCOMError VCOM_CALLTYPE ResetDCCStatus() = 0;
			virtual VCOMError VCOM_CALLTYPE IsVSSLicensed(bool& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE ShowStatusDialog() = 0;
			virtual VCOMError VCOM_CALLTYPE GetNotSynchronizedFiles(const TXStringArray& inFilesForPublish, const TXString& storageType, TXStringArray& outFilesNotSynchronized) = 0;
			virtual VCOMError VCOM_CALLTYPE SynchronizeFiles(const TXStringArray& inFilesToSynchronize) = 0;
			virtual VCOMError VCOM_CALLTYPE IsDCCResponding(bool& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE GetShareableLink(const TXString& inFilePath, const TXString& inStorageType, TXString& outLink) = 0;
			virtual VCOMError VCOM_CALLTYPE GeneratePanorama(const TXString& vwxFilePath, const TXString& resultFilePath, const TXString& storageType, Uint32 renderMode, RefNumber renderStyle, Uint32 resolutionWidth, bool deleteSource) = 0;
            virtual VCOMError VCOM_CALLTYPE StartGenericJob(const TXString& operation, const TXString& sourceFiles, const TXString& refFiles, const TXString& resultPath, const TXString& storageType, const TXString& options, const TXString& workspaceName, bool deleteSource) = 0;
			// This will ask the user to sign-in if they are signed out in SSO and run DCC if its not already running. 
			// If DCC couldn't be found in the known location, a dialog will ask the user to select a different location.
			// All functionality that needs DCC to be operational should use this function prior to calling everything else.
			virtual PreparationResult VCOM_CALLTYPE Prepare() = 0;
		};

		typedef VCOMPtr<IVCSCommunicator>	IVCSCommunicatorPtr;
	}
}


