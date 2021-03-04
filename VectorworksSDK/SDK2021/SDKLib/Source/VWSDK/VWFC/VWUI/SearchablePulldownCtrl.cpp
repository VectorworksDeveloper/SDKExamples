//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/SearchablePulldownCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWSearchablePulldownCtrl::VWSearchablePulldownCtrl(TControlID id)
	: VWControl( id )
{

}

VWSearchablePulldownCtrl::~VWSearchablePulldownCtrl()
{
    
}

bool VWSearchablePulldownCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar)
{
	gSDK->CreateSearchablePulldownMenu(pDlg->GetDialogID(), fControlID, widthInStdChar);

	return VWControl::CreateControl( pDlg );
}

void VWSearchablePulldownCtrl::Clear()
{
	gSDK->ClearChoicesFromSearchablePulldown(fpParentDlg->GetControlID(), fControlID, false);
}

void VWSearchablePulldownCtrl::Add(const TXString& idName, const TXString& text, const TXString& toolTip, const TXString& iconSpec)
{
	gSDK->InsertItemInSearchablePulldown(fpParentDlg->GetControlID(), fControlID, idName, text, toolTip, iconSpec);
}

void VWSearchablePulldownCtrl::AddChild(const TXString& idName, const TXString& text, const TXString& parentIdName, const TXString& toolTip, const TXString& iconSpec)
{
	gSDK->InsertChildItemInSearchablePulldown(fpParentDlg->GetControlID(), fControlID, idName, text, parentIdName, toolTip, iconSpec);
}

void VWSearchablePulldownCtrl::ClearStaticChoices()
{
	gSDK->ClearChoicesFromSearchablePulldown(fpParentDlg->GetControlID(), fControlID, true);
}

void VWSearchablePulldownCtrl::AddStaticChoice(const TXString& idName, const TXString& text, const TXString& toolTip, const TXString& iconSpec)
{
	gSDK->InsertStaticItemInSearchablePulldown(fpParentDlg->GetControlID(), fControlID, idName, text, toolTip, iconSpec);
}

void VWSearchablePulldownCtrl::AddHeaderItem(const TXString& text, const TXString& toolTip, const TXString& iconSpec)
{
	gSDK->InsertHeaderItemInSearchablePulldown(fpParentDlg->GetControlID(), fControlID, text, toolTip, iconSpec);
}

TXString VWSearchablePulldownCtrl::GetSelectedItem()
{
	return gSDK->GetActiveIDStrFromSearchablePulldown(fpParentDlg->GetControlID(), fControlID);
}

bool VWSearchablePulldownCtrl::SetSelectedItem(const TXString& idName)
{
	return gSDK->SetActiveIDStrInSearchablePulldown(fpParentDlg->GetControlID(), fControlID, idName);
}

bool VWSearchablePulldownCtrl::GetTextByID(const TXString& idName, TXString& outText)
{
	return gSDK->GetDisplayNameFromIDStrInSearchablePulldown(fpParentDlg->GetControlID(), fControlID, idName, outText);
}

bool VWSearchablePulldownCtrl::GetIDByText(const TXString& text, TXString& outIdName)
{
	return gSDK->GetIDStrFromDisplayNameInSearchablePulldown(fpParentDlg->GetControlID(), fControlID, text, outIdName);
}




