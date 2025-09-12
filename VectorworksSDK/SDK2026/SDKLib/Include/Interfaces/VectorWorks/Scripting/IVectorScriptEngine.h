//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Scripting
	{		
		// ---------------------------------------------------------------------------------------------------
		enum EPredefinedCodeRequest {
			ePredefinedCodeRequest_Procedure,
			ePredefinedCodeRequest_Criteria,
			ePredefinedCodeRequest_ToolAttribute,
			ePredefinedCodeRequest_Parameter,
			ePredefinedCodeRequest_File
		};
		
		// ---------------------------------------------------------------------------------------------------
		// {7B793B1B-E2C8-43A0-86C6-542EEA7E946B}
		static const VWIID IID_VectorScriptEngine = { 0x7B793B1B, 0xE2C8, 0x43A0, { 0x86, 0xC6, 0x54, 0x2E, 0xEA, 0x7E, 0x94, 0x6B } };

		class IVectorScriptEngine : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE CompileScript(const TXString& script,
														  bool inShouldDisplayDialogs,
														  bool& outWasCompiledSuccessfully,
														  Sint32* outLineNumberOfSelectedError, /* optional. Pass NULL if not desired */
														  TXString* outErrorText /* optional. Pass NULL if not desired */) = 0;

			virtual VCOMError VCOM_CALLTYPE RequestPredefinedCode(EPredefinedCodeRequest predefinedCodeType, TXString& outCode) = 0;

			virtual VCOMError VCOM_CALLTYPE CallUserFunction(void* functionRef, PluginLibraryArgTable* arguments, size_t argumentsCount) = 0;
			virtual VCOMError VCOM_CALLTYPE CallUserProcedure(void* procedureRef, PluginLibraryArgTable* arguments, size_t argumentsCount) = 0;

			virtual VCOMError VCOM_CALLTYPE ReportRuntimeWarning(const TXString& text) = 0;
			virtual VCOMError VCOM_CALLTYPE ReportRuntimeError(const TXString& text) = 0;

		// VW2012
		public:
			virtual VCOMError VCOM_CALLTYPE ExecuteScript(const TXString& script) = 0;

			virtual VCOMError VCOM_CALLTYPE Repository_RemoveValues() = 0;
			virtual VCOMError VCOM_CALLTYPE Repository_RemoveValue(const TXString& name) = 0;
			virtual VCOMError VCOM_CALLTYPE Repository_GetValue(const TXString& name, VWVariant& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE Repository_SetValue(const TXString& name, const VWVariant& value) = 0;
			virtual VCOMError VCOM_CALLTYPE Repository_GetValueNames(TXStringArray& outArray) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IVectorScriptEngine>		IVectorScriptEnginePtr;

		// ---------------------------------------------------------------------------------------------------
		const VCOMError		kVCOMError_InvalidRef			= 100;
		const VCOMError		kVCOMError_InvalidParameters	= 101;
	}
}