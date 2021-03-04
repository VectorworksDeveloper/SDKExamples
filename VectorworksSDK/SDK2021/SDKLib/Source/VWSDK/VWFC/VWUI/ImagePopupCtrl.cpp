//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ImagePopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWImagePopupCtrl::VWImagePopupCtrl(TControlID id)
: VWControl( id )
{
}

VWImagePopupCtrl::~VWImagePopupCtrl()
{
}

bool VWImagePopupCtrl::CreateControl(VWDialog* pDlg)
{
	// gSDK->Create...
	//return VWControl::CreateControl( pDlg );
	pDlg;
	return false;
}

void VWImagePopupCtrl::SetAdvanced()
{
	gSDK->SetImagePopupResourceAdvanced( fpParentDlg->GetControlID(), fControlID );
}

void VWImagePopupCtrl::RefreshControl()
{
	gSDK->RefreshItem(  fpParentDlg->GetControlID(), fControlID );
}

bool VWImagePopupCtrl::Clear()
{
	return gSDK->RemoveAllImagePopupItems( fpParentDlg->GetControlID(), fControlID) ? true : false;
}

bool VWImagePopupCtrl::RemoveItem(size_t index)
{
	return gSDK->RemoveImagePopupItem( fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, index+1) ) ? true : false;
}

size_t VWImagePopupCtrl::AddItem(InternalIndex objectIndex)
{
	Sint32 index = gSDK->InsertImagePopupObjectItem( fpParentDlg->GetControlID(), fControlID, objectIndex );
	return index <= 0 ? size_t(-1) : size_t(index-1);
}

size_t VWImagePopupCtrl::AddItem(const VWFC::Tools::VWResourceList& resourcList, size_t resourceIndex)
{
	Sint32 index = gSDK->InsertImagePopupResource( fpParentDlg->GetControlID(), fControlID, resourcList.GetListID(), DemoteTo<Sint32>( kVStanev, resourceIndex+1) );
	return index <= 0 ? size_t(-1) : size_t(index-1);
}

void VWImagePopupCtrl::AddItems(const VWFC::Tools::VWResourceList& resourcList)
{
	Sint32	resListID = resourcList.GetListID();
	for(size_t i=0, cnt=resourcList.GetNumItems(); i<cnt; ++i)
	{
		gSDK->InsertImagePopupResource( fpParentDlg->GetControlID(), fControlID, resListID, DemoteTo<Sint32>( kVStanev, i+1) );
	}
}

size_t VWImagePopupCtrl::AddItemSeparator(const TXString& label)
{
	Sint32 index = gSDK->InsertImagePopupSeparator( fpParentDlg->GetControlID(), fControlID, label );
	return index <= 0 ? size_t(-1) : size_t(index-1);
}

size_t VWImagePopupCtrl::GetItemsCount() const
{
	return (size_t) gSDK->GetNumImagePopupItems( fpParentDlg->GetControlID(), fControlID );
}

InternalIndex VWImagePopupCtrl::GetItemInternalIndex(size_t index) const
{
	return gSDK->GetImagePopupObject( fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, index+1) );
}

size_t VWImagePopupCtrl::GetItemIndex(InternalIndex internalIndex) const
{
	return (size_t) gSDK->GetImagePopupObjectItemIndex( fpParentDlg->GetControlID(), fControlID, internalIndex );
}

size_t VWImagePopupCtrl::GetSelectedItemIndex() const
{
	short selIndex = gSDK->GetImagePopupSelectedItem( fpParentDlg->GetControlID(), fControlID );
	return selIndex <= 0 ? size_t(-1) : size_t(selIndex-1);
}

bool VWImagePopupCtrl::SetSelectedItemIndex(size_t index)
{
	return gSDK->SetImagePopupSelectedItem( fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, index+1) ) ? true : false;
}

void VWImagePopupCtrl::SetCategories(const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex)
{
	gSDK->SetImagePopupResourceCategories( fpParentDlg->GetControlID(), fControlID, categoryTitle, categoryArray, categorySelIndex );
}

void VWImagePopupCtrl::PullDownResourceLayoutInit(VectorWorks::Extension::IResourceManagerContent* content)
{
	gSDK->PullDownResourceLayoutInit( fpParentDlg->GetDialogID(), fControlID, content );
}

void VWImagePopupCtrl::PullDownResourceLayoutSetSelectedResourceName(const TXString & name)
{
	if ( !name.IsEmpty() )
	{
		gSDK->PullDownResourceLayoutSetSelectedResourceName( fpParentDlg->GetDialogID(), fControlID, name );
	}
	else
	{
		// init default selection.
		TXString currName = gSDK->PullDownResourceLayoutGetSelectedResourceName( fpParentDlg->GetDialogID(), fControlID );
		gSDK->PullDownResourceLayoutSetSelectedResourceName( fpParentDlg->GetDialogID(), fControlID, currName );
	}
}

TXString VWImagePopupCtrl::PullDownResourceLayoutGetSelectedResourceName() const
{
	return gSDK->PullDownResourceLayoutGetSelectedResourceName( fpParentDlg->GetDialogID(), fControlID );
}

void VWImagePopupCtrl::ShowImage( bool showImage )
{
	gSDK->SetComponentIndeterminate( fpParentDlg->GetDialogID(), fControlID, !showImage );
}
