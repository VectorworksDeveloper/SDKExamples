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


// JAK 3/7/00 Suddenly the SDK Plug-ins do not build.  I think MikeH's changes to SharedDefines.h broke it on 3-1-00.
// Try defining RELEASE_BLD here and relying on SharedDefines.h to set TEST, NETBUG, BUG appropriately.
#define RELEASE_BLD

// So I think the following are unnecessary now...
#undef	TEST
#undef	NETBUG
#undef	BUG

#include "ExternDefines.h"

#define __EXTERNDEFINES__ 1

#define _GSESDK_ 1


#ifndef _WINDOWS
	#include <Carbon/Carbon.h>
#endif
