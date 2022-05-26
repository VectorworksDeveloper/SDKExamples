//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWSolidObj::VWSolidObj(EVWSolidObjOperation operation, MCObjectHandle hObject1, MCObjectHandle hObject2)
{
	short	error	= 1;
	switch( operation ) {
		case kVWSolidObjOperation_Add:
			error	= ::GS_AddSolid( gCBP, hObject1, hObject2, fhObject );
			break;
		case kVWSolidObjOperation_Intersect:
			error	= ::GS_IntersectSolid( gCBP, hObject1, hObject2, fhObject );
			break;
		case kVWSolidObjOperation_Subtract:
			error	= ::GS_SubtractSolid( gCBP, hObject1, hObject2, fhObject );
			break;
	}

	VWFC_ASSERT( error == 0 && fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "VWSolidObj : cannot create extrude" );
}

VWSolidObj::VWSolidObj(const VWPolygon2D& base, const VWPoint3D& dir)
{
	// the extrusion should not be in horizontal plane
	VWFC_ASSERT( ! MathUtils::Equalish( dir.z, 0, VWPoint3D::sEpsilon ) );
	if ( MathUtils::Equalish( dir.z, 0, VWPoint3D::sEpsilon )  )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "VWSolidObj : cannot have Oxy plane extrusion" );

	TSTLPolygons2DArray	arrOpenings;
	fhObject					= this->CreateObject( base, arrOpenings, dir );

	VWFC_ASSERT( fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "VWSolidObj : cannot create extrude" );
}

VWSolidObj::VWSolidObj(const VWPolygon3D& base, const VWPoint3D& dir)
{
	bool				bISCW			= base.IsClockWise();
	VWTransformMatrix	matrix			= base.GetTransformMatrix();
	if ( bISCW ) {
		VWPoint3D	vVec			= matrix.GetVVector();
		VWPoint3D	wVec			= matrix.GetWVector();
		matrix.SetVVector( - vVec );
		matrix.SetWVector( - wVec );
	}

	VWPolygon3D			planarBase	= base;
	VWPoint3D			extrudeDir	= dir;
	planarBase.InversePointsTransform( matrix );

	VWPoint3D			offset		= matrix.GetOffset();
	matrix.SetOffset( 0, 0, 0 );
	extrudeDir						= matrix.InversePointTransform( extrudeDir );
	matrix.SetOffset( offset );

	VWPolygon2D			planarBase2D;
	planarBase.GetPlanarPolygon( planarBase2D );

	TSTLPolygons2DArray	arrOpenings;
	fhObject					= this->CreateObject( planarBase2D, arrOpenings, extrudeDir );
	if ( fhObject ) {
		this->SetObjectMatrix( matrix );
	}

	VWFC_ASSERT( fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "VWSolidObj : cannot create extrude" );
}

VWSolidObj::VWSolidObj(const VWPolygon2D& base, const TSTLPolygons2DArray& arrOpenings, const VWPoint3D& dir)
{
	// the extrusion should not be in horizontal plane
	VWFC_ASSERT( ! MathUtils::Equalish( dir.z, 0, VWPoint3D::sEpsilon ) );
	if ( MathUtils::Equalish( dir.z, 0, VWPoint3D::sEpsilon )  )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "VWSolidObj : cannot have Oxy plane extrusion" );

	fhObject					= this->CreateObject( base, arrOpenings, dir );

//	VWFC_ASSERT( fhObject != nil );
//	if ( fhObject == NULL )
//		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "VWSolidObj : cannot create extrude" );
}

VWSolidObj::VWSolidObj(const VWPolygon3D& base, const TSTLPolygons3DArray& arrOpenings, const VWPoint3D& dir)
{
	VWTransformMatrix	transf		= base.GetTransformMatrix();

	VWPoint3D			extrudeDir	= dir;
	VWPolygon3D			planarBase	= base;
	planarBase.InversePointsTransform( transf );
	transf.InversePointTransform( extrudeDir );

	TSTLPolygons2DArray	arrOpenings2D;
	size_t				opCnt		= arrOpenings.size();
	for(size_t i=0; i<opCnt; i++) {
		VWPolygon3D		opPoly	= arrOpenings[ i ];
		opPoly.InversePointsTransform( transf );

		VWPolygon2D		opPoly2D;
		opPoly.GetPlanarPolygon( opPoly2D );
		arrOpenings2D.push_back( opPoly2D );
	}

	VWPolygon2D			planarBase2D;
	planarBase.GetPlanarPolygon( planarBase2D );

	fhObject					= this->CreateObject( planarBase2D, arrOpenings2D, extrudeDir );
	if ( fhObject ) {
		this->SetObjectMatrix( transf );
	}

	VWFC_ASSERT( fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "VWSolidObj : cannot create extrude" );
}

VWSolidObj::VWSolidObj(MCObjectHandle hSolid)
{
	VWFC_ASSERT( VWSolidObj::IsSolidObject( hSolid ) );
	if ( ! VWSolidObj::IsSolidObject( hSolid ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "VWSolidObj : bad handle type when creating" );
	fhObject		= hSolid;
	VWFC_ASSERT( fhObject != nil );
}

VWSolidObj::VWSolidObj(const VWSolidObj& src)
{
	fhObject		= src.fhObject;
}

VWSolidObj::~VWSolidObj()
{
	fhObject		= NULL;
}

VWSolidObj& VWSolidObj::operator=(const VWSolidObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

bool VWSolidObj::IsSolidObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kCSGTreeNode;
}

MCObjectHandle VWSolidObj::CreateObject(const VWPolygon2D& base, const TSTLPolygons2DArray& arrOpenings, const VWPoint3D& dir)
{
	VWFC_ASSERT( ! MathUtils::Equalish( dir.z, 0, VWPoint3D::sEpsilon ) );
	VWFC_ASSERT( base.GetVertexCount() > 0 );
	if ( MathUtils::Equalish( dir.z, 0, VWPoint3D::sEpsilon )  )
		return NULL;
	if ( base.GetVertexCount() == 0 )
		return NULL;

	VWPoint3D			wDir	= dir;
	wDir.Normalize();
	VWPoint3D			uDir( 1, 0, 0 );
	VWPoint3D			vDir	= wDir.Cross( uDir );
	vDir.Normalize();
	uDir						= vDir.Cross( wDir );
	uDir.Normalize();

	VWTransformMatrix	mat( uDir, vDir, wDir );
	double				extrLength	= dir.Magnitude();

	double				kCleanUpEpsilon	= 0.01;

	// create 2d base section on which the main extrude will be created
	VWPoint2D			firstPt		= base.GetVertexAt( 0 );
	VWPolygon2D			baseSection	= base;
	baseSection.CleanUpPolygon( kCleanUpEpsilon );
	baseSection.MovePolygon( - firstPt.x, - firstPt.y );
	baseSection.InversePointsTransform( mat );

	// create openings sections
	TSTLPolygons2DArray	arrOpeningSections;
	size_t				openingsCnt	= arrOpenings.size();
	for(size_t i=0; i<openingsCnt; i++) {
		VWPolygon2D		openingSection	= arrOpenings[ i ];
		openingSection.CleanUpPolygon( kCleanUpEpsilon );
		// remove last point
		size_t			vertCnt			= openingSection.GetVertexCount();
		if ( vertCnt > 1 ) {
			double_gs	dist	= ( openingSection.GetVertexAt(vertCnt-1) - openingSection.GetVertexAt(0) ).Magnitude();
			if ( dist < kCleanUpEpsilon ) {
				VWPoint2D&		vertex	= openingSection.GetVertexAt( vertCnt - 1 );
				vertex					= openingSection.GetVertexAt( vertCnt - 2 );
				openingSection.CleanUpPolygon( kCleanUpEpsilon );
			}
		}

		openingSection.MovePolygon( - firstPt.x, - firstPt.y );
		openingSection.InversePointsTransform( mat );

		arrOpeningSections.push_back( openingSection );
	}

	// prepare bounding for cliping extrudes
	VWRectangle2D		baseBounds	= baseSection.GetPolygonBounds();
	double				dBaseDiag	= sqrt( baseBounds.GetHeight() * baseBounds.GetHeight() + baseBounds.GetWidth() * baseBounds.GetWidth() );

	// calculate upright extrude length
	bool				bUpRight	= wDir.z > 0;
	double				dZAngle		= wDir.DotProduct( VWPoint3D( 0, 0, 1 ) );
	double				dUprightLen	= 2 * (extrLength / dZAngle) + dBaseDiag * dZAngle;
	double				dTopCutElev	= extrLength * dZAngle;

	// create the extrude object and rotate it
	VWExtrudeObj	extrudeObj( baseSection, 0, /*(bUpRight ? 1 : -1) **/ 4 * dUprightLen );

	const double	kOffsetDist		= 10;

	// put extrude's openings
	// XXX Bobi: here I subtract openings from the extrude object instead of adding holes to it.
	// I do this because of a problem with subtracting from extrudes with holes (with added holes to the base polygon)
	MCObjectHandle	hExtrude	= extrudeObj;
	size_t			sectOpCnt	= arrOpeningSections.size();
	for( size_t i = 0 ; i < sectOpCnt ; i ++ ) {
		const VWPolygon2D&	openingPoly	= arrOpeningSections[ i ];
		VWExtrudeObj		openingObj( openingPoly,  - kOffsetDist, ( 4 * dUprightLen ) + kOffsetDist );
		::GS_SubtractSolid( gCBP, hExtrude, openingObj, hExtrude );
	}
	// XXX Bobi: openings are subtracted from the extrude object instead of adding holes to it.
	/*
	size_t			sectOpCnt	= arrOpeningSections.GSSize();
	for(size_t i=0; i<sectOpCnt; i++) {
		const VWPolygon2D&	openingPoly	= arrOpeningSections[ i ];
		extrudeObj.AddHoleObject( openingPoly );
	}
	MCObjectHandle	hExtrude	= extrudeObj;
	*/
	// position the main extrude
	::GS_SetEntityMatrix( gCBP, hExtrude, mat );
	VWPoint3D		moveAmount	= - wDir * 2 * dUprightLen;
	moveAmount.x				+= firstPt.x;
	moveAmount.y				+= firstPt.y;
	::GS_MoveObject3D( gCBP, hExtrude, moveAmount.x, moveAmount.y, moveAmount.z );

	// get the rotated extrude's bounds
	WorldCube	objBounds;
	::GS_ResetObject( gCBP, hExtrude );
	::GS_GetObjectCube( gCBP, hExtrude, objBounds );

	// create base bound rectangle for the clipping extrudes
	VWPolygon2D		boundRect;
	boundRect.AddVertex( objBounds.MinX() - kOffsetDist, objBounds.MinY() - kOffsetDist );
	boundRect.AddVertex( objBounds.MinX() - kOffsetDist, objBounds.MaxY() + kOffsetDist );
	boundRect.AddVertex( objBounds.MaxX() + kOffsetDist, objBounds.MaxY() + kOffsetDist );
	boundRect.AddVertex( objBounds.MaxX() + kOffsetDist, objBounds.MinY() - kOffsetDist );
	boundRect.SetClosed( true );

	// create the clipping extrudes
	VWExtrudeObj	botClipObj( boundRect, 0,			(bUpRight ? -1 : 1) * ( objBounds.Depth() + kOffsetDist ) );
	VWExtrudeObj	topClipObj( boundRect, dTopCutElev, (bUpRight ? 1 : -1) * ( objBounds.Depth() + kOffsetDist ) );

	// subtract the clipping from the object
	MCObjectHandle	hBotClipObj	= botClipObj;
	MCObjectHandle	hTopClipObj	= topClipObj;
	MCObjectHandle	hRes1		= NULL;
	MCObjectHandle	hRes2		= NULL;
	::GS_SubtractSolid( gCBP, hExtrude,	hBotClipObj,		hRes1 );
	if ( hRes1 == NULL && hExtrude && hBotClipObj ) {
/*		hExtrude		= ::GS_ConvertTo3DPolygons( gCBP, hExtrude, false );
		if ( hExtrude ) {
			hBotClipObj		= ::GS_ConvertTo3DPolygons( gCBP, hBotClipObj, false );
			if (	::GS_GroupToMesh( gCBP, hExtrude ) == kMeshNoError &&
					::GS_GroupToMesh( gCBP, hBotClipObj ) == kMeshNoError )
			{
				::GS_SubtractSolid( gCBP, hExtrude,	hBotClipObj,		hRes1 );
			}
		}*/
	}

	::GS_SubtractSolid(gCBP, hRes1,			hTopClipObj,		hRes2 );
	if ( hRes2 == NULL && hRes1 && hTopClipObj ) {
/*		hRes1			= ::GS_ConvertTo3DPolygons( gCBP, hRes1, false );
		if ( hRes1 ) {
			hTopClipObj		= ::GS_ConvertTo3DPolygons( gCBP, hTopClipObj, false );
			if (	::GS_GroupToMesh( gCBP, hRes1 ) == kMeshNoError &&
					::GS_GroupToMesh( gCBP, hTopClipObj ) == kMeshNoError )
			{
				::GS_SubtractSolid(gCBP, hRes1,			hTopClipObj,		hRes2 );
			}
		}*/
	}

	if ( hRes2 == NULL ) {
		hRes2	= hRes1;
		if ( hRes1 == NULL ) {
			if ( hBotClipObj )	::GS_DeleteObject( gCBP, hBotClipObj, false );

			hRes2		= hExtrude;
		}

		if ( hTopClipObj )	::GS_DeleteObject( gCBP, hTopClipObj, false );
	}

	return hRes2;
}

/*static*/ void VWSolidObj::RunSelfTest()
{
	Sint32			testMode			= 3;

	if ( testMode == 3 ) {
		{
			VWPolygon3D		base3d;
			base3d.AddVertex( 0,		0,		0 );
			base3d.AddVertex( 100,		0,		20 );
			base3d.AddVertex( 100,		100,	20 );
			base3d.AddVertex( 0,		100,	0 );
			VWPoint3D		dir( 0, 0, 1 );	dir.Normalize();
			dir								*= 50;
			VWSolidObj		obj( base3d, dir );
			VWPolygon3DObj	baseObj( base3d );
			obj.ResetObject();
		}
		{
			VWPolygon3D		base3d;
			base3d.AddVertex( 0,		0,		0 );
			base3d.AddVertex( 100,		0,		20 );
			base3d.AddVertex( 100,		100,	20 );
			base3d.AddVertex( 0,		100,	0 );
			base3d.MovePoints( 400, 0, 0 );
			VWPoint3D		dir( 0, 0, -1 );	dir.Normalize();
			dir								*= 50;
			VWSolidObj		obj( base3d, dir );
			VWPolygon3DObj	baseObj( base3d );
			obj.ResetObject();
		}
	}
	else if ( testMode == 2 ) {
		{ // big base poly with small extrude
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 2000,		0	);
			base2d.AddVertex( 2000,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 0, 0 );
			VWPoint3D		dir( 1, 0, 1 );	dir.Normalize();
			dir								*= 50;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
		{
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 0, 1000 );
			VWPoint3D		dir( 0.9659, 0, 0.2588 );
			dir								*= 100;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
	}
	else if ( testMode == 0 || testMode == 1 ) {
		// angles of positive extrusions and negative extrusions
		double		dExtrudeHeight		= (testMode==1) ? -100 : 100;
		{
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 0, 0 );
			VWPoint3D		dir( 0, 0, 1 );	dir.Normalize();
			dir								*= dExtrudeHeight;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
		{
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 400, 0 );
			VWPoint3D		dir( 1, 0, 1 );	dir.Normalize();
			dir								*= dExtrudeHeight;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
		{
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 800, 0 );
			VWPoint3D		dir( 1, 1, 1 );	dir.Normalize();
			dir								*= dExtrudeHeight;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
		{ // second row
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 0, -400 );
			VWPoint3D		dir( 0, 1, 1 );	dir.Normalize();
			dir								*= dExtrudeHeight;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
		{
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 400, -400 );
			VWPoint3D		dir( -1, 1, 1 );	dir.Normalize();
			dir								*= dExtrudeHeight;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
		{
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 800, -400 );
			VWPoint3D		dir( -1, 0, 1 );	dir.Normalize();
			dir								*= dExtrudeHeight;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
		{ // third row
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 0, -800 );
			VWPoint3D		dir( -1, -1, 1 );	dir.Normalize();
			dir								*= dExtrudeHeight;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
		{
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 400, -800 );
			VWPoint3D		dir( 0, -1, 1 );	dir.Normalize();
			dir								*= dExtrudeHeight;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
		{
			VWPolygon2D		base2d;
			base2d.AddVertex( 0,		0	);
			base2d.AddVertex( 200,		0	);
			base2d.AddVertex( 200,		100	);
			base2d.AddVertex( 0,		100 );
			base2d.MovePolygon( 800, -800 );
			VWPoint3D		dir( 1, -1, 1 );	dir.Normalize();
			dir								*= dExtrudeHeight;
			VWSolidObj		obj( base2d, dir );
			VWPolygon3DObj	baseObj( base2d );
			obj.ResetObject();
		}
	}
	else {
		// unrecognized test mode
		VWFC_ASSERT( false );
	}
}
