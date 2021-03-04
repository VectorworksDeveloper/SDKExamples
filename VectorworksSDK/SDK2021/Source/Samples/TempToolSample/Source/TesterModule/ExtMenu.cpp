//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdAfx.h"

#include "ExtMenu.h"
#include "ExtTool.h"
#include "LineObjSelection.h"



using namespace VectorWorks::Filing;
using namespace TesterModule;

namespace TesterModule
{
	// --------------------------------------------------------------------------------------------------------
	static SMenuDef		gMenuDef = {
		/*Needs*/				0x00,
		/*NeedsNot*/			0x00,
		/*Title*/				{"CExtMenu", "title"},
		/*Category*/			{"CExtMenu", "category"},
		/*HelpText*/			{"CExtMenu", "help"},
		/*VersionCreated*/		16,
		/*VersoinModified*/		0,
		/*VersoinRetired*/		0,
		/*OverrideHelpID*/		""
	};

	/*static SSTRResource	gMenuChunksDef[] = {
		{ {"CExtMenu", "item1"}, "" },
		{ {"CExtMenu", "item2"}, "" },
		{ {"CExtMenu", "item3"}, "" },
		{ {"CExtMenu", "item4"}, "" },
		{ {"CExtMenu", "item5"}, "" },
		{ {NULL, NULL}, NULL }
	};*/
}

// --------------------------------------------------------------------------------------------------------
// {4A8EF1B3-8FC4-4A72-B362-3FD919F522EF}
IMPLEMENT_VWMenuExtension(
	/*Extension class*/	CExtMenu,
	/*Event sink*/		CMenu_EventSink,
	/*Universal name*/	"CExtMenu_TempToolSample",
	/*Version*/			1,
	/*UUID*/			0x4a8ef1b3, 0x8fc4, 0x4a72, 0xb3, 0x62, 0x3f, 0xd9, 0x19, 0xf5, 0x22, 0xef );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtMenu::CExtMenu(CallBackPtr cbp)
	: VWExtensionMenu( cbp, gMenuDef, NULL )
//	: VWExtensionMenu( cbp, gMenuDef, gMenuChunksDef )
{
}

CExtMenu::~CExtMenu()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CMenu_EventSink::CMenu_EventSink(IVWUnknown* parent)
	: VWMenu_EventSink( parent )
{
}

CMenu_EventSink::~CMenu_EventSink()
{
}

TXString CMenu_EventSink::GetOverrideHelpID() const
{
	return "";
}

void CMenu_EventSink::DoInterface()
{
	gSDK->SetUndoMethod( kUndoSwapObjects );

	CLineObjSelection&		selContext	= CLineObjSelection::Instance();

	if ( selContext.InitializeFromSelection() )	// check if there is a line object in the selection.
	{

		TXString			strAlert(TXResource( "ErrorsCollectorStrings", "alert" ));
		TXString			strAlertAdvise(TXResource( "ErrorsCollectorStrings", "advise" ));
		TXString			strStretch(TXResource( "ErrorsCollectorStrings", "stretch" ));
		TXString			strMove(TXResource( "ErrorsCollectorStrings", "move" ));
		// call a question dialog.
		short				res			= gSDK->AlertQuestion( strAlert, strAlertAdvise, 0, strStretch, strMove );

		// update the record format object.
		MCObjectHandle		hRecFormat	= VWRecordFormatObj::GetRecordFormat( kStr_TempTool_Record );
		if ( hRecFormat == NULL )
		{
			VWRecordFormatObj	newRecFormat( kStr_TempTool_Record );
			gSDK->AddAfterSwapObject( newRecFormat );

			newRecFormat.AddParamBool( kStrField_Param_TempTool, ( res == 1 ) );	// stretch.
		}

		VWRecordFormatObj	recFormat( kStr_TempTool_Record );
		if ( recFormat != NULL )
		{
			recFormat.SetParamBool( kStrField_Param_TempTool, ( res == 1 ) );		// stretch.
		}

		// call the temp tool.
		const VWIID&	iidTempTool		= CExtTool::_GetIID();
		gSDK->RunTempTool( iidTempTool );
	}

	gSDK->EndUndoEvent();
}