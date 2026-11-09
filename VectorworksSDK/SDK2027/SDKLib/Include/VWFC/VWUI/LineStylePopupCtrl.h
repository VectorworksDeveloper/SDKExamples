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
		class VWLineStylePopupCtrl : public VWControl
		{
		public:
							VWLineStylePopupCtrl(TControlID id);
			virtual			~VWLineStylePopupCtrl();

			virtual bool	CreateControl(VWDialog* pDlg);

		// attributes
		public:
			InternalIndex	GetSelectedLineType() const;				 //replaces GetSelectedLineStyle
			void			SetSelectedLineType(InternalIndex lineType); //replaces SetSelectedLineStyle

			void			ShowByClassChoice();
			void			SelectClassChoice(bool select);
			bool			IsClassChoiceSelected();
		};
	}
}