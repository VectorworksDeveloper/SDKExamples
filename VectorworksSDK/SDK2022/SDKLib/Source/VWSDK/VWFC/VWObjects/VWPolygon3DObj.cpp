//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWPolygon3DObj::VWPolygon3DObj()
{
	fhObject		= ::GS_Create3DPoly( gCBP );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create polygon3D" );
}

VWPolygon3DObj::VWPolygon3DObj(std::initializer_list<VWPoint3D> src)
	: VWPolygon3DObj( VWPolygon3D( src ) )
{
}

VWPolygon3DObj::VWPolygon3DObj(const VWPolygon3D& poly)
{
	fhObject		= ::GS_Create3DPoly( gCBP );
	size_t	len		= poly.GetVertexCount();
	VWFC_VERIFY( ( len < kMaxNum3DPolyVertices ) );
	for(size_t i=0; i<len; i++) {
		this->AddVertex( poly.GetVertexAt( i ), (i == len-1) );
	}

	::GS_SetPolyShapeClose( gCBP, fhObject, poly.IsClosed() );
	
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create polygon3D" );
}

VWPolygon3DObj::VWPolygon3DObj(const VWPolygon2D& poly, double z /*=0*/)
{
	fhObject		= ::GS_Create3DPoly( gCBP );
	size_t	len		= poly.GetVertexCount();
	VWFC_VERIFY( ( len < kMaxNum3DPolyVertices ) );
	for(size_t i=0; i<len; i++) {
		VWPoint2D	pt	= poly.GetVertexAt( i );
		this->AddVertex( pt.x, pt.y, z, false );
	}

	::GS_SetPolyShapeClose( gCBP, fhObject, poly.IsClosed() );

	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create polygon3D" );
}

VWPolygon3DObj::VWPolygon3DObj(MCObjectHandle hPoly3D)
{
	VWFC_ASSERT( VWPolygon3DObj::IsPolygon3DObject( hPoly3D ) );
	if ( ! VWPolygon3DObj::IsPolygon3DObject( hPoly3D ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hPoly3D;
	VWFC_ASSERT( fhObject != nil );
}

VWPolygon3DObj::VWPolygon3DObj(const VWPolygon3DObj& src)
{
	fhObject		= src.fhObject;
}

VWPolygon3DObj::~VWPolygon3DObj()
{
}

VWPolygon3DObj&	VWPolygon3DObj::operator=(const VWPolygon3DObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

bool VWPolygon3DObj::IsPolygon3DObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == qPolyNode;
}

size_t VWPolygon3DObj::GetVertexCount() const
{
	VWFC_ASSERT( fhObject );
	return (size_t) ::GS_CountVertices( gCBP, fhObject );
}

void VWPolygon3DObj::DeleteVertex(size_t index)
{
	VWFC_ASSERT( fhObject );
	short		ind		= DemoteTo<short>( kVStanev, index );
	::GS_DeleteVertex( gCBP, fhObject, ind+1 );
}

void VWPolygon3DObj::AddVertex(double x, double y, double z, bool bRecalcBounds /*=true*/)
{
	VWFC_ASSERT( fhObject );
	::GS_Add3DVertex( gCBP, fhObject, WorldPt3(x,y,z), bRecalcBounds );
}

void VWPolygon3DObj::AddVertex(const VWPoint3D& pt, bool bRecalcBounds /*=true*/)
{
	VWFC_ASSERT( fhObject );
	::GS_Add3DVertex( gCBP, fhObject, pt, bRecalcBounds );
}

void VWPolygon3DObj::AddVertex(const TSTLPoints3DArray& arrPts, bool reverse, bool bRecalcBounds /*=true*/)
{
	VWFC_ASSERT( fhObject );
	for(size_t i=0, cnt=arrPts.size(); i<cnt; ++i)
	{
		size_t index = reverse ? (cnt - i - 1): i;
		gSDK->Add3DVertex( fhObject, arrPts[index], bRecalcBounds );
	}
}

void VWPolygon3DObj::InsertVertex(size_t beforeIndex, const VWPoint3D& pt, bool bRecalcBounds /*=true*/)
{
	VWFC_ASSERT( fhObject );
	short		ind		= DemoteTo<short>( kVStanev, beforeIndex );
	::GS_Insert3DVertex( gCBP, fhObject, pt, ind+1, bRecalcBounds );
}

void VWPolygon3DObj::SetVertex(size_t index, const VWPoint3D& pt, bool bRecalcBounds /*=true*/)
{
	VWFC_ASSERT( fhObject );
	short		ind		= DemoteTo<short>( kVStanev, index );
	::GS_Set3DVertex( gCBP, fhObject, ind+1, pt, bRecalcBounds );
}

VWPoint3D VWPolygon3DObj::GetVertex(size_t index) const
{
	VWFC_ASSERT( fhObject );
	short		ind		= DemoteTo<short>( kVStanev, index );
	WorldPt3	pt;
	::GS_Get3DVertex( gCBP, fhObject, ind+1, pt );
	return pt;
}

void VWPolygon3DObj::SetClosed(bool bClosed)
{
	VWFC_ASSERT( fhObject );
	::GS_SetPolyShapeClose( gCBP, fhObject, bClosed );
}

bool VWPolygon3DObj::GetClosed() const
{
	return ::GS_GetPolyShapeClose( gCBP, fhObject ) ? true : false;
}

void VWPolygon3DObj::GetPolygon(VWPolygon2D& outPoly) const
{
	VWFC_ASSERT( fhObject );
	outPoly.ClearVertices();
	short	len	= ::GS_CountVertices( gCBP, fhObject );
	for(short i=0; i<len; i++) {
		WorldPt3	pt;
		::GS_Get3DVertex( gCBP, fhObject, i+1, pt );

		outPoly.AddVertex( pt.x, pt.y );
	}

	outPoly.SetClosed( ::GS_GetPolyShapeClose( gCBP, fhObject ) );
}

void VWPolygon3DObj::GetPolygon(VWPolygon3D& outPoly) const
{
	VWFC_ASSERT( fhObject );
	outPoly.ClearVertices();
	short	len	= ::GS_CountVertices( gCBP, fhObject );
	for(short i=0; i<len; i++) {
		WorldPt3	pt;
		::GS_Get3DVertex( gCBP, fhObject, i+1, pt );

		outPoly.AddVertex( pt );
	}

	outPoly.SetClosed( ::GS_GetPolyShapeClose( gCBP, fhObject ) );
}

void VWPolygon3DObj::SetPolygon(const VWPolygon3D& poly)
{
	size_t	vertCnt			= poly.GetVertexCount();
	size_t	existVertCnt	= this->GetVertexCount();
	for(size_t i=0; i<vertCnt; i++)
	{
		const VWPoint3D&	pt	= poly.GetVertexAt( i );
		if ( i < existVertCnt )
		{
			this->SetVertex( i, pt, false );
		}
		else
		{
			this->AddVertex( pt, false );
		}
	}

	for(size_t i=vertCnt; i<existVertCnt; i++)
	{
		this->DeleteVertex( vertCnt );
	}
}

void VWPolygon3DObj::GetObjectMatrix(VWTransformMatrix& outMatrix) const
{
	outMatrix.SetIdentity();
}

void VWPolygon3DObj::SetObjectMatrix(const VWTransformMatrix& matrix)
{
	VWFC_ASSERT( fhObject );
	VWPoint3D	thisPt;
	short		len			= ::GS_CountVertices( gCBP, fhObject );
	for(short i=0; i<len; i++) {
		WorldPt3	pt;
		::GS_Get3DVertex( gCBP, fhObject, i+1, pt );
		thisPt.x			= pt.x;
		thisPt.y			= pt.y;
		thisPt.z			= pt.z;
		thisPt				= matrix.PointTransform( thisPt );
		pt.x				= thisPt.x;
		pt.y				= thisPt.y;
		pt.z				= thisPt.z;
		::GS_Set3DVertex( gCBP, fhObject, i+1, pt, true );
	}
}
