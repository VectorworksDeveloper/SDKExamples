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
		class VWTabPaneCtrl;
		class VWTabCtrl : public VWControl
		{
		public:
							VWTabCtrl(TControlID id);
			virtual			~VWTabCtrl();

			virtual bool	CreateControl(VWDialog* pDlg);
			void			AddPane(VWTabPaneCtrl* pPane);

			TControlID		GetActivePaneControlID() const;
			void			SetActivePaneControlID(TControlID paneControlID);
		};
	}
}