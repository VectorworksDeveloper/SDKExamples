//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VWFC/VWUI/BorderlessButtonCtrl.h"


using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWBorderlessButtonCtrl::VWBorderlessButtonCtrl(TControlID id)
: VWControl( id, {eCompBorderlessButton} )
{
}

VWBorderlessButtonCtrl::~VWBorderlessButtonCtrl()
{
}

bool VWBorderlessButtonCtrl::CreateControl(VWDialog* pDlg, const TXString& title, const TXString& iconResPath, const bool isToggleButton, const EButtonImagePos imagePos)
{
	gSDK->CreateBorderlessButton(pDlg->GetControlID(), fControlID, title, iconResPath, isToggleButton, imagePos);
	return VWControl::CreateControl( pDlg );
}

bool VWBorderlessButtonCtrl::GetState() const
{
	Boolean			state		= 0;

	::GS_GetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );

	return (bool)state;
}

void VWBorderlessButtonCtrl::SetState(bool state)
{
	::GS_SetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );
}

bool VWBorderlessButtonCtrl::UpdateImage( const TXString &imageSpec )
{
	return gSDK->UpdateImageButton( fpParentDlg->GetDialogID(), fControlID, imageSpec );
}
