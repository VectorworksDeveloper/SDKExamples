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
		// ---------------------------------------------------------------------------------------
		enum ECheckButtonCtrlState
		{
			eCheckButtonCtrlState_Unchecked		= 0,
			eCheckButtonCtrlState_Checked		= 1,
			eCheckButtonCtrlState_Undetermined	= 2,
		};

		// ---------------------------------------------------------------------------------------
		class VWCheckButtonCtrl : public VWControl
		{
		public:
							VWCheckButtonCtrl(TControlID id);
			virtual			~VWCheckButtonCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& text, bool triState=false);

		// attributes
		public:
			bool					GetState() const;
			void					SetState(bool state);
			ECheckButtonCtrlState	GetThreeState() const;
			void					SetThreeState(ECheckButtonCtrlState state);

		};
	}
}