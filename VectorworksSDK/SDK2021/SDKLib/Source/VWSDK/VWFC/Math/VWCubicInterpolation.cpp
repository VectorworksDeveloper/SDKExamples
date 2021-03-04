//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;

VWCubicInterpolation::VWCubicInterpolation( const VWCubicInterpolation& cubicBezier )
{
	*this = cubicBezier;
}

VWCubicInterpolation::VWCubicInterpolation( const VWPoint2D&	point0, 
											const VWPoint2D&	point1, 
											const VWPoint2D&	point2, 
											const VWPoint2D&	point3 )
{
	this->fPoint0		= point0;
	this->fPoint1		= point1;
	this->fPoint2		= point2;
	this->fPoint3		= point3;

	// valid intervals
	this->FindIntervals();
}

void	VWCubicInterpolation::Set( const VWPoint2D& point0,
								   const VWPoint2D& point1,
								   const VWPoint2D& point2,
								   const VWPoint2D& point3 )
{
	this->fPoint0		= point0;
	this->fPoint1		= point1;
	this->fPoint2		= point2;
	this->fPoint3		= point3;

	// valid intervals
	this->FindIntervals();
}

VWPoint2D	VWCubicInterpolation::Pt0() const
{ 
	return ( this->fPoint0 );
}

VWPoint2D	VWCubicInterpolation::Pt1() const
{ 
	return ( this->fPoint1 );
}

VWPoint2D	VWCubicInterpolation::Pt2() const
{
	return ( this->fPoint2 );
}

VWPoint2D	VWCubicInterpolation::Pt3() const
{
	return ( this->fPoint3 );
}

VWPoint2D VWCubicInterpolation::StartPt() const
{
	return ( this->fPoint0 );
}

VWPoint2D VWCubicInterpolation::EndPt() const
{
	return ( this->fPoint3 );
}

bool VWCubicInterpolation::PtOn( double tX, double tY,
								 const VWPoint2D& prevAddedPt, const double& addInterval,
								 const VWPoint2D& nextPt, VWPoint2D& result )
{
	double tolerance	= addInterval * 0.2;
	double ctrlDist		= 1.5 * prevAddedPt.DistanceTo( nextPt );

	double a0, a1, a2, a3;

	VWPoint2D	res1,	res2;
	double		dist1,	dist2;

	bool		bCorrect1	= true;
	bool		bCorrect2	= true;

	// find the XtoY polynomial
	if ( FindPolynomialXtoY( a0, a1, a2, a3 ) ) {
		// prevent incorrect parameter value
		if		( tX < fMinX )		tX	= fMinX;
		else if ( tX > fMaxX )		tX	= fMaxX;

		res1.x	= tX;
		res1.y	= a0 + a1 * tX + a2 * tX * tX + a3 * tX * tX * tX;
		double toPrevDist	= res1.DistanceTo( prevAddedPt );
		if ( Abs( toPrevDist - addInterval ) < tolerance ) {
			dist1	= toPrevDist + res1.DistanceTo( nextPt );
			if ( dist1 > ctrlDist )	bCorrect1	= false;
		}
		else	bCorrect1	= false;
	}
	else	bCorrect1	= false;

	// find the YtoX polynomial
	if ( FindPolynomialYtoX( a0, a1, a2, a3 ) )
	{
		// prevent incorrect parameter value
		if		( tY < fMinY )		tY	= fMinY;
		else if ( tY > fMaxY )		tY	= fMaxY;

		res2.y	= tY;
		res2.x	= a0 + a1 * tY + a2 * tY * tY + a3 * tY * tY * tY;
		double toPrevDist	= res2.DistanceTo( prevAddedPt );
		if ( Abs( toPrevDist - addInterval ) < tolerance ) {
			dist2	= toPrevDist + res2.DistanceTo( nextPt );
			if ( dist2 > ctrlDist )	bCorrect2	= false;
		}
		else	bCorrect2	= false;
	}
	else
		bCorrect2	= false;

	// find correct result
	if ( bCorrect1 && bCorrect2 ) {
		if ( dist1 < dist2 )	result = res1;
		else					result = res2;
	}
	else if ( bCorrect1 ) {
		result = res1;
	}
	else if ( bCorrect2 ) {
		result = res2;
	}
	else {
		return false;
	}

	return true;
}

// calculates point that lies on monotone Hermite spline.
bool VWCubicInterpolation::PtOnHermiteSpline( double tX, double tY,
											  const VWPoint2D& prevAddedPt, const double& addInterval,
											  const VWPoint2D& nextPt, VWPoint2D& result,
											  double coeffExpand /*= 0.3*/ ) const
{
	// constants.
	const	double	kTolerance			=	( addInterval * coeffExpand );
	const	double	kControlDistance	=	1.5 * prevAddedPt.DistanceTo( nextPt );

	VWPoint2D	res1,	res2;
	double		dist1, dist2;

	bool		isCorrXtoY	=	true;
	bool		isCorrYtoX	=	true;
	
	double		der0, der1, der2, der3;
	bool		isXMono, isYMono;

	double		intrplX0 = 0, intrplX1 = 0, intrplY0 = 0, intrplY1 = 0, tang0 = 0, tang1 = 0;

	// I try: prepare for X to Y interpolation.
	// ----------------------------------------
	VWPoint2D	pt0			=	fPoint0;
	VWPoint2D	pt1			=	fPoint1;
	VWPoint2D	pt2			=	fPoint2;
	VWPoint2D	pt3			=	fPoint3;
	
	VWPoint2D	tPt( tX, tY );
	double		minX		=	fMinX;
	double		maxX		=	fMaxX;
	
	VWPoint2D	rotCenter;
	bool		foundRotToXMono, foundRotToYMono;
	
	// try to get a rotation angle that makes the sequence strictly X monotone.
	double		rotAng		=	VWCubicInterpolation::Make4PtsSequenceXMonotone( pt0, pt1, pt2, pt3, rotCenter, foundRotToXMono );
	if ( foundRotToXMono ) {	// apply rotation only if such is found.
	
		tPt.RotateAtDeg(	rotCenter, rotAng );
		
		// recalculate min/max X values.
		minX						= pt0.x;
		if ( minX > pt1.x )	minX	= pt1.x;
		if ( minX > pt2.x )	minX	= pt2.x;
		if ( minX > pt3.x )	minX	= pt3.x;

		maxX						= pt0.x;
		if ( maxX < pt1.x )	maxX	= pt1.x;
		if ( maxX < pt2.x )	maxX	= pt2.x;
		if ( maxX < pt3.x )	maxX	= pt3.x;
	}
	else {	// rotation to X monotone is NOT found.
	
		// restore to original positions.
		pt0	=	fPoint0;	pt1	=	fPoint1;
		pt2	=	fPoint2;	pt3	=	fPoint3;
	}

	// I try: X to Y.
	// --------------
	// calculate the derivatives of two middle points.
	if ( VWCubicInterpolation::CalcDerivativesSpec( pt0.x, pt1.x, pt2.x, pt3.x,
													pt0.y, pt1.y, pt2.y, pt3.y,
													der0, der1, der2, der3, isXMono ) ) {
	
		// prevent incorrect parameter value
		if ( tPt.x < minX ) {
			tPt.x			=	minX;
		}
		else if ( tPt.x > maxX ) {
			tPt.x			=	maxX;
		}

		// choose proper interval for the interpolation.
		if (		MathUtils::IsBetween( tPt.x, pt1.x, pt2.x, VWPoint2D::sEpsilon ) ) {	// prefered case.
			intrplX0		=	pt1.x;
			intrplX1		=	pt2.x;
			intrplY0		=	pt1.y;
			intrplY1		=	pt2.y;
			tang0			=	der1;
			tang1			=	der2;
		}
		else if (	MathUtils::IsBetween( tPt.x, pt0.x, pt1.x, VWPoint2D::sEpsilon ) ) {	// a secondary case.
			intrplX0		=	pt0.x;
			intrplX1		=	pt1.x;
			intrplY0		=	pt0.y;
			intrplY1		=	pt1.y;
			tang0			=	der0;
			tang1			=	der1;
		}
		else if (	MathUtils::IsBetween( tPt.x, pt2.x, pt3.x, VWPoint2D::sEpsilon ) ) {	// a secondary case.
			intrplX0		=	pt2.x;
			intrplX1		=	pt3.x;
			intrplY0		=	pt2.y;
			intrplY1		=	pt3.y;
			tang0			=	der2;
			tang1			=	der3;
		}
		
		res1.x				=	tPt.x;
		// evaluate the cubic Hermite spline value.
		if ( ! VWCubicInterpolation::HermiteSplineVal( intrplX0, intrplX1, intrplY0, intrplY1,
													   tang0, tang1, res1.x, res1.y ) ) {
			isCorrXtoY	=	false;
		}
		else {

			if ( foundRotToXMono ) {	// get the correct position of the result point.
				res1.RotateAtDeg( rotCenter, - rotAng );
			}
		
			// check the distance to the previously added.
			double	toPrevDist	=	res1.DistanceTo( prevAddedPt );
			if ( Abs( toPrevDist - addInterval ) < kTolerance ) {
			
				dist1			=	( toPrevDist + res1.DistanceTo( nextPt ) );
				if ( dist1 > kControlDistance ) {
					isCorrXtoY	=	false;
				}
			}
			else {
				isCorrXtoY		=	false;
			}
		}
	}
	else {
		isCorrXtoY				=	false;
	}

	// II try: prepare for Y to X interpolation.
	// ----------------------------------------
	pt0						=	fPoint0;
	pt1						=	fPoint1;
	pt2						=	fPoint2;
	pt3						=	fPoint3;
	
	tPt.SetPoint( tX, tY );
	double	minY			=	fMinY;
	double	maxY			=	fMaxY;
	
	// try to get a rotation angle that makes the sequence strictly Y monotone.
	rotAng					=	VWCubicInterpolation::Make4PtsSequenceYMonotone( pt0, pt1, pt2, pt3, rotCenter, foundRotToYMono );
	if ( foundRotToYMono ) {	// apply rotation only if such is found.
	
		tPt.RotateAtDeg(	rotCenter, rotAng );
		
		// recalculate min/max Y values.
		minY							= pt0.y;
		if ( minY > pt1.y )	minY	= pt1.y;
		if ( minY > pt2.y )	minY	= pt2.y;
		if ( minY > pt3.y )	minY	= pt3.y;

		maxY						= pt0.y;
		if ( maxY < pt1.y )	maxY	= pt1.y;
		if ( maxY < pt2.y )	maxY	= pt2.y;
		if ( maxY < pt3.y )	maxY	= pt3.y;
	}
	else {	// rotation to Y monotone is NOT found.
	
		// restore to original positions.
		pt0	=	fPoint0;	pt1	=	fPoint1;
		pt2	=	fPoint2;	pt3	=	fPoint3;
	}

	// II try: Y to X.
	// ---------------
	// calculate the derivatives of two middle points.
	if ( VWCubicInterpolation::CalcDerivativesSpec( pt0.y, pt1.y, pt2.y, pt3.y,
													pt0.x, pt1.x, pt2.x, pt3.x,
													der0, der1, der2, der3, isYMono ) ) {
	
		// prevent incorrect parameter value
		if ( tPt.y < minY ) {
			tPt.y			=	minY;
		}
		else if ( tPt.y > maxY ) {
			tPt.y			=	maxY;
		}

		// choose proper interval for the interpolation.
		if (		MathUtils::IsBetween( tPt.y, pt1.y, pt2.y, VWPoint2D::sEpsilon ) ) {	// prefered case.
			intrplY0		=	pt1.y;
			intrplY1		=	pt2.y;
			intrplX0		=	pt1.x;
			intrplX1		=	pt2.x;
			tang0			=	der1;
			tang1			=	der2;
		}
		else if (	MathUtils::IsBetween( tPt.y, pt0.y, pt1.y, VWPoint2D::sEpsilon ) ) {	// a secondary case.
			intrplY0		=	pt0.y;
			intrplY1		=	pt1.y;
			intrplX0		=	pt0.x;
			intrplX1		=	pt1.x;
			tang0			=	der0;
			tang1			=	der1;
		}
		else if (	MathUtils::IsBetween( tPt.y, pt2.y, pt3.y, VWPoint2D::sEpsilon ) ) {	// a secondary case.
			intrplY0		=	pt2.y;
			intrplY1		=	pt3.y;
			intrplX0		=	pt2.x;
			intrplX1		=	pt3.x;
			tang0			=	der2;
			tang1			=	der3;
		}
		
		res2.y			=	tPt.y;
		// evaluate the cubic Hermite spline value.
		if ( ! VWCubicInterpolation::HermiteSplineVal( intrplY0, intrplY1, intrplX0, intrplX1,
													   tang0, tang1, res2.y, res2.x ) ) {
			isCorrYtoX	=	false;
		}
		else {

			if ( foundRotToYMono ) {	// get the correct position of the result point.
				res2.RotateAtDeg( rotCenter, - rotAng );
			}
			
			// check the distance to the previously added.
			double	toPrevDist	=	res2.DistanceTo( prevAddedPt );
			if ( Abs( toPrevDist - addInterval ) < kTolerance ) {
			
				dist2			=	( toPrevDist + res2.DistanceTo( nextPt ) );
				if ( dist2 > kControlDistance ) {
					isCorrYtoX	=	false;
				}
			}
			else {
				isCorrYtoX		=	false;
			}
		}
	}
	else {
		isCorrYtoX				=	false;
	}
	
	// make use of the results.
	// foundRotToXMono, foundRotToYMono:
	// ---------------------------------
	// 0, 0	-> X and Y interpolation.
	// 0, 1	-> Y interpolation.
	// 1, 0	-> X interpolation.
	// 1, 1	-> X and Y interpolation.
	if ( foundRotToXMono || foundRotToYMono ) {

		isCorrXtoY				=	( isCorrXtoY && foundRotToXMono );
		isCorrYtoX				=	( isCorrYtoX && foundRotToYMono );
	}
	
	// choose the better result.
	bool	isCorrect			=	true;
	if ( isCorrXtoY && isCorrYtoX ) {
	
		if ( dist1 < dist2 )	result = res1;
		else					result = res2;
	}
	else if ( isCorrXtoY ) {
	
		result					=	res1;
	}
	else if ( isCorrYtoX ) {
	
		result					=	res2;
	}
	else {
		isCorrect				=	false;
	}

	return	isCorrect;
}

bool	VWCubicInterpolation::FindPolynomialXtoY( double& a0, double& a1, double& a2, double& a3 )
{
	// linear system matrix
	double LSystem[4][5];
	
	// initialization of this matrix
	// row 1
	LSystem[0][0] = 1;			LSystem[0][4] = fPoint0.y;
	LSystem[0][1] = fPoint0.x;	LSystem[0][2] = fPoint0.x * fPoint0.x;	LSystem[0][3] = fPoint0.x * fPoint0.x * fPoint0.x;

	// row 2
	LSystem[1][0] = 1;			LSystem[1][4] = fPoint1.y;
	LSystem[1][1] = fPoint1.x;	LSystem[1][2] = fPoint1.x * fPoint1.x;	LSystem[1][3] = fPoint1.x * fPoint1.x * fPoint1.x;

	// row 3
	LSystem[2][0] = 1;			LSystem[2][4] = fPoint2.y;
	LSystem[2][1] = fPoint2.x;	LSystem[2][2] = fPoint2.x * fPoint2.x;	LSystem[2][3] = fPoint2.x * fPoint2.x * fPoint2.x;

	// row 3
	LSystem[3][0] = 1;			LSystem[3][4] = fPoint3.y;
	LSystem[3][1] = fPoint3.x;	LSystem[3][2] = fPoint3.x * fPoint3.x;	LSystem[3][3] = fPoint3.x * fPoint3.x * fPoint3.x;

	// solve the linear system
	return	SolveLSystem( LSystem, a0, a1, a2, a3 );
}

bool	VWCubicInterpolation::FindPolynomialYtoX( double& a0, double& a1, double& a2, double& a3 )
{
	// linear system matrix
	double LSystem[4][5];
	
	// initialization of this matrix
	// row 1
	LSystem[0][0] = 1;			LSystem[0][4] = fPoint0.x;
	LSystem[0][1] = fPoint0.y;	LSystem[0][2] = fPoint0.y * fPoint0.y;	LSystem[0][3] = fPoint0.y * fPoint0.y * fPoint0.y;

	// row 2
	LSystem[1][0] = 1;			LSystem[1][4] = fPoint1.x;
	LSystem[1][1] = fPoint1.y;	LSystem[1][2] = fPoint1.y * fPoint1.y;	LSystem[1][3] = fPoint1.y * fPoint1.y * fPoint1.y;

	// row 3
	LSystem[2][0] = 1;			LSystem[2][4] = fPoint2.x;
	LSystem[2][1] = fPoint2.y;	LSystem[2][2] = fPoint2.y * fPoint2.y;	LSystem[2][3] = fPoint2.y * fPoint2.y * fPoint2.y;

	// row 3
	LSystem[3][0] = 1;			LSystem[3][4] = fPoint3.x;
	LSystem[3][1] = fPoint3.y;	LSystem[3][2] = fPoint3.y * fPoint3.y;	LSystem[3][3] = fPoint3.y * fPoint3.y * fPoint3.y;

	// solve the linear system
	return	SolveLSystem( LSystem, a0, a1, a2, a3 );
}

void	VWCubicInterpolation::FindIntervals()
{
	fMinX	= fPoint0.x;
	if ( fMinX > fPoint1.x )	fMinX	= fPoint1.x;
	if ( fMinX > fPoint2.x )	fMinX	= fPoint2.x;
	if ( fMinX > fPoint3.x )	fMinX	= fPoint3.x;

	fMaxX	= fPoint0.x;
	if ( fMaxX < fPoint1.x )	fMaxX	= fPoint1.x;
	if ( fMaxX < fPoint2.x )	fMaxX	= fPoint2.x;
	if ( fMaxX < fPoint3.x )	fMaxX	= fPoint3.x;

	fMinY	= fPoint0.y;
	if ( fMinY > fPoint1.y )	fMinY	= fPoint1.y;
	if ( fMinY > fPoint2.y )	fMinY	= fPoint2.y;
	if ( fMinY > fPoint3.y )	fMinY	= fPoint3.y;

	fMaxY	= fPoint0.y;
	if ( fMaxY < fPoint1.y )	fMaxY	= fPoint1.y;
	if ( fMaxY < fPoint2.y )	fMaxY	= fPoint2.y;
	if ( fMaxY < fPoint3.y )	fMaxY	= fPoint3.y;
}

bool	VWCubicInterpolation::SolveLSystem( double LSystem[4][5], double& a0, double& a1, double& a2, double& a3 )
{
	double epsilon = 1e-10;

	size_t iRows	= 4;
	size_t iColumns	= 5;

	// for any Xi eliminate
	for ( size_t i = 0 ; i < iColumns - 1 ; i ++ ) {
		// find non-zero coeficient for Xi
		bool	bFound	= false;
		size_t	j		= i;

		while ( ! bFound && j < iRows ) {
			if ( !MathUtils::Equalish( LSystem[j][i], 0.0, epsilon ) )	bFound = true;
			else														j++;
		}

		if ( !bFound )	return false;
		
		// exchange i and j rows
		for ( size_t k = 0 ; k < iColumns && i != j ; k ++ ) {
			VWFC::Tools::SwapVariables( LSystem[i][k], LSystem[j][k] );
		}

		double dNumber = -1.0 / LSystem[i][i];
		
		for ( size_t k = 0 ; k < iRows; k ++ ) {
			if ( k != i ) {
				// multiply column i and add to column k
				double *pS		= LSystem[ i ];
				double *pD		= LSystem[ k ];
				double coeff	= dNumber * LSystem[ k ][ i ];

				for ( size_t l = 0 ; l < iColumns ; l ++, pS ++, pD ++ )	*pD += (*pS) * coeff;

				LSystem[ k ][ i ] = 0.0;
			}
		}

	}

	// find the result
	double result[4];
	for ( size_t i = 0 ; i < iRows ; i ++ ) {
		if ( MathUtils::Equalish( LSystem[i][i], 0.0, epsilon ) )	return false;
		result[ i ] = LSystem[ i ][ iColumns-1 ] / LSystem[ i ][ i ];
	}

	a0 = result[ 0 ];	a1 = result[ 1 ];	
	a2 = result[ 2 ];	a3 = result[ 3 ];

	return true;
}

// calculates the derivatives of the function points.
bool VWCubicInterpolation::CalcDerivatives( double t0, double t1, double t2, double t3,	// t values (must be distinct).
											double f0, double f1, double f2, double f3,	// the corresponding function values.
											double& outDer0, double& outDer1,
											double& outDer2, double& outDer3,			// result: derivatives.
											bool& outIsMono )							// result: monotonicity.
{
	// init.
	double	arrT[ 4 ]	=	{ t0, t1, t2, t3 };
	double	arrF[ 4 ]	=	{ f0, f1, f2, f3 };
	
	// check t intervals.
	// ------------------
	bool	doExist		=	true;
	for ( size_t i = 1 ; i < 4 ; ++ i ) {
	
		if ( Abs( arrT[ i ] - arrT[ i - 1 ] ) < VWPoint2D::sEpsilon ) {
			doExist		=	false;
			outIsMono	=	false;
			break;
		}
	}
	
	// go on.
	if ( doExist ) {
	
		// monotonicity.
		outIsMono			=	true;
		
		double	endsDiff	=	( arrT[ 3 ] - arrT[ 0 ] );	// difference between the two end points.
		// check monotonicity.
		// -------------------
		if ( endsDiff < 0 ) {
		
			if ( ( arrT[ 1 ] - arrT[ 0 ] > 0 ) ||
				 ( arrT[ 2 ] - arrT[ 1 ] > 0 ) ||
				 ( arrT[ 3 ] - arrT[ 2 ] > 0 ) ) {
				outIsMono	=	false;
			}
		}
		else {
		
			if ( ( arrT[ 1 ] - arrT[ 0 ] < 0 ) ||
				 ( arrT[ 2 ] - arrT[ 1 ] < 0 ) ||
				 ( arrT[ 3 ] - arrT[ 2 ] < 0 ) ) {
				outIsMono	=	false;
			}
		}
		
		// to store divided f differences.
		double	arrDivDiff[ 4 ];
		
		// compute divided f differences.
		// ------------------------------
		double	prevFDiff		=	0;		// to store previous difference.
		for ( size_t i = 1 ; i < 4 ; ++ i ) {
		
			double	funcDiff	=	( arrF[ i ] - arrF[ i - 1 ] );
			if ( ( funcDiff * prevFDiff ) < 0 )	{	// check monotonicity.
				outIsMono		=	false;
			}
			prevFDiff			=	funcDiff;
			arrDivDiff[ i ]		=	funcDiff / ( arrT[ i ] - arrT[ i - 1 ] );	// t intervals already checked.
		}
		
		// compute derivatives.
		// --------------------
		double	deriv[ 4 ];
		deriv[ 0 ]				=	arrDivDiff[ 1 ];
		deriv[ 3 ]				=	arrDivDiff[ 3 ];
		for ( size_t i = 1 ; i < 3 ; ++ i ) {
			deriv[ i ]			=	0.5 * ( arrDivDiff[ i ] + arrDivDiff[ i + 1 ] ); 
		}
		
		// correction for monotonicity.
		// ----------------------------
		if ( outIsMono ) {
		
			for ( size_t i = 1 ; i < 4 ; ++ i ) {
			
				if ( Abs( arrDivDiff[ i ] ) < VWPoint2D::sEpsilon )	{	// prevent from zero division.
					deriv[ i - 1 ]		=	0;
					deriv[ i ]			=	0;
				}
				else {
					double	a			=	deriv[ i - 1 ]	/	arrDivDiff[ i ];
					double	b			=	deriv[ i ]		/	arrDivDiff[ i ];
					double	c			=	( a * a ) + ( b * b );
					
					if ( c > 9 ) {	// correction!
						
						c				=	3 / sqrt( c );
						deriv[ i - 1 ]	*=	c;
						deriv[ i ]		*=	c;
					}
				}
			}
		}
		
		// results.
		// --------
		outDer0							=	deriv[ 0 ];
		outDer1							=	deriv[ 1 ];
		outDer2							=	deriv[ 2 ];
		outDer3							=	deriv[ 3 ];
	}
	
	return	doExist;
}

// calculates the derivatives of the function points (second variant).
bool VWCubicInterpolation::CalcDerivativesSpec( double t0, double t1, double t2, double t3,	// t values (must be distinct).
												double f0, double f1, double f2, double f3,	// the corresponding function values.
												double& outDer0, double& outDer1,
												double& outDer2, double& outDer3,			// result: derivatives.
												bool& outIsMono )							// result: monotonicity.
{
	// init.
	double	arrT[ 4 ]	=	{ t0, t1, t2, t3 };
	double	arrF[ 4 ]	=	{ f0, f1, f2, f3 };
	
	// check t intervals.
	// ------------------
	bool	doExist		=	true;
	for ( size_t i = 1 ; i < 4 ; ++ i ) {
	
		if ( Abs( arrT[ i ] - arrT[ i - 1 ] ) < VWPoint2D::sEpsilon ) {
			doExist		=	false;
			outIsMono	=	false;
			break;
		}
	}
	
	// go on.
	if ( doExist ) {
	
		// monotonicity.
		outIsMono			=	true;
		
		double	endsDiff	=	( arrT[ 3 ] - arrT[ 0 ] );	// difference between the two end points.
		// check monotonicity.
		// -------------------
		if ( endsDiff < 0 ) {
		
			if ( ( arrT[ 1 ] - arrT[ 0 ] > 0 ) ||
				 ( arrT[ 2 ] - arrT[ 1 ] > 0 ) ||
				 ( arrT[ 3 ] - arrT[ 2 ] > 0 ) ) {
				outIsMono	=	false;
			}
		}
		else {
		
			if ( ( arrT[ 1 ] - arrT[ 0 ] < 0 ) ||
				 ( arrT[ 2 ] - arrT[ 1 ] < 0 ) ||
				 ( arrT[ 3 ] - arrT[ 2 ] < 0 ) ) {
				outIsMono	=	false;
			}
		}
		
		// begin calculations.
		// -------------------
		double	diff1		=	( arrT[ 1 ] - arrT[ 0 ] );
		double	divDiff1	=	( arrF[ 1 ] - arrF[ 0 ] )	/	diff1;	// t intervals already checked (non zero).
		
		double	divDiffSave	=	divDiff1;
		
		double	diff2		=	( arrT[ 2 ] - arrT[ 1 ] );
		double	divDiff2	=	( arrF[ 2 ] - arrF[ 1 ] )	/	diff2;	// t intervals already checked (non zero).
		
		// derivatives.
		double	deriv[ 4 ];
		
		// calc derivative 0 by using non-centered three point formula - shape preserving.
		double	sumDiff		=	( diff1 + diff2 );
		double	a			=	( diff1 + sumDiff )			/	sumDiff;
		double	b			=	- diff1						/	sumDiff;
		deriv[ 0 ]			=	( a * divDiff1 ) + ( b * divDiff2 );
		
		if ( ( deriv[ 0 ] * divDiff1 ) <= 0 ) {	// sign checking.
			deriv[ 0 ]		=	0;
		}
		else if ( ( divDiff1 * divDiff2 ) < 0 ) {	// only if monotonicity switches.
		
			double tmp		=	( 3 * divDiff1 );
			if ( Abs ( tmp ) < Abs ( deriv[ 0 ] ) ) {
				deriv[ 0 ]	=	tmp;
			}
		}
		
		// loop inner points.
		// ------------------
		for ( size_t i = 2 ; i <= 3 ; ++ i ) {	// interior points.
		
			// re-init.
			if ( i > 2 ) {
				diff1		=	diff2;
				diff2		=	( arrT[ i ] - arrT[ i - 1 ] );
				sumDiff		=	( diff1 + diff2 );
				divDiff1	=	divDiff2;
				divDiff2	=	( arrF[ i ] - arrF[ i - 1 ] )	/	diff2;	// t intervals already checked (non zero).
			}
			
			// calc derivatives be 0 unless data are strictly monotonic.
			deriv[ i - 1 ]	=	0;

			double	sign	=	( divDiff1 * divDiff2 );	// sign checking.
			if ( sign < 0 ) {
				outIsMono	=	false;
				divDiffSave	=	divDiff2;
			}
			else if ( sign == 0 ) {		// changes in direction of monotonicity.
			
				if ( divDiff2 != 0 ) {
					if ( ( divDiffSave * divDiff2 ) < 0 ) {	// sign checking.
						outIsMono	=	false;
					}
					divDiffSave		=	divDiff2;
				}
			}
			else {	// Brodlie modification of the Butland formula.
			
				double	sumDiffx3	=	( 3 * sumDiff );
				
				a					=	( sumDiff + diff1 )	/	sumDiffx3;
				b					=	( sumDiff + diff2 )	/	sumDiffx3;
				
				double	maxDivDiff	=	Max( Abs ( divDiff1 ), Abs ( divDiff2 ) );
				double	minDivDiff	=	Min( Abs ( divDiff1 ), Abs ( divDiff2 ) );
				
				double	coeff1		=	divDiff1			/	maxDivDiff;
				double	coeff2		=	divDiff2			/	maxDivDiff;
				
				// derivative correction.
				deriv[ i - 1 ]		=	minDivDiff			/	( ( a * coeff1 ) + ( b * coeff2 ) );
			}
		}
		
		// calc derivative using non-centered three point formula - shape preserving.
		a						=	- diff2					/	sumDiff;
		b						=	( diff2 + sumDiff )		/	sumDiff;
		deriv[ 3 ]				=	( a * divDiff1 ) + ( b * divDiff2 );

		if ( ( deriv[ 3 ] * divDiff2 ) <= 0 ) {
			deriv[ 3 ]			=	0;
		}
		else if ( ( divDiff1 * divDiff2 ) < 0 ) {	// only if monotonicity switches.
		
			double	tmp			=	( 3 * divDiff2 );
			if ( Abs ( tmp ) < Abs( deriv[ 3 ] ) ) {
				deriv[ 3 ]		=	tmp;
			}
		}
		
		// results.
		// --------
		outDer0					=	deriv[ 0 ];
		outDer1					=	deriv[ 1 ];
		outDer2					=	deriv[ 2 ];
		outDer3					=	deriv[ 3 ];
	}
	
	return	doExist;
}

// evaluates a cubic polynomial given in Hermite form.
bool VWCubicInterpolation::HermiteSplineVal( double t0, double t1,			// t values (must be distinct).
											 double f0, double f2,			// the corresponding function values.
											 double deriv0, double deriv1,	// the corresponding derivatives.
											 double tVal,					// t value that will be evaluated.
											 double& outFVal )				// resulting function value (for tVal).
{
	double	dt			=	( t1 - t0 );
	bool	isFound		=	false;
	
	// t values must be distinct.
	if ( Abs( dt ) > VWPoint2D::sEpsilon ) {
	
		double	minT	=	Min( 0.0, dt );
		double	maxT	=	Max( 0.0, dt );
		
		// calculates cubic coefficients.
		double	delta	=		( f2		- f0 		) 	/	dt;
		double	delta1	=		( deriv0 	- delta		)	/	dt;
		double	delta2	=		( deriv1 	- delta		)	/	dt;
		double	C2		=	- 	( delta1 + delta1 + delta2 );
		double	C3		=		( delta1 	+ delta2	)	/	dt;
		
		// evaluation.
		double	a		=	tVal - t0;
		outFVal			=	f0 + ( a * ( deriv0 + ( a * ( C2 + ( a * C3 ) ) ) ) );
		
		// check if it is an extrapolation points.
		if ( ( a < minT ) || ( a > maxT ) ) {
			ASSERTN( kVStanev, false );	// should not be!
		}
		
		isFound			=	true;
	}

	return	isFound;
}

// checks if a sequence of 4 points is strictly X monotone.
bool VWCubicInterpolation::Is4PtsSequenceXMonotone( const VWPoint2D& pt0, const VWPoint2D& pt1,
												    const VWPoint2D& pt2, const VWPoint2D& pt3, double dEpsilon )
{
	return 
			( ( MathUtils::Lesserish( pt0.x, pt1.x, dEpsilon ) &&
				MathUtils::Lesserish( pt1.x, pt2.x, dEpsilon ) &&
				MathUtils::Lesserish( pt2.x, pt3.x, dEpsilon ) )
			  ||
			  ( MathUtils::Lesserish( pt3.x, pt2.x, dEpsilon ) &&
				MathUtils::Lesserish( pt2.x, pt1.x, dEpsilon ) &&
				MathUtils::Lesserish( pt1.x, pt0.x, dEpsilon ) ) );
}

// checks if a sequence of 4 points is strictly Y monotone.
bool VWCubicInterpolation::Is4PtsSequenceYMonotone( const VWPoint2D& pt0, const VWPoint2D& pt1,
												    const VWPoint2D& pt2, const VWPoint2D& pt3, double dEpsilon )
{
	return 
			( ( MathUtils::Lesserish( pt0.y, pt1.y, dEpsilon ) &&
				MathUtils::Lesserish( pt1.y, pt2.y, dEpsilon ) &&
				MathUtils::Lesserish( pt2.y, pt3.y, dEpsilon ) )
			  ||
			  ( MathUtils::Lesserish( pt3.y, pt2.y, dEpsilon ) &&
				MathUtils::Lesserish( pt2.y, pt1.y, dEpsilon ) &&
				MathUtils::Lesserish( pt1.y, pt0.y, dEpsilon ) ) );
}

// tries to get a rotation angle that makes a 4-points sequence strictly X monotone.
double VWCubicInterpolation::Make4PtsSequenceXMonotone( VWPoint2D& pt0, VWPoint2D& pt1, VWPoint2D& pt2, VWPoint2D& pt3,
														VWPoint2D& outRotCenter, bool& outIsFound )
{
	// init.
	double	rotateAng			=	0;
	outIsFound					=	false;
	outRotCenter				=	pt1;
	
	if ( ! VWCubicInterpolation::Is4PtsSequenceXMonotone( pt0, pt1, pt2, pt3, 0 ) ) {
	
		VWPoint2D	vecToRot	=	( pt0 - pt1 );
		vecToRot.Normalize();
		VWPoint2D	vecCntrl	=	( pt2 - pt1 );
		vecCntrl.Normalize();
		
		// get the angle to Oy.
		rotateAng				=	vecToRot.CalcAng360() - 90;
		double		cntrlAng	=	vecCntrl.CalcAng360() - 90;

		// correction for negative results.
		if ( rotateAng < 0 ) {
			rotateAng			=	360 + rotateAng;
		}
		if ( cntrlAng < 0 ) {
			cntrlAng			=	360 + cntrlAng;
		}

		// additional angle (to achieve monotonicity).
		double		addEps		=	1;
		// correction (depending on vecs' positions).
		if ( cntrlAng > rotateAng ) {
			if ( ( cntrlAng - rotateAng ) > 180 ) {
				addEps			=	-1;
			}
		}
		else {
			if ( ( rotateAng - cntrlAng ) < 180 ) {
				addEps			=	-1;
			}
		}

		rotateAng				+=	addEps;
		
		// rotate points.
		pt0.RotateAtDeg( outRotCenter, rotateAng );
		pt1.RotateAtDeg( outRotCenter, rotateAng );
		pt2.RotateAtDeg( outRotCenter, rotateAng );
		pt3.RotateAtDeg( outRotCenter, rotateAng );
		
		// check monotonicity.
		if ( VWCubicInterpolation::Is4PtsSequenceXMonotone( pt0, pt1, pt2, pt3, 0 ) ) {
			outIsFound			=	true;
		}
	}
	else {	// sequence is already X monotone.
		outIsFound				=	true;
	}
	
	// result rotation angle.
	return	rotateAng;
}

// tries to get a rotation angle that makes a 4-points sequence strictly Y monotone.
double VWCubicInterpolation::Make4PtsSequenceYMonotone( VWPoint2D& pt0, VWPoint2D& pt1, VWPoint2D& pt2, VWPoint2D& pt3,
														VWPoint2D& outRotCenter, bool& outIsFound )
{
	// init.
	double	rotateAng			=	0;
	outIsFound					=	false;
	outRotCenter				=	pt1;
	
	if ( ! VWCubicInterpolation::Is4PtsSequenceYMonotone( pt0, pt1, pt2, pt3, 0 ) ) {
	
		VWPoint2D	vecToRot	=	( pt0 - pt1 );
		vecToRot.Normalize();
		VWPoint2D	vecCntrl	=	( pt2 - pt1 );
		vecCntrl.Normalize();
		
		// get the angle to Ox.
		rotateAng				=	vecToRot.CalcAng360();
		double		cntrlAng	=	vecCntrl.CalcAng360();

		// additional angle (to achieve monotonicity).
		double		addEps		=	1;
		// correction (depending on vecs' positions).
		if ( cntrlAng > rotateAng ) {
			if ( ( cntrlAng - rotateAng ) > 180 ) {
				addEps			=	-1;
			}
		}
		else {
			if ( ( rotateAng - cntrlAng ) < 180 ) {
				addEps			=	-1;
			}
		}

		rotateAng				+=	addEps;
		
		// rotate points.
		pt0.RotateAtDeg( outRotCenter, rotateAng );
		pt1.RotateAtDeg( outRotCenter, rotateAng );
		pt2.RotateAtDeg( outRotCenter, rotateAng );
		pt3.RotateAtDeg( outRotCenter, rotateAng );
		
		// check monotonicity.
		if ( VWCubicInterpolation::Is4PtsSequenceYMonotone( pt0, pt1, pt2, pt3, 0 ) ) {
			outIsFound			=	true;
		}
	}
	else {	// sequence is already Y monotone.
		outIsFound				=	true;
	}
	
	// result rotation angle.
	return	rotateAng;
}