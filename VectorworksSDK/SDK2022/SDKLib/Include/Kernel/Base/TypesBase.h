//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include <stdint.h>
#include <typeinfo>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <limits>
#include <functional>

#define _GS_TYPES_

///////////////////////////////////////////////////////////////////////////////
// Fixed-width unsigned integer types.

typedef uint8_t		Uint8;
typedef	uint16_t	Uint16;
typedef	uint32_t	Uint32;
typedef uint64_t	Uint64;


///////////////////////////////////////////////////////////////////////////////
// Fixed-width signed integer types.

typedef char		Sint8;	
typedef	int16_t		Sint16;
typedef	int32_t		Sint32;
typedef int64_t		Sint64;


///////////////////////////////////////////////////////////////////////////////
// Interger type maximums and minimums.

#define kGSMaxUint8		255
#define kGSMaxUint16	65535
#define kGSMaxUint32	4294967295UL
#define kGSMaxUint64	18446744073709551615ULL
#define kGSMaxSint8		127
#define kGSMaxSint16	32767
#define kGSMaxSint32	2147483647L
#define kGSMaxSint64	9223372036854775807LL

#define kGSMinUint8		0
#define kGSMinUint16	0
#define kGSMinUint32	0UL
#define kGSMinUint64	0ULL
#define kGSMinSint8		(-128)
#define kGSMinSint16	(-32768)
#define kGSMinSint32	(-2147483647-1)
#define kGSMinSint64	(-9223372036854775808LL)


///////////////////////////////////////////////////////////////////////////////
// Boolean types.

typedef	unsigned char	Bool8;

#if __cplusplus
	const Bool8		kFalse = 0;
	const Bool8		kTrue = 1;
#else
	enum EBool {
		kFalse = 0,
		kTrue = 1
	};
#endif

///////////////////////////////////////////////////////////////////////////////
// Integer pointer types. (guaranteed to have the same size as a pointer regardless of the platform.)
typedef intptr_t	SintptrT;
typedef uintptr_t	UintptrT;

typedef size_t		GSSize;


///////////////////////////////////////////////////////////////
// XXXKIS : Put this type definition back in temporarily until
//			I find out why it was removed to being with.
typedef unsigned char	Boolean;


///////////////////////////////////////////////////////////////////////////////
// Floating point types.

typedef	float			Real32;
typedef double			Real64;

// Limits of double that, when converted to float, will be precise to the
// first digit to the left of the decimal (zero decimal places).
#define kGSMaxPreciseFloat 16777215
#define kGSMinPreciseFloat (-16777215)

#ifndef CGFLOAT_EPSILON
	#if CGFLOAT_IS_DOUBLE
		#define CGFLOAT_EPSILON DBL_EPSILON
	#else
		#define CGFLOAT_EPSILON FLT_EPSILON
	#endif
#endif



///////////////////////////////////////////////////////////////////////////////
// Character types.

// Non-Unicode
typedef unsigned char	Uchar;

// Unicode (Encoding format is UTF-16 in platform-native byte order)
typedef Uint16			UCChar;
typedef UCChar*			UCCharPtr;       // Pointer to one or an array of UCCChars
typedef UCChar**		UCCharHandle;    // Handle to one or an array of UCCChars
typedef UCChar*			UCStrPtr;        // Pointer to NULL-word terminated UCChars
typedef UCChar**		UCStrHandle;     // Handle to NULL-word terminated UCChars
typedef const UCChar*	ConstUCCharPtr;  // Pointer to one or an array of constant UCCChars
typedef const UCChar*	ConstUCStrPtr;   // Pointer to NULL-word terminated constant UCChars
typedef Uint32			UCCharCnt;


///////////////////////////////////////////////////////////////////////////////
// String types.
//   Non-Unicode base types used by our cross-platform string code

// Pascal string types
typedef Uchar			GSStr255[256], GSStr63[64], GSStr32[33], GSStr31[32], GSStr27[28], GSStr15[16];
typedef Uchar			*GSStringPtr, **GSStringHandle;
typedef const Uchar		*ConstGSStringPtr, *ConstGSStr255Param, *ConstGSStr31Param, *ConstGSStr15Param;

// C string types
typedef char			*GSCStrPtr;			// C-String Pointer
typedef const char		*ConstGSCStrPtr;	// Constant C-String Pointer

#if GS_WIN

/********************************************************************************

    String Types
    
        UniChar                 A single 16-bit Unicode character
        UniCharCount            A count of Unicode characters in an array or buffer

        StrNNN                  Pascal string holding up to NNN bytes
        StringPtr               Pointer to a pascal string
        StringHandle            Pointer to a StringPtr
        ConstStringPtr          Pointer to a read-only pascal string
        ConstStrNNNParam        For function parameters only - means string is const
        
        CStringPtr              Pointer to a C string           (in C:  char*)
        ConstCStringPtr         Pointer to a read-only C string (in C:  const char*)
        
    Note: The length of a pascal string is stored as the first byte.
          A pascal string does not have a termination byte.
          A pascal string can hold at most 255 bytes of data.
          The first character in a pascal string is offset one byte from the start of the string. 
          
          A C string is terminated with a byte of value zero.  
          A C string has no length limitation.
          The first character in a C string is the zeroth byte of the string. 
          
        
*********************************************************************************/
typedef Uint16                          UniChar;
typedef UniChar *                       UniCharPtr;
typedef Uint32                          UniCharCount;
typedef UniCharCount *                  UniCharCountPtr;
typedef unsigned char                   Str255[256];
typedef unsigned char                   Str63[64];
typedef unsigned char                   Str32[33];
typedef unsigned char                   Str31[32];
typedef unsigned char                   Str27[28];


typedef unsigned char *                 StringPtr;
typedef StringPtr *                     StringHandle;
typedef const unsigned char *           ConstStringPtr;
typedef const unsigned char *           ConstStr255Param;


inline unsigned char StrLength(ConstStr255Param string) { return (*string); }

#else

#define _hypot hypot
#define _stricmp stricmp
#define _strcmpi strcmpi
#define _strcmp strcmp
#define _strnicmp strnicmp

#endif // GS_WIN

///////////////////////////////////////////////////////////////////////////////
// --- Sets

typedef Uint32 Set32;
typedef unsigned short Set16;
typedef unsigned char Set8;

Bool8 _setmember(Sint32 c, ...);

template<typename T1, typename T2>
inline bool setmember(T1 x, T2 y)
{
	return x == y;
}

// June/2020 - BZarev: use variadic template
template<typename T1, typename T2, typename... Args>
inline bool setmember(T1 x, T2 head, Args... tail)
{
	return x == head || setmember(x, tail...);
}

///////////////////////////////////////////////////////////////////////////////

#if GS_MAC 

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

// nonstandard types on mac
#define PRIpPTR		"p"		// p is already prefixed with 0x
#define SCNpPTR		"p"

#else 

// Visual Studio 2013 will include C99 support
#if (_MSC_VER >= 1800)

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#else

// this is a small subset of the specifiers, for now just add what we need
#define PRId32       "I32d"
#define PRIi32       "I32i"
#define PRIo32       "I32o"
#define PRIu32       "I32u"
#define PRIx32       "I32x"
#define PRIX32       "I32X"

#define PRId64       "I64d"
#define PRIi64       "I64i"
#define PRIo64       "I64o"
#define PRIu64       "I64u"
#define PRIx64       "I64x"
#define PRIX64       "I64X"

#define PRIdPTR     "Id"
#define PRIiPTR     "Ii"
#define PRIoPTR     "Io"
#define PRIuPTR     "Iu"
#define PRIxPTR     "Ix"
#define PRIXPTR     "IX"

#ifdef _WIN64 // [
#  define SCNdPTR     "I64d"
#  define SCNiPTR     "I64i"
#  define SCNxPTR     "I64x"
#else  // _WIN64 ][
#  define SCNdPTR     "ld"
#  define SCNiPTR     "li"
#  define SCNxPTR     "lx"
#endif  // _WIN64 ]

#endif

// nonstandard types on win
#define PRIpPTR		"#p"	// p has no prefix. #p is 0X but no prefix if null. x doesn't pad and has identical problems to p
#define SCNpPTR		SCNxPTR

#endif

/* for portability, different ways of expressing a char w/ all 1's */
#if _WINDOWS
	#define CHAR0xFF	('\xFF')
#else
	#define CHAR0xFF	(0xFF)
#endif

///////////////////////////////////////////////////////////////////////////////
// GSHandle
//   This is the basic resizable handle structure with cross-platform support
//   from the MiniCAD SDK. SDK memory calls can also be used on MCObjectHandle.

typedef char**	GSHandle;


///////////////////////////////////////////////////////////////////////////////
//	ColorRef
typedef Uint16 ColorRef;

///////////////////////////////////////////////////////////////////////////////
//	OpacityRef
typedef Uint8 OpacityRef;

///////////////////////////////////////////////////////////////////////////////
//	kMaxOpacity
const OpacityRef kMaxOpacity = 100;

///////////////////////////////////////////////////////////////////////////////
// PlanarRef identifier type definition
// 3D coordinate definition of the planar object
typedef Uint32 TPlanarRefID;

const TPlanarRefID kPlanarRefID_ScreenPlane	= TPlanarRefID(0);

typedef Uint8 SnapByType;

///////////////////////////////////////////////////////////////////////////////
typedef Uint32 HandleAsUint32;
typedef Uint32 PointerAsUint32;

typedef Uint64 HandleAsUint64;
typedef Uint64 PointerAsUint64;

///////////////////////////////////////////////////////////////////////////////
typedef Real32 ResolutionRef;
const ResolutionRef kHighResolutionDisplay		= 196.0;	//dpi
const ResolutionRef kDefaultWindowResolution	= 110.0;	//dpi
const ResolutionRef kDefaultFeedbackResolution	= 100.0;	//dpi

// XXX_JDW_ALTURA [2003-1-12]	Clean up whole file... how much is needed?
	
#if !defined(_MINICAD_)

	#if _WIN_EXTERNAL_ || _GSWINSDK_
		// type definions used by the SDK
		
		// QTREMOVAL
		#ifdef __MACTYPESQT__ 
			#define _QTMACCARBONTYPES_
		#endif
		
		
			
		#ifndef _QTMACCARBONTYPES_
			typedef unsigned char Boolean;
			typedef Sint32 Fract;
			typedef Sint32 Fixed;
		#endif

		#ifndef TRUE
			#define TRUE 1
		#endif
		#ifndef FALSE
			#define FALSE 0
		#endif

		#if !defined(false) && (!defined(_MSC_VER) || _MSC_VER <= 1000)
			#define false FALSE
		#endif

		#if !defined(true) && (!defined(_MSC_VER) || _MSC_VER <= 1000)
			#define true TRUE
		#endif

		// added !_QUICKTIME_EXTERNAL_ to prevent conflicts when Apple's Quicktime headers
		// attempt redefine the types which we define in MCTypes.h - TDW 11/4/97
		#ifndef _QTMACCARBONTYPES_	// !_QUICKTIME_EXTERNAL_

// we may not need this now that we have converted to extended80_gs
//			typedef struct { Sint32 man[2]; short exp; } extended80;
			typedef unsigned char Byte;
			typedef unsigned char Str255[256], Str63[64], Str32[33], Str31[32], Str27[28], Str15[16], *StringPtr, **StringHandle;
			typedef char ** Handle;

			#ifndef nil
				#define nil 0L
			#endif

			// This Rect to represent a RECT_SMALL (a Windows RECT that used shorts) and was pretty much unused.
			// For VW9 it is NOT used in the Windows way, but it IS picked up by plug-ins that need a Mac Rect
			// definition since we took Altura dependencies out of the plug-ins for VW9. The member variable
			// ordering is swapped around between Mac and Windows, so we need to use the Mac ordering here now. 
			// [MAF 7/31/00]

//			typedef struct Rect {
//				short left;
//				short top;
//				short right;
//				short bottom;
//			} Rect;

			typedef struct Rect {
				short top;
				short left;
				short bottom;
				short right;
			} Rect;


			typedef Uint32 OSType;

			typedef struct Point {
				short v;
				short h;
			} Point;

			typedef const unsigned char* ConstStr255Param;


			#ifdef RGBColor
				// RGBColor has been defined to be GSColor
			#else

				struct RGBColor {
					unsigned short			red;			/*magnitude of red component*/
					unsigned short			green;			/*magnitude of green component*/
					unsigned short			blue;			/*magnitude of blue component*/
				};
				typedef struct RGBColor RGBColor, *RGBColorPtr, **RGBColorHdl;
			#endif
		#endif // _QTMACCARBONTYPES_		// !_QUICKTIME_EXTERNAL_

		#undef _QTMACCARBONTYPES_

	#else

		#if GS_WIN
			#include "TypesMacQT.h"
			#include "QTHeader.h"
		#else
			#include <MacTypes.h>
			#include <Carbon/Carbon.h>
		#endif

	#endif // _WIN_EXTERNAL_

#else

	#if GS_WIN
		#include "TypesMacQT.h"
		#include "QTHeader.h"
	#else
		#include <MacTypes.h>
	#endif

#endif // !_MINICAD_

#if GS_WIN

/********************************************************************************

    Boolean types and values
    
        Boolean         A one byte value, holds "false" (0) or "true" (1)       
*********************************************************************************/


typedef unsigned char                   Boolean;
				
/********************************************************************************/
#define CALLBACK_API(_type, _name)              _type (__cdecl * _name)
#define CALLBACK_API_C(_type, _name)            _type (__cdecl * _name)
#define STACK_UPP_TYPE(name)    name

/********************************************************************************

    Function Pointer Types
    
        ProcPtr                 Generic pointer to a function
        Register68kProcPtr      Pointer to a 68K function that expects parameters in registers
        UniversalProcPtr        Pointer to classic 68K code or a RoutineDescriptor
        
        ProcHandle              Pointer to a ProcPtr
        UniversalProcHandle     Pointer to a UniversalProcPtr
        
*********************************************************************************/



typedef CALLBACK_API_C( Sint32 , ProcPtr )();
typedef CALLBACK_API( void , Register68kProcPtr )();

typedef ProcPtr                         UniversalProcPtr;

typedef ProcPtr *                       ProcHandle;
typedef UniversalProcPtr *              UniversalProcHandle;

#endif //#if GS_WIN

///////////////////////////////////////////////////////////////////////////////
//	Casting macros (can be used as l-values.)
// Do not use these unless you need them. Do not use them for convenience.
// If you think you need to cast, try const_cast, static_cast, or dynamic_cast.

#define CAST(Type, thing)	(*((Type *) &(thing)))
#define CAST_SHORT(x)		(*((short *) &(x)))
#define CAST_LONG(x)		(*((Sint32 *) &(x)))


///////////////////////////////////////////////////////////////////////////////

union HiLo {
#if GS_LITTLE_ENDIAN
	struct	{ short lo, hi; } shortWord;
	Sint32	longWord;
#else
	struct	{ short hi, lo; } shortWord;
	Sint32	longWord;
#endif
};	// Used for extracting short words from Sint32 words. THIS IS MACHINE DEPENDENT.

inline const short HiWrd(const Sint32& x) { return ((const HiLo *) &x)->shortWord.hi; }
inline const short LoWrd(const Sint32& x) { return ((const HiLo *) &x)->shortWord.lo; }
inline short& HiWrd(Sint32& x) { return ((HiLo *) &x)->shortWord.hi; }
inline short& LoWrd(Sint32& x) { return ((HiLo *) &x)->shortWord.lo; }
// XXX_JDW_MISC - maybe make a << and >> version called HighWord and LowWord that might be faster for some purposes

// See also PinToCoord in MCCoordTypes.h

///////////////////////////////////////////////////////////////////////////////
template<class A, class B, class C> 
inline bool inrange(A value, B lowerBound, C upperBound)
	{ return (value >= lowerBound && value <= upperBound); }

inline void ClipTop(short &x, short upperBound) { if (x > upperBound) x = upperBound; }
inline void ClipTop(Sint32  &x, Sint32  upperBound) { if (x > upperBound) x = upperBound; }
inline void ClipBottom(short &x, short lowerBound) { if (x < lowerBound) x = lowerBound; }
inline void ClipBottom(Sint32  &x, Sint32  lowerBound) { if (x < lowerBound) x = lowerBound; }

inline void ClipNum(short &x, short lowerBound, short upperBound)
	{ if (x < lowerBound) x = lowerBound; else if (x > upperBound) x = upperBound; }

inline void ClipNum(Sint32 &x, Sint32 lowerBound, Sint32 upperBound)
	{ if (x < lowerBound) x = lowerBound; else if (x > upperBound) x = upperBound; }

inline void ClipNum(double &x, double lowerBound, double upperBound)
	{ if (x < lowerBound) x = lowerBound; else if (x > upperBound) x = upperBound; }

///////////////////////////////////////////////////////////////////////////////

// Translate the bit position of a bit in a Motorola Sint32 to its position in
// a native Sint32.  [DMB, 6/15/95]
inline void TranslateBitPosition32(Sint32 *pBit)
{
	#if GS_LITTLE_ENDIAN
		// Translate the bit position of a bit in a big endian Sint32 to its
		// position in an little endian Sint32.
		if (*pBit < 8)		 *pBit += 24;
		else if (*pBit < 16) *pBit +=  8;
		else if (*pBit < 24) *pBit -=  8;
		else				 *pBit -= 24;
	#else
		// Translate the bit position of a bit in a Motorola Sint32 to its
		// position in a Motorola Sint32.
		#pragma unused(pBit)
	#endif
}
//
// Work on Motorola byte order.
inline void		pbitclear(Sint32 &x, Sint32 bit)	{ x &= ~(1L << (bit&31)); }
inline Bool8	pbittest(Sint32 x, Sint32 bit)		{ return (x & (1L << (bit&31))) != 0; }
inline void		pbitset(Sint32 &x, Sint32 bit)		{ x |= (1L << (bit&31)); }
//
// Work on native byte order.
inline void		_pbitclear(Sint32 &x, Sint32 bit)	{ TranslateBitPosition32(&bit); pbitclear(x,bit); }
inline Bool8	_pbittest(Sint32 x, Sint32 bit)		{ TranslateBitPosition32(&bit); return pbittest(x,bit); }
inline void		_pbitset(Sint32 &x, Sint32 bit)		{ TranslateBitPosition32(&bit); pbitset(x,bit); }


/* Set of 0..2047 */
class IntegerSet {
	private:
		enum { numLongs = 64 } ;
		enum { maxElement = numLongs * 32 - 1 } ;
		Sint32	bits[numLongs];
	public:
		IntegerSet();
		IntegerSet(short i0, short i1 = -1, short i2 = -1, short i3 = -1,
					short i4 = -1, short i5 = -1, short i6 = -1, short i7 = -1,
					short i8 = -1, short i9 = -1);
		IntegerSet(const IntegerSet &s);
		
		Bool8 contains(short i) const;
		void operator +=(short i);
		void operator +=(const IntegerSet &s);
		void operator -=(short i);
		void operator -=(const IntegerSet &s);
		IntegerSet& operator =(const IntegerSet &s);
};
