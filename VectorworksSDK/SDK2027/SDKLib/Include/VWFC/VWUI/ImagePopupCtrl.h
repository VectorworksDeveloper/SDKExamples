//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Control.h"
#include "VWFC/Tools/VWResourceList.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWImagePopupCtrl : public VWControl
		{
		public:
								VWImagePopupCtrl(TControlID id);
			virtual				~VWImagePopupCtrl();

			virtual bool		CreateControl(VWDialog* pDlg);
			void 				SetAdvanced(); // enable advanced messageing

		// attributes
		public:
			void				RefreshControl();

			bool				Clear();

			bool				RemoveItem(size_t index);
			size_t				AddItem(InternalIndex objectIndex);
			size_t				AddItem(const VWFC::Tools::VWResourceList& resourcList, size_t resourceIndex);
			void				AddItems(const VWFC::Tools::VWResourceList& resourcList);
			size_t				AddItemSeparator(const TXString& label);

			size_t				GetItemsCount() const;
			InternalIndex		GetItemInternalIndex(size_t index) const;
			size_t				GetItemIndex(InternalIndex internalIndex) const;

			size_t				GetSelectedItemIndex() const;
			bool				SetSelectedItemIndex(size_t index);

			// SetCategories is typically called during the popup open (reported by an event when SetAdvanced)
			void 				SetCategories(const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex);

			// Pull Down Resource Layout
		public:
			void				PullDownResourceLayoutInit(VectorWorks::Extension::IResourceManagerContent* content);
			void				PullDownResourceLayoutSetSelectedResourceName(const TXString & name); // If the name is empty, then default value will be initialised.
			TXString			PullDownResourceLayoutGetSelectedResourceName() const;
			void				ShowImage( bool showImage );
		};
	}
}
