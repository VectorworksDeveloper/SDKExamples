//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VWFC/VWUI/StaticTextCtrl.h"


using namespace VWFC::VWUI;

VWStaticTextCtrl::VWStaticTextCtrl(TControlID id)
: VWControl( id )
{
}

VWStaticTextCtrl::~VWStaticTextCtrl()
{
}

bool VWStaticTextCtrl::CreateControl(VWDialog* pDlg, const TXString& text, short widthInStdChar/*=-1*/, EStaticTextType style/*=eStaticTextTypeRegular*/)
{
	gSDK->CreateStyledStaticText(pDlg->GetControlID(), fControlID, text, widthInStdChar, style );
	return VWControl::CreateControl( pDlg );
}

// Deprecated: this function should be avoided. On Windows, calling this can result in the control not being sized properly. The style should
// be entered in CreateControl to get the sizing correct.
void VWStaticTextCtrl::SetStyle(EStaticTextCtrlStyle style)
{
	gSDK->SetStaticTextStyle( fpParentDlg->GetControlID(), fControlID, short(style) );
}

void VWStaticTextCtrl::SetColor(const VWFC::Tools::CRGBColor& color)
{
	gSDK->SetStaticTextColor( fpParentDlg->GetControlID(), fControlID, color.GetRed(), color.GetGreen(), color.GetBlue() );
}

void VWStaticTextCtrl::SetTint(const EUiControlTextTint tint)
{
	gSDK->SetStaticTextColorN( fpParentDlg->GetControlID(), fControlID, tint);
}

void VWStaticTextCtrl::SetClickable(bool value)
{
	gSDK->SetItemClickable( fpParentDlg->GetControlID(), fControlID, value );
}

