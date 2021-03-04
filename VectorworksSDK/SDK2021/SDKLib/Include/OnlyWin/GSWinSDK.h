//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#ifndef _GSWINSDK_H
#define _GSWINSDK_H

#include "../VectorworksSDK.h"


/////////////////////////////////////////////////////////////////////////////////////////
Sint32 WINAPI GS_DialogBox(CallBackPtr cbp, HINSTANCE hInstance, LPCTSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam = 0L);
//
// Description:
//   Use this function instead of the Win32 API function 'DialogBox()' to display dialogs.
//
// Parameters:
//   cbp - input - Call back pointer passed to main().
//   The remain functions all have the use as in the Win32 API function 'DialogBox()'.
//
// Returns:
//   Sint32 WINAPI - Same as in the Win32 API function 'DialogBox()'.
//


#if _MFC_EXTERNAL_
// This section is for MFC based externals.

	#include "GSDialog.h" // Declare the TGSDialog dialog class


	/////////////////////////////////////////////////////////////////////////////////////
	// Use these functions to get and release the parent window for an dialog that is
	// derived from TGSDialog.

		//-------------------------------------------------------------------------------
		CWnd* GS_GetCWndParent(CallBackPtr cbp);
			//
			// Description:
			//   Get the parent winodw to use for an MFC dialog derived from TGSDialog.
			//   When you are done with your dialog, you MUST return this window to the
			//   system by calling GS_ReleaseCWndParent().
			//
			// Parameters:
			//   cbp - input - Call back pointer passed to main().
			//
			// Returns:
			//   CWnd - The parent window to use for your TGSDialog dialog. Pass this to
			//     GS_ReleaseCWndParent() when you are done with it.
			//

		//-------------------------------------------------------------------------------
		void GS_ReleaseCWndParent(CallBackPtr cbp, CWnd* &parent);
			//
			// Description:
			//   Returns the parent window returned from GS_GetCWndParent() to the system.
			//
			// Parameters:
			//   cbp - input - Call back pointer passed to main().
			//   parent - input - The parent window returned from GS_GetCWndParent(). Set
			//     to NULL when fuction returns.
			//


	/////////////////////////////////////////////////////////////////////////////////////
	// Use these functions to get and release the parent window for an dialog that is
	// NOT derived from TGSDialog.

		//-------------------------------------------------------------------------------
		CWnd* GS_EnterMfcDialog(CallBackPtr cbp);
			//
			// Description:
			//   Get the parent winodw to use for an MFC dialog that is not derived from
			//   TGSDialog. When you are done with your dialog, you MUST return this
			//   window to the system by calling GS_ExitMfcDialog().
			//
			// Parameters:
			//   cbp - input - Call back pointer passed to main().
			//
			// Returns:
			//   CWnd - The parent window to use for your dialog. Pass this to
			//     GS_ExitMfcDialog() when you are done with it.
			//

		//-------------------------------------------------------------------------------
		void GS_ExitMfcDialog(CallBackPtr cbp, CWnd* &parent);
			//
			// Description:
			//   Returns the parent window returned from GS_EnterMfcDialog() to the system.
			//
			// Parameters:
			//   cbp - input - Call back pointer passed to main().
			//   parent - input - The parent window returned from GS_EnterMfcDialog(). Set
			//     to NULL when fuction returns.
			//


#endif // _MFC_EXTERNAL_

#endif // _GSWINSDK_H
