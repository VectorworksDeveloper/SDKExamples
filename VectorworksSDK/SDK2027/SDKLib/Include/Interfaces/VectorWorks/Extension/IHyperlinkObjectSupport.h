//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// --------------------------------------------------------------------------------------------------		
		// {63ada918-0764-4778-80ee-a08daa6933fa}
		static const VWIID IID_VCOMHyperlink = { 0xea97555f, 0xb3ae, 0x4a09, {0xb0, 0xc2, 0xff, 0x6b, 0x5d, 0xea, 0xb1, 0x72}};


		class IHyperlinkObjectSupport : public IVWSingletonUnknown
		{
			public:
			virtual MCObjectHandle VCOM_CALLTYPE CreateHyperlink(const TXString HyperlinkName, const TXString path, const TXString SymDefName, const WorldPt& position) = 0;
		};
		
		// ---------------------------------------------------------------------------
		typedef VCOMPtr<IHyperlinkObjectSupport>	IHyperlinkObjectSupportPtr;
	}
}
