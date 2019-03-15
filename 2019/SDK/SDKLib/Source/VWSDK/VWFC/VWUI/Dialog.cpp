//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/Dialog.h"
#include "VWFC/VWUI/DialogEventArgs.h"

#include "VWFC/VWUI/Control.h"
#include "VWFC/VWUI/CheckButtonCtrl.h"
#include "VWFC/VWUI/GroupBoxCtrl.h"
#include "VWFC/VWUI/ListBoxCtrl.h"
#include "VWFC/VWUI/ListBrowserCtrl.h"
#include "VWFC/VWUI/MarkerPopupCtrl.h"
#include "VWFC/VWUI/PictureCtrl.h"
#include "VWFC/VWUI/PullDownMenuCtrl.h"
#include "VWFC/VWUI/PushButtonCtrl.h"
#include "VWFC/VWUI/RadioButtonCtrl.h"
#include "VWFC/VWUI/RadioGroupBoxCtrl.h"
#include "VWFC/VWUI/StaticTextCtrl.h"
#include "VWFC/VWUI/TabPaneCtrl.h"
#include "VWFC/VWUI/TabCtrl.h"
#include "VWFC/VWUI/ThumbnailPopupCtrl.h"
#include "VWFC/VWUI/CheckButtonCtrl.h"
#include "VWFC/VWUI/CheckGroupBoxCtrl.h"
#include "VWFC/VWUI/ColorButtonCtrl.h"
#include "VWFC/VWUI/EditIntegerCtrl.h"
#include "VWFC/VWUI/EditRealCtrl.h"
#include "VWFC/VWUI/EditTextCtrl.h"
#include "VWFC/VWUI/SliderCtrl.h"
#include "VWFC/VWUI/ColorPopupCtrl.h"
#include "VWFC/VWUI/PatternPopupCtrl.h"
#include "VWFC/VWUI/LineAttributePopupCtrl.h"
#include "VWFC/VWUI/LineStylePopupCtrl.h"
#include "VWFC/VWUI/LineWeightPopupCtrl.h"
#include "VWFC/VWUI/ChooseClassPopupCtrl.h"
#include "VWFC/VWUI/CustomCtrl.h"
#include "VWFC/VWUI/StyleButtonCtrl.h"
#include "VWFC/VWUI/ChooseLayerPopupCtrl.h"
#include "DialogData.h"

#undef NEW_OBJECT
#undef DELETE_OBJECT
// memory managment macros
#define		NEW_OBJECT(T)				new ( malloc( sizeof(T) ) ) T
#define		DELETE_OBJECT(T, p)			if ( p ) { p->~T(); free( p ); } p = NULL;

using namespace VWFC::VWUI;
using namespace VWFC::Tools;

EVENT_DISPATCH_MAP_BEGIN( VWDialog );
EVENT_DISPATCH_MAP_END;

VWDialog::VWDialog()
: VWControlsContainer( 0 )
{
	fbIsSetup				= false;
	fpSelectionSupport		= NULL;

	fpStyleSupport = NULL;
	fbStyleMode = false;

	// allocate arrays
	fpArrControls			= NEW_OBJECT( TControlsArray );
	fpArrTabPanes			= NEW_OBJECT( TTabPanesArray );
	fpArrDDXData			= NEW_OBJECT( TDDXDataArray );
	
	this->InitExtendedEventSupport();
}

VWDialog::~VWDialog()
{
	this->DeinitExtendedEventSupport();

	TControlsArray*				pArrControls	= (TControlsArray*) fpArrControls;
	TTabPanesArray*				pArrPanes		= (TTabPanesArray*) fpArrTabPanes;
	TDDXDataArray*				pArrDDX			= (TDDXDataArray*) fpArrDDXData;

	if ( pArrControls ) {
		size_t				len				= pArrControls->size();
		for(size_t i=0; i<len; i++) {
			SChildControls&	child	= (*pArrControls)[ i ];
			if ( child.bFake ) {
				DELETE_OBJECT( VWControl, child.pControl );
			}
		}
		pArrControls->clear();
	}

	// free
	DELETE_OBJECT( TControlsArray, pArrControls );
	DELETE_OBJECT( TTabPanesArray, pArrPanes );
	DELETE_OBJECT( TDDXDataArray, pArrDDX );

	fpArrControls		= NULL;
	fpArrTabPanes		= NULL;
	fpArrDDXData		= NULL;
}

bool VWDialog::CreateDialog(const TXString& dlgTitle, const TXString& defaultBtn, const TXString& cancelBtn, bool hasHelp/*=true*/, bool bResizableWidth/*=false*/, bool bResizableHeight/*=false*/)
{
	if ( bResizableWidth || bResizableHeight ) {
		fControlID = ::GS_CreateResizableLayout( gCBP, dlgTitle, hasHelp, defaultBtn, cancelBtn, bResizableWidth, bResizableHeight );
	}
	else {
		fControlID = ::GS_CreateLayout( gCBP, dlgTitle, hasHelp, defaultBtn, cancelBtn );
	}
	return ::GS_VerifyLayout( gCBP, fControlID ) ? true : false;
}

bool VWDialog::CreateDialog(short strListID, short dlgTitleIndex, short defaultBtnIndex, short cancelBtnIndex, bool hasHelp/*=true*/, bool bResizableWidth/*=false*/, bool bResizableHeight/*=false*/)
{
	TXString dlgTitle	= TXLegacyResource(strListID, dlgTitleIndex);
	TXString defaultBtn	= TXLegacyResource(strListID, defaultBtnIndex );
	TXString cancelBtn	= TXLegacyResource(strListID, cancelBtnIndex);


	if ( bResizableWidth || bResizableHeight ) {
		fControlID = ::GS_CreateResizableLayout( gCBP, dlgTitle, hasHelp, defaultBtn, cancelBtn, bResizableWidth, bResizableHeight );
	}
	else {
		fControlID = ::GS_CreateLayout( gCBP, dlgTitle, hasHelp, defaultBtn, cancelBtn);
	}
	return ::GS_VerifyLayout( gCBP, fControlID ) ? true : false;
}

bool VWDialog::CreateDialogLayoutFromRsrc(short TEXTResourceID)
{
	fControlID = ::GS_GetLayoutFromRsrc( gCBP, TEXTResourceID );
	return ::GS_VerifyLayout( gCBP, fControlID ) ? true : false;
}

bool VWDialog::CreateDialogLayoutFromRsrcAndVWR(short TEXTResourceID, const char* defaultVWRName)
{
    gSDK->Kludge(3602, (void *)defaultVWRName, NULL);
    return CreateDialogLayoutFromRsrc(TEXTResourceID);
}

bool VWDialog::CreateDialogLayoutFromVWR(const char* resIdentifier)
{
    fControlID = gSDK->CreateLayoutDialogFromVWResource(resIdentifier);
    return ::GS_VerifyLayout( gCBP, fControlID ) ? true : false;
}

TControlID VWDialog::GetDialogID() const
{
	return fControlID;
}

void VWDialog::SetDefaultButtonHelpString(const TXString& helpText)
{
	::GS_SetHelpText( gCBP, fControlID, 1, helpText );
}

void VWDialog::SetDefaultButtonHelpString(short strListID, short strHelpIndex)
{
	this->SetDefaultButtonHelpString( TXLegacyResource( strListID, strHelpIndex ) );
}

void VWDialog::SetCancelButtonHelpString(const TXString& helpText)
{
	::GS_SetHelpText( gCBP, fControlID, 2, helpText );
}

void VWDialog::SetCancelButtonHelpString(short strListID, short strHelpIndex)
{
	this->SetCancelButtonHelpString( TXLegacyResource( strListID, strHelpIndex ) );
}

VWDialogEventArgs VWDialog::GetEmptyEventArgs(TControlID controlID) const
{
	return VWDialogEventArgs( fControlID, controlID, NULL );
}

VWDialogEventArgs VWDialog::GetEmptyEventArgs(VWControl* pControl) const
{
	return VWDialogEventArgs( fControlID, pControl->fControlID, NULL );
}

ViewRect VWDialog::GetDialogDimension() const
{
	short	left, top, right, bottom;
	Boolean	ok	= ::GS_GetLayoutDialogPosition( gCBP, this->GetDialogID(), left, top, right, bottom );
	VERIFYN( kVStanev, ok );

	ViewRect	dlgDim;
	if ( ok ) {
		dlgDim.left			= left;
		dlgDim.top			= top;
		dlgDim.right		= right;
		dlgDim.bottom		= bottom;
	}

	return dlgDim;
}

ViewPt VWDialog::GetDialogPosition() const
{
	short	left, top, right, bottom;
	Boolean	ok	= ::GS_GetLayoutDialogPosition( gCBP, this->GetDialogID(), left, top, right, bottom );
	VERIFYN( kVStanev, ok );

	ViewPt	dlgPos;
	if ( ok ) {
		dlgPos.x			= left;
		dlgPos.y			= top;
	}

	return dlgPos;
}

void VWDialog::SetDialogPosition(ViewCoord left, ViewCoord top)
{
	VERIFYN( kVStanev, ::GS_SetLayoutDialogPosition( gCBP, this->GetDialogID(), left, top ) );
}

void VWDialog::GetDialogSize(ViewCoord& outWidth, ViewCoord& outHeight) const
{
	short		width, height;
	::GS_GetLayoutDialogSize( gCBP, this->GetDialogID(), width, height);

	outWidth		= width;
	outHeight		= height;
}

void VWDialog::SetDialogSize(ViewCoord width, ViewCoord height) const
{
	::GS_SetLayoutDialogSize( gCBP, this->GetDialogID(), width, height );
}

EDialogButton VWDialog::RunDialogLayout(const TXString &contextualHelpID)
{
    return RunDialogLayout(contextualHelpID, true);
}

EDialogButton VWDialog::RunDialogLayout(const TXString &contextualHelpID, const bool bEnableContextualHelp)
{
    // first create the layout
    if ( ! this->CreateDialogLayout() )
        return kDialogButton_None;
    
    TControlID	result	= 0;
    // check if the dialog was created with CreateDilaogLayout
    ASSERTN( kVStanev, fControlID != 0 );
    if ( fControlID == 0 )
        return kDialogButton_None;
    
    // set off the setup of the dialog
    // we dont want to dispatch messages untill the dialog is setup
    fbIsSetup			= false;
    
    bool	isLayoutOK	= ::GS_VerifyLayout( gCBP, fControlID );
    ASSERTN( kVStanev, isLayoutOK );
    // Verify that all items were created on the dialog.
    if ( isLayoutOK ) {
        // Display the dialog. Will call the Event handling routine specified.
        // Returns the id of the button used to close the dialog: 1 for default button, 2 for cancel button.
        result = gSDK->RunLayoutDialog( fControlID, VWDialog::DialogEventHandler, this, contextualHelpID, bEnableContextualHelp);
    }
    
    return (EDialogButton) result;
}

void VWDialog::DialogEventHandler(Sint32 dlogID, Sint32& itemHit, void* data, void* env)
{
	VWDialog*		pEnv	= static_cast<VWDialog*>( env );
	ASSERTN( kVStanev, pEnv );
	if ( pEnv )
	{
		// assert that this event belongs to the environment dialog that has to be called
		if ( VERIFYN( kVStanev, pEnv->fControlID == dlogID ) ) {
			pEnv->LocalDialogEventHandler( itemHit, data );
		}
	}
}

void VWDialog::LocalDialogEventHandler(Sint32& itemHit, void* pData)
{
	ASSERTN( kVStanev, fpArrControls );
	ASSERTN( kVStanev, fpArrTabPanes );
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrControls == NULL || fpArrTabPanes == NULL || fpArrDDXData == NULL )
		return;
	TTabPanesArray&		arrPanes		= * ((TTabPanesArray*) fpArrTabPanes);

	bool		bUpdateUI		= false;

	switch( itemHit )
	{
	case kSetupMessage: {
			this->OnSetUpEvent();

			bUpdateUI		= true;
			fbIsSetup		= true;
		} break;
	case kSetdownMessage: {
			this->OnSetDownEvent();

			size_t	len		= arrPanes.size();
			for(size_t i=0; i<len; i++) {
				VWTabPaneCtrl*	pPane	= arrPanes[ i ];
				pPane->OnSetDownEvent();
			}
			fbIsSetup		= false;
		} break;
	case kDefaultButtonID:
		// update the variables
		this->UpdateData( false );

		// let itemHit be 0 which means that the dialog wont close
		// by 'fstackItemHit' VWDialog function for default button handling can set itemHit not null and cause dialog to close
		fstackItemHit.push_back( & itemHit );
		itemHit			= 0;
		this->SaveListBrowserColumnSavedSets();
		this->OnDefaultButtonEvent();
		this->OnSaveSavedSettings( true );
		fstackItemHit.pop_back();
		break;
	case kCancelButtonID:
		// let itemHit be 0 which means that the dialog wont close
		// by 'fstackItemHit' VWDialog function for cancel button handling can set itemHit not null and cause dialog to close
		fstackItemHit.push_back( & itemHit );
		itemHit			= 0;
		this->SaveListBrowserColumnSavedSets();
		this->OnCancelButtonEvent();
		this->OnSaveSavedSettings( false );
		fstackItemHit.pop_back();
		break;

	case kCanEditLabelMessage:
		if ( pData )
		{
			TItemMessageData* messageData = (TItemMessageData*) pData;
			bool result = this->OnTreeCtrlCanEditLabel( messageData->fControl, messageData->fItemId );
			messageData->fReturnCode = result ? 1 : 0;
		}
		break;

	case kEditLabelCompleteMessage:
		if ( pData )
		{
			TItemMessageData* messageData = (TItemMessageData*) pData;
			this->OnTreeCtrlCompleteEditlabel( messageData->fControl, messageData->fItemId );
		}
		break;

	case kCanDeleteItemMessage:
		if ( pData )
		{
			TItemMessageData* messageData = (TItemMessageData*) pData;
			bool result = this->OnTreeCtrlCanDeleteItem( messageData->fControl, messageData->fItemId );
			messageData->fReturnCode = result ? 1 : 0;
		}
		break;

	case kDeletedItemMessage:
		if ( pData )
		{
			TItemMessageData* messageData = (TItemMessageData*) pData;
			this->OnTreeCtrlDeleteItem( messageData->fControl, messageData->fItemId );
		}
		break;

	case kDragOverMessage:
		if ( pData )
		{
			TDragMessageData*				dragData = (TDragMessageData*) pData;
			TTreeControlDropMessageData*	dropData = (TTreeControlDropMessageData*) dragData->fData;
			this->OnTreeCtrlDragOver(  dropData->fSourceControlID, *dropData );
			dragData->fShowPreview = dropData->fAllow;
		}
		break;

	case kDropMessage:
		if ( pData )
		{
			TTreeControlDropMessageData*	dropData = (TTreeControlDropMessageData*) pData;
			this->OnTreeCtrlDrop( dropData->fSourceControlID, *dropData );
		}
		break;

	default: {
			// dont dispatch if the dialog has not need setup
			// there were the times when VW called event for the tab control
			// even before the setup event -- prevet this!!!
			if ( fbIsSetup ) {
				// update the variables
				Sint32		controlID	= itemHit >= 0 ? itemHit : - itemHit;				
				VWDialogEventArgs	eventArg( this->GetControlID(), itemHit, pData );				
				
				this->UpdateSelectionInfo( controlID, eventArg );
				this->UpdateData( false );

				bUpdateUI		= true;

				// control IDs are always positive values
				// negative value for 'itemHit' is used to
				// specify special event for the control with Abs(itemHit) ID
				// we let the VWDialogEventArgs class handle this specific event
				// and work with absolute control ID value

				VWControl*	pControl	= this->GetControl( controlID );
				if ( pControl )
					this->OnControlEvent( pControl );

				fstackItemHit.push_back( & itemHit );

				// store saved data if necessary
				for(const SSavedColumnData& data : farrSavedSwapTabData)
				{
					if ( data.fControlID == controlID )
					{
						if ( data.fColumnIndex == 0 ) // swap
						{
							VWListBoxCtrl*	overviewPaneList	= this->GetListBoxCtrlByID( data.fControlID );
							size_t	selIndex = overviewPaneList->GetSelectedIndex();
							if ( selIndex != size_t(-1) )
							{
								if ( data.fTranslateCallback )
								{
									selIndex = data.fTranslateCallback( true, selIndex );
								}									

								this->SetSavedValue( data.fSavedSettingsColumnName, TXString::ToStringInt( selIndex ) );

								if ( data.fAutoSwap )
								{
									VWSwapCtrl* swap = this->GetSwapCtrlByID( data.fSupportControlID );
									swap->SetActivePaneIndex( selIndex );
								}
							}
						}
						else if ( data.fColumnIndex == 1 ) // tab
						{
							VWTabCtrl*		tabCtrl			= this->GetTabCtrlByID( data.fControlID );
							TControlID		activeControlID	= tabCtrl->GetActivePaneControlID();
							this->SetSavedValue( data.fSavedSettingsColumnName, TXString::ToStringInt( activeControlID ) );
						}
					}
				}

				this->OnBeforeDispatchEvent( controlID, eventArg );

				if ( itemHit == kDialogTimerEventMessage )
				{
					this->OnDialogTimer();
				}
				else
				{
					// dispatch the event into the dialogs' event dispatching map
					this->DispatchEvent( controlID, eventArg );
				}

				if ( controlID > 2 ) {
					size_t	len		= arrPanes.size();
					for(size_t i=0; i<len; i++) {
						VWTabPaneCtrl*	pPane	= arrPanes[ i ];
						pPane->DispatchEvent( controlID, eventArg );
					}
				}

				fstackItemHit.pop_back();
			}
		} break;
	}


	if ( bUpdateUI ) {
		this->OnUpdateUI();

		size_t	len		= arrPanes.size();
		if ( len > 0 ) {
			bool	bEnableOK	= true;
			for(size_t i=0; i<len; i++) {
				VWTabPaneCtrl*	pPane	= arrPanes[ i ];
				pPane->OnUpdateUI();
				bEnableOK	= bEnableOK && pPane->CanEnableOK();
			}
			this->EnableDefaultButton( bEnableOK );
		}
	}
}

void VWDialog::OnSetUpEvent()
{
	fSavedDialogPosition.MakeEmpty();

	// before all, read saved settings for this dialog if available
	this->UpdateSavedSettings( true );

	if ( ! fSavedDialogPosition.IsEmpty() ) {
		// set the saved settings dialog dimensions
		this->SetDialogPosition( fSavedDialogPosition.left, fSavedDialogPosition.top );
		this->SetDialogSize( fSavedDialogPosition.Width(), fSavedDialogPosition.Height() );
	}

	ASSERTN( kVStanev, fpArrTabPanes );
	if ( fpArrTabPanes == NULL )
		return;
	TTabPanesArray&		arrPanes		= * ((TTabPanesArray*) fpArrTabPanes);

	// set up event to the panes
	size_t	panesCnt		= arrPanes.size();
	for(size_t i=0; i<panesCnt; i++) {
		VWTabPaneCtrl*	pPane	= arrPanes[ i ];
		pPane->OnSetUpEvent();
	}

	this->OnLoadSavedSettings();

	// initialize content before attaching DDX
	this->OnInitializeContent();
	

	for(const SSavedColumnData& data : farrSavedSwapTabData)
	{
		if ( data.fColumnIndex == 0 ) // swap
		{
			size_t selPaneIndex		= this->GetSavedValue( data.fSavedSettingsColumnName, "0" ).atoi();
			size_t selListIndex		= selPaneIndex;
			if ( data.fTranslateCallback )
			{
				selListIndex = data.fTranslateCallback( false, selPaneIndex );
			}									

			VWListBoxCtrl*	overviewPaneList	= this->GetListBoxCtrlByID( data.fControlID );
			overviewPaneList->SelectIndex( selListIndex );

			VWSwapCtrl*		swapPaneCtrl	= this->GetSwapCtrlByID( data.fSupportControlID );
			swapPaneCtrl->SetActivePaneIndex( selPaneIndex );
		}
		else if ( data.fColumnIndex == 1 ) // tab
		{
			VWTabCtrl*		tabCtrl			= this->GetTabCtrlByID( data.fControlID );
			size_t			selPaneIndex	= this->GetSavedValue( data.fSavedSettingsColumnName, "0" ).atoi();
			tabCtrl->SetActivePaneControlID( (TControlID) selPaneIndex );
		}
	}
	for(size_t i=0; i<panesCnt; i++) {
		VWTabPaneCtrl*	pPane	= arrPanes[ i ];
		pPane->OnInitializeContent();
	}

	// initialize DDX
	this->OnDDXInitialize();
	for(size_t i=0; i<panesCnt; i++) {
		VWTabPaneCtrl*	pPane	= arrPanes[ i ];
		pPane->OnDDXInitialize();
	}
	
	// update UI
	this->UpdateData( true );
}

void VWDialog::OnSetDownEvent()
{
	// get dialog dimensions
	ViewCoord	width	= 0;
	ViewCoord	height	= 0;
	ViewPt		dlgPos	= this->GetDialogPosition();
	this->GetDialogSize( width, height );

	// ... and prepare it as saved settings
	fSavedDialogPosition.left	= dlgPos.x;
	fSavedDialogPosition.top	= dlgPos.y;
	fSavedDialogPosition.left	= dlgPos.x + width;
	fSavedDialogPosition.top	= dlgPos.y + height;

	// save saved settings for this dialog if available
	this->UpdateSavedSettings( false );

	this->DeregisterForTimerEvents();
}

void VWDialog::OnDefaultButtonEvent()
{
	this->UpdateStyleSupport();

	for(auto it : fstackItemHit)
	{
		if ( it )
		{
			*it = 1;
		}
	}
}

void VWDialog::OnCancelButtonEvent()
{
	for(auto it : fstackItemHit)
	{
		if ( it )
		{
			*it = 2;
		}
	}
}

void VWDialog::OnControlEvent(VWControl* /*pParentControl*/)
{
}

void VWDialog::OnBeforeDispatchEvent(TControlID /*controlID*/, VWDialogEventArgs& /*eventArg*/)
{
}

void VWDialog::OnDialogTimer()
{
}

bool VWDialog::OnTreeCtrlCanEditLabel(TControlID controlID, TTreeItemID treeItemID)
{
	return false;
}

void VWDialog::OnTreeCtrlCompleteEditlabel(TControlID controlID, TTreeItemID treeItemID)
{
}

bool VWDialog::OnTreeCtrlCanDeleteItem(TControlID controlID, TTreeItemID treeItemID)
{
	return false;
}

void VWDialog::OnTreeCtrlDeleteItem(TControlID controlID, TTreeItemID treeItemID)
{
}

void VWDialog::OnTreeCtrlDragOver(TControlID controlID, TTreeControlDropMessageData& data)
{
}

void VWDialog::OnTreeCtrlDrop(TControlID controlID, TTreeControlDropMessageData& data)
{
}

void VWDialog::OnInitializeContent()
{
}

void VWDialog::OnUpdateUI()
{
}

void VWDialog::OnLoadSavedSettings()
{
}

void VWDialog::OnSaveSavedSettings(bool closedOk)
{
}

TXString VWDialog::GetDialogTitle() const
{
	TXString	title;
	::GS_GetItemText( gCBP, this->GetDialogID(), this->GetDialogID(), title );
	return title;
}

void VWDialog::SetDialogTitle( const TXString &inTitle )
{
	::GS_SetItemText( gCBP, this->GetDialogID(), this->GetDialogID(), inTitle);
}

void VWDialog::EnableDefaultButton(bool bEnable)
{
	::GS_EnableItem( gCBP, fControlID, 1, bEnable );
}

void VWDialog::EnableCancelButton(bool bEnable)
{
	::GS_EnableItem( gCBP, fControlID, 2, bEnable );
}

void VWDialog::EnableControl(TControlID id, bool bEnable)
{
	::GS_EnableItem( gCBP, fControlID, id, bEnable );
}

void VWDialog::ShowControl(TControlID id, bool bVisible)
{
	::GS_ShowItem( gCBP, fControlID, id, bVisible );
}

void VWDialog::SetControlHelpText(TControlID id, const TXString& helpText)
{
	::GS_SetHelpText( gCBP, fControlID, id, helpText );
}

void VWDialog::AddFirstGroupControl(VWControl* pControl)
{
	VERIFYN( kVStanev, ::GS_SetFirstLayoutItem( gCBP, fControlID, pControl->GetControlID() ) );
	this->AddControl( pControl );
}

void VWDialog::AddBelowControl(VWControl* pExistingControl, VWControl* pNewControl, short indentStdCh /*=0*/, short lineSpacing /*=0*/)
{
	VERIFYN( kVStanev, ::GS_SetBelowItem( gCBP, fControlID, pExistingControl->GetControlID(), pNewControl->GetControlID(), indentStdCh, lineSpacing ) );			
	this->AddControl( pNewControl );
}

void VWDialog::AddRightControl(VWControl* pExistingControl, VWControl* pNewControl, short indentStdCh /*=0*/, short lineSpacing /*=0*/)
{
	VERIFYN( kVStanev, ::GS_SetRightItem( gCBP, fControlID, pExistingControl->GetControlID(), pNewControl->GetControlID(), indentStdCh, lineSpacing ) );
	this->AddControl( pNewControl );
}

VWCheckButtonCtrl* VWDialog::GetCheckButtonCtrByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWCheckButtonCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWCheckButtonCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWCheckButtonCtrl*) pControl;
}

VWGroupBoxCtrl* VWDialog::GetGroupBoxCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWGroupBoxCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWGroupBoxCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWGroupBoxCtrl*) pControl;
}

VWListBoxCtrl* VWDialog::GetListBoxCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWListBoxCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWListBoxCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWListBoxCtrl*) pControl;
}

VWMarkerPopupCtrl* VWDialog::GetMarkerPopupCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWMarkerPopupCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWMarkerPopupCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWMarkerPopupCtrl*) pControl;
}

VWPictureCtrl* VWDialog::GetPictureCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWPictureCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWPictureCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWPictureCtrl*) pControl;
}

VWPullDownMenuCtrl* VWDialog::GetPullDownMenuCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWPullDownMenuCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWPullDownMenuCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWPullDownMenuCtrl*) pControl;
}

VWPushButtonCtrl* VWDialog::GetPushButtonCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWPushButtonCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWPushButtonCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWPushButtonCtrl*) pControl;
}

VWRadioButtonCtrl* VWDialog::GetRadioButtonCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWRadioButtonCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWRadioButtonCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWRadioButtonCtrl*) pControl;
}

VWRadioGroupBoxCtrl* VWDialog::GetRadioGroupBoxCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWRadioGroupBoxCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWRadioGroupBoxCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWRadioGroupBoxCtrl*) pControl;
}

VWStaticTextCtrl* VWDialog::GetStaticTextCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWStaticTextCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWStaticTextCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWStaticTextCtrl*) pControl;
}

VWTabPaneCtrl* VWDialog::GetTabPaneCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWTabPaneCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWTabPaneCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWTabPaneCtrl*) pControl;
}

VWTabCtrl* VWDialog::GetTabCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWTabCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWTabCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWTabCtrl*) pControl;
}

VWSwapPaneCtrl* VWDialog::GetSwapPaneCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWSwapPaneCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWSwapPaneCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWSwapPaneCtrl*) pControl;
}

VWSwapCtrl* VWDialog::GetSwapCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWSwapCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWSwapCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWSwapCtrl*) pControl;
}


VWThumbnailPopupCtrl* VWDialog::GetThumbnailPopupCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWThumbnailPopupCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWThumbnailPopupCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWThumbnailPopupCtrl*) pControl;
}

VWCheckButtonCtrl* VWDialog::GetCheckButtonCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWCheckButtonCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWCheckButtonCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWCheckButtonCtrl*) pControl;
}

VWCheckGroupBoxCtrl* VWDialog::GetCheckGroupBoxCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWCheckGroupBoxCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWCheckGroupBoxCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWCheckGroupBoxCtrl*) pControl;
}

VWColorButtonCtrl* VWDialog::GetColorButtonCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWColorButtonCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWColorButtonCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWColorButtonCtrl*) pControl;
}

VWEditIntegerCtrl* VWDialog::GetEditIntegerCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWEditIntegerCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWEditIntegerCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWEditIntegerCtrl*) pControl;
}

VWEditRealCtrl* VWDialog::GetEditRealCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWEditRealCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWEditRealCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWEditRealCtrl*) pControl;
}

VWEditTextCtrl* VWDialog::GetEditTextCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWEditTextCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWEditTextCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWEditTextCtrl*) pControl;
}

VWEditPasswordCtrl* VWDialog::GetEditPasswordCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWEditPasswordCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWEditPasswordCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWEditPasswordCtrl*) pControl;
}

VWSliderCtrl* VWDialog::GetSliderCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWSliderCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWSliderCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWSliderCtrl*) pControl;
}

VWColorPopupCtrl* VWDialog::GetColorPopupCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWColorPopupCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWColorPopupCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWColorPopupCtrl*) pControl;
}


VWColorPopupCustomCtrl* VWDialog::GetColorPopupCustomCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWColorPopupCustomCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWColorPopupCustomCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWColorPopupCustomCtrl*) pControl;
}

VWPatternPopupCtrl* VWDialog::GetPatternPopupCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWPatternPopupCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWPatternPopupCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWPatternPopupCtrl*) pControl;
}

VWLineAttributePopupCtrl* VWDialog::GetLineAttributePopupCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWLineAttributePopupCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWLineAttributePopupCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWLineAttributePopupCtrl*) pControl;
}

VWLineStylePopupCtrl* VWDialog::GetLineStylePopupCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWLineStylePopupCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWLineStylePopupCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWLineStylePopupCtrl*) pControl;
}

VWLineWeightPopupCtrl* VWDialog::GetLineWeightPopupCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWLineWeightPopupCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWLineWeightPopupCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWLineWeightPopupCtrl*) pControl;
}

VWListBrowserCtrl* VWDialog::GetListBrowserCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWListBrowserCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWListBrowserCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWListBrowserCtrl*) pControl;
}

VWTreeCtrl* VWDialog::GetTreeCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWTreeCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWTreeCtrl)( id );
	pControl->fpParentDlg	= this;
	pControl->AttachControl();
	this->AddControl( pControl, true );
	return (VWTreeCtrl*) pControl;
}

VWChooseClassPopupCtrl* VWDialog::GetChooseClassPopupCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWChooseClassPopupCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWChooseClassPopupCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWChooseClassPopupCtrl*) pControl;
}

VWChooseLayerPopupCtrl* VWDialog::GetChooseLayerPopupCtrlByID(TControlID id)
{
	VWControl*	pControl = this->GetControl(id);
	if (pControl)
		return dynamic_cast<VWChooseLayerPopupCtrl*>(pControl);
	pControl = NEW_OBJECT(VWChooseLayerPopupCtrl)(id);
	pControl->fpParentDlg = this;
	this->AddControl(pControl, true);
	return (VWChooseLayerPopupCtrl*)pControl;
}

VWImagePopupCtrl* VWDialog::GetImagePopupCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWImagePopupCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWImagePopupCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWImagePopupCtrl*) pControl;
}

VWStyleButtonCtrl* VWDialog::GetStyleButtonCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWStyleButtonCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWStyleButtonCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWStyleButtonCtrl*) pControl;
}

VWStyleGroupButtonCtrl* VWDialog::GetStyleGroupButtonCtrlByID(TControlID id)
{
	VWControl*	pControl	= this->GetControl( id );
	if ( pControl )
		return dynamic_cast<VWStyleGroupButtonCtrl*>( pControl );
	pControl				= NEW_OBJECT(VWStyleGroupButtonCtrl)( id );
	pControl->fpParentDlg	= this;
	this->AddControl( pControl, true );
	return (VWStyleGroupButtonCtrl*) pControl;
}


VWControl* VWDialog::GetControl(TControlID id)
{
	ASSERTN( kVStanev, fpArrControls );
	if ( fpArrControls == NULL )
		return NULL;
	TControlsArray&		arrControls		= * ((TControlsArray*) fpArrControls);

	size_t		len		= arrControls.size();
	for(size_t i=0; i<len; i++) {
		SChildControls&	child	= arrControls[ i ];
		if ( child.pControl->GetControlID() == id )
			return child.pControl;
	}
	return NULL;
}

void VWDialog::AddControl(VWControl* pControl, bool fake /*=false*/)
{
	ASSERTN( kVStanev, fpArrControls );
	if ( fpArrControls == NULL )
		return;
	TControlsArray&		arrControls		= * ((TControlsArray*) fpArrControls);

	ASSERTN( kVStanev, pControl );
	if ( pControl == NULL )
		return;

	VWControl*			pCtrl	= this->GetControl( pControl->GetControlID() );
	if ( pCtrl != NULL )
		return;

	SChildControls		child;
	child.bFake				= fake;
	child.pControl			= pControl;
	arrControls.push_back( child );
}

// tab pane managment
void VWDialog::AddTabPaneControl(VWTabPaneCtrl* pTabPane)
{
	ASSERTN( kVStanev, fpArrTabPanes );
	if ( fpArrTabPanes == NULL )
		return;
	TTabPanesArray&		arrPanes		= * ((TTabPanesArray*) fpArrTabPanes);

	pTabPane->fpParentDlg	= this;
	this->AddControl( pTabPane );
	arrPanes.push_back( pTabPane );
}

void VWDialog::SetSelectionSupport( VWSelectionSupport * pSelectionSupport )
{
	fpSelectionSupport = pSelectionSupport;
	fMapRadioControls.clear();
}

VWSelectionSupport	* VWDialog::GetSelectionSupport()
{
	return fpSelectionSupport;
}

void VWDialog::SetRadioButtonGroup( const TXString& fieldID, Sint32 groupID )
{	
	fMapRadioControls.insert( TRadioControl_Pair( fieldID, groupID ) );
}


bool VWDialog::IsComponentIndeterminate( TControlID controlID )
{
	bool bReturn = false;

	if ( fpSelectionSupport && fpArrDDXData != NULL) {
		
		TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);
		bool bFound = false;
		size_t	len	= arrDDX.size();

		for ( size_t i = 0;  i < len && bFound == false; i++ ) {
			SDDXData&	data	= arrDDX[ i ];

			if ( data.controlID == controlID ) {

				if ( fpSelectionSupport->KeyExists( data.key ) ) {
					bFound = true;
					bool bCheck = false;
					if ( fpSelectionSupport->IsDeterminate( data.key, bCheck, data.flag ) ) {
						if ( bCheck == false ) {
							bReturn = true;
						}
					}
				}
			}
		}


	}

	return bReturn;
}


bool VWDialog::IsComponentEdited( TControlID controlID )
{
	bool bReturn = true;

	if ( fpSelectionSupport && fpArrDDXData != NULL) {
		
		TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);
		bool bFound = false;
		size_t	len	= arrDDX.size();

		for ( size_t i = 0;  i < len && bFound == false; i++ ) {
			SDDXData&	data	= arrDDX[ i ];

			if ( data.controlID == controlID ) {

				if ( fpSelectionSupport->KeyExists( data.key ) ) {
					bFound = true;
					bool bCheck = false;
					if ( fpSelectionSupport->IsEdited( data.key, bCheck, data.flag ) ) {
						bReturn = bCheck;
					}
				}
			}
		}


	}

	return bReturn;
}


void VWDialog::UpdateSelectionInfo(TControlID controlID, VWDialogEventArgs& eventArg)
{
	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL || fpSelectionSupport == NULL )
		return;

	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	// find control in ddx array
	bool bFound = false;
	size_t foundID;

	size_t	len	= arrDDX.size();
	for ( size_t i = 0;  i < len && bFound == false; i++ ) {
		SDDXData&	data	= arrDDX[ i ];

		if ( data.controlID == controlID ) {

			if ( fpSelectionSupport->KeyExists( data.key ) ) {
				bFound = true;
				foundID = i;
			}
		}
	}

	if ( bFound ) {
		SDDXData& data = arrDDX[ foundID ];

		switch( data.type ) {
			case kDDXTypeEditReal:
			case kDDXTypeEditInteger:
			case kDDXTypeEditText:
			case kDDXTypeEditPassword:
			case kDDXTypeUnitEditText:{
				if ( eventArg.GetEventData() == kEditFieldEventType_TextChanged )  {
					fpSelectionSupport->SetEdited( data.key, true );
				}
			}	break;
			case kDDXTypeSearchEditBox: {
				if (eventArg.GetEventData() == kSearchEditFieldEventType_TextChanged) {
					fpSelectionSupport->SetEdited(data.key, true);
				}
			}	break;
			case kDDXTypeLineAttribPopup : {
				fpSelectionSupport->SetEdited( data.key, true );
				fpSelectionSupport->SetEdited( data.strData, true );
			}	break;
			

			case kDDXTypeRadioButton:
			case kDDXTypeRadioButtonBoolean:
			case kDDXTypeRadioGroupBox: {
				fpSelectionSupport->SetEdited( data.key, true );

				if ( fMapRadioControls.empty() == false ) {
					TRadioControl_Iterator iterBase = fMapRadioControls.find( data.key );
					if ( iterBase != fMapRadioControls.end() ) {
						Sint32 groupID = iterBase->second;

						TRadioControl_Iterator iter;
						for ( iter = fMapRadioControls.begin( ) ; iter != fMapRadioControls.end( ); iter++ ) {
							if ( iter->first != data.key && iter->second == groupID ) {
								if ( fpSelectionSupport->KeyExists( iter->first ) ) {
									fpSelectionSupport->SetEdited( iter->first, true );
								}
							}
						}


					}
				}
		
			} break;

			default: {
				fpSelectionSupport->SetEdited( data.key, true, data.flag );
				
			}	break;				

		}
	}

}


void VWDialog::UpdateData(bool bSafeToUI/*=false*/)
{
	this->UpdateDataInternal( bSafeToUI, TControlID(-1), false );
}

void VWDialog::UpdateDataForControl(bool bSafeToUI, TControlID id)
{
	this->UpdateDataInternal( bSafeToUI, id, false );
}

void VWDialog::UpdateDataAllExceptControl(bool bSafeToUI, TControlID id)
{
	this->UpdateDataInternal( bSafeToUI, id, true );
}

void VWDialog::UpdateDataInternal(bool bSafeToUI, TControlID id, bool onlyThisOne)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	size_t	len	= arrDDX.size();
	for(size_t i=0; i<len; i++) {
		SDDXData&	data	= arrDDX[ i ];

		if ( id != TControlID(-1) && onlyThisOne == false && id != data.controlID )
			continue; // we are not interested in this iteration
					  // as the requested control ID doesn't match

		if ( id != TControlID(-1) && onlyThisOne == true && id == data.controlID )
			continue; // we are not interested in this iteration
					  // as the requested control ID doesn't match

		bool bDeterminate = true;
		bool bEdited	  = true;

		if ( fpSelectionSupport != NULL &&  data.key.IsEmpty() == false ) {
			bool bCheck;

			if ( fpSelectionSupport->IsDeterminate( data.key, bCheck, data.flag ) ) {
				bDeterminate = bCheck;	
			}
			
			if ( fpSelectionSupport->IsEdited( data.key, bCheck, data.flag ) ) {
				bEdited = bCheck;
			}

			if ( data.type == kDDXTypeLineAttribPopup ) {
				if ( fpSelectionSupport->IsDeterminate( data.strData, bCheck ) ) {
					bDeterminate = bCheck && bDeterminate;	
				}

				if ( fpSelectionSupport->IsEdited( data.strData, bCheck ) ) {
					bEdited = bCheck && bEdited;
				}
			}


		}



		switch( data.type ) {
			case kDDXTypeStaticText: {
					VWStaticTextCtrl*		pCtrl	= this->GetStaticTextCtrlByID( data.controlID );
					TXString*				pData	= (TXString*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( bDeterminate || bEdited ) {
							pCtrl->SetControlText( *pData );
						}
						else {
							pCtrl->SetControlText( "" );
						}
					}
				} break;
			case kDDXTypeCheckButton: {
					VWCheckButtonCtrl*		pCtrl	= this->GetCheckButtonCtrByID( data.controlID );
					bool*					pData	= (bool*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SetThreeState( eCheckButtonCtrlState_Undetermined ) ;
						}
						else {
							pCtrl->SetState( *pData );
						}
					}

					if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData		= pCtrl->GetState();
					}
				} break;
				
			case kDDXTypeCheckButtonBoolean: {
					VWCheckButtonCtrl*		pCtrl	= this->GetCheckButtonCtrByID( data.controlID );
					Boolean*				pData	= (Boolean*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SetThreeState( eCheckButtonCtrlState_Undetermined ) ;
						}
						else {
							pCtrl->SetState( *pData );
						}
					}

					if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData		= pCtrl->GetState();
					}
				} break;
				
			case kDDXTypeCheckButtonTriState: {
					VWCheckButtonCtrl*		pCtrl	= this->GetCheckButtonCtrByID( data.controlID );
					short*					pData	= (short*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( (!bDeterminate && !bEdited) || *pData == -1 ) {
							pCtrl->SetThreeState( eCheckButtonCtrlState_Undetermined ) ;
						}
						else if ( *pData == 1 ) {
							pCtrl->SetThreeState( eCheckButtonCtrlState_Checked );
						}
						else  {
							pCtrl->SetThreeState( eCheckButtonCtrlState_Unchecked );
						}
					}

					if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						ECheckButtonCtrlState	state = pCtrl->GetThreeState();
						if ( eCheckButtonCtrlState_Unchecked		 == state ) *pData = 0;
						else if ( eCheckButtonCtrlState_Checked		 == state ) *pData = 1;
						else if ( eCheckButtonCtrlState_Undetermined == state ) *pData = -1;
					}
				} break;

			case kDDXTypeCheckGroupBox: {
					VWCheckGroupBoxCtrl*	pCtrl	= this->GetCheckGroupBoxCtrlByID( data.controlID );
					bool*					pData	= (bool*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							gSDK->SetThreeStateCheckBoxState( fControlID, data.controlID,eCheckButtonCtrlState_Undetermined );
						}
						else {
							pCtrl->SetState( *pData );
						}
					}

					if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData		= pCtrl->GetState();
					}
				} break;
			case kDDXTypeColorButton: {					
					VWColorButtonCtrl*		pCtrl	= this->GetColorButtonCtrlByID( data.controlID );
					RGBColor*				pData	= (RGBColor*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						DSTOPIF( bDeterminate == false,  ( kJWarshaw, "Color Button controls do not currenlty show an indeterminate state and are no longer recommended for use. Use a Color Popup instead.") );
						pCtrl->SetColor( *pData );
					}
					if ( pCtrl && pData && ! bSafeToUI )
						*pData		= pCtrl->GetColor();
				} break;
			case kDDXTypeEditInteger: {					
					VWEditIntegerCtrl*		pCtrl	= this->GetEditIntegerCtrlByID( data.controlID );
					Sint32*					pData	= (Sint32*) data.pData;
					
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SetControlText( "" );
						}
						else {
							pCtrl->SetEditInteger( *pData );
						}
					}
					if ( pCtrl && pData && ! bSafeToUI && bEdited )
						*pData		= pCtrl->GetEditInteger();
				} break;
			case kDDXTypeEditReal: {					
					VWEditRealCtrl*			pCtrl	= this->GetEditRealCtrlByID( data.controlID );
					double*					pData	= (double*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SetControlText( "" );

						}
						else {
							pCtrl->SetEditReal( *pData, (VWEditRealCtrl::EEditControlType) data.lData );
						}
					}
					
					if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData		= pCtrl->GetEditReal( (VWEditRealCtrl::EEditControlType) data.lData );
					}
				} break;
			case kDDXTypeEditText:
			case kDDXTypeSearchEditBox: {
					VWEditTextCtrl*			pCtrl	= this->GetEditTextCtrlByID( data.controlID );
					TXString*				pData	= (TXString*) data.pData;
					
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SetControlText( "" );
						}
						else {										
							pCtrl->SetText( *pData );
						}
					}
					if ( pCtrl && pData && ! bSafeToUI  && bEdited ) {
						*pData = pCtrl->GetText();
					}
				} break;
			case kDDXTypeEditPassword: {
					VWEditPasswordCtrl*		pCtrl	= this->GetEditPasswordCtrlByID( data.controlID );
					TXString*				pData	= (TXString*) data.pData;
					
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SetControlText( "" );
						}
						else {										
							pCtrl->SetText( *pData );
						}
					}
					if ( pCtrl && pData && ! bSafeToUI  && bEdited ) {
						*pData = pCtrl->GetText();
					}
				} break;
			case kDDXTypeUnitEditText: {
					VWEditTextCtrl*			pCtrl	= this->GetEditTextCtrlByID( data.controlID );
					double*					pData	= (double*) data.pData;
					
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SetControlText( "" );
						}
						else {
							TXString	txt;
							if ( data.fCallbackToTxt ) 	data.fCallbackToTxt( *pData, txt );
							else						txt.Format( "%f", *pData );

							pCtrl->SetText( txt );
						}
					}
					if ( pCtrl && pData && ! bSafeToUI  && bEdited ) {
						TXString	txt =  pCtrl->GetText( );

						if ( data.fCallbackToValue )	*pData = data.fCallbackToValue( txt );
						else							*pData = txt.atof();
					}
				} break;
			case kDDXTypeSlider: {
					VWSliderCtrl*			pCtrl	= this->GetSliderCtrlByID( data.controlID );
					Sint32*					pData	= (Sint32*) data.pData;
					if ( pCtrl && pData && bSafeToUI )
					{
						DSTOPIF( bDeterminate == false, ( kJWarshaw, "Slider controls do not currenlty show an indeterminate state." ) );
						pCtrl->SetSliderValue( *pData );
					}
					if ( pCtrl && pData && ! bSafeToUI )
						*pData		= pCtrl->GetSliderValue();
				} break;
			case kDDXTypeRadioButton: {					
					VWRadioButtonCtrl*		pCtrl	= this->GetRadioButtonCtrlByID( data.controlID );
					bool*					pData	= (bool*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SetState( false );
						}
						else {
							pCtrl->SetState( *pData );
						}
					}

					else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData		= pCtrl->GetState();
					}
				} break;

			case kDDXTypeRadioButtonBoolean: {					
					VWRadioButtonCtrl*		pCtrl	= this->GetRadioButtonCtrlByID( data.controlID );
					Boolean*				pData	= (Boolean*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SetState( false );
						}
						else {
							pCtrl->SetState( *pData );
						}
					}

					else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData		= pCtrl->GetState();
					}
				} break;

			case kDDXTypeRadioGroupBox: {					
					VWRadioGroupBoxCtrl*	pCtrl	= this->GetRadioGroupBoxCtrlByID( data.controlID );
					bool*					pData	= (bool*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
						}
						else {
							pCtrl->SetState( *pData );
						}
					}
					else if ( pCtrl && pData && ! bSafeToUI && bEdited  ) {
						*pData		= pCtrl->GetState();
					}
				} break;

			case kDDXTypePulldownMenuShort: {
					VWPullDownMenuCtrl*	pCtrl	= this->GetPullDownMenuCtrlByID( data.controlID );
					short*				pData	= (short*) data.pData;
					if ( pCtrl && pData && bSafeToUI )
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SelectIndex( -1 );
						}
						else {
							pCtrl->SelectIndex( *pData );
						}

					else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData	= (short)pCtrl->GetSelectedIndex();
					}
				} break;

			case kDDXTypePulldownMenuSizeT: {
					VWPullDownMenuCtrl*	pCtrl	= this->GetPullDownMenuCtrlByID( data.controlID );
					size_t*				pData	= (size_t*) data.pData;
					if ( pCtrl && pData && bSafeToUI )
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SelectIndex( -1 );
						}
						else {
							pCtrl->SelectIndex( *pData );
						}

					else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData	= pCtrl->GetSelectedIndex();
					}
				} break;

			case kDDXTypePulldownMenuTXString: {
					VWPullDownMenuCtrl*	pCtrl	= this->GetPullDownMenuCtrlByID( data.controlID );
					TXString*			pData	= (TXString*) data.pData;
					if ( pCtrl && pData && bSafeToUI )
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SelectIndex( -1 );
						}
						else {
							pCtrl->SelectItem( *pData );
						}

					else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData	= pCtrl->GetSelectedItem();
					}
				} break;

			case kDDXTypePulldownMenuMarker: {
					VWPullDownMenuCtrl*	pCtrl	= this->GetPullDownMenuCtrlByID( data.controlID );
					Sint32*				pData	= (Sint32*) data.pData;
					if ( pCtrl && pData && bSafeToUI )
						if ( !bDeterminate && !bEdited ) {
							pCtrl->SelectIndex( -1 );
						}
						else {
							pCtrl->SelectItemWithMarker( *pData );
						}

					else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData	= pCtrl->GetSelectedItemMarker();
					}
				} break;

			case kDDXTypeListBoxShort: {
					VWListBoxCtrl*		pCtrl	= this->GetListBoxCtrlByID( data.controlID );
					short*				pData	= (short*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->DeselectAll();
						}
						else {
							pCtrl->SelectIndex( *pData );
						}
					}

					else if ( pCtrl && pData && ! bSafeToUI  && bEdited ) {
						*pData	= (short)pCtrl->GetSelectedIndex();
					}

				} break;

			case kDDXTypeListBoxSizeT: {
					VWListBoxCtrl*		pCtrl	= this->GetListBoxCtrlByID( data.controlID );
					size_t*				pData	= (size_t*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							pCtrl->DeselectAll();
						}
						else {
							pCtrl->SelectIndex( *pData );
						}
					}

					else if ( pCtrl && pData && ! bSafeToUI  && bEdited ) {
						*pData	= pCtrl->GetSelectedIndex();
					}

				} break;

			case kDDXTypeColorPopup: {
				const RGBColor		kRGBWhite	= { 0xFFFF, 0xFFFF, 0xFFFF };
				const RGBColor		kRGBBlack	= { 0x0000, 0x0000, 0x0000 };
				bool		bReverseBlackAndWhite	= false;
				if ( data.lData != 0 ) {
					::GS_GetProgramVariable( gCBP, varBlackBackground, & bReverseBlackAndWhite );
				}
				
				VWColorPopupCtrl*	pCtrl		= this->GetColorPopupCtrlByID( data.controlID );
				RGBColor*			pData		= (RGBColor*) data.pData;
				if ( pCtrl && pData && bSafeToUI ) {
					if ( !bDeterminate && !bEdited ) {
						gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
					}
					else {
						RGBColor	color					= *pData;
						if ( bReverseBlackAndWhite ) {
							if ( color.red == kRGBBlack.red && color.green == kRGBBlack.green && color.blue == kRGBBlack.blue )
								color		= kRGBWhite;
							else if ( color.red == kRGBWhite.red && color.green == kRGBWhite.green && color.blue == kRGBWhite.blue )
								color		= kRGBBlack;
						}
					
						pCtrl->SetSelectedColor( color );
					}
				}
				else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
					*pData		= pCtrl->GetSelectedColor();
					if ( bEdited && bDeterminate == false ) {
						gSDK->SetComponentIndeterminate( fControlID, data.controlID, false );
						*pData		= pCtrl->GetSelectedColor();
					}
					
					if ( bReverseBlackAndWhite ) {
						if ( (*pData).red == kRGBBlack.red && (*pData).green == kRGBBlack.green && (*pData).blue == kRGBBlack.blue )
							*pData		= kRGBWhite;
						else if ( (*pData).red == kRGBWhite.red && (*pData).green == kRGBWhite.green && (*pData).blue == kRGBWhite.blue )
							*pData		= kRGBBlack;
					}

				}
			} break;
				
			case kDDXTypeColorPopupCustom: {
					VWColorPopupCustomCtrl*	pCtrl	= this->GetColorPopupCustomCtrlByID( data.controlID );
					ColorRef*				pData	= (ColorRef*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
						}
						else {
							pCtrl->SetSelectedColor( *pData );
						}
					}
					else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData		= pCtrl->GetSelectedColor();
						if ( bEdited && bDeterminate == false ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, false );
							*pData		= pCtrl->GetSelectedColor();
						}
					}

			} break;

			case kDDXTypePatternPopup: {
					VWPatternPopupCtrl*	pCtrl	= this->GetPatternPopupCtrlByID( data.controlID );
					short*				pData	= (short*) data.pData;
					RGBColor*			pData1	= (RGBColor*) data.pData1; 
					RGBColor*			pData2	= (RGBColor*) data.pData2;	
					if ( pCtrl && pData && pData1 && pData2 && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
						}
						else {
							pCtrl->SetSelectedPattern( *pData, *pData1, *pData2 );
						}
					}
					else if ( pCtrl && pData && pData1 && pData2 && ! bSafeToUI && bEdited ) {
						pCtrl->GetSelectedPattern( *pData, *pData1, *pData2 );
						if ( bEdited && bDeterminate == false ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, false );
							pCtrl->GetSelectedPattern( *pData, *pData1, *pData2 );
						}
					}
				} break;

			case kDDXTypeLineAttribPopup: {
					VWLineAttributePopupCtrl*	pCtrl	= this->GetLineAttributePopupCtrlByID( data.controlID );
					InternalIndex*				pData	= (InternalIndex*) data.pData;
					short*						pData1	= (short*) data.pData1;
					if ( pCtrl && pData && pData1 && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
						}
						else {
							pCtrl->SetSelectedLineTypeAttribute( *pData, *pData1 );
						}
					}
					else if ( pCtrl && pData && pData1 && ! bSafeToUI && bEdited ) {
						pCtrl->GetSelectedLineTypeAttribute( *pData, *pData1 );
						if ( bEdited && bDeterminate == false ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, false );
							pCtrl->SetSelectedLineTypeAttribute( *pData, *pData1 );
						}
					}
				} break;

			case kDDXTypeLineStylePopup: {
					VWLineStylePopupCtrl*	pCtrl	= this->GetLineStylePopupCtrlByID( data.controlID );
					InternalIndex*			pData	= (InternalIndex*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
						}
						else {
							pCtrl->SetSelectedLineType( *pData );
						}
					}
					else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData		= pCtrl->GetSelectedLineType();
						if ( bEdited && bDeterminate == false ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, false );
							pCtrl->SetSelectedLineType( *pData );
						}
					}

				} break;

			case kDDXTypeLineWeightPopup: {
					VWLineWeightPopupCtrl*	pCtrl	= this->GetLineWeightPopupCtrlByID( data.controlID );
					short*					pData	= (short*) data.pData;
					if ( pCtrl && pData && bSafeToUI ) {
						if ( !bDeterminate && !bEdited ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
						}
						else {
							pCtrl->SetSelectedLineWeight( *pData );
						}
					}
					else if ( pCtrl && pData && ! bSafeToUI && bEdited ) {
						*pData		= pCtrl->GetSelectedLineWeight();
						if ( bEdited && bDeterminate == false ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, false );
							pCtrl->SetSelectedLineWeight( *pData );
						}
					}

				} break;

			case kDDXTypeMarkerPopup:{
					VWMarkerPopupCtrl*		pCtrl	= this->GetMarkerPopupCtrlByID( data.controlID );
					SMarkerStyle*			pValue	= (SMarkerStyle*) data.pData;
					if ( pCtrl && pValue && bSafeToUI  ) {
						if ( !bDeterminate && !bEdited ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
						}
						else {
							pCtrl->SetSelectedItem( *pValue );
						}
					}
					else if ( pCtrl && pValue && ! bSafeToUI && bEdited ) {
						pCtrl->GetSelectedItem( *pValue );
						if ( bEdited && bDeterminate == false ) {
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, false );
							pCtrl->SetSelectedItem( *pValue );
						}

					}
				} break;

			case kDDXTypeChooseClassPopupShort: {
					VWChooseClassPopupCtrl*	pCtrl		= this->GetChooseClassPopupCtrlByID( data.controlID );
					TXString *				pValue  	= (TXString*) data.pData;
					short *					pSelected	= (short*) data.pData1;
					if ( pCtrl && pValue && pSelected ) {
						if ( bSafeToUI ) {
							if ( bDeterminate || bEdited ) {

								if ( -1 == *pSelected ) {
#if _MINICAD_
									// not implemented -- let Vlado know if you want it
									pCtrl->SetSelectedClass( * pValue );
#else
									TXString userClass = VWFC::Tools::VWAutoClassing::GetUserClass( *pValue );
									pCtrl->SetSelectedClass( userClass );
#endif
									*pSelected = (short)pCtrl->GetSelectedIndex();
								}
								else {
									pCtrl->SelectIndex( *pSelected );
									pCtrl->GetSelectedClass( *pValue );
								}
							}
							else {

								gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
							}
						}
						
						else if ( bEdited ) {
							TXString strUserClassName;
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, false );
							*pSelected = (short)pCtrl->GetSelectedIndex();
							pCtrl->GetSelectedClass(strUserClassName);

#if _MINICAD_
							*pValue = strUserClassName;
#else
							*pValue	= VWFC::Tools::VWAutoClassing::GetRefClass( strUserClassName );
#endif
						}
					}
				} break;

			case kDDXTypeChooseClassPopupSizeT: {
					VWChooseClassPopupCtrl*	pCtrl		= this->GetChooseClassPopupCtrlByID( data.controlID );
					TXString *				pValue  	= (TXString*) data.pData;
					size_t *				pSelected	= (size_t*) data.pData1;
					if ( pCtrl && pValue && pSelected ) {
						if ( bSafeToUI ) {
							if ( bDeterminate || bEdited ) {

								if ( -1 == *pSelected ) {
#if _MINICAD_
									// not implemented -- let Vlado know if you want it
									pCtrl->SetSelectedClass( * pValue );
#else
									TXString userClass = VWFC::Tools::VWAutoClassing::GetUserClass( *pValue );
									pCtrl->SetSelectedClass( userClass );
#endif
									*pSelected = pCtrl->GetSelectedIndex();
								}
								else {
									pCtrl->SelectIndex( *pSelected );
									pCtrl->GetSelectedClass( *pValue );
								}
							}
							else {

								gSDK->SetComponentIndeterminate( fControlID, data.controlID, true );
							}
						}
						
						else if ( bEdited ) {
                            TXString strUserClassName;
							gSDK->SetComponentIndeterminate( fControlID, data.controlID, false );
							*pSelected = pCtrl->GetSelectedIndex();
                            pCtrl->GetSelectedClass(strUserClassName);
#if _MINICAD_
							*pValue = strUserClassName;
#else
							*pValue	= VWFC::Tools::VWAutoClassing::GetRefClass( strUserClassName );
#endif
						}
					}
				} break;

			case kDDXTypeChooseLayerPopupShort: {
				VWChooseLayerPopupCtrl*	pCtrl = this->GetChooseLayerPopupCtrlByID(data.controlID);
				TXString *				pValue = (TXString*)data.pData;
				short *					pSelected = (short*)data.pData1;
				if (pCtrl && pValue && pSelected) {
					if (bSafeToUI) {
						if (bDeterminate || bEdited) {

							if (-1 == *pSelected) {
								pCtrl->SetSelectedLayer(*pValue);
								*pSelected = pCtrl->GetSelectedIndex();
							}
							else {
								pCtrl->SelectIndex(*pSelected);
								pCtrl->GetSelectedLayer(*pValue);
							}
						}
						else {
							gSDK->SetComponentIndeterminate(fControlID, data.controlID, true);
						}
					}

					else if (bEdited) {
						gSDK->SetComponentIndeterminate(fControlID, data.controlID, false);
						*pSelected = pCtrl->GetSelectedIndex();
						pCtrl->GetSelectedLayer(*pValue);
					}
				}
			} break;
		}
	}
}

void VWDialog::ClearDDX()
{
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);
	arrDDX.clear();
}


void VWDialog::AddDDX_StaticText(TControlID controlID, TXString* pValue, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pValue );
	SDDXData		data;
	data.type				= kDDXTypeStaticText;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_CheckButton(TControlID controlID, bool* pCheckState, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckState );
	SDDXData		data;
	data.type				= kDDXTypeCheckButton;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckState;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_CheckButton(TControlID controlID, Boolean* pCheckState, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckState );
	SDDXData		data;
	data.type				= kDDXTypeCheckButtonBoolean;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckState;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_CheckButton(TControlID controlID, short* pCheckTriState, const  TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckTriState );
	SDDXData		data;
	data.type				= kDDXTypeCheckButtonTriState;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckTriState;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_CheckGroupBox(TControlID controlID, bool* pCheckState, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckState );
	SDDXData		data;
	data.type				= kDDXTypeCheckGroupBox;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckState;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_ColorButton(TControlID controlID, RGBColor* pSelectedColor, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pSelectedColor );
	SDDXData		data;
	data.type				= kDDXTypeColorButton;
	data.controlID			= controlID;
	data.pData				= (void*) pSelectedColor;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_EditInteger(TControlID controlID, Sint32* pValue, const TXString& key )
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pValue );
	SDDXData		data;
	data.type				= kDDXTypeEditInteger;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_EditReal(TControlID controlID, double* pValue, VWEditRealCtrl::EEditControlType editType, const TXString& key )
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pValue );
	SDDXData		data;
	data.type				= kDDXTypeEditReal;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.lData				= (Sint32) editType;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_EditText(TControlID controlID, TXString* pValue, const TXString& key )
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pValue );
	SDDXData		data;
	data.type				= kDDXTypeEditText;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.lData				= 0;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_EditPassword(TControlID controlID, TXString* pValue, const TXString& key )
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pValue );
	SDDXData		data;
	data.type				= kDDXTypeEditPassword;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.lData				= 0;
	data.key				= key;
	arrDDX.push_back( data );
}
void VWDialog::AddDDX_SearchEditBox(TControlID controlID, TXString* pValue, const TXString& key)
{
	ASSERTN(kVStanev, fpArrDDXData);
	if (fpArrDDXData == NULL)
		return;
	TDDXDataArray&		arrDDX = *((TDDXDataArray*)fpArrDDXData);

	ASSERTN(kVStanev, pValue);
	SDDXData		data;
	data.type 		= kDDXTypeSearchEditBox;
	data.controlID 	= controlID;
	data.pData 		= (void*)pValue;
	data.lData 		= 0;
	data.key 		= key;
	arrDDX.push_back(data);
}

void VWDialog::AddDDX_UnitEditText(TControlID controlID, double* pValue, std::function<void(double value,TXString& out)> callbackToTxt, std::function<double(const TXString& value)> callbackToValue, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pValue );
	SDDXData		data;
	data.type				= kDDXTypeUnitEditText;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.lData				= 0;
	data.key				= key;
	data.fCallbackToTxt		= callbackToTxt;
	data.fCallbackToValue	= callbackToValue;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_Slider(TControlID controlID, Sint32* pPosition, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pPosition );
	SDDXData		data;
	data.type				= kDDXTypeSlider;
	data.controlID			= controlID;
	data.pData				= (void*) pPosition;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_RadioButton(TControlID controlID, bool* pCheckState, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckState );
	SDDXData		data;
	data.type				= kDDXTypeRadioButton;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckState;
	data.key				= key;
	arrDDX.push_back( data );
}


void VWDialog::AddDDX_RadioButton(TControlID controlID, Boolean* pCheckState, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckState );
	SDDXData		data;
	data.type				= kDDXTypeRadioButtonBoolean;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckState;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_RadioGroupBox(TControlID controlID, bool* pCheckState, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckState );
	SDDXData		data;
	data.type				= kDDXTypeRadioGroupBox;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckState;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_PulldownMenu(TControlID controlID, short* pSelected, const TXString& key )
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pSelected );
	SDDXData		data;
	data.type				= kDDXTypePulldownMenuShort;
	data.controlID			= controlID;
	data.pData				= (void*) pSelected;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_PulldownMenu(TControlID controlID, size_t* pSelected, const TXString& key )
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pSelected );
	SDDXData		data;
	data.type				= kDDXTypePulldownMenuSizeT;
	data.controlID			= controlID;
	data.pData				= (void*) pSelected;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_PulldownMenu(TControlID controlID, TXString* pSelected, const TXString& key )
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pSelected );
	SDDXData		data;
	data.type				= kDDXTypePulldownMenuTXString;
	data.controlID			= controlID;
	data.pData				= (void*) pSelected;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_PulldownMenu(TControlID controlID, Sint32* pMarker, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pMarker );
	SDDXData		data;
	data.type				= kDDXTypePulldownMenuMarker;
	data.controlID			= controlID;
	data.pData				= (void*) pMarker;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_ListBox(TControlID controlID, short* pSelected, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pSelected );
	SDDXData		data;
	data.type				= kDDXTypeListBoxShort;
	data.controlID			= controlID;
	data.pData				= (void*) pSelected;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_ListBox(TControlID controlID, size_t* pSelected, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pSelected );
	SDDXData		data;
	data.type				= kDDXTypeListBoxSizeT;
	data.controlID			= controlID;
	data.pData				= (void*) pSelected;
	data.key				= key;
	arrDDX.push_back( data );
}
void VWDialog::AddDDX_ColorPopup(TControlID controlID, RGBColor* pSelectedColor, bool bMatchBlackBkgr /*=true*/, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pSelectedColor );
	SDDXData		data;
	data.type				= kDDXTypeColorPopup;
	data.controlID			= controlID;
	data.pData				= (void*) pSelectedColor;
	data.lData				= bMatchBlackBkgr ? 1 : 0;
	data.key				= key;
	arrDDX.push_back( data );
}



void VWDialog::AddDDX_ColorPopupCustom(TControlID controlID, ColorRef* pSelectedColor, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pSelectedColor );
	SDDXData		data;
	data.type				= kDDXTypeColorPopupCustom;
	data.controlID			= controlID;
	data.pData				= (void*) pSelectedColor;
	data.key				= key;
	arrDDX.push_back( data );
}


void VWDialog::AddDDX_PatternPopup(TControlID controlID, short* pPatternIndex, RGBColor* pForeColor, RGBColor* pBackColor, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pPatternIndex );
	ASSERTN( kVStanev, pForeColor );
	ASSERTN( kVStanev, pBackColor );
	SDDXData		data;
	data.type				= kDDXTypePatternPopup;
	data.controlID			= controlID;
	data.pData				= (void*) pPatternIndex;
	data.pData1				= (void*) pForeColor;
	data.pData2				= (void*) pBackColor;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_LineAttribsPopup(TControlID controlID, InternalIndex* pLineStyle, short* pLineWeight )
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pLineStyle );
	ASSERTN( kVStanev, pLineWeight );
	SDDXData		data;
	data.type				= kDDXTypeLineAttribPopup;
	data.controlID			= controlID;
	data.pData				= (void*) pLineStyle;
	data.pData1				= (void*) pLineWeight;
	data.key				= "";
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_LineAttribsPopup(TControlID controlID, InternalIndex* pLineStyle, short* pLineWeight, const TXString& keyStyle, const TXString& keyWeight )
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pLineStyle );
	ASSERTN( kVStanev, pLineWeight );
	SDDXData		data;
	data.type				= kDDXTypeLineAttribPopup;
	data.controlID			= controlID;
	data.pData				= (void*) pLineStyle;
	data.pData1				= (void*) pLineWeight;
	data.key				= keyStyle;
	data.strData			= keyWeight;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_LineStylePopup(TControlID controlID, InternalIndex* pLineStyle, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pLineStyle );
	SDDXData		data;
	data.type				= kDDXTypeLineStylePopup;
	data.controlID			= controlID;
	data.pData				= (void*) pLineStyle;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_LineWeightPopup(TControlID controlID, short* pLineWeight, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pLineWeight );
	SDDXData		data;
	data.type				= kDDXTypeLineWeightPopup;
	data.controlID			= controlID;
	data.pData				= (void*) pLineWeight;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_MarkerPopup(TControlID controlID, SMarkerStyle* pValue, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pValue );
	SDDXData		data;
	data.type				= kDDXTypeMarkerPopup;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.key				= key;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, short* pSelected)
{
	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kJWarshaw, pValue );
	SDDXData		data;
	data.type				= kDDXTypeChooseClassPopupShort;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.pData1				= (void*) pSelected;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, short* pSelected, const TXString& standardClass)
{
	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kJWarshaw, pValue );
	SDDXData		data;
	data.type				= kDDXTypeChooseClassPopupShort;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.pData1				= (void*) pSelected;
	data.strData			= standardClass;
	arrDDX.push_back( data );

	// add the standard class to the popup
	VWChooseClassPopupCtrl*		thePopup	= this->GetChooseClassPopupCtrlByID( controlID );
	if ( thePopup ) {
#if _MINICAD_
		DSTOP((kVStanev, "Let Vlado know that you need this functionality in the core"));
#else
		TXString	userClass	= VWFC::Tools::VWAutoClassing::GetUserClass( standardClass );
		thePopup->InsertProposedClass( userClass );
#endif
	}
}

void VWDialog::AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, short* pSelected, const TXString& standardClass, const TXStringArray& arrAdditionalItems )
{
	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kJWarshaw, pValue );
	SDDXData		data;
	data.type				= kDDXTypeChooseClassPopupShort;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.pData1				= (void*) pSelected;
	data.strData			= standardClass;
	arrDDX.push_back( data );

	// add the additional items and the standard class to the popup
	VWChooseClassPopupCtrl*		thePopup	= this->GetChooseClassPopupCtrlByID( controlID );
	if ( thePopup ) {
		size_t	itemsCnt	= arrAdditionalItems.GetSize();
		for(size_t i=0; i<itemsCnt; i++) {
			const TXString& item	= arrAdditionalItems.GetAt( i );
			thePopup->InsertProposedClass( item );
		}

#if _MINICAD_
		DSTOP((kVStanev, "Let Vlado know that you need this functionality in the core"));
#else
		TXString	userClass	= VWFC::Tools::VWAutoClassing::GetUserClass( standardClass );
		thePopup->InsertProposedClass( userClass );
#endif
	}
}

void VWDialog::AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, short* pSelected, const TXStringArray& arrAdditionalItems )
{
	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kJWarshaw, pValue );
	SDDXData		data;
	data.type				= kDDXTypeChooseClassPopupShort;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.pData1				= (void*) pSelected;
	arrDDX.push_back( data );

	// add the additional items to the popup
	VWChooseClassPopupCtrl*		thePopup	= this->GetChooseClassPopupCtrlByID( controlID );
	if ( thePopup ) {
		size_t	itemsCnt	= arrAdditionalItems.GetSize();
		for(size_t i=0; i<itemsCnt; i++) {
			const TXString& item	= arrAdditionalItems.GetAt( i );
			thePopup->InsertProposedClass( item );
		}
	}
}

void VWDialog::AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, size_t* pSelected)
{
	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kJWarshaw, pValue );
	SDDXData		data;
	data.type				= kDDXTypeChooseClassPopupSizeT;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.pData1				= (void*) pSelected;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, size_t* pSelected, const TXString& standardClass)
{
	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kJWarshaw, pValue );
	SDDXData		data;
	data.type				= kDDXTypeChooseClassPopupSizeT;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.pData1				= (void*) pSelected;
	data.strData			= standardClass;
	arrDDX.push_back( data );

	// add the standard class to the popup
	VWChooseClassPopupCtrl*		thePopup	= this->GetChooseClassPopupCtrlByID( controlID );
	if ( thePopup ) {
#if _MINICAD_
		DSTOP((kVStanev, "Let Vlado know that you need this functionality in the core"));
#else
		TXString	userClass	= VWFC::Tools::VWAutoClassing::GetUserClass( standardClass );
		thePopup->InsertProposedClass( userClass );
#endif
	}
}

void VWDialog::AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, size_t* pSelected, const TXString& standardClass, const TXStringArray& arrAdditionalItems )
{
	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kJWarshaw, pValue );
	SDDXData		data;
	data.type				= kDDXTypeChooseClassPopupSizeT;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.pData1				= (void*) pSelected;
	data.strData			= standardClass;
	arrDDX.push_back( data );

	// add the additional items and the standard class to the popup
	VWChooseClassPopupCtrl*		thePopup	= this->GetChooseClassPopupCtrlByID( controlID );
	if ( thePopup ) {
		size_t	itemsCnt	= arrAdditionalItems.GetSize();
		for(size_t i=0; i<itemsCnt; i++) {
			const TXString& item	= arrAdditionalItems.GetAt( i );
			thePopup->InsertProposedClass( item );
		}

#if _MINICAD_
		DSTOP((kVStanev, "Let Vlado know that you need this functionality in the core"));
#else
		TXString	userClass	= VWFC::Tools::VWAutoClassing::GetUserClass( standardClass );
		thePopup->InsertProposedClass( userClass );
#endif
	}
}

void VWDialog::AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, size_t* pSelected, const TXStringArray& arrAdditionalItems )
{
	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kJWarshaw, pValue );
	SDDXData		data;
	data.type				= kDDXTypeChooseClassPopupSizeT;
	data.controlID			= controlID;
	data.pData				= (void*) pValue;
	data.pData1				= (void*) pSelected;
	arrDDX.push_back( data );

	// add the additional items to the popup
	VWChooseClassPopupCtrl*		thePopup	= this->GetChooseClassPopupCtrlByID( controlID );
	if ( thePopup ) {
		size_t	itemsCnt	= arrAdditionalItems.GetSize();
		for(size_t i=0; i<itemsCnt; i++) {
			const TXString& item	= arrAdditionalItems.GetAt( i );
			thePopup->InsertProposedClass( item );
		}
	}
}

void VWDialog::AddDDX_ChooseLayerPopup(TControlID controlID, TXString* pValue, short* pSelected)
{
	ASSERTN(kILane, fpArrDDXData);
	if (fpArrDDXData == NULL)
		return;
	TDDXDataArray&		arrDDX = *((TDDXDataArray*)fpArrDDXData);

	ASSERTN(kILane, pValue);
	SDDXData		data;
	data.type = kDDXTypeChooseLayerPopupShort;
	data.controlID = controlID;
	data.pData = (void*)pValue;
	data.pData1 = (void*)pSelected;
	arrDDX.push_back(data);
}

void VWDialog::AddDDX_ChooseLayerPopup(TControlID controlID, TXString* pValue, short* pSelected, const TXStringArray& arrAdditionalItems)
{
	ASSERTN(kILane, fpArrDDXData);
	if (fpArrDDXData == NULL)
		return;
	TDDXDataArray&		arrDDX = *((TDDXDataArray*)fpArrDDXData);

	ASSERTN(kILane, pValue);
	SDDXData		data;
	data.type = kDDXTypeChooseLayerPopupShort;
	data.controlID = controlID;
	data.pData = (void*)pValue;
	data.pData1 = (void*)pSelected;
	arrDDX.push_back(data);

	// add the additional items to the popup
	VWChooseLayerPopupCtrl*		thePopup = this->GetChooseLayerPopupCtrlByID(controlID);
	if (thePopup) {
		size_t	itemsCnt = arrAdditionalItems.GetSize();
		for (size_t i = 0; i < itemsCnt; i++) {
			const TXString& item = arrAdditionalItems.GetAt(i);
			thePopup->InsertProposedLayer(item);
		}
	}
}

void VWDialog::AddDDX_CheckButton(TControlID controlID, bool* pCheckState, TValueFlags flag, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckState );
	SDDXData		data;
	data.type				= kDDXTypeCheckButton;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckState;
	data.key				= key;
	data.flag				= flag;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_CheckButton(TControlID controlID, Boolean* pCheckState, TValueFlags flag, const  TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckState );
	SDDXData		data;
	data.type				= kDDXTypeCheckButtonBoolean;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckState;
	data.key				= key;
	data.flag				= flag;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_CheckButton(TControlID controlID, short* pCheckTriState, TValueFlags flag, const  TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckTriState );
	SDDXData		data;
	data.type				= kDDXTypeCheckButtonTriState;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckTriState;
	data.key				= key;
	data.flag				= flag;
	arrDDX.push_back( data );
}

void VWDialog::AddDDX_CheckGroupBox(TControlID controlID, bool* pCheckState, TValueFlags flag, const TXString& key)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return;
	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	ASSERTN( kVStanev, pCheckState );
	SDDXData		data;
	data.type				= kDDXTypeCheckGroupBox;
	data.controlID			= controlID;
	data.pData				= (void*) pCheckState;
	data.key				= key;
	data.flag				= flag;
	arrDDX.push_back( data );
}

bool VWDialog::SetMultipleSelectionKey( TControlID controlID, const TXString& key )
{
	bool bReturn = true;

	ASSERTN( kJWarshaw, fpArrDDXData );
	if ( fpArrDDXData == NULL ) {
		bReturn = false;
	}

	if ( fpSelectionSupport == NULL ) {
		bReturn = false;
	}

	if ( key.IsEmpty() ) {
		bReturn = false;
	}

	if ( bReturn ) {
		TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);
	
		// find control in ddx array
		bool bFound = false;
		size_t foundID;

		size_t	len	= arrDDX.size();
		for ( size_t i = 0;  i < len && bFound == false; i++ ) {
			SDDXData&	data	= arrDDX[ i ];

			if ( data.controlID == controlID ) {

				if ( fpSelectionSupport->KeyExists( key ) ) {
					bFound = true;
					foundID = i;
				}
			}
		}

		if ( bFound ) {
			SDDXData& data = arrDDX[ foundID ];
			data.key = key;
		}
		else {
			bReturn = false;
		}

	}

	return bReturn;
}

bool VWDialog::SetDDXControlValue(TControlID controlID, const TXString& value)
{
	ASSERTN( kAValchev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return false;

	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	bool	ok	= false;
	size_t	len	= arrDDX.size();
	for(size_t i=0; i<len; i++) {
		SDDXData&	data	= arrDDX[ i ];
		if ( data.controlID == controlID ) {
			switch( data.type ) {

				case kDDXTypeEditInteger: {
						if ( TXStringExt::IsDigit( value ) ) {
							Sint32*		pData	= (Sint32*) data.pData;
							*pData				= value.atoi();
							ok					= true;
						}
					} break;
				case kDDXTypeEditReal: {
						if ( TXStringExt::IsDigit( value ) ) {
							double*		pData	= (double*) data.pData;
							*pData				= value.atof();
							ok					= true;
						}
					} break;
				case kDDXTypeEditText:
				case kDDXTypeEditPassword:
				case kDDXTypeSearchEditBox: {
						TXString*	pData	= (TXString*) data.pData;
						*pData				= value;
						ok					= true;
					} break;

				case kDDXTypeUnitEditText: {
						double*		pData	= (double*) data.pData;
						if ( data.fCallbackToValue )	*pData = data.fCallbackToValue( value );
						else							*pData = value.atof();
						ok					= true;
					} break;

				default:
					break;
			}
		}

		if ( ok ) {
			break;
		}
	}

	return ok;
}

bool VWDialog::GetDDXControlValue(TControlID controlID, TXString& outValue)
{
	ASSERTN( kVStanev, fpArrDDXData );
	if ( fpArrDDXData == NULL )
		return false;

	TDDXDataArray&		arrDDX			= * ((TDDXDataArray*) fpArrDDXData);

	bool	ok	= false;
	size_t	len	= arrDDX.size();
	for(size_t i=0; i<len; i++) {
		SDDXData&	data	= arrDDX[ i ];
		if ( data.controlID == controlID ) {
			switch( data.type ) {

				case kDDXTypeEditInteger: {					
						Sint32*		pData	= (Sint32*) data.pData;
						outValue.Format( "%d", *pData );
						ok					= true;
					} break;
				case kDDXTypeEditReal: {					
						double*		pData	= (double*) data.pData;
						outValue.Format( "%f", *pData );
						ok					= true;
					} break;
				case kDDXTypeEditText:
				case kDDXTypeEditPassword:
				case kDDXTypeSearchEditBox: {
						TXString*	pData	= (TXString*) data.pData;
						outValue			= *pData;
						ok					= true;
					} break;

				case kDDXTypeUnitEditText: {
						double*		pData	= (double*) data.pData;
						if ( data.fCallbackToTxt ) 	data.fCallbackToTxt( *pData, outValue );
						else						outValue.Format( "%f", *pData );
						ok					= true;
					} break;

/*				case kDDXTypePulldownMenu: {
						VWPullDownMenuCtrl*	pCtrl	= this->GetPullDownMenuCtrlByID( data.controlID );
						short*				pData	= (short*) data.pData;
						if ( pCtrl && pData && bSafeToUI )
							pCtrl->SelectIndex( *pData );
						else if ( pCtrl && pData && ! bSafeToUI )
							*pData	= pCtrl->GetSelectedIndex();
					} break;*/

				default:
					break;
			}
		}

		if ( ok ) {
			break;
		}
	}

	return ok;
}

// ---------------------------------------------------------------------------------------------------
// tools

// Displays an alert dialog that informs the user of a serious problem
// that requires intervention or correction before work can continue.
/*static*/ void VWDialog::AlertCritical(const TXString& text, const TXString& advice)
{
	::GS_AlertCritical( gCBP, text, advice );
}

// Displays a dialog which informs the user about the result of a command.
// Offers no user choices; the user acknowledges the message by clicking the OK button.
/*static*/ void VWDialog::AlertInform(const TXString& text, const TXString& advice, bool bMinorAlert)
{
	::GS_AlertInform( gCBP, text, advice, bMinorAlert );
}

// Displays a dialog that alerts the user to a condition
// or situation that requires the user's decision and input before preceeding,
// such as an impending action with potentially destructive or irreversible consequencies. 
/*static*/ EDialogButton VWDialog::AlertQuestion(	const TXString& question,
													const TXString& advice,
													EDialogButton defaultButton,
													const TXString& strOkText,
													const TXString& strCancelText,
													const TXString& strCustomButtonAText,
													const TXString& strCustomButtonBText )
{
	// Specifies which button is to be made the default 
	//		0: the negative button is the default
	//		1: the positive button is the default
	//		2: custom button A is the default
	//		3: custom button B is the default
	short			defButton	= 0;
	switch( defaultButton ) {
		case kDialogButton_Cancel:		defButton = 0;	break;
		case kDialogButton_Ok:			defButton = 1;	break;
		case kDialogButton_CustomA:		defButton = 2;	break;
		case kDialogButton_CustomB:		defButton = 3;	break;
		default:
			break;
	}

	short			res		= ::GS_AlertQuestion( gCBP, question, advice, defButton, strOkText, strCancelText, strCustomButtonAText, strCustomButtonBText );
	EDialogButton	result	= kDialogButton_None;
	switch( res ) {
		case 0:	result = kDialogButton_Cancel;	break;
		case 1:	result = kDialogButton_Ok;		break;
		case 2:	result = kDialogButton_CustomA;	break;
		case 3:	result = kDialogButton_CustomB;	break;
		default:
			break;
	}
	return result;
}

void VWDialog::SetDialogClose(bool bCloseWithOK)
{
	for(auto it : fstackItemHit)
	{
		if ( it )
		{
			*it	= bCloseWithOK ? kDialogButton_Ok : kDialogButton_Cancel;
		}
	}
}

// enables saved settings for this dialog
// if no dialog name is specified, the dialog title is used
void VWDialog::SetSavedSettingsTag(const TXString& category)
{
	fstrDialogCategory		= category;
	fstrDialogName.Clear();
}

void VWDialog::SetSavedSettingsTag(const TXString& category, const TXString& dialogName)
{
	fstrDialogCategory		= category;
	fstrDialogName			= dialogName;
}

// allows additional data to be stored in saved settings for this dialog
void VWDialog::SetSavedValue(const TXString& name, const TXString& value)
{
	if ( VERIFYN( kVStanev, fSavedSettingsDlgCategory.IsEmpty() == false ) )
	{
		gSDK->SetSavedSetting( fSavedSettingsDlgCategory, name, value );
	}
}

bool VWDialog::GetSavedValue(const TXString& name, TXString& outValue) const
{
	bool	bItemFound	= false;

	if ( VERIFYN( kVStanev, fSavedSettingsDlgCategory.IsEmpty() == false ) )
	{
		// read user defined items
		bItemFound	= gSDK->GetSavedSetting( fSavedSettingsDlgCategory, name, outValue );
	}

	return bItemFound;
}

TXString VWDialog::GetSavedValue(const TXString& name, const TXString& defValue) const
{
	TXString result;
	if ( this->GetSavedValue( name, result ) == false )
	{
		result = defValue;
	}

	return result;
}

void VWDialog::UpdateSavedSettings(bool bRead)
{
	const TXString			kX			= "x";
	const TXString			kY			= "y";
	const TXString			kWidth		= "width";
	const TXString			kHeight		= "height";

	if ( ! fstrDialogCategory.IsEmpty() )
	{
		if ( bRead )
		{
			if ( fstrDialogName.IsEmpty() ) {
				fstrDialogName	= this->GetDialogTitle();
			}

			// prepare full string category for this dialog
			TXString		theDlgCategory	= fstrDialogCategory + "/" + fstrDialogName;

			fSavedSettingsDlgCategory.Clear();

			// ensure the category name doesn't contain illegal caracters
			// nothing but chars or numbers goes in
			size_t			charsCnt		= theDlgCategory.GetLength();
			for(size_t i=0; i<charsCnt; i++) {
				UCChar	c		= theDlgCategory.GetAt( i );
				if ( c != '/' ) {
					bool	isDigit	= ( (((c) >= '0') && ((c) <= '9')) );
					bool	isAlpha	= ( (((c) >= 'a') && ((c) <= 'z')) ) || ( (((c) >= 'A') && ((c) <= 'Z')) );
					bool	isOk	= isAlpha || (i > 0 && isDigit);
					if ( isOk ) {
						fSavedSettingsDlgCategory	+= c;
					}
				}
				else {
					fSavedSettingsDlgCategory	+= c;
				}
			}

			// read dialog position
			TXString		strX, strY, strWidth, strHeight;
			if ( ::GS_GetSavedSetting( gCBP, fSavedSettingsDlgCategory, kX, strX ) &&
				 ::GS_GetSavedSetting( gCBP, fSavedSettingsDlgCategory, kY, strY ) &&
				 ::GS_GetSavedSetting( gCBP, fSavedSettingsDlgCategory, kWidth, strWidth ) &&
				 ::GS_GetSavedSetting( gCBP, fSavedSettingsDlgCategory, kHeight, strHeight ) )
			{
				fSavedDialogPosition.left	= TXString(strX).atoi();
				fSavedDialogPosition.top	= TXString(strY).atoi();
				fSavedDialogPosition.right	= fSavedDialogPosition.left + TXString(strWidth).atoi();
				fSavedDialogPosition.bottom	= fSavedDialogPosition.top + TXString(strHeight).atoi();
			}
		}
		else {
			// save dialog position
			ViewPt		dlgPos	= this->GetDialogPosition();
			
			ViewCoord	dialogWidth;
			ViewCoord	dialogHeight;			
			this->GetDialogSize( dialogWidth, dialogHeight );
			
			TXString	strX;		strX.Format( "%d", dlgPos.x );
			TXString	strY;		strY.Format( "%d", dlgPos.y );
			TXString	strWidth;	strWidth.Format( "%d", dialogWidth );
			TXString	strHeight;	strHeight.Format( "%d", dialogHeight );

			::GS_SetSavedSetting( gCBP, fSavedSettingsDlgCategory, kX, strX );
			::GS_SetSavedSetting( gCBP, fSavedSettingsDlgCategory, kY, strY );
			::GS_SetSavedSetting( gCBP, fSavedSettingsDlgCategory, kWidth, strWidth );
			::GS_SetSavedSetting( gCBP, fSavedSettingsDlgCategory, kHeight, strHeight );
		}
	}
}

void VWDialog::RegisterListBrowserColumn(TControlID controlID, size_t columnIndex, const TXString& savedSettingsColumnName)
{
	SSavedColumnData	data;
	data.fControlID					= controlID;
	data.fColumnIndex				= columnIndex;
	data.fSavedSettingsColumnName	= savedSettingsColumnName;
	farrSavedLSColumnData.push_back( data );
}

void VWDialog::SaveListBrowserColumnSavedSets()
{
	if ( fSavedSettingsDlgCategory.IsEmpty() == false )
	{
		TXString	strValue;

		for(size_t i=0, cnt=farrSavedLSColumnData.size(); i<cnt; ++i)
		{
			const SSavedColumnData&	data	= farrSavedLSColumnData[ i ];

			short	width	= 0;
			if ( gSDK->GetListBrowserColumnWidth( fControlID, data.fControlID, (short)data.fColumnIndex, width ) )
			{
				strValue.Format( "%d", width );
				this->SetSavedValue( data.fSavedSettingsColumnName, strValue );
			}
		}
	}
}

void VWDialog::RegisterSwapControl(TControlID listControlID, TControlID swapControlID, const TXString& savedSettingsName, bool autoSwap, TRegisterSwapCtrlTranslateCallback callback)
{
	SSavedColumnData	data;
	data.fControlID					= listControlID;
	data.fSupportControlID			= swapControlID;
	data.fColumnIndex				= 0;
	data.fSavedSettingsColumnName	= savedSettingsName;
	data.fAutoSwap					= autoSwap;
	data.fTranslateCallback			= callback;
	farrSavedSwapTabData.push_back( data );
}

void VWDialog::RegisterTabControl(TControlID controlID, const TXString& savedSettingsName)
{
	SSavedColumnData	data;
	data.fControlID					= controlID;
	data.fColumnIndex				= 1;
	data.fSavedSettingsColumnName	= savedSettingsName;
	data.fAutoSwap					= false;
	data.fTranslateCallback			= nullptr;
	farrSavedSwapTabData.push_back( data );
}

VWDialog::TRegisterSwapCtrlTranslateCallback VWDialog::GetRegisteredSwapConrolCallback(TControlID listControlID, TControlID swapControlID)
{
	TRegisterSwapCtrlTranslateCallback result = nullptr;
	for(const auto& data : farrSavedSwapTabData)
	{
		if ( data.fControlID == listControlID && data.fSupportControlID == swapControlID)
		{
			result = data.fTranslateCallback;
			break;
		}
	}

	return result;
}

void VWDialog::UpdateContextualHelpID(const TXString& newID)
{
	int dialogID = this->GetDialogID();
	gSDK->Kludge(521, (void *)&dialogID, (void *)&newID);
}

void VWDialog::RegisterForTimerEvents(Uint32 timerDelayInMilliseconds)
{
    gSDK->RegisterDialogForTimerEvents(this->GetDialogID(), timerDelayInMilliseconds);
}

void VWDialog::DeregisterForTimerEvents()
{
	gSDK->DeregisterDialogFromTimerEvents( this->GetDialogID() );
}


// extended eventing support for custom controls
void VWDialog::InitExtendedEventSupport()
{
}

void VWDialog::DeinitExtendedEventSupport()
{
}

void VWDialog::InstallExtendedEventSupport(VWControl* pControl)
{
}

VWDialog::SStyleControl::SStyleControl()
{
	key = 0;
	paramName.Clear();
	pControl = NULL;
	styleType = kPluginStyleParameter_ByInstance;
}

VWDialog::SStyleControl::~SStyleControl()
{
}

void VWDialog::SetStyleSupport( VWStyleSupport * pStyleSupport, bool styleMode)
{
	fpStyleSupport = pStyleSupport;
	fbStyleMode = styleMode;

	this->InitializeStyleSupport();
}


void VWDialog::InitializeStyleSupport()
{

	fStyleButtonHelp = TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "StyleButtonHelp" );
	fByStyleButtonHelp = TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "StyleButtonByStyle" );
	fByInstacneButtonHelp = TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "StyleButtonByInstance" );	
}

void VWDialog::InitStyleControl( TControlID controlID, Sint32 groupID,  const TXString & paramName, TControlID primaryControl, TControlID addedControl2, TControlID addedControl3, TControlID addedControl4 )
{
	VWStyleButtonCtrl * pControl = NULL;
	pControl = GetStyleButtonCtrlByID( controlID );
	if ( pControl ) {

		SStyleControl style;
		style.key = controlID;
		style.pControl = pControl;
		style.paramName = paramName;
		style.groupID = groupID;

		if ( fpStyleSupport ) {
			EPluginStyleParameter styleType;
			if ( fpStyleSupport->GetStyleType( paramName, styleType ) ) {
				style.styleType = styleType;				
				if ( fpStyleSupport->IsCatalogParam( paramName ) ) {
					style.styleType = kPluginStyleParameter_ByCatalog;
				}
			}
			else {
				fpStyleSupport->AddItem( paramName, kPluginStyleParameter_ByInstance );
				style.styleType = kPluginStyleParameter_ByInstance;
			}
		}


		pControl->SetParameterName( paramName );
		pControl->SetStyleType( style.styleType );
		if ( fbStyleMode ) {
			pControl->SetHelpText( fStyleButtonHelp );
		}
		else {
			if ( style.styleType == kPluginStyleParameter_ByStyle ) {
				pControl->SetHelpText( fByStyleButtonHelp );
			}
			else { 
				pControl->SetHelpText( fByInstacneButtonHelp );
			}
		}


		if ( primaryControl > 0 ) pControl->AddAssociatedControl( primaryControl );
		if ( addedControl2 > 0 ) pControl->AddAssociatedControl( addedControl2 );
		if ( addedControl3 > 0 ) pControl->AddAssociatedControl( addedControl3 );
		if ( addedControl4 > 0 ) pControl->AddAssociatedControl( addedControl4 );

		fStyleControlMap.insert( TStyleControl_Pair( controlID, style ) );

	}

}

void VWDialog::InitStyleGroupControl( TControlID controlID, Sint32 groupID, TControlID textControlID )
{
	VWStyleGroupButtonCtrl * pControl = GetStyleGroupButtonCtrlByID( controlID );
	if ( pControl ) {
		pControl->SetGroupID( groupID );
		if ( textControlID > 0 ) {
			pControl->SetTextControlID( textControlID );
		}
		fStyleGroupControls.push_back( pControl );
		UpdateStyleGroupButton( groupID );

	}
}


void VWDialog::AssociateStyleControl( TControlID controlID, TControlID associatedControlID )
{
	TStyleControl_Iterator iter = fStyleControlMap.find( controlID );
	if ( iter != fStyleControlMap.end() ) {			
		VWStyleButtonCtrl * pCtrl = iter->second.pControl;
		pCtrl->AddAssociatedControl( associatedControlID );
	}

}

void VWDialog::AssociateStyleParameter( TControlID controlID,  const TXString &  paramName )
{
	TStyleControl_Iterator iter = fStyleControlMap.find( controlID );
	if ( iter != fStyleControlMap.end() ) {			
		VWStyleButtonCtrl * pCtrl = iter->second.pControl;
		pCtrl->AddAssociatedParameter( paramName );
	}
	
}

void VWDialog::UpdateStyleGroupButton( Sint32 groupID )
{
	VWStyleGroupButtonCtrl * pGroupControl = NULL;

	for ( size_t i = 0; i < fStyleGroupControls.size(); i++ ) {
		if ( fStyleGroupControls[i]->GetGroupID() == groupID ) {
			pGroupControl = fStyleGroupControls[i];
			break;
		}
	}

	bool byStyle = false;
	bool byInst  = false;
	
	if ( pGroupControl ) {
		TStyleControl_Iterator iter;
		for ( iter = fStyleControlMap.begin(); iter != fStyleControlMap.end(); iter++ ) {
			if ( iter->second.groupID == groupID ) {
				if ( iter->second.styleType ==  kPluginStyleParameter_ByStyle ) {
					byStyle = true;
				}
				else {
					byInst = true;
				}
			}
			if ( byStyle && byInst ) {
				break;
			}
		}

		if ( byStyle && byInst ) {
			pGroupControl->SetStyleGroupType( kPluginStyleGroup_Mixed );
		}
		else if ( byStyle ) {
			pGroupControl->SetStyleGroupType( kPluginStyleGroup_ByStyle );
		}
		else {
			pGroupControl->SetStyleGroupType( kPluginStyleGroup_ByInstance );
		}

	}

}

void VWDialog::UpdateStyleSupport()
{
	if ( fbStyleMode && fpStyleSupport ) {
		VWStyleButtonCtrl * pStyleButtonControl;
		TXString paramName;

		TStyleControl_Iterator iter;
		for ( iter = fStyleControlMap.begin(); iter != fStyleControlMap.end(); iter++ ) {
			pStyleButtonControl = iter->second.pControl;
			paramName = iter->second.paramName;
			if ( iter->second.styleType != kPluginStyleParameter_ByCatalog ) {
				fpStyleSupport->SetStyleType( paramName, iter->second.styleType );

				size_t numAddedParams = pStyleButtonControl->NumberofAssoicatedParameters();
				if (  numAddedParams > 0 ) {
					for ( size_t i = 0; i < numAddedParams; i++ ) {
						paramName.Clear();
						paramName = pStyleButtonControl->GetAssociatedParameter( i ) ;
						if ( paramName.IsEmpty() == false && iter->second.styleType != kPluginStyleParameter_ByCatalog ) {
							fpStyleSupport->SetStyleType( paramName, iter->second.styleType );
						}
					}
				}		
			}
		}
	}
}

void VWDialog::UpdateStyleUI()
{
	VWStyleButtonCtrl * pStyleButtonControl;
	TControlID associatedId;
	TControlID dialogID = this->GetDialogID();

	TStyleControl_Iterator iter;
	for ( iter = fStyleControlMap.begin(); iter != fStyleControlMap.end(); iter++ ) {
		pStyleButtonControl = iter->second.pControl;
		
		if ( fpStyleSupport ) {
			if ( fbStyleMode == false ) {
				pStyleButtonControl->Enable( false );
				associatedId = pStyleButtonControl->GetPrimaryAssoicatedControl();
				if ( associatedId > 0 )  {
					if ( gSDK->IsItemEnabled( dialogID, associatedId ) ) {
						pStyleButtonControl->UpdateAssociatedControls();
					}
				}
			}

			if ( fpStyleSupport->IsCatalogParam( iter->second.paramName ) ) {				
				pStyleButtonControl->EnableAssociatedControls( false );
				pStyleButtonControl->SetStyleType( kPluginStyleParameter_ByCatalog );
				pStyleButtonControl->Enable( false );
			}

		}
	}
}

void VWDialog::UpdateCatalogUI()
{
	if ( fpStyleSupport ) {

		fpStyleSupport->LoadCatalogList();
				
		VWStyleButtonCtrl * pStyleButtonControl;		

		TStyleControl_Iterator iter;
		for ( iter = fStyleControlMap.begin(); iter != fStyleControlMap.end(); iter++ ) {
			if ( fpStyleSupport->IsCatalogParam( iter->second.paramName ) ) {
				pStyleButtonControl = iter->second.pControl;						
				pStyleButtonControl->EnableAssociatedControls( false );
				pStyleButtonControl->SetStyleType( kPluginStyleParameter_ByCatalog );
				pStyleButtonControl->Enable( false );
			}

		}
	
	
	}


}

void VWDialog::OnChangeStyleButton( TControlID controlID, VWDialogEventArgs& eventArgs )
{
	VWStyleButtonCtrl * ctrl = GetStyleButtonCtrlByID( controlID );
	TXString paramName = ctrl->GetParameterName();

	EPluginStyleParameter currentStyleType = ctrl->GetStyleType();
	EPluginStyleParameter newStyleType;
	if ( currentStyleType == kPluginStyleParameter_ByStyle ) {
		newStyleType = kPluginStyleParameter_ByInstance;
	}
	else {
		newStyleType = kPluginStyleParameter_ByStyle;
	}

	if ( paramName.IsEmpty() == false && fbStyleMode ) {

		TStyleControl_Iterator iter = fStyleControlMap.find( controlID );
		if ( iter != fStyleControlMap.end() ) {			
			VWStyleButtonCtrl * mappedCtrl = iter->second.pControl;
			iter->second.styleType = newStyleType;
			mappedCtrl->SetStyleType( newStyleType );
			UpdateStyleGroupButton( iter->second.groupID );
		}
	}

}


void VWDialog::OnChangeStyleGroupButton( TControlID controlID, VWDialogEventArgs& eventArgs )
{
	Sint32 groupID = -1;
	EPluginStyleGroup groupType;
	VWStyleGroupButtonCtrl * pGroupControl = NULL;

	for ( size_t i = 0; i < fStyleGroupControls.size(); i++ ) {
		if ( fStyleGroupControls[i]->GetControlID() == controlID ) {
			pGroupControl = fStyleGroupControls[i];
			break;
		}
	}

	ASSERTN( kJWarshaw, pGroupControl != NULL );
	if ( pGroupControl ) {
		groupID = pGroupControl->GetGroupID();
		groupType = pGroupControl->GetStyleGroupType();

		EPluginStyleGroup newStyleGroupType;
		if ( groupType == kPluginStyleGroup_ByStyle ) {
			newStyleGroupType = kPluginStyleGroup_ByInstance;
		}
		else {
			newStyleGroupType = kPluginStyleGroup_ByStyle;
		}
		
		EPluginStyleParameter newType = kPluginStyleParameter_ByInstance;
		if ( newStyleGroupType == kPluginStyleGroup_ByStyle ) {
			newType = kPluginStyleParameter_ByStyle;
		}

		TStyleControl_Iterator iter;
		for ( iter = fStyleControlMap.begin(); iter != fStyleControlMap.end(); iter++ ) {
			if ( iter->second.groupID == groupID ) {
				iter->second.styleType = newType;
				iter->second.pControl->SetStyleType( newType );		
			}			
		}

		pGroupControl->SetStyleGroupType( newStyleGroupType );
	}
}


#ifndef _WINDOWS
VWCustomCtrl* VWDialog::GetCustomCtrlAtPoint(const ViewPt& pt)
{
	VWCustomCtrl*	pFoundCtrl	= NULL;

	ASSERTN( kVStanev, fpArrControls );
	if ( fpArrControls ) {
		TControlsArray&		arrControls		= * ((TControlsArray*) fpArrControls);

		size_t	ctrlsCnt	= arrControls.size();
		for(size_t i=0; i<ctrlsCnt; i++) {
			SChildControls&		controlDef	= arrControls[ i ];

			VWCustomCtrl*	pCustomCtrl	= dynamic_cast<VWCustomCtrl*>( controlDef.pControl );
			if ( pCustomCtrl ) {
				ViewRect	ctrlRect	= pCustomCtrl->GetControlRect();
				if ( pCustomCtrl->IsVisible() && ctrlRect.PtInRect( ViewPt(pt) ) ) {
					pFoundCtrl	= pCustomCtrl;
					// found! BREAK!
					break;
				}
			}
		}
	}
	
	return pFoundCtrl;
}
#endif
