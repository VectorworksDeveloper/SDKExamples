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
		class VWPatternPopupCtrl : public VWControl
		{
		public:
							VWPatternPopupCtrl(TControlID id);
			virtual			~VWPatternPopupCtrl();

			virtual bool	CreateControl(VWDialog* pDlg);

		// attributes
		public:
			void			GetSelectedPattern(short& outPatternIndex, RGBColor& outForeColor, RGBColor& outBackColor) const;
			void			SetSelectedPattern(short patternIndex, const RGBColor& foreColor, const RGBColor& backColor);

		};
	}
}