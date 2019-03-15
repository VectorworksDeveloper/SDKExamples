//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWUI
	{
		// ---------------------------------------------------------------------------------------
		enum EControlAlignMode {
			kControlAlignModeResize		= 0,
			kControlAlignModeShift		= 1
		};

		// ---------------------------------------------------------------------------------------
		typedef		Sint32			TControlID;

		// ---------------------------------------------------------------------------------------
		class VWDialog;
		class VWDialogEventArgs;

		// ---------------------------------------------------------------------------------------
		class VWControl
		{
			friend class VWDialog;
		public:
										VWControl(TControlID id);
			virtual						~VWControl();

			bool						CreateControl(VWDialog* pDlg);

		public:
			virtual TControlID			GetControlID() const;
			void						AlignLeftEdge(short alingID, EControlAlignMode mode);
			void						AlignRightEdge(short alingID, EControlAlignMode mode);
			void						AlignBottomEdge(short alingID, EControlAlignMode mode);
			void						AlignColumnEdge(short alingID, EControlAlignMode mode);

			void						SetEdgeBinding(bool bBoundToLeft, bool bBoundToRight, bool bBoundToTop, bool bBoundToBottom);

		// eventing
		public:
			virtual void				NotifyEvent();

		// state
		public:
			void						Enable(bool bEnable=true);
			bool						IsEnabled(void) const;
			void						Show(bool bVisible=true);
			bool						IsVisible(void) const;
			void						Editable(bool bEditable);
			void						SetControlText(short strListID, short strTextIndex);
			void						SetControlText(const TXString& text);
			TXString					GetControlText();
			void						SetHelpText(short strListID, short strHelpIndex);
			void						SetHelpText(const TXString& text);
			void						SetFocus();

		protected:
			virtual void				AttachControl();

		protected:
			TControlID					fControlID;
			VWDialog*					fpParentDlg;
		};
	}
}

////////////////////////////////////////////////////////////////////////////////////
// dispath function macros for making event dispatch maps for the dialog's controls
#define		DEFINE_EVENT_DISPATH_MAP		virtual void DispatchEvent(VWFC::VWUI::TControlID controlID, VWFC::VWUI::VWDialogEventArgs& eventArg)
#define		EVENT_DISPATCH_MAP_BEGIN(clas)	void clas::DispatchEvent(VWFC::VWUI::TControlID controlID, VWFC::VWUI::VWDialogEventArgs& eventArg) { /*eventArg;*/ switch ( controlID ) {
#define		EVENT_DISPATCH_MAP_END			case -1: default: break; } }
// event handing func: 
// SomeName(VWControl* pControl);
#define		ADD_DISPATCH_EVENT(id,f)		case id: this->f( controlID, eventArg ); break;
