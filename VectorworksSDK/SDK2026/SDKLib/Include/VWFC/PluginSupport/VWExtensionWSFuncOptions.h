//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace PluginSupport
	{
		using namespace VectorWorks::Extension;

		// ------------------------------------------------------------------------------------------------------
		class VWWSFunctionCall_EventSink : public VCOMImpl<IWSFunctionCallEventSink>
		{
		public:
								VWWSFunctionCall_EventSink(IVWUnknown* parent);
			virtual				~VWWSFunctionCall_EventSink();

		// IWSFunctionCallEventSink
		public:
			// use the macros DEFINE_WSFuncOpt_DISPATCH_MAP etc to define and implement this
			virtual bool VCOM_CALLTYPE	Execute(EQTOFunction function, const TXString& optionName, MCObjectHandle obj, MCObjectHandle subpart, const std::vector<VWVariant>& args, VWVariant& outResult, bool isEditing) = 0;

		// use the define macro and the function definitions in your header file:
		protected:
			// dispatch routine
//			DEFINE_WSFuncOpt_DISPATCH_MAP;
//
//			outResult is one of: (Note: depending on the function, the result must be in the metric units required by the function, and it will be converted in document units to display in the Worksheet)
//				eVWVariantType_SignedInteger		-> ok
//				eVWVariantType_UnsignedInteger		-> ok
//				eVWVariantType_Double				-> ok
//				eVWVariantType_Float				-> ok
//				eVWVariantType_Bool					-> ok
//				eVWVariantType_String				-> ok
//				VWVariant() or eVWVariantType_Empty	-> error N/A
//				<any other>							-> error #PARMS?
//
//			returns 'true' if the call was handled and value is provided
//
//				bool TCallbackFunction(const SDispatchContext& context, VWVariant& outResult);
		

		protected:
			struct SDispatchContext
			{
				MCObjectHandle					fObject;		// object that would provide the data
				EQTOFunction					fFunction;		// requseted function
				const TXString&					fOptionName;	// requested option, always lower case
				const std::vector<VWVariant>&	farrArguments;	// requested arguments;
				bool							fIsEditing;		// true when the event is called with user input to be applied
																// this can be true only for options defined as SWSFunctionOptionsDef::fEditable = true
																// The event will be executed after edit commit, so the handler can show up alerts
				MCObjectHandle					fSubpart;		// When not nullptr will mean that the value is requested for this subpart of the registered object

				SDispatchContext(MCObjectHandle h, MCObjectHandle subpart, EQTOFunction f, const TXString& n, const std::vector<VWVariant>& a, bool isEditing) : fObject(h), fSubpart(subpart), fFunction(f), fOptionName(n), farrArguments(a), fIsEditing(isEditing) {}
			};
		};

		// ------------------------------------------------------------------------------------------------------
		struct SWSFO_TDType			{ SWSFO_TDType(short v)			{ fVal = v; } short fVal; };
		struct SWSFO_TInternalID	{ SWSFO_TInternalID(short v)		{ fVal = v; } TInternalID fVal; };
		struct SWSFO_UnivName		{ SWSFO_UnivName(const char* v)	{ fVal = v; } const char* fVal; };
		struct SWSFunctionOptionObjectsDef
		{
			short			fTdType;				// kParametricNode would require internalID or univName
			TInternalID		fParametricInternalID;	// if available, otherwise provide universal name
			const char*		fParametricUnivName;	// if internal id is not available for the parametric


			SWSFunctionOptionObjectsDef(const SWSFO_TDType& tdType)							: fTdType(tdType.fVal),     fParametricInternalID(0),       fParametricUnivName(nullptr)       {}
			SWSFunctionOptionObjectsDef(const SWSFO_TInternalID& id)						: fTdType(kParametricNode), fParametricInternalID(id.fVal), fParametricUnivName(nullptr)       {}
			SWSFunctionOptionObjectsDef(const SWSFO_UnivName& univName)						: fTdType(kParametricNode), fParametricInternalID(0),       fParametricUnivName(univName.fVal) {}
			SWSFunctionOptionObjectsDef(TInternalID id, const char* univName)				: fTdType(kParametricNode), fParametricInternalID(id),      fParametricUnivName(univName)      {}
			SWSFunctionOptionObjectsDef(short tdType, TInternalID id, const char* univName) : fTdType(tdType),          fParametricInternalID(id),      fParametricUnivName(univName)      {}
		};

		// ------------------------------------------------------------------------------------------------------
		struct SWSFunctionOptionsDef
		{
			EQTOFunction								fFunction;
			const char*									fOptionName;		// always lower case
			bool										fEditable;			// true when this value can be edited in the worksheet. 
																			// note the edit will be allowed for the option, not for the specified objects, 
																			// which might trigger edit callback for objects that wont support it.
			std::vector<SWSFunctionOptionObjectsDef>	farrObjects;

			size_t			fLocalizableParamCnt = 0;						// number of parameters after the option that will be localized by the system via resource "1914 *"
																			// and reported together with the option names in WorksheetFunctionOptionsRegistry.txt

			// Help for this option will automatically be loaded from the current 'DefaultPluginVWRIdentifier()'
			// Definition and Description of the option must be provided in:
			//	- WSFunctionsHelp/Desc.vwstrings		- for function use in a cell with criteria
			//	- WSFunctionsHelp/Desc DB.vwstrings		- for function use in a database cell
			//
			// The key for the string in these vwstring is generated by the fOptionName. fFunction is the names of the EQTOFunction values.
			//		fFunction + "-" + fOptionName				- function definition to be displayed in the UI
			//		fFunction + "-" + fOptionName + "-desc"		- the function description
			//
			// Example: 
			//	"Area-test"					= "...";
			//	"Area-test-desc"			= "...";
			//
			//
			// The Example (if provided) must be located in a .txt file (UTF-8 with or without BOM, or UTF-16 with BOM)
			//		file location and name:	"WSFunctionsHelp/Opt Examples/" + fFunction + "-" + fOptionName + ".txt"
			//
			//
			//
			// The image (if provided) must be located in a .png file:
			//		file location and name:	"WSFunctionsHelp/Opt Images/" + fFunction + "-" + fOptionName + ".png"
			//
		};

		// alternative to SWSFunctionOptionsDef with an additional option for localizable params count
		struct SWSFunctionOptions2Def
		{
			EQTOFunction								fFunction;
			const char*									fOptionName;
			size_t										fLocalizableParamCnt;			// number of parameters after the option that will be localized by the system via resource "1914 *"
			bool										fEditable;
			std::vector<SWSFunctionOptionObjectsDef>	farrObjects;

		};

		typedef std::vector<SWSFunctionOptionsDef>	TWSFunctionOptionsDefArray;
		typedef std::vector<SWSFunctionOptions2Def>	TWSFunctionOptions2DefArray;
		typedef std::vector<TXString>				TWSFunctionOptions2ValuesArray;

		// ------------------------------------------------------------------------------------------------------
		class VWExtensionWSFuncOptions : public VCOMImmediateImpl<IExtensionWSFunctionOptions>
		{
		public:
											VWExtensionWSFuncOptions(	CallBackPtr,
																		const TWSFunctionOptionsDefArray& arrFunctionOptions);
											VWExtensionWSFuncOptions(	CallBackPtr,
																		const TWSFunctionOptions2DefArray& arrFunctionOptions,
																		const TWSFunctionOptions2ValuesArray& arrLocalizableValues);
			virtual							~VWExtensionWSFuncOptions();

		// IExtensionApp
		public:
			virtual IEventSink* VCOM_CALLTYPE			QueryEventSink(const TSinkIID& iid);

		// IExtensionVSFunctions
		public:
			virtual size_t			VCOM_CALLTYPE	GetFunctionsCount();
			virtual bool			VCOM_CALLTYPE	GetFunctionOption(size_t funcIndex, EQTOFunction& outFunction, TXString& outUnivName /*case insensitive*/, bool& outEditable);
			virtual bool			VCOM_CALLTYPE	GetFunctionOptionDesc(size_t funcIndex,  TXString& outCategory, SIExtensionWSFunctionDefDesc& outFuncDef, SIExtensionWSFunctionDefDesc& outFuncDBDef, TXString& outImageSpec, TXString& outExample);
			virtual size_t			VCOM_CALLTYPE	GetFunctionOptionObjsCount(size_t funcIndex);
			virtual bool			VCOM_CALLTYPE	GetFunctionOptionObj(size_t funcIndex, size_t objIndex, short& outTdType, TInternalID& outInternalIndex, TXString& outUnivName);

		protected:
			virtual void						OnRefCountZero();
			virtual IWSFunctionCallEventSink*	CreateWSFuncOptionsEventSink(IVWUnknown* parent) = 0;
			virtual bool						GetProtectionSinkIID(TSinkIID& outIID);
			virtual IProviderProtection*		CreateProtectionSink(IVWUnknown* parent);

		protected:
			IWSFunctionCallEventSink*	fWSFuncOptionsEventSink;
			bool						fProtectionObtained;
			bool						fHasProtection;
			TSinkIID					fProtectionSinkIID;
			IProviderProtection*		fProtectionSink;

			IWSFuncLocalizableOptionsEventSink*	fWSFuncLocalizableOptionsEventSink = nullptr;

		private:
			struct SWSFunctionOptionDesc : public SWSFunctionOptionsDef
			{
				TXString						fCategory;
				SIExtensionWSFunctionDefDesc	fFunctionDef;		// name and parameters
				SIExtensionWSFunctionDefDesc	fFunctionDBDef;		// name and parameters
				TXString						fDescription;
				TXString						fImageSpec;			// full resource spec path to an image, e.g. PluginVWRFileName/Images/MyImage.png
				TXString						fExample;
			};

			std::vector<SWSFunctionOptionDesc>	farrFunctionOptions;

		private:
			class CWSFuncLocalizableOptionsEventSink : public VCOMImpl<IWSFuncLocalizableOptionsEventSink>
			{
			public:
						CWSFuncLocalizableOptionsEventSink(VWExtensionWSFuncOptions* parent);
				virtual	~CWSFuncLocalizableOptionsEventSink();

			// IWSFuncLocalizableOptionsEventSink
			public:
				virtual size_t VCOM_CALLTYPE GetLocalizableParamCnt(EQTOFunction function, const TXString& optionName);
				virtual void VCOM_CALLTYPE GetLocalizableValues(std::vector<TXString>& outUniversalValues);
 
			private:
				VWExtensionWSFuncOptions*		fParent;
			};

			struct TFuncKey
			{
				EQTOFunction	fFunc;
				TXString		fOptName;
				bool operator < (const TFuncKey& other) const;
			};

			std::map<TFuncKey, size_t>			fmapFuncOpt2LocParamCnt;
			std::vector<TXString>				farrLocalizableValues;
		};
	}
}

#define		DEFINE_WSFuncOpt_DISPATCH_MAP						virtual bool Execute(EQTOFunction function, const TXString& optionName, MCObjectHandle obj, MCObjectHandle subpart, const std::vector<VWVariant>& args, VWVariant& outResult, bool isEditing);

#define		BEGIN_WSFuncOpt_DISPATCH_MAP(clas)					bool clas::Execute(EQTOFunction function, const TXString& optionName, MCObjectHandle obj, MCObjectHandle subpart, const std::vector<VWVariant>& args, VWVariant& outResult, bool isEditing) \
																{ const char* szOptionName = optionName.operator const char*(); szOptionName;
#define		ADD_WSFuncOpt_FUNCTION(wsfunc, option, callbackFun)		if ( function == wsfunc && strcmp(szOptionName, option) == 0 ) { return this->callbackFun( SDispatchContext( obj, subpart, function, optionName, args, isEditing ), outResult ); }
#define		END_WSFuncOpt_DISPATCH_MAP								return false; }
