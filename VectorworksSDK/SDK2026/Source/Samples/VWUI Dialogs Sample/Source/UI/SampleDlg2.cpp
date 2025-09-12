#include "StdAfx.h"

#include "SampleDlg2.h"

// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kListBoxText          4
#define		kListBox1             5
#define		kListBrowserText      6
#define		kListBrowser          7
#define		kListBox2             8


using namespace UI;

EVENT_DISPATCH_MAP_BEGIN( CSampleDlg2 );
ADD_DISPATCH_EVENT( kListBox1, OnListBoxControl );
EVENT_DISPATCH_MAP_END;

CSampleDlg2::CSampleDlg2()
{
    this->SetSavedSettingsTag( "sampleDlg", "CSampleDlg2" ); 
}

CSampleDlg2::~CSampleDlg2()
{
}

bool CSampleDlg2::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "VWUI Dialogs Sample/DialogLayout/SampleDlg2.vs" );
}

void CSampleDlg2::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	// TODO: Fill up your dialog controls here
	VWListBoxCtrl*		pList1			= this->GetListBoxCtrlByID( kListBox1 );
	VWListBoxCtrl*		pList2			= this->GetListBoxCtrlByID( kListBox2 );
	VWListBrowserCtrl*	pListBrowser	= this->GetListBrowserCtrlByID( kListBrowser );

	// init list 1
	for(size_t i=0; i<23; i++) {
		long		marker	= 1 << i;
		TXString	itemName;
		itemName.Format( "item %d; marker %d", (i+1), marker );
		pList1->AddItem( itemName, size_t(-1), marker );
	}

	// init list 2
	pList2->AddTabStop( 5 );
	pList2->AddTabStop( 10 );
	pList2->AddTabStop( 15 );
	pList2->AddItem( "a1\tb1\tc1\td1" );
	pList2->AddItem( "a2\tb2\tc2\td2" );
	pList2->AddItem( "a3\tb3\tc3\td3" );

	// init list browser
	pListBrowser->AddColumn( "col1", 50 );
	pListBrowser->AddColumn( "col2", 50 );
	pListBrowser->AddColumn( "col3", 100 );
	pListBrowser->AddColumn( "col4", 50 );

	size_t				at		= pListBrowser->AddRow( "1" );
	VWListBrowserItem	item	= pListBrowser->GetItem( at, 2 );
	item.SetItemText( "some item text" );

}

void CSampleDlg2::OnDDXInitialize()
{

}

void CSampleDlg2::OnUpdateUI()
{
	VWDialog::OnUpdateUI();
}

void CSampleDlg2::OnListBoxControl(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	VWListBoxCtrl*		pList1			= this->GetListBoxCtrlByID( kListBox1 );

	long				marker			= pList1->GetSelectedItemMarker();

	TXString			strMarker;
	strMarker.Format( "Selected index marker: %d", marker );
	VWDialog::AlertInform( strMarker );
}

