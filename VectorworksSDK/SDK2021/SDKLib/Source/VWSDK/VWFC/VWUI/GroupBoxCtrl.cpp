//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/GroupBoxCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWGroupBoxCtrl::VWGroupBoxCtrl(TControlID id)
: VWControlsContainer( id )
{
}

VWGroupBoxCtrl::~VWGroupBoxCtrl()
{
}

bool VWGroupBoxCtrl::CreateControl(VWDialog* pDlg, const TXString& text, bool bHasFrame/*=true*/)
{
	::GS_CreateGroupBox( gCBP, pDlg->GetControlID(), fControlID, text, bHasFrame );
	return VWControl::CreateControl( pDlg );
}
