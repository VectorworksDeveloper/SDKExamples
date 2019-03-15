//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Control.h"
#include "TreeCtrlItem.h"

namespace VWFC
{
	namespace VWUI
	{
		// ---------------------------------------------------------------------------------------------------------------
		class VWTreeCtrl	: public VWControl
							, public VWTreeCtrlContainer
		{
		public:
							VWTreeCtrl(TControlID id);
			virtual			~VWTreeCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, short widthInStdChar, short heightInLines=1);

			virtual bool	EnableDragAndDrop(bool enable);

			// this control and the 'dragToCtrl' must be on the same dialog
			virtual void	EnableDrag(const VWTreeCtrl& dragToCtrl);

			typedef std::function<bool(VWTreeCtrlItem item)>	TShowCallback;
			typedef std::function<void(VWTreeCtrlItem item)>	THandleCallback;

			// will display a button on the right for each item
			// Enabling button column will disable the display of the right text (VWTreeCtrlItem::SetItemTextRight)
			virtual void	EnableButtonColumn(const TXString& text, TShowCallback showForItemCallback, THandleCallback handleForItemCallback);

		public:
			void			Clear();

			VWTreeCtrlItem	GetItem(TTreeItemID itemID);

			VWTreeCtrlItem	GetSelectedItem();
			bool			GetSelectedItem(TXString& outText);

			void			CopySubtree(const VWTreeCtrl& targetTree, const VWTreeCtrlItem& sourceItem, const VWTreeCtrlItem& targetItem);

		protected:
			virtual void	AttachControl();

		private:
			// managing tree control button column
			typedef std::map< std::pair<Sint32,Sint32>, VWTreeCtrl*>	TDlgTreeCtrlMap;
			static TDlgTreeCtrlMap		s_DlgReeCtrlMap;
			static bool			_ShowButtonColumn(Sint32 dialogID, Sint32 controlID, int itemID);
			static void			_HandleButtonColumn(Sint32 dialogID, Sint32 controlID, int itemID);

			TShowCallback		fButtonColumnShowCallback;
			THandleCallback		fButtonColumnHandleCallback;
			bool				ShowButtonColumn(int itemID);
			void				HandleButtonColumn(int itemID);
		};
	}
}