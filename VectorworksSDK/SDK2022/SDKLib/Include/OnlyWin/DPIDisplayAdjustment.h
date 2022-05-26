#ifndef DPIDISPLAYADJUSTMENT_H
#define DPIDISPLAYADJUSTMENT_H

#include <type_traits>
#include <memory>

class TXImage;

namespace Gdiplus
{
	class Bitmap;
}

namespace DPIDisplayAdjustment 
{
	typedef std::unique_ptr< std::remove_pointer< HDC >::type, std::function< void ( HDC ) > > HdcReleaseDC_ptr;

	static const float PREFERRED_IMAGE_SCALING_THRESHOLD = float(1.24);
	static const float IMAGE_SCALING_NO = 1.f;
	static const float IMAGE_SCALING_DOUBLE = 2.f;

	/* All functions always return number of pixels per logical inch along the screen height. LOGPIXELSY */
	/* Ask BWilliams if you need LOGPIXELSX */
	inline float	DPIScaleFactor( HWND /*hWnd*/ );

	/* Function will scale and draw icon in to Device Context */
	bool			DrawDPIScaledIcon( HDC, HWND, int /*x*/, int /*y*/, const TXImage&, bool /*grayed*/ = false, int width = -1, int height = -1);

	/* mapping between DPI scale factor and image scaling */
	float			GetPreferredImageScaling( HWND = ::GetDesktopWindow() );

	float			GetEffectiveScaleFactor( HWND = ::GetDesktopWindow() );

#ifdef _AFX // or _MFC_VER

	// Draw DPI scaled bitmap to a device context.
	// pDC (input) : pointer to the device context.
	// pWnd (input) : pointer to a CWnd pointer for DPI scaling.
	// bBitmap (input) : handle of the bitmap.
	// (x, y) : the coordinates of the top-left corner of the bitmap in the destination.
	void			DrawDPIScaledHbitmap( CDC const * const /*pDC*/, CWnd const * const /*pWnd*/, HBITMAP /*hBitmap*/, int /*x*/, int /*y*/, bool scaleXandY=false );
	void			DrawDPIScaledBitmap(CDC const * const /*pDC*/, CWnd const * const /*pWnd*/, Gdiplus::Bitmap* /*bitmap*/, int /*x*/, int /*y*/, bool scaleXandY = false);
	void			DrawDPIScaledIcon( CDC const * const, CWnd const * const, int /*x*/, int /*y*/, const TXImage&, bool /*grayed*/ = false , int width = -1, int height = -1);

	/* All functions always return number of pixels per logical inch along the screen height. LOGPIXELSY */
	float			DPIScaleFactor( CWnd const * const /*pWnd*/ );
	float			DPIScaleFactor( const CWnd& /*pWnd*/ );
	
	/* 
	*	Scaling of different windows types and integral values
	*	DPIScale overloads are enabled via the return type, because of 
	*	(error C4519: default template arguments are only allowed on a class template)
	*/
	template<typename TValue> 
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
					DPIScale(CWnd const * const /*pWnd*/, TValue /*tvalue*/ );

	template<typename TValue> 
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
					DPIScale(const CWnd& /*rWnd*/, TValue /*tvalue*/ );

	template<typename TValue> // Convenient function of pDC.
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
					DPIScale(CDC const * const /*pDC*/, TValue /*value*/ );

	template<typename TValue>
	typename std::enable_if<std::is_base_of<SIZE, TValue>::value, TValue>::type
					DPIScale(CWnd const * const /*pWnd*/, const TValue& /*tvalue*/ );

	template<typename TValue>
	typename std::enable_if<std::is_base_of<POINT, TValue>::value, TValue>::type
					DPIScale(CWnd const * const /*pWnd*/, const TValue& /*tvalue*/ );

	template<typename TValue>
	typename std::enable_if<std::is_base_of<RECT, TValue>::value, TValue>::type
					DPIScale(CWnd const * const /*pWnd*/, const TValue& /*tvalue*/ );

#endif
	
	template<typename TValue>
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
					DPIScale(HWND /*hWnd*/, TValue /*tvalue*/ );

	template<typename TValue>
	typename std::enable_if<std::is_base_of<RECT, TValue>::value, TValue>::type
					DPIScale(HWND /*hWnd*/, const TValue& /*tvalue*/ );

	/* return scaled Native windows icon handle for given input */
	HICON			GetDPIScaledIcon( const TXImage&, Sint16 /*iconWidth*/, Sint16 /*iconHeight*/ );
	HICON			GetDPIScaledIcon( const VectorWorks::UI::IIcon& );
	HICON			GetDPIScaledIcon( const TXImage& );

	HBITMAP 		GetDPIScaledBitmap( const TXImage&, Sint16 /*iconWidth*/, Sint16 /*iconHeight*/ );
	HBITMAP 		GetDPIScaledBitmap( const VectorWorks::UI::IIcon& );
	HBITMAP 		GetDPIScaledBitmap( const TXImage& );
}


// template implementations
namespace DPIDisplayAdjustment {

	float DPIScaleFactor( HWND hWnd ) {
		static float skaleFactorY = 0.0;

		if( skaleFactorY == 0.0 ) {
			skaleFactorY = 1.0;

			HdcReleaseDC_ptr hdc( ::GetDC( hWnd ), [&hWnd](HDC hDC ){ ::ReleaseDC( hWnd, hDC ); } );
			if ( hdc ) {
				skaleFactorY = ::GetDeviceCaps( hdc.get(), LOGPIXELSY ) / 96.0f;
			}
		}

		return skaleFactorY;
	}

#ifdef _AFX // or _MFC_VER

	template<typename TValue>
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
		DPIScale(CWnd const * const pWnd, TValue tvalue ) 
	{
		return DPIScale( pWnd->GetSafeHwnd(), tvalue );
	}

	template<typename TValue> 
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
		DPIScale(const CWnd& rWnd, TValue tvalue )
	{
		return DPIScale( rWnd.GetSafeHwnd(), tvalue );
	}

	template<typename TValue>
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
		DPIScale(CDC const * const pDC, TValue tvalue ) 
	{
		return DPIScale( pDC->GetWindow(), tvalue );
	}

	template<typename TValue>
	typename std::enable_if<std::is_base_of<SIZE, TValue>::value, TValue>::type
		DPIScale(CWnd const * const pWnd, const TValue& tvalue ) 
	{
		return DPIScale( pWnd->GetSafeHwnd(), tvalue );
	}

	template<typename TValue>
	typename std::enable_if<std::is_base_of<POINT, TValue>::value, TValue>::type
		DPIScale(CWnd const * const pWnd, const TValue& tvalue ) 
	{
		return DPIScale( pWnd->GetSafeHwnd(), tvalue );
	}

	template<typename TValue>
	typename std::enable_if<std::is_base_of<RECT, TValue>::value, TValue>::type
		DPIScale(CWnd const * const pWnd, const TValue& tvalue )
	{
		return DPIScale( pWnd->GetSafeHwnd(), tvalue );
	}

#endif

	template<typename TValue>
	typename std::enable_if<std::is_integral<TValue>::value && !std::is_same<bool, TValue>::value, TValue>::type 
		DPIScale(HWND hWnd, TValue tvalue ) 
	{
		return static_cast<TValue>( .5 + tvalue * DPIScaleFactor( hWnd ) );
	}

	// Scale SIZE derived class object.
	template<typename TValue>
	typename std::enable_if<std::is_base_of<SIZE, TValue>::value, TValue>::type
		DPIScale(HWND hWnd, const TValue& tvalue ) 
	{
		TValue result( tvalue );
		result.cx = DPIScale(hWnd, result.cx);
		result.cy = DPIScale(hWnd, result.cy);
		return result;
	}

	// Scale POINT derived class object.
	template<typename TValue>
	typename std::enable_if<std::is_base_of<POINT, TValue>::value, TValue>::type
		DPIScale(HWND hWnd, const TValue& tvalue ) 
	{
		TValue result( tvalue );
		result.x = DPIScale(hWnd, result.x);
		result.y = DPIScale(hWnd, result.y);
		return result;
	}

	// Scale RECT derived class object.
	template<typename TValue>
	typename std::enable_if<std::is_base_of<RECT, TValue>::value, TValue>::type
		DPIScale(HWND hWnd, const TValue& tvalue ) 
	{
		TValue result( tvalue );
		result.SetRect(DPIScale(hWnd, result.TopLeft()), DPIScale(hWnd, result.BottomRight()));
		return result;
	}

}

#endif // DPIDISPLAYADJUSTMENT_H
