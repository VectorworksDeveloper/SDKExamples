//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/StandardIconCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWStadanrdIconCtrl::VWStadanrdIconCtrl(TControlID id)
: VWControl( id )
{
}

VWStadanrdIconCtrl::~VWStadanrdIconCtrl()
{
}

bool VWStadanrdIconCtrl::CreateControl(VWDialog* pDlg, EStandardIconType icon)
{
	::GS_CreateStandardIconControl( gCBP, pDlg->GetControlID(), fControlID, (Sint32) icon );
	return VWControl::CreateControl( pDlg );
}
