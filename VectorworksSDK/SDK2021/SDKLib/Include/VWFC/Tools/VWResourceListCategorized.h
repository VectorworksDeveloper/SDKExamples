//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "VWFC/Tools/VWResourceList.h"

namespace VWFC
{
	namespace Tools
	{
		// ----------------------------------------------------------------------------------------------------------------
		typedef std::function<bool(MCObjectHandle h)>						THandleFilterCallback;	// return 'true' to filter-in the object
		typedef std::function<bool(VWResourceList& resList, size_t index)>	TNameFilterCallback;	// return 'true' to filter-in the object
		typedef std::function<bool(IFileIdentifier* fileID)>				TFileFilterCallback;	// return 'true' to filter-in the file
		typedef std::function<void(VWResourceList& resList)>				TPostProcessCallback;

		// ----------------------------------------------------------------------------------------------------------------
		enum class EResourceListCategoryType
		{
			  Document
			, DefaultContent
			, OpenDocuments
			, Favorites
			, File
			, Custom
		};

		// ----------------------------------------------------------------------------------------------------------------
		// This class organizes and manages resources in a default categories organization
		// - Current Document
		//      <sub folder>
		// - Default Content
		// - Files
		// - Custom
		//
		class VWResourceListCategorized
		{
		public:
						VWResourceListCategorized();
						VWResourceListCategorized(const VWResourceListCategorized& src);
			virtual		~VWResourceListCategorized();

			VWResourceListCategorized&	operator=(const VWResourceListCategorized& src);

		public:
			// tool mode bar management
			virtual void	ToolModeGroup_Init(short modeGroup, const TXString& emptyMsg="");
			virtual bool	ToolModeGroup_Show(short modeGroup);

			// dialog image popup management - VWDialog
			virtual void	DialogImagePopup_Init(VWFC::VWUI::VWDialog* dialog, VWFC::VWUI::TControlID imagePopupCtrlID);
			virtual bool	DialogImagePopup_Event(VWFC::VWUI::VWDialog* dialog, VWFC::VWUI::TControlID imagePopupCtrlID, VWFC::VWUI::VWDialogEventArgs& eventArgs);
			virtual void	DialogImagePopup_Update(VWFC::VWUI::VWDialog* dialog, VWFC::VWUI::TControlID imagePopupCtrlID, const TXString& itemName);

			// dialog image popup management - direct event handler from ISDK::RunLayoutDialog
			virtual void	DialogImagePopup_Init(Sint32 dialogID, Sint32 imagePopupCtrlID);
			virtual bool	DialogImagePopup_Event(Sint32 dialogID, Sint32 imagePopupCtrlID, void* eventArgs);
			virtual void	DialogImagePopup_Update(Sint32 dialogID, Sint32 imagePopupCtrlID, const TXString& itemName);

			// direct display on screen management
			virtual bool	DirectScreen_Show(const ViewPt& pt);

			// Shape pane
			virtual bool	ShapePane_Show(VectorWorks::Extension::IShapePaneWidgetAccess* widgetAccessm, SintptrT viewWidget);

		public:
			virtual void						Update();
			// selection management
				// SetInitialSelectedItem: works only the first time (when not forced) to find the item in the document or in the default content
				// then the class itself will store the selected item
				// which will be used in consecutive calls to 'show'
			virtual void						SetSelectedItemText(const TXString& itemName);
			virtual void						SetInitialSelectedItem(const TXString& itemName, bool force=false);
			virtual void						SetSelectedSpecialItem();
			virtual VWResourceList&				GetResourceList();
			virtual Sint32						GetResourceListSelectionIndex();
			virtual EResourceListCategoryType	GetSelectedResourceCategoryType();
			virtual bool						GetSpecialItemSelected();

			// This is the name of the column that lists the categories
			// Call this function if you want to customize it, otherwise it will say 'Categories'
			virtual void	SetCategoryTitle(const TXString& name);

		public:
			// List resources from the current document, open documents, and resource browser favorites
			virtual void		Document_Init(TDType objectType, bool foldersAreCategories = true);
			virtual void		Document_Init(TDType objectType, const TXString& defaultItemName, const TXString& defaultItemImageSpec, bool foldersAreCategories = true);
			virtual void		Document_Set(THandleFilterCallback filter);
			virtual void		Document_Set(TNameFilterCallback filter);
			virtual void		Document_Set(TPostProcessCallback postProcess);

			// List resources from the default content
			virtual void		DefaultContent_Init(TDType objectType, EFolderSpecifier folderIndex, const TXString& subFolderName, bool listAsFiles=true);
			virtual void		DefaultContent_Set(TNameFilterCallback filter);
			virtual void		DefaultContent_Set(TPostProcessCallback postProcess);

			// List resources from open documents other than the current document
			virtual void		OpenDocuments_Init(TDType objectType);
			virtual void		OpenDocuments_Set(THandleFilterCallback filter);
			virtual void		OpenDocuments_Set(TNameFilterCallback filter);
			virtual void		OpenDocuments_Set(TPostProcessCallback postProcess);

			// List resources from the resource browser favorites files
			virtual void		Favorites_Init(TDType objectType);
			virtual void		Favorites_Set(TNameFilterCallback filter);
			virtual void		Favorites_Set(TPostProcessCallback postProcess);

			// List resources for specific files
			virtual void		Files_Init(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath);
			virtual void		Files_Init(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, const TXString& groupName);
			virtual void		Files_Init(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, TFileFilterCallback fileFilter);
			virtual void		Files_Init(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, TFileFilterCallback fileFilter, const TXString& groupName);
			virtual void		Files_Clear();
			virtual void		Files_Add(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath);
			virtual void		Files_Add(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, const TXString& groupName);
			virtual void		Files_Add(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, TFileFilterCallback fileFilter);
			virtual void		Files_Add(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, TFileFilterCallback fileFilter, const TXString& groupName);
			virtual void		Files_Add(TDType objectType, IFileIdentifier* fileID);
			virtual void		Files_Set(TNameFilterCallback filter);
			virtual void		Files_Set(TPostProcessCallback postProcess);

			virtual void		Custom_Add(const TXString& name, TPostProcessCallback postProcess);

			virtual void		RevealInOS();

		protected:
			// ------------------------------------------------
			struct SFileGroup
			{
				TXString			fName;
				IFileIdentifierPtr	fFileID;
			};

			// ------------------------------------------------
			struct SDefinition
			{
				EResourceListCategoryType	fType;
				TXString					fName;
				size_t						fNameIndex;

				TDType						fObjectType;
				bool						fSymFoldersAreCategories;
				TXString					fSymFolderName;
				EFolderSpecifier			fFolderIndex;
				TXString					fSubFolderName;
				std::vector<SFileGroup>		farrFileGroups;
				size_t						fRootLevel;
				bool						fIsSelectable;

				THandleFilterCallback		fFilterHandle;
				TNameFilterCallback			fFilterName;
				TPostProcessCallback		fPostProcess;

						SDefinition();
			};

			typedef std::vector<SDefinition>						TDefinitionsArray;

			// ------------------------------------------------
			struct SDefinitionID
			{
				EResourceListCategoryType	fType;
				size_t						fIndex;

						SDefinitionID();
			};

			// ------------------------------------------------
			struct SCategoryItem
			{
				SDefinitionID	fDefinitionID;
				size_t			fCategoryIndex;

						SCategoryItem();
			};

			typedef std::vector<SCategoryItem>	TCategoryMappingArray;

			// ------------------------------------------------
			struct SResourceItem
			{
				TXString		fSeparatorName;
				VWResourceList	fResourceList;
			};

			// ------------------------------------------------
			struct SSelectionInfo
			{
				Sint32			fResourceGlobalIndex;
				size_t			fResourceIndex;
				Sint32			fResourceListIndex;
				bool			fIsSpecialItem;

						SSelectionInfo();
				void	Clear();
			};

		protected:
			bool		PopupMng_Show(const ViewPt* pt, VectorWorks::Extension::IShapePaneWidgetAccess* widgetAccess, SintptrT viewWidget, short modeGroup);

			void		CreateCategoriesForSymbolFolders(THandleFilterCallback, MCObjectHandle hContainer=NULL, size_t level=0);
			bool		FindDocumentSymbolFolderCategory(const TXString& symName, size_t& categoryIndex);

			TDefinitionsArray&	GetDefinitionArray(EResourceListCategoryType type);
			void				GetCategories(const TDefinitionsArray& arrDefinitions, TXStringArray& outArrCategories, TCategoryMappingArray& outCategoryMapping, size_t& outCategorySelIndex);

			void		ClearResourceList();
			void		BuildResourceList();
			void		BuildResourceList(const SDefinitionID& defID);
			void		BuildResourceList(const SDefinition& def);
			void		BuildResourceList_Symbol(SResourceItem& resourceItem, const SDefinition& def);

			bool		UpdateSelectionInfo(Sint32 globalIndex);

			void		EnsureSelectionInitializedPreFill();
			void		EnsureSelectionInitializedPostFill();

			bool		DialogImagePopup_Event_Selected(Sint32 dialogID, VWFC::VWUI::TControlID imagePopupCtrlID);
			bool		DialogImagePopup_Event_BeforeOpen(Sint32 dialogID, VWFC::VWUI::TControlID imagePopupCtrlID);
			bool		DialogImagePopup_Event_CategoryChange(Sint32 dialogID, VWFC::VWUI::TControlID imagePopupCtrlID);

		private:
			TXString					fCategoryTitle;	// used for the name of the column header in the popup
			TXString					fEmptyMessage;

			TXString					fDocumentDefaultItemName;
			TXString					fDocumentDefaultItemImageSpec;

			TDefinitionsArray			farrDocument;
			TDefinitionsArray			farrDefaultContent;
			TDefinitionsArray			farrOpenDocuments;
			TDefinitionsArray			farrFavorites;
			TDefinitionsArray			farrFiles;
			TDefinitionsArray			farrCustom;

			VWResourceList				fEmptyResourceList;
			std::vector<SResourceItem>	farrResourceItems;

			bool						fSelectionInitialized;
			bool						fSelectionInitSpecialItem;
			TXString					fSelectedItemText;
			SCategoryItem				fSelectedItem;
			SSelectionInfo				fSelectedInfo;

			TXStringArray				fCategoriesArray;
			TCategoryMappingArray		fCategoriesMapping;
			SCategoryItem				fCategoriesTempSelection;
		};
	}
}
