//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/PullDownMenuCtrl.h"

#include "VWFC/VWUI/Dialog.h"


using namespace VWFC::VWUI;

VWPullDownMenuCtrl::VWPullDownMenuCtrl(TControlID id)
: VWControl( id )
{
}

VWPullDownMenuCtrl::~VWPullDownMenuCtrl()
{
}

bool VWPullDownMenuCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar, bool enhanced, bool showIconInMainWindow)
{
	farrIndexToMarker.clear();
	if ( enhanced )
		gSDK->CreateEnhancedPullDownMenu( pDlg->GetControlID(), fControlID, widthInStdChar, showIconInMainWindow );
	else
		gSDK->CreatePullDownMenu( pDlg->GetControlID(), fControlID, widthInStdChar );
	return VWControl::CreateControl( pDlg );
}

void VWPullDownMenuCtrl::Clear()
{
	::GS_DeleteAllItems( gCBP, fpParentDlg->GetControlID(), fControlID );
	farrIndexToMarker.clear();
}

void VWPullDownMenuCtrl::AddItem(const TXString& itemText, size_t insertAt /* = (size_t)-1*/, Sint32 marker /*= 0*/ )
{
	if ( insertAt == (size_t) -1 )
		insertAt		= this->GetItemsCount();

	::GS_AddChoice( gCBP, fpParentDlg->GetControlID(), fControlID, itemText, DemoteTo<short>( kVStanev, insertAt ) );

	farrIndexToMarker.insert( farrIndexToMarker.begin() + insertAt, marker );
}

void VWPullDownMenuCtrl::AddItemSorted(const TXString& itemText, Sint32 marker)
{
	size_t		insertAt	= (size_t) -1;

	TXString	thisItemText;
	size_t		itemsCnt	= this->GetItemsCount();
	for(size_t i=0; i<itemsCnt; i++)
	{
		this->GetItemText( i, thisItemText );
		if ( itemText < thisItemText )
		{
			insertAt	= i;
			break;
		}
	}

	this->AddItem( itemText, insertAt, marker );
}

void VWPullDownMenuCtrl::Erase(size_t itemIndex)
{
	DSTOPIF( itemIndex >= this->GetItemsCount(), (kVStanev, "Deleting item = %d that doesn't exist in VWPullDownMenuCtrl", itemIndex) );

	ASSERTN( kVStanev, itemIndex < farrIndexToMarker.size() );
	if ( itemIndex < farrIndexToMarker.size() ) {
		farrIndexToMarker.erase( farrIndexToMarker.begin() + itemIndex );
	}
	::GS_RemoveChoice( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, itemIndex ) );
}

size_t VWPullDownMenuCtrl::GetItemsCount() const
{
	short numItems	= -1;
	::GS_GetChoiceCount( gCBP, fpParentDlg->GetControlID(), fControlID, numItems );
	return (size_t) numItems;
}

size_t VWPullDownMenuCtrl::GetItemIndex(const TXString& itemText) const
{
	short nItemIndex	= -1;
	::GS_GetChoiceIndex( gCBP, fpParentDlg->GetControlID(), fControlID, itemText, nItemIndex );
	return (size_t) nItemIndex;
}

void VWPullDownMenuCtrl::GetItemText(size_t itemIndex, TXString& outText) const
{
	::GS_GetChoiceText( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, itemIndex ), outText );
}

Sint32 VWPullDownMenuCtrl::GetItemMarker(size_t itemIndex) const
{
	Sint32	marker	= 0;
	if ( itemIndex < farrIndexToMarker.size() ) {
		marker	= farrIndexToMarker[ itemIndex ];
	}

	return marker;
}

void VWPullDownMenuCtrl::SetItemMarker(size_t itemIndex, Sint32 marker)
{
	if ( itemIndex < farrIndexToMarker.size() ) {
		farrIndexToMarker[ itemIndex ]	= marker;
	}
}

size_t VWPullDownMenuCtrl::GetSelectedIndex() const
{
	short	nItemIndex	= -1;
	::GS_GetSelectedChoiceIndex( gCBP, fpParentDlg->GetControlID(), fControlID, nItemIndex );
	return (size_t) nItemIndex;
}

void VWPullDownMenuCtrl::SelectIndex(size_t itemIndex)
{
	::GS_SelectChoice( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, itemIndex ) );
}

TXString VWPullDownMenuCtrl::GetSelectedItem() const
{
	TXString result;
	size_t	selIndex	= this->GetSelectedIndex();
	if ( selIndex != size_t(-1) )
	{
		this->GetItemText( selIndex, result );
	}

	return result;
}

void VWPullDownMenuCtrl::SelectItem(const TXString& item)
{
	size_t	selIndex	= this->GetItemIndex( item );
	this->SelectIndex( selIndex );
}

Sint32 VWPullDownMenuCtrl::GetSelectedItemMarker() const
{
	size_t	selIndex	= this->GetSelectedIndex();
	return this->GetItemMarker( selIndex );
}

bool VWPullDownMenuCtrl::SelectItemWithMarker(Sint32 marker)
{
	bool		bOk			= false;
	size_t		markersCnt	= farrIndexToMarker.size();
	for(size_t i=0; i<markersCnt; i++) {
		const Sint32&		thisMarker	= farrIndexToMarker[ i ];
		if ( thisMarker == marker ) {
			this->SelectIndex( i );
			bOk			= true;
			// STOP! pull downs can only have one selectoin
			break;
		}
	}

	return bOk;
}

void VWPullDownMenuCtrl::EnableNotifyPullDown()
{
	::GS_NotifyPullDownClicked( gCBP, fpParentDlg->GetControlID(), fControlID );
}

// Set the indicated item as enabled or disabled, which should cause it to be greyed and not selectable.
void VWPullDownMenuCtrl::SetItemEnabled(size_t itemIndex, bool enabled)
{
	gSDK->SetListItemEnabled(fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kTArdoin, itemIndex ), enabled);
}

void VWPullDownMenuCtrl::AddItemEnhanced(const TXString& itemText, const TXString& itemResourceSpecifier, Sint32 marker)
{
	size_t	insertAt	= this->GetItemsCount();

	gSDK->InsertEnhancedPullDownMenuItem( fpParentDlg->GetControlID(), fControlID, itemText, itemResourceSpecifier );

	// set marker for this item
	if ( insertAt >= farrIndexToMarker.size() ) {
		// make sure we have enough space for the marker of this element
		farrIndexToMarker.resize( insertAt + 1 );
	}

	farrIndexToMarker[ insertAt ]	= marker;
}

void VWPullDownMenuCtrl::RemoveItemEnhanceds()
{
	size_t count = this->GetItemsCount();
	if ( count > 0 )
	{
		gSDK->RemoveEnhancedPullDownMenuItemRange( fpParentDlg->GetControlID(), fControlID, 0, DemoteTo<Sint32>(kVStanev,count-1) );
	}
}

bool VWPullDownMenuCtrl::RemoveItemEnhanced(size_t startIndex, size_t endIndex)
{
	if ( endIndex == size_t(-1) )
		endIndex = startIndex + 1;
	return gSDK->RemoveEnhancedPullDownMenuItemRange( fpParentDlg->GetControlID(), fControlID, DemoteTo<Sint32>(kVStanev,startIndex), DemoteTo<Sint32>(kVStanev,endIndex) ) ? true : false;
}

bool VWPullDownMenuCtrl::ShowEnhancedGroupIcon(bool showGroupIcon)
{
	return gSDK->ShowEnhancedPullDownMenuGroupIcon( fpParentDlg->GetControlID(), fControlID, showGroupIcon ) ? true : false;
}

void VWPullDownMenuCtrl::PullDownResourceLayoutInit(VectorWorks::Extension::IResourceManagerContent* content)
{
	gSDK->PullDownResourceLayoutInit( fpParentDlg->GetDialogID(), fControlID, content );
}

void VWPullDownMenuCtrl::PullDownResourceLayoutSetSelectedResourceName(const TXString & name)
{
	gSDK->PullDownResourceLayoutSetSelectedResourceName( fpParentDlg->GetDialogID(), fControlID, name );
}

TXString VWPullDownMenuCtrl::PullDownResourceLayoutGetSelectedResourceName() const
{
	return gSDK->PullDownResourceLayoutGetSelectedResourceName( fpParentDlg->GetDialogID(), fControlID );
}
