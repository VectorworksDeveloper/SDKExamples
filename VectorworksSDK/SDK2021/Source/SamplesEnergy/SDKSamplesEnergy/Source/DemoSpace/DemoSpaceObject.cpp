#include "stdafx.h"
#include "DemoSpaceObject.h"

using namespace DemoSpace;

CDemoSpaceObject::CDemoSpaceObject(MCObjectHandle hObject)
	: VWParametricObj( hObject )
	, fSpaceEnergyData( IID_EnergySpace )
{
	fObjectData.LoadObjectData( fhObject );
	this->InitNewObject();

	fSpaceEnergyData->LoadCreate( fhObject );
}

CDemoSpaceObject::~CDemoSpaceObject()
{
}

void CDemoSpaceObject::InitNewObject()
{
	if ( fObjectData.fIsNew )
	{
		MCObjectHandle	hRecFormat	= VWRecordFormatObj::GetRecordFormat( "EnergyDemoSpace" );
		IEnergySpacePtr formatEnergyData( IID_EnergySpace );
		formatEnergyData->LoadCreate( hRecFormat );

		formatEnergyData->CopyDataTo( fhObject );

		fObjectData.fIsNew = false;
	}
}

void CDemoSpaceObject::DrawObject() const
{
	// create 2D representaion from the parametric path
	VWPolygon2DObj	baseObj( gSDK->DuplicateObject( this->GetObjectPath() ) );
	baseObj.SetClosed( true );

	VWPolygon2D		base;
	baseObj.GetPolygon( base );
	
	double thickness = fObjectData.fHeight;

	double volumeCuMM = 0;
	if ( Double1_GT_Double2( thickness, 0 ) )
	{
		// create 3D representation
		VWExtrudeObj ext( base, thickness );
		volumeCuMM	= VWStringConv::ConvertVolume_FromDocumentUnits( gSDK->ObjVolume( ext ) ); // CalcVolume returns document units.
	}

	fSpaceEnergyData->SetVolume( volumeCuMM / ( 1000.0 * 1000.0 * 1000.0 ), true ); // net volume cu m

	double areaSqM = 0;
	if ( fObjectData.fIsManualArea )
	{
		areaSqM = fObjectData.fArea;
	}
	else
	{
		areaSqM = base.GetArea() / ( 1000 * 1000 );
	}

	fSpaceEnergyData->SetArea( areaSqM, true ); // net area in sq m

	TXString	objName;
	gSDK->GetObjectName( fhObject, objName );

	fSpaceEnergyData->SetName( objName, true );
	fSpaceEnergyData->SetHeight( fObjectData.fHeight / 1000.0 );	// height in m
}

void CDemoSpaceObject::SaveObjectData()
{
	fSpaceEnergyData->Save();
	fObjectData.SaveObjectData( fhObject );
}
