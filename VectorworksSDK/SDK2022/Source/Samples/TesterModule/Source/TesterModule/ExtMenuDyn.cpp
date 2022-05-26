#include "StdAfx.h"

#include "ExtMenuDyn.h"

using namespace TesterModule;

namespace TesterModule
{
	// --------------------------------------------------------------------------------------------------------
	static SMenuDef		gMenuDef = {
		/*Needs*/				0x00,
		/*NeedsNot*/			0x00,
		/*Title*/				{"ExtMenuDyn", "title"},
		/*Category*/			{"ExtMenuDyn", "category"},
		/*HelpText*/			{"ExtMenuDyn", "help"},
		/*VersionCreated*/		16,
		/*VersoinModified*/		0,
		/*VersoinRetired*/		0,
		/*OverrideHelpID*/		"",
	};

	// --------------------------------------------------------------------------------------------------------
	static SMenuChunkDef	gMenuChunkDef[] = {
		{ {"ExtMenuDyn", "item1"}, {"ExtMenuDyn", "item1_help"}, "" },
		{ {"ExtMenuDyn", "item2"}, {"ExtMenuDyn", "item2_help"}, "" },
		// Terminator
		{ {0,0}, {NULL}, NULL }
	};
}


// --------------------------------------------------------------------------------------------------------
// {A61E976F-6FDE-436F-873F-A3F27D061685}
IMPLEMENT_VWMenuExtension(
	/*Extension class*/	CExtMenuDyn,
	/*Event sink*/		CMenuDyn_EventSink,
	/*Universal name*/	"CExtMenuDyn",
	/*Version*/			1,
	/*UUID*/			0xa61e976f, 0x6fde, 0x436f, 0x87, 0x3f, 0xa3, 0xf2, 0x7d, 0x6, 0x16, 0x85 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtMenuDyn::CExtMenuDyn(CallBackPtr cbp)
	: VWExtensionMenu( cbp, gMenuDef, gMenuChunkDef, eMenuChunkType_DynamicVariable )
{
}

CExtMenuDyn::~CExtMenuDyn()
{
}

void CExtMenuDyn::AddMenu(const TXString& newMenu)
{
	VWExtensionMenu::SChunkInfo	newMenuInfo;
	newMenuInfo.fItem	= newMenu;

	TSubItemsVector		arrItems;
	this->GetSubMenuItems( arrItems );
	arrItems.push_back( newMenuInfo );
	this->SetSubMenuItems( arrItems );
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CMenuDyn_EventSink::CMenuDyn_EventSink(IVWUnknown* parent)
	: VWMenu_EventSink( parent )
	, fpParent( dynamic_cast<CExtMenuDyn*>( parent ) )
{
}

CMenuDyn_EventSink::~CMenuDyn_EventSink()
{
}

void CMenuDyn_EventSink::OnDynamicVariableChunkUpdate()
{
}

void CMenuDyn_EventSink::DoInterface()
{
	gSDK->AlertInform( "CMenuDyn_EventSink::DoInterface" );

	if ( fpParent )
	{
		static int a = 0;
		TXString	menuName;
		menuName.Format( "New Menu %d", a ++ );

		fpParent->AddMenu( menuName );
	}
}
