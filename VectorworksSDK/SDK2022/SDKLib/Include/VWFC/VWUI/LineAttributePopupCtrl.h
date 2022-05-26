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
		class VWLineAttributePopupCtrl : public VWControl
		{
		public:
							VWLineAttributePopupCtrl(TControlID id);
			virtual			~VWLineAttributePopupCtrl();

			virtual bool	CreateControl(VWDialog* pDlg);

		// attributes
		public:
			void			GetSelectedLineTypeAttribute(InternalIndex& outLineType, short& outLineWeight) const;  //replaces GetSelectedAttribute
			void			SetSelectedLineTypeAttribute(InternalIndex lineType, short lineWeight);				   //replaces SetSelectedAttribute

			void			ShowByClassChoice();
			void			SelectClassChoice(bool select);
			bool			IsClassChoiceSelected();
		};
	}
}