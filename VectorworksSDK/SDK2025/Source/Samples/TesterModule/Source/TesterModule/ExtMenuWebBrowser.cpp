#include "StdAfx.h"
#include "ExtMenuWebBrowser.h"

#include <Interfaces/VectorWorks/UI/IWebBrowserDlg.h>
using namespace TesterModule;


namespace TesterModule
{
	// --------------------------------------------------------------------------------------------------------
	static SMenuDef		gMenuDef = {
		/*Needs*/			0x00,
		/*NeedsNot*/		0x00,
		/*Title*/			{ "CExtMenuWebBrowser" , "title" },
		/*Category*/		{ "CExtMenuWebBrowser" , "category" },
		/*HelpText*/		{ "CExtMenuWebBrowser" , "help" },
		/*VersionCreated*/	16,
		/*VersoinModified*/	0,
		/*VersoinRetired*/	0
	};

}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------
//// {35169C9D-86AD-42AF-8F21-5893C576A2C2}
IMPLEMENT_VWMenuExtension(
	/*Extension class*/	CExtMenuWebBrowser,
	/*Event sink*/		CMenuWebBrowser_EventSink,
	/*Universal name*/	"CExtMenuWebBrowser",
	/*Version*/			1,
	/*UUID*/			0x35169c9d, 0x86ad, 0x42af, 0x8f, 0x21, 0x58, 0x93, 0xc5, 0x76, 0xa2, 0xc2);

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtMenuWebBrowser::CExtMenuWebBrowser(CallBackPtr cbp)
	: VWExtensionMenu(cbp, gMenuDef, NULL)
	//	: VWExtensionMenu( cbp, gMenuDef, gMenuChunksDef )
{
}

CExtMenuWebBrowser::~CExtMenuWebBrowser()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CMenuWebBrowser_EventSink::CMenuWebBrowser_EventSink(IVWUnknown* parent)
	: VWMenu_EventSink(parent)
{
}

CMenuWebBrowser_EventSink::~CMenuWebBrowser_EventSink()
{
}

void CMenuWebBrowser_EventSink::DoInterface()
{
	using namespace VectorWorks::UI;
	IWebBrowserDlgPtr p( IID_WebBrowserDlg );
	p->SetButtonOk( true, "Ok");
	p->SetButtonCancel(true);
	p->SetButtonHome( true );
	p->SetButtonReload(true);
	p->SetAddressBar(EAddressBarMode::Editable);
	p->SetButtonSettings( true, []() { gSDK->AlertInform(L"Message"); }, "", true );
	p->SetInitialURL("www.google.com");
	p->AddHomeURL("https://www.mtextur.com");
	p->AddHomeURL("http://www.monrovia.com/plant-catalog/plants/1593/katrina-african-iris/");
	p->RunModalDialog("");
	return;
}
