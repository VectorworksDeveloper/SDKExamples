//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtToolResourcePopupComplex.h"
#include "DlgResourcePopupComplex.h"

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
		/*Message*/						{"ExtToolResourcePopupComplex", "tool_message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"ExtToolResourcePopupComplex", "tool_title"},
		/*Category*/					{"ExtToolResourcePopupComplex", "tool_category"},
		/*HelpText*/					{"ExtToolResourcePopupComplex", "tool_help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*OverrideHelpID*/				"",
		/*IconSpec*/					"TesterModule/Images/ExtToolResourcePopupComplex.png",
		/*CursorImageSpec*/				"",
	};
}


// --------------------------------------------------------------------------------------------------------
// {D7D9EF74-8285-4B08-985B-5C30A17A1821}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtToolResourcePopupComplex,
	/*Event sink*/		CToolResourcePopupComplex_EventSink,
	/*Universal name*/	"ResourcePopupComplexTool",
	/*Version*/			1,
	/*UUID*/			0xd7d9ef74, 0x8285, 0x4b08, 0x98, 0x5b, 0x5c, 0x30, 0xa1, 0x7a, 0x18, 0x21 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtToolResourcePopupComplex::CExtToolResourcePopupComplex(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtToolResourcePopupComplex::~CExtToolResourcePopupComplex()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CToolResourcePopupComplex_EventSink::CToolResourcePopupComplex_EventSink(IVWUnknown* parent)
	: VWTool_EventSink( parent )
	, fContent( VectorWorks::Extension::IID_ResourceManagerContent )
{
	fBarState_Insert = EToolInsertMode::Point;
}

CToolResourcePopupComplex_EventSink::~CToolResourcePopupComplex_EventSink()
{
}

bool CToolResourcePopupComplex_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* inModeBarInitProvider)
{
	TXStringArray images;
	images.Append("Vectorworks/ModeViewBar/SymbolsObjectPlugIn_Mode6.png");
	images.Append("Vectorworks/ModeViewBar/SymbolsObjectPlugIn_Mode8.png");
	inModeBarInitProvider->AddRadioModeGroup( size_t( fBarState_Insert ), images );

	inModeBarInitProvider->AddPullDownResourceModeGroup( TXResStr( "ExtToolResourcePopupComplex", "ToolMode_Content" ), "" );

	inModeBarInitProvider->AddButtonModeGroup( "Vectorworks/Images/ModeViewBar/Options.png" );		// preferences

	VectorWorks::TVWModeBarButtonHelpArray arrModeBarButtonsHelp;
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupComplex", "ToolMode_Insert" ),		TXResStr( "ExtToolResourcePopupComplex", "ToolMode_Insert_Help" ), VectorWorks::eModeBarButtonType_RadioMode ) );
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupComplex", "ToolMode_PickUp" ),		TXResStr( "ExtToolResourcePopupComplex", "ToolMode_PickUp_Help" ), VectorWorks::eModeBarButtonType_RadioMode ) );
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupComplex", "ToolMode_Content" ),		TXResStr( "ExtToolResourcePopupComplex", "ToolMode_Content_Help" ), VectorWorks::eModeBarButtonType_RadioMode ) );
	arrModeBarButtonsHelp.Append( VectorWorks::SModeBarButtonHelp( TXResStr( "ExtToolResourcePopupComplex", "ToolMode_Preferences" ),	TXResStr( "ExtToolResourcePopupComplex", "ToolMode_Preferences_Help" ), VectorWorks::eModeBarButtonType_PrefButtonMode ) );
	gSDK->SetModeBarButtonsText( arrModeBarButtonsHelp );

	fContent->InitByInternalID( kInternalID_Plant );
	fContent->SetEmptyMessage( TXResStr( "ExtToolResourcePopupComplex", "ToolMode_Content_EmptyMsg" )  );
	fContent->SetFilter( (THandleFilterCallback) [](MCObjectHandle h)
	{
		TXString name;
		gSDK->GetObjectName( h, name );
		return name != "Test";
	} );

	inModeBarInitProvider->PullDownResourcePopupSet( EModeBarGroupComplex::Content, fContent );

	TXString currName = fpModeBarProvider->PullDownResourcePopupGetSelected( EModeBarGroupComplex::Content );
	
	if ( fContent->IsSelectedItemValid() )
	{
		if ( fContent->GetSelectedResourceIsDocument() && !currName.IsEmpty() )
		{
			MCObjectHandle existingDocumentSymbol = gSDK->GetNamedObject( currName );
			if ( !existingDocumentSymbol )
			{
				fpModeBarProvider->PullDownResourcePopupSetSelected( EModeBarGroupComplex::Content, "" );
			}
		}
	}
	else
	{
		fpModeBarProvider->PullDownResourcePopupSetSelected( EModeBarGroupComplex::Content, "" );
	}

	return true;
}

void CToolResourcePopupComplex_EventSink::DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID)
{
	if ( modeGroupID == EModeBarGroupComplex::InsertMode)
	{
		fBarState_Insert = (EToolInsertMode)newButtonID;
	}
	else if ( modeGroupID == EModeBarGroupComplex::Content )
	{
		this->OnContent();
	}
	else if ( modeGroupID == EModeBarGroupComplex::PrefsButton )
	{
		this->OnPreferences();
	}
}

void CToolResourcePopupComplex_EventSink::GetCursorSpecifier(TXString& cursorSpecifier)
{
	if ( fBarState_Insert == EToolInsertMode::Point )
	{
		cursorSpecifier = "Vectorworks/Cursors/SmallCrosshair.png";
	}
	else if ( fBarState_Insert == EToolInsertMode::Pickup )
	{
		cursorSpecifier	= "LandscapeIrrigation/Images/Cursors/EmptyEyedropper.png";
	}
}

void CToolResourcePopupComplex_EventSink::HandleComplete()
{
	if ( fBarState_Insert == EToolInsertMode::Point )
	{
		// init the undo.
		gSDK->SetUndoMethod( kUndoSwapObjects );

		TXString		resourceName	= fpModeBarProvider->PullDownResourcePopupGetSelected( EModeBarGroupComplex::Content );
		MCObjectHandle	hSymbol			= gSDK->GetNamedObject( resourceName );

		if ( hSymbol == nullptr )
		{
			hSymbol = fContent->ImportSelectedResourceToCurrentFile( VectorWorks::eImportResourceConflictResult_AskWithUI );
		}

		VWSymbolObj		newObj( hSymbol, VWPoint2D( 0, 0 ), 0 );
		gSDK->AddObjectToContainer( newObj, gSDK->GetActiveLayer() );

		fpModeBarProvider->PullDownResourcePopupSetSelected( EModeBarGroupComplex::Content, resourceName );

		// end the undo.
		gSDK->EndUndoEvent();
	}
	else if ( fBarState_Insert == EToolInsertMode::Pickup )
	{
		VWPoint2D		pt0				= this->GetToolPt2D( 0 );
		WorldPt			currentPoint( pt0.x, pt0.y );
		MCObjectHandle	currentObj	= gSDK->ObjectNearCoordPt( currentPoint );
		if ( currentObj && gSDK->GetObjectTypeN( currentObj ) == kSymbolNode )
		{
			VWSymbolObj		symbolObj( currentObj );
			MCObjectHandle	hSymbol = symbolObj.GetSymbolDef();
			TXString		name;
			gSDK->GetObjectName( hSymbol, name );

			fpModeBarProvider->PullDownResourcePopupSetSelected( EModeBarGroupComplex::Content, name );
		}
	}
}

void CToolResourcePopupComplex_EventSink::OnPreferences()
{
	TXString		resourceName	= fpModeBarProvider->PullDownResourcePopupGetSelected( EModeBarGroupComplex::Content );

	CDlgResourcePopupComplex	dlg( resourceName );
	if ( dlg.RunDialogLayout( "" ) == kDialogButton_Ok )
	{
		// init the undo.
		gSDK->SetUndoMethod( kUndoSwapObjects );

		TXString		currName	= dlg.GetSelectedItem();
		MCObjectHandle	hSymbol		= gSDK->GetNamedObject( currName );
		
		if ( hSymbol == nullptr )
		{
			hSymbol = fContent->ImportSelectedResourceToCurrentFile( VectorWorks::eImportResourceConflictResult_AskWithUI );
		}

		fpModeBarProvider->PullDownResourcePopupSetSelected( EModeBarGroupComplex::Content, currName );

		// end the undo.
		gSDK->EndUndoEvent();
	}
}

void CToolResourcePopupComplex_EventSink::OnContent()
{
	TXString		currName				= fpModeBarProvider->PullDownResourcePopupGetSelected( EModeBarGroupComplex::Content );
	MCObjectHandle	existingDocumentSymbol	= nullptr;

	if ( !fContent->GetSelectedResourceIsDocument() )
	{
		existingDocumentSymbol = gSDK->GetNamedObject( currName );
	}

	if ( existingDocumentSymbol )
	{
		gSDK->SetUndoMethod( kUndoSwapObjects );

		MCObjectHandle hSymbol = fContent->ImportSelectedResourceToCurrentFile( VectorWorks::eImportResourceConflictResult_Replace );
		if ( hSymbol )
		{
			TXString name;
			gSDK->GetObjectName( hSymbol, name );

			fpModeBarProvider->PullDownResourcePopupSetSelected( EModeBarGroupComplex::Content, name );
		}
		else
		{
			fpModeBarProvider->PullDownResourcePopupSetSelected( EModeBarGroupComplex::Content, currName );
		}

		gSDK->EndUndoEvent();
	}
}
