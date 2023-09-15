//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

#include "Control.h"
#include "CustomCtrlDrawing.h"

namespace VWFC
{
	namespace VWUI
	{
		// ------------------------------------------------------------------------------------------------------
		enum EKeyType
		{
			kKeyType_Unknown,
			kKeyType_Shift,
			kKeyType_Control,
            kKeyType_Alt,
			kKeyType_Space,
			kKeyType_Enter,
			kKeyType_Escape,
			kKeyType_Insert,
			kKeyType_Delete,
			kKeyType_BackSpace,
			kKeyType_Home,
			kKeyType_End,
			kKeyType_PageUp,
			kKeyType_PageDown,
			kKeyType_Tab,
			kKeyType_Left,
			kKeyType_Right,
			kKeyType_Up,
			kKeyType_Down,
			kKeyType_F1,
			kKeyType_F2,
			kKeyType_F3,
			kKeyType_F4,
			kKeyType_F5,
			kKeyType_F6,
			kKeyType_F7,
			kKeyType_F8,
			kKeyType_F9,
			kKeyType_F10,
			kKeyType_F11,
			kKeyType_F12
		};

		// ------------------------------------------------------------------------------------------------------
		struct SCustomCtrlMouseEvent
		{
			Uint16				x;
			Uint16				y;
			bool				bShiftDown;
			bool				bCtrlDown;
			bool				bAltDown;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SCustomCtrlKeyEvent
		{
			EKeyType			keyType;
			Uint32				keyCode;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SCustomCtrlGeneralEvent
		{
			SintptrT			wnd;
			Uint32				message;
			UintptrT			data1;			// (Win:(WPARAM))(Mac:(void* ioParam))
			UintptrT			data2;			// (Win:(LPARAM))(Mac:(void* paneVP))
			Uint32				result;			// (Win:(HRESULT))
		};

		// ------------------------------------------------------------------------------------------------------
		struct SCustomCtrlToolTip
		{
							SCustomCtrlToolTip();

			TXString		fText;
			ViewRect		fRect;
			bool			fbTrackMouse;
			ViewPt			fPos;
		};

		// ------------------------------------------------------------------------------------------------------
		class VWDialog;
		class VWCustomCtrl : public VWControl
		{
			friend class VWDialog;
		public:
								VWCustomCtrl(TControlID id, bool bDefaultPaint=false);
			virtual				~VWCustomCtrl();

			virtual bool		CreateControl(VWDialog* pDlg, Uint16 width, Uint16 height);
			void				AttachControl(TControlID dialogID);

		// attributes
		public:
			ViewCoord			GetControlWidth() const;
			ViewCoord			GetControlHeight() const;

			virtual void		Refresh();
			void				UpdateScrollArea(Sint32 width, Sint32 height, Sint32 leftStart, Sint32 topStart, Sint32 stepSize, bool bLiveUpdate, bool bAlwaysShowHoriz=false, bool bAlwaysShowVert=false);
			void				GetScrollArea(Sint32& outLeftStart, Sint32& outTopStart);

			SintptrT			GetOSParentHandle() const;
			SintptrT			GetOSControlHandle() const;

			void				SetCursor( const TXString& fullVWRCursorPath );

		// eventing
		protected:
			virtual void		OnControlAttached();
			virtual bool		OnEvent(SCustomCtrlGeneralEvent& event);
			virtual void		OnPaint(VWCustomCtrlDC& dc) = 0;
			virtual void		OnAfterPaint();

			virtual void		OnMouseMoved(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseDown(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseUp(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseClick(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseDblClick(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseRDown(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseRUp(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseRClick(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseRDblClick(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseMDown(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseMUp(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseMClick(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseMDblClick(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseWheel(const SCustomCtrlMouseEvent& event, Sint16 deltaX, Sint16 deltaY);
			virtual void		OnMouseEnter(const SCustomCtrlMouseEvent& event);
			virtual void		OnMouseLeave(const SCustomCtrlMouseEvent& event);

			virtual void		OnKeyDown(const SCustomCtrlKeyEvent& event);
			virtual void		OnKeyUp(const SCustomCtrlKeyEvent& event);
			virtual void		OnChar(const SCustomCtrlKeyEvent& event);

			virtual bool		OnToolTip(size_t id, SCustomCtrlToolTip& inoutToolTip);

		protected:
			virtual void		AttachControl();
			ViewRect			GetControlRect() const;

			// tool tip support
		protected:
			void				EnableToolTips(bool bEnable);
			void				ClearActiveTooltip( void );
			void				RemoveAllToolTips();
			void				RemoveToolTip(size_t id);
			size_t				AddToolTip(const SCustomCtrlToolTip& toolTip);

		// OS Event handlers
		private:
			TControlID				fParentDialogID;

			UI::IMouseCursorManagerPtr	fMouseCursorAPI;
			
			void		DettachControl();
#ifdef _WINDOWS
	#if defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H)
			static LRESULT CALLBACK _CustomWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
			LRESULT					CustomWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

			WNDPROC					fpDefaultWndProc;

			HWND					fhParentWnd;
			HWND					fhCustomWnd;

			void*					fpToolTipItem;
			HWND					fhToolTip;
			bool					fbTrackingMouse;
			bool					fbSendMouseEnterNotification;
	#else
			void*					fpDefaultWndProc;

			void*					fhParentWnd;
			void*					fhCustomWnd;

			void*					fpToolTipItem;
			void*					fhToolTip;
			bool					fbTrackingMouse;
			bool					fbSendMouseEnterNotification;
	#endif
#else
			static void				_CustomMacHandler(Sint32 inMessage, void *ioParam, void *paneVP, Sint32 dialogID, Sint32 componentID );
			void					CustomMacHandler(Sint32 inMessage, void *ioParam, void *paneVP, Sint32 dialogID, Sint32 componentID );
			
			void*					fParentWnd;
			void*                   fControlRef;
			Rect					fControlRect;
#endif

			bool					fbDefaultPaint;
			ViewRect				fCustomCtrlRect;

			struct SToolTipDef
			{
				SCustomCtrlToolTip	fToolTip;
				size_t				fTipID;
				bool				fbCustomPos;
			};

			typedef std::vector<SToolTipDef>		TToolTipsArray;
			bool					fbToolTipsEnabled;
			TToolTipsArray			farrToolTips;
			SToolTipDef*			fpActiveToolTip;
			TXString				fCursorResource;
		};
	}
}
