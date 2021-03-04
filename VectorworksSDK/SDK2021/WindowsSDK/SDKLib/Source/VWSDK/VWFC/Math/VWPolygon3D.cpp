//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;

VWPolygon3D::VWPolygon3D()
{
	fbIsClosed	= false;
}

VWPolygon3D::VWPolygon3D(std::initializer_list<VWPoint3D> src)
	: VWPolygon3D( TSTLPoints3DArray( src ) )
{
}

VWPolygon3D::VWPolygon3D(const VWPolygon3D& src)
{
	size_t	len	= src.farrVertices.size();
	for(size_t i=0; i<len; i++)
		farrVertices.push_back( src.farrVertices[ i ] );

	fbIsClosed	= src.fbIsClosed;
}

VWPolygon3D::VWPolygon3D(const VWPolygon2D& src, double z /*=0*/)
{
	size_t	len	= src.GetVertexCount();
	for(size_t i=0; i<len; i++)
		farrVertices.push_back( VWPoint3D( src.GetVertexAt(i), z ) );

	fbIsClosed	= src.IsClosed();
}

VWPolygon3D::VWPolygon3D(const TSTLPoints3DArray& src)
{
	size_t	len	= src.size();
	for(size_t i=0; i<len; i++)
		farrVertices.push_back( src[ i ] );

	fbIsClosed	= false;
}

 VWPolygon3D::VWPolygon3D(const TSTLPoints3DVWArray& src)
{
	size_t	len	= src.size();
	for(size_t i=0; i<len; i++)
		farrVertices.push_back( src[ i ] );

	fbIsClosed	= false;
}

VWPolygon3D::VWPolygon3D(IPolyDefPtr pPolygonDef)
{
	this->SetPolygon( pPolygonDef );
}

// create 3d polygon by three points (a plane)
VWPolygon3D::VWPolygon3D(const VWPoint3D& a, const VWPoint3D& b, const VWPoint3D& c)
{
	farrVertices.push_back( a );
	farrVertices.push_back( b );
	farrVertices.push_back( c );
	fbIsClosed		= true;
}

VWPolygon3D::VWPolygon3D(const VWTransformMatrix& plane)
{
	VWPoint3D	offset	= plane.GetOffset();
	farrVertices.push_back( offset );
	farrVertices.push_back( offset + plane.GetUVector() );
	farrVertices.push_back( offset + plane.GetVVector() );
	fbIsClosed		= true;
}

VWPolygon3D::~VWPolygon3D()
{
	farrVertices.clear();
}

bool VWPolygon3D::operator==(const VWPolygon3D& poly) const
{
	// init.
	bool		result	= false;

	size_t		cnt		= farrVertices.size();

	if ( cnt == poly.farrVertices.size() )
	{
		result	= true;
		for ( size_t i = 0 ; i < cnt ; ++ i )
		{
			if ( farrVertices[ i ] != poly.farrVertices[ i ] )
			{
				result	= false;
				break;	// difference found - stop.
			}
		}
	}

	// result.
	return	( result );
}

bool VWPolygon3D::operator!=(const VWPolygon3D& poly) const
{
	// result.
	return	( ! this->operator== ( poly ) );
}

VWPolygon3D& VWPolygon3D::operator=(const VWPolygon3D& src)
{
	farrVertices.clear();
	size_t	len	= src.farrVertices.size();
	for(size_t i=0; i<len; i++)
		farrVertices.push_back( src.farrVertices[ i ] );

	fbIsClosed	= src.fbIsClosed;
	return *this;
}

VWPolygon3D& VWPolygon3D::operator=(const VWPolygon2D& src)
{
	farrVertices.clear();
	size_t	len	= src.GetVertexCount();
	for(size_t i=0; i<len; i++)
		farrVertices.push_back( VWPoint3D( src.GetVertexAt(i), 0 ) );

	fbIsClosed	= src.IsClosed();
	return *this;
}

VWPolygon3D& VWPolygon3D::operator=(const TSTLPoints3DArray& src)
{
	farrVertices.clear();
	size_t	len	= src.size();
	for(size_t i=0; i<len; i++)
		farrVertices.push_back( src[ i ] );
	return *this;
}

VWPolygon3D& VWPolygon3D::operator=(const TSTLPoints3DVWArray& src)
{
	farrVertices.clear();
	size_t	len	= src.size();
	for(size_t i=0; i<len; i++)
		farrVertices.push_back( src[ i ] );
	return *this;
}

VWPolygon3D& VWPolygon3D::operator=(IPolyDefPtr pPolygonDef)
{
	this->ClearVertices();
	if ( pPolygonDef ) {
		Uint32	cnt		= 0;
		pPolygonDef->GetVertexCount( cnt );
		for(Uint32 i=0; i<cnt; i++) {
			WorldPt3	pt;

			pPolygonDef->GetVertexAt( i, pt );

			farrVertices.push_back( pt );
		}
		pPolygonDef->IsClosed( fbIsClosed );
	}
	return *this;
}

void VWPolygon3D::SetPolygon(const TSTLPoints3DArray& src)
{
	(*this) = src;
}

void VWPolygon3D::SetPolygon(const TSTLPoints3DVWArray& src)
{
	(*this) = src;
}

void VWPolygon3D::GetPolygon(TSTLPoints3DArray& out) const
{
	out.clear();
	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++)
		out.push_back( farrVertices[i] );
}

void VWPolygon3D::GetPolygon(TSTLPoints3DVWArray& out) const
{
	out.clear();
	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++)
		out.push_back( farrVertices[i] );
}

void VWPolygon3D::GetPolygon(IPolyDefPtr pPolygonDef) const
{
	if ( pPolygonDef ) {
		pPolygonDef->ClearVertices();
		size_t		len		= farrVertices.size();
		for(size_t i=0; i<len; i++) {
			const VWPoint3D&	pt = farrVertices[ i ];

			pPolygonDef->AddVertex( pt );
		}
		pPolygonDef->SetClosed( fbIsClosed );
	}
}

// create 3d polygon by three points (a plane)
void VWPolygon3D::SetPolygon(const VWPoint3D& a, const VWPoint3D& b, const VWPoint3D& c)
{
	farrVertices.clear();
	farrVertices.push_back( a );
	farrVertices.push_back( b );
	farrVertices.push_back( c );
	fbIsClosed		= true;
}

void VWPolygon3D::SetPolygon(const VWTransformMatrix& plane)
{
	VWPoint3D	offset	= plane.GetOffset();
	farrVertices.clear();
	farrVertices.push_back( offset );
	farrVertices.push_back( offset + plane.GetUVector() );
	farrVertices.push_back( offset + plane.GetVVector() );
	fbIsClosed		= true;
}

void VWPolygon3D::SetPolygon(IPolyDefPtr pPolygonDef)
{
	(*this) = pPolygonDef;
}

void VWPolygon3D::ClearVertices()
{
	farrVertices.clear();
}

void VWPolygon3D::AddVertex(double x, double y, double z)
{
	farrVertices.push_back( VWPoint3D( x, y, z ) );
}

void VWPolygon3D::AddVertex(const VWPoint3D& pt)
{
	farrVertices.push_back( pt );
}

void VWPolygon3D::AddVertex(const VWPolygon3D& poly)
{
	size_t	cnt	= poly.farrVertices.size();
	for(size_t i=0; i<cnt; i++) {
		farrVertices.push_back( poly.farrVertices[ i ] );
	}
}

void VWPolygon3D::AddVertex(const TSTLPoints3DArray& arrPts, bool reverse)
{
	for(size_t i=0, cnt=arrPts.size(); i<cnt; ++i)
	{
		size_t index = reverse ? (cnt - i - 1): i;
		farrVertices.push_back( arrPts[ index ] );
	}
}

void VWPolygon3D::InsertVertex(size_t at, double x, double y, double z)
{
	farrVertices.insert( farrVertices.begin() + at, VWPoint3D( x, y, z ) );
}

void VWPolygon3D::InsertVertex(size_t at, const VWPoint3D& pt)
{
	farrVertices.insert( farrVertices.begin() + at, pt );
}

void VWPolygon3D::InsertVertex(size_t at, const VWPolygon3D& poly)
{
	size_t	cnt	= poly.farrVertices.size();
	for(size_t i=0; i<cnt; i++) {
		farrVertices.insert( farrVertices.begin() + at, poly.farrVertices[ cnt - i - 1 ] );
	}
}

void VWPolygon3D::ClearVertex(size_t at)
{
	farrVertices.erase( farrVertices.begin() + at );
}

size_t VWPolygon3D::GetVertexCount() const
{
	return farrVertices.size();
}

bool VWPolygon3D::IsEmpty() const
{
	return farrVertices.size() <= 1;
}

VWPoint3D& VWPolygon3D::operator[](size_t at)
{
	return this->GetVertexAt( at );
}

const VWPoint3D& VWPolygon3D::operator[](size_t at) const
{
	return this->GetVertexAt( at );
}

const VWPoint3D& VWPolygon3D::GetVertexAt(size_t at, bool bLoopVerts /*=false*/) const
{
	if ( bLoopVerts ) {
		// loop the vertex indeces inside the array
		VWFC_ASSERT( farrVertices.size() > 0 );
		at		= at % farrVertices.size();
	}
	else {
		VWFC_ASSERT( at < farrVertices.size() );
	}
	return farrVertices[ at ];
}

VWPoint3D& VWPolygon3D::GetVertexAt(size_t at, bool bLoopVerts /*=false*/)
{
	if ( bLoopVerts ) {
		// loop the vertex indeces inside the array
		VWFC_ASSERT( farrVertices.size() > 0 );
		at		= at % farrVertices.size();
	}
	else {
		VWFC_ASSERT( at < farrVertices.size() );
	}
	return farrVertices[ at ];
}

void VWPolygon3D::SetVertexAt(size_t at, const VWPoint3D& pt, bool bLoopVerts /*=false*/)
{
	if ( bLoopVerts ) {
		// loop the vertex indeces inside the array
		VWFC_ASSERT( farrVertices.size() > 0 );
		at		= at % farrVertices.size();
	}
	else {
		VWFC_ASSERT( at < farrVertices.size() );
	}
	farrVertices[ at ]	= pt;
}

VWLine3D VWPolygon3D::GetLineAt(size_t at) const
{
	VWFC_ASSERT( at < farrVertices.size() );
	size_t	next	= at + 1;
	if ( next >= farrVertices.size() )
		next	= 0;

	return VWLine3D( farrVertices[ at ], farrVertices[ next ] );
}

bool VWPolygon3D::IsClosed() const
{
	return fbIsClosed;
}

void VWPolygon3D::SetClosed(bool bClosed)
{
	fbIsClosed	= bClosed;
}

// return true if the passed polygon has more than 3 different vertices
bool VWPolygon3D::IsValidPolygon(double dEpsilon) const
{
	size_t	len	= farrVertices.size();
	if ( len < 3 )
		return false;

	size_t		count	= 1;
	VWPoint3D	pt		= farrVertices[ 0 ];
	for(size_t i=1; i<len; i++)
	{
		double_gs	dist	= ( pt - farrVertices[ i ] ).Magnitude();
		if ( dist > dEpsilon )
		{
			count++;
			if ( count >= 3 )
				return true;
		}

		pt			= farrVertices[ i ];
	}

	return count >= 3;
}

// check if all polygon vertices lie on a 3D plane.
bool VWPolygon3D::IsFlatPolygon(double dEpsilon) const
{
	bool						isFlat	= false;

	// get the plane equation.
	double						A, B, C, D;
	if ( this->GetPlaneEquation( A, B, C, D ) )
	{
		isFlat							= true;

		size_t					len		= this->GetVertexCount();
		for ( size_t i = 0 ; i < len ; ++ i )
		{
			const VWPoint3D&	pt		= this->GetVertexAt( i );
			// get distance to the plane.
			double				dist	= Abs( ( A*pt.x + B*pt.y + C*pt.z + D ) / sqrt( A*A + B*B + C*C ) );

			if ( ! MathUtils::Equalish( dist, 0.0, dEpsilon ) )
			{
				isFlat					= false;
				break;
			}
		}
	}

	// result.
	return	isFlat;
}

// removed all same points in the polygon
void VWPolygon3D::CleanUpPolygon(double dEpsilon)
{
	VWPoint3D					lastPt;
	TSTLPoints3DArray::iterator	it		= farrVertices.begin();
	while( it != farrVertices.end() )
	{
		if ( it == farrVertices.begin() ) 
		{
			lastPt		= *it;
			it++;
		}
		else
		{
			double_gs	dist	= ( lastPt - (*it) ).Magnitude();
			if ( dist < dEpsilon )
			{
				// remove the unnecessary point
				farrVertices.erase( it );
				// start all over
				it		= farrVertices.begin();
			}
			else {
				lastPt		= *it;
				it++;
			}
		}
	}
}

// gets a polygon where all same ('duplicate') points are removed.
void VWPolygon3D::GetCleanedUpPolygon(VWPolygon3D& outCleanPoly, double epsilon) const
{
	outCleanPoly.ClearVertices();	// init.

	size_t			len			= this->GetVertexCount();

	VWPoint3D		lastPt;

	if ( len > 0 )	// has points.
	{
		// get squared epsilon.
		double		sqrEps		= sqr( epsilon );

		for ( size_t i = 0 ; i < len ; ++ i )
		{
			const VWPoint3D&	currPt	= farrVertices[ i ];

			if ( ( i == 0 ) ||
				 ( lastPt.DistanceSquaredTo( currPt ) > sqrEps ) )
			{
				outCleanPoly.AddVertex( currPt );
				lastPt			= currPt;
			}
		}
	}
}

// this function works as follows depending on 'doClosenessCheck':
// ( doClosenessCheck == false ) - clean up all polygon vertices which are collinear with their neighbors.
// ( doClosenessCheck == true  ) - clean up all polygon vertices which are collinear with their neighbors and are too close to their neighbors.
void VWPolygon3D::CleanUp_FeaturePreserving(bool doClosenessCheck, double epsCollinear, double epsCloseness)
{
	size_t		vertCnt			= this->GetVertexCount();

	VWFC_ASSERT( vertCnt > 1 );	// empty poly. check !

	if ( vertCnt > 2 )			// has at least 3 vertices (could clean it up).
	{
		// prepare squared epsilons.
		double	sqrEpsCollinear	= sqr( epsCollinear );
		double	sqrEpsCloseness	= sqr( epsCloseness );

		bool	isClosed		= this->IsClosed();

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

			const VWPoint3D&	thisPt		= this->GetVertexAt( thisInx );
			const VWPoint3D&	prevPt		= this->GetVertexAt( prevInx );
			const VWPoint3D&	nextPt		= this->GetVertexAt( nextInx );

			bool				doRemove	= false;

			// get cross product: normal vector to plane defined by the two normalized vectors.
			VWPoint3D			normalVec	= ( ( prevPt - thisPt ).Normalize() ).Cross( ( nextPt - thisPt ).Normalize() );

			// collinearity check.
			if ( MathUtils::Equalish( normalVec.MagnitudeSquared(), 0.0, sqrEpsCollinear ) )
			{
				if ( doClosenessCheck )
				{
					if ( ( thisPt.DistanceSquaredTo( prevPt ) < sqrEpsCloseness ) ||	// distance to previous vertex is too small.
						 ( thisPt.DistanceSquaredTo( nextPt ) < sqrEpsCloseness ) )		// distance to next vertex is too small.
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
	}
}

void VWPolygon3D::GetPlanarPolygon(VWPolygon2D& out) const
{
	out.ClearVertices();

	TSTLPoints3DArray::const_iterator	it		= farrVertices.begin();
	while( it != farrVertices.end() ) {
		out.AddVertex( VWPoint2D( it->x, it->y ) );
		++it;
	}

	out.SetClosed( fbIsClosed );
}

// given a 3D polygon, segments it (subdivides it) into segments of 'segmentation length' by introducing ...
// ... new vertices while preserving the original ones (thus, there might be produced shorter segments as well).
// note: shape of the original 3D polygon will be fully preserved.
void VWPolygon3D::GetSegmentedPolygon(VWPolygon3D& outPolygon3D, double segmentationLength) const
{
	// init.
	outPolygon3D.ClearVertices();

	size_t				ptsCnt		= this->GetVertexCount();

	if ( ( ptsCnt > 1 ) &&									// valid polygon and ...
		 Double1_GT_Double2( segmentationLength, 0.0 ) )	// ... valid segmentation length.
	{
		size_t			procCnt		= ptsCnt;

		// check whether it is closed polygon.
		if ( fbIsClosed )			// closed.
		{
			const VWPoint3D&		firstPt		= this->GetVertexAt( 0 );
			const VWPoint3D&		lastPt		= this->GetVertexAt( ptsCnt - 1 );

			if ( ! MathUtils::Equalish( firstPt, lastPt, VWPoint3D::sEpsilon ) )	// not coinciding.
			{
				++ procCnt;			// increase (to cover the last polygon segment).
			}
		}

		VWPoint3D		ptToAdd;
		bool			addPt, addIntrs;
		double			lineLen;
		size_t			inx;

		TSTLPoints3DArray			resOrderedPts;

		for ( size_t it = 0 ; it < procCnt ; ++ it )
		{
			inx			= ( it < ptsCnt ? it : 0 );
			const VWPoint3D&		pt			= this->GetVertexAt( inx );

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
				// prepare the last 'non-examined' line vector.
				VWPoint3D			lineVec		= ( pt - ptToAdd );

				// get the squared length of the line vector.
				lineLen				= lineVec.Magnitude();

				// get normalized vector.
				lineVec				/= lineLen;

				if ( lineLen > ( segmentationLength + VWPoint3D::sEpsilon ) )	// new point(s) can be inserted.
				{
					addIntrs		= true;		// add first intersection.

					ptToAdd			= ( ptToAdd + ( lineVec * segmentationLength ) );
				}
				else	// no new point(s) can be inserted.
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
			outPolygon3D			= resOrderedPts;		// form the result polygon.

			outPolygon3D.SetClosed( fbIsClosed );
		}
	}
	else
	{
		outPolygon3D	= *this;
	}
}

void VWPolygon3D::GetXBounds(double& outMinX, double& outMaxX) const
{
	bool								init	= true;
	TSTLPoints3DArray::const_iterator	it		= farrVertices.begin();
	while( it != farrVertices.end() ) {
		if ( init ) {
			init		= false;
			outMinX		= it->x;
			outMaxX		= it->x;
		}
		else {
			if ( it->x < outMinX )	outMinX		= it->x;
			if ( it->x > outMaxX )	outMaxX		= it->x;
		}
		++it;
	}
}

void VWPolygon3D::GetYBounds(double& outMinY, double& outMaxY) const
{
	bool								init	= true;
	TSTLPoints3DArray::const_iterator	it		= farrVertices.begin();
	while( it != farrVertices.end() ) {
		if ( init ) {
			init		= false;
			outMinY		= it->y;
			outMaxY		= it->y;
		}
		else {
			if ( it->y < outMinY )	outMinY		= it->y;
			if ( it->y > outMaxY )	outMaxY		= it->y;
		}
		++it;
	}
}

void VWPolygon3D::GetZBounds(double& outMinZ, double& outMaxZ) const
{
	bool								init	= true;
	TSTLPoints3DArray::const_iterator	it		= farrVertices.begin();
	while( it != farrVertices.end() ) {
		if ( init ) {
			init		= false;
			outMinZ		= it->z;
			outMaxZ		= it->z;
		}
		else {
			if ( it->z < outMinZ )	outMinZ		= it->z;
			if ( it->z > outMaxZ )	outMaxZ		= it->z;
		}
		++it;
	}
}

// gets bounds cube.
VWCube VWPolygon3D::GetBoundsCube() const
{
	VWCube	boundsCube;

	TSTLPoints3DArray::const_iterator	it	= farrVertices.begin();
	while ( it != farrVertices.end() )
	{
		boundsCube.Unite( *it );
		++ it;
	}

	// result.
	return	( boundsCube );
}

// gets the bounds rectangle of the planar (projected) polygon.
VWRectangle2D VWPolygon3D::GetPlanarBoundsRect() const
{
	// init.
	double		minX		= 0.0;
	double		maxX		= 0.0;
	double		minY		= 0.0;
	double		maxY		= 0.0;

	size_t		len			= farrVertices.size();

	if ( len > 0 )			// has vertices.
	{
		const VWPoint3D&	pt	= farrVertices[ 0 ];

		minX				= pt.x;
		maxX				= pt.x;
		minY				= pt.y;
		maxY				= pt.y;

		for ( size_t i = 1 ; i < len ; ++ i )	// loop.
		{
			const VWPoint3D&	pt	= farrVertices[ i ];

			minX			= min( minX, pt.x );
			maxX			= max( maxX, pt.x );
			minY			= min( minY, pt.y );
			maxY			= max( maxY, pt.y );
		}
	}

	// result.
	return VWRectangle2D( minX, maxX, maxY, minY );
}

//////////////////////////////////////////////////////////////////////
// mathematics
//////////////////////////////////////////////////////////////////////

// find index of next 'apposite' polygon point (not too close).
bool VWPolygon3D::GetNextAppositePtIndex(size_t inPtIndex, size_t& outNextPtIndex, double dEpsilon) const
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
	const VWPoint3D&	pt			= this->GetVertexAt( inPtIndex );

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
		
		const VWPoint3D&	currPt	= this->GetVertexAt( currIndex );

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
bool VWPolygon3D::GetNextAppositePt(size_t inPtIndex, VWPoint3D& outNextPt, double dEpsilon) const
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
bool VWPolygon3D::GetPrevAppositePtIndex(size_t inPtIndex, size_t& outPrevPtIndex, double dEpsilon) const
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
	const VWPoint3D&	pt			= this->GetVertexAt( inPtIndex );

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
		
		const VWPoint3D&	currPt	= this->GetVertexAt( currIndex );

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
bool VWPolygon3D::GetPrevAppositePt(size_t inPtIndex, VWPoint3D& outPrevPt, double dEpsilon) const
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
// their corresponding polygon points define a reasonable plane.
bool VWPolygon3D::GetPlanePtIndices(size_t& ptIndex0, size_t& ptIndex1, size_t& ptIndex2) const
{
	// init.
	ptIndex0 = ptIndex1 = ptIndex2	= 0;

	// check if polygon has at least 3 vertices.
	size_t				len			= this->GetVertexCount();
	if ( len < 3 )
	{
		return false;
	}

	// get first apposite plane vertex.
	ptIndex0						= 0;
	const VWPoint3D&	pt0			= this->GetVertexAt( ptIndex0 );

	bool				hasPlane	= false;
	// get second apposite plane vertex.
	ptIndex1						= 1;
	VWPoint3D			pt1;
	while ( ptIndex1 < len )
	{
		pt1							= this->GetVertexAt( ptIndex1 );
		if ( ! MathUtils::Equalish( pt0, pt1, VWPoint3D::sEpsilon ) )	// not too close.
		{
			hasPlane				= true;
			break;
		}
		++ ptIndex1;
	}

	// get third apposite plane vertex.
	if ( hasPlane )
	{
		hasPlane					= false;

		ptIndex2					= ( ptIndex1 + 1 );
		while ( ptIndex2 < len )
		{
			const VWPoint3D& pt2	= this->GetVertexAt( ptIndex2 );
			if ( ! VWPoint3D::ArePointsCollinear( pt0, pt1, pt2, VWPoint3D::sEpsilonCollinear ) )	// not collinear.
			{
				hasPlane			= true;
				break;
			}
			++ ptIndex2;
		}
	}
	
	// result.
	return	hasPlane;
}

// find the first 3 'apposite' polygon points (not too close and not collinear).
// they define a reasonable plane.
bool VWPolygon3D::GetThreePlanePoints(VWPoint3D& pt0, VWPoint3D& pt1, VWPoint3D& pt2) const
{
	// init.
	size_t	ptIndex0, ptIndex1, ptIndex2;
	// find indices of the first 3 'apposite' polygon points (not too close and not collinear).
	bool	hasPlane	= this->GetPlanePtIndices( ptIndex0, ptIndex1, ptIndex2 );

	if ( hasPlane )
	{
		// get the corresponding polygon points.
		pt0				= this->GetVertexAt( ptIndex0 );
		pt1				= this->GetVertexAt( ptIndex1 );
		pt2				= this->GetVertexAt( ptIndex2 );
	}

	// result.
	return	hasPlane;
}

// return the plane equation of the plane made by the first 3 'apposite' vertices (not too close and not collinear).
// A*x + B*y + C*z + D
bool VWPolygon3D::GetPlaneEquation(double& A, double& B, double& C, double& D) const
{
	size_t	planePtIndex0, planePtIndex1, planePtIndex2;
	// find indices of the first 3 'apposite' polygon points (not too close and not collinear).
	bool	hasPlane	= this->GetPlanePtIndices( planePtIndex0, planePtIndex1, planePtIndex2 );

	if ( hasPlane )
	{
		// get the plane equation.
		hasPlane		= this->GetPlaneEquation( planePtIndex0, planePtIndex1, planePtIndex2, A, B, C, D );
	}

	// result.
	return	hasPlane;
}

// return the plane equation of the plane made by the specified 3 vertices.
// A*x + B*y + C*z + D
bool VWPolygon3D::GetPlaneEquation(size_t ptIndex0, size_t ptIndex1, size_t ptIndex2, double& A, double& B, double& C, double& D) const
{
	size_t		len		= this->GetVertexCount();
	if ( len < 3 )
	{
		return false;
	}

	VWFC_ASSERT( ptIndex0 < len && ptIndex1 < len && ptIndex2 < len );	// validate indices.

	VWPoint3D	p0		= farrVertices[ ptIndex0 ];
	VWPoint3D	p1		= farrVertices[ ptIndex1 ];
	VWPoint3D	p2		= farrVertices[ ptIndex2 ];

	VWPoint3D	cross( (p1-p0) * (p2-p0) );
	cross.Normalize();
	A		= cross.x;
	B		= cross.y;
	C		= cross.z;
	D		= - (A * p0.x + B * p0.y + C * p0.z);

	return true;
}

// set the object to a plane by given equation A*x + B*y + C*z + D = 0
void VWPolygon3D::SetPlaneEquation(double A, double B, double C, double D)
{
	VWPoint3D a( 0, 0 );
	VWPoint3D b( 100, 0 );
	VWPoint3D c( 0, 100 );

	a.z = - (A * a.x + B * a.y + C * a.z + D) / sqrt(A*A + B*B + C*C);
	b.z = - (A * b.x + B * b.y + C * b.z + D) / sqrt(A*A + B*B + C*C);
	c.z = - (A * c.x + B * c.y + C * c.z + D) / sqrt(A*A + B*B + C*C);

	*this = VWPolygon3D( a, b, c );
}

// return transformation which describes this plane
VWTransformMatrix VWPolygon3D::GetTransformMatrix() const
{
	VWTransformMatrix	matrix;
	size_t		len	= farrVertices.size();
	if ( len < 3 )
		return matrix;

	size_t		cnt		= farrVertices.size();
	VWPoint3D	p0		= farrVertices[ 0 ];
	size_t		i		= 1;
	if ( i >= cnt ) 	return matrix;

	while( i < cnt && p0 == farrVertices[ i ] ) {
		i++;
	}
	if ( i >= cnt ) 	return matrix;

	VWPoint3D	p1		= farrVertices[ i ];
	i++;
	while( i < cnt && ( p1 == farrVertices[ i ] || ((p1 - p0) * (farrVertices[ i ] - p0)) == VWPoint3D(0,0,0) ) ) {
		i++;
	}
	if ( i >= cnt ) 	return matrix;

	VWPoint3D	p2		= farrVertices[ i ];

	VWPoint3D	uVec	= p1 - p0;
	VWPoint3D	vVec	= p2 - p0;
	VWPoint3D	wVec	= uVec * vVec;
	vVec				= wVec * uVec;

	uVec.Normalize();
	vVec.Normalize();
	wVec.Normalize();
	matrix.SetMatrix( uVec, vVec, wVec, p0 );

	return matrix;
}

// perpendicular distance to the plane made by the first 3 points
// the distance is reversed if the polygon is CCW
double VWPolygon3D::GetDistance(const VWPoint3D& pt) const
{
	double	A, B, C, D;
	if ( !this->GetPlaneEquation( A, B, C, D ) )
		return 0.0;

	return - (A * pt.x + B * pt.y + C * pt.z + D) / sqrt(A*A + B*B + C*C);
}

// distance to the "reasonable" plane defined by certain 3 poly vertices.
// different thiad of the poly vertices could make a different plane, so use the "closest" plane here.
// the vertical distance -- what z for the point to be on the plane.
double VWPolygon3D::GetVerticalDistance(const VWPoint3D& pt) const
{
	double			reply			= 0.0;

	// search for a correct plane made by the closest edge and one other poly vertex.
	size_t			len				= this->GetVertexCount();
	bool			isPlaneFound	= false;
	double			A, B, C, D;
	if ( len > 2 )	// do we have at least 3 point to make a plane?
	{
		// get closest edge index of the planar poly.
		VWPolygon2D	projPoly;
		this->GetPlanarPolygon( projPoly );

		double		dist;
		Sint32			segIndex		= -1;
		projPoly.GetClosestPtOnPoly( pt, dist, segIndex );
		VWFC_ASSERT( segIndex != -1 );	// must not happen!

		size_t		planePtIndex0	= segIndex; 
		size_t		planePtIndex1	= ( segIndex + 1 ) % len;

		// get start vertex.
		size_t		startPtIndex	= ( segIndex + 2 ) % len;
		if ( ( segIndex - 1 ) >= 0 )
		{
			startPtIndex			= ( segIndex - 1 ); 
		}

		size_t		iterPtIndex		= startPtIndex;
		do
		{
			// get the corresponding plane equation.
			if ( iterPtIndex != planePtIndex0 &&
				 iterPtIndex != planePtIndex1 &&
				 this->GetPlaneEquation( planePtIndex0, planePtIndex1, iterPtIndex, A, B, C, D ) )
			{
				if ( ! MathUtils::Equalish( C, 0, VWPoint3D::sEpsilon ) )
				{
					isPlaneFound	= true;
					break;
				}
			}
			// next.
			iterPtIndex				= ( iterPtIndex + 1 ) % len;
		}
		while ( iterPtIndex != startPtIndex );
	}

	if ( isPlaneFound )
	{
		reply						= - ( A * pt.x + B * pt.y + C * pt.z + D ) / C;	// C is not zero for sure.
	}
	else
	{
		// this can happen if count of vertices is less than 3 or if all poly vertices lie on a plane perpendicular to Oxy.
		// in this case: vertical distance can be found only if the point lies on the poly projection.
		if ( len > 1 )
		{
			double	minVertDist		= 0.0;
			bool	isDistFound		= false;
			for ( size_t i = 0 ; i < ( len - 1 ) ; ++ i )
			{
				const VWPoint3D&	linePt0	= this->GetVertexAt( i );
				const VWPoint3D&	linePt1	= this->GetVertexAt( i + 1 );
				if ( VWLine2D::PtOnLine( pt, linePt0, linePt1, VWPoint2D::sEpsilon ) )
				{
					VWLine3D		line3D( linePt0, linePt1 );
					double currDist	= line3D.GetVerticalDistance( pt );

					if ( ( ! isDistFound ) || ( currDist < minVertDist ) )
					{
						minVertDist	= currDist;
						isDistFound	= true;
					}
				}
			}

			if ( isDistFound )
			{
				reply				= minVertDist;
			}
		}
		else
		{
			// not implemented.
		}
	}

	return reply;
}

// normal of the plane made by the first 3 points
VWPoint3D VWPolygon3D::Normal() const
{
	VWPoint3D	normal;

	double	A, B, C, D;
	if ( this->GetPlaneEquation( A, B, C, D ) )
	{
		normal.SetPoint( A, B, C );
	}

	return normal;
}

// average normal to the "average" plane which best fits to arbitrary polygon (Newell's Method).
VWPoint3D VWPolygon3D::AveragedNormal() const
{
	VWPoint3D		avgNormalVec;	// init: a zero vector.

	size_t			vertCnt		= this->GetVertexCount();
	if ( vertCnt > 2 )			// poly has at least 3 points which can define a plane.
	{
		size_t		cntMinusOne	= ( vertCnt - 1 );

		double		normX		= 0.0;
		double		normY		= 0.0;
		double		normZ		= 0.0;

		for ( size_t i = 0 ; i < vertCnt ; ++ i )
		{
			size_t	next		= ( i < cntMinusOne ? i + 1 : 0 );

			normX				+= ( farrVertices[ i ].y - farrVertices[ next ].y ) *	// ( Yi - Yi+1 ) *
								   ( farrVertices[ i ].z + farrVertices[ next ].z );	// ( Zi + Zi+1
			
			normY				+= ( farrVertices[ i ].z - farrVertices[ next ].z ) *	// ( Zi - Zi+1 ) *
								   ( farrVertices[ i ].x + farrVertices[ next ].x );	// ( Xi + Xi+1 )

			normZ				+= ( farrVertices[ i ].x - farrVertices[ next ].x ) *	// ( Xi - Xi+1 ) *
								   ( farrVertices[ i ].y + farrVertices[ next ].y );	// ( Yi + Yi+1 )
		}

		avgNormalVec.SetPoint( normX, normY, normZ );
		avgNormalVec.Normalize();
	}

	// result.
	return	( avgNormalVec );
}

// get geometry center of the polygon
VWPoint3D VWPolygon3D::GetCenter() const
{
	VWPoint3D	centerPt;

	size_t		polyLen		= farrVertices.size();
	for(size_t i=0; i<polyLen; i++) {
		const VWPoint3D&		pt		= farrVertices[ i ];
		if ( i == 0 )
			centerPt		= pt;
		else
			centerPt		+= pt;
	}

	centerPt	/= (double)polyLen;

	return centerPt;
}

// get a point at a given distance from the beginning
bool VWPolygon3D::GetPtOnPoly( double offset, VWPoint3D& outPt ) const
{
	bool		result		= false;
	double		length		= 0;
	size_t		vertsCnt	= this->GetVertexCount();

	for ( size_t i = 1; i < vertsCnt; ++i )
	{
		const VWPoint3D&	prevPt		= this->GetVertexAt( i - 1 );
		const VWPoint3D&	thisPt		= this->GetVertexAt( i );

		double				newLen		= length + prevPt.DistanceTo( thisPt );

		if ( MathUtils::GEish( newLen, offset, VWPoint3D::sEpsilon ) )
		{
			double		dist			= offset - length;
			VWPoint3D	n				= ( thisPt - prevPt ).Normalize();
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

// get a point at a given distance from the beginning
VWPoint3D VWPolygon3D::GetClosestPtOnPoly3d( const VWPoint3D& pt, double& outDist, Sint32& outOnSegIndex ) const
{
	VWPoint3D						closestPt;

	size_t							vertCnt		= this->GetVertexCount();
	// validate.
	VWFC_ASSERT( vertCnt > 0 );	// poly is empty! incorrect.

	if ( vertCnt < 2 )	// single point poly.
	{
		closestPt								= this->GetVertexAt( 0 );
		outDist									= pt.DistanceTo( closestPt );
		outOnSegIndex							= 0;
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
			double					currDist;	// for min distance to this poly segment.
			VWPoint3D				currPt;		// for closest point on this poly segment.

			bool					isOnSeg		= true;

			// this index.
			size_t					thisIndex	= i;

			// index of next poly point.
			size_t					nextIndex;
			if ( isClosed )			nextIndex	= ( thisIndex + 1 ) % procCnt;
			else					nextIndex	= ( thisIndex + 1 );


			const VWLine3D&		polyLine	= this->GetLineAt( thisIndex );

			// get the closest point on line.
			const VWPoint3D&	projPt		= polyLine.PtPerpLine( pt );
			if ( polyLine.PtOnLine( projPt, VWPoint3D::sEpsilon ) )	// projection is on line.
			{
				currDist					= pt.DistanceTo( projPt );
				currPt						= projPt;
			}
			else
			{
				isOnSeg						= false;
			}

			// if projection is not on segment.
			if ( ! isOnSeg )
			{
				// get segment ends.
				const VWPoint3D&	segPt0	= this->GetVertexAt( thisIndex );
				const VWPoint3D&	segPt1	= this->GetVertexAt( nextIndex );

				double			distToPt0	= pt.DistanceTo( segPt0 );
				double			distToPt1	= pt.DistanceTo( segPt1 );
				if ( distToPt0 < distToPt1 )
				{
					currDist				= distToPt0;
					currPt					= segPt0;
				}
				else
				{
					currDist				= distToPt1;
					currPt					= segPt1;
				}
			}

			if ( ( thisIndex == 0 ) || ( currDist < outDist ) )
			{
				// the following lines will be reached at least once (see that vertsCnt is > 1)
				outDist						= currDist;
				closestPt					= currPt;
				outOnSegIndex				= (Sint32)thisIndex;

				if ( MathUtils::Equalish( outDist, 0.0, VWPoint3D::sEpsilon ) )	// stop if point lies on the poly segment.
				{
					break;
				}
			}
		}
	}

	return	closestPt;
}

// area3D_Polygon(): computes the area of a 3D planar polygon
//    Return: the (float) area of the polygon
//			positive if polygon is CCW -- negative if CW
double  VWPolygon3D::GetArea() const
{
	size_t		n		= farrVertices.size();
	if ( n < 2 )
		return 0;

#define GET_PTx(i)	((i<n) ? farrVertices[i].x : ( (i==n) ? farrVertices[0].x : ( /*i==n+1*/ farrVertices[1].x ) ))
#define GET_PTy(i)	((i<n) ? farrVertices[i].y : ( (i==n) ? farrVertices[0].y : ( /*i==n+1*/ farrVertices[1].y ) ))
#define GET_PTz(i)	((i<n) ? farrVertices[i].z : ( (i==n) ? farrVertices[0].z : ( /*i==n+1*/ farrVertices[1].z ) ))

	// unit normal vector of the polygon's plane
	VWPoint3D	N		= this->Normal();

	// if normal vector is zero, this means that all polygon vertices are near to collinear and ...
	// ... no meaningful plane equation can be found. the area is zero in this case.
	if ( MathUtils::Equalish( N.Magnitude(), 0.0, VWPoint3D::sEpsilon ) ) {
		return 0.0;
	}

	double		area	= 0;
	double		an, ax, ay, az;  // abs value of normal and its coords
	Sint32			coord;           // coord to ignore: 1=x, 2=y, 3=z
	size_t		i, j, k;         // loop indices

	// select largest abs coordinate to ignore for projection
	ax		= (N.x>0 ? N.x : -N.x);		// abs x-coord
	ay		= (N.y>0 ? N.y : -N.y);		// abs y-coord
	az		= (N.z>0 ? N.z : -N.z);		// abs z-coord

	coord	= 3;					// ignore z-coord
	if (ax > ay) {
		if (ax > az) coord = 1;		// ignore x-coord
	}
	else if (ay > az) coord = 2;	// ignore y-coord

	// compute area of the 2D projection
	for (i=1, j=2, k=0; i<=n; i++, j++, k++) {
		switch (coord) {
		case 1:
			area += ( GET_PTy(i) * ( GET_PTz(j) - GET_PTz(k) ) );
			continue;
		case 2:
			area += ( GET_PTx(i) * ( GET_PTz(j) - GET_PTz(k) ) );
			continue;
		case 3:
			area += ( GET_PTx(i) * ( GET_PTy(j) - GET_PTy(k) ) );
			continue;
		}
	}

	// scale to get area before projection
	an = sqrt( ax*ax + ay*ay + az*az);  // length of normal vector
	switch (coord) {
	case 1:
		area *= ( an / ( 2 * ax ) );
		break;
	case 2:
		area *= ( an / ( 2 * ay ) );
		break;
	case 3:
		area *= ( an / ( 2 * az ) );
	}

#undef GET_PTx
#undef GET_PTy
#undef GET_PTz

	return area;
}

double VWPolygon3D::GetPerim() const
{
	double	result	= 0;

 	size_t	len		= farrVertices.size();
	for(size_t i=1; i<len; i++)
	{
		VWPoint3D		temp		= farrVertices[ i ];

		result		+= temp.DistanceTo( farrVertices[ i - 1 ] );
	}

	if ( len > 1 && fbIsClosed ) 
	{
		result		+= farrVertices[ 0 ].DistanceTo( farrVertices[ len - 1 ] );
	}

	return result;
}

// check if polygon is equalish to this.
// note: to check the equality regardless the direction use reverse check.
bool VWPolygon3D::EqualishTo(const VWPolygon3D& poly, bool doReverseCheck/*=false*/) const
{
	// init.
	bool		areEqual	= false;

	size_t		len			= this->GetVertexCount();

	if ( ( len > 0 ) &&		// at least one point and ...
		 ( len == poly.GetVertexCount() ) )		// ... same length.
	{
		// search for coincidence between first point in 'this' polygon and some point in 'poly'.

		const VWPoint3D&	thisPt0		= this->GetVertexAt( 0 );

		size_t	polyBegInx	= -1;

		for ( size_t i = 0 ; i < len ; ++ i )
		{
			const VWPoint3D& polyPt		= poly.GetVertexAt( i );

			if ( MathUtils::Equalish( thisPt0, polyPt, VWPoint3D::sEpsilon ) )
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

				// check positions.
				if ( ! MathUtils::Equalish( this->GetVertexAt( i ), poly.GetVertexAt( ptInx ), VWPoint3D::sEpsilon ) )
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

					// check positions.
					if ( ! MathUtils::Equalish( this->GetVertexAt( i ), poly.GetVertexAt( ptInx ), VWPoint3D::sEpsilon ) )
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

// reverse the order of the points (if CW to CCW or CCW to CW)
void VWPolygon3D::ReversePoints()
{
 	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len / 2; i++)
	{
		VWPoint3D		temp		= farrVertices[ i ];
		farrVertices[ i ]			= farrVertices[ len-i-1 ];
		farrVertices[ len-i-1 ]		= temp;
	}
}

// determine if the polygon is Clock Wise oriented
bool VWPolygon3D::IsClockWise() const
{
	double	area	= this->GetArea();
	return area <= 0;
}

// intersect the plane made by the first 3 points with a specified line
//  return false if line is parallel to plane
bool VWPolygon3D::Intersect(const VWLine3D& line, VWPoint3D& outIntersPt, double dEpsilon) const
{
	VWPoint3D	b	= line.GetStart();
	VWPoint3D	m	= (line.GetEnd() - b).Normalize();

	return this->Intersect( b, m, outIntersPt, dEpsilon );
}

// intersect the plane made by the first 3 points with a specified line given by points and direction
//  return false if line is parallel to plane
bool VWPolygon3D::Intersect(const VWPoint3D& startPt, const VWPoint3D& dir, VWPoint3D& outIntersPt, double dEpsilon) const
{
	double	A, B, C, D;
	if ( !this->GetPlaneEquation( A, B, C, D ) )
		return false;

	double		f0	= A * startPt.x + B * startPt.y + C * startPt.z + D;
	double		f1	= A * -dir.x + B * -dir.y + C * -dir.z;
	if ( f1 < -dEpsilon || f1 > dEpsilon )
	{
		double	t	= f0 / f1;

		outIntersPt	= startPt + dir * t;
		return true;
	}
	else
	{
		return false;
	}
}

// intersect this plane made by the first 3 points
// with the specified plane (first 3 points)
//  return false is planes are parallel
bool VWPolygon3D::Intersect(const VWPolygon3D& plane, VWLine3D& outIntersLine, double dEpsilon) const
{
	VWPoint3D	n0	= - this->Normal();
	VWPoint3D	n1	= - plane.Normal();

	double		n00	= n0 % n0;
	double		n01	= n0 % n1;
	double		n11	= n1 % n1;
	double		det	= n00*n11 - n01*n01;

	if ( Abs(det) < dEpsilon )
		return false;
	else
	{
		double	A1, B1, C1, D1;
		if ( !this->GetPlaneEquation( A1, B1, C1, D1 ) )
			return false;
		double	A2, B2, C2, D2;
		if ( !plane.GetPlaneEquation( A2, B2, C2, D2 ) )
			return false;

		double		inv_det	= 1.0 / det;
		double		c0		= (n11 * D1 - n01 * D2) * inv_det;
		double		c1		= (n00 * D2 - n01 * D1) * inv_det;

		VWPoint3D	m		= n0 * n1;
		VWPoint3D	b		= n0 * c0 + n1 * c1;

		outIntersLine.SetLine( b, b + m );

		return true;
	}
}

// determines if a point is in the area of the projected polygon (the 2D projection)
bool VWPolygon3D::IsPtInProjPoly2D(const VWPoint2D& pt, double dEpsilon) const
{
	return this->IsPtInProjPoly2D( pt.x, pt.y, dEpsilon );
}

bool VWPolygon3D::IsPtInProjPoly2D(double ptX, double ptY, double dEpsilon) const
{
	// not using epsilon -- but we should
	dEpsilon;

	ptrdiff_t	cn			= 0;    // the crossing number counter

	size_t		polyPtCnt	= farrVertices.size();
	// loop through all edges of the polygon
	for (size_t i=0; i<polyPtCnt; i++) {    // edge from V[i] to V[i+1]
		const VWPoint3D&	pt		= farrVertices[i];
		const VWPoint3D&	nextPt	= i+1 < polyPtCnt ? farrVertices[i+1] : farrVertices[0];

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

bool VWPolygon3D::IsPtInOrOnProjPoly2D(double ptX, double ptY, double dEpsilon) const
{
	// not using epsilon -- but we should
	dEpsilon;

	VWPoint2D	inPt( ptX, ptY );

	bool		inPoly		= false;
	bool		onPoly		= false;

	ptrdiff_t	cn			= 0;    // the crossing number counter

	size_t		polyPtCnt	= farrVertices.size();
	// loop through all edges of the polygon
	for (size_t i=0; i<polyPtCnt; i++) {    // edge from V[i] to V[i+1]
		const VWPoint3D&	pt		= farrVertices[i];
		const VWPoint3D&	nextPt	= i+1 < polyPtCnt ? farrVertices[i+1] : farrVertices[0];

		onPoly	= VWLine2D::PtOnLine( inPt, pt, nextPt, dEpsilon );
		// if it is on poly break -- we have 'on poly' and dont have 'in poly'
		if ( onPoly ) 
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
	if ( ! onPoly ) {
		inPoly	= ( cn & 1 ) ? true : false;    // 0 if even (out), and 1 if odd (in)
	}
	else {
		inPoly	= false;
	}

	return onPoly || inPoly;
}

void VWPolygon3D::PointsTransform(const VWTransformMatrix& matrix)
{
 	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++) {
		VWPoint3D&	pt		= farrVertices[i];
		matrix.TransformPoint( pt );
	}
}

void VWPolygon3D::InversePointsTransform(const VWTransformMatrix& matrix)
{
 	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++) {
		VWPoint3D&	pt		= farrVertices[i];
		pt					= matrix.InversePointTransform( pt );
	}
}

void VWPolygon3D::MovePoints(double dx, double dy, double dz)
{
 	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++) {
		VWPoint3D&	pt		= farrVertices[i];
		pt.x				+= dx;
		pt.y				+= dy;
		pt.z				+= dz;
	}
}

void VWPolygon3D::MovePoints(const VWPoint3D& amount)
{
 	size_t	len	= farrVertices.size();
	for(size_t i=0; i<len; i++) {
		VWPoint3D&	pt		= farrVertices[i];
		pt					+= amount;
	}
}

// checks whether the two polygons have common volume.
/*static*/ bool VWPolygon3D::DoPolygonsHaveCommonCubeVolume(const VWPolygon3D& poly0, const VWPolygon3D& poly1, double coordEpsilon)
{
	// init.
	bool		hasCommVol	= false;

	size_t		poly0Cnt	= poly0.GetVertexCount();
	size_t		poly1Cnt	= poly1.GetVertexCount();

	if ( poly0Cnt > 0 && poly1Cnt > 0 )	// non-empty polygons.
	{
		// find the cubes of the two polygons.
		VWCube	poly0Cube, poly1Cube;

		// find the cube of the first polygon.
		for ( size_t i = 0 ; i < poly0Cnt ; ++ i )
		{
			poly0Cube.Unite( poly0.GetVertexAt( i ) );
		}

		// find the cube of the second polygon.
		for ( size_t i = 0 ; i < poly1Cnt ; ++ i )
		{
			poly1Cube.Unite( poly1.GetVertexAt( i ) );
		}

		// check polygons' cubes for common volume.
		hasCommVol			= ( ! poly0Cube.IsOutside( poly1Cube, coordEpsilon ) );
	}

	// result.
	return	( hasCommVol );
}

// checks whether the two triangles have common volume.
/*static*/ bool VWPolygon3D::DoTrianglesHaveCommonCubeVolume(const VWPoint3D& tri0Pt0, const VWPoint3D& tri0Pt1, const VWPoint3D& tri0Pt2,
															 const VWPoint3D& tri1Pt0, const VWPoint3D& tri1Pt1, const VWPoint3D& tri1Pt2,
															 double coordEpsilon)
{
	// find the cubes of the two triangles.
	VWCube				tri0Cube, tri1Cube;

	// prepare an arrays for the loop.
	const VWPoint3D*	tri0[ 3 ]	= { ( & tri0Pt0 ), ( & tri0Pt1 ), ( & tri0Pt2 ) };
	const VWPoint3D*	tri1[ 3 ]	= { ( & tri1Pt0 ), ( & tri1Pt1 ), ( & tri1Pt2 ) };

	for ( size_t i = 0 ; i < 3 ; ++ i )
	{
		tri0Cube.Unite( * tri0[ i ] );
		tri1Cube.Unite( * tri1[ i ] );
	}

	// result: check triangles' cubes for common volume.
	return	( ! tri0Cube.IsOutside( tri1Cube, coordEpsilon ) );
}

// checks whether two 3D triangles intersect.
// returns the intersection line/point.
/*static*/ bool VWPolygon3D::DoTrianglesIntersect(const VWPoint3D& tri0Pt0, const VWPoint3D& tri0Pt1, const VWPoint3D& tri0Pt2,
												  const VWPoint3D& tri1Pt0, const VWPoint3D& tri1Pt1, const VWPoint3D& tri1Pt2,
												  VWLine3D& outIntersLine, double coordEpsilon, double radEpsilon)
{
	// init.
	bool						hasInters	= false;

	// first, checks whether the two triangles have common volume.
	if ( VWPolygon3D::DoTrianglesHaveCommonCubeVolume( tri0Pt0, tri0Pt1, tri0Pt2, tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon ) )
	{
		// checks for degenerate triangles.

		// check if first triangle is degenerate.
		bool					isNonDegen	= true;

		VWLine3D				intersLine;

		if ( MathUtils::Equalish( tri0Pt0, tri0Pt1, coordEpsilon ) &&
			 MathUtils::Equalish( tri0Pt1, tri0Pt2, coordEpsilon ) )	// the three points of the first triangle coincide.
		{
			// first one is a point-like degenerate triangle (all its points coincide).
			if ( tri0Pt0.IsOnTriangle( tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon, radEpsilon ) )
			{
				hasInters					= true;
				outIntersLine.SetLine( tri0Pt0, tri0Pt0 );	// degenerate point-like line.
			}

			isNonDegen						= false;		// mark as degenerate.
		}
		else
		{
			// check if the first triangle is line-like (collinear points).
			// Note: don't normalize the vectors as we don't expect them to differ greatly in length. such cases will be caught in the standard case.
			VWPoint3D			crossP		= ( ( tri0Pt0 - tri0Pt1 ) * ( tri0Pt2 - tri0Pt1 ) );	// cross product.
			if ( MathUtils::Equalish( crossP.MagnitudeSquared(), 0.0, VWPoint3D::sSqrEpsilon ) )	// degenerate.
			{
				// first one is a line-like degenerate triangle (collinear points).
				VWLine3D		tri0Edge	= VWPoint3D::GetTriLongestEdge( tri0Pt0, tri0Pt1, tri0Pt2 );

				bool			lineOnTriPlane;
				if ( tri0Edge.IntersectTriangle( tri1Pt0, tri1Pt1, tri1Pt2, intersLine, lineOnTriPlane, coordEpsilon, radEpsilon ) )
				{
					hasInters				= true;
					outIntersLine			= intersLine;
				}

				isNonDegen					= false;	// mark as degenerate.
			}
		}

		if ( isNonDegen )					// the first triangle is not degenerate.
		{
			// first one is not a degenerate triangle.

			// check if second triangle is degenerate.

			if ( MathUtils::Equalish( tri1Pt0, tri1Pt1, coordEpsilon ) &&
				 MathUtils::Equalish( tri1Pt1, tri1Pt2, coordEpsilon ) )	// the three points of the second triangle coincide.
			{
				// second one is a point-like degenerate triangle (all its points coincide).
				// check whether it is inside the non-degenerate first triangle.
				if ( tri1Pt0.IsOnTriangle( tri0Pt0, tri0Pt1, tri0Pt2, coordEpsilon, radEpsilon ) )
				{
					hasInters				= true;
					outIntersLine.SetLine( tri1Pt0, tri1Pt0 );	// degenerate point-like line.
				}

				isNonDegen					= false;			// mark as degenerate.
			}
			else
			{
				// check if the second triangle is line-like (collinear points).
				// Note: don't normalize the vectors as we don't expect them to differ greatly in length. such cases will be caught in the standard case.
				VWPoint3D		crossP		= ( ( tri1Pt0 - tri1Pt1 ) * ( tri1Pt2 - tri1Pt1 ) );		// cross product.
				if ( MathUtils::Equalish( crossP.MagnitudeSquared(), 0.0, VWPoint3D::sSqrEpsilon ) )	// degenerate.
				{
					// second one is a line-like degenerate triangle (collinear points).
					// check whether it intersects the non-degenerate first triangle.
					VWLine3D	tri1Edge	= VWPoint3D::GetTriLongestEdge( tri1Pt0, tri1Pt1, tri1Pt2 );

					bool		lineOnTriPlane;
					if ( tri1Edge.IntersectTriangle( tri0Pt0, tri0Pt1, tri0Pt2, intersLine, lineOnTriPlane, coordEpsilon, radEpsilon ) )
					{
						hasInters			= true;
						outIntersLine		= intersLine;
					}

					isNonDegen				= false;	// mark as degenerate.
				}
			}

			if ( isNonDegen )				// both triangles are not degenerate.
			{
				// both triangles are not degenerate.
				// check if the two non-degenerate triangles intersect.

				// check if the edges of first triangle intersect the plane of the second triangle.

				// collect intersections.
				VWPoint3D					intersPts[ 2 ];
				size_t						intersCnt	= 0;

				// prepare an array for the loop.
				const VWPoint3D*			tri0[ 4 ]	= { ( &tri0Pt0 ), ( &tri0Pt1 ), ( &tri0Pt2 ), ( &tri0Pt0 ) };

				bool						lineOnPlane;
				VWLine3D					tri0Edge;

				VWPoint3D					plane1Vec0	= ( tri1Pt1 - tri1Pt0 );
				VWPoint3D					plane1Vec1	= ( tri1Pt2 - tri1Pt0 );

				bool						allOnPlane	= true;

				// loop.
				for ( size_t i = 0 ; ( i < 3 ) && ( allOnPlane || intersCnt < 2 ) ; ++ i )
				{
					const VWPoint3D&		pt0			= ( * tri0[ i ] );
					const VWPoint3D&		pt1			= ( * tri0[ i + 1 ] );

					tri0Edge.SetLine( pt0, pt1 );		// get i-th edge of first triangle.

					if ( tri0Edge.IntersectPlane( tri1Pt0, plane1Vec0, plane1Vec1, intersLine, lineOnPlane, coordEpsilon, radEpsilon ) )
					{
						if ( ! lineOnPlane )			// single point intersection.
						{
							// mark that there is an edge of first triangle which doesn't lie on the plane defined by second triangle.
							if ( allOnPlane )			// the first edge of triangle which intersects the plane and not lying on it.
							{
								// XXX Bobi:
								// validation: we don't expect the 3rd triangle's edge to be the first one which intersects the plane and not lying on it.
								// if there is an intersection of this kind, this means that exactly two triangle's edges intersect the plane and not lying on it.
								// however, this could happen due to the epsilon check when one of the triangle's vertices just "touches" the plane (check if this is the case).
								ASSERTN( kVStanev, ( i < 2 ) );	// not expected. check !

								allOnPlane				= false;
							}

							intersPts[ intersCnt ]		= intersLine.GetStart();
							++ intersCnt;				// increase the count of intersections.
						}
					}
				}

				if ( allOnPlane )						// special case: all edges of first triangle lie on the plane defined by second triangle.
				{
					// loop: check for all edges of first triangle if intersect the second triangle.
					for ( size_t i = 0 ; i < 3 ; ++ i )
					{
						const VWPoint3D&	pt0			= ( * tri0[ i ] );
						const VWPoint3D&	pt1			= ( * tri0[ i + 1 ] );

						tri0Edge.SetLine( pt0, pt1 );		// get i-th edge of first triangle.

						if ( tri0Edge.IntersectTriangleOnSamePlane( tri1Pt0, tri1Pt1, tri1Pt2, intersLine, coordEpsilon, radEpsilon ) )
						{
							hasInters					= true;
							outIntersLine				= intersLine;

							// Note: in this case it is possible to have more that one intersection lines - return only the first occurred intersection.
							break;						// stop.
						}
					}
				}
				else									// the two triangles don't lie on same plane.
				{
					// XXX Bobi:
					// validation: this could happen due to the epsilon check when one of the triangle's vertices just "touches" the plane (check if this is the case).
					ASSERTN( kVStanev, ( intersCnt == 2 ) );	// check !

					// check intersections.
					if ( intersCnt > 1 )				// two intersections.
					{
						// means that the first triangle intersects the second triangle's plane and ...
						// ... we have the intersection points.

						const VWPoint3D&	intersPt0	= intersPts[ 0 ];
						const VWPoint3D&	intersPt1	= intersPts[ 1 ];

						// check the intersection points.
						if ( MathUtils::Equalish( intersPt0, intersPt1, coordEpsilon ) )	// same.
						{
							// means that two edges from the first triangle intersect the plane of the second triangle in same intersection point.
							// check whether this intersection point is inside the second triangle.
							if ( intersPt0.IsOnTriangle( tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon, radEpsilon ) )
							{
								hasInters				= true;
								outIntersLine.SetLine( intersPt0, intersPt0 );	// degenerate point-like line.
							}
						}
						else							// different.
						{
							// means that there are two different intersection points.

							// prepare the line formed by the two intersection points.
							tri0Edge.SetLine( intersPt0, intersPt1 );

							// check for intersection between this line and the non-degenerate triangle.
							if ( tri0Edge.IntersectTriangleOnSamePlane( tri1Pt0, tri1Pt1, tri1Pt2, intersLine, coordEpsilon, radEpsilon ) )
							{
								hasInters				= true;
								outIntersLine			= intersLine;
							}
						}
					}
					else if ( intersCnt == 1 )			// single intersection (suspicious case).
					{
						const VWPoint3D&	intersPt	= intersPts[ 0 ];

						// check whether this intersection point is inside the second triangle.
						if ( intersPt.IsOnTriangle( tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon, radEpsilon ) )
						{
							hasInters					= true;
							outIntersLine.SetLine( intersPt, intersPt );	// degenerate point-like line.
						}
					}
				}
			}
		}
	}

	// result.
    return ( hasInters );
}

// checks whether two 3D triangles intersect.
// doesn't return the intersection line/point (faster function).
/*static*/ bool VWPolygon3D::DoTrianglesIntersect(const VWPoint3D& tri0Pt0, const VWPoint3D& tri0Pt1, const VWPoint3D& tri0Pt2,
												  const VWPoint3D& tri1Pt0, const VWPoint3D& tri1Pt1, const VWPoint3D& tri1Pt2,
												  double coordEpsilon, double radEpsilon)
{
	// init.
	bool						hasInters	= false;

	// first, checks whether the two triangles have common volume.
	if ( VWPolygon3D::DoTrianglesHaveCommonCubeVolume( tri0Pt0, tri0Pt1, tri0Pt2, tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon ) )
	{
		// checks for degenerate triangles.

		// check if first triangle is degenerate.
		bool					isNonDegen	= true;

		if ( MathUtils::Equalish( tri0Pt0, tri0Pt1, coordEpsilon ) &&
			 MathUtils::Equalish( tri0Pt1, tri0Pt2, coordEpsilon ) )	// the three points of the first triangle coincide.
		{
			// first one is a point-like degenerate triangle (all its points coincide).
			hasInters						= tri0Pt0.IsOnTriangle( tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon, radEpsilon );

			isNonDegen						= false;		// mark as degenerate.
		}
		else
		{
			// check if the first triangle is line-like (collinear points).
			// Note: don't normalize the vectors as we don't expect them to differ greatly in length. such cases will be caught in the standard case.
			VWPoint3D			crossP		= ( ( tri0Pt0 - tri0Pt1 ) * ( tri0Pt2 - tri0Pt1 ) );	// cross product.
			if ( MathUtils::Equalish( crossP.MagnitudeSquared(), 0.0, VWPoint3D::sSqrEpsilon ) )	// degenerate.
			{
				// first one is a line-like degenerate triangle (collinear points).
				VWLine3D		tri0Edge	= VWPoint3D::GetTriLongestEdge( tri0Pt0, tri0Pt1, tri0Pt2 );

				hasInters					= tri0Edge.IntersectTriangle( tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon, radEpsilon );

				isNonDegen					= false;			// mark as degenerate.
			}
		}

		if ( isNonDegen )					// the first triangle is not degenerate.
		{
			// first one is not a degenerate triangle.

			// check if second triangle is degenerate.

			if ( MathUtils::Equalish( tri1Pt0, tri1Pt1, coordEpsilon ) &&
				 MathUtils::Equalish( tri1Pt1, tri1Pt2, coordEpsilon ) )	// the three points of the second triangle coincide.
			{
				// second one is a point-like degenerate triangle (all its points coincide).
				// check whether it is inside the non-degenerate first triangle.
				hasInters					= tri1Pt0.IsOnTriangle( tri0Pt0, tri0Pt1, tri0Pt2, coordEpsilon, radEpsilon );

				isNonDegen					= false;			// mark as degenerate.
			}
			else
			{
				// check if the second triangle is line-like (collinear points).
				// Note: don't normalize the vectors as we don't expect them to differ greatly in length. such cases will be caught in the standard case.
				VWPoint3D		crossP		= ( ( tri1Pt0 - tri1Pt1 ) * ( tri1Pt2 - tri1Pt1 ) );		// cross product.
				if ( MathUtils::Equalish( crossP.MagnitudeSquared(), 0.0, VWPoint3D::sSqrEpsilon ) )	// degenerate.
				{
					// second one is a line-like degenerate triangle (collinear points).
					// check whether it intersects the non-degenerate first triangle.
					VWLine3D	tri1Edge	= VWPoint3D::GetTriLongestEdge( tri1Pt0, tri1Pt1, tri1Pt2 );

					hasInters				= tri1Edge.IntersectTriangle( tri0Pt0, tri0Pt1, tri0Pt2, coordEpsilon, radEpsilon );

					isNonDegen				= false;	// mark as degenerate.
				}
			}

			if ( isNonDegen )				// both triangles are not degenerate.
			{
				// both triangles are not degenerate.
				// check if the two non-degenerate triangles intersect.

				// check if the edges of first triangle intersect the plane of the second triangle.

				// collect intersections.
				VWPoint3D					intersPts[ 2 ];
				size_t						intersCnt	= 0;

				// prepare an array for the loop.
				const VWPoint3D*			tri0[ 4 ]	= { ( &tri0Pt0 ), ( &tri0Pt1 ), ( &tri0Pt2 ), ( &tri0Pt0 ) };

				VWLine3D					intersLine;
				bool						lineOnPlane;
				VWLine3D					tri0Edge;

				VWPoint3D					plane1Vec0	= ( tri1Pt1 - tri1Pt0 );
				VWPoint3D					plane1Vec1	= ( tri1Pt2 - tri1Pt0 );

				bool						allOnPlane	= true;

				// loop.
				for ( size_t i = 0 ; ( i < 3 ) && ( allOnPlane || intersCnt < 2 ) ; ++ i )
				{
					const VWPoint3D&		pt0			= ( * tri0[ i ] );
					const VWPoint3D&		pt1			= ( * tri0[ i + 1 ] );

					tri0Edge.SetLine( pt0, pt1 );		// get i-th edge of first triangle.

					if ( tri0Edge.IntersectPlane( tri1Pt0, plane1Vec0, plane1Vec1, intersLine, lineOnPlane, coordEpsilon, radEpsilon ) )
					{
						if ( ! lineOnPlane )			// single point intersection.
						{
							// mark that there is an edge of first triangle which doesn't lie on the plane defined by second triangle.
							if ( allOnPlane )			// the first edge of triangle which intersects the plane and not lying on it.
							{
								// XXX Bobi:
								// validation: we don't expect the 3rd triangle's edge to be the first one which intersects the plane and not lying on it.
								// if there is an intersection of this kind, this means that exactly two triangle's edges intersect the plane and not lying on it.
								// however, this could happen due to the epsilon check when one of the triangle's vertices just "touches" the plane (check if this is the case).
								ASSERTN( kVStanev, ( i < 2 ) );	// not expected. check !

								allOnPlane				= false;
							}

							intersPts[ intersCnt ]		= intersLine.GetStart();
							++ intersCnt;				// increase the count of intersections.
						}
					}
				}

				if ( allOnPlane )						// special case: all edges of first triangle lie on the plane defined by second triangle.
				{
					// loop: check for all edges of first triangle if intersect the second triangle.
					for ( size_t i = 0 ; i < 3 ; ++ i )
					{
						const VWPoint3D&	pt0			= ( * tri0[ i ] );
						const VWPoint3D&	pt1			= ( * tri0[ i + 1 ] );

						tri0Edge.SetLine( pt0, pt1 );		// get i-th edge of first triangle.

						if ( tri0Edge.IntersectTriangleOnSamePlane( tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon, radEpsilon ) )
						{
							hasInters					= true;

							// Note: in this case it is possible to have more that one intersection lines - return only the first occurred intersection.
							break;						// stop.
						}
					}
				}
				else									// the two triangles don't lie on same plane.
				{
					// XXX Bobi:
					// validation: this could happen due to the epsilon check when one of the triangle's vertices just "touches" the plane (check if this is the case).
					ASSERTN( kVStanev, ( intersCnt == 2 ) );	// check !

					// check intersections.
					if ( intersCnt > 1 )				// two intersections.
					{
						// means that the first triangle intersects the second triangle's plane and ...
						// ... we have the intersection points.

						const VWPoint3D&	intersPt0	= intersPts[ 0 ];
						const VWPoint3D&	intersPt1	= intersPts[ 1 ];

						// check the intersection points.
						if ( MathUtils::Equalish( intersPt0, intersPt1, coordEpsilon ) )	// same.
						{
							// means that two edges from the first triangle intersect the plane of the second triangle in same intersection point.
							// check whether this intersection point is inside the second triangle.
							hasInters					= intersPt0.IsOnTriangle( tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon, radEpsilon );
						}
						else							// different.
						{
							// means that there are two different intersection points.

							// prepare the line formed by the two intersection points.
							tri0Edge.SetLine( intersPt0, intersPt1 );

							// check for intersection between this line and the non-degenerate triangle.
							hasInters					= tri0Edge.IntersectTriangleOnSamePlane( tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon, radEpsilon );
						}
					}
					else if ( intersCnt == 1 )			// single intersection (suspicious case).
					{
						const VWPoint3D&	intersPt	= intersPts[ 0 ];

						// check whether this intersection point is inside the second triangle.
						hasInters						= intersPt.IsOnTriangle( tri1Pt0, tri1Pt1, tri1Pt2, coordEpsilon, radEpsilon );
					}
				}
			}
		}
	}

	// result.
    return ( hasInters );
}