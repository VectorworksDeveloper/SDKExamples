//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//	This file is a "Prefix File" which is included by MW CodeWarrior when it is specified 
//	in the "Project Settings" dialog's "Language Settings/C/C++ Language" pane.
//	That mechanism allows you to include different prefix files for differnet Targets within the project.
//

// JAK 3/7/00 I think we now need to define DEV_BLD so SharedDefines.h is happy.
#define DEV_BLD 1

#define	TEST 1
#define	BUG 1

#include <OnlyMac/ExternDefines.h>

#define __EXTERNDEFINES__ 1

#define _GSESDK_ 1

#ifndef _WINDOWS
	#include <Carbon/Carbon.h>
#endif
