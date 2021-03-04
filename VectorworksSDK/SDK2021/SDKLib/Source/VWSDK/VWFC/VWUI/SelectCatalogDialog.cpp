//
//	Copyright  Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/SelectCatalogDialog.h"
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
#include "DialogData.h"

using namespace VWFC::VWUI;
using namespace VWFC::Tools;
using namespace VectorWorks::Filing;

#define			kDetachCatalog			4
#define			kAttachCatalog			5
#define			kCatalogList			6

#define			kColNumber		0
#define			kColByStyle		1
#define			kColParamName	2		

EVENT_DISPATCH_MAP_BEGIN( VWSelectCatalog );
ADD_DISPATCH_EVENT( kDetachCatalog, OnDetachCatalog );
ADD_DISPATCH_EVENT( kAttachCatalog, OnAttachCatalog );
ADD_DISPATCH_EVENT( kCatalogList, OnDataListBrowser );
EVENT_DISPATCH_MAP_END;


/////////////////////////////////////////////////////////////////////////////////////////
class CSelecteCatalogFolderContentListener : IFolderContentListener
{
public:
	VWListBrowserCtrl * fpListBrower;
	TXStringArray * fpXMLNames;
	TXStringArray * fpTXTNames;
	virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFolderContent(IFolderIdentifier* pFolderID);
	virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFileContent(IFileIdentifier* pFileID);
};

EFolderContentListenerResult CSelecteCatalogFolderContentListener::OnFolderContent(IFolderIdentifier* pFolderID)
{
	return eFolderContentListenerResult_Continue;
}

EFolderContentListenerResult CSelecteCatalogFolderContentListener::OnFileContent(IFileIdentifier* pFileID)
{
	if ( fpListBrower != NULL ) {
		TXString txFileName;
		TXString txExtension;
		pFileID->GetFileExtension(txExtension);
		txExtension.MakeUpper();
		pFileID->GetFileNameWithoutExtension(txFileName);
		if (txExtension == "XML") {			
			fpXMLNames->Append( txFileName );
		}
		else if ( txExtension == "TXT" ) {
			fpTXTNames->Append( txFileName );
		}
		
	}
	return eFolderContentListenerResult_Continue;
}



VWSelectCatalog::VWSelectCatalog()
{
	fSelectedCatalog.Clear();
	fRelativePath.Clear();
	fXMLCatalogNames.Clear();
	fTXTCatalogNames.Clear();

	fSelectedCatalogRow = 0;
}

VWSelectCatalog::~VWSelectCatalog()
{
}


bool VWSelectCatalog::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR( "Vectorworks/DialogLayout/SelectCatalog.vs" );
}

void VWSelectCatalog::OnDDXInitialize()
{
	this->AddDDX_RadioButton( kDetachCatalog, &fDetachCatalog );
	this->AddDDX_RadioButton( kAttachCatalog, &fAttachCatalog );
}

void VWSelectCatalog::OnUpdateUI()
{
	VWListBrowserCtrl * pCatalogList = GetListBrowserCtrlByID( kCatalogList );
	pCatalogList->Enable( fAttachCatalog );

	if ( pCatalogList->GetRowsCount() == 0 ) {
		VWRadioButtonCtrl * pAttach = GetRadioButtonCtrlByID( kAttachCatalog );
		pAttach->Enable( false );
	}
}

void VWSelectCatalog::OnInitializeContent()
{
	VWListBrowserCtrl * pCatalogList = GetListBrowserCtrlByID( kCatalogList );
	pCatalogList->EnableSingleLineSelection( true );
	TXString catNameHeader = TXResource( "Vectorworks/Strings/SelectCatalog.vwstrings", "CatalogName" );
	pCatalogList->AddColumn( catNameHeader, 300 );

	CSelecteCatalogFolderContentListener fListener;
	fListener.fpListBrower = pCatalogList;
	fListener.fpXMLNames = &fXMLCatalogNames;
	fListener.fpTXTNames = &fTXTCatalogNames;

	IApplicationFoldersPtr	appFolders( IID_ApplicationFolders );
	appFolders->ForEachFileInStandardFolderN( fFolderSpecifier, fRelativePath, ETraverse::NonRecursively_IncludeWorkgroupFolders, (IFolderContentListener*)&fListener );

	fDetachCatalog = true;
	fAttachCatalog = false;
	
	size_t catalogCount = fXMLCatalogNames.GetSize();
	TXString catalogName;
	for( size_t i = 0; i < catalogCount; i++ ) {
		catalogName = fXMLCatalogNames[i];
		if ( fTXTCatalogNames.Find( catalogName, true ) != -1 ) {
			size_t newRow = pCatalogList->AddRow( catalogName );
			if ( catalogName.EqualNoCase( fSelectedCatalog ) ) {
				pCatalogList->SelectRow( newRow, true );
				fAttachCatalog = true;
				fDetachCatalog = false;
				fSelectedCatalogRow = newRow;
			}
		}
	}	

}

void VWSelectCatalog::OnDefaultButtonEvent()
{
	VWDialog::OnDefaultButtonEvent();
	
	if ( fAttachCatalog ) {
		VWListBrowserCtrl * pCatalogList = GetListBrowserCtrlByID( kCatalogList );
		if ( pCatalogList->GetRowsCount() > 0 ) {
			size_t selIndex = pCatalogList->GetFirstSelected();
			VWListBrowserItem item = pCatalogList->GetItem( selIndex, 0 );
			fSelectedCatalog = item.GetItemText();
		}
		else {
			fSelectedCatalog.Clear();
		}
	}
	else {
		fSelectedCatalog.Clear();
	}
}

void VWSelectCatalog::OnCancelButtonEvent()
{
	VWDialog::OnCancelButtonEvent();
}

void VWSelectCatalog::SetFolderSpecifier( EFolderSpecifier folderSpec )
{
	fFolderSpecifier = folderSpec;
}

void VWSelectCatalog::SetRelativePath( const TXString & relativePath )
{
	fRelativePath = relativePath;
}

TXString VWSelectCatalog::GetSelectedCatalog()
{
	return fSelectedCatalog;
}

void VWSelectCatalog::SetSelectedCatalog( const TXString & selectedCatalog )
{
	fSelectedCatalog = selectedCatalog;
}

void VWSelectCatalog::OnDataListBrowser( Sint32 controlID, VWDialogEventArgs& eventArgs )
{
	//VWListBrowserCtrl*	pListBrowser = GetListBrowserCtrlByID( kCatalogList );

	size_t row;
	size_t col;

	EListBrowserEventType eventType = eventArgs.GetListBrowserEvent( row, col );
	if ( eventType == kListBrowserEventType_SelectionChangeClick ) {
		fSelectedCatalogRow = row;
	}
}

void VWSelectCatalog::OnAttachCatalog( Sint32 controlID, VWDialogEventArgs& eventArgs )
{
	VWListBrowserCtrl*	pListBrowser = GetListBrowserCtrlByID( kCatalogList );	
	pListBrowser->SelectRow( fSelectedCatalogRow, true );
}

void VWSelectCatalog::OnDetachCatalog( Sint32 controlID, VWDialogEventArgs& eventArgs )
{
}