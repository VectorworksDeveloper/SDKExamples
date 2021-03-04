//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//  This file contains generic byte-swapping routines. 
//	It is part of the SDK, and does not include platform-specific data types.


#pragma once

#include "GSDebug.h"

template<class _T> inline void GSByteSwap(_T& data)
{
	if ((std::numeric_limits<_T>::is_integer) &&
	   (((sizeof(_T) == sizeof(uint64_t)) ||	// is x64 working right?
		 (sizeof(_T) == sizeof(uint32_t)) ||
		 (sizeof(_T) == sizeof(uint16_t)) ||
		 (sizeof(_T) == sizeof(uint8_t)))))
	{
		union
		{	
			_T	theLong;
			char theBytes[ sizeof(_T) ];
		} src, dst;

		src.theLong = data;
		for (size_t i=0, j=(sizeof(_T)-1); i < sizeof(_T); ++i, --j)
		{
			dst.theBytes[ i ] = src.theBytes[ j ];
		}
		data = dst.theLong;
	}
	else
	{
		DSTOP((kEveryone, "GSByteSwap of a bad type!  Add a new template specialization"));
	}
}

template<> inline void GSByteSwap(Real64& data)
{
	union
	{	
		double	theDouble;
		char	theBytes[ sizeof(double) ];
	} src, dst;

	src.theDouble = data;
	dst.theBytes[ 0 ] = src.theBytes[ 7 ];
	dst.theBytes[ 1 ] = src.theBytes[ 6 ];
	dst.theBytes[ 2 ] = src.theBytes[ 5 ];
	dst.theBytes[ 3 ] = src.theBytes[ 4 ];
	dst.theBytes[ 4 ] = src.theBytes[ 3 ];
	dst.theBytes[ 5 ] = src.theBytes[ 2 ];
	dst.theBytes[ 6 ] = src.theBytes[ 1 ];
	dst.theBytes[ 7 ] = src.theBytes[ 0 ];
	data = dst.theDouble;
}

