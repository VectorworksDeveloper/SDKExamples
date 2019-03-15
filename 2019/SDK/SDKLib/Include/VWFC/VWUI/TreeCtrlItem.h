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
		// ---------------------------------------------------------------------------------------------------------------
		class VWTreeCtrlItem;
		class VWTreeCtrl;

		// ---------------------------------------------------------------------------------------------------------------
		typedef Sint32		TTreeItemID;

		// ---------------------------------------------------------------------------------------------------------------
		class VWTreeCtrlContainer
		{
			friend class VWTreeCtrlItem;
		protected:
									VWTreeCtrlContainer(TControlID dialogID, TControlID controlID, TTreeItemID itemID);

		public:
									VWTreeCtrlContainer(const VWTreeCtrlContainer& src);
			virtual					~VWTreeCtrlContainer();

			VWTreeCtrlContainer&	operator=(const VWTreeCtrlContainer& src);
			bool					operator==(const VWTreeCtrlContainer& src);
			bool					operator!=(const VWTreeCtrlContainer& src);

		public:
			bool			IsValid() const;

			VWTreeCtrlItem	GetParentItem() const;

			size_t			GetChildItemsCount() const;
			VWTreeCtrlItem	GetChildItemAt(size_t index) const;

			VWTreeCtrlItem	AddChildItem(const TXString& text, bool addFirst = false);
			VWTreeCtrlItem	InsertChildItem(const TXString& text, const VWTreeCtrlItem& afterItem);
			void			DeleteItem();

		public:
			static VWTreeCtrlItem	kEmptyTreeItem;

		protected:
			TControlID			fDialogID;
			TControlID			fThisControlID;
			TTreeItemID			fThisItemID;
		};

		// ---------------------------------------------------------------------------------------------------------------
		class VWTreeCtrlItem : public VWTreeCtrlContainer
		{
			friend class VWTreeCtrlContainer;
			friend class VWTreeCtrl;
		public:
									VWTreeCtrlItem();
									VWTreeCtrlItem(const VWTreeCtrlItem& src);
			virtual					~VWTreeCtrlItem();

			VWTreeCtrlItem&			operator=(const VWTreeCtrlItem& src);
			bool					operator==(const VWTreeCtrlItem& src);
			bool					operator!=(const VWTreeCtrlItem& src);

		public:
			TTreeItemID				GetItemID() const;

			TXString				GetItemText() const;
			void					SetItemTextRight(const TXString & text);

			void 					SetItemImage(const TXString & imageSpecifier);
			void 					SetItemImageFromIcon(VectorWorks::UI::IIcon* icon);
			void 					SetItemAsDivider(bool isDivider = true);

			bool					GetItemCheck(ECheckButtonCtrlState& outState) const;
			ECheckButtonCtrlState	GetItemCheck() const;
			void					SetItemCheck(ECheckButtonCtrlState state);

			void					ExpandItem(bool bExpand);

			void					SelectItem();
			void					SelectItem(bool selectionState);

			void					SetItemData(SintptrT data);
			SintptrT				GetItemData() const;

		protected:
							VWTreeCtrlItem(TControlID dialogID, TControlID controlID, TTreeItemID itemID);

		};
	}
}
