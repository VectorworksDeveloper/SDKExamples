//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ListBrowserColumn.h"

using namespace VWFC::VWUI;

VWListBrowserColumn::VWListBrowserColumn(TControlID dialogID, TControlID controlID, short columnID)
{
	fDialogID	= dialogID;
	fControlID	= controlID;
	fColumnID	= columnID;
}

VWListBrowserColumn::VWListBrowserColumn(const VWListBrowserColumn& column)
{
	fDialogID	= column.fDialogID;
	fControlID	= column.fControlID;
	fColumnID	= column.fColumnID;
}

VWListBrowserColumn::~VWListBrowserColumn()
{
}

VWListBrowserColumn& VWListBrowserColumn::operator=(const VWListBrowserColumn& column)
{
	fDialogID	= column.fDialogID;
	fControlID	= column.fControlID;
	fColumnID	= column.fColumnID;
	return *this;
}

size_t VWListBrowserColumn::GetColumnIndex() const
{
	return fColumnID;
}

size_t VWListBrowserColumn::GetColumnWidth() const
{
	short width = 0;
	VERIFYN( kVStanev, ::GS_GetListBrowserColumnWidth( gCBP, fDialogID, fControlID, fColumnID, width ) );
	return (size_t) width;
}

size_t VWListBrowserColumn::GetColumnDataItemsCount() const
{
	return (size_t) ::GS_GetNumListBrowserColumnDataItems( gCBP, fDialogID, fControlID, fColumnID );
}

void VWListBrowserColumn::SetColumnType(EListBrowserControlType columnType)
{
	if ( columnType != kListBrowserControlNone ) {
		VERIFYN( kVStanev, ::GS_SetListBrowserControlType( gCBP, fDialogID, fControlID, fColumnID, DemoteTo<short>( kVStanev, columnType ) ) );
	}
}

EListBrowserControlType VWListBrowserColumn::GetColumnType() const
{
	return (EListBrowserControlType) ::GS_GetListBrowserControlType( gCBP, fDialogID, fControlID, fColumnID );
}

void VWListBrowserColumn::SetAsDragAndDropColumn()
{
	VERIFYN( kVStanev, ::GS_SetListBrowserDragAndDropColumn( gCBP, fDialogID, fControlID, fColumnID ) );
}

void VWListBrowserColumn::SetAsHierarchicalDisplayColumn()
{
	gSDK->SetListBrowserHierarchicalDisplayColumn( fDialogID, fControlID, fColumnID );
}

void VWListBrowserColumn::SetSortColumn(bool enable)
{
	::GS_SetListBrowserSortColumn( gCBP, fDialogID, fControlID, fColumnID, enable );
}

size_t VWListBrowserColumn::GetSortColumn() const
{
	return (size_t) ::GS_GetListBrowserSortColumn( gCBP, fDialogID, fControlID); 
}

EColumnSortState VWListBrowserColumn::GetColumnSortState() const
{
	return (EColumnSortState) ::GS_GetListBrowserColumnSortState( gCBP, fDialogID, fControlID, fColumnID );
}

bool VWListBrowserColumn::SetColumnSortState(EColumnSortState state)
{
	if ( state != kNoSortState )
	{
		gSDK->SetListBrowserSortColumn( fDialogID, fControlID, fColumnID, state == kAscendingSortState );
	}
	return state != kNoSortState;
}

void VWListBrowserColumn::SetColumnHeaderImage(size_t imageIndex)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserColumnImage( gCBP, fDialogID, fControlID, fColumnID, DemoteTo<Sint32> ( kVStanev, imageIndex ) ) );
}

void VWListBrowserColumn::SetColumnHeaderJust(EColumnHeaderJustification justification)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserColumnHeaderJust( gCBP, fDialogID, fControlID, fColumnID, DemoteTo<Sint32> ( kVStanev, justification ) ) );
}

EColumnHeaderJustification VWListBrowserColumn::GetColumnHeaderJust() const
{
	Sint32 justification;
	VERIFYN( kVStanev, ::GS_GetListBrowserColumnHeaderJust( gCBP, fDialogID, fControlID, fColumnID, justification ) );
	return (EColumnHeaderJustification) justification;
}

void VWListBrowserColumn::SetColumnHeaderToolTip(const TXString& primaryText, const TXString& subText)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserColumnHeaderToolTip( gCBP, fDialogID, fControlID, fColumnID, primaryText, subText ) );
}

bool VWListBrowserColumn::GetColumnHeaderToolTip(TXString& outPrimaryText, TXString& outSubText) const
{
	TXString	primaryText;
	TXString	subText;

	bool	ok	= ::GS_GetListBrowserColumnHeaderToolTip( gCBP, fDialogID, fControlID, fColumnID, primaryText, subText ) ? true : false;

	if ( ok ) {
		outPrimaryText	= primaryText;
		outSubText		= subText;
	}
	else {
		outPrimaryText.Clear();
		outSubText.Clear();
	}

	return ok;
}

void VWListBrowserColumn::SetEditDisplayType(EListBrowserDisplayType displayType)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserEditDisplayType( gCBP, fDialogID, fControlID, fColumnID, DemoteTo<short> ( kVStanev, displayType ) ) );
}

EListBrowserDisplayType VWListBrowserColumn::GetEditDisplayType() const
{
	return (EListBrowserDisplayType) ::GS_GetListBrowserEditDisplayType( gCBP, fDialogID, fControlID, fColumnID );
}

void VWListBrowserColumn::SetItemDisplayType(EListBrowserDisplayType displayType)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemDisplayType( gCBP, fDialogID, fControlID, fColumnID, DemoteTo<short> ( kVStanev, displayType ) ) );
}

EListBrowserDisplayType VWListBrowserColumn::GetItemDisplayType() const
{
	return (EListBrowserDisplayType) ::GS_GetListBrowserItemDisplayType( gCBP, fDialogID, fControlID, fColumnID );
}

bool VWListBrowserColumn::AreRadioColumnLinesEnabled() const
{
	return ::GS_AreListBrowserRadioColumnLinesEnabled( gCBP, fDialogID, fControlID, fColumnID ) ? true : false;
}

bool VWListBrowserColumn::IsTrackingEnabled() const
{
	return ::GS_IsListBrowserColumnTrackingEnabled( gCBP, fDialogID, fControlID, fColumnID ) ? true : false;
}

void VWListBrowserColumn::EnableColumnTracking(bool enable) const
{
	::GS_EnableListBrowserColumnTracking( gCBP, fDialogID, fControlID, fColumnID, enable );
}

void VWListBrowserColumn::EnableRadioColumnLines(bool enable) const
{
	::GS_EnableListBrowserRadioColumnLines( gCBP, fDialogID, fControlID, fColumnID, enable );
}

size_t VWListBrowserColumn::FindColumnDataItem(const TXString& text) const
{
	short columnDataItemIndex;
	bool ok = ::GS_FindListBrowserColumnDataItem( gCBP, fDialogID, fControlID, fColumnID, text, columnDataItemIndex);
	return ok ? (size_t) columnDataItemIndex : (size_t) -1;
}

size_t VWListBrowserColumn::FindColumnItem(const TXString& text) const
{
	short itemIndex;
	bool ok = ::GS_FindListBrowserColumnItem( gCBP, fDialogID, fControlID, fColumnID, text, itemIndex );
	return ok ? (size_t) itemIndex : (size_t) -1;
}

size_t VWListBrowserColumn::InsertColumnChoice(const TXString& text)
{
	return (size_t) ::GS_InsertListBrowserColumnDataItem( gCBP, fDialogID, fControlID, fColumnID, text, -1, -1, -1 );
}

size_t VWListBrowserColumn::InsertColumnChoice(const TXString& text, size_t imageOn)
{
	return (size_t) ::GS_InsertListBrowserColumnDataItem( gCBP, fDialogID, fControlID, fColumnID, text, DemoteTo<short> ( kVStanev, imageOn ), -1, -1 );
}

size_t VWListBrowserColumn::InsertColumnChoice(const TXString& text, size_t imageOn, size_t imageOff)
{
	return (size_t) ::GS_InsertListBrowserColumnDataItem( gCBP, fDialogID, fControlID, fColumnID, text, DemoteTo<short> ( kVStanev, imageOn ), DemoteTo<short> ( kVStanev, imageOff ), -1 );
}

size_t VWListBrowserColumn::InsertColumnChoice(const TXString& text, size_t imageOn, size_t imageOff, size_t itemData)
{
	return (size_t) ::GS_InsertListBrowserColumnDataItem( gCBP, fDialogID, fControlID, fColumnID, text, DemoteTo<short> ( kVStanev, imageOn ), DemoteTo<short> ( kVStanev, imageOff ), DemoteTo<short> ( kVStanev, itemData ) );
}

bool VWListBrowserColumn::RemoveColumnChoice(size_t choiceIndex)
{
	return ::GS_RemoveListBrowserColumnDataItem( gCBP, fDialogID, fControlID, fColumnID, DemoteTo<short> ( kVStanev, choiceIndex ) ) ? true : false;
}

void VWListBrowserColumn::RemoveAllColumnChoices()
{
	::GS_RemoveAllListBrowserColumnDataItems( gCBP, fDialogID, fControlID, fColumnID );
}
