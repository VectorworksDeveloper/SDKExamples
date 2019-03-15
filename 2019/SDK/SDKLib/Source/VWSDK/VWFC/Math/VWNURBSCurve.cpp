//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"
#include "Interfaces/VectorWorks/IParasolidKernel.h"

using namespace VWFC::Math;

VWNURBSCurve::VWNURBSCurve()
{
	fNURBSCurveID	= 0;
	fStartParam		= 0;
	fEndParam		= 1;
	fp				= NULL;
	fpAPI			= NULL;
	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );
}

VWNURBSCurve::VWNURBSCurve(Sint32 curveID)
{
	fp				= NULL;
	fpAPI			= NULL;
	fNURBSCurveID	= 0;
	fStartParam		= 0;
	fEndParam		= 1;

	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );

	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kBiplab, !PK_ENTITY_is(curveID, &isEntity));

	if (isEntity == PK_LOGICAL_true) {
		fNURBSCurveID	= curveID;
		PK_INTERVAL_t interval;
		Sint32 numEdges;
		PK_EDGE_t* edges = NULL;
		VERIFYN(kMFlamer, !PK_CURVE_ask_edges(fNURBSCurveID, &numEdges, &edges));
		if(numEdges)
		{
			VERIFYN(kMFlamer, !PK_EDGE_find_interval(edges[0], &interval));
		}
		else VERIFYN(kBiplab, !PK_CURVE_ask_interval(fNURBSCurveID, &interval));
		fStartParam = interval.value[0];
		fEndParam = interval.value[1];
		
		if (edges) //memory leak: added 6/13 fabbasinejad
			PK_MEMORY_free(edges);
	}
}

VWNURBSCurve::VWNURBSCurve(const VWNURBSCurve& src)
{
	fp				= NULL;
	fpAPI			= NULL;
	fNURBSCurveID	= 0;
	fStartParam		= 0;
	fEndParam		= 1;

	::GS_VWQueryInterface( IID_ParasolidKernel, & fp );
	::GS_VWQueryInterface( IID_ParasolidVWAPI, & fpAPI );

	PK_LOGICAL_t isEntity = PK_LOGICAL_false;
	VERIFYN(kBiplab, !PK_ENTITY_is(src.fNURBSCurveID, &isEntity));

	if (isEntity == PK_LOGICAL_true) {
		fNURBSCurveID	= src.fNURBSCurveID;
		fStartParam     = src.fStartParam;
		fEndParam       = src.fEndParam;
	}
}

VWNURBSCurve::~VWNURBSCurve()
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

VWNURBSCurve& VWNURBSCurve::operator=(const VWNURBSCurve& src)
{
	fNURBSCurveID	= src.fNURBSCurveID;
	PK_INTERVAL_t interval;
	VERIFYN(kBiplab, !PK_CURVE_ask_interval(fNURBSCurveID, &interval));
	fStartParam = interval.value[0];
	fEndParam = interval.value[1];
	return *this;
}

void VWNURBSCurve::SetStartParameter(double startParam)
{
	if (fp) {
		if (fNURBSCurveID != PK_ENTITY_null) {
			PK_INTERVAL_t interval;
			VERIFYN(kBiplab, !PK_CURVE_ask_interval(fNURBSCurveID, &interval));
			if (MathUtils::GEish(startParam, interval.value[0], 1E-6))
				fStartParam = startParam;
		}
	}
}

void VWNURBSCurve::SetEndParameter(double endParam)
{
	if (fp) {
		if (fNURBSCurveID != PK_ENTITY_null) {
			PK_INTERVAL_t interval;
			VERIFYN(kBiplab, !PK_CURVE_ask_interval(fNURBSCurveID, &interval));
			if (MathUtils::LEish(endParam, interval.value[1], 1E-6))
				fEndParam = endParam;
		}
	}
}

double VWNURBSCurve::GetStartParameter()
{
	return fStartParam;
}

double VWNURBSCurve::GetEndParameter()
{
	return fEndParam;
}

double VWNURBSCurve::GetLength()
{
	if (fp && fpAPI)
	{
		PK_INTERVAL_t interval;
		interval.value[0] = fStartParam;
		interval.value[1] = fEndParam;

		PK_INTERVAL_t errorInterval;
		double length;

		VERIFYN(kMFlamer, !PK_CURVE_find_length(fNURBSCurveID, interval, &length, &errorInterval));

		return ((IParasolidVWAPI *)fpAPI)->PKUnitToVWUnit(length);
	}
	return 0;
}

double VWNURBSCurve::GetLength( double startParam, double endParam )
{
	
	if (fp && fpAPI)
	{
		PK_INTERVAL_t interval;
		interval.value[0] = Max<double>(startParam, fStartParam);
		interval.value[1] = Min<double>(endParam, fEndParam);

		PK_INTERVAL_t errorInterval;
		double length;

		VERIFYN(kMFlamer, !PK_CURVE_find_length(fNURBSCurveID, interval, &length, &errorInterval));

		return ((IParasolidVWAPI *)fpAPI)->PKUnitToVWUnit(length);
	}
	return 0;
}

Sint32 VWNURBSCurve::GetVWNURBSCurveID()
{
	return fNURBSCurveID;
}

VWPoint3D VWNURBSCurve::EvaluateCurve( double t )
{
	if (fp)
	{
		if(fNURBSCurveID != PK_ENTITY_null)
		{
			PK_VECTOR_t* outVecs = NULL;
			VERIFYN(kMFlamer, !PK_CURVE_eval(fNURBSCurveID, t, 0, outVecs));
			if(outVecs && fpAPI)
			{				
				VWPoint3D pnt(((IParasolidVWAPI *)fpAPI)->PKVecToWorldPt3( *outVecs ));
				PK_MEMORY_free( outVecs );
				return pnt;
			}
		}
	}
	return VWPoint3D(0,0,0);
}

bool VWNURBSCurve::EvaluateCurve( double t, Sint32 numDerivs, VWPoint3D& coord, TVWPoint3DArray& derivs)
{
	if (fp)
	{
		if(fNURBSCurveID != PK_ENTITY_null)
		{
			PK_VECTOR_t* outVecs = new PK_VECTOR_t[numDerivs+1]; 			
			VERIFYN(kMFlamer, !PK_CURVE_eval(fNURBSCurveID, t, numDerivs, outVecs));
			if(outVecs && fpAPI)
			{				
				coord = VWPoint3D(((IParasolidVWAPI *)fpAPI)->PKVecToWorldPt3(outVecs[0]));
				if(numDerivs > 0)
				{
					for(Sint32 i = 1; i <= numDerivs; i++)
					{													
						derivs.push_back(VWPoint3D(((IParasolidVWAPI *)fpAPI)->PKVecToWorldPt3( outVecs[i] )));	
					}
				}
				delete[] outVecs;
				return true;
			}			
		}
	}
	return false;
}


bool VWNURBSCurve::GetPointsAtDistance( double dist, VWPoint3D& outPoint, double& outParam )
{
	if (fp && fpAPI)
	{
		if(fNURBSCurveID != PK_ENTITY_null)
		{
			PK_INTERVAL_t interval;
			interval.value[0] = fStartParam;
			interval.value[1] = fEndParam;
			
			PK_CURVE_find_vectors_o_s options;
			PK_CURVE_find_vectors_o_m(options);

			options.measurements = &dist;
			options.n_measurements = 1;
			options.measurement_method = PK_measure_distance_c;

			double tolerence = ((IParasolidVWAPI *)fpAPI)->VWUnitToPKUnit(1);//Keep an eye on performance here

			PK_CURVE_find_vectors_r_s outStruc;

			VERIFYN(kMFlamer, !PK_CURVE_find_vectors(fNURBSCurveID, interval, tolerence, &options, &outStruc));
			
			outPoint = VWPoint3D(((IParasolidVWAPI *)fpAPI)->PKVecToWorldPt3( outStruc.vectors[0] ));
			outParam = outStruc.parms[0];							
			
			return true;
			
		}
	}
	return false;

}
bool VWNURBSCurve::GetPointsAtDistance( double startParam, double endParam, double tolerence, TDoubleArray distances, TVWPoint3DArray& points, TDoubleArray& params)
{
	if (fp && fpAPI)
	{
		if(fNURBSCurveID != PK_ENTITY_null)
		{
			PK_INTERVAL_t interval;
			interval.value[0] = Min<double>(startParam, fStartParam);
			interval.value[1] = Max<double>(endParam, fEndParam);
			
			PK_CURVE_find_vectors_o_s options;
			PK_CURVE_find_vectors_o_m(options);
			options.n_measurements = (int) distances.size();

			TDoubleArray::iterator itr = distances.begin();
			while(itr != distances.end())
			{
				*itr = ((IParasolidVWAPI *)fpAPI)->VWUnitToPKUnit( *itr );
				itr++;
			}
			options.measurements = &(distances[0]);

			options.measurement_method = PK_measure_distance_c;

			double tol = ((IParasolidVWAPI *)fpAPI)->VWUnitToPKUnit(tolerence);

			PK_CURVE_find_vectors_r_s outStruc;

			VERIFYN(kMFlamer, !PK_CURVE_find_vectors(fNURBSCurveID, interval, tol, &options, &outStruc));
			
			points.clear();			
			params.clear();
			for(Sint32 i=0; i < outStruc.n_entries; i++)
			{
				points.push_back(VWPoint3D(((IParasolidVWAPI *)fpAPI)->PKVecToWorldPt3( outStruc.vectors[i] )));
				params.push_back(outStruc.parms[i]);
			}
			
			return true;			
		}
	}
	return false;
}

bool VWNURBSCurve::GetEvenlySpacedPointsArc( size_t numDivisions, double offsetDistance, TVWPoint3DArray& points, TDoubleArray& params )
{
	double length = this->GetLength();
	double stepLength = length / double(numDivisions);
	TDoubleArray distances;
	double distance = fmod( offsetDistance, stepLength);
	double startExt = 0;
	double endExt = 0;
	if(distance < 0) startExt = (distance/length) * 1.1 * (fEndParam - fStartParam);
	if(distance > 0) endExt = (distance/length) * 1.1 * (fEndParam - fStartParam);
	for(size_t i = 0; i <= numDivisions; i++)
	{
		distances.push_back(distance);
		distance += stepLength;
	}	

	bool ok = this->GetPointsAtDistance( fStartParam + startExt, fEndParam + endExt, 50, distances, points, params);

	return ok;
}

bool VWNURBSCurve::GetEvenlySpacedPointsChord( size_t numDivisions, double tolerence, TVWPoint3DArray& points, TDoubleArray& params, TDoubleArray& distances )
{
	bool result = false;
	if (fp && fpAPI)
	{
		if(fNURBSCurveID != PK_ENTITY_null)
		{
			bool tolOk = false;
			double tol = ((IParasolidVWAPI *)fpAPI)->VWUnitToPKUnit(tolerence);
            PK_VECTOR_t* Q = SDK_NEW PK_VECTOR_t[numDivisions + 1];
            double* t = SDK_NEW double[numDivisions + 1];
            double* oldt = SDK_NEW double[numDivisions + 1];
            double* s = SDK_NEW double[numDivisions + 1];
            double* temp;
			double dt = (fEndParam - fStartParam) / numDivisions;
			t[0] = fStartParam;
			t[numDivisions] = fEndParam;
			oldt[0] = fStartParam;
			oldt[numDivisions] = fEndParam;			
			double d = 2 * tol;
			double num;
			double den;
			double aver = 1;
			size_t i;
			Sint32 iters = 1;
			Sint32 k;

			for (i = 1; i < numDivisions; i++) t[i] = fStartParam + double(i) * dt;

			VERIFYN(kMFlamer, !PK_CURVE_eval(fNURBSCurveID, fStartParam, 0, &Q[0]));

			s[0] = 0;

			

			while(iters < 50 && !tolOk)
			{
				//Compute points and distances//

				for (i = 1; i <= numDivisions; i++)
				{
					VERIFYN(kMFlamer, !PK_CURVE_eval(fNURBSCurveID, t[i], 0, &Q[i]));
					d = sqrt( pow(Q[i].coord[0] - Q[i-1].coord[0], 2) + pow(Q[i].coord[1] - Q[i-1].coord[1], 2) + pow(Q[i].coord[2] - Q[i-1].coord[2], 2) );
					s[i] = s[i-1] + d;
				}

				aver = s[numDivisions] / double(numDivisions);

				//Compute Deviations//

				if(aver > VWPoint3D::sEpsilon)
				{
					d = 0;
					i = 1;
					while( i <= numDivisions && MathUtils::Lesserish(d, tol, VWPoint3D::sEpsilon))					
					{
						d = Abs(s[i] - s[i-1] - aver);
						i++;
					}
					if(MathUtils::Greaterish(d, tol, VWPoint3D::sEpsilon))
					{
							tolOk = false;
					}
					else tolOk = true;
				}


				//Re-compute t values using linear interpolation//
				if(tolOk == false)
				{
					temp	= t;
					t		= oldt;
					oldt	= temp;
					k = 1;

					for(i = 1; i < numDivisions; i++)
					{
						d = double(i)*aver;
						while (MathUtils::Greaterish(d, s[k], VWPoint3D::sEpsilon))   k++;
						num = oldt[k]-oldt[k-1];
						den = s[k]-s[k-1];					
						t[i] = (num/den)*(d-s[k-1])+oldt[k-1];
					}
				}


				iters++;
			}

			//Either exceeded iters limit or reached tolerence so
			//return points and params	

			points.clear();
			params.clear();
			distances.clear();

			for(size_t i=0; i <= numDivisions; i++)
			{
				points.push_back(VWPoint3D(((IParasolidVWAPI *)fpAPI)->PKVecToWorldPt3( Q[i] )));
				distances.push_back(((IParasolidVWAPI *)fpAPI)->PKUnitToVWUnit(s[i]) );
				params.push_back(t[i]);
			}

			delete[] Q;
			delete[] t;
			delete[] oldt;
			delete[] s;
			result = true;
		}
	}
	return result;
}




void VWNURBSCurve::GetNURBSCurvesFromPoly(MCObjectHandle poly, std::vector<VWNURBSCurve>& curves, std::vector<short>& crvTypes)
{
	curves.clear();
	std::vector<Sint32> crvIDs;
    std::vector<std::pair<double, double>> intervals;
	std::vector<Boolean> visibilities;
	
	VCOMPtr<VectorWorks::Math::IPoly2DMath> polyMath = VCOMPtr<VectorWorks::Math::IPoly2DMath>( VectorWorks::Math::IID_Poly2DMath );
	if(polyMath)
		polyMath->GetPK_CurvesFromPoly(poly, crvIDs, intervals, visibilities, crvTypes);
	for(size_t i = 0; i < crvIDs.size(); i++)
	{
		VWFC::Math::VWNURBSCurve crv = VWFC::Math::VWNURBSCurve(crvIDs.at(i));
		crv.fStartParam = intervals.at(i).first;
		crv.fEndParam = intervals.at(i).second;
		curves.push_back(crv);
	}
}


bool VWNURBSCurve::GetClosestPointAndParamOnCurve(VWPoint3D& ptInOut, double& outPtParam, double& distance)
{
	bool withinParams = false;
	if (fp && fpAPI && fNURBSCurveID != PK_ENTITY_null)
	{
		PK_GEOM_range_vector_o_t options;
		PK_GEOM_range_vector_o_m(options);
		PK_range_result_t result;
		PK_range_1_r_t range;
		VERIFYN(kMFlamer, !PK_GEOM_range_vector(fNURBSCurveID, ((IParasolidVWAPI *)fpAPI)->WorldPt3ToPKVec(ptInOut), &options, &result, &range));

		if (result == PK_range_result_found_c) 
		{
			outPtParam = range.end.parameters[0];
			distance = ((IParasolidVWAPI *)fpAPI)->PKUnitToVWUnit(range.distance);
			ptInOut = ((IParasolidVWAPI *)fpAPI)->PKVecToWorldPt3(range.end.vector);
			if(outPtParam >= this->fStartParam && outPtParam <= this->fEndParam)
				withinParams = true;	
		}
	}
	return withinParams;
}