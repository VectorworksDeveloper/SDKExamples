//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ColorPopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWColorPopupCtrl::VWColorPopupCtrl(TControlID id)
: VWControl( id )
{
}

VWColorPopupCtrl::~VWColorPopupCtrl()
{
}

bool VWColorPopupCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreateColorPopup( gCBP, pDlg->GetControlID(), fControlID );
	return VWControl::CreateControl( pDlg );
}

bool VWColorPopupCtrl::CreateControlWithWidth(VWDialog* pDlg, short width)
{
	::GS_CreateColorPopup( gCBP, pDlg->GetControlID(), fControlID, width );
	return VWControl::CreateControl( pDlg );
}

RGBColor VWColorPopupCtrl::GetSelectedColor() const
{
	short		colorIndex;
	::GS_GetColorChoice( gCBP, fpParentDlg->GetControlID(), fControlID, colorIndex );

	RGBColor	color;
	//ECO_REVISIT_VML Replace GS_ColorIndexToRGB call with new ColorRef-based call when available.
	::GS_ColorIndexToRGB( gCBP, DemoteTo<ColorRef>(kSteve, colorIndex), color );
	return color;
}

void VWColorPopupCtrl::SetSelectedColor(const RGBColor& color)
{
	ColorRef		colorIndex;
	::GS_RGBToColorIndex( gCBP, color, colorIndex );

	::GS_SetColorChoice( gCBP, fpParentDlg->GetControlID(), fControlID, colorIndex );
}

void VWColorPopupCtrl::ShowByClassChoice()
{
	gSDK->ShowByClassChoice( fpParentDlg->GetDialogID(), fControlID );
}

void VWColorPopupCtrl::SelectClassChoice(bool select)
{
	gSDK->SelectClassChoice( fpParentDlg->GetDialogID(), fControlID, select );
}

bool VWColorPopupCtrl::IsClassChoiceSelected()
{
	return gSDK->IsClassChoiceSelected( fpParentDlg->GetDialogID(), fControlID ) ? true : false;
}

void VWColorPopupCtrl::ShowColor( bool showColor )
{
	gSDK->SetComponentIndeterminate( fpParentDlg->GetDialogID(), fControlID, !showColor );
}

