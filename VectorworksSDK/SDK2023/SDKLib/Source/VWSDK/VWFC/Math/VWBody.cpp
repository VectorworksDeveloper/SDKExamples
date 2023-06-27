//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "Interfaces/VectorWorks/IParasolidKernel.h"


using namespace VWFC::Math;


VWBody::VWBody()
{
	fp		= NULL;
	fBodyID	= 0;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
}

VWBody::VWBody(Sint32 bodyID)
{
	fp		= NULL;
	fBodyID = 0;

	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	
	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kBiplab, !PK_ENTITY_is(bodyID, &isEntity));

	if (isEntity == PK_LOGICAL_true) 
		fBodyID	= bodyID;
}

VWBody::VWBody(const VWBody& src)
{
	fp		= NULL;
	fBodyID = 0;

	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	
	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kBiplab, !PK_ENTITY_is(src.fBodyID, &isEntity));

	if (isEntity == PK_LOGICAL_true) 
		fBodyID	= src.fBodyID;
}

VWBody::~VWBody()
{
	if ( fp ) {
		fp->Release();
		fp	= NULL;
	}
}

VWBody& VWBody::operator=(const VWBody& src)
{
	fBodyID	= src.fBodyID;
	return *this;
}

size_t VWBody::GetFacesCount()
{
	Sint32 nFaces = 0;
	if (fp) {
		VERIFYN(kBiplab, !PK_BODY_ask_faces(fBodyID, &nFaces, NULL));
	}

	return (size_t) nFaces; //-V201
}

VWBodyFace VWBody::GetFaceAt(size_t index)
{
	if (fp) {
		Sint32 nFaces = 0;
		PK_FACE_t *faces = NULL;
		VERIFYN(kBiplab, !PK_BODY_ask_faces(fBodyID, &nFaces, &faces));

		if (nFaces > 0 && index < (size_t)nFaces) { //-V201
			PK_FACE_t face = faces[index];
			if (faces)
				PK_MEMORY_free(faces);

			return VWBodyFace(face);
		}

		if (faces)
			PK_MEMORY_free(faces);
	}

	return VWBodyFace( PK_ENTITY_null );
}

size_t VWBody::GetEdgesCount()
{
	Sint32 nEdges = 0;
	if (fp) {
		VERIFYN(kBiplab, !PK_BODY_ask_edges(fBodyID, &nEdges, NULL));
	}

	return (size_t) nEdges; //-V201
}

VWBodyEdge VWBody::GetEdgeAt(size_t index)
{
	if (fp) {	
		Sint32 nEdges = 0;
		PK_EDGE_t *edges = NULL;
		VERIFYN(kBiplab, !PK_BODY_ask_edges(fBodyID, &nEdges, &edges));

		if (nEdges > 0 && index < (size_t)nEdges) { //-V201
			PK_EDGE_t edge = edges[index];
			if (edges)
				PK_MEMORY_free(edges);

			return VWBodyEdge(edge);
		}

		if (edges)
			PK_MEMORY_free(edges);
	}

	return VWBodyEdge( PK_ENTITY_null );
}

Sint32 VWBody::GetBodyID() const
{
	return fBodyID;
}

bool VWBody::RayShoot(const VWPoint3D& pt, const VWPoint3D& vector, VWBodyFace& outFace, VWBodyEdge& outEdge)
{
	outFace.SetBodyFaceID( 0 );
	outEdge.SetBodyEdgeID( 0 );

	DSTOP((kVStanev, "Not implemented"));

	return false;
}

