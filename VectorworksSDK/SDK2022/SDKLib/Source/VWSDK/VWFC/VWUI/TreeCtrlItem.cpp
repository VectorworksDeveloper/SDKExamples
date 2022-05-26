//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/TreeCtrlItem.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWTreeCtrlItem	VWTreeCtrlContainer::kEmptyTreeItem;

// ---------------------------------------------------------------------------------------------------------------
VWTreeCtrlContainer::VWTreeCtrlContainer(TControlID dialogID, TControlID controlID, TTreeItemID itemID)
{
	fDialogID		= dialogID;
	fThisControlID	= controlID;
	fThisItemID		= itemID;
}

VWTreeCtrlContainer::VWTreeCtrlContainer(const VWTreeCtrlContainer& src)
{
	this->operator = ( src );
}

VWTreeCtrlContainer::~VWTreeCtrlContainer()
{
}

VWTreeCtrlContainer& VWTreeCtrlContainer::operator=(const VWTreeCtrlContainer& src)
{
	fDialogID		= src.fDialogID;
	fThisControlID	= src.fThisControlID;
	fThisItemID		= src.fThisItemID;

	return *this;
}

bool VWTreeCtrlContainer::operator==(const VWTreeCtrlContainer& src)
{
	return
			fDialogID		== src.fDialogID
		&&	fThisControlID	== src.fThisControlID
		&&	fThisItemID		== src.fThisItemID;
}

bool VWTreeCtrlContainer::operator!=(const VWTreeCtrlContainer& src)
{
	return ! this->operator == ( src );
}

bool VWTreeCtrlContainer::IsValid() const
{
	return (fDialogID != -1 && fThisControlID != -1);
}

VWTreeCtrlItem VWTreeCtrlContainer::GetParentItem() const
{
	Sint32 parentID;
	if ( gSDK->GetTreeControlItemParent( fDialogID, fThisControlID, fThisItemID, parentID ) )
	{
		return VWTreeCtrlItem( fDialogID, fThisControlID, parentID );
	}
	else
	{
		return VWTreeCtrlContainer::kEmptyTreeItem;
	}
}

size_t VWTreeCtrlContainer::GetChildItemsCount() const
{
	return gSDK->GetTreeControlItemNumberOfChildren( fDialogID, fThisControlID, fThisItemID );
}

VWTreeCtrlItem VWTreeCtrlContainer::GetChildItemAt(size_t index) const
{
	size_t itemsCnt = gSDK->GetTreeControlItemNumberOfChildren( fDialogID, fThisControlID, fThisItemID );
	if ( index < itemsCnt )
	{
		TTreeItemID	itemID = gSDK->GetTreeControlItemChildID( fDialogID, fThisControlID, fThisItemID, Sint32(index) );
		return VWTreeCtrlItem( fDialogID, fThisControlID, itemID );
	}
	else
	{
		return VWTreeCtrlContainer::kEmptyTreeItem;
	}
}

VWTreeCtrlItem VWTreeCtrlContainer::AddChildItem(const TXString& text, bool addFirst)
{
	if ( ! this->IsValid() )
		return VWTreeCtrlContainer::kEmptyTreeItem;


	TTreeItemID		afterItemID	= -1;
	if ( addFirst == false )
	{
		size_t itemsCnt = gSDK->GetTreeControlItemNumberOfChildren( fDialogID, fThisControlID, fThisItemID );
		if ( itemsCnt > 0 && itemsCnt != size_t(-1) )
		{
			afterItemID = gSDK->GetTreeControlItemChildID( fDialogID, fThisControlID, fThisItemID, Sint32(itemsCnt - 1) );
		}
	}

	TTreeItemID		newItemID	= gSDK->InsertTreeControlItem( fDialogID, fThisControlID, text, fThisItemID, afterItemID );

	return VWTreeCtrlItem( fDialogID, fThisControlID, newItemID );
}

VWTreeCtrlItem VWTreeCtrlContainer::InsertChildItem(const TXString& text, const VWTreeCtrlItem& afterItem)
{
	if ( ! this->IsValid() )
		return VWTreeCtrlContainer::kEmptyTreeItem;

	TTreeItemID		newItemID	= gSDK->InsertTreeControlItem( fDialogID, fThisControlID, text, fThisItemID, afterItem.fThisItemID );

	return VWTreeCtrlItem( fDialogID, fThisControlID, newItemID );
}

void VWTreeCtrlContainer::DeleteItem()
{
	if ( this->IsValid() ) {
		VERIFYN( kVStanev, gSDK->RemoveTreeControlItem( fDialogID, fThisControlID, fThisItemID ) );
	}
}

// ---------------------------------------------------------------------------------------------------------------
VWTreeCtrlItem::VWTreeCtrlItem()
	: VWTreeCtrlContainer( -1, -1, -1 )
{
}

VWTreeCtrlItem::VWTreeCtrlItem(TControlID dialogID, TControlID controlID, TTreeItemID itemID)
	: VWTreeCtrlContainer( dialogID, controlID, itemID )
{
}

VWTreeCtrlItem::VWTreeCtrlItem(const VWTreeCtrlItem& src)
	: VWTreeCtrlContainer( src )
{
}

VWTreeCtrlItem::~VWTreeCtrlItem()
{
}

VWTreeCtrlItem&	VWTreeCtrlItem::operator=(const VWTreeCtrlItem& src)
{
	((VWTreeCtrlContainer*)this)->operator = ( src );

	return *this;
}

bool VWTreeCtrlItem::operator==(const VWTreeCtrlItem& src)
{
	return ((VWTreeCtrlContainer*)this)->operator == ( src );
}

bool VWTreeCtrlItem::operator!=(const VWTreeCtrlItem& src)
{
	return ((VWTreeCtrlContainer*)this)->operator != ( src );
}

void VWTreeCtrlItem::ExpandItem(bool bExpand)
{
	if ( this->IsValid() ) {
		gSDK->ExpandTreeControlItem( fDialogID, fThisControlID, fThisItemID, bExpand );
	}
}

void VWTreeCtrlItem::SelectItem()
{
	if ( this->IsValid() ) {
		VERIFYN( kVStanev, gSDK->SelectTreeControlItem( fDialogID, fThisControlID, fThisItemID ) );
	}
}

void VWTreeCtrlItem::SelectItem(bool selectionState)
{
	if ( this->IsValid() ) {
		gSDK->SetTreeControlItemSelectionState( fDialogID, fThisControlID, fThisItemID, selectionState );
	}
}

TTreeItemID VWTreeCtrlItem::GetItemID() const
{
	return fThisItemID;
}


void VWTreeCtrlItem::SetItemData(SintptrT data)
{
	if ( this->IsValid() ) {
		VERIFYN( kVStanev, gSDK->SetTreeControlItemData( fDialogID, fThisControlID, fThisItemID, data ) );
	}
}

SintptrT VWTreeCtrlItem::GetItemData() const
{
	if ( ! this->IsValid() )
		return 0;

	SintptrT	data	= 0;
	VERIFYN( kVStanev, gSDK->GetTreeControlItemData( fDialogID, fThisControlID, fThisItemID, data ) );
	return data;
}

TXString VWTreeCtrlItem::GetItemText() const
{
	TXString	result;
	if ( this->IsValid() ) {
		VERIFYN( kVStanev, gSDK->GetTreeControlItemText( fDialogID, fThisControlID, fThisItemID, result ) );
	}

	return result;
}

void VWTreeCtrlItem::SetItemTextRight(const TXString & data)
{
	if ( this->IsValid() ) {
		VERIFYN( kVStanev, gSDK->SetTreeControlItemData2( fDialogID, fThisControlID, fThisItemID, data ) );
	}
}

void VWTreeCtrlItem::SetItemImage(const TXString & imageSpecifier)
{
	if ( this->IsValid() ) {
		VERIFYN( kVStanev, gSDK->SetTreeControlItemImage( fDialogID, fThisControlID, fThisItemID, imageSpecifier ) );
	}
}

void VWTreeCtrlItem::SetItemImageFromIcon(VectorWorks::UI::IIcon* icon)
{
	if ( this->IsValid() ) {
		VERIFYN( kVStanev, gSDK->SetTreeControlItemImageFromIcon( fDialogID, fThisControlID, fThisItemID, icon ) );
	}
}

void VWTreeCtrlItem::SetItemAsDivider(bool isDivider)
{
	if ( this->IsValid() ) {
		gSDK->SetTreeControlItemAsDivider( fDialogID, fThisControlID, fThisItemID, isDivider );
	}
}

bool VWTreeCtrlItem::GetItemCheck(ECheckButtonCtrlState& outState) const
{
	bool result = false;
	if ( this->IsValid() ) {
		Sint32 state;
		result = gSDK->GetTreeControlItemCheckBoxState( fDialogID, fThisControlID, fThisItemID, state );
		if ( result )
		{
			switch ( state )
			{
				case eCheckButtonCtrlState_Unchecked	: outState = eCheckButtonCtrlState_Unchecked	; break;
				case eCheckButtonCtrlState_Checked		: outState = eCheckButtonCtrlState_Checked		; break;
				case eCheckButtonCtrlState_Undetermined	: outState = eCheckButtonCtrlState_Undetermined	; break;
				default: result = false; break;
			}
		}
	}
	return result;
}

ECheckButtonCtrlState VWTreeCtrlItem::GetItemCheck() const
{
	ECheckButtonCtrlState	result = eCheckButtonCtrlState_Unchecked;
	this->GetItemCheck( result );
	return result;
}

void VWTreeCtrlItem::SetItemCheck(ECheckButtonCtrlState state)
{
	if ( this->IsValid() ) {
		VERIFYN( kVStanev, gSDK->SetTreeControlItemCheckBoxState( fDialogID, fThisControlID, fThisItemID, state ) );
	}
}













