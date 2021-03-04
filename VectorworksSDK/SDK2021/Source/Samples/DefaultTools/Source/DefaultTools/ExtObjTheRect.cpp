#include "StdAfx.h"

#include "ExtObjTheRect.h"

using namespace DefaultTools;

namespace DefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_DefaultBox,
		/*ParametricName*/				"SampleToolDef_Rect",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjTheRect", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjTheRect", "tool_title"},
		/*Category*/					{"ExtObjTheRect", "tool_category"},
		/*HelpText*/					{"ExtObjTheRect", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjTheRectDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png", 
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjTheRect", "localized_name"},
		/*SubType*/					kParametricSubType_Rectangular,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};
/*
	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"ExtObjTheRect", "choice1"} },
		{ 128,	"Arc",					{"ExtObjTheRect", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjTheRect", "choice3"} },
		{ 128,	"None",					{"ExtObjTheRect", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"ExtObjTheRect", "choice5"} },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
*/
	static SParametricParamDef gArrParameters[] = {
		// Default box parameters
		{ "Width",		{"ExtObjTheRect", ""},		"10cm",	"10cm",	kFieldCoordDisp,		0 },
		{ "Height",		{"ExtObjTheRect", ""},		"10cm",	"10cm",	kFieldCoordDisp,		0 },

		// custom parameters
		{ "p1",			{"ExtObjTheRect", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjTheRect", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjTheRect", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjTheRect", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjTheRect", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjTheRect", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjTheRect", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}


// --------------------------------------------------------------------------------------------------------
// {088B350E-BFF8-47B3-AC30-AC0BE5FBF7C4}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjTheRect,
	/*Event sink*/		CObjTheRect_EventSink,
	/*Universal name*/	"SampleToolDef_Rect",
	/*Version*/			1,
	/*UUID*/			0x88b350e, 0xbff8, 0x47b3, 0xac, 0x30, 0xac, 0xb, 0xe5, 0xfb, 0xf7, 0xc4 );

// Test with VectorScript:
// SetSelect(CreateCustomObject('SampleToolDef_Rect',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjTheRect::CExtObjTheRect(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters )
//	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjTheRect::~CExtObjTheRect()
{
}

// --------------------------------------------------------------------------------------------------------
// {34781EF5-35FD-4989-8ABC-7C5FAC8EDF0D}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjTheRectDefTool,
	/*Event sink*/		CExtObjTheRectDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_RectTool",
	/*Version*/			1,
	/*UUID*/			0x34781ef5, 0x35fd, 0x4989, 0x8a, 0xbc, 0x7c, 0x5f, 0xac, 0x8e, 0xdf, 0xd );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjTheRectDefTool::CExtObjTheRectDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjTheRectDefTool::~CExtObjTheRectDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjTheRectDefTool_EventSink::CExtObjTheRectDefTool_EventSink(IVWUnknown* parent)
	: VWToolDefaultRect_EventSink( parent, "SampleToolDef_Rect" )
{
}

CExtObjTheRectDefTool_EventSink::~CExtObjTheRectDefTool_EventSink()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjTheRect_EventSink::CObjTheRect_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjTheRect_EventSink::~CObjTheRect_EventSink()
{
}

EObjectEvent CObjTheRect_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );



	return kObjectEventNoErr;
}

EObjectEvent CObjTheRect_EventSink::Recalculate()
{
	VWParametricObj paramObj( fhObject );

	double objWidth = paramObj.GetParamReal( "Width" );
	double objHeight = paramObj.GetParamReal( "Height" );

	VWPolygon2DObj	poly;
	poly.AddVertex( 0, 0, false );
	poly.AddVertex( objWidth, 0, false );
	poly.AddVertex( objWidth, objHeight, false );
	poly.AddVertex( 0, objHeight, false );
	poly.SetClosed( true );

	return kObjectEventNoErr;
}
