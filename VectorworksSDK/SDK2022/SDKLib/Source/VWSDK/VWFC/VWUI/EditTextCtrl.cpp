//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/EditTextCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWEditTextCtrl::VWEditTextCtrl(TControlID id)
: VWControl( id )
{
}

VWEditTextCtrl::~VWEditTextCtrl()
{
}

bool VWEditTextCtrl::CreateControl(VWDialog* pDlg, const TXString& text, short widthInStdChar, short heightInLines/*=1*/)
{
	gSDK->CreateEditText( pDlg->GetControlID(), fControlID, text, widthInStdChar, heightInLines );
	return VWControl::CreateControl( pDlg );
}

TXString VWEditTextCtrl::GetText() const
{
	TXString	string;
	gSDK->GetItemText( fpParentDlg->GetControlID(), fControlID, string );
	return string;
}

void VWEditTextCtrl::SetText(const TXString& text)
{
	gSDK->SetItemText( fpParentDlg->GetControlID(), fControlID, text );
}

void VWEditTextCtrl::SelectContent()
{
	::GS_SelectEditText( gCBP, fpParentDlg->GetControlID(), fControlID );
}

void VWEditTextCtrl::DeselectContent()
{
	gSDK->DeselectEditText( fpParentDlg->GetControlID(), fControlID );
}

void VWEditTextCtrl::GetSelectionRange(Sint32& startPos, Sint32& endPos)
{
	gSDK->GetSelectionRange( fpParentDlg->GetControlID(), fControlID, startPos, endPos );
}

void VWEditTextCtrl::SetSelectionRange(Sint32& startPos, Sint32& endPos)
{
	gSDK->SetSelectionRange( fpParentDlg->GetControlID(), fControlID, startPos, endPos );
}
