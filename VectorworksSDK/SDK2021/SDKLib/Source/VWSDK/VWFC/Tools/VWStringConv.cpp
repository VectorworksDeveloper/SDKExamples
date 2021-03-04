//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#include "VectorworksSDK.h"



struct SScale {
	const char*		szName;
	double			dScale;
};

static const SScale	g_arrScales[] = 
{
	{ "Custom",					0 },
	{ "1/32\" = 1'0\"",			1.0/384 },
	{ "1/16\" = 1'0\"",			1.0/192 },
	{ "3/32\" = 1'0\"",			1.0/128 },
	{ "1/8\" = 1'0\"",			1.0/96 },
	{ "3/16\" = 1'0\"",			1.0/64 },
	{ "1/4\" = 1'0\"",			1.0/48 },
	{ "3/8\" = 1'0\"",			1.0/32 },
	{ "1/2\" = 1'0\"",			1.0/24 },
	{ "3/4\" = 1'0\"",			1.0/16 },
	{ "1\" = 1'0\"",			1.0/12 },
	{ "1-1/2\" = 1'0\"",		1.0/8 },
	{ "2\" = 1'0\"",			1.0/6 },
	{ "3\" = 1'0\"",			1.0/4 },
	{ "1\" = 10'0\"",			1.0/120 },
	{ "1\" = 20'0\"",			1.0/240 },
	{ "1\" = 30'0\"",			1.0/360 },
	{ "1\" = 40'0\"",			1.0/480 },
	{ "1\" = 50'0\"",			1.0/600 },
	{ "1\" = 100'0\"",			1.0/1200 },
	{ "1:1",					1.0 },
	{ "1:2",					1.0/2 },
	{ "1:4",					1.0/4 },
	{ "1:5",					1.0/5 },
	{ "1:8",					1.0/8 },
	{ "1:10",					1.0/10 },
	{ "1:20",					1.0/20 },
	{ "1:25",					1.0/25 },
	{ "1:50",					1.0/50 },
	{ "1:100",					1.0/100 },
	{ "1:200",					1.0/200 },
	{ "1:500",					1.0/500 },
	{ "1:1000",					1.0/1000 },
	{ "1:5000",					1.0/5000 },
	{ "1:10000",				1.0/10000 },
	{ "2x",						2.0 },
	{ "3x",						3.0 },
	{ "4x",						4.0 },
	{ "5x",						5.0 },
	{ "6x",						6.0 },
	{ "8x",						8.0 },
	{ "10x",					10.0 },
	{ "15x",					15.0 },
	{ "20x",					20.0 },
	{ "50x",					50.0 },
	{ "100x",					100.0 },
	{ "500x",					500.0 },
	{ NULL,						0 }
};

using namespace VWFC::Tools;

VWStringConv::VWStringConv(const TXString& str)
{
	fbIsString		= true;
	fTheString		= str;
	fdValue			= 0;
}

VWStringConv::VWStringConv(double value)
{
	fbIsString		= false;
	fdValue			= value;
}

VWStringConv::VWStringConv(Sint32 value)
{
	fbIsString		= false;
	fdValue			= value;
}

VWStringConv::~VWStringConv()
{
}

double VWStringConv::GetScale() const
{
	if ( fbIsString ) {
		for(size_t i=0; g_arrScales[i].szName; i++) {
			if ( fTheString.EqualNoCase( g_arrScales[i].szName )  ) {
				return g_arrScales[i].dScale;
			}
		}

		return 0;
	}
	else
		return fdValue;
}

TXString VWStringConv::GetScaleString(double dEpsilon/* = kNearlyEqualEpsilonForDoubles*/) const
{
	if ( ! fbIsString ) {
		for(size_t i=0; g_arrScales[i].szName; i++) {
			if ( MathUtils::Equalish( g_arrScales[i].dScale, fdValue, dEpsilon ) ) {
				return g_arrScales[i].szName;
			}
		}

		TXString	string;
		if ( fdValue == (double)( (Sint32)fdValue ) )
			string.Format( "1:%d", (Sint32)fdValue );
		else
			string.Format( "1:%.3f", fdValue );
		return string;
	}
	else
		return fTheString;
}

double VWStringConv::GetDimCoord() const
{
	if ( fbIsString ) {
		WorldCoord	coord	= 0;
		if ( fTheString.IsEmpty() == false )
		{
			VWFC_VERIFY( ::GS_DimStringToCoord( gCBP, fTheString, coord ) );
		}

		return coord;
	}
	else
		return fdValue;
}

TXString VWStringConv::GetDimCoordString() const
{
	if ( ! fbIsString ) {
		TXString		string;
		::GS_CoordToDimString( gCBP, fdValue, string );
		return string;
	}
	else
		return fTheString;
}

TXString VWStringConv::GetDimCoordString(VectorWorks::Units::EDefaultLenghtUnitType lengthUnit, bool showUnitMarks /*= true*/, Sint32 precision /*= -1*/) const
{
	TXString result;

	if ( !fbIsString )
	{
		VWStringConv::ConvertDimCoord_DoubleToString( fdValue, result, lengthUnit, showUnitMarks, precision );
	}
	else
	{
		result = fTheString;
	}

	return result;
}

TXString VWStringConv::GetDimGeneralCoordString() const
{
	if ( ! fbIsString ) {
		Sint32		precision	= 1;
		VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varUnit1DecDimPrecision, & precision ) );

		double		upi			= 25.4;
		VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varUnit1UnitsPerInch, & upi ) );

		short		format		= ufDecimal;
		VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varUnit1Format, & format ) );

		// convert in document units
		double		dValue			= fdValue * upi / 25.4;
		if ( format == ufFeetAndInches ) {
			// GS_DoubleToString funtion requires the value to be in feet when document is in feet&inches
			dValue		/= 12;		// 1' = 12"
		}

		TXString		str;
		Byte		accuracy		= DemoteTo<Byte>( kVStanev, precision );
		::GS_DoubleToString( gCBP, nsDimension, accuracy, 0 /*unused*/, dValue, str );

		return str;
	}
	else
		return fTheString;
}

TXString VWStringConv::GetDimGeneralCoordString(VectorWorks::Units::EDefaultLenghtUnitType lengthUnit, bool showUnitMarks /*= true*/, Sint32 precision /*= -1*/) const
{
	TXString result;

	if ( !fbIsString )
	{
		Units::IVWUnitsPtr unitsInterface( Units::IID_VWUnits );
		if ( unitsInterface )
		{
			if ( precision == -1 )
			{
				precision = 1;
				VERIFYN( kKIvanov, gSDK->GetProgramVariable( varUnit1DecDimPrecision, &precision ) );
			}

			unitsInterface->Init( lengthUnit, Units::EDefaultAreaUnitType::SquareMeters, Units::EDefaultVolumeUnitType::CubicMeters );
			unitsInterface->SetSpecialLengthUnitDivider( "" );
			unitsInterface->SetDecimalDisplayPrecision( precision );
			unitsInterface->SetShowUnitMarks( showUnitMarks );
			unitsInterface->SetShowTrailingZeroes( true );
			unitsInterface->SetShowLeadingZeroes( true );

			double upi			= unitsInterface->GetUnitPerInch();

			// convert in document units
			double	dValue		= fdValue * upi / 25.4;
			if ( lengthUnit == Units::EDefaultLenghtUnitType::FeetNInches )
			{
				// DoubleToStringInUnits funtion requires the value to be in feet when unit is in feet&inches
				dValue /= 12;		// 1' = 12"
			}

			Byte	accuracy	= DemoteTo<Byte>( kKIvanov, precision );
			gSDK->DoubleToStringInUnits( nsDimension, accuracy, 0, dValue, unitsInterface, result );
		}
	}
	else
	{
		result = fTheString;
	}

	return result;
}

double VWStringConv::GetAngleDeg() const
{
	if ( fbIsString ) {
		double	value		= 0;
		VWFC_VERIFY( ::GS_StringToAngleN( gCBP, fTheString, value ) );
		return value;
	}
	else	
		return fdValue;
}

TXString VWStringConv::GetAngleDegString() const
{
	if ( ! fbIsString ) {
		TXString		string;
		::GS_AngleToStringN( gCBP, fdValue, string );
		return string;
	}
	else 
		return fTheString;
}

TXString VWStringConv::GetAngleDegString(VectorWorks::Units::EDefaultAngularUnitType angleUnit, Sint32 inAccuracy /*= -1*/) const
{
	TXString result;

	if ( !fbIsString )
	{
		Units::IVWUnitsPtr unitsInterface( Units::IID_VWUnits );
		if ( unitsInterface )
		{
			if ( inAccuracy == -1 )
			{
				// Set a big number to use default value.
				inAccuracy = 100;
			}
			else
			{
				// the accuracy in the core start from 1.
				inAccuracy++;
			}

			unitsInterface->SetAngularUnit( angleUnit );
			unitsInterface->SetShowTrailingZeroes( true );
			unitsInterface->SetShowLeadingZeroes( true );

			if ( angleUnit != VectorWorks::Units::EDefaultAngularUnitType::Degrees && inAccuracy != 1 )
			{
				inAccuracy += 3;
			}

			Byte accuracy = DemoteTo<Byte>( kKIvanov, inAccuracy );
			gSDK->DoubleToStringInUnits( nsAngle, accuracy, 0, fdValue, unitsInterface, result );
		}
	}
	else
	{
		result = fTheString;
	}

	return result;
}

double VWStringConv::GetArea() const
{
	double result = 0;
	if ( fbIsString )
	{
		gSDK->StringToArea( fTheString, result );
	}
	else
	{
		result = fdValue;
	}

	return result;
}

//debug
TXString VWStringConv::GetAreaString(bool bPreserveNumber /*= false*/) const
{
	Sint32		precision	= 1;
	VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varUnit1AreaDecPrecision, & precision ) );

	double		upsi			= 25.4 * 25.4;
	VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varUnit1AreaUnitsPerSquareInch, & upsi ) );

	double		dValue			= fdValue;

	if ( ! bPreserveNumber ) {
		// convert in document units
		dValue					= fdValue * upsi / (25.4 * 25.4);
	}

	TXString		str;
	Byte		accuracy		= DemoteTo<Byte>( kVStanev, precision );
	::GS_DoubleToString( gCBP, nsDimensionArea, accuracy, 0 /*unused*/, dValue, str );

	return str;
}

TXString VWStringConv::GetAreaString(VectorWorks::Units::EDefaultAreaUnitType areaUnit, Sint32 precision /*= -1*/) const
{
	TXString result;

	if ( !fbIsString )
	{
		VWStringConv::ConvertArea_DoubleToString( fdValue, result, areaUnit, precision );
	}
	else
	{
		result = fTheString;
	}

	return result;
}

double VWStringConv::GetVolume() const
{
	double result = 0;
	if ( fbIsString )
	{
		gSDK->StringToVolume( fTheString, result );
	}
	else
	{
		result = fdValue;
	}

	return result;
}

TXString VWStringConv::GetVolumeString() const
{
	Sint32		precision	= 1;
	VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varUnit1VolumeDecPrecision, & precision ) );

	double		upci			= 25.4 * 25.4 * 25.4;
	VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varUnit1VolumeUnitsPerCubicInch, & upci ) );

	// convert in document units
	double		dValue			= fdValue * upci / (25.4 * 25.4 * 25.4);

	TXString		str;
	Byte		accuracy		= DemoteTo<Byte>( kVStanev, precision );
	::GS_DoubleToString( gCBP, nsDimensionVolume, accuracy, 0 /*unused*/, dValue, str );

	return str;
}

TXString VWStringConv::GetVolumeString(VectorWorks::Units::EDefaultVolumeUnitType volumeUnit, Sint32 precision /*= -1*/) const
{
	TXString result;

	if ( !fbIsString )
	{
		VWStringConv::ConvertVolume_DoubleToString( fdValue, result, volumeUnit, precision );
	}
	else
	{
		result = fTheString;
	}

	return result;
}

double VWStringConv::GetVWDocumentDouble(TNumStyleClass style) const
{
	if ( fbIsString ) {
		double value		= 0;
		VWFC_VERIFY( ::GS_StringToDouble( gCBP, style, fTheString, value ) );
		return value;
	}
	else 
		return fdValue;
}

TXString VWStringConv::GetVWDocumentDoubleString(TNumStyleClass style, Uint8 accuracy, Uint8 format) const
{
	if ( ! fbIsString ) {
		TXString		string;
		::GS_DoubleToString( gCBP, style, accuracy, format, fdValue, string );
		return string;
	}
	else
		return fTheString;
}

Sint32 VWStringConv::GetMils(VectorWorks::EThicknessUnitsType unitsType) const
{
	Sint32 result = 0;
	gSDK->StringToMils( fTheString, unitsType, result );
	return result;
}

TXString VWStringConv::GetMilsString(VectorWorks::EThicknessUnitsType unitsType) const
{
	return gSDK->MilsToString( (Sint32) fdValue, unitsType );
}

/*static*/ TXString VWStringConv::GetDimCoordUnitString()
{
	TXString	unitMark;
	gSDK->GetProgramVariable( varUnit1UnitMark, &unitMark );	// varUnit1SUnitMark
	if ( unitMark == "'" ) unitMark = "ft";
	else if ( unitMark == "\"" ) unitMark = "in";

	unitMark.Trim();
	return unitMark;
}

/*static*/ TXString VWStringConv::GetAreaUnitString()
{
	TXString	unitMark;
	gSDK->GetProgramVariable( varUnit1AreaUnitMark, &unitMark );

	unitMark.Trim();
	return unitMark;
}

/*static*/ TXString VWStringConv::GetVolumeUnitString()
{
	TXString	unitMark;
	gSDK->GetProgramVariable( varUnit1VolumeUnitMark, &unitMark );

	unitMark.Trim();
	return unitMark;
}

/*static*/ double VWStringConv::ConvertDimCoord_ToDocumentUnits(double value)
{
	double		upi			= 25.4;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1UnitsPerInch, & upi ) );

	short		format		= ufDecimal;
	VERIFYN( kKIvanov, gSDK->GetProgramVariable( varUnit1Format, & format ) );

	// convert to document units
	double		result		= value * upi / 25.4;
	if ( format == ufFeetAndInches )
	{
		result		/= 12;		// 1' = 12"
	}

	return result;
}

/*static*/ double VWStringConv::ConvertDimCoord_FromDocumentUnits(double value)
{
	double		upi			= 25.4;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1UnitsPerInch, & upi ) );

	short		format		= ufDecimal;
	VERIFYN( kKIvanov, gSDK->GetProgramVariable( varUnit1Format, & format ) );

	// convert from document units
	double		result		= value * 25.4 / upi;
	if ( format == ufFeetAndInches )
	{
		result		*= 12;		// 1' = 12"
	}

	return result;
}

/*static*/ double VWStringConv::ConvertDimCoord_ToDocumentUnitsN(double value)
{
	double		upi			= 25.4;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1UnitsPerInch, & upi ) );

	// convert to document units
	double		result		= value * upi / 25.4;

	return result;
}

/*static*/ double VWStringConv::ConvertDimCoord_FromDocumentUnitsN(double value)
{
	double		upi			= 25.4;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1UnitsPerInch, & upi ) );

	// convert from document units
	double		result		= value * 25.4 / upi;

	return result;
}

/*static*/ double VWStringConv::ConvertArea_ToDocumentUnits(double value)
{
	double		upsi			= 25.4 * 25.4;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1AreaUnitsPerSquareInch, & upsi ) );

	// convert in document units
	return value * upsi / (25.4 * 25.4);
}

/*static*/ double VWStringConv::ConvertArea_FromDocumentUnits(double value)
{
	double		upsi			= 25.4 * 25.4;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1AreaUnitsPerSquareInch, & upsi ) );

	// convert in document units
	return value * (25.4 * 25.4) / upsi;
}

/*static*/ double VWStringConv::ConvertVolume_ToDocumentUnits(double value)
{
	double		upci			= 25.4 * 25.4 * 25.4;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1VolumeUnitsPerCubicInch, & upci ) );

	// convert in document units
	return value * upci / (25.4 * 25.4 * 25.4);
}

/*static*/ double VWStringConv::ConvertVolume_FromDocumentUnits(double value)
{
	double		upci			= 25.4 * 25.4 * 25.4;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1VolumeUnitsPerCubicInch, & upci ) );

	// convert in document units
	return value * (25.4 * 25.4 * 25.4) / upci;
}

/*static*/ void VWStringConv::ConvertDimCoord_DoubleToString(double value, TXString& outValue, bool incUnitMark)
{
	Sint32		precision	= 1;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1FracDimPrecision, & precision ) );

	TXString	strFormat;
	strFormat.Format( "%%.%df", precision );

	value = VWStringConv::ConvertDimCoord_ToDocumentUnits( value );
	outValue.Format( strFormat, value );
	if ( incUnitMark )
	{
		outValue += " ";
		outValue += VWStringConv::GetDimCoordUnitString();
	}
}

/*static*/ void VWStringConv::ConvertArea_DoubleToString(double value, TXString& outValue, bool incUnitMark)
{
	Sint32		precision	= 1;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1AreaDecPrecision, & precision ) );

	TXString	strFormat;
	strFormat.Format( "%%.%df", precision );

	value = VWStringConv::ConvertArea_ToDocumentUnits( value );
	outValue.Format( strFormat, value );
	if ( incUnitMark )
	{
		outValue += " ";
		outValue += VWStringConv::GetAreaUnitString();
	}
}

/*static*/ void VWStringConv::ConvertVolume_DoubleToString(double value, TXString& outValue, bool incUnitMark)
{
	Sint32		precision	= 1;
	VERIFYN( kVStanev, gSDK->GetProgramVariable( varUnit1VolumeDecPrecision, & precision ) );

	TXString	strFormat;
	strFormat.Format( "%%.%df", precision );

	value = VWStringConv::ConvertVolume_ToDocumentUnits( value );
	outValue.Format( strFormat, value );
	if ( incUnitMark )
	{
		outValue += " ";
		outValue += VWStringConv::GetVolumeUnitString();
	}
}

/*static*/ void VWStringConv::ConvertDimCoord_DoubleToString(double value, TXString& outValue, VectorWorks::Units::EDefaultLenghtUnitType lengthUnit, bool incUnitMark /*= true*/, Sint32 precision /*= -1*/)
{
	outValue.Clear();

	Units::IVWUnitsPtr unitsInterface( Units::IID_VWUnits );
	if ( unitsInterface )
	{
		if ( precision == -1 )
		{
			precision = 1;
			VERIFYN( kKIvanov, gSDK->GetProgramVariable( varUnit1DecDimPrecision, &precision ) );
		}

		unitsInterface->Init( lengthUnit, Units::EDefaultAreaUnitType::SquareMeters, Units::EDefaultVolumeUnitType::CubicMeters );
		unitsInterface->SetSpecialLengthUnitDivider( "" );
		unitsInterface->SetDecimalDisplayPrecision( precision );
		unitsInterface->SetShowUnitMarks( incUnitMark );
		unitsInterface->SetShowTrailingZeroes( true );
		unitsInterface->SetShowLeadingZeroes( true );
		gSDK->CoordToDimStringInUnits( value, unitsInterface, outValue );
	}
}

/*static*/ void VWStringConv::ConvertArea_DoubleToString(double value, TXString& outValue, VectorWorks::Units::EDefaultAreaUnitType areaUnit, Sint32 precision /*= -1*/)
{
	outValue.Clear();

	Units::IVWUnitsPtr unitsInterface( Units::IID_VWUnits );
	if ( unitsInterface )
	{
		if ( precision == -1 )
		{
			precision = 1;
			VERIFYN( kKIvanov, gSDK->GetProgramVariable( varUnit1AreaDecPrecision, &precision ) );
		}

		unitsInterface->Init( Units::EDefaultLenghtUnitType::Millimeters, areaUnit, Units::EDefaultVolumeUnitType::CubicMeters );
		unitsInterface->SetAreaDecimalDisplayPrecision( precision );
		unitsInterface->SetShowTrailingZeroes( true );
		unitsInterface->SetShowLeadingZeroes( true );

		double upsi			= unitsInterface->GetUnitPerSquareInch();

		double dValue		= value * upsi / ( 25.4 * 25.4 );

		Byte	accuracy	= DemoteTo<Byte>( kKIvanov, precision );
		gSDK->DoubleToStringInUnits( nsDimensionArea, accuracy, 0, dValue, unitsInterface, outValue );
	}
}

/*static*/ void VWStringConv::ConvertVolume_DoubleToString(double value, TXString& outValue, VectorWorks::Units::EDefaultVolumeUnitType volumeUnit, Sint32 precision /*= -1*/)
{
	outValue.Clear();

	Units::IVWUnitsPtr unitsInterface( Units::IID_VWUnits );
	if ( unitsInterface )
	{
		if ( precision == -1 )
		{
			precision = 1;
			VERIFYN( kKIvanov, gSDK->GetProgramVariable( varUnit1VolumeDecPrecision, &precision ) );
		}

		unitsInterface->Init( Units::EDefaultLenghtUnitType::Millimeters, Units::EDefaultAreaUnitType::SquareMeters, volumeUnit );
		unitsInterface->SetVolumeDecimalDisplayPrecision( precision );
		unitsInterface->SetShowTrailingZeroes( true );
		unitsInterface->SetShowLeadingZeroes( true );
			
		double	upci		= unitsInterface->GetUnitPerCubicInch();
	
		double	dValue		= value * upci / ( 25.4 * 25.4 * 25.4 );

		Byte	accuracy	= DemoteTo<Byte>( kKIvanov, precision );
		gSDK->DoubleToStringInUnits( nsDimensionVolume, accuracy, 0, dValue, unitsInterface, outValue );
	}
}

/*static*/ TXString	VWStringConv::WorksheetParamDelimiter()
{
	TXString result;
	gSDK->GetProgramVariable( varWSParamDelimiter, & result );
	return result;
}

