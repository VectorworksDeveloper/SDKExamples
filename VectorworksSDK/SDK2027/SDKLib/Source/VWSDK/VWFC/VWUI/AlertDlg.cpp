//
// Copyright Vectorworks, Inc. 2026.
// All Rights Reserved.
//
//
// Started 02/17/26 by Alberto Antonini
//

#include "StdHeaders.h"	// Must be first non-comment line.  See StdHeaders.h for explanation.

#include "VWFC/VWUI/AlertDlg.h"

using namespace VectorWorks;
using namespace VWFC::VWUI;

static const char* kAlertStrings = "Vectorworks/Strings/144 *";
static const char* kOKStr = "1";
static const char* kCancelStr = "6";
static const char* kYesStr = "10";
static const char* kNoStr = "11";
static const char* kYesAlwaysStr = "12";
static const char* kNoAlwaysStr = "13";
static const char* kDontShowDialogAgainStr = "15";
static const char* kAlwaysDoSelectedActionStr = "17";

// ------------------------------------------------------------------------------------------------
CAlertDialog::CAlertDialog()
	: CAlertDialog( SAlertParameters{} )
{
}

// ------------------------------------------------------------------------------------------------
CAlertDialog::CAlertDialog(const TXString& title)
	: CAlertDialog( SAlertParameters{ .fTitle = title } )
{
}

// ------------------------------------------------------------------------------------------------
CAlertDialog::CAlertDialog(const TXString& title, EAlertParameterType type)
	: CAlertDialog( SAlertParameters{ .fType = type, .fTitle = title } )
{
}

// ------------------------------------------------------------------------------------------------
CAlertDialog::CAlertDialog(const TXString& title, EAlertParameterPriority priority)
	: CAlertDialog( SAlertParameters{ .fPriority = priority, .fTitle = title } )
{
}

// ------------------------------------------------------------------------------------------------
CAlertDialog::CAlertDialog(const TXString& title, EAlertParameterType type, EAlertParameterPriority priority)
	: CAlertDialog( SAlertParameters{ .fPriority = priority, .fType = type, .fTitle = title } )
{
}

// ------------------------------------------------------------------------------------------------
CAlertDialog::CAlertDialog(const TXString& title, EAlertParameterCheckboxBehavior checkboxBehavior)
	: CAlertDialog( SAlertParameters{ .fTitle = title, .fCheckboxBehavior = checkboxBehavior } )
{
}

// ------------------------------------------------------------------------------------------------
CAlertDialog::CAlertDialog(const SAlertParameters& params)
	: fParams( params )
{
}

// ------------------------------------------------------------------------------------------------
SAlertResult CAlertDialog::ShowAlert()
{
	return gSDK->ShowAlert( fParams );
}

// ------------------------------------------------------------------------------------------------
void CAlertDialog::ShowAlert(std::function<void(const SAlertResult&)> resultCallback)
{
	gSDK->ShowAlert( fParams, resultCallback );
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::SetPriority(EAlertParameterPriority value)
{
	fParams.fPriority = value;
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::SetType(EAlertParameterType value)
{
	fParams.fType = value;
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::SetTitle(const TXString& value)
{
	fParams.fTitle = value;
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::SetMessage(const TXString& value)
{
	fParams.fMessage = value;
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::AddButtonOk()
{
	fParams.fButtons.push_back( TXResource(kAlertStrings, kOKStr) );
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::AddButtonCancel()
{
	fParams.fButtons.push_back( TXResource(kAlertStrings, kCancelStr) );
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::AddButtonOkCancel()
{
	fParams.fButtons = {
		TXResource(kAlertStrings, kOKStr),
		TXResource(kAlertStrings, kCancelStr)
	};
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::AddButtonYesNo()
{
	fParams.fButtons = {
		TXResource(kAlertStrings, kYesStr),
		TXResource(kAlertStrings, kNoStr)
	};
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::AddButtonYesCancel()
{
	fParams.fButtons = {
		TXResource(kAlertStrings, kYesStr),
		TXResource(kAlertStrings, kCancelStr)
	};
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::SetButtons(const std::vector<TXString>& value)
{
	fParams.fButtons = value;
	return *this;
}

CAlertDialog& CAlertDialog::SetDefaultButtonIndex(Sint8 index)
{
	fParams.fDefaultButtonIndex = index;
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::SetCheckbox(const TXString& customText, EAlertParameterCheckboxBehavior behavior)
{
	fParams.fCheckboxTitle = customText;
	fParams.fCheckboxBehavior = behavior;
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::SetSavedSettings(const TXString& category, const TXString& key)
{
	fParams.fSavedSettingsCategory = category;
	fParams.fSavedSettingsKey = key;
	return *this;
}

// ------------------------------------------------------------------------------------------------
CAlertDialog& CAlertDialog::SetLink(const TXString& linkText, const TXString& linkURL)
{
	fParams.fLinkTitle = linkText;
	fParams.fLinkURL = linkURL;
	return *this;
}
