//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include <windows.h>


/*extern "C"	HDC __stdcall ASI_GetCurrentDC(void);


void HackResetWindowsClipRect()
{
	RECT winRect;
	HWND hWnd;
	HRGN hrgn;

	HDC hDC = ASI_GetCurrentDC();
	hWnd = WindowFromDC(hDC);
	GetClientRect(hWnd, &winRect);

//#if 0
	SelectObject(hDC, GetStockObject(WHITE_BRUSH));
	SetBkColor(hDC, 0x00FF00FF);
	SetBkMode(hDC, OPAQUE);
	SetROP2(hDC, R2_BLACK);
	SetBrushOrgEx(hDC, 0, 0, NULL);
//#endif

	RECT	clipRect;
	Sint32 getClipResult = GetClipBox(hDC, &clipRect);

	clipRect.left = 0;
	clipRect.top = 0;
	clipRect.right = 1000;
	clipRect.bottom = 1000;

	hrgn = CreateRectRgn(clipRect.left, clipRect.top, clipRect.right, clipRect.bottom);
//	hrgn = CreateRectRgn(0, 0, winRect.right, winRect.bottom);
//	SelectClipRgn(hDC, hrgn);
	SelectClipRgn(hDC, NULL);
//	MoveToEx(hDC, 0, 0, NULL);

//	FillRect(hDC, &winRect, (HBRUSH) GetStockObject(WHITE_BRUSH));

	DeleteObject(hrgn);

}
*/

#ifdef HELLFREEZE
typedef const void *        HANDLE;

typedef HANDLE HWND;
typedef HANDLE HDC;

typedef Sint32			BOOL;

// Stuff for the GetWindowPlacement API call.
typedef struct tagPOINT
{
    Sint32  x, y;
} POINT, *PPOINT, *LPPOINT;
typedef struct tagRECT
{
    Sint32    left, top, right, bottom;
} RECT, *PRECT, *LPRECT;

#undef FillRect
#define WinFillRect FillRect

extern "C" {
	__declspec(dllimport) HWND __stdcall WindowFromDC(HDC hDC);
	__declspec(dllimport) BOOL __stdcall GetClientRect(HWND hWnd, LPRECT lpRect);
	__declspec(dllimport) Sint32  __stdcall FillRect(HDC hDC, const RECT *lprc, HANDLE h);
	__declspec(dllimport) Uint32 __stdcall GetSysColor(Sint32 nIndex);

}

#define COLOR_ACTIVECAPTION     2

#endif
