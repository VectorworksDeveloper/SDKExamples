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
		// {A162E405-E859-4e0c-B5C8-959C9BEC0565}
		static const VWIID IID_FolderChooserDialog = { 0xa162e405, 0xe859, 0x4e0c, { 0xb5, 0xc8, 0x95, 0x9c, 0x9b, 0xec, 0x5, 0x65 } };

		class DYNAMIC_ATTRIBUTE IFolderChooserDialog : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	SetTitle(const TXString& title) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetDescription(const TXString& desc) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetSelectedPath(IFolderIdentifier** ppOutFolderID) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetSelectedPath(IFolderIdentifier* pFolderID) = 0;

			virtual VCOMError VCOM_CALLTYPE	RunDialog() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IFolderChooserDialog>		IFolderChooserDialogPtr;
	}
}