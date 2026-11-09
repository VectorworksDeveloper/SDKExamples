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
		class VWColorPopupCtrl : public VWControl
		{
		public:
								VWColorPopupCtrl(TControlID id);
			virtual				~VWColorPopupCtrl();

			virtual bool		CreateControl(VWDialog* pDlg);
			virtual bool		CreateControlWithWidth(VWDialog* pDlg, short width);

		// attributes
		public:
			RGBColor			GetSelectedColor() const;
			void				SetSelectedColor(const RGBColor& color);

			void				ShowByClassChoice();
			void				SelectClassChoice(bool select);
			bool				IsClassChoiceSelected();

			void				ShowColor( bool showColor );
		};
	}
}