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
			kListBrowserEventType_DragAndDrop					= -51,
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

		public:
			Sint32				fDialogID;
			Sint32				fControlID;
			void*				fpData;
			bool				fbNegativeControlID;
		};
	}
}