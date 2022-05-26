//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_MESH_OBJECT__H
#define VECTORWORKS_MESH_OBJECT__H

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		// --------------------------------------------------------------------------
		class VWMeshObj : public VWObject
		{
		public:
							VWMeshObj();
							VWMeshObj(MCObjectHandle hMesh);
							VWMeshObj(const VWMeshObj& src);
			virtual			~VWMeshObj();

			VWMeshObj&		operator=(const VWMeshObj& src);

		public:
			VectorWorks::IMeshDataPtr	GetMesh();

		// tool
		public:
			// Return true if the specified object handle is 3D locus
			static bool		IsMeshObject(MCObjectHandle hObj);

		private:
			VectorWorks::IMeshDataPtr	fMeshData;
		};

		// --------------------------------------------------------------------------
		// Helps creating meshes from vertex and face data
		// 1. Use 'AddVertex' to fill all vertices
		// 2. Use 'AddPart' to define all texturable parts
		// 3. Use 'AddFace' or 'AddFace_*" calls to define the faces of the mesh
		//
		// Note, the order is not essetial
		//
		class VWMeshCreator
		{
		public:
						VWMeshCreator();
			virtual		~VWMeshCreator();

			size_t		AddPart(InternalIndex textureRef = 0L);
			size_t		AddPartUnique(InternalIndex textureRef);
			size_t		AddVertex(const WorldPt3& position, const WorldPt& uvCoord = WorldPt( 0.0, 0.0 ), const WorldPt3& normal = WorldPt3( 0.0, 0.0, 0.0 ));
			void		AddFace(size_t vertex1, size_t vertex2, size_t vertex3, size_t partIndex);
			void		AddFace(size_t vertex1, size_t vertex2, size_t vertex3, size_t partIndex, const ObjectColorType& color);
			void		AddFace_Begin();
			void		AddFace_Add(size_t vertex);
			void		AddFace_SetColor(const ObjectColorType& color);
			void		AddFace_End();
			void		AddFace_End(size_t partIndex);
			void		SetIsImported(bool isImported);

			void		GenerateSmoothNormals();

			void		GenerateMeshes(bool useUndo = true);
			const TMCObjectHandlesSTLArray&		GetGeneratedMeshes() const;

			size_t					GetVerticesCount() const;
			const WorldPt3&			GetVertexPosition(size_t index) const;
			const WorldPt&			GetVertexUVCoord(size_t index) const;
			const WorldPt3&			GetVertexNormal(size_t index) const;
			size_t					GetPartsCount() const;
			const InternalIndex&	GetPartTextureRef(size_t index) const;
			size_t					GetFacesCount() const;
			const bool&				IsFaceHaveColor(size_t index) const;
			const ObjectColorType&	GetFaceColor(size_t index) const;
			const size_t&			GetFacePartIndex(size_t index) const;
			size_t					GetFaceVertexCount(size_t index) const;
			const size_t&			GetFaceVertexIndexAt(size_t faceIndex, size_t vertexIndexAt) const;

			void					SetVertexPositionZ(size_t index, double z);
			void					SetVertexUVCoord( size_t index, const WorldPt&  ptUV );
			void					SetVertexNormal( size_t index, const WorldPt3& normal );
			void					SetMeshSmoothing( short meshSmoothingType, double creaseAngle = 50.0 );

		private:
			struct SVertexDef
			{
				WorldPt3	fPosition;
				WorldPt		fUVCoord;
				WorldPt3	fNormal;

				bool operator<(const SVertexDef& v) const
				{
					auto& p0 = fPosition;
					auto& p1 = v.fPosition;
					
					auto& n0 = fNormal;
					auto& n1 = v.fNormal;

					auto& t0 = fUVCoord;
					auto& t1 = v.fUVCoord;

					if( p0.x < p1.x ) return true;
					else if( p0.x > p1.x ) return false;

					if( p0.y < p1.y ) return true;
					else if( p0.y > p1.y ) return false;

					if( p0.z < p1.z ) return true;
					else if( p0.z > p1.z ) return false;

					if( n0.x < n1.x ) return true;
					else if( n0.x > n1.x ) return false;

					if( n0.y < n1.y ) return true;
					else if( n0.y > n1.y ) return false;

					if( n0.z < n1.z ) return true;
					else if( n0.z > n1.z ) return false;

					if( t0.x < t1.x ) return true;
					else if( t0.x > t1.x ) return false;

					if( t0.y < t1.y ) return true;
					else if( t0.y > t1.y ) return false;
					
					return false;
				}
			};

			struct SFaceDef
			{
				VectorWorks::TVWArray_SizeT	farrVertices;
				bool						fHasColor;
				ObjectColorType				fColor;
				size_t						fPartIndex;

				SFaceDef();
			};

			struct SPartDef
			{
				InternalIndex				fTextureRef;

				SPartDef();
			};

			typedef std::vector<SVertexDef>		TVertexArray;
			typedef std::vector<SFaceDef>		TFaceArray;
			typedef std::vector<SPartDef>		TPartArray;

			TVertexArray						farrVertices;
			TFaceArray							farrFaces;
			TPartArray							farrParts;
			bool								fIsImported;
			MeshSmoothing::EMeshSmoothing		fMeshSmoothing;
			double								fMeshCreaseAngle;
			std::map<SVertexDef, size_t>		fVertexMap;

			typedef std::map<InternalIndex, size_t>		TInternalIndex2PartDef;
			TInternalIndex2PartDef	fmapInternalIndex2PartDef;

			SFaceDef			fCurrentFaceWhenAdding;

			TMCObjectHandlesSTLArray	farrGeneratedMeshes;
		};
	}
}

#endif // VECTORWORKS_MESH_OBJECT__H