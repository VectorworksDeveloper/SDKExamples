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
		// ---------------------------------------------------------------------------------------
		class VWBorderlessButtonCtrl : public VWControl
		{
		public:
							VWBorderlessButtonCtrl(TControlID id);
			virtual			~VWBorderlessButtonCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& title, const TXString& iconResPath, const bool isToggleButton = false, const EButtonImagePos imagePos = EButtonImagePos::kImageAbove);

		// attributes
		public:
			bool					GetState() const;
			void					SetState(bool state);
			
			bool 					UpdateImage(const TXString &imageSpec);
		};
	}
}
