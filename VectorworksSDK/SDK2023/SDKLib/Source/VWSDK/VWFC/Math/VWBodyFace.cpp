//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "Interfaces/VectorWorks/IParasolidKernel.h"

using namespace VWFC::Math;

VWBodyFace::VWBodyFace()
{
	fp		= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );

	fBodyFaceID	= 0;
}

VWBodyFace::VWBodyFace(Sint32 faceID)
{
	fBodyFaceID = 0;
	fp			= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );

	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kBiplab, !PK_ENTITY_is(faceID, &isEntity));

	if (isEntity == PK_LOGICAL_true) 
		fBodyFaceID	= faceID;
}

VWBodyFace::VWBodyFace(const VWBodyFace& src)
{
	fBodyFaceID = 0;
	fp			= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );

	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kBiplab, !PK_ENTITY_is(src.fBodyFaceID, &isEntity));

	if (isEntity == PK_LOGICAL_true) 
		fBodyFaceID	= src.fBodyFaceID;
}

VWBodyFace::~VWBodyFace()
{
	if ( fp ) {
		fp->Release();
		fp	= NULL;
	}
}

VWBodyFace& VWBodyFace::operator=(const VWBodyFace& src)
{
	fBodyFaceID	= src.fBodyFaceID;
	return *this;
}

bool VWBodyFace::IsValid() const
{
	return fBodyFaceID != 0;
}

Sint32 VWBodyFace::GetBodyFaceID() const
{
	return fBodyFaceID;
}

void VWBodyFace::SetBodyFaceID(Sint32 id)
{
	fBodyFaceID	= id;
}

VWBody VWBodyFace::GetBody() const
{
	if (fp)
	{
		if (fBodyFaceID != PK_ENTITY_null) {
			PK_BODY_t body = PK_ENTITY_null;
			VERIFYN(kSPrabu, !PK_FACE_ask_body(fBodyFaceID, &body));
			if (body != PK_ENTITY_null)
			{
				return VWBody(body);
			}
		}
		
	}
	return VWBody(0);
}

bool VWBodyFace::GetPlanarSurface(VWPoint3D& outPlaneLocation, VWPoint3D& outPlaneNormal)
{
	if (fp) {
		if (fBodyFaceID != PK_ENTITY_null) {
			PK_SURF_t surface = PK_ENTITY_null;
			PK_LOGICAL_t faceSense = PK_LOGICAL_false;
			VERIFYN(kBiplab, !PK_FACE_ask_oriented_surf(fBodyFaceID, &surface, &faceSense));

			if (surface == PK_ENTITY_null)
				return false; // rubber face

			// check if the surface is a planar surface
			PK_ENTITY_t actualClass = PK_ENTITY_null;
			VERIFYN(kBiplab, !PK_ENTITY_ask_class(surface, &actualClass));
			if (actualClass != PK_CLASS_plane) {
				PK_LOGICAL_t verdict = PK_LOGICAL_false;
				VERIFYN(kBiplab, !PK_CLASS_is_subclass(actualClass, PK_CLASS_plane, &verdict));
				if (verdict == PK_LOGICAL_false)
					return false;  // not planar
			}

			// get data from plane
			PK_PLANE_sf_t planeSF;
			VERIFYN(kBiplab, !PK_PLANE_ask(surface, &planeSF));

			PK_VECTOR_t location = planeSF.basis_set.location;
			outPlaneLocation = VWPoint3D(location.coord[0]*10000, location.coord[1]*10000, location.coord[2]*10000);

			PK_VECTOR_t normal = planeSF.basis_set.axis;
			if (faceSense == PK_LOGICAL_false) {
				normal.coord[0] *= -1;
				normal.coord[1] *= -1;
				normal.coord[2] *= -1;
			}
			
			outPlaneNormal = VWPoint3D(normal.coord[0], normal.coord[1], normal.coord[2]);
		}
	}

	return false;
}

bool VWBodyFace::GetPlanarSurface(VWPlane& out)
{
	if (fp) {
		if (fBodyFaceID != PK_ENTITY_null) {
			PK_SURF_t surface = PK_ENTITY_null;
			PK_LOGICAL_t faceSense = PK_LOGICAL_false;
			VERIFYN(kBiplab, !PK_FACE_ask_oriented_surf(fBodyFaceID, &surface, &faceSense));

			if (surface == PK_ENTITY_null)
				return false; // rubber face

			// check if the surface is a planar surface
			PK_ENTITY_t actualClass = PK_ENTITY_null;
			VERIFYN(kBiplab, !PK_ENTITY_ask_class(surface, &actualClass));
			if (actualClass != PK_CLASS_plane) {
				PK_LOGICAL_t verdict = PK_LOGICAL_false;
				VERIFYN(kBiplab, !PK_CLASS_is_subclass(actualClass, PK_CLASS_plane, &verdict));
				if (verdict == PK_LOGICAL_false)
					return false;  // not planar
			}

			// get data from plane
			PK_PLANE_sf_t planeSF;
			VERIFYN(kBiplab, !PK_PLANE_ask(surface, &planeSF));

			PK_VECTOR_t location = planeSF.basis_set.location;
			WorldPt3 planeLocation = VWPoint3D(location.coord[0]*10000, location.coord[1]*10000, location.coord[2]*10000);

			PK_VECTOR_t normal = planeSF.basis_set.axis;
			if (faceSense == PK_LOGICAL_false) {
				normal.coord[0] *= -1;
				normal.coord[1] *= -1;
				normal.coord[2] *= -1;
			}
			
			WorldPt3 planeNormal = VWPoint3D(normal.coord[0], normal.coord[1], normal.coord[2]);

			out.SetPlane(planeLocation, planeNormal);
		}
	}

	return true;
}

VWNURBSSurface VWBodyFace::GetSurface()
{
	if (fp) 
	{
		if (fBodyFaceID != PK_ENTITY_null) 
		{
			PK_SURF_t surface = PK_ENTITY_null;			
			VERIFYN(kBiplab, !PK_FACE_ask_surf(fBodyFaceID, &surface));

			if (surface != PK_ENTITY_null)
			{
				return VWNURBSSurface( surface );
			}
		}
	}
	return VWNURBSSurface(0);
}

VWNURBSCurve VWBodyFace::GetIsoCurveU( double param )
{
	if(fp)
	{
		PK_LOGICAL_t wasError;
		PK_ERROR_sf_t errorSF;
		PK_ERROR_code_t error = PK_ERROR_no_errors;
		PK_SURF_t surface;
		VERIFYN(kMFlamer, !PK_FACE_ask_surf(fBodyFaceID, &surface));
		PK_UVBOX_t uvBox;
		VERIFYN(kMFlamer, !PK_SURF_ask_uvbox( surface, &uvBox ));
		param = max( param, uvBox.param[0] );//change for V!!
		param = min( param, uvBox.param[2] );
		PK_PARAM_direction_t crvDir = PK_PARAM_direction_u_c;//change for V!!
		PK_SURF_make_curve_isoparam_o_t options;
		PK_SURF_make_curve_isoparam_o_m(options);
		options.want_interval = PK_LOGICAL_true;
		options.preferred_curve_type =  PK_isoparam_prefer_simple_c ;

		PK_CURVE_t curve;
		PK_INTERVAL_t interval;
		PK_FACE_t face = fBodyFaceID;

		error = PK_SURF_make_curve_isoparam(surface, param, crvDir, &options, &curve, &interval);
		error = PK_ERROR_ask_last( &wasError, &errorSF );

	/*	PK_LOGICAL_t m_generalTopology;
		PK_SESSION_ask_general_topology(&m_generalTopology);
		PK_SESSION_set_general_topology(PK_LOGICAL_true);
		PK_BODY_t sheetBody;
		error = PK_FACE_make_sheet_body(1, &face, &sheetBody);

		PK_BODY_imprint_cus_normal_o_t imprintOptions;
		PK_BODY_imprint_cus_normal_o_m(imprintOptions);
		PK_TOPOL_track_r_t tracking;
		const double resabs = 1e-6;
		error = PK_BODY_imprint_cus_normal(sheetBody, 1, &curve, &interval, resabs * 100, &imprintOptions, &tracking);*/

		PK_FACE_imprint_cus_normal_o_t opts;
		PK_FACE_imprint_cus_normal_o_m(opts);
		opts.imprint_coi_exactly = PK_LOGICAL_true;
		PK_TOPOL_track_r_t tracking;
		error = PK_FACE_imprint_cus_normal(1, &face, 1, &curve, &interval, 0.0001, &opts, &tracking);

		
		


	
		

		/*PK_SESSION_set_general_topology(m_generalTopology);*/
	
		if(!error)
		{
			PK_TOPOL_track_record_r_t trackRecord = tracking.track_records[0];

			PK_TOPOL_t topol = trackRecord.product_topols[0];
		
			PK_ENTITY_t pkClass;
			VERIFYN(kMFlamer, !PK_ENTITY_ask_class(topol, &pkClass));
		
			if (pkClass == PK_CLASS_edge) 
			{
				PK_LOGICAL_t wantInterval = true;
				PK_VECTOR_t ends[2];
				PK_CURVE_t curve = PK_ENTITY_null;
				PK_CLASS_t curveClass;
				PK_LOGICAL_t sense;
				PK_INTERVAL_t paramInterval;
			
				VERIFYN(kMFlamer, !PK_EDGE_ask_geometry(topol, wantInterval, &curve, &curveClass, ends, &paramInterval, &sense));
				VWNURBSCurve VWCurve(curve);
				VWCurve.SetStartParameter(paramInterval.value[0]);
				VWCurve.SetEndParameter(paramInterval.value[1]);
				return VWCurve;
			}
		}
	}
	return VWNURBSCurve();		
}

VWNURBSCurve VWBodyFace::GetIsoCurveV( double param )
{
	
	return VWNURBSCurve();
		
}

void VWBodyFace::GetUVBox(VWPoint2D& UVMin, VWPoint2D& UVMax)
{
	PK_UVBOX_t box;
	VERIFYN(kMFlamer, !PK_FACE_find_uvbox(fBodyFaceID, &box));
	UVMin.SetPoint( box.param[0], box.param[1] );
	UVMax.SetPoint( box.param[2], box.param[3] );
}
