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
		class VWSearchBoxCtrl : public VWControl
		{
		public:
							VWSearchBoxCtrl(TControlID id);
			virtual			~VWSearchBoxCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& promptText, short widthInStdChar);

		// attributes
		public:
			TXString		GetSearchText() const;
			void			SetSearchText(const TXString& text);

			void			SelectContent();
			void			DeselectContent();

		};
	}
}