//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"



using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWColorPopupCustomCtrl::VWColorPopupCustomCtrl(TControlID id)
: VWControl( id, {eCompColorPopup} )
{
}

VWColorPopupCustomCtrl::~VWColorPopupCustomCtrl()
{
}

bool VWColorPopupCustomCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreateColorPopup( gCBP, pDlg->GetControlID(), fControlID );
	return VWControl::CreateControl( pDlg );
}

ColorRef VWColorPopupCustomCtrl::GetSelectedColor() const
{
	short		colorIndex;
	
	::GS_GetColorChoice( gCBP, fpParentDlg->GetControlID(), fControlID, colorIndex );

	return colorIndex;
}

void VWColorPopupCustomCtrl::SetSelectedColor(const ColorRef &colorIndex)
{
	::GS_SetColorChoice( gCBP, fpParentDlg->GetControlID(), fControlID, colorIndex );
}
