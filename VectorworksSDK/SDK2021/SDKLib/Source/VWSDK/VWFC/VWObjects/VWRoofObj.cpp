//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWRoofObj::VWRoofObj(MCObjectHandle hRoof)
{
	VWFC_ASSERT( VWRoofObj::IsRoofObject( hRoof ) );
	if ( ! VWRoofObj::IsRoofObject( hRoof ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating roof object" );

	fhObject		= hRoof;

	// fbGenGableWall: Set to true to have a wall created at gable ends of the roof.  Otherwise no object will be inserted.
	// fdBearingInset  is where the weight of the roof rests on the wall.  This is an inset from the defining edge of the roof plan.
	// fMiterType: Specify 1 for a vertical miter, 2 for horizontal miter, 3 for a double miter cut, and 4 for a square end miter cut.
	// fdVertMiter: This is used only with the double miter type; it specifies the vertical length of the miter cut.
	short miterType;
	VERIFYN( kVStanev, ::GS_GetRoofAttributes( gCBP, fhObject, fbGenGableWall, fdBearingInset, fdRoofThick, miterType, fdVertMiter ) );
	fMiterType				= (ERoofMiterType)(miterType % 10);
	fSkylightMiterType		= (ERoofMiterType)Sint32(miterType / 10);

	short		count		= ::GS_CountVertices( gCBP, fhObject );
	
	// extract the roof faces
	for(short index=1; index<=count; index++) {
		WorldPt		pt;
		double_gs	dSlope; 
		WorldCoord	dProjection, dEaveHeight;

		if ( ::GS_GetRoofEdge( gCBP, fhObject, index, pt, dSlope, dProjection, dEaveHeight ) ) {
			fEdgesPolygon.AddVertex( pt );
		}
	}

	// get the first item in the group
	MCObjectHandle	hItem			= ::GS_FirstMemberObj( gCBP, fhObject );
	// go through all the items in the group
	while ( hItem )	{
		// get the inner item type
		short	type	= gSDK->GetObjectTypeN( hItem );
		if ( type == kSlabNode ) {
			// add this face to the roof
			fArrFaces.push_back( hItem );
		}
	
		// ... and go to the next item
		hItem	= ::GS_NextObject( gCBP, hItem );
	}
}

VWRoofObj::~VWRoofObj()
{
}

VWRoofObj::VWRoofObj(const VWRoofObj& )
{
	VWFC_ASSERT( FALSE );
}

VWRoofObj& VWRoofObj::operator=(const VWRoofObj&)
{
	VWFC_ASSERT( FALSE );
	return *this;
}

const VWPolygon2D& VWRoofObj::GetRoofPoly() const
{
	return fEdgesPolygon;
}

size_t VWRoofObj::GetFacesCount() const
{
	return fArrFaces.size();
}

MCObjectHandle VWRoofObj::GetFaceAt(size_t at)
{
	VWFC_ASSERT( at < fArrFaces.size() );
	return fArrFaces[ at ];
}

bool VWRoofObj::GetIsFaceDormer(size_t at)
{
	VWFC_ASSERT( at < fArrFaces.size() );
	VWRoofFaceObj	faceObj( fArrFaces[ at ] );

	bool	bIsDormer		= false;
	// dont be too exact
	if (	  fEdgesPolygon.IsPtInPoly2D( faceObj.fBearingLine.GetStart(), 1 ) &&
			! fEdgesPolygon.IsPtOnPoly2D( faceObj.fBearingLine.GetStart(), 1 ) &&
			  fEdgesPolygon.IsPtInPoly2D( faceObj.fBearingLine.GetEnd(), 1 ) &&
			! fEdgesPolygon.IsPtOnPoly2D( faceObj.fBearingLine.GetEnd(), 1 ) )
	{
		bIsDormer	= true;
	}

	return bIsDormer;
}

bool VWRoofObj::IsRoofFaceDormer(MCObjectHandle hRoofFace)
{
	bool	bIsDormer	= false;
	size_t	len			= fArrFaces.size();
	for(size_t i=0; i<len; i++) {
		MCObjectHandle	hFace	= fArrFaces[ i ];
		if ( hRoofFace == hFace ) {
			bIsDormer	= this->GetIsFaceDormer( i );
			break;
		}
	}

	return bIsDormer;
}

bool VWRoofObj::GetGableWall() const
{
	return fbGenGableWall;
}

double VWRoofObj::GetBearingInset() const
{
	return fdBearingInset;
}

double VWRoofObj::GetRoofThick() const
{
	return fdRoofThick;
}

ERoofMiterType VWRoofObj::GetMiterType() const
{
	return fMiterType;
}

double VWRoofObj::GetVertMiter() const
{
	return fdVertMiter;
}

ERoofMiterType VWRoofObj::GetSkylightMiterType() const
{
	return fSkylightMiterType;
}

bool VWRoofObj::IsRoofObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kRoofContainerNode;
}