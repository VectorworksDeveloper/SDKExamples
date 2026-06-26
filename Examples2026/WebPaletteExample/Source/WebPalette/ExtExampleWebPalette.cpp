#include "StdAfx.h"

#include "ExtExampleWebPalette.h"


using namespace WebPalette;

// --------------------------------------------------------------------------------------------------------
BEGIN_WebPalette_DISPATCH_MAP(CPaletteJSProvider)
ADD_WebPalette_FUNCTION( "getAllPlantStyles", OnGetAllPlantStyles )
ADD_WebPalette_FUNCTION( "getAllPlantData", OnGetAllPlantData )
ADD_WebPalette_FUNCTION( "updatePlantAssociations", OnUpdatePlantAssociations )
END_WebPalette_DISPATCH_MAP

CPaletteJSProvider::CPaletteJSProvider( IVWUnknown* parent )
	: VWExtensionPaletteJSProvider( parent )
{
}

CPaletteJSProvider::~CPaletteJSProvider()
{
}
void CPaletteJSProvider::OnInit(IInitContext* context)
{
	fWebFrame = context->GetWebFrame();

	// add the integrator object plus access to all recourses to the front-end
	context->AddReourceAccessFunction( "vwAPI", DefaultPluginVWRIdentifier() );

	// Note: Use *Sync or no-sync function depending if you need to access the SDK in the function or not
	// *Sunc functions will be executed on the main thread, and thus will have to wait to be executed, where non-sync ones will be executed immediately, but you cannot use the SDK
	context->AddFunctionPromiseSync( "vwAPI.getAllPlantStyles" );
	context->AddFunctionPromiseSync( "vwAPI.getAllPlantData" );
	context->AddFunctionSync( "vwAPI.updatePlantAssociations" );
}

void CPaletteJSProvider::OnGetAllPlantStyles(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
{
	nlohmann::json jsonResult = nlohmann::json::array();
	// ...

	context->Resolve( jsonResult );
}

void CPaletteJSProvider::OnGetAllPlantData(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
{
	nlohmann::json data;
	data["one"] = "dfds";
	data["two"] = 34;

	context->Resolve( data );
}

void CPaletteJSProvider::OnUpdatePlantAssociations(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
{
	// ...
}

// --------------------------------------------------------------------------------------------------------
CUpdateSupport::CUpdateSupport(CallBackPtr)
{
}

CUpdateSupport::~CUpdateSupport()
{
}

void CUpdateSupport::Init(IObjUpdateSupportContext* context)
{
/*	we'll add those when we need them
	dont forget to register the extension!!!

	context->AcceptNotification( kNotifyDocChange );
	context->AcceptNotification( kNotifySelChange );*/
}

void CUpdateSupport::OnNotification(IObjUpdateSupportContext* context)
{
/*	StatusID	whichChange;
	StatusData	additionalData;
	context->GetNotification( whichChange, additionalData );
	if ( whichChange == kNotifyDocChange )
	{
		IWebPaletteFrame* webFrame = context->GetWebPaletteFrame( CExtWebPaletteExample::_GetIID() );
		if ( gGlobalState.IsValid() && webFrame )
		{
			TXString jsonTxt = "{state: 'kNotifyDocChange'}";

			TXString js = "window.exampleBridge.setDocumentState(";
			js += jsonTxt;
			js += ")";
			webFrame->ExecuteJavaScript( js );
		}
	}
	else if ( whichChange == kNotifySelChange )
	{
		IWebPaletteFrame* webFrame = context->GetWebPaletteFrame( CExtWebPaletteExample::_GetIID() );
		if ( gGlobalState.IsValid() && webFrame )
		{
			TXString jsonTxt = "{state: 'kNotifySelChange'}";

			TXString js = "window.exampleBridge.setSelectionState(";
			js += jsonTxt;
			js += ")";
			webFrame->ExecuteJavaScript( js );
		}
	}*/
}

// --------------------------------------------------------------------------------------------------------

//
// This code is after Vectorworks 2025 SDK. See the header of this file for more info.
//
CExtWebPaletteExample::CExtWebPaletteExample(CallBackPtr)
{
}

CExtWebPaletteExample::~CExtWebPaletteExample()
{
}

void CExtWebPaletteExample::DefineSinks()
{
	this->DefineSink<CPaletteJSProvider>( IID_WebJavaScriptProvider );
}

TXString CExtWebPaletteExample::GetTitle()
{
	return TXResStr("ExtWebPaletteExample", "paletteName");
}

bool CExtWebPaletteExample::GetInitialSize(ViewCoord& outCX, ViewCoord& outCY)
{
	outCX = 1000;
	outCY = 700;
	return true;
}

bool CExtWebPaletteExample::GetMinimalSize(ViewCoord& outCX, ViewCoord& outCY)
{
	outCX = 680;
	outCY = 500;
	return true;
}

// This is practically the same implementation as "VWFC::PluginSupport::GetStandardURL"
// But we must do it because we use RELEASE SDK which doesn't give us URL to the local index.html in the resources in DEBUG
TXString CExtWebPaletteExample::GetInitialURL()
{
	// Change those if your front-end is in a different folder and file
	const TXString	htmlFolderName	= "html";
	const TXString	htmlFile		= "index.html";
	return VWFC::PluginSupport::GetStandardURL( htmlFolderName, htmlFile );
}

// --------------------------------------------------------------------------------------------------------
// /*YOU MUST CHANGE THIS UUID if you copy this code*/	{291F9D08-E795-45E9-A2B0-FDE34A8A0DDE}
IMPLEMENT_VWPaletteExtension(
	/*Extension class*/	CExtWebPaletteExample,
	/*Universal name*/	"WebPaletteExample",
	/*Version*/			1,
	/*UUID*/			/*YOU MUST CHANGE THIS UUID if you copy this code*/	0x291f9d08, 0xe795, 0x45e9, 0xa2, 0xb0, 0xfd, 0xe3, 0x4a, 0x8a, 0xd, 0xde );

// --------------------------------------------------------------------------------------------------------
static SMenuDef		gMenuDef = {
	/*Needs*/				EMenuEnableFlags::DocIsActive,
	/*NeedsNot*/			EMenuEnableFlags::None,
	/*Title*/				{"ExtMenuShowWebPaletteExample", "menu_title"}, 
	/*Category*/			{"ExtMenuShowWebPaletteExample", "menu_category"},
	/*HelpText*/			{"ExtMenuShowWebPaletteExample", "menu_helptext"},
	/*VersionCreated*/		30,
	/*VersoinModified*/		0,
	/*VersoinRetired*/		0,
	/*OverrideHelpID*/		" "
};

// --------------------------------------------------------------------------------------------------------
// {65D73787-53E9-4E11-BFE5-3E2F41A204A0}
IMPLEMENT_VWMenuExtension(
	/*Extension class*/	CExtMenuShowWebPaletteExample,
	/*Event sink*/		CExtMenuShowWebPaletteExample_EventSink,
	/*Universal name*/	"ExtMenuShowWebPaletteExample",
	/*Version*/			1,
	/*UUID*/			0x65d73787, 0x53e9, 0x4e11, 0xbf, 0xe5, 0x3e, 0x2f, 0x41, 0xa2, 0x4, 0xa0 );

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtMenuShowWebPaletteExample::CExtMenuShowWebPaletteExample(CallBackPtr cbp)
	: VWExtensionMenu( cbp, gMenuDef )
{
}

CExtMenuShowWebPaletteExample::~CExtMenuShowWebPaletteExample()
{
}

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
CExtMenuShowWebPaletteExample_EventSink::CExtMenuShowWebPaletteExample_EventSink(IVWUnknown* parent)
	: VWMenu_EventSink( parent )
{
}

CExtMenuShowWebPaletteExample_EventSink::~CExtMenuShowWebPaletteExample_EventSink()
{
}

void CExtMenuShowWebPaletteExample_EventSink::DoInterface()
{
	gSDK->SetWebPaletteVisibility( CExtWebPaletteExample::_GetIID(), true );
}

// --------------------------------------------------------------------------------------------------------
