//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace TrussAnalysis
	{
		// ----------------------------------------------------------------------------------------------------
		enum class EMassUnit
		{
			Milligram		= 0,
			Gram			= 1,
			Kilogram		= 2,
			Tonne			= 3,
			Ounce			= 4,
			Pound			= 5,
			Stone			= 6,
			Quarter			= 7,
			HundredWeightUK	= 8,
			HundredWeightUS	= 9,
			ShortTon		= 10,
			LongTon			= 11,
			Custom			= 12,
		};


		// ----------------------------------------------------------------------------------------------------
		enum class EMassDistributedUnit
		{
			GramPerMillimeter	= 0,
			KilogramPerMeter	= 1,
			OuncePerInch		= 2,
			PoundPerFoot		= 3,
			Custom				= 4,
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EForceUnit
		{
			Newton		= 0,
			Kilonewton	= 1,
			OunceForce	= 2,
			PoundForce	= 3,
			Custom		= 4,
		};

		template <class UnitEnum> struct SUnitSettingData
		{
			UnitEnum	fUnit;
			short		fPrecision;
			bool		fShowUnitMark;
		};

		// ----------------------------------------------------------------------------------------------------
		// {C038FD23-1970-4643-9932-C0018628480E}
		static const VWIID IID_MassForceUnits	= { 0xc038fd23, 0x1970, 0x4643, { 0x99, 0x32, 0xc0, 0x1, 0x86, 0x28, 0x48, 0xe } };

		class DYNAMIC_ATTRIBUTE IMassForceUnits : public IVWSingletonUnknown
		{
		public:
			
			virtual void		VCOM_CALLTYPE GetDocumentUnit(SUnitSettingData<EMassUnit>& unit) = 0;
			virtual void		VCOM_CALLTYPE SetDocumentUnit(const SUnitSettingData<EMassUnit>& unit) = 0;
			virtual void		VCOM_CALLTYPE GetDocumentUnit(SUnitSettingData<EMassDistributedUnit>& unit) = 0;
			virtual void		VCOM_CALLTYPE SetDocumentUnit(const SUnitSettingData<EMassDistributedUnit>& unit) = 0;
			virtual void		VCOM_CALLTYPE GetDocumentUnit(SUnitSettingData<EForceUnit>& unit) = 0;
			virtual void		VCOM_CALLTYPE SetDocumentUnit(const SUnitSettingData<EForceUnit>& unit) = 0;

			// Mass units
			virtual TXString	VCOM_CALLTYPE GetUnitMark	(EMassUnit x) = 0;
			virtual TXString	VCOM_CALLTYPE GetUnitName	(EMassUnit x) = 0;
			virtual double		VCOM_CALLTYPE GetUnitScale	(EMassUnit x) = 0;
			virtual bool		VCOM_CALLTYPE MassStringToReal			(const TXString& value, double& result) = 0;
			virtual TXString	VCOM_CALLTYPE MassRealToDocumentString	(double value) = 0;
			virtual TXString	VCOM_CALLTYPE MassRealToString			(double value, SUnitSettingData<EMassUnit> unit) = 0;

			// Mass Distributed units
			virtual TXString	VCOM_CALLTYPE GetUnitMark	(EMassDistributedUnit x) = 0;
			virtual TXString	VCOM_CALLTYPE GetUnitName	(EMassDistributedUnit x) = 0;
			virtual double		VCOM_CALLTYPE GetUnitScale	(EMassDistributedUnit x) = 0;
			virtual bool		VCOM_CALLTYPE MassDistrStringToReal			(const TXString& value, double& result) = 0;
			virtual TXString	VCOM_CALLTYPE MassDistrRealToDocumentString	(double value) = 0;
			virtual TXString	VCOM_CALLTYPE MassDistrRealToString			(double value, SUnitSettingData<EMassDistributedUnit> unit) = 0;

			// Force units
			virtual TXString	VCOM_CALLTYPE GetUnitMark	(EForceUnit x) = 0;
			virtual TXString	VCOM_CALLTYPE GetUnitName	(EForceUnit x) = 0;
			virtual double		VCOM_CALLTYPE GetUnitScale	(EForceUnit x) = 0;
			virtual bool		VCOM_CALLTYPE ForceStringToReal			(const TXString& value, double& result) = 0;
			virtual TXString	VCOM_CALLTYPE ForceRealToDocumentString	(double value) = 0;
			virtual TXString	VCOM_CALLTYPE ForceRealToString			(double value, SUnitSettingData<EForceUnit> unit) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IMassForceUnits>		IMassForceUnitsPtr;
	}
}
