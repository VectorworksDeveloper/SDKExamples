//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

//#define _AFX_NO_OLE_SUPPORT
#define _AFX_NO_DB_SUPPORT
#define _AFX_NO_DAO_SUPPORT
//#define _AFX_NO_AFXCMN_SUPPORT

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
	#include <afxole.h>         // MFC OLE classes
	#include <afxodlgs.h>       // MFC OLE dialog classes
	#include <afxdisp.h>        // MFC OLE automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
	#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
	#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_AFXCMN_SUPPORT
	#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define _MFC_EXTERNAL_ 1

#include "VectorworksSDK.h"


Sint32 WINAPI GS_DialogBox(CallBackPtr cbp, HINSTANCE hInstance, LPCTSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
	GS_EnterMoveableWindow(cbp, NULL);
	Sint32 ret = (Sint32)DialogBoxParam(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam); //-V202
	GS_ExitMoveableWindow(cbp, NULL);
	return ret;
}
