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
		class VWRadioGroupBoxCtrl : public VWControlsContainer
		{
		public:
							VWRadioGroupBoxCtrl(TControlID id);
			virtual			~VWRadioGroupBoxCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& text, bool bHasFrame=true);
		
		// attributes
		public:
			bool		GetState() const;
			void		SetState(bool state);

		};
	}
}