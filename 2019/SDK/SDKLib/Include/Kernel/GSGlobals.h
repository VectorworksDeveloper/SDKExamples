//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//  This file contains global #defines, global const declarations and global
//  variables that are necessary when using GSCore.h.
//
//		THIS IS THE ONLY PLACE THAT GLOBALS SHOULD BE DEFINED FOR GSCore.h.
//
//  Any #define, const or variable that does not NEED a global scope should be 
//  placed elsewhere.  In addition if a const or #def is associated closely with
//  an object, that declaration should then be placed with the declaration of
//  the object.
//


#ifndef _GS_GLOBALS
#define _GS_GLOBALS

#include "GSGeometry.h"

extern const GSColor kGSColorBlack;
extern const GSColor kGSColorWhite;
extern const GSColor kGSColorRed;
extern const GSColor kGSColorBrightRed;
extern const GSColor kGSColorGreen;
extern const GSColor kGSColorLtGreen;
extern const GSColor kGSColorBlue;
extern const GSColor kGSColorMedBlue;
extern const GSColor kGSColorLtBlue;
extern const GSColor kGSColorLighterBlue;
extern const GSColor kGSColorViolet;
extern const GSColor kGSColorYellow;
extern const GSColor kGSColorLtGray;
extern const GSColor kGSColorLighterGray;


extern const GSColor kGSColor16Black;
extern const GSColor kGSColor16White;


#endif // _GS_GLOBALS_
