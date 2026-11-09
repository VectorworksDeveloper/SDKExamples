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
			class CPrimitiveLocus2D : public CPrimitive
			{
			public:
						CPrimitiveLocus2D(MCObjectHandle h);
				virtual ~CPrimitiveLocus2D();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
				VWPoint2D	fPt;
			};

			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveLine : public CPrimitive
			{
			public:
						CPrimitiveLine(MCObjectHandle h);
				virtual ~CPrimitiveLine();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
				VWPoint2D	fPt1;
				VWPoint2D	fPt2;
			};

			// ------------------------------------------------------------------------------------------------------
			class CPrimitivePolygon2D : public CPrimitive
			{
			public:
						CPrimitivePolygon2D(MCObjectHandle h, bool isPolyline);
				virtual ~CPrimitivePolygon2D();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
				VWPolygon2D		fPoly2D;
				bool			fIsPolyline;
			};

			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveFormat : public CPrimitive
			{
			public:
						CPrimitiveFormat(MCObjectHandle h);
				virtual ~CPrimitiveFormat();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
				TXString	fName;
				bool		fIsParametric;
				bool		fIsVisible;

				typedef std::map<TXString, TXString>	TName2ValueMap;

				TName2ValueMap	fmapParamName2Value;
			};

			// ------------------------------------------------------------------------------------------------------
			class CPrimitiveRecord : public CPrimitive
			{
			public:
						CPrimitiveRecord(MCObjectHandle h);
				virtual ~CPrimitiveRecord();

			public:
				virtual void	Freeze(IStdFile* outputFile, EDocumentFreezerVersion version);
				virtual bool	AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter);

			protected:
				TXString	fRecordName;
				bool		fIsParametric;

				typedef std::map<TXString, TXString>	TName2ValueMap;

				TName2ValueMap	fmapParamName2Value;
			};
		}
	}
}
