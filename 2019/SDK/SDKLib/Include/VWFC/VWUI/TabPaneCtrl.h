//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "ControlsContainer.h"
#include "DialogEventArgs.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWTabPaneCtrl : public VWControlsContainer
		{
			friend class VWDialog;
		public:
							VWTabPaneCtrl(TControlID id);
			virtual			~VWTabPaneCtrl();

			virtual bool	CreateControl(VWDialog* pDlg, const TXString& text, bool bHasFrame=true);

		// events
		protected:
			virtual void			OnSetUpEvent();
			virtual void			OnSetDownEvent();
			virtual void			OnUpdateUI();
			virtual bool			CanEnableOK();
			virtual	void			OnDDXInitialize();
			virtual void			OnInitializeContent();

		// events dispatcher map
		protected:
			DEFINE_EVENT_DISPATH_MAP;
		};
	}
}