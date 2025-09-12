//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Dialog.h"

namespace VWFC
{
	namespace VWUI
	{
		class CSavedSettingsManager
		{
		public:
						CSavedSettingsManager();
			virtual		~CSavedSettingsManager();
			

			void		OpenSaveSettingsDialog(	std::function<bool(const TXString& name)> functionCheckSetExists,
						 						std::function<bool(const TXString& name)> functionSaveSet);

			void		OpenManageSetsDialog(	const std::vector<TXString>& savedSetsNames,
												std::function<bool(const TXString& oldName, const TXString& newName)>	functionRenameSet,
												std::function<bool(const TXString& name)>           					functionDeleteSet,
												const std::vector<TXString>& secondColumnStrings = std::vector<TXString>(),
												const TXString& secondColumnTitle = "");
			
		private:

			enum class SetAction {
				NoAction = 0,
				Save,
				Rename,
				Delete
			};

			struct Set {
				TXString fOldName;
				SetAction fAction;
				TXString fNewName;
				
				Set() {}
				Set(const TXString& oldName, SetAction action, const TXString& newName) : fOldName(oldName), fAction(action), fNewName(newName) {}
			};
			typedef std::vector<Set> TSetArray;

			//Save Dialog
			class CSaveSettingsDefaultDlg : public VWDialog
			{
			public:
									CSaveSettingsDefaultDlg();
				virtual				~CSaveSettingsDefaultDlg();
				
				void				SetDialogTitle(const TXString& newTitle);
				void				SetInputName(const TXString& defaultSettingsName);
				void				GetResultName(TXString& outName);
				
			protected:
				virtual bool		CreateDialogLayout();
				virtual void		OnInitializeContent();
				virtual	void		OnDDXInitialize();
				virtual void		OnUpdateUI();
				
			protected:
				DEFINE_EVENT_DISPATH_MAP;

			private:
				Set fSet;
				TXString fDialogTitle;

				//DDX
				TXString fDDXname;
			};

			//Manage Dialog
			class CManageSetsDefaultDlg : public VWDialog
			{
			public:
									CManageSetsDefaultDlg();
				virtual				~CManageSetsDefaultDlg();

				void				SetInput1Names(const std::vector<TXString>& savedSetsNames);
				void				SetInput2Info(const std::vector<TXString>& secondColumnStrings);
				void				SetInput2InfoTitle(const TXString& secondColumnTitle);
				void				GetResultNames(TSetArray& outSetArray);

			protected:
				virtual bool		CreateDialogLayout();
				virtual void		OnInitializeContent();
				virtual	void		OnDDXInitialize();
				virtual void		OnUpdateUI();

				void				RefreshListBrowser();

			protected:
				DEFINE_EVENT_DISPATH_MAP;
				void				OnRenameButton(TControlID controlID, VWDialogEventArgs& eventArgs);
				void				OnDeleteButton(TControlID controlID, VWDialogEventArgs& eventArgs);

			private:
				std::vector<TXString> fSetsNames;
				std::vector<TXString> fSecondColumnStrings;
				TXString fSecondColumnTitle;
				TSetArray fSetsModified;
				size_t fItemsRemoved = 0;
			};


		};

	}
}

