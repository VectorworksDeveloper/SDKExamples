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


static void ArmBoolEng_3D(Bool_Engine* pBoolEngine);
static void SetPolygonA_3D(Bool_Engine* pBoolEngine, const VWPolygon3D& poly);
static void SetPolygonB_3D(Bool_Engine* pBoolEngine, const VWPolygon2D& poly);
static void GetResult_3D(Bool_Engine* pBoolEngine, const VWPolygon3D& refPoly, TSTLPolygons3DArray& out);
static void GetResult_3D(Bool_Engine* pBoolEngine, const VWPolygon3D& refPoly, VWPolygon3D& out);

VWPolygon3DOperation::VWPolygon3DOperation(const VWPolygon2D& clipPoly)
: VWPolygonOperation( clipPoly )
{
	m_pSTLCutResultArray	= NULL;
}

VWPolygon3DOperation::~VWPolygon3DOperation()
{
}

bool VWPolygon3DOperation::BooleanOR(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons)
{
	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
		return false;

	bool	ok		= true;

	try
	{
		((Bool_Engine*) m_pBooleanEngine)->Activate();
		::SetPolygonA_3D( (Bool_Engine*) m_pBooleanEngine, polygon );
		::SetPolygonB_3D( (Bool_Engine*) m_pBooleanEngine, m_clipPoly );
		((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_OR );
		::GetResult_3D( (Bool_Engine*) m_pBooleanEngine, polygon, resultPolygons );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

bool VWPolygon3DOperation::BooleanAND(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons, bool forceOperation/*=false*/)
{
	resultPolygons.clear();
	bool						isOK				= true;
	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
	{
		VWFC_ASSERT( false );						// bad input !
		isOK										= false;
	}

	if ( isOK )										// good input polygons.
	{
		VWPolygon2D				planarPoly;

		NNA_SCOPE				// for locking.
		{
			VWPolygon2D::CLockForEdit				lock( planarPoly );		// don't recalculate the bounds till the scope ends.

			polygon.GetPlanarPolygon( planarPoly );	// get planar polygon.
		}

		// XXX Bobi:
		// instead of 'VWPolygon3DOperation::AreOverlapping' use the following function which is faster.
		// check if the polygon operation is necessary.
		// if there are cases missed by the following function, try using 'ArePolygonsIntersecting'.
		bool					performOperation	= false;

		bool					noCommonArea;
		if ( forceOperation ||						// force the boolean operation.
			 VWPolygon2D::ArePolygonsIntersecting_Fast( m_clipPoly, planarPoly, noCommonArea ) )
		{
			performOperation						= true;
		}
		else
		{
			// 3 possible cases here:
			// - planar polygon of 'polygon' is inside the 'm_clipPoly'.
			// - 'm_clipPoly' is inside the planar polygon of the 'polygon' (perform the boolean operation in this case !).
			// - no common areas.

			if ( ! noCommonArea )								// might have common area. check!
			{
				size_t					polyPtCnt	= planarPoly.GetVertexCount();
				size_t					clipPtCnt	= m_clipPoly.GetVertexCount();
				if ( polyPtCnt > 2 && clipPtCnt > 2 )			// both polygons are correct.
				{
					size_t				maxPtCnt	= ( polyPtCnt > clipPtCnt ) ? polyPtCnt : clipPtCnt;
					for ( size_t i = 0 ; i < maxPtCnt ; ++ i )
					{
						if ( i < polyPtCnt )
						{
							const VWPoint2D&	vp	= planarPoly.GetVertexAt( i );
							if ( m_clipPoly.IsPtInPoly2D( vp.x, vp.y, VWPoint2D::sEpsilon ) )	// planarPoly is inside the m_clipPoly.
							{
								resultPolygons.push_back( polygon );
								break;
							}
						}

						if ( i < clipPtCnt )
						{
							const VWPoint2D&	vc	= m_clipPoly.GetVertexAt( i );
							if ( planarPoly.IsPtInPoly2D( vc.x, vc.y, VWPoint2D::sEpsilon ) )	// m_clipPoly is inside the planarPoly.
							{
								performOperation	= true;		// perform the boolean operation in this case !
								break;
							}
						}
					}
				}
			}
			// else: no common areas. no elements in resultPolygons.
		}

		if ( performOperation )						// the boolean operation must be performed.
		{
			VWPolygon2D			polyB( m_clipPoly );
			VWPolygon3D			polyA( polygon );

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
				::SetPolygonA_3D( (Bool_Engine*) m_pBooleanEngine, polyA );
				::SetPolygonB_3D( (Bool_Engine*) m_pBooleanEngine, polyB );
				((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_AND );
				::GetResult_3D( (Bool_Engine*) m_pBooleanEngine, polyA, resultPolygons );
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
					VWPolygon3D&	poly			=	resultPolygons[ i ];
					poly.InversePointsTransform( mat );
				}
			}
		}
	}

	// result.
	return	( isOK );
}

bool VWPolygon3DOperation::BooleanAND(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons, bool& outPolysOverlap, bool forceOperation/*=false*/)
{
	// init.
	bool						isOK				= true;
	resultPolygons.clear();
	outPolysOverlap				= false;

	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
	{
		VWFC_ASSERT( false );	// bad input !
		isOK					= false;
	}

	if ( isOK )										// good input polygons.
	{
		VWPolygon2D				planarPoly;

		NNA_SCOPE				// for locking.
		{
			VWPolygon2D::CLockForEdit				lock( planarPoly );		// don't recalculate the bounds till the scope ends.

			polygon.GetPlanarPolygon( planarPoly );	// get planar polygon.
		}

		// XXX Bobi:
		// instead of 'VWPolygon3DOperation::AreOverlapping' use the following function which is faster.
		// check if the polygon operation is necessary.
		// if there are cases missed by the following function, try using 'ArePolygonsIntersecting'.

		bool					performOperation	= false;

		bool					noCommonArea;
		// check for intersections.
		outPolysOverlap			= VWPolygon2D::ArePolygonsIntersecting_Fast( m_clipPoly, planarPoly, noCommonArea );

		if ( forceOperation ||	// force the boolean operation or ...
			 outPolysOverlap )	// ... polygons are intersecting (obviously - overlapping).
		{
			performOperation	= true;
		}
		else
		{
			// 3 possible cases here:
			// - planar polygon of 'polygon' is inside the 'm_clipPoly'.
			// - 'm_clipPoly' is inside the planar polygon of the 'polygon' (perform the boolean operation in this case !).
			// - no common areas.

			if ( ! noCommonArea )								// might have common area. check!
			{
				size_t					polyPtCnt	= planarPoly.GetVertexCount();
				size_t					clipPtCnt	= m_clipPoly.GetVertexCount();
				if ( polyPtCnt > 2 && clipPtCnt > 2 )			// both polygons are correct.
				{
					size_t				maxPtCnt	= ( polyPtCnt > clipPtCnt ) ? polyPtCnt : clipPtCnt;
					for ( size_t i = 0 ; i < maxPtCnt ; ++ i )
					{
						if ( i < polyPtCnt )
						{
							const VWPoint2D&	vp	= planarPoly.GetVertexAt( i );
							if ( m_clipPoly.IsPtInPoly2D( vp.x, vp.y, VWPoint2D::sEpsilon ) )	// planarPoly is inside the m_clipPoly.
							{
								resultPolygons.push_back( polygon );
								break;
							}
						}

						if ( i < clipPtCnt )
						{
							const VWPoint2D&	vc	= m_clipPoly.GetVertexAt( i );
							if ( planarPoly.IsPtInPoly2D( vc.x, vc.y, VWPoint2D::sEpsilon ) )	// m_clipPoly is inside the planarPoly.
							{
								outPolysOverlap		= true;		// polygons overlap.
								performOperation	= true;		// perform the boolean operation in this case !

								break;
							}
						}
					}
				}
			}
			// else: no common areas. no elements in resultPolygons.
		}

		if ( performOperation )	// the boolean operation must be performed.
		{
			VWPolygon2D			polyB( m_clipPoly );
			VWPolygon3D			polyA( polygon );

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
				::SetPolygonA_3D( (Bool_Engine*) m_pBooleanEngine, polyA );
				::SetPolygonB_3D( (Bool_Engine*) m_pBooleanEngine, polyB );
				((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_AND );
				::GetResult_3D( (Bool_Engine*) m_pBooleanEngine, polyA, resultPolygons );
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
					VWPolygon3D&	poly			=	resultPolygons[ i ];
					poly.InversePointsTransform( mat );
				}
			}
		}
	}

	// result.
	return	( isOK );
}

bool VWPolygon3DOperation::BooleanEXOR(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons)
{
	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
		return false;

	bool	ok		= true;

	try
	{
		((Bool_Engine*) m_pBooleanEngine)->Activate();
		::SetPolygonA_3D( (Bool_Engine*) m_pBooleanEngine, polygon );
		::SetPolygonB_3D( (Bool_Engine*) m_pBooleanEngine, m_clipPoly );
		((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_EXOR );
		::GetResult_3D( (Bool_Engine*) m_pBooleanEngine, polygon, resultPolygons );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

bool VWPolygon3DOperation::BooleanPoly_SUB_Clip(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons, bool forceOperation/*=false*/)
{
	bool						isOK				= true;
	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
	{
		VWFC_ASSERT( false );						// bad input !
		isOK										= false;
	}
	resultPolygons.clear();

	if ( isOK )										// good input polygons.
	{
		VWPolygon2D				planarPoly;
		polygon.GetPlanarPolygon( planarPoly );		// get planar polygon.

		// XXX Bobi:
		// instead of 'VWPolygon3DOperation::AreOverlapping' use the following function which is faster.
		// check if the polygon operation is necessary.
		// if there are cases missed by the following function, try using 'ArePolygonsIntersecting'.
		bool					performOperation	= false;

		bool					noCommonArea;
		if ( forceOperation ||						// force the boolean operation.
			 VWPolygon2D::ArePolygonsIntersecting_Fast( m_clipPoly, planarPoly, noCommonArea ) )
		{
			performOperation						= true;
		}
		else
		{
			// 3 possible cases here:
			// - planar polygon of 'polygon' is inside the 'm_clipPoly'.
			// - 'm_clipPoly' is inside the planar polygon of the 'polygon' (perform the boolean operation in this case !).
			// - no common areas.

			if ( ! noCommonArea )								// might have common area. check!
			{
				// as it is still not sure that 'planarPoly' and 'm_clipPoly' overlap (they might not have common area), ...
				// ... make this additional check here.
				noCommonArea						= true;

				size_t					polyPtCnt	= planarPoly.GetVertexCount();
				size_t					clipPtCnt	= m_clipPoly.GetVertexCount();
				if ( polyPtCnt > 2 && clipPtCnt > 2 )			// both polygons are correct.
				{
					size_t				maxPtCnt	= ( polyPtCnt > clipPtCnt ) ? polyPtCnt : clipPtCnt;
					for ( size_t i = 0 ; i < maxPtCnt ; ++ i )
					{
						if ( i < polyPtCnt )
						{
							const VWPoint2D&	vp	= planarPoly.GetVertexAt( i );
							if ( m_clipPoly.IsPtInPoly2D( vp.x, vp.y, VWPoint2D::sEpsilon ) )	// 'planarPoly' is inside the 'm_clipPoly'.
							{
								noCommonArea		= false;
								break;
							}
						}

						if ( i < clipPtCnt )
						{
							const VWPoint2D&	vc	= m_clipPoly.GetVertexAt( i );
							if ( planarPoly.IsPtInPoly2D( vc.x, vc.y, VWPoint2D::sEpsilon ) )	// 'm_clipPoly' is inside the 'planarPoly'.
							{
								noCommonArea		= false;
								performOperation	= true;		// perform the boolean operation in this case !
								break;
							}
						}
					}
				}
			}

			if ( noCommonArea )									// do not have common area for sure (do not overlap).
			{
				resultPolygons.push_back( polygon );			// the result is 'polygon' itself !
			}
		}

		if ( performOperation )						// the boolean operation must be performed.
		{
			VWPolygon2D			polyB( m_clipPoly );
			VWPolygon3D			polyA( polygon );

			// get clipper center.
			const VWPoint2D&	center				= polyB.GetCenter();
			// transformation matrix.
			VWTransformMatrix	mat;

			// check whether center coordinates are too big (could lead to incorrect result).
			bool				isTooFar			= ( center.Magnitude() > KBOOL_MAX_COORD_VAL );
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
				::SetPolygonA_3D( (Bool_Engine*) m_pBooleanEngine, polyA );
				::SetPolygonB_3D( (Bool_Engine*) m_pBooleanEngine, polyB );
				((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_A_SUB_B );
				::GetResult_3D( (Bool_Engine*) m_pBooleanEngine, polyA, resultPolygons );
			}
			catch (Bool_Engine_Error& /*error*/)
			{
				isOK								= false;
			}

			if ( isOK && isTooFar )					// translate results (if needed).
			{
				size_t				len				= resultPolygons.size();
				for ( size_t i = 0 ; i < len ; ++ i )
				{
					VWPolygon3D&	poly			= resultPolygons[ i ];
					poly.InversePointsTransform( mat );
				}
			}
		}
	}

	// result.
	return	( isOK );
}

bool VWPolygon3DOperation::BooleanClip_SUB_Poly(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons)
{
	if ( polygon.IsEmpty() || m_clipPoly.IsEmpty() )
		return false;

	bool	ok		= true;

	try
	{
		((Bool_Engine*) m_pBooleanEngine)->Activate();
		::SetPolygonA_3D( (Bool_Engine*) m_pBooleanEngine, polygon );
		::SetPolygonB_3D( (Bool_Engine*) m_pBooleanEngine, m_clipPoly );
		((Bool_Engine*) m_pBooleanEngine)->Do_Operation( BOOL_B_SUB_A );
		::GetResult_3D( (Bool_Engine*) m_pBooleanEngine, polygon, resultPolygons );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

// clip the 'poly' using 'clipper' polygon as clipping object
bool VWPolygon3DOperation::ClipToPoly(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly, const VWPolygon2D& inClipper)
{
	VWPolygon3DOperation	operation( inClipper );
	return	operation.BooleanAND( inPoly, resultPolygons );
}

// clip the 'poly' using 'clipper' polygon as clipping object
bool VWPolygon3DOperation::ClipToPoly(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly, const VWPolygon2D& inClipper, bool& outPolysOverlap, bool forceOperation/* = false*/)
{
	VWPolygon3DOperation	operation( inClipper );
	return	operation.BooleanAND( inPoly, resultPolygons, outPolysOverlap, forceOperation );
}

bool VWPolygon3DOperation::CombinePolygons(VWPolygon3D&/*out*/ resultPolygon, const VWPolygon3D& inPoly1, const VWPolygon2D& inPoly2)
{
	if ( inPoly1.IsEmpty() || inPoly2.IsEmpty() )
		return false;

	bool	ok		= true;

	try
	{
		Bool_Engine		engine;
		::ArmBoolEng_3D( & engine );
		::SetPolygonA_3D( &engine, inPoly1 );
		::SetPolygonB_3D( &engine, inPoly2 );

		// combine
		engine.Do_Operation( BOOL_OR );

		::GetResult_3D( & engine, inPoly1, resultPolygon );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

bool VWPolygon3DOperation::SubtractPolygons(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly1, const VWPolygon2D& inPoly2)
{
	if ( inPoly1.IsEmpty() || inPoly2.IsEmpty() )
		return false;

	bool	ok		= true;

	try
	{
		Bool_Engine		engine;
		::ArmBoolEng_3D( & engine );
		::SetPolygonA_3D( &engine, inPoly1 );
		::SetPolygonB_3D( &engine, inPoly2 );

		// combine
		engine.Do_Operation( BOOL_A_SUB_B );

		::GetResult_3D( & engine, inPoly1, resultPolygons );
	}
	catch(Bool_Engine_Error& /*error*/)
	{
		ok = false;
	}

	return ok;
}

// cut the specified polygon by cutter
// the result are those parts of the polygon that lie inside the cutter
bool VWPolygon3DOperation::CutPolygon(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly, const VWPolygon2D& inCutter)
{
	VWPolygon3DOperation	operation( inCutter );
	return operation.CutPolygon( inPoly, resultPolygons );
}

// cut the specified polygon by cutter
// the result are those parts of the polygon that lie inside the cutter
bool VWPolygon3DOperation::CutPolygon(const VWPolygon3D& inPoly, TSTLPolygons3DArray&/*out*/ resultPolygons)
{
	// create vertices list from poly.
	SVertex*				pFirstVert	= NULL;
	SVertex*				pLastVert	= NULL;
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

// split the specified polygon by splitter.
// the result are all split parts of the polygon (their union will be the polygon itself).
bool VWPolygon3DOperation::SplitByPoly(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly, const VWPolygon2D& inSplitter)
{
	resultPolygons.clear();

	bool					isOK				= true;

	VWPolygon2D				inPolyPlanar;
	inPoly.GetPlanarPolygon( inPolyPlanar );	// get planar of 'inPoly'.

	// XXX Bobi:
	// instead of 'VWPolygon3DOperation::AreOverlapping' use the following function which is faster.
	// check if the polygon operation is necessary.
	// if there are cases missed by the following function, try using 'ArePolygonsIntersecting'.
	bool					performOperation	= false;

	bool					noCommonArea;
	if ( VWPolygon2D::ArePolygonsIntersecting_Fast( inSplitter, inPolyPlanar, noCommonArea ) )
	{
		performOperation						= true;
	}
	else
	{
		// 3 possible cases here:
		// - planar polygon of 'inPoly' is inside the 'inSplitter'.
		// - 'inSplitter' is inside the planar polygon of the 'inPoly' (this 3D polygon operation is not appropriate in this case !).
		// - no common areas.

		if ( ! noCommonArea )								// might have common area. check!
		{
			// as it is still not sure that 'inPolyPlanar' and 'inSplitter' overlap (they might not have common area), ...
			// ... make this additional check here.
			noCommonArea						= true;

			size_t					polyPtCnt	= inPolyPlanar.GetVertexCount();
			size_t					clipPtCnt	= inSplitter.GetVertexCount();
			if ( polyPtCnt > 2 && clipPtCnt > 2 )			// both polygons are correct.
			{
				size_t				maxPtCnt	= ( polyPtCnt > clipPtCnt ) ? polyPtCnt : clipPtCnt;
				for ( size_t i = 0 ; i < maxPtCnt ; ++ i )
				{
					if ( i < polyPtCnt )
					{
						const VWPoint2D&	vp	= inPolyPlanar.GetVertexAt( i );
						if ( inSplitter.IsPtInPoly2D( vp.x, vp.y, VWPoint2D::sEpsilon ) )	// 'inPolyPlanar' is inside the 'inSplitter'.
						{
							noCommonArea		= false;
							resultPolygons.push_back( inPoly );								// as result of BooleanAND !
							break;
						}
					}

					if ( i < clipPtCnt )
					{
						const VWPoint2D&	vc	= inSplitter.GetVertexAt( i );
						if ( inPolyPlanar.IsPtInPoly2D( vc.x, vc.y, VWPoint2D::sEpsilon ) )	// 'inSplitter' is inside the 'inPolyPlanar'.
						{
							noCommonArea		= false;
							performOperation	= true;		// perform the boolean operation in this case !
							break;
						}
					}
				}
			}
		}

		if ( noCommonArea )									// do not have common area for sure (do not overlap).
		{
			resultPolygons.push_back( inPoly );				// the result is 'inPoly' itself (as result of BooleanPoly_SUB_Clip) !
		}
	}

	if ( performOperation )						// the boolean operation must be performed.
	{
		// polygon operation.
		VWPolygon3DOperation	operation( inSplitter );

		// get the parts that lie within the splitter.
		TSTLPolygons3DArray		arrPolys;
		if ( operation.BooleanAND( inPoly, arrPolys, true ) )			// force the boolean operation.
		{
			size_t				len				= arrPolys.size();
			for ( size_t i = 0 ; i < len ; ++ i )
			{
				resultPolygons.push_back( arrPolys[ i ] );
			}
		}
		else
		{
			isOK								= false;				// boolean operation failed.
		}

		// get the parts that lie outside the splitter.
		arrPolys.clear();
		if ( operation.BooleanPoly_SUB_Clip( inPoly, arrPolys, true ) )	// force the boolean operation.
		{
			size_t				len				= arrPolys.size();
			for ( size_t i = 0 ; i < len ; ++ i )
			{
				resultPolygons.push_back( arrPolys[ i ] );
			}
		}
		else
		{
			isOK								= false;				// boolean operation failed.
		}
	}

	// result.
	return	( isOK );
}

// collects inner parts (inside the cutter).
void VWPolygon3DOperation::WalkValidVertexsForCut(SVertex* pFirstVertex)
{
	SVertex*		pThisVert		=	pFirstVertex;
	do
	{
		// search for the beginning of an inner segment (inside cutter).
		VWPolygonOperation::SearchStartOfInnerSegment( pFirstVertex, pThisVert );
		if ( pThisVert == NULL )
		{
			break;
		}

		// add inner segment.
		SVertex*	pStartVert		=	pThisVert;

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

		this->FinishValidVerticesForPoly( pStartVert == pThisVert );
	}
	while( true );
}

// collects the outer parts (outside the clipper).
void VWPolygon3DOperation::WalkValidVertexsForClip(SVertex* pFirstVertex)
{
	SVertex*		pThisVert		= pFirstVertex;
	do
	{
		SVertex*	pStartVert		= pThisVert;
		if ( pStartVert == NULL )
		{
			break;
		}

		// add outer segment.
		while ( pStartVert && ( ! pStartVert->bInCutter ) )	// vertex is outside or on the cutter.
		{
			this->AddValidVertex( pStartVert );

			// current point is on cutter => the next point is from other inner segment.
			bool	isGoingIn		= ( ( pStartVert != pThisVert ) &&	// not just started (first added) ...
										( pStartVert->bOnCutter ) );	// ... and is on cutter.

			// prevent repeated adding.
			pStartVert->bInCutter	= true;					// mark as inner.

			if ( isGoingIn )								// next point is from other segment. stop!
			{
				break;
			}

			// next.
			pStartVert				= pStartVert->pNextVertex;
		}

		// collect the polygon.
		this->FinishValidVerticesForPoly( pStartVert == pThisVert );

		// searches for the ending of an inner segment (outside clipper).
		VWPolygonOperation::SearchFinishOfInnerSegment( pStartVert, pThisVert );
	}
	while( true );
}

void VWPolygon3DOperation::AddValidVertex(SVertex* pVertex)
{
	m_cutResutPoly.AddVertex( pVertex->pt.x, pVertex->pt.y, pVertex->z );
}

void VWPolygon3DOperation::FinishValidVerticesForPoly(bool bClosed)
{
	if ( m_pSTLCutResultArray ) {
		if ( m_cutResutPoly.GetVertexCount() >= 2 )  {
			m_cutResutPoly.SetClosed( bClosed );
			m_pSTLCutResultArray->push_back( m_cutResutPoly );
		}
	}
	m_cutResutPoly.ClearVertices();
}

/*static*/ bool VWPolygon3DOperation::AreOverlapping(const VWPolygon2D& a, const VWPolygon3D& b)
{
	const double kEpsilon	= 0.0001;

	bool		bClip		= false;

	size_t		vertCnt2	= b.GetVertexCount();

	size_t		vertCnt1	= a.GetVertexCount();
	for(size_t i=0; i<vertCnt1; i++) {
		const VWPoint2D& v1	= a.GetVertexAt( i, false );
		const VWPoint2D& v2	= a.GetVertexAt( i + 1, true );

		for(size_t j=0; j<vertCnt2; j++) {
			const VWPoint3D& p1	= b.GetVertexAt( j, false );
			const VWPoint3D& p2	= b.GetVertexAt( j + 1, true );

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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bool engine code
static void ArmBoolEng_3D(Bool_Engine* pBoolEngine)
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

static void SetPolygonA_3D(Bool_Engine* pBoolEngine, const VWPolygon3D& poly)
{
    if ( pBoolEngine->StartPolygonAdd( GROUP_A ) )
    {
		size_t		len	= poly.GetVertexCount();
		for(size_t i=0; i<len; i++) {
			const VWPoint3D& pt	= poly.GetVertexAt( i );
			pBoolEngine->AddPoint( pt.x, pt.y );
		}
    }
    pBoolEngine->EndPolygonAdd(); 
}

static void SetPolygonB_3D(Bool_Engine* pBoolEngine, const VWPolygon2D& poly)
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

static void GetResult_3D(Bool_Engine* pBoolEngine, const VWPolygon3D& refPoly, TSTLPolygons3DArray& out)
{
	out.clear();
    // foreach resultant polygon in the booleng ...
    while ( pBoolEngine->StartPolygonGet() )
    {
		VWPolygon3D	resultPoly;
        // foreach point in the polygon
        while ( pBoolEngine->PolygonHasMorePoints() )
        {
			VWPoint3D		pt;
			pt.x					= pBoolEngine->GetPolygonXPoint();
			pt.y					= pBoolEngine->GetPolygonYPoint();
			pt.z					= refPoly.GetVerticalDistance( pt );
			resultPoly.AddVertex( pt );
        }
        pBoolEngine->EndPolygonGet();
		out.push_back( resultPoly );
    }
}

static void GetResult_3D(Bool_Engine* pBoolEngine, const VWPolygon3D& refPoly, VWPolygon3D& out)
{
	out.ClearVertices();
    // foreach resultant polygon in the booleng ...
    if ( pBoolEngine->StartPolygonGet() )
    {
        // foreach point in the polygon
        while ( pBoolEngine->PolygonHasMorePoints() )
        {
			VWPoint3D		pt;
			pt.x					= pBoolEngine->GetPolygonXPoint();
			pt.y					= pBoolEngine->GetPolygonYPoint();
			pt.z					= refPoly.GetVerticalDistance( pt );
			out.AddVertex( pt );
        }
        pBoolEngine->EndPolygonGet();
    }
}


