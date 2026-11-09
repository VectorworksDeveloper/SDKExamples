#pragma once

#include "Control.h"

namespace VWFC
{
	namespace VWUI
	{
		enum class ETreeNodeType
		{
			  Delimiter
			, Button
			, DataItem
		};

		struct STreeColumnSpec
		{
			TXString    fID;
			TXString    fName;
			int         fWidth;
		};

		struct STreeNodeSpec
		{
			TXString						fID;
			ETreeNodeType					fType;
			bool							fIsGroupOnly = false;	// valid only for Delimiter type, indicates that all the elements in the group are treated as one item
			bool							fIsMandatory = false;	// Items cannot be unchecked, they will be gray.
			std::map<TXString, TXString>    fColumnValues;
		};

		using TTreeNodeSpecArray    = std::vector<STreeNodeSpec>;
		using TTreeColumnSpecArray  = std::vector<STreeColumnSpec>;

		class IVWListBrowserTreeSource
		{
		public:
			virtual ~IVWListBrowserTreeSource() = default;

			virtual void GetColumnSpecs(TTreeColumnSpecArray& out) const = 0;
			virtual void GetAllItems(TTreeNodeSpecArray& out) const = 0;
			virtual void GetSpecialGroupMembership(const TXStringSTLArray arrCheckedIDs, TXStringSTLArray& outArrCheckedGroups) const {};
			virtual void RequiresAdditionalTag(TXStringSTLArray& outCheckedGroups) const {};
		};

		class VWListBrowserTreeCtrl : public VWControl
		{
		public:
							VWListBrowserTreeCtrl(const IVWListBrowserTreeSource& data, const TControlID& id, VWDialog* parentDlg);
			virtual			~VWListBrowserTreeCtrl();

		public:
			void			OnInitializeContent(const TXString& showStr);
			void			BuildListItemsArray(const TXStringSTLArray& arrCheckedIDs, const TXStringSTLArray& arrOpenedIDs);
			void			FillListBrowser();
			void			OnTree(VWDialogEventArgs& eventArgs);
			bool			IsRowOK(size_t rowIndex) const;
			void			GetCheckedData(TXStringSTLArray& outArrCheckedIDs) const;
			void			GetCheckedGroups(const TXStringSTLArray arrCheckedIDs, TXStringSTLArray& outArrCheckedGroups) const;
			void			GetOpened(TXStringSTLArray& outArrOpenedIDs) const;
			void			SetAllToChecked();

		protected:
			void			SetCheck(size_t rowIndex, bool value);
			void			CollapseItems(size_t groupRowIndex, size_t listItem);
			void			ExpandItems(size_t groupRowIndex, size_t listItem);
		
		// Inner data
		private:
			size_t			fImageIndexBlank;
			size_t			fImageIndexCheckmark;
			size_t			fImageIndexCheckmarkDisabled;
			size_t			fImageIndexTreeClosed;
			size_t			fImageIndexTreeOpen;

			struct SListItem
			{
				size_t							fRowIndex;
				bool							fIsGroup;
				bool							fIsGroupOnly = false;
				bool							fIsMandatory = false;
				bool							fIsChecked;
				bool							fIsVisible;
				bool							fIsOpened;
				TXString						fID;
				std::map<TXString, TXString>    fColumnValues;
			};

			typedef std::vector<SListItem>	TListItemArray;
			TListItemArray			farrListItems;
			TSizeTArray				farrLBRowIndex2ListItemIndex;
			TTreeColumnSpecArray    farrColumnSpecs;

		private:
			void GetClickTargetRow(size_t selItemIdx, size_t fallbackRow, size_t& outTargetRow) const;
			void ToggleSelection(const TSizeTArray& selItems, bool value);
			void RestoreSelectionImages(const TSizeTArray& selItems);

			void WriteColumnValues(VWListBrowserCtrl* theList, size_t rowIndex, const std::map<TXString, TXString>& colValues) const;
			void ApplyRowEnabledState(VWListBrowserCtrl* theList, size_t rowIndex, bool enabled) const;
			size_t GetCheckImage(const SListItem& data) const;

			void ResyncRowIndices();

		private:
			const IVWListBrowserTreeSource&	fDataSource; 
		};
	}
}
