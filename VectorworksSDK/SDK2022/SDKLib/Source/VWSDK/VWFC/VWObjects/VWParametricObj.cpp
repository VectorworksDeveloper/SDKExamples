//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "../../../../../Include/Interfaces/VectorWorks/IExtendedPropsSupport.h"

using namespace VWFC::Tools;
using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWParametricObj::VWParametricObj(MCObjectHandle hParametric)
: VWGroupObj( 0 )	// call nothing doing constructor -- we dont want a new group created
{
	// this may come NULL
	if ( hParametric ) {
		VWFC_ASSERT( VWParametricObj::IsParametricObject( hParametric ) );
//		if ( ! VWParametricObj::IsParametricObject( hParametric ) )
//			THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	}

	this->SetParametricHandle( hParametric );
}

VWParametricObj::VWParametricObj(const TXString& parametricName, const VWPoint2D& location, double angle /*= 0*/)
: VWGroupObj( 0 )	// call nothing doing constructor -- we dont want a new group created
{
	::GS_DefineCustomObject( gCBP, parametricName, kCustomObjectPrefNever );
	MCObjectHandle hParametric = ::GS_CreateCustomObject( gCBP, parametricName, location, angle );
	VWFC_ASSERT( hParametric );
//	if ( hParametric == NULL )
//		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create parametric" );
	this->SetParametricHandle( hParametric );
}

VWParametricObj::VWParametricObj(const TXString& parametricName, MCObjectHandle hPathObject)
: VWGroupObj( 0 )	// call nothing doing constructor -- we dont want a new group created
{
	::GS_DefineCustomObject( gCBP, parametricName, kCustomObjectPrefNever );
	MCObjectHandle hParametric = ::GS_CreateCustomObjectPath( gCBP, parametricName, hPathObject, NULL );
	VWFC_ASSERT( hParametric );
//	if ( hParametric == NULL )
//		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create parametric" );
	this->SetParametricHandle( hParametric );
}

VWParametricObj::VWParametricObj(const VWParametricObj& src)
: VWGroupObj(0)
{
	this->SetParametricHandle( src.fhObject );
}


// this is constructor for inheritant of this class
// so this class will not create a new parametric but let the inheritant do that job
VWParametricObj::VWParametricObj(Sint32) : VWGroupObj(0)
{
	
}


VWParametricObj::~VWParametricObj()
{
}

VWParametricObj& VWParametricObj::operator=(const VWParametricObj& src)
{
	this->SetParametricHandle( src.fhObject );
	return *this;
}

// get the world transform.
// currently: get the object matrix to the layer if object is inside a layer.
void VWParametricObj::GetObjectToWorldTransform(VWTransformMatrix& out) const
{
	TransformMatrix	matrix;
	::GS_GetEntityMatrix( gCBP, fhObject, matrix );
	out		= matrix;
}

bool VWParametricObj::IsParametricObject(MCObjectHandle hObj)
{
	return gSDK->GetObjectTypeN( hObj ) == kParametricNode;
}

/*static*/ bool VWParametricObj::IsParametricObject(MCObjectHandle hObj, const TXString& name)
{
	if ( !IsParametricObject( hObj ) )
		return false;

	bool	bFound	= false;
	MCObjectHandle	hRecord	= ::GS_FindAuxObject( gCBP, hObj, recordNode );
	MCObjectHandle	hFormat	= NULL;
	while( hRecord && ! bFound ){
		hFormat = ::GS_GetDefinition( gCBP, (MCObjectHandle) hRecord );
		if ( hFormat ) {
			TFormatHandler		currFormatHandler( hFormat );
			if ( currFormatHandler.IsParametric() ) {
				// If we find a recordNode on the aux list of the kParametricNode, and its formatNode has the parametric bit set,
				// then we can assume it is "the one".  No name checking is necessary.  JAK 9/27/99 Fix for VW 8.5.0.
				bFound = true;
			}
		}

		if ( ! bFound ) {
			// loop increment
			hRecord = ::GS_NextAuxObject( gCBP, ::GS_NextObject( gCBP, hRecord ), recordNode );
		}
	}

	if ( hFormat == NULL )
		return false;

	TFormatHandler	fh( hFormat );

	return fh.GetNameOfFormat() == name;
}

/*static*/ bool VWParametricObj::IsParametricObject(MCObjectHandle hObj, TInternalID inInternalID)
{
	return IsParametricObject( hObj ) && GetInternalID( hObj ) == inInternalID;
}

void VWParametricObj::SetParametricHandle(MCObjectHandle hParametric)
{
	fhObject		= hParametric;

	bool	bFound	= false;

	// Loop to find record among all record nodes on aux list.
	MCObjectHandle	hRecord	= ::GS_FindAuxObject( gCBP, hParametric, recordNode );
	MCObjectHandle	hFormat	= NULL;
	while( hRecord && ! bFound ){
		hFormat = ::GS_GetDefinition( gCBP, (MCObjectHandle) hRecord );
		if ( hFormat ) {
			TFormatHandler		currFormatHandler( hFormat );
			if ( currFormatHandler.IsParametric() ) {
				// If we find a recordNode on the aux list of the kParametricNode, and its formatNode has the parametric bit set,
				// then we can assume it is "the one".  No name checking is necessary.  JAK 9/27/99 Fix for VW 8.5.0.
				bFound = true;
			}
		}

		if ( ! bFound ) {
			// loop increment
			hRecord = ::GS_NextAuxObject( gCBP, ::GS_NextObject( gCBP, hRecord ), recordNode );
		}
	}
	
	fhParamRecord	= bFound ? hRecord : NULL;
	fhParamFormat	= bFound ? hFormat : NULL;
}

TXString VWParametricObj::GetParametricName() const
{
	TFormatHandler	fh( fhParamFormat );

	return fh.GetNameOfFormat();
}

TXString VWParametricObj::GetLocalizedParametricName() const
{
	TXString	localizedName;
	VERIFYN( kYKostadinov, gSDK->GetLocalizedPluginName( this->GetParametricName(), localizedName ) );
	return localizedName;
}

MCObjectHandle VWParametricObj::GetObjectPath() const
{
	return ::GS_GetCustomObjectPath( gCBP, fhObject );
}

void VWParametricObj::SetObjectPath(MCObjectHandle hPathGroup)
{
	::GS_SetCustomObjectPath( gCBP, fhObject, hPathGroup );
}

MCObjectHandle VWParametricObj::GetObjectProfileGroup() const
{
	return ::GS_GetCustomObjectProfileGroup( gCBP, fhObject );
}

void VWParametricObj::SetObjectProfileGroup(MCObjectHandle hProfileGroup)
{
	VERIFYN( kVStanev, ::GS_SetCustomObjectProfileGroup( gCBP, fhObject, hProfileGroup ) );
}

VWRecordFormatObj VWParametricObj::GetRecordFormat() const
{
	return VWRecordFormatObj( fhParamFormat );
}

VWRecordObj VWParametricObj::GetRecord() const
{
	return VWRecordObj( fhParamRecord );
}

VWPoint2D VWParametricObj::GetPointObjectPos() const
{
	VWTransformMatrix	matrix;
	this->GetObjectMatrix( matrix );
	return matrix.GetOffset();
}

void VWParametricObj::SetPointObjectPos(const VWPoint2D& pt)
{
	VWTransformMatrix	matrix;
	this->GetObjectMatrix( matrix );
	matrix.SetOffset( pt );
	this->SetObjectMatrix( matrix );
}

VWPoint3D VWParametricObj::GetObjectModelPos() const
{
	return this->GetObjectModelMatrix().GetOffset();
}

void VWParametricObj::SetObjectModelPos( const VWPoint3D& pt )
{
	VWTransformMatrix	modelMatrix = this->GetObjectModelMatrix();
	modelMatrix.SetOffset( pt );
	this->SetObjectModelMatrix( modelMatrix );
}

void VWParametricObj::GetLinearObjectPos(VWPoint2D& outA, VWPoint2D& outB) const
{
	WorldPt			startPt;
	WorldPt			endPt;
	::GS_GetEndPoints( gCBP, fhObject, startPt, endPt );

	outA			= startPt;
	outB			= endPt;		
}

void VWParametricObj::SetLinearObjectPos(const VWPoint2D& a, const VWPoint2D& b)
{
	::GS_SetEndPoints( gCBP, fhObject, a, b );
}

void VWParametricObj::EnableParameter_OBSOLETE(size_t paramIndex, bool bEnabled)
{
	// NOTE! 'GS_SetParameterVisibility' return 1 based value
	::GS_EnableParameter( gCBP, fhObject, (short) paramIndex+1, bEnabled );
}

void VWParametricObj::SetControlPtVisibility(size_t ctrlPtIndex, bool bVisible)
{
	// NOTE! 1 based index value
	::GS_SetCustomObjectControlPointVisibility( gCBP, fhObject, DemoteTo<short>( kVStanev, ctrlPtIndex + 1 ), bVisible );
}

void VWParametricObj::SetParameterVisibility_OBSOLETE(size_t paramIndex, bool bVisible)
{
	// NOTE! 'GS_SetParameterVisibility' return 1 based value
	::GS_SetParameterVisibility( gCBP, fhObject, (short) paramIndex+1, bVisible );
}

size_t VWParametricObj::GetParamsCount() const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	TRecordHandler rh( fhParamRecord );
	return (size_t) rh.GetNumOfFields();
}

TXString VWParametricObj::GetParamName(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return TXString();

	TRecordHandler rh( fhParamRecord );

	TXString	nameOfField;
	// NOTE! 'GetNameOfField' return 1 based value
	rh.GetNameOfField( DemoteTo<short>( kVStanev, paramIndex+1 ), nameOfField );
	return nameOfField;
}

TXString VWParametricObj::GetParamLocalizedName(size_t paramIndex) const
{
	TXString			paramName;

	// If we get there, there is no Chc object in the resoource with the specified index
	// We try to look for choices using the ParametricProvider

	using namespace VectorWorks::Extension;

	IExtendedPropsPtr		extProps( IID_ExtendedProps );
	CodeRefID				codeRefID		= 0;
	extProps->GetCodeRefID( GetThisObject(), codeRefID );
	TParametricFileIndex	fileIndex		= 0;
	extProps->GetFileIndex( codeRefID, fileIndex );
	IExtension*				extension		= extProps->GetExtension( fileIndex );
	IEventSinkPtr			eventSink( extension, IID_ParametricParamsProvider );

	// dynamic_cast doesn't work on Mac so we dont use it
	IParametricParamsProvider*	modifProvider	=  (IParametricParamsProvider*)( (IVWUnknown*) eventSink );

	if ( modifProvider ) {
		TXStringArray uniNames,localNames;
		paramName	= modifProvider->GetParamNameAt( paramIndex );
	}
	else
	{
		VWRecordFormatObj	formatObj		= this->GetRecordFormat();
		TXString			formatName		= formatObj.GetFormatName();
		paramName							= formatObj.GetParamName( paramIndex );
		TXString			paramLocName	= paramName;
		bool				isLocalized		= false;
		if ( formatObj.IsParametric() )
		{
			if ( gSDK->GetLocalizedPluginParameter( formatName, paramName, paramLocName ) )
			{
				paramName	= paramLocName;
				isLocalized = true;
			}
		}

		if ( !isLocalized )
		{
			// Current parameter resource not found.  Look for old resource type ('PARM').
			paramName	= this->GetParamName( paramIndex );
		}
	}

	return paramName;
}

size_t VWParametricObj::GetParamIndex(const TXString& paramName) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return (size_t) -1;	// not found

	TRecordHandler rh( fhParamRecord );
	// NOTE! 'GetFieldIndex' return 1 based value
	Sint32		index	= rh.GetFieldIndex( paramName );
	if ( index == 0 )
		return (size_t) -1;	// not found

	return (size_t) (index - 1); 
}

EFieldStyle VWParametricObj::GetParamStyle(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return kFieldLongInt;	// Error default value

	TRecordHandler rh( fhParamRecord );
	// NOTE! 'GetFieldStyle' return 1 based value
	return (EFieldStyle) rh.GetFieldStyle( DemoteTo<short>( kVStanev, paramIndex+1 ) );
}

TXString VWParametricObj::GetParamValue(size_t paramIndex) const
{
	TXString	value;
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return value;

	TRecordHandler rh( fhParamRecord );
//	TFormatHandler fh( fhParamFormat );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	EFieldStyle		style		= (EFieldStyle) rh.GetFieldStyle( itemIndex );
	TRecordItem valueItem( style );
	Boolean			ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	if ( style == kFieldText ) {
		if ( ok ) {
			valueItem.GetFieldValue( value );
		}
	}
	else {
		TXString		theString;
		if ( valueItem.GetFieldValueAsString( theString ) ) {
			value	= theString;
		}
	}

	return value;
}

void VWParametricObj::SetParamValue(size_t paramIndex, const TXString& value)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	EFieldStyle		style		= (EFieldStyle) rh.GetFieldStyle( itemIndex );
	TRecordItem		recItem( style );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) ) {
		TXString currFieldValue;
		// Check if the current value is the same as the new value. If it is, we can skip SetFieldObject below.
		if ( !recItem.GetFieldValueAsString( currFieldValue ) || !currFieldValue.Equal( value ) )
		{
			if ( style == kFieldText ) {
				const UCChar* szText	= value;
				size_t		textLen		= value.GetLength();

				if ( VWFC_VERIFY( recItem.SetFieldValue( szText, textLen ) ) ) {
					VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
				}
			}
			else {
			
				if ( VWFC_VERIFY( recItem.SetFieldValueAsString( value ) ) ) {
					VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
				}
			}
		}
	}
}

Sint32 VWParametricObj::GetParamLong(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	TRecordHandler rh( fhParamRecord );
//	TFormatHandler fh( fhParamFormat );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	Sint32		value	= 0;
	if ( ok ) {
		valueItem.GetFieldValue( value );
	}

	return value;
}

void VWParametricObj::SetParamLong(size_t paramIndex, Sint32 value)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) ) {
		if ( VWFC_VERIFY( recItem.SetFieldValue( value ) ) ) {
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

bool VWParametricObj::GetParamBool(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	TRecordHandler rh( fhParamRecord );
//	TFormatHandler fh( fhParamFormat );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	Boolean		value	= 0;
	if ( ok ) {
		valueItem.GetFieldValue( value );
	}

	return value ? true : false;
}

void VWParametricObj::SetParamBool(size_t paramIndex, bool value)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) ) {
		Boolean		boolValue	= value;
		if ( VWFC_VERIFY( recItem.SetFieldValue( boolValue ) ) ) {
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

double VWParametricObj::GetParamReal(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	TRecordHandler rh( fhParamRecord );
//	TFormatHandler fh( fhParamFormat );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	double		value	= 0;
	if ( ok ) {
		valueItem.GetFieldValue( value );
	}

	return value;
}

void VWParametricObj::SetParamReal(size_t paramIndex, double value)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) ) {
		if ( VWFC_VERIFY( recItem.SetFieldValue( value ) ) ) {
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

TXString VWParametricObj::GetParamString(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return "";

	TRecordHandler rh( fhParamRecord );
//	TFormatHandler fh( fhParamFormat );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok		= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	TXString	value;
	if ( ok ) {
		valueItem.GetFieldValue( value );
	}

	return value;
}

void VWParametricObj::SetParamString(size_t paramIndex, const TXString& value)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );
//	TFormatHandler	fh( fhParamFormat );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) ) {
		TXString currFieldValue;
		// Check if the current value is the same as the new value. If it is, we can skip SetFieldObject below.
		if ( !recItem.GetFieldValueAsString( currFieldValue ) || !currFieldValue.Equal( value ) )
		{
			if ( VWFC_VERIFY( recItem.SetFieldValue( value ) ) )
			{
				VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
			}
		}
	}
}

InternalIndex VWParametricObj::GetParamClass(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	InternalIndex		value	= 0;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	if ( ok )
	{
		valueItem.GetFieldClass( value );
	}

	return value;
}

void VWParametricObj::SetParamClass(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.SetFieldClass( resource ) ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

InternalIndex VWParametricObj::GetParamBuildingMaterial(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	InternalIndex		value	= 0;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	if ( ok )
	{
		valueItem.GetFieldBuildingMaterial( value );
	}

	return value;
}

void VWParametricObj::SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.SetFieldBuildingMaterial( resource ) ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

VWPattern VWParametricObj::GetParamFill(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return VWPattern( true );

	VWPattern		value( true );

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	InternalIndex resource;
	ok = ok && valueItem.GetFieldFill( resource );
	if ( ok )
	{
		value = VWPattern( resource, true );
	}


	return value;
}

void VWParametricObj::SetParamFill(size_t paramIndex, const VWPattern& attr)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY(recItem.SetFieldFill( attr )) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

VWPattern VWParametricObj::GetParamPenStyle(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return VWPattern( false );

	VWPattern		value( false );

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	InternalIndex resource;
	ok = ok && valueItem.GetFieldPenStyle( resource );
	if ( ok )
	{
		value = VWPattern( resource, false );
	}

	return value;
}

void VWParametricObj::SetParamPenStyle(size_t paramIndex, const VWPattern& attr)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY(recItem.SetFieldPenStyle( attr )) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

Uint8 VWParametricObj::GetParamPenWeight(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	Uint8		value	= 0;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	if ( ok )
	{
		valueItem.GetFieldPenWeight( value );
	}

	return value;
}

void VWParametricObj::SetParamPenWeight(size_t paramIndex, Uint8 value)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.SetFieldPenWeight( value ) ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

ColorRef VWParametricObj::GetParamColor(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	ColorRef		value	= 0;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	if ( ok )
	{
		valueItem.GetFieldColor( value );
	}

	return value;
}

void VWParametricObj::SetParamColor(size_t paramIndex, ColorRef value)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.SetFieldColor( value ) ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

InternalIndex VWParametricObj::GetParamTexture(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	InternalIndex		value	= 0;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	if ( ok )
	{
		valueItem.GetFieldTexture( value );
	}

	return value;
}

void VWParametricObj::SetParamTexture(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.SetFieldTexture( resource ) ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

InternalIndex VWParametricObj::GetParamSymDef(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return 0;

	InternalIndex		value	= 0;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	if ( ok )
	{
		valueItem.GetFieldSymDef( value );
	}

	return value;
}

void VWParametricObj::SetParamSymDef(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.SetFieldSymDef( resource ) ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

TXString VWParametricObj::GetParamAsString(size_t paramIndex) const
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return "";

	TRecordHandler rh( fhParamRecord );
//	TFormatHandler fh( fhParamFormat );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
	Boolean		ok		= rh.GetFieldObject( itemIndex, valueItem );
	VWFC_ASSERT( ok );

	TXString	value;
	if ( ok ) {
		valueItem.GetFieldValueAsString( value );
	}

	return value;
}

void VWParametricObj::SetParamAsString(size_t paramIndex, const TXString& value)
{
	VWFC_ASSERT( fhParamFormat && fhParamRecord );
	if ( fhParamFormat == NULL || fhParamRecord == NULL )
		return;

	TRecordHandler	rh( fhParamRecord );
//	TFormatHandler	fh( fhParamFormat );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) ) {
		const char* szText		= value;
		TXString	currFieldValue;
		// Check if the current value is the same as the new value. If it is, we can skip SetFieldObject below.
		if ( !recItem.GetFieldValueAsString( currFieldValue ) || !currFieldValue.Equal( value ) )
		{
			if ( VWFC_VERIFY( recItem.SetFieldValueAsString( szText ) ) )
			{
				VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
			}
		}
	}
}



double VWParametricObj::Get2DRotation180() const
{
	VWTransformMatrix	mat;
	this->GetObjectToWorldTransform( mat );

	VWPoint2D	pt	= mat.GetUVector();
	return	pt.CalcAng180(); 
}

double VWParametricObj::Get2DRotation360() const
{
	VWTransformMatrix	mat;
	this->GetObjectToWorldTransform( mat );

	VWPoint2D	pt	= mat.GetUVector();
	return	pt.CalcAng360(); 
}

bool VWParametricObj::GetParamChoices(size_t paramIndex, TXStringSTLArray& outArray) const
{
	outArray.clear();

	// If we get there, there is no Chc object in the resoource with the specified index
	// We try to look for choices using the ParametricProvider

	using namespace VectorWorks::Extension;

	IExtendedPropsPtr		extProps( IID_ExtendedProps );
	CodeRefID				codeRefID		= 0;
	extProps->GetCodeRefID( GetThisObject(), codeRefID );
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
	else
	{
		using namespace VectorWorks::Extension;

		IExtendedPropsPtr		extProps( IID_ExtendedProps );
		CodeRefID				codeRefID		= 0;
		extProps->GetCodeRefID( GetThisObject(), codeRefID );
		TParametricFileIndex	fileIndex		= 0;
		extProps->GetFileIndex( codeRefID, fileIndex );
		IExtendedPropsSupportPtr	support( IID_ExtendedPropsSupport );
		TXStringSTLArray	arrResult;
		ok = support->GetParamChoices( fileIndex, paramIndex, arrResult, false );
		if ( ok )
		{
			for(size_t i=0, cnt=arrResult.size(); i<cnt; i+=2)
			{
				outArray.push_back(arrResult[i]);
			}
		}
	}

	return ok;
}

bool VWParametricObj::GetParamLocalizedChoices(size_t paramIndex, TXStringSTLArray& outArray) const
{
	using namespace VectorWorks::Extension;

	IExtendedPropsPtr		extProps( IID_ExtendedProps );
	CodeRefID				codeRefID		= 0;
	extProps->GetCodeRefID( GetThisObject(), codeRefID );
	TParametricFileIndex	fileIndex		= 0;
	extProps->GetFileIndex( codeRefID, fileIndex );
	IExtendedPropsSupportPtr	support( IID_ExtendedPropsSupport );
	return support->GetParamChoices( fileIndex, paramIndex, outArray );
}

bool VWParametricObj::GetParamLocalizedChoiceFromString(const TXString& paramName, const TXString& universalName, TXString& outLocalizedName) const
{
	bool ok = false;
	outLocalizedName = universalName; //return the universal name it it fails
	VWParametricObj paramObj( fhObject );
	if ( paramObj.GetParamStyle( paramName ) == kFieldPopUp )
	{
		size_t paramIndex = paramObj.GetParamIndex( paramName );
		TXStringSTLArray arrChoices, arrChoicesLocalized;
		paramObj.GetParamChoices( paramIndex, arrChoices );
		paramObj.GetParamLocalizedChoices( paramIndex, arrChoicesLocalized );
		for(size_t i=0, cnt=arrChoices.size(); i<cnt; i++)
		{
			if ( universalName.EqualNoCase(arrChoices[i]) )
			{
				outLocalizedName = arrChoicesLocalized[i];
				ok = true;
			}
		}
	}
	return ok;
}

/*static*/ MCObjectHandle VWParametricObj::DefineCustomObject(const TXString& name, bool bShowPrefs)
{
	return ::GS_DefineCustomObject( gCBP, name, bShowPrefs ? kCustomObjectPrefAlways : kCustomObjectPrefNever );
}

size_t VWParametricObj::GetParamIndexByUnivName(const TXString& univParamName) const
{
	size_t	paramIndex	= size_t(-1);

	// this little hach but we want to be able to change the this
	// this is needed for performance optimization
	// so we would add the parameters only when they are needed
	// not for every parameter in the contrustor
	VWParametricObj*	pThis = (VWParametricObj*)( this );

	TXString	macUnivParamName	= univParamName;
	TUnviNameKeyMap::iterator	it = pThis->fmapUnivNameKey.find( macUnivParamName );
	if ( it == pThis->fmapUnivNameKey.end() ) {
		TRecordHandler rh( fhParamRecord );
		// NOTE! 'GetFieldIndex' return 1 based value
		Sint32		index	= rh.GetFieldIndex( macUnivParamName );
		if ( index != 0 ) {
			paramIndex	= (size_t) (index - 1); 
		}

		pThis->fmapUnivNameKey.insert( TUnviNameKeyMap::value_type( macUnivParamName, paramIndex ) );
	}
	else {
		paramIndex	= it->second;
	}

	return paramIndex;
}

EFieldStyle VWParametricObj::GetParamStyle(const TXString& univParamName) const
{
	return this->GetParamStyle( this->GetParamIndexByUnivName( univParamName ) );
}

TXString VWParametricObj::GetParamValue(const TXString& univParamName) const
{
	return this->GetParamValue( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamValue(const TXString& univParamName, const TXString& value)
{
	this->SetParamValue( this->GetParamIndexByUnivName( univParamName ), value );
}

Sint32 VWParametricObj::GetParamLong(const TXString& univParamName) const
{
	return this->GetParamLong( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamLong(const TXString& univParamName, Sint32 value)
{
	this->SetParamLong( this->GetParamIndexByUnivName( univParamName ), value );
}

bool VWParametricObj::GetParamBool(const TXString& univParamName) const
{
	return this->GetParamBool( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamBool(const TXString& univParamName, bool value)
{
	this->SetParamBool( this->GetParamIndexByUnivName( univParamName ), value );
}

double VWParametricObj::GetParamReal(const TXString& univParamName) const
{
	return this->GetParamReal( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamReal(const TXString& univParamName, double value)
{
	this->SetParamReal( this->GetParamIndexByUnivName( univParamName ), value );
}

TXString VWParametricObj::GetParamString(const TXString& univParamName) const
{
	return this->GetParamString( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamString(const TXString& univParamName, const TXString& value)
{
	this->SetParamString( this->GetParamIndexByUnivName( univParamName ), value );
}

InternalIndex VWParametricObj::GetParamClass(const TXString& univParamName) const
{
	return this->GetParamClass( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamClass(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamClass( this->GetParamIndexByUnivName( univParamName ), resource );
}

InternalIndex VWParametricObj::GetParamBuildingMaterial(const TXString& univParamName) const
{
	return this->GetParamBuildingMaterial( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamBuildingMaterial( this->GetParamIndexByUnivName( univParamName ), resource );
}

VWPattern VWParametricObj::GetParamFill(const TXString& univParamName) const
{
	return this->GetParamFill( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamFill(const TXString& univParamName, const VWPattern& attr)
{
	this->SetParamFill( this->GetParamIndexByUnivName( univParamName ), attr );
}

VWPattern VWParametricObj::GetParamPenStyle(const TXString& univParamName) const
{
	return this->GetParamPenStyle( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamPenStyle(const TXString& univParamName, const VWPattern& attr)
{
	this->SetParamPenStyle( this->GetParamIndexByUnivName( univParamName ), attr );
}

Uint8 VWParametricObj::GetParamPenWeight(const TXString& univParamName) const
{
	return this->GetParamPenWeight( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamPenWeight(const TXString& univParamName, Uint8 value)
{
	this->SetParamPenWeight( this->GetParamIndexByUnivName( univParamName ), value );
}

ColorRef VWParametricObj::GetParamColor(const TXString& univParamName) const
{
	return this->GetParamColor( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamColor(const TXString& univParamName, ColorRef value)
{
	this->SetParamColor( this->GetParamIndexByUnivName( univParamName ), value );
}

InternalIndex VWParametricObj::GetParamTexture(const TXString& univParamName) const
{
	return this->GetParamTexture( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamTexture(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamTexture( this->GetParamIndexByUnivName( univParamName ), resource );
}

InternalIndex VWParametricObj::GetParamSymDef(const TXString& univParamName) const
{
	return this->GetParamSymDef( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamSymDef(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamSymDef( this->GetParamIndexByUnivName( univParamName ), resource );
}

TXString VWParametricObj::GetParamAsString(const TXString& univParamName) const
{
	return this->GetParamAsString( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamAsString(const TXString& univParamName, const TXString& value)
{
	this->SetParamAsString( this->GetParamIndexByUnivName( univParamName ), value );
}

VWPoint2D VWParametricObj::GetParamCtrlPt(const TXString& univParamNameX) const
{
	VWPoint2D	result;
	size_t		len	= univParamNameX.GetLength();
	if ( len > 0 )
	{
		TXString	univParamNameY = univParamNameX;
		univParamNameY.SetAt( len - 1, 'Y' );

		result.x = this->GetParamReal( univParamNameX );
		result.y = this->GetParamReal( univParamNameY );
	}

	return result;
}

void VWParametricObj::SetParamCtrlPt(const TXString& univParamNameX, const VWPoint2D& pt)
{
	size_t		len	= univParamNameX.GetLength();
	if ( len > 0 )
	{
		TXString	univParamNameY = univParamNameX;
		univParamNameY.SetAt( len - 1, 'Y' );

		this->SetParamReal( univParamNameX, pt.x );
		this->SetParamReal( univParamNameY, pt.y );
	}
}

size_t VWParametricObj::PopupGetChoicesCount(const TXString& univParamName) const
{
	size_t result = 0;

	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	size_t paramIndex = this->GetParamIndexByUnivName( univParamName );
	if ( paramIndex != size_t(-1) )
	{
		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, valueItem ) ) )
		{
			result = valueItem.PopupGetChoicesCount();
		}
	}

	return result;
}

void VWParametricObj::PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue) const
{
	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	size_t paramIndex = this->GetParamIndexByUnivName( univParamName );
	if ( paramIndex != size_t(-1) )
	{
		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, valueItem ) ) )
		{
			VWFC_VERIFY( valueItem.PopupGetChoice( index, outKey, outValue ) );
		}
	}
}

void VWParametricObj::PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs) const
{
	outKeyValuePairs.clear();

	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short itemIndex	= rh.GetFieldIndex( univParamName );
	if ( itemIndex > 0 )
	{
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, valueItem ) ) )
		{
			size_t	choicesCount	= valueItem.PopupGetChoicesCount();

			TXString	key;
			TXString	value;
			for ( size_t i = 0; i < choicesCount; i++ )
			{
				VWFC_VERIFY( valueItem.PopupGetChoice( i, key, value ) );
				outKeyValuePairs.emplace_back( key, value );
			}
		}
	}
}

void VWParametricObj::PopupClearChoices(const TXString& univParamName)
{
	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	size_t paramIndex = this->GetParamIndexByUnivName( univParamName );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.PopupClearChoices() ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

void VWParametricObj::PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append)
{
	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	size_t paramIndex = this->GetParamIndexByUnivName( univParamName );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.PopupSetChoices( keyValuePairs, append ) ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

size_t VWParametricObj::PopupGetChoicesCount(size_t paramIndex) const
{
	size_t result = 0;

	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	if ( paramIndex != size_t(-1) )
	{
		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, valueItem ) ) )
		{
			result = valueItem.PopupGetChoicesCount();
		}
	}

	return result;
}

void VWParametricObj::PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue) const
{
	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	if ( paramIndex != size_t(-1) )
	{
		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, valueItem ) ) )
		{
			VWFC_VERIFY( valueItem.PopupGetChoice( index, outKey, outValue ) );
		}
	}
}

void VWParametricObj::PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs) const
{
	outKeyValuePairs.clear();

	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	if ( itemIndex > 0 )
	{
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, valueItem ) ) )
		{
			size_t	choicesCount	= valueItem.PopupGetChoicesCount();

			TXString	key;
			TXString	value;
			for ( size_t i = 0; i < choicesCount; i++ )
			{
				VWFC_VERIFY( valueItem.PopupGetChoice( i, key, value ) );
				outKeyValuePairs.emplace_back( key, value );
			}
		}
	}
}

void VWParametricObj::PopupClearChoices(size_t paramIndex)
{
	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.PopupClearChoices() ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

void VWParametricObj::PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append)
{
	VWFC_ASSERT( fhParamRecord );
	TRecordHandler	rh( fhParamRecord );

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
	TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
	if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
	{
		if ( VWFC_VERIFY( recItem.PopupSetChoices( keyValuePairs, append ) ) )
		{
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
		}
	}
}

/*static*/ MCObjectHandle VWParametricObj::GetRecordFormat(MCObjectHandle hParametric, MCObjectHandle hDefault)
{
	MCObjectHandle hFormat	= hDefault;
	if ( VWParametricObj::IsParametricObject( hParametric ) ) {
		VWParametricObj	obj( hParametric );
		hFormat	= obj.fhParamFormat;
	}

	return hFormat;
}

/*static*/ MCObjectHandle VWParametricObj::GetRecord(MCObjectHandle hParametric, MCObjectHandle hDefault)
{
	MCObjectHandle hRecord	= hDefault;
	if ( VWParametricObj::IsParametricObject( hParametric ) ) {
		VWParametricObj	obj( hParametric );
		hRecord	= obj.fhParamRecord;
	}

	return hRecord;
}

TInternalID VWParametricObj::GetInternalID() const
{
	return GetInternalID( fhObject );
}

/*static*/ TInternalID VWParametricObj::GetInternalID(MCObjectHandle hParametric)
{
	TVariableBlock	internalIDVar;
	gSDK->GetObjectVariable( hParametric, ovParametricInternalID, internalIDVar );
	short			internalID	= 0;
	internalIDVar.GetSint16( internalID );
	return internalID;
}

void VWParametricObj::AnalyzeAndUpdateTransformMatrix( bool & paramNeedsFlipping )
{
	paramNeedsFlipping = false;

	VWTransformMatrix paramMatrix;
	this->GetObjectMatrix( paramMatrix ); 

	if ( paramMatrix.IsFlipped() )
	{
		// this is the case of the object in the document
		// un flip the matrix
		paramMatrix.SetUVector( - paramMatrix.GetUVector() );
		this->SetObjectMatrix( paramMatrix );

		// and flip the open direction
		paramNeedsFlipping	= true;
	} 

	MCObjectHandle hParentWall = NULL;
	bool foundBreak = false;
	SWallSymbolBreak theBreak; 

	// find the corresponding break for this object in the parent wall if any
	if ( VWWallObj::IsWallObject( this->GetParentObject() ) )
	{
		hParentWall = this->GetParentObject();

		// this is the case of the object in a wall
		VWWallObj parentWallObj( hParentWall );
		foundBreak = parentWallObj.FindBreak( fhObject, theBreak );

		// we have a break, so reverse it
		if ( foundBreak && hParentWall && theBreak.symBreak.flipH )
		{
			theBreak.symBreak.flipH = false; // never flip
			theBreak.symBreak.theSymbol = NULL; // clean the symbol, so it doesn't get duplicated
			// we're just changing insertion option, so this is ok
			VWWallObj(hParentWall).SetBreak( theBreak );
		}
	} 

}

ESymbolDefType VWParametricObj::GetSymType() const
{
	ESymbolDefType	symbolType	= kSymbolDefType_Hybrid;

	TVariableBlock value;
	if ( gSDK->GetObjectVariable( fhObject, ovCustomObjectSymType, value ) )
	{
		short symTypeShort = 0;
		if ( value.GetSint16( symTypeShort ) )
		{
			symbolType	= (ESymbolDefType)symTypeShort;
		}
	}

	return symbolType;
}


RefNumber VWParametricObj::GetStyleRefNumber() const
{
	RefNumber num = 0;
	if ( fhObject ) {
		gSDK->GetPluginObjectStyle( fhObject, num );
	}
	return num;
}

MCObjectHandle VWParametricObj::GetStyleHandle() const
{
	RefNumber num = 0;
	MCObjectHandle retHandle = NULL;
	if ( fhObject ) {
		gSDK->GetPluginObjectStyle( fhObject, num );

		if ( num > 0 ) {
			retHandle = gSDK->InternalIndexToHandle( num );
		}
	}
	return retHandle;
}