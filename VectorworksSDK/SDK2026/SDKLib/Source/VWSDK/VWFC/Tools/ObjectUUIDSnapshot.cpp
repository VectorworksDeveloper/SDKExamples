//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

using namespace VWFC::Tools;

/*static*/CObjectUUIDSnapshot& CObjectUUIDSnapshot::GetInstance()
{
	static CObjectUUIDSnapshot instance;

	return instance;
}

void CObjectUUIDSnapshot::Rebuild(Sint16 traverseOptions, bool useCache/* = false*/)
{
	bool rebuild = fmapUIDToHandle.empty() || !useCache || fNestingLevel == 0;

	if ( rebuild )
	{
		fmapUIDToHandle.clear();

		gSDK->ForEachObjectN( traverseOptions, [ this ] ( MCObjectHandle h )
		{
			UuidStorage uid;
			gSDK->GetObjectUuidN( h, uid );

			fmapUIDToHandle[ uid ] = h;
		} );
	}
}

void CObjectUUIDSnapshot::Clear()
{
	// Do not clear the cache when nesting is allowed, as this should be done from the top most scope
	if ( fNestingLevel == 0 )
	{
		fmapUIDToHandle.clear();
	}
}

MCObjectHandle CObjectUUIDSnapshot::GetObjectByUUID_Fast(const UuidStorage& u)
{
	MCObjectHandle	hObject	= nullptr;
	auto			entry	= fmapUIDToHandle.find( u );

	if ( entry != fmapUIDToHandle.end() )
	{
		// UUID found in the cache
		hObject = entry->second;

#if BUG
		UuidStorage objectUUID;
		gSDK->GetObjectUuidN( hObject, objectUUID );

		DSTOPIF( objectUUID != u, ( kNZhelyazkov, "Cached UUID does not match the object's UUID!\n" ) );
#endif
	}
	else
	{
		if ( !u.IsEmpty() )
		{
			// UUID not found in the cache 
			hObject = gSDK->GetObjectByUuidN( u );
		}

		DSTOPIF( hObject != nullptr, ( kNZhelyazkov, "Handle was not cached in the snapshot, possible incorrect usage of the class!\n" ) );

		// For further optimization cache the missing uuid, even if it is to nullptr
		fmapUIDToHandle[ u ] = hObject;
	}

	return hObject;
}

void CObjectUUIDSnapshot::SetAllowNesting(bool allowNesting)
{
	if ( !allowNesting )
	{
		--fNestingLevel;

		if ( !VERIFYN( kNZhelyazkov, fNestingLevel >= 0 ) )
		{
			fNestingLevel = 0;
		}
	}
	else
	{
		++fNestingLevel;

		DSTOPIF( fNestingLevel > 4, ( kNZhelyazkov, "The nesting of the UUID snapshot is getting too big, check if this can be optimized!\n" ) );
	}
}

void CObjectUUIDSnapshot::AddObject(MCObjectHandle hObject)
{
	UuidStorage uid;
	gSDK->GetObjectUuidN( hObject, uid );

	fmapUIDToHandle[ uid ] = hObject;
}

void CObjectUUIDSnapshot::RemoveUUID(const UuidStorage& uuid)
{
	fmapUIDToHandle.erase( uuid );
}
