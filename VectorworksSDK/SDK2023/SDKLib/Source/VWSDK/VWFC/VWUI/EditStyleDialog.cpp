//
//	Copyright  Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/EditStyleDialog.h"
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
using namespace VectorWorks::DataCatalog;

#define			kOKButton					1
#define			kCancelButton				2
#define			kStyleNameCaption			4
#define			kStyleNameEdit				5
#define			kCatalogLabel				6	
#define			kCatalogPopup				7
#define			kCatStyleBtn				8
#define			kCatItemBtn					9
#define			kCatItemText				10
#define			kListBrowser				11


#define			kColNumber		0
#define			kColByStyle		1
#define			kColParamName	2		


EVENT_DISPATCH_MAP_BEGIN( VWEditStyleDialog );
ADD_DISPATCH_EVENT(kCatItemBtn, OnChooseCatalogItem);
ADD_DISPATCH_EVENT(kCatalogPopup, OnChooseCatalog);
ADD_DISPATCH_EVENT( kListBrowser, OnDataListBrowser );
ADD_DISPATCH_EVENT( kCatalogLabel, OnUseCatalog );
ADD_DISPATCH_EVENT( kCatStyleBtn, OnCatByStyleBtn );
EVENT_DISPATCH_MAP_END;


VWEditStyleDialog::VWEditStyleDialog()
	: fListBrowser( kListBrowser ),
	fStyleNameCapiton( kStyleNameCaption ),
	fStyleNameText( kStyleNameEdit ),
	fCatalogText( kCatalogLabel ),
	fCatalogPopup( kCatalogPopup ),
	fCatByStyleButton( kCatStyleBtn ),
	fChooseCatItemButton( kCatItemBtn ),
	fCatItemName( kCatItemText )

{
	fLBByStyle		= TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "Style" );
	fLBByInstance	= TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "Instance" );
	fLBByCatalog = TXResource("Vectorworks/Strings/PluginStyles.vwstrings", "Catalog");

	fNoCatalogChosen = TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "NoCatalogChosen" );
	fNoCatalogsFound = TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "NoCatalogsFound" );
	
	fpWidgetsProvider = NULL;
	fpStyleSupport = NULL;
	fUsesCatalog = false;
	fParamNames.Clear();
}

VWEditStyleDialog::~VWEditStyleDialog()
{
}

void VWEditStyleDialog::OnDDXInitialize()
{
}

void VWEditStyleDialog::SetWidgetsProvider( IWidgetsProvider * pWidgetsProvider )
{
	if ( pWidgetsProvider != NULL ) {
		fpWidgetsProvider = pWidgetsProvider;
	}
}

void VWEditStyleDialog::SetStyleSupport(VWStyleSupport * pStyleSupport, bool styleMode)
{
	VWDialog::SetStyleSupport(pStyleSupport, styleMode);
	
	MCObjectHandle obj = pStyleSupport->GetStyleSourceObject();
	using namespace VectorWorks::Extension;
	IExtendedPropsPtr		extProps(IID_ExtendedProps);
	extProps->GetObjectProperty(obj, kObjXCatalogSupport, fUsesCatalog);

	if ( fUsesCatalog ) {
		fFolderSpec = kObjectStylesFolder;
		gSDK->GetCatalogPath( obj, fFolderSpec, fRelativePath );
		fCatalogSupport.LoadCatalogList( obj );
	}

}

void VWEditStyleDialog::SetStyleName( const TXString & styleName ) 
{
	if ( styleName.IsEmpty() == false ) {
		fStyleName = styleName;
	}
}

bool VWEditStyleDialog::CreateDialogLayout()
{
	// create the dialog layout.
	TXResource title( "Vectorworks/Strings/PluginStyles.vwstrings", "EditStyleMapTitle" );
	TXResource styleNameCaption("Vectorworks/Strings/PluginStyles.vwstrings", "StyleName" );
	
	TXResource styleNameHelp("Vectorworks/Strings/PluginStyles.vwstrings", "StyleNameHelp" );
	TXResource lbHelpText( "Vectorworks/Strings/PluginStyles.vwstrings", "EditStyleMapHelp" );

	TXResource okText( "Vectorworks/Strings/PluginStyles.vwstrings", "OK" );
	TXResource okHelp( "Vectorworks/Strings/PluginStyles.vwstrings", "OKHelp" );
	TXResource cancelText( "Vectorworks/Strings/PluginStyles.vwstrings", "Cancel" );
	TXResource cancelHelp( "Vectorworks/Strings/PluginStyles.vwstrings", "CancelHelp" );
	
	


	
	bool bReturn	= this->CreateDialog( title, okText, cancelText, true, true, true );
	if ( bReturn ) {
		fStyleNameCapiton.CreateControl( this, styleNameCaption );
		fStyleNameText.CreateControl( this, fStyleName );
		fStyleNameCapiton.SetHelpText( styleNameHelp );
		fStyleNameText.SetHelpText( styleNameHelp );
		
		if (fUsesCatalog) {
			TXResource catalogName( "Vectorworks/Strings/PluginStyles.vwstrings", "CatalogName" );
			TXResource noItemChosen( "Vectorworks/Strings/SelectCatalog.vwstrings", "NoCatalogItem" );

			TXResource useCatalogHelp( "Vectorworks/Strings/PluginStyles.vwstrings", "UseCatalogHelp" );
			TXResource catalogListHelp( "Vectorworks/Strings/PluginStyles.vwstrings", "CatalogListHelp" );
			TXResource catByStyleHelp( "Vectorworks/Strings/PluginStyles.vwstrings", "CatByStyleHelp" );
			TXResource chooseCatItemHelp( "Vectorworks/Strings/PluginStyles.vwstrings", "ChooseCatItemHelp" );
			TXResource catItemDescHelp( "Vectorworks/Strings/PluginStyles.vwstrings", "CatItemDescHelp" );

			fCatalogText.CreateControl(this, catalogName);
			fCatalogText.SetHelpText( useCatalogHelp );

			fCatalogPopup.CreateControl(this, 40);
			fCatalogPopup.SetHelpText( catalogListHelp );

			fCatByStyleButton.CreateControl(this, "Vectorworks/Standard Images/ByStyle.png", 1);
			fCatByStyleButton.SetHelpText( catByStyleHelp );

			fChooseCatItemButton.CreateControl(this, "Vectorworks/Standard Images/GetCatItem.png", 1);
			fChooseCatItemButton.SetHelpText( chooseCatItemHelp );

			fCatItemName.CreateControl(this, noItemChosen, 40);
			fCatItemName.SetHelpText( catItemDescHelp );
		}

		bReturn = fListBrowser.CreateControl( this, 100, 20 );
		fListBrowser.SetHelpText( lbHelpText );

		this->AddFirstGroupControl( &fStyleNameCapiton );
		this->AddRightControl( &fStyleNameCapiton, &fStyleNameText );
		
		if (fUsesCatalog) {
			this->AddBelowControl(&fStyleNameCapiton, &fCatalogText);
			this->AddRightControl(&fCatalogText, &fCatalogPopup);
			this->AddBelowControl(&fCatalogText, &fCatByStyleButton);
			this->AddRightControl(&fCatByStyleButton, &fChooseCatItemButton, -2);
			this->AddRightControl(&fChooseCatItemButton, &fCatItemName);
			this->AddBelowControl(&fCatByStyleButton, &fListBrowser);
		}
		else {
			this->AddBelowControl(&fStyleNameCapiton, &fListBrowser);
		}
		


		if ( fUsesCatalog ) {
			fStyleNameText.AlignLeftEdge( 1, kControlAlignModeShift );
			fCatalogPopup.AlignLeftEdge( 1, kControlAlignModeShift );
			fCatItemName.AlignLeftEdge( 1, kControlAlignModeShift );

			fStyleNameText.AlignColumnEdge( 2, kControlAlignModeResize );
			fListBrowser.AlignColumnEdge( 2, kControlAlignModeResize );
			fCatItemName.AlignColumnEdge( 2, kControlAlignModeResize );
		}

		

		gSDK->SetHelpText( this->GetDialogID(), kOKButton, okHelp );
		gSDK->SetHelpText( this->GetDialogID(), kCancelButton, cancelHelp );

	}


	return bReturn;
}

void VWEditStyleDialog::OnInitializeContent()
{
	fListBrowser.EnableClickAllDataChange( true );

	TXResource listNumber( "Vectorworks/Strings/PluginStyles.vwstrings", "ListNumber" );	
	fListBrowser.AddColumn( listNumber, 40 );

	fImageIndexByInst	= fListBrowser.AddImage( "Vectorworks/Standard Images/LBByInstance.png", "Vectorworks/Standard Images/LBByInstanceWhite.png" );
	fImageIndexByStyle	= fListBrowser.AddImage( "Vectorworks/Standard Images/LBByStyle.png", "Vectorworks/Standard Images/LBByStyleWhite.png"  );
	fImageIndexByCat = fListBrowser.AddImage("Vectorworks/Standard Images/LBByCatalog.png", "Vectorworks/Standard Images/LBByCatalogWhite.png");
	VWListBrowserColumn colNumber = fListBrowser.GetColumn( 0 ) ;
	colNumber.SetColumnHeaderToolTip( TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "ListNumberHelp" ), "" );

	TXResource headerName( "Vectorworks/Strings/PluginStyles.vwstrings", "ByStyle" );
	VWListBrowserColumn colCheck = fListBrowser.AddColumn(headerName, 60 );
	colCheck.SetColumnType( kListBrowserControlMultiState );
	colCheck.SetColumnHeaderToolTip( TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "ByStyleHelp" ), TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "ByStyleDescription" ) );

	colCheck.SetItemDisplayType( kListBrowserDisplayImageOnly );
	colCheck.InsertColumnChoice( fLBByInstance, fImageIndexByInst );
	colCheck.InsertColumnChoice( fLBByStyle, fImageIndexByStyle );

	TXResource parameterName( "Vectorworks/Strings/PluginStyles.vwstrings", "ParamaterName" );
	VWListBrowserColumn colName = fListBrowser.AddColumn( parameterName, 400 );
	colName.SetColumnHeaderToolTip( TXResource( "Vectorworks/Strings/PluginStyles.vwstrings", "ParamaterName" ), "" );

	Sint32 rowNum = 0;
	TXString newDisplayText;

	VWParametricObj paramObj(fpStyleSupport->fhHostParametricObject);

	// use widgets if available
	if ( fpWidgetsProvider && fpStyleSupport ) {

		size_t widgetCount = fpWidgetsProvider->GetWidgetsCount();
		
		for( size_t i = 0; i < widgetCount; i++ ) {
			EPluginStyleParameter styleType = kPluginStyleParameter_ByInstance;
			SWidgetDefinition widget = fpWidgetsProvider->GetWidgetAt( i );
			
			newDisplayText.Clear();
			if ( widget.fRecordParamIndex > 0 && this->AddItem( widget.fRecordParamIndex, widget.fWidgetText, newDisplayText ) ) {
				TXString num;
				rowNum++;
				num.itoa( rowNum );

				fParamNames.Append( paramObj.GetParamName( widget.fRecordParamIndex ) );

				size_t rowIndex = fListBrowser.AddRow( num );

				VWListBrowserItem name = fListBrowser.GetItem( rowIndex, kColParamName );
				name.SetItemText( newDisplayText );
				name.SetItemData( widget.fRecordParamIndex );

				fpStyleSupport->GetStyleTypeByParamIndex( widget.fRecordParamIndex, styleType );
				VWListBrowserItem byStyle = fListBrowser.GetItem( rowIndex, kColByStyle );

				if ( styleType == kPluginStyleParameter_ByStyle ) {
					byStyle.SetItemInfo( fLBByStyle, fImageIndexByStyle );
				}
				else {
					byStyle.SetItemInfo( fLBByInstance, fImageIndexByInst );
				}
			}
		}
	}

	// if no widgets are linked then go directly to the style map
	else if ( fpStyleSupport ) {
		VWStyleSupport::TStyleInfo_Iterator iter;
		MCObjectHandle hObject = fpStyleSupport->GetStyleSourceObject();
		VWParametricObj paramObj( hObject );
		for ( iter = fpStyleSupport->fmapStyleInfo.begin(); iter != fpStyleSupport->fmapStyleInfo.end(); iter++ ) {
			EPluginStyleParameter styleType = kPluginStyleParameter_ByInstance;

			TXString localizedName;
			if ( iter->second.paramIndex == (size_t)-1  ||  iter->second.paramIndex == 0 ) {
				localizedName = iter->second.key;
			}
			else {
				localizedName = paramObj.GetParamLocalizedName( iter->second.paramIndex );
			}

			fParamNames.Append( paramObj.GetParamName( iter->second.paramIndex + 1 ) );

			newDisplayText.Clear();
			if ( this->AddItem( (Sint16)iter->second.paramIndex + 1, localizedName, newDisplayText ) ) {
				TXString num;
				rowNum++;
				num.itoa( rowNum );

				size_t rowIndex = fListBrowser.AddRow( num );
	
				VWListBrowserItem name = fListBrowser.GetItem( rowIndex, kColParamName );
				
				name.SetItemText( newDisplayText );
				name.SetItemData( (Sint32)iter->second.paramIndex + 1);

				fpStyleSupport->GetStyleTypeByParamIndex( iter->second.paramIndex + 1, styleType );
				VWListBrowserItem byStyle = fListBrowser.GetItem( rowIndex, kColByStyle );
				byStyle.SetItemImage( styleType );

			}

		}
	}

	if ( fpStyleSupport ) {
		VWStyleSupport::TStyleEditList_Iterator iter;
		for ( iter = fpStyleSupport->fmapStyleEditList.begin() ; iter != fpStyleSupport->fmapStyleEditList.end( ); iter++ ) {
			if ( iter->second.editListType == kPluginStyleEditList_AddToEdit ) {
				EPluginStyleParameter styleType = kPluginStyleParameter_ByInstance;
				TXString num;
				rowNum++;
				num.itoa( rowNum );

				size_t rowIndex = fListBrowser.AddRow( num );
				fParamNames.Append( paramObj.GetParamName( iter->second.paramIndex + 1 ) );

				VWListBrowserItem name = fListBrowser.GetItem( rowIndex, kColParamName );
				name.SetItemText( iter->second.displayName );
				name.SetItemData( (Sint32)iter->second.paramIndex + 1 );

				fpStyleSupport->GetStyleTypeByParamIndex( iter->second.paramIndex + 1, styleType );
				VWListBrowserItem byStyle = fListBrowser.GetItem( rowIndex, kColByStyle );
				byStyle.SetItemImage( styleType );

			}
		}
	}

	if ( fpStyleSupport && fUsesCatalog ) {
		// load catalog popup
		VWStyleButtonCtrl * btn = this->GetStyleButtonCtrlByID( kCatStyleBtn );

		fCatalogSupport.LoadCatalogList( fpStyleSupport->fhHostSymbolDefiniiton );
		fCatalogSupport.FillCatalogList( fpStyleSupport->fhHostParametricObject, NULL, &fCatalogPopup );

		TXString currentCatalog = fCatalogSupport.GetCatalogName();
		if ( fCatalogPopup.GetItemsCount() > 0 ) {
			if ( currentCatalog.IsEmpty() ) {
				fCatItemName.SetControlText( fNoCatalogChosen );
			}
			else {
				fCatalogPopup.SelectItem( currentCatalog );
				fCatalogText.SetState( true );
				this->UpdateCatalogInfo();
			}

			if ( fCatalogSupport.GetCatalogItemByStyle() ) {
				btn->SetStyleType( kPluginStyleParameter_ByStyle );
			}
			else {
				btn->SetStyleType( kPluginStyleParameter_ByInstance );
			}

			
		}
		else  {
			fCatalogText.SetState( false );
			fCatalogText.Enable( false );
			btn->SetStyleType( kPluginStyleParameter_ByInstance );
			btn->Enable( false );
			fCatItemName.SetControlText( fNoCatalogsFound );
		}

		this->UpdateListBrowser();
	}

}

bool VWEditStyleDialog::AddItem( Sint16 paramIndex, const TXString & displayText, TXString & newDisplayText )
{
	if( fpStyleSupport == NULL ) {
		ASSERTN( kJWarshaw, fpStyleSupport == NULL );
		return false;
	}

	if ( displayText.IsEmpty() == false ) {
		newDisplayText = displayText;
	}


	bool addItem = true;
	if ( paramIndex < 0  ) {
		addItem = false;
	}

	if ( addItem ) {
		if ( displayText.Left( 5 ) == "__NNA" ) {
			addItem = false;
		}
	}

	if ( addItem ) {
		EPluginStyleParameter styleType = kPluginStyleParameter_ByInstance;
		if ( paramIndex == 0 || paramIndex == (size_t)-1 ) {
			fpStyleSupport->GetStyleType( displayText, styleType );
		}
		else {
			addItem = fpStyleSupport->GetStyleTypeByParamIndex( paramIndex, styleType );
		}

		if ( styleType == kPluginStyleParameter_AllwaysByInstance ) {
			addItem = false;
		}
	}

	if ( addItem ) {
		EPluginStyleEditList editListType = kPluginStyleEditList_Unused;
		TXString displayName;
		if ( paramIndex == 0 || paramIndex == (size_t)-1  ) {
			fpStyleSupport->GetStyleEditListType( displayText, editListType, displayName );
		}
		else {
			fpStyleSupport->GetStyleEditListTypeByParamIndex( paramIndex, editListType, displayName );
		}
		
		if ( editListType == kPluginStyleEditList_RemoveFromEdit ) {
			addItem = false;
		}
		else if ( editListType == kPluginSytleEditList_NewDisplayName ) {
			newDisplayText = displayName;
		}
	}


	return addItem;
}

void VWEditStyleDialog::OnDefaultButtonEvent()
{
	size_t rowCount = fListBrowser.GetRowsCount();
	for ( size_t i = 0; i < rowCount; i++ ) {
		VWListBrowserItem name = fListBrowser.GetItem( i, kColParamName );
		Sint32 paramIndex;
		if ( name.GetItemData( paramIndex ) ) {
			VWListBrowserItem byStyle = fListBrowser.GetItem( i, kColByStyle );
			size_t styleIndex = byStyle.GetItemImage();	
			if (styleIndex != fImageIndexByCat ) {
				fpStyleSupport->SetStyleTypeByParamIndex(paramIndex, (EPluginStyleParameter)styleIndex);
			}
		}
	}

	if ( fUsesCatalog ) {
		VWStyleButtonCtrl * btn = this->GetStyleButtonCtrlByID( kCatStyleBtn );
		if ( btn->GetStyleType() == kPluginStyleParameter_ByStyle ) {
			fCatalogSupport.SetCatalogItemByStyle( true );
		}
		else {
			fCatalogSupport.SetCatalogItemByStyle( false );
		}
		fCatalogSupport.SaveCatalogList();
	}


	VWDialog::OnDefaultButtonEvent();
}

void VWEditStyleDialog::OnCancelButtonEvent()
{
	VWDialog::OnCancelButtonEvent();
}

void VWEditStyleDialog::OnUpdateUI()
{
	if (fUsesCatalog) {
		bool useCatalog = fCatalogText.GetState();
		fCatalogPopup.Enable(useCatalog);
		fCatByStyleButton.Enable(useCatalog);
		fChooseCatItemButton.Enable(useCatalog);
		fCatItemName.Enable(useCatalog);
	}

	VWDialog::OnUpdateUI();
}

void VWEditStyleDialog::OnUseCatalog( Sint32 controlID, VWDialogEventArgs& eventArgs )
{
	bool useCatalog = fCatalogText.GetState();
	if ( useCatalog == false ) {
		fCatalogSupport.ClearCatalogList();
		this->UpdateListBrowser();
		fCatItemName.SetControlText( fNoCatalogChosen );
	}
	else {
		TXString newCatalog = fCatalogPopup.GetSelectedItem();
		fCatalogSupport.SetCatalogName( newCatalog );
		this->LoadCatalog( newCatalog );
		this->UpdateCatalogInfo();
	}
}

void VWEditStyleDialog::OnChooseCatalog(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	TXString newCatalog = fCatalogPopup.GetSelectedItem();

	TXString currentCatalog = fCatalogSupport.GetCatalogName();
	if (currentCatalog.EqualNoCase(newCatalog) == false) {
		fCatalogSupport.SetCatalogName( newCatalog );
		this->LoadCatalog( newCatalog );
		this->UpdateCatalogInfo();
	}

}

void VWEditStyleDialog::OnChooseCatalogItem(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	TXString currentCatalog = fCatalogSupport.GetCatalogName();

	if (currentCatalog.IsEmpty()) {
		currentCatalog = fCatalogPopup.GetSelectedItem();
		fCatalogSupport.SetCatalogName( currentCatalog );
		this->LoadCatalog( currentCatalog );
	}

	VWFC::VWObjects::VWParametricObj paramObj( fpStyleSupport->fhHostParametricObject );
	TXString pluginName = paramObj.GetParametricName();
	TXString catalogInfoName;
	catalogInfoName.Format( "Vectorworks/Strings/Catalog Strings - %s.vwstrings", pluginName );
	



	//bool getItem = gSDK->SelectItemFromPluginCatalog(fpStyleSupport->fhHostParametricObject, currentCatalog);
	bool getItem = gSDK->SelectItemFromPluginCatalog( fpStyleSupport->fhHostParametricObject, currentCatalog, [&]( const TXString  id, EEmptyHandling opt )
	{
		return TXResStr( catalogInfoName, id, opt );
	} );

	if ( getItem ) {
		this->UpdateCatalogInfo();
	}
}

void VWEditStyleDialog::OnDataListBrowser(Sint32 controlID, VWDialogEventArgs& eventArgs)
{
	if ( fUsesCatalog == false ) {
		return;
	}

	size_t row;
	size_t col;

	eventArgs.GetListBrowserEvent(row, col);
	bool allow = true;
	if (row == (size_t)-1 || col == (size_t)-1) {
		allow = false;
	}
	
	if (allow) {
		VWListBrowserItem name = fListBrowser.GetItem( row, kColParamName );

		Sint32 paramIndex;
		if ( name.GetItemData( paramIndex ) ) {
			VWParametricObj paramObj( fpStyleSupport->fhHostParametricObject );
			TXString paramName = paramObj.GetParamName( paramIndex - 1 );
			
			if ( fCatalogText.GetState() && fCatalogSupport.IsCatalogParam( paramName ) ) {
				VWListBrowserItem byStyle = fListBrowser.GetItem( row, kColByStyle );
				byStyle.SetItemInfo( fLBByCatalog, fImageIndexByCat );
			}			
		}
	}

}

void VWEditStyleDialog::LoadCatalog( TXString & catalogName )
{
	EFolderSpecifier folderSpec = kObjectStylesFolder;
	TXString relativePath;

	MCObjectHandle hParamObj = fpStyleSupport->GetStyleSourceObject();
	gSDK->GetCatalogPath( hParamObj, folderSpec, relativePath );

	IDataCatalogPtr	dataCatalog( IID_DataCatalog );

	IFolderIdentifierPtr pFolderID( IID_FolderIdentifier );
	TXString catalogPath;
	if ( relativePath.IsEmpty() == false ) {
		pFolderID->Set( relativePath );
		IFileIdentifierPtr	fileID( IID_FileIdentifier );
		fileID->Set( pFolderID, catalogName );
		fileID->GetFileFullPath( catalogPath );
	}
	else {
		catalogPath = catalogName;
	}

	bool isReg = dataCatalog->IsCatalogRegistered( folderSpec, catalogPath );
	if ( isReg == false ) {
		SContentFile contFile;
		contFile.fFolderSpec = folderSpec;
		contFile.fFileNameID = catalogPath;
		SCatalogDefinition catDef;
		catDef.fAccessor = nullptr;
		catDef.fDefinitionFile_CatalogID = contFile;
		catDef.fPerformanceDataDef = nullptr;
		catDef.fPerformanceDataParamName = "";
		catDef.fSymbolFile_ContentID.fFolderSpec = folderSpec;
		catDef.fSymbolFile_ContentID.fFileNameID = "";
		catDef.fIrrigationCatalog = false;
		dataCatalog->Register( catDef );

	}

	ICatalogAccessor* accessor = dataCatalog->GetCatalogAccessor( folderSpec, catalogPath );
	if ( accessor != nullptr ) {
		const TManifestColumnsMap colMap = accessor->GetManifest().GetColumns();
		fCatalogSupport.ClearCatalogList();
		fCatalogSupport.SetCatalogName( catalogName );
		for ( const auto& it : colMap ) {
			if ( it.second.fParam.IsEmpty() == false ) {
				fCatalogSupport.fCatParamList.Append( it.second.fParam );

				if ( it.second.fKey == true ) {
					fCatalogSupport.fCatKeyList.Append( it.second.fParam );
				}


			}
		}

		bool findDescription = true;
		size_t descIndex = 1;
		while ( findDescription ) {
			findDescription = false;
			for ( const auto& it : colMap ) {
				if ( it.second.fParam.IsEmpty() == false ) {
					if ( it.second.fDescIndex == descIndex ) {
						fCatalogSupport.fCatDescList.Append( it.second.fParam );
						findDescription = true;
						descIndex++;
					}
				}
			}

		}

		gSDK->AplyFirstCatalogItem( hParamObj, catalogName );
		this->UpdateListBrowser();
	}

}

void VWEditStyleDialog::UpdateListBrowser()
{
	TXString catalogName = fCatalogSupport.GetCatalogName();
	bool hasCatalog = catalogName.GetLength() > 0;

	VWParametricObj paramObj( fpStyleSupport->fhHostParametricObject );
	size_t rowCount = fListBrowser.GetRowsCount();
	for ( size_t i = 0; i < rowCount; i++ ) {
		VWListBrowserItem name = fListBrowser.GetItem( i, kColParamName );
		VWListBrowserItem byStyle = fListBrowser.GetItem( i, kColByStyle );
		
		Sint32 paramIndex;
		if ( name.GetItemData( paramIndex ) ) {
			TXString paramName = paramObj.GetParamName( paramIndex - 1);
			if ( hasCatalog &&  fCatalogSupport.IsCatalogParam( paramName ) ) {
				byStyle.SetItemInfo( fLBByCatalog, fImageIndexByCat );
			}
			else {
				size_t imageIndex = byStyle.GetItemImage();
				if ( imageIndex == fImageIndexByCat ) {
					if ( fCatByStyleButton.GetStyleType() == kPluginStyleParameter_ByStyle ) {
						byStyle.SetItemInfo( fLBByStyle, fImageIndexByStyle );
					}
					else {
						byStyle.SetItemInfo( fLBByInstance, fImageIndexByInst );
					}
				}


			}
		}
	}


}

void VWEditStyleDialog::UpdateCatalogInfo()
{
	MCObjectHandle hParamObj = fpStyleSupport->GetStyleSourceObject();
	TXString catItem = fCatalogSupport.BuildCatalogItemName( hParamObj );
	fCatItemName.SetControlText( catItem );

}

void VWEditStyleDialog::OnCatByStyleBtn( Sint32 controlID, VWDialogEventArgs& eventArgs )
{
	if ( fpStyleSupport && fUsesCatalog ) {
		VWStyleButtonCtrl * btn = this->GetStyleButtonCtrlByID( kCatStyleBtn );
		EPluginStyleParameter sType = btn->GetStyleType();
				
		if ( sType == kPluginStyleParameter_ByInstance ) {
			sType = kPluginStyleParameter_ByStyle;
		}
		else {
			sType = kPluginStyleParameter_ByInstance;
		}
		btn->SetStyleType( sType );
	}
}