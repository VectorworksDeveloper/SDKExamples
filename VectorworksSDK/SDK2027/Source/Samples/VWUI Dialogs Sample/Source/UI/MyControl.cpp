#include "StdAfx.h"

#include "MyControl.h"

using namespace UI;

CMyControl::CMyControl(TControlID id, bool bUseDefault) :
	VWCustomCtrl( id, bUseDefault ),
	fIcon( VectorWorks::UI::IID_Icon )
{
}

CMyControl::~CMyControl()
{
}

void CMyControl::OnControlAttached()
{
	fIcon->SetFromResourceSpecifier("VWUI Dialogs Sample/Images/Image.png");

	this->EnableToolTips( true );

	SCustomCtrlToolTip	toolTip1;
	toolTip1.fText			= "this is my tool tip\nsecond line tool tip";
	toolTip1.fPos.Set( 10, 10 );
	this->AddToolTip( toolTip1 );

	SCustomCtrlToolTip	toolTip2;
	toolTip2.fText			= "region tool tip";
	toolTip2.fRect			= ViewRect( 15, 15, 55, 55 );
	toolTip2.fbTrackMouse	= true;
	this->AddToolTip( toolTip2 );

	SCustomCtrlToolTip	toolTip3;
	toolTip3.fText			= "another region tool tip";
	toolTip3.fRect			= ViewRect( 55, 15, 105, 55 );
	this->AddToolTip( toolTip3 );
}

void CMyControl::OnPaint(VWCustomCtrlDC& dc)
{
	VWCustomCtrlFont	fontSmall( "Arial", 9, false, false, false );
	VWCustomCtrlFont	font( "Arial", 12, true, false, true );
	font.SetRotation( 45 );

	ViewCoord		ctrlWidth		= this->GetControlWidth();
	ViewCoord		ctrlHeight		= this->GetControlHeight();
	VWCustomCtrlDC	backbufferDC( ctrlWidth, ctrlHeight );

	backbufferDC.SelectPen( VWCustomCtrlPen( 0, 0, 255 ) );
	backbufferDC.SelectBrush( VWCustomCtrlBrush( 255, 0, 0 ) );
	backbufferDC.DrawLine( ViewPt(0, 0), ViewPt(70, 70) );
	backbufferDC.FillRect( ViewRect( 10, 10, 50, 50 ) );
	backbufferDC.DrawRect( ViewRect( 15, 15, 55, 55 ) );

	VWCustomCtrlDC	offscreen( 20, 20 );
	offscreen.SelectBrush( VWCustomCtrlBrush( 255, 255, 0 ) );
	offscreen.FillRect( ViewRect( 0, 0, 20, 20 ) );
	offscreen.SelectPen( VWCustomCtrlPen( 0, 255, 0 ) );
	offscreen.SelectBrush( VWCustomCtrlBrush( 0, 255, 255 ) );
	offscreen.DrawLine( ViewPt(10, 10), ViewPt(20, 20) );
	offscreen.FillRect( ViewRect( 5, 5, 10, 10 ) );

	ViewRect	srcRc( 0, 0, 20, 20 );
	ViewRect	destRc( 10, 10, 30, 30 );
	backbufferDC.BitBlt( destRc, offscreen, srcRc );

	backbufferDC.PathBegin();
	backbufferDC.PathMoveTo( 70, 70 );
	backbufferDC.PathLineTo( 110, 110 );
	backbufferDC.PathLineTo( 20, 100 );
	backbufferDC.PathLineTo( 70, 70 );
	backbufferDC.PathEndFillAndDraw();

	backbufferDC.DrawIcon( ViewPt(0,0), fIcon );

	TXString	objName("sym");
	MCObjectHandle	hSymObj		= gSDK->GetNamedObject( objName );
	if ( hSymObj ) {
		InternalIndex	resIndex	= gSDK->GetObjectInternalIndex( hSymObj );
		backbufferDC.DrawSymbolPreview( resIndex, ViewRect( 30, 30, 80, 80 ), kCustomDCPreviewMode_LeftRearIso, kCustomDCRenderMode_OpenGL );
	}

	backbufferDC.SelectFont( fontSmall );
	backbufferDC.DrawString( ViewPt(55,10), "Dbl click to disable tooltips!" );

	if ( ! fstrText.IsEmpty() ) {
		backbufferDC.SelectFont( font );
		backbufferDC.DrawString( fptText, fstrText );
	}

	dc.BitBlt( ViewRect(0,0, ctrlWidth, ctrlHeight), backbufferDC, ViewPt(0,0) );

	this->UpdateScrollArea( 10, 0, 0, 0, 1, true, true, true );
}

void CMyControl::OnMouseMoved(const SCustomCtrlMouseEvent& event)
{
	fptText.x		= event.x;
	fptText.y		= event.y;
	fstrText.Format( "x=%d y=%d s=%d c=%d", event.x, event.y, event.bShiftDown, event.bCtrlDown );
	
	this->Refresh();
}

void CMyControl::OnMouseDown(const SCustomCtrlMouseEvent& event)
{
	fptText.x		= event.x;
	fptText.y		= event.y;
	fstrText.Format( "OnMouseDown: x=%d y=%d s=%d c=%d", event.x, event.y, event.bShiftDown, event.bCtrlDown );

//	::GS_AlertInform( gCBP, fstrText );
}

void CMyControl::OnMouseUp(const SCustomCtrlMouseEvent& event)
{
	fptText.x		= event.x;
	fptText.y		= event.y;
	fstrText.Format( "OnMouseUp: x=%d y=%d s=%d c=%d", event.x, event.y, event.bShiftDown, event.bCtrlDown );

//	::GS_AlertInform( gCBP, fstrText );
}

void CMyControl::OnMouseDblClick(const SCustomCtrlMouseEvent& event)
{
	fptText.x		= event.x;
	fptText.y		= event.y;
	fstrText.Format( "OnMouseDblClick: x=%d y=%d s=%d c=%d", event.x, event.y, event.bShiftDown, event.bCtrlDown );

	this->EnableToolTips( false );

	::GS_AlertInform( gCBP, fstrText );
}

void CMyControl::OnMouseWheel(const SCustomCtrlMouseEvent& event, Sint16 deltaX, Sint16 deltaY)
{
	fptText.x		= event.x;
	fptText.y		= event.y;
	fstrText.Format( "OnMouseWheel: x=%d y=%d dx=%d dy=%d s=%d c=%d", event.x, event.y, deltaX, deltaY, event.bShiftDown, event.bCtrlDown );

	::GS_AlertInform( gCBP, fstrText );
}
 
void CMyControl::OnKeyDown(const SCustomCtrlKeyEvent& event)
{
	TXString	szType;
	switch( event.keyType ) {
		case kKeyType_Unknown:		szType = "Unknown";		break;
		case kKeyType_Shift:		szType = "Shift";		break;
		case kKeyType_Control:		szType = "Control";		break;
		case kKeyType_Space:		szType = "Space";		break;
		case kKeyType_Enter:		szType = "Enter";		break;
		case kKeyType_Escape:		szType = "Escape";		break;
		case kKeyType_Insert:		szType = "Insert";		break;
		case kKeyType_Delete:		szType = "Delete";		break;
		case kKeyType_BackSpace:	szType = "BackSpace";	break;
		case kKeyType_Home:			szType = "Home";		break;
		case kKeyType_End:			szType = "End";			break;
		case kKeyType_PageUp:		szType = "PageUp";		break;
		case kKeyType_PageDown:		szType = "PageDown";	break;
		case kKeyType_Tab:			szType = "Tab";			break;
		case kKeyType_Left:			szType = "Left";		break;
		case kKeyType_Right:		szType = "Right";		break;
		case kKeyType_Up:			szType = "Up";			break;
		case kKeyType_Down:			szType = "Down";		break;
		case kKeyType_F1:			szType = "F1";			break;
		case kKeyType_F2:			szType = "F2";			break;
		case kKeyType_F3:			szType = "F3";			break;
		case kKeyType_F4:			szType = "F4";			break;
		case kKeyType_F5:			szType = "F5";			break;
		case kKeyType_F6:			szType = "F6";			break;
		case kKeyType_F7:			szType = "F7";			break;
		case kKeyType_F8:			szType = "F8";			break;
		case kKeyType_F9:			szType = "F9";			break;
		case kKeyType_F10:			szType = "F10";			break;
		case kKeyType_F11:			szType = "F11";			break;
		case kKeyType_F12:			szType = "F12";			break;
	}

	TXString str;
	str.Format( "OnKeyDown: type=%s code=0x%X char=%c", (const char*)szType, event.keyCode, (char)event.keyCode );
	::GS_AlertInform( gCBP, str );
}

void CMyControl::OnKeyUp(const SCustomCtrlKeyEvent& event)
{
	TXString	szType;
	switch( event.keyType ) {
		case kKeyType_Unknown:		szType = "Unknown";		break;
		case kKeyType_Shift:		szType = "Shift";		break;
		case kKeyType_Control:		szType = "Control";		break;
		case kKeyType_Space:		szType = "Space";		break;
		case kKeyType_Enter:		szType = "Enter";		break;
		case kKeyType_Escape:		szType = "Escape";		break;
		case kKeyType_Insert:		szType = "Insert";		break;
		case kKeyType_Delete:		szType = "Delete";		break;
		case kKeyType_BackSpace:	szType = "BackSpace";	break;
		case kKeyType_Home:			szType = "Home";		break;
		case kKeyType_End:			szType = "End";			break;
		case kKeyType_PageUp:		szType = "PageUp";		break;
		case kKeyType_PageDown:		szType = "PageDown";	break;
		case kKeyType_Tab:			szType = "Tab";			break;
		case kKeyType_Left:			szType = "Left";		break;
		case kKeyType_Right:		szType = "Right";		break;
		case kKeyType_Up:			szType = "Up";			break;
		case kKeyType_Down:			szType = "Down";		break;
		case kKeyType_F1:			szType = "F1";			break;
		case kKeyType_F2:			szType = "F2";			break;
		case kKeyType_F3:			szType = "F3";			break;
		case kKeyType_F4:			szType = "F4";			break;
		case kKeyType_F5:			szType = "F5";			break;
		case kKeyType_F6:			szType = "F6";			break;
		case kKeyType_F7:			szType = "F7";			break;
		case kKeyType_F8:			szType = "F8";			break;
		case kKeyType_F9:			szType = "F9";			break;
		case kKeyType_F10:			szType = "F10";			break;
		case kKeyType_F11:			szType = "F11";			break;
		case kKeyType_F12:			szType = "F12";			break;
	}

	TXString str;
	str.Format( "OnKeyUp: type=%s code=0x%X char=%c", (const char*)szType, event.keyCode, (char)event.keyCode );
	::GS_AlertInform( gCBP, str );
}

void CMyControl::OnChar(const SCustomCtrlKeyEvent& event)
{
	TXString	szType;
	switch( event.keyType ) {
		case kKeyType_Unknown:		szType = "Unknown";		break;
		case kKeyType_Shift:		szType = "Shift";		break;
		case kKeyType_Control:		szType = "Control";		break;
		case kKeyType_Space:		szType = "Space";		break;
		case kKeyType_Enter:		szType = "Enter";		break;
		case kKeyType_Escape:		szType = "Escape";		break;
		case kKeyType_Insert:		szType = "Insert";		break;
		case kKeyType_Delete:		szType = "Delete";		break;
		case kKeyType_BackSpace:	szType = "BackSpace";	break;
		case kKeyType_Home:			szType = "Home";		break;
		case kKeyType_End:			szType = "End";			break;
		case kKeyType_PageUp:		szType = "PageUp";		break;
		case kKeyType_PageDown:		szType = "PageDown";	break;
		case kKeyType_Tab:			szType = "Tab";			break;
		case kKeyType_Left:			szType = "Left";		break;
		case kKeyType_Right:		szType = "Right";		break;
		case kKeyType_Up:			szType = "Up";			break;
		case kKeyType_Down:			szType = "Down";		break;
		case kKeyType_F1:			szType = "F1";			break;
		case kKeyType_F2:			szType = "F2";			break;
		case kKeyType_F3:			szType = "F3";			break;
		case kKeyType_F4:			szType = "F4";			break;
		case kKeyType_F5:			szType = "F5";			break;
		case kKeyType_F6:			szType = "F6";			break;
		case kKeyType_F7:			szType = "F7";			break;
		case kKeyType_F8:			szType = "F8";			break;
		case kKeyType_F9:			szType = "F9";			break;
		case kKeyType_F10:			szType = "F10";			break;
		case kKeyType_F11:			szType = "F11";			break;
		case kKeyType_F12:			szType = "F12";			break;
	}

	TXString str;
	str.Format( "OnChar: type=%s code=0x%X char=%c", (const char*) szType, event.keyCode, (char)event.keyCode );
	::GS_AlertInform( gCBP, str );
}



