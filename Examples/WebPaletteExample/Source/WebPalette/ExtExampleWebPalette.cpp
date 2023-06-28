#include "StdAfx.h"

#include "ExtExampleWebPalette.h"


using namespace WebPalette;

const CBSignedShort kKludgeRunOnMainThreadSync = 6015;

// --------------------------------------------------------------------------------------------------------
CPaletteJSProvider::CPaletteJSProvider()
	: fWebFrame( nullptr )
{
	this->UpdateLocalizedJSON();
}

CPaletteJSProvider::~CPaletteJSProvider()
{
}

void CPaletteJSProvider::UpdateLocalizedJSON()
{
	TXString json;

	TXResource	resource( TXString(DefaultPluginVWRIdentifier()) + "/strings/html.vwstrings" );
	const void* buffer = resource.Buffer();
	size_t		bufferSize = resource.Size();
	if ( buffer && bufferSize > 0)
	{
		const static std::vector<char>	sBOM_UTF16 = { char(0xFF), char(0xFE) };
		const static std::vector<char>	sBOM_UTF8  = { char(0xEF), char(0xBB), char(0xBF) };

		if ( bufferSize >= sBOM_UTF16.size() &&
			memcmp( buffer, &sBOM_UTF16[0], sBOM_UTF16.size() )  == 0 )
			json = TXString( (const UCChar*) (((const char*)buffer) + sBOM_UTF16.size()), (bufferSize - sBOM_UTF16.size())/2 );
		else if ( bufferSize >= sBOM_UTF8.size() &&
					memcmp( buffer, &sBOM_UTF8[0], sBOM_UTF8.size() ) == 0 )
			json = TXString( ((const char*)buffer) + sBOM_UTF8.size(), bufferSize - sBOM_UTF8.size() );
		else
			json = resource.operator const TXString & ();
	}

	// clean up any comments
	size_t pos = 0;
	while ( true )
	{
		ptrdiff_t at = json.Find( "//", pos );
		if ( at < 0 )
			break;

		ptrdiff_t atEnd = std::max( json.Find( "\n", at + 1 ), json.Find( "\r", at + 1 ) );
		if ( atEnd > at )
			json.Delete( at, atEnd - at + 1 );

		pos = at + 1;
	}

	// trun into JSON key:value list defintiion
	json.Replace( "=", ":" );
	json.Replace( ";", "," );

	// add a last element as JSON cannot have comma at the end
	json += "\"\":\"\"";

	fLocalizedJSON = "{" + json + "}";
}

void CPaletteJSProvider::OnInit(IInitContext* context)
{
	fWebFrame = context->GetWebFrame();

	context->AddExecute(R"(
			exampleIntegrator = {};
			exampleIntegrator.getLocalStrings = () => new Promise( function(resolve, reject)	{ exampleIntegrator.getLocalStringsInner(resolve, reject); } );
			exampleIntegrator.getAllPlantStyles = () => new Promise(function(resolve, reject)   { exampleIntegrator.getAllPlantStylesInner(resolve, reject); } );
			exampleIntegrator.getAllPlantData = () => new Promise(function(resolve, reject)     { exampleIntegrator.getAllPlantDataInner(resolve, reject); } );
		)");
	
	context->AddFunction( "exampleIntegrator.getLocalStringsInner" );
	context->AddFunction( "exampleIntegrator.getAllPlantStylesInner" );
	context->AddFunction( "exampleIntegrator.getAllPlantDataInner" );
	context->AddFunction( "exampleIntegrator.updatePlantAssociations" );
}

void CPaletteJSProvider::OnFunction(const TXString& name, const std::vector<VWVariant>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
{
	TXString	shortName;
	ptrdiff_t at = name.Find( '.' );
	if ( at >= 0 )
		shortName = name.Mid( at + 1 );

	if ( shortName == "getLocalStringsInner" )
	{
		VWVariant result = this->OnGetLocalStringsInner();
		context->Call( args[0], result );
	}
	else if ( shortName == "getAllPlantStylesInner" )
	{
		VWVariant result = this->OnGetAllPlantStyles();
		context->Call( args[0], result );
	}
	else if ( shortName == "getAllPlantDataInner" )
	{
		VWVariant result = this->OnGetAllPlantData();
		context->Call( args[0], result );
	}
	else if ( shortName == "updatePlantAssociations" )
		this->OnUpdatePlantAssociations( args );
}

VWVariant CPaletteJSProvider::OnGetLocalStringsInner()
{
#if defined(DEV_BLD) || defined(_DEBUG_FAST)
	std::function<void()> runOnMainThreadCallback = [&]()
	{
		this->UpdateLocalizedJSON();
	};

	const CBSignedShort kKludgeRunOnMainThreadSync = 6015;
	gSDK->Kludge( kKludgeRunOnMainThreadSync, & runOnMainThreadCallback, nullptr );
#endif

	return VWVariant(fLocalizedJSON);
}

VWVariant CPaletteJSProvider::OnGetAllPlantStyles()
{
	TXString jsonTxt;
	std::function<void()> runOnMainThreadCallback = [&jsonTxt]()
	{
		// ...
	};

	const CBSignedShort kKludgeRunOnMainThreadSync = 6015;
	gSDK->Kludge( kKludgeRunOnMainThreadSync, & runOnMainThreadCallback, nullptr );

	return VWVariant(jsonTxt);
}

VWVariant CPaletteJSProvider::OnGetAllPlantData()
{
	TXString jsonTxt;
	std::function<void()> runOnMainThreadCallback = [&jsonTxt]()
	{
		nlohmann::json data;
		data["one"] = "dfds";
		data["two"] = 34;

		jsonTxt = data.dump();
	};

	gSDK->Kludge( kKludgeRunOnMainThreadSync, & runOnMainThreadCallback, nullptr );

	return VWVariant(jsonTxt);
}

void CPaletteJSProvider::OnUpdatePlantAssociations(const std::vector<VWVariant>& args)
{
	std::function<void()> runOnMainThreadCallback = []()
	{
		// ...
	};

	gSDK->Kludge( kKludgeRunOnMainThreadSync, & runOnMainThreadCallback, nullptr );
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
CExtWebPaletteExample::CExtWebPaletteExample(CallBackPtr)
{
}

CExtWebPaletteExample::~CExtWebPaletteExample()
{
}

IEventSink* CExtWebPaletteExample::QueryEventSink(const TSinkIID& iid)
{
	IEventSink* result = nullptr;
	if ( iid == IID_WebJavaScriptProvider )
	{
		fJSProvider.AddRef();
		result = &fJSProvider;
	}

	return result;
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
/*
static void ExtractResourceAsFile(const TXString& resourceRoot, const TXString& fileName)
{
	VectorWorks::Filing::IFileIdentifierPtr	outputFileID;
	outputFileID->Set( kExternalDataFolder, true, "
}
*/
TXString CExtWebPaletteExample::GetInitialURL() 
{
	// OR - OR = two possibilities here!

	// use this block when internal (in the vwr file) site will be used
	{
#if !defined(DEV_BLD) && !defined(_DEBUG_FAST)
		// make a copy of the site off of the bundled resources for release
		TXString resRoot = TXString(DefaultPluginVWRIdentifier()) + "/html/";
		VectorWorks::Filing::IFolderIdentifierPtr	rootFolder( VectorWorks::Filing::IID_FolderIdentifier );
		rootFolder->Set( kExternalDataFolder, true, resRoot );
		rootFolder->CreateOnDisk();

		VectorWorks::Filing::IFileIdentifierPtr	outputFileID( VectorWorks::Filing::IID_FileIdentifier );
		VectorWorks::Filing::IRawOSFilePtr outputRawFile( VectorWorks::Filing::IID_RawOSFile );

		TXResource	resJS( resRoot + "main.js" );
		outputFileID->Set( rootFolder, "main.js" );
		outputRawFile->Open( outputFileID, false, true, false, true );
		outputRawFile->Write( 0, resJS.Size(), resJS.Buffer() );
		outputRawFile->Close();

		TXResource	resHTML( resRoot + "index.html" );
		outputFileID->Set( rootFolder, "index.html" );
		outputRawFile->Open( outputFileID, false, true, false, true );
		outputRawFile->Write( 0, resHTML.Size(), resHTML.Buffer() );
		outputRawFile->Close();
#else
		using namespace VectorWorks::Filing;
	
		// the debug versions use schortcut for the resource
		// we want to use that so we can use the site we are developing to make direct changes, instead of a copy
		IFileIdentifierPtr	outputFileID( IID_FileIdentifier );
		#ifdef _WINDOWS
			outputFileID->Set( kApplicationFolder, false, "Plug-Ins/" + TXString(DefaultPluginVWRIdentifier())+".vwr/html/index.html" );
		#else
			outputFileID->Set( kApplicationFolder, false, "Plug-Ins/WebPaletteExample.vwlibrary/Contents/Resources/" + TXString(DefaultPluginVWRIdentifier())+".vwr/html/index.html" );
		#endif
	

		IPathResolverPtr resolver( IID_PathResolver );
		resolver->Resolve( outputFileID );

		TXString path;
		outputFileID->GetFileFullPath(path);

		bool exist = false;
		outputFileID->ExistsOnDisk( exist );
		DSTOPIF(!exist, (kVStanev, "Web index page cannot be found for the patched up Debug build. Consult with Vlado!"));
#endif

        TXString url;
        outputFileID->GetFileFullPath( url );
        return TXString("file://") + url;
	}

	// use this block when external site will be used with the palette
	{
		TXString url = TXResource( "WebPaletteExample/Strings/Palette.vwstrings", "url", eAllowEmptyResult );
		return url.IsEmpty() ? TXResStr("ExtWebPaletteExample", "paletteURL") : url;
		//return "E:\\_Test Files\\test1.html";
	}
}

// --------------------------------------------------------------------------------------------------------
// {291F9D08-E795-45E9-A2B0-FDE34A8A0DDE}
IMPLEMENT_VWPaletteExtension(
	/*Extension class*/	CExtWebPaletteExample,
	/*Universal name*/	"WebPaletteExample",
	/*Version*/			1,
	/*UUID*/			0x291f9d08, 0xe795, 0x45e9, 0xa2, 0xb0, 0xfd, 0xe3, 0x4a, 0x8a, 0xd, 0xde );

// --------------------------------------------------------------------------------------------------------


