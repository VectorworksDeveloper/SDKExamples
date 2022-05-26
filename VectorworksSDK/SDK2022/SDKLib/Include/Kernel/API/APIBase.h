//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

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

//=======================================================================================
// typedef of RefName
typedef TXString RefName;			// RefName is TXString!


/////////////////////////////////////////////////////////////////////////////////////////

// You might think we could allow LONG_MAX (about 2 billion SysNames).  But
// the RefListType node will have 4 bytes for every SysName, and we were
// concerned that it would be a problem if its size was greater than a
// Sint32, since most of our handle functions have Sint32 parameters, assuming
// the size of the handle will not be greater than a Sint32.  We allow more
// total SysNames than named SysNames (has a string, not just an id), because
// the RefNameNode has about 68 bytes for every named SysName.  If you divide
// 2 billion by 100, you get 20 million, but we decided to be a little
// conservative and set a limit of 10 million named SysNames.  [BF 6/16/00]


const Sint32 refNumberListMax	= 100000000L;
const Sint32 refNameListMax		= 10000000L;

typedef Sint32 RefNumber;

typedef RefNumber ClassRefNumber;
typedef RefNumber HatchRefNumber;
typedef RefNumber MaterialRefNumber;
typedef RefNumber FillRefNumber;

////////////////////////
// MCObjectHandle
//   In VectorWorks, this allows access to BlankHandle
//   In externals, this provides opaque access
//   The VectorWorks internal version is in InitGlobals.h
////////////////////////

#ifndef _MINICAD_
	typedef GSHandle MCObjectHandle;
#endif
