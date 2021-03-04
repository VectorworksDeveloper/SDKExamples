//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/LineStylePopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWLineStylePopupCtrl::VWLineStylePopupCtrl(TControlID id)
: VWControl( id )
{
}

VWLineStylePopupCtrl::~VWLineStylePopupCtrl()
{
}

bool VWLineStylePopupCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreateLineStylePopup( gCBP, pDlg->GetControlID(), fControlID );
	return VWControl::CreateControl( pDlg );
}

InternalIndex VWLineStylePopupCtrl::GetSelectedLineType() const
{
	InternalIndex	lineStyle;
	gSDK->GetLineTypeChoice( fpParentDlg->GetControlID(), fControlID, lineStyle );
	return lineStyle;
}

void VWLineStylePopupCtrl::SetSelectedLineType(InternalIndex lineStyle)
{
	gSDK->SetLineTypeChoice( fpParentDlg->GetControlID(), fControlID, lineStyle );
}

void VWLineStylePopupCtrl::ShowByClassChoice()
{
	gSDK->ShowByClassChoice( fpParentDlg->GetDialogID(), fControlID );
}

void VWLineStylePopupCtrl::SelectClassChoice(bool select)
{
	gSDK->SelectClassChoice( fpParentDlg->GetDialogID(), fControlID, select );
}

bool VWLineStylePopupCtrl::IsClassChoiceSelected()
{
	return gSDK->IsClassChoiceSelected( fpParentDlg->GetDialogID(), fControlID ) ? true : false;
}
