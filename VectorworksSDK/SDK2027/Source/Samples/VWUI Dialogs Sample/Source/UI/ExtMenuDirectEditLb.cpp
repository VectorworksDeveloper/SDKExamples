#include "StdAfx.h"

#include "ExtMenuDirectEditLb.h"
#include "DlgDirectEditListBrowser.h"

using namespace VectorWorks::Filing;
using namespace UI;


namespace DirectEditListBrowser
{
	// --------------------------------------------------------------------------------------------------------
	static SMenuDef		gMenuDef = {
		/*Needs*/			0x00,
		/*NeedsNot*/		0x00,
		/*Title*/			{"ExtMenuDirectEditLb", "title"},
		/*Category*/		{"ExtMenuDirectEditLb", "category"},
		/*HelpText*/		{"ExtMenuDirectEditLb", "help"},
		/*VersionCreated*/	26,
		/*VersoinModified*/	0,
		/*VersoinRetired*/	0
	};
}

// --------------------------------------------------------------------------------------------------------
// {ACC6EE12-7A4B-45AF-AD23-2E462710E87A}
IMPLEMENT_VWMenuExtension(
	/*Extension class*/	CExtMenuDirectEditLb,
	/*Event sink*/		CMenuDirectEditLb_EventSink,
	/*Universal name*/	"DirectEditLb",
	/*Version*/			1,
	/*UUID*/			0x91bcb1e8, 0x5e28, 0x4107, 0xbf, 0x6, 0xa4, 0x47, 0x7e, 0x39, 0x2a, 0xf );



// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtMenuDirectEditLb::CExtMenuDirectEditLb(CallBackPtr cbp)
	: VWExtensionMenu( cbp, DirectEditListBrowser::gMenuDef, NULL  )
{
}

CExtMenuDirectEditLb::~CExtMenuDirectEditLb()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CMenuDirectEditLb_EventSink::CMenuDirectEditLb_EventSink(IVWUnknown* parent)
	: VWMenu_EventSink( parent )
{
}

CMenuDirectEditLb_EventSink::~CMenuDirectEditLb_EventSink()
{
}

void CMenuDirectEditLb_EventSink::DoInterface()
{
	CDlgDirectEditListBrowser directEditDlg;

	if ( directEditDlg.RunDialogLayout( "DirectEditLb" ) == EDialogButton::kDialogButton_Ok )
	{

	}
}
