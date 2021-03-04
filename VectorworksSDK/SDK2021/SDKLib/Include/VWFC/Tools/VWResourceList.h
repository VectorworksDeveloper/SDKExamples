#pragma once

// Wrapper for ResourceList-related ISDK functions
// All methods virtual to allow for smooth testing-related subclassing

namespace VWFC
{
	namespace Tools
	{
		class VWResourceList
		{
		public:
					VWResourceList();
					VWResourceList(Sint32 buildResourceListID);
					VWResourceList(const VWResourceList& src);
			virtual	~VWResourceList();

			VWResourceList& operator=(const VWResourceList& src);
			
			virtual size_t			BuildList(short objectType, bool sort = true);
			virtual size_t			BuildList(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, bool sort = true);
			virtual size_t			BuildList(short objectType, IFileIdentifier* fileID);
			virtual size_t			BuildList_OpenDocument(short objectType, size_t openDocumentIndex);
 
			virtual void			Dispose();

			virtual MCObjectHandle	GetResource(size_t index) const;
			virtual void			GetResourceName(size_t index, TXString& name) const;
			virtual void			GetActualResourceName(size_t index, TXString& name) const;
			virtual void			GetParentFolderNameFromResourceList (size_t index, TXString& name) const;

			virtual size_t			AddResource(MCObjectHandle resource);
			virtual void			DeleteResource(size_t index);

			virtual Sint32			GetListID() const;
			virtual size_t			GetNumItems() const;

			virtual size_t			FindResource(const TXString& name, size_t defaultResult=size_t(-1));

			virtual MCObjectHandle	ImportResourceToCurrentFile(size_t index);
			virtual MCObjectHandle	ImportResourceToCurrentFile(size_t index, VectorWorks::EImportResourceConflictResult resolveConflict);
			virtual void			UseImportConflictCallback(VectorWorks::TImportResourceConflictCallbackProcPtr conflictCallback, void* env = nullptr);

		private:
			typedef size_t	TResourceID;

			TResourceID	fResourceID;
			Sint32		fResourceListID;	// for performance, so we dont have to look it up every time
			
			VectorWorks::TImportResourceConflictCallbackProcPtr fConflictCallback;
			void*	fenv;

		// manage reference of resources for the copy operator
		// this is needed as VW doesn't provide copy functionality of resource lists
		private:
			struct SResourceInstnace
			{
				size_t	fRefCnt;
				bool	fCreated;
				Sint32	fResourceListID;

				SResourceInstnace();
				SResourceInstnace(Sint32 resListID);
			};

			typedef std::map<TResourceID, SResourceInstnace>	TID2ResourceInstanceMap;
			static TID2ResourceInstanceMap	s_resources;

			static TResourceID	RLISTCreateResource(Sint32 resListID, bool created, Sint32& outResListID);
			static TResourceID	RLISTDuplicateResource(TResourceID resID, Sint32& outResListID);
			static void			RLISTDeleteResource(TResourceID& resID);
		};
	}
}
