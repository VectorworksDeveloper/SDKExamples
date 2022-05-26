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
			class CPrimitivePolygon3D : public CPrimitive
			{
			public:
						CPrimitivePolygon3D(MCObjectHandle h);
				virtual ~CPrimitivePolygon3D();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
				VWPolygon3D		fPoly3D;
			};

			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveMesh : public CPrimitive
			{
			public:
						CPrimitiveMesh(MCObjectHandle h);
				virtual ~CPrimitiveMesh();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
			};

			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveSymbol : public CPrimitive
			{
			public:
						CPrimitiveSymbol(MCObjectHandle h);
				virtual ~CPrimitiveSymbol();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
				TXString			fSymbolDefName;
				VWTransformMatrix	fTransform;
			};
		}
	}
}
