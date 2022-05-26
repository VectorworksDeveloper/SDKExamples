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
		class VWEditTextColorCtrl : public VWControl
		{
		public:
							VWEditTextColorCtrl(TControlID id);
			virtual			~VWEditTextColorCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, short widthInStdChar, short heightInLines);

		// attributes
		public:
			virtual TXString		GetText() const;
			virtual void			SetText(const TXString& text);
			virtual TXString		GetControlText();
			virtual void			SetControlText(const TXString& text);

			virtual void			SelectContent();
			virtual void			DeselectContent();
			virtual void			GetSelectionRange(Sint32& startPos, Sint32& endPos);
			virtual void			SetSelectionRange(Sint32 startPos, Sint32 endPos);

			// Color Text Box support
			virtual void			SetFocus();
			virtual void			SetReadOnly(bool value);
			virtual void			SetLineEnding(bool CR, bool LF);	// by default the control uses mac-syle (CR only), but this can be used to override this

			virtual void			GoToLine(size_t line);
			virtual void			GoToPos(size_t pos);
			virtual size_t			GetCurrLine();
			virtual size_t			GetCurrPos();
			virtual size_t			GetLineFromPos(size_t pos);

			virtual size_t			GetTextLength();
			virtual void			ClearText();

			virtual bool			SetStyle(const TXString& strStyle, VWVariant* outResult=nullptr, VWVariant* outParam2 = nullptr);
		};
	}
}