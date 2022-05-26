//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Units
	{
		enum_def( EDefaultLenghtUnitType,
			FeetNInches,
			Inches,
			Feet,
			Miles,
			Yards,
			Microns,
			Millimeters,
			Centimeters,
			Meters,
			Kilometers,
			Degrees,
		);

		enum_def( EDefaultAreaUnitType,
			SquareInches,
			SquareFeet,
			SquareYards,
			SquareMiles,
			Acres,
			SquareMicrons,
			SquareMillimeters,
			SquareCentimeters,
			SquareMeters,
			SquareKilometers,
			Hectares,
			Ares,
		);

		enum_def( EDefaultVolumeUnitType,
			CubicInches,
			CubicFeet,
			CubicYards,
			Gallons,
			CubicMillimeters,
			CubicCentimeters,
			CubicMeters,
			Litres,
		);

		enum_def( EFractionDisplayStyle,
			Regular,
			Diagonal,
			Horizontal,
		);

		enum_def( ERoundingBase,
			RoundTenth,			// 1
			RoundQuarter,		// 2.5
			RoundHalf,			// 5
		);

		enum_def( EDefaultAngularUnitType,
			Degrees,
			Radians,
			Gradians,
		);

		// {7E724E45-7987-4952-BF2B-29F7E9BFB1FB}
		//===============================================================================
		// Vectorworks Units 
		static const VWIID IID_VWUnits = { 0x7e724e45, 0x7987, 0x4952,{ 0xbf, 0x2b, 0x29, 0xf7, 0xe9, 0xbf, 0xb1, 0xfb } };

		class DYNAMIC_ATTRIBUTE IVWUnits : public IVWUnknown
		{
		public:

			virtual VCOMError VCOM_CALLTYPE	Init(EDefaultLenghtUnitType lengthUnit, EDefaultAreaUnitType areaUnit, EDefaultVolumeUnitType volumeUnit) = 0;
			virtual VCOMError VCOM_CALLTYPE	InitFromDocPrimaryUnits() = 0;
			virtual VCOMError VCOM_CALLTYPE	InitFromDocSecondaryUnits() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetShowUnitMarks(bool value) = 0;
			virtual bool VCOM_CALLTYPE	GetShowUnitMarks() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetShowThousandSeparator(bool value) = 0;
			virtual bool VCOM_CALLTYPE	GetShowThousandSeparator() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetShowTrailingZeroes(bool value) = 0;
			virtual bool VCOM_CALLTYPE	GetShowTrailingZeroes() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetShowLeadingZeroes(bool value) = 0;
			virtual bool VCOM_CALLTYPE	GetShowLeadingZeroes() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetDisplayAsFractions(bool value) = 0;
			virtual bool VCOM_CALLTYPE	GetDisplayAsFractions() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetRoundFractionsToDecimal(bool value) = 0;
			virtual bool VCOM_CALLTYPE	GetRoundFractionsToDecimal() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetDecimalDisplayPrecision(Sint32 n) = 0;	// n is the number of digits after the decimal
			virtual Sint32 VCOM_CALLTYPE GetDecimalDisplayPrecision() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetDimensionPrecision(Sint32 n) = 0; // n is the number of digits after the decimal
			virtual Sint32 VCOM_CALLTYPE GetDimensionPrecision() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetFractionalDisplayPrecision(Sint32 n) = 0; // n where 2^n is the fractional display rounding value
			virtual Sint32 VCOM_CALLTYPE GetFractionalDisplayPrecision() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetFractionalDimensionPrecision(Sint32 n) = 0;// n where 2^n is the fractional dimension rounding value
			virtual Sint32 VCOM_CALLTYPE GetFractionalDimensionPrecision() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetAreaDecimalDisplayPrecision(Sint32 n) = 0;// n is the number of digits after the decimal
			virtual Sint32 VCOM_CALLTYPE GetAreaDecimalDisplayPrecision() = 0;	

			virtual VCOMError VCOM_CALLTYPE	SetVolumeDecimalDisplayPrecision(Sint32 n) = 0;// n is the number of digits after the decimal
			virtual Sint32 VCOM_CALLTYPE GetVolumeDecimalDisplayPrecision() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetDimensionFractionDisplayStyle(EFractionDisplayStyle style) = 0;
			virtual EFractionDisplayStyle VCOM_CALLTYPE	GetDimensionFractionDisplayStyle() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetDimensionRoundingBase(ERoundingBase style) = 0;
			virtual ERoundingBase VCOM_CALLTYPE	GetDimensionRoundingBase() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetDecimalRoundingBase(ERoundingBase style) = 0;
			virtual ERoundingBase VCOM_CALLTYPE	GetDecimalRoundingBase() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetLengthUnitMark(const TXString& str) = 0; // length unit mark (e.g: m, mm, ", ', cm, ...)
			virtual TXString VCOM_CALLTYPE GetLengthUnitMark() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetSpecialLengthUnitMark(const TXString& str) = 0; // for Feet & Inches: the feet unit mark (')
			virtual TXString VCOM_CALLTYPE GetSpecialLengthUnitMark() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetSpecialLengthUnitDivider(const TXString& str) = 0; // for Feet & Inches: the dash for dividing feet and inches (1'-3")
			virtual TXString VCOM_CALLTYPE GetSpecialLengthUnitDivider() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetSquareUnitMark(const TXString& str) = 0; // square unit mark (e.g: "sq m" , ...)
			virtual TXString GetSquareUnitMark() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetCubeUnitMark(const TXString& str) = 0; // cube unit mark (e.g: "cubic m", " cc", ...)
			virtual TXString VCOM_CALLTYPE GetCubeUnitMark() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetAreaUnitMark(const TXString& str) = 0; // area unit mark (e.g: "sq in", "sq m", etc.)
			virtual TXString VCOM_CALLTYPE GetAreaUnitMark() = 0;

			virtual VCOMError VCOM_CALLTYPE	SetVolumeUnitMark(const TXString& str) = 0; //volume unit mark(e.g: "cu in", "cu m", etc.)
			virtual TXString VCOM_CALLTYPE GetVolumeUnitMark() = 0;

			virtual bool VCOM_CALLTYPE IsMetric() = 0;
			virtual VCOMError VCOM_CALLTYPE SetIsMetric(bool value) = 0;

			virtual VCOMError VCOM_CALLTYPE SetUnitPerInch(double value) = 0;
			virtual double VCOM_CALLTYPE GetUnitPerInch() = 0;

			virtual VCOMError VCOM_CALLTYPE SetUnitPerSquareInch(double value) = 0;
			virtual double VCOM_CALLTYPE GetUnitPerSquareInch() = 0;

			virtual VCOMError VCOM_CALLTYPE SetUnitPerCubicInch(double value) = 0;
			virtual double VCOM_CALLTYPE GetUnitPerCubicInch() = 0;

			virtual VCOMError VCOM_CALLTYPE SetAngularUnit(EDefaultAngularUnitType unit) = 0;
			virtual EDefaultAngularUnitType VCOM_CALLTYPE GetAngularUnit() = 0;
		};

		typedef VCOMPtr<IVWUnits> IVWUnitsPtr;

		//===============================================================================
	}
}
