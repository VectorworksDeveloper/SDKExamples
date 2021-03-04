//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// --------------------------------------------------------------------------------------------------
		// {556DA0A0-8D3F-479A-BB66-600E9C54F582}
		static const VWIID IID_VCOMSpace = { 0x556da0a0, 0x8d3f, 0x479a, {0xbb, 0x66, 0x60, 0x0e, 0x9c, 0x54, 0xf5, 0x82} };

		class ISpaceObjectSupport : public IVWSingletonUnknown
		{
		public:
			enum class SpaceDataSelector {
				SpaceNames,
				OccOrganizations,
				RoomFinishes_Ceiling,
				RoomFinishes_Walls,
				RoomFinishes_Baseboard,
				RoomFinishes_Floor
			};
			
		public:
			// Creates a space object from the polygon "spacePoly" with setting the height "height". 
			virtual MCObjectHandle VCOM_CALLTYPE Create(MCObjectHandle spacePoly, WorldCoord height) = 0;
	
			// Returns the net area "area" of the given space object "spaceObject".
			virtual bool VCOM_CALLTYPE NetArea (MCObjectHandle spaceObject, WorldCoord& outArea) = 0;
			// Returns the gross area "area" of the given space object "spaceObject".
			virtual bool VCOM_CALLTYPE GrossArea (MCObjectHandle spaceObject, WorldCoord& outArea) = 0;
	
			//Returns the net volume of the given space object "spaceObject".
			virtual bool VCOM_CALLTYPE NetVolume (MCObjectHandle spaceObject, WorldCoord& outVolume) = 0;
			//Returns the gross volume of the given space object "spaceObject".
			virtual bool VCOM_CALLTYPE GrossVolume (MCObjectHandle spaceObject, WorldCoord& outVolume) = 0;
	
			//Returns a net polygon of the given space object "spaceObject".
			virtual bool VCOM_CALLTYPE NetPoly (MCObjectHandle spaceObject, MCObjectHandle& outPoly, Boolean isWallInsideFace=false) = 0;
			//Returns a gross polygon of the given space object "spaceObject".
			virtual bool VCOM_CALLTYPE GrossPoly (MCObjectHandle spaceObject, MCObjectHandle& outPoly) = 0;
	
			virtual bool VCOM_CALLTYPE Net3DBoundary (MCObjectHandle spaceObject, MCObjectHandle& outBoundary) = 0;
			virtual bool VCOM_CALLTYPE Gross3DBoundary (MCObjectHandle spaceObject, MCObjectHandle& outBoundary) = 0;

			
			//Set Net Top Offset of an existing Space Object
			virtual bool VCOM_CALLTYPE SetNetTopOffset(MCObjectHandle spaceObject, double fOffset, bool selected = false) = 0;
			//Set Net Bottom Offset of an existing Space Object
			virtual bool VCOM_CALLTYPE SetNetBottomOffset(MCObjectHandle spaceObject, double fOffset, bool selected = false) = 0;
			//Set Gross Top Offset of an existing Space Object
			virtual bool VCOM_CALLTYPE SetGrossTopOffset(MCObjectHandle spaceObject, double fOffset, bool selected = false) = 0;
			//Set Gross Bottom Offset of an existing Space Object
			virtual bool VCOM_CALLTYPE SetGrossBottomOffset(MCObjectHandle spaceObject, double fOffset, bool selected = false) = 0;
			// Add Area Modifiers to current Space Object
			virtual bool VCOM_CALLTYPE AddAreaModifierToSpace(MCObjectHandle spaceObject, std::vector<MCObjectHandle> modifiers) = 0;
			
			// Add Space Name to current Space Object
			virtual bool VCOM_CALLTYPE AddName(MCObjectHandle spaceObject, const TXString& name) = 0;
			// Add Description to current Space Object
			virtual bool VCOM_CALLTYPE AddDescription(MCObjectHandle spaceObject, const TXString& discription) = 0;
			// Add RoomID to current Space Object
			virtual bool VCOM_CALLTYPE AddRoomID(MCObjectHandle spaceObject, const TXString& roomID) = 0;
			
			
			//Assign new Zone to Space Object
			virtual bool VCOM_CALLTYPE AssignZone(MCObjectHandle spaceObject, const TXString& zoneType, const TXString& zoneName) = 0;
			//Returns all available zones of the space tool. String looks like this: [zonetype]-zone
			virtual void VCOM_CALLTYPE AvailableZones (TXStringArray& outStringArray) = 0;
			//Returns all assigned zones of the given space object "spaceObject". Return stringArray which includes max 5 zones. String looks like this: [zonetype]-zone
			virtual bool VCOM_CALLTYPE AssignedZones(MCObjectHandle spaceObject, TXStringArray& outStringArray) = 0;
			// Add Zone to current Document Definition
			virtual bool VCOM_CALLTYPE AddZone( const TXString& zoneType, const TXString& zoneName ) = 0;
			// De-assign Zone from current Space Object
			virtual bool VCOM_CALLTYPE DeassignZone( MCObjectHandle spaceObject, const TXString& zoneType, const TXString& zoneName ) = 0;
			// Rename Zone (n) from current Space Object
			virtual bool VCOM_CALLTYPE RenameAssignedZoneX( MCObjectHandle spaceObject, short inedx, const TXString& zoneType, const TXString& zoneName ) = 0;
			// Return all associated walls with the given Space Object
			virtual bool VCOM_CALLTYPE GetAssociatedWalls( MCObjectHandle spaceObject, TMCObjectHandlesSTLArray& outArrayAccosiatedWalls) = 0;

			
			
			// Update Custom Units from extern
			virtual void VCOM_CALLTYPE UpdateCustomUnitsSupport() = 0;
			
			virtual void VCOM_CALLTYPE GetNumberingStyles( TXStringArray& outArrayNumberingStyles) = 0;
			virtual void VCOM_CALLTYPE GetSpaceNamesOrOccOrganizations( SpaceDataSelector type, TXStringArray& outArrayNumberingStyles) = 0;
			virtual void VCOM_CALLTYPE GetSpaceFinishes( SpaceDataSelector type, TXStringArray& outArrayNumberingStyles) = 0;
		};
	}
}
