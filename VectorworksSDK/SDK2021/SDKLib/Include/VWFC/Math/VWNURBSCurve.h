//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Math
	{
		typedef std::vector< double, std::vwallocator<double> >   TDoubleArray;
		typedef std::vector< Sint32, std::vwallocator<Sint32> >   TIntArray;
		typedef std::vector< VWPoint3D >   TVWPoint3DArray;
		typedef std::vector< VWPoint2D >   TVWPoint2DArray;		

		class VWBodyFace;
		class VWBodyEdge;
		class VWNURBSCurve
		{
			friend class VWBodyFace;
			friend class VWBodyEdge;
			friend class VWNURBSSurface;
						
		public:
			// construction
							VWNURBSCurve();
							VWNURBSCurve(const VWNURBSCurve& src);
			virtual			~VWNURBSCurve();

			VWNURBSCurve&	operator=(const VWNURBSCurve& src);

			bool			IsValid() const;

		public:
							void			SetStartParameter(double startParam);
							void			SetEndParameter(double endParam);
							double			GetStartParameter();
							double			GetEndParameter();

							double			GetLength();
							double			GetLength( double startParam, double endParam );

							VWPoint3D		EvaluateCurve( double param );
							bool 			EvaluateCurve( double param, Sint32 numDerivs, VWPoint3D& coord, TVWPoint3DArray& derivs);
							bool			GetClosestPointAndParamOnCurve(VWPoint3D& ptInOut, double& outPtParam, double& distance);

							bool			GetPointsAtDistance(double dist, VWPoint3D& outPoint, double& outParam );
							bool			GetPointsAtDistance( double startParam, double endParam, double tolerence, TDoubleArray distances,
											TVWPoint3DArray& points, TDoubleArray& params);

							bool			GetEvenlySpacedPointsArc( size_t numDivisions, double offsetDistance, TVWPoint3DArray& points, TDoubleArray& params );
							bool			GetEvenlySpacedPointsChord( size_t numDivisions, double tolerence, TVWPoint3DArray& points, TDoubleArray& params, TDoubleArray& distances );
					 static void			GetNURBSCurvesFromPoly(MCObjectHandle poly, std::vector<VWNURBSCurve>& curves, std::vector<short>& crvTypes);

							Sint32 GetVWNURBSCurveID();

							

							
		protected:
							VWNURBSCurve(Sint32 curveID);


		private:
			IVWUnknown*	fp;
			IVWUnknown* fpAPI;
			Sint32			fNURBSCurveID;
			double		fStartParam;
			double		fEndParam;
		};

		typedef std::vector<VWNURBSCurve> VWNURBSCurveArray;



	}
}
