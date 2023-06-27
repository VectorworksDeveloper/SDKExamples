//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/CustomCtrl.h"
#include "VWFC/VWUI/Dialog.h"

#include <map>


#if _MINICAD_
	#ifdef _WINDOWS
	# include <commctrl.h>
	#endif
#endif

using namespace VWFC::VWUI;

SCustomCtrlToolTip::SCustomCtrlToolTip()
{
	fRect.MakeEmpty();
	fbTrackMouse		= false;
	fPos.Set( -1, -1 );
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
VWCustomCtrl::VWCustomCtrl(TControlID id, bool bDefaultPaint)
	: VWControl( id )
	, fMouseCursorAPI( UI::IID_MouseCursorManager )
{
	fParentDialogID		= 0;

#ifdef _WINDOWS
	fhParentWnd						= NULL;
	fhCustomWnd						= NULL;
	fpDefaultWndProc				= NULL;
	fpToolTipItem					= NULL;
	fhToolTip						= NULL;
	fbTrackingMouse					= false;
	fbSendMouseEnterNotification	= true;
#else
	fParentWnd			= NULL;
#endif

	fbDefaultPaint		= bDefaultPaint;
	fpActiveToolTip		= NULL;
	fbToolTipsEnabled	= false;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
VWCustomCtrl::~VWCustomCtrl()
{
	this->DettachControl();
	
#ifdef _WINDOWS
	if ( fhToolTip ) {
		DestroyWindow( fhToolTip );
	}
	if ( fpToolTipItem ) {
		TOOLINFO*	pToolTip = (TOOLINFO*) fpToolTipItem;
		if ( pToolTip->lpszText ) {
			delete pToolTip->lpszText;
		}

		free( pToolTip );
		pToolTip	= NULL;
	}
	fpToolTipItem	= NULL;
	fhToolTip		= NULL;
#else
#endif
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::AttachControl(TControlID dialogID)
{
	fParentDialogID	= dialogID;

	this->AttachControl();
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
bool VWCustomCtrl::CreateControl(VWDialog* pDlg, Uint16 width, Uint16 height)
{
	::GS_CreateCustomControl( gCBP, pDlg->GetControlID(), fControlID, width, height );
	return VWControl::CreateControl( pDlg );
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnControlAttached()
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnAfterPaint()
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
bool VWCustomCtrl::OnEvent(SCustomCtrlGeneralEvent& event)
{
	return false;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseMoved(const SCustomCtrlMouseEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseDown(const SCustomCtrlMouseEvent& event)
{
	if ( fpParentDlg ) {
		Sint32        controlID    = fControlID;
		Sint32		cusotmCtrlPos[3] = { -1, event.x, event.y };

		// call the dialog to dispatch normal event to the dialog
		// though the event map, as if the control is being click and the message
		fpParentDlg->LocalDialogEventHandler( controlID, cusotmCtrlPos );
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseUp(const SCustomCtrlMouseEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseClick(const SCustomCtrlMouseEvent& event)
{
	if ( fpParentDlg ) {
		Sint32        controlID    = fControlID;
		Sint32		cusotmCtrlPos[3] = { 0, event.x, event.y };

		// call the dialog to dispatch normal event to the dialog
		// though the event map, as if the control is being click and the message
		fpParentDlg->LocalDialogEventHandler( controlID, cusotmCtrlPos );
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseDblClick(const SCustomCtrlMouseEvent& event)
{
	if ( fpParentDlg ) {
		Sint32        controlID    = -fControlID;
		Sint32		cusotmCtrlPos[3] = { 10, event.x, event.y };

		// call the dialog to dispatch normal event to the dialog
		// though the event map, as if the control is being click and the message
		fpParentDlg->LocalDialogEventHandler( controlID, cusotmCtrlPos );
	}
}
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseRDown(const SCustomCtrlMouseEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseRUp(const SCustomCtrlMouseEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseRClick(const SCustomCtrlMouseEvent& event)
{
	if ( fpParentDlg ) {
		Sint32        controlID	= fControlID;
		Sint32		cusotmCtrlData[3] = { 1, event.x, event.y };
		// call the dialog to dispatch normal event to the dialog
		// though the event map, as if the control is being click and the message
		fpParentDlg->LocalDialogEventHandler( controlID, cusotmCtrlData );
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseRDblClick(const SCustomCtrlMouseEvent& event)
{
	if ( fpParentDlg ) {
		Sint32        controlID	= -fControlID;
		Sint32		cusotmCtrlData[3] = { 11, event.x, event.y };
		// call the dialog to dispatch normal event to the dialog
		// though the event map, as if the control is being click and the message
		fpParentDlg->LocalDialogEventHandler( controlID, cusotmCtrlData );
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseMDown(const SCustomCtrlMouseEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseMUp(const SCustomCtrlMouseEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseMClick(const SCustomCtrlMouseEvent& event)
{
	if ( fpParentDlg ) {
		Sint32        controlID	= fControlID;
		Sint32		cusotmCtrlData[3] = { 2, event.x, event.y };
		// call the dialog to dispatch normal event to the dialog
		// though the event map, as if the control is being click and the message
		fpParentDlg->LocalDialogEventHandler( controlID, cusotmCtrlData );
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseMDblClick(const SCustomCtrlMouseEvent& event)
{
	if ( fpParentDlg ) {
		Sint32        controlID	= -fControlID;
		Sint32		cusotmCtrlData[3] = { 2, event.x, event.y };
		// call the dialog to dispatch normal event to the dialog
		// though the event map, as if the control is being click and the message
		fpParentDlg->LocalDialogEventHandler( controlID, cusotmCtrlData );
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void  VWCustomCtrl::OnMouseWheel(const SCustomCtrlMouseEvent& event, Sint16 deltaX, Sint16 deltaY)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseEnter(const SCustomCtrlMouseEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnMouseLeave(const SCustomCtrlMouseEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnKeyDown(const SCustomCtrlKeyEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnKeyUp(const SCustomCtrlKeyEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::OnChar(const SCustomCtrlKeyEvent& event)
{
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
bool VWCustomCtrl::OnToolTip(size_t id, SCustomCtrlToolTip& inoutToolTip)
{
	return true;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::Refresh()
{
	Sint32	dialogID	= fpParentDlg ? fpParentDlg->GetDialogID() : fParentDialogID;
	if ( dialogID != 0 )
		::GS_RefreshItem( gCBP, dialogID, fControlID ); 
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::UpdateScrollArea(Sint32 width, Sint32 height, Sint32 leftStart, Sint32 topStart, Sint32 stepSize, bool bLiveUpdate, bool bAlwaysShowHoriz, bool bAlwaysShowVert)
{
    Sint32 dialogID = fpParentDlg ? fpParentDlg->GetDialogID() : fParentDialogID;
	   
	if ( dialogID ) {
		::GS_UpdateCustomControlScrollArea( gCBP, dialogID, fControlID, width, height, leftStart, topStart, stepSize, bLiveUpdate, bAlwaysShowHoriz, bAlwaysShowVert );

#if GS_MAC
		Sint32 l, t, r, b;
		::GS_GetComponentRect( gCBP, dialogID, fControlID, l, t, r, b);
		fControlRect.left = l;
		fControlRect.top = t;
		fControlRect.right = r;
		fControlRect.bottom = b;
#endif
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::GetScrollArea(Sint32& outLeftStart, Sint32& outTopStart)
{
	Sint32	dialogID	= fpParentDlg ? fpParentDlg->GetDialogID() : fParentDialogID;
	::GS_GetCustomControlScrollArea(gCBP, dialogID, fControlID, & outLeftStart, & outTopStart );
}


//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
ViewCoord VWCustomCtrl::GetControlWidth() const
{
#ifdef _WINDOWS
	RECT r;
	::GetClientRect( fhCustomWnd, & r );
	return (ViewCoord) (r.right - r.left);
#else
	return (ViewCoord)(fControlRect.right - fControlRect.left);
#endif
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
ViewCoord VWCustomCtrl::GetControlHeight() const
{
#ifdef _WINDOWS
	RECT r;
	::GetClientRect( fhCustomWnd, & r );
	return (ViewCoord) (r.bottom - r.top);
#else
	return (ViewCoord)(fControlRect.bottom - fControlRect.top);
#endif
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
ViewRect VWCustomCtrl::GetControlRect() const
{
#if GS_WIN
	return fCustomCtrlRect;
#else
	ViewRect	rc;
	rc.left		= fControlRect.left;
	rc.right	= fControlRect.right;
	rc.top		= fControlRect.top;
	rc.bottom	= fControlRect.bottom;
	return rc;
#endif
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
SintptrT VWCustomCtrl::GetOSParentHandle() const
{
#if GS_WIN
	return (SintptrT) fhParentWnd;
#else
	return (SintptrT) fParentWnd;
#endif
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
SintptrT VWCustomCtrl::GetOSControlHandle() const
{
#if GS_WIN
	return (SintptrT) fhCustomWnd;
#else
	return (SintptrT) fControlRef;
#endif
}



//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::EnableToolTips(bool bEnable)
{
	fbToolTipsEnabled	= bEnable;

#if GS_WIN
	if ( fpToolTipItem == NULL ) {
		fpToolTipItem			= malloc( sizeof(TOOLINFO) );

		TOOLINFO*	pToolTip	= (TOOLINFO*) fpToolTipItem;
		memset( pToolTip, 0, sizeof(TOOLINFO) );

		// Create a ToolTip.
		fhToolTip = CreateWindowEx(	WS_EX_TOPMOST,
									TOOLTIPS_CLASS, NULL,
									WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,		
									CW_USEDEFAULT, CW_USEDEFAULT,
									CW_USEDEFAULT, CW_USEDEFAULT,
									fhParentWnd,
									NULL, (HINSTANCE) NULL, NULL );

		DSTOPIF( fhToolTip == NULL, (kVStanev, "Cannot create tooltip window.") );
		if ( fhToolTip ) {   
			// Set up tool information.
			// In this case, the "tool" is the entire parent window.
			pToolTip->cbSize	= sizeof(TOOLINFO);
			pToolTip->uFlags	= TTF_IDISHWND | TTF_TRACK | TTF_ABSOLUTE | TTF_SUBCLASS | TTF_TRANSPARENT;
			pToolTip->hwnd		= fhParentWnd;
			pToolTip->hinst		= (HINSTANCE) NULL;
			pToolTip->lpszText	= SDK_NEW wchar_t[ 1024 ];
			pToolTip->lpszText[0] = 0;
			pToolTip->uId		= (UINT_PTR) fhParentWnd;
			GetClientRect( fhParentWnd, & pToolTip->rect );

			// Associate the ToolTip with the tool window.
			SendMessage( fhToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) pToolTip );
		}
		else {
			delete pToolTip;
			fpToolTipItem	= NULL;
		}
	}

	if ( ! fbToolTipsEnabled ) {
		if ( fpActiveToolTip ) {
			if ( ! fpActiveToolTip->fbCustomPos ) {
				fpActiveToolTip->fToolTip.fPos.Set( -1, -1 );
			}
			fpActiveToolTip		= NULL;
		}

		Sint32	initial	= GetDoubleClickTime();
		Sint32	autopop	= GetDoubleClickTime() * 10;
		Sint32	reshow	= GetDoubleClickTime() / 5;

		SendMessage( fhToolTip, TTM_SETDELAYTIME, TTDT_INITIAL,		MAKELONG(initial, 0) ); 
		SendMessage( fhToolTip, TTM_SETDELAYTIME, TTDT_AUTOPOP,		MAKELONG(autopop, 0) ); 
		SendMessage( fhToolTip, TTM_SETDELAYTIME, TTDT_RESHOW,		MAKELONG(reshow, 0) ); 
		//SendMessage( fhToolTip, TTM_SETDELAYTIME, TTDT_AUTOMATIC,	MAKELONG(, 0) );

		SendMessage( fhToolTip, TTM_SETMAXTIPWIDTH, 0, 300 );

		SendMessage( fhToolTip, TTM_TRACKACTIVATE, (WPARAM) FALSE, (LPARAM) (TOOLINFO*) fpToolTipItem );
		fbTrackingMouse		= false;
	}
#else

#endif
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::ClearActiveTooltip( void )
{
	if ( fpActiveToolTip ) {
		if ( !fpActiveToolTip->fbCustomPos ) {
			fpActiveToolTip->fToolTip.fPos.Set( -1, -1 );
		}
		
		fpActiveToolTip		= NULL;
	}
}



void VWCustomCtrl::RemoveAllToolTips()
{
#if GS_MAC
    Sint32 dialogID = fpParentDlg ? fpParentDlg->GetDialogID() : fParentDialogID;
    
	Sint32 ids[] = { dialogID, this->GetControlID() };
	gSDK->Kludge(5541, ids, NULL);
#else
	ClearActiveTooltip();
	
	farrToolTips.clear();
#endif
}

void VWCustomCtrl::RemoveToolTip(size_t id)
{
	ASSERTN( kVStanev, id < farrToolTips.size() );
	
	if ( id < farrToolTips.size() ) {
		SToolTipDef	*tooltip = &(farrToolTips[id]);
		
		if ( tooltip == fpActiveToolTip )
			ClearActiveTooltip();
		
		farrToolTips.erase( farrToolTips.begin() + id );
		fpActiveToolTip = NULL;
	}
}

size_t VWCustomCtrl::AddToolTip(const SCustomCtrlToolTip& toolTip)
{
#if GS_MAC
    Sint32 dialogID = fpParentDlg ? fpParentDlg->GetDialogID() : fParentDialogID;
    
	Sint32 ids[] = { dialogID, this->GetControlID() };
	gSDK->Kludge(5540, (void*)&toolTip, ids);
	return 0;
#else
	SToolTipDef		def;
	def.fToolTip		= toolTip;
	// make sure the tool tip appears on the rect borders too
	if ( ! def.fToolTip.fRect.IsEmpty() ) {
		def.fToolTip.fRect.Outset( 1, 1 );
	}
	// remember if we have fixed tool tip position
	def.fbCustomPos		= def.fToolTip.fPos.x >= 0 && def.fToolTip.fPos.y >= 0;
	def.fTipID			= farrToolTips.size();
	farrToolTips.push_back( def );

	return def.fTipID;
#endif
}

void VWCustomCtrl::SetCursor( const TXString& fullVWRCursorPath )
{
	fCursorResource	= fullVWRCursorPath;
	if( fMouseCursorAPI )
		fMouseCursorAPI->SetCursor( fullVWRCursorPath );
}

// ==============================================================================
#if GS_WIN
typedef std::map<HWND, VWCustomCtrl*>	TControlInstanceMap;
static TControlInstanceMap				s_controlsInstances;

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::AttachControl()
{
	Sint32	dialogID	= fpParentDlg ? fpParentDlg->GetDialogID() : fParentDialogID;
	fhParentWnd			= (HWND) ::GS_OverrideControl( gCBP, dialogID, fControlID,  NULL );
		HWND hWndControl	= ::GetDlgItem( fhParentWnd, fControlID );
		ASSERTN( kVStanev, hWndControl );
		if ( hWndControl != NULL ) {
			// override the window proc that is to receive windows events
			fpDefaultWndProc	= (WNDPROC) ::GetWindowLongPtr( hWndControl, GWLP_WNDPROC ); 
			VERIFYN( kVStanev, ::SetWindowLongPtr( hWndControl, GWLP_WNDPROC, (LPARAM)(WNDPROC) VWCustomCtrl::_CustomWindowProc ) ); 

			// make sure needed flags are set
			//	SS_NOTIFY	- sends notification messages to static controls
			LONG_PTR	style	= GetWindowLongPtr( hWndControl, GWL_STYLE );
			::SetWindowLongPtr( hWndControl, GWL_STYLE, style | SS_NOTIFY );

			fhCustomWnd			= hWndControl;
			s_controlsInstances.insert( TControlInstanceMap::value_type( hWndControl, this ) );

			this->OnControlAttached();
		}
}

void VWCustomCtrl::DettachControl()
{
	auto it = s_controlsInstances.find( fhCustomWnd );
	if ( it != s_controlsInstances.end() )
		s_controlsInstances.erase( it );
	fhCustomWnd = NULL;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
/*static*/ LRESULT VWCustomCtrl::_CustomWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	TControlInstanceMap::iterator	it			= s_controlsInstances.find( hWnd );
	VWCustomCtrl*					pInstance	= it != s_controlsInstances.end() ? it->second : NULL;
	return pInstance
			? pInstance->CustomWindowProc( hWnd, nMsg, wParam, lParam )
			: ::DefWindowProc(hWnd, nMsg, wParam, lParam);
}
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
LRESULT VWCustomCtrl::CustomWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT	result	= 0L;

	SCustomCtrlGeneralEvent		event;
	event.wnd						= (SintptrT) hWnd;
	event.message					= nMsg;
	event.data1						= (UintptrT) wParam; 
	event.data2						= (UintptrT) lParam; 
	event.result					= 0;
	if ( this->OnEvent( event ) ) {
		// event has been handled by the general event handling funtino
		// so it's not necessary to recognize it
		result	= event.result; 
	}
	else {
		switch( nMsg ) {
			case WM_PAINT: {
					if ( fbDefaultPaint ) {
						// use default window proc to paint for this window
						result	= CallWindowProc( fpDefaultWndProc, hWnd, nMsg, wParam, lParam );

						HDC		hDC	= GetDC( hWnd );

						{ // keep this block so 'VWCustomCtrlDC' could be deleted before OnAfterPaint call
							VWCustomCtrlDC	dc( (SintptrT)hWnd, (void*)hDC, 0, 0 );

							RECT r;
							::GetClientRect( hWnd, & r );

							fCustomCtrlRect.SetLTRB( (ViewCoord)r.left, (ViewCoord)r.top, (ViewCoord)r.right, (ViewCoord)r.bottom );
							dc.SetClipRect( fCustomCtrlRect );

							this->OnPaint( dc );
						} // keep this block so 'VWCustomCtrlDC' could be deleted before OnAfterPaint call
	
						this->OnAfterPaint();

						ReleaseDC( hWnd, hDC );
					}
					else {
						PAINTSTRUCT		ps;
						HDC				hDC	= ::BeginPaint( hWnd, & ps );

						{ // keep this block so 'VWCustomCtrlDC' could be deleted before OnAfterPaint call
							VWCustomCtrlDC	dc( (SintptrT)hWnd, (void*)hDC, 0, 0 );

							RECT r;
							::GetClientRect( hWnd, & r );

							fCustomCtrlRect.SetLTRB( (ViewCoord)r.left, (ViewCoord)r.top, (ViewCoord)r.right, (ViewCoord)r.bottom );
							dc.SetClipRect( fCustomCtrlRect );

							this->OnPaint( dc );
						} // keep this block so 'VWCustomCtrlDC' could be deleted before OnAfterPaint call
	
						this->OnAfterPaint();

						::EndPaint( hWnd, & ps );
					}
				} break;

			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN: {
					SCustomCtrlMouseEvent	event;
					event.x							= ((Sint32)(short)LOWORD(lParam));
					event.y							= ((Sint32)(short)HIWORD(lParam));
					event.bShiftDown				= wParam & MK_SHIFT;
					event.bCtrlDown					= wParam & MK_CONTROL;
					event.bAltDown					= ((GetKeyState(VK_MENU) & 0x80) != 0);

					if ( nMsg == WM_LBUTTONDOWN ) 			this->OnMouseDown( event );
					else if ( nMsg == WM_RBUTTONDOWN )		this->OnMouseRDown( event );
					else if ( nMsg == WM_MBUTTONDOWN )		this->OnMouseMDown( event );
					else									DSTOP((kVStanev, "something's wrong with the message in VWCustomCtrl::CustomWindowProc" ));
					::SetFocus( hWnd );
				} break;

			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP: {
					SCustomCtrlMouseEvent	event;
					event.x							= ((Sint32)(short)LOWORD(lParam));
					event.y							= ((Sint32)(short)HIWORD(lParam));
					event.bShiftDown				= wParam & MK_SHIFT;
					event.bCtrlDown					= wParam & MK_CONTROL;
					event.bAltDown					= ((GetKeyState(VK_MENU) & 0x80) != 0);

					if ( nMsg == WM_LBUTTONUP ) 			this->OnMouseUp( event );
					else if ( nMsg == WM_RBUTTONUP )		this->OnMouseRUp( event );
					else if ( nMsg == WM_MBUTTONUP )		this->OnMouseMUp( event );
					else									DSTOP((kVStanev, "something's wrong with the message in VWCustomCtrl::CustomWindowProc" ));

					if ( nMsg == WM_LBUTTONUP ) 			this->OnMouseClick( event );
					else if ( nMsg == WM_RBUTTONUP )		this->OnMouseRClick( event );
					else if ( nMsg == WM_MBUTTONUP )		this->OnMouseMClick( event );
					else									DSTOP((kVStanev, "something's wrong with the message in VWCustomCtrl::CustomWindowProc" ));
				} break;

			case WM_LBUTTONDBLCLK:
			case WM_RBUTTONDBLCLK:
			case WM_MBUTTONDBLCLK: {
					SCustomCtrlMouseEvent	event;
					event.x							= ((Sint32)(short)LOWORD(lParam));
					event.y							= ((Sint32)(short)HIWORD(lParam));
					event.bShiftDown				= wParam & MK_SHIFT;
					event.bCtrlDown					= wParam & MK_CONTROL;
					event.bAltDown					= ((GetKeyState(VK_MENU) & 0x80) != 0);

					if ( nMsg == WM_LBUTTONDBLCLK ) 		this->OnMouseDblClick( event );
					else if ( nMsg == WM_RBUTTONDBLCLK )	this->OnMouseRDblClick( event );
					else if ( nMsg == WM_MBUTTONDBLCLK )	this->OnMouseMDblClick( event );
					else									DSTOP((kVStanev, "something's wrong with the message in VWCustomCtrl::CustomWindowProc" ));
					::SetFocus( hWnd );
				} break;

			case WM_ERASEBKGND:
				// Eliminates flicker.
				// We could place a this->OnEraseBackground here.
				break;

			case WM_MOUSEMOVE: {
					SCustomCtrlMouseEvent	event;

					event.x							= ((Sint32)(short)LOWORD(lParam));
					event.y							= ((Sint32)(short)HIWORD(lParam));
					event.bShiftDown				= wParam & MK_SHIFT;
					event.bCtrlDown					= wParam & MK_CONTROL;
					event.bAltDown					= ((GetKeyState(VK_MENU) & 0x80) != 0);

					if ( fbSendMouseEnterNotification )
					{
						this->OnMouseEnter( event );
						fbSendMouseEnterNotification = false;
					}
					
					this->OnMouseMoved( event );

					if ( fbToolTipsEnabled && fpToolTipItem ) {
						static ViewPt	oldPt( 0, 0 );
						bool			bActivateToolTip	= false;
						if ((event.x != oldPt.x) || (event.y != oldPt.y)) {
							oldPt.x						= event.x;
							oldPt.y						= event.y;

							ViewPt		scrollAreaPoint;
							Sint32			leftStart;
							Sint32			topStart;
							
							this->GetScrollArea( leftStart, topStart );

							leftStart	= ( leftStart == Uint16(-1) ) ? 0 : leftStart;
							topStart	= ( topStart == Uint16(-1) ) ? 0 : topStart;

							scrollAreaPoint.x	= event.x + leftStart;
							scrollAreaPoint.y	= event.y + topStart;
							
							// check the existing tool tip
							if ( fpActiveToolTip &&
								! (fpActiveToolTip->fToolTip.fRect.IsEmpty() || fpActiveToolTip->fToolTip.fRect.PtInRect( scrollAreaPoint )) )
							{
								// this tool tip is no longer active
								if ( ! fpActiveToolTip->fbCustomPos ) {
									fpActiveToolTip->fToolTip.fPos.Set( -1, -1 );
								}
								fpActiveToolTip		= NULL;
								SendMessage( fhToolTip, TTM_TRACKACTIVATE, (WPARAM) FALSE, (LPARAM) (TOOLINFO*) fpToolTipItem );
							}

							bActivateToolTip = true;

							// find the tool
							SToolTipDef*	pFoundToolTip	= NULL;
							size_t			toolCnt			= farrToolTips.size();
							for(size_t i=0; i<toolCnt; i++) {
								SToolTipDef&	toolTip	= farrToolTips[ i ];
								if ( toolTip.fToolTip.fRect.IsEmpty() ) {
									// we just found a tool tip for the whole window
									// continue searching for more bound restricted one
									pFoundToolTip	= & toolTip;
								}
								else if ( toolTip.fToolTip.fRect.PtInRect( scrollAreaPoint ) ) {
									// op, here is bound restricted one, that's it! STOP!
									pFoundToolTip	= & toolTip;
									break;
								}
							}
							
							if ( fpActiveToolTip == NULL ) {
								fpActiveToolTip		= pFoundToolTip;
							}
							else if ( pFoundToolTip && pFoundToolTip->fToolTip.fRect.PtInRect( scrollAreaPoint ) ) {
								// if the found tool tip is a region it overrides the active tool tip
								fpActiveToolTip		= pFoundToolTip;
							}

							if ( fpActiveToolTip ) {
								// Position the ToolTip. 
								if ( fpActiveToolTip->fToolTip.fbTrackMouse ) {
									// The coordinates are adjusted so that the ToolTip does not overlap the mouse pointer.
									fpActiveToolTip->fToolTip.fPos.Set( event.x + 10, event.y - 20 );
								}
								else if ( fpActiveToolTip->fToolTip.fPos.x < 0 || fpActiveToolTip->fToolTip.fPos.y < 0 ) {
									fpActiveToolTip->fToolTip.fPos.Set( event.x + 10, event.y - 20 );
								}

								if ( this->OnToolTip( fpActiveToolTip->fTipID, fpActiveToolTip->fToolTip ) ) {
									TOOLINFO*	pTooltipInfo	= (TOOLINFO*) fpToolTipItem;
									// Update the text.
									fpActiveToolTip->fToolTip.fText.CopyInto( pTooltipInfo->lpszText, 1024 );
									SendMessage( fhToolTip, TTM_SETTOOLINFO, 0, (LPARAM) ((TOOLINFO*) fpToolTipItem) );
									SendMessage( fhToolTip, TTM_SETMAXTIPWIDTH, 0, 300 );

									POINT pt = { fpActiveToolTip->fToolTip.fPos.x, fpActiveToolTip->fToolTip.fPos.y }; 
									ClientToScreen( fhCustomWnd, & pt );

									Sint32		leftStart	= 0;
									Sint32		topStart	= 0;
									this->GetScrollArea( leftStart, topStart );

									// compensate tool position according to the scroll
									// so it appear on correct location
									pt.x		+= leftStart;
									pt.y		-= topStart;

									SendMessage( fhToolTip, TTM_TRACKPOSITION, 0, (LPARAM)MAKELONG(pt.x, pt.y) ); 
								}
							}
						}

						if ( ! fbTrackingMouse ) {
							// Request notification when the mouse leaves.
							TRACKMOUSEEVENT tme = { sizeof(TRACKMOUSEEVENT) };
							tme.hwndTrack		= fhCustomWnd;
							tme.dwFlags			= TME_LEAVE;
							TrackMouseEvent( & tme );

							bActivateToolTip	= true;
							fbTrackingMouse		= true;
						}

						if ( fpActiveToolTip && 
							 bActivateToolTip ) {
							// Activate the ToolTip.
							SendMessage( fhToolTip, TTM_TRACKACTIVATE, (WPARAM) TRUE, (LPARAM) (TOOLINFO*) fpToolTipItem );
						}
					}					

					if ( fbTrackingMouse == false )
					{
						// Request notification when the mouse leaves.
						TRACKMOUSEEVENT tme;
						tme.cbSize		= sizeof(tme);
						tme.dwFlags		= TME_LEAVE;
						tme.hwndTrack	= hWnd;
						TrackMouseEvent( & tme );
						fbTrackingMouse	= true;
					}

				} break;

			case WM_MOUSELEAVE: {
					POINT	cursorPt;
					GetCursorPos( & cursorPt );
					HWND	hCursorOverWnd	= WindowFromPoint( cursorPt );

					POINT	localPt		= cursorPt;
					ClientToScreen( hCursorOverWnd, & localPt );

					SCustomCtrlMouseEvent	event;
					event.x							= (Uint16) localPt.x;
					event.y							= (Uint16) localPt.y;
					event.bCtrlDown					= (0 != (GetAsyncKeyState(VK_CONTROL) & 0x8000));
					event.bShiftDown				= (0 != (GetAsyncKeyState(VK_SHIFT) & 0x8000));
					event.bAltDown					= (0 != (GetAsyncKeyState(VK_MENU) & 0x8000));

					this->OnMouseLeave( event );
					fbSendMouseEnterNotification = true;

					if ( fbToolTipsEnabled ) {
						// The mouse pointer has left our window. Deactivate the ToolTip.
						// make sure we dont stop the tooltip if mouse over the tool tip
						if ( fpToolTipItem && hCursorOverWnd != fhToolTip ) {
							if ( fpActiveToolTip ) {
								if ( ! fpActiveToolTip->fbCustomPos ) {
									fpActiveToolTip->fToolTip.fPos.Set( -1, -1 );
								}
								fpActiveToolTip		= NULL;
							}
							SendMessage( fhToolTip, TTM_TRACKACTIVATE, (WPARAM) FALSE, (LPARAM) (TOOLINFO*) fpToolTipItem );
						}
					}
					fbTrackingMouse		= false;
					result				= FALSE;
				} break;

			case WM_MOUSEWHEEL: {
					DWORD					fwKeys	= (LOWORD(wParam));
					short 					zDelta	= GET_WHEEL_DELTA_WPARAM(wParam);
					// correct the delta to be 1 per step
					zDelta							/= WHEEL_DELTA;

					SCustomCtrlMouseEvent	event;

					event.x							= ((Sint32)(short)LOWORD(lParam));
					event.y							= ((Sint32)(short)HIWORD(lParam));
					event.bShiftDown				= fwKeys & MK_SHIFT;
					event.bCtrlDown					= fwKeys & MK_CONTROL;
					event.bAltDown					= ((GetKeyState(VK_MENU) & 0x80) != 0);

					this->OnMouseWheel( event, 0, zDelta );
				} break;

			case WM_KEYDOWN:
			case WM_KEYUP: {
					SCustomCtrlKeyEvent		event;
					event.keyCode					= (Uint32) wParam; 
					switch( wParam ) {
						case VK_SHIFT:			event.keyType = kKeyType_Shift;		break;
						case VK_CONTROL:		event.keyType = kKeyType_Control;	break;
						case VK_MENU:			event.keyType = kKeyType_Alt;		break;
						case VK_SPACE:			event.keyType = kKeyType_Space;		break;
						case VK_RETURN:			event.keyType = kKeyType_Enter;		break;
						case VK_ESCAPE:			event.keyType = kKeyType_Escape;	break;
						case VK_INSERT:			event.keyType = kKeyType_Insert;	break;
						case VK_DELETE:			event.keyType = kKeyType_Delete;	break;
						case VK_BACK:			event.keyType = kKeyType_BackSpace;	break;
						case VK_HOME:			event.keyType = kKeyType_Home;		break;
						case VK_END:			event.keyType = kKeyType_End;		break;
						case VK_PRIOR:			event.keyType = kKeyType_PageUp;	break;
						case VK_NEXT:			event.keyType = kKeyType_PageDown;	break;
						case VK_TAB:			event.keyType = kKeyType_Tab;		break;
						case VK_LEFT:  			event.keyType = kKeyType_Left;		break;
						case VK_RIGHT: 			event.keyType = kKeyType_Right;		break;
						case VK_UP: 			event.keyType = kKeyType_Up;		break;
						case VK_DOWN:  			event.keyType = kKeyType_Down;		break;
						case VK_F1:				event.keyType = kKeyType_F1;		break;
						case VK_F2:				event.keyType = kKeyType_F2;		break;
						case VK_F3:				event.keyType = kKeyType_F3;		break;
						case VK_F4:				event.keyType = kKeyType_F4;		break;
						case VK_F5:				event.keyType = kKeyType_F5;		break;
						case VK_F6:				event.keyType = kKeyType_F6;		break;
						case VK_F7:				event.keyType = kKeyType_F7;		break;
						case VK_F8:				event.keyType = kKeyType_F8;		break;
						case VK_F9:				event.keyType = kKeyType_F9;		break;
						case VK_F10:			event.keyType = kKeyType_F10;		break;
						case VK_F11:			event.keyType = kKeyType_F11;		break;
						case VK_F12:			event.keyType = kKeyType_F12;		break;
						default:				event.keyType = kKeyType_Unknown;	break;
					}

					if ( nMsg == WM_KEYDOWN )		this->OnKeyDown( event );
					else if ( nMsg == WM_KEYUP )	this->OnKeyUp( event );
				} break;

			case WM_CHAR : {
					SCustomCtrlKeyEvent		event;
					event.keyCode					= (Uint32) wParam; 
					event.keyType					= kKeyType_Unknown;
					this->OnChar( event );
				} break;

			case WM_GETDLGCODE: {
 					//result = DLGC_WANTCHARS | DLGC_WANTALLKEYS | DLGC_WANTARROWS | DLGC_WANTTAB;
				} break;

			case WM_COMMAND: {
					HWND		hControl	= (HWND) lParam;
					// reflect the message back to the control
					::SendMessage( hControl, WM_COMMAND, wParam, lParam );
				} break;

			case WM_SETCURSOR: {
					if ( ! fCursorResource.IsEmpty() &&fMouseCursorAPI )
					{
						fMouseCursorAPI->SetCursor( fCursorResource );
						result = TRUE;
					}
					else
					{
						result	= ::DefWindowProc( hWnd, nMsg, wParam, lParam );
					}
				} break;

			default: {
					/* We have this default proc call here commented
					 * becaues it messes up with scroll bars behaviour of the custom control
					 * And since there is no advantage of calling the default wnd proc here and now
					 * We have it commented. If uncommening be sure to fix the scroll bar problems
					 * Vlado, 3/6/08
					 *
					if ( fpDefaultWndProc ) {
						result	= CallWindowProc( fpDefaultWndProc, hWnd, nMsg, wParam, lParam );
					}
					else {
						result	= ::DefWindowProc( hWnd, nMsg, wParam, lParam );
					}*/

					result	= ::DefWindowProc( hWnd, nMsg, wParam, lParam );
				} break;
		}
	}

	return result;
}


//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
#endif

