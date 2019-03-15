//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "ControlsContainer.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWSwapPaneCtrl : public VWControlsContainer
		{
			friend class VWDialog;
		public:
							VWSwapPaneCtrl(TControlID id);
			virtual			~VWSwapPaneCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, bool bHasFrame=true);

		// events
		protected:
			virtual void			OnSetUpEvent();
			virtual void			OnSetDownEvent();
			virtual void			OnUpdateUI();
			virtual bool			CanEnableOK();
			virtual	void			OnDDXInitialize();

		// events dispatcher map
		protected:
			DEFINE_EVENT_DISPATH_MAP;
		};
	}
}