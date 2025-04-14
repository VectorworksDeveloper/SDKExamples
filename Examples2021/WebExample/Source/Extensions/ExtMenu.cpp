#include "StdAfx.h"

#include "ExtMenu.h"
#include "../Data/Data.h"

using namespace VectorWorks::UI;
using namespace Extensions;

namespace Extensions
{
	// --------------------------------------------------------------------------------------------------------
	static SMenuDef		gMenuDef = {
		/*Needs*/			0x00,
		/*NeedsNot*/		0x00,
		/*Title*/			{"CMenuDownload", "title"},
		/*Category*/		{"CMenuDownload", "category"},
		/*HelpText*/		{"CMenuDownload", "help"},
		/*VersionCreated*/	25,
		/*VersoinModified*/	0,
		/*VersoinRetired*/	0
	};

	/*static SSTRResource	gMenuChunksDef[] = {
		{ {12000, 4}, "" },
		{ {12000, 5}, "" },
		{ {12000, 6}, "" },
		{ {12000, 7}, "" },
		{ {12000, 8}, "" },
		{ {NULL, NULL}, NULL }
	};*/
}

// --------------------------------------------------------------------------------------------------------
// /*YOU MUST CHANGE THIS UUID if you copy this code*/ {30DD1A73-D363-44C8-BA7F-6ACFA76EE772}
IMPLEMENT_VWMenuExtension(
	/*Extension class*/	CMenuDownload,
	/*Event sink*/		CMenuDownload_EventSink,
	/*Universal name*/	"WebExampleMenu",
	/*Version*/			1,
	/*UUID*/			/*YOU MUST CHANGE THIS UUID if you copy this code*/ 0x30dd1a73, 0xd363, 0x44c8, 0xba, 0x7f, 0x6a, 0xcf, 0xa7, 0x6e, 0xe7, 0x72 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CMenuDownload::CMenuDownload(CallBackPtr cbp)
	: VWExtensionMenu( cbp, gMenuDef, NULL )
//	: VWExtensionMenu( cbp, gMenuDef, gMenuChunksDef )
{
}

CMenuDownload::~CMenuDownload()
{
}


// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
// this is a flag that will turn on log files created in the users folder \Plug-ins\Data
// this can help tracking down issues on user machines
bool gLocalDebugLogFileCreateEnabled = false;

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CMenuDownload_EventSink::CMenuDownload_EventSink(IVWUnknown* parent)
	: VWMenu_EventSink( parent )
	, fWebContext( "https://www.myserver.com")
{
}

CMenuDownload_EventSink::~CMenuDownload_EventSink()
{
}

void CMenuDownload_EventSink::DoInterface()
{
	// this is for debugging purposes, that will make more verbose logging
	NNA_SCOPE {
 		Boolean bCtrlCmdKeyDown = false;
#ifdef _WINDOWS
		gSDK->GetProgramVariable( varToolCtrlCmdKeyDown, & bCtrlCmdKeyDown );
#else
		gSDK->GetProgramVariable( varToolOptionKeyDown, & bCtrlCmdKeyDown );
#endif

		if ( ! gLocalDebugLogFileCreateEnabled )
			gLocalDebugLogFileCreateEnabled	= bCtrlCmdKeyDown;
	}

	fWebContext.LogInIfNeeded( false );

	auto onGetRequestHeadersCallback = [&](const TXString& url, TStringKeyValueMap& outHeaders)
	{
		outHeaders["access_token"]	= fWebContext.GetOAuthToken();
		outHeaders["user_token"]	= fWebContext.GetUserToken();
	};

	TXString closedWithURL;
	IWebBrowserDlg::TOnBeforeOpenLinkCallback	onBeforeOpenLinkCallback = [&](const TXString& url, bool isRedirect)
	{
		EEventResult result = EEventResult::Proceed;
		if ( url.Right(4) == ".zip" ) // operator == compares case insensitive
		{
			closedWithURL = url;
			result = EEventResult::CloseDialogWithOk;
		}

		return result;
	};

	IWebBrowserDlg::TOnBeforeOpenLinkCallback	onBeforeOpenNewWndLinkCallback = [](const TXString& url, bool isRedirect)
	{
		gSDK->OpenURL( url );
		return EEventResult::Block;
	};

	IWebBrowserDlgPtr dlg( IID_WebBrowserDlg );
	dlg->SetTitle( TXResStr("CMenuDownload", "WebDlg Title") );
	dlg->SetAddressBar( EAddressBarMode::ReadOnly );
	dlg->SetInitialURL( fWebContext.GetServerURL() );
	dlg->SetCallback_OnGetRequestHeaders( onGetRequestHeadersCallback );
	dlg->SetCallback_OnBeforeOpenLink( onBeforeOpenLinkCallback );
	dlg->SetCallback_OnBeforeOpenNewWindowLink( onBeforeOpenNewWndLinkCallback );
	if ( dlg->RunModalDialog( "DialogHelpID" ) == EWebBrowserDlgRes::OKButton )
	{
	}
}

