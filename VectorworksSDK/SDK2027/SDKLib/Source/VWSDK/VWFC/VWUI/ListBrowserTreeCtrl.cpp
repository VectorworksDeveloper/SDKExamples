#include "StdHeaders.h"

#include "VWFC/VWUI/ListBrowserTreeCtrl.h"

using namespace VWFC::VWUI;
using namespace VWFC::VWUI::VWControlType;

VWListBrowserTreeCtrl::VWListBrowserTreeCtrl(const IVWListBrowserTreeSource& data, const TControlID& id, VWDialog* parentDlg)
	: VWControl( id, { eCompListBrowserControl } )
	, fDataSource( data )
{
	this->CreateControl( parentDlg );
	fDataSource.GetColumnSpecs( farrColumnSpecs );
}

VWListBrowserTreeCtrl::~VWListBrowserTreeCtrl()
{
}

void VWListBrowserTreeCtrl::OnInitializeContent(const TXString& showStr)
{
	VWListBrowserCtrl*	theList		= fpParentDlg->GetListBrowserCtrlByID( fControlID );
	theList->EnableDragAndDrop( false );
	theList->EnableSorting( false );
	theList->EnableSingleLineSelection( false );

	fImageIndexBlank				= theList->AddImageStandard( kStandardImageID_Blank );
	fImageIndexCheckmark			= theList->AddImageStandard( kStandardImageID_CheckMark );
	fImageIndexCheckmarkDisabled	= theList->AddImageStandard( kStandardImageID_CheckMarkGrayed );
	fImageIndexTreeClosed			= theList->AddImage( "Vectorworks/Images/Standard Images/Expandable1.png" );
	fImageIndexTreeOpen				= theList->AddImage( "Vectorworks/Images/Standard Images/Expanded1.png" );

	VWListBrowserColumn	checkCol	= theList->AddColumn( showStr, "ColumnShow", 40 );
	checkCol.SetColumnType( kListBrowserControlMultiState );
	checkCol.SetItemDisplayType( kListBrowserDisplayImageOnly );
	checkCol.InsertColumnChoice( "yes", fImageIndexBlank );
	checkCol.InsertColumnChoice( "no", fImageIndexCheckmark );

	VWListBrowserColumn treeCol		= theList->AddColumn( "", "ColumnTree", 40 );
	treeCol.SetColumnType( kListBrowserControlNone );
	treeCol.SetItemDisplayType( kListBrowserDisplayImageOnly );

	for ( const auto& spec : farrColumnSpecs )
		theList->AddColumn( spec.fName, spec.fID, spec.fWidth );
}

void VWListBrowserTreeCtrl::FillListBrowser()
{
	VWListBrowserCtrl*	theList		= fpParentDlg->GetListBrowserCtrlByID( fControlID );
	theList->DeleteAllRows();
	farrLBRowIndex2ListItemIndex.clear();

	size_t				itemIndex	= 0;
	for ( auto& data : farrListItems )
	{
		if ( data.fIsVisible )
		{
			size_t rowIndex	= theList->AddRow( "" );
			theList->GetItem( rowIndex, 0 ).SetItemImage( this->GetCheckImage( data ) );
			theList->GetItem( rowIndex, 1 ).SetItemImage( data.fIsGroup ? (data.fIsOpened ? fImageIndexTreeOpen : fImageIndexTreeClosed) : fImageIndexBlank );

			this->WriteColumnValues( theList, rowIndex, data.fColumnValues );

			this->ApplyRowEnabledState( theList, rowIndex, !data.fIsMandatory );

			data.fRowIndex	= rowIndex;
			farrLBRowIndex2ListItemIndex.push_back( itemIndex );
		}

		itemIndex++;
	}
}

void VWListBrowserTreeCtrl::OnTree(VWDialogEventArgs& eventArgs)
{
	size_t					rowIndex;
	size_t					colIndex;
	EListBrowserEventType	type	= eventArgs.GetListBrowserEvent( rowIndex, colIndex );
	
	if ( type != kListBrowserEventType_Unknown && this->IsRowOK( rowIndex ) )
	{
		size_t		itemIndex	= farrLBRowIndex2ListItemIndex[ rowIndex ];
		const auto&	itemData	= farrListItems[ itemIndex ];
		if ( colIndex == 0 && type == kListBrowserEventType_DataChangeClick )
		{
			VWListBrowserCtrl* theList = fpParentDlg->GetListBrowserCtrlByID( fControlID );
			TSizeTArray selItems;
			theList->GetSelectedItemIndices( selItems );

			if ( !itemData.fIsMandatory )
				this->ToggleSelection( selItems, !itemData.fIsChecked );

			this->RestoreSelectionImages( selItems );
		}
		else if ( colIndex == 1 && itemData.fIsGroup )
		{
			if ( itemData.fIsOpened )
			{
				this->CollapseItems( rowIndex, itemIndex );
			}
			else
			{
				this->ExpandItems( rowIndex, itemIndex );
			}
		}
	}
}

bool VWListBrowserTreeCtrl::IsRowOK(size_t rowIndex) const
{
	return rowIndex < farrLBRowIndex2ListItemIndex.size() ;
}

void VWListBrowserTreeCtrl::GetCheckedData(TXStringSTLArray& outArrCheckedIDs) const
{
	outArrCheckedIDs.clear();
	for ( const auto& it : farrListItems )
	{
		if ( !it.fIsGroup && it.fIsChecked )
		{
			outArrCheckedIDs.push_back( it.fID );
		}
	}
}

void VWListBrowserTreeCtrl::GetCheckedGroups(const TXStringSTLArray arrCheckedIDs, TXStringSTLArray& outArrCheckedGroups) const
{
	outArrCheckedGroups.clear();
	fDataSource.GetSpecialGroupMembership( arrCheckedIDs, outArrCheckedGroups );

	TXString	groupName;
	bool		isAdded								= true;
	for ( const auto& it : farrListItems )
	{
		if ( it.fIsGroup )
		{
			groupName	= it.fID;
			isAdded		= false;
		}
		else if ( it.fIsChecked && !isAdded )
		{
			outArrCheckedGroups.push_back( groupName );
			isAdded								= true;
		}
	}

	fDataSource.RequiresAdditionalTag( outArrCheckedGroups );
}

void VWListBrowserTreeCtrl::GetOpened(TXStringSTLArray& outArrOpenedIDs) const
{
	outArrOpenedIDs.clear();
	for ( const auto& it : farrListItems )
	{
		if ( it.fIsGroup && it.fIsOpened )
		{
			outArrOpenedIDs.push_back( it.fID );
		}
	}
}

void VWListBrowserTreeCtrl::SetAllToChecked()
{
	for ( auto& it : farrListItems )
	{
		if ( !it.fIsGroup )
		{
			it.fIsChecked = true;
		}
	}
}

void VWListBrowserTreeCtrl::BuildListItemsArray(const TXStringSTLArray& arrCheckedIDs, const TXStringSTLArray& arrOpenedIDs)
{
	farrListItems.clear();

	std::map<TXString, bool>	mapChecked;
	for ( const auto& it : arrCheckedIDs )
	{
		mapChecked.insert( std::pair<TXString, bool>( it, true ) );
	}

	std::map<TXString, bool>	mapOpened;
	for ( const auto& it : arrOpenedIDs )
	{
		mapOpened.insert( std::pair<TXString, bool>( it, true ) );
	}

	size_t  lastItemGroupIndex    = size_t(-1);
	bool    lastItemGroupIsChecked = true;

	TTreeNodeSpecArray detailedItems;
	fDataSource.GetAllItems( detailedItems );
	for ( const auto& it : detailedItems )
	{
		switch ( it.fType )
		{
			case ETreeNodeType::Delimiter:
				{
					if ( lastItemGroupIndex != size_t(-1) )
					{
						SListItem&	groupItem = farrListItems[ lastItemGroupIndex ];
						if ( groupItem.fIsOpened && !groupItem.fIsMandatory )
						{
							groupItem.fIsChecked = lastItemGroupIsChecked;
						}
					}

					lastItemGroupIsChecked	= true;

					SListItem	item;
					item.fRowIndex			= size_t(-1);
					item.fID				= it.fID;
					item.fIsChecked			= it.fIsMandatory;
					item.fIsGroup			= true;
					item.fIsGroupOnly		= it.fIsGroupOnly;
					item.fIsMandatory		= it.fIsMandatory;
					item.fIsVisible			= true;
					item.fIsOpened			= mapOpened.find( it.fID ) != mapOpened.end();
					item.fColumnValues		= it.fColumnValues;

					farrListItems.push_back( item );

					lastItemGroupIndex		= farrListItems.size() - 1;
				}
				break;

			case ETreeNodeType::DataItem:
				if ( lastItemGroupIndex < farrListItems.size() )
				{
					SListItem&	groupItem	= farrListItems[ lastItemGroupIndex ];

					SListItem	item;
					item.fRowIndex		= size_t(-1);
					item.fID			= it.fID;
					item.fIsChecked		= it.fIsMandatory || ( mapChecked.find( it.fID ) != mapChecked.end() );
					item.fIsGroup		= false;
					item.fIsGroupOnly	= false;
					item.fIsMandatory	= it.fIsMandatory;
					item.fIsVisible		= groupItem.fIsOpened;
					item.fIsOpened		= false;
					item.fColumnValues  = it.fColumnValues;

					if ( item.fIsChecked )
					{
						if ( !groupItem.fIsOpened )
						{
							groupItem.fIsChecked	= true;
						}
					}
					else
					{
						lastItemGroupIsChecked = false;
					}

					// this push_back might change the 'groupItem' reference
					farrListItems.push_back( item );
				}	
				break;

			case ETreeNodeType::Button:
				// we can't show these
				break;
		}
	}
}

void VWListBrowserTreeCtrl::GetClickTargetRow(size_t selItemIdx, size_t fallbackRow, size_t& outTargetRow) const
{
	outTargetRow = fallbackRow;

	if ( !farrListItems[ selItemIdx ].fIsGroup )
	{
		for ( size_t i = selItemIdx - 1; i != size_t( -1 ); i-- )
		{
			if ( farrListItems[ i ].fIsGroup )
			{
				if ( farrListItems[ i ].fIsGroupOnly && !farrListItems[ i ].fIsMandatory )
					outTargetRow = farrListItems[ i ].fRowIndex;
				break;
			}
		}
	}
}

void VWListBrowserTreeCtrl::ToggleSelection(const TSizeTArray& selItems, bool value)
{
	std::set<size_t> toggled;

	for ( const auto& it : selItems )
	{
		size_t idx = farrLBRowIndex2ListItemIndex[ it ];
		if ( !farrListItems[ idx ].fIsMandatory )
		{
			size_t targetRow;
			this->GetClickTargetRow( idx, it, targetRow );

			if ( toggled.insert( targetRow ).second )
				this->SetCheck( targetRow, value );
		}
	}
}

void VWListBrowserTreeCtrl::RestoreSelectionImages(const TSizeTArray& selItems)
{
	VWListBrowserCtrl* theList = fpParentDlg->GetListBrowserCtrlByID( fControlID );
	for ( const auto& it : selItems )
	{
		size_t idx = farrLBRowIndex2ListItemIndex[ it ];
		if( farrListItems[ idx ].fIsMandatory )
			theList->GetItem( it, 0 ).SetItemImage( this->GetCheckImage( farrListItems[ idx ] ) );
	}
}

void VWListBrowserTreeCtrl::WriteColumnValues( VWListBrowserCtrl* theList, size_t rowIndex, const std::map<TXString, TXString>& colValues ) const
{
	for ( size_t c = 0; c < farrColumnSpecs.size(); ++c )
	{
		auto it = colValues.find( farrColumnSpecs[ c ].fID );
		if ( it != colValues.end() )
		{
			theList->GetItem( rowIndex, 2 + c ).SetItemText( it->second );
		}
	}
}

void VWListBrowserTreeCtrl::ApplyRowEnabledState(VWListBrowserCtrl* theList, size_t rowIndex, bool enabled) const
{
	EUiControlTextTint tint = enabled ? EUiControlTextTint::eDefaultTint : EUiControlTextTint::eDisabledTint;

	size_t totalCols = 2 + farrColumnSpecs.size();
	for (size_t col = 0; col < totalCols; ++col)
	{
		VWListBrowserItem item = theList->GetItem(rowIndex, col);
		item.SetItemTextColorN(tint);
	}
}

size_t VWListBrowserTreeCtrl::GetCheckImage(const SListItem& data) const
{
	if (!data.fIsChecked)
		return fImageIndexBlank;
	return data.fIsMandatory ? fImageIndexCheckmarkDisabled : fImageIndexCheckmark;
}

void VWListBrowserTreeCtrl::ResyncRowIndices()
{
	for ( auto& item : farrListItems )
		item.fRowIndex = size_t(-1);

	for ( size_t r = 0, cnt = farrLBRowIndex2ListItemIndex.size(); r < cnt; ++r )
	{
		size_t arrayIdx = farrLBRowIndex2ListItemIndex[ r ];
		farrListItems[ arrayIdx ].fRowIndex = r;
	}
}

void VWListBrowserTreeCtrl::SetCheck(size_t rowIndex, bool value)
{
	VWListBrowserCtrl*	theList		= fpParentDlg->GetListBrowserCtrlByID( fControlID );

	size_t				itemIndex	= farrLBRowIndex2ListItemIndex[ rowIndex ];
	auto&				itemData	= farrListItems[ itemIndex ];

	if ( itemData.fIsGroup )
	{
		for ( size_t i = itemIndex + 1, cnt = farrListItems.size(); i < cnt; ++i )
		{
			auto& data		= farrListItems[ i ];
			if ( data.fIsGroup )
				break;

			if ( !data.fIsMandatory )
			{
				data.fIsChecked	= value;

				if ( data.fRowIndex != size_t(-1) )
				{
					theList->GetItem( data.fRowIndex, 0 ).SetItemImage( this->GetCheckImage( data ) );
				}
			}		
		}

		if ( !itemData.fIsMandatory )
		{
			itemData.fIsChecked	= value;
			theList->GetItem( rowIndex, 0 ).SetItemImage( this->GetCheckImage( itemData ) );
		}
	}
	else
	{
		if ( !itemData.fIsMandatory )
		{
			itemData.fIsChecked	= value;
			theList->GetItem( rowIndex, 0 ).SetItemImage( this->GetCheckImage( itemData ) );
		}

	}
}

void VWListBrowserTreeCtrl::CollapseItems(size_t groupRowIndex, size_t listItem)
{
	VWListBrowserCtrl*	theList		= fpParentDlg->GetListBrowserCtrlByID( fControlID );

	auto&				groupItem	= farrListItems[ listItem ];
	groupItem.fIsChecked			= groupItem.fIsMandatory;

	size_t			deleteAtIndex	= groupRowIndex + 1;

	for ( size_t i = listItem + 1, cnt = farrListItems.size(); i < cnt; ++i )
	{
		auto& data				= farrListItems[ i ];
		if ( data.fIsGroup )
			break;

		groupItem.fIsChecked	= groupItem.fIsChecked || data.fIsChecked;

		if ( deleteAtIndex < farrLBRowIndex2ListItemIndex.size() )
		{
			theList->DeleteRow( deleteAtIndex );

			farrLBRowIndex2ListItemIndex.erase( farrLBRowIndex2ListItemIndex.begin() + deleteAtIndex );
		}
	}

	groupItem.fIsOpened				= false;
	theList->GetItem( groupRowIndex, 0 ).SetItemImage( this->GetCheckImage( groupItem ) );
	theList->GetItem( groupRowIndex, 1 ).SetItemImage( fImageIndexTreeClosed );

	this->ResyncRowIndices();
}

void VWListBrowserTreeCtrl::ExpandItems(size_t groupRowIndex, size_t listItem)
{
	VWListBrowserCtrl*		theList			= fpParentDlg->GetListBrowserCtrlByID( fControlID );

	bool					isGroupChecked	= false;

	size_t					insertAtIndex	= groupRowIndex + 1;

	for ( size_t i = listItem + 1, cnt = farrListItems.size(); i < cnt; ++i )
	{
		auto&	data	= farrListItems[ i ];
		if ( data.fIsGroup )
			break;

		if ( i == listItem + 1 )
		{
			isGroupChecked = true;
		}
		isGroupChecked	= isGroupChecked && data.fIsChecked;

		size_t	rowIndex = theList->InsertRow( insertAtIndex, "" );
		theList->GetItem( rowIndex, 0 ).SetItemImage( this->GetCheckImage( data ) );
		theList->GetItem( rowIndex, 1 ).SetItemImage( fImageIndexBlank );
		this->WriteColumnValues( theList, rowIndex, data.fColumnValues );

		this->ApplyRowEnabledState( theList, rowIndex, !data.fIsMandatory );

		farrLBRowIndex2ListItemIndex.insert( farrLBRowIndex2ListItemIndex.begin() + insertAtIndex, i );
		insertAtIndex++;
	}

	auto&					groupItem		= farrListItems[ listItem ];
	groupItem.fIsChecked					= groupItem.fIsMandatory ? true : isGroupChecked;
	groupItem.fIsOpened						= true;
	theList->GetItem( groupRowIndex, 0 ).SetItemImage( this->GetCheckImage( groupItem ) );
	theList->GetItem( groupRowIndex, 1 ).SetItemImage( fImageIndexTreeOpen );

	this->ResyncRowIndices();
}
