//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#if GS_SHELL_BUILD && _WINDOWS

	// When building the MFC application, I think it's better to use the 'new' provided
	// by MFC (which does not throw). I'm afraid it will cause hidden nasties if we use
	// our own 'new' instead of MFC's global 'new' or (this is the important one:) their
	// 'CObject::new' method.  [DMB 5/28/99 & 8/2/00]

#if BUG
	#define NEW_NOTHROW DEBUG_NEW
#else
	#define NEW_NOTHROW new
#endif

#else

#include <stdlib.h>
#include <new>


#if !GS_SHELL_BUILD && !GS_CORE_BUILD && !GS_COMP_BUILD && !GS_PROTECTION_BUILD && GS_WIN

#elif GS_WIN
	#ifndef nil
		#define nil 0
	#endif
	typedef char   *Ptr;
	typedef Ptr	   *Handle;
	
	typedef ptrdiff_t	Size; 
	
	typedef short	OSErr;
#endif

////////////////////
// OVERVIEW
////////////////////

/*

There are two general types of memory allocation within MiniCad: Those allocations
which can return failure, and those which cannot.
	
	Allocations which cannot return failure rely on the Mac's (and Altura's)
		growZone functionality, which provides a mechanism by which a memory
		failure handler (similar to new_handler in c++) is called when there is
		not enough memory. This handler is responsible for finding enough memory
		or terminating the application. Usually, it can satisfy the request by
		releasing part of an emergency block it keeps around just for that purpose.
		Since memory failure can terminate the application, though, it does not
		provide a good general solution.

		Allocation families which do not return errors:
			
			NewHandleGZ and other GZ routines.
			
			NEW_GZ

	Allocations which do return errors rely on their client code to ALWAYS do the
		appropriate thing if an allocation fails. If the client code does not notice
		a nil returned from an allocation routine, the application will crash when
		this memory is used. Even worse, if the application is in the middle of a complex
		operation, failure to get memory can set off a chain reaction of incorrect error
		handling which can result in a corrupted file.

		Allocation families which return errors:
			
			VWMM::NewHandle and other Ck routines.
			
			NEW_THROW
			
			NEW_NOTHROW
	
	
	Allocation routines from the standard C library such as malloc() and its many cousins
		have not been set up to handle errors gracefully and SHOULD NEVER BE USED. Use of
		these functions will compromize the stability of the application.

*/



/////////////////////////////////////////////////////////////////////////////////////////
// Define macro used to export functions.

#if GS_CORE_DLL
	#if _WINDOWS
		#if GS_CORE_BUILD
			#define GS_MEMORY_EXPORT	__declspec( dllexport )
		#else
			#define GS_MEMORY_EXPORT	__declspec( dllimport )
		#endif
	#else
		#define GS_MEMORY_EXPORT
	#endif
#else
	#define GS_MEMORY_EXPORT
#endif



/////////////////////////////////
// Define Query Functions
/////////////////////////////////

GS_MEMORY_EXPORT size_t GSFreeMem();
GS_MEMORY_EXPORT size_t GSMaxBlock();


/////////////////////////////////
// Define GZ_ versions of allocation calls 
/////////////////////////////////

#if BUG

	#if !GS_ALLOW_MAC_MEMORY_CALLS

	#endif // !GS_ALLOW_MAC_MEMORY_CALLS

#endif // BUG

/////////////////////////////////
// Convenience Routines 
/////////////////////////////////

#if GS_CORE_BUILD || defined(__MEMORY__)

Boolean	HandleIsLocked (Handle handle);
Boolean	HandleIsPurgeable (Handle handle);
Boolean	HandleIsResource (Handle handle);

#endif



void	GS_MEMORY_EXPORT SignalLowMemory();
			// SignalLowMemory is used by all Ck style allocation routines to notify
			// the application (and the user) that a memory allocation failure has
			// occurred.

GS_MEMORY_EXPORT void		HLockCk(Handle h);
GS_MEMORY_EXPORT void		HUnlockCk(Handle h);
GS_MEMORY_EXPORT char		HGetStateCk(Handle h);
GS_MEMORY_EXPORT void		HSetStateCk(Handle h, char flags);


/////////////////////////////////
// DisposeHandleSetNil
/////////////////////////////////

GS_MEMORY_EXPORT void LLDisposeHandleSetNil(Handle& h);

template <class T>
	inline void DisposeHandleSetNil(T** &h)
		{ LLDisposeHandleSetNil(CAST(Handle, h)); }





/////////////////////////////////
// Memory Management globals 
/////////////////////////////////

GS_MEMORY_EXPORT extern Boolean opAbortLowMem;

	// opAbortLowMem is set to true if a memory allocation routine fails.
	// The next time the application reaches the main event loop, a low
	// memory dialog is presented to the user.


////////////////////////////////////////////////
// operator new Redefinitions
////////////////////////////////////////////////
#if BUG
	#if _WINDOWS
		#define	_CRTDBG_MAP_ALLOC 1
		#include <crtdbg.h>
	#else
		#define DEBUG_NEW	DEBUG_NEW_OFF
	#endif
#endif

// HACK - for some strange reason, MSVC doesn't support = {} here!!
#if BUG
	#if _WINDOWS
		#define NNA_GDB_NOT_OPAQUE_STRUCTURE_MARKER
	#else
		#define NNA_GDB_NOT_OPAQUE_STRUCTURE_MARKER char notOpaqueStructureMarker
	#endif
#else
	#define NNA_GDB_NOT_OPAQUE_STRUCTURE_MARKER
#endif

struct usethrow_t { NNA_GDB_NOT_OPAQUE_STRUCTURE_MARKER; };
#if __MWERKS__
	const usethrow_t usethrow = {};
#else
	const usethrow_t usethrow = usethrow_t();
#endif

struct nna_nothrow_t { NNA_GDB_NOT_OPAQUE_STRUCTURE_MARKER; };
#if __MWERKS__
	const nna_nothrow_t nna_nothrow = {};
#else
	const nna_nothrow_t nna_nothrow = nna_nothrow_t();
#endif



////////////////////////////////////////////////
// new_nothrow
////////////////////////////////////////////////

// This is the basic implementation of an allocator which does not throw
// We can't use nothrow syntax on Windows, so we catch any exceptions
// which might be thrown. Note that this allocator works correctly regardless
// of whether the new implementation might throw exceptions.

// Exceptions depend on the allocator being set up correctly in SetUpMemory() in
// MemoryMaintenance.cp

#if BUG
inline void *new_nothrow(size_t s, const char* file, Sint32 line) //throw(bad_alloc)
#else
inline void *new_nothrow(size_t s) //throw(bad_alloc);
#endif
{
	try {
		#if BUG
			#if _WINDOWS
				return ::operator new(s, _NORMAL_BLOCK, file, line);
			#else
				return ::operator new(s); // , file, line); // Turned off for the Mach-O version of VectorWorks.
			#endif
		#else
			return ::operator new(s);
		#endif
	}
	catch(std::bad_alloc) {
		return nil;
	}
#if _WINDOWS
	// In MFC projects, CMemoryException is usually raised instead of std::bad_alloc. Catch all and return nil.
	catch(...) {
		return nil;
	}
#endif
}

#if !_WINDOWS
#if BUG
inline void *new_nothrow_array(size_t s, const char* file, Sint32 line) //throw(bad_alloc)
#else
inline void *new_nothrow_array(size_t s) //throw(bad_alloc);
#endif
{
	try {
		#if BUG && GS_MAC_CFM
			return ::operator new[](s, file, line);
		#else
			return ::operator new[](s);
		#endif
	}
	catch(std::bad_alloc) {
		return nil;
	}
}
#endif


////////////////////////////////////////////////
// new(nothrow)
////////////////////////////////////////////////

// since we want new(nothrow) to fail without using growZone memory, we are defining this
// for both Mac and Win. The Mac version will override its equivalent in the runtime library.

#if BUG
inline void *operator new(size_t s, const nna_nothrow_t&, const char* file, Sint32 line) //throw()
#else
inline void *operator new(size_t s, const nna_nothrow_t&) // throw()
#endif
{
	#if BUG
	void* result = new_nothrow(s, file, line);
	#else
	void* result = new_nothrow(s);
	#endif
	
	if (!result)
		SignalLowMemory(); // signal the low mem alert

	return result;
}


#if !_WINDOWS
// CW4 Pro compilers require a separate implementation for new[]

#if BUG
inline void *operator new[](size_t s, const nna_nothrow_t&, const char* file, Sint32 line) //throw()
#else
inline void *operator new[](size_t s, const nna_nothrow_t&) // throw()
#endif
{
	#if BUG
	void* result = new_nothrow_array(s, file, line);
	#else
	void* result = new_nothrow_array(s);
	#endif
	
	if (!result)
		SignalLowMemory(); // signal the low mem alert

	return result;
}

#endif // !_WINDOWS


////////////////////////////////////////////////
// new(usethrow)
////////////////////////////////////////////////

// throws on allocation failure, but doesn't use growZone memory

#if BUG
inline void *operator new(size_t s, const usethrow_t&, const char* file, Sint32 line) // throw(bad_alloc)
#else
inline void *operator new(size_t s, const usethrow_t&) // throw(bad_alloc)
#endif
{
	#if BUG
	void* result = ::operator new(s, nna_nothrow, file, line);	// call our new which doesn't throw, and doesn't use growZone memory
	#else
	void* result = ::operator new(s, nna_nothrow);				// call our new which doesn't throw, and doesn't use growZone memory
	#endif

	if (!result) {
		SignalLowMemory();									// signal the low mem alert
		throw std::bad_alloc();								// throw if we fail
	}
	
	return result;
}

#if !_WINDOWS
// CW4 Pro compilers require a separate implementation for new[]

#if BUG
inline void *operator new[](size_t s,const usethrow_t&, const char* file, Sint32 line) // throw(bad_alloc)
#else
inline void *operator new[](size_t s,const usethrow_t&) // throw(bad_alloc)
#endif
{
	#if BUG
	void* result = ::operator new[](s, nna_nothrow, file, line);	
	#else
	void* result = ::operator new[](s, nna_nothrow);				
	#endif
	
	if (!result) {
		SignalLowMemory();									// signal the low mem alert
		throw std::bad_alloc();								// throw if we fail
	}

	return result;
}
#endif

////////////////////////////////////////////////
// MACRO Definitions
////////////////////////////////////////////////


// NEW_THROW  - Mainstream version of operator new which throws bad_alloc on failure.
//
// NEW_NOTHROW	- Mainstream version of operator new which returns NULL on failure.
//
// NEW_GZ  - Low level allocator which has no failure mechanism other than application termination.
//           DO NOT USE THIS unless you have a very good reason
//
// Usage examples:
//
//   object* objPtr = NEW_NOTHROW Object;	// returns nil on failure, does not throw, does not use growZone memory
//   object* objPtr = NEW_THROW Object;		// throws bad_alloc on failure, does not use growZone memory
//   object* objPtr = NEW_GZ Object;		// quits application on failure, uses growZone memory

#if BUG
	// these are the macros which are responsible for passing the proper
	// debug info for leak location identification
	#define NEW_NOTHROW		new(nna_nothrow, THIS_FILE, __LINE__)
	#define NEW_THROW		new(usethrow, THIS_FILE, __LINE__)
#else
	#define NEW_NOTHROW		new(nna_nothrow)
	#define NEW_THROW		new(usethrow)
#endif

// this will go away - PCP
#ifdef DEBUG_NEW
	#undef DEBUG_NEW
#endif
#define DEBUG_NEW		NEW_NOTHROW

#endif // GS_SHELL_BUILD && _WINDOWS



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

namespace VWMM
{
	class Partition;
};

extern VWMM::Partition* gVWMM;
