//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/SearchBoxCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWSearchBoxCtrl::VWSearchBoxCtrl(TControlID id)
: VWControl( id )
{
}

VWSearchBoxCtrl::~VWSearchBoxCtrl()
{
}

bool VWSearchBoxCtrl::CreateControl(VWDialog* pDlg, const TXString& promptText, short widthInStdChar)
{
	gSDK->CreateSearchEditBox(pDlg->GetControlID(), fControlID, promptText, widthInStdChar);
	return VWControl::CreateControl( pDlg );
}

TXString VWSearchBoxCtrl::GetSearchText() const
{
	TXString	string;
	gSDK->GetItemText( fpParentDlg->GetControlID(), fControlID, string );
	return string;
}

void VWSearchBoxCtrl::SetSearchText(const TXString& text)
{
	gSDK->SetItemText( fpParentDlg->GetControlID(), fControlID, text );
}

void VWSearchBoxCtrl::SelectContent()
{
	::GS_SelectEditText( gCBP, fpParentDlg->GetControlID(), fControlID );
}

void VWSearchBoxCtrl::DeselectContent()
{
	gSDK->DeselectEditText( fpParentDlg->GetControlID(), fControlID );
}
