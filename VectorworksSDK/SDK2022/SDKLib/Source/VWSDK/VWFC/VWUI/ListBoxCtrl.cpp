//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ListBoxCtrl.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWListBoxCtrl::VWListBoxCtrl(TControlID id)
: VWControl( id )
{
}

VWListBoxCtrl::~VWListBoxCtrl()
{
}

bool VWListBoxCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar, short heightInLines/*=1*/)
{
	farrIndexToMarker.clear();
	::GS_CreateListBox( gCBP, pDlg->GetControlID(), fControlID, widthInStdChar, heightInLines );
	return VWControl::CreateControl( pDlg );
}

void VWListBoxCtrl::Clear()
{
	::GS_DeleteAllItems( gCBP, fpParentDlg->GetControlID(), fControlID );
	farrIndexToMarker.clear();
}

void VWListBoxCtrl::AddItem(const TXString& itemText, size_t insertAt /* = (size_t)-1*/, Sint32 marker /* = 0*/)
{
	if ( insertAt == (size_t) -1 )
		insertAt		= this->GetItemsCount();

	::GS_AddChoice( gCBP, fpParentDlg->GetControlID(), fControlID, itemText, DemoteTo<short>( kVStanev, insertAt ) );

	farrIndexToMarker.insert( farrIndexToMarker.begin() + insertAt, marker );
}

void VWListBoxCtrl::Erase(size_t itemIndex)
{
	DSTOPIF( itemIndex >= this->GetItemsCount(), (kVStanev, "Deleting item = %d that doesn't exist in VWListBoxCtrl", itemIndex) );

	ASSERTN( kVStanev, itemIndex < farrIndexToMarker.size() );
	if ( itemIndex < farrIndexToMarker.size() ) {
		farrIndexToMarker.erase( farrIndexToMarker.begin() + itemIndex );
	}
	::GS_RemoveChoice( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, itemIndex ) );
}

size_t VWListBoxCtrl::GetItemsCount() const
{
	short	numItems	= 0;
	::GS_GetChoiceCount( gCBP, fpParentDlg->GetControlID(), fControlID, numItems );
	return (size_t) numItems;
}

size_t VWListBoxCtrl::GetItemIndex(const TXString& itemText) const
{
	short nItemIndex	= -1;
	::GS_GetChoiceIndex( gCBP, fpParentDlg->GetControlID(), fControlID, itemText, nItemIndex );
	return (size_t) nItemIndex;
}

void VWListBoxCtrl::GetItemText(size_t itemIndex, TXString& outText) const
{
	::GS_GetChoiceText( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, itemIndex ), outText );
}

void VWListBoxCtrl::SetItemText(size_t itemIndex, const TXString& text)
{
	bool	bWasSelected	= this->GetSelectedIndex() == itemIndex;
	this->Erase( itemIndex );
	this->AddItem( text, itemIndex );
	if ( bWasSelected ) {
		this->SelectIndex( itemIndex );
	}
}

Sint32 VWListBoxCtrl::GetItemMarker(size_t itemIndex) const
{
	Sint32	marker	= 0;
	if ( itemIndex < farrIndexToMarker.size() ) {
		marker	= farrIndexToMarker[ itemIndex ];
	}

	return marker;
}

void VWListBoxCtrl::SetItemMarker(size_t itemIndex, Sint32 marker)
{
	if ( itemIndex < farrIndexToMarker.size() ) {
		farrIndexToMarker[ itemIndex ]	= marker;
	}
}

size_t VWListBoxCtrl::GetSelectedIndex() const
{
	short	nItemIndex	= -1;
	::GS_GetSelectedChoiceIndex( gCBP, fpParentDlg->GetControlID(), fControlID, nItemIndex );
	return (size_t) nItemIndex;
}

void VWListBoxCtrl::SelectIndex(size_t itemIndex)
{
	::GS_SelectChoice( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, itemIndex ) );
}

Sint32 VWListBoxCtrl::GetSelectedItemMarker() const
{
	size_t	selIndex	= this->GetSelectedIndex();
	return this->GetItemMarker( selIndex );
}

bool VWListBoxCtrl::SelectItemWithMarker(Sint32 marker)
{
	bool		bOk			= false;
	size_t		markersCnt	= farrIndexToMarker.size();
	for(size_t i=0; i<markersCnt; i++) {
		const Sint32&		thisMarker	= farrIndexToMarker[ i ];
		if ( thisMarker == marker ) {
			this->SelectIndex( i );
			bOk			= true;
			// continue to allow multiple selection -- if supported
			// or it will select the last item with the same marker - which is ok with us
		}
	}

	return bOk;
}

void VWListBoxCtrl::AddTabStop(size_t size)
{
	::GS_AddListBoxTabStop( gCBP, fpParentDlg->GetControlID(), fControlID, (short) size );
}

void VWListBoxCtrl::RemoveLastTabStop()
{
	::GS_RemoveListBoxTabStop( gCBP, fpParentDlg->GetControlID(), fControlID );
}

void VWListBoxCtrl::DeselectAll()
{
	::GS_SelectChoice( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, -1 ), false );
}

size_t VWListBoxCtrl::GetSelectedItemsCount()
{
	size_t result = 0;

	for(size_t i=0; ; )
	{
		Sint16 selIndex = -1;
		gSDK->GetSelChoiceIndex( fpParentDlg->GetControlID(), fControlID, DemoteTo<short>(kVStanev, i), selIndex );
		if ( selIndex == -1 )
			break;

		result++;
		i = selIndex + 1;
	}

	return result;
}

void VWListBoxCtrl::GetSelectedItemIndices(TSizeTArray& outArray) const
{
	outArray.clear();
	for(Sint16 i=0; ;)
	{
		Sint16 selIndex = -1;
		gSDK->GetSelChoiceIndex( fpParentDlg->GetControlID(), fControlID, i, selIndex );
		if ( selIndex == -1 )
			break;

		outArray.push_back( selIndex );
		i = selIndex + 1;
	}
}

