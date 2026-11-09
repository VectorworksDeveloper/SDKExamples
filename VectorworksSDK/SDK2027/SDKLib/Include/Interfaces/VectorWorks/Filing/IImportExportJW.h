//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		// -----------------------------------------------------------------------------------
		// {AC8B9DCC-74D3-4A63-91A1-8CF040DFC54D}
		static const VWIID IID_IImportExportJw = 	{ 0xac8b9dcc, 0x74d3, 0x4a63, { 0x91, 0xa1, 0x8c, 0xf0, 0x40, 0xdf, 0xc5, 0x4d } };

		class IImportExportJw : public IImportReference
		{
		public:
			VCOMError	VCOM_CALLTYPE	Import( IFileIdentifierPtr& fileID, const bool bShowUI = true, EImportModeRef importMode = EImportModeRef::Normal ) override = 0;

			// Unique char used for serializing the referencing options in a UserDataNode
			static const OSType		kRefJwDataType = 'TJW';
		};
		typedef VCOMPtr<IImportExportJw>		IImportExportJwPtr;
	}
}
