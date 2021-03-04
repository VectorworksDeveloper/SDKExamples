//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IEnergyUnits.h"
#include "IExternalSystemData.h"

namespace VectorWorks
{
	namespace EnergyAnalysis
	{
		// ----------------------------------------------------------------------------------------------------
		enum class ERoomType
		{
			Kitchen,
			Bathroom,
			Shower,
			WC,
			Other,
		};

		// ----------------------------------------------------------------------------------------------------
		struct SExtractAir
		{
			ERoomType	fRoomType;
			double		fAirRequirementPreRoom;	// m^3/h

			SExtractAir() { fRoomType = ERoomType::Other; fAirRequirementPreRoom = 0.0; }
		};

		// ----------------------------------------------------------------------------------------------------
		enum class ELightingControlType
		{
			Manual,			// manual
			WithoutOffMode,	// automatic, dimming, not turning off
			WithOffMode,	// automatic, dimming, turning off
			BusSystem,		// by bus system
		};

		// ----------------------------------------------------------------------------------------------------
		// {34917A90-3747-4AA5-B62A-84B2E455F14A}
		static const VWIID IID_EnergySpace = { 0x34917a90, 0x3747, 0x4aa5, { 0xb6, 0x2a, 0x84, 0xb2, 0xe4, 0x55, 0xf1, 0x4a } };

		class DYNAMIC_ATTRIBUTE IEnergySpace : public IVWUnknown
		{
		public:
			// tools
			// This function will return true, if the handle has a property energy data.
			virtual bool    VCOM_CALLTYPE IsHandleContainingData(MCObjectHandle h) = 0;
			// This function will delete the energy data from the handle.
			virtual void    VCOM_CALLTYPE DeleteDataFromHandle(MCObjectHandle h) = 0;

		public:
			virtual MCObjectHandle		VCOM_CALLTYPE Get() = 0;
			
			//This function will load energy data from the handle, if it has data,
			//or this function will load default energy data, if the handle does not have energy data.
			virtual void				VCOM_CALLTYPE LoadCreate(MCObjectHandle h) = 0;
	
			virtual bool				VCOM_CALLTYPE Save() = 0;	// Must be called after Set operations

			virtual void				VCOM_CALLTYPE CopyDataTo(MCObjectHandle h) = 0;
			virtual void				VCOM_CALLTYPE CopyInterfaceDataFrom(IEnergySpace* interfaceData) = 0;

			virtual bool				VCOM_CALLTYPE GetIsModified() = 0;
			virtual void				VCOM_CALLTYPE SetIsModified(bool value) = 0;

			virtual bool				VCOM_CALLTYPE GetSupportEdit() = 0;
			virtual void				VCOM_CALLTYPE SetSupportEdit(bool value) = 0;

			virtual TXString			VCOM_CALLTYPE GetName(bool useOriginal) = 0;
			virtual void				VCOM_CALLTYPE SetName(const TXString & value, bool toOriginal) = 0;

			virtual double				VCOM_CALLTYPE GetArea(bool useOriginal) = 0;				// sq m
			virtual void				VCOM_CALLTYPE SetArea(double value, bool toOriginal) = 0;	// sq m

			virtual double				VCOM_CALLTYPE GetAreaFactor() = 0;				// [0..1]
			virtual void				VCOM_CALLTYPE SetAreaFactor(double value) = 0;	// [0..1]

			virtual double				VCOM_CALLTYPE GetVolume(bool useOriginal) = 0;				// cu m
			virtual void				VCOM_CALLTYPE SetVolume(double value, bool toOriginal) = 0;	// cu m
		
			virtual bool				VCOM_CALLTYPE GetIncludeInEnergyAnalysis() = 0;
			virtual void				VCOM_CALLTYPE SetIncludeInEnergyAnalysis(bool value) = 0;

			virtual SExtractAir			VCOM_CALLTYPE GetExtractAirRoom() = 0;
			virtual void				VCOM_CALLTYPE SetExtractAirRoom(const SExtractAir& extractAirRoom) = 0;

			virtual IExternalSystemDataPtr	VCOM_CALLTYPE GetProfileSpaceUse() = 0;
			virtual void					VCOM_CALLTYPE CopyProfileSpaceUse(IExternalSystemDataPtr profileSpaceUse) = 0;

			virtual double				VCOM_CALLTYPE GetHeight() = 0;				// m
			virtual void				VCOM_CALLTYPE SetHeight(double value) = 0;	// m

			virtual double				VCOM_CALLTYPE GetInstalledLightingPower() = 0;				// W/m2
			virtual void				VCOM_CALLTYPE SetInstalledLightingPower(double value) = 0;	// W/m2

			virtual ELightingControlType	VCOM_CALLTYPE GetLightingControl()  = 0;
			virtual void					VCOM_CALLTYPE SetLightingControl(ELightingControlType value)  = 0;

			virtual bool				VCOM_CALLTYPE GetIsWithMotionDetector() = 0;
			virtual void				VCOM_CALLTYPE SetIsWithMotionDetector(bool value) = 0;

			virtual double				VCOM_CALLTYPE GetLightingFullLoadHours() = 0;				// h/a
			virtual void				VCOM_CALLTYPE SetLightingFullLoadHours(double value) = 0;	// h/a

			// Space settings dialog support
			virtual bool				VCOM_CALLTYPE DialogUI_EditAdvancedOptionsDlg() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergySpace>		IEnergySpacePtr;
	}
}