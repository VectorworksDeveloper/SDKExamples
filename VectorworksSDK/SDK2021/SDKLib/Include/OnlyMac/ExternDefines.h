//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Global definitions and includes go here


/*
The ExternDefines files include the basic files and define the correct
preprocessor symbols to enable three versions of the external to be built.

	RELEASE - contains no debugging code
	
	TEST - contains invisible debugging code.
			DMSG calls do nothing
			DSTOP and ASSERT calls report to network based debug server
				if you are running a BUG or TEST build of MiniCad
	
	BUG - contains full debugging code
			DMSG calls print to the DebugWindow application
			DSTOP and ASSERT calls report to network based debug server
				and break into MacsBug or a high level debugger.
	
	
	To enable these capabilities, you should include one of the following
	files in the Metrowerks C/C++ Language Prefix File in the Preferences dialog.
	
	GSRELEASE.h
	GSTEST.h
	GSBUG.h

*/


#define _MINICAD_EXTERNAL_ 1

#if defined(__MWERKS__) || defined(WINVER)
#define UNIVERSAL_INTERFACES 1
#endif


#if defined(__MWERKS__)


// here is where we check, warn, and reset compile options which
// will cause our external to break

#pragma warn_emptydecl on
#pragma warn_extracomma on
#pragma warn_illpragma on
#pragma warn_possunwant on
#pragma warn_unusedarg on
#pragma warn_unusedvar on


//#error This will generate an error

#if __MWERKS__ < 0x0800
#error You must use CodeWarrior 8 or more recent.
#endif

#if __A5__
#error This external is not set up as a code resource!
#endif

// GS_SDKPPC_JAK
// SDK Plug-ins are now PPC so these options are undefined, (as of VW 9.0.0).  JAK 10/21/99
//
// #if !__option(fourbyteints)
// #error Externals require four byte ints!
// #endif
//
// #if !__option(IEEEdoubles)
// #error Externals require 8 byte doubles! (you must select eight byte doubles)
// #endif

#if __option(unsigned_char)
#error Cannot use unsigned chars with externals
#endif

#if __option(pool_strings)
// This check must be disabled due to a bug in CW 8.3
//#error Pooling strings is untested in GS externals
#endif

// SDK Plug-ins are now PPC so these options are undefined, (as of VW 9.0.0).  JAK 10/21/99
// #if __option(pcrelstrings)
// #error PC relative strings are untested in GS externals
// #endif

#if __option(enumsalwaysint)
#error enumsalwaysints should be off in preferences. 
#endif

#if __option(exceptions)
//#error Exceptions are not yet supported in externals
#endif

// SDK Plug-ins are now PPC so these options are undefined, (as of VW 9.0.0).  JAK 10/21/99
// #if __option(mpwc)
// #error Cannot use MPW calling conventions globally!
// #endif

#if __option(mpwc_relax)
#error Cannot use MPW pointer type rules!
#endif

// SDK Plug-ins are now PPC so these options are undefined, (as of VW 9.0.0).  JAK 10/21/99
// #if __option(far_data)
// Commented out the following error so that the Far Data option can
// be used in externals. This is necessary for the Workspace Editor. -Caleb.
// #error You are doing something wrong if you need far_data!
// #endif

#if !__option(mpwc_newline)
#error You should use MPW newlines and include (N) versions of standard libs!
#endif

#if __option(profile)
#error Externals have not been tested with the profiler!
#endif

#if __option(RTTI)
// Commented out the following error so that RTTI can be used for the
// TTSMAttachment in the Workspace Editor. -Caleb.
//#error Externals have not been tested with the RTTI!
#endif

// Externals should use:
// ANSI (N/4i) C++.A4.68K.Lib
// ANSI (N/4i) C.A4.68K.Lib
// MathLib68K (4i).A4.Lib
// CPlusPlusA4.lib
// MacOS.lib


// generate an error if inconsistent precompiled header is used
#pragma check_header_flags on
#pragma ignore_oldstyle off
#pragma extended_errorcheck on
#pragma options align= mac68k
#pragma align_array_members off

// #pragma code68020 off
// #pragma code68881 off


#if BUG
#pragma auto_inline off
#pragma dont_inline on

// remove because it is unnecessary for PowerPC - PCP 10-17-2000
//#pragma a6frames on

#else
#pragma dont_inline off
#endif

#if TEST
#pragma sym on
// #pragma macsbug on

// remove because it is unnecessary for PowerPC - PCP 10-17-2000
//#pragma oldstyle_symbols off

#else
// #pragma macsbug off
#endif

#endif

#if __MWERKS__
//#undef OLDROUTINELOCATIONS
//#define OLDROUTINELOCATIONS 0
#endif

#include "Kernel/ExternalUser.h"



