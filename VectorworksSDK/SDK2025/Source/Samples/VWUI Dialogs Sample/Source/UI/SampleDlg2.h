#pragma once

namespace UI
{
	class CSampleDlg2 : public VWDialog
	{
	public:
							CSampleDlg2();
		virtual				~CSampleDlg2();

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
		void				OnListBoxControl(TControlID controlID, VWDialogEventArgs& eventArgs);

	// DDX
	protected:

	// Inner data
	private:

	};
}

