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
		// ----------------------------------------------------------------------------------------------------
		// {57E7EED5-6BBC-46F1-BB87-6E932D23517C}
		static const VWIID IID_ImportExportSAT = { 0x57e7eed5, 0x6bbc, 0x46f1, { 0xbb, 0x87, 0x6e, 0x93, 0x2d, 0x23, 0x51, 0x7c } };

		class DYNAMIC_ATTRIBUTE IImportExportSAT : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	ImportAsSymbol(IFileIdentifier* pFileID, const TXString& symName) = 0;
			virtual VCOMError VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(IFileIdentifier* pFileID, bool exportSolidAsSurface) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportSAT>		IImportExportSATPtr;
	}
}
