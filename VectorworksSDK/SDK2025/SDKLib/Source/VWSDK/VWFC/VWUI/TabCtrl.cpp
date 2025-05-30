//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"

#include "VWFC/VWUI/TabCtrl.h"


using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWTabCtrl::VWTabCtrl(TControlID id)
: VWControl( id, {eCompTabControl} )
{
}

VWTabCtrl::~VWTabCtrl()
{
}

bool VWTabCtrl::CreateControl(VWDialog* pDlg)
{
	::GS_CreateTabControl( gCBP, pDlg->GetControlID(), (short)fControlID );
	return VWControl::CreateControl( pDlg );;
}

void VWTabCtrl::AddPane(VWTabPaneCtrl* pPane)
{
	::GS_CreateTabPane( gCBP, fpParentDlg->GetControlID(), (short)fControlID, (short)pPane->GetControlID() );
}

TControlID VWTabCtrl::GetActivePaneControlID() const
{
	return ::GS_GetActivePane( gCBP, fpParentDlg->GetControlID(), fControlID );
}

void VWTabCtrl::SetActivePaneControlID(TControlID paneControlID)
{
	::GS_DisplayTabPane( gCBP, fpParentDlg->GetControlID(), fControlID, paneControlID );
}
