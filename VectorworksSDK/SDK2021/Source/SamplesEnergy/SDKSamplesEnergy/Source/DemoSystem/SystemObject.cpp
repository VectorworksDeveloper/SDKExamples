#include "stdafx.h"
#include "SystemObject.h"

using namespace DemoSystem;

CSystemObject::CSystemObject(MCObjectHandle hObject, short systemType)
	: VWParametricObj( hObject )
	, fEASystems( VectorWorks::EnergyAnalysis::IID_EnergySystemObject )
{
	// init energy data
	fEASystems->LoadCreate( fhObject, (VectorWorks::EnergyAnalysis::ESystemObjectType)systemType );
}

CSystemObject::~CSystemObject()
{
}

void CSystemObject::DrawObject()
{
	VWPolygon2DObj poly;

	poly.AddCornerVertex( VWPoint2D( -50, -50 ) );
	poly.AddCornerVertex( VWPoint2D( -50, 50 ) );
	poly.AddCornerVertex( VWPoint2D( 50, 50 ) );
	poly.AddCornerVertex( VWPoint2D( 50, -50 ) );

	poly.SetClosed( true );
}

bool CSystemObject::Save()
{
	return fEASystems->Save();
}
