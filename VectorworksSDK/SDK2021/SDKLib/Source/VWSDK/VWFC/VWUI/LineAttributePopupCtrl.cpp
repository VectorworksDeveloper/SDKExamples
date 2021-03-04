//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/LineAttributePopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWLineAttributePopupCtrl::VWLineAttributePopupCtrl(TControlID id)
: VWControl( id )
{
}

VWLineAttributePopupCtrl::~VWLineAttributePopupCtrl()
{
}

bool VWLineAttributePopupCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreateLineAttributePopup( gCBP, pDlg->GetControlID(), fControlID );
	return VWControl::CreateControl( pDlg );
}

void VWLineAttributePopupCtrl::GetSelectedLineTypeAttribute(InternalIndex& outLineStyle, short& outLineWeight) const
{
	gSDK->GetLineTypeAttributeData(fpParentDlg->GetControlID(), fControlID, outLineStyle, outLineWeight );
}

void VWLineAttributePopupCtrl::SetSelectedLineTypeAttribute(InternalIndex lineStyle, short lineWeight)
{
	gSDK->SetLineTypeAttributeData( fpParentDlg->GetControlID(), fControlID, lineStyle, lineWeight );
}

void VWLineAttributePopupCtrl::ShowByClassChoice()
{
	gSDK->ShowByClassChoice( fpParentDlg->GetDialogID(), fControlID );
}

void VWLineAttributePopupCtrl::SelectClassChoice(bool select)
{
	gSDK->SelectClassChoice( fpParentDlg->GetDialogID(), fControlID, select );
}

bool VWLineAttributePopupCtrl::IsClassChoiceSelected()
{
	return gSDK->IsClassChoiceSelected( fpParentDlg->GetDialogID(), fControlID ) ? true : false;
}
