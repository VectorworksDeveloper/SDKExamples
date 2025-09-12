//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once


namespace VectorWorks
{
	namespace Filing
	{
		struct SPublishOptions
		{
			bool fDoPDFOnly						= false;
			bool fOpenDestinationFolder			= false;
			bool fCreateFolderForeachFiletype	= false;
		};

		struct SPublishSetInfo
		{
			TXString fItemName;
			TXString fFilePath;
		};
		using TPublishSetInfoArr		= std::vector<SPublishSetInfo>;
		using TStrToPublishSetInfoUMap	= std::unordered_map<TXString, TPublishSetInfoArr>;

		// {B5C21FF5-0A2C-498B-B876-90521EEC3BA6}
		static const VWIID IID_Publish = { 0xb5c21ff5, 0xa2c, 0x498b, { 0xb8, 0x76, 0x90, 0x52, 0x1e, 0xec, 0x3b, 0xa6 } };

		class DYNAMIC_ATTRIBUTE IPublish : public IVWUnknown
		{
		public:

			virtual VCOMError VCOM_CALLTYPE	Publish(IFolderIdentifier* outServerFolder) = 0;
			virtual VCOMError VCOM_CALLTYPE RunDCC(bool& isStarted) = 0;
			virtual VCOMError VCOM_CALLTYPE DoingPublish(bool& bDoingPublish) = 0;
			virtual VCOMError VCOM_CALLTYPE DoingCloudPublish(bool& bDoingCloudPublish) = 0;	
			virtual VCOMError VCOM_CALLTYPE PublishSavedSet(const TXString& savedSetName, IFolderIdentifier* outputFolder) = 0;
			virtual VCOMError VCOM_CALLTYPE PreparingCloudPublish(bool& bPreparingCloudPublish) = 0;
			virtual VCOMError VCOM_CALLTYPE PublishSavedSet(const TXString& savedSetName, IFolderIdentifier* outputFolder, const SPublishOptions& publishOptions, TXStringArray& outResultFilePaths) = 0;
			virtual VCOMError VCOM_CALLTYPE GetPublishSavedSets(TStrToPublishSetInfoUMap& outPublishSetInfoMap) = 0;
			virtual VCOMError VCOM_CALLTYPE PublishWithUI(IFileIdentifier* outputFileID, bool showResultDetailsDlg, std::vector<IFileIdentifierPtr>& outResultFileIDs) = 0;
		};

		typedef VCOMPtr<IPublish>		IPublishPtr;
	}
}
