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
		// {9011FDC8-591D-4BE4-AB66-488079935CFF}
		static const VWIID IID_EnergyBuildingElementOther = { 0x9011fdc8, 0x591d, 0x4be4, { 0xab, 0x66, 0x48, 0x80, 0x79, 0x93, 0x5c, 0xff } };

		class DYNAMIC_ATTRIBUTE IEnergyBuildingElementOther : public IVWUnknown
		{
		public:
			// tools
			// This function will return true, if the handle has a property energy data.
			virtual bool    VCOM_CALLTYPE IsHandleContainingData(MCObjectHandle h) = 0;
			// This function will delete the energy data from the handle.
			virtual void    VCOM_CALLTYPE DeleteDataFromHandle(MCObjectHandle h) = 0;

		public:
			//This function will load energy data from the handle, if it has data,
			//or this function will load default energy data, if the handle does not have energy data.
			virtual MCObjectHandle		VCOM_CALLTYPE Get() = 0;
			virtual void				VCOM_CALLTYPE Load(MCObjectHandle h) = 0;
			virtual bool				VCOM_CALLTYPE Save() = 0;

			virtual void				VCOM_CALLTYPE CopyDataTo(MCObjectHandle h) = 0;
			virtual void				VCOM_CALLTYPE CopyInterfaceDataFrom(IEnergyBuildingElementOther* interfaceDataPtr) = 0;

			virtual bool				VCOM_CALLTYPE GetIsModified() = 0;
			virtual void				VCOM_CALLTYPE SetIsModified(bool value) = 0;

			virtual TXString			VCOM_CALLTYPE GetName(bool useOriginal) = 0;
			virtual void				VCOM_CALLTYPE SetName(const TXString & value, bool toOriginal) = 0;

			virtual double				VCOM_CALLTYPE GetArea(bool useOriginal) = 0;				// sq m
			virtual void				VCOM_CALLTYPE SetArea(double value, bool toOriginal) = 0;	// sq m

			virtual size_t				VCOM_CALLTYPE GetSortIndex() = 0;
			virtual void				VCOM_CALLTYPE SetSortIndex(size_t value) = 0;

			virtual bool				VCOM_CALLTYPE GetIncludeInEnergyAnalysis() = 0;
			virtual void				VCOM_CALLTYPE SetIncludeInEnergyAnalysis(bool value) = 0;

			virtual double				VCOM_CALLTYPE GetUValue(bool useOriginal) = 0;				// W/(m^2 K)
			virtual void				VCOM_CALLTYPE SetUValue(double value, bool toOriginal) = 0;	// W/(m^2 K)
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyBuildingElementOther>		IEnergyBuildingElementOtherPtr;
	}
}
