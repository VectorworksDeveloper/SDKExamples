//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VWFC/VWUI/SwapCtrl.h"


using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWSwapCtrl::VWSwapCtrl(TControlID id)
: VWControl( id, {eCompSwapControl} )
{
}

VWSwapCtrl::~VWSwapCtrl()
{
}

bool VWSwapCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreateSwapControl( gCBP, pDlg->GetControlID(), fControlID );
	return VWControl::CreateControl( pDlg );;
}

void VWSwapCtrl::AddPane(VWSwapPaneCtrl* pPane)
{
	::GS_CreateSwapPane( gCBP, fpParentDlg->GetControlID(), fControlID, pPane->GetControlID() );
}

size_t VWSwapCtrl::GetActivePaneIndex() const
{
	return ::GS_GetActivePane( gCBP, fpParentDlg->GetControlID(), fControlID ); 
}

void VWSwapCtrl::SetActivePaneIndex(size_t paneIndex)
{
	::GS_DisplaySwapPane( gCBP, fpParentDlg->GetControlID(), fControlID, (Sint32) paneIndex ); 
}
