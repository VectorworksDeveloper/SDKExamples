#include "StdAfx.h"

#include "ExtObjTheRectEx.h"

using namespace CustomDefaultTools;

namespace CustomDefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Normal,
		/*ParametricName*/				"SampleToolDef_RectEx",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjTheRectEx", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjTheRectEx", "tool_title"},
		/*Category*/					{"ExtObjTheRectEx", "tool_category"},
		/*HelpText*/					{"ExtObjTheRectEx", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjTheRectDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png"
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjTheRectEx", "localized_name"},
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
		{ 128,	"Line",					{"ExtObjTheRectEx", "choice1"} },
		{ 128,	"Arc",					{"ExtObjTheRectEx", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjTheRectEx", "choice3"} },
		{ 128,	"None",					{"ExtObjTheRectEx", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"ExtObjTheRectEx", "choice5"} },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
*/
	static SParametricParamDef gArrParameters[] = {
		// Default box parameters
		{ "Width",		{"ExtObjTheRectEx", ""},		"10cm",	"10cm",	kFieldCoordDisp,		0 },
		{ "Height",		{"ExtObjTheRectEx", ""},		"10cm",	"10cm",	kFieldCoordDisp,		0 },

		// custom parameters
		{ "p1",			{"ExtObjTheRectEx", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjTheRectEx", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjTheRectEx", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjTheRectEx", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjTheRectEx", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjTheRectEx", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjTheRectEx", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}

// --------------------------------------------------------------------------------------------------------
// {15BFF968-F1F0-49AF-8154-4463A3778070}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjTheRect,
	/*Event sink*/		CObjTheRect_EventSink,
	/*Universal name*/	"SampleToolDef_RectEx",
	/*Version*/			1,
	/*UUID*/			0x15bff968, 0xf1f0, 0x49af, 0x81, 0x54, 0x44, 0x63, 0xa3, 0x77, 0x80, 0x70 );

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
// {C78E9DA8-DCB5-456F-A56E-FBDAB47B3A3E}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjTheRectDefTool,
	/*Event sink*/		CExtObjTheRectDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_RectToolEx",
	/*Version*/			1,
	/*UUID*/			0xc78e9da8, 0xdcb5, 0x456f, 0xa5, 0x6e, 0xfb, 0xda, 0xb4, 0x7b, 0x3a, 0x3e );

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
	: VWToolDefaultRect_EventSink( parent, "SampleToolDef_RectEx" )
{
}

CExtObjTheRectDefTool_EventSink::~CExtObjTheRectDefTool_EventSink()
{
}

void CExtObjTheRectDefTool_EventSink::Init(const TXString& universalName)
{
	SDefaultRectToolInfo	toolInfo	= this->GetToolInfo();

	toolInfo.fModeGroup	= 0;
	toolInfo.fCenterLineChoiceIndex	= 0;
	toolInfo.fEdgePlacementChoiceIndex	= 1;

	this->SetToolInfo( toolInfo );

	VWToolDefaultRect_EventSink::Init( universalName );
}

bool CExtObjTheRectDefTool_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider)
{
	const IToolModeBarInitProvider* p2 = dynamic_cast<const IToolModeBarInitProvider*> (modeBarInitProvider);
	if (p2)
	{
		p2->AddButtonModeGroup("DefaultTools/Images/SampleToolButtonA.png");
		p2->AddButtonModeGroup("DefaultTools/Images/SampleToolButtonB.png");
		p2->AddButtonModeGroup("DefaultTools/Images/SampleToolButtonC.png");
	}
	return VWToolDefaultRect_EventSink::DoSetUp( bRestore, modeBarInitProvider );
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


	extProps->SetObjectProperty( objectID, kObjXPropDefaultPropertyUI, (Sint8)kUseAppropriateLocationWidget );


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
