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

void CObjectUUIDSnapshot::Rebuild(Sint16 traverseOptions)
{
	fmapUIDToHandle.clear();

	gSDK->ForEachObjectN( traverseOptions, [ this ] (MCObjectHandle h)
	{
		UuidStorage uid;
		gSDK->GetObjectUuidN( h, uid );

		fmapUIDToHandle[ uid ] = h;
	} );
}

void CObjectUUIDSnapshot::Clear()
{
	fmapUIDToHandle.clear();
}

MCObjectHandle CObjectUUIDSnapshot::GetObjectByUUID_Fast(const UuidStorage& u)
{
	MCObjectHandle	hObject	= nullptr;
	auto			entry	= fmapUIDToHandle.find( u );

	if ( entry != fmapUIDToHandle.end() )
	{
		// UUID found in the cache
		hObject = entry->second;
	}
	else
	{
		// UUID not found in the cache 
		hObject = gSDK->GetObjectByUuidN( u );

		if ( hObject != nullptr )
		{
			// For further optimization cache the missing uuid
			fmapUIDToHandle[ u ] = hObject;
		}
	}

	return hObject;
}
