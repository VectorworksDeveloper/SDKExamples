//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VWFC/VWUI/ColorButtonCtrl.h"


using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWColorButtonCtrl::VWColorButtonCtrl(TControlID id)
: VWControl( id, {eCompColorButton} )
{
}

VWColorButtonCtrl::~VWColorButtonCtrl()
{
}

bool VWColorButtonCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreateControl( gCBP, pDlg->GetControlID(), fControlID, kColorButtonControl, "", 0 );
	return VWControl::CreateControl( pDlg );
}

RGBColor VWColorButtonCtrl::GetColor() const
{
	RGBColor	color;
	color.red = color.green = color.blue = 0;

	::GS_GetColorButton( gCBP, fpParentDlg->GetControlID(), fControlID, color );
	return color;
}

void VWColorButtonCtrl::GetColor(RGBColor& color)
{
	color.red = color.green = color.blue = 0;

	::GS_GetColorButton( gCBP, fpParentDlg->GetControlID(), fControlID, color );
}

void VWColorButtonCtrl::GetColor(TGSColorV2& color)
{
	gSDK->GetColorButton( fpParentDlg->GetControlID(), fControlID, color );
}

void VWColorButtonCtrl::SetColor(const RGBColor& color)
{
	::GS_SetColorButton( gCBP, fpParentDlg->GetControlID(), fControlID, color );
}

void VWColorButtonCtrl::SetColor(const TGSColorV2& color)
{
	gSDK->SetColorButton( fpParentDlg->GetControlID(), fControlID, color );
}
