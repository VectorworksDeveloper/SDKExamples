//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VectorWorks::Filing;

namespace VWFC
{
	namespace Tools
	{
		enum EDataSerializerSwapContext
		{
			eDataSerializerSwapContext_Read,
			eDataSerializerSwapContext_Write
		};
	}
}

VWDataSerializerContext::VWDataSerializerContext()
{
	fByteSwap	= 1;
	fSaveStringsInMacEncoding = false;
	fSaveWithSwapBytes = false;
}

VWDataSerializerContext::~VWDataSerializerContext()
{
	
}

// Depending on where we are (in the caller class function or the called global function (this one)) ...
// ... this static variable has different value (or its value is not preserved inside this global function).
// That is why I pass this variable as an additional parameter here.
template<class T> T EnsureSwappedBytes(const T& value, VWDataSerializerContext& context, EDataSerializerSwapContext callContext)
{
	T	result;
	if ( callContext == eDataSerializerSwapContext_Write )
	{
		if ( context.fByteSwap == 0 && context.fSaveWithSwapBytes )
		{
			result = VWFC::Tools::SwapBytes( value );
		}
		else
		{
			result = value;
		}
	}
	else
	{
		if ( context.fByteSwap == 1 )	// use the value.
		{
			result	= value;
		}
		else							// check for swapped bytes.
		{
			// this is kind of stupid, but it's the only way
			// to be able to work with broken not equal byte order of existing documents
			// This should not be problem for current use of the DataSerializer
			// since nobody currently stores monster data

			T	swappedValue	= VWFC::Tools::SwapBytes( value );

			if ( swappedValue == value )
			{
				result	= value;
			}
			else
			{
				if ( context.fByteSwap == -1 )	// still not decided.
				{
					context.fByteSwap	= ( swappedValue < value ) ? 0 : 1;
				}

				result	= ( context.fByteSwap == 0 ) ? swappedValue : value;
			}
		}
	}

	return result;
}

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, void* pData, size_t size)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( pData, size );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, Sint8 data)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( data );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, Uint8 data)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( data );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, Sint16 data)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( data );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, Uint16 data)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( data );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, Sint32 data)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( data );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, Uint32 data)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( data );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, Sint64 data)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( data );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, double data)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( data );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, const TXString& str)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	this->SetValue( str );
}

VWDataSerializerValue::VWDataSerializerValue(VWDataSerializerContext& context, Uint32 data, const char* szEnum1, ...)
	: m_context( context )
	, m_bUnkonwnType( false )
	, m_valueAsStringType( EValueAsStringType::Unknown )
{
	va_list marker;
	va_start( marker, szEnum1 );
	const char*		szThisEnum		= szEnum1;
	while( szThisEnum ) {
		TXString	enumValue	= szThisEnum;
		m_arrEnumValues.push_back( enumValue );
		
		szThisEnum = va_arg( marker, const char* );
	}
	va_end( marker );

	size_t		len		= m_arrEnumValues.size();
	VWFC_ASSERT( data < len );
	if ( data < len )
		this->SetValue( m_arrEnumValues[ data ] );
	else
		this->SetValue( data );
}

VWDataSerializerValue::VWDataSerializerValue(const VWDataSerializerValue& src)
	: m_context( src.m_context )
{
	m_nBytesCnt		= src.m_nBytesCnt;
	m_pBytes		= SDK_NEW Uint8[ m_nBytesCnt ];
	for(size_t i=0; i<m_nBytesCnt; i++) {
		m_pBytes[i]	= src.m_pBytes[i];
	}
	m_valueAsStringType	= src.m_valueAsStringType;
	m_valueAsString		= src.m_valueAsString;
	m_bUnkonwnType		= src.m_bUnkonwnType;
}

VWDataSerializerValue::~VWDataSerializerValue()
{
	delete [] m_pBytes;
	m_pBytes			= NULL;
	m_nBytesCnt			= 0;
}

VWDataSerializerContext& VWDataSerializerValue::GetContext()
{
	return m_context;
}

void VWDataSerializerValue::AllowSwappedBytesProcessing()
{
	// XXX Bobi:
	// The following allows checking and processing for swapped bytes.

	m_context.fByteSwap		= -1;
}

VWDataSerializerValue& VWDataSerializerValue::SetEnumValues(const char* szEnum1, ...)
{
	va_list marker;
	va_start( marker, szEnum1 );
	const char*		szThisEnum		= szEnum1;
	while( szThisEnum ) {
		TXString	enumValue	= szThisEnum;
		m_arrEnumValues.push_back( enumValue );
		
		szThisEnum = va_arg( marker, const char* );
	}
	va_end( marker );

	return *this;
}

VWDataSerializerValue& VWDataSerializerValue::operator=(const VWDataSerializerValue& src)
{
	delete [] m_pBytes;
	m_pBytes		= NULL;

	m_nBytesCnt		= src.m_nBytesCnt;
	m_pBytes		= SDK_NEW Uint8[ m_nBytesCnt ];
	for(size_t i=0; i<m_nBytesCnt; i++) {
		m_pBytes[i]	= src.m_pBytes[i];
	}
	m_valueAsStringType	= src.m_valueAsStringType;
	m_valueAsString		= src.m_valueAsString;

	return *this;
}

void VWDataSerializerValue::SetValue(Sint8 data)
{
	m_bUnkonwnType	= false;
	// make the string before altering the byte order
	m_valueAsStringType		= EValueAsStringType::Int;
	m_valueAsString.fInt	= data;

	data	= /*static*/ ::EnsureSwappedBytes( data, m_context, eDataSerializerSwapContext_Write );
	this->SetData( & data, sizeof(Sint8) );
}

void VWDataSerializerValue::SetValue(Uint8 data)
{
	m_bUnkonwnType	= false;
	// make the string before altering the byte order
	m_valueAsStringType		= EValueAsStringType::Int;
	m_valueAsString.fInt	= data;

	data	= /*static*/ ::EnsureSwappedBytes( data, m_context, eDataSerializerSwapContext_Write );
	this->SetData( & data, sizeof(Uint8) );
}

void VWDataSerializerValue::SetValue(Sint16 data)
{
	m_bUnkonwnType	= false;
	// make the string before altering the byte order
	m_valueAsStringType		= EValueAsStringType::Int;
	m_valueAsString.fInt	= data;

	data	= /*static*/ ::EnsureSwappedBytes( data, m_context, eDataSerializerSwapContext_Write );
	this->SetData( & data, sizeof(Sint16) );
}

void VWDataSerializerValue::SetValue(Uint16 data)
{
	m_bUnkonwnType	= false;
	// make the string before altering the byte order
	m_valueAsStringType		= EValueAsStringType::Int;
	m_valueAsString.fInt	= data;

	data	= /*static*/ ::EnsureSwappedBytes( data, m_context, eDataSerializerSwapContext_Write );
	this->SetData( & data, sizeof(Uint16) );
}

void VWDataSerializerValue::SetValue(Sint32 data)
{
	m_bUnkonwnType	= false;
	// make the string before altering the byte order
	m_valueAsStringType		= EValueAsStringType::Int;
	m_valueAsString.fInt	= data;

	data	= /*static*/ ::EnsureSwappedBytes( data, m_context, eDataSerializerSwapContext_Write );
	this->SetData( & data, sizeof(Sint32) );
}

void VWDataSerializerValue::SetValue(Uint32 data)
{
	m_bUnkonwnType	= false;
	// make the string before altering the byte order
	m_valueAsStringType		= EValueAsStringType::Int;
	m_valueAsString.fInt	= data;

	data	= /*static*/ ::EnsureSwappedBytes( data, m_context, eDataSerializerSwapContext_Write );
	this->SetData( & data, sizeof(Uint32) );
}

void VWDataSerializerValue::SetValue(Sint64 data)
{
	m_bUnkonwnType	= false;
	// make the string before altering the byte order
	m_valueAsStringType		= EValueAsStringType::Real;
	m_valueAsString.fReal	= static_cast<double>(data);
	
	VWFC_ASSERT( sizeof(double) == sizeof(Sint64) );
	Sint64	bitValue;
	memcpy( & bitValue, & data, sizeof(Sint64) );
	
	this->SetData( & bitValue, sizeof(Sint64) );
	
}

void VWDataSerializerValue::SetValue(double data)
{
	m_bUnkonwnType	= false;
	// make the string before altering the byte order
	m_valueAsStringType		= EValueAsStringType::Real;
	m_valueAsString.fReal	= data;

	VWFC_ASSERT( sizeof(double) == sizeof(Uint64) );
	Uint64	bitValue;
	memcpy( & bitValue, & data, sizeof(double) );

	// XXX Bobi:
	// As the result of 'memcpy' between 'double data' and 'Uint64 bitValue' doesn't preserve the "swapping monotonity"
	// (i.e. if ('data' <= SwapBytes('data')), doesn't mean that ('bitValue' <= SwapBytes('bitValue')) and vice versa),
	// then the validity of the swapping criteria in the function 'EnsureSwappedBytes' is not guaranteed. Therefore, do not call EnsureSwappedBytes here.
	//
	//bitValue	= /*static*/ ::EnsureSwappedBytes( bitValue, m_context, eDataSerializerSwapContext_Write );

	this->SetData( & bitValue, sizeof(Uint64) );
}

void VWDataSerializerValue::SetValue(void* pData, size_t size)
{
	m_bUnkonwnType	= false;
	this->SetData( pData, size );

	m_valueAsStringType	= EValueAsStringType::Unknown;
}

void VWDataSerializerValue::SetValue(const TXString& str)
{
	m_bUnkonwnType	= false;
	if ( m_context.fSaveStringsInMacEncoding )
	{
		size_t	len		= str.GetEncodingLength(ETXEncoding::eMacEncoded);
		m_nBytesCnt		= (len + 1) * sizeof(char);	// 2 extra UCChars reserved for byte marker and 0-term
		m_pBytes		= SDK_NEW Uint8[ m_nBytesCnt ];
		char *pUC		= (char *)m_pBytes;
		str.CopyInto(pUC, m_nBytesCnt, ETXEncoding::eMacEncoded);
	}
	else
	{
		size_t	len		= str.GetLength();
		m_nBytesCnt		= (len + 2) * sizeof(UCChar);	// 2 extra UCChars reserved for byte marker and 0-term
		m_pBytes		= SDK_NEW Uint8[ m_nBytesCnt ];
		UCChar *pUC		= (UCChar *)m_pBytes;
		pUC[0]			= 0xFEFF;
		str.CopyInto(pUC + 1, m_nBytesCnt/sizeof(UCChar));
	}

	m_valueAsStringType	= EValueAsStringType::String;
}

TXString VWDataSerializerValue::GetDefaultStringRepresentation() const // used for the error cases
{
	TXString	result;
	if ( m_valueAsStringType == EValueAsStringType::Int )
	{
		result.Format( "%d", m_valueAsString.fInt );
	}
	else if ( m_valueAsStringType == EValueAsStringType::Real )
	{
		if ( DoubleIsNearlyZero( m_valueAsString.fReal ) )
		{
			result = "0.0";
		}
		else
		{
			result.Format( "%f", m_valueAsString.fReal );
		}
	}
	else if ( m_valueAsStringType == EValueAsStringType::String )
	{
		if ( m_nBytesCnt > 0 && m_pBytes )
		{
			if (m_nBytesCnt > 1 && ((UCChar*)m_pBytes)[0] == 0xFEFF)
				result = TXString( ((const UCChar*)m_pBytes) + 1 );
			else
				result = TXString( (const char*) m_pBytes, m_nBytesCnt-1, ETXEncoding::eMacEncoded );
		}
	}
	else
	{
		if ( m_nBytesCnt == 0 || m_pBytes == nullptr )
		{
			result = "0";
		}
		else
		{
			result		= "0x";

			TXString	thisValue;
			for(size_t i=0; i<m_nBytesCnt; i++) {
				thisValue.Format( "%X", m_pBytes[i] );
				result	+= thisValue;
			}
		}
	}

	return result;
}

VWDataSerializerValue::operator Sint8() const
{
	Sint32	commonValue	= this->GetSIntValue();
	Sint8	value		= ::DemoteTo<Sint8>( kVStanev, commonValue );
	return value;
}

VWDataSerializerValue::operator Uint8() const
{
	Uint32	commonValue	= this->GetUIntValue();
	Uint8	value		= ::DemoteTo<Uint8>( kVStanev, commonValue );
	return value;
}

VWDataSerializerValue::operator Sint16() const
{
	Sint32	commonValue	= this->GetSIntValue();
	Sint16	value		= ::DemoteTo<Sint16>( kVStanev, commonValue );
	return value;
}

VWDataSerializerValue::operator Uint16() const
{
	Uint32	commonValue	= this->GetUIntValue();
	Uint16	value		= ::DemoteTo<Uint16>( kVStanev, commonValue );
	return value;
}

VWDataSerializerValue::operator Sint32() const
{
	Sint32	commonValue	= this->GetSIntValue();
	return commonValue;
}

VWDataSerializerValue::operator Uint32() const
{
	Uint32	commonValue	= this->GetUIntValue();
	return commonValue;
}

VWDataSerializerValue::operator Sint64() const
{
	Sint64	value	= 0;
	if ( m_bUnkonwnType )
	{
		value	= this->GetDefaultStringRepresentation().atoi64();
	}
	else
	{
		VWFC_ASSERT( sizeof(Sint64) == m_nBytesCnt );
		if ( sizeof(Sint64) != m_nBytesCnt )
			return this->GetDefaultStringRepresentation().atoi64();

		VWFC_ASSERT( sizeof(double) == sizeof(Sint64) );
		Sint64	bitValue;
		memcpy( & bitValue, m_pBytes, sizeof(Sint64) );

		memcpy( & value, & bitValue, sizeof(Sint64) );

		Sint64	swappedValue	= VWFC::Tools::SwapBytes( value );
		if ( m_context.fByteSwap == -1 )		// context says nothing.
		{
			value				= ( std::abs(swappedValue) < std::abs(value) ) ? swappedValue : value;
		}
		else if ( m_context.fByteSwap == 0 )	// context says to use the swapped value.
		{
			value				= swappedValue;
		}
	}
	return value;
}

VWDataSerializerValue::operator double() const
{
	double	value	= 0;
	if ( m_bUnkonwnType )
	{
		value	= this->GetDefaultStringRepresentation().atof();
	}
	else
	{
		VWFC_ASSERT( sizeof(double) == m_nBytesCnt );
		if ( sizeof(double) != m_nBytesCnt )
			return this->GetDefaultStringRepresentation().atof();

		VWFC_ASSERT( sizeof(double) == sizeof(Uint64) );
		Uint64	bitValue;
		memcpy( & bitValue, m_pBytes, sizeof(double) );

		// XXX Bobi:
		// As the result of 'memcpy' between 'double data' and 'Uint64 bitValue' doesn't preserve the "swapping monotonity"
		// (i.e. if ('data' <= SwapBytes('data')), doesn't mean that ('bitValue' <= SwapBytes('bitValue')) and vice versa),
		// then the validity of the swapping criteria in the function 'EnsureSwappedBytes' is not guaranteed.
		// Therefore, 'EnsureSwappedBytes' is not called in the function 'SetValue(double data)'. Accordingly, do not be call it here too.
		//
		//bitValue		= /*static*/ ::EnsureSwappedBytes( bitValue, m_context, eDataSerializerSwapContext_Read );

		memcpy( & value, & bitValue, sizeof(double) );

		// XXX Bobi:
		// Special case: Ensuring swapped bytes when reading a 'double' value.
		// This is the only way to work with broken byte order in old documents.
		// Note that the context is not changed.
		double	swappedValue	= VWFC::Tools::SwapBytes( value );
		if ( m_context.fByteSwap == -1 )		// context says nothing.
		{
			value				= ( std::abs( (int)swappedValue ) < std::abs( (int)value ) ) ? swappedValue : value;
		}
		else if ( m_context.fByteSwap == 0 )	// context says to use the swapped value.
		{
			value				= swappedValue;
		}
	}
	return value;
}

VWDataSerializerValue::operator TXString() const
{
	if ( m_bUnkonwnType )
	{
		return this->GetDefaultStringRepresentation();
	}
	else if (m_nBytesCnt > 1 && ((UCChar*)m_pBytes)[0] == 0xFEFF)
	{
		return TXString( ((const UCChar*)m_pBytes) + 1 );
	}
	else
	{
		return TXString( (char*) m_pBytes, m_nBytesCnt-1, ETXEncoding::eMacEncoded );
	}
}

size_t VWDataSerializerValue::GetBytesCount() const
{
	return m_nBytesCnt;
}

const void* VWDataSerializerValue::GetBytes() const
{
	return m_pBytes;
}

Sint32 VWDataSerializerValue::GetSIntValue() const
{
	Sint32	value	= 0;
	if ( m_bUnkonwnType )
	{
		value	= this->GetDefaultStringRepresentation().atoi();
	}
	else
	{
		if ( m_arrEnumValues.size() > 0 )
		{
			// check for enum
			TXString	strValue;
			if (m_nBytesCnt > 1 && ((UCChar*)m_pBytes)[0] == 0xFEFF)
				strValue= TXString( ((const UCChar*)m_pBytes) + 1 );
			else
				strValue = TXString( (const char*) m_pBytes, m_nBytesCnt-1, ETXEncoding::eMacEncoded );

			size_t		len		= m_arrEnumValues.size();
			bool		bFound	= false;
			for(size_t i=0; i<len; i++) {
				const TXString&		enumValue	= m_arrEnumValues[ i ];
				if ( enumValue == strValue ) {
					bFound		= true;
					value		= (Sint32)i; 
					break;
				}
			}
			
			if ( !bFound )
			{
				value = 0;
			}
		}
		else if ( sizeof(Sint8) == m_nBytesCnt ) {
			Sint8*	pValue	= (Sint8*) m_pBytes;
			value			= (Sint32) /*static*/ ::EnsureSwappedBytes( *pValue, m_context, eDataSerializerSwapContext_Read );
		}
		else if ( sizeof(Sint16) == m_nBytesCnt ) {
			Sint16*	pValue	= (Sint16*) m_pBytes;
			value			= (Sint32) /*static*/ ::EnsureSwappedBytes( *pValue, m_context, eDataSerializerSwapContext_Read );
		}
		else if ( sizeof(Sint32) == m_nBytesCnt ) {
			Sint32*	pValue	= (Sint32*) m_pBytes;
			value			= (Sint32) /*static*/ ::EnsureSwappedBytes( *pValue, m_context, eDataSerializerSwapContext_Read );
		}
		else {
			value	= this->GetDefaultStringRepresentation().atoi();

			// not an integer type
			VWFC_ASSERT( false );
		}
	}

	return value;
}

Uint32 VWDataSerializerValue::GetUIntValue() const
{
	Uint32	value	= 0;
	if ( m_bUnkonwnType )
	{
		value	= this->GetDefaultStringRepresentation().atoi();
	}
	else
	{
		if ( m_arrEnumValues.size() > 0 )
		{
			// check for enum
			TXString	strValue;
			if (m_nBytesCnt > 1 && ((UCChar*)m_pBytes)[0] == 0xFEFF)
				strValue= TXString( ((const UCChar*)m_pBytes) + 1 );
			else
				strValue = TXString( (const char*) m_pBytes, m_nBytesCnt-1, ETXEncoding::eMacEncoded );

			size_t		len		= m_arrEnumValues.size();
			bool		bFound	= false;
			for(size_t i=0; i<len; i++) {
				const TXString&		enumValue	= m_arrEnumValues[ i ];
				if ( enumValue == strValue ) {
					bFound		= true;
					value		= (Uint32) i; 
					break;
				}
			}
			
			if ( !bFound )
			{
				value = 0;
			}
		}
		else if ( sizeof(Uint8) == m_nBytesCnt ) {
			Uint8*	pValue	= (Uint8*) m_pBytes;
			value			= (Uint32) /*static*/ ::EnsureSwappedBytes( *pValue, m_context, eDataSerializerSwapContext_Read );
		}
		else if ( sizeof(Uint16) == m_nBytesCnt ) {
			Uint16*	pValue	= (Uint16*) m_pBytes;
			value			= (Uint32) /*static*/ ::EnsureSwappedBytes( *pValue, m_context, eDataSerializerSwapContext_Read );
		}
		else if ( sizeof(Uint32) == m_nBytesCnt ) {
			Uint32*	pValue	= (Uint32*) m_pBytes;
			value			= (Uint32) /*static*/ ::EnsureSwappedBytes( *pValue, m_context, eDataSerializerSwapContext_Read );
		}
		else {
			value	= DemoteTo<Uint32>( kVStanev, this->GetDefaultStringRepresentation().atoi() );

			// not an integer type
			VWFC_ASSERT( false );
		}
	}

	return value;
}

TXString VWDataSerializerValue::GetTXStringValue() const
{
	if ( m_bUnkonwnType )
	{
		return this->GetDefaultStringRepresentation();
	}
	else
	{
		if ( m_nBytesCnt == 0 ) {
			return TXString();
		}
		else if ( m_pBytes[0] == 0 ) {
			return TXString();
		}
		if (m_nBytesCnt > 1 && ((UCChar*)m_pBytes)[0] == 0xFEFF)
			return TXString( ((const UCChar*)m_pBytes) + 1 );
		else { 
			return TXString( (const char*) m_pBytes, m_nBytesCnt-1, ETXEncoding::eMacEncoded );
		}
	}
}

void VWDataSerializerValue::CopyInto(void* pData, size_t size) const
{
	VWFC_ASSERT( m_nBytesCnt <= size );
	if ( m_nBytesCnt > size )
		return;

	memcpy( pData, m_pBytes, size );
}

TXString VWDataSerializerValue::GetValueAsString()
{
	return this->GetDefaultStringRepresentation();
}

void VWDataSerializerValue::SetValueAsString(const TXString& str)
{
	delete [] m_pBytes;
	m_pBytes				= NULL;
	m_nBytesCnt				= 0;

	const char*	szString	= str;
	size_t		len			= str.GetLength();

	bool		bDigits		= false;
	bool		bHasDot		= false;
	for(size_t i=0; i<len; i++) {
		if ( i == 0 )					bDigits	= TXStringExt::IsDigit( szString[i] ) || szString[i] == '-' || szString[i] == '+';
		else if ( szString[i] != '.' )	bDigits	= bDigits && TXStringExt::IsDigit( szString[i] );
		if ( ! bHasDot )				bHasDot	= szString[i] == '.';
	}

	if ( len >= 1 && szString[0] == '0' && szString[1] == 'x' ) {
		VWFC_ASSERT( false );	// NOT TESTED!!!!
		// we have binary data
		bool	switc		= false;
		size_t	dataIndex	= 0;
		Uint8*	arrBytes	= SDK_NEW Uint8[ len ];	// make a little bit more
		for(size_t i=2; i<len; i++) {
			Uint8	data	= 0;
			if ( szString[i] >= '0' && szString[i] <= '9' )			data	= szString[i] - '0';
			else if ( szString[i] >= 'A' && szString[i] <= 'F' )	data	= szString[i] - 'A' + 0x0A;
			else													VWFC_ASSERT( false );

			if ( switc == false ) {
				switc					= true;
				arrBytes[ dataIndex ]	= data;
			}
			else {
				switc					= false;
				arrBytes[ dataIndex ]	= (data << 4) & arrBytes[ dataIndex ];
				dataIndex++;
			}
		}
		// set the data
		this->SetValue( arrBytes, dataIndex );
	}
	else if ( bDigits  ) {
		// we have integer or real
		if ( bHasDot ) {
			double		value	= str.atof();
			this->SetValue( value );
		}
		else {
			Sint32		value	= str.atoi();
			this->SetValue( value );
		}
	}
	else {
		// we have string
		this->SetValue( str );
	}
}
void VWDataSerializerValue::SetValueUnknownType(const TXString& value)
{
	this->SetValueAsString( value );
	m_bUnkonwnType	= true;
}

const TXString& VWDataSerializerValue::GetName() const
{
	return m_name;
}

void VWDataSerializerValue::SetName(const TXString& name)
{
	m_name		= name;
}

void VWDataSerializerValue::SetData(void* pData, size_t size)
{
	m_nBytesCnt		= size;
	m_pBytes		= SDK_NEW Uint8[ m_nBytesCnt ];
	Uint8*	pSource	= (Uint8*) pData;
	for(size_t i=0; i<m_nBytesCnt; i++) {
		m_pBytes[i]	= pSource[i];
	}
}

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
VWDataSerializerGroup::VWDataSerializerGroup(VWDataSerializerContext& context, TDataIdentifier id, const char* szName)
	: m_context( context )
{
	m_identifier		= id;
	if ( szName )	m_szName		= szName;
	else			m_szName.Format( "Gr%X", id );
}

VWDataSerializerGroup::~VWDataSerializerGroup()
{
	this->ClearChildGroups();
}


VWDataSerializerContext& VWDataSerializerGroup::GetContext()
{
	return m_context;
}

void VWDataSerializerGroup::AllowSwappedBytesProcessing()
{
	// XXX Bobi:
	// The following allows checking and processing for swapped bytes.

	m_context.fByteSwap		= -1;
}

void VWDataSerializerGroup::ClearChildGroups()
{
	for ( auto pValue : m_arrValues )
	{
		if ( pValue )
			delete pValue;
	}
	m_arrValues.clear();

	for ( auto pChildGroup : m_arrChildGroups )
	{
		if ( pChildGroup )
			delete pChildGroup;
	}
	m_arrChildGroups.clear();
}

VWDataSerializerGroup* VWDataSerializerGroup::CreateChildDataGroup(TDataIdentifier id, const char* szGroupName)
{
	VWDataSerializerGroup*		pNewGroup	= SDK_NEW VWDataSerializerGroup( m_context, id, szGroupName );

	m_arrChildGroups.push_back( pNewGroup );

	return pNewGroup;
}

VWDataSerializerGroup* VWDataSerializerGroup::FindChildDataGroup(TDataIdentifier id, const char* szGroupName) const
{
	VWDataSerializerGroup*	pFound		= NULL;
	for ( auto pGroup : m_arrChildGroups )
	{
		if	(	pGroup != nullptr
			&&	( pGroup->m_identifier == id || ( szGroupName && pGroup->m_szName == szGroupName ) ) )
		{
			pFound	= pGroup;
			break;
		}
	}
	return pFound;
}

void VWDataSerializerGroup::FindChildDataGroups(TDataSerializerGroupsArray& outArray, TDataIdentifier id, const char* szGroupName) const
{
	outArray.clear();
	for ( auto pGroup : m_arrChildGroups )
	{
		if	(	pGroup != nullptr
			&&	( pGroup->m_identifier == id || ( szGroupName && pGroup->m_szName == szGroupName ) ) )
		{
			outArray.push_back( pGroup );
		}
	}
}

size_t VWDataSerializerGroup::GetChildGroupsCount() const
{
	return m_arrChildGroups.size();
}

VWDataSerializerGroup* VWDataSerializerGroup::GetChildGorupAt(size_t index)
{
	return index < m_arrChildGroups.size() ? m_arrChildGroups[ index ] : nullptr;
}

const TXString& VWDataSerializerGroup::GetName() const
{
	return m_szName;
}

TDataIdentifier VWDataSerializerGroup::GetIdentifier() const
{
	return m_identifier;
}

void VWDataSerializerGroup::AddValue(const VWDataSerializerValue& value, size_t index, const char* szValueName)
{
	VWDataSerializerValue*	pValue	= SDK_NEW VWDataSerializerValue( value );

	TXString		valueName;
	if ( szValueName )		valueName	= szValueName;

	pValue->SetName( valueName );

	size_t	len		= m_arrValues.size();
	if ( index == size_t(-1) )
	{
		index	= len;
	}

	for(size_t i=len; i<=index; i++)
		m_arrValues.push_back( NULL );

	// If there is a value at index into m_arrValues, we have to delete it before replacing.
	if ( m_arrValues[index] )
	{
		delete m_arrValues[index];
	}

	m_arrValues[ index ]	= pValue;
}

VWDataSerializerValue* VWDataSerializerGroup::GetValuePtr(size_t index, const char* szValueName) const
{
	VWDataSerializerValue*	pResultValue	= nullptr;

	// first search for the name
	if ( szValueName )
	{
		for ( auto pValue : m_arrValues )
		{
			if ( pValue )
			{
				const TXString&	name	= pValue->GetName();
				if ( !name.IsEmpty() && name == szValueName )
				{
					pResultValue	= pValue;
					break;
				}
			}
		}
	}

	if ( pResultValue == nullptr && index < m_arrValues.size() )
	{
		pResultValue	= m_arrValues[ index ];
	}
	
	return	pResultValue;
}

VWDataSerializerValue VWDataSerializerGroup::GetValue(size_t index, const char* szValueName) const
{
	VWDataSerializerValue*	pValue	= this->GetValuePtr( index, szValueName );
	return	pValue	? ( *pValue )
					: VWDataSerializerValue( m_context, (Sint32) 0 );
}

bool VWDataSerializerGroup::GetValue(size_t index, const char* szValueName, VWDataSerializerValue& outValue) const
{
	VWDataSerializerValue*	pValue	= this->GetValuePtr( index, szValueName );
	outValue = pValue ? ( *pValue ) : VWDataSerializerValue( m_context, (Sint32) 0 );
	return	( pValue != nullptr );
}

bool VWDataSerializerGroup::HasValue(size_t index, const char* szValueName) const
{
	VWDataSerializerValue*	pValue	= this->GetValuePtr( index, szValueName );
	return	( pValue != nullptr );
}

bool VWDataSerializerGroup::ResetValueString(size_t index, const char* szValueName)
{
	VWDataSerializerValue*	pValue	= this->GetValuePtr( index, szValueName );
	if ( pValue )
	{
		pValue->SetValue( pValue->GetTXStringValue() );
	}
	return	( pValue != nullptr );
}

bool VWDataSerializerGroup::IsGroupIdentifier(TDataIdentifier id)
{
	return m_identifier == id;
}

VWDataSerializerGroup* VWDataSerializerGroup::GetChildGroup(TDataIdentifier id, const char* szGroupName)
{
	VWDataSerializerGroup*	pFound	= nullptr;
	for ( auto pChild : m_arrChildGroups )
	{
		if	(	pChild != nullptr
			&&	( pChild->GetIdentifier() == id || ( szGroupName && pChild->GetName() == szGroupName ) ) )
		{
			pFound	= pChild;
			break;
		}
	}
	
	return pFound;
}

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
VWDataSerializer::VWDataSerializer(const char* szSerializerName)
{
	m_pMainGroup		= SDK_NEW VWDataSerializerGroup( m_context, 0, szSerializerName ? szSerializerName : "MainGroup" );
}

VWDataSerializer::~VWDataSerializer()
{
	this->ClearChildGroups();
	delete m_pMainGroup;
	m_pMainGroup		= NULL;
}

VWDataSerializerContext& VWDataSerializer::GetContext()
{
	return m_context;
}

void VWDataSerializer::AllowSwappedBytesProcessing()
{
	// XXX Bobi:
	// The following allows checking and processing for swapped bytes.

	m_context.fByteSwap		= -1;
}

void VWDataSerializer::SaveStringsInMacEncoding()
{
	m_context.fSaveStringsInMacEncoding = true;
}

void VWDataSerializer::SaveWithSwapBytes()
{
	m_context.fSaveWithSwapBytes = true;
}

void VWDataSerializer::ClearChildGroups()
{
	m_pMainGroup->ClearChildGroups();
}

VWDataSerializerGroup* VWDataSerializer::CreateChildDataGroup(TDataIdentifier id, const char* szGroupName)
{
	return m_pMainGroup->CreateChildDataGroup( id, szGroupName );
}

VWDataSerializerGroup* VWDataSerializer::FindChildDataGroup(TDataIdentifier id, const char* szGroupName) const
{
	return m_pMainGroup->FindChildDataGroup( id, szGroupName );
}

void VWDataSerializer::FindChildDataGroups(TDataSerializerGroupsArray& outArray, TDataIdentifier id, const char* szGroupName) const
{
	m_pMainGroup->FindChildDataGroups( outArray, id, szGroupName );
}

size_t VWDataSerializer::GetChildGroupsCount() const
{
	return m_pMainGroup ? m_pMainGroup->GetChildGroupsCount() : 0;
}

VWDataSerializerGroup* VWDataSerializer::GetChildGorupAt(size_t index)
{
	return m_pMainGroup ? m_pMainGroup->GetChildGorupAt( index ) : nullptr;
}

size_t VWDataSerializer::SaveDataInMemoryReq(IWriteContext* context, Uint8* pData) const
{
	Uint8*			pDataID		= pData;
	Uint8*			pChunkSize	= pDataID + sizeof(TDataIdentifier);
	Uint8*			pValueData	= pChunkSize + sizeof(Uint32);

	// vlado: we must do that! I hate it, but i dont want to remove the 'const' from the function
	VWDataSerializerContext*	serializerContext = (VWDataSerializerContext*) & m_context;
	
	for(size_t i=0; true; i++) {
		bool hasValue = context->ValueBegin( i );
		if ( ! hasValue )
			break;

		Uint8*			pThisValueSize	= pValueData;
		pValueData						+= sizeof(Uint32);

		Uint32	bytesCnt	= context->ValueGetByteCnt();
		if ( bytesCnt > 0 ) {
			Uint32		origByteCnt	= bytesCnt;
			if ( pData ) {
				bytesCnt			= /*static*/ ::EnsureSwappedBytes( origByteCnt, *serializerContext, eDataSerializerSwapContext_Write );

				memcpy( pThisValueSize, & bytesCnt, sizeof(Uint32) );
				context->ValueCopyInto( pValueData, origByteCnt );
			}

			pValueData		+= origByteCnt;
		}
		else {
			if ( pData ) {
				Uint32	bytesCnt	= 1;
				memcpy( pThisValueSize, & bytesCnt, sizeof(Uint32) );

				char	byte	= 0;
				memcpy( pValueData, &byte, 1 );
			}

			pValueData		+= 1;	// no data
		}
	}
	if ( pData ) {
		Uint32	bytesEnd	= 0;
		memcpy( pValueData, & bytesEnd, sizeof(Uint32) );
	}
	pValueData		+= sizeof(Uint32);

	for(size_t i=0; true; i++) {
		bool hasSubGroup = context->GroupBegin( i );
		if ( ! hasSubGroup )
			break;

		size_t	size	= this->SaveDataInMemoryReq( context, pData ? pValueData : NULL );

		context->GroupEnd( i );

		pValueData		+=  size;
	}

	size_t	chunkSize		= pValueData - pData;

	if ( pData ) {
		TDataIdentifier	id			= context->GroupGetID();
		id							= /*static*/ ::EnsureSwappedBytes( id, *serializerContext, eDataSerializerSwapContext_Write );
		memcpy( pDataID, & id, sizeof(TDataIdentifier) );

		Uint32			size		= (Uint32) chunkSize; 
		size						= /*static*/ ::EnsureSwappedBytes( size, *serializerContext, eDataSerializerSwapContext_Write );
		memcpy( pChunkSize, & size, sizeof(Uint32) );
	}

	return chunkSize;
}

bool VWDataSerializer::ReadDataFromMemoryReq(IReadContext* context, Uint8* pData, size_t datasize)
{
#define CHECK_CAN_READ_BYTES(bytes)	if ( size_t(pReadData - pData + bytes) > datasize ) return false;

	TDataIdentifier		id;
	size_t				chunkSize		= 0;
	Uint32				size = 0;

	Uint8*				pReadData		= pData;

	CHECK_CAN_READ_BYTES( sizeof(TDataIdentifier) );
	memcpy( & id, pReadData, sizeof(TDataIdentifier) );
	id				= /*static*/ ::EnsureSwappedBytes( id, m_context, eDataSerializerSwapContext_Read );
	pReadData		+= sizeof(TDataIdentifier);

	CHECK_CAN_READ_BYTES( sizeof(Uint32) );
	memcpy( & size, pReadData, sizeof(Uint32) );
	chunkSize		= /*static*/ ::EnsureSwappedBytes( size, m_context, eDataSerializerSwapContext_Read );
	pReadData		+= sizeof(Uint32);

	context->BeginGroup( id, NULL );

	size_t	valuesCnt	= 0;
	while( true ) {
		Uint32		bytesCnt	= 0;

		CHECK_CAN_READ_BYTES( sizeof(Uint32) );
		memcpy( & bytesCnt, pReadData, sizeof(Uint32) );
		bytesCnt		= /*static*/ ::EnsureSwappedBytes( bytesCnt, m_context, eDataSerializerSwapContext_Read );
		pReadData		+= sizeof(Uint32);
		if ( bytesCnt == 0 )
			break;

		CHECK_CAN_READ_BYTES( bytesCnt );
		if ( context->AddValue( m_context, (void*) pReadData, bytesCnt, valuesCnt, NULL ) == false )
		{
			// force exit!
			return false;
		}

		valuesCnt++;

		pReadData		+= bytesCnt;
	}

	size_t		currSize		= pReadData - pData;
	if ( currSize > chunkSize )		return false;

	size_t		childChunksSize	= chunkSize - currSize;
	while( childChunksSize > 0 ) {
		size	= 0;
		CHECK_CAN_READ_BYTES( sizeof(TDataIdentifier) );
		memcpy( & size, pReadData + sizeof(TDataIdentifier), sizeof(Uint32) );
		size		= /*static*/ ::EnsureSwappedBytes( size, m_context, eDataSerializerSwapContext_Read );

		// there were case where the data was saved with some ridiculous size
		// we want to filter it and not allow it to crash
		if ( ! VERIFYN( kVStanev, size <= childChunksSize && size <= datasize) )
			return false;
        
		if ( ! this->ReadDataFromMemoryReq( context, pReadData, size ) ) 
			return false;

		if ( childChunksSize < size )	return false;
		childChunksSize	-= size; 

		pReadData		+= size;
	}
#undef CHECK_CAN_READ_BYTES

	context->EndGroup( id, NULL );

	return true;
}

void VWDataSerializer::SaveDataInVWSettingsReq(VWDataSerializerGroup* pGroup, const TXString& category) const
{
	typedef std::unordered_map<TXString, size_t>		TNameMap;
	TNameMap	mapUsedNames;

	size_t	valueCnt		= pGroup->m_arrValues.size();
	for(size_t i=0; i<valueCnt; i++) {
		VWDataSerializerValue*	pValue	= pGroup->m_arrValues[i];

		TXString		valueName		= pValue->GetName();
		TXString		valueContent	= pValue->GetValueAsString();

		::GS_SetSavedSetting( gCBP, category, valueName, valueContent );
	}

	size_t	groupCnt		= pGroup->m_arrChildGroups.size();
	for(size_t i=0; i<groupCnt; i++) {
		VWDataSerializerGroup*	pChildGroup	= pGroup->m_arrChildGroups[i];

		TXString	childName		= pChildGroup->GetName();

		TNameMap::iterator	it		= mapUsedNames.find( childName );
		if ( it != mapUsedNames.end() ) {
			size_t&	index	= it->second;
			index++;

			TXString	arrIndex;
			arrIndex.Format( "%d", index );

			childName		+= arrIndex;
		}
		else {
			mapUsedNames.insert( TNameMap::value_type( childName, 0 ) );
		}

		TXString	childCategory	= category;
		childCategory				+= "/";
		childCategory				+= childName;
		this->SaveDataInVWSettingsReq( pChildGroup, childCategory );
	}
}

bool VWDataSerializer::ReadDataFromVWSettingsReq(VWDataSerializerGroup* pGroup, const TXString& category)
{
	typedef std::unordered_map<TXString, size_t>		TNameMap;
	TNameMap	mapUsedNames;

	size_t	valueCnt		= pGroup->m_arrValues.size();
	for(size_t i=0; i<valueCnt; i++) {
		VWDataSerializerValue*	pValue	= pGroup->m_arrValues[i];
		if ( pValue ) {
			TXString		valueName		= pValue->GetName();

			TXString			value;
			if ( ::GS_GetSavedSetting( gCBP, category, valueName, value ) ) {
				pValue->SetValueAsString( value );
			}
		}
	}

	size_t	groupCnt		= pGroup->m_arrChildGroups.size();
	for(size_t i=0; i<groupCnt; i++) {
		VWDataSerializerGroup*	pChildGroup	= pGroup->m_arrChildGroups[i];
		TXString	childName		= pChildGroup->GetName();

		TNameMap::iterator	it		= mapUsedNames.find( childName );
		if ( it != mapUsedNames.end() ) {
			size_t&	index	= it->second;
			index++;

			TXString	arrIndex;
			arrIndex.Format( "%d", index );

			childName		+= arrIndex;
		}
		else {
			mapUsedNames.insert( TNameMap::value_type( childName, 0 ) );
		}

		TXString	childCategory	= category;
		childCategory				+= "/";
		childCategory				+= childName;
		this->ReadDataFromVWSettingsReq( pChildGroup, childCategory );
	}

	return true;
}

void VWDataSerializer::SaveDataInXMLSettingsReq(IXMLFileNodePtr xmlNode, VWDataSerializerGroup* pGroup) const
{
	typedef std::unordered_map<TXString, size_t>		TNameMap;
	TNameMap	mapUsedNames;

	IXMLFileNodePtr		childNode;

	size_t	valueCnt		= pGroup->m_arrValues.size();
	for(size_t i=0; i<valueCnt; i++)
	{
		VWDataSerializerValue*	pValue	= pGroup->m_arrValues[i];

		TXString		valueName		= pValue->GetName();
		TXString		valueContent	= pValue->GetValueAsString();

		if ( VERIFYN( kVStanev, VCOM_SUCCEEDED( xmlNode->CreateChildNode( valueName, & childNode ) ) ) )
		{
			childNode->SetNodeValue( valueContent );
		}
	}

	size_t	groupCnt		= pGroup->m_arrChildGroups.size();
	for(size_t i=0; i<groupCnt; i++)
	{
		VWDataSerializerGroup*	pChildGroup	= pGroup->m_arrChildGroups[i];

		TXString	childName		= pChildGroup->GetName();

		if ( VERIFYN( kVStanev, VCOM_SUCCEEDED( xmlNode->CreateChildNode( childName, & childNode ) ) ) )
		{
			TNameMap::iterator	it		= mapUsedNames.find( childName );
			if ( it != mapUsedNames.end() )
			{
				size_t&	index	= it->second;
				index++;

				TXString	arrIndex;
				arrIndex.Format( "%d", index );

				childName		+= arrIndex;
			}
			else
			{
				mapUsedNames.insert( TNameMap::value_type( childName, 0 ) );
			}

			this->SaveDataInXMLSettingsReq( childNode, pChildGroup );
		}
	}
}

bool VWDataSerializer::ReadDataFromXMLSettingsReq(IXMLFileNodePtr xmlNode, VWDataSerializerGroup* pGroup)
{
	TXString			nodeName;
	xmlNode->GetNodeName( nodeName );

	IXMLFileNodePtr		childNode;
	if ( VCOM_SUCCEEDED( xmlNode->GetFirstChildNode( & childNode ) ) )
	{
		VWDataSerializerGroup*	pNewGroup	= m_pMainGroup;
		if ( pGroup )
		{
			pNewGroup		= pGroup->CreateChildDataGroup( 0, nodeName );
		}

		IXMLFileNodePtr	nextNode;
		while ( childNode )
		{
			this->ReadDataFromXMLSettingsReq( childNode, pNewGroup );

			childNode->GetNextSiblingNode( & nextNode );
			childNode	= nextNode;
		}
	}
	else
	{
		TXString	strValue;
		if ( VCOM_SUCCEEDED( xmlNode->GetNodeValue( strValue ) ) )
		{
			VWDataSerializerValue	value( m_context, strValue );
			value.SetValueUnknownType( strValue );
			pGroup->AddValue( value, size_t(-1), nodeName );
		}
	}

	return true;
}

namespace VWFC
{
	namespace Tools
	{
		class CWriteFromMemoryContext : public VWDataSerializer::IWriteContext
		{
		public:
			CWriteFromMemoryContext(VWDataSerializerGroup* mainGroup)
			{
				farrGroupStack.push_back( mainGroup );
			}

			virtual ~CWriteFromMemoryContext()
			{
			}

			virtual bool	GroupBegin(size_t iGroup)
			{
				bool result = false;

				const VWDataSerializerGroup* topGroup = farrGroupStack.back();
				if ( iGroup < topGroup->m_arrChildGroups.size() )
				{
					farrGroupStack.push_back( topGroup->m_arrChildGroups[iGroup] );
					result = true;
				}

				return result;
			}
	
			virtual void	GroupEnd(size_t)
			{
				farrGroupStack.pop_back();
			}

			virtual TDataIdentifier	GroupGetID()
			{
				const VWDataSerializerGroup* topGroup = farrGroupStack.back();
				return topGroup->m_identifier;
			}

			virtual bool	ValueBegin(size_t iValue)
			{
				bool result = false;

				const VWDataSerializerGroup* topGroup = farrGroupStack.back();
				if ( iValue < topGroup->m_arrValues.size() )
				{
					farrValuesStack.push_back( topGroup->m_arrValues[iValue] );
					result = true;
				}

				return result;
			}

			virtual void	ValueEnd(size_t )
			{
				farrValuesStack.pop_back();
			}

			virtual Uint32	ValueGetByteCnt()
			{
				const VWDataSerializerValue* topValue = farrValuesStack.back();
				return topValue == nullptr ? 0 : (Uint32)topValue->m_nBytesCnt;
			}

			virtual void	ValueCopyInto(void* dst, size_t dstSize)
			{
				const VWDataSerializerValue* topValue = farrValuesStack.back();
				memcpy( dst, topValue->m_pBytes, dstSize );
			}

		private:
			std::vector<VWDataSerializerGroup*>	farrGroupStack;
			std::vector<VWDataSerializerValue*>	farrValuesStack;
		};
	}
}

size_t VWDataSerializer::GetDataBytesCount() const
{
	CWriteFromMemoryContext context( m_pMainGroup );
	return this->SaveDataInMemoryReq( & context, NULL );
}

void VWDataSerializer::SaveDataInMemory(void* pData) const
{
	CWriteFromMemoryContext context( m_pMainGroup );
	this->SaveDataInMemoryReq( & context, (Uint8*) pData );
}

size_t VWDataSerializer::GetDataBytesCount(IWriteContext* writeContext) const
{
	return this->SaveDataInMemoryReq( writeContext, NULL );
}

void VWDataSerializer::SaveDataInMemory(void* pData, IWriteContext* writeContext) const
{
	this->SaveDataInMemoryReq( writeContext, (Uint8*) pData );
}

namespace VWFC
{
	namespace Tools
	{
		class CReadFromMemoryContext : public VWDataSerializer::IReadContext
		{
		public:
			CReadFromMemoryContext(VWDataSerializerGroup* mainGroup)
				: fMainGroup( mainGroup )
			{
			}

			virtual ~CReadFromMemoryContext()
			{
			}

			virtual void BeginGroup(TDataIdentifier id, const char* szGroupName)
			{
				VWDataSerializerGroup*	group		= NULL;
				if ( fGroupStack.size() > 0 )
				{
					group = fGroupStack.back();
				}

				VWDataSerializerGroup*	newGroup	= fMainGroup;
				if ( group )
				{
					newGroup	= group->CreateChildDataGroup( id, szGroupName );
				}

				fGroupStack.push_back( newGroup );
			}

			virtual void EndGroup(TDataIdentifier id, const char* szGroupName)
			{
				fGroupStack.pop_back();
			}

			virtual bool AddValue(VWDataSerializerContext& context, void* buffer, size_t bufferSize, size_t index, const char* szValueName)
			{
				if ( VERIFYN( kVStanev, fGroupStack.size() > 0 ) )
				{
					VWDataSerializerGroup*	newGroup	= fGroupStack.back();

					VWDataSerializerValue	value( context, buffer, bufferSize );
					newGroup->AddValue( value, index, szValueName );
				}
				return true;
			}

		private:
			VWDataSerializerGroup*		fMainGroup;

			TDataSerializerGroupsArray	fGroupStack;
		};
	}
}

bool VWDataSerializer::ReadDataFromMemory(void* pData, size_t size)
{
	this->ClearChildGroups();

	CReadFromMemoryContext	context( m_pMainGroup );

	bool		ok = true;
	if ( ! this->ReadDataFromMemoryReq( & context, (Uint8*) pData, size ) ) {
		ok		= false;
		m_pMainGroup->ClearChildGroups();
	}

	return ok;
}

bool VWDataSerializer::ReadDataFromMemory(void* pData, size_t size, IReadContext* readContext)
{
	return this->ReadDataFromMemoryReq( readContext, (Uint8*) pData, size );
}

void VWDataSerializer::SaveDataInVWSettings() const
{
	this->SaveDataInVWSettingsReq( m_pMainGroup, m_pMainGroup->GetName() );
}

bool VWDataSerializer::ReadDataFromVWSettings()
{
	bool		ok = true;
	if ( ! this->ReadDataFromVWSettingsReq( m_pMainGroup, m_pMainGroup->GetName() ) ) {
		ok		= false;
		m_pMainGroup->ClearChildGroups();
	}

	return ok;
}

void VWDataSerializer::SaveDataInXMLSettings(IFileIdentifierPtr fileID) const
{
	IXMLFilePtr	xmlFile( IID_XMLFile );
	if ( VCOM_SUCCEEDED( xmlFile->CreateNew( m_pMainGroup->GetName() ) ) )
	{
		IXMLFileNodePtr	rootNode;
		xmlFile->GetRootNode( & rootNode );
		if ( rootNode )
		{
			this->SaveDataInXMLSettingsReq( rootNode, m_pMainGroup );

			xmlFile->WriteFile( fileID, eXMLEncoding_UTF8 );
		}
	}
}

bool VWDataSerializer::ReadDataFromXMLSettings(IFileIdentifierPtr fileID)
{
	bool		ok = false;

	IXMLFilePtr	xmlFile( IID_XMLFile );
	if ( VCOM_SUCCEEDED( xmlFile->ReadFile( fileID ) ) )
	{
		IXMLFileNodePtr	rootNode;
		xmlFile->GetRootNode( & rootNode );
		if ( rootNode )
		{
			TXString		rootNodeName;
			rootNode->GetNodeName( rootNodeName );

			if ( VERIFYN( kVStanev, rootNodeName == m_pMainGroup->GetName() ) )
			{
				ok = true;
				m_pMainGroup->ClearChildGroups();

				IXMLFileNodePtr		childNode;
				if ( VCOM_SUCCEEDED( rootNode->GetFirstChildNode( & childNode ) ) )
				{
					IXMLFileNodePtr	nextNode;
					while ( childNode )
					{
						if ( ! this->ReadDataFromXMLSettingsReq( childNode, m_pMainGroup ) ) {
							ok		= false;
							m_pMainGroup->ClearChildGroups();
							break;
						}

						childNode->GetNextSiblingNode( & nextNode );
						childNode	= nextNode;
					}
				}
			}
		}
	}

	return ok;
}

namespace VWFC
{
	namespace Tools
	{
		class CDataSerializerString : public IXMLFileIOBuffer
		{
		public:
						CDataSerializerString();
						CDataSerializerString(const TXString& src);
			virtual		~CDataSerializerString();

			const TXString&	GetData() const;

			virtual	VCOMError VCOM_CALLTYPE	GetDataSize(size_t& outSize);
			virtual VCOMError VCOM_CALLTYPE	CopyDataInto(void* pBuffer, size_t bufferSize);
			virtual VCOMError VCOM_CALLTYPE	SetData(void* pBuffer, size_t bufferSize);

		private:
			const TXString&		fSource;
			TXString			fData;
		};
	}
}

// ----------------------------------------------------------------------------------------------------------------
CDataSerializerString::CDataSerializerString()
	: fSource( fData )
{
}

CDataSerializerString::CDataSerializerString(const TXString& src)
	: fSource( src )
{
}

CDataSerializerString::~CDataSerializerString()
{
}

const TXString&	CDataSerializerString::GetData() const
{
	return fData;
}

VCOMError CDataSerializerString::GetDataSize(size_t& outSize)
{
	outSize	= fSource.GetLength();
	return kVCOMError_NoError;
}

VCOMError CDataSerializerString::CopyDataInto(void* pBuffer, size_t bufferSize)
{
	size_t	srcLen	= fSource.GetLength();
	memcpy( pBuffer, (const char*) fSource, (srcLen < bufferSize ? srcLen : bufferSize) );
	return kVCOMError_NoError;
}

VCOMError CDataSerializerString::SetData(void* pBuffer, size_t bufferSize)
{
	fData	+= TXString( (const char*) pBuffer, bufferSize );
	return kVCOMError_NoError;
}

// ----------------------------------------------------------------------------------------------------------------
bool VWDataSerializer::SaveDataInXMLString(TXString& outData) const
{
	bool	ok	= false;

	IXMLFilePtr	xmlFile( IID_XMLFile );
	if ( VCOM_SUCCEEDED( xmlFile->CreateNew( m_pMainGroup->GetName() ) ) )
	{
		IXMLFileNodePtr	rootNode;
		xmlFile->GetRootNode( & rootNode );
		if ( rootNode )
		{
			this->SaveDataInXMLSettingsReq( rootNode, m_pMainGroup );

			CDataSerializerString	buffer;
			if ( VCOM_SUCCEEDED( xmlFile->WriteBuffer( & buffer, eXMLEncoding_UTF8 ) ) )
			{
				outData	= buffer.GetData();
				ok	= true;
			}
		}

	}
	return ok;
}

bool VWDataSerializer::ReadDataFromXMLString(const TXString& data)
{
	bool		ok = false;

	CDataSerializerString	buffer( data );

	IXMLFilePtr	xmlFile( IID_XMLFile );
	if ( VCOM_SUCCEEDED( xmlFile->ReadBuffer( & buffer, eXMLEncoding_UTF8 ) ) )
	{
		IXMLFileNodePtr	rootNode;
		xmlFile->GetRootNode( & rootNode );
		if ( rootNode )
		{
			TXString		rootNodeName;
			rootNode->GetNodeName( rootNodeName );

			if ( VERIFYN( kVStanev, rootNodeName == m_pMainGroup->GetName() ) )
			{
				ok = true;
				m_pMainGroup->ClearChildGroups();

				IXMLFileNodePtr		childNode;
				if ( VCOM_SUCCEEDED( rootNode->GetFirstChildNode( & childNode ) ) )
				{
					IXMLFileNodePtr	nextNode;
					while ( childNode )
					{
						if ( ! this->ReadDataFromXMLSettingsReq( childNode, m_pMainGroup ) ) {
							ok		= false;
							m_pMainGroup->ClearChildGroups();
							break;
						}

						childNode->GetNextSiblingNode( & nextNode );
						childNode	= nextNode;
					}
				}
			}
		}
	}

	return ok;
}


void VWDataSerializer::SaveDataInBinaryFile(VectorWorks::Filing::IFileIdentifierPtr fileID) const
{
	VectorWorks::Filing::IRawOSFilePtr	rawFile( VectorWorks::Filing::IID_RawOSFile );
	if ( rawFile && VCOM_SUCCEEDED( rawFile->Open( fileID, false, true, false, true ) ) )
	{
		size_t		fileSize	= this->GetDataBytesCount();
		if ( fileSize > 0 )
		{
			try
			{
				char*		fileBuffer	= SDK_NEW char[ fileSize + 1 ];
				this->SaveDataInMemory( fileBuffer );

				rawFile->Write( 0, fileSize, fileBuffer );

				delete [] fileBuffer;
			}
			catch ( ... )
			{
			}
		}

		rawFile->Close();
	}
}

bool VWDataSerializer::ReadDataInBinaryFile(VectorWorks::Filing::IFileIdentifierPtr fileID)
{
	bool	result	= false;

	VectorWorks::Filing::IRawOSFilePtr	rawFile( VectorWorks::Filing::IID_RawOSFile );
	if ( rawFile && VCOM_SUCCEEDED( rawFile->Open( fileID, true, false, false, false ) ) )
	{
		Uint64		fileSizeU	= 0;
		rawFile->GetFileSize( fileSizeU );

		if ( fileSizeU < size_t(-1) )
		{
			size_t	fileSize	= (size_t)( fileSizeU );
			try 
			{
				char*		fileBuffer	= SDK_NEW char[ fileSize + 1 ];
				rawFile->Read( 0, fileSizeU, fileBuffer );

				fileSize	= (size_t)( fileSizeU );
				result		= this->ReadDataFromMemory( fileBuffer, fileSize );

				delete [] fileBuffer;
			}
			catch (... )
			{
			}
		}

		rawFile->Close();
	}

	return result;
}

