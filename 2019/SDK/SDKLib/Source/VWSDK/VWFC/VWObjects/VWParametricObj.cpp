//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#ifdef _MINICAD_
    #include "ExternalsParametric.h"
#else
    #include "Kernel/CustomObjects.h"
#endif

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
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kParametricNode;
}

/*static*/ bool VWParametricObj::IsParametricObject(MCObjectHandle hObj, const TXString& name)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	if ( type != kParametricNode )
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
	short	type	= gSDK->GetObjectTypeN( hObj );
	if ( type != kParametricNode )
		return false;

	TVariableBlock	internalIDVar;
	gSDK->GetObjectVariable( hObj, ovParametricInternalID, internalIDVar );
	short			internalID	= 0;
	internalIDVar.GetSint16( internalID );

	return (internalID == inInternalID);
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

/*
enum EFieldStyle {
	kFieldLongInt		= 1,
	kFieldBoolean		= 2,
	kFieldReal			= 3,
	kFieldText			= 4,
	kFieldCalculation	= 5,
	kFieldHandle 		= 6,
	kFieldCoordDisp		= 7,
	kFieldPopUp			= 8,
	kFieldRadio			= 9,
	kFieldCoordLocX		= 10,	
	kFieldCoordLocY		= 11,
	kFieldStaticText	= 14
	
};
*/

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
		if ( style == kFieldText ) {
			const UCChar* szText		= value;
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

		if ( VWFC_VERIFY( recItem.SetFieldValue(value) ) ) {
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

		if ( VWFC_VERIFY( recItem.SetFieldValueAsString( szText ) ) ) {
			VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
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

TXString VWParametricObj::GetParamAsString(const TXString& univParamName) const
{
	return this->GetParamAsString( this->GetParamIndexByUnivName( univParamName ) );
}

void VWParametricObj::SetParamAsString(const TXString& univParamName, const TXString& value)
{
	this->SetParamAsString( this->GetParamIndexByUnivName( univParamName ), value );
}



VWPoint2D VWParametricObj::GetParamCtrlPt(const TXString& univParamNameX)
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
	TVariableBlock	internalIDVar;
	gSDK->GetObjectVariable( fhObject, ovParametricInternalID, internalIDVar );
	short			internalID	= 0;
	internalIDVar.GetSint16( internalID );
	return internalID;
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

RefNumber VWParametricObj::GetStyleRefNumber()
{
	RefNumber num = 0;
	if ( fhObject ) {
		gSDK->GetPluginObjectStyle( fhObject, num );
	}
	return num;
}

MCObjectHandle VWParametricObj::GetStyleHandle()
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