//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#import "StdHeaders.h"
#import"VectorworksSDK.h"
#import <Cocoa/Cocoa.h>

using namespace VWFC::VWUI;

typedef std::map<Uint64, VWCustomCtrl*>		TControlInstanceMap;
static TControlInstanceMap					s_controlsInstances;

void VWCustomCtrl::AttachControl()
{
	Sint32	dialogID	= fpParentDlg ? fpParentDlg->GetDialogID() : fParentDialogID;
    
    Uint64				uniqueID;
	uniqueID = dialogID;
    uniqueID = uniqueID << 32;
    uniqueID = uniqueID | fControlID;
        
	fControlRef	= ::GS_OverrideControl( gCBP, dialogID, fControlID, (void*) VWCustomCtrl::_CustomMacHandler );
        
    @autoreleasepool
    {
        NSView* controlView = (NSView*)fControlRef;
        
        fParentWnd = (VoidPtr) [controlView window];
        
        NSRect bounds = [controlView bounds];

#if CORE_IS_RESOLUTION_INDEPENDENT_PHASE2
        bounds = [controlView convertRectToBacking:bounds];
#endif

        fControlRect.top = bounds.origin.y + bounds.size.height;
        fControlRect.left = bounds.origin.x;
        fControlRect.right = bounds.origin.x + bounds.size.width;
        fControlRect.bottom = bounds.origin.y;
    }
    
    s_controlsInstances.insert( TControlInstanceMap::value_type( uniqueID, this ) );
    
    this->OnControlAttached();
}


void VWCustomCtrl::DettachControl()
{
	Sint32	dialogID	= fpParentDlg ? fpParentDlg->GetDialogID() : fParentDialogID;
	
	Uint64				uniqueID;
	uniqueID = dialogID;
	uniqueID = uniqueID << 32;
	uniqueID = uniqueID | fControlID;
	
	auto it = s_controlsInstances.find( uniqueID );
	if ( it != s_controlsInstances.end() )
		s_controlsInstances.erase( it );
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
/*static*/ void VWCustomCtrl::_CustomMacHandler( Sint32 inMessage, void *ioParam, void *paneVP, int dialogID, int componentID )
{
	Uint64		bigDialogID		= dialogID;
	Uint64		uniqueID;
	uniqueID					= bigDialogID << 32;
	uniqueID					= uniqueID | componentID;
	
	TControlInstanceMap::iterator	it	= s_controlsInstances.find( uniqueID );
	
	if ( it != s_controlsInstances.end() ) {
		VWCustomCtrl*	pInstance	= it->second;;
		
		if ( pInstance ) {
            pInstance->CustomMacHandler( inMessage, ioParam, paneVP, dialogID, componentID );
		}
	}
}


inline bool UsingCocoaForDialog(int dlogID)
{
	return gSDK->Kludge(650, &dlogID, nil);
}

struct NNAControlKeyDownRec {
    UInt16              modifiers;
    SInt16              keyCode;
    SInt16              charCode;
};

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void VWCustomCtrl::CustomMacHandler(Sint32 inMessage, void* ioParam, void* paneVP, int dialogID, int componentID )
{
    //	Those are deprecated messages. They are still send by VW but we use our own
	const Sint32 msg_Click				= 812;	// SMouseEvent*
	const Sint32 msg_MouseUp			= 850;	// SMouseEvent*
	const Sint32 msg_AdjustCursor		= 813;	// SMouseEvent*
    
	const Sint32 msg_DrawOrPrint		= 811;	// Rect* (frame of Pane)
    
	const Sint32 msg_KeyPress			= 814;	// NNAControlKeyDownRec*
	const Sint32 msg_KeyUp				= 914;	// NNAControlKeyDownRec*
	
	const Sint32 msg_MouseWheel		= 851;	// SMouseEvent*
	const Sint32 msg_MouseWheelCocoa	= 100;	// SMouseEvent*
    
	const Sint32 msg_MouseDown			= 852;	// SMouseEvent*
    //	const Sint32 msg_MouseUp			= 853;	// SMouseEvent*
	const Sint32 msg_MouseClick		= 854;	// SMouseEvent*
	const Sint32 msg_MouseDblClick		= 855;	// SMouseEvent*
    
	const Sint32 msg_MouseRDown		= 856;	// SMouseEvent*
	const Sint32 msg_MouseRUp			= 857;	// SMouseEvent*
	const Sint32 msg_MouseRClick		= 858;	// SMouseEvent*
	const Sint32 msg_MouseRDblClick	= 859;	// SMouseEvent*
    
	const Sint32 msg_MouseMDown		= 860;	// SMouseEvent*
	const Sint32 msg_MouseMUp			= 861;	// SMouseEvent*
	const Sint32 msg_MouseMClick		= 862;	// SMouseEvent*
	const Sint32 msg_MouseMDblClick	= 863;	// SMouseEvent*
    
	const Sint32 msg_MouseMoved		= 864;	// SMouseEvent*
    
	typedef struct {
		Point		wherePort;
		Point		whereLocal;
		EventRecord	macEvent;
		Boolean		delaySelect;
	} SMouseEvent;
    
	// there are other messages that will be documented for keyboard events and other mouse events on this widget.
	// other types of events need to be registered with the operating system.
	
    
	SCustomCtrlGeneralEvent		event;
	event.wnd						= 0;
	event.message					= inMessage;
	event.data1						= (SintptrT)ioParam;
	event.data2						= (SintptrT)paneVP;
	event.result					= 0;
	if ( this->OnEvent( event ) ) {
		// event has been handled by the general event handling funtino
		// so it's not necessary to recognize it
		;
	}
	else {
		switch( inMessage ) {
			case msg_DrawOrPrint: {
                
				
				NNA_SCOPE 
                { // keep this block so 'VWCustomCtrlDC' could be deleted before OnAfterPaint call
					Rect&	rect			= *((Rect*)ioParam);
					void*	port;
					
                    paneVP = 0;
                    port = ioParam;
                    int l, t, r, b;
                    gSDK->GetComponentRect(dialogID, componentID, l, t, r, b, eLayoutCoordinateSpacePixels);
                    fControlRect.left = l;
                    fControlRect.top = t;
                    fControlRect.right = r;
                    fControlRect.bottom = b;
					
					
					VWCustomCtrlDC	dc( (SintptrT)paneVP, (void*) port, rect.left, rect.top );
					
					fCustomCtrlRect.left	= 0;
					fCustomCtrlRect.top		= 0;
					fCustomCtrlRect.right	= rect.right - rect.left;
					fCustomCtrlRect.bottom	= rect.bottom - rect.top;
                    
					this->OnPaint( dc );
				} // keep this block so 'VWCustomCtrlDC' could be deleted before OnAfterPaint call
                
				this->OnAfterPaint();
                
				break;
			}
				
			case msg_Click:
			case msg_MouseDown:
			case msg_MouseRDown:
			case msg_MouseMDown: {
                SMouseEvent*			pEvent	= (SMouseEvent*) ioParam;
                
                SCustomCtrlMouseEvent	event;
                event.x							= pEvent->whereLocal.h;
                event.y							= pEvent->whereLocal.v;
                event.bCtrlDown					= pEvent->macEvent.modifiers & cmdKey;
                event.bShiftDown				= pEvent->macEvent.modifiers & shiftKey;
                event.bAltDown                  = pEvent->macEvent.modifiers & optionKey;
                if      ( inMessage == msg_MouseRDown )	this->OnMouseRDown( event );
                else if ( inMessage == msg_MouseMDown ) this->OnMouseMDown( event );
                else {
                    this->OnMouseDown( event );	
                    this->OnMouseClick( event );
                }
            } break;
                
			case msg_MouseUp:
			case msg_MouseRUp:
			case msg_MouseMUp: {
                SMouseEvent*			pEvent	= (SMouseEvent*) ioParam;
                
                SCustomCtrlMouseEvent	event;
                event.x							= pEvent->whereLocal.h;
                event.y							= pEvent->whereLocal.v;
                event.bCtrlDown					= pEvent->macEvent.modifiers & cmdKey;
                event.bShiftDown				= pEvent->macEvent.modifiers & shiftKey;
                event.bAltDown                  = pEvent->macEvent.modifiers & optionKey;
                if ( inMessage == msg_MouseUp ) 			this->OnMouseUp( event );
                else if ( inMessage == msg_MouseRUp ) 		this->OnMouseRUp( event );
                else if ( inMessage == msg_MouseMUp ) 		this->OnMouseMUp( event );
                else										DSTOP((kVStanev, "something's wrong with the message in VWCustomCtrl::CustomMacHandler" ));
            } break;
                
			case msg_MouseClick:
			case msg_MouseRClick:
			case msg_MouseMClick: {
                SMouseEvent*			pEvent	= (SMouseEvent*) ioParam;
                
                SCustomCtrlMouseEvent	event;
                event.x							= pEvent->whereLocal.h;
                event.y							= pEvent->whereLocal.v;
                event.bCtrlDown					= pEvent->macEvent.modifiers & cmdKey;
                event.bShiftDown				= pEvent->macEvent.modifiers & shiftKey;
                event.bAltDown                  = pEvent->macEvent.modifiers & optionKey;
                if ( inMessage == msg_MouseClick ) 			this->OnMouseClick( event );
                else if ( inMessage == msg_MouseRClick ) 	this->OnMouseRClick( event );
                else if ( inMessage == msg_MouseMClick ) 	this->OnMouseMClick( event );
                else										DSTOP((kVStanev, "something's wrong with the message in VWCustomCtrl::CustomMacHandler" ));
            } break;
                
			case msg_MouseDblClick:
			case msg_MouseRDblClick:
			case msg_MouseMDblClick: {
                SMouseEvent*			pEvent	= (SMouseEvent*) ioParam;
                
                SCustomCtrlMouseEvent	event;
                event.x							= pEvent->whereLocal.h;
                event.y							= pEvent->whereLocal.v;
                event.bCtrlDown					= pEvent->macEvent.modifiers & cmdKey;
                event.bShiftDown				= pEvent->macEvent.modifiers & shiftKey;
                event.bAltDown                  = pEvent->macEvent.modifiers & optionKey;
                if ( inMessage == msg_MouseDblClick ) 			this->OnMouseDblClick( event );
                else if ( inMessage == msg_MouseRDblClick ) 	this->OnMouseRDblClick( event );
                else if ( inMessage == msg_MouseMDblClick ) 	this->OnMouseMDblClick( event );
                else											DSTOP((kVStanev, "something's wrong with the message in VWCustomCtrl::CustomMacHandler" ));
            } break;
                
			case msg_AdjustCursor:
			case msg_MouseMoved: {
                SMouseEvent*			pEvent	= (SMouseEvent*) ioParam;
                
                SCustomCtrlMouseEvent	event;
                event.x							= pEvent->whereLocal.h;
                event.y							= pEvent->whereLocal.v;
                event.bCtrlDown					= pEvent->macEvent.modifiers & cmdKey;
                event.bShiftDown				= pEvent->macEvent.modifiers & shiftKey;
                event.bAltDown                  = pEvent->macEvent.modifiers & optionKey;
                this->OnMouseMoved( event );
                
            } break;
                
			case msg_MouseWheelCocoa:
			case msg_MouseWheel: {
                
                SCustomCtrlMouseEvent event;
                SInt16 x = ((ViewPt*)ioParam)[1].x;
                SInt16 y = ((ViewPt*)ioParam)[1].y;
                this->OnMouseWheel( event, x, y );
            } break;
                
			case msg_KeyPress: 
			case msg_KeyUp: {
                
				SCustomCtrlKeyEvent event;
				event.keyCode = ((NNAControlKeyDownRec*)ioParam)->keyCode;
                
				switch( event.keyCode ) {
					case kVK_Shift:			event.keyType = kKeyType_Shift;		break;
					case kVK_Control:		event.keyType = kKeyType_Control;	break;
                    case kVK_Option:        event.keyType = kKeyType_Alt;    	break;
					case kVK_Space:			event.keyType = kKeyType_Space;		break;
					case kVK_Return:		event.keyType = kKeyType_Enter;		break;
					case kVK_Escape:		event.keyType = kKeyType_Escape;	break;
					case kVK_Delete:		event.keyType = kKeyType_Delete;	break;
					case kVK_Home:			event.keyType = kKeyType_Home;		break;
					case kVK_End:			event.keyType = kKeyType_End;		break;
					case kVK_PageUp:		event.keyType = kKeyType_PageUp;	break;
					case kVK_PageDown:		event.keyType = kKeyType_PageDown;	break;
					case kVK_Tab:			event.keyType = kKeyType_Tab;		break;
					case kVK_LeftArrow:  	event.keyType = kKeyType_Left;		break;
					case kVK_RightArrow: 	event.keyType = kKeyType_Right;		break;
					case kVK_UpArrow: 		event.keyType = kKeyType_Up;		break;
					case kVK_DownArrow:  	event.keyType = kKeyType_Down;		break;
					case kVK_F1:			event.keyType = kKeyType_F1;		break;
					case kVK_F2:			event.keyType = kKeyType_F2;		break;
					case kVK_F3:			event.keyType = kKeyType_F3;		break;
					case kVK_F4:			event.keyType = kKeyType_F4;		break;
					case kVK_F5:			event.keyType = kKeyType_F5;		break;
					case kVK_F6:			event.keyType = kKeyType_F6;		break;
					case kVK_F7:			event.keyType = kKeyType_F7;		break;
					case kVK_F8:			event.keyType = kKeyType_F8;		break;
					case kVK_F9:			event.keyType = kKeyType_F9;		break;
					case kVK_F10:			event.keyType = kKeyType_F10;		break;
					case kVK_F11:			event.keyType = kKeyType_F11;		break;
					case kVK_F12:			event.keyType = kKeyType_F12;		break;
					default:				event.keyType = kKeyType_Unknown;	break;
                }
                
				if ( inMessage == msg_KeyPress )	
					this->OnKeyDown( event );
				else if ( inMessage == msg_KeyUp )	
					this->OnKeyUp( event );
				
			} break;
                
			case 101:
			case 102:
			{
				SMouseEvent*			pEvent	= (SMouseEvent*) ioParam;
				SCustomCtrlMouseEvent	event;
				event.x							= pEvent->whereLocal.h;
				event.y							= pEvent->whereLocal.v;
				event.bCtrlDown					= pEvent->macEvent.modifiers & cmdKey;
				event.bShiftDown				= pEvent->macEvent.modifiers & shiftKey;
                event.bAltDown                  = pEvent->macEvent.modifiers & optionKey;
				
				if (inMessage == 101)
					this->OnMouseEnter(event);
				else 
					this->OnMouseLeave(event);
                
			} break;
                
		}
	}
}

