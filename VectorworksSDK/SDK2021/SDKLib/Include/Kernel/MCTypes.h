//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#ifndef _MCTYPES
#define _MCTYPES

#include "GSTypes.h"

#pragma once

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

	#endif // _WIN_EXTERNAL_


#endif // !_MINICAD_

#endif // _MCTYPES
