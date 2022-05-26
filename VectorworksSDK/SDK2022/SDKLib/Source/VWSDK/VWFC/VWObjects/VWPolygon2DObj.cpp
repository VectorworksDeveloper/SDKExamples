//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWPolygon2DObj::VWPolygon2DObj()
{
	fhObject		= ::GS_CreatePolyshape( gCBP );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create polygon2D" );
}

VWPolygon2DObj::VWPolygon2DObj(std::initializer_list<VWPoint2D> src)
	: VWPolygon2DObj( VWPolygon2D( src ) )
{
}

VWPolygon2DObj::VWPolygon2DObj(const VWPolygon2D& poly)
{
	fhObject		= ::GS_CreatePolyshape( gCBP );
	size_t	len		= poly.GetVertexCount();
	VWFC_VERIFY( ( len < kMaxNum2DPolyVertices ) );
	for(size_t i=0; i<len; i++) {
		VWPoint2D	pt	= poly.GetVertexAt( i );
		switch( poly.GetVertexType( i ) ) {
			case eVertexType_Corner:	this->AddCornerVertex( pt, false );	break;
			case eVertexType_Bezier:	this->AddBezierVertex( pt, false ); break;
			case eVertexType_Cubic:		this->AddCubicVertex( pt, false ); break;
			case eVertexType_Arc:		this->AddArcVertex( pt, poly.GetArcVertexRadius(i), false ); break;
			case eVertexType_Radius:	this->AddRadiusVertex( pt, false ); break;
			default:	VWFC_ASSERT( false );	break;
		}
	}

	// hide vertices if that is desire
	bool	bHaveHiddenVerts		= false;
	for(size_t i=0; i<len; i++) {
		bool	bVis	= poly.GetVertexVisible( i );
		if ( ! bVis ) {
			bHaveHiddenVerts	= true;
			break;
		}
	}

	if ( bHaveHiddenVerts ) {
		for(size_t i=0; i<len; i++) {
			this->SetVertexVisible( i, poly.GetVertexVisible( i ) );
		}

		// if the poly is not closed override the last vertex visibility to false
		if ( ! poly.IsClosed() )
			this->SetVertexVisible( len-1, false );
	}
	else {
		::GS_SetPolyShapeClose( gCBP, fhObject, poly.IsClosed() );
	}

	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create polygon2D" );
}

VWPolygon2DObj::VWPolygon2DObj(const VWPolygon3D& poly)
{
	fhObject		= ::GS_CreatePolyshape( gCBP );
	size_t	len		= poly.GetVertexCount();
	VWFC_VERIFY( ( len < kMaxNum2DPolyVertices ) );
	for(size_t i=0; i<len; i++) {
		VWPoint2D	pt	= poly.GetVertexAt( i );
		this->AddCornerVertex( pt, false );
	}

	::GS_SetPolyShapeClose( gCBP, fhObject, poly.IsClosed() );

	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create polygon2D" );
}

VWPolygon2DObj::VWPolygon2DObj(MCObjectHandle hPoly2D)
{
	VWFC_ASSERT( VWPolygon2DObj::IsPoly2DObject( hPoly2D ) );
	if ( ! VWPolygon2DObj::IsPoly2DObject( hPoly2D ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hPoly2D;
	VWFC_ASSERT( fhObject != nil );
}

VWPolygon2DObj::VWPolygon2DObj(const VWPolygon2DObj& src)
{
	fhObject		= src.fhObject;
}

VWPolygon2DObj::VWPolygon2DObj(const VWRectangle2D& srcRect)
{
	fhObject	= ::GS_CreatePolyshape( gCBP );

	this->AddCornerVertex(srcRect.GetTopLeft());
	this->AddCornerVertex(srcRect.GetRight(), srcRect.GetTop());
	this->AddCornerVertex(srcRect.GetBottomRight());
	this->AddCornerVertex(srcRect.GetLeft(), srcRect.GetBottom());

	::GS_SetPolyShapeClose( gCBP, fhObject, true );

	
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create polygon2D" );


}

VWPolygon2DObj::~VWPolygon2DObj()
{
}

VWPolygon2DObj& VWPolygon2DObj::operator=(const VWPolygon2DObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

bool VWPolygon2DObj::IsPoly2DObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kPolygonNode || type == kPolylineNode || type == kBoxNode;
}

bool VWPolygon2DObj::IsPolygon2DObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kPolygonNode || type == kBoxNode;
}

bool VWPolygon2DObj::IsPolyline2DObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kPolylineNode;
}

void VWPolygon2DObj::AddVertex(double x, double y, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode ) {
		WorldRect	rect;
		::GS_GetObjectBounds( gCBP, fhObject, rect );
		rect.Unite( WorldPt( x, y ) );
		::GS_SetObjectBounds( gCBP, fhObject, rect );
	}
	else {
		::GS_AddVertex( gCBP, fhObject, WorldPt(x,y), vtCorner, 0, bRecalcBounds );
	}
}

void VWPolygon2DObj::AddVertex(const VWPoint2D& pt, bool bRecalcBounds/*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode ) {
		WorldRect	rect;
		::GS_GetObjectBounds( gCBP, fhObject, rect );
		rect.Unite( pt );
		::GS_SetObjectBounds( gCBP, fhObject, rect );
	}
	else {
		::GS_AddVertex( gCBP, fhObject, pt, vtCorner, 0, bRecalcBounds );
	}
}

void VWPolygon2DObj::AddCornerVertex(double x, double y, bool bRecalcBounds /*=true*/ )
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode ) {
		WorldRect	rect;
		::GS_GetObjectBounds( gCBP, fhObject, rect );
		rect.Unite( WorldPt( x, y ) );
		::GS_SetObjectBounds( gCBP, fhObject, rect );
	}
	else {
		::GS_AddVertex( gCBP, fhObject, WorldPt(x,y), vtCorner, 0, bRecalcBounds );
	}
}

void VWPolygon2DObj::AddCornerVertex(const VWPoint2D& pt, bool bRecalcBounds /*=true*/ )
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode ) {
		WorldRect	rect;
		::GS_GetObjectBounds( gCBP, fhObject, rect );
		rect.Unite( pt );
		::GS_SetObjectBounds( gCBP, fhObject, rect );
	}
	else {
		::GS_AddVertex( gCBP, fhObject, pt, vtCorner, 0, bRecalcBounds );
	}
}

void VWPolygon2DObj::InsertCornerVertex(size_t beforeIndex, const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	bIndex	= DemoteTo<short>( kVStanev, beforeIndex );
	::GS_InsertVertex( gCBP, fhObject, pt, bIndex+1, vtCorner, 0, bRecalcBounds );
}

void VWPolygon2DObj::SetCornerVertex(size_t index, const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode ) {
		WorldRect	rect;
		::GS_GetObjectBounds( gCBP, fhObject, rect );
		rect.Unite( pt );
		::GS_SetObjectBounds( gCBP, fhObject, rect );
	}
	else {
		short	ind	= DemoteTo<short>( kVStanev, index );
		::GS_SetVertex( gCBP, fhObject, ind+1, pt, vtCorner, 0, bRecalcBounds );
	}
}

void VWPolygon2DObj::AddBezierVertex(const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	::GS_AddVertex( gCBP, fhObject, pt, vtBezier, 0, bRecalcBounds );
}

void VWPolygon2DObj::InsertBezierVertex(size_t beforeIndex, const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	bIndex	= DemoteTo<short>( kVStanev, beforeIndex );
	::GS_InsertVertex( gCBP, fhObject, pt, bIndex+1, vtBezier, 0, bRecalcBounds );
}

void VWPolygon2DObj::SetBezierVertex(size_t index, const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	ind	= DemoteTo<short>( kVStanev, index );
	::GS_SetVertex( gCBP, fhObject, ind+1, pt, vtBezier, 0, bRecalcBounds );
}

void VWPolygon2DObj::AddCubicVertex(const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	::GS_AddVertex( gCBP, fhObject, pt, vtCubic, 0, bRecalcBounds );
}

void VWPolygon2DObj::InsertCubicVertex(size_t beforeIndex, const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	bIndex	= DemoteTo<short>( kVStanev, beforeIndex );
	::GS_InsertVertex( gCBP, fhObject, pt, bIndex+1, vtCubic, 0, bRecalcBounds );
}

void VWPolygon2DObj::SetCubicVertex(size_t index, const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	ind	= DemoteTo<short>( kVStanev, index );
	::GS_SetVertex( gCBP, fhObject, ind+1, pt, vtCubic, 0, bRecalcBounds );
}

void VWPolygon2DObj::AddArcVertex(const VWPoint2D& pt, double dRadius, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	::GS_AddVertex( gCBP, fhObject, pt, vtArc, dRadius, bRecalcBounds );
}

void VWPolygon2DObj::InsertArcVertex(size_t beforeIndex, const VWPoint2D& pt, double dRadius, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	bIndex	= DemoteTo<short>( kVStanev, beforeIndex );
	::GS_InsertVertex( gCBP, fhObject, pt, bIndex+1, vtArc, dRadius, bRecalcBounds );
}

void VWPolygon2DObj::SetArcVertex(size_t index, const VWPoint2D& pt, double dRadius, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	ind	= DemoteTo<short>( kVStanev, index );
	::GS_SetVertex( gCBP, fhObject, ind+1, pt, vtArc, dRadius, bRecalcBounds );
}

void VWPolygon2DObj::AddRadiusVertex(const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	::GS_AddVertex( gCBP, fhObject, pt, vtRadius, 0, bRecalcBounds );
}

void VWPolygon2DObj::InsertRadiusVertex(size_t beforeIndex, const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	bIndex	= DemoteTo<short>( kVStanev, beforeIndex );
	::GS_InsertVertex( gCBP, fhObject, pt, bIndex+1, vtRadius, 0, bRecalcBounds );
}

void VWPolygon2DObj::SetRadiusVertex(size_t index, const VWPoint2D& pt, bool bRecalcBounds /*=true*/)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	ind	= DemoteTo<short>( kVStanev, index );
	::GS_SetVertex( gCBP, fhObject, ind+1, pt, vtRadius, 0, bRecalcBounds );
}

size_t VWPolygon2DObj::GetVertexCount() const
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode )
		return 4;

	return (size_t) ::GS_CountVertices( gCBP, fhObject );
}

void VWPolygon2DObj::DeleteAllVertices()
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short cnt = gSDK->CountVertices( fhObject );
	for(short i=0; i<cnt; i++)
		gSDK->DeleteVertex( fhObject, 1 );
}

void VWPolygon2DObj::DeleteVertex(size_t vertIndex)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( type != kBoxNode );

	short	index	= DemoteTo<short>( kVStanev, vertIndex );
	::GS_DeleteVertex( gCBP, fhObject, index + 1 );
}

VWPoint2D VWPolygon2DObj::GetVertexPoint(size_t index) const
{
	WorldPt		vertex;
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode )
	{
		WorldRectVerts rect;
		gSDK->GetObjectPlanarBounds( fhObject, rect );
		switch( index ) {
			case 0: vertex	= rect.topLeft;		break;
			case 1: vertex	= rect.topRight;	break;
			case 2: vertex	= rect.bottomRight;	break;
			case 3: vertex	= rect.bottomLeft;	break;
			default:	VWFC_ASSERT( false );	break;
		}
	}
	else {
		short		ind		= DemoteTo<short>( kVStanev, index );
		VertexType	type;
		WorldCoord	radius;
		::GS_GetVertex( gCBP, fhObject, ind+1, vertex, type, radius );
	}
	return vertex;
}

void VWPolygon2DObj::SetVertexPoint(size_t index, const VWPoint2D& pt)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode ) {
		WorldRect	rect;
		gSDK->GetObjectBounds( fhObject, rect );
		switch( index ) {
			case 0: rect.left = pt.x; rect.top = pt.y;		break;
			case 1: rect.right = pt.x; rect.top = pt.y;		break;
			case 2: rect.right = pt.x; rect.bottom = pt.y;	break;
			case 3: rect.left = pt.x; rect.bottom = pt.y;	break;
			default:	VWFC_ASSERT( false );	break;
		}
		gSDK->SetObjectBounds( fhObject, rect );
	}
	else {
		short		ind		= DemoteTo<short>( kVStanev, index );
		WorldPt		vertex;
		VertexType	type;
		WorldCoord	radius;
		gSDK->GetVertex( fhObject, ind+1, vertex, type, radius );
		vertex = pt;
		gSDK->SetVertex( fhObject, ind+1, vertex, type, radius );
	}
}

double VWPolygon2DObj::GetVertexRadius(size_t index) const
{
	short	objType		= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( objType != kBoxNode );

	short		ind		= DemoteTo<short>( kVStanev, index );
	WorldPt		vertex;
	VertexType	type;
	WorldCoord	radius;
	::GS_GetVertex( gCBP, fhObject, ind+1, vertex, type, radius );
	VWFC_ASSERT( type == vtArc );
	if ( type == vtArc && DoubleIsNearlyZero( radius ) )
	{
		radius	= gSDK->GetVertexMaxRadius( fhObject, ind+1 );
	}

	return radius;
}

double VWPolygon2DObj::GetVertexMaxRadius(size_t index) const
{
	short	objType		= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( objType != kBoxNode );

	short		ind		= DemoteTo<short>( kVStanev, index );
	WorldPt		vertex;
	VertexType	type;
	WorldCoord	radius;
	::GS_GetVertex( gCBP, fhObject, ind+1, vertex, type, radius );
	
	radius	= 0;
	if ( type == vtArc && DoubleIsNearlyZero( radius ) )
	{
		radius	= gSDK->GetVertexMaxRadius( fhObject, ind+1 );
	}

	return radius;
}

bool VWPolygon2DObj::IsVertexCorner(size_t index) const
{
	short	objType		= gSDK->GetObjectTypeN( fhObject );
	if ( objType == kBoxNode )
		return true;

	short		ind		= DemoteTo<short>( kVStanev, index );
	WorldPt		vertex;
	VertexType	type;
	WorldCoord	radius;
	::GS_GetVertex( gCBP, fhObject, ind+1, vertex, type, radius );
	return type == vtCorner;
}

bool VWPolygon2DObj::IsVertexBezier(size_t index) const
{
	short	objType		= gSDK->GetObjectTypeN( fhObject );
	if ( objType == kBoxNode )
		return false;

	short		ind		= DemoteTo<short>( kVStanev, index );
	WorldPt		vertex;
	VertexType	type;
	WorldCoord	radius;
	::GS_GetVertex( gCBP, fhObject, ind+1, vertex, type, radius );
	return type == vtBezier;
}

bool VWPolygon2DObj::IsVertexCubic(size_t index) const
{
	short	objType		= gSDK->GetObjectTypeN( fhObject );
	if ( objType == kBoxNode )
		return false;

	short		ind		= DemoteTo<short>( kVStanev, index );
	WorldPt		vertex;
	VertexType	type;
	WorldCoord	radius;
	::GS_GetVertex( gCBP, fhObject, ind+1, vertex, type, radius );
	return type == vtCubic;
}

bool VWPolygon2DObj::IsVertexArc(size_t index) const
{
	short	objType		= gSDK->GetObjectTypeN( fhObject );
	if ( objType == kBoxNode )
		return false;

	short		ind		= DemoteTo<short>( kVStanev, index );
	WorldPt		vertex;
	VertexType	type;
	WorldCoord	radius;
	::GS_GetVertex( gCBP, fhObject, ind+1, vertex, type, radius );
	return type == vtArc;
}

bool VWPolygon2DObj::IsVertexRadius(size_t index) const
{
	short	objType		= gSDK->GetObjectTypeN( fhObject );
	if ( objType == kBoxNode )
		return false;

	short		ind		= DemoteTo<short>( kVStanev, index );
	WorldPt		vertex;
	VertexType	type;
	WorldCoord	radius;
	::GS_GetVertex( gCBP, fhObject, ind+1, vertex, type, radius );
	return type == vtRadius;
}

// Identical to GetVertex except that it returns the Bezier control point for cubic spline sections.
VWPoint2D VWPolygon2DObj::GetControlVertex(size_t index) const
{
	short	objType		= gSDK->GetObjectTypeN( fhObject );
	VWFC_ASSERT( objType != kBoxNode );

	short		ind		= DemoteTo<short>( kVStanev, index );
	WorldPt		vertex;
	VertexType	type;
	WorldCoord	radius;
	::GS_GetControlVertex( gCBP, fhObject, ind+1, vertex, type, radius );
	return vertex;
}

bool VWPolygon2DObj::IsVertexVisible(size_t index) const
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode )
		return true;

	short		ind		= DemoteTo<short>( kVStanev, index );
	Boolean		vis		= false;
	::GS_GetVertexVis( gCBP, fhObject, ind, vis );
	return vis ? true : false;
}

void VWPolygon2DObj::SetVertexVisible(size_t index, bool bVisible)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type != kBoxNode ) {
		short		ind		= DemoteTo<short>( kVStanev, index );
		::GS_SetVertexVis( gCBP, fhObject, ind, bVisible );
	}
}

void VWPolygon2DObj::SetAllVertexVisible(bool bVisible)
{
	for(size_t i=0, cnt=this->GetVertexCount(); i<cnt; ++i)
	{
		this->SetVertexVisible( i, bVisible );
	}
	this->SetClosed( bVisible );
}

void VWPolygon2DObj::ApplyVertexVisible(const VWPolygon2D& poly)
{
	size_t polyVertCnt = poly.GetVertexCount();
	for(size_t i=0, cnt=this->GetVertexCount(); i<cnt && i<polyVertCnt; ++i)
	{
		bool bVisible = poly.GetVertexVisible( i );
		this->SetVertexVisible( i, bVisible );
	}
}

bool VWPolygon2DObj::IsClosed() const
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode )
		return true;

	return ::GS_GetPolyShapeClose( gCBP, fhObject ) ? true : false;
}

void VWPolygon2DObj::SetClosed(bool bClosed)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type != kBoxNode ) {
		::GS_SetPolyShapeClose( gCBP, fhObject, bClosed );
	}
}

void VWPolygon2DObj::GetPolygon(VWPolygon2D& outPoly) const
{
	VWPolygon2D::CLockForEdit	outPolyLock( outPoly );

	outPoly.ClearVertices();
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode ) {
		WorldRectVerts	rect;
		gSDK->GetObjectPlanarBounds( fhObject, rect );

		outPoly.AddVertex( rect.topLeft );
		outPoly.AddVertex( rect.topRight );
		outPoly.AddVertex( rect.bottomRight );
		outPoly.AddVertex( rect.bottomLeft );
	}
	else {
		short	len	= ::GS_CountVertices( gCBP, fhObject );
		for(short i=0; i<len; i++) {
			WorldPt		vertex;
			VertexType	type;
			WorldCoord	radius;
			::GS_GetVertex( gCBP, fhObject, i+1, vertex, type, radius );
			Boolean		vis		= false;
			::GS_GetVertexVis( gCBP, fhObject, i, vis );

			outPoly.AddVertex( vertex, (EVertexType) type, radius );
			outPoly.SetVertexVisible( i, vis );
		}

		outPoly.SetClosed( ::GS_GetPolyShapeClose( gCBP, fhObject ) );
	}
}

void VWPolygon2DObj::GetPolygon(VWPolygon3D& outPoly) const
{
	outPoly.ClearVertices();
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kBoxNode ) {
		WorldRectVerts	rect;
		gSDK->GetObjectPlanarBounds( fhObject, rect );

		WorldPt		vertex;
		vertex				= rect.topLeft;
		outPoly.AddVertex( vertex.x, vertex.y, 0 );
		vertex				= rect.topRight;
		outPoly.AddVertex( vertex.x, vertex.y, 0 );
		vertex				= rect.bottomRight;
		outPoly.AddVertex( vertex.x, vertex.y, 0 );
		vertex				= rect.bottomLeft;
		outPoly.AddVertex( vertex.x, vertex.y, 0 );
	}
	else {
		short	len	= ::GS_CountVertices( gCBP, fhObject );
		for(short i=0; i<len; i++) {
			WorldPt		vertex;
			VertexType	type;
			WorldCoord	radius;
			::GS_GetVertex( gCBP, fhObject, i+1, vertex, type, radius );

			outPoly.AddVertex( vertex.x, vertex.y, 0 );
		}

		outPoly.SetClosed( ::GS_GetPolyShapeClose( gCBP, fhObject ) );
	}
}

void VWPolygon2DObj::SetPolygon(const VWPolygon2D& poly)
{
	size_t	existVertCnt	= this->GetVertexCount();
	size_t	vertCnt			= poly.GetVertexCount();

	if ( existVertCnt > vertCnt )
	{
		for(size_t i=0; i < existVertCnt - vertCnt; i++)
		{
			this->DeleteVertex( 0 );
		}
	}

	for(size_t i=0; i<vertCnt; i++)
	{
		const VWPoint2D&	pt	= poly.GetVertexAt( i );
		if(i < existVertCnt)
		{
			switch( poly.GetVertexType( i ) )
			{
				case eVertexType_Corner:	this->SetCornerVertex( i, pt, false );	break;
				case eVertexType_Bezier:	this->SetBezierVertex( i, pt, false ); break;
				case eVertexType_Cubic:		this->SetCubicVertex( i, pt, false ); break;
				case eVertexType_Arc:		this->SetArcVertex( i, pt, poly.GetArcVertexRadius(i), false ); break;
				case eVertexType_Radius:	this->SetRadiusVertex( i, pt, false ); break;
				default:	VWFC_ASSERT( false );	break;
			}
		}
		else
		{
			switch( poly.GetVertexType( i ) )
			{
				case eVertexType_Corner:	this->AddCornerVertex( pt, false );	break;
				case eVertexType_Bezier:	this->AddBezierVertex( pt, false ); break;
				case eVertexType_Cubic:		this->AddCubicVertex( pt, false ); break;
				case eVertexType_Arc:		this->AddArcVertex( pt, poly.GetArcVertexRadius(i), false ); break;
				case eVertexType_Radius:	this->AddRadiusVertex( pt, false ); break;
				default:	VWFC_ASSERT( false );	break;
			}
		}
	}

	this->SetClosed( poly.IsClosed() );
}

double VWPolygon2DObj::GetArea() const
{
	double	area;
	double	perimeter;
	gSDK->Get2DPolyAreaAndPerimeter( fhObject, area, perimeter );
	return area;
}

double VWPolygon2DObj::GetPerimeter() const
{
	double	area;
	double	perimeter;
	gSDK->Get2DPolyAreaAndPerimeter( fhObject, area, perimeter );
	return perimeter;
}

//void VWPolygon2DObj::GetNURBSCurves(VWNURBSCurveArray& curves) const
//{
//	curves.clear();
//	std::vector<Sint32> crvIDs;
//	std::vector<double[2]> intervals;
//	std::vector<Boolean> visibilities;
//	std::vector<short> arcTypes;
//	VCOMPtr<VectorWorks::Math::IPoly2DMath> polyMath = VCOMPtr<VectorWorks::Math::IPoly2DMath>( VectorWorks::Math::IID_Poly2DMath );
//	if(polyMath)
//		polyMath->GetPK_CurvesFromPoly(fhObject, crvIDs, intervals, visibilities, arcTypes);
//	for(size_t i = 0; i < crvIDs.size(); i++)
//	{
//		VWFC::Math::VWNURBSCurve crv(crvIDs.at(i));
//		curves.push_back(crv);
//	}
//
//}

void VWPolygon2DObj::ConvertToPolyline()
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type != kPolylineNode )
		fhObject	= ::GS_ConvertToPolyline( gCBP, fhObject, false );
}

void VWPolygon2DObj::ConvertToPolygon(short res)
{
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type != kPolygonNode ) {
		if ( res == 0 )
			fhObject	= ::GS_ConvertToPolygon( gCBP, fhObject, false );
		else
			fhObject	= ::GS_ConvertToPolygonN( gCBP, fhObject, false, res );
	}
}

void VWPolygon2DObj::AddHoleObject(const VWPolygon2D& poly)
{
	this->ConvertToPolyline();

	VWPolygon2DObj	holeObj( poly );
	holeObj.ConvertToPolyline();
	::GS_AttachAuxObject( gCBP, (MCObjectHandle) holeObj, fhObject );
}

void VWPolygon2DObj::AddHoleObject(const VWPolygon2DObj& poly)
{
	this->ConvertToPolyline();

	VWPolygon2DObj	holeObj( poly );
	holeObj.ConvertToPolyline();
	::GS_AttachAuxObject( gCBP, (MCObjectHandle) holeObj, fhObject );
}

size_t VWPolygon2DObj::GetHoleObjectsCount() const
{
	// only polylines can have openings
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type != kPolylineNode )
		return 0;

	size_t			count	= 0;
	MCObjectHandle	hHole	= ::GS_FindAuxObject( gCBP, fhObject, kPolylineNode );
	while( hHole ) {
		count++;
		MCObjectHandle	hNextAux	= ::GS_NextObject( gCBP, hHole );
		hHole						= ::GS_NextAuxObject( gCBP, hNextAux, kPolylineNode );
	}
	return count;
}

MCObjectHandle  VWPolygon2DObj::GetHoleObjectAt(size_t at)
{
	MCObjectHandle	hHole	= NULL;

	// only polylines can have openings
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kPolylineNode ) {
		size_t		count	= 0;
		hHole				= ::GS_FindAuxObject( gCBP, fhObject, kPolylineNode );
		while( hHole ) {
			if ( at == count )
				break;
			count++;
			MCObjectHandle	hNextAux	= ::GS_NextObject( gCBP, hHole );
			hHole						= ::GS_NextAuxObject( gCBP, hNextAux, kPolylineNode );
		}
	}

	return hHole;
}

void VWPolygon2DObj::GetHoles(TMCObjectHandlesSTLArray& arrOpenings)
{
	// only polylines can have openings
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kPolylineNode )
    {
		MCObjectHandle  hHole	= ::GS_FindAuxObject( gCBP, fhObject, kPolylineNode );
		while( hHole )
        {
			arrOpenings.push_back( hHole );
            
			MCObjectHandle	hNextAux	= ::GS_NextObject( gCBP, hHole );
			hHole						= ::GS_NextAuxObject( gCBP, hNextAux, kPolylineNode );
		}
	}
}

void VWPolygon2DObj::GetHoles(TSTLPolygons2DArray& arrOpenings)
{
	// only polylines can have openings
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kPolylineNode )
    {
		MCObjectHandle  hHole	= ::GS_FindAuxObject( gCBP, fhObject, kPolylineNode );
		while( hHole )
        {
			VWPolygon2DObj  holeObj( hHole );
            VWPolygon2D     poly;
            holeObj.GetPolygon( poly );
            arrOpenings.push_back( poly );
            
			MCObjectHandle	hNextAux	= ::GS_NextObject( gCBP, hHole );
			hHole						= ::GS_NextAuxObject( gCBP, hNextAux, kPolylineNode );
		}
	}
}


void VWPolygon2DObj::GetHoles(TSTLPolygons3DArray& arrOpenings)
{
	// only polylines can have openings
	short	type	= gSDK->GetObjectTypeN( fhObject );
	if ( type == kPolylineNode )
    {
		MCObjectHandle  hHole	= ::GS_FindAuxObject( gCBP, fhObject, kPolylineNode );
		while( hHole )
        {
			VWPolygon2DObj  holeObj( hHole );
            VWPolygon2D     poly;
            holeObj.GetPolygon( poly );
            arrOpenings.push_back( poly );
            
			MCObjectHandle	hNextAux	= ::GS_NextObject( gCBP, hHole );
			hHole						= ::GS_NextAuxObject( gCBP, hNextAux, kPolylineNode );
		}
	}
}

