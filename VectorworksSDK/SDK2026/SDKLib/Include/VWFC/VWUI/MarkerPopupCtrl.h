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
		// ---------------------------------------------------------------
		class VWMarkerPopupCtrl : public VWControl
		{
		public:
							VWMarkerPopupCtrl(TControlID id);
			virtual			~VWMarkerPopupCtrl();

			virtual bool	CreateControl(VWDialog* pDlg);

		// attributes
		public:
			void			GetSelectedItem(SMarkerStyle& outValue) const;
			void			SetSelectedItem(const SMarkerStyle& value);

			void			ShowByClassChoice();
			void			SelectClassChoice(bool select);
			bool			IsClassChoiceSelected();
		};
	}
}