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
		class VWEditTextCtrl : public VWControl
		{
		public:
							VWEditTextCtrl(TControlID id);
			virtual			~VWEditTextCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& text, short widthInStdChar, short heightInLines=1);

		// attributes
		public:
			TXString		GetText() const;
			void			SetText(const TXString& text);

			void			SelectContent();
			void			DeselectContent();
			void			GetSelectionRange(Sint32& startPos, Sint32& endPos);
			void			SetSelectionRange(Sint32& startPos, Sint32& endPos);
		};
	}
}