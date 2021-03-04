//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VW_RECORD_FORMAT_OBJECT__H
#define VW_RECORD_FORMAT_OBJECT__H

#pragma once

#include <unordered_map>

namespace VWFC
{
	using namespace Tools;
	using namespace VectorWorks::IFCLib;
	
	namespace VWObjects
	{
		// ----------------------------------------------------------------------------------------------------
		enum class ERecordIFCWrapMode
		{
			Auto,
			None,
			IFC,
			PSet,
			IFCTag,
		};

		// ----------------------------------------------------------------------------------------------------
		class VWRecordFormatObj : public VWObject
		{
		public:
								VWRecordFormatObj(MCObjectHandle hFormatHandle, ERecordIFCWrapMode wrapMode=ERecordIFCWrapMode::None);
								VWRecordFormatObj(const TXString& formatName, ERecordIFCWrapMode wrapMode=ERecordIFCWrapMode::None);
								VWRecordFormatObj(const VWRecordFormatObj& src);
			virtual				~VWRecordFormatObj();

			VWRecordFormatObj&	operator=(const VWRecordFormatObj& src);
	
		public:
			TXString			GetFormatName() const;
			TXString			GetFormatLocalizedName() const;
			bool				SetFormatLocalizedName(const TXString& name);
			bool				IsParametric() const;
			void				SetParametric(bool bIsParametric);
			bool				GetFormatVisibility() const;
			void				SetFormatVisibility(bool bVisibility);

			VCOMPtr<VectorWorks::Extension::IEventSink>
								GetParametricEventSink(const VectorWorks::Extension::TSinkIID& sindIID);

		// parameters
		public:
			size_t				AddParamLong(const TXString& name, Sint32 value, bool bUpdateExistingRecords = true);
			size_t				AddParamBool(const TXString& name, bool value, bool bUpdateExistingRecords = true);
			size_t				AddParamReal(const TXString& name, double value, bool bUpdateExistingRecords = true);
			size_t				AddParamCoord(const TXString& name, double value, bool bUpdateExistingRecords = true);
			size_t				AddParamAngle(const TXString& name, double value, bool bUpdateExistingRecords = true);
			size_t				AddParamArea(const TXString& name, double value, bool bUpdateExistingRecords = true);
			size_t				AddParamVolume(const TXString& name, double value, bool bUpdateExistingRecords = true);
			size_t				AddParamString(const TXString& name, const TXString& value, bool bUpdateExistingRecords = true);
			size_t				AddParamPopup(const TXString& name, const TXString& value, bool bUpdateExistingRecords = true);
			size_t				AddParamClassesPopUp(const TXString& name, const TXString& value, bool bUpdateExistingRecords = true);
			size_t				AddParamClass(const TXString& name, InternalIndex resource, bool bUpdateExistingRecords = true);
			size_t				AddParamBuildingMaterial(const TXString& name, InternalIndex resource, bool bUpdateExistingRecords = true);
			size_t				AddParamFill(const TXString& name, const VWPattern& attr, bool bUpdateExistingRecords = true);
			size_t				AddParamPenStyle(const TXString& name, const VWPattern& attr, bool bUpdateExistingRecords = true);
			size_t				AddParamPenWeight(const TXString& name, Uint8 value, bool bUpdateExistingRecords = true);
			size_t				AddParamColor(const TXString& name, ColorRef value, bool bUpdateExistingRecords = true);
			size_t				AddParamTexture(const TXString& name, InternalIndex resource, bool bUpdateExistingRecords = true);
			size_t				AddParamSymDef(const TXString& name, InternalIndex resource, bool bUpdateExistingRecords = true);

			size_t				GetParamsCount() const;
			TXString			GetParamName(size_t paramIndex) const;
			TXString			GetParamLocalizedName(size_t paramIndex) const;
			bool				SetParamLocalizedName(size_t paramIndex, const TXString& name);
			bool				DeleteParam(const TXString& univParamName) const;

			// returns ((size_t) -1) if not found
			size_t				GetParamIndex(const TXString& paramName) const;

			// universal param name based
			EFieldStyle			GetParamStyle(const TXString& univParamName) const;
			TNumStyleClass		GetParamNumStyle(const TXString& univParamName) const;
			void				SetParamNumStyle(const TXString& univParamName, TNumStyleClass value);
			Byte				GetParamAccuracy(const TXString& univParamName) const;
			void				SetParamAccuracy(const TXString& univParamName, Byte value);
			TXString			GetParamValue(const TXString& univParamName) const;
			void				SetParamValue(const TXString& univParamName, const TXString& value);
			Sint32				GetParamLong(const TXString& univParamName) const;
			void				SetParamLong(const TXString& univParamName, Sint32 value);
			bool				GetParamBool(const TXString& univParamName) const;
			void				SetParamBool(const TXString& univParamName, bool value);
			double				GetParamReal(const TXString& univParamName) const;
			void				SetParamReal(const TXString& univParamName, double value);
			TXString			GetParamString(const TXString& univParamName) const;
			void				SetParamString(const TXString& univParamName, const TXString& value);
			InternalIndex		GetParamClass(const TXString& univParamName) const;
			void				SetParamClass(const TXString& univParamName, InternalIndex resource);
			InternalIndex		GetParamBuildingMaterial(const TXString& univParamName) const;
			void				SetParamBuildingMaterial(const TXString& univParamName, InternalIndex resource);
			VWPattern			GetParamFill(const TXString& univParamName) const;
			void				SetParamFill(const TXString& univParamName, const VWPattern& attr);
			VWPattern			GetParamPenStyle(const TXString& univParamName) const;
			void				SetParamPenStyle(const TXString& univParamName, const VWPattern& attr);
			Uint8				GetParamPenWeight(const TXString& univParamName) const;
			void				SetParamPenWeight(const TXString& univParamName, Uint8 value);
			ColorRef			GetParamColor(const TXString& univParamName) const;
			void				SetParamColor(const TXString& univParamName, ColorRef value);
			InternalIndex		GetParamTexture(const TXString& univParamName) const;
			void				SetParamTexture(const TXString& univParamName, InternalIndex resource);
			InternalIndex		GetParamSymDef(const TXString& univParamName) const;
			void				SetParamSymDef(const TXString& univParamName, InternalIndex resource);

			// popup choices support
			size_t				PopupGetChoicesCount(const TXString& univParamName, bool useParametric=true);
			void				PopupGetChoice(const TXString& univParamName, size_t index, TXString& outKey, TXString& outValue, bool useParametric=true);
			void				PopupGetChoices(const TXString& univParamName, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs, bool useParametric=true);
			void				PopupClearChoices(const TXString& univParamName);
			void				PopupSetChoices(const TXString& univParamName, const TXStringArray& keyValuePairs, bool append);
			TXString			PopupGetLocalizedChoice(const TXString& univParamName, const TXString& key);

			// determines if the field has no value defined
			bool				GetIsEmpty(const TXString& univParamName) const;
			void				SetIsEmpty(const TXString& univParamName, bool value);
		 
			// determines if the field value will be determined by the data manager link
			bool				GetIsDataLinked(const TXString& univParamName) const;
			void				SetIsDataLinked(const TXString& univParamName, bool value);

			// UI support
			bool				EditWithUI();
			// return size_t(-1) if canceled, or the index of the new parameter
			size_t				AddParameWithUI(const TXString& name, EFieldStyle style, const TXString& value);
			size_t				EditParamWithUI(const TXString& univParamName);
			size_t				EditParamWithUI(size_t paramIndex);

			bool				EditFieldDefineWithUI(size_t paramIndex);

		public:
			// index based
			// NOTE: Recomended use of universal parameter name based (above) functions because they are safer
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			EFieldStyle			/*Use univParamName funcsion instead*/	GetParamStyle(size_t paramIndex) const;
			TNumStyleClass		/*Use univParamName funcsion instead*/	GetParamNumStyle(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamNumStyle(size_t paramIndex, TNumStyleClass value);
			Byte				/*Use univParamName funcsion instead*/	GetParamAccuracy(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamAccuracy(size_t paramIndex, Byte value);
			TXString			/*Use univParamName funcsion instead*/	GetParamValue(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamValue(size_t paramIndex, const TXString& value);
			Sint32				/*Use univParamName funcsion instead*/	GetParamLong(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamLong(size_t paramIndex, Sint32 value);
			bool				/*Use univParamName funcsion instead*/	GetParamBool(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamBool(size_t paramIndex, bool value);
			double				/*Use univParamName funcsion instead*/	GetParamReal(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamReal(size_t paramIndex, double value);
			TXString			/*Use univParamName funcsion instead*/	GetParamString(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamString(size_t paramIndex, const TXString& value);
			InternalIndex		/*Use univParamName funcsion instead*/	GetParamClass(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamClass(size_t paramIndex, InternalIndex resource);
			InternalIndex		/*Use univParamName funcsion instead*/	GetParamBuildingMaterial(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamBuildingMaterial(size_t paramIndex, InternalIndex resource);
			VWPattern			/*Use univParamName funcsion instead*/	GetParamFill(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamFill(size_t paramIndex, const VWPattern& attr);
			VWPattern			/*Use univParamName funcsion instead*/	GetParamPenStyle(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamPenStyle(size_t paramIndex, const VWPattern& attr);
			Uint8				/*Use univParamName funcsion instead*/	GetParamPenWeight(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamPenWeight(size_t paramIndex, Uint8 value);
			ColorRef			/*Use univParamName funcsion instead*/	GetParamColor(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamColor(size_t paramIndex, ColorRef value);
			InternalIndex		/*Use univParamName funcsion instead*/	GetParamTexture(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamTexture(size_t paramIndex, InternalIndex resource);
			InternalIndex		/*Use univParamName funcsion instead*/	GetParamSymDef(size_t paramIndex) const;
			void				/*Use univParamName funcsion instead*/	SetParamSymDef(size_t paramIndex, InternalIndex resource);


			void				/*Use univParamName funcsion instead*/	DeleteParam(size_t paramIndex);

			size_t				/*Use univParamName funcsion instead*/	PopupGetChoicesCount(size_t paramIndex, bool useParametric=true);
			void				/*Use univParamName funcsion instead*/	PopupGetChoice(size_t paramIndex, size_t index, TXString& outKey, TXString& outValue, bool useParametric=true);
			void				/*Use univParamName funcsion instead*/	PopupGetChoices(size_t paramIndex, std::vector<std::pair<TXString, TXString>>& outKeyValuePairs, bool useParametric=true);
			void				/*Use univParamName funcsion instead*/	PopupClearChoices(size_t paramIndex);
			void				/*Use univParamName funcsion instead*/	PopupSetChoices(size_t paramIndex, const TXStringArray& keyValuePairs, bool append);

			bool				/*Use univParamName funcsion instead*/	GetIsEmpty(size_t paramIndex) const;			// determines if the field has no value defined
			void				/*Use univParamName funcsion instead*/	SetIsEmpty(size_t paramIndex, bool value);
		 
			bool				/*Use univParamName funcsion instead*/	GetIsDataLinked(size_t paramIndex) const;		// determines if the field value will be determined by the data manager link
			void				/*Use univParamName funcsion instead*/	SetIsDataLinked(size_t paramIndex, bool value);

		// Tools
		public:
			// Return true if the specified object handle is record format
			static bool				IsRecordFormatObject(MCObjectHandle hObj);
			static bool				IsRecordFormatObject(MCObjectHandle hObj, const TXString& name);
			static MCObjectHandle	GetRecordFormat(const TXString& name);

			static void				DeleteRecordFormat(MCObjectHandle hRecFormat);

			static bool				IsIFCFormat(const TXString& name);
			static bool				IsIFCFormat(MCObjectHandle hObj);
			static bool				IsIFCFormat(MCObjectHandle hObj, const TXString& ifcName, ERecordIFCWrapMode mode);
			static ERecordIFCType	GetIfcRecordType(ERecordIFCWrapMode mode);

		protected:
			size_t					GetParamIndexByUnivName(const TXString& univParamName) const;
			void					SpecifyIFCRecordType();
			void					SetParamStringI(size_t paramIndex, const TXString& value);
			inline bool				IsIfc() const
			{
				return (fIFCMode == ERecordIFCWrapMode::IFC || fIFCMode == ERecordIFCWrapMode::PSet || fIFCMode == ERecordIFCWrapMode::IFCTag);
			};
			
		protected:
			typedef std::unordered_map<TXString, size_t>		TUnviNameKeyMap;
			TUnviNameKeyMap		fmapUnivNameKey;

			ERecordIFCWrapMode	fIFCMode;		// specified by IFClib
		};
	}
}

#endif // VW_RECORD_FORMAT_OBJECT__H