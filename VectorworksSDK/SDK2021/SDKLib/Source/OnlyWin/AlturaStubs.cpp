//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-COMMENT LINE.  [DMB, 10/30/95]

#ifndef _INC_WINDOWS
#error XXX_JDW_ALTURA
#endif

#include "AlturaDefs.h"

#if GS_WIN
//Required for GS_Kludge(...) usage.
#include <MiniCadCallBacks.h>
#endif	//#if GS_WIN - For GS_Kludge(...) and supporting structures/routines.

// XXX_JDW_ALTURA [2002-12-16]	random; just to compile	




#include <Resources.h>




#define VAR_TIMEVALUEONLY       ((DWORD)0x00000001)    /* return time value */
#define VAR_DATEVALUEONLY       ((DWORD)0x00000002)    /* return date value */

typedef DWORD LCID;
typedef double DATE;
typedef LONG HRESULT;

typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character
typedef WCHAR OLECHAR;
typedef WCHAR *LPWSTR, *PWSTR;

#define CP_ACP                    0           // default to ANSI code page
typedef Uint32 ULONG;


//#include <ColorPicker.h>

////////////////////////////////////////////////////////////////////////////////
#ifndef __COLORPICKER__

extern "C" {
	/* A SmallFract value is just the fractional part of a Fixed number,
	which is the low order word.  SmallFracts are used to save room,
	and to be compatible with Quickdraw's RGBColor.  They can be
	assigned directly to and from INTEGERs. */
	/* Unsigned fraction between 0 and 1 */
	typedef unsigned short                  SmallFract;
	/* For developmental simplicity in switching between the HLS and HSV
	models, HLS is reordered into HSL. Thus both models start with
	hue and saturation values; value/lightness/brightness is last. */


	struct HSVColor {
		SmallFract                      hue;                        /*Fraction of circle, red at 0*/
		SmallFract                      saturation;                 /*0-1, 0 for gray, 1 for pure color*/
		SmallFract                      value;                      /*0-1, 0 for black, 1 for max intensity*/
	};
	typedef struct HSVColor                 HSVColor;

	struct HSLColor {
		SmallFract                      hue;                        /*Fraction of circle, red at 0*/
		SmallFract                      saturation;                 /*0-1, 0 for gray, 1 for pure color*/
		SmallFract                      lightness;                  /*0-1, 0 for black, 1 for white*/
	};
	typedef struct HSLColor                 HSLColor;

	struct CMYColor {
		SmallFract                      cyan;
		SmallFract                      magenta;
		SmallFract                      yellow;
	};
	typedef struct CMYColor                 CMYColor;
} //extern "C"
#endif	//  __COLORPICKER__
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
/*

#if !_GSESDK_
		//#include <OsTDefs.h>

		#define	OST_cicn	0x6369636EL


		CIconHandle XPlatform::GetCIcon(Sint16 iconID)
		{
			CIconHandle	hIcon = (CIconHandle) RsrcMgr::GSGetResource( OST_cicn, iconID );

			return hIcon;
		}

#endif
*/
