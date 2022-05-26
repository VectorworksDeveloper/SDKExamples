//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Control.h"
#include "DialogEventArgs.h"

namespace VWFC
{
	namespace VWUI
	{
		class VWControlsContainer : public VWControl
		{
			friend class VWDialog;
		public:
								VWControlsContainer(TControlID id);
			virtual				~VWControlsContainer();

			bool				CreateControl(VWDialog* pDlg);

		// child control managment
		public:
			virtual void		AddFirstGroupControl(VWControl* pControl);

		// events
		public:
			virtual void			OnSetUpEvent();
			virtual void			OnSetDownEvent();
			virtual void			OnInitializeContent();
			virtual void			OnUpdateUI();
			virtual bool			CanEnableOK();
			virtual	void			OnDDXInitialize();
			virtual void			OnBeforeDispatchEvent(TControlID controlID, VWDialogEventArgs& eventArg);
			virtual void			OnDefaultButtonEvent();
			virtual void			OnCancelButtonEvent();

		// events dispatcher map
		public:
			DEFINE_EVENT_DISPATH_MAP;
			std::shared_ptr<void> fEventHandlers;

			// add event handles with the DEFINE_EVENT_DISPATH_MAP macros
			// here are example event handlers
			//void				OnMyControl(TControlID controlID, VWDialogEventArgs& eventArgs);
			//void				OnMyListBrowserDirectEdit(TControlID controlID, VWListBrowserEventArgs& eventArgs);
		};
	}
}