//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/TreeCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

// ------------------------------------------------------------------------------------------------------------
VWTreeCtrl::VWTreeCtrl(TControlID id)
	: VWControl( id )
	, VWTreeCtrlContainer( -1, -1, -1 )
{
}

VWTreeCtrl::~VWTreeCtrl()
{
	auto it = s_DlgReeCtrlMap.find( std::pair<Sint32,Sint32>( fDialogID, fThisControlID ) );
	if ( it != s_DlgReeCtrlMap.end() )
	{
		s_DlgReeCtrlMap.erase( it );
	}
}

bool VWTreeCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar, short heightInLines/*=1*/)
{
	gSDK->CreateTreeControl( pDlg->GetControlID(), fControlID, widthInStdChar, heightInLines );
	fDialogID		= pDlg->GetControlID();
	fThisControlID	= fControlID;
	fThisItemID		= -1;
	return VWControl::CreateControl( pDlg );
}

void VWTreeCtrl::AttachControl()
{
	fDialogID		= fpParentDlg->GetControlID();
	fThisControlID	= fControlID;
	fThisItemID		= -1;
}

bool VWTreeCtrl::EnableDragAndDrop(bool enable)
{
	return gSDK->EnableTreeControlDragAndDrop( fpParentDlg->GetControlID(), fControlID, enable ) ? true : false;
}

void VWTreeCtrl::EnableDrag(const VWTreeCtrl& dragToCtrl)
{
	 gSDK->EnableDragBetweenControls( fpParentDlg->GetControlID(), fControlID, dragToCtrl.GetControlID() );
}

/*static*/ VWTreeCtrl::TDlgTreeCtrlMap VWTreeCtrl::s_DlgReeCtrlMap;

/*static*/ bool VWTreeCtrl::_ShowButtonColumn(Sint32 dialogID, Sint32 controlID, int itemID)
{
	bool result = false;
	auto it = s_DlgReeCtrlMap.find( std::pair<Sint32,Sint32>( dialogID, controlID ) );
	if ( it != s_DlgReeCtrlMap.end() )
	{
		result = it->second->ShowButtonColumn( itemID );
	}

	return result;
}

/*static*/ void VWTreeCtrl::_HandleButtonColumn(Sint32 dialogID, Sint32 controlID, int itemID)
{
	auto it = s_DlgReeCtrlMap.find( std::pair<Sint32,Sint32>( dialogID, controlID ) );
	if ( it != s_DlgReeCtrlMap.end() )
	{
		it->second->HandleButtonColumn( itemID );
	}
}

bool VWTreeCtrl::ShowButtonColumn(int itemID)
{
	bool result = false;
	if ( fButtonColumnShowCallback )
	{
		result = fButtonColumnShowCallback( VWTreeCtrlItem( fDialogID, fControlID, itemID ) );
	}

	return result;
}

void VWTreeCtrl::HandleButtonColumn(int itemID)
{
	if ( fButtonColumnShowCallback )
	{
		fButtonColumnHandleCallback( VWTreeCtrlItem( fDialogID, fControlID, itemID ) );
	}
}

void VWTreeCtrl::EnableButtonColumn(const TXString& text, TShowCallback showForItemCallback, THandleCallback handleForItemCallback)
{
	fButtonColumnShowCallback	= showForItemCallback;
	fButtonColumnHandleCallback	= handleForItemCallback;

	s_DlgReeCtrlMap[ std::pair<Sint32,Sint32>( fDialogID, fThisControlID ) ] = this;

	AllowButtonColumnInTreeInput bIn(	fpParentDlg->GetControlID(), fControlID,
										text,
										VWTreeCtrl::_ShowButtonColumn,
										VWTreeCtrl::_HandleButtonColumn
									);

	const int kAllowButtonColumnInTree = -32002;
	gSDK->Kludge( kAllowButtonColumnInTree, &bIn, NULL );
}

void VWTreeCtrl::Clear()
{
	gSDK->RemoveAllTreeControlItems( fpParentDlg->GetControlID(), fControlID );
}

VWTreeCtrlItem VWTreeCtrl::GetItem(TTreeItemID itemID)
{
	return VWTreeCtrlItem( fDialogID, fControlID, itemID );
}

VWTreeCtrlItem VWTreeCtrl::GetSelectedItem()
{
	VWTreeCtrlItem	item;
	Sint32				itemID	= -1;
	if ( fpParentDlg && gSDK->GetTreeControlSelectedItem( fpParentDlg->GetControlID(), fControlID, itemID ) )
	{
		return VWTreeCtrlItem( fDialogID, fControlID, itemID );
	}
	else
	{
		return VWTreeCtrlContainer::kEmptyTreeItem;
	}
}

bool VWTreeCtrl::GetSelectedItem(TXString& outText)
{
	return gSDK->GetTreeControlSelectedItemText( fpParentDlg->GetControlID(), fControlID, outText ) ? true : false;
}


void VWTreeCtrl::CopySubtree(const VWTreeCtrl& targetTree, const VWTreeCtrlItem& sourceItem, const VWTreeCtrlItem& targetItem)
{
	int res = gSDK->CopyTreeControlSubtree( fpParentDlg->GetControlID(), fControlID, targetTree.fControlID, sourceItem.GetItemID(), targetItem.GetItemID(), targetItem.GetParentItem().GetItemID() );
	res;
}


