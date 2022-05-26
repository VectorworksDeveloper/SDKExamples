//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VWFC::VWObjects;
using namespace VectorWorks::Extension;
using namespace VectorWorks::IFCLib;

//--------------------------------------------------------------------
VWRecordFormatObj::VWRecordFormatObj(MCObjectHandle hFormatHandle, ERecordIFCWrapMode wrapMode)
{
	fhObject		= hFormatHandle;

	VWFC_ASSERT( VWRecordFormatObj::IsRecordFormatObject( fhObject ) );
	if ( ! VWRecordFormatObj::IsRecordFormatObject( fhObject ) )
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

VWRecordFormatObj::VWRecordFormatObj(const TXString& formatName, ERecordIFCWrapMode wrapMode)
{
	TFormatHandler	fh( formatName );

	fhObject		= ::GS_GetNamedObject( gCBP, formatName );
	VWFC_ASSERT( VWRecordFormatObj::IsRecordFormatObject( fhObject ) );
	if ( ! VWRecordFormatObj::IsRecordFormatObject( fhObject ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	
	if ( wrapMode == ERecordIFCWrapMode::Auto )
	{
		this->SpecifyIFCRecordType();
	}
	else
	{
		fIFCMode	= wrapMode;
	}
}

VWRecordFormatObj::VWRecordFormatObj(const VWRecordFormatObj& src)
{
	fhObject	= src.fhObject;
	fIFCMode	= src.fIFCMode;
}

VWRecordFormatObj::~VWRecordFormatObj()
{
}

VWRecordFormatObj& VWRecordFormatObj::operator=(const VWRecordFormatObj& src)
{
	fhObject	= src.fhObject;
	fIFCMode	= src.fIFCMode;
	return *this;
}

TXString VWRecordFormatObj::GetFormatName() const
{
	VWFC_ASSERT( fhObject );
	TFormatHandler	fh( fhObject );
	
	return fh.GetNameOfFormat();
}

TXString VWRecordFormatObj::GetFormatLocalizedName() const
{
	TXString	localizedName;

	VWFC_ASSERT( fhObject );
	TFormatHandler	fh( fhObject );
	if ( ! this->IsIfc() )
	{
		if ( fh.IsParametric() )
		{
			TVariableBlock	varName;
			gSDK->GetObjectVariable(fhObject, ovParametricLocalizedName, varName);
			if ( ! varName.GetTXString(localizedName) )
			{
				localizedName = fh.GetLocalizedName();
			}
		}
		else
		{
			localizedName = fh.GetLocalizedName();
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

bool VWRecordFormatObj::SetFormatLocalizedName(const TXString& name)
{
	bool	result = false;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );
		if ( ! fh.IsParametric() )
		{
			result = fh.SetLocalizedName( name );
		}
	}

	return result;
}

bool VWRecordFormatObj::IsParametric() const
{
	bool	result	= false;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );
		result	= fh.IsParametric() ? true : false;
	}

	return result;
}

void VWRecordFormatObj::SetParametric(bool bIsParametric)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );
		fh.SetIsParametric( bIsParametric );
	}
}

bool VWRecordFormatObj::GetFormatVisibility() const
{
	bool	result = false;

	if ( ! this->IsIfc() )	// IFC records and formats must be created and managed using the IFC Library
	{
		TVariableBlock		varBlock;
		::GS_GetObjectVariable( gCBP, fhObject, ovFormatVisibility, varBlock );

		Boolean				bVis	= false;
		VERIFYN( kVStanev, varBlock.GetBoolean( bVis ) );
		result	= bVis ? true : false;
	}
	
	return result;
}

void VWRecordFormatObj::SetFormatVisibility(bool bVisibility)
{
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TVariableBlock		varBlock	= TVariableBlock( (Boolean) bVisibility );
		::GS_SetObjectVariable( gCBP, fhObject, ovFormatVisibility, varBlock );
	}
}

size_t VWRecordFormatObj::AddParamLong(const TXString& name, Sint32 value, bool bUpdateExistingRecords)
{
	size_t	result	= size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldLongInt );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( value ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1;
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamBool(const TXString& name, bool value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldBoolean );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( (Boolean) value ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1;
	}

	return result;
}

size_t VWRecordFormatObj::AddParamReal(const TXString& name, double value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldReal );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( (double_param) value ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamCoord(const TXString& name, double value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldCoordDisp );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( (double_param) value ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}

	return result;
}

size_t VWRecordFormatObj::AddParamAngle(const TXString& name, double value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldAngle );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( (double_param) value ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1;
	}

	return result;
}

size_t VWRecordFormatObj::AddParamArea(const TXString& name, double value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldArea );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( (double_param) value ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1;
	}

	return result;
}

size_t VWRecordFormatObj::AddParamVolume(const TXString& name, double value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldVolume );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( (double_param) value ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamString(const TXString& name, const TXString& value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldText );
		VERIFYN( kVStanev, defaultValue.SetFieldValue(  value, value.GetLength() ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1;
	}

	return result;
}

size_t VWRecordFormatObj::AddParamPopup(const TXString& name, const TXString& value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldPopUp );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( value, value.GetLength() ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1;
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamClassesPopUp(const TXString& name, const TXString& value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldClassesPopup );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( value, value.GetLength() ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1;
	}

	return result;
}

size_t VWRecordFormatObj::AddParamClass(const TXString& name, InternalIndex resource, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldClass );
		VERIFYN( kVStanev, defaultValue.SetFieldClass( resource ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamBuildingMaterial(const TXString& name, InternalIndex resource, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldBuildingMaterial );
		VERIFYN( kVStanev, defaultValue.SetFieldBuildingMaterial( resource ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamFill(const TXString& name, const VWPattern& attr, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldFill );
		VERIFYN( kVStanev, defaultValue.SetFieldFill( attr ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamPenStyle(const TXString& name, const VWPattern& attr, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldPenStyle );
		VERIFYN( kVStanev, defaultValue.SetFieldPenStyle( attr ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamPenWeight(const TXString& name, Uint8 value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldPenWeight );
		VERIFYN( kVStanev, defaultValue.SetFieldPenWeight( value ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamColor(const TXString& name, ColorRef value, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldColor );
		VERIFYN( kVStanev, defaultValue.SetFieldColor( value ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamTexture(const TXString& name, InternalIndex resource, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldTexture );
		VERIFYN( kVStanev, defaultValue.SetFieldTexture( resource ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamSymDef(const TXString& name, InternalIndex resource, bool bUpdateExistingRecords)
{
	size_t	result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc()) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );
		
		TRecordItem		defaultValue( kFieldSymDef );
		VERIFYN( kVStanev, defaultValue.SetFieldSymDef( resource ) );

		short index	= fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result	= index - 1; 
	}
	
	return result;
}

size_t VWRecordFormatObj::AddParamStaticString(const TXString& name, const TXString& value, bool bUpdateExistingRecords)
{
	size_t	result = size_t( -1 );

	VWFC_ASSERT( fhObject );
	if( VWFC_VERIFY( !this->IsIfc() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		ASSERTN( kVStanev, name.GetLength() < 63 );

		TRecordItem		defaultValue( kFieldStaticText );
		VERIFYN( kVStanev, defaultValue.SetFieldValue( value, value.GetLength() ) );

		short index = fh.AddField( name, defaultValue, bUpdateExistingRecords );
		result = index - 1;
	}

	return result;
}

size_t VWRecordFormatObj::GetParamsCount() const
{
	size_t	result	= size_t(-1);
	
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);
		result = (size_t)fh.GetNumOfFields();
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamsCount( fhObject, result, VWRecordFormatObj::GetIfcRecordType(fIFCMode) );
		}
	}

	return result;
}

TXString VWRecordFormatObj::GetParamName(size_t paramIndex) const
{
	TXString	result;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! 'GetNameOfField' return 1 based value
		fh.GetNameOfField(DemoteTo<short>(kVStanev, paramIndex + 1), result);
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamName( fhObject, paramIndex, result, VWRecordFormatObj::GetIfcRecordType(fIFCMode) );
		}
	}

	return result;
}

TXString VWRecordFormatObj::GetParamLocalizedName(size_t paramIndex) const
{
	TXString	paramName;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );
		if ( fh.IsParametric() )
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
			fh.GetNameOfFieldLocalized( DemoteTo<short>( kVStanev, paramIndex+1 ), paramName );
		}
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamName( fhObject, paramIndex, paramName, VWRecordFormatObj::GetIfcRecordType(fIFCMode) );
		}
	}

	return paramName;
}

bool VWRecordFormatObj::SetParamLocalizedName(size_t paramIndex, const TXString& name)
{
	bool result = false;
	if ( ! this->IsIfc() )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );
		if ( ! fh.IsParametric() )
		{
			result	= fh.SetNameOfFieldLocalized( DemoteTo<short>( kVStanev, paramIndex+1 ), name );
		}
	}

	return result;
}

bool VWRecordFormatObj::DeleteParam(const TXString& univParamName) const
{
	bool result = false;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );

		size_t	paramIndex = this->GetParamIndexByUnivName( univParamName );
		if ( paramIndex != size_t(-1) )
		{
			fh.DeleteField( DemoteTo<short>( kVStanev, paramIndex+1 ) );
			result = true;
		}
	}

	return result;
}

void  VWRecordFormatObj::DeleteParam(size_t paramIndex)
{
	if ( VWFC_VERIFY( ! this->IsIfc() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		VWFC_ASSERT( fhObject );
		TFormatHandler	fh( fhObject );

		fh.DeleteField( DemoteTo<short>( kVStanev, paramIndex+1 ) );
	}
}

// returns ((size_t) -1) if not found
size_t VWRecordFormatObj::GetParamIndex(const TXString& paramName) const
{
	size_t	result	= -1;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		// NOTE! 'GetFieldIndex' return 1 based value
		Sint32		index	= fh.GetFieldIndex( paramName );
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
			ifcSupport->IFC_GetParamIndex( fhObject, paramName, result, VWRecordFormatObj::GetIfcRecordType(fIFCMode) );
		}
	}

	return result;
}

EFieldStyle VWRecordFormatObj::GetParamStyle(size_t paramIndex) const
{
	EFieldStyle	result	= (EFieldStyle)0;

	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		// NOTE! 'GetFieldStyle' return 1 based value
		return (EFieldStyle) fh.GetFieldStyle( DemoteTo<short>( kVStanev, paramIndex+1 ) );
	}
	else
	{
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport )
		{
			ifcSupport->IFC_GetParamStyle( fhObject, paramIndex, result, VWRecordFormatObj::GetIfcRecordType(fIFCMode) );
		}
	}

	return result;
}

TNumStyleClass	VWRecordFormatObj::GetParamNumStyle(size_t paramIndex) const
{
	TNumStyleClass	numStyle = nsGeneral;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );
		Byte			accuracy;

		// NOTE! 'GetFieldNumStyle' return 1 based value
		fh.GetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, accuracy );
	}

	return numStyle;
}

void VWRecordFormatObj::SetParamNumStyle(size_t paramIndex, TNumStyleClass value)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );
		TNumStyleClass  numStyle;
		Byte			accuracy;

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! 'GetFieldNumStyle' return 1 based value
			fh.GetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, accuracy );
			fh.SetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), value, accuracy );
		}
	}
}

Byte VWRecordFormatObj::GetParamAccuracy(size_t paramIndex) const
{
	Byte	accuracy = 0;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );
		TNumStyleClass  numStyle;

		// NOTE! 'GetFieldNumStyle' return 1 based value
		fh.GetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, accuracy );
	}
	
	return accuracy;
}

void VWRecordFormatObj::SetParamAccuracy(size_t paramIndex, Byte value)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )	// IFC records and formats must be created and managed using the IFC Library
	{
		TFormatHandler	fh( fhObject );
		TNumStyleClass  numStyle;
		Byte			accuracy;

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! 'GetFieldNumStyle' return 1 based value
			fh.GetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, accuracy );
			fh.SetFieldNumStyle( DemoteTo<short>( kVStanev, paramIndex+1 ), numStyle, value );
		}
	}
}

TXString VWRecordFormatObj::GetParamValue(size_t paramIndex) const
{
	TXString	value;
	
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );
		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			EFieldStyle		style		= (EFieldStyle) fh.GetFieldStyle( itemIndex );
			TRecordItem valueItem( style );
			Boolean			ok			= fh.GetFieldDefault( itemIndex, valueItem );
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
				TXString		theString;
				if ( valueItem.GetFieldValueAsString( theString ) )
				{
					value	= theString;
				}
			}
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

void VWRecordFormatObj::SetParamValue(size_t paramIndex, const TXString& value)
{
	VWFC_ASSERT( fhObject );

	if ( this->IsIfc() )
	{
		// get the correct paramInde for IFC records
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ! ifcSupport || VCOM_FAILED(ifcSupport->IFC_GetParamIndex(fhObject, paramIndex, paramIndex, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			paramIndex	= -1;
		}
	}

	if ( paramIndex	!= -1 )
	{
		TFormatHandler	fh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		EFieldStyle		style		= (EFieldStyle) fh.GetFieldStyle( itemIndex );
		TRecordItem		recItem( style );
		if ( VWFC_VERIFY( fh.GetFieldDefault( itemIndex, recItem ) ) )
		{
			TXString currFieldValue;
			// Check if the current value is the same as the new value. If it is, we can skip SetFieldObject below.
			if ( !recItem.GetFieldValueAsString( currFieldValue ) || !currFieldValue.Equal( value ) )
			{
				if ( style == kFieldText )
				{
					const UCChar* szText = value;
					size_t		textLen = value.GetLength();

					if ( VWFC_VERIFY( recItem.SetFieldValue( szText, textLen ) ) )
					{
						VWFC_VERIFY( fh.SetFieldDefault( itemIndex, recItem ) );
					}
				}
				else
				{
					if ( VWFC_VERIFY( recItem.SetFieldValueAsString( value ) ) )
					{
						VWFC_VERIFY( fh.SetFieldDefault( itemIndex, recItem ) );
					}
				}
			}
		}
	}
}

Sint32 VWRecordFormatObj::GetParamLong(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	Sint32		value	= 0;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok )
			{
				valueItem.GetFieldValue( value );
			}
		}
	}
	else
	{
		TXString	paramValue;
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport && VCOM_SUCCEEDED(ifcSupport->IFC_GetParamValue(fhObject, paramIndex, paramValue, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			value	= paramValue.atoi();
		}
	}

	return value;
}

void VWRecordFormatObj::SetParamLong(size_t paramIndex, Sint32 value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldValue(value)) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
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

bool VWRecordFormatObj::GetParamBool(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	Boolean		value	= 0;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok )
			{
				valueItem.GetFieldValue( value );
			}
		}
	}
	else
	{
		TXString	str;
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport && VCOM_SUCCEEDED(ifcSupport->IFC_GetParamValue(fhObject, paramIndex, str, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			value = str.EqualNoCase( "true" )  || str.EqualNoCase( "yes" )  || str.atoi() != 0;
		}
	}

	return value ? true : false;
}

void VWRecordFormatObj::SetParamBool(size_t paramIndex, bool value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			Boolean		boolValue = value;
			if ( VWFC_VERIFY(recItem.SetFieldValue(boolValue)) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
			}
		}
	}
	else
	{
		// get the correct paramInde for IFC records
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport || VCOM_SUCCEEDED(ifcSupport->IFC_GetParamIndex(fhObject, paramIndex, paramIndex, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			this->SetParamStringI( paramIndex, value ? "true" : "false" );
		}
	}
}

double VWRecordFormatObj::GetParamReal(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	double		value	= 0;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok ) {
				valueItem.GetFieldValue( value );
			}
		}
	}
	else
	{
		TXString	paramValue;
		VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
		if ( ifcSupport && VCOM_SUCCEEDED(ifcSupport->IFC_GetParamValue(fhObject, paramIndex, paramValue, VWRecordFormatObj::GetIfcRecordType(fIFCMode))) )
		{
			value =	paramValue.atof();
		}
	}

	return value;
}

void VWRecordFormatObj::SetParamReal(size_t paramIndex, double value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldValue(value)) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
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

TXString VWRecordFormatObj::GetParamString(size_t paramIndex) const
{
	TXString	value;
	
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok		= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok )
			{
				valueItem.GetFieldValue( value );
			}
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

void VWRecordFormatObj::SetParamString(size_t paramIndex, const TXString& value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
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

InternalIndex VWRecordFormatObj::GetParamClass(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	InternalIndex		value	= 0;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok ) {
				valueItem.GetFieldClass( value );
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordFormatObj::SetParamClass(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldClass(resource)) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

InternalIndex VWRecordFormatObj::GetParamBuildingMaterial(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	InternalIndex		value	= 0;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok ) {
				valueItem.GetFieldBuildingMaterial( value );
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordFormatObj::SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldBuildingMaterial(resource)) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

VWPattern VWRecordFormatObj::GetParamFill(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	VWPattern		value( true );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			InternalIndex resource;
			ok = ok && valueItem.GetFieldFill( resource );
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

void VWRecordFormatObj::SetParamFill(size_t paramIndex, const VWPattern& attr)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldFill( attr )) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

VWPattern VWRecordFormatObj::GetParamPenStyle(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	VWPattern		value( false );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			InternalIndex resource;
			ok = valueItem.GetFieldPenStyle( resource );
			if ( ok )
			{
				value = VWPattern( resource, false );
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordFormatObj::SetParamPenStyle(size_t paramIndex, const VWPattern& attr)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldPenStyle( attr )) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

Uint8 VWRecordFormatObj::GetParamPenWeight(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	Uint8		value	= 0;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok ) {
				valueItem.GetFieldPenWeight( value );
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordFormatObj::SetParamPenWeight(size_t paramIndex, Uint8 value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldPenWeight(value)) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

ColorRef VWRecordFormatObj::GetParamColor(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	ColorRef		value	= 0;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok ) {
				valueItem.GetFieldColor( value );
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordFormatObj::SetParamColor(size_t paramIndex, ColorRef value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldColor(value)) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

InternalIndex VWRecordFormatObj::GetParamTexture(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	InternalIndex		value	= 0;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok ) {
				valueItem.GetFieldTexture( value );
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordFormatObj::SetParamTexture(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldTexture(resource)) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

InternalIndex VWRecordFormatObj::GetParamSymDef(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	InternalIndex		value	= 0;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok ) {
				valueItem.GetFieldSymDef( value );
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordFormatObj::SetParamSymDef(size_t paramIndex, InternalIndex resource)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			if ( VWFC_VERIFY(recItem.SetFieldSymDef(resource)) )
			{
				VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

bool VWRecordFormatObj::GetIsEmpty(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	bool		value	= false;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok ) {
				value = valueItem.GetIsEmpty();
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordFormatObj::SetIsEmpty(size_t paramIndex, bool value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			recItem.SetIsEmpty(value);
			VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

bool VWRecordFormatObj::GetIsDataLinked(size_t paramIndex) const
{
	VWFC_ASSERT( fhObject );

	bool		value	= false;
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			// NOTE! itemIndex is expected from the SDK as 1 based value
			short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
			TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
			Boolean		ok			= fh.GetFieldDefault( itemIndex, valueItem );
			VWFC_ASSERT( ok );

			if ( ok ) {
				value = valueItem.GetIsDataLinked();
			}
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}

	return value;
}

void VWRecordFormatObj::SetIsDataLinked(size_t paramIndex, bool value)
{
	VWFC_ASSERT( fhObject );
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh(fhObject);

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
		TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
		if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
		{
			recItem.SetIsDataLinked(value);
			VWFC_VERIFY(fh.SetFieldDefault(itemIndex, recItem));
		}
	}
	else
	{
		DSTOP((kVStanev, "not implemented"));
	}
}

size_t VWRecordFormatObj::GetParamIndexByUnivName(const TXString& univParamName) const
{
	size_t	paramIndex	= size_t(-1);

	// this little hack but we want to be able to change the this
	// this is needed for performance optimization
	// so we would add the parameters only when they are needed
	// not for every parameter in the constructor
	VWRecordFormatObj*	pThis = (VWRecordFormatObj*)( this );

	TXString	macUnivParamName	= univParamName;
	TUnviNameKeyMap::iterator	it = pThis->fmapUnivNameKey.find( macUnivParamName );
	if ( it == pThis->fmapUnivNameKey.end() )
	{
		TFormatHandler	fh( fhObject );
		// NOTE! 'GetFieldIndex' return 1 based value
		Sint32		index	= fh.GetFieldIndex( macUnivParamName );
		if ( ! this->IsIfc() )
		{
			if ( index != 0 )
			{
				paramIndex = (size_t)(index - 1);
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

		pThis->fmapUnivNameKey.insert( TUnviNameKeyMap::value_type( macUnivParamName, paramIndex ) );
	}
	else
	{
		paramIndex	= it->second;
	}

	return paramIndex;
}

void VWRecordFormatObj::SpecifyIFCRecordType()
{
	// set IFC to false for default
	fIFCMode = ERecordIFCWrapMode::None;

	VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
	if ( ifcSupport )
	{
		TFormatHandler	fh(fhObject);
		TXString		name	= fh.GetNameOfFormat();
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

void VWRecordFormatObj::SetParamStringI(size_t paramIndex, const TXString& value)
{
	TFormatHandler	fh(fhObject);

	// NOTE! itemIndex is expected from the SDK as 1 based value
	short			itemIndex = DemoteTo<short>(kVStanev, paramIndex + 1);
	TRecordItem		recItem(fh.GetFieldStyle(itemIndex));
	if ( VWFC_VERIFY(fh.GetFieldDefault(itemIndex, recItem)) )
	{
		TXString currFieldValue;
		// Check if the current value is the same as the new value. If it is, we can skip SetFieldObject below.
		if ( !recItem.GetFieldValueAsString( currFieldValue ) || !currFieldValue.Equal( value ) )
		{
			if ( VWFC_VERIFY( recItem.SetFieldValue( value ) ) )
			{
				VWFC_VERIFY( fh.SetFieldDefault( itemIndex, recItem ) );
			}
		}
	}
}

EFieldStyle VWRecordFormatObj::GetParamStyle(const TXString& univParamName) const
{
	return this->GetParamStyle( this->GetParamIndexByUnivName( univParamName ) );
}

TNumStyleClass	VWRecordFormatObj::GetParamNumStyle(const TXString& univParamName) const
{
	return this->GetParamNumStyle( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamNumStyle(const TXString& univParamName, TNumStyleClass value)
{
	this->SetParamNumStyle( this->GetParamIndexByUnivName( univParamName ), value );
}

Byte VWRecordFormatObj::GetParamAccuracy(const TXString& univParamName) const
{
	return this->GetParamAccuracy( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamAccuracy(const TXString& univParamName, Byte value)
{
	this->SetParamAccuracy( this->GetParamIndexByUnivName( univParamName ), value);
}

TXString VWRecordFormatObj::GetParamValue(const TXString& univParamName) const
{
	return this->GetParamValue( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamValue(const TXString& univParamName, const TXString& value)
{
	this->SetParamValue( this->GetParamIndexByUnivName( univParamName ), value );
}

Sint32 VWRecordFormatObj::GetParamLong(const TXString& univParamName) const
{
	return this->GetParamLong( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamLong(const TXString& univParamName, Sint32 value)
{
	this->SetParamLong( this->GetParamIndexByUnivName( univParamName ), value );
}

bool VWRecordFormatObj::GetParamBool(const TXString& univParamName) const
{
	return this->GetParamBool( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamBool(const TXString& univParamName, bool value)
{
	this->SetParamBool( this->GetParamIndexByUnivName( univParamName ), value );
}

double VWRecordFormatObj::GetParamReal(const TXString& univParamName) const
{
	return this->GetParamReal( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamReal(const TXString& univParamName, double value)
{
	this->SetParamReal( this->GetParamIndexByUnivName( univParamName ), value );
}

TXString VWRecordFormatObj::GetParamString(const TXString& univParamName) const
{
	return this->GetParamString( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamString(const TXString& univParamName, const TXString& value)
{
	this->SetParamString( this->GetParamIndexByUnivName( univParamName ), value );
}

InternalIndex VWRecordFormatObj::GetParamClass(const TXString& univParamName) const
{
	return this->GetParamClass( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamClass(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamClass( this->GetParamIndexByUnivName( univParamName ), resource );
}

InternalIndex VWRecordFormatObj::GetParamBuildingMaterial(const TXString& univParamName) const
{
	return this->GetParamBuildingMaterial( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamBuildingMaterial( this->GetParamIndexByUnivName( univParamName ), resource );
}

VWPattern VWRecordFormatObj::GetParamFill(const TXString& univParamName) const
{
	return this->GetParamFill( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamFill(const TXString& univParamName, const VWPattern& attr)
{
	this->SetParamFill( this->GetParamIndexByUnivName( univParamName ), attr );
}

VWPattern VWRecordFormatObj::GetParamPenStyle(const TXString& univParamName) const
{
	return this->GetParamPenStyle( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamPenStyle(const TXString& univParamName, const VWPattern& attr)
{
	this->SetParamPenStyle( this->GetParamIndexByUnivName( univParamName ), attr );
}

Uint8 VWRecordFormatObj::GetParamPenWeight(const TXString& univParamName) const
{
	return this->GetParamPenWeight( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamPenWeight(const TXString& univParamName, Uint8 value)
{
	this->SetParamPenWeight( this->GetParamIndexByUnivName( univParamName ), value );
}

ColorRef VWRecordFormatObj::GetParamColor(const TXString& univParamName) const
{
	return this->GetParamColor( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamColor(const TXString& univParamName, ColorRef value)
{
	this->SetParamColor( this->GetParamIndexByUnivName( univParamName ), value );
}

InternalIndex VWRecordFormatObj::GetParamTexture(const TXString& univParamName) const
{
	return this->GetParamTexture( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamTexture(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamTexture( this->GetParamIndexByUnivName( univParamName ), resource );
}

InternalIndex VWRecordFormatObj::GetParamSymDef(const TXString& univParamName) const
{
	return this->GetParamSymDef( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetParamSymDef(const TXString& univParamName, InternalIndex resource)
{
	this->SetParamSymDef( this->GetParamIndexByUnivName( univParamName ), resource );
}

VCOMPtr<IEventSink> VWRecordFormatObj::GetParametricEventSink(const TSinkIID& sindIID)
{
	VCOMPtr<IEventSink>	result;
 
	if ( ! this->IsIfc() )
	{
		TFormatHandler	fh( fhObject );
		if ( fh.IsParametric() )
		{
			VCOMPtr<IExtendedProps>	extProps( IID_ExtendedProps );
			result = extProps->QueryExtensionEventSink( fhObject, sindIID );
		}
	}
  
	return result;
}

size_t VWRecordFormatObj::PopupGetChoicesCount(const TXString& univParamName, bool useParametric)
{
	size_t result = 0;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );

		size_t paramIndex = this->GetParamIndexByUnivName( univParamName );
		if ( paramIndex != size_t(-1) )
		{
			bool	handled = false;
			if ( useParametric && fh.IsParametric() )
			{
				VCOMPtr<IEventSink> eventSink = this->GetParametricEventSink( IID_ParametricParamsProvider );
				if ( eventSink )
				{
					// Vlado: Temporally removed 'dynamic_cast'
					// because on new Mac OS it is failing to cast properly
					VCOMPtr<IParametricParamsProvider> provider = (IParametricParamsProvider*) (IVWUnknown*) eventSink;
					if ( provider )
					{
						TXStringArray arrUnivChoices, arrLocalizedChoices;
						provider->GetParamChoices( paramIndex,arrUnivChoices, arrLocalizedChoices );
                            
						result = arrUnivChoices.GetSize();
						handled = true;
					}
				}
			}

			if ( ! handled )
			{
				// NOTE! itemIndex is expected from the SDK as 1 based value
				short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
				TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
				if ( VWFC_VERIFY( fh.GetFieldDefault( itemIndex, valueItem ) ) )
				{
					result = valueItem.PopupGetChoicesCount();
				}
			}
		}
	}

	return result;
}

void VWRecordFormatObj::PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue, bool useParametric)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );

		size_t paramIndex = this->GetParamIndexByUnivName( univParamName );
		if ( paramIndex != size_t(-1) )
		{
			bool	handled = false;
			if ( useParametric && fh.IsParametric() )
			{
				VCOMPtr<IEventSink> eventSink = this->GetParametricEventSink( IID_ParametricParamsProvider );
				if ( eventSink )
				{
					// Vlado: Temporally removed 'dynamic_cast'
					// because on new Mac OS it is failing to cast properly
					VCOMPtr<IParametricParamsProvider> provider = (IParametricParamsProvider*) (IVWUnknown*) eventSink;
					if ( provider )
					{
						TXStringArray arrUnivChoices, arrLocalizedChoices;
						provider->GetParamChoices( paramIndex,arrUnivChoices, arrLocalizedChoices );
	                            
						size_t cntChoices = arrUnivChoices.GetSize();                        
						if ( index < cntChoices )
						{
							outKey = arrUnivChoices[index];
							outValue = arrLocalizedChoices[index];
	                           
						}
	
						handled = true;
					}
				}
			}
	
			if ( ! handled )
			{
				// NOTE! itemIndex is expected from the SDK as 1 based value
				short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
				TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
				if ( VWFC_VERIFY( fh.GetFieldDefault( itemIndex, valueItem ) ) )
				{
					VWFC_VERIFY( valueItem.PopupGetChoice( index, outKey, outValue ) );
				}
			}
		}
	}
}

void VWRecordFormatObj::PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs, bool useParametric)
{
	outKeyValuePairs.clear();

	size_t	choicesCount	= this->PopupGetChoicesCount( univParamName, useParametric );

	TXString	key;
	TXString	value;

	for ( size_t i = 0; i < choicesCount; i++ )
	{
		this->PopupGetChoice( univParamName, i, key, value, useParametric );

		outKeyValuePairs.emplace_back( key, value );
	}
}

void VWRecordFormatObj::PopupClearChoices(const TXString& univParamName)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );

		size_t paramIndex = this->GetParamIndexByUnivName( univParamName );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem		recItem( fh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( fh.GetFieldDefault( itemIndex, recItem ) ) )
		{
			if ( VWFC_VERIFY( recItem.PopupClearChoices() ) )
			{
				VWFC_VERIFY( fh.SetFieldDefault( itemIndex, recItem ) );
			}
		}
	}
}

void VWRecordFormatObj::PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );

		size_t paramIndex = this->GetParamIndexByUnivName( univParamName );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem		recItem( fh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( fh.GetFieldDefault( itemIndex, recItem ) ) )
		{
			if ( VWFC_VERIFY( recItem.PopupSetChoices( keyValuePairs, append ) ) )
			{
				VWFC_VERIFY( fh.SetFieldDefault( itemIndex, recItem ) );
			}
		}
	}
}

TXString VWRecordFormatObj::PopupGetLocalizedChoice(const TXString& univParamName, const TXString& key)
{
	TXString	result;

	std::vector<std::pair<TXString, TXString>>	keyValuePairs;

	this->PopupGetChoices( univParamName, keyValuePairs );

	if ( keyValuePairs.size() > 0 )
	{
		auto iter = std::find_if( keyValuePairs.begin(), keyValuePairs.end(), [&key]( const std::pair<TXString, TXString>& pair ) {return pair.first == key; } );

		if ( VWFC_VERIFY( iter != keyValuePairs.end() ) )
		{
			result = iter->second;
		}
	}

	return result;
}

bool VWRecordFormatObj::GetIsEmpty(const TXString& univParamName) const
{
	return this->GetIsEmpty( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetIsEmpty(const TXString& univParamName, bool value)
{
	this->SetIsEmpty( this->GetParamIndexByUnivName( univParamName ), value );
}

bool VWRecordFormatObj::GetIsDataLinked(const TXString& univParamName) const
{
	return this->GetIsDataLinked( this->GetParamIndexByUnivName( univParamName ) );
}

void VWRecordFormatObj::SetIsDataLinked(const TXString& univParamName, bool value)
{
	this->SetIsDataLinked( this->GetParamIndexByUnivName( univParamName ), value );
}

bool VWRecordFormatObj::EditWithUI()
{
	bool	result = false;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );
		result = fh.EditWithUI();
	}

	return result;
}

size_t VWRecordFormatObj::AddParameWithUI(const TXString& name, EFieldStyle style, const TXString& value)
{
	size_t result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );
		short paramIndex = fh.AddFieldWithUI( name, style, value );
		if ( paramIndex > 0 )
			result = paramIndex - 1;
	}

	return result;
}

size_t VWRecordFormatObj::EditParamWithUI(const TXString& univParamName)
{
	size_t result = size_t(-1);

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		size_t paramIndex = this->GetParamIndexByUnivName( univParamName );
		if ( paramIndex != size_t(-1) )
		{
			TFormatHandler	fh( fhObject );
			short itemIndex		= DemoteTo<short>( kVStanev, paramIndex+1 );
			short paramIndex	= fh.EditFieldWithUI( itemIndex );
			if ( paramIndex > 0 )
				result = paramIndex - 1;
		}
	}

	return result;
}

size_t VWRecordFormatObj::EditParamWithUI(size_t paramIndex)
{
	size_t result = size_t(-1);
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );
		short itemIndex		= DemoteTo<short>( kVStanev, paramIndex+1 );
		short paramIndex	= fh.EditFieldWithUI( itemIndex );
		if ( paramIndex > 0 )
			result = paramIndex - 1;
	}

	return result;
}

bool VWRecordFormatObj::EditFieldDefineWithUI(size_t paramIndex)
{
	bool result = false;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( !this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );
		short			itemIndex	= DemoteTo<short>( kKIvanov, paramIndex + 1 );
		result						= fh.EditFieldDefineWithUI( itemIndex );
	}

	return result;
}

size_t VWRecordFormatObj::PopupGetChoicesCount(size_t paramIndex, bool useParametric)
{
	size_t result = 0;

	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			bool	handled = false;
			if ( useParametric && fh.IsParametric() )
			{
				VCOMPtr<IEventSink> eventSink = this->GetParametricEventSink( IID_ParametricParamsProvider );
				if ( eventSink )
				{
					// Vlado: Temporally removed 'dynamic_cast'
					// because on new Mac OS it is failing to cast properly
					VCOMPtr<IParametricParamsProvider> provider = (IParametricParamsProvider*) (IVWUnknown*) eventSink;
					if ( provider )
					{
						TXStringArray arrUnivChoices, arrLocalizedChoices;
						provider->GetParamChoices( paramIndex,arrUnivChoices, arrLocalizedChoices );
	                            
						result = arrUnivChoices.GetSize();
						handled = true;
					}
				}
			}
	
			if ( ! handled )
			{
				// NOTE! itemIndex is expected from the SDK as 1 based value
				short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
				TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
				if ( VWFC_VERIFY( fh.GetFieldDefault( itemIndex, valueItem ) ) )
				{
					result = valueItem.PopupGetChoicesCount();
				}
			}
		}
	}

	return result;
}

void VWRecordFormatObj::PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue, bool useParametric)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );

		if ( paramIndex != size_t(-1) )
		{
			bool	handled = false;
			if ( useParametric && fh.IsParametric() )
			{
				VCOMPtr<IEventSink> eventSink = this->GetParametricEventSink( IID_ParametricParamsProvider );
				if ( eventSink )
				{
					// Vlado: Temporally removed 'dynamic_cast'
					// because on new Mac OS it is failing to cast properly
					VCOMPtr<IParametricParamsProvider> provider = (IParametricParamsProvider*) (IVWUnknown*) eventSink;
					if ( provider )
					{
						TXStringArray arrUnivChoices, arrLocalizedChoices;
						provider->GetParamChoices( paramIndex,arrUnivChoices, arrLocalizedChoices );
	                            
						size_t cntChoices = arrUnivChoices.GetSize();                        
						if ( index < cntChoices )
						{
							outKey = arrUnivChoices[index];
							outValue = arrLocalizedChoices[index];
	                           
						}
	
						handled = true;
					}
				}
			}
	
			if ( ! handled )
			{
				// NOTE! itemIndex is expected from the SDK as 1 based value
				short		itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
				TRecordItem valueItem( fh.GetFieldStyle( itemIndex ) );
				if ( VWFC_VERIFY( fh.GetFieldDefault( itemIndex, valueItem ) ) )
				{
					VWFC_VERIFY( valueItem.PopupGetChoice( index, outKey, outValue ) );
				}
            }
		}
	}
}

void VWRecordFormatObj::PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs, bool useParametric)
{
	outKeyValuePairs.clear();

	size_t	choicesCount	= this->PopupGetChoicesCount( paramIndex, useParametric );

	TXString	key;
	TXString	value;

	for ( size_t i = 0; i < choicesCount; i++ )
	{
		this->PopupGetChoice( paramIndex, i, key, value, useParametric );

		outKeyValuePairs.emplace_back( key, value );
	}
}

void VWRecordFormatObj::PopupClearChoices(size_t paramIndex)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem		recItem( fh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( fh.GetFieldDefault( itemIndex, recItem ) ) )
		{
			if ( VWFC_VERIFY( recItem.PopupClearChoices() ) )
			{
				VWFC_VERIFY( fh.SetFieldDefault( itemIndex, recItem ) );
			}
		}
	}
}

void VWRecordFormatObj::PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append)
{
	VWFC_ASSERT( fhObject );
	if ( VWFC_VERIFY( ! this->IsIfc() ) )
	{
		TFormatHandler	fh( fhObject );

		// NOTE! itemIndex is expected from the SDK as 1 based value
		short			itemIndex	= DemoteTo<short>( kVStanev, paramIndex+1 );
		TRecordItem		recItem( fh.GetFieldStyle( itemIndex ) );
		if ( VWFC_VERIFY( fh.GetFieldDefault( itemIndex, recItem ) ) )
		{
			if ( VWFC_VERIFY( recItem.PopupSetChoices( keyValuePairs, append ) ) )
			{
				VWFC_VERIFY( fh.SetFieldDefault( itemIndex, recItem ) );
			}
		}
	}
}

/*static*/ bool VWRecordFormatObj::IsRecordFormatObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kFormatNode;
}

/*static*/ bool VWRecordFormatObj::IsRecordFormatObject(MCObjectHandle hObj, const TXString& name)
{
	if ( ! VWRecordFormatObj::IsRecordFormatObject( hObj ) )
		return false;

	TFormatHandler	fh( hObj );
	
	return name == fh.GetNameOfFormat();
}

/*static*/ MCObjectHandle VWRecordFormatObj::GetRecordFormat(const TXString& name)
{
	MCObjectHandle	hFormat	=	::GS_GetNamedObject( gCBP, name );
	return ( VWRecordFormatObj::IsRecordFormatObject( hFormat ) ? hFormat : nullptr );
}

/*static*/ void VWRecordFormatObj::DeleteRecordFormat(MCObjectHandle hRecFormat)
{
	if ( VWRecordFormatObj::IsRecordFormatObject( hRecFormat ) ) {
		TFormatHandler	fh( hRecFormat );
		fh.DeleteFormat();
	}
}

/*static*/ bool VWRecordFormatObj::IsIFCFormat(const TXString& name)
{
	bool result = false;
	
	VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
	if ( ifcSupport )
	{
		ERecordIFCType	type;
		if ( VCOM_SUCCEEDED(ifcSupport->IFC_IsIFCRecord( name, type )) )
		{
			result	= type != ERecordIFCType::None;
		}
	}

	return result;
}

/*static*/ bool VWRecordFormatObj::IsIFCFormat(MCObjectHandle hObj)
{
	bool	result	= false;
	short	type	= gSDK->GetObjectTypeN( hObj );
	if ( type == kFormatNode )
	{
		VWFC_ASSERT( hObj );
		TFormatHandler	fh( hObj );

		TXString nameOfFormat = fh.GetNameOfFormat();

		result = VWRecordFormatObj::IsIFCFormat( nameOfFormat );
	}

	return result;
}

/*static*/ bool VWRecordFormatObj::IsIFCFormat(MCObjectHandle hObj, const TXString& ifcName, ERecordIFCWrapMode mode)
{
	bool	result	= false;
	short	type	= gSDK->GetObjectTypeN( hObj );
	if ( type == kFormatNode )
	{
		VWFC_ASSERT( hObj );
		TFormatHandler	fh( hObj );

		TXString nameOfFormat = fh.GetNameOfFormat();

		result = VWRecordFormatObj::IsIFCFormat( nameOfFormat );
		if ( result )
		{
			VCOMPtr<IIFCSupport>	ifcSupport(IID_IFCSupport);
			if ( ifcSupport )
			{
				if ( mode == ERecordIFCWrapMode::IFC )
				{
					TXString	name;
					if ( VCOM_SUCCEEDED(ifcSupport->GetIFCName2(hObj, name)) )
					{
						result = ifcName.EqualNoCase(name) ;
					}
				}
				else if ( mode == ERecordIFCWrapMode::PSet )
				{
					short cntPsets	= 0;
					if ( VCOM_SUCCEEDED(ifcSupport->IFC_GetNumPsets( hObj, cntPsets)) )
					{
						for ( auto iPset = 0; ! result && iPset < cntPsets ; ++iPset )
						{
							TXString	psetName;
							if ( VCOM_SUCCEEDED(ifcSupport->IFC_GetPsetName( hObj, iPset, psetName )) )
							{
								if ( ifcName.EqualNoCase(psetName)  )
								{
									result	= true;
								}
							}
						}
					}
				}
			}
		}
	}

	return result;
}

/*static*/ ERecordIFCType VWRecordFormatObj::GetIfcRecordType(ERecordIFCWrapMode mode)
{
	ERecordIFCType	result = ERecordIFCType::None;

	switch ( mode )
	{
		case ERecordIFCWrapMode::IFC:		result = ERecordIFCType::IFC;		break;
		case ERecordIFCWrapMode::IFCTag:	result = ERecordIFCType::IFCTag;	break;
		case ERecordIFCWrapMode::PSet:		result = ERecordIFCType::PSet;		break;
		case ERecordIFCWrapMode::None:
		default:							result = ERecordIFCType::None;		break;
	}

	return result;
}

