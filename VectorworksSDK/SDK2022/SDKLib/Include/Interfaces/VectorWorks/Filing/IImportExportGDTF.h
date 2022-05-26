//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


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
			virtual VCOMError ExportLightingDeviceGDTF(MCObjectHandle handle, IFileIdentifier* filePath) = 0;

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

		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportGDTF>		IImportExportGDTFPtr;

	}
}