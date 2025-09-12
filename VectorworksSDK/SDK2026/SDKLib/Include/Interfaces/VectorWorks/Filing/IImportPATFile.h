//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		// {26A628E3-8DD0-46B9-B014-7204BB3E48BF}
		static const VWIID IID_IImportPATFile = { 0x26a628e3, 0x8dd0, 0x46b9, { 0xb0, 0x14, 0x72, 0x4, 0xbb, 0x3e, 0x48, 0xbf } };

		class DYNAMIC_ATTRIBUTE IImportPATFile : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Import(bool bAddHatchInternalIndexToList = false, std::vector<InternalIndex>* hatchInternalIndexList = nullptr) = 0;
			virtual VCOMError VCOM_CALLTYPE	ImportSelectedFile(IFileIdentifier* pFileID, std::vector<InternalIndex>* hatchInternalIndexList = nullptr) = 0;

			// ----------------------------------------------------------------------------------------------------
			typedef VCOMPtr<IImportPATFile>		IImportPATFilePtr;
		};
	}
}
