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
		class VWPullDownMenuCtrl : public VWControl
		{
		public:
							VWPullDownMenuCtrl(TControlID id);
			virtual			~VWPullDownMenuCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, short widthInStdChar, bool enhanced=false, bool showIconInMainWindow=false);

		// attributes
		public:
			void			Clear();
			void			AddItem(const TXString& itemText, size_t insertAt = (size_t) -1, Sint32 marker = 0);
			void			AddItemSorted(const TXString& itemText, Sint32 marker = 0);

			void			Erase(size_t itemIndex);

			size_t			GetItemsCount() const;
			size_t			GetItemIndex(const TXString& itemText) const;
			void			GetItemText(size_t itemIndex, TXString& outText) const;

			Sint32			GetItemMarker(size_t itemIndex) const;
			void			SetItemMarker(size_t itemIndex, Sint32 marker);

			size_t			GetSelectedIndex() const;
			void			SelectIndex(size_t itemIndex);

			TXString		GetSelectedItem() const;
			void			SelectItem(const TXString& item);

			Sint32			GetSelectedItemMarker() const;
			bool			SelectItemWithMarker(Sint32 marker);

			// Enable sending an item hit notification when the pull down menu is clicked
			// allowing developers to dynamically populate the menu.
			void			EnableNotifyPullDown();

			// Set the indicated item as enabled or disabled, which should cause it to be greyed and not selectable.
			virtual void	SetItemEnabled(size_t itemIndex, bool enabled=true); 

			// enhanced pulldown control
			void			AddItemEnhanced(const TXString& itemText, const TXString& itemResourceSpecifier, Sint32 marker = 0);
			void			RemoveItemEnhanceds();
			bool			RemoveItemEnhanced(size_t startIndex, size_t endIndex = size_t(-1));
			bool			ShowEnhancedGroupIcon(bool showGroupIcon);

			// Pull Down Resource Layout
		public:
			void			PullDownResourceLayoutInit(VectorWorks::Extension::IResourceManagerContent* content);
			void			PullDownResourceLayoutSetSelectedResourceName(const TXString & name); // If the name is empty, the Empty Message from the content will be displayed.
			TXString		PullDownResourceLayoutGetSelectedResourceName() const;

		private:
			typedef std::vector<Sint32>		TMarkersArray;

			TMarkersArray		farrIndexToMarker;
		};
	}
}