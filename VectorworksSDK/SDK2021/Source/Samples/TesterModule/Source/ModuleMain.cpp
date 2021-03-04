//
//	TesterModuleModule.cpp
//
//	Main entry point for Vectorworks module code.
//


#include "StdAfx.h"

#include "TesterModule/ExtTool.h"
#include "TesterModule/ExtMenu.h"
#include "TesterModule/ExtObj.h"
#include "TesterModule/ExtVSFunc.h"
#include "TesterModule/ExtMenuDyn.h"
#include "TesterModule/ExtMenuWebBrowser.h"
#include "Advanced/ExtObjAdvComplex.h"
#include "ResourcePopup/ExtObjResourcePopup.h"
#include "ResourcePopup/ExtToolResourcePopupSimple.h"
#include "ResourcePopup/ExtToolResourcePopupComplex.h"

const char * DefaultPluginVWRIdentifier() { return "TesterModule"; }

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
	REGISTER_Extension<TesterModule::CExtObj>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<TesterModule::CExtVSFuncs>( GROUPID_ExtensionVSFunctions, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<TesterModule::CExtMenuDyn>( GROUPID_ExtensionMenu, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<TesterModule::CExtMenuWebBrowser>( GROUPID_ExtensionMenu, action, moduleInfo, iid, inOutInterface, cbp, reply );

	// advanced samples
	REGISTER_Extension<Advanced::CExtObjAdvComplexDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<Advanced::CExtObjAdvComplex>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	// resource popup samples
	REGISTER_Extension<ResourcePopup::CExtObjResourcePopup>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<ResourcePopup::CExtToolResourcePopupSimple>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<ResourcePopup::CExtToolResourcePopupComplex>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );

	return reply;
}
