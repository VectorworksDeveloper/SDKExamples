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
		enum class EExport
		{
			SelectedObjectsOnly,
			AllObjectsInCurrentLayer,
			AllVisibleObjectsInAllLayers
		};

		enum class EQuality
		{
			Low,
			Medium,
			High,
			VeryHigh
		};
		
		struct SExportOBJOptions
		{
			EExport		fExport					= EExport::AllVisibleObjectsInAllLayers;
			EQuality	fQuality				= EQuality::High;
			bool		fApplyDoubleSidedFaces	= true;
		};

		// ----------------------------------------------------------------------------------------------------
		// {74ABBF1E-4A94-4950-967C-8A3F53DECF2F}
		static const VWIID IID_ExportOBJ = { 0x74abbf1e, 0x4a94, 0x4950, { 0x96, 0x7c, 0x8a, 0x3f, 0x53, 0xde, 0xcf, 0x2f } };

		class DYNAMIC_ATTRIBUTE IExportOBJ : public IVWUnknown
		{
		public:
			virtual void VCOM_CALLTYPE	Export(IFileIdentifier* pFileID, const SExportOBJOptions& options) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IExportOBJ> IExportOBJPtr;
	}
}
