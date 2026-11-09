//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	// ---------------------------------------------------------------------------------------------------
	static const VWIID IID_Document	= { 0x52E7C7F5, 0x05E6, 0x11DB, { 0x95, 0x92, 0x00, 0x05, 0x9A, 0x3C, 0x78, 0x00 } };

	class DYNAMIC_ATTRIBUTE IDocument : public IVWUnknown
	{
	public:
		virtual	VCOMError	VCOM_CALLTYPE ShowPreferencesDialog(Sint16 paneIndex=-1) = 0;
		virtual	VCOMError	VCOM_CALLTYPE ShowUnitsDialog() = 0;
		virtual	VCOMError	VCOM_CALLTYPE ShowDashStylesDialog() = 0;
		virtual	VCOMError	VCOM_CALLTYPE ShowPatternsDialog() = 0;
	};

	// ---------------------------------------------------------------------------------------------------
	typedef VCOMPtr<IDocument>	IDocumentPtr;
}
