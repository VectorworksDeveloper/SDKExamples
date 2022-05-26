//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

// this is included very early so it has a chance to pre-define almost anthing
// AutoBuildControl.h does nothing except when special configurations are
// called for by the auto build machine. When this is necessary, AutoBuildControl.h
// is completely overwritten by a generated file which sets flags as appropriate.

#include "AutoBuildControl.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Platform Variables




#if _WINDOWS
	#define GS_WIN				1
	#define GS_MAC				0
	#if _WIN64					// WIN32 is defined on 64 bit systems too, for compatibility.  So we check _WIN64 first
		#define GS_PLATFORM32		0
		#define GS_PLATFORM64		1
		#define __C4D_64BIT
	#elif _WIN32
		#define GS_PLATFORM32		1
		#define GS_PLATFORM64		0
	#else
		#error  No recognized windows platform variable was defined!
	#endif

	#define GS_LITTLE_ENDIAN	1
	#define GS_BIG_ENDIAN		0

#elif __APPLE__
	#define GS_WIN				0
	#define GS_MAC				1

    // This symbol can be used to temporarily disable things
    // for Apple Silicon branch / Universal Binary compilation -
    // should not be used long-term.
    #define GS_MAC_APPLESILICON_TRANSITION 1
    #if GS_MAC_APPLESILICON_TRANSITION
        #define GS_MAC_APPLESILICON_TRANSITION_Remove_this_NonEssentialParasolids_code_SAJ

        #include "TargetConditionals.h"
        #if !TARGET_CPU_X86_64
            // This code can be called on intel. Waiting to add arm libs.
            #define GS_MAC_APPLESILICON_TRANSITION_Remove_this_NonEssential_LicenseServer_code_SAJ
            #define GS_MAC_APPLESILICON_TRANSITION_Remove_this_NonEssential_ProjectSahringServer_code_SAJ
        #endif
    #endif
	#if __LP64__
		#define GS_PLATFORM32		0
		#define GS_PLATFORM64		1
		#define __C4D_64BIT
	#else
		// 32 bit platform
		#define GS_PLATFORM32		1
		#define GS_PLATFORM64		0
	#endif

	#if __LITTLE_ENDIAN__
		#define GS_LITTLE_ENDIAN 1
		#define GS_BIG_ENDIAN	 0
	#else
		#define GS_LITTLE_ENDIAN 0
		#define GS_BIG_ENDIAN	 1
	#endif

#else
	#error  No recognized platform variable was defined!
#endif

#if GS_LITTLE_ENDIAN
	#define GS_LITTLE_ENDIAN_ONLY(x) x // Replaces WIN_ONLY when used in the context of byte swapping.
#else
	#define GS_LITTLE_ENDIAN_ONLY(x)
#endif

/////////////////////////////////////////////////////////////////////////////////////////
// Final Release Flag
//
//	Once we are solidly in the beta period & have locked down our file format
//	and other major changes, we need to set NEARING_FINAL_RELEASE to 1 to enable
//	some more strict checks than we otherwise wouldn't perform.

#define NEARING_FINAL_RELEASE 1

/////////////////////////////////////////////////////////////////////////////////////////
// Final Release Build Flag
//
//	This flag enables the Beta Alerts. Beta Alerts are turned off when building Release  
//  builds (i.e. Release Candidate or Final Release builds). It is off when building 
//  Development and Beta builds.
//
#define FINAL_RELEASE_BUILD !GS_BETA_PROGRAM_SUPPORT

/////////////////////////////////////////////////////////////////////////////////////////
// Unused Reference Code Flag
//
//	Use this flag to wrap dead code with an #if and #endif to indicate that
// it should stay in the file, but it will never be compiled into the application.
//
// For example:
/*
	#if NNA_UNUSED_REFERENCE_CODE
	// This code was added by request by our Irish distributors, but the project was canceled.
	// Please leave this code here for reference.
	// See Lyndsey Ferguson for more details.

	if (monkeySeeMonkeyDo) {
		BeginEepEep();
	}

	#endif // NNA_UNUSED_REFERENCE_CODE
*/
#define NNA_UNUSED_REFERENCE_CODE 0

/////////////////////////////////////////////////////////////////////////////////////////
// Debug flags: PROFILE, NETBUG, BUG, and TEST
//  These are automatically defined (or undefined) based on the build type.
//
//  PROFILE	: Define to include profiling code (currently available only on Mac).
//			   Undefined for all except profile versions.
//  NETBUG	: Define to send ASSERT failures to the network logger.
//			   Undefined for external release and profile versions.
//  BUG		: Define to include code that breaks to the platform's debugger or
//			   writes to the application's debug window.
//			   Undefined for external release, profile, and internal beta versions.
//  TEST	: Define to enable Asserts and include testing code.
//			   Defined when either BUG or NETBUG are, undefined otherwise.

#if defined(_DEBUG_FAST)	// RELEASE with disabled optimization should allow ASSERTN
							// keep in front of RELEASE_BLD as it is based on release build
	#undef  PROFILE
	#undef  NETBUG
	#define BUG		1
#elif defined(RELEASE_BLD) || EXTERNAL_BUILD
	#undef  PROFILE
	#undef  NETBUG
	#undef  BUG
#elif defined(PROFILE_BLD)
	#define PROFILE  1				// Profiling code included
	#undef  NETBUG
	#undef  BUG
#elif defined(BETA_BLD)
	#undef  PROFILE
	#define NETBUG  GS_WIN				// Assert failures sent to network logger
	#undef  BUG
#elif defined(DEV_BLD)
	#undef  PROFILE
	#define NETBUG  GS_WIN				// Assert failures sent to network logger
	#define BUG  1					// Debugging code included
#elif defined(SPCDEV_BLD)
	#undef  PROFILE
	#define NETBUG  GS_WIN				// Assert failures sent to network logger
	#define BUG  1					// Debugging code included
	#define GS_SPECIAL_VERSION 1	// Special features included (e.g. VW 9 stuff in 8.5)
#else
	#error  No recognized version variable was defined!
#endif

#if (defined(NETBUG) || defined(BUG))
	#define TEST  1					// Asserts enabled, testing code included
#else
	#undef  TEST
#endif


///////////////////////////////////////////////////////////////////////////////
// This section contains function type specifiers for functions exported from GSESDK.
//
//	GS_API: Use this like a pascal modifier for functions in VectorWorks which are part of the
//		externally available interface. E.g. "void GS_API WackyMiniCadFunction();".
//
//	GS_API_PTR: Apply this to pointers to API functions.  E.g.  "typedef void
//		GS_API_PTR(WackyMiniCadFunctionPtr)();".
//
//	GS_CALLBACK: This is the type used for all glue code between the externals and
//		callbacks into MiniCAD
//
//	GS_CALLBACK_PTR: Pointer to GS_CALLBACK

#define GS_API
#define GS_API_PTR(ptr_t)					(*ptr_t)
#define GS_CALLBACK
#define GS_CALLBACK_PTR(name)				(*name)
#if GS_WIN
	#ifndef _MINICAD_
		#define GS_EXTERNAL_ENTRY			__declspec(dllexport)
	#endif
#elif GS_MAC
	#define GS_EXTERNAL_ENTRY				__attribute__((visibility("default")))
#endif

///////////////////////////////////////////////////////////////////////////////

#if BUG
	#define BUG_ONLY(x)				x
#else
	#define BUG_ONLY(x)
#endif

///////////////////////////////////////////////////////////////////////////////

#if GS_WIN
#define force_inline __forceinline

#else // mac

#define force_inline inline
#endif


///////////////////////////////////////////////////////////////////////////////
// Macros for unused parameters.  Use these instead of just commenting
// out the parameter name.

#ifdef __AFX_H__
	// MFC defines its own UNUSED macro that does not appear to have the same
	// meaning and use as our own. [DMB 7/27/99]
#else
	#define UNUSED(x)
#endif

#if GS_CLASSIC_SHELL
	#define CLASSIC_ONLY(x) x
#else
	#define CLASSIC_ONLY(x)
#endif

#if _WINDOWS
	#define MAC_ONLY(x)
	#define WIN_ONLY(x)    x
	#define MAC_WIN(m, w)  w
	#ifndef GS_LITTLE_ENDIAN
		#define GS_LITTLE_ENDIAN 1
	#endif
	#ifndef GS_BIG_ENDIAN
		#define GS_BIG_ENDIAN 0
	#endif
#else
	#define MAC_ONLY(x)  x
	#define WIN_ONLY(x)
	#define MAC_WIN(m, w)  m
#endif

#if GS_INTERFACE_FACTORING

	/////////////////////////////////////////////////////////////////////////////////////
	// Define to 1 if building *.dll, 0 or undefine if building *.lib
	#if _WINDOWS
		#define GS_SHELL_DLL		0
		#define GS_COMP_DLL			0
		#define GS_CORE_DLL			0
		#define GS_PROTECTION_DLL	0
	#endif

	// If shell is a DLL, than either (or both) Core, Components or Protection better also be a DLL.
	#if GS_SHELL_DLL && !GS_CORE_DLL && !GS_COMP_DLL && !GS_PROTECTION_DLL
		#error If Application is a DLL, either Core, Components or Protection should also be a DLL.
	#endif


	/////////////////////////////////////////////////////////////////////////////////////
	// UI Shell (Application)

	#if GS_SHELL_DLL
		// Application is a DLL.
		#if GS_SHELL_BUILD
			// Building shell application.
			#define GS_SHELL_API			__declspec(dllexport)
		#else
			// Building a client of the shell application.
			#define GS_SHELL_API			__declspec(dllimport)
		#endif
	#else
		// Application shell is a LIB, no need to export or import anything.
		#define GS_SHELL_API
	#endif


	/////////////////////////////////////////////////////////////////////////////////////
	// Components

	#if GS_COMP_DLL
		// Components is a DLL.
		#if GS_COMP_BUILD
			// Building Components.
			#define GS_COMP_API			__declspec(dllexport)
		#else
			// Building a client of Components.
			#define GS_COMP_API			__declspec(dllimport)
		#endif
	#else
		// Components is a LIB, no need to export or import anything.
		#define GS_COMP_API
	#endif

	
	/////////////////////////////////////////////////////////////////////////////////////
	// Protection

	#if GS_PROTECTION_DLL
		// Protection is a DLL.
		#if GS_PROTECTION_BUILD
			// Building Components.
			#define GS_PROTECTION_API			__declspec(dllexport)
		#else
			// Building a client of Components.
			#define GS_PROTECTION_API			__declspec(dllimport)
		#endif
	#else
		// Components is a LIB, no need to export or import anything.
		#define GS_PROTECTION_API
	#endif
	/////////////////////////////////////////////////////////////////////////////////////
	// Core

	#if GS_CORE_DLL
		// Core is a DLL.
		#if GS_CORE_BUILD
			// Building Core.
			#define GS_CORE_API			__declspec(dllexport)
		#else
			// Building a client of Core.
			#define GS_CORE_API			__declspec(dllimport)
		#endif
	#else
		// Core is a LIB, no need to export or import anything.
		#define GS_CORE_API
	#endif


#else // GS_INTERFACE_FACTORING

	// UI Shell (Application)
	#define GS_SHELL_API

	// Components
	#define GS_COMP_API

	// Core
	#define GS_CORE_API

#endif // GS_INTERFACE_FACTORING


/////////////////////////////////////////////////////////////////////////////////////////
#if _WINDOWS
	#define MACAPI GS_COMP_API _stdcall
#else
	#define MACAPI pascal
#endif

#if _WINDOWS
    #define GS_HIDDEN_VISIBILITY
#else
    #define GS_HIDDEN_VISIBILITY __attribute__((visibility("hidden")))
#endif

/////////////////////////////////////////////////////////////////////////////////////////
// This is a do-nothing reading aid which can be used before brackets to
// make it clear that the brackets are meant to be there to indicate scope
// of enclosed vars; ie   ... scope { TFoo foo(); foo.DoSomething(); } ...
#define NNA_SCOPE

// Use this macro in the private section of a class to disallow copying or assignment
//	of that class.

#define DISALLOW_DUPLICATES(T) \
	T (const T &)			= delete;	/* no copying allowed. */ \
	T& operator=(const T &)	= delete;	/* no assignment allowed, either. */

#if GS_WIN
/////////////////////////////////////////////////////////////////////////////////////////
// Start Windows-only section.

	/////////////////////////////////////////////////////////////////////////////////////
	// Set structure packing to 2 bytes.

	//#pragma pack(2)


	/////////////////////////////////////////////////////////////////////////////////////
	// Turn off annoying compiler warnings. Think Sint32 and hard before putting a warning
	// into this section, we don't want to cover up any legitimate errors. More of these
	// are turned off in CoreDefines.h.

	#pragma warning (disable : 4200)	// nonstandard extension used : zero-sized array in struct/union
	#pragma warning (disable : 4250)	// 'x' : inherits 'y::z' via dominance
	#pragma warning (disable : 4291)	// no matching operator delete found; memory will not be freed if in itialization throws an exception
	#pragma warning (disable : 4786)	// identifier was truncated to '255' characters in the browser information
	#pragma warning (disable : 4800)	// forcing value to bool 'true' or 'false'
	#pragma warning (disable : 4503)	// decorated name length exceeded, name was truncated

	/////////////////////////////////////////////////////////////////////////////////////
	// Turn on warnings normally associated with level 4. We cannot as of yet have
	// level 4 warnings for Visual Studio because too much of our code fails.
	//
#if BUG
	//#pragma warning(3: 4100)			// unreferenced formal parameter
	#pragma warning(3: 4189)			// local variable is initialized but not referenced
	#pragma warning(3: 4101)			// unreferenced local variable
	#ifndef _ALLOW_RTCc_IN_STL
		#define _ALLOW_RTCc_IN_STL // Visual Studio 2017 disallows Run time code checks with the STL because of "errors" on well defined behaviors. It must be disabled.
	#endif
#endif

/////////////////////////////////////////////////////////////////////////////////////
	// This turns on the flag that allows VW to build under the .NET compiler
	//	(version 13 or 1300).
	#if _MSC_VER >= 1300
		#define GS_DOTNET_COMPILER 1
	#else
		#define GS_DOTNET_COMPILER 0
	#endif

// End Windows-only section.
/////////////////////////////////////////////////////////////////////////////////////////

#else
/////////////////////////////////////////////////////////////////////////////////////////
// Start Mac-only section.

	/////////////////////////////////////////////////////////////////////////////////////
	// Macintosh Universal Interfaces Variables
	#ifndef TARGET_API_MAC_CARBON
		#define TARGET_API_MAC_CARBON  1
	#endif

	/////////////////////////////////////////////////////////////////////////////////////
	// Non-GS Library Variables
	#ifndef __dest_os
		#define __dest_os  __mac_os			// Metrowerks Standard Library
	#endif
#ifndef __GNUC__  // XXX: Need to set _MINICAD_ in third-party libs built for the app,
       //  and then test on it, so can avoid #include for externals.  MFH 04/01
	#include <UseDLLPrefix.h>			// Using shared-library version of MSL


#endif
#if (Paul || Jeff) // Turn network checking off for Jeff & Paul so they don't have to worry about this on MacOS X
#define GS_NEWMACNETWORKCHECK 0
#else
#define GS_NEWMACNETWORKCHECK 1
#endif

// End Mac-only section.
/////////////////////////////////////////////////////////////////////////////////////////
#endif  // GS_WIN
