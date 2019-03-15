//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "Interfaces/VectorWorks/IParasolidKernel.h"


using namespace VWFC::Math;


VWNURBSSurface::VWNURBSSurface()
{
	fNURBSSurfaceID	= 0;
	fUVBoundsMin.SetPoint(0, 0);
	fUVBoundsMax.SetPoint(1, 1);
	fp				= NULL;
	fpAPI			= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );
}

VWNURBSSurface::VWNURBSSurface(Sint32 surfaceID)
{
	fp				= NULL;
	fpAPI			= NULL;
	fNURBSSurfaceID	= 0;
	fUVBoundsMin.SetPoint(0, 0);
	fUVBoundsMax.SetPoint(1, 1);

	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );

	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kMFlamer, !PK_ENTITY_is(surfaceID, &isEntity));

	if (isEntity == PK_LOGICAL_true) 
	{
		fNURBSSurfaceID	= surfaceID;
		PK_UVBOX_t box;
		//Sint32 numFaces = 0;
		//PK_FACE_t* faces; 
		/*VERIFYN(kMFlamer, !PK_SURF_ask_faces(fNURBSSurfaceID, &numFaces, &faces));
		if( numFaces )
		{
			VERIFYN(kMFlamer, !PK_FACE_find_uvbox(faces[0], &box));
			fUVBoundsMin.SetPoint( box.param[0], box.param[1] );
			fUVBoundsMax.SetPoint( box.param[2], box.param[3] );
		}
		else
		{*/
			VERIFYN(kMFlamer, !PK_SURF_ask_uvbox(fNURBSSurfaceID, &box));
			fUVBoundsMin.SetPoint( box.param[0], box.param[1] );
			fUVBoundsMax.SetPoint( box.param[2], box.param[3] );
		/*}
		if (faces) PK_MEMORY_free(faces);*/
	}
}

VWNURBSSurface::VWNURBSSurface(const VWNURBSSurface& src)
{
	fp				= NULL;
	fpAPI			= NULL;
	fNURBSSurfaceID	= 0;
	fUVBoundsMin.SetPoint(0, 0);
	fUVBoundsMax.SetPoint(1, 1);

	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );

	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kMFlamer, !PK_ENTITY_is(src.fNURBSSurfaceID, &isEntity));

	if (isEntity == PK_LOGICAL_true) {
		fNURBSSurfaceID	= src.fNURBSSurfaceID;
		fUVBoundsMin     = src.fUVBoundsMin;
		fUVBoundsMax     = src.fUVBoundsMax;
	}
}

VWNURBSSurface::~VWNURBSSurface()
{
	if ( fp ) {
		fp->Release();
		fp	= NULL;
	}
	if ( fpAPI ) {
		fpAPI->Release();
		fpAPI	= NULL;
	}
}

VWNURBSSurface& VWNURBSSurface::operator=(const VWNURBSSurface& src)
{
	fNURBSSurfaceID	= src.fNURBSSurfaceID;	
	fUVBoundsMin = src.fUVBoundsMin;
	fUVBoundsMax = src.fUVBoundsMax;	

	return *this;
}

void VWNURBSSurface::GetUVBox(VWPoint2D& UVMin, VWPoint2D& UVMax)
{
	UVMin = fUVBoundsMin;
	UVMax = fUVBoundsMax;
}

Sint32 VWNURBSSurface::GetVWNURBSSurfaceID()
{
	return fNURBSSurfaceID;
}

VWNURBSCurve VWNURBSSurface::GetIsoCurveU(double param)
{
	if(fp && fpAPI)
	{
		param = max( param, fUVBoundsMin.x );
		param = min( param, fUVBoundsMax.x );
		PK_PARAM_direction_t crvDir = PK_PARAM_direction_u_c;
		PK_SURF_make_curve_isoparam_o_t options;
		PK_SURF_make_curve_isoparam_o_m(options);
		options.want_interval = PK_LOGICAL_true;
		options.preferred_curve_type =  PK_isoparam_prefer_spcurve_c  ;


		PK_CURVE_t curve;
		PK_INTERVAL_t interval;
		PK_PARAM_sf_t paramData;

		VERIFYN(kMFlamer, !PK_SURF_make_curve_isoparam(fNURBSSurfaceID, param, crvDir, &options, &curve, &interval));		
		VERIFYN(kMFlamer, !PK_CURVE_ask_param( curve, &paramData ));


		VWNURBSCurve VWCurve(curve);
		VWCurve.SetStartParameter( interval.value[0] );
		VWCurve.SetEndParameter( interval.value[1] );

		return VWCurve;
	}

	return VWNURBSCurve(0);
}

VWNURBSCurve VWNURBSSurface::GetIsoCurveV(double param)
{
	if(fp && fpAPI)
	{
		param = max( param, fUVBoundsMin.y );
		param = min( param, fUVBoundsMax.y );

		PK_PARAM_direction_t crvDir = PK_PARAM_direction_v_c;
		PK_SURF_make_curve_isoparam_o_t options;
		PK_SURF_make_curve_isoparam_o_m(options);
		options.want_interval = PK_LOGICAL_true;
		options.preferred_curve_type =  PK_isoparam_prefer_spcurve_c;

		PK_CURVE_t curve;
		PK_INTERVAL_t interval;
		PK_PARAM_sf_t paramData;

		VERIFYN(kMFlamer, !PK_SURF_make_curve_isoparam(fNURBSSurfaceID, param, crvDir, &options, &curve, &interval));		
		VERIFYN(kMFlamer, !PK_CURVE_ask_param( curve, &paramData ));


		VWNURBSCurve VWCurve(curve);
		VWCurve.SetStartParameter( interval.value[0] );
		VWCurve.SetEndParameter( interval.value[1] );

		return VWCurve;
	}

	return VWNURBSCurve(0);
}

bool VWNURBSSurface::GetEvenlySpacedPointsArc(Sint32 UDivs, Sint32 VDivs, double UOffsetDist, double VOffsetDist, TVWPoint3DArray& points)
{
	if(fp)
	{
		TDoubleArray UAvgParams(UDivs + 1);
		TDoubleArray VAvgParams(VDivs + 1);
		TDoubleArray UEqParams(UDivs + 1);
		TDoubleArray VEqParams(VDivs + 1);
		TDoubleArray tempParams(Max<Sint32>(UDivs + 1, VDivs + 1));
		double crvUParamStep = (fUVBoundsMax.x - fUVBoundsMin.x) / UDivs;
		double crvUParam = 0;
		double crvVParamStep = (fUVBoundsMax.y - fUVBoundsMin.y) / VDivs;
		double crvVParam = 0;
		Sint32 i, j;
		bool ok;
			

		points.resize( UDivs + 1 * VDivs + 1 );

		//Get average V parameters at uniform U's// 

		for(i = 0; i <= UDivs; i++)
		{
			VWNURBSCurve isoCrv(this->GetIsoCurveU( crvUParam ));
			ok = isoCrv.GetEvenlySpacedPointsArc( VDivs, VOffsetDist, points, tempParams );

			for(j = 1; j < VDivs; j++) VAvgParams[j] += tempParams[j];

			crvUParam += crvUParamStep;
			
			Sint32 ID = isoCrv.GetVWNURBSCurveID();
			PK_CURVE_t* crv = &ID;
			VERIFYN(kMFlamer, !PK_ENTITY_delete(1, crv));				
		}

		VAvgParams[0] = tempParams[0];
		VAvgParams[VDivs] = tempParams[VDivs];

		for(j = 1; j < VDivs; j++) VAvgParams[j] /= (UDivs + 1);

		//Get average U parameters at uniform V's// 

		for(i = 0; i <= VDivs; i++)
		{
			VWNURBSCurve isoCrv(this->GetIsoCurveV( crvVParam ));
			ok = isoCrv.GetEvenlySpacedPointsArc( UDivs, UOffsetDist, points, tempParams );

			for(j = 1; j < UDivs; j++) UAvgParams[j] += tempParams[j];

			crvVParam += crvVParamStep;

			Sint32 ID = isoCrv.GetVWNURBSCurveID();
			PK_CURVE_t* crv = &ID;
			VERIFYN(kMFlamer, !PK_ENTITY_delete(1, crv));	

		}

		UAvgParams[0] = tempParams[0];
		UAvgParams[UDivs] = tempParams[UDivs];

		for(j = 1; j < UDivs; j++) UAvgParams[j] /= (VDivs + 1);

		//Get equally spaced points in V direction using average U's//

		for(i = 0; i <= UDivs; i++)
		{
			VWNURBSCurve isoCrv(this->GetIsoCurveU( UAvgParams[i]));
			ok = isoCrv.GetEvenlySpacedPointsArc( VDivs, VOffsetDist, points, tempParams );

			for(j = 1; j < VDivs; j++) VEqParams[j] += tempParams[j];				

			Sint32 ID = isoCrv.GetVWNURBSCurveID();
			PK_CURVE_t* crv = &ID;
			VERIFYN(kMFlamer, !PK_ENTITY_delete(1, crv));	
		}

		VEqParams[0] = tempParams[0];
		VEqParams[VDivs] = tempParams[VDivs];

		for(j = 1; j < VDivs; j++) VEqParams[j] /= (UDivs + 1);

		//Get equally spaced points in U direction using average V's//

		for(i = 0; i <= VDivs; i++)
		{
			VWNURBSCurve isoCrv(this->GetIsoCurveV( VAvgParams[i]));
			ok = isoCrv.GetEvenlySpacedPointsArc( UDivs, UOffsetDist, points, tempParams );

			for(j = 1; j < UDivs; j++) UEqParams[j] += tempParams[j];				

			Sint32 ID = isoCrv.GetVWNURBSCurveID();
			PK_CURVE_t* crv = &ID;
			VERIFYN(kMFlamer, !PK_ENTITY_delete(1, crv));	
		}

		UEqParams[0] = tempParams[0];
		UEqParams[UDivs] = tempParams[UDivs];

		for(j = 1; j < UDivs; j++) UEqParams[j] /= (VDivs + 1);

		this->GetPointsOnUVGrid( UEqParams, VEqParams, points );

		return true;
	}

	return false;
}

bool VWNURBSSurface::GetEvenlySpacedPointsChord(Sint32 UDivs, Sint32 VDivs, double UOffsetDist, double VOffsetDist, TVWPoint3DArray& points)
{
	if(fp)
	{
		TDoubleArray UAvgParams(UDivs + 1);
		TDoubleArray VAvgParams(VDivs + 1);
		TDoubleArray UEqParams(UDivs + 1);
		TDoubleArray VEqParams(VDivs + 1);
		TDoubleArray tempParams(Max<Sint32>(UDivs + 1, VDivs + 1));
		TDoubleArray tempDist(Max<Sint32>(UDivs + 1, VDivs + 1));
		double crvUParamStep = (fUVBoundsMax.x - fUVBoundsMin.x) / UDivs;
		double crvUParam = 0;
		double crvVParamStep = (fUVBoundsMax.y - fUVBoundsMin.y) / VDivs;
		double crvVParam = 0;
		Sint32 i, j;
		bool ok;
			

		points.resize( UDivs + 1 * VDivs + 1 );

		//Get average V parameters at uniform U's// 

		for(i = 0; i <= UDivs; i++)
		{
			VWNURBSCurve isoCrv(this->GetIsoCurveU( crvUParam ));
			ok = isoCrv.GetEvenlySpacedPointsChord( VDivs, 50, points, tempParams, tempDist );

			for(j = 1; j < VDivs; j++) VAvgParams[j] += tempParams[j];

			crvUParam += crvUParamStep;
			
			Sint32 ID = isoCrv.GetVWNURBSCurveID();
			PK_CURVE_t* crv = &ID;
			VERIFYN(kMFlamer, !PK_ENTITY_delete(1, crv));				
		}

		VAvgParams[0] = tempParams[0];
		VAvgParams[VDivs] = tempParams[VDivs];

		for(j = 1; j < VDivs; j++) VAvgParams[j] /= (UDivs + 1);

		//Get average U parameters at uniform V's// 

		for(i = 0; i <= VDivs; i++)
		{
			VWNURBSCurve isoCrv(this->GetIsoCurveV( crvVParam ));
			ok = isoCrv.GetEvenlySpacedPointsChord( UDivs, 50, points, tempParams, tempDist );

			for(j = 1; j < UDivs; j++) UAvgParams[j] += tempParams[j];

			crvVParam += crvVParamStep;

			Sint32 ID = isoCrv.GetVWNURBSCurveID();
			PK_CURVE_t* crv = &ID;
			VERIFYN(kMFlamer, !PK_ENTITY_delete(1, crv));	

		}

		UAvgParams[0] = tempParams[0];
		UAvgParams[UDivs] = tempParams[UDivs];

		for(j = 1; j < UDivs; j++) UAvgParams[j] /= (VDivs + 1);

		//Get equally spaced points in V direction using average U's//

		for(i = 0; i <= UDivs; i++)
		{
			VWNURBSCurve isoCrv(this->GetIsoCurveU( UAvgParams[i]));
			ok = isoCrv.GetEvenlySpacedPointsChord( VDivs, 50, points, tempParams, tempDist );

			for(j = 1; j < VDivs; j++) VEqParams[j] += tempParams[j];				

			Sint32 ID = isoCrv.GetVWNURBSCurveID();
			PK_CURVE_t* crv = &ID;
			VERIFYN(kMFlamer, !PK_ENTITY_delete(1, crv));	
		}

		VEqParams[0] = tempParams[0];
		VEqParams[VDivs] = tempParams[VDivs];

		for(j = 1; j < VDivs; j++) VEqParams[j] /= (UDivs + 1);

		//Get equally spaced points in U direction using average V's//

		for(i = 0; i <= VDivs; i++)
		{
			VWNURBSCurve isoCrv(this->GetIsoCurveV( VAvgParams[i]));
			ok = isoCrv.GetEvenlySpacedPointsChord( UDivs, 50, points, tempParams, tempDist );

			for(j = 1; j < UDivs; j++) UEqParams[j] += tempParams[j];				

			Sint32 ID = isoCrv.GetVWNURBSCurveID();
			PK_CURVE_t* crv = &ID;
			VERIFYN(kMFlamer, !PK_ENTITY_delete(1, crv));	
		}

		UEqParams[0] = tempParams[0];
		UEqParams[UDivs] = tempParams[UDivs];

		for(j = 1; j < UDivs; j++) UEqParams[j] /= (VDivs + 1);

		this->GetPointsOnUVGrid( UEqParams, VEqParams, points );

		return true;
	}

	return false;
}

bool VWNURBSSurface::GetPointsOnUVGrid(Sint32 UDivs, Sint32 VDivs, double UOffsetDist, double VOffsetDist, TVWPoint3DArray& points)
{
	bool result = false;
	if(fp && fpAPI)
	{		
		PK_LOGICAL_t triangular = PK_LOGICAL_false;
		double UParamStep =	(fUVBoundsMax.x - fUVBoundsMin.x) / UDivs;
		double UParam = fmod( UOffsetDist, UParamStep);
		double VParamStep = (fUVBoundsMax.y - fUVBoundsMin.y) / VDivs;
		double VParam =fmod( VOffsetDist, VParamStep);
		double* UParams = SDK_NEW double[UDivs + 1]; //-V121
		double* VParams = SDK_NEW double[VDivs + 1]; //-V121
		Sint32 arraySize = (UDivs + 1) * (VDivs + 1);

		for(Sint32 i = 0; i <= UDivs; i++)
		{
			UParams[i] = UParam;
			UParam += UParamStep;
		}

		for(Sint32 i = 0; i <= VDivs; i++)
		{
			VParams[i] = VParam;
			VParam += VParamStep;
		}		
	
		PK_VECTOR_t* outVecs = SDK_NEW PK_VECTOR_t[arraySize];			 //-V121

		VERIFYN(kMFlamer, !PK_SURF_eval_grid(fNURBSSurfaceID, UDivs + 1, UParams, VDivs + 1, VParams, 0, 0, triangular, outVecs));

		points.clear();		

		for(Sint32 i = 0; i < arraySize; i++)
		{				
			points.push_back(VWPoint3D(((IParasolidVWAPI *)fpAPI)->PKVecToWorldPt3( outVecs[i] )));				
		}

		delete[] outVecs;
		delete[] UParams;
		delete[] VParams;
		result = true;
	}
	return result;
}

bool VWNURBSSurface::GetPointsOnUVGrid(TDoubleArray& UParams, TDoubleArray& VParams, TVWPoint3DArray& points)
{
	bool result = false;
	if(fp && fpAPI)
	{		
		PK_LOGICAL_t triangular = PK_LOGICAL_false;
		Sint32 USize = (Sint32)UParams.size();
		Sint32 VSize = (Sint32)VParams.size();
		Sint32 arraySize = USize * VSize;
		PK_VECTOR_t* outVecs = SDK_NEW PK_VECTOR_t[arraySize];  //-V121
		double* UparamsP = &(UParams[0]);
		double* VparamsP = &(VParams[0]);		

		VERIFYN(kMFlamer, !PK_SURF_eval_grid(fNURBSSurfaceID, USize, UparamsP, VSize, VparamsP, 0, 0, triangular, outVecs));

		points.clear();		

		for(Sint32 i = 0; i < arraySize; i++)
		{				
			points.push_back(VWPoint3D(((IParasolidVWAPI *)fpAPI)->PKVecToWorldPt3( outVecs[i] )));				
		}

		delete[] outVecs;
		result = true;
	}
	return result;
}


