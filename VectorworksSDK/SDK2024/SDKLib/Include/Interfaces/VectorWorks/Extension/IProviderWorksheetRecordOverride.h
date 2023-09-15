//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IProviderShapePane.h"

// Summary:
//	This provider is used to hide the data of formats/records. This is mostly usable for hiding parametric format/record,
//	so the worksheet doesn't directly offer the inner data of the parametrics to the user,
//	and expose it as a new set of fields provided and managed by the implementation.
//	This works in a very similar way as the IProviderShapePane
//
// Usage:
//	1. Define a new VWIID for your implementation:		static const VWIID IID_TestWorksheetProvider = ...
//	2. Implement the interface in your plugin:			class CTesteWorksheetProvider : public VCOMImmediateImpl<IProviderWorksheetRecordOverride>
//	3. Register the interface as a regular VCOM:		REGISTER_Interface<SiteModel::CStakeWorksheetProvider>( SiteModel::IID_TestWorksheetProvider, action, moduleInfo, iid, inOutInterface, cbp, reply );
//	4. Associate the implementation with your parametric.
//		a. Define a IObjUpdateSupport implementation (if not already)	class CUpdateSupport : public VCOMImmediateImpl<IObjUpdateSupport>
//		b. And register it												REGISTER_Interface<SiteModel::CUpdateSupport>( GROUPID_ObjUpdateSupport, SiteModel::IID_UpdateSupport, action, moduleInfo, iid, inOutInterface, cbp, reply );
//		c. Then associate a record/format 
//																		void CUpdateSupport::Init(IObjUpdateSupportContext* context)
//																		{
//																			context->AddWorksheetRecordOverrideProvider( "TestObjUnivName", IID_TestWorksheetProvider );
//
// Notes:
//	- This is primarily desiged for parametric records, created by the parametric extension's parameters, allowing the parametric to hide it and preset to the user a nice clean list of parameters to the Worksheet
//	- It can be used for any record/formats, specified by name. This must beused only for formats/records created and mnaged by the parametric. It's not recommened for general use for any format/record
//
//
namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		struct SProviderWorksheetField
		{
			TXString	fUniversalName;
			TXString	fLocalizedName;
			EFieldStyle	fStyle			= kFieldLongInt;
		};

		typedef std::vector<SProviderWorksheetField>	TProviderWorksheetFields;

		// ----------------------------------------------------------------------------------------------------
		struct TWorksheetCellPopupItem
		{
			TXString	fUniversalName;
			TXString	fLocalizedName;

			TWorksheetCellPopupItem() {}
			TWorksheetCellPopupItem(const TXString& univ, const TXString& local) : fUniversalName(univ), fLocalizedName(local) {}
		};

		typedef std::vector<TWorksheetCellPopupItem>		TWorksheetCellPopupList;

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderWorksheetRecordOverride : public IEventSink
		{
		public:
			// The Format/Record will not be displayed in UI, but it will still provide data when used in a cell
			virtual bool VCOM_CALLTYPE		IsVisible()			{ return true; }

			// The localized name to be used in the UI
			virtual TXString VCOM_CALLTYPE	GetLocalizedName() = 0;

			// Provide fields to be listed as available in the UI
			virtual void VCOM_CALLTYPE		GetAvailableFields(TProviderWorksheetFields& outFields) = 0;

			// Get the field type to determine the type of data in the cell
			//	Note:	This is a fast accessor to the data provided by 'GetAvailableFields'
			//			The implementation needs to make sure the data is identical, only it's faster to call (rather than array loop lookup)
			virtual bool VCOM_CALLTYPE		GetFieldType(const TXString& univParamName, EFieldStyle& outFieldType) = 0;

		public:
			// Return the value of a field as a variant. Depending on the field type (GetFieldType) the corresponding VWVariant type is expected
			// EFieldStyle match to variant types:
			//	kFieldReal				- VWVariant::SetDouble
			//	kFieldLongInt			- VWVariant::SetSint32
			//	kFieldBoolean			- VWVariant::SetBool
			//	kFieldText				- VWVariant::operator=(const TXString& value) or the other string operator=
			//	kFieldPopUp				- VWVariant::operator=(const TXString& value) or the other string operator=
			//	kFieldStaticText		- VWVariant::operator=(const TXString& value) or the other string operator=
			//	kFieldRadio				- VWVariant::operator=(const TXString& value) or the other string operator=
			//	kFieldClassesPopup		- VWVariant::operator=(const TXString& value) or the other string operator=
			//	kFieldPenWeight			- VWVariant::SetUint8
			//	kFieldColor				- VWVariant::SetUint16	( for ColorRef	    ) 
			//	kFieldPenStyle			- VWVariant::SetSint32	( for InternalIndex ) 
			//	kFieldFill				- VWVariant::SetSint32	( for InternalIndex ) 
			//	kFieldClass				- VWVariant::SetSint32	( for InternalIndex ) or VWVariant::SetTXString ( for name )
			//	kFieldBuildingMaterial	- VWVariant::SetSint32	( for InternalIndex ) or VWVariant::SetTXString ( for name )
			//	kFieldTexture			- VWVariant::SetSint32	( for InternalIndex ) or VWVariant::SetTXString ( for name )
			//	kFieldSymDef			- VWVariant::SetSint32	( for InternalIndex ) or VWVariant::SetTXString ( for name )
			//	kFieldCoordDisp			- VWVariant::SetDouble
			//	kFieldCoordLocX			- VWVariant::SetDouble
			//	kFieldCoordLocY			- VWVariant::SetDouble
			//	kFieldArea				- VWVariant::SetDouble
			//	kFieldVolume			- VWVariant::SetDouble
			//	kFieldAngle				- VWVariant::SetDouble
			//
			// Parameters:
			//	obj				- can be null_ptr when the requested value is from the defaults (not associated with an object)
			//	localizedValue	- parameter is required for popup fields, where the Worksheet request to show the localized value of the choice, instead of the universal
			//
			virtual bool VCOM_CALLTYPE		GetFieldValue(MCObjectHandle obj, const TXString& univParamName, VWVariant& outValue, bool localizedValue) = 0;
			virtual bool VCOM_CALLTYPE		SetFieldValue(MCObjectHandle obj, const TXString& univParamName, const VWVariant& newValue) = 0;

			// Allow the worksheet to change this field, then the new value will be pushed via a 'SetFieldValue' call
			// The return value should be synchronized with the 'IsFieldByStyle' as by-style fields should be reported non editable
			// the difference is just the reason for not being able to edit
			virtual bool VCOM_CALLTYPE		IsFieldEditable(const TXString& univParamName)																	{ return true; }

			// Mark a field by-style, which means tha the Worksheet will not be able to change it, and show an alert instead
			// The return value should be synchronized with the 'IsFieldEditable' as by-style fields should be reported non editable
			// the difference is just the reason for not being able to edit
			virtual bool VCOM_CALLTYPE		IsFieldByStyle(MCObjectHandle obj, const TXString& univParamName)												{ return false; }

			// This function will be called for kFieldPopUp or kFieldRadio to get a custom list
			// 'obj' might be nullptr when the function is called to translate universal to localized in general
			virtual bool VCOM_CALLTYPE		GetFieldPopupList(MCObjectHandle obj, const TXString& univParamName, TWorksheetCellPopupList& outCustomList)	{ return false; }
		};
	}
}