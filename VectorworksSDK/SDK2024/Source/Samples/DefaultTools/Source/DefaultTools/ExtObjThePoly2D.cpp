#include "StdAfx.h"

#include "ExtObjThePoly2D.h"

using namespace DefaultTools;

namespace DefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Default2DPath,
		/*ParametricName*/				"SampleToolDef_Poly2D",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjThePoly2D", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjThePoly2D", "tool_title"},
		/*Category*/					{"ExtObjThePoly2D", "tool_category"},
		/*HelpText*/					{"ExtObjThePoly2D", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjThePoly2DDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png", 
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjThePoly2D", "localized_name"},
		/*SubType*/					kParametricSubType_2DPath,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

/*	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"ExtObjThePoly2D", "choice1"} },
		{ 128,	"Arc",					{"ExtObjThePoly2D", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjThePoly2D", "choice3"} },
		{ 128,	"None",					{"ExtObjThePoly2D", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"ExtObjThePoly2D", "choice5"} },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
*/
	static SParametricParamDef gArrParameters[] = {
		{ "p1",			{"ExtObjThePoly2D", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjThePoly2D", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjThePoly2D", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjThePoly2D", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjThePoly2D", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjThePoly2D", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjThePoly2D", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}


// --------------------------------------------------------------------------------------------------------
// {0DCA59C5-4A13-4A67-8026-AED463ED07DC}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjThePoly2D,
	/*Event sink*/		CObjThePoly2D_EventSink,
	/*Universal name*/	"SampleToolDef_Poly2D",
	/*Version*/			1,
	/*UUID*/			0xdca59c5, 0x4a13, 0x4a67, 0x80, 0x26, 0xae, 0xd4, 0x63, 0xed, 0x7, 0xdc );

// Test with VectorScript:
// SetSelect(CreateCustomObject('SampleToolDef_Poly2D',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjThePoly2D::CExtObjThePoly2D(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters )
//	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjThePoly2D::~CExtObjThePoly2D()
{
}

// --------------------------------------------------------------------------------------------------------
// {7C8D90BD-5401-4788-9B2E-CD65E9341BD1}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjThePoly2DDefTool,
	/*Event sink*/		CExtObjThePoly2DDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_Poly2DTool",
	/*Version*/			1,
	/*UUID*/			0x7c8d90bd, 0x5401, 0x4788, 0x9b, 0x2e, 0xcd, 0x65, 0xe9, 0x34, 0x1b, 0xd1 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjThePoly2DDefTool::CExtObjThePoly2DDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjThePoly2DDefTool::~CExtObjThePoly2DDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjThePoly2DDefTool_EventSink::CExtObjThePoly2DDefTool_EventSink(IVWUnknown* parent)
	: VWToolDefault2DPoly_EventSink( parent, "SampleToolDef_Poly2D" )
{
}

CExtObjThePoly2DDefTool_EventSink::~CExtObjThePoly2DDefTool_EventSink()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjThePoly2D_EventSink::CObjThePoly2D_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjThePoly2D_EventSink::~CObjThePoly2D_EventSink()
{
}

EObjectEvent CObjThePoly2D_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );



	return kObjectEventNoErr;
}

EObjectEvent CObjThePoly2D_EventSink::Recalculate()
{
	VWParametricObj obj( fhObject );

	MCObjectHandle hPath = obj.GetObjectPath();

	MCObjectHandle hVisual = gSDK->DuplicateObject( hPath );
	obj.AddObject( hVisual ); // duplicate doesn't add automatically

	// lineObj will be added automatically to the parametric
	VWLine2DObj lineObj( 0, 0, 100, 100 );

	return kObjectEventNoErr;
}
