//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING FIRST NON-COMMENT LINE.  [DMB, 10/30/95]


typedef std::vector<VWVariant*, std::vwallocator< VWVariant* > >	TVWVariantArray;

/*static*/ VWVariant	VWVariant::sEmpty;

VWVariant::VWVariant()
{
	this->Init();
}

VWVariant::VWVariant(EVWVariantType type)
{
	this->Init();
	fType			= type;
}

VWVariant::VWVariant(Sint8 value)
{
	this->Init();
	fType	= eVWVariantType_SignedInteger;
	this->InitForSimpleType( value );
}

VWVariant::VWVariant(Uint8 value)
{
	this->Init();
	fType	= eVWVariantType_UnsignedInteger;
	this->InitForSimpleType( value );
}

VWVariant::VWVariant(Sint16 value)
{
	this->Init();
	fType	= eVWVariantType_SignedInteger;
	this->InitForSimpleType( value );
}

VWVariant::VWVariant(Uint16 value)
{
	this->Init();
	fType	= eVWVariantType_UnsignedInteger;
	this->InitForSimpleType( value );
}

VWVariant::VWVariant(Sint32 value)
{
	this->Init();
	fType	= eVWVariantType_SignedInteger;
	this->InitForSimpleType( value );
}

VWVariant::VWVariant(Uint32 value)
{
	this->Init();
	fType	= eVWVariantType_UnsignedInteger;
	this->InitForSimpleType( value );
}

VWVariant::VWVariant(double value)
{
	this->Init();
	fType	= eVWVariantType_Double;
	this->InitForSimpleType( value );
}

VWVariant::VWVariant(float value)
{
	this->Init();
	fType	= eVWVariantType_Float;
	this->InitForSimpleType( value );
}

VWVariant::VWVariant(bool value)
{
	this->Init();
	fType				= eVWVariantType_Bool;
	fBytesCnt			= 1;
	this->EnsureBuffeSize( fBytesCnt );
	Uint8	theValue	= value ? 1 : 0;
	memcpy( fBuffer, & theValue, fBytesCnt );
}

VWVariant::VWVariant(const char* szBuffer, size_t size)
{
	this->Init();
	fType		= eVWVariantType_String;
	fBytesCnt	= size;
	this->EnsureBuffeSize( fBytesCnt );
	memcpy( fBuffer, szBuffer, fBytesCnt );
}

VWVariant::VWVariant(const unsigned char* psBuffer, size_t size)
{
	this->Init();
	fType		= eVWVariantType_String;
	fBytesCnt	= size;
	this->EnsureBuffeSize( fBytesCnt );
	memcpy( fBuffer, (psBuffer+1), psBuffer[0] );
}

VWVariant::VWVariant(const TXString& value)
{
	this->Init();
	fType		= eVWVariantType_String;
	fBytesCnt	= value.GetEncodingLength(ETXEncoding::eUTF8);
	this->EnsureBuffeSize( fBytesCnt );
	memcpy( fBuffer, (const char*) value, fBytesCnt );
}

VWVariant::VWVariant(void* buffer, size_t size, size_t typeID)
{
	this->Init();
	fType		= eVWVariantType_RawBuffer;
	fBytesCnt	= size;
	// the typeID is a size_t, but we don't want the size in the buffer to change between 32 and 64 bit, so we truncate it here.
	Uint32 truncTypeID = DemoteTo<Uint32>(kBMarinari, typeID);
	this->EnsureBuffeSize( fBytesCnt + sizeof(truncTypeID) );
	memcpy( fBuffer, &truncTypeID, sizeof(truncTypeID) );
	memcpy( fBuffer + sizeof(truncTypeID), buffer, fBytesCnt );
}

VWVariant::VWVariant(MCObjectHandle value)
{
	this->Init();
	fType	= eVWVariantType_Handle;
	this->InitForSimpleType( value );
}

VWVariant::VWVariant(const VWVariant& src)
{
	this->Init();
	fType		= src.fType;
	fBytesCnt	= src.fBytesCnt;
	this->EnsureBuffeSize( src.fBufferSize );
	memcpy( fBuffer, src.fBuffer, src.fBufferSize );
}

VWVariant::~VWVariant()
{
	fType	= eVWVariantType_Empty;
	this->Free( true );
}

VWVariant& VWVariant::operator=(const VWVariant& value)
{
	this->Free( false );
	fType		= value.fType;
	fBytesCnt	= value.fBytesCnt;
	this->EnsureBuffeSize( value.fBufferSize );
	memcpy( fBuffer, value.fBuffer, value.fBufferSize );
	return *this;
}

VWVariant& VWVariant::operator=(Sint8 value)
{
	this->Free( false );
	fType	= eVWVariantType_SignedInteger;
	this->InitForSimpleType( value );
	return *this;
}

VWVariant& VWVariant::operator=(Uint8 value)
{
	this->Free( false );
	fType	= eVWVariantType_UnsignedInteger;
	this->InitForSimpleType( value );
	return *this;
}

VWVariant& VWVariant::operator=(Sint16 value)
{
	this->Free( false );
	fType	= eVWVariantType_SignedInteger;
	this->InitForSimpleType( value );
	return *this;
}

VWVariant& VWVariant::operator=(Uint16 value)
{
	this->Free( false );
	fType	= eVWVariantType_UnsignedInteger;
	this->InitForSimpleType( value );
	return *this;
}

VWVariant& VWVariant::operator=(Sint32 value)
{
	this->Free( false );
	fType	= eVWVariantType_SignedInteger;
	this->InitForSimpleType( value );
	return *this;
}

VWVariant& VWVariant::operator=(Uint32 value)
{
	this->Free( false );
	fType	= eVWVariantType_UnsignedInteger;
	this->InitForSimpleType( value );
	return *this;
}

VWVariant& VWVariant::operator=(double value)
{
	this->Free( false );
	fType	= eVWVariantType_Double;
	this->InitForSimpleType( value );
	return *this;
}

VWVariant& VWVariant::operator=(float value)
{
	this->Free( false );
	fType	= eVWVariantType_Float;
	this->InitForSimpleType( value );
	return *this;
}

VWVariant& VWVariant::operator=(bool value)
{
	this->Free( false );
	fType				= eVWVariantType_Bool;
	fBytesCnt			= 1;
	this->EnsureBuffeSize( fBytesCnt );
	Uint8	theValue	= value ? 1 : 0;
	memcpy( fBuffer, & theValue, fBytesCnt );
	return *this;
}

VWVariant& VWVariant::operator=(const TXString& value)
{
	this->Free( false );
	fType		= eVWVariantType_String;
	fBytesCnt	= value.GetEncodingLength(ETXEncoding::eUTF8);
	this->EnsureBuffeSize( fBytesCnt );
	memcpy( fBuffer, (const char*) value, fBytesCnt );
	return *this;
}

VWVariant& VWVariant::operator=(const char* szString)
{
	this->Free( false );
	fType		= eVWVariantType_String;
	fBytesCnt	= strlen(szString);
	this->EnsureBuffeSize( fBytesCnt );
	memcpy( fBuffer, szString, fBytesCnt );
	return *this;
}

VWVariant& VWVariant::operator=(const unsigned char* psString)
{
	this->Free( false );
	fType		= eVWVariantType_String;
	fBytesCnt	= psString[0];
	this->EnsureBuffeSize( fBytesCnt );
	memcpy( fBuffer, (psString+1), psString[0] );
	return *this;
}

VWVariant& VWVariant::operator=(MCObjectHandle value)
{
	this->Free( false );
	fType	= eVWVariantType_Handle;
	this->InitForSimpleType( value );
	return *this;
}

bool VWVariant::operator==(const VWVariant& v)
{
	bool result = false;
	if(this->fType == v.fType && this->fBytesCnt == v.fBytesCnt)
	{
		result = true;
		for(size_t i = 0; i < this->fBytesCnt; i++)
		{
			if(this->fBuffer[i] != v.fBuffer[i])
			{
				result = false;
				break;
			}
		}
	}
	return result;
}

EVWVariantType VWVariant::GetType() const
{
	return fType;
}

bool VWVariant::IsEmpty() const
{
	return (fType == eVWVariantType_Empty);
}

size_t VWVariant::GetBytesCount() const
{
	return fBytesCnt;
}

Sint8 VWVariant::GetSint8() const
{
	return this->GetIntegerSimpleType<Sint8>( true );
}

void VWVariant::SetSint8(Sint8 value)
{
	this->SetForSimpleType( eVWVariantType_SignedInteger, value );
}

Uint8 VWVariant::GetUint8() const
{
	return this->GetIntegerSimpleType<Uint8>( false );
}

void VWVariant::SetUint8(Uint8 value)
{
	this->SetForSimpleType( eVWVariantType_UnsignedInteger, value );
}

Sint16 VWVariant::GetSint16() const
{
	return this->GetIntegerSimpleType<Sint16>( true );
}

void VWVariant::SetSint16(Sint16 value)
{
	this->SetForSimpleType( eVWVariantType_SignedInteger, value );
}

Uint16 VWVariant::GetUint16() const
{
	return this->GetIntegerSimpleType<Uint16>( false );
}

void VWVariant::SetUint16(Uint16 value)
{
	this->SetForSimpleType( eVWVariantType_SignedInteger, value );
}

Sint32 VWVariant::GetSint32() const
{
	return this->GetIntegerSimpleType<Sint32>( true );
}

void VWVariant::SetSint32(Sint32 value)
{
	this->SetForSimpleType( eVWVariantType_SignedInteger, value );
}

Uint32 VWVariant::GetUint32() const
{
	return this->GetIntegerSimpleType<Uint32>( false );
}

void VWVariant::SetUint32(Uint32 value)
{
	this->SetForSimpleType( eVWVariantType_SignedInteger, value );
}

double VWVariant::GetDouble() const
{
	double	result	= 0;
	if (	fType == eVWVariantType_Double
		&&	VERIFYN( kVStanev, sizeof(double) == fBytesCnt )
		)
	{
		memcpy( & result, fBuffer, sizeof(double) );
	}
	else if (	fType == eVWVariantType_Float
			&&	VERIFYN( kVStanev, sizeof(float) == fBytesCnt )
		)
	{
		float	value;
		memcpy( & value, fBuffer, sizeof(float) );
		result		= value;
	}
	else {
		TXString	strRes	= this->GetTXString();
		result				= strRes.atof();
	}

	return result;
}

void VWVariant::SetDouble(double value)
{
	this->SetForSimpleType( eVWVariantType_Double, value );
}

float VWVariant::GetFloat() const
{
	float	result	= 0;
	if (	fType == eVWVariantType_Float
		&&	VERIFYN( kVStanev, sizeof(float) == fBytesCnt )
		)
	{
		memcpy( & result, fBuffer, sizeof(float) );
	}
	else if (	fType == eVWVariantType_Double
			&&	VERIFYN( kVStanev, sizeof(double) == fBytesCnt )
		)
	{
		double	value;
		memcpy( & value, fBuffer, sizeof(double) );
		result		= float(value);
	}
	else {
		TXString	strRes	= this->GetTXString();
		result				= float(strRes.atof());
	}

	return result;
}

void VWVariant::SetFloat(float value)
{
	this->SetForSimpleType( eVWVariantType_Float, value );
}

bool VWVariant::GetBool() const
{
	Uint8	result		= 0;
	
	if (	fType == eVWVariantType_Bool
		&&	VERIFYN( kVStanev, sizeof(Uint8) == fBytesCnt ) )
	{
		memcpy( & result, fBuffer, sizeof(Uint8) );
	}
	else {
		TXString	strRes	= this->GetTXString();
		result				= strRes.atoi();
	}

	return result ? true : false;
}

void VWVariant::SetBool(bool value)
{
	Uint8	theValue	= value ? 1 : 0;
	this->SetForSimpleType( eVWVariantType_Bool, theValue );
}

TXString VWVariant::GetTXString() const
{
	TXString	result;
	switch( fType ) {
		case eVWVariantType_Empty:
			{
				result.Clear();
				break;
			}

		case eVWVariantType_SignedInteger:
			{
				Sint32	value	= 0;
				if ( VERIFYN( kVStanev, sizeof(Sint32) >= fBytesCnt ) ) {
					memcpy( & value, fBuffer, fBytesCnt );
				}
				result.Format( "%d", value );
				break;
			}

		case eVWVariantType_UnsignedInteger:
			{
				Uint32	value	= 0;
				if ( VERIFYN( kVStanev, sizeof(Uint32) >= fBytesCnt ) ) {
					memcpy( & value, fBuffer, fBytesCnt );
				}
				result.Format( "%d", value );
				break;
			}

		case eVWVariantType_Double:
			{
				double	value	= 0;
				if ( VERIFYN( kVStanev, sizeof(double) == fBytesCnt ) ) {
					memcpy( & value, fBuffer, sizeof(double) );
				}
				result.Format( "%f", value );
				break;
			}

		case eVWVariantType_Float:
			{
				float	value	= 0;
				if ( VERIFYN( kVStanev, sizeof(float) == fBytesCnt ) ) {
					memcpy( & value, fBuffer, sizeof(float) );
				}
				result.Format( "%f", value );
				break;
			}

		case eVWVariantType_Bool:
			{
				Uint8	value	= false;
				if ( VERIFYN( kVStanev, 1 == fBytesCnt ) ) {
					memcpy( & value, fBuffer, 1 );
					value	= value ? 1 : 0;
				}
				result.Format( "%d", value );
				break;
			}

		case eVWVariantType_String:
			{
				result	= TXString( (const char*) fBuffer, fBytesCnt );
				break;
			}

		case eVWVariantType_RawBuffer:
			{
				result.Clear();
				break;
			}

		case eVWVariantType_Arrary:
			{
				result.Clear();
				break;
			}

		// Vectorworks types
		case eVWVariantType_Handle:
			{
				Uint32	value	= 0;
				if ( VERIFYN( kVStanev, sizeof(Uint32) == fBytesCnt ) ) {
					memcpy( & value, fBuffer, sizeof(Uint32) );
				}
				result.Format( "%d", value );
				break;
			}

		case eVWVariantType_InternalNumber:
			{
				Uint16	value	= 0;
				if ( VERIFYN( kVStanev, sizeof(Uint16) == fBytesCnt ) ) {
					memcpy( & value, fBuffer, sizeof(Uint16) );
				}
				result.Format( "%d", value );
				break;
			}

		case eVWVariantType_InternalName:
			{
				result	= TXString( (const char*) fBuffer, fBytesCnt );
				break;
			}

		default:
			{
				DSTOP((kVStanev, "Unknown variant type=%d", fType ));
				result.Clear();
			}
	}

	return result;
}

void VWVariant::SetTXString(const TXString& value)
{
	switch( fType ) {
		case eVWVariantType_Empty:
			{
				break;
			}

		case eVWVariantType_SignedInteger:
			{
				Sint32	theValue	= value.atoi();
				this->SetForSimpleType( eVWVariantType_SignedInteger, theValue );
				break;
			}

		case eVWVariantType_UnsignedInteger:
			{
				Uint32	theValue	= Abs( value.atoi() );
				this->SetForSimpleType( eVWVariantType_UnsignedInteger, theValue );
				break;
			}

		case eVWVariantType_Double:
			{
				double	theValue	= value.atof();
				this->SetForSimpleType( eVWVariantType_Double, theValue );
				break;
			}

		case eVWVariantType_Float:
			{
				float	theValue	= float(value.atof());
				this->SetForSimpleType( eVWVariantType_Float, theValue );
				break;
			}

		case eVWVariantType_Bool:
			{
				bool	theValue	= (value.EqualNoCase("true")  || value.atoi()) ? true : false;
				this->SetBool( theValue );
				break;
			}

		case eVWVariantType_String:
			{
				this->operator = ( (const char*) value );
				break;
			}

		case eVWVariantType_RawBuffer:
			{
				break;
			}

		case eVWVariantType_Arrary:
			{
				break;
			}

		// Vectorworks types
		case eVWVariantType_Handle:
			{
				Uint32	theValue	= Abs( value.atoi() );
				this->SetForSimpleType( eVWVariantType_Handle, theValue );
				break;
			}

		case eVWVariantType_InternalNumber:
			{
				Sint32	theValue	= value.atoi();
				this->SetForSimpleType( eVWVariantType_InternalNumber, theValue );
				break;
				break;
			}

		case eVWVariantType_InternalName:
			{
				this->operator = (value);

				break;
			}

		default:
			{
				DSTOP((kVStanev, "Unknown variant type=%d", fType ));
			}
	}
}

size_t VWVariant::GetBuffer(void* buffer, size_t bufferSize) const
{
	size_t	typeID;
	return this->GetBuffer( buffer, bufferSize, typeID );
}

size_t VWVariant::GetBuffer(void* buffer, size_t bufferSize, size_t& outTypeID) const
{
	size_t	bytesCpy	= 0;
	if ( fType == eVWVariantType_Arrary ) {
		Uint32 intTypeID = *((Uint32*)fBuffer);
		outTypeID	= (size_t)intTypeID; 
		bytesCpy	= fBytesCnt;
		if ( buffer ) {
			bytesCpy	= fBytesCnt < bufferSize ? fBytesCnt : bufferSize;
			memcpy( buffer, fBuffer + sizeof(intTypeID), bytesCpy );
		}
	}

	return bytesCpy;
}

MCObjectHandle VWVariant::GetHandle() const
{
	MCObjectHandle	result		= 0;
	
	if (	fType == eVWVariantType_Handle
		&&	VERIFYN( kVStanev, sizeof(SintptrT) == fBytesCnt ) )
	{
		SintptrT	value	= 0;
		memcpy( & value, fBuffer, sizeof(SintptrT) );
		result			= MCObjectHandle(value);
	}
	else {
		TXString	strRes	= this->GetTXString();
		result				= MCObjectHandle( strRes.atoi64() );
	}

	return result;
}

InternalIndex VWVariant::GetInternalIndex() const
{
	InternalIndex	result		= 0;
	
	if (	fType == eVWVariantType_SignedInteger
		&&	VERIFYN( kVStanev, sizeof(Sint32) == fBytesCnt ) )
	{
		Sint32	value	= 0;
		memcpy( & value, fBuffer, sizeof(Sint32) );
		result			= InternalIndex(value);
	}
	else {
		TXString	strRes	= this->GetTXString();
		result				= InternalIndex( strRes.atoi() );
	}

	return result;
}

bool VWVariant::GetInternalName(InternalName& outName) const
{
	outName = this->GetTXString();
	return fType == eVWVariantType_InternalName;
}

size_t VWVariant::GetElementCount() const
{
	size_t	count	= 0;
	if ( VERIFYN( kVStanev, fType == eVWVariantType_Arrary && fBuffer ) ) {
		TVWVariantArray*	pArr	= (TVWVariantArray*) fBuffer;
		count						= pArr->size();
	}

	return count;
}

void VWVariant::AddElement(const VWVariant& value)
{
	if ( fType == eVWVariantType_Empty ) {
		ASSERTN( kVStanev, fBufferSize == 0 && fBuffer == NULL );

		fType						= eVWVariantType_Arrary;
		void*				memory	= gSDK->GSNewPtr( sizeof( TVWVariantArray ) );
		TVWVariantArray*	pArr	= new ( memory ) TVWVariantArray();
		fBuffer						= (Uint8*) pArr;
	}

	if ( VERIFYN( kVStanev, fType == eVWVariantType_Arrary && fBuffer ) ) {
		TVWVariantArray*	pArr			= (TVWVariantArray*) fBuffer;
		void*				pNewValueBuff	= gSDK->GSNewPtr( sizeof( VWVariant ) );
		VWVariant*			pNewValue		= new ( pNewValueBuff ) VWVariant( value );
		pArr->push_back( pNewValue );
	}
}

VWVariant& VWVariant::GetElement(size_t at)
{
	if ( VERIFYN( kVStanev, fType == eVWVariantType_Arrary && fBuffer ) ) {
		TVWVariantArray*	pArr	= (TVWVariantArray*) fBuffer;
		if ( at >= pArr->size() ) {
			return VWVariant::sEmpty;
		}
		else {
			return * (*pArr)[ at ];
		}
	}
	else {
		return VWVariant::sEmpty;
	}
}

const VWVariant& VWVariant::GetElement(size_t at) const
{
	if ( VERIFYN( kVStanev, fType == eVWVariantType_Arrary && fBuffer ) ) {
		TVWVariantArray*	pArr	= (TVWVariantArray*) fBuffer;
		if ( at >= pArr->size() ) {
			return VWVariant::sEmpty;
		}
		else {
			return * (*pArr)[ at ];
		}
	}
	else {
		return VWVariant::sEmpty;
	}
}

void VWVariant::RemoveElement(size_t at)
{
	if ( VERIFYN( kVStanev, fType == eVWVariantType_Arrary && fBuffer ) ) {
		TVWVariantArray*	pArr	= (TVWVariantArray*) fBuffer;
		if ( at < pArr->size() ) {
			VWVariant*	pValue	= (*pArr)[ at ];
			if ( pValue ) {
				gSDK->GSDisposePtr( pValue );
			}

			pArr->erase( pArr->begin() + at );
		}
	}
}

void VWVariant::ClearElements()
{
	if ( fType == eVWVariantType_Arrary && fBuffer ) {
		TVWVariantArray*	pArr	= (TVWVariantArray*) fBuffer;
		size_t				cnt		= pArr->size();
		for(size_t i=0; i<cnt; i++) {
			VWVariant*	pValue	= (*pArr)[ i ];
			if ( pValue ) {
				gSDK->GSDisposePtr( pValue );
			}
		}
		pArr->clear();
	}
}

void VWVariant::Clear()
{
	this->Free(true);
}

void VWVariant::Init()
{
	fType			= eVWVariantType_Empty;
	fBytesCnt		= 0;
	fBuffer			= NULL;
	fBufferSize		= 0;
}

void VWVariant::Free(bool complete)
{
	fBytesCnt	= 0;
	if ( fBuffer ) {
		if ( fType == eVWVariantType_Arrary ) {
			TVWVariantArray*	pArr	= (TVWVariantArray*) fBuffer;
			size_t				cnt		= pArr->size();
			for(size_t i=0; i<cnt; i++) {
				VWVariant*	pValue	= (*pArr)[ i ];
				if ( pValue ) {
					gSDK->GSDisposePtr( pValue );
				}
			}
			pArr->clear();
		}

		fType	= eVWVariantType_Empty;
		if ( complete ) {
			gSDK->GSDisposePtr( fBuffer );
			fBuffer			= NULL;
			fBufferSize		= 0;
		}
	}
}

void VWVariant::EnsureBuffeSize(size_t size, size_t extraChunksCnt)
{
	if ( VERIFYN( kVStanev, fType != eVWVariantType_Arrary ) ) {
		if ( size >= fBufferSize ) {
			// it's time to enlarge the buffer
			size_t		newBufferSize	= size;
			if ( extraChunksCnt > 0 ) {
				newBufferSize	= extraChunksCnt * size;
			}

			Uint8*		newBuffer		= (Uint8*) gSDK->GSNewPtr( newBufferSize );

			if ( fBuffer ) {
				memcpy( newBuffer, fBuffer, fBufferSize );

				gSDK->GSDisposePtr( fBuffer );
				fBuffer	= NULL;
			}

			fBuffer		= newBuffer;
			fBufferSize	= newBufferSize;
		}
	}
}



