//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "Interfaces/VectorWorks/IParasolidKernel.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWNURBSCurveObj::VWNURBSCurveObj()
{
	fpAPI			= NULL;
	fhObject		= NULL;
}

VWNURBSCurveObj::VWNURBSCurveObj(const VWNURBSCurve& curve)
{
	fpAPI			= NULL;
	fhObject		= NULL;

	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );

	if (fpAPI) {
		VWNURBSCurve *curveData = const_cast<VWNURBSCurve*>(&curve);
		Sint32 curveID = curveData->GetVWNURBSCurveID();
		double startParam = curveData->GetStartParameter();
		double endParam = curveData->GetEndParameter();
		// create nurbs curve handle
		PK_INTERVAL_t interval;
		interval.value[0] = startParam;
		interval.value[1] = endParam;
		fhObject = ((IParasolidVWAPI *)fpAPI)->CreateNURBSHandleFromParasolidCurve(curveID, interval);
	}
}

VWNURBSCurveObj::VWNURBSCurveObj(MCObjectHandle hObj)
{
	VWFC_ASSERT( VWNURBSCurveObj::IsNURBSCurveObject( hObj ) );
	if ( ! VWNURBSCurveObj::IsNURBSCurveObject( hObj ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hObj;
	VWFC_ASSERT( fhObject != nil );
}

VWNURBSCurveObj::VWNURBSCurveObj(const VWNURBSCurveObj& src)
{
	fhObject		= src.fhObject;
}

VWNURBSCurveObj::~VWNURBSCurveObj()
{
	fhObject		= nil;
	if ( fpAPI ) {
		fpAPI->Release();
		fpAPI	= NULL;
	}
}

VWNURBSCurveObj& VWNURBSCurveObj::operator=(const VWNURBSCurveObj& src)
{
	fhObject		= src.fhObject;
	return *this;
}

bool VWNURBSCurveObj::GetNURBSCurve(VWNURBSCurve& outCurve)
{
	return false;
}

bool VWNURBSCurveObj::IsNURBSCurveObject(MCObjectHandle hObj)
{
	short	type = gSDK->GetObjectTypeN( hObj );
	return type == kPieceWiseNurbsCurveNode;
}

