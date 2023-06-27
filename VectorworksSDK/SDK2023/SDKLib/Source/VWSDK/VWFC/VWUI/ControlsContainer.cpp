//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ControlsContainer.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

EVENT_DISPATCH_MAP_BEGIN( VWControlsContainer );
EVENT_DISPATCH_MAP_END;

VWControlsContainer::VWControlsContainer(TControlID id)
: VWControl( id )
{
}

VWControlsContainer::~VWControlsContainer()
{
}

bool VWControlsContainer::CreateControl(VWDialog* pDlg)
{
	return VWControl::CreateControl( pDlg );
}

void VWControlsContainer::AddFirstGroupControl(VWControl* pControl)
{
	if ( fpParentDlg ) {
		VERIFYN( kVStanev, ::GS_SetFirstGroupItem( gCBP, fpParentDlg->GetControlID(), fControlID, pControl->GetControlID() ) );
		fpParentDlg->AddControl( pControl );
	}
}

void VWControlsContainer::OnDDXInitialize()
{
}

void VWControlsContainer::OnInitializeContent()
{
}

void VWControlsContainer::OnSetUpEvent()
{
}

void VWControlsContainer::OnSetDownEvent()
{
}

void VWControlsContainer::OnUpdateUI()
{
}

bool VWControlsContainer::CanEnableOK()
{
	return true;
}

void VWControlsContainer::OnBeforeDispatchEvent(TControlID controlID, VWDialogEventArgs& eventArg)
{
}

void VWControlsContainer::OnDefaultButtonEvent()
{
}

void VWControlsContainer::OnCancelButtonEvent()
{
}

