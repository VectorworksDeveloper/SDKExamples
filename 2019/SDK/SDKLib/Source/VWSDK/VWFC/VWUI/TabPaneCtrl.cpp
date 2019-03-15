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

EVENT_DISPATCH_MAP_BEGIN( VWTabPaneCtrl );
EVENT_DISPATCH_MAP_END;

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

void VWTabPaneCtrl::OnDDXInitialize()
{
}

void VWTabPaneCtrl::OnInitializeContent()
{
}

void VWTabPaneCtrl::OnSetUpEvent()
{
}

void VWTabPaneCtrl::OnSetDownEvent()
{
}

void VWTabPaneCtrl::OnUpdateUI()
{
}

bool VWTabPaneCtrl::CanEnableOK()
{
	return true;
}
