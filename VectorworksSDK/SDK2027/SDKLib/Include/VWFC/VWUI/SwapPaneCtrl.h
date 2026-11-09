//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "ControlsContainer.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWSwapPaneCtrl : public VWControlsContainer
		{
		public:
							VWSwapPaneCtrl(TControlID id);
			virtual			~VWSwapPaneCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, bool bHasFrame=true);
		};
	}
}