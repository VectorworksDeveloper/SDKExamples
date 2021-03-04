//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// Declarations of GetSysColor() and SetButtonColor().
//

#ifndef _EXTERNMISC_
#define _EXTERNMISC_

#pragma once

#if GS_WIN

	#include "QTHeader.h"

#endif




#if GS_MAC
#ifndef __QUICKDRAWTYPES__
//	Need these QD color constants while we work on QD removal.
enum {
  blackColor                    = 33,   /* colors expressed in these mappings */
  whiteColor                    = 30,
  redColor                      = 205,
  greenColor                    = 341,
  blueColor                     = 409,
  cyanColor                     = 273,
  magentaColor                  = 137,
  yellowColor                   = 69
};
#endif	//#ifndef __QUICKDRAWTYPES__
#endif	//#if GS_MAC


void GetSysColor(int index, TRGBColor *rgb, Sint32 *qd=nil);


// Button color indexes.  DO NOT CHANGE these values or add new values.  They
// are predefined by the Windows operating systems to be the specified values.
// [DMB, 5/12/95]


#if WINVER
	#define COLOR_WINDOWFRAME        6
	#define COLOR_3DLIGHT           22
#endif


#define COLOR_WINDOW				5
#define COLOR_HIGHLIGHT         	13
#define COLOR_BTNFACE           	15
#define COLOR_BTNSHADOW         	16
#define COLOR_GRAYTEXT          	17
#define COLOR_BTNTEXT           	18
#define COLOR_BTNHIGHLIGHT      	20


#if WINVER
	#define COLOR_BTNFACEDISABLED	COLOR_BTNFACE
	#define COLOR_WNDBACKGROUND		COLOR_BTNFACE
#else
	#define COLOR_BTNFACEDISABLED	10003
	#define COLOR_WNDBACKGROUND		10004
#endif

// These are color indexes added by us and not defined by Windows.  We can
// add these because they eventualy map to predefined values under Windows.
#define COLOR_SELECTED				10001
#define COLOR_SELECTEDLITE			10002


#endif // _EXTERNMISC_
