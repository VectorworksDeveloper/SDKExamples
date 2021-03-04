//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/EditIntegerCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWEditIntegerCtrl::VWEditIntegerCtrl(TControlID id)
: VWControl( id )
{
}

VWEditIntegerCtrl::~VWEditIntegerCtrl()
{
}

bool VWEditIntegerCtrl::CreateControl(VWDialog* pDlg, Sint32 lDefaultValue, short widthInStdChar)
{
	::GS_CreateEditInteger( gCBP, pDlg->GetControlID(), fControlID, lDefaultValue, widthInStdChar );
	return VWControl::CreateControl( pDlg );
}


Sint32 VWEditIntegerCtrl::GetEditInteger() const
{
	Sint32 value = 0;
	this->GetEditInteger( value );

	return value;
}

bool VWEditIntegerCtrl::GetEditInteger(Sint32& outValue) const
{
	return ::GS_GetEditInteger( gCBP, fpParentDlg->GetControlID(), fControlID, outValue );
}

void VWEditIntegerCtrl::SetEditInteger(Sint32 value)
{
	::GS_SetEditInteger( gCBP, fpParentDlg->GetControlID(), fControlID, value );
}

void VWEditIntegerCtrl::SelectContent()
{
	::GS_SelectEditText( gCBP, fpParentDlg->GetControlID(), fControlID );
}