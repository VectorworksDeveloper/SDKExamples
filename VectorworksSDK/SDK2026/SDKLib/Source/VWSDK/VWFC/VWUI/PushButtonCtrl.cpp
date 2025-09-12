//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"

#include "VWFC/VWUI/PushButtonCtrl.h"


using namespace VWFC::VWUI;
using namespace VectorWorks::Filing;
using namespace VWFC::VWUI::VWControlType;

VWPushButtonCtrl::VWPushButtonCtrl(TControlID id)
: VWControl( id, {eCompPushButton} )
{
}

VWPushButtonCtrl::~VWPushButtonCtrl()
{
}

bool VWPushButtonCtrl::CreateControl(VWDialog* pDlg, const TXString& text)
{
	::GS_CreatePushButton( gCBP, pDlg->GetControlID(), fControlID, text );
	return VWControl::CreateControl( pDlg );
}
