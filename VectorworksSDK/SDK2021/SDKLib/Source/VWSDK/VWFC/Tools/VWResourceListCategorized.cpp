//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VWFC::PluginSupport;
using namespace VWFC::VWUI;
using namespace VectorWorks::Filing;

// ----------------------------------------------------------------------------------------------------------------
VWResourceListCategorized::SDefinition::SDefinition()
{
	fType					= EResourceListCategoryType::Document;
	fNameIndex				= size_t(-1);
	fSymFoldersAreCategories= true;
	fFolderIndex			= kRootFolderSpecifier;
	fRootLevel				= 0;
	fIsSelectable			= true;
}

// ----------------------------------------------------------------------------------------------------------------
VWResourceListCategorized::SDefinitionID::SDefinitionID()
{
	fType	= EResourceListCategoryType::Document;
	fIndex	= 0;
}

// ----------------------------------------------------------------------------------------------------------------
VWResourceListCategorized::SCategoryItem::SCategoryItem()
{
	fCategoryIndex	= size_t(-1);
}

// ----------------------------------------------------------------------------------------------------------------
VWResourceListCategorized::SSelectionInfo::SSelectionInfo()
{
	this->Clear();
}

void VWResourceListCategorized::SSelectionInfo::Clear()
{
	fResourceGlobalIndex	= -1;
	fResourceIndex			= size_t(-1);
	fResourceListIndex		= -1;
	fIsSpecialItem			= false;
}

// ----------------------------------------------------------------------------------------------------------------
VWResourceListCategorized::VWResourceListCategorized()
{
	fSelectionInitialized		= false;
	fSelectionInitSpecialItem	= false;
	fSelectedItem.fDefinitionID.fType	= EResourceListCategoryType::Document;
	fSelectedItem.fDefinitionID.fIndex	= 0;
	fSelectedItem.fCategoryIndex		= 0;
}

VWResourceListCategorized::VWResourceListCategorized(const VWResourceListCategorized& src)
{
	this->operator= ( src );
}

VWResourceListCategorized::~VWResourceListCategorized()
{
	this->ClearResourceList();
}

VWResourceListCategorized& VWResourceListCategorized::operator=(const VWResourceListCategorized& src)
{
	fCategoryTitle	= src.fCategoryTitle;
	fEmptyMessage	= src.fEmptyMessage;

	fDocumentDefaultItemName		= src.fDocumentDefaultItemName;;
	fDocumentDefaultItemImageSpec	= src.fDocumentDefaultItemImageSpec;;

	farrDocument		= src.farrDocument;
	farrDefaultContent	= src.farrDefaultContent;
	farrFiles			= src.farrFiles;
	farrCustom			= src.farrCustom;

	fEmptyResourceList	= src.fEmptyResourceList;
	farrResourceItems	= src.farrResourceItems;

	fSelectionInitialized		= src.fSelectionInitialized;
	fSelectionInitSpecialItem	= src.fSelectionInitSpecialItem;
	fSelectedItemText			= src.fSelectedItemText;
	fSelectedItem				= src.fSelectedItem;
	fSelectedInfo				= src.fSelectedInfo;

	fCategoriesArray		= src.fCategoriesArray;
	fCategoriesMapping		= src.fCategoriesMapping;
	fCategoriesTempSelection= src.fCategoriesTempSelection;

	return *this;
}

void VWResourceListCategorized::Update()
{
	this->BuildResourceList();
	this->UpdateSelectionInfo( -1 );
}

void VWResourceListCategorized::SetSelectedItemText(const TXString& itemName)
{
	fSelectedItemText		= itemName;
}

void VWResourceListCategorized::SetInitialSelectedItem(const TXString& itemName, bool force)
{
	if ( ! fSelectionInitialized || force )
	{
		this->SetSelectedItemText( itemName );
		fSelectionInitialized	= false;
	}
}

void VWResourceListCategorized::SetSelectedSpecialItem()
{
	fSelectionInitSpecialItem	= true;
	fSelectionInitialized		= true;

	fSelectedItemText 	= fEmptyMessage;

	fSelectedInfo.Clear();
}

VWResourceList& VWResourceListCategorized::GetResourceList()
{
	if ( fSelectedInfo.fResourceIndex < farrResourceItems.size() )
	{
		SResourceItem& resItem = farrResourceItems[ fSelectedInfo.fResourceIndex ];
		return resItem.fResourceList;
	}
	else
	{
		return fEmptyResourceList;
	}
}

Sint32 VWResourceListCategorized::GetResourceListSelectionIndex()
{
	return fSelectedInfo.fResourceIndex != size_t(-1) ? fSelectedInfo.fResourceListIndex : -1;
}

EResourceListCategoryType VWResourceListCategorized::GetSelectedResourceCategoryType()
{
	return fSelectedItem.fDefinitionID.fType;
}

bool VWResourceListCategorized::GetSpecialItemSelected()
{
	return fSelectedInfo.fIsSpecialItem;
}

void VWResourceListCategorized::SetCategoryTitle(const TXString& name)
{
	fCategoryTitle = name;
}

// ------------------------------------------------------------------------------------------------------------
// List resources from the current document
void VWResourceListCategorized::Document_Init(TDType objectType, bool foldersAreCategories)
{
	TXString strEmpty;
	this->Document_Init( objectType, strEmpty, strEmpty, foldersAreCategories );
}

void VWResourceListCategorized::Document_Init(TDType objectType, const TXString& defaultItemName, const TXString& defaultItemImageSpec, bool foldersAreCategories)
{
	fDocumentDefaultItemName		= defaultItemName;
	fDocumentDefaultItemImageSpec	= defaultItemImageSpec;

	farrDocument.clear();

	SDefinition	def;
	def.fType					= EResourceListCategoryType::Document;
	def.fName					= TXResource("Vectorworks/Strings/4000 *", "ResourcePopupCategoryItemCurrentDoc");
	def.fObjectType				= objectType;
	def.fSymFoldersAreCategories= foldersAreCategories;

	farrDocument.push_back( def );
}

void VWResourceListCategorized::Document_Set(THandleFilterCallback filter)
{
	for(auto& it : farrDocument )
	{
		it.fFilterHandle = filter;
	}
}

void VWResourceListCategorized::Document_Set(TNameFilterCallback filter)
{
	for(auto& it : farrDocument )
	{
		it.fFilterName = filter;
	}
}

void VWResourceListCategorized::Document_Set(TPostProcessCallback postProcess)
{
	for(auto& it : farrDocument )
	{
		it.fPostProcess = postProcess;
	}
}

// ------------------------------------------------------------------------------------------------------------
// List resources from the default content

namespace VWFC
{
	namespace Tools
	{
		template<class TDef, class TFileGroup> class CContentFileSearchContext : public IFolderContentListener
		{
		public:
			CContentFileSearchContext(TDType objectType, EFolderSpecifier folderIndex, const TXString& subFolderName, EResourceListCategoryType categoryType, const TDef* parentDef = nullptr)
				: fObjectType( objectType )
				, fFolderIndex( folderIndex )
				, fSubFolderName( subFolderName )
				, fCategoryType( categoryType )
				, fBaseDefValid( parentDef != nullptr )
				, fBaseDef( parentDef ? *parentDef : TDef() )
				, fFileFilter( nullptr )
			{
				IFolderIdentifierPtr	rootFolder( IID_FolderIdentifier );
				rootFolder->Set( fFolderIndex, false, fSubFolderName );
				rootFolder->GetFullPath( fRootFolderApp );
				rootFolder->Set( fFolderIndex, true, fSubFolderName );
				rootFolder->GetFullPath( fRootFolderUsr );

				IApplicationFoldersPtr	appFolders( IID_ApplicationFolders );
				appFolders->GetStandardFolderName( folderIndex, fStandardFolderName );
			}

			virtual	~CContentFileSearchContext()
			{
				for(TContentFileSearch* p : farrChildren)
				{
					delete p;
				}

				farrChildren.clear();
			}

			void	SetFileFilter(TFileFilterCallback filter)
			{
				fFileFilter = filter;
			}

			bool 	HasDefs() const
			{
				return farrChildren.size() > 0;
			}

			void	GetDefs(std::vector<TDef>& outArray)
			{
				if ( fBaseDefValid )
				{
					TDef	newDef = fBaseDef;

					// trim the # suffix that controls resource combine into single category
					if ( newDef.fName.GetLength() > 0 && newDef.fName.Right(1) == "$" )
					{
						newDef.fName = newDef.fName.Left( newDef.fName.GetLength() - 1 );
					}

					// trim numbering in front of the name, that might be used to control the sorting
					if ( newDef.fName.GetLength() > 3 && newDef.fName.GetAt(2) == '.' && newDef.fName.GetAt(3) == ' ' )
					{
						newDef.fName = newDef.fName.Mid( 3 );
					}
					else if ( newDef.fName.GetLength() > 2 && newDef.fName.GetAt(1) == '.' && newDef.fName.GetAt(2) == ' ' )
					{
						newDef.fName = newDef.fName.Mid( 2 );
					}

					newDef.fName.Trim();

					outArray.push_back( newDef );
				}

				std::sort( farrChildren.begin(), farrChildren.end(),
					[](const TContentFileSearch* a, const TContentFileSearch* b)
					{
						bool result = false;
						if ( a->fBaseDefValid && b->fBaseDefValid )
							result = a->fBaseDef.fName < b->fBaseDef.fName;
						else
							result = a->fSubFolderName < b->fSubFolderName;
						return result;
					});

				for(TContentFileSearch* p : farrChildren)
				{
					p->GetDefs( outArray );
				}
			}

		public:
			virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFolderContent(IFolderIdentifier* folderID)
			{
				TXString	path;
				folderID->GetFullPath( path );

				TDef		def;
				folderID->GetName( def.fName );
				if ( def.fName.GetLength() > 0 && def.fName.GetAt(0) != '.' &&def.fName.GetAt(0) != '_' )
				{
					def.fType			= fCategoryType;
					def.fObjectType		= fObjectType;
					def.fIsSelectable	= false;
					def.fRootLevel		= 1 + this->ExtractPathNestingLevel( path );

					TContentFileSearch*	foundContext = nullptr;
					for(TContentFileSearch* context : farrChildren)
					{
						if (	context->fBaseDefValid
							&&	context->fBaseDef.fName == def.fName
							&&	context->fBaseDef.fRootLevel == def.fRootLevel
							)
						{
							foundContext = context;
							break;
						}
					}

					if ( foundContext )
					{
						folderID->EnumerateContents( foundContext, false );
					}
					else
					{
						TContentFileSearch*	subContext	= SDK_NEW TContentFileSearch( fObjectType, fFolderIndex, fSubFolderName, fCategoryType, & def );
						folderID->EnumerateContents( subContext, false );

						if (	subContext->farrChildren.size() > 0
							||	(subContext->fBaseDefValid && subContext->fBaseDef.farrFileGroups.size() > 0) )
						{
							farrChildren.push_back( subContext );
						}
						else
						{
							delete subContext;
							subContext = nullptr;
						}
					}
				}

				return eFolderContentListenerResult_Continue;
			}

			virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFileContent(IFileIdentifier* fileID)
			{
				if ( fFileFilter == nullptr || fFileFilter( fileID ) )
				{
					VWResourceList		resList;
					resList.BuildList( fObjectType, fileID );
					if ( resList.GetNumItems() > 0 )
					{
						TXString	path;
						fileID->GetFileFullPath( path );


						TXString	strName;
						TDef		newDef;
						fileID->GetFileName( strName );
						newDef.fName = strName;

						if ( newDef.fName.GetLength() > 0 && newDef.fName.GetAt(0) != '.' )
						{
							TFileGroup	fileGroup;
							fileGroup.fFileID	= fileID;

							if ( fBaseDefValid && fBaseDef.fName.GetLength() > 0 && fBaseDef.fName.Right(1) == "$" )
							{
								fileID->GetFileNameWithoutExtension( fileGroup.fName );

								// trim numbering in front of the name, that might be used to control the sorting
								if ( fileGroup.fName.GetLength() > 3 && fileGroup.fName.GetAt(2) == '.' && fileGroup.fName.GetAt(3) == ' ' )
								{
									fileGroup.fName = fileGroup.fName.Mid( 3 );
								}
								else if ( fileGroup.fName.GetLength() > 2 && fileGroup.fName.GetAt(1) == '.' && fileGroup.fName.GetAt(2) == ' ' )
								{
									fileGroup.fName = fileGroup.fName.Mid( 2 );
								}

								fileGroup.fName.Trim();

								fBaseDef.fIsSelectable = true;

								fBaseDef.farrFileGroups.push_back( fileGroup );
							}
							else
							{
								newDef.fType			= fCategoryType;
								newDef.fObjectType		= fObjectType;
								newDef.farrFileGroups.push_back( fileGroup );
								newDef.fRootLevel		= 1 + this->ExtractPathNestingLevel( path );

								TContentFileSearch*	subContext	= SDK_NEW TContentFileSearch( fObjectType, fFolderIndex, fSubFolderName, fCategoryType, & newDef );
								farrChildren.push_back( subContext );
							}
						}
					}
				}

				return eFolderContentListenerResult_Continue;
			}

		private:
			size_t ExtractPathNestingLevel(const TXString& filePath)
			{
				TXString	divider;
				if ( filePath.Left( fRootFolderApp.GetLength() ).EqualNoCase( fRootFolderApp )  )
				{
					divider	= filePath.Mid( fRootFolderApp.GetLength() );
				}
				else if ( filePath.Left( fRootFolderUsr.GetLength() ).EqualNoCase( fRootFolderUsr )  )
				{
					divider	= filePath.Mid( fRootFolderUsr.GetLength() );
				}
				else
				{
					ptrdiff_t at = filePath.Find( fStandardFolderName );
					if ( at != -1 )
					{
						divider = filePath.Mid( at + fStandardFolderName.GetLength() + 1 );
					}
				}

				size_t level = 0;
				if ( ! divider.IsEmpty() )
				{
					size_t	divLen = divider.GetLength();
					ptrdiff_t at = 0;
					while ( true )
					{
						ptrdiff_t at1 = divider.Find( '\\', at );
						ptrdiff_t at2 = divider.Find( '/', at );

						at = -1;
						if ( at1 != -1 )
						{
							at = (at2 == -1) ? at1 : Min( at1, at2 );
						}
						else if ( at2 != -1 )
						{
							at = (at1 == -1) ? at2 : Min( at1, at2 );
						}

						if ( at != -1 && at != divLen - 1 ) // disregard the trailing symbol
						{
							level++;
							at++;
						}
						else
							break; //STOP!
					}
				}

				return level;
			}

		private:
			TDType						fObjectType;
			EFolderSpecifier			fFolderIndex;
			TXString					fSubFolderName;
			EResourceListCategoryType	fCategoryType;

			bool				fBaseDefValid;
			TDef				fBaseDef;

			typedef CContentFileSearchContext<TDef, TFileGroup>	TContentFileSearch;
			std::vector<TContentFileSearch*>	farrChildren;

			TXString			fRootFolderApp;
			TXString			fRootFolderUsr;
			TXString			fStandardFolderName;
			TFileFilterCallback fFileFilter;
		};
	}
}

void VWResourceListCategorized::DefaultContent_Init(TDType objectType, EFolderSpecifier folderIndex, const TXString& subFolderName, bool listAsFiles)
{
	farrDefaultContent.clear();

	SDefinition		def;
	def.fType			= EResourceListCategoryType::DefaultContent;
	def.fName			= TXResource("Vectorworks/Strings/4000 *", "ResourcePopupCategoryItemDefContent");
	def.fObjectType		= objectType;
	def.fFolderIndex	= folderIndex;
	def.fSubFolderName	= subFolderName;

	farrDefaultContent.push_back( def );

	if ( listAsFiles )
	{
		IApplicationFoldersPtr	appFolders( IID_ApplicationFolders );

		CContentFileSearchContext<SDefinition, SFileGroup>	context( objectType, folderIndex, subFolderName, EResourceListCategoryType::DefaultContent );
		appFolders->ForEachFileInStandardFolderN( folderIndex, subFolderName, ETraverse::NonRecursively_IncludeWorkgroupFolders, & context );

		context.GetDefs( farrDefaultContent );

		if ( farrDefaultContent.size() > 1 )
		{
			// the Default Content item should not be selectable if we have sub items
			farrDefaultContent[0].fIsSelectable = false;
		}
	}
}

void VWResourceListCategorized::DefaultContent_Set(TNameFilterCallback filter)
{
	for(auto& it : farrDefaultContent )
	{
		it.fFilterName = filter;
	}
}

void VWResourceListCategorized::DefaultContent_Set(TPostProcessCallback postProcess)
{
	for(auto& it : farrDefaultContent )
	{
		it.fPostProcess = postProcess;
	}
}

// ------------------------------------------------------------------------------------------------------------
// List resources from open documents other than the current document
void VWResourceListCategorized::OpenDocuments_Init(TDType objectType)
{
    TVWArray_OpenFileInformation arrFiles;
    gSDK->GetOpenFilesList(arrFiles);
 
	farrOpenDocuments.clear();

	if ( arrFiles.GetSize() > 1 )
	{
		SDefinition	rootDef;
		rootDef.fType				= EResourceListCategoryType::OpenDocuments;
		rootDef.fName				= TXResource("Vectorworks/Strings/4000 *", "ResourcePopupCategoryItemOpenFiles");
		rootDef.fObjectType			= objectType;
		rootDef.fIsSelectable		= false;
		farrOpenDocuments.push_back( rootDef );

		for(size_t i=0, cnt=arrFiles.GetSize(); i<cnt; ++i)
		{
			// exclude the currently open document in this list
		    if ( !arrFiles[i].fIsActive)
			{
				TXString fileName;
				arrFiles[i].fpFileID->GetFileName(fileName);;

				SDefinition	def;
				def.fType					= EResourceListCategoryType::OpenDocuments;
				def.fName					= fileName;
				def.fNameIndex				= arrFiles[i].fFileRef;
				def.fObjectType				= objectType;
				def.fRootLevel				= 1;

				farrOpenDocuments.push_back( def );
			}
		}
	}
}

void VWResourceListCategorized::OpenDocuments_Set(THandleFilterCallback filter)
{
	for(auto& it : farrOpenDocuments )
	{
		it.fFilterHandle = filter;
	}
}

void VWResourceListCategorized::OpenDocuments_Set(TNameFilterCallback filter)
{
	for(auto& it : farrOpenDocuments )
	{
		it.fFilterName = filter;
	}
}

void VWResourceListCategorized::OpenDocuments_Set(TPostProcessCallback postProcess)
{
	for(auto& it : farrOpenDocuments )
	{
		it.fPostProcess = postProcess;
	}
}

// ------------------------------------------------------------------------------------------------------------
// List resources from the resource browser favorites files
void VWResourceListCategorized::Favorites_Init(TDType objectType)
{
	TVWArray_IFileIdentifierPtr	arrFiles;
	gSDK->GetFavoritesList( arrFiles );

	farrFavorites.clear();

	if ( arrFiles.GetSize() > 0 )
	{
		SDefinition	rootDef;
		rootDef.fType				= EResourceListCategoryType::Favorites;
		rootDef.fName				= TXResource("Vectorworks/Strings/4000 *", "ResourcePopupCategoryItemFavorites");
		rootDef.fObjectType			= objectType;
		rootDef.fIsSelectable		= false;
		farrFavorites.push_back( rootDef );

		for(size_t i=0, cnt=arrFiles.GetSize(); i<cnt; ++i)
		{
			TXString fileName;
			arrFiles[ i ]->GetFileName(fileName);

            SFileGroup fileGroup;
            fileGroup.fFileID = arrFiles[i];  //name part of group isn't used for favorites. Just using group to set the fileID.

			SDefinition	def;
			def.fType					= EResourceListCategoryType::Favorites;
			def.fName					= fileName;
			def.fNameIndex				= i;
			def.fObjectType				= objectType;
			def.fRootLevel				= 1;
            def.farrFileGroups.push_back(fileGroup);

			farrFavorites.push_back( def );
		}
	}
}

void VWResourceListCategorized::Favorites_Set(TNameFilterCallback filter)
{
	for(auto& it : farrFavorites )
	{
		it.fFilterName = filter;
	}
}

void VWResourceListCategorized::Favorites_Set(TPostProcessCallback postProcess)
{
	for(auto& it : farrFavorites )
	{
		it.fPostProcess = postProcess;
	}
}

// ------------------------------------------------------------------------------------------------------------
// List resources for specific files
void VWResourceListCategorized::Files_Init(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath)
{
	farrFiles.clear();
	this->Files_Add( objectType, folderSpec, relativePath, nullptr, "" );
}

void VWResourceListCategorized::Files_Init(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, const TXString& groupName)
{
	farrFiles.clear();
	this->Files_Add( objectType, folderSpec, relativePath, nullptr, groupName );
}

void VWResourceListCategorized::Files_Init(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, TFileFilterCallback fileFilter)
{
	farrFiles.clear();
	this->Files_Add( objectType, folderSpec, relativePath, fileFilter, "" );
}

void VWResourceListCategorized::Files_Init(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, TFileFilterCallback fileFilter, const TXString& groupName)
{
	farrFiles.clear();
	this->Files_Add( objectType, folderSpec, relativePath, fileFilter, groupName );
}

void VWResourceListCategorized::Files_Clear()
{
	farrFiles.clear();
}

void VWResourceListCategorized::Files_Add(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath)
{
	this->Files_Add( objectType, folderSpec, relativePath, nullptr, "" );
}

void VWResourceListCategorized::Files_Add(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, const TXString& groupName)
{
	this->Files_Add( objectType, folderSpec, relativePath, nullptr, groupName );
}

void VWResourceListCategorized::Files_Add(TDType objectType, EFolderSpecifier folderSpec, const TXString& relativePath, TFileFilterCallback fileFilter)
{
	this->Files_Add( objectType, folderSpec, relativePath, fileFilter, "" );
}

void VWResourceListCategorized::Files_Add(TDType objectType, EFolderSpecifier folderSpec, const TXString& inRelativePath, TFileFilterCallback fileFilter, const TXString& groupName)
{
	IApplicationFoldersPtr	appFolders( IID_ApplicationFolders );

	TXString	rootFolderApp;
	TXString	rootFolderUsr;
	IFolderIdentifierPtr	rootFolder( IID_FolderIdentifier );
	rootFolder->Set( folderSpec, false, inRelativePath );
	rootFolder->GetFullPath( rootFolderApp );
	rootFolder->Set( folderSpec, true, inRelativePath );
	rootFolder->GetFullPath( rootFolderUsr );

	CContentFileSearchContext<SDefinition, SFileGroup>	context( objectType, folderSpec, inRelativePath, EResourceListCategoryType::File );
	context.SetFileFilter( fileFilter );
	appFolders->ForEachFileInStandardFolderN( folderSpec, inRelativePath, ETraverse::NonRecursively_IncludeWorkgroupFolders, & context );

	if ( context.HasDefs() )
	{
		SDefinition	rootDef;
		rootDef.fType				= EResourceListCategoryType::File;
		rootDef.fName				= groupName.IsEmpty() ? TXResource("Vectorworks/Strings/4000 *", "ResourcePopupCategoryItemCustomFiles") : groupName;
		rootDef.fObjectType			= objectType;
		rootDef.fIsSelectable		= false;
		farrFiles.push_back( rootDef );

		context.GetDefs( farrFiles );
	}
}

void VWResourceListCategorized::Files_Add(TDType objectType, IFileIdentifier* fileID)
{
	SFileGroup	fileGroup;
	fileGroup.fFileID	= fileID;

	SDefinition		def;
	def.fType		= EResourceListCategoryType::File;
	def.fObjectType	= objectType;
	def.farrFileGroups.push_back( fileGroup );

	fileID->GetFileName( def.fName );

	farrFiles.push_back( def );
}

void VWResourceListCategorized::Files_Set(TNameFilterCallback filter)
{
	for(auto& it : farrFiles)
	{
		it.fFilterName = filter;
	}
}

void VWResourceListCategorized::Files_Set(TPostProcessCallback postProcess)
{
	for(auto& it : farrFiles)
	{
		it.fPostProcess = postProcess;
	}
}

void VWResourceListCategorized::Custom_Add(const TXString& name, TPostProcessCallback postProcess)
{
	SDefinition		def;
	def.fType			= EResourceListCategoryType::Custom;
	def.fName			= name;
	def.fPostProcess	= postProcess;
	farrFiles.push_back( def );
}

void VWResourceListCategorized::CreateCategoriesForSymbolFolders(THandleFilterCallback filter, MCObjectHandle hContainer, size_t level)
{
	if ( hContainer == NULL )
	{
		hContainer = gSDK->FindAuxObject( gSDK->GetDrawingHeader(), symListNode );
	}

	if ( hContainer )
	{
		for(MCObjectHandle hObject = gSDK->FirstMemberObj( hContainer );
			hObject && *hObject;
			hObject = gSDK->NextObject( hObject ))
		{
			short type = gSDK->GetObjectTypeN( hObject );
			if ( type == kFolderNode )
			{
				bool hasValidObjects = true;
				if ( filter )
				{
					hasValidObjects = false;
					for(MCObjectHandle hInnerObj = gSDK->FirstMemberObj( hObject );
						hInnerObj && *hInnerObj && gSDK->GetObjectTypeN( hInnerObj ) != kTermNode;
						hInnerObj = gSDK->NextObject( hInnerObj ))
					{
						if ( filter( hInnerObj ) )
						{
							hasValidObjects = true;
							break;
						}
					}
				}

				if ( hasValidObjects )
				{
					SDefinition		def;
					def.fType						= EResourceListCategoryType::Document;
					def.fObjectType					= kSymDefNode;
					def.fSymFoldersAreCategories	= true;
					def.fFilterHandle = filter;
					gSDK->GetObjectName( hObject, def.fSymFolderName );

					for(size_t i=0; i<level+1; ++i)
					{
						def.fName += "  ";
					}

					def.fName += def.fSymFolderName;

					farrDocument.push_back( def );
				}

				this->CreateCategoriesForSymbolFolders( filter, hObject, level + 1 );
			}
		}
	}
}

bool VWResourceListCategorized::FindDocumentSymbolFolderCategory(const TXString& symName, size_t& categoryIndex)
{
	bool result = false;

	TXString	objName;
	for(size_t i=0, cnt=farrDocument.size(); i<cnt && !result; ++i)
	{
		const auto& it = farrDocument[ i ];

		if ( it.fObjectType == kSymDefNode )
		{
			MCObjectHandle hContainer = NULL;
			if ( it.fSymFolderName.IsEmpty() )	hContainer = gSDK->FindAuxObject( gSDK->GetDrawingHeader(), symListNode );
			else								hContainer = gSDK->GetNamedObject( it.fSymFolderName );
		
			for(MCObjectHandle hObject = gSDK->FirstMemberObj( hContainer );
				hObject && *hObject;
				hObject = gSDK->NextObject( hObject ))
			{
				short type = gSDK->GetObjectTypeN( hObject );
				if ( type == kSymDefNode )
				{
					bool process = true;

					if ( it.fFilterHandle )
						process = it.fFilterHandle( hObject );

					if ( process )
					{
						gSDK->GetObjectName( hObject, objName );
						if ( objName == symName )
						{
							categoryIndex = i;
							result	= true;
							break;
						}
						else if ( symName.IsEmpty() && ! objName.IsEmpty() )
						{
							// this is the default case when 'symName' is empty
							// default to the first found that is valid
							categoryIndex = i;
							result	= true;
							break;
						}
					}
				}
			}
		}
		else
		{
			MCObjectHandle h = gSDK->GetNamedObject( symName );
			if ( h && gSDK->GetObjectTypeN(h) == it.fObjectType )
			{
				categoryIndex = i;
				result = true;
				break;
			}
		}
	}

	return result;
}

VWResourceListCategorized::TDefinitionsArray& VWResourceListCategorized::GetDefinitionArray(EResourceListCategoryType type)
{
	switch ( type )
	{
		default:
		case EResourceListCategoryType::Document:		return farrDocument;
		case EResourceListCategoryType::DefaultContent:	return farrDefaultContent;
		case EResourceListCategoryType::File:			return farrFiles;
		case EResourceListCategoryType::Custom:			return farrCustom;
		case EResourceListCategoryType::OpenDocuments:	return farrOpenDocuments;
		case EResourceListCategoryType::Favorites:		return farrFavorites;
	}
}

void VWResourceListCategorized::GetCategories(const TDefinitionsArray& arrDefinitions, TXStringArray& outArrCategories, TCategoryMappingArray& outCategoryMapping, size_t& outCategorySelIndex)
{
	for(size_t iDef=0, cntDef=arrDefinitions.size(); iDef<cntDef; ++iDef)
	{
		const auto& def = arrDefinitions[ iDef ];

		SCategoryItem	categoryItem;
		categoryItem.fDefinitionID.fType	= def.fType;
		categoryItem.fDefinitionID.fIndex	= iDef;
		categoryItem.fCategoryIndex			= outArrCategories.GetSize();

		if (	fSelectedItem.fDefinitionID.fType == def.fType
			&&	fSelectedItem.fDefinitionID.fIndex == iDef )
		{
			outCategorySelIndex = categoryItem.fCategoryIndex;
		}

		TXString	listName;
		if ( def.fRootLevel > 0 )
		{
			listName	= TXString( (UCChar)' ', (size_t)3 * def.fRootLevel );
		}

		listName	+= def.fName;

		outArrCategories.Append( listName );
		outCategoryMapping.push_back( categoryItem );
	}
}

void VWResourceListCategorized::BuildResourceList()
{
	if ( farrDocument.size() > 0 )
	{
		const auto& firstDoc = farrDocument[ 0 ];
		if ( firstDoc.fObjectType == kSymDefNode && firstDoc.fSymFoldersAreCategories )
		{
			// delete all except the first one
			for(size_t i=1, cnt=farrDocument.size(); i<cnt; ++i)
			{
				farrDocument.erase( farrDocument.begin() + 1 );
			}

			this->CreateCategoriesForSymbolFolders( firstDoc.fFilterHandle );
		}
	}

	fCategoriesArray.Clear();
	fCategoriesMapping.clear();
	size_t	categorySelIndex = size_t(-1);
	this->GetCategories( farrDocument		, fCategoriesArray, fCategoriesMapping, categorySelIndex );
	this->GetCategories( farrOpenDocuments	, fCategoriesArray, fCategoriesMapping, categorySelIndex );
	this->GetCategories( farrFavorites		, fCategoriesArray, fCategoriesMapping, categorySelIndex );
	this->GetCategories( farrDefaultContent , fCategoriesArray, fCategoriesMapping, categorySelIndex );
	this->GetCategories( farrFiles 			, fCategoriesArray, fCategoriesMapping, categorySelIndex );
	this->GetCategories( farrCustom 		, fCategoriesArray, fCategoriesMapping, categorySelIndex );

	bool updateSelIndex = ! fSelectionInitialized;
	this->EnsureSelectionInitializedPreFill();
	if ( updateSelIndex )
	{
		fSelectedItem.fCategoryIndex = categorySelIndex;
	}
	else if ( fSelectionInitSpecialItem )
	{
		fSelectedItem.fCategoryIndex = 0;
		fSelectedItem.fDefinitionID.fType = EResourceListCategoryType::Document;
		fSelectedItem.fDefinitionID.fIndex = 0;
		fSelectionInitSpecialItem = false;
	}

	// validate the mapping and update the selection
	for(auto& itMapping : fCategoriesMapping)
	{
		TDefinitionsArray& arrDefs = this->GetDefinitionArray( itMapping.fDefinitionID.fType );

		size_t	defIDIndex	= itMapping.fDefinitionID.fIndex;
		size_t	catIndex	= itMapping.fCategoryIndex;
		if ( defIDIndex < arrDefs.size() && catIndex < fCategoriesArray.GetSize() && ! arrDefs[ defIDIndex ].fIsSelectable )
		{
			size_t level = arrDefs[ defIDIndex ].fRootLevel;
			do
			{
				level = level + 1;

				defIDIndex	= itMapping.fDefinitionID.fIndex;
				catIndex	= itMapping.fCategoryIndex;

				do
				{
					defIDIndex++;
					catIndex++;
				}
				while ( defIDIndex < arrDefs.size()
					&&	catIndex < fCategoriesArray.GetSize()
					&&	( ! arrDefs[ defIDIndex ].fIsSelectable || arrDefs[ defIDIndex ].fRootLevel != level )
					);
				
			}
			while( defIDIndex >= arrDefs.size() && level < defIDIndex );
		}

		// just an overflow protection
		if ( defIDIndex < arrDefs.size() )
		{
			// update the selection
			if (	fSelectedItem.fDefinitionID.fType == itMapping.fDefinitionID.fType
				&&	fSelectedItem.fDefinitionID.fIndex == itMapping.fDefinitionID.fIndex )
			{
				fSelectedItem.fDefinitionID.fIndex	= defIDIndex;
				fSelectedItem.fCategoryIndex		= catIndex;
			}

			// update the mapping
			itMapping.fDefinitionID.fIndex	= defIDIndex;
			itMapping.fCategoryIndex		= catIndex;
		}
	}

	this->BuildResourceList( fSelectedItem.fDefinitionID );
	this->EnsureSelectionInitializedPostFill();
}

void VWResourceListCategorized::BuildResourceList(const SDefinition& def)
{
	switch ( def.fType )
	{
		case EResourceListCategoryType::Document:
		{
			SResourceItem	resourceItem;

			if ( def.fSymFoldersAreCategories && def.fObjectType == kSymDefNode )
			{
				this->BuildResourceList_Symbol( resourceItem, def );
			}
			else
			{
				resourceItem.fResourceList.BuildList( def.fObjectType );

				if ( def.fFilterHandle )
				{
					size_t cnt = resourceItem.fResourceList.GetNumItems();
					size_t i = 0;
					while ( i < cnt )
					{
						MCObjectHandle hResource = resourceItem.fResourceList.GetResource( i );
						if ( ! def.fFilterHandle( hResource ) )
						{
							resourceItem.fResourceList.DeleteResource( i );
							cnt = resourceItem.fResourceList.GetNumItems();
						}
						else
						{
							i++;
						}
					}
				}
			}

			farrResourceItems.push_back( resourceItem );
		}
		break;

		case EResourceListCategoryType::DefaultContent:
		{
			if ( def.farrFileGroups.size() > 0 )
			{
				bool hasMultiple = def.farrFileGroups.size() > 1;
				for(const SFileGroup& fileGroup : def.farrFileGroups)
				{
					if ( hasMultiple && ! fileGroup.fName.IsEmpty() )
					{
						SResourceItem	resourceItem;
						resourceItem.fSeparatorName	= fileGroup.fName;
						farrResourceItems.push_back( resourceItem );
					}

					SResourceItem	resourceItem;
					resourceItem.fResourceList.BuildList( def.fObjectType, fileGroup.fFileID );
					farrResourceItems.push_back( resourceItem );
				}
			}
			else
			{
				SResourceItem	resourceItem;
				resourceItem.fResourceList.BuildList( def.fObjectType, -def.fFolderIndex, def.fSubFolderName );
				farrResourceItems.push_back( resourceItem );
			}
		}
		break;

		case EResourceListCategoryType::File:
		{
			bool hasMultiple = def.farrFileGroups.size() > 1;
			for(const SFileGroup& fileGroup : def.farrFileGroups)
			{
				if ( hasMultiple && ! fileGroup.fName.IsEmpty() )
				{
					SResourceItem	resourceItem;
					resourceItem.fSeparatorName	= fileGroup.fName;
					farrResourceItems.push_back( resourceItem );
				}

				SResourceItem	resourceItem;
				resourceItem.fResourceList.BuildList( def.fObjectType, fileGroup.fFileID );
				farrResourceItems.push_back( resourceItem );
			}
		}
		break;

		case EResourceListCategoryType::OpenDocuments:
		{
			if ( def.fNameIndex != size_t(-1) )
			{
				SResourceItem	resourceItem;
				resourceItem.fResourceList.BuildList_OpenDocument( def.fObjectType, def.fNameIndex );
				farrResourceItems.push_back( resourceItem );
			}
		}
		break;

		case EResourceListCategoryType::Favorites:
		{
			if ( def.farrFileGroups.size() >=1 )
			{
				SResourceItem	resourceItem;
				resourceItem.fResourceList.BuildList( def.fObjectType, def.farrFileGroups[0].fFileID );  //only expect one item selected in favorites
				farrResourceItems.push_back( resourceItem );
			}
		}
		break;

		case EResourceListCategoryType::Custom:
			break;
	}

	if ( def.fFilterName )
	{
		for(SResourceItem& resItem : farrResourceItems)
		{
			size_t cnt = resItem.fResourceList.GetNumItems();
			size_t i = 0;
			while ( i < cnt )
			{
				if ( ! def.fFilterName( resItem.fResourceList, i ) )
				{
					resItem.fResourceList.DeleteResource( i );
					cnt = resItem.fResourceList.GetNumItems();
				}
				else
				{
					i++;
				}
			}
		}
	}

	if ( def.fPostProcess )
	{
		for(SResourceItem& resItem : farrResourceItems)
		{
			if ( resItem.fSeparatorName.IsEmpty() )
			{
				def.fPostProcess( resItem.fResourceList );
			}
		}
	}
}

void VWResourceListCategorized::ClearResourceList()
{
	farrResourceItems.clear();
}

void VWResourceListCategorized::BuildResourceList(const SDefinitionID& defID)
{
	this->ClearResourceList();

	TDefinitionsArray& arrDefs = this->GetDefinitionArray( defID.fType );
	if ( VERIFYN( kVStanev, defID.fIndex < arrDefs.size() ) )
	{
		this->BuildResourceList( arrDefs[ defID.fIndex ] );
	}
}

void VWResourceListCategorized::BuildResourceList_Symbol(SResourceItem& resourceItem, const SDefinition& def)
{
	TXString symbolFolderName = def.fSymFolderName;
	MCObjectHandle hContainer = gSDK->GetNamedObject( def.fSymFolderName );
	if ( hContainer == NULL )
	{
		symbolFolderName.Clear();
		hContainer = gSDK->FindAuxObject( gSDK->GetDrawingHeader(), symListNode );
	}

	resourceItem.fResourceList.BuildList( kSymDefNode );

	// Originally, this traversed symbol folder and performed AddResource for each symbol.
	// However, AddResource does enough processing to cause performance problems when there
	// are large numbers of symbols. It turns out that building the resource list for symbols
	// and removing those that aren't in the folder (or aren't allowed because of the filter)
	// is faster. There is currently no BuildResourceList method that just builds for a
	// single symbol folder. MLieblein 5/2015

	size_t cnt = resourceItem.fResourceList.GetNumItems();
	size_t i = 0;
	while ( i < cnt )
	{
		MCObjectHandle hResource = resourceItem.fResourceList.GetResource( i );
		TXString   parentName; 
		resourceItem.fResourceList.GetParentFolderNameFromResourceList ( i, parentName);
		if ( (parentName != symbolFolderName) || (def.fFilterHandle && ! def.fFilterHandle( hResource )) )
		{
			resourceItem.fResourceList.DeleteResource( i );
			cnt = resourceItem.fResourceList.GetNumItems();
		}
		else
		{
			i++;
		}
	}
}

void VWResourceListCategorized::EnsureSelectionInitializedPreFill()
{
	if ( ! fSelectionInitialized )
	{
		if ( this->FindDocumentSymbolFolderCategory( fSelectedItemText, fSelectedItem.fDefinitionID.fIndex ) )
		{
			fSelectedItem.fDefinitionID.fType	= EResourceListCategoryType::Document;
			fSelectedItem.fCategoryIndex		= 0;
			fSelectionInitialized = true;
		}
		else if ( farrDefaultContent.size() > 1 )
		{
			fSelectedItem.fDefinitionID.fType	= EResourceListCategoryType::DefaultContent;
			fSelectedItem.fDefinitionID.fIndex	= 0;
			fSelectedItem.fCategoryIndex		= 0;
			fSelectionInitialized 		= true;
		}
		else if ( farrFiles.size() > 0 )
		{
			fSelectedItem.fDefinitionID.fType	= EResourceListCategoryType::File;
			fSelectedItem.fDefinitionID.fIndex	= 0;
			fSelectedItem.fCategoryIndex		= 0;
			fSelectionInitialized 		= true;
		}
	}
}

void VWResourceListCategorized::EnsureSelectionInitializedPostFill()
{
	if ( ! fSelectionInitialized )
	{
		fSelectionInitialized = true;
	}
}

inline TXString _TruncateAndMaybeAddEllipsis(const TXString& in)
{
	enum { kMaxLength = 31 };

	TXString result = in;

	if(result.GetLength() > kMaxLength)
	{
		result.Truncate(kMaxLength-3);
		result += "...";
	}

	return result;
}

void VWResourceListCategorized::ToolModeGroup_Init(short modeGroup, const TXString& emptyMsg)
{
	fEmptyMessage = emptyMsg;

	TXString item = fSelectedItemText;
	if ( item.IsEmpty() )
	{
		item = fEmptyMessage;
	}

	TXString itemTruncated = ::_TruncateAndMaybeAddEllipsis(item);
	gSDK->SetPullDownResourceValue( DemoteTo<short>(kVStanev, modeGroup+1), itemTruncated );

	// make sure we have the resource list up to date
	// as the tool might use it without showing the popup
	this->BuildResourceList();
}

bool VWResourceListCategorized::ToolModeGroup_Show(short modeGroup)
{
	return this->PopupMng_Show( nullptr, nullptr, 0, modeGroup );
}

bool VWResourceListCategorized::DirectScreen_Show(const ViewPt& pt)
{
	return this->PopupMng_Show( & pt, nullptr, 0, 0 );
}

bool VWResourceListCategorized::ShapePane_Show(IShapePaneWidgetAccess* widgetAccess, SintptrT viewWidget)
{
	return this->PopupMng_Show( nullptr, widgetAccess, viewWidget, 0 );
}

bool VWResourceListCategorized::PopupMng_Show(const ViewPt* pt, IShapePaneWidgetAccess* widgetAccess, SintptrT viewWidget, short modeGroup)
{
	this->BuildResourceList();

	bool	showResultOk = false;
	Sint32	showResultIndex	= -1;
	if ( fCategoriesArray.GetSize() > 1 )
	{
		SCategoryItem	selItem		= fSelectedItem;
		do
		{
			SShowPullDownResourcePopup	data;
			if ( selItem.fCategoryIndex == 0 && selItem.fDefinitionID.fType == EResourceListCategoryType::Document )
			{
				data.fSpecialItemName	= fDocumentDefaultItemName;
				data.fSpecialItemImage	= fDocumentDefaultItemImageSpec;
			}
			for(SResourceItem& resItem : farrResourceItems)
			{
				if ( resItem.fSeparatorName.IsEmpty() )
					data.AddItem( resItem.fResourceList.GetListID() );
				else
					data.AddItem( resItem.fSeparatorName );
			}

			if ( pt )
				showResultIndex = gSDK->ShowPullDownResourcePopupN( *pt, data, fSelectedItemText, fCategoryTitle, fCategoriesArray, selItem.fCategoryIndex);
			else if ( widgetAccess )
				showResultIndex = widgetAccess->ShowPullDownResourcePopup( viewWidget, data, fSelectedItemText, fCategoryTitle, fCategoriesArray, selItem.fCategoryIndex);
			else
				showResultIndex = gSDK->ShowPullDownResourcePopup(DemoteTo<short>(kVStanev, modeGroup+1), data, fSelectedItemText, fCategoryTitle, fCategoriesArray, selItem.fCategoryIndex);

			if ( showResultIndex < -1 )
			{
				// category changed
				selItem.fCategoryIndex	= - showResultIndex - 2;
				if ( selItem.fCategoryIndex >= fCategoriesMapping.size() )
					break; // STOP!

				selItem = fCategoriesMapping[ selItem.fCategoryIndex ];
				this->BuildResourceList( selItem.fDefinitionID );
			}
			else
				break; // STOP!
		} while ( true );

		if ( showResultIndex >= 0 )
		{
			showResultOk	= true;

			if (	selItem.fCategoryIndex == 0 && selItem.fDefinitionID.fType == EResourceListCategoryType::Document
				&&	! fDocumentDefaultItemName.IsEmpty() /*has special item*/ )
			{
				// the resource contains the extra special item
				// account for this if necessary
				if ( selItem.fDefinitionID.fIndex == 0 ) // the special item is always first
				{
					showResultIndex--;
				}
			}

			fSelectedItem		= selItem;
			this->BuildResourceList( fSelectedItem.fDefinitionID );
		}
	}
	else
	{
		SShowPullDownResourcePopup	data;
		if ( fSelectedItem.fCategoryIndex == 0 && fSelectedItem.fDefinitionID.fType == EResourceListCategoryType::Document )
		{
			data.fSpecialItemName	= fDocumentDefaultItemName;
			data.fSpecialItemImage	= fDocumentDefaultItemImageSpec;
		}
		for(SResourceItem& resItem : farrResourceItems)
		{
			if ( resItem.fSeparatorName.IsEmpty() )
				data.AddItem( resItem.fResourceList.GetListID() );
			else
				data.AddItem( resItem.fSeparatorName );
		}

		TXStringArray arrEmpty;
		if ( pt )
			showResultIndex = gSDK->ShowPullDownResourcePopupN( *pt, data, fSelectedItemText, "", arrEmpty, 0, kStandardSize );
		else if ( widgetAccess )
			showResultIndex = widgetAccess->ShowPullDownResourcePopup( viewWidget, data, fSelectedItemText, "", arrEmpty, 0, kStandardSize );
		else
			showResultIndex = gSDK->ShowPullDownResourcePopup( DemoteTo<short>(kVStanev, modeGroup+1), data, fSelectedItemText, "", arrEmpty, 0, kStandardSize );

		showResultOk = showResultIndex >= 0;
	}

	fSelectedInfo.Clear();
	if ( showResultOk )
	{
		if ( showResultIndex == -1 )
		{
			fSelectedInfo.fIsSpecialItem = true;
			fSelectedItemText.Clear();
		}
		else if ( this->UpdateSelectionInfo( showResultIndex ) )
		{
			if ( fSelectedInfo.fResourceIndex < farrResourceItems.size() )
			{
				SResourceItem& resItem = farrResourceItems[ fSelectedInfo.fResourceIndex ];
				resItem.fResourceList.GetActualResourceName( fSelectedInfo.fResourceListIndex, fSelectedItemText );
			}
		}

		if ( pt == nullptr && widgetAccess == nullptr )
		{
			TXString item = fSelectedItemText;
			if ( item.IsEmpty() )
			{
				item = fEmptyMessage;
			}

			TXString itemTruncated = ::_TruncateAndMaybeAddEllipsis(item);
			gSDK->SetPullDownResourceValue(DemoteTo<short>(kVStanev, modeGroup+1), itemTruncated);
		}
	}
	else
	{
		// the selection was canceled from the popup
		// so, we need to update fSelectedInfo accordingly

		this->BuildResourceList();
		this->UpdateSelectionInfo( -1 );
	}

	return showResultOk;
}


bool VWResourceListCategorized::UpdateSelectionInfo(Sint32 globalIndex)
{
	bool	result = false;

	Sint32	thisListIndex = 0;
	for(size_t iResIndex=0, cnt=farrResourceItems.size(); iResIndex<cnt; ++iResIndex)
	{
		SResourceItem& item = farrResourceItems[ iResIndex ];

		Sint32	nextListIndex = 0;
		if ( item.fSeparatorName.IsEmpty() == false )
			nextListIndex = thisListIndex + 1;
		else
			nextListIndex = thisListIndex + (Sint32) item.fResourceList.GetNumItems();

		bool	found = false;
		Sint32	foundIndex = 0;
		if ( globalIndex >= 0 )
		{
			found		= (thisListIndex <= globalIndex && globalIndex < nextListIndex);
			foundIndex	= globalIndex;
		}
		else
		{
			size_t resIndex = item.fResourceList.FindResource( fSelectedItemText );
			if ( resIndex != size_t(-1) )
			{
				found		= true;
				foundIndex	= thisListIndex + Sint32(resIndex);
			}
		}

		if ( found )
		{
			fSelectedInfo.fResourceGlobalIndex	= foundIndex;
			fSelectedInfo.fResourceIndex		= iResIndex;
			fSelectedInfo.fResourceListIndex	= foundIndex - thisListIndex;
			result = true;

			break;		// STOP!
		}

		thisListIndex = nextListIndex;
	}

	return result;
}

void VWResourceListCategorized::DialogImagePopup_Init(VWFC::VWUI::VWDialog* dialog, VWFC::VWUI::TControlID imagePopupCtrlID)
{
	this->DialogImagePopup_Init( dialog->GetDialogID(), imagePopupCtrlID );
}

bool VWResourceListCategorized::DialogImagePopup_Event(VWFC::VWUI::VWDialog* dialog, VWFC::VWUI::TControlID imagePopupCtrlID, VWFC::VWUI::VWDialogEventArgs& eventArgs)
{
	bool result = false;
	if ( eventArgs.IsImagePopupSelected() )
	{
		result = this->DialogImagePopup_Event_Selected( dialog->GetDialogID(), imagePopupCtrlID );
	}
	else if ( eventArgs.IsImagePopupBeforeOpen() )
	{
		result = this->DialogImagePopup_Event_BeforeOpen( dialog->GetDialogID(), imagePopupCtrlID );
	}
	else if ( eventArgs.IsImagePopupCategoryChanged( fSelectedItem.fCategoryIndex ) )
	{
		result = this->DialogImagePopup_Event_CategoryChange( dialog->GetDialogID(), imagePopupCtrlID );
	}

	return result;
}

void VWResourceListCategorized::DialogImagePopup_Update(VWFC::VWUI::VWDialog* dialog, VWFC::VWUI::TControlID imagePopupCtrlID, const TXString& itemName)
{
	this->DialogImagePopup_Update( dialog->GetDialogID(), imagePopupCtrlID, itemName );
}

void VWResourceListCategorized::DialogImagePopup_Init(Sint32 dialogID, Sint32 imagePopupCtrlID)
{
	gSDK->SetImagePopupResourceAdvanced( dialogID, imagePopupCtrlID );

	this->BuildResourceList();

	if ( fSelectedItem.fCategoryIndex < fCategoriesMapping.size() )
	{
		fCategoriesTempSelection = fCategoriesMapping[ fSelectedItem.fCategoryIndex ];
	}
	else
	{
		fCategoriesTempSelection.fDefinitionID.fType	= EResourceListCategoryType::Document;
		fCategoriesTempSelection.fDefinitionID.fIndex	= 0;
		fCategoriesTempSelection.fCategoryIndex			= 0;
	}

	size_t selResourceIndex = size_t(-1);

	gSDK->SetImagePopupResourceCategories( dialogID, imagePopupCtrlID, fCategoryTitle, fCategoriesArray, fCategoriesTempSelection.fCategoryIndex );
	gSDK->RemoveAllImagePopupItems( dialogID, imagePopupCtrlID );

	size_t	globalResIndex = 0;
	for(SResourceItem& resItem : farrResourceItems)
	{
		if ( resItem.fSeparatorName.IsEmpty() )
		{
			Sint32	resListID = resItem.fResourceList.GetListID();
			size_t	resCnt	= resItem.fResourceList.GetNumItems();
			for(size_t i=0; i<resCnt; ++i)
			{
				gSDK->InsertImagePopupResource( dialogID, imagePopupCtrlID, resListID, DemoteTo<Sint32>( kVStanev, i+1) );
			}

			if ( selResourceIndex == size_t(-1) )
			{
				size_t foundResIndex = resItem.fResourceList.FindResource( fSelectedItemText, size_t(-1) );
				if ( foundResIndex != size_t(-1) )
				{
					selResourceIndex = (globalResIndex + foundResIndex);
				}
			}

			globalResIndex += resCnt;
		}
		else
		{
			gSDK->InsertImagePopupSeparator( dialogID, imagePopupCtrlID, resItem.fSeparatorName );
			globalResIndex++;
		}
	}

	// dont let it stay without selection as we dont want the dialog to have an empty selection
	if ( selResourceIndex == size_t(-1) )
		selResourceIndex = 0;

	gSDK->SetImagePopupSelectedItem( dialogID, imagePopupCtrlID, DemoteTo<short>( kVStanev, selResourceIndex+1) );

	fSelectedInfo.Clear();
	this->UpdateSelectionInfo( (Sint32) selResourceIndex ); 
}

bool VWResourceListCategorized::DialogImagePopup_Event(Sint32 dialogID, Sint32 imagePopupCtrlID, void* eventArgs)
{
	bool result = false;
	if ( imagePopupCtrlID >= 0 )
	{
		result = this->DialogImagePopup_Event_Selected( dialogID, imagePopupCtrlID );
	}
	else if ( imagePopupCtrlID < 0 && eventArgs )
	{
		imagePopupCtrlID = -imagePopupCtrlID;
		SImagePopupAdvancedMsgData* pInfo = (SImagePopupAdvancedMsgData*) eventArgs;
		if ( pInfo->fReason == SImagePopupAdvancedMsgData::Opened )
		{
			result = this->DialogImagePopup_Event_BeforeOpen( dialogID, imagePopupCtrlID );
		}
		else if ( pInfo->fReason == SImagePopupAdvancedMsgData::CategoryChanged )
		{
			fSelectedItem.fCategoryIndex	= pInfo->fCategoryIndex;
			result = this->DialogImagePopup_Event_CategoryChange( dialogID, imagePopupCtrlID );
		}
	}

	return result;
}

void VWResourceListCategorized::DialogImagePopup_Update(Sint32 dialogID, Sint32 imagePopupCtrlID, const TXString& itemName)
{
	//this->SetInitialSelectedItem( itemName, true );

	this->BuildResourceList();

	size_t selResourceIndex = size_t(-1);;
	
	gSDK->RemoveAllImagePopupItems( dialogID, imagePopupCtrlID );

	for(SResourceItem& resItem : farrResourceItems)
	{
		if ( resItem.fSeparatorName.IsEmpty() )
		{
			Sint32	resListID = resItem.fResourceList.GetListID();
			for(size_t i=0, cnt=resItem.fResourceList.GetNumItems(); i<cnt; ++i)
			{
				gSDK->InsertImagePopupResource( dialogID, imagePopupCtrlID, resListID, DemoteTo<Sint32>( kVStanev, i+1) );
			}

			if ( selResourceIndex == size_t(-1) )
			{
				selResourceIndex = resItem.fResourceList.FindResource( fSelectedItemText, 0 );
			}
		}
		else
		{
			gSDK->InsertImagePopupSeparator( dialogID, imagePopupCtrlID, resItem.fSeparatorName );
		}
	}

	gSDK->SetImagePopupSelectedItem( dialogID, imagePopupCtrlID, DemoteTo<short>( kVStanev, selResourceIndex+1) );
}

bool VWResourceListCategorized::DialogImagePopup_Event_Selected(Sint32 dialogID, TControlID imagePopupCtrlID)
{
	fSelectedItem		= fCategoriesTempSelection;
	this->BuildResourceList( fSelectedItem.fDefinitionID );

	short	selIndexInner	= gSDK->GetImagePopupSelectedItem( dialogID, imagePopupCtrlID );
	size_t	selIndex		= selIndexInner <= 0 ? size_t(-1) : size_t(selIndexInner-1);

	if ( this->UpdateSelectionInfo( (Sint32) selIndex ) )
	{
		if ( fSelectedInfo.fResourceIndex < farrResourceItems.size() )
		{
			SResourceItem& resItem = farrResourceItems[ fSelectedInfo.fResourceIndex ];
			resItem.fResourceList.GetActualResourceName( fSelectedInfo.fResourceListIndex, fSelectedItemText );
		}
	}
	
	return true;
}

bool VWResourceListCategorized::DialogImagePopup_Event_BeforeOpen(Sint32 dialogID, TControlID imagePopupCtrlID)
{
	this->BuildResourceList();

	fCategoriesTempSelection = fCategoriesMapping[ fSelectedItem.fCategoryIndex ];

	gSDK->SetImagePopupResourceCategories( dialogID, imagePopupCtrlID, fCategoryTitle, fCategoriesArray, fCategoriesTempSelection.fCategoryIndex );
	gSDK->RemoveAllImagePopupItems( dialogID, imagePopupCtrlID );

	size_t selResourceIndex = size_t(-1);

	for(SResourceItem& resItem : farrResourceItems)
	{
		if ( resItem.fSeparatorName.IsEmpty() )
		{
			Sint32	resListID = resItem.fResourceList.GetListID();
			for(size_t i=0, cnt=resItem.fResourceList.GetNumItems(); i<cnt; ++i)
			{
				gSDK->InsertImagePopupResource( dialogID, imagePopupCtrlID, resListID, DemoteTo<Sint32>( kVStanev, i+1) );
			}
		}
		else
		{
			gSDK->InsertImagePopupSeparator( dialogID, imagePopupCtrlID, resItem.fSeparatorName );
		}

		if ( selResourceIndex == size_t(-1) )
		{
			selResourceIndex = resItem.fResourceList.FindResource( fSelectedItemText, 0 );
		}
	}

	gSDK->SetImagePopupSelectedItem( dialogID, imagePopupCtrlID, DemoteTo<short>( kVStanev, selResourceIndex+1) );

	return true;
}

bool VWResourceListCategorized::DialogImagePopup_Event_CategoryChange(Sint32 dialogID, TControlID imagePopupCtrlID)
{
	fCategoriesTempSelection = fCategoriesMapping[ fSelectedItem.fCategoryIndex ];
	this->BuildResourceList( fCategoriesTempSelection.fDefinitionID );

	gSDK->SetImagePopupResourceCategories( dialogID, imagePopupCtrlID, fCategoryTitle, fCategoriesArray, fCategoriesTempSelection.fCategoryIndex );
	gSDK->RemoveAllImagePopupItems( dialogID, imagePopupCtrlID );
	size_t numResources = -1;
	for(SResourceItem& resItem : farrResourceItems)
	{
		if ( resItem.fSeparatorName.IsEmpty() )
		{
			Sint32	resListID = resItem.fResourceList.GetListID();
			numResources=resItem.fResourceList.GetNumItems();
			for(size_t i=0; i<numResources; ++i)
			{
				gSDK->InsertImagePopupResource( dialogID, imagePopupCtrlID, resListID, DemoteTo<Sint32>( kVStanev, i+1) );
			}
		}
		else
		{
			gSDK->InsertImagePopupSeparator( dialogID, imagePopupCtrlID, resItem.fSeparatorName );
		}
	}

	if (numResources == 0 )
	{
		gSDK->SetImagePopupSelectedItem( dialogID, imagePopupCtrlID,-1);
		fSelectionInitialized = false;
		fSelectedItemText = "";
		fSelectedInfo.fResourceListIndex = -1;
	}
	else
	{
		gSDK->SetImagePopupSelectedItem( dialogID, imagePopupCtrlID, DemoteTo<short>( kVStanev, 0+1) );
	}

	return true;
}

void VWResourceListCategorized::RevealInOS()
{
	TDefinitionsArray& arrDefs = this->GetDefinitionArray( fSelectedItem.fDefinitionID.fType );
	if ( VERIFYN( kVStanev, fSelectedItem.fDefinitionID.fIndex < arrDefs.size() ) )
	{
		SDefinition&	def = arrDefs[ fSelectedItem.fDefinitionID.fIndex ];
		if ( def.farrFileGroups.size() > 0 )
		{
			if( def.farrFileGroups[0].fFileID != NULL )
			{
				def.farrFileGroups[0].fFileID->RevealInOS();
			}
		}
	}
}
