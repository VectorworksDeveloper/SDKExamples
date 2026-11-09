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
		class VWColorButtonCtrl : public VWControl
		{
		public:
								VWColorButtonCtrl(TControlID id);
			virtual				~VWColorButtonCtrl();

			virtual bool		CreateControl(VWDialog* pDlg);

		// attributes
		public:
			RGBColor			GetColor() const;
			
			void				GetColor(RGBColor& color);
			void				GetColor(TGSColorV2& color);

			void				SetColor(const RGBColor& color);
			void				SetColor(const TGSColorV2& color);
		};
	}
}
