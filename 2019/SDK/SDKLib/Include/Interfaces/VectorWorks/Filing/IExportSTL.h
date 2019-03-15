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
		// {E325768F-8FA4-4658-B792-AB6FA6C3C7A0}
		static const VWIID IID_ExportSTL = { 0xe325768f, 0x8fa4, 0x4658, { 0xb7, 0x92, 0xab, 0x6f, 0xa6, 0xc3, 0xc7, 0xa0 } };

		class DYNAMIC_ATTRIBUTE IExportSTL : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(IFileIdentifier* pFileID, bool exportBinary, double percentTess, Sint16 exportObjectsOptions) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IExportSTL>		IExportSTLPtr;

		// ----------------------------------------------------------------------------------------------------
		// {A078D74B-C6A3-4F26-8229-630CC68914E4}
		static const VWIID IID_ExportSTEP = { 0xa078d74b, 0xc6a3, 0x4f26, { 0x82, 0x29, 0x63, 0xc, 0xc6, 0x89, 0x14, 0xe4 } };

		class DYNAMIC_ATTRIBUTE IExportSTEP : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Export(IFileIdentifier* pFileID, bool exportSolidAsSurface) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IExportSTEP>		IExportSTEPPtr;
	}
}
