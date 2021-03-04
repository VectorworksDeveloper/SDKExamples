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
		class VWSliderCtrl : public VWControl
		{
		public:
							VWSliderCtrl(TControlID id);
			virtual			~VWSliderCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, Sint32 lSliderSize);

		// attributes
		public:
			Sint32			GetSliderValue() const;
			void			SetSliderValue(Sint32 value);

			void			SetSliderLiveUpdate(bool liveUpdate);
		};
	}
}