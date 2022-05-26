//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ListBrowserCtrl.h"
#include "VWFC/VWUI/ListBrowserColumn.h"
#include "VWFC/VWUI/ListBrowserItem.h"

#include "VWFC/VWUI/Dialog.h"

using namespace VWFC::VWUI;

VWListBrowserCtrl::VWListBrowserCtrl(TControlID id)
	: VWControl( id )
	, fIsHierarchical( false )
{
}

VWListBrowserCtrl::~VWListBrowserCtrl()
{
}

bool VWListBrowserCtrl::CreateControl(VWDialog* pDlg, short widthInStdChar, short heightInLines)
{
	fIsHierarchical	= false;

	::GS_CreateListBrowser( gCBP, pDlg->GetControlID(), fControlID, widthInStdChar, heightInLines );
	return VWControl::CreateControl( pDlg );
}

void VWListBrowserCtrl::EnableControl(bool enable)
{
	VERIFYN( kVStanev, ::GS_EnableListBrowser( gCBP, fpParentDlg->GetControlID(), fControlID, enable ) );
}

void VWListBrowserCtrl::EnableClickAllDataChange(bool enable)
{
	VERIFYN( kVStanev, ::GS_EnableListBrowserClickAllDataChange( gCBP, fpParentDlg->GetControlID(), fControlID, enable ) );
}

void VWListBrowserCtrl::EnableDragAndDrop(bool enable)
{
	VERIFYN( kVStanev, ::GS_EnableListBrowserDragAndDrop( gCBP, fpParentDlg->GetControlID(), fControlID, enable) );
}

void VWListBrowserCtrl::EnableRadioToolTips()
{
	gSDK->ShowListBrowserRadioToolTips( fpParentDlg->GetControlID(), fControlID );
}

void VWListBrowserCtrl::SetFocusOnControl()
{
	VERIFYN( kVStanev, ::GS_SetFocusOnListBrowser( gCBP, fpParentDlg->GetControlID(), fControlID ) );
}

void VWListBrowserCtrl::RefreshControl()
{
	VERIFYN( kVStanev, ::GS_RefreshListBrowser( gCBP, fpParentDlg->GetControlID(), fControlID ) );
}

bool VWListBrowserCtrl::IsSortingEnabled() const
{
	return ::GS_IsListBrowserSortingEnabled( gCBP, fpParentDlg->GetControlID(), fControlID ) ? true : false;
}

void VWListBrowserCtrl::EnableDirectEdit(bool enable)
{
	gSDK->SetListBrowserReadOnly( fpParentDlg->GetControlID(), fControlID, !enable );
}

bool VWListBrowserCtrl::IsDirectEditEnabled()
{
	return !gSDK->IsListBrowserReadOnly( fpParentDlg->GetControlID(), fControlID );
}

void VWListBrowserCtrl::EnableSorting(bool enable)
{
	::GS_EnableListBrowserSorting( gCBP, fpParentDlg->GetControlID(), fControlID, enable );
}

size_t VWListBrowserCtrl::GetSelectedItemsCount()
{
	return (size_t) ::GS_GetNumSelectedListBrowserItems( gCBP, fpParentDlg->GetControlID(), fControlID ); 
}

void VWListBrowserCtrl::EnableSingleLineSelection(bool enable)
{
	VERIFYN( kVStanev, ::GS_EnableListBrowserSingleLineSelection( gCBP, fpParentDlg->GetControlID(), fControlID, enable ) );
}

void VWListBrowserCtrl::EnableUpdates(bool enable)
{
	VERIFYN( kVStanev, ::GS_EnableListBrowserUpdates( gCBP, fpParentDlg->GetControlID(), fControlID, enable ) );
}

void VWListBrowserCtrl::SelectRow(size_t rowIndex, bool select) const
{
	this->SelectRow( rowIndex, rowIndex, select );
}

void VWListBrowserCtrl::SelectRow(size_t firstRowIndex, size_t lastRowIndex, bool select) const
{
	VERIFYN( kVStanev, ::GS_SetListBrowserSelection( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short> ( kVStanev, firstRowIndex ), DemoteTo<short> ( kVStanev, lastRowIndex ), select ) );
}

void VWListBrowserCtrl::DeselectAll() const
{
	size_t	rowIndex	= this->GetFirstSelected();
	if ( rowIndex != size_t(-1) ) {
		do
		{
			this->SelectRow( rowIndex, rowIndex, false );
		} while( this->GetNextSelected( rowIndex ) );
	}
}

Sint32 VWListBrowserCtrl::GetRowData(size_t rowIndex) const
{
	Sint32 data = 0;
	gSDK->GetListBrowserItemData( fpParentDlg->GetControlID(), fControlID, DemoteTo<int>(kVStanev, rowIndex), 0, data );
	return data;
}

void VWListBrowserCtrl::SetRowData(size_t rowIndex, Sint32 data)
{
	gSDK->SetListBrowserItemData( fpParentDlg->GetControlID(), fControlID, DemoteTo<int>(kVStanev, rowIndex), 0, data );
}

Sint32 VWListBrowserCtrl::GetRowMarker(size_t rowIndex) const
{
	// the markers work only for non-hierarchical lists
	ASSERTN( kVStanev, fIsHierarchical == false );

	Sint32	marker	= 0;
	if ( rowIndex < farrIndexToMarker.size() ) {
		marker	= farrIndexToMarker[ rowIndex ];
	}

	return marker;
}

void VWListBrowserCtrl::SetRowMarker(size_t rowIndex, Sint32 marker)
{
	// the markers work only for non-hierarchical lists
	ASSERTN( kVStanev, fIsHierarchical == false );

	size_t markerSize = farrIndexToMarker.size();
	if ( rowIndex >= markerSize )
	{
		farrIndexToMarker.resize( rowIndex+1 );
		markerSize = farrIndexToMarker.size();
	}

	if ( rowIndex < markerSize ) {
		farrIndexToMarker[ rowIndex ]	= marker;
	}
}

size_t VWListBrowserCtrl::GetRowWithMarker(Sint32 marker)
{
	// the markers work only for non-hierarchical lists
	ASSERTN( kVStanev, fIsHierarchical == false );

	size_t	rowIndex	= size_t(-1);

	size_t	cnt			= farrIndexToMarker.size();
	for(size_t i=0; i<cnt; i++) {
		const Sint32&	theMarker	= farrIndexToMarker[ i ];
		if ( theMarker == marker ) {
			rowIndex	= i;
			// FOUND ! STOP
			break;
		}
	}

	return rowIndex;
}

void VWListBrowserCtrl::SetColumnWidth(size_t fromColumn, size_t toColumn, size_t width)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserColumnWidth( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short> ( kVStanev, fromColumn ), DemoteTo<short> ( kVStanev, toColumn ), DemoteTo<short> ( kVStanev, width ) ) );
}

void VWListBrowserCtrl::GetColumnWidth(size_t column, short &width)
{
	VERIFYN( kVStanev, ::GS_GetListBrowserColumnWidth( gCBP, fpParentDlg->GetControlID(), fControlID, (short)column, width ) );
}

void VWListBrowserCtrl::EnableDropOnIndices(size_t startItemIndex, size_t endItemIndex, bool enable)
{
	VERIFYN( kVStanev, ::GS_EnableListBrowserDropOnIndices( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<Sint32> ( kVStanev, startItemIndex ), DemoteTo<Sint32> ( kVStanev, endItemIndex ), enable ) );
}

void VWListBrowserCtrl::EnableHierarchicalDisplay(bool enable)
{
	gSDK->EnableListBrowserHierarchicalDisplay( fpParentDlg->GetDialogID(), fControlID, enable );
	fIsHierarchical = enable;
}

bool VWListBrowserCtrl::IsHierarchicalDisplay() const
{
	return gSDK->IsListBrowserDisplayHierarchical( fpParentDlg->GetDialogID(), fControlID ) ? true : false;
}

TXString VWListBrowserCtrl::GetHierarchicalRowContainerPath(size_t rowIndex)
{
	Sint32 demotedRowIndex = DemoteTo<Sint32> ( kNZhelyazkov, rowIndex );
	return gSDK->GetHierarchicalListBrowserRowContainerPath( fpParentDlg->GetDialogID(), fControlID, demotedRowIndex );
}

size_t VWListBrowserCtrl::GetFirstSelected() const
{
	size_t	row		= 0;
	bool	ok		= this->GetNextRowSelected( row );
	if ( ! ok )
		row		= (size_t) -1;
	return row;
}

size_t VWListBrowserCtrl::GetLastSelected() const
{
	size_t	result		= size_t(-1);
	size_t	itemsCnt	= this->GetRowsCount();
	if ( itemsCnt > 0 )
	{
		size_t	row		= itemsCnt - 1;
		bool	ok		= this->GetPrevRowSelected( row );
		if ( ok )
			result	= row;
	}

	return result;
}

bool VWListBrowserCtrl::GetNextSelected(size_t& row) const
{
	row++;
	return this->GetNextRowSelected( row );
}

bool VWListBrowserCtrl::GetPrevSelected(size_t& row) const
{
	return row != size_t(-1) ? this->GetPrevRowSelected( row ) : false;
}

bool VWListBrowserCtrl::GetNextRowSelected(size_t& row) const
{
	size_t	itemsCnt = this->GetRowsCount();
	while ( row < itemsCnt && ! this->IsRowSelected( row ) ) {
		row++;
	}
	return row < itemsCnt;
}

bool VWListBrowserCtrl::GetPrevRowSelected(size_t& row) const
{
	while ( row != size_t(-1) && ! this->IsRowSelected( row ) ) {
		row--;
	}

	return row != size_t(-1);
}

void VWListBrowserCtrl::EnableExternalSort(bool bEnable/* = true*/)
{
	gSDK->EnableListBrowserExternalSort(fpParentDlg->GetControlID(), fControlID, bEnable);
}

bool VWListBrowserCtrl::IsExternalSortEnabled() const
{
	return gSDK->IsListBrowserExternalSortEnabled(fpParentDlg->GetControlID(), fControlID);
}

// ------------------------------------------------------------------------
// columns
VWListBrowserColumn VWListBrowserCtrl::GetColumn(size_t columnIndex)
{
	VWListBrowserColumn column( fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, columnIndex ) );
	return column;
}

VWListBrowserColumn	VWListBrowserCtrl::AddColumn(const TXString& text, const TXString& savedSettingsColumnName, size_t defaultWidth)
{
	short	columnIndex	= ::GS_GetNumListBrowserColumns( gCBP, fpParentDlg->GetControlID(), fControlID );

	size_t	width		= defaultWidth;
	if ( VERIFYN( kVStanev, fpParentDlg && savedSettingsColumnName.IsEmpty() == false ) )
	{
		fpParentDlg->RegisterListBrowserColumn( fControlID, columnIndex, savedSettingsColumnName );

		TXString		value;
		if ( fpParentDlg->GetSavedValue( savedSettingsColumnName, value ) )
		{
			Sint32 theValue = value.atoi();
			if ( theValue > 10 && theValue < 1000 )
			{
				// built-in limit to something sensible
				width = size_t(theValue);
			}
		}
	}

	::GS_InsertListBrowserColumn( gCBP, fpParentDlg->GetControlID(), fControlID, columnIndex, text, DemoteTo<short>( kVStanev, width ) );
	return this->GetColumn( columnIndex );
}

VWListBrowserColumn VWListBrowserCtrl::AddColumn(const TXString& text, size_t width)
{
	short	columnIndex	= ::GS_GetNumListBrowserColumns( gCBP, fpParentDlg->GetControlID(), fControlID );
	::GS_InsertListBrowserColumn( gCBP, fpParentDlg->GetControlID(), fControlID, columnIndex, text, DemoteTo<short>( kVStanev, width ) );
	return this->GetColumn( columnIndex );
}

VWListBrowserColumn	VWListBrowserCtrl::InsertColumn(size_t columnIndex, const TXString& text, const TXString& savedSettingsColumnName, size_t defaultWidth)
{
	size_t	width		= defaultWidth;
	if ( VERIFYN( kVStanev, fpParentDlg && savedSettingsColumnName.IsEmpty() == false ) )
	{
		fpParentDlg->RegisterListBrowserColumn( fControlID, columnIndex, savedSettingsColumnName );

		TXString		value;
		if ( fpParentDlg->GetSavedValue( savedSettingsColumnName, value ) )
		{
			Sint32 theValue = value.atoi();
			if ( theValue > 10 && theValue < 1000 )
			{
				// built-in limit to something sensible
				width = size_t(theValue);
			}
		}
	}

	::GS_InsertListBrowserColumn( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, columnIndex ), text, DemoteTo<short>( kVStanev, width ) );
	return this->GetColumn( columnIndex );
}

VWListBrowserColumn VWListBrowserCtrl::InsertColumn(size_t columnIndex, const TXString& text, size_t width)
{
	::GS_InsertListBrowserColumn( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, columnIndex ), text, DemoteTo<short>( kVStanev, width ) );
	return this->GetColumn( columnIndex );
}

void VWListBrowserCtrl::DeleteColumn(size_t columnIndex)
{
	VERIFYN( kVStanev, ::GS_DeleteListBrowserColumn( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, columnIndex ) ) );
}

size_t VWListBrowserCtrl::GetColumnsCount() const
{
	return (size_t) ::GS_GetNumListBrowserColumns( gCBP, fpParentDlg->GetControlID(), fControlID );
}

void VWListBrowserCtrl::EnableColumnLines(bool enable)
{
	::GS_EnableListBrowserColumnLines( gCBP, fpParentDlg->GetControlID(), fControlID, enable );
}

bool VWListBrowserCtrl::AreColumnLinesEnabled() const
{
	return ::GS_AreListBrowserColumnLinesEnabled( gCBP, fpParentDlg->GetControlID(), fControlID ) ? true : false;
}

// ------------------------------------------------------------------------
// items
VWListBrowserItem VWListBrowserCtrl::GetItem(size_t rowIndex, size_t columnIndex)
{
	// assert that we have such column
	ASSERTN( kVStanev, columnIndex < (size_t) ::GS_GetNumListBrowserColumns( gCBP, fpParentDlg->GetControlID(), fControlID ) );

	TXString	strEmpty;
	size_t		rowsCnt		= ::GS_GetNumListBrowserItems( gCBP, fpParentDlg->GetControlID(), fControlID );
	if ( rowsCnt != (size_t) -1 ) {
		for(size_t i=rowsCnt; i<=rowIndex; i++) {
			size_t	newRowIndex	= ::GS_InsertListBrowserItem( gCBP, fpParentDlg->GetControlID(), fControlID, (short)i, strEmpty );

			if ( fIsHierarchical == false )
			{
				// set marker for this item
				if ( newRowIndex >= farrIndexToMarker.size() ) {
					// make sure we have enough space for the marker of this element
					farrIndexToMarker.resize( newRowIndex + 1 );
				}
			}
		}
	}

	VWListBrowserItem item ( fpParentDlg->GetControlID(), fControlID, DemoteTo<short>( kVStanev, columnIndex ), DemoteTo<short>( kVStanev, rowIndex ) );
	return item;
}

// ------------------------------------------------------------------------
// rows
bool VWListBrowserCtrl::IsRowSelected(size_t rowIndex) const
{
	return ::GS_IsListBrowserItemSelected( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short> ( kVStanev, rowIndex ) ) ? true : false;
}

size_t VWListBrowserCtrl::AddRow(const TXString& text, Sint32 marker /*=0*/)
{
	short	rowIndex	= ::GS_GetNumListBrowserItems( gCBP, fpParentDlg->GetControlID(), fControlID );
	
	if ( fIsHierarchical == false )
	{
		// set marker for this item
		if ( rowIndex >= 0 && size_t(rowIndex) >= farrIndexToMarker.size() ) {
			// make sure we have enough space for the marker of this element
			farrIndexToMarker.resize( rowIndex + 1 );
		}
		
		farrIndexToMarker[ rowIndex ]	= marker;
	}

	return ::GS_InsertListBrowserItem( gCBP, fpParentDlg->GetControlID(), fControlID, rowIndex, text );
}

size_t VWListBrowserCtrl::InsertRow(size_t rowIndex, const TXString& text, Sint32 marker /*=0*/)
{
	size_t	newRowIndex	= ::GS_InsertListBrowserItem( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short> ( kVStanev, rowIndex ), text );

	if ( fIsHierarchical == false )
	{
		// set marker for this item
		if ( newRowIndex >= farrIndexToMarker.size() ) {
			// make sure we have enough space for the marker of this element
			farrIndexToMarker.resize( newRowIndex + 1 );
		}
	
		farrIndexToMarker[ newRowIndex ]	= marker;
	}
	
	return newRowIndex;
}

void VWListBrowserCtrl::DeleteRow(size_t rowIndex)
{
	DSTOPIF( rowIndex >= this->GetRowsCount(), (kVStanev, "Deleting row = %d that doesn't exist in VWListBrowserCtrl", rowIndex) );

	if ( fIsHierarchical == false )
	{
		ASSERTN( kVStanev, rowIndex < farrIndexToMarker.size() );
		if ( rowIndex < farrIndexToMarker.size() ) {
			farrIndexToMarker.erase( farrIndexToMarker.begin() + rowIndex );
		}
	}

	VERIFYN( kVStanev, ::GS_DeleteListBrowserItem( gCBP, fpParentDlg->GetControlID(), fControlID, DemoteTo<short> ( kVStanev, rowIndex ) ) );
}

void VWListBrowserCtrl::DeleteAllRows()
{
	farrIndexToMarker.clear();
	VERIFYN( kVStanev, ::GS_DeleteAllListBrowserItems( gCBP, fpParentDlg->GetControlID(), fControlID ) );
}

size_t VWListBrowserCtrl::GetRowsCount() const
{
	size_t	cntCount	= ::GS_GetNumListBrowserItems( gCBP, fpParentDlg->GetControlID(), fControlID );
	if ( cntCount == (size_t) -1 )
		cntCount	= 0;
	return cntCount;
}

bool VWListBrowserCtrl::GetSelectedItemIndices(TSizeTArray& outArray) const
{
	outArray.clear();

	size_t	loopSelRow	= this->GetFirstSelected();
	if ( loopSelRow != size_t(-1) ) {
		do {
			outArray.push_back( loopSelRow );
		} while ( this->GetNextSelected( loopSelRow ) );
	}

	return outArray.size() > 0;
}

void VWListBrowserCtrl::SetSelectedItemIndices(const TSizeTArray& arr, bool selected)
{
	for(size_t i=0, cnt=arr.size(); i<cnt; i++)
	{
		this->SelectRow( arr[ i ], selected );
	}
}

// ------------------------------------------------------------------------
// images support
size_t VWListBrowserCtrl::AddImage(size_t resourceID, size_t resourceIDSelected /*=0*/)
{
	return (size_t) ::GS_AddListBrowserImage( gCBP, fpParentDlg->GetControlID(), fControlID, kResourceSmallIcon, DemoteTo<short> ( kVStanev, resourceID ), DemoteTo<short> ( kVStanev, resourceIDSelected ) );
}

// ------------------------------------------------------------------------

size_t	VWListBrowserCtrl::AddImage(const TXString& imageSpecifier, const TXString& selectedImageSpecifier)
{
#ifdef _WINDOWS
	if ( selectedImageSpecifier.IsEmpty() )
		return (size_t) gSDK->AddListBrowserImage(fpParentDlg->GetControlID(), fControlID, imageSpecifier, imageSpecifier);
	else
		return (size_t) gSDK->AddListBrowserImage(fpParentDlg->GetControlID(), fControlID, imageSpecifier, selectedImageSpecifier);
#else
    // The mac (as of VW2016) doesn't support selected image specifier
	return (size_t) gSDK->AddListBrowserImage(fpParentDlg->GetControlID(), fControlID, imageSpecifier);
#endif
}


// ------------------------------------------------------------------------

static const char* GetStandardImageSpecifier(EStandardImageID imageID)
{
	const char* imageSpecifier = "";

	switch(imageID) {
		case kStandardImageID_None:
			break;
		case kStandardImageID_Blank:
			imageSpecifier = "Vectorworks/Standard Images/Blank.png";
			break;
		case kStandardImageID_DiamondBlack:
			imageSpecifier = "Vectorworks/Standard Images/Visible.png";
			break;
		case kStandardImageID_DiamondHollow:
			imageSpecifier = "Vectorworks/Standard Images/Invisible.png";
			break;
		case kStandardImageID_DiamondGray:
			imageSpecifier = "Vectorworks/Standard Images/Gray.png";
			break;
		case kStandardImageID_RedCrossedCircle:
			imageSpecifier = "Vectorworks/Standard Images/DontSave.png";
			break;
		case kStandardImageID_CheckMark:
			imageSpecifier = "Vectorworks/Standard Images/Checkmark.png";
			break;
		case kStandardImageID_CheckMarkWhite:
			imageSpecifier = "Vectorworks/Standard Images/WhiteCheckmark.png";
			break;
		case kStandardImageID_LeftBlackArrow:
			break;
		case kStandardImageID_RightBlackArrow:
			break;
		case kStandardImageID_LeftHollowArrow:
			break;
		case kStandardImageID_RightHollowArraw:
			break;
		case kStandardImageID_LeftThinArrow:
			break;
		case kStandardImageID_RightThinkArrow:
			break;
		case kStandardImageID_BallBlack:
			break;
		case kStandardImageID_BallHollow:
			break;
		case kStandardImageID_Slash:
			break;
		case kStandardImageID_XMark:
			break;
		default:
			break;
	}
	return imageSpecifier;
}

size_t VWListBrowserCtrl::AddImageStandard(EStandardImageID image, EStandardImageID selImage)
{
	const char* imageSpecifier = GetStandardImageSpecifier(image);
	const char* selectedImageSpecifier = GetStandardImageSpecifier(selImage);
    
	return this->AddImage(imageSpecifier, selectedImageSpecifier);
}

void VWListBrowserCtrl::ExpandAllItems()
{
	gSDK->ExpandAllListBrowserItems( fpParentDlg->GetControlID(), fControlID );
}

bool VWListBrowserCtrl::IsRowClosed(size_t rowIndex)
{
	return gSDK->HierarchicalListBrowserItemIsClosed( fpParentDlg->GetDialogID(), fControlID,  DemoteTo<short>(kSasha, rowIndex) ) ? true : false;
}

void VWListBrowserCtrl::ExpandItems(size_t rowIndex, bool recursive, size_t& outRedisplayedItemsCnt)
{
	// the markers work only for hierarchical lists
	ASSERTN( kVStanev, fIsHierarchical );

	short	cntRedisplayedItems	= 0;
	gSDK->HierarchicalListBrowserItemOpened( fpParentDlg->GetDialogID(), fControlID, DemoteTo<short>(kSasha, rowIndex), recursive, cntRedisplayedItems );

	outRedisplayedItemsCnt	= cntRedisplayedItems;
}

void VWListBrowserCtrl::CloseItems(size_t rowIndex, bool recursive, size_t& outClosedItemsCnt)
{
	// the markers work only for hierarchical lists
	ASSERTN( kVStanev, fIsHierarchical );

	short cntDisplayedItems = 0;
	gSDK->GetDisplayedItemsCountInHierarchicalContainer( fpParentDlg->GetDialogID(), fControlID, DemoteTo<short>(kSasha, rowIndex), cntDisplayedItems );
	gSDK->HierarchicalListBrowserItemClosed( fpParentDlg->GetDialogID(), fControlID, DemoteTo<short>(kSasha, rowIndex), recursive );

	outClosedItemsCnt = cntDisplayedItems;
}

bool VWListBrowserCtrl::IsItemContainer(size_t rowIndex)
{
	return gSDK->HierarchicalListBrowserItemIsContainer( fpParentDlg->GetDialogID(), fControlID, DemoteTo<short>(kSasha, rowIndex) );
}

void VWListBrowserCtrl::CloseAllItems()
{
	// the markers work only for hierarchical lists
	ASSERTN( kVStanev, fIsHierarchical );

	gSDK->CollapseAllListBrowserItems( fpParentDlg->GetDialogID(), fControlID );
}

TXString VWListBrowserCtrl::GetItemOriginalName(size_t rowIndex, bool returnContainerName)
{
	TXString result = gSDK->GetListBrowserItemOriginalName( fpParentDlg->GetDialogID(), fControlID, DemoteTo<short>(kSasha, rowIndex) );
	if ( returnContainerName && result.IsEmpty() )
	{
		short hierarchicalCol = gSDK->GetListBrowserHierarchicalDisplayColumn( fpParentDlg->GetDialogID(), fControlID );
		if ( hierarchicalCol >= 0 )
		{
			short imageIndex;
			gSDK->GetListBrowserItemInfo( fpParentDlg->GetDialogID(), fControlID, DemoteTo<short>(kSasha, rowIndex), hierarchicalCol, result, imageIndex );
		}
	}

	return result;
}
