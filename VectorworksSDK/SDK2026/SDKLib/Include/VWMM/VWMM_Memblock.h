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
	
	~MemoryBlock() 
	{ 
		if (stackTraceAddr)
			delete stackTraceAddr;
	}

	void* mem = nullptr;					// points to the memory similar to a handle
	unsigned short listIndex = 0;	// index of the list inside the partition
	MemoryBlock* next = nullptr;			// doubly linked list
	MemoryBlock* prev = nullptr;
	size_t memSize = 0;				// size of the mem (not including the MemoryBlock structure itself)
	size_t maxMemSize = 0;			// maximum size of the mem
	unsigned short flags = 0;
	Uint32 oversize = 0;	// when resized, it maxsize will be this much over requested size to lower fragmentation and overhead of multiple resizing.
	void* pool = nullptr;					// if this belongs to a pool, the pointer is saved here. If not, this will be NULL.
	void** originalQTResource = nullptr;	// If this is a resource, this stores a pointer to the resource info.
	short QTResourceHomeFile = 0;	// this has to be stored for resources in the case of CloseResFile() being called.
	std::vector<void*>* stackTraceAddr = nullptr;	//For use with stacktrace collection only, NULL in production code
	bool legacyLocked = false;			// stores lock/unlock state (but does nothing)
	void *userData = nullptr;				// for the user to use.
	bool isInstantiatedObject = false;	// true if memory was instantiated via the placement new operator/NewInstantiatedClassHandle; false otherwise.
	void(*destructorMethodPtr)(const void*) = nullptr; // a pointer to an instatiated object's destructor method, which is called prior to handle disposal.
	Uint32 fBlockMagicNumber = 0;
	
#if MEMORY_BLOCK_DEBUGGING
	Uint32 magicNumberPad = 0;
#endif // MEMORY_BLOCK_DEBUGGING
	// ---- below is the relocatable part ---
	MemoryBlock* parentBlock = nullptr;	// points back up to the block. When a block becomes disconnected, this is how we get back to the block from the separated memory.
	// after the above there will be the actual memory that the user requested.
	// unsigned char mem[...];


	// Methods...

	// given *this, return the memory.
	void *GetMem(void) const
	{
		return mem;
	}

	// given the mem, back up slightly to retrieve the pointer to the block
	static MemoryBlock* GetBlockPtrFromMem(const void *mem)
	{
		MemoryBlock *result = *((MemoryBlock **) (((unsigned char *) mem) - sizeof(void *)));
		return result;
	}

	// Given memory (must be allocated here), return the parent memory block.
	static MemoryBlock* GetBlock(const void *mem)
	{
		// We have to reference memory before what the user thinks the start of the block is...
		MemoryBlock *parentBlock = (MemoryBlock *) GetBlockPtrFromMem(mem);
		return parentBlock;
	}
};
} // namespace VWMM

