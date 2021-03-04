//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#if !defined(ALTURADEFS_H) && _WINDOWS
#define ALTURADEFS_H
#if NNA_BUILD_WITH_QUICKTIME_
////////////////////////////////////////////////////////////////////////////////
#if _WINDOWS
#include "QuickTimeWinRemovalFlag.h"
#endif

#if !defined(_INC_WINDOWS) && !defined(__AFX_H__)
	#error (This is a Windows only file - Include Windows.h first)
#endif


////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////////
	
	typedef unsigned short		UWORD;
	typedef short			SWORD;
	
	void SysBreak(void);
	inline Sint32 StackSpace(void) {	return 2048;	}
}


////////////////////////////////////////////////////////////////////////////////
#endif // NNA_BUILD_WITH_QUICKTIME_
#endif // ALTURADEFS_H
////////////////////////////////////////////////////////////////////////////////
