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
		class VWCubicInterpolation
		{
			public:
				//construction
								VWCubicInterpolation( const VWCubicInterpolation& cubicBezier );

								VWCubicInterpolation( const VWPoint2D&	point0, 
													  const VWPoint2D&	point1, 
													  const VWPoint2D&	point2, 
													  const VWPoint2D&	point3 );

				void			Set( const VWPoint2D& point0, 
									 const VWPoint2D& point1, 
									 const VWPoint2D& point2, 
									 const VWPoint2D& point3 );

				VWPoint2D		Pt0()		const;
				VWPoint2D		Pt1()		const;
				VWPoint2D		Pt2()		const;
				VWPoint2D		Pt3()		const;

				VWPoint2D		StartPt()	const;
				VWPoint2D		EndPt()		const;

				bool			PtOn( double tX, double tY,
									  const VWPoint2D& prevAddedPt, const double& addInterval,
									  const VWPoint2D& nextPt, VWPoint2D& result );

				// calculates point that lies on monotone Hermite spline.
				bool			PtOnHermiteSpline( double tX, double tY,
												   const VWPoint2D& prevAddedPt, const double& addInterval,
												   const VWPoint2D& nextPt, VWPoint2D& result,
												   double coeffExpand = 0.3 ) const;

			private:
				bool			SolveLSystem( double LSystem[4][5], double& a0, double& a1, double& a2, double& a3 );
				bool			FindPolynomialXtoY( double& a0, double& a1, double& a2, double& a3 );
				bool			FindPolynomialYtoX( double& a0, double& a1, double& a2, double& a3 );
				void			FindIntervals();
				
				// tools for Monotone Hermite spline construction.
				// -----------------------------------------------

				// calculates the derivatives of the function points.
				static	bool	CalcDerivatives( double t0, double t1, double t2, double t3,	// t values (must be distinct).
												 double f0, double f1, double f2, double f3,	// the corresponding function values.
												 double& outDer0, double& outDer1, 
												 double& outDer2, double& outDer3,				// result: derivatives.
												 bool& outIsMono );								// result: monotonicity.
				
				// calculates the derivatives of the function points (second variant).
				static	bool	CalcDerivativesSpec( double t0, double t1, double t2, double t3,	// t values (must be distinct).
													 double f0, double f1, double f2, double f3,	// the corresponding function values.
													 double& outDer0, double& outDer1,
													 double& outDer2, double& outDer3,				// result: derivatives.
													 bool& outIsMono );								// result: monotonicity.
				
				// evaluates a cubic polynomial given in Hermite form.
				static	bool	HermiteSplineVal( double t0, double t1,			// t values (must be distinct).
												  double f0, double f2,			// the corresponding function values.
												  double deriv0, double deriv1,	// the corresponding derivatives.
												  double tVal,					// t value that will be evaluated.
												  double& outFVal );			// resulting function value (for tVal).
				
				// checks if a sequence of 4 points is strictly X monotone.
				static	bool	Is4PtsSequenceXMonotone( const VWPoint2D& pt0, const VWPoint2D& pt1, 
														 const VWPoint2D& pt2, const VWPoint2D& pt3, double dEpsilon );
				
				// checks if a sequence of 4 points is strictly Y monotone.
				static	bool	Is4PtsSequenceYMonotone( const VWPoint2D& pt0, const VWPoint2D& pt1,
														 const VWPoint2D& pt2, const VWPoint2D& pt3, double dEpsilon );
				
				// tries to get a rotation angle that makes a 4-points sequence strictly X monotone.
				static	double	Make4PtsSequenceXMonotone( VWPoint2D& pt0, VWPoint2D& pt1, VWPoint2D& pt2, VWPoint2D& pt3,
														   VWPoint2D& outRotCenter, bool& outIsFound );
				
				// tries to get a rotation angle that makes a 4-points sequence strictly Y monotone.
				static	double	Make4PtsSequenceYMonotone( VWPoint2D& pt0, VWPoint2D& pt1, VWPoint2D& pt2, VWPoint2D& pt3,
														   VWPoint2D& outRotCenter, bool& outIsFound );

			private:
				VWPoint2D		fPoint0;
				VWPoint2D		fPoint1;
				VWPoint2D		fPoint2;
				VWPoint2D		fPoint3;
				// x limits
				double			fMinX;
				double			fMaxX;
				// y limits
				double			fMinY;
				double			fMaxY;
		};
	}
}