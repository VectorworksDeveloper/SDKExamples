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
		struct S3DSImportOptions : public SMvrBackendImportOptions
		{
			S3DSImportOptions() : SMvrBackendImportOptions() { fSize = sizeof(S3DSImportOptions); }
			virtual	~S3DSImportOptions() {}
		};

		struct S3DSExporterOptions : public SMvrBackendExporterOptions
		{
			S3DSExporterOptions() : SMvrBackendExporterOptions() { fSize = sizeof(S3DSExporterOptions); }
			virtual	~S3DSExporterOptions() {}
		};

		// ----------------------------------------------------------------------------------------------------
		// {263BD4CD-417F-4fc0-8BEE-9CBFF95FDC76}
		static const VWIID IID_IImportExport3DS = { 0x263bd4cd, 0x417f, 0x4fc0, { 0x8b, 0xee, 0x9c, 0xbf, 0xf9, 0x5f, 0xdc, 0x76 } };

		class DYNAMIC_ATTRIBUTE IImportExport3DS : public IVWUnknown
		{
		public:
			virtual ~IImportExport3DS() {}
			virtual VCOMError VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID, const WorldPt& position, bool silent = false) = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID, const WorldPt& position, const TXString& strProgressTitle, const TXString& strProgressBar) = 0; 
			virtual VCOMError VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetOptions(const S3DSImportOptions& options) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetOptions(S3DSImportOptions& outOptions) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetOptions(const S3DSExporterOptions& options) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetOptions(S3DSExporterOptions& outOptions) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileScale(IFileIdentifier* pFileID, float& outUnitsPerInch) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExport3DS>		IImportExport3DSPtr;

		//-------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IGeometryReceiver3DS : public IGeometryReceiverMvrBackend
		{
		public:
			virtual	~IGeometryReceiver3DS() {}
		};

		//-------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IGeometryProvider3DS : public IGeometryProviderMvrBackend
		{
		public:
			virtual	~IGeometryProvider3DS() {}
		};

		// ----------------------------------------------------------------------------------------------------
		// {E7468FA1-5A3D-49E8-9D70-561A5B60A52A}
		static const VWIID IID_IImportExportObject3DS = { 0xe7468fa1, 0x5a3d, 0x49e8,{ 0x9d, 0x70, 0x56, 0x1a, 0x5b, 0x60, 0xa5, 0x2a } };

		class DYNAMIC_ATTRIBUTE IImportExportObject3DS : public IImportExportObjectMvrBackend
		{
		public:
			virtual	~IImportExportObject3DS() {}
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportObject3DS>		IImportExportObject3DSPtr;
	}
}
