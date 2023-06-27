//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//	Main entry point for Vectorworks module code.
//

#include "StdAfx.h"

#include "TesterModule/ExtTool.h"
#include "TesterModule/ExtMenu.h"

const char * DefaultPluginVWRIdentifier() { return "TempToolSample"; }

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

	REGISTER_Extension<TesterModule::CExtTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<TesterModule::CExtMenu>( GROUPID_ExtensionMenu, action, moduleInfo, iid, inOutInterface, cbp, reply );

	return reply;
}
