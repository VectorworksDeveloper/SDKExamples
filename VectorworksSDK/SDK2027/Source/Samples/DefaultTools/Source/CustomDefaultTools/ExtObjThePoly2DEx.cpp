#include "StdAfx.h"

#include "ExtObjThePoly2DEx.h"

using namespace CustomDefaultTools;

namespace CustomDefaultTools
{
	// --------------------------------------------------------------------------------------------------------
	static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Normal,
		/*ParametricName*/				"SampleToolDef_Poly2DEx",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtObjThePoly2DEx", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtObjThePoly2DEx", "tool_title"},
		/*Category*/					{"ExtObjThePoly2DEx", "tool_category"},
		/*HelpText*/					{"ExtObjThePoly2DEx", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*contextual help*/				"",
		/*Icon Specifier*/				"DefaultTools/Images/ExtObjThePoly2DDefTool.png",
		/*Cursor Specifier*/			"Vectorworks/Cursors/SmallCrosshair.png"
	};

	// --------------------------------------------------------------------------------------------------------
	static SParametricDef gParametricDef = {
		/*LocalizedName*/			{"ExtObjThePoly2DEx", "localized_name"},
		/*SubType*/					kParametricSubType_2DPath,
		/*ResetOnMove*/				false,
		/*ResetOnRotate*/			false,
		/*WallInsertOnEdge*/		false,
		/*WallInsertNoBreak*/		false,
		/*WallInsertHalfBreak*/		false,
		/*WallInsertHideCaps*/		false,
	};

/*	static SParametricParamChc	gArrChoices[] = {
		{ 128,	"Line",					{"ExtObjThePoly2DEx", "choice1"} },
		{ 128,	"Arc",					{"ExtObjThePoly2DEx", "choice2"} },
		{ 128,	"Bezier",				{"ExtObjThePoly2DEx", "choice3"} },
		{ 128,	"None",					{"ExtObjThePoly2DEx", "choice4"} },
		//------
		{ 129,	"Default Legend",		{"ExtObjThePoly2DEx", "choice5"} },
		//------
		// TERMINATE
		{ NULL, NULL, {0,0} }
	};
*/
	static SParametricParamDef gArrParameters[] = {
		{ "p1",			{"ExtObjThePoly2DEx", "param1"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p2",			{"ExtObjThePoly2DEx", "param2"},		"False",	"False",	kFieldBoolean,		0 },
		{ "p3",			{"ExtObjThePoly2DEx", "param3"},		"",			"",			kFieldText,			0 },
		{ "p4",			{"ExtObjThePoly2DEx", "param4"},		"",			"",			kFieldText,			0 },
		{ "p5",			{"ExtObjThePoly2DEx", "param5"},		"2\"",		"2\"",		kFieldCoordDisp,	0 },
		{ "p6",			{"ExtObjThePoly2DEx", "param6"},		"Auto",		"Auto",		kFieldPopUp,		128 },
		{ "p7",			{"ExtObjThePoly2DEx", "param7"},		"Auto",		"Auto",		kFieldPopUp,		129 },
		// TERMINATE
		{ "", {0,0}, "", "", EFieldStyle(0), 0 }
	};
}

// --------------------------------------------------------------------------------------------------------
// {ACB9A4E8-A9FB-4BEA-98D0-B512A1D47373}
IMPLEMENT_VWParametricExtension(
	/*Extension class*/	CExtObjThePoly2D,
	/*Event sink*/		CObjThePoly2D_EventSink,
	/*Universal name*/	"SampleToolDef_Poly2DEx",
	/*Version*/			1,
	/*UUID*/			0xacb9a4e8, 0xa9fb, 0x4bea, 0x98, 0xd0, 0xb5, 0x12, 0xa1, 0xd4, 0x73, 0x73 );

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
// {F5E5CAEA-7A91-4A76-A231-8B47D5CE0E87}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtObjThePoly2DDefTool,
	/*Event sink*/		CExtObjThePoly2DDefTool_EventSink,
	/*Universal name*/	"SampleToolDef_Poly2DToolEx",
	/*Version*/			1,
	/*UUID*/			0xf5e5caea, 0x7a91, 0x4a76, 0xa2, 0x31, 0x8b, 0x47, 0xd5, 0xce, 0xe, 0x87 );

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
	: VWToolDefault2DPoly_EventSink( parent, "SampleToolDef_Poly2DEx" )
{
	memset( fBarState, 0, sizeof(fBarState) );

	// default values for our groups
	fBarState[0]	= 0;
	fBarState[2]	= 0;
}

CExtObjThePoly2DDefTool_EventSink::~CExtObjThePoly2DDefTool_EventSink()
{
}

void CExtObjThePoly2DDefTool_EventSink::Init(const TXString& universalName)
{
	SDefault2DPolyToolInfo	toolInfo	= this->GetToolInfo();

	toolInfo.fModeGroup			= 2;	// group 2
	toolInfo.fFiletRadiusGroup	= 3;	// group 3

	toolInfo.fCornerVertChoiceIndex	= 0;	//fModeGroup:	button index 0	
	toolInfo.fBezierVertChoiceIndex	= 1;	//				button index 1
	toolInfo.fCubicVertChoiceIndex	= 2;	//				button index 2
	toolInfo.fTangetChoiceIndex		= 3;	//				button index 3
	toolInfo.fPointOnArcChoiceIndex	= 4;	//				button index 4
	toolInfo.fArcVertChoiceIndex	= 5;	//				button index 5

	this->SetToolInfo( toolInfo );

	VWToolDefault2DPoly_EventSink::Init( universalName );
}

bool CExtObjThePoly2DDefTool_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider)
{
	// NOTE! the constructor initializes
	// the default values of fBarState

	TXStringArray group0ImageSpecs;
	group0ImageSpecs.Append("DefaultTools/Images/SampleToolButtonA.png");
	group0ImageSpecs.Append("DefaultTools/Images/SampleToolButtonB.png");
	
	modeBarInitProvider->AddRadioModeGroup( /*group 0*/ fBarState[0], group0ImageSpecs);
	modeBarInitProvider->AddButtonModeGroup( /*group 1*/ "DefaultTools/Images/SampleToolButtonB.png");
		
	TXStringArray group2ImageSpecs;
	group2ImageSpecs.Append("DefaultTools/Images/SampleToolButtonA.png");
	group2ImageSpecs.Append("DefaultTools/Images/SampleToolButtonB.png");
	group2ImageSpecs.Append("DefaultTools/Images/SampleToolButtonA.png");
	group2ImageSpecs.Append("DefaultTools/Images/SampleToolButtonB.png");
	group2ImageSpecs.Append("DefaultTools/Images/SampleToolButtonA.png");
	group2ImageSpecs.Append("DefaultTools/Images/SampleToolButtonB.png");
	modeBarInitProvider->AddRadioModeGroup( /*group 2*/ fBarState[2], group2ImageSpecs);
		
	modeBarInitProvider->AddButtonModeGroup( /*group 3*/ "Vectorworks/ModeViewBar/Options.png" );	

	TXStringArray	arrButtonsHelps;
	arrButtonsHelps.Append( TXString( TXResStr("ExtObjThePoly2DEx", "buttonHelp_A" ) ) );
	arrButtonsHelps.Append( TXString( TXResStr("ExtObjThePoly2DEx", "buttonHelp_B" ) ) );
	arrButtonsHelps.Append( TXString( TXResStr("ExtObjThePoly2DEx", "buttonHelp_C" ) ) );
	arrButtonsHelps.Append( TXString( TXResStr("ExtObjThePoly2DEx", "buttonHelp_D" ) ) );
	arrButtonsHelps.Append( TXString( TXResStr("ExtObjThePoly2DEx", "buttonHelp_E" ) ) );
	arrButtonsHelps.Append( TXString( TXResStr("ExtObjThePoly2DEx", "buttonHelp_F" ) ) );
	arrButtonsHelps.Append( TXString( TXResStr("ExtObjThePoly2DEx", "buttonHelp_G" ) ) );
	arrButtonsHelps.Append( TXString( TXResStr("ExtObjThePoly2DEx", "buttonHelp_I" ) ) );
	arrButtonsHelps.Append( TXString( TXResStr("ExtObjThePoly2DEx", "buttonHelp_J" ) ) );
	modeBarInitProvider->SetButtonsHelpText( arrButtonsHelps );

	return VWToolDefault2DPoly_EventSink::DoSetUp( bRestore, modeBarInitProvider );
}

void CExtObjThePoly2DDefTool_EventSink::DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID)
{
	// save the state so to be able to restore the mode bar proerly
	fBarState[ modeGroupID ]	= newButtonID;

	// just for fun, show a dialog
	TXString	msg;
	msg.Format( "groupID: %d newButtonID: %d oldButtonID: %d", modeGroupID, newButtonID, oldButtonID );
	gSDK->AlertInform( "CExtObjThePoly2DDefTool_EventSink::DoModeEvent", msg );

	VWToolDefault2DPoly_EventSink::DoModeEvent( modeGroupID, newButtonID, oldButtonID );
}

void CExtObjThePoly2DDefTool_EventSink::HandleComplete()
{
#if 1
	// call the default if you need
	VWToolDefault2DPoly_EventSink::Default();
#else
	MCObjectHandle	hPath	= this->DefaultHandleCreate();

	if ( VWPolygon2DObj::IsPoly2DObject( hPath ) )
	{
		VWDialog::AlertInform( "use the template object" );
	}

#endif
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


	extProps->SetObjectProperty( objectID, kObjXPropDefaultPropertyUI, (Sint8)kUseAppropriateLocationWidget );
	extProps->SetObjectProperty( objectID, kObjXPropShowLinearDirection, true );


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
