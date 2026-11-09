//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//

#include "StdHeaders.h"

// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE



#ifndef _MINICAD_

extern "C" void GS_EXTERNAL_ENTRY plugin_module_deinit()
{
	gIFC.Release();
	gDataTagSupport.Release();
	gFormatHandlerSupport.Release();
}

#endif
