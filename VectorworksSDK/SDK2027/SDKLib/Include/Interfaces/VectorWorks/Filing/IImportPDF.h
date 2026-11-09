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
		// {6FBA7AB9-DD27-44F6-9987-7944FE98E633}
		static const VWIID IID_ImportPDF = { 0x6fba7ab9, 0xdd27, 0x44f6, { 0x99, 0x87, 0x79, 0x44, 0xfe, 0x98, 0xe6, 0x33 } };

		class DYNAMIC_ATTRIBUTE IImportPDF : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* fileID) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportPDF>		IImportPDFPtr;
	}
}

