//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//	Main entry point for Vectorworks plug-in module code.
//

#include "StdAfx.h"
#include "DemoSpace/ExtObjDemoSpace.h"
#include "DemoWindow/ExtObjDemoWindow.h"
#include "DemoSystem/ExtObjDemoSystem.h"

const char * DefaultPluginVWRIdentifier() { return "SDKSamplesEnergy"; }

//------------------------------------------------------------------
// provide SDK version for which this plugin was compiled
extern "C" Sint32 GS_EXTERNAL_ENTRY plugin_module_ver() { return SDK_VERSION; }

//------------------------------------------------------------------
// Entry point of the module plug-in for Vectorworks
// More info at: http://developer.vectorworks.net/index.php?title=SDK:Module_Plug-in
//
extern "C" Sint32 GS_EXTERNAL_ENTRY plugin_module_main(Sint32 action, void* moduleInfo, const VWIID& iid, IVWUnknown*& inOutInterface, CallBackPtr cbp)
{
	// initialize VCOM mechanism
	::GS_InitializeVCOM( cbp );

	Sint32	reply	= 0L;

	using namespace VWFC::PluginSupport;

	REGISTER_Extension<DemoSpace::CExtObjDemoSpaceDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DemoSpace::CExtObjDemoSpace>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DemoWindow::CExtObjDemoWindowDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DemoWindow::CExtObjDemoWindow>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DemoSystem::CExtObjDemoSystemDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DemoSystem::CExtObjDemoSystem>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	return reply;
}
