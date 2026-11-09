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
		class VWRadioButtonCtrl : public VWControl
		{
		public:
							VWRadioButtonCtrl(TControlID id);
			virtual			~VWRadioButtonCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& text);

		// attributes
		public:
			bool		GetState() const;
			void		SetState(bool state);

		};
	}
}