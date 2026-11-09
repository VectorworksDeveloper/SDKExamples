//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Preprocessor stuff for the Core module. This file has a companion file that has
// preprocessor stuff for all modules:  Include/Common/SharedDefines.h
//

#pragma once


///////////////////////////////////////////////////////////////////////////////
// This section defines cross-platform macros for declaring callback functions which
// need to be passed to MacOS on the Mac platform and Altura on the Windows platform.
// These can be used in VectorWorks code or Altura-based externals.
//

#if !_GSWINSDK_
	#define HAS_PASCAL 1
	
	#if GS_WIN
		#if _MINICAD_
			#define __pascal				__stdcall
			#define _pascal					__stdcall
//			#define pascal					__stdcall
			#define __export				__declspec(dllexport)
			#define _export					__declspec(dllexport)
		#endif
		#define MACOS_CALLBACK				//__declspec(dllexport) __stdcall
		#define MACOS_CALLBACK_PTR(name)	(/*__stdcall */ *name)
	#else
		#define MACOS_CALLBACK				pascal
		#define MACOS_CALLBACK_PTR(name)	pascal (*name)
	#endif
#endif // !_GSWINSDK_


///////////////////////////////////////////////////////////////////////////////
// This section contains function type specifiers for all modules.
//
//	MINICAD_FUNC : Use for functions that reside in VectorWorks.exe.
//		Calling convention will be the default for the file.
//
//	MINICAD_C_FUNC : Use for functions that reside in VectorWorks.exe.
//		Calling convention will be C.
//
//	MINICAD_PASCAL_FUNC : Use for functions that reside in MiniCad.exe.
//		Calling convention will be Pascal-like.

#if GS_WIN
	#ifdef __cplusplus
		#define C_FUNC	extern "C"
	#else
		#define C_FUNC
	#endif
	
	#if _MINICAD_
		#define MINICAD_FUNC	__declspec( dllexport )
	#else
		#define MINICAD_FUNC	__declspec( dllimport )
	#endif
	#define MINICAD_C_FUNC		C_FUNC MINICAD_FUNC
	#define MINICAD_PASCAL_FUNC	MINICAD_FUNC __stdcall

	#if _GSWINSDK_
		#define GSWINSDK_FUNC	__declspec( dllexport )
	#else
		#define GSWINSDK_FUNC	__declspec( dllimport )
	#endif

	#if _MCWINSUP_
		#define MCWINSUP_FUNC	__declspec( dllexport )
	#else
		#define MCWINSUP_FUNC	__declspec( dllimport )
	#endif
	#define MCWINSUP_C_FUNC		C_FUNC MCWINSUP_FUNC
	
#else  // Macintosh
	
	#define MINICAD_FUNC
	#define MINICAD_C_FUNC
	#define MINICAD_PASCAL_FUNC	pascal
	#define GSWINSDK_FUNC
	#define MCWINSUP_FUNC
	#define MCWINSUP_C_FUNC
#endif  // GS_WIN


///////////////////////////////////////////////////////////////////////////////
// This determines if the code is being compiled as a Mac external
// we need to integrate any preprocessor symbols used by Windows externals - PCP

// XXX_JDW_ALTURA [2003-1-10]	out of date?	
#if ( __SC__ || _WIN_EXTERNAL_)
	#define _MINICAD_EXTERNAL_		1
#endif


/////////////////////////////////////////////////////////////////////////////////////////
// Start Windows-only section.
#if GS_WIN


///////////////////////////////////////////////////////////////////////////////
// Define things always needed for a Windows build.

#if defined(applec) || defined(macintosh) || defined(powerc)
	#error None of the following should be defined during a Windows build: applec, macintosh, powerc
	#undef applec
	#undef macintosh
	#undef powerc
#endif
#undef PROFILE
#define LONG_FILENAMES				1	// Tells Altura's header files to use Sint32 file names.
#define GRAPHSOFT					1	// Tells Altura's header files to use things specific to us.


#if !_GSWINSDK_ && !_MCWINSUP_

	#if _MINICAD_
	// Main MiniCad application.
		#if !_BLUEPRINT_
			#undef MPLUS
			#define MPLUS				1		// Building MiniCad Plus.
		#endif
		#undef WINDOWS_DO_PALETTES
		#undef  _MINICAD_EXTERNAL_
		#undef  _WIN_EXTERNAL_
		#undef  _MFC_EXTERNAL_
	//#elif ALTURA		XXX_JDW_ALTURA CLEANUP
	//// Altura based externals.
	//	#define _MINICAD_EXTERNAL_		1
	//	#undef  _WIN_EXTERNAL_
	//	#undef  _MFC_EXTERNAL_
	#elif _AFX
	// MFC based externals.
		// Check MFC version number.
		#if _MFC_VER < 0x0400
			#error MiniCad MFC externals require MFC version 4.0 or later.
		#endif
		#define _MINICAD_EXTERNAL_		1
		#define _WIN_EXTERNAL_			1		// Building a Windows based external.
		#define _MFC_EXTERNAL_			1		// Building an MFC based MiniCad external.
	#else
	// Windows based externals.
		#define _MINICAD_EXTERNAL_		1
		#define _WIN_EXTERNAL_			1		// Building a Windows based external.
		#undef  _MFC_EXTERNAL_
	#endif

//	#if _WIN_EXTERNAL_
		#ifdef ALTURA
			#error Can not build Altura-based Windows externals.
		#endif
//	#else
////		#define ALTURA					1		// Using Altura's Mac2Win.
//	#endif

#endif // !_GSWINSDK_ && !_MCWINSUP_


//#if _MINICAD_EXTERNAL_ || _GSESDK_
//	#if _MFC_EXTERNAL_
//		#undef _supply_new_
//	#else
//		#define _supply_new_			1
//	#endif
//#endif


/////////////////////////////////////////////////////////////////////////////////////////
// Turn off annoying compiler warnings. Think Sint32 and hard before putting a warning
// into this section, we don't want to cover up any legitimate errors.  More of these
// are turned off in SharedDefines.h.

#if !_MCWINSUP_
#pragma warning( disable : 4001 )		// nonstandard extension 'single line comment' was used
#pragma warning( disable : 4051 )		// possible data loss
#pragma warning( disable : 4121 )		// alignment of member sensitive to packing
#pragma warning( disable : 4125 )		// decimal digit terminates octal escape sequence
#pragma warning( disable : 4127 )		// conditional expression is constant
#pragma warning( disable : 4135 4136 )	// conversion of diff Sint32, float
#pragma warning( disable : 4209 )		// nonstandard extension used : benign typedef redefinition
#pragma warning( disable : 4214 )		// nonstandard extension used : bit field types other than Sint32
#pragma warning( disable : 4237 )		// nonstandard extension used : 'false' keyword is reserved for future use
#pragma warning( disable : 4390 )		// ';' : empty controlled statement found
#pragma warning( disable : 4505 )		// unreferenced local function was removed
#pragma warning( disable : 4699 )		// Note: Using precompiled header
#pragma warning( disable : 4705 )		// statement has no effect
#pragma warning( disable : 4711 )		// fn selected for inlining
#pragma warning( disable : 4805 )		// unsafe mix of type 'unsigned char' and type 'const bool' in operation
#endif


#endif
// End Windows-only section.
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Set up SDK compatibility mode.


// These flags indicate that the current SDK will bend over backwards
// to minimize the number of changes necessary to port externals from
// the previous SDK to the new one. It is strongly recommended that external
// developers leave this on initially to ease the transition to the new SDK,
// but turn it off later and modernize their code to call the new preferred
// functionality. Nemetschek will maintain this compatibily for only one major
// release, so release n.0.0 will have a compatability flag set to true for
// release n-1, and false for n-2 and earlier.

// *** IMPORTANT ***
// Turning these flags off can affect existing VectorScripts which use
// hard-coded object and program variable selectors. You may need to update 
// VectorScript documentation and possibly put in compatibility code to avoid
// breaking existing scripts.


// MC7 SDK compatibility mode turned off permanently by JDW 1/17/2000
#undef MC7SDK_COMPATIBLE

// VW8 SDK compatibility mode turned off permanently by JDW 8/22/2003
#undef GS_SDK_VW8_COMPATIBLE

#define GS_SDK_VW9_COMPATIBLE 1

#define GS_SDK_VW10_COMPATIBLE 1

#define GS_SDK_VW11_COMPATIBLE 1


///////////////////////////////////////////////////////////////////////////////
// Define a bunch of constants to see what we should compile in common modules.

#define USE_TOOLBAR_VIEW		1
#define	USE_CONSTRAINT_VIEW		1

#define USE_NEW_PALPOS			1	// New palette positioning


///////////////////////////////////////////////////////////////////////////////
// Activate native controls on both platforms and use Appearance Manager on Mac
//  XXX: Both of these are now always true, and should be removed from the code.

#define USE_CONTROLS 1
#if GS_MAC
	#define APPEARANCE
#endif


///////////////////////////////////////////////////////////////////////////////
// This section is temporary to include the Subscription code.
//  Currently, this will be in the mainline MiniCAD product, but
//  the possibility that it will be only in a new high-end product
//  precludes me from #ifdefing on MPLUS for its code.
//
// [TTF Code clean-up 11/30/07]



/////////////////////////////////////////////////////////////////////////////////////////
// GS_SPECIAL_VERSION is turned on in the compiler command line on Mac and Windows. You
// can build the development version of the application with this flag turned on under
// Windows by selecting the "Win32 SPECIAL Debug" target and on the Mac by passing the
// specialDev version to gbuild or using the s version for mbuild (e.g. mbuild VWPPCs).

#if GS_SPECIAL_VERSION
	// Currently nothing
#endif




/////////////////////////////////////////////////////////////////////////////////////////
//	JAK 10/15/99
//	Temporary wrapper functions around SDK calls that want to return a WorldCoord, which
//	is illegal now.  When we go to PPC SDK then I think we can turn off this switch.

#define GS_WRAP_RETURN_COORD_JAK 1




/////////////////////////////////////////////////////////////////////////////////////////
// GS_APP_METRICS
//
//	Defining GS_APP_METRICS adds GS_DEFINE_APP_METRIC_REPORT macro to the build.
//	GS_DEFINE_APP_METRIC_REPORT enables the counting and reporting of instances of 
//	code execution.  See MCNotify.h for macro definition.  See .cpp file for further 
//	documentation.
//
//	If the developer wants to create a Non- BUG build with GS_APP_METRICS defined it is 
//	suggested that he/she place a "#define GS_APP_METRICS" in User.h.
#if BUG
	#ifndef GS_APP_METRICS
		#define GS_APP_METRICS
	#endif
#endif
