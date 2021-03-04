//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef _CALLBACKPARAMTYPES_
#define _CALLBACKPARAMTYPES_

#pragma once

#include "GSTypes.h"


#define MUST_PROMOTE_SCALARS 0


typedef Sint8				lbyte_t;
typedef Uint8				lubyte_t;
typedef Sint16				lshort_t;
typedef Uint16				lushort_t;
	

typedef lbyte_t				lboolean_t;

#if _WINDOWS
	typedef Real64			callback_double_param;
	typedef Real64			CBDouble_param;
	typedef const Real64  &CBWorldCoord_param;	// JAK 10/15/99 еееееееееееееееееееееееееееееееееееееееее
#else
	// Callbacks always take FP params by reference because
	// Mixed Mode can't convert stack based to register based.
	typedef const Real64  &callback_double_param;
	typedef const Real64  &CBDouble_param;
	typedef const Real64  &CBWorldCoord_param;	// JAK 10/15/99 еееееееееееееееееееееееееееееееееееееееее
#endif



typedef Sint8				CBSignedByte;
typedef Uint8				CBUnsignedByte;
typedef Sint16				CBSignedShort;
typedef Uint16				CBUnsignedShort;
typedef CBSignedByte		CBBoolean;
typedef Real64				CBDouble;


#endif // _CALLBACKPARAMTYPES_
