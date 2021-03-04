//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Cross-platform memory management functions for VectorWorks 9.
//

#ifndef _MCMEMORY_H_
#define _MCMEMORY_H_ 1

#pragma once

#include "MemoryAllocationVWMM.h"

// I am hereby inventing a new naming convention: Mem_[function name]
// (this is, of course, subject to revision at any time, by myself or any competent authority).

// The names of these functions are based on the names of Macintosh Memory Manager functions.
// This should make it possible to do a fairly straightforward search-and-replace
// when converting MiniCAD files.

// XXX: Should we use Handle or a new type?
//			What about the already defined GSHandle (GSTypes.h). There is no GSPtr defined
//			yet (don't know why). [DMB 9/4/98]

// 10/6/98  LAK  renamed Handle to MemHandle, to avoid conflict with QuickTime types


/////////////////////////////////////////////////////////////////////////////////////////
// Data types

typedef char* MemPtr;
typedef char** MemHandle;
typedef size_t MemSize;


/////////////////////////////////////////////////////////////////////////////////////////
// Nulls

const MemPtr	Mem_NullPtr		= (MemPtr) 0;
const MemHandle	Mem_NullHandle	= (MemHandle) 0;


/////////////////////////////////////////////////////////////////////////////////////////

#if GS_INTERFACE_FACTORING && !GS_CORE_BUILD

	void		GS_COMP_API Mem_SetupMemory();
	void		GS_COMP_API Mem_MaintainMemory();
	void		GS_COMP_API Mem_CleanupMemory();

	MemPtr		GS_COMP_API Mem_NewPtr(MemSize size);
	MemPtr		GS_COMP_API Mem_NewPtrClear(MemSize size);
	void		GS_COMP_API Mem_DisposePtr(MemPtr pointer);
	MemHandle	GS_COMP_API Mem_NewHandle(MemSize size);
	void		GS_COMP_API Mem_DisposeHandle(MemHandle handle);

	MemHandle	GS_COMP_API Mem_NewHandleClear(MemSize size);

	template <class T>
		inline void Mem_DisposeHandleSetNil(T** &h)
			{ Mem_DisposeHandle((MemHandle)h); h = Mem_NullHandle; }

	void		GS_COMP_API Mem_HLock(MemHandle handle);			// ???	might not need these
	void		GS_COMP_API Mem_HUnlock(MemHandle handle);		// ???
	bool		GS_COMP_API Mem_IsHandleLocked(MemHandle handle);

	#define		Mem_HLockHi	Mem_HLock

	Sint8		GS_COMP_API Mem_HGetState(MemHandle handle);
	void		GS_COMP_API Mem_HSetState(MemHandle handle, Sint8 state);

	MemSize		GS_COMP_API Mem_GetHandleSize(MemHandle handle);
	Bool8		GS_COMP_API Mem_SetHandleSize(MemHandle handle, MemSize newSize);
	void		GS_COMP_API Mem_ReduceHandleSize(MemHandle handle, MemSize newSize);

	void		GS_COMP_API Mem_HandToHand(MemHandle &handle);
	void		GS_COMP_API Mem_PtrToHand(MemPtr srcPtr, MemHandle &dstHndl, MemSize size);
	Bool8		GS_COMP_API Mem_PtrToXHand(MemPtr srcPtr, MemHandle dstHndl, MemSize size);	// not used much - can dispense with?
	Bool8		GS_COMP_API Mem_HandAndHand(MemHandle hand1, MemHandle hand2);				// not used much - can dispense with?
	Bool8		GS_COMP_API Mem_PtrAndHand(MemPtr ptr1, MemHandle hand2, MemSize size);

	inline MemHandle GS_COMP_API Mem_CopyHand(MemHandle h) { MemHandle hCopy = h; Mem_HandToHand(hCopy); return hCopy; }

	//#define StripAddress(x) ((MemPtr)(x))			This should go away

	//Bool8 HandleIsPurgeable(MemHandle handle)		These can definitely go away
	//Bool8 HandleIsResource(MemHandle handle)


	/////////////////////////////////////////////////////////////////////////////////////////
	// Generic memory manipulation functions.

	void GS_COMP_API Mem_Copy(void *pDest, const void *pSrc, MemSize nBytes);
	void GS_COMP_API Mem_Move(void *pDest, const void *pSrc, MemSize nBytes);
	void GS_COMP_API Mem_Zero(void *pDest, MemSize nBytes);
	void GS_COMP_API Mem_Fill(void *pDest, MemSize nBytes, Uint8 uFill);


	///////////////////////////////////////////////////////////////////////////////
	// Debugging functions - don't call these directly!
	///////////////////////////////////////////////////////////////////////////////

	// Don't do these macro substitutions when compiling MCMemory.cpp itself
	#if BUG
		#ifndef _MCMEMORY_
			#define Mem_NewHandle(s)		Mem_NewHandleDebug(s, THIS_FILE, __LINE__)
			#define Mem_NewHandleClear(s)	Mem_NewHandleClearDebug(s, THIS_FILE, __LINE__)
			#define Mem_SetHandleSize(h, s)	Mem_SetHandleSizeDebug(h, s, THIS_FILE, __LINE__)
		#endif // _MCMEMORY_

		MemHandle GS_COMP_API Mem_NewHandleDebug(MemSize size, const char* file, Sint32 line);
		MemHandle GS_COMP_API Mem_NewHandleClearDebug(MemSize size, const char* file, Sint32 line);
		Bool8 GS_COMP_API Mem_SetHandleSizeDebug(MemHandle handle, MemSize newSize, const char* file, Sint32 line);
	#endif // BUG


	/////////////////////////////////////////////////////////////////////////////////////////
	// Map GS_ memory functions to Mem_ memory functions.

	#if !GS_CORE_BUILD

		#define GS_DisposeHandle(cbp, h)		Mem_DisposeHandle(h)
		#define GS_GetHandleSize(cbp, h, sz)	sz = Mem_GetHandleSize(h)
		#define GS_NewHandle(cbp, sz)			Mem_NewHandle(sz)
		#define GS_SetHandleSize(cbp, h, sz)	Mem_SetHandleSize(h, sz)

		#define GS_ReduceHandleSize(cbp, h, sz)	Mem_ReduceHandleSize(h, sz)
		#define GS_HLock(cbp, h)				Mem_HLock(h)
		#define GS_HUnlock(cbp, h)				Mem_HUnlock(h)

		#define GS_GetHandleState(cbp, h, isLocked) isLocked = Mem_IsHandleLocked(h)
		#define GS_SetHandleState(cbp, h, isLocked)	do { if (isLocked) Mem_HLock(h); else Mem_HUnlock(h); } while (0)

	#endif



#else

	/////////////////////////////////////////////////////////////////////////////////////
	// This section is used for Braque. It maps all new VectorWorks 9 memory management
	// functions to old calls for VectorWorks 8.5

	#define Mem_NewPtr					gVWMM->NewPtr
	#define Mem_NewPtrClear				gVWMM->NewPtrClear
	#define Mem_DisposePtr				gVWMM->DisposePtr

	#define Mem_NewHandle				gVWMM->NewHandle
	#define Mem_NewHandleClear			gVWMM->NewHandleClear
	#define Mem_DisposeHandle			gVWMM->DisposeHandle

	#define Mem_HLock					gVWMM->HLock
	#define Mem_HUnlock					gVWMM->HUnlock
	#define Mem_HLockHi					UNDEFINED_HLockHi

	#define Mem_HGetState				gVWMM->HGetState
	#define Mem_HSetState				UNDEFINED_HSetState

	#define Mem_GetHandleSize			gVWMM->GetHandleSize
	#define Mem_SetHandleSize			gVWMM->SetHandleSize
	#define Mem_ReduceHandleSize		UNDEFINED_ReduceHandleSize

	#define Mem_HandToHand				UNDEFINED_HandToHand
	#define Mem_PtrToHand				UNDEFINED_PtrToHand
	#define Mem_PtrToXHand				UNDEFINED_PtrToXHand
	#define Mem_HandAndHand				UNDEFINED_HandAndHand
	#define Mem_PtrAndHand				UNDEFINED_PtrAndHand
	#define Mem_CopyHand				UNDEFINED_CopyHand

	#define Mem_Copy(dest, src, bytes)	::VWMM::NNABlockMoveData(src, dest, bytes)
	#define Mem_Move(dest, src, bytes)	::VWMM::NNABlockMoveData(src, dest, bytes)
	#define Mem_Zero(dest, bytes)		Mem_Fill(dest, bytes, 0)
	#define Mem_Fill(dest, bytes, fill)	memset(dest, fill, bytes)

#endif // GS_INTERFACE_FACTORING && !GS_CORE_BUILD

#endif // _MCMEMORY_H_
