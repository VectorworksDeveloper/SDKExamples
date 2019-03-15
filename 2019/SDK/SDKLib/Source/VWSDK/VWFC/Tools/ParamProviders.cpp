//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VWFC::VWObjects;
using namespace VWFC::Math;

// --------------------------------------------------------------------------------------------------------
CParamProviderAbstract::CParamProviderAbstract()
{
}

CParamProviderAbstract::~CParamProviderAbstract()
{
}

// ---------------------------------------------------------------------------------------------------
// Process boolean parmeter
// ---------------------------------------------------------------------------------------------------
void CParamProviderAbstract::ProcessParameter(bool bRead, bool& inOutValue, bool oldValue, const char* szParamName)
{
	this->ProcessParameter( bRead, inOutValue, oldValue, this->GetParamIndex( szParamName ) );
}

void CParamProviderAbstract::ProcessParameter(bool bRead, bool& inOutValue, bool oldValue, size_t paramIndex)
{
	if ( bRead ) {
		inOutValue			= this->GetParamBool( paramIndex );
	}
	else if ( oldValue != inOutValue )  {
		this->SetParamBool( paramIndex, inOutValue );
	}
}

// ---------------------------------------------------------------------------------------------------
// Process Sint32 parameter
// ---------------------------------------------------------------------------------------------------
void CParamProviderAbstract::ProcessParameter(bool bRead, Uint32& inOutValue, Uint32 oldValue, const char* szParamName)
{
	this->ProcessParameter( bRead, inOutValue, oldValue, this->GetParamIndex( szParamName ) );
}

void CParamProviderAbstract::ProcessParameter(bool bRead, Uint32& inOutValue, Uint32 oldValue, size_t paramIndex)
{
	if ( bRead ) {
		inOutValue			= this->GetParamLong( paramIndex );
	}
	else if ( oldValue != inOutValue )  {
		this->SetParamLong( paramIndex, inOutValue );
	}
}

// ---------------------------------------------------------------------------------------------------
// Process Line style parameter (converts to/from pseudo-index/line type as needed
// ---------------------------------------------------------------------------------------------------

void CParamProviderAbstract::ProcessParameterLineStyle(bool bRead, Sint32& inOutValue, Sint32 oldValue, size_t paramIndex, const TMultiplePseudoDashIndexConverter& converter)
{
	if (bRead) {
		inOutValue = converter.GetDashLineTypeFromPseudoDashIndex(this->GetParamLong(paramIndex));
	}
	else if (oldValue != inOutValue) {
		this->SetParamLong(paramIndex, converter.GetPseudoDashIndexFromDashLineType(inOutValue));
	}
}

// ---------------------------------------------------------------------------------------------------
// Process Sint32 parameter
// ---------------------------------------------------------------------------------------------------
void CParamProviderAbstract::ProcessParameter(bool bRead, Sint32& inOutValue, Uint32 oldValue, const char* szParamName)
{
	this->ProcessParameter( bRead, inOutValue, oldValue, this->GetParamIndex( szParamName ) );
}

void CParamProviderAbstract::ProcessParameter(bool bRead, Sint32& inOutValue, Uint32 oldValue, size_t paramIndex)
{
	if ( bRead ) {
		inOutValue			= this->GetParamLong( paramIndex );
	}
	else if ( oldValue != inOutValue )  {
		this->SetParamLong( paramIndex, inOutValue );
	}
}

// ---------------------------------------------------------------------------------------------------
// Process double parameter
// ---------------------------------------------------------------------------------------------------
void CParamProviderAbstract::ProcessParameter(bool bRead, double& inOutValue, double oldValue, const char* szParamName)
{
	this->ProcessParameter( bRead, inOutValue, oldValue, this->GetParamIndex( szParamName ) );
}

void CParamProviderAbstract::ProcessParameter(bool bRead, double& inOutValue, double oldValue, size_t paramIndex)
{
	if ( bRead ) {
		inOutValue			= this->GetParamReal( paramIndex );
	}
	else if ( ! MathUtils::Equalish( inOutValue, oldValue, VWPoint2D::sEpsilon ) )  {
		this->SetParamReal( paramIndex, inOutValue );
	}
}

// ---------------------------------------------------------------------------------------------------
// Process string parameter
// ---------------------------------------------------------------------------------------------------
void  CParamProviderAbstract::ProcessParameter(bool bRead, TXString& inOutValue, const TXString& oldValue, const char* szParamName)
{
	this->ProcessParameter( bRead, inOutValue, oldValue, this->GetParamIndex( szParamName ) );
}

void CParamProviderAbstract::ProcessParameter(bool bRead, TXString& inOutValue, const TXString& oldValue, size_t paramIndex)
{
	if ( bRead ) {
		inOutValue			= this->GetParamString( paramIndex );
	}
	else if ( oldValue != inOutValue )  {
		this->SetParamString( paramIndex, inOutValue );
	}
}

// ---------------------------------------------------------------------------------------------------
// Process control point parameter, represented by a pair of kFieldCoordLocX and kFieldCoordLocY parameters.
// This functionality doesn't handle the kFieldControlPoint parametric field type.
// ---------------------------------------------------------------------------------------------------
void  CParamProviderAbstract::ProcessParameter(bool bRead, VWPoint2D& inOutValue, const VWPoint2D& oldValue, const char* szParamNameXCoord, const char* szParamNameYCoord)
{
	this->ProcessParameter( bRead, inOutValue, oldValue, this->GetParamIndex( szParamNameXCoord ), this->GetParamIndex( szParamNameYCoord ) );
}

void CParamProviderAbstract::ProcessParameter(bool bRead, VWPoint2D& inOutValue, const VWPoint2D& oldValue, size_t paramIndexXCoord, size_t paramIndexYCoord)
{
	if ( bRead ) {
		inOutValue			= this->GetParamCtrlPt( paramIndexXCoord, paramIndexYCoord );
	}
	else if ( oldValue != inOutValue )  {
		this->SetParamCtrlPt( paramIndexXCoord, paramIndexYCoord, inOutValue );
	}
}

// ---------------------------------------------------------------------------------------------------
// Decode enumeration parameter string from parameter enum values
// ---------------------------------------------------------------------------------------------------
Uint32 CParamProviderAbstract::DecodeEnumString(size_t paramIndex, const TXString& string, Uint32 def) const
{	
	Uint32				result	= def;

	TXStringSTLArray	arrChoices;
	if ( this->GetParamChoices( paramIndex, arrChoices ) ) {
		size_t choicesCnt	= arrChoices.size();
		for(size_t i=0; i<choicesCnt; i++) {
			const TXString&		strChoice	= arrChoices[ i ];
			if ( strChoice == string ) {
				result	= (Uint32) i; 
				break;
			}
		}
	}

	return result;
}

// ---------------------------------------------------------------------------------------------------
// Encode enumeration parameter string from parameter enum values
// ---------------------------------------------------------------------------------------------------
TXString CParamProviderAbstract::EncodeEnumString(size_t paramIndex, Uint32 index, Uint32 def) const
{
	TXString			result;

	TXStringSTLArray	arrChoices;
	if ( this->GetParamChoices( paramIndex, arrChoices ) ) {
		size_t choicesCnt	= arrChoices.size();
		if ( index < choicesCnt ) {
			result	= arrChoices[ index ];
		}
		else if ( def < choicesCnt ) {
			result	= arrChoices[ def ];
		}
	}

	return result;
}

// ---------------------------------------------------------------------------------------------------
// Decode enumeration parameter string from specivied string array
// ---------------------------------------------------------------------------------------------------
Uint32 CParamProviderAbstract::DecodeEnumString(char** arrStrings, const TXString& string, Uint32 def) const
{
	Uint32	result	= def;
	for(size_t i=0; arrStrings && arrStrings[i]; i++) {
		if ( string == arrStrings[i] ) {
			result = (Uint32) i; 
			break;
		}
	}

	return result;
}

// ---------------------------------------------------------------------------------------------------
// Encode enumeration parameter string from specivied string array
// ---------------------------------------------------------------------------------------------------
TXString CParamProviderAbstract::EncodeEnumString(char** arrStrings, Uint32 index, Uint32 defIndex) const
{
	size_t	stringsCount	= 0;
	for(size_t i=0; arrStrings && arrStrings[i]; i++) {
		stringsCount++;
	}

	ASSERTN( kVStanev, defIndex < stringsCount );
	if (index < stringsCount )	return arrStrings[ index ];
	else						return arrStrings[ defIndex ];
}

bool CParamProviderAbstract::ResourceGetParamChoices(MCObjectHandle handle, size_t paramIndex, TXStringSTLArray& outArray) const
{
	outArray.clear();

	// If we get there, there is no Chc object in the resoource with the specified index
	// We try to look for choices using the ParametricProvider

	using namespace VectorWorks::Extension;

	IExtendedPropsPtr		extProps( IID_ExtendedProps );
	CodeRefID				codeRefID		= 0;
	extProps->GetCodeRefID( handle, codeRefID );
	TParametricFileIndex	fileIndex		= 0;
	extProps->GetFileIndex( codeRefID, fileIndex );
	IExtension*				extension		= extProps->GetExtension( fileIndex );
	IEventSinkPtr			eventSink( extension, IID_ParametricParamsProvider );

	// dynamic_cast doesn't work on Mac so we dont use it
	IParametricParamsProvider*	modifProvider	=  (IParametricParamsProvider*)( (IVWUnknown*) eventSink );

	bool ok = false;
	if ( modifProvider ) {
		TXStringArray uniNames,localNames;
		modifProvider->GetParamChoices( paramIndex, uniNames, localNames);

		for(size_t i = 0; i < uniNames.GetSize(); i++){
			outArray.push_back(uniNames[i]);
		}

		ok = true;
	}

	return ok;
}

// --------------------------------------------------------------------------------------------------------
CGenericParamProvider::CGenericParamProvider()
	: fProvider( NULL )
{
}

CGenericParamProvider::CGenericParamProvider(MCObjectHandle hGenericObject)
	: fProvider( NULL )
{
	this->Set( hGenericObject );
}

CGenericParamProvider::CGenericParamProvider(MCObjectHandle hParametricObject, const char* szFormatName)
	: fProvider( NULL )
{
	this->Set( hParametricObject, szFormatName );
}

CGenericParamProvider::CGenericParamProvider(MCObjectHandle hParametricObject, MCObjectHandle hFormat)
	: fProvider( NULL )
{
	this->Set( hParametricObject, hFormat );
}

CGenericParamProvider::~CGenericParamProvider()
{
	if ( fProvider )
	{
		delete fProvider;
		fProvider = NULL;
	}
}

/*static*/ bool CGenericParamProvider::IsGenericObject(MCObjectHandle h)
{
	return		VWFC::VWObjects::VWParametricObj::IsParametricObject( h )
			||	VWFC::VWObjects::VWRecordFormatObj::IsRecordFormatObject( h )
			||	VWFC::VWObjects::VWRecordObj::IsRecordObject( h )
			;
}

void CGenericParamProvider::Set(MCObjectHandle hGenericObject)
{
	if ( VWFC::VWObjects::VWParametricObj::IsParametricObject( hGenericObject ) )
	{
		fProvider	= SDK_NEW CObjectParamProvider( hGenericObject );
	}
	else if ( VWFC::VWObjects::VWRecordFormatObj::IsRecordFormatObject( hGenericObject ) )
	{
		fProvider	= SDK_NEW CFormatParamProvider( hGenericObject );
	}
	else if ( VWFC::VWObjects::VWRecordObj::IsRecordObject( hGenericObject ) )
	{
		fProvider	= SDK_NEW CRecordParamProvider( hGenericObject );
	}
	VWFC_ASSERT( fProvider != NULL );
}

void CGenericParamProvider::Set(MCObjectHandle hParametricObject, const char* szFormatName)
{
	if ( VWFC::VWObjects::VWParametricObj::IsParametricObject( hParametricObject ) )
	{
		fProvider	= SDK_NEW CObjectParamProvider( hParametricObject );
	}
	else
	{
		fProvider	= SDK_NEW CFormatParamProvider( VWRecordFormatObj::GetRecordFormat( szFormatName ) );
	}
	VWFC_ASSERT( fProvider != NULL );
}

void CGenericParamProvider::Set(MCObjectHandle hParametricObject, MCObjectHandle hFormat)
{
	if ( VWFC::VWObjects::VWParametricObj::IsParametricObject( hParametricObject ) )
	{
		fProvider	= SDK_NEW CObjectParamProvider( hParametricObject );
	}
	else
	{
		fProvider	= SDK_NEW CFormatParamProvider( hFormat );
	}
	VWFC_ASSERT( fProvider != NULL );
}

MCObjectHandle CGenericParamProvider::GetObject() const
{
	if ( fProvider )
		return fProvider->GetObject( );
	else
		return nullptr;
}

Sint32 CGenericParamProvider::GetParamLong(const char* szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamLong( szParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamLong(const char* szParamName, Sint32 value)
{
	if ( fProvider )
		fProvider->SetParamLong( szParamName, value );
}

bool CGenericParamProvider::GetParamBool(const char* szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamBool( szParamName );
	else
		return false;
}

void CGenericParamProvider::SetParamBool(const char* szParamName, bool value)
{
	if ( fProvider )
		fProvider->SetParamBool( szParamName, value );
}

double CGenericParamProvider::GetParamReal(const char* szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamReal( szParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamReal(const char* szParamName, double value)
{
	if ( fProvider )
		fProvider->SetParamReal( szParamName, value );
}

TXString CGenericParamProvider::GetParamString(const char* szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamString( szParamName );
	else return "";
}

void CGenericParamProvider::SetParamString(const char* szParamName, const TXString& value)
{
	if ( fProvider )
		fProvider->SetParamString( szParamName, value );
}

VWPoint2D CGenericParamProvider::GetParamCtrlPt(const char* szParamXCoord) const
{
	if ( fProvider )
		return fProvider->GetParamCtrlPt( szParamXCoord );
	else 
		return VWPoint2D( 0 ,0 );
}

void CGenericParamProvider::SetParamCtrlPt(const char* szParamXCoord, const VWPoint2D& value)
{
	if ( fProvider )
		fProvider->SetParamCtrlPt( szParamXCoord, value );
}

TXString CGenericParamProvider::GetParamValue(const char* szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamValue( szParamName );
	else
		return "";
}

void CGenericParamProvider::SetParamValue(const char* szParamName, const TXString& value)
{
	if ( fProvider )
		fProvider->SetParamValue( szParamName, value );
}

size_t CGenericParamProvider::GetParamsCount() const
{
	if ( fProvider )
		return fProvider->GetParamsCount();
	else 
		return 0;
}

EFieldStyle CGenericParamProvider::GetParamStyle(const char* szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamStyle( szParamName );
	else 
		return EFieldStyle::kFieldReal;
}

size_t CGenericParamProvider::GetParamIndex(const char* szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamIndex( szParamName );
	else 
		return 0;
}

TXString CGenericParamProvider::GetParamName(size_t index) const
{
	if ( fProvider )
		return fProvider->GetParamName( index );
	else
		return "";
}

Sint32 CGenericParamProvider::GetParamLong(size_t paramIndex) const
{
	// do not use this function!!!
	if ( fProvider )
		return fProvider->GetParamLong( paramIndex );
	else 
		return 0;
}

void CGenericParamProvider::SetParamLong(size_t paramIndex, Sint32 value)
{
	// do not use this function!!!
	if ( fProvider )
		fProvider->SetParamLong( paramIndex, value );
}

bool CGenericParamProvider::GetParamBool(size_t paramIndex) const
{
	// do not use this function!!!
	if ( fProvider )
		return fProvider->GetParamBool( paramIndex );
	else
		return false;
}

void CGenericParamProvider::SetParamBool(size_t paramIndex, bool value)
{
	// do not use this function!!!
	if ( fProvider )
		fProvider->SetParamBool( paramIndex, value );
}

double CGenericParamProvider::GetParamReal(size_t paramIndex) const
{
	// do not use this function!!!
	if ( fProvider )
		return fProvider->GetParamReal( paramIndex );
	else
		return 0;
}

void CGenericParamProvider::SetParamReal(size_t paramIndex, double value)
{
	// do not use this function!!!
	if ( fProvider )
		fProvider->SetParamReal( paramIndex, value );
}

TXString CGenericParamProvider::GetParamString(size_t paramIndex) const
{
	// do not use this function!!!
	if ( fProvider )
		return fProvider->GetParamString( paramIndex );
	else 
		return "";
}

void CGenericParamProvider::SetParamString(size_t paramIndex, const TXString& value)
{
	// do not use this function!!!
	if ( fProvider )
		fProvider->SetParamString( paramIndex, value );
}

VWPoint2D CGenericParamProvider::GetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord) const
{
	// do not use this function!!!
	if ( fProvider )
		return fProvider->GetParamCtrlPt( paramIndexXCoord, paramIndexYCoord );
	else 
		return VWPoint2D( 0, 0 );
}

void CGenericParamProvider::SetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord, const VWPoint2D& value)
{
	// do not use this function!!!
	if ( fProvider )
		fProvider->SetParamCtrlPt( paramIndexXCoord, paramIndexYCoord, value );
}

bool CGenericParamProvider::GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const
{
	// do not use this function!!!
	if ( fProvider )
		return fProvider->GetParamChoices( paramIndex, outArray );
	else
		return false;
}

EFieldStyle CGenericParamProvider::GetParamStyle(size_t paramIndex) const
{
	// do not use this function!!!
	if ( fProvider )
		return fProvider->GetParamStyle( paramIndex );
	else 
		return EFieldStyle::kFieldReal;
}


// --------------------------------------------------------------------------------------------------------
CObjectParamProvider::CObjectParamProvider(MCObjectHandle hParametricObj)
: fObj( hParametricObj )
{
}

CObjectParamProvider::CObjectParamProvider(VWParametricObj& obj)
: fObj( obj )
{
}

CObjectParamProvider::~CObjectParamProvider()
{
}

MCObjectHandle CObjectParamProvider::GetObject() const
{
    return fObj;
}

Sint32 CObjectParamProvider::GetParamLong(const char* szParamName) const
{
	return fObj.GetParamLong( szParamName );
}

void CObjectParamProvider::SetParamLong(const char* szParamName, Sint32 value)
{
	fObj.SetParamLong( szParamName, value );
}

bool CObjectParamProvider::GetParamBool(const char* szParamName) const
{
	return fObj.GetParamBool( szParamName );
}

void CObjectParamProvider::SetParamBool(const char* szParamName, bool value)
{
	fObj.SetParamBool( szParamName, value );
}

double CObjectParamProvider::GetParamReal(const char* szParamName) const
{
	return fObj.GetParamReal( szParamName );
}

void CObjectParamProvider::SetParamReal(const char* szParamName, double value)
{
	fObj.SetParamReal( szParamName, value );
}

TXString CObjectParamProvider::GetParamString(const char* szParamName) const
{
	return fObj.GetParamString( szParamName );
}

void CObjectParamProvider::SetParamString(const char* szParamName, const TXString& value)
{
	fObj.SetParamString( szParamName, value );
}

VWPoint2D CObjectParamProvider::GetParamCtrlPt(const char* szParamXCoord) const
{
	VWPoint2D	result;

	TXString	univParamNameX( szParamXCoord );
	size_t		len	= univParamNameX.GetLength();
	if ( len > 0 )
	{
		TXString	univParamNameY = univParamNameX;
		univParamNameY.SetAt( len - 1, 'Y' );

		result.x = fObj.GetParamReal( univParamNameX );
		result.y = fObj.GetParamReal( univParamNameY );
	}

	return result;
}

void CObjectParamProvider::SetParamCtrlPt(const char* szParamXCoord, const VWPoint2D& value)
{
	TXString	univParamNameX( szParamXCoord );
	size_t		len	= univParamNameX.GetLength();
	if ( len > 0 )
	{
		TXString	univParamNameY = univParamNameX;
		univParamNameY.SetAt( len - 1, 'Y' );

		fObj.SetParamReal( univParamNameX, value.x );
		fObj.SetParamReal( univParamNameY, value.y );
	}
}

EFieldStyle	 CObjectParamProvider::GetParamStyle(const char* szParamName) const
{
	return fObj.GetParamStyle( szParamName );
}

size_t CObjectParamProvider::GetParamIndex(const char* szParamName) const
{
	return fObj.GetParamIndex( szParamName );
}

TXString CObjectParamProvider::GetParamName(size_t index) const
{
	return fObj.GetParamName( index );
}

Sint32 CObjectParamProvider::GetParamLong(size_t paramIndex) const
{
	return fObj.GetParamLong( paramIndex );
}

void CObjectParamProvider::SetParamLong(size_t paramIndex, Sint32 value)
{
	fObj.SetParamLong( paramIndex, value );
}

bool CObjectParamProvider::GetParamBool(size_t paramIndex) const
{
	return fObj.GetParamBool( paramIndex );
}

void CObjectParamProvider::SetParamBool(size_t paramIndex, bool value)
{
	fObj.SetParamBool( paramIndex, value );
}

double CObjectParamProvider::GetParamReal(size_t paramIndex) const
{
	return fObj.GetParamReal( paramIndex );
}

void CObjectParamProvider::SetParamReal(size_t paramIndex, double value)
{
	fObj.SetParamReal( paramIndex, value );
}

TXString CObjectParamProvider::GetParamString(size_t paramIndex) const
{
	return fObj.GetParamString( paramIndex );
}

void CObjectParamProvider::SetParamString(size_t paramIndex, const TXString& value)
{
	fObj.SetParamString( paramIndex, value );
}

TXString CObjectParamProvider::GetParamValue(const char* szParamName) const
{
	return fObj.GetParamValue( szParamName );
}

void CObjectParamProvider::SetParamValue(const char* szParamName, const TXString& value)
{
	fObj.SetParamValue( szParamName, value );
}

VWPoint2D CObjectParamProvider::GetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord) const
{
	return VWPoint2D(	fObj.GetParamReal( paramIndexXCoord ),
						fObj.GetParamReal( paramIndexYCoord ) );
}

void CObjectParamProvider::SetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord, const VWPoint2D& value)
{
	fObj.SetParamReal( paramIndexXCoord, value.x );
	fObj.SetParamReal( paramIndexYCoord, value.y );
}

bool CObjectParamProvider::GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const
{
	return this->ResourceGetParamChoices( fObj, paramIndex, outArray );
}

size_t CObjectParamProvider::GetParamsCount() const
{
	return fObj.GetParamsCount();
}

EFieldStyle CObjectParamProvider::GetParamStyle(size_t paramIndex) const
{
	return fObj.GetParamStyle( paramIndex );
}


// --------------------------------------------------------------------------------------------------------
CFormatParamProvider::CFormatParamProvider(MCObjectHandle hRecordFormatObj)
: fObj( hRecordFormatObj )
{
}

CFormatParamProvider::CFormatParamProvider(VWRecordFormatObj& obj)
: fObj( obj )
{
}

CFormatParamProvider::~CFormatParamProvider()
{
}

MCObjectHandle CFormatParamProvider::GetObject() const
{
    return fObj;
}

Sint32 CFormatParamProvider::GetParamLong(const char* szParamName) const
{
	return fObj.GetParamLong( szParamName );
}

void CFormatParamProvider::SetParamLong(const char* szParamName, Sint32 value)
{
	fObj.SetParamLong( szParamName, value );
}

bool CFormatParamProvider::GetParamBool(const char* szParamName) const
{
	return fObj.GetParamBool( szParamName );
}

void CFormatParamProvider::SetParamBool(const char* szParamName, bool value)
{
	fObj.SetParamBool( szParamName, value );
}

double CFormatParamProvider::GetParamReal(const char* szParamName) const
{
	return fObj.GetParamReal( szParamName );
}

void CFormatParamProvider::SetParamReal(const char* szParamName, double value)
{
	fObj.SetParamReal( szParamName, value );
}

TXString CFormatParamProvider::GetParamString(const char* szParamName) const
{
	return fObj.GetParamString( szParamName );
}

void CFormatParamProvider::SetParamString(const char* szParamName, const TXString& value)
{
	fObj.SetParamString( szParamName, value );
}

VWPoint2D CFormatParamProvider::GetParamCtrlPt(const char* szParamXCoord) const
{
	VWPoint2D	result;

	TXString	univParamNameX( szParamXCoord );
	size_t		len	= univParamNameX.GetLength();
	if ( len > 0 )
	{
		TXString	univParamNameY = univParamNameX;
		univParamNameY.SetAt( len - 1, 'Y' );

		result.x = fObj.GetParamReal( univParamNameX );
		result.y = fObj.GetParamReal( univParamNameY );
	}

	return result;
}

void CFormatParamProvider::SetParamCtrlPt(const char* szParamXCoord, const VWPoint2D& value)
{
	TXString	univParamNameX( szParamXCoord );
	size_t		len	= univParamNameX.GetLength();
	if ( len > 0 )
	{
		TXString	univParamNameY = univParamNameX;
		univParamNameY.SetAt( len - 1, 'Y' );

		fObj.SetParamReal( univParamNameX, value.x );
		fObj.SetParamReal( univParamNameY, value.y );
	}
}

EFieldStyle CFormatParamProvider::GetParamStyle(const char* szParamName) const
{
	return fObj.GetParamStyle( szParamName );
}

size_t CFormatParamProvider::GetParamIndex(const char* szParamName) const
{
	return fObj.GetParamIndex( szParamName );
}

TXString CFormatParamProvider::GetParamName(size_t index) const
{
	return fObj.GetParamName( index );
}

Sint32 CFormatParamProvider::GetParamLong(size_t paramIndex) const
{
	return fObj.GetParamLong( paramIndex );
}

void CFormatParamProvider::SetParamLong(size_t paramIndex, Sint32 value)
{
	fObj.SetParamLong( paramIndex, value );
}

bool CFormatParamProvider::GetParamBool(size_t paramIndex) const
{
	return fObj.GetParamBool( paramIndex );
}

void CFormatParamProvider::SetParamBool(size_t paramIndex, bool value)
{
	fObj.SetParamBool( paramIndex, value );
}

double CFormatParamProvider::GetParamReal(size_t paramIndex) const
{
	return fObj.GetParamReal( paramIndex );
}

void CFormatParamProvider::SetParamReal(size_t paramIndex, double value)
{
	fObj.SetParamReal( paramIndex, value );
}

TXString CFormatParamProvider::GetParamString(size_t paramIndex) const
{
	return fObj.GetParamString( paramIndex );
}

void CFormatParamProvider::SetParamString(size_t paramIndex, const TXString& value)
{
	fObj.SetParamString( paramIndex, value );
}

TXString CFormatParamProvider::GetParamValue(const char* szParamName) const
{
	return fObj.GetParamValue( szParamName );
}

void CFormatParamProvider::SetParamValue(const char* szParamName, const TXString& value)
{
	fObj.SetParamValue( szParamName, value );
}

VWPoint2D CFormatParamProvider::GetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord) const
{
	return VWPoint2D(	fObj.GetParamReal( paramIndexXCoord ),
						fObj.GetParamReal( paramIndexYCoord ) );
}

void CFormatParamProvider::SetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord, const VWPoint2D& value)
{
	fObj.SetParamReal( paramIndexXCoord, value.x );
	fObj.SetParamReal( paramIndexYCoord, value.y );
}

bool CFormatParamProvider::GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const
{
	return this->ResourceGetParamChoices( fObj, paramIndex, outArray );
}

size_t CFormatParamProvider::GetParamsCount() const
{
	return fObj.GetParamsCount();
}

EFieldStyle CFormatParamProvider::GetParamStyle(size_t paramIndex) const
{
	return fObj.GetParamStyle( paramIndex );
}


// --------------------------------------------------------------------------------------------------------
CRecordParamProvider::CRecordParamProvider(MCObjectHandle hRecordObj)
: fObj( hRecordObj )
{
}

CRecordParamProvider::CRecordParamProvider(VWRecordObj& obj)
: fObj( obj )
{
}

CRecordParamProvider::~CRecordParamProvider()
{
}

MCObjectHandle CRecordParamProvider::GetObject() const
{
	return fObj;
}

Sint32 CRecordParamProvider::GetParamLong(const char* szParamName) const
{
	return fObj.GetParamLong( szParamName );
}

void CRecordParamProvider::SetParamLong(const char* szParamName, Sint32 value)
{
	fObj.SetParamLong( szParamName, value );
}

bool CRecordParamProvider::GetParamBool(const char* szParamName) const
{
	return fObj.GetParamBool( szParamName );
}

void CRecordParamProvider::SetParamBool(const char* szParamName, bool value)
{
	fObj.SetParamBool( szParamName, value );
}

double CRecordParamProvider::GetParamReal(const char* szParamName) const
{
	return fObj.GetParamReal( szParamName );
}

void CRecordParamProvider::SetParamReal(const char* szParamName, double value)
{
	fObj.SetParamReal( szParamName, value );
}

TXString CRecordParamProvider::GetParamString(const char* szParamName) const
{
	return fObj.GetParamString( szParamName );
}

void CRecordParamProvider::SetParamString(const char* szParamName, const TXString& value)
{
	fObj.SetParamString( szParamName, value );
}

VWPoint2D CRecordParamProvider::GetParamCtrlPt(const char* szParamXCoord) const
{
	VWPoint2D	result;

	TXString	univParamNameX( szParamXCoord );
	size_t		len	= univParamNameX.GetLength();
	if ( len > 0 )
	{
		TXString	univParamNameY = univParamNameX;
		univParamNameY.SetAt( len - 1, 'Y' );

		result.x = fObj.GetParamReal( univParamNameX );
		result.y = fObj.GetParamReal( univParamNameY );
	}

	return result;
}

void CRecordParamProvider::SetParamCtrlPt(const char* szParamXCoord, const VWPoint2D& value)
{
	TXString	univParamNameX( szParamXCoord );
	size_t		len	= univParamNameX.GetLength();
	if ( len > 0 )
	{
		TXString	univParamNameY = univParamNameX;
		univParamNameY.SetAt( len - 1, 'Y' );

		fObj.SetParamReal( univParamNameX, value.x );
		fObj.SetParamReal( univParamNameY, value.y );
	}
}

EFieldStyle CRecordParamProvider::GetParamStyle(const char* szParamName) const
{
	return fObj.GetParamStyle( szParamName );
}

size_t CRecordParamProvider::GetParamIndex(const char* szParamName) const
{
	return fObj.GetParamIndex( szParamName );
}

TXString CRecordParamProvider::GetParamName(size_t index) const
{
	return fObj.GetParamName( index );
}

Sint32 CRecordParamProvider::GetParamLong(size_t paramIndex) const
{
	return fObj.GetParamLong( paramIndex );
}

void CRecordParamProvider::SetParamLong(size_t paramIndex, Sint32 value)
{
	fObj.SetParamLong( paramIndex, value );
}

bool CRecordParamProvider::GetParamBool(size_t paramIndex) const
{
	return fObj.GetParamBool( paramIndex );
}

void CRecordParamProvider::SetParamBool(size_t paramIndex, bool value)
{
	fObj.SetParamBool( paramIndex, value );
}

double CRecordParamProvider::GetParamReal(size_t paramIndex) const
{
	return fObj.GetParamReal( paramIndex );
}

void CRecordParamProvider::SetParamReal(size_t paramIndex, double value)
{
	fObj.SetParamReal( paramIndex, value );
}

TXString CRecordParamProvider::GetParamString(size_t paramIndex) const
{
	return fObj.GetParamString( paramIndex );
}

void CRecordParamProvider::SetParamString(size_t paramIndex, const TXString& value)
{
	fObj.SetParamString( paramIndex, value );
}

TXString CRecordParamProvider::GetParamValue(const char* szParamName) const
{
	return fObj.GetParamValue( szParamName );
}

void CRecordParamProvider::SetParamValue(const char* szParamName, const TXString& value)
{
	fObj.SetParamValue( szParamName, value );
}

VWPoint2D CRecordParamProvider::GetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord) const
{
	return VWPoint2D(	fObj.GetParamReal( paramIndexXCoord ),
						fObj.GetParamReal( paramIndexYCoord ) );
}

void CRecordParamProvider::SetParamCtrlPt(size_t paramIndexXCoord, size_t paramIndexYCoord, const VWPoint2D& value)
{
	fObj.SetParamReal( paramIndexXCoord, value.x );
	fObj.SetParamReal( paramIndexYCoord, value.y );
}

bool CRecordParamProvider::GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const
{
	return this->ResourceGetParamChoices( fObj, paramIndex, outArray );
}

size_t CRecordParamProvider::GetParamsCount() const
{
	return fObj.GetParamsCount();
}

EFieldStyle CRecordParamProvider::GetParamStyle(size_t paramIndex) const
{
	return fObj.GetParamStyle( paramIndex );
}

