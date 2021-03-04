//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"


using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWRoofFaceObj::VWRoofFaceObj(ERoofFaceType newFaceType, const VWPolygon2D& poly)
{
	fhObject = gSDK->CreateBasicSlab( newFaceType );

	fSlabRoofRise				= 0;
	fSlabRoofRun				= 0;
	fSlabRoofMiterType			= kRoofMiterTypeNone;
	fSlabRoofDoubleMiterRatio	= 0;
	fSlabThickness				= 0;
	fSlabHeigh					= 0;

	fdOverhang					= 0;

	fhParentRoof				= NULL;

	fRoofFacePolygon	= poly;

	// make sure the face polygons are always CW
	//if ( ! fRoofFacePolygon.IsProjectionClockWise() ) {
	if ( fRoofFacePolygon.GetArea() > 0 ) {
		fRoofFacePolygon.ReversePoints();
	}

	VWPolygon2DObj	polyObj( fRoofFacePolygon );
	gSDK->AddObjectToContainer( polyObj, fhObject );

	// init the roof face geometry
	this->InitGeometry();
}

VWRoofFaceObj::VWRoofFaceObj(ERoofFaceType newFaceType, const VWPolygon2D& poly, double z, const VWPoint2D& upSlopeDir, double rise, double run)
{
	fhObject = gSDK->CreateBasicSlab( newFaceType );

	fSlabRoofRise				= 0;
	fSlabRoofRun				= 0;
	fSlabRoofMiterType			= kRoofMiterTypeNone;
	fSlabRoofDoubleMiterRatio	= 0;
	fSlabThickness				= 0;
	fSlabHeigh					= 0;

	fdOverhang					= 0;

	fhParentRoof				= NULL;

	fRoofFacePolygon	= poly;

	// make sure the face polygons are always CW
	//if ( ! fRoofFacePolygon.IsProjectionClockWise() ) {
	if ( fRoofFacePolygon.GetArea() > 0 ) {
		fRoofFacePolygon.ReversePoints();
	}

	VWPolygon2DObj	polyObj( fRoofFacePolygon );
	gSDK->AddObjectToContainer( polyObj, fhObject );

	VWRectangle2D	faceBounds = fRoofFacePolygon.GetPolygonBounds();

	double		dim		= Min(faceBounds.GetWidth(), faceBounds.GetHeight()) / 2;
	VWPoint2D	lineDir = upSlopeDir.Perp();

	VWPoint2D	slabRoofPt1 =   lineDir * dim;
	VWPoint2D	slabRoofPt2 = - lineDir * dim;

	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofPt1, TVariableBlock( slabRoofPt1.operator const WorldPt & () ) ) );
	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofPt2, TVariableBlock( slabRoofPt2.operator const WorldPt & () ) ) );
	fSlabRoofLine.SetLine( slabRoofPt1, slabRoofPt2 );

	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofUpslopePt, TVariableBlock( upSlopeDir ) ) );

	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofRise, TVariableBlock( rise ) ) );
	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofRun, TVariableBlock( run ) ) );

	// init the roof face geometry
	this->InitGeometry();
}

VWRoofFaceObj::VWRoofFaceObj(ERoofFaceType newFaceType, const VWPolygon2D& poly, const VWTransformMatrix& transform)
{
	fhObject = gSDK->CreateBasicSlab( newFaceType );

	fSlabRoofRise				= 0;
	fSlabRoofRun				= 0;
	fSlabRoofMiterType			= kRoofMiterTypeNone;
	fSlabRoofDoubleMiterRatio	= 0;
	fSlabThickness				= 0;
	fSlabHeigh					= 0;

	fdOverhang					= 0;

	fhParentRoof				= NULL;

	fRoofFacePolygon	= poly;

	// make sure the face polygons are always CW
	//if ( ! fRoofFacePolygon.IsProjectionClockWise() ) {
	if ( fRoofFacePolygon.GetArea() > 0 ) {
		fRoofFacePolygon.ReversePoints();
	}

	VWPolygon2DObj	polyObj( fRoofFacePolygon );
	gSDK->AddObjectToContainer( polyObj, fhObject );

	this->SetRotationTransform( transform );

	// init the roof face geometry
	this->InitGeometry();
}

VWRoofFaceObj::VWRoofFaceObj(MCObjectHandle hRoofFace)
{
	VWFC_ASSERT( VWRoofFaceObj::IsRoofFaceObject( hRoofFace ) );
	if ( ! VWRoofFaceObj::IsRoofFaceObject( hRoofFace ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating roof face object" );

	fhObject					= hRoofFace;

	fSlabRoofRise				= 0;
	fSlabRoofRun				= 0;
	fSlabRoofMiterType			= kRoofMiterTypeNone;
	fSlabRoofDoubleMiterRatio	= 0;
	fSlabThickness				= 0;
	fSlabHeigh					= 0;

	fdOverhang					= 0;

	// keep 'GetParentObject' call after fhObject init
	// since it re
	fhParentRoof				= NULL;
	MCObjectHandle	hParentObj	= ::GS_ParentObject( gCBP, fhObject );
	if ( VWRoofObj::IsRoofObject( hParentObj ) ) {
		fhParentRoof	= hParentObj;
	}

	// init the roof face geometry
	this->InitGeometry();
}

VWRoofFaceObj::~VWRoofFaceObj()
{
}

VWRoofFaceObj::VWRoofFaceObj(const VWRoofFaceObj& )
{
	VWFC_ASSERT( false );
}
VWRoofFaceObj& VWRoofFaceObj::operator=(const VWRoofFaceObj& )
{
	VWFC_ASSERT( false );
	return *this;
}

bool VWRoofFaceObj::IsRoofFaceObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kSlabNode;	
}

/*static*/ bool VWRoofFaceObj::IsRoofFaceObjectN( MCObjectHandle hRoofFace )
{
	bool result = false;

	if (hRoofFace && gSDK->GetObjectTypeN(hRoofFace) == kSlabNode)
	{
		short			slabKind = 0;
		TVariableBlock	value;
		gSDK->GetObjectVariable( hRoofFace, ovSlabKind, value );
		value.GetSint16( slabKind );
		ERoofFaceType	slabType = (ERoofFaceType) slabKind;

		result = slabType == ERoofFaceType::kRoofFaceType_Roof;
	}
	return result;
}

MCObjectHandle VWRoofFaceObj::GetParentRoof() const
{
	return fhParentRoof;
}

const VWPolygon2D& VWRoofFaceObj::GetPolygon() const
{
	return fRoofFacePolygon;
}

void VWRoofFaceObj::SetPolygon(const VWPolygon2D& poly)
{
	// do this after collecting roof face's info
	MCObjectHandle		hItem	= gSDK->FirstMemberObj( fhObject );
	while ( hItem )
	{
		// try to find some polygon in here
		short		type	= gSDK->GetObjectTypeN( hItem );
		if ( type == kPolygonNode || type == kPolylineNode )
		{
			VWPolygon2DObj	polyObj( hItem );
			polyObj.SetPolygon( poly );
			break;
		}
		else if ( type == kBoxNode )
		{
			VWPolygon2DObj	obj( poly );
			obj.ApplyVertexVisible( poly );
			gSDK->InsertObjectAfter( obj, hItem );

			gSDK->AddBeforeSwapObject(hItem);
			gSDK->DeleteObject( hItem );

			break;
		}

		// ... and go to the next item
		hItem	= ::GS_NextObject( gCBP, hItem );
	}

	this->InitGeometry();
}

const VWPolygon3D& VWRoofFaceObj::GetPolygon3D() const
{
	return fRoofFacePolygon3D;
}

const TSTLPolygons2DArray& VWRoofFaceObj::GetOpeningPolygons() const
{
	return farrOpenings;
}

void VWRoofFaceObj::AddOpeningPolygon(const VWPolygon2D& poly)
{
	MCObjectHandle		hItem	= ::GS_FirstMemberObj( gCBP, fhObject );
	while ( hItem )
	{
		// try to find some polygon in here
		short		type	= gSDK->GetObjectTypeN( hItem );
		if ( type == kPolygonNode || type == kPolylineNode )
		{
			if ( type == kPolygonNode )
			{
				hItem = gSDK->ConvertToPolyline( hItem );
			}

			VWPolygon2DObj	openingPoly( poly );
			gSDK->AttachAuxObject( gSDK->ConvertToPolyline(openingPoly), hItem );

			break;
		}

		// ... and go to the next item
		hItem	= ::GS_NextObject( gCBP, hItem );
	}
}

void VWRoofFaceObj::ClearOpeningPolygons()
{
	MCObjectHandle		hItem	= ::GS_FirstMemberObj( gCBP, fhObject );
	while ( hItem )
	{
		// try to find some polygon in here
		short		type	= gSDK->GetObjectTypeN( hItem );
		if ( type == kPolygonNode || type == kPolylineNode )
		{
			MCObjectHandle h = gSDK->FirstAuxObject( hItem );
			while ( h != nil )
			{
				// we have to go to the next object before deleting current.
				MCObjectHandle	currentHandle	= h;
				h								= gSDK->NextObject( h );
				short			type			= gSDK->GetObjectTypeN( currentHandle );
				if ( type == kPolylineNode )
				{
					gSDK->AddBeforeSwapObject( currentHandle );
					gSDK->DeleteObject( currentHandle );
				}
			}

			break;
		}

		// ... and go to the next item
		hItem	= ::GS_NextObject( gCBP, hItem );
	}
}

VWPoint3D VWRoofFaceObj::GetBearingStartPos() const
{
	return VWPoint3D( fBearingLine.GetStart(), fSlabHeigh );
}

VWPoint3D VWRoofFaceObj::GetBearingEndPos() const
{
	return VWPoint3D( fBearingLine.GetEnd(), fSlabHeigh );
}

void VWRoofFaceObj::GetRotationTransform(VWTransformMatrix& mat) const
{
	if ( MathUtils::Equalish( fBearingLine.GetLength(), 0, 0.0001 ) ) {
		mat.SetIdentity();
	}
	else {
		VWPoint3D			uVec	= fBearingLine.GetDirection();

		VWPoint3D			vVec	= fUpSlopeDir;
		// vVec.z will be ( vVec.Magnitude() * tan( slope_angle ) ).
		// also note that: vVec.Magnitude() is 1.0, and tan( slope_angle ) is ( fSlabRoofRise / fSlabRoofRun ).
		vVec.z						= ( fSlabRoofRise / fSlabRoofRun ) /* vVec.Magnitude() * tan( slope_angle )*/;
		vVec.Normalize();

		VWPoint3D			wVec	= uVec.Cross( vVec );
		wVec.Normalize();

		mat.SetMatrix( uVec, vVec, wVec );
	}
}

void VWRoofFaceObj::SetRotationTransform(const VWTransformMatrix& mat)
{
	VWPoint3D	off	= mat.GetOffset();

	VWPolygon3D	horizPlane( off );
	VWPolygon3D	facePlane      = VWPolygon3D( off, off + mat.GetUVector(), off + mat.GetVVector() );

	VWLine3D	intersLine;
	VWPoint3D	lineDir( 1, 0, 0 );
	if ( facePlane.Intersect( horizPlane, intersLine, VWPoint3D::sEpsilon ) )
	{
		lineDir = intersLine.GetDirectionVector();
	}

	VWRectangle2D	faceBounds = fRoofFacePolygon.GetPolygonBounds();
	double		dim		= Min(faceBounds.GetWidth(), faceBounds.GetHeight()) / 2;

	VWPoint2D	slabRoofPt1 = off + lineDir * dim;
	VWPoint2D	slabRoofPt2 = off - lineDir * dim;

	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofPt1, TVariableBlock( slabRoofPt1.operator const WorldPt & () ) ) );
	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofPt2, TVariableBlock( slabRoofPt2.operator const WorldPt & () ) ) );
	fSlabRoofLine.SetLine( slabRoofPt1, slabRoofPt2 );

	VWPoint2D	upSlopeDir = VWPoint2D(lineDir).Perp();

	fSlabRoofUpslopePt	= off + upSlopeDir * dim;

	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofUpslopePt, TVariableBlock( fSlabRoofUpslopePt ) ) );

	double z = facePlane.GetVerticalDistance( fSlabRoofUpslopePt );

	fSlabRoofRun 	= (fSlabRoofUpslopePt - off).Magnitude();
	fSlabRoofRise 	= z - off.z;

	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofRise, TVariableBlock( fSlabRoofRise ) ) );
	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabRoofRun, TVariableBlock( fSlabRoofRun ) ) );
}

double VWRoofFaceObj::GetThickness() const
{
	return	( fSlabThickness );
}

void VWRoofFaceObj::SetThickness(double value)
{
	fSlabThickness	= value;

	TVariableBlock	var( value );
	VERIFYN( kVStanev, gSDK->SetObjectVariable( fhObject, ovSlabThickness, var ) );
}

void VWRoofFaceObj::SetAsDormerRoofFace(bool isDormerFace)
{
	if ( isDormerFace ) {
		// if this face is dormer roof face
		// then we should not have bearing inset
		// and the inner points should be the bearing points
		fInsetLine		= fBearingLine;
	}
}

void VWRoofFaceObj::CreateOpening(MCObjectHandle hPoly, VWPolygon2D* pPoly)
{
	VWPolygon2DObj	polyObj( hPoly );
	VWPolygon2D		p;
	polyObj.GetPolygon( p );

	VWLine2D	baseLine	= fSlabRoofLine;

	// first calculate base points on which the opening will be projected
	// that are the two points of the line penpendicular of the bearing line
	VWPoint2D	intersPt;
	size_t		polyLen		= fRoofFacePolygon.GetVertexCount();
	for(size_t ip=0; ip<polyLen; ip++) {
		VWLine2D	line	= fRoofFacePolygon.GetLineAt( ip );
		// if we cannot intersect these lines
		// means that we have parallel lines
		if ( ! baseLine.IntersectLines( line, intersPt ) ) {
			baseLine		= line;
		}
	}


	const VWPoint2D&	basePt1				= baseLine.GetStart();
	VWPoint2D			minPt, maxPt;
	VWPoint2D			minProjPt, maxProjPt;
	// min and max distance from the begining of the line (face bearing line)
	double				minProjDist, maxProjDist;
	// mian am max dist from the poly to the line
	double				minDist, maxDist;
	size_t				vertCnt	= p.GetVertexCount();
	for(size_t v=0; v<vertCnt; v++)
	{
		VWPoint2D	pt			= p.GetVertexAt( v );
		VWPoint2D	projPt		= baseLine.PtPerpLine( pt );
		double		dist		= pt.DistanceTo( projPt );
		double		projDist	= basePt1.DistanceTo( projPt );
		if ( v == 0 ) {
			// first time - init
			minPt			= maxPt				= pt;
			minProjPt		= maxProjPt			= projPt;
			minProjDist		= maxProjDist		= projDist;
			minDist			= maxDist			= dist;
		}
		else {
			if ( projDist < minProjDist )
			{
				minPt			= pt;
				minProjPt		= projPt;
				minProjDist		= projDist;
			}
			if ( projDist > maxProjDist )
			{
				maxPt			= pt;
				maxProjPt		= projPt;
				maxProjDist		= projDist;
			}
			if ( dist < minDist )
				minDist		= dist;
			if ( dist > maxDist )
				maxDist		= dist;
		}
	}

	VWPoint2D	minDir	= (minPt - minProjPt).Normalize();
	VWPoint2D	maxDir	= (maxPt - maxProjPt).Normalize();

	// calculate the four points of the rotated bounding box
	VWPoint2D	a		= minProjPt + minDir * minDist;
	VWPoint2D	b		= maxProjPt + minDir * minDist;
	VWPoint2D	c		= minProjPt + maxDir * maxDist;
	VWPoint2D	d		= maxProjPt + maxDir * maxDist;


	pPoly->AddVertex( a );
	pPoly->AddVertex( b );
	pPoly->AddVertex( d );
	pPoly->AddVertex( c );
}

void VWRoofFaceObj::CheckAndCollectOpenings(MCObjectHandle hPolyGroup)
{
	farrOpenings.clear();

	for (MCObjectHandle h = GS_FirstAuxObject( gCBP, hPolyGroup ); h != nil; h = GS_NextObject( gCBP, h ) ) {
		short		type	= gSDK->GetObjectTypeN( h );
		if ( type == kPolylineNode ) {
			VWPolygon2D  poly;

			this->CreateOpening( h, &poly );

			if ( poly.IsValidPolygon( 0.001 )  ) {
				farrOpenings.push_back( poly );
			}
		}
	}
}

void VWRoofFaceObj::InitGeometry()
{
	// collect the roof face info
	TVariableBlock value;

	short		slabKind		= 0;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabKind, value ) );
	VERIFYN( kVStanev, value.GetSint16( slabKind ) );

	// short, 1 = roof, 2 = floor, 3 = column
	fSlabType		= (ERoofFaceType) slabKind;
	
	// WorldCoord, the thickness
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabThickness, value ) );
	VERIFYN( kVStanev, value.GetReal64( fSlabThickness ) );

	// WorldCoord, the z elevation
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabHeight, value ) );
	VERIFYN( kVStanev, value.GetReal64( fSlabHeigh ) );

	WorldPt	slabRoofPt1, slabRoofPt2;
	// WorldPt, first point of the roof axis
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabRoofPt1, value ) );
	VERIFYN( kVStanev, value.GetWorldPt( slabRoofPt1 ) );

	// WorldPt, second point of the roof axis
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabRoofPt2, value ) );
	VERIFYN( kVStanev, value.GetWorldPt( slabRoofPt2 ) );

	fSlabRoofLine.SetLine( slabRoofPt1, slabRoofPt2 );

	WorldPt		upSlopePt;
	// WorldPt, a point on the upslope side of the roof
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabRoofUpslopePt, value ) );
	VERIFYN( kVStanev, value.GetWorldPt( upSlopePt ) );
	fSlabRoofUpslopePt		= upSlopePt;

	// WorldCoord, the rise over a given distance.  Use with the run to calculate a slope
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabRoofRise, value ) );
	VERIFYN( kVStanev, value.GetReal64( fSlabRoofRise ) );

	// WorldCoord, the run over a given distance.  Use with the rise to calculate a slope
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabRoofRun, value ) );
	VERIFYN( kVStanev, value.GetReal64( fSlabRoofRun ) );

	// mitter type
	short mitterType			= 0;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabRoofMiterType, value ) );
	VERIFYN( kVStanev, value.GetSint16( mitterType ) );
	ASSERTN( kVStanev, mitterType <= 4 );
	fSlabRoofMiterType	= (ERoofMiterType)mitterType;

	// double_gs, the percentage of a double miter which is vertical (1 is a vertical miter and 0 is a horizontal)
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovSlabRoofDoubleMiterRatio, value ) );
	VERIFYN( kVStanev, value.GetReal64( fSlabRoofDoubleMiterRatio ) );

	// if the roof face rise is negative then this roof face has downward slope
	// so we have to correct the z elevation of this roof face
	if ( fSlabRoofRise < 0 ) {
		double			angle	= atan( Abs( fSlabRoofRise / fSlabRoofRun ) );
		fSlabHeigh		-= ( fSlabThickness / cos( angle ) );
	}

	// calculate the help data
	VWPoint2D		projPt1		= fSlabRoofLine.PtPerpLine( fSlabRoofUpslopePt );
	fUpSlopeDir					= ( fSlabRoofUpslopePt - projPt1 ).Normalize();

	// do this after collecting roof face's info
	MCObjectHandle		hItem	= ::GS_FirstMemberObj( gCBP, fhObject );
	while ( hItem )	{
		// try to find some polygon in here
		short		type	= gSDK->GetObjectTypeN( hItem );
		if ( type == kPolygonNode || type == kPolylineNode ) {
			// create the polygon representation
			fRoofFacePolygon.ClearVertices();
			short	numVerts	= ::GS_CountVertices( gCBP, hItem );
			if ( numVerts > 2 )	{
				for(short i=1; i<=numVerts; i++) {

					WorldPt		vertex;
					VertexType	vType;
					WorldCoord	arcRadius;

					::GS_GetVertex( gCBP, hItem, i, vertex, vType, arcRadius );

					fRoofFacePolygon.AddVertex( vertex );
				}

				// make sure the face polygons are always CW
				//if ( ! fRoofFacePolygon.IsProjectionClockWise() ) {
				if ( fRoofFacePolygon.GetArea() > 0 ) {
					fRoofFacePolygon.ReversePoints();
				}

				this->CheckAndCollectOpenings( hItem );

				break;
			}
		}
		else if ( type == kBoxNode ) {
			// create the polygon representation
			fRoofFacePolygon.ClearVertices();

			WorldRect		bounds;
			if ( ::GS_GetObjectBounds( gCBP, hItem, bounds ) ) {
				fRoofFacePolygon.AddVertex( bounds.TopLeft() );
				fRoofFacePolygon.AddVertex( bounds.TopRight() );
				fRoofFacePolygon.AddVertex( bounds.BotRight() );
				fRoofFacePolygon.AddVertex( bounds.BotLeft() );
			}
		}

		// ... and go to the next item
		hItem	= ::GS_NextObject( gCBP, hItem );
	}

	ASSERTN( kVStanev, fRoofFacePolygon.GetVertexCount() > 2 );

	this->CalculateSlabAndBearingPoints();
	this->CalculateOverhang();
	this->EnsureDirectionOfReferencePoints();

	// calculate the 3D face polygon, with rising the 2D polygon
	VWTransformMatrix		slab3DRot;
	this->GetRotationTransform( slab3DRot );
	slab3DRot.SetOffset( this->GetBearingStartPos() );

	VWPolygon3D				slab3DPlane( slab3DRot );
	fRoofFacePolygon3D					= fRoofFacePolygon;
	size_t					vertsCnt	= fRoofFacePolygon3D.GetVertexCount();
	for(size_t i=0; i<vertsCnt; i++) {
		VWPoint3D&	pt	= fRoofFacePolygon3D.GetVertexAt( i );
		pt.z			= slab3DPlane.GetVerticalDistance( pt );
	}
}

void VWRoofFaceObj::GetIntersectionSegments(const VWPoint2D& pt, const VWPoint2D& dir, TSTLPoints2DArray& /*out*/ arrPts) const
{
	TSTLPoints2DArray	arrIntersPts;

	VWLine2D		segmentLine( pt, pt+dir );
	size_t			len			= fRoofFacePolygon.GetVertexCount();
	for(size_t i=0; i<len; i++) {
		VWLine2D	line	= fRoofFacePolygon.GetLineAt( i );

		VWPoint2D	intersPt;
		if ( segmentLine.IntersectLineSegments( line, intersPt ) ) {
			bool	bFound	= false;
			size_t	ll		= arrIntersPts.size();
			for(size_t j=0; j<ll; j++) {
				if ( arrIntersPts[j] == intersPt ) {
					bFound	= true;
					break;
				}
			}

			if ( !bFound )
				arrIntersPts.push_back( intersPt );
		}
	}

	// if there is only one point clear it, since this is the begin point at some corner
	if ( arrIntersPts.size() == 1 )
		arrIntersPts.clear();

	arrPts.clear();

	// make segments from each two points that lie inside the roof face
	size_t	ptsCnt		= arrIntersPts.size();
	if ( ptsCnt == 2 ) {
		// add the only one segment
		arrPts.push_back( arrIntersPts[0] );
		arrPts.push_back( arrIntersPts[1] );
	}
	else if ( ptsCnt > 2 ) {
		// check if there are many segments
		// which lines inside the roof face polygon
		// and add them as segments
		for(size_t i=0; i<ptsCnt; i++) {
			WorldPt		a		= arrIntersPts[i];
			WorldPt		b		= arrIntersPts[(i+1)%ptsCnt];
			WorldPt		midPt	= (a + b) / 2;

			if ( fRoofFacePolygon.IsPtInPoly2D( midPt, VWPoint2D::sEpsilon ) ) {
				arrPts.push_back( a );
				arrPts.push_back( b );
			}
		}
	}
}

void VWRoofFaceObj::CalculateOverhang()
{
	VWPoint2D	perp		= - fSlabRoofLine.GetDirection().Perp();
	VWPoint2D	slabRoofPt1	= fSlabRoofLine.GetStart();

	// calculate line equation
	double A		= perp.x;
	double B		= perp.y;
	double C		= - (slabRoofPt1.x * A + slabRoofPt1.y * B);

	// determine the side on which slab side the upslope point is according the bearing line
	bool	sign1	= A * fSlabRoofUpslopePt.x + B * fSlabRoofUpslopePt.y + C >= 0;

	fdOverhang		= 0;
	bool	bFirst	= true;

	size_t	len		= fRoofFacePolygon.GetVertexCount();
	for(size_t i=0; i<len; i++) {
		VWPoint2D	a		= fRoofFacePolygon.GetVertexAt( i );

		double		k		= A * a.x + B * a.y + C;
		if ( Abs(k) > 0.00001 ) {
			// determine the side on which side this point is according the bearing line
			bool	sign2	= k >= 0;

			// if not on the same side as the upslope pt
			// then we have overhang
			if ( sign2 != sign1 ) {
				VWPoint2D	projPt			= fBearingLine.PtPerpLine( a );
				double		thisOverhang	= (projPt-a).Magnitude();
				if ( bFirst || thisOverhang > fdOverhang ){
					bFirst		= false;
					fdOverhang	= thisOverhang;
				}
			}
		}
	}
}

// return true if the given line (pt1, pt2) lies on a side of this roof face
// side of roof face are those lines which intersect with slab line
bool VWRoofFaceObj::IsLyingOnSide(const VWPoint2D& pt1, const VWPoint2D& pt2) const
{
	bool		isOnSide	= false;

	VWLine2D	sideLine( pt1, pt2 );

	VWPoint2D	ptInters;
	if ( fSlabRoofLine.IntersectLines( sideLine, ptInters, isOnSide ) ) {
		if ( ! isOnSide ) {
			VWLine2D	baseLine;
			bool		bFound	= false;
			size_t		len		= fRoofFacePolygon.GetVertexCount();
			for(size_t i=0; i<len; i++) {
				VWLine2D	line	= fRoofFacePolygon.GetLineAt( i );

				VWPoint2D	ptInters;
				// if we cannot intersect these lines
				// means that we have parallel lines
				if ( ! fSlabRoofLine.IntersectLines( line, ptInters ) ) {
					bFound		= true;
					baseLine	= line;
					break;
				}
			}

			if ( bFound ) {
				baseLine.IntersectLines( sideLine, ptInters, isOnSide );
			}
		}
	}

	return isOnSide;
}

// return true if the given roof face is touching this on it's edge line
// side of roof face are those lines which intersect with slab line
bool VWRoofFaceObj::IsLyingOnSide(const VWRoofFaceObj* pFace) const
{
	VWLine2D	baseLine	= fSlabRoofLine;
	size_t		len			= fRoofFacePolygon.GetVertexCount();
	for(size_t i=0; i<len; i++) {
		VWLine2D	line	= fRoofFacePolygon.GetLineAt( i );

		VWPoint2D	ptInters;
		// if we cannot intersect these lines
		// means that we have parallel lines
		if ( ! fSlabRoofLine.IntersectLines( line, ptInters ) ) {
			baseLine		= line;
			break;
		}
	}

	for(size_t i=0; i<len; i++) {
		VWLine2D	line	= fRoofFacePolygon.GetLineAt( i );

		VWPoint2D	ptInters;
		bool		isOnSegments	= false;
		if ( baseLine.IntersectLines( line, ptInters, isOnSegments ) ) {
			return isOnSegments;
		}
	}

	return false;
}

void VWRoofFaceObj::CalculateSlabAndBearingPoints()
{
	// init these points.
	fBearingLine				= fSlabRoofLine;
	bool	bFoundBearing		= false;
	double	minDistForBearing	= 0;

	// find which segment of the roof's polygon is lying on this roof face
	// this segment will make the real slab roof points
	if ( fhParentRoof ) {
		VWRoofObj			roofObj( fhParentRoof );

		const VWPolygon2D&	roofPoly	= roofObj.GetRoofPoly();
		size_t				len			= roofPoly.GetVertexCount();
		for(size_t i=0; i<len; i++) {
			VWLine2D	line	= roofPoly.GetLineAt( i );

			VWPoint2D	ptInters;
			// if we cannot intersect these lines
			// means that we have parallel lines
			if ( ! fSlabRoofLine.IntersectLines( line, ptInters ) ) {
				// ok, this could be. Try to see if this is not another parallel segment
				// check it to see ifthe middle point of this segment is in this roof face's polygon
				WorldPt		midPt		= line.CenterPt();
				if ( fRoofFacePolygon.IsPtInPoly2D( midPt, 1 ) || fRoofFacePolygon.IsPtOnPoly2D( midPt, 1 ) ) {
					// ok this is the one
					// not calculate the real slab points
					// which should be the closest line to (fSlabRoofPt1, fSlabRoofPt2)
					VWPoint2D	projPt	= fSlabRoofLine.PtPerpLine( midPt );
					double		dist	= (projPt - midPt).Magnitude();
					if ( ! bFoundBearing || dist < minDistForBearing ) {
						bFoundBearing		= true;

						minDistForBearing	= dist;
						fBearingLine		= line;
					}
				}
			}
		}

/*ObjectColorType color;
color.penFore = 4; color.fillFore	= 0; color.fillBack	= 0; color.penBack	= 0;
GSHandle	h = GS_CreateLine( gCBP, fBearingPt1, fBearingPt2 );
GS_SetColor( gCBP, h, color );*/

		WorldCoord	bearingInset	= roofObj.GetBearingInset();
		// NOTE! this causes infitite loop trough the object creation
		//if ( roofObj.IsRoofFaceDormer( fhObject ) )
		//	bearingInset		= 0;
		fInsetLine					+= fUpSlopeDir * bearingInset;

/*color.penFore = 6; color.fillFore	= 0; color.fillBack	= 0; color.penBack	= 0;
h = GS_CreateLine( gCBP, fInsetPt1, fInsetPt2 );
GS_SetColor( gCBP, h, color );*/
	}
}

//-----------------------------------------------------------------------------------------
// return true if the specified point lies on a gable end
//-----------------------------------------------------------------------------------------
bool VWRoofFaceObj::IsOnGableEnd(const VWPoint2D& pt)
{
	VWPoint2D		projPt1		= fSlabRoofLine.PtPerpLine( pt );

	TSTLPoints2DArray	arrPts;
	this->GetIntersectionSegments( projPt1, fSlabRoofLine.GetStart() - fSlabRoofLine.GetEnd(), arrPts );

	size_t		len				= arrPts.size();
	for(size_t i=0; i<len; i++) {
		if ( projPt1 == arrPts[i] )
			return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void VWRoofFaceObj::ModifyForDormer(const VWPoint2D& pt1, const VWPoint2D& pt2)
{
	VWPoint2D	projPt	= fBearingLine.PtPerpLine( pt1 );
	double		a		= (projPt-pt1).Magnitude();

	double		tanA	= Abs( fSlabRoofRise / fSlabRoofRun );
	fSlabHeigh			= ( fSlabHeigh / tanA - a ) * tanA;

	fBearingLine.SetStart( pt1 );
	fBearingLine.SetEnd( pt2 );
	fInsetLine			= fBearingLine;

	this->EnsureDirectionOfReferencePoints();

/*	fSlabRoofRise		= Abs( fSlabRoofRise );
	fSlabRoofRun		= Abs( fSlabRoofRun );

	WorldPt		projPt	= MathUtils::PtPerpLine( pt1, fBearingPt1, fBearingPt2 );
	double_gs	a		= (projPt-pt1).Magnitude();

	double_gs	tanA	= fSlabRoofRise / fSlabRoofRun;
	fSlabHeigh			= ( fSlabHeigh / tanA - a ) * tanA;

	fSlabRoofPt1		= pt1;
	fSlabRoofPt2		= pt2;

	fUpSlopeDir			= - fUpSlopeDir;
	
	this->CalculateSlabAndBearingPoints();
	this->CalculateOverhang();*/
}

//-----------------------------------------------------------------------------------------
// makes sure that fBearingPt1, fBearingPt2 and fInsetPt1,fInsetPt2 points have proper direction
// the perp vertor of (fBearingPt2-fBearingPt1) should be collinear with upslope vector
//-----------------------------------------------------------------------------------------
void VWRoofFaceObj::EnsureDirectionOfReferencePoints()
{
	VWPoint2D	bearingDir	= fBearingLine.GetDirection().Perp();

	if ( Abs( fUpSlopeDir.x - bearingDir.x ) > 0.01 || Abs( fUpSlopeDir.y - bearingDir.y ) > 0.01  ) {
		fBearingLine.ReverseSides();
	}

	VWPoint2D	insetDir	= fInsetLine.GetDirection().Perp();
	if ( Abs( fUpSlopeDir.x - insetDir.x ) > 0.01 || Abs( fUpSlopeDir.y - insetDir.y ) > 0.01  ) {
		fInsetLine.ReverseSides();
	}
}