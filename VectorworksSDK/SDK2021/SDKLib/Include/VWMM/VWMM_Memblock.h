//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	This file contains the memory block structure used for VWMM memory blocks

#pragma once
#include <vector>

namespace VWMM {

struct MemoryBlock
{
	const static Uint32 kBlockMagicNumberPool		= 0xFACEFEED;
	const static Uint32 kBlockMagicNumberNonPool	= 0xA4FEB3AF;
	
    MemoryBlock() {
        mem = nullptr;
        next = nullptr;
        prev = nullptr;
        pool = nullptr;
        originalQTResource = nullptr;
        stackTraceAddr = nullptr;
        userData = nullptr;
        parentBlock = nullptr;
		isInstantiatedObject = false;
		destructorMethodPtr = nullptr;
		fBlockMagicNumber = 0;
#if MEMORY_BLOCK_DEBUGGING
		magicNumberPad = 0;
#endif
    }
    
	~MemoryBlock() 
	{ 
		if (stackTraceAddr)
			delete stackTraceAddr;
	}

	void* mem;					// points to the memory similar to a handle
	unsigned short listIndex;	// index of the list inside the partition
	MemoryBlock* next;			// doubly linked list
	MemoryBlock* prev;
	size_t memSize;				// size of the mem (not including the MemoryBlock structure itself)
	size_t maxMemSize;			// maximum size of the mem
	unsigned short flags;
	Uint32 oversize;	// when resized, it maxsize will be this much over requested size to lower fragmentation and overhead of multiple resizing.
	void* pool;					// if this belongs to a pool, the pointer is saved here. If not, this will be NULL.
	void** originalQTResource;	// If this is a resource, this stores a pointer to the resource info.
	short QTResourceHomeFile;	// this has to be stored for resources in the case of CloseResFile() being called.
	std::vector<void*>* stackTraceAddr;	//For use with stacktrace collection only, NULL in production code
	bool legacyLocked;			// stores lock/unlock state (but does nothing)
	void *userData;				// for the user to use.
	bool isInstantiatedObject;	// true if memory was instantiated via the placement new operator/NewInstantiatedClassHandle; false otherwise.
	void(*destructorMethodPtr)(const void*); // a pointer to an instatiated object's destructor method, which is called prior to handle disposal.
	Uint32 fBlockMagicNumber;
	
#if MEMORY_BLOCK_DEBUGGING
	Uint32 magicNumberPad;
#endif // MEMORY_BLOCK_DEBUGGING
	// ---- below is the relocatable part ---
	MemoryBlock* parentBlock;	// points back up to the block. When a block becomes disconnected, this is how we get back to the block from the separated memory.
	// after the above there will be the actual memory that the user requested.
	// unsigned char mem[...];


	// Methods...

	// given *this, return the memory.
	void *GetMem(void)
	{
		return mem;
	}

	// given the mem, back up slightly to retrieve the pointer to the block
	static MemoryBlock* GetBlockPtrFromMem(void *mem)
	{
		MemoryBlock *result = *((MemoryBlock **) (((unsigned char *) mem) - sizeof(void *)));
		return result;
	}

	// Given memory (must be allocated here), return the parent memory block.
	static MemoryBlock* GetBlock(void *mem)
	{
		// We have to reference memory before what the user thinks the start of the block is...
		MemoryBlock *parentBlock = (MemoryBlock *) GetBlockPtrFromMem(mem);
		return parentBlock;
	}
};
} // namespace VWMM

