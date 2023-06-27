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
void CParamProviderAbstract::ProcessParameter(bool bRead, bool& inOutValue, bool oldValue, const TXString& szParamName)
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
void CParamProviderAbstract::ProcessParameter(bool bRead, Uint32& inOutValue, Uint32 oldValue, const TXString& szParamName)
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
void CParamProviderAbstract::ProcessParameter(bool bRead, Sint32& inOutValue, Uint32 oldValue, const TXString& szParamName)
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
void CParamProviderAbstract::ProcessParameter(bool bRead, double& inOutValue, double oldValue, const TXString& szParamName)
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
void  CParamProviderAbstract::ProcessParameter(bool bRead, TXString& inOutValue, const TXString& oldValue, const TXString& szParamName)
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
void  CParamProviderAbstract::ProcessParameter(bool bRead, VWPoint2D& inOutValue, const VWPoint2D& oldValue, const TXString& szParamNameXCoord, const TXString& szParamNameYCoord)
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

CGenericParamProvider::CGenericParamProvider(MCObjectHandle hParametricObject, const TXString& szFormatName)
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

void CGenericParamProvider::Set(MCObjectHandle hParametricObject, const TXString& szFormatName)
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

Sint32 CGenericParamProvider::GetParamLong(const TXString& szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamLong( szParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamLong(const TXString& szParamName, Sint32 value)
{
	if ( fProvider )
		fProvider->SetParamLong( szParamName, value );
}

bool CGenericParamProvider::GetParamBool(const TXString& szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamBool( szParamName );
	else
		return false;
}

void CGenericParamProvider::SetParamBool(const TXString& szParamName, bool value)
{
	if ( fProvider )
		fProvider->SetParamBool( szParamName, value );
}

double CGenericParamProvider::GetParamReal(const TXString& szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamReal( szParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamReal(const TXString& szParamName, double value)
{
	if ( fProvider )
		fProvider->SetParamReal( szParamName, value );
}

TXString CGenericParamProvider::GetParamString(const TXString& szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamString( szParamName );
	else return "";
}

void CGenericParamProvider::SetParamString(const TXString& szParamName, const TXString& value)
{
	if ( fProvider )
		fProvider->SetParamString( szParamName, value );
}

VWPoint2D CGenericParamProvider::GetParamCtrlPt(const TXString& szParamXCoord) const
{
	if ( fProvider )
		return fProvider->GetParamCtrlPt( szParamXCoord );
	else 
		return VWPoint2D( 0 ,0 );
}

void CGenericParamProvider::SetParamCtrlPt(const TXString& szParamXCoord, const VWPoint2D& value)
{
	if ( fProvider )
		fProvider->SetParamCtrlPt( szParamXCoord, value );
}

InternalIndex CGenericParamProvider::GetParamClass(const TXString& univParamName) const
{
	if ( fProvider )
		return fProvider->GetParamClass( univParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamClass(const TXString& univParamName, InternalIndex resource)
{
	if ( fProvider )
		fProvider->SetParamClass( univParamName, resource );
}

InternalIndex CGenericParamProvider::GetParamBuildingMaterial(const TXString& univParamName) const
{
	if ( fProvider )
		return fProvider->GetParamBuildingMaterial( univParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource)
{
	if ( fProvider )
		fProvider->SetParamBuildingMaterial( univParamName, resource );
}

VWPattern CGenericParamProvider::GetParamFill(const TXString& univParamName) const
{
	if ( fProvider )
		return fProvider->GetParamFill( univParamName );
	else 
		return VWPattern( true );
}

void CGenericParamProvider::SetParamFill(const TXString& univParamName, const VWPattern& attr)
{
	if ( fProvider )
		fProvider->SetParamFill( univParamName, attr );
}

VWPattern CGenericParamProvider::GetParamPenStyle(const TXString& univParamName) const
{
	if ( fProvider )
		return fProvider->GetParamPenStyle( univParamName );
	else 
		return VWPattern( false );
}

void CGenericParamProvider::SetParamPenStyle(const TXString& univParamName, const VWPattern& attr)
{
	if ( fProvider )
		fProvider->SetParamPenStyle( univParamName, attr );
}

Uint8 CGenericParamProvider::GetParamPenWeight(const TXString& univParamName) const
{
	if ( fProvider )
		return fProvider->GetParamPenWeight( univParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamPenWeight(const TXString& univParamName, Uint8 value)
{
	if ( fProvider )
		fProvider->SetParamPenWeight( univParamName, value );
}

ColorRef CGenericParamProvider::GetParamColor(const TXString& univParamName) const
{
	if ( fProvider )
		return fProvider->GetParamColor( univParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamColor(const TXString& univParamName, ColorRef value)
{
	if ( fProvider )
		fProvider->SetParamColor( univParamName, value );
}

InternalIndex CGenericParamProvider::GetParamTexture(const TXString& univParamName) const
{
	if ( fProvider )
		return fProvider->GetParamTexture( univParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamTexture(const TXString& univParamName, InternalIndex resource)
{
	if ( fProvider )
		fProvider->SetParamTexture( univParamName, resource );
}

InternalIndex CGenericParamProvider::GetParamSymDef(const TXString& univParamName) const
{
	if ( fProvider )
		return fProvider->GetParamSymDef( univParamName );
	else 
		return 0;
}

void CGenericParamProvider::SetParamSymDef(const TXString& univParamName, InternalIndex resource)
{
	if ( fProvider )
		fProvider->SetParamSymDef( univParamName, resource );
}

TXString CGenericParamProvider::GetParamValue(const TXString& szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamValue( szParamName );
	else
		return "";
}

void CGenericParamProvider::SetParamValue(const TXString& szParamName, const TXString& value)
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

EFieldStyle CGenericParamProvider::GetParamStyle(const TXString& szParamName) const
{
	if ( fProvider )
		return fProvider->GetParamStyle( szParamName );
	else 
		return EFieldStyle::kFieldReal;
}

size_t CGenericParamProvider::GetParamIndex(const TXString& szParamName) const
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

size_t CGenericParamProvider::PopupGetChoicesCount(const TXString& univParamName)
{
	if ( fProvider )
		return fProvider->PopupGetChoicesCount( univParamName );
	else
		return 0;
}

void CGenericParamProvider::PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue)
{
	if ( fProvider )
		fProvider->PopupGetChoice( univParamName, index, outKey, outValue );
}

void CGenericParamProvider::PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	if ( fProvider )
		fProvider->PopupGetChoices( univParamName, outKeyValuePairs );
}

void CGenericParamProvider::PopupClearChoices(const TXString& univParamName)
{
	if ( fProvider )
		fProvider->PopupClearChoices( univParamName );
}

void CGenericParamProvider::PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append)
{
	if ( fProvider )
		fProvider->PopupSetChoices( univParamName, keyValuePairs, append );
}

size_t CGenericParamProvider::PopupGetChoicesCount(size_t paramIndex)
{
	if ( fProvider )
		return fProvider->PopupGetChoicesCount( paramIndex );
	else
		return 0;
}

void CGenericParamProvider::PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue)
{
	if ( fProvider )
		fProvider->PopupGetChoice( paramIndex, index, outKey, outValue );
}

void CGenericParamProvider::PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	if ( fProvider )
		fProvider->PopupGetChoices( paramIndex, outKeyValuePairs );
}

void CGenericParamProvider::PopupClearChoices(size_t paramIndex)
{
	if ( fProvider )
		fProvider->PopupClearChoices( paramIndex );
}

void CGenericParamProvider::PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append)
{
	if ( fProvider )
		fProvider->PopupSetChoices( paramIndex, keyValuePairs, append );
}

// added vw2022
InternalIndex CGenericParamProvider::GetParamClass(size_t paramIndex) const
{
	return fProvider->GetParamClass( paramIndex );
}

void CGenericParamProvider::SetParamClass(size_t paramIndex, InternalIndex resource)
{
	fProvider->SetParamClass( paramIndex, resource );
}

InternalIndex CGenericParamProvider::GetParamBuildingMaterial(size_t paramIndex) const
{
	return fProvider->GetParamBuildingMaterial( paramIndex );
}

void CGenericParamProvider::SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource)
{
	fProvider->SetParamBuildingMaterial( paramIndex, resource );
}

InternalIndex CGenericParamProvider::GetParamTexture(size_t paramIndex) const
{
	return fProvider->GetParamTexture( paramIndex );
}

void CGenericParamProvider::SetParamTexture(size_t paramIndex, InternalIndex resource)
{
	fProvider->SetParamTexture( paramIndex, resource );
}

InternalIndex CGenericParamProvider::GetParamSymDef(size_t paramIndex) const
{
	return fProvider->GetParamSymDef( paramIndex );
}

void CGenericParamProvider::SetParamSymDef(size_t paramIndex, InternalIndex resource)
{
	fProvider->SetParamSymDef( paramIndex, resource );
}

VWPattern CGenericParamProvider::GetParamFill(size_t paramIndex) const
{
	return fProvider->GetParamFill( paramIndex );
}

void CGenericParamProvider::SetParamFill(size_t paramIndex, const VWPattern& attr)
{
	return fProvider->SetParamFill( paramIndex, attr );
}

VWPattern CGenericParamProvider::GetParamPenStyle(size_t paramIndex) const
{
	return fProvider->GetParamPenStyle( paramIndex );
}

void CGenericParamProvider::SetParamPenStyle(size_t paramIndex, const VWPattern& attr)
{
	return fProvider->SetParamPenStyle( paramIndex, attr );
}

Uint8 CGenericParamProvider::GetParamPenWeight(size_t paramIndex) const
{
	return fProvider->GetParamPenWeight( paramIndex );
}

void CGenericParamProvider::SetParamPenWeight(size_t paramIndex, Uint8 value)
{
	return fProvider->SetParamPenWeight( paramIndex, value );
}

ColorRef CGenericParamProvider::GetParamColor(size_t paramIndex) const
{
	return fProvider->GetParamColor( paramIndex );
}

void CGenericParamProvider::SetParamColor(size_t paramIndex, ColorRef value)
{
	return fProvider->SetParamColor( paramIndex, value );
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

Sint32 CObjectParamProvider::GetParamLong(const TXString& szParamName) const
{
	return fObj.GetParamLong( szParamName );
}

void CObjectParamProvider::SetParamLong(const TXString& szParamName, Sint32 value)
{
	fObj.SetParamLong( szParamName, value );
}

bool CObjectParamProvider::GetParamBool(const TXString& szParamName) const
{
	return fObj.GetParamBool( szParamName );
}

void CObjectParamProvider::SetParamBool(const TXString& szParamName, bool value)
{
	fObj.SetParamBool( szParamName, value );
}

double CObjectParamProvider::GetParamReal(const TXString& szParamName) const
{
	return fObj.GetParamReal( szParamName );
}

void CObjectParamProvider::SetParamReal(const TXString& szParamName, double value)
{
	fObj.SetParamReal( szParamName, value );
}

TXString CObjectParamProvider::GetParamString(const TXString& szParamName) const
{
	return fObj.GetParamString( szParamName );
}

void CObjectParamProvider::SetParamString(const TXString& szParamName, const TXString& value)
{
	fObj.SetParamString( szParamName, value );
}

VWPoint2D CObjectParamProvider::GetParamCtrlPt(const TXString& szParamXCoord) const
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

void CObjectParamProvider::SetParamCtrlPt(const TXString& szParamXCoord, const VWPoint2D& value)
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
InternalIndex CObjectParamProvider::GetParamClass(const TXString& univParamName) const
{
	return fObj.GetParamClass( univParamName );
}

void CObjectParamProvider::SetParamClass(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamClass( univParamName, resource );
}

InternalIndex CObjectParamProvider::GetParamBuildingMaterial(const TXString& univParamName) const
{
	return fObj.GetParamBuildingMaterial( univParamName );
}

void CObjectParamProvider::SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamBuildingMaterial( univParamName, resource );
}

VWPattern CObjectParamProvider::GetParamFill(const TXString& univParamName) const
{
	return fObj.GetParamFill( univParamName );
}

void CObjectParamProvider::SetParamFill(const TXString& univParamName, const VWPattern& attr)
{
	fObj.SetParamFill( univParamName, attr );
}

VWPattern CObjectParamProvider::GetParamPenStyle(const TXString& univParamName) const
{
	return fObj.GetParamPenStyle( univParamName );
}

void CObjectParamProvider::SetParamPenStyle(const TXString& univParamName, const VWPattern& attr)
{
	fObj.SetParamPenStyle( univParamName, attr );
}

Uint8 CObjectParamProvider::GetParamPenWeight(const TXString& univParamName) const
{
	return fObj.GetParamPenWeight( univParamName );
}

void CObjectParamProvider::SetParamPenWeight(const TXString& univParamName, Uint8 value)
{
	fObj.SetParamPenWeight( univParamName, value );
}

ColorRef CObjectParamProvider::GetParamColor(const TXString& univParamName) const
{
	return fObj.GetParamColor( univParamName );
}

void CObjectParamProvider::SetParamColor(const TXString& univParamName, ColorRef value)
{
	fObj.SetParamColor( univParamName, value );
}

InternalIndex CObjectParamProvider::GetParamTexture(const TXString& univParamName) const
{
	return fObj.GetParamTexture( univParamName );
}

void CObjectParamProvider::SetParamTexture(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamTexture( univParamName, resource );
}

InternalIndex CObjectParamProvider::GetParamSymDef(const TXString& univParamName) const
{
	return fObj.GetParamSymDef( univParamName );
}

void CObjectParamProvider::SetParamSymDef(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamSymDef( univParamName, resource );
}

EFieldStyle	 CObjectParamProvider::GetParamStyle(const TXString& szParamName) const
{
	return fObj.GetParamStyle( szParamName );
}

size_t CObjectParamProvider::GetParamIndex(const TXString& szParamName) const
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

TXString CObjectParamProvider::GetParamValue(const TXString& szParamName) const
{
	return fObj.GetParamValue( szParamName );
}

void CObjectParamProvider::SetParamValue(const TXString& szParamName, const TXString& value)
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

size_t CObjectParamProvider::PopupGetChoicesCount(const TXString& univParamName)
{
	return fObj.PopupGetChoicesCount( univParamName );
}

void CObjectParamProvider::PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue)
{
	fObj.PopupGetChoice( univParamName, index, outKey, outValue );
}

void CObjectParamProvider::PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	fObj.PopupGetChoices( univParamName, outKeyValuePairs );
}

void CObjectParamProvider::PopupClearChoices(const TXString& univParamName)
{
	fObj.PopupClearChoices( univParamName );
}

void CObjectParamProvider::PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append)
{
	fObj.PopupSetChoices( univParamName, keyValuePairs, append );
}

size_t CObjectParamProvider::PopupGetChoicesCount(size_t paramIndex)
{
	return fObj.PopupGetChoicesCount( paramIndex );
}

void CObjectParamProvider::PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue)
{
	fObj.PopupGetChoice( paramIndex, index, outKey, outValue );
}

void CObjectParamProvider::PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	fObj.PopupGetChoices( paramIndex, outKeyValuePairs );
}

void CObjectParamProvider::PopupClearChoices(size_t paramIndex)
{
	fObj.PopupClearChoices( paramIndex );
}

void CObjectParamProvider::PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append)
{
	fObj.PopupSetChoices( paramIndex, keyValuePairs, append );
}

// added vw2022
InternalIndex CObjectParamProvider::GetParamClass(size_t paramIndex) const
{
	return fObj.GetParamClass( paramIndex );
}

void CObjectParamProvider::SetParamClass(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamClass( paramIndex, resource );
}

InternalIndex CObjectParamProvider::GetParamBuildingMaterial(size_t paramIndex) const
{
	return fObj.GetParamBuildingMaterial( paramIndex );
}

void CObjectParamProvider::SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamBuildingMaterial( paramIndex, resource );
}

InternalIndex CObjectParamProvider::GetParamTexture(size_t paramIndex) const
{
	return fObj.GetParamTexture( paramIndex );
}

void CObjectParamProvider::SetParamTexture(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamTexture( paramIndex, resource );
}

InternalIndex CObjectParamProvider::GetParamSymDef(size_t paramIndex) const
{
	return fObj.GetParamSymDef( paramIndex );
}

void CObjectParamProvider::SetParamSymDef(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamSymDef( paramIndex, resource );
}

VWPattern CObjectParamProvider::GetParamFill(size_t paramIndex) const
{
	return fObj.GetParamFill( paramIndex );
}

void CObjectParamProvider::SetParamFill(size_t paramIndex, const VWPattern& attr)
{
	return fObj.SetParamFill( paramIndex, attr );
}

VWPattern CObjectParamProvider::GetParamPenStyle(size_t paramIndex) const
{
	return fObj.GetParamPenStyle( paramIndex );
}

void CObjectParamProvider::SetParamPenStyle(size_t paramIndex, const VWPattern& attr)
{
	return fObj.SetParamPenStyle( paramIndex, attr );
}

Uint8 CObjectParamProvider::GetParamPenWeight(size_t paramIndex) const
{
	return fObj.GetParamPenWeight( paramIndex );
}

void CObjectParamProvider::SetParamPenWeight(size_t paramIndex, Uint8 value)
{
	return fObj.SetParamPenWeight( paramIndex, value );
}

ColorRef CObjectParamProvider::GetParamColor(size_t paramIndex) const
{
	return fObj.GetParamColor( paramIndex );
}

void CObjectParamProvider::SetParamColor(size_t paramIndex, ColorRef value)
{
	return fObj.SetParamColor( paramIndex, value );
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

Sint32 CFormatParamProvider::GetParamLong(const TXString& szParamName) const
{
	return fObj.GetParamLong( szParamName );
}

void CFormatParamProvider::SetParamLong(const TXString& szParamName, Sint32 value)
{
	fObj.SetParamLong( szParamName, value );
}

bool CFormatParamProvider::GetParamBool(const TXString& szParamName) const
{
	return fObj.GetParamBool( szParamName );
}

void CFormatParamProvider::SetParamBool(const TXString& szParamName, bool value)
{
	fObj.SetParamBool( szParamName, value );
}

double CFormatParamProvider::GetParamReal(const TXString& szParamName) const
{
	return fObj.GetParamReal( szParamName );
}

void CFormatParamProvider::SetParamReal(const TXString& szParamName, double value)
{
	fObj.SetParamReal( szParamName, value );
}

TXString CFormatParamProvider::GetParamString(const TXString& szParamName) const
{
	return fObj.GetParamString( szParamName );
}

void CFormatParamProvider::SetParamString(const TXString& szParamName, const TXString& value)
{
	fObj.SetParamString( szParamName, value );
}

VWPoint2D CFormatParamProvider::GetParamCtrlPt(const TXString& szParamXCoord) const
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

void CFormatParamProvider::SetParamCtrlPt(const TXString& szParamXCoord, const VWPoint2D& value)
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
InternalIndex CFormatParamProvider::GetParamClass(const TXString& univParamName) const
{
	return fObj.GetParamClass( univParamName );
}

void CFormatParamProvider::SetParamClass(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamClass( univParamName, resource );
}

InternalIndex CFormatParamProvider::GetParamBuildingMaterial(const TXString& univParamName) const
{
	return fObj.GetParamBuildingMaterial( univParamName );
}

void CFormatParamProvider::SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamBuildingMaterial( univParamName, resource );
}

VWPattern CFormatParamProvider::GetParamFill(const TXString& univParamName) const
{
	return fObj.GetParamFill( univParamName );
}

void CFormatParamProvider::SetParamFill(const TXString& univParamName, const VWPattern& attr)
{
	fObj.SetParamFill( univParamName, attr );
}

VWPattern CFormatParamProvider::GetParamPenStyle(const TXString& univParamName) const
{
	return fObj.GetParamPenStyle( univParamName );
}

void CFormatParamProvider::SetParamPenStyle(const TXString& univParamName, const VWPattern& attr)
{
	fObj.SetParamPenStyle( univParamName, attr );
}

Uint8 CFormatParamProvider::GetParamPenWeight(const TXString& univParamName) const
{
	return fObj.GetParamPenWeight( univParamName );
}

void CFormatParamProvider::SetParamPenWeight(const TXString& univParamName, Uint8 value)
{
	fObj.SetParamPenWeight( univParamName, value );
}

ColorRef CFormatParamProvider::GetParamColor(const TXString& univParamName) const
{
	return fObj.GetParamColor( univParamName );
}

void CFormatParamProvider::SetParamColor(const TXString& univParamName, ColorRef value)
{
	fObj.SetParamColor( univParamName, value );
}

InternalIndex CFormatParamProvider::GetParamTexture(const TXString& univParamName) const
{
	return fObj.GetParamTexture( univParamName );
}

void CFormatParamProvider::SetParamTexture(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamTexture( univParamName, resource );
}

InternalIndex CFormatParamProvider::GetParamSymDef(const TXString& univParamName) const
{
	return fObj.GetParamSymDef( univParamName );
}

void CFormatParamProvider::SetParamSymDef(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamSymDef( univParamName, resource );
}

EFieldStyle CFormatParamProvider::GetParamStyle(const TXString& szParamName) const
{
	return fObj.GetParamStyle( szParamName );
}

size_t CFormatParamProvider::GetParamIndex(const TXString& szParamName) const
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

TXString CFormatParamProvider::GetParamValue(const TXString& szParamName) const
{
	return fObj.GetParamValue( szParamName );
}

void CFormatParamProvider::SetParamValue(const TXString& szParamName, const TXString& value)
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

size_t CFormatParamProvider::PopupGetChoicesCount(const TXString& univParamName)
{
	return fObj.PopupGetChoicesCount( univParamName );
}

void CFormatParamProvider::PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue)
{
	fObj.PopupGetChoice( univParamName, index, outKey, outValue );
}

void CFormatParamProvider::PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	fObj.PopupGetChoices( univParamName, outKeyValuePairs );
}

void CFormatParamProvider::PopupClearChoices(const TXString& univParamName)
{
	fObj.PopupClearChoices( univParamName );
}

void CFormatParamProvider::PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append)
{
	fObj.PopupSetChoices( univParamName, keyValuePairs, append );
}

size_t CFormatParamProvider::PopupGetChoicesCount(size_t paramIndex)
{
	return fObj.PopupGetChoicesCount( paramIndex );
}

void CFormatParamProvider::PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue)
{
	fObj.PopupGetChoice( paramIndex, index, outKey, outValue );
}

void CFormatParamProvider::PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	fObj.PopupGetChoices( paramIndex, outKeyValuePairs );
}

void CFormatParamProvider::PopupClearChoices(size_t paramIndex)
{
	fObj.PopupClearChoices( paramIndex );
}

void CFormatParamProvider::PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append)
{
	fObj.PopupSetChoices( paramIndex, keyValuePairs, append );
}

//-- added vw2022
InternalIndex CFormatParamProvider::GetParamClass(size_t paramIndex) const
{
	return fObj.GetParamClass( paramIndex );
}

void CFormatParamProvider::SetParamClass(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamClass( paramIndex, resource );
}

InternalIndex CFormatParamProvider::GetParamBuildingMaterial(size_t paramIndex) const
{
	return fObj.GetParamBuildingMaterial( paramIndex );
}

void CFormatParamProvider::SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamBuildingMaterial( paramIndex, resource );
}

InternalIndex CFormatParamProvider::GetParamTexture(size_t paramIndex) const
{
	return fObj.GetParamTexture( paramIndex );
}

void CFormatParamProvider::SetParamTexture(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamTexture( paramIndex, resource );
}

InternalIndex CFormatParamProvider::GetParamSymDef(size_t paramIndex) const
{
	return fObj.GetParamSymDef( paramIndex );
}

void CFormatParamProvider::SetParamSymDef(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamSymDef( paramIndex, resource );
}

VWPattern CFormatParamProvider::GetParamFill(size_t paramIndex) const
{
	return fObj.GetParamFill( paramIndex );
}

void CFormatParamProvider::SetParamFill(size_t paramIndex, const VWPattern& attr)
{
	return fObj.SetParamFill( paramIndex, attr );
}

VWPattern CFormatParamProvider::GetParamPenStyle(size_t paramIndex) const
{
	return fObj.GetParamPenStyle( paramIndex );
}

void CFormatParamProvider::SetParamPenStyle(size_t paramIndex, const VWPattern& attr)
{
	return fObj.SetParamPenStyle( paramIndex, attr );
}

Uint8 CFormatParamProvider::GetParamPenWeight(size_t paramIndex) const
{
	return fObj.GetParamPenWeight( paramIndex );
}

void CFormatParamProvider::SetParamPenWeight(size_t paramIndex, Uint8 value)
{
	return fObj.SetParamPenWeight( paramIndex, value );
}

ColorRef CFormatParamProvider::GetParamColor(size_t paramIndex) const
{
	return fObj.GetParamColor( paramIndex );
}

void CFormatParamProvider::SetParamColor(size_t paramIndex, ColorRef value)
{
	return fObj.SetParamColor( paramIndex, value );
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

Sint32 CRecordParamProvider::GetParamLong(const TXString& szParamName) const
{
	return fObj.GetParamLong( szParamName );
}

void CRecordParamProvider::SetParamLong(const TXString& szParamName, Sint32 value)
{
	fObj.SetParamLong( szParamName, value );
}

bool CRecordParamProvider::GetParamBool(const TXString& szParamName) const
{
	return fObj.GetParamBool( szParamName );
}

void CRecordParamProvider::SetParamBool(const TXString& szParamName, bool value)
{
	fObj.SetParamBool( szParamName, value );
}

double CRecordParamProvider::GetParamReal(const TXString& szParamName) const
{
	return fObj.GetParamReal( szParamName );
}

void CRecordParamProvider::SetParamReal(const TXString& szParamName, double value)
{
	fObj.SetParamReal( szParamName, value );
}

TXString CRecordParamProvider::GetParamString(const TXString& szParamName) const
{
	return fObj.GetParamString( szParamName );
}

void CRecordParamProvider::SetParamString(const TXString& szParamName, const TXString& value)
{
	fObj.SetParamString( szParamName, value );
}

VWPoint2D CRecordParamProvider::GetParamCtrlPt(const TXString& szParamXCoord) const
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

void CRecordParamProvider::SetParamCtrlPt(const TXString& szParamXCoord, const VWPoint2D& value)
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

InternalIndex CRecordParamProvider::GetParamClass(const TXString& univParamName) const
{
	return fObj.GetParamClass( univParamName );
}

void CRecordParamProvider::SetParamClass(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamClass( univParamName, resource );
}

InternalIndex CRecordParamProvider::GetParamBuildingMaterial(const TXString& univParamName) const
{
	return fObj.GetParamBuildingMaterial( univParamName );
}

void CRecordParamProvider::SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamBuildingMaterial( univParamName, resource );
}

VWPattern CRecordParamProvider::GetParamFill(const TXString& univParamName) const
{
	return fObj.GetParamFill( univParamName );
}

void CRecordParamProvider::SetParamFill(const TXString& univParamName, const VWPattern& attr)
{
	fObj.SetParamFill( univParamName, attr );
}

VWPattern CRecordParamProvider::GetParamPenStyle(const TXString& univParamName) const
{
	return fObj.GetParamPenStyle( univParamName );
}

void CRecordParamProvider::SetParamPenStyle(const TXString& univParamName, const VWPattern& attr)
{
	fObj.SetParamPenStyle( univParamName, attr );
}

Uint8 CRecordParamProvider::GetParamPenWeight(const TXString& univParamName) const
{
	return fObj.GetParamPenWeight( univParamName );
}

void CRecordParamProvider::SetParamPenWeight(const TXString& univParamName, Uint8 value)
{
	fObj.SetParamPenWeight( univParamName, value );
}

ColorRef CRecordParamProvider::GetParamColor(const TXString& univParamName) const
{
	return fObj.GetParamColor( univParamName );
}

void CRecordParamProvider::SetParamColor(const TXString& univParamName, ColorRef value)
{
	fObj.SetParamColor( univParamName, value );
}

InternalIndex CRecordParamProvider::GetParamTexture(const TXString& univParamName) const
{
	return fObj.GetParamTexture( univParamName );
}

void CRecordParamProvider::SetParamTexture(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamTexture( univParamName, resource );
}

InternalIndex CRecordParamProvider::GetParamSymDef(const TXString& univParamName) const
{
	return fObj.GetParamSymDef( univParamName );
}

void CRecordParamProvider::SetParamSymDef(const TXString& univParamName, InternalIndex resource)
{
	fObj.SetParamSymDef( univParamName, resource );
}

EFieldStyle CRecordParamProvider::GetParamStyle(const TXString& szParamName) const
{
	return fObj.GetParamStyle( szParamName );
}

size_t CRecordParamProvider::GetParamIndex(const TXString& szParamName) const
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

TXString CRecordParamProvider::GetParamValue(const TXString& szParamName) const
{
	return fObj.GetParamValue( szParamName );
}

void CRecordParamProvider::SetParamValue(const TXString& szParamName, const TXString& value)
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

size_t CRecordParamProvider::PopupGetChoicesCount(const TXString& univParamName)
{
	return fObj.PopupGetChoicesCount( univParamName );
}

void CRecordParamProvider::PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue)
{
	fObj.PopupGetChoice( univParamName, index, outKey, outValue );
}

void CRecordParamProvider::PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	fObj.PopupGetChoices( univParamName, outKeyValuePairs );
}

void CRecordParamProvider::PopupClearChoices(const TXString& univParamName)
{
	fObj.PopupClearChoices( univParamName );
}

void CRecordParamProvider::PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append)
{
	fObj.PopupSetChoices( univParamName, keyValuePairs, append );
}

size_t CRecordParamProvider::PopupGetChoicesCount(size_t paramIndex)
{
	return fObj.PopupGetChoicesCount( paramIndex );
}

void CRecordParamProvider::PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue)
{
	fObj.PopupGetChoice( paramIndex, index, outKey, outValue );
}

void CRecordParamProvider::PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	fObj.PopupGetChoices( paramIndex, outKeyValuePairs );
}

void CRecordParamProvider::PopupClearChoices(size_t paramIndex)
{
	fObj.PopupClearChoices( paramIndex );
}

void CRecordParamProvider::PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append)
{
	fObj.PopupSetChoices( paramIndex, keyValuePairs, append );
}

//-- added vw2022
InternalIndex CRecordParamProvider::GetParamClass(size_t paramIndex) const
{
	return fObj.GetParamClass( paramIndex );
}

void CRecordParamProvider::SetParamClass(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamClass( paramIndex, resource );
}

InternalIndex CRecordParamProvider::GetParamBuildingMaterial(size_t paramIndex) const
{
	return fObj.GetParamBuildingMaterial( paramIndex );
}

void CRecordParamProvider::SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamBuildingMaterial( paramIndex, resource );
}

InternalIndex CRecordParamProvider::GetParamTexture(size_t paramIndex) const
{
	return fObj.GetParamTexture( paramIndex );
}

void CRecordParamProvider::SetParamTexture(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamTexture( paramIndex, resource );
}

InternalIndex CRecordParamProvider::GetParamSymDef(size_t paramIndex) const
{
	return fObj.GetParamSymDef( paramIndex );
}

void CRecordParamProvider::SetParamSymDef(size_t paramIndex, InternalIndex resource)
{
	fObj.SetParamSymDef( paramIndex, resource );
}

VWPattern CRecordParamProvider::GetParamFill(size_t paramIndex) const
{
	return fObj.GetParamFill( paramIndex );
}

void CRecordParamProvider::SetParamFill(size_t paramIndex, const VWPattern& attr)
{
	return fObj.SetParamFill( paramIndex, attr );
}

VWPattern CRecordParamProvider::GetParamPenStyle(size_t paramIndex) const
{
	return fObj.GetParamPenStyle( paramIndex );
}

void CRecordParamProvider::SetParamPenStyle(size_t paramIndex, const VWPattern& attr)
{
	return fObj.SetParamPenStyle( paramIndex, attr );
}

Uint8 CRecordParamProvider::GetParamPenWeight(size_t paramIndex) const
{
	return fObj.GetParamPenWeight( paramIndex );
}

void CRecordParamProvider::SetParamPenWeight(size_t paramIndex, Uint8 value)
{
	return fObj.SetParamPenWeight( paramIndex, value );
}

ColorRef CRecordParamProvider::GetParamColor(size_t paramIndex) const
{
	return fObj.GetParamColor( paramIndex );
}

void CRecordParamProvider::SetParamColor(size_t paramIndex, ColorRef value)
{
	return fObj.SetParamColor( paramIndex, value );
}
