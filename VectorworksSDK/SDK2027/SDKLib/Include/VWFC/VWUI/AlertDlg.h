//
//	Copyright 2026 Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VWFC
{
	namespace VWUI
	{
		class CAlertDialog
		{
		public:

			CAlertDialog();
			CAlertDialog(const TXString& title);
			CAlertDialog(const TXString& title, EAlertParameterType type);
			CAlertDialog(const TXString& title, EAlertParameterPriority priority);
			CAlertDialog(const TXString& title, EAlertParameterType type, EAlertParameterPriority priority);
			CAlertDialog(const TXString& title, EAlertParameterCheckboxBehavior checkboxBehavior);
			CAlertDialog(const SAlertParameters& params);
		
			// Use for blocking alerts where the result is needed immediately or notifications where you don't need to handle user feedback.
			SAlertResult	ShowAlert();
			
			// Useful for non-blocking notification to handle the result when the dialog actually closes.
			// Note: you still need to set the EAlertParameterPriority parameter to Notification to get one.
			void			ShowAlert(std::function<void(const SAlertResult&)> resultCallback);
			
			CAlertDialog&	SetPriority(EAlertParameterPriority value);
			CAlertDialog&	SetType(EAlertParameterType value);
			CAlertDialog&	SetTitle(const TXString& value);
			CAlertDialog&	SetMessage(const TXString& value);
		
			CAlertDialog&	AddButtonOk();
			CAlertDialog&	AddButtonCancel();
			CAlertDialog&	AddButtonOkCancel();
			CAlertDialog&	AddButtonYesNo();
			CAlertDialog&	AddButtonYesCancel();
			CAlertDialog&	SetButtons(const std::vector<TXString>& value);
			CAlertDialog&	SetDefaultButtonIndex(Sint8 index);
		
			CAlertDialog&	SetCheckbox(const TXString& customText, EAlertParameterCheckboxBehavior behavior = EAlertParameterCheckboxBehavior::Custom);
			CAlertDialog&	SetSavedSettings(const TXString& category, const TXString& key);
			
			CAlertDialog&	SetLink(const TXString& linkText, const TXString& linkURL);
			
		private:
			SAlertParameters	fParams;
		};
	}
}
