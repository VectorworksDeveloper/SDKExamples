//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IVectorScriptEngine.h"
#include "IPythonWrapper.h"

namespace VectorWorks
{
	namespace Scripting
	{				
		// ---------------------------------------------------------------------------------------------------
		// {473B0000-869A-4E12-86C9-056EFC87871B}
		static const VWIID IID_PythonScriptEngine = { 0x473b0000, 0x869a, 0x4e12, { 0x86, 0xc9, 0x5, 0x6e, 0xfc, 0x87, 0x87, 0x1b } };

		class IPythonScriptEngine : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE CompileScript(const TXString& script,
														  bool inShouldDisplayDialogs,
														  bool& outWasCompiledSuccessfully,
														  Sint32* outLineNumberOfSelectedError, /* optional. Pass NULL if not desired */
														  TXString* outErrorText /* optional. Pass NULL if not desired */) = 0;

			virtual VCOMError VCOM_CALLTYPE RequestPredefinedCode(EPredefinedCodeRequest predefinedCodeType, TXString& outCode) = 0;


			virtual VCOMError VCOM_CALLTYPE ExecuteScript(const TXString& script, IPythonLogger* logger = NULL) = 0;
			
			virtual VCOMError VCOM_CALLTYPE Repository_RemoveValues() = 0;
			virtual VCOMError VCOM_CALLTYPE Repository_RemoveValue(const TXString& name) = 0;
			virtual VCOMError VCOM_CALLTYPE Repository_GetValue(const TXString& name, VWVariant& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE Repository_SetValue(const TXString& name, const VWVariant& value) = 0;
			virtual VCOMError VCOM_CALLTYPE Repository_GetValueNames(TXStringArray& outArray) = 0;
			
			virtual VCOMError VCOM_CALLTYPE CallUserFunction(void* functionRef, PluginLibraryArgTable* arguments, size_t argumentsCount) = 0;
			virtual VCOMError VCOM_CALLTYPE CallUserProcedure(void* procedureRef, PluginLibraryArgTable* arguments, size_t argumentsCount) = 0;

			virtual VCOMError VCOM_CALLTYPE ReportRuntimeWarning(const TXString& text) = 0;
			virtual VCOMError VCOM_CALLTYPE ReportRuntimeError(const TXString& text) = 0;
			virtual VCOMError VCOM_CALLTYPE DisplayScriptOptionsDlg() = 0;

			virtual VCOMError VCOM_CALLTYPE ScriptContext_Begin(const TXString& script, IPythonLogger* logger = nullptr, IPythonWrapperInitListener* loader = nullptr) = 0;
			virtual VCOMError VCOM_CALLTYPE ScriptContext_AddPackagePath(const TXString& packagePath) = 0;
			virtual VCOMError VCOM_CALLTYPE ScriptContext_AddVariableDef(const TXString& name, const TXString& rightSideValue) = 0;
			virtual VCOMError VCOM_CALLTYPE ScriptContext_AddVariable(const TXString& name, double value) = 0;
			virtual VCOMError VCOM_CALLTYPE ScriptContext_AddVariable(const TXString& name, const TXString& value) = 0;
			virtual VCOMError VCOM_CALLTYPE ScriptContext_Run() = 0;
			virtual VCOMError VCOM_CALLTYPE ScriptContext_RunEx(IPythonLogger* logger) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IPythonScriptEngine>		IPythonScriptEnginePtr;
	}
}
