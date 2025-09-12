//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks::Extension
{

	enum class EComponnentType
	{
		Input,
		Output,
		Fuse,
		Generator,
		Consumer,
	};


	struct SElectricComponentData
	{
		SElectricComponentData(EComponnentType type): fType( type )
		{
		}

		// Defines how this electric component is connected to other electric components in the same device. 
		// This is used to calculate how the phases are getting passed from inputs to outputs.
		struct InternalConnection
		{
			// The name of the internal connection; It's not shown in UI and it's only for debug purposes; 
			// Better to name it - Source component to destination component and to include in which power patch you set to store it
			// Example: "FROM input 0 TO LinkThrough(L0) OUT
			TXString	fName;

			// You can see how it's used in LightRightElectric::ProcessDrawingObject to construct the tree for the connectors.
			// You can see how it's used in LRElectricTree::Calculate() to do the power calculations.
			size_t		fOwnSocket			= 0;	// The index of the pin of this electric component. Pins are defined in CableConnectors.xml for each connector.
			size_t		fOtherSocketSocket	= 0;	// The index of the pin of the other electric component. Pins are defined in CableConnectors.xml for each connector.

			UuidStorage	fOtherComponent; // The UUID (fCompGeometryUID) of the other electrical component
		};

		UuidStorage						fDeviceUUID;			// The UUID of the device

		// The UUID of the electrical component - If it's virtual component with no real graphics and geometry 
		// the uuid is whatever you want in UUIDStorage format. If there is an real electric component, this field should be the uuid of the component.
		// Both UUIDs are used as a key for the connections map.
		// Two different devices with different DeviceUUID can have the same component UUID.
		UuidStorage						fCompGeometryUID;		
		EComponnentType					fType;					// The type of the component - Input, Output, Fuse, Generator, Consumer
		std::vector<InternalConnection>	fInternalConnections;	// The internal connections of the component

		TXString						fPowerConnector;		// The power connector of the component; It should be settled with universal name from CableConnectors.xml; It's shown in the OIP and does matters for the cable style
		TXString						fName;					// The name of the component; It's shown in the OIP of the device and in the power schematic; Example: "Input", "LinkThrough"
		TXString						fSymbolName;			// The description of the schematic device.
		TXString						fParentDeviceID;		// The ID of the parent device. Currently it's not displayed anywhere and it's used for debug purposes.
		TXString						fParentDeviceName;		// The name of the parent device. Currently it's not displayed anywhere and it's used for debug purposes.
		double							fAverageConsumption		= 0;	// The average wattage that will be consumed by consumer or input component
		double							fMaximumConsumption		= 0;	// The maximum wattage that will be consumed by consumer or input component
		double							fVoltage				= 0;	// Currently not used
		double							fMaximumPower			= 0;	// Currently not used
		bool							fIsLinkThroughOutput	= false;// If this component is output and this flag is true, the component will be Left oriented in the schematic device and its power consumption will be passed through to the first non LinkThrough output up the power connections chain.
		bool							fIsDefaultComponent 	= false;// This is a virtual component without an existing object representing it.
	};

	using TElectricComponentArray = std::vector<SElectricComponentData>;

	// This struct is used to initialize the data for the schematic device at the power schematic.
	struct SSchematicData
	{
		TXString	fUniqueID;		// The unique ID of the schematic device - It's used by the cable tool to show it's start and end objects
		TXString	fName;			// The name of the schematic device
		TXString	fDescription;	// The description of the schematic device

		// The position of the schematic device - Its displayed below the name and description and above the power info
		// If the object has Load Info, the position will be taken from the Load Info and this value will be ignored.
		TXString	fDefaultPosition;
		TXString	fUnitNumber;	// The unit number of the schematic device - Its displayed next to the position
		double		fPowerInWatts = 0.0;	// The power of the schematic device.
	};

	// ----------------------------------------------------------------------------------------------------
	// {5D08CD29-B08F-4234-A5E3-DFB60AE0FF1A}
	static const Extension::TSinkIID IID_CableConnectionsProvider = { 0x5d08cd29, 0xb08f, 0x4234, { 0xa5, 0xe3, 0xdf, 0xb6, 0xa, 0xe0, 0xff, 0x1a } };

	class DYNAMIC_ATTRIBUTE ICableConnectionsProvider : public Extension::IEventSink
	{
	public:
		// Get the electric components of the object
		virtual VCOMError		VCOM_CALLTYPE GetObjectConnections(MCObjectHandle hObject, TElectricComponentArray& outComponents) = 0;

		// Get the schematic data of the device which will be set for name, description, position and unit number of the schematic device.
		// If the result is not NoError, the name will be the parametric name, the description will be the parametric name and the position and unit number will be empty.
		virtual VCOMError		VCOM_CALLTYPE GetDeviceSchematicData(MCObjectHandle hObject, SSchematicData& outData) { return kVCOMError_Failed; }
	};
}