//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/SliderCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWSliderCtrl::VWSliderCtrl(TControlID id)
: VWControl( id )
{
}

VWSliderCtrl::~VWSliderCtrl()
{
}

bool VWSliderCtrl::CreateControl(VWDialog* pDlg, Sint32 lSliderSize)
{
	::GS_CreateControl( gCBP, pDlg->GetControlID(), fControlID, kSliderControl, "", lSliderSize ); 
	return VWControl::CreateControl( pDlg );
}


Sint32 VWSliderCtrl::GetSliderValue() const
{
	SControlData_Slider value( 0 );
	gSDK->GetControlData( fpParentDlg->GetControlID(), fControlID, value );
	return value.fSliderPos;
}

void VWSliderCtrl::SetSliderValue(Sint32 value)
{
	gSDK->SetControlData( fpParentDlg->GetControlID(), fControlID, SControlData_Slider(value) );
}

void VWSliderCtrl::SetSliderLiveUpdate(bool liveUpdate)
{
	gSDK->SetSliderLiveUpdate( fpParentDlg->GetControlID(), fControlID, liveUpdate );
}