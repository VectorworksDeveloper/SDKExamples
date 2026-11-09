//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VWFC/VWUI/EditRealCtrl.h"


using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWEditRealCtrl::VWEditRealCtrl(TControlID id)
: VWControl( id, {eCompEditReal} )
{
}

VWEditRealCtrl::~VWEditRealCtrl()
{
}

bool VWEditRealCtrl::CreateControl(VWDialog* pDlg, double dDefaultValue, short widthInStdChar, EEditControlType type)
{
	::GS_CreateEditReal( gCBP, pDlg->GetControlID(), fControlID, (Sint32) type, dDefaultValue, widthInStdChar );
	return VWControl::CreateControl( pDlg );
}

double VWEditRealCtrl::GetEditReal(EEditControlType type) const
{
	double value = 0.0;

	this->GetEditReal(type, value);

	return value;
}

bool VWEditRealCtrl::GetEditReal(EEditControlType type, double& outValue) const
{
	return ::GS_GetEditReal( gCBP, fpParentDlg->GetControlID(), fControlID, type, outValue );
}

void VWEditRealCtrl::SetEditReal(double value, EEditControlType type)
{
	::GS_SetEditReal( gCBP, fpParentDlg->GetControlID(), fControlID, type, value );
}

void VWEditRealCtrl::SelectContent()
{
	::GS_SelectEditText( gCBP, fpParentDlg->GetControlID(), fControlID );
}

void VWEditRealCtrl::SetColor(const VWFC::Tools::CRGBColor& color)
{
	SControlData_EditReal	data;
	GSColor					gsColor;	gsColor.Set8( color.GetRed(), color.GetGreen(), color.GetBlue() );
	data.fTextTint	= CoreUiTintSupport::ExpressColorAsTint( gsColor );
	gSDK->SetControlData( fpParentDlg->GetControlID(), fControlID, data );
}
