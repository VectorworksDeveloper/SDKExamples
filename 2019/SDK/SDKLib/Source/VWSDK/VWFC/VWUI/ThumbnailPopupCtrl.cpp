//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ThumbnailPopupCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWThumbnailPopupCtrl::VWThumbnailPopupCtrl(TControlID id)
: VWControl( id )
{
}

VWThumbnailPopupCtrl::~VWThumbnailPopupCtrl()
{
}

bool VWThumbnailPopupCtrl::CreateControl(VWDialog* pDlg, ThumbnailSizeType sizeType /*= kStandardSize*/)
{
	gSDK->CreateCustomThumbnailPopup(pDlg->GetControlID(), fControlID, sizeType);

    return VWControl::CreateControl( pDlg );
}

void VWThumbnailPopupCtrl::AddImage(InternalIndex item)
{
	::GS_InsertImagePopupObjectItem( gCBP, fpParentDlg->GetControlID(), fControlID, item );
}

void VWThumbnailPopupCtrl::AddImageFromResource(Sint32 listID, size_t index)
{
	::GS_InsertImagePopupResource(  gCBP, fpParentDlg->GetControlID(), fControlID, listID, (Sint32) index+1 ); 
}

void VWThumbnailPopupCtrl::RemoveAllImages()
{
	::GS_RemoveAllImagePopupItems( gCBP, fpParentDlg->GetControlID(), fControlID );
}

bool VWThumbnailPopupCtrl::RemoveItem(size_t itemIndex)
{
	ASSERTN( kVStanev, itemIndex < this->GetItemsCount() );
	// NOTE: itemIndex is zero based
	// but the SDK functions wants 1 based ... fix that with +1
	return ::GS_RemoveImagePopupItem( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, itemIndex+1 ) ) ? true : false;
}

bool VWThumbnailPopupCtrl::SelectItem(size_t itemIndex)
{
	ASSERTN( kVStanev, 0 <= itemIndex && itemIndex < this->GetItemsCount() );
	// NOTE: itemIndex is zero based
	// but the SDK functions wants 1 based ... fix that with +1
	return ::GS_SetImagePopupSelectedItem( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, itemIndex+1 ) ) ? true : false;
}

bool VWThumbnailPopupCtrl::SelectItem(InternalIndex item)
{
	size_t	itemIndex	= this->GetObjectItemIndex( item );
	if ( itemIndex == (size_t) -1 || itemIndex >= this->GetItemsCount() )
		return false;

	return this->SelectItem( itemIndex );
}

InternalIndex VWThumbnailPopupCtrl::GetItemObject(size_t itemIndex) const
{
	ASSERTN( kVStanev, itemIndex < this->GetItemsCount() );
	// NOTE: itemIndex is zero based
	// but the SDK functions wants 1 based ... fix that with +1
	return ::GS_GetImagePopupObject( gCBP, fpParentDlg->GetControlID(), fControlID, (short)itemIndex+1 );
}

size_t VWThumbnailPopupCtrl::GetObjectItemIndex(InternalIndex item) const
{
	short	index	= ::GS_GetImagePopupObjectItemIndex( gCBP, fpParentDlg->GetControlID(), fControlID, item );
	// NOTE: itemIndex is zero based
	// but the SDK functions returns 1 based ... fix that with -1
	ASSERTN( kVStanev, index >= 0 );
	return (size_t) ( index - 1 ); 
}

size_t VWThumbnailPopupCtrl::GetSelectedItemIndex() const
{
	short	sel = ::GS_GetImagePopupSelectedItem( gCBP, fpParentDlg->GetControlID(), fControlID );
	// NOTE: itemIndex is zero based
	// but the SDK functions returns 1 based ... fix that with -1
	ASSERTN( kVStanev, sel >= 0 );
	return (size_t) ( sel - 1 ); 
}

InternalIndex VWThumbnailPopupCtrl::GetSelectedItem() const
{
	short	sel = ::GS_GetImagePopupSelectedItem( gCBP, fpParentDlg->GetControlID(), fControlID );
	return ::GS_GetImagePopupObject( gCBP, fpParentDlg->GetControlID(), fControlID, sel );
}

size_t VWThumbnailPopupCtrl::GetItemsCount() const
{
	return (size_t) ::GS_GetNumImagePopupItems( gCBP, fpParentDlg->GetControlID(), fControlID );
}
