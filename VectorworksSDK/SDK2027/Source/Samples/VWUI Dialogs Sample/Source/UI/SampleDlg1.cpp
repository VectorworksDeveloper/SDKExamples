#include "StdAfx.h"

#include "SampleDlg1.h"

#define    kTextControlID			3
#define    kEditIntegerControlID	4
#define    kMyImageControlID		17

using namespace UI;

// ------------------------------------------------------------------
CMyDialog::CDataItem::CDataItem(const TXString& value, bool visible, bool createChild)
{
	fVisible	= visible;
	fName		= value;

	if ( createChild )
	{
		for(size_t i=0; i<5; i++)
		{
			TXString	line;
			line.Format( "    %s: sub %d", (const char*) value, i );
			farrChildItems.push_back( CDataItem( line, false, false ) );
		}
	}
}

CMyDialog::CDataItem::~CDataItem()
{
}

bool CMyDialog::CDataItem::IsVisible()
{
	return fVisible;
}

size_t CMyDialog::CDataItem::GetChildCount()
{
	return farrChildItems.size();
}

CMyDialog::CDataItem* CMyDialog::CDataItem::GetChildAt(size_t index)
{
	return index < farrChildItems.size() ? & farrChildItems[index] : NULL;
}

int CMyDialog::CDataItem::OnPaint(VWCustomCtrl& parent, VWCustomCtrlDC& dc, const ViewPt& pt)
{
	int lineWidth	= 0;

	dc.DrawString( pt, fName );
	lineWidth += dc.GetStringWidth( fName );

	return lineWidth;
}

void CMyDialog::CDataItem::OnMouseClick(VWCustomCtrl& parent, const SCustomCtrlMouseEvent& event, bool isDoubleClick)
{
	for(size_t i=0, cnt=farrChildItems.size(); i<cnt; i++)
	{
		CDataItem& data = farrChildItems[ i ];
		data.fVisible = ! data.fVisible;
	}

	parent.Refresh();
}

// ------------------------------------------------------------------
EVENT_DISPATCH_MAP_BEGIN( CMyDialog );
ADD_DISPATCH_EVENT( kEditIntegerControlID, EditIntegerChanged );
EVENT_DISPATCH_MAP_END;

CMyDialog::CMyDialog() :
   fStaticTextCtrl( kTextControlID ),
   fEditIntegerCtrl( kEditIntegerControlID ),
   fMyCustomCtrl1( kMyImageControlID, farrItems )
{
	this->SetSavedSettingsTag( "sampleDlg", "CMyDialog" ); 
	fIntControlValue    = 5;

	// fill some data
	//for(size_t i=0; i<33100; i++)
	for(size_t i=0; i<100; i++)
	{
		TXString	line;
		line.Format( "Line %d", i );
		farrItems.push_back( CDataItem( line ) );
	}
}

CMyDialog::~CMyDialog()
{
}

bool CMyDialog::CreateDialogLayout()
{
   // create the dialog
   if ( ! this->CreateDialog( "CinerenderTCP", "OK", "Cancel", true ) )
       return false;

   // create the controls in the dialog
   if ( ! fStaticTextCtrl.CreateControl( this, "Enter a value:" ) )
       return false;
   if ( ! fEditIntegerCtrl.CreateControl( this, 4, 5 ) )
      return false;

   if ( ! fMyCustomCtrl1.CreateControl( this, 400, 300 ) )
      return false;

   // add the controls to the dialog
   this->AddFirstGroupControl( & fStaticTextCtrl );
   this->AddRightControl( & fStaticTextCtrl, & fEditIntegerCtrl );
   this->AddBelowControl( & fStaticTextCtrl, & fMyCustomCtrl1 );

   return true;
}
void CMyDialog::OnInitializeContent()
{
    VWDialog::OnInitializeContent();

    // TODO: Fill up your dialog controls here

	fMyCustomCtrl1.SetVScrollPos( 21000 );
}

void CMyDialog::OnDDXInitialize()
{
   // TODO: Attach DDX variables -- if any
   this->AddDDX_EditInteger( kEditIntegerControlID, & fIntControlValue );

  this->AddDDX_Control( & fMyCustomCtrl1 );
}

void CMyDialog::EditIntegerChanged(TControlID controlID, VWDialogEventArgs& eventArgs)
{
   // TODO: Handle the control event
}


