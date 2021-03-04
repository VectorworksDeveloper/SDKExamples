#include "stdafx.h"
#include "WindowEnergyData.h"

using namespace DemoWindow::Data;

CWindowEnergyData::CWindowEnergyData()
{
}


CWindowEnergyData::~CWindowEnergyData()
{
}
// --------------------------------------------------------------------------------------------------------
// Load data from object.
// --------------------------------------------------------------------------------------------------------
void CWindowEnergyData::LoadObjectData(MCObjectHandle hObject)
{
	VWParametricObj	paramObj( hObject );
	if ( paramObj )
	{
		fIsNew			= paramObj.GetParamBool( "__IsNew" );
		fHeight			= paramObj.GetParamReal( "Height" );
		fWidth			= paramObj.GetParamReal( "Width" );;
		fHasTilting		= paramObj.GetParamBool( "HasTilting" );

		TXString type	= paramObj.GetParamString( "Type" );

		fType			= EType::Window;
		if ( type == "Door" )
		{
			fType = EType::Door;
		}
		else if( type == "Win/Door" )
		{
			fType = EType::WinDoor;
		}
	}
}

// --------------------------------------------------------------------------------------------------------
// Save data to object.
// --------------------------------------------------------------------------------------------------------
void CWindowEnergyData::SaveObjectData(MCObjectHandle hObject) const
{
	VWParametricObj	paramObj( hObject );
	if ( paramObj )
	{
		paramObj.SetParamBool( "__IsNew",		fIsNew );
		paramObj.SetParamReal( "Height",		fHeight );
		paramObj.SetParamReal( "Width",			fWidth );
		paramObj.SetParamBool( "HasTilting",	fHasTilting );

		TXString type = "Window";
		if ( fType == EType::Door )
		{
			type = "Door";
		}
		else if( fType == EType::WinDoor )
		{
			type = "Win/Door";
		}

		paramObj.SetParamString( "Type",		type );
	}
}

// --------------------------------------------------------------------------------------------------------
// Load data from record format. This function is used by preference dialog.
// --------------------------------------------------------------------------------------------------------
void CWindowEnergyData::LoadCurrentSettings()
{
	MCObjectHandle		hRecFormat	= VWRecordFormatObj::GetRecordFormat( "EnergyDemoWindow" );
	if ( hRecFormat == NULL || ( ! VWRecordFormatObj::IsRecordFormatObject( hRecFormat ) ) )
	{
		hRecFormat	= VWParametricObj::DefineCustomObject( "EnergyDemoWindow", false );
	}

	VWRecordFormatObj	recordFormat( hRecFormat );
	fIsNew			= recordFormat.GetParamBool( "__IsNew" );
	fHeight			= recordFormat.GetParamReal( "Height" );
	fWidth			= recordFormat.GetParamReal( "Width" );;
	fHasTilting		= recordFormat.GetParamBool( "HasTilting" );

	TXString type	= recordFormat.GetParamString( "Type" );

	fType			= EType::Window;
	if ( type == "Door" )
	{
		fType = EType::Door;
	}
	else if( type == "Win/Door" )
	{
		fType = EType::WinDoor;
	}
}

// --------------------------------------------------------------------------------------------------------
// Save data to record format. This function is used by preference dialog.
// --------------------------------------------------------------------------------------------------------
void CWindowEnergyData::SaveCurrentSettings() const
{
	MCObjectHandle		hRecFormat	= VWRecordFormatObj::GetRecordFormat( "EnergyDemoWindow" );
	if ( hRecFormat == NULL || ( ! VWRecordFormatObj::IsRecordFormatObject( hRecFormat ) ) )
	{
		hRecFormat	= VWParametricObj::DefineCustomObject( "EnergyDemoSpace", false );
	}

	VWRecordFormatObj	recordFormat( hRecFormat );
	recordFormat.SetParamBool( "__IsNew",		fIsNew );
	recordFormat.SetParamReal( "Height",		fHeight );
	recordFormat.SetParamReal( "Width",			fWidth );
	recordFormat.SetParamBool( "HasTilting",	fHasTilting );

	TXString type = "Window";
	if ( fType == EType::Door )
	{
		type = "Door";
	}
	else if( fType == EType::WinDoor )
	{
		type = "Win/Door";
	}

	recordFormat.SetParamString( "Type",		type );
}
