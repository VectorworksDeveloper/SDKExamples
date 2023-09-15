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
		class VWLineWeightPopupCtrl : public VWControl
		{
		public:
							VWLineWeightPopupCtrl(TControlID id);
			virtual			~VWLineWeightPopupCtrl();

			virtual bool	CreateControl(VWDialog* pDlg);

		// attributes
		public:
			short			GetSelectedLineWeight() const;
			void			SetSelectedLineWeight(short lineWeight);

			void			ShowByClassChoice();
			void			SelectClassChoice(bool select);
			bool			IsClassChoiceSelected();
		};
	}
}