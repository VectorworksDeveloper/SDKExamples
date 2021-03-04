//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2020 www.deersoft.de
//-----------------------------------------------------------------------------

#pragma once

namespace VectorWorks
{
	namespace TrussAnalysis
	{
		using LocalicedStringArray = std::vector<std::pair< TXString, TXString> >;  // <NativeStr, LocalicedStr >

		class DYNAMIC_ATTRIBUTE ICableInterface : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	GetConnectors(LocalicedStringArray& outArray) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetConnector_NativeName(const TXString & locNam, TXString& out_NativeNam) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetConnector_Localiced (const TXString & nativeNam, TXString& out_LocNam) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetConnectorAdapters(LocalicedStringArray& outArray) = 0;
		};

		typedef VCOMPtr<ICableInterface>	ICableInterfacePtr;
		const VWIID IID_ICableInterface = { 0x8c604dc2, 0x4355, 0x43a3, {0x9c, 0x76, 0x37, 0xff, 0x84, 0x1b, 0x0b, 0x8d} };
	}
} // Namespace
