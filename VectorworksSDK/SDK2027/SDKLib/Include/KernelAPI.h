//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

// Base
#include "KernelBaseTypes.h"

// Kernel Core
#include "Kernel/Core/CoreDefines.h"
#include "Kernel/Core/MCLogging.h"
#include "Kernel/Core/MCGeometry.h"
#include "Kernel/Core/UuidStorage.h"
#include "Kernel/Core/OSTDefs.h"
#include "Kernel/Core/MCNotification.h"
#include "Kernel/Core/MCResources.h"
#include "Kernel/Core/FolderSpecifiers.h"

// Math
#include "Kernel/Math/MathBasic.h"
#include "Kernel/Math/MathCoordTypes.h"
#include "Kernel/Math/MathVector.h"
#include "Kernel/Math/MathMatrix.h"

// Vectorworks Base - Low level API
#include "Kernel/API/APIBase.h"
#include "Kernel/API/Objs.TDType.h"

#if _MINICAD_ && !defined(_OBJS_BLANKTYPE_H_)
	// Need the definition of 'MCObjectHandle' from "Objs.BlankType.h".
	#include "Objs.BlankType.h"
#endif

#include "Kernel/API/ProgramVariables.h"
#include "Kernel/API/ObjectVariables.h"
#include "Kernel/API/MiniCadHookIntf.h"
#include "Kernel/API/MiniCadCallBacks.h"
#include "Kernel/API/VWUtils.h"

