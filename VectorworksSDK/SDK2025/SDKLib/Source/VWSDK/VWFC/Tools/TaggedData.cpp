//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"


using namespace VWFC::Tools;
using namespace VWFC::Math;

// ---------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------
CTaggedDataContainer::CTaggedDataContainer(MCObjectHandle hOwnerObj, Uint32 id)
{
	fhOwnerObj	= hOwnerObj;
	fID			= id;
}

CTaggedDataContainer::CTaggedDataContainer(const CTaggedDataContainer& src)
{
	this->operator = ( src );
}

CTaggedDataContainer::~CTaggedDataContainer()
{
}

CTaggedDataContainer& CTaggedDataContainer::operator=(const CTaggedDataContainer& src)
{
	fhOwnerObj	= src.fhOwnerObj;
	fID			= src.fID;

	return *this;
}

void CTaggedDataContainer::Clear()
{
	::GS_TaggedDataRemoveContainer( gCBP, fhOwnerObj, fID );
}

CTaggedDataTag CTaggedDataContainer::CreateTagUint8(TTaggedDataTagID id, size_t count)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_Byte, id, count ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_Byte, id );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::CreateTagSint8(TTaggedDataTagID id, size_t count)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_Byte, id, count ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_Byte, id );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::CreateTagUint16(TTaggedDataTagID id, size_t count)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_Integer, id, count ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_Integer, id );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::CreateTagSint16(TTaggedDataTagID id, size_t count)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_Integer, id, count ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_Integer, id );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::CreateTagUint32(TTaggedDataTagID id, size_t count)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_Integer, id, count ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_Integer, id );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::CreateTagSint32(TTaggedDataTagID id, size_t count)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_Integer, id, count ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_Integer, id );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::CreateTagReal(TTaggedDataTagID id, size_t count)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_Real, id, count ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_Real, id );
	}

	return tag;
}

CTaggedDataTag	CTaggedDataContainer::CreateTagColor(TTaggedDataTagID id, size_t count)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_ColorRef, id, count ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_ColorRef, id );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::CreateTagString(TTaggedDataTagID id, const TXString& value)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_Byte, id, value.GetByteSize() + sizeof(UCChar) ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_Byte, id );
		tag.SetValueString( value );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::CreateTagMatrix(TTaggedDataTagID id,  const VWFC::Math::VWTransformMatrix& value)
{
	CTaggedDataTag	tag;
	if ( ::GS_TaggedDataCreate( gCBP, fhOwnerObj, fID, eTaggedDataType_Matrix, id, 1 ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_Matrix, id );
		tag.SetValueMatrix( value );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::CreateTagInternalIndex(TTaggedDataTagID id, size_t count)
{
	CTaggedDataTag	tag;
	if ( gSDK->TaggedDataCreate( fhOwnerObj, fID, eTaggedDataType_InternalIndex, id, (Sint32)count ) ) {
		tag.Set( fhOwnerObj, fID, eTaggedDataType_InternalIndex, id );
	}

	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagUint8(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_Byte, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagSint8(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_Byte, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagUint16(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_Integer, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagSint16(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_Integer, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagUint32(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_Integer, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagSint32(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_Integer, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagReal(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_Real, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagColor(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_ColorRef, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagString(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_Byte, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagMatrix(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_Matrix, id );
	return tag;
}

CTaggedDataTag CTaggedDataContainer::GetTagInternalIndex(TTaggedDataTagID id)
{
	CTaggedDataTag	tag;
	tag.Set( fhOwnerObj, fID, eTaggedDataType_InternalIndex, id );
	return tag;
}

// ---------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------
CTaggedDataTag::CTaggedDataTag()
{
	fhOwnerObj		= 0;
	fOwnerID		= 0;
	fType			= ETaggedDataType( 0 );
	fId				= 0;
}

void CTaggedDataTag::Set(MCObjectHandle hOwnerObj, OSType ownerID, ETaggedDataType type, TTaggedDataTagID id)
{
	fhOwnerObj		= hOwnerObj;
	fOwnerID		= ownerID;
	fType			= type;
	fId				= id;
}

CTaggedDataTag::CTaggedDataTag(const CTaggedDataTag& src)
{
	this->operator = ( src );
}

CTaggedDataTag::~CTaggedDataTag()
{
}

CTaggedDataTag& CTaggedDataTag::operator=(const CTaggedDataTag& src)
{
	fhOwnerObj		= src.fhOwnerObj;
	fOwnerID		= src.fOwnerID;
	fType			= src.fType;
	fId				= src.fId;
	return *this;
}

bool CTaggedDataTag::IsValid() const
{
	return fhOwnerObj != NULL;
}

TTaggedDataTagID CTaggedDataTag::GetID() const
{
	return fId;
}

ETaggedDataType CTaggedDataTag::GetType() const
{
	return fType;
}

size_t CTaggedDataTag::GetValuesCount() const
{
	size_t	result		= 0;
	if ( fhOwnerObj ) {
		if ( 
				fType == eTaggedDataType_Byte
			||	fType == eTaggedDataType_Integer
			||	fType == eTaggedDataType_Real
			||	fType == eTaggedDataType_ColorRef
			||  fType == eTaggedDataType_InternalIndex
			)
		{
			Sint32	dataLen		= 0;
			if ( ::GS_TaggedDataGetNumElements( gCBP, fhOwnerObj, fOwnerID, fType, fId, & dataLen ) ) { 
				result	= size_t( dataLen ); 
			}
		}
		else {
			// the type is not array
			VWFC_ASSERT( false );
		}
	}

	return result;
}


void CTaggedDataTag::SetValueUint8(size_t index, Uint8 value)
{
	VWFC_VERIFY( ::GS_TaggedDataSet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Byte, fId, index, & value ) );
}

Uint8 CTaggedDataTag::GetValueUint8(size_t index) const
{
	Uint8	result	= 0;
	
	Uint8*	pData	= nullptr;
	if ( gSDK->TaggedDataGet( fhOwnerObj, fOwnerID, eTaggedDataType_Byte, fId, (Sint32)index, & pData ) ) {
		result	= *pData;
	}
	return result;
}

void CTaggedDataTag::SetValueSint8(size_t index, Sint8 value)
{
	VWFC_VERIFY( ::GS_TaggedDataSet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Byte, fId, index, & value ) );
}

Sint8 CTaggedDataTag::GetValueSint8(size_t index) const
{
	Sint8	result	= 0;
	
	Sint8*	pData	= nullptr;
	if ( gSDK->TaggedDataGet( fhOwnerObj, fOwnerID, eTaggedDataType_Byte, fId, (Sint32)index, & pData ) ) {
		result	= *pData;
	}
	return result;
}

void CTaggedDataTag::SetValueUint16(size_t index, Uint16 value)
{
	Uint32	value32b = value;
	VWFC_VERIFY( ::GS_TaggedDataSet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Integer, fId, index, & value32b ) );
}

Uint16 CTaggedDataTag::GetValueUint16(size_t index) const
{
	Uint16	result	= 0;
	
	Uint16*	pData	= nullptr;
	if ( gSDK->TaggedDataGet( fhOwnerObj, fOwnerID, eTaggedDataType_Integer, fId, (Sint32)index, & pData ) ) {
		result	= *pData;
	}
	return result;
}

void CTaggedDataTag::SetValueSint16(size_t index, Sint16 value)
{
	Sint32	value32b = value;
	VWFC_VERIFY( ::GS_TaggedDataSet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Integer, fId, index, & value32b ) );
}

Sint16 CTaggedDataTag::GetValueSint16(size_t index) const
{
	Sint16	result	= 0;
	
	Sint16*	pData	= nullptr;
	if ( gSDK->TaggedDataGet( fhOwnerObj, fOwnerID, eTaggedDataType_Integer, fId, (Sint32)index, & pData ) ) {
		result	= *pData;
	}
	return result;
}

void CTaggedDataTag::SetValueUint32(size_t index, Uint32 value)
{
	VWFC_VERIFY( ::GS_TaggedDataSet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Integer, fId, index, & value ) );
}

Uint32 CTaggedDataTag::GetValueUint32(size_t index) const
{
	Uint32	result	= 0;
	
	Uint32*	pData	= nullptr;
	if ( gSDK->TaggedDataGet( fhOwnerObj, fOwnerID, eTaggedDataType_Integer, fId, (Sint32)index, & pData ) ) {
		result	= *pData;
	}
	return result;
}

void CTaggedDataTag::SetValueSint32(size_t index, Sint32 value)
{
	VWFC_VERIFY( ::GS_TaggedDataSet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Integer, fId, index, & value ) );
}

Sint32 CTaggedDataTag::GetValueSint32(size_t index) const
{
	Sint32	result	= 0;
	
	Sint32*	pData	= nullptr;
	if ( gSDK->TaggedDataGet( fhOwnerObj, fOwnerID, eTaggedDataType_Integer, fId, (Sint32)index, & pData ) ) {
		result	= *pData;
	}
	return result;
}

double CTaggedDataTag::GetValueReal(size_t index) const
{
	double	result	= 0;
	
	double*	pData	= nullptr;
	if ( gSDK->TaggedDataGet( fhOwnerObj, fOwnerID, eTaggedDataType_Real, fId, (Sint32)index, & pData ) ) {
		result	= *pData;
	}
	return result;
}

void CTaggedDataTag::SetValueReal(size_t index, double value)
{
	VWFC_VERIFY( ::GS_TaggedDataSet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Real, fId, index, & value ) );
}

ColorRef CTaggedDataTag::GetValueColorRef(size_t index) const
{
	ColorRef	result	= 0;
	
	ColorRef*	pData	= nullptr;
	if ( gSDK->TaggedDataGet( fhOwnerObj, fOwnerID, eTaggedDataType_ColorRef, fId, (Sint32)index, & pData ) ) {
		result	= *pData;
	}
	return result;
}

void CTaggedDataTag::SetValueColorRef(size_t index, ColorRef value)
{
	VWFC_VERIFY( ::GS_TaggedDataSet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_ColorRef, fId, index, & value ) );
}

TXString CTaggedDataTag::GetValueString() const
{
	TXString	result;

	if ( fType == eTaggedDataType_Byte ) {
		size_t		dataCnt	= this->GetValuesCount();

		Uint8*		pData	= NULL;
		if ( dataCnt > 0 && ::GS_TaggedDataGet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Byte, fId, 0, & pData ) ) { 
			result = TXString( (const UCChar*)pData, dataCnt / sizeof(UCChar) - 1 );
		}
	}

	return result;
}

void CTaggedDataTag::SetValueString(const TXString& value)
{
	if ( fType == eTaggedDataType_Byte ) {
		size_t		dataCnt	= this->GetValuesCount();

		TXString	theValue	= value;

		Uint8*	pData	= NULL;
		if ( ::GS_TaggedDataGet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Byte, fId, 0, & pData ) ) { 
			VWFC_ASSERT( theValue.GetByteSize() + sizeof(UCChar) <= dataCnt );
			theValue.CopyInto( (UCChar*) pData, (dataCnt / sizeof(UCChar)) );
		}
	}
}

VWTransformMatrix CTaggedDataTag::GetValueMatrix() const
{
	VWTransformMatrix	result;
	if ( fType == eTaggedDataType_Matrix ) {
		TransformMatrix*	pData	= NULL;
		if ( ::GS_TaggedDataGet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Matrix, fId, 0, & pData ) ) { 
			result	= *pData;
		}
	}

	return result;
}

void CTaggedDataTag::SetValueMatrix(const VWTransformMatrix& value)
{
	if ( fType == eTaggedDataType_Matrix ) {
		TransformMatrix	data	= value;
		VWFC_VERIFY( ::GS_TaggedDataSet( gCBP, fhOwnerObj, fOwnerID, eTaggedDataType_Matrix, fId, 0, & data ) ); 
	}
}

InternalIndex CTaggedDataTag::GetValueInternalIndex(size_t index) const
{
	InternalIndex	result	= -1;

	InternalIndex*	pData	= NULL;
	if ( gSDK->TaggedDataGet( fhOwnerObj, fOwnerID, eTaggedDataType_InternalIndex, fId, (Sint32)index, & pData ) ) {
		result	= *pData;
	}
	
	return result;
}

void CTaggedDataTag::SetValueInternalIndex(size_t index, InternalIndex value)
{
	VWFC_VERIFY( gSDK->TaggedDataSet( fhOwnerObj, fOwnerID, eTaggedDataType_InternalIndex, fId, (Sint32)index, & value ) );
}




