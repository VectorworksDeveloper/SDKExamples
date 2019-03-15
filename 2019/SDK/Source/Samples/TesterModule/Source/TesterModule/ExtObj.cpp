#include "StdAfx.h"

#include "ExtObj.h"

using namespace TesterModule;

namespace TesterModule
{
	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"CExtObj", "localized_name"},
		/*SubType*/					kParametricSubType_Point,
		/*ResetOnMove*/				true,
		/*ResetOnRotate*/			true,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"CExtObj", "choice1"} },
		{ 128,	"Arc",					{"CExtObj", "choice2"} },
		{ 128,	"Bezier",				{"CExtObj", "choice3"} },
		{ 128,	"None",					{"CExtObj", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"CExtObj", "choice5"} },
		//------
		// TERMINATE
		{ 0, "", {0,0} }
	};

	static SParametricParamDef gArrParameters[] = {
		{ "p1",			{"CExtObj", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"CExtObj", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"CExtObj", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"CExtObj", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"CExtObj", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"CExtObj", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"CExtObj", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		{ "pAngle",		{"CExtObj", "param8"},		"15",		"15",		kFieldAngle,		0 },
		{ "pArea",		{"CExtObj", "param9"},		"1",		"1",		kFieldArea,			0 },
		{ "pVolume",	{"CExtObj", "param10"},		"2",		"2",		kFieldVolume,		0 },
		{ "pClass",		{"CExtObj", "param11"},		"None",		"Nodn",		kFieldClassesPopup,	0 },
		{ "pLayer",		{"CExtObj", "param12"},		"",			"",			kFieldLayersPopup,	0 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}

// --------------------------------------------------------------------------------------------------------
// {3BA4CC4B-B330-4F61-9594-64D8E5BC803E}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObj,
	/*Event sink*/		CObj_EventSink,
	/*Universal name*/	"CExtObj",
	/*Version*/			1,
	/*UUID*/			0x3ba4cc4b, 0xb330, 0x4f61, 0x95, 0x94, 0x64, 0xd8, 0xe5, 0xbc, 0x80, 0x3e );
// Test:
// SetSelect(CreateCustomObject('CExtObj',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObj::CExtObj(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObj::~CExtObj()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObj_EventSink::CObj_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObj_EventSink::~CObj_EventSink()
{
}

EObjectEvent CObj_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );

	//...

	return kObjectEventNoErr;
}

EObjectEvent CObj_EventSink::Recalculate()
{
/*	VWPoint3D	offset( 100, 0, 0 );

	VWPolygon3DObj	poly;
	poly.AddVertex( offset + VWPoint3D(50, 100, 0) );
	poly.AddVertex( offset + VWPoint3D(1000, 0, 0) );
	poly.AddVertex( offset + VWPoint3D(1000, 1000, 0) );
	poly.AddVertex( offset + VWPoint3D(100, 800, 0) );
	poly.SetClosed( true );

	VWParametricObj	paramObj( fhObject );
	TXString val1 = paramObj.GetParamValue( "p3" );
	*/

	TransformMatrix	matrix;
	gSDK->GetEntityMatrix( fhObject, matrix );

	WorldPt	ptOrigin;
	gSDK->GetUserOriginFP( ptOrigin );

	TXString	strText1;
	strText1.Format( "ObjPos: x=%f y=%f       UserOriginFP: x=%f y=%f", matrix.P().x, matrix.P().y, ptOrigin.x, ptOrigin.y );
	VWTextBlockObj	textObj1( strText1 );

	return kObjectEventNoErr;
}
