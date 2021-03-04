//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/CheckGroupBoxCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWCheckGroupBoxCtrl::VWCheckGroupBoxCtrl(TControlID id)
: VWControlsContainer( id )
{
}

VWCheckGroupBoxCtrl::~VWCheckGroupBoxCtrl()
{
}

bool VWCheckGroupBoxCtrl::CreateControl(VWDialog* pDlg, const TXString& text, bool bHasFrame/*=true*/)
{
	::GS_CreateCheckBoxGroupBox( gCBP, pDlg->GetControlID(), (short) fControlID, text, bHasFrame );
	return VWControl::CreateControl( pDlg );
}

bool VWCheckGroupBoxCtrl::GetState() const
{
	Boolean			state		= 0;

	::GS_GetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );

	return (bool)state;
}

void VWCheckGroupBoxCtrl::SetState(bool state)
{
	::GS_SetBooleanItem( gCBP, fpParentDlg->GetControlID(), fControlID, state );
}
