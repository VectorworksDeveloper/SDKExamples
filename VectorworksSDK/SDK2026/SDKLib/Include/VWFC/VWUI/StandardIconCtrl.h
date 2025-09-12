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
		// ----------------------------------------------------------------------
		enum EStandardIconType {
			kStandardIconVectorWorks		= 0,
			kStandardIconInformation		= 1,
			kStandardIconStop				= 2,
			kStandardIconExclamation		= 3,
			kStandardIconQuestion			= 4
		};

		// ----------------------------------------------------------------------
		class VWStadanrdIconCtrl : public VWControl
		{
		public:
							VWStadanrdIconCtrl(TControlID id);
			virtual			~VWStadanrdIconCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, EStandardIconType icon);

		// attributes
		public:

		};
	}
}