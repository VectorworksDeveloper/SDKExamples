//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"


#include "VWFC/PluginSupport/WidgetsEditProvider.h"

using namespace VWFC::PluginSupport;
using namespace VectorWorks::Extension;

// ------------------------------------------------------------------------------------------------------
CWidgetsEditProvider::CWidgetsEditProvider(CodeRefID objectID, TComponentTypeID compType)
	: fExtProps( IID_ExtendedProps )
	, fWidgetsProvider( NULL )
{
	VERIFYN( kVStanev, VCOM_SUCCEEDED( fExtProps->GetObjComponentTypeWidgets( objectID, compType, fWidgetsProvider ) ) );
}

CWidgetsEditProvider::CWidgetsEditProvider(VectorWorks::Extension::IExtendedProps* extProps, CodeRefID objectID, TComponentTypeID compType)
	: fExtProps( extProps )
	, fWidgetsProvider( NULL )
{
	VERIFYN( kVStanev, VCOM_SUCCEEDED( fExtProps->GetObjComponentTypeWidgets( objectID, compType, fWidgetsProvider ) ) );
}

CWidgetsEditProvider::CWidgetsEditProvider(MCObjectHandle hObject, TComponentTypeID compType)
	: fExtProps( IID_ExtendedProps )
	, fWidgetsProvider( NULL )
{
	CodeRefID		objectID;
	if ( VCOM_SUCCEEDED( fExtProps->GetCodeRefID( hObject, objectID ) ) )
	{
		VERIFYN( kVStanev, VCOM_SUCCEEDED( fExtProps->GetObjComponentTypeWidgets( objectID, compType, fWidgetsProvider ) ) );
	}
}

CWidgetsEditProvider::CWidgetsEditProvider(VectorWorks::Extension::IExtendedProps* extProps, const TXString& recordFormatName )
	: fExtProps( extProps )
	, fWidgetsProvider( NULL )
{
	VERIFYN( kVStanev, VCOM_SUCCEEDED( fExtProps->GetRecordFormatTypeWidgets( recordFormatName, fWidgetsProvider ) ) );
}

CWidgetsEditProvider::~CWidgetsEditProvider()
{
}

VectorWorks::Extension::IWidgetsEditProvider* CWidgetsEditProvider::operator->()
{
	return fWidgetsProvider;
}

void CWidgetsEditProvider::Clear()
{
	if ( fWidgetsProvider ) {
		fWidgetsProvider->ClearWidgets();
	}
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget(const char* widgetID, const TXString& paramName)
{
	Sint32	id = fWidgetsProvider->GetWidgetIDByName( widgetID );
	return this->AddWidget( id, paramName );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget(const char* widgetID, const TXString& paramName, const TXString& localizedName)
{
	Sint32	id = fWidgetsProvider->GetWidgetIDByName( widgetID );
	return this->AddWidget( id, paramName, localizedName );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget(const char* widgetID, EWidgetType widgetType, const TXString& paramName, const TXString& localizedName)
{
	Sint32	id = fWidgetsProvider->GetWidgetIDByName( widgetID );
	return this->AddWidget( id, widgetType, paramName, localizedName );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget(const char* widgetID, EWidgetType widgetType, const TXString& localizedName)
{
	Sint32	id = fWidgetsProvider->GetWidgetIDByName( widgetID );
	return this->AddWidget( id, widgetType, localizedName );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget_BoundPopup(const char* widgetID, VectorWorks::TObjectBoundID boundID, bool isTopBound, const TXString& localizedName)
{
	Sint32	id = fWidgetsProvider->GetWidgetIDByName( widgetID );
	return this->AddWidget_BoundPopup( id, boundID, isTopBound, localizedName );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget_BoundOffset(const char* widgetID, VectorWorks::TObjectBoundID boundID, const TXString& localizedName)
{
	Sint32	id = fWidgetsProvider->GetWidgetIDByName( widgetID );
	return this->AddWidget_BoundOffset( id, boundID, localizedName );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget_BoundOffset(const char* widgetID, VectorWorks::TObjectBoundID boundID, const TXString& localizedName, const TXString& legacyOffsetParam)
{
	Sint32	id = fWidgetsProvider->GetWidgetIDByName( widgetID );
	return this->AddWidget_BoundOffset( id, boundID, localizedName, legacyOffsetParam );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::GetWidget(const char* widgetID)
{
	Sint32	id = fWidgetsProvider->GetWidgetIDByName( widgetID );
	return this->GetWidget( id );
}


CWidgetsEditProvider::CWidget	CWidgetsEditProvider::GetWidget(Sint32 widgetID)
{
	return CWidget( this, widgetID );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget(Sint32 widgetID, const TXString& paramName)
{
	if ( fWidgetsProvider ) {
		fWidgetsProvider->AddWidget( widgetID, paramName );
	}
	return CWidget( this, widgetID );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget(Sint32 widgetID, const TXString& paramName, const TXString& localizedName)
{
	if ( fWidgetsProvider ) {
		fWidgetsProvider->AddWidget( widgetID, paramName, localizedName );
	}
	return CWidget( this, widgetID );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget(Sint32 widgetID, EWidgetType widgetType, const TXString& paramName, const TXString& localizedName)
{
	if ( fWidgetsProvider ) {
		fWidgetsProvider->AddWidget( widgetID, widgetType, paramName, localizedName );
	}
	return CWidget( this, widgetID );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget(Sint32 widgetID, EWidgetType widgetType, const TXString& localizedName)
{
	if ( fWidgetsProvider ) {
		fWidgetsProvider->AddWidget( widgetID, widgetType, localizedName );
	}
	return CWidget( this, widgetID );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget_BoundPopup(Sint32 widgetID, VectorWorks::TObjectBoundID boundID, bool isTopBound, const TXString& localizedName)
{
	if ( fWidgetsProvider ) {
		fWidgetsProvider->AddWidget( widgetID, kWidgetBoundPopup, localizedName );

		IWidgetDataBound*	boundData	= dynamic_cast<IWidgetDataBound*> ( fWidgetsProvider->GetWidgetByIDSafe( widgetID ).fpWidgetData );
		if ( VERIFYN( kVStanev, boundData ) )
		{
			boundData->SetObjectBoundID( boundID );
			boundData->SetIsTopBound( isTopBound );
		}
	}
	return CWidget( this, widgetID );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget_BoundOffset(Sint32 widgetID, VectorWorks::TObjectBoundID boundID, const TXString& localizedName)
{
	return this->AddWidget_BoundOffset( widgetID, boundID, localizedName, "" );
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::AddWidget_BoundOffset(Sint32 widgetID, VectorWorks::TObjectBoundID boundID, const TXString& localizedName, const TXString& legacyOffsetParam)
{
	if ( fWidgetsProvider ) {
		if ( legacyOffsetParam.IsEmpty() ) 
		{
			fWidgetsProvider->AddWidget( widgetID, kWidgetBoundOffset, localizedName );
		}
		else
		{
			fWidgetsProvider->AddWidget( widgetID, kWidgetBoundOffset, legacyOffsetParam, localizedName );
		}

		IWidgetDataBound*	boundData	= dynamic_cast<IWidgetDataBound*> ( fWidgetsProvider->GetWidgetByIDSafe( widgetID ).fpWidgetData );
		if ( VERIFYN( kVStanev, boundData ) )
		{
			boundData->SetObjectBoundID( boundID );
		}
	}
	return CWidget( this, widgetID );
}

IWidgetsProvider* CWidgetsEditProvider::GetWidgetsProvider()
{
	return fWidgetsProvider;
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::UpdatePopupWidgetChoices(const char* widgetID, MCObjectHandle h, const TXString& paramName)
{
	CGenericParamProvider params( h );

	std::vector<std::pair<TXString, TXString>> arrParams;
	params.PopupGetChoices( paramName, arrParams );

	Sint32	id = fWidgetsProvider->GetWidgetIDByName( widgetID );
	CWidget widget = this->GetWidget( id );
	widget.ClearPopupItems();
	for(const auto& it : arrParams )
	{
		widget.AddPopupItem( it.first, it.second );
	}
	
	return widget;
}

CWidgetsEditProvider::CWidget CWidgetsEditProvider::UpdatePopupWidgetChoices(Sint32 widgetID, MCObjectHandle h, const TXString& paramName)
{
	CGenericParamProvider params( h );

	std::vector<std::pair<TXString, TXString>> arrParams;
	params.PopupGetChoices( paramName, arrParams );
	
	CWidget widget( this, widgetID );
	widget.ClearPopupItems();
	for(const auto& it : arrParams )
	{
		widget.AddPopupItem( it.first, it.second );
	}

	return widget;
}


// ------------------------------------------------------------------------------------------------------
CWidgetsEditProvider::CWidget::CWidget()
{
	fWidgetDef	= NULL;
}

CWidgetsEditProvider::CWidget::CWidget(CWidgetsEditProvider* provider, Sint32 widgetID)
{
	fWidgetDef	= provider &&  provider->fWidgetsProvider ? provider->fWidgetsProvider->GetWidgetByID( widgetID ) : NULL;
}

CWidgetsEditProvider::CWidget::CWidget(const CWidget& src)
{
	this->operator = ( src );
}

CWidgetsEditProvider::CWidget::~CWidget()
{
}

CWidgetsEditProvider::CWidget& CWidgetsEditProvider::CWidget::operator=(const CWidget& src)
{
	fWidgetDef	= src.fWidgetDef;
	return *this;
}

Sint32 CWidgetsEditProvider::CWidget::GetID() const
{
	return fWidgetDef ? fWidgetDef->fWidgetID : 0;
}

CWidgetsEditProvider::CWidget& CWidgetsEditProvider::CWidget::SetIndent(Sint32 indent)
{
	if ( fWidgetDef )
	{
		fWidgetDef->fWidgetIndentLevel	= indent;
	}

	return *this;
}

CWidgetsEditProvider::CWidget& CWidgetsEditProvider::CWidget::SetVisible(bool value)
{
	if ( fWidgetDef )
	{
		fWidgetDef->fWidgedVisible	= value;
	}

	return *this;
}

CWidgetsEditProvider::CWidget& CWidgetsEditProvider::CWidget::SetEnabled(bool value)
{
	if ( fWidgetDef )
	{
		fWidgetDef->fWidgetEnabled	= value;
	}

	return *this;
}

CWidgetsEditProvider::CWidget& CWidgetsEditProvider::CWidget::SetRed(bool value)
{
	if ( fWidgetDef )
	{
		fWidgetDef->fWidgetRed	= value;
	}

	return *this;
}

CWidgetsEditProvider::CWidget& CWidgetsEditProvider::CWidget::SetRotatedCoord(bool value)
{
	if ( fWidgetDef )
	{
		fWidgetDef->fWidgetRotatedCoord	= value;
	}

	return *this;
}

CWidgetsEditProvider::CWidget& CWidgetsEditProvider::CWidget::SetReadOnly(bool value)
{
	if ( fWidgetDef )
	{
		fWidgetDef->fReadOnly	= value;
	}

	return *this;
}

void CWidgetsEditProvider::CWidget::ClearPopupItems()
{
	IWidgetDataPopup*	popup	= fWidgetDef ? dynamic_cast<IWidgetDataPopup*>( fWidgetDef->fpWidgetData ) : NULL;
	if ( popup )
	{
		popup->Clear();
	}
}

void CWidgetsEditProvider::CWidget::AddPopupItem(const TXString& idName, const TXString& text)
{
	IWidgetDataPopup*	popup	= fWidgetDef ? dynamic_cast<IWidgetDataPopup*>( fWidgetDef->fpWidgetData ) : NULL;
	if ( popup )
	{
		popup->Add( idName, text );
	}
}


