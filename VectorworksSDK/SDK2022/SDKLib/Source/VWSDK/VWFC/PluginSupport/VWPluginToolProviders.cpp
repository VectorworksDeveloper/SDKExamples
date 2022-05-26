//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC//PluginSupport/VWPluginToolProviders.h"

using namespace VWFC::Math;
using namespace VWFC::PluginSupport;

// ------------------------------------------------------------------------------------------------------------------
CDrawProvider::CDrawProvider()
{
	fbPoly3DRender	= false;
}

void CDrawProvider::DrawDefaultRect() const
{
	::GS_BoxToolDraw( gCBP );
}

void CDrawProvider::DrawDefault2D() const
{
	::GS_Default2DToolDraw( gCBP );
}

void CDrawProvider::DrawDefault3D() const
{
	::GS_Default3DToolDraw( gCBP );
}

void CDrawProvider::DrawLine2D(const VWLine2D& line) const
{
	VWPoint2D a, b;
	line.GetLine( a, b );
	::GS_DrawCoordLine( gCBP, a, b );
}

void CDrawProvider::DrawLine3D(const VWLine3D& line) const
{
	VWPoint3D a, b;
	line.GetLine( a, b );
	::GS_DrawCoordLine3D( gCBP, a, b );
}

void CDrawProvider::DrawRect(const VWRectangle2D& rect) const
{
	WorldRect rc( rect.GetLeft(), rect.GetTop(), rect.GetRight(), rect.GetBottom() );
	::GS_DrawCoordRect( gCBP, rc );
}

void CDrawProvider::DrawArc(const VWArc2D& arc) const
{
	VWPoint2D cen = arc.GetCenterPt();
	double r = arc.GetRadius();
	WorldRect rc( cen.x-r, cen.y-r, cen.x+r, cen.y+r );
	::GS_DrawCoordArcN( gCBP, rc, arc.GetStartAngle(), arc.GetSweepAngle() );
}

void CDrawProvider::DrawEllipse(const VWRectangle2D& rect) const
{
	WorldRect rc( rect.GetLeft(), rect.GetTop(), rect.GetRight(), rect.GetBottom() );
	::GS_DrawCoordEllipse( gCBP, rc );
}

void CDrawProvider::DrawPolyBegin()
{
	farrPoints.clear();
}

void CDrawProvider::DrawPoly_AddCornerVertex(const VWPoint2D& pt)
{
	SPolyVertex		vertex;
	vertex.fType			= vtCorner;
	vertex.fTypeOriginal	= vtCorner;
	vertex.fPt				= pt;
	vertex.fControlPt		= pt;
	vertex.fdRadius			= 0;
	farrPoints.push_back( vertex );
}

void CDrawProvider::DrawPoly_AddBezierVertex(const VWPoint2D& pt)
{
	SPolyVertex		vertex;
	vertex.fType			= vtBezier;
	vertex.fTypeOriginal	= vtBezier;
	vertex.fPt				= pt;
	vertex.fControlPt		= pt;
	vertex.fdRadius			= 0;
	farrPoints.push_back( vertex );
}

void CDrawProvider::DrawPoly_AddCubicVertex(const VWPoint2D& pt)
{
	SPolyVertex		vertex;
	vertex.fType			= vtCubic;
	vertex.fTypeOriginal	= vtCubic;
	vertex.fPt				= pt;
	vertex.fControlPt		= pt;
	vertex.fdRadius			= 0;
	farrPoints.push_back( vertex );
}

void CDrawProvider::DrawPoly_AddArcVertex(const VWPoint2D& pt, double dRadius)
{
	SPolyVertex		vertex;
	vertex.fType			= vtArc;
	vertex.fTypeOriginal	= vtArc;
	vertex.fPt				= pt;
	vertex.fControlPt		= pt;
	vertex.fdRadius			= dRadius;
	farrPoints.push_back( vertex );
}

void CDrawProvider::DrawPolyEnd()
{
	fbPoly3DRender		= false;

	size_t	vertexCnt	= farrPoints.size();
	if ( vertexCnt > 1 ) {
		// at the beginning end points should be corners
		farrPoints[ vertexCnt - 1 ].fType	= vtCorner;
		farrPoints[ 0 ].fType				= vtCorner;

		// render polyline
		this->RenderPolyline( farrPoints );
	}

	// clear up the poly points
	// cleaning for the next calls
	//debug
	//farrPoints.clear();
}

void CDrawProvider::DrawPolyEnd(const VWTransformMatrix& matrix)
{
	fbPoly3DRender		= true;
	fPoly3DMatrix		= matrix;

	size_t	vertexCnt	= farrPoints.size();
	if ( vertexCnt > 1 ) {
		// at the beginning end points should be corners
		farrPoints[ vertexCnt - 1 ].fType	= vtCorner;
		farrPoints[ 0 ].fType				= vtCorner;

		// render polyline
		this->RenderPolyline( farrPoints );
	}
}

void CDrawProvider::PolyRenderDrawLine(const VWLine2D& line) const
{
	if ( ! fbPoly3DRender ) {
		this->DrawLine2D( line );
	}
	else {
		VWPoint3D	a	= line.GetStart();
		VWPoint3D	b	= line.GetEnd();

		a				= fPoly3DMatrix.PointTransform( a );
		b				= fPoly3DMatrix.PointTransform( b );

		this->DrawLine3D( VWLine3D( a, b ) );
	}
}

void CDrawProvider::DrawObject(MCObjectHandle hObj, bool bDoSelect) const
{
	::GS_DrawObject( gCBP, hObj, bDoSelect );
}

void CDrawProvider::DrawNurbsObject(MCObjectHandle hNurbsObj) const
{
	::GS_DrawNurbsObject( gCBP, hNurbsObj );
}

void CDrawProvider::DrawDataDisplayBar(bool bDrawFramesFirst) const
{
	::GS_DrawDataDisplayBar( gCBP, bDrawFramesFirst );
}

void CDrawProvider::SetPenSize(short penSize) const
{
	InternalIndex classID = ::GS_GetDefaultClass( gCBP );
	if ( penSize == 0 ) {
		penSize	 = 1;
		if ( ::GS_GetClUseGraphic( gCBP, classID ) )
			penSize = ::GS_GetClLineWeight( gCBP, classID );
		else 
			penSize = ::GS_GetDefaultLineWeight( gCBP );
	}
	if ( penSize > 1 )
		::GS_SetProgramVariable( gCBP, varToolPenSize, (void*) &penSize );
}

void CDrawProvider::SetPenPattern(short penPatIndex) const
{
	::GS_SetProgramVariable( gCBP, varToolPenPattern, (void*) &penPatIndex );
}

void CDrawProvider::RenderPolyline(TPointsArray& arrVertices)
{
	size_t ptsCnt	= arrVertices.size();
	ASSERTN( kVStanev, ptsCnt > 1 );
	if ( ptsCnt <= 1 )
		return;

	// check if it is a closed polyline
	bool	bClosed	= false;
	if ( ptsCnt > 2 && arrVertices[ 0 ].fPt == arrVertices[ ptsCnt - 1 ].fPt ) {

		// restore original points types of the changed ones
		farrPoints[ ptsCnt - 1 ].fType	= farrPoints[ ptsCnt - 1 ].fTypeOriginal;
		farrPoints[ 0 ].fType			= farrPoints[ 0 ].fTypeOriginal;

		// prepare beginning and end vertices
		SPolyVertex* pFrstVert	= & arrVertices[ 0 ];
		SPolyVertex* pLastVert	= & arrVertices[ ptsCnt - 1 ];

		if ( pLastVert->fType == vtCubic || pLastVert->fType == vtBezier ) {

			arrVertices.erase( arrVertices.begin() );
			ptsCnt --;
		}
		else if ( pLastVert->fType == vtArc ) {

			if ( pFrstVert->fType == vtArc ) {
				arrVertices.erase( arrVertices.begin() );
				ptsCnt --;
			}
			else {
				pFrstVert->fType	= vtArc;
			}
		}
		else {
			pFrstVert->fType	= vtCorner;
		}
		
		bClosed		= true;
	}

	// begin the polyline
	fCurrPolyPt		= arrVertices[ 0 ].fPt;

	// prepare cubic vertices
	this->CalculatePolyline( arrVertices );
	this->SwapControlPts( arrVertices );
	
	size_t			lastIndex;
	if ( bClosed && arrVertices[ 0 ].fPt == arrVertices[ ptsCnt - 1 ].fPt)	lastIndex	= ptsCnt - 2;
	else																	lastIndex	= ptsCnt - 1;

	SPolyVertex		lastVert	= arrVertices[ lastIndex ];
	
	Sint32 c = 1;
	SPolyVertex		thisVert	= arrVertices[ c - 1 ];

	SPolyVertex	nextVert;
	if ( c == ptsCnt )	nextVert	= arrVertices[ 0 ];
	else				nextVert	= arrVertices[ c ];

	// if the polyline is closed
	if ( bClosed ) {

		if ( thisVert.fType != vtCorner ) {

			// create the first poly segment
			fCurrPolyPt		= ( thisVert.fPt + lastVert.fPt ) * 0.5;
			this->DrawPolyVert( lastVert, thisVert, nextVert );
		}
		else {
			lastVert.fPt	= thisVert.fPt;
			fCurrPolyPt		= lastVert.fPt;
		}
	}
	else {
		lastVert.fPt	= thisVert.fPt;
		fCurrPolyPt		= lastVert.fPt;
	}
		
	c ++ ;
	while ( c < (Sint32)ptsCnt ) { 
		lastVert = thisVert;
		thisVert = nextVert;
		nextVert = arrVertices[ c ] ;
		
		this->DrawPolyVert( lastVert, thisVert, nextVert);

		c ++ ;
	}

	lastVert = thisVert;
	thisVert = nextVert;
	nextVert = arrVertices[ 0 ];
	this->DrawPolyVert( lastVert, thisVert, nextVert );
			
	this->SwapControlPts( arrVertices );
}

void CDrawProvider::DisplaySplineSubSection(const VWPoint2D &v1, const VWPoint2D &v2, const VWPoint2D &v3, short level )
{
	VWPoint2D		v12, v22, v23;
	VWPoint2D		v1A, v2A, v3A, v1B, v2B, v3B;

	VWLine2D		line;

	if ( level > 1 ) {	// now if it is called with level > 1, it processes

		v12 = ( v1 + v2 )	* 0.5;		// 2 levels, to reduce the number of recursive
		v23 = ( v2 + v3 )	* 0.5;		// function calls, which makes it faster; also
		v22 = ( v12 + v23 ) * 0.5;		// it won't make a recursive call with level = 0,
		level -- ;					// but will do the TDFLineTo [BF 11/7/02]
		
		v1A = v1;
		v2A = v12;
		v3A = v22;
		v1B = v22;
		v2B = v23;
		v3B = v3;
		
		v12 = ( v1A + v2A ) * 0.5;
		v23 = ( v2A + v3A ) * 0.5;
		v22 = ( v12 + v23 ) * 0.5;
		level -- ;

		if ( level == 0 ) {

			line.SetLine( fCurrPolyPt, v22 );
			this->PolyRenderDrawLine( line );
			fCurrPolyPt	= v22;

			line.SetLine( fCurrPolyPt, v3A );
			this->PolyRenderDrawLine( line );
			fCurrPolyPt	= v3A;
		}
		else {
			// recursion
			this->DisplaySplineSubSection( v1A, v12, v22, level );
			this->DisplaySplineSubSection( v22, v23, v3A, level );
		}
		
		v12 = ( v1B + v2B ) * 0.5;
		v23 = ( v2B + v3B ) * 0.5;
		v22 = ( v12 + v23 ) * 0.5;

		if ( level == 0 ) {

			line.SetLine( fCurrPolyPt, v22 );
			this->PolyRenderDrawLine( line );
			fCurrPolyPt	= v22;

			line.SetLine( fCurrPolyPt, v3B );
			this->PolyRenderDrawLine( line );
			fCurrPolyPt	= v3B;
		}
		else {
			// recursion
			this->DisplaySplineSubSection( v1B, v12, v22, level );
			this->DisplaySplineSubSection( v22, v23, v3B, level );
		}
	}
	else if ( level == 1 ) {
		v12 = ( v1 + v2 ) * 0.5;
		v23 = ( v2 + v3 ) * 0.5;
		v22 = ( v12 + v23 ) * 0.5;

		line.SetLine( fCurrPolyPt, v22 );
		this->PolyRenderDrawLine( line );
		fCurrPolyPt	= v22;

		line.SetLine( fCurrPolyPt, v3 );
		this->PolyRenderDrawLine( line );
		fCurrPolyPt	= v3;
	}
	else {
		line.SetLine( fCurrPolyPt, v3 );
		this->PolyRenderDrawLine( line );
		fCurrPolyPt	= v3;
	}
}

void CDrawProvider::CalculatePolyline(TPointsArray& arrVertices)
// This function seems to iterate through the polyline looking for
// cubic control points.  If it does not find any it exits.  If
// some are found they are processed.
//
// According to SteveJ:
// This is computing the controlPt member of the PolylineVert structure for the cubic verts.
// The controlPt is a cached value, which, one would think, could be updated at edit/reset time.
// We are always doing this in Render.
///////////////////////////////////////////////////////////////////////////////
{
	size_t ptsCnt	= arrVertices.size();
	if ( ptsCnt > 0 ) {
		//Set the controlpt to p for cubic vertices
		bool	bFound = false;
		for (size_t k = 1 ; k <= ptsCnt ; k ++ ) {

			SPolyVertex*	vertex	= & arrVertices[ k - 1 ];
			if ( vertex->fType == vtCubic ) {

				vertex->fControlPt	= vertex->fPt;
				bFound				= true;
			}
		}
		//don't bother to itterate if no cubics are found
		if ( ! bFound ) return;

		size_t		prevIndex	= ptsCnt - 1;
		size_t		i			= ptsCnt;

		VWPoint2D	vPrev;
		VWPoint2D	vNext;

		// here we set 5 iterations
		for ( size_t j = 1 ; j <= 5 ; j ++ ) {

			for ( size_t nextIndex = 1 ; nextIndex <= ptsCnt ; nextIndex ++ ) {

				SPolyVertex*	currVertex	= & arrVertices[ i - 1 ];
				if ( currVertex->fType == vtCubic ) {

					SPolyVertex	prevVertex	= arrVertices[ prevIndex - 1 ];
					switch ( prevVertex.fType ) {
						case vtCubic: {
							vPrev = prevVertex.fControlPt;
							break;
						}
						case vtCorner: {
							VWPoint2D	tempPt	= prevVertex.fPt	- arrVertices[ i - 1 ].fControlPt;
							vPrev				= tempPt + prevVertex.fPt;
							break;
						}
						default:	vPrev = prevVertex.fPt;
					}

					SPolyVertex		nextVertex	= arrVertices[ nextIndex - 1 ];

					switch ( nextVertex.fType ) {
						case vtCubic: {
							vNext = nextVertex.fControlPt;
							break;
						}
						case vtCorner: {
							VWPoint2D	tempPt	= nextVertex.fPt - arrVertices[ i - 1 ].fControlPt;
							vNext				= tempPt + nextVertex.fPt;
							break;
						}
						default:	vNext = nextVertex.fPt;
					}

					//withthird order
					double	divResultX = ( currVertex->fPt.x - ( vPrev.x + vNext.x ) / 2.0 ) / 3.0;
					//third order
					double	divResultY = ( currVertex->fPt.y - ( vPrev.y + vNext.y ) / 2.0 ) / 3.0;

					//Update the polyline
					currVertex->fControlPt.x = currVertex->fPt.x + divResultX;
					currVertex->fControlPt.y = currVertex->fPt.y + divResultY;
				}

				prevIndex	= i;
				i			= nextIndex;

			} // end for nextIndex loop
		} // end for j loop
	}
}

void CDrawProvider::SwapControlPts(TPointsArray& arrVertices)
{
	size_t ptsCnt	= arrVertices.size();
	for (size_t i = 1 ; i <= ptsCnt ; i++ ) {

		SPolyVertex*	vertex = & arrVertices[ i - 1 ];
		if ( vertex->fType == vtCubic ) {
			VWPoint2D	tmp		= vertex->fControlPt;
			vertex->fControlPt	= vertex->fPt;
			vertex->fPt			= tmp;
		}
	}
}

void CDrawProvider::DrawPolyVert(const SPolyVertex& lastVert, const SPolyVertex& thisVert, const SPolyVertex& nextVert )
{
	switch ( thisVert.fType ) {
		case vtCorner: {

				VWLine2D	line( fCurrPolyPt, thisVert.fPt );
				this->PolyRenderDrawLine( line );
				// current polygon point
				fCurrPolyPt	= thisVert.fPt;
			}
			break;
		case vtCubic:
		case vtBezier: {
				VWPoint2D p0, p1, p2;

				if ( lastVert.fType	== vtCorner )	p0	= lastVert.fPt;
				else								p0	= ( thisVert.fPt + lastVert.fPt ) * 0.5;

				p1 = thisVert.fPt;

				if ( nextVert.fType == vtCorner )	p2	= nextVert.fPt;
				else								p2	= ( thisVert.fPt + nextVert.fPt ) * 0.5;
				
				short startLevel = 8;	// max recursion level	kDefaultMaxRecursionLevel

				this->DisplaySplineSubSection( p0, p1, p2, startLevel );	
			}
			break;
		case vtArc: {
				VWPoint2D thisPt, lastPt, nextPt;

				if ( lastVert.fType == vtCorner )	lastPt	= lastVert.fPt;
				else								lastPt	= ( lastVert.fPt + thisVert.fPt ) * 0.5;

				// draw a line
				VWLine2D	line( fCurrPolyPt, lastPt );
				this->PolyRenderDrawLine( line );
				fCurrPolyPt	= lastPt;

				if ( nextVert.fType == vtCorner)	nextPt = nextVert.fPt;
				else								nextPt = ( nextVert.fPt + thisVert.fPt ) * 0.5;

				thisPt = thisVert.fPt;

				// draw arc
				this->DisplayArc( lastPt, thisPt, nextPt, thisVert.fdRadius );
			}
			break;
	}
}

void CDrawProvider::DisplayArc(const VWPoint2D& lastPt, const VWPoint2D& thisPt, const VWPoint2D& nextPt, double radius)
{
	VWPoint2D	lastCam;
	VWPoint2D	thisCam;
	VWPoint2D	center;
	double		myStart;
	double		myArc;

	// prepare to draw the arc
	if ( this->CalcChamfer( lastPt, thisPt, nextPt, lastCam, thisCam, center, radius, myStart, myArc ) ) {
		this->DisplayArc( lastPt, thisPt, nextPt, radius, lastCam, thisCam, center, myStart, myArc );
	}
}

bool CDrawProvider::CalcChamfer(	const VWPoint2D& pt1, const VWPoint2D& int0Value, const VWPoint2D& pt4,
									VWPoint2D& lastCam, VWPoint2D& thisCam, VWPoint2D& center, double& radius,
									double &lastAngle, double &thisAngle)
{
	VWPoint2D	int0 = int0Value;
	double		shortLen;
	VWPoint2D	thisPerp, lastPerp, lastVec, thisVec;
	double		lastLen, thisLen;
	bool 		intersect, parallel;
	double		signedRadius;

	// find intersection
	this->InterLoc( pt1, int0, int0, pt4, intersect, parallel, int0 );

	if ( parallel ) {
		return false;
	}
	else {
		thisLen		= int0.DistanceTo( pt4 );
		lastLen		= int0.DistanceTo( pt1 );
		if ( thisLen != 0 )		thisVec = ( pt4 - int0 ) / thisLen;	// normalize
		if ( lastLen != 0 )		lastVec = ( pt1 - int0 ) / lastLen;	// normalize

		//if the radius is preset by user and the segments are Sint32 enough then
		// use the preset radius
		// If the lengths are within a certain percentage of eachother, don't bother with the Cams.
		if ( ( thisLen != 0 ) && ( Abs( ( lastLen / thisLen ) - 1 ) < 0.001 ) ) {

			lastCam = pt1;
			thisCam = pt4;
		}
		else if ( lastLen < thisLen ) {
			lastCam = pt1;
			thisCam = int0 + thisVec * lastLen;
		}
		else {
			thisCam = pt4;
			lastCam = int0 + lastVec * thisLen;
		}

		//arc part
		thisPerp				= thisCam;
		VWPoint2D	perpVec( thisVec.y, -thisVec.x );
		thisPerp				 -=	perpVec;
		lastPerp				= lastCam;
		perpVec.SetPoint( lastVec.y, -lastVec.x );
		lastPerp				-= perpVec;
		this->InterLoc( lastCam, lastPerp, thisCam, thisPerp, intersect, parallel, center );

		if ( parallel )
			return false;

		shortLen	= Min( ( center - thisCam ).Magnitude(), ( center - lastCam ).Magnitude() );

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

		if ( parallel ) {
			return false;
		}
		else {
			lastAngle	= MathUtils::FixedAngle( center, lastCam );
			thisAngle	= MathUtils::FixedAngle( center, thisCam );

			thisAngle	-= lastAngle;

            if ( thisAngle == 0 || std::abs( (int)thisAngle ) == 360 ) {
				return false;
			}
			else {
				lastAngle	= 90.0 - lastAngle;
				thisAngle	= -thisAngle;

				if (thisAngle > 180.0) thisAngle -= 360.0;
				else if (-thisAngle > 180.0) thisAngle += 360.0;

				if (lastAngle < 0)
					do { lastAngle += 360.0; } while (lastAngle <= 0);
					
				if (lastAngle > 360.0)
					do { lastAngle -= 360.0; } while (lastAngle >= 360.0);
			}
		}

		return true;
	}
}

void CDrawProvider::InterLoc(	const VWPoint2D& a1, const VWPoint2D& a2, const VWPoint2D& b1, const VWPoint2D& b2,
								bool& intersect, bool& parallel, VWPoint2D& int0)
//This intersection code is based on a parametric definition of a line: p(a1, a2) = a1 + (1-t)(a2-a1) & p(b1, b2) = b1 + (1 -s)(b2 - b1)
// t and s are includede [0,1]
// parameters: 
// Input       a1: start point of the first line
//			   a2: end point of the first line
// 			   b1: start point of the second line
//			   b2: end point of the second line
// Output      parallel: true if the two lines are parallel
//			   intersect: true if the intersection point is inside of the two lines
//			   int0: the intersection point
// Author : Abdel 11/21/2005
{

	// this is a determinant of the (t,s) linear equation. Geometrically we can notice that it is a a cross product of vectors
	// a2 - a1 and b2 - b1, if it is nil then the lines are parallel.
	double part1 = ( b2.x - b1.x ) * ( a1.y - a2.y );
	double part2 = ( a1.x - a2.x ) * ( b2.y - b1.y );

	parallel = false;
	double Epsilon	= 0.0001;

	if ( MathUtils::Equalish( part1, part2, Epsilon ) ) {
		intersect = false;
		parallel  = true;
	}
	else {
		double d = part1 - part2;
		double s = ( ( a1.x - b1.x ) * ( a1.y - a2.y ) + ( a1.y - b1.y )	* ( a2.x - a1.x ) ) / d;
		double t = ( ( a1.x - b1.x ) * ( b1.y - b2.y ) + ( a1.y - b1.y )	* ( b2.x - b1.x ) ) / d;

		if ( a1.x == a2.x ) {

			int0.x = a1.x;
			int0.y = s * ( b2.y - b1.y ) + b1.y;
			if ( MathUtils::IsBetween( int0, a1, a2, Epsilon ) )
				t = 0.5;
		}
		else if ( b1.x == b2.x ) {
			int0.x = b1.x;
			int0.y = t * ( a2.y - a1.y ) + a1.y;
			if ( MathUtils::IsBetween( int0, b1, b2, Epsilon ) )
				s = 0.5;
		}
		else {
			int0.x = t * ( a2.x - a1.x ) + a1.x;
			int0.y = t * ( a2.y - a1.y ) + a1.y;
		}
		if( MathUtils::Greaterish(	s, 0, Epsilon ) && 
			MathUtils::Lesserish(	s, 1, Epsilon ) &&
			MathUtils::Greaterish(	t, 0, Epsilon ) &&
			MathUtils::Lesserish(	t, 1, Epsilon ) ) {

			intersect = true;
		}
		else {
			intersect = false;
		}
	}
}

void CDrawProvider::DisplayArc( const VWPoint2D &lastPt, const VWPoint2D &/*thisPt*/, const VWPoint2D &nextPt,
								double radius, VWPoint2D& lastCam, VWPoint2D& thisCam, VWPoint2D& center, double myStart, double myArc)
{
	if ( lastPt != lastCam ) {

		VWLine2D	line( fCurrPolyPt, lastCam );
		this->PolyRenderDrawLine( line );
		fCurrPolyPt	= lastCam;
	}

	if ( myArc ) {
		this->SegmentArc( myStart, myArc, center, radius );
	}

	if ( nextPt != thisCam ) {

		VWLine2D	line( fCurrPolyPt, thisCam );
		this->PolyRenderDrawLine( line );
		fCurrPolyPt	= thisCam;
	}
}

void CDrawProvider::SegmentArc(double inMyStart, double inMyArc, const VWPoint2D& cen, double radius )
{
	double myEnd;

	if ( inMyArc < 0 ) {
		inMyStart	+= 360.0;
	}

	myEnd = inMyArc + inMyStart;

	if ( ( myEnd >= 360.0 ) && ( inMyStart > 360.0 ) ) {
		myEnd 		-= 360.0;
		inMyStart	-= 360.0;
	}

	// start recursion level
	short	startLevel = 8;

	this->RenderArc( inMyStart, myEnd, startLevel, cen, radius );
}

void CDrawProvider::RenderArc(double arcStart, double arcEnd, short currentLevel, const VWPoint2D& cen, double radius)
{
	double	midArc		= ( arcStart + arcEnd ) / 2.0;
	double	normalArc	= midArc;
	if ( midArc >= 360.0 ) {
		normalArc -= 360.0;
	}

	if ( currentLevel > 1 ) {

		currentLevel -- ;
		// recursion
		this->RenderArc( arcStart, midArc, currentLevel, cen, radius );
		
		// draw a line
		const VWPoint2D& nextPt	= this->NextLoc( normalArc, cen, radius );
		
		VWLine2D	line( fCurrPolyPt, nextPt );
		this->PolyRenderDrawLine( line );

		fCurrPolyPt		= nextPt;
		
		// recursion
		this->RenderArc( midArc, arcEnd, currentLevel, cen, radius );
	}
	else {
		const VWPoint2D&	nextPt		= this->NextLoc( midArc, cen, radius );
		
		VWLine2D			line( fCurrPolyPt, nextPt );
		this->PolyRenderDrawLine( line );

		fCurrPolyPt		= nextPt;
	}
}

VWPoint2D CDrawProvider::NextLoc(double a, const VWPoint2D& cen, double radius)
{
	VWPoint2D	orientation( 1, 0 );
	VWPoint2D	perpDir( 0, 1 );

	return	( cen + radius * MathUtils::SpecialSin( a ) * orientation + radius * MathUtils::SpecialCos( a ) * perpDir );
	
}


// ------------------------------------------------------------------------------------------------------------------
VWFC::PluginSupport::TToolStatus CStatusProvider::GetOnePointToolStatus() const
{
	return (VWFC::PluginSupport::TToolStatus) ::GS_OnePointToolStatus( gCBP );
}

VWFC::PluginSupport::TToolStatus CStatusProvider::GetTwoPointToolStatus() const
{
	return (VWFC::PluginSupport::TToolStatus) ::GS_TwoPointToolStatus( gCBP );
}

VWFC::PluginSupport::TToolStatus CStatusProvider::GetThreePointToolStatus() const
{
	return (VWFC::PluginSupport::TToolStatus) ::GS_ThreePointToolStatus( gCBP );
}

VWFC::PluginSupport::TToolStatus CStatusProvider::GetPolyToolStatus() const
{
	return (VWFC::PluginSupport::TToolStatus) ::GS_PolyToolStatus( gCBP );
}

VWFC::PluginSupport::TToolStatus CStatusProvider::GetClickDragToolStatus() const
{
	return (VWFC::PluginSupport::TToolStatus) ::GS_ClickDragToolStatus( gCBP );
}

// ------------------------------------------------------------------------------------------------------------------
void CModeBarProvider::EnableModeGroup(size_t modeGroupID, bool bEnable) const
{
	::GS_EnableMode( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1), bEnable );
}

void CModeBarProvider::SetHelpString(const TXString& helpMessage) const	
{
	::GS_SetHelpString( gCBP, helpMessage );
}

void CModeBarProvider::SetHighlightedHelpString(const TXString& helpMessage) const
{
	gSDK->SetHighlightedHelpString( helpMessage );
}

Sint32 CModeBarProvider::GetModeGroupValue(size_t modeGroupID) const
{
	return ::GS_GetModeValue( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1) ) - 1;
}

void CModeBarProvider::SetModeGroupValue(size_t modeGroupID, Sint32 value) const
{
	::GS_SetModeValue( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1), DemoteTo<short>(kVStanev, value+1) );
}

void CModeBarProvider::SetRadioModeGroupValue(size_t modeGroupID, Sint32 value, const TXStringArray& imageSpecs) const
{
	gSDK->SetRadioButtonModeValue( DemoteTo<short>(kEKolev, modeGroupID + 1), DemoteTo<short>(kEKolev, value + 1), imageSpecs );
}

void CModeBarProvider::InsertPullDownMenuItem(size_t modeGroupID, const TXString& text) const
{
	::GS_AddPullDownMenuItem( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1), text );
}

size_t CModeBarProvider::GetPullDownMenuSelection( size_t modeGroupID ) const
{
	return ::GS_GetModeValue( gCBP, DemoteTo<short>( kYAleksiev, modeGroupID + 1 ) );
}

void CModeBarProvider::SetPullDownMenuSelection(size_t modeGroupID, size_t selection) const
{
	::GS_SetPullDownMenuSelection( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1), DemoteTo<short>(kVStanev, selection) );
}

void CModeBarProvider::SetPullDownResourceValue(size_t modeGroupID, const TXString& value)
{
	gSDK->SetPullDownResourceValue( DemoteTo<short>(kVStanev, modeGroupID+1), value );
}

Sint32 CModeBarProvider::ShowPullDownResourcePopup(size_t modeGroupID, const VectorWorks::SShowPullDownResourcePopup& data, const TXString& selectedName, ThumbnailSizeType thumbSize)
{
	TXStringArray arrEmpty;
	return gSDK->ShowPullDownResourcePopup( DemoteTo<short>(kVStanev, modeGroupID+1), data, selectedName, "", arrEmpty, 0, thumbSize );
}

Sint32 CModeBarProvider::ShowPullDownResourcePopup(size_t modeGroupID, const VectorWorks::SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize)
{
	return gSDK->ShowPullDownResourcePopup( DemoteTo<short>(kVStanev, modeGroupID+1), data, selectedName, categoryTitle, categoryArray, categorySelIndex, thumbSize );
}

bool CModeBarProvider::SetButtonsHelpText(const TXStringArray& arrHelpText) const
{
	return gSDK->SetModeBarButtonsHelpText( arrHelpText );
}

void CModeBarProvider::ClearPullDownMenu(size_t modeGroupID) const
{
	gSDK->ClearClearPullDownMenu( DemoteTo<short>(kVStanev, modeGroupID+1) );
}

void CModeBarProvider::SetEditTextValue(size_t modeGroupID, const TXString& value)
{
	gSDK->SetToolEditTextMethodValue( DemoteTo<short>(kVStanev, modeGroupID+1), value );
}

TXString CModeBarProvider::GetEditTextValue(size_t modeGroupID)
{
	return gSDK->GetToolEditTextMethodValue( DemoteTo<short>(kVStanev, modeGroupID+1) );
}

TXString CModeBarProvider::PullDownResourcePopupGetSelected(size_t modeGroupID)
{
	return gSDK->PullDownResourceGetSelectedResourceName( DemoteTo<short>(kVStanev, modeGroupID+1) );
}

void CModeBarProvider::PullDownResourcePopupSetSelected(size_t modeGroupID, const TXString& name)
{
	return gSDK->PullDownResourceSetSelectedResourceName( DemoteTo<short>(kVStanev, modeGroupID+1), name );
}

bool CModeBarProvider::GetCheckGroupState( size_t modeGroupID ) const
{
	return ::GS_GetModeValue( gCBP, DemoteTo<short>( kYAleksiev, modeGroupID + 1 ) ) != 0;
}

void CModeBarProvider::SetCheckGroupState( size_t modeGroupID, bool state ) const
{
	::GS_SetModeValue( gCBP, DemoteTo<short>( kYAleksiev, modeGroupID + 1 ), DemoteTo<short>( kYAleksiev, state ? 1 : 0 ) );
}


// ------------------------------------------------------------------------------------------------------------------
void CModeBarInitProvider::AddButtonModeGroup(const TXString& iconSpec) const
{
	gSDK->AddButtonMode(iconSpec);
}

void CModeBarInitProvider::AddCheckModeGroup(const TXString& iconSpec, bool initState) const
{
	gSDK->AddCheckMode(initState ? 1 : 0, iconSpec);
}

void CModeBarInitProvider::AddPullDownMenuModeGroup(const TXString& label) const
{
	::GS_AddPullDownMenuMode( gCBP, label );
}

void CModeBarInitProvider::AddRadioModeGroup(size_t initState, const TXStringArray& images) const
{
	gSDK->AddRadioMode(DemoteTo<short>(kVStanev, initState+1 ), images );
}

void CModeBarInitProvider::AddPullDownResourceModeGroup(const TXString& label, const TXString& value) const
{
	gSDK->AddPullDownResourceMethod( label, value );
}

void CModeBarInitProvider::AddTextButtonModeGroup(const TXString& text) const
{
	::GS_AddTxtBtnMode( gCBP, text );
}

void CModeBarInitProvider::AddEditTextModeGroup(const TXString& label, const TXString& value) const
{
	gSDK->AddToolEditTextMethod( label, value );
}

void CModeBarInitProvider::AddEditTextModeGroup(const TXString& label, const TXString& value, Sint32 textWidth) const
{
	gSDK->AddToolEditTextMethodN( label, value, textWidth );
}

void CModeBarInitProvider::PullDownResourcePopupSet(size_t modeGroupID, VectorWorks::Extension::IResourceManagerContent*content) const
{
	gSDK->PullDownResourceSetToolBarPopup( DemoteTo<short>(kVStanev, modeGroupID+1), content );
}

void CModeBarInitProvider::EnableModeGroup(size_t modeGroupID, bool bEnable) const
{
	::GS_EnableMode( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1), bEnable );
}

void CModeBarInitProvider::SetHelpString(const TXString& helpMessage) const
{
	::GS_SetHelpString( gCBP, helpMessage );
}

void CModeBarInitProvider::SetHighlightedHelpString(const TXString& helpMessage) const
{
	gSDK->SetHighlightedHelpString( helpMessage );
}

Sint32 CModeBarInitProvider::GetModeGroupValue(size_t modeGroupID) const
{
	return ::GS_GetModeValue( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1) ) - 1;
}

void CModeBarInitProvider::SetModeGroupValue(size_t modeGroupID, Sint32 value) const
{
	::GS_SetModeValue( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1), DemoteTo<short>(kVStanev, value+1) );
}

void CModeBarInitProvider::InsertPullDownMenuItem(size_t modeGroupID, const TXString& text) const
{
	::GS_AddPullDownMenuItem( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1), text );
}

size_t CModeBarInitProvider::GetPullDownMenuSelection( size_t modeGroupID ) const
{
	return ::GS_GetModeValue( gCBP, DemoteTo<short>( kYAleksiev, modeGroupID + 1 ) );
}

void CModeBarInitProvider::SetPullDownMenuSelection(size_t modeGroupID, size_t selection) const
{
	::GS_SetPullDownMenuSelection( gCBP, DemoteTo<short>(kVStanev, modeGroupID+1), DemoteTo<short>(kVStanev, selection) );
}

void CModeBarInitProvider::SetPullDownResourceValue(size_t modeGroupID, const TXString& value)
{
	gSDK->SetPullDownResourceValue( DemoteTo<short>(kVStanev, modeGroupID+1), value );
}

Sint32 CModeBarInitProvider::ShowPullDownResourcePopup(size_t modeGroupID, const VectorWorks::SShowPullDownResourcePopup& data, const TXString& selectedName, ThumbnailSizeType thumbSize)
{
	TXStringArray arrEmpty;
	return gSDK->ShowPullDownResourcePopup( DemoteTo<short>(kVStanev, modeGroupID+1), data, selectedName, "", arrEmpty, 0, thumbSize );
}

Sint32 CModeBarInitProvider::ShowPullDownResourcePopup(size_t modeGroupID, const VectorWorks::SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize)
{
	return gSDK->ShowPullDownResourcePopup( DemoteTo<short>(kVStanev, modeGroupID+1), data, selectedName, categoryTitle, categoryArray, categorySelIndex, thumbSize );
}

bool CModeBarInitProvider::SetButtonsHelpText(const TXStringArray& arrHelpText) const
{
	return gSDK->SetModeBarButtonsHelpText( arrHelpText );
}

void CModeBarInitProvider::ClearPullDownMenu(size_t modeGroupID) const
{
	gSDK->ClearClearPullDownMenu( DemoteTo<short>(kVStanev, modeGroupID+1) );
}

void CModeBarInitProvider::SetEditTextValue(size_t modeGroupID, const TXString& value)
{
	gSDK->SetToolEditTextMethodValue( DemoteTo<short>(kVStanev, modeGroupID+1), value );
}

TXString CModeBarInitProvider::GetEditTextValue(size_t modeGroupID)
{
	return gSDK->GetToolEditTextMethodValue( DemoteTo<short>(kVStanev, modeGroupID+1) );
}

TXString CModeBarInitProvider::PullDownResourcePopupGetSelected(size_t modeGroupID)
{
	return gSDK->PullDownResourceGetSelectedResourceName( DemoteTo<short>(kVStanev, modeGroupID+1) );
}

void CModeBarInitProvider::PullDownResourcePopupSetSelected(size_t modeGroupID, const TXString& name)
{
	return gSDK->PullDownResourceSetSelectedResourceName( DemoteTo<short>(kVStanev, modeGroupID+1), name );
}

bool CModeBarInitProvider::GetCheckGroupState( size_t modeGroupID ) const
{
	return ::GS_GetModeValue( gCBP, DemoteTo<short>( kYAleksiev, modeGroupID + 1 ) ) != 0;
}

void CModeBarInitProvider::SetCheckGroupState( size_t modeGroupID, bool state ) const
{
	::GS_SetModeValue( gCBP, DemoteTo<short>( kYAleksiev, modeGroupID + 1 ), DemoteTo<short>( kYAleksiev, state ? 1 : 0 ) );
}

void CModeBarInitProvider::SetRadioModeGroupValue(size_t modeGroupID, Sint32 value, const TXStringArray& imageSpecs) const
{
	gSDK->SetRadioButtonModeValue( DemoteTo<short>(kEKolev, modeGroupID + 1), DemoteTo<short>(kEKolev, value + 1), imageSpecs );
}

// ------------------------------------------------------------------------------------------------------------------
CToolPropertiesProvider::CToolPropertiesProvider(Sint32 codeRefID)
{
	fCodeRefID = codeRefID;
}

bool CToolPropertiesProvider::SetProperty(Sint32 propID, bool bValue)
{
	return ::GS_SetToolProperty( gCBP, fCodeRefID, propID, bValue ) ? true : false;
}

bool CToolPropertiesProvider::SetPropertyChar(Sint32 propID, char value)
{
	return ::GS_SetToolPropertyChar( gCBP, fCodeRefID, propID, value ) ? true : false;
}

Sint32 CToolPropertiesProvider::GetCodeRefID()
{
	return fCodeRefID;
}
