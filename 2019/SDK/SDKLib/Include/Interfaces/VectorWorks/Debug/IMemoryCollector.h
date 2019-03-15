//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Debug
	{
		// ----------------------------------------------------------------------------------------
		enum EMemoryType
		{
			eMemoryType_Unknown,
			eMemoryType_VectorWorks,
			eMemoryType_DLL,
			eMemoryType_Special
		};

		// ----------------------------------------------------------------------------------------
		// {FABA8016-9E47-4796-A60E-122ABBBA76A4}
		static const VWIID IID_MemoryCollector	= { 0xFABA8016, 0x9E47, 0x4796, { 0xA6, 0x0E, 0x12, 0x2A, 0xBB, 0xBA, 0x76, 0xA4 } };
		class DYNAMIC_ATTRIBUTE IMemoryCollector : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE RegisterMemory(EMemoryType type, void* pMemory, size_t size, const TXString& fileName, size_t fileLine) = 0;
			virtual VCOMError VCOM_CALLTYPE UnRegisterMemory(EMemoryType type, void* pMemory) = 0;
			virtual VCOMError VCOM_CALLTYPE VerifyPointer(EMemoryType type, void* pMemory, size_t size, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE GetMemoryMarker(void* pMemory, TXString& outMarker) = 0;
			virtual VCOMError VCOM_CALLTYPE SetMemoryMarker(void* pMemory, const TXString& marker) = 0;
			virtual VCOMError VCOM_CALLTYPE ReportMemory(const TXString& moduleName) = 0;
		};
	}
}