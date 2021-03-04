//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Control.h"


namespace VWFC
{
	namespace VWUI
	{
		// -----------------------------------------------------------------------------
		enum EColumnHeaderJustification {
			kColumnHeaderJustificationNone		= 0,
			kColumnHeaderJustificationLeft		= 1,
			kColumnHeaderJustificationCenter	= 2,
			kColumnHeaderJustificationRight		= 3
		};

		// -----------------------------------------------------------------------------
		enum EColumnSortState {
			kDescendingSortState				= -1,
			kNoSortState						=  0,
			kAscendingSortState					=  1
		};

		// -----------------------------------------------------------------------------
		class VWListBrowserCtrl;

		// -----------------------------------------------------------------------------
		class VWListBrowserColumn
		{
		friend class VWListBrowserCtrl;
		protected:
										  VWListBrowserColumn(TControlID dialogID, TControlID controlID, short columnID);

		public:
										  VWListBrowserColumn(const VWListBrowserColumn& column);
										  ~VWListBrowserColumn();

			VWListBrowserColumn&		  operator=(const VWListBrowserColumn& column);

		// column specific functions
		public:
			size_t						  GetColumnIndex() const;

			size_t						  GetColumnWidth() const;
			size_t						  GetColumnDataItemsCount() const;

			void						  SetColumnType(EListBrowserControlType columnType);
			EListBrowserControlType		  GetColumnType() const;
			void						  SetAsDragAndDropColumn();
			void						  SetAsHierarchicalDisplayColumn();

			void						  SetSortColumn(bool enable);
			size_t						  GetSortColumn() const;
			EColumnSortState  			  GetColumnSortState() const;
			bool						  SetColumnSortState(EColumnSortState state);

			void						  SetColumnHeaderImage(size_t imageIndex);

			void						  SetColumnHeaderJust(EColumnHeaderJustification justification);
			EColumnHeaderJustification	  GetColumnHeaderJust() const;

			void						  SetColumnHeaderToolTip(const TXString& primaryText, const TXString& subText);
			bool						  GetColumnHeaderToolTip(TXString& outPrimaryText, TXString& outSubText) const;

			void						  SetEditDisplayType(EListBrowserDisplayType displayType);
			EListBrowserDisplayType		  GetEditDisplayType() const;

			void					      SetItemDisplayType(EListBrowserDisplayType displayType);
			EListBrowserDisplayType		  GetItemDisplayType() const;

			bool					      AreRadioColumnLinesEnabled() const;
			bool						  IsTrackingEnabled() const;
			void						  EnableColumnTracking(bool enable) const;
			void						  EnableRadioColumnLines(bool enable) const;

			size_t						  FindColumnDataItem(const TXString& text) const;
			size_t						  FindColumnItem(const TXString& text) const;

			size_t						  InsertColumnChoice(const TXString& text);
			size_t						  InsertColumnChoice(const TXString& text, size_t imageOn);
			size_t						  InsertColumnChoice(const TXString& text, size_t imageOn, size_t imageOff);
			size_t						  InsertColumnChoice(const TXString& text, size_t imageOn, size_t imageOff, size_t itemData);
			bool						  RemoveColumnChoice(size_t choiceIndex);
			void						  RemoveAllColumnChoices();

		protected:
			short						  fColumnID;
			TControlID					  fDialogID;
			TControlID					  fControlID;
		};
	}
}