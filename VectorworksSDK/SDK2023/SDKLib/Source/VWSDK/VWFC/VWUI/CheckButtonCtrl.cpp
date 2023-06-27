//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/CheckButtonCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWCheckButtonCtrl::VWCheckButtonCtrl(TControlID id)
: VWControl( id )
{
}

VWCheckButtonCtrl::~VWCheckButtonCtrl()
{
}

bool VWCheckButtonCtrl::CreateControl(VWDialog* pDlg, const TXString& text, bool triState)
{
	if ( triState )
		gSDK->CreateThreeStateCheckBox( pDlg->GetControlID(), fControlID, text );
	else
		gSDK->CreateCheckBox( pDlg->GetControlID(), fControlID, text );
	return VWControl::CreateControl( pDlg );
}

bool VWCheckButtonCtrl::GetState() const
{
	Boolean			state		= 0;

	::GS_GetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );

	return (bool)state;
}

void VWCheckButtonCtrl::SetState(bool state)
{
	::GS_SetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );
}

ECheckButtonCtrlState VWCheckButtonCtrl::GetThreeState() const
{
	Sint32	state	= 0;
	gSDK->GetThreeStateCheckBoxState( fpParentDlg->GetControlID(), fControlID, state );
	return (ECheckButtonCtrlState) state;
}

void VWCheckButtonCtrl::SetThreeState(ECheckButtonCtrlState state)
{
	gSDK->SetThreeStateCheckBoxState( fpParentDlg->GetControlID(), fControlID, Sint32(state) );
}
