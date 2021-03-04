#include "StdAfx.h"

#include "ExtObjDemoSystem_ShapePane.h"

using namespace DemoSystem;
using namespace VectorWorks::EnergyAnalysis;

namespace DemoSystem
{
	// --------------------------------------------------------------------------------------------------------
	const Sint32 kWidgetID_SystemName		= 1;
	const Sint32 kWidgetID_ParamNamePopup	= 2;
	const Sint32 kWidgetID_EditParamValue	= 3;
}


// --------------------------------------------------------------------------------------------------------
CExtObjDemoSystem_ShapePane::CExtObjDemoSystem_ShapePane(IVWUnknown* parent)
	: VCOMImpl<IProviderShapePane>( parent )
	, fEASystem( IID_EnergySystemObject )
{
	fParamInfo.fBoolValue			= false;
	fParamInfo.fIntValue			= 0;
	fParamInfo.fDoubleValue			= 0.0;
	fParamInfo.fStrValue			= "";
	fSystemName						= "";
}

CExtObjDemoSystem_ShapePane::~CExtObjDemoSystem_ShapePane()
{
}

void CExtObjDemoSystem_ShapePane::Init(CodeRefID objectID, IExtendedProps* extProps)
{
	VWFC::PluginSupport::CWidgetsEditProvider	widgetProvider( extProps, objectID );

	widgetProvider.AddWidget( kWidgetID_ParamNamePopup,	kWidgetPopUp,	TXResStr("ExtObjDemoSystem", "ParamNamePopup")		);
	widgetProvider.AddWidget( kWidgetID_EditParamValue,	kWidgetButton,	TXResStr("ExtObjDemoSystem", "EditParamButton")		);
	widgetProvider.AddWidget( kWidgetID_SystemName,		kWidgetText,	TXResStr("ExtObjDemoSystem", "SystemName")			);
}

void CExtObjDemoSystem_ShapePane::Activate(MCObjectHandle hObject, const SSelectionContext& selContext)
{
	fhObject			= hObject;
	fSelContext			= selContext;

	Sint32 sysType = VWParametricObj( fhObject ).GetParamLong( "SystemObjectType" );

	fEASystem->LoadCreate( fhObject, (ESystemObjectType)sysType );	// set the current object to the interface

	fEASystem->GetSystemName( fSystemName );
}

void CExtObjDemoSystem_ShapePane::Deactivate()
{
	fhObject	= NULL;
}

void CExtObjDemoSystem_ShapePane::Update(IWidgetsProvider* widgetProvider)
{
	widgetProvider->GetWidgetByID( kWidgetID_ParamNamePopup )->fWidgetEnabled = !fSelContext.fIsMultipleSelection;
	widgetProvider->GetWidgetByID( kWidgetID_EditParamValue )->fWidgetEnabled = !fSelContext.fIsMultipleSelection;
	widgetProvider->GetWidgetByID( kWidgetID_SystemName )->fWidgetEnabled = !fSelContext.fIsMultipleSelection;
}

bool CExtObjDemoSystem_ShapePane::OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk)
{
	switch (data.fWidgetID)
	{
		case kWidgetID_SystemName:
		{
			fSystemName = data.fWidgetAccess->GetValueString( data.fViewWidget );
			fEASystem->SetSystemName( fSystemName );
			fEASystem->Save();
			break;
		}

		case kWidgetID_EditParamValue:
		{
			outNeedReset	= this->OnEditParamButton();
			break;
		}

		case kWidgetID_ParamNamePopup:
		{
			SWidgetDefinition*		paramNameWidget = data.fWidgetAccess->GetWidgetProvider()->GetWidgetByID( kWidgetID_ParamNamePopup );
			IWidgetDataPopup*		paramNameData	= dynamic_cast<IWidgetDataPopup*>( paramNameWidget->fpWidgetData );
			outNeedReset							= this->OnParamNamePopup( data.fWidgetAccess->GetValueString( data.fViewWidget ), paramNameData );
			break;
		}
	}

	return true;
}

bool CExtObjDemoSystem_ShapePane::TransferValue(SShapePaneWidgetTransferValue& data)
{
	bool handled = false;

	if(	data.fTransferToView == true )
	{
		if ( data.fWidgetID == kWidgetID_ParamNamePopup )
		{
			this->FillParamNamePopup( data );
			handled = true;
		}
		else if( data.fWidgetID == kWidgetID_SystemName )
		{
			data.fWidgetAccess->SetValueString( data.fViewWidget, fSystemName );
		}
	}
	else
	{
		handled = true;
	}

	return handled;
}

bool CExtObjDemoSystem_ShapePane::OnEditParamButton()
{
	bool	needReset	= false;

	UI::CDlgSysObjEditParam	dlg( fParamInfo );
	if ( dlg.RunDialogLayout( "DlgSysObjEditParam" ) == kDialogButton_Ok )
	{
		switch( fParamInfo.fParamType )
		{
			case CSystemDataParam::EType::Bool:
			{
				fParamInfo.fBoolValue = dlg.GetParamValueBool();
				fEASystem->SetParamValue( fParamInfo.fName, fParamInfo.fBoolValue );
				break;
			}

			case CSystemDataParam::EType::Int:
			{
				fParamInfo.fIntValue = dlg.GetParamValueInt();
				fEASystem->SetParamValue( fParamInfo.fName, fParamInfo.fIntValue );
				break;
			}

			case CSystemDataParam::EType::Double:
			{
				fParamInfo.fDoubleValue = dlg.GetParamValueDouble();
				fEASystem->SetParamValue( fParamInfo.fName, fParamInfo.fDoubleValue );
				break;
			}

			case CSystemDataParam::EType::String:
			{
				fParamInfo.fStrValue = dlg.GetParamValueString();
				fEASystem->SetParamValue( fParamInfo.fName, fParamInfo.fStrValue );
				break;
			}
		}

		fEASystem->Save();
	}

	return needReset;
}

bool CExtObjDemoSystem_ShapePane::OnParamNamePopup(const TXString& selParamName, IWidgetDataPopup* paramNameData)
{
	bool	needReset	= false;
	size_t	selIndex	= 0;

	if( paramNameData->GetIndexByIDName( selParamName, selIndex ) )
	{
		EEnergyUnitType			unitType;
		fEASystem->GetParamInfo( selIndex, fParamInfo.fName, fParamInfo.fParamType, unitType );
		VWParametricObj( fhObject ).SetParamAsString( "ParamName", fParamInfo.fName );

		switch( fParamInfo.fParamType )
		{
			case CSystemDataParam::EType::Bool:
			{
				fEASystem->GetParamValue( selIndex, fParamInfo.fBoolValue );
				break;
			}

			case CSystemDataParam::EType::Int:
			{
				fEASystem->GetParamValue( selIndex, fParamInfo.fIntValue );
				break;
			}

			case CSystemDataParam::EType::Double:
			{
				fEASystem->GetParamValue( selIndex, fParamInfo.fDoubleValue );
				break;
			}

			case CSystemDataParam::EType::String:
			{
				fEASystem->GetParamValue( selIndex, fParamInfo.fStrValue );
				break;
			}
		}
	}

	return needReset;
}

void CExtObjDemoSystem_ShapePane::FillParamNamePopup(SShapePaneWidgetTransferValue& data)
{
	CSystemDataParam::EType	valueType;
	EEnergyUnitType			unitType;
	size_t					paramsCnt		= fEASystem->GetParamsCnt();
	TXString				name;
	SWidgetDefinition*		paramNameWidget = data.fWidgetAccess->GetWidgetProvider()->GetWidgetByID( kWidgetID_ParamNamePopup );
	IWidgetDataPopup*		paramNameData	= dynamic_cast<IWidgetDataPopup*>( paramNameWidget->fpWidgetData );
	TXString				paramName		= VWParametricObj( fhObject ).GetParamAsString( "ParamName" );
	paramNameData->Clear();
	size_t selIndex = 0;

	for( size_t i = 0; i < paramsCnt; i++ )
	{
		fEASystem->GetParamInfo( i, name, valueType, unitType );
		paramNameData->Add( name, name );
		if( name == paramName )
		{
			selIndex = i;
		}
	}

	if( !paramName.IsEmpty() )
	{
		data.fWidgetAccess->SetValueString( data.fViewWidget, paramName );
	}

	fEASystem->GetParamInfo( selIndex, fParamInfo.fName, fParamInfo.fParamType, unitType );

	switch( valueType )
	{
		case CSystemDataParam::EType::Bool:
		{
			fEASystem->GetParamValue( selIndex, fParamInfo.fBoolValue );
			break;
		}

		case CSystemDataParam::EType::Int:
		{
			fEASystem->GetParamValue( selIndex, fParamInfo.fIntValue );
			break;
		}

		case CSystemDataParam::EType::Double:
		{
			fEASystem->GetParamValue( selIndex, fParamInfo.fDoubleValue );
			break;
		}

		case CSystemDataParam::EType::String:
		{
			fEASystem->GetParamValue( selIndex, fParamInfo.fStrValue );
			break;
		}
	}
}

