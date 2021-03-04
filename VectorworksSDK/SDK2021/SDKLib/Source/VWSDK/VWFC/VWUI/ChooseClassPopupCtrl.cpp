//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ChooseClassPopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWChooseClassPopupCtrl::VWChooseClassPopupCtrl(TControlID id)
	: VWControl( id )
{
}

VWChooseClassPopupCtrl::~VWChooseClassPopupCtrl()
{
}

bool VWChooseClassPopupCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar, bool bShowDefaultStaticItems /*= true*/)
{
	gSDK->CreateClassPullDownMenuN( pDlg->GetDialogID(), fControlID, widthInStdChar, bShowDefaultStaticItems);
	return VWControl::CreateControl( pDlg );
}

size_t VWChooseClassPopupCtrl::GetSelectedIndex() const
{
	short	nItemIndex	= -1;
	::GS_GetSelectedChoiceIndex( gCBP, fpParentDlg->GetControlID(), fControlID, nItemIndex );
	return (size_t) nItemIndex;
}

void VWChooseClassPopupCtrl::SelectIndex( size_t  nIndex )
{
	gSDK->SelectChoice( fpParentDlg->GetControlID(), fControlID, (short) nIndex );	
}

void VWChooseClassPopupCtrl::GetSelectedClass( TXString & selectedClass ) const
{
	short nIndex;
	gSDK->GetSelectedChoiceIndex( fpParentDlg->GetControlID(), fControlID, nIndex) ;

	gSDK->GetChoiceText( fpParentDlg->GetControlID(), fControlID, nIndex, selectedClass );
}

void VWChooseClassPopupCtrl::SetSelectedClass( const TXString & selectedClass )
{
	bool bClassExists = false;
	MCObjectHandle hClass = gSDK->GetNamedObject( selectedClass );
	if ( hClass ) {
		if ( gSDK->GetObjectTypeN( hClass ) == kClassDefNode ) {
			bClassExists = true;
		}
	}

	
	short nItemIndex	= -1;
	if ( bClassExists ) {
		gSDK->GetChoiceIndex( fpParentDlg->GetControlID(), fControlID, selectedClass, nItemIndex );
		if ( nItemIndex >= 0 ) {
			gSDK->SelectChoice( fpParentDlg->GetControlID(), fControlID, nItemIndex );
		}
	}
	else {
		gSDK->GetChoiceIndex( fpParentDlg->GetControlID(), fControlID, selectedClass, nItemIndex );
		if ( nItemIndex == -1 ) {
			this->InsertProposedClass( selectedClass );
			gSDK->GetChoiceIndex( fpParentDlg->GetControlID(), fControlID, selectedClass, nItemIndex );
		}
			
		if ( nItemIndex >= 0 ) {
			gSDK->SelectChoice( fpParentDlg->GetControlID(), fControlID, nItemIndex );
		}
	}

}

void VWChooseClassPopupCtrl::InsertProposedClass( const TXString & proposedClass )
{
	gSDK->InsertProposedClassOrLayerItem( fpParentDlg->GetControlID(), fControlID, proposedClass, "");
}

void VWChooseClassPopupCtrl::Refresh()
{
	gSDK->RefreshClassPopup( fpParentDlg->GetControlID(), fControlID );
}

bool VWChooseClassPopupCtrl::GetChoiceIndex(const TXString& choiceToFind, size_t& choiceIndex ) const
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

