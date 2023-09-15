#include "stdafx.h"
#include "WindowObject.h"

using namespace DemoWindow;

CWindowObject::CWindowObject(MCObjectHandle hObject)
: VWParametricObj( hObject )
, fEAWinDoor( VectorWorks::EnergyAnalysis::IID_EnergyBuildingElementWinDoor )
{
	fEAData.LoadObjectData( fhObject );
	this->InitNewObject();

	// init energy data
	fEAWinDoor->LoadCreate( fhObject );
	fEAData.fIncludeToEA	= fEAWinDoor->GetIncludeInEnergyAnalysis();
}

CWindowObject::~CWindowObject()
{
}

void CWindowObject::DrawObject()
{
	switch ( fEAData.fType )
	{
	case DemoWindow::Data::EType::Window:
		this->DrawWindow( VWPoint3D(0, 0, 0) );
		fEAWinDoor->SetType( VectorWorks::EnergyAnalysis::EWinDoorType::Window );
		break;
	case DemoWindow::Data::EType::Door:
		this->DrawDoor( VWPoint3D(0, 0, 0) );
		fEAWinDoor->SetType( VectorWorks::EnergyAnalysis::EWinDoorType::Door );
		break;
	case DemoWindow::Data::EType::WinDoor:
		this->DrawWinDoor( VWPoint3D(0, 0, 0) );
		fEAWinDoor->SetType( VectorWorks::EnergyAnalysis::EWinDoorType::WinDoor );
		break;
	}
}

void CWindowObject::SaveObjectData()
{
	fEAWinDoor->Save();
	fEAData.SaveObjectData( fhObject );
}

void CWindowObject::UpdateData()
{
	// this will affect area, glazing area, frame length, etc.

	fEAWinDoor->SetArea( (fEAData.fHeight * fEAData.fWidth) / 1000000.0, true );	// !! be careful! The inerface expects sq meters !!
	
	// width is changed also
	fEAWinDoor->SetWidth( fEAData.fWidth / 1000.0 );	// !! be careful! The inerface expects meters !!

	// glazing area is changed also
	
	if( fEAData.fType == DemoWindow::Data::EType::Window )
	{
		double	glazingArea	= (fEAData.fWidth-kFrameThickness*2) * (fEAData.fHeight-kFrameThickness*2);
		fEAWinDoor->SetGlazingArea( glazingArea / 1000000.0 );	// !! be careful! The inerface expects sq meters !!
	}
	else if( fEAData.fType == DemoWindow::Data::EType::Door )
	{
		double glazingArea = (fEAData.fWidth-kFrameThickness*2) * (fEAData.fHeight-kFrameThickness);
		fEAWinDoor->SetGlazingArea( glazingArea / 1000000.0 );	// !! be careful! The inerface expects sq meters !!
	}
	else
	{
		double width		= fEAData.fWidth / 2.0;
		double glazingArea	= (width-kFrameThickness*2) * (fEAData.fHeight-kFrameThickness*2);

		fEAWinDoor->SetGlazingArea( glazingArea / 1000000.0 );	// !! be careful! The inerface expects sq meters !!
		fEAWinDoor->SetFrameArea( (fEAData.fHeight * width) / 1000000.0 - glazingArea / 1000000.0 );

		glazingArea = (width-kFrameThickness*2) * (fEAData.fHeight-kFrameThickness);
		fEAWinDoor->SetGlazingArea( glazingArea / 1000000.0, VectorWorks::EnergyAnalysis::EValueType::HybridDoor );	// !! be careful! The inerface expects sq meters !!
		fEAWinDoor->SetFrameArea( (fEAData.fHeight * width) / 1000000.0 - glazingArea / 1000000.0, VectorWorks::EnergyAnalysis::EValueType::HybridDoor );
	}

	// glazing length is changed also
	if( fEAData.fType == DemoWindow::Data::EType::Window )
	{
		double	glazingLength	= (fEAData.fHeight-kFrameThickness*2)*2 + (fEAData.fWidth-kFrameThickness*2)*2;
		fEAWinDoor->SetGlazingLength( glazingLength / 1000.0 );	// !! be careful! The inerface expects meters !!
	}
	else if( fEAData.fType == DemoWindow::Data::EType::Door )
	{
		double glazingLength = (fEAData.fHeight-kFrameThickness)*2 + (fEAData.fWidth-kFrameThickness*2)*2;
		fEAWinDoor->SetGlazingLength( glazingLength / 1000.0 );	// !! be careful! The inerface expects meters !!
	}
	else
	{
		double width			= fEAData.fWidth / 2.0;
		double glazingLength	= (fEAData.fHeight-kFrameThickness*2)*2 + (width-kFrameThickness*2)*2;
		fEAWinDoor->SetGlazingLength( glazingLength / 1000.0 );	// !! be careful! The inerface expects meters !!

		glazingLength = (fEAData.fHeight-kFrameThickness)*2 + (width-kFrameThickness*2)*2;
		fEAWinDoor->SetGlazingLength( glazingLength / 1000.0, VectorWorks::EnergyAnalysis::EValueType::HybridDoor );	// !! be careful! The inerface expects meters !!
	}

	// frame length is changed also
	
	if( fEAData.fType == DemoWindow::Data::EType::Window )
	{
		double	frameLength	= fEAData.fHeight*2 + fEAData.fWidth*2;
		fEAWinDoor->SetFrameLength( frameLength / 1000.0 );	// !! be careful! The inerface expects meters !!
	}
	else if( fEAData.fType == DemoWindow::Data::EType::Door )
	{
		double frameLength = fEAData.fHeight*2 + fEAData.fWidth + kFrameThickness*2;
		fEAWinDoor->SetFrameLength( frameLength / 1000.0 );	// !! be careful! The inerface expects meters !!
	}
	else
	{
		double width		= fEAData.fWidth / 2.0;
		double frameLength	= fEAData.fHeight + width*2;
		fEAWinDoor->SetFrameLength( frameLength / 1000.0 );	// !! be careful! The inerface expects meters !!

		frameLength = fEAData.fHeight + width + kFrameThickness*2;
		fEAWinDoor->SetFrameLength( frameLength / 1000.0, VectorWorks::EnergyAnalysis::EValueType::HybridDoor );	// !! be careful! The inerface expects meters !!
	}

	// update summer ventilation data. Clear width, clear height and clear area are changed.
		// Clear width is the rough opening minus twice the width of the window frame.
	double	clearWidth	= fEAData.fWidth - 2*kFrameThickness;
		// Clear height is the rough opening minus twice the height of the window frame.
	double	clearHeight	= fEAData.fType == Data::EType::Door ? fEAData.fHeight - kFrameThickness : fEAData.fHeight - 2*kFrameThickness;
		// Clear area is the area of the rough opening without the frame area.
	double	clearArea	= clearWidth * clearHeight;
	VectorWorks::EnergyAnalysis::SWinDoorSummerVentilationData	ventData;
	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayGF, ventData );
	ventData.fClearWidth	= clearWidth;
	ventData.fClearHeight	= clearHeight;
	ventData.fClearArea		= clearArea;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayGF, ventData );

	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayUF, ventData );
	ventData.fClearWidth	= clearWidth;
	ventData.fClearHeight	= clearHeight;
	ventData.fClearArea		= clearArea;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::DayUF, ventData );

	fEAWinDoor->GetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::Night, ventData );
	ventData.fClearWidth	= clearWidth;
	ventData.fClearHeight	= clearHeight;
	ventData.fClearArea		= clearArea;
	fEAWinDoor->SetSummerVentilation( VectorWorks::EnergyAnalysis::EWinDoorSummerVentilationType::Night, ventData );
}

void CWindowObject::InitNewObject()
{
	if ( fEAData.fIsNew )
	{
		// get data from the format records and copy it to this object
		VectorWorks::EnergyAnalysis::IEnergyBuildingElementWinDoorPtr	srcFormatData( VectorWorks::EnergyAnalysis::IID_EnergyBuildingElementWinDoor );
		if ( srcFormatData )
		{
			srcFormatData->LoadCreate( VWRecordFormatObj::GetRecordFormat( "EnergyDemoWindow" ) );

			srcFormatData->CopyDataTo( fhObject );

			fEAData.fIsNew	= false;
		}
	}
}

void CWindowObject::DrawDoor(VWPoint3D origin)
{
	// draw 2D
	VWPolygon2DObj	poly;
	poly.AddCornerVertex( origin.x,						origin.y,					false );
	poly.AddCornerVertex( origin.x + fEAData.fWidth,	origin.y,					false );
	poly.AddCornerVertex( origin.x + fEAData.fWidth,	origin.y - kFrameThickness,	false );
	poly.AddCornerVertex( origin.x,						origin.y - kFrameThickness,	true );
	poly.SetClosed( true );

	// draw 3D
	VWPolygon2D		leftBeam;
	leftBeam.AddVertex( origin.x,					origin.y );
	leftBeam.AddVertex( origin.x + kFrameThickness,	origin.y );
	leftBeam.AddVertex( origin.x + kFrameThickness,	origin.y - kFrameThickness );
	leftBeam.AddVertex( origin.x,					origin.y - kFrameThickness );
	leftBeam.SetClosed( true );
	VWExtrudeObj	leftExtr( leftBeam, origin.z + fEAData.fHeight - kFrameThickness );
	VWObjectAttr	leftAttr( leftExtr );
	leftAttr.SetFillBackColor( CRGBColor(138, 65, 23) );

	VWPolygon2D		rightBeam;
	rightBeam.AddVertex( origin.x + fEAData.fWidth - kFrameThickness,	origin.y );
	rightBeam.AddVertex( origin.x + fEAData.fWidth,						origin.y );
	rightBeam.AddVertex( origin.x + fEAData.fWidth,						origin.y - kFrameThickness );
	rightBeam.AddVertex( origin.x + fEAData.fWidth - kFrameThickness,	origin.y - kFrameThickness );
	rightBeam.SetClosed( true );
	VWExtrudeObj	rightExtr( rightBeam, origin.z + fEAData.fHeight - kFrameThickness );
	VWObjectAttr	rightAttr( rightExtr );
	rightAttr.SetFillBackColor( CRGBColor(138, 65, 23) );

	VWPolygon2D		upperBeam;
	upperBeam.AddVertex( origin.x,					origin.y );
	upperBeam.AddVertex( origin.x + fEAData.fWidth,	origin.y );
	upperBeam.AddVertex( origin.x + fEAData.fWidth,	origin.y - kFrameThickness );
	upperBeam.AddVertex( origin.x,					origin.y - kFrameThickness );
	upperBeam.SetClosed( true );
	VWExtrudeObj	upperExtr( upperBeam, origin.z + fEAData.fHeight - kFrameThickness, origin.z + kFrameThickness );
	VWObjectAttr	upperAttr( upperExtr );
	upperAttr.SetFillBackColor( CRGBColor(138, 65, 23) );

	// draw glass
	VWPolygon2D		glass;
	glass.AddVertex( origin.x + kFrameThickness,					origin.y - 4 );
	glass.AddVertex( origin.x + fEAData.fWidth - kFrameThickness,	origin.y - 4 );
	glass.AddVertex( origin.x + fEAData.fWidth - kFrameThickness,	origin.y - 6 );
	glass.AddVertex( origin.x + kFrameThickness,					origin.y - 6 );
	glass.SetClosed( true );
	VWExtrudeObj	glassExtr( glass, origin.z, origin.z + fEAData.fHeight - kFrameThickness );
	VWObjectAttr	glassAttr( glassExtr );
	glassAttr.SetFillBackColor( CRGBColor(102, 152, 255) );
	glassAttr.SetOpacity( 10 );
	if ( fEAData.fHasTilting )
	{
		VWPolygon3DObj	front;
		front.AddVertex( VWPoint3D(origin.x + kFrameThickness,											origin.y - 4,		origin.z									),	false	);
		front.AddVertex( VWPoint3D(origin.x + kFrameThickness + ((fEAData.fWidth-kFrameThickness*2)/2),	origin.y - 4,		origin.z + fEAData.fHeight - kFrameThickness),	false	);
		front.AddVertex( VWPoint3D(origin.x + fEAData.fWidth - kFrameThickness,							origin.y - 4,		origin.z									),	true	);
		front.SetClosed( false );
		VWObjectAttr	frontAttr( front );
		frontAttr.SetPenSolid();
		frontAttr.SetLineWeightInMils( 100 );
		frontAttr.SetPenForeColor( CRGBColor(193, 27, 23) );
		frontAttr.SetFillNone();

		VWPolygon3DObj	back;
		back.AddVertex( VWPoint3D(	origin.x + kFrameThickness,												origin.y - 6,		origin.z									),	false	);
		back.AddVertex( VWPoint3D(	origin.x + kFrameThickness + ((fEAData.fWidth-kFrameThickness*2)/2),	origin.y - 6,		origin.z + fEAData.fHeight - kFrameThickness),	false	);
		back.AddVertex( VWPoint3D(	origin.x + fEAData.fWidth - kFrameThickness,							origin.y - 6,		origin.z									),	true	);
		back.SetClosed( false );
		VWObjectAttr	backAttr( back );
		backAttr.SetPenSolid();
		backAttr.SetLineWeightInMils( 100 );
		backAttr.SetPenForeColor( CRGBColor(193, 27, 23) );
		backAttr.SetFillNone();
	}
}

void CWindowObject::DrawWindow(VWPoint3D origin)
{
	// --------------------------------------------------------------------------------------------------------
	// draw 2D
	VWPolygon2DObj	poly;
	poly.AddCornerVertex( origin.x,						origin.y,					false );
	poly.AddCornerVertex( origin.x + fEAData.fWidth,	origin.y,					false );
	poly.AddCornerVertex( origin.x + fEAData.fWidth,	origin.y - kFrameThickness,	false );
	poly.AddCornerVertex( origin.x,						origin.y - kFrameThickness,	true );
	poly.SetClosed( true );

	// --------------------------------------------------------------------------------------------------------
	// draw 3D
	VWPolygon2D		leftFrame;
	leftFrame.AddVertex( origin.x,						origin.y );
	leftFrame.AddVertex( origin.x + kFrameThickness,	origin.y );
	leftFrame.AddVertex( origin.x + kFrameThickness,	origin.y - kFrameThickness );
	leftFrame.AddVertex( origin.x,						origin.y - kFrameThickness );
	leftFrame.SetClosed( true );
	VWExtrudeObj	leftExtr( leftFrame, origin.z + fEAData.fHeight );
	VWObjectAttr	leftAttr( leftExtr );
	leftAttr.SetFillBackColor( CRGBColor(138, 65, 23) );

	VWPolygon2D		rightFrame;
	rightFrame.AddVertex( origin.x + fEAData.fWidth-kFrameThickness,	origin.y );
	rightFrame.AddVertex( origin.x + fEAData.fWidth,					origin.y );
	rightFrame.AddVertex( origin.x + fEAData.fWidth,					origin.y - kFrameThickness );
	rightFrame.AddVertex( origin.x + fEAData.fWidth-kFrameThickness,	origin.y - kFrameThickness );
	rightFrame.SetClosed( true );
	VWExtrudeObj	rightExtr( rightFrame, origin.z + fEAData.fHeight );
	VWObjectAttr	rightAttr( rightExtr );
	rightAttr.SetFillBackColor( CRGBColor(138, 65, 23) );

	VWPolygon2D		downFrame;
	downFrame.AddVertex( origin.x + kFrameThickness,				origin.y );
	downFrame.AddVertex( origin.x + fEAData.fWidth-kFrameThickness,	origin.y );
	downFrame.AddVertex( origin.x + fEAData.fWidth-kFrameThickness,	origin.y - kFrameThickness );
	downFrame.AddVertex( origin.x + kFrameThickness,				origin.y - kFrameThickness );
	downFrame.SetClosed( true );
	VWExtrudeObj	downExtr( downFrame, origin.z + kFrameThickness );
	VWObjectAttr	downAttr( downExtr );
	downAttr.SetFillBackColor( CRGBColor(138, 65, 23) );
	VWExtrudeObj	upExtr( downFrame, origin.z + fEAData.fHeight - kFrameThickness, origin.z + kFrameThickness );
	VWObjectAttr	upAttr( upExtr );
	upAttr.SetFillBackColor( CRGBColor(138, 65, 23) );

	// draw glass
	VWPolygon2D		glass;
	glass.AddVertex( origin.x + kFrameThickness,				origin.y - 4 );
	glass.AddVertex( origin.x + fEAData.fWidth-kFrameThickness,	origin.y - 4 );
	glass.AddVertex( origin.x + fEAData.fWidth-kFrameThickness,	origin.y - 6 );
	glass.AddVertex( origin.x + kFrameThickness,				origin.y - 6 );
	glass.SetClosed( true );
	VWExtrudeObj	glassExtr( glass, origin.z + kFrameThickness, origin.y + fEAData.fHeight - kFrameThickness*2 );
	VWObjectAttr	glassAttr( glassExtr );
	glassAttr.SetFillBackColor( CRGBColor(102, 152, 255) );
	glassAttr.SetOpacity( 10 );
	if ( fEAData.fHasTilting )
	{
		VWPolygon3DObj	front;
		front.AddVertex( VWPoint3D(origin.x + kFrameThickness,											origin.y - 4,	origin.z + kFrameThickness						),	false	);
		front.AddVertex( VWPoint3D(origin.x + kFrameThickness+((fEAData.fWidth-kFrameThickness*2)/2),	origin.y - 4,	origin.z + fEAData.fHeight - kFrameThickness	),	false	);
		front.AddVertex( VWPoint3D(origin.x + fEAData.fWidth-kFrameThickness,							origin.y - 4,	origin.z + kFrameThickness						),	true	);
		front.SetClosed( false );
		VWObjectAttr	frontAttr( front );
		frontAttr.SetLineWeightInMils( 100 );
		frontAttr.SetPenForeColor( CRGBColor(193, 27, 23) );
		frontAttr.SetFillNone();

		VWPolygon3DObj	back;
		back.AddVertex( VWPoint3D(	origin.x + kFrameThickness,											origin.y - 6,	origin.z + kFrameThickness					),	false	);
		back.AddVertex( VWPoint3D(	origin.x + kFrameThickness+((fEAData.fWidth-kFrameThickness*2)/2),	origin.y - 6,	origin.z + fEAData.fHeight-kFrameThickness	),	false	);
		back.AddVertex( VWPoint3D(	origin.x + fEAData.fWidth-kFrameThickness,							origin.y - 6,	origin.z + kFrameThickness					),	true	);
		back.SetClosed( false );
		VWObjectAttr	backAttr( back );
		backAttr.SetLineWeightInMils( 100 );
		backAttr.SetPenForeColor( CRGBColor(193, 27, 23) );
		backAttr.SetFillNone();
	}
}

void CWindowObject::DrawWinDoor(VWPoint3D origin)
{
	double width = fEAData.fWidth;
	fEAData.fWidth /= 2;

	this->DrawDoor( origin );

	origin.x += fEAData.fWidth;

	this->DrawWindow( origin );

	fEAData.fWidth = width;
}
