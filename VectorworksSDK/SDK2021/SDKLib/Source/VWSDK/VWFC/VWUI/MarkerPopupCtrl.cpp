//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/MarkerPopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWMarkerPopupCtrl::VWMarkerPopupCtrl(TControlID id)
: VWControl( id )
{
}

VWMarkerPopupCtrl::~VWMarkerPopupCtrl()
{
}

bool VWMarkerPopupCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreateControl( gCBP, pDlg->GetControlID(), fControlID, kMarkerPopup, "", 0 );
	return VWControl::CreateControl( pDlg );
}

void VWMarkerPopupCtrl::GetSelectedItem(SMarkerStyle& outValue) const
{
	::GS_GetMarkerChoice( gCBP, fpParentDlg->GetControlID(), fControlID,
									outValue.style,
									outValue.nAngle,
									outValue.dSize,
									outValue.dWidth,
									outValue.nThicknessBasis,
									outValue.dThickness );

}

void VWMarkerPopupCtrl::SetSelectedItem(const SMarkerStyle& value)
{
	::GS_SetMarkerChoice( gCBP, fpParentDlg->GetControlID(), fControlID,
									value.style,
									value.nAngle,
									value.dSize,
									value.dWidth,
									value.nThicknessBasis,
									value.dThickness );
}

void VWMarkerPopupCtrl::ShowByClassChoice()
{
	gSDK->ShowByClassChoice( fpParentDlg->GetDialogID(), fControlID );
}

void VWMarkerPopupCtrl::SelectClassChoice(bool select)
{
	gSDK->SelectClassChoice( fpParentDlg->GetDialogID(), fControlID, select );
}

bool VWMarkerPopupCtrl::IsClassChoiceSelected()
{
	return gSDK->IsClassChoiceSelected( fpParentDlg->GetDialogID(), fControlID ) ? true : false;
}
