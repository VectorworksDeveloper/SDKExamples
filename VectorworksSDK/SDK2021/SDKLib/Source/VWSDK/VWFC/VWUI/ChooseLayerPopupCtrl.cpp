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

bool VWChooseLayerPopupCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar, EChooseLayerControlType type, bool bShowDefaultStaticItems /*= true*/)
{
	switch (type) {
		case EChooseLayerControlType::eAllLayers: {
            gSDK->CreateLayerPullDownMenuN(pDlg->GetDialogID(), fControlID, widthInStdChar, bShowDefaultStaticItems);
			break;
		}

		case EChooseLayerControlType::eDesignLayers: {
			gSDK->CreateDesignLayerPullDownMenuN(pDlg->GetDialogID(), fControlID, widthInStdChar, bShowDefaultStaticItems);
			break;
		}

		case EChooseLayerControlType::eSheetLayers: {
			gSDK->CreateSheetLayerPullDownMenuN(pDlg->GetDialogID(), fControlID, widthInStdChar, bShowDefaultStaticItems);
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

void VWChooseLayerPopupCtrl::SelectIndex(short  nIndex)
{
	gSDK->SelectChoice( fpParentDlg->GetControlID(), fControlID, (short) nIndex );	
}

void VWChooseLayerPopupCtrl::GetSelectedLayer(TXString& selectedLayer) const
{
	short		nIndex;

	gSDK->GetSelectedChoiceIndex( fpParentDlg->GetControlID(), fControlID, nIndex) ;
	gSDK->GetChoiceText( fpParentDlg->GetControlID(), fControlID, nIndex, selectedLayer);
}

void VWChooseLayerPopupCtrl::SetSelectedLayer(const TXString& selectedLayer)
{
	bool			bLayerExists	= false;
	MCObjectHandle	hLayer			= gSDK->GetNamedLayer( selectedLayer );
	TXString		itemText( selectedLayer );

	if ( hLayer )
	{
		if ( VWLayerObj::IsLayerObject( hLayer ) )
		{
			VWLayerObj layerObj( hLayer );

			if ( layerObj.GetLayerType() == kLayerSheet )
			{
				itemText = layerObj.GetNameExpanded();
			}

			bLayerExists = true;
		}
	}

	short nItemIndex	= -1;
	if ( bLayerExists )
	{
		gSDK->GetChoiceIndex( fpParentDlg->GetControlID(), fControlID, itemText, nItemIndex );
		if ( nItemIndex >= 0 )
		{
			gSDK->SelectChoice( fpParentDlg->GetControlID(), fControlID, nItemIndex );
		}
	}
	else
	{
		gSDK->GetChoiceIndex( fpParentDlg->GetControlID(), fControlID, itemText, nItemIndex );

		if ( nItemIndex == -1 )
		{
			this->InsertProposedLayer( selectedLayer );
			gSDK->GetChoiceIndex( fpParentDlg->GetControlID(), fControlID, selectedLayer, nItemIndex );
		}

		if ( nItemIndex >= 0 )
		{
			gSDK->SelectChoice( fpParentDlg->GetControlID(), fControlID, nItemIndex );
		}
	}

}

void VWChooseLayerPopupCtrl::InsertProposedLayer(const TXString& proposedLayer)
{
	gSDK->InsertProposedClassOrLayerItem( fpParentDlg->GetControlID(), fControlID, proposedLayer, "");
}

void VWChooseLayerPopupCtrl::Refresh()
{
	gSDK->RefreshClassPopup( fpParentDlg->GetControlID(), fControlID );
}

bool VWChooseLayerPopupCtrl::GetChoiceIndex(const TXString& choiceToFind, size_t& choiceIndex) const
{
	bool choiceFound = false;
	short nItemIndex = -1;
	choiceIndex = 0;

	gSDK->GetChoiceIndex(fpParentDlg->GetControlID(), fControlID, choiceToFind, nItemIndex);
	if (nItemIndex >= 0) {
		choiceFound = true;
		choiceIndex = nItemIndex;
	}

	return choiceFound;
}
