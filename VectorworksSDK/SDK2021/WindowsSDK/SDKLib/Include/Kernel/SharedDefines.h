//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Preprocessor stuff that is common to ALL modules of the project.
// This file has companion files for the separate modules:
//		Core:  Core/Source/CoreDefines.h
//		Shell: Include/Common/ShellDefines.h
//
// IMPORTANT:  ALL FILES IN THE PROJECT MUST INCLUDE THIS DIRECTLY OR INDIRECTLY!!!
//

#pragma once
#if _WINDOWS
#ifdef _SHAREDDEFINES_
	#error Error: SharedDefines.h should not be included more than once FOR ANY REASON.
#endif
#endif
#define _SHAREDDEFINES_


/////////////////////////////////////////////////////////////////////////////////////////
// The following flags should be set in the Windows projects' settings or in the
//  Mac projects' Hdr.Xxxx.YY.Zzz.h files to indicate the type of build desired.
//
// RELEASE_BLD, PROFILE_BLD, BETA_BLD, DEV_BLD, SPCDEV_BLD:
//                : Define exactly one of these (and undefine others) to specify
//					the type of the build.  NETBUG, BUG, and TEST are then defined
//					according to which build type is selected (see below).
//
// EXTERNAL_BUILD : Define to 1 to build a version for external distribution--this
//					will ensure that all debugging is off. Undefine or define to 0 to
//					build any internal version.  [Windows only.  Mac uses a distinct
//					XXX_BLD #define for each build version, and Windows will be migrated
//					to that method.  MFH 01/2000]
//
// MPLUS          : Define to 1 if building the VectorWorks application;
//					undefine if building VectorWorks Lt or Azimuth.
//
// AZIM           : Define to 1 if building the Azimuth application;
//					undefine if building VectorWorks or VectorWorks Lt.
//
// _MINICAD_      : Define to 1 if building the main VectorWorks-family application;
//					undefine if not (building plug-ins, SDK, etc.).
//
// _WIN_EXTERNAL_ : Automatically defined to be 1 if building a Windows-based
//					external; automatically undefined if not.
//
// _MFC_EXTERNAL_ :	Automatically defined to be 1 if building an MFC-based
//					Windows external; automatically undefined if not.
//
/////////////////////////////////////////////////////////////////////////////////////////

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



/////////////////////////////////////////////////////////////////////////////////////////
// Miscellaneous

#define _GSDEBUG_LIB_		1		// Debug code in separately-compiled library
#if GS_WIN
	#define GS_HWND_CHECK	1
#else
	#define GS_HWND_CHECK	0
#endif

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

#define _hypot hypot
#define _stricmp stricmp
#define _strcmpi strcmpi
#define _strcmp strcmp
#define _strnicmp strnicmp


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


/////////////////////////////////////////////////////////////////////////////////////////
// The file "User.h" is a file that each person that builds VectorWorks must have. The
// contents of this file is up to each individual user. The most common use is to define
// a name constant so that you can insert code into source that only compiles for you.
// This file MUST NOT be included in the SourceSafe project. The file is only included in
// developer builds of the application.
//
// If you get an error because of a missing User.h file, do this:
//
// Create a file named User.h in Bernini:AppSource:Include:Common: and add
// the following to the file:
//
// #define MyName 1
//
// where MyName is the login name you use for the company file servers and
// the SourceSafe databases. (This should be the same name.) See Paul if you
// don't know what name to use.
//
//
// This allows you to write code like the following:
//
//        #if Dave
//            ...debug code for me only...
//        #else
//            ...code for everyone else...
//        #endif

#if BUG && _MINICAD_
	#include "User.h"  // if you get an error here, see the above comment
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


/////////////////////////////////////////////////////////////////////////////////////////
// Global Includes

#include "ImportAndExportDefines.h"		// Defines function and class export tags

#include "../VWMM/VWMM.h"


/////////////////////////////////////////////////////////////////////////////////////////
// Feature/Implementation Variables

	/////////////////////////////////////////////////////////////////////////////////////
	// Carbon-Related Variables

	// Code which is apparently functional but needs additional scrutiny for
	//  Carbon should be marked with this identifier in a comment block
	#define GS_CARBON_REVISIT

	// Late 9.5.0 changes to reduce slowdowns caused by large workspaces and menus.
	// Setting this to 0 will restore the 9.0.1 behavior. - JDW 10/29/01
	#define GS_MENU_SPEEDUP 1

	/////////////////////////////////////////////////////////////////////////////////////
	// VW 10 flags
	#define	GS_VW10_FEATURE			0

#define POSTDRAWING_NXOR 1

	#if GS_MAC
        #define NNA_COCOA_OIP_DEBUG_ENABLED 0
        #define NNA_COCOA_LAYOUT_MANAGER_DEBUG_ENABLED 0
	#endif

#define WIDGET_FRAMEWORK_ENABLED 1

#define GS_USE_NEW_SELECTION_TOOL

#define CORE_IS_RESOLUTION_INDEPENDENT 1
#define CORE_IS_RESOLUTION_INDEPENDENT_PHASE2 0

#if GS_MAC
#define HW_USE_STANDARD_STREAMS 1
#define USE_NEW_IOSTREAMS 1
#endif


#define Use_QD_ 0	// as of 9.18.13 we set this to "0" so no more QuickDraw is being called.
					//  There is still code that needs to be removed or replaced inside the
					// USE-QD_ flags below.

#if Use_QD_
#define Use_QD_FOR_Core_Application 1		// Remove QuickDraw APIs in the Core application
#define Use_QD_FOR_PLUGINS 1				// Remove QuickDraw APIs in the Plugins
#define Use_COCOA_FONTS__FOR_QD_REMOVAL_TASK 0
#else
#define Use_QD_FOR_Core_Application 0		// Keep the existing QuickDraw APIs in the Core application
#define Use_QD_FOR_PLUGINS 0				// Keep the existing QuickDraw APIs in the Plugins
#define Use_COCOA_FONTS__FOR_QD_REMOVAL_TASK GS_MAC
#endif

////////////////////

//	Use_QD_ Flags
//
//	Workflow:
//
//	MAKE SURE mainline builds with Use_QD_ "1" set above.  You likely will set this to "0" to work in
//		Xcode463QDRemoval.
//
//	Target a particular Use_QD_#### flag. Feel free to add new Use_QD_ flags if you
//	need to split code up.
//
//	Install Xcode463QDRemoval. This special Xcode lets you compile without QuickDraw.
//You can find this : smb://nemetschekfiles/SoftwareDev/EngineeringLibrary/MasterDevTools/Mac/Xcode/For Mac OS 10.7 & 10.8/Xcode463QDRemoval.zip
//
//	Check in a comment in SharedDefines.h so others know you are working on a particular flag.
//
//	The name of the game:  "REPLACE OR REMOVE"
//
//	QuickDraw code will either be replaced or removed to achieve our GOAL.  For example,
//	Charlene was able to REMOVE a lot of QD code in the TrueTypeTOPoly Plugin.  See her
//	CL 201272
//
//	See Steve with any questions.
//
//	Thanks for helping out - 64 Bit or BUST!
//


#ifndef USE_QD_FontMapping
	// Brian W ?
	// As of 9.13.13 a search shows 12 blocks of code in 4 files:
	// As of 9.30.13 a search shows 8 blocks of code in 2 files:
#define USE_QD_FontMapping Use_QD_FOR_Core_Application
#endif

#ifndef USE_QD_EXPORTPICT
	// John K ?
	// As of 9.13.13 a search shows 6 blocks of code in 2 files:
#define USE_QD_EXPORTPICT Use_QD_FOR_Core_Application
#endif

#ifndef USE_CARBON_PRINTINFOMAC_kPCTQuickDrawAndPS
	// John K ?
	//	Not sure what we need to replace here.
#define USE_CARBON_PRINTINFOMAC_kPCTQuickDrawAndPS Use_QD_FOR_Core_Application
#endif

/////////////////////////////////////////
//
//	Plugin Flags:

#define USE_OLD_DATATAGUPDATING 0 // This flag will be used if we need to go back old updating.

///////////

