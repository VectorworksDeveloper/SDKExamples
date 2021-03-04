#include "StdAfx.h"

#include "ExtObjUpdater.h"

using namespace Updater;

namespace Updater
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Default2DPath,
		/*ParametricName*/				"SampleUpdaterObj",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjClassName", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjClassName", "tool_title"},
		/*Category*/					{"ExtObjClassName", "tool_category"},
		/*HelpText*/					{"ExtObjClassName", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjClassName", "localized_name"},
		/*SubType*/					kParametricSubType_2DPath,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

	/*static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{11002, "choice1"} },
		{ 128,	"Arc",					{11002, "choice2"} },
		{ 128,	"Bezier",				{11002, "choice3"} },
		{ 128,	"None",					{11002, "choice4"} },
		//------
		{ 129,	"Default Legend",		{11002, "choice5"} },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};*/

	static SParametricParamDef gArrParameters[] = {
		{ "p1",			{"ExtObjClassName", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjClassName", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjClassName", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjClassName", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjClassName", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjClassName", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjClassName", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}


// --------------------------------------------------------------------------------------------------------
// {32ADBB12-8B9F-4BC2-BC78-E75329ECF147}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjUpdater,
	/*Event sink*/		CObjUpdater_EventSink,
	/*Universal name*/	"SampleUpdaterObj",
	/*Version*/			1,
	/*UUID*/			0x32adbb12, 0x8b9f, 0x4bc2, 0xbc, 0x78, 0xe7, 0x53, 0x29, 0xec, 0xf1, 0x47 );

// Test with VectorScript:
// SetSelect(CreateCustomObject('SampleUpdaterObj',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjUpdater::CExtObjUpdater(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters )
//	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjUpdater::~CExtObjUpdater()
{
}

// --------------------------------------------------------------------------------------------------------
// {6BD619B4-0C27-4ED0-9162-62EF0C3C3F08}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjUpdaterDefTool,
	/*Event sink*/		VWToolEmpty_EventSink,
	/*Universal name*/	"SampleUpdaterObjTool",
	/*Version*/			1,
	/*UUID*/			0x6bd619b4, 0xc27, 0x4ed0, 0x91, 0x62, 0x62, 0xef, 0xc, 0x3c, 0x3f, 0x8 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjUpdaterDefTool::CExtObjUpdaterDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjUpdaterDefTool::~CExtObjUpdaterDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjUpdater_EventSink::CObjUpdater_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjUpdater_EventSink::~CObjUpdater_EventSink()
{
}

EObjectEvent CObjUpdater_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );



	return kObjectEventNoErr;
}

EObjectEvent CObjUpdater_EventSink::Recalculate()
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
