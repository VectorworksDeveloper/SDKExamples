//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		namespace DocumentFreezer
		{
			class CPrimitive
			{
			public:
						CPrimitive(MCObjectHandle h);
				virtual ~CPrimitive();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version) = 0;
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter) = 0;

			protected:
				virtual void	FreezeAUX(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual void	FreezeClass(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual void	FreezeAttributes(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual void	FreezeTextureAttrbs(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual void	FreezeChildList(IStdFile* outputFile, EDocumentFreezerVersion version, MCObjectHandle hFirstInList=NULL);

			protected:
				virtual bool	AssertFrozenAUX(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);
				virtual bool	AssertFrozenTag(IStdFile* inputFile, const char* tag, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line);
				virtual bool	AssertFrozenClass(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);
				virtual bool	AssertFrozenAttributes(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);
				virtual bool	AssertFrozenTextureAttrbs(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);
				virtual bool	AssertFrozenChildList(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter, MCObjectHandle hFirstInList=NULL);

			// helper functions
			protected:
				template <class T>	
				bool	AssertFrozenValue(IStdFile* inputFile, T value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line);
				bool	AssertFrozenValue(IStdFile* inputFile, bool value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line);
				bool	AssertFrozenValue(IStdFile* inputFile, double value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line);
				bool	AssertFrozenValue(IStdFile* inputFile, const TXString& value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line);
				bool	AssertFrozenValue(IStdFile* inputFile, const CRGBColor& value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line);

			protected:
				MCObjectHandle		fObject;

				TXString		fClassName;
				CRGBColor		fClrPenBack;
				CRGBColor		fClrPenFore;
				bool			fPenByClass;
				CRGBColor		fClrFillBack;
				CRGBColor		fClrFillFore;
				bool			fFillByClass;

				struct STextureInfo
				{
					TexturePartSDK			fPartID;
					TXString				fName;
					TextureMappingInfoSDK	fMapping;
				};

				std::vector<STextureInfo> farrTextureMapping;
			};
		}
	}
}

namespace VWFC
{
	namespace Tools
	{
		namespace DocumentFreezer
		{
			template <class T>bool CPrimitive::AssertFrozenValue(IStdFile* inputFile, T value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line)
			{
				T inputValue = 0;
				inputFile->Read( inputValue );

				bool result = inputValue == value;
				if ( asserter && ! result )
				{
					TXString msg;
					msg.Format( "Unexpected value %d when it should be %d for variable '%s'", inputValue, value, valueName );
					asserter->AddFail( msg, szFile, line );
				}

				return result;
			}
		}
	}
}