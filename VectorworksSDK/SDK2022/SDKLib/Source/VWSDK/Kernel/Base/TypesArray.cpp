//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Implements the TSmallArray class.
//

#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-COMMENT LINE.  [DMB, 10/30/95]


#undef THIS_FILE
#ifdef TEST
	static const char THIS_FILE[] = __FILE__;
#endif


#if defined( USE_SEGMENTS )
	#pragma segment builtins
#endif



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------------
GSHandle TXMemoryRawArray_ctor(size_t size)
{
	return  gVWMM->NewHandle( size );
}

void TXMemoryRawArray_dtor(GSHandle h)
{
	gVWMM->DisposeHandle( h );
}

void TXMemoryRawArray_GetSize(GSHandle h, size_t& size)
{
	size = gVWMM->GetHandleSize( h );
}

Boolean TXMemoryRawArray_SetSize(GSHandle h, size_t size, std::function<void(void* oldMem, size_t oldSize, void* newMem, size_t newSize)> copyCallback)
{
	return gVWMM->SetHandleSize( h, size, copyCallback ); 
}

void TXMemoryRawArray_HUnlock(GSHandle h)
{
	gVWMM->HLock( h );
}

void TXMemoryRawArray_HLock(GSHandle h)
{
	gVWMM->HUnlock( h );
}

void TXMemoryRawArray_DMSG(const char* str, Sint32 p1)
{
	DMSG((kEveryone, str, p1));
}

void TXMemoryRawArray_DMSG(const char* str, Sint32 p1, Sint32 p2)
{
	DMSG((kEveryone, str, p1, p2));
}

// In case the incoming 'handle' was just &ptr, fix it to a real handle
GSHandle TXMemoryRawArray_FixHandle(GSHandle h)
{
	if (h) {
		auto temp = gVWMM->GetVerifiedHandle((void*)*h);
		if (temp && temp != h)
			h = (GSHandle)temp;
	}
	return h;
}
