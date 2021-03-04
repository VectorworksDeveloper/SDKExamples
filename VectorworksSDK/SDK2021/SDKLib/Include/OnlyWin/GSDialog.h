//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#ifndef _GSDIALOG_
#define _GSDIALOG_ 1

#define _GSDIALOG_VER	0x0100

#include <afxtempl.h>


///////////////////////////////////////////////////////////////////////////////
class TGSDialog : public CDialog
{
// Interface.  Use these functions.
public:
	// Constructor.
	TGSDialog(CallBackPtr cbp, UINT nIDTemplate, CWnd *pParent = NULL);

	// Get the callback pointer used to construct the class.
	CallBackPtr GetCBP() const					{ ASSERT_VALID(this); return fCBP; }

	// Context sensative help.
	void EnableHelp(UINT nControlID, UINT nDefaultHelpID = -1);
	void RegisterHelpItem(UINT nStringID, UINT nControlID, UINT nLabelID = -1);

// Implementation.  You don't wanna look here.
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual BOOL DisplayHelpItem(const CPoint &point);

	// Generated message map functions
	//{{AFX_MSG(TGSDialog)
	afx_msg Sint32 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CallBackPtr	fCBP;					// MiniCad callback pointer.

protected:
	///////////////////////////////////////////////////////////////////////////
	class THelpItem : public CObject
	{
	public:
		THelpItem();					// Default constructor.  Required by CArray.
		THelpItem(UINT nStringID, UINT nControlID, UINT nLabelID = -1);
		THelpItem(const THelpItem &a)		{ *this = a; }
		THelpItem &operator=(const THelpItem &a);
		void Display(CWnd *pWnd)			{ ASSERT_VALID(this); ASSERT_VALID(pWnd); pWnd->SetWindowText(GetString()); }
		BOOL PointInRect(const CWnd *pParent, const CPoint &pt) const;
	protected:
		const CString &GetString();

	// these were made public for Stephan at ComputerWorks
	// we may want to revisit this for a better Sint32 term solution - PCP
	public:
		UINT	fControlID, fLabelID;	// Control IDs.
		UINT	fStringID;				// Help string ID.
		BOOL	fLoaded;				// Has the help string, 'fString', been loaded?
		CString	fString;				// The help string.
	};
	typedef CArray<THelpItem, THelpItem&> THelpItemArray;
	BOOL fUseHelp;						// Is context sensative help being used?
	THelpItemArray fHelpItems;			// All the help items.
	UINT fHelpControlID;				// The control to which help will be written.
	CString fDefaultHelp;				// Defult help message.
	Sint32 fLastHelpIndex;					// Index into 'fHelpItems' of help item currently being displayed.



};

#endif // _GSDIALOG_

