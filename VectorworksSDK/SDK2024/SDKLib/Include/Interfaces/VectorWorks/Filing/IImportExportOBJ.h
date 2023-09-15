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
		struct SImportOBJOptions
		{
			// set to true of the entire file should be imported as a symbol
			// with a name of the file
			bool	fImportAsSingleSymbol = false;

			bool	fImportMaterials = true;
			bool	fImportTraspAndImage = true;			// only trasparency and image materials create RenderWorks resources
			bool	fImporAllRW = false;					// all materials create RenderWorks resources
			bool	fAllowMissingMaterialTexture = false;	// in headless mode, allow import to proceed when material texture is missing

		};

		// ----------------------------------------------------------------------------------------------------
		// {58F756CA-903E-4d9e-9C92-3C844BEAEE7D}
		static const VWIID IID_IImportExportOBJ = { 0x58f756ca, 0x903e, 0x4d9e, { 0x9c, 0x92, 0x3c, 0x84, 0x4b, 0xea, 0xee, 0x7d } };

		class DYNAMIC_ATTRIBUTE IImportExportOBJ : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError	VCOM_CALLTYPE	Import(IFileIdentifier* fileID) = 0;
			virtual VCOMError	VCOM_CALLTYPE	Import(IFileIdentifier* fileID, const SImportOBJOptions& options, bool silent = false) = 0; // no UI
			virtual VCOMError	VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError	VCOM_CALLTYPE	Export(IFileIdentifier* fileID) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportOBJ>		IImportExportOBJPtr;
	}
}