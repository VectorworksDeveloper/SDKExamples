//
//	ModuleMain.cpp
//
//	Main entry point for Vectorworks module code.
//

#include "StdAfx.h"

#include "DefaultTools/ExtObjThePoint.h"
#include "DefaultTools/ExtObjTheLine.h"
#include "DefaultTools/ExtObjTheRect.h"
#include "DefaultTools/ExtObjThePoly2D.h"
#include "DefaultTools/ExtObjThePoly3D.h"

#include "CustomDefaultTools/ExtObjThePointEx.h"
#include "CustomDefaultTools/ExtObjTheLineEx.h"
#include "CustomDefaultTools/ExtObjTheRectEx.h"
#include "CustomDefaultTools/ExtObjThePoly2DEx.h"
#include "CustomDefaultTools/ExtObjThePoly3DEx.h"

const char * DefaultPluginVWRIdentifier() { return "DefaultTools"; }

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

	REGISTER_Extension<DefaultTools::CExtObjThePointDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DefaultTools::CExtObjThePoint>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	REGISTER_Extension<DefaultTools::CExtObjTheLineDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DefaultTools::CExtObjTheLine>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	REGISTER_Extension<DefaultTools::CExtObjTheRectDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DefaultTools::CExtObjTheRect>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	REGISTER_Extension<DefaultTools::CExtObjThePoly2DDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DefaultTools::CExtObjThePoly2D>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	REGISTER_Extension<DefaultTools::CExtObjThePoly3DDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<DefaultTools::CExtObjThePoly3D>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	REGISTER_Extension<CustomDefaultTools::CExtObjThePointDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<CustomDefaultTools::CExtObjThePoint>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	// Custom default line is not supported by Vectorworks 2015
	// REGISTER_Extension<CustomDefaultTools::CExtObjTheLineDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	// REGISTER_Extension<CustomDefaultTools::CExtObjTheLine>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	// Custom default rect is not supported by Vectorworks 2015
	//REGISTER_Extension<CustomDefaultTools::CExtObjTheRectDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	//REGISTER_Extension<CustomDefaultTools::CExtObjTheRect>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	REGISTER_Extension<CustomDefaultTools::CExtObjThePoly2DDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	REGISTER_Extension<CustomDefaultTools::CExtObjThePoly2D>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	// Custom default 3D poly is not supported by Vectorworks 2015
	//REGISTER_Extension<CustomDefaultTools::CExtObjThePoly3DDefTool>( GROUPID_ExtensionTool, action, moduleInfo, iid, inOutInterface, cbp, reply );
	//REGISTER_Extension<CustomDefaultTools::CExtObjThePoly3D>( GROUPID_ExtensionParametric, action, moduleInfo, iid, inOutInterface, cbp, reply );

	return reply;
}
