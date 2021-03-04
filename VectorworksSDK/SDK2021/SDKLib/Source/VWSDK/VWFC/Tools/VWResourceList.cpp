#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;

// ------------------------------------------------------------------------------------------------------------
/*static*/ VWResourceList::TID2ResourceInstanceMap	VWResourceList::s_resources;

/*static*/ VWResourceList::TResourceID VWResourceList::RLISTCreateResource(Sint32 resListID, bool created, Sint32& outResListID)
{
	static TResourceID s_uniqueResID = 0;
	s_uniqueResID++;
	if ( s_uniqueResID == 0 ) s_uniqueResID ++;

	SResourceInstnace	resInst;
	resInst.fRefCnt	= 1;
	resInst.fResourceListID = resListID;
	resInst.fCreated = created;

	VWResourceList::s_resources.insert( TID2ResourceInstanceMap::value_type( s_uniqueResID, resInst ) );

	outResListID	= resListID;

	return s_uniqueResID;
}

/*static*/ VWResourceList::TResourceID VWResourceList::RLISTDuplicateResource(TResourceID resID, Sint32& outResListID)
{
	TResourceID result = 0;
	if ( resID != 0 )
	{
		auto it = VWResourceList::s_resources.find( resID );
		if ( VERIFYN( kVStanev, it != VWResourceList::s_resources.end() ) )
		{
			SResourceInstnace&	resInst	= it->second;
			resInst.fRefCnt++;
			outResListID = resInst.fResourceListID;

			result = it->first;
		}
	}

	return result;
}

/*static*/ void VWResourceList::RLISTDeleteResource(TResourceID& resID)
{
	if ( resID != 0 )
	{
		auto it = VWResourceList::s_resources.find( resID );
		if ( VERIFYN( kVStanev, it != VWResourceList::s_resources.end() ) )
		{
			SResourceInstnace&	resInst	= it->second;
			if ( resInst.fRefCnt <= 1 )
			{
				// to be deleted
				if ( resInst.fCreated && resInst.fResourceListID )
				{
					gSDK->DisposeResourceList( resInst.fResourceListID );
				}

				VWResourceList::s_resources.erase( it );
				resID = 0;
			}
			else
			{
				resInst.fRefCnt--;
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------------------
VWResourceList::SResourceInstnace::SResourceInstnace()
{
	fRefCnt	= 0;
	fCreated = false;
	fResourceListID = 0;
}

// ------------------------------------------------------------------------------------------------------------
VWResourceList::VWResourceList()
	: fResourceID( 0 )
	, fResourceListID( 0 )
	, fConflictCallback(nullptr)
	, fenv(nullptr)
{
}

VWResourceList::VWResourceList(Sint32 buildResourceListID)
	: fConflictCallback(nullptr)
	, fenv(nullptr)
{
	fResourceID = VWResourceList::RLISTCreateResource( buildResourceListID, false, fResourceListID );
}

VWResourceList::VWResourceList(const VWResourceList& src)
	: fResourceID( 0 )
	, fResourceListID( 0 )
	, fConflictCallback( src.fConflictCallback )
	, fenv( src.fenv )
{
	fResourceID = VWResourceList::RLISTDuplicateResource( src.fResourceID, fResourceListID );
}

VWResourceList::~VWResourceList()
{
	this->Dispose();
	
	fConflictCallback = nullptr;
	fenv = nullptr;
}

VWResourceList& VWResourceList::operator=(const VWResourceList& src)
{
	this->Dispose();

	fResourceID = VWResourceList::RLISTDuplicateResource( src.fResourceID, fResourceListID );

	return *this;
}

size_t VWResourceList::BuildList(short objectType, bool sort/*=true*/)
{
	this->Dispose();

	Sint32 numItems = 0;
	Sint32 resListID = 0;

	if ( sort )	resListID = gSDK->BuildResourceList( objectType, kRootFolderSpecifier, "", numItems );
	else		resListID = gSDK->BuildResourceListUnsorted( objectType, kRootFolderSpecifier, "", numItems );

	fResourceID = VWResourceList::RLISTCreateResource( resListID, true, fResourceListID );

	return numItems;
}

size_t VWResourceList::BuildList(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, bool sort/*=true*/)
{
	this->Dispose();

	Sint32 numItems = 0;
	Sint32 resListID = 0;

	if ( sort )	resListID = gSDK->BuildResourceList( objectType, folderIndex, subFolderName, numItems );
	else		resListID = gSDK->BuildResourceListUnsorted( objectType, folderIndex, subFolderName, numItems );

	fResourceID = VWResourceList::RLISTCreateResource( resListID, true, fResourceListID );

	return numItems;
}

size_t VWResourceList::BuildList(short objectType, VectorWorks::Filing::IFileIdentifier* fileID)
{
	this->Dispose();
	
	Sint32 numItems = 0;
	Sint32	resListID = gSDK->BuildResourceListN(objectType, fileID, numItems);

	fResourceID = VWResourceList::RLISTCreateResource( resListID, true, fResourceListID );

	return numItems;
}

size_t VWResourceList::BuildList_OpenDocument(short objectType, size_t openDocumentIndex)
{
	this->Dispose();
	
	Sint32 numItems = 0;
	Sint32	resListID = gSDK->BuildResourceListFromOpenFile(objectType, openDocumentIndex, numItems);

	fResourceID = VWResourceList::RLISTCreateResource( resListID, true, fResourceListID );

	return numItems;
}

void VWResourceList::Dispose()
{
	VWResourceList::RLISTDeleteResource( fResourceID );
}

Sint32 VWResourceList::GetListID() const
{
	return fResourceListID;
}

size_t VWResourceList::GetNumItems() const
{
	return fResourceListID == 0 ? 0 : gSDK->ResourceListSize( fResourceListID );
}

MCObjectHandle VWResourceList::GetResource(size_t index) const
{
	return gSDK->GetResourceFromList(fResourceListID, Sint32(index+1) );
}

void VWResourceList::GetResourceName(size_t index, TXString& name) const
{
	gSDK->GetNameFromResourceList(fResourceListID, Sint32(index+1), name);
}

void VWResourceList::GetActualResourceName(size_t index, TXString& name) const
{
	gSDK->GetActualNameFromResourceList(fResourceListID, Sint32(index+1), name);
}

void VWResourceList::GetParentFolderNameFromResourceList(size_t index, TXString& name) const
{
	gSDK->GetParentFolderNameFromResourceList(fResourceListID, Sint32(index+1), name);
}

size_t VWResourceList::AddResource(MCObjectHandle resource)
{
	return gSDK->AddResourceToList(fResourceListID, resource);
}

void VWResourceList::DeleteResource(size_t index)
{
	gSDK->DeleteResourceFromList(fResourceListID, Sint32(index+1));
}

void VWResourceList::UseImportConflictCallback(VectorWorks::TImportResourceConflictCallbackProcPtr conflictCallback, void* env)
{
	fConflictCallback = conflictCallback;
	fenv = env;
}

size_t VWResourceList::FindResource(const TXString& name, size_t defaultResult)
{
	size_t result = defaultResult;

	TXString resName;
	for(size_t i=0, cnt=this->GetNumItems(); i<cnt; i++)
	{
		this->GetActualResourceName( i, resName );
		resName.Trim();
		if ( name == resName )
		{
			result = i;
			break;
		}

		this->GetResourceName( i, resName );
		resName.Trim();
		if ( name == resName )
		{
			result = i;
			break;
		}
	}

	return result;
}

MCObjectHandle VWResourceList::ImportResourceToCurrentFile(size_t index)
{
	MCObjectHandle	result = nullptr;
	if (fConflictCallback)
	{
		result = gSDK->ImportResourceToCurrentFileN(fResourceListID, Sint32(index+1), fConflictCallback, fenv);
	}
	else
	{
		result =gSDK->ImportResourceToCurrentFile(fResourceListID, Sint32(index+1));
	}

	return result;
}

static VectorWorks::EImportResourceConflictResult _ImportResourceToCurrentFile_DefaultCallback(TXString& inoutName, void* env)
{
	VectorWorks::EImportResourceConflictResult* theEnv = (VectorWorks::EImportResourceConflictResult*) env;
	return *theEnv;
}

MCObjectHandle VWResourceList::ImportResourceToCurrentFile(size_t index, VectorWorks::EImportResourceConflictResult resolveConflict)
{
	return gSDK->ImportResourceToCurrentFileN(fResourceListID, Sint32(index+1), _ImportResourceToCurrentFile_DefaultCallback, &resolveConflict);
}

