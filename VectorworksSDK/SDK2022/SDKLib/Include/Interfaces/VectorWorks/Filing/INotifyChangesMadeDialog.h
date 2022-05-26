//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		enum ENotifyChangesMadeResult {
			eNotifyChangesMadeResult_UnknownError,
			eNotifyChangesMadeResult_Save,
			eNotifyChangesMadeResult_Continue,
			eNotifyChangesMadeResult_Cancel,
			eNotifyChangesMadeResult_DontSave,
		};
        
        enum ENotifyChangesMadeMode {
            eUnsavedRegularFile,
            eUnsavedWorkingFileWithCheckOuts,
        };
		
		// ----------------------------------------------------------------------------------------------------
		// {38BF02F1-524F-4705-A5D5-CD7624C43421}
		static const VWIID IID_NotifyChangesMadeDialog = { 0x38BF02F1, 0x524F, 0x4705, { 0xA5, 0xD5, 0xCD, 0x76, 0x24, 0xC4, 0x34, 0x21 } };
		
		class DYNAMIC_ATTRIBUTE INotifyChangesMadeDialog : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	SetFileName(const TXString& fileName) = 0;
			virtual VCOMError VCOM_CALLTYPE SetCanCancel(bool inCanCancel) = 0;
			virtual VCOMError VCOM_CALLTYPE SetMode(ENotifyChangesMadeMode mode) = 0;
            
			virtual VCOMError VCOM_CALLTYPE RunDialog(ENotifyChangesMadeResult& result) = 0;
		};
	}
}