//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"


using namespace VWFC::Math;



// default epsilon for operator==
double	VWPoint2D::sEpsilon				= 0.0000001;

// squared default epsilon.
double	VWPoint2D::sSqrEpsilon			= 0.00000000000001;	// sqr( VWPoint2D::sEpsilon )

// negative epsilons.
double	VWPoint2D::sNegEpsilon			= -0.0000001;		// -VWPoint2D::sEpsilon.
double	VWPoint2D::sNegSqrEpsilon		= -0.00000000000001;// -VWPoint2D::sSqrEpsilon.

// raw (bigger) epsilon.
double	VWPoint2D::sRawEpsilon			= 0.0001;

// default epsilon for checking collinearity.
double	VWPoint2D::sEpsilonCollinear	= 0.01;

// default epsilon for checking nearness between angles in radians.
double	VWPoint2D::sEpsilonRadians		= 0.001745329252;	// 0.1 degrees.

VWPoint2D::VWPoint2D()
{
	this->x		= 0;
	this->y		= 0;
}

VWPoint2D::VWPoint2D(const WorldPt& src)
{
	this->x		= src.x;
	this->y		= src.y;
}

VWPoint2D::VWPoint2D(double x, double y)
{
	this->x		= x;
	this->y		= y;
}


VWPoint2D::VWPoint2D(const VWPoint2D& src)
{
	this->x		= src.x;
	this->y		= src.y;
}

VWPoint2D::~VWPoint2D()
{
}

void VWPoint2D::SetPoint(const WorldPt& pt)
{
	this->x		= pt.x;
	this->y		= pt.y;
}

void VWPoint2D::SetPoint(double x, double y)
{
	this->x		= x;
	this->y		= y;
}

void VWPoint2D::SetAngle(double radians)
{
	x = cos(radians);
	y = sin(radians);
}

void VWPoint2D::SetPointByAngle(double degAng, double length)
{
	this->SetAngle( degAng * kRadiansPerDegree );
	*this		*= length;
}

VWPoint2D& VWPoint2D::operator=(const VWPoint2D& src)
{
	this->SetPoint( src.x, src.y );
	return *this;
}

VWPoint2D& VWPoint2D::operator=(const WorldPt& src)
{
	this->SetPoint( src.x, src.y );
	return *this;
}

bool VWPoint2D::operator==(const VWPoint2D& p) const
{
	return this->Equal( p, VWPoint2D::sEpsilon );
}

bool VWPoint2D::operator!=(const VWPoint2D& p) const
{
	return !this->Equal( p, VWPoint2D::sEpsilon );
}

VWPoint2D VWPoint2D::operator+(const VWPoint2D& p) const
{
	return VWPoint2D(x + p.x, y + p.y);
}

VWPoint2D VWPoint2D::operator-(const VWPoint2D& p) const
{
	return VWPoint2D(x - p.x, y - p.y);
}

VWPoint2D VWPoint2D::operator*(double scalar) const
{
	return VWPoint2D((x * scalar), (y * scalar));
}

VWPoint2D VWPoint2D::operator/(double scalar) const
{
	return VWPoint2D((x / scalar), (y / scalar));
}

VWPoint2D VWPoint2D::operator-(void) const
{
	return VWPoint2D(-x, -y);
}

VWPoint2D& VWPoint2D::operator+=(const VWPoint2D& p)
{
	x += p.x;    y += p.y;    return *this;
}

VWPoint2D& VWPoint2D::operator-=(const VWPoint2D& p)
{
	x -= p.x;    y -= p.y;    return *this;
}

VWPoint2D& VWPoint2D::operator*=(double scalar)
{
	x *= scalar; y *= scalar; return *this;
}

VWPoint2D& VWPoint2D::operator/=(double scalar)
{
	x /= scalar; y /= scalar; return *this;
}

// dot product
double VWPoint2D::operator%(const VWPoint2D& p) const
{
	return this->x * p.x + this->y * p.y;
}

VWPoint2D::operator const WorldPt&() const
{
	// fool the compiler to allow us to modify member functoin of this class
	WorldPt*	pPt	= (WorldPt*) & fPoint;
	pPt->Set( x, y );
	return *pPt;
}


//////////////////////////////////////////////////////////////////////////
// math functions
//////////////////////////////////////////////////////////////////////////
double VWPoint2D::Magnitude() const
{
	return sqrt( x * x + y * y );
}

// return the squared distance from (0,0) to this point
double VWPoint2D::MagnitudeSquared() const
{
	return x * x + y * y;
}

// return true if the specified point is equal within the given epsilon to this point
bool VWPoint2D::Equal(const VWPoint2D& pt, double dEpsilon) const
{
	double	xx	= (x - pt.x);
	double	yy	= (y - pt.y);
	return xx * xx + yy * yy < dEpsilon * dEpsilon;
}

// calculate the distance from the specified point to this point
double VWPoint2D::DistanceTo(const VWPoint2D& pt) const
{
	return VWPoint2D::Distance( this->x, this->y, pt.x, pt.y );
}

double VWPoint2D::DistanceTo(double x, double y) const
{
	return VWPoint2D::Distance( this->x, this->y, x, y );
}

// calculate the squared distance from the specified point to this point.
double VWPoint2D::DistanceSquaredTo(double x, double y) const
{
	return VWPoint2D::DistanceSqare( this->x, this->y, x, y );
}

double VWPoint2D::DistanceSquaredTo(const VWPoint2D& pt) const
{
	return VWPoint2D::DistanceSqare( this->x, this->y, pt.x, pt.y );
}

// rotate this point at specified angle in degrees and center point
VWPoint2D& VWPoint2D::RotateAtDeg(const VWPoint2D& centerPt, double_gs dDegAngle)
{
	double_gs	dAng	= dDegAngle * kRadiansPerDegree;

	double		cenX	= centerPt.x;
	double		cenY	= centerPt.y;

	WorldPt		p;
	p.x					= this->x - cenX;
	p.y					= this->y - cenY;

	this->x				= cos( dAng ) * p.x + sin( dAng ) * p.y;
	this->y				= -sin( dAng ) * p.x + cos( dAng ) * p.y;

	this->x				+= cenX;
	this->y				+= cenY;

	return *this;
}

// rotate this point at specified angle in radians and center point
VWPoint2D& VWPoint2D::RotateAtRad(const VWPoint2D& centerPt, double_gs dRadAngle)
{
	double		cenX	= centerPt.x;
	double		cenY	= centerPt.y;

	WorldPt		p;
	p.x					= this->x - cenX;
	p.y					= this->y - cenY;

	this->x				= cos( dRadAngle ) * p.x + sin( dRadAngle ) * p.y;
	this->y				= -sin( dRadAngle ) * p.x + cos( dRadAngle ) * p.y;

	this->x				+= cenX;
	this->y				+= cenY;

	return *this;
}

// return perpendicular point of this point
VWPoint2D VWPoint2D::Perp() const
{
	return WorldPt( this->y, -this->x );
}

// normalize this vector
VWPoint2D& VWPoint2D::Normalize()
{
	double		len	= this->Magnitude();
	if ( len > 0.0 )
	{
		this->x	/= len;
		this->y	/= len;
	}
	return *this;
}

// normalizes this vector and returns its magnitude.
VWPoint2D& VWPoint2D::Normalize(double& outMagnitude)
{
	outMagnitude	= this->Magnitude();

	if ( outMagnitude > 0.0 )
	{
		this->x		/= outMagnitude;
		this->y		/= outMagnitude;
	}

	// result.
	return *this;
}

// get normalized of this vector.
VWPoint2D VWPoint2D::GetNormalized() const
{
	VWPoint2D	norm	= ( *this );
	norm.Normalize();

	// result.
	return norm;
}

// gets normalized of this vector and returns its magnitude.
VWPoint2D VWPoint2D::GetNormalized(double& outMagnitude) const
{
	VWPoint2D	norm	= ( *this );
	norm.Normalize( outMagnitude );

	// result.
	return norm;
}

// set this point to the perpendicullar of the specified point
VWPoint2D& VWPoint2D::Perp(const VWPoint2D& pt)
{
	this->x		= pt.y;
	this->y		= - pt.x;

	return *this;
}

// get the angle of this point's vector from -180 to 180 deg
double VWPoint2D::CalcAng180() const
{
	double				sinAng, cosAng, a;
	WorldPt3			w( 1.0, 0.0, 0.0 );
	// If the vector is a NULL vector, the result doesn't matter.
	double	 magnitude = this->Magnitude();
	if ( DoubleIsNearlyZero( magnitude ) )
		cosAng = 1;
	else
		cosAng = ::DotProduct( WorldPt3( this->x, this->y, 0 ), w ) / magnitude;
		
	if ( cosAng != 0.0 ) {
		sinAng	= Sqrt( 1.0 - sqr( cosAng ) );
		a		= atan( sinAng / cosAng ) * kDegreesPerRadian;
		if ( this->x < 0.0 ) {
			if ( this->y > 0.0 )
				a += 180.0;
			else if ( this->y < 0.0 )
				a = - ( 180.0 + a );
			if ( a == 0.0 )
				a = 180.0;
		}
		else if ( this->x > 0.0 && this->y < 0.0 )
			a = -a;
	}
	else
		a = this->y > 0.0 ? 90.0 : -90.0;

	return a;
}

// get the angle of this point's vector from 0 to 360 deg
double VWPoint2D::CalcAng360() const
{
	double	angle = this->CalcAng180();
	if ( angle < 0 ) 
		angle = angle + 360;

	return angle;
}

// get the angle between this point's vector and the specified vector (returned angle is between 0 and 180 degrees).
double VWPoint2D::CalcAngleTo(const VWPoint2D& vec) const
{
	return VWPoint2D::CalcAngleBetween( *this, vec ) * kDegreesPerRadian;	// from radians to degrees.
}

// set this points as the center of a circle passing thru 3 given points
VWPoint2D& VWPoint2D::ThreePtCenter(const VWPoint2D& pt1, const VWPoint2D& pt2, const VWPoint2D& pt3)
{
	VWPoint2D		chord1_mid		= ((pt1 + pt2) / 2);
	VWPoint2D		chord2_mid		= ((pt2 + pt3) / 2);
	VWPoint2D		spoke1_end		= chord1_mid + (pt1 - pt2).Perp();
	VWPoint2D		spoke2_end		= chord2_mid + (pt2 - pt3).Perp();
	
	WorldPt			temp_pt( 0, 0 );

	Boolean			bParallel, bIntOnLines;
	::GS_LineLineIntersect( gCBP, chord1_mid, spoke1_end, chord2_mid, spoke2_end, bParallel, bIntOnLines, temp_pt );

	this->SetPoint( temp_pt.x, temp_pt.y );

	return *this;
}

// translates this point into a coordinate system defined by 2 other points.
VWPoint2D& VWPoint2D::RelativeCoords(const VWPoint2D& pt1, const VWPoint2D& pt2)
{
	VWPoint2D	p		= (*this) - pt1;
	double_gs	ang		= p.CalcAng180() - (pt2 - pt1).CalcAng180();
	this->SetPointByAngle( ang, p.Magnitude() );

	return *this;
}

// Cross product magnitude is primarily used for determining the left/right orientation of two vectors.
double VWPoint2D::CrossProductMagnitude(const VWPoint2D& pt) const
{
	return this->x * pt.y - this->y * pt.x;
}

//The mathematical definition of Dot Product is:
//		|a||b|cos theta or 
//		the magnitude of 'a' times the magnitude of 'b' times the cosine of the angle between 'a' and 'b'
double VWPoint2D::DotProduct(const VWPoint2D& pt) const
{
	return this->x * pt.x + this->y * pt.y;
}

// whether the current point is on the left of vector provided as parameter
bool VWPoint2D::IsPointOnTheRightOfVector(const VWPoint2D& vec) const
{
	// Perp() generates a vector on the right of the current.
	// If the point provided as parameter lies on the current vector then
	// it is reported as being situated on the right side of the vector.
	const double dSign = MathUtils::Sign( vec.Perp() % *this );

	return (dSign > 0.0);
}

//////////////////////////////////////////////////////////////////////////
// static point functoins
//////////////////////////////////////////////////////////////////////////
double VWPoint2D::TriArea(const VWPoint2D& pt1, const VWPoint2D& pt2, const VWPoint2D& pt3)
{
	return (pt1.x*pt2.y + pt2.x*pt3.y + pt3.x*pt1.y - pt1.y*pt2.x - pt2.y*pt3.x - pt3.y*pt1.x) / 2;
}

// calculated the are of the specified triangle
double VWPoint2D::TriArea(	double pt1x, double pt1y,
							double pt2x, double pt2y,
							double pt3x, double pt3y)
{
	return (pt1x*pt2y + pt2x*pt3y + pt3x*pt1y - pt1y*pt2x - pt2y*pt3x - pt3y*pt1x) / 2;
}

// calculates the area of triangle using the side/edge lengths (Heron's formula).
/*static*/ double VWPoint2D::TriArea(double edgeLen0, double edgeLen1, double edgeLen2)
{
	double	halfPerim	= ( ( edgeLen0 + edgeLen1 + edgeLen2 ) * 0.5 );

	// result.
	return	( sqrt( halfPerim * ( halfPerim - edgeLen0 ) * ( halfPerim - edgeLen1 ) * ( halfPerim - edgeLen2 ) ) );
}

// calculated the distance between specified two points
double VWPoint2D::Distance(double x1, double y1, double x2, double y2)
{
	double	x	= x2 - x1;
	double	y	= y2 - y1;
	return sqrt( x*x + y*y );
}

// calculated the distance between specified two points
double VWPoint2D::DistanceSqare(double x1, double y1, double x2, double y2)
{
	double	x	= x2 - x1;
	double	y	= y2 - y1;
	return ( x*x + y*y );
}

// calculates the barycentric coordinates of the circumcircle of a triangle (passed triangle's edge vectors).
// returns whether it can be calculated (non-degenerate triangle).
/*static*/ bool VWPoint2D::GetBarycentricCoordsOfTriCircumCenter(const VWPoint2D& vecEdge01, const VWPoint2D& vecEdge12, const VWPoint2D& vecEdge20,
																 double& outB0, double& outB1, double& outB2)
{
	// init.
	bool		exists	= false;

	double		d0		= - ( vecEdge01.DotProduct( vecEdge20 ) );	// (vec01.vec02)=(vec01.(-vec20))=-(vec01.vec20).
	double		d1		= - ( vecEdge12.DotProduct( vecEdge01 ) );	// (vec12.vec10)=(vec12.(-vec01))=-(vec12.vec01).
	double		d2		= - ( vecEdge20.DotProduct( vecEdge12 ) );	// (vec20.vec21)=(vec20.(-vec12))=-(vec20.vec12).

	double		c0		= ( d1 * d2 );
	double		c1		= ( d2 * d0 );
	double		c2		= ( d0 * d1 );
	double		sumc	= ( c2 + c1 + c0 );

	if ( ! MathUtils::Equalish( sumc, 0.0, VWPoint2D::sEpsilon ) )	// prevent division by zero.
	{
		double	cs		= ( 0.5 / sumc );

		outB0	= ( c2 + c1 ) * cs;
		outB1	= ( c2 + c0 ) * cs;
		outB2	= ( c0 + c1 ) * cs;

		exists	= true;
	}

	// result.
	return	( exists );
}

// find the center and squared radius of triangle circumcircle. return whether it exists (triangle points are not collinear).
bool VWPoint2D::GetTriCircumCircle(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, VWPoint2D& outCenPt, double& outSqrRad)
{
	VWPoint2D	vec01	= ( pt1 - pt0 );
	VWPoint2D	vec12	= ( pt2 - pt1 );
	VWPoint2D	vec20	= ( pt0 - pt2 );

	double		b0, b1, b2;

	// calculate the barycentric coordinates of the circum center.
	bool		exists	= VWPoint2D::GetBarycentricCoordsOfTriCircumCenter( vec01, vec12, vec20, b0, b1, b2 );

	if ( exists )
	{
		// circum center.
		outCenPt.x		= ( ( b0 * pt0.x )  + ( b1 * pt1.x )  + ( b2 * pt2.x ) );
		outCenPt.y		= ( ( b0 * pt0.y )  + ( b1 * pt1.y )  + ( b2 * pt2.y ) );

		// circum squared radius.
		outSqrRad		= VWPoint2D::DistanceSqare( outCenPt.x, outCenPt.y, pt0.x, pt0.y );
	}

	// result.
	return	( exists );
}

// calculates the squared radius of the inscribed circle in a triangle (passed the lengths of triangle's edges). return whether it exists.
/*static*/ bool VWPoint2D::GetTriInscribedCircleRadius(double edge0Len, double edge1Len, double edge2Len, double& outSqrRad)
{
	// init.
	bool		exists		= false;

	double		perim		= ( edge0Len + edge1Len + edge2Len ) * 0.5;

	if ( ! MathUtils::Equalish( perim, 0.0, VWPoint2D::sEpsilon ) )	// prevent division by zero.
	{
		// get squared radius.
		outSqrRad			= ( ( perim - edge0Len ) * ( perim - edge1Len ) * ( perim - edge2Len ) ) / perim;

		exists				= true;
	}

	return	( exists );
}

// find the squared radius of triangle inscribed circle. return whether it exists.
bool VWPoint2D::GetTriInscribedCircleRadius(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, double& outSqrRad)
{
	double		len0		= pt0.DistanceTo( pt1 );
	double		len1		= pt1.DistanceTo( pt2 );
	double		len2		= pt2.DistanceTo( pt0 );

	// result - calculate the squared radius of triangle inscribed circle.
	return	( VWPoint2D::GetTriInscribedCircleRadius( len0, len1, len2, outSqrRad ) );
}

// find the center of triangle inscribed circle.
void VWPoint2D::GetTriInscribedCircleCenter(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, VWPoint2D& outCenPt)
{
	// get center.
	VWPoint2D	dir1	= ( pt1 - pt0 );
	dir1.Normalize();
	VWPoint2D	dir2	= ( pt2 - pt0 );
	dir2.Normalize();
	VWPoint2D	dir3	= ( pt2 - pt1 );
	dir3.Normalize();

	VWPoint2D	dirB1	= ( dir1 + dir2 );
	VWPoint2D	dirB2	= ( dir3 - dir1 );
	
	dirB1.Normalize();
	dirB2.Normalize();

	VWLine2D	lineB1( pt0, dirB1 );
	outCenPt			= pt1 + dirB2 * lineB1.Distance( pt1 );
}

// get an estimation of the triangle aspect ratio. ratio can not be estimated for degenerate triangles.
bool VWPoint2D::TriAspectRatioEval(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, double& ratioEval)
{
	// init.
	bool			hasRatio	= false;

	// get the vectors of the tiangle's edges.
	VWPoint2D		vec01		= ( pt1 - pt0 );
	VWPoint2D		vec12		= ( pt2 - pt1 );
	VWPoint2D		vec20		= ( pt0 - pt2 );

	double			b0, b1, b2;

	// calculate the barycentric coordinates of the circum center.
	if ( VWPoint2D::GetBarycentricCoordsOfTriCircumCenter( vec01, vec12, vec20, b0, b1, b2 ) )
	{
		double		inscribedSqrRadius;

		// calculate squared radius of the inscribed circle.
		if ( VWPoint2D::GetTriInscribedCircleRadius( vec01.Magnitude(), vec12.Magnitude(), vec20.Magnitude(), inscribedSqrRadius ) )
		{
			if ( inscribedSqrRadius > VWPoint2D::sEpsilon )		// prevent division by zero.
			{
				// get circum center.
				double			outCenPtX		= ( ( b0 * pt0.x )  + ( b1 * pt1.x )  + ( b2 * pt2.x ) );
				double			outCenPtY		= ( ( b0 * pt0.y )  + ( b1 * pt1.y )  + ( b2 * pt2.y ) );

				// evaluate the aspect ratio (can be done!).
				ratioEval		= ( VWPoint2D::DistanceSqare( outCenPtX, outCenPtY, pt0.x, pt0.y ) / inscribedSqrRadius );

				hasRatio		= true;
			}
		}
	}

	// result.
	return	( hasRatio );
}

// check if given 3 points are collinear.
bool VWPoint2D::ArePointsCollinear(const VWPoint2D& pt0, const VWPoint2D& pt1, const VWPoint2D& pt2, double dEpsilon)
{
	// get two vectors that will be checked for collinearity.
	// since this is a direction test the vectors must be normalized.
	// otherwise, if they differ greatly in length the result becomes unstable.

	const VWPoint2D	vecA	= ( pt0 - pt1 ).Normalize();
	const VWPoint2D	vecB	= ( pt2 - pt1 ).Normalize();

	return MathUtils::Equalish( vecA.CrossProductMagnitude( vecB ), 0.0, dEpsilon );
}

// get the angle between two vectors (returned angle is in radians between 0 and PI).
/*static*/ double VWPoint2D::CalcAngleBetween(const VWPoint2D& vec1, const VWPoint2D& vec2, bool areNormalized/*= false*/)
{
	// init.
	double		resAngle	= 0.0;

	// get the product of magnitudes.
	double		divider		= 1.0;
	if ( ! areNormalized )
	{
		divider				= ( vec1.Magnitude() * vec2.Magnitude() );
	}

	if ( MathUtils::Greaterish( divider, 0.0, VWPoint2D::sEpsilon ) )
	{
		// get angle between vectors.

		double	cosAng		= ( vec1.DotProduct( vec2 ) / divider );	// get cosine.

		// ensure boundary cases (the value is in interval [-1, 1]).
		if		( cosAng <= -1.0 )		// boundary case 1: angle is PI (180 degrees).
		{
			resAngle		= ( MathUtils::PI );

			VWFC_ASSERT( MathUtils::GEish( cosAng, -1.0, VWPoint2D::sEpsilon ) );
		}
		else if	( cosAng >= 1.0 )		// boundary case 2: angle is 0 (0 degrees).
		{
			resAngle		= 0.0;

			VWFC_ASSERT( MathUtils::LEish( cosAng, 1.0, VWPoint2D::sEpsilon ) );
		}
		else
		{
			resAngle		= acos( cosAng );
		}
	}
	// else: the product of magnitudes is zero, then one or the other of the vectors is with length zero, so return zero angle.

	// result.
	return	( resAngle );	// in radians.
}
