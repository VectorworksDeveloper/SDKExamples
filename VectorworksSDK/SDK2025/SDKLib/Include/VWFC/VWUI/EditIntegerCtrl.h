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
		class VWEditIntegerCtrl : public VWControl
		{
		public:
							VWEditIntegerCtrl(TControlID id);
			virtual			~VWEditIntegerCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, Sint32 lDefaultValue, short widthInStdChar);

		// attributes
		public:
			Sint32			GetEditInteger() const;
			bool			GetEditInteger(Sint32& outValue) const;
			void			SetEditInteger(Sint32 value);
			void			SelectContent();

		};
	}
}