//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtTool.h"
#include "ExtMenu.h"
#include "LineObjSelection.h"

using namespace VectorWorks::Filing;
using namespace TesterModule;

namespace TesterModule
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
		/*Message*/						{"CExtTool", "message"},
		/*WaitMoveDistance*/			0,
		/*ConstraintFlags*/				0,
		/*BarDisplay*/					kToolBarDisplay_XYClLaZo,
		/*MinimumCompatibleVersion*/	900,
		/*Title*/						{"CExtTool", "title"},
		/*Category*/					{"CExtTool", "category"},
		/*HelpText*/					{"CExtTool", "help"},
		/*VersionCreated*/				16,
		/*VersoinModified*/				0,
		/*VersoinRetired*/				0,
		/*OverrideHelpID*/				"",
		/*IconSpec*/					"",
		/*CursorImageSpec*/				"",
	};
}

// --------------------------------------------------------------------------------------------------------
// {082B22D1-1AC2-4C5A-BE76-62576F5E81F5}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtTool,
	/*Event sink*/		CTool_EventSink,
	/*Universal name*/	"CExtTool_TempToolSample",
	/*Version*/			1,
	/*UUID*/			0x82b22d1, 0x1ac2, 0x4c5a, 0xbe, 0x76, 0x62, 0x57, 0x6f, 0x5e, 0x81, 0xf5 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtTool::CExtTool(CallBackPtr cbp)
	: VWExtensionTool( cbp, gToolDef )
{
}

CExtTool::~CExtTool()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CTool_EventSink::CTool_EventSink(IVWUnknown* parent)
	: VWToolDefaultLine_EventSink( parent, "" )
	, fToolRecFormat( kStr_TempTool_Record )
{
	fDoStretch			= true;
}

CTool_EventSink::~CTool_EventSink()
{
}

bool CTool_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider)
{
	fDoStretch			= true;

	if ( fToolRecFormat == NULL )
	{
		fToolRecFormat	= VWRecordFormatObj::GetRecordFormat( kStr_TempTool_Record );
	}

	if ( fToolRecFormat != NULL )
	{
		fDoStretch		= fToolRecFormat.GetParamBool( kStrField_Param_TempTool );
	}

	return	true;
}

void CTool_EventSink::HandleComplete()
{
	CLineObjSelection&	selContext	= CLineObjSelection::Instance();

	MCObjectHandle	hSelLine		= selContext.Get();
	if ( hSelLine == NULL )
	{
		//assert
		return;
	}

	// get tool line points.
	VWPoint2D		linePt0			= this->GetToolPt2D( 0 );
	VWPoint2D		linePt1			= this->GetToolPt2D( 1 );
	VWLine2D		toolLine( linePt0, linePt1 );

	// check the tool line.
	double			lineA, lineB, lineC;
	toolLine.CalcLineEquation( lineA, lineB, lineC );

	if ( ! MathUtils::Equalish( Abs( lineA ), 0.0, VWPoint2D::sEpsilon ) )	// line is not horizontal (not parallel to Ox).
	{
		VWLine2DObj	lineObj( hSelLine );
		VWPoint2D	startLnPt		= lineObj.GetStartPoint();
		VWPoint2D	endLnPt			= lineObj.GetEndPoint();

		// project point on the tool line
		VWPoint2D	newEndLnPt		= toolLine.PtPerpLine( endLnPt );

		// get the movement vector.
		VWPoint2D	vec				= ( newEndLnPt - endLnPt );

		if ( fDoStretch )
		{
			// stretch the line object.
			lineObj.SetEndPoint( endLnPt + vec );
		}
		else
		{
			// move the line object.
			lineObj.SetStartPoint( startLnPt + vec );
			lineObj.SetEndPoint( endLnPt + vec );
		}
	}
	else																	// line is horizontal (parallel to Ox).
	{
		// alert dialog.
	}
}


