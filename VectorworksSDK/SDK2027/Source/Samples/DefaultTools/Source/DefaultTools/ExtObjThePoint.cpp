#include "StdAfx.h"

#include "ExtObjThePoint.h"

using namespace DefaultTools;

namespace DefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_DefaultPoint,
		/*ParametricName*/				"SampleToolDef_Point",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjThePoint", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjThePoint", "tool_title"},
		/*Category*/					{"ExtObjThePoint", "tool_category"},
		/*HelpText*/					{"ExtObjThePoint", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjThePointDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png", 
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjThePoint", "localized_name"},
		/*SubType*/					kParametricSubType_Point,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

/*
 static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"ExtObjThePoint", "choice1"} },
		{ 128,	"Arc",					{"ExtObjThePoint", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjThePoint", "choice3"} },
		{ 128,	"None",					{"ExtObjThePoint", "choice4"} },
		//------								 
		{ 129,	"Default Legend",		{"ExtObjThePoint", "choice5"} },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
*/
	static SParametricParamDef gArrParameters[] = {
		{ "p1",			{"ExtObjThePoint", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjThePoint", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjThePoint", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjThePoint", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjThePoint", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjThePoint", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjThePoint", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}


// --------------------------------------------------------------------------------------------------------
// {5376CFDC-9E15-4F12-82AA-688EB18AAD4C}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjThePoint,
	/*Event sink*/		CObjThePoint_EventSink,
	/*Universal name*/	"SampleToolDef_Point",
	/*Version*/			1,
	/*UUID*/			0x5376cfdc, 0x9e15, 0x4f12, 0x82, 0xaa, 0x68, 0x8e, 0xb1, 0x8a, 0xad, 0x4c );

// Test with VectorScript:
// SetSelect(CreateCustomObject('SampleToolDef_Point',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjThePoint::CExtObjThePoint(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters )
//	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjThePoint::~CExtObjThePoint()
{
}

// --------------------------------------------------------------------------------------------------------
// {D680D90A-D19B-45F1-8B4F-4EDFE9298C84}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjThePointDefTool,
	/*Event sink*/		CExtObjThePointDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_PointTool",
	/*Version*/			1,
	/*UUID*/			0xd680d90a, 0xd19b, 0x45f1, 0x8b, 0x4f, 0x4e, 0xdf, 0xe9, 0x29, 0x8c, 0x84 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjThePointDefTool::CExtObjThePointDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjThePointDefTool::~CExtObjThePointDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjThePointDefTool_EventSink::CExtObjThePointDefTool_EventSink(IVWUnknown* parent)
	: VWToolDefaultPoint_EventSink( parent, "SampleToolDef_Point" )
{
}

CExtObjThePointDefTool_EventSink::~CExtObjThePointDefTool_EventSink()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjThePoint_EventSink::CObjThePoint_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjThePoint_EventSink::~CObjThePoint_EventSink()
{
}

EObjectEvent CObjThePoint_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );



	return kObjectEventNoErr;
}

EObjectEvent CObjThePoint_EventSink::Recalculate()
{
	VWPoint3D	offset( -500, 0, 0 );

	VWPolygon3DObj	poly;
	poly.AddVertex( offset + VWPoint3D(50, 100, 0) );
	poly.AddVertex( offset + VWPoint3D(1000, 0, 0) );
	poly.AddVertex( offset + VWPoint3D(1000, 1000, 0) );
	poly.AddVertex( offset + VWPoint3D(100, 800, 0) );
	poly.SetClosed( true );

	return kObjectEventNoErr;
}
