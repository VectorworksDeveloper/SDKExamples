//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

/*
This file must be included before any windows types (i.e. HANDLE) are used
	if Windows.h is not included

This file can be included after Windows.h, in which case it avoids
	redeclaring windows stuff

This file should never be included before Windows.h

This file should be included after MacTypes.x for MacRectToWinRect et. al.
	to be defined
*/

#if !defined( _INC_WINDOWS )
	#error ( Windows only - include Windows.h )
#endif


#if !defined(_GSWIN_) && _WINDOWS
#define _GSWIN_

// XXX_JDW_ALTURA CLEANUP [2003-05-28]

// User messages.
#if defined(WM_USER)
	#define WM_GS_LOADFILE WM_USER
#endif
	
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	From this point down are declarations for
//	functions and data defined in GSWin.cpp
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


	// Global Altura variables.
	extern HINSTANCE hInst;			// Application's instance handle.
	extern HWND hMainWnd;			// Main window handle as defined by Altura.
	extern HANDLE gGSESDK;			// Handle to GSESDK.DLL

	//extern HMODULE gAltura;			// Handle to Altura's library.
	extern short gl_InWinDialog;	// Number of dialogs open.
	//extern BOOL bInitAppOK;			// ASIWMain.c
	
	char **MacHandleAllocate(size_t size);
	
	// Special functions to determine stuff about the running system.


extern COLORREF SysColor_3DDKSHADOW, SysColor_3DFACE, SysColor_3DHILIGHT, SysColor_3DLIGHT,
		SysColor_3DSHADOW, SysColor_ACTIVEBORDER, SysColor_ACTIVECAPTION, SysColor_APPWORKSPACE,
		SysColor_BACKGROUND, SysColor_BTNFACE, SysColor_BTNHILIGHT, SysColor_BTNSHADOW,
		SysColor_BTNTEXT, SysColor_CAPTIONTEXT, SysColor_GRAYTEXT, SysColor_HIGHLIGHT,
		SysColor_HIGHLIGHTTEXT, SysColor_INACTIVEBORDER, SysColor_INACTIVECAPTION,
		SysColor_INACTIVECAPTIONTEXT, /*SysColor_INFOBK, SysColor_INFOTEXT,*/ SysColor_MENU,
		SysColor_MENUTEXT, SysColor_SCROLLBAR, SysColor_WINDOW, SysColor_WINDOWFRAME,
		SysColor_WINDOWTEXT;

void EnableAlturaWindows(BOOL bEnable);
BOOL GetParentRelativeWindowRect(HWND hWnd, RECT *lpRect, HWND *parent);
void CommandMDI(Sint32 cmd);
short GS_LBItemFromClientPt(HWND hWnd, POINT pt, BOOL bAutoScroll);
BOOL WINAPI IsEscapeKeyDown();
void Mac2WinString(const unsigned char *ps, char *sz, Sint32 max);
void Win2MacString(const char *sz, unsigned char *ps, Sint32 max);

HFONT GetWindowsStockHFont();

LONG GetIMEStringWidth(HWND hWnd);



#ifdef __MACTYPES__
	Point GetIMEStartPoint(HWND hWnd);
	ViewRect GetIMEContextRect(HWND hWnd);
	void SetIMEConversionFont(HWND hWnd, short font, short size, Style style);
	#ifdef __cplusplus
		void GetIMEWindowBounds(HWND hWnd, ViewRect& IMERect);
	#endif
#endif

#ifdef __cplusplus
	// Call these instead of AdjustWindowRectEx
	void AdjustWndRect(RECT *pRect, BOOL bOut, DWORD dwStyle, DWORD dwExStyle);
	void AdjustWndRect(RECT *pRect, BOOL bOut, HWND hWnd);
	#ifdef __MACTYPES__
		void AdjustWndRect(ViewRect *prMac, BOOL bOut, DWORD dwStyle, DWORD dwExStyle);
		void AdjustWndRect(ViewRect *prMac, BOOL bOut, HWND hWnd);
	#endif // __MACTYPES__
	const char* GetApplicationPath(char *szFN = NULL);
#endif // __cplusplus




#ifdef __cplusplus
extern "C"
{
#endif
	
	
	#ifdef __MACTYPES__
		Rect GetApplicationClientRect();
	#endif // __MACTYPES__
	
	
	
#ifdef __cplusplus
//extern "C"
}
#endif


#ifdef __cplusplus
	//#if !defined( _INC_WINDOWS )
	#ifdef __MACTYPES__
		BOOL CreateComboRects(const ViewRect &srcRect, ViewRect *comboFieldRect, ViewRect *comboButtonRect);
		void DrawComboButton(HWND hWnd, HDC hDCUser, const ViewRect &iRect_p, BOOL bDisabled, BOOL isSelected);
		void DrawComboField(HWND hWnd, HDC hDCUser, const ViewRect &userRect, BOOL isSelected);
	#endif // __MACTYPES__
	//#endif
	Sint32 GS_LoadString(UINT uID, unsigned char *pascalString, Sint32 nBufferMax);
	Sint32 GS_LoadString(UINT uID, LPSTR lpBuffer, Sint32 nBufferMax);
#endif


#ifdef __cplusplus
extern "C"
{
#endif
	
	
	
	
	
	
	
	
	#if TEST
		BOOL IsValidDC(HDC hdc);
	#endif // TEST
	
	
	
#ifdef __cplusplus
//extern "C"
}
#endif



///////////////////////////////////////////////////////////////////////////////
#if defined(__cplusplus)
///////////////////////////////////////////////////////////////////////////////
	
	#if defined(__MACTYPES__)
	
	inline void ViewRectToWinRect(const ViewRect& viewRect, RECT& winRect)
	{
		winRect.left   = viewRect.left;
		winRect.top    = viewRect.top;
		winRect.right  = viewRect.right;
		winRect.bottom = viewRect.bottom;
	}
	
	inline void WinRectToViewRect(const RECT& winRect, ViewRect& viewRect)
	{
		#ifndef SHRT_MIN
		#define SHRT_MIN    (-32768)        /* minimum (signed) short value */
		#define SHRT_MAX      32767         /* maximum (signed) short value */
		#endif
	
		#define CONVERT(side) \
			/*_ASSERT((winRect.side > SHRT_MIN) && (winRect.side < SHRT_MAX));*/ \
			viewRect.side = (short) winRect.side;
	
		CONVERT(top); CONVERT(left); CONVERT(bottom); CONVERT(right);
	
		#undef CONVERT
	}
	
	ViewRect GetDesktopWindowRect();
	
	#endif // __MACTYPES__
	
	
	
	
	
	
	
	
	
	
	
	
	///////////////////////////////////////////////////////////////////////////////
	class TDLL
	{
	public:
		TDLL()						{ fDLL = NULL; }
		TDLL(LPCSTR lpszFN)			{ fDLL = NULL; Load(lpszFN); }
		~TDLL()						{ Free(); }
	
	
	
	
	
	
	
	
	
		BOOL IsOkay() const			{ return fDLL != NULL; }
	
	
	
		BOOL Load(LPCSTR lpszFN);
		BOOL Free();
		FARPROC GetProcAddress(LPCSTR name) const;
		DWORD GetModuleFileName(LPSTR lpFilename, DWORD nSize) const;
	
	private:
		HMODULE fDLL;
	};
	
	/*
	enum EFileFlags {
		eNoFlags		= 0,
		eIsDirectory	= 1
	};
	
	typedef BOOL (*TraverseFuncPtr)(EFileFlags flags, const char* fileName, void* env);
		// Return false to stop traversal
	
	HANDLE TraverseDirectory(TraverseFuncPtr fileFunc, const char* path, void* env, HANDLE hFirstFile,
		const char* filter=0, BOOL skipFutureFiles=0);
	
	///////////////////////////////////////////////////////////////////////////////
	// To use this class, derive your own call from it.  For example:
	//
	//	class TMyFunction : public TDLLFunc
	//	{
	//		public:
	//			typedef MyReturnType (CALLBACK *MyFunctionType)(Type1 param1, Type2 param2, Type3 param3);
	//			TMyFunction(TDLL &dll) : TDLLFunc(dll, "MyFunctionName")			{ }
	//			MyReturnType Call(Type1 param1, Type2 param2, Type3 param3)	{ return ((MyFunctionType) *GetFunctionPtr())(param1, param2, param3); }
	//	};
	//
	//	TMyFunction myFunction(myDll);
	//	ASSERTN(kMe, myFunction.IsOkay());
	//	MyReturnType ret = myFunction.Call(one, two, three);
	//
	class TDLLFunc
	{
	public:
		TDLLFunc()									{ fProcPtr = NULL; }
		TDLLFunc(TDLL &dll, LPCSTR funcName)		{ IDLLFunc(dll, funcName); }
		BOOL IDLLFunc(TDLL &dll, LPCSTR funcName)	{ fProcPtr = (dll.IsOkay() ? dll.GetProcAddress(funcName) : NULL); return fProcPtr != NULL; }
		BOOL IsOkay() const							{ return fProcPtr != NULL; }
	protected:
		FARPROC GetFunctionPtr()					{ return fProcPtr; }
	private:
		FARPROC	fProcPtr;
	};
	*/

	///////////////////////////////////////////////////////////////////////////////

	
	
	

///////////////////////////////////////////////////////////////////////////////
#endif // __cplusplus
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C"
{
#endif


	#if !_MCWINSUP_ //Can't include this in MCWinSup dll stuff RWM

	//This is for RichEdit stuff
	typedef struct _charrange
	{
		LONG	cpMin;
		LONG	cpMax;
	} CHARRANGE;
	#define EM_EXSETSEL				(WM_USER + 55)
	#define EM_GETSELTEXT			(WM_USER + 62)

	#endif //!_MCWINSUP_


#ifdef __cplusplus
//extern "C"
}
#endif


#endif	// !_GSWIN_ && WINVER
