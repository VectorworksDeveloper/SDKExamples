//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtObjResourcePopup.h"
#include "ExtObjResourcePopup_ShapePane.h"

using namespace ResourcePopup;

namespace ResourcePopup
{
	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjResourcePopup", "LocalizedName"},
		/*SubType*/					kParametricSubType_Point,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",				{"ExtObjResourcePopup", "param_shape_choice_line"} },
		{ 128,	"Circle",			{"ExtObjResourcePopup", "param_shape_choice_circle"} },
		{ 128,	"Box",				{"ExtObjResourcePopup", "param_shape_choice_box"} },
		//------
		// TERMINATE
		{ 0, "", {0,0} }
	};

	static SParametricParamDef gArrParameters[] = {
		{ "shape",		{"ExtObjResourcePopup", "param_shape"},		"Box",	"Box",		kFieldPopUp,		128 },
		{ "text",		{"ExtObjResourcePopup", "param_text"},		"",		"",			kFieldText,			0 },
		{ "size",		{"ExtObjResourcePopup", "param_size"},		"1\"",	"2cm",		kFieldCoordDisp,	0 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}


// --------------------------------------------------------------------------------------------------------
// {A9B5AE58-7D5B-43C4-A6FC-CA7DF240C63F}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjResourcePopup,
	/*Event sink*/		CObjResourcePopup_EventSink,
	/*Universal name*/	"ResourcePopupObject",
	/*Version*/			1,
	/*UUID*/			0xa9b5ae58, 0x7d5b, 0x43c4, 0xa6, 0xfc, 0xca, 0x7d, 0xf2, 0x40, 0xc6, 0x3f );

// Test with VectorScript:
// SetSelect(CreateCustomObject('ResourcePopupObject',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjResourcePopup::CExtObjResourcePopup(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjResourcePopup::~CExtObjResourcePopup()
{
}

void CExtObjResourcePopup::DefineSinks()
{
	this->DefineSink<CExtObjResourcePopup_ShapePane>( IID_ProviderShapePane );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjResourcePopup_EventSink::CObjResourcePopup_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjResourcePopup_EventSink::~CObjResourcePopup_EventSink()
{
}

EObjectEvent CObjResourcePopup_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );



	return kObjectEventNoErr;
}

EObjectEvent CObjResourcePopup_EventSink::Recalculate()
{
	VWParametricObj	param( fhObject );
	double	size	= param.GetParamReal( "size" );

	MCObjectHandle	hShape = nullptr;

	TXString shape = param.GetParamString( "shape" );
	if ( shape == "Line" )
	{
		VWLine2DObj	lineObj( -size/2, 0, size/2, 0 );
		hShape	= lineObj;
	}
	else if ( shape == "Circle" )
	{
		VWArcObj arcObj( VWPoint2D(0,0), size );
		hShape = arcObj;
	}
	else if ( shape == "Box" )
	{
		VWPolygon2DObj	polyObj( VWRectangle2D( -size/2, size/2, -size/2, size/2 ) );
		polyObj.SetClosed( true );
		hShape = polyObj;
	}

	TXString	text = param.GetParamString( "text" );
	VWTextBlockObj	textObj( text );
	textObj.SetTextVerticalAlignment( kTextVertAlign_CenterBox );
	textObj.SetTextJustification( kTextHorzAlign_Center );

	hShape;

	return kObjectEventNoErr;
}
