//
//	Markers_ModuleMain.cpp
//
//	Main entry point for Vectorworks module code.
//


#include "StdAfx.h"

#include "WebPalette/ExtExampleWebPalette.h"

const char * DefaultPluginVWRIdentifier() { return "WebPaletteExample"; }

//------------------------------------------------------------------
// provide SDK version for which this plugin was compiled
extern "C" Sint32 GS_EXTERNAL_ENTRY plugin_module_ver() { return SDK_VERSION; }

//------------------------------------------------------------------
// Entry point of the module plug-in for Vectorworks
// More info at: http://developer.vectorworks.net/index.php?title=SDK:Module_Plug-in
//
extern "C" Sint32 GS_EXTERNAL_ENTRY plugin_module_main(Sint32 action, void* moduleInfo, const VWIID& iid, IVWUnknown*& inOutInterface, CallBackPtr cbp)
{
	// initialize VCOM mechanizm
	::GS_InitializeVCOM( cbp );

	Sint32	reply	= 0L;

	using namespace VWFC::PluginSupport;

	REGISTER_Extension<WebPalette::CExtWebPaletteExample>( GROUPID_ExtensionWebPalettes, action, moduleInfo, iid, inOutInterface, cbp, reply );
	//REGISTER_Interface<WebPalette::CUpdateSupport>( GROUPID_ObjUpdateSupport, WebPalette::IID_UpdateSupport, action, moduleInfo, iid, inOutInterface, cbp, reply );

	return reply;
}
