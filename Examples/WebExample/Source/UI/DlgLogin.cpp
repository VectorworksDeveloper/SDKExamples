#include "StdAfx.h"

#include "DlgLogin.h"

// dialog control IDs
#define		kOK                        1
#define		kCancel                    2
#define		kMainLbl                   4
#define		kCredentialsStaticTextGrp  6
#define		kUsernameStaticText        7
#define		kUsernameEditTextBox       8
#define		kPasswordStaticText        9
#define		kPasswordEditTextBox       10
#define		kRememberCheckBox          11
#define		kNoAccessStaticText        12
#define		kRegisterAccountStaticText 13

// custom strings IDs
#define		kStr_LogoutButton          TXResStr("DlgLogin", "LogoutButton")				// Log Out
#define		kStr_LogoutDialogTitle     TXResStr("DlgLogin", "LogoutDialogTitle")		// Log Out
#define		kStr_LogoutButtonHelpTxt   TXResStr("DlgLogin", "LogoutButtonHelpTxt")		// Click to log out.
#define		kStr_LogoutMainLblTxt      TXResStr("DlgLogin", "LogoutMainLblTxt")			// Log out of the account in use.


using namespace UI;

EVENT_DISPATCH_MAP_BEGIN(CDlgLogin);
ADD_DISPATCH_EVENT(kNoAccessStaticText, OnNoAccessStaticText);
ADD_DISPATCH_EVENT(kRegisterAccountStaticText, OnRegisterAccountStaticText);
EVENT_DISPATCH_MAP_END;

CDlgLogin::CDlgLogin(bool alreadyLoggedIn, const TXString& username, const TXString& password, bool rememberLoginInfo)
	: fWasCreateUserRequested(false)
	, fWasResetUserPasswordRequested(false)
	, fIsDemoUser(false)
{
	// Assign settings tag to this dialog so it would save it's position and size automatically
	this->SetSavedSettingsTag("Data", "CDlgLogin");

	fAlreadyLoggedIn = alreadyLoggedIn;
	fUsername = username;
	fPassword = password;
	fRememberLoginInfo = rememberLoginInfo;

	// from ProtectionAPI.h
	const Uint16	kModeEducation = 0x0004;
	const Uint16	kModeStudent = 0x0008;
	short protectionMode = gSDK->GetCurrentMode();
	fIsDemoUser = (protectionMode & kModeEducation) || (protectionMode & kModeStudent);
}

CDlgLogin::~CDlgLogin()
{
}

bool CDlgLogin::WasCreateUserRequested() const
{
	return !fIsDemoUser && fWasCreateUserRequested;
}

bool CDlgLogin::WasResetUserPasswordRequested() const
{
	return fWasResetUserPasswordRequested;
}

void CDlgLogin::GetData(TXString& outEmail, TXString& outPassword, bool& outRememberLoginInfo)
{
	outEmail = fUsername;
	outPassword = fPassword;
	outRememberLoginInfo = fRememberLoginInfo;
}

bool CDlgLogin::CreateDialogLayout()
{
	VectorWorks::Scripting::IVectorScriptEnginePtr	vsEngine(VectorWorks::Scripting::IID_VectorScriptEngine);
	if (vsEngine)
	{
		VWVariant	varParamsList(!fAlreadyLoggedIn);
		vsEngine->Repository_SetValue("AccLinks", varParamsList);
	}

	return this->CreateDialogLayoutFromVWR(TXString(DefaultPluginVWRIdentifier())+"/DialogLayout/DlgLogin.vs");
}

void CDlgLogin::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	if (fAlreadyLoggedIn)
	{
		this->SetDialogTitle(kStr_LogoutDialogTitle);
		this->GetStaticTextCtrlByID(kMainLbl)->SetControlText(kStr_LogoutMainLblTxt);
		this->GetPushButtonCtrlByID(kOK)->SetControlText(kStr_LogoutButton);
		this->GetPushButtonCtrlByID(kOK)->SetHelpText(kStr_LogoutButtonHelpTxt);
	}

	if (!fAlreadyLoggedIn)
	{
		this->GetStaticTextCtrlByID(kNoAccessStaticText)->SetClickable(true);
		this->GetStaticTextCtrlByID(kRegisterAccountStaticText)->SetClickable(true);
	}
}

void CDlgLogin::OnDDXInitialize()
{
	this->AddDDX_EditText(kUsernameEditTextBox, &fUsername);
	this->AddDDX_EditPassword(kPasswordEditTextBox, &fPassword);
	this->AddDDX_CheckButton(kRememberCheckBox, &fRememberLoginInfo);
}

void CDlgLogin::OnUpdateUI()
{
	VWDialog::OnUpdateUI();

	if (!fAlreadyLoggedIn)
		this->ShowControl(kRegisterAccountStaticText, !fIsDemoUser);

	this->EnableControl(kUsernameEditTextBox, !fAlreadyLoggedIn);
	this->EnableControl(kPasswordEditTextBox, !fAlreadyLoggedIn);

	this->ShowControl(kNoAccessStaticText, !fAlreadyLoggedIn);
	this->ShowControl(kRegisterAccountStaticText, !fAlreadyLoggedIn);
}

void CDlgLogin::OnNoAccessStaticText(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	fWasResetUserPasswordRequested = true;
	VWDialog::SetDialogClose(true);
}

void CDlgLogin::OnRegisterAccountStaticText(TControlID controlID, VWDialogEventArgs& eventArgs)
{
	if (!fIsDemoUser)
	{
		fWasCreateUserRequested = true;
		VWDialog::SetDialogClose(true);
	}
}


