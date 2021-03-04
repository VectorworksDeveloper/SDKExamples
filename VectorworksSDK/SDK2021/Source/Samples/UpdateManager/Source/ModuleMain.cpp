//
//	ModuleMain.cpp
//
//	Main entry point for Vectorworks module code.
//

#include "StdAfx.h"

#include "Updater/ExtObjUpdater.h"
#include "Updater/UpdateSupport.h"
#include "Updater/DataPaneProvider_UpdateSupportSampleFormat.h"

const char * DefaultPluginVWRIdentifier() { return "UpdateManager"; }

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

	REGISTER_Extension<Updater::CExtObjUpdaterDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<Updater::CExtObjUpdater>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Interface<Updater::CUpdateSupport>( GROUPID_ObjUpdateSupport, Updater::IID_UpdateSupport, action, moduleInfo, iid, inOutInterface, cbp, reply );

	REGISTER_Interface<Updater::CDataPaneProvider_UpdateSupportSampleFormat>( Updater::IID_DataPaneProvider_UpdateSupportSampleFormat, action, moduleInfo, iid, inOutInterface, cbp, reply );

	return reply;
}
