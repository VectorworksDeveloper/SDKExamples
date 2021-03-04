//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/EditPasswordCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWEditPasswordCtrl::VWEditPasswordCtrl(TControlID id)
: VWControl( id )
{
}

VWEditPasswordCtrl::~VWEditPasswordCtrl()
{
}

bool VWEditPasswordCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar)
{
	gSDK->CreateEditPassword( pDlg->GetControlID(), fControlID, widthInStdChar );
	return VWControl::CreateControl( pDlg );
}

TXString VWEditPasswordCtrl::GetText() const
{
	TXString	string;
	gSDK->GetItemText( fpParentDlg->GetControlID(), fControlID, string );
	return string;
}

void VWEditPasswordCtrl::SetText(const TXString& text)
{
	gSDK->SetItemText( fpParentDlg->GetControlID(), fControlID, text );
}

void VWEditPasswordCtrl::SelectContent()
{
	gSDK->SelectEditText( fpParentDlg->GetControlID(), fControlID );
}

void VWEditPasswordCtrl::DeselectContent()
{
	gSDK->DeselectEditText( fpParentDlg->GetControlID(), fControlID );
}
