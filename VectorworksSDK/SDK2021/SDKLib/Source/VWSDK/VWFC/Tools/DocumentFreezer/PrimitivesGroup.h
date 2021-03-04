//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Primitive.h"

namespace VWFC
{
	namespace Tools
	{
		namespace DocumentFreezer
		{
			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveGroup : public CPrimitive
			{
			public:
						CPrimitiveGroup(MCObjectHandle h);
				virtual ~CPrimitiveGroup();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
			};

			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveLayer : public CPrimitiveGroup
			{
			public:
						CPrimitiveLayer(MCObjectHandle h);
				virtual ~CPrimitiveLayer();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			private:
				TXString		fName;
				ELayerType		fType;
			};
			
			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveSymbolFolder : public CPrimitiveGroup
			{
			public:
						CPrimitiveSymbolFolder(MCObjectHandle h);
				virtual ~CPrimitiveSymbolFolder();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			private:
				TXString			fName;
			};
			
			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveAUXData : public CPrimitiveGroup
			{
			public:
						CPrimitiveAUXData(MCObjectHandle h);
				virtual ~CPrimitiveAUXData();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);
			};

			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveSymbolDef : public CPrimitiveGroup
			{
			public:
						CPrimitiveSymbolDef(MCObjectHandle h);
				virtual ~CPrimitiveSymbolDef();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
				TXString				fName;
				ESymbolDefType			fType;
				ESymbolInsertMode		fInsertMode;
				ESymbolBreakMode		fBreakMode;
				bool					fInsertAsGroup;
			};

			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveParametric : public CPrimitiveGroup
			{
			public:
						CPrimitiveParametric(MCObjectHandle h);
				virtual ~CPrimitiveParametric();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			private:
				TXString			fName;
				VWTransformMatrix	fTransform;
			};
		}
	}
}
