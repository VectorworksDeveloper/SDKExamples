//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/StaticTextCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWStaticTextCtrl::VWStaticTextCtrl(TControlID id)
: VWControl( id )
{
}

VWStaticTextCtrl::~VWStaticTextCtrl()
{
}

bool VWStaticTextCtrl::CreateControl(VWDialog* pDlg, const TXString& text, short widthInStdChar/*=-1*/)
{
	::GS_CreateStaticText( gCBP, pDlg->GetControlID(), fControlID, text, widthInStdChar );
	return VWControl::CreateControl( pDlg );
}

void VWStaticTextCtrl::SetStyle(EStaticTextCtrlStyle style)
{
	gSDK->SetStaticTextStyle( fpParentDlg->GetControlID(), fControlID, short(style) );
}

void VWStaticTextCtrl::SetColor(const VWFC::Tools::CRGBColor& color, bool atDialogInitTime)
{
	if ( atDialogInitTime )
	{
		gSDK->SetStaticTextColor( fpParentDlg->GetControlID(), fControlID, color.GetRed(), color.GetGreen(), color.GetBlue() );
	}
	else
	{
		SControlData_StaticText	data;
		data.fColorRed = color.GetRed();
		data.fColorGreen = color.GetGreen();
		data.fColorBlue = color.GetBlue();
		gSDK->SetControlData( fpParentDlg->GetControlID(), fControlID, data );
	}
}

void VWStaticTextCtrl::SetClickable(bool value)
{
	gSDK->SetItemClickable( fpParentDlg->GetControlID(), fControlID, value );
}

