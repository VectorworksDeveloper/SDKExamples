#include "StdAfx.h"

#include "ExtObjThePoly3D.h"

using namespace DefaultTools;

namespace DefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Default3DPath,
		/*ParametricName*/				"SampleToolDef_Poly3D",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjThePoly3D", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjThePoly3D", "tool_title"},
		/*Category*/					{"ExtObjThePoly3D", "tool_category"},
		/*HelpText*/					{"ExtObjThePoly3D", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjThePoly3DDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png", 
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjThePoly3D", "localized_name"},
		/*SubType*/					kParametricSubType_3DPath,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

/*	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"ExtObjThePoly3D", "choice1"} },
		{ 128,	"Arc",					{"ExtObjThePoly3D", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjThePoly3D", "choice3"} },
		{ 128,	"None",					{"ExtObjThePoly3D", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"ExtObjThePoly3D", "choice5"} },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
*/
	static SParametricParamDef gArrParameters[] = {
		{ "p1",			{"ExtObjThePoly3D", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjThePoly3D", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjThePoly3D", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjThePoly3D", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjThePoly3D", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjThePoly3D", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjThePoly3D", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}


// --------------------------------------------------------------------------------------------------------
// {F4A67936-3B0A-45F7-A2F5-9BD513108D31}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjThePoly3D,
	/*Event sink*/		CObjThePoly3D_EventSink,
	/*Universal name*/	"SampleToolDef_Poly3D",
	/*Version*/			1,
	/*UUID*/			0xf4a67936, 0x3b0a, 0x45f7, 0xa2, 0xf5, 0x9b, 0xd5, 0x13, 0x10, 0x8d, 0x31 );

// Test with VectorScript:
// SetSelect(CreateCustomObject('SampleToolDef_Poly3D',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjThePoly3D::CExtObjThePoly3D(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters )
//	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjThePoly3D::~CExtObjThePoly3D()
{
}

// --------------------------------------------------------------------------------------------------------
// {41B4542E-33A2-4B94-8341-AE32FB2130C8}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjThePoly3DDefTool,
	/*Event sink*/		CExtObjThePoly3DDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_Poly3DTool",
	/*Version*/			1,
	/*UUID*/			0x41b4542e, 0x33a2, 0x4b94, 0x83, 0x41, 0xae, 0x32, 0xfb, 0x21, 0x30, 0xc8 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjThePoly3DDefTool::CExtObjThePoly3DDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjThePoly3DDefTool::~CExtObjThePoly3DDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjThePoly3DDefTool_EventSink::CExtObjThePoly3DDefTool_EventSink(IVWUnknown* parent)
	: VWToolDefault3DPoly_EventSink( parent, "SampleToolDef_Poly3D" )
{
}

CExtObjThePoly3DDefTool_EventSink::~CExtObjThePoly3DDefTool_EventSink()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjThePoly3D_EventSink::CObjThePoly3D_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjThePoly3D_EventSink::~CObjThePoly3D_EventSink()
{
}

EObjectEvent CObjThePoly3D_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );



	return kObjectEventNoErr;
}

EObjectEvent CObjThePoly3D_EventSink::Recalculate()
{
	VWParametricObj obj( fhObject );

	MCObjectHandle hPath = obj.GetObjectPath();

	MCObjectHandle hVisual = gSDK->DuplicateObject( hPath );
	obj.AddObject( hVisual ); // duplicate doesn't add automatically

	// lineObj will be added automatically to the parametric
	VWLine2DObj lineObj( 0, 0, 100, 100 );

	return kObjectEventNoErr;
}
