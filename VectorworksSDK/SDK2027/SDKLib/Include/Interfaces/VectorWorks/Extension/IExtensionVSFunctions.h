//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IExtension.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		const Uint32	kExtensionVSFunctionsInitFlag_None				= 0;
		const Uint32	kExtensionVSFunctionsInitFlag_DontOpenResource	= 2;

		// ----------------------------------------------------------------------------------------------------
		// {698FD687-E472-4ece-9581-7ABB73E85A4A}
		static const VWGroupID GROUPID_ExtensionVSFunctions = { 0x698fd687, 0xe472, 0x4ece, { 0x95, 0x81, 0x7a, 0xbb, 0x73, 0xe8, 0x5a, 0x4a } };

		// ----------------------------------------------------------------------------------------------------
		// Abstract class base for VectorSrcipt functions provider extension application
		class DYNAMIC_ATTRIBUTE IExtensionVSFunctions : public IExtension
		{
		public:
			virtual Uint32 VCOM_CALLTYPE				Initialize() = 0;
			virtual size_t VCOM_CALLTYPE				GetFunctionsCount() = 0;
			virtual const TXString& VCOM_CALLTYPE		GetFunctionName(size_t funcIndex) = 0;
			virtual const TXString& VCOM_CALLTYPE		GetFunctionCategory(size_t funcIndex) = 0;
			virtual const TXString& VCOM_CALLTYPE		GetFunctionDescription(size_t funcIndex) = 0;
			virtual Sint32 VCOM_CALLTYPE				GetFunctionVersion(size_t funcIndex) = 0;
			virtual Sint8 VCOM_CALLTYPE					GetFunctionScope(size_t funcIndex) = 0;
			virtual bool VCOM_CALLTYPE					GetFunctionHasReturnValue(size_t funcIndex) = 0;
			virtual size_t VCOM_CALLTYPE				GetFunctionParamsCount(size_t funcIndex) = 0;
			virtual const TXString& VCOM_CALLTYPE		GetFunctionParamName(size_t funcIndex, size_t paramIndex) = 0;
			virtual EPluginLibraryArgType VCOM_CALLTYPE	GetFunctionParamType(size_t funcIndex, size_t paramIndex) = 0;
		};
	}
}