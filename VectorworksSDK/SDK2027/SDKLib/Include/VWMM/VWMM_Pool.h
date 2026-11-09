//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// This file contains code to handle the automatic and explicit pooling system.

#pragma once


namespace VWMM
{

// This structure is used to store information about free and used memory blocks.
struct BlockUse
{
	size_t blockIndex;			// index of this block
	bool inUse;					// true if it's in use, false otherwise. Used to prevent problems with double deallocates.
	struct BlockUse* prev;		// prev in list
	struct BlockUse* next;		// next in list
};

// This structure contains everything required to handle a memory pool
struct Pool
{
	size_t maxBlockSize;
	size_t numBlocks;
	size_t actualBlockSize;	// because blocks may be padded
	size_t numFreeBlocks;	// count of free blocks
	struct BlockUse* freeBlocks;	// head of free block list
	struct BlockUse* usedBlocks;	// head of used block list

	void *blockUseStart;	// quick lookup to start of blockUse array
	void *blockStart;		// quick lookup to start of actual blocks
	// Note, after this, comes an array of block use structures, one for each of numBlocks
	// AFter that comes an array of memory blocks allocated to maxBlockSize, one for each of numBlocks
};


}	// namespace VWMM