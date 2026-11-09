//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtObjDemoSpace_ShapePane.h"
#include "UI/DlgSpaceSettings.h"

using namespace DemoSpace;
using namespace DemoSpace::UI;

namespace DemoSpace
{
	// --------------------------------------------------------------------------------------------------------
	const Sint32	kWidgetID_Settings			= 1;
	const Sint32	kWidgetID_Height			= 2;
	const Sint32	kWidgetID_IncludeChechBox	= 3;
	const Sint32	kWidgetID_IsManualArea		= 4;
	const Sint32	kWidgetID_Area				= 5;
	const Sint32	kWidgetID_AreaFactor		= 6;
}


// --------------------------------------------------------------------------------------------------------
CExtObjSpacesEnergy_ShapePane::CExtObjSpacesEnergy_ShapePane(IVWUnknown* parent)
	: VCOMImpl<IProviderShapePane>( parent )
	, fEnergyData( IID_EnergySpace )
	, fEnergyUnits( IID_EnergyUnits )
{
}

CExtObjSpacesEnergy_ShapePane::~CExtObjSpacesEnergy_ShapePane()
{
}

void CExtObjSpacesEnergy_ShapePane::Init(CodeRefID objectID, IExtendedProps* extProps)
{
	VWFC::PluginSupport::CWidgetsEditProvider	widgetProvider( extProps, objectID );

	widgetProvider.AddWidget( kWidgetID_Settings,			kWidgetButton,		TXResStr("ExtObjDemoSpace", "shapePane_Widget_SettingsButton") );
	widgetProvider.AddWidget( kWidgetID_Height,				"Height" );
	widgetProvider.AddWidget( kWidgetID_IncludeChechBox,	kWidgetBoolean,		TXResStr("ExtObjDemoSpace", "shapePane_Widget_IncludeChechBox") );
	widgetProvider.AddWidget( kWidgetID_IsManualArea,		"IsManualArea" ).SetIndent( 1 );
	widgetProvider.AddWidget( kWidgetID_Area,				kWidgetText,		TXResStr("ExtObjDemoSpace", "Area" ) ).SetIndent( 2 );
	widgetProvider.AddWidget( kWidgetID_AreaFactor,			kWidgetReal,		TXResStr("ExtObjDemoSpace", "shapePane_Widget_AreaFactor" ) ).SetIndent( 1 );
}

void CExtObjSpacesEnergy_ShapePane::Activate(MCObjectHandle hObject, const SSelectionContext& selContext)
{
	fhObject			= hObject;
	fSelectionContext	= selContext;

	fEnergyData->LoadCreate( hObject );
}

void CExtObjSpacesEnergy_ShapePane::Deactivate()
{
	fhObject = NULL;
}

void CExtObjSpacesEnergy_ShapePane::Update(IWidgetsProvider* widgetProvider)
{
	CSpaceEnergyData	objectData;
	objectData.LoadObjectData( fhObject );

	bool isIncludeInEnergyAnalysis = fEnergyData->GetIncludeInEnergyAnalysis();

	widgetProvider->GetWidgetByID( kWidgetID_IsManualArea )->fWidgetEnabled = isIncludeInEnergyAnalysis;
	widgetProvider->GetWidgetByID( kWidgetID_AreaFactor )->fWidgetEnabled	= isIncludeInEnergyAnalysis;

	widgetProvider->GetWidgetByID( kWidgetID_Area )->fWidgetEnabled			= objectData.fIsManualArea && isIncludeInEnergyAnalysis;
}

bool CExtObjSpacesEnergy_ShapePane::OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk)
{
	if ( data.fWidgetID == kWidgetID_Settings )
	{
		CSpaceEnergyData	objectData;
		objectData.LoadObjectData( fhObject );

		CDlgSpaceSettings dlg( objectData, fEnergyData );

		if ( dlg.RunDialogLayout( "SettingsDlg" ) == kDialogButton_Ok )
		{
			dlg.GetData( objectData );
			objectData.SaveObjectData( fhObject );

			fEnergyData->Save();
			outNeedReset	= true;
		}
		else
		{
			outNeedReset	= false;
		}
	}
	else if ( data.fWidgetID == kWidgetID_IncludeChechBox )
	{
		fEnergyData->SetIncludeInEnergyAnalysis( data.fWidgetAccess->GetValueBool( data.fViewWidget ) );
		fEnergyData->Save();
		
		outNeedReset	= true;
	}
	if ( data.fWidgetID == kWidgetID_Area )
	{
		CSpaceEnergyData	objectData;
		objectData.LoadObjectData( fhObject );

		TXString areaTxt = data.fWidgetAccess->GetValueString( data.fViewWidget );

		objectData.fArea = fEnergyUnits->ConvertString2X( EEnergyUnitType::SqM, areaTxt );

		objectData.SaveObjectData( fhObject );
		outNeedReset	= true;
	}
	else if ( data.fWidgetID == kWidgetID_AreaFactor )
	{
		fEnergyData->SetAreaFactor( data.fWidgetAccess->GetValueReal( data.fViewWidget ) );
		fEnergyData->Save();
		
		outNeedReset	= true;
	}

	return true;
}

bool CExtObjSpacesEnergy_ShapePane::TransferValue(SShapePaneWidgetTransferValue& data)
{
	bool handled = false;

	if(	data.fTransferToView == true )
	{
		if ( data.fWidgetID == kWidgetID_IncludeChechBox )
		{
			data.fWidgetAccess->SetValueBool( data.fViewWidget, fEnergyData->GetIncludeInEnergyAnalysis() );

			handled = true;
		}
		else if ( data.fWidgetID == kWidgetID_Area )
		{
			CSpaceEnergyData	objectData;
			objectData.LoadObjectData( fhObject );

			TXString areaTxt;
			fEnergyUnits->ConvertX2Document( EEnergyUnitType::SqM, objectData.fArea, areaTxt );

			data.fWidgetAccess->SetValueString( data.fViewWidget, areaTxt );

			handled = true;
		}
		else if ( data.fWidgetID == kWidgetID_AreaFactor )
		{
			data.fWidgetAccess->SetValueReal( data.fViewWidget, fEnergyData->GetAreaFactor() );

			handled = true;
		}
	}

	return handled;
}
