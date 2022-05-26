//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#ifndef _VWMM_H_
#define _VWMM_H_

#include <stdint.h>
#include <stddef.h>
#include <cstring>
#include <functional>

#if _WINDOWS
	// Set this flag to build VW without Quicktime on Windows
	#define QUICKTIME_REMOVED 1
#endif

#ifndef Uint8
typedef uint8_t		Uint8;
#endif
#ifndef Uint16
typedef	uint16_t	Uint16;
#endif
#ifndef Uint32
typedef	uint32_t	Uint32;
#endif
#ifndef Sint32
typedef	int32_t		Sint32;
#endif

#ifndef Byte
typedef unsigned char Byte;
#endif

#ifndef Ptr
typedef char *                          Ptr;
#endif
#ifndef Handle
typedef Ptr *                           Handle;
#endif
#if _WINDOWS  
typedef ptrdiff_t                       Size;
#else
typedef long                            Size;  //X64PRJ_REVISIT Miriam - Eliminate upon Carbon/QT removal // QTREMOVAL
#endif

#ifndef Sint16
typedef signed short                    Sint16;
#endif

#ifndef OSErr
typedef Sint16                          OSErr;
#endif

#ifndef GSSize
typedef size_t							GSSize;
#endif

#if _WINDOWS
#ifdef VWMM_EXPORTS
	#define MM_DLL_EXPORT __declspec (dllexport)
#else	// not VWMM_EXPORTS
	#define MM_DLL_EXPORT __declspec (dllimport)
#endif	// VWMM_EXPORTS
#else	// not _WINDOWS
	#define MM_DLL_EXPORT
#endif

#ifndef _WINDOWS
#include <os/lock.h>
#endif

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
#include "VWMM_Defines.h"
#include "VWMM_Memblock.h"
#include "VWMM_Pool.h"

// -------------------------------------------------------------------------------------------------
// Used for saving the stack in allocation calls
// -------------------------------------------------------------------------------------------------
#pragma pack(push, 1)
#if MEMORY_BLOCK_STACKTRACE_HISTORY
struct StackTraceEntry
{
	StackTraceEntry *next;
	Sint32 numCalls;
	Uint32 averageSize;
	Uint32 stackLength;
	void* stack[MEMORY_BLOCK_STACKTRACE_FRAME_COUNT_LIMIT];
};
#endif
#pragma pack(pop)

namespace VWFC
{
	namespace Memory
	{
		class VWMemoryLeakChecker;
		struct MemoryLeakResults;
	}
}

// -------------------------------------------------------------------------------------------------
// VWMM encapsulates our local memory management system.
// -------------------------------------------------------------------------------------------------
namespace VWMM
{

#define PARTITION_IDENTIFIER_BUFFER_SIZE (128)
#define NUM_MEMCALLBACK_FUNCTIONS (128)


inline void NNABlockMove(const void *srcPtr,void *destPtr, size_t byteCount)
{
    if ( byteCount > 0 )
        memmove( destPtr, srcPtr, byteCount );
}
    
inline void NNABlockMoveData(const void *srcPtr,void *destPtr, size_t byteCount)
{
    if ( byteCount > 0 && srcPtr != 0)
        memmove( destPtr, srcPtr, byteCount );
}


// -------------------------------------------------------------------------------------------------
// A partition is a modular, self contained area  that contains all the information for an instance of VWMM.
// These were stored in globals before 
// -------------------------------------------------------------------------------------------------
class MM_DLL_EXPORT Partition
{
public:
	enum
	{
		PARTITION_FLAG_USEPOOL = 1,	// if set, new allocations may use the pool. If clear, they won't.
	};
protected:
	Handle fPool;	// the pool for this partition. May be NULL if no pool has been set up.
	Uint32 fFlags;	// flags for this partition, see above.

	MemoryBlock *fAllBlocks[MEMORYBLOCK_HASH_SIZE];	// all blocks currently in use in this partition (including pooled)
	size_t fBlockListCounts[MEMORYBLOCK_HASH_SIZE];	// counts the amount of blocks in each list
	
	// All resources (Created with GetOrCreateHandleFromQTResourceHandle()) are stored in these lists.
	MemoryBlock *fAllResourceBlocks[MEMORYBLOCK_HASH_SIZE];
	size_t fResourceBlockListCounts[MEMORYBLOCK_HASH_SIZE];
	
	size_t fBytesAllocated;		// total bytes currently allocated (as the user sees, does not include header info)
	size_t fNumBlocks;				// total number of blocks allocated (should be in sync with contents of fAllBlocks)
	Uint32 fNumCalls;		// this just counts the number of calls to allocate/resize for printing out debug info intermittantly
	size_t fNumPoolHits;	// increased when memory is allocated from pool instead of from heap
	size_t fNumAllocatesTotal;	// total amount of allocates.

	Sint32 fNumCallsBetweenOutput;	// how often to print out debug info
	Uint32 fMagicNumber;	// used to sanity check
	char fIdentifier[PARTITION_IDENTIFIER_BUFFER_SIZE];	// used to retrieve a partition from the map
	bool fStackTraceOn;			// if true, we will record stack information for each block.
	size_t fStackTraceDepth;	//The depth of the stack information we're going to record and print out.  Capped at MEMORY_BLOCK_STACKTRACE_FRAME_COUNT_LIMIT

	// mechanism for informing the app about out of memory conditions.
	// You register a callback function which gets called if any allocation fails. When done, unregister it.
	// The callbacks are reference counted so you can nest them if needed, and should be thread-safe.
	// The function used looks like:
	// void MemCallback(Sint32 reason, Uint32 requestSize, void* userData);
	// reason right now is always going to be VWMM_CALLBACK_ALLOCATE_FAILED.
	// requestSize is the size of the allocate that failed.
	// userData is whatever was passed in the most recent call to RegisterMemoryCallbackFunction.
	
	void (*memCallbackArray[NUM_MEMCALLBACK_FUNCTIONS])(Sint32, size_t, void *);
	Sint32 callbackFuncRefCounts[NUM_MEMCALLBACK_FUNCTIONS];
	void* callbackFuncUserData[NUM_MEMCALLBACK_FUNCTIONS];
	Sint32 GetMemoryCallbackFunctionIndex(void (*func)(Sint32, size_t, void*));	// returns -1 if not found or index (0<=ret<NUM_MEMCALLBACK_FUNCTIONS)
	Sint32 GetFreeMemoryCallbackFunctionSlot(void);
	void InvokeCallbacks(Sint32 reason, size_t requestSize);

#if MEMORY_BLOCK_STACKTRACE_HISTORY	// format for each is void * next, stacktrace string
	StackTraceEntry *fStackTraceHistory;
#endif // MEMORY_BLOCK_STACKTRACE_HISTORY

	// each slot x will contain the sum of allocations from (gAllocSizesLessThan[x - 1] + 1) to gAllocSizesLessThan[x] (for example slot 1 will be sizes 11 - 50).
	size_t fAllocSizesLessThanOrEqual[NUM_ALLOCSIZE_SLOTS];	// This holds the max alloc size for the given slot.
	size_t fAllocSizeCounts[NUM_ALLOCSIZE_SLOTS];				// this holds the count for the given slot
	Sint32 fAllocSizeTotals;	// count for average of above

	void MemoryStat_GetSlotBoundsStr(char *str, size_t slotNum); // given a slot and a buffer, fill buffer with a string such as "100-250" based on the range stored in slot
	void MemoryStat_AddAlloc(size_t size);	// add the given size allocation to the statistics

	// Some utility/helper functions
	void HookupBlockToList(MemoryBlock *block, MemoryBlock **blockList, size_t *countArray);		// assumes block valid and not in a list.
	void RemoveBlockFromList(MemoryBlock *block, MemoryBlock **blockList, size_t *countArray);	// assumes block is in this list.

	// Used to keep a mapping of partitions to be shared among all modules in a process
	static Partition *partitionList;
	void AddThisToList(void);			// assumes this doesn't have to be removed from a list.. only adds it.
	void RemoveThisFromList(void);
	Partition *fNextInList, *fPrevInList;

	bool BlockIsResource(MemoryBlock* block);
	MemoryBlock* AllocateFromExistingResource(void* mem, size_t size);	// creates a memory block that points to resource memory.

	// Used by VWFC::Memory::VWMemoryLeakChecker
	void CollectStackTrace(MemoryBlock* block);
	void EnableStackTraceInfo(bool enable);
#if MEMORY_BLOCK_STACKTRACE_HISTORY
	void CollectStackTraceHistory(MemoryBlock* block, size_t size);
#endif
	void SetDestructor(const void* mem, void(*inDestructorMethodPtr)(const void*));
	void CallDestructor(const void* mem);
	void ClearDestructor(const void* mem);
	void SetInstantiatedState(const void* mem, bool state = true);
	bool GetInstantiatedState(const void* mem);

	MemoryBlock* GetVerifiedBlockForPointer(const void* mem);	// return nonnull if the memory belongs to use. This is fairly expensive.

public:
	Partition();
	~Partition();

	// Retrieve the Partition with given ID. Potentially creating if necessary.
	static Partition *GetPartitionByIdentifier(char *identifier, bool createIfNotFound);
	static Partition *GetPartitionListHead(void);
	static void		  FreeAllPartitions(void);

	void SetIdentifier(char *newIdentifier);
	void GetIdentifier(char *buffer);	// Note that buffer must be at least PARTITION_IDENTIFIER_BUFFER_SIZE.

	Uint32 GetFlags(void) {return fFlags;}
	void SetFlags(Uint32 newFlags) {fFlags = newFlags;}

	Handle  GetCurrentPool(void) {return fPool;}
	void	SetCurrentPool(Handle poolHandle);		// set the current pool.

	// These functions are new in VWMM and provide generic memory operations. The QT replacements below will call these.
	void* Allocate(size_t size);	// basic allocation of memory block
	void Deallocate(void* mem);		// this must be called to free up the block created by Allocate.

	void* TXStringAllocate(size_t size);	// For TXString
	void TXStringDeallocate(void* pointer);		// For TXString

	void* GetHandle(void* mem);						// given memory allocated by this library, return a handle.
	void* GetVerifiedHandle(void* mem);				// slow, GetHandle plus verifies it's allocated by this library.
	size_t GetVWMMHandleSize(void* handlein);				// given a handle, return its size

	size_t GetVWMMHandleMaxSize(void* handlein);			// give a handle, return its max mem size (this is the actual allocated bytes not the handle size)

	bool PointerBelongsToUs(const void* mem, bool forceBlockCheck = false);						// return true if the memory beloings to use. This is fairly expensive.
	bool HandleBelongsToUs(void* handle);
	bool PointerIsValid(void* mem, bool checkForOwnage, bool forceBlockCheck = false);	// return true if the pointer is valid
	bool HandleIsValid(void* handle, bool checkForOwnage);	// return true if the handle is valid

	bool Resize(void* handle, size_t  size,
				std::function<void(void* oldMem, size_t oldSize, void* newMem, size_t newSize)> copyCallback = nullptr);
															// given a handle allocated by us, resize the memory
	void* DuplicateHandle(void* handlein);					// duplicate the passed handle.

	void* GetUserData(void* handlein);						// return the value of user data stored in the memory block header.
	void SetUserData(void* data, void* handlein);			// set the value of user data stored in the memory block header.

	// Functions dealing with Mac Resource handles
	// Note that if this can find an existing resource with the same qtHandle stored in it, it will just return that one similar to how Mac Resources do
	Handle GetOrCreateHandleFromQTResourceHandle(void** qtHandle, size_t size, short homeFileRef);
	void DeallocateResource(void* handlein);						// blocks allocated from AllocateFromExistingResource shoudl be deallocated with this call
	
	Handle FindBlockWithQTResourceHandle(void** qtHandle, short homeFileRef);	// attempt to find a block with the given handle
	Handle GetOriginalQTResource(void* handlein);			// return the QT resource handle if possible
	void SetQTResourcePtr(void* handlein, void** qtHandle, short homeFileRef);

	static void VWMM_Assert(bool condition, const char* reason);	// defined here so we can enable them in release mode if desired.

	static void *MemMem(const void *haystack, size_t hlen, const void *needle, size_t nlen);
	bool InsertData(void* handle, size_t offset, void* data, size_t dataSize);

	template <typename VICO>
	Handle NewInstantiatedClassHandle()
	{
		Handle newHandle = NewHandleClear(sizeof(VICO));

		if (newHandle)
		{
			new (*newHandle) VICO;

			SetInstantiatedState(*newHandle, true);

			// Store class destructor.
			SetDestructor(*newHandle, [](const void* x) { static_cast<const VICO*>(x)->~VICO(); });
		}

		return newHandle;
	}

	// STOP: THIS IS A TEMPORARY FUNCTION THAT WILL BE REMOVED IN THE NEAR FUTURE.
	// DO NOT CREATE NEW CALLS TO NewInstantiatedClassHandle_UsingExistingHandle. T01936_Revisit.
	template <typename VICO>
	bool NewInstantiatedClassHandle_UsingExistingHandle(Handle existingHandle)
	{
		bool success = false;

		if (existingHandle && *existingHandle)
		{
			SetInstantiatedState(*existingHandle, false);
			CallDestructor(*existingHandle);
			ClearDestructor(*existingHandle);
			
			SetHandleSize(existingHandle, sizeof(VICO));

			new (*existingHandle) VICO;

			SetInstantiatedState(*existingHandle, true);

			// Store class destructor.
			SetDestructor(*existingHandle, [](const void* x) { static_cast<const VICO*>(x)->~VICO(); });

			success = true;
		}

		return success;
	}

	// These functions are replacements for calls into QTMM. They have the same signature as the original QT calls, but 
	// call into our local VWMM code instead.
	Handle		NewHandle(GSSize byteCount);
	Handle		NewHandleClear(GSSize byteCount);
	Ptr			NewPtr(GSSize byteCount);
	Ptr			NewPtrClear(GSSize byteCount);
	bool		SetHandleSize(Handle h, GSSize byteCount);
	bool		SetHandleSize(Handle h, GSSize byteCount, std::function<void(void* oldMem, size_t oldSize, void* newMem, size_t newSize)> copyCallback);
	bool		SetPtrSize(Ptr p, GSSize byteCount);
	bool		HandToHand(Handle &h);
	void		PtrToHand(const void *srcPtr, Handle &dstHndl, size_t size);
	bool		PtrToXHand(const void *srcPtr, Handle dstHndl, size_t size);
	bool		HandAndHand(Handle hand1, Handle hand2);
	bool		PtrAndHand(const void *p, Handle h, GSSize byteCount);
	GSSize		GetHandleSize(Handle h);
	GSSize		GetHandleMaxSize(Handle h);
	GSSize		GetPtrSize(Ptr p);
	void		DisposePtr(Ptr p);
	void		DisposeHandle(Handle h);
	bool		IsHandleInUse(Handle h);
	short		MemError(void);									// does nothing for gVWMM pointer. Here so that existing code can switch back to QTMM
	void		HLock(Handle h);	// this exists for backwards compatibility with handle lock/unlock mechanisms
	void		HUnlock(Handle h);	// this exists for backwards compatibility with handle lock/unlock mechanisms
	char		HGetState(Handle h);// this exists for backwards compatibility with handle lock/unlock mechanisms

	void		DeleteAllHandlesWithResourceFile(short resFile);

	// The following methods exist to provide a lock/unlock mechanism for older code that may require valid lock states
	bool		HandleIsLocked_Legacy(Handle h);
	bool		SetHandleLockState_Legacy(Handle h, bool newState);

	// The following functions are helpers to translate between the two memory systems.
	Handle	ConvertFromQTHandleToVWMMHandle(Handle qtHandle);	// given a QT handle return a VWMM handle copy
	Handle	ConvertFromVWMMHandleToQTHandle(Handle qtHandle);	// given a VWMM handle return a QT handle copy

	// Functions for Pooling
	Handle CreatePool(size_t maxBlockSize, size_t numBlocks);	// return a handle representing a VWMM pool with the given parameters, or NULL if we couldn't create one.
	Handle RequestPoolBlock(Handle pool);	// return a handle from the passed in Pool, or NULL. This will not fall back on standard calls if no pool blocks are available.
	void ReleasePoolBlock(Handle pool, Handle block);// release the block (which must be part of pool) back to the pool's pool of free blocks
	void DestroyPool(Handle pool);// delete this pool and all the memory inside it. You should make sure you're not still using any of that memory still.

	// Functions of a debug nature
	void PrintMemoryStats(Uint32 flags);
	static Uint32 GetMemoryBlockHash(MemoryBlock *block);

	// Reference counted and thread safe.
	bool RegisterMemoryCallbackFunction(void (*func)(Sint32, size_t, void*), void* userData);	// returns true if it registered successfully
	bool UnregisterMemoryCallbackFunction(void (*func)(Sint32, size_t, void*));	// returns true if it found it

	// Functions for setting the "oversize" of a block, which controls how much extra space is allocated on multiple resize operations.
	// For example, if you set this to 10000, then if it needs to increase the block size, it will internally make a block 10k bigger than requested.
	// Then for subsequent resizes, as long as the requested size is under maxsize, it won't have to actually allocate anything, it can just set the
	// reported size and return. This improves speed and decreases memory fragmentation.
	Uint32 GetHandleOversize(Handle handle);
	void SetHandleOversize(Handle handle, Uint32 value, bool reset = true);
	
	// The following methods can be used for analysis and probing the current state of memory
	size_t GetBlockCount(void);
	size_t GetAllBlocks(void** buffer, size_t bufferSizeInPtrSize); // returns the count of blocks in buffer. Unused elements will be NULL.
	size_t GetAllBlocks(std::vector<void*>& buffer); // returns the count of blocks in buffer. Unused elements will be NULL.
	void GetBlockStackTrace(void* block, char* outBufferNullTerminated, size_t bufferSizeInChars); // If not collecting stack trace info, this will return an empty string in buffer
	size_t GetBlockSize(void* block);
	bool BlockArrayContainsBlock(void** blockArray, size_t blockArraySize, const void* block); // returns true if the array contains the given block.
	bool BlockArrayContainsBlock(const std::vector<void*>& blockArray, const void* block); // returns true if the array contains the given block.
	// Performs a subtraction of right from left and puts result in result array. returns the element count in the result array.
	// Unused elements in each array should be set to NULL, and will be ignored.
	size_t SubtractBlockArrays(void** leftArray, size_t leftArraySize, void** rightArray, size_t rightArraySize, void** resultArray, size_t resultArraySize);
	size_t SubtractBlockArrays(const std::vector<void*>& leftArray, const std::vector<void*>& rightArray, std::vector<void*>& resultArray);
	
	
	//out of memory conditions.
	enum
	{
		VWMM_CALLBACK_ALLOCATE_FAILED = 1,
	};

	friend class VWFC::Memory::VWMemoryLeakChecker;

};	// class Partition

#ifndef _WINDOWS
	// Declare Mac calls for thread safety
	void EnterCriticalSection(os_unfair_lock_t id);
	void LeaveCriticalSection(os_unfair_lock_t id);

#ifndef OutputDebugString
	void OutputDebugStringA(const char *str);
#endif
#endif // _WINDOWS
	
}	// namespace VWMM


// -------------------------------------------------------------------------------------------------
// These functions are direct calls into QuickTime - use only when necessary, for example, when they
// need to be passed back into other areas of Quicktime that expect native handles.
// -------------------------------------------------------------------------------------------------
namespace QTMM
{
	MM_DLL_EXPORT Handle	NewHandle(Size byteCount);
	MM_DLL_EXPORT Handle	NewHandleClear(Size byteCount);
	MM_DLL_EXPORT Ptr		NewPtr(Size byteCount);
	MM_DLL_EXPORT Ptr		NewPtrClear(Size byteCount);
	MM_DLL_EXPORT void		SetHandleSize(Handle h, Size byteCount);
	MM_DLL_EXPORT void		SetPtrSize(Ptr p, Size byteCount);
	MM_DLL_EXPORT OSErr		HandToHand(Handle *h);
	MM_DLL_EXPORT OSErr		PtrToHand(const void *srcPtr, Handle *dstHndl, size_t size);
	MM_DLL_EXPORT OSErr		PtrToXHand(const void *srcPtr, Handle dstHndl, size_t size);
	MM_DLL_EXPORT OSErr		HandAndHand(Handle hand1, Handle hand2);
	MM_DLL_EXPORT OSErr		PtrAndHand(const void *p, Handle h, Size byteCount);
	MM_DLL_EXPORT Size		GetHandleSize(Handle h);
	MM_DLL_EXPORT void		DisposePtr(Ptr p);
	MM_DLL_EXPORT void		DisposeHandle(Handle h);
	MM_DLL_EXPORT OSErr		MemError(void);
	MM_DLL_EXPORT void		HLock(Handle h);
	MM_DLL_EXPORT void		HUnlock(Handle h);
	MM_DLL_EXPORT char		HGetState(Handle h);
	MM_DLL_EXPORT bool		InsertData(Handle handle, size_t offset, void* data, size_t dataSize);
	
	

} // namespace QTMM



#endif /* _VWMM_H_ */
