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
		class VWThumbnailPopupCtrl : public VWControl
		{
		public:
							VWThumbnailPopupCtrl(TControlID id);
			virtual			~VWThumbnailPopupCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, ThumbnailSizeType sizeType = kStandardSize);

		// attributes
		public:
			void			RemoveAllImages();
			void			AddImage(InternalIndex item);
			void			AddImageFromResource(Sint32 listID, size_t index);
			bool			RemoveItem(size_t itemIndex);
			bool			SelectItem(size_t itemIndex);
			bool			SelectItem(InternalIndex item);
			InternalIndex	GetItemObject(size_t itemIndex) const;
			size_t			GetObjectItemIndex(InternalIndex item) const;
			size_t			GetSelectedItemIndex() const;
			InternalIndex	GetSelectedItem() const;
			size_t			GetItemsCount() const;

		};
	}
}