#include "StdAfx.h"

#include "SampleDlg3.h"

// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kTextPopupText        4
#define		kTextPopup            5
#define		kTextEnhPopupText     6
#define		kTextEnhPopup         7
#define		kMarkerPopupText      8
#define		kMarkerPopup          9
#define		kPattPopupText        10
#define		kPattPopup            11
#define		kLWPopupText          12
#define		kLWPopup              13
#define		kLSPopupText          14
#define		kLSPopup              15
#define		kLAttrPopupText       16
#define		kLAttrPopup           17
#define		kColorPopupText       18
#define		kColorPopup           19
#define		kImagePopupText       20
#define		kImagePopup           21


using namespace UI;

EVENT_DISPATCH_MAP_BEGIN( CSampleDlg3 );
ADD_DISPATCH_EVENT( kTextPopup, OnPopupControl );
EVENT_DISPATCH_MAP_END;

CSampleDlg3::CSampleDlg3()
{
    this->SetSavedSettingsTag( "sampleDlg", "CSampleDlg3" ); 

	fTextPopup					= 1;
	fPattPopupIndex				= 1;
	fLWPopup					= 1;
	fLSPopup					= 1;
	fLAttrPopupLineStyle		= 1;
	fLAttrPopupLineWeight		= 1;
	fPattPopupForeColor.red		= 0xFFFF;
	fPattPopupForeColor.green	= 0xFFFF;
	fPattPopupForeColor.blue	= 0xFFFF;
	fPattPopupBackColor.red		= 0x0000;
	fPattPopupBackColor.green	= 0x0000;
	fPattPopupBackColor.blue	= 0x0000;
	fColorPopup.red				= 0xFFFF;
	fColorPopup.green			= 0xFFFF;
	fColorPopup.blue			= 0xFFFF;

	CBBoolean		visibility;
	::GS_GetDefaultBeginningMarker( gCBP, fMarkerPopup, visibility );
}

CSampleDlg3::~CSampleDlg3()
{
}

bool CSampleDlg3::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "VWUI Dialogs Sample/DialogLayout/SampleDlg3.vs" );
}

void CSampleDlg3::OnPopupControl(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	if ( eventArgs.IsPullDownNotification() ) {
		VWPullDownMenuCtrl*		pTextPopup	= this->GetPullDownMenuCtrlByID( kTextPopup );
		pTextPopup->AddItem( "item 1" );
		pTextPopup->AddItem( "item 2" );
		pTextPopup->AddItem( "item 3" );
		pTextPopup->AddItem( "item 4" );
		pTextPopup->AddItem( "item 5" );
	}
	else {
		//int c = 0;
		this->SetDialogClose( false );
	}
}

void CSampleDlg3::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	// TODO: Fill up your dialog controls here
	VWPullDownMenuCtrl*		pTextPopup	= this->GetPullDownMenuCtrlByID( kTextPopup );
	pTextPopup->EnableNotifyPullDown();
}

void CSampleDlg3::OnDDXInitialize()
{
	this->AddDDX_PulldownMenu( kTextPopup, & fTextPopup );
	this->AddDDX_MarkerPopup( kMarkerPopup, & fMarkerPopup );
	this->AddDDX_PatternPopup( kPattPopup, & fPattPopupIndex, & fPattPopupForeColor, & fPattPopupBackColor );
	this->AddDDX_LineWeightPopup( kLWPopup, & fLWPopup );
	this->AddDDX_LineStylePopup( kLSPopup, & fLSPopup );
	this->AddDDX_LineAttribsPopup( kLAttrPopup, & fLAttrPopupLineStyle, & fLAttrPopupLineWeight );
	this->AddDDX_ColorPopup( kColorPopup, & fColorPopup );

}

void CSampleDlg3::OnUpdateUI()
{
	VWDialog::OnUpdateUI();
}


