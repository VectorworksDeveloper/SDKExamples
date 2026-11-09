//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtToolResourcePopupSimple.h"
#include "DlgResourcePopupSample.h"

using namespace ResourcePopup;

namespace ResourcePopup
{
// --------------------------------------------------------------------------------------------------------
static SToolDef		gToolDef = {
		/*ToolType*/					eExtensionToolType_Normal,
		/*ParametricName*/				"",
		/*PickAndUpdate*/				ToolDef::pickAndUpdate,
		/*NeedScreenPlane*/				ToolDef::doesntNeedScreenPlane,
		/*Need3DProjection*/			ToolDef::doesntNeed3DView,
		/*Use2DCursor*/					ToolDef::use2DCursor,
		/*ConstrainCursor*/				ToolDef::constrainCursor,
		/*NeedPerspective*/				ToolDef::doesntNeedPerspective,
		/*ShowScreenHints*/				ToolDef::showScreenHints,
		/*NeedsPlanarContext*/			ToolDef::needsPlanarContext,
		/*Message*/						{"ExtToolResourcePopupSimple", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtToolResourcePopupSimple", "tool_title"},
		/*Category*/					{"ExtToolResourcePopupSimple", "tool_category"},
		/*HelpText*/					{"ExtToolResourcePopupSimple", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*OverrideHelpID*/				"",
		/*IconSpec*/					"TesterModule/Images/ExtToolResourcePopupSimple.png",
		/*CursorImageSpec*/				"",
	};
}


// --------------------------------------------------------------------------------------------------------
// {3970633D-36B4-4166-947A-4BD9A79BF57A}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtToolResourcePopupSimple,
	/*Event sink*/		CToolResourcePopupSimple_EventSink,
	/*Universal name*/	"ResourcePopupSimpleTool",
	/*Version*/			1,
	/*UUID*/			0x3970633d, 0x36b4, 0x4166, 0x94, 0x7a, 0x4b, 0xd9, 0xa7, 0x9b, 0xf5, 0x7a );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtToolResourcePopupSimple::CExtToolResourcePopupSimple(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtToolResourcePopupSimple::~CExtToolResourcePopupSimple()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CToolResourcePopupSimple_EventSink::CToolResourcePopupSimple_EventSink(IVWUnknown* parent)
	: VWTool_EventSink( parent )
	, fContent( VectorWorks::Extension::IID_ResourceManagerContent )
{
	fBarState_Shape	= EShape::Box;
}

CToolResourcePopupSimple_EventSink::~CToolResourcePopupSimple_EventSink()
{
}

bool CToolResourcePopupSimple_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* inModeBarInitProvider)
{
	const IToolModeBarInitProvider* modeBarInitProvider = dynamic_cast<const IToolModeBarInitProvider*> (inModeBarInitProvider);

	modeBarInitProvider->AddPullDownResourceModeGroup( TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Content" ), "" );

	TXStringArray images;
	images.Append("Vectorworks/Images/ModeViewBar/Line_Button2.png");
	images.Append("Vectorworks/Images/ModeViewBar/CircleSelection.png");
	images.Append("Vectorworks/Images/ModeViewBar/Wall_Rectangle.png");
	modeBarInitProvider->AddRadioModeGroup( size_t(fBarState_Shape), images);	// configuration

	modeBarInitProvider->AddButtonModeGroup( "Vectorworks/Images/ModeViewBar/EditCurtainWall_SelectionSettings.png" );		// sample dialog

	modeBarInitProvider->AddButtonModeGroup( "Vectorworks/Images/ModeViewBar/Options.png" );		// preferences

	VectorWorks::TVWModeBarButtonHelpArray arrModeBarButtonsHelp;
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Content" ),		TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Content_Help" ), VectorWorks::eModeBarButtonType_RadioMode ) );
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Shape_Line" ),		TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Shape_Line_Help" ), VectorWorks::eModeBarButtonType_RadioMode ) );
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Shape_Circle" ),	TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Shape_Circle_Help" ), VectorWorks::eModeBarButtonType_RadioMode ) );
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Shape_Rect" ),		TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Shape_Rect_Help" ), VectorWorks::eModeBarButtonType_RadioMode ) );
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupSimple", "ToolMode_SampleDlg" ),		TXResStr( "ExtToolResourcePopupSimple", "ToolMode_SampleDlg_Help" ), VectorWorks::eModeBarButtonType_PrefButtonMode ) );
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Preferences" ),	TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Preferences_Help" ), VectorWorks::eModeBarButtonType_PrefButtonMode ) );
	gSDK->SetModeBarButtonsText( arrModeBarButtonsHelp );

	fContent->InitByUnivName( "ResourcePopupObject" );
	fContent->SetEmptyMessage( TXResStr( "ExtToolResourcePopupSimple", "ToolMode_Content_EmptyMsg" ) );

	modeBarInitProvider->PullDownResourcePopupSet( EModeBarGroupSimple::Content, fContent );

	return true;
}

void CToolResourcePopupSimple_EventSink::DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID)
{
	static bool	sRecursiveLock = false;
	switch ( modeGroupID )
	{
		case EModeBarGroupSimple::PrefsButton:
			this->OnPreferences();
			break;

		case EModeBarGroupSimple::SampleDlgButton:
			this->OnSampleDialog();
			break;

		case EModeBarGroupSimple::Configuration:
			fBarState_Shape	= EShape(newButtonID);

			// remove selected item as it is no longer valid
			// after changing the shape from the toolbar
			if ( sRecursiveLock == false )	// only when the user has changed the shape update the content popup
				fpModeBarProvider->PullDownResourcePopupSetSelected( EModeBarGroupSimple::Content, "" );
			break;

		case EModeBarGroupSimple::Content: {
			this->OnContent();

			// update the shape selection
			// lock so it wont affect the shape case as if the user changes it
			TState<bool>	recursiveLockState( sRecursiveLock, true );
			fpModeBarProvider->SetModeGroupValue( EModeBarGroupSimple::Configuration, Sint32(fBarState_Shape) );
		} break;
	}
}

CToolResourcePopupSimple_EventSink::EShape CToolResourcePopupSimple_EventSink::GetShape(const TXString& str)
{
	EShape	result;
	if ( str == "Line" )		result = EShape::Line;
	else if ( str == "Circle" )	result = EShape::Circle;
	else						result = EShape::Box;
	return result;
}

TXString CToolResourcePopupSimple_EventSink::GetShape(const EShape& shape)
{
	TXString	result;
	switch( fBarState_Shape )
	{
		case EShape::Line:		result = "Line";	break;
		case EShape::Circle:	result = "Circle";	break;
		default:
		case EShape::Box:		result = "Box";		break;
	}
	return result;
}

void CToolResourcePopupSimple_EventSink::OnPreferences()
{
	gSDK->SetUndoMethod( kUndoSwapObjects );

	MCObjectHandle hFormat = VWParametricObj::DefineCustomObject( "ResourcePopupObject", true );
	if ( hFormat )
	{
		CGenericParamProvider	formatObj( hFormat );
		TXString	strShape = formatObj.GetParamString( "shape" );
		fBarState_Shape = this->GetShape( strShape );

		// this call would remove the selection from the content
		// leaving the empty message visible
		fpModeBarProvider->PullDownResourcePopupSetSelected( EModeBarGroupSimple::Content, "" );
	}

	gSDK->EndUndoEvent();
}

void CToolResourcePopupSimple_EventSink::OnSampleDialog()
{
	CDlgResourcePopupSample	dlg( fContent );
	if ( dlg.RunDialogLayout( "" ) == kDialogButton_Ok )
	{
		this->OnContent();
	}
}

void CToolResourcePopupSimple_EventSink::OnContent()
{
	bool		dataOk = false;
	TXString	strText;
	double		sizeValue = 0;

	gSDK->SupportUndoAndRemove();
	gSDK->SetUndoMethod( kUndoSwapObjects );

	MCObjectHandle hSymbol = fContent->ImportSelectedResourceToCurrentFile( VectorWorks::eImportResourceConflictResult_Replace );
	if ( hSymbol && VWParametricObj::IsParametricObject( gSDK->FirstMemberObj(hSymbol), "ResourcePopupObject" ) )
	{
		VWParametricObj	paramsSrc( gSDK->FirstMemberObj(hSymbol) );

		dataOk	= true;

		TXString	strShape = paramsSrc.GetParamString( "shape" );
		fBarState_Shape	= this->GetShape( strShape );
		strText			= paramsSrc.GetParamString( "text" );
		sizeValue		= paramsSrc.GetParamReal( "size" );
	}

	gSDK->UndoAndRemove();

	if ( dataOk )
	{
		// we wont use the undo for this 
		// as it will make too much unecessary undo events
		// when the user browsers through the content
		Boolean suspend = true;
		gSDK->SetProgramVariable( 9871, &suspend );

		MCObjectHandle hFormat = VWParametricObj::DefineCustomObject( "ResourcePopupObject", false );
		if ( hFormat )
		{
			CGenericParamProvider	formatObj( hFormat );
			formatObj.SetParamString( "shape", this->GetShape( fBarState_Shape ) );
			formatObj.SetParamString( "text", strText );
			formatObj.SetParamReal( "size", sizeValue );
		}

		suspend = false;
		gSDK->SetProgramVariable( 9871, &suspend );
	}
}

void CToolResourcePopupSimple_EventSink::HandleComplete()
{
	gSDK->SetUndoMethod( kUndoSwapObjects );

	gSDK->DeselectAll();

	VWPoint3D	pt	= this->GetToolPt3D( 0 );

	VWParametricObj	paramObj( "ResourcePopupObject", VWPoint2D(pt.x,pt.y) );

	paramObj.SetParamString( "shape", this->GetShape( fBarState_Shape ) );

	paramObj.ResetObject();

	gSDK->EndUndoEvent();
}


