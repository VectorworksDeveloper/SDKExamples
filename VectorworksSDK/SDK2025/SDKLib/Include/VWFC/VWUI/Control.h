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
		namespace VWControlType {
			// ---------------------------------------------------------------------------------------
			// Component Types
			typedef enum {
				eCompLayout,
				eCompCheckBox,
				eCompEditText,
				eCompIcon,
				eCompListBox,
				eCompPullDownMenu,
				eCompPushButton,
				eCompRadioButton,
				eCompStaticText,
				eCompColorButton,
				eCompSlider,
				eCompGradientSlider,
				eCompThumbnailPopup,
				eCompResourceTextPopup,
				eCompColorPopup,     // (1) << These six are Layout Manager Attribute Controls. >>
				eCompPatternPopup,   // (2)
				eCompDashPopup,      // (3)
				eCompLinePopup,      // (4)
				eCompLineComboPopup, // (5) (Combined line style and weight. )
				eCompMarkerPopup,    // (6)
				eCompEditReal,
				eCompEditMultilineText,
				eCompCheckBoxGroupBox,
				eCompRadioButtonGroupBox,
				eCompTabControl,
				eCompTreeControl,
				eCompListBrowserControl,
				eCompSwapControl,
				eCompSymbolDisplay,
		#if GS_ENABLE_NEW_LAYOUT_MANAGER_CONTROLS
				eCompThreeStateCheckbox,
				eCompIconPushButton,
				eCompEnhancedComboBox,
				eCompEditableEnhancedComboBox,
				eCompUnused1,
				eCompImageControl,
				eCompSeparator,
				eCompPullDownMenuGroupBox,
		#endif
				eCompCustom,
				
				eCompUndefined,
				
				eCompEditablePatternsDropDown,
				eCompSearchEditText,
				eCompPasswordEditText,
				eCompFilterableComboBox,
				eCompEditColorText,
				
				eCompCheckBoxWithIcon,
				eCompRadioButtonWithIcon,
				
				eCompBorderlessButton,
				eCompBorderlessMenuButton,
			} EType;
		}
	
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
		protected:
										VWControl(TControlID id, const std::vector<VWControlType::EType>& allowedComponentTypes);
		public:
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
			virtual void				Enable(bool bEnable=true);
			virtual bool				IsEnabled(void) const;
			virtual void				Show(bool bVisible=true);
			virtual bool				IsVisible(void) const;
			virtual void				Editable(bool bEditable);
			virtual void				SetControlText(short strListID, short strTextIndex);
			virtual void				SetControlText(const TXString& text);
			virtual TXString			GetControlText();
			virtual void				SetHelpText(short strListID, short strHelpIndex);
			virtual void				SetHelpText(const TXString& text);
			virtual void				SetFocus();

		protected:
			virtual void				AttachControl();

		protected:
			TControlID					fControlID;
			const std::vector<VWControlType::EType> fAllowedComponentTypes;
			VWDialog*					fpParentDlg;
		};
	}
}

////////////////////////////////////////////////////////////////////////////////////
// dispath function macros for making event dispatch maps for the dialog's controls
#define		DEFINE_EVENT_DISPATH_MAP		void InitDispatchEventMapIfNeeded(); \
											virtual void DispatchEvent(VWFC::VWUI::TControlID controlID, VWFC::VWUI::VWDialogEventArgs& eventArg); \
											virtual void DispatchEvent(VWFC::VWUI::TControlID controlID, VWFC::VWUI::VWListBrowserEventArgs& eventArg);
// ------------------------------------------------------------------------------------------------
#define		EVENT_DISPATCH_MAP_BEGIN(clas)	void clas::DispatchEvent(VWFC::VWUI::TControlID controlID, VWFC::VWUI::VWDialogEventArgs& eventArg)\
											{ \
												this->InitDispatchEventMapIfNeeded(); \
												std::map< TControlID, CDialogEventHandlers<clas>>& mapHandlers = *(std::map<TControlID, CDialogEventHandlers<clas>>*) fEventHandlers.get(); \
												auto it = mapHandlers.find(controlID); \
												if ( it != mapHandlers.end() ) \
													it->second.Call( *this, controlID, eventArg ); \
											} \
											void clas::DispatchEvent(VWFC::VWUI::TControlID controlID, VWFC::VWUI::VWListBrowserEventArgs& eventArg)\
											{ \
												this->InitDispatchEventMapIfNeeded(); \
												std::map< TControlID, CDialogEventHandlers<clas>>& mapHandlers = *(std::map<TControlID, CDialogEventHandlers<clas>>*) fEventHandlers.get(); \
												auto it = mapHandlers.find(controlID); \
												if ( it != mapHandlers.end() ) \
													it->second.Call( *this, controlID, eventArg ); \
											} \
											void clas::InitDispatchEventMapIfNeeded()\
											{ \
												if ( fEventHandlers.get() == nullptr ) { \
													fEventHandlers.reset( new std::map<TControlID, CDialogEventHandlers<clas>>() ); \
													std::map< TControlID, CDialogEventHandlers<clas>>& mapHandlers = *(std::map<TControlID, CDialogEventHandlers<clas>>*) fEventHandlers.get(); \
													mapHandlers; \
													typedef clas	TClassType;												
// ------------------------------------------------------------------------------------------------
#define		EVENT_DISPATCH_MAP_END				} \
											}
// ------------------------------------------------------------------------------------------------
// generic dispatch event handler
#define		ADD_DISPATCH_EVENT(id,f)				{\
														auto callback = &TClassType::f;\
														auto it = mapHandlers.find(id); \
														if ( it != mapHandlers.end() ) it->second.Set( callback ); \
														else { mapHandlers[id] = CDialogEventHandlers<TClassType>(callback); } \
													}
// ------------------------------------------------------------------------------------------------
// list browser direct edit handler
#define		ADD_LB_DIRECT_EDIT(id,f)				{\
														auto callback = &TClassType::f;\
														auto it = mapHandlers.find(id); \
														if ( it != mapHandlers.end() ) it->second.Set( callback ); \
														else { mapHandlers[id] = CDialogEventHandlers<TClassType>(callback); } \
													}
