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
		class VWEditPasswordCtrl : public VWControl
		{
		public:
							VWEditPasswordCtrl(TControlID id);
			virtual			~VWEditPasswordCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, short widthInStdChar);

		// attributes
		public:
			TXString		GetText() const;
			void			SetText(const TXString& text);

			void			SelectContent();
			void			DeselectContent();

		};
	}
}