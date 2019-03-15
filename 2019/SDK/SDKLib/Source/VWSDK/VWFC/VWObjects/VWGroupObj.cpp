//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWGroupObj::VWGroupObj()
{
	fhObject		= ::GS_CreateGroup( gCBP );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create group" );
}

VWGroupObj::VWGroupObj(MCObjectHandle hGroup)
{
	VWFC_ASSERT( VWGroupObj::IsGroupLikeObject( hGroup ) );
	if ( ! VWGroupObj::IsGroupLikeObject( hGroup ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hGroup;
}

// this is constructor for inheritant of this class
// so this class will not create a new group but let the inheritant do that job
VWGroupObj::VWGroupObj(Sint32)
{
}

VWGroupObj::VWGroupObj(const VWGroupObj& src)
{
	fhObject	= src.fhObject;
}

VWGroupObj::~VWGroupObj()
{
}

VWGroupObj& VWGroupObj::operator=(const VWGroupObj& src)
{
	fhObject	= src.fhObject;
	return *this;
}

MCObjectHandle VWGroupObj::GroupSelection()
{
	return ::GS_GroupSelection( gCBP );
}

bool VWGroupObj::IsGroupObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN(hObj );
	return type == kGroupNode;
}

bool VWGroupObj::IsGroupLikeObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN(hObj );
	return	type == kGroupNode ||
			type == kLayerNode ||
			type == kSymbolNode ||
			type == kExtrudeNode ||
			type == kParametricNode ||
			type == kCSGTreeNode ||
			type == kSymDefNode ||
			type == kSweepNode;
}

void VWGroupObj::AddObject(MCObjectHandle hObj)
{
	VWFC_ASSERT( fhObject );
	::GS_AddObjectToContainer( gCBP, hObj, fhObject );
}

void VWGroupObj::DeleteAllInnerObjects(bool useUndo/* = false*/)
{
	VWFC_ASSERT( fhObject );

	bool canUseUndo = useUndo && gSDK->IsCurrentlyBuildingAnUndoEvent();

	VWObjectIterator	objectIterator = VWObjectIterator( ::GS_FirstMemberObj( gCBP, fhObject ) );

	while( *objectIterator ) {
		MCObjectHandle objDelete = *objectIterator;
		objectIterator++;

		if( canUseUndo && !setmember( gSDK->GetObjectTypeN( objDelete ), kUndoPlaceholderNode, kTermNode ) ) {
			gSDK->AddBeforeSwapObject( objDelete );
		}

		::GS_DeleteObject( gCBP, objDelete, canUseUndo );
	}
}

MCObjectHandle VWGroupObj::GetFirstMemberObject() const
{
	VWFC_ASSERT( fhObject );
	return ::GS_FirstMemberObj( gCBP, fhObject );
}

VWObjectIterator VWGroupObj::GetFirstMemberIterator() const
{
	VWFC_ASSERT( fhObject );
	return VWObjectIterator( ::GS_FirstMemberObj( gCBP, fhObject ) );
}

MCObjectHandle VWGroupObj::GetLastMemberObject() const
{
	VWFC_ASSERT( fhObject );
	return ::GS_LastMemberObj( gCBP, fhObject );
}

VWObjectIterator VWGroupObj::GetLastMemberIterator() const
{
	VWFC_ASSERT( fhObject );
	return VWObjectIterator( ::GS_LastMemberObj( gCBP, fhObject ) );
}

VWObjectIterator VWGroupObj::begin() const
{ 
	return VWObjectIterator( gSDK->FirstMemberObj( fhObject ) );
};

VWObjectIterator VWGroupObj::end() const
{
	return VWObjectIterator( gSDK->LastMemberObj( fhObject ) );
};

Boolean VWGroupObj::FindHandleDeep(MCObjectHandle hObj)
{
	VWFC_ASSERT( fhObject );
	MCObjectHandle		unused;
	return ::GS_FindHandleDeep( gCBP, hObj, fhObject, unused );
}

MCObjectHandle VWGroupObj::FindObject(short type, MCObjectHandle hAfter)
{
	MCObjectHandle result = NULL;

	MCObjectHandle h;
	if ( hAfter == NULL )
	{
		h = gSDK->FirstMemberObj( fhObject );
	}
	else
	{
		h = gSDK->NextObject( hAfter );
	}

	while( h && gSDK->GetObjectTypeN(h) != kTermNode )
	{
		if ( gSDK->GetObjectTypeN(h) == type )
		{
			result = h;
			break;
		}

		h = gSDK->NextObject( h );
	}

	return result;
}

void VWGroupObj::MoveObjectDeep(const VWPoint2D& offset)
{
	this->MoveDeepReq( fhObject, offset );
}

void VWGroupObj::Move3DObjectDeep(const VWPoint3D& offset)
{
	this->MoveDeepReq( fhObject, offset );
}

// set the specified transformation to all objects within this group
// and to all other going reqursively down the groups
void VWGroupObj::ApplyTransformDeep(const VWTransformMatrix& matrix)
{
	this->ApplyTransformDeepReq( fhObject, matrix );
}

void VWGroupObj::ApplyTransformDeepReq(MCObjectHandle hObject, const VWTransformMatrix& matrix)
{
	short	type	= gSDK->GetObjectTypeN(hObject );
	if ( type == kGroupNode ) {
		VWGroupObj			groupObj( hObject );
		VWObjectIterator	objectIterator( groupObj.GetFirstMemberObject() );
		while ( *objectIterator ) {
			this->ApplyTransformDeepReq( *objectIterator, matrix );
			objectIterator++;
		}
	}
	else if ( type != 0 ) {
		VWObject theObject( hObject );

		VWTransformMatrix objectMatrix;
		theObject.GetObjectMatrix( objectMatrix );
		objectMatrix		= objectMatrix * matrix;
		theObject.SetObjectMatrix( objectMatrix );
	}
}

void VWGroupObj::MoveDeepReq(MCObjectHandle hObject, const VWPoint2D& offset)
{
	short	type	= gSDK->GetObjectTypeN(hObject );
	if ( type == kGroupNode || type == kParametricNode ) {
		VWGroupObj			groupObj( hObject );
		VWObjectIterator	objectIterator( groupObj.GetFirstMemberObject() );
		while ( *objectIterator ) {
			this->MoveDeepReq( *objectIterator, offset );
			objectIterator++;
		}
	}
	else if ( type != 0 ) {
		VWObject theObject( hObject );

		theObject.MoveObject( offset );
	}
}


void VWGroupObj::MoveDeepReq(MCObjectHandle hObject, const VWPoint3D& offset)
{
	short	type	= gSDK->GetObjectTypeN(hObject );
	if ( type == kGroupNode ) {
		VWGroupObj			groupObj( hObject );
		VWObjectIterator	objectIterator( groupObj.GetFirstMemberObject() );
		while ( *objectIterator ) {
			this->MoveDeepReq( *objectIterator, offset );
			objectIterator++;
		}
	}
	else if ( type != 0 ) {
		VWObject theObject( hObject );

		theObject.MoveObject3D( offset );
	}
}

