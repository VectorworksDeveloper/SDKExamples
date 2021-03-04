//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/TabPaneCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWTabPaneCtrl::VWTabPaneCtrl(TControlID id)
: VWControlsContainer( id )
{
}

VWTabPaneCtrl::~VWTabPaneCtrl()
{
}

bool VWTabPaneCtrl::CreateControl(VWDialog* pDlg, const TXString& text, bool bHasFrame /*=true*/)
{
	::GS_CreateGroupBox( gCBP, pDlg->GetControlID(), fControlID, text, bHasFrame );
	return VWControl::CreateControl( pDlg );
}
