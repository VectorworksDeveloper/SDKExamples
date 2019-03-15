//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ChooseLayerPopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWChooseLayerPopupCtrl::VWChooseLayerPopupCtrl(TControlID id)
	: VWControl( id )
{
    
}

VWChooseLayerPopupCtrl::~VWChooseLayerPopupCtrl()
{
    
}

bool VWChooseLayerPopupCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar, EChooseLayerControlType type)
{
	switch (type) {
		case EChooseLayerControlType::eAllLayers: {
            gSDK->CreateLayerPullDownMenu(pDlg->GetDialogID(), fControlID, widthInStdChar);
			break;
		}

		case EChooseLayerControlType::eDesignLayers: {
			gSDK->CreateDesignLayerPullDownMenu(pDlg->GetDialogID(), fControlID, widthInStdChar);
			break;
		}

		case EChooseLayerControlType::eSheetLayers: {
			gSDK->CreateSheetLayerPullDownMenu(pDlg->GetDialogID(), fControlID, widthInStdChar);
			break;
		}

		default: {
			DSTOP((kILane, "Trying to create a choose layer popup with an incorrect type!"));
		}
	}

	return VWControl::CreateControl( pDlg );
}

short VWChooseLayerPopupCtrl::GetSelectedIndex() const
{
	short	nItemIndex	= -1;
    gSDK->GetSelectedChoiceIndex(fpParentDlg->GetControlID(), fControlID, nItemIndex);
	return nItemIndex;
}

void VWChooseLayerPopupCtrl::SelectIndex( short  nIndex )
{
	gSDK->SelectChoice( fpParentDlg->GetControlID(), fControlID, (short) nIndex );	
}

void VWChooseLayerPopupCtrl::GetSelectedLayer( TXString & selectedLayer ) const
{
	short nIndex;
	gSDK->GetSelectedChoiceIndex( fpParentDlg->GetControlID(), fControlID, nIndex) ;
	gSDK->GetChoiceText( fpParentDlg->GetControlID(), fControlID, nIndex, selectedLayer);
}

void VWChooseLayerPopupCtrl::SetSelectedLayer( const TXString & selectedLayer )
{
	bool bLayerExists = false;
	MCObjectHandle hLayer = gSDK->GetNamedObject(selectedLayer);
	if (hLayer) {
		if ( gSDK->GetObjectTypeN(hLayer) == kLayerNode ) {
			bLayerExists = true;
		}
	}

	short nItemIndex	= -1;
	if (bLayerExists) {
		gSDK->GetChoiceIndex( fpParentDlg->GetControlID(), fControlID, selectedLayer, nItemIndex );
		if ( nItemIndex >= 0 ) {
			gSDK->SelectChoice( fpParentDlg->GetControlID(), fControlID, nItemIndex );
		}
	}
	else {
		gSDK->GetChoiceIndex( fpParentDlg->GetControlID(), fControlID, selectedLayer, nItemIndex );
		if ( nItemIndex == -1 ) {
			this->InsertProposedLayer(selectedLayer);
			gSDK->GetChoiceIndex( fpParentDlg->GetControlID(), fControlID, selectedLayer, nItemIndex );
		}
			
		if ( nItemIndex >= 0 ) {
			gSDK->SelectChoice( fpParentDlg->GetControlID(), fControlID, nItemIndex );
		}
	}

}

void VWChooseLayerPopupCtrl::InsertProposedLayer( const TXString & proposedLayer )
{
	gSDK->InsertProposedClassOrLayerItem( fpParentDlg->GetControlID(), fControlID, proposedLayer, "");
}

void VWChooseLayerPopupCtrl::Refresh()
{
	gSDK->RefreshClassPopup( fpParentDlg->GetControlID(), fControlID );
}


