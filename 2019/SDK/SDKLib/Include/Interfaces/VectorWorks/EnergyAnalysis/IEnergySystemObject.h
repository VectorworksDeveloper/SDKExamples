//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace EnergyAnalysis
	{
		enum class ESystemObjectType
		{
			UserProfileSpaceUsePattern,
			UserProfileActivityOfPersons,
			ElectricityLighting,
			ElectricityConsumerElectric,
			ElectricitySmallAppliances,
			ElectricityOffice,
			ElectricityFridge,
			ElectricityFreezer,
			ElectricityFridgeCombo,
			ElectricityDishwasher,
			ElectricityWasher,
			ElectricityDryer,
			ElectricityClothLineEvaporation,
			ElectricityOther,
			ElectricityCooking,
			BuildingUtilPatternRes,
			BuildingUtilPatternNonRes,
			VentilationOperationMode,
			VentilationSystem,
			VentilationDistribution,
			HeatingCompactUnit,
			HeatingHeatPump,
			HeatingBoiler,
			HeatingDistrictHeat,
			HeatingDirectElectric,
			HeatingSolar,
			HeatingOther,
			HeatingDistribution,
			CoolingPanel,
			CoolingRecirculation,
			CoolingSupplyAir,
			CoolingHumidification,
			CoolingDistribution,
			HotWaterCompactUnit,
			HotWaterHeatPump,
			HotWaterBoiler,
			HotWaterDistrictHeat,
			HotWaterDirectElectric,
			HotWaterSolar,
			HotWaterOther,
			HotWaterDistribution,
		};

		// {12A837DB-6D08-4B27-A8CB-CEE687EAB148}
		static const VWIID IID_EnergySystemObject = { 0x12a837db, 0x6d08, 0x4b27, { 0xa8, 0xcb, 0xce, 0xe6, 0x87, 0xea, 0xb1, 0x48 } };

		class DYNAMIC_ATTRIBUTE IEnergySystemObject : public IVWUnknown
		{
		public:
			// tools
			// This function will return true, if the handle has a property energy data.
			virtual bool				VCOM_CALLTYPE IsHandleContainingData(MCObjectHandle h) = 0;
			// This function will delete the energy data from the handle.
			virtual void				VCOM_CALLTYPE DeleteDataFromHandle(MCObjectHandle h) = 0;

		public:
			virtual MCObjectHandle		VCOM_CALLTYPE Get() = 0;

			//This function will load energy data from the handle, if it has data,
			//or this function will load default energy data, if the handle does not have energy data.
			virtual void				VCOM_CALLTYPE LoadCreate(MCObjectHandle h, ESystemObjectType systemType) = 0;

			virtual bool				VCOM_CALLTYPE Save() = 0;	// Must be called after Set operations

			virtual void				VCOM_CALLTYPE CopyDataTo(MCObjectHandle h) = 0;

			virtual size_t				VCOM_CALLTYPE GetParamsCnt() = 0;
			virtual bool				VCOM_CALLTYPE GetParamInfo(size_t paramIndex, TXString& outParamName, CSystemDataParam::EType& outType, EEnergyUnitType& outUnitType) = 0;

			virtual bool				VCOM_CALLTYPE GetParamValue(size_t paramIndex, TXString& outValue) = 0;
			virtual bool				VCOM_CALLTYPE GetParamValue(size_t paramIndex, bool& outValue) = 0;
			virtual bool				VCOM_CALLTYPE GetParamValue(size_t paramIndex, Sint32& outValue) = 0;
			virtual bool				VCOM_CALLTYPE GetParamValue(size_t paramIndex, double& outValue) = 0;

			virtual bool				VCOM_CALLTYPE GetParamValue(const TXString& paramName, TXString& outValue) = 0;
			virtual bool				VCOM_CALLTYPE GetParamValue(const TXString& paramName, bool& outValue) = 0;
			virtual bool				VCOM_CALLTYPE GetParamValue(const TXString& paramName, Sint32& outValue) = 0;
			virtual bool				VCOM_CALLTYPE GetParamValue(const TXString& paramName, double& outValue) = 0;

			virtual bool				VCOM_CALLTYPE SetParamValue(size_t paramIndex, const TXString& inValue) = 0;
			virtual bool				VCOM_CALLTYPE SetParamValue(size_t paramIndex, bool inValue) = 0;
			virtual bool				VCOM_CALLTYPE SetParamValue(size_t paramIndex, Sint32 inValue) = 0;
			virtual bool				VCOM_CALLTYPE SetParamValue(size_t paramIndex, double inValue) = 0;

			virtual bool				VCOM_CALLTYPE SetParamValue(const TXString& paramName, const TXString& inValue) = 0;
			virtual bool				VCOM_CALLTYPE SetParamValue(const TXString& paramName, bool inValue) = 0;
			virtual bool				VCOM_CALLTYPE SetParamValue(const TXString& paramName, Sint32 inValue) = 0;
			virtual bool				VCOM_CALLTYPE SetParamValue(const TXString& paramName, double inValue) = 0;

			virtual bool				VCOM_CALLTYPE SetSystemName(const TXString& systemName) = 0;
			virtual bool				VCOM_CALLTYPE GetSystemName(TXString& outName) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergySystemObject>		IEnergySystemObjectPtr;
	}
}
