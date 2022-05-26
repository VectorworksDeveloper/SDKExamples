//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/RadioButtonCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWRadioButtonCtrl::VWRadioButtonCtrl(TControlID id)
: VWControl( id )
{
}

VWRadioButtonCtrl::~VWRadioButtonCtrl()
{
}

bool VWRadioButtonCtrl::CreateControl(VWDialog* pDlg, const TXString& text)
{
	::GS_CreateRadioButton( gCBP, pDlg->GetControlID(), fControlID, text );
	return VWControl::CreateControl( pDlg );
}

bool VWRadioButtonCtrl::GetState() const
{
	Boolean			state	= 0;

	::GS_GetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );

	return (bool)state;
}

void VWRadioButtonCtrl::SetState(bool state)
{
	::GS_SetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );
}
