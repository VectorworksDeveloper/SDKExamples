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
		enum EStaticTextCtrlStyle
		{
			eStaticTextCtrlStyle_Regular		= 0,
			eStaticTextCtrlStyle_Bold			= 1,
			eStaticTextCtrlStyle_Italic			= 2,
			eStaticTextCtrlStyle_BoldAndItalic	= 3,
			eStaticTextCtrlStyle_Underlined		= 4,
		};

		class VWStaticTextCtrl : public VWControl
		{
		public:
							VWStaticTextCtrl(TControlID id);
			virtual			~VWStaticTextCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& text, short widthInStdChar=-1, EStaticTextType=eStaticTextTypeRegular);

			void			SetStyle(EStaticTextCtrlStyle style);
			void			SetColor(const Tools::CRGBColor& color, bool atDialogInitTime=true);
			void			SetClickable(bool value);
		};
	}
}