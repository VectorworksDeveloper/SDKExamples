//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWExtrudeObj::VWExtrudeObj(const VWPolygon2D& base, double dThickness)
{
	fbDeleteBasePoly	= false;
	fhObject			= ::GS_CreateExtrude( gCBP, 0, dThickness );
	fpBasePolyObj		= new VWPolygon2DObj( base );
	::GS_AddObjectToContainer( gCBP, *fpBasePolyObj, fhObject );

	VWFC_ASSERT( fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create extrude" );
}

VWExtrudeObj::VWExtrudeObj(const VWPolygon2D& base, double dBaseElevation, double dThickness)
{
	fbDeleteBasePoly	= false;
	fhObject			= ::GS_CreateExtrude( gCBP, dBaseElevation, dBaseElevation+dThickness );
	fpBasePolyObj		= new VWPolygon2DObj( base );
	::GS_AddObjectToContainer( gCBP, *fpBasePolyObj, fhObject );

	VWFC_ASSERT( fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create extrude" );
}

VWExtrudeObj::VWExtrudeObj(const VWPolygon3D& base, double dThickness)
{
	bool				bISCW			= base.IsClockWise();
	VWTransformMatrix	matrix;
	if ( bISCW ) {
		VWPolygon3D	baseCopy	= base;
		baseCopy.ReversePoints();
		matrix		= baseCopy.GetTransformMatrix();
	}
	else {
		matrix		= base.GetTransformMatrix();
	}

	VWPolygon2D			base2D;
	size_t				vertsCnt		= base.GetVertexCount();
	for(size_t i=0; i<vertsCnt; i++) {
		VWPoint3D	pt	= base.GetVertexAt( i );
		pt				= matrix.InversePointTransform( pt );
		base2D.AddVertex( pt.x, pt.y );
	}

	fbDeleteBasePoly	= false;
	fhObject			= ::GS_CreateExtrude( gCBP, 0, dThickness );
	fpBasePolyObj		= new VWPolygon2DObj ( base2D );
	::GS_AddObjectToContainer( gCBP, *fpBasePolyObj, fhObject );

	this->SetObjectMatrix( matrix );

	VWFC_ASSERT( fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "VWExtrudeObj::VWExtrudeObj : cannot create extrude" );
}

VWExtrudeObj::VWExtrudeObj(MCObjectHandle hBasePoly2D, double dBaseElevation, double dThickness)
{
	fbDeleteBasePoly	= false;
	fhObject			= ::GS_CreateExtrude( gCBP, dBaseElevation, dBaseElevation+dThickness );

	auto polygonize = [ & ] ( MCObjectHandle h )
	{
		return ( VWPolygon2DObj::IsPoly2DObject( h ) ) ? h : gSDK->ConvertToPolygon( h, false );
	};

	fpBasePolyObj		= new VWPolygon2DObj ( polygonize( hBasePoly2D ) );
	::GS_AddObjectToContainer( gCBP, *fpBasePolyObj, fhObject );

	VWFC_ASSERT( fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create extrude" );
}

VWExtrudeObj::VWExtrudeObj(MCObjectHandle hBasePoly2D, const VWPoint3D& start, const VWPoint3D& end)
{
	double len = start.DistanceTo(end);
	fbDeleteBasePoly	= false;
	fhObject			= ::GS_CreateExtrude( gCBP, 0, len );

	auto polygonize = [ & ] ( MCObjectHandle h )
	{
		return ( VWPolygon2DObj::IsPoly2DObject( h ) ) ? h : gSDK->ConvertToPolygon( h, false );
	};

	fpBasePolyObj		= new VWPolygon2DObj ( polygonize( hBasePoly2D ) );
	::GS_AddObjectToContainer( gCBP, *fpBasePolyObj, fhObject );	
	VWTransformMatrix mat;
	mat.SetOffset(start);
	VWPoint3D test = (end - start).GetNormalized();
	test.z = Abs(test.z);
	if(test != VWPoint3D(0,0,1))
	{
		mat.SetWVector((end - start).Normalize());
		mat.SetUVector(mat.GetWVector().Cross(VWPoint3D(0,0,1)).Normalize());
		mat.SetVVector(mat.GetWVector().Cross(mat.GetUVector()));
	}
	SetObjectMatrix(mat);
	ResetObject(fhObject);
	VWFC_ASSERT( fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create extrude" );
}

VWExtrudeObj::VWExtrudeObj(MCObjectHandle hBasePoly2D, const VWPoint3D& start, const VWPoint3D& end, const VWPoint3D& profileY)
{
	double len = start.DistanceTo(end);
	fbDeleteBasePoly	= false;
	fhObject			= ::GS_CreateExtrude( gCBP, 0, len );

	auto polygonize = [ & ] ( MCObjectHandle h )
	{
		return ( VWPolygon2DObj::IsPoly2DObject( h ) ) ? h : gSDK->ConvertToPolygon( h, false );
	};

	fpBasePolyObj		= new VWPolygon2DObj ( polygonize( hBasePoly2D ) );
	::GS_AddObjectToContainer( gCBP, *fpBasePolyObj, fhObject );	
	VWTransformMatrix mat;
	mat.SetOffset(start);
	VWPoint3D dir = (end - start).GetNormalized();	
	mat.SetWVector(dir);
	mat.SetUVector(profileY.Cross(dir).Normalize());
	mat.SetVVector(dir.Cross(mat.GetUVector()));	
	SetObjectMatrix(mat);
	ResetObject(fhObject);
	VWFC_ASSERT( fhObject != nil );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create extrude" );
}

VWExtrudeObj::VWExtrudeObj(MCObjectHandle hExtrude)
{
	VWFC_ASSERT( VWExtrudeObj::IsExtrudeObject( hExtrude ) );
	if ( ! VWExtrudeObj::IsExtrudeObject( hExtrude ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "VWExtrudeObj : bad handle type when creating" );
	fhObject		= hExtrude;
	VWFC_ASSERT( fhObject != nil );

	MCObjectHandle	hBasePoly	= ::GS_FirstMemberObj( gCBP, fhObject );
	if ( hBasePoly == NULL )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "VWExtrudeObj : bad base polygon object" );

	fbDeleteBasePoly		= false;
	if ( ! VWPolygon2DObj::IsPoly2DObject( hBasePoly ) ) {
		hBasePoly		= ::GS_ConvertToPolygon( gCBP, hBasePoly, true );
		fbDeleteBasePoly	= true;
	}

	fpBasePolyObj				= new VWPolygon2DObj ( hBasePoly );
}

VWExtrudeObj::VWExtrudeObj(const VWExtrudeObj& src)
{
	fbDeleteBasePoly	= false;
	fpBasePolyObj		= new VWPolygon2DObj ( *src.fpBasePolyObj );
	fhObject			= src.fhObject;
}

VWExtrudeObj::~VWExtrudeObj()
{
	if ( fbDeleteBasePoly ) {
		::GS_DeleteObject( gCBP, *fpBasePolyObj, false );
	}

	delete fpBasePolyObj;
	fpBasePolyObj = nullptr;
}

VWExtrudeObj& VWExtrudeObj::operator=(const VWExtrudeObj& src)
{
	delete fpBasePolyObj;
	fpBasePolyObj	= new VWPolygon2DObj ( *src.fpBasePolyObj );
	fhObject		= src.fhObject;
	return *this;
}

void VWExtrudeObj::AddHoleObject(const VWPolygon2D& poly)
{
	VWFC_ASSERT( fpBasePolyObj );
	if ( fpBasePolyObj == NULL )
		return;

	fpBasePolyObj->ConvertToPolyline();

	VWPolygon2DObj	holeObj( poly );
	holeObj.ConvertToPolyline();
	::GS_AttachAuxObject( gCBP, (MCObjectHandle) holeObj, *fpBasePolyObj );
}


void VWExtrudeObj::AddHoleObject(MCObjectHandle hObject)
{
	VWFC_ASSERT( fpBasePolyObj &&   VWPolygon2DObj::IsPoly2DObject( hObject ) );
	if ( fpBasePolyObj == NULL || ! VWPolygon2DObj::IsPoly2DObject( hObject ) )
		return;

	fpBasePolyObj->ConvertToPolyline();

	VWPolygon2DObj	holeObj( hObject );
	if ( ! VWPolygon2DObj::IsPolyline2DObject( hObject ) ) {
		holeObj.ConvertToPolyline();
	}
	::GS_AttachAuxObject( gCBP, (MCObjectHandle) holeObj, *fpBasePolyObj );
}

MCObjectHandle VWExtrudeObj::GetBaseObject() const
{
	VWFC_ASSERT( fpBasePolyObj );
	if ( fpBasePolyObj == NULL )
		return NULL;
	return *fpBasePolyObj;
}

void VWExtrudeObj::GetExtrudeValues(double& outBaseElev, double& outThickness) const
{
	WorldCoord bottom, top;
	::GS_GetExtrudeValues( gCBP, fhObject, bottom, top );

	outBaseElev		= bottom;
	outThickness	= top - bottom;
}

void VWExtrudeObj::SetExtrudeValues(double baseElev, double thickness)
{
	WorldCoord	bottom		= baseElev;
	WorldCoord	top			= baseElev + thickness;

	::GS_SetExtrudeValues( gCBP, fhObject, bottom, top );
}

void VWExtrudeObj::SetBaseElevation(double baseElev)
{
	WorldCoord bottom, top;
	::GS_GetExtrudeValues( gCBP, fhObject, bottom, top );

	double	thickness	= top - bottom;
	bottom				= baseElev;
	top					= baseElev + thickness;

	::GS_SetExtrudeValues( gCBP, fhObject, bottom, top );
}

double VWExtrudeObj::GetBaseElevation() const
{
	WorldCoord bottom, top;
	::GS_GetExtrudeValues( gCBP, fhObject, bottom, top );
	return (double) bottom;
}

void VWExtrudeObj::SetThickness(double thickness)
{
	WorldCoord bottom, top;
	::GS_GetExtrudeValues( gCBP, fhObject, bottom, top );

	top					= bottom + thickness;

	::GS_SetExtrudeValues( gCBP, fhObject, bottom, top );
}

double VWExtrudeObj::GetThickness() const
{
	WorldCoord bottom, top;
	::GS_GetExtrudeValues( gCBP, fhObject, bottom, top );
	return (double) top - bottom;
}

bool VWExtrudeObj::IsExtrudeObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN(hObj );
	return type == kExtrudeNode;
}
