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
#include "OnlyWin/GSDialog.h"

/////////////////////////////////////////////////////////////////////////////////////////
CWnd *GS_GetCWndParent(CallBackPtr cbp)
{
	AfxLockTempMaps();
	HWND hMainWnd = GS_GetMainHWND(cbp);
	return CWnd::FromHandle(hMainWnd);
}

void GS_ReleaseCWndParent(CallBackPtr /*cbp*/, CWnd *&parent)
{
	AfxUnlockTempMaps();
	parent = NULL;
}


///////////////////////////////////////////////////////////////////////////////
// THelpItem implementation

///////////////////////////////////////////////////////////////////////////////
TGSDialog::THelpItem::THelpItem()
{
	fControlID = fLabelID = fStringID = (UINT) -1;
	fLoaded = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
TGSDialog::THelpItem::THelpItem(UINT nStringID, UINT nControlID, UINT nLabelID)
{
	fControlID = nControlID;
	fLabelID = nLabelID;
	fStringID = nStringID;
	fLoaded = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
TGSDialog::THelpItem &TGSDialog::THelpItem::operator=(const THelpItem &a)
{
	ASSERT_VALID(this);

	fControlID = a.fControlID;
	fLabelID = a.fLabelID;
	fStringID = a.fStringID;
	fLoaded = a.fLoaded;
	fString = a.fString;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
BOOL TGSDialog::THelpItem::PointInRect(const CWnd *pParent, const CPoint &pt) const
{
	ASSERT_VALID(this);

	// Try control.
	CRect rTarget;
	CWnd *pTarget = pParent->GetDescendantWindow(fControlID);
	ASSERT(pTarget);
	if (pTarget) {
		CRect rTarget;
		pTarget->GetWindowRect(&rTarget);
		if (rTarget.PtInRect(pt))
			return TRUE;
	}

	// Try label control.
	if (fLabelID != -1) {
		pTarget = pParent->GetDescendantWindow(fLabelID);
		ASSERT(pTarget);
		if (pTarget) {
			pTarget->GetWindowRect(&rTarget);
			if (rTarget.PtInRect(pt))
				return TRUE;
		}
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
const CString &TGSDialog::THelpItem::GetString()
{
	if (!fLoaded) {
		VERIFY( fString.LoadString(fStringID) );
		fLoaded = TRUE;
	}
	return fString;
}


///////////////////////////////////////////////////////////////////////////////
// TGSDialog implementation

BEGIN_MESSAGE_MAP(TGSDialog, CDialog)
	//{{AFX_MSG_MAP(TGSDialog)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
TGSDialog::TGSDialog(CallBackPtr cbp, UINT nIDTemplate, CWnd *pParent)
	: CDialog(nIDTemplate, pParent)
{
	fCBP = cbp;
	fHelpControlID = (UINT) -1;
	fLastHelpIndex = -1;
	fUseHelp = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
void TGSDialog::EnableHelp(UINT nControlID, UINT nDefaultHelpID)
{
	ASSERT_VALID(this);

	fUseHelp = TRUE;
	fHelpControlID = nControlID;
	fLastHelpIndex = -2;
	if (nDefaultHelpID != -1)
		fDefaultHelp.LoadString(nDefaultHelpID);
	fHelpItems.RemoveAll();
}

///////////////////////////////////////////////////////////////////////////////
void TGSDialog::RegisterHelpItem(UINT nStringID, UINT nControlID, UINT nLabelID)
{
	ASSERT_VALID(this);

	THelpItem item(nStringID, nControlID, nLabelID);
	fHelpItems.Add(item);
}

///////////////////////////////////////////////////////////////////////////////
BOOL TGSDialog::DisplayHelpItem(const CPoint &point)
{
	// Search for an item under the point.
	for (INT_PTR i=0, max = fHelpItems.GetSize(); i < max; ++i) { //-V103
		if (fHelpItems[i].PointInRect(this, point)) {
			if (i != fLastHelpIndex) {
				fHelpItems[i].Display(GetDlgItem(fHelpControlID));
				fLastHelpIndex = (Sint32)i; //-V202
			}
			return TRUE;
		}
	}
	// No item found.
	if (fLastHelpIndex != -1) {
		GetDlgItem(fHelpControlID)->SetWindowText(fDefaultHelp);
		fLastHelpIndex = -1;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
BOOL TGSDialog::PreTranslateMessage(MSG *pMsg) 
{
	if (fUseHelp && pMsg->message == WM_MOUSEMOVE)
		DisplayHelpItem(pMsg->pt);
	return CDialog::PreTranslateMessage(pMsg);
}

//---------------------------------------------------------------------------------------
Sint32 TGSDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	const Sint32 result = CDialog::OnCreate(lpCreateStruct);
	ASSERT(this->GetSafeHwnd() != NULL);
	ASSERT(this->GetParent() != NULL);
	GS_EnterMoveableWindow(GetCBP(), this->GetSafeHwnd());
	return result;
}

//---------------------------------------------------------------------------------------
void TGSDialog::OnDestroy()
{
	ASSERT(this->GetSafeHwnd() != NULL);
	GS_ExitMoveableWindow(GetCBP(), this->GetSafeHwnd());
	CDialog::OnDestroy();
}
