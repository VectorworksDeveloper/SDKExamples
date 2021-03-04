#include "StdAfx.h"

#include "ExtObjClassName.h"
#include "ProviderShapePane.h"

using namespace TesterModule;

namespace TesterModule
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_DefaultPoint,
		/*ParametricName*/				"ProviderTestObj",
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
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"ProvidersSample/ExtObjClassNameDefTool.png",
		/*Cursor Specifier*/			""
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjClassName", "localized_name"},
		/*SubType*/					kParametricSubType_Point,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"ExtObjClassName", "choice1"} },
		{ 128,	"Arc",					{"ExtObjClassName", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjClassName", "choice3"} },
		{ 128,	"None",					{"ExtObjClassName", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"ExtObjClassName", "choice5"} },
		//------
		// TERMINATE
		{ 0, "", {0,0} }
	};

	static SParametricParamDef	gArrParameters[] = {
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
// {56D3EBD2-4871-41BB-A9CF-EBBBC622F540}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjClassName,
	/*Event sink*/		CObjClassName_EventSink,
	/*Universal name*/	"ProviderTestObj",
	/*Version*/			1,
	/*UUID*/			0x56d3ebd2, 0x4871, 0x41bb, 0xa9, 0xcf, 0xeb, 0xbb, 0xc6, 0x22, 0xf5, 0x40 );

// Test with VectorScript:
// SetSelect(CreateCustomObject('ProviderTestObj',0,0,0));

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjClassName::CExtObjClassName(CallBackPtr cbp)
	: VWExtensionParametric( cbp, gParametricDef, gArrParameters, gArrChoices )
{
}

CExtObjClassName::~CExtObjClassName()
{
}

void CExtObjClassName::DefineSinks()
{
	this->DefineSink<CProviderShapePane>( IID_ProviderShapePane );
//	this->DefineSink<CProviderReshape3D>( IID_ProviderReshape3D );
//	this->DefineSink<CProviderSiteModifiers>( IID_DTMModifiersProvider );
}

// --------------------------------------------------------------------------------------------------------
// {8252E086-52F3-44EF-AA81-9A5A386AC1D5}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjClassNameDefTool,
	/*Event sink*/		VWToolEmpty_EventSink,
	/*Universal name*/	"ProviderTestObjTool",
	/*Version*/			1,
	/*UUID*/			0x8252e086, 0x52f3, 0x44ef, 0xaa, 0x81, 0x9a, 0x5a, 0x38, 0x6a, 0xc1, 0xd5 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtObjClassNameDefTool::CExtObjClassNameDefTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtObjClassNameDefTool::~CExtObjClassNameDefTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CObjClassName_EventSink::CObjClassName_EventSink(IVWUnknown* parent)
	: VWParametric_EventSink( parent )
{
}

CObjClassName_EventSink::~CObjClassName_EventSink()
{
}

EObjectEvent CObjClassName_EventSink::OnInitXProperties(CodeRefID objectID)
{
	// obtain the interfact for accessing the extended properties
	using namespace VectorWorks::Extension;
	VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );



	return kObjectEventNoErr;
}

EObjectEvent CObjClassName_EventSink::Recalculate()
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
