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

static TXString Custom_GetStandardURL(const TXString& htmlFolderName, const TXString& htmlFile)
{
	using namespace VectorWorks::Filing;
	
	TXString	fileFullPath;

#if !defined(DEV_BLD) && !defined(_DEBUG_FAST) && !defined(DEBUG_EXTERNAL)
	// make a copy of the site off of the bundled resources for release
	TXString resRoot = TXString(DefaultPluginVWRIdentifier()) + "/" + htmlFolderName + "/";
	VectorWorks::Filing::IFolderIdentifierPtr	rootFolder( VectorWorks::Filing::IID_FolderIdentifier );
	rootFolder->Set( kExternalDataFolder, true, resRoot );
	rootFolder->CreateOnDisk();

	VectorWorks::Filing::IFolderIdentifierPtr outputFolderID;
	VectorWorks::Filing::IFileIdentifierPtr	outputFileID( VectorWorks::Filing::IID_FileIdentifier );
	VectorWorks::Filing::IRawOSFilePtr outputRawFile( VectorWorks::Filing::IID_RawOSFile );

	gSDK->EnumerateVWResources( resRoot, true, [&](const TXString& resourceIdentifier) {
		TXResource	res( resourceIdentifier );

		TXString fileName = resourceIdentifier.Mid( resRoot.GetLength() );
		outputFileID->Set( rootFolder, fileName );

		outputFileID->GetFolder( & outputFolderID );
		outputFolderID->CreateOnDisk();

		outputRawFile->Open( outputFileID, false, true, false, true );
		outputRawFile->Write( 0, res.Size(), res.Buffer() );
		outputRawFile->Close();

		if ( fileName.Right(htmlFile.GetLength()) == htmlFile )
			outputFileID->GetFileFullPath( fileFullPath );
	});

	bool exist = false;
	outputFileID->ExistsOnDisk( exist );
	DSTOPIF(!exist, (kVStanev, "Web-palette required web-file cannot be found for the patched up Debug build. Make sure the list is correct if you use the non-default VWExtensionWebPalette, or consult with Vlado!"));
#else
	// the debug versions use schortcut for the resource
	// we want to use that so we can use the site we are developing to make direct changes, instead of a copy
	VectorWorks::Filing::IFileIdentifierPtr	outputFileID( VectorWorks::Filing::IID_FileIdentifier );
#ifdef _WINDOWS
	outputFileID->Set( kExternalsFolder, false, TXString("_WebPaletteExample/")+TXString(DefaultPluginVWRIdentifier())+".vwr/" + htmlFolderName + "/" + htmlFile );
#else
	outputFileID->Set( kExternalsFolder, false, TXString("_WebPaletteExample/")+TXString(DefaultPluginVWRIdentifier())+".vwlibrary/Contents/Resources/" + TXString(DefaultPluginVWRIdentifier())+".vwr/" + htmlFolderName + "/" + htmlFile );
#endif
	IPathResolverPtr resolver( IID_PathResolver );
	VCOMError err = resolver->ResolveN( outputFileID );

	outputFileID->GetFileFullPath( fileFullPath );

	bool exist = false;
	outputFileID->ExistsOnDisk( exist );
	DSTOPIF(!exist, (kVStanev, "Web-palette required web-file cannot be found for the patched up Debug build. Make sure the list is correct if you use the non-default VWExtensionWebPalette, or consult with Vlado!"));
#endif

	// For development purposes, you can provide an override URL in DevSettings_<VWR Identifier>.vwr placed in the user's folder
	TXString urlOverride = TXResource( TXString("DevSettings_") + TXString(DefaultPluginVWRIdentifier()) + "/Strings/settings.vwstrings", htmlFile, eAllowEmptyResult );

	TXString url;
	if ( urlOverride.IsEmpty() )
	{
		url = TXString("file://") + fileFullPath;
	}
	else
	{
		// URL provided by override for development purposes
		if ( urlOverride.Left(7) != "http://" && urlOverride.Left(7) != "file://" && urlOverride.Left(8) != "https://" )
			url = TXString("file://") + urlOverride;
		else
			url = urlOverride;
	}

	return url;
}

// This is practically the same implementation as "VWFC::PluginSupport::GetStandardURL"
// But we must do it because we use RELEASE SDK which doesn't give us URL to the local index.html in the resources in DEBUG
TXString CExtWebPaletteExample::GetInitialURL()
{
	// Change those if your front-end is in a different folder and file
	const TXString	htmlFolderName	= "html";
	const TXString	htmlFile		= "index.html";
	return Custom_GetStandardURL( htmlFolderName, htmlFile );
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
