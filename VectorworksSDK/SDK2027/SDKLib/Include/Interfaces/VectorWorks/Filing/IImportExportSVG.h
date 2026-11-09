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
		// {636B929C-7CAD-4B7D-88D1-F90D68C0A928}
		static const VWIID IID_ImportExportSVG = { 0x636b929c, 0x7cad, 0x4b7d, { 0x88, 0xd1, 0xf9, 0xd, 0x68, 0xc0, 0xa9, 0x28 } };

		class DYNAMIC_ATTRIBUTE IImportExportSVG : public IVWUnknown
		{
		public:
			virtual MCObjectHandle	VCOM_CALLTYPE	Import() = 0;
			virtual MCObjectHandle	VCOM_CALLTYPE	Import(IFileIdentifier* fileID) = 0;
			virtual MCObjectHandle	VCOM_CALLTYPE	ImportAsSymbol(IFileIdentifier* fileID, const TXString& symName) = 0;
			virtual bool			VCOM_CALLTYPE	Export() = 0;
			virtual bool			VCOM_CALLTYPE	ExportSelection(IFileIdentifier* fileID) = 0;
			virtual bool			VCOM_CALLTYPE	ExportGroup(IFileIdentifier* fileID, MCObjectHandle hGroupOrSymbol) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportSVG>		IImportExportSVGPtr;
	}
}
