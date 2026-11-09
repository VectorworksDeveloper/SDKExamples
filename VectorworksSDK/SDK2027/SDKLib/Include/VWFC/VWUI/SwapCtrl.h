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
		class VWSwapPaneCtrl;
		class VWSwapCtrl : public VWControl
		{
		public:
							VWSwapCtrl(TControlID id);
			virtual			~VWSwapCtrl();

			virtual bool	CreateControl(VWDialog* pDlg);
			void			AddPane(VWSwapPaneCtrl* pPane);

			size_t			GetActivePaneIndex() const;
			void			SetActivePaneIndex(size_t paneIndex);

		};
	}
}