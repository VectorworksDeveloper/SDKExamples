//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/SavedSettingsManager.h"
using namespace VWFC::VWUI;

#define kDefaultSettingsName		TXResource("Vectorworks/Strings/DefaultDialog_SavedSettingsManager.vwstrings",	"defaultSettingsName"	)
#define kQuestionSetAlreadyExists	TXResource("Vectorworks/Strings/DefaultDialog_SavedSettingsManager.vwstrings",	"setAlreadyExists"		)
#define kQuestionReplaceSet			TXResource("Vectorworks/Strings/DefaultDialog_SavedSettingsManager.vwstrings",	"questionReplaceSet"	)
#define kAlertErrorStringEmpty		TXResource("Vectorworks/Strings/DefaultDialog_SavedSettingsManager.vwstrings",	"errorStringEmpty"		)
#define kAlertErrorSpecialCharacter	TXResource("Vectorworks/Strings/DefaultDialog_SavedSettingsManager.vwstrings",	"errorSpecialCharacter"	)
#define kAlertErrorSavingSet		TXResource("Vectorworks/Strings/DefaultDialog_SavedSettingsManager.vwstrings",	"errorSavingSet"		)
#define kAlertErrorDeletingSet		TXResource("Vectorworks/Strings/DefaultDialog_SavedSettingsManager.vwstrings",	"errorDeletingSet"		)
#define kAlertErrorRenamingSet		TXResource("Vectorworks/Strings/DefaultDialog_SavedSettingsManager.vwstrings",	"errorRenamingSet"		)
#define kName						TXResource("Vectorworks/Strings/DefaultDialog_ManageSets.vwstrings",			"name"					)
#define kName2						TXResource("Vectorworks/Strings/DefaultDialog_ManageSets.vwstrings",			"name2"					)
#define kTitleRename				TXResource("Vectorworks/Strings/DefaultDialog_SaveSettings.vwstrings",			"dialog_title_Rename"	)
#define kAlertNoItemSelected		TXResource("Vectorworks/Strings/DefaultDialog_ManageSets.vwstrings",			"noItemSelected"		)
#define kQuestionAboutDeleting		TXResource("Vectorworks/Strings/DefaultDialog_ManageSets.vwstrings",			"questionAboutDeleting"	)
#define kAdviceAboutChange			TXResource("Vectorworks/Strings/DefaultDialog_ManageSets.vwstrings",			"adviceAboutChange"		)


inline bool IncludesSpecialSymbol(const TXString & name)
{
	if (name.FindOneOf("\\/:*\"<>|") != -1)
		return true;
	return false;
}


CSavedSettingsManager::CSavedSettingsManager()
{
}


CSavedSettingsManager::~CSavedSettingsManager()
{
}

void CSavedSettingsManager::OpenSaveSettingsDialog(	std::function<bool(const TXString& name)> functionCheckSetExists,
													std::function<bool(const TXString& name)> functionSaveSet)
{

	CSaveSettingsDefaultDlg	saveDlg;

	Uint16 n = 1;
	TXString defaultSettingsName;
	do {
		defaultSettingsName = kDefaultSettingsName;
		defaultSettingsName = defaultSettingsName.Replace("#N#", n < 10 ? " " + TXString::ToStringInt(n) : TXString::ToStringInt(n));
		n++;
	} while (functionCheckSetExists(defaultSettingsName));

	EDialogButton result;
	bool done = false;
	do{
		saveDlg.SetInputName(defaultSettingsName);
		result = saveDlg.RunDialogLayout("SaveSettings");
		
		if (result == EDialogButton::kDialogButton_Ok) {
			TXString newName;
			saveDlg.GetResultName(newName);
			if (newName.IsEmpty()) {
				gSDK->AlertInform(kAlertErrorStringEmpty);
			}
			else if (IncludesSpecialSymbol(newName)) {
				gSDK->AlertInform(kAlertErrorSpecialCharacter);
			}
			else{

				bool save = false;
				if (!functionCheckSetExists(newName)) { //if it doesn't exist
					save = true;
				}
				else { //if it exists
					TXString question = kQuestionSetAlreadyExists;
					question += "\n" + kQuestionReplaceSet;
					if (gSDK->AlertQuestion(question) == EDialogButton::kDialogButton_Ok) {
						save = true;
					}
				}
				if (save) {
					if (functionSaveSet(newName))
						done = true;
					else
						gSDK->AlertInform(kAlertErrorSavingSet);
				}

			}
		}
		else
			done = true;
	} while (!done);

}

void CSavedSettingsManager::OpenManageSetsDialog(	const std::vector<TXString>& savedSetsNames,
													std::function<bool(const TXString& oldName, const TXString& newName)>	functionRenameSet,
													std::function<bool(const TXString& name)>           					functionDeleteSet,
													const std::vector<TXString>& secondColumnStrings,
													const TXString& secondColumnTitle)
{
	CManageSetsDefaultDlg	manageDlg;
	manageDlg.SetInput1Names(savedSetsNames);
	manageDlg.SetInput2Info(secondColumnStrings);
	manageDlg.SetInput2InfoTitle(secondColumnTitle);
	if (manageDlg.RunDialogLayout("SaveSettings") == EDialogButton::kDialogButton_Ok)
	{
		TSetArray setsModified;
		manageDlg.GetResultNames(setsModified);

		auto it = setsModified.begin();
		while (it != setsModified.end()) {
			if (it->fAction == SetAction::Delete) {
				if (!functionDeleteSet(it->fOldName))
					gSDK->AlertInform(kAlertErrorDeletingSet);
			}
			else if (it->fAction == SetAction::Rename) {
				if (!functionRenameSet(it->fOldName, it->fNewName))
					gSDK->AlertInform(kAlertErrorRenamingSet);
			}
			++it;
		}

	}

}





//*****Methods for CSaveSettingsDefaultDlg*****
// dialog control IDs
#define		kOK                   1
#define		kCancel               2
#define		kStaticText           4
#define		kEditText             5


EVENT_DISPATCH_MAP_BEGIN(CSavedSettingsManager::CSaveSettingsDefaultDlg);
EVENT_DISPATCH_MAP_END;


CSavedSettingsManager::CSaveSettingsDefaultDlg::CSaveSettingsDefaultDlg()
{
	this->SetSavedSettingsTag("Vectorworks", "SaveSettingsDefaultDialog");
}

CSavedSettingsManager::CSaveSettingsDefaultDlg::~CSaveSettingsDefaultDlg()
{
}

void CSavedSettingsManager::CSaveSettingsDefaultDlg::SetDialogTitle(const TXString& newDialogTitle)
{
	fDialogTitle = newDialogTitle;
}

void CSavedSettingsManager::CSaveSettingsDefaultDlg::SetInputName(const TXString& defaultSettingsName)
{
	fDDXname = defaultSettingsName;
	fSet.fOldName = defaultSettingsName;
}

void CSavedSettingsManager::CSaveSettingsDefaultDlg::GetResultName(TXString& outName)
{
	outName = fDDXname;
	outName.Trim();
}

bool CSavedSettingsManager::CSaveSettingsDefaultDlg::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR("Vectorworks/DialogLayout/DefaultDialog_SaveSettings.vs");
}

void CSavedSettingsManager::CSaveSettingsDefaultDlg::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	if(!fDialogTitle.IsEmpty())
		VWDialog::SetDialogTitle(fDialogTitle);

	auto ptrEditText = this->GetEditTextCtrlByID(kEditText);
	ptrEditText->SetControlText(fSet.fOldName);
}

void CSavedSettingsManager::CSaveSettingsDefaultDlg::OnDDXInitialize()
{
	this->AddDDX_EditText(kEditText, &fDDXname);
}

void CSavedSettingsManager::CSaveSettingsDefaultDlg::OnUpdateUI()
{
	VWDialog::OnUpdateUI();
}


//*****Methods for CManageSetsDefaultDlg*****
// dialog control IDs
//#define		kOK                   1		//already defined
//#define		kCancel               2		//already defined
#define		kListBrowser		 4
#define		kRenameButton		 5
#define		kDeleteButton		 6


EVENT_DISPATCH_MAP_BEGIN(CSavedSettingsManager::CManageSetsDefaultDlg);
ADD_DISPATCH_EVENT(kRenameButton, OnRenameButton);
ADD_DISPATCH_EVENT(kDeleteButton, OnDeleteButton);
EVENT_DISPATCH_MAP_END;


CSavedSettingsManager::CManageSetsDefaultDlg::CManageSetsDefaultDlg()
{
	this->SetSavedSettingsTag("Vectorworks", "ManageSetsDefaultDialog");
}

CSavedSettingsManager::CManageSetsDefaultDlg::~CManageSetsDefaultDlg()
{
}

void CSavedSettingsManager::CManageSetsDefaultDlg::SetInput1Names(const std::vector<TXString>& savedSetsNames)
{
	fSetsNames = savedSetsNames;
}

void CSavedSettingsManager::CManageSetsDefaultDlg::SetInput2Info(const std::vector<TXString>& secondColumnStrings)
{
	fSecondColumnStrings = secondColumnStrings;
}

void CSavedSettingsManager::CManageSetsDefaultDlg::SetInput2InfoTitle(const TXString & secondColumnTitle)
{
	fSecondColumnTitle = secondColumnTitle;
}

void CSavedSettingsManager::CManageSetsDefaultDlg::GetResultNames(TSetArray & outSetArray)
{
	outSetArray = fSetsModified;
}

bool CSavedSettingsManager::CManageSetsDefaultDlg::CreateDialogLayout()
{
	return this->CreateDialogLayoutFromVWR("Vectorworks/DialogLayout/DefaultDialog_ManageSets.vs");
}

void CSavedSettingsManager::CManageSetsDefaultDlg::OnInitializeContent()
{
	VWDialog::OnInitializeContent();

	auto ptrListBrowser = this->GetListBrowserCtrlByID(kListBrowser);
	//ptrListBrowser->EnableSingleLineSelection(true); //no need since multiple selection is handled
	ptrListBrowser->AddColumn(kName, 200);
	if (!fSecondColumnStrings.empty()) {
		if (!fSecondColumnTitle.IsEmpty())
			ptrListBrowser->AddColumn(fSecondColumnTitle, 200);
		else
			ptrListBrowser->AddColumn(kName2, 200);
	}
	//ptrListBrowser->EnableSorting(true);
	//ptrListBrowser->GetColumn(0).SetColumnSortState(kDescendingSortState);
	for (size_t i = 0; i < fSetsNames.size(); i++) {
		ptrListBrowser->AddRow(fSetsNames[i]);
	}

	if (!fSecondColumnStrings.empty()) {
		for (size_t i = 0; i < fSecondColumnStrings.size() && i < fSetsNames.size(); i++) {
			ptrListBrowser->GetItem(i, 1).SetItemText(fSecondColumnStrings[i]);
		}
	}
}

void CSavedSettingsManager::CManageSetsDefaultDlg::OnDDXInitialize()
{
}

void CSavedSettingsManager::CManageSetsDefaultDlg::OnUpdateUI()
{
	VWDialog::OnUpdateUI();

	auto ptrListBrowser = this->GetListBrowserCtrlByID(kListBrowser);
	
	bool enable = (ptrListBrowser->GetSelectedItemsCount()>0);
	this->EnableControl(kRenameButton, enable);
	this->EnableControl(kDeleteButton, enable);
}

void CSavedSettingsManager::CManageSetsDefaultDlg::RefreshListBrowser()
{
	auto ptrListBrowser = this->GetListBrowserCtrlByID(kListBrowser);
	ptrListBrowser->DeleteAllRows();

	for (const TXString& setName : fSetsNames) {
		ptrListBrowser->AddRow(setName);
	}

	if (!fSecondColumnStrings.empty()) {
		for (size_t i = 0; i < fSecondColumnStrings.size() && i < fSetsNames.size(); i++) {
			ptrListBrowser->GetItem(i, 1).SetItemText(fSecondColumnStrings[i]);
		}
	}
}

void CSavedSettingsManager::CManageSetsDefaultDlg::OnRenameButton(TControlID controlID, VWDialogEventArgs & eventArgs)
{
	auto ptrListBrowser = this->GetListBrowserCtrlByID(kListBrowser);

	TSizeTArray rowsSelected; 
	if (ptrListBrowser->GetSelectedItemIndices(rowsSelected)) {
		for (size_t i = 0; i < rowsSelected.size(); i++) {
			size_t index = rowsSelected[i];
			TXString currentName = ptrListBrowser->GetItem(index, 0).GetItemText();
			
			CSaveSettingsDefaultDlg	saveDlg;
			saveDlg.SetDialogTitle(kTitleRename);

			EDialogButton result;
			bool done = false;
			do{
				saveDlg.SetInputName(currentName);
				result = saveDlg.RunDialogLayout("SaveSettings");
				if (result == EDialogButton::kDialogButton_Ok) {
					TXString newName;
					saveDlg.GetResultName(newName);
					if (newName.IsEmpty()) {
						gSDK->AlertInform(kAlertErrorStringEmpty);
					}
					else if (IncludesSpecialSymbol(newName)) {
						gSDK->AlertInform(kAlertErrorSpecialCharacter);
					}
					else {

						if (currentName == newName) //user gave it the same name
							break;

						//check if a set with that name already exists
						auto itnew = std::find(fSetsNames.begin(), fSetsNames.end(), newName);
						auto itcurr = std::find(fSetsNames.begin(), fSetsNames.end(), currentName);
						if (itnew != fSetsNames.end()) { //a set already exists with that name
							TXString question = kQuestionSetAlreadyExists;
							question += "\n" + kQuestionReplaceSet;
							if (gSDK->AlertQuestion(question) == EDialogButton::kDialogButton_Ok) { //rename and delete the other
								//delete the other set with the same name
								fSetsModified.push_back(Set(*itnew, SetAction::Delete, ""));
								//rename current set
								fSetsModified.push_back(Set(currentName, SetAction::Rename, newName));
								//change name in list
								*itcurr = newName;
								//remove the other set from the list(s)
								size_t index1 = size_t(itnew - fSetsNames.begin());
								if (index1 < fSecondColumnStrings.size()) //usually there isn't a second column
									fSecondColumnStrings.erase(fSecondColumnStrings.begin() + index1);
								fSetsNames.erase(itnew);
								done = true;
							}
							break;
						}
						else { //a set doesn't exist with that name
							fSetsModified.push_back(Set(*itcurr, SetAction::Rename, newName));
							*itcurr = newName;
							done = true;
						}

					}


				}
				else //user clicked Cancel when renaming
					done = true;

			} while (!done);
		}
	}
	else
		gSDK->AlertInform(kAlertNoItemSelected);

	
	RefreshListBrowser();
}

void CSavedSettingsManager::CManageSetsDefaultDlg::OnDeleteButton(TControlID controlID, VWDialogEventArgs & eventArgs)
{
	auto ptrListBrowser = this->GetListBrowserCtrlByID(kListBrowser);

	TXString	advice = kAdviceAboutChange;

	TSizeTArray rowsSelected;
	if (ptrListBrowser->GetSelectedItemIndices(rowsSelected)) {
		for (size_t i = 0; i < rowsSelected.size(); i++) {
			size_t index = rowsSelected[i];
			TXString currentName = ptrListBrowser->GetItem(index, 0).GetItemText();

			TXString	question = kQuestionAboutDeleting;
			question.Replace("#setname#", currentName);
			if (VWDialog::AlertQuestion(question, advice) == EDialogButton::kDialogButton_Ok)
			{
				//delete the other set with the same name
				fSetsModified.push_back(Set(currentName, SetAction::Delete, ""));
				auto itcurr = std::find(fSetsNames.begin(), fSetsNames.end(), currentName);
				if (itcurr != fSetsNames.end()) {//safety check just in case (although it should always find it)
					size_t index1 = size_t(itcurr - fSetsNames.begin());
					if (index1 < fSecondColumnStrings.size()) //usually there isn't a second column
						fSecondColumnStrings.erase(fSecondColumnStrings.begin() + index1);
					fSetsNames.erase(itcurr);
				}
			}

		}
	}
	else
		gSDK->AlertInform(kAlertNoItemSelected);


	RefreshListBrowser();
}

