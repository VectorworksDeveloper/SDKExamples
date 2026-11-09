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

	enum class ESignalCategory
	{
		None,
		Audio,
		Comms,
		Control,
		Data,
		Lighting,
		Network,
		Optical,
		Power,
		Radio,
		Video
	};

	const Uint16	kInvalidUNumber	= -1;
	const double	kInvalidDouble	= -1;
	const TXString	kInvalidString	= "__NNA_NotSet";

	const TXString	kDevDefRecName	= "ConnectCAD Device Definition";

	struct SPinData
	{
		Uint16		fPinID		= 0;
		TXString	fName;
		Uint16		fSourceID	= kInvalidUNumber;	// Only initialized if type is dst
	};

	using TPinDataArr = std::vector<SPinData>;

	struct SExtraData
	{
		double		fAvgConsumption	= kInvalidDouble;
		double		fMaxConsumption	= kInvalidDouble;
		double		fMaxVoltage		= kInvalidDouble;
		double		fMinVoltage		= kInvalidDouble;
		TXString	fPowerFactor	= kInvalidString;
		TXString	fRating			= kInvalidString;
		double		fAmpere			= kInvalidDouble;
		double		fMaxPower		= kInvalidDouble;
		double		fVoltage		= kInvalidDouble;
		WorldPt3	fPosition		= { 0.0, 0.0, 0.0 };
		WorldPt3	fScale			= { 1.0, 1.0, 1.0 };
		WorldPt		f2DOffset		= { 0.0, 0.0 };
		double		fZRotAngle		= 0.0;
		bool		fIsLinkThrough	= false;
	};

	struct SBasicSocketData
	{
		Sint16			fCount		= 0;
		TXString		fType;
		TXString		fSignal;
		TXString		fConn;
		TXString		fNamePrefix;
		TXString		fOrientation;
		UuidStorage		fSPComponentUUID;
		TXString		fSource;
		TPinDataArr		fPinout;
		SExtraData		fExtraData;

		SBasicSocketData() = default;
	};
	using TBaseSocketDataArr	= std::vector<SBasicSocketData>;

	// ------------------------------------------------------------------------------------------------------------
	// {1B1A48F8-1F17-4960-8C15-4475D2F028AC}
	static const VWIID IID_ConnectCADSupport = { 0x1b1a48f8, 0x1f17, 0x4960, { 0x8c, 0x15, 0x44, 0x75, 0xd2, 0xf0, 0x28, 0xac } };

	class DYNAMIC_ATTRIBUTE IConnectCADSupport : public IVWUnknown
	{
		public:
			virtual void						VCOM_CALLTYPE	NotifyElectricalConnectionChange( EConnectionChangeType state, MCObjectHandle hStartObj, MCObjectHandle hEndObject, const UuidStorage& startCompUUID, const UuidStorage& endCompUUID ) = 0;
			virtual void						VCOM_CALLTYPE	ResetSpotlightConnectedDevice( MCObjectHandle hSpotlightObj) = 0;

			virtual bool						VCOM_CALLTYPE	SupportsDeviceDefinitionData( MCObjectHandle hObj) = 0;
			virtual void						VCOM_CALLTYPE	EditDeviceDefinitionDataUI( MCObjectHandle hObj) = 0;

			virtual EPowerConsumptionOption		VCOM_CALLTYPE	GetPowerConsumptionOption() = 0;

			virtual void						VCOM_CALLTYPE	InitElectricalHandler(const TMCObjectHandlesSTLArray& arrObjects) = 0;
			virtual void						VCOM_CALLTYPE	ClearElectricalHandler() = 0;

			virtual MCObjectHandle				VCOM_CALLTYPE	GetDeviceDefinitionRecord() = 0;

			virtual TBaseSocketDataArr			VCOM_CALLTYPE	GetSocketDataFromSymbol(MCObjectHandle hSymbol, bool includeFuses = true, bool* outHasRecord = nullptr) = 0;
			virtual void						VCOM_CALLTYPE	SetSocketData(MCObjectHandle hSymbol, const TBaseSocketDataArr& socketData) = 0;

			virtual MCObjectHandle				VCOM_CALLTYPE	GetInternalWiringObject(MCObjectHandle hResource) = 0;

			virtual ESignalCategory				VCOM_CALLTYPE	GetSignalCategory(const TXString& signal) const = 0;
			virtual void 						VCOM_CALLTYPE	AttachCCADRecordToLight(const TXString& lightSymbolName, const VectorWorks::Filing::TPowerInformationList& gdtfPowerInformationList) = 0;

			virtual void						VCOM_CALLTYPE	ReplaceConnectors(const TMCObjectHandlesSTLArray& arrSymbols) = 0;

			virtual TMCObjectHandlesSTLArray	VCOM_CALLTYPE	GetConnectCADAssociatedObjects(MCObjectHandle hObject) = 0;
	};

	// ------------------------------------------------------------------------------------------------------------
	using IConnectCADSupportPtr = VCOMPtr<IConnectCADSupport>;
}
