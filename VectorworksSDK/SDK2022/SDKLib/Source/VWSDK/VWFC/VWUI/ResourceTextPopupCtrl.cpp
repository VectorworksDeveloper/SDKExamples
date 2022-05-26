//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ResourceTextPopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

#include "Interfaces/VectorWorks/Extension/IResourceManagerContent.h"

using namespace VWFC::VWUI;

VWResourceTextPopupCtrl::VWResourceTextPopupCtrl(TControlID id)
: VWControl( id )
{
}

VWResourceTextPopupCtrl::~VWResourceTextPopupCtrl()
{
}

bool VWResourceTextPopupCtrl::CreateControl(VWDialog* pDlg, Sint32 widthInStdChar)
{
	gSDK->CreateResourceTextPopup(pDlg->GetControlID(), fControlID, widthInStdChar);

    return VWControl::CreateControl( pDlg );
}

void VWResourceTextPopupCtrl::PullDownResourceLayoutInit(VectorWorks::Extension::IResourceManagerContent* content)
{
	gSDK->PullDownResourceLayoutInit(fpParentDlg->GetDialogID(), fControlID, content);
}

void VWResourceTextPopupCtrl::PullDownResourceLayoutSetSelectedResourceName(const TXString& name)
{
	if (!name.IsEmpty())
	{
		gSDK->PullDownResourceLayoutSetSelectedResourceName(fpParentDlg->GetDialogID(), fControlID, name);
	}
	else
	{
		// init default selection.
		TXString currName = gSDK->PullDownResourceLayoutGetSelectedResourceName(fpParentDlg->GetDialogID(), fControlID);
		gSDK->PullDownResourceLayoutSetSelectedResourceName(fpParentDlg->GetDialogID(), fControlID, currName);
	}
}

TXString VWResourceTextPopupCtrl::PullDownResourceLayoutGetSelectedResourceName() const
{
	return gSDK->PullDownResourceLayoutGetSelectedResourceName(fpParentDlg->GetDialogID(), fControlID);
}
