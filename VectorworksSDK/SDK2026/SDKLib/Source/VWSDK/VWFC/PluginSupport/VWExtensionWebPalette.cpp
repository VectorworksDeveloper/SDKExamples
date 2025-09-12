//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#if _MINICAD_
# include "HelpText.X.h"
#endif


using namespace VWFC::PluginSupport;

// --------------------------------------------------------------------------------------------------------
VWExtensionPaletteJSProvider::VWExtensionPaletteJSProvider(IVWUnknown* parent)
	: fParent( parent )
{
}

VWExtensionPaletteJSProvider::~VWExtensionPaletteJSProvider()
{
}

void VWExtensionPaletteJSProvider::OnInit(IInitContext* context)
{
	fWebFrame = context->GetWebFrame();
}

void VWExtensionPaletteJSProvider::OnFunction(const TXString& name, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context)
{
	TXString	shortName;
	ptrdiff_t at = name.Find( '.' );
	if ( at >= 0 )
		shortName = name.Mid( at + 1 );

	TXString objName = name.Left( at );
	this->OnFunctionCall( objName, shortName, args, context );
}

// --------------------------------------------------------------------------------------------------------
VWExtensionWebPalette::VWExtensionWebPalette()
{
}

VWExtensionWebPalette::VWExtensionWebPalette(const char* htmlFolderName)
	: fHTMLFolderName( htmlFolderName )
{
}

VWExtensionWebPalette::VWExtensionWebPalette(const char* htmlFolderName, const char* htmlFile)
	: fHTMLFolderName( htmlFolderName )
	, fHTMLFile( htmlFile )
{
}

VWExtensionWebPalette::~VWExtensionWebPalette()
{
}

void VWExtensionWebPalette::OnRefCountZero()
{
	for(TSinksMap::iterator it=fmapSinks.begin(); it!=fmapSinks.end(); it++)
	{
		IEventSink*	theSink	= it->second;
		if ( theSink )
		{
			delete theSink;
		}
	}

	fmapSinks.clear();
}

bool VWExtensionWebPalette::GetProtectionSinkIID(TSinkIID& outIID)
{
	return false;
}

IProviderProtection* VWExtensionWebPalette::CreateProtectionSink(IVWUnknown* parent)
{
	return NULL;
}

IEventSink* VWExtensionWebPalette::QueryEventSink(const TSinkIID& iid)
{
	if (fProtectionObtained == false)
	{
		fHasProtection = this->GetProtectionSinkIID(fProtectionSinkIID);
		fProtectionObtained = true;
	}

	IEventSink*			theSink	= nullptr;
	TSinksMap::iterator	it		= fmapSinks.find( iid );
	if ( it != fmapSinks.end() )
	{
		theSink	= it->second;
	}
	else if ( fHasProtection && fProtectionSinkIID == iid ) {
		theSink = CreateProtectionSink( this );
		if (theSink)
			fmapSinks.insert( TSinksMap::value_type( iid, theSink ) );
		else
			fHasProtection = false;
	}
	else {
		fDefinedSink		= nullptr;
		fDefinedSinkIID		= iid;
		this->DefineSinks();
		if ( fDefinedSink )
		{
			fmapSinks.insert( TSinksMap::value_type( iid, fDefinedSink ) );
			theSink			= fDefinedSink;
			fDefinedSink	= nullptr;
		}
	}

	if ( theSink )
		theSink->AddRef();

	return theSink;
}

TXString VWExtensionWebPalette::GetInitialURL()
{
	if ( fHTMLFolderName.IsEmpty() && fHTMLFile.IsEmpty() )
		return VWFC::PluginSupport::GetStandardURL();
	else if ( fHTMLFile.IsEmpty() )
		return VWFC::PluginSupport::GetStandardURL( fHTMLFolderName );
	else
		return VWFC::PluginSupport::GetStandardURL( fHTMLFolderName, fHTMLFile );
}

TXString VWFC::PluginSupport::GetStandardURL(const TXString& htmlFolderName, const TXString& htmlFile)
{
	TXString	fileFullPath;

#if !defined(DEV_BLD) && !defined(_DEBUG_FAST)
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
	outputFileID->Set( kExternalsFolder, false, TXString(DefaultPluginVWRIdentifier())+".vwr/" + htmlFolderName + "/" + htmlFile );
#else
	outputFileID->Set( kExternalsFolder, false, TXString(DefaultPluginVWRIdentifier())+".vwlibrary/Contents/Resources/" + TXString(DefaultPluginVWRIdentifier())+".vwr/" + htmlFolderName + "/" + htmlFile );
#endif
	IPathResolverPtr resolver( IID_PathResolver );
	resolver->Resolve( outputFileID );

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

/*
TXString VWFC::PluginSupport::GetStandardURL(const TXString& inHtmlFolderName, const std::vector<TXString>& inArrWebFiles)
{
	TXString	fileFullPath;

	std::vector<TXString>	arrWebFiles = inArrWebFiles;
	if ( arrWebFiles.size() == 0 )
	{
		arrWebFiles.push_back( "index.html" );
		arrWebFiles.push_back( "main.js" );
	}

	TXString	htmlFolderName = ! inHtmlFolderName.IsEmpty() ? inHtmlFolderName : TXString("html");

#if !defined(DEV_BLD) && !defined(_DEBUG_FAST)
	// make a copy of the site off of the bundled resources for release
	TXString resRoot = TXString(DefaultPluginVWRIdentifier()) + "/" + htmlFolderName + "/";
	VectorWorks::Filing::IFolderIdentifierPtr	rootFolder( VectorWorks::Filing::IID_FolderIdentifier );
	rootFolder->Set( kExternalDataFolder, true, resRoot );
	rootFolder->CreateOnDisk();

	VectorWorks::Filing::IFileIdentifierPtr	outputFileID( VectorWorks::Filing::IID_FileIdentifier );
	VectorWorks::Filing::IRawOSFilePtr outputRawFile( VectorWorks::Filing::IID_RawOSFile );

	for(const TXString& fileName : arrWebFiles)
	{
		TXResource	res( resRoot + fileName );
		outputFileID->Set( rootFolder, fileName );
		outputRawFile->Open( outputFileID, false, true, false, true );
		outputRawFile->Write( 0, res.Size(), res.Buffer() );
		outputRawFile->Close();

		if ( fileName.Right(5) == ".html" )
			outputFileID->GetFileFullPath( fileFullPath );
	}

#else
	// the debug versions use schortcut for the resource
	// we want to use that so we can use the site we are developing to make direct changes, instead of a copy
	VectorWorks::Filing::IFileIdentifierPtr	outputFileID( VectorWorks::Filing::IID_FileIdentifier );
	for(const TXString& fileName : arrWebFiles)
	{
#ifdef _WINDOWS
		outputFileID->Set( kExternalsFolder, false, TXString(DefaultPluginVWRIdentifier())+".vwr/" + htmlFolderName + "/" + fileName );
#else
		outputFileID->Set( kExternalsFolder, false, TXString(DefaultPluginVWRIdentifier())+".vwlibrary/Contents/Resources/" + TXString(DefaultPluginVWRIdentifier())+".vwr/" + htmlFolderName + "/" + fileName );
#endif
		IPathResolverPtr resolver( IID_PathResolver );
		resolver->Resolve( outputFileID );

		TXString path;
		outputFileID->GetFileFullPath(path);

		if ( fileName.Right(5) == ".html" )
			fileFullPath = path;

		bool exist = false;
		outputFileID->ExistsOnDisk( exist );
		DSTOPIF(!exist, (kVStanev, "Web-palette required web-file cannot be found for the patched up Debug build. Make sure the list is correct if you use the non-default VWExtensionWebPalette, or consult with Vlado!"));
	}
#endif

	// For development purposes, you can provide an override URL in DevSettings_<VWR Identifier>.vwr placed in the user's folder
	TXString urlOverride = TXResource( TXString("DevSettings_") + TXString(DefaultPluginVWRIdentifier()) + "/Strings/settings.vwstrings", "url", eAllowEmptyResult );

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
}*/

