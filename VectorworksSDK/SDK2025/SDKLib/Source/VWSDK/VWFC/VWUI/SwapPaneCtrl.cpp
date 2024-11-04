//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"

#include "VWFC/VWUI/SwapPaneCtrl.h"


using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWSwapPaneCtrl::VWSwapPaneCtrl(TControlID id)
: VWControlsContainer( id, {eCompSwapControl} )
{
}

VWSwapPaneCtrl::~VWSwapPaneCtrl()
{
}

bool VWSwapPaneCtrl::CreateControl(VWDialog* pDlg, bool bHasFrame /*=true*/)
{
	::GS_CreateGroupBox( gCBP, pDlg->GetControlID(), fControlID, TXString(""), bHasFrame );
	return VWControl::CreateControl( pDlg );
}
