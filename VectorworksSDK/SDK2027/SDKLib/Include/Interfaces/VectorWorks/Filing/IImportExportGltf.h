//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IImportExportMvrBackend.h"

namespace VectorWorks
{
	namespace Filing
	{
		struct SGltfImportOptions : public SMvrBackendImportOptions
		{
			SGltfImportOptions() : SMvrBackendImportOptions() { fSize = sizeof(SGltfImportOptions); }
			virtual	~SGltfImportOptions() {}
		};

		struct SGltfExporterOptions : public SMvrBackendExporterOptions
		{
			SGltfExporterOptions() : SMvrBackendExporterOptions() { fSize = sizeof(SGltfExporterOptions); }
			virtual	~SGltfExporterOptions() {}
		};

		//-------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IGeometryReceiverGltf : public IGeometryReceiverMvrBackend
		{
		public:
			virtual	~IGeometryReceiverGltf() {}
		};

		//-------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IGeometryProviderGltf : public IGeometryProviderMvrBackend
		{
		public:
			virtual	~IGeometryProviderGltf() {}
		};

		// ----------------------------------------------------------------------------------------------------
		// {045BBC63-E2BA-446E-98EE-89A300337938}
		static const VWIID IID_IImportExportObjectGltf = { 0x045bbc63, 0xe2ba, 0x446e,{ 0x98, 0xee, 0x89, 0xa3, 0x00, 0x33, 0x79, 0x38 } };

		class DYNAMIC_ATTRIBUTE IImportExportObjectGltf : public IImportExportObjectMvrBackend
		{
		public:
			virtual	~IImportExportObjectGltf() {}
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportObjectGltf>		IImportExportObjectGltfPtr;
	}
}
