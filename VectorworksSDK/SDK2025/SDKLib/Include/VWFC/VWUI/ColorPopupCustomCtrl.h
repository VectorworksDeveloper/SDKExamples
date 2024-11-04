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
		class VWColorPopupCustomCtrl : public VWControl
		{
		public:
								VWColorPopupCustomCtrl(TControlID id);
			virtual				~VWColorPopupCustomCtrl();

			virtual bool		CreateControl(VWDialog* pDlg);

		// attributes
		public:
			ColorRef			GetSelectedColor() const;
			void				SetSelectedColor(const ColorRef& color);
		};
	}
}