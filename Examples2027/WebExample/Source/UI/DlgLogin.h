#pragma once

namespace UI
{
	class CDlgLogin : public VWDialog
	{
	public:
							CDlgLogin(bool alreadyLoggedIn, const TXString& email, const TXString& password, bool rememberLoginInfo);
		virtual				~CDlgLogin();

		bool	WasCreateUserRequested() const;
		bool	WasResetUserPasswordRequested() const;
		void	GetData(TXString& outEmail, TXString& outPassword, bool& outRememberLoginInfo);

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
		void				OnNoAccessStaticText(TControlID controlID, VWDialogEventArgs& eventArgs);
		void				OnRegisterAccountStaticText(TControlID controlID, VWDialogEventArgs& eventArgs);

		// DDX
	protected:
		bool		fWasCreateUserRequested;
		bool		fWasResetUserPasswordRequested;
		TXString	fUsername;
		TXString	fPassword;
		bool		fRememberLoginInfo;

		// Inner data
	private:
		bool		fAlreadyLoggedIn;
		bool		fIsDemoUser;
	};
}