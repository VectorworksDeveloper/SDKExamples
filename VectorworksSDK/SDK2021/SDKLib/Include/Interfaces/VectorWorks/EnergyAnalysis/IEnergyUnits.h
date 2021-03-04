//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace EnergyAnalysis
	{
		// ----------------------------------------------------------------------------------------------------
		struct SShading
		{
			enum EMode
			{
				None,
				Low,
				Medium,
				Hight,
				Custom
			};

			EMode		fShadingMode;
			double		fCustomValue;

			SShading()		{ fShadingMode = SShading::Low; fCustomValue = 0; }
		};

		// ----------------------------------------------------------------------------------------------------
		struct SAdditionalShading
		{
			enum EMode
			{
				None,
				VerExteriorVenetianBlinds,
				HorExteriorVenetianBlinds,
				ExteriorShutters,
				ExteriorShuttersDarkColour,
				VerInteriorVenetianBlinds,
				HorInteriorVenetianBlinds,
				InteriorShutters,
				InteriorShuttersDarkColour,
				InteriorFoil,
				Custom,
			};

			EMode	fShadingMode;
			double	fCustomValue;

			SAdditionalShading()		{ fShadingMode = EMode::None; fCustomValue = 0; }
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EWinDoorType
		{
			Window,
			Door,
			WinDoor
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EWinDoorSummerVentilationType
		{
			DayGF,
			DayUF,
			Night
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EWinDoorSummerVentilationTypeOfUsage
		{
			NotUsed,
			PartOfStandardSummerVentilation,
			PartOfCrossVentilation
		};

		// ----------------------------------------------------------------------------------------------------
		struct SWinDoorSummerVentilationData
		{
			EWinDoorSummerVentilationTypeOfUsage	fTypeOfUsage;
			double									fClearWidth;			// m
			double									fClearHeight;			// m
			double									fClearArea;				// sq m
			bool									fTilting;
			double									fTiltingOpeningWidth;	// m
			double									fHeightFromFloor;		// m

			SWinDoorSummerVentilationData()
			{
				fTypeOfUsage			= EWinDoorSummerVentilationTypeOfUsage::NotUsed;
				fClearWidth				= 0.0;
				fClearHeight			= 0.0;
				fClearArea				= 0.0;
				fTilting				= false;
				fTiltingOpeningWidth	= 0.0;
				fHeightFromFloor		= 0.0;
			}
		};

		// ----------------------------------------------------------------------------------------------------
		enum class ECalculationMode
		{
			Automatic,
			Manual,
		};

		// ----------------------------------------------------------------------------------------------------
		struct SBuildingElemComponent
		{
			bool	fInclude;
			double	fLambda;		// W/(mK)
			double	fThickness;		// m

			SBuildingElemComponent() { fInclude = true; fLambda = 0; fThickness = 0; }
		};
		typedef std::vector<SBuildingElemComponent>	TSCompArray;

		// ---------------------------------------------------------------------------
		enum class EThermalBridgeLocation
		{
			None,
			Ambient,
			Perimeter,
			FloorSlab,
		};

		// ----------------------------------------------------------------------------------------------------
		enum class EEnergyUnitType
		{
			  None
			, None_Undefined_Temp	// Vlado: this is for temp use until we figure out the types of all the parameters
			, Percent				// [0;100]
			, PercentNormal			// [0;1]
			, MM					// Length - mm (document)
			, M						// Length - m
			, SqMM					// Area - sq mm
			, SqM					// Area - sq m
			, CuMM					// Volume cu mm
			, CuM					// Volume cu m
			, C						// Temperature - C
			, KWhPSqMM				// Specific Energy Consumption - kWh/sq m month
			, KWhPSqMA				// Specific Energy Consumption - kWh/sq m a
			, SqMKPW				// Thermal Resistance - sq m K/W
			, WPSqMK				// Transfer Coefficient - W/sq m K
			, WPMK					// Thermal Conductivity - W/mK
			, CuMh					// Volume Flow - cu m/h
			, Wh					// Energy - Wh
			, kWh					// Energy - kWh
			, kWhA					// Energy Annually - kWh/a
			, kWhD					// Energy Daily - kWh/d
			, W						// Power - W
			, kW					// Power - kW
			, WPSqM					// Specific Power - W/sq m
			, WhPCuM				// Specific Power - Wh/cu m
			, WhPSqMK				// Specific Power - Wh/sq m K
			, MJPCuMK				// Heat Capacity - MJ/cu m K
			, KGPSqMA				// CO2 - kg/sq m a
			, L						// Liter - l
			, K						// Temperature Diff - K
			, kKhA					// Temperature Diff - kKh/a
			, MPS					// Wind Velocity - m/s
			, CuMHrSqM				// Air permeability at 50 Pa and noted usually q50 or qa50 (units: m^3/(h*m^2))
			, WPK					// Heat Losses Storage - W/K
			, PPSM					// people/sq m
			, UValue				// This is not unit. This is use only to mark that this is U/R-Value depending.
		};

		typedef std::vector< std::pair<TXString,Sint32> >	TPrecisionArray;

		// ----------------------------------------------------------------------------------------------------
		struct SEnergyUnit
		{
			struct Definition
			{
				TXString	fMark;
				bool		fIsMetric;
				double		fUnitsPerX;			// The conversion: <unit> * fUnitsPerX = <value in the units>
				Sint32		fPrecission;		// number of digits after the decimal point

				bool		fUseFormulasToConvert;
				TXString	fFormulaToUnit;		// from X
				TXString	fFormulaFromUnit;	// to X

				Definition()																														{ fIsMetric = true; fPrecission = 4; fUseFormulasToConvert = false; fUnitsPerX = 1; }
				Definition(bool metric, Sint32 precission, const TXString& mark, double unitsPerX)													{ fIsMetric = metric; fPrecission = precission; fMark = mark; fUseFormulasToConvert = false; fUnitsPerX = 1; }
				Definition(bool metric, Sint32 precission, const TXString& mark, const TXString& formulaToUnit, const TXString& formulaFromUnit)	{ fIsMetric = metric; fPrecission = precission; fMark = mark; fUseFormulasToConvert = true; fUnitsPerX = 1; fFormulaToUnit = formulaToUnit; fFormulaFromUnit = formulaFromUnit; }
			};

			TXString			fName;
			bool				fUseUValue;

			const Definition&	Get(EEnergyUnitType type) const						{ return size_t(type) < farrDefinisions.size() ? farrDefinisions[ size_t(type) ] : fEmptyDefinition; }
			void				Set(EEnergyUnitType type, const Definition& def)	{ for(size_t i=0; i<=size_t(type); ++i) { farrDefinisions.push_back( Definition() ); } farrDefinisions[ size_t(type) ] = def; }

		private:
			typedef std::vector<Definition>	TDefinitionArray;
			TDefinitionArray	farrDefinisions;
			Definition			fEmptyDefinition;
		};

		// ----------------------------------------------------------------------------------------------------
		// {07EA39C0-C5CB-4448-AE7C-9326D6D9FBCF}
		static const VWIID IID_EnergyUnits = { 0x7ea39c0, 0xc5cb, 0x4448, { 0xae, 0x7c, 0x93, 0x26, 0xd6, 0xd9, 0xfb, 0xcf } };

		class DYNAMIC_ATTRIBUTE IEnergyUnits : public IVWSingletonUnknown
		{
		public:
			virtual TXString			VCOM_CALLTYPE GetCurrentUnit() = 0;
			virtual const SEnergyUnit&	VCOM_CALLTYPE GetCurrentUnitDef() = 0;

			virtual void				VCOM_CALLTYPE SetCurrentUnit(const TXString& unitName) = 0;

			virtual void				VCOM_CALLTYPE GetAvailableUnits(TXStringArray& outArrNames) = 0;
			virtual void				VCOM_CALLTYPE GetAvailableUnitAt(const TXString& unitName, SEnergyUnit& outUnit) = 0;
			virtual void				VCOM_CALLTYPE GetAvailablePrecisionsAt(const TXString& unitName, TXStringArray& outArrNames) = 0;
			virtual void				VCOM_CALLTYPE GetAvailablePrecisionsAt(const TXString& unitName, TPrecisionArray& outArrPrecision, size_t& outThermalIndex) = 0;
			virtual void				VCOM_CALLTYPE GetPrecisionAt(const TXString& unitName, short& outTypeIndex, Sint32& outPrecision) = 0;
			virtual void				VCOM_CALLTYPE SetPrecisionTo(const TXString& unitName, short typeIndex, Sint32 precision) = 0;

			virtual TXString			VCOM_CALLTYPE GetValueText(bool UValue) = 0;
			virtual bool				VCOM_CALLTYPE IsUsedUValue() = 0;
			virtual void				VCOM_CALLTYPE SetIsUValueUsedTo(const TXString& unitName, bool isUsed) = 0;

		public:
			virtual TXString			VCOM_CALLTYPE GetDocumentUnitString_X(EEnergyUnitType x) = 0;
			virtual TXString			VCOM_CALLTYPE GetDocumentUnitString_X(EEnergyUnitType x, const SEnergyUnit& currentUnit) = 0;
			virtual double				VCOM_CALLTYPE ConvertX2Document(EEnergyUnitType x, double value) = 0;
			virtual double				VCOM_CALLTYPE ConvertDocument2X(EEnergyUnitType x, double value) = 0;
			virtual double				VCOM_CALLTYPE ConvertDocument2X(EEnergyUnitType x, const SEnergyUnit::Definition& def, double value) = 0;
			virtual double				VCOM_CALLTYPE ConvertString2X(EEnergyUnitType x, const TXString& value) = 0;
			virtual void				VCOM_CALLTYPE ConvertX2Document(EEnergyUnitType x, double value, TXString& outValue, bool incUnitMark = true) = 0;
			virtual double				VCOM_CALLTYPE ConvertX2Document(EEnergyUnitType x, const SEnergyUnit::Definition& def, double value) = 0;
			virtual void				VCOM_CALLTYPE ConvertX2Document(EEnergyUnitType x, const SEnergyUnit::Definition& def, double value, TXString& outValue, bool incUnitMark = true) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyUnits>		IEnergyUnitsPtr;
	}
}
