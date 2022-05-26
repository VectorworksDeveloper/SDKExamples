//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "CheckButtonCtrl.h"
#include "GroupBoxCtrl.h"
#include "ListBoxCtrl.h"
#include "MarkerPopupCtrl.h"
#include "PictureCtrl.h"
#include "PullDownMenuCtrl.h"
#include "PushButtonCtrl.h"
#include "RadioButtonCtrl.h"
#include "RadioGroupBoxCtrl.h"
#include "StaticTextCtrl.h"
#include "TabPaneCtrl.h"
#include "TabCtrl.h"
#include "SwapPaneCtrl.h"
#include "SwapCtrl.h"
#include "ThumbnailPopupCtrl.h"
#include "ResourceTextPopupCtrl.h"
#include "CheckButtonCtrl.h"
#include "CheckGroupBoxCtrl.h"
#include "ColorButtonCtrl.h"
#include "EditIntegerCtrl.h"
#include "EditRealCtrl.h"
#include "EditTextCtrl.h"
#include "EditPasswordCtrl.h"
#include "SliderCtrl.h"
#include "ColorPopupCtrl.h"
#include "ColorPopupCustomCtrl.h"
#include "PatternPopupCtrl.h"
#include "LineAttributePopupCtrl.h"
#include "LineStylePopupCtrl.h"
#include "LineWeightPopupCtrl.h"
#include "MarkerPopupCtrl.h"
#include "ListBrowserCtrl.h"
#include "TreeCtrl.h"
#include "ChooseClassPopupCtrl.h"
#include "ImagePopupCtrl.h"
#include "StyleButtonCtrl.h"
#include "ChooseLayerPopupCtrl.h"
#include "SearchablePulldownCtrl.h"

#include "../Tools/VWSelectionSupport.h"
#include "../Tools/VWStyleSupport.h"

// Windows MFC defines macros with these names
// that mess up the functions in the class
#ifdef CreateDialog
# undef CreateDialog
#endif

namespace VWFC
{
	namespace VWUI
	{
		// ---------------------------------------------------------------------------------------------------------------
		enum EDialogButton
		{
			kDialogButton_None		= 0,
			kDialogButton_Ok		= 1,
			kDialogButton_Cancel	= 2,
			kDialogButton_CustomA	= 3,
			kDialogButton_CustomB	= 4
		};
		
		class VWCustomCtrl;
		
		// ---------------------------------------------------------------------------------------------------------------
		class VWDialog : public VWControlsContainer
		{
			friend class VWControlsContainer;
			friend class VWCustomCtrl;
			
		protected:
									VWDialog();
		public:
			virtual					~VWDialog();

		// dialog managment
		public:
			virtual EDialogButton	RunDialogLayout(const TXString &contextualHelpID);
            virtual EDialogButton   RunDialogLayout(const TXString &contextualHelpID, const bool bEnableContextualHelp);
			TControlID				GetDialogID() const;

			virtual TXString		GetDialogTitle() const;
			virtual void			SetDialogTitle(const TXString &inTitle);

		// dialog saved settings managment
		public:
			// enables saved settings for this dialog
			// if no dialog name is specified, the dialog title is used
			void					SetSavedSettingsTag(const TXString& category);
			void					SetSavedSettingsTag(const TXString& category, const TXString& dialogName);

			// allows additional data to be stored in saved settings for this dialog
			void					SetSavedValue(const TXString& name, const TXString& value);
			bool					GetSavedValue(const TXString& name, TXString& outValue) const;
			TXString				GetSavedValue(const TXString& name, const TXString& defValue) const;

		// child control managment
		public:
			virtual void				EnableDefaultButton(bool bEnable);
			virtual void				EnableCancelButton(bool bEnable);
			virtual void				EnableControl(TControlID id, bool bEnable);
			virtual void				ShowControl(TControlID id, bool bVisible);
			virtual void				SetControlHelpText(TControlID id, const TXString& helpText);

			virtual void				AddFirstGroupControl(VWControl* pControl);
			virtual void				AddBelowControl(VWControl* pExistingControl, VWControl* pNewControl, short indentStdCh = 0, short lineSpacing = 0);
			virtual void				AddRightControl(VWControl* pExistingControl, VWControl* pNewControl, short indentStdCh = 0, short lineSpacing = 0);

			VWCheckButtonCtrl*			GetCheckButtonCtrByID(TControlID id);
			VWGroupBoxCtrl*				GetGroupBoxCtrlByID(TControlID id);
			VWListBoxCtrl*				GetListBoxCtrlByID(TControlID id);
			VWMarkerPopupCtrl*			GetMarkerPopupCtrlByID(TControlID id);
			VWPictureCtrl*				GetPictureCtrlByID(TControlID id);
			VWPullDownMenuCtrl*			GetPullDownMenuCtrlByID(TControlID id);
			VWPushButtonCtrl*			GetPushButtonCtrlByID(TControlID id);
			VWRadioButtonCtrl*			GetRadioButtonCtrlByID(TControlID id);
			VWRadioGroupBoxCtrl*		GetRadioGroupBoxCtrlByID(TControlID id);
			VWStaticTextCtrl*			GetStaticTextCtrlByID(TControlID id);
			VWTabPaneCtrl*				GetTabPaneCtrlByID(TControlID id);
			VWTabCtrl*					GetTabCtrlByID(TControlID id);
			VWSwapPaneCtrl*				GetSwapPaneCtrlByID(TControlID id);
			VWSwapCtrl*					GetSwapCtrlByID(TControlID id);
			VWThumbnailPopupCtrl*		GetThumbnailPopupCtrlByID(TControlID id);
			VWResourceTextPopupCtrl*	GetResourceTextPopupCtrlByID(TControlID id);
			VWCheckButtonCtrl*			GetCheckButtonCtrlByID(TControlID id);
			VWCheckGroupBoxCtrl*		GetCheckGroupBoxCtrlByID(TControlID id);
			VWColorButtonCtrl*			GetColorButtonCtrlByID(TControlID id);
			VWEditIntegerCtrl*			GetEditIntegerCtrlByID(TControlID id);
			VWEditRealCtrl*				GetEditRealCtrlByID(TControlID id);
			VWEditTextCtrl*				GetEditTextCtrlByID(TControlID id);
			VWEditPasswordCtrl*			GetEditPasswordCtrlByID(TControlID id);
			VWEditTextColorCtrl*		GetEditTextColorCtrlByID(TControlID id);
			VWSliderCtrl*				GetSliderCtrlByID(TControlID id);
			VWColorPopupCtrl*			GetColorPopupCtrlByID(TControlID id);
			VWColorPopupCustomCtrl*		GetColorPopupCustomCtrlByID(TControlID id);
			VWPatternPopupCtrl*			GetPatternPopupCtrlByID(TControlID id);
			VWLineAttributePopupCtrl*	GetLineAttributePopupCtrlByID(TControlID id);
			VWLineStylePopupCtrl*		GetLineStylePopupCtrlByID(TControlID id);
			VWLineWeightPopupCtrl*		GetLineWeightPopupCtrlByID(TControlID id);
			VWListBrowserCtrl*			GetListBrowserCtrlByID(TControlID id);
			VWTreeCtrl*					GetTreeCtrlByID(TControlID id);
			VWChooseClassPopupCtrl*		GetChooseClassPopupCtrlByID(TControlID id);
			VWChooseLayerPopupCtrl*		GetChooseLayerPopupCtrlByID(TControlID id);
			VWImagePopupCtrl*			GetImagePopupCtrlByID(TControlID id);
			VWStyleButtonCtrl*			GetStyleButtonCtrlByID(TControlID id);
			VWStyleGroupButtonCtrl*		GetStyleGroupButtonCtrlByID(TControlID id);
			VWSearchablePulldownCtrl*	GetSearchablePulldownCtrlByID(TControlID id);

			// tab pane managment
			void						AddTabPaneControl(VWTabPaneCtrl* pTabPane);
			void						AddEventContainer(VWControlsContainer* pContainer);

		// Dynamic Data Exchange
		public:
			virtual void	UpdateData(bool bSafeToUI=false);
			virtual void	UpdateDataIgnoringBlackBackgroundInvert(bool bSafeToUI=false);
			virtual void	UpdateDataForControl(bool bSafeToUI, TControlID id);
			virtual void	UpdateDataAllExceptControl(bool bSafeToUI, TControlID id);

			void	ClearDDX();

			/*******************************************************************
			The optional text parameter is used for multiple selection support. 
			The key is used to check the determinate status in the VWSelectionSupport map.
			There must first be a call to SetSelectionSupport() to add support for multiple selection.
			This object must be intiated and called before a call to RunDialogLayout.
			See DoorObjectApp.cpp for DoorSettingsDlg.cpp for full working samples.

			ColorPopup and Slider controls will properly track the multiple selection state,
			but do not have a currenty implementation to display indeterminate.

			ChooseClassPopups should use a separate call to SetMultipleSelectionKey for their support
			due to the large number of versions for AddDDX_ChooseClassPopup.

			ChooseDesignLayer and ChooseSheetLayer popup contorls are not currently supported in DDX
			and by extension for multiple selection. If support is needed for these controls
			they should be implemented for DDX in the same manner ChooseClassPopups.

			All radion button contorls in a grouping should be grouped with calls to SetRadioButtonGroup.
			This will allow for all radion buttons to update their edited state when one in a group is changed.
			See DoorSettingsDlg.cpp for full working samples of these calls.

			JPW for VW 18; March 2012
			********************************************************************/


			
			void	AddDDX_StaticText(TControlID controlID, const TXString* pValue, const  TXString& key = "");
			void	AddDDX_CheckButton(TControlID controlID, bool* pCheckState, const TXString& key = "");
			void	AddDDX_CheckButton(TControlID controlID, Boolean* pCheckState, const  TXString& key = "");
			void	AddDDX_CheckButton(TControlID controlID, short* pCheckTriState, const  TXString& key = ""); // -1 = indeterminate
			void	AddDDX_CheckGroupBox(TControlID controlID, bool* pCheckState, const TXString& key = "");
			void	AddDDX_ColorButton(TControlID controlID, RGBColor* pSelectedColor, const TXString& key = "");
			void	AddDDX_ColorButton(TControlID controlID, TGSColorV2* pSelectedColor, const TXString& key = "");
			void	AddDDX_EditInteger(TControlID controlID, Sint32* pValue, const TXString& key = "" );
			void	AddDDX_EditReal(TControlID controlID, double* pValue, VWEditRealCtrl::EEditControlType editType, const TXString& key = "" );
			void	AddDDX_EditText(TControlID controlID, TXString* pValue, const TXString& key = "" );
			void	AddDDX_EditPassword(TControlID controlID, TXString* pValue, const TXString& key = "" );
			void	AddDDX_EditTextColor(TControlID controlID, TXString* pValue, const TXString& key = "" );
			void	AddDDX_SearchEditBox(TControlID controlID, TXString* pValue, const TXString& key = "");
			void	AddDDX_Slider(TControlID controlID, Sint32* pPosition, const TXString& key = "");
			void	AddDDX_RadioButton(TControlID controlID, bool* pCheckState, const TXString& key = "");
			void	AddDDX_RadioButton(TControlID controlID, Boolean* pCheckState, const TXString& key = "");
			template<class Enum>
			void	AddDDX_RadioButton(TControlID controlID, Enum* pCheckState, Enum value, const TXString& key = ""); // 'value' will be stored in 'pCheckState' when the radio is on; off would not change it. You must use this for all radios in the group with exclusive 'value' from an enumeration
			void	AddDDX_RadioGroupBox(TControlID controlID, bool* pCheckState, const TXString& key = "");
			void	AddDDX_PulldownMenu(TControlID controlID, short* pSelected, const TXString& key = "" );
			void	AddDDX_PulldownMenu(TControlID controlID, size_t* pSelected, const TXString& key = "" );
			void	AddDDX_PulldownMenu(TControlID controlID, TXString* pSelected, const TXString& key = "" );
			void	AddDDX_PulldownMenu(TControlID controlID, Sint32* pMarker, const TXString& key = "" );
			void	AddDDX_ListBox(TControlID controlID, short* pSelected, const TXString& key = "");
			void	AddDDX_ListBox(TControlID controlID, size_t* pSelected, const TXString& key = "");
			void	AddDDX_ListBrowser(TControlID controlID, size_t* pSelected, const TXString& key = "");
			void	AddDDX_ColorPopup(TControlID controlID, RGBColor* pSelectedColor, bool bMatchBlackBkgr=true, const TXString& key = "");
			void	AddDDX_ColorPopupCustom(TControlID controlID, ColorRef* pSelectedColor, const TXString& key = "");
			void	AddDDX_PatternPopup(TControlID controlID, short* pPatternIndex, RGBColor* pForeColor, RGBColor* pBackColor, const TXString& key = "");
			void	AddDDX_LineAttribsPopup(TControlID controlID, InternalIndex* pLineStyle, short* pLineWeight );
			void	AddDDX_LineAttribsPopup(TControlID controlID, InternalIndex* pLineStyle, short* pLineWeight, const TXString& keyStyle, const  TXString& keyWeight );
			void	AddDDX_LineStylePopup(TControlID controlID, InternalIndex* pLineStyle, const TXString& key = "");
			void	AddDDX_LineWeightPopup(TControlID controlID, short* pLineWeight, const TXString& key = "");
			void	AddDDX_MarkerPopup(TControlID controlID, SMarkerStyle* pValue, const TXString& key = "");
			void	AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, short* pSelected);
			void	AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, short* pSelected, const TXString& standardClass);
			void	AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, short* pSelected, const TXString& standardClass, const TXStringArray& arrAdditionalItems);
			void	AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, short* pSelected, const TXStringArray& arrAdditionalItems);
			void	AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, size_t* pSelected);
			void	AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, size_t* pSelected, const TXString& standardClass);
			void	AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, size_t* pSelected, const TXString& standardClass, const TXStringArray& arrAdditionalItems);
			void	AddDDX_ChooseClassPopup(TControlID controlID, TXString* pValue, size_t* pSelected, const TXStringArray& arrAdditionalItems);
			void	AddDDX_ChooseLayerPopup(TControlID controlID, TXString* pValue, short* pSelected);
			void	AddDDX_ChooseLayerPopup(TControlID controlID, TXString* pValue, short* pSelected, const TXStringArray& arrAdditionalItems);
			void	AddDDX_UnitEditText(TControlID controlID, double* pValue, std::function<void(double value,TXString& out)> callbackToTxt, std::function<double(const TXString& value)> callbackToValue, const TXString& key = "" );
			void	AddDDX_SearchablePulldownMenu(TControlID controlID, TXString* pValue, const TXString& key = "");
			void	AddDDX_ImagePopup(TControlID controlID, TXString* pValue, const TXString& key = "");
			void	AddDDX_ResourceTextPopup(TControlID controlID, TXString* pValue, const TXString& key = "");
			
			template<class TControlClass>
			void	AddDDX_Control(TControlClass* pControl);

			void	SetSelectionSupport( VWSelectionSupport * pSelectionSupport );
			void	SetRadioButtonGroup( const TXString& fieldName, Sint32 groupID );
			bool	SetMultipleSelectionKey( TControlID controlID, const TXString& key );
			
			bool	IsComponentIndeterminate( TControlID controlID );
			bool	IsComponentEdited( TControlID controlID );
			
			VWSelectionSupport	* GetSelectionSupport();

			// plugin style support
			virtual void	SetStyleSupport( VWStyleSupport * pStyleSupport, bool styleMode );


		// Advance Dynamic Data Exchange
		public:
			/*******************************************************************
			These functions are used when the key is flags parameter. With "flag"
			we marked which flag of the flags parameter is for this control.

			KI for VW 18; June 2012
			********************************************************************/

			void	AddDDX_CheckButton(TControlID controlID, bool* pCheckState, Tools::TValueFlags flag, const TXString& key);
			void	AddDDX_CheckButton(TControlID controlID, Boolean* pCheckState, Tools::TValueFlags flag, const  TXString& key);
			void	AddDDX_CheckButton(TControlID controlID, short* pCheckTriState, Tools::TValueFlags flag, const  TXString& key);
			void	AddDDX_CheckGroupBox(TControlID controlID, bool* pCheckState, Tools::TValueFlags flag, const TXString& key);

		// tools
		public:			
			// Displays an alert dialog that informs the user of a serious problem
			// that requires intervention or correction before work can continue.
			static void				AlertCritical(const TXString& text, const TXString& advice = "");

			// Displays an alert dialog that informs the user of a serious problem
			// that requires intervention or correction before work can continue.
			// The displayed dialog is able to contain a single, titled hyperlink.
			static void				AlertCriticalWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink);

			// Displays a dialog which informs the user about the result of a command.
			// Offers no user choices; the user acknowledges the message by clicking the OK button.
			static void				AlertInform(const TXString& text, const TXString& advice = "", bool bMinorAlert = false);

			// Displays a dialog which informs the user about the result of a command.
			// The displayed dialog is able to contain a single, titled hyperlink.
			// Offers no user choices; the user acknowledges the message by clicking the OK button.
			static void				AlertInformWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink, bool bMinorAlert = false);

			// Displays a dialog that alerts the user to a condition
			// or situation that requires the user's decision and input before preceeding,
			// such as an impending action with potentially destructive or irreversible consequencies. 
			static EDialogButton	AlertQuestion(	const TXString& question,
													const TXString& advice = "",
													EDialogButton defaultButton = kDialogButton_None,
													const TXString& strOkText = "",
													const TXString& strCancelText = "",
													const TXString& strCustomButtonAText = "",
													const TXString& strCustomButtonBText = "" );

			// support for automatic list browser column width storage
			void					RegisterListBrowserColumn(TControlID controlID, size_t columnIndex, const TXString& savedSettingsColumnName);
			void					SaveListBrowserColumnSavedSets();

			// support for automatic tab/swap control state storage
			// use in your VWDialog constructor to add automatic restore of swap/tab selected pages
			typedef std::function<size_t(bool inputIsListIndex, size_t& index)>	TRegisterSwapCtrlTranslateCallback;
			void					RegisterSwapControl(TControlID listControlID, TControlID swapControlID, const TXString& savedSettingsName, bool autoSwap, TRegisterSwapCtrlTranslateCallback callback = nullptr);
			void					RegisterTabControl(TControlID controlID, const TXString& savedSettingsName);

			TRegisterSwapCtrlTranslateCallback	GetRegisteredSwapConrolCallback(TControlID listControlID, TControlID tabControlID);

			// for external developers that wish to show multiple contextual help listings for an individual dialog,
			// based on events that happen within the dialog.
			// (Nemetschek developers should not use this, as it is not hooked up to help Querying tools)
			void					UpdateContextualHelpID(const TXString& newHelpID);

			// start and stop receiving timed events via 'virtual void OnDialogTimer();'
			void					RegisterForTimerEvents(Uint32 timerDelayInMilliseconds);
			void					DeregisterForTimerEvents();

			// start receiving key event messages 'OnKeyEvent'
			void					EnableKeyEvents(bool enable);

		// creational
		protected:
			bool					CreateDialog(const TXString& dlgTitle, const TXString& defaultBtn, const TXString& cancelBtn, bool hasHelp=true, bool bResizableWidth=false, bool bResizableHeight=false);
			bool					CreateDialog(short strListID, short dlgTitleIndex, short defaultBtnIndex, short cancelBtnIndex, bool hasHelp=true, bool bResizableWidth=false, bool bResizableHeight=false);
			bool					CreateDialogLayoutFromRsrc(short TEXTResourceID);
            bool                    CreateDialogLayoutFromRsrcAndVWR(short TEXTResourceID, const char* defaultVWRName);
            bool                    CreateDialogLayoutFromVWR(const char* resIdentifier);
            
			void					SetDefaultButtonHelpString(const TXString& helpText);
			void					SetDefaultButtonHelpString(short strListID, short strHelpIndex);
			void					SetCancelButtonHelpString(const TXString& helpText);
			void					SetCancelButtonHelpString(short strListID, short strHelpIndex);

			virtual ViewRect		GetDialogDimension() const;
			virtual ViewPt			GetDialogPosition() const;
			virtual void			SetDialogPosition(ViewCoord left, ViewCoord top);
			virtual void			GetDialogSize(ViewCoord& outWidth, ViewCoord& outHeight) const;
			virtual void			SetDialogSize(ViewCoord width, ViewCoord height) const;

			VWDialogEventArgs		GetEmptyEventArgs(TControlID controlID) const;
			VWDialogEventArgs		GetEmptyEventArgs(VWControl* pControl) const;

		// virtuals
		protected:
			virtual bool			CreateDialogLayout() = 0;
			virtual void			OnInitializeContent();
			virtual	void			OnDDXInitialize() = 0;
			virtual void			OnUpdateUI();
			virtual void			OnLoadSavedSettings();
			virtual void			OnSaveSavedSettings(bool closedOk);

		// events
		protected:
			virtual void			OnSetUpEvent();
			virtual void			OnSetDownEvent();
			virtual void			OnDefaultButtonEvent();
			virtual void			OnCancelButtonEvent();
			virtual void			OnControlEvent(VWControl* pParentControl);
			virtual void			OnBeforeDispatchEvent(TControlID controlID, VWDialogEventArgs& eventArg);
			virtual void			OnDialogTimer();
			virtual bool			OnKeyEvent(TDialogKeyDownEvent& theEvent); // return true if handled, so the event wont be propagated more
			virtual void			OnDialogResize();

			// default events for plugin style buttons
			virtual	void			OnChangeStyleButton( TControlID controlID, VWDialogEventArgs& eventArgs );
			virtual	void			OnChangeStyleGroupButton( TControlID controlID, VWDialogEventArgs& eventArgs );


			// tree control events
			virtual bool			OnTreeCtrlCanEditLabel(TControlID controlID, TTreeItemID treeItemID);
			virtual void			OnTreeCtrlCompleteEditlabel(TControlID controlID, TTreeItemID treeItemID);
			virtual bool			OnTreeCtrlCanDeleteItem(TControlID controlID, TTreeItemID treeItemID);
			virtual void			OnTreeCtrlDeleteItem(TControlID controlID, TTreeItemID treeItemID);
			virtual void			OnTreeCtrlDragOver(TControlID controlID, TTreeControlDropMessageData& data);
			virtual void			OnTreeCtrlDrop(TControlID controlID, TTreeControlDropMessageData& data);

		// private dialong event handler
		private:
			static void			DialogEventHandler(Sint32 dlogID, Sint32& itemHit, void* data, void* env);
			void				LocalDialogEventHandler(Sint32& itemHit, void* pData);

		// events dispatcher map
		protected:
			DEFINE_EVENT_DISPATH_MAP;
			std::shared_ptr<void> fEventHandlers;

			// add event handles with the DEFINE_EVENT_DISPATH_MAP macros
			// here are example event handlers
			//void				OnMyControl(TControlID controlID, VWDialogEventArgs& eventArgs);
			//void				OnMyListBrowserDirectEdit(TControlID controlID, VWListBrowserEventArgs& eventArgs);

		protected:
			void				AddControl(VWControl* pControl, bool fake=false);
			VWControl*			GetControl(TControlID id);
			void				SetDialogClose(bool bCloseWithOK);
			void				UpdateSavedSettings(bool bRead);
			bool				SetDDXControlValue(TControlID controlID, const TXString& value);
			bool				GetDDXControlValue(TControlID controlID, TXString& outValue);
			void				UpdateSelectionInfo(TControlID controlID, VWDialogEventArgs& eventArg);
			void				UpdateDataInternal(bool bSafeToUI, TControlID id, bool bOnlyThisOne, bool bDoBlackBackgroundInvert);

		// Style Support
		protected:
			virtual void	InitializeStyleSupport();
			virtual void	InitStyleControl( TControlID controlID, Sint32  groupID, const TXString & paramName, TControlID primaryControl, TControlID addedControl2 = 0, TControlID addedControl3 = 0, TControlID addedControl4 = 0 );
			virtual void	InitStyleGroupControl( TControlID controlID, Sint32 groupdID, TControlID textControlID = 0 );
			virtual void	AssociateStyleControl( TControlID controlID, TControlID associatedControlID );
			virtual void	AssociateStyleParameter( TControlID controlID, const TXString & paramName );

			virtual void	UpdateStyleSupport();
			virtual void	UpdateStyleControlTypes();
			virtual void	UpdateStyleUI();
			virtual void	UpdateStyleGroups();
			virtual void	UpdateStyleGroupButton( Sint32 groupID );

			virtual void	UpdateCatalogUI();

		// extended custom control event support
		protected:
			virtual void		InitExtendedEventSupport();
			virtual void		DeinitExtendedEventSupport();
			virtual void		InstallExtendedEventSupport(VWControl* pControl);
#ifndef _WINDOWS
			VWCustomCtrl*		GetCustomCtrlAtPoint(const ViewPt& pt);
#endif

			void				DDXHelper_TypeRadioButtonEnum(TControlID controlID, void* pData, Sint32 lData, const TXString& key);

		protected:
			// true when the dialog is setup
			// this prevets the calling dispatcher when the dialog is not setup
			bool				fbIsSetup;

			// the item hit when default button or cancel button events occure
			// used to prevend the dialog from closing if you dont call VWDialog::OnDefaultButtonEvent or VWDialog::OnCancelButtonEvent
			std::vector<Sint32*>	fstackItemHit;

			void*				fpArrControls;

			// containers that that the dialog will pass events to
			void*				fpArrEventContainers;

			// DDX data
			void*				fpArrDDXData;
			
			// Multiple Selection Suppoort data
			VWSelectionSupport	* fpSelectionSupport;
			
			typedef std::pair<TXString, Sint32> TRadioControl_Pair;	
			typedef std::map <TXString, Sint32> :: iterator TRadioControl_Iterator;
			std::map<TXString, Sint32>	  fMapRadioControls;

			struct SSavedColumnData
			{
				TControlID							fControlID;
				TControlID							fSupportControlID;
				size_t								fColumnIndex;
				TXString							fSavedSettingsColumnName;
				bool								fAutoSwap;
				TRegisterSwapCtrlTranslateCallback	fTranslateCallback;
			};

			typedef std::vector<SSavedColumnData>	TSavedColumnDataArray;

			// saved settings support
			TXString				fstrDialogCategory;
			TXString				fstrDialogName;
			TXString				fSavedSettingsDlgCategory;
			TSavedColumnDataArray	farrSavedLSColumnData;
			TSavedColumnDataArray	farrSavedSwapTabData;
			ViewRect				fSavedDialogPosition;

			
			// support for style controls
			std::vector<VWStyleGroupButtonCtrl *>	fStyleGroupControls;

			struct SStyleControl {			
				TControlID				key;
				TXString				paramName;
				EPluginStyleParameter	styleType;
				VWStyleButtonCtrl *		pControl;
				Sint32					groupID;

				SStyleControl();
				~SStyleControl();
			};

			typedef std::map<TControlID, SStyleControl>					TStyleControlMap;
			typedef std::pair<TControlID, SStyleControl>				TStyleControl_Pair;	
			typedef std::map <TControlID, SStyleControl> :: iterator	TStyleControl_Iterator;

			TStyleControlMap	fStyleControlMap;
			VWStyleSupport	*	fpStyleSupport;
			bool				fbStyleMode;

			TXString			fStyleButtonHelp;
			TXString			fByStyleButtonHelp;
			TXString			fByInstanseButtonHelp;
			TXString			fByCatalogButtonHelp;
		};


		// ---------------------------------------------------------------------------------------------------------------
		template<class TControlClass>
		void VWDialog::AddDDX_Control(TControlClass* pControl)
		{
			if ( pControl == NULL )
				return;

			VWControl*	pThisControl	= pControl;
			VWControl*	pOldControl		= this->GetControl( pThisControl->GetControlID() );
			// this control should not be added twice
			ASSERTN( kVStanev, pOldControl == NULL || pThisControl == pOldControl );
			if ( pOldControl == NULL || pThisControl == pOldControl ) {
				pThisControl->fpParentDlg	= this;
				pThisControl->AttachControl();
				this->InstallExtendedEventSupport( pThisControl );
				if ( pOldControl == NULL ) {
					this->AddControl( pThisControl, false );
				}
			}
		}

		template<class Enum>
		void VWDialog::AddDDX_RadioButton(TControlID controlID, Enum* pCheckState, Enum value, const TXString& key)
		{
			this->DDXHelper_TypeRadioButtonEnum( controlID, (void*)pCheckState, (Sint32)value, key );
		}
	}
}
