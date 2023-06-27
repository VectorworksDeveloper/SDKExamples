//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "Primitives3D.h"

using namespace VectorWorks::Filing;
using namespace VWFC::Tools;
using namespace VWFC::Tools::DocumentFreezer;

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitivePolygon3D::CPrimitivePolygon3D(MCObjectHandle h)
	: CPrimitive( h )
{
	VWPolygon3DObj	obj( fObject );
	obj.GetPolygon( fPoly3D );
}

CPrimitivePolygon3D::~CPrimitivePolygon3D()
{
}

void CPrimitivePolygon3D::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Pl3D:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );
		CPrimitive::FreezeClass( outputFile, version );
		CPrimitive::FreezeAttributes( outputFile, version );
		CPrimitive::FreezeTextureAttrbs( outputFile, version );

		outputFile->Write( Uint8(fPoly3D.IsClosed()) );

		size_t	vertexCnt = fPoly3D.GetVertexCount();
		outputFile->Write( Uint64(vertexCnt) );

		for(size_t i=0; i<vertexCnt; ++i)
		{
			const VWPoint3D&	pt = fPoly3D.GetVertexAt( i );

			outputFile->Write( sizeof(double), & pt.x );
			outputFile->Write( sizeof(double), & pt.y );
			outputFile->Write( sizeof(double), & pt.z );
		}
	}

	outputFile->Write( "Pl3D:E", true ); // end marker
}

bool CPrimitivePolygon3D::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Pl3D:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenClass( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenAttributes( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenTextureAttrbs( inputFile, version, asserter );

		result = result && this->AssertFrozenValue<Uint8>( inputFile, fPoly3D.IsClosed(), "fPoly3D.IsClosed()", asserter, __FILE__, __LINE__ );

		if ( result )
		{
			Uint64	inputCnt;
			inputFile->Read( inputCnt );

			size_t	vertexCnt = fPoly3D.GetVertexCount();
			result = result && ( vertexCnt == inputCnt );

			if ( result )
			{
				for(size_t i=0; i<vertexCnt && result; ++i)
				{
					const VWPoint3D&	vertexPt = fPoly3D.GetVertexAt( i );

					result = result && this->AssertFrozenValue( inputFile, vertexPt.x, "vertexPt.x", asserter, __FILE__, __LINE__ );
					result = result && this->AssertFrozenValue( inputFile, vertexPt.y, "vertexPt.y", asserter, __FILE__, __LINE__ );
					result = result && this->AssertFrozenValue( inputFile, vertexPt.z, "vertexPt.z", asserter, __FILE__, __LINE__ );
				}
			}
			else if ( asserter )
			{
				asserter->AddFail( "Poly line vertex count doesn't match", __FILE__, __LINE__ );
			}
		}
	}

	result = result && this->AssertFrozenTag( inputFile, "Pl3D:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveMesh::CPrimitiveMesh(MCObjectHandle h)
	: CPrimitive( h )
{
}

CPrimitiveMesh::~CPrimitiveMesh()
{
}

void CPrimitiveMesh::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Msh:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );
		CPrimitive::FreezeClass( outputFile, version );
		CPrimitive::FreezeAttributes( outputFile, version );

		VectorWorks::IMeshDataPtr	meshData;
		if ( gSDK->GetMesh( fObject, & meshData ) )
		{
			// vertex data
			outputFile->Write( Uint8(meshData->HasVertexUVCoords() ) );
			outputFile->Write( Uint8(meshData->HasVertexNormals() ) );

			size_t	vertexCnt = meshData->GetVertexCount();
			outputFile->Write( Uint64(vertexCnt) );
			for(size_t iVertex=0; iVertex<vertexCnt; ++iVertex)
			{
				WorldPt3	vertex;
				meshData->GetVertexPosition( iVertex, vertex );
				outputFile->Write( sizeof(double), & vertex.x );
				outputFile->Write( sizeof(double), & vertex.y );
				outputFile->Write( sizeof(double), & vertex.z );

				WorldPt		uvCoord;
				meshData->GetVertexUVCoord( iVertex, uvCoord );
				outputFile->Write( sizeof(double), & uvCoord.x );
				outputFile->Write( sizeof(double), & uvCoord.y );

				WorldPt3	normal;
				meshData->GetVertexNormal( iVertex, normal );
				outputFile->Write( sizeof(double), & normal.x );
				outputFile->Write( sizeof(double), & normal.y );
				outputFile->Write( sizeof(double), & normal.z );
			}

			MeshSmoothing::EMeshSmoothing	meshSmoothing;
			meshData->GetMeshSmoothing( meshSmoothing );
			outputFile->Write( Uint16(meshSmoothing) );

			double		creaseAngle;
			meshData->GetCreaseAngle( creaseAngle );
			outputFile->Write( sizeof(double), & creaseAngle );

			// face data
			outputFile->Write( Uint8(meshData->HasFaceTextures()) );

			size_t	facesCnt = meshData->GetFaceCount();
			outputFile->Write( Uint64(facesCnt) );
			for(size_t iFace=0; iFace<facesCnt; ++iFace)
			{
				TVWArray_SizeT	arrVertexIndices;
				meshData->GetFaceVertices( iFace, arrVertexIndices );

				size_t vetexIndicesCnt = arrVertexIndices.GetSize();
				outputFile->Write( Uint64(vetexIndicesCnt) );

				for(size_t i=0; i<vetexIndicesCnt; ++i)
				{
					outputFile->Write( Uint64(arrVertexIndices[i]) );
				}

				size_t	partIndex;
				meshData->GetFacePart( iFace, partIndex );
				outputFile->Write( Uint64(partIndex) );
			}

			// parts data
			size_t partsCnt = meshData->GetPartsCount();
			outputFile->Write( Uint64(partsCnt) );
			for(size_t iPart=0; iPart<partsCnt; ++iPart)
			{
				RefNumber	texture;
				meshData->GetPartTexture( iPart, texture );
				outputFile->Write( Uint32(texture) );
			}
		}
	}


	outputFile->Write( "Msh:E", true ); // end marker
}

bool CPrimitiveMesh::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Msh:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenClass( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenAttributes( inputFile, version, asserter );

		if ( result )
		{
			VectorWorks::IMeshDataPtr	meshData;
			if ( gSDK->GetMesh( fObject, & meshData ) )
			{
				// vertex data
				result = result && this->AssertFrozenValue<Uint8>( inputFile, meshData->HasVertexUVCoords(), "meshData->HasVertexUVCoords()", asserter, __FILE__, __LINE__ );
				result = result && this->AssertFrozenValue<Uint8>( inputFile, meshData->HasVertexNormals(), "meshData->HasVertexNormals()", asserter, __FILE__, __LINE__ );

				Uint64	inputVertexCnt;
				inputFile->Read( inputVertexCnt );

				size_t	vertexCnt = meshData->GetVertexCount();
				result = result && (inputVertexCnt == vertexCnt );

				if ( result )
				{
					for(size_t iVertex=0; iVertex<vertexCnt && result; ++iVertex)
					{
						WorldPt3	vertex;
						meshData->GetVertexPosition( iVertex, vertex );
						result = result && this->AssertFrozenValue( inputFile, vertex.x, "vertex.x", asserter, __FILE__, __LINE__ );
						result = result && this->AssertFrozenValue( inputFile, vertex.y, "vertex.y", asserter, __FILE__, __LINE__ );
						result = result && this->AssertFrozenValue( inputFile, vertex.z, "vertex.z", asserter, __FILE__, __LINE__ );

						WorldPt		uvCoord;
						meshData->GetVertexUVCoord( iVertex, uvCoord );
						result = result && this->AssertFrozenValue( inputFile, uvCoord.x, "uvCoord.x", asserter, __FILE__, __LINE__ );
						result = result && this->AssertFrozenValue( inputFile, uvCoord.y, "uvCoord.y", asserter, __FILE__, __LINE__ );

						WorldPt3	normal;
						meshData->GetVertexNormal( iVertex, normal );
						result = result && this->AssertFrozenValue( inputFile, normal.x, "normal.x", asserter, __FILE__, __LINE__ );
						result = result && this->AssertFrozenValue( inputFile, normal.y, "normal.y", asserter, __FILE__, __LINE__ );
						result = result && this->AssertFrozenValue( inputFile, normal.z, "normal.z", asserter, __FILE__, __LINE__ );
					}

					MeshSmoothing::EMeshSmoothing	meshSmoothing;
					meshData->GetMeshSmoothing( meshSmoothing );
					result = result && this->AssertFrozenValue<Uint16>( inputFile, meshSmoothing, "meshSmoothing", asserter, __FILE__, __LINE__ );

					double		creaseAngle;
					meshData->GetCreaseAngle( creaseAngle );
					result = result && this->AssertFrozenValue( inputFile, creaseAngle, "creaseAngle", asserter, __FILE__, __LINE__ );

					// face data
					result = result && this->AssertFrozenValue<Uint8>( inputFile, meshData->HasFaceTextures(), "meshData->HasFaceTextures()", asserter, __FILE__, __LINE__ );

					Uint64	inputFacesCnt;
					inputFile->Read( inputFacesCnt );

					size_t	facesCnt = meshData->GetFaceCount();
					result = result && ( inputFacesCnt == facesCnt);

					if ( result )
					{
						for(size_t iFace=0; iFace<facesCnt && result; ++iFace)
						{
							TVWArray_SizeT	arrVertexIndices;
							meshData->GetFaceVertices( iFace, arrVertexIndices );

							Uint64	inputVertexIndicesCnt;
							inputFile->Read( inputVertexIndicesCnt );

							size_t vetexIndicesCnt = arrVertexIndices.GetSize();
							result = result && (inputVertexIndicesCnt == vetexIndicesCnt);
							if ( result )
							{
								for(size_t i=0; i<vetexIndicesCnt && result; ++i)
								{
									Uint64	inputIndex;
									inputFile->Read( inputIndex );

									result = result && (inputIndex == arrVertexIndices[i]);
								}

								Uint64	inputPartIndex;
								inputFile->Read( inputPartIndex );

								size_t	partIndex;
								meshData->GetFacePart( iFace, partIndex );
							}
							else if ( asserter )
							{
								asserter->AddFail( "mesh face vertex indices count doesn't match", __FILE__, __LINE__ );
							}
						}

						// parts data
						Uint64	inputPartsCnt;
						inputFile->Read( inputPartsCnt );

						size_t partsCnt = meshData->GetPartsCount();
						result = result && (inputPartsCnt == partsCnt);
						if ( result )
						{
							for(size_t iPart=0; iPart<partsCnt && result; ++iPart)
							{
								RefNumber	texture;
								meshData->GetPartTexture( iPart, texture );

								result = result && this->AssertFrozenValue<Uint32>( inputFile, texture, "texture", asserter, __FILE__, __LINE__ );
							}
						}
						else if ( asserter )
						{
							asserter->AddFail( "mesh parts count doesn't match", __FILE__, __LINE__ );
						}
					}
					else if ( asserter )
					{
						asserter->AddFail( "mesh faces count doesn't match", __FILE__, __LINE__ );
					}
				}
				else if ( asserter )
				{
					asserter->AddFail( "mesh vertex count doesn't match", __FILE__, __LINE__ );
				}
			}
		}
	}

	result = result && this->AssertFrozenTag( inputFile, "Msh:E", asserter, __FILE__, __LINE__ );

	return result;
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
CPrimitiveSymbol::CPrimitiveSymbol(MCObjectHandle h)
	: CPrimitive( h )
{
	VWSymbolObj		symObj( fObject );
	MCObjectHandle	hSymDef = symObj.GetSymbolDef();
	
	gSDK->GetObjectName( hSymDef, fSymbolDefName );

	symObj.GetObjectMatrix( fTransform );
}

CPrimitiveSymbol::~CPrimitiveSymbol()
{
}

void CPrimitiveSymbol::Freeze(IStdFile* outputFile, EDocumentFreezerVersion version)
{
	outputFile->Write( "Sym:B", true ); // begin marker

	if ( version <= eDocumentFreezerVersion_1 )
	{
		CPrimitive::FreezeAUX( outputFile, version );
		CPrimitive::FreezeClass( outputFile, version );
		CPrimitive::FreezeAttributes( outputFile, version );

		outputFile->Write( fSymbolDefName, true );

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

	outputFile->Write( "Sym:E", true ); // end marker
}

bool CPrimitiveSymbol::AssertFrozen(IStdFile* inputFile, EDocumentFreezerVersion version, IDocumentFreezerAsserter* asserter)
{
	bool result = this->AssertFrozenTag( inputFile, "Sym:B", asserter, __FILE__, __LINE__ );

	if ( version <= eDocumentFreezerVersion_1 )
	{
		result = result && CPrimitive::AssertFrozenAUX( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenClass( inputFile, version, asserter );
		result = result && CPrimitive::AssertFrozenAttributes( inputFile, version, asserter );

		result	= result && this->AssertFrozenValue( inputFile, fSymbolDefName, "fSymbolDefName", asserter, __FILE__, __LINE__ );

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

	result = result && this->AssertFrozenTag( inputFile, "Sym:E", asserter, __FILE__, __LINE__ );

	return result;
}
