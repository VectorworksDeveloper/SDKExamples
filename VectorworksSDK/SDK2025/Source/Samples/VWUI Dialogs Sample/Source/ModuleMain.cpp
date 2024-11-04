//
//	ModuleMain.cpp
//
//	Main entry point for Vectorworks module code.
//

#include "StdAfx.h"
#include "UI/ExtMenuClassName.h"
#include "UI/ExtMenuDirectEditLb.h"
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

	Sint32 reply	= 0;

	using namespace VWFC::PluginSupport;

	REGISTER_Extension<UI::CExtMenuClassName>( GROUPID_ExtensionMenu, action, moduleInfo, iid, inOutInterface, cbp, reply );

	// edit list browser
	REGISTER_Extension<UI::CExtMenuDirectEditLb>( GROUPID_ExtensionMenu, action, moduleInfo, iid, inOutInterface, cbp, reply );


	return reply;
}
