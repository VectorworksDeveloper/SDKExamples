//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once



// for ByteSwap conversion direction parameter
enum EByteSwapDirection {
	kReading,
	kWriting
};




inline void ByteSwapDouble(double *pld)
{
	char t;
	char *pb1 = (char *) pld;
	char *pb2 = pb1 + sizeof(Real64) - 1;
	while (pb2 > pb1) {
		t = *pb1;
		*pb1 = *pb2;
		*pb2 = t;
		++pb1;
		--pb2;
	}
}



inline void ByteSwapFloat(float *pf)
{
	char t;
	char *pb1 = (char *) pf;
	char *pb2 = pb1 + sizeof(float) - 1;
	while (pb2 > pb1) {
		t = *pb1;
		*pb1 = *pb2;
		*pb2 = t;
		++pb1;
		--pb2;
	}
}

inline void ByteSwapUint64(Uint64 *pld)
{
	char t;
	char *pb1 = (char *) pld;
	char *pb2 = pb1 + sizeof(Uint64) - 1;
	while (pb2 > pb1) {
		t = *pb1;
		*pb1 = *pb2;
		*pb2 = t;
		++pb1;
		--pb2;
	}
}

inline void ByteSwapUint32(Uint32 *pld)
{
	char t;
	char *pb1 = (char *) pld;
	char *pb2 = pb1 + sizeof(Uint32) - 1;
	while (pb2 > pb1) {
		t = *pb1;
		*pb1 = *pb2;
		*pb2 = t;
		++pb1;
		--pb2;
	}
}

inline void ByteSwapLONG(Sint32 *pl)
{
	char t;
	char* p1 = (char*)pl;
	char* p2 = p1 + 3;

	t = *p1;
	*p1 = *p2;
	*p2 = t;

	++p1; --p2;

	t = *p1;
	*p1 = *p2;
	*p2 = t;
}

#if GS_MAC && GS_PLATFORM32
//X64PRJ_REVISIT Hugues // QTREMOVAL
inline void ByteSwapLONG(long *pl)
{
    ByteSwapLONG((Sint32 *)pl);
}
#endif


inline void ByteSwapSHORT(Sint16 *ps)
{
	char *p1 = (char*)ps;
	char *p2 = p1 + 1;
	char t = *p1;
	*p1 = *p2;
	*p2 = t;
}

inline void ByteSwapDWORD(Uint32 *pl)
{
    ByteSwapLONG((Sint32 *)pl);
}

#if GS_MAC && GS_PLATFORM32
//X64PRJ_REVISIT Hugues // QTREMOVAL
inline void ByteSwapDWORD(unsigned long *pl)
{
    ByteSwapLONG((Sint32 *)pl);
}
#endif

inline void ByteSwapWORD(Uint16 *ps)
{
    ByteSwapSHORT((Sint16 *)ps);
}
	
inline Uint32 TruncatePointer(const void* ptr)
{
    return (Uint32)((UintptrT)ptr); //-V202
}

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

