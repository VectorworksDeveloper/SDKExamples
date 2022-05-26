//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IFileIdentifier.h"


namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		// {6FC15217-044A-4D1B-AB4A-8EBFE5B2AF13}
		static const VWIID IID_FileTools = 		{ 0x6fc15217, 0x44a, 0x4d1b, { 0xab, 0x4a, 0x8e, 0xbf, 0xe5, 0xb2, 0xaf, 0x13 } };

		class DYNAMIC_ATTRIBUTE IFileTools : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	MacOS_IsFileVisible(IFileIdentifier* fileID, bool& outVisible) = 0;
			virtual VCOMError VCOM_CALLTYPE	MacOS_GetHFSFileType(IFileIdentifier* fileID, OSType& outHFSFileType) = 0;
			virtual VCOMError VCOM_CALLTYPE	MacOS_SetHFSFileType(IFileIdentifier* fileID, OSType inHFSFileType) = 0;
			virtual VCOMError VCOM_CALLTYPE	MacOS_SetFileCreator(IFileIdentifier* fileID, Uint32 creator) = 0;
            virtual VCOMError VCOM_CALLTYPE MacOS_FindFolder(Uint32 domain, Uint32 folderType, bool createFolder, TXString& folderPath) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IFileTools>			IFileToolsPtr;
        
        //
        // domain constants
        const Uint32 kUserDomainMask = 1;
        const Uint32 kLocalDomainMask = 2;
        const Uint32 kNetworkDomainMask = 4;
        const Uint32 kSystemDomainMask = 8;
        const Uint32 kAllDomainsMask = 0x0ffff;
        
        //
        // folder type constants
		const Uint32 kApplicationsDirectory = 1;
        const Uint32 kLibraryDirectory = 5;
        const Uint32 kUserDirectory = 7;
        const Uint32 kDocumentDirectory = 9;
        const Uint32 kApplicationSupportDirectory = 14;
        const Uint32 kPreferencePanesDirectory = 22;
        const Uint32 kItemReplacementDirectory = 99;
	}
}