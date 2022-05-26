//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/PushButtonCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;
using namespace VectorWorks::Filing;

VWPushButtonCtrl::VWPushButtonCtrl(TControlID id)
: VWControl( id )
{
}

VWPushButtonCtrl::~VWPushButtonCtrl()
{
}

bool VWPushButtonCtrl::CreateControl(VWDialog* pDlg, const TXString& text)
{
	::GS_CreatePushButton( gCBP, pDlg->GetControlID(), fControlID, text );
	return VWControl::CreateControl( pDlg );
}

void VWPushButtonCtrl::SetIconPushButtonImage(const TXString& imageSpec)
{
	gSDK->UpdateImageControl2( fpParentDlg->GetControlID(), fControlID, imageSpec );
}

void VWPushButtonCtrl::SetIconPushButtonImageUsingFullFilePath(IFileIdentifier* imgFileID)
{
	gSDK->UpdateImageControlUsingFullFilePath( fpParentDlg->GetControlID(), fControlID, imgFileID );
}

void VWPushButtonCtrl::SetIconPushButtonState(bool pressed)
{
	gSDK->SetIconPushButtonState( fpParentDlg->GetControlID(), fControlID, pressed );
}

bool VWPushButtonCtrl::GetIconPushButtonState() const
{
	Boolean pressed = false;
	gSDK->GetIconPushButtonState( fpParentDlg->GetControlID(), fControlID, pressed );
	return pressed ? true : false;
}

