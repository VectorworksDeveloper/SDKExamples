//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Setup routines / dummies for A4 management.
//
//
//	As of VW 9, the SDK Plug-ins are PowerPC native, not 68K.  
//	Therefore, the A4 management is unecessary.
//	JAK 8/16/00
//

#ifndef _GSESETUP_
#define _GSESETUP_

#ifdef ALTURA
	#include "asiport.h"
#endif

#include "MiniCadCallBacks.h"
	
// GS_SDKPPC_JAK	I am commenting out the definitions of SetUpA4 and RestoreA4 here bec I'm getting duplicate definition errors. We don't need them anyway now with PPC externals.

#define RememberA0()		((void) 0)
#define RememberA4()
#define SetUpA4()
#define RestoreA4()
#define MCXMemorizeA4(x)
#define MCXRecallA4(cbp)
#define UnloadA4Seg(x)

	struct A4Recaller {
		A4Recaller (CallBackPtr /*cbp*/) {}
	};

//////////
// SET_MFC_STATE
#if _AFXDLL

	// this state management code is not adequate to allow us to link against MFC as a DLL. This will properly
	// allow MFC code in the DLL to work as expected, but we do not reset the state during calls back into the
	// core application. Such calls which result in MFC code to execute in the core
	// (e.g. GS_ClearDataDisplayBar(gCBP)) will result in MFC becoming unable to make associations between its
	// objects and the corresponding operating system structures through its mapping mechanism, causing total failure.
	
	// if we want to allow this in the future, we need to either properly handle these state transitions across
	// all calls to the core, or not do this here at the entry point to the plug-in and force the plug-in author
	// to make these calls around their own use of MFC. Neither is a very appealing solution - PCP
	

	#define SET_MFC_STATE AFX_MANAGE_STATE( ::AfxGetStaticModuleState() )
#else
	#define SET_MFC_STATE
#endif

// GS_SDKPPC_JAK
// The following macros now handle reentrancy, and have nothing to do with 68K or A4 register as previous versions did. (for VW9)
	#define GSExternalSetup(cbp) SET_MFC_STATE; CallBackPtr rentrancyProtector = gCBP; SetupGlobalCBP(cbp); char VWMMMainPartName[] = "VWMainPartition"; gVWMM = VWMM::Partition::GetPartitionByIdentifier(VWMMMainPartName, true);

	#define GSExternalSetdown(l) gCBP = rentrancyProtector; // EJK 00/04/24 restore previous value so reentrancy stops crashing
	#define GSCalledRoutineSetup(x)

#endif // _GSESETUP_
