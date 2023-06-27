//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VectorWorks::Filing;


VWDataSerializerSimple::VWDataSerializerSimple()
	: fSerializer( NULL )
	, fhObject( NULL )
	, fLoaded( false )
	, fDataTag( 0 )
{
}

VWDataSerializerSimple::VWDataSerializerSimple(MCObjectHandle h, Uint32/*FourCharCode*/ category)
	: fSerializer( NULL )
	, fhObject( h )
	, fLoaded( false )
	, fDataTag( category )
{
}

VWDataSerializerSimple::VWDataSerializerSimple(const VWDataSerializerSimple& src)
	: fSerializer( NULL )
	, fhObject( src.fhObject )
	, fLoaded( false )
	, fDataTag( src.fDataTag )
{
}

VWDataSerializerSimple::~VWDataSerializerSimple()
{
}

VWDataSerializerSimple& VWDataSerializerSimple::operator=(const VWDataSerializerSimple&)
	// hidden, use the copy constructor instead
{
	return *this;
}

VWDataSerializer& VWDataSerializerSimple::GetSerializer()
{
	return fSerializer;
}

bool VWDataSerializerSimple::Load()
{
	fLoaded = false;

	GSHandle	hDataObj	= (GSHandle) gSDK->FindDataObject( fhObject, fDataTag );
	if ( hDataObj )
	{
		size_t handleSize;
		gSDK->GSGetHandleSize( hDataObj, handleSize );

		char*	pDataMemory		= *hDataObj;
		// offset the reserved data so it will point to the actually data
		pDataMemory				+= kUserDataTypeSize;
		handleSize				-= kUserDataTypeSize;

		if ( handleSize > 0 )
		{
			fLoaded = fSerializer.ReadDataFromMemory( pDataMemory, handleSize );
		}
	}

	return fLoaded;
}

bool VWDataSerializerSimple::IsLoaded() const
{
	return fLoaded;
}

bool VWDataSerializerSimple::Save(bool undo)
{
	bool result = false;

	// first delete data if exist
	MCObjectHandle	hDataObj		= NULL;
	do {
		hDataObj	= gSDK->FindDataObject( fhObject, fDataTag );
		if(hDataObj)
		{
			if ( undo )
			{
				gSDK->AddBeforeSwapObject( hDataObj );
				gSDK->DeleteObject( hDataObj );
			}
			else
				gSDK->DeleteAuxObject( hDataObj , fhObject);
		}
	} while ( hDataObj );

	// create new data
	size_t	dataSize	= fSerializer.GetDataBytesCount() + kUserDataTypeSize;
	hDataObj			= gSDK->NewDataObject( fhObject, fDataTag, dataSize );
	if ( hDataObj ) {
		char* pDataMemory	= *(char**)hDataObj;
		// offset the data to the actual data
		pDataMemory			+= kUserDataTypeSize;

		fSerializer.SaveDataInMemory( pDataMemory );
		result		= true;		

		if ( undo ) gSDK->AddAfterSwapObject( hDataObj );
	}

	return result;
}

void VWDataSerializerSimple::Clear()
{
	if ( fLoaded )
	{
		fSerializer.ClearChildGroups();
	}
}

size_t VWDataSerializerSimple::GetGroupCount()
{
	if ( fLoaded ) {
		return fSerializer.GetChildGroupsCount();
	}
	else {
		return 0;
	}
}

size_t VWDataSerializerSimple::GetChildGroupCount(const GroupID& groupID)
{
	if ( fLoaded )
	{
		VWDataSerializerGroup* dataGroup = this->GetGroup( groupID );
		if ( dataGroup )
		{
			return dataGroup->GetChildGroupsCount();
		}
	}

	return 0;
}

void VWDataSerializerSimple::ClearChildGroups(const GroupID& groupID)
{
	VWDataSerializerGroup* dataGroup	= this->GetGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->ClearChildGroups();
	}
}

VWDataSerializerGroup* VWDataSerializerSimple::GetGroup(const GroupID& groupID) const
{
	VWDataSerializerGroup* dataGroup = NULL;

	if ( groupID.groupID_level1 != TDataIdentifier(-1) )
	{
		dataGroup = fSerializer.FindChildDataGroup( groupID.groupID_level1, NULL );
		if ( dataGroup )
		{
			if ( groupID.groupID_level2 != TDataIdentifier(-1) )
			{
				VWDataSerializerGroup*	dataGroup2 = dataGroup->FindChildDataGroup( groupID.groupID_level2, NULL );
				dataGroup = dataGroup2;
			}
		}
	}

	return dataGroup;
}

void VWDataSerializerSimple::ReadLocal(VWDataSerializer::IReadContext* context) const
{
	GSHandle	hDataObj	= (GSHandle) gSDK->FindDataObject( fhObject, fDataTag );
	if ( hDataObj )
	{
		size_t handleSize;
		gSDK->GSGetHandleSize( hDataObj, handleSize );

		char*	pDataMemory		= *hDataObj;
		// offset the reserved data so it will point to the actually data
		pDataMemory				+= kUserDataTypeSize;
		handleSize				-= kUserDataTypeSize;

		if ( handleSize > 0 )
		{
			fSerializer.ReadDataFromMemory( pDataMemory, handleSize, context );
		}
	}
}

bool VWDataSerializerSimple::HasValue(const GroupID& groupID, size_t valueIndex) const
{
	bool result = false;
	if ( fLoaded )
	{
		VWDataSerializerGroup* dataGroup = this->GetGroup( groupID );
		if ( dataGroup )
		{
			result = dataGroup->HasValue( valueIndex, NULL );
		}
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		result	= reader.HasValue();
	}

	return result;
}

template <typename T>
static inline T GetValueNumeric(VWDataSerializerGroup* dataGroup, size_t valueIndex, const T& defaultValue)
{
	T	result	= defaultValue;

	if ( dataGroup )
	{
		VWDataSerializerValue	value( dataGroup->GetContext(), result );
		if ( dataGroup->GetValue( valueIndex, nullptr, value ) )
		{
			result	= value;
		}
	}

	return result;
}

template <typename T>
static inline bool GetValueOutNumeric(VWDataSerializerGroup* dataGroup, size_t valueIndex, T& outValue)
{
	bool	resultOk	= false;

	if ( dataGroup )
	{
		VWDataSerializerValue	value( dataGroup->GetContext(), outValue );
		if ( dataGroup->GetValue( valueIndex, nullptr, value ) )
		{
			outValue	= value;
			resultOk	= true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueBool(const GroupID& groupID, size_t valueIndex, bool defaultValue) const
{
	bool result = defaultValue;
	if ( fLoaded )
	{
		result	= GetValueNumeric<Uint8>( this->GetGroup( groupID ), valueIndex, defaultValue ? 1u : 0u ) != 0u;
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Uint8 ) ) )
		{
			result = reader.GetValue()->operator Uint8() ? true : false;
		}
	}

	return result;
}

Sint8 VWDataSerializerSimple::GetValueSint8(const GroupID& groupID, size_t valueIndex, Sint8 defaultValue) const
{
	Sint8 result = defaultValue;
	if ( fLoaded )
	{
		result	= GetValueNumeric<Sint8>( this->GetGroup( groupID ), valueIndex, defaultValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Sint8 ) ) )
		{
			result = reader.GetValue()->operator Sint8();
		}
	}

	return result;
}

Uint8 VWDataSerializerSimple::GetValueUint8(const GroupID& groupID, size_t valueIndex, Uint8 defaultValue) const
{
	Uint8 result = defaultValue;
	if ( fLoaded )
	{
		result	= GetValueNumeric<Uint8>( this->GetGroup( groupID ), valueIndex, defaultValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue(  sizeof( Uint8 ) ) )
		{
			result = reader.GetValue()->operator Uint8();
		}
	}

	return result;
}

Sint16 VWDataSerializerSimple::GetValueSint16(const GroupID& groupID, size_t valueIndex, Sint16 defaultValue) const
{
	Sint16 result = defaultValue;
	if ( fLoaded )
	{
		result	= GetValueNumeric<Sint16>( this->GetGroup( groupID ), valueIndex, defaultValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Sint16 ) ) )
		{
			result = reader.GetValue()->operator Sint16();
		}
	}

	return result;
}

Uint16 VWDataSerializerSimple::GetValueUint16(const GroupID& groupID, size_t valueIndex, Uint16 defaultValue) const
{
	Uint16 result = defaultValue;
	if ( fLoaded )
	{
		result	= GetValueNumeric<Uint16>( this->GetGroup( groupID ), valueIndex, defaultValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Uint16 ) ) )
		{
			result = reader.GetValue()->operator Uint16();
		}
	}

	return result;
}

Sint32 VWDataSerializerSimple::GetValueSint32(const GroupID& groupID, size_t valueIndex, Sint32 defaultValue) const
{
	Sint32 result = defaultValue;
	if ( fLoaded )
	{
		result	= GetValueNumeric<Sint32>( this->GetGroup( groupID ), valueIndex, defaultValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Sint32 ) ) )
		{
			result = reader.GetValue()->operator Sint32();
		}
	}

	return result;
}

Uint32 VWDataSerializerSimple::GetValueUint32(const GroupID& groupID, size_t valueIndex, Uint32 defaultValue) const
{
	Uint32 result = defaultValue;
	if ( fLoaded )
	{
		result	= GetValueNumeric<Uint32>( this->GetGroup( groupID ), valueIndex, defaultValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Uint32 ) ) )
		{
			result = reader.GetValue()->operator Uint32();
		}
	}

	return result;
}

size_t VWDataSerializerSimple::GetValueSizeT(const GroupID& groupID, size_t valueIndex, size_t defaultValue) const
{
	size_t result = defaultValue;
	if ( fLoaded )
	{
		VWDataSerializerGroup*	dataGroup = this->GetGroup( groupID );
		if ( dataGroup )
		{
			VWDataSerializerValue	value( dataGroup->GetContext(), (Sint32) 0 );
			if ( dataGroup->GetValue( valueIndex, nullptr, value ) )
			{
				Uint64	theValue = 0;
				value.CopyInto( &theValue, sizeof( theValue ) );
				result = size_t( theValue );
				ASSERTN( kVStanev, Uint64( result ) == theValue );
			}
		}
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Uint64 ) ) )
		{
			Uint64	theValue = 0;
			reader.GetValue()->CopyInto( & theValue, sizeof(theValue) );
			result = size_t( theValue );
			ASSERTN( kVStanev, Uint64(result) == theValue );
		}
	}

	return result;
}

double VWDataSerializerSimple::GetValueDouble(const GroupID& groupID, size_t valueIndex, double defaultValue) const
{
	double result = defaultValue;
	if ( fLoaded )
	{
		result	= GetValueNumeric<double>( this->GetGroup( groupID ), valueIndex, defaultValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof(double) ) )
		{
			result = reader.GetValue()->operator double();
		}
	}

	return result;
}

TXString VWDataSerializerSimple::GetValueTXString(const GroupID& groupID, size_t valueIndex, const TXString& defaultValue) const
{
	TXString result = defaultValue;
	if ( fLoaded )
	{
		VWDataSerializerGroup* dataGroup = this->GetGroup( groupID );
		if ( dataGroup )
		{
			VWDataSerializerValue	value( dataGroup->GetContext(), result );
			if ( dataGroup->GetValue( valueIndex, nullptr, value ) )
			{
				result	= value.operator TXString();
			}
		}
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue() )
		{
			result = reader.GetValue()->operator TXString();
		}
	}

	return result;
}

bool VWDataSerializerSimple::GetValueOutBool(const GroupID& groupID, size_t valueIndex, bool& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		Uint8	value	= outValue ? 1u : 0u;
		resultOk		= GetValueOutNumeric<Uint8>( this->GetGroup( groupID ), valueIndex, value );
		outValue		= value != 0;
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Uint8 ) ) )
		{
			outValue = reader.GetValue()->operator Uint8() ? true : false;
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueOutSint8(const GroupID& groupID, size_t valueIndex, Sint8& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		resultOk	= GetValueOutNumeric<Sint8>( this->GetGroup( groupID ), valueIndex, outValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Sint8 ) ) )
		{
			outValue = reader.GetValue()->operator Sint8();
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueOutUint8(const GroupID& groupID, size_t valueIndex, Uint8& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		resultOk	= GetValueOutNumeric<Uint8>( this->GetGroup( groupID ), valueIndex, outValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Uint8 ) ) )
		{
			outValue = reader.GetValue()->operator Uint8();
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueOutSint16(const GroupID& groupID, size_t valueIndex, Sint16& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		resultOk	= GetValueOutNumeric<Sint16>( this->GetGroup( groupID ), valueIndex, outValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Sint16 ) ) )
		{
			outValue = reader.GetValue()->operator Sint16();
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueOutUint16(const GroupID& groupID, size_t valueIndex, Uint16& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		resultOk	= GetValueOutNumeric<Uint16>( this->GetGroup( groupID ), valueIndex, outValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Uint16 ) ) )
		{
			outValue = reader.GetValue()->operator Uint16();
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueOutSint32(const GroupID& groupID, size_t valueIndex, Sint32& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		resultOk	= GetValueOutNumeric<Sint32>( this->GetGroup( groupID ), valueIndex, outValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Sint32 ) ) )
		{
			outValue = reader.GetValue()->operator Sint32();
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueOutUint32(const GroupID& groupID, size_t valueIndex, Uint32& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		resultOk	= GetValueOutNumeric<Uint32>( this->GetGroup( groupID ), valueIndex, outValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Uint32 ) ) )
		{
			outValue = reader.GetValue()->operator Uint32();
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueOutSizeT(const GroupID& groupID, size_t valueIndex, size_t& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		VWDataSerializerGroup*	dataGroup = this->GetGroup( groupID );
		if ( dataGroup )
		{
			VWDataSerializerValue	value( dataGroup->GetContext(), (Sint32) 0 );
			if ( dataGroup->GetValue( valueIndex, nullptr, value ) )
			{
				Uint64	theValue = 0;
				value.CopyInto( &theValue, sizeof( theValue ) );
				outValue = size_t( theValue );
				ASSERTN( kVStanev, Uint64( outValue ) == theValue );
				resultOk = true;
			}
		}
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( Uint64 ) ) )
		{
			Uint64	theValue = 0;
			reader.GetValue()->CopyInto( & theValue, sizeof(theValue) );
			outValue = size_t( theValue );
			ASSERTN( kVStanev, Uint64(outValue) == theValue );
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueOutDouble(const GroupID& groupID, size_t valueIndex, double& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		resultOk	= GetValueOutNumeric<double>( this->GetGroup( groupID ), valueIndex, outValue );
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue( sizeof( double ) ) )
		{
			outValue = reader.GetValue()->operator double();
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueOutTXString(const GroupID& groupID, size_t valueIndex, TXString& outValue) const
{
	bool resultOk = false;
	if ( fLoaded )
	{
		VWDataSerializerGroup* dataGroup = this->GetGroup( groupID );
		if ( dataGroup  )
		{
			VWDataSerializerValue	value( dataGroup->GetContext(), outValue );
			if ( dataGroup->GetValue( valueIndex, nullptr, value ) )
			{
				outValue = value.operator TXString();
				resultOk = true;
			}
		}
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue() )
		{
			outValue = reader.GetValue()->operator TXString();
			resultOk = true;
		}
	}

	return resultOk;
}

bool VWDataSerializerSimple::GetValueMemory(const GroupID& groupID, size_t valueIndex, std::vector<char>& outValue) const
{
	outValue.clear();

	bool resultOk = false;
	if ( fLoaded )
	{
		VWDataSerializerGroup* dataGroup = this->GetGroup( groupID );
		if ( dataGroup && dataGroup->HasValue( valueIndex, NULL ) )
		{
			VWDataSerializerValue dataValue = dataGroup->GetValue( valueIndex, NULL );

			size_t		bytesCnt	= dataValue.GetBytesCount();
			const void*	bytesBegin	= dataValue.GetBytes();
			outValue.insert( outValue.end(), (const char*)bytesBegin, ((const char*)bytesBegin) + bytesCnt );

			resultOk = true;
		}
	}
	else
	{
		CLocalReader	reader( groupID, valueIndex );
		this->ReadLocal( & reader );
		if ( reader.HasValue() )
		{
			VWDataSerializerValue* dataValue = reader.GetValue();

			size_t		bytesCnt	= dataValue->GetBytesCount();
			const void*	bytesBegin	= dataValue->GetBytes();
			outValue.insert( outValue.end(), (const char*)bytesBegin, ((const char*)bytesBegin) + bytesCnt );

			resultOk = true;
		}
	}

	return resultOk;
}

VWDataSerializerGroup* VWDataSerializerSimple::GetCreateGroup(const GroupID& groupID)
{
	VWDataSerializerGroup* dataGroup = NULL;

	if ( groupID.groupID_level1 != TDataIdentifier(-1) )
	{
		dataGroup = fSerializer.FindChildDataGroup( groupID.groupID_level1, NULL );
		if ( dataGroup == NULL )
		{
			dataGroup = fSerializer.CreateChildDataGroup( groupID.groupID_level1, NULL );
		}

		if ( dataGroup )
		{
			if ( groupID.groupID_level2 != TDataIdentifier(-1) )
			{
				VWDataSerializerGroup*	dataGroup2 = dataGroup->FindChildDataGroup( groupID.groupID_level2, NULL );
				if ( dataGroup2 == NULL )
				{
					dataGroup2 = dataGroup->CreateChildDataGroup( groupID.groupID_level2, NULL );
				}

				dataGroup = dataGroup2;
			}
		}
	}

	return dataGroup;
}

void VWDataSerializerSimple::SetValueBool(const GroupID& groupID, size_t valueIndex, bool value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), Uint8(value) ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueSint8(const GroupID& groupID, size_t valueIndex, Sint8 value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), value ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueUint8(const GroupID& groupID, size_t valueIndex, Uint8 value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), value ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueSint16(const GroupID& groupID, size_t valueIndex, Sint16 value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), value ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueUint16(const GroupID& groupID, size_t valueIndex, Uint16 value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), value ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueSint32(const GroupID& groupID, size_t valueIndex, Sint32 value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), value ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueUint32(const GroupID& groupID, size_t valueIndex, Uint32 value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), value ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueSizeT(const GroupID& groupID, size_t valueIndex, size_t value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		Uint64	theValue = value;
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), &theValue, sizeof(theValue) ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueDouble(const GroupID& groupID, size_t valueIndex, double value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), value ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueTXString(const GroupID& groupID, size_t valueIndex, const TXString& value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), value ), valueIndex, NULL );
	}
}

void VWDataSerializerSimple::SetValueMemory(const GroupID& groupID, size_t valueIndex, const std::vector<char>& value)
{
	VWDataSerializerGroup* dataGroup = this->GetCreateGroup( groupID );
	if ( dataGroup )
	{
		dataGroup->AddValue( VWDataSerializerValue( dataGroup->GetContext(), (void*)&value[0], value.size() ), valueIndex, NULL );
	}
}

bool VWDataSerializerSimple::ResetValueString(const GroupID& groupID, size_t valueIndex)
{
	bool					result	= false;

	VWDataSerializerGroup*	group	= this->GetGroup( groupID );
	if ( group )
	{
		result = group->ResetValueString( valueIndex, nullptr );
	}

	return result;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------
VWDataSerializerSimple::CLocalReader::CLocalReader(const GroupID& groupID, size_t valueIndex)
	: fGroupID( groupID )
	, fValueIndex( valueIndex )
	, fValue( NULL )
	, fDataIdentifierIndex( 0 )
{
}

VWDataSerializerSimple::CLocalReader::~CLocalReader()
{
	if ( fValue )
		delete fValue;
	fValue = NULL;
}

bool VWDataSerializerSimple::CLocalReader::HasValue() const
{
	return fValue != NULL;
}

bool VWDataSerializerSimple::CLocalReader::HasValue(size_t bytesCnt) const
{
	return fValue != NULL && fValue->GetBytesCount() == bytesCnt;
}

VWDataSerializerValue* VWDataSerializerSimple::CLocalReader::GetValue()
{
	return fValue;
}

void VWDataSerializerSimple::CLocalReader::BeginGroup(TDataIdentifier id, const char* )
{
	if ( fDataIdentifierIndex < kDataIdentifiersSize )
	{
		farrDataIdentifiers[ fDataIdentifierIndex ] = id;
	}

	fDataIdentifierIndex++;
}

void VWDataSerializerSimple::CLocalReader::EndGroup(TDataIdentifier id, const char* )
{
	fDataIdentifierIndex--;
}

bool VWDataSerializerSimple::CLocalReader::AddValue(VWDataSerializerContext& context, void* buffer, size_t bufferSize, size_t index, const char* )
	// return false to interrupt traversal
{
	bool dataFound = false;

	if ( fGroupID.groupID_level1 != TDataIdentifier(-1) )
	{
		// first check to see if the data group is what we need
		if ( fDataIdentifierIndex == 2 )
		{
			dataFound =		(farrDataIdentifiers[ 0 ] == 0 )
						&&	(farrDataIdentifiers[ 1 ] == fGroupID.groupID_level1)
						&&	(fGroupID.groupID_level2 == TDataIdentifier(-1));
		}
		else if ( fDataIdentifierIndex == 3 )
		{
			dataFound =		(farrDataIdentifiers[ 0 ] == 0 )
						&&	(farrDataIdentifiers[ 1 ] == fGroupID.groupID_level1)
						&&	(farrDataIdentifiers[ 2 ] == fGroupID.groupID_level2);
		}

		// then check the value index
		if ( dataFound )
		{
			dataFound = (index == fValueIndex);
		}

		// and if ok read the value
		if ( dataFound && fValue == NULL )
		{
			fValue = SDK_NEW VWDataSerializerValue( context, buffer, bufferSize );
		}
	}

	return ! dataFound;
}
