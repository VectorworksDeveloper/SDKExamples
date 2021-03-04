#include "StdAfx.h"
#include "DlgDirectEditListBrowser.h"

// dialog control IDs
enum EDirectEditLB {
	kOK                   = 1,
	kCancel               = 2,
	kListBr               = 4,
};


using namespace UI;

EVENT_DISPATCH_MAP_BEGIN( CDlgDirectEditListBrowser );
ADD_LB_DIRECT_EDIT( kListBr, OnListBrowserDirectEdit );
EVENT_DISPATCH_MAP_END;

CDlgDirectEditListBrowser::CDlgDirectEditListBrowser()
{
	fRowInfo.push_back( SSelectedRowInfo( fUserName[0]	, "", "", true, fUnits[ 0 ], false) );
	fRowInfo.push_back( SSelectedRowInfo( fUserName[1]	, "", "", true, fUnits[ 0 ], false) );
	fRowInfo.push_back( SSelectedRowInfo( fUserName[2]	, "", "", true, fUnits[ 0 ], false) );

	size_t index = 0;
	for ( const auto& it : fWorkSpacesData )
	{
		fRowInfo[ index ].fWorkSpace	= it.first;
		fRowInfo[ index ].fToolName		= it.second[ 0 ];

		index++;
	}
}

CDlgDirectEditListBrowser::~CDlgDirectEditListBrowser()
{
}

bool CDlgDirectEditListBrowser::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "VWUI Dialogs Sample/DialogLayout/DirectEditLB.vs" );
}

void CDlgDirectEditListBrowser::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	VWListBrowserCtrl* pListBrowser	= this->GetListBrowserCtrlByID( kListBr );
	pListBrowser->EnableSorting( false );
	pListBrowser->EnableDirectEdit( true );

	pListBrowser->AddColumn( "User name"			, 100 ); // static text
	pListBrowser->AddColumn( "Workspace"			, 100 ); // popUp
	pListBrowser->AddColumn( "Tool name"			, 100 ); // popUp
	pListBrowser->AddColumn( "Use"					, 100 ); // check box
	pListBrowser->AddColumn( "Units"				, 100 ); // popUp
	pListBrowser->AddColumn( "Hide previous  field"	, 100 ); // check box

	this->UpdateLB();
}

void CDlgDirectEditListBrowser::OnDDXInitialize()
{
}

void CDlgDirectEditListBrowser::OnUpdateUI()
{
	VWDialog::OnUpdateUI();
}

void CDlgDirectEditListBrowser::UpdateLB()
{
	for ( size_t itRow = 0 ; itRow < fRowInfo.size(); itRow++ )
	{
		this->SetLBRow( itRow );
	}
}

void CDlgDirectEditListBrowser::SetLBRow( size_t row )
{
	VWListBrowserCtrl* paramList	= this->GetListBrowserCtrlByID( kListBr );

	if ( row == (size_t)-1 || row >= fRowInfo.size() )
	{
		row = paramList->GetFirstSelected();
	}
	
	//cell 0----
	VWListBrowserItem item	= paramList->GetItem( row, (size_t)EFirstGroupModes::eUserName );
	item.SetItemText( fRowInfo[ row ].fUserName );

	//cell 1------
	item	= paramList->GetItem( row, (size_t)EFirstGroupModes::eWorkspace );
	item.SetItemText( fRowInfo[ row ].fWorkSpace );
	item.SetItemInteractionType( kListBrowserItemInteractionEditGenericList );

	//cell 2------
	item	= paramList->GetItem( row, (size_t)EFirstGroupModes::eTool );
	item.SetItemText( fRowInfo[ row ].fToolName );
	item.SetItemInteractionType( kListBrowserItemInteractionEditGenericList );

	//cell 3------
	TControlID dlgID = this->GetDialogID();

	item	= paramList->GetItem( row, (size_t)EFirstGroupModes::eUse );
	item.SetItemInteractionType( kListBrowserItemInteractionEditCheckState );
	gSDK->SetListBrowserItemCheckState( dlgID, kListBr, (Sint32)row, (size_t)EFirstGroupModes::eUse, fRowInfo[ row ].fUse ? CGSMultiStateValueChange::eStateValueOn : CGSMultiStateValueChange::eStateValueOff );
	
	//cell 4------
	item	= paramList->GetItem( row, (size_t)EFirstGroupModes::eUnits );
	item.SetItemText( fRowInfo[ row ].fUnits );
	item.SetItemInteractionType( kListBrowserItemInteractionEditGenericList );

	//cell 5------
	item	= paramList->GetItem( row, (size_t)EFirstGroupModes::eHidePreviousField );
	item.SetItemInteractionType( kListBrowserItemInteractionEditCheckState );
	gSDK->SetListBrowserItemCheckState( dlgID, kListBr, (Sint32)row, (size_t)EFirstGroupModes::eHidePreviousField, fRowInfo[ row ].fHidePreviousField ? CGSMultiStateValueChange::eStateValueOn : CGSMultiStateValueChange::eStateValueOff );
	
}

void CDlgDirectEditListBrowser::OnListBrowserDirectEdit( TControlID controlID, VWListBrowserEventArgs& eventArgs )
{
	size_t outRow, outColumn;
	EListBrowserDirectEditType directEditType	= eventArgs.GetType( outRow, outColumn );

	if ( directEditType == EListBrowserDirectEditType::QueryItemListRetrieval )
	{
		auto& itemCollection = eventArgs.GetCellMenuItemCollection();

		switch ( outColumn )
		{
			case (size_t)EFirstGroupModes::eWorkspace: //Workspace
			{
				size_t choiseIndex = 0;
				for ( const auto& itWorkspace : fWorkSpacesData )
				{
					const TXString& currWorkspace =  itWorkspace.first;

					CGSMenuItemValue item( currWorkspace, choiseIndex );

					if ( fRowInfo[ outRow ].fWorkSpace == currWorkspace )
					{
						item.SetCheckedState( true );
					}
					itemCollection.AddMenuItem( item );
				}

				break;
			}

			case (size_t)EFirstGroupModes::eTool : //Tool Names
			{
				size_t choiseIndex = 0;
				{
					TXString savedToolName = fRowInfo[ outRow ].fWorkSpace;

					const auto& itWorkspace =  fWorkSpacesData.find( savedToolName );
					if ( itWorkspace != fWorkSpacesData.end() )
					{
						const StrVec& toolNames = itWorkspace->second;

						for ( size_t itTools = 0; itTools < toolNames.size(); itTools++ )
						{
							TXString currToolName = toolNames[ itTools ];
							CGSMenuItemValue item( currToolName, choiseIndex );

							if ( savedToolName == currToolName )
							{
								item.SetCheckedState( true );
							}
							itemCollection.AddMenuItem( item );
						}
					}
				}

				break;
			}
			case (size_t)EFirstGroupModes::eUnits : //Units
			{
				for ( size_t itUnits = 0; itUnits < fUnits.size(); itUnits++ )
				{
					TXString currUnit = fUnits[ itUnits ];
					CGSMenuItemValue item( currUnit, itUnits );

					if ( fRowInfo[ outRow ].fWorkSpace == currUnit )
					{
						item.SetCheckedState( true );
					}
					itemCollection.AddMenuItem( item );
				}

				break;
			}

			case (size_t)EFirstGroupModes::eUse :
			{
				CGSMultiStateValueChange& checkboxData = eventArgs.GetCellCheckbox();
				checkboxData.fStateValue = fRowInfo[ outRow ].fUse ? CGSMultiStateValueChange::eStateValueOn : CGSMultiStateValueChange::eStateValueOff;
			
				break;
			}

			case (size_t)EFirstGroupModes::eHidePreviousField : //Units
			{
				CGSMultiStateValueChange& checkboxData = eventArgs.GetCellCheckbox();
				checkboxData.fStateValue = fRowInfo[ outRow ].fHidePreviousField ? CGSMultiStateValueChange::eStateValueOn : CGSMultiStateValueChange::eStateValueOff;

				break;
			}


			default:
				break;
		}
	}
	else if ( directEditType == EListBrowserDirectEditType::QueryItemValue )
	{
		CGSMultiStateValueChange& checkboxData = eventArgs.GetCellCheckbox();	

		if ( outColumn == (size_t)EFirstGroupModes::eUse )
		{
			checkboxData.fStateValue = fRowInfo[ outRow ].fUse? CGSMultiStateValueChange::eStateValueOn : CGSMultiStateValueChange::eStateValueOff;
		}
		else if ( outColumn == (size_t)EFirstGroupModes::eHidePreviousField )
		{
			checkboxData.fStateValue = fRowInfo[ outRow ].fHidePreviousField? CGSMultiStateValueChange::eStateValueOn : CGSMultiStateValueChange::eStateValueOff;
		}
	}

	else if ( directEditType == EListBrowserDirectEditType::ItemEditCompletionData )
	{
		const TXString& newValue = eventArgs.GetCellMenuItemValue().fMenuItemName;

		switch ( outColumn )
		{
			case (size_t) EFirstGroupModes::eWorkspace:
			{
				fRowInfo[ outRow ].fWorkSpace	= newValue;
				fRowInfo[ outRow ].fToolName	= fWorkSpacesData[ newValue ][ 0 ]; // get first tool name

				this->UpdateTextCel( outRow, (size_t)EFirstGroupModes::eWorkspace, newValue );
				this->UpdateTextCel( outRow, (size_t)EFirstGroupModes::eTool, fRowInfo[ outRow ].fToolName );

				break;
			}

			case (size_t)EFirstGroupModes::eTool : //Tool Names
			{
				fRowInfo[ outRow ].fToolName = newValue;

				this->UpdateTextCel( outRow, (size_t)EFirstGroupModes::eTool, newValue );
				break;
			}

			case (size_t)EFirstGroupModes::eUnits : //Units
			{
				fRowInfo[ outRow ].fUnits = newValue;
				this->UpdateTextCel( outRow, (size_t)EFirstGroupModes::eUnits, newValue );
				break;
			}

			case (size_t)EFirstGroupModes::eUse :
			{
				CGSMultiStateValueChange checkboxData	= eventArgs.GetCellCheckbox();
				fRowInfo[ outRow ].fUse					= (checkboxData.fStateValue == CGSMultiStateValueChange::eStateValueOn);
				break;
			}

			case (size_t)EFirstGroupModes::eHidePreviousField :
			{
				CGSMultiStateValueChange checkboxData	= eventArgs.GetCellCheckbox();
				fRowInfo[ outRow ].fHidePreviousField	= (checkboxData.fStateValue == CGSMultiStateValueChange::eStateValueOn);
				break;
			}

			default:
				break;
		}
	}
}

void CDlgDirectEditListBrowser::UpdateTextCel( const size_t& row, const size_t& column, const TXString& newValue )
{
	VWListBrowserCtrl* paramList	= this->GetListBrowserCtrlByID( kListBr );
	VWListBrowserItem item			= paramList->GetItem( row, column );
	
	item.SetItemText( newValue );
}
