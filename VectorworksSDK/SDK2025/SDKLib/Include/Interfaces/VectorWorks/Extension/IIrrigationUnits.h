//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		enum class EIrrigationUnitType
		{
			  None
			, Real
			, Percent
			, AngleDeg
			, DimSize
			, DimDistance
			, Flow
			, Pressure
			, Velocity
			, Int
			, DimGeneric
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EIrrigationUnitDimSize
		{
			  mm
			, cm
			, in
			, Custom
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EIrrigationUnitDimDistance
		{
			  m
			, ft
			, Custom
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EIrrigationUnitFlow
		{
			  lpm
			, gpm
			, cmph
			, Custom
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EIrrigationUnitPressure
		{
			  kPa
			, psi
			, bar
			, Custom
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EIrrigationUnitVelocity
		{
			  mPs
			, ftPs
			, Custom
		};

		// ----------------------------------------------------------------------------------------------------
		// {0d595367-2dcb-45e2-b2c4-ed3153527725}
		static const VWIID IID_IrrigationUnits = { 0x0d595367, 0x2dcb, 0x45e2, {0xb2, 0xc4, 0xed, 0x31, 0x53, 0x52, 0x77, 0x25}};

		class DYNAMIC_ATTRIBUTE IIrrigationUnits : public IVWSingletonUnknown
		{
		public:
			virtual void		VCOM_CALLTYPE SetDocumentUnit(EIrrigationUnitDimSize unit) = 0;
			virtual void		VCOM_CALLTYPE GetDocumentUnit(EIrrigationUnitDimSize& outUnit) = 0;
			virtual void		VCOM_CALLTYPE SetDocumentUnit(EIrrigationUnitDimDistance unit) = 0;
			virtual void		VCOM_CALLTYPE GetDocumentUnit(EIrrigationUnitDimDistance& outUnit) = 0;
			virtual void		VCOM_CALLTYPE SetDocumentUnit(EIrrigationUnitFlow unit) = 0;
			virtual void		VCOM_CALLTYPE GetDocumentUnit(EIrrigationUnitFlow& outUnit) = 0;
			virtual void		VCOM_CALLTYPE SetDocumentUnit(EIrrigationUnitPressure unit) = 0;
			virtual void		VCOM_CALLTYPE GetDocumentUnit(EIrrigationUnitPressure& outUnit) = 0;
			virtual void		VCOM_CALLTYPE SetDocumentUnit(EIrrigationUnitVelocity unit) = 0;
			virtual void		VCOM_CALLTYPE GetDocumentUnit(EIrrigationUnitVelocity& outUnit) = 0;

			virtual Sint32		VCOM_CALLTYPE GetPrecision(EIrrigationUnitType type) = 0;
			virtual void		VCOM_CALLTYPE SetPrecision(EIrrigationUnitType type, Sint32 precision) = 0;

			virtual void		VCOM_CALLTYPE AllowFractionsWhenConvert2Str(bool value) = 0;

			virtual bool		VCOM_CALLTYPE GetUnitType(TInternalID internalID, const TXString& fieldName, EIrrigationUnitType& unitType) = 0;

			virtual TXString	VCOM_CALLTYPE GettUnitString_X	(EIrrigationUnitType type) = 0;
			virtual double		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitType type, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertX2Metric	(EIrrigationUnitType type, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertStr2Metric	(EIrrigationUnitType type, const TXString& value) = 0;
			virtual void		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitType type, double value, TXString& outValue, bool incUnitMark = true) = 0;

		// Dimension Size
		public:
			virtual TXString	VCOM_CALLTYPE GettUnitString_X	(EIrrigationUnitDimSize x) = 0;
			virtual double		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitDimSize x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertX2Metric	(EIrrigationUnitDimSize x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertStr2Metric	(EIrrigationUnitDimSize x, const TXString& value) = 0;
			virtual void		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitDimSize x, double value, TXString& outValue, bool incUnitMark = true) = 0;
			virtual bool		VCOM_CALLTYPE IsDimSizeExactFraction(double value) = 0;

		// Dimension Distance
		public:
			virtual TXString	VCOM_CALLTYPE GettUnitString_X	(EIrrigationUnitDimDistance x) = 0;
			virtual double		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitDimDistance x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertX2Metric	(EIrrigationUnitDimDistance x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertStr2Metric(EIrrigationUnitDimDistance x, const TXString& value) = 0;
			virtual void		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitDimDistance x, double value, TXString& outValue, bool incUnitMark = true) = 0;

		// Flow
		public:
			virtual TXString	VCOM_CALLTYPE GettUnitString_X	(EIrrigationUnitFlow x) = 0;
			virtual double		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitFlow x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertX2Metric	(EIrrigationUnitFlow x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertStr2Metric	(EIrrigationUnitFlow x, const TXString& value) = 0;
			virtual void		VCOM_CALLTYPE ConvertMetric2X		(EIrrigationUnitFlow x, double value, TXString& outValue, bool incUnitMark = true) = 0;

		// Pressure
		public:
			virtual TXString	VCOM_CALLTYPE GettUnitString_X	(EIrrigationUnitPressure x) = 0;
			virtual double		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitPressure x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertX2Metric	(EIrrigationUnitPressure x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertStr2Metric	(EIrrigationUnitPressure x, const TXString& value) = 0;
			virtual void		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitPressure x, double value, TXString& outValue, bool incUnitMark = true) = 0;

		// Velocity
		public:
			virtual TXString	VCOM_CALLTYPE GettUnitString_X	(EIrrigationUnitVelocity x) = 0;
			virtual double		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitVelocity x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertX2Metric	(EIrrigationUnitVelocity x, double value) = 0;
			virtual double		VCOM_CALLTYPE ConvertStr2Metric	(EIrrigationUnitVelocity x, const TXString& value) = 0;
			virtual void		VCOM_CALLTYPE ConvertMetric2X	(EIrrigationUnitVelocity x, double value, TXString& outValue, bool incUnitMark = true) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IIrrigationUnits>		IIrrigationUnitsPtr;
	}
}
