//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IDocument.h"

namespace VectorWorks
{
	// ---------------------------------------------------------------------------------------------------
	static const VWIID IID_Application	= { 0x4CC4B404, 0x05E6, 0x11DB, { 0x95, 0x92, 0x00, 0x05, 0x9A, 0x3C, 0x78, 0x00 } };

	class DYNAMIC_ATTRIBUTE IApplication : public IVWSingletonUnknown
	{
	public:
		virtual	VCOMError	VCOM_CALLTYPE ShowPreferencesDialog(Sint16 paneIndex=-1) = 0;
		virtual Uint32		VCOM_CALLTYPE GetDocumentsCount() = 0;
		virtual VCOMError	VCOM_CALLTYPE GetDocument(IDocument** ppOutDocument) = 0;
		virtual VCOMError	VCOM_CALLTYPE GetActiveDocument(IDocument** ppOutDocument) = 0;
	};

	// ---------------------------------------------------------------------------------------------------
	typedef VCOMPtr<IApplication>		IApplicationPtr;
}
