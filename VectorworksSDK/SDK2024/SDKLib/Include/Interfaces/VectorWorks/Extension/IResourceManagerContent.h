//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		
		// ----------------------------------------------------------------------------------------------------------------
		struct SResourceProperties {

				TXString	srpName;
				TDType		srpTDType = 0;
				bool		srpIsSketch = false;
				bool		srpIsActiveDoc = false;

				std::vector<TXString>	sprTags;

				typedef std::vector<std::pair<TXString, TXString>>	TResKey2ValueArray;
				typedef std::vector<std::pair<TXString, TResKey2ValueArray>> TResRecordsArray;
				TResRecordsArray sprRecords;

				// nullptr means the property does not apply
				std::unique_ptr <short>		srpSubType = nullptr;
				std::unique_ptr <TXString>	srpPIOName = nullptr;
				std::unique_ptr <bool>		srpSimple = nullptr;		// for Line types and Materials

				enum class ESymbolType {
					st2D = 0,
					st3D,
					stHybrid
				};

				std::unique_ptr <ESymbolType> srpSymbolType = nullptr;
		};

		struct SSearchProperties {
			bool	fOnlyCurrentDoc = false;
			bool	fSearchOnline = true;
			bool	fSkipCurrentDoc = false;
		};

		struct SResourceSelection {
			TXString fResourceName;
			TXString fFilePath;	// full path for local files; relative to the library folder for online files
			ELibrariesID fLibraryID = ELibrariesID::elAnother;	// elAnother means local, for online files it will be libraryID; 
																// this ID may be then used in gSDK->DownloadLibraryFile
			bool	fOnlineFile = false;
		};
	
		// The action buttons are displayed on an additional top button bar of resource selectors (not in main resource manager UI).
		struct SResourceControl {
			using ControlID = int8_t;
			enum DefaultID: ControlID {
				Invalid = -1,
				None,
				Unstyled,
				ByClass,
				RevertToMaterial,
				LastControlID // Custom buttons can be defined with IDs greater than LastControlID. Use LastControlID + 1, LastControlID + 2...
			};
			
			TXString 	fTitle;
			TXString 	fIconSpec;
			ControlID	fID;
			
			// Creates a button with one of the types above. Title and icon spec are set-up automatically.
			SResourceControl(DefaultID id): fID(id) {
			switch (id) {
				case DefaultID::None:
					fTitle = TXResource("Vectorworks/Strings/ResourceManager.vwstrings", "ActionButtonNone");
					fIconSpec = "Vectorworks/Images/Standard Images/unstyled.svg";
					break;
				case DefaultID::Unstyled:
					fTitle = TXResource("Vectorworks/Strings/ResourceManager.vwstrings", "ActionButtonUnstyled");
					fIconSpec = "Vectorworks/Images/Standard Images/unstyled.svg";
					break;
				case DefaultID::ByClass:
					fTitle = TXResource("Vectorworks/Strings/ResourceManager.vwstrings", "ActionButtonByClass");
					fIconSpec = "Vectorworks/Images/Standard Images/class-style-texture.svg";
					break;
				case DefaultID::RevertToMaterial:
					fTitle = TXResource("Vectorworks/Strings/ResourceManager.vwstrings", "ActionButtonRevertToMaterial");
					fIconSpec = "Vectorworks/Images/Standard Images/material-texture.svg";
					break;
				default:
					DSTOP((kAAntonini, "Invalid ID provided to the SResourceControl initializer."));
					break;
				}
			};

			
			SResourceControl(): fID(DefaultID::Invalid) {};
			SResourceControl(ControlID id, TXString title, TXString iconSpec): fID(id), fTitle(title), fIconSpec(iconSpec) {}
		};

		typedef std::function<bool(MCObjectHandle h)>									THandleFilterCallback2;				// return 'true' to filter-in the object
		typedef std::function<bool(const SResourceProperties& properties)>				TPropertiesFilterCallback;			// return 'true' to filter-in the object by properties: name, type, complex or simple (applies to Line types)
		typedef std::function<bool(MCObjectHandle h, void* env)>						THandleScriptFilterCallback;		// return 'true' to filter-in the object( for script )
		typedef std::function<bool(const SResourceProperties& properties, void* env)>	TPropertiesScriptFilterCallback;	// return 'true' to filter-in the object by properties: name or type ( for script )
		typedef std::vector<EFolderSpecifier>											TFolderSpecifierArray;
		typedef std::vector<TXString>													TFolderNameArray;
		typedef std::vector<SResourceControl>											TResourceControlArray;

		// ----------------------------------------------------------------------------------------------------------------
		// {FB62237A-C7F5-4B41-9E01-E3860D997657}
		static const VWIID IID_ResourceManagerContent = { 0xfb62237a, 0xc7f5, 0x4b41, { 0x9e, 0x1, 0xe3, 0x86, 0xd, 0x99, 0x76, 0x57 } };

		// ----------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IResourceManagerContent : public IVWUnknown
		{
		public:
			virtual void		InitByTDType(TDType objectType) = 0;
			virtual void		InitByInternalID(TInternalID subType) = 0;
			virtual void		InitByUnivName(const TXString& pioUnivName) = 0;

			virtual void		AddContent(EFolderSpecifier folderSpec) = 0;
			virtual void		AddContent(EFolderSpecifier baseFolderSpec, const TXString& folderName) = 0;

			// sets the filter for the active document
			virtual void		SetFilter(THandleFilterCallback2 filter) = 0;

			virtual TXString	GetEmptyMessage() = 0;
			virtual void		SetEmptyMessage(const TXString& msg) = 0;

			virtual TXString	GetSelectedItemText() = 0;
			virtual bool		IsSelectedItemValid() = 0;
			virtual void		SetSelectedItemText(const TXString& itemName) = 0;
			virtual bool		SetSelectedItemText(const TXString& itemName, const TXString& filePath) = 0;

			// saves the current selection in the Resource popup/manager and returns the ID of the selection
			virtual int			SaveCurrentSelection() = 0;
			// restores the last saved selection
			virtual void		RestorePreviousSelection() = 0;
			// restores the selection with given ID
			virtual void		RestoreSelectionWithID(int ID) = 0;

			virtual MCObjectHandle	ImportSelectedResourceToCurrentFile(VectorWorks::EImportResourceConflictResult resolveConflicts, bool preserveFolders = false) = 0;
			virtual bool			GetSelectedResourceIsDocument() = 0;	

		// Vectorworks 2017 SP3
		public:
			// use SetSelectedItemText(const TXString& itemName) if your major goal is to select in the popup a resource with itemName regardless of the file; 
			// in this case if the itemName does not match the last-selected resource name, the selected resource is reset, which results in the first available 
			// item of the correct type being selected. It will be searched in the current file and then in the libraries;
			// use SetSelectedItemTextPreserveFile(const TXString& itemName) if your major goal is to select in the popup the last-selected file;
			// in this case the saved resource name will be replaced with itemName,
			// but the last-selected file remains selected, even if the selected resource is not in that file
			virtual void		SetSelectedItemTextPreserveFile(const TXString& itemName) = 0;

		// Vectorworks 2018
		public:
			// sets the filter for the non-active open documents
			virtual void		SetFilterNonActiveOpenDoc(THandleFilterCallback2 filter) = 0;

			// sets the filter for the resource properties: name, type, complex or simple (applies to Line types)
			virtual void		SetResourcePropertiesFilter(TPropertiesFilterCallback filter) = 0;

			// searches in the content for the first available resource and returns its name; if filters are set they will be applied;
			// searches first in the active doc, then in libraries (VW libs, Workgroup, User, Subscription);
			// this method DOES NOT change the selection;
			// expected use - check if something of the type with filtering is available
			virtual bool		GetFirstAvailableResource(TXString& outResourceName, const SSearchProperties& properties) = 0;

			// subscribeID is needed if the content should contain the guest resources
			virtual void		SetSubscribeID(short subscribeID) = 0;	

		// Vectorworks 2019
		public:
			// searches in the content for the first available resource and returns its name; if filters are set they will be applied;
			// searches first in the active doc (if properties.fSkipCurrentDoc not set), then in libraries (VW libs, Workgroup, User, Subscription);
			// this method DOES change the selection;
			// expected use - change the popup data selection if something of the type with filtering is available
			// @param - input/output - resourceName - if not empty the method will be searching for the first available resource with this name; 
			//										  if empty - resource with any name  will be picked, found name will be assigned to resourceName ;
			// @param - input - properties - search parameters;
			// @return - result of the operation (true - success)
			virtual bool SelectFirstAvailableResource(TXString& resourceName, const SSearchProperties& properties) = 0;

			// by default when we open a popup we select the previously used location;
			// if false - the current selection will be used, if it is valid; otherwise - default behavior;
			// @param - input - value 
			// @return - no
			virtual void SetUseSavedSelectionInPopup(bool value) = 0;

		// Vectorworks 2020
		public:
			// sets the filter for the active document( for script )
			virtual void SetFilter(THandleScriptFilterCallback filter, void* env) = 0;

			// sets the filter for the non-active open documents( for script )
			virtual void SetFilterNonActiveOpenDoc(THandleScriptFilterCallback filter, void* env) = 0;

			// sets the filter for the resource properties: name or type( for script )
			virtual void SetResourcePropertiesFilter(TPropertiesScriptFilterCallback filter, void* env) = 0;

			// Vectorworks 2022
		public:
			// if value == true only content from the current document will appear in popups
			virtual void SetOnlyCurrentDocument(bool value) = 0;
			virtual bool GetOnlyCurrentDocument() const = 0;

			// adds content folders for "regular" symbols. Examples of use: Symbol insertion tool, Symbol Replace dialog
			virtual void AddSymbolDefaultContent() = 0;

			// returns true if we have a valid selection
			virtual bool	GetCurrentSelection(SResourceSelection& outSelection) const = 0;

			// Vectorworks 2024
		public:
			virtual void AddResourceControl(const SResourceControl& control) = 0;
			virtual void RemoveAllResourceControls() = 0;
			virtual SResourceControl::ControlID GetSelectedResourceControlID() const = 0;
			virtual void SetSelectedResourceByClass(bool byClass) = 0;
			virtual bool GetSelectedResourceByClass() const = 0;
			virtual void SetSelectedResourceControl(const SResourceControl& button) = 0;
		};

		typedef VCOMPtr<IResourceManagerContent>	IResourceManagerContentPtr;
	}
}
