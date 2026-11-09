//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Kernel/Config.h"

#if _WINDOWS
	// We are going to define min() and max() as templates; however, at this
	// point, they have already been defined as macros by "windef.h", so we
	// undefined them here.  [DMB, 10/19/95]
	#if defined(min)
		#undef min
	#endif
	#if defined(max)
		#undef max
	#endif
#endif // _WINDOWS

#include "VWMM/VWMM.h"

// Base
#include "Kernel/Base/VariableState.h"
#include "Kernel/Base/TypesBase.h"
#include "Kernel/Base/DebugBase.h"
#include "Kernel/Base/TypesFloat.h"
#include "Kernel/Base/TypesCasting.h"
#include "Kernel/Base/TypesByteSwap.h"
#include "Kernel/Base/MemoryVWMM.h"
#include "Kernel/Base/TypesString.h"
#include "Kernel/Base/TypesArray.h"
