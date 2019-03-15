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
		class VWControlsContainer : public VWControl
		{
		public:
								VWControlsContainer(TControlID id);
			virtual				~VWControlsContainer();

			bool				CreateControl(VWDialog* pDlg);

		// child control managment
		public:
			virtual void		AddFirstGroupControl(VWControl* pControl);
		};
	}
}