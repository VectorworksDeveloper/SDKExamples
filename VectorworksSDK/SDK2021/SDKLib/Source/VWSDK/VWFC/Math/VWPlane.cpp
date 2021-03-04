//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "Interfaces/VectorWorks/IParasolidKernel.h"

using namespace VWFC::Math;

VWPlane::VWPlane()
{
	fp		= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );

	fPlaneLocation = VWPoint3D(0, 0, 0);
	fPlaneNormal = VWPoint3D(0, 0, 0);
}

VWPlane::VWPlane(const VWPoint3D& planeLocation, const VWPoint3D& planeNormal)
{
	fp			= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );

	fPlaneLocation = planeLocation;
	fPlaneNormal = planeNormal;
}

VWPlane::VWPlane(const VWPlane& src)
{
	fp		= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	
	fPlaneLocation = src.fPlaneLocation;
	fPlaneNormal = src.fPlaneNormal;
}

VWPlane::~VWPlane()
{
	if ( fp ) {
		fp->Release();
		fp	= NULL;
	}
}

VWPlane& VWPlane::operator=(const VWPlane& src)
{
	fPlaneLocation = src.fPlaneLocation;
	fPlaneNormal = src.fPlaneNormal;
	return *this;
}

void VWPlane::SetPlane(const VWPoint3D& planeLocation, const VWPoint3D& planeNormal)
{
	fPlaneLocation = planeLocation;
	fPlaneNormal = planeNormal;
}

VWPoint3D VWPlane::GetLocation()
{
	return fPlaneLocation;
}

VWPoint3D VWPlane::GetNormal()
{
	return fPlaneNormal;
}

VWPoint3D GetPerpendicular(const VWPoint3D &normal)
{
	ASSERTN(kBiplab, normal.MagnitudeSquared() >= 1e-6*1e-6);

	VWPoint3D zAxis(0, 0, 1);
	VWPoint3D yAxis(0, 1, 0);

	VWPoint3D result = zAxis.Cross(normal);
	double length = result.Magnitude();
	if (length >= 1e-6) 
		return result/length;

	return yAxis.Cross(normal);
}

bool VWPlane::IntersectPWithVector(const VWPoint3D& pt, const VWPoint3D& dir, VWPoint3D& outInters)
{
	bool result = false;

	if (fp) {
		// create parasolid line
		PK_VECTOR_t point = {{pt.x/10000, pt.y/10000, pt.z/10000}};
		PK_VECTOR_t direction = {{dir.x, dir.y, dir.z}};
		PK_VECTOR1_t axis;
		VERIFYN(kBiplab, !PK_VECTOR_normalise(direction, &axis));
		PK_AXIS1_sf_t lineData;
		lineData.location = point;
		lineData.axis = axis;
		PK_LINE_sf_t line_sf;
		line_sf.basis_set = lineData;
		PK_LINE_t line = PK_ENTITY_null;
		VERIFYN(kBiplab, !PK_LINE_create(&line_sf, &line));
		if (line == PK_ENTITY_null)
			return result;

		PK_INTERVAL_t lineInterval;
		lineInterval.value[0] = -5000;  // infinite line
		lineInterval.value[1] = 5000;

		// create a parasolid plane
		fPlaneNormal.Normalize();
		VWPoint3D refDir = GetPerpendicular(fPlaneNormal);
		PK_VECTOR_t location = {{fPlaneLocation.x/10000, fPlaneLocation.y/10000, fPlaneLocation.z/10000}};
		PK_PLANE_sf_t stdForm;
		stdForm.basis_set.location = location;
		stdForm.basis_set.axis.coord[0] = fPlaneNormal.x;
		stdForm.basis_set.axis.coord[1] = fPlaneNormal.y;
		stdForm.basis_set.axis.coord[2] = fPlaneNormal.z;
		stdForm.basis_set.ref_direction.coord[0] = refDir.x;
		stdForm.basis_set.ref_direction.coord[1] = refDir.y;
		stdForm.basis_set.ref_direction.coord[2] = refDir.z;
		PK_PLANE_t plane = PK_ENTITY_null;
		VERIFYN(kBiplab, !PK_PLANE_create(&stdForm, &plane));

		if (plane == PK_ENTITY_null)
			return result;

		// compute the intersection
		Sint32						n_vectors = 0;
		PK_VECTOR_t*			vectors = NULL;
		PK_UV_t*				uvs = NULL;
		double*					ts = NULL;
		PK_intersect_vector_t*	types = NULL;
		PK_ERROR_code_t			error = PK_ERROR_no_errors;

		PK_SURF_intersect_curve_o_t options;
		PK_SURF_intersect_curve_o_m(options);
		
		error = PK_SURF_intersect_curve(plane, line, lineInterval, &options, &n_vectors, &vectors, &uvs, &ts, &types);
		if (error == PK_ERROR_no_errors && n_vectors == 1) {
			PK_VECTOR_t v = vectors[0];
			outInters.x = v.coord[0] * 10000;
			outInters.y = v.coord[1] * 10000;
			outInters.z = v.coord[2] * 10000;
			result = true;
		}

		if (vectors)
			PK_MEMORY_free(vectors);
		if (uvs)
			PK_MEMORY_free(uvs);
		if (ts)
			PK_MEMORY_free(ts);
		if (types)
			PK_MEMORY_free(types);
		
		PK_ENTITY_delete(1, &line);
		PK_ENTITY_delete(1, &plane);
	}

	return result;
}


