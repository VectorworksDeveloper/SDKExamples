//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Inventory
	{

		class IObjectCustomData
		{
		public:
			// define data specific for the object, that's needed for edit and preview.
			// the plug-in should allocate the memory, the Inventory will release it.
			virtual ~IObjectCustomData() {}
		};

		// ---------------------------------------------DEFINITIONS--------------------------------------------
		struct SChoicesDef	// public in the SDK with the interface
		{
			struct SChoiceDef
			{
				TXString				fUnivName;
				TXString				fLocalName;

			};

			std::vector<SChoiceDef>		farrChoices;
		};

		struct SParamDef
		{
			size_t						fIndex;
			TXString					fUnivName;
			TXString					fLocalName;
			EFieldStyle					fStyle;
			SChoicesDef					fChoices;
		};

		using SParamDefinitionsArr		= std::vector<SParamDef>;
		struct SPartDef
		{
			bool						fIsVirtual = false;
			TXString					fUnivName;
			TXString					fLocalName;
			SParamDefinitionsArr		farrParameters;
		};

		struct SObjectID
		{
			TInternalID					fInternalID;	// use fUniversalName when fInternalID == 0
			TXString					fUniversalName;	// external plugin universal name
			TXString					fLocalizedName;	// external plugin localized name
		};

		using SPartsDefinitionsArr		= std::vector<SPartDef>;

		// --------------------------------------------------------VALUES--------------------------------------
		struct SParamValue
		{
			std::shared_ptr<TXString>	fStringValue;
			std::shared_ptr<bool>		fBoolValue;
			std::shared_ptr<double>		fDoubleValue;
			std::shared_ptr<Sint32>		fSint32Value;
			std::shared_ptr<size_t>		fSize_tValue;
		};

		using SParamValueArr			= std::vector<SParamValue>;
		struct SPartValue
		{
			SPartValue() { fQuantity = 1; }

			TXString							fPartUnivName;
			TXString							fGettingFromInventory;
			size_t								fQuantity;
			MCObjectHandle						fParentHandle;
			std::shared_ptr<IObjectCustomData>	fCustomData;
			SParamValueArr						fParamValuesArr;
		};

		using SPartValuesArr			= std::vector<SPartValue>;
		struct SObjectParts
		{
			SObjectParts() { fQuantity = 1; }
			SObjectID					fObjectID;
			MCObjectHandle				fhObject;
			TXString					fUnifiedName;
			size_t						fQuantity;
			SPartValuesArr				fArrPartValues;
		};

		// ----------------------------------------------------------------------------------------------------
		// {DBD33EFD-E007-44FE-8A71-35F9871207A0}
		static const Extension::TSinkIID	IID_InventoryObjectDataProvider = { 0xdbd33efd, 0xe007, 0x44fe, { 0x8a, 0x71, 0x35, 0xf9, 0x87, 0x12, 0x7, 0xa0 } };

		class DYNAMIC_ATTRIBUTE IInventoryObjectDataProvider : public Extension::IEventSink
		{
		public:
			virtual SPartsDefinitionsArr	VCOM_CALLTYPE GetPartsDefinitions() = 0;
			virtual SObjectParts			VCOM_CALLTYPE GetPartsValues( MCObjectHandle inObj, bool onlyExistingVirtualParts = false ) = 0;
			virtual TXString				VCOM_CALLTYPE GetPartUnifiedName( const SPartValue& part ) = 0;
			virtual TXString				VCOM_CALLTYPE GetVirtualPartsQuantityRecordName() = 0;
			virtual TXString				VCOM_CALLTYPE GetVirtualPartsInventoriesRecordName() = 0;
			virtual void					VCOM_CALLTYPE SaveObjectData( const SObjectParts& object ) = 0;
			virtual TXString				VCOM_CALLTYPE GetDefaultCategory() = 0;
			virtual std::vector<TXString>	VCOM_CALLTYPE GetAdditionalWorksheetParams() = 0;
			virtual TXString				VCOM_CALLTYPE GetWattage( MCObjectHandle inObj ) = 0;
			virtual void					VCOM_CALLTYPE ReadVirtualPartsFromRecords( const TXString& quantityRecord, const TXString& inventoryRecord, SObjectParts& allParts, bool onlyExistingVirtualParts ) = 0;
			virtual void					VCOM_CALLTYPE WriteVirtualPartsInRecord( const TXString& quantityRecord, const TXString& inventoryRecord, const SObjectParts& allParts, size_t index ) = 0;
		};

		typedef Extension::VCOMSinkPtr<IInventoryObjectDataProvider>		IInventoryObjectDataProviderPtr;
	}
}
