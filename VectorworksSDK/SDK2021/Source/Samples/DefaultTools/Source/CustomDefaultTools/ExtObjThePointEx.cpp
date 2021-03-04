#include "StdAfx.h"

#include "ExtObjThePointEx.h"

using namespace CustomDefaultTools;

namespace CustomDefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Normal,
		/*ParametricName*/				"SampleToolDef_PointEx",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjThePointEx", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjThePointEx", "tool_title"},
		/*Category*/					{"ExtObjThePointEx", "tool_category"},
		/*HelpText*/					{"ExtObjThePointEx", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjThePointDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png"
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjThePointEx", "localized_name"},
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
		{ 128,	"Line",					{"ExtObjThePointEx", "choice1"} },
		{ 128,	"Arc",					{"ExtObjThePointEx", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjThePointEx", "choice3"} },
		{ 128,	"None",					{"ExtObjThePointEx", "choice4"} },
		//------								 
		{ 129,	"Default Legend",		{"ExtObjThePointEx", "choice5"} },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
*/
	static SParametricParamDef gArrParameters[] = {
		{ "p1",			{"ExtObjThePointEx", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjThePointEx", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjThePointEx", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjThePointEx", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjThePointEx", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjThePointEx", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjThePointEx", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}

// --------------------------------------------------------------------------------------------------------
// {80832D54-FFAD-4414-9BB6-62D13CE393A6}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjThePoint,
	/*Event sink*/		CObjThePoint_EventSink,
	/*Universal name*/	"SampleToolDef_PointEx",
	/*Version*/			1,
	/*UUID*/			0x80832d54, 0xffad, 0x4414, 0x9b, 0xb6, 0x62, 0xd1, 0x3c, 0xe3, 0x93, 0xa6 );

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
// {0344D86F-50BF-4326-8660-9058E5EF6433}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjThePointDefTool,
	/*Event sink*/		CExtObjThePointDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_PointToolEx",
	/*Version*/			1,
	/*UUID*/			0x344d86f, 0x50bf, 0x4326, 0x86, 0x60, 0x90, 0x58, 0xe5, 0xef, 0x64, 0x33 );

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
	: VWToolDefaultPoint_EventSink( parent, "SampleToolDef_PointEx" )
{
	memset( fBarState, 0, sizeof(fBarState) );

	// default values for our groups
	fBarState[0]	= 0;
	fBarState[2]	= 0;
	fBarState[3]	= 3;
}

CExtObjThePointDefTool_EventSink::~CExtObjThePointDefTool_EventSink()
{
}

void CExtObjThePointDefTool_EventSink::Init(const TXString& universalName)
{
	SDefaultPointToolInfo	toolInfo	= this->GetToolInfo();

	toolInfo.fModeGroup              	= 0;	// group 2
	toolInfo.fAlignmentGroup         	= 2;	// group 3
	toolInfo.fRegularInsChoiceIndex  	= 0;	// fModeGroup:	button index 0
	toolInfo.fOffsetInsChoiceIndex   	= 1;	//				button index 1
	toolInfo.fLeftChoiceIndex        	= 0;	// fAlignmentGroup:	button index 0
	toolInfo.fCenterChoiceIndex      	= 1;	//					button index 1
	toolInfo.fRightChoiceIndex       	= 2;	//					button index 2
	toolInfo.fNaturalChoiceIndex     	= 3;	//					button index 3

	this->SetToolInfo( toolInfo );

	VWToolDefaultPoint_EventSink::Init( universalName );
}

bool CExtObjThePointDefTool_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider)
{
	// NOTE! the constructor initializes
	// the default values of fBarState

	const IToolModeBarInitProvider* p2 = dynamic_cast<const IToolModeBarInitProvider*> (modeBarInitProvider);
	if (p2)
	{
		TXStringArray group0ImageSpecs;
		group0ImageSpecs.Append("DefaultTools/Images/SampleToolButtonA.png");
		group0ImageSpecs.Append("DefaultTools/Images/SampleToolButtonB.png");
		
		p2->AddRadioModeGroup( /*group 0*/ fBarState[0], group0ImageSpecs);
		p2->AddButtonModeGroup( /*group 1*/ "DefaultTools/Images/SampleToolButtonB.png");
		
		TXStringArray group2ImageSpecs;
		group2ImageSpecs.Append("DefaultTools/Images/SampleToolButtonA.png");
		group2ImageSpecs.Append("DefaultTools/Images/SampleToolButtonB.png");
		group2ImageSpecs.Append("Vectorworks/ModeViewBar/Classes.png");
		group2ImageSpecs.Append("DefaultTools/Images/SampleToolButtonA.png");
		p2->AddRadioModeGroup( /*group 2*/ fBarState[2], group2ImageSpecs);
		
		p2->AddButtonModeGroup( /*group 3*/ "Vectorworks/ModeViewBar/Options.png" );
	}

	TXStringArray	arrButtonsHelps;
//	arrButtonsHelps.Append( TXString( (short)11000, (short)10 ) );
//	arrButtonsHelps.Append( TXString( (short)11000, (short)11 ) );
//	arrButtonsHelps.Append( TXString( (short)11000, (short)12 ) );
//	arrButtonsHelps.Append( TXString( (short)11000, (short)13 ) );
//	arrButtonsHelps.Append( TXString( (short)11000, (short)14 ) );
//	arrButtonsHelps.Append( TXString( (short)11000, (short)15 ) );
//	arrButtonsHelps.Append( TXString( (short)11000, (short)16 ) );
//	arrButtonsHelps.Append( TXString( (short)11000, (short)17 ) );
//	arrButtonsHelps.Append( TXString( (short)11000, (short)18 ) );
//	modeBarInitProvider->SetButtonsHelpText( arrButtonsHelps );

	return VWToolDefaultPoint_EventSink::DoSetUp( bRestore, modeBarInitProvider );
}

void CExtObjThePointDefTool_EventSink::DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID)
{
	// save the state so to be able to restore the mode bar proerly
	fBarState[ modeGroupID ]	= newButtonID;

	if ( modeGroupID == 3 )
	{
		// display the properties dialog
		VWParametricObj::DefineCustomObject( "SampleToolDef_PointEx", true );
	}
	else
	{
		// just for fun, show a dialog and do default action
		TXString	msg;
		msg.Format( "groupID: %d newButtonID: %d oldButtonID: %d", modeGroupID, newButtonID, oldButtonID );
		gSDK->AlertInform( "CExtObjThePointDefTool_EventSink::DoModeEvent", msg );

		VWToolDefaultPoint_EventSink::DoModeEvent( modeGroupID, newButtonID, oldButtonID );
	}
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
