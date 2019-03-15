//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/LineWeightPopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWLineWeightPopupCtrl::VWLineWeightPopupCtrl(TControlID id)
: VWControl( id )
{
}

VWLineWeightPopupCtrl::~VWLineWeightPopupCtrl()
{
}

bool VWLineWeightPopupCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreateLineWeightPopup( gCBP, pDlg->GetControlID(), fControlID );
	return VWControl::CreateControl( pDlg );
}

short VWLineWeightPopupCtrl::GetSelectedLineWeight() const
{
	short	lineWeight;
	::GS_GetLineWeightChoice( gCBP, fpParentDlg->GetControlID(), fControlID, lineWeight);
	return lineWeight;
}

void VWLineWeightPopupCtrl::SetSelectedLineWeight(short lineWeight)
{
	::GS_SetLineWeightChoice( gCBP, fpParentDlg->GetControlID(), fControlID, lineWeight );
}

void VWLineWeightPopupCtrl::ShowByClassChoice()
{
	gSDK->ShowByClassChoice( fpParentDlg->GetDialogID(), fControlID );
}

void VWLineWeightPopupCtrl::SelectClassChoice(bool select)
{
	gSDK->SelectClassChoice( fpParentDlg->GetDialogID(), fControlID, select );
}

bool VWLineWeightPopupCtrl::IsClassChoiceSelected()
{
	return gSDK->IsClassChoiceSelected( fpParentDlg->GetDialogID(), fControlID ) ? true : false;
}
