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
		class VWListBoxCtrl : public VWControl
		{
		public:
							VWListBoxCtrl(TControlID id);
			virtual			~VWListBoxCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, short widthInStdChar, short heightInLines=1);

		// attributes
		public:
			void			Clear();
			void			AddItem(const TXString& itemText, size_t insertAt = (size_t)-1, Sint32 marker = 0 );

			void			Erase(size_t itemIndex);

			size_t			GetItemsCount() const;
			size_t			GetItemIndex(const TXString& itemText) const;
			void			GetItemText(size_t itemIndex, TXString& outText) const;
			void			SetItemText(size_t itemIndex, const TXString& text);

			Sint32			GetItemMarker(size_t itemIndex) const;
			void			SetItemMarker(size_t itemIndex, Sint32 marker);

			size_t			GetSelectedIndex() const;
			void			SelectIndex(size_t itemIndex);
			void			DeselectAll();

			Sint32			GetSelectedItemMarker() const;
			bool			SelectItemWithMarker(Sint32 marker);

			void			AddTabStop(size_t size);
			void			RemoveLastTabStop();

			// for multi-line ListBox (CreateListBoxN)
			size_t			GetSelectedItemsCount();
			void			GetSelectedItemIndices(TSizeTArray& outArray) const;

		private:
			typedef std::vector<Sint32>		TMarkersArray;

			TMarkersArray		farrIndexToMarker;
		};
	}
}