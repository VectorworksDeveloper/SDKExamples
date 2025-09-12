//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		// gSDK->GetObjectByUUID is not optimized as it looks for the object doing a foreach.
		// This class provides a faster approach by caching the object's UUIDs with a single foreach.
		// This class should be used in a strict scope where it is certain that the cached handles will remain valid!
		// Make sure to always call Clear after you are done with the class so that it does not keep handles outside its scope.
		//
		// Sample use case assuming arrUUIDs is an array of UUIDs:
		//
		// CObjectUUIDSnapshot& uuidSnapshot = CObjectUUIDSnapshot::GetInstance();
		// uuidSnapshot.Rebuild( allDrawing );
		//
		// for ( const auto& uuid : arrUUIDs )
		// {
		//		MCObjectHandle hObject = uuidSnapshot.GetObjectByUUID_Fast( uuid );
		//		// Do stuff with the handle here
		// }
		// uuidSnapshot.Clear(); // Clear the cached data
		class CObjectUUIDSnapshot
		{
			public:
				// Get the class' instance using this function
				// That way you can use the class in function calls without passing it as an argument
				static CObjectUUIDSnapshot& GetInstance();

			private:
				CObjectUUIDSnapshot() = default;

			public:
				// Call this to take a snapshot of the object UUIDs.
				// This should be done in the begining of the scope/operation.
				// If we know that this is in a nested scope that already did the rebuild, we can pass useCache = true
				// and this will avoid the extra rebuild
				void			Rebuild(Sint16 traverseOptions, bool useCache = false);
				// Call this always at the end of the scope/operation to make sure
				// no handles are kept in the cache for too long.
				void			Clear();
				// Returns a handle by the given UUID by looking in the cache.
				// If the UUID is not in the cache it will try to find it with foreach.
				MCObjectHandle	GetObjectByUUID_Fast(const UuidStorage& u);

				// If we have a bigger scope that we know will use the UUIDCache multiple times in very deeply nested functions
				// and we know that we can do the cache only once at a top level of the scope we can allow the nesting
				// from this top level and make the deeper levels just use this global cache that should be safe.
				// Clear will not work when nesting is allowed, so always disable nesting in the global scope before doing the clear!
				void			SetAllowNesting(bool allowNesting);

				// Quick add and remove of data from the snapshot, in case we know that a new object was created
				// or an existing one was deleted.
				void			AddObject(MCObjectHandle hObject);
				void			RemoveUUID(const UuidStorage& uuid);

			private:
				std::unordered_map<UuidStorage, MCObjectHandle>	fmapUIDToHandle;
				Sint16											fNestingLevel = 0;
		};
	}
}
