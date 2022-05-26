//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/SwapPaneCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWSwapPaneCtrl::VWSwapPaneCtrl(TControlID id)
: VWControlsContainer( id )
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
