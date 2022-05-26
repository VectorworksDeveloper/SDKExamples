#include "StdAfx.h"

#include "DlgResourcePopupComplex.h"

// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kPopup                4
#define		kLatinNameTxt         5
#define		kLatinNameVal         6
#define		kCommonNameTxt        7
#define		kCommonNameVal        8


using namespace ResourcePopup;

EVENT_DISPATCH_MAP_BEGIN( CDlgResourcePopupComplex );
ADD_DISPATCH_EVENT( kPopup, OnPlantImagePopup );
EVENT_DISPATCH_MAP_END;

CDlgResourcePopupComplex::CDlgResourcePopupComplex(const TXString& selItem)
	: fContent( VectorWorks::Extension::IID_ResourceManagerContent )
	, fSelItem( selItem )
{
	// Assign settings tag to this dialog so it would save it's position and size automatically
	this->SetSavedSettingsTag( "TesterModule", "DlgResourcePopupComplex" );
}

CDlgResourcePopupComplex::~CDlgResourcePopupComplex()
{
}

bool CDlgResourcePopupComplex::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "TesterModule/DialogLayout/DlgResourcePopupComplex.vs" );
}

TXString CDlgResourcePopupComplex::GetSelectedItem()
{
	return fSelItem;
}

void CDlgResourcePopupComplex::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	fContent->InitByInternalID( kInternalID_Plant );

	gSDK->PullDownResourceLayoutInit( this->GetDialogID(), kPopup, fContent );

	VWImagePopupCtrl* symbolPopup = this->GetImagePopupCtrlByID( kPopup );
	symbolPopup->PullDownResourceLayoutInit( fContent );
	symbolPopup->PullDownResourceLayoutSetSelectedResourceName( fSelItem );

	this->UpdateSymbol();
}

void CDlgResourcePopupComplex::OnDDXInitialize()
{

}

void CDlgResourcePopupComplex::OnUpdateUI()
{
	VWDialog::OnUpdateUI();

	VWImagePopupCtrl*	symbolPopup	= this->GetImagePopupCtrlByID( kPopup );
	bool				hasResSel	= ! symbolPopup->PullDownResourceLayoutGetSelectedResourceName().IsEmpty();
	this->EnableControl( kOK, hasResSel );
}

void CDlgResourcePopupComplex::OnDefaultButtonEvent()
{
	VWImagePopupCtrl*	symbolPopup	= this->GetImagePopupCtrlByID( kPopup );
	fSelItem						= symbolPopup->PullDownResourceLayoutGetSelectedResourceName();

	VWDialog::OnDefaultButtonEvent();
}

void CDlgResourcePopupComplex::OnPlantImagePopup(Sint32 controlID, VWDialogEventArgs &eventArgs)
{
	this->UpdateSymbol();
}

void CDlgResourcePopupComplex::UpdateSymbol()
{
	gSDK->SupportUndoAndRemove();
	gSDK->SetUndoMethod( kUndoSwapObjects );

	MCObjectHandle hSymbol = fContent->ImportSelectedResourceToCurrentFile( VectorWorks::eImportResourceConflictResult_Replace );
	if ( hSymbol && VWParametricObj::IsParametricObject( gSDK->FirstMemberObj(hSymbol), "Plant" ) )
	{
		VWParametricObj	paramsSrc( gSDK->FirstMemberObj(hSymbol) );

		TXString	latinName	= paramsSrc.GetParamString( "latin name" );
		TXString	commonName	= paramsSrc.GetParamString( "common name" );

		this->GetStaticTextCtrlByID( kLatinNameVal )->SetControlText( latinName );
		this->GetStaticTextCtrlByID( kCommonNameVal )->SetControlText( commonName );

	}

	gSDK->UndoAndRemove();
}



