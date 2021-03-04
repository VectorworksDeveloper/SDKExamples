//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "Primitive.h"

#include "Primitives2D.h"
#include "Primitives3D.h"
#include "PrimitivesGroup.h"

using namespace VectorWorks::Filing;
using namespace VWFC::Tools;
using namespace VWFC::Tools::DocumentFreezer;

CPrimitive::CPrimitive(MCObjectHandle h)
	: fObject( h )
{
	InternalIndex classIndex = gSDK->GetObjectClass( fObject );
	if ( gSDK->ValidClass( classIndex ) )
	{
		gSDK->ClassIDToName( classIndex, fClassName );
	}

	VWObjectAttr	attr( fObject );

	fClrPenBack		= attr.GetPenBackColor();
	fClrPenFore		= attr.GetPenForeColor();
	fPenByClass		= attr.GetPenColorByClass();
	fClrFillBack	= attr.GetFillBackColor();
	fClrFillFore	= attr.GetFillForeColor();
	fFillByClass	= attr.GetFillColorByClass();

	for(TexturePartSDK texturePartID = kTexturePart_Overall;
		texturePartID < kTexturePart_Maximum;
		texturePartID = (TexturePartSDK) (texturePartID + 1))
	{
		InternalIndex textureIndex = gSDK->GetTextureRef( fObject, texturePartID, false );
		if ( textureIndex )
		{
			STextureInfo	textureInfo;
			textureInfo.fPartID		= texturePartID;
			gSDK->InternalIndexToNameN( textureIndex, textureInfo.fName );
			if ( ! textureInfo.fName.IsEmpty() )
			{
				textureInfo.fMapping	= gSDK->GetTextureMappingInfo( fObject, texturePartID );

				farrTextureMapping.push_back( textureInfo );
			}
		}
	}
}

CPrimitive::~CPrimitive()
{
}

void CPrimitive::FreezeAUX(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "AUX:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		MCObjectHandle firstAUX = gSDK->FirstAuxObject( fObject );
		if ( firstAUX )
		{
			this->FreezeChildList( outputFile, version, firstAUX );
		}
	}

	outputFile->Write( "AUX:E", true ); // end marker
}

void CPrimitive::FreezeClass(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Cls:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		outputFile->Write( fClassName, true );
	}

	outputFile->Write( "Cls:E", true ); // end marker
}

void CPrimitive::FreezeAttributes(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Att:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		outputFile->Write( fClrPenBack.GetRed() );
		outputFile->Write( fClrPenBack.GetGreen() );
		outputFile->Write( fClrPenBack.GetBlue() );
		outputFile->Write( fClrPenFore.GetRed() );
		outputFile->Write( fClrPenFore.GetGreen() );
		outputFile->Write( fClrPenFore.GetBlue() );

		outputFile->Write( Uint8(fPenByClass) );

		outputFile->Write( fClrFillBack.GetRed() );
		outputFile->Write( fClrFillBack.GetGreen() );
		outputFile->Write( fClrFillBack.GetBlue() );
		outputFile->Write( fClrFillFore.GetRed() );
		outputFile->Write( fClrFillFore.GetGreen() );
		outputFile->Write( fClrFillFore.GetBlue() );

		outputFile->Write( Uint8(fFillByClass) );
	}

	outputFile->Write( "Att:E", true ); // end marker
}

void CPrimitive::FreezeTextureAttrbs(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "TAt:B", true ); // begin marker
	if ( version <= eDocumentFreezerVersion_1 )
	{
		size_t	texturePartsCnt = farrTextureMapping.size();
		outputFile->Write( (Uint64) texturePartsCnt );

		for(size_t i=0; i<texturePartsCnt; ++i)
		{
			const STextureInfo&	textureInfo	= farrTextureMapping[ i ];

			outputFile->Write( Uint32(textureInfo.fPartID) );
			outputFile->Write( Uint8(textureInfo.fMapping.fInitialized) );
			outputFile->Write( Uint32(textureInfo.fMapping.fParamSpaceKind) );
			outputFile->Write( textureInfo.fName, true );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.a00 );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.a01 );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.a02 );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.a10 );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.a11 );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.a12 );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.a20 );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.a21 );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.a22 );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.xOff );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.yOff );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fOriginOrient.v1.zOff );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.f2DOffset.x );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.f2DOffset.y );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.f2DScale );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.f2DRotation );
			outputFile->Write( sizeof(double), & textureInfo.fMapping.fRadius );
			outputFile->Write( Uint8(textureInfo.fMapping.fFlipTexture) );
			outputFile->Write( Uint8(textureInfo.fMapping.fRepeatH) );
			outputFile->Write( Uint8(textureInfo.fMapping.fRepeatV) );
			outputFile->Write( Uint8(textureInfo.fMapping.fUseWorldZ) );
			outputFile->Write( Uint8(textureInfo.fMapping.fAutoAlignPlanar) );
			outputFile->Write( Uint8(textureInfo.fMapping.fAutoAlignPlanarLongestEdge) );
		}
	}

	outputFile->Write( "TAt:E", true ); // end marker
}

void CPrimitive::FreezeChildList(IStdFile* outputFile, EDocumentFreezerVersion version, MCObjectHandle hFirstInList)
{
	if ( hFirstInList == nullptr )
		hFirstInList = gSDK->FirstMemberObj( fObject );

	for(MCObjectHandle hObject = hFirstInList;
		hObject;
		hObject = gSDK->NextObject( hObject ))
	{
		if ( version <= eDocumentFreezerVersion_1 )
		{
			short type = gSDK->GetObjectTypeN( hObject );
			if ( VWLocus2DObj::IsLocus2DObject( hObject ) )
			{
				CPrimitiveLocus2D	primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWLine2DObj::IsLine2DObject( hObject ) )
			{
				CPrimitiveLine	primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWGroupObj::IsGroupObject( hObject ) )
			{
				CPrimitiveGroup	primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWPolygon3DObj::IsPolygon3DObject( hObject ) )
			{
				CPrimitivePolygon3D	primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWMeshObj::IsMeshObject( hObject ) )
			{
				CPrimitiveMesh	primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWPolygon2DObj::IsPolygon2DObject( hObject ) )
			{
				CPrimitivePolygon2D	primitive( hObject, false );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWPolygon2DObj::IsPolyline2DObject( hObject ) )
			{
				CPrimitivePolygon2D	primitive( hObject, true );
				primitive.Freeze( outputFile, version );
			}
			else if ( type == kFolderNode )
			{
				CPrimitiveSymbolFolder	primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWParametricObj::IsParametricObject( hObject ) )
			{
				CPrimitiveParametric primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWRecordFormatObj::IsRecordFormatObject( hObject ) )
			{
				CPrimitiveFormat primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWRecordObj::IsRecordObject( hObject ) )
			{
				CPrimitiveRecord primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWSymbolDefObj::IsSymbolDefObject( hObject ) )
			{
				CPrimitiveSymbolDef primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
			else if ( VWSymbolObj::IsSymbolObject( hObject ) )
			{
				CPrimitiveSymbol primitive( hObject );
				primitive.Freeze( outputFile, version );
			}
		}
	}
}

bool CPrimitive::AssertFrozenAUX(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "AUX:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		MCObjectHandle firstAUX = gSDK->FirstAuxObject( fObject );
		if ( firstAUX )
		{
			result = result && this->AssertFrozenChildList( inputFile, version, asserter, firstAUX );
		}
	}

	result = result && this->AssertFrozenTag( inputFile, "AUX:E", asserter, __FILE__, __LINE__ );

	return result;
}

bool CPrimitive::AssertFrozenTag(IStdFile* inputFile, const char* tag, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line)
{
	bool result = false;

	TXString	strTag;
	if ( VCOM_SUCCEEDED( inputFile->Read( strTag ) ) )
	{
		result = ( strTag.EqualNoCase( tag )  );

		if ( asserter && ! result )
		{
			TXString msg;
			msg.Format( "Unexpected tag found '%s' while looking for '%s'", strTag, tag );
			asserter->AddFail( msg, szFile, line );
		}
	}

	return result;
}

bool CPrimitive::AssertFrozenValue(IStdFile* inputFile, bool value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line)
{
	Uint8 inputValue = 0;
	inputFile->Read( inputValue );

	bool result = inputValue == value;
	if ( asserter && ! result )
	{
		TXString msg;
		msg.Format( "Unexpected value %s when it should be %s for variable '%s'", (inputValue?"TRUE":"FALSE"), (value?"TRUE":"FALSE"), valueName );
		asserter->AddFail( msg, szFile, line );
	}

	return result;
}

bool CPrimitive::AssertFrozenValue(IStdFile* inputFile, double value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line)
{
	double inputValue = 0;
	Uint64 bytes = sizeof(double);
	inputFile->Read( bytes, &inputValue );

	Boolean result = DoublesAreNearlyEqual( inputValue, value, kNearlyEqualEpsilonForNormalizedValues );
	if ( asserter && ! result )
	{
		TXString msg;
		msg.Format( "Unexpected value %f when it should be %f for variable '%s'", inputValue, value, valueName );
		asserter->AddFail( msg, szFile, line );
	}

	return result;
}

bool CPrimitive::AssertFrozenValue(IStdFile* inputFile, const TXString& value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line)
{
	TXString inputValue;
	inputFile->Read( inputValue );

	bool result = inputValue == value;
	if ( asserter && ! result )
	{
		TXString msg;
		msg.Format( "Unexpected value '%s' when it should be '%s' for variable '%s'", inputValue, value, valueName );
		asserter->AddFail( msg, szFile, line );
	}

	return result;
}

bool CPrimitive::AssertFrozenValue(IStdFile* inputFile, const CRGBColor& value, const char* valueName, IDocumentFreezerAsserter* asserter, const char* szFile, size_t line)
{
	Uint8	clrR, clrG, clrB;
	inputFile->Read( clrR );
	inputFile->Read( clrG );
	inputFile->Read( clrB );

	bool result = (clrR == value.GetRed()) && (clrG == value.GetGreen()) && (clrB == value.GetBlue());
	if ( asserter && ! result )
	{
		TXString msg;
		msg.Format( "Unexpected color (%d,%d,%d) when it should be (%d,%d,%d) for variable '%s'", clrR, clrG, clrB, value.GetRed(), value.GetGreen(), value.GetBlue(), valueName );
		asserter->AddFail( msg, szFile, line );
	}

	return result;
}

bool CPrimitive::AssertFrozenClass(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Cls:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && this->AssertFrozenValue( inputFile, fClassName, "fClassName", asserter, __FILE__, __LINE__ );
	}

	result = result && this->AssertFrozenTag( inputFile, "Cls:E", asserter, __FILE__, __LINE__ );

	return result;
}

bool CPrimitive::AssertFrozenAttributes(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Att:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && this->AssertFrozenValue( inputFile, fClrPenBack, "fClrPenBack", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, fClrPenFore, "fClrPenFore", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, fPenByClass, "fPenByClass", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, fClrFillBack, "fClrFillBack", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, fClrFillFore, "fClrFillFore", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, fFillByClass, "fFillByClass", asserter, __FILE__, __LINE__ );
	}

	result = result && this->AssertFrozenTag( inputFile, "Att:E", asserter, __FILE__, __LINE__ );

	return result;
}

bool CPrimitive::AssertFrozenTextureAttrbs(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "TAt:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		Uint64	inputCnt;
		inputFile->Read( inputCnt );


		size_t	texturePartsCnt = farrTextureMapping.size();
		result = ( texturePartsCnt == inputCnt );

		if ( result )
		{
			for(size_t i=0; result && i<texturePartsCnt; ++i)
			{
				const STextureInfo&	textureInfo	= farrTextureMapping[ i ];

				result = result && this->AssertFrozenValue<Uint32>( inputFile, textureInfo.fPartID, "textureInfo.fPartID", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue<Uint8>( inputFile, textureInfo.fMapping.fInitialized, "textureInfo.fMapping.fInitialized", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue<Uint32>( inputFile, textureInfo.fMapping.fParamSpaceKind, "textureInfo.fMapping.fParamSpaceKind", asserter, __FILE__, __LINE__ );

				result = result && this->AssertFrozenValue( inputFile, textureInfo.fName, "textureInfo.fName", asserter, __FILE__, __LINE__ );

				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.a00 , "textureInfo.fMapping.fOriginOrient.v1.a00 ", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.a01 , "textureInfo.fMapping.fOriginOrient.v1.a01 ", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.a02 , "textureInfo.fMapping.fOriginOrient.v1.a02 ", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.a10 , "textureInfo.fMapping.fOriginOrient.v1.a10 ", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.a11 , "textureInfo.fMapping.fOriginOrient.v1.a11 ", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.a12 , "textureInfo.fMapping.fOriginOrient.v1.a12 ", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.a20 , "textureInfo.fMapping.fOriginOrient.v1.a20 ", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.a21 , "textureInfo.fMapping.fOriginOrient.v1.a21 ", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.a22 , "textureInfo.fMapping.fOriginOrient.v1.a22 ", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.xOff, "textureInfo.fMapping.fOriginOrient.v1.xOff", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.yOff, "textureInfo.fMapping.fOriginOrient.v1.yOff", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fOriginOrient.v1.zOff, "textureInfo.fMapping.fOriginOrient.v1.zOff", asserter, __FILE__, __LINE__ );

				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.f2DOffset.x,	"textureInfo.fMapping.f2DOffset.x", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.f2DOffset.y,	"textureInfo.fMapping.f2DOffset.y", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.f2DScale,		"textureInfo.fMapping.f2DScale",	asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.f2DRotation,	"textureInfo.fMapping.f2DRotation", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fRadius,		"textureInfo.fMapping.fRadius",		asserter, __FILE__, __LINE__ );

				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fFlipTexture,	"textureInfo.fMapping.fFlipTexture",	asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fRepeatH,		"textureInfo.fMapping.fRepeatH",		asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fRepeatV,		"textureInfo.fMapping.fRepeatV",		asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fUseWorldZ,		"textureInfo.fMapping.fUseWorldZ",		asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fAutoAlignPlanar,		"textureInfo.fMapping.fAutoAlignPlanar",		asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue( inputFile, textureInfo.fMapping.fAutoAlignPlanarLongestEdge,		"textureInfo.fMapping.fAutoAlignPlanarLongestEdge",		asserter, __FILE__, __LINE__ );
			}
		}
		else if ( asserter )
			{
				asserter->AddFail( "Texture attributes count doesn't match", __FILE__, __LINE__ );
			}
	}

	result = result && this->AssertFrozenTag( inputFile, "TAt:E", asserter, __FILE__, __LINE__ );

	return result;
}

bool CPrimitive::AssertFrozenChildList(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter, MCObjectHandle hFirstInList)
{
	if ( hFirstInList == nullptr )
		hFirstInList = gSDK->FirstMemberObj( fObject );

	bool result = true;
	for(MCObjectHandle hObject = hFirstInList;
		hObject && result;
		hObject = gSDK->NextObject( hObject ))
	{
		if ( version <= eDocumentFreezerVersion_1 )
		{
			if ( VWLocus2DObj::IsLocus2DObject( hObject ) )
			{
				CPrimitiveLocus2D	primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWLine2DObj::IsLine2DObject( hObject ) )
			{
				CPrimitiveLine	primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWGroupObj::IsGroupObject( hObject ) )
			{
				CPrimitiveGroup	primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWPolygon3DObj::IsPolygon3DObject( hObject ) )
			{
				CPrimitivePolygon3D	primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWMeshObj::IsMeshObject( hObject ) )
			{
				CPrimitiveMesh	primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWPolygon2DObj::IsPolygon2DObject( hObject ) )
			{
				CPrimitivePolygon2D	primitive( hObject, false );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWPolygon2DObj::IsPolyline2DObject( hObject ) )
			{
				CPrimitivePolygon2D	primitive( hObject, true );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWParametricObj::IsParametricObject( hObject ) )
			{
				CPrimitiveParametric primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWRecordFormatObj::IsRecordFormatObject( hObject ) )
			{
				CPrimitiveFormat primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWRecordObj::IsRecordObject( hObject ) )
			{
				CPrimitiveRecord primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWSymbolDefObj::IsSymbolDefObject( hObject ) )
			{
				CPrimitiveSymbolDef primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
			else if ( VWSymbolObj::IsSymbolObject( hObject ) )
			{
				CPrimitiveSymbol primitive( hObject );
				result = primitive.AssertFrozen( inputFile, version, asserter );
			}
		}
	}

	return result;
}

