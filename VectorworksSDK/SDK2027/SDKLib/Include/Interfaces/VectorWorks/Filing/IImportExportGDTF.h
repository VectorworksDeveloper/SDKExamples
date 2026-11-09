//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
#include "IImportExportGltf.h"

#pragma once

namespace VectorWorks
{
	namespace Filing
	{

		// ----------------------------------------------------------------------------------------------------
		struct SGDTFFileInfo
		{
			TXString			fGDTFFileName;
			TXString			fFixtureName;
			TXString			fFixtureMode;
			TXString			fManufacturer;
            size_t              fFootPrint;
			MCObjectHandle		fGdtfSymbolDefinition;
			//ICompressedImagePtr	fTumbnail;
			//IFileIdentifierPtr	fFile;
		};
		typedef std::vector<SGDTFFileInfo> TGDTFFileInfoArray;

		enum EImportOptions
		{
			kImportOptions_Default = 0,
			kImportOptions_ReplaceAll = 1,
			kImportOptions_ReplaceNone = 2
		};

		struct SPinPatch
		{
			TXString	destinationName	= "";
			size_t		pinIndex		= -1;
			size_t		sourcePinIndex	= -1;
		};

		struct SPowerInformation
		{
			std::vector<SPinPatch> arrPinPatches;

			TXString name					= "";
			TXString componentType			= "";
			TXString signalType				= "";
			TXString connectorType			= "";
			TXString wireGroup				= "";
			TXString fuseRating				= "";
					 
			size_t	 pinCount				= 0;
			size_t	 signalLayer			= 0;
					 
			double	 electricalPayLoad		= 0;
			double	 voltageRangeMin		= 0;
			double	 voltageRangeMax		= 0;
			double	 frequencyRangeMin		= 0;
			double	 frequencyRangeMax		= 0;
			double	 cosPhi					= 0;
			double	 maxPayload				= 0;
			double	 fuseCurrent			= 0;
			double	 voltage				= 0;
		};
		using TPowerInformationList = std::vector<SPowerInformation>;

		// ----------------------------------------------------------------------------------------------------
		// {cd87cfd8-fa53-4dda-823c-53662723f08b}
		static const VWIID IID_ImportExportGDTF	= { 0xcd87cfd8, 0xfa53, 0x4dda, {0x82, 0x3c, 0x53, 0x66, 0x27, 0x23, 0xf0, 0x8b } };

		class DYNAMIC_ATTRIBUTE IImportExportGDTF : public IVWSingletonUnknown
		{

			//-----------------------------------------------------------------------------
			// Export GDTF
			// This will export a GDTF File in the given file, if there is a manufacturer file in the ressources from Vectorworks
			// then this file will be just copied. If the fixture is customized, or, there is no manufacturer file a
			// generic file based on the properties from the parameters from the lighting device
		public:
			virtual VCOMError ExportLightingDeviceGDTF(MCObjectHandle handle, IFileIdentifier* filePath, IImportExportObjectGltf* exporter) = 0;

			//-----------------------------------------------------------------------------
			// Import GDTF
			// This will import a GDTF File ans apply the parameters to a Lighting Device. If there is no defined Symbol for the
			// Lighting Device, the GDTF geometry will be dumped in a SymDef and linked to the Lighting Device.
		public:
			virtual VCOMError ImportLightingDeviceGDTF(MCObjectHandle handle, IFileIdentifier* filePath, const TXString& choosenDmxMode) = 0;

			//-----------------------------------------------------------------------------
			// Get List for available GDTF files
			// This give you a array with all available Gdtf files that are currently installed on the local maschine
			// You can acces it via the file info. With the FileIdent you can export use ImportLightingDeviceGdtf to apply
			// changes to a existing Lighting Device
		public:
			virtual VCOMError GetAvailableGDTFFileList(TGDTFFileInfoArray& outArray) = 0;
			
			
			//-----------------------------------------------------------------------------
			// Try to get the linked GDTF file for a LIT File
		public:
			virtual VCOMError GetLinkedGDTFFile(const TXString& litFileName, TXString& outGdtfFileName, TXString& outGdtfMode) = 0;

			// VW2020 SP3
			virtual VCOMError IsValidGdtfSymbol(MCObjectHandle h) = 0;


			//-----------------------------------------------------------------------------
			// VW2021 SP3

			//-----------------------------------------------------------------------------
			// Get List for available GDTF files
			// Opens the linked GDTF for Ligthing Device
			virtual VCOMError OpenFixtureBuilder(MCObjectHandle h) = 0;


			//-----------------------------------------------------------------------------
			// VW2024 SP4

			//-----------------------------------------------------------------------------
			// Export generated GDTF for Blended Projectors and Video Screens
			// This will export a programmatically generated GDTF File in the given file.
			virtual VCOMError ExportVidScreenGDTF(MCObjectHandle handle, IFileIdentifier* filePath, IImportExportObjectGltf* exporter) = 0;

			virtual VCOMError GetAvailableGDTFFileSize( size_t& size ) = 0;


			//-----------------------------------------------------------------------------
			// VW2026 SP3

			//-----------------------------------------------------------------------------
			// Import GDTF to the resources folder
			virtual VCOMError ImportGDTF( IFileIdentifier* pFile ) = 0;

			//-----------------------------------------------------------------------------
			// Import GDTF to the resources folder, but also return the GDTF Symbol Definition object
			virtual VCOMError ImportGDTF( IFileIdentifier* pFile, MCObjectHandle& hGDTFSymbolDef, EImportOptions override = kImportOptions_Default, const bool& refreshRB = true ) = 0;


			//-----------------------------------------------------------------------------
			// VW2027 SP0

			//-----------------------------------------------------------------------------
			// Import MVR
			virtual VCOMError ImportMVR( IFileIdentifier* pFile ) = 0;

			//-----------------------------------------------------------------------------
			// Applying GDTF data to Lighting Device using the name of the GDTF
			// - This will use the first available GDTF Fixture mode
			virtual VCOMError ApplyGDTFDataToLightingDevice(const TXString& gdtfFileName, const MCObjectHandle& hLightingDevice) = 0;

			//-----------------------------------------------------------------------------
			// Applying GDTF data to Lighting Device using the name of the GDTF and the name of the GDTF mode
			// - This will use the specified GDTF Fixture mode
			virtual VCOMError ApplyGDTFDataToLightingDevice(const TXString& gdtfFileName, const TXString& gdtfMode, const MCObjectHandle& hLightingDevice) = 0;

			//-----------------------------------------------------------------------------
			// Imports the GDTF Gobo to the resources folder
			virtual VCOMError ImportGobo( IFileIdentifier* pFile ) = 0;
			
			//-----------------------------------------------------------------------------
			// Imports the GDTF SVG graphic to the specified object.
			// - It must contain the GDTF Fixture UUID.
			virtual VCOMError ImportSVG( const MCObjectHandle& hObject, const TXString& uuid, bool alignToCenter = false ) = 0;

			//-----------------------------------------------------------------------------
			// Export Truss to GDTF
			// This will export a GDTF File in the given file, based on the Truss object parameters and geometry
			virtual VCOMError ExportTrussGDTF( MCObjectHandle hTruss, IFileIdentifier* pFile, IImportExportObjectGltf* exporter ) = 0;

			//-----------------------------------------------------------------------------
			// Export Projector to GDTF
			// This will export a GDTF File in the given file, based on the Projector object parameters and geometry
			virtual VCOMError ExportProjectorGDTF(MCObjectHandle handle, MCObjectHandle hSymDef, IFileIdentifier* filePath, IImportExportObjectGltf* exporter) = 0;

			//-----------------------------------------------------------------------------
			// Export Speaker to GDTF
			// This will export a GDTF File in the given file, based on the Speaker object parameters and geometry
			virtual VCOMError ExportSpeakerGDTF(MCObjectHandle hSpeaker, IFileIdentifier* pFile, IImportExportObjectGltf* exporter) = 0;

			//-----------------------------------------------------------------------------
			// Export Speaker Bumper to GDTF
			// This will export a GDTF File in the given file, based on the Speaker Bumper object parameters and geometry
			virtual VCOMError ExportSpeakerBumperGDTF(MCObjectHandle hBumper, IFileIdentifier* pFile, IImportExportObjectGltf* exporter) = 0;

			//-----------------------------------------------------------------------------
			// Get Power Infromation From Lighting Device with applyied GDTF
			// - The Lighting Device must have GDTF attached
			virtual	VCOMError GetGDTFPowerInfromation(MCObjectHandle& hLightingDevice, TPowerInformationList& powerInfromation) = 0;

			//-----------------------------------------------------------------------------
			// Get the correct DMX Footprint based on the choosen DMX Mode
			// - This will return the DMX Footprint for the specified DMX Mode. If the DMX Mode is not specified it will return the footprint for the first available mode
			// - This will exclude virtual channels and return only the physical channels that are needed for the specified mode
			virtual VCOMError GetCorrectDMXFootprint( const MCObjectHandle& hGDTFSymbol, size_t modeIndex, size_t& footprint ) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportGDTF>		IImportExportGDTFPtr;

	}
}
