#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		// {DEB707BF-D7A1-4F3E-86D4-C7C761B108A1}
		static const VWIID IID_IImportAsSymbol = { 0xdeb707bf, 0xd7a1, 0x4f3e, { 0x86, 0xd4, 0xc7, 0xc7, 0x61, 0xb1, 0x8, 0xa1 } };

		class DYNAMIC_ATTRIBUTE IImportAsSymbol : public IVWSingletonUnknown
		{
		public:
			virtual bool VCOM_CALLTYPE FinishCreateSymbol(const IFileIdentifierPtr& file) const = 0;
		};

		typedef VCOMPtr<IImportAsSymbol>	IImportAsSymbolPtr;
	}
}