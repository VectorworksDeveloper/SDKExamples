//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/RadioGroupBoxCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWRadioGroupBoxCtrl::VWRadioGroupBoxCtrl(TControlID id)
: VWControlsContainer( id )
{
}

VWRadioGroupBoxCtrl::~VWRadioGroupBoxCtrl()
{
}

bool VWRadioGroupBoxCtrl::CreateControl(VWDialog* pDlg, const TXString& text, bool bHasFrame /*=true*/)
{
	::GS_CreateRadioButtonGroupBox( gCBP, pDlg->GetControlID(), (short)fControlID, text, bHasFrame );
	return VWControl::CreateControl( pDlg );
}

bool VWRadioGroupBoxCtrl::GetState() const
{
	Boolean			state		= 0;

	::GS_GetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );

	return (bool)state;
}

void VWRadioGroupBoxCtrl::SetState(bool state)
{
	::GS_SetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );
}
