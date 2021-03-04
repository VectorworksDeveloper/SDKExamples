#pragma once

namespace DemoSystem
{
	namespace UI
	{
		class CDlgSystemObjPrefs : public VWDialog
		{
		public:
								CDlgSystemObjPrefs(short type);
			virtual				~CDlgSystemObjPrefs();


			short				GetSystemValue() const;
		// virtuals
		protected:
			virtual bool		CreateDialogLayout();
			virtual void		OnInitializeContent();
			virtual void		OnDDXInitialize();
			virtual void		OnUpdateUI();

		// events
		protected:

		// dispatch map
		protected:
			DEFINE_EVENT_DISPATH_MAP;

		// DDX
		protected:
			short                     fSysObjTypePopup;

		// Inner data
		private:

		};
	}
}
