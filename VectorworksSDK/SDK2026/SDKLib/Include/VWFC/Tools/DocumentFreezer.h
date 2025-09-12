#pragma once

namespace VWFC
{
	namespace Tools
	{
		// ------------------------------------------------------------------------------------------------------------------------------------
		enum EDocumentFreezerVersion
		{
			eDocumentFreezerVersion_1,

			eDocumentFreezerVersion_MaxVersion
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		class IDocumentFreezerAsserter
		{
		public:
			virtual ~IDocumentFreezerAsserter() {}
			virtual void AddFail(const TXString& message, const char* szFile, size_t line) = 0;
			virtual void AddMessage(const TXString& message, const char* szFile, size_t line) = 0;
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		class CDocumentFreezer
		{
		public:
					CDocumentFreezer();
			virtual ~CDocumentFreezer();

		public:
			void	Freeze(VectorWorks::Filing::IFileIdentifier* outputFileID, EDocumentFreezerVersion version = eDocumentFreezerVersion_MaxVersion);
			bool	AssertFrozen(VectorWorks::Filing::IFileIdentifier* inputFileID, EDocumentFreezerVersion& outVersion, IDocumentFreezerAsserter* asserter = NULL);
		};
	}
}