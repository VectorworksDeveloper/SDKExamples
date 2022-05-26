#include "StdAfx.h"

#include "ExtTool.h"

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
		/*OverrideHelpID*/				" ",
		/*Icon Specifier*/				"TesterModule/Images/CExtTool.png",
		/*Cursor Specifier*/			""
	};
}

// --------------------------------------------------------------------------------------------------------
// {DF0D9D08-1704-4c9c-B2BF-18CA526267BA}
IMPLEMENT_VWToolExtension(
	/*Extension class*/	CExtTool,
	/*Event sink*/		CTool_EventSink,
	/*Universal name*/	"CExtTool",
	/*Version*/			1,
	/*UUID*/			0xdf0d9d08, 0x1704, 0x4c9c, 0xb2, 0xbf, 0x18, 0xca, 0x52, 0x62, 0x67, 0xba );

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
	: VWTool_EventSink( parent )
{
}

CTool_EventSink::~CTool_EventSink()
{
}

bool CTool_EventSink::DoSetUp(bool bRestore, const IToolModeBarInitProvider* pModeBarInitProvider)
{

	return true;
}

void CTool_EventSink::DoSetDown(bool bRestore, const IToolModeBarInitProvider* pModeBarInitProvider)
{
	this->ClearAllToolInteractiveObjects();
}

void CTool_EventSink::MouseMove()
{
	this->UpdateToolInteractiveObjects();
}

void CTool_EventSink::HandleComplete()
{
    gSDK->SupportUndoAndRemove();
    gSDK->SetUndoMethod( kUndoSwapObjects );
    gSDK->NameUndoEvent( TXResStr("CExtTool", "ExtToolUndoEvent") );
    
	TXString sym_name("example_sym"); 
	Handle h_sym_container = gSDK->CreateSymbolDefinition(sym_name); 
	if(h_sym_container)
	{
        gSDK->AddAfterSwapObject( h_sym_container );
		WorldRect wr; 
		wr.Set(WorldPt(0.0, 0.0), WorldPt(500.0, 500.0)); 
		Handle hrect = gSDK->CreateRectangle(wr); 
		gSDK->ResetObject(hrect); 
		gSDK->AddObjectToContainer(hrect, h_sym_container);
		gSDK->ResetObject(h_sym_container); 
		VCOMPtr<IFileIdentifier> fileID( IID_FileIdentifier ); 
		if (fileID) { 
			TXString full("C:\\MyProjects\\Test Files\\EmptyFile.vwx"); 
			fileID->Set(full); 
			bool bool_out = false; 
			fileID->ExistsOnDisk(bool_out); 
			fileID->GetFileFullPath(full); 
			if(bool_out){ 
				gSDK->ExportResource(h_sym_container, fileID, false); 
			} 
		}
        
        gSDK->AddBeforeSwapObject( h_sym_container );
        gSDK->DeleteObject(h_sym_container);
        gSDK->EndUndoEvent();
        
	}
    else {
        gSDK->UndoAndRemove();
    }
    
	InternalIndex ind = gSDK->MaxClassID(); 
	TXString cl_name; 
	for(int i = 0; i <= ind; i ++){ 
		Handle hh = gSDK->InternalIndexToHandle(i); 
		if(hh){ 
			short obj_type = gSDK->GetObjectTypeN(hh); 
			if(obj_type == kClassDefNode)
			{ 
				cl_name.Clear(); 
				if(gSDK->ValidClass(i))
				{ 
					gSDK->ClassIDToName(i, cl_name); 
					if(cl_name.GetLength() > 0){ 
					}	
				} 
			} 
		} 
	}
}


void CTool_EventSink::ClearAllToolInteractiveObjects()
{
	VectorWorks::IToolInteractiveDrawPtr toolInteractive;
	gSDK->GetCurrToolInteractiveDraw( & toolInteractive );
	if (toolInteractive)
	{
		toolInteractive->ClearObjects();
	}
}

void CTool_EventSink::UpdateToolInteractiveObjects()
{
	VectorWorks::IToolInteractiveDrawPtr toolInteractive;
	gSDK->GetCurrToolInteractiveDraw( & toolInteractive );
	if ( toolInteractive )
	{
		size_t	ptCnt	= this->GetToolPointsCount();
		if ( ptCnt > 1 )
		{
			VWPoint2D	currPt;
			this->GetToolPtCurren2D( currPt );

			VWLine2DObj	lineObj( toolInteractive->GetObject( kLineNode ) );
			lineObj.SetLine( this->GetToolPt2D( 0 ), currPt );
		}
	}
}
