//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

// --------------------------------------------------------------------------
VWMeshObj::VWMeshObj()
{
	fhObject		= gSDK->CreateMesh( & fMeshData );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create mesh" );
}

VWMeshObj::VWMeshObj(MCObjectHandle hMesh)
{
	VWFC_ASSERT( VWMeshObj::IsMeshObject( hMesh ) );
	if ( ! VWMeshObj::IsMeshObject( hMesh ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hMesh;
	VWFC_ASSERT( fhObject != nil );

	gSDK->GetMesh( fhObject, & fMeshData );
}

VWMeshObj::VWMeshObj(const VWMeshObj& src)
{
	fhObject		= src.fhObject;
}

VWMeshObj::~VWMeshObj()
{
	fhObject		= nil;
}

VWMeshObj& VWMeshObj::operator=(const VWMeshObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

/*static*/ bool VWMeshObj::IsMeshObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kMeshNode;
}

VectorWorks::IMeshDataPtr VWMeshObj::GetMesh()
{
	return fMeshData;
}

// --------------------------------------------------------------------------
VWMeshCreator::SFaceDef::SFaceDef()
{
	fHasColor = false;
	fPartIndex = kTexturePart_Overall;
}

// --------------------------------------------------------------------------
VWMeshCreator::SPartDef::SPartDef()
{
	fTextureRef = 0L;
}

// --------------------------------------------------------------------------
VWMeshCreator::VWMeshCreator()
	: fIsImported( false )
{
	fMeshSmoothing   = MeshSmoothing::EMeshSmoothing::eUseDocumentPreference;
	fMeshCreaseAngle = 50.0;
	// Add primary, secondary, tertiary , and overall parts to part array so that first added mesh part is actually overall + 1.
	// Overall is used for untextured faces.  -DLD 3/11/2014
	SPartDef	partDef;
	partDef.fTextureRef	= 0L;
	farrParts.push_back(partDef);
	farrParts.push_back(partDef);
	farrParts.push_back(partDef);
	farrParts.push_back(partDef);
	fmapInternalIndex2PartDef.insert( TInternalIndex2PartDef::value_type( 0L, kTexturePart_Overall ) );
}

VWMeshCreator::~VWMeshCreator()
{
}

size_t VWMeshCreator::AddPart(InternalIndex textureRef)
{
	size_t newPartIndex = kTexturePart_Overall;

	ASSERTN(kDaveD, farrParts.size() >= 4L);

	SPartDef	partDef;
	partDef.fTextureRef		= textureRef;
	farrParts.push_back( partDef );
	newPartIndex	= farrParts.size() - 1;

	fmapInternalIndex2PartDef.insert( TInternalIndex2PartDef::value_type( textureRef, newPartIndex ) );
	
	ASSERTN(kDaveD, newPartIndex >= kTexturePart_Overall);

	return newPartIndex;
}

size_t VWMeshCreator::AddPartUnique(InternalIndex textureRef)
{
	size_t newPartIndex	= kTexturePart_Overall;

	if (textureRef > 0L) {
		TInternalIndex2PartDef::const_iterator it = fmapInternalIndex2PartDef.find( textureRef );
		if ( it != fmapInternalIndex2PartDef.end() )
		{
			newPartIndex	= it->second;
		}
		else
		{
			newPartIndex	= this->AddPart( textureRef );
		}
	}

	return newPartIndex;
}

size_t VWMeshCreator::AddVertex(const WorldPt3& position, const WorldPt& uvCoord, const WorldPt3& normal)
{
	SVertexDef	vertex;
	vertex.fPosition	= position;
	vertex.fUVCoord		= uvCoord;
	vertex.fNormal		= normal;

	// VWMeshCreator is generating duplicate vertices which which is unnecessary 
	// So a modules like OBJImport which usually don't have duplicate vertices will 
	// add them using AddVertes multiple times because they iterate over faces not the vertices.- FatemehA 3/2017
	// setting this to false right now
	static bool avoidDuplicateVertices = false;
	if (avoidDuplicateVertices){
		auto it = fVertexMap.find(vertex);
		if( it == fVertexMap.end() )
		{
			it = fVertexMap.insert(std::make_pair(vertex, farrVertices.size())).first; 
			farrVertices.push_back( vertex );
		}

		return it->second;
	}
	else{ 
		farrVertices.push_back( vertex );
		return farrVertices.size() - 1;
	}
}

void VWMeshCreator::AddFace(size_t vertex1, size_t vertex2, size_t vertex3, size_t partIndex)
{
	SFaceDef	faceDef;
	faceDef.farrVertices.Append( vertex1 );
	faceDef.farrVertices.Append( vertex2 );
	faceDef.farrVertices.Append( vertex3 );
	faceDef.fPartIndex	 = partIndex;
	farrFaces.push_back( faceDef );
	
	ASSERTN(kDaveD, partIndex >= kTexturePart_Overall);
}

void VWMeshCreator::AddFace(size_t vertex1, size_t vertex2, size_t vertex3, size_t partIndex, const ObjectColorType& color)
{
	SFaceDef	faceDef;
	faceDef.farrVertices.Append( vertex1 );
	faceDef.farrVertices.Append( vertex2 );
	faceDef.farrVertices.Append( vertex3 );
	faceDef.fPartIndex	= partIndex;
	faceDef.fHasColor	= true;
	faceDef.fColor		= color;
	farrFaces.push_back( faceDef );
	
	ASSERTN(kDaveD, partIndex >= kTexturePart_Overall);
}

void VWMeshCreator::AddFace_Begin()
{
	fCurrentFaceWhenAdding = SFaceDef();
}

void VWMeshCreator::AddFace_Add(size_t vertex)
{
	fCurrentFaceWhenAdding.farrVertices.Append( vertex );
}

void VWMeshCreator::AddFace_SetColor(const ObjectColorType& color)
{
	fCurrentFaceWhenAdding.fHasColor	= true;
	fCurrentFaceWhenAdding.fColor		= color;
}

void VWMeshCreator::AddFace_End()
{
	farrFaces.push_back( fCurrentFaceWhenAdding );
	fCurrentFaceWhenAdding = SFaceDef();
}

void VWMeshCreator::AddFace_End(size_t partIndex)
{
	fCurrentFaceWhenAdding.fPartIndex	 = partIndex;
	farrFaces.push_back( fCurrentFaceWhenAdding );
	fCurrentFaceWhenAdding = SFaceDef();
}

void VWMeshCreator::SetIsImported(bool isImported)
{
	fIsImported = isImported;
}

void VWMeshCreator::GenerateSmoothNormals()
{
	// not implemented
}

void VWMeshCreator::GenerateMeshes(bool useUndo/*=true*/)
{
	if( farrFaces.size() > 0 )
	{
		VectorWorks::IMeshDataPtr	meshData;
		MCObjectHandle hMesh = gSDK->CreateMesh( & meshData );

		if ( useUndo )
		{
			gSDK->AddAfterSwapObject( hMesh );
		}

		bool bSingleMesh				= true;
		bool bLastMeshPart				= false;
		//Charlene: question here
		//const size_t maxVerticesLimit	= 30000;
		const size_t maxVerticesLimit	= 0x000FFFFF;

		size_t maxVertices				= maxVerticesLimit - 1000;//for splitting meshes limit = maxVerticesLimit - maxFaceLimit	
		bSingleMesh						= farrVertices.size() < maxVerticesLimit;

		// Don't set vertex UVs if they are all 0,0 (default parameter value), and don't set
		// vertex normals if the data is bad or nonsensical.  -DLD 2/28/2014
		bool badNormals = false;
		bool allUVsDefault = true;

		for (size_t iVertex = 0, n = farrVertices.size(); iVertex < n; ++iVertex )
		{
			const SVertexDef& vertex = farrVertices[ iVertex ];

			if (!DoublesAreNearlyEqual(vertex.fUVCoord.x, 0.0, kNearlyEqualEpsilonForNormalizedValues) ||
				!DoublesAreNearlyEqual(vertex.fUVCoord.y, 0.0, kNearlyEqualEpsilonForNormalizedValues)) {

					allUVsDefault = false;
			}

			// If vertex normal is not normalized then don't use them, this can happen with all zeroes or default
			// WorldCoord of 1E+100 or just bad file data.  -DLD 3/18/2014
			if (!DoublesAreNearlyEqual(vertex.fNormal.Magnitude(), 1.0, kNearlyEqualEpsilonForNormalizedValues))
				badNormals = true;
		}

		// set mesh smoothing 	 eUseDocumentPreference is by default
		if ( !badNormals && fIsImported == true )
			meshData->SetMeshSmoothing( VectorWorks::MeshSmoothing::eImported );

		if ( fMeshSmoothing == VectorWorks::MeshSmoothing::eCustomCrease )
		{
			meshData->SetMeshSmoothing( fMeshSmoothing );
			meshData->SetCreaseAngle( fMeshCreaseAngle );
		}
		else if ( fMeshSmoothing == VectorWorks::MeshSmoothing::eUseDocumentPreference )
		{
			meshData->SetMeshSmoothing( VectorWorks::MeshSmoothing::eUseDocumentPreference);
		}		
		else if ( fMeshSmoothing == VectorWorks::MeshSmoothing::eNone )
		{
			meshData->SetMeshSmoothing( VectorWorks::MeshSmoothing::eNone );
		}

		meshData->ClearVertex();
		meshData->ClearVertexNormalsAndUVCoords();

		typedef std::map<size_t, size_t>	TInternalPartIndex2MeshPartIndex;

		TInternalPartIndex2MeshPartIndex	mapInternalPartIndex2MeshPartIndex;


		for(size_t iPart=0, n=farrParts.size(); iPart < n; ++iPart)
		{
			const SPartDef&	part	= farrParts[ iPart ];

			size_t	meshPartIndex	= meshData->AddPart( part.fTextureRef );

			mapInternalPartIndex2MeshPartIndex.insert( TInternalPartIndex2MeshPartIndex::value_type( iPart, meshPartIndex ) );
		}

		size_t nFaces = farrFaces.size();
		size_t nFaceBreak = 0;

		typedef std::map<size_t, size_t>	TInternalVertexIDPart2MeshOriginalIndex; // old index , new index in the split mesh

		TInternalVertexIDPart2MeshOriginalIndex	mapInternalSplitMeshVertex;

		for(size_t iFace=0; iFace < nFaces; ++iFace )
		{
			SFaceDef&	face	= farrFaces[ iFace ];
			size_t nVertexCountFace = face.farrVertices.GetSize();

			// add Vertices	from faces
			for( size_t iVertex = 0; iVertex < nVertexCountFace; ++iVertex )
			{
				size_t nCurrentFaceVertexIndex = face.farrVertices.GetAt( iVertex );

				const SVertexDef&	vertex	= farrVertices[ nCurrentFaceVertexIndex ];

				auto itIndex = mapInternalSplitMeshVertex.find( nCurrentFaceVertexIndex );
				if ( itIndex == mapInternalSplitMeshVertex.end() )
				{
					size_t mapSize = mapInternalSplitMeshVertex.size();
					mapInternalSplitMeshVertex.insert( TInternalVertexIDPart2MeshOriginalIndex::value_type( nCurrentFaceVertexIndex, mapSize ) );
					face.farrVertices.SetAt( iVertex, mapSize );
				}
				else
				{
					face.farrVertices.SetAt( iVertex, itIndex->second );
				}

				itIndex =  mapInternalSplitMeshVertex.find( nCurrentFaceVertexIndex );

				meshData->SetVertexPosition( itIndex->second, vertex.fPosition );

				if (!allUVsDefault)
					meshData->SetVertexUVCoord( itIndex->second, vertex.fUVCoord );

				if (!badNormals)
					meshData->SetVertexNormal( itIndex->second, vertex.fNormal );
			}

			// Add Faces
			MCObjectHandle hMeshFace = gSDK->AddMeshFace( hMesh, face.farrVertices );
			if ( hMeshFace && face.fHasColor )
			{
				gSDK->SetColor( hMeshFace, face.fColor );
			}

			TInternalPartIndex2MeshPartIndex::const_iterator it = mapInternalPartIndex2MeshPartIndex.find( face.fPartIndex );
			if ( it != mapInternalPartIndex2MeshPartIndex.end() )
			{
				size_t	meshPartIndex = it->second;
				meshData->SetFacePart( iFace - nFaceBreak, meshPartIndex );
			}
			else
			{
				meshData->SetFacePart( iFace - nFaceBreak, kTexturePart_Overall );
			}

			// split the mesh if neccessary
			bool bNextFaceSplit = ( mapInternalSplitMeshVertex.size() > maxVertices );

			bLastMeshPart = ( iFace + 1 == nFaces );

			if( !bSingleMesh && bNextFaceSplit && !bLastMeshPart )
			{
				if ( meshData->Save() )
				{
					farrGeneratedMeshes.push_back( hMesh );

					meshData->ClearFaces();
					meshData->ClearVertex();
					meshData->ClearVertexNormalsAndUVCoords();
					meshData->ClearParts();
					mapInternalSplitMeshVertex.clear();

					hMesh = NULL;
					hMesh = gSDK->CreateMesh( & meshData );

                    if ( hMesh && useUndo )
					{
                        gSDK->AddAfterSwapObject( hMesh );
                    }

					if ( !badNormals && fIsImported == true )
					{
						meshData->SetMeshSmoothing( VectorWorks::MeshSmoothing::eImported );
					}

					if ( fMeshSmoothing == VectorWorks::MeshSmoothing::eCustomCrease )
					{
						meshData->SetMeshSmoothing( fMeshSmoothing );
						meshData->SetCreaseAngle( fMeshCreaseAngle );
					}
					else if ( fMeshSmoothing == VectorWorks::MeshSmoothing::eUseDocumentPreference )
					{
						meshData->SetMeshSmoothing( VectorWorks::MeshSmoothing::eUseDocumentPreference );
					}		
					else if ( fMeshSmoothing == VectorWorks::MeshSmoothing::eNone )
					{
						meshData->SetMeshSmoothing( VectorWorks::MeshSmoothing::eNone );
					}


					mapInternalPartIndex2MeshPartIndex.clear();
					for(size_t iPart=0, n=farrParts.size(); iPart < n; ++iPart)
					{
						const SPartDef&	part	= farrParts[ iPart ];
						size_t	meshPartIndex	= meshData->AddPart( part.fTextureRef );
						mapInternalPartIndex2MeshPartIndex.insert( TInternalPartIndex2MeshPartIndex::value_type( iPart, meshPartIndex ) );
					}

					nFaceBreak = iFace + 1;
				}
				else if ( hMesh )
				{
					if( useUndo )
					{
                        gSDK->AddBeforeSwapObject( hMesh );
					}

					gSDK->DeleteObject( hMesh, useUndo );
				}
			}  
		}

		if( bSingleMesh || bLastMeshPart )
		{
			//all vertices are saved if it is Single mesh
			if ( meshData->Save() )
			{
				farrGeneratedMeshes.push_back( hMesh );

				meshData->ClearFaces();
				meshData->ClearVertex();
				meshData->ClearVertexNormalsAndUVCoords();
				meshData->ClearParts();
			}
			else if ( hMesh )
			{
                if ( useUndo )
				{
                    gSDK->AddBeforeSwapObject( hMesh );
                }

				gSDK->DeleteObject( hMesh, useUndo );
			}
		}
	}
}

const TMCObjectHandlesSTLArray& VWMeshCreator::GetGeneratedMeshes() const
{
	return farrGeneratedMeshes;
}

size_t VWMeshCreator::GetVerticesCount() const
{
	return farrVertices.size();
}

const WorldPt3& VWMeshCreator::GetVertexPosition(size_t index) const
{
	return farrVertices[index].fPosition;
}

void VWMeshCreator::SetVertexPositionZ(size_t index, double z)
{
	farrVertices[index].fPosition.z = z;
}

void VWMeshCreator::SetVertexNormal( size_t index, const WorldPt3& normal )
{
	farrVertices[index].fNormal = normal;
}

void VWMeshCreator::SetVertexUVCoord( size_t index, const WorldPt&  ptUV )
{
	farrVertices[index].fUVCoord = ptUV;
}


const WorldPt& VWMeshCreator::GetVertexUVCoord(size_t index) const
{
	return farrVertices[index].fUVCoord;
}

const WorldPt3& VWMeshCreator::GetVertexNormal(size_t index) const
{
	return farrVertices[index].fNormal;
}

size_t VWMeshCreator::GetPartsCount() const
{
	return farrParts.size();
}

const InternalIndex& VWMeshCreator::GetPartTextureRef( size_t index) const
{
	return farrParts[index].fTextureRef;
}

size_t VWMeshCreator::GetFacesCount() const
{
	return farrFaces.size();
}

const bool& VWMeshCreator::IsFaceHaveColor(size_t index) const
{
	return farrFaces[index].fHasColor;
}

const ObjectColorType& VWMeshCreator::GetFaceColor(size_t index) const
{
	return farrFaces[index].fColor;
}

const size_t& VWMeshCreator::GetFacePartIndex(size_t index) const
{
	return farrFaces[index].fPartIndex;
}

size_t VWMeshCreator::GetFaceVertexCount(size_t index) const
{
	return farrFaces[index].farrVertices.GetSize();
}

const size_t& VWMeshCreator::GetFaceVertexIndexAt(size_t faceIndex, size_t vertexIndexAt) const
{
	return farrFaces[faceIndex].farrVertices.GetAt( vertexIndexAt );
}

void VWMeshCreator::SetMeshSmoothing( short meshSmoothingType, double creaseAngle )
{
	switch( meshSmoothingType )
	{
	case 0:
		fMeshSmoothing = MeshSmoothing::EMeshSmoothing::eNone;
		break;
	case 1:
		fMeshSmoothing = MeshSmoothing::EMeshSmoothing::eUseDocumentPreference;
		break;
	case 2:
		fMeshSmoothing = MeshSmoothing::EMeshSmoothing::eCustomCrease;
		fMeshCreaseAngle = creaseAngle;
		break;
	case 3:
		fMeshSmoothing = MeshSmoothing::EMeshSmoothing::eImported;
		break;
	default:
		fMeshSmoothing = MeshSmoothing::EMeshSmoothing::eUseDocumentPreference;
		break;
	}
}
