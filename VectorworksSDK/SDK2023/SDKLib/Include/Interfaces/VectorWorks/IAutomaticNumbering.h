//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	// ------------------------------------------------------------------------------------------------------------------------------------
	// {806EF48A-3053-4929-87A9-419E75430483}
	static const VWIID IID_AutomaticNumbering = { 0x806ef48a, 0x3053, 0x4929, { 0x87, 0xa9, 0x41, 0x9e, 0x75, 0x43, 0x4, 0x83 } };

	// ------------------------------------------------------------------------------------------------------------------------------------
	enum class EIncrementTypes
	{
		Integer,
		LowerCaseChar,
		UpperCaseChar,
	};

	// ------------------------------------------------------------------------------------------------------------------------------------
	struct SSequenceData
	{
		MCObjectHandle	fhObject			= nullptr;

		// Used if the increment value will be saved to text objects
		MCObjectHandle	fhLinkedText		= nullptr;

		// The current increment value of the object
		TXString		fstrCurrentValue	= "";
	};
	using TSequenceDataArray = std::vector<SSequenceData>;

	// ------------------------------------------------------------------------------------------------------------------------------------
	struct SFilterOption
	{
		// The criteria that will be applied to the objects passed to Manage Sequence dialog
		// Example is ( (L='Layer-1') & (C='None') ), which gets the object which are in layer Layer-1 and in class None
		TXString fUniversalCriteria;

		// The choice displayed in the Filter popup in Manage Sequence dialog
		TXString fLocalizedValue;
	};
	using TFilterOptionArray = std::vector<SFilterOption>;

	// ------------------------------------------------------------------------------------------------------------------------------------
	struct SAutoNumberingData
	{
		EIncrementTypes		fIncrementType		= EIncrementTypes::UpperCaseChar;

		// The sequence data that will be processed
		TSequenceDataArray	fSequenceData;

		// The starting value of the sequence - displayed in manage sequence dialog
		TXString			fStartValue;
		// The increment value - defines the increment between two preceeding values
		Sint32				fIncrementValue		= 1;
		// The next value - defines which is the next value that will be assigned to an object added to the sequence
		TXString			fNextValue;

		// Specify additional filters that should be displayed in the manage sequence dialog
		TFilterOptionArray	farrAdditionalFilters;
	};

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IAutomaticNumbering : public IVWUnknown
	{
		public:
			// Shows Manage Sequence dialog. Returns true if the dialog is closed with OK.
			// Modifies inOutNumberingData on dialog close with OK.
			// The objects are used for the basic filters in the manage sequence dialog
			// If empty list is passed, the first object from inOutNumberingData.fSequenceData will be used
			virtual bool				VCOM_CALLTYPE ShowManageSequenceDialog(const TMCObjectHandlesSTLArray& arrObjects, SAutoNumberingData& inOutNumberingData) = 0;

			// Renumbers fSequenceData of inOutNumberingData without showing dialogs, using the passed information in inOutNumberingData.
			// Returns true if the renumbering was successful.
			virtual bool				VCOM_CALLTYPE RenumberAll(SAutoNumberingData& inOutNumberingData) = 0;

			// Shows Manage Sequence dialog. Returns true if the dialog is closed with OK.
			// Modifies the output parameters on dialog close with OK.
			virtual bool				VCOM_CALLTYPE ShowSequenceSettingsDialog(bool isRenumberVisible, const EIncrementTypes& incrementType, TXString& inOutStartValue, Sint32& inOutIncrement, TXString& inOutNextValue) = 0;

			virtual TXString			VCOM_CALLTYPE GetLetterByNumber(size_t inputInt, bool toUpper) = 0;
			virtual Sint32				VCOM_CALLTYPE GetNumberByLetter(const TXString& inputStr, bool isUpper) = 0;
			virtual TXString			VCOM_CALLTYPE IntToStringLeadingZeroes(Sint32 value, size_t length, EIncrementTypes incrType) = 0;
	};

	// ------------------------------------------------------------------------------------------------------------------------------------
	typedef VCOMPtr<IAutomaticNumbering> IAutomaticNumberingPtr;
}
