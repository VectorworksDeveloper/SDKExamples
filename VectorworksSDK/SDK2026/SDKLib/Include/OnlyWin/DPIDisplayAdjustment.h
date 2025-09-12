#ifndef DPIDISPLAYADJUSTMENT_H
#define DPIDISPLAYADJUSTMENT_H

#include <type_traits>
#include <memory>
#include <processthreadsapi.h>

class TXImage;

namespace Gdiplus
{
	class Bitmap;
}

namespace DPIDisplayAdjustment 
{
	static const float PREFERRED_IMAGE_SCALING_THRESHOLD = float(1.24);
	static const float IMAGE_SCALING_NO = 1.f;
	static const float IMAGE_SCALING_DOUBLE = 2.f;

#ifdef _AFX // or _MFC_VER

	/* mapping between DPI scale factor and image scaling */
	double			GetPreferredImageScaling(const CWnd* = NULL);
	double			GetEffectiveScaleFactor(const CWnd* = NULL);

	// Draw DPI scaled bitmap to a device context.
	// pDC (input) : pointer to the device context.
	// pWnd (input) : pointer to a CWnd pointer for DPI scaling.
	// bBitmap (input) : handle of the bitmap.
	// (x, y) : the coordinates of the top-left corner of the bitmap in the destination.
	void			DrawDPIScaledHbitmap( CDC const * const /*pDC*/, CWnd const * const /*pWnd*/, HBITMAP /*hBitmap*/, int /*x*/, int /*y*/, bool scaleXandY=false, bool grayed = false);
	void			DrawDPIScaledBitmap(CDC const * const /*pDC*/, CWnd const * const /*pWnd*/, Gdiplus::Bitmap* /*bitmap*/, int /*x*/, int /*y*/, bool scaleXandY = false, bool grayed = false);
	BOOL			DrawDPIScaledIcon( CDC const * const, CWnd const * const, int /*x*/, int /*y*/, const TXImage&, bool /*grayed*/ = false , int width = -1, int height = -1);

#endif

	inline float	DPIScaleFactor(HWND = ::GetDesktopWindow());

	template<typename TValue>
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
					DPIScale(HWND /*hWnd*/, TValue /*tvalue*/ );

	/* return scaled Native windows icon handle for given input */
	HICON			GetDPIScaledIcon( const TXImage&, Sint16 /*iconWidth*/, Sint16 /*iconHeight*/ );
	HICON			GetDPIScaledIcon( const TXImage& );
}

// template implementations
namespace DPIDisplayAdjustment 
{
	//******************************************************************************************
	float DPIScaleFactor( HWND hWnd ) 
	{
		GUITHREADINFO gti = {0};
		gti.cbSize = sizeof(GUITHREADINFO);

		if (hWnd == HWND_TOP && ::GetGUIThreadInfo(::GetCurrentThreadId(), &gti))
		{
			hWnd = gti.hwndActive ? gti.hwndActive : ::GetDesktopWindow();
		}

		using HdcReleaseDC_ptr = std::unique_ptr< std::remove_pointer< HDC >::type, std::function< void(HDC) > >;
		using FreeLibrary_ptr = std::unique_ptr< std::remove_pointer<HMODULE>::type, std::function< void(HMODULE) > >;
		using GETDPIFORWINDOW = UINT(__stdcall*)(HWND);

		static UINT nDPIDefault = 0;

		if (nDPIDefault == 0) 
		{
			HdcReleaseDC_ptr hdc(::GetDC(hWnd), [&hWnd](HDC hDC) { ::ReleaseDC(hWnd, hDC); });
			
			if (hdc) 
			{
				nDPIDefault = ::GetDeviceCaps(hdc.get(), LOGPIXELSY);
			}
		}

		UINT nDPI = nDPIDefault;

		if(hWnd != NULL)
		{
			static FreeLibrary_ptr hinstUser32(LoadLibrary(L"USER32.DLL"), [](HMODULE hmodule) { FreeLibrary(hmodule); });
			static GETDPIFORWINDOW lpfnGetDpiForWindow = reinterpret_cast<GETDPIFORWINDOW>(::GetProcAddress(hinstUser32.get(), "GetDpiForWindow"));

			if (lpfnGetDpiForWindow)
			{
				nDPI = (*lpfnGetDpiForWindow)(hWnd);
			}
		}

		float dblScale = (float)nDPI / 96.0f;
		if (dblScale > 1. && dblScale < 1.1)
		{
			dblScale = 1.;
		}

		return dblScale;
	}

	//******************************************************************************************
	template<typename TValue>
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
		DPIScale(HWND hWnd, TValue tvalue ) 
	{
		const double dblD = tvalue < 0 ? -0.5 : 0.5;
		return static_cast<TValue>(dblD + tvalue * DPIScaleFactor( hWnd ) );
	}
}

#endif // DPIDISPLAYADJUSTMENT_H
