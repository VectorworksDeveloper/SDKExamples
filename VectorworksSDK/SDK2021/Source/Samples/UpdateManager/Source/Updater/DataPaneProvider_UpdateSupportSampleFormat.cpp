#include "StdAfx.h"

#include "DataPaneProvider_UpdateSupportSampleFormat.h"

using namespace Updater;

CDataPaneProvider_UpdateSupportSampleFormat::CDataPaneProvider_UpdateSupportSampleFormat(CallBackPtr)
	: fWidgetsProvider( nullptr )
	, fUpdateCustomPopup( true )
{
}

CDataPaneProvider_UpdateSupportSampleFormat::~CDataPaneProvider_UpdateSupportSampleFormat()
{
}

void CDataPaneProvider_UpdateSupportSampleFormat::Init(const TXString& recordFormatName, IExtendedProps* extProps)
{
	using namespace VWFC::PluginSupport;

	CWidgetsEditProvider	widgetProvider( extProps, recordFormatName );
	fWidgetsProvider	= widgetProvider.GetWidgetsProvider();

	// we are making presumations of the parameters in the record format here!
	// value 1 - type: any
	// value 2 - type: real
	// popup 1 - type: popup
	// popup 2 - type: popup
	widgetProvider.AddWidget( "Cust Value", kWidgetText, "Custom Value" );
	widgetProvider.AddWidget( "value 1", "value 1" );
	widgetProvider.AddWidget( "value 2", "value 2" );
	widgetProvider.AddWidget( "popup 1", "popup 1" );
	widgetProvider.AddWidget( "popup 2", "popup 2" );
	widgetProvider.AddWidget( "editBtn", kWidgetButton, "Edit Something..." );
	widgetProvider.AddWidget( "addBtn", kWidgetButton, TXResStr("DataPaneProvider_UpdateSupportSampleFormat", "addBtn") );

	fUpdateCustomPopup	= true;
}

void CDataPaneProvider_UpdateSupportSampleFormat::Activate(MCObjectHandle hObject, MCObjectHandle hRecord, const SSelectionContext& selContext)
{
	fhObject = hObject;
	fhRecord = hRecord;
}

void CDataPaneProvider_UpdateSupportSampleFormat::Deactivate()
{
	fhObject = nullptr;
}

void CDataPaneProvider_UpdateSupportSampleFormat::Update(IWidgetsProvider* widgetProvider)
{
	VWRecordObj	params( fhRecord );

	// update the popup if needed
	// Note: this must be smart not to happen often, as Update is called many times
	if ( fUpdateCustomPopup )
	{
		fUpdateCustomPopup = false;

		SWidgetDefinition&	popup2 = widgetProvider->GetWidgetByIDSafe( "popup 2" );
		IWidgetDataPopup* popup2Data = dynamic_cast<IWidgetDataPopup*>( popup2.fpWidgetData );
		if ( popup2Data )
		{
			popup2Data->Clear();

			TXString	key, value;
			size_t cnt = params.PopupGetChoicesCount( "popup 2" );
			if ( cnt == 0 )
			{
				popup2Data->Add( "", TXResStr("DataPaneProvider_UpdateSupportSampleFormat", "popupNone") );
				popup2Data->Add( "div", "-" );
				popup2Data->Add( "edit", TXResStr("DataPaneProvider_UpdateSupportSampleFormat", "popupEdit") );
			}
			else
			{
				for(size_t i=0; i<cnt; ++i)
				{
					params.PopupGetChoice( "popup 2", i, key, value );
					popup2Data->Add( key, value );
				}
			}
		}
	}


	double value2 = params.GetParamReal( "value 2" );

	widgetProvider->GetWidgetByIDSafe("editBtn").fWidgetEnabled = value2 > 10;;
}

bool CDataPaneProvider_UpdateSupportSampleFormat::OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk)
{
	if ( fWidgetsProvider->GetWidgetByIDSafe( "editBtn" ).fWidgetID == data.fWidgetID )
	{
		gSDK->AlertInform( "Button clicked" );
	}
	else if ( fWidgetsProvider->GetWidgetByIDSafe( "addBtn" ).fWidgetID == data.fWidgetID )
	{
		VWRecordObj	params( fhRecord );

		std::vector<std::pair<TXString, TXString>>	arrOptions;

		TXString	key, value;
		size_t cnt = params.PopupGetChoicesCount( "popup 2" );
		for(size_t i=0; i<cnt; ++i)
		{
			params.PopupGetChoice( "popup 2", i, key, value );
			if ( key != "div" && key != "edit" )
				arrOptions.push_back( std::make_pair( key, value ) );
		}

		static size_t sLastItemIndex = 1;
		TXString	newItem	= TXString::Formatted( "New Item %d", sLastItemIndex );
		sLastItemIndex++;

		arrOptions.push_back( std::make_pair( newItem, newItem ) );
		arrOptions.push_back( std::make_pair( "div", "-" ) );
		arrOptions.push_back( std::make_pair( "edit", TXResStr("DataPaneProvider_UpdateSupportSampleFormat", "popupEdit") ) );

		TXStringArray	keyValuePairs;
		for(auto it : arrOptions)
		{
			keyValuePairs.Append( it.first );
			keyValuePairs.Append( it.second );
		}

		params.PopupSetChoices( "popup 2", keyValuePairs, false );
		params.SetParamString( "popup 2", newItem );
		fUpdateCustomPopup	= true; // flag to update the popup
	}
	else if ( fWidgetsProvider->GetWidgetByIDSafe( "popup 2" ).fWidgetID == data.fWidgetID )
	{
		TXString key = data.fWidgetAccess->GetValueString( data.fViewWidget );
		if ( key == "div" || key == "edit" )
		{
			gSDK->AlertInform( "The edit option was selected. See the 'editBtn' case for an example how to edit the content" );
		}
	}

	return true;
}

bool CDataPaneProvider_UpdateSupportSampleFormat::TransferValue(SShapePaneWidgetTransferValue& data)
{
	bool result = false;

	if ( fWidgetsProvider->GetWidgetByIDSafe( "Cust Value" ).fWidgetID == data.fWidgetID )
	{
		if ( data.fTransferToView )
		{
			data.fWidgetAccess->SetValueString( data.fViewWidget, "The value" );
		}
		else
		{
			TXString val = data.fWidgetAccess->GetValueString( data.fViewWidget );
			gSDK->AlertInform( "New value is: " + val );
		}
	}

	return result;
}