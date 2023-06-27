#include "StdAfx.h"

#include "ExtObjThePoly3DEx.h"

using namespace CustomDefaultTools;

namespace CustomDefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Normal,
		/*ParametricName*/				"SampleToolDef_Poly3DEx",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjThePoly3DEx", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjThePoly3DEx", "tool_title"},
		/*Category*/					{"ExtObjThePoly3DEx", "tool_category"},
		/*HelpText*/					{"ExtObjThePoly3DEx", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjThePoly3DDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png"
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjThePoly3DEx", "localized_name"},
		/*SubType*/					kParametricSubType_3DPath,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

/*	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"ExtObjThePoly3DEx", "choice1"} },
		{ 128,	"Arc",					{"ExtObjThePoly3DEx", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjThePoly3DEx", "choice3"} },
		{ 128,	"None",					{"ExtObjThePoly3DEx", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"ExtObjThePoly3DEx", "choice5"} },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
*/
	static SParametricParamDef gArrParameters[] = {
		{ "p1",			{"ExtObjThePoly3DEx", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjThePoly3DEx", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjThePoly3DEx", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjThePoly3DEx", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjThePoly3DEx", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjThePoly3DEx", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjThePoly3DEx", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}

// --------------------------------------------------------------------------------------------------------
// {739F4253-28C4-47B5-B4DB-D3C30591F096}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjThePoly3D,
	/*Event sink*/		CObjThePoly3D_EventSink,
	/*Universal name*/	"SampleToolDef_Poly3DEx",
	/*Version*/			1,
	/*UUID*/			0x739f4253, 0x28c4, 0x47b5, 0xb4, 0xdb, 0xd3, 0xc3, 0x5, 0x91, 0xf0, 0x96 );

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
// {9A10207A-4B99-4DDD-8D10-BF52A07FAE37}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjThePoly3DDefTool,
	/*Event sink*/		CExtObjThePoly3DDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_Poly3DToolEx",
	/*Version*/			1,
	/*UUID*/			0x9a10207a, 0x4b99, 0x4ddd, 0x8d, 0x10, 0xbf, 0x52, 0xa0, 0x7f, 0xae, 0x37 );

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
	: VWToolDefault3DPoly_EventSink( parent, "SampleToolDef_Poly3DEx" )
{
}

CExtObjThePoly3DDefTool_EventSink::~CExtObjThePoly3DDefTool_EventSink()
{
}

void CExtObjThePoly3DDefTool_EventSink::Init(const TXString& universalName)
{
	SDefault3DPolyToolInfo	toolInfo	= this->GetToolInfo();

	toolInfo.fModeGroup	= 0;
	toolInfo.fNURBSByInterpChoiceIndex	= 0;

	this->SetToolInfo( toolInfo );

	VWToolDefault3DPoly_EventSink::Init( universalName );
}

bool CExtObjThePoly3DDefTool_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider)
{	
	const IToolModeBarInitProvider* p2 = dynamic_cast<const IToolModeBarInitProvider*> (modeBarInitProvider);
	if (p2)
	{
		p2->AddButtonModeGroup("DefaultTools/Images/SampleToolButtonA.png");
		p2->AddButtonModeGroup("DefaultTools/Images/SampleToolButtonB.png");
		p2->AddButtonModeGroup("DefaultTools/Images/SampleToolButtonC.png");
	}
	return VWToolDefault3DPoly_EventSink::DoSetUp( bRestore, modeBarInitProvider );
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
