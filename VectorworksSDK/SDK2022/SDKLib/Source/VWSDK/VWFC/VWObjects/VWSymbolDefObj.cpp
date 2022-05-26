//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"


using namespace VWFC::VWObjects;

VWSymbolDefObj::VWSymbolDefObj(const TXString& symDefName)
: VWGroupObj( 0 )	// call nothing doing constructor -- we dont want a new group created
{
	fhObject		= NULL;

	fhObject	= ::GS_GetNamedObject( gCBP, symDefName );
	if ( ! VWSymbolDefObj::IsSymbolDefObject( fhObject ) ) {
		fhObject	= ::GS_CreateSymbolDefinition( gCBP, symDefName );
	}

	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create symbol def" );
}

VWSymbolDefObj::VWSymbolDefObj(MCObjectHandle hSymbolDef)
: VWGroupObj( 0 )	// call nothing doing constructor -- we dont want a new group created
{
	VWFC_ASSERT( VWSymbolDefObj::IsSymbolDefObject( hSymbolDef ) );
	if ( ! VWSymbolDefObj::IsSymbolDefObject( hSymbolDef ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject	= hSymbolDef;
	VWFC_ASSERT( fhObject );
}

VWSymbolDefObj::VWSymbolDefObj(const VWSymbolDefObj& src)
{
	fhObject	= src.fhObject;
	VWFC_ASSERT( fhObject );
}

VWSymbolDefObj::~VWSymbolDefObj()
{
}

VWSymbolDefObj& VWSymbolDefObj::operator=(const VWSymbolDefObj& src)
{
	fhObject = src.fhObject;
	return *this;
}

bool VWSymbolDefObj::IsSymbolDefObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kSymDefNode;
}

bool VWSymbolDefObj::IsSymbolDefObject(const TXString& symDefName)
{
	MCObjectHandle	hSymbolDef	= ::GS_GetNamedObject( gCBP, symDefName );
	return VWSymbolDefObj::IsSymbolDefObject( hSymbolDef );
}

void VWSymbolDefObj::SetAsActiveSymbolDef()
{
	::GS_SetActiveSymbolDef( gCBP, fhObject );
}

MCObjectHandle VWSymbolDefObj::GetActiveSymbolDef()
{
	return ::GS_GetActiveSymbolDef( gCBP );
}

ESymbolDefType VWSymbolDefObj::GetType() const
{
	return (ESymbolDefType) ::GS_GetSymbolDefinitionType( gCBP, fhObject );
}

bool VWSymbolDefObj::IsContainingLight() const
{
	return ::GS_SymbolContainsLight( gCBP, fhObject ) ? true : false;
}

ESymbolInsertMode VWSymbolDefObj::GetInsertMode() const
{
	TVariableBlock	value;
	VWFC_VERIFY( ::GS_GetObjectVariable( gCBP, fhObject, ovSymDefInsertMode, value ) );

	short			mode;
	VWFC_VERIFY( value.GetSint16( mode ) );
	return (ESymbolInsertMode) mode;
}

void VWSymbolDefObj::SetInsertMode(ESymbolInsertMode mode)
{
	TVariableBlock	value( (short) mode );
	VWFC_VERIFY( ::GS_SetObjectVariable( gCBP, fhObject, ovSymDefInsertMode, value ) );
}

ESymbolBreakMode VWSymbolDefObj::GetBreakMode() const
{
	TVariableBlock	value;
	VWFC_VERIFY( ::GS_GetObjectVariable( gCBP, fhObject, ovSymDefBreakMode, value ) );

	short			mode;
	VWFC_VERIFY( value.GetSint16( mode ) );
	return (ESymbolBreakMode) mode;
}

void VWSymbolDefObj::SetBreakMode(ESymbolBreakMode mode)
{
	TVariableBlock	value( (short) mode );
	VWFC_VERIFY( ::GS_SetObjectVariable( gCBP, fhObject, ovSymDefBreakMode, value ) );
}

bool VWSymbolDefObj::GetInsertAsGroup() const
{
	TVariableBlock		value;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSymbolInsertAsGroup, value ) );
	Boolean				result;
	VERIFYN( kVStanev, value.GetBoolean( result ) );

	return result ? true : false;
}

void VWSymbolDefObj::SetInsertAsGroup(bool bInsertAsGroup)
{
	TVariableBlock		value( (Boolean) bInsertAsGroup );
	VERIFYN( kVStanev, ::GS_SetObjectVariable( gCBP, fhObject, ovSymbolInsertAsGroup, value ) );
}

VWGroupObj VWSymbolDefObj::GetSymbolGroup() const
{
	VWGroupObj			resultGroup;

	VWObjectIterator	it	= this->GetFirstMemberIterator();
	while( *it ) {
		MCObjectHandle	hCopyObj	= ::GS_DuplicateObject( gCBP, *it );
		short	type	= gSDK->GetObjectTypeN( hCopyObj );
		if (type != termNode){
			resultGroup.AddObject( hCopyObj );
		}

		it++;
	}

	return resultGroup;
}

//////////////////////////////////////////////////////////////////////////////////
bool VWSymbolDefObj::HasPluginStyleSupport() const
{
	Sint32 subType = gSDK->GetSymbolDefSubType( fhObject );
	return subType > 0;
}

TInternalID	VWSymbolDefObj::PluginStyleObjectID() const
{
	TInternalID id 	= gSDK->GetSymbolDefSubType( fhObject );
	return id;
}

