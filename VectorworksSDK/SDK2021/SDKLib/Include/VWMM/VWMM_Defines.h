//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	This file contains definitions that support VWMM and allow configuration of
//	its behavior.

#pragma once

// -------------------------------------------------------------------------------------------------
// Configurable Defines
// -------------------------------------------------------------------------------------------------
// Some meta defines that will set various configurations
#define _DEBUG_SPEED (1)		// set to 1 if you want this to be a debug build without any instrumentation
//#define _DEBUG_FULLCHECKS (1) // set to 1 if you want a debug build with full checking even with all functions
//#define _DEBUG_LIGHTCHECKS (1) // set to 1 if you want checking of "important" functions but not common ones like GetHandleSize, Lock/Unlock
#ifdef _DEBUG


#ifdef _DEBUG_SPEED
#define MEMORY_OUTPUT_STATS (0)
#define MEMORY_BLOCK_DEBUGGING (0)
#define MEMORY_BLOCK_CHECK_GETHANDLESIZE (0)	// GetHandleSize has its own special check since it is called so much
#define MEMORY_BLOCK_CHECK_LOCKING (0)			// set to 1 if you want to check lock/unlock calls for proper handles
#define MEMORY_BLOCK_QTMM_HANDLE_CHECKS (0)		// set to 1 if you want to check that QTMM calls are not passed VWMM handles
#define MEMORY_BLOCK_LARGEALLOC_CHECKS (0)		// Check for allocs greater than MEMORY_BLOCK_LARGEST_EXPECTED_ALLOC_SIZE
#define MEMORY_BLOCK_STACKTRACE_HISTORY (0)		// set to 1 if you want to save a stack trace history over time for each alloc
#define MEMORY_BLOCK_STACKTRACE_FRAME_COUNT_LIMIT (59) // how deep of a stack to record
#define MEMORY_BLOCK_STACKTRACE_DISPLAY_COUNT (6) // display this many of the highest frequency calls
#define VWMM_RELEASE_ASSERTS (0)				// turn this on to show assert dialogs in release mode
#define MEMORY_BLOCK_CLEAR_FREED_MEMORY (0)		// set this to true to clear out freed memory.

#elif _DEBUG_FULLCHECKS
#define MEMORY_OUTPUT_STATS (0)
#define MEMORY_BLOCK_DEBUGGING (1)
#define MEMORY_BLOCK_CHECK_GETHANDLESIZE (1)	// GetHandleSize has its own special check since it is called so much
#define MEMORY_BLOCK_CHECK_LOCKING (1)			// set to 1 if you want to check lock/unlock calls for proper handles
#define MEMORY_BLOCK_LARGEALLOC_CHECKS (1)		// Check for allocs greater than MEMORY_BLOCK_LARGEST_EXPECTED_ALLOC_SIZE
#define MEMORY_BLOCK_QTMM_HANDLE_CHECKS (1)		// set to 1 if you want to check that QTMM calls are not passed VWMM handles
#define MEMORY_BLOCK_STACKTRACE_HISTORY (0)		// set to 1 if you want to save a stack trace history over time for each alloc
#define MEMORY_BLOCK_STACKTRACE_FRAME_COUNT_LIMIT (59) // how deep of a stack to record
#define MEMORY_BLOCK_STACKTRACE_DISPLAY_COUNT (6) // display this many of the highest frequency calls
#define VWMM_RELEASE_ASSERTS (0)				// turn this on to show assert dialogs in release mode
#define MEMORY_BLOCK_CLEAR_FREED_MEMORY (1)		// set this to true to clear out freed memory.

#elif _DEBUG_LIGHTCHECKS
#define MEMORY_OUTPUT_STATS (0)
#define MEMORY_BLOCK_DEBUGGING (1)
#define MEMORY_BLOCK_CHECK_GETHANDLESIZE (0)	// GetHandleSize has its own special check since it is called so much
#define MEMORY_BLOCK_CHECK_LOCKING (0)			// set to 1 if you want to check lock/unlock calls for proper handles
#define MEMORY_BLOCK_LARGEALLOC_CHECKS (1)		// Check for allocs greater than MEMORY_BLOCK_LARGEST_EXPECTED_ALLOC_SIZE
#define MEMORY_BLOCK_QTMM_HANDLE_CHECKS (1)		// set to 1 if you want to check that QTMM calls are not passed VWMM handles
#define MEMORY_BLOCK_STACKTRACE_HISTORY (0)		// set to 1 if you want to save a stack trace history over time for each alloc
#define MEMORY_BLOCK_STACKTRACE_FRAME_COUNT_LIMIT (59) // how deep of a stack to record
#define MEMORY_BLOCK_STACKTRACE_DISPLAY_COUNT (6) // display this many of the highest frequency calls
#define VWMM_RELEASE_ASSERTS (0)				// turn this on to show assert dialogs in release mode
#define MEMORY_BLOCK_CLEAR_FREED_MEMORY (0)		// set this to true to clear out freed memory.

#else // not _DEBUG_SPEED
#define MEMORY_OUTPUT_STATS (1)
#define MEMORY_BLOCK_DEBUGGING (1)
#define MEMORY_BLOCK_CHECK_GETHANDLESIZE (1)	// GetHandleSize has its own special check since it is called so much
#define MEMORY_BLOCK_CHECK_LOCKING (1)			// set to 1 if you want to check lock/unlock calls for proper handles
#define MEMORY_BLOCK_LARGEALLOC_CHECKS (1)		// Check for allocs greater than MEMORY_BLOCK_LARGEST_EXPECTED_ALLOC_SIZE
#define MEMORY_BLOCK_QTMM_HANDLE_CHECKS (1)		// set to 1 if you want to check that QTMM calls are not passed VWMM handles
#define MEMORY_BLOCK_STACKTRACE_HISTORY (1) // set to 1 if you want to save a stack trace history over time for each alloc
#define MEMORY_BLOCK_STACKTRACE_FRAME_COUNT_LIMIT (59) // how deep of a stack to record
#define MEMORY_BLOCK_STACKTRACE_DISPLAY_COUNT (12) // display this many of the highest frequency calls
#define VWMM_RELEASE_ASSERTS (0)				// turn this on to show assert dialogs in release mode
#define MEMORY_BLOCK_CLEAR_FREED_MEMORY (1)		// set this to true to clear out freed memory.
#endif

#else	// release
#define MEMORY_OUTPUT_STATS (0)
#define MEMORY_BLOCK_DEBUGGING (0)
#define MEMORY_BLOCK_CHECK_GETHANDLESIZE (0)	// GetHandleSize has its own special check since it is called so much
#define MEMORY_BLOCK_CHECK_LOCKING (0)			// set to 1 if you want to check lock/unlock calls for proper handles
#define MEMORY_BLOCK_LARGEALLOC_CHECKS (0)		// Check for allocs greater than MEMORY_BLOCK_LARGEST_EXPECTED_ALLOC_SIZE
#define MEMORY_BLOCK_QTMM_HANDLE_CHECKS (0)		// set to 1 if you want to check that QTMM calls are not passed VWMM handles
#define MEMORY_BLOCK_STACKTRACE_HISTORY (0) // set to 1 if you want to save a stack trace history over time for each alloc
#define MEMORY_BLOCK_STACKTRACE_FRAME_COUNT_LIMIT (59) // how deep of a stack to record
#define MEMORY_BLOCK_STACKTRACE_DISPLAY_COUNT (6) // display this many of the highest frequency calls
#define VWMM_RELEASE_ASSERTS (0)				// turn this on to show assert dialogs in release mode
#define MEMORY_BLOCK_CLEAR_FREED_MEMORY (0)		// set this to true to clear out freed memory.
#endif	// _DEBUG


// The following are various configurable, but seldom changed values
#define MEMORYBLOCK_SEPERATE_THRESHHOLD (5000)	// above this value, blocks will be allocated as disconnected so that they can be resized
#define MEMORYBLOCK_RESIZE_FREE_THRESHHOLD (5000U)	// resizes that decrease size by this or more will attempt to free up the memory instead of just setting the shown size smaller
#define NUM_ALLOCSIZE_SLOTS (13)
#define MEMORYBLOCK_HASH_BITS (10)	// There will be 2^MEMORYBLOCK_HASH_BITS buckets for hashing memory blocks into lists (1024 currently)
#define MEMORYBLOCK_HASH_SIZE (1 << MEMORYBLOCK_HASH_BITS) // absolute size.
#define MEMORYBLOCK_REALLOC_OVERSIZE (16)	// when a block needs to be resized, it is oversized by this amount to speed up the next resize
#define MEMORY_BLOCK_LARGEST_EXPECTED_ALLOC_SIZE (50000000) // 50 MB. This flag is for debug purposes. It's possible something will be bigger, but not very probable.
#define MEMORY_BLOCK_CLEAR_VALUE (0)	// value used when memory is cleared as a result of MEMORY_BLOCK_CLEAR_FREED_MEMORY

enum
{
	// set if the block has been resized bigger - this causes the structure to change from a single block to a block with a pointer at the end.
	MEMORYBLOCK_FLAG_DISCONNECTED_DATA = 1,	

	// set if this memory block is part of a Pool. If it is, the "pool" variable will be set too. This flag provides an extra layer of sanity checking.
	MEMORYBLOCK_FLAG_POOL = 2,
	
	// set if this memory block comes from a QT resource.
	MEMORYBLOCK_FLAG_RESOURCE = 4,
};

// ----- Here is a good place if you want to turn on flags one at a time, overriding the above blocks
// ----- End of flag overrides

#define MEMSTAT_AVERAGES (1)
#define STACKTRACE_HISTORY (2)

