//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Functions GetSysColor() and SetButtonColor().
//

#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-COMMENT LINE.  [DMB, 10/30/95]

#if !_WINDOWS || _MINICAD_ || _GSESDK_

#include "Kernel/ExternMisc.h"	
#include "Kernel/MiniCadCallBacks.h"


#if !_WINDOWS
#include "PUtils.h"
#endif

// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE


#if _WINDOWS
	// XXX_JDW_ALTURA
	typedef unsigned short      WORD;

	extern "C" __declspec(dllimport) DWORD WINAPI GetSysColor(Sint32 nIndex);

	// Undefine any old color extraction defines
	#ifdef GetRValue
	#undef GetRValue
	#endif
	#ifdef GetGValue
	#undef GetGValue
	#endif
	#ifdef GetBValue
	#undef GetBValue
	#endif

	#define GetRValue(rgb)	((BYTE)(rgb))
	#define GetGValue(rgb)  ((BYTE)(((WORD)(rgb)) >> 8))
	#define GetBValue(rgb)  ((BYTE)((rgb)>>16))
#endif

#if !_WINDOWS
static const unsigned short
	kGrayF = (unsigned short) 0xFFFF,	// 65535 (white)
	kGrayE = (unsigned short) 0xEEEE,	// 61166
	kGrayD = (unsigned short) 0xDDDD,	// 56797
	kGrayC = (unsigned short) 0xCCCC,	// 52428
	kGrayB = (unsigned short) 0xBBBB,	// 48059
	kGrayA = (unsigned short) 0xAAAA,	// 43690
	kGray9 = (unsigned short) 0x9999,	// 39321
	kGray8 = (unsigned short) 0x8888,	// 34952
	kGray7 = (unsigned short) 0x7777,	// 30583
	kGray6 = (unsigned short) 0x6666,	// 26214
	kGray5 = (unsigned short) 0x5555,	// 21845
	kGray4 = (unsigned short) 0x4444,	// 17476
	kGray3 = (unsigned short) 0x3333,	// 13107
	kGray2 = (unsigned short) 0x2222,	//  8738
	kGray1 = (unsigned short) 0x1111,	//  4369
	kGray0 = (unsigned short) 0x0000;	//     0 (black)
#endif


void GetSysColor(Sint32 index, TRGBColor *rgb, Sint32* qd)
{
	// Check pointers.
	ASSERTN(kDave, rgb || qd);	// Must give us at least one pointer to work with.
	if (rgb) ASSERTPOINTER(kDave, rgb, sizeof(TRGBColor));
	if (qd) ASSERTPOINTER(kDave, qd, sizeof(Sint32));

#if _WINDOWS

	if (qd) {
		// Windows never uses this value, so we'll just assign black to
		// cover our as.. I mean.. cover all the bases.  [DMB, 5/18/95]
		*qd = blackColor;
	}
	if (rgb) {

		if (index == COLOR_SELECTED || index == COLOR_SELECTEDLITE) {

			// Make selected color darker/lighter than normal button face if using
			// shades of gray, leave it untouched if not.
			unsigned short darker = 16;
			if (index == COLOR_SELECTEDLITE)
				darker = -darker;

			// Get individual gray levels.
			DWORD wincolor = GetSysColor(COLOR_BTNFACE);
			rgb->red = GetRValue(wincolor);
			rgb->green = GetGValue(wincolor);
			rgb->blue = GetBValue(wincolor);

			Boolean isGray = (rgb->red == rgb->green && rgb->green == rgb->blue);
			Boolean isInRange = (index == COLOR_SELECTED ? (rgb->red > darker) : (rgb->red < 255+darker));

			if (isGray && isInRange) {
				// Change the gray level.
				rgb->red = (rgb->red - darker) * 256;
				rgb->green = rgb->blue = rgb->red;
			}
			else {
				// Leave color untouched.
	 			rgb->red *= 256;
				rgb->green *= 256;
				rgb->blue *= 256;
			}
		}
		else {
			DWORD wincolor = GetSysColor(index);
			rgb->red = GetRValue(wincolor) * 256;
			rgb->green = GetGValue(wincolor) * 256;
			rgb->blue = GetBValue(wincolor) * 256;
		}
	}

#else
// This is Mac code.

	TRGBColor TRGBColor;
	Sint32 qdColor;

	switch (index) {
		case COLOR_BTNFACE: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGrayD;
			qdColor = whiteColor;
			break;
		}
		case COLOR_BTNFACEDISABLED:
		case COLOR_WNDBACKGROUND: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGrayE;
			qdColor = whiteColor;
			break;
		}
		case COLOR_SELECTED:
		case COLOR_HIGHLIGHT: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGrayA;
			qdColor = blackColor;
			break;
		}
		case COLOR_WINDOW:
		case COLOR_SELECTEDLITE:
		case COLOR_BTNHIGHLIGHT: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGrayF;
			qdColor = whiteColor;
			break;
		}
		case COLOR_BTNSHADOW: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGray7;
			qdColor = whiteColor;
			break;
		}
		case COLOR_BTNTEXT: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGray0;
			qdColor = blackColor;
			break;
		}
		default:
			DSTOP((kDave, "Invalid color index used in \"GetSysColor()\": %d\n", index));
			return;
	}

	if (rgb) *rgb = TRGBColor;
	if (qd) *qd = qdColor;

#endif	// _WINDOWS
}

#endif //  #if !_WINDOWS || _MINICAD_ || _GSESDK_
