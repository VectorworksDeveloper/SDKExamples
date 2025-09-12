//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	enum class EConnectionChangeType
	{
		Connect,
		Disconnect
	};

	enum class EPowerConsumptionOption
	{
		AveragePower = 0,
		MaximumPower
	};

	// ------------------------------------------------------------------------------------------------------------
	// {1B1A48F8-1F17-4960-8C15-4475D2F028AC}
	static const VWIID IID_ConnectCADSupport = { 0x1b1a48f8, 0x1f17, 0x4960, { 0x8c, 0x15, 0x44, 0x75, 0xd2, 0xf0, 0x28, 0xac } };

	class DYNAMIC_ATTRIBUTE IConnectCADSupport : public IVWUnknown
	{
		public:
			virtual void	VCOM_CALLTYPE	NotifyElectricalConnectionChange( EConnectionChangeType state, MCObjectHandle hStartObj, MCObjectHandle hEndObject, const UuidStorage& startCompUUID, const UuidStorage& endCompUUID ) = 0;
			virtual void	VCOM_CALLTYPE	ResetSpotlightConnectedDevice( MCObjectHandle hSpotlightObj) = 0;

			virtual bool	VCOM_CALLTYPE	SupportsDeviceDefinitionData( MCObjectHandle hObj) = 0;
			virtual void	VCOM_CALLTYPE	EditDeviceDefinitionDataUI( MCObjectHandle hObj) = 0;

			virtual EPowerConsumptionOption	VCOM_CALLTYPE	GetPowerConsumptionOption() = 0;

			virtual void	VCOM_CALLTYPE	InitElectricalHandler(const TMCObjectHandlesSTLArray& arrObjects) = 0;
			virtual void	VCOM_CALLTYPE	ClearElectricalHandler() = 0;
	};

	// ------------------------------------------------------------------------------------------------------------
	using IConnectCADSupportPtr = VCOMPtr<IConnectCADSupport>;
}
