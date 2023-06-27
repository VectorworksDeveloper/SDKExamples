//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "KernelAPI.h"

#include "Kernel/API/APIBase.Legacy.h"

#if _MINICAD_ && !BUG
	// inline these calls if we are compiling inside MiniCAD except for the BUG version.
	// we won't get duplicate function name checks if we inline these functions
	// because the inlined functions use C++ calling conventions - PCP
	#define GS_INLINE_SDK_CALLS 1
#else
	#define GS_INLINE_SDK_CALLS 0
#endif

#if GS_INTERFACE_FACTORING && !GS_CORE_BUILD
	// This is skipped for now in Bernini because some of the functions are implemented as macros. [DMB 4/7/99]
#else
	#if GS_INLINE_SDK_CALLS
		#include "MiniCadCallBacks.InlineDefs.h"	
	#else
		#include "Kernel/API/APIBase.Legacy.Defs.h"
	#endif

#endif
