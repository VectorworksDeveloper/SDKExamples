//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IEnergyUnits.h"

namespace VectorWorks
{
	namespace EnergyAnalysis
	{
		// ----------------------------------------------------------------------------------------------------
		// {7774A293-913A-4DAA-A573-1FF322FA2954}
		static const VWIID IID_EnergyThermalBridges = { 0x7774a293, 0x913a, 0x4daa, { 0xa5, 0x73, 0x1f, 0xf3, 0x22, 0xfa, 0x29, 0x54 } };

		class DYNAMIC_ATTRIBUTE IEnergyThermalBridges : public IVWUnknown
		{
		public:
			virtual MCObjectHandle			VCOM_CALLTYPE Get() = 0;
			virtual void					VCOM_CALLTYPE Set(MCObjectHandle h) = 0;
	
			virtual bool					VCOM_CALLTYPE Save() = 0;	// Must be called after Set operations

			virtual bool					VCOM_CALLTYPE GetSupportEdit() = 0;
			virtual void					VCOM_CALLTYPE SetSupportEdit(bool value) = 0;

			virtual size_t					VCOM_CALLTYPE GetCount() = 0;
			virtual void					VCOM_CALLTYPE Clear() = 0;

			virtual TXString				VCOM_CALLTYPE GetName(size_t index) = 0;
			virtual void					VCOM_CALLTYPE SetName(size_t index, const TXString& value) = 0;

			virtual Uint32					VCOM_CALLTYPE GetQuantity(size_t index) = 0;
			virtual void					VCOM_CALLTYPE SetQuantity(size_t index, Uint32 value) = 0;

			virtual EThermalBridgeLocation	VCOM_CALLTYPE GetLocation(size_t index) = 0;
			virtual void					VCOM_CALLTYPE SetLocation(size_t index, EThermalBridgeLocation value) = 0;

			virtual double					VCOM_CALLTYPE GetLength(size_t index) = 0;					// m
			virtual void					VCOM_CALLTYPE SetLength(size_t index, double value) = 0;	// m

			virtual double					VCOM_CALLTYPE GetPSI(size_t index) = 0;
			virtual void					VCOM_CALLTYPE SetPSI(size_t index, double value) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyThermalBridges>		IEnergyThermalBridgesPtr;
	}
}