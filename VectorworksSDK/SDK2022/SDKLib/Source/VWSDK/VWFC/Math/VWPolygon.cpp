//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;

// ---------------------------------------------------------------------------------------------------------------------
VWPolygon2D::CLockForEdit::CLockForEdit(VWPolygon2D& poly)
	: fPoly( poly )
{
	fPoly.fLockedForEdit	= true;
}

VWPolygon2D::CLockForEdit::~CLockForEdit()
{
	fPoly.fLockedForEdit	= false;
	fPoly.RecalculateBoundingBox();
}

// ---------------------------------------------------------------------------------------------------------------------
VWPolygon2D::SVertex::SVertex()
{
	type			= eVertexType_Corner;
	dArcRadius		= 0.0;
	bVisible		= true;
}

VWPolygon2D::SVertex::SVertex(const SVertex& src)
{
	type		= src.type;
	pt			= src.pt;
	dArcRadius	= src.dArcRadius;
	bVisible	= src.bVisible;
}

VWPolygon2D::SVertex::~SVertex()
{
}

VWPolygon2D::SVertex& VWPolygon2D::SVertex::operator=(const VWPolygon2D::SVertex& src)
{
	type		= src.type;
	pt			= src.pt;
	dArcRadius	= src.dArcRadius;
	bVisible	= src.bVisible;

	return	*this;
}

bool VWPolygon2D::SVertex::operator==(const VWPolygon2D::SVertex& that) const
{
	return ( ( type			== that.type		) &&
			 ( pt			== that.pt			) &&
			 ( dArcRadius	== that.dArcRadius	) &&
			 ( bVisible		== that.bVisible	) );
}

bool VWPolygon2D::SVertex::operator!=(const VWPolygon2D::SVertex& that) const
{
	return ! ( this->operator == ( that ) );
}

// ---------------------------------------------------------------------------------------------------------------------
VWPolygon2D::SExtVertex::SExtVertex()
	: SVertex()
{
}

VWPolygon2D::SExtVertex::SExtVertex(const SExtVertex& src)
{
	type			= src.type;
	pt				= src.pt;
	dArcRadius		= src.dArcRadius;
	bVisible		= src.bVisible;
	controlPt		= src.controlPt;
}

VWPolygon2D::SExtVertex::SExtVertex(const SVertex& src)
{
	type			= src.type;
	pt				= src.pt;
	dArcRadius		= src.dArcRadius;
	bVisible		= src.bVisible;
}

VWPolygon2D::SExtVertex::~SExtVertex()
{
}

VWPolygon2D::SExtVertex& VWPolygon2D::SExtVertex::operator=(const VWPolygon2D::SExtVertex& src)
{
	type			= src.type;
	pt				= src.pt;
	dArcRadius		= src.dArcRadius;
	bVisible		= src.bVisible;
	controlPt		= src.controlPt;

	return	*this;
}

VWPolygon2D::SExtVertex& VWPolygon2D::SExtVertex::operator=(const VWPolygon2D::SVertex& src)
{
	type			= src.type;
	pt				= src.pt;
	dArcRadius		= src.dArcRadius;
	bVisible		= src.bVisible;

	return	*this;
}

bool VWPolygon2D::SExtVertex::operator==(const VWPolygon2D::SExtVertex& that) const
{
	return ( ( type			== that.type		) &&
			 ( pt			== that.pt			) &&
			 ( dArcRadius	== that.dArcRadius	) &&
			 ( bVisible		== that.bVisible	) &&
			 ( controlPt	== that.controlPt	) );
}

bool VWPolygon2D::SExtVertex::operator!=(const VWPolygon2D::SExtVertex& that) const
{
	return ! ( this->operator == ( that ) );
}

// ---------------------------------------------------------------------------------------------------------------------
VWPolygon2D::VWPolygon2D()
{
	fdMinX			= 0;
	fdMaxX			= 0;
	fdMinY			= 0;
	fdMaxY			= 0;
	fbIsClosed		= true;
	fLockedForEdit	= false;
}

VWPolygon2D::VWPolygon2D(std::initializer_list<VWPoint2D> src)
	: VWPolygon2D( TSTLPoints2DArray( src ) )
{
}

VWPolygon2D::VWPolygon2D(const TSTLPoints2DArray& src)
{
	farrVertices.reserve(src.size());
	// temporarily suppresses recalculating of the polygon bounding box.
	fLockedForEdit	= true;

	size_t	len		= src.size();
	for ( size_t i = 0 ; i < len ; ++ i )
	{
		this->AddVertex( src[ i ] );
	}

	fbIsClosed		= false;
	fLockedForEdit	= false;	// unlock.

	// recalculate the bounding box at the end.
	this->RecalculateBoundingBox();
}

VWPolygon2D::VWPolygon2D(const TSTLPoints2DVWArray& src)
{
	// temporarily suppresses recalculating of the polygon bounding box.
	fLockedForEdit	= true;

	size_t	len		= src.size();
	for ( size_t i = 0 ; i < len ; ++ i )
	{
		this->AddVertex( src[ i ] );
	}

	fbIsClosed		= false;
	fLockedForEdit	= false;	// unlock.

	// recalculate the bounding box at the end.
	this->RecalculateBoundingBox();
}

VWPolygon2D::VWPolygon2D(IPolyDefPtr pPolygonDef)
{
	fdMinX			= 0;
	fdMaxX			= 0;
	fdMinY			= 0;
	fdMaxY			= 0;
	fbIsClosed		= true;
	fLockedForEdit	= false;

	this->operator = ( pPolygonDef );
}

VWPolygon2D::VWPolygon2D(const VWPolygon2D& src)
{
	fdMinX				= src.fdMinX;
	fdMaxX				= src.fdMaxX;
	fdMinY				= src.fdMinY;
	fdMaxY				= src.fdMaxY;
	fbIsClosed			= src.fbIsClosed;
	fLockedForEdit		= src.fLockedForEdit;

	size_t		len		= src.farrVertices.size();
	for(size_t i=0; i<len; i++)
		farrVertices.push_back( src.farrVertices[ i ] );
}


VWPolygon2D::~VWPolygon2D()
{
	farrVertices.clear();
}

bool VWPolygon2D::operator==(const VWPolygon2D& poly) const
{
	bool result = false;
	size_t cnt = farrVertices.size();
	if ( cnt == poly.farrVertices.size() )
	{
		result = true;
		for(size_t i=0; i<cnt; i++)
		{
			if ( farrVertices[i] != poly.farrVertices[i] )
			{
				result = false;
				break;
			}
		}
	}

	return result;
}

bool VWPolygon2D::operator!=(const VWPolygon2D& poly) const
{
	return ! this->operator== ( poly );
}

VWPolygon2D& VWPolygon2D::operator=(const TSTLPoints2DArray& src)
{
	this->ClearVertices();

	NNA_SCOPE
	{
		// temporarily suppresses recalculating of the polygon bounding box.
		fLockedForEdit		= true;

		size_t		len		= src.size();
		for ( size_t i = 0 ; i < len ; ++ i )
		{
			this->AddVertex( src[ i ] );
		}

		// recalculate the bounding box at the end.
		this->RecalculateBoundingBox();

		// unlock.
		fLockedForEdit		= false;
	}

	// result.
	return	( *this );
}

VWPolygon2D& VWPolygon2D::operator=(const TSTLPoints2DVWArray& src)
{
	this->ClearVertices();

	NNA_SCOPE
	{
		// temporarily suppresses recalculating of the polygon bounding box.
		fLockedForEdit		= true;

		size_t		len		= src.size();
		for ( size_t i = 0 ; i < len ; ++ i )
		{
			this->AddVertex( src[ i ] );
		}

		// recalculate the bounding box at the end.
		this->RecalculateBoundingBox();

		// unlock.
		fLockedForEdit		= false;
	}

	// result.
	return	( *this );
}

VWPolygon2D& VWPolygon2D::operator=(IPolyDefPtr pPolygonDef)
{
	this->ClearVertices();
	if ( pPolygonDef ) {
		Uint32	cnt		= 0;
		pPolygonDef->GetVertexCount( cnt );
		for(Uint32 i=0; i<cnt; i++) {
			WorldPt		pt;
			EVertexType	vertType	= eVertexType_Corner;
			double		dRadius		= 0;

			pPolygonDef->GetVertexAt( i, pt );
			pPolygonDef->GetVertexType( i, vertType );
			pPolygonDef->GetArcVertexRadius( i, dRadius );
			bool	bVisible	= VCOM_SUCCEEDED( pPolygonDef->GetVertexVisible( i ) );

			SVertex		vertex;
			vertex.type				= vertType;
			vertex.pt.x				= pt.x;
			vertex.pt.y				= pt.y;
			vertex.dArcRadius		= dRadius;
			vertex.bVisible			= bVisible;
			farrVertices.push_back( vertex );
		}
		pPolygonDef->IsClosed( fbIsClosed );

		this->RecalculateBoundingBox();
	}
	return *this;
}

VWPolygon2D& VWPolygon2D::operator=(const VWPolygon2D& src)
{
	if ( this != &src )
	{
		fdMinX				= src.fdMinX;
		fdMaxX				= src.fdMaxX;
		fdMinY				= src.fdMinY;
		fdMaxY				= src.fdMaxY;
		fbIsClosed			= src.fbIsClosed;

		farrVertices.clear();
		size_t		len		= src.farrVertices.size();
		for(size_t i=0; i<len; i++)
			farrVertices.push_back( src.farrVertices[ i ] );
	}

	return *this;
}

void VWPolygon2D::SetPolygon(const TSTLPoints2DArray& src)
{
	(*this) = src;
}

void VWPolygon2D::SetPolygon(const TSTLPoints2DVWArray& src)
{
	(*this) = src;
}

void VWPolygon2D::SetPolygon(IPolyDefPtr pPolygonDef)
{
	(*this) = pPolygonDef;
}

void VWPolygon2D::GetPolygon(TSTLPoints2DArray& out) const
{
	out.clear();
	size_t		len		= farrVertices.size();
	for(size_t i=0; i<len; i++)
		out.push_back( farrVertices[i].pt );
}

void VWPolygon2D::GetPolygon(TSTLPoints2DVWArray& out) const
{
	out.clear();
	size_t		len		= farrVertices.size();
	for(size_t i=0; i<len; i++)
		out.push_back( farrVertices[i].pt );
}

void VWPolygon2D::GetPolygon(IPolyDefPtr& pPolygonDef) const
{
	if ( pPolygonDef == nullptr )
		pPolygonDef.Query( IID_PolyDef );
	
	if ( pPolygonDef ) {
		pPolygonDef->ClearVertices();
		size_t		len		= farrVertices.size();
		for(size_t i=0; i<len; i++) {
			const SVertex&	vertex = farrVertices[ i ];

			if ( vertex.type == eVertexType_Arc ) {
				pPolygonDef->AddVertex( vertex.pt, vertex.dArcRadius );
			}
			else {
				pPolygonDef->AddVertex( vertex.pt, vertex.type );
			}
		}
		pPolygonDef->SetClosed( fbIsClosed );
	}
}

void VWPolygon2D::ClearVertices()
{
	fdMinX			= 0;
	fdMaxX			= 0;
	fdMinY			= 0;
	fdMaxY			= 0;
	farrVertices.clear();
	fbIsClosed		= true;
}

void VWPolygon2D::PopBack()
{
	this->ClearVertex( this->GetVertexCount() - 1 );
}

void VWPolygon2D::AddVertex(const VWPoint2D& pt, EVertexType type /*=eVertexType_Corner*/, double dArcRadius /*=0*/)
{
	SVertex		vertex;
	vertex.type				= type;
	vertex.pt				= pt;
	vertex.dArcRadius		= dArcRadius;
	vertex.bVisible			= true;
	farrVertices.push_back( vertex );

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

void VWPolygon2D::AddVertex(double x, double y, EVertexType type /*=eVertexType_Corner*/, double dArcRadius /*=0*/)
{
	SVertex		vertex;
	vertex.type				= type;
	vertex.pt.x				= x;
	vertex.pt.y				= y;
	vertex.dArcRadius		= dArcRadius;
	vertex.bVisible			= true;
	farrVertices.push_back( vertex );

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

void VWPolygon2D::AddVertex(const VWPolygon2D& poly)
{
	size_t	vertsCnt	= poly.farrVertices.size();
	for(size_t i=0; i<vertsCnt; i++) {
		const SVertex&	vertex = poly.farrVertices[ i ];
		farrVertices.push_back( vertex );
	}

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

void VWPolygon2D::InsertVertex(size_t at, double x, double y, EVertexType type /*=eVertexType_Corner*/, double dArcRadius /*=0*/)
{
	SVertex		vertex;
	vertex.type				= type;
	vertex.pt.x				= x;
	vertex.pt.y				= y;
	vertex.dArcRadius		= dArcRadius;
	vertex.bVisible			= true;
	farrVertices.insert( farrVertices.begin() + at, vertex );

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

void VWPolygon2D::InsertVertex(size_t at, const VWPoint2D& pt, EVertexType type /*=eVertexType_Corner*/, double dArcRadius /*=0*/)
{
	SVertex		vertex;
	vertex.type				= type;
	vertex.pt				= pt;
	vertex.dArcRadius		= dArcRadius;
	vertex.bVisible			= true;
	farrVertices.insert( farrVertices.begin() + at, vertex );

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

void VWPolygon2D::InsertVertex(size_t at, const VWPolygon2D& poly)
{
	size_t	vertsCnt	= poly.farrVertices.size();
	for(size_t i=0; i<vertsCnt; i++) {
		const SVertex&	vertex = poly.farrVertices[ vertsCnt - i - 1 ];
		farrVertices.insert( farrVertices.begin() + at, vertex );
	}

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

void VWPolygon2D::ClearVertex(size_t at)
{
	farrVertices.erase( farrVertices.begin() + at );
	this->RecalculateBoundingBox();
}

size_t VWPolygon2D::GetVertexCount() const
{
	return farrVertices.size();
}

bool VWPolygon2D::IsEmpty() const
{
	return farrVertices.size() <= 1;
}

VWPoint2D& VWPolygon2D::operator[](size_t at)
{
	return this->GetVertexAt( at );
}

const VWPoint2D& VWPolygon2D::operator[](size_t at) const
{
	return this->GetVertexAt( at );
}

VWPoint2D& VWPolygon2D::Back()
{
	return this->GetVertexAt( this->GetVertexCount() - 1 );
}

const VWPoint2D& VWPolygon2D::Back() const
{
	return this->GetVertexAt( this->GetVertexCount() - 1 );
}

VWPoint2D& VWPolygon2D::GetVertexAt(size_t at, bool bLoopVerts /*=false*/)
{
	if ( bLoopVerts ) {
		// loop the vertex indeces inside the array
		VWFC_ASSERT( farrVertices.size() > 0 );
		at		= at % farrVertices.size();
	}
	else {
		VWFC_ASSERT( at < farrVertices.size() );
	}
	return farrVertices[ at ].pt;
}

const VWPoint2D& VWPolygon2D::GetVertexAt(size_t at, bool bLoopVerts /*=false*/) const
{
	if ( bLoopVerts ) {
		// loop the vertex indeces inside the array
		VWFC_ASSERT( farrVertices.size() > 0 );
		at		= at % farrVertices.size();
	}
	else {
		VWFC_ASSERT( at < farrVertices.size() );
	}
	return farrVertices[ at ].pt;
}

EVertexType VWPolygon2D::GetVertexType(size_t at) const
{
	VWFC_ASSERT( at < farrVertices.size() );
	return farrVertices[ at ].type;
}

void VWPolygon2D::SetVertexType(size_t at, EVertexType type)
{
	VWFC_ASSERT( at < farrVertices.size() );
	farrVertices[ at ].type = type;
}

double VWPolygon2D::GetArcVertexRadius(size_t at) const
{
	VWFC_ASSERT( at < farrVertices.size() );
	VWFC_ASSERT( farrVertices[ at ].type == eVertexType_Arc );
	return farrVertices[ at ].dArcRadius;
}

void VWPolygon2D::SetArcVertexRadius(size_t at, double dRadius)
{
	VWFC_ASSERT( at < farrVertices.size() );
	VWFC_ASSERT( farrVertices[ at ].type == eVertexType_Arc );
	farrVertices[ at ].dArcRadius	= dRadius;
}

bool VWPolygon2D::GetVertexVisible(size_t at) const
{
	VWFC_ASSERT( at < farrVertices.size() );
	return farrVertices[ at ].bVisible;
}

void VWPolygon2D::SetVertexVisible(size_t at, bool bVisible)
{
	VWFC_ASSERT( at < farrVertices.size() );
	farrVertices[ at ].bVisible		= bVisible;
}

// return a line from (at, at+1) vertex (at the end the line is (len-1, 0)
VWLine2D VWPolygon2D::GetLineAt(size_t at) const
{
	VWFC_ASSERT( at < farrVertices.size() );
	size_t	next	= at + 1;
	if ( next >= farrVertices.size() )
		next	= 0;

	return VWLine2D( farrVertices[ at ].pt, farrVertices[ next ].pt );
}

// checks whether the vertex is collinear in the polygon context (i.e. is collinear with respect to its neighboring vertices).
bool VWPolygon2D::IsVertexCollinear(size_t at, double epsCollinear/*=VWPoint2D::sEpsilonCollinear*/) const
{
	// init.
	bool			isCollinear			= false;

	// validate.
	VWFC_ASSERT( ( at < farrVertices.size() ) );

	VWPoint2D		prevPt, nextPt;

	// get the previous and the next 'apposite' polygon points (not too close).
	if ( this->GetPrevAppositePt( at, prevPt, VWPoint2D::sEpsilon ) &&
		 this->GetNextAppositePt( at, nextPt, VWPoint2D::sEpsilon ) )
	{
		isCollinear	= VWPoint2D::ArePointsCollinear( prevPt, farrVertices[ at ].pt, nextPt, epsCollinear );
	}
	//else: could happen in degenerate or open polygon.

	// result.
	return	( isCollinear );
}

// checks if the polygon has at least one non-corner vertex.
bool VWPolygon2D::HasNonCornerVertices() const
{
	// init.
	bool	hasNonCornerVerts	= false;
	size_t	vertsCnt			= this->GetVertexCount();

	for ( size_t i = 0 ; i < vertsCnt ; ++ i )
	{
		if ( this->GetVertexType( i ) != eVertexType_Corner )
		{
			hasNonCornerVerts	= true;
			break;				// found. stop.
		}
	}

	// result.
	return	( hasNonCornerVerts );
}

void VWPolygon2D::RecalculateBoundingBox()
{
	fdMinX		= 0;
	fdMaxX		= 0;
	fdMinY		= 0;
	fdMaxY		= 0;

	size_t	len	= farrVertices.size();
	if ( len > 0 )
	{
		const	VWPoint2D&	pt	= farrVertices[ 0 ].pt;
		fdMinX		= pt.x;
		fdMaxX		= pt.x;
		fdMinY		= pt.y;
		fdMaxY		= pt.y;

		for(size_t i=1; i<len; i++)
		{
			const	VWPoint2D&	pt	= farrVertices[ i ].pt;
			fdMinX		= min( fdMinX, pt.x );
			fdMaxX		= max( fdMaxX, pt.x );
			fdMinY		= min( fdMinY, pt.y );
			fdMaxY		= max( fdMaxY, pt.y );
		}
	}
}

void VWPolygon2D::SetClosed(bool isClosed)
{
	fbIsClosed		= isClosed;
	size_t		len	= farrVertices.size();
	if ( len > 0 )
	{
		farrVertices[ len-1 ].bVisible	= isClosed;
	}
}

bool VWPolygon2D::IsClosed() const
{
	return fbIsClosed;
}

void VWPolygon2D::SetAllVertexVisible(bool bVisible)
{
	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++) {
		farrVertices[ i ].bVisible		= bVisible;
	}
}

// --------------------------------------------------------------------------------------------------------
// correctly opens an polyline.
// the challenging case is when first or last poly vertex is non-corner.
// in this case a part of the resulting open polyline will polygonized but the shape will be preserved.
void VWPolygon2D::OpenPolyline()
{
	// epsilon for checking collinearity.
	const double					kEpsCollinear		= 0.025;

	// examine the input polyline.
	if ( this->IsClosed() )							// a closed poly. so it can be opened.
	{
		size_t						vertCnt				= this->GetVertexCount();

		if ( vertCnt > 1 )								// not empty (at least 2 vertices).
		{
			bool					isFirstCorner		= ( this->GetVertexType( 0 )			== eVertexType_Corner );
			bool					isLastCorner		= ( this->GetVertexType( vertCnt - 1 )	== eVertexType_Corner );

			if ( isFirstCorner && isLastCorner )
			{
				// both first and end poly vertices are corners, so simply open the poly.
				this->SetClosed( false );
			}
			else
			{
				VWPolygon2D			subPolygon;
				size_t				subBegIndex, subEndIndex;
				double				distToProj;
				Sint32				onSegIndex;
				VWPoint2D			projPt;

				// get the non-corner ending vertex.
				size_t				nonCornerIndex = 0;
				if		( ! isFirstCorner	)	nonCornerIndex	= 0;
				else if ( ! isLastCorner	)	nonCornerIndex	= ( vertCnt - 1 );
				else							ASSERTN( kVStanev, false );	// must not happen. check !

				// get polygonized part around the non-corner vertex.
				if ( this->GetPolygonizedPartOfClosedPoly( nonCornerIndex, subPolygon, subBegIndex, subEndIndex ) )
				{
					size_t			subCnt				= subPolygon.GetVertexCount();

					// change the beginning and ending of the polyline. add parts of the polygonization at its beginning and ending.

					// get where the first and the last vertices projections on the polygonized part are.
					size_t			fromIndex			= 0;
					size_t			toIndex				= ( subCnt - 1 );

					// get closest projection of the first vertex.
					VWPoint2D		firstPtProj			= subPolygon.GetClosestPtOnPoly( this->GetVertexAt( 0 ), distToProj, onSegIndex );
					fromIndex							= ( onSegIndex + 1 ) % subCnt;	// from second segment vertex.

					// get closest projection of the last vertex.
					VWPoint2D		lastPtProj			= subPolygon.GetClosestPtOnPoly( this->GetVertexAt( vertCnt - 1 ), distToProj, onSegIndex );
					toIndex								= onSegIndex;					// to first segment vertex.

					// prepare a new polyline.

					VWPolygon2D	openPolyline;
					openPolyline.SetClosed( false );

					NNA_SCOPE
					{
						// XXX Bobi:
						// this temporary suppresses recalculating of the poly bounding box - ...
						// ... it's a slow operation and not needed while collecting points.
						VWPolygon2D::CLockForEdit	outPolylineLock( openPolyline );

						if ( subPolygon.IsClosed() )	// the sub-polygon is closed.
						{
							// means that we have polygonization of the whole polyline.

							// get the closed polygon part except the segments between first and the last vertices projections.
							VWPolygon2D	tempPolygon;
							subPolygon.GetPartOfClosedPolyFromTo( fromIndex, toIndex, tempPolygon );

							// compose the open poly.
							openPolyline.AddVertex( firstPtProj );	// the start vertex.
							openPolyline.AddVertex( tempPolygon );
							openPolyline.AddVertex( lastPtProj );	// the end vertex.

							// clean up collinear vertices. Note: there are only corner vertices.
							openPolyline.CleanUp_FeaturePreserving( false, kEpsCollinear, VWPoint2D::sEpsilon );
						}
						else
						{
							// add part of the polygonization at its beginning.

							openPolyline.AddVertex( firstPtProj );	// the start vertex.

							for ( size_t i = fromIndex ; i < ( subCnt - 1 ) ; ++ i )
							{
								openPolyline.AddVertex( subPolygon.GetVertexAt( i ) );
							}

							// clean up collinear vertices. Note: at this stage there are only corner vertices.
							openPolyline.CleanUp_FeaturePreserving( false, kEpsCollinear, VWPoint2D::sEpsilon );

							// add the not polygonized part.

							// validation.
							ASSERTN( kVStanev, ( subEndIndex <= subBegIndex ) );	// not expected. check !

							// compose.
							VWPolygon2D	nonCornerPart;
							this->GetPartOfClosedPolyFromTo( subEndIndex, subBegIndex, nonCornerPart );

							// add.
							openPolyline.AddVertex( nonCornerPart );

							// add part of the polygonization at its ending.

							// compose.
							VWPolygon2D	cornerPart;
							cornerPart.SetClosed( false );

							for ( size_t i = 1 ; i < ( toIndex + 1 ) ; ++ i )
							{
								cornerPart.AddVertex( subPolygon.GetVertexAt( i ) );
							}
							cornerPart.AddVertex( lastPtProj );		// the end vertex.

							// clean up collinear vertices. Note: there are only corner vertices.
							cornerPart.CleanUp_FeaturePreserving( false, kEpsCollinear, VWPoint2D::sEpsilon );

							// add.
							openPolyline.AddVertex( cornerPart );
						}
					}

					// prepare the result.
					operator=( openPolyline );
				}
				else
				{
					ASSERTN( kVStanev, false );			// not expected. check !
				}
			}
		}
		else											// an empty poly.
		{
			ASSERTN( kVStanev, false );					// bad input. check !
			this->SetClosed( false );					// force open.
		}
	}
}

void VWPolygon2D::GetPolygonBounds(double& outMinX, double& outMaxX, double& outMinY, double& outMaxY) const
{
	// not expected the polygon to be locked for edit.
	VWFC_ASSERT( ! fLockedForEdit );

	outMinX		= fdMinX;
	outMaxX		= fdMaxX;
	outMinY		= fdMinY;
	outMaxY		= fdMaxY;
}

VWRectangle2D VWPolygon2D::GetPolygonBounds() const
{
	// not expected the polygon to be locked for edit.
	VWFC_ASSERT( ! fLockedForEdit );

	return VWRectangle2D( fdMinX, fdMaxX, fdMaxY, fdMinY );
}

VWPoint2D VWPolygon2D::GetPolygonBoundsCenter() const
{
	// not expected the polygon to be locked for edit.
	VWFC_ASSERT( ! fLockedForEdit );

	return VWPoint2D( (fdMinX+fdMaxX)/2, (fdMinY+fdMaxY)/2 );
}

// reverse the order of the points (if CW to CCW or CCW to CW)
void VWPolygon2D::ReversePoints(const bool& kbDoFullReversion  /* = false */)
{
 	size_t	len	= farrVertices.size();

	if (kbDoFullReversion && len > 1)
	{
		bool kbLastVertexIsVisible = farrVertices[ len - 1 ].bVisible;
		for(size_t i=len-1; i>0; i--)
			farrVertices[ i ].bVisible = farrVertices[ i - 1 ].bVisible;

		farrVertices[ 0 ].bVisible = kbLastVertexIsVisible;
	}

	for(size_t i=0; i<len / 2; i++)
	{
		/*
			Get the vertices to be exchanged as references, so that to avoid the multiple
			use of the array access operator. A problem could arise if copies of the vertices
			are generated and modified instead of editing the elements of the farrVertices STL vector.
			Actually, STL vector's operator[] returns either a modifiable reference or a constant
			reference to the visited element. Therefore, it is guaranteed that the following expression:
			"SVertex& leftVertex = farrVertices[ i ];" won't make the compiler copy the vertex
			"farrVertices[ i ]" to a temporary implicit ( hidden ) variable of SVertex type
			and point the reference "SVertex& leftVertex" to it.
			Another possible flaw when using references to dynamically allocated data
			would occur if the it is expanded or diminished e.g. the reserved memory
			for the data is reallocated. Then there is a great chance to lose the reference.
			This case is impossible to be encountered, since we are only modifying the data
			e.g. what farrVertices points to, not adding or removing data elements
			( changing its size thus changing the value held by farrVertices ).
		*/
		SVertex&		leftVertex 			= farrVertices[ i ];
		VWPoint2D		temp				= leftVertex.pt;
		const size_t	knRghtVertexIndex	= len-i-1;
		SVertex&		rghtVertex 			= farrVertices[ knRghtVertexIndex ];
		leftVertex.pt						= rghtVertex.pt;
		rghtVertex.pt						= temp;

		if (kbDoFullReversion) {
			// Obtain the additional data from the LEFT vertex.
			const EVertexType	kLeftVertexType			= leftVertex.type;
			const double		kdLeftVertexArcRadius	= leftVertex.dArcRadius;
			const bool			kbLeftVertexIsVisible	= leftVertex.bVisible;

			// Copy the data of the RIGHT vertex to that of the LEFT one.
			leftVertex.type			= rghtVertex.type;
			leftVertex.dArcRadius	= rghtVertex.dArcRadius;
			leftVertex.bVisible		= rghtVertex.bVisible;

			// Set the data of the RIGHT vertex with that, which has already been
			// gathered above from the LEFT vertex.
			rghtVertex.type			= kLeftVertexType;
			rghtVertex.dArcRadius	= kdLeftVertexArcRadius;
			rghtVertex.bVisible		= kbLeftVertexIsVisible;
		}
	}

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

// return true if the passed polygon has more than 3 different vertices
bool VWPolygon2D::IsValidPolygon(double dEpsilon) const
{
	size_t	len	= farrVertices.size();
	if ( len < 3 )
		return false;

	size_t		count	= 1;
	VWPoint2D	pt		= farrVertices[ 0 ].pt;
	for(size_t i=1; i<len; i++)
	{
		double_gs	dist	= ( pt - farrVertices[ i ].pt ).Magnitude();
		if ( dist > dEpsilon )
		{
			count++;
			if ( count >= 3 )
				return true;
		}

		pt			= farrVertices[ i ].pt;
	}

	return count >= 3;
}

// removed all same points in the polygon
void VWPolygon2D::CleanUpPolygon(double dEpsilon)
{
	double						sqrEps	= sqr( dEpsilon );

	VWPoint2D					lastPt;
	TVertexArray::iterator		it		= farrVertices.begin();
	while( it != farrVertices.end() )
	{
		if ( it == farrVertices.begin() ) 
		{
			lastPt		= it->pt;
			++it;
		}
		else
		{
			double_gs	sqrDist	= ( lastPt - it->pt ).MagnitudeSquared();
			if ( sqrDist < sqrEps )
			{
				// remove the unnecessary point
				farrVertices.erase( it );
				// start all over
				it		= farrVertices.begin();
			}
			else {
				lastPt		= it->pt;
				++it;
			}
		}
	}

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

// This function works as follows depending on 'doClosenessCheck':
// ( doClosenessCheck == false )	- clean up all polygon vertices which are collinear with their neighbors.
// ( doClosenessCheck == true  )	- clean up all polygon vertices which are collinear with their neighbors and are too close to their neighbors.
// Note: works on polygon with only corner vertices.
void VWPolygon2D::CleanUp_FeaturePreserving(bool doClosenessCheck, double epsCollinear, double epsCloseness)
{
	size_t						vertCnt		= this->GetVertexCount();

	VWFC_ASSERT( vertCnt > 1 );	// empty poly. check !

	if ( vertCnt > 2 )			// has at least 3 vertices (could clean it up).
	{
		double					sqrEps		= sqr( epsCloseness );

		bool					isClosed	= this->IsClosed();

		// init.
		size_t					endChkInx	= ( vertCnt - 1 );	// last vertex index.
		size_t					begChkInx	= 0;

		if ( ! isClosed )
		{
			-- endChkInx;		// to last but one vertex index.
			++ begChkInx;		// to 1.
		}

		// note:
		// it is expected that 'endChkInx' >= 'begChkInx' and both be less than 'vertCnt'.
		VWFC_ASSERT( ( endChkInx < vertCnt ) && ( begChkInx < vertCnt ) && ( endChkInx >= begChkInx ) );

		ptrdiff_t				it			= endChkInx;		// start from.

		while ( it >= (ptrdiff_t) begChkInx )					// loop the polygon vertices backwards.
		{
			size_t				thisInx		= it;				// this index.

			size_t				prevInx;	// index of previous poly point.
			if ( isClosed )		prevInx		= ( thisInx < endChkInx ) ? ( thisInx + 1 ) : 0;
			else				prevInx		= ( thisInx + 1 );

			size_t				nextInx;	// index of next poly point.
			if ( isClosed )		nextInx		= ( thisInx > 0 ) ? ( thisInx - 1 ) : endChkInx;
			else				nextInx		= ( thisInx - 1 );

			const VWPoint2D&	thisPt		= this->GetVertexAt( thisInx );
			const VWPoint2D&	prevPt		= this->GetVertexAt( prevInx );
			const VWPoint2D&	nextPt		= this->GetVertexAt( nextInx );

			bool				doRemove	= false;

			VWPoint2D			vecToPrev	= ( prevPt - thisPt ).Normalize();
			VWPoint2D			vecToNext	= ( nextPt - thisPt ).Normalize();

			// check if the three points lie on a line.
			if ( MathUtils::Equalish( vecToPrev.CrossProductMagnitude( vecToNext ), 0.0, epsCollinear ) )
			{
				if ( doClosenessCheck )
				{
					if ( ( thisPt.DistanceSquaredTo( prevPt ) < sqrEps ) ||		// distance to previous vertex is too small.
						 ( thisPt.DistanceSquaredTo( nextPt ) < sqrEps ) )		// distance to next vertex is too small.
					{
						doRemove			= true;
					}
				}
				else
				{
					doRemove	= true;
				}
			}

			if ( doRemove )
			{
				farrVertices.erase( farrVertices.begin() + it );

				// note: decrease both the last checkable index and the counter.

				-- endChkInx;	// update last checkable element index.
				-- it;			// decrease (go to next, no need to check again the previous).

				if ( endChkInx < 1 )		// no more checkable (single polygon point left).
				{
					break;		// done - stop.
				}
			}
			else
			{
				-- it;			// decrease counter (go to next).
			}
		}

		if ( ! fLockedForEdit )
		{
			this->RecalculateBoundingBox();
		}
	}
}

// This function removes polygon "jags" (such "jags" can be a result from cutting, clipping, offsetting, etc.).
// It also removes all polygon vertices which are collinear with their neighbors.
// 'maxJagAngle'	- a threshold for recognizing of a "jag"		(Note: this must be an acute angle !).
// Note: works on polygon with corner vertices only.
void VWPolygon2D::CleanUp_RemoveJags(double maxJagAngle, double epsCollinear, double epsCloseness)
{
	// if an angle is below following threshold and it is a part of a 'S' shape then then this is a "jag".
	const double			kMaxAngForSureJag		= 5.0;	// 5 degrees.

	// a threshold constant for the "jag ratio" ( longer adjacent edge / shorter adjacent edge ) for a PI/2 angle between vectors.
	const double			kMaxJagRatioAtPIOver2	= 1.5;

	// XXX Bobi:
	// removing from a polygon with "jags" the vertices collinear to their neighbors might produce a self-intersecting polygon.
	// this could happen as the collinearity check uses epsilon and removing a collinear vertex could very slightly change the polygon's geometry.
	// no matter that it is a negligible change, if at the neighbors of the removed there are "jags", this could lead to self-intersection.
	// so we need to first remove all polygon "jags" before removing the collinear vertices.

	// first remove all polygon "jags".

	size_t							vertCnt			= this->GetVertexCount();
	bool							isClosed		= this->IsClosed();

	size_t							procCnt			= vertCnt;
	size_t							startFrom		= 0;
	if ( ! isClosed )
	{
		-- procCnt;
		++ startFrom;
	}

	// loop polygon vertices.
	size_t							i				= startFrom;
	while ( i < procCnt )
	{
		size_t						thisInx			= i;	// this index.

		size_t						prevInx;		// index of previous poly point.
		if ( isClosed )				prevInx			= ( thisInx > 0 ) ? ( thisInx - 1 ) : ( procCnt - 1 );	// note that ( vertCnt == procCnt ) here !
		else						prevInx			= ( thisInx - 1 );										// note that ( thisInx > 0 ) here !

		size_t						nextInx;		// index of next poly point.
		if ( isClosed )				nextInx			= ( thisInx + 1 ) % procCnt;
		else						nextInx			= ( thisInx + 1 );

		VWPoint2D&					thisPt			= this->GetVertexAt( thisInx );
		const VWPoint2D&			prevPt			= this->GetVertexAt( prevInx );
		const VWPoint2D&			nextPt			= this->GetVertexAt( nextInx );

		VWPoint2D					vecToPrev		= ( prevPt - thisPt );
		VWPoint2D					vecToNext		= ( nextPt - thisPt );

		double						lenToPrev		= vecToPrev.Magnitude();
		double						lenToNext		= vecToNext.Magnitude();

		// check if it is a correct polygon point (not too close to its neighbors).
		bool						hasCorrectRatio	= ( MathUtils::Greaterish( lenToPrev, 0.0, epsCloseness ) &&	
														MathUtils::Greaterish( lenToNext, 0.0, epsCloseness ) );

		VWPoint2D					intersPt;
		bool						isJag			= false;
		bool						isSShape		= false;
		bool						canMove			= false;
		bool						doMoveToNext;
		size_t						ppInx			= size_t(-1);	// for the index prior to the previous (init as an invalid index).

		if ( hasCorrectRatio )						// point is not too close to its neighbors.
		{
			// normalize (note that lengths are not zero).
			vecToPrev								/= lenToPrev;
			vecToNext								/= lenToNext;

			// get the angle between vectors (in radians and in degrees).
			double					angBetVecsR		= VWPoint2D::CalcAngleBetween( vecToPrev, vecToNext, true );
			double					angBetVecsD		= ( angBetVecsR * kDegreesPerRadian );

			// check angle between vectors (first criterion).
			if ( angBetVecsD <= maxJagAngle )		// note that the 'maxJagAngle' is in degrees !
			{
				VWPoint2D			intersPtOnNext, intersPtOnPrev;
				bool				canMoveOnNext	= false;
				bool				canMoveOnPrev	= false;
				double				propRatio1, propRatio2;

				// check the previous poly segment.
				if ( isClosed || ( prevInx > 0 ) )	// there is prior to the previous index.
				{
					// get the index prior to the previous index.
					ppInx							= ( prevInx > 0 ) ? ( prevInx - 1 ) : ( vertCnt - 1 );
					const VWPoint2D&	ppPt		= this->GetVertexAt( ppInx );

					// check if it is a 'S' shape and whether this point can be removed/moved.
					isSShape						= VWPolygon2D::CheckForSShape( 	ppPt, prevPt, thisPt, nextPt,
																					vecToPrev, vecToNext, epsCloseness,
																					intersPtOnNext, canMoveOnNext );

					if ( canMoveOnNext )			// this point can be moved to a new position ('intersPtOnNext') at segment ( this, next ).
					{
						// test 'length to next'.
						double			lenToNextT = thisPt.DistanceTo( intersPtOnNext );

						// get "jag ratio" ( longer adjacent edge / shorter adjacent edge ) for this case.
						propRatio1					= ( lenToPrev / lenToNextT );
						if ( lenToNextT > lenToPrev )
						{
							propRatio1				= ( 1.0 / propRatio1 );
						}
					}
				}

				// check the next poly segment.
				if ( isClosed || ( nextInx < vertCnt - 1 ) )	// there is next to the next index.
				{
					// get the index next to the next index.
					size_t				nnInx		= ( nextInx > vertCnt - 2 ) ? 0 : ( nextInx + 1 );
					const VWPoint2D&	nnPt		= this->GetVertexAt( nnInx );

					// check if it is a 'S' shape and whether this point can be removed/moved.
					isSShape						= ( VWPolygon2D::CheckForSShape( 	nnPt, nextPt, thisPt, prevPt,
																						vecToNext, vecToPrev, epsCloseness,
																						intersPtOnPrev, canMoveOnPrev )
																						||
																						( isSShape ) );

					if ( canMoveOnPrev )			// this point can be moved to a new position ('intersPtOnPrev') at segment ( this, prev ).
					{
						// test 'length to prev'.
						double			lenToPrevT	= thisPt.DistanceTo( intersPtOnPrev );

						// get "jag ratio" ( longer adjacent edge / shorter adjacent edge ) for this case.
						propRatio2					= ( lenToPrevT / lenToNext );
						if ( lenToNext > lenToPrevT )
						{
							propRatio2				= ( 1.0 / propRatio2 );
						}
					}
				}

				if ( isSShape )						// we have a 'S' shape.
				{
					double				jagRatio;

					canMove							= ( canMoveOnNext || canMoveOnPrev );
					if ( canMove )					// this point can be moved.
					{
						if ( canMoveOnNext && canMoveOnPrev )	// we have two choices for movement of this point.
						{
							// choose best "jag ratio" and intersection point.
							if ( propRatio1 < propRatio2 )
							{
								doMoveToNext		= true;

								jagRatio			= propRatio1;
								intersPt			= intersPtOnNext;
							}
							else
							{
								doMoveToNext		= false;

								jagRatio			= propRatio2;
								intersPt			= intersPtOnPrev;
							}
						}
						else if ( canMoveOnNext )	// single choice.
						{
							doMoveToNext			= true;

							jagRatio				= propRatio1;
							intersPt				= intersPtOnNext;
						}
						else if ( canMoveOnPrev )	// single choice.
						{
							doMoveToNext			= false;

							jagRatio				= propRatio2;
							intersPt				= intersPtOnPrev;
						}
					}
					else							// this point cannot be moved.
					{
						// get "jag ratio" ( longer adjacent edge / shorter adjacent edge ).
						jagRatio					= ( lenToPrev / lenToNext );
						if ( lenToNext > lenToPrev )
						{
							jagRatio				= ( 1.0 / jagRatio );
						}
					}

					isJag							= ( angBetVecsD <= kMaxAngForSureJag );	// it is a "jag".

					// check the "jag ratio" (second criterion).
					if ( ! isJag )					// still not decided whether it is a "jag". check if it is (according to the "jag ratio").
					{
						double		sinAng			= sin( angBetVecsR );

						// the smaller the angle is the bigger is probability to have a "jag" (use the sine for this relation).
						isJag						= ( jagRatio < ( kMaxJagRatioAtPIOver2 / sinAng ) );
					}
				}
			}
		}

		// processing.
		if ( isJag )								// we have a "jag" to be removed.
		{
			size_t					toRemoveInx		= thisInx;

			if ( canMove )							// this point can be moved to a new position ('intersPt').
			{
				// the movement.
				thisPt								= intersPt;

				// remove the previous or the next point (depending on where the intersection is) as it will be collinear to its neighbors after the movement.
				if ( doMoveToNext )
				{
					toRemoveInx						= prevInx;
				}
				else
				{
					toRemoveInx						= nextInx;
				}
			}

			// remove.
			farrVertices.erase( farrVertices.begin() + toRemoveInx );

			// update counts.
			-- procCnt;
			-- vertCnt;

			// decide from which point to go on.
			if ( ( ppInx != size_t(-1) ) &&			// there is a index prior to the previous and ...
				 ( ppInx < i ) )					// ... it is less than current.
			{
				i									= ppInx;	// go on from the 'prev of prev' index.
			}
			else if ( prevInx < i )					// previous index is less than current. note that there is always a previous index.
			{
				i									= prevInx;	// go on from the previous index.
			}
			//else: do not change: go on from this index.
		}
		else										// it is not a "jag".
		{
			++ i;									// increase counter.
		}
	}

	// next (after the "jags" are already removed) remove all polygon vertices which are collinear with their neighbors.
	this->CleanUp_FeaturePreserving( false, epsCollinear, epsCloseness );

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

// check polygon for self intersections. return true is so. Note: works on polygon with only corner vertices.
// 'doConsiderTouching' tells if touching will be considered as intersection.
// Note: touching of ends is not considered as self-intersection even if ('doConsiderTouching' == true).
bool VWPolygon2D::IsSelfIntersecting(bool doConsiderTouching/*=true*/) const
{
	// use a copy polygon in order to clean up repetitive points before the check.
	VWPolygon2D				copyPoly	= (*this);

	// lock the temporary copy polygon while cleaning up its repetitive points.
	// this suppresses recalculating of the polygon bounding box as it is not needed here.
	copyPoly.fLockedForEdit				= true;

	// clean up repetitive points.
	copyPoly.CleanUpPolygon( VWPoint2D::sEpsilon );

	size_t					ptsCnt		= copyPoly.GetVertexCount();
	size_t					procCnt		= ptsCnt;

	bool					eqEnds		= false;

	// prevent check at the end of the polygon (when first and last points coincide).
	// don't check the last legment if this is open poly.
	if ( ptsCnt > 0 )
	{
		const VWPoint2D&	firstPt		= copyPoly.GetVertexAt( 0 );
		const VWPoint2D&	lastPt		= copyPoly.GetVertexAt( ptsCnt - 1 );

		// check if polygon has coincident ends.
		eqEnds							= MathUtils::Equalish( firstPt, lastPt, VWPoint2D::sEpsilon );

		if ( eqEnds ||					// ends coincide.
			 ! copyPoly.IsClosed() )	// poly is open.
		{
			-- procCnt;
		}
	}

	VWPoint2D				intersPt;
	bool			bSelfIntersection	= false;
	for ( size_t i = 0 ; ( i < procCnt ) && ( ! bSelfIntersection ) ; i ++ )
	{
		size_t				prevInx;
		if		( i > 0 )	prevInx		= ( i - 1 );
		else if ( eqEnds )	prevInx		= ( ptsCnt - 2 );	// case: ( i == 0 &&   eqEnds ). Note: if we are here then ( ptsCnt > 1 ) for sure.
		else				prevInx		= ( ptsCnt - 1 );	// case: ( i == 0 && ! eqEnds )

		size_t				nextInx		= ( i + 1 ) % ptsCnt;
		if ( nextInx == ptsCnt - 1 &&	// next is the last and ...
			 eqEnds )					// ... ends coincide.
		{
			nextInx						= 0;
		}

		const VWPoint2D&	pt1line1	= copyPoly.GetVertexAt( i );
		const VWPoint2D&	pt2line1	= copyPoly.GetVertexAt( nextInx );

		// first line.
		const VWLine2D		line1( pt1line1, pt2line1 );

		for ( size_t j = 0 ; j < procCnt ; j ++ ) {

			// do not check for same edge or its adjacent.
			if ( i != j && prevInx != j && nextInx != j ) {

				const VWPoint2D&	pt1line2	= copyPoly.GetVertexAt( j );
				const VWPoint2D&	pt2line2	= copyPoly.GetVertexAt( ( j + 1 ) % ptsCnt );

				// second line.
				const VWLine2D		line2( pt1line2, pt2line2 );

				if ( line2.IntersectLineSegments( line1, intersPt ) ) {

					// ensure that the intersection point lies on both lines (no epsilon!).
					bool			isOnLines	= false;

					double			lenLine		= VWPoint2D::DistanceSqare( pt1line1.x, pt1line1.y, pt2line1.x, pt2line1.y );
					double			distToPt1	= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt1line1.x, pt1line1.y );
					double			distToPt2	= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt2line1.x, pt2line1.y );

					bool			isOnLine	= ( doConsiderTouching ) ?
												  ( distToPt1 <= lenLine ) && ( distToPt2 <= lenLine ) :
												  ( distToPt1 <  lenLine ) && ( distToPt2 <  lenLine );

					if ( isOnLine ) {			// intersection lies on line 1 (no epsilon!).

						lenLine					= VWPoint2D::DistanceSqare( pt1line2.x, pt1line2.y, pt2line2.x, pt2line2.y );
						distToPt1				= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt1line2.x, pt1line2.y );
						distToPt2				= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt2line2.x, pt2line2.y );

						isOnLine				= ( doConsiderTouching ) ?
												  ( distToPt1 <= lenLine ) && ( distToPt2 <= lenLine ) :
												  ( distToPt1 <  lenLine ) && ( distToPt2 <  lenLine );

						if ( isOnLine ) {		// intersection lies on line 2 (no epsilon!).
							isOnLines			= true;
						}
					}

					if ( isOnLines ) {	// it is really a self-intersection point.
						bSelfIntersection	= true;
						break;
					}
				}
			}
		}
	}
	return bSelfIntersection;
}

bool VWPolygon2D::IsSelfIntersecting(TSTLPoints2DArray& outArrIntersPts, bool doConsiderTouching/* = true*/) const
{
	outArrIntersPts.clear();

	// use a copy polygon in order to clean up repetitive points before the check.
	VWPolygon2D				copyPoly	= (*this);

	// lock the temporary copy polygon while cleaning up its repetitive points.
	// this suppresses recalculating of the polygon bounding box as it is not needed here.
	copyPoly.fLockedForEdit				= true;

	// clean up repetitive points.
	copyPoly.CleanUpPolygon( VWPoint2D::sEpsilon );

	size_t					ptsCnt		= copyPoly.GetVertexCount();
	size_t					procCnt		= ptsCnt;

	bool					eqEnds		= false;

	// prevent check at the end of the polygon (when first and last points coincide).
	// don't check the last legment if this is open poly.
	if ( ptsCnt > 0 )
	{
		const VWPoint2D&	firstPt		= copyPoly.GetVertexAt( 0 );
		const VWPoint2D&	lastPt		= copyPoly.GetVertexAt( ptsCnt - 1 );

		// check if polygon has coincident ends.
		eqEnds							= MathUtils::Equalish( firstPt, lastPt, VWPoint2D::sEpsilon );

		if ( eqEnds ||				// ends coincide.
			 !copyPoly.IsClosed() )	// poly is open.
		{
			-- procCnt;
		}
	}

	VWPoint2D		intersPt;
	bool			isSelfIntersection	= false;
	for ( size_t i = 0 ; i < procCnt; ++i )
	{
		size_t				prevInx;
		if		( i > 0 )	prevInx		= ( i - 1 );
		else if ( eqEnds )	prevInx		= ( ptsCnt - 2 );	// case: ( i == 0 &&   eqEnds ). Note: if we are here then ( ptsCnt > 1 ) for sure.
		else				prevInx		= ( ptsCnt - 1 );	// case: ( i == 0 && ! eqEnds )

		size_t				nextInx		= ( i + 1 ) % ptsCnt;
		if ( nextInx == ptsCnt - 1 &&	// next is the last and ...
			 eqEnds )					// ... ends coincide.
		{
			nextInx						= 0;
		}

		const VWPoint2D&	pt1line1	= copyPoly.GetVertexAt( i );
		const VWPoint2D&	pt2line1	= copyPoly.GetVertexAt( nextInx );

		// first line.
		const VWLine2D		line1( pt1line1, pt2line1 );

		// get line bounding box.
		VWRectangle2D		bboxLine1(	pt1line1.x, pt2line1.x,		// left / right.
										pt1line1.y, pt2line1.y );	// top / bottom.

		for ( size_t j = 0 ; j < procCnt ; ++j )
		{
			// do not check for same edge or its adjacent.
			if ( i != j && prevInx != j && nextInx != j )
			{
				const VWPoint2D&	pt1line2	= copyPoly.GetVertexAt( j );
				const VWPoint2D&	pt2line2	= copyPoly.GetVertexAt( ( j + 1 ) % ptsCnt );

				VWRectangle2D		bboxLine2(	pt1line2.x, pt2line2.x,		// left / right.
												pt1line2.y, pt2line2.y );	// top / bottom.

				if ( !bboxLine1.IsOutside( bboxLine2, VWPoint2D::sEpsilon ) )
				{
					// second line.
					const VWLine2D		line2( pt1line2, pt2line2 );

					if ( line2.IntersectLineSegments( line1, intersPt ) )
					{
						// ensure that the intersection point lies on both lines (no epsilon!).
						bool			isOnLines	= false;

						double			lenLine		= VWPoint2D::DistanceSqare( pt1line1.x, pt1line1.y, pt2line1.x, pt2line1.y );
						double			distToPt1	= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt1line1.x, pt1line1.y );
						double			distToPt2	= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt2line1.x, pt2line1.y );

						bool			isOnLine	= ( doConsiderTouching ) ?
													  ( distToPt1 <= lenLine ) && ( distToPt2 <= lenLine ) :
													  ( distToPt1 <  lenLine ) && ( distToPt2 <  lenLine );

						if ( isOnLine ) // intersection lies on line 1 (no epsilon!).
						{
							lenLine					= VWPoint2D::DistanceSqare( pt1line2.x, pt1line2.y, pt2line2.x, pt2line2.y );
							distToPt1				= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt1line2.x, pt1line2.y );
							distToPt2				= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt2line2.x, pt2line2.y );

							isOnLine				= ( doConsiderTouching ) ?
													  ( distToPt1 <= lenLine ) && ( distToPt2 <= lenLine ) :
													  ( distToPt1 <  lenLine ) && ( distToPt2 <  lenLine );

							if ( isOnLine ) // intersection lies on line 2 (no epsilon!).
							{
								isOnLines			= true;
							}
						}

						if ( isOnLines ) // it is really a self-intersection point.
						{
							isSelfIntersection	= true;
							auto newPt = std::find( outArrIntersPts.begin(), outArrIntersPts.end(), intersPt );
							if ( newPt == outArrIntersPts.end() )
							{
								outArrIntersPts.push_back( intersPt );
							}
						}
					}
				}
			}
		}
	}

	return isSelfIntersection;
}

// checks if there are arc vertices with degenerate (zero) radii and recalculates them.
void VWPolygon2D::RecalcDegenerateArcVerticesRadii()
{
	size_t				ptsCnt		= farrVertices.size();

	// validation.
	if ( ptsCnt <= 1 )
	{
		ASSERTN( kVStanev, false );
		return;
	}

	bool				isClosed	= this->IsClosed();

	size_t				startIndex	= 0;

	// check for a special case: first point coincides with the last one.
	if (	( ptsCnt > 2 ) &&
			( MathUtils::Equalish( farrVertices[ 0 ].pt, farrVertices[ ptsCnt - 1 ].pt, VWPoint2D::sEpsilon ) ) )
	{
		// validate: coincident points must have same vertex types.
		ASSERTN( kVStanev, ( farrVertices[ 0 ].type == farrVertices[ ptsCnt - 1 ].type ) );

		startIndex					= 1;

		isClosed					= true;
	}

	SVertex*			lastVert	= & farrVertices[ ptsCnt - 1 ];
	SVertex*			thisVert	= & farrVertices[ startIndex ];
	SVertex*			nextVert	= & farrVertices[ startIndex + 1 ];

	if ( isClosed && ( thisVert->type != eVertexType_Corner ) )	// the polyline is closed and start vertex is not corner.
	{
		// ensure non-degenerate arc vertex radius.
		this->RecalcDegenerateArcVertexRadius( lastVert, thisVert, nextVert );
	}

	// pass next segments.
	for ( size_t i = ( startIndex + 2 ) ; i < ptsCnt ; ++ i )
	{
		lastVert					= thisVert;
		thisVert					= nextVert;
		nextVert					= & farrVertices[ i ] ;

		// ensure non-degenerate arc vertex radius.
		this->RecalcDegenerateArcVertexRadius( lastVert, thisVert, nextVert );
	}

	lastVert						= thisVert;
	thisVert						= nextVert;
	nextVert						= & farrVertices[ startIndex ];

	if ( isClosed && ( thisVert->type != eVertexType_Corner ) )	// the polyline is closed and last vertex is not corner.
	{
		// ensure non-degenerate arc vertex radius.
		this->RecalcDegenerateArcVertexRadius( lastVert, thisVert, nextVert );
	}
}

//This code was not working correctly. It does not account for min coord correctly, so I 
//swapped it for the code below. [MFlamer 1/5/2013] 


// get the bouding box which is parallel to given line
// the result polygon contains 4 vertices of the bounding box
//void VWPolygon2D::GetPolygonBounds(const VWLine2D& line, VWPolygon2D& outBounds) const
//{
//	VWPoint2D			basePt1		= line.GetStart();
//
//	VWPoint2D			minPt, maxPt;
//	VWPoint2D			minProjPt, maxProjPt;
//	// min and max distance from the begining of the line (face bearing line)
//	double_gs			minProjDist, maxProjDist;
//	// mian am max dist from the poly to the line
//	double_gs			minDist, maxDist;
//	size_t				vertCnt		= farrVertices.size();
//	for(size_t v=0; v<vertCnt; v++)
//	{
//		VWPoint2D	pt			= farrVertices[ v ].pt;
//		VWPoint2D	projPt		= line.PtPerpLine( pt );
//		double_gs	dist		= ( projPt - pt ).Magnitude();
//		double_gs	projDist	= ( projPt - basePt1 ).Magnitude();
//		if ( v == 0 )
//		{
//			// first time - init
//			minPt			= maxPt				= pt;
//			minProjPt		= maxProjPt			= projPt;
//			minProjDist		= maxProjDist		= projDist;
//			minDist			= maxDist			= dist;
//		}
//		else
//		{
//			if ( projDist < minProjDist )
//			{
//				minPt			= pt;
//				minProjPt		= projPt;
//				minProjDist		= projDist;
//			}
//			if ( projDist > maxProjDist )
//			{
//				maxPt			= pt;
//				maxProjPt		= projPt;
//				maxProjDist		= projDist;
//			}
//			if ( dist < minDist )
//				minDist		= dist;
//			if ( dist > maxDist )
//				maxDist		= dist;
//		}
//	}
//
//	VWPoint2D	minDir	= (minPt - minProjPt).Normalize();
//	VWPoint2D	maxDir	= (maxPt - maxProjPt).Normalize();
//
//	// calculate the four points of the rotated bounding box
//	VWPoint2D	a		= minProjPt + minDir * minDist;
//	VWPoint2D	b		= maxProjPt + minDir * minDist;
//	VWPoint2D	c		= minProjPt + maxDir * maxDist;
//	VWPoint2D	d		= maxProjPt + maxDir * maxDist;
//
//	outBounds.ClearVertices();
//	outBounds.AddVertex( a );
//	outBounds.AddVertex( b );
//	outBounds.AddVertex( d );
//	outBounds.AddVertex( c );
//}


// get the bouding box which is parallel to given line
// the result polygon contains 4 vertices of the bounding box
void VWPolygon2D::GetPolygonBounds(const VWLine2D& line, VWPolygon2D& outBounds) const
{
	VWLine2D			baseLine( line.RelativeCoords(VWPoint2D(0,0)), line.RelativeCoords(VWPoint2D(1,0)) );

	VWPoint2D			minPt, maxPt;
	
	size_t				vertCnt		= farrVertices.size();
	for(size_t v=0; v<vertCnt; v++)
	{
		VWPoint2D		pt			= line.RelativeCoords(farrVertices[ v ].pt);
		
		if ( v == 0 )
		{
			// first time - init
			minPt					= maxPt				= pt;
		}
		else
		{
			if ( pt.x < minPt.x ) minPt.x = pt.x;
			if ( pt.y < minPt.y ) minPt.y = pt.y;
			if ( pt.x > maxPt.x ) maxPt.x = pt.x;
			if ( pt.y > maxPt.y ) maxPt.y = pt.y;
		}
	}	

	// calculate the four points of the rotated bounding box
	VWPoint2D	a		= baseLine.RelativeCoords( minPt );
	VWPoint2D	b		= baseLine.RelativeCoords( VWPoint2D(maxPt.x, minPt.y) );
	VWPoint2D	c		= baseLine.RelativeCoords( maxPt );
	VWPoint2D	d		= baseLine.RelativeCoords( VWPoint2D(minPt.x, maxPt.y) );

	outBounds.ClearVertices();
	outBounds.AddVertex( a );
	outBounds.AddVertex( b );
	outBounds.AddVertex( c );
	outBounds.AddVertex( d );
}

void VWPolygon2D::GetPolygonBounds(const VWLine2D& line, VWRectangle2D& outBounds) const
{
	VWLine2D			baseLine( line.RelativeCoords(VWPoint2D(0,0)), line.RelativeCoords(VWPoint2D(1,0)) );

	VWPoint2D			minPt, maxPt;
	
	size_t				vertCnt		= farrVertices.size();
	for(size_t v=0; v<vertCnt; v++)
	{
		VWPoint2D		pt			= line.RelativeCoords(farrVertices[ v ].pt);
		
		if ( v == 0 )
		{
			// first time - init
			minPt					= maxPt				= pt;
		}
		else
		{
			if ( pt.x < minPt.x ) minPt.x = pt.x;
			if ( pt.y < minPt.y ) minPt.y = pt.y;
			if ( pt.x > maxPt.x ) maxPt.x = pt.x;
			if ( pt.y > maxPt.y ) maxPt.y = pt.y;
		}
	}	

	// calculate the four points of the rotated bounding box
	VWPoint2D	a		= baseLine.RelativeCoords( minPt );
	VWPoint2D	b		= baseLine.RelativeCoords( VWPoint2D(maxPt.x, minPt.y) );
	VWPoint2D	c		= baseLine.RelativeCoords( maxPt );
	VWPoint2D	d		= baseLine.RelativeCoords( VWPoint2D(minPt.x, maxPt.y) );

	outBounds.SetRect( minPt.x, maxPt.x, maxPt.y, minPt.y );
}

// gets the bounding box which is parallel to the given direction (a similar approach).
// the result is 4 vertices (UL, UR, LL, LR) of the bounding box.
// 'doPolygonize' controls whether the poly to be polygonized or not.
void VWPolygon2D::GetPolygonBounds(const VWPoint2D& vDirection, VWPoint2D& vUL, VWPoint2D& vUR, VWPoint2D& vLL, VWPoint2D& vLR, bool doPolygonize /*=true*/) const
{
	// the direction has to be defined.
	VWFC_ASSERT( vDirection.MagnitudeSquared() > VWPoint3D::sSqrEpsilon );	// bad input !

	// get polygonized poly.
	VWPolygon2D			poly2DPolygonized;

	if ( doPolygonize &&				// has to be polygonized and ...
		 this->HasNonCornerVertices() )	// ... there are non-corner vertices.
	{
		// polygonize.
		VWPolygon2DObj	poly2DObj( gSDK->ConvertToPolygonN( VWPolygon2DObj( *this ), false , 32 ) );
		poly2DObj.GetPolygon( poly2DPolygonized );
		poly2DObj.DeleteObject( false );
	}
	else								// this is already a polygon.
	{
		poly2DPolygonized				= ( *this );
	}

	// normalize the vector.
	VWPoint2D			vDir			= vDirection;
	vDir.Normalize();

	// get the perpendicular normalized direction.
	VWPoint2D			vPerpDir		= vDir.Perp();
	//vPerpDir.Normalize();				// note it's already known that 'vPerpDir' is normalized.

	// four zero vectors.
	VWPoint2D			vIMax, vIMin, vJMax, vJMin;

	const VWPoint2D&	vInit			= poly2DPolygonized.GetVertexAt( 0 );
	size_t				vertCount		= poly2DPolygonized.GetVertexCount();

	for ( size_t i = 1 ; i < vertCount ; i ++ )
	{
		// get current
		const VWPoint2D&	vCurr		= poly2DPolygonized.GetVertexAt( i ) - vInit;

		// project the current onto directional vector and on its perpendicular.
		// note that 'vDir' and 'vPerpDir' are normalized, so we don't need divisors.
		VWPoint2D			vPara		= ( vDir     * ( vCurr.DotProduct( vDir     ) ) );
		VWPoint2D			vPerp		= ( vPerpDir * ( vCurr.DotProduct( vPerpDir ) ) );

		// get normalized vectors.
		VWPoint2D			vParaNorm	= vPara;
		VWPoint2D			vPerpNorm	= vPerp;
		vParaNorm.Normalize();
		vPerpNorm.Normalize();
		
		if ( ( vParaNorm - vDir ).MagnitudeSquared() < VWPoint3D::sSqrEpsilon )
		{
			if ( vPara.MagnitudeSquared() > vIMax.MagnitudeSquared() )
				vIMax	= vPara;
		}
		else
		{
			if ( vPara.MagnitudeSquared() > vIMin.MagnitudeSquared() )
				vIMin	= vPara;
		}

		if ( ( vPerpNorm - vPerpDir ).MagnitudeSquared() < VWPoint3D::sSqrEpsilon )
		{
			if ( vPerp.MagnitudeSquared() > vJMax.MagnitudeSquared() )
				vJMax	= vPerp;
		}
		else
		{
			if ( vPerp.MagnitudeSquared() > vJMin.MagnitudeSquared() )
				vJMin	= vPerp;
		}
	}

	// find the bounding box polygon in the given direction.
	vUL									= ( vInit + vIMin + vJMax );
	vUR									= ( vInit + vIMax + vJMax );
	vLL									= ( vInit + vIMin + vJMin );
	vLR									= ( vInit + vIMax + vJMin );
}

/////////////////////////////////////////////////////////////////////////////////
// Mathematics
/////////////////////////////////////////////////////////////////////////////////

// join this polygon to the given polygon only if both polygons are not closed and have touching endpoints (within epsilon).
bool VWPolygon2D::AddAdjoiningPolygon(const VWPolygon2D& adjoiningPoly, double epsilon, bool checkTypes/*= false*/)
{
	// init.
	bool						doAdd			= true;
	bool						isAdded			= false;

	if ( this->IsClosed() || adjoiningPoly.IsClosed() )		// bad input! cannot concatenate closed polygons.
	{
		doAdd									= false;
	}

	if ( doAdd && ! isAdded )	// still not added.
	{
		if ( this->IsEmpty() )
		{
			(*this)								= adjoiningPoly;
			isAdded								= true;
		}
		else if ( adjoiningPoly.IsEmpty() )
		{
			isAdded								= true;
		}

		if ( ! isAdded )		// still not added.
		{
			size_t	thisPolyCnt	= this->GetVertexCount();
			size_t	adjPolyCnt	= adjoiningPoly.GetVertexCount();

			// validate.
			VWFC_ASSERT( ( thisPolyCnt > 0 ) && ( adjPolyCnt > 0 ) );			// should be already ensured (see IsEmpty check above).

			// get endpoints.
			const VWPoint2D&	thisBegPt		= this->GetVertexAt(	0 );
			const VWPoint2D&	thisEndPt		= this->GetVertexAt(	thisPolyCnt - 1 );
			const VWPoint2D&	adjBegPt		= adjoiningPoly.GetVertexAt(	0 );
			const VWPoint2D&	adjEndPt		= adjoiningPoly.GetVertexAt(	adjPolyCnt - 1 );

			// get endpoints types.
			EVertexType			thisBegType		= this->GetVertexType(	0 );
			EVertexType			thisEndType		= this->GetVertexType(	thisPolyCnt - 1 );
			EVertexType			adjBegType		= adjoiningPoly.GetVertexType(	0 );
			EVertexType			adjEndType		= adjoiningPoly.GetVertexType(	adjPolyCnt - 1 );

			// check if endpoints touch.
			doAdd								= false;
			bool				dontCheckTypes	= ( ! checkTypes );
			VWPolygon2D			firstToAdd, secondToAdd;
			if		( ( dontCheckTypes || ( thisEndType == adjBegType ) ) &&	// types check (conditional).
					  MathUtils::Equalish( thisEndPt, adjBegPt, epsilon ) )
			{
				firstToAdd						= (*this);
				secondToAdd						= adjoiningPoly;

				doAdd							= true;
			}
			else if	( ( dontCheckTypes || ( thisEndType == adjEndType ) ) &&	// types check (conditional).
					  MathUtils::Equalish( thisEndPt, adjEndPt, epsilon ) )
			{
				firstToAdd						= (*this);
				secondToAdd						= adjoiningPoly;
				secondToAdd.ReversePoints( checkTypes );

				doAdd							= true;
			}
			else if	( ( dontCheckTypes || ( thisBegType == adjEndType ) ) &&	// types check (conditional).
					  MathUtils::Equalish( thisBegPt, adjEndPt, epsilon ) )
			{
				firstToAdd						= adjoiningPoly;
				secondToAdd						= (*this);

				doAdd							= true;
			}
			else if	( ( dontCheckTypes || ( thisBegType == adjBegType ) ) &&	// types check (conditional).
					  MathUtils::Equalish( thisBegPt, adjBegPt, epsilon ) )
			{
				firstToAdd						= (*this);
				firstToAdd.ReversePoints( checkTypes );
				secondToAdd						= adjoiningPoly;

				doAdd							= true;
			}

			if ( doAdd )	// adding is possible (there are touching endpoints).
			{
				// add second poly to first poly.
				size_t				secPolyCnt	= secondToAdd.farrVertices.size();
				for ( size_t i = 1 ; i < secPolyCnt ; ++ i )	// start from second vertex (don't add first vertex)!
				{
					const SVertex&	vertex		= secondToAdd.farrVertices[ i ];
					firstToAdd.farrVertices.push_back( vertex );
				}

				// update this poly with the result.
				(*this)							= firstToAdd;

				isAdded							= true;
			}
		}
	}

	// recalculate bounding box if needed.
	if ( isAdded && ( ! fLockedForEdit ) )
	{
		this->RecalculateBoundingBox();
	}

	// result.
	return	( isAdded );
}

// find index of next 'apposite' polygon point (not too close).
bool VWPolygon2D::GetNextAppositePtIndex(size_t inPtIndex, size_t& outNextPtIndex, double dEpsilon) const
{
	bool				hasNext		= false;

	// check if polygon has at least 2 vertices.
	size_t				len			= this->GetVertexCount();
	if ( len < 2 )
	{
		return	false;
	}
	// validation.
	VWFC_ASSERT( inPtIndex < len );

	// the point.
	const VWPoint2D&	pt			= this->GetVertexAt( inPtIndex );

	size_t				counter		= inPtIndex;	// init.
	// loop all next points.
	for ( size_t i = 0 ; i < ( len - 1 ) ; ++ i )
	{
		++ counter;		// increase.

		// check if index is acceptable.
		if ( ( ! this->IsClosed() ) && ( counter >= len ) )
		{
			break;
		}

		// get index of next point.
		size_t			currIndex	= counter;
		if ( counter >= len )
		{
			currIndex				= ( counter % len );
		}
		
		const VWPoint2D&	currPt	= this->GetVertexAt( currIndex );

		if ( ! MathUtils::Equalish( pt, currPt, dEpsilon ) )	// not too close.
		{
			outNextPtIndex			= currIndex;
			hasNext					= true;
			break;
		}
	}

	// result.
	return	hasNext;
}

// find next 'apposite' polygon point (not too close).
bool VWPolygon2D::GetNextAppositePt(size_t inPtIndex, VWPoint2D& outNextPt, double dEpsilon) const
{
	size_t	nextPtIndex;
	bool	hasNext		= this->GetNextAppositePtIndex( inPtIndex, nextPtIndex, dEpsilon );
	if ( hasNext )
	{
		outNextPt		= this->GetVertexAt( nextPtIndex );
	}
	return	hasNext;
}

// find index of previous 'apposite' polygon point (not too close).
bool VWPolygon2D::GetPrevAppositePtIndex(size_t inPtIndex, size_t& outPrevPtIndex, double dEpsilon) const
{
	bool				hasPrev		= false;

	// check if polygon has at least 2 vertices.
	size_t				len			= this->GetVertexCount();
	if ( len < 2 )
	{
		return	false;
	}
	// validation.
	VWFC_ASSERT( inPtIndex < len );

	// the point.
	const VWPoint2D&	pt			= this->GetVertexAt( inPtIndex );

	ptrdiff_t			counter		= inPtIndex;	// init. 
	// loop all previous points.
	for ( size_t i = 0 ; i < ( len - 1 ) ; ++ i )
	{
		-- counter;		// increase.

		// check if index is acceptable.
		if ( ( ! this->IsClosed() ) && ( counter < 0 ) )
		{
			break;
		}

		// get index of previous point.
		size_t			currIndex	= counter;
		if ( counter < 0 )
		{
			currIndex				= ( len + counter );
			VWFC_ASSERT( currIndex < len );	// must not happen !
		}
		
		const VWPoint2D&	currPt	= this->GetVertexAt( currIndex );

		if ( ! MathUtils::Equalish( pt, currPt, dEpsilon ) )	// not too close.
		{
			outPrevPtIndex			= currIndex;
			hasPrev					= true;
			break;
		}
	}

	// result.
	return	hasPrev;
}

// find previous 'apposite' polygon point (not too close).
bool VWPolygon2D::GetPrevAppositePt(size_t inPtIndex, VWPoint2D& outPrevPt, double dEpsilon) const
{
	size_t	prevPtIndex;
	bool	hasPrev		= this->GetPrevAppositePtIndex( inPtIndex, prevPtIndex, dEpsilon );
	if ( hasPrev )
	{
		outPrevPt		= this->GetVertexAt( prevPtIndex );
	}
	return	hasPrev;
}

// find indices of the first 3 'apposite' polygon points (not too close and not collinear).
bool VWPolygon2D::GetAppositePtIndices(size_t& ptIndex0, size_t& ptIndex1, size_t& ptIndex2) const
{
	// init.
	ptIndex0 = ptIndex1 = ptIndex2	= 0;

	// check if polygon has at least 3 vertices.
	size_t				len			= this->GetVertexCount();
	if ( len < 3 )
	{
		return false;
	}

	// get first apposite vertex.
	ptIndex0						= 0;
	const VWPoint2D&	pt0			= this->GetVertexAt( ptIndex0 );

	bool				hasApposite	= false;
	// get second apposite vertex.
	ptIndex1						= 1;
	VWPoint2D			pt1;
	while ( ptIndex1 < len )
	{
		pt1							= this->GetVertexAt( ptIndex1 );
		if ( ! MathUtils::Equalish( pt0, pt1, VWPoint2D::sEpsilon ) )	// not too close.
		{
			hasApposite				= true;
			break;
		}
		++ ptIndex1;
	}

	// get third apposite vertex.
	if ( hasApposite )
	{
		hasApposite					= false;

		ptIndex2					= ( ptIndex1 + 1 );
		while ( ptIndex2 < len )
		{
			const VWPoint2D& pt2	= this->GetVertexAt( ptIndex2 );
			if ( ! VWPoint2D::ArePointsCollinear( pt0, pt1, pt2, VWPoint2D::sEpsilonCollinear ) )	// not collinear.
			{
				hasApposite			= true;
				break;
			}
			++ ptIndex2;
		}
	}
	
	// result.
	return	hasApposite;
}

// find the first 3 'apposite' polygon points (not too close and not collinear).
bool VWPolygon2D::GetThreeAppositePoints(VWPoint2D& pt0, VWPoint2D& pt1, VWPoint2D& pt2) const
{
	// init.
	size_t	ptIndex0, ptIndex1, ptIndex2;
	// find indices of the first 3 'apposite' polygon points (not too close and not collinear).
	bool	hasApposite	= this->GetAppositePtIndices( ptIndex0, ptIndex1, ptIndex2 );

	if ( hasApposite )
	{
		// get the corresponding polygon points.
		pt0				= this->GetVertexAt( ptIndex0 );
		pt1				= this->GetVertexAt( ptIndex1 );
		pt2				= this->GetVertexAt( ptIndex2 );
	}

	// result.
	return	hasApposite;
}

// find indices of next two 'apposite' polygon points (not too close and not collinear).
bool VWPolygon2D::GetNextAppositePtIndices(size_t ptIndex, size_t& outPtIndex0, size_t& outPtIndex1) const
{
	// init.
	outPtIndex0	= outPtIndex1			= ptIndex;
	bool					hasApposite	= false;

	size_t					len			= this->GetVertexCount();
	if ( len > 2 )						// polygon has at least 3 vertices.
	{
		// get first apposite vertex.
		const VWPoint2D&	pt			= this->GetVertexAt( ptIndex );

		bool				isClosed	= this->IsClosed();

		// get threshold index for searching.
		size_t				toIndex;
		if ( isClosed )
		{
			if ( ptIndex > 0 )			toIndex	= ( ptIndex - 1 );
			else						toIndex	= ( len - 1 );
		}
		else
		{
			toIndex						= ( len - 1 );
		}

		// get second apposite vertex.

		outPtIndex0						= ptIndex;	// init index for searching.

		VWPoint2D			pt0;
		do
		{
			++ outPtIndex0;				// increase index.

			if ( outPtIndex0 >= len )
			{
				if ( isClosed )			outPtIndex0	= ( outPtIndex0 % len );
				else					break;
			}

			pt0							= this->GetVertexAt( outPtIndex0 );
			if ( ! MathUtils::Equalish( pt, pt0, VWPoint2D::sEpsilon ) )	// not too close.
			{
				hasApposite				= true;
				break;
			}
		}
		while ( outPtIndex0 != toIndex );

		// get third apposite vertex.
		if ( hasApposite )
		{
			hasApposite					= false;

			outPtIndex1					= outPtIndex0;	// init index for searching.

			do
			{
				++ outPtIndex1;			// increase index.

				if ( outPtIndex1 >= len )
				{
					if ( isClosed )		outPtIndex1	= ( outPtIndex1 % len );
					else				break;
				}

				const VWPoint2D& pt1	= this->GetVertexAt( outPtIndex1 );
				if ( ! VWPoint2D::ArePointsCollinear( pt, pt0, pt1, VWPoint2D::sEpsilonCollinear ) )	// not collinear.
				{
					hasApposite			= true;
					break;
				}
			}
			while ( outPtIndex1 != toIndex );
		}
	}

	// result.
	return	( hasApposite );
}

// find next two 'apposite' polygon points (not too close and not collinear).
bool VWPolygon2D::GetNextAppositePoints(size_t ptIndex, VWPoint2D& outPt0, VWPoint2D& outPt1) const
{
	// init.
	size_t	ptIndex0, ptIndex1;
	// find indices of the next 2 'apposite' polygon points (not too close and not collinear).
	bool	hasApposite	= this->GetNextAppositePtIndices( ptIndex, ptIndex0, ptIndex1 );

	if ( hasApposite )
	{
		// get the corresponding polygon points.
		outPt0			= this->GetVertexAt( ptIndex0 );
		outPt1			= this->GetVertexAt( ptIndex1 );
	}

	// result.
	return	( hasApposite );
}

// find indices of previous two 'apposite' polygon points (not too close and not collinear).
bool VWPolygon2D::GetPrevAppositePtIndices(size_t ptIndex, size_t& outPtIndex0, size_t& outPtIndex1) const
{
	// init.
	outPtIndex0	= outPtIndex1			= ptIndex;
	bool					hasApposite	= false;

	size_t					len			= this->GetVertexCount();
	if ( len > 2 )						// polygon has at least 3 vertices.
	{
		// get first apposite vertex.
		const VWPoint2D&	pt			= this->GetVertexAt( ptIndex );

		bool				isClosed	= this->IsClosed();

		// get threshold index for searching.
		size_t				toIndex;
		if ( isClosed )		toIndex		= ( ptIndex + 1 % len );
		else				toIndex		= 0;

		// get second apposite vertex.

		// init index for searching.
		outPtIndex0						= ptIndex;

		ptrdiff_t			index		= outPtIndex0;
		VWPoint2D			pt0;
		do
		{
			-- index;					// decrease index.

			if ( index < 0 )			// just become negative.
			{
				if ( isClosed )			index	= ( len - 1 );
				else					break;
			}

			outPtIndex0					= index;				// update.

			pt0							= this->GetVertexAt( outPtIndex0 );
			if ( ! MathUtils::Equalish( pt, pt0, VWPoint2D::sEpsilon ) )	// not too close.
			{
				hasApposite				= true;
				break;
			}
		}
		while ( index != (ptrdiff_t) toIndex );

		// get third apposite vertex.
		if ( hasApposite )
		{
			hasApposite					= false;

			// get init index for searching.
			outPtIndex1					= outPtIndex0;

			index						= outPtIndex1;
			do
			{
				-- index;				// decrease index.

				if ( index < 0 )		// just become negative.
				{
					if ( isClosed )		index	= ( len - 1 );
					else				break;
				}

				outPtIndex1				= index;				// update.

				const VWPoint2D& pt1	= this->GetVertexAt( outPtIndex1 );
				if ( ! VWPoint2D::ArePointsCollinear( pt, pt0, pt1, VWPoint2D::sEpsilonCollinear ) )	// not collinear.
				{
					hasApposite			= true;
					break;
				}
			}
			while ( index != (ptrdiff_t) toIndex );
		}
	}

	// result.
	return	( hasApposite );
}

// find previous two 'apposite' polygon points (not too close and not collinear).
bool VWPolygon2D::GetPrevAppositePoints(size_t ptIndex, VWPoint2D& outPt0, VWPoint2D& outPt1) const
{
	// init.
	size_t	ptIndex0, ptIndex1;
	// find indices of the previous 2 'apposite' polygon points (not too close and not collinear).
	bool	hasApposite	= this->GetPrevAppositePtIndices( ptIndex, ptIndex0, ptIndex1 );

	if ( hasApposite )
	{
		// get the corresponding polygon points.
		outPt0			= this->GetVertexAt( ptIndex0 );
		outPt1			= this->GetVertexAt( ptIndex1 );
	}

	// result.
	return	( hasApposite );
}

void VWPolygon2D::Transform(const VWTransformMatrix& mat)
{
	fdMinX		= 0;
	fdMaxX		= 0;
	fdMinY		= 0;
	fdMaxY		= 0;

	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++)
	{
		VWPoint2D		pt		= farrVertices[ i ].pt;
		VWPoint3D		p( pt.x, pt.y, 0 );
		mat.TransformPoint( p );
		if ( i == 0 )
		{
			fdMinX		= p.x;
			fdMaxX		= p.x;
			fdMinY		= p.y;
			fdMaxY		= p.y;
		}
		else
		{
			fdMinX		= min( fdMinX, p.x );
			fdMaxX		= max( fdMaxX, p.x );
			fdMinY		= min( fdMinY, p.y );
			fdMaxY		= max( fdMaxY, p.y );
		}
		farrVertices[ i ].pt.SetPoint( p.x, p.y );
	}
}

void VWPolygon2D::MovePolygon(double cx, double cy)
{
	fdMinX		= 0;
	fdMaxX		= 0;
	fdMinY		= 0;
	fdMaxY		= 0;

	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++)
	{
		VWPoint2D &		pt	= farrVertices[i].pt;

		pt.x		+= cx;
		pt.y		+= cy;

		if ( i == 0 )
		{
			fdMinX		= pt.x;
			fdMaxX		= pt.x;
			fdMinY		= pt.y;
			fdMaxY		= pt.y;
		}
		else
		{
			fdMinX		= min( fdMinX, pt.x );
			fdMaxX		= max( fdMaxX, pt.x );
			fdMinY		= min( fdMinY, pt.y );
			fdMaxY		= max( fdMaxY, pt.y );
		}
	}
}

// rotate the polygon by the center of the bounding box
void VWPolygon2D::Rotate(double degAngle)
{
	double_gs	x		= fdMinX + ( fdMaxX - fdMinX ) / 2;
	double_gs	y		= fdMinY + ( fdMaxY - fdMinY ) / 2;
	this->MovePolygon( -x, -y );

	double_gs	alpha	= MathUtils::Deg2Rad( degAngle );
	double_gs	s		= sin( alpha );
	double_gs	c		= cos( alpha );
	TransformMatrix		rotationMatrix;
	rotationMatrix.SetToIdentity();
	rotationMatrix.SetRow0( NormalVector(  c, s, 0 ) );
	rotationMatrix.SetRow1( NormalVector( -s, c, 0 ) );
	rotationMatrix.SetRow2( NormalVector(  0, 0, 1 ) );
	this->Transform( rotationMatrix );

	this->MovePolygon( x, y );
}

// rotate by specified center
void VWPolygon2D::Rotate(const VWPoint2D& pt, double degAngle)
{
	this->MovePolygon( -pt.x, -pt.y );

	double_gs	alpha	= MathUtils::Deg2Rad( degAngle );
	double_gs	s		= sin( alpha );
	double_gs	c		= cos( alpha );
	TransformMatrix		rotationMatrix;
	rotationMatrix.SetToIdentity();
	rotationMatrix.SetRow0( NormalVector(  c, s, 0 ) );
	rotationMatrix.SetRow1( NormalVector( -s, c, 0 ) );
	rotationMatrix.SetRow2( NormalVector(  0, 0, 1 ) );
	this->Transform( rotationMatrix );

	this->MovePolygon( pt.x, pt.y );
}

// calculate the area of the polygon
// A = 1/2 Sum(i:=0 to N-1)( x(i)*y(i+1) - x(i+1)*y(i) )
double VWPolygon2D::GetArea() const
{
	double	dArea			= 0;

	size_t	nVertexCount	= farrVertices.size();
	if ( nVertexCount == 0 )
		return dArea;

	VWPoint2D		a		= farrVertices[ 0 ].pt;
	VWPoint2D		b;
	VWPoint2D		c;

	for(size_t i=1; i<nVertexCount-1; i++) {

		b		= farrVertices[ i ].pt;
		c		= farrVertices[ i + 1 ].pt;

		// Get the area
		double_gs	triArea		= VWPoint2D::TriArea( a, b, c );

		// Calculate the area
		dArea		= dArea + triArea;
	}

	/*double dOldArea = dArea;
	 ***********************************
	 * other NOT working VERSION
	 **********************************

	dArea			= 0;
	for(size_t i=0; i<nVertexCount-1; i++) {
		const	VWPoint2D&	p0		= farrVertices[ i ].pt;
		const	VWPoint2D&	p1		= farrVertices[ i + 1 ].pt;

		dArea		+= p0.x*p1.y - p1.x*p0.y;
	}
	dArea		/= 2;

	VWFC_ASSERT( VWFC::Math::MathUtils::Equalish( dArea, dOldArea, 0.0001 ) );
	*/

	return dArea;
}

bool VWPolygon2D::IsClockWise() const
{
	double	area	= this->GetArea();
	return area <= 0;
}

// calculate the perimeter of the polygon
double VWPolygon2D::GetPerimeter() const
{
	double	dPerimeter			= 0;

	size_t	nVertexCount	= farrVertices.size();
	if ( nVertexCount == 0 )
		return dPerimeter;

	size_t	len	= nVertexCount;
	if ( ! fbIsClosed )
		len--;
	for(size_t i=0; i<len; i++) {
		VWPoint2D	a, b;
		a			= farrVertices[ i ].pt;
		b			= i+1 < nVertexCount ? farrVertices[ i+1 ].pt : farrVertices[ 0 ].pt;

		dPerimeter	+= a.DistanceTo( b );
	}

	return dPerimeter;
}

double VWPolygon2D::GetLength() const
{
	double	length		= 0;

	size_t	vertsCnt	= this->GetVertexCount();
	for(size_t i=0; i<vertsCnt;) {
		EVertexType			vertType	= this->GetVertexType( i );
		if ( vertType == eVertexType_Corner ) {
			if ( i > 0 ) {
				const VWPoint2D&	prevPt		= this->GetVertexAt( i - 1 );
				const VWPoint2D&	thisPt		= this->GetVertexAt( i );

				length	+= prevPt.DistanceTo( thisPt );
			}
			i++;
		}
		else if ( vertType == eVertexType_Bezier ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
		else if ( vertType == eVertexType_Cubic ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
		else if ( vertType == eVertexType_Arc ) {
			const VWPoint2D&	prevPt		= this->GetVertexAt( (i > 0) ? (i - 1) : (farrVertices.size() - 1) );
			const VWPoint2D&	thisPt		= this->GetVertexAt( i );
			const VWPoint2D&	nextPt		= this->GetVertexAt( i + 1, true );
			VWArc2D		arc( prevPt, thisPt, nextPt );
			length		+= arc.GetLength();
			i			+= 2;
		}
		else if ( vertType == eVertexType_Radius ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
	}

	return length;
}
// calculate the length of the curve formed by the polyline up to the specified point
// if the point is not on the poly 
double VWPolygon2D::GetLength(const VWPoint2D& pt, double dEpsilon) const
{
	double	length		= 0;

	size_t	vertsCnt	= this->GetVertexCount();
	for(size_t i=0; i<vertsCnt;) {
		EVertexType			vertType	= this->GetVertexType( i );
		if ( vertType == eVertexType_Corner ) {
			if ( i > 0 ) {
				const VWPoint2D&	prevPt		= this->GetVertexAt( i - 1 );
				const VWPoint2D&	thisPt		= this->GetVertexAt( i );

				if ( VWLine2D::PtOnLine( pt, prevPt, thisPt, dEpsilon ) ) {
					length	+= prevPt.DistanceTo( pt );
					// Finished, Stop!
					break;
				}
				else {
					length	+= prevPt.DistanceTo( thisPt );
				}
			}
			i++;
		}
		else if ( vertType == eVertexType_Bezier ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
		else if ( vertType == eVertexType_Cubic ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
		else if ( vertType == eVertexType_Arc ) {
			const VWPoint2D&	prevPt		= this->GetVertexAt( (i > 0) ? (i - 1) : (farrVertices.size() - 1) );
			const VWPoint2D&	thisPt		= this->GetVertexAt( i );
			const VWPoint2D&	nextPt		= this->GetVertexAt( i + 1, true );
			VWArc2D		arc( prevPt, thisPt, nextPt );
			if ( arc.IsPtOnArc( pt, dEpsilon ) ) {
				length	+= arc.GetLength( pt );
				// Finished, Stop!
				break;
			}
			else {
				length		+= arc.GetLength();
				i			+= 2;
			}
		}
		else if ( vertType == eVertexType_Radius ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
	}

	return length;
}

double VWPolygon2D::GetLength(size_t fromVert, size_t toVert) const
{
	double	length		= 0;

	size_t	vertsCnt	= this->GetVertexCount();
	for(size_t i=fromVert; i<toVert && i<vertsCnt;) {
		EVertexType			vertType	= this->GetVertexType( (i + 1) % vertsCnt );
		if ( vertType == eVertexType_Corner ) {
			const VWPoint2D&	prevPt		= this->GetVertexAt( i );
			const VWPoint2D&	thisPt		= this->GetVertexAt( i + 1, true );

			length	+= prevPt.DistanceTo( thisPt );
			i++;
		}
		else if ( vertType == eVertexType_Bezier ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
		else if ( vertType == eVertexType_Cubic ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
		else if ( vertType == eVertexType_Arc ) {
			const VWPoint2D&	thisPt		= this->GetVertexAt( i );
			const VWPoint2D&	nextPt		= this->GetVertexAt( i + 1, true );
			const VWPoint2D&	nextNextPt	= this->GetVertexAt( i + 2, true );
			VWArc2D		arc( thisPt, nextPt, nextNextPt );
			length		+= arc.GetLength();
			i			+= 2;
		}
		else if ( vertType == eVertexType_Radius ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
	}

	return length;
}

Sint32 VWPolygon2D::GetIndexOf( const VWPoint2D& pt ) const
{
	Sint32 result = -1;

	for ( Sint32 ind = 0; ind < farrVertices.size() && (result == -1); ind++ )
	{
		if ( pt == farrVertices[ ind ].pt )
		{
			result = ind;
		}
	}

	return result;
}


// returns a point along the poly on the specified offset
bool VWPolygon2D::GetPtOnPoly(double offset, VWPoint2D& outPt) const
{
	VWPolygon2D	polygon = *this;

	if ( polygon.HasNonCornerVertices() )
	{// This method is designed to be used only with polygonized data!
		this->GetPolygonized( polygon );
	}

	bool		result		= false;
	double		length		= 0;
	size_t		vertsCnt	= polygon.GetVertexCount();

	for ( size_t i = 1 ; i < vertsCnt ; ++ i )
	{
		const VWPoint2D&	prevPt		= polygon.GetVertexAt( i - 1 );
		const VWPoint2D&	thisPt		= polygon.GetVertexAt( i );

		double				newLen		= length + prevPt.DistanceTo( thisPt );

		if ( MathUtils::GEish( newLen, offset, VWPoint2D::sEpsilon ) )
		{
			double		dist			= offset - length;
			VWPoint2D	n				= ( thisPt - prevPt ).Normalize();
			outPt						= prevPt + ( dist * n );
			result						= true;
			// Finished, Stop!
			break;
		}
		else
		{
			length			= newLen;
		}
	}

	return	result;
}

// returns a point along the poly on the specified offset
bool VWPolygon2D::GetPtOnPoly(double offset, VWPoint2D& outPt, size_t& outOnSegIndex) const
{
	VWPolygon2D	polygon = *this;

	if ( polygon.HasNonCornerVertices() )
	{// This method is designed to be used only with polygonized data!
		this->GetPolygonized( polygon );
	}

	bool		result		= false;
	outOnSegIndex			= size_t(-1);

	double		length		= 0;
	size_t		vertsCnt	= polygon.GetVertexCount();

	for ( size_t i = 1 ; i < vertsCnt ; ++ i )
	{
		const VWPoint2D&	prevPt		= polygon.GetVertexAt( i - 1 );
		const VWPoint2D&	thisPt		= polygon.GetVertexAt( i );

		double				newLen		= length + prevPt.DistanceTo( thisPt );

		if ( MathUtils::GEish( newLen, offset, VWPoint2D::sEpsilon ) )
		{
			double		dist			= offset - length;
			VWPoint2D	n				= ( thisPt - prevPt ).Normalize();
			outPt						= prevPt + ( dist * n );
			outOnSegIndex				= i - 1;
			result						= true;
			// Finished, Stop!
			break;
		}
		else
		{
			length			= newLen;
		}
	}

	return	result;
}

bool VWPolygon2D::GetPtOnPoly(double offset, VWPoint2D& outPt, VWPoint2D& outNormal, size_t* outOnSegIndex/* = nullptr*/) const
{
	VWPolygon2D	polygon = *this;

	if ( polygon.HasNonCornerVertices() )
	{// This method is designed to be used only with polygonized data!
		this->GetPolygonized( polygon );
	}

	bool		result		= false;
	double		length		= 0;
	size_t		vertsCnt	= polygon.GetVertexCount();
	for(size_t i=0; i<vertsCnt;) {
		EVertexType			vertType	= polygon.GetVertexType( i );
		if ( vertType == eVertexType_Corner ) {
			if ( i > 0 ) {
				size_t				prevIndex	= i - 1;
				const VWPoint2D&	prevPt		= polygon.GetVertexAt( prevIndex );
				const VWPoint2D&	thisPt		= polygon.GetVertexAt( i );

				double	newLen	= length + prevPt.DistanceTo( thisPt );
				if ( MathUtils::GEish( newLen, offset, VWPoint2D::sEpsilon ) ) {
					double		dist	= offset - length;
					VWPoint2D	n		= (thisPt - prevPt).Normalize();
					outPt				= prevPt + dist * n;
					if ( outOnSegIndex )
						*outOnSegIndex = prevIndex;
					result				= true;

					// calc the normal
					bool	atStart	= MathUtils::Equalish( dist, 0, VWPoint2D::sEpsilon );
					bool	atEnd	= MathUtils::Equalish( newLen, offset, VWPoint2D::sEpsilon );
					if ( atStart ||	atEnd )
					{

						VWPoint2D	v1, v2;
						double		ang;
						if ( atStart )
						{
							const VWPoint2D&	prevPrevPt	= polygon.GetVertexAt( (prevIndex > 0) ? (prevIndex - 1) : (vertsCnt - 1) );
							v1								= (prevPt - prevPrevPt).Normalize();
							v2								= (thisPt - prevPt).Normalize();
							ang								= Abs( (prevPrevPt - prevPt).CalcAng180() - (thisPt - prevPt).CalcAng180() );
						}
						else
						{
							const VWPoint2D&	nextPt	= polygon.GetVertexAt( (prevIndex > 0) ? (prevIndex - 1) : (vertsCnt - 1) );
							v1							= (thisPt - prevPt).Normalize();
							v2							= (nextPt - thisPt).Normalize();
							ang							= Abs( (prevPt - thisPt).CalcAng180() - (nextPt - thisPt).CalcAng180() );
						}

						if ( ! polygon.IsClosed() && atStart && prevIndex == 0 )
						{
							outNormal		= - v2.Perp();
						}
						else if ( ! polygon.IsClosed() && atEnd && prevIndex == vertsCnt - 2 )
						{
							outNormal		= - v1.Perp();
						}
						else
						{
							outNormal		= - ((v1.Perp() + v2.Perp()) / 2).Normalize();
							double		div	= sin( MathUtils::Deg2Rad( ang / 2 ) );
							if ( ! MathUtils::Equalish( div, 0, VWPoint2D::sEpsilon ) )
							{
								// calculate the common length
								outNormal		/= div;
							}
						}
					}
					else
					{
						outNormal			= - (thisPt - prevPt).Normalize().Perp();
					}
					
					// Finished, Stop!
					break;
				}
				else {
					length	= newLen;
				}
			}
			i++;
		}
		else if ( vertType == eVertexType_Bezier ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
		else if ( vertType == eVertexType_Cubic ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
		else if ( vertType == eVertexType_Arc ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
		else if ( vertType == eVertexType_Radius ) {
			DSTOP((kVStanev, "not implemented"));
			length	= 0;
			break;
		}
	}

	return result;
}

// Bozho - review: needs more testing.
// calculates point along the polygon at given offset starting from given vertex index.
// returns the index of the segment where calculated point lies.
// note: works on polygonized data only (corner vertices only).
bool VWPolygon2D::GetPtOnPolyOffsetFrom(size_t vertInx, double offset, VWPoint2D& outPt, size_t& outSegInx) const
{
	double		onSegOffset, segLength;

	// result.
	return	( this->GetPtOnPolyOffsetFrom( vertInx, offset, outPt, outSegInx, onSegOffset, segLength ) );
}

// calculates point along the polygon at given offset starting from given vertex index.
// returns the index of the segment where calculated point lies, the offset from the segment starting point and segment length.
// note: works on polygonized data only (corner vertices only).
bool VWPolygon2D::GetPtOnPolyOffsetFrom(size_t vertInx, double offset, VWPoint2D& outPt,
										size_t& outSegInx, double& outOnSegOff, double& outSegLen) const
{
	VWPolygon2D	polygon			= ( *this );

	// make sure to use polygonized data (with corner vertices only).
	if ( polygon.HasNonCornerVertices() )
	{
		VWFC_ASSERT( false );	// bad input - check.

		this->GetPolygonized( polygon );
	}

	// init.
	bool		notFound		= true;
	outSegInx	= -1;

	size_t		vertsCnt		= polygon.GetVertexCount();

	if ( VWFC_VERIFY( ( vertsCnt > 1 &&			// at least two points (has formed segment) and ...
						vertInx < vertsCnt &&	// ... valid input and ...
						offset >= 0.0 ) ) )		// ... non-negative offset.
	{
		double	prevLen			= 0.0;

		// lambda: calculates point along the given polygon segment at offset = ('offset' - 'prevLen').
		auto	getPtOnPolySeg	= [&] (size_t segInx, bool loopNeeded) -> bool
		{
			// init.
			bool				found			= false;

			const VWPoint2D&	thisPt			= polygon.GetVertexAt( segInx );

			// get valid next index.
			size_t				nextInx			= ( loopNeeded ? ( ( segInx + 1 ) % vertsCnt ) : ( segInx + 1 ) );

			VWPoint2D			segVec			= ( polygon.GetVertexAt( nextInx ) - thisPt );

			double				segLen			= segVec.Magnitude();		// segment length.

			if ( segLen > 0.0 )	// check segment length - prevent division by zero.
			{
				double			curOffset		= ( prevLen + segLen );		// current offset.

				if ( curOffset >= offset )		// the 'right' segment is reached.
				{
					segVec		/= segLen;		// normalize.

					outSegLen	= segLen;
					outOnSegOff	= ( offset - prevLen );

					outPt		= thisPt + ( outOnSegOff * segVec );

					found		= true;
				}
				else			// go on.
				{
					// update.
					prevLen		= curOffset;
				}
			}
			//else: zero-length segment.

			// result.
			return	( found );
		};

		size_t		lastVertInx	= ( vertsCnt - 1 );

		// search from the input vertex (specified by 'vertInx') to the last vertex.
		for ( size_t i = vertInx ; i < lastVertInx ; ++ i )
		{
			if ( getPtOnPolySeg( i, false /*no loop*/ ) )
			{
				notFound		= false;
				outSegInx		= i;

				break;			// stop.
			}
		}

		if ( polygon.IsClosed() &&				// closed polygon and ...
			 ( notFound ) )						// ... still not found.
		{
			// check the 'closing' last vertex -> first vertex.
			if ( getPtOnPolySeg( lastVertInx, true /*loop*/ ) )
			{
				notFound		= false;
				outSegInx		= lastVertInx;
			}

			if ( notFound )		// still not found.
			{
				// search from the first vertex to the input vertex (specified by 'vertInx').
				for ( size_t i = 0 ; i < vertInx ; ++ i )
				{
					if ( getPtOnPolySeg( i, false /*no loop*/ ) )
					{
						notFound				= false;
						outSegInx				= i;

						break;	// stop.
					}
				}
			}
		}
	}
	//else: bad input.

	// result.
	return	( ! notFound );
}

// finds the closest point on poly of the given point.
VWPoint2D VWPolygon2D::GetClosestPtOnPoly(const VWPoint2D& pt, double& outDist, Sint32& outOnSegIndex) const
{
	VWPoint2D						closestPt;

	size_t							vertCnt		= this->GetVertexCount();
	// validate.
	VWFC_ASSERT( vertCnt > 0 );		// poly is empty! incorrect.

	// Note: calculate squared distance while searching (which is faster).
	// at the end get the square root of the closest squared distance.

	if ( vertCnt < 2 )	// single point poly.
	{
		closestPt					= this->GetVertexAt( 0 );
		outDist						= pt.DistanceSquaredTo( closestPt );
		outOnSegIndex				= 0;
	}
	else				// poly has at least two points.
	{
		// compute poly segments to process.
		bool						isClosed	= this->IsClosed();
		size_t						procCnt		= vertCnt;
		if ( ! isClosed )
		{
			-- procCnt;
		}

		for ( size_t i = 0 ; i < procCnt ; ++ i )
		{
			double					currSqrDist;// for min distance to this poly segment.
			VWPoint2D				currPt;		// for closest point on this poly segment.

			bool					isOnSeg		= true;

			// this index.
			size_t					thisIndex	= i;

			// index of next poly point.
			size_t					nextIndex;
			if ( isClosed )			nextIndex	= ( thisIndex + 1 ) % procCnt;
			else					nextIndex	= ( thisIndex + 1 );

			// get vertex type.
			EVertexType				vertType	= this->GetVertexType( nextIndex );

			if ( vertType == eVertexType_Corner )	// this segment is a line.
			{
				const VWLine2D&		polyLine	= this->GetLineAt( thisIndex );
		
				// get the closest point on line.
				const VWPoint2D&	projPt		= polyLine.PtPerpLine( pt );
				if ( polyLine.PtOnLine( projPt, VWPoint2D::sEpsilon ) )	// projection is on line.
				{
					currSqrDist		= pt.DistanceSquaredTo( projPt );
					currPt			= projPt;
				}
				else
				{
					isOnSeg			= false;
				}
			}
			else if ( vertType == eVertexType_Bezier )
			{
				DSTOP( ( kVStanev, "not implemented" ) );
				isOnSeg				= false;
			}
			else if ( vertType == eVertexType_Cubic )
			{
				DSTOP( ( kVStanev, "not implemented" ) );
				isOnSeg							= false;
			}
			else if ( vertType == eVertexType_Radius )	// the segment is an arc.
			{
				// get next of next index.
				size_t				nextNextInx	= size_t(-1);
				if ( isClosed )
				{
					nextNextInx		= ( nextIndex + 1 ) % procCnt;
				}
				else if ( nextIndex < procCnt )
				{
					nextNextInx		= ( nextIndex + 1 );
				}

				if ( nextNextInx != size_t(-1) )
				{
					// get poly arc.
					const VWPoint2D&	prevPt	= this->GetVertexAt( thisIndex );
					const VWPoint2D&	thisPt	= this->GetVertexAt( nextIndex );
					const VWPoint2D&	nextPt	= this->GetVertexAt( nextNextInx );
					VWArc2D				polyArc( prevPt, thisPt, nextPt );

					// get the closest point on arc.
					const VWPoint2D&	projPt	= polyArc.PtPerpArc( pt );
					if ( polyArc.IsPtOnArc( projPt, VWPoint2D::sEpsilon ) )
					{
						currSqrDist		= pt.DistanceSquaredTo( projPt );
						currPt			= projPt;
					}
					else
					{
						isOnSeg			= false;
					}

					++	i;								// increase counter!
					nextIndex			= nextNextInx;	// update next index.
				}
				else
				{
					isOnSeg				= false;
				}
			}
			else if ( vertType == eVertexType_Arc ) {
				DSTOP((kVStanev, "not implemented"));
				break;
			}

			// if projection is not on segment.
			if ( ! isOnSeg )
			{
				// get segment ends.
				const VWPoint2D&	segPt0	= this->GetVertexAt( thisIndex );
				const VWPoint2D&	segPt1	= this->GetVertexAt( nextIndex );

				double			sqrDisToPt0	= pt.DistanceSquaredTo( segPt0 );
				double			sqrDisToPt1	= pt.DistanceSquaredTo( segPt1 );
				if ( sqrDisToPt0 < sqrDisToPt1 )
				{
					currSqrDist	= sqrDisToPt0;
					currPt		= segPt0;
				}
				else
				{
					currSqrDist	= sqrDisToPt1;
					currPt		= segPt1;
				}
			}

			if ( ( thisIndex == 0 ) || ( currSqrDist < outDist ) )
			{
				// the following lines will be reached at least once (see that vertsCnt is > 1)
				outDist			= currSqrDist;
				closestPt		= currPt;
				outOnSegIndex	= (Sint32)thisIndex; 

				if ( outDist < VWPoint2D::sSqrEpsilon )	// stop if point lies on the poly segment.
				{
					break;
				}
			}
		}
	}

	// get the square root of the closest squared distance.
	outDist		= sqrt( outDist );

	// result.
	return	( closestPt );
}

// fast search for closest polygon point to the given point. Note: works on polygon with only corner vertices.
bool VWPolygon2D::GetClosestPtOnPolygon(const VWPoint2D& pt, double& outSqrDist, Sint32& outOnSegInx, VWPoint2D& outClosestPt) const
{
	// init.
	bool		isFound		= false;

	double		sqrDstToVtx;

	// get the closest polygon vertex.
	size_t		clstVtxInx	= this->GetClosestPolyVertex( pt, sqrDstToVtx );

	if ( VWFC_VERIFY( ( clstVtxInx != -1 ) ) )
	{ 
		size_t	vtxOnSegInx	= clstVtxInx;

		// correct 'vtxOnSegInx' without changing the logic.
		if ( vtxOnSegInx == ( farrVertices.size() - 1 ) )
		{
			// validate.
			ASSERTN( kBStanchev, ( vtxOnSegInx > 0 ) );	// not expected - single-vertex polygon? - check.

			if ( vtxOnSegInx > 0 )
			{
				-- vtxOnSegInx;
			}
		}

		double	sqrDstToPrj;
		Sint32	prjOnSegInx;
		VWPoint2D			clsstPrjPt;

		// get closest projection (if exists).
		if ( this->GetClosestProjPtOnPoly( pt, sqrDstToPrj, prjOnSegInx, clsstPrjPt ) &&	// projection exists and ...
			 ( sqrDstToPrj < sqrDstToVtx ) )												// ... it is closer.
		{
			outSqrDist		= sqrDstToPrj;
			outOnSegInx		= prjOnSegInx;
			outClosestPt	= clsstPrjPt;
		}
		else	// project doesn't exist or it is not closer than the closest vertex.
		{
			outSqrDist		= sqrDstToVtx;
			outOnSegInx		= (Sint32) vtxOnSegInx;
			outClosestPt	= farrVertices[ clstVtxInx ].pt;
		}

		isFound	= true;		// closest already found.
	}
	//else: degenerate empty (no vertices) polygon.

	// result.
	return	( isFound );
}

// returns the index of the closest poly vertex and the squared distance to it.
size_t VWPolygon2D::GetClosestPolyVertex(const VWPoint2D& pt, double& outSqrDist) const
{
	// init.
	size_t			closestPtInx	= -1;

	size_t			vertCnt			= this->GetVertexCount();

	// validate.
	VWFC_ASSERT( vertCnt > 0 );		// poly is empty - bad input.

	if ( vertCnt > 0 )				// non-empty poly.
	{
		for ( size_t i = 0 ; i < vertCnt ; ++ i )
		{
			const VWPoint2D&		vert	= farrVertices[ i ].pt;

			double	sqrDisToVert	= pt.DistanceSquaredTo( vert );

			if ( ( i == 0 ) || ( sqrDisToVert < outSqrDist ) )
			{
				outSqrDist			= sqrDisToVert;
				closestPtInx		= i;
			}
		}
	}

	// result.
	return	( closestPtInx );
}

// finds the closest projection point on the polygon of the given point (if exists). Note: works on polygon with only corner vertices.
// returns closest projection point, squared distance to the projection point and index of the segment where the projection point lies.
bool VWPolygon2D::GetClosestProjPtOnPoly_Fast(const VWPoint2D& pt, double& outSqrDist, Sint32& outOnSegIndex, VWPoint2D& outProjPt) const
{
	size_t							vertCnt		= this->GetVertexCount();
	// validate.
	VWFC_ASSERT( vertCnt > 0 );		// poly is empty! bad input.

	bool							isFound		= false;
	if ( vertCnt > 1 )				// poly has at least two points.
	{
		// compute poly segments to process.
		bool						isClosed	= this->IsClosed();
		size_t						procCnt		= vertCnt;
		if ( ! isClosed )
		{
			-- procCnt;
		}

		for ( size_t i = 0 ; i < procCnt ; ++ i )
		{
			const VWLine2D&			polyLine	= this->GetLineAt( i );
			const VWPoint2D&		lnPt0		= polyLine.GetStart();
			const VWPoint2D&		lnPt1		= polyLine.GetEnd();

			VWPoint2D				projPt;
			// get the projection point on line.
			VWLine2D::PtPerpLine( pt.x, pt.y, lnPt0.x, lnPt0.y, lnPt1.x, lnPt1.y, projPt.x, projPt.y );

			// use a fast check here whether the projection is on the line.
			// get line bounding box.
			VWRectangle2D	bboxLine(	lnPt0.x, lnPt1.x,	// left / right.
										lnPt0.y, lnPt1.y );	// top / bottom.

			// check if point is inside the line bounding box: this will mean that the point lies on the line segment for sure.
			if ( bboxLine.IsPtInside( projPt, VWPoint2D::sEpsilon ) )
			{
				// find current square distance to the projection.
				double				curSqrDist	= VWPoint2D::DistanceSqare( pt.x, pt.y, projPt.x, projPt.y );;

				if ( ( ! isFound ) || ( curSqrDist < outSqrDist ) )
				{
					isFound							= true;

					// the following lines will be reached at least once (see that vertsCnt is > 1)
					outSqrDist						= curSqrDist;
					outProjPt						= projPt;
					outOnSegIndex					= (Sint32)i; 

					if ( outSqrDist < VWPoint2D::sEpsilon )	// stop if point lies on the poly segment.
					{
						break;
					}
				}
			}
		}
	}

	// result.
	return	isFound;
}

// finds the closest projection point on the polygon of the given point (if exists). Note: works on polygon with only corner vertices.
// returns closest projection point, squared distance to the projection point and index of the segment where the projection point lies.
bool VWPolygon2D::GetClosestProjPtOnPoly(const VWPoint2D& inPt, double& outSqrDist, Sint32& outOnSegIndex, VWPoint2D& outProjPt) const
{
	// init.
	bool						isFound		= false;

	size_t						vertCnt		= this->GetVertexCount();
	// validate.
	VWFC_ASSERT( vertCnt > 0 );	// poly is empty! bad input.

	if ( vertCnt > 1 )			// poly has at least two points.
	{
		// compute poly segments to process.
		size_t					procCnt		= vertCnt;
		if ( ! this->IsClosed() )
		{
			-- procCnt;
		}

		// loop polygon segments.
		for ( size_t i = 0 ; i < procCnt ; ++ i )
		{
			// first edge point.
			const VWPoint2D&	thisPt		= farrVertices[ i ].pt;

			// second edge point.
			size_t				nextIndex	= ( i < ( vertCnt - 1 ) ) ? ( i + 1 ) : 0;
			const VWPoint2D&	nextPt		= farrVertices[ nextIndex ].pt;

			// get the line vector.
			VWPoint2D			vecLine		= ( nextPt - thisPt );

			double				sqrLineLen	= vecLine.MagnitudeSquared();

			VWPoint2D			vecThisToPt	= ( inPt - thisPt );

			double				dx			= vecThisToPt.x;
			double				dy			= vecThisToPt.y;

			// get the squared distance from 'thisPt' to 'inPt'.
			double				sqrPtLen	= ( ( dx * dx ) + ( dy * dy ) );	

			// skip zero-length segments.
			if ( sqrLineLen < VWPoint2D::sSqrEpsilon )
			{
				if ( sqrPtLen < VWPoint2D::sSqrEpsilon )	// the point lies on the zero-length line.
				{
					isFound					= true;

					outSqrDist				= 0.0;
					outProjPt				= thisPt;
					outOnSegIndex			= (Sint32) i;

					break;					// found. stop !
				}

				continue;					// go to next segment.
			}

			// get its perpendicular vector.
			VWPoint2D			vecPerp		= vecLine.Perp();

			// check if the point can be projected on the line segment.
			// it is done explicitly as thus are avoided unnecessary repeat operations.
			// --------------------------------------------------------

			VWPoint2D			projPt;		// for the projection point.

			// check if it is on left of first perpendicular line.

			bool				isProjFound	= false;

			// does it coincide with 'thisPt'?
			bool				canProject	= ( sqrPtLen < VWPoint2D::sSqrEpsilon );

			if ( ! canProject )				// point doesn't coincide with 'thisPt'.
			{
				VWPoint2D		perpPt		= ( thisPt + vecPerp );	// get second point on first perpendicular line.

				// check if point is on left of first perpendicular line.
				canProject					= ( ( perpPt.x - thisPt.x ) * dy >= ( perpPt.y - thisPt.y ) * dx );

				if ( canProject )			// point coincides with 'thisPt' or it is on left of first perpendicular line.
				{
					// check if it is on right of second perpendicular line.
					dx						= ( inPt.x - nextPt.x );
					dy						= ( inPt.y - nextPt.y );

					// does it coincide with 'nextPt'?
					canProject				= ( ( dx * dx ) + ( dy * dy ) < VWPoint2D::sSqrEpsilon );

					if ( ! canProject )		// point doesn't coincide with 'nextPt'.
					{
						perpPt				= ( nextPt + vecPerp );	// get second point on second perpendicular line.

						// check if point is on right of first perpendicular line.
						canProject			= ( ( perpPt.x - nextPt.x ) * dy <= ( perpPt.y - nextPt.y ) * dx );
					}
					else					// point coincides with 'nextPt'.
					{
						projPt				= nextPt;
						isProjFound			= true;
					}
				}
			}
			else							// point coincides with 'thisPt'.
			{
				projPt						= thisPt;
				isProjFound					= true;
			}

			if ( canProject )				// the point can be projected on the line segment.
			{
				// so, the point can be projected on the line segment.
				// Note: this also means that it is not a zero-length line.

				// get the projection point.

				if ( ! isProjFound )		// projection point is not found (point doesn't coincide with segment ends).
				{
					// get the length of the projection (start - proj), which is 'proj length' = ( dot product( vecLine, 'start->inPt' ) / 'line length' ).
					// on the other hand the coefficient is 'proj length' / 'line length', so as a whole we have that ...
					// ... the coefficient is ( dot product( vecLine, 'start->inPt' ) / 'squared line length'.
					double		coeff		= ( ( vecLine % vecThisToPt ) / sqrLineLen );

					// validate.
					VWFC_ASSERT( MathUtils::GEish( coeff, 0.0, VWPoint2D::sEpsilon ) &&
								 MathUtils::LEish( coeff, 1.0, VWPoint2D::sEpsilon ) );	// not expected. check !

					// get the projection point (linear interpolation as it is expected to lie on the line segment).
					projPt					= ( ( thisPt * ( 1.0 - coeff ) ) + ( nextPt * coeff ) );
				}

				// find current squared distance to the projection.
				double			curSqrDist	= inPt.DistanceSquaredTo( projPt );

				if ( ( ! isFound ) || ( curSqrDist < outSqrDist ) )
				{
					isFound					= true;

					outSqrDist				= curSqrDist;
					outProjPt				= projPt;
					outOnSegIndex			= (Sint32) i; 

					if ( outSqrDist < VWPoint2D::sSqrEpsilon )	// stop if point lies on the poly segment.
					{
						break;
					}
				}
			}
		}
	}

	// result.
	return	( isFound );
}

// finds the projection point on the polygon of the given point which is closest to the check point. Note: works on polygon with only corner vertices.
// returns projection point, squared distance to the check point and index of the segment where the projection point lies.
bool VWPolygon2D::GetProjPtOnPolyClosestTo(const VWPoint2D& inPt, const VWPoint2D& inCheckPt, double& outSqrDist, Sint32& outOnSegIndex, VWPoint2D& outProjPt) const
{
	// init.
	bool						isFound		= false;

	size_t						vertCnt		= this->GetVertexCount();
	// validate.
	VWFC_ASSERT( vertCnt > 0 );	// poly is empty! bad input.

	if ( vertCnt > 1 )			// poly has at least two points.
	{
		// compute poly segments to process.
		size_t					procCnt		= vertCnt;
		if ( ! this->IsClosed() )
		{
			-- procCnt;
		}

		// loop polygon segments.
		for ( size_t i = 0 ; i < procCnt ; ++ i )
		{
			// first edge point.
			const VWPoint2D&	thisPt		= farrVertices[ i ].pt;

			// second edge point.
			size_t				nextIndex	= ( i < ( vertCnt - 1 ) ) ? ( i + 1 ) : 0;
			const VWPoint2D&	nextPt		= farrVertices[ nextIndex ].pt;

			// get the line vector.
			VWPoint2D			vecLine		= ( nextPt - thisPt );

			double				sqrLineLen	= vecLine.MagnitudeSquared();

			VWPoint2D			vecThisToPt	= ( inPt - thisPt );

			double				dx			= vecThisToPt.x;
			double				dy			= vecThisToPt.y;

			// get the squared distance from 'thisPt' to 'inPt'.
			double				sqrPtLen	= ( ( dx * dx ) + ( dy * dy ) );	

			// skip zero-length segments.
			if ( MathUtils::Equalish( sqrLineLen, 0.0, VWPoint2D::sSqrEpsilon ) )
			{
				if ( MathUtils::Equalish( sqrPtLen, 0.0, VWPoint2D::sSqrEpsilon ) )	// the point lies on the zero-length line.
				{
					// find current squared distance to the projection.
					double		curSqrDist	= inCheckPt.DistanceSquaredTo( thisPt );

					if ( ( ! isFound ) || ( curSqrDist < outSqrDist ) )
					{
						isFound				= true;

						outSqrDist			= curSqrDist;
						outProjPt			= thisPt;
						outOnSegIndex		= (Sint32) i;
					}
				}

				continue;					// go to next segment.
			}

			// get its perpendicular vector.
			VWPoint2D			vecPerp		= vecLine.Perp();

			// check if the point can be projected on the line segment.
			// it is done explicitly as thus are avoided unnecessary repeat operations.
			// --------------------------------------------------------

			VWPoint2D			projPt;		// for the projection point.

			// check if it is on left of first perpendicular line.

			bool				isProjFound	= false;

			// does it coincide with 'thisPt'?
			bool				canProject	= ( sqrPtLen < VWPoint2D::sSqrEpsilon );

			if ( ! canProject )				// point doesn't coincide with 'thisPt'.
			{
				VWPoint2D		perpPt		= ( thisPt + vecPerp );	// get second point on first perpendicular line.

				// check if point is on left of first perpendicular line.
				canProject					= ( ( perpPt.x - thisPt.x ) * dy >= ( perpPt.y - thisPt.y ) * dx );

				if ( canProject )			// point coincides with 'thisPt' or it is on left of first perpendicular line.
				{
					// check if it is on right of second perpendicular line.
					dx						= ( inPt.x - nextPt.x );
					dy						= ( inPt.y - nextPt.y );

					// does it coincide with 'nextPt'?
					canProject				= ( ( dx * dx ) + ( dy * dy ) < VWPoint2D::sSqrEpsilon );

					if ( ! canProject )		// point doesn't coincide with 'nextPt'.
					{
						perpPt				= ( nextPt + vecPerp );	// get second point on second perpendicular line.

						// check if point is on right of first perpendicular line.
						canProject			= ( ( perpPt.x - nextPt.x ) * dy <= ( perpPt.y - nextPt.y ) * dx );
					}
					else					// point coincides with 'nextPt'.
					{
						projPt				= nextPt;
						isProjFound			= true;
					}
				}
			}
			else							// point coincides with 'thisPt'.
			{
				projPt						= thisPt;
				isProjFound					= true;
			}

			if ( canProject )				// the point can be projected on the line segment.
			{
				// so, the point can be projected on the line segment.
				// Note: this also means that it is not a zero-length line.

				// get the projection point.

				if ( ! isProjFound )		// projection point is not found (point doesn't coincide with segment ends).
				{
					// get the length of the projection (start - proj), which is 'proj length' = ( dot product( vecLine, 'start->inPt' ) / 'line length' ).
					// on the other hand the coefficient is 'proj length' / 'line length', so as a whole we have that ...
					// ... the coefficient is ( dot product( vecLine, 'start->inPt' ) / 'squared line length'.
					double		coeff		= ( ( vecLine % vecThisToPt ) / sqrLineLen );

					// validate.
					VWFC_ASSERT( MathUtils::GEish( coeff, 0.0, VWPoint2D::sEpsilon ) &&
								 MathUtils::LEish( coeff, 1.0, VWPoint2D::sEpsilon ) );	// not expected. check !

					// get the projection point (linear interpolation as it is expected to lie on the line segment).
					projPt					= ( ( thisPt * ( 1.0 - coeff ) ) + ( nextPt * coeff ) );
				}

				// find current squared distance to the projection.
				double			curSqrDist	= inCheckPt.DistanceSquaredTo( projPt );

				if ( ( ! isFound ) || ( curSqrDist < outSqrDist ) )
				{
					isFound					= true;

					outSqrDist				= curSqrDist;
					outProjPt				= projPt;
					outOnSegIndex			= (Sint32) i; 

					if ( MathUtils::Equalish( outSqrDist, 0.0, VWPoint2D::sSqrEpsilon ) )	// stop if point lies on the poly segment.
					{
						break;
					}
				}
			}
		}
	}

	// result.
	return	( isFound );
}

// Bozho - review: needs more testing.
// checks if point lies on the polygon part (specified by 'from' and 'to' vertex indices).
// returns: segment index on which the point lies and the offset of the point along the polygon part (from the 'from' vertex).
// note: works on polygonized data only (corner vertices only).
bool VWPolygon2D::IsPtOnPolygonPart(const VWPoint2D& pt, size_t fromVertInx, size_t toVertInx, double epsilon,
									size_t& outOnSegInx, double& outPtOffset) const
{
	VWPolygon2D		polygon			= ( *this );

	// make sure to use polygonized data.
	if ( polygon.HasNonCornerVertices() )
	{
		VWFC_ASSERT( false );		// bad input - check.

		this->GetPolygonized( polygon );
	}

	// init.
	bool			isOnPart		= false;
	outOnSegInx		= -1;
	outPtOffset		= 0.0;

	size_t			vertCnt			= polygon.GetVertexCount();

	// validate.
	if ( VWFC_VERIFY( ( vertCnt > 1 &&										// poly has at least two points and ...
						fromVertInx < vertCnt && toVertInx < vertCnt ) ) )	// ... valid indices.
	{
		size_t		lastVertInx		= ( vertCnt - 1 );

		// get squared epsilon.
		double		sqrEps			= sqr( epsilon );

		// lambda for calculating the length provided 'from' < 'to'.
		auto		IsPtOnPart		= [&] (size_t fromInx, size_t toInx, bool doLoop) -> bool
		{
			double	closestDist;
			double	offset;

			// init.
			bool	notOn			= true;

			size_t	inx				= fromInx;

			// loop segments until the 'to-vertex' is reached.
			do
			{
				size_t				nextInx			= ( doLoop ?
														( inx < lastVertInx ? inx + 1 : 0 ) :
														inx + 1 );

				// segment ends.
				const VWPoint2D&	segPt0			= polygon.GetVertexAt( inx );
				const VWPoint2D&	segPt1			= polygon.GetVertexAt( nextInx );

				// calculate the segment length.
				double				segLength		= segPt0.DistanceTo( segPt1 );

				// check whether point projects on the inx-th segment.
				if ( VWLine2D::IsPtOnLine(	pt,
											segPt0, segPt1, segLength,
											epsilon, closestDist, offset ) )
				{
					outOnSegInx		= inx;
					outPtOffset		+= offset;		// add offset of the point along the current segment.

					notOn			= false;
				}
				else				// check the segment's ends (when point can't be projected on the segment).
				{
					// check against segment starting vertex ('pt'-'segPt0').
					double			sqrDist			= segPt0.DistanceSquaredTo( pt );

					if ( sqrDist < sqrEps )			// within epsilon.
					{
						outOnSegInx	= inx;
						//outPtOffset				+= 0.0;			// plus zero.

						notOn		= false;
					}
					else
					{
						// check against segment ending vertex ('pt'-'segPt1').
						sqrDist		= segPt1.DistanceSquaredTo( pt );

						if ( sqrDist < sqrEps )		// within epsilon.
						{
							outOnSegInx				= inx;
							outPtOffset				+= segLength;	// plus segment length.

							notOn	= false;
						}
					}
				}

				if ( notOn )		// not on current segment.
				{
					// add the segment length.
					outPtOffset		+= segLength;	// plus segment length.
				}

				inx	= nextInx;		// go to next..
			}
			while ( notOn && ( inx != toInx ) );

			// result.
			return	( ! notOn );
		};

		// process:

		// note: if polygon is closed then 'to-index' can be < 'from-index'.
		if ( polygon.IsClosed() )
		{
			if ( fromVertInx < toVertInx )
			{
				// check.
				isOnPart			= IsPtOnPart( fromVertInx, toVertInx, false /*no loop*/ );
			}
			else //if ( fromVertInx >= toVertInx )
			{
				// check.
				isOnPart			= IsPtOnPart( fromVertInx, toVertInx, true /*loop*/ );
			}
		}
		else if ( fromVertInx < toVertInx )
		{
			isOnPart				= IsPtOnPart( fromVertInx, toVertInx, false /*no loop*/ );
		}
	}
	//else: bad input.

	// result.
	return	( isOnPart );
}

// calculates an offset ring poly ouside or inside of this poly.
void VWPolygon2D::GetOffsetRingPoly(double offset, bool doOutsideOffset, VWPolygon2D& offsetRingPoly) const
{
	offsetRingPoly.ClearVertices();

	// get poly center.
	VWPoint2D				cenPt	= this->GetCenter();

	// get the sign of the usable directions.
	double					sign	=  1.0;
	if ( this->IsClockWise() )
	{
		sign						= -1.0;
	}

	if ( ! doOutsideOffset )		// doing inside offset.
	{
		sign						*= -1.0;
	}

	VWPoint2D				prevPt;
	size_t					cnt		= this->GetVertexCount();
	for ( size_t i = 0 ; i < cnt ; ++ i )
	{
		const	VWPoint2D&	pt		= this->GetVertexAt( i );			// current poly point.

		if ( i == 0 )
		{
			if ( ! GetPrevAppositePt( i, prevPt, VWPoint2D::sEpsilon ) )
			{
				ASSERTN( kBStanchev, false );							// not expected to be here. check !

				prevPt				= this->GetVertexAt( cnt - 1 );		// get last point.
			}
		}

		VWPoint2D			nextPt;
		if ( ! GetNextAppositePt( i, nextPt, VWPoint2D::sEpsilon ) )
		{
			ASSERTN( kBStanchev, false );							// not expected to be here. check !

			size_t			nextInx	= ( i < cnt - 1 ? i + 1 : 0 );
			VWPoint2D		nextPt	= this->GetVertexAt( nextInx );
		}

		VWPoint2D			vecPrev	= ( pt - prevPt ).Normalize();		// prev normal vector.
		VWPoint2D			vecNext	= ( nextPt - pt ).Normalize();		// next normal vector.

		// get usable direction.
		VWPoint2D			dir		= ( vecPrev + vecNext ).Normalize();
		dir							= dir.Perp();
		dir							*= sign;

		// if the direction isn't usable use the poly center to find a usable.
		if ( ! MathUtils::Equalish( dir.Magnitude(), 1.0, VWPoint2D::sEpsilon ) )
		{
			dir						= ( pt - cenPt ).Normalize();
		}

		// calculate and store the offset point.
		VWPoint2D			ringPt	= pt + ( offset * dir );
		offsetRingPoly.AddVertex( ringPt );

		prevPt						= pt;								// store prev point.
	}

	// set closed.
	offsetRingPoly.SetClosed( this->IsClosed() );
}

// check if polygon is equalish to this.
// note: to check the equality regardless the direction use reverse check.
bool VWPolygon2D::EqualishTo(const VWPolygon2D& poly, bool doReverseCheck/*=false*/) const
{
	// init.
	bool		areEqual	= false;

	size_t		len			= this->GetVertexCount();

	if ( ( len > 0 ) &&		// at least one point and ...
		 ( len == poly.GetVertexCount() ) )		// ... same length.
	{
		// search for coincidence between first point in 'this' polygon and some point in 'poly'.

		const VWPoint2D&	thisPt0		= this->GetVertexAt( 0 );

		size_t	polyBegInx	= -1;

		for ( size_t i = 0 ; i < len ; ++ i )
		{
			const VWPoint2D& polyPt		= poly.GetVertexAt( i );

			if ( MathUtils::Equalish( thisPt0, polyPt, VWPoint2D::sEpsilon ) )
			{
				polyBegInx	= i;
				areEqual	= true;

				break;		// stop.
			}
		}

		if ( areEqual )		// first point in 'this' polygon coincide with a point in 'poly'.
		{
			VWFC_ASSERT( polyBegInx < len );

			// init.
			size_t			ptInx		= polyBegInx;

			for ( size_t i = 1 ; i < len ; ++ i )
			{
				// increase to the corresponding index.
				++ ptInx;
				if ( ptInx >= len )
				{
					ptInx	= 0;
				}

				// check types.
				EVertexType	vType1		= this->GetVertexType( i );
				EVertexType	vType2		= poly.GetVertexType( ptInx );

				if ( vType1 != vType2 )
				{
					areEqual			= false;
					break;				// difference - stop.
				}

				// check radii.
				if ( vType1 == eVertexType_Arc && 
					this->GetArcVertexRadius( i ) != poly.GetArcVertexRadius( ptInx ) )
				{
					areEqual			= false;
					break;				// difference - stop.
				}

				// check positions.
				if ( ! MathUtils::Equalish( this->GetVertexAt( i ), poly.GetVertexAt( ptInx ), VWPoint2D::sEpsilon ) )
				{
					areEqual			= false;
					break;				// difference - stop.
				}
			}

			if ( doReverseCheck && ( ! areEqual ) )		// 'straight check' has not detected coincidence and reverse check is required.
			{
				// init.
				areEqual	= true;
				ptInx		= polyBegInx;

				for ( size_t i = 1 ; i < len ; ++ i )
				{
					// decrease to corresponding index.
					ptInx	= ( ptInx < 1 ? len - 1 : ptInx - 1 );

					// check types.
					EVertexType			vType1			= this->GetVertexType( i );
					EVertexType			vType2			= poly.GetVertexType( ptInx );

					if ( vType1 != vType2 )
					{
						areEqual		= false;
						break;			// difference - stop.
					}

					// check radii.
					if ( vType1 == eVertexType_Arc && 
						this->GetArcVertexRadius( i ) != poly.GetArcVertexRadius( ptInx ) )
					{
						areEqual		= false;
						break;			// difference - stop.
					}

					// check positions.
					if ( ! MathUtils::Equalish( this->GetVertexAt( i ), poly.GetVertexAt( ptInx ), VWPoint2D::sEpsilon ) )
					{
						areEqual		= false;
						break;			// difference - stop.
					}
				}
			}
		}
	}

	// result.
	return	( areEqual );
}

// is specified point on the edge of the specified polygon
bool VWPolygon2D::IsPtOnPoly2D(const VWPoint2D& pt, double dEpsilon) const
{
	bool	onPoly	= false;
	bool	inPoly	= false;
	this->IsPtOnPoly2D( pt.x, pt.y, onPoly, inPoly, dEpsilon );
	return onPoly;
}

bool VWPolygon2D::IsPtOnPoly2D_Fast(const VWPoint2D& inPt, Sint32& outOnSegIndex, double epsilon) const
{
	// init.
	bool						isOnPoly	= false;
	outOnSegIndex = -1;

	size_t						polyPtCnt	= farrVertices.size();
	if ( polyPtCnt > 1 )		// poly has at least two points.
	{
		// compute poly edges to process.
		size_t					procPtCnt	= polyPtCnt;
		if ( ! this->IsClosed() )
		{
			-- procPtCnt;
		}

		// loop through all edges of the polygon.
		for ( size_t i = 0 ; i < procPtCnt ; ++ i )		// edge from V[i] to V[i+1].
		{
			// first edge point.
			const VWPoint2D&	pt			= farrVertices[ i ].pt;

			// second edge point.
			size_t				nextIndex	= ( i < ( polyPtCnt - 1 ) ) ? ( i + 1 ) : 0;
			const VWPoint2D&	nextPt		= farrVertices[ nextIndex ].pt;

			// use the fast check here.
			if ( VWLine2D::PtOnLine_Fast( inPt, pt, nextPt, epsilon ) )
			{
				isOnPoly					= true;
				outOnSegIndex				= (Sint32)i; 
				break;
			}
		}
	}

	// result.
	return	isOnPoly;
}

// checks if the given point lies on a straight poly segment (with corner vertices).
bool VWPolygon2D::IsPtOnPolyStraightSegment(const VWPoint2D& pt, size_t& outOnStraightSegIndex, double epsilon) const
{
	// init.
	bool					isOnStraightSeg			= false;
	outOnStraightSegIndex							= size_t(-1);	// invalid index.

	size_t					vertsCnt				= this->GetVertexCount();

	if ( vertsCnt > 0 )
	{
		size_t				len						= vertsCnt;
		// don't check the last segment if this is open poly.
		if ( ! this->IsClosed() )
		{
			-- len;
		}

		// find first corner vertex.
		size_t				firstCornerInx			= 0;
		while ( firstCornerInx < len )
		{
			EVertexType		vertType				= this->GetVertexType( firstCornerInx );
			if ( vertType == eVertexType_Corner )	// first corner.
			{
				break;
			}
			++ firstCornerInx;						// increase.
		}

		if ( firstCornerInx < vertsCnt )			// has at least one corner vertex.
		{
			// loop segments.
			VWPoint2D		vertP					= this->GetVertexAt( firstCornerInx );
			size_t			inx						= ( firstCornerInx + 1 );
			while ( inx <= len )
			{
				size_t		inxInPoly;
				// get index in poly.
				if ( inx == vertsCnt )	inxInPoly	= 0;
				else					inxInPoly	= inx;

				EVertexType	vertType				= this->GetVertexType( inxInPoly );

				if ( vertType == eVertexType_Corner )	// corner vertex.
				{
					const VWPoint2D&	vertQ		= this->GetVertexAt( inxInPoly );

					// we have a straight segment.
					VWLine2D	straightLine( vertP, vertQ );

					// check if the point is on this straight segment.
					if ( straightLine.PtOnLine( pt, epsilon ) )
					{
						isOnStraightSeg				= true;
						outOnStraightSegIndex		= ( inx - 1 );

						break;						// stop.
					}

					vertP							= vertQ;

					++ inx;							// increase.
				}
				else								// non-corner vertex.
				{
					++ inx;							// increase.

					// find next corner vertex.
					while ( inx < len )
					{
						EVertexType	vertType		= this->GetVertexType( inx );
						if ( vertType == eVertexType_Corner )
						{
							vertP					= this->GetVertexAt( inx );
							++ inx;					// increase.

							break;					// stop.
						}
						++ inx;						// increase.
					}
				}
			}
		}
		// else: has no corner vertices.
	}
	else
	{
		ASSERTN( kVStanev, false );					// bad input.
	}

	// result.
	return	( isOnStraightSeg );
}

// fast check if point is near (within tolerance) to the polygon.
bool VWPolygon2D::IsPtNearPoly2D(const VWPoint2D& inPt, Sint32& outOnSegIndex, VWPoint2D& outClosestPtOnPoly, double tolerance) const
{
	// init.
	bool						isNearPoly	= false;

	size_t						polyPtCnt	= farrVertices.size();
	if ( polyPtCnt > 1 )		// poly has at least two points.
	{
		// compute poly edges to process.
		size_t					procPtCnt	= polyPtCnt;
		if ( ! this->IsClosed() )
		{
			-- procPtCnt;
		}

		// loop through all edges of the polygon.
		for ( size_t i = 0 ; i < procPtCnt ; ++ i )		// edge from V[i] to V[i+1].
		{
			// first edge point.
			const VWPoint2D&	pt			= farrVertices[ i ].pt;

			// second edge point.
			size_t				nextIndex	= ( i < ( polyPtCnt - 1 ) ) ? ( i + 1 ) : 0;
			const VWPoint2D&	nextPt		= farrVertices[ nextIndex ].pt;

			// use the fast check here.
			if ( VWLine2D::PtNearLine( inPt, pt, nextPt, outClosestPtOnPoly, tolerance ) )
			{
				isNearPoly					= true;
				outOnSegIndex				= (Sint32)i; 
				break;
			}
		}
	}

	// result.
	return	( isNearPoly );
}

// fast check if point is within or near (within tolerance) to the polygon. Note: works on polygon with only corner vertices.
bool VWPolygon2D::IsPtWithinOrNearPoly2D(const VWPoint2D& inPt, bool& outNearPoly, bool& outWithinPoly, Sint32& outOnSegIndex, VWPoint2D& outClosestPtOnPoly, double tolerance) const
{
	// init.
	bool							isInOrNear	= false;
	outNearPoly						= false;
	outWithinPoly					= false;

	// validate.
	ASSERTN( kVStanev, ( this->IsClosed() ) );	// not expected. bad input.

	// check if point is within the polygon bounds.
	VWRectangle2D					bboxPoly	= this->GetPolygonBounds();

	// check if point is within the tolerance to the polygon bounding box.
	// this will mean that point might be near the polygon (limiting the search area).
	if ( bboxPoly.IsPtInside( inPt, tolerance ) )
	{
		size_t						polyPtCnt	= farrVertices.size();
		if ( polyPtCnt > 1 )		// polygon has at least two points (no-empty).
		{
			ptrdiff_t				crossCnt	= 0;    // the horizontal crossings number counter.

			// loop through all edges of the polygon.
			for ( size_t i = 0 ; i < polyPtCnt ; ++ i )	// edge from V[i] to V[i+1].
			{
				// first edge point.
				const VWPoint2D&	thisPt		= farrVertices[ i ].pt;

				// second edge point.
				size_t				nextIndex	= ( i < ( polyPtCnt - 1 ) ) ? ( i + 1 ) : 0;
				const VWPoint2D&	nextPt		= farrVertices[ nextIndex ].pt;

				// use the fast check here.
				if ( VWLine2D::PtNearLine( inPt, thisPt, nextPt, outClosestPtOnPoly, tolerance ) )
				{
					isInOrNear		= true;
					outNearPoly		= true;
					outOnSegIndex	= (Sint32) i;

					break;			// stop. result is found.
				}

				// examine for intersection with the horizontal ray through the point.
				// ( for the check whether the point is within ).

				if ( ( thisPt.y > inPt.y ) != ( nextPt.y > inPt.y ) )		// upward or downward crossing.
				{
					// compute the actual edge-ray intersect x-coordinate.
					double			vt			= ( inPt.y - thisPt.y ) / ( nextPt.y - thisPt.y );	// Note: the divisor is non-zero in this case.

					if ( inPt.x < thisPt.x + vt * ( nextPt.x - thisPt.x ) )	// P.x < intersect.
					{
						// it is a valid crossing of y=P.y right of P.x.
						++ crossCnt;
					}
				}
			}

			if ( ! isInOrNear )		// still not known.
			{
				// check if the point is within the polygon.
				outWithinPoly		= ( crossCnt & 1 ) ? true : false;	// 0 if even (out), and 1 if odd (in).

				isInOrNear			= outWithinPoly;

				// note:
				// it is possible that the point can't be projected on the polygon (no projection on any of the polygon segments exists), ...
				// ... still this doesn't affect the result, i.e. this means such validation (checking whether projections exist) is not correct.
			}
			//else: point is near the line (already found).
		}
	}

	// result.
	return	( isInOrNear );
}

// fast check if point is within or near (within tolerance) to the polygon. Note: works on polygon with only corner vertices.
bool VWPolygon2D::IsPtWithinOrNearPoly2D(const VWPoint2D& inPt, Sint32& outOnSegIndex, VWPoint2D& outClosestPtOnPoly, double tolerance) const
{
	// init.
	bool							isInOrNear	= false;

	// validate.
	ASSERTN( kVStanev, ( this->IsClosed() ) );	// not expected. bad input.

	// check if point is within the polygon bounds.
	VWRectangle2D					bboxPoly	= this->GetPolygonBounds();

	// check if point is within the tolerance to the polygon bounding box.
	// this will mean that point might be near the polygon (limiting the search area).
	if ( bboxPoly.IsPtInside( inPt, tolerance ) )
	{
		size_t						polyPtCnt	= farrVertices.size();
		if ( polyPtCnt > 1 )		// polygon has at least two points (no-empty).
		{
			ptrdiff_t				crossCnt	= 0;    // the horizontal crossings number counter.

			// loop through all edges of the polygon.
			for ( size_t i = 0 ; i < polyPtCnt ; ++ i )	// edge from V[i] to V[i+1].
			{
				// first edge point.
				const VWPoint2D&	thisPt		= farrVertices[ i ].pt;

				// second edge point.
				size_t				nextIndex	= ( i < ( polyPtCnt - 1 ) ) ? ( i + 1 ) : 0;
				const VWPoint2D&	nextPt		= farrVertices[ nextIndex ].pt;

				// use the fast check here.
				if ( VWLine2D::PtNearLine( inPt, thisPt, nextPt, outClosestPtOnPoly, tolerance ) )
				{
					isInOrNear					= true;
					outOnSegIndex				= (Sint32) i;

					break;						// stop. result is found.
				}

				// examine for intersection with the horizontal ray through the point.
				// ( for the check whether the point is within ).

				if ( ( thisPt.y > inPt.y ) != ( nextPt.y > inPt.y ) )		// upward or downward crossing.
				{
					// compute the actual edge-ray intersect x-coordinate.
					double			vt			= ( inPt.y - thisPt.y ) / ( nextPt.y - thisPt.y );	// Note: the divisor is non-zero in this case.

					if ( inPt.x < thisPt.x + vt * ( nextPt.x - thisPt.x ) )	// P.x < intersect.
					{
						// it is a valid crossing of y=P.y right of P.x.
						++ crossCnt;
					}
				}
			}

			if ( ! isInOrNear )					// still not known.
			{
				// check if the point is within the polygon.
				isInOrNear						= ( crossCnt & 1 ) ? true : false;	// 0 if even (out), and 1 if odd (in).
			}
		}
	}

	// result.
	return	( isInOrNear );
}

// fast check if point is within the polygon. Note: no epsilon/tolerance is used here.
bool VWPolygon2D::IsPtWithinPoly2D(const VWPoint2D& inPt) const
{
	// init.
	bool							isWithin	= false;

	// validate.
	ASSERTN( kVStanev, ( this->IsClosed() ) );	// not expected. bad input.

	// check if point is within the polygon bounds.
	VWRectangle2D					bboxPoly	= this->GetPolygonBounds();

	// check if point is within the polygon bounding box.
	// this will mean that point might be within the polygon (limiting the search area).
	if ( bboxPoly.IsPtInside( inPt ) )
	{
		size_t						polyPtCnt	= farrVertices.size();
		if ( polyPtCnt > 1 )		// polygon has at least two points (no-empty).
		{
			ptrdiff_t				crossCnt	= 0;    // the horizontal crossings number counter.

			// loop through all edges of the polygon.
			for ( size_t i = 0 ; i < polyPtCnt ; ++ i )	// edge from V[i] to V[i+1].
			{
				// first edge point.
				const VWPoint2D&	thisPt		= farrVertices[ i ].pt;

				// second edge point.
				size_t				nextIndex	= ( i < ( polyPtCnt - 1 ) ) ? ( i + 1 ) : 0;
				const VWPoint2D&	nextPt		= farrVertices[ nextIndex ].pt;

				// examine for intersection with the horizontal ray through the point.
				// ( for the check whether the point is within ).

				if ( ( thisPt.y > inPt.y ) != ( nextPt.y > inPt.y ) )		// upward or downward crossing.
				{
					// compute the actual edge-ray intersect x-coordinate.
					double			vt			= ( inPt.y - thisPt.y ) / ( nextPt.y - thisPt.y );	// Note: the divisor is non-zero in this case.

					if ( inPt.x < thisPt.x + vt * ( nextPt.x - thisPt.x ) )	// P.x < intersect.
					{
						// it is a valid crossing of y=P.y right of P.x.
						++ crossCnt;
					}
				}
			}

			// check if the point is within the polygon.
			isWithin							= ( crossCnt & 1 ) ? true : false;	// 0 if even (out), and 1 if odd (in).
		}
	}

	// result.
	return	( isWithin );
}

// determines if a point is in the area of a given polygon (the 2D projection)
bool VWPolygon2D::IsPtInPoly2D(double ptX, double ptY, double dEpsilon) const
{
	bool	onPoly	= false;
	bool	inPoly	= false;
	this->IsPtOnPoly2D( ptX, ptY, onPoly, inPoly, dEpsilon );
	return inPoly;
}

bool VWPolygon2D::IsPtInPoly2D(const VWPoint2D& pt, double dEpsilon) const
{
	bool	onPoly	= false;
	bool	inPoly	= false;
	this->IsPtOnPoly2D( pt.x, pt.y, onPoly, inPoly, dEpsilon );
	return inPoly;
}

bool VWPolygon2D::IsPtInPoly2D_Fast(double ptX, double ptY, double dEpsilon) const
{
	// not using epsilon -- but we should
	dEpsilon;

	ptrdiff_t	cn			= 0;    // the crossing number counter

	size_t	polyPtCnt	= farrVertices.size();
	// loop through all edges of the polygon
	for (size_t i=0; i<polyPtCnt; i++) {    // edge from V[i] to V[i+1]
		const VWPoint2D&	pt		= farrVertices[i].pt;
		const VWPoint2D&	nextPt	= i+1 < polyPtCnt ? farrVertices[i+1].pt : farrVertices[0].pt;

		double				Vix		= pt.x;
		double				Viy		= pt.y;
		double				Vi1x	= nextPt.x;
		double				Vi1y	= nextPt.y;

		if (((Viy <= ptY) && (Vi1y > ptY))    // an upward crossing
			|| ((Viy > ptY) && (Vi1y <= ptY))) { // a downward crossing
			// compute the actual edge-ray intersect x-coordinate
			double vt = (double)(ptY - Viy) / (Vi1y - Viy);
			if ( ptX < Vix + vt * (Vi1x - Vix) ) // P.x < intersect
				++cn;   // a valid crossing of y=P.y right of P.x
		}
	}

	return (cn&1);    // 0 if even (out), and 1 if odd (in)
}

bool VWPolygon2D::IsPtOnPoly2D(double ptX, double ptY, double dEpsilon) const
{
	bool	onPoly	= false;
	bool	inPoly	= false;
	this->IsPtOnPoly2D( ptX, ptY, onPoly, inPoly, dEpsilon );
	return onPoly;
}

// combined operations
bool VWPolygon2D::IsPtInOrOnPoly2D(double ptX, double ptY, double dEpsilon) const
{
	bool	onPoly	= false;
	bool	inPoly	= false;
	this->IsPtOnPoly2D( ptX, ptY, onPoly, inPoly, dEpsilon );
	return onPoly || inPoly;
}

bool VWPolygon2D::IsPtInOrOnPoly2D(const VWPoint2D& pt, double dEpsilon) const
{
	bool	onPoly	= false;
	bool	inPoly	= false;
	this->IsPtOnPoly2D( pt.x, pt.y, onPoly, inPoly, dEpsilon );
	return onPoly || inPoly;
}

void VWPolygon2D::IsPtOnPoly2D(const VWPoint2D& pt, bool& outOnPoly, bool& outInPoly, double dEpsilon) const
{
	this->IsPtOnPoly2D( pt.x, pt.y, outOnPoly, outInPoly, dEpsilon );
}

void VWPolygon2D::IsPtOnPoly2D(double ptX, double ptY, bool& outOnPoly, bool& outInPoly, double dEpsilon) const
{
	VWPoint2D	inPt( ptX, ptY );

	outOnPoly			= false;
	ptrdiff_t	cn			= 0;    // the crossing number counter

	size_t	polyPtCnt	= farrVertices.size();
	// loop through all edges of the polygon
	for (size_t i=0; i<polyPtCnt; i++) {    // edge from V[i] to V[i+1]
		const VWPoint2D&	pt		= farrVertices[i].pt;
		const VWPoint2D&	nextPt	= i+1 < polyPtCnt ? farrVertices[i+1].pt : farrVertices[0].pt;

		outOnPoly	= VWLine2D::PtOnLine( inPt, pt, nextPt, dEpsilon );
		// if it is on poly break -- we have 'on poly' and dont have 'in poly'
		if ( outOnPoly ) 
			break;

		double				Vix		= pt.x;
		double				Viy		= pt.y;
		double				Vi1x	= nextPt.x;
		double				Vi1y	= nextPt.y;

		if (((Viy <= ptY) && (Vi1y > ptY))    // an upward crossing
			|| ((Viy > ptY) && (Vi1y <= ptY))) { // a downward crossing
			// compute the actual edge-ray intersect x-coordinate
			double vt = (double)(ptY - Viy) / (Vi1y - Viy);
			if ( ptX < Vix + vt * (Vi1x - Vix) ) // P.x < intersect
				++cn;   // a valid crossing of y=P.y right of P.x
		}
	}

	// if we have 'on poly' means that we dont have 'in poly'
	if ( ! outOnPoly ) {
		outInPoly	= ( cn & 1 ) ? true : false;    // 0 if even (out), and 1 if odd (in)
	}
	else {
		outInPoly	= false;
	}

/*	size_t	len		= farrVertices.size();
	if ( len <= 2 )
		return false;

	// find Inside poly 
	VWPoint2D	p	= pt;
	VWPoint2D	thisPt	= farrVertices[ len - 1 ].pt;
	VWPoint2D	lastPt;

	bool right1		= thisPt.x >= pt.x;
	bool high1		= thisPt.y >= pt.y;

	bool right2, high2;

	short	cross	= 0;
	for (size_t i=0; i<len; i++)
	{
		lastPt	= thisPt;
		thisPt	= farrVertices[ i ].pt;

		if ( thisPt.Equal( lastPt, dEpsilon ) )
			continue;

		VWLine2D	line( thisPt, lastPt );
		if ( line.PtOnLine( p, dEpsilon ) )
		{
			cross	= 0;
			break;
		}

		right2 = thisPt.x >= pt.x;
		high2  = thisPt.y >= pt.y;

		if ( high1 != high2 )
		{
			if ( right1 != right2 )
			{
				// cross=maybe			
				double_gs	test = lastPt.x + (thisPt.x - lastPt.x)*(p.y - lastPt.y)/(double_gs)(thisPt.y - lastPt.y);

				if (test == 0)
				{
					cross = 0;
					break;
				//	return false;
				}
				else if (test >= p.x) 
					cross++;
			}
			else {
				if (right1) {
					if ( thisPt.x == pt.x && lastPt.x == pt.x ) {
						//AND right2 follows, since theY are Equalrich:test this for new Clip,
						// if pt lay on horizontal edge, then it is not
						// Inside
						
						cross	= 0;
						break;
						//return false;
					}
					cross++;
				}
			}
		}
		right1	= right2;
		high1	= high2;
	}


	bool res = (cross & 1) != 0L;
	return res;*/
}

// return true if the specified line intersects the poly
bool VWPolygon2D::IsIntersecting(const VWLine2D& line, double dEpsilon, VWPoint2D* /*out*/ pInsertPt/*=NULL*/) const
{
	// not using epsilon -- but we should
	dEpsilon;

	size_t		vertsCnt	= farrVertices.size();
	size_t		len			= vertsCnt;
	if ( len == 0 )
		return false;

	// dont check the last legment if this is open poly
	if ( ! fbIsClosed )
		len --;

	if ( len == 0 )
		return false;

	VWPoint2D	insertPt;
	VWPoint2D	p			= farrVertices[ 0 ].pt;
	for(size_t i=1; i<=len; i++)
	{
		VWPoint2D		q;
		if ( i == vertsCnt )	q	= farrVertices[ 0 ].pt;
		else					q	= farrVertices[ i ].pt;

		VWLine2D	curLine( p, q );
		if ( line.IntersectLineSegments( curLine, insertPt ) )
		{
			if ( pInsertPt )
				(*pInsertPt)		= insertPt;
			return true;
		}

		p		= q;
	}

	return false;
}

bool VWPolygon2D::IsIntersecting(const VWPoint2D& a, const VWPoint2D& b, double dEpsilon, VWPoint2D* /*out*/ pInsertPt/*=NULL*/) const
{
	// not using epsilon -- but we should
	dEpsilon;

	size_t		len			= farrVertices.size();
	if ( len == 0 )
		return false;

	// dont check the last legment if this is open poly
	if ( ! fbIsClosed )
		len --;

	if ( len == 0 )
		return false;

	VWPoint2D	insertPt;
	VWPoint2D	p			= farrVertices[ 0 ].pt;
	for(size_t i=1; i<=len; i++)
	{
		VWPoint2D		q;
		if ( i == len )	q	= farrVertices[ 0 ].pt;
		else			q	= farrVertices[ i ].pt;

		VWLine2D	curLine( p, q );
		if ( curLine.IntersectLineSegments( a, b, insertPt ) )
		{
			if ( pInsertPt )
				(*pInsertPt)		= insertPt;
			return true;
		}

		p		= q;
	}

	return false;
}

// return true if the specified line intersects the poly
bool VWPolygon2D::IsIntersecting(const VWLine2D& line, double dEpsilon, TSTLPoints2DArray& outArrIntersectPts) const
{
	
	size_t		vertsCnt	= farrVertices.size();
	size_t		len			= vertsCnt;
	if ( len == 0 )
		return false;

	// dont check the last legment if this is open poly
	if ( ! fbIsClosed )
		len --;

	if ( len == 0 )
		return false;

	const VWPoint2D& a = line.GetStart();
	const VWPoint2D& b = line.GetEnd();
	double inMinX = min( a.x, b.x );
	double inMaxX = max( a.x, b.x );
	double inMinY = min( a.y, b.y );
	double inMaxY = max( a.y, b.y );

	VWPoint2D	insertPt;
	VWPoint2D	p			= farrVertices[ 0 ].pt;
	bool foundIntersectPoint = false;
	for(size_t i=1; i<=len; i++)
	{
		bool bSimilarPts = false;
		VWPoint2D		q;
		if ( i == vertsCnt )	q	= farrVertices[ 0 ].pt;
		else					q	= farrVertices[ i ].pt;

		double thisMinX = min( p.x, q.x );
		double thisMaxX = max( p.x, q.x );
		double thisMinY = min( p.y, q.y );
		double thisMaxY = max( p.y, q.y );

		bool isNotInters = 
					(inMaxX < thisMinX || inMinX > thisMaxX)
				&&	(inMaxY < thisMinY || inMinY > thisMaxY)
				;

		if ( ! isNotInters )
		{
			VWLine2D	curLine( p, q );
			if ( line.IntersectLineSegments( curLine, insertPt ) )
			{
				size_t arraySize = outArrIntersectPts.size();

				if( arraySize == 0 ) {
					outArrIntersectPts.push_back( insertPt );
					foundIntersectPoint = true;
				}
				else {
					for( size_t k = 0; k < arraySize; k++ ) 
					{
						if( WorldPtsAreRelativelyClose( insertPt, outArrIntersectPts[k], dEpsilon ) ) 
						{
							bSimilarPts = true;
							break;
						}					
					}

					if( !bSimilarPts ) 
					{
						outArrIntersectPts.push_back( insertPt );
						foundIntersectPoint = true;
					}
				}
			}
		}

		p		= q;
	}

	return foundIntersectPoint;
}

// returns true if the specified line intersects the poly. returns the intersection points and the corresponding intersected segments.
bool VWPolygon2D::IsIntersecting(const VWLine2D& line, double epsilon, TSTLPoints2DArray& outIntersPts, TSizeTArray& outIntersSegs) const
{
	// init.
	bool					hasInters	= false;

	size_t					vertsCnt	= farrVertices.size();

	if ( vertsCnt > 1 )			// polygon is not empty.
	{
		size_t				len			= vertsCnt;

		// don't check the last segment if this is open poly.
		if ( ! fbIsClosed )
		{
			-- len;
		}

		VWPoint2D			insertPt;
		VWPoint2D			p			= farrVertices[ 0 ].pt;

		// loop.
		for ( size_t i = 1 ; i <= len ; ++ i )
		{
			VWPoint2D		q;

			if ( i == vertsCnt )	q	= farrVertices[ 0 ].pt;
			else					q	= farrVertices[ i ].pt;

			if ( line.IntersectLineSegments( p, q, insertPt ) )
			{
				size_t		intersCnt	= outIntersPts.size();

				bool		doAddPt		= false;

				// check if point has to be added (there is not an equal intersection point already added).
				if ( intersCnt == 0 )
				{
					doAddPt				= true;
				}
				else
				{
					doAddPt				= true;
					// check if there is a 'equal' point 
					for( size_t k = 0 ; k < intersCnt ; ++ k ) 
					{
						if ( MathUtils::Equalish( insertPt, outIntersPts[ k ], epsilon ) )
						{
							doAddPt		= false;
							break;		// found 'equal'. stop.
						}					
					}
				}

				if( doAddPt )			// has to be added.
				{
					outIntersPts.push_back( insertPt );

					size_t	prevIndex	= ( i - 1 );	// Note that ( i >= 1 ) here.
					outIntersSegs.push_back( prevIndex );

					hasInters			= true;
				}
			}

			// update for next.
			p							= q;
		}
	}

	// result.
	return	( hasInters );
}

// return true if the specified line intersects the poly
bool VWPolygon2D::IsRayIntersecting(const VWLine2D& line, double dEpsilon, TSTLPoints2DArray& outArrIntersectPts) const
{
	bool bSimilarPts = true;
	size_t		vertsCnt	= farrVertices.size();
	size_t		len			= vertsCnt;
	if ( len == 0 )
		return false;

	// dont check the last legment if this is open poly
	if ( ! fbIsClosed )
		len --;

	if ( len == 0 )
		return false;

	VWPoint2D	insertPt;
	VWPoint2D	p			= farrVertices[ 0 ].pt;
	bool foundIntersectPoint = false;
	for(size_t i=1; i<=len; i++)
	{
		VWPoint2D		q;
		if ( i == vertsCnt )	q	= farrVertices[ 0 ].pt;
		else					q	= farrVertices[ i ].pt;

		VWLine2D	curLine( p, q );
		bool isParallel, onSeg1, onSeg2;
		VWLine2D::IntersectLines( line.GetStart(), line.GetEnd(), curLine.GetStart()
			, curLine.GetEnd(), insertPt, isParallel, onSeg1, onSeg2 );
		if ( onSeg2 )
		{
			size_t arraySize = outArrIntersectPts.size();

			if( arraySize == 0 ) {
				outArrIntersectPts.push_back( insertPt );
				foundIntersectPoint = true;
			}
			else
			{
				bSimilarPts = false;
				for ( size_t k = 0; k < arraySize && !bSimilarPts; k++ )
				{
					if( WorldPtsAreRelativelyClose( insertPt, outArrIntersectPts[k], dEpsilon ) )
					{
						bSimilarPts = true;
					}
				}

				if( !bSimilarPts ) {
					outArrIntersectPts.push_back( insertPt );
					foundIntersectPoint = true;
				}
			}
		}

		p		= q;
	}

	return foundIntersectPoint;
}


bool VWPolygon2D::IsIntersecting(const VWPoint2D& a, const VWPoint2D& b, double dEpsilon, TSTLPoints2DArray& outArrIntersectPts) const
{
	VWLine2D tempLine( a, b );

	return this->IsIntersecting( tempLine, dEpsilon, outArrIntersectPts );

	/*
	// not using epsilon -- but we should
	dEpsilon;

	size_t		len			= farrVertices.size();
	if ( len == 0 )
		return false;

	// dont check the last legment if this is open poly
	if ( ! fbIsClosed )
		len --;

	if ( len == 0 )
		return false;

	VWPoint2D	insertPt;
	VWPoint2D	p			= farrVertices[ 0 ].pt;
	bool foundIntersectPoint = false;
	for(size_t i=1; i<=len; i++)
	{
		VWPoint2D		q;
		if ( i == len )	q	= farrVertices[ 0 ].pt;
		else			q	= farrVertices[ i ].pt;

		VWLine2D	curLine( p, q );
		if ( curLine.IntersectLineSegments( a, b, insertPt ) )
		{
			outArrIntersectPts.push_back( insertPt );
			foundIntersectPoint = true;
		}

		p		= q;
	}

	return foundIntersectPoint;*/
}

// return true if the given polygon and this polygon intersects each other
// intersect 'true' means that they have intersection points or same points
bool VWPolygon2D::IsIntersecting(const VWPolygon2D& poly, double dEpsilon) const
{
	size_t		polyLen		= poly.farrVertices.size();
	if ( polyLen == 0 )
		return false;

	// dont consider the last line (end-start) if poly is open
	if ( ! poly.IsClosed() )
		polyLen--;

	bool		bInters		= false;
	for(size_t i=0; i<polyLen; i++)
	{
		VWLine2D		line	= poly.GetLineAt( i );
		if ( this->IsIntersecting( line, dEpsilon, NULL ) ) {
			bInters		= true;
			break;
		}
	}

	return bInters;
}

// returns 'true' if the given polygon and this polygon intersect each other (including touching).
// this means that they have intersection points or same points.
// in 'outArrIntersPts' returns all intersection points.
// NOTE: this function will be slower as it will search for all intersection points.
bool VWPolygon2D::IsIntersecting(const VWPolygon2D& poly, double epsilon, TSTLPoints2DArray& outArrIntersPts) const
{
	// init.
	bool				hasInters	= false;
	outArrIntersPts.clear();

	size_t				polyLen		= poly.farrVertices.size();

	if ( polyLen > 0 )
	{
		// don't consider the last line (end-start) if poly is open.
		if ( ! poly.IsClosed() )
		{
			-- polyLen;
		}

		for ( size_t i = 0 ; i < polyLen ; ++ i )
		{
			VWLine2D	line		= poly.GetLineAt( i );

			TSTLPoints2DArray	arrIntersLinePts;
			if ( this->IsIntersecting( line, epsilon, arrIntersLinePts ) )
			{
				hasInters			= true;

				// add the newly found intersection points.
				outArrIntersPts.insert( outArrIntersPts.end(), arrIntersLinePts.begin(), arrIntersLinePts.end() );
			}
		}
	}

	// result.
	return	( hasInters );
}

bool VWPolygon2D::IsIntersecting(const VWPolygon2D& poly, bool& outIsTouching, double epsilon) const
{
	VWPoint2D	pt;
	return this->IsIntersecting( poly, outIsTouching, pt, epsilon );
}

// retun true if the given polygon and this polygon intersects each other (including touching).
// outIsTouching returns if they are tourching
bool VWPolygon2D::IsIntersecting(const VWPolygon2D& poly, bool& outIsTouching, VWPoint2D& outIntersPt, double epsilon) const
{
	// init.
	bool							hasInters			= false;
	bool							hasClearInters		= false;

	size_t							polyLen				= poly.farrVertices.size();
	if ( polyLen > 0 )
	{
		// don't consider the last line (end-start) if poly is open.
		if ( ! poly.IsClosed() )
		{
			-- polyLen;
		}

		bool						goOn				= true;

		// loop.
		for ( size_t i = 0 ; ( i < polyLen ) && goOn ; ++ i )
		{
			VWLine2D				line				= poly.GetLineAt( i );
		
			size_t					vertsCnt			= farrVertices.size();
			size_t					len					= vertsCnt;
			if ( len > 0 )
			{
				// don't check the last segment if this is open poly.
				if ( ! fbIsClosed )
				{
					-- len;
				}

				if ( len > 0 )
				{
					VWPoint2D		insertPt;
					VWPoint2D		p					= farrVertices[ 0 ].pt;

					for ( size_t j = 1 ; j <= len ; ++ j )
					{
						VWPoint2D	q;
						if ( j == vertsCnt )	q		= farrVertices[ 0 ].pt;
						else					q		= farrVertices[ j ].pt;

						VWLine2D	curLine( p, q );
						bool		onSegment;
						VWPoint2D	intersPt;

						if ( line.IntersectLines( curLine, intersPt, onSegment ) )
						{
							if ( onSegment )
							{
								hasInters				= true;
								outIntersPt				= intersPt;

								// check for special cases for the intersection point.
								bool	atPolyLineEnd	= intersPt.Equal( line.GetEnd(),		epsilon );
								bool	atPolyLineBeg	= intersPt.Equal( line.GetStart(),		epsilon );
								bool	atThisLineEnd	= intersPt.Equal( curLine.GetEnd(),		epsilon );
								bool	atThisLineBeg	= intersPt.Equal( curLine.GetStart(),	epsilon );

								if ( ! atPolyLineEnd && ! atPolyLineBeg &&	// intersecting point not on poly line ending points and ...
									 ! atThisLineEnd && ! atThisLineBeg )	// ... intersecting point not on this line ending points.
								{
									hasClearInters		= true;
								}
								else
								{
									// here we have a vertex lying on line (segment).
									// additional checks whether line intersects the poly, or just touching it.

									if		( atPolyLineBeg )				// intersecting point on poly line start point.
									{
										// check if the two polys intersect at the vertex lying on line (segment) or they are just touching.
										// Note that:
										// - the vertex which lies on the line (segment) is given by 'i' and it is a correct index in 'poly'.
										// - the line (segment) on which the vertex lies is given by '( j - 1 )' and it is a correct index in 'this poly'.
										hasClearInters	= poly.IsPolyIntersectingPolyAt( i, *this, ( j - 1 ), epsilon );
									}
									else if	( atThisLineBeg )				// intersecting point on this line start point.
									{
										// check if the two polys intersect at the vertex lying on line (segment) or they are just touching.
										// Note that:
										// - the vertex which lies on the line (segment) is given by '( j - 1 )' and it is a correct index in 'this poly'.
										// - the line (segment) on which the vertex lies is given by 'i' and it is a correct index in 'poly'.
										hasClearInters	= this->IsPolyIntersectingPolyAt( ( j - 1 ), poly, i , epsilon );
									}
								}

								if ( hasClearInters )						// already known that polygons intersect each other (and not just touching).
								{
									goOn				= false;			// stop outer loop.
									break;									// stop inner loop.
								}
							}
						}
						else if ( onSegment )								// the two lines are parallel and lie on each other.
						{
							hasInters					= true;
							outIntersPt					= intersPt;
						}

						p								= q;
					}
				}
			}
		}
	}

	// check if polys just touch (not clear intersection).
	outIsTouching		= ( hasInters && ! hasClearInters );

	// result.
	return	( hasInters );
}

// retuns 'true' if the given polygon and this polygon intersects each other (including touching).
// 'outIsTouching' returns if they are touching. 'outArrIntersPts' returns all intersection points.
// NOTE: this function will be slower as it will search for all intersection points.
bool VWPolygon2D::IsIntersecting(const VWPolygon2D& poly, bool& outIsTouching, TSTLPoints2DArray& outArrIntersPts, double epsilon) const
{
	// init.
	bool								hasInters			= false;
	bool								hasClearInters		= false;

	size_t								polyLen				= poly.farrVertices.size();
	if ( polyLen > 0 )
	{
		// don't consider the last line (end-start) if poly is open.
		if ( ! poly.IsClosed() )
		{
			-- polyLen;
		}

		for ( size_t i = 0 ; i < polyLen ; ++ i )
		{
			VWLine2D					line				= poly.GetLineAt( i );

			size_t						vertsCnt			= this->farrVertices.size();
			size_t						len					= vertsCnt;
			if ( len > 0 )
			{
				// don't check the last segment if this is open poly.
				if ( ! fbIsClosed )
				{
					-- len;
				}

				if ( len > 0 )
				{
					VWPoint2D			p					= this->farrVertices[ 0 ].pt;
					for ( size_t j = 1 ; j <= len ; ++ j )
					{
						VWPoint2D		q;
						if ( j == vertsCnt )	q			= this->farrVertices[ 0 ].pt;
						else					q			= this->farrVertices[ j ].pt;

						VWLine2D		curLine( p, q );
						bool			onSegment;
						VWPoint2D		intersPt;

						if ( line.IntersectLines( curLine, intersPt, onSegment ) )
						{
							if ( onSegment )
							{
								hasInters					= true;
								outArrIntersPts.push_back( intersPt );

								if ( ! hasClearInters )							// still not decided whether polygons touch or intersect each other.
								{
									// check for special cases for the intersection point.
									bool	atPolyLineEnd	= intersPt.Equal( line.GetEnd(),		epsilon );
									bool	atPolyLineBeg	= intersPt.Equal( line.GetStart(),		epsilon );
									bool	atThisLineEnd	= intersPt.Equal( curLine.GetEnd(),		epsilon );
									bool	atThisLineBeg	= intersPt.Equal( curLine.GetStart(),	epsilon );

									if ( ! atPolyLineEnd && ! atPolyLineBeg &&	// intersecting point not on poly line ending points and ...
										 ! atThisLineEnd && ! atThisLineBeg )	// ... intersecting point not on this line ending points.
									{
										hasClearInters		= true;
									}
									else
									{
										// here we have a vertex lying on line.
										// additional checks whether line intersects the poly, or just touching it.

										if		( atPolyLineBeg )				// intersecting point on poly line start point.
										{
											// check if the two polys intersect at the vertex lying on line (segment) or they are just touching.
											// Note that:
											// - the vertex which lies on the line (segment) is given by 'i' and it is a correct index in 'poly'.
											// - the line (segment) on which the vertex lies is given by '( j - 1 )' and it is a correct index in 'this poly'.
											hasClearInters	= poly.IsPolyIntersectingPolyAt( i, *this, ( j - 1 ), epsilon );
										}
										else if	( atThisLineBeg )				// intersecting point on this line start point.
										{
											// check if the two polys intersect at the vertex lying on line (segment) or they are just touching.
											// Note that:
											// - the vertex which lies on the line (segment) is given by '( j - 1 )' and it is a correct index in 'this poly'.
											// - the line (segment) on which the vertex lies is given by 'i' and it is a correct index in 'poly'.
											hasClearInters	= this->IsPolyIntersectingPolyAt( ( j - 1 ), poly, i , epsilon );
										}
									}
								}
							}
						}
						else if ( onSegment )
						{
							hasInters						= true;
							outArrIntersPts.push_back( intersPt );
						}

						p									= q;
					}
				}
			}
		}
	}

	// check if polys just touch (not clear intersection).
	outIsTouching		= ( hasInters && ! hasClearInters );

	// result.
	return	( hasInters );
}

// returns 'true' if the given polygon and this polygon intersects each other (including touching).
// 'outIsTouching' returns if they are touching. 'outArrIntersPts' returns all intersection points. 'outArrTouchPts' returns all touching points.
// NOTE: this function will be slower as it will search for all intersection and touching points.
bool VWPolygon2D::IsIntersecting(const VWPolygon2D& poly, bool& outIsTouching, TSTLPoints2DArray& outArrIntersPts, TSTLPoints2DArray& outArrTouchPts, double epsilon) const
{
	// init.
	bool								hasIntersOrTouch	= false;
	bool								hasClearInters		= false;

	size_t								polyLen				= poly.farrVertices.size();
	if ( polyLen > 0 )
	{
		bool							isPolyClosed		= poly.IsClosed();

		// don't consider the last line (end-start) if poly is open.
		if ( ! isPolyClosed )
		{
			-- polyLen;
		}

		VWPoint2D						sleepPtToPoly, sleepPtToThis, suspectPtToThis;
		bool							hasSleepyToThis		= false;

		for ( size_t i = 0 ; i < polyLen ; ++ i )			// loop 'poly' segments.
		{
			VWLine2D					line				= poly.GetLineAt( i );

			size_t						vertsCnt			= this->farrVertices.size();
			size_t						len					= vertsCnt;
			if ( len > 0 )
			{
				// don't check the last segment if this is open poly.
				if ( ! fbIsClosed )
				{
					-- len;
				}

				if ( len > 0 )
				{
					bool				hasAtPolyLineBeg	= false;
					bool				hasSuspectToThis	= false;
					bool				hasSleepyToPoly		= false;

					VWPoint2D			p					= this->farrVertices[ 0 ].pt;
					for ( size_t j = 1 ; j <= len ; ++ j )	// loop 'this poly' segments.
					{
						VWPoint2D		q;
						if ( j == vertsCnt )	q			= this->farrVertices[ 0 ].pt;
						else					q			= this->farrVertices[ j ].pt;

						VWLine2D		curLine( p, q );
						VWPoint2D		intersPt;
						bool			parallel			= false;

						bool			atThisLineBeg		= false;
						bool			atPolyLineBeg		= false;
						bool			hasSuspectToPoly	= false;

						// check for intersection between the line segments.
						bool			onSegments			= line.AreLineSegmentsIntersecting( curLine, intersPt, parallel, VWPoint2D::sEpsilon );

						if ( onSegments && ! parallel )		// intersection between non-parallel line segments.
						{
							hasIntersOrTouch				= true;

							// check if it is an intersection or just touching between polygons.

							bool		isTouching			= true;
							bool		isDecided			= false;

							// check for special cases for the intersection point.
							bool		atPolyLineEnd		= intersPt.Equal( line.GetEnd(),		epsilon );
							atPolyLineBeg					= intersPt.Equal( line.GetStart(),		epsilon );
							bool		atThisLineEnd		= intersPt.Equal( curLine.GetEnd(),		epsilon );
							atThisLineBeg					= intersPt.Equal( curLine.GetStart(),	epsilon );

							if ( ! atPolyLineEnd && ! atPolyLineBeg &&	// intersecting point not on poly line ending points and ...
								 ! atThisLineEnd && ! atThisLineBeg )	// ... intersecting point not on this line ending points.
							{
								isTouching					= false;		// clear intersection.

								isDecided					= true;			// estimation is made.
							}
							else
							{
								// here we have a vertex lying on line.
								// additional checks whether line intersects the poly, or just touching it.

								if		( atPolyLineBeg )					// intersecting point on poly line start point.
								{
									// check if the two polys intersect at the vertex lying on line (segment) or they are just touching.
									// Note that:
									// - the vertex which lies on the line (segment) is given by 'i' and it is a correct index in 'poly'.
									// - the line (segment) on which the vertex lies is given by '( j - 1 )' and it is a correct index in 'this poly'.
									isTouching				= ( ! poly.IsPolyIntersectingPolyAt( i, *this, ( j - 1 ), epsilon ) );

									isDecided				= true;			// estimation is made.
								}
								else if	( atThisLineBeg )					// intersecting point on this line start point.
								{
									// check if the two polys intersect at the vertex lying on line (segment) or they are just touching.
									// Note that:
									// - the vertex which lies on the line (segment) is given by '( j - 1 )' and it is a correct index in 'this poly'.
									// - the line (segment) on which the vertex lies is given by 'i' and it is a correct index in 'poly'.
									isTouching				= ( ! this->IsPolyIntersectingPolyAt( ( j - 1 ), poly, i , epsilon ) );

									isDecided				= true;			// estimation is made.
								}
								else if ( atThisLineEnd )					// intersecting point on this line end point.
								{
									if ( j == len )			// touch is at the last vertex in 'this poly'.
									{
										// note:
										// special case - touch is at the last vertex (no more checks to do against the 'poly' segment).
										isTouching			= true;

										isDecided			= true;			// estimation is made.
									}
									else
									{
										// collect the suspect touch as it might not be caught at the next step due to imperfect epsilon check.
										hasSuspectToPoly	= true;
									}
								}
								else if ( atPolyLineEnd )					// intersecting point on poly line end point.
								{
									if ( i == polyLen - 1 )
									{
										// note:
										// special case - touch is at the last vertex (no more checks to do against 'this poly' segment).
										isTouching			= true;

										isDecided			= true;			// estimation is made.
									}
									else
									{
										// collect the suspect touch as it might not be caught at the next step due to imperfect epsilon check.
										hasSuspectToThis	= true;

										suspectPtToThis		= intersPt;
									}
								}
							}

							// collect the intersection point.

							if ( isDecided )								// estimation is made.
							{
								if ( isTouching )							// local touching.
								{
									// add to the array of touches.
									outArrTouchPts.push_back( intersPt );
								}
								else										// local intersection.
								{
									// add to the array of intersections.
									outArrIntersPts.push_back( intersPt );
								}

								// update: if there is clear intersection between polys (generally).
								hasClearInters				= ( hasClearInters || ! isTouching );
							}
						}
						else if ( onSegments )
						{
							// if we are here, this means that we have parallel and touching lines (i.e. coincident).
							hasIntersOrTouch				= true;

							// add to the array of touches.
							outArrTouchPts.push_back( intersPt );
						}
						else if ( parallel )
						{
							// if we are here, this means that we have parallel lines. check if they have common points.

							// get projection of 'p' on the straight line defined by 'line'.
							VWPoint2D	projPt				= line.PtPerpLine( p );

							// check if 'p' is on the straight line 'line'.
							if ( MathUtils::Equalish( p.DistanceTo( projPt ), 0.0, epsilon ) )
							{
								// we are here when both lines lie on same straight line.
								// so they might have common points.

								bool	isTouching			= false;
								if		( line.PtOnLine( p, epsilon ) )
								{
									isTouching				= true;
									atThisLineBeg			= true;
									intersPt				= p;
								}
								else if	( line.PtOnLine( q, epsilon ) )
								{
									isTouching				= true;
									intersPt				= q;
								}
								else if	( curLine.PtOnLine( line.GetStart(), epsilon ) )
								{
									isTouching				= true;
									atPolyLineBeg			= true;
									intersPt				= line.GetStart();
								}
								// Note: the above 3 checks are sufficient (we don't need to check if 'line.GetEnd()' lies on curLine).

								if ( isTouching )
								{
									hasIntersOrTouch		= true;

									// add to the array of touches.
									outArrTouchPts.push_back( intersPt );
								}
							}
						}

						// update (if there is found intersecting point at the 'poly' line start point).
						hasAtPolyLineBeg					= ( hasAtPolyLineBeg || atPolyLineBeg );

						// XXX Bobi:
						// check for a special case: there is a suspect (sleepy) touch caught at previous step but ...
						// ... not caught at this step due to imperfect epsilon check.

						if ( hasSleepyToPoly &&				// has 'sleep touch' to 'poly' (from the previous segment) and ...
							 ( ! atThisLineBeg ) )			// ... intersecting point is not on this line start point (from this segment).
						{
							// so accept that the 'sleep point" is a touch (as we don't have more information in this case).
							outArrTouchPts.push_back( sleepPtToPoly );
						}

						// update/store the suspicion.
						hasSleepyToPoly						= hasSuspectToPoly;
						if ( hasSleepyToPoly )				sleepPtToPoly	= intersPt;

						p									= q;	// prepare for next segment.

					} // end of loop ('this poly' segments).

					// XXX Bobi:
					// check for a special case: there is a suspect (sleepy) touch caught at previous step but ...
					// ... not caught at this step due to imperfect epsilon check.

					if ( hasSleepyToThis &&					// has 'sleep touch' to 'this poly' (from the previous segment) and ...
						( ! hasAtPolyLineBeg ) )			// ... intersecting point is not on poly line start point (from this segment).
					{
						// so accept that the 'sleep point" is a touch (as we don't have more information in this case).
						outArrTouchPts.push_back( sleepPtToThis );
					}

					// update/store the suspicion.
					hasSleepyToThis							= hasSuspectToThis;
					if ( hasSleepyToThis )					sleepPtToThis	= suspectPtToThis;
				}
			}
		} // end of loop ('poly' segments).
	}

	// check if polys just touch (not clear intersection).
	outIsTouching			= ( hasIntersOrTouch && ! hasClearInters );

	// result.
	return	( hasIntersOrTouch );
}

// return true if the specified line intersects the poly.
// NOTE: The function returns intersection lines, not points.
// 1. If start and end points of the line are equal, this line represent one intersection point.
// 2. If start and end points of the line are NOT equal, this line overlaps some edge of the poly.
bool VWPolygon2D::IsIntersecting(const VWLine2D& line, double epsilon, TSTLLines2DArray& outIntersectLines) const
{
	// init.
	outIntersectLines.clear();

	const size_t	vertsCnt	= farrVertices.size();

	// validate.
	VWFC_ASSERT( vertsCnt > 1 );// empty polygon (see the 'IsEmpty' function). check !

	if ( vertsCnt > 1 )			// non-empty polygon.
	{
		// get line and poly bounds.
		const VWRectangle2D&	polyBbox	= this->GetPolygonBounds();
		const VWRectangle2D&	lineBbox	= line.GetLineBounds();

		if ( ! polyBbox.IsOutside( lineBbox ) )	// bounding boxes have common area.
		{
			size_t	polyLen		= vertsCnt;

			// Note: do not check the last segment if the poly is open.
			if ( ! fbIsClosed )
			{
				-- polyLen;
			}

			const VWPoint2D&	a		= line.GetStart();
			const VWPoint2D&	b		= line.GetEnd();

			VWPoint2D			p		= farrVertices[ 0 ].pt;

			// Note: main loop. the points p and q are forming the line segments from the poly.
			for ( size_t i = 1 ; i <= polyLen ; ++ i )
			{
				VWPoint2D		q;
				if ( i == vertsCnt )	
				{
					q			= farrVertices[ 0 ].pt;
				}
				else
				{
					q			= farrVertices[ i ].pt;
				}

				VWLine2D		intersectLine;
				bool			parallel, onSeg1, onSeg2;

				// checks if line (a,b) intersects with line (p,q), returns intersection line/point.
				// even if lines are parallel, it checks for overlapping between them considered as intersection.
				VWLine2D::IntersectLines( a, b, p, q, intersectLine, parallel, onSeg1, onSeg2, epsilon, VWPoint2D::sEpsilonCollinear );

				if ( onSeg1 && onSeg2 )	// intersection found.
				{
					const VWPoint2D&	start	= intersectLine.GetStart();
					const VWPoint2D&	end		= intersectLine.GetEnd();

					// Note: Traverse the intersection lines. Ensure the new intersecLine does NOT attend in the vector.
					bool		isFound	= false;
					for ( const auto& it : outIntersectLines )
					{
						if ( MathUtils::Equalish( start, it.GetStart(), epsilon ) &&
							 MathUtils::Equalish( end, it.GetEnd(), epsilon ) )
						{
							isFound		= true;
							break;
						}
					}

					if ( ! isFound )
					{
						outIntersectLines.push_back( intersectLine );
					}
				}

				p		= q;
			}
		}
	}

	return outIntersectLines.size() > 0;
}

// checks whether the line segment (specified by its ending points 'lnPt0' and 'lnPt1') intersects the polygon.
// note 1: it doesn't calculate the intersection point (for faster checking).
// note 2: requires polygonized poly (corner vertices only).
bool VWPolygon2D::IsIntersectingLine(const VWPoint2D& lnPt0, const VWPoint2D& lnPt1, double epsilon) const
{
	// init.
	bool			isIntersecting	= false;

	size_t			vertsCnt		= farrVertices.size();

	if ( vertsCnt > 1 )				// non-empty polygon.
	{
		size_t		lastInx			= ( vertsCnt - 1 );

		size_t		procCnt			= vertsCnt;

		// don't check the last segment if this is open polygon.
		if ( ! fbIsClosed )
		{
			-- procCnt;
		}

		// get the line bounding box.
		VWRectangle2D				bboxLine(	lnPt0.x, lnPt1.x,		// left / right.
												lnPt0.y, lnPt1.y );		// top / bottom.

		// note:
		// we can't rely on the calculated polygon bounds while it is being edited (locked for edit, 'fLockedForEdit').
		// therefore, do check for common area between polygon's and line's bounding boxes (filter by overlap) ...
		// ... only when the polygon is not locked for edit.

		// not expected the polygon to be locked for edit.
		VWFC_ASSERT( ! fLockedForEdit );

		// filter by overlap between bounding boxes of the polygon and the line.
		if ( fLockedForEdit ||
			 ( ! VWRectangle2D( fdMinX, fdMaxX, fdMaxY, fdMinY ).IsOutside( bboxLine, epsilon ) ) )
		{
			for ( size_t i = 0 ; i < procCnt ; ++ i )
			{
				const VWPoint2D&	segPt0		= farrVertices[ i ].pt;

				size_t	nxtInx		= ( i < lastInx ? i + 1 : 0 );
				const VWPoint2D&	segPt1		= farrVertices[ nxtInx ].pt;

				// get the line bounding box.
				VWRectangle2D		bboxSeg(	segPt0.x, segPt1.x,		// left / right.
												segPt0.y, segPt1.y );	// top / bottom.

				if ( ! bboxLine.IsOutside( bboxSeg ) )					// bounding boxes have common area.
				{
					// unambiguous intersection check:
					// check if line intersects polygon segment. note: the function doesn't calculate the intersection point (for faster checking).
					if ( VWLine2D::AreLineSegmentsIntersecting( lnPt0, lnPt1, segPt0, segPt1, epsilon ) )
					{
						isIntersecting			= true;

						break;		// intersection found - stop.
					}
				}
			}
		}
	}

	// result.
	return	( isIntersecting );
}

// return true if part of a polygon is inside a vicinity of this polygon.
bool VWPolygon2D::IsInVicinity(const VWPolygon2D& poly, double dVicinity) const
{
	bool		inVicinity			= false;

	// check closeness of the given poly's points to this polygon.
	size_t		polyLen				= poly.GetVertexCount();
	for ( size_t i = 0 ; i < polyLen ; ++ i ) {
		const VWPoint2D&	pt		= poly.GetVertexAt( i );

		if ( this->IsPtOnPoly2D( pt, dVicinity ) ) {
			inVicinity				= true;
			break;
		}
	}

	// check closeness of this polygon's points to the given poly.
	if ( ! inVicinity ) {

		polyLen						= this->GetVertexCount();
		for ( size_t i = 0 ; i < polyLen ; ++ i ) {
			const VWPoint2D&	pt	= this->GetVertexAt( i );

			if ( poly.IsPtOnPoly2D( pt, dVicinity ) ) {
				inVicinity			= true;
				break;
			}
		}
	}

	// check for intersections.
	if ( ( ! inVicinity ) && this->IsIntersecting( poly, dVicinity ) ) {	// if intersecting then it is inside vicinity.
		inVicinity					= true;
	}

	return	inVicinity;
}

// returns true if the given polygon is fully within this polygon
bool VWPolygon2D::IsFullyInside(const VWPolygon2D& poly, double dEpsilon) const
{
	bool	bIsFullyInside	= false;
	bool	bInters			= this->IsIntersecting( poly, dEpsilon );
	if ( bInters ) {
		bIsFullyInside	= false;
	}
	else {
		bIsFullyInside			= true;

		size_t		polyLen		= poly.farrVertices.size();
		for(size_t i=0; i<polyLen; i++)
		{
			VWPoint2D		pt		= poly.farrVertices[ i ].pt;
			bool			onPoly	= false;
			bool			inPoly	= false;
			this->IsPtOnPoly2D( pt, onPoly, inPoly, dEpsilon );

			if ( ! onPoly && ! inPoly ) {
				bIsFullyInside	= false;
				break;	// STOP!
			}
		}
	}

	return bIsFullyInside;
}

// returns true if the given polygon is fully outside this polygon
bool VWPolygon2D::IsFullyOutside(const VWPolygon2D& poly, double dEpsilon) const
{
	bool	bIsFullyOutside	= false;
	bool	bInters			= this->IsIntersecting( poly, dEpsilon );
	if ( bInters ) {
		bIsFullyOutside	= false;
	}
	else {
		bIsFullyOutside			= true;

		size_t		polyLen		= poly.farrVertices.size();
		for(size_t i=0; i<polyLen; i++) {
			VWPoint2D		pt		= poly.farrVertices[ i ].pt;
			bool			onPoly	= false;
			bool			inPoly	= false;
			this->IsPtOnPoly2D( pt, onPoly, inPoly, dEpsilon );

			if ( onPoly || inPoly ) {
				bIsFullyOutside	= false;
				break;	// STOP!
			}
		}
	}

	return bIsFullyOutside;
}


// returns true if the given polygon is fully within this polygon, including having common points
bool VWPolygon2D::IsInside(const VWPolygon2D& poly, double dEpsilon) const
{
	bool	bIsInside			= true;

	size_t		polyLen		= poly.farrVertices.size();
	for(size_t i=0; i<polyLen; i++)
	{
		VWPoint2D		pt		= poly.farrVertices[ i ].pt;
		bool			onPoly	= false;
		bool			inPoly	= false;
		this->IsPtOnPoly2D( pt, onPoly, inPoly, dEpsilon );

		if ( ! onPoly && ! inPoly ) {
			bIsInside	= false;
			break;	// STOP!
		}
	}

	return bIsInside;
}

// returns true if the given polygon is fully within this polygon, including having common points (using tolerance). faster.
bool VWPolygon2D::IsWithin(const VWPolygon2D& poly, double tolerance) const
{
	// init.
	bool		isInside	= true;

	size_t		polyLen		= poly.farrVertices.size();
	for ( size_t i = 0 ; i < polyLen ; ++ i )
	{
		const VWPoint2D&	pt		= poly.farrVertices[ i ].pt;

		Sint32				onSegIndex;
		VWPoint2D			closestPtOnPoly;
		if ( ! this->IsPtWithinOrNearPoly2D( pt, onSegIndex, closestPtOnPoly, tolerance ) )
		{
			isInside		= false;
			break;			// stop.
		}
	}

	// result.
	return	( isInside );
}

// returns true if the given polygon is fully outside this polygon, including having common points
bool VWPolygon2D::IsOutside(const VWPolygon2D& poly, double dEpsilon) const
{
	bool bIsOutside			= true;

	size_t		polyLen		= poly.farrVertices.size();
	for(size_t i=0; i<polyLen; i++) {
		VWPoint2D		pt		= poly.farrVertices[ i ].pt;
		bool			onPoly	= false;
		bool			inPoly	= false;
		this->IsPtOnPoly2D( pt, onPoly, inPoly, dEpsilon );

		// xxx Yordan 04/2015: to include having common points, we shouldn't check whether current point is onPoly
		if ( /*onPoly ||*/ inPoly ) {
			bIsOutside	= false;
			break;	// STOP!
		}
	}

	return bIsOutside;
}

// get geometry center of the polygon
VWPoint2D VWPolygon2D::GetCenter() const
{
	VWPoint2D	centerPt;

	size_t		polyLen		= farrVertices.size();
	for(size_t i=0; i<polyLen; i++) {
		const VWPoint2D&	pt		= farrVertices[ i ].pt;
		if ( i == 0 )
			centerPt		= pt;
		else
			centerPt		+= pt;
	}

	centerPt	/= (double)polyLen;

	return centerPt;
}

// get mass center (centroid) of the polygon.
VWPoint2D VWPolygon2D::GetMassCenter() const
{
	size_t					polyLen		= farrVertices.size();

	double					sumX		= 0.0;
	double					sumY		= 0.0;
	double					singedArea	= 0.0;

	for ( size_t i = 0 ; i < polyLen ; ++ i )
	{
		const VWPoint2D&	p0			= farrVertices[ i ].pt;

		// get next index.
		size_t				next		= ( i + 1 );
		if ( next == polyLen )	next	= 0;

		const VWPoint2D&	p1			= farrVertices[ next ].pt;

		double				area		= ( ( p0.x * p1.y ) - ( p1.x * p0.y ) );

		sumX							+= ( ( p0.x + p1.x ) * area );
		sumY							+= ( ( p0.y + p1.y ) * area );
		singedArea						+= area;
	}

	VWPoint2D				massCenterPt;
	if ( ! MathUtils::Equalish( singedArea, 0.0, VWPoint2D::sEpsilon ) )
	{
		singedArea						*= 3.0;
		massCenterPt.SetPoint( ( sumX / singedArea ), ( sumY / singedArea ) );
	}
	else
	{
		massCenterPt.SetPoint( sumX, sumY );
		VWFC_ASSERT( false );			// check !
	}

	// result.
	return	( massCenterPt );
}

// get an inside point: prefer points that are not too close to the polygon boundary.
bool VWPolygon2D::GetPtInsidePoly(VWPoint2D& insidePt, double dEpsilon) const
{
	bool			isInside	= false;

	// get first 3 'apposite' polygon points - not too close and not collinear.
	VWPoint2D		pt0, pt1, pt2;
	if ( this->GetThreeAppositePoints( pt0, pt1, pt2 ) )
	{
		isInside				= true;

		// get the median direction.
		VWPoint2D	midDir		= ( ( pt0 - pt1 ) + ( pt2 - pt1 ) ).Normalize();
		// correct direction.
		if ( this->IsPtInPoly2D( ( pt1 - ( midDir * VWPoint2D::sEpsilon ) ), 0.0 ) )
		{
			midDir				*= - 1.0;
		}
		else if ( ! this->IsPtInPoly2D( ( pt1 + ( midDir * VWPoint2D::sEpsilon ) ), 0.0 ) )
		{
			isInside			= false;
			VWFC_ASSERT( false );	// a degenerate polygon!
		}

		if ( isInside )	// we have a correct direction.
		{
			// start from the distance: from pt1 to center of the triangle defined by the three points.
			double	dist		= pt1.DistanceTo( ( pt0 + pt2 + pt1 ) / 3 );

			do
			{
				insidePt		= ( pt1 + ( midDir * dist ) );
				isInside		= this->IsPtInPoly2D( insidePt, dEpsilon );

				// decrease the distance.
				dist			*= 0.5;
			}
			while ( ( ! isInside ) && ( dist > dEpsilon ) );
		}
	}

	// result.
	return	isInside;
}

// get random point that lies in the poly.
// XXX Bobi: not advisable to use:
// for polygon with small area it could take very long time to finish !
VWPoint2D VWPolygon2D::GetRandomPtInPoly(double dEpsilon) const
{
	VWPoint2D	pt;
	if ( MathUtils::Greaterish( Abs( this->GetArea() ), 0.0, ( this->GetPerimeter() * dEpsilon ) ) )
	{
		do
		{
			pt.x	= MathUtils::RealRandom( fdMinX, fdMaxX );
			pt.y	= MathUtils::RealRandom( fdMinY, fdMaxY );
		}
		while ( ! this->IsPtInPoly2D( pt, dEpsilon ) );
	}
	else
	{
		// this is a degenerate polygon (very small area).
		// return the center point in this case.
		pt			= this->GetCenter();
		VWFC_ASSERT( false );		// degenerate polygon.
	}

	return pt;
}

// get bounding points along line
// the result points are projection on the line of the two points from the poly wich are bound points along the line
void VWPolygon2D::GetBoundingProjOnLine(VWPoint2D&/*in-out*/ minProjPt, VWPoint2D&/*in-out*/ maxProjPt, double dEpsilon) const
{
	// not using epsilon -- but we should
	dEpsilon;

	VWLine2D			line( minProjPt, maxProjPt );
	
	// min and max distance from the begining of the line (face bearing line)
	double				minProjDist;
	double				maxProjDist;
	size_t				vertCnt	= farrVertices.size();
	for(size_t v=0; v<vertCnt; v++)
	{
		VWPoint2D	pt			= farrVertices[ v ].pt;
		VWPoint2D	projPt		= line.PtPerpLine( pt );
		//double		dist		= ( projPt - pt ).Magnitude();
		double		projDist	= ( projPt - line.GetStart() ).Magnitude();
		if ( v == 0 )
		{
			// first time - init
			minProjPt = maxProjPt			= projPt;
			minProjDist = maxProjDist		= projDist;
		}
		else
		{
			if ( projDist < minProjDist )
			{
				minProjPt		= projPt;
				minProjDist		= projDist;
			}
			if ( projDist > maxProjDist )
			{
				maxProjPt		= projPt;
				maxProjDist		= projDist;
			}
		}
	}
}

// get an inside point near the vertex at
VWPoint2D VWPolygon2D::GetInsidePtNearVertexAt(size_t at)
{
	VWFC_ASSERT( at < farrVertices.size() );

	const double	kNearPtEpsilon	= 1000 * VWPoint2D::sEpsilon;

	VWPoint2D	pt		= this->GetVertexAt( at );
	VWPoint2D	prevPt;
	if ( at < 1 )	prevPt	= this->GetVertexAt( this->GetVertexCount() - 1 );
	else			prevPt	= this->GetVertexAt( at - 1 );
	VWPoint2D		nextPt	= this->GetVertexAt( at + 1, true );

	VWLine2D	line( prevPt, nextPt );
	VWPoint2D	midDir	= line.CenterPt() - pt;
	if ( midDir.Magnitude() < VWPoint2D::sEpsilon ) {
		VWPoint2D	vec		= nextPt - pt;
		midDir.SetPoint( vec.y, -vec.x );
	}
	midDir.Normalize();

	VWPoint2D	checkPt	= pt + midDir * kNearPtEpsilon;
	if ( this->IsPtInPoly2D( checkPt, VWPoint2D::sEpsilon ) ) {
		return	checkPt;
	}
	else {
		checkPt	= pt - midDir * kNearPtEpsilon;
		VWFC_ASSERT( this->IsPtInPoly2D( checkPt, VWPoint2D::sEpsilon ) );
		return	checkPt;
	}
}

// get set of inside points near polygon's vertices
TSTLPoints2DArray VWPolygon2D::GetInsideNearPts()
{
	size_t	ptsCnt	= this->GetVertexCount();
	TSTLPoints2DArray	resultArray;
	for ( size_t i = 0 ; i < ptsCnt ; i ++ ) {
		resultArray.push_back( this->GetInsidePtNearVertexAt( i ) );
	}
	return	resultArray;
}

// ---------------------------------------------------------------------------------------------------------------------
// compares 'this' polygon against the given polygon. collects the parts of 'this' polygon that do not overlap with the given polygon.
// Note: both polygons ('this' and given) must be polygonized (must have only corner vertices).
void VWPolygon2D::GetDifferencesAgainstPolygon(const VWPolygon2D& polygon, TSTLPolygons2DArray& outDifferences, double epsilon) const
{
	bool		noOverlap;

	// compare.
	this->GetDifferencesAgainstPolygon( polygon, outDifferences, noOverlap, epsilon );
}

// ---------------------------------------------------------------------------------------------------------------------
// compares 'this' polygon against the given polygon. collects the parts of 'this' polygon that do not overlap with the given polygon.
// also, 'outNoOverlap' returns whether there is some overlapping (at all) or not between 'this' and the given polygon.
// Note: both polygons ('this' and given) must be polygonized (must have only corner vertices).
void VWPolygon2D::GetDifferencesAgainstPolygon(const VWPolygon2D& polygon, TSTLPolygons2DArray& outDifferences, bool& outNoOverlap, double epsilon) const
{
	typedef				std::vector<std::pair<double,size_t>>		TSqrDistAndInxArray;

	// init.
	outNoOverlap		= true;
	outDifferences.clear();

	size_t				thisCnt		= farrVertices.size();
	size_t				checkCnt	= polygon.GetVertexCount();

	// validate.
	VWFC_ASSERT( thisCnt > 1 && checkCnt > 1 );		// empty polygons (see the 'IsEmpty' function). check !

	if ( thisCnt > 1 && checkCnt > 1 )				// non-empty polygons.
	{
		// get the bounding box of 'this' polygon.
		const VWRectangle2D&		thisBbox		= this->GetPolygonBounds();
		const VWRectangle2D&		checkBbox		= polygon.GetPolygonBounds();

		if ( ! thisBbox.IsOutside( checkBbox, epsilon ) )			// bounding boxes have common area.
		{
			// get squared epsilon.
			double		sqrEps		= sqr( epsilon );

			size_t		thisLen		= thisCnt;

			// Note: do not check the last segment if 'this' polygon is open.
			if ( ! fbIsClosed )		// 'this' polygon is open.
			{
				-- thisLen;
			}

			size_t		checkLen	= checkCnt;

			// Note: do not check the last segment if 'check' polygon is open.
			if ( ! polygon.IsClosed() )				// 'check' polygon is open.
			{
				-- checkLen;
			}

			size_t		diffsCnt	= 0;

			bool		hasOpenDiff	= false;

			VWPoint2D	tSegBeg		= farrVertices[ 0 ].pt;

			// loop 'this' polygon. the points 'tSegBeg' and 'tSegEnd' are forming the line segments in 'this' polygon.
			for ( size_t i = 1 ; i <= thisLen ; ++ i )
			{
				// prepare the 'tSegEnd'.
				VWPoint2D			tSegEnd;
				if ( i == thisCnt )	
				{
					tSegEnd			= farrVertices[ 0 ].pt;
				}
				else
				{
					tSegEnd			= farrVertices[ i ].pt;
				}

				TSTLLines2DArray	validOverlaps;	// for the non-zero-length overlaps.
				TSqrDistAndInxArray	sqrDistsAndInxs;// for sorting the overlaps.

				VWPoint2D			cSegBeg			= polygon.GetVertexAt( 0 );

				// loop 'check' polygon. the points 'cSegBeg' and 'cSegEnd' are forming the line segments in 'check' polygon.
				for ( size_t j = 1 ; j <= checkLen ; ++ j )
				{
					// prepare the 'cSegEnd'.
					VWPoint2D		cSegEnd;
					if ( j == checkCnt )	
					{
						cSegEnd		= polygon.GetVertexAt( 0 );
					}
					else
					{
						cSegEnd		= polygon.GetVertexAt( j );
					}

					VWLine2D		intersectLine;
					bool			parallel, onSeg1, onSeg2;

					// check if line ('tSegBeg','tSegEnd') intersects with line ('cSegBeg','cSegEnd'), returns intersection line/point.
					// even if lines are parallel, it checks for overlapping between them considered as intersection.
					VWLine2D::IntersectLines(		tSegBeg, tSegEnd,				// segment from 'this' polygon.
													cSegBeg, cSegEnd,				// segment from 'check' polygon.
													intersectLine, parallel, onSeg1, onSeg2,
													epsilon,						// distance epsilon.
													VWPoint2D::sEpsilonCollinear );	// collinearity epsilon.

					if ( onSeg1 && onSeg2 )			// intersection found.
					{
						// check the result.
						VWPoint2D&	lp0				= intersectLine.GetStart();
						VWPoint2D&	lp1				= intersectLine.GetEnd();

						double		sqrLineLen		= lp0.DistanceSquaredTo( lp1 );

						// is it not a zero-length line?
						if ( sqrLineLen > sqrEps )	// not a zero-length line.
						{
							double	sqrDistLP0		= lp0.DistanceSquaredTo( tSegBeg );
							double	sqrDistLP1		= lp1.DistanceSquaredTo( tSegBeg );

							double	minSqrDist;

							// sort result towards 'this' segment's start point.
							if ( sqrDistLP0 > sqrDistLP1 )
							{
								minSqrDist			= sqrDistLP1;	// get minimum.

								// swap.
								Tools::SwapVariables( lp0, lp1 );
							}
							else
							{
								minSqrDist			= sqrDistLP0;	// get minimum.
							}

							// collect.
							validOverlaps.push_back( VWLine2D( lp0, lp1 ) );

							// collect auxiliary.
							sqrDistsAndInxs.push_back( std::make_pair( minSqrDist, ( validOverlaps.size() - 1 ) ) );
						}
					}

					// prepare for next segment.
					cSegBeg			= cSegEnd;
				}

				// overlaps are already collected.

				size_t	overlapsCnt	= validOverlaps.size();

				// examine the collected overlaps.
				if ( overlapsCnt > 0 )				// has overlaps.
				{
					if ( outNoOverlap )				// update the 'no overlap' flag.
					{
						outNoOverlap				= false;
					}

					// validate.
					VWFC_ASSERT( overlapsCnt == sqrDistsAndInxs.size() );	// something is wrong. check !

					// sort the auxiliary array. note: preferably sorts by 'first' (doubles - the squared distances).
					// so we will have the overlaps sorted according to their distance to the segment's start.
					std::sort( sqrDistsAndInxs.begin(), sqrDistsAndInxs.end() );

					diffsCnt		= outDifferences.size();

					VWPoint2D&		lastAdded		= tSegBeg;

					// look valid overlaps.
					for ( const auto& it : sqrDistsAndInxs )
					{
						size_t		overlapInx		= it.second;

						// validate.
						VWFC_ASSERT( overlapInx < overlapsCnt );	// not expected. check !

						// get the current 'overlap'.
						const VWLine2D&	overlap		= validOverlaps[ overlapInx ];

						// prepare a point to add (last for this 'difference').
						const VWPoint2D&			ptLast			= overlap.GetStart();

						// finish the previous 'difference'.
						// ---------------------------------

						if ( hasOpenDiff )			// has a non-ended 'difference'.
						{
							VWFC_ASSERT( diffsCnt > 0 );	// must not happen. check !

							// prevent from doubling of points.
							if ( ptLast.DistanceSquaredTo( lastAdded ) > sqrEps )
							{
								outDifferences[ diffsCnt - 1 ].AddVertex( ptLast );	// add.
							}
						}
						else		// doesn't have added.
						{
							// prepare a new polygon (will consist of single segment only).

							// prevent from doubling of points.
							if ( ptLast.DistanceSquaredTo( lastAdded ) > sqrEps )
							{
								VWPolygon2D				newDiffPoly;
								newDiffPoly.SetClosed( false );				// force open.

								newDiffPoly.fLockedForEdit	= true;

								newDiffPoly.AddVertex( lastAdded );			// add.
								newDiffPoly.AddVertex( ptLast );			// add.

								outDifferences.push_back( newDiffPoly );	// collect.

								++ diffsCnt;			// update count.
							}
						}

						// prepare a point to add (first for next 'difference').
						const VWPoint2D&			ptStart			= overlap.GetEnd();

						// start a new 'difference' (if possible).
						// ---------------------------------------

						// check if the end of segment is reached (... and prevent from doubling of points).
						if ( ptStart.DistanceSquaredTo( tSegEnd ) > sqrEps )
						{
							// prepare a new polygon.
							VWPolygon2D				newDiffPoly;
							newDiffPoly.SetClosed( false );			// force open.

							newDiffPoly.fLockedForEdit	= true;

							newDiffPoly.AddVertex( ptStart );		// add.

							outDifferences.push_back( newDiffPoly );// collect.

							++ diffsCnt;			// update count.

							lastAdded				= ptStart;		// update last.

							hasOpenDiff				= true;			// mark that there is a non-ended 'difference'.
						}
						else
						{
							hasOpenDiff				= false;		// mark that there is not a non-ended 'difference'.
						}
					}

					// add the segment's end point (if needed).
					if ( hasOpenDiff )				// has a non-ended 'difference'.
					{
						diffsCnt	= outDifferences.size();		// update count.

						// validate.
						VWFC_ASSERT( diffsCnt > 0 );				// must not happen. check !

						// add the segment's end to the last 'difference'.
						outDifferences[ diffsCnt - 1 ].AddVertex( tSegEnd );		// add.
					}
				}
				else				// no overlaps.
				{
					diffsCnt		= outDifferences.size();

					if ( hasOpenDiff )				// has a non-ended 'difference'.
					{
						// validate.
						VWFC_ASSERT( diffsCnt > 0 );				// must not happen. check !

						outDifferences[ diffsCnt - 1 ].AddVertex( tSegEnd );		// add.
					}
					else			// doesn't have a non-ended 'difference'.
					{
						// prepare a new polygon.
						VWPolygon2D	diffPoly;
						diffPoly.SetClosed( false );			// force open.

						diffPoly.fLockedForEdit		= true;

						// add the segment's ending points.
						diffPoly.AddVertex( tSegBeg );
						diffPoly.AddVertex( tSegEnd );

						outDifferences.push_back( diffPoly );	// collect.
					}

					hasOpenDiff		= true;			// mark that there is a non-ended 'difference'.
				}

				// prepare for next segment.
				tSegBeg				= tSegEnd;
			}

			diffsCnt	= outDifferences.size();

			// loop results backwards.
			for ( ptrdiff_t i = ( diffsCnt - 1 ) ; i >= 0 ; -- i )
			{
				VWPolygon2D&		diffPoly		= outDifferences[ i ];

				size_t	ptsCnt		= diffPoly.GetVertexCount();

				// validate.
				VWFC_ASSERT( ptsCnt > 1 );			// not expected. check !

				bool	notCorrect	= false;

				if ( ptsCnt == 1 )	// degenerate single-point difference.
				{
					notCorrect		= true;
				}
				// check for zero-length 'difference'.
				// Note: such could be collected if there are zero-length polygons' segments.
				else if ( ptsCnt == 2 )
				{
					const VWPoint2D&	pt0			= diffPoly.GetVertexAt( 0 );
					const VWPoint2D&	pt1			= diffPoly.GetVertexAt( 1 );

					if ( pt0.DistanceSquaredTo( pt1 ) < sqrEps )
					{
						notCorrect	= true;
					}
				}

				if ( notCorrect )	// not correct/degenerate difference.
				{
					// remove the difference.
					outDifferences.erase( outDifferences.begin() + i );
					continue;		// go to next (backwards).
				}

				// it is not a zero-length 'difference'.
				// recalculate bounds.
				diffPoly.fLockedForEdit				= false;
				diffPoly.RecalculateBoundingBox();
			}
		}
	}
}

void VWPolygon2D::GetOverlapAgainstPolygon(const VWPolygon2D& polygon, TSTLPolygons2DArray& outOverlaps, double epsilon) const
{
	typedef std::vector<std::pair<double,size_t>> TSqrDistAndInxArray;

	outOverlaps.clear();

	size_t	thisCnt		= farrVertices.size();
	size_t	checkCnt	= polygon.GetVertexCount();

	// validate.
	VWFC_ASSERT( thisCnt > 1 && checkCnt > 1 );		// empty polygons (see the 'IsEmpty' function). check !

	if ( thisCnt > 1 && checkCnt > 1 )				// non-empty polygons.
	{
		// get the bounding box of 'this' polygon.
		const VWRectangle2D&	thisBbox	= this->GetPolygonBounds();
		const VWRectangle2D&	checkBbox	= polygon.GetPolygonBounds();

		if ( !thisBbox.IsOutside( checkBbox, epsilon ) )			// bounding boxes have common area.
		{
			// get squared epsilon.
			double		sqrEps			= sqr( epsilon );

			size_t		thisLen			= thisCnt;

			// Note: do not check the last segment if 'this' polygon is open.
			if ( !fbIsClosed )		// 'this' polygon is open.
			{
				--thisLen;
			}

			size_t		checkLen		= checkCnt;

			// Note: do not check the last segment if 'check' polygon is open.
			if ( !polygon.IsClosed() )				// 'check' polygon is open.
			{
				--checkLen;
			}

			VWPoint2D	tSegBeg			= farrVertices[0].pt;

			size_t		overlapsCnt		= 0;

			bool		hasOpenOverlap	= false;
			VWPoint2D	lastAddedPt;

			// loop 'this' polygon. the points 'tSegBeg' and 'tSegEnd' are forming the line segments in 'this' polygon.
			for ( size_t i = 1; i <= thisLen; ++i )
			{
				// prepare the 'tSegEnd'.
				VWPoint2D			tSegEnd;
				if ( i == thisCnt )	
				{
					tSegEnd	= farrVertices[0].pt;
				}
				else
				{
					tSegEnd	= farrVertices[i].pt;
				}

				TSTLLines2DArray	validOverlaps;	// for the non-zero-length overlaps.
				TSqrDistAndInxArray	sqrDistsAndInxs;// for sorting the overlaps.

				VWPoint2D			cSegBeg	= polygon.GetVertexAt( 0 );

				// loop 'check' polygon. the points 'cSegBeg' and 'cSegEnd' are forming the line segments in 'check' polygon.
				for ( size_t j = 1; j <= checkLen; ++j )
				{
					// prepare the 'cSegEnd'.
					VWPoint2D	cSegEnd;
					if ( j == checkCnt )	
					{
						cSegEnd	= polygon.GetVertexAt( 0 );
					}
					else
					{
						cSegEnd	= polygon.GetVertexAt( j );
					}

					VWLine2D	intersectLine;
					bool		parallel, onSeg1, onSeg2;

					// check if line ('tSegBeg','tSegEnd') intersects with line ('cSegBeg','cSegEnd'), returns intersection line/point.
					// even if lines are parallel, it checks for overlapping between them considered as intersection.
					VWLine2D::IntersectLines(		tSegBeg, tSegEnd,				// segment from 'this' polygon.
													cSegBeg, cSegEnd,				// segment from 'check' polygon.
													intersectLine, parallel, onSeg1, onSeg2,
													epsilon,						// distance epsilon.
													VWPoint2D::sEpsilonCollinear );	// collinearity epsilon.

					if ( onSeg1 && onSeg2 )			// intersection found.
					{
						// check the result.
						VWPoint2D&	lp0			= intersectLine.GetStart();
						VWPoint2D&	lp1			= intersectLine.GetEnd();

						double		sqrLineLen	= lp0.DistanceSquaredTo( lp1 );

						// is it not a zero-length line?
						if ( sqrLineLen > sqrEps )	// not a zero-length line.
						{
							double	sqrDistLP0	= lp0.DistanceSquaredTo( tSegBeg );
							double	sqrDistLP1	= lp1.DistanceSquaredTo( tSegBeg );

							double	minSqrDist;

							// sort result towards 'this' segment's start point.
							if ( sqrDistLP0 > sqrDistLP1 )
							{
								minSqrDist	= sqrDistLP1;	// get minimum.

								// swap.
								Tools::SwapVariables( lp0, lp1 );
							}
							else
							{
								minSqrDist	= sqrDistLP0;	// get minimum.
							}

							// collect.
							validOverlaps.push_back( VWLine2D( lp0, lp1 ) );

							// collect auxiliary.
							sqrDistsAndInxs.push_back( std::make_pair( minSqrDist, ( validOverlaps.size() - 1 ) ) );
						}
					}

					// prepare for next segment.
					cSegBeg	= cSegEnd;
				}

				// overlaps are already collected.

				size_t	validOverlapsCnt	= validOverlaps.size();

				// examine the collected overlaps.
				if ( validOverlapsCnt > 0 )				// has overlaps.
				{
					// validate.
					VWFC_ASSERT( validOverlapsCnt == sqrDistsAndInxs.size() );	// something is wrong. check !

					// sort the auxiliary array. note: preferably sorts by 'first' (doubles - the squared distances).
					// so we will have the overlaps sorted according to their distance to the segment's start.
					std::sort( sqrDistsAndInxs.begin(), sqrDistsAndInxs.end() );

					bool	isFirstValidOverlap	= true;

					// look valid overlaps.
					for ( const auto& it : sqrDistsAndInxs )
					{
						size_t				overlapInx	= it.second;

						// validate.
						VWFC_ASSERT( overlapInx < validOverlapsCnt );	// not expected. check !

						// get the current 'overlap'.
						const VWLine2D&		overlap			= validOverlaps[ overlapInx ];

						// prepare a point to add (last for this 'difference').
						const VWPoint2D&	overlapStartPt	= overlap.GetStart();
						const VWPoint2D&	overlapEndPt	= overlap.GetEnd();

						// finish the previous 'difference'.
						// ---------------------------------

						if ( isFirstValidOverlap )
						{
							if ( hasOpenOverlap )
							{
								if ( tSegBeg.DistanceSquaredTo( overlapStartPt ) > sqrEps )
								{
									VWPolygon2D newOverlapPoly;
									newOverlapPoly.SetClosed( false );				// force open.

									newOverlapPoly.fLockedForEdit	= true;

									newOverlapPoly.AddVertex( overlapStartPt );		// add.
									newOverlapPoly.AddVertex( overlapEndPt );		// add.
									lastAddedPt						= overlapEndPt;

									outOverlaps.push_back( newOverlapPoly );		// collect.

									++overlapsCnt;									// update count.
								}
								else
								{
									outOverlaps[overlapsCnt - 1].AddVertex( overlapEndPt );	// add.
									lastAddedPt	= overlapEndPt;
								}
							}
							else
							{
								VWPolygon2D newOverlapPoly;
								newOverlapPoly.SetClosed( false );				// force open.

								newOverlapPoly.fLockedForEdit	= true;

								newOverlapPoly.AddVertex( overlapStartPt );		// add.
								newOverlapPoly.AddVertex( overlapEndPt );		// add.
								lastAddedPt						= overlapEndPt;

								outOverlaps.push_back( newOverlapPoly );		// collect.

								++overlapsCnt;									// update count.

								hasOpenOverlap					= true;
							}
						}
						else
						{
							if ( hasOpenOverlap )
							{
								double	sqrDistlastAddedtPt	= lastAddedPt.DistanceSquaredTo( tSegBeg );

								if ( it.first <= sqrDistlastAddedtPt )
								{
									outOverlaps[overlapsCnt - 1].AddVertex( overlapEndPt );	// add.
									lastAddedPt	= overlapEndPt;
								}
								else
								{
									VWPolygon2D newOverlapPoly;
									newOverlapPoly.SetClosed( false );				// force open.

									newOverlapPoly.fLockedForEdit	= true;

									newOverlapPoly.AddVertex( overlapStartPt );		// add.
									newOverlapPoly.AddVertex( overlapEndPt );		// add.
									lastAddedPt						= overlapEndPt;

									outOverlaps.push_back( newOverlapPoly );		// collect.

									++overlapsCnt;									// update count.
								}
							}
							else
							{
								VWPolygon2D newOverlapPoly;
								newOverlapPoly.SetClosed( false );				// force open.

								newOverlapPoly.fLockedForEdit	= true;

								newOverlapPoly.AddVertex( overlapStartPt );		// add.
								newOverlapPoly.AddVertex( overlapEndPt );		// add.
								lastAddedPt						= overlapEndPt;

								outOverlaps.push_back( newOverlapPoly );		// collect.

								++overlapsCnt;									// update count.

								hasOpenOverlap					= true;
							}
						}

						isFirstValidOverlap = false;
					}
				}
				else
				{
					hasOpenOverlap = false;
				}

				// prepare for next segment.
				tSegBeg	= tSegEnd;
			}

			overlapsCnt = outOverlaps.size();

			// loop results backwards.
			for ( ptrdiff_t i = ( overlapsCnt - 1 ); i >= 0; --i )
			{
				VWPolygon2D&	overlapPoly	= outOverlaps[ i ];

				size_t			ptsCnt		= overlapPoly.GetVertexCount();

				// validate.
				VWFC_ASSERT( ptsCnt > 1 );			// not expected. check !

				bool			notCorrect	= false;

				if ( ptsCnt == 1 )	// degenerate single-point difference.
				{
					notCorrect		= true;
				}
				// check for zero-length 'difference'.
				// Note: such could be collected if there are zero-length polygons' segments.
				else if ( ptsCnt == 2 )
				{
					const VWPoint2D&	pt0	= overlapPoly.GetVertexAt( 0 );
					const VWPoint2D&	pt1	= overlapPoly.GetVertexAt( 1 );

					if ( pt0.DistanceSquaredTo( pt1 ) < sqrEps )
					{
						notCorrect	= true;
					}
				}

				if ( notCorrect )	// not correct/degenerate difference.
				{
					// remove the difference.
					outOverlaps.erase( outOverlaps.begin() + i );
				}
				else
				{
					// it is not a zero-length 'difference'.
					// recalculate bounds.
					overlapPoly.fLockedForEdit	= false;
					overlapPoly.RecalculateBoundingBox();
				}
			}
		}
	}
}

void VWPolygon2D::PointsTransform(const VWTransformMatrix& matrix)
{
 	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++) {
		VWPoint2D&	pt		= farrVertices[i].pt;
		matrix.TransformPoint( pt );
	}

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

void VWPolygon2D::InversePointsTransform(const VWTransformMatrix& matrix)
{
 	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++) {
		VWPoint2D&	pt		= farrVertices[i].pt;
		pt					= matrix.InversePointTransform( pt );
	}

	if ( ! fLockedForEdit )
	{
		this->RecalculateBoundingBox();
	}
}

// is pt (x0,y0) is inside or/and on the specified triangle (x1,y1):(x2,y2):(x3,y3)
void VWPolygon2D::IsPtInTriangle( 	double x0, double y0,
									double x1, double y1,
									double x2, double y2,
									double x3, double y3,
									bool& outInTri, bool& outOnTri)
{
	VWPolygon2D::IsPtInTriangle( x0, y0, x1, y1, x2, y2, x3, y3, outInTri, outOnTri, VWPoint2D::sEpsilon );
}

void VWPolygon2D::IsPtInTriangle(	double x0, double y0,
									double x1, double y1,
									double x2, double y2,
									double x3, double y3,
									bool& outInTri, bool& outOnTri,
									double epsilon)
{
	// init.
	outInTri			=	false;
	outOnTri			=	false;

	double		negEps	= ( - epsilon );
	
	double		b0		=  (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);

#define EQ_ZERO(val)	( val > negEps && val < epsilon )
#define GR_ZERO(val)	MathUtils::Greaterish( val, 0.0, epsilon )

	if ( ! EQ_ZERO(b0) ) {	// triangle points are not collinear - this is a "good" triangle.
	
		double		b1	= ((x2 - x0) * (y3 - y0) - (x3 - x0) * (y2 - y0)) / b0;
		double		b2	= ((x3 - x0) * (y1 - y0) - (x1 - x0) * (y3 - y0)) / b0;
		double		b3	= ((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0)) / b0;

//		outInTri		= b1 > 0 && b2 > 0 && b3 > 0;
//		outOnTri		= (b1 == 0 && b2 > 0 && b3 > 0)		||
//						  (b1 > 0 && b2 == 0 && b3 > 0)		||
//						  (b1 > 0 && b2 > 0 && b3 == 0)		||
//						  // is on points
//						  (b1 > 0 && b2 == 0 && b3 == 0)	||
//						  (b1 == 0 && b2 > 0 && b3 == 0)	||
//						  (b1 == 0 && b2 == 0 && b3 > 0) ;

		outInTri		= GR_ZERO(b1) && GR_ZERO(b2) && GR_ZERO(b3);
		outOnTri		= ( EQ_ZERO(b1) && GR_ZERO(b2) && GR_ZERO(b3) )	||
						  ( GR_ZERO(b1) && EQ_ZERO(b2) && GR_ZERO(b3) )	||
						  ( GR_ZERO(b1) && GR_ZERO(b2) && EQ_ZERO(b3))	||
						  // is on points
						  ( GR_ZERO(b1) && EQ_ZERO(b2) && EQ_ZERO(b3) )	||
						  ( EQ_ZERO(b1) && GR_ZERO(b2) && EQ_ZERO(b3) )	||
						  ( EQ_ZERO(b1) && EQ_ZERO(b2) && GR_ZERO(b3) ) ;
	}
	else {	// if the three triangle points are close to collinear.
		
		// check if point is on the triangle's border.
		Sint32 onSegIndex	=	-1;
		Sint32 onPtIndex	=	-1;
		VWPolygon2D::IsPtOnTriangleBorder( x0, y0, x1, y1, x2, y2, x3, y3,
										   onSegIndex, onPtIndex, epsilon );
		outOnTri		=	( onSegIndex != -1 ) || ( onPtIndex != -1 );
	}

#undef EQ_ZERO
#undef GR_ZERO
}

// is pt (x0,y0) is inside or/and on the specified triangle (x1,y1):(x2,y2):(x3,y3)
// outOnSegIndex returns:
//	if (x0,y0) on [(x1,y1),(x2,y2] -> 0
//	if (x1,y1) on [(x2,y2),(x3,y3] -> 1
//	if (x2,y2) on [(x3,y3),(x1,y1] -> 2
// outOnPtIndex returns:
//	if (x0,y0) == (x1,y1) -> 0
//	if (x0,y0) == (x2,y2) -> 1
//	if (x0,y0) == (x3,y3) -> 2
void VWPolygon2D::IsPtInTriangle(	double x0, double y0,
									double x1, double y1,
									double x2, double y2,
									double x3, double y3,
									bool& outInTri,
									Sint32& outOnSegIndex,
									Sint32& outOnPtIndex,
									double epsilon)
{
	// init.
	outInTri		= false;
	outOnSegIndex	= -1;
	outOnPtIndex	= -1;

	//									|x1 y1 1|
	// compute the det(p1, p2, p3)	=	|x2 y2 1|
	//									|x3 y3 1|
	double			b0		=  (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);

	// check if the three (triangle) points are close to collinear.
	if ( b0 > epsilon || b0 < -epsilon )	// triangle points are not collinear - this is a "good" triangle.
	{
		double		x1mx0	= (x1 - x0);
		double		x2mx0	= (x2 - x0);
		double		x3mx0	= (x3 - x0);

		double		y1my0	= (y1 - y0);
		double		y2my0	= (y2 - y0);
		double		y3my0	= (y3 - y0);

		// get det(p0, p2, p3), det(p0, p1, p3) and det(p0, p1, p2).
		double		b1		= ( ( x2mx0 * y3my0 ) - ( x3mx0 * y2my0 ) );
		double		b2		= ( ( x3mx0 * y1my0 ) - ( x1mx0 * y3my0 ) );
		double		b3		= ( ( x1mx0 * y2my0 ) - ( x2mx0 * y1my0 ) );

		// use a corrected 'epsilon' so we won't need to find the actual ...
		// ... barycentric coordinates of p0 by dividing by 'b0'.
		double		eps		= ( epsilon * b0 );

		if ( b0 < 0 )		// negative determinant.
		{
			eps		= -eps;
			b1		= -b1;
			b2		= -b2;
			b3		= -b3;
		}

		double		negEps	= -eps;

		// check the point position to the triangle.

		if ( b1 > negEps && b2 > negEps && b3 > negEps )	// minimum condition.
		{
			if ( b1 > eps )
			{
				if ( b2 < eps )
				{
					if ( b3 > eps )
					{
						outOnSegIndex	= 2;
					}
					else // if ( b3 <= eps )
					{
						outOnPtIndex	= 0;
					}
				}
				else // if ( b2 >= eps )
				{
					if ( b3 > eps )
					{
						outInTri		= true;
					}
					else // if ( b3 <= eps )
					{
						outOnSegIndex	= 0;
					}
				}
			}
			else // if ( b1 <= eps )
			{
				if ( b2 < eps )
				{
					VWFC_ASSERT( b3 > eps );	// not expected. collinear points.

					outOnPtIndex		= 2;
				}
				else // if ( b2 >= eps )
				{
					if ( b3 < eps )
					{
						outOnPtIndex	= 1;
					}
					else // if ( b3 >= eps )
					{
						outOnSegIndex	= 1;
					}
				}
			}
		}
	}
	else	// if the three triangle points are close to collinear.
	{
		// check if point is on the triangle's border.
		VWPolygon2D::IsPtOnTriangleBorder( x0, y0, x1, y1, x2, y2, x3, y3,
										   outOnSegIndex, outOnPtIndex, epsilon );
	}
}

// is pt (x0,y0) on the border of the specified triangle (x1,y1):(x2,y2):(x3,y3)
// works in all cases (including triangle with 3 vertices close to collinear).
// outOnSegIndex returns:
//	if (x0,y0) on [(x1,y1),(x2,y2)] -> 0
//	if (x1,y1) on [(x2,y2),(x3,y3)] -> 1
//	if (x2,y2) on [(x3,y3),(x1,y1)] -> 2
// outOnPtIndex returns:
//	if (x0,y0) == (x1,y1) -> 0
//	if (x0,y0) == (x2,y2) -> 1
//	if (x0,y0) == (x3,y3) -> 2
void VWPolygon2D::IsPtOnTriangleBorder(	double x0, double y0,
										double x1, double y1,
										double x2, double y2,
										double x3, double y3,
										Sint32& outOnSegIndex,
										Sint32& outOnPtIndex,
										double epsilon)
{
	outOnSegIndex	= -1;
	outOnPtIndex	= -1;

	double		negEps	= ( - epsilon );

#ifndef	EQ_ZERO
#define	EQ_ZERO(val)		( val > negEps && val < epsilon )
#endif
#define	BETWN(val, a, b)	MathUtils::IsBetween( val, a, b, epsilon )

	double		x1mx0	= (x1 - x0);
	double		x2mx0	= (x2 - x0);
	double		x3mx0	= (x3 - x0);

	double		y1my0	= (y1 - y0);
	double		y2my0	= (y2 - y0);
	double		y3my0	= (y3 - y0);
	
	// -------------------------------------------------------------------------------------
	//							|x0 y0 1|
	// get det(p0, p2, p3)	=	|x2 y2 1|, det(p0, p1, p3) and det(p0, p1, p2) (analogously).
	//							|x3 y3 1|
	// -------------------------------------------------------------------------------------
	double		b1		= ( ( x2mx0 * y3my0 ) - ( x3mx0 * y2my0 ) );
	double		b2		= ( ( x3mx0 * y1my0 ) - ( x1mx0 * y3my0 ) );
	double		b3		= ( ( x1mx0 * y2my0 ) - ( x2mx0 * y1my0 ) );

	// if the three triangle points are close to collinear.

	if ( BETWN(x0, x1, x2) && BETWN(y0, y1, y2) && EQ_ZERO(b3) )		// pt on triangle's segment 0.
	{
		if 		( EQ_ZERO( x1mx0 ) && EQ_ZERO( y1my0 ) )				// coincides with p1.
		{
			outOnPtIndex	=	0;
		}
		else if ( EQ_ZERO( x2mx0 ) && EQ_ZERO( y2my0 ) )				// coincides with p2.
		{
			outOnPtIndex	=	1;
		}
		else
		{
			outOnSegIndex	=	0;
		}
	}
	else if ( BETWN(x0, x2, x3) && BETWN(y0, y2, y3) && EQ_ZERO(b1) )	// pt on triangle's segment 1.
	{
		if 		( EQ_ZERO( x2mx0 ) && EQ_ZERO( y2my0 ) )				// coincides with p2.
		{
			outOnPtIndex	=	1;
		}
		else if ( EQ_ZERO( x3mx0 ) && EQ_ZERO( y3my0 ) )				// coincides with p3.
		{
			outOnPtIndex	=	2;
		}
		else
		{
			outOnSegIndex	=	1;
		}
	}
	else if ( BETWN(x0, x1, x3) && BETWN(y0, y1, y3) && EQ_ZERO(b2) )	// pt on triangle's segment 2.
	{
		if 		( EQ_ZERO( x1mx0 ) && EQ_ZERO( y1my0 ) )				// coincides with p1.
		{
			outOnPtIndex	=	0;
		}
		else if ( EQ_ZERO( x3mx0 ) && EQ_ZERO( y3my0 ) )				// coincides with p3.
		{
			outOnPtIndex	=	2;
		}
		else
		{
			outOnSegIndex	=	2;
		}
	}

#ifdef	EQ_ZERO
#undef	EQ_ZERO
#endif
#undef BETWN
}

// faster check if two polygons intersect each other. NOTE: no epsilon is used.
// before checking for actual intersections, this function checks if bounding boxes have common area.
// NOTE: if returned 'outNoCommonArea' is true, then polygons don't have common area for sure, otherwise ...
// ... if 'outNoCommonArea' is false then polygons probably have common area, but this still has to be checked.
bool VWPolygon2D::ArePolygonsIntersecting_Fast(const VWPolygon2D& polyA, const VWPolygon2D& polyB, bool& outNoCommonArea)
{
	// XXX Bobi:
	// use a very small epsilon (1e-16) when checking if two lines are intersecting (see the call of AreLineSegmentsIntersecting below).
	// this epsilon will catch the case when a lines are "touching" each other:
	// i.e. at least one of the end points of a line lie exactly on the other line or match its end points.
	const double		kIntersSegsEpsilon	= 0.000000000000001;	// 1e-16.

	// init.
	bool				areIntersecting		= false;
	outNoCommonArea							= true;

	// validate.
	if ( polyA.IsEmpty() || polyB.IsEmpty() )
	{
		ASSERTN( kVStanev, false );	// bad input !
		return	false;
	}

	const VWRectangle2D&		bboxA		= polyA.GetPolygonBounds();
	const VWRectangle2D&		bboxB		= polyB.GetPolygonBounds();

	// first: check if bounding boxes of the two polygons do not have common area, in such case they do not overlap.
	if ( ! bboxA.IsOutside( bboxB ) )							// bounding boxes have common area.
	{
		size_t					vertCntA	= polyA.GetVertexCount();
		size_t					cntA		= ( polyA.IsClosed() ) ? vertCntA : ( vertCntA - 1 );

		size_t					vertCntB	= polyB.GetVertexCount();
		size_t					cntB		= ( polyB.IsClosed() ) ? vertCntB : ( vertCntB - 1 );

		// next: check for intersection between the two polygons.
		for ( size_t i = 0 ; i < cntA ; ++ i )
		{
			const VWPoint2D&		v1		= polyA.GetVertexAt( i );

			size_t					iNext	= ( i + 1 );
			iNext							= ( iNext < vertCntA ) ? iNext : 0;
			const VWPoint2D&		v2		= polyA.GetVertexAt( iNext );

			VWRectangle2D			bboxLineA( v1.x, v2.x, v1.y, v2.y );		// get line bounding box.

			// check if line's bounding box has common area with the bounding box of the other poly, in such case they do not overlap.
			if ( ! bboxB.IsOutside( bboxLineA ) )				// they have common area.
			{
				outNoCommonArea					= false;						// we can't say that they don't have common area any more.
																				// from now on we are not sure about it.

				for ( size_t j = 0 ; j < cntB ; ++ j )
				{
					const VWPoint2D&	p1		= polyB.GetVertexAt( j );

					size_t				jNext	= ( j + 1 );
					jNext						= ( jNext < vertCntB ) ? jNext : 0;
					const VWPoint2D&	p2		= polyB.GetVertexAt( jNext );

					// check if line segments intersect (first if their bounding boxes have common area and then if they actually intersect).
					if ( VWLine2D::AreLineSegmentsIntersecting( p1, p2, v1, v2, kIntersSegsEpsilon ) )	// use fast check here !
					{
						areIntersecting			= true;
						break;
					}
				}

				if ( areIntersecting )
				{
					break;
				}
			}
		}

		// additional check:
		// if polygons don't intersect and all bounding boxes of polyA's segments are outside the bounding box of the polyB, ...
		// ... then the polygons might still have common area if the bounding box of polyB is inside the bounding box of polyA.
		if ( outNoCommonArea && bboxA.IsInside( bboxB ) )
		{
			outNoCommonArea						= false;
		}
	}

	// result.
	return	areIntersecting;
}

// checks if two polygons intersect each other (similar to the previous function). NOTE: it uses epsilon, ...
// ... hence, it is a little bit slower than the previous one, but catches the suspicious boundary cases.
// before checking for actual intersections, this function checks if bounding boxes have common area (using epsilon).
// NOTE: if returned 'outNoCommonArea' is true, then polygons don't have common area for sure, otherwise ...
// ... if 'outNoCommonArea' is false then polygons probably have common area, but this still has to be checked.
bool VWPolygon2D::ArePolygonsIntersecting(const VWPolygon2D& polyA, const VWPolygon2D& polyB, bool& outNoCommonArea, double epsilon)
{
	// init.
	bool				areIntersecting		= false;
	outNoCommonArea							= true;

	// validate.
	if ( polyA.IsEmpty() || polyB.IsEmpty() )
	{
		ASSERTN( kVStanev, false );	// bad input !
		return	false;
	}

	const VWRectangle2D&		bboxA		= polyA.GetPolygonBounds();
	const VWRectangle2D&		bboxB		= polyB.GetPolygonBounds();

	// first: check if bounding boxes of the two polygons do not have common area, in such case they do not overlap.
	if ( ! bboxA.IsOutside( bboxB, epsilon ) )					// bounding boxes have common area.
	{
		size_t					vertCntA	= polyA.GetVertexCount();
		size_t					cntA		= ( polyA.IsClosed() ) ? vertCntA : ( vertCntA - 1 );

		size_t					vertCntB	= polyB.GetVertexCount();
		size_t					cntB		= ( polyB.IsClosed() ) ? vertCntB : ( vertCntB - 1 );

		// next: check for intersection between the two polygons.
		for ( size_t i = 0 ; i < cntA ; ++ i )
		{
			const VWPoint2D&		v1		= polyA.GetVertexAt( i );

			size_t					iNext	= ( i + 1 );
			iNext							= ( iNext < vertCntA ) ? iNext : 0;
			const VWPoint2D&		v2		= polyA.GetVertexAt( iNext );

			VWRectangle2D			bboxLineA( v1.x, v2.x, v1.y, v2.y );		// get line bounding box.

			// check if line's bounding box has common area with the bounding box of the other poly, in such case they do not overlap.
			if ( ! bboxB.IsOutside( bboxLineA, epsilon ) )		// they have common area.
			{
				outNoCommonArea					= false;						// we can't say that they don't have common area any more.
																				// from now on we are not sure about it.

				for ( size_t j = 0 ; j < cntB ; ++ j )
				{
					const VWPoint2D&	p1		= polyB.GetVertexAt( j );

					size_t				jNext	= ( j + 1 );
					jNext						= ( jNext < vertCntB ) ? jNext : 0;
					const VWPoint2D&	p2		= polyB.GetVertexAt( jNext );

					// check if line segments intersect (first if their bounding boxes have common area and then if they actually intersect).
					if ( VWLine2D::AreLineSegmentsIntersecting( p1, p2, v1, v2, epsilon ) )	// use fast check here !
					{
						areIntersecting			= true;
						break;
					}
				}

				if ( areIntersecting )
				{
					break;
				}
			}
		}

		// additional check:
		// if polygons don't intersect and all bounding boxes of polyA's segments are outside the bounding box of the polyB, ...
		// ... then the polygons might still have common area if the bounding box of polyB is inside the bounding box of polyA.
		if ( outNoCommonArea && bboxA.IsInside( bboxB, epsilon ) )
		{
			outNoCommonArea						= false;
		}
	}

	// result.
	return	areIntersecting;
}

// checks whether given polygons overlap. note: works with polygon with corner vertices only. it is a fast check.
// note also that polygons are not expected to be closed (but it is recommended) !
/*static*/ bool VWPolygon2D::ArePolygonsOverlapping(const VWPolygon2D& polygonA, const VWPolygon2D& polygonB, double tolerance)
{
	// init.
	bool					noOverlap	= true;

	size_t					polyALen	= polygonA.GetVertexCount();
	size_t					polyBLen	= polygonB.GetVertexCount();

	// validation.
	VWFC_ASSERT( polyALen > 0 && polyBLen > 0 );

	if ( polyALen > 0 && polyBLen > 0 )	// non-empty polygons.
	{
		Sint32				onSegIndex;
		VWPoint2D			closestPtOnPoly;

		// check 1: are there vertices from 'polygonB' that fall within the 'polygonA' ?

		if ( noOverlap )				// still not known.
		{
			size_t			polyLen		= polygonB.farrVertices.size();
			for ( size_t i = 0 ; i < polyLen ; ++ i )
			{
				const VWPoint2D&	pt	= polygonB.farrVertices[ i ].pt;

				if ( polygonA.IsPtWithinOrNearPoly2D( pt, onSegIndex, closestPtOnPoly, tolerance ) )
				{
					noOverlap			= false;
					break;				// stop (overlapping already found).
				}
			}
		}

		// check 2: fast check whether 'polygonB' and 'polygonA' intersect each other ?

		if ( noOverlap )				// still not known.
		{
			// fast check for intersection between the polygons.
			if ( VWPolygon2D::ArePolygonsIntersecting( polygonA, polygonB, noOverlap, tolerance ) )	// polygons intersect each other.
			{
				noOverlap				= false;
			}
			else if ( ! noOverlap )		// might have common area (see how 'ArePolygonsIntersecting' works).
			{
				// init.
				noOverlap				= true;

				// check 3: last check - still we have 3 possibilities:
				// - 'polygonA' is inside the 'polygonB'.
				// - 'polygonB' is inside the 'polygonA'.
				// - no overlapping.

				if ( polyALen > 2 )		// 'polygonA' has at least 3 points (so it can contain).
				{
					const VWPoint2D& vp	= polygonB.GetVertexAt( 0 );	// get an arbitrary vertex.

					if ( polygonA.IsPtWithinOrNearPoly2D( vp, onSegIndex, closestPtOnPoly, tolerance ) )
					{
						noOverlap		= false;
					}
				}

				if ( noOverlap &&		// still not known and ...
					 polyBLen > 2 )		// ... 'polygonB' has at least 3 points (so it can contain).
				{
					const VWPoint2D& vp	= polygonA.GetVertexAt( 0 );	// get an arbitrary vertex.

					if ( polygonB.IsPtWithinOrNearPoly2D( vp, onSegIndex, closestPtOnPoly, tolerance ) )
					{
						noOverlap		= false;
					}
				}
			}
		}
	}

	// result.
	return	( ! noOverlap );
}

// polygonization.
// ---------------------------------------------------------------------------------------------------------------------
void VWPolygon2D::GetPolygonized(VWPolygon2D& outPolygon, double segmentationLength, bool areStraightForPolygonizing) const
{
	bool hasSegmentation = Double1_GT_Double2( segmentationLength, 0.0 );

	struct SSegmentationData
	{
		size_t	fIndexStart;
		size_t	fIndexEnd;
	};

	typedef std::vector<SSegmentationData> TSegmentationDataArray;

	TSegmentationDataArray	arrSegmentationData;
	auto segmentationCallback = [&](size_t inpuIndex, size_t outputIndexStart, size_t outputIndexEnd)
	{
		if ( hasSegmentation )
		{
			SSegmentationData data;
			data.fIndexStart	= outputIndexStart;
			data.fIndexEnd		= outputIndexEnd;
			arrSegmentationData.push_back( data );
		}
	};

	this->GetPolygonized(	outPolygon,
							false,
							kPolygonize_MaxRecursLevel,
							kPolygonize_ArcResolution,
							kPolygonize_MaxIterCount,
							segmentationCallback );

	if ( hasSegmentation )
	{
		bool				isClosed = outPolygon.IsClosed(); // store.

		TSTLPolygons2DArray	arrResults;
		// If the poly is closed, the last segmate is same as the first.
		for ( size_t i = 0, len = arrSegmentationData.size(); i < len - isClosed ? 1 : 0; ++i )
		{
			const auto&	data		= arrSegmentationData[i];
			size_t		ptsCnt		= data.fIndexEnd - data.fIndexStart;

			VWPolygon2D	poly;
			poly.fLockedForEdit		= true;
			for ( size_t j = 0; j < ptsCnt; ++j )
			{
				poly.AddVertex( outPolygon.GetVertexAt( data.fIndexStart + j ) );
			}

			if ( ptsCnt == 1 && areStraightForPolygonizing )
			{
				if ( i + 1 < len )
				{
					const auto&	secondData = arrSegmentationData[i + 1];
					if ( secondData.fIndexEnd - secondData.fIndexStart == 1 )
					{
						poly.AddVertex( outPolygon.GetVertexAt( data.fIndexStart + 1, true ) );
					}
				}
			}

			poly.CleanUpPolygon( VWPoint2D::sEpsilon );	// clean up.

			VWPolygon2D segmentedPoly;
			poly.GetSegmentedPoly( segmentedPoly, segmentationLength );
			
			if ( segmentedPoly.GetVertexCount() > 0 )
			{
				arrResults.push_back( segmentedPoly );
			}
		}

		VWPolygon2D::CLockForEdit editLock( outPolygon );

		outPolygon.ClearVertices();
		for ( size_t i = 0, len = arrResults.size() ; i < len; ++i )
		{
			outPolygon.AddVertex( arrResults[i] );
		}

		outPolygon.CleanUpPolygon( VWPoint2D::sEpsilon );

		outPolygon.SetClosed( isClosed );	// restore.
	}
}

// The last vertex may not be part of the result.
void VWPolygon2D::GetSegmentedPoly(VWPolygon2D& outPolygon, double segmentationLength) const
{
	size_t numOfVtxs = this->GetVertexCount();

	if ( Double1_GT_Double2( segmentationLength, 0.0 ) && numOfVtxs > 1 ) // at least 2 points.
	{
		size_t		lastVtxNumTo	= numOfVtxs;

		VWPoint2D	prevAddedPt;
		VWPoint2D	ptForAdd;
		VWPoint2D	prevToPt;
		VWPoint2D	ptCenter;

		VWPolygon2D	result;
		result.fLockedForEdit		= true;

		for ( size_t vtxNumTo = 0; vtxNumTo < lastVtxNumTo; ++vtxNumTo )
		{
			// 'GetVertexAt' will loop when reached the finish.
			VWPoint2D	toPt		= this->GetVertexAt( vtxNumTo, true );

			bool		addPrevVtx	= false;

			if ( vtxNumTo == 0 )
			{
				ptForAdd	= toPt;
				addPrevVtx	= true;
			}
			else
			{
				VWCircle2D	circle( ptCenter, segmentationLength );
				VWLine2D	line( prevToPt, toPt );
				WorldPt		pt1, pt2;
				if ( circle.Intersect( line, VWPoint2D::sEpsilon, pt1, pt2 ) )
				{
					double sqrDist1 = (prevAddedPt - pt1).MagnitudeSquared();
					double sqrDist2 = (prevAddedPt - pt2).MagnitudeSquared();

					if ( line.PtOnLine( pt1, VWPoint2D::sEpsilon ) && Double1_GE_Double2( sqrDist1, sqrDist2 ) )
					{
						addPrevVtx	= true;
						ptForAdd	= pt1;
					}
					else if ( line.PtOnLine( pt2, VWPoint2D::sEpsilon ) && Double1_LE_Double2( sqrDist1, sqrDist2 ) )
					{
						addPrevVtx	= true;
						ptForAdd	= pt2;
					}
				}
			}

			if ( addPrevVtx )
			{
				result.AddVertex( ptForAdd );
				prevAddedPt	= ptCenter;
				ptCenter	= ptForAdd;

				if ( vtxNumTo > 0 )
				{
					--vtxNumTo;
				}
				else
				{
					prevAddedPt	= ptForAdd;
					prevToPt	= toPt;
				}

				addPrevVtx	= false;
			}
			else
			{
				prevToPt = toPt;
			}
		}

		size_t	resultVertCnt			= result.GetVertexCount();

		if ( resultVertCnt > 0 ) // non-empty poly.
		{
			outPolygon = result;
		}
	}
	else
	{
		outPolygon = *this;
	}
}

// given a polygon (corner vertices only), segments it (subdivides it) into segments of 'segmentation length' by introducing ...
// ... new vertices while preserving the original ones (thus, there might be produced shorter segments as well).
// note: shape of the original polygon will be fully preserved.
void VWPolygon2D::GetSegmentedPolygon(VWPolygon2D& outPolygon, double segmentationLength) const
{
	// init.
	outPolygon.ClearVertices();

	size_t				ptsCnt		= this->GetVertexCount();

	if ( ( ptsCnt > 1 ) &&									// valid polygon and ...
		 Double1_GT_Double2( segmentationLength, 0.0 ) )	// ... valid segmentation length.
	{
		size_t			procCnt		= ptsCnt;

		// check whether it is closed polygon.
		if ( fbIsClosed )			// closed.
		{
			const VWPoint2D&		firstPt		= this->GetVertexAt( 0 );
			const VWPoint2D&		lastPt		= this->GetVertexAt( ptsCnt - 1 );

			if ( ! MathUtils::Equalish( firstPt, lastPt, VWPoint2D::sEpsilon ) )	// not coinciding.
			{
				++ procCnt;			// increase (to cover the last polygon segment).
			}
		}

		// get squared segmentation length.
		double			sqrSegmLen	= sqr( segmentationLength );

		VWPoint2D		ptToAdd;
		WorldPt			intrsPt0, intrsPt1;
		bool			addPt, addIntrs;
		double			sqrLineLen;
		size_t			inx;

		TSTLPoints2DArray			resOrderedPts;

		for ( size_t it = 0 ; it < procCnt ; ++ it )
		{
			inx			= ( it < ptsCnt ? it : 0 );
			const VWPoint2D&		pt			= this->GetVertexAt( inx );

			// init.
			addPt		= false;
			addIntrs	= false;

			if ( it == 0 )			// first point.
			{
				addPt	= true;		// add first point.

				ptToAdd	= pt;
			}
			else	// not first (has previous).
			{
				VWLine2D			line( ptToAdd /*previous added*/, pt );	// last not examined line.
				VWCircle2D			circle( ptToAdd /*previous added*/, segmentationLength );

				// get the squared line length.
				sqrLineLen			= ptToAdd.DistanceSquaredTo( pt );

				// find the intersections between the circle and the line.
				if ( ( sqrLineLen > sqrSegmLen + VWPoint2D::sSqrEpsilon ) &&
					 circle.Intersect( line, VWPoint2D::sEpsilon, intrsPt0, intrsPt1 ) )
				{
					if ( line.PtOnLine( intrsPt0, VWPoint2D::sEpsilon ) )
					{
						addIntrs	= true;		// add first intersection.

						ptToAdd		= intrsPt0;
					}
					else if ( line.PtOnLine( intrsPt1, VWPoint2D::sEpsilon ) )
					{
						addIntrs	= true;		// add second intersection.

						ptToAdd		= intrsPt1;
					}
					//else: no valid intersection - not expected here.
				}
				//else: no valid intersection.

				if ( ! addIntrs )	// not a valid intersection.
				{
					addPt			= true;		// add the point.

					ptToAdd			= pt;
				}
			}

			if ( addIntrs )			// intersection to add.
			{
				// add.
				resOrderedPts.push_back( ptToAdd );

				// validate: 'it' > 0 in this case.
				VWFC_ASSERT( it > 0 );			// must not happen.

				-- it;	// decrease (stay on the same segment).
			}
			else if ( addPt )		// point to add.
			{
				// add.
				resOrderedPts.push_back( ptToAdd );
			}
		}

		// validate.
		VWFC_ASSERT( resOrderedPts.size() > 0 );

		if ( resOrderedPts.size() > 0 )		// non-empty polygon.
		{
			outPolygon	= resOrderedPts;	// form the result polygon.

			outPolygon.SetClosed( fbIsClosed );
		}
	}
	else
	{
		outPolygon		= *this;
	}
}

// get polygonization:
// has parameters to control the density of the resulting polygon. recommended to use defaults !
// if 'interpolate' is true, then bezier and cubic segments will be interpolated by adding cubic vertices, ...
// ... so result will be interpolation poly with only corner and cubic vertices.
void VWPolygon2D::GetPolygonized(	VWPolygon2D& outPolygon,
									bool	interpolate		/*=false*/,
									short	splineRecusLevel/*=kPolygonize_MaxRecursLevel*/,
									double	arcDegRes		/*=kPolygonize_ArcResolution*/,
									size_t	iterationCount	/*=kPolygonize_MaxIterCount*/,
									std::function<void(size_t inpuIndex, size_t outputIndexStart, size_t outputIndexEnd)> callbackAddSegment,
									short	arcRecursLevel	/*=kPolygonize_MaxRecursLevel*/) const
{
	// XXX Bobi: an optimization.
	// lock the 'outPolygon' while collecting its polygonization points.
	// this suppresses recalculating of the polygon bounding box - it is a slow operation which is not needed here.
	// Note: at the end the 'outPolygon' must be unlocked and its bounding box must be recalculated once !
	outPolygon.fLockedForEdit		= true;

	// init.
	outPolygon.ClearVertices();

	size_t				ptsCnt		= farrVertices.size();

	// validation.
	if ( ptsCnt <= 1 )
	{
		ASSERTN( kVStanev, false );
		return;
	}

	// init the array of extended vertices.
	TExtVertexArray		arrVertices;
	for ( size_t i = 0 ; i < ptsCnt ; ++ i )
	{
		SExtVertex		extVert		= farrVertices[ i ];
		arrVertices.push_back( extVert );
	}

	bool				isClosed	= this->IsClosed();

	// check for a special case: first point coincides with the last one.
	if (	( ptsCnt > 2 ) &&
			( MathUtils::Equalish( arrVertices[ 0 ].pt, arrVertices[ ptsCnt - 1 ].pt, VWPoint2D::sEpsilon ) ) )
	{
		// validate: coincident points must have same vertex types.
		if( arrVertices[ 0 ].type == arrVertices[ ptsCnt - 1 ].type )
		{
			// remove first point.
			arrVertices.erase( arrVertices.begin() );
			-- ptsCnt;
		}
		else if ( arrVertices[ ptsCnt - 1 ].type == eVertexType_Corner )
		{
			// remove last point when it is set to corner 
			arrVertices.pop_back();
			-- ptsCnt;
		}
		isClosed					= true;
	}

	outPolygon.SetClosed( isClosed );

	// prepare cubic vertices.
	this->CalculatePolyline( arrVertices, iterationCount );
	this->SwapControlPts( arrVertices );

	size_t				lastVertI	= ( ptsCnt - 1 );
	SExtVertex			lastVert	= arrVertices[ lastVertI ];

	size_t				thisVertI	= 0;
	SExtVertex			thisVert	= arrVertices[ thisVertI ];

	size_t				nextVertI	= 1;
	SExtVertex			nextVert	= arrVertices[ nextVertI ];

	if ( isClosed && ( thisVert.type != eVertexType_Corner ) )	// the polyline is closed and start vertex is not corner.
	{
		size_t vertStart = outPolygon.GetVertexCount();

		// polygonize the start poly segment.
		this->PolygonizeSection( lastVert, thisVert, nextVert, outPolygon, interpolate, splineRecusLevel, arcDegRes, arcRecursLevel );

		if ( callbackAddSegment )
		{
			callbackAddSegment( thisVertI, vertStart, outPolygon.GetVertexCount() );
		}
	}
	else														// the start point of an open polyline must be a corner vertex.
	{
		size_t vertStart = outPolygon.GetVertexCount();

		lastVert.pt					= thisVert.pt;

		outPolygon.AddVertex( lastVert.pt );					// add as corner vertex.

		if ( callbackAddSegment )
		{
			callbackAddSegment( thisVertI, vertStart, outPolygon.GetVertexCount() );
		}
	}

	// polygonize next segments.
	for ( size_t i = 2 ; i < ptsCnt ; ++ i )
	{
		size_t vertStart = outPolygon.GetVertexCount();

		lastVertI					= thisVertI;
		lastVert					= thisVert;
		thisVertI					= nextVertI;
		thisVert					= nextVert;
		nextVertI					= i;
		nextVert					= arrVertices[ i ] ;

		// polygonize current poly segment.
		this->PolygonizeSection( lastVert, thisVert, nextVert, outPolygon, interpolate, splineRecusLevel, arcDegRes, arcRecursLevel );

		if ( callbackAddSegment )
		{
			size_t	vertEnd = outPolygon.GetVertexCount();
			if ( vertEnd > vertStart && vertEnd - vertStart > 1 )
			{
				// we have a curve, so include the starting vertex
				if ( vertStart > 0 )
				{
					vertStart --;
				}
			}

			callbackAddSegment( thisVertI, vertStart, vertEnd );
		}
	}

	lastVertI						= thisVertI;
	lastVert						= thisVert;
	thisVertI						= nextVertI;
	thisVert						= nextVert;
	nextVertI						= 0;
	nextVert						= arrVertices[ 0 ];

	if ( isClosed && ( thisVert.type != eVertexType_Corner ) )	// the polyline is closed and last vertex is not corner.
	{
		size_t vertStart = outPolygon.GetVertexCount();

		// polygonize the last poly segment.
		this->PolygonizeSection( lastVert, thisVert, nextVert, outPolygon, interpolate, splineRecusLevel, arcDegRes, arcRecursLevel );

		if ( callbackAddSegment )
		{
			callbackAddSegment( thisVertI, vertStart, outPolygon.GetVertexCount() );
		}
	}
	else														// the start point of an open polyline must be a corner vertex.
	{
		size_t vertStart = outPolygon.GetVertexCount();

		outPolygon.AddVertex( thisVert.pt );					// add as corner vertex.

		if ( callbackAddSegment )
		{
			callbackAddSegment( thisVertI, vertStart, outPolygon.GetVertexCount() );
		}
	}

	if ( isClosed && ( ! outPolygon.IsEmpty() ) )
	{
		size_t vertStart = outPolygon.GetVertexCount();

		outPolygon.AddVertex( outPolygon.GetVertexAt( 0 ) );	// enclose the polygon.

		if ( callbackAddSegment )
		{
			callbackAddSegment( 0, vertStart, outPolygon.GetVertexCount() );
		}
	}

	if ( callbackAddSegment == nullptr )
	{
		// clean up.
		outPolygon.CleanUpPolygon( VWPoint2D::sEpsilon );
	}

	// XXX Bobi: an optimization.
	// unlock the 'outPolygon' as all polygonization points are already collected in it.
	// also recalculate its bounding box once here.
	outPolygon.fLockedForEdit		= false;
	outPolygon.RecalculateBoundingBox();
}

// having a non-corner poly vertex, finds the previous and next corner vertices and polygonizes the poly between them.
// if there are not corner vertices at all, returns closed polygonization of the whole polyline.
bool VWPolygon2D::GetPolygonizedPartOfClosedPoly(size_t inIndex, VWPolygon2D& outPolygon, size_t& outBegIndex, size_t& outEndIndex) const
{
	// constants used for polygonization.
	const short					kRecurLevel		= 4;
	const double				kArcDegRes		= 7.0;
	const size_t				kItersCnt		= 4;

	// init.
	bool						isFound			= false;

	size_t						vertCnt			= this->GetVertexCount();

	// validate.
	if ( this->IsClosed() &&					// poly is closed (as expected) and ...
		 inIndex < vertCnt )					// ... it is a valid segment index.
	{
		if ( this->GetVertexType( inIndex ) != eVertexType_Corner )
		{
			VWPolygon2D			subPolyToPolygonize;

			// get previous corner vertex.
			bool				isOK			= this->GetPrevCornerVertexInClosedPoly( inIndex, outBegIndex );
			if ( isOK )							// go on.
			{
				// get next corner vertex.
				isOK							= this->GetNextCornerVertexInClosedPoly( inIndex, outEndIndex );
				if ( isOK )						// go on. both previous and next corner vertices are found.
				{
					// check if there is just a single corner vertex in the polyline ('outBegIndex' == 'outEndIndex').
					isOK						= ( outBegIndex > outEndIndex );
					if ( isOK )					// go on. there are at least 2 corner vertices in the polyline.
					{
						// prepare the sub-polyline between the found previous and next vertices.

						NNA_SCOPE
						{
							// XXX Bobi:
							// this temporary suppresses recalculating of the poly bounding box - ...
							// ... it's a slow operation and not needed while collecting points.
							VWPolygon2D::CLockForEdit	subPolyLock( subPolyToPolygonize );

							size_t	index;
							if ( outBegIndex > 0 )	index		= ( outBegIndex - 1 );
							else					index		= ( vertCnt - 1 );

							do
							{
								++ index;			// increase index.

								if ( index >= vertCnt ) index	= ( index % vertCnt );

								subPolyToPolygonize.AddVertex(	this->GetVertexAt(			index ),	// position.
																this->GetVertexType(		index ),	// vertex type.
																this->GetArcVertexRadius(	index ) );	// vertex radius.
							}
							while ( index != outEndIndex );
						}

						// force open.
						subPolyToPolygonize.SetClosed( false );
					}
					else
					{
						ASSERTN( kVStanev, ( outBegIndex == outEndIndex ) );	// not expected. check !
					}
				}
			}

			if ( ! isOK )						// there are non-corner vertices at all.
			{
				// we need to polygonize the whole polyline in this case.
				// the resulting polygon will be closed.

				subPolyToPolygonize				= *this;
			}

			// get polygonized.
			subPolyToPolygonize.GetPolygonized( outPolygon, false, kRecurLevel, kArcDegRes, kItersCnt );

			// mark as found.
			isFound								= true;
		}
		//else: it is a corner vertex. doesn't need polygonization.
	}
	else
	{
		ASSERTN( kVStanev, false );				// bad input. check !
	}

	// result.
	return	( isFound );
}

// given 'from' and 'to' indices, gets a part of a closed poly in between.
bool VWPolygon2D::GetPartOfClosedPolyFromTo(size_t fromIndex, size_t toIndex, VWPolygon2D& outPolyPart) const
{
	// init.
	outPolyPart.ClearVertices();
	outPolyPart.SetClosed( false );				// force open.

	size_t							vertCnt		= this->GetVertexCount();

	if ( this->IsClosed() &&					// poly is expected to be closed and ...
		 vertCnt > 1 )							// ... not empty.
	{
		NNA_SCOPE
		{
			// XXX Bobi:
			// this temporary suppresses recalculating of the poly bounding box - ...
			// ... it's a slow operation and not needed while collecting points.
			VWPolygon2D::CLockForEdit	outPolyPartLock( outPolyPart );

			// validate.
			ASSERTN( kVStanev, ( fromIndex < vertCnt && toIndex < vertCnt ) );	// bad input.

			size_t					index;
			if ( fromIndex > 0 )	index		= ( fromIndex - 1 );
			else					index		= ( vertCnt - 1 );

			do
			{
				++ index;						// increase index.

				if ( index >= vertCnt ) index	= ( index % vertCnt );

				// add.
				outPolyPart.AddVertex( this->GetVertexAt(		index ),	// position.
									   this->GetVertexType(		index ),	// vertex type.
									   this->GetArcVertexRadius(index ) );	// vertex radius.
			}
			while ( index != toIndex );
		}
	}
	else
	{
		ASSERTN( kVStanev, false );				// bad input.
	}

	// result.
	return	( outPolyPart.GetVertexCount() > 0 );
}

// get previous corner vertex in a closed polyline.
bool VWPolygon2D::GetPrevCornerVertexInClosedPoly(size_t inIndex, size_t& outPrevIndex) const
{
	// init.
	outPrevIndex					= size_t(-1);

	size_t				vertCnt		= this->GetVertexCount();

	if ( this->IsClosed() &&		// poly is expected to be closed and ...
		 vertCnt > 1 )				// ... not empty.
	{
		// validate.
		ASSERTN( kVStanev, ( inIndex < vertCnt ) );		// bad input.

		size_t			toIndex		= ( inIndex + 1 ) % vertCnt;	// threshold index for searching.
		ptrdiff_t		index		= inIndex;						// init index for searching.

		do
		{
			-- index;									// decrease index.

			if ( index < 0 ) index	= ( vertCnt - 1 );	// just become negative.

			if ( this->GetVertexType( index ) == eVertexType_Corner )
			{
				outPrevIndex		= index;

				break;				// stop !
			}
		}
		while ( index != (ptrdiff_t) toIndex );
	}
	else
	{
		ASSERTN( kVStanev, false );	// bad input.
	}

	// result.
	return	( outPrevIndex != size_t(-1) );
}

// get next corner vertex in a closed polyline.
bool VWPolygon2D::GetNextCornerVertexInClosedPoly(size_t inIndex, size_t& outNextIndex) const
{
	// init.
	outNextIndex							= size_t(-1);

	size_t					vertCnt			= this->GetVertexCount();

	if ( this->IsClosed() &&				// poly is expected to be closed and ...
		 vertCnt > 1 )						// ... not empty.
	{
		// validate.
		ASSERTN( kVStanev, ( inIndex < vertCnt ) );		// bad input.

		size_t				toIndex;
		if ( inIndex > 0 )	toIndex			= ( inIndex - 1 );
		else				toIndex			= ( vertCnt - 1 );

		size_t				index			= inIndex;		// init index for searching.

		do
		{
			++ index;						// increase index.

			if ( index >= vertCnt ) index	= ( index % vertCnt );

			if ( this->GetVertexType( index ) == eVertexType_Corner )
			{
				outNextIndex				= index;

				break;						// stop !
			}
		}
		while ( index != toIndex );
	}
	else
	{
		ASSERTN( kVStanev, false );			// bad input.
	}

	// result.
	return	( outNextIndex != size_t(-1) );
}

void VWPolygon2D::CalculatePolyline(	TExtVertexArray& arrVertices,
										size_t iterationCount/*=kPolygonize_MaxIterCount*/) const
// This function seems to iterate through the polyline looking for
// cubic control points.  If it does not find any it exits.  If some are found they are processed.
//
// According to SteveJ:
// This is computing the controlPt member of the PolylineVert structure for the cubic verts.
// The controlPt is a cached value, which, one would think, could be updated at edit/reset time.
// We are always doing this in Render.
///////////////////////////////////////////////////////////////////////////////
{
	size_t			ptsCnt			= arrVertices.size();

	if ( ptsCnt > 1 )		// there are at least two points.
	{
		// check if there are cubic vertices and set the control pt to pt for them (the cubic vertices).
		bool		bFound			= false;
		for ( size_t k = 1 ; k <= ptsCnt ; ++ k )
		{
			SExtVertex*	vertex		= & arrVertices[ k - 1 ];
			if ( vertex->type == eVertexType_Cubic )
			{
				vertex->controlPt	= vertex->pt;
				bFound				= true;
			}
		}

		// don't bother to itterate if no cubics are found.
		if ( ! bFound )
		{
			return;
		}

		size_t		prevIndex		= ( ptsCnt - 1 );
		size_t		i				= ptsCnt;

		VWPoint2D	vPrev;
		VWPoint2D	vNext;

		// here we set 5 iterations.
		for ( size_t j = 1 ; j <= iterationCount ; ++ j )
		{
			for ( size_t nextIndex = 1 ; nextIndex <= ptsCnt ; ++ nextIndex )
			{
				SExtVertex*		currVertex		= & arrVertices[ i - 1 ];
				if ( currVertex->type == eVertexType_Cubic )
				{
					SExtVertex	prevVertex		= arrVertices[ prevIndex - 1 ];
					switch ( prevVertex.type )
					{
						case eVertexType_Cubic:
							{
								vPrev			= prevVertex.controlPt;
								break;
							}
						case eVertexType_Corner:
							{
								VWPoint2D	tempPt	= prevVertex.pt	- arrVertices[ i - 1 ].controlPt;
								vPrev				= tempPt + prevVertex.pt;
								break;
							}
						default:
							{
								vPrev			= prevVertex.pt;
								break;
							}
					}

					SExtVertex	nextVertex		= arrVertices[ nextIndex - 1 ];

					switch ( nextVertex.type )
					{
						case eVertexType_Cubic:
							{
								vNext			= nextVertex.controlPt;
								break;
							}
						case eVertexType_Corner:
							{
								VWPoint2D	tempPt	= nextVertex.pt - arrVertices[ i - 1 ].controlPt;
								vNext				= tempPt + nextVertex.pt;
								break;
							}
						default:
							{
								vNext			= nextVertex.pt;
								break;
							}
					}

					// with third order.
					double	divResultX			= ( currVertex->pt.x - ( vPrev.x + vNext.x ) * 0.5 ) / 3.0;
					// third order.
					double	divResultY			= ( currVertex->pt.y - ( vPrev.y + vNext.y ) * 0.5 ) / 3.0;

					// update the polyline.
					currVertex->controlPt.x		= ( currVertex->pt.x + divResultX );
					currVertex->controlPt.y		= ( currVertex->pt.y + divResultY );
				}

				prevIndex	= i;
				i			= nextIndex;

			} // end for nextIndex loop.
		} // end for j loop.
	}
}

void VWPolygon2D::SwapControlPts(TExtVertexArray& arrVertices) const
{
	size_t				ptsCnt	= arrVertices.size();
	for ( size_t i = 1 ; i <= ptsCnt ; ++ i )
	{
		SExtVertex*		vertex	= & arrVertices[ i - 1 ];
		// swap control pt and pt for cubic vertices.
		if ( vertex->type == eVertexType_Cubic )
		{
			VWPoint2D	tmp		= vertex->controlPt;
			vertex->controlPt	= vertex->pt;
			vertex->pt			= tmp;
		}
	}
}

void VWPolygon2D::PolygonizeSection(	const SExtVertex& lastVert, const SExtVertex& thisVert, const SExtVertex& nextVert,
										VWPolygon2D& outPolygon,
										bool	interpolate		/*=false*/,
										short	splineRecusLevel/*=kPolygonize_MaxRecursLevel*/,
										double	arcDegRes		/*=kPolygonize_ArcResolution*/,
										short	arcRecursLevel	/*=kPolygonize_MaxRecursLevel*/) const
{
	switch ( thisVert.type )
	{
		case eVertexType_Corner:
			{
				outPolygon.AddVertex( thisVert.pt );		// add.
			}
			break;
		case eVertexType_Cubic:
		case eVertexType_Bezier:
			{
				VWPoint2D		p0, p2;

				if ( lastVert.type	== eVertexType_Corner )	p0	= lastVert.pt;
				else										p0	= ( thisVert.pt + lastVert.pt ) * 0.5;

				if ( nextVert.type == eVertexType_Corner )	p2	= nextVert.pt;
				else										p2	= ( thisVert.pt + nextVert.pt ) * 0.5;

				// polygonize the spline sub section.
				this->PolygonizeSplineSubSection( p0, thisVert.pt, p2, splineRecusLevel, interpolate, outPolygon );
			}
			break;
		case eVertexType_Arc:
		case eVertexType_Radius:
			{
				VWPoint2D		lastPt, nextPt;

				if ( lastVert.type == eVertexType_Corner )	lastPt	= lastVert.pt;
				else										lastPt	= ( lastVert.pt + thisVert.pt ) * 0.5;

				outPolygon.AddVertex( lastPt );				// add.

				if ( nextVert.type == eVertexType_Corner)	nextPt = nextVert.pt;
				else										nextPt = ( nextVert.pt + thisVert.pt ) * 0.5;

				if ( thisVert.type == eVertexType_Arc )
				{
					// polygonize the arc.
					this->PolygonizeArc( lastPt, thisVert.pt, nextPt, thisVert.dArcRadius, outPolygon, arcRecursLevel );
				}
				else if ( thisVert.type == eVertexType_Radius )
				{
					// 'thisVert.pt' lies on the arc.
					VWArc2D			arc( lastPt, thisVert.pt, nextPt );	// form the arc.

					VWPolygon2D		arcPolygon;
					arc.GetPolygon( arcPolygon, arcDegRes, false );		// polygonize arc to corner vertices only.

					outPolygon.AddVertex( arcPolygon );					// add resulting polygon.
				}
			}
			break;
	}
}

void VWPolygon2D::PolygonizeSplineSubSection(const VWPoint2D& v1, const VWPoint2D& v2, const VWPoint2D& v3, short level, bool interpolate, VWPolygon2D& outPolygon) const
{
	VWPoint2D		v12, v22, v23;
	VWPoint2D		v1A, v2A, v3A, v1B, v2B, v3B;

	VWLine2D		line;

	if ( level > 1 )					// now if it is called with level > 1, it processes
	{
		v12 = ( v1 + v2 )	* 0.5;		// 2 levels, to reduce the number of recursive
		v23 = ( v2 + v3 )	* 0.5;		// function calls, which makes it faster; also
		v22 = ( v12 + v23 ) * 0.5;		// it won't make a recursive call with level = 0,
		-- level;						// but will do the TDFLineTo [BF 11/7/02]

		v1A = v1;
		v2A = v12;
		v3A = v22;
		v1B = v22;
		v2B = v23;
		v3B = v3;

		v12 = ( v1A + v2A ) * 0.5;
		v23 = ( v2A + v3A ) * 0.5;
		v22 = ( v12 + v23 ) * 0.5;
		-- level;

		if ( level == 0 )
		{
			if ( interpolate )
			{
				outPolygon.AddVertex( v22, eVertexType_Cubic );
				outPolygon.AddVertex( v3A, eVertexType_Cubic );
			}
			else
			{
				outPolygon.AddVertex( v22 );
				outPolygon.AddVertex( v3A );
			}
		}
		else
		{
			// recursion.
			this->PolygonizeSplineSubSection( v1A, v12, v22, level, interpolate, outPolygon );
			this->PolygonizeSplineSubSection( v22, v23, v3A, level, interpolate, outPolygon );
		}

		v12 = ( v1B + v2B ) * 0.5;
		v23 = ( v2B + v3B ) * 0.5;
		v22 = ( v12 + v23 ) * 0.5;

		if ( level == 0 )
		{
			if ( interpolate )
			{
				outPolygon.AddVertex( v22, eVertexType_Cubic );
				outPolygon.AddVertex( v3B, eVertexType_Cubic );
			}
			else
			{
				outPolygon.AddVertex( v22 );
				outPolygon.AddVertex( v3B );
			}
		}
		else
		{
			// recursion.
			this->PolygonizeSplineSubSection( v1B, v12, v22, level, interpolate, outPolygon );
			this->PolygonizeSplineSubSection( v22, v23, v3B, level, interpolate, outPolygon );
		}
	}
	else if ( level == 1 )
	{
		v12 = ( v1 + v2 )	* 0.5;
		v23 = ( v2 + v3 )	* 0.5;
		v22 = ( v12 + v23 ) * 0.5;

		if ( interpolate )
		{
			outPolygon.AddVertex( v22, eVertexType_Cubic );
			outPolygon.AddVertex( v3, eVertexType_Cubic );
		}
		else
		{
			outPolygon.AddVertex( v22 );
			outPolygon.AddVertex( v3 );
		}
	}
	else
	{
		if ( interpolate )
		{
			outPolygon.AddVertex( v3, eVertexType_Cubic );
		}
		else
		{
			outPolygon.AddVertex( v3 );
		}
	}
}

bool VWPolygon2D::CalcChamfer(const VWPoint2D& pt1, const VWPoint2D& int0Value, const VWPoint2D& pt4, VWPoint2D& lastCam, VWPoint2D& thisCam, VWPoint2D& center, double& radius, double& lastAngle, double& thisAngle) const
{
	VWPoint2D	int0	= int0Value;
	double		shortLen;
	VWPoint2D	thisPerp, lastPerp, lastVec, thisVec;
	double		lastLen, thisLen;
	bool 		intersect, parallel;
	double		signedRadius;

	// find intersection.
	VWLine2D::IntersectLines( pt1, int0, int0, pt4, intersect, parallel, int0, kPolygonize_IntersEpsilon );

	if ( parallel )
	{
		return	false;
	}
	else
	{
		thisLen			= int0.DistanceTo( pt4 );
		lastLen			= int0.DistanceTo( pt1 );
		if ( thisLen != 0 )		thisVec = ( pt4 - int0 ) / thisLen;	// normalize.
		if ( lastLen != 0 )		lastVec = ( pt1 - int0 ) / lastLen;	// normalize.

		// if the radius is preset by user and the segments are long enough then use the preset radius.
		// if the lengths are within a certain percentage of eachother, don't bother with the Cams.
		if ( ( thisLen != 0 ) && ( Abs( ( lastLen / thisLen ) - 1 ) < 0.001 ) )
		{
			lastCam		= pt1;
			thisCam		= pt4;
		}
		else if ( lastLen < thisLen )
		{
			lastCam		= pt1;
			thisCam		= int0 + thisVec * lastLen;
		}
		else
		{
			thisCam		= pt4;
			lastCam		= int0 + lastVec * thisLen;
		}

		// arc part.
		thisPerp		= thisCam;
		VWPoint2D	perpVec( thisVec.y, -thisVec.x );
		thisPerp		-=	perpVec;
		lastPerp		= lastCam;
		perpVec.SetPoint( lastVec.y, -lastVec.x );
		lastPerp		-= perpVec;
		VWLine2D::IntersectLines( lastCam, lastPerp, thisCam, thisPerp, intersect, parallel, center, kPolygonize_IntersEpsilon );

		if ( parallel )
		{
			return false;
		}

		shortLen		= Min( ( center - thisCam ).Magnitude(), ( center - lastCam ).Magnitude() );

		if ( radius > 0.0 )		// valid preset radius.
		{
			if ( shortLen <= radius )	// 'shortLen' is shorter than the preset radius - use 'shortLen'.
			{
				radius			= shortLen;
			}
			else
			{
				signedRadius	= ( lastVec.CrossProductMagnitude( thisVec ) > 0 ) ? radius : -radius;

				// make first Vector negative so it will point in due to right hand rule.
				thisVec			= ( thisVec.Perp() * signedRadius );
				lastVec			= ( lastVec.Perp() * -signedRadius );

				VWLine2D::IntersectLines( ( thisVec + int0 ), ( thisVec + pt4 ), ( lastVec + int0 ), ( lastVec + pt1 ),
										  intersect, parallel, center, kPolygonize_IntersEpsilon );

				lastCam			= ( center - lastVec );
				thisCam			= ( center - thisVec );
			}
		}
		else					// zero preset radius - use 'shortLen'.
		{
			radius				= shortLen;
		}

		if ( parallel )
		{
			return false;
		}
		else
		{
			lastAngle	= MathUtils::FixedAngle( center, lastCam );
			thisAngle	= MathUtils::FixedAngle( center, thisCam );

			thisAngle	-= lastAngle;

            if ( thisAngle == 0 || std::abs( (int)thisAngle ) == 360 )
			{
				return false;
			}
			else
			{
				lastAngle			= 90.0 - lastAngle;
				thisAngle			= -thisAngle;

				if ( thisAngle > 180.0 )
				{
					thisAngle		-= 360.0;
				}
				else if (-thisAngle > 180.0 )
				{
					thisAngle		+= 360.0;
				}

				if ( lastAngle < 0 )
				{
					do
					{
						lastAngle	+= 360.0;
					}
					while ( lastAngle <= 0 );
				}

				if ( lastAngle > 360.0 )
				{
					do
					{
						lastAngle	-= 360.0;
					}
					while ( lastAngle >= 360.0 );
				}
			}
		}

		return true;
	}
}

VWPoint2D VWPolygon2D::NextLoc(double a, const VWPoint2D& cen, double radius) const
{
	VWPoint2D	orientation(	1, 0 );
	VWPoint2D	perpDir(		0, 1 );

	return		( cen + radius * MathUtils::SpecialSin( a ) * orientation + radius * MathUtils::SpecialCos( a ) * perpDir );
}

void VWPolygon2D::PolygonizeArc(const VWPoint2D& lastPt, const VWPoint2D& thisPt, const VWPoint2D& nextPt, double radius, VWPolygon2D& outPolygon, short arcRecursLevel) const
{
	VWPoint2D	lastCam;
	VWPoint2D	thisCam;
	VWPoint2D	center;
	double		theStart;
	double		theArc;

	// prepare the arc.
	if ( this->CalcChamfer( lastPt, thisPt, nextPt, lastCam, thisCam, center, radius, theStart, theArc ) )
	{
		this->PolygonizeArc( lastPt, nextPt, radius, lastCam, thisCam, center, theStart, theArc, outPolygon, arcRecursLevel );
	}
}

void VWPolygon2D::PolygonizeArc(const VWPoint2D &lastPt, const VWPoint2D& nextPt, double radius, VWPoint2D& lastCam, VWPoint2D& thisCam, VWPoint2D& center, double theStart, double theArc, VWPolygon2D& outPolygon, short arcRecursLevel) const
{
	if ( lastPt != lastCam )
	{
		outPolygon.AddVertex( lastCam );
	}

	if ( theArc )
	{
		this->PolygonizeArcSegment( theStart, theArc, center, radius, outPolygon, arcRecursLevel );
	}

	if ( nextPt != thisCam )
	{
		outPolygon.AddVertex( thisCam );
	}
}

void VWPolygon2D::PolygonizeArcSegment(double inStart, double inArc, const VWPoint2D& cen, double radius, VWPolygon2D& outPolygon, short arcRecursLevel) const
{
	if ( inArc < 0 )
	{
		inStart			+= 360.0;
	}

	double	theEnd		= inArc + inStart;

	if ( ( theEnd >= 360.0 ) && ( inStart > 360.0 ) )
	{
		theEnd 			-= 360.0;
		inStart			-= 360.0;
	}

	// start recursion level.
	short	startLevel	= arcRecursLevel;

	this->PolygonizeArcSegment( inStart, theEnd, startLevel, cen, radius, outPolygon );
}

void VWPolygon2D::PolygonizeArcSegment(double arcStart, double arcEnd, short currentLevel, const VWPoint2D& cen, double radius, VWPolygon2D& outPolygon) const
{
	double	midArc		= ( arcStart + arcEnd ) * 0.5;
	double	normalArc	= midArc;

	if ( midArc >= 360.0 )
	{
		normalArc		-= 360.0;
	}

	if ( currentLevel > 1 )
	{
		-- currentLevel;

		// recursion.
		this->PolygonizeArcSegment( arcStart, midArc, currentLevel, cen, radius, outPolygon );

		// add arc point.
		const VWPoint2D& nextPt	= this->NextLoc( normalArc, cen, radius );
		outPolygon.AddVertex( nextPt );

		// recursion.
		this->PolygonizeArcSegment( midArc, arcEnd, currentLevel, cen, radius, outPolygon );
	}
	else
	{
		const VWPoint2D&	nextPt		= this->NextLoc( midArc, cen, radius );
		outPolygon.AddVertex( nextPt );
	}
}

// checks if the radius of arc vertex ('thisVert') is degenerate (zero) and recalculates it.
void VWPolygon2D::RecalcDegenerateArcVertexRadius(SVertex* lastVert, SVertex* thisVert, SVertex* nextVert)
{
	if ( thisVert->type == eVertexType_Arc &&										// arc vertex ...
		 MathUtils::Equalish( thisVert->dArcRadius, 0.0, VWPoint2D::sEpsilon ) )	// ... with zero radius (degenerate radius).
	{
		VWPoint2D	lastPt, nextPt;

		if ( lastVert->type == eVertexType_Corner )	lastPt	= lastVert->pt;
		else										lastPt	= ( lastVert->pt + thisVert->pt ) * 0.5;

		if ( nextVert->type == eVertexType_Corner )	nextPt	= nextVert->pt;
		else										nextPt	= ( nextVert->pt + thisVert->pt ) * 0.5;

		VWPoint2D	lastCam, thisCam, center;
		double		theStart, theArc;

		double		newRadius			= thisVert->dArcRadius;

		// use the following function to calculate the arc radius.
		if ( this->CalcChamfer( lastPt, thisVert->pt, nextPt, lastCam, thisCam, center, newRadius, theStart, theArc ) )
		{
			thisVert->dArcRadius		= newRadius;
		}
	}
}

// Checks if the four points define a 'S' shape.
// Searches if the point 'pt' can be removed/moved in order to "smooth" the 'S' shape.
// Note: vectors 'vecPtP1' and 'vecPtP3' have to be normalized.
/*static*/ bool	VWPolygon2D::CheckForSShape(	const VWPoint2D& p0, const VWPoint2D& p1, const VWPoint2D& pt, const VWPoint2D& p3,
												const VWPoint2D& vecPtP1, const VWPoint2D& vecPtP3, double epsilon,
												VWPoint2D& outIntersPt, bool& outCanMove)
{
	const double			kPIOverTwo	= ( MathUtils::PI * 0.5 );		// 90 degrees.

	// init.
	bool					isSShape	= false;
	outCanMove							= false;

	VWPoint2D				vecP1P0		= ( p0 - p1 ).Normalize();

	// check if here we have 'S' shape.

	// get middle vectors at 'p1' and 'pt'.
	const VWPoint2D			midVecAtPt	= ( vecPtP1 + vecPtP3 ).Normalize();
	const VWPoint2D			midVecAtP1	= ( vecP1P0 - vecPtP1 ).Normalize();

	// get direction middle vectors at 'p1' and 'pt'.
	const VWPoint2D			perpDirAtPt	= ( vecPtP1.Perp() - vecPtP3.Perp() ).Normalize();
	const VWPoint2D			perpDirAtP1	= ( vecP1P0.Perp() + vecPtP1.Perp() ).Normalize();

	// get angles between middle vectors and direction middle vectors.
	double					ang1		= VWPoint2D::CalcAngleBetween( midVecAtPt, perpDirAtPt, true );
	double					ang2		= VWPoint2D::CalcAngleBetween( midVecAtP1, perpDirAtP1, true );

	// validate angles (expected to be 0 or PI).
	VWFC_ASSERT( MathUtils::Equalish( ang1, 0.0, epsilon ) || MathUtils::Equalish( ang1, ( MathUtils::PI ), epsilon ) );
	VWFC_ASSERT( MathUtils::Equalish( ang2, 0.0, epsilon ) || MathUtils::Equalish( ang2, ( MathUtils::PI ), epsilon ) );

	// find signs:
	// (if a middle vector has same direction as its direction middle vector then the sign is 1, otherwise (they have opposite directions) the sign is -1).
	double					sign1		= ( ang1 < kPIOverTwo ) ? 1.0 : -1.0;
	double					sign2		= ( ang2 < kPIOverTwo ) ? 1.0 : -1.0;

	if( MathUtils::Equalish( ( sign1 + sign2 ), 0.0, epsilon ) )		// we have 'S' shape (signs of the middle vectors are different).
	{
		isSShape						= true;

		// try to find intersection of segment ( pt, p3 ) and the ray ( p0, p1 )->.

		bool				parallel, onSeg1Pt1, onSeg1Pt2, onSeg1, onSeg2;
		VWLine2D::IntersectLines(	pt.x,	pt.y,	p3.x,	p3.y,		// segment ( pt, p3 ).
									p0.x,	p0.y,	p1.x,	p1.y,		// ray ( p0, p1 )->.
									outIntersPt.x,	outIntersPt.y,		// result: intersection.
									parallel,	onSeg1Pt1, onSeg1Pt2, onSeg1, onSeg2, epsilon );

		if ( ! parallel && onSeg1 )
		{
			if ( onSeg1Pt1 )			// 'pt' coincides with 'outIntersPt': means that 'vecP1P0' and 'vecPtP1' are collinear.
			{
				// this is a degenerate 'S' shape. do not consider it as an 'S' shape.
				isSShape				= false;
			}
			else if ( ! onSeg1Pt2 )		// 'p3' doesn't coincide with 'outIntersPt'.
			{
				// 'outIntersPt' lies within the segment (pt, p3).
				outCanMove				= true;
			}
		}
	}

	// result.
	return	( isSShape );
}

// having a vertex of 'this poly' lying on a line (segment) from the 'given poly', checks whether the 'given poly' intersects 'this poly' at that vertex or just touches it.
bool VWPolygon2D::IsPolyIntersectingPolyAt(size_t at, const VWPolygon2D& poly, size_t segIndex, double epsilon) const
{
	// init.
	bool						isInters	= false;

	// validate.
	VWFC_ASSERT( at < this->GetVertexCount() );				// bad input.

	const VWPoint2D&			thisPt		= this->GetVertexAt( at );

	// validate.
	VWFC_ASSERT( segIndex < poly.GetVertexCount() );		// bad input.

	// get the line.
	const VWPoint2D&			linePt1		= poly.GetVertexAt( segIndex );
	size_t						endLineInx;
	if ( poly.GetNextAppositePtIndex( segIndex, endLineInx, epsilon ) )
	{
		const VWPoint2D&		linePt2		= poly.GetVertexAt( endLineInx );

		// validate that the vertex lies on the line (segment).
		VWFC_ASSERT( VWLine2D( linePt1, linePt2 ).PtOnLine( thisPt, epsilon ) );	// not expected ! intersection vertex is not on line: bad input.

		bool					atLinePt1	= MathUtils::Equalish( thisPt, linePt1, epsilon );
		bool					atLinePt2	= MathUtils::Equalish( thisPt, linePt2, epsilon );

		if (	( ! atLinePt1 ) &&			// vertex doesn't coincide with the line point 1 and ...
				( ! atLinePt2 ) )			// ... vertex doesn't coincide with the line point 2.
		{
			VWPoint2D			prevPt, nextPt;

			// get prev and next 'apposite' poly points (not too close).
			if ( this->GetPrevAppositePt( at, prevPt, epsilon ) &&
				 this->GetNextAppositePt( at, nextPt, epsilon ) )	// can check: has prev and next.
			{
				bool			parallel, onLineSeg1, onLineSeg2, onSeg1Pt1, onSeg1Pt2;
				double			intersX, intersY;
				// check if neighbour (prev and next) vertices lie on different sides of the line.
				VWLine2D::IntersectLines(	prevPt.x,	prevPt.y,	nextPt.x,	nextPt.y,	// line 1 (prev, next).
											linePt1.x,	linePt1.y,	linePt2.x,	linePt2.y,	// line 2 (the input line).
											intersX,	intersY,
											parallel,	onSeg1Pt1, onSeg1Pt2, onLineSeg1, onLineSeg2, epsilon );

				isInters					= (	! parallel	&&					// not parallel lines.
												onLineSeg1	&&					// intersection point lies on line 1 (prev, next).
												! onSeg1Pt1	&& ! onSeg1Pt2 );	// intersection point doesn't coincide with prev or next.
			}
		}
		else								// vertex coincides with a line end.
		{
			// XXX Bobi:
			// means that the line doesn't intersects 'this poly'. However, we still could have intersection between polys.
			// this can happen when the intersection point coincides with vertices from the two polys.
			// in this case we can examine neighbour vertices and their position (in/out).
			// here are examined the medium points of the neighbour segments as otherwise will be missed ...
			// ... a case when neighbour vertices coincide with vertices from 'this poly'.

			if ( atLinePt1 )
			{
				// get the previous vertex before the poly line.
				VWPoint2D		prevPolyPt;
				if ( poly.GetPrevAppositePt( segIndex, prevPolyPt, epsilon ) )
				{
					// check the medium point of the previous segment and the medium of the poly line.
					bool		isIn1		= this->IsPtInPoly2D( ( prevPolyPt	+ linePt1 ) / 2,	epsilon );
					bool		isIn2		= this->IsPtInPoly2D( ( linePt2		+ linePt1 ) / 2,	epsilon );

					isInters				=  ( ( isIn1 || isIn2 ) && ! ( isIn1 && isIn2 ) );	// xor.
				}
			}
			else if ( atLinePt2 )
			{
				// get the next vertex after the poly line.
				VWPoint2D		nextPolyPt;
				if ( poly.GetNextAppositePt( endLineInx, nextPolyPt, epsilon ) )
				{
					// check the medium point of the next segment and the medium of the poly line.
					bool		isIn1		= this->IsPtInPoly2D( ( nextPolyPt	+ linePt2 ) / 2,	epsilon );
					bool		isIn2		= this->IsPtInPoly2D( ( linePt1		+ linePt2 ) / 2,	epsilon );

					isInters				=  ( ( isIn1 || isIn2 ) && ! ( isIn1 && isIn2 ) );	// xor.
				}
			}
		}
	}
	else
	{
		VWFC_ASSERT( false );				// no next point. bad input.
	}

	// result.
	return	( isInters );
}


// provided the input polygon has only arc and corner vertices, returns the polyginization of the segment with given index.
// When visiting a vertex in this case, it might return an arc as well as a line. Two boolean variables to indicate whether there is an arc and/or line returned.
// The last boolean recursion is used to limit the recursion to happen once, avoiding infinite loop.
bool VWPolygon2D::GetSegment(size_t segIndex, VWLine2D& outSegLine, VWArc2D& outSegArc, bool& outIsArc, bool& outIsLine, bool recursion) const
{
	bool				isFound		= false;

	size_t				vertCnt		= this->GetVertexCount();

	// validate.
	ASSERTN( kVStanev, ( segIndex < vertCnt ) );

	outIsArc						= false;
	outIsLine						= false;

	if ( segIndex < vertCnt &&
		 this->GetVertexVisible( segIndex ) )
	{
		EVertexType		vertType	= this->GetVertexType( segIndex );

		if ( vertType == eVertexType_Corner )
		{
			size_t		nextIndex	= ( segIndex < ( vertCnt - 1 ) ) ? ( segIndex + 1 ) : 0;

			EVertexType	nextType	= this->GetVertexType( nextIndex );

			const VWPoint2D&	ptBeg	= this->GetVertexAt( segIndex );
			if ( nextType == eVertexType_Corner )
			{
				const VWPoint2D&	ptEnd	= this->GetVertexAt( nextIndex );

				if ( ! MathUtils::Equalish( ptBeg, ptEnd, VWPoint2D::sEpsilon ) )	// not coincident.
				{
					outSegLine.SetLine( ptBeg, ptEnd );

					outIsArc		= false;
					outIsLine		= true;
					isFound			= true;
				}
			}
			else
			{
				VWLine2D	thisLine;
				VWArc2D		thisArc;
				bool		thisIsArc;
				bool		thisIsLine;
				if ( this->GetSegment( nextIndex, thisLine, thisArc, thisIsArc, thisIsLine, !recursion ) )
				{
					if ( thisIsArc &&  ! MathUtils::Equalish( ptBeg, thisArc.GetStartPt(), VWPoint2D::sEpsilon ) )
					{
					
						outSegLine.SetLine( ptBeg, thisArc.GetStartPt() );

						outIsArc		= false;
						outIsLine		= true;
						isFound			= true;
					}
				}
			}
		}
		else if	( vertType == eVertexType_Arc )
		{
			if ( this->GetArcFromArcPolyAt( segIndex, outSegArc ) )
			{
				outIsArc			= true;
				isFound				= true;
			}

			size_t		nextIndex	= ( segIndex < ( vertCnt - 1 ) ) ? ( segIndex + 1 ) : 0;

			EVertexType	nextType	= this->GetVertexType( nextIndex );

			if ( nextType == eVertexType_Arc && recursion )
			{
				VWLine2D	thisLine;
				VWArc2D		thisArc;
				bool		thisIsArc;
				bool		thisIsLine;
				if ( this->GetSegment( nextIndex, thisLine, thisArc, thisIsArc, thisIsLine, !recursion ) )
				{
					if ( thisIsArc && ! MathUtils::Equalish( outSegArc.GetEndPt(), thisArc.GetStartPt(), VWPoint2D::sEpsilon ) )
					{
						outSegLine.SetLine( outSegArc.GetEndPt(), thisArc.GetStartPt() );
						outIsLine		= true;
						isFound			= true;
					}
				}
			}
			else 
			{
				outIsLine = false; // avoid draw the line twice.
			}
		}
	}
	// this handles the situation when the last vertex is not visible but we still need draw the last line
	if ( segIndex == vertCnt - 1 && 
		this->GetVertexVisible (segIndex - 1) &&
		!this->GetVertexVisible( segIndex ) )
	{
		EVertexType	prevType	= this->GetVertexType( segIndex - 1 );
		VWLine2D	thisLine;
		VWArc2D		thisArc;
		bool		thisIsArc;
		bool		thisIsLine;
		if ( prevType == eVertexType_Arc && this->GetSegment( segIndex - 1, thisLine, thisArc, thisIsArc, thisIsLine, !recursion ))
		{
			if( thisIsArc && ! MathUtils::Equalish( thisArc.GetEndPt(), this->GetVertexAt(segIndex), VWPoint2D::sEpsilon ) )
			{
				outSegLine.SetLine(thisArc.GetEndPt(), this->GetVertexAt(segIndex));
				outIsArc = false;
				outIsLine = true;
				isFound = true;
			}
		}
	}

	return	( isFound );
}

// returns the arc for segment specified by (at-1, at (the arc vertex), at+1). works on polyline with only arc and corner vertices.

bool VWPolygon2D::GetArcFromArcPolyAt(size_t at, VWArc2D& outArc) const
{
	bool				isArc		= false;

	bool				isClosed	= this->IsClosed();
	size_t				vertCnt		= this->GetVertexCount();

	VWFC_ASSERT( isClosed || ( at > 0 && at < vertCnt - 1 ) );

	if ( ( isClosed || ( at > 0 && at < vertCnt - 1 ) ) &&
		 ( this->GetVertexType( at ) == eVertexType_Arc ) )
	{
		size_t			prexIndex;	// index of previous poly point.
		if ( isClosed )	prexIndex	= ( at > 0 ) ? ( at - 1 ) : ( vertCnt - 1 );
		else			prexIndex	= ( at - 1 );	// note that ( at > 0 ) in this case !

		size_t			nextIndex;	// index of next poly point.
		if ( isClosed )	nextIndex	= ( at + 1 ) % vertCnt;
		else			nextIndex	= ( at + 1 );	// note that ( at < vertCnt - 1 ) in this case !

		VWPoint2D		thisPt		= this->GetVertexAt( at );

		VWPoint2D		prevPt, nextPt;

		const VWPoint2D& prevVert	= this->GetVertexAt( prexIndex );

		EVertexType		prevType    = this->GetVertexType( prexIndex );

		if ( prevType == eVertexType_Arc )
		{
			prevPt		= ( prevVert + thisPt ) * 0.5;
		}
		else
		{
			ASSERTN( kVStanev, ( prevType == eVertexType_Corner ) );

			prevPt		= prevVert;
		}

		const VWPoint2D& nextVert	= this->GetVertexAt( nextIndex );

		EVertexType		nextType    = this->GetVertexType( nextIndex );

		if ( nextType == eVertexType_Arc )
		{
			nextPt		= ( nextVert + thisPt ) * 0.5;
		}
		else
		{
			// validate.
			ASSERTN( kVStanev, ( nextType == eVertexType_Corner ) );

			nextPt		= this->GetVertexAt( nextIndex );
		}

		VWPoint2D		dir1			= ( prevPt - thisPt );
		VWPoint2D		dir2			= ( nextPt - thisPt );         
		
		// dir1.Normalize() + dir2.Normalize() will return the actual direction of center point given two directions.
		VWPoint2D		centerDir	= ( dir1.Normalize() + dir2.Normalize() ).Normalize();
			
		double			theta			= dir1.CalcAngleTo( dir2 );
		double			tanHalfTheta	= tan( MathUtils::Deg2Rad( theta /2 ) );

		double			d1				= prevPt.DistanceTo( thisPt );
		double			d2				= thisPt.DistanceTo( nextPt );

		double			radius			= this->GetArcVertexRadius( at );

		if ( MathUtils::Equalish( radius, 0.0, VWPoint2D::sEpsilon ) )	// zero radius arc.
		{
			// recalculate the radius.
			VWPoint2D	pt			= prevPt;
			pt.RelativeCoords( thisPt, nextPt );
			double		angle		= pt.CalcAng360();
			double		dist        = prevPt.DistanceTo(thisPt);
			radius					= Abs( dist * tan( MathUtils::Deg2Rad( angle / 2 ) ) );
		}
	
		// need recalculate the radius because the default setting value might not be the real radius when drawing the polyline.
		radius =  min( radius, ( d1 > d2 ? d2 * tanHalfTheta : d1 * tanHalfTheta ));

		double			x				= radius / tanHalfTheta;

		if ( d1 > x )  // need update the new prevPt 
		{
			prevPt = thisPt + dir1.Normalize() * x; 
		}

		if( d2 > x )  // need update the new nextPt
		{
			nextPt = thisPt + dir2.Normalize() * x;
		}

		double			dist		= prevPt.DistanceTo( thisPt );

		double			hyp			= Sqrt( ( radius * radius ) + ( dist * dist ) );

		// get third point on arc.
		VWPoint2D		onArcPt		= thisPt + ( centerDir * (hyp - radius) );

		outArc.SetArc( prevPt, onArcPt, nextPt);

		isArc			= true;

	}

	return	( isArc );
}

VWPolygon2D::CPointWithPolarAngle::CPointWithPolarAngle( const VWPoint2D& pt, const VWPoint2D& angleAccordingTo, const VWPoint2D& ctr )
	: fThePoint( pt ) 
{
	double offset = Math::MathUtils::Deg2Rad( ( angleAccordingTo - ctr ).CalcAng180() );
	fTheAngle	  = Math::MathUtils::Deg2Rad( ( pt - ctr ).CalcAng180() ) - offset;

	if ( Math::MathUtils::Lesserish( fTheAngle, 0.0, VWPoint2D::sRawEpsilon ) )
	{
		fTheAngle += 2 * PI;
	}
}

bool VWPolygon2D::CPointWithPolarAngle::operator<( const VWPolygon2D::CPointWithPolarAngle& other ) const
{ 
	return Math::MathUtils::Lesserish( fTheAngle, other.fTheAngle, VWPoint2D::sEpsilonRadians ); 
}

/* Get the convex hull using Graham scan algorithm */
/*static*/ bool VWPolygon2D::GetBoundingPoly( const std::vector<VWPoint2D>& allPoints, VWPolygon2D& outPoly )
{
	bool result = false;

	std::vector<VWPoint2D> points;
	points = allPoints;

	if( !points.empty() )
	{
		auto& pt0 = points[0];
		size_t count = points.size();

		for ( size_t i = 1; i < count; i++ )
		{
			auto& currentPoint = points[ i ];
			if ( MathUtils::Lesserish( currentPoint.y, pt0.y, VWPoint2D::sRawEpsilon ) || ( MathUtils::Equalish( pt0.y, currentPoint.y, VWPoint2D::sRawEpsilon ) && ( MathUtils::Lesserish( currentPoint.x, pt0.x, VWPoint2D::sRawEpsilon ) ) ) )
			{
				std::swap( currentPoint, pt0 );
			}
		}

		double maxX = pt0.x , maxY = pt0.y, minX = pt0.x, minY = pt0.y;
		for ( size_t i = 1; i < count; i++ )
		{
			const auto& pt	= points[ i ];
			if( MathUtils::Greaterish( pt.x, maxX, VWPoint2D::sRawEpsilon ) ) 
			{
				maxX = pt.x;
			}
			else if( MathUtils::Lesserish( pt.x, minX, VWPoint2D::sRawEpsilon ) ) 
			{
				minX = pt.x;
			}

			if( MathUtils::Greaterish( pt.y, maxY, VWPoint2D::sRawEpsilon ) )
			{
				maxY = pt.y;
			}
			else if( MathUtils::Lesserish( pt.y, minY, VWPoint2D::sRawEpsilon ) )
			{
				minY = pt.y;
			}
		}
		VWPoint2D center( ( maxX + minX) / 2.0, ( maxY + minY ) / 2.0 );

		std::vector<CPointWithPolarAngle> arr;
		arr.push_back( CPointWithPolarAngle( pt0, pt0, center ) );

		for ( size_t i = 1; i < count; i++ )
		{
			arr.push_back( CPointWithPolarAngle( points[ i ], arr[0].GetPoint(), center ) );
		}

		std::sort( arr.begin(), arr.end() );
		arr.insert( arr.begin(), arr.back() );

		size_t outerPointsCount = 1;
		for ( size_t i = 2; i <= count; i++ )
		{
			while ( MathUtils::LEish( VWPoint2D::TriArea( arr[outerPointsCount-1].GetPoint(), arr[outerPointsCount].GetPoint(), arr[i].GetPoint() ), 0.0, VWPoint2D::sEpsilonCollinear  ) )
			{
				if ( outerPointsCount > 1)
				{
					outerPointsCount -= 1;
				}
				else if ( i == count )
				{
					break;
				}
				else
				{
					i += 1;
				}
			}
			outerPointsCount += 1;
			std::swap( arr[outerPointsCount], arr[i] );
		}

		outPoly.ClearVertices();
		for ( size_t i = 0; i < outerPointsCount; i++ )
		{
			outPoly.AddVertex( arr[i].GetPoint() );
		}
		result = outPoly.GetVertexCount();
	}

	return result;
}
