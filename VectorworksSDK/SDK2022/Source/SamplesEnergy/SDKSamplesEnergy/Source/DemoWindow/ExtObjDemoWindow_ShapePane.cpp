//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtObjDemoWindow_ShapePane.h"
#include "Data/WindowEnergyData.h"
#include "UI/DlgWindowSettings.h"

using namespace DemoWindow;

namespace DemoWindow
{
	// --------------------------------------------------------------------------------------------------------
	const Sint32	kWidgetID_Settings			= 1;
	const Sint32	kWidgetID_Sep_General		= 2;
	const Sint32	kWidgetID_Type				= 3;
	const Sint32	kWidgetID_Height			= 4;
	const Sint32	kWidgetID_Width				= 5;
	const Sint32	kWidgetID_HasTilting		= 6;
	const Sint32	kWidgetID_Sep_EA			= 7;
	const Sint32	kWidgetID_IncludeToEA		= 8;
	const Sint32	kWidgetID_UValueCalcMode	= 9;
	const Sint32	kWidgetID_UValueMan			= 10;
	const Sint32	kWidgetID_Frame				= 11;
	const Sint32	kWidgetID_WindowGlazing		= 12;
	const Sint32	kWidgetID_Sep_Shading		= 13;
	const Sint32	kWidgetID_Shading			= 14;
	const Sint32	kWidgetID_General			= 15;
	const Sint32	kWidgetID_Surrounding		= 16;
	const Sint32	kWidgetID_SumShading		= 17;
	const Sint32	kWidgetID_AddShading		= 18;
	const Sint32	kWidgetID_DoorType			= 19;
}


// --------------------------------------------------------------------------------------------------------
CExtObjDemoWindow_ShapePane::CExtObjDemoWindow_ShapePane(IVWUnknown* parent)
	: VCOMImpl<IProviderShapePane>( parent )
	, fEAUnits( VectorWorks::EnergyAnalysis::IID_EnergyUnits )
	, fEAWinDoor( VectorWorks::EnergyAnalysis::IID_EnergyBuildingElementWinDoor )
{
}

CExtObjDemoWindow_ShapePane::~CExtObjDemoWindow_ShapePane()
{
}

void CExtObjDemoWindow_ShapePane::Init(CodeRefID objectID, IExtendedProps* extProps)
{
	VWFC::PluginSupport::CWidgetsEditProvider	widgetProvider( extProps, objectID );

	widgetProvider.AddWidget( kWidgetID_Settings,			kWidgetButton,			TXResStr("ExtObjDemoWindow", "SettingsButton")		);
	widgetProvider.AddWidget( kWidgetID_Sep_General,		kWidgetSeparator,		TXResStr("ExtObjDemoWindow", "SeparatorGeneral")	);
	widgetProvider.AddWidget( kWidgetID_Type,				"Type"																		);
	widgetProvider.AddWidget( kWidgetID_Height,				"Height"																	);
	widgetProvider.AddWidget( kWidgetID_Width,				"Width"																		);
	widgetProvider.AddWidget( kWidgetID_HasTilting,			"HasTilting"																);
	widgetProvider.AddWidget( kWidgetID_Sep_EA,				kWidgetSeparator,		TXResStr("ExtObjDemoWindow", "SeparatorEA")			);
	widgetProvider.AddWidget( kWidgetID_IncludeToEA,		kWidgetBoolean,			TXResStr("ExtObjDemoWindow", "IncludeToEA")			);
	// show U-Value or R-Value depending on settings
	if ( fEAUnits && fEAUnits->IsUsedUValue() )
	{
		widgetProvider.AddWidget( kWidgetID_UValueCalcMode,	kWidgetPopUp,			TXResStr("ExtObjDemoWindow", "UValueCalcMode")		);
		widgetProvider.AddWidget( kWidgetID_UValueMan,		kWidgetText,			TXResStr("ExtObjDemoWindow", "UValueManInput")		);
	}
	else
	{
		widgetProvider.AddWidget( kWidgetID_UValueCalcMode,	kWidgetPopUp,			TXResStr("ExtObjDemoWindow", "RValueCalcMode")		);
		widgetProvider.AddWidget( kWidgetID_UValueMan,		kWidgetText,			TXResStr("ExtObjDemoWindow", "RValueManInput")		);
	}
 	
	// Add Window Frame popup...
	widgetProvider.AddWidget( kWidgetID_Frame,				kWidgetPopUp,			TXResStr("ExtObjDemoWindow", "WindowFrame")				);
		// ... and set the type of energy data. This is necessary for dealing with events.
	SWidgetDefinition* widgetDef	= widgetProvider->GetWidgetByID( kWidgetID_Frame );
	widgetDef->fEnergyDataType		= EEnergyDataType::WindowOrDoorFrame;

	// Add Window Glazing popup...
	widgetProvider.AddWidget( kWidgetID_WindowGlazing,		kWidgetPopUp,			TXResStr("ExtObjDemoWindow", "WindowGlazing")		);
		// ... and set the type of energy data. This is necessary for dealing with events.
	widgetDef	= widgetProvider->GetWidgetByID( kWidgetID_WindowGlazing );
	widgetDef->fEnergyDataType		= EEnergyDataType::WindowOrDoorGlazing;

	// Add DoorType popup...
	widgetProvider.AddWidget( kWidgetID_DoorType,			kWidgetPopUp,			TXResStr("ExtObjDemoWindow", "DoorType")			);
		// ... and set the type of energy data. This is necessary for dealing with events.
	widgetDef	= widgetProvider->GetWidgetByID( kWidgetID_DoorType );
	widgetDef->fEnergyDataType		= EEnergyDataType::DoorType;

	widgetProvider.AddWidget( kWidgetID_Sep_Shading,		kWidgetSeparator,		""	 												);
	widgetProvider.AddWidget( kWidgetID_Shading,			kWidgetStaticText,		TXResStr("ExtObjDemoWindow", "Shading")				);

	// Add Shading popup...
	widgetProvider.AddWidget( kWidgetID_General,			kWidgetPopUp,			TXResStr("ExtObjDemoWindow", "General")				);
		// ... and set the type of energy data. This is necessary for dealing with events.
	widgetDef	= widgetProvider->GetWidgetByID( kWidgetID_General );
	widgetDef->fEnergyDataType		= EEnergyDataType::WindowOrDoorGeneralShading;
	
	// Add Surrounding Shading popup...
	widgetProvider.AddWidget( kWidgetID_Surrounding,		kWidgetPopUp,			TXResStr("ExtObjDemoWindow", "Surrounding")			);
	// ... and set the type of energy data. This is necessary for dealing with events.
	widgetDef	= widgetProvider->GetWidgetByID( kWidgetID_Surrounding );
	widgetDef->fEnergyDataType		= EEnergyDataType::WindowOrDoorSurroundingShading;

	// Add Summer Shading popup...
	widgetProvider.AddWidget( kWidgetID_SumShading,			kWidgetPopUp,			TXResStr("ExtObjDemoWindow", "SumShading")			);
	// ... and set the type of energy data. This is necessary for dealing with events.
	widgetDef	= widgetProvider->GetWidgetByID( kWidgetID_SumShading );
	widgetDef->fEnergyDataType		= EEnergyDataType::WindowOrDoorSummerShading;
	
	// Add Advanced Shading popup...
	widgetProvider.AddWidget( kWidgetID_AddShading,			kWidgetPopUp,			TXResStr("ExtObjDemoWindow", "AdvShading")			);
	// ... and set the type of energy data. This is necessary for dealing with events.
	widgetDef	= widgetProvider->GetWidgetByID( kWidgetID_AddShading );
	widgetDef->fEnergyDataType		= EEnergyDataType::WindowOrDoorAdditionalShading;

	widgetProvider->GetWidgetByID( kWidgetID_DoorType )->fWidgedVisible	= false;
}

void CExtObjDemoWindow_ShapePane::Activate(MCObjectHandle hObject, const SSelectionContext& selContext)
{
	fhObject			= hObject;
	fSelectionContext	= selContext;
	
	fEAWinDoor->LoadCreate( fhObject );	// set the current object to the interface
}

void CExtObjDemoWindow_ShapePane::Deactivate()
{
	fhObject	= NULL;
}

void CExtObjDemoWindow_ShapePane::Update(IWidgetsProvider* widgetProvider)
{
	// disable manual input for u value if the calculation are auto
	SWidgetDefinition* widgetUValMan		= widgetProvider->GetWidgetByID( kWidgetID_UValueMan );
	SWidgetDefinition* widgetFrame			= widgetProvider->GetWidgetByID( kWidgetID_Frame );
	SWidgetDefinition* widgetGlazing		= widgetProvider->GetWidgetByID( kWidgetID_WindowGlazing );
	SWidgetDefinition* widgetDoorType		= widgetProvider->GetWidgetByID( kWidgetID_DoorType );
	SWidgetDefinition* widgetUValCalcMode	= widgetProvider->GetWidgetByID( kWidgetID_UValueCalcMode );
	SWidgetDefinition* widgetShading		= widgetProvider->GetWidgetByID( kWidgetID_Shading );
	SWidgetDefinition* widgetGeneral		= widgetProvider->GetWidgetByID( kWidgetID_General );
	SWidgetDefinition* widgetSurround		= widgetProvider->GetWidgetByID( kWidgetID_Surrounding );
	SWidgetDefinition* widgetSumShade		= widgetProvider->GetWidgetByID( kWidgetID_SumShading );
	SWidgetDefinition* widgetAddShade		= widgetProvider->GetWidgetByID( kWidgetID_AddShading );

	if ( widgetUValMan && widgetFrame && widgetGlazing && widgetDoorType && widgetUValCalcMode && widgetShading
						&& widgetGeneral && widgetSurround && widgetSumShade && widgetAddShade )
	{
		Data::CWindowEnergyData	data;
		data.LoadObjectData( fhObject );

		widgetFrame->fWidgedVisible			= data.fType != DemoWindow::Data::EType::Door;
		widgetGlazing->fWidgedVisible		= data.fType != DemoWindow::Data::EType::Door;
		widgetDoorType->fWidgedVisible		= data.fType != DemoWindow::Data::EType::Window;

		bool bInclude						= fEAWinDoor->GetIncludeInEnergyAnalysis();

		widgetUValCalcMode->fWidgetEnabled	= bInclude;
		widgetUValMan->fWidgetEnabled		= bInclude && fEAWinDoor->GetUValueCalculationMode() == VectorWorks::EnergyAnalysis::ECalculationMode::Manual;
		widgetFrame->fWidgetEnabled			= bInclude;
		widgetGlazing->fWidgetEnabled		= bInclude;
		widgetShading->fWidgetEnabled		= bInclude;
		widgetGeneral->fWidgetEnabled		= bInclude;
		widgetSurround->fWidgetEnabled		= bInclude;
		widgetSumShade->fWidgetEnabled		= bInclude;
		widgetAddShade->fWidgetEnabled		= bInclude;
		widgetDoorType->fWidgetEnabled		= bInclude;
	}
}

bool CExtObjDemoWindow_ShapePane::OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk)
{
	switch (data.fWidgetID)
	{
	case kWidgetID_Settings:
		outNeedReset	= this->OnSettingsButton();
		break;
	case kWidgetID_HasTilting:
		outNeedReset	= this->OnTilting( data.fWidgetAccess->GetValueBool( data.fViewWidget ) );
		break;
	case kWidgetID_IncludeToEA:
		outNeedReset	= this->OnIncludeToEACalc( data.fWidgetAccess->GetValueBool( data.fViewWidget ) );
		break;
	case kWidgetID_UValueCalcMode:
		fEAWinDoor->WidgetUI_Select_UValueCalculation( data );
		fEAWinDoor->Save();
		outNeedReset	= true;
		break;
	case kWidgetID_UValueMan:
		outNeedReset	= this->OnUValueManual( data.fWidgetAccess->GetValueString( data.fViewWidget ) );
		break;
	}

	return true;
}

bool CExtObjDemoWindow_ShapePane::TransferValue(SShapePaneWidgetTransferValue& data)
{
	bool	hasHandled	= false;

	// update widgets to show energy data
	if(	data.fTransferToView == true )
	{
		if ( data.fWidgetID == kWidgetID_IncludeToEA )
		{
			data.fWidgetAccess->SetValueBool( data.fViewWidget, fEAWinDoor->GetIncludeInEnergyAnalysis() );

			hasHandled = true;
		}
		else if ( data.fWidgetID == kWidgetID_UValueCalcMode)
		{
			// Energy plugin will process the widget for us. Just pass the data.
 			fEAWinDoor->WidgetUI_Fill_UValueCalculation( data );

 			hasHandled = true;
		}
		else if ( data.fWidgetID == kWidgetID_UValueMan )
		{
			// if the calculation mode of U-value calcualtion is manual
			if ( fEAWinDoor->GetUValueCalculationMode() == VectorWorks::EnergyAnalysis::ECalculationMode::Manual )
			{
				double uValue = fEAWinDoor->GetUValue( true );	// get the U value in W/(m^2 K)
				TXString uValueTxt;
				if ( fEAUnits->IsUsedUValue() )
				{
					// convert it to document units to show the value with units
					fEAUnits->ConvertX2Document( VectorWorks::EnergyAnalysis::EEnergyUnitType::WPSqMK, uValue, uValueTxt );
				}
				else
				{
					// calclate the R-value
					if ( ! ::DoubleIsNearlyZero( uValue ) )
					{
						uValue = 1 / uValue;
					}
					// convert it to document units to show the value with units
					fEAUnits->ConvertX2Document( VectorWorks::EnergyAnalysis::EEnergyUnitType::SqMKPW, uValue, uValueTxt );
				}

				data.fWidgetAccess->SetValueString( data.fViewWidget, uValueTxt );
			}
			else
			{
				// if the calculation mode of U-value calcualtion is auto
				if ( data.fWidgetAccess->GetValueString( data.fViewWidget ).IsEmpty() )
				{
					double uValue = 0.0;
										
					TXString uValueTxt;
					if ( fEAUnits->IsUsedUValue() )
					{
						// convert it to document units to show the value with units
						fEAUnits->ConvertX2Document( VectorWorks::EnergyAnalysis::EEnergyUnitType::WPSqMK, uValue, uValueTxt );
					}
					else
					{
						// convert it to document units to show the value with units
						fEAUnits->ConvertX2Document( VectorWorks::EnergyAnalysis::EEnergyUnitType::SqMKPW, uValue, uValueTxt );
					}

					data.fWidgetAccess->SetValueString( data.fViewWidget, uValueTxt );
				}
			}
			
			hasHandled = true;
		}
	}

	return hasHandled;
}

bool CExtObjDemoWindow_ShapePane::OnSettingsButton()
{
	bool	needReset	= false;

	Data::CWindowEnergyData	data;
	data.LoadObjectData( fhObject );

	UI::CDlgWindowSettings	dlg( data, fEAWinDoor );
	if ( dlg.RunDialogLayout( "SettingsDlg" ) == kDialogButton_Ok )
	{
		dlg.GetData( data, fEAWinDoor );
		data.SaveObjectData( fhObject );

		fEAWinDoor->Save();
		needReset	= true;
	}

	return needReset;
}

bool CExtObjDemoWindow_ShapePane::OnIncludeToEACalc(bool value)
{
	fEAWinDoor->SetIncludeInEnergyAnalysis( value );
	fEAWinDoor->Save();

	return true;
}

bool CExtObjDemoWindow_ShapePane::OnUValueManual(const TXString& value)
{
	double uValue = 0.0;
	
	if ( fEAUnits->IsUsedUValue() )
	{
		uValue = fEAUnits->ConvertString2X( VectorWorks::EnergyAnalysis::EEnergyUnitType::WPSqMK, value );
	}
	else
	{
		// calculate R value
		uValue = fEAUnits->ConvertString2X( VectorWorks::EnergyAnalysis::EEnergyUnitType::SqMKPW, value );

		if ( ! ::DoubleIsNearlyZero( uValue ) )
		{
			uValue = 1 / uValue;
		}
	}

	fEAWinDoor->SetUValue( uValue, true );
	fEAWinDoor->Save();

	return true;
}

bool CExtObjDemoWindow_ShapePane::OnTilting(bool value)
{
	// this affect summer ventilation data
	VectorWorks::EnergyAnalysis::SWinDoorSummerVentilationData	ventData;
	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayGF, ventData );
	ventData.fTilting	= value;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayGF, ventData );

	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayUF, ventData );
	ventData.fTilting	= value;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayUF, ventData );

	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::Night, ventData );
	ventData.fTilting	= value;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::Night, ventData );

	fEAWinDoor->Save();

	return true;
}

bool CExtObjDemoWindow_ShapePane::OnTypeChange(Sint32 value)
{
	Data::CWindowEnergyData	data;
	data.LoadObjectData( fhObject );
	data.fType	= (Data::EType)value;
	data.SaveObjectData( fhObject );

	return true;
}

