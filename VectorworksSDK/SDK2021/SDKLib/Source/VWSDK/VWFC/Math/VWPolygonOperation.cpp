//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

// engine from http://www.xs4all.nl/~kholwerd/download/download.html

#include "kbool/booleng.h"


using namespace VWFC::Math;


static void ArmBoolEng(Bool_Engine* pBoolEngine);
static void SetPolygonA(Bool_Engine* pBoolEngine, const VWPolygon2D& poly);
static void SetPolygonB(Bool_Engine* pBoolEngine, const VWPolygon2D& poly);
static void GetResult(Bool_Engine* pBoolEngine, TSTLPolygons2DArray& out);
static void GetResult(Bool_Engine* pBoolEngine, VWPolygon2D& out);

////////////////////////////////////////////////////////////////////////
// VWPolygonOperation
////////////////////////////////////////////////////////////////////////
VWPolygonOperation::VWPolygonOperation(const VWPolygon2D& clipPoly)
: m_clipPoly( clipPoly )
{
	m_pSTLCutResultArray		= NULL;
	
	m_pBooleanEngine	= SDK_NEW Bool_Engine;
	::ArmBoolEng( (Bool_Engine*) m_pBooleanEngine );
}

VWPolygonOperation::~VWPolygonOperation()
{
	if(m_pBooleanEngine)
		delete (Bool_Engine*) m_pBooleanEngine;
}

bool VWPolygonOperation::BooleanOR(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons)
{
	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
		return false;

	bool	ok		= true;

	try
	{
		((Bool_Engine*) m_pBooleanEngine)->Activate();
		::SetPolygonA( (Bool_Engine*) m_pBooleanEngine, polygon );
		::SetPolygonB( (Bool_Engine*) m_pBooleanEngine, m_clipPoly );
		((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_OR );
		::GetResult( (Bool_Engine*) m_pBooleanEngine, resultPolygons );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

// unites polygon with the specified clipper polygon. result are closed polygons representing the union (or two polygons if there is no common are).
// also returns whether polygon and clipper have common area.
bool VWPolygonOperation::BooleanOR(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons, bool& outNoCommonArea, bool& outInnerClipper)
{
	bool						isOK				= true;
	outNoCommonArea									= true;
	outInnerClipper									= false;
	resultPolygons.clear();

	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
	{
		VWFC_ASSERT( false );						// bad input !
		isOK										= false;
	}

	if ( isOK )										// good input polygons.
	{
		// XXX Bobi:
		// instead of 'VWPolygonOperation::AreOverlapping' use the following function which is faster.
		// check if the polygon operation is necessary.
		bool					performOperation	= false;

		if ( VWPolygon2D::ArePolygonsIntersecting( m_clipPoly, polygon, outNoCommonArea, VWPoint2D::sRawEpsilon ) )
		{
			performOperation						= true;
		}
		else
		{
			// 3 possible cases here:
			// - 'polygon' is inside the 'm_clipPoly'.
			// - 'm_clipPoly' is inside 'polygon' (perform the boolean operation in this case !).
			// - no common areas.

			if ( ! outNoCommonArea )												// might have common area. check!
			{
				// as it is still not sure that 'polygon' and 'm_clipPoly' overlap (they might not have common area), ...
				// ... make this additional check here.
				outNoCommonArea						= true;

				size_t					polyPtCnt	= polygon.GetVertexCount();
				size_t					clipPtCnt	= m_clipPoly.GetVertexCount();
				if ( polyPtCnt > 2 && clipPtCnt > 2 )								// both polygons are correct.
				{
					size_t				maxPtCnt	= ( polyPtCnt > clipPtCnt ) ? polyPtCnt : clipPtCnt;
					for ( size_t i = 0 ; i < maxPtCnt ; ++ i )
					{
						if ( i < polyPtCnt )
						{
							const VWPoint2D&	vp	= polygon.GetVertexAt( i );
							if ( m_clipPoly.IsPtInPoly2D( vp.x, vp.y, VWPoint2D::sEpsilon ) )	// 'polygon' is inside the 'm_clipPoly'.
							{
								outNoCommonArea		= false;
								resultPolygons.push_back( m_clipPoly );
								break;
							}
						}

						if ( i < clipPtCnt )
						{
							const VWPoint2D&	vc	= m_clipPoly.GetVertexAt( i );
							if ( polygon.IsPtInPoly2D( vc.x, vc.y, VWPoint2D::sEpsilon ) )		// 'm_clipPoly' is inside the 'polygon'.
							{
								outNoCommonArea		= false;
								outInnerClipper		= true;
								resultPolygons.push_back( polygon );
								break;
							}
						}
					}
				}
			}
		}

		if ( performOperation )						// the boolean operation must be performed.
		{
			VWPolygon2D			polyB( m_clipPoly );
			VWPolygon2D			polyA( polygon );

			// get clipper center.
			const VWPoint2D&	center				=	polyB.GetCenter();
			// transformation matrix.
			VWTransformMatrix	mat;

			// check whether center coordinates are too big (could lead to incorrect result).
			bool				isTooFar			=	( center.Magnitude() > KBOOL_MAX_COORD_VAL );
			if ( isTooFar )							// get usable polys B and A.
			{
				// set translation.
				mat.SetOffset( - center );

				polyB.PointsTransform( mat );		// usable poly B.
				polyA.PointsTransform( mat );		// usable poly A.
			}

			// the boolean operation.
			try
			{
				((Bool_Engine*) m_pBooleanEngine)->Activate();
				::SetPolygonA( (Bool_Engine*) m_pBooleanEngine, polyA );
				::SetPolygonB( (Bool_Engine*) m_pBooleanEngine, polyB );
				((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_OR );
				::GetResult( (Bool_Engine*) m_pBooleanEngine, resultPolygons );
			}
			catch (Bool_Engine_Error& /*error*/)
			{
				isOK								= false;
			}

			if ( isOK && isTooFar )					// translate results (if needed).
			{
				size_t				len				=	resultPolygons.size();
				for ( size_t i = 0 ; i < len ; ++ i )
				{
					VWPolygon2D&	poly			=	resultPolygons[ i ];
					poly.InversePointsTransform( mat );
				}
			}
		}
	}

	// result.
	return	( isOK );
}

bool VWPolygonOperation::BooleanAND(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons)
{
	bool	noCommonArea;
	return	( VWPolygonOperation::BooleanAND( polygon, resultPolygons, noCommonArea ) );
}

// clips polygon by the specified clipper polygon. result are closed polygons representing the parts of the polygon which lie inside the clipper.
// also returns whether polygon and clipper have common area.
bool VWPolygonOperation::BooleanAND(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons, bool& outNoCommonArea)
{
	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
		return false;

	bool	ok		= true;
	resultPolygons.clear();

	try
	{
		// XXX Bobi:
		// instead of 'VWPolygonOperation::AreOverlapping' use the following function which is faster.
		// check if the polygon operation is necessary.
		if ( VWPolygon2D::ArePolygonsIntersecting( m_clipPoly, polygon, outNoCommonArea, VWPoint2D::sRawEpsilon ) )
		{
			VWPolygon2D			polyB( m_clipPoly );
			VWPolygon2D			polyA( polygon );

			// get clipper center.
			const VWPoint2D&	center		=	polyB.GetCenter();
			// transformation matrix.
			VWTransformMatrix	mat;

			// check whether center coordinates are too big (could lead to incorrect result).
			bool				isTooFar	=	( center.Magnitude() > KBOOL_MAX_COORD_VAL );
			if ( isTooFar ) {					// get usable polys B and A.

				// set translation.
				mat.SetOffset( - center );

				polyB.PointsTransform( mat );	// usable poly B.
				polyA.PointsTransform( mat );	// usable poly A.
			}

			// the boolean operation.
			((Bool_Engine*) m_pBooleanEngine)->Activate();
			::SetPolygonA( (Bool_Engine*) m_pBooleanEngine, polyA );
			::SetPolygonB( (Bool_Engine*) m_pBooleanEngine, polyB );
			((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_AND );
			::GetResult( (Bool_Engine*) m_pBooleanEngine, resultPolygons );

			if ( isTooFar ) {	// translate results (if needed).

				size_t				len			=	resultPolygons.size();
				for ( size_t i = 0 ; i < len ; ++ i ) {
					VWPolygon2D&	poly		=	resultPolygons[ i ];
					poly.InversePointsTransform( mat );
				}
			}
		}
		else {

			// 3 possible cases here:
			// - polygon is inside the m_clipPoly.
			// - m_clipPoly is inside the polygon.
			// - no common areas.

			if ( ! outNoCommonArea )												// might have common area. check!
			{
				// as it is still not sure that 'polygon' and 'm_clipPoly' overlap (they might not have common area), ...
				// ... make this additional check here.
				outNoCommonArea						= true;

				size_t					polyPtCnt	= polygon.GetVertexCount();
				size_t					clipPtCnt	= m_clipPoly.GetVertexCount();
				if ( polyPtCnt > 2 && clipPtCnt > 2 )								// both polygons are correct.
				{
					size_t				maxPtCnt	= ( polyPtCnt > clipPtCnt ) ? polyPtCnt : clipPtCnt;
					for ( size_t i = 0 ; i < maxPtCnt ; ++ i )
					{
						if ( i < polyPtCnt )
						{
							const VWPoint2D&	vp	= polygon.GetVertexAt( i );
							if ( m_clipPoly.IsPtInPoly2D( vp.x, vp.y, VWPoint2D::sEpsilon ) )	// polygon is inside the m_clipPoly.
							{
								resultPolygons.push_back( polygon );
								outNoCommonArea		= false;
								break;
							}
						}

						if ( i < clipPtCnt )
						{
							const VWPoint2D&	vc	= m_clipPoly.GetVertexAt( i );
							if ( polygon.IsPtInPoly2D( vc.x, vc.y, VWPoint2D::sEpsilon ) )		// m_clipPoly is inside the polygon.
							{
								resultPolygons.push_back( m_clipPoly );
								outNoCommonArea		= false;
								break;
							}
						}
					}
				}
			}
			// else: no common areas. no elements in resultPolygons.
		}
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

bool VWPolygonOperation::BooleanEXOR(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons)
{
	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
		return false;

	bool	ok		= true;

	try
	{
		((Bool_Engine*) m_pBooleanEngine)->Activate();
		::SetPolygonA( (Bool_Engine*) m_pBooleanEngine, polygon );
		::SetPolygonB( (Bool_Engine*) m_pBooleanEngine, m_clipPoly );
		((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_EXOR );
		::GetResult( (Bool_Engine*) m_pBooleanEngine, resultPolygons );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

bool VWPolygonOperation::BooleanPoly_SUB_Clip(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons)
{
	bool	noCommonArea;
	return	( VWPolygonOperation::BooleanPoly_SUB_Clip( polygon, resultPolygons, noCommonArea ) );
}

// clips polygon by the specified clipper polygon. result are closed polygons representing the parts of the polygon which lie outside the clipper.
// also returns whether polygon and clipper have common area.
bool VWPolygonOperation::BooleanPoly_SUB_Clip(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons, bool& outNoCommonArea)
{
	bool						isOK				= true;
	outNoCommonArea									= true;
	resultPolygons.clear();

	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
	{
		VWFC_ASSERT( false );						// bad input !
		isOK										= false;
	}

	if ( isOK )										// good input polygons.
	{
		// XXX Bobi:
		// instead of 'VWPolygonOperation::AreOverlapping' use the following function which is faster.
		// check if the polygon operation is necessary.
		bool					performOperation	= false;

		if ( VWPolygon2D::ArePolygonsIntersecting( m_clipPoly, polygon, outNoCommonArea, VWPoint2D::sRawEpsilon ) )
		{
			performOperation						= true;
		}
		else
		{
			// 3 possible cases here:
			// - 'polygon' is inside the 'm_clipPoly'.
			// - 'm_clipPoly' is inside 'polygon' (perform the boolean operation in this case !).
			// - no common areas.

			if ( ! outNoCommonArea )												// might have common area. check!
			{
				// as it is still not sure that 'polygon' and 'm_clipPoly' overlap (they might not have common area), ...
				// ... make this additional check here.
				outNoCommonArea						= true;

				size_t					polyPtCnt	= polygon.GetVertexCount();
				size_t					clipPtCnt	= m_clipPoly.GetVertexCount();
				if ( polyPtCnt > 2 && clipPtCnt > 2 )								// both polygons are correct.
				{
					size_t				maxPtCnt	= ( polyPtCnt > clipPtCnt ) ? polyPtCnt : clipPtCnt;
					for ( size_t i = 0 ; i < maxPtCnt ; ++ i )
					{
						if ( i < polyPtCnt )
						{
							const VWPoint2D&	vp	= polygon.GetVertexAt( i );
							if ( m_clipPoly.IsPtInPoly2D( vp.x, vp.y, VWPoint2D::sEpsilon ) )	// 'polygon' is inside the 'm_clipPoly'.
							{
								outNoCommonArea		= false;
								break;
							}
						}

						if ( i < clipPtCnt )
						{
							const VWPoint2D&	vc	= m_clipPoly.GetVertexAt( i );
							if ( polygon.IsPtInPoly2D( vc.x, vc.y, VWPoint2D::sEpsilon ) )		// 'm_clipPoly' is inside the 'polygon'.
							{
								outNoCommonArea		= false;
								performOperation	= true;							// perform the boolean operation in this case !
								break;
							}
						}
					}
				}
			}

			if ( outNoCommonArea )								// do not have common area for sure (do not overlap).
			{
				resultPolygons.push_back( polygon );			// the result is 'polygon' itself !
			}
		}

		if ( performOperation )						// the boolean operation must be performed.
		{
			VWPolygon2D			polyB( m_clipPoly );
			VWPolygon2D			polyA( polygon );

			// get clipper center.
			const VWPoint2D&	center				=	polyB.GetCenter();
			// transformation matrix.
			VWTransformMatrix	mat;

			// check whether center coordinates are too big (could lead to incorrect result).
			bool				isTooFar			=	( center.Magnitude() > KBOOL_MAX_COORD_VAL );
			if ( isTooFar )							// get usable polys B and A.
			{
				// set translation.
				mat.SetOffset( - center );

				polyB.PointsTransform( mat );		// usable poly B.
				polyA.PointsTransform( mat );		// usable poly A.
			}

			// the boolean operation.
			try
			{
				((Bool_Engine*) m_pBooleanEngine)->Activate();
				::SetPolygonA( (Bool_Engine*) m_pBooleanEngine, polyA );
				::SetPolygonB( (Bool_Engine*) m_pBooleanEngine, polyB );
				((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_A_SUB_B );
				::GetResult( (Bool_Engine*) m_pBooleanEngine, resultPolygons );
			}
			catch (Bool_Engine_Error& /*error*/)
			{
				isOK								= false;
			}

			if ( isOK && isTooFar )					// translate results (if needed).
			{
				size_t				len				=	resultPolygons.size();
				for ( size_t i = 0 ; i < len ; ++ i )
				{
					VWPolygon2D&	poly			=	resultPolygons[ i ];
					poly.InversePointsTransform( mat );
				}
			}
		}
	}

	// result.
	return	( isOK );
}

bool VWPolygonOperation::BooleanClip_SUB_Poly(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons)
{
	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
		return false;

	bool	ok		= true;

	try
	{
		((Bool_Engine*) m_pBooleanEngine)->Activate();
		::SetPolygonA( (Bool_Engine*) m_pBooleanEngine, polygon );
		::SetPolygonB( (Bool_Engine*) m_pBooleanEngine, m_clipPoly );
		((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_B_SUB_A );
		::GetResult( (Bool_Engine*) m_pBooleanEngine, resultPolygons );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

// clip the 'poly' using 'clipper' polygon as clipping object
bool VWPolygonOperation::ClipToPoly(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly, const VWPolygon2D& inClipper)
{
	VWPolygonOperation	operation( inClipper );
	return	operation.BooleanAND( inPoly, resultPolygons );
}

bool VWPolygonOperation::CombinePolygons(VWPolygon2D&/*out*/ resultPolygon, const VWPolygon2D& inPoly1, const VWPolygon2D& inPoly2)
{
	if ( inPoly1.IsEmpty() || inPoly2.IsEmpty() )
		return false;

	bool	ok		= true;
	try
	{
		Bool_Engine		engine;
		::ArmBoolEng( & engine );
		::SetPolygonA( &engine, inPoly1 );
		::SetPolygonB( &engine, inPoly2 );

		// combine
		engine.Do_Operation( BOOL_OR );

		::GetResult( & engine, resultPolygon );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

bool VWPolygonOperation::SubtractPolygons(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly1, const VWPolygon2D& inPoly2)
{
	if ( inPoly1.IsEmpty() || inPoly2.IsEmpty() )
		return false;

	bool	ok		= true;
	try
	{
		Bool_Engine		engine;
		::ArmBoolEng( & engine );
		::SetPolygonA( &engine, inPoly1 );
		::SetPolygonB( &engine, inPoly2 );

		// combine
		engine.Do_Operation( BOOL_A_SUB_B );

		::GetResult( & engine, resultPolygons );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}


bool VWPolygonOperation::SmoothPolygon(VWPolygon2D&/*out*/ resultPolygon, const VWPolygon2D& polygon, double smoothAber /*=10.0*/)
{
	if ( polygon.IsEmpty() )
		return false;

	bool	ok		= true;
	try
	{
		Bool_Engine		engine;
		::ArmBoolEng( & engine );
		engine.SetSmoothAber( smoothAber );
		::SetPolygonA( &engine, polygon );

		engine.Do_Operation( BOOL_SMOOTHEN );

		::GetResult( & engine, resultPolygon );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

/*static*/ bool VWPolygonOperation::AreOverlapping(const VWPolygon2D& a, const VWPolygon2D& b)
{
	const double kEpsilon	= 0.0001;

	bool		bClip		= false;

	size_t		vertCnt2	= b.GetVertexCount();

	size_t		vertCnt1	= a.GetVertexCount();
	for(size_t i=0; i<vertCnt1; i++) {
		const VWPoint2D& v1	= a.GetVertexAt( i, false );
		const VWPoint2D& v2	= a.GetVertexAt( i + 1, true );

		for(size_t j=0; j<vertCnt2; j++) {
			const VWPoint2D& p1	= b.GetVertexAt( j, false );
			const VWPoint2D& p2	= b.GetVertexAt( j + 1, true );

			if ( ! bClip ) {
				double	intersX, intersY;
				bool	bParal	= false;
				bool	bOnSeg1	= false;
				bool	bOnSeg2	= false;
				VWLine2D::IntersectLines( p1.x, p1.y, p2.x, p2.y, v1.x, v1.y, v2.x, v2.y, intersX, intersY, bParal, bOnSeg1, bOnSeg2, kEpsilon );

				bClip			= ! bParal && bOnSeg1 && bOnSeg2;
				if ( bClip ) {
					break;
				}
			}
		}

		if ( bClip ) {
			break;
		}
	}

	return bClip;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cut polygon routines
VWPolygonOperation::SVertex::SVertex()
{
	bOnCutter		= false;
	bInCutter		= false;
	bInters			= false;
	pNextVertex		= NULL;
	type			= eVertexType_Corner;
	radius			= 0;
}

bool VWPolygonOperation::CutPolygon(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly, const VWPolygon2D& inCutter)
{
	VWPolygonOperation	operation( inCutter );
	return operation.CutPolygon( inPoly, resultPolygons );
}

bool VWPolygonOperation::CutPolygon(const VWPolygon2D& inPoly, TSTLPolygons2DArray&/*out*/ resultPolygons)
{
	// create vertices list from poly.
	SVertex*				pFirstVert	= NULL;
	SVertex*				pLastVert	= NULL;
	resultPolygons.clear();

	if ( VWPolygonOperation::InitVerticesListFromPoly( inPoly, pFirstVert, pLastVert ) )
	{
		size_t				vertsCnt	= inPoly.GetVertexCount();

		// validate.
		VWFC_ASSERT( vertsCnt > 0 );	// must not happen !

		VWPolygonOperation::AddIntersectionVerticesForCut( pFirstVert, vertsCnt, m_clipPoly );

		m_pSTLCutResultArray			= & resultPolygons;
		m_cutResutPoly.ClearVertices();

		// collect cut polygons.
		this->WalkValidVertexsForCut( pFirstVert );

		// clear vertices list.
		VWPolygonOperation::ClearVerticesList( pFirstVert, pLastVert );
	}

	// result.
	return	( resultPolygons.size() > 0 );
}

bool VWPolygonOperation::CutPolygon_Fast(const VWPolygon2D& inPoly, TSTLPolygons2DArray&/*out*/ resultPolygons)
{
	size_t					polyPtCnt			= inPoly.GetVertexCount();
	if ( ( polyPtCnt == 0 ) || m_clipPoly.IsEmpty() )
		return false;

	resultPolygons.clear();

	// XXX Bobi:
	// instead of 'VWPolygonOperation::AreOverlapping' use the following function which is faster.
	// check if the polygon operation is necessary at all.
	// if there are cases missed by the following function, try using 'ArePolygonsIntersecting'.
	bool					noCommonArea;
	if ( VWPolygon2D::ArePolygonsIntersecting_Fast( m_clipPoly, inPoly, noCommonArea ) )
	{
		this->CutPolygon( inPoly, resultPolygons );								// cutting.
	}
	else {

		// 3 possible cases here:
		// - inPoly is inside the m_clipPoly.
		// - m_clipPoly is inside the inPoly.
		// - no common areas.

		if ( ! noCommonArea )													// might have common area. check!
		{
			size_t					clipPtCnt	= m_clipPoly.GetVertexCount();
			if ( polyPtCnt > 2 && clipPtCnt > 2 )								// both polygons are correct.
			{
				size_t				maxPtCnt	= ( polyPtCnt > clipPtCnt ) ? polyPtCnt : clipPtCnt;
				for ( size_t i = 0 ; i < maxPtCnt ; ++ i )
				{
					if ( i < polyPtCnt )
					{
						const VWPoint2D&	vp	= inPoly.GetVertexAt( i );
						if ( m_clipPoly.IsPtInPoly2D( vp.x, vp.y, VWPoint2D::sEpsilon ) )	// inPoly is inside the m_clipPoly.
						{
							resultPolygons.push_back( inPoly );
							break;
						}
					}

					if ( i < clipPtCnt )
					{
						const VWPoint2D&	vc	= m_clipPoly.GetVertexAt( i );
						if ( inPoly.IsPtInPoly2D( vc.x, vc.y, VWPoint2D::sEpsilon ) )		// m_clipPoly is inside the inPoly.
						{
							break;
						}
					}
				}
			}
		}
		// else: no common areas. no elements in resultPolygons.
	}

	return ( resultPolygons.size() > 0 );
}

// clip the specified polygon by clipper.
// the result are those parts of the polygon that lie outside the clipper.
// NOTE! the cut preserve the vertex types outside the clipper. New points are corners !
bool VWPolygonOperation::ClipPolygon(const VWPolygon2D& inPoly, TSTLPolygons2DArray&/*out*/ resultPolygons)
{
	// create vertices list from poly.
	SVertex*				pFirstVert	= NULL;
	SVertex*				pLastVert	= NULL;
	resultPolygons.clear();
	if ( VWPolygonOperation::InitVerticesListFromPoly( inPoly, pFirstVert, pLastVert ) )
	{
		size_t				vertsCnt	= inPoly.GetVertexCount();

		// validate.
		VWFC_ASSERT( vertsCnt > 0 );	// must not happen !

		VWPolygonOperation::AddIntersectionVertices( pFirstVert, vertsCnt, m_clipPoly );

		m_pSTLCutResultArray			= & resultPolygons;
		m_cutResutPoly.ClearVertices();

		// collect clipped polygons.
		this->WalkValidVertexsForClip( pFirstVert );

		// clear vertices list.
		VWPolygonOperation::ClearVerticesList( pFirstVert, pLastVert );
	}

	// result.
	return	( resultPolygons.size() > 0 );
}

// a faster version. NOTE! as it might work a little bit differently, preferably use it in new functionalities and test well!
bool VWPolygonOperation::ClipPolygon_Fast(const VWPolygon2D& inPoly, TSTLPolygons2DArray&/*out*/ resultPolygons)
{
	size_t					polyPtCnt			= inPoly.GetVertexCount();
	if ( ( polyPtCnt == 0 ) || m_clipPoly.IsEmpty() )
		return false;

	resultPolygons.clear();
	// XXX Bobi:
	// instead of 'VWPolygonOperation::AreOverlapping' use the following function which is faster.
	// check if the polygon operation is necessary at all.
	// if there are cases missed by the following function, try using 'ArePolygonsIntersecting'.
	bool					noCommonArea;
	if ( VWPolygon2D::ArePolygonsIntersecting_Fast( m_clipPoly, inPoly, noCommonArea ) )
	{
		this->ClipPolygon( inPoly, resultPolygons );								// clipping.
	}
	else
	{
		// 3 possible cases here:
		// - inPoly is inside the m_clipPoly.
		// - m_clipPoly is inside the inPoly.
		// - no common areas.

		if ( ! noCommonArea )													// might have common area. check!
		{
			size_t					clipPtCnt	= m_clipPoly.GetVertexCount();
			if ( polyPtCnt > 2 && clipPtCnt > 2 )								// both polygons are correct.
			{
				size_t				maxPtCnt	= ( polyPtCnt > clipPtCnt ) ? polyPtCnt : clipPtCnt;
				for ( size_t i = 0 ; i < maxPtCnt ; ++ i )
				{
					if ( i < polyPtCnt )
					{
						const VWPoint2D&	vp	= inPoly.GetVertexAt( i );
						if ( m_clipPoly.IsPtInPoly2D( vp.x, vp.y, VWPoint2D::sEpsilon ) )	// inPoly is inside the m_clipPoly.
						{
							break;
						}
					}

					if ( i < clipPtCnt )
					{
						const VWPoint2D&	vc	= m_clipPoly.GetVertexAt( i );
						if ( inPoly.IsPtInPoly2D( vc.x, vc.y, VWPoint2D::sEpsilon ) )		// m_clipPoly is inside the inPoly.
						{
							resultPolygons.push_back( inPoly );
							break;
						}
					}
				}
			}
		}
		else		// no common areas. original poly in resultPolygons.
		{
			resultPolygons.push_back( inPoly );
		}
	}

	return ( resultPolygons.size() > 0 );
}

void VWPolygonOperation::AddIntersectionVertices(SVertex* pFirstVertex, size_t& vertsCnt, const VWPolygon2D& cutter)
{
	if ( vertsCnt == 0 || pFirstVertex == NULL )
		return;

	SVertex*	pThisVert	= pFirstVertex;
	do
	{
		SVertex*	pNextVert			= pThisVert ? pThisVert->pNextVertex : NULL;
		bool		bPrepareToFinish	= pNextVert == pFirstVertex;

		if ( pThisVert == NULL || pNextVert == NULL )
			break;

		bool		bMoveVert	= true;
		size_t		cutterCnt	= cutter.GetVertexCount();
		if ( ! cutter.IsClosed() )
			cutterCnt--;

		for(size_t j=0; j<cutterCnt; j++) {
			const VWPoint2D&	a	= cutter.GetVertexAt( j, true );
			const VWPoint2D&	b	= cutter.GetVertexAt( j+1, true );

			double				intersX, intersY;
			bool				parallel, onSegment1, onSegment2;
			VWLine2D::IntersectLines(	pThisVert->pt.x, pThisVert->pt.y, pNextVert->pt.x, pNextVert->pt.y,
										a.x, a.y, b.x, b.y,
										intersX, intersY, parallel, onSegment1, onSegment2,
										VWPoint2D::sEpsilon );

			if ( ! parallel && onSegment1 && onSegment2 ) {
				VWPoint2D	intersPt( intersX, intersY );

				//bool	okWithA		= ! MathUtils::Equalish( intersPt, a, 0.0001 );
				//bool	okWithB		= ! MathUtils::Equalish( intersPt, b, 0.0001 );
				bool	okWithP1	= ! MathUtils::Equalish( intersPt, pThisVert->pt, 0.0001 );
				bool	okWithP2	= ! MathUtils::Equalish( intersPt, pNextVert->pt, 0.0001 );

				if ( /*okWithA && okWithB &&*/ okWithP1 && okWithP2  )
				{
					SVertex*			pVert	= SDK_NEW SVertex();
					pVert->bInCutter			= false;
					pVert->bOnCutter			= true;
					pVert->bInters				= true;
					pVert->index				= vertsCnt;
					pVert->pt.x					= intersX;
					pVert->pt.y					= intersY;
					pVert->z					= VWLine3D::GetVerticalDistance( pThisVert->pt.x, pThisVert->pt.y, pThisVert->z, pNextVert->pt.x, pNextVert->pt.y, pNextVert->z, intersX, intersY );
					pVert->bVisible				= pThisVert->bVisible;
					pVert->pNextVertex			= pNextVert;

					pThisVert->pNextVertex		= pVert;

					vertsCnt++;
					bMoveVert		= false;
					break;
				}
			}
		}

		if ( bMoveVert ) {
			pThisVert	= pThisVert ? pThisVert->pNextVertex : NULL;
			if( bPrepareToFinish && pThisVert == pFirstVertex )
				pThisVert		= NULL;
		}

	} while(true);

	// now validate the points
	// valid points are those which line inside or on the cut poly
	pThisVert		= pFirstVertex;
	do {
		if ( ! pThisVert->bOnCutter && ! pThisVert->bInCutter ) {
			cutter.IsPtOnPoly2D( pThisVert->pt.x, pThisVert->pt.y, pThisVert->bOnCutter, pThisVert->bInCutter, 0.0001 );
		}

		pThisVert	= pThisVert->pNextVertex;
		if ( pThisVert == pFirstVertex )
			pThisVert	= NULL;
	} while ( pThisVert );
}

void VWPolygonOperation::AddIntersectionVerticesForCut(SVertex* pFirstVertex, size_t& vertsCnt, const VWPolygon2D& cutter)
{
	if ( vertsCnt == 0 || pFirstVertex == NULL )
		return;

	SVertex*	pThisVert	= pFirstVertex;
	do
	{
		SVertex*	pNextVert			= pThisVert ? pThisVert->pNextVertex : NULL;
		bool		bPrepareToFinish	= pNextVert == pFirstVertex;

		if ( pThisVert == NULL || pNextVert == NULL )
			break;

		size_t		cutterCnt	= cutter.GetVertexCount();
		if ( ! cutter.IsClosed() )
			cutterCnt--;

		// find and add all intersections between the cutter sides and (this->next) side.
		// note that with every found and added intersection, 'next' will be updated to be the last added.
		for ( size_t j = 0 ; j < cutterCnt ; ++ j )
		{
			const VWPoint2D&	a	= cutter.GetVertexAt( j, true );
			const VWPoint2D&	b	= cutter.GetVertexAt( j+1, true );

			double				intersX, intersY;
			bool				parallel;

			double				ua, ub;
			// find the intersection and the coefficients 'ua' and 'ub' defining where the intersection along the lines' vectors is.
			VWLine2D::IntersectLines(	pThisVert->pt.x, pThisVert->pt.y, pNextVert->pt.x, pNextVert->pt.y,
										a.x, a.y, b.x, b.y,
										parallel, intersX, intersY, ua, ub,
										VWPoint2D::sEpsilon );		// collinearity epsilon.

			// note: ensure that the intersection really lies on both lines (no epsilon).

			if ( ( ! parallel ) &&				// not parallel (intersection exists) and ...
				 ( ua > 0.0 && ua < 1.0 ) &&	// ... the intersection lies on 'line 1' (no epsilon) and ...
				 ( ub > 0.0 && ub < 1.0 ) )		// ... on 'line 2' (no epsilon).
			{
				VWPoint2D	intersPt( intersX, intersY );

				bool	okWithA		= ! MathUtils::Equalish( intersPt, a, 0.0001 );
				bool	okWithB		= ! MathUtils::Equalish( intersPt, b, 0.0001 );
				bool	okWithP1	= ! MathUtils::Equalish( intersPt, pThisVert->pt, 0.0001 );
				bool	okWithP2	= ! MathUtils::Equalish( intersPt, pNextVert->pt, 0.0001 );

				if ( okWithA && okWithB && okWithP1 && okWithP2  )
				{
					// prepare the new vertex.
					SVertex*			pVert	= SDK_NEW SVertex();
					pVert->bInCutter			= false;
					pVert->bOnCutter			= true;
					pVert->bInters				= true;
					pVert->index				= vertsCnt;
					pVert->pt.x					= intersX;
					pVert->pt.y					= intersY;
					pVert->z					= VWLine3D::GetVerticalDistance( pThisVert->pt.x, pThisVert->pt.y, pThisVert->z, pNextVert->pt.x, pNextVert->pt.y, pNextVert->z, intersX, intersY );

					// insert the newly added to the list.
					pVert->pNextVertex			= pNextVert;
					pThisVert->pNextVertex		= pVert;

					// update the 'next' to be the last added.
					pNextVert		= pVert;

					++ vertsCnt;	// increase the count.
				}
			}
		}

		// note that at this point the current (this->next) list segment is already examined for intersections (see the above loop).
		// so we have to move to the next list segment.
		pThisVert	= pThisVert ? pThisVert->pNextVertex : NULL;
		if ( bPrepareToFinish && pThisVert == pFirstVertex )
			pThisVert	= NULL;

	} while(true);

	// now validate the points
	// valid points are those which lie inside or on the cut poly
	pThisVert		= pFirstVertex;
	do {
		if ( ! pThisVert->bOnCutter && ! pThisVert->bInCutter ) {
			cutter.IsPtOnPoly2D( pThisVert->pt.x, pThisVert->pt.y, pThisVert->bOnCutter, pThisVert->bInCutter, 0.0001 );
		}

		pThisVert	= pThisVert->pNextVertex;
		if ( pThisVert == pFirstVertex )
			pThisVert	= NULL;
	} while ( pThisVert );
}

// collects inner parts (inside the cutter).
void VWPolygonOperation::WalkValidVertexsForCut(SVertex* pFirstVertex)
{
	SVertex*			pThisVert		=	pFirstVertex;
	do
	{
		// search for the beginning of an inner segment (inside cutter).
		VWPolygonOperation::SearchStartOfInnerSegment( pFirstVertex, pThisVert );
		if ( pThisVert == NULL )
		{
			break;
		}

		// add inner segment.
		SVertex*		pStartVert		=	pThisVert;

		NNA_SCOPE
		{
			// XXX Bobi:
			// lock the collecting poly while collecting the poly part points.
			// this temporary supresses recalculating of the poly bounding box - it's a slow operation and not needed while collecting points.
			VWPolygon2D::CLockForEdit	clippedPolyLock( m_cutResutPoly );

			while ( pThisVert && ( pThisVert->bOnCutter || pThisVert->bInCutter ) )
			{
				this->AddValidVertex( pThisVert );

				// current point is on cutter => the next point is from other inner segment.
				bool	isGoingOut		=	pThisVert->bOnCutter && ( pThisVert != pStartVert );

				// prevent repeat adding.
				pThisVert->bOnCutter	=	false;
				pThisVert->bInCutter	=	false;

				if ( isGoingOut )							// next point is from other segment. stop!
				{
					break;
				}

				// next.
				pThisVert				=	pThisVert->pNextVertex;
			}
		}

		this->FinishValidVerticesForPoly( pStartVert == pThisVert );
	}
	while( true );
}

// collects the outer parts (outside the clipper).
void VWPolygonOperation::WalkValidVertexsForClip(SVertex* pFirstVertex)
{
	SVertex*			pThisVert		= pFirstVertex;
	do
	{
		SVertex*		pStartVert		= pThisVert;
		if ( pStartVert == NULL )
		{
			break;
		}

		NNA_SCOPE
		{
			// XXX Bobi:
			// lock the collecting poly while collecting the poly part points.
			// this temporary supresses recalculating of the poly bounding box - it's a slow operation and not needed while collecting points.
			VWPolygon2D::CLockForEdit	clippedPolyLock( m_cutResutPoly );

			// add outer segment.
			while ( pStartVert && ( ! pStartVert->bInCutter ) )	// vertex is outside or on the cutter.
			{
				this->AddValidVertex( pStartVert );

				// current point is on cutter => the next point is from other inner segment.
				bool	isGoingIn		= ( ( pStartVert != pThisVert ) &&	// not just started (first added) ...
											( pStartVert->bOnCutter ) );	// ... and is on cutter.

				// prevent repeated adding.
				// to collect correctly the part at start/finish of the original polygon.
				if ( pStartVert == pFirstVertex )
				{
					pStartVert->bOnCutter	= true;
				}
				else
				{
					pStartVert->bInCutter	= true;				// mark as inner.
				}

				if ( isGoingIn )								// next point is from other segment. stop!
				{
					break;
				}

				// next.
				pStartVert				= pStartVert->pNextVertex;
			}
		}

		// collect the polygon.
		this->FinishValidVerticesForPoly( pStartVert == pThisVert );

		// searches for the ending of an inner segment (outside clipper).
		VWPolygonOperation::SearchFinishOfInnerSegment( pStartVert, pThisVert );
	}
	while( true );
}

void VWPolygonOperation::AddValidVertex(SVertex* pVertex)
{
	m_cutResutPoly.AddVertex( pVertex->pt, pVertex->type, pVertex->radius );
}

void VWPolygonOperation::FinishValidVerticesForPoly(bool bClosed)
{
	if ( m_pSTLCutResultArray ) {
		if ( m_cutResutPoly.GetVertexCount() >= 2 )  {
			m_cutResutPoly.SetClosed( bClosed );
			m_pSTLCutResultArray->push_back( m_cutResutPoly );
		}
	}
	m_cutResutPoly.ClearVertices();
}

// creates vertices list from 2D polygon.
/*static*/ bool VWPolygonOperation::InitVerticesListFromPoly(const VWPolygon2D& inPoly, SVertex*& outFirstVert, SVertex*& outLastVert)
{
	// init.
	bool						isDone		= false;

	outFirstVert							= NULL;
	outLastVert								= NULL;

	size_t						vertCnt		= inPoly.GetVertexCount();
	if ( vertCnt > 0 )
	{
		for ( size_t i = 0 ; i < vertCnt ; ++ i )
		{
			SVertex*			vert		= SDK_NEW SVertex();
			const VWPoint2D&	pt			= inPoly.GetVertexAt( i );
			EVertexType			type		= inPoly.GetVertexType( i );
			double				r			= ( type == eVertexType_Arc ) ? inPoly.GetArcVertexRadius( i ) : 0;

			vert->index						= i;
			vert->pt						= pt;
			vert->z							= 0;
			vert->type						= type;
			vert->radius					= r;
			vert->bVisible					= inPoly.GetVertexVisible( i );

			if ( outFirstVert == NULL )
			{
				outFirstVert				= vert;
			}
			else
			{
				outLastVert->pNextVertex	= vert;
			}

			outLastVert						= vert;
		}

		if ( inPoly.IsClosed() )
		{
			outLastVert->pNextVertex		= outFirstVert;
		}

		// validate.
		if ( outFirstVert )
		{
			isDone							= true;
		}
		else
		{
			VWFC_ASSERT( false );			// must not happen !
		}
	}
	else
	{
		VWFC_ASSERT( false );				// empty input poly.
	}

	// result.
	return	( isDone );
}

// creates vertices list from 3D polygon.
/*static*/ bool VWPolygonOperation::InitVerticesListFromPoly(const VWPolygon3D& inPoly, SVertex*& outFirstVert, SVertex*& outLastVert)
{
	// init.
	bool						isDone		= false;

	outFirstVert							= NULL;
	outLastVert								= NULL;

	size_t						vertCnt		= inPoly.GetVertexCount();
	if ( vertCnt > 0 )
	{
		for ( size_t i = 0 ; i < vertCnt ; ++ i )
		{
			SVertex*			vert		= SDK_NEW SVertex();
			const VWPoint3D&	pt			= inPoly.GetVertexAt( i );

			vert->index						= i;
			vert->pt						= pt;
			vert->z							= pt.z;

			if ( outFirstVert == NULL )
			{
				outFirstVert				= vert;
			}
			else
			{
				outLastVert->pNextVertex	= vert;
			}

			outLastVert						= vert;
		}

		if ( inPoly.IsClosed() )
		{
			outLastVert->pNextVertex		= outFirstVert;
		}

		// validate.
		if ( outFirstVert )
		{
			isDone							= true;
		}
		else
		{
			VWFC_ASSERT( false );			// must not happen !
		}
	}
	else
	{
		VWFC_ASSERT( false );				// empty input poly.
	}

	// result.
	return	( isDone );
}

// clears vertices list.
/*static*/ void VWPolygonOperation::ClearVerticesList(SVertex*& firstVert, SVertex*& lastVert)
{
	SVertex*		thisVert	= firstVert;
	do
	{
		SVertex*	nextVert	= thisVert->pNextVertex;
		if ( nextVert == firstVert )
		{
			nextVert			= NULL;
		}

		delete	thisVert;
		thisVert				= nextVert;
	}
	while ( thisVert );

	firstVert					= NULL;
	lastVert					= NULL;
}

// having intersection vertices added (using cutter/clipper), searches for the beginning of an inner segment (inside cutter/clipper).
/*static*/ void VWPolygonOperation::SearchStartOfInnerSegment(SVertex* inFirstVertex, SVertex*& outVertex)
{
	// init.
	outVertex						=	NULL;

	SVertex*		searchVertex	=	inFirstVertex;
	// search for the beginning of an inner segment (inside cutter).
	while ( searchVertex )
	{
		bool		isBegOfInnerSeg	=	false;

		if ( searchVertex->bOnCutter )
		{
			if ( searchVertex->pNextVertex && ( searchVertex->pNextVertex->bOnCutter || searchVertex->pNextVertex->bInCutter ) )
			{
				isBegOfInnerSeg		=	true;			// the point is on cutter, next is on/in cutter.
			}
		}
		else if ( searchVertex->bInCutter )
		{
			isBegOfInnerSeg			=	true;
		}

		if ( isBegOfInnerSeg )							// if it is the beginning of an inner segment (inside cutter).
		{
			outVertex				=	searchVertex;	// the point is inside cutter.
			break;
		}

		// next.
		searchVertex				=	searchVertex->pNextVertex;

		if ( searchVertex == inFirstVertex )			// if last point is reached.
		{
			searchVertex			=	NULL;
		}
	}
}

// having intersection vertices added (using cutter/clipper), searches for the ending of an inner segment (outside cutter/clipper).
/*static*/ void VWPolygonOperation::SearchFinishOfInnerSegment(SVertex* inFirstVertex, SVertex*& outVertex)
{
	// init.
	outVertex						=	NULL;

	SVertex*		searchVertex	=	inFirstVertex;
	// search for the ending of an inner segment (inside cutter).
	while ( searchVertex )
	{
		bool		isEndOfInnerSeg	=	false;

		if ( searchVertex->bOnCutter &&
			( ! searchVertex->bInCutter ) )				// not already passed (as it is not maked as on and in cutter at the same time).
		{
			if ( searchVertex->pNextVertex &&
				( ( ! searchVertex->pNextVertex->bOnCutter ) && ( ! searchVertex->pNextVertex->bInCutter ) ) )	// next is outer.
			{
				isEndOfInnerSeg		=	true;			// the point is on cutter, next is on/in cutter.
			}
		}
		else if ( ( ! searchVertex->bOnCutter ) && ( ! searchVertex->bInCutter ) )								// this is outer.
		{
			isEndOfInnerSeg			=	true;
		}

		if ( isEndOfInnerSeg )							// if it is the ending of an inner segment.
		{
			outVertex				=	searchVertex;	// the point is inside cutter.
			break;
		}

		// next.
		searchVertex				=	searchVertex->pNextVertex;

		if ( searchVertex == inFirstVertex )			// if last point is reached.
		{
			searchVertex			=	NULL;
		}
	}
}

// add points when segments polygon intersect with source polyg
// and hide those segments that are inside the specified segment polygons
void VWPolygonOperation::HideSetmentsBeloPolygon(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& arrSegmentPolys)
{
	size_t						segsCnt		= arrSegmentPolys.size();

	// create vertices list from poly.
	SVertex*					pFirstVert	= NULL;
	SVertex*					pLastVert	= NULL;
	resultPolygons.clear();
	if ( ( segsCnt > 0 ) && VWPolygonOperation::InitVerticesListFromPoly( inPoly, pFirstVert, pLastVert ) )
	{
		size_t					vertsCnt	= inPoly.GetVertexCount();

		// validate.
		VWFC_ASSERT( vertsCnt > 0 );	// must not happen !

		for ( size_t j = 0 ; j < segsCnt ; ++ j )
		{
			const VWPolygon2D&	segPoly		= arrSegmentPolys[ j ];
			VWPolygonOperation::AddIntersectionVertices( pFirstVert, vertsCnt, segPoly );
		}

		resultPolygons.clear();

		VWPolygon2D				poly;
		poly.SetClosed( false );

		bool					lastVisible	= true;
		VWPoint2D				lastVert;
		SVertex*				pThisVert	= pFirstVert;
		do
		{
			SVertex*			pNextVert	= pThisVert->pNextVertex;

			bool				bStopThis	= false;
			if ( ! lastVisible )
			{
				// invisible segment
				bStopThis					= true;
			}
			else
			{
				if ( pThisVert != pFirstVert )
				{
					VWPoint2D	midPt		= (lastVert + pThisVert->pt) / 2;
					for ( size_t j = 0 ; j < segsCnt ; ++ j )
					{
						const VWPolygon2D&	segPoly		= arrSegmentPolys[ j ];
						if ( segPoly.IsPtInPoly2D( midPt, VWPoint2D::sEpsilon ) )
						{
							bStopThis		= true;
							break;
						}
					}
				}
			}

			if ( bStopThis )
			{
				if ( poly.GetVertexCount() > 0 )
				{
					resultPolygons.push_back( poly );
				}

				poly.ClearVertices();
				poly.SetClosed( false );
			}

			poly.AddVertex( pThisVert->pt, pThisVert->type, pThisVert->radius );
			if ( pNextVert == pFirstVert )
			{
				poly.AddVertex( pNextVert->pt, pNextVert->type, pNextVert->radius );
				pNextVert					= NULL;
			}

			lastVisible						= pThisVert->bVisible;
			lastVert						= pThisVert->pt;
			pThisVert						= pNextVert;
		}
		while ( pThisVert );

		if ( poly.GetVertexCount() > 0 )
		{
			resultPolygons.push_back( poly );
		}

		// clear vertices list.
		VWPolygonOperation::ClearVerticesList( pFirstVert, pLastVert );
	}
}

// clips polygon by the specified clipper polygons.
// result are those parts of clipped polygon which lie outside the clipper polygons.
void VWPolygonOperation::ClipByPolygons(TSTLPolygons2DArray&/*out*/ outResultPolys, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& clipPolys)
{
	// init.
	outResultPolys.clear();
	outResultPolys.push_back( inPoly );							// start from original.

	size_t							vertsCnt	= inPoly.GetVertexCount();
	size_t							clipCnt		= clipPolys.size();

	if ( ( vertsCnt > 0 ) && ( clipCnt > 0 ) )					// ok.
	{
		for ( size_t iClip = 0 ; iClip < clipCnt ; ++ iClip )	// loop clip polys.
		{
			const VWPolygon2D&		clipPoly	= clipPolys[ iClip ];

			VWPolygonOperation		operation( clipPoly );		// prepare the polygon operation.

			size_t					currPolyCnt	= outResultPolys.size();
			size_t					i			= 0;
			while ( i < currPolyCnt )
			{
				const VWPolygon2D&	polygon		= outResultPolys[ i ];

				bool				isClipped	= false;
				TSTLPolygons2DArray	clippedPolys;
				if ( operation.ClipPolygon_Fast( polygon, clippedPolys ) )
				{
					isClipped					= true;

					outResultPolys.erase( outResultPolys.begin() + i );	// remove current polygon.
					-- currPolyCnt;										// decrease the count of polygons to clip with this clipper.

					size_t			clippedCnt	= clippedPolys.size();
					if ( clippedCnt > 0 )
					{
						// push clipped into the array.
						for ( size_t j = 0 ; j < clippedCnt ; ++ j )
						{
							outResultPolys.push_back( clippedPolys[ j ] );
						}
					}
				}

				if ( ! isClipped )			// not clipped. hence, nothing removed.
				{
					++ i;					// increase counter.
				}
			}
		}
	}
}

// clips polygon by the specified clipper polygons. returns whether polygon is clipped by clippers.
// result are closed polygons representing the parts of the polygon which lie outside the clippers.
/*static*/ bool VWPolygonOperation::Polygon_SUB_Clippers(TSTLPolygons2DArray&/*out*/ outResultPolys, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& clipPolys)
{
	// init.
	bool							isClipped		= false;

	outResultPolys.clear();
	outResultPolys.push_back( inPoly );							// start from original.

	size_t							vertsCnt		= inPoly.GetVertexCount();
	size_t							clipCnt			= clipPolys.size();

	if ( ( vertsCnt > 0 ) && ( clipCnt > 0 ) )					// ok.
	{
		for ( size_t iClip = 0 ; iClip < clipCnt ; ++ iClip )	// loop clip polys.
		{
			const VWPolygon2D&		clipPoly		= clipPolys[ iClip ];

			VWPolygonOperation		operation( clipPoly );		// prepare the polygon operation.

			size_t					currPolyCnt		= outResultPolys.size();
			size_t					i				= 0;
			while ( i < currPolyCnt )
			{
				const VWPolygon2D&	polygon			= outResultPolys[ i ];

				bool				isClipDone		= false;

				TSTLPolygons2DArray	clippedPolys;

				bool				noCommArea		= true;
				// clip the polygon by the clipper.
				if ( operation.BooleanPoly_SUB_Clip( polygon, clippedPolys, noCommArea ) &&	// successful clipping and ...
					 ( ! noCommArea ) )														// ... some area is clipped for sure.
				{
					if ( ! isClipped )
					{
						isClipped					= true;				// mark as clipped.
					}

					isClipDone						= true;

					outResultPolys.erase( outResultPolys.begin() + i );	// remove current polygon.
					-- currPolyCnt;										// decrease the count of polygons to clip with this clipper.

					size_t			clippedCnt		= clippedPolys.size();
					if ( clippedCnt > 0 )
					{
						// push clipped into the array.
						for ( size_t j = 0 ; j < clippedCnt ; ++ j )
						{
							outResultPolys.push_back( clippedPolys[ j ] );
						}
					}
				}

				if ( ! isClipDone )					// not clipped. hence, nothing removed.
				{
					++ i;							// increase counter.
				}
			}
		}
	}

	// result.
	return	( isClipped );
}

// clips polygon by the specified clipper polygons. returns whether polygon is clipped by clippers.
// result are closed polygons representing the parts of the polygon which lie inside all of the clippers.
/*static*/ bool VWPolygonOperation::Polygon_AND_Clippers(TSTLPolygons2DArray&/*out*/ outResultPolys, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& clipPolys)
{
	// init.
	bool							isClipped		= false;

	outResultPolys.clear();
	outResultPolys.push_back( inPoly );							// start from original.

	size_t							vertsCnt		= inPoly.GetVertexCount();
	size_t							clipCnt			= clipPolys.size();

	if ( ( vertsCnt > 0 ) && ( clipCnt > 0 ) )					// ok.
	{
		for ( size_t iClip = 0 ; iClip < clipCnt ; ++ iClip )	// loop clip polys.
		{
			const VWPolygon2D&		clipPoly		= clipPolys[ iClip ];

			VWPolygonOperation		operation( clipPoly );		// prepare the polygon operation.

			size_t					currPolyCnt		= outResultPolys.size();
			size_t					i				= 0;
			while ( i < currPolyCnt )
			{
				const VWPolygon2D&	polygon			= outResultPolys[ i ];

				bool				isClipDone		= false;

				TSTLPolygons2DArray	clippedPolys;

				bool				noCommArea		= true;
				// clip the polygon by the clipper.
				if ( operation.BooleanAND( polygon, clippedPolys, noCommArea ) &&	// successful clipping and ...
					 ( ! noCommArea ) )												// ... some area is clipped for sure.
				{
					if ( ! isClipped )
					{
						isClipped					= true;				// mark as clipped.
					}

					isClipDone						= true;

					outResultPolys.erase( outResultPolys.begin() + i );	// remove current polygon.
					-- currPolyCnt;										// decrease the count of polygons to clip with this clipper.

					size_t			clippedCnt		= clippedPolys.size();
					if ( clippedCnt > 0 )
					{
						// push clipped into the array.
						for ( size_t j = 0 ; j < clippedCnt ; ++ j )
						{
							outResultPolys.push_back( clippedPolys[ j ] );
						}
					}
				}

				if ( ! isClipDone )					// not clipped. hence, nothing removed.
				{
					++ i;							// increase counter.
				}
			}
		}
	}

	// result.
	return	( isClipped );
}

// unites polygon with the specified polygons. returns if there is at least one union.
/*static*/ bool VWPolygonOperation::Polygon_OR_Polygons(TSTLPolygons2DArray&/*out*/ outResultPolys, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& inPolys)
{
	// init.
	bool							isUnited		= false;

	outResultPolys.clear();
	outResultPolys.push_back( inPoly );							// start from original.

	size_t							vertsCnt		= inPoly.GetVertexCount();
	size_t							polysCnt		= inPolys.size();

	if ( ( vertsCnt > 0 ) && ( polysCnt > 0 ) )					// ok.
	{
		for ( size_t iPoly = 0 ; iPoly < polysCnt ; ++ iPoly )	// loop polys.
		{
			const VWPolygon2D&		poly			= inPolys[ iPoly ];

			VWPolygonOperation		operation( poly );			// prepare the polygon operation.

			size_t					currPolyCnt		= outResultPolys.size();
			size_t					i				= 0;
			while ( i < currPolyCnt )
			{
				const VWPolygon2D&	polygon			= outResultPolys[ i ];

				bool				isUnionDone		= false;

				TSTLPolygons2DArray	unionPolys;

				bool				noCommArea, isInnerPoly;
				// unite.
				if ( operation.BooleanOR( polygon, unionPolys, noCommArea, isInnerPoly ) &&	// successful union and ...
					 ( ! noCommArea ) &&													// ... some area is united for sure and ...
					 ( ! isInnerPoly ) )													// ... the 'poly' is not inside the 'polygon'.
				{
					if ( ! isUnited )
					{
						isUnited					= true;				// mark as united.
					}

					isUnionDone						= true;

					outResultPolys.erase( outResultPolys.begin() + i );	// remove current polygon.
					-- currPolyCnt;										// decrease the count of polygons.

					size_t			unitedCnt		= unionPolys.size();
					if ( unitedCnt > 0 )
					{
						// push united into the array.
						for ( size_t j = 0 ; j < unitedCnt ; ++ j )
						{
							outResultPolys.push_back( unionPolys[ j ] );
						}
					}
				}

				if ( ! isUnionDone )				// not united. hence, nothing removed.
				{
					++ i;							// increase counter.
				}
			}
		}
	}

	// result.
	return	( isUnited );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Partitioning complex polygon routines


// SIntersPt.
VWPolygonOperation::SIntersPt::SIntersPt()
{
	fSegIndex0		= VWFC::kInvalidIndex;
	fSegIndex1		= VWFC::kInvalidIndex;
}

VWPolygonOperation::SIntersPt::~SIntersPt()
{
}

// SPolySegment.
VWPolygonOperation::SPolySegment::SPolySegment()
{
	fIndex			= VWFC::kInvalidIndex;
}

VWPolygonOperation::SPolySegment::~SPolySegment()
{
}

// the algorithm.
// NOTE: 1. The input polygon must be closed.
//		 2. Works only for complex (self-intersecting) polygons that have only corner vertices.
/////////////////
// collect data.
bool VWPolygonOperation::CollectSelfIntersData(const VWPolygon2D& polygon, TSTLPolySegmentArray& outArrPolySegments)
{
	// validate input poly is closed.
	if ( ! polygon.IsClosed() )
	{
		return	false;
	}

	// init.
	outArrPolySegments.clear();

	size_t					ptsCnt		= polygon.GetVertexCount();

	// prepare segments (one for every point).
	for ( size_t i = 0 ; i < ptsCnt ; ++ i )
	{
		TPolySegment		segment;
		segment.fIndex					= i;
		segment.fBegPt					= polygon.GetVertexAt( i );
		segment.fEndPt					= polygon.GetVertexAt( (i + 1) % ptsCnt );
		outArrPolySegments.push_back( segment );
	}

	VWPoint2D				intersPt;
	bool				hasSelfInters	= false;
	// loop.
	for ( size_t i = 0 ; i < ptsCnt ; ++ i )
	{
		TPolySegment&		currSeg		= outArrPolySegments[ i ];	// get the segment.

		size_t				prevInx		= ( i > 0 ) ? i - 1 : ptsCnt - 1;
		size_t				nextInx		= ( i + 1 ) % ptsCnt;

		const VWPoint2D&	pt1line1	= polygon.GetVertexAt( i );
		const VWPoint2D&	pt2line1	= polygon.GetVertexAt( nextInx );

		// first line.
		const VWLine2D		line1( pt1line1, pt2line1 );

		for ( size_t j = 0 ; j < ptsCnt ; ++ j )
		{
			// do not check for same edge or its adjacent.
			if ( i != j && prevInx != j && nextInx != j )
			{
				const VWPoint2D&	pt1line2	= polygon.GetVertexAt( j );
				const VWPoint2D&	pt2line2	= polygon.GetVertexAt( ( j + 1 ) % ptsCnt );

				// second line.
				const VWLine2D		line2( pt1line2, pt2line2 );

				if ( line2.IntersectLineSegments( line1, intersPt ) )
				{
					// ensure that the intersection point lies on both lines (no epsilon!).
					bool			isOnLines	= false;

					double			lenLine		= VWPoint2D::DistanceSqare( pt1line1.x, pt1line1.y, pt2line1.x, pt2line1.y );
					double			distToPt1	= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt1line1.x, pt1line1.y );
					double			distToPt2	= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt2line1.x, pt2line1.y );

					if ( ( distToPt1 <= lenLine ) && ( distToPt2 <= lenLine ) )	// intersection lies on line 1 (no epsilon!).
					{
						lenLine					= VWPoint2D::DistanceSqare( pt1line2.x, pt1line2.y, pt2line2.x, pt2line2.y );
						distToPt1				= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt1line2.x, pt1line2.y );
						distToPt2				= VWPoint2D::DistanceSqare( intersPt.x, intersPt.y, pt2line2.x, pt2line2.y );

						if ( ( distToPt1 <= lenLine ) && ( distToPt2 <= lenLine ) )	// intersection lies on line 2 (no epsilon!).
						{
							isOnLines			= true;
						}
					}

					if ( isOnLines )	// it is really a self-intersection point.
					{
						// prepare the intersection.
						TIntersPt	newInters;
						newInters.fPt			= intersPt;
						newInters.fSegIndex0	= i;
						newInters.fSegIndex1	= j;

						// distance to the beginning of the segment.
						double		distToBeg	= VWPoint2D::DistanceSqare( newInters.fPt.x, newInters.fPt.y, pt1line1.x, pt1line1.y );

						// add to sorted array!
						bool		intersAdded	= false;
						size_t		cntInters	= currSeg.farrIntersPts.size();
						for ( size_t k = 0 ; k < cntInters ; ++ k )
						{
							const TIntersPt&	currInters	= currSeg.farrIntersPts[ k ];
							// distance to the beginning of the segment.
							double	currDist	= VWPoint2D::DistanceSqare( currInters.fPt.x, currInters.fPt.y, pt1line1.x, pt1line1.y );

							if ( MathUtils::Lesserish( distToBeg, currDist, VWPoint2D::sEpsilon ) )
							{	
								// new intersection is closer to the segment's beginning.
								// insert.
								currSeg.farrIntersPts.insert( currSeg.farrIntersPts.begin() + k, newInters );
								intersAdded		= true;
								break;
							}
						}

						if ( ! intersAdded )	// still not added.
						{
							currSeg.farrIntersPts.push_back( newInters );
						}

						hasSelfInters			= true;
					}
				}
			}
		}
	}

	// result.
	return hasSelfInters;
}

// an algorithm for partitioning of a complex (self-intersecting) polygon.
// NOTE: 1. The input polygon must be closed.
//		 2. Works only for complex (self-intersecting) polygons that have only corner vertices.
void VWPolygonOperation::PartitionComplexPolygon(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly)
{
	// init.
	resultPolygons.clear();
	VWPolygon2D						polygon		= inPoly;	// work with a copy.
	polygon.CleanUpPolygon( VWPoint2D::sEpsilon );			// clean up.

	bool							isCW		= polygon.IsClockWise();

	// fill data structure.
	TSTLPolySegmentArray			arrPolySegments;
	if ( ! VWPolygonOperation::CollectSelfIntersData( polygon, arrPolySegments ) )
	{
		// no self intersections are found, or input polygon is not closed.
		resultPolygons.push_back( polygon );
	}
	else
	{
		size_t						cntSeg		= arrPolySegments.size();
		for ( size_t i = 0 ; i < cntSeg ; ++ i )
		{
			const TPolySegment&		polySeg		= arrPolySegments[ i ];
			size_t					cntInters	= polySeg.farrIntersPts.size();
			for ( size_t j = 0 ; j < cntInters; ++ j )
			{
				const TIntersPt&	inters		= polySeg.farrIntersPts[ j ];

				for ( size_t k = 0 ; k < 2 ; ++ k )	// for cw and ccw turns at intersections.
				{
					bool			bK			= ( k == 1 );
					bool			turnToCW	= ( bK || isCW ) && ! ( bK && isCW );	// xor.

					VWPolygon2D		resPoly;

					NNA_SCOPE
					{
						VWPolygon2D::CLockForEdit	lock( resPoly );	// lock (don't calculate bounds until the scope ends).

						// get simple polygon starting from this intersection.
						VWPolygonOperation::GetSimplePolygon( arrPolySegments, inters.fSegIndex0, inters.fPt, false, turnToCW, resPoly );
					}

					if ( resPoly.IsValidPolygon( VWPoint2D::sEpsilon ) )
					{
						// make a copy to check reversed poly as well.
						VWPolygon2D		copyPoly	= resPoly;
						copyPoly.ReversePoints();

						// check if already added.
						bool			isAdded		= false;
						size_t			cntRes		= resultPolygons.size();
						for ( size_t l = 0 ; l < cntRes ; ++ l )
						{
							const VWPolygon2D&	poly	= resultPolygons[ l ];
							if ( resPoly.EqualishTo( poly ) || copyPoly.EqualishTo( poly ) )
							{
								isAdded				= true;
								break;
							}
						}

						if ( ! isAdded )	// still not added.
						{
							resultPolygons.push_back( resPoly );
						}
					}
				}
			}
		}
	}
}

// having a set of polygons, concatenates those which have touching endpoints (if there are such).
void VWPolygonOperation::ConnectAdjoiningPolygons(TSTLPolygons2DArray& inOutPolygons, bool checkVertexTypes/*=false*/)
{
	size_t				inPolysCnt		= inOutPolygons.size();
	size_t				i				= 0;
	while ( i < ( inPolysCnt - 1 ) )
	{
		VWPolygon2D&	curResPoly		= inOutPolygons[ i ];

		size_t			j				= ( i + 1 );
		while ( j < inPolysCnt )
		{
			if ( curResPoly.AddAdjoiningPolygon( inOutPolygons[ j ], VWPoint2D::sEpsilon, checkVertexTypes ) )
			{
				inOutPolygons.erase( inOutPolygons.begin() + j );
				-- inPolysCnt;
			}

			++ j;
		}

		++ i;
	}
}

// find a closed simple polygon (without self-intersections).
// Input: segment index, start point which lies on the segment, if we go in reversed direction, direction to go on after reaching an intersection (CW/CCW).
// Output: resulting simple polygon.
void VWPolygonOperation::GetSimplePolygon(const TSTLPolySegmentArray& arrPolySegments, size_t segIndex, const VWPoint2D& fromPt, bool reversedDir, bool turnToCW, VWPolygon2D& resPoly)
{
	// check if we already have an enclosed polygon.
	size_t				fromPtIndex			= kInvalidIndex;
	Sint32				cntPts				= (Sint32) resPoly.GetVertexCount();
	for ( Sint32 i = ( cntPts - 1 ) ; i >= 0 ; -- i )
	{
		const VWPoint2D&	pt				= resPoly.GetVertexAt( i );
		if ( MathUtils::Equalish( fromPt, pt, VWPoint2D::sEpsilon ) )
		{
			fromPtIndex						= i; //-V101
			break;
		}
	}

	if ( fromPtIndex != kInvalidIndex )		// here we have a simple polygon found.
	{
		// clear extra points.
		for ( size_t i = 0 ; i < fromPtIndex ; ++ i )
		{
			resPoly.ClearVertex( 0 );
		}

		// set closed.
		resPoly.SetClosed( true );
	}
	else									// result polygon still not found.
	{
		resPoly.AddVertex( fromPt );		// add starting point.

		const TPolySegment&	currSeg			= arrPolySegments[ segIndex ];		// this segment.

		// get end point according to the direction we go to.
		VWPoint2D			endPt			= currSeg.fEndPt;
		if ( reversedDir )	endPt			= currSeg.fBegPt;

		// distance from 'fromPt' to the end of the segment.
		double				distToEnd		= VWPoint2D::DistanceSqare( fromPt.x, fromPt.y, endPt.x, endPt.y );

		// get segment direction vector.
		VWPoint2D			vecSeg			= ( endPt - fromPt ).Normalize();

		// get the intersection after 'fromPt' before the end of the segment.
		size_t				cntInters		= currSeg.farrIntersPts.size();
		size_t				nextIntersIndex	= kInvalidIndex;
		for ( size_t i = 0 ; i < cntInters ; ++ i )
		{
			size_t				inx			= i;
			if ( reversedDir )	inx			= ( cntInters - 1 - i );

			const TIntersPt&	inters		= currSeg.farrIntersPts[ inx ];
			double			dist			= VWPoint2D::DistanceSqare( inters.fPt.x, inters.fPt.y, endPt.x, endPt.y );

			if ( MathUtils::Greaterish( distToEnd, dist, VWPoint2D::sEpsilon ) )
			{
				nextIntersIndex				= inx;
				break;
			}
		}

		if ( nextIntersIndex != kInvalidIndex )	// there is an intersection on segment after 'fromPt'. 
		{
			const TIntersPt&	nextInters	= currSeg.farrIntersPts[ nextIntersIndex ];

			size_t				otherSegInx	= nextInters.fSegIndex1;		// index of the other intersection segment.

			// decide the direction to go on.
			const VWPoint2D&	otherBegPt	= arrPolySegments[ otherSegInx ].fBegPt;
			bool				isReversed	= false;
			if ( ( otherBegPt - endPt ).IsPointOnTheRightOfVector( vecSeg ) )
			{
				if ( turnToCW )		isReversed	= true;	// go to otherBegPt (reversed direction).
			}
			else
			{
				if ( ! turnToCW )	isReversed	= true;	// go to otherBegPt (reversed direction).
			}

			// recursive call.
			VWPolygonOperation::GetSimplePolygon( arrPolySegments, otherSegInx, nextInters.fPt, isReversed, turnToCW, resPoly );
		}
		else									// this segment has not intersections.
		{
			size_t				cntSeg		= arrPolySegments.size();
			size_t				nextSegInx	= ( segIndex + 1 ) % cntSeg;
			if ( reversedDir )	nextSegInx	= ( segIndex > 0 ) ? segIndex - 1 : cntSeg - 1;

			// recursive call.
			VWPolygonOperation::GetSimplePolygon( arrPolySegments, nextSegInx, endPt, reversedDir, turnToCW, resPoly );
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bool engine code
static void ArmBoolEng(Bool_Engine* pBoolEngine)
{
    // set some global vals to arm the boolean engine
    double DGRID = 0.00000001;		// round coordinate X or Y value in calculations to this
    double MARGE = 0.0000001;		// snap with in this range points to lines in the intersection routines
									// should always be > DGRID  a  MARGE >= 10*DGRID is oke
									// this is also used to remove small segments and to decide when
									// two segments are in line.
    double CORRECTIONFACTOR = 500.0;  // correct the polygons by this number
    double CORRECTIONABER   = 1.0;    // the accuracy for the rounded shapes used in correction
    double ROUNDFACTOR      = 1.5;    // when will we round the correction shape to a circle
    double SMOOTHABER       = 10.0;   // accuracy when smoothing a polygon
    double MAXLINEMERGE     = 1000.0; // leave as is, segments of this length in smoothen
   
    if (MARGE <= DGRID)
    {
		VWFC_ASSERT( false );
       // cout << "MARGE smaller than GRID" << endl;
        MARGE = DGRID*10;
    }

    // DGRID is only meant to make fractional parts of input data which 
    // are doubles, part of the integers used in vertexes within the boolean algorithm.
    // And therefore bigger than 1 is not usefull.
    // Within the algorithm all input data is multiplied with DGRID
    if ( DGRID < 1 )
        DGRID = 1/DGRID;
    else
        DGRID = 1;
    
    // space for extra intersection inside the boolean algorithms
    // only change this if there are problems
    Sint32 GRID =100;

    pBoolEngine->SetMarge( MARGE );
    pBoolEngine->SetGrid( GRID );
    pBoolEngine->SetDGrid( DGRID );
    pBoolEngine->SetCorrectionFactor( CORRECTIONFACTOR );
    pBoolEngine->SetCorrectionAber( CORRECTIONABER );
    pBoolEngine->SetSmoothAber( SMOOTHABER );
    pBoolEngine->SetMaxlinemerge( MAXLINEMERGE );
    pBoolEngine->SetRoundfactor( ROUNDFACTOR );

}


static void SetPolygonA(Bool_Engine* pBoolEngine, const VWPolygon2D& poly)
{
    if ( pBoolEngine->StartPolygonAdd( GROUP_A ) )
    {
		size_t		len	= poly.GetVertexCount();
		for(size_t i=0; i<len; i++) {
			const VWPoint2D& pt	= poly.GetVertexAt( i );
			pBoolEngine->AddPoint( pt.x, pt.y );
		}
    }
    pBoolEngine->EndPolygonAdd(); 
}

static void SetPolygonB(Bool_Engine* pBoolEngine, const VWPolygon2D& poly)
{
    if ( pBoolEngine->StartPolygonAdd( GROUP_B ) )
    {
		size_t		len	= poly.GetVertexCount();
		for(size_t i=0; i<len; i++) {
			const VWPoint2D& pt	= poly.GetVertexAt( i );
			pBoolEngine->AddPoint( pt.x, pt.y );
		}
    }
    pBoolEngine->EndPolygonAdd(); 
}

static void GetResult(Bool_Engine* pBoolEngine, TSTLPolygons2DArray& out)
{
	out.clear();
    // foreach resultant polygon in the booleng ...
    while ( pBoolEngine->StartPolygonGet() )
    {
		VWPolygon2D	resultPoly;
        // foreach point in the polygon
        while ( pBoolEngine->PolygonHasMorePoints() )
        {
			resultPoly.AddVertex( pBoolEngine->GetPolygonXPoint(), pBoolEngine->GetPolygonYPoint() );
        }
        pBoolEngine->EndPolygonGet();
		out.push_back( resultPoly );
    }
}

static void GetResult(Bool_Engine* pBoolEngine, VWPolygon2D& out)
{
	out.ClearVertices();
    // foreach resultant polygon in the booleng ...
    if ( pBoolEngine->StartPolygonGet() )
    {
        // foreach point in the polygon
        while ( pBoolEngine->PolygonHasMorePoints() )
        {
			out.AddVertex( pBoolEngine->GetPolygonXPoint(), pBoolEngine->GetPolygonYPoint() );
        }
        pBoolEngine->EndPolygonGet();
    }
}


#include "kbool/graph.h"
#include "kbool/graphlst.h"
#include "kbool/link.h"
#include "kbool/line.h"
#include "kbool/node.h"
#include "kbool/lpoint.h"
#include "kbool/record.h"
#include "kbool/scanbeam.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// booleng.cpp
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------/
//----------------- Bool_Engine_Error -------------------------------/
//-------------------------------------------------------------------/

Bool_Engine_Error::Bool_Engine_Error(const char* message, const char* header, Sint32 degree, Sint32 fatal)
{
}

Bool_Engine_Error::Bool_Engine_Error(const Bool_Engine_Error& a)
{

}

Bool_Engine_Error::~Bool_Engine_Error()
{
}


//-------------------------------------------------------------------/
//----------------- Bool_Engine -------------------------------------/
//-------------------------------------------------------------------/
Bool_Engine* ACTIVE_BoolEng;

Bool_Engine::Bool_Engine()
{

	ACTIVE_BoolEng = this;

	m_graphlist = SDK_NEW GraphList();
	m_ACCUR = 1e-4;
	m_WINDINGRULE = true;
	m_GraphToAdd = NULL;
	m_firstNodeToAdd = NULL;
	m_lastNodeToAdd = NULL;

}

Bool_Engine::~Bool_Engine()
{
	delete m_graphlist;
}

void Bool_Engine::SetLog( bool OnOff )
{
}

void Bool_Engine::Activate()
{
	ACTIVE_BoolEng = this;
}

void Bool_Engine::SetState( const char* process )
{
}

void Bool_Engine::error(const char *text, const char *title)
{
	throw Bool_Engine_Error(" Fatal Error", "Fatal Error", 9, 1);
};

void Bool_Engine::info(const char *text, const char *title)
{
	VWFC_ASSERT( false );
	//Write_Log("FATAL ERROR: ", title);
	//Write_Log("FATAL ERROR: ", text);
};

void Bool_Engine::SetMarge(double marge)
{
	m_MARGE = marge;
}

double Bool_Engine::GetAccur()
{
	return m_ACCUR;
}

void Bool_Engine::SetRoundfactor(double roundfac)
{
	m_ROUNDFACTOR = roundfac;
}

double Bool_Engine::GetRoundfactor()
{
	return m_ROUNDFACTOR;
}

double Bool_Engine::GetMarge()
{
	return m_MARGE;
}

void Bool_Engine::SetDGrid(double dgrid)
{
	m_DGRID = dgrid;
}

double Bool_Engine::GetDGrid()
{
	return m_DGRID;
}

void Bool_Engine::SetGrid(B_INT grid)
{
	m_GRID = grid;
}

B_INT Bool_Engine::GetGrid()
{
	return m_GRID;
}

void Bool_Engine::SetCorrectionAber(double aber)
{
	m_CORRECTIONABER = aber;
}

double Bool_Engine::GetCorrectionAber()
{
	return m_CORRECTIONABER;
}

void Bool_Engine::SetCorrectionFactor(double aber)
{
	m_CORRECTIONFACTOR = aber;
}

double Bool_Engine::GetCorrectionFactor()
{
	return m_CORRECTIONFACTOR;
}

void Bool_Engine::SetSmoothAber(double aber)
{
	m_SMOOTHABER = aber;
}

double Bool_Engine::GetSmoothAber()
{
	return m_SMOOTHABER;
}

void Bool_Engine::SetMaxlinemerge(double maxline)
{
	m_MAXLINEMERGE = maxline;
}

double Bool_Engine::GetMaxlinemerge()
{
	return m_MAXLINEMERGE;
}

void Bool_Engine::SetWindingRule(bool rule)
{
	m_WINDINGRULE = rule;
}

bool Bool_Engine::GetWindingRule()
{
	return m_WINDINGRULE;
}


void Bool_Engine::SetInternalMarge( B_INT marge )
{
	m_MARGE = (double)marge/m_GRID/m_DGRID;
}

B_INT Bool_Engine::GetInternalMarge()
{
	return (B_INT) ( m_MARGE*m_GRID*m_DGRID );
}

double Bool_Engine::GetInternalCorrectionAber()
{
	return  m_CORRECTIONABER*m_GRID*m_DGRID;
}

double Bool_Engine::GetInternalCorrectionFactor()
{
	return m_CORRECTIONFACTOR*m_GRID*m_DGRID;
}

double Bool_Engine::GetInternalSmoothAber()
{
	return m_SMOOTHABER*m_GRID*m_DGRID;
}

B_INT Bool_Engine::GetInternalMaxlinemerge()
{
	return (B_INT) ( m_MAXLINEMERGE*m_GRID*m_DGRID );
}

bool Bool_Engine::Do_Operation(BOOL_OP operation)
{
	switch (operation)
	{
	case (BOOL_OR):
	case (BOOL_AND):
	case (BOOL_EXOR):
	case (BOOL_A_SUB_B):
	case (BOOL_B_SUB_A):
		m_graphlist->Boolean(operation);
		break;
	case (BOOL_CORRECTION):
		m_graphlist->Correction();
		break;
	case (BOOL_MAKERING):
		m_graphlist->MakeRings();
		break;
	case (BOOL_SMOOTHEN):
		m_graphlist->Smoothen( GetInternalSmoothAber() );
		break;
	default:
		{
			error("Wrong operation","Command Error");
			return false;
		}
	}
	return true;
}

bool Bool_Engine::StartPolygonAdd(kbGroupType A_or_B)
{
	if (m_GraphToAdd != NULL)
		return false;

	Graph *myGraph = SDK_NEW Graph();
	m_graphlist->insbegin(myGraph);
	m_GraphToAdd = myGraph;
	m_groupType = A_or_B;

	return true;
}

bool Bool_Engine::AddPoint(double x, double y)
{
	if (m_GraphToAdd == NULL){return false;}

	B_INT rintx = ((B_INT) (x * m_DGRID)) * m_GRID;
	B_INT rinty = ((B_INT) (y * m_DGRID)) * m_GRID;
	//   Node *myNode = new Node( rintx*m_GRID, rinty*m_GRID );
	Node *myNode = SDK_NEW Node( rintx, rinty );

	// adding first point to graph
	if (m_firstNodeToAdd == NULL)
	{
		m_firstNodeToAdd = (Node *) myNode;
		m_lastNodeToAdd  = (Node *) myNode;
	}
	else
	{
		m_GraphToAdd->AddLink(m_lastNodeToAdd, myNode);
		m_lastNodeToAdd = (Node *) myNode;
	}

	return true;
}

bool Bool_Engine::EndPolygonAdd()
{
	if (m_GraphToAdd == NULL) {return false;}

	m_GraphToAdd->AddLink(m_lastNodeToAdd, m_firstNodeToAdd);
	m_GraphToAdd->SetGroup(m_groupType);
	m_GraphToAdd = NULL;
	m_lastNodeToAdd  = NULL;
	m_firstNodeToAdd = NULL;

	return true;
}

bool Bool_Engine::StartPolygonGet()
{
	if (!m_graphlist->empty())
	{
		m_getGraph = (Graph*) m_graphlist->headitem();
		m_getLink  = m_getGraph->GetFirstLink();
		m_getNode  = m_getLink->GetBeginNode();
		m_numPtsInPolygon = m_getGraph->GetNumberOfLinks();
		m_numNodesVisited = 0;
		return true;
	} 
	else
	{
		return false;
	}
}

bool Bool_Engine::PolygonHasMorePoints()
{
	// see if first point
	if (m_numNodesVisited == 0)
	{
		// don't need to touch the m_getNode
		m_numNodesVisited++;
		return true;
	}

	if (m_numNodesVisited < m_numPtsInPolygon)
	{
		// traverse to the next node
		m_getNode = m_getLink->GetOther(m_getNode);
		m_getLink = m_getLink->Forth(m_getNode);

		m_numNodesVisited++;
		return true;
	}
	else
	{
		return false;
	}
}

void Bool_Engine::EndPolygonGet()
{
	m_graphlist->removehead();
	delete m_getGraph;
}

double Bool_Engine::GetPolygonXPoint()
{
	return m_getNode->GetX()/m_GRID/m_DGRID;
}

double Bool_Engine::GetPolygonYPoint()
{
	return m_getNode->GetY()/m_GRID/m_DGRID;
}

bool Bool_Engine::GetHoleSegment()
{
	if (m_getLink->IsHoleMarked())
		return true;
	return false;
}

bool Bool_Engine::GetHoleConnectionSegment()
{
	if (m_getLink->GetHoleLink())
		return true;
	return false;
}

kbEdgeType Bool_Engine::GetPolygonPointEdgeType()
{
	// see if the point is the beginning of a false edge
	if ( m_getLink->GetHoleLink() )
		return KB_FALSE_EDGE;
	else
		// it's either an outside or inside edge
		if ( m_getLink->IsHoleMarked() )
			return KB_INSIDE_EDGE;
		else
			return KB_OUTSIDE_EDGE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// graph.cpp
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// Prototype of function
Sint32 linkXYsorter(KBoolLink *, KBoolLink *);
Sint32 linkYXsorter(KBoolLink *, KBoolLink *);
Sint32 linkLsorter(KBoolLink *, KBoolLink *);
Sint32 linkYXtopsorter(KBoolLink *a, KBoolLink *b);
Sint32 linkGraphNumsorter(KBoolLink *_l1, KBoolLink* _l2);

// constructor, initialize with one link
// usage: Graph *a_graph = new Graph(a_link);
Graph::Graph(KBoolLink *a_link )
{
	_linklist=SDK_NEW DL_List<void*>();

	_linklist->insbegin(a_link);
	_bin = false;

}


// constructor, initialize graph with no contents
// usage: Graph *a_graph = new Graph();
Graph::Graph()
{
	_linklist=SDK_NEW DL_List<void*>();
	_bin = false;
}


// destructor
// deletes all object of the linklist
Graph::~Graph()
{
   {
      TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);

      //first empty the graph
      _LI.delete_all();
   }

   delete _linklist;
}

KBoolLink*	Graph::GetFirstLink()
{
   return (KBoolLink*) _linklist->headitem();
};


void Graph::Prepare()
{
	ACTIVE_BoolEng->SetState("Intersection");

	CalculateCrossings(ACTIVE_BoolEng->GetInternalMarge());

//WHY
//	Round(ACTIVE_BoolEng->Get_Grid());

   {
   	TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
		_LI.foreach_mf(&KBoolLink::UnMark);// Reset Bin and Mark flag
   }
	ACTIVE_BoolEng->SetState("Set group A/B Flags");

   if (ACTIVE_BoolEng->GetWindingRule())
	   ScanGraph2(INOUT);
   ScanGraph2(GENLR);

//	writegraph();

	ACTIVE_BoolEng->SetState("Set operation Flags");
	Set_Operation_Flags();

	ACTIVE_BoolEng->SetState("Remove doubles");
	// Remove the marked links
   {
   	TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
      _LI.tohead();
      while(!_LI.hitroot())
      {
         if (_LI.item()->IsMarked())
         {
            delete _LI.item();
            _LI.remove();
         }
         else
            _LI++;
      }
   }

	ACTIVE_BoolEng->SetState("Remove inlinks");
	Remove_IN_Links();


	ACTIVE_BoolEng->SetState("Finished prepare graph");
}



// x and y of the point will be rounded to the nearest
// xnew=N*grid and ynew=N*grid
void Graph::Round(B_INT grid)
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
	while (!_LI.hitroot())
	{
			_LI.item()->GetBeginNode()->Round(grid);
			_LI.item()->GetEndNode()->Round(grid);
			_LI++;
	}
}

/*
//wrapper
static void Link_Reset_flags(KBoolLink* a_link)
{
  a_link->Reset_flags();
}
foreach_f(Link_Reset_flags);
*/

// rotate graph minus 90 degrees or plus 90 degrees
void Graph::Rotate(bool plus90)
{
	B_INT swap;
	Node* last=NULL;

   B_INT neg=-1;
   if (plus90)
      neg=1;

   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.mergesort(linkXYsorter);

	_LI.tohead();
	while (!_LI.hitroot())
	{
			if (_LI.item()->GetBeginNode() != last)
			{
				swap=_LI.item()->GetBeginNode()->GetX();
				_LI.item()->GetBeginNode()->SetX(-neg*(_LI.item()->GetBeginNode()->GetY()));
				_LI.item()->GetBeginNode()->SetY(neg*swap);
				last=_LI.item()->GetBeginNode();
			}
			_LI++;
	}
}

bool Graph::RemoveNullLinks()
{
	bool graph_is_modified = false;

   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
	while (!_LI.hitroot())
	{
		if (_LI.item()->GetBeginNode() == _LI.item()->GetEndNode())
		{
			_LI.item()->MergeNodes(_LI.item()->GetBeginNode());
			delete _LI.item();
			_LI.remove();
			graph_is_modified = true;
		}
		else
		  _LI++;
	}
	return (graph_is_modified);
}

// Add a link to the graph connection with
// other links is through the link his nodes
void Graph::AddLink(KBoolLink *a_link)
{
	VWFC_ASSERT(a_link);

	_linklist->insend(a_link);
}


// Add a link to the graph, by giving it two nodes
// the link is then made and added to the graph
void Graph::AddLink(Node *begin, Node *end)
{
	 VWFC_ASSERT(begin && end);
	 VWFC_ASSERT(begin != end);
	 AddLink(SDK_NEW KBoolLink(0, begin, end));
}


// Checks if there is a zeroline in the graph
bool Graph::AreZeroLines(B_INT Marge)
{
	bool Found_it = false;

   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
	while (!_LI.hitroot())
	{
		if (_LI.item()->IsZero(Marge))
		{
			Found_it = true;
			break;
		}
		_LI++;
	}
	return Found_it;
}


// Delete links that do not fit the condition for given operation
void Graph::DeleteNonCond(BOOL_OP operation)
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
	while(!_LI.hitroot())
	{
		if ( !_LI.item()->IsMarked(operation))
		{
			delete _LI.item();
			_LI.remove();
		}
		else
			_LI++;
	}
}

// All lines in the graph wich have a length < ACTIVE_BoolEng->Get_Marge() will be deleted
//
// input : a marge, standard on ACTIVE_BoolEng->Get_Marge()
// return: true if lines in the graph are deleted
//       : false if no lines in the graph are deleted
bool Graph::DeleteZeroLines(B_INT Marge)
{
	// Is the graph modified ?
	bool Is_Modified = false;
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);

	Sint32 Processed = _LI.count();

	_LI.tohead();
	while (Processed > 0)
	{
		Processed--;
		if (_LI.item()->IsZero(Marge))
		{
			// the current link is zero, so make from both nodes one node
			// and delete the current link from this graph
			_LI.item()->MergeNodes(_LI.item()->GetBeginNode());
			// if an item is deleted the cursor of the list is set to the next
			// so no explicit forth is needed
			delete _LI.item();
			_LI.remove();
			// we have to set Processed, because if a zero line is deleted
			// another can be made zero by this deletion
			Processed = _LI.count();
			Is_Modified = true;
			if (_LI.hitroot())
				_LI.tohead();
		}
		else
			_LI++;
			if (_LI.hitroot())
				_LI.tohead();
	}
	return Is_Modified;
}


// Collects a graph starting at currentnode or attached link
// follow graphs right around.
// since the input node is always a topleft node, we can see on
// a connected link if we or dealing with a hole or NON hole.
// for instance a top link of a hole that is horizontal, always
// is IN above the link and OUT underneath the link.
// this for a non hole the opposite
// if called with detecthole=false normally there should not be more
// then 2 links connected to each node, because holes are already
// connected in the right order at that moment
void Graph::CollectGraph(Node *current_node,BOOL_OP operation, bool detecthole,Sint32 graphnumber, bool& foundholes )
{
	KBoolLink *currentlink;
	KBoolLink *nextlink;
	Node *next_node;
	Node *MyFirst;
	Node *Unlinked;
	KBoolLink *MyFirstlink;

	bool Hole;
	LinkStatus whatside;

	currentlink=current_node->GetNotFlat();
	if (!currentlink)
   {
      char buf[100];
      if (detecthole)
	      sprintf(buf,"no NON flat link Collectgraph for operation at %15.3lf , %15.3lf",
         				(double) current_node->GetX(), (double) current_node->GetY());
      else
	      sprintf(buf,"no NON flat link Collectgraph at %15.3lf , %15.3lf",
         				(double) current_node->GetX(), (double) current_node->GetY());
		throw Bool_Engine_Error(buf, "Error", 9, 0);
	}

	currentlink->SetBeenHere();

   if (detecthole)
		Hole = currentlink->IsHole(operation);
   else
      Hole = false; //simple extract do not detect holes.

   currentlink->Redirect(current_node);

   foundholes = Hole || foundholes;

	//depending if we have a hole or not
	//we take the left node or right node from the selected link (currentlink)
	//this MEANS for holes go left around and for non holes go right around
   //since the currentlink is already set to binhere, it will not go in that direction
	if (Hole)
	{
      whatside = IS_LEFT;
	   if ( currentlink->GetEndNode()->GetX() > current_node->GetX())
		   current_node=currentlink->GetEndNode();
	}
	else
	{
      whatside = IS_RIGHT;
	   if ( currentlink->GetEndNode()->GetX() < current_node->GetX())
			current_node=currentlink->GetEndNode();
	}
   currentlink->Redirect(current_node);
   MyFirst=current_node; //remember this as the start
   MyFirstlink=currentlink;

	next_node = currentlink->GetEndNode();

	// If this is a hole, Set as special link, this is the top link of this hole !
	// from this link we have to make links to the link above later on.
	if (Hole)
		currentlink->SetTopHole(true);
   //set also the link as being part of a hole
   if (detecthole)
		currentlink->SetHole(Hole);
	currentlink->SetGraphNum(graphnumber);

	// Walk over links and redirect them. taking most right links around
	while (currentlink != NULL)
	{
      //if ( Hole )
		   nextlink = next_node->GetMost(currentlink,IS_RIGHT);
      //else
		//   nextlink = next_node->GetMost(currentlink,IS_LEFT);

		//for god sake try this
		if (nextlink == NULL)
		{	//END POINT MUST BE EQAUL TO BEGIN POINT
			if (!next_node->Equal(MyFirst, 1))
			{
				ACTIVE_BoolEng->info("no next (endpoint != beginpoint)","graph");
				nextlink = next_node->GetMost(currentlink,whatside);
			}
		}

		current_node = next_node;

		if (nextlink!=NULL)
		{
		   nextlink->Redirect(current_node);
			nextlink->SetBeenHere();
			next_node = nextlink->GetEndNode();

         if ( current_node->GetNumberOfLinks() > 2)
         {  // replace endnode of currentlink and beginnode of nextlink with new node
            Unlinked = SDK_NEW Node(current_node);
				currentlink->Replace(current_node,Unlinked);
				nextlink->Replace(current_node,Unlinked);
         }

		   if (detecthole)
				nextlink->SetHole(Hole);
			nextlink->SetGraphNum(graphnumber);
		}
      else
      {
         //close the found graph properly
         if ( current_node->GetNumberOfLinks() > 2)
         {  // replace endnode of currentlink and beginnode of nextlink with new node
            Unlinked = SDK_NEW Node(current_node);
            currentlink->Replace(current_node,Unlinked);
            MyFirstlink->Replace(current_node,Unlinked);
         }
      }

		currentlink = nextlink;
	}

	//END POINT MUST BE EQAUL TO BEGIN POINT
	if (!current_node->Equal(MyFirst, 1))
   {
		ACTIVE_BoolEng->info("problem","graph");
   }
//      throw GDS_Error("in collect graph endpoint != beginpoint"
//						, "Error", 9, 0);
}

//==============================================================================
//==============================================================================

// Extract bi-directional graphs from this graph
// Mark the graphs also as being a hole or not.
void Graph::Extract_Simples(BOOL_OP operation, bool detecthole, bool& foundholes )
{
	TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	if (_LI.empty()) return;
	Node *begin;
   Sint32 graphnumber=1;

	_LI.foreach_mf(&KBoolLink::UnMark);//reset bin and mark flag of each link
	_LI.mergesort(linkYXtopsorter);
   _LI.tohead();
	while (true)
	{
		begin = GetMostTopLeft(&_LI); // from all the most Top nodes,
												// take the most left one
												// to most or not to most, that is the question
		if (!begin)
			break;

		try // collect the graph
		{
				CollectGraph( begin,operation,detecthole,graphnumber++, foundholes );
		}
		catch (Bool_Engine_Error& error)
		{
			//ACTIVE_BoolEng->info(error.GetErrorMessage(), "error");
			throw error;
		}
	}
}

void Graph::Split(GraphList* partlist)
{
	TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	if (_LI.empty()) return;

	Graph *part;
   Sint32 graphnumber=0;

   //sort the graph on graphnumber
	_LI.mergesort(linkGraphNumsorter);

   _LI.tohead();
	while (!_LI.hitroot())
	{  if (graphnumber != _LI.item()->GetGraphNum())
      {
         graphnumber=_LI.item()->GetGraphNum();
			part = SDK_NEW Graph();
			partlist->insend(part);
      }
      KBoolLink* tmp=_LI.item();
      _LI.remove();
      part->AddLink(tmp);
	}
}

bool Graph::GetBeenHere()
{
	return _bin;
}

// return total number of links in this graph
Sint32 Graph::GetNumberOfLinks()
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	return _LI.count();
}

//for all operations set the operation flags for the links
//based on the Group_Left_Right values
void Graph::Set_Operation_Flags()
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
	while(!_LI.hitroot())
	{
	  _LI.item()->SetLineTypes();
	  _LI++;
	}
}

//  Remove unused (those not used for any operation) links
void Graph::Remove_IN_Links()
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
	for (Sint32 t = _LI.count() ; t > 0; t--)
	{
		// Is this link not used for any operation?
		if (_LI.item()->IsUnused())
		{
			delete _LI.item();
			_LI.remove();
		}
		else
			_LI++;
	}
}

void Graph::ReverseAllLinks()
{
	Node *dummy;
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
	while (!_LI.hitroot())
	{
		// swap the begin- and endnode of the current link
		dummy = _LI.item()->GetBeginNode();
		_LI.item()->SetBeginNode(_LI.item()->GetEndNode());
		_LI.item()->SetEndNode(dummy);
		_LI++;
	}
}

void Graph::SetBeenHere(bool value)
{
	_bin=value;
}

// ReSet the flags  of the links
void Graph::Reset_flags()
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.foreach_mf(&KBoolLink::Reset_flags);
}

// ReSet the bin and mark flag of the links
void Graph::Reset_Mark_and_Bin()
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.foreach_mf(&KBoolLink::UnMark);//reset bin and mark flag of each link
}

// Set the group of the links to the same as newgroup
void Graph::SetGroup(kbGroupType newgroup)
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
	while (!_LI.hitroot())
	{
		_LI.item()->SetGroup(newgroup);
		_LI++;
	}
}


// Set the number of the links to the same as newnr
void Graph::SetNumber(const Sint32 newnr)
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
	while (!_LI.hitroot())
	{
		_LI.item()->SetGraphNum(newnr);
		_LI++;
	}
}


// This function will simplify a graph with the following rules
//
// This are the rules for symplifying the graphs
// 1. The following point is the same as the current one
// 2. The point after the following point is the same as the current one
// 3. The point after the following point lies on the same line as the current
//
// input : a marge
// return: true if graph is modified
// 		: false if graph is NOT simplified
bool Graph::Simplify( B_INT Marge )
{
	bool graph_is_modified = false;
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	Sint32 Processed = _LI.count();

	_LI.foreach_mf(&KBoolLink::UnMark);//reset bin and mark flag of each link

	_LI.tohead();
	kbGroupType mygroup=_LI.item()->Group();

	// All items must be processed
	while (Processed > 0)
	{
		// Gives the number of items to process
		Processed--;
		// Check if line is marked
		// Links will be marked during the process
		if (_LI.item()->IsMarked())
		{
			delete _LI.item();
			_LI.remove();
			graph_is_modified = true;
			Processed = _LI.count();
			if (_LI.hitroot())
				_LI.tohead();
			continue;
		}

		// Line is not marked, check if line is zero
		if (_LI.item()->IsZero(Marge))
		{
			_LI.item()->MergeNodes(_LI.item()->GetBeginNode());
			delete _LI.item();
			_LI.remove();
			graph_is_modified = true;
			Processed = _LI.count();
			if (_LI.hitroot())
				_LI.tohead();
			continue;
		}

		// begin with trying to simplify the link
		{
			// Line is not marked, not zero, so maybe it can be simplified
			bool virtual_link_is_modified;
			Node *new_begin, *new_end, *a_node;
			KBoolLink *a_link;

			_LI.item()->Mark();
			new_begin = _LI.item()->GetBeginNode();
			new_end   = _LI.item()->GetEndNode();

			// while virtual link is modified
			do
			{
				virtual_link_is_modified = false;
				// look in the previous direction
				if ((a_link = new_begin->GetPrevLink()) != NULL)
				{
					a_node = a_link->GetBeginNode();
					if (a_node->Simplify(new_begin,new_end,Marge))
					{
						new_begin->GetPrevLink()->Mark();
						new_begin = a_node;
						virtual_link_is_modified = true;
					}
				}
				// look in the next direction
				if ((a_link = new_end->GetNextLink()) != NULL)
				{
					a_node = a_link->GetEndNode();
					if (a_node->Simplify(new_begin,new_end,Marge))
					{
						new_end->GetNextLink()->Mark();
						new_end = a_node;
						virtual_link_is_modified = true;
					}
				}
				graph_is_modified = (bool) (graph_is_modified || virtual_link_is_modified);
			} while (virtual_link_is_modified);

			// was the link simplified
			if ((_LI.item()->GetBeginNode() != new_begin) ||
				(_LI.item()->GetEndNode() != new_end))
			{
				// YES !!!!!
				Sint32 number = _LI.item()->GetGraphNum();
				delete _LI.item();
				_LI.remove();

            if (_LI.hitroot())
               _LI.tohead();

				KBoolLink *newlink = SDK_NEW KBoolLink(number, new_begin, new_end);
				newlink->SetGroup(mygroup);

				_LI.insend(newlink);
				Processed = _LI.count();
				graph_is_modified = true;
				continue;
			}
			_LI.item()->UnMark();
		}	// end of try to simplify
		_LI++;
		if (_LI.hitroot())
			_LI.tohead();
	}//end while all processed

	return graph_is_modified;
}

/*
// This function will smoothen a graph with the following rules
//
// 0.	Process graphs with more than 3 links only. (while more than 3)
//		Otherwise some objects may end-up as lines or disappear completely.
// 1.
// 	a. ?  Does begin-node lay on line(prevline.beginnode,endnode)
//    	->  merge beginnode to endnode
// 	b. ?  Does end-node lay on line(beginnode,nextline.endnode)
//   		->  merge endnode to beginnode
// 2.
//		a. ?  Is distance between prevline.beginnode and endnode to short
//   		->  merge beginnode to endnode
//	 	b.	?  Is distance between beginnode and nextline.endnode to short
//   		->  merge endnode to beginnode
// 3.
//		a. ?  Does (this)beginnode lay in area of nextline
//				AND does cross-node lay on nextline
//			->   move endnode to crossing of prevline and nextline
//		b. ?  Does (this)endnode lay in area of prevline
//				AND does cross-node lay on prevline
//			->   move beginnode to crossing of prevline and nextline
// 4.
//		?  Is this link too short
//			?  Is prevline shorter than nextline
//		   Y ->  ?  Is prevlink shorter than maxlength
//					->  merge endnode to beginnode
//		   N ->  ?  Is nextlink shorter than maxlength
//					->  merge endnode to beginnode
//
//
//	Types of glitches / lines to remove :
//
//    \         /      \   		/							\         /
//		 Z---A---B	 OR 	Z-------B---A				=> 	 Z-------B
//
//	  (1)
//
//	  ----A   	C----										=>		----A-----C----
//			 \   /
//	  (2)   \ /
//		      B
//
//	  ---Z                                        		---Z
//	      \                                                \
//	  (3)  \                                                \
//	        \   B----------C--							=>          A---B----------C--
//          \ /
//           A
//
//	  --Z---A                                          --Z__
//          \                                              -__
//	  (4)     B------------C--							=>            B------------C--
//
//	linkLsorter(L1,L2)
//		ret:
//			+1		L1 <	L2
//			 0		L1 ==	L2
//			-1		L1 >	L2
//
*/
bool Graph::Smoothen( B_INT Marge )
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	if (_LI.count()<=3)	// Don't modify it
		return false;

	Node *Z, *A, *B, *C, *cross_node = SDK_NEW Node;
	KBoolLink *prevlink, *nextlink, *thislink;
	KBoolLine	prevline,  nextline,  thisline;
	KBoolLine	prevhelp,  nexthelp;

	KBoolLink  LZB(SDK_NEW Node, SDK_NEW Node),
			LAC(SDK_NEW Node, SDK_NEW Node);

	double distance=0;
   double prevdist,nextdist;

	bool doprev, donext;
	bool graph_is_modified = false;
	bool kill = false;	// for first instance

	_LI.tohead();
	Sint32 todo = _LI.count();
	thislink=_LI.item();
	B = thislink->GetEndNode();
	nextlink = thislink->Forth(B);

	// Type 1
	while (todo>0)
	{
		if (kill==true)
		{
			// remove link from graph
			_LI.toitem(thislink);
			graph_is_modified = true;
			delete _LI.item();
			_LI.remove();
			kill=false;
			thislink=nextlink;
			todo--;
			if (_LI.count()<3)
				break;
		}

		A = thislink->GetBeginNode();
		B = thislink->GetEndNode();

		if (A->ShorterThan(B,1))
		{
			A->Merge(B);
			kill = true;
			continue;
		}

		Z = thislink->Forth(A)->GetBeginNode();
		C = thislink->Forth(B)->GetEndNode();
		thisline.Set(thislink);
		thisline.CalculateLineParameters();
		nextlink = thislink->Forth(B);

		if (thisline.PointInLine(Z,distance,0.0) == ON_AREA)
		{	// Z--A--B	=>		Z--B							Merge this to previous
			thislink->MergeNodes(B);	// remove A
			kill = true;
			continue;
		}
		else if (thisline.PointInLine(C,distance,0.0) == ON_AREA)
		{	// A--B--C	=>		A--C							Merge this to next
			thislink->MergeNodes(A);	//	remove B
			kill = true;
			continue;
		}

		thislink=nextlink;
		todo--;
	}

	kill=false;
	todo = _LI.count();
	_LI.mergesort(linkLsorter);
	_LI.tohead();

	while (todo>0)
	{
		if (kill==true)
		{
			delete _LI.item();
			_LI.remove();
			graph_is_modified = true;
			kill = false;
			//mergesort(linkLsorter);
			_LI.mergesort(linkLsorter);
			_LI.tohead();
			todo = _LI.count();
			if (todo<3)		// A polygon, at least, has 3 sides
				break;
		}

		// Keep this order!
		thislink = _LI.item();
		A = thislink->GetBeginNode();
		B = thislink->GetEndNode();
		prevlink = thislink->Forth(A);
		nextlink = thislink->Forth(B);
		Z = prevlink->GetBeginNode();
		C = nextlink->GetEndNode();

		if (A->ShorterThan(B,1))
		{
			A->Merge(B);
			kill = true;
			continue;
		}

		prevline.Set(prevlink);
		prevline.CalculateLineParameters();
		nextline.Set(nextlink);
		nextline.CalculateLineParameters();

		// Type 2
		if (B->ShorterThan(Z,Marge))
		{	// Z--A--B	=>		Z--B							Merge this to previous
			thislink->MergeNodes(B);	// remove A
			kill = true;
			continue;
		}
		else if (A->ShorterThan(C,Marge))
		{	// A--B--C	=>		A--C							Merge this to next
			thislink->MergeNodes(A);	//	remove B
			kill = true;
			continue;
		}


		*LZB.GetBeginNode()=*Z;
		*LZB.GetEndNode()=*B;
		*LAC.GetBeginNode()=*A;
		*LAC.GetEndNode()=*C;
		prevhelp.Set(&LZB);
		nexthelp.Set(&LAC);
		prevhelp.CalculateLineParameters();
		nexthelp.CalculateLineParameters();


		//	Type 4
		doprev = bool(prevhelp.PointInLine(A,prevdist,(double)Marge) == IN_AREA);
		donext = bool(nexthelp.PointInLine(B,nextdist,(double)Marge) == IN_AREA);
		doprev = bool(B->ShorterThan(Z,ACTIVE_BoolEng->GetInternalMaxlinemerge()) && doprev);
		donext = bool(A->ShorterThan(C,ACTIVE_BoolEng->GetInternalMaxlinemerge()) && donext);

		if (doprev && donext)
		{
			if (fabs(prevdist)<=fabs(nextdist))
				thislink->MergeNodes(B);	// remove A
			else
				thislink->MergeNodes(A);	// remove B

			kill = true;
			continue;
		}
		else if (doprev)
		{
			thislink->MergeNodes(B);	// remove A
			kill = true;
			continue;
		}
		else if (donext)
		{
			thislink->MergeNodes(A);	// remove B
			kill = true;
			continue;
		}


		thisline.Set(thislink);
		thisline.CalculateLineParameters();

		// Type 1
		if (thisline.PointInLine(Z,distance,0.0) == ON_AREA)
		{	// Z--A--B	=>		Z--B							Merge this to previous
			thislink->MergeNodes(B);	// remove A
			kill = true;
			continue;
		}
		else if (thisline.PointInLine(C,distance,0.0) == ON_AREA)
		{	// A--B--C	=>		A--C							Merge this to next
			thislink->MergeNodes(A);	//	remove B
			kill = true;
			continue;
		}


		// Type 3
		if (nextline.PointInLine(A,distance, (double) Marge)==IN_AREA)
		{
			if (nextline.Intersect2(cross_node,&prevline))
			{
				if (nextline.PointInLine(cross_node,distance,0.0)==IN_AREA)
				{
					B->Set(cross_node);
					thislink->MergeNodes(B);	// remove A
					kill=true;
					continue;
				}
				else
				{
					thislink->MergeNodes(A);	// remove B
					kill=true;
					continue;
				}
			}
			else
			{
				thislink->MergeNodes(A);	// remove B
				kill=true;
				continue;
			}
		}

		// Type 3
		if (prevline.PointInLine(B,distance,(double)Marge)==IN_AREA)
		{
			if (prevline.Intersect2(cross_node,&nextline))
			{
				if (prevline.PointInLine(cross_node,distance,0.0)==IN_AREA)
				{
					A->Set(cross_node);
					thislink->MergeNodes(A);	// remove B
					kill=true;
					continue;
				}
				else
				{
					thislink->MergeNodes(B);	// remove A
					kill=true;
					continue;
				}
			}
			else
			{
				thislink->MergeNodes(B);	// remove A
				kill=true;
				continue;
			}
		}

		todo--;
		_LI++;
	}	// end: while all processed

	delete cross_node;

	return graph_is_modified;
}


// Give the graphnumber of the first link in the graphlist
Sint32 Graph::GetGraphNum()
{
	return ((KBoolLink*)_linklist->headitem())->GetGraphNum();
}


// get the node with the highest Y value
Node* Graph::GetTopNode()
{
	B_INT max_Y = MAXB_INT;
	Node* result;

   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);

	_LI.tohead();
	while (!_LI.hitroot())
	{
		if (!(_LI.item()->GetBeginNode()->GetY() < max_Y))
			 break;
		_LI++;
	}
	result = _LI.item()->GetBeginNode();

	return result;
}

// THE GRAPH MUST be SORTED before using this function
//	mergesort(linkYXtopsorter);
// Get the mostleft top node from the graph  for which the link flag is not set yet
Node*	Graph::GetMostTopLeft(TDLI<KBoolLink>* _LI)
{
	while (!_LI->hitroot())
	{
		if (!_LI->item()->BeenHere())
      {
         KBoolLink* a=_LI->item();
         //find the top node of this link (sorted on top allready)
         if (a->GetBeginNode()->GetY() > a->GetEndNode()->GetY())
				return(a->GetBeginNode());
         if (a->GetBeginNode()->GetY() < a->GetEndNode()->GetY())
   			return(a->GetEndNode());
         else
   			return(a->GetBeginNode());
      }
		(*_LI)++;
	}
	return NULL;
}

// Take the linkslist over from a other graph
// The linklist of the other graph will be empty afterwards
void Graph::TakeOver(Graph *other)
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.takeover( other->_linklist);
}

// calculate crossing with scanbeams   
void Graph::CalculateCrossings(B_INT Marge)
{
	// POINT <==> POINT
	ACTIVE_BoolEng->SetState("Node to Node");

	Merge_NodeToNode(Marge);

	if (_linklist->count() < 3)
		  return;


	// POINT <==> LINK
	ACTIVE_BoolEng->SetState("Node to KBoolLink 0");

   ScanGraph2(NODELINK);

	ACTIVE_BoolEng->SetState("Rotate -90");
	Rotate(false);


	ACTIVE_BoolEng->SetState("Node to KBoolLink -90");
   ScanGraph2(NODELINK);

	ACTIVE_BoolEng->SetState("Rotate +90");
	Rotate(true);

	// LINK <==> LINK
	ACTIVE_BoolEng->SetState("intersect");

   ScanGraph2(LINKLINK);

/*
   if (!checksort())
   { {
	   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
		_LI.mergesort(linkXYsorter);
     }
	  writeintersections();
	  writegraph(true);
   }
*/

//	Rotate(false);
//	ACTIVE_BoolEng->SetState("KBoolLink to KBoolLink -90");
//   ScanGraph2(LINKLINK);
//	Rotate(true);

//   writegraph(true);

	ACTIVE_BoolEng->SetState("Node to Node");

	Merge_NodeToNode(Marge);
//   writegraph(true);

	if (_linklist->count() < 3)
		  return;

}

// neem de nodes die binnen de margeafstand bij elkaar liggen samen	RICHARD
Sint32 Graph::Merge_NodeToNode(B_INT Marge)
{
	//aantal punten dat verplaatst is
	Sint32 merges = 0;
   {
      TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);

      //unmark all links; markflag wordt gebruikt om aan te geven
      //of een link (eigenlijk beginnode ervan) al verwerkt is
      _LI.foreach_mf(&KBoolLink::UnMark);

      //sort links on x value of beginnode
      _LI.mergesort(linkXYsorter);

      //extra iterator voor doorlopen links in graph
      {
      TDLI<KBoolLink> 	links=TDLI<KBoolLink>(_linklist);

      Node *nodeOne, *nodeTwo;
      //verwerk alle links (alle (begin)nodes)
      for(_LI.tohead(); !_LI.hitroot(); _LI++)
      {
         nodeOne = _LI.item()->GetBeginNode();

         // link (beginnode) al verwerkt?
         if(!_LI.item()->IsMarked())
         {
            // wordt verwerkt dus markeer
            _LI.item()->Mark();

            // doorloop alle links vanaf huidige tot link buiten marge
            links.toiter(&_LI);links++;
            while (!links.hitroot())
            {
               nodeTwo = links.item()->GetBeginNode();

               // marked?
               if(!links.item()->IsMarked())
               {
                  // x van beginnode vd link binnen marge?
                  if(babs(nodeOne->GetX()-nodeTwo->GetX()) <= Marge )
                  {
                     // y van beginnode vd link binnen marge?
                     // zijn twee node-object referenties wel verschillend?
                     if(babs(nodeOne->GetY()-nodeTwo->GetY()) <= Marge &&
                        (!(nodeOne == nodeTwo))
                       )
                     {
                        links.item()->Mark();
                        nodeOne->Merge(nodeTwo);
                        merges++;
                     }//y binnen marge en niet zelfde node
                  }//x binnen marge?
                  else
                  {
                     // link valt buiten marge; de rest vd links
                     // dus ook (omdat lijst gesorteerd is)
                     links.totail();
                  }
               }//marked?
               links++;
            }//current -> ongeldig
         }//verwerkt?
      }//all links

      }//om de extra iterator te verwijderen
   }
	RemoveNullLinks();

	return merges;
}


Sint32 Graph::ScanGraph2(SCANTYPE scantype)
{
   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
   Sint32 found=0;

	//sort links on x and y value of beginnode
	_LI.mergesort(linkXYsorter);

	writegraph( false );

	//bin flag is used in scanbeam so reset
   _LI.foreach_mf(&KBoolLink::SetNotBeenHere);

	ScanBeam* scanbeam = SDK_NEW ScanBeam();
   Node*  _low;
   Node*  _high;

   _LI.tohead();
   while (!_LI.attail())
   {
         _low = _LI.item()->GetBeginNode();
         //find new links for the new beam and remove the old links
         if (scanbeam->FindNew(scantype,&_LI))
            found++;

         //find a new low node, this should be a node not eqaul to the current _low
         do
         {  _LI++;}
         while (!_LI.hitroot() && (_low == _LI.item()->GetBeginNode()));
         if (_LI.hitroot())
            //if the last few links share the same beginnode
            //we arive here
            break;
         else
            _high=_LI.item()->GetBeginNode();

         scanbeam->SetType(_low,_high);

         if (scanbeam->RemoveOld(scantype,&_LI))
            found++;
   }

	delete scanbeam;
	return found;
}


/*

//      	scanbeam->writebeam();

      if (j%100 ==0)
      {
        Sint32 x;
        Sint32 y;
        char buf[80];
		   x=(Sint32)_lowlink->GetBeginNode()->GetX();
		   y=(Sint32)_lowlink->GetBeginNode()->GetY();
        sprintf(buf," x=%I64d , y=%I64d here %I64d",x,y,scanbeam->count());
			ACTIVE_BoolEng->SetState(buf);
      	scanbeam->writebeam();
      }



         writegraph(false);
            if (!checksort())
            {
               double x=_lowlink->GetBeginNode()->GetX();
               checksort();
            }



         _LI++;
      }
   }

	delete scanbeam;
	return 0;
}


         if (!checksort())
         {
            x=_lowlink->GetBeginNode()->GetX();
            checksort();
         }

         if (x >= -112200)
         {
//	         writegraph(true);
//	         scanbeam->writebeam();
         }
*/


//=============================== Global Functions =============================

// Sorts the links on the X values
Sint32 linkXYsorter(KBoolLink *a, KBoolLink* b)
{
	if ( a->GetBeginNode()->GetX() < b->GetBeginNode()->GetX())
		return(1);
	if ( a->GetBeginNode()->GetX() > b->GetBeginNode()->GetX())
		return(-1);
   //they are eqaul in x
	if ( a->GetBeginNode()->GetY() < b->GetBeginNode()->GetY())
		return(-1);
	if ( a->GetBeginNode()->GetY() > b->GetBeginNode()->GetY())
		return(1);
   //they are eqaul in y
	return(0);
}

// Sorts the links on the Y value of the beginnode
Sint32 linkYXsorter(KBoolLink *a, KBoolLink* b)
{
	if ( a->GetBeginNode()->GetY() > b->GetBeginNode()->GetY())
		return(1);
	if ( a->GetBeginNode()->GetY() < b->GetBeginNode()->GetY())
		return(-1);
	if ( a->GetBeginNode()->GetX() > b->GetBeginNode()->GetX())
		return(-1);
	if ( a->GetBeginNode()->GetX() < b->GetBeginNode()->GetX())
		return(1);
	return(0);
}


// The sort function for sorting graph from shortest to longest (_l1 < _l2)
Sint32 linkLsorter(KBoolLink *_l1, KBoolLink* _l2)
{
	B_INT dx1,dx2,dy1,dy2;
	dx1 = (_l1->GetEndNode()->GetX() - _l1->GetBeginNode()->GetX());
	dx1*=dx1;
	dy1 = (_l1->GetEndNode()->GetY() - _l1->GetBeginNode()->GetY());
	dy1*=dy1;
	dx2 = (_l2->GetEndNode()->GetX() - _l2->GetBeginNode()->GetX());
	dx2*=dx2;
	dy2 = (_l2->GetEndNode()->GetY() - _l2->GetBeginNode()->GetY());
	dy2*=dy2;

	dx1+=dy1;	dx2+=dy2;

	if ( dx1 > dx2 )
		return(-1);
	if ( dx1 < dx2 )
		return(1);
	return(0);
}

// The sort function for the links in a graph (a.topnode < b.topnode)
// if the two links lay with the top nodes on eachother the most left will be selected

Sint32 linkYXtopsorter(KBoolLink *a, KBoolLink *b)
{

	if (bmax(a->GetBeginNode()->GetY(),a->GetEndNode()->GetY()) < bmax(b->GetBeginNode()->GetY(),b->GetEndNode()->GetY()))
		return -1;

	if (bmax(a->GetBeginNode()->GetY(),a->GetEndNode()->GetY()) > bmax(b->GetBeginNode()->GetY(),b->GetEndNode()->GetY()))
		return 1;

	//equal
   if (bmin(a->GetBeginNode()->GetX(),a->GetEndNode()->GetX()) < bmin(b->GetBeginNode()->GetX(),b->GetEndNode()->GetX()))
	   return -1;

   if (bmin(a->GetBeginNode()->GetX(),a->GetEndNode()->GetX()) > bmin(b->GetBeginNode()->GetX(),b->GetEndNode()->GetX()))
		return 1;

	return 0;
}

// The sort function for sorting graph from shortest to longest (_l1 < _l2)
Sint32 linkGraphNumsorter(KBoolLink *_l1, KBoolLink* _l2)
{
	if ( _l1->GetGraphNum() > _l2->GetGraphNum())
		return(-1);
	if ( _l1->GetGraphNum() < _l2->GetGraphNum())
		return(1);
	return(0);
}

// Perform an operation on the graph
void Graph::Boolean(BOOL_OP operation,GraphList* Result)
{
	ACTIVE_BoolEng->SetState("Performing Operation");

	// At this moment we have one graph
	// step one, split it up in single graphs, and mark the holes
	// step two, make one graph again and link the holes
	// step three, split up again and dump the result in Result

	ACTIVE_BoolEng->SetState("Extract simples first ");
   DeleteNonCond(operation);

   bool foundholes = false;
	try
	{
		Extract_Simples(operation,true, foundholes);
	}
	catch (Bool_Engine_Error& /*error*/)
	{
		return;
	}

	// now we will link all the holes in de graphlist
	// By the scanbeam method we will search all the links that are marked
	//	as topleft link of a the hole polygon, when we find them we will get the
	//	closest link, being the one higher in the beam.
	//	Next we will create a link and nodes toceoonect the hole into it outside contour 
   // or other hole.
	ACTIVE_BoolEng->SetState("Linking Holes");

   if (_linklist->count() == 0)
      //extract simples did leaf an empty graph
      //so we are ready
      return;

   if ( foundholes )
   {
      //the first extract simples introduced nodes at the same location that are not merged.
      //e.g. Butterfly polygons as two seperate polygons.
      //The scanlines can not cope with this, so merge them, and later extract one more time.
      Merge_NodeToNode(0);

      //link the holes into the non holes if there are any.
      if (ScanGraph2(LINKHOLES))
      {
		   //to delete extra points
		   //those extra points are caused by link holes
         //and are eqaul
		   DeleteZeroLines(1);

		   ACTIVE_BoolEng->SetState("extract simples last");
		   Extract_Simples(operation,false, foundholes);
      }
   }

   //writegraph( false );
   Split(Result);
}

// Perform an correction on the graph
void Graph::Correction( GraphList* Result, double factor )
{

	// At this moment we have one graph
	// step one, split it up in single graphs, and mark the holes
	// step two, make one graph again and link the holes
	// step three, split up again and dump the result in Result
	ACTIVE_BoolEng->SetState("Extract simple graphs");

	//extract the (MERGE or OR) result from the graph
	if (Simplify(ACTIVE_BoolEng->GetGrid()))
		if (GetNumberOfLinks() < 3)
				return;

	Graph* original=SDK_NEW Graph();

   {
      if (_linklist->empty()) return;

      KBoolLink* _current = GetFirstLink();
		Node *_first = SDK_NEW Node(_current->GetBeginNode());
      Node *_last	 = _current->GetBeginNode();
      Node *_begin = _first;
      Node *_end   = _first;

		Sint32 _nr_of_points = GetNumberOfLinks();
		for (Sint32 i = 1; i < _nr_of_points; i++)
      {
 			// get the other node on the link
			_last = _current->GetOther(_last);
        // make a node from this point
         _end = SDK_NEW Node(_last);

         // make a link between begin and end
         original->AddLink(_begin, _end);

         _begin=_end;
 			_current = _current->Forth(_last);
      }

      // make a link between the _begin and the first to close the graph
      original->AddLink(_begin, _first);
   }

	SetNumber(1);
	SetGroup(GROUP_A);
	Prepare();
   DeleteNonCond(BOOL_OR);

   bool foundholes = false;
	Extract_Simples( BOOL_OR, true, foundholes );
   Split(Result);

	//Result contains the separate boundaries and holes

	ACTIVE_BoolEng->SetState("Create rings");
	//first create a ring around all simple graphs
   {
   	TDLI<Graph> IResult=TDLI<Graph>(Result);
      GraphList *_ring=SDK_NEW GraphList();
      {
         //put into one graphlist
         IResult.tohead();
         Sint32 i;
         Sint32 n=IResult.count();
         for (i=0;i<n;i++)
         {
           {
				  IResult.item()->MakeClockWise();
              IResult.item()->CreateRing_fast(_ring,fabs(factor));
      //			  IResult.item()->CreateRing(_ring,fabs(factor));
           }
           delete(IResult.item());
           IResult.remove();

            //move ring graphlist to result
            while (!_ring->empty())
            {
               //add to end
					((Graph*)_ring->headitem())->MakeClockWise();
               IResult.insend((Graph*)_ring->headitem());
               _ring->removehead();
            }
         }
      }
      delete _ring;

      //IResult contains all rings
      //prepare the graphs for extracting the links of a certain operation
      //set original graphlist to groupA and ring to groupB
      Sint32 i=2;
      IResult.tohead();
      while (!IResult.hitroot())
      {
        IResult.item()->Reset_flags();
        IResult.item()->SetGroup(GROUP_B);
        IResult.item()->SetNumber(i);
        i++;
        IResult++;
      }
   }

	TakeOver(original);
   Reset_flags();
   SetNumber(1);
   SetGroup(GROUP_A);
	Result->MakeOneGraph(this); // adds all graph its links to original
										  // Result will be empty afterwords


	//merge ring with original shapes for positive correction else subtract ring

	//calculate intersections etc.
	//SINCE correction will calculate intersections between
	//ring and original ACTIVE_BoolEng->Get_Marge() must be set a lot smaller then factor
	//during the rest of this routine
	//else wierd effects will be the result.
	double Backup_Marge = ACTIVE_BoolEng->GetMarge();

	if (ACTIVE_BoolEng->GetInternalMarge() > fabs(factor/100))
	{
      ACTIVE_BoolEng->SetInternalMarge( (B_INT) fabs(factor/100));
	   //less then 1 is usless since all coordinates are integers
	   if (ACTIVE_BoolEng->GetInternalMarge() < 1)
		   ACTIVE_BoolEng->SetInternalMarge(1);
	}


	Prepare();

	ACTIVE_BoolEng->SetState("Add/Substract rings");

	if (factor > 0)
		Boolean(BOOL_OR,Result);
	else
		Boolean(BOOL_A_SUB_B,Result);

	ACTIVE_BoolEng->SetMarge( Backup_Marge);
	//the result of the graph correction is in Iresult
   delete original;
}

// Perform an operation on the graph
void Graph::MakeRing( GraphList* Result, double factor )
{
	// At this moment we have one graph
	// step one, split it up in single graphs, and mark the holes
	// step two, make one graph again and link the holes
	// step three, split up again and dump the result in Result
	ACTIVE_BoolEng->SetState("Extract simple graphs");

	//extract the (MERGE or OR) result from the graph
	SetNumber(1);
	Prepare();

   DeleteNonCond(BOOL_OR);
   bool foundholes = false;
	Extract_Simples( BOOL_OR, true, foundholes );
   Split(Result);
	//Iresult contains the separate boundaries and holes
	//make a correction on the boundaries factor
	//make a correction on the holes -factor

	ACTIVE_BoolEng->SetState("Create rings");

   //first create a ring around all simple graphs
   TDLI<Graph> IResult=TDLI<Graph>(Result);
   GraphList *_ring=SDK_NEW GraphList();
   {
      IResult.tohead();
      Sint32 i;
      Sint32 n=IResult.count();
      for (i=0;i<n;i++)
      {
        {
  			   IResult.item()->MakeClockWise();
            IResult.item()->CreateRing_fast(_ring,fabs(factor));
        }
        delete(IResult.item());
        IResult.remove();

         //move ring graphlist to result
         while (!_ring->empty())
         {
            //add to end
				((Graph*)_ring->headitem())->MakeClockWise();
            IResult.insend((Graph*)_ring->headitem());
            _ring->removehead();
         }
      }
   }
	delete _ring;
}

//create a ring shapes on every edge of the graph
void Graph::CreateRing( GraphList *ring, double factor )
{
  TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
  _LI.tohead();
  while( !_LI.hitroot())
  {
	 Graph *shape=SDK_NEW Graph();
	 //generate shape around link
	 shape->Make_Rounded_Shape(_LI.item(),factor);
	 ring->insbegin(shape);
	 _LI++;
  }
}

//create a ring shapes on every edge of the graph
void Graph::CreateRing_fast( GraphList *ring, double factor )
{
	Node* begin;
	KBoolLink* currentlink;
	KBoolLine  currentline;

	KBoolLine  firstline;

	KBoolLink* nextlink;
	KBoolLine nextline;

   {
   	TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
		_LI.foreach_mf(&KBoolLink::UnMark);//reset bin and mark flag of each link
		_LI.mergesort(linkYXsorter);
	   _LI.tohead();

		begin = GetMostTopLeft(&_LI); // from all the most Top nodes,
											   // take the most left one
   }
	if (!begin)
		return;

	currentlink=begin->GetIncomingLink();
	currentline.Set(currentlink);
	currentline.CalculateLineParameters();

	nextlink=begin->GetOutgoingLink();
	nextline.Set(nextlink);
	nextline.CalculateLineParameters();

	firstline.Set(nextlink);
	firstline.CalculateLineParameters();

	while (nextlink)
	{
		Graph *shape=SDK_NEW Graph();
		{

			Node* _last_ins_left  =0;
			Node* _last_ins_right =0;

			currentline.Create_Begin_Shape(&nextline,&_last_ins_left,&_last_ins_right,factor,shape);

			while(true)
			{
				currentline=nextline;
				currentlink=nextlink;
				currentlink->SetBeenHere();

				nextlink=currentlink->GetEndNode()->Follow(currentlink);
				if (nextlink)
				{
					nextline.Set(nextlink);
					nextline.CalculateLineParameters();
					if (!currentline.Create_Ring_Shape(&nextline,&_last_ins_left,&_last_ins_right,factor,shape))
						break;
				}
				else
					break;
			}

			//finish this part
			if (nextlink)
				currentline.Create_End_Shape(&nextline,_last_ins_left,_last_ins_right,factor,shape);
			else
				currentline.Create_End_Shape(&firstline,_last_ins_left,_last_ins_right,factor,shape);

			shape->MakeOneDirection();
  			shape->MakeClockWise();
		}

		//if the shape is very small first merge it with the previous shape
		if (!ring->empty() && shape->Small( (B_INT) fabs(factor*3)))
		{
		   TDLI<Graph> Iring = TDLI<Graph>(ring);

			Iring.totail();

			GraphList *_twoshapes=SDK_NEW GraphList();
			_twoshapes->insbegin(shape);
			_twoshapes->insbegin(Iring.item());
			Iring.remove();
			_twoshapes->Merge();

			//move merged graphlist to ring
			Iring.takeover(_twoshapes);
			delete _twoshapes;
		}
		else
			ring->insend(shape);

		currentlink->SetBeenHere();
  }
}

//create an arc and add it to the graph
//center of circle
//begin point of arc
//end point of arc
//radius of arc
//aberation for generating the segments
void Graph::CreateArc(Node* center, Node* begin, Node* end,double radius,bool clock,double aber)
{
	double phi,dphi,dx,dy;
	Sint32 Segments;
	Sint32 i;
	double ang1,ang2,phit;

	Node* _last_ins;
	Node* _current;

	_last_ins=begin;

	dx = (double) _last_ins->GetX() - center->GetX();
	dy = (double) _last_ins->GetY() - center->GetY();
	ang1=atan2(dy,dx);
	if (ang1<0) ang1+=2.0*M_PI;
	dx = (double) end->GetX() - center->GetX();
	dy = (double) end->GetY() - center->GetY();
	ang2=atan2(dy,dx);
	if (ang2<0) ang2+=2.0*M_PI;

	if (clock)
	{ //clockwise
		if (ang2 > ang1)
			phit=2.0*M_PI-ang2+ ang1;
		else
			phit=ang1-ang2;
	}
	else
	{ //counter_clockwise
		if (ang1 > ang2)
			phit=-(2.0*M_PI-ang1+ ang2);
		else
			phit=-(ang2-ang1);
	}

	//what is the delta phi to get an accurancy of aber
	dphi=2*acos((radius-aber)/radius);

	//set the number of segments
	if (phit > 0)
		Segments=(Sint32)ceil(phit/dphi);
	else
		Segments=(Sint32)ceil(-phit/dphi);

	if (Segments <= 1)
	  Segments=1;
	if (Segments > 6)
	  Segments=6;

	dphi=phit/(Segments);

	for (i=1; i<Segments; i++)
	{
	  dx = (double) _last_ins->GetX() - center->GetX();
	  dy = (double) _last_ins->GetY() - center->GetY();
	  phi=atan2(dy,dx);

	  _current = SDK_NEW Node((B_INT) (center->GetX() + radius * cos(phi-dphi)),
								 (B_INT) (center->GetY() + radius * sin(phi-dphi)));
	  AddLink(_last_ins, _current);

	  _last_ins=_current;
	}

	// make a node from the endnode of link
	AddLink(_last_ins, end);
}

void Graph::CreateArc(Node* center, KBoolLine* incoming, Node* end,double radius,double aber)
{
	double distance=0;
	if (incoming->PointOnLine(center, distance, ACTIVE_BoolEng->GetAccur()) == RIGHT_SIDE)
		CreateArc(center,incoming->GetEndNode(),end,radius,true,aber);
	else
		CreateArc(center,incoming->GetEndNode(),end,radius,false,aber);
}

void Graph::MakeOneDirection()
{
	Sint32 _nr_of_points = _linklist->count();
	KBoolLink* _current = (KBoolLink*)_linklist->headitem();

	Node* _last = _current->GetBeginNode();
	Node* dummy;

	for (Sint32 i = 0; i < _nr_of_points; i++)
	{
		// get the other node on the link
		_last = _current->GetOther(_last);
		// get the other link on the node
		_current = _current->Forth(_last);

		if (_current->GetBeginNode() != _last)
		{
			// swap the begin- and endnode of the current link
			dummy = _current->GetBeginNode();
			_current->SetBeginNode(_current->GetEndNode());
			_current->SetEndNode(dummy);
		}
	}
}

bool Graph::Small(B_INT howsmall)
{

   TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	_LI.tohead();
   Node* bg=_LI.item()->GetBeginNode();
   B_INT xmin=bg->GetX();
   B_INT xmax=bg->GetX();
   B_INT ymin=bg->GetY();
   B_INT ymax=bg ->GetY();
	while (!_LI.hitroot())
	{
     bg=_LI.item()->GetBeginNode();
     // make _boundingbox bigger if the link makes the graph bigger
	  // Checking if point is in bounding-box with marge
     xmin=bmin(xmin,bg->GetX());
     xmax=bmax(xmax,bg->GetX());
     ymin=bmin(ymin,bg->GetY());
     ymax=bmax(ymax,bg->GetY());
	  _LI++;
	}

	B_INT dx=(xmax-xmin);
	B_INT dy=(ymax-ymin);

	if ((dx < howsmall) && (dy < howsmall) )
      return true;

	return false;
}


//create a circle at end and begin point
// and block in between
void	Graph::Make_Rounded_Shape( KBoolLink* a_link, double factor)
{
	double phi,dphi,dx,dy;
	Sint32 Segments=6;
	Sint32 i;


	KBoolLine theline(a_link);
	theline.CalculateLineParameters();

	Node* _current;
	Node *_first = SDK_NEW Node(a_link->GetBeginNode());
	Node *_last_ins = _first;

	theline.Virtual_Point(_first,factor);

	// make a node from this point
	_current = SDK_NEW Node(a_link->GetEndNode());
	theline.Virtual_Point(_current,factor);

	// make a link between the current and the previous and add this to graph
	AddLink(_last_ins, _current);
	_last_ins=_current;

	// make a half circle around the clock with the opposite point as
	// the middle point of the circle
	dphi=M_PI/(Segments);
	for (i=1; i<Segments; i++)
	{
	  dx = (double) _last_ins->GetX() - a_link->GetEndNode()->GetX();
	  dy = (double) _last_ins->GetY() - a_link->GetEndNode()->GetY();
	  phi=atan2(dy,dx);

	  _current = SDK_NEW Node((B_INT) (a_link->GetEndNode()->GetX() + factor * cos(phi-dphi)),
								 (B_INT) (a_link->GetEndNode()->GetY() + factor * sin(phi-dphi)));

	  AddLink(_last_ins, _current);

	  _last_ins=_current;
	}

	// make a node from the endnode of link
	_current = SDK_NEW Node(a_link->GetEndNode());
	theline.Virtual_Point(_current,-factor);
	AddLink(_last_ins, _current);
	_last_ins=_current;

	// make a node from this beginnode of link
	_current = SDK_NEW Node(a_link->GetBeginNode());
	theline.Virtual_Point(_current,-factor);
	AddLink(_last_ins, _current);
	_last_ins=_current;

	for (i=1; i<Segments; i++)
	{
	  dx = (double) _last_ins->GetX() - a_link->GetBeginNode()->GetX();
	  dy = (double) _last_ins->GetY() - a_link->GetBeginNode()->GetY();
	  phi=atan2(dy,dx);

	  _current = SDK_NEW Node((B_INT)(a_link->GetBeginNode()->GetX() + factor * cos(phi-dphi)),
								 (B_INT)(a_link->GetBeginNode()->GetY() + factor * sin(phi-dphi)));

	  AddLink(_last_ins, _current);

	  _last_ins=_current;
	}

	// make a link between the last and the first to close the graph
	AddLink(_last_ins, _first);
};

//make the graph clockwise orientation,
//return if the graph needed redirection
bool Graph::MakeClockWise()
{
	TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
	if (_LI.empty()) return false;

	KBoolLink *currentlink;
	Node *begin;

	_LI.foreach_mf(&KBoolLink::UnMark);//reset bin and mark flag of each link
	_LI.mergesort(linkYXtopsorter);
   _LI.tohead();

	begin = GetMostTopLeft(&_LI); // from all the most Top nodes,
   								  		// take the most left one

	currentlink=begin->GetNotFlat();
	if (!currentlink)
   {
      char buf[100];
	   sprintf(buf,"no NON flat link MakeClockWise at %15.3lf , %15.3lf",
         				(double) begin->GetX(), (double) begin->GetY());
		throw Bool_Engine_Error(buf, "Error", 9, 0);
	}

   //test to see if the orientation is right or left
   if (currentlink->GetBeginNode() == begin)
   {
      if ( currentlink->GetEndNode()->GetX() < begin->GetX())
      {
	      //going left
         //it needs redirection
         ReverseAllLinks();
         return true;
      }
   }
   else
   {
      if ( currentlink->GetBeginNode()->GetX() > begin->GetX())
      {  //going left
			//it needs redirection
         ReverseAllLinks();
         return true;
      }
   }
   return false;
}

bool Graph::writegraph(bool linked)
{
   return true;
}

bool Graph::writeintersections()
{



   return true;
}

bool Graph::checksort()
{
	// if empty then just insert
	if (_linklist->empty())
		return true;

	TDLI<KBoolLink> _LI=TDLI<KBoolLink>(_linklist);
   // put new item left of the one that is bigger
   _LI.tohead();
   KBoolLink* prev=_LI.item();
   KBoolLink* cur=_LI.item();
   _LI++;
   while(!_LI.hitroot())
   {
      KBoolLink* aap=_LI.item();
      if (linkXYsorter(prev,_LI.item())==-1)
      {
         cur=aap;

         return false;
      }
      prev=_LI.item();
      _LI++;
   }
   return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// graphlst.cpp
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//////////////////////////////////////////////////////////////////////////////////////////////////////////


//extern Debug_driver* _debug_driver;
//this here is to initialize the static iterator of graphlist
//with NOLIST constructor

Sint32 	graphsorterX( Graph *, Graph * );
Sint32 	graphsorterY( Graph *, Graph * );

GraphList::GraphList()
{
}

GraphList::~GraphList()
{
   TDLI<Graph> _LI=TDLI<Graph>(this);
	//first empty the graph
	_LI.delete_all();
}

//prepare the graphlist for the boolean operations
//group all graphs into ONE graph
void GraphList::Prepare(Graph* total)
{
   if (empty())
      return;

	// Simplify all graphs in the list
	Simplify( (double) ACTIVE_BoolEng->GetGrid() );

   {
      // Round all node = point to grid
      TDLI<Graph> _LI=TDLI<Graph>(this);
      _LI.tohead();
      while (!_LI.hitroot())
      {
			_LI.item()->MakeClockWise();
         _LI++;
      }
   }

	Renumber();

	//the graplist contents will be transferred to one graph
	MakeOneGraph(total);
}



// the function will make from all the graphs in the graphlist one graph,
// simply by throwing all the links in one graph, the graphnumbers will
// not be changed
void GraphList::MakeOneGraph(Graph* total)
{
   TDLI<Graph> _LI=TDLI<Graph>(this);
	_LI.tohead();
	while(!_LI.hitroot())
	{
		total->TakeOver(_LI.item());
		delete _LI.item();
		_LI.remove();
	}
}

//
// Renumber all the graphs
//
void GraphList::Renumber()
{
	Uint32 Number = 1;
   TDLI<Graph> _LI=TDLI<Graph>(this);
	_LI.tohead();
	while (!_LI.hitroot())
	{
		_LI.item()->SetNumber(Number++);
		_LI++;
	}
}


// Simplify the graphs
void GraphList::Simplify(double marge)
{
   TDLI<Graph> _LI=TDLI<Graph>(this);
	_LI.foreach_mf(&Graph::Reset_Mark_and_Bin);

	_LI.tohead();
	while (!_LI.hitroot())
	{
		if (_LI.item()->Simplify( (B_INT) marge))
      { 
			if (_LI.item()->GetNumberOfLinks() < 3)
				// delete this graph from the graphlist
         {
            delete _LI.item();
            _LI.remove();
         }
      }
		else
			_LI++;
	}
}

// Smoothen the graphs
void GraphList::Smoothen(double marge)
{
   TDLI<Graph> _LI=TDLI<Graph>(this);
	_LI.foreach_mf(&Graph::Reset_Mark_and_Bin);

	_LI.tohead();
	while (!_LI.hitroot())
	{
		if (_LI.item()->Smoothen( (B_INT) marge))
      {
			if (_LI.item()->GetNumberOfLinks() < 3)
			// delete this graph from the graphlist
         {
            delete _LI.item();
            _LI.remove();
         }
      }
		else
			_LI++;
	}
}


// Turn off all markers in all the graphs
void GraphList::UnMarkAll()
{
   TDLI<Graph> _LI=TDLI<Graph>(this);
	_LI.foreach_mf(&Graph::Reset_Mark_and_Bin);
}

//==============================================================================
//
//======================== BOOLEAN FUNCTIONS ===================================
//
//==============================================================================

void GraphList::Correction()
{
   TDLI<Graph> _LI=TDLI<Graph>(this);
	Sint32 todo=_LI.count();

   if ( ACTIVE_BoolEng->GetInternalCorrectionFactor()) //not zero
   {
      _LI.tohead();
      for(Sint32 i=0; i<todo ; i++)
      {
         //the input graph will be empty in the end
         GraphList *_correct=SDK_NEW GraphList();
         {
            _LI.item()->MakeClockWise();
            _LI.item()->Correction(_correct,ACTIVE_BoolEng->GetInternalCorrectionFactor());

            delete _LI.item();
            _LI.remove();

            //move corrected graphlist to result
            while (!_correct->empty())
            {
               //add to end
               _LI.insend((Graph*)_correct->headitem());
               _correct->removehead();
            }
         }
         delete _correct;
      }
   }   
}

void GraphList::MakeRings()
{
   TDLI<Graph> _LI=TDLI<Graph>(this);
	Sint32 todo=_LI.count();

	_LI.tohead();
	for(Sint32 i=0; i<todo ; i++)
	{
		//the input graph will be empty in the end
		GraphList *_ring=SDK_NEW GraphList();
		{
			_LI.item()->MakeClockWise();
			_LI.item()->MakeRing(_ring,ACTIVE_BoolEng->GetInternalCorrectionFactor());

         delete _LI.item();
			_LI.remove();

			//move created rings graphs to this
			while (!_ring->empty())
			{
				//add to end
				((Graph*)_ring->headitem())->MakeClockWise();
				_LI.insend((Graph*)_ring->headitem());
				_ring->removehead();
			}
		}
		delete _ring;
	}

}

//merge the graphs in the list and return the merged result
void GraphList::Merge()
{
   if (count()<=1)
      return;

   {
      TDLI<Graph> _LI=TDLI<Graph>(this);
      _LI.tohead();
      while (!_LI.hitroot())
      {
         _LI.item()->SetGroup(GROUP_A);
         _LI++;
      }
   }

   Graph* _tomerge=SDK_NEW Graph();

   Renumber();

   //the graplist contents will be transferred to one graph
   MakeOneGraph(_tomerge);
   //the original is empty now

   _tomerge->Prepare();
   _tomerge->Boolean(BOOL_OR,this);

	delete _tomerge;
}

//perform boolean operation on the graphs in the list
void GraphList::Boolean(BOOL_OP operation)
{
	ACTIVE_BoolEng->SetState("Performing Boolean Operation");

   if (count()==0)
         return;

	Graph* _prepared=SDK_NEW Graph();
   //round to grid and put in one graph
	ACTIVE_BoolEng->SetState("Simplify");
   Prepare(_prepared);
   if (_prepared->GetNumberOfLinks())
   {
      //calculate intersections etc.
      ACTIVE_BoolEng->SetState("prepare");
      _prepared->Prepare();
//      _prepared->writegraph(true);
      _prepared->Boolean(operation,this);
   }
	delete _prepared;
}


void GraphList::WriteGraphs()
{
   TDLI<Graph> _LI=TDLI<Graph>(this);
	_LI.tohead();
	while(!_LI.hitroot())
	{
        _LI.item()->writegraph( false );
        _LI++;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// line.cpp
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//////////////////////////////////////////////////////////////////////////////////////////////////////////


//
// The default constructor
//
KBoolLine::KBoolLine()
{
	_AAA = 0.0;
	_BBB = 0.0;
	_CCC = 0.0;
	_link = 0;
	linecrosslist = NULL;
	_valid_parameters = false;
}

KBoolLine::~KBoolLine()
{
	if (linecrosslist)
		delete linecrosslist;
}

//
// constructor with a link
//
KBoolLine::KBoolLine(KBoolLink *a_link)
{
	// a_link must exist
	VWFC_ASSERT(a_link);
	// points may not be equal
	// must be an if statement because if an VWFC_ASSERT is used there will
	// be a macro expansion error
	if (a_link->GetBeginNode()->Equal(a_link->GetEndNode(), 1))
		VWFC_ASSERT(!a_link);

	linecrosslist = NULL;
	_link = a_link;
	_valid_parameters = false;
}



// ActionOnTable1
// This function decide which action must be taken, after PointInLine
// has given the results of two points in relation to a line. See table 1 in the report
//
// input Result_beginnode:
//			Result_endnode :
//       The results can be LEFT_SIDE, RIGHT_SIDE, ON_AREA, IN_AREA
//
// return -1: Illegal combination
//         0: No action, no crosspoints
//         1: Investigate results points in relation to the other line
//         2: endnode is a crosspoint, no further investigation
//         3: beginnode is a crosspoint, no further investigation
//			  4: beginnode and endnode are crosspoints, no further investigation
//         5: beginnode is a crosspoint, need further investigation
//         6: endnode is a crosspoint, need further investigation
Sint32 KBoolLine::ActionOnTable1(PointStatus Result_beginnode, PointStatus Result_endnode)
{
	// Action 1.5 beginnode and endnode are crosspoints, no further investigation needed
	if (
		 (Result_beginnode == IN_AREA)
		 &&
		 (Result_endnode == IN_AREA)
		)
		return 4;
   // Action 1.1, there are no crosspoints, no action
	if (
		 (
		  (Result_beginnode == LEFT_SIDE)
		  &&
		  (Result_endnode == LEFT_SIDE)
		 )
		 ||
		 (
		  (Result_beginnode == RIGHT_SIDE)
		  &&
		  (Result_endnode == RIGHT_SIDE)
		 )
		)
		return 0;
	// Action 1.2, maybe there is a crosspoint, further investigation needed
	if (
		 (
		  (Result_beginnode == LEFT_SIDE)
		  &&
		  (
			(Result_endnode == RIGHT_SIDE)
			||
			(Result_endnode == ON_AREA)
		  )
		 )
		 ||
		 (
		  (Result_beginnode == RIGHT_SIDE)
		  &&
		  (
			(Result_endnode == LEFT_SIDE)
			||
			(Result_endnode == ON_AREA)
		  )
		 )
		 ||
		 (
		  (Result_beginnode == ON_AREA)
		  &&
		  (
			(Result_endnode == LEFT_SIDE)
			||
			(Result_endnode == RIGHT_SIDE)
			||
			(Result_endnode == ON_AREA)
		  )
		 )
		)
		return 1;
	// Action 1.3, there is a crosspoint, no further investigation
	if (
		 (
		  (Result_beginnode == LEFT_SIDE)
		  ||
		  (Result_beginnode == RIGHT_SIDE)
		 )
		 &&
		 (Result_endnode == IN_AREA)
		)
		return 2;
	// Action 1.4  there is a crosspoint, no further investigation
	if (
		 (Result_beginnode == IN_AREA)
		 &&
		 (
		  (Result_endnode == LEFT_SIDE)
		  ||
		  (Result_endnode == RIGHT_SIDE)
		 )
		)
		return 3;
	// Action 1.6  beginnode is a crosspoint, further investigation needed
	if (
		 (Result_beginnode == IN_AREA)
		 &&
		 (Result_endnode == ON_AREA)
		)
		return 5;
	// Action 1.7  endnode is a crosspoint, further investigation needed
	if (
		 (Result_beginnode == ON_AREA)
		 &&
		 (Result_endnode == IN_AREA)
		)
		return 6;
	// All other combinations are illegal
	return -1;
}


// ActionOnTable2
// This function decide which action must be taken, after PointInLine
// has given the results of two points in relation to a line. It can only give a
// correct decision if first the relation of the points from the line
// are investigated in relation to the line wich can be constucted from the points.
//
// input Result_beginnode:
//			Result_endnode :
//       The results can be LEFT_SIDE, RIGHT_SIDE, ON_AREA, IN_AREA
//
// return -1: Illegal combination
//         0: No action, no crosspoints
//         1: Calculate crosspoint
//         2: endnode is a crosspoint
//         3: beginnode is a crosspoint
//         4: beginnode and endnode are crosspoints
Sint32 KBoolLine::ActionOnTable2(PointStatus Result_beginnode, PointStatus Result_endnode)
{
	// Action 2.5, beginnode and eindpoint are crosspoints
	if (
		 (Result_beginnode == IN_AREA)
		 &&
		 (Result_endnode == IN_AREA)
		)
		return 4;
	// Action 2.1, there are no crosspoints
	if (
		 (
		  (Result_beginnode == LEFT_SIDE)
		  &&
		  (
			(Result_endnode == LEFT_SIDE)
			||
			(Result_endnode == ON_AREA)
		  )
		 )
		 ||
		 (
		  (Result_beginnode == RIGHT_SIDE)
		  &&
		  (
			(Result_endnode == RIGHT_SIDE)
			||
			(Result_endnode == ON_AREA)
		  )
		 )
		 ||
		 (
		  (Result_beginnode == ON_AREA)
		  &&
		  (
			(Result_endnode == LEFT_SIDE)
			||
			(Result_endnode == RIGHT_SIDE)
			||
			(Result_endnode == ON_AREA)
		  )
		 )
		)
		return 0;
	// Action 2.2, there is a real intersection, which must be calculated
	if (
		 (
		  (Result_beginnode == LEFT_SIDE)
		  &&
		  (Result_endnode == RIGHT_SIDE)
		 )
		 ||
		 (
		  (Result_beginnode == RIGHT_SIDE)
		  &&
		  (Result_endnode == LEFT_SIDE)
		 )
		)
		return 1;
	// Action 2.3, endnode is a crosspoint
	if (
		 (
		  (Result_beginnode == LEFT_SIDE)
		  ||
		  (Result_beginnode == RIGHT_SIDE)
		  ||
		  (Result_beginnode == ON_AREA)
		 )
		 &&
		 (Result_endnode == IN_AREA)
		)
		return 2;
	// Action 2.4, beginnode is a crosspoint
	if (
		 (Result_beginnode == IN_AREA)
		 &&
		 (
		  (Result_endnode == LEFT_SIDE)
		  ||
		  (Result_endnode == RIGHT_SIDE)
		  ||
		  (Result_endnode == ON_AREA)
		 )
		)
		return 3;
	// All other combinations are illegal
	return -1;
}

//
// This fucntion will ad a crossing to this line and the other line
// the crossing will be put in the link, because the line will be destructed
// after use of the variable
//
void KBoolLine::AddLineCrossing(B_INT X, B_INT Y, KBoolLine *other_line)
{
	// the other line must exist
	VWFC_ASSERT(other_line);
	// the links of the lines must exist
	VWFC_ASSERT(other_line->_link && _link);
	other_line->AddCrossing(AddCrossing(X,Y));
}

// Calculate the Y when the X is given
//
B_INT KBoolLine::Calculate_Y(B_INT X)
{
	// link must exist to get info about the nodes
	VWFC_ASSERT(_link);

	CalculateLineParameters();
	if (_AAA != 0)
		return (B_INT)(-(_AAA * X + _CCC) / _BBB);
	else
		// horizontal line
		return _link->GetBeginNode()->GetY();
}

B_INT KBoolLine::Calculate_Y_from_X(B_INT X)
{
	// link must exist to get info about the nodes
	VWFC_ASSERT(_link);
	VWFC_ASSERT(_valid_parameters);

	if (_AAA != 0)
		return (B_INT) ((-(_AAA * X + _CCC) / _BBB)+0.5);
	else
		// horizontal line
		return _link->GetBeginNode()->GetY();
}

void KBoolLine::Virtual_Point(LPoint *a_point,double distance)
{
	// link must exist to get info about the nodes
	VWFC_ASSERT(_link);
	VWFC_ASSERT(_valid_parameters);

	//calculate the distance using the slope of the line
   //and rotate 90 degrees

	a_point->SetY((B_INT)(a_point->GetY() + (distance * -(_BBB))));
	a_point->SetX((B_INT)(a_point->GetX() - (distance * _AAA   )));
}



//
// Calculate the lineparameters for the line if nessecary
//
void KBoolLine::CalculateLineParameters()
{
	// linkmust exist to get beginnode AND endnode
	VWFC_ASSERT(_link);

	// if not valid_parameters calculate the parameters
	if (!_valid_parameters)
	{
		Node *bp, *ep;
		double length;

		// get the begin and endnode via the link
		bp = _link->GetBeginNode();
		ep = _link->GetEndNode();

		// bp AND ep may not be the same
		if (bp == ep)
			VWFC_ASSERT (bp != ep);

		_AAA = (double) (ep->GetY() - bp->GetY()); // A = (Y2-Y1)
		_BBB = (double) (bp->GetX() - ep->GetX()); // B = (X1-X2)

		// the parameters A end B can now be normalized
		length = sqrt(_AAA*_AAA + _BBB*_BBB);

		if(length ==0)
			ACTIVE_BoolEng->error("length = 0","CalculateLineParameters");

		_AAA = (_AAA / length);
		_BBB = (_BBB / length);

		_CCC = -((_AAA * bp->GetX()) + (bp->GetY() * _BBB));

		_valid_parameters = true;
	}
}


// Checks if a line intersect with another line
// inout    Line : another line
//          Marge: optional, standard on MARGE (declared in MISC.CPP)
//
// return	true : lines are crossing
// 			false: lines are not crossing
//
Sint32 KBoolLine::CheckIntersect (KBoolLine * lijn, double Marge)
{
	double distance=0;
	// link must exist
	VWFC_ASSERT(_link);
	// lijn must exist
	VWFC_ASSERT(lijn);

	// points may not be equal
	// must be an if statement because if an VWFC_ASSERT is used there will
	// be a macro expansion error
	if (_link->GetBeginNode() == _link->GetEndNode())
		VWFC_ASSERT(!_link);

	Sint32 Take_Action1, Take_Action2, Total_Result;
	Node *bp, *ep;
	PointStatus Result_beginnode,Result_endnode;

	bp = lijn->_link->GetBeginNode();
	ep = lijn->_link->GetEndNode();
	Result_beginnode = PointInLine(bp,distance,Marge);
	Result_endnode   = PointInLine(ep,distance,Marge);
	Take_Action1 = ActionOnTable1(Result_beginnode,Result_endnode);
	switch (Take_Action1)
	{
		case 0: Total_Result = false ; break;
		case 1: {
						bp = _link->GetBeginNode();
						ep = _link->GetEndNode();
						Result_beginnode = lijn->PointInLine(bp,distance,Marge);
						Result_endnode   = lijn->PointInLine(ep,distance,Marge);
						Take_Action2 = ActionOnTable2(Result_beginnode,Result_endnode);
						switch (Take_Action2)
						{
							case 0: Total_Result = false; break;
							case 1: case 2: case 3: case 4: Total_Result = true; break;
						}
				  }; break; // This break belongs to the switch(Take_Action1)
		case 2: case 3: case 4: case 5: case 6: Total_Result = true; break;
	}
	return Total_Result; //This is the final decision
}


//
// Get the beginnode from the line
// usage: Node *anode = a_line.GetBeginNode()
//
Node *KBoolLine::GetBeginNode()
{
  // link must exist
  VWFC_ASSERT(_link);
  return _link->GetBeginNode();
}


//
// Get the endnode from the line
// usage: Node *anode = a_line.GetEndNode()
//
Node *KBoolLine::GetEndNode()
{
	// link must exist
	VWFC_ASSERT(_link);
	return _link->GetEndNode();
}

// Intersects two lines
// input    Line : another line
//          Marge: optional, standard on MARGE
//
// return	0: If there are no crossings
//				1: If there is one crossing
//				2: If there are two crossings
Sint32 KBoolLine::Intersect(KBoolLine * lijn, double Marge)
{
	double distance=0;
	// lijn must exist
	VWFC_ASSERT(lijn);

	// points may not be equal
	// must be an if statement because if an VWFC_ASSERT is used there will
	// be a macro expansion error
	if (_link->GetBeginNode() == _link->GetEndNode())
		VWFC_ASSERT(!_link);

	Node *bp, *ep;
	PointStatus Result_beginnode,Result_endnode;
	Sint32 Take_Action1, Take_Action2, Number_of_Crossings = 0;

	// Get the nodes from lijn via the link
	bp = lijn->_link->GetBeginNode();
	ep = lijn->_link->GetEndNode();

  	Result_beginnode = PointInLine(bp,distance,Marge);
	Result_endnode   = PointInLine(ep,distance,Marge);

	Take_Action1 = ActionOnTable1(Result_beginnode,Result_endnode);

	// The first switch will insert a crosspoint immediatly
	switch (Take_Action1)
	{
		// for the cases see the returnvalue of ActionTable1
		case 2: case 6: AddCrossing(ep);
							 Number_of_Crossings = 1;
							 break;
		case 3: case 5: AddCrossing(bp);
							 Number_of_Crossings = 1;
							 break;
		case 4: 			 AddCrossing(bp);
							 AddCrossing(ep);
							 Number_of_Crossings = 2;
							 break;
	}
	// This switch wil investigate the points of this line in relation to lijn
	switch (Take_Action1)
	{
		// for the cases see the returnvalue of ActionTable1
		case 1: case 5: case 6:
		  {
				// Get the nodes from this line via the link
				bp = _link->GetBeginNode();
				ep = _link->GetEndNode();
            Result_beginnode = lijn->PointInLine(bp,distance,Marge);
            Result_endnode   = lijn->PointInLine(ep,distance,Marge);
				Take_Action2 = ActionOnTable2(Result_beginnode,Result_endnode);
				switch (Take_Action2)
				{
					// for the cases see the returnvalue of ActionTable2
					case 1: {   // begin of scope to calculate the intersection
									double X, Y, Denominator;
									CalculateLineParameters();
									Denominator  = (_AAA * lijn->_BBB) - (lijn->_AAA * _BBB);
									// Denominator may not be 0
									VWFC_ASSERT(Denominator != 0.0);
									// Calculate intersection of both linesegments
									X = ((_BBB * lijn->_CCC) - (lijn->_BBB * _CCC)) / Denominator;
									Y = ((lijn->_AAA * _CCC) - (_AAA * lijn->_CCC)) / Denominator;

                           //make a decent rounding to B_INT
                           AddLineCrossing((B_INT)X,(B_INT)Y,lijn);
							  }   // end of scope to calculate the intersection
							  Number_of_Crossings++;
							  break;
					case 2: lijn->AddCrossing(ep);
							  Number_of_Crossings++;
							  break;
					case 3: lijn->AddCrossing(bp);
							  Number_of_Crossings++;
							  break;
					case 4: lijn->AddCrossing(bp);
							  lijn->AddCrossing(ep);
							  Number_of_Crossings = 2;
							  break;
				}
		  }; break; // This break belongs to the outer switch
	}
	return Number_of_Crossings; //This is de final number of crossings
}


// Intersects two lines there must be a crossing
Sint32 KBoolLine::Intersect_simple(KBoolLine * lijn)
{
	// lijn must exist
	VWFC_ASSERT(lijn);

	double X, Y, Denominator;
	Denominator  = (_AAA * lijn->_BBB) - (lijn->_AAA * _BBB);
	// Denominator may not be 0
	if (Denominator == 0.0)
			ACTIVE_BoolEng->error("colliniar lines","line");
	// Calculate intersection of both linesegments
	X = ((_BBB * lijn->_CCC) - (lijn->_BBB * _CCC)) / Denominator;
	Y = ((lijn->_AAA * _CCC) - (_AAA * lijn->_CCC)) / Denominator;
	AddLineCrossing((B_INT)X,(B_INT)Y,lijn);
	return(0);
}

// Intersects two lines there must be a crossing
bool KBoolLine::Intersect2(Node* crossing,KBoolLine * lijn)
{
	// lijn must exist
	VWFC_ASSERT(lijn);

	double X, Y, Denominator;
	Denominator  = (_AAA * lijn->_BBB) - (lijn->_AAA * _BBB);
	// Denominator may not be 0
	if (Denominator == 0.0)
		return false;
	// Calculate intersection of both linesegments
	X = ((_BBB * lijn->_CCC) - (lijn->_BBB * _CCC)) / Denominator;
	Y = ((lijn->_AAA * _CCC) - (_AAA * lijn->_CCC)) / Denominator;

	crossing->SetX((B_INT)X);
	crossing->SetY((B_INT)Y);
	return true;
}

//
// test if a point lies in the linesegment. If the point isn't on the line
// the function returns a value that indicates on which side of the
// line the point is (in linedirection from first point to second point
//
// returns LEFT_SIDE, when point lies on the left side of the line
//         RIGHT_SIDE, when point lies on the right side of the line
//         ON_AREA, when point lies on the infinite line within a range
//			  IN_AREA, when point lies in the area of the linesegment
// 		  the returnvalues are declared in (LINE.H)
PointStatus KBoolLine::PointInLine(Node *a_node, double& Distance, double Marge)
{
	  Distance=0;

	  //Punt must exist
	  VWFC_ASSERT(a_node);
	  // link must exist to get beginnode and endnode via link
	  VWFC_ASSERT(_link);

	  // get the nodes form the line via the link
	  Node *bp, *ep;
	  bp = _link->GetBeginNode();
	  ep = _link->GetEndNode();

	  // both node must exist
	  VWFC_ASSERT(bp && ep);
	  // node may not be the same
	  VWFC_ASSERT(bp != ep);

     //quick test if point is begin or endpoint
     if (a_node == bp || a_node == ep)
        return IN_AREA;

	  Sint32 Result_of_BBox=false;
	  PointStatus Result_of_Online;

	  // Checking if point is in bounding-box with marge
     B_INT xmin=bmin(bp->GetX(),ep->GetX());
     B_INT xmax=bmax(bp->GetX(),ep->GetX());
     B_INT ymin=bmin(bp->GetY(),ep->GetY());
     B_INT ymax=bmax(bp->GetY(),ep->GetY());

     if (  a_node->GetX() >= (xmin - Marge) && a_node->GetX() <= (xmax + Marge) &&
           a_node->GetY() >= (ymin - Marge) && a_node->GetY() <= (ymax + Marge) )
		  Result_of_BBox=true;

	  // Checking if point is on the infinite line
	  Result_of_Online = PointOnLine(a_node, Distance, Marge);

	  // point in boundingbox of the line and is on the line then the point is IN_AREA
	  if ((Result_of_BBox) && (Result_of_Online == ON_AREA))
			return IN_AREA;
	  else
			return Result_of_Online;
}


//
// test if a point lies on the line. If the point isn't on the line
// the function returns a value that indicates on which side of the
// line the point is (in linedirection from first point to second point
//
// returns LEFT_SIDE, when point lies on the left side of the line
//         ON_AREA, when point lies on the infinite line within a range
//         RIGHT_SIDE, when point lies on the right side of the line
// 		  LEFT_SIDE , RIGHT_SIDE , ON_AREA
PointStatus KBoolLine::PointOnLine(Node *a_node, double& Distance, double Marge)
{
   Distance=0;

	// a_node must exist
	VWFC_ASSERT(a_node);
	// link must exist to get beginnode and endnode
	VWFC_ASSERT(_link);

	// get the nodes from the line via the link
	Node *bp, *ep;
	bp = _link->GetBeginNode();
	ep = _link->GetEndNode();

	// both node must exist
	VWFC_ASSERT(bp && ep);
	// node may not be queal
	VWFC_ASSERT(bp!=ep);

   //quick test if point is begin or endpoint
   if (a_node == bp || a_node == ep)
      return ON_AREA;

	CalculateLineParameters();
	// calculate the distance of a_node in relation to the line
	Distance = (_AAA * a_node->GetX())+(_BBB * a_node->GetY()) + _CCC;

	if (Distance < -Marge)
		return LEFT_SIDE;
	else
	{
		if (Distance > Marge)
			return RIGHT_SIDE;
		else
		 return ON_AREA;
	}
}


//
// Sets lines parameters
// usage: a_line.Set(a_pointer_to_a_link);
//
void KBoolLine::Set(KBoolLink *a_link)
{
	// points must exist
	VWFC_ASSERT(a_link);
	// points may not be equal
	// must be an if statement because if an VWFC_ASSERT is used there will
	// be a macro expansion error
//	if (a_link->GetBeginNode()->Equal(a_link->GetEndNode(),MARGE)) VWFC_ASSERT(!a_link);

	linecrosslist = NULL;
	_link = a_link;
	_valid_parameters = false;
}

KBoolLink* KBoolLine::GetLink()
{
   return _link;
}
//
// makes a line same as these
// usage : line1 = line2;
//
KBoolLine& KBoolLine::operator=(const KBoolLine& a_line)
{
	_AAA = a_line._AAA;
	_BBB = a_line._BBB;
	_CCC = a_line._CCC;
	_link = a_line._link;
  	linecrosslist = NULL;
	_valid_parameters = a_line._valid_parameters;
	return *this;
}

Node* KBoolLine::OffsetContour(KBoolLine* const nextline,Node* _last_ins, double factor,Graph *shape)
{
	KBoolLink* offs_currentlink;
	KBoolLine  offs_currentline;
	KBoolLink* offs_nextlink;
	KBoolLine  offs_nextline;
	Node* offs_end;

	Node* offs_bgn_next;
	Node* offs_end_next;

	// make a node from this point
	offs_end = SDK_NEW Node(GetEndNode());
	Virtual_Point(offs_end,factor);
	offs_currentlink=SDK_NEW KBoolLink(0, _last_ins,offs_end);
	offs_currentline.Set(offs_currentlink);

	offs_bgn_next = SDK_NEW Node(nextline->_link->GetBeginNode());
	nextline->Virtual_Point(offs_bgn_next,factor);

	offs_end_next = SDK_NEW Node(nextline->_link->GetEndNode());
	nextline->Virtual_Point(offs_end_next,factor);

	offs_nextlink=SDK_NEW KBoolLink(0, offs_bgn_next, offs_end_next);
	offs_nextline.Set(offs_nextlink);

	offs_currentline.CalculateLineParameters();
	offs_nextline.CalculateLineParameters();
	offs_currentline.Intersect2(offs_end,&offs_nextline);

	// make a link between the current and the previous and add this to graph
	shape->AddLink(offs_currentlink);

	delete offs_nextlink;

	return(offs_end);
}


Node* KBoolLine::OffsetContour_rounded(KBoolLine* const nextline,Node* _last_ins, double factor,Graph *shape)
{
	KBoolLink* offs_currentlink;
	KBoolLine  offs_currentline;
	KBoolLink* offs_nextlink;
	KBoolLine  offs_nextline;
	Node* offs_end;
	Node* medial_axes_point= SDK_NEW Node();
	Node* bu_last_ins = SDK_NEW Node(_last_ins);

	Node* offs_bgn_next;
	Node* offs_end_next;

	// make a node from this point
	offs_end = SDK_NEW Node(GetEndNode());

	*_last_ins = *GetBeginNode();
	Virtual_Point(_last_ins,factor);
	Virtual_Point(offs_end,factor);
	offs_currentlink=SDK_NEW KBoolLink(0, _last_ins,offs_end);
	offs_currentline.Set(offs_currentlink);

	offs_bgn_next = SDK_NEW Node(nextline->_link->GetBeginNode());
	nextline->Virtual_Point(offs_bgn_next,factor);

	offs_end_next = SDK_NEW Node(nextline->_link->GetEndNode());
	nextline->Virtual_Point(offs_end_next,factor);

	offs_nextlink=SDK_NEW KBoolLink(0, offs_bgn_next, offs_end_next);
	offs_nextline.Set(offs_nextlink);

	offs_currentline.CalculateLineParameters();
	offs_nextline.CalculateLineParameters();
	offs_currentline.Intersect2(medial_axes_point,&offs_nextline);

	double result_offs=sqrt( pow((double)GetEndNode()->GetY()-medial_axes_point->GetY(),2) +
							 pow((double)GetEndNode()->GetX()-medial_axes_point->GetX(),2) );

	if ( result_offs < fabs(ACTIVE_BoolEng->GetRoundfactor()*factor))
	{
		*_last_ins=*bu_last_ins;
		*offs_end=*medial_axes_point;
		delete medial_axes_point;
		delete bu_last_ins;
		// make a link between the current and the previous and add this to graph
		delete offs_nextlink;
		shape->AddLink(offs_currentlink);
		return(offs_end);
	}
	else
	{ //let us create a circle
		*_last_ins=*bu_last_ins;
		delete medial_axes_point;
		delete bu_last_ins;
		Node* endarc= SDK_NEW Node(offs_bgn_next);
		shape->AddLink(offs_currentlink);
		delete offs_nextlink;
		shape->CreateArc(GetEndNode(), &offs_currentline, endarc,fabs(factor),ACTIVE_BoolEng->GetInternalCorrectionAber());
		return(endarc);
	}
}


bool KBoolLine::OkeForContour(KBoolLine* const nextline,double factor,Node* LastLeft,Node* LastRight, LinkStatus& _outproduct)
{
	VWFC_ASSERT(_link);
	VWFC_ASSERT(_valid_parameters);
	VWFC_ASSERT(nextline->_link);
	VWFC_ASSERT(nextline->_valid_parameters);

	factor = fabs(factor);

//	PointStatus status=ON_AREA;
	double distance=0;

	Node offs_end_next(nextline->_link->GetEndNode());

	_outproduct= _link->OutProduct(nextline->_link,ACTIVE_BoolEng->GetAccur());

	switch (_outproduct)
	{
		// current line lies on  leftside of prev line
		case IS_RIGHT :
		{
			nextline->Virtual_Point(&offs_end_next,-factor);

			// status=
			nextline->PointOnLine(LastRight, distance, ACTIVE_BoolEng->GetAccur());
			if (distance > factor)
			{  PointOnLine(&offs_end_next, distance, ACTIVE_BoolEng->GetAccur());
				if (distance > factor)
					 return(true);
			}
		}
		break;
		// current line lies on  rightside of prev line
		case IS_LEFT :
		{
			nextline->Virtual_Point(&offs_end_next,factor);

			// status=
			nextline->PointOnLine(LastLeft, distance, ACTIVE_BoolEng->GetAccur());
			if (distance < -factor)
			{  PointOnLine(&offs_end_next, distance, ACTIVE_BoolEng->GetAccur());
				if (distance <-factor)
					 return(true);
			}
		}
		break;
		// current line  lies on prev line
		case IS_ON	 :
		{
			return(true);
		}
	}//end switch

	return(false);
}


bool KBoolLine::Create_Ring_Shape(KBoolLine* nextline,Node** _last_ins_left,Node** _last_ins_right,double factor,Graph *shape)
{
	Node* _current;
	LinkStatus _outproduct=IS_ON;

	if (OkeForContour(nextline,factor,*_last_ins_left,*_last_ins_right,_outproduct))
	{
		switch (_outproduct)
		{
			// Line 2 lies on  leftside of this line
			case IS_RIGHT :
			{
				*_last_ins_left  =OffsetContour_rounded(nextline,*_last_ins_left,factor,shape);
				*_last_ins_right =OffsetContour(nextline,*_last_ins_right,-factor,shape);
			}
			break;
			case IS_LEFT :
			{
				*_last_ins_left  =OffsetContour(nextline,*_last_ins_left,factor,shape);
				*_last_ins_right =OffsetContour_rounded(nextline,*_last_ins_right,-factor,shape);

			}
			break;
			// Line 2 lies on this line
			case IS_ON	 :
			{
				// make a node from this point
				_current = SDK_NEW Node(_link->GetEndNode());
				Virtual_Point(_current,factor);

				// make a link between the current and the previous and add this to graph
				shape->AddLink(*_last_ins_left, _current);
				*_last_ins_left=_current;

				_current = SDK_NEW Node(_link->GetEndNode());
				Virtual_Point(_current,-factor);

				shape->AddLink(*_last_ins_right, _current);
				*_last_ins_right=_current;
			}
			break;
		}//end switch
		return(true);
	}
/*	else
	{
		switch (_outproduct)
		{
			// Line 2 lies on  leftside of this line
			case IS_RIGHT :
			{
				*_last_ins_left  =OffsetContour_rounded(nextline,*_last_ins_left,factor,Ishape);
				*_last_ins_right =OffsetContour(nextline,*_last_ins_right,-factor,Ishape);
			}
			break;
			case IS_LEFT :
			{
				*_last_ins_left  =OffsetContour(nextline,*_last_ins_left,factor,Ishape);
				*_last_ins_right =OffsetContour_rounded(nextline,*_last_ins_right,-factor,Ishape);

			}
			break;
			// Line 2 lies on this line
			case IS_ON	 :
			{
				// make a node from this point
				_current = new Node(_link->GetEndNode());
				Virtual_Point(_current,factor);

				// make a link between the current and the previous and add this to graph
				Ishape->AddLink(*_last_ins_left, _current);
				*_last_ins_left=_current;

				_current = new Node(_link->GetEndNode());
				Virtual_Point(_current,-factor);

				Ishape->AddLink(*_last_ins_right, _current);
				*_last_ins_right=_current;
			}
			break;
		}//end switch
		return(true);
	}
*/
	return(false);
}


void KBoolLine::Create_Begin_Shape(KBoolLine* nextline,Node** _last_ins_left,Node** _last_ins_right,double factor,Graph *shape)
{
	factor = fabs(factor);
	LinkStatus _outproduct;
	_outproduct= _link->OutProduct(nextline->_link,ACTIVE_BoolEng->GetAccur());

	switch (_outproduct)
	{
		case IS_RIGHT :
		{
			*_last_ins_left = SDK_NEW Node(_link->GetEndNode());

			Virtual_Point(*_last_ins_left,factor);

			*_last_ins_right = SDK_NEW Node(nextline->_link->GetBeginNode());
			nextline->Virtual_Point(*_last_ins_right,-factor);

			shape->AddLink(*_last_ins_left, *_last_ins_right);

			*_last_ins_left=OffsetContour_rounded(nextline,*_last_ins_left,factor,shape);
		}
		break;
		case IS_LEFT :
		{
			*_last_ins_left = SDK_NEW Node(nextline->_link->GetBeginNode());
			nextline->Virtual_Point(*_last_ins_left,factor);

			*_last_ins_right = SDK_NEW Node(_link->GetEndNode());
			Virtual_Point(*_last_ins_right,-factor);

			shape->AddLink(*_last_ins_left, *_last_ins_right);

			*_last_ins_right=OffsetContour_rounded(nextline,*_last_ins_right,-factor,shape);
		}
		break;
		// Line 2 lies on this line
		case IS_ON	 :
		{
			*_last_ins_left = SDK_NEW Node(nextline->_link->GetBeginNode());
			Virtual_Point(*_last_ins_left,factor);

			*_last_ins_right = SDK_NEW Node(nextline->_link->GetBeginNode());
			Virtual_Point(*_last_ins_right,-factor);

			shape->AddLink(*_last_ins_left, *_last_ins_right);
		}
		break;
	}//end switch

}

void KBoolLine::Create_End_Shape(KBoolLine* nextline,Node* _last_ins_left,Node* _last_ins_right,double factor,Graph *shape)
{
	Node* _current;
	factor = fabs(factor);
	LinkStatus _outproduct;
	_outproduct= _link->OutProduct(nextline->_link,ACTIVE_BoolEng->GetAccur());

	switch (_outproduct)
	{
		case IS_RIGHT :
		{
			_current = SDK_NEW Node(_link->GetEndNode());
			Virtual_Point(_current,-factor);
			shape->AddLink(_last_ins_right, _current);
			_last_ins_right=_current;

			_last_ins_left=OffsetContour_rounded(nextline,_last_ins_left,factor,shape);
			shape->AddLink(_last_ins_left,_last_ins_right);
		}
		break;
		case IS_LEFT :
		{
			_current = SDK_NEW Node(_link->GetEndNode());
			Virtual_Point(_current,factor);
			shape->AddLink(_last_ins_left, _current);
			_last_ins_left=_current;

			_last_ins_right=OffsetContour_rounded(nextline,_last_ins_right,-factor,shape);
			shape->AddLink(_last_ins_right, _last_ins_left);
		}
		break;
		// Line 2 lies on this line
		case IS_ON	 :
		{
			_current = SDK_NEW Node(_link->GetEndNode());
			Virtual_Point(_current,factor);
			shape->AddLink(_last_ins_left, _current);
			_last_ins_left=_current;

			_current = SDK_NEW Node(_link->GetEndNode());
			Virtual_Point(_current,-factor);
			shape->AddLink(_last_ins_right, _current);
			_last_ins_right=_current;

			shape->AddLink(_last_ins_left, _last_ins_right);
		}
		break;
	}//end switch

}

//
// Generate from the found crossings a part of the graph
//
bool KBoolLine::ProcessCrossings(TDLI<KBoolLink>* _LI)
{
	Node *last;	KBoolLink *dummy;
//	VWFC_ASSERT (beginnode && endnode);

	if (!linecrosslist)	return false;

	if (linecrosslist->empty())	return false;
	if (linecrosslist->count()>1)	SortLineCrossings();
	_link->GetEndNode()->RemoveLink(_link);
	last=_link->GetEndNode();
	// Make new links :
	while (!linecrosslist->empty())
	{
		dummy=SDK_NEW KBoolLink(_link->GetGraphNum(),(Node*) linecrosslist->tailitem(),last);
      dummy->SetBeenHere();
		dummy->SetGroup(_link->Group());
      _LI->insbegin(dummy);
		last=(Node*)linecrosslist->tailitem();
		linecrosslist->removetail();
	}
	// Recycle this link :
	last->AddLink(_link);
	_link->SetEndNode(last);
	delete linecrosslist;
	linecrosslist=NULL;
	return true;
}

/*
// Sorts the links on the X values
Sint32 NodeXYsorter(Node* a, Node* b)
{
	if ( a->GetX() < b->GetX())
		return(1);
	if ( a->GetX() > b->GetX())
		return(-1);
   //they are eqaul in x
	if ( a->GetY() < b->GetY())
		return(-1);
	if ( a->GetY() > b->GetY())
		return(1);
   //they are eqaul in y
	return(0);
}

//
// Generate from the found crossings a part of the graph
// this routine is used in combination with the scanbeam class
// the this link most stay at the same place in the sorted graph
// The link is split into peaces wich are inserted sorted into the graph
// on beginnode.
// The mostleft link most become the new link for the beam record
// therefore the mostleft new/old link is returned to become the beam record link
// also the part returned needs to have the bin flag set to the original value it had in the beam
KBoolLink* KBoolLine::ProcessCrossingsSmart(TDLI<KBoolLink>* _LI)
{
   Node *lastinserted;
   KBoolLink *new_link;
   KBoolLink *returnlink;
	VWFC_ASSERT (beginnode && endnode);
	if (!linecrosslist)	return this;

	if (linecrosslist->empty())	return this;
	if (linecrosslist->count()>1)
   {
   	SortLineCrossings();
   }
	Sint32 inbeam;

   //most left at the beginnode or endnode
   if (NodeXYsorter(beginnode,endnode)==1)
   {
      //re_use this link
      endnode->RemoveLink(this);
      linecrosslist->insend(endnode); //the last link to create is towards this node
      endnode=(Node*) linecrosslist->headitem();
      endnode->AddLink(this);
      inbeam=NodeXYsorter(_LI->item()->beginnode,beginnode);
      switch (inbeam)
      {
        case -1:
        case 0:
            bin=true;
            break;
        case 1:
            bin=false;
            break;
      }
      returnlink=this;

      lastinserted=endnode;
      linecrosslist->removehead();
      // Make new links starting at endnode
      while (!linecrosslist->empty())
      {
         new_link=new KBoolLink(graphnum,lastinserted,(Node*) linecrosslist->headitem());

         new_link->group=group;
         Sint32 inbeam=NodeXYsorter(_LI->item()->beginnode,lastinserted);
         switch (inbeam)
         {
           case -1:
               {
                 double x,y,xl,yl;
                 char buf[80];
                 x=((Node*)(linecrosslist->headitem()))->GetX();
                 y=((Node*)(linecrosslist->headitem()))->GetY();
					  xl=_LI->item()->beginnode->GetX();
                 yl=_LI->item()->beginnode->GetY();
                 sprintf(buf," x=%f , y=%f inserted before %f,%f",x,y,xl,yl);
                 _messagehandler->info(buf,"scanbeam");
		           new_link->bin=true;
               }
               break;
           case 0:
	            new_link->bin=true;
	            returnlink=new_link;
               break;
           case 1:
	            new_link->bin=false;
               break;
         }

         //insert a link into the graph that is already sorted on beginnodes of the links.
         //starting at a given position
         // if empty then just insert

         if (_LI->empty())
            _LI->insend(new_link);
         else
         {
            // put new item left of the one that is bigger are equal
            Sint32 i=0;
            Sint32 insert=0;
            while(!_LI->hitroot())
            {
               if ((insert=linkXYsorter(new_link,_LI->item()))!=-1)
                  break;
               (*_LI)++;
               i++;
            }

            _LI->insbefore_unsave(new_link);
            if (insert==0 && _LI->item()->beginnode!=new_link->beginnode)
             //the begin nodes are equal but not the same merge them into one node
            {  Node* todelete=_LI->item()->beginnode;
					new_link->beginnode->Merge(todelete);
					delete todelete;
            }

            //set back iter
            (*_LI) << (i+1);
         }

         lastinserted=(Node*)linecrosslist->headitem();
         linecrosslist->removehead();
      }
   }
   else
   {
      //re_use this link
      endnode->RemoveLink(this);
      linecrosslist->insend(endnode); //the last link to create is towards this node
      endnode=(Node*) linecrosslist->headitem();
      endnode->AddLink(this);
      inbeam=NodeXYsorter(_LI->item()->beginnode,endnode);
      switch (inbeam)
      {
        case -1:
        case 0:
            bin=true;
            break;
        case 1:
            bin=false;
            break;
      }
      returnlink=this;

      lastinserted=endnode;
      linecrosslist->removehead();

      // Make new links starting at endnode
      while (!linecrosslist->empty())
      {
         new_link=new KBoolLink(graphnum,lastinserted,(Node*) linecrosslist->headitem());
         new_link->group=group;

         inbeam=NodeXYsorter(_LI->item()->beginnode,(Node*) linecrosslist->headitem());
         switch (inbeam)
         {
           case -1:
           case 0:
	            new_link->bin=true;
               break;
           case 1:
	            new_link->bin=false;
               break;
         }
         inbeam=NodeXYsorter(_LI->item()->beginnode,lastinserted);
         switch (inbeam)
         {
           case -1:
               {
                 double x,y,xl,yl;
                 char buf[80];
                 x=lastinserted->GetX();
                 y=lastinserted->GetY();
					  xl=_LI->item()->beginnode->GetX();
                 yl=_LI->item()->beginnode->GetY();
                 sprintf(buf," x=%f , y=%f inserted before %f,%f",x,y,xl,yl);
                 _messagehandler->info(buf,"scanbeam");
               }
               break;
           case 0:
               break;
           case 1:
	            returnlink=new_link;
               break;
         }

         //insert a link into the graph that is already sorted on beginnodes of the links.
         //starting at a given position
         // if empty then just insert

         if (_LI->empty())
            _LI->insend(new_link);
         else
         {
            // put new item left of the one that is bigger are equal
            Sint32 i=0;
            Sint32 insert=0;
            while(!_LI->hitroot())
            {
               if ((insert=linkXYsorter(new_link,_LI->item()))!=-1)
                  break;
               (*_LI)++;
               i++;
            }

            _LI->insbefore_unsave(new_link);
            if (insert==0 && _LI->item()->beginnode!=new_link->beginnode)
             //the begin nodes are equal but not the same merge them into one node
            {  Node* todelete=_LI->item()->beginnode;
					new_link->beginnode->Merge(todelete);
					delete todelete;
            }
            //set back iter
            (*_LI) << (i+1);
         }

         lastinserted=(Node*)linecrosslist->headitem();
         linecrosslist->removehead();
      }
   }
	delete linecrosslist;
	linecrosslist=NULL;

  	return returnlink;
}
*/

static Sint32 NODE_X_ASCENDING_L (Node* a, Node* b)
{
	if(b->GetX() > a->GetX()) return(1);
	else
	if(b->GetX() == a->GetX()) return(0);

	return(-1);
}

static Sint32 NODE_X_DESCENDING_L(Node* a, Node* b)
{
	if(a->GetX() > b->GetX()) return(1);
	else
	if(a->GetX() == b->GetX()) return(0);

	return(-1);
}

static Sint32 NODE_Y_ASCENDING_L (Node* a, Node* b)
{
	if(b->GetY() > a->GetY()) return(1);
	else
	if(b->GetY() == a->GetY()) return(0);
	return(-1);
}

static Sint32 NODE_Y_DESCENDING_L(Node* a, Node* b)
{
	if(a->GetY() > b->GetY()) return(1);
	else
	if(a->GetY() == b->GetY()) return(0);

	return(-1);
}

//
// This function finds out which sortfunction to use with sorting
// the crossings.
//
void KBoolLine::SortLineCrossings()
{
	TDLI<Node> I(linecrosslist);

	B_INT dx, dy;
	dx=babs(_link->GetEndNode()->GetX() - _link->GetBeginNode()->GetX());
	dy=babs(_link->GetEndNode()->GetY() - _link->GetBeginNode()->GetY());
	if (dx > dy)
	{	// thislink is more horizontal then vertical
		if (_link->GetEndNode()->GetX() > _link->GetBeginNode()->GetX())
			I.mergesort(NODE_X_ASCENDING_L);
		else
			I.mergesort(NODE_X_DESCENDING_L);
	}
	else
	{	// this link is more vertical then horizontal
		if (_link->GetEndNode()->GetY() > _link->GetBeginNode()->GetY())
			I.mergesort(NODE_Y_ASCENDING_L);
		else
			I.mergesort(NODE_Y_DESCENDING_L);
	}
}

//
// Adds a cross Node to this. a_node may not be deleted before processing the crossings
//
void KBoolLine::AddCrossing(Node *a_node)
{
	if (a_node==_link->GetBeginNode() || a_node==_link->GetEndNode())	return;


	if (!linecrosslist)
	{
		linecrosslist=SDK_NEW DL_List<void*>();
		linecrosslist->insend(a_node);
	}
	else
	{
		TDLI<Node> I(linecrosslist);
		if (!I.has(a_node))
			I.insend(a_node);
	}
}

//
// see above
//
Node* KBoolLine::AddCrossing(B_INT X, B_INT Y)
{
	Node* result=SDK_NEW Node(X,Y);
	AddCrossing(result);
	return result;
}

DL_List<void*>* KBoolLine::GetCrossList()
{
	if (linecrosslist)
		return linecrosslist;
	return NULL;
}

bool KBoolLine::CrossListEmpty()
{
	if (linecrosslist)
		return linecrosslist->empty();
	return true;
}

/*
bool KBoolLine::HasInCrossList(Node *n)
{
	if(linecrosslist!=NULL)
	{
		TDLI<Node> I(linecrosslist);
		return I.has(n);
	}
	return false;
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// link.cpp
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//////////////////////////////////////////////////////////////////////////////////////////////////////////


Sint32 linkXYsorter(KBoolLink *, KBoolLink *);

//
// Default constructor
//
KBoolLink::KBoolLink()
{
	Reset();
}


//
// This constructor makes this link a valid part of a graph
//
KBoolLink::KBoolLink(Sint32 graphnr, Node *begin, Node *end)
{
	Reset();

	// Set the references of the node and of this link correct
	begin->AddLink(this);
	end->AddLink(this);
	beginnode=begin;
	endnode=end;
	if (graphnr!=0)
		graphnum=graphnr;
}

//
// This constructor makes this link a valid part of a graph
//
KBoolLink::KBoolLink(Node *begin, Node *end)
{
	Reset();

	// Set the references of the node and of this link correct
	begin->AddLink(this);
	end->AddLink(this);
	beginnode=begin;
	endnode=end;
	graphnum=0;
}


//
// Destructor
//
KBoolLink::~KBoolLink()
{
	UnLink();
}

//
//	Checks whether the current algorithm has been on this link
//
bool KBoolLink::BeenHere()
{
   if (bin) return true;
	return false;
}

//
//	Returns the next link from the argument
//
KBoolLink*	KBoolLink::Forth(Node *node)
{
	VWFC_ASSERT(node==beginnode || node==endnode);
	return node->GetOtherLink(this);
}

//
// Returns the Beginnode
//
Node *KBoolLink::GetBeginNode()
{
	return beginnode;
}

//
// Returns the endnode
//
Node*	KBoolLink::GetEndNode()
{
	return endnode;
}

Node*	KBoolLink::GetLowNode()
{
	return ( ( beginnode->GetY() < endnode->GetY() ) ? beginnode : endnode );
}

Node*	KBoolLink::GetHighNode()
{
	return ( ( beginnode->GetY() > endnode->GetY() ) ? beginnode : endnode );
}

//
// Returns the graphnumber
//
Sint32 KBoolLink::GetGraphNum()
{
	return graphnum;
}

bool KBoolLink::GetInc()
{
   return Inc;
//   if (Inc) return true;
//	return false;
}

void KBoolLink::SetInc(bool inc)
{
     Inc=inc;
//   Inc=0;
//   if (inc) Inc=1;
}

bool KBoolLink::GetLeftA()
{
	return LeftA;
}

void KBoolLink::SetLeftA(bool la)
{
	LeftA=la;
}

bool KBoolLink::GetLeftB()
{
	return LeftB;
}

void KBoolLink::SetLeftB(bool lb)
{
	LeftB=lb;
}

bool KBoolLink::GetRightA()
{
	return RightA;
}

void KBoolLink::SetRightA(bool ra)
{
	RightA=ra;
}

bool KBoolLink::GetRightB()
{
	return RightB;
}

void KBoolLink::SetRightB(bool rb)
{
	RightB=rb;
}

//
//	This function is very popular by GP-faults
// It returns the node different from a
//
Node* KBoolLink::GetOther(const Node *const a)
{
	return ( (a!=beginnode) ? beginnode : endnode);
}


//
//	Is this marked for given operation
//
bool KBoolLink::IsMarked(BOOL_OP operation)
{
		switch (operation)
		{
			 case(BOOL_OR): 	 		return merge;
			 case(BOOL_AND):  		return intersect;
			 case(BOOL_A_SUB_B):		return a_substract_b;
			 case(BOOL_B_SUB_A): 	return b_substract_a;
			 case(BOOL_EXOR):	 		return exor;
			 default:					break;
		}
      return false; //should not appear
}



void KBoolLink::SetHoleLink(bool val)
{
	holelink=val;
}



bool KBoolLink::GetHoleLink()
{
	return holelink;
}



//
//	Is this a hole for given operation
// beginnode must be to the left
bool KBoolLink::IsHole(BOOL_OP operation)
{

   bool topsideA,topsideB;

	if (beginnode->GetX() < endnode->GetX()) //going to the right?
   { 	topsideA=RightA;topsideB=RightB;  }
   else
   {  topsideA=LeftA;topsideB=LeftB;    }

   switch (operation)
   {
       case(BOOL_OR):
            return ( !topsideB && !topsideA );
       case(BOOL_AND):
         return ( !topsideB || !topsideA );
       case(BOOL_A_SUB_B):
         return ( topsideB || !topsideA );
       case(BOOL_B_SUB_A):
         return ( topsideA || !topsideB );
       case(BOOL_EXOR):
         return !( (topsideB && !topsideA) || (!topsideB && topsideA) );
//         return (bool) !( topsideB != topsideA );  // don't use ^, in a strange way it doesn't work !!!
	   default:					break;
   }
   return false; //should not appear
}

//
// Is this a part of a hole
//
bool KBoolLink::IsHoleMarked()
{
	return (hole);
}


void KBoolLink::SetHole(bool h)
{
	hole=h;
}


//
//	Is this not marked at all
//
bool KBoolLink::IsUnused()
{
	return  !(exor || merge || a_substract_b || b_substract_a || intersect);
}


bool KBoolLink::IsZero(B_INT marge)
{
	return (beginnode->Equal(endnode,marge)) ;
}


bool KBoolLink::ShorterThan(B_INT marge)
{
	return (beginnode->ShorterThan(endnode,marge)) ;
}


//
//	Mark this link
//
void KBoolLink::Mark()
{
	mark=true;
}


#ifndef ABS
#define ABS(a) (((a)<0) ? -(a) : (a))
#endif


//
// This makes from the begin and endnode one node (argument begin_or_end_node)
// The references to this link in the node will also be deleted
// After doing that, link link can be deleted or be recycled.
//
void KBoolLink::MergeNodes(Node *const begin_or_end_node)
{
//	VWFC_ASSERT(beginnode && endnode);
//	VWFC_ASSERT ((begin_or_end_node == beginnode)||(begin_or_end_node == endnode));

	beginnode->RemoveLink(this);
	endnode->RemoveLink(this);

	if (endnode!=beginnode)
	{	// only if beginnode and endnode are different nodes
		begin_or_end_node->Merge(GetOther(begin_or_end_node));
	}
	endnode = NULL;
	beginnode=NULL;
}

//
//	Return the position of the second link compared to this link
// Result = IS_ON | IS_LEFT | IS_RIGHT
// Here Left and Right is defined as being left or right from
// the this link towards the center (common) node
//
LinkStatus KBoolLink::OutProduct(KBoolLink* const two,double accur)
{
	Node*	center;
	double distance;
	if (two->GetBeginNode()->Equal(two->GetEndNode(), 1))
		VWFC_ASSERT(!two);
	if (GetBeginNode()->Equal(GetEndNode(), 1))
		VWFC_ASSERT(!this);
	KBoolLine* temp_line = SDK_NEW KBoolLine(this);

	//the this link should connect to the other two link at at least one node
	if (endnode==two->endnode || endnode==two->beginnode)
		center=endnode;
	else
	{	center=beginnode;
//		VWFC_ASSERT(center==two->endnode || center==two->beginnode);
	}

	//here something tricky
	// the factor 10000.0 is needed to asure that the pointonline
	// is more accurate in this case compared to the intersection for graphs
	Sint32 uitp=temp_line->PointOnLine(two->GetOther(center), distance, accur);

	delete temp_line;

	/*double uitp=	(_x - first._x) * (third._y - _y) -
					(_y - first._y) * (third._x - _x);
	if (uitp>0) return IS_LEFT;
	if (uitp<0) return IS_RIGHT;
	return IS_ON;*/

	//depending on direction of this link (going to or coming from centre)
	if (center==endnode)
	{
	  if (uitp==LEFT_SIDE)
			return IS_LEFT;
	  if (uitp==RIGHT_SIDE)
			return IS_RIGHT;
	}
	else  //center=beginnode
	{
	  if (uitp==LEFT_SIDE)
			return IS_RIGHT;
	  if (uitp==RIGHT_SIDE)
			return IS_LEFT;
	}
	return IS_ON;
}

//
//	Return the position of the third link compared to this link and
// the second link
// Result = IS_ON | IS_LEFT | IS_RIGHT
//
LinkStatus KBoolLink::PointOnCorner(KBoolLink* const two, KBoolLink* const third)
{
	LinkStatus
		TwoToOne,		// Position of two to this line
		ThirdToOne,    // Position of third to this line
		ThirdToTwo,		// Position of third to two
		Result;

//m		Node*	center;

//the this link should connect to the other two link at at least one node
//m		if (endnode==two->endnode || endnode==two->beginnode)
//m			center=endnode;
//m		else
//m		{	center=beginnode;
//		VWFC_ASSERT(center==two->endnode || center==two->beginnode);
//m	}
//	VWFC_ASSERT(center==third->endnode || center==third->beginnode);



	// Calculate the position of the links compared to eachother
	TwoToOne	 = OutProduct(two,ACTIVE_BoolEng->GetAccur());
	ThirdToOne= OutProduct(third,ACTIVE_BoolEng->GetAccur());
	//center is used in outproduct to give de direction of two
	// this is why the result should be swapped
	ThirdToTwo=	two->OutProduct(third,ACTIVE_BoolEng->GetAccur());
	if (ThirdToTwo==IS_RIGHT)
	  ThirdToTwo=IS_LEFT;
	else if (ThirdToTwo==IS_LEFT)
	  ThirdToTwo=IS_RIGHT;

	// Select the result
	switch(TwoToOne)
	{
		// Line 2 lies on  leftside of this line
		case IS_LEFT : if ((ThirdToOne==IS_RIGHT) || (ThirdToTwo==IS_RIGHT))	return IS_RIGHT;
							else if ((ThirdToOne==IS_LEFT) && (ThirdToTwo==IS_LEFT))	return IS_LEFT;
							else	Result=IS_ON;	break;
		// Line 2 lies on this line
		case IS_ON	 :	if ((ThirdToOne==IS_RIGHT) && (ThirdToTwo==IS_RIGHT))		  return IS_RIGHT;
							else if ((ThirdToOne==IS_LEFT) && (ThirdToTwo==IS_LEFT))   return IS_LEFT;
					  //		else if ((ThirdToOne==IS_RIGHT) && (ThirdToTwo==IS_LEFT))   return IS_RIGHT;
					  //		else if ((ThirdToOne==IS_LEFT) && (ThirdToTwo==IS_RIGHT))   return IS_LEFT;
							else	Result=IS_ON;	break;
		// Line 2 lies on right side of this line
		case IS_RIGHT :if ((ThirdToOne==IS_RIGHT) && (ThirdToTwo==IS_RIGHT))	return IS_RIGHT;
							else if ((ThirdToOne==IS_LEFT) || (ThirdToTwo==IS_LEFT)) return IS_LEFT;
							else	Result=IS_ON;	break;
	}
	return Result;
}

//
// Remove the reference from this link to a_node
//
void KBoolLink::Remove(Node *a_node)
{
	(beginnode==a_node) ? beginnode=NULL : endnode=NULL;
}


//
//	Replace oldnode by newnode and correct the references
//
void KBoolLink::Replace(Node *oldnode, Node *newnode)
{	if (beginnode==oldnode)
	{	beginnode->RemoveLink(this);	// remove the reference to this
		newnode->AddLink(this);       // let newnode refer to this
		beginnode=newnode;				// let this refer to newnode
	}
	else
	{	//VWFC_ASSERT(endnode==oldnode);
		endnode->RemoveLink(this);
		newnode->AddLink(this);
		endnode=newnode;
	}
}


//
//	Reset all values
//
void KBoolLink::Reset()
{
	beginnode = 0;
	endnode = 0;
	Reset_flags();
}


//
//	Reset all flags
//
void KBoolLink::Reset_flags()
{
	bin	= false; 			// Marker for walking over the graph
	hole  = false;				// Is this a part of hole ?
	hole_top = false;	   	// link that is toplink of hole?
	group = GROUP_A;		   // Does this belong to group A or B ( o.a. for boolean operations between graphs)
	LeftA = false;     		// Is left in polygongroup A
	RightA= false;     		// Is right in polygon group A
	LeftB = false;     		// Is left in polygon group B
	RightB= false;     		// Is right in polygongroup B
	mark	= false;     		// General purose marker, internally unused
	merge = false;				// Marker for Merge
   holelink=false;
	a_substract_b= false;	// Marker for substract
	b_substract_a= false;	// Marker for substract
	intersect= false;			// Marker for intersect
	exor		= false;       // Marker for Exor
}

//
//	Refill this link by the arguments
//
void KBoolLink::Reset(Node *begin, Node *end,Sint32 graphnr)
{
	// Remove all the previous references
	UnLink();
	Reset();
	// Set the references of the node and of this link correct
	begin->AddLink(this);
	end->AddLink(this);
	beginnode=begin;
	endnode=end;
	if (graphnr!=0)
		graphnum=graphnr;
}


void KBoolLink::Set(Node *begin, Node *end)
{
	beginnode = begin;
	endnode = end;
}

void KBoolLink::SetBeenHere()
{
	bin = true;
}

void KBoolLink::SetNotBeenHere()
{
	bin = false;
}

void KBoolLink::SetBeginNode(Node* new_node)
{
	beginnode = new_node;
}


void KBoolLink::SetEndNode(Node* new_node)
{
	endnode = new_node;
}


//
//	Sets the graphnumber to argument num
//
void KBoolLink::SetGraphNum(const Sint32 num)
{
	graphnum=num;
}

kbGroupType KBoolLink::Group()
{
	return group;
}


//
// Reset the groupflag to argument groep
//
void KBoolLink::SetGroup(kbGroupType groep)
{
	group= groep;
}


//
//	Remove all references to this link and from this link
//
void KBoolLink::UnLink()
{
	if (beginnode)
	{	beginnode->RemoveLink(this);
		if (!beginnode->GetNumberOfLinks())	delete beginnode;
	}
	beginnode=NULL;
	if (endnode)
	{	endnode->RemoveLink(this);
		if (!endnode->GetNumberOfLinks())	delete endnode;
	}
	endnode=NULL;
}


void KBoolLink::UnMark()
{
	mark=false;
	bin=false;
}

void KBoolLink::SetMark(bool value)
{
	mark=value;
}

//
//	general purpose mark checker
//
bool KBoolLink::IsMarked()
{	return mark ;	}


void  KBoolLink::SetTopHole(bool value)
{	hole_top = value; }


bool KBoolLink::IsTopHole()
{	return hole_top;	}


//
// Calculates the merge/substact/exor/intersect flags
//
void	KBoolLink::SetLineTypes()
{
	bool Rand_A;
	bool Rand_B;
	bool Rand_AB;
	bool In_AB;
	bool In_A	;
	bool In_B	;

#define Buiten_A (!(Rand_A || In_A))  // Out of A is not in A and not a border of A
#define Buiten_B (!(Rand_B || In_B))

	//Rand_AB= (bool)((LeftA || LeftB)   ^  (RightA || RightB));    // Is it a border of group A and B together
	Rand_AB= !(( (LeftA || LeftB) &&  (RightA || RightB)) ||
                     (!(LeftA || LeftB) && !(RightA || RightB))
                    );    // Is it a border of group A and B together
	In_AB  = ((LeftA || LeftB)   && (RightA || RightB));		// Is it in group A or B
	Rand_A = ((LeftA && !RightA) || (RightA && !LeftA));		// Is it on a border of group A
	Rand_B = ((LeftB && !RightB) || (RightB && !LeftB));		// Is it on a border of group B
	In_A   = (LeftA && RightA);										// Is it in group A
	In_B   = (LeftB && RightB);										// Is it in group B

	merge     = Rand_AB ;  											// Only the borders of A and B together
	a_substract_b = ((In_AB && Rand_B) || (Rand_A && Buiten_B));
	b_substract_a = ((In_AB && Rand_A) || (Rand_B && Buiten_A));
	intersect = (((Rand_B && In_A) || (Rand_A && In_B)) || ((Rand_B && Rand_A) && !In_AB));
	exor      = !((Rand_AB && intersect) || (!Rand_AB && !intersect));

   //HELP the next does not work if using bitfields
	//exor      = (Rand_AB ^ intersect);
}


//put in direction with a_node as beginnode
void  KBoolLink::Redirect(Node* a_node)
{
   if (a_node != beginnode)
   {
		// swap the begin- and endnode of the current link
		Node* dummy = beginnode;
		beginnode=endnode;
		endnode=dummy;
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// lpoint.cpp
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Constructors
LPoint::LPoint()
{
	_x = 0;
	_y = 0;
}


LPoint::LPoint(B_INT const X, B_INT const Y)
{
	_x = X;
	_y = Y;
}


LPoint::LPoint(LPoint* const a_point)
{
	if (!a_point)
		throw Bool_Engine_Error("Cannot copy a NULL Point Object.\n\nCould not create a LPoint Object.",
						"Fatal Creation Error", 0, 1);
	_x = a_point->_x;
	_y = a_point->_y;
}


B_INT LPoint::GetX()
{
	return _x;
}

B_INT LPoint::GetY()
{
	return _y;
}


void LPoint::SetX(B_INT a_point_x)
{
	_x = a_point_x;
}


void LPoint::SetY(B_INT a_point_y)
{
	_y = a_point_y;
}


LPoint LPoint::GetPoint()
{
	return *this;
}


void LPoint::Set(const B_INT X,const B_INT Y)
{
	_x = X;
	_y = Y;
}


void LPoint::Set(const LPoint &a_point)
{
	_x = a_point._x;
	_y  =a_point._y;
}

bool LPoint::Equal(const LPoint a_point, B_INT Marge)
{
	B_INT delta_x, delta_y;

	delta_x = babs((_x - a_point._x));
	delta_y = babs((_y - a_point._y));

	if ((delta_x <= Marge) && (delta_y <= Marge))
		return true;
	else
		return false;
}


bool LPoint::Equal(const B_INT X, const B_INT Y, B_INT Marge)
{
	return (bool)((babs(_x - X) <= Marge) && (babs(_y - Y) <= Marge));
}

bool LPoint::ShorterThan(const LPoint a_point, B_INT Marge)
{
	double a,b;
	a = (double) (a_point._x - _x);
	a*= a;
	b = (double) (a_point._y - _y);
	b*= b;

	return (bool) ( (a+b) <= Marge*Marge ? true : false ) ;
}


bool LPoint::ShorterThan(const B_INT X, const B_INT Y, B_INT Marge)
{
	double a,b;
	a = (double) (X - _x);
	a*= a;
	b = (double) (Y - _y);
	b*= b;

	return (bool) ( a+b <= Marge*Marge ? true : false ) ;
}


// overload the assign (=) operator
// usage : a_point = another_point;

LPoint &LPoint::operator=(const LPoint &other_point)
{
	_x = other_point._x;
	_y = other_point._y;
	return *this;
}


// overload the + operator
// usage : a_point = point1 + point2;

LPoint &LPoint::operator+(const LPoint &other_point)
{
	_x += other_point._x;
	_y += other_point._y;
	return *this;
}



// overload the - operator
// usage : a_point = point1 - point2;

LPoint &LPoint::operator-(const LPoint &other_point)
{
	_x -= other_point._x;
	_y -= other_point._y;
	return *this;
}


// overload the * operator
// usage: a_point = point1 * 100;

LPoint &LPoint::operator*(Sint32 factor)
{
	_x *= factor;
	_y *= factor;
	return *this;
}


// overload the / operator
// usage: a_point = point1 / 100;

LPoint &LPoint::operator/(Sint32 factor)
{
	_x /= factor;
	_y /= factor;
	return *this;
}


// overload the compare (==) operator
// usage: if (point1 == point2) { };

Sint32 LPoint::operator==(const LPoint &other_point) const
{
	return ((other_point._x == _x) && (other_point._y == _y));
}


// overload the diffrent (!=) operator
// usage: if (point1 != point2) { };

Sint32 LPoint::operator!=(const LPoint &other_point) const
{
	return ((other_point._x != _x) || (other_point._y != _y));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// node.cpp
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//////////////////////////////////////////////////////////////////////////////////////////////////////////


//this here is to initialize the static iterator of node
//with NOLIST constructor
TDLI<KBoolLink> 	Node::_linkiter=TDLI<KBoolLink>();

Node::Node() : LPoint(0,0)
{
	_linklist=SDK_NEW DL_List<void*>();
}


Node::Node(B_INT const X, B_INT const Y) : LPoint(X,Y)
{

	_linklist=SDK_NEW DL_List<void*>();
}


Node::Node(LPoint* const a_point) : LPoint(a_point)
{
	_linklist=SDK_NEW DL_List<void*>();
}


//Node::Node(Node * const other) : LPoint(other)
Node::Node(Node * const other)
{
	_x = other->_x;
	_y = other->_y;
	_linklist=SDK_NEW DL_List<void*>();
}

Node& Node::operator=(const Node &other_node)
{
	_x = other_node._x;
	_y = other_node._y;

	return *this;
}


// x and y of the point will be rounded to the nearest
// xnew=N*grid and ynew=N*grid
void Node::Round(B_INT grid)
{
  _x=(B_INT) floor((_x + grid * 0.5) / grid) * grid;
  _y=(B_INT) floor((_y + grid * 0.5) / grid) * grid;
}

Node::~Node()
{
  delete _linklist;
}

DL_List<void*>* Node::GetLinklist()
{
	return _linklist;
}

void Node::AddLink(KBoolLink *a_link)
{
//	assert(a_link);
	_linklist->insbegin(a_link);
}

KBoolLink* Node::GetIncomingLink()
{
	if (((KBoolLink*)_linklist->headitem())->GetEndNode() == this)
		return (KBoolLink*)_linklist->headitem();
   else
		return (KBoolLink*)_linklist->tailitem();
}

KBoolLink* Node::GetOutgoingLink()
{
	if (((KBoolLink*)_linklist->headitem())->GetBeginNode() == this)
		return (KBoolLink*)_linklist->headitem();
   else
		return (KBoolLink*)_linklist->tailitem();
}

//
// Returns the number of connected links
//
Sint32	Node::GetNumberOfLinks()
{
   return _linklist->count();
}

KBoolLink* Node::GetOtherLink(KBoolLink* prev)
{
	if (prev==(KBoolLink*)_linklist->headitem())
      return (KBoolLink*)_linklist->tailitem();
	if (prev==(KBoolLink*)_linklist->tailitem())
      return (KBoolLink*)_linklist->headitem();

	return NULL;
}


Sint32 Node::Merge(Node *other)
{
   if (this==other) //they are already merged dummy
      return 0;

	_linkiter.Attach(_linklist);
	Sint32 Counter;
	// used to delete Iterator on other->_linklist
	// otherwise there can't be a takeover, because for takeover there can't
	// be an iterator on other->_linklist;
   {
      TDLI<KBoolLink> Iother(other->_linklist);
      KBoolLink* temp;

      Counter = Iother.count();

      Iother.tohead();
      while (!Iother.hitroot())
      {
         temp=Iother.item();
         //need to test both nodes because it may be a zero length link
         if (temp->GetEndNode()==other)
            temp->SetEndNode(this);
         if (temp->GetBeginNode()==other)
            temp->SetBeginNode(this);
         Iother++;
      }
      _linkiter.takeover(&Iother);
   }
	_linkiter.Detach();

   //at this moment the other nodes has no link pointing to it so it needs to be deleted
   delete other;
	return Counter;
}


void Node::RemoveLink(KBoolLink *a_link)
{
//	assert(a_link);
	_linkiter.Attach(_linklist);

	if (_linkiter.toitem(a_link))	// find the link
   	_linkiter.remove();
	_linkiter.Detach();
}

// This function will determinate if the given three points
// can be simplified to two points
//
// input : three nodes, the first and the second must be points of
//			  a line in correct order, the third point is a point of another
//         line.
// output: -
// return: true if points can be simplified
//			  false if points can't be simplified
bool Node::Simplify(Node *First, Node *Second, B_INT Marge)
{
	double distance=0;

	// The first and second point are a zero line, if so we can
	// make a line between the first and third point
	if (First->Equal(Second,Marge))
		return true;

	// Are the first and third point equal, if so
	// we can delete the second point
	if (First->Equal(this, Marge))
		return true;

	// Used tmp_link.set here, because the link may not be linked in the graph,
	// because the point of the graphs are used, after use of the line we have
	//to set the link to zero so the nodes will not be destructed by exit of the function
	KBoolLink tmp_link;
	tmp_link.Set(First,Second);
	KBoolLine tmp_line;
	tmp_line.Set(&tmp_link);

	//	If third point is on the same line which is made from the first
	// and second point then we can delete the second point
	if (tmp_line.PointOnLine(this,distance, (double) Marge) == ON_AREA)
	{
		tmp_link.Set(NULL,NULL);
		return true;
	}
	//
	//
	tmp_link.Set(Second,this);
	tmp_line.Set(&tmp_link);
	if (tmp_line.PointOnLine(First,distance, (double) Marge) == ON_AREA)
	{
		tmp_link.Set(NULL,NULL);
		return true;
	}
	tmp_link.Set(NULL,NULL);
	return false;
}


KBoolLink* Node::GetNextLink()
{
	Sint32 Aantal = _linklist->count();

//	assert (Aantal != 0);

	// there is one link, so there is no previous link
	if (Aantal == 1)
		return NULL;
	Sint32 Marked_Counter = 0;
	KBoolLink *the_link = NULL;

	// count the marked links
	_linkiter.Attach(_linklist);
	_linkiter.tohead();
	while (!_linkiter.hitroot())
	{
		if (_linkiter.item()->IsMarked())
			Marked_Counter++;
		else
		{
			if (!the_link)
				the_link = _linkiter.item();
		}
		_linkiter++;
	}
	_linkiter.Detach();
	if (Aantal - Marked_Counter != 1)
			// there arent two unmarked links
			return NULL;
	else
	{
		if (the_link->GetBeginNode() == this)
			return the_link;
		else
			return NULL;
	}
}


KBoolLink* Node::GetPrevLink()
{
	Sint32 Aantal;
	if (!_linklist)
		return NULL;

	Aantal = _linklist->count();

//	assert (Aantal != 0);

	// there is one link, so there is no previous link
	if (Aantal == 1)
		return NULL;

	Sint32 Marked_Counter = 0;
	KBoolLink *the_link = NULL;

	_linkiter.Attach(_linklist);
	// count the marked links
	_linkiter.tohead();
	while (!_linkiter.hitroot())
	{
		if (_linkiter.item()->IsMarked())
			Marked_Counter++;
		else
		{
			if (!the_link)
				the_link = _linkiter.item();
		}
		_linkiter++;
	}
	_linkiter.Detach();
	if (Aantal - Marked_Counter != 1)
			// there arent two unmarked links
			return NULL;
	else
	{
		if (the_link->GetEndNode() == this)
			return the_link;
		else
			return NULL;
	}
}

//  on the node get the link
//  is the most right or left one
//  This function is used to collect the simple graphs from a graph
KBoolLink* Node::GetMost( KBoolLink* const prev ,LinkStatus whatside)
{
	KBoolLink *temp,*Result=0,*reserve=0;
	Node* prevbegin=prev->GetOther(this);

	if (_linklist->count() == 2) // only two links to this node take the one != prev
	{
		if ( (temp=(KBoolLink*)_linklist->headitem()) == prev )      //this is NOT the one to go on
         temp=(KBoolLink*)_linklist->tailitem();
		if (temp->BeenHere())
			//we are back where we started (bin is true) return Null
			return(0);
		return  temp;
	}

	_linkiter.Attach(_linklist);
	_linkiter.tohead();
	//more then 2 links to the Node
	while(!_linkiter.hitroot())
	{
		if ( (!_linkiter.item()->BeenHere()) &&
			  (_linkiter.item()!=prev )   //should be set to bin already
			)
		{
			if (prevbegin==_linkiter.item()->GetOther(this) )//pointers equal
				//we are going back in the same direction on a parallel link
				//only take this possibility if nothing else is possible
				reserve=_linkiter.item();
			else
			{  //this link is in a different direction
				if (!Result)
					Result=_linkiter.item(); //first one found sofar
				else
				{
					if	(prev->PointOnCorner(Result,_linkiter.item())==whatside)
						//more right than take this one
						Result=_linkiter.item();
				}
			}
		}
		_linkiter++;
	}

	// if there is a next link found return it
	// else if a parallel link is found return that one
	// else return NULL
	_linkiter.Detach();
	return ((Result) ? Result : reserve);
}


// this function gets the highest not flat link
KBoolLink* Node::GetNotFlat()
{
	KBoolLink *Result=NULL,*link;

	_linkiter.Attach(_linklist);

   double tangold;
   double tangnew;

	for(_linkiter.tohead();!_linkiter.hitroot();_linkiter++)
	{
		link=_linkiter.item();
		if (!_linkiter.item()->BeenHere())
		{
         B_INT dx=link->GetOther(this)->GetX()-_x;
         B_INT dy=link->GetOther(this)->GetY()-_y;
         if (dx!=0)
	         tangnew=fabs( (double) dy / (double) dx );
         else
            tangnew=MAXDOUBLE;
			if (!Result)
         {
			  //this link is in a different direction
				Result=link; //first one found sofar
	         tangold=tangnew;
         }
         else
         {
           if(tangnew < tangold)
           {
					//this one is higher (more horizontal) then the old Result
					Result=link;
               tangold=tangnew;
           }
			}
		}
	}

	// if there is a next link found return it
	// else if a parallel link is found return that one
	// else return NULL
	_linkiter.Detach();
	return (Result);
}

//  on the node get the link that is not BIN
//  and that has the same graphnumber and is in same direction
KBoolLink *Node::Follow(KBoolLink* const prev )
{
   KBoolLink *temp;
	_linkiter.Attach(_linklist);

	_linkiter.tohead();
	while(!_linkiter.hitroot())
	{
		if (( _linkiter.item() != prev ) &&
			 ( !_linkiter.item()->BeenHere()) &&
			 ( _linkiter.item()->GetGraphNum() == prev->GetGraphNum()) &&
			 (
				( (prev->GetEndNode()   == this) &&
				  (_linkiter.item()->GetEndNode()  !=this)
				)
				||
				( (prev->GetBeginNode() == this) &&
				  (_linkiter.item()->GetBeginNode() !=this)
				)
			 )
			)
		{
			temp=_linkiter.item();
			_linkiter.Detach();
			return(temp);
		}
		_linkiter++;
	}

	_linkiter.Detach();
	return (0);
}

// this function gets the highest (other node) link ascending from the node
// that has the bin flag set as the argument binset
// if no such link exists return 0
KBoolLink* Node::GetBinHighest(bool binset)
{
	KBoolLink *Result=NULL,*link;
	_linkiter.Attach(_linklist);

   double tangold;
   double tangnew;

	for(_linkiter.tohead();!_linkiter.hitroot();_linkiter++)
	{
		link=_linkiter.item();
		if (_linkiter.item()->BeenHere() == binset)
		{
         B_INT dx=link->GetOther(this)->GetX()-_x;
         B_INT dy=link->GetOther(this)->GetY()-_y;
         if (dx!=0)
	         tangnew = (double) dy / (double) dx;
         else if (dy > 0)
            tangnew = MAXDOUBLE;
         else
            tangnew = -MAXDOUBLE;

			if (!Result)
         {
				Result = link; //first one found sofar
	         tangold = tangnew;
         }
         else
         {
           if(tangnew > tangold)
           {
					//this one is higher then the old Result
					Result = link;
               tangold = tangnew;
           }
			}
		}
	}

	// if there is a link found return it
	// else return NULL
	_linkiter.Detach();
	return (Result);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// record.cpp
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//////////////////////////////////////////////////////////////////////////////////////////////////////////


#define LNK _line.GetLink()

Sint32 r_index=-1;
void* _Record_Pool[30];

void DeleteRecordPool()
{
   while (r_index!=-1)
   {
     free( _Record_Pool[r_index--]);
   }
}

Record::~Record()
{
}


void* Record::operator new(size_t size)
{

   if (r_index!=-1)
   {
     return _Record_Pool[r_index--];
   }

   return malloc(size);
}

void Record::operator delete(void* recordptr)
{

   if (r_index < 28)
   {
     _Record_Pool[++r_index]= recordptr;
     return;
   }

	free (recordptr);
}

void Record::deletepool()
{

   while (r_index!=-1)
   {
     free( _Record_Pool[r_index--]);
   }
}

Record::Record(KBoolLink* link)
{
	_dir=GO_RIGHT;
   _a=0;
   _b=0;
	_line.Set(link);
	_line.CalculateLineParameters();
}


//when the dimensions of a link for a record changes, its line parameters need to be recalculated
void Record::SetNewLink(KBoolLink* link)
{
	_line.Set(link);
   _line.CalculateLineParameters();
}

//for beams calculate the ysp on the low scanline
void Record::Calc_Ysp(Node* low)
{
	if ((LNK->GetEndNode() == low) || (LNK->GetBeginNode() == low))
   {
      _ysp=low->GetY();
      return;
   }

   if	(LNK->GetEndNode()->GetX() == LNK->GetBeginNode()->GetX())
         _ysp=low->GetY(); //flatlink only in flatbeams
   else if (LNK->GetEndNode()->GetX() == low->GetX())
         _ysp=LNK->GetEndNode()->GetY();
   else if (LNK->GetBeginNode()->GetX() == low->GetX())
         _ysp=LNK->GetBeginNode()->GetY();
   else
      	_ysp=_line.Calculate_Y_from_X(low->GetX());
}

//to set the _dir for new links in the beam
void Record::Set_Flags()
{
	if (LNK->GetEndNode()->GetX()==LNK->GetBeginNode()->GetX()) //flatlink ?
	{  //only happens in flat beams
		if (LNK->GetEndNode()->GetY() < LNK->GetBeginNode()->GetY())
			_dir=GO_RIGHT;
		else
			_dir=GO_LEFT;
	}
	else
	{
		if (LNK->GetEndNode()->GetX() > LNK->GetBeginNode()->GetX())
			_dir=GO_RIGHT;
		else
			_dir=GO_LEFT;
	}
}

KBoolLink* Record::GetLink()
{
	return LNK;
}

B_INT Record::Ysp()
{
	return _ysp;
}

void Record::SetYsp(B_INT ysp)
{
	_ysp=ysp;
}

DIRECTION Record::Direction()
{
	return DIRECTION(_dir);
}

bool Record::Calc_Left_Right(Record* record_above_me)
{
   bool par=false;

   if (!record_above_me)   //null if no record above
   { 	_a=0;_b=0;  }
   else
   {
   	_a=record_above_me->_a;
   	_b=record_above_me->_b;
   }

   switch (_dir&1)
   {
      case GO_LEFT	:	if (LNK->Group() == GROUP_A)
                        {
                           LNK->SetRightA((bool)(_a>0));

                           if (ACTIVE_BoolEng->GetWindingRule())
                              LNK->GetInc() ? _a++ : _a--;
                           else
                           {  //ALTERNATE
                              if (_a)
                                 _a=0;
                              else
                                 _a=1;
                           }

                           LNK->SetLeftA((bool)(_a>0));
                           LNK->SetLeftB((bool)(_b>0));
                           LNK->SetRightB((bool)(_b>0));
                        }
                        else
                        {
                           LNK->SetRightA((bool)(_a > 0));
                           LNK->SetLeftA((bool)(_a>0));
                           LNK->SetRightB((bool)(_b>0));

                           if (ACTIVE_BoolEng->GetWindingRule())
                              LNK->GetInc() ? _b++ : _b--;
                           else //ALTERNATE
                           {
                               if (_b)
                                    _b=0;
                               else
                                    _b=1;
                           }

                           LNK->SetLeftB((bool)(_b>0));
                        }
                           break;
      case	GO_RIGHT	:	if (LNK->Group() == GROUP_A)
                        {
                           LNK->SetLeftA((bool)(_a>0));

                           if (ACTIVE_BoolEng->GetWindingRule())
                              LNK->GetInc() ? _a++ : _a--;
                           else
                           {  //ALTERNATE
                              if (_a)
                                 _a=0;
                              else
                                 _a=1;
                           }

                           LNK->SetRightA((bool)(_a>0));
                           LNK->SetLeftB((bool)(_b>0));
                           LNK->SetRightB((bool)(_b>0));
                        }
                        else
                        {
                           LNK->SetRightA((bool)(_a>0));
                           LNK->SetLeftA((bool)(_a>0));
                           LNK->SetLeftB((bool)(_b>0));

                           if (ACTIVE_BoolEng->GetWindingRule())
                              LNK->GetInc() ? _b++ : _b--;
                           else
                           {  //ALTERNATE
                              if (_b)
                                 _b=0;
                              else
                                 _b=1;
                           }

                           LNK->SetRightB((bool)(_b>0));
                        }
                        break;
      default			:  ACTIVE_BoolEng->error("Undefined Direction of link","function IScanBeam::Calc_Set_Left_Right()");
                        break;
   }

//THE NEXT WILL WORK for MOST windingrule polygons,
//even when not taking into acount windingrule
// not all
/*
   switch (_dir&1)
   {
      case GO_LEFT	:	if (LNK->Group() == GROUP_A)
                        {
                           LNK->SetRightA((bool)(_a>0));

                           if (booleng->Get_WindingRule())
                              LNK->GetInc() ? _a++ : _a--;
                           else
                              _a--;

                           LNK->SetLeftA((bool)(_a>0));
                           LNK->SetLeftB((bool)(_b>0));
                           LNK->SetRightB((bool)(_b>0));
                        }
                        else
                        {
                           LNK->SetRightA((bool)(_a > 0));
                           LNK->SetLeftA((bool)(_a>0));
                           LNK->SetRightB((bool)(_b>0));

                           if (booleng->Get_WindingRule())
                              LNK->GetInc() ? _b++ : _b--;
                           else
                              _b--;

                           LNK->SetLeftB((bool)(_b>0));
                        }
                           break;
      case	GO_RIGHT	:	if (LNK->Group() == GROUP_A)
                           {
                              LNK->SetLeftA((bool)(_a>0));

                              if (booleng->Get_WindingRule())
                                 LNK->GetInc() ? _a++ : _a--;
                              else
                                 _a++;

                              LNK->SetRightA((bool)(_a>0));
                              LNK->SetLeftB((bool)(_b>0));
                              LNK->SetRightB((bool)(_b>0));
                           }
                        else
                           {
                              LNK->SetRightA((bool)(_a>0));
                              LNK->SetLeftA((bool)(_a>0));
                              LNK->SetLeftB((bool)(_b>0));

                              if (booleng->Get_WindingRule())
                                 LNK->GetInc() ? _b++ : _b--;
                              else
                                 _b++;

                              LNK->SetRightB((bool)(_b>0));
                           }
                        break;
      default			:  _messagehandler->error("Undefined Direction of link","function IScanBeam::Calc_Set_Left_Right()");
                        break;
   }
*/
   //if the records are parallel (same begin/endnodes)
   //the above link a/b flag are adjusted to the current a/b depth
   if (record_above_me && Equal(record_above_me))
   {
      par=true;
		LNK->Mark();
   	record_above_me->_a=_a;
   	record_above_me->_b=_b;
		if (Direction()== GO_LEFT)
		{
         //set the bottom side  of the above link
         if (record_above_me->Direction()== GO_LEFT)
         {
            record_above_me->LNK->SetLeftA(LNK->GetLeftA());
            record_above_me->LNK->SetLeftB(LNK->GetLeftB());
         }
         else
         {
            record_above_me->LNK->SetRightA(LNK->GetLeftA());
            record_above_me->LNK->SetRightB(LNK->GetLeftB());
         }
		}
		else
		{
         //set the bottom side  of the above link
         if (record_above_me->Direction()== GO_LEFT)
         {
            record_above_me->LNK->SetLeftA(LNK->GetRightA());
            record_above_me->LNK->SetLeftB(LNK->GetRightB());
         }
         else
         {
            record_above_me->LNK->SetRightA(LNK->GetRightA());
            record_above_me->LNK->SetRightB(LNK->GetRightB());
         }
		}
   }
   return par;
}

bool Record::Equal(Record *a)
{
	return((bool)( ( LNK->GetOther(a->LNK->GetBeginNode()) == a->LNK->GetEndNode())  &&
						  ( LNK->GetOther(a->LNK->GetEndNode())   == a->LNK->GetBeginNode())  ));
}


KBoolLine* Record::GetLine()
{
	return &_line;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// scanbeam.cpp
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// class scanbeam
// this class represents de space between two scanlines



//this here is to initialize the static iterator of scanbeam
//with NOLIST constructor

Sint32 recordsorter(Record* , Record* );

Sint32 recordsorter_ysp_angle(Record* , Record* );
Sint32 recordsorter_ysp_angle_back(Record* rec1, Record* rec2);

ScanBeam::ScanBeam()
{
	_type=NORMAL;
   _BI.Attach(this);
}

ScanBeam::~ScanBeam()
{
   //first delete all record still in the beam

   _BI.delete_all();
   _BI.Detach();

   DeleteRecordPool(); 
}

void ScanBeam::SetType(Node* low,Node* high)
{
   if (low->GetX() < high->GetX())
   	_type=NORMAL;
   else
   	_type=FLAT;
}

/*
//catch node to link crossings
// must be sorted on ysp
Sint32 ScanBeam::FindCloseLinksAndCross(TDLI<KBoolLink>* _I,Node* _lowf)
{
	Sint32 merges = 0;
	Record* record;

   TDLI<Record> _BBI=TDLI<Record>(this);

	if (_BI.count() > 1)
	{
		//first search a link towards this node
		for(_BI.tohead(); !_BI.hitroot(); _BI++)
		{
			record=_BI.item();
			if( (record->GetLink()->GetBeginNode()==_lowf) ||
				 (record->GetLink()->GetEndNode()  ==_lowf)
			  )
			  break;
		}

		//NOTICE if the node "a_node" is not inside a record
		//for instance to connected flat links (flatlinks not in beam)
		//then IL will be at end    (those will be catched at 90 degrees rotation)
		if (_BI.hitroot())
      {
			return(merges);
      }

      //from IL search back for close links
      _BBI.toiter(&_BI);
      _BBI--;
      while(!_BBI.hitroot())
      {
         record=_BBI.item();

         if (record->Ysp() != _lowf->GetY())
            break;

         // the distance to the low node is smaller then the MARGE
         if( (record->GetLink()->GetBeginNode()!=_lowf) &&
             (record->GetLink()->GetEndNode()  !=_lowf)
           )
         {  // the link is not towards the low node
            record->GetLink()->AddCrossing(_lowf);
            record->SetNewLink(record->GetLink()->ProcessCrossingsSmart(_I));
            merges++;
         }
         _BBI--;
      }

      //from IL search forward for close links
      _BBI.toiter(&_BI);
      _BBI++;
      while(!_BBI.hitroot())
      {
         record=_BBI.item();

         if (record->Ysp() != _lowf->GetY())
//         if (record->Ysp() < _lowf->GetY()-MARGE)
            break;

         // the distance to the low node is smaller then the MARGE
         if( (record->GetLink()->GetBeginNode()!=_lowf) &&
             (record->GetLink()->GetEndNode()  !=_lowf)
           )
         {  // the link is not towards the low node
            record->GetLink()->AddCrossing(_lowf);
            record->SetNewLink(record->GetLink()->ProcessCrossingsSmart(_I));
            merges++;
         }
         _BBI++;
      }
   }
	return merges;
}
*/

/*
bool  ScanBeam::Update(TDLI<KBoolLink>* _I,Node* _lowf)
{
	bool found=false;
	KBoolLink* link;

	_BI.tohead();
	while (!_BI.hitroot())
	{

		Record* record=_BI.item();
		record->Calc_Ysp(_type,_low);
		_BI++;
	}

   FindCloseLinksAndCross(_I,_lowf);

   _BI.tohead();
   while (!_BI.hitroot())
   {
      Record* record=_BI.item();
      //records containing links towards the new low node
      //are links to be marked for removal

      if ((record->GetLink()->GetEndNode() == _lowf) ||
          (record->GetLink()->GetBeginNode() == _lowf)
         )
      {
         //cross here the links that meat eachother now
         delete _BI.item();
         _BI.remove();

         //cross here the links that meat eachother now
         _BI--;
         if (!_BI.hitroot() && (_BI.count() > 1))
         {
            Record* prev=_BI.item();
            _BI++;
            if (!_BI.hitroot())
            {
               if (!_BI.item()->Equal(prev)) // records NOT parallel
                  if (_BI.item()->GetLine()->Intersect(prev->GetLine(),MARGE))
                  {
                     //they did cross, integrate the crossings in the graph
                     //this  may modify the links already part of the record
                     //this is why they are returned in set for the record
                     _BI.item()->SetNewLink(_BI.item()->GetLink()->ProcessCrossingsSmart(_I));
                     prev->SetNewLink(prev->GetLink()->ProcessCrossingsSmart(_I));
                  }
            }
         }
         else
          	_BI++;
      }
      else
         _BI++;
   }

	//writebeam();

   //ONLY links towards the low node are possible to be added
	//the bin flag will be set if it fits in the beam
	//so for following beams it will not be checked again
	while ( bool(link=_lowf->GetBinHighest(false)) )
	{
      Record* record=new Record(link);
      // yp_new will always be the y of low node since all new links are
      // from this node
      record->SetYsp(_lowf->GetY());
      record->Set_Flags(_type);
      //need to calculate ysn to be able to sort this record in the right order
      //this is only used when the insert node is equal for both records
      // ins_smart and cross neighbour  directly
      // if empty then just insert

      if (empty())
         insend(record);
      else
      {
         // put new item left of the one that is bigger
         _BI.tohead();
         while(!_BI.hitroot())
         {
            if (recordsorter_ysp_angle(record,_BI.item())==1)
               break;
            _BI++;
         }

         _BI.insbefore(record);
         _BI--;_BI--; //just before the new record inserted
         if (!_BI.hitroot())
         {
            Record* prev=_BI.item();
            _BI++; //goto the new record inserted
            if (!_BI.item()->Equal(prev)) // records NOT parallel
            {
               if (_BI.item()->GetLine()->Intersect(prev->GetLine(),MARGE))
               {
                  //this  may modify the links already part of the record
                  //this is why they are returned in set for the record
                  _BI.item()->SetNewLink(_BI.item()->GetLink()->ProcessCrossingsSmart(_I));
                  prev->SetNewLink(prev->GetLink()->ProcessCrossingsSmart(_I));
               }
            }
         }
         else
           _BI++;

         Record* prev=_BI.item(); //the new record
         _BI++;
         if (!_BI.hitroot() && !_BI.item()->Equal(prev)) // records NOT parallel
         {
	         Record* cur=_BI.item();
            if (cur->GetLine()->Intersect(prev->GetLine(),MARGE))
            {
               //this  may modify the links already part of the record
               //this is why they are returned in set for the record
               cur->SetNewLink(cur->GetLink()->ProcessCrossingsSmart(_I));
               prev->SetNewLink(prev->GetLink()->ProcessCrossingsSmart(_I));
            }
         }
      }
      //remember this to calculate in/out values for each new link its polygon again.
      GNI->insend(record->GetLink()->GetGraphNum());
      found=true;
	   record->GetLink()->SetBeenHere();
   }

   FindCloseLinksAndCross(_I,_lowf);
	//writebeam();
	return(found);
}
*/

bool  ScanBeam::FindNew(SCANTYPE scantype,TDLI<KBoolLink>* _II)
{
	bool holes=false;

   _low = _II->item()->GetBeginNode();

	KBoolLink* link;

	//if (!checksort())
	//	SortTheBeam();

   lastinserted=0;
   //ONLY links towards the low node are possible to be added
	//the bin flag will be set if it fits in the beam
	//so for following beams it will not be checked again
	while ( (link = _low->GetBinHighest(false)) != NULL )
   {
     	if ( (link->GetEndNode()->GetX() == link->GetBeginNode()->GetX()) //flatlink in flatbeam
           && ((scantype == NODELINK) || (scantype == LINKLINK) || (scantype == LINKHOLES))
         )
      {
            switch(scantype)
            {
               case NODELINK:
               {
                  //all vertical links in flatbeam are ignored
                  //normal link in beam
                  Record* record=new Record(link);
                  // yp_new will always be the y of low node since all new links are
                  // from this node
                  record->SetYsp(_low->GetY());
                  record->Set_Flags();
                  // put new item left of the one that is lower in the beam 
                  // The last one inserted in this loop, is already left of the current
                  // iterator position. So the new links are inerted in proper order.
                  _BI.insbefore(record);
                  _BI--;
	               Process_PointToLink_Crossings();
                  delete record;
                  _BI.remove();
                  break;
               }
               case LINKLINK:
               //is the new record a flat link
               {
                  KBoolLine flatline = KBoolLine(link);
                  Process_LinkToLink_Flat(&flatline);
                  //flatlinks are not part of the beams, still they are used to find new beams
                  //they can be processed now if the beginnode does not change, since this is used to
                  //to find new beams. and its position does not change
                  //ProcessCrossings does take care of this
	   				flatline.ProcessCrossings(_II);
		            break;
               }
               case LINKHOLES : //holes are never to flatlinks
			   default:
                   VWFC_ASSERT( true );
			}
      }
      else
      {
         //normal link in beam
         Record* record=new Record(link);
         // yp_new will always be the y of low node since all new links are
         // from this node
         record->SetYsp(_low->GetY());
         record->Set_Flags();
         // put new item left of the one that is lower in the beam 
         // The last one inserted in this loop, is already left of the current
         // iterator position. So the new links are inserted in proper order.
         _BI.insbefore(record);
         lastinserted++;

         //ACTIVE_BoolEng->Write_Log( "after insert" );
         writebeam();

         switch(scantype)
         {
          case NODELINK:
               _BI--;
               Process_PointToLink_Crossings();
               _BI++;
               break;
          case INOUT:
            {
               _BI--;
               //now we can set the _inc flag
					Generate_INOUT(record->GetLink()->GetGraphNum());
               _BI++;
            }
            break;
          case GENLR:
            {
               //now we can set the a/b group flags based on the above link
               _BI--;
               _BI--;
               Record* above=0;
               if (!_BI.hitroot())
                  above=_BI.item();
               _BI++;

               //something to do for winding rule

               if (record->Calc_Left_Right(above))
               {
                  delete record;
                  _BI.remove();
                  lastinserted--;
               }
               else
                  _BI++;
            }
            break;
          case LINKHOLES:
            _BI--;
            holes=ProcessHoles(true,_II) || holes;
            _BI++;
            break;
		  default:
			  break;
         }
      }
      link->SetBeenHere();
	}

   writebeam();

	return(holes);
}

bool  ScanBeam::RemoveOld(SCANTYPE scantype,TDLI<KBoolLink>* _II)
{
	bool 			found=false;
	bool 			holes=false;
   TDLI<Record>   _BBI=TDLI<Record>();
	bool 			attached=false;

   _low = _II->item()->GetBeginNode();

	found=false;
   switch(scantype)
   {
      case INOUT:
      case GENLR:
      case LINKHOLES:
      if (_type==NORMAL )
      {
         if (_low->GetBinHighest(true)) //is there something to remove
         {
            _BI.tohead();
            while (!_BI.hitroot())
            {
               Record* record=_BI.item();
               //records containing links towards the new low node
               //are links to be removed
               if ((record->GetLink()->GetEndNode() == _low) ||
                   (record->GetLink()->GetBeginNode() == _low)
                  )
               {
                  switch(scantype)
                  {
                     case LINKHOLES:
                          holes=ProcessHoles(false,_II) || holes;
						 break;
				     default:
						 break;
                  }
                  if (attached)   //there is a bug
                  {
                     _BBI.Detach();
                     if (!checksort())
                        SortTheBeam();
                     _BI.tohead();
                     attached=false;

                  }
                  delete _BI.item();
                  _BI.remove();
                  found=true;
               }
               else if (found) //only once in here
               {
                  attached=true;
                  found=false;
                  _BBI.Attach(this);
                  _BBI.toiter(&_BI); //this is the position new records will be inserted

                  //recalculate ysp for the new scanline
                  record->Calc_Ysp(_low);
                  _BI++;
               }
               else
               {
                  //recalculate ysp for the new scanline
                  record->Calc_Ysp(_low);
                  _BI++;
               }
            }

            if (attached)
            {
               _BI.toiter(&_BBI);
               _BBI.Detach();
            }

         }
         else
         {
            _BBI.Attach(this);
            _BBI.toroot();
            _BI.tohead();
            while (!_BI.hitroot())
            {
                  Record* record=_BI.item();

                  record->Calc_Ysp(_low);
                  if (!found && (record->Ysp() < _low->GetY()))
                  {
                     found=true;
                     _BBI.toiter(&_BI);
                  }
                  _BI++;
            }
            _BI.toiter(&_BBI);
            _BBI.Detach();
         }
      }
      else
      {  //because the previous beam was flat the links to remove are
         //below the last insert position
         if (_low->GetBinHighest(true)) //is there something to remove
         {
            //on record back bring us to the last inserted record
            //or if nothing was inserted the record before the last deleted record
            //if there was no record before the last deleted record this means
            //we where at the beginning of the beam, so at root

            //_BI << (lastinserted+1);
            //_BI--;
            //if (_BI.hitroot())  //only possible when at the begin of the beam
               _BI.tohead();
            while (!_BI.hitroot())
            {
               Record* record=_BI.item();
               //records containing links towards the new low node
               //are links to be removed
               if ((record->GetLink()->GetEndNode() == _low) ||
                   (record->GetLink()->GetBeginNode() == _low)
                  )
               {
                  switch(scantype)
                  {
                     case LINKHOLES:
                          holes=ProcessHoles(false,_II) || holes;
						 break;
					 default:
						 break;
                  }
                  delete _BI.item();
                  _BI.remove();
                  found=true;
               }
               else if (found) //only once in here
                  break;
               else if (record->Ysp() < _low->GetY())
                     //if flatlinks are not in the beam nothing will be found
                     //this will bring us to the right insertion point
                     break;
               else
                  _BI++;
            }
         }
         else
         {
            //on record back bring us to the last inserted record
            //or if nothing was inserted the record before the last deleted record
            //if there was no record before the last deleted record this means
            //we where at the beginning of the beam, so at root

            //_BI << (lastinserted+ 1);
            //_BI--;
            //if (_BI.hitroot())  //only possible when at the begin of the beam
               _BI.tohead();
            while (!_BI.hitroot())
            {
                  Record* record=_BI.item();
                  if (record->Ysp() < _low->GetY())
                     break;
                  _BI++;
            }
         }
      }
      break;

      case NODELINK:
      case LINKLINK:
      {
         if (_type == NORMAL)
         {
            Calc_Ysp();
            if (scantype==LINKLINK)
               Process_LinkToLink_Crossings();
            else
               SortTheBeam();
         }
         //else beam is already sorted because the added/removed flat links
         //do not change the ysp of links already there, new non flat links
         //are inserted in order, as result the beam stays sorted

         if (_low->GetBinHighest(true)) //is there something to remove
         {
            _BI.tohead();
            while (!_BI.hitroot())
            {
               Record* record=_BI.item();
               //records containing links towards the new low node
               //are links to be removed
               if ((record->GetLink()->GetEndNode() == _low) ||
                   (record->GetLink()->GetBeginNode() == _low)
                  )
               {
                  KBoolLine* line=record->GetLine();
                  if (scantype==NODELINK)
                      Process_PointToLink_Crossings();
                  line->ProcessCrossings(_II);
                  delete _BI.item();
                  _BI.remove();
                  found=true;
               }
               //because the beam is sorted on ysp, stop when nothing can be there to remove
               //and the right insertion point for new links has been found
               else if ((record->Ysp() < _low->GetY()))
                  break;
               else
                  _BI++;
            }
         }
         else
         {
            _BI.tohead();
            while (!_BI.hitroot())
            {
                  Record* record=_BI.item();
                  //because the beam is sorted on ysp, stop when
                  //the right insertion point for new links has been found
                  if ((record->Ysp() < _low->GetY()))
                     break;
                  _BI++;
            }
         }
      }
      break;
   }

	return(holes);
}


void ScanBeam::SortTheBeam()
{
	_BI.mergesort(recordsorter_ysp_angle);
}

void	ScanBeam::Calc_Ysp()
{
	_BI.tohead();
	while (!_BI.hitroot())
	{
		Record* record=_BI.item();
		KBoolLink* link=_BI.item()->GetLink();
      record->Calc_Ysp(_low);
		_BI++;
		
		link; // dumb use
	}
}

// this function will set for all the records which contain a link with the
// corresponding graphnumber the inc flag.
// The inc flag's function is to see in a beam if we go deeper in the graph or not
void ScanBeam::Generate_INOUT(Sint32 graphnumber)
{
	DIRECTION first_dir;
	Sint32 diepte=0;

   TDLI<Record>   _BBI=TDLI<Record>();
   _BBI.Attach(this);
	for( _BBI.tohead(); !_BBI.hitroot(); _BBI++ )
	{
   	// recalculate _inc again
		if ( _BBI.item()->GetLink()->GetGraphNum()==graphnumber)
		{	//found a link that belongs to the graph
			if (diepte==0)
			{	// first link found or at depth zero again
            // the direction is important since this is used to find out
            // if we go further in or out for coming links
				first_dir=_BBI.item()->Direction();
				_BBI.item()->GetLink()->SetInc(true);
				diepte=1;
			}
			else
			{	// according to depth=1 links set depth
				// verhoog of verlaag diepte
				if (_BBI.item()->Direction()==first_dir)
				{
					diepte++;
					_BBI.item()->GetLink()->SetInc(true);
				}
				else
				{
					diepte--;
					_BBI.item()->GetLink()->SetInc(false);
				}
			}
		}
		if ( _BBI.item() == _BI.item()) break; //not need to do the rest, will come in a later beam
	}
   _BBI.Detach();
}


// function ProcessHoles
//
// this function will search the closest link to a hole
// step one, search for a link that is marked (this is a hole)
// step two, this is tricky, the closest link is the previous link in
//				 the beam, but only in the beam that contains the highest node
//				 from the marked link.
//				 why ? : if the marked link has for the begin and end node different
//				 x,y values, see below as link C
//                                 B
//               A            +---------+
//          +----------+
//				                 ___--+
//		                ___---
//	               +---    C
//
//				 when we at first detect link C we would link it to link A, should work he
//				 but; we always link a hole at its topleft node, so the highest node
//				 and then we can't link to A but we should link to B
//				 so when we found the link, we will look if the node that will come
//				 in a later beam will be higher than the current, if so we will wait
//				 till that node comes around otherwise we will link this node to the
//				 closest link (prev in beam)
bool ScanBeam::ProcessHoles(bool atinsert,TDLI<KBoolLink>* _LI)
{
	// The scanbeam must already be sorted at this moment
   Node *topnode;
   bool foundholes=false;

   Record* record = _BI.item();
   KBoolLink* link = record->GetLink();

   if (!record->GetLine()->CrossListEmpty())
   {
      SortTheBeam();

      // link the holes in the graph to a link above.
      // a the link where the linecrosslist is not empty, means that
      //	there are links which refer to this link (must be linked to this link)
      //	make new nodes and links and set them, re-use the old link, so the links
      //	that still stand in the linecrosslist will not be lost.
      // There is a hole that must be linked to this link !
      TDLI<Node> I(record->GetLine()->GetCrossList());
      I.tohead();
      while(!I.hitroot())
      {
         topnode=I.item();
         I.remove();

         KBoolLine line;
         line.Set(link);

         B_INT Y=line.Calculate_Y(topnode->GetX());

         // Now we'll create four new nodes and four new links to make the link between
         // the graphs.

         //holes are always linked in a non hole or hole
         //for a non hole this link will be to the right
         //because non holes are right around
         //for holes this will be to the right also,
         //because the are left around but the link is always on the
         //bottom of the hole

         //			 linkA    nodeA  nodeD         linkD
         //	  o-------->--------o  o----------->------------
         //							  |  |
         //							  |  |
         //					 linkB  v  ^ linkC
         //							  |  |
         //							  |  |
         //		 outgoing*       |  |          incoming*
         //	  o------<----------o  o--------<----------o
         //						 nodeB  nodeC
         //
         // all holes are oriented left around


         Node * leftnode; //left node of clossest link
         (link->GetBeginNode()->GetX() < link->GetEndNode()->GetX()) ?
               leftnode=link->GetBeginNode():
               leftnode=link->GetEndNode();

         Node *node_A = SDK_NEW Node(topnode->GetX(),Y);
         Node *node_B = SDK_NEW Node(topnode);
         Node *node_C = SDK_NEW Node(topnode);
         Node *node_D = SDK_NEW Node(topnode->GetX(),Y);
         KBoolLink *link_A = SDK_NEW KBoolLink(0,leftnode, node_A);
         KBoolLink *link_B = SDK_NEW KBoolLink(0,node_A, node_B);
         KBoolLink *link_C = SDK_NEW KBoolLink(0,node_C, node_D);
         KBoolLink *link_D = _BI.item()->GetLink();
         link_D->Replace(leftnode,node_D);

         KBoolLink* in  = topnode->GetIncomingLink();
         KBoolLink* out = topnode->GetOutgoingLink();

         in->Replace(topnode, node_C);
         out->Replace(topnode, node_B);

         //is where we come from/link to a hole
         bool closest_is_hole=link->IsHoleMarked();

         link_A->SetHole(closest_is_hole);
         link_B->SetHole(closest_is_hole);
         link_C->SetHole(closest_is_hole);
         link_B->SetHoleLink(true);
         link_C->SetHoleLink(true);

         _LI->insbegin(link_A);
         _LI->insbegin(link_B);
         _LI->insbegin(link_C);

         delete topnode;
      }
   }

   if (link->IsTopHole() )
   {
      SortTheBeam();
      writebeam();
   }      
      
   if (link->IsTopHole() && !_BI.athead() )
   {
   	 // now we check if this hole should now be linked, or later
   	 // we always link on the node with the maximum y value, Why ? because i like it !
   	 // to link we put the node of the hole into the crosslist of the closest link !

       VWFC_ASSERT( record->Direction() == GO_LEFT );
       // he goes to the left
       if (atinsert)
       {
          if ( link->GetBeginNode()->GetY() <= link->GetEndNode()->GetY() )
          {
            topnode = link->GetEndNode();
            //the previous link in the scanbeam == the closest link to the hole in vertical
            //direction PUT this node into this link
            _BI--;
            _BI.item()->GetLine()->AddCrossing(topnode);
            _BI++;
            //reset tophole flag, hole has been processed
            link->SetTopHole(false);
            foundholes=true;
          }
       }
       else  //remove stage of links from te beam
       {
         //the tophole link was NOT linked at the insert stage, so it most be linked now
         topnode=_BI.item()->GetLink()->GetBeginNode();
         //the previous link in the scanbeam == the closest link to the hole in vertical
         //direction PUT this node into this link
         _BI--;
         _BI.item()->GetLine()->AddCrossing(topnode);
         _BI++;
         //reset mark to flag that this hole has been processed
         link->SetTopHole(false);
         foundholes=true;
       }
   }
   return foundholes;
}

//sort the records on Ysp if eqaul, sort on tangent at ysp
Sint32 recordsorter_ysp_angle(Record* rec1, Record* rec2)
{
	if (rec1->Ysp() > rec2->Ysp() )
		return(1);
	if (rec1->Ysp() < rec2->Ysp() )
		return(-1);
	//it seems they are equal
   //calculate the tangent of the link from leftmostnode to rightmost node
   double tangrec1;
   double tangrec2;

   double dx1 = double( rec1->GetLink()->GetEndNode()->GetX() - rec1->GetLink()->GetBeginNode()->GetX() );
   double dy1 = double( rec1->GetLink()->GetEndNode()->GetY() - rec1->GetLink()->GetBeginNode()->GetY() );
   double dx2 = double( rec2->GetLink()->GetEndNode()->GetX() - rec2->GetLink()->GetBeginNode()->GetX() );
   double dy2 = double( rec2->GetLink()->GetEndNode()->GetY() - rec2->GetLink()->GetBeginNode()->GetY() );

   if (rec1->Direction()==GO_LEFT)
   { dx1=-dx1;dy1=-dy1; }
   if (rec2->Direction()==GO_LEFT)
   { dx2=-dx2;dy2=-dy2; }

   if (dx1!=0)
      tangrec1=dy1/dx1;
   else
   {
     if (dy1>0)
      tangrec1=MAXDOUBLE;
     else
      tangrec1=-MAXDOUBLE;
   }
   if (dx2!=0)
      tangrec2=dy2/dx2;
   else
   {
     if (dy2>0)
      tangrec2=MAXDOUBLE;
     else
      tangrec2=-MAXDOUBLE;
   }


   if (tangrec1 > tangrec2)
			return(1);
   if (tangrec1 < tangrec2)
			return(-1);
	return(0);
}

//sort the records on Ysp if eqaul, sort on tangent at ysp
Sint32 recordsorter_ysp_angle_back(Record* rec1, Record* rec2)
{
	if (rec1->Ysp() > rec2->Ysp() )
		return(1);
	if (rec1->Ysp() < rec2->Ysp() )
		return(-1);
	//it seems they are equal
   //calculate the tangent of the link from leftmostnode to rightmost node
   double tangrec1;
   double tangrec2;

   double dx1 = double( rec1->GetLink()->GetEndNode()->GetX()-rec1->GetLink()->GetBeginNode()->GetX() );
   double dy1 = double( rec1->GetLink()->GetEndNode()->GetY()-rec1->GetLink()->GetBeginNode()->GetY() );
   double dx2 = double( rec2->GetLink()->GetEndNode()->GetX()-rec2->GetLink()->GetBeginNode()->GetX() );
   double dy2 = double( rec2->GetLink()->GetEndNode()->GetY()-rec2->GetLink()->GetBeginNode()->GetY() );
   if (rec1->Direction()==GO_LEFT)
   { dx1=-dx1;dy1=-dy1; }
   if (rec2->Direction()==GO_LEFT)
   { dx2=-dx2;dy2=-dy2; }

   if (dx1!=0)
      tangrec1=dy1/dx1;
   else
   {
     if (dy1>0)
      tangrec1=MAXDOUBLE;
     else
      tangrec1=-MAXDOUBLE;
   }
   if (dx2!=0)
      tangrec2=dy2/dx2;
   else
   {
     if (dy2>0)
      tangrec2=MAXDOUBLE;
     else
      tangrec2=-MAXDOUBLE;
   }


   if (tangrec1 < tangrec2)
			return(1);
   if (tangrec1 > tangrec2)
			return(-1);
	return(0);
}

// swap functie for cocktailsort ==> each swap means an intersection of links
void swap_crossing_normal(Record *a, Record *b)
{

	if (!a->Equal(b)) // records NOT parallel
		a->GetLine()->Intersect_simple(b->GetLine());
}

void ScanBeam::Process_LinkToLink_Crossings()
{
	// sort on y value of next intersection; and find the intersections
	_BI.cocktailsort(recordsorter_ysp_angle_back, swap_crossing_normal);
}

//catch node to link crossings
// must be sorted on ysp
Sint32 ScanBeam::Process_PointToLink_Crossings()
{
	Sint32 merges = 0;
	Record* record;

	if (_BI.count() > 1)
	{
	   TDLI<Record> IL=TDLI<Record>(this);
	   IL.toiter(&_BI);

		//from IL search back for close links
		IL--;
		while(!IL.hitroot())
		{
			record=IL.item();

			if (record->Ysp() > _low->GetY()+ ACTIVE_BoolEng->GetInternalMarge())
				break;

			// the distance to the lo/hi node is smaller then the ACTIVE_BoolEng->GetInternalMarge()
			if( (record->GetLink()->GetBeginNode()!= _low) &&
				 (record->GetLink()->GetEndNode()  != _low)
			  )
			{  // the link is not towards the lohi node
				record->GetLine()->AddCrossing(_low);
				merges++;
			}
			IL--;
		}

		//from IL search forward for close links
		IL.toiter(&_BI);
		IL++;
		while(!IL.hitroot())
		{
			record=IL.item();

			if (record->Ysp() < _low->GetY()- ACTIVE_BoolEng->GetInternalMarge())
				break;

			// the distance to the lohi node is smaller then the booleng->Get_Marge()
			if( (record->GetLink()->GetBeginNode()!=_low) &&
				 (record->GetLink()->GetEndNode()  !=_low)
			  )
			{  // the link is not towards the low node
				record->GetLine()->AddCrossing(_low);
				merges++;
			}
			IL++;
		}

	}

	return merges;
}

Sint32 ScanBeam::Process_LinkToLink_Flat(KBoolLine* flatline)
{
	Sint32 crossfound = 0;
	Record* record;
   TDLI<Record> _BBI=TDLI<Record>();
   _BBI.Attach(this);
   _BBI.toiter(&_BI);

		for(_BI.tohead(); !_BI.hitroot(); _BI++)
		{
			record=_BI.item();

			if (record->Ysp() < (flatline->GetLink()->GetLowNode()->GetY() - ACTIVE_BoolEng->GetInternalMarge()))
				break;//they are sorted so no other can be there

			if ((record->Ysp() > (flatline->GetLink()->GetLowNode()->GetY() - ACTIVE_BoolEng->GetInternalMarge()))
				  &&
				 (record->Ysp() < (flatline->GetLink()->GetHighNode()->GetY() + ACTIVE_BoolEng->GetInternalMarge()))
				)
			{ //it is in between the flat link region
			  //create a new node at ysp and insert it in both the flatlink and the crossing link

				if (
						(record->GetLink()->GetEndNode()  != flatline->GetLink()->GetHighNode()) &&
						(record->GetLink()->GetEndNode()  != flatline->GetLink()->GetLowNode() ) &&
						(record->GetLink()->GetBeginNode()!= flatline->GetLink()->GetHighNode()) &&
						(record->GetLink()->GetBeginNode()!= flatline->GetLink()->GetLowNode() )
					)
				{
				  Node *newnode = SDK_NEW Node(_low->GetX(),_BI.item()->Ysp());
				  flatline->AddCrossing(newnode);
				  record->GetLine()->AddCrossing(newnode);
				  crossfound++;
				}
			}
		}

   _BI.toiter(&_BBI);
   _BBI.Detach();
	return crossfound;
}

bool ScanBeam::checksort()
{
	// if empty then just insert
	if (empty())
		return true;

   // put new item left of the one that is bigger
   _BI.tohead();
   Record* prev=_BI.item();
   _BI++;
   while(!_BI.hitroot())
   {
	   Record* curr=_BI.item();
      if (recordsorter_ysp_angle(prev,curr)==-1)
      {
         recordsorter_ysp_angle(prev,curr);
         return false;
      }
      prev=_BI.item();
      _BI++;
   }
   return true;
}

bool ScanBeam::writebeam()
{
   return true;
}
