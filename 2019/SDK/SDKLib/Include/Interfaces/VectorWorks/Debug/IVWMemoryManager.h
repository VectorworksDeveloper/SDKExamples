//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IMemoryCollector.h"

namespace VectorWorks
{
	namespace Debug
	{
		// ----------------------------------------------------------------------------------------
		// {190E36CE-E944-4E9B-AA96-D355E9975E66}
		static const VWIID IID_VWMemoryManager		= { 0x190E36CE, 0xE944, 0x4E9B, { 0xAA, 0x96, 0xD3, 0x55, 0xE9, 0x97, 0x5E, 0x66 } };
		class DYNAMIC_ATTRIBUTE IVWMemoryManager : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE GetVWMemoryCollector(IMemoryCollector** ppOutCollector) = 0;

			virtual VCOMError VCOM_CALLTYPE Allocate(size_t size, void** ppOutMemory) = 0;
			virtual VCOMError VCOM_CALLTYPE Free(void* pMemory) = 0;
			virtual VCOMError VCOM_CALLTYPE SetPtrSize(void** ppInOutMemory, size_t newSize) = 0;

			virtual VCOMError VCOM_CALLTYPE AllocateHandle(GSHandle& outHandle, size_t size) = 0;
			virtual VCOMError VCOM_CALLTYPE FreeHandle(GSHandle handle) = 0;
			virtual VCOMError VCOM_CALLTYPE GetHandleSize(GSHandle handle, size_t& outSize) = 0;
			virtual VCOMError VCOM_CALLTYPE SetHandleSize(GSHandle handle, size_t newSize) = 0;
			virtual VCOMError VCOM_CALLTYPE ReduceHandleSize(GSHandle handle, size_t newSize) = 0;
			virtual VCOMError VCOM_CALLTYPE GetIsHandleLocked(GSHandle handle, bool& outLocked) = 0;
			virtual VCOMError VCOM_CALLTYPE SetIsHandleLocked(GSHandle handle, bool locked) = 0;
			virtual VCOMError VCOM_CALLTYPE HandleLock(GSHandle handle) = 0;
			virtual VCOMError VCOM_CALLTYPE HandleUnlock(GSHandle handle) = 0;
		};
	}
}