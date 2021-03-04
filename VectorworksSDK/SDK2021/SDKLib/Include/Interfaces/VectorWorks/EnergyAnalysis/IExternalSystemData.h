//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IEnergyUnits.h"

namespace VectorWorks
{
	namespace EnergyAnalysis
	{
		// ---------------------------------------------------------------------------
		// universal name to identify complex data accessible through classes in the 'External' namespace
		typedef	TXString							TExternalUnivID;
		typedef std::vector<TExternalUnivID>		TExternalUnivIDArray;
		typedef std::map<TExternalUnivID, size_t>	TExternalUnivID2IndexMap;

		// ------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IExternalSystemData;

		// ------------------------------------------------------------------------------------
		class CSystemDataParam
		{
		public:
			typedef std::function<void(const IExternalSystemData* system, CSystemDataParam& ioParam)>	TCalculationFunction;
			typedef std::function<void(CSystemDataParam& ioParam)>										TValidationFunction;

		public:
						CSystemDataParam()																: fValueType( EType::Bool )  ,		           fUnit( EEnergyUnitType::None ), fValueCalc( nullptr ), fValueBool( false ), fValueInt( 0 )    , fValueDouble( 0 )     , fValidationLock( false ) { }
						CSystemDataParam(const TExternalUnivID& id, bool value)							: fValueType( EType::Bool )  ,		fID( id ), fUnit( EEnergyUnitType::None ), fValueCalc( nullptr ), fValueBool( value ), fValueInt( 0 )    , fValueDouble( 0 )     , fValidationLock( false ) { }
						CSystemDataParam(const TExternalUnivID& id, Sint32 value)						: fValueType( EType::Int )   ,		fID( id ), fUnit( EEnergyUnitType::None ), fValueCalc( nullptr ), fValueBool( false ), fValueInt( value ), fValueDouble( 0 )     , fValidationLock( false ) { }
						CSystemDataParam(const TExternalUnivID& id, double value)						: fValueType( EType::Double ),		fID( id ), fUnit( EEnergyUnitType::None ), fValueCalc( nullptr ), fValueBool( false ), fValueInt( 0 )    , fValueDouble( value ) , fValidationLock( false ) { }
						CSystemDataParam(const TExternalUnivID& id, const TXString& value)				: fValueType( EType::String ),		fID( id ), fUnit( EEnergyUnitType::None ), fValueCalc( nullptr ), fValueBool( false ), fValueInt( 0 )    , fValueDouble( 0 )     , fValidationLock( false ) { fValueString	= value; }
						CSystemDataParam(const TExternalUnivID& id, TCalculationFunction&& calcFunc)	: fValueType( EType::Calculation ),	fID( id ), fUnit( EEnergyUnitType::None ), fValueCalc( calcFunc ),fValueBool( false ), fValueInt( 0 )    , fValueDouble( 0 )     , fValidationLock( false ) { }
						CSystemDataParam(const CSystemDataParam& src)						{ this->operator=( src ); }
						~CSystemDataParam()													{ }

			CSystemDataParam&	operator=(const CSystemDataParam& src)						{ fID = src.fID; fUnit = src.fUnit; fValueType = src.fValueType; fValueBool = src.fValueBool; fValueInt = src.fValueInt; fValueDouble = src.fValueDouble; fValueString = src.fValueString; fValueCalc = src.fValueCalc; fValueValidate = src.fValueValidate; fValidationLock = false; return *this; }

			enum class EType
			{
				Bool,
				Int,
				Double,
				String,
				Calculation,
			};

			// Specific access
			const TExternalUnivID&	GetID() const									{ return fID; }

			EEnergyUnitType			GetUnit() const									{ return fUnit; }
			void					SetUnit(EEnergyUnitType unit)					{ fUnit = unit; }

			EType					GetValueType() const							{ return fValueType; }

			void					SetValidation(TValidationFunction callback)		{ fValueValidate = callback; }

			bool					IsBeingCalculated() const						{ return fValueCalc != nullptr; /*check if there is a calc function as the type will change from the calculation*/ }

			bool					GetValueBool() const							{																		switch ( fValueType ) { case EType::Bool: return fValueBool;															case EType::Int: return fValueInt != 0;						case EType::Double: return DoublesAreNotNearlyEqual( fValueDouble, 0 );	case EType::String: return fValueString.atoi() != 0 || fValueString.EqualNoCase( "true" );	default: return false;	} }						// GetValueBool
			void					SetValueBool(bool value)						{ if ( fValueType == EType::Calculation ) fValueType = EType::Bool;		switch ( fValueType ) { case EType::Bool: fValueBool = value; break;													case EType::Int: fValueInt = value; break;					case EType::Double: fValueDouble = value; break;						case EType::String: fValueString = value ? "true" : "false"; break;									default: break;			} this->Validate(); }	// SetValueBool
			Sint32					GetValueSint32() const							{ 																		switch ( fValueType ) { case EType::Bool: return fValueBool;															case EType::Int: return fValueInt;							case EType::Double: return (Sint32) fValueDouble;						case EType::String: return fValueString.atoi();														default: return 0;		} }						// GetValueSint32
			void					SetValueSint32(Sint32 value)					{ if ( fValueType == EType::Calculation ) fValueType = EType::Int;		switch ( fValueType ) { case EType::Bool: fValueBool = value != 0; break;												case EType::Int: fValueInt = value; break;					case EType::Double: fValueDouble = value; break;						case EType::String: fValueString.Format( "%d", value ); break;										default: break;			} this->Validate(); }	// SetValueSint32
			double					GetValueDouble() const							{ 																		switch ( fValueType ) { case EType::Bool: return fValueBool;															case EType::Int: return fValueInt;							case EType::Double: return fValueDouble;								case EType::String: return fValueString.atof();														default: return 0.0;	} }						// GetValueDouble
			void					SetValueDouble(double value)					{ if ( fValueType == EType::Calculation ) fValueType = EType::Double;	switch ( fValueType ) { case EType::Bool: fValueBool = DoublesAreNotNearlyEqual( value, 0 ); break;						case EType::Int: fValueInt = (Sint32) value; break;			case EType::Double: fValueDouble = value; break;						case EType::String: fValueString.Format( "%f", value ); break;										default: break;			} this->Validate(); }	// SetValueDouble
			TXString				GetValueString() const							{ TXString result;														switch ( fValueType ) { case EType::Bool: result = fValueBool ? "true" : "false"; break;								case EType::Int: result.Format( "%d", fValueInt ); break;	case EType::Double: result.Format( "%f", fValueDouble ); break;			case EType::String: result = fValueString; break;													default: break;			} return result; }		// GetValueString
			void					SetValueString(const TXString& value)			{ if ( fValueType == EType::Calculation ) fValueType = EType::String;	switch ( fValueType ) { case EType::Bool: fValueBool = value.atoi() != 0 || value.EqualNoCase( "true" ); break;	case EType::Int: fValueInt = value.atoi(); break;			case EType::Double: fValueDouble = value.atof(); break;					case EType::String: fValueString = value; break;													default: break;			} this->Validate(); }	// SetValueString

			void					Calculate(const IExternalSystemData* system)	{ if ( fValueCalc ) fValueCalc( system, *this ); }

		protected:
			void		Validate()													{ if ( fValueValidate && ! fValidationLock ) { /* prevent reqursive validation */ fValidationLock	= true; fValueValidate( *this ); fValidationLock = false; } }

		protected:
			TExternalUnivID			fID;
			EEnergyUnitType			fUnit;
			EType					fValueType;
			Sint32					fValueInt;
			bool					fValueBool;
			double					fValueDouble;
			TXString				fValueString;
			TCalculationFunction	fValueCalc;
			TValidationFunction		fValueValidate;
			bool					fValidationLock;
		};

		// ----------------------------------------------------------------------------------------------------
		// This is private interface accessible through the other energy interfaces
		class DYNAMIC_ATTRIBUTE IExternalSystemData : public IVWUnknown
		{
		public:
			virtual size_t					VCOM_CALLTYPE GetParamsCnt() = 0;
			virtual const CSystemDataParam&	VCOM_CALLTYPE GetParam(size_t paramIndex) = 0;
			virtual void					VCOM_CALLTYPE SetParam(size_t paramIndex, const CSystemDataParam& value) = 0;
			virtual const CSystemDataParam&	VCOM_CALLTYPE GetParam(const char* szParamName) = 0;
			virtual void					VCOM_CALLTYPE SetParam(const char* szParamName, const CSystemDataParam& value) = 0;

			virtual TXString				VCOM_CALLTYPE GetName() const = 0;

		// Dialog UI management
		public:
			virtual void	VCOM_CALLTYPE DialogUI_Fill(short dialogID, short systemCtrlID) = 0;
			virtual void	VCOM_CALLTYPE DialogUI_Select(short dialogID, short systemCtrlID) = 0;

		// Widget UI management
		public:
			virtual void	VCOM_CALLTYPE WidgetUI_Fill(IWidgetDataPopup* widgetPopup, TXString& outItemID)					{}
			virtual void	VCOM_CALLTYPE WidgetUI_Select(IWidgetDataPopup* widgetPopup, const TXString& itemID)			{}
			virtual void	VCOM_CALLTYPE WidgetUI_Fill(IWidgetSearchableDataPopup* widgetPopup, TXString& outItemID)		{}
			virtual void	VCOM_CALLTYPE WidgetUI_Select(IWidgetSearchableDataPopup* widgetPopup, const TXString& itemID)	{}
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IExternalSystemData>		IExternalSystemDataPtr;
	}
}
