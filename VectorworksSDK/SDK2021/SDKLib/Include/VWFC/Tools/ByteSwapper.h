//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		// swap the bytes in 'value'
		template<class T> T SwapBytes(const T& value)
		{
			T		res		= value;

			size_t	len		= sizeof(T);
			char*	buffer	= (char*) & res;
			for(size_t i=0; i<len/2; i++) {
				char	temp	= buffer[i];
				buffer[i]		= buffer[len-i-1];
				buffer[len-i-1]	= temp;
			}

			return res;
		}

		// swap the butes in 'value' when compiled on Mac only
		template<class T> T SwapBytesForBigEndian(const T& value)
		{
#if GS_LITTLE_ENDIAN
			return value;
#else
			return SwapBytes( value );
#endif
		}

		// swap the content of two variables
		// using operator== of <class T>
		template<class T> void SwapVariables(T& a, T& b)
		{
			T	temp	= a;
			a			= b;
			b			= temp;
		}
	}
}