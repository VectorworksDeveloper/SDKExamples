//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Created by Vlado Sep 2013

//	This is the main include for the entire Vectorworks SDK
//
//	The following macros control the behavior of the SDK
//
//		_MINICAD_			define when you are not compiling a Vectorworks plug-in
//		DEV_BLD				define when compiling debug, don't define when release
//		RELEASE_BLD			define when compiling release, don't define when debug
//
//		_WINDOWS			define when compiling on windows

#pragma once

#ifndef _MINICAD_
	#define	_MINICAD_EXTERNAL_	1

	#if defined DEV_BLD && !defined RELEASE_BLD
		#ifndef DEBUG
		# define DEBUG					1
		#endif
		#define _DEBUG					1
		#undef RELEASE_BLD
		#undef NDEBUG
	#elif defined RELEASE_BLD && !DEV_BLD
		#undef DEV_BLD
		#undef DEBUG
		#undef _DEBUG
		#define NDEBUG					1
	#else
		#error You must define DEV_BLD or RELEASE_BLD
	#endif

	#define __EXTERNDEFINES__		1
	#define _GSESDK_				1
#endif

#if defined DEV_BLD && _WINDOWS
	#define SDK_NEW		new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
	#define SDK_NEW		new
#endif

#include "Kernel/CoreDefines.h"

#ifndef _MINICAD_
	#ifndef _WINDOWS
		// The GSDebug.h include here is just to satisfy the Carbon.h include
		// It will try to include assert.h and will get confused by our own
		// which cannot compile with GSDebug.h providing some types
		// Vlado Sep 2013
		#include "Kernel/GSDebug.h"
    #ifndef EXCLUDE_CARBON_FRAMEWORK
        #include <Carbon/Carbon.h>
    #endif
	#endif
#endif

#include <limits>
#include <functional>

// -------------------------------------------------------------------------------
// Include the basic SDK
#include "Kernel/GSGlobals.h"
#include "Kernel/GSByteSwap.h"
////#include "MCMemory.h"
#include "Kernel/MCMatrix.h"
#include "Kernel/MCVector.h"
#include "Kernel/TArray.h"
#include "Kernel/OSTDefs.h"


#include "Kernel/VariableState.h"
#include "Kernel/SysName.h"
#include "Kernel/FPNumerics.h"
#include "Kernel/ProjectionType.h"
#include "Kernel/RenderOptionsValues.h"
#include "Kernel/CallbackIDs.h"
#include "Kernel/ExtendedProperties.h"
#include "Kernel/EditShader.Common.h"
#include "Kernel/GSVariant.h"
#include "Kernel/WorldInchesToCoords.h"
#include "Kernel/CustomObjects.h"
#include "Kernel/GSLogging.h"

#ifdef _MINICAD_
	#include "Kernel/AlturaDefs.h"
	#include "Kernel/ExternMisc.h"
#endif

#include "MockUp/MockInvironment.h"
#include "MockUp/MockSDK.h"

// this function will provide the SDK/Vectorworks version number of a compiled plugin
// this way Vectorworks would know when the plugin was compiled and not loaded as it might crash if the version is not appropriate
#define		SDK_VERSION		/*kVectorWorks26FileVersion BUMP THIS NUMBER TOO->*/ 2600

// This will allow Vectorworks to request the version for which this plugin was compiled
// this function is used in GS_InitializeVCOM and it will report 'unresolved external symbol' when linked if not defined by a plugin
// to fix this error, the plugin should implement this function like this:
//	extern "C" Sint32 GS_EXTERNAL_ENTRY plugin_module_ver() { return SDK_VERSION; }
#if ! _MINICAD_
	extern "C" Sint32 GS_EXTERNAL_ENTRY plugin_module_ver();
#else
	#include "FileVersionInfo.h"
	#if SDK_VERSION != (kCurrentFileRelease*100)
		#error You should update SDK_VERSION so it matches the current Vectorworks release version
	#endif
#endif

// -------------------------------------------------------------------------------
// json library
// https://github.com/nlohmann/json
#include "json/nlohmann/json.hpp"

// -------------------------------------------------------------------------------
// Include the VectorWorks Fondation Classes Library
#include "VWFC/VWFCLibrary.h"
#include "VWFC/PluginSupport/VWExtensions.h"

// -------------------------------------------------------------------------------
// VCOM standard interfaces
#include "Interfaces/VWInterfaces.h"
