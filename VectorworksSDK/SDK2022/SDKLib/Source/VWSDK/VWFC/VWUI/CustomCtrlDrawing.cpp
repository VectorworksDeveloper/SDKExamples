//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/CustomCtrlDrawing.h"

#ifdef _WINDOWS
	#include "OnlyWin/DPIDisplayAdjustment.h"
#endif

using namespace VectorWorks;
using namespace VWFC::VWUI;

// ----------------------------------------------------------------------------------------
namespace VWFC
{
	namespace VWUI
	{
		struct SVisualPoint {
			ViewPt		pt;
			bool		bVisible;
		};

		typedef std::vector<SVisualPoint>	TPointsArray;
	}
}

// ----------------------------------------------------------------------------------------
VWCustomCtrlDC::VWCustomCtrlDC(SintptrT devHandle, void* devDC, ViewCoord xOffset, ViewCoord yOffset) :
	fpDrawPad( VectorWorks::IID_DrawPad ),
	fXOffset( xOffset ),
	fYOffset( yOffset )
{
	farrPolyPts		= SDK_NEW TPointsArray;

	fDevHandle		= devHandle;
	fpDevDC			= devDC;

	if ( fpDrawPad == NULL || VCOM_FAILED( fpDrawPad->InitializeInDevice( devHandle, devDC ) ) ) {
		// error! release and use empty instance
		fpDrawPad	= TDrawPad();
	}
}

VWCustomCtrlDC::VWCustomCtrlDC(ViewCoord width, ViewCoord height) :
	fpDrawPad( VectorWorks::IID_DrawPad ),
	fXOffset( 0 ),
	fYOffset( 0 )
{
	farrPolyPts		= SDK_NEW TPointsArray;

	fDevHandle		= NULL;
	fpDevDC			= NULL;

	ViewRect	rect( 0, 0, width, height );
	if ( fpDrawPad == NULL || VCOM_FAILED( fpDrawPad->InitializeInMemory( rect ) ) ) {
		// error! release and use empty instance
		fpDrawPad	= TDrawPad();
	}
	else {
		fpDrawPad->SetClipRect( rect );
	}
}

VWCustomCtrlDC::VWCustomCtrlDC(const ViewRect& inViewRect) :
	fpDrawPad( VectorWorks::IID_DrawPad ),
	fXOffset( 0 ),
	fYOffset( 0 )
{
	farrPolyPts		= SDK_NEW TPointsArray;

	if ( fpDrawPad == NULL || VCOM_FAILED( fpDrawPad->InitializeInMemory( inViewRect ) ) ) {
		// error! release and use empty instance
		fpDrawPad	= TDrawPad();
	}
	else {
		fpDrawPad->SetClipRect( inViewRect );
	}
}

VWCustomCtrlDC::VWCustomCtrlDC(const VWCustomCtrlDC& scr)
{
}

VWCustomCtrlDC::~VWCustomCtrlDC()
{
	if ( farrPolyPts ) {
		delete (TPointsArray*) farrPolyPts;
		farrPolyPts		= NULL;
	}
}

VWCustomCtrlDC& VWCustomCtrlDC::operator=(const VWCustomCtrlDC& scr)
{
	return *this;
}

SintptrT VWCustomCtrlDC::GetOSDevice() const
{
	void*	dc	= 0;
	fpDrawPad->GetOSDeviceContext( dc );
	return (SintptrT) dc;
}

ViewCoord VWCustomCtrlDC::GetXOffset() const
{
	return fXOffset;
}

ViewCoord VWCustomCtrlDC::GetYOffset() const
{
	return fYOffset;
}

void VWCustomCtrlDC::SelectPen(const VWCustomCtrlPen& pen)
{
	fCurrentPen		= pen;

#ifdef _WINDOWS
	float scaleFactor = DPIDisplayAdjustment::DPIScaleFactor( WindowFromDC( reinterpret_cast<HDC>(GetOSDevice()) ) );
	fCurrentPen.SetSize( scaleFactor * fCurrentPen.GetSize() );
#endif
}

void VWCustomCtrlDC::SelectBrush(const VWCustomCtrlBrush& brush)
{
	fCurrentBrush	= brush;
}

void VWCustomCtrlDC::SelectFont(const VWCustomCtrlFont& font)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		DPFont	textFont;
		textFont.nameStr    = font.GetFontName();
		textFont.family		= kNoFamily;
		textFont.ptSize		= font.GetFontSize();
		textFont.bold		= font.GetBold();
		textFont.italic		= font.GetItalic();
		textFont.underline	= font.GetUnderlined();
#ifdef _WINDOWS
		textFont.outline	= 0;					// Mac only.
		textFont.shadow		= 0;					// Mac only.

		textFont.ptSize = DPIDisplayAdjustment::DPIScale( WindowFromDC( reinterpret_cast<HDC>( GetOSDevice() ) ), font.GetFontSize() );
#else
		textFont.outline	= font.GetOutline();	// Mac only.
		textFont.shadow		= font.GetShadow();		// Mac only.
#endif
		textFont.condense	= 0;		// Mac only, text pasted from other apps.
		textFont.extend		= 0;		// Mac only, text pasted from other apps.
		textFont._pad		= 0;

		fpDrawPad->SetTextFont( textFont );
		fpDrawPad->SetTextAngle( font.GetRotation(), font.GetBaselineMirror() );
	}
}

VWCustomCtrlPen	VWCustomCtrlDC::GetSelectedPen() const
{
#ifdef _WINDOWS
	float scaleFactor = DPIDisplayAdjustment::DPIScaleFactor( WindowFromDC( reinterpret_cast<HDC>(GetOSDevice()) ) );
	VWCustomCtrlPen pen(fCurrentPen);
	pen.SetSize(fCurrentPen.GetSize() / scaleFactor);
	return pen;
#else
	return fCurrentPen;
#endif
}

VWCustomCtrlBrush VWCustomCtrlDC::GetSelectedBrush() const
{
	return fCurrentBrush;
}

VWCustomCtrlFont VWCustomCtrlDC::GetSelectedFont() const
{
	VWCustomCtrlFont	currFont;

	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		DPFont		textFont;
		double		dAngle;
		bool		bMirror;

		fpDrawPad->GetTextFont( textFont );
		fpDrawPad->GetTextAngle( dAngle, bMirror );

#ifdef _WINDOWS
		float scaleFactor = DPIDisplayAdjustment::DPIScaleFactor( WindowFromDC( reinterpret_cast<HDC>(GetOSDevice()) ) );
		Uint32 ptSize = static_cast<Sint16>( textFont.ptSize/scaleFactor );
		currFont.SetFont( textFont.nameStr, ptSize );
#else
		currFont.SetFont( textFont.nameStr, textFont.ptSize );
#endif
		currFont.SetStyle( textFont.bold, textFont.italic, textFont.underline );
		currFont.SetRotation( dAngle );
		currFont.SetBaselineMirror( bMirror );
	}

	return currFont;
}

void VWCustomCtrlDC::SetClipRect(const ViewRect& rect)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		ViewRect	theRect	= rect;
		theRect.Offset( fXOffset, fYOffset );
		fpDrawPad->SetClipRect( theRect );
	}
}

const Sint16 k_solid_fore_pattern = 2;

void VWCustomCtrlDC::PrepForFrame()
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		fpDrawPad->SetPenF( fCurrentPen.GetSize(), fCurrentPen.GetColor(), fCurrentPen.GetColor(), k_solid_fore_pattern );
	}
}

void VWCustomCtrlDC::PrepForFrame(Uint8 red, Uint8 green, Uint8 blue)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		GSColor	tempColor;
		// This seems wrong, but we don't want to promote this to a 16bit color.
		// We just want to set the low order 8 bits for the color.
		tempColor.Set16( red, green, blue );
		fpDrawPad->SetPenF( fCurrentPen.GetSize(), tempColor, fCurrentPen.GetColor(), k_solid_fore_pattern );
	}
}

void VWCustomCtrlDC::PrepForFill()
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		fpDrawPad->SetPenF( fCurrentPen.GetSize(), fCurrentBrush.GetColor(), fCurrentBrush.GetBackgroundColor(), fCurrentBrush.GetPatternIndex() ? fCurrentBrush.GetPatternIndex() : k_solid_fore_pattern );
	}
}

void VWCustomCtrlDC::DrawLine(const ViewPt& fromPt, const ViewPt& toPt)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		this->PrepForFrame();

		fpDrawPad->DPMoveTo( fromPt.x + fXOffset, fromPt.y + fYOffset );
		fpDrawPad->DPLineTo( toPt.x + fXOffset, toPt.y + fYOffset );
	}
}

void VWCustomCtrlDC::DrawRect(const ViewRect& rect)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		ViewRect	theRect	= rect;
		theRect.Offset( fXOffset, fYOffset );
		this->PrepForFrame();

		fpDrawPad->FrameRect( theRect );
	}
}

void VWCustomCtrlDC::FillRect(const ViewRect& rect)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		ViewRect	theRect	= rect;
		theRect.Offset( fXOffset, fYOffset );

		this->PrepForFill();

		fpDrawPad->FillRect( theRect );

		this->PrepForFrame();
	}
}

Uint32 VWCustomCtrlDC::GetStringWidth(const TXString& string)
{
	Uint32		width	= 0;

	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		fpDrawPad->GetTextWidth( string, width );
	}

	return width;
}

void VWCustomCtrlDC::DrawString(const ViewPt& pt, const TXString& string)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		this->PrepForFrame();

		fpDrawPad->DPMoveTo( pt.x + fXOffset, pt.y + fYOffset );
		fpDrawPad->DrawTextString( string );
	}
}

void VWCustomCtrlDC::DrawString(const ViewPt& pt, const TXString& string, Uint8 red, Uint8 green, Uint8 blue)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		this->PrepForFrame( red, green, blue );

		fpDrawPad->DPMoveTo( pt.x + fXOffset, pt.y + fYOffset );
		fpDrawPad->DrawTextString( string );

		this->PrepForFrame();
	}
}

void VWCustomCtrlDC::DrawString_TXString(const ViewPt& pt, const TXString& string)
{
	this->DrawString( pt, string );
}

void VWCustomCtrlDC::DrawString_TXString(const ViewPt& pt, const TXString& string, Uint8 red, Uint8 green, Uint8 blue)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		this->PrepForFrame( red, green, blue );

		fpDrawPad->DPMoveTo( pt.x + fXOffset, pt.y + fYOffset );

        this->DrawString( pt, string );

		this->PrepForFrame();
	}
}

Uint32 VWCustomCtrlDC::GetStringWidth(ConstUCStrPtr uniString)
{
	Uint32		width	= 0;

	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		fpDrawPad->GetTextWidthN( uniString, width );
	}

	return width;
}

void VWCustomCtrlDC::DrawString(const ViewPt& pt, ConstUCStrPtr uniString)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		this->PrepForFrame();
		fpDrawPad->DPMoveTo( pt.x + fXOffset, pt.y + fYOffset );
		fpDrawPad->DrawTextStringN( uniString );
	}
}

void VWCustomCtrlDC::DrawString(const ViewPt& pt, ConstUCStrPtr uniString, Uint8 red, Uint8 green, Uint8 blue)
{
	if ( VERIFYN( kVStanev, fpDrawPad ) ) {
		this->PrepForFrame( red, green, blue );

		fpDrawPad->DPMoveTo( pt.x + fXOffset, pt.y + fYOffset );
		fpDrawPad->DrawTextStringN( uniString );

		this->PrepForFrame();
	}
}

void VWCustomCtrlDC::BitBlt(const ViewRect& destRect, const VWCustomCtrlDC& srcDC, const ViewPt& srcPt, EDrawPadTransferMode mode)
{
	if ( VERIFYN( kVStanev, fpDrawPad && srcDC.fpDrawPad ) ) {
		GSRect32		gsSrcRect	( srcPt.x, srcPt.y, srcPt.x + destRect.Width(), srcPt.y + destRect.Height() );
		GSRect32		gsDestRect	( destRect.left + fXOffset, destRect.top + fYOffset, destRect.right + fXOffset, destRect.bottom + fYOffset );
		srcDC.fpDrawPad->CopyBitsOut( gsSrcRect, fpDrawPad, gsDestRect, mode );
	}
}

void VWCustomCtrlDC::BitBlt(const ViewRect& destRect, const VWCustomCtrlDC& srcDC, const ViewRect& srcRect, EDrawPadTransferMode mode)
{
	if ( VERIFYN( kVStanev, fpDrawPad && srcDC.fpDrawPad ) ) {
		GSRect32		gsSrcRect	( srcRect.left, srcRect.top, srcRect.right, srcRect.bottom );
		GSRect32		gsDestRect	( destRect.left + fXOffset, destRect.top + fYOffset, destRect.right + fXOffset, destRect.bottom + fYOffset );
		srcDC.fpDrawPad->CopyBitsOut( gsSrcRect, fpDrawPad, gsDestRect, mode );
	}
}

void VWCustomCtrlDC::PathBegin()
{
	TPointsArray*	pPtsArray	= (TPointsArray*) farrPolyPts;
	if ( pPtsArray ) {
		pPtsArray->clear();
	}
}

void VWCustomCtrlDC::PathMoveTo(Sint16 x, Sint16 y)
{
	TPointsArray*	pPtsArray	= (TPointsArray*) farrPolyPts;
	if ( pPtsArray ) {
		SVisualPoint	pt;
		pt.bVisible			= false;
		pt.pt.x				= x;
		pt.pt.y				= y;

		pPtsArray->push_back( pt );
	}
}

void VWCustomCtrlDC::PathLineTo(Sint16 x, Sint16 y)
{
	TPointsArray*	pPtsArray	= (TPointsArray*) farrPolyPts;
	if ( pPtsArray ) {
		SVisualPoint	pt;
		pt.bVisible			= true;
		pt.pt.x				= x;
		pt.pt.y				= y;

		pPtsArray->push_back( pt );
	}
}

void VWCustomCtrlDC::PathEndDraw()
{
	TPointsArray*	pPtsArray	= (TPointsArray*) farrPolyPts;
	if ( pPtsArray ) {
		ViewPt	lastPt;
		size_t	ptsCnt	= pPtsArray->size();
		for(size_t i=0; i<ptsCnt; i++) {
			const SVisualPoint& pt	= (*pPtsArray)[ i ];

			if ( i != 0 && pt.bVisible ) {
				this->DrawLine( lastPt, pt.pt );
			}
			
			lastPt		= pt.pt;
		}
	}
}

void VWCustomCtrlDC::PathEndDrawAndFill()
{
	TPointsArray*	pPtsArray	= (TPointsArray*) farrPolyPts;

	if ( pPtsArray && fpDrawPad ) {
		GSPolyRef	polyRef;

		if ( VCOM_SUCCEEDED( fpDrawPad->CreatePoly( polyRef ) ) ) {
			ViewPt	lastPt;
			size_t	ptsCnt	= pPtsArray->size();

			for(size_t i=0; i<ptsCnt; i++) {
				const SVisualPoint& pt	= (*pPtsArray)[ i ];

				ViewPt				thePt;
				thePt.x					= pt.pt.x + fXOffset;
				thePt.y					= pt.pt.y + fYOffset;
				fpDrawPad->AddPolyPt( polyRef, thePt );

				if ( i != 0 && pt.bVisible ) {
					this->DrawLine( lastPt, pt.pt );
				}
				
				lastPt		= pt.pt;
			}

			this->PrepForFill();
			fpDrawPad->FillPoly( polyRef );

			fpDrawPad->ReleasePoly( polyRef );

			this->PrepForFrame();
		}
	}
}

void VWCustomCtrlDC::PathEndFill()
{
	TPointsArray*	pPtsArray	= (TPointsArray*) farrPolyPts;

	if ( pPtsArray && fpDrawPad ) {
		GSPolyRef	polyRef;

		if ( VCOM_SUCCEEDED( fpDrawPad->CreatePoly( polyRef ) ) ) {
			size_t	ptsCnt	= pPtsArray->size();

			for(size_t i=0; i<ptsCnt; i++) {
				const SVisualPoint& pt	= (*pPtsArray)[ i ];

				ViewPt thePt(pt.pt.x + fXOffset, pt.pt.y + fYOffset);
				fpDrawPad->AddPolyPt( polyRef, thePt );
			}

			this->PrepForFill();
			fpDrawPad->FillPoly( polyRef );

			fpDrawPad->ReleasePoly( polyRef );

			this->PrepForFrame();
		}
	}
}

void VWCustomCtrlDC::PathEndFillAndDraw()
{
	TPointsArray*	pPtsArray	= (TPointsArray*) farrPolyPts;

	if ( pPtsArray && fpDrawPad ) {
		GSPolyRef	polyRef;

		if ( VCOM_SUCCEEDED( fpDrawPad->CreatePoly( polyRef ) ) ) {
			size_t	ptsCnt	= pPtsArray->size();

			for(size_t i=0; i<ptsCnt; i++) {
				const SVisualPoint& pt	= (*pPtsArray)[ i ];

				ViewPt thePt(pt.pt.x + fXOffset, pt.pt.y + fYOffset);
				fpDrawPad->AddPolyPt( polyRef, thePt );
			}

			this->PrepForFill();
			fpDrawPad->FillPoly( polyRef );

			fpDrawPad->ReleasePoly( polyRef );

			this->PrepForFrame();

			ViewPt	lastPt;

			for (size_t i=0; i<ptsCnt; i++) {
				const SVisualPoint& pt	= (*pPtsArray)[ i ];
				
				if ( i != 0 && pt.bVisible ) {
					this->DrawLine( lastPt, pt.pt );
				}
				
				lastPt		= pt.pt;
			}
		}
	}
}

void VWCustomCtrlDC::DrawSymbolPreview(	InternalIndex resourceRefNum,
										const ViewRect& destRect,
										ECustomDCPreviewMode viewMode,
										ECustomDCRenderMode renderMode)
{
	gSDK->DrawSymbolPreview( fpDrawPad, resourceRefNum, destRect, (short) viewMode, (short) renderMode );
}

void VWCustomCtrlDC::DrawSymbolPreview(	InternalIndex resourceRefNum,
										const ViewRect& destRect,
										ViewRect& outDrawnBounts,
										ECustomDCPreviewMode viewMode,
										ECustomDCRenderMode renderMode)
{
	gSDK->DrawSymbolPreview( fpDrawPad, resourceRefNum, destRect, (short) viewMode, (short) renderMode, & outDrawnBounts );
}

void VWCustomCtrlDC::DrawIcon(const ViewPt& pt, VectorWorks::UI::IIcon* pIcon)
{
	if ( pIcon == NULL )
		return;

	Sint16		iconWidth	= 0;
	Sint16		iconHeight	= 0;
	pIcon->GetDimensions( iconWidth, iconHeight );

	bool isSet = false;
	VERIFYN( kVStanev, VCOM_SUCCEEDED( pIcon->IsSet( isSet ) ) );
	if ( isSet ) {

#ifdef _WINDOWS
		void* pNativeIcon	= NULL;
		if ( VERIFYN(kVStanev, VCOM_SUCCEEDED( pIcon->GetNativeIcon( pNativeIcon ) ) ) ) { // has to be GetScaledNativeIcon
			HICON	hIcon	= (HICON) pNativeIcon;
			HDC		hDC		= (HDC) this->GetOSDevice();

			if ( hDC && hIcon ) {
				::DrawState( hDC, NULL, NULL, (LPARAM)hIcon, NULL, pt.x, pt.y, 0, 0, DST_ICON | DSS_NORMAL);
			}
		}
#else
		VectorWorks::Imaging::ImageStream imgStreamData;
		imgStreamData.bufferPtr = nullptr;
		imgStreamData.bufferSizeInBytes = 0;
		imgStreamData.bufferRetinaPtr = nullptr;
		imgStreamData.bufferSizeRetinaInBytes = 0;
		imgStreamData.compressionType = VectorWorks::Imaging::ePNG;

		// Get the data size then alloc memory.
		size_t buffSize = 0;
        size_t buffSizeRetina = 0;
		pIcon->GetPngData(nil, buffSize, nil, buffSizeRetina);
		imgStreamData.bufferSizeInBytes = buffSize;
        imgStreamData.bufferSizeRetinaInBytes = buffSizeRetina;

		try {
			imgStreamData.bufferPtr = new Uint8[imgStreamData.bufferSizeInBytes];
            imgStreamData.bufferRetinaPtr = new Uint8[imgStreamData.bufferSizeRetinaInBytes];
		} catch (Sint32) {
			return;
		}

		if ( VERIFYN( kVStanev, VCOM_SUCCEEDED( pIcon->GetPngData( imgStreamData.bufferPtr, buffSize, imgStreamData.bufferRetinaPtr, buffSizeRetina)))) {
			
			VectorWorks::Imaging::ICompressedImagePtr pICompImage(VectorWorks::Imaging::IID_CompressedImage);
			if ( VCOM_SUCCEEDED( pICompImage->CreateFromStream( imgStreamData) ) ) {

				if (pICompImage->IsInitialized()) {
					VERIFYN( kVStanev, VCOM_SUCCEEDED( fpDrawPad->DrawCompressedImage( pt, pICompImage)));
				}
			}
		}
		delete [] (Uint8*)imgStreamData.bufferPtr;
        delete [] (Uint8*)imgStreamData.bufferRetinaPtr;
#endif
	}
}

void VWCustomCtrlDC::DrawIcon(const ViewRect& rect, VectorWorks::UI::IIcon* pIcon)
{
	if ( pIcon == NULL )
		return;

	Sint16		iconWidth	= 0;
	Sint16		iconHeight	= 0;
	pIcon->GetDimensions( iconWidth, iconHeight );

	bool isSet = false;
	VERIFYN( kVStanev, VCOM_SUCCEEDED( pIcon->IsSet( isSet ) ) );
	if ( isSet ) {

		VectorWorks::Imaging::ImageStream imgStreamData;
		imgStreamData.bufferPtr = nullptr;
		imgStreamData.bufferSizeInBytes = 0;
		imgStreamData.bufferRetinaPtr = nullptr;
		imgStreamData.bufferSizeRetinaInBytes = 0;
		imgStreamData.compressionType = VectorWorks::Imaging::ePNG;

		// Get the data size then alloc memory.
		size_t buffSize = 0;
        size_t buffSizeRetina = 0;
		pIcon->GetPngData(nil, buffSize, nil, buffSizeRetina);
		imgStreamData.bufferSizeInBytes = (Uint32)buffSize;
        imgStreamData.bufferSizeRetinaInBytes = (Uint32)buffSizeRetina;

		try {
			imgStreamData.bufferPtr = SDK_NEW Uint8[imgStreamData.bufferSizeInBytes];
            imgStreamData.bufferRetinaPtr = SDK_NEW Uint8[imgStreamData.bufferSizeRetinaInBytes];
		} catch (Sint32) {
			return;
		}

		if ( VERIFYN( kVStanev, VCOM_SUCCEEDED( pIcon->GetPngData( imgStreamData.bufferPtr, buffSize, imgStreamData.bufferRetinaPtr, buffSizeRetina)))) {
			
			VectorWorks::Imaging::ICompressedImagePtr pICompImage(VectorWorks::Imaging::IID_CompressedImage);
			if ( VCOM_SUCCEEDED( pICompImage->CreateFromStream( imgStreamData) ) ) {

				if (pICompImage->IsInitialized()) {
					VERIFYN( kVStanev, VCOM_SUCCEEDED( fpDrawPad->DrawCompressedImage( rect, pICompImage)));
				}
			}
		}
		delete [] (Uint8*)imgStreamData.bufferPtr;
        delete [] (Uint8*)imgStreamData.bufferRetinaPtr;

	}
}





