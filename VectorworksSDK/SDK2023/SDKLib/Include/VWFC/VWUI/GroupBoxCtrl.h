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
		class VWGroupBoxCtrl : public VWControlsContainer
		{
		public:
							VWGroupBoxCtrl(TControlID id);
			virtual			~VWGroupBoxCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& text, bool bHasFrame=true);

		};
	}
}