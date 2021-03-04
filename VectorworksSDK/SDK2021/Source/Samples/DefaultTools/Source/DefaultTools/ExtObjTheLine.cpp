#include "StdAfx.h"

#include "ExtObjTheLine.h"

using namespace DefaultTools;

namespace DefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_DefaultLine,
		/*ParametricName*/				"SampleToolDef_Line",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjTheLine", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjTheLine", "tool_title"},
		/*Category*/					{"ExtObjTheLine", "tool_category"},
		/*HelpText*/					{"ExtObjTheLine", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjTheLineDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png", 
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjTheLine", "localized_name"},
		/*SubType*/					kParametricSubType_Linear,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};
	/*
	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"ExtObjTheLine", "choice1"} },
		{ 128,	"Arc",					{"ExtObjTheLine", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjTheLine", "choice3"} },
		{ 128,	"None",					{"ExtObjTheLine", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"ExtObjTheLine", "choice5" },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
	 */
	static SParametricParamDef gArrParameters[] = {
		// Default line parameters
		{ "LineLength",		{"ExtObjTheRect", ""},		"10cm",	"10cm",	kFieldCoordDisp,		0 },

		// custom parameters
		{ "p1",			{"ExtObjTheLine", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjTheLine", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjTheLine", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjTheLine", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjTheLine", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjTheLine", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjTheLine", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}


// --------------------------------------------------------------------------------------------------------
// {45C740D8-B0D5-43D7-A73B-391AB019CF85}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjTheLine,
	/*Event sink*/		CObjTheLine_EventSink,
	/*Universal name*/	"SampleToolDef_Line",
	/*Version*/			1,
	/*UUID*/			0x45c740d8, 0xb0d5, 0x43d7, 0xa7, 0x3b, 0x39, 0x1a, 0xb0, 0x19, 0xcf, 0x85 );

// Test with VectorScript:
// SetSelect(CreateCustomObject('SampleToolDef_Line',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjTheLine::CExtObjTheLine(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters )
//	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjTheLine::~CExtObjTheLine()
{
}

// --------------------------------------------------------------------------------------------------------
// {A05B4443-7D21-427E-8962-3C45DCB99F70}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjTheLineDefTool,
	/*Event sink*/		CExtObjTheLineDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_LineTool",
	/*Version*/			1,
	/*UUID*/			0xa05b4443, 0x7d21, 0x427e, 0x89, 0x62, 0x3c, 0x45, 0xdc, 0xb9, 0x9f, 0x70 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjTheLineDefTool::CExtObjTheLineDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjTheLineDefTool::~CExtObjTheLineDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjTheLineDefTool_EventSink::CExtObjTheLineDefTool_EventSink(IVWUnknown* parent)
	: VWToolDefaultLine_EventSink( parent, "SampleToolDef_Line" )
{
}

CExtObjTheLineDefTool_EventSink::~CExtObjTheLineDefTool_EventSink()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjTheLine_EventSink::CObjTheLine_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjTheLine_EventSink::~CObjTheLine_EventSink()
{
}

EObjectEvent CObjTheLine_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );

	extProps->SetObjectProperty( objectID, kObjXPropDefaultPropertyUI, (Sint8)kUseAppropriateLocationWidget );
	extProps->SetObjectProperty( objectID, kObjXPropShowLinearDirection, true );


	return kObjectEventNoErr;
}

EObjectEvent CObjTheLine_EventSink::Recalculate()
{
	VWParametricObj paramObj( fhObject );

	double lineLength = paramObj.GetParamReal( "LineLength" );

	VWLine2DObj lineObj( 0, 0, lineLength, 0 );

	return kObjectEventNoErr;
}
