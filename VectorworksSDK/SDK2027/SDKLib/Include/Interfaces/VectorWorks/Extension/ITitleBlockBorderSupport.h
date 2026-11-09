//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {3201FE5D-1A73-4ECE-8559-F95317563577}
		static const VWIID IID_TitleBlockBorderSupport =
		{ 0x3201fe5d, 0x1a73, 0x4ece, { 0x85, 0x59, 0xf9, 0x53, 0x17, 0x56, 0x35, 0x77 } };

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ITitleBlockBorderSupport : public IVWSingletonUnknown
		{
			public:

				// Project Data...
				virtual bool	VCOM_CALLTYPE AddProjectDataField(const TXString& fieldName, EFieldStyle fieldStyle, const TXString& value, TNumStyleClass numStyle = nsGeneral, Byte accuracy = 0) = 0;
				virtual bool	VCOM_CALLTYPE DeleteProjectDataField(const TXString& fieldName) = 0;
				virtual bool	VCOM_CALLTYPE DeleteProjectDataField(size_t fieldIndex) = 0;

				virtual bool	VCOM_CALLTYPE GetProjectDataFieldsCount(size_t& outCountFields) = 0;
				virtual bool	VCOM_CALLTYPE GetProjectDataFormatName(TXString& outFormatName) = 0;

				// ...Name based selectors
				virtual bool	VCOM_CALLTYPE GetProjectDataFieldIndex(const TXString& fieldName, size_t& outIndex) = 0;

				// ...Index based selectors
				virtual bool	VCOM_CALLTYPE GetProjectDataFieldName(size_t fieldIndex, TXString& outName) = 0;
				virtual bool	VCOM_CALLTYPE GetProjectDataFieldValue(size_t fieldIndex, TXString& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetProjectDataFieldReal(size_t fieldIndex, double& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetProjectDataFieldLong(size_t fieldIndex, Sint32& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetProjectDataFieldBool(size_t fieldIndex, bool& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetProjectDataFieldStyle(size_t fieldIndex, EFieldStyle& outStyle) = 0;
				virtual bool	VCOM_CALLTYPE GetProjectDataFieldNumStyle(size_t fieldIndex, TNumStyleClass& outNumStyle) = 0;
				virtual bool	VCOM_CALLTYPE GetProjectDataFieldAccuracy(size_t fieldIndex, Byte& outAccuracy) = 0;
				virtual bool	VCOM_CALLTYPE GetProjectDataPopupChoices(size_t fieldIndex, TXStringArray& outPopupChoices) = 0;

				// ...Index based mutators
				virtual bool	VCOM_CALLTYPE SetProjectDataFieldValue(size_t fieldIndex, const TXString& value, bool resetTBBs = false) = 0;
				virtual bool	VCOM_CALLTYPE SetProjectDataFieldReal(size_t fieldIndex, double value, bool resetTBBs = false) = 0;
				virtual bool	VCOM_CALLTYPE SetProjectDataFieldLong(size_t fieldIndex, Sint32 value, bool resetTBBs = false) = 0;
				virtual bool	VCOM_CALLTYPE SetProjectDataFieldBool(size_t fieldIndex, bool value, bool resetTBBs = false) = 0;
				virtual bool	VCOM_CALLTYPE SetProjectDataPopupChoices(size_t fieldIndex, const TXStringArray& popupChoices, bool append) = 0;

				// Sheet Data...
				virtual bool	VCOM_CALLTYPE AddSheetDataField(const TXString& fieldName, EFieldStyle fieldStyle, const TXString& value, TNumStyleClass numStyle = nsGeneral, Byte accuracy = 0) = 0;
				virtual bool	VCOM_CALLTYPE DeleteSheetDataField(const TXString& fieldName) = 0;
				virtual bool	VCOM_CALLTYPE DeleteSheetDataField(size_t fieldIndex) = 0;

				virtual bool	VCOM_CALLTYPE GetSheetDataFieldsCount(size_t& outCountFields) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFormatName(TXString& outFormatName) = 0;

				// ...Name based selectors
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldIndex(const TXString& fieldName, size_t& outIndex) = 0;

				// ...Index based selectors
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldName(size_t fieldIndex, TXString& outName) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldDefaultValue(size_t fieldIndex, TXString& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldDefaultReal(size_t fieldIndex, double& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldDefaultLong(size_t fieldIndex, Sint32& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldDefaultBool(size_t fieldIndex, bool& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldStyle(size_t fieldIndex, EFieldStyle& outStyle) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldNumStyle(size_t fieldIndex, TNumStyleClass& outNumStyle) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldAccuracy(size_t fieldIndex, Byte& outAccuracy) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataPopupChoices(size_t fieldIndex, TXStringArray& outPopupChoices) = 0;

				virtual bool	VCOM_CALLTYPE GetSheetDataFieldValue(MCObjectHandle hTitleBlock, size_t fieldIndex, TXString& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldReal(MCObjectHandle hTitleBlock, size_t fieldIndex, double& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldLong(MCObjectHandle hTitleBlock, size_t fieldIndex, Sint32& outValue) = 0;
				virtual bool	VCOM_CALLTYPE GetSheetDataFieldBool(MCObjectHandle hTitleBlock, size_t fieldIndex, bool& outValue) = 0;

				// ...Index based mutators
				virtual bool	VCOM_CALLTYPE SetSheetDataFieldDefaultValue(size_t fieldIndex, const TXString& value) = 0;
				virtual bool	VCOM_CALLTYPE SetSheetDataFieldDefaultReal(size_t fieldIndex, double value) = 0;
				virtual bool	VCOM_CALLTYPE SetSheetDataFieldDefaultLong(size_t fieldIndex, Sint32 value) = 0;
				virtual bool	VCOM_CALLTYPE SetSheetDataFieldDefaultBool(size_t fieldIndex, bool value) = 0;
				virtual bool	VCOM_CALLTYPE SetSheetDataPopupChoices(size_t fieldIndex, const TXStringArray& popupChoices, bool append) = 0;

				virtual bool	VCOM_CALLTYPE SetSheetDataFieldValue(MCObjectHandle hTitleBlock, size_t fieldIndex, const TXString& value, bool resetTBBs = false) = 0;
				virtual bool	VCOM_CALLTYPE SetSheetDataFieldReal(MCObjectHandle hTitleBlock, size_t fieldIndex, double value, bool resetTBBs = false) = 0;
				virtual bool	VCOM_CALLTYPE SetSheetDataFieldLong(MCObjectHandle hTitleBlock, size_t fieldIndex, Sint32 value, bool resetTBBs = false) = 0;
				virtual bool	VCOM_CALLTYPE SetSheetDataFieldBool(MCObjectHandle hTitleBlock, size_t fieldIndex, bool value, bool resetTBBs = false) = 0;

				// Updating of TBB Data
				virtual void	VCOM_CALLTYPE UpdateTBBData(bool updateAutoData) = 0;

				virtual void	VCOM_CALLTYPE SetFileNameSyncSuspended(bool suspendFileNameSync) = 0;
				virtual bool	VCOM_CALLTYPE IsFileNameSyncSuspended() = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<ITitleBlockBorderSupport>	ITitleBlockBorderSupportPtr;
	}
}