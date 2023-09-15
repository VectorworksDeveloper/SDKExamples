//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components

#define _MFC_EXTERNAL_ 1

#include "VectorworksSDK.h"

Sint32 WINAPI GS_DialogBox(CallBackPtr cbp, HINSTANCE hInstance, LPCTSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
	GS_EnterMoveableWindow(cbp, NULL);
	Sint32 ret = (Sint32)DialogBoxParam(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam); //-V202
	GS_ExitMoveableWindow(cbp, NULL);
	return ret;
}
