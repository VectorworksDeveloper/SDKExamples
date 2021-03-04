//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "PrimitivesGroup.h"


using namespace VectorWorks::Filing;
using namespace VWFC::Tools;
using namespace VWFC::Tools::DocumentFreezer;

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveGroup::CPrimitiveGroup(MCObjectHandle h)
	: CPrimitive( h )
{
}

CPrimitiveGroup::~CPrimitiveGroup()
{
}

void CPrimitiveGroup::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Gr:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );

		this->FreezeChildList( outputFile, version );
	}

	outputFile->Write( "Gr:E", true ); // end marker
}

bool CPrimitiveGroup::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Gr:B", asserter, __FILE__, __LINE__ );

	result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );

	result = result && this->AssertFrozenChildList( inputFile, version, asserter );

	result = result && this->AssertFrozenTag( inputFile, "Gr:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveLayer::CPrimitiveLayer(MCObjectHandle h)
	: CPrimitiveGroup( h )
{
	VWLayerObj	obj( fObject );
	fName	= obj.GetName();
	fType	= obj.GetLayerType();
}

CPrimitiveLayer::~CPrimitiveLayer()
{
}

void CPrimitiveLayer::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Ly:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );

		outputFile->Write( fName, true );
		outputFile->Write( Uint16(fType) );
	}

	CPrimitiveGroup::FreezeChildList( outputFile, version );

	outputFile->Write( "Ly:E", true ); // end marker
}

bool CPrimitiveLayer::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Ly:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );

		result	= result && this->AssertFrozenValue( inputFile, fName, "fName", asserter, __FILE__, __LINE__ );
		result	= result && this->AssertFrozenValue<Uint16>( inputFile, fType, "fType", asserter, __FILE__, __LINE__ );
	}

	result = result && CPrimitiveGroup::AssertFrozenChildList( inputFile, version, asserter );

	result = result && this->AssertFrozenTag( inputFile, "Ly:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveSymbolFolder::CPrimitiveSymbolFolder(MCObjectHandle h)
	: CPrimitiveGroup( h )
{
	short type = gSDK->GetObjectTypeN( fObject );
	if ( type == kFolderNode )
	{
		gSDK->GetObjectName( fObject, fName );
	}
}

CPrimitiveSymbolFolder::~CPrimitiveSymbolFolder()
{
}

void CPrimitiveSymbolFolder::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "SymF:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		outputFile->Write( fName, true );
	}

	CPrimitiveGroup::FreezeChildList( outputFile, version );

	outputFile->Write( "SymF:E", true ); // end marker
}

bool CPrimitiveSymbolFolder::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "SymF:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result	= result && this->AssertFrozenValue( inputFile, fName, "fName", asserter, __FILE__, __LINE__ );
	}

	result = result && CPrimitiveGroup::AssertFrozenChildList( inputFile, version, asserter );

	result = result && this->AssertFrozenTag( inputFile, "SymF:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveAUXData::CPrimitiveAUXData(MCObjectHandle h)
	: CPrimitiveGroup( h )
{
}

CPrimitiveAUXData::~CPrimitiveAUXData()
{
}

void CPrimitiveAUXData::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "AUXD:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		;
	}

	CPrimitiveGroup::FreezeAUX( outputFile, version );
	CPrimitiveGroup::FreezeChildList( outputFile, version );

	outputFile->Write( "AUXD:E", true ); // end marker
}

bool CPrimitiveAUXData::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "AUXD:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		;
	}

	result = result && CPrimitiveGroup::AssertFrozenAUX( inputFile, version, asserter );
	result = result && CPrimitiveGroup::AssertFrozenChildList( inputFile, version, asserter );

	result = result && this->AssertFrozenTag( inputFile, "AUXD:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveSymbolDef::CPrimitiveSymbolDef(MCObjectHandle h)
	: CPrimitiveGroup( h )
{
	VWSymbolDefObj	symDefObj( fObject );

	gSDK->GetObjectName( fObject, fName );
	fType			= symDefObj.GetType();
	fInsertMode		= symDefObj.GetInsertMode();
	fBreakMode		= symDefObj.GetBreakMode();
	fInsertAsGroup	= symDefObj.GetInsertAsGroup();

}

CPrimitiveSymbolDef::~CPrimitiveSymbolDef()
{
}

void CPrimitiveSymbolDef::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "SDef:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );
		CPrimitive::FreezeClass( outputFile, version );
		CPrimitive::FreezeAttributes( outputFile, version );

		outputFile->Write( fName, true );
		outputFile->Write( Uint16(fType) );
		outputFile->Write( Uint16(fInsertMode) );
		outputFile->Write( Uint16(fBreakMode) );
		outputFile->Write( Uint8(fInsertAsGroup) );
	}

	CPrimitiveGroup::FreezeAUX( outputFile, version );
	CPrimitiveGroup::FreezeChildList( outputFile, version );

	outputFile->Write( "SDef:E", true ); // end marker
}

bool CPrimitiveSymbolDef::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "SDef:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenClass( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenAttributes( inputFile, version, asserter );

		result	= result && this->AssertFrozenValue( inputFile, fName, "fName", asserter, __FILE__, __LINE__ );
		result	= result && this->AssertFrozenValue<Uint16>( inputFile, fType, "fType", asserter, __FILE__, __LINE__ );
		result	= result && this->AssertFrozenValue<Uint16>( inputFile, fInsertMode, "fInsertMode", asserter, __FILE__, __LINE__ );
		result	= result && this->AssertFrozenValue<Uint16>( inputFile, fBreakMode, "fBreakMode", asserter, __FILE__, __LINE__ );
		result	= result && this->AssertFrozenValue<Uint8>( inputFile, fInsertAsGroup, "fInsertAsGroup", asserter, __FILE__, __LINE__ );
	}

	result = result && CPrimitiveGroup::AssertFrozenAUX( inputFile, version, asserter );
	result = result && CPrimitiveGroup::AssertFrozenChildList( inputFile, version, asserter );

	result = result && this->AssertFrozenTag( inputFile, "SDef:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveParametric::CPrimitiveParametric(MCObjectHandle h)
	: CPrimitiveGroup( h )
{
	VWParametricObj	paramObj( fObject );
	fName		= paramObj.GetParametricName();
	paramObj.GetObjectToWorldTransform( fTransform );
}

CPrimitiveParametric::~CPrimitiveParametric()
{
}

void CPrimitiveParametric::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Prm:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );
		CPrimitive::FreezeClass( outputFile, version );
		CPrimitive::FreezeAttributes( outputFile, version );

		outputFile->Write( fName, true );

		TransformMatrix		localTransform = fTransform;

		outputFile->Write( sizeof(double), & localTransform.v1.a00 );
		outputFile->Write( sizeof(double), & localTransform.v1.a01 );
		outputFile->Write( sizeof(double), & localTransform.v1.a02 );
		outputFile->Write( sizeof(double), & localTransform.v1.a10 );
		outputFile->Write( sizeof(double), & localTransform.v1.a11 );
		outputFile->Write( sizeof(double), & localTransform.v1.a12 );
		outputFile->Write( sizeof(double), & localTransform.v1.a20 );
		outputFile->Write( sizeof(double), & localTransform.v1.a21 );
		outputFile->Write( sizeof(double), & localTransform.v1.a22 );
		outputFile->Write( sizeof(double), & localTransform.v1.xOff );
		outputFile->Write( sizeof(double), & localTransform.v1.yOff );
		outputFile->Write( sizeof(double), & localTransform.v1.zOff );
	}

	outputFile->Write( "Prm:E", true ); // end marker
}

bool CPrimitiveParametric::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Prm:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenClass( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenAttributes( inputFile, version, asserter );

		result	= result && this->AssertFrozenValue( inputFile, fName, "fName", asserter, __FILE__, __LINE__ );

		TransformMatrix		localTransform = fTransform;

		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.a00 , "localTransform.v1.a00 ", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.a01 , "localTransform.v1.a01 ", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.a02 , "localTransform.v1.a02 ", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.a10 , "localTransform.v1.a10 ", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.a11 , "localTransform.v1.a11 ", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.a12 , "localTransform.v1.a12 ", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.a20 , "localTransform.v1.a20 ", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.a21 , "localTransform.v1.a21 ", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.a22 , "localTransform.v1.a22 ", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.xOff, "localTransform.v1.xOff", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.yOff, "localTransform.v1.yOff", asserter, __FILE__, __LINE__ );
		result = result && this->AssertFrozenValue( inputFile, localTransform.v1.zOff, "localTransform.v1.zOff", asserter, __FILE__, __LINE__ );
	}

	result = result && this->AssertFrozenTag( inputFile, "Prm:E", asserter, __FILE__, __LINE__ );

	return result;
}
