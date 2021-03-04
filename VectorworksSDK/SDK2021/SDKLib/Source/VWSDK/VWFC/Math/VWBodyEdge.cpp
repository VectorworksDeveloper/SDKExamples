//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "Interfaces/VectorWorks/IParasolidKernel.h"

using namespace VWFC::Math;

VWBodyEdge::VWBodyEdge()
{
	fp		= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );

	fBodyEdgeID	= 0;
}

VWBodyEdge::VWBodyEdge(Sint32 edgeID)
{
	fp			= NULL;
	fBodyEdgeID = 0;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );

	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kBiplab, !PK_ENTITY_is(edgeID, &isEntity));

	if (isEntity == PK_LOGICAL_true) 
		fBodyEdgeID	= edgeID;
}

VWBodyEdge::VWBodyEdge(const VWBodyEdge& src)
{
	fp			= NULL;
	fBodyEdgeID = 0;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );

	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kBiplab, !PK_ENTITY_is(src.fBodyEdgeID, &isEntity));

	if (isEntity == PK_LOGICAL_true) 
		fBodyEdgeID	= src.fBodyEdgeID;
}

VWBodyEdge::~VWBodyEdge()
{
	if ( fp ) {
		fp->Release();
		fp	= NULL;
	}
}

VWBodyEdge& VWBodyEdge::operator=(const VWBodyEdge& src)
{
	fBodyEdgeID	= src.fBodyEdgeID;
	return *this;
}

bool VWBodyEdge::IsValid() const
{
	return fBodyEdgeID != 0;
}

Sint32 VWBodyEdge::GetBodyEdgeID() const
{
	return fBodyEdgeID;
}

void VWBodyEdge::SetBodyEdgeID(Sint32 id)
{
	fBodyEdgeID	= id;
}

VWNURBSCurve VWBodyEdge::GetEdgeCurve()
{
	if (fp) {
		if (fBodyEdgeID != PK_ENTITY_null) {
			PK_LOGICAL_t wantInterval = true;
			PK_VECTOR_t ends[2];
			PK_CURVE_t curve = PK_ENTITY_null;
			PK_CLASS_t curveClass;
			PK_LOGICAL_t sense;
			PK_INTERVAL_t paramInterval;
			PK_ERROR_code_t error = PK_ERROR_no_errors;

			error = PK_EDGE_ask_geometry(fBodyEdgeID, wantInterval, &curve, &curveClass, ends, &paramInterval, &sense);
			if (error == PK_ERROR_no_errors && curve != PK_ENTITY_null) {
				if (sense == PK_LOGICAL_false) {
					PK_CURVE_t newCurve = PK_ENTITY_null;
					VERIFYN(kBiplab, !PK_CURVE_make_curve_reversed(curve, &newCurve));
					VERIFYN(kBiplab, !PK_CURVE_find_vector_interval(newCurve, ends[1], ends[0], &paramInterval));
					VWNURBSCurve nurbsCurve(newCurve);
					nurbsCurve.SetStartParameter(paramInterval.value[0]);
					nurbsCurve.SetEndParameter(paramInterval.value[1]);
					return nurbsCurve;
				}
				else {
					VWNURBSCurve nurbsCurve(curve);
					nurbsCurve.SetStartParameter(paramInterval.value[0]);
					nurbsCurve.SetEndParameter(paramInterval.value[1]);
					return nurbsCurve;
				}
			}
		}
	}

	return VWNURBSCurve(0);
}
