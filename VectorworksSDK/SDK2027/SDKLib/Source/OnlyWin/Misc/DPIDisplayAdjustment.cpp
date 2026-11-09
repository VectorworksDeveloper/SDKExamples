#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <gdiplus.h>
#include <VectorworksSDK.h>
#include <OnlyWin/DPIDisplayAdjustment.h>
#include <../../Include/ModernIcons.X.h>
#include "../../../../../Contrib/BCGCBPro/source/BCGPGlobalUtils.h"

namespace DPIDisplayAdjustment {

	using namespace std;
	using namespace Gdiplus;
	using namespace VectorWorks::UI;

	typedef unique_ptr< remove_pointer< HDC >::type, decltype(&::DeleteObject) > HdcDeleteObject_ptr;
 	typedef unique_ptr< remove_pointer< HBITMAP >::type, decltype(&::DeleteObject) > BmpDeleteObject_ptr;
	
	void	ScaleImage( const TXImage&/*img*/, Gdiplus::Bitmap& /*scaledBitmap*/ );

	static const ColorMatrix CM_GRAY_WEIGHT_AVERAGE = { 
		0.333f, 0.333f, 0.333f, 0.0f, 0.0f,
		0.444f, 0.444f, 0.444f, 0.0f, 0.0f,
		0.222f, 0.222f, 0.222f, 0.0f, 0.0f,
		0.0f,	0.0f,	0.0f,	0.2f, 0.0f,
		0.0f,	0.0f,	0.0f,	0.0f, 1.0f
	};

#ifdef _AFX // or _MFC_VER
	BOOL  DrawDPIScaledIcon( CDC const * const pDC, CWnd const * const pWnd, int x, int y, const TXImage& txImage, bool grayed, int width, int height ){
		BOOL fOk = false;

		Sint16 iconWidth = 0, iconHeight = 0;
		txImage.GetDimensions(iconWidth, iconHeight);
		// default is small image
		const TXImage::TByteArray& imageData = txImage.GetData(VectorWorks::UI::ImageVariant::Auto);

		if (!imageData.empty())
		{
			const Uint8* rawData = &imageData[0];
			size_t rawDataSize = imageData.size();

			assert(rawData && rawDataSize);

			do {
				CComPtr<IStream> pIStream;
				if (CreateStreamOnHGlobal(NULL, TRUE, &pIStream) != S_OK) {
					break;
				}

				ULONG bytesWritten = 0;
				if (pIStream->Write(rawData, static_cast<ULONG>(rawDataSize), &bytesWritten) != S_OK) {
					break;
				}

				unique_ptr<Image> bitmap(Image::FromStream(pIStream));
				unique_ptr<Graphics> graphics(new Graphics(pDC->GetSafeHdc()));

				if (grayed) {
					// set color transformation matrix
					ImageAttributes imageAttributes;
					imageAttributes.SetColorMatrix(&CM_GRAY_WEIGHT_AVERAGE);
					// drawing area
					Gdiplus::Rect rc(x, y, globalUtils.ScaleByDPI(static_cast<int>(iconWidth), pWnd), globalUtils.ScaleByDPI(static_cast<int>(iconHeight), pWnd));
					if (Status::Ok != graphics->DrawImage(bitmap.get(), rc, 0, 0, bitmap->GetWidth(), bitmap->GetHeight(), UnitPixel, &imageAttributes)) break;
				}
				else {

					if (width <= 0)
						width = globalUtils.ScaleByDPI(static_cast<int>(iconWidth), pWnd);

					if (height <= 0)
						height = globalUtils.ScaleByDPI(static_cast<int>(iconHeight), pWnd);

					if (Status::Ok != graphics->DrawImage(bitmap.get(), x, y, width, height)) break;
				}

				fOk = TRUE;
			} while (false);
		}

		return fOk;
	}

	// Draw bitmap
	void DrawDPIScaledHbitmap(CDC const * const pDC, CWnd const * const pWnd, HBITMAP hBitmap, int x, int y, bool scaleXandY/*=No=*/, bool grayed /*= false*/)
	{
		unique_ptr<Bitmap> bitmap( Bitmap::FromHBITMAP(hBitmap, 0) );
		DrawDPIScaledBitmap(pDC, pWnd, bitmap.get(), x, y, scaleXandY, grayed);
	}

	void DrawDPIScaledBitmap(CDC const * const pDC, CWnd const * const pWnd, Gdiplus::Bitmap* bitmap, int x, int y, bool scaleXandY/*=No=*/, bool grayed /*= false*/)
	{
		auto DrawBitmap = [&]() {

			Graphics graphics(pDC->GetSafeHdc());

			if (scaleXandY)
			{
				REAL scaleFactor = static_cast<REAL>(GetEffectiveScaleFactor(pWnd));
				graphics.ScaleTransform(scaleFactor, scaleFactor);
				graphics.DrawImage(bitmap, x, y, bitmap->GetWidth(), bitmap->GetHeight());
			}
			else
			{
				graphics.DrawImage(bitmap, x, y, globalUtils.ScaleByDPI(static_cast<int>(bitmap->GetWidth()), pWnd), globalUtils.ScaleByDPI(static_cast<int>(bitmap->GetHeight()), pWnd));
			}
		};

		auto DrawBitmapGrayed = [&]() {

			Graphics graphics(pDC->GetSafeHdc());

			ImageAttributes imageAttributes;
			imageAttributes.SetColorMatrix(&CM_GRAY_WEIGHT_AVERAGE);

			UINT mbWidth = bitmap->GetWidth();
			UINT mbHeight = bitmap->GetHeight();

			if (scaleXandY)
			{
				REAL scaleFactor = static_cast<REAL>(GetEffectiveScaleFactor(pWnd));
				graphics.ScaleTransform(scaleFactor, scaleFactor);

				Gdiplus::Rect rc(x, y, mbWidth, mbHeight);
				graphics.DrawImage(bitmap, rc, 0, 0, mbWidth, mbHeight, UnitPixel, &imageAttributes);
			}
			else
			{
				Gdiplus::Rect rc(x, y, globalUtils.ScaleByDPI(static_cast<int>(mbWidth), pWnd), globalUtils.ScaleByDPI(static_cast<int>(mbHeight), pWnd));
				graphics.DrawImage(bitmap, rc, 0, 0, mbWidth, mbHeight, UnitPixel, &imageAttributes);
			}
		};

		if (grayed)
		{
			DrawBitmapGrayed();
		}
		else
		{
			DrawBitmap();
		}
	}
#endif

	// return scaled Native windows icon handle for given TXImage
	// it could be better to move this code inside TXImage class
	HICON GetDPIScaledIcon(const TXImage& img) {
		Sint16 iconWidth = 0, iconHeight = 0;
		img.GetDimensions(iconWidth, iconHeight);
		return GetDPIScaledIcon( img, iconWidth, iconHeight );
	}

	// return scaled Native windows icon handle for given TXImage
	// it could be better to move this code inside TXImage class
	HICON GetDPIScaledIcon(const TXImage& img, Sint16 iconWidth, Sint16 iconHeight )
	{
		HICON icon = NULL;

		Gdiplus::Bitmap bitmap(globalUtils.ScaleByDPI(static_cast<int>(iconWidth), &CWnd::wndTop), globalUtils.ScaleByDPI(static_cast<int>(iconHeight), &CWnd::wndTop) );

		ScaleImage( img, bitmap );

		bitmap.GetHICON(&icon);

		return icon;
	}

	void ScaleImage(const TXImage &image, Gdiplus::Bitmap& outScaledBitmap )
	{
		if (!image.IsSet()) return;

		double effectiveScaleFactor = globalUtils.GetDPIScale(&CWnd::wndTop);

		const TXImage::TByteArray& imageBuffer = image.GetData(VectorWorks::UI::ImageVariant::Auto);

		if (!imageBuffer.empty())
		{
			const Uint8* data = &imageBuffer[0];
			size_t dataSize = imageBuffer.size();

			if (GetPreferredImageScaling(&CWnd::wndTop) == IMAGE_SCALING_DOUBLE)
			{
				effectiveScaleFactor = GetEffectiveScaleFactor(&CWnd::wndTop);
			}

			do {
				CComPtr<IStream> stream;
				if (CreateStreamOnHGlobal(NULL, TRUE, &stream) != S_OK)
				{
					break;
				}

				ULONG bytesWritten = 0;
				if (stream->Write(data, static_cast<ULONG>(dataSize), &bytesWritten) != S_OK)
				{
					break;
				}

				unique_ptr<Bitmap> originalBitmap(Bitmap::FromStream(stream));

				Graphics graphics(&outScaledBitmap);

				graphics.ScaleTransform(static_cast<REAL>(effectiveScaleFactor), static_cast<REAL>(effectiveScaleFactor));

				graphics.DrawImage(originalBitmap.get(), 0, 0, originalBitmap->GetWidth(), originalBitmap->GetHeight());

			} while (false);
		}
	}

	double GetPreferredImageScaling(const CWnd* pWnd /*= NULL*/)
	{
		return globalUtils.GetDPIScale( pWnd ) > PREFERRED_IMAGE_SCALING_THRESHOLD ? IMAGE_SCALING_DOUBLE : IMAGE_SCALING_NO;
	}

	double GetEffectiveScaleFactor(const CWnd* pWnd /*= NULL*/)
	{
		return globalUtils.GetDPIScale( pWnd ) / GetPreferredImageScaling( pWnd );
	}
}
