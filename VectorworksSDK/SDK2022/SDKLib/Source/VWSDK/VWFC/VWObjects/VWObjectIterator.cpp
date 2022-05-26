//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::VWObjects;

VWObjectIterator::VWObjectIterator(MCObjectHandle hObj)
{
	fhObject	= hObj;
}

VWObjectIterator::~VWObjectIterator()
{
}

bool VWObjectIterator::operator==(const VWObjectIterator& src) const
{
	return fhObject && fhObject == src.fhObject;
}

bool VWObjectIterator::operator!=(const VWObjectIterator& src) const
{
	return fhObject && fhObject != src.fhObject;
}

MCObjectHandle VWObjectIterator::MoveNext()
{
	VWFC_ASSERT( fhObject );
	fhObject	= ::GS_NextObject( gCBP, fhObject );
	if ( gSDK->GetObjectTypeN(fhObject) == kTermNode )
		fhObject = nullptr;
	return fhObject;
}

MCObjectHandle VWObjectIterator::MoveNextSelected()
{
	MCObjectHandle	hNextObj	= nil;
	do
	{
		hNextObj	= this->MoveNext();
	} while ( hNextObj && ! ::GS_IsSelected( gCBP, hNextObj ) );
	return hNextObj;
}

MCObjectHandle VWObjectIterator::MovePrev()
{
	VWFC_ASSERT( fhObject );
	fhObject	= ::GS_PrevObject( gCBP, fhObject );
	return fhObject;
}

MCObjectHandle VWObjectIterator::MovePrevSelected()
{
	MCObjectHandle	hNextObj	= nil;
	do
	{
		hNextObj	= this->MovePrev();
	} while ( hNextObj && ! ::GS_IsSelected( gCBP, hNextObj ) );
	return hNextObj;
}

MCObjectHandle VWObjectIterator::GetObject() const
{
	return fhObject;
}

MCObjectHandle VWObjectIterator::operator++()
{
	return this->MoveNext();
}

MCObjectHandle VWObjectIterator::operator++(Sint32)
{
	return this->MoveNext();
}

MCObjectHandle VWObjectIterator::operator--()
{
	return this->MovePrev();
}

MCObjectHandle VWObjectIterator::operator--(Sint32)
{
	return this->MovePrev();
}

MCObjectHandle VWObjectIterator::operator*() const
{
	return fhObject;
}

VWObjectIterator::operator MCObjectHandle() const
{
	return fhObject;
}

VWObjectIterator::operator bool() const
{
	return fhObject && gSDK->GetObjectTypeN(fhObject) != kTermNode;
}

MCObjectHandle VWObjectIterator::NextObject(MCObjectHandle hObj)
{
	MCObjectHandle result = ::GS_NextObject( gCBP, hObj );
	if ( gSDK->GetObjectTypeN(result) == kTermNode )
		result = nullptr;
	return result;
}

MCObjectHandle VWObjectIterator::PrevObject(MCObjectHandle hObj)
{
	return ::GS_PrevObject( gCBP, hObj );
}

MCObjectHandle VWObjectIterator::NextSelectedObject(MCObjectHandle hObj)
{
	do {
		hObj	= ::GS_NextObject( gCBP, hObj );
		if ( gSDK->GetObjectTypeN(hObj) == kTermNode )
			hObj = nullptr;
	} while ( hObj && ! ::GS_IsSelected( gCBP, hObj ) );
	return hObj;
}

MCObjectHandle VWObjectIterator::PrevSelectedObject(MCObjectHandle hObj)
{
	do {
		hObj	= ::GS_PrevObject( gCBP, hObj );
	} while ( hObj && ! ::GS_IsSelected( gCBP, hObj ) );
	return hObj;
}

short VWObjectIterator::GetType() const
{
	return gSDK->GetObjectTypeN( fhObject );
}
