//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "CheckButtonCtrl.h"
#include "TreeCtrlItem.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWDialog;

		// ---------------------------------------------------------------------------------------------------------------
		enum EListBrowserEventType {
			kListBrowserEventType_Unknown						= 0,
			kListBrowserEventType_DataChangeClick				= -2,
			kListBrowserEventType_DataChangeAllClick			= -3,
			kListBrowserEventType_SelectionChangeClick			= -4,
			kListBrowserEventType_DoubleClick					= -5,
			kListBrowserEventType_DoubleAllClick				= -14,
			kListBrowserEventType_DoubleRecursiveClick			= -15,
			kListBrowserEventType_DeleteKeyPressed				= -6,
			kListBrowserEventType_UpKeyPressed					= -7,
			kListBrowserEventType_DownKeyPressed				= -8,
			kListBrowserEventType_AlphaNumericKeyPressed		= -9,
			kListBrowserEventType_SortOccurred					= -10,
			kListBrowserEventType_SelectionMultChangeClick		= -11,
			kListBrowserEventType_EnterKeyPressed				= -12,
			kListBrowserEventType_DataChangeRecursiveClick		= -13,
			kListBrowserEventType_ReceivingDragAndDrop			= -50,
			kListBrowserEventType_DragAndDrop					= -51,
		};

		// ---------------------------------------------------------------------------------------------------------------
		enum class EListBrowserDirectEditType {
			QueryInteractionHandlingType    = -16,		// SDK type: kMessageQueryInteractionHandlingType
			QueryItemValue                  = -17,		// SDK type: kMessageQueryItemValue
			QueryItemListRetrieval          = -18,		// SDK type: kMessageQueryItemListRetrieval
			ItemEditCompletionData          = -19,		// SDK type: kMessageItemEditCompletionData
		};

		enum EEditFieldEventType 
		{
			kEditFieldEventType_TextChanged		= 0,
			kEditFieldEventType_Focused			= 1
		};

		enum ESearchEditFieldEventType
		{
			kSearchEditFieldEventType_TextChanged		= 0,
			kSearchEditFieldEventType_Focused			= 1,
			kSearchEditFieldEventType_EnterKeyPressed	= 2,
			kSearchEditFieldEventType_Cancelled			= 3
		};

		
		// ---------------------------------------------------------------------------------------------------------------
		class VWDialogEventArgs
		{
			friend class VWDialog;
		protected:
									VWDialogEventArgs(Sint32 dlgID, Sint32 ctrlID, void* pData);
		public:
									VWDialogEventArgs();
			virtual					~VWDialogEventArgs();

		// general events support
		public:
			Sint32					GetEventData() const;
			void*					GetEventDataPtr() const;

		// list browser events support
		public:
			EListBrowserEventType	GetListBrowserEvent(size_t& outRowIndex, size_t& outColumnIndex) const;
			bool					IsListBrowserDoubleClickEvent() const;
			bool					IsListBrowserDrawNDropEnd() const;
			bool					IsListBrowserNextMessageIsDropInfo() const;

			SListBrowserDragDropInfo*	GetListBrowserDropInfo();


		// pull down menu events support
		public:
			bool					IsPullDownNotification() const;

		// image popup events support (call SetAdvanced to enable)
		public:
			bool					IsImagePopupSelected() const;
			bool					IsImagePopupBeforeOpen() const;
			bool					IsImagePopupCategoryChanged(size_t& outCategoryIndex);

		// tree control events support
		public:
			TTreeItemID				GetTreeCtrlClickItemID() const;
			bool					IsTreeCtrlSelectionChanged() const;
			bool					IsTreeCtrlDoubleClickEvent() const;
			bool					IsTreeCtrlClickOnIcon() const;
			bool					IsTreeCtrlClickOnCheckBox() const;
			void					GetTreeCtrlModifiers(bool& outShiftDown, bool& outCtrlDown, bool& outAltDown) const;
			bool					GetTreeCtrlKeyClick(Sint32& outKeyCode) const;

		// custom control events support
		public:
			bool					IsCustomCtrlMouseDown() const;
			bool					IsCustomCtrlClickEvent() const;
			bool					IsCustomCtrlDoubleClickEvent() const;
			bool					IsCustomCtrlRightClickEvent() const;
			bool					IsCustomCtrlRightDoubleClickEvent() const;
			bool					IsCustomCtrlMiddleClickEvent() const;
			bool					IsCustomCtrlMiddleDoubleClickEvent() const;
			Sint32					GetCustomCtrlEventPosX() const;
			Sint32					GetCustomCtrlEventPosY() const;

		// edit field control events support
		public:
			EEditFieldEventType		GetEditFieldEvent() const;

		// search edit field control events support
		public:
			ESearchEditFieldEventType	GetSearchEditFieldEvent() const;
			bool						IsSearchEditCommitted() const; // Returns true when the user commits a text to search
			
		public:
			Sint32				fDialogID;
			Sint32				fControlID;
			void*				fpData;
			bool				fbNegativeControlID;
		};

		// ---------------------------------------------------------------------------------------------------------------
		class VWListBrowserEventArgs
		{
			friend class VWDialog;
		protected:
									VWListBrowserEventArgs(TControlID dlgID, TItemMessageData& data);
		public:
			virtual					~VWListBrowserEventArgs();

		public:
			EListBrowserDirectEditType		GetType();
			EListBrowserDirectEditType		GetType(size_t& outRowIndex, size_t& outColumnIndex);

			size_t		GetRowIndex();
			size_t		GetColumnIndex();

			// EListBrowserDirectEditType::QueryInteractionHandlingType
			void		SetInteractionHandlingType(EListBrowserItemInteractionType type);

			// Use this function to notify the shell list browser system that the value supplied from a direct editing
			// operation is not a valid value.  This will set the fReturnCode in the message to false.  This must be 
			// called AFTER the corresponding GetCellString() or GetCell...() call is made.
			void		SetInvalidEditCompletionData();

			// EListBrowserDirectEditType::QueryItemValue              
			// EListBrowserDirectEditType::QueryItemListRetrieval
			// EListBrowserDirectEditType::ItemEditCompletionData
			CGSStringValueChange&					GetCellString();
			CGSColorValueChange&					GetCellColor();
			CGSPatternValueChange&					GetCellPattern();
			CGSPatternWithColorValueChange&			GetCellPatternWithColor();
			CGSHatchStyleValueChange& 				GetCellHatchStyle();
			CGSGradientValueChange& 				GetCellGradient();
			CGSImageResourceValueChange&			GetCellImageResource();
			CGSTileResourceValueChange& 			GetCellTileResource();
			CGSLineTypeValueChange& 				GetCellLineType();
			CGSLineWeightValueChange& 				GetCellLineWeight();
			CGSLineEndValueChange& 					GetCellLineEnd();
			CGSMenuItemCollection& 					GetCellMenuItemCollection();
			CGSMenuItemValue& 						GetCellMenuItemValue();
			CGSMultiStateValueChange&				GetCellCheckbox();
			CGSClassAndLayerPulldownCollection&		GetCellClassLayerPulldownCollection();
			CGSClassAndLayerPulldownItemValue&		GetCellClassLayerPulldownValue();
			CGSListItemValue&						GetCellListItemValue();
			CGSSearchablePulldownCollection&		GetCellSearchablePulldownCollection();
			CGSSearchablePulldownItemValue&			GetCellSearchablePulldownItemValue();

		private:
			TControlID			fDialogID;
			TItemMessageData&	fData;			
		};

		// ---------------------------------------------------------------------------------------------------------------
		template<class T> class CDialogEventHandlers
		{
		public:
			typedef void(T::*TEventDispatchCallback)(TControlID controlID, VWDialogEventArgs& eventArgs);
			typedef void(T::*TListBrowserDirectEditCallback)(TControlID controlID, VWListBrowserEventArgs& eventArgs);

			CDialogEventHandlers()											{ fDispatchCallback = nullptr; fLBDirectEditCallback = nullptr; }
			CDialogEventHandlers(TEventDispatchCallback callback)			{ fDispatchCallback = callback; fLBDirectEditCallback = nullptr; }
			CDialogEventHandlers(TListBrowserDirectEditCallback callback)	{ fLBDirectEditCallback = callback; fDispatchCallback = nullptr; }

			void Set(TEventDispatchCallback callback)			{ fDispatchCallback = callback; }
			void Set(TListBrowserDirectEditCallback callback)	{ fLBDirectEditCallback = callback; }

			void Call(T & obj, TControlID controlID, VWDialogEventArgs& eventArgs)
			{
				if ( fDispatchCallback )
					(obj.*fDispatchCallback)(controlID, eventArgs);
			}

			void Call(T & obj, TControlID controlID, VWListBrowserEventArgs& eventArgs)
			{
				if ( fLBDirectEditCallback )
					(obj.*fLBDirectEditCallback)(controlID, eventArgs);
			}

		private:
			TEventDispatchCallback			fDispatchCallback;
			TListBrowserDirectEditCallback	fLBDirectEditCallback;
		};
	}
}
