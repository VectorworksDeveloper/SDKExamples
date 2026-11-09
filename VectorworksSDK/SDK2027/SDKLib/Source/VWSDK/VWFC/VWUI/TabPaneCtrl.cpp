//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"

#include "VWFC/VWUI/TabPaneCtrl.h"


using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWTabPaneCtrl::VWTabPaneCtrl(TControlID id)
: VWControlsContainer( id, {eCompLayout} )
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
