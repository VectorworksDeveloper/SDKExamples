#include "StdAfx.h"

#include "ExtObjTheLineEx.h"

using namespace CustomDefaultTools;

namespace CustomDefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Normal,
		/*ParametricName*/				"SampleToolDef_LineEx",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjTheLineEx", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjTheLineEx", "tool_title"},
		/*Category*/					{"ExtObjTheLineEx", "tool_category"},
		/*HelpText*/					{"ExtObjTheLineEx", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjTheLineDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png", 
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjTheLineEx", "localized_name"},
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
		{ 128,	"Line",					{"ExtObjTheLineEx", "choice1"} },
		{ 128,	"Arc",					{"ExtObjTheLineEx", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjTheLineEx", "choice3"} },
		{ 128,	"None",					{"ExtObjTheLineEx", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"ExtObjTheLineEx", "choice5" },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
	 */
	static SParametricParamDef gArrParameters[] = {
		// Default line parameters
		{ "LineLength",		{"ExtObjTheRect", ""},		"10cm",	"10cm",	kFieldCoordDisp,		0 },

		// custom parameters
		{ "p1",			{"ExtObjTheLineEx", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjTheLineEx", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjTheLineEx", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjTheLineEx", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjTheLineEx", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjTheLineEx", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjTheLineEx", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}

// --------------------------------------------------------------------------------------------------------
// {BFF6F152-1AFB-481F-BE54-0AD22CE2E178}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjTheLine,
	/*Event sink*/		CObjTheLine_EventSink,
	/*Universal name*/	"SampleToolDef_LineEx",
	/*Version*/			1,
	/*UUID*/			0xbff6f152, 0x1afb, 0x481f, 0xbe, 0x54, 0xa, 0xd2, 0x2c, 0xe2, 0xe1, 0x78 );

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
// {8D1E4C23-D13E-45F9-9BEB-9E2EADC8D8E6}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjTheLineDefTool,
	/*Event sink*/		CExtObjTheLineDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_LineToolEx",
	/*Version*/			1,
	/*UUID*/			0x8d1e4c23, 0xd13e, 0x45f9, 0x9b, 0xeb, 0x9e, 0x2e, 0xad, 0xc8, 0xd8, 0xe6 );

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
	: VWToolDefaultLine_EventSink( parent, "SampleToolDef_LineEx" )
{
	memset( fBarState, 0, sizeof(fBarState) );

	// default values for our groups
	fBarState[0]	= 0;
	fBarState[2]	= 1;
}

CExtObjTheLineDefTool_EventSink::~CExtObjTheLineDefTool_EventSink()
{
}

void CExtObjTheLineDefTool_EventSink::Init(const TXString& universalName)
{
	SDefaultLineToolInfo	toolInfo	= this->GetToolInfo();

	toolInfo.fModeGroup					= 2;	// group 2
	toolInfo.fConstrainedChoiceIndex	= 1;	// fModeGroup:	button index 1
	toolInfo.fUnconstrainedChoiceIndex	= 3;	//				button index 3

	this->SetToolInfo( toolInfo );

	VWToolDefaultLine_EventSink::Init( universalName );
}

bool CExtObjTheLineDefTool_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider)
{
	// NOTE! the constructor initializes
	// the default values of fBarState
	
	const IToolModeBarInitProvider* p2 = dynamic_cast<const IToolModeBarInitProvider*> (modeBarInitProvider);
	if (p2)
	{
		TXStringArray imageSpecs;
		imageSpecs.Append("DefaultTools/Images/SampleToolButtonA.png");
		imageSpecs.Append("DefaultTools/Images/SampleToolButtonB.png");
		
		p2->AddRadioModeGroup( /*group 0*/ fBarState[0], imageSpecs);
		p2->AddButtonModeGroup("DefaultTools/Images/SampleToolButtonB.png");
		
		// NOTE! The sample uses Vectorworks icons for this group.
		// This could be dangerous since these numbers are not guaranteed and may change in the future
		imageSpecs.Append("Vectorworks/ModeViewBar/Classes.png");
		p2->AddRadioModeGroup( /*group 2*/ fBarState[2], imageSpecs);
		
		p2->AddButtonModeGroup( /*group 3*/ "Vectorworks/ModeViewBar/Options.png" );
	}
	
	TXStringArray	arrButtonsHelps;
//	arrButtonsHelps.Append( TXString( (short)11100, (short)10 ) );
//	arrButtonsHelps.Append( TXString( (short)11100, (short)11 ) );
//	arrButtonsHelps.Append( TXString( (short)11100, (short)12 ) );
//	arrButtonsHelps.Append( TXString( (short)11100, (short)13 ) );
//	arrButtonsHelps.Append( TXString( (short)11100, (short)14 ) );
//	arrButtonsHelps.Append( TXString( (short)11100, (short)15 ) );
//	arrButtonsHelps.Append( TXString( (short)11100, (short)16 ) );
//	arrButtonsHelps.Append( TXString( (short)11100, (short)17 ) );
//	arrButtonsHelps.Append( TXString( (short)11100, (short)18 ) );
//	pModeBarInitProvider->SetButtonsHelpText( arrButtonsHelps );

	return VWToolDefaultLine_EventSink::DoSetUp( bRestore, modeBarInitProvider );
}

void CExtObjTheLineDefTool_EventSink::DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID)
{
	// save the state so to be able to restore the mode bar proerly
	fBarState[ modeGroupID ]	= newButtonID;

	// just for fun, show a dialog
	TXString	msg;
	msg.Format( "groupID: %d newButtonID: %d oldButtonID: %d", modeGroupID, newButtonID, oldButtonID );
	gSDK->AlertInform( "CExtObjThePointDefTool_EventSink::DoModeEvent", msg );

	VWToolDefaultLine_EventSink::DoModeEvent( modeGroupID, newButtonID, oldButtonID );
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
