#include "stdafx.h"
#include "SpaceEnergyData.h"

using namespace DemoSpace::Data;

CSpaceEnergyData::CSpaceEnergyData()
{
	fHeight			= 3;
	fIsManualArea	= false;
	fArea			= 0;
	fIsNew			= true;
}

CSpaceEnergyData::~CSpaceEnergyData()
{
}

void CSpaceEnergyData::LoadObjectData(MCObjectHandle hObject)
{
	VWParametricObj	paramObj( hObject );

	if ( paramObj )
	{
		fHeight			= paramObj.GetParamReal( "Height" );
		fIsManualArea	= paramObj.GetParamBool( "IsManualArea" );
		fArea			= paramObj.GetParamReal( "Area" );
		fIsNew			= paramObj.GetParamBool( "__IsNew" );
	}
}

void CSpaceEnergyData::SaveObjectData(MCObjectHandle hObject) const
{
	VWParametricObj	paramObj( hObject );

	if ( paramObj )
	{
		paramObj.SetParamReal( "Height", fHeight );
		paramObj.SetParamBool( "IsManualArea", fIsManualArea );
		paramObj.SetParamReal( "Area", fArea );
		paramObj.SetParamBool( "__IsNew", fIsNew );
	}
}

void CSpaceEnergyData::LoadCurrentSettings()
{
	MCObjectHandle		hRecFormat	= VWRecordFormatObj::GetRecordFormat( "EnergyDemoSpace" );
	if ( hRecFormat == NULL || ( ! VWRecordFormatObj::IsRecordFormatObject( hRecFormat ) ) )
	{
		hRecFormat	= VWParametricObj::DefineCustomObject( "EnergyDemoSpace", false );
	}

	VWRecordFormatObj	recordFormat( hRecFormat );
	
	fHeight			= recordFormat.GetParamReal( "Height" );
	fIsManualArea	= recordFormat.GetParamBool( "IsManualArea" );
	fArea			= recordFormat.GetParamReal( "Area" );
	fIsNew			= recordFormat.GetParamBool( "__IsNew" );
}

void CSpaceEnergyData::SaveCurrentSettings() const
{
	MCObjectHandle		hRecFormat	= VWRecordFormatObj::GetRecordFormat( "EnergyDemoSpace" );
	if ( hRecFormat == NULL || ( ! VWRecordFormatObj::IsRecordFormatObject( hRecFormat ) ) )
	{
		hRecFormat	= VWParametricObj::DefineCustomObject( "EnergyDemoSpace", false );
	}

	VWRecordFormatObj	recordFormat( hRecFormat );

	recordFormat.SetParamReal( "Height", fHeight );
	recordFormat.SetParamBool( "IsManualArea", fIsManualArea );
	recordFormat.SetParamReal( "Area", fArea );
	recordFormat.SetParamBool( "__IsNew", true );
}
