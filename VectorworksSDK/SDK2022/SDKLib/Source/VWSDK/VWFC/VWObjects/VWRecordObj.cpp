//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VWFC::VWObjects;

VWRecordObj::VWRecordObj(MCObjectHandle hRecordHandle, ERecordIFCWrapMode wrapMode)
{
	fhObject		= hRecordHandle;

	VWFC_ASSERT( VWRecordObj::IsRecordObject( fhObject ) );
	if ( ! VWRecordObj::IsRecordObject( fhObject ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );

	// we are interested if this is IFC record ONLY in default Auto mode. Otherwise use the wrapMode as
	// non-default input parameter 
	if ( wrapMode == ERecordIFCWrapMode::Auto )
	{
		this->SpecifyIFCRecordType();
	}
	else
	{
		fIFCMode = wrapMode;
	}
}

// bUseExistingRecord	- true then use the record in hObject of format hFormat if it exist - otherwise create record
//						- false then always create record object from the hFormat inside hObject
VWRecordObj::VWRecordObj(MCObjectHandle hFormat, MCObjectHandle hObject, bool bUseExistingRecord, ERecordIFCWrapMode wrapMode)
{
	// we are interested if this is IFC record ONLY in default Auto mode. Otherwise use the wrapMode as
	// non-default input parameter 
	if ( wrapMode == ERecordIFCWrapMode::Auto )
	{
		this->SpecifyIFCRecordType();
	}
	else
	{
		fIFCMode = wrapMode;
	}

	if ( hFormat == nullptr )
	{
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad format handle type when creating" );
	}
	else
	{
		MCObjectHandle		hRecord	= nullptr;
		if ( bUseExistingRecord )
		{
			TFormatHandler		fh( hFormat );
			hRecord		= fh.AttachRecordToObject( hObject ); 
		}
		else 
		{
			MCObjectHandle	hDefaultRecord	= ::GS_FindAuxObject( gCBP, hFormat, kRecordNode );
			ASSERTN( kVStanev, hDefaultRecord );
			hRecord							= ::GS_DuplicateObject( gCBP, hDefaultRecord );
			::GS_AttachAuxObject( gCBP, hRecord, hObject );

			// find the last object in the AUX list
			MCObjectHandle	hLastObj	= NULL;
			MCObjectHandle	hNextObj	= hRecord;
			while( hNextObj )
			{
				MCObjectHandle	hNextAux	= ::GS_NextObject( gCBP, hNextObj );
				hNextObj					= ::GS_NextAuxObject( gCBP, hNextAux, kRecordNode );
				if ( hNextObj )
				{
					hLastObj	= hNextObj;
				}
			}

			// attach this record at the end of the AUX list
			if ( hLastObj )
			{
				::GS_InsertObjectAfter( gCBP, hRecord, hLastObj );
			}
		}

		fhObject					= hRecord;

		VWFC_ASSERT( VWRecordObj::IsRecordObject( fhObject ) );
		if ( ! VWRecordObj::IsRecordObject( fhObject ) )
			THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	}
}

VWRecordObj::VWRecordObj(const VWRecordObj& src)
{
	fIFCMode	= src.fIFCMode;
	fhObject	= src.fhObject;
}

VWRecordObj::~VWRecordObj()
{
}

VWRecordObj& VWRecordObj::operator=(const VWRecordObj& src)
{
	fIFCMode	= src.fIFCMode;
	fhObject	= src.fhObject;
	return *this;
}

TXString VWRecordObj::GetRecordName() const
{
	VWFC_ASSERT( fhObject );
	TRecordHandler	rh( fhObject );
	
	return rh.GetNameOfFormat();
}

TXString VWRecordObj::GetRecordLocalizedName() const
{
	TXString	localizedName;

	VWFC_ASSERT( fhObject );
	TRecordHandler	rh( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		if ( rh.IsParametric() )
		{
			TVariableBlock	varName;
			gSDK->GetObjectVariable( fhObject, ovParametricLocalizedName, varName );
			if ( ! varName.GetTXString( localizedName ) )
			{
				localizedName	= rh.GetLocalizedName();
			}
		}
		else
		{
			localizedName	= rh.GetLocalizedName();
		}
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetRecordLocalizedName( fhObject, localizedName );	
		}
	}

	return localizedName;
}

bool VWRecordObj::SetRecordLocalizedName(const TXString& name)
{
	bool	result = false;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )	// IFC records and formats must be created and managed using the IFC Library
	{
		TRecordHandler	rh( fhObject );
		if ( ! rh.IsParametric() )
		{
			result = rh.SetLocalizedName( name );
		}
	}

	return result;
}

bool VWRecordObj::IsParametric() const
{
	bool	result	= false;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )	
	{
		TRecordHandler	rh( fhObject );
		result	= rh.IsParametric() ? true : false;
	}

	return result;
}

void VWRecordObj::SetParametric(bool bIsParametric)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );
		rh.SetIsParametric( bIsParametric );
	}
}

size_t VWRecordObj::GetParamsCount() const
{
	size_t	result	= size_t(-1);

	VWFC_ASSERT( fhObject );

	TRecordHandler	rh(fhObject);
	result	= (size_t)rh.GetNumOfFields();

	if ( fIFCMode == ERecordIFCWrapMode::IFC )
	{
		result = 2 + ((result - 2) / 3);
	}
	else if ( fIFCMode == ERecordIFCWrapMode::PSet )
	{
		result /= 3;
	}
	else if ( fIFCMode == ERecordIFCWrapMode::IFCTag )
	{
		result = 2;
	}

	return result;
}

TXString VWRecordObj::GetParamName(size_t paramIndex) const
{
	TXString	result;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! 'GetNameOfField' return 1 based value
		rh.GetNameOfField( DemoteTo<short>( kVStanev, paramIndex+1 ), result );
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamName(fhObject, paramIndex, result, VWRecordFormatObj::GetIfcRecordType(fIFCMode));
		}
	}

	return result;
}

TXString VWRecordObj::GetParamLocalizedName(size_t paramIndex) const
{
	TXString			paramName;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );
		if ( rh.IsParametric() )
		{
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

			if ( modifProvider )
			{
				TXStringArray uniNames,localNames;
				paramName	= modifProvider->GetParamNameAt( paramIndex );
			}
			else
			{
				// Current parameter resource not found.  Look for old resource type ('PARM').
				paramName	= this->GetParamName( paramIndex );
			}
		}
		else
		{
			// NOTE! 'GetNameOfField' return 1 based value
			rh.GetNameOfFieldLocalized( DemoteTo<short>( kVStanev, paramIndex+1 ), paramName );
		}
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamName(fhObject, paramIndex, paramName, VWRecordFormatObj::GetIfcRecordType(fIFCMode));
		}
	}

	return paramName;
}

bool VWRecordObj::SetParamLocalizedName(size_t paramIndex, const TXString& name)
{
	bool result = false;
	if ( ! this->IsIFCRecord() )	// IFC records and formats must be created and managed using the IFC Library
	{
		TRecordHandler	rh( fhObject );
		if ( ! rh.IsParametric() )
		{
			return rh.SetNameOfFieldLocalized( DemoteTo<short>( kVStanev, paramIndex+1 ), name );
		}
	}

	return result;
}

size_t VWRecordObj::GetParamIndex(const TXString& paramName) const
{
	size_t	result	= -1;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! 'GetFieldIndex' return 1 based value
		Sint32		index	= rh.GetFieldIndex( paramName );
		if ( index == 0 )
		{
			result	= (size_t) -1;	// not found
		}
		else
		{
			result	= (size_t)(index - 1);
		}
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamIndex(fhObject, paramName, result, VWRecordFormatObj::GetIfcRecordType(fIFCMode));
		}
	}

	return result;
}

EFieldStyle VWRecordObj::GetParamStyle(size_t paramIndex) const
{
	EFieldStyle	result	= (EFieldStyle)0;
	
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );
		
		// NOTE! 'GetFieldStyle' return 1 based value
		result	= (EFieldStyle) rh.GetFieldStyle( DemoteTo<short>( kVStanev, paramIndex+1 ) );
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamStyle(fhObject, paramIndex, result, VWRecordFormatObj::GetIfcRecordType(fIFCMode));
		}
	}

	return result;
}

TNumStyleClass	VWRecordObj::GetParamNumStyle(size_t paramIndex) const
{
	TNumStyleClass	numStyle = nsGeneral;

	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		VWFC_ASSERT( fhObject );
		TRecordHandler	rh( fhObject );
		Byte			accuracy;

		// NOTE! 'GetParamNumStyle' return 1 based value
		rh.GetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, accuracy );
	}
	
	return numStyle;
}

void VWRecordObj::SetParamNumStyle(size_t paramIndex, TNumStyleClass value)
{
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		VWFC_ASSERT( fhObject );
		TRecordHandler	rh( fhObject );
		TNumStyleClass  numStyle;
		Byte			accuracy;

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! 'GetFieldNumStyle' return 1 based value
			rh.GetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, accuracy );
			rh.SetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), value, accuracy );
		}
	}
}

Byte VWRecordObj::GetParamAccuracy(size_t paramIndex) const
{
	Byte	accuracy = 0;

	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		VWFC_ASSERT( fhObject );
		TRecordHandler	rh( fhObject );
		TNumStyleClass  numStyle;

		// NOTE! 'GetFieldNumStyle' return 1 based value
		rh.GetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, accuracy );
	}

	return accuracy;
}

void VWRecordObj::SetParamAccuracy(size_t paramIndex, Byte value)
{
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		VWFC_ASSERT( fhObject );
		TRecordHandler	rh( fhObject );
		TNumStyleClass  numStyle;
		Byte			accuracy;

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! 'GetFieldNumStyle' return 1 based value
			rh.GetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, accuracy );
			rh.SetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, value );
		}
	}
}

TXString VWRecordObj::GetParamValue(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );
	TXString	value;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		EFieldStyle		style		= (EFieldStyle) rh.GetFieldStyle( itemIndex );
		TRecordItem valueItem( style );
		Boolean			ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( style == kFieldText )
		{
			if ( ok )
			{
				valueItem.GetFieldValue( value );
			}
		}
		else
		{
			// If we fail to get the value as string, clear the contents 
			// of value just in case it is no longer empty
			if (!valueItem.GetFieldValueAsString( value ) )
			{
				value.Clear();
			}
		}
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamValue(fhObject, paramIndex, value, VWRecordFormatObj::GetIfcRecordType(fIFCMode));
		}
	}

	return value;
}

void VWRecordObj::SetParamValue(size_t paramIndex, const TXString& value)
{
	VWFC_ASSERT( fhObject );
	
	if ( this->IsIFCRecord() )
	{
		// get the correct paramInde for IFC records
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( !ifcSupport || VCOM_FAILED(ifcSupport->IFC_GetParamIndex(fhObject, paramIndex, paramIndex, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			paramIndex = -1;
		}
	}
	
	if ( paramIndex	!= -1 )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		EFieldStyle		style		= (EFieldStyle) rh.GetFieldStyle( itemIndex );
		TRecordItem		recItem( style );
		TXString 		currFieldValue;
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
		{
			// Check if the current value is the same as the new value. If it is, we can skip SetFieldObject below.
			if ( !recItem.GetFieldValueAsString( currFieldValue ) || !currFieldValue.Equal( value ) ) {
				if ( style == kFieldText )
				{
					const UCChar* szText	= value;
					size_t		textLen		= value.GetLength();

					if ( VWFC_VERIFY( recItem.SetFieldValue( szText, textLen ) ) )
					{
						VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
					}
				}
				else
				{
					if ( VWFC_VERIFY( recItem.SetFieldValueAsString( value ) ) )
					{
						VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
					}
				}
			}
		}
	}
}

Sint32 VWRecordObj::GetParamLong(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	Sint32		value	= 0;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldValue( value );
		}
	}
	else
	{
		TXString	paramValue;
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport && VCOM_SUCCEEDED(ifcSupport->IFC_GetParamValue(fhObject, paramIndex, paramValue, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			value = paramValue.atoi();
		}
	}

	return value;
}

void VWRecordObj::SetParamLong(size_t paramIndex, Sint32 value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
		{
			if ( VWFC_VERIFY( recItem.SetFieldValue( value ) ) )
			{
				VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
			}
		}
	}
	else
	{
		// get the correct paramInde for IFC records
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport || VCOM_SUCCEEDED(ifcSupport->IFC_GetParamIndex(fhObject, paramIndex, paramIndex, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			TXString	str;
			str << value;
			this->SetParamStringI( paramIndex, str );
		}
	}
}

bool VWRecordObj::GetParamBool(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	Boolean		value	= 0;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldValue( value );
		}
	}
	else
	{
		TXString	str;
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport && VCOM_SUCCEEDED(ifcSupport->IFC_GetParamValue(fhObject, paramIndex, str, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			value = str.EqualNoCase("true")  || str.EqualNoCase("yes")  || str.atoi() != 0;
		}
	}

	return value ? true : false;
}

void VWRecordObj::SetParamBool(size_t paramIndex, bool value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
		{
			Boolean		boolValue	= value;
			if ( VWFC_VERIFY( recItem.SetFieldValue( boolValue ) ) )
			{
				VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
			}
		}
	}
	else
	{
		// get the correct paramInde for IFC records
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport || VCOM_SUCCEEDED(ifcSupport->IFC_GetParamIndex(fhObject, paramIndex, paramIndex, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			this->SetParamStringI(paramIndex, value ? "true" : "false");
		}
	}
}

double VWRecordObj::GetParamReal(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	double		value	= 0;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldValue( value );
		}
	}
	else
	{
		TXString	paramValue;
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport && VCOM_SUCCEEDED(ifcSupport->IFC_GetParamValue(fhObject, paramIndex, paramValue, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			value = paramValue.atof();
		}
	}

	return value;
}

void VWRecordObj::SetParamReal(size_t paramIndex, double value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
		{
			if ( VWFC_VERIFY( recItem.SetFieldValue( value ) ) )
			{
				VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
			}
		}
	}
	else
	{
		// get the correct paramInde for IFC records
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport || VCOM_SUCCEEDED(ifcSupport->IFC_GetParamIndex(fhObject, paramIndex, paramIndex, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			TXString	str;
			str.Format("%f", value);
			this->SetParamStringI( paramIndex, str );
		}
	}
}

TXString VWRecordObj::GetParamString(size_t paramIndex) const
{
	TXString	value;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok		= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldValue( value );
		}
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamValue( fhObject, paramIndex, value, VWRecordFormatObj::GetIfcRecordType(fIFCMode) );
		}
	}

	return value;
}

void VWRecordObj::SetParamString(size_t paramIndex, const TXString& value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		this->SetParamStringI( paramIndex, value );
	}
	else
	{
		// get the correct paramInde for IFC records
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport || VCOM_SUCCEEDED(ifcSupport->IFC_GetParamIndex(fhObject, paramIndex, paramIndex, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			this->SetParamStringI( paramIndex, value );
		}
	}
}

InternalIndex VWRecordObj::GetParamClass(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	InternalIndex		value	= 0;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldClass( value );
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordObj::SetParamClass(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

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
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

InternalIndex VWRecordObj::GetParamBuildingMaterial(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	InternalIndex		value	= 0;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldBuildingMaterial( value );
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordObj::SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

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
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

VWPattern VWRecordObj::GetParamFill(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	VWPattern		value( true );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			InternalIndex resource;
			ok = valueItem.GetFieldFill( resource );
			if ( ok )
			{
				value = VWPattern( resource, true );
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordObj::SetParamFill(size_t paramIndex, const VWPattern& attr)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

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
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

VWPattern VWRecordObj::GetParamPenStyle(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	VWPattern		value( false );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

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
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordObj::SetParamPenStyle(size_t paramIndex, const VWPattern& attr)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

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
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

Uint8 VWRecordObj::GetParamPenWeight(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	Uint8		value	= 0;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldPenWeight( value );
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordObj::SetParamPenWeight(size_t paramIndex, Uint8 value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

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
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

ColorRef VWRecordObj::GetParamColor(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	ColorRef		value	= 0;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldColor( value );
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordObj::SetParamColor(size_t paramIndex, ColorRef value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

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
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

InternalIndex VWRecordObj::GetParamTexture(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	InternalIndex		value	= 0;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldTexture( value );
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordObj::SetParamTexture(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

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
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

InternalIndex VWRecordObj::GetParamSymDef(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	InternalIndex		value	= 0;
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
		Boolean		ok			= rh.GetFieldObject( itemIndex, valueItem );
		VWFC_ASSERT( ok );

		if ( ok )
		{
			valueItem.GetFieldSymDef( value );
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordObj::SetParamSymDef(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIFCRecord() )
	{
		TRecordHandler	rh( fhObject );

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
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

size_t VWRecordObj::GetParamIndexByUnivName(const TXString& univParamName) const
{
	size_t	paramIndex	= size_t(-1);

	// this little hack but we want to be able to change the this
	// this is needed for performance optimization
	// so we would add the parameters only when they are needed
	// not for every parameter in the constructor
	VWRecordObj*	pThis = (VWRecordObj*)( this );

	TUnviNameKeyMap::iterator	it = pThis->fmapUnivNameKey.find(univParamName);
	if ( it == pThis->fmapUnivNameKey.end() )
	{
		TRecordHandler rh( fhObject );
		// NOTE! 'GetFieldIndex' return 1 based value
		Sint32		index	= rh.GetFieldIndex(univParamName);
		if ( ! this->IsIFCRecord() )
		{
			if ( index != 0 )
			{
				paramIndex	= (size_t) (index - 1); 
			}
		}
		else
		{
			VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
			if ( ifcSupport )
			{
				ifcSupport->IFC_GetParamIndex(fhObject, index, paramIndex, VWRecordFormatObj::GetIfcRecordType(fIFCMode));
			}
		}

		pThis->fmapUnivNameKey.insert( TUnviNameKeyMap::value_type(univParamName, paramIndex ) );
	}
	else
	{
		paramIndex	= it->second;
	}

	return paramIndex;
}

void VWRecordObj::SpecifyIFCRecordType()
{
	// set IFC to false for default
	fIFCMode = ERecordIFCWrapMode::None;

	VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
	if ( ifcSupport )
	{
		TRecordHandler	fh(fhObject);
		TXString		name = fh.GetNameOfFormat();
		ERecordIFCType	type;
		if ( VCOM_SUCCEEDED(ifcSupport->IFC_IsIFCRecord(name, type)) )
		{
			switch ( type )
			{
			case ERecordIFCType::IFC:		fIFCMode = ERecordIFCWrapMode::IFC;		break;
			case ERecordIFCType::IFCTag:	fIFCMode = ERecordIFCWrapMode::IFCTag;	break;
			case ERecordIFCType::PSet:		fIFCMode = ERecordIFCWrapMode::PSet;	break;
			case ERecordIFCType::None:		fIFCMode = ERecordIFCWrapMode::None;	break;
			default:						fIFCMode = ERecordIFCWrapMode::None;	break;
			}
		}
	}
}

void VWRecordObj::SetParamStringI(size_t paramIndex, const TXString& value)
{
	TRecordHandler	rh(fhObject);

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
	TRecordItem		recItem(rh.GetFieldStyle(itemIndex));
	if ( VWFC_VERIFY(rh.GetFieldObject(itemIndex, recItem)) )
	{
		TXString currFieldValue;
		// Check if the current value is the same as the new value. If it is, we can skip SetFieldObject below.
		if ( !recItem.GetFieldValueAsString( currFieldValue ) || !currFieldValue.Equal( value ) )
		{
			const UCChar* szText = value;
			size_t		textLen = value.GetLength();

			if ( VWFC_VERIFY( recItem.SetFieldValue( szText, textLen ) ) )
			{
				VWFC_VERIFY( rh.SetFieldObject( itemIndex, recItem ) );
			}
		}
	}
}

EFieldStyle VWRecordObj::GetParamStyle(const TXString& univParamName) const
{
	return this->GetParamStyle( this->GetParamIndexByUnivName( univParamName ) );
}

TNumStyleClass	VWRecordObj::GetParamNumStyle(const TXString& univParamName) const
{
	return this->GetParamNumStyle( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamNumStyle(const TXString& univParamName, TNumStyleClass value)
{
	this->SetParamNumStyle( this->GetParamIndexByUnivName( univParamName ), value );
}

Byte VWRecordObj::GetParamAccuracy(const TXString& univParamName) const
{
	return this->GetParamAccuracy( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamAccuracy(const TXString& univParamName, Byte value)
{
	this->SetParamAccuracy( this->GetParamIndexByUnivName( univParamName ), value);
}


TXString VWRecordObj::GetParamValue(const TXString& univParamName) const
{
	return this->GetParamValue( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamValue(const TXString& univParamName, const TXString& value)
{
	this->SetParamValue( this->GetParamIndexByUnivName( univParamName ), value );
}

Sint32 VWRecordObj::GetParamLong(const TXString& univParamName) const
{
	return this->GetParamLong( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamLong(const TXString& univParamName, Sint32 value)
{
	this->SetParamLong( this->GetParamIndexByUnivName( univParamName ), value );
}

bool VWRecordObj::GetParamBool(const TXString& univParamName) const
{
	return this->GetParamBool( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamBool(const TXString& univParamName, bool value)
{
	this->SetParamBool( this->GetParamIndexByUnivName( univParamName ), value );
}

double VWRecordObj::GetParamReal(const TXString& univParamName) const
{
	return this->GetParamReal( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamReal(const TXString& univParamName, double value)
{
	this->SetParamReal( this->GetParamIndexByUnivName( univParamName ), value );
}

TXString VWRecordObj::GetParamString(const TXString& univParamName) const
{
	return this->GetParamString( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamString(const TXString& univParamName, const TXString& value)
{
	this->SetParamString( this->GetParamIndexByUnivName( univParamName ), value );
}

InternalIndex VWRecordObj::GetParamClass(const TXString& univParamName) const
{
	return this->GetParamClass( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamClass(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamClass( this->GetParamIndexByUnivName( univParamName ), resource );
}

InternalIndex VWRecordObj::GetParamBuildingMaterial(const TXString& univParamName) const
{
	return this->GetParamBuildingMaterial( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamBuildingMaterial( this->GetParamIndexByUnivName( univParamName ), resource );
}

VWPattern VWRecordObj::GetParamFill(const TXString& univParamName) const
{
	return this->GetParamFill( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamFill(const TXString& univParamName, const VWPattern& attr)
{
	this->SetParamFill( this->GetParamIndexByUnivName( univParamName ), attr );
}

VWPattern VWRecordObj::GetParamPenStyle(const TXString& univParamName) const
{
	return this->GetParamPenStyle( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamPenStyle(const TXString& univParamName, const VWPattern& attr)
{
	this->SetParamPenStyle( this->GetParamIndexByUnivName( univParamName ), attr );
}

Uint8 VWRecordObj::GetParamPenWeight(const TXString& univParamName) const
{
	return this->GetParamPenWeight( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamPenWeight(const TXString& univParamName, Uint8 value)
{
	this->SetParamPenWeight( this->GetParamIndexByUnivName( univParamName ), value );
}

ColorRef VWRecordObj::GetParamColor(const TXString& univParamName) const
{
	return this->GetParamColor( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamColor(const TXString& univParamName, ColorRef value)
{
	this->SetParamColor( this->GetParamIndexByUnivName( univParamName ), value );
}

InternalIndex VWRecordObj::GetParamTexture(const TXString& univParamName) const
{
	return this->GetParamTexture( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamTexture(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamTexture( this->GetParamIndexByUnivName( univParamName ), resource );
}

InternalIndex VWRecordObj::GetParamSymDef(const TXString& univParamName) const
{
	return this->GetParamSymDef( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetParamSymDef(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamSymDef( this->GetParamIndexByUnivName( univParamName ), resource );
}

size_t VWRecordObj::PopupGetChoicesCount(const TXString& univParamName)
{
	size_t result = 0;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

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
	}

	return result;
}

void VWRecordObj::PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

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
}

void VWRecordObj::PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	outKeyValuePairs.clear();

	size_t	choicesCount	= this->PopupGetChoicesCount( univParamName );

	TXString	key;
	TXString	value;

	for ( size_t i = 0; i < choicesCount; i++ )
	{
		this->PopupGetChoice( univParamName, i, key, value );

		outKeyValuePairs.emplace_back( key, value );
	}
}

void VWRecordObj::PopupClearChoices(const TXString& univParamName)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

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
}

void VWRecordObj::PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

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
}

size_t VWRecordObj::PopupGetChoicesCount(size_t paramIndex)
{
	size_t result = 0;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

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
	}

	return result;
}

void VWRecordObj::PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

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
}

void VWRecordObj::PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs)
{
	outKeyValuePairs.clear();

	size_t	choicesCount	= this->PopupGetChoicesCount( paramIndex );

	TXString	key;
	TXString	value;

	for ( size_t i = 0; i < choicesCount; i++ )
	{
		this->PopupGetChoice( paramIndex, i, key, value );

		outKeyValuePairs.emplace_back( key, value );
	}
}

void VWRecordObj::PopupClearChoices(size_t paramIndex)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

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
}

void VWRecordObj::PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

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
}

bool VWRecordObj::GetIsEmpty(const TXString& univParamName) const
{
	return this->GetIsEmpty( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordObj::SetIsEmpty(const TXString& univParamName, bool value)
{
	this->SetIsEmpty( this->GetParamIndexByUnivName( univParamName ), value );
}

bool VWRecordObj::GetIsDataLinked(const TXString& univParamName) const
{
	return this->GetIsDataLinked(this->GetParamIndexByUnivName( univParamName ));
}

void VWRecordObj::SetIsDataLinked(const TXString& univParamName, bool value)
{
	this->SetIsDataLinked(this->GetParamIndexByUnivName( univParamName ), value);
}

bool VWRecordObj::GetIsEmpty(size_t paramIndex) const
{
	bool result = 0;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
			if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, valueItem ) ) )
			{
				result = valueItem.GetIsEmpty();
			}
		}
	}

	return result;
}

void VWRecordObj::SetIsEmpty(size_t paramIndex, bool value)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
		{
			recItem.SetIsEmpty( value );
			VWFC_VERIFY( rh.SetFieldObjectOptions( itemIndex, recItem ) );
		}
	}
}

bool VWRecordObj::GetIsDataLinked(size_t paramIndex) const
{
	bool result = 0;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( rh.GetFieldStyle( itemIndex ) );
			if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, valueItem ) ) )
			{
				result = valueItem.GetIsDataLinked();
			}
		}
	}

	return result;
}

void VWRecordObj::SetIsDataLinked(size_t paramIndex, bool value)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIFCRecord() ) )
	{
		TRecordHandler	rh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem		recItem( rh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( rh.GetFieldObject( itemIndex, recItem ) ) )
		{
			recItem.SetIsDataLinked( value );
			VWFC_VERIFY( rh.SetFieldObjectOptions( itemIndex, recItem ) );
		}
	}
}

bool VWRecordObj::IsIFCRecord() const
{
	return (fIFCMode == ERecordIFCWrapMode::IFC || fIFCMode == ERecordIFCWrapMode::PSet || fIFCMode == ERecordIFCWrapMode::IFCTag);
}

void VWRecordObj::GetIFCAttachedData(TMCObjectHandlesSTLArray& outArr) const
{
	VWFC_ASSERT( fhObject );
	VWRecordObj::GetIFCAttachedData( fhObject, outArr );
}

/*static*/ bool VWRecordObj::IsRecordObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kRecordNode;
}

/*static*/ bool VWRecordObj::IsRecordObject(MCObjectHandle hObj, const TXString& recordName)
{
	bool	result	= false;
	short	type	= gSDK->GetObjectTypeN( hObj );
	if ( type == kRecordNode ) {
		VWFC_ASSERT( hObj );
		TRecordHandler	rh( hObj );
		
		result	= (recordName.EqualNoCase( rh.GetNameOfFormat() ) );
	}

	return result;
}

/*static*/ MCObjectHandle VWRecordObj::GetRecordObject(MCObjectHandle hObj, const TXString& recordName)
{
	MCObjectHandle	hFoundRecord	= NULL;
	if ( hObj ) {
		VWObject			theObject( hObj );
		MCObjectHandle		hRecord		= theObject.FindAuxObject( kRecordNode );
		while ( hRecord && VWRecordObj::IsRecordObject( hRecord ) ) {
			TRecordHandler	rh( hRecord );
			
			if ( recordName.EqualNoCase( rh.GetNameOfFormat() )  ) {
				hFoundRecord	= hRecord;
				break;
			}

			hRecord		= theObject.FindAuxObject( kRecordNode, hRecord );
		}
	}

	return hFoundRecord;
}

/*static*/ bool VWRecordObj::IsIFCRecord(MCObjectHandle hObj)
{
	bool	result	= false;
	short	type	= gSDK->GetObjectTypeN( hObj );
	if ( type == kRecordNode )
	{
		VWFC_ASSERT( hObj );

		TXString nameOfFormat;
		gSDK->GetObjectName(gSDK->GetDefinition(hObj), nameOfFormat);

		result = VWRecordFormatObj::IsIFCFormat( nameOfFormat );
	}

	return result;
}

/*static*/ bool VWRecordObj::IsIFCRecord(MCObjectHandle hObj, const TXString& ifcName, ERecordIFCWrapMode mode)
{
	bool	result	= false;
	short	type	= gSDK->GetObjectTypeN( hObj );
	if ( type == kRecordNode )
	{
		VWFC_ASSERT( hObj );

		TXString nameOfFormat;
		MCObjectHandle	hFormat	= gSDK->GetDefinition( hObj );
		result = VWRecordFormatObj::IsIFCFormat( hFormat, ifcName, mode );
	}

	return result;
}

/*static*/ void VWRecordObj::GetIFCAttachedData(MCObjectHandle hIFCRecord, TMCObjectHandlesSTLArray& outArray)
{
	outArray.clear();

	short	type = gSDK->GetObjectTypeN( hIFCRecord );
	if ( type == kRecordNode )
	{
		TRecordHandler	rh( hIFCRecord );
		TXString		name	= rh.GetNameOfFormat();
		ERecordIFCType	ifcType;
		if ( VCOM_SUCCEEDED(gIFC->IFC_IsIFCRecord( name, ifcType)) && ifcType != ERecordIFCType::None )
		{
			VWObject	obj( hIFCRecord );

			for( MCObjectHandle	hLastRecord	= NULL, hCurrRecord = NULL;
				 (hCurrRecord = obj.FindAuxObject( kRecordNode, hLastRecord ));
				 hLastRecord = hCurrRecord)
			{
				TRecordHandler	crh( hCurrRecord );
				name	= crh.GetNameOfFormat();
				if ( VCOM_SUCCEEDED( gIFC->IFC_IsIFCRecord( name, ifcType )) && ifcType != ERecordIFCType::None ) 
				{
					outArray.push_back( hCurrRecord );
				}
			}
		}
	}
}


