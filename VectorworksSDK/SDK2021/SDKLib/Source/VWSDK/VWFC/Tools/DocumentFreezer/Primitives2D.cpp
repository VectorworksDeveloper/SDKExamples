//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "Primitives2D.h"

using namespace VectorWorks::Filing;
using namespace VWFC::Tools;
using namespace VWFC::Tools::DocumentFreezer;

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveLocus2D::CPrimitiveLocus2D(MCObjectHandle h)
	: CPrimitive( h )
{
	VWLocus2DObj	obj( fObject );
	fPt	= obj.GetPoint();
}

CPrimitiveLocus2D::~CPrimitiveLocus2D()
{
}

void CPrimitiveLocus2D::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Lc2D:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );
		CPrimitive::FreezeClass( outputFile, version );
		CPrimitive::FreezeAttributes( outputFile, version );

		outputFile->Write( sizeof(double), & fPt.x );
		outputFile->Write( sizeof(double), & fPt.y );
	}

	outputFile->Write( "Lc2D:E", true ); // end marker
}

bool CPrimitiveLocus2D::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Lc2D:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenClass( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenAttributes( inputFile, version, asserter );

		result = result && this->AssertFrozenValue( inputFile, fPt.x, "fPt.x", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, fPt.y, "fPt.y", asserter, __FILE__, __LINE__ );
	}

	result = result && this->AssertFrozenTag( inputFile, "Lc2D:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveLine::CPrimitiveLine(MCObjectHandle h)
	: CPrimitive( h )
{
	VWLine2DObj	obj( fObject );
	obj.GetLine( fPt1, fPt2 );
}

CPrimitiveLine::~CPrimitiveLine()
{
}

void CPrimitiveLine::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Ln2D:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );
		CPrimitive::FreezeClass( outputFile, version );
		CPrimitive::FreezeAttributes( outputFile, version );

		outputFile->Write( sizeof(double), & fPt1.x );
		outputFile->Write( sizeof(double), & fPt1.y );
		outputFile->Write( sizeof(double), & fPt2.x );
		outputFile->Write( sizeof(double), & fPt2.y );
	}

	outputFile->Write( "Ln2D:E", true ); // end marker
}

bool CPrimitiveLine::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Ln2D:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenClass( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenAttributes( inputFile, version, asserter );

		result = result && this->AssertFrozenValue( inputFile, fPt1.x, "fPt1.x", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, fPt1.y, "fPt1.y", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, fPt2.x, "fPt2.x", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, fPt2.y, "fPt2.y", asserter, __FILE__, __LINE__ );
	}

	result = result && this->AssertFrozenTag( inputFile, "Ln2D:E", asserter, __FILE__, __LINE__ );

	return result;
}


// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitivePolygon2D::CPrimitivePolygon2D(MCObjectHandle h, bool isPolyline)
	: CPrimitive( h )
	, fIsPolyline( isPolyline )
{
	VWPolygon2DObj	obj( fObject );
	obj.GetPolygon( fPoly2D );
}

CPrimitivePolygon2D::~CPrimitivePolygon2D()
{
}

void CPrimitivePolygon2D::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Pl2D:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );
		CPrimitive::FreezeClass( outputFile, version );
		CPrimitive::FreezeAttributes( outputFile, version );

		outputFile->Write( Uint8(fIsPolyline) );
		outputFile->Write( Uint8(fPoly2D.IsClosed()) );

		size_t	vertexCnt = fPoly2D.GetVertexCount();
		outputFile->Write( (Uint64) vertexCnt );

		for(size_t i=0; i<vertexCnt; ++i)
		{
			const VWPoint2D&	vertexPt = fPoly2D.GetVertexAt( i );

			outputFile->Write( sizeof(double), & vertexPt.x );
			outputFile->Write( sizeof(double), & vertexPt.y );

			if ( fIsPolyline )
			{
				EVertexType			vertexType = fPoly2D.GetVertexType( i );
				bool				vertexVisible = fPoly2D.GetVertexVisible( i );

				outputFile->Write( Uint16(vertexType) );
				outputFile->Write( Uint8(vertexVisible) );
			}
		}
	}

	outputFile->Write( "Pl2D:E", true ); // end marker
}

bool CPrimitivePolygon2D::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Pl2D:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenClass( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenAttributes( inputFile, version, asserter );

		result = result && this->AssertFrozenValue<Uint8>( inputFile, fIsPolyline, "fIsPolyline", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue<Uint8>( inputFile, fPoly2D.IsClosed(), "fPoly2D.IsClosed()", asserter, __FILE__, __LINE__ );

		if ( result )
		{
			Uint64	inputCnt;
			inputFile->Read( inputCnt );

			size_t	vertexCnt = fPoly2D.GetVertexCount();
			result = ( vertexCnt == inputCnt );

			if ( result )
			{
				for(size_t i=0; i<vertexCnt && result; ++i)
				{
					const VWPoint2D&	vertexPt = fPoly2D.GetVertexAt( i );

					result = result && this->AssertFrozenValue( inputFile, vertexPt.x, "vertexPt.x", asserter, __FILE__, __LINE__ );
					result = result && this->AssertFrozenValue( inputFile, vertexPt.y, "vertexPt.y", asserter, __FILE__, __LINE__ );

					if ( fIsPolyline )
					{
						EVertexType			vertexType = fPoly2D.GetVertexType( i );
						bool				vertexVisible = fPoly2D.GetVertexVisible( i );

						result = result && this->AssertFrozenValue<Uint16>( inputFile, vertexType, "vertexType", asserter, __FILE__, __LINE__ );
						result = result && this->AssertFrozenValue<Uint8>( inputFile, vertexVisible, "vertexVisible", asserter, __FILE__, __LINE__ );
					}
				}
			}
			else if ( asserter )
			{
				asserter->AddFail( "Poly line vertex count doesn't match", __FILE__, __LINE__ );
			}
		}
	}

	result = result && this->AssertFrozenTag( inputFile, "Pl2D:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveFormat::CPrimitiveFormat(MCObjectHandle h)
	: CPrimitive( h )
{
	VWRecordFormatObj	formatObj( h );
	fName			= formatObj.GetFormatName();
	fIsParametric	= formatObj.IsParametric();
	fIsVisible		= formatObj.GetFormatVisibility();

	size_t paramsCnt = formatObj.GetParamsCount();
	for(size_t i=0; i<paramsCnt; ++i)
	{
		const TXString& paramName	= formatObj.GetParamName( i );
		const TXString& paramValue	= formatObj.GetParamValue( i );

		fmapParamName2Value.insert( TName2ValueMap::value_type( paramName, paramValue ) );
	}
}

CPrimitiveFormat::~CPrimitiveFormat()
{
}

void CPrimitiveFormat::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Form:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		outputFile->Write( fName, true );
		outputFile->Write( Uint8(fIsParametric) );
		outputFile->Write( Uint8(fIsVisible) );

		outputFile->Write( (Uint64) fmapParamName2Value.size() );

		for(auto it=fmapParamName2Value.begin(); it != fmapParamName2Value.end(); ++it)
		{
			const TXString& paramName	= it->first;
			const TXString& paramValue	= it->second;

			outputFile->Write( paramName, true );
			outputFile->Write( paramValue, true );
		}
	}

	outputFile->Write( "Form:E", true ); // end marker
}

bool CPrimitiveFormat::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Form:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && this->AssertFrozenValue( inputFile, fName, "fName", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue<Uint8>( inputFile, fIsParametric, "fIsParametric", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue<Uint8>( inputFile, fIsVisible, "fIsVisible", asserter, __FILE__, __LINE__ );

		if ( result )
		{
			Uint64	inputCnt;
			inputFile->Read( inputCnt );

			size_t	paramsCnt = fmapParamName2Value.size();
			result = ( paramsCnt == inputCnt );

			if ( result )
			{
				for(auto it=fmapParamName2Value.begin(); it != fmapParamName2Value.end() && result; ++it)
				{
					const TXString& paramName	= it->first;
					const TXString& paramValue	= it->second;

					result = result && this->AssertFrozenValue( inputFile, paramName, "paramName", asserter, __FILE__, __LINE__ );
					result = result && this->AssertFrozenValue( inputFile, paramValue, "paramValue", asserter, __FILE__, __LINE__ );
				}
			}
			else if ( asserter )
			{
				asserter->AddFail( "Format parameters count doesn't match", __FILE__, __LINE__ );
			}
		}
	}

	result = result && this->AssertFrozenTag( inputFile, "Form:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveRecord::CPrimitiveRecord(MCObjectHandle h)
	: CPrimitive( h )
{
	VWRecordObj	recordObj( fObject );
	fRecordName		= recordObj.GetRecordName();
	fIsParametric	= recordObj.IsParametric();

	size_t paramsCnt = recordObj.GetParamsCount();
	for(size_t i=0; i<paramsCnt; ++i)
	{
		const TXString& paramName	= recordObj.GetParamName( i );
		const TXString& paramValue	= recordObj.GetParamValue( i );

		fmapParamName2Value.insert( TName2ValueMap::value_type( paramName, paramValue ) );
	}
}

CPrimitiveRecord::~CPrimitiveRecord()
{
}

void CPrimitiveRecord::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Rec:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		outputFile->Write( fRecordName, true );
		outputFile->Write( Uint8(fIsParametric) );

		outputFile->Write( (Uint64) fmapParamName2Value.size() );

		for(auto it=fmapParamName2Value.begin(); it != fmapParamName2Value.end(); ++it)
		{
			const TXString& paramName	= it->first;
			const TXString& paramValue	= it->second;

			outputFile->Write( paramName, true );
			outputFile->Write( paramValue, true );
		}
	}

	outputFile->Write( "Rec:E", true ); // end marker
}

bool CPrimitiveRecord::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Rec:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && this->AssertFrozenValue( inputFile, fRecordName, "fRecordName", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue<Uint8>( inputFile, fIsParametric, "fIsParametric", asserter, __FILE__, __LINE__ );

		if ( result )
		{
			Uint64	inputCnt;
			inputFile->Read( inputCnt );

			size_t	paramsCnt = fmapParamName2Value.size();
			result = ( paramsCnt == inputCnt );

			if ( result )
			{
				for(auto it=fmapParamName2Value.begin(); it != fmapParamName2Value.end() && result; ++it)
				{
					const TXString& paramName	= it->first;
					const TXString& paramValue	= it->second;

					result = result && this->AssertFrozenValue( inputFile, paramName, "paramName", asserter, __FILE__, __LINE__ );
					result = result && this->AssertFrozenValue( inputFile, paramValue, "paramValue", asserter, __FILE__, __LINE__ );
				}
			}
			else if ( asserter )
			{
				asserter->AddFail( "Record parameters count doesn't match", __FILE__, __LINE__ );
			}
		}
	}

	result = result && this->AssertFrozenTag( inputFile, "Rec:E", asserter, __FILE__, __LINE__ );

	return result;
}
