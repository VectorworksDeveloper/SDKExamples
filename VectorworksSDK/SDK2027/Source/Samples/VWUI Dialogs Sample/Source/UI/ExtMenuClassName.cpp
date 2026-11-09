#include "StdAfx.h"

#include "ExtMenuClassName.h"

#include "SampleDlg1.h"
#include "SampleDlg2.h"
#include "SampleDlg3.h"
#include "SampleDlg4.h"

const char * DefaultPluginVWRIdentifier() { return "VWUI Dialogs Sample"; }


using namespace UI;

namespace UI
{
	// --------------------------------------------------------------------------------------------------------
	static SMenuDef		gMenuDef = {
		/*Needs*/				0x00,
		/*NeedsNot*/			0x00,
		/*Title*/				{"ExtMenuClassName", "title"},
		/*Category*/			{"ExtMenuClassName", "category"},
		/*HelpText*/			{"ExtMenuClassName", "help"},
		/*VersionCreated*/		16,
		/*VersoinModified*/		0,
		/*VersoinRetired*/		0,
		/*OverrideHelpID*/		" "
	};


	static SMenuChunkDef	gMenuChunksDef[] = {
		{ {"ExtMenuClassName", "item1"}, {"ExtMenuClassName", "item1_help"}, ""},
		{ {"ExtMenuClassName", "item2"}, {"ExtMenuClassName", "item2_help"}, ""},
		{ {"ExtMenuClassName", "item3"}, {"ExtMenuClassName", "item3_help"}, ""},
		{ {"ExtMenuClassName", "item4"}, {"ExtMenuClassName", "item4_help"}, ""},
		{ {NULL, NULL}, {NULL}, NULL }
	};
}


// --------------------------------------------------------------------------------------------------------
// {45A63CAE-98FF-4712-9F44-75C05049EADE}
IMPLEMENT_VWMenuExtension(
	/*Extension class*/	CExtMenuClassName,
	/*Event sink*/		CMenuClassName_EventSink,
	/*Universal name*/	"VWUI Dialogs Sample",
	/*Version*/			1,
	/*UUID*/			0x45a63cae, 0x98ff, 0x4712, 0x9f, 0x44, 0x75, 0xc0, 0x50, 0x49, 0xea, 0xde );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtMenuClassName::CExtMenuClassName(CallBackPtr cbp)
	: VWExtensionMenu( cbp, gMenuDef, gMenuChunksDef )
{
}

CExtMenuClassName::~CExtMenuClassName()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CMenuClassName_EventSink::CMenuClassName_EventSink(IVWUnknown* parent)
	: VWMenu_EventSink( parent )
{
}

CMenuClassName_EventSink::~CMenuClassName_EventSink()
{
}

TXString CMenuClassName_EventSink::GetOverrideHelpID() const
{
	return "";
}

void CMenuClassName_EventSink::DoInterface()
{
	switch( fpMenuChunkInfo->chunkIndex ) {
		case 1:	{
			CMyDialog		dlg;
			dlg.RunDialogLayout( "" );
		} break;
		case 2:	{
			CSampleDlg2		dlg;
			dlg.RunDialogLayout( "" );
		} break;
		case 3:	{
			CSampleDlg3		dlg;
			dlg.RunDialogLayout( "" );
		} break;
		case 4:	{
			CSampleDlg4		dlg;
			dlg.RunDialogLayout( "" );
		} break;
	}
}
