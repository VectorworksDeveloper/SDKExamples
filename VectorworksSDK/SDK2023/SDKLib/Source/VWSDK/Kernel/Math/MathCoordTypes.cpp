//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Implements support for most of the standard geometric data types used
//	in MiniCAD code. Much of the contents of this file requires ALTURA
//	Fixed & Fract math support under Windows, so it cannot be inlined.
//


#include "StdHeaders.h"	// Must be first non-comment line.  See StdHeaders.h for explanation.



// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE



/////////////////////////
// TEMPORARY RELOCATION
/////////////////////////
//
// These were in BasicMath.X.h and were causing our TOC on the Mac to grow wildly
// because each constant took up a TOC slot for each file they were included into.
//
// We should move them into a BasicMath.cpp file but it needs to be integrated
// with the SDK so I'm taking it slow and putting it here - non optimal - PCP
//

#if defined(_MINICAD_) && !_WINDOWS
	const extern double PI				= pi;
#else
const extern double PI					= 3.141592653589793239;

/* XXX: This value of pi, being written in decimal, is slightly less accurate than using
	pi() -- inaccurate enough that cos(PI/2.0) does not quite equal zero (using extended
	numbers).  However, because of the way Symantec C++ implements globals in code resources,
	we can't use the pi() form, since there's no such thing as static constructors in a
	Symantec C++ code resource, so for the time being we're forced to keep this slightly
	inaccurate form for them.
*/
#endif

const extern double kDegreesPerRadian	= 180.0 / PI;
const extern double kRadiansPerDegree	= PI / 180.0;
const extern double kGradiansPerDegree	= 100.0 / 90.0;
const extern double kDegreesPerGradian	= 90.0 / 100.0;

const extern double kHalfPi				=       PI / 2.0;
const extern double kThreePiOver2		= 3.0 * PI / 2.0;
const extern double kTwoPi				= 2.0 * PI;


#if GS_SDK_VW8_COMPATIBLE

// don't use these anymore, use constants above
const extern double radToDeg 			= kDegreesPerRadian;
const extern double degToRad 			= kRadiansPerDegree;

const extern double halfPi				= kHalfPi;
const extern double twoPi				= kTwoPi;

#endif // GS_SDK_VW8_COMPATIBLE


//----------------------------------------------------------------------------------------
// Floating Point WorldCoord Constants (see Mark with questions)
//----------------------------------------------------------------------------------------

// kWorldCoordsPerInch
//
// As of Bernini A5, one internal WorldCoord is now equivalent to one world millimeter.
const extern double kWorldCoordsPerInch = 25.4;         // mm
const extern double kWorldCoordsPerMM   = 1;

const extern double kInchesPerWorldCoord = 1 / kWorldCoordsPerInch;
const extern double kWorldCoordsPerInch_Squared = kWorldCoordsPerInch * kWorldCoordsPerInch;



// kWorldCoordsPerDecimicron
//
// Conversion factor for decimicrons, which were used in VW 8.x.x plug-in objects. This is
// a special purpose constant and has no widespread utility outside of file format floating point
// value conversion.
const extern double kDecimicronsPerInch = 254000.0;
const extern double kWorldCoordsPerDecimicron = kWorldCoordsPerInch / kDecimicronsPerInch;


// kTypographicalPointsPerInch
//
// The correct value of an American typographical points per inch constant should
// be 72.46376812, but the standard computer industry practice is to approximate it
// as 72.0. - PCP
const extern double kTypographicalPointsPerInch = 72.0;



// kMaximumTotalDigitsOfPrecision
//
// The maximum number of digits we will display to the user.
// This is 2 digits less than
// Float.h:  #define DBL_DIG 15 /* # of decimal digits of precision */
// Often a floating point value (one that which represents 1.2 for example) is an approximation.
// The approximation is usually very very close to the exact value it is meant to represent.
// The extra 2 digits we have here (15 - 13) let us appear to be exact at all times to the user,
// even when there's a little internal drift.
const extern short kMaximumTotalDigitsOfPrecision = 13;    // 123456.7890123


// kMaximumFractionalDigitsOfPrecision
//
// The maximum number of digits we will display to the user to the right of the decimal point.
//
// Note, we allow 15 for VectorScript Export. kMaximumFractionalDigitsOfPrecision is for general display to the user. [MAF 12/11/00]
const extern short kMaximumFractionalDigitsOfPrecision = 10;    // 7.1234567890


// kMaxLegalWorldCoord
//
// kMaxLegalWorldCoord is the maximum legal WorldCoord value that VectorWorks will recognize
// internally before it starts complaining and dropping objects.
//
// kMaxLegalWorldCoord is approximately (somewhat less than) the cube root of
// DBL_MAX (~1.79e+308) allowing the squares of any three legal WorldCoords to be added together.
// If we did not impose this limit, then we would not be able to reliably find the
// distance between two 3D points or the area or volume of an object without doing our computations
// in a longer data type, such as a 128 bit long double. Technically the cube root of DBL_MAX
// (1.7976931348623158e+308) is 1.somethingE102ish, but we went with e100 because it was convenient
// and that's close to (if not exactly) what AutoCAD does.
//
// Any coordinate whose magnitude is greater than kMaxLegalWorldCoord is considered illegal.
// Any coordinate that might have math performed on it should never be greater than kMaxLegalWorldCoord.
// Objects containing coordinate values greater than kMaxLegalWorldCoord are potentially subject to removal.
// - PCP 1/3/00  (this block comment modified some by [MAF 1/27/00]).
const extern WorldCoord kMaxLegalWorldCoord =  1.0E100;

// kMaxOutOfRangeWorldCoord
// (previously kMaxCoord [MAF 11/30/00])
//
// kMaxOutOfRangeWorldCoord is NOT the same as kMaxLegalWorldCoord. kMaxOutOfRangeWorldCoord should only be used for very special 
// non math-related purposes. kMaxOutOfRangeWorldCoord is NOT a legal WorldCoord.
const extern WorldCoord kMaxOutOfRangeWorldCoord =  DBL_MAX;


// kNearlyEqualEpsilonForWorldCoords
//
// kNearlyEqualEpsilonForDoubles is the very small number we use to decide if 2 WorldCoords
// are virtually equal. For now we're saying that it's the same epsilon we use for straight
// double comparisons. 
//
// NOTE! You generally should NOT be using kNearlyEqualEpsilonForWorldCoords directly because it 
// does not take into account the magnitude of the values you're working with. You should be using 
// functions that use (directly or indirectly) kNearlyEqualEpsilonForWorldCoords , namely:
//
//		Boolean WorldCoordsAreNearlyEqual(WorldCoord n1, WorldCoord n2);
//		Boolean WorldCoordIsNearlyZero(WorldCoord n);
//		Boolean WorldPt::operator==(const WorldPt& p);
//		Boolean WorldRect::operator==(const WorldRect& r);
//		Boolean WorldPt3::operator==(const WorldPt3& p);
//		Boolean WorldCube::operator==(const WorldCubePt3& p);
const extern double kNearlyEqualEpsilonForWorldCoords = kNearlyEqualEpsilonForDoubles;


// kWorldCoordBumpEpsilon
//
// Some code (much to my chagrin) needs "a slightly higher WorldCoord". We use bumpEpsilon for that 
// which is a very small number, but decidedly bigger than the level of granularity we define for 
// nearly equal WorldCoords. [MAF 1/11/00]
//
// NOTE! You generally should NOT be using kWorldCoordBumpEpsilon directly because it does not 
// take into account the magnitude of the values you're working with. You should be using 
// functions that use kWorldCoordBumpEpsilon, namely:
//
//     inline WorldCoord WorldCoordBumpedHigher(WorldCoord n);
//     inline WorldCoord WorldCoordBumpedLower(WorldCoord n);
const extern double kWorldCoordBumpEpsilon = kNearlyEqualEpsilonForWorldCoords * 100;

const extern WorldRect kEmptyWorldRect = WorldRect();

const extern double kNearlyEqualEpsilonForRadians = 1e-08;

Boolean RadiansAreNearlyEqual(Radians angle1, Radians angle2)
{
	Boolean areEqual = false;

	//Check the value of the angle parameters - a value of NaN
	//can cause an infinite loop in this routine. [AAO, 1-26-04]
	if(VERIFYN(kAyo, !::IsIllegal(angle1) && !::IsIllegal(angle2))) {
		// this code calculates the difference in values between -PI and PI
		double diff = ((angle2 - angle1) + PI) / kTwoPi;
		diff = ((diff - floor(diff)) * kTwoPi) - PI;
		if (Abs(diff) <= kNearlyEqualEpsilonForRadians)
			areEqual = true; 
	}

	return areEqual;
}

//----------------------------------------------------------------------------------------

#if BUG && !_MINICAD_EXTERNAL_ && !_GSESDK_
void WorldPt::Dump(const TProgrammer &toWhom, TDumpDevice &dd, Sint32 indent) const
{
	dd.printf(toWhom, indent, "WorldPt:\n");
	dd.printf(toWhom, ++indent, "x = %ld, y = %ld\n", x, y);
}
#endif



// ===== 3-D Types

// -- FloatPt3
	void GS_API FloatPt3::Set(WorldCoord inx, WorldCoord iny, WorldCoord inz)
		{ x = DemoteTo<float>(kEveryone, inx); y = DemoteTo<float>(kEveryone, iny); z = DemoteTo<float>(kEveryone, inz);}

	void GS_API FloatPt3::Set(const WorldPt3& in)
		{ this->Set(in.x, in.y, in.z); }


// -- WorldPt3

	WorldPt3 GS_API WorldPt3::operator/(double s)	 const	{ return WorldPt3((x / s), (y / s), (z / s)); }
	WorldPt3 GS_API WorldPt3::Normal() const				{ WorldPt3 r = *this; r.Normalize(); return r; }
	WorldPt3 GS_API WorldPt3::Abs() const					{ return WorldPt3(::Abs(x), ::Abs(y), ::Abs(z)); }

#if TEST && GS_USE_CLASS_DEBUGGING
void WorldPt3::AssertValid(const TProgrammer &toWhom, Bool8 bCheckMem) const
{ 
	if (bCheckMem)
		ASSERTPOINTER(toWhom, this, sizeof(WorldPt3));
}
#endif

#if BUG && !_MINICAD_EXTERNAL_ && !_GSESDK_
void WorldPt3::Dump(const TProgrammer &toWhom, TDumpDevice &dd, Sint32 indent) const
{
	dd.printf(toWhom, indent, "WorldPt3:\n");
	dd.printf(toWhom, ++indent, "x = %ld, y = %ld, z = %ld\n", x, y, z);
}
#endif



// -- WorldCube
void GS_API WorldCube::Set(const WorldPt3& a, const WorldPt3& b)
{
	// We have to do a strict compare here, as our test of cubes being empty relies
	// on the values being ordered properly.
	if (a.y > b.y) { top = a.y; bottom = b.y; } else { top = b.y; bottom = a.y;}
	if (a.x > b.x) { right = a.x; left = b.x; } else { right = b.x; left = a.x;}
	if (a.z > b.z) { front = a.z; back = b.z; } else { front = b.z; back = a.z;}
}

GS_API WorldCube::WorldCube(const WorldPt3& a, const WorldPt3& b)
{
	this->Set(a, b);
}


// This was incorrect code. We can't use the "fuzzy" compares, because IsEmpty() -- for speed reasons -- uses the
// > operator. So if a is greater than b but within epsilon, it swaps, and then min > max which returns true for IsEmpty().
// The Set function was just awful. Never mind using the funcs rather than operators;
// in half the cases it didn't even set the values it's supposedly setting.
/*	GS_API WorldCube::WorldCube(const WorldPt3& a, const WorldPt3& b)
		{ if (WorldCoord1_GT_WorldCoord2(a.y, b.y)) { top = a.y, bottom = b.y; } else { top = b.y, bottom = a.y;} 
		  if (WorldCoord1_GT_WorldCoord2(a.x, b.x)) { right = a.x, left = b.x; } else { right = b.x, left = a.x;} 
		  if (WorldCoord1_GT_WorldCoord2(a.z, b.z)) { front = a.z, back = b.z; } else { front = b.z, back = a.z;}  }
	void GS_API WorldCube::Set(const WorldPt3& a, const WorldPt3& b)
		{ WorldCoord i, j;
		  if (WorldCoord1_GT_WorldCoord2(a.y, b.y)) { i = a.y, j = b.y; } else { i = b.y, j = a.y; top = i, bottom = j;} 
		  if (WorldCoord1_GT_WorldCoord2(a.x, b.x)) { i = a.x, j = b.x; } else { i = b.x, j = a.x; right = i, left = j;} 
		  if (WorldCoord1_GT_WorldCoord2(a.z, b.z)) { i = a.z, j = b.z; } else { i = b.z, j = a.z; front = i, back = j;}  }
*/
	WorldCube GS_API WorldCube::Union(const WorldCube &c) const
		{ WorldCube r = *this; r.Unite(c); return r; }


// These cannot be compiled under MFC.

void GS_API CubeVerts::GetBoundingCube(WorldCube& wc) const
{
	wc.MakeEmpty();
	for_i(8)
		wc.Unite((*this)[i]);
}

//////////////////////////////////////////////////
void GS_API CubeVerts::Transform(const TransformMatrix& inMat)
{
	for_i(8)
		PointTransformN((*this)[i], inMat, (*this)[i]);
}

//////////////////////////////////////////////////
void GS_API CubeVerts::InverseTransform(const TransformMatrix& inMat)
{
	for_i(8)
		InversePointTransformN((*this)[i], inMat, (*this)[i]);
}

//////////////////////////////////////////////////
void GS_API Ray::Transform(const TransformMatrix &mat)
{
	PointTransformN(vertex, mat, vertex);
	VectorTransformN(direction, mat, direction);
}

//////////////////////////////////////////////////
void GS_API Ray::InverseTransform(const TransformMatrix &mat)
{
	InversePointTransformN(vertex, mat, vertex);
	InverseVectorTransformN(direction, mat, direction);
}

//////////////////////////////////////////////////
bool GS_API WorldRectVerts::IsAPoint() const
{
	bool bIsAPoint = false;

	if (!this->IsEmpty())
		bIsAPoint = topLeft == topRight && topLeft == bottomLeft && topLeft == bottomRight;

	return bIsAPoint;
}

//////////////////////////////////////////////////
bool GS_API WorldRectVerts::IsEmpty() const
{
	WorldPt wpt(kMaxLegalWorldCoord, kMaxLegalWorldCoord);
	return topLeft == wpt && topRight == wpt && bottomLeft == wpt && bottomRight == wpt;
}

//////////////////////////////////////////////////
void GS_API WorldRectVerts::MakeEmpty()
{
	WorldPt wpt(kMaxLegalWorldCoord, kMaxLegalWorldCoord);
	topLeft		= wpt;
	topRight	= wpt;
	bottomLeft	= wpt;
	bottomRight	= wpt;
}

//////////////////////////////////////////////////
void GS_API WorldRectVerts::Set(const WorldRect& inR)
{
	if (inR.IsEmpty()) {
		this->MakeEmpty();
	}
	else {
		topLeft		= inR.TopLeft();
		topRight	= inR.TopRight();
		bottomLeft	= inR.BotLeft();
		bottomRight	= inR.BotRight();
	}
}

//////////////////////////////////////////////////
void GS_API WorldRectVerts::SetRotatedRect(const WorldPt& pt1, const WorldPt& pt2, const TransformMatrix& mat)
{
	WorldPt xi; 
	xi.Set(mat.v2.i.x, mat.v2.i.y);
	WorldPt xj; 
	xj.Set(mat.v2.j.x, mat.v2.j.y);
 	topRight		= pt2;
	bottomLeft		= pt1;
	WorldPt hyp	= pt2 - pt1;
	bottomRight		= pt1 + xi * DotProduct(xi, hyp);
	topLeft			= pt1 + xj * DotProduct(xj, hyp);
}

//////////////////////////////////////////////////
void GS_API WorldRectVerts::GetBoundingBox(WorldRect& wr) const
{
	if (this->IsEmpty()) {
		wr.MakeEmpty();
	}
	else {
		wr.left		= min(min(topLeft.x, topRight.x), min(bottomLeft.x, bottomRight.x));
		wr.top		= max(max(topLeft.y, topRight.y), max(bottomLeft.y, bottomRight.y));
		wr.right	= max(max(topLeft.x, topRight.x), max(bottomLeft.x, bottomRight.x));
		wr.bottom	= min(min(topLeft.y, topRight.y), min(bottomLeft.y, bottomRight.y));
	}
}

//////////////////////////////////////////////////
void GS_API WorldRectVerts::Transform(const TransformMatrix &mat)
{
	if (!this->IsEmpty()) {
		Point2DTransform(topLeft, mat, topLeft);
		Point2DTransform(topRight, mat, topRight);
		Point2DTransform(bottomLeft, mat, bottomLeft);
		Point2DTransform(bottomRight, mat, bottomRight);
	}
}

//////////////////////////////////////////////////
void GS_API WorldRectVerts::InverseTransform(const TransformMatrix &mat)
{
	if (!this->IsEmpty()) {
		InversePoint2DTransform(topLeft, mat, topLeft);
		InversePoint2DTransform(topRight, mat, topRight);
		InversePoint2DTransform(bottomLeft, mat, bottomLeft);
		InversePoint2DTransform(bottomRight, mat, bottomRight);
	}
}


//////////////////////////////////////////////////
void WorldRectVerts::Unite(const WorldRectVerts cwrv)
{
	*this = this->Union(cwrv);
}

//////////////////////////////////////////////////
WorldRectVerts WorldRectVerts::Union(const WorldRectVerts cwrv) const
{
	WorldRectVerts newRect;

	if (this->IsEmpty()) {
		newRect = cwrv;
	}
	else if (cwrv.IsEmpty()) {
		newRect = *this;
	}
	else {
		Vector2 xDir(1, 0);
		Vector2 yDir(0, 1);
		WorldCoord maxX = 0;
		WorldCoord maxY = 0;
		WorldCoord minX = 0;
		WorldCoord minY = 0;
		WorldCoord tempX, tempY;
		
		if (this->topRight != this->topLeft)  {
			xDir = (this->topRight - this->topLeft).Normal();
		}

		if (this->topLeft != this->bottomLeft)  {
			yDir = (this->topLeft - this->bottomLeft).Normal();
		}

		tempX = (this->topLeft - this->topLeft).Dot(xDir);
		maxX = (tempX > maxX) ? tempX : maxX;
		minX = (tempX < minX) ? tempX : minX;
		tempY = (this->topLeft - this->topLeft).Dot(yDir);
		maxY = (tempY > maxY) ? tempY : maxY;
		minY = (tempY < minY) ? tempY : minY;

		tempX = (this->topRight - this->topLeft).Dot(xDir);
		maxX = (tempX > maxX) ? tempX : maxX;
		minX = (tempX < minX) ? tempX : minX;
		tempY = (this->topRight - this->topLeft).Dot(yDir);
		maxY = (tempY > maxY) ? tempY : maxY;
		minY = (tempY < minY) ? tempY : minY;

		tempX = (this->bottomLeft - this->topLeft).Dot(xDir);
		maxX = (tempX > maxX) ? tempX : maxX;
		minX = (tempX < minX) ? tempX : minX;
		tempY = (this->bottomLeft - this->topLeft).Dot(yDir);
		maxY = (tempY > maxY) ? tempY : maxY;
		minY = (tempY < minY) ? tempY : minY;

		tempX = (this->bottomRight - this->topLeft).Dot(xDir);
		maxX = (tempX > maxX) ? tempX : maxX;
		minX = (tempX < minX) ? tempX : minX;
		tempY = (this->bottomRight - this->topLeft).Dot(yDir);
		maxY = (tempY > maxY) ? tempY : maxY;
		minY = (tempY < minY) ? tempY : minY;

		tempX = (cwrv.topLeft - this->topLeft).Dot(xDir);
		maxX = (tempX > maxX) ? tempX : maxX;
		minX = (tempX < minX) ? tempX : minX;
		tempY = (cwrv.topLeft - this->topLeft).Dot(yDir);
		maxY = (tempY > maxY) ? tempY : maxY;
		minY = (tempY < minY) ? tempY : minY;

		tempX = (cwrv.topRight - this->topLeft).Dot(xDir);
		maxX = (tempX > maxX) ? tempX : maxX;
		minX = (tempX < minX) ? tempX : minX;
		tempY = (cwrv.topRight - this->topLeft).Dot(yDir);
		maxY = (tempY > maxY) ? tempY : maxY;
		minY = (tempY < minY) ? tempY : minY;

		tempX = (cwrv.bottomLeft - this->topLeft).Dot(xDir);
		maxX = (tempX > maxX) ? tempX : maxX;
		minX = (tempX < minX) ? tempX : minX;
		tempY = (cwrv.bottomLeft - this->topLeft).Dot(yDir);
		maxY = (tempY > maxY) ? tempY : maxY;
		minY = (tempY < minY) ? tempY : minY;

		tempX = (cwrv.bottomRight - this->topLeft).Dot(xDir);
		maxX = (tempX > maxX) ? tempX : maxX;
		minX = (tempX < minX) ? tempX : minX;
		tempY = (cwrv.bottomRight - this->topLeft).Dot(yDir);
		maxY = (tempY > maxY) ? tempY : maxY;
		minY = (tempY < minY) ? tempY : minY;

		newRect.topLeft = this->topLeft + (xDir * minX) + (yDir * maxY);
		newRect.topRight = this->topLeft + (xDir * maxX) + (yDir * maxY);
		newRect.bottomLeft = this->topLeft + (xDir * minX) + (yDir * minY);
		newRect.bottomRight = this->topLeft + (xDir * maxX) + (yDir * minY);
	}

	return newRect;
}

//////////////////////////////////////////////////
void WorldRectVerts::Outset(WorldCoord dI, WorldCoord dJ)
{
	WorldPt wptI = topLeft - bottomLeft;
	WorldPt wptJ = bottomRight - bottomLeft;

	bool bIz = wptI.IsZero();
	bool bJz = wptJ.IsZero();

	if (bIz && bJz) {
		wptI.Set(1,0);
		wptJ.Set(0,1);
	}
	else if (bIz) {
		wptJ /= wptJ.Magnitude();
		wptI = wptJ.Perpendicular();
	}
	else if (bJz) {
		wptI /= wptI.Magnitude();
		wptJ = wptI.Perpendicular();
	}
	else {
		wptI /= wptI.Magnitude();
		wptJ /= wptJ.Magnitude();
	}

	WorldPt wptIOff = wptI * dI;
	WorldPt wptJOff = wptJ * dJ;

	topLeft		+= wptIOff - wptJOff;
	topRight	+= wptIOff + wptJOff;
	bottomLeft	+= -wptIOff - wptJOff;
	bottomRight	+= -wptIOff + wptJOff;
}

//////////////////////////////////////////////////
void WorldRectVerts::Offset(const WorldPt& inwpt)
{
	if (!this->IsEmpty()) {
		topLeft		+= inwpt;
		topRight	+= inwpt;
		bottomLeft	+= inwpt;
		bottomRight	+= inwpt;
	}
}

//////////////////////////////////////////////////
WorldRectVerts& WorldRectVerts::operator*=(double scale) 
{
	if (!this->IsEmpty()) {
		topLeft		*= scale; 
		topRight	*= scale; 
		bottomLeft	*= scale; 
		bottomRight	*= scale;
	}
			
	return *this;
}

//////////////////////////////////////////////////
bool WorldRectVerts::IsFlipped() const
{
	bool bIsFlipped = false;

	if (!this->IsEmpty()) {
		WorldPt p1 = topLeft - topRight;
		WorldPt p2 = bottomLeft - topLeft;
		bIsFlipped = (p2.y*p1.x - p1.y*p2.x < 0);
	}

	return bIsFlipped;
}

//////////////////////////////////////////////////
void GS_API RotateWorldRect(const TransformMatrix &matIn, const WorldRect &cIn, WorldRectVerts &verts)
{
	const TransformMatrix mat = matIn;  // [MAF FP Speedup, 2/18/01]
	const WorldRect       c   = cIn;    // [MAF FP Speedup, 2/18/01]

	if ( VERIFYN(kMCCoordTypes, !c.IsEmpty())) {	
		WorldPt hx,hy,lx,ly;
		hx.x = c.Right() * mat.v1.a00;
		hx.y = c.Right() * mat.v1.a01;
		hy.x = c.Top() * mat.v1.a10;
		hy.y = c.Top() * mat.v1.a11;
		lx.x = c.Left() * mat.v1.a00;
		lx.y = c.Left() * mat.v1.a01;
		ly.x = c.Bottom() * mat.v1.a10;
		ly.y = c.Bottom() * mat.v1.a11;

		verts.topLeft		= WorldPt(	lx.x+hy.x+mat.v1.xOff,lx.y+hy.y+mat.v1.yOff);
		verts.topRight	 	= WorldPt(	hx.x+hy.x+mat.v1.xOff,hx.y+hy.y+mat.v1.yOff);
		verts.bottomLeft 	= WorldPt(	lx.x+ly.x+mat.v1.xOff,lx.y+ly.y+mat.v1.yOff);
		verts.bottomRight 	= WorldPt(	hx.x+ly.x+mat.v1.xOff,hx.y+ly.y+mat.v1.yOff);
	} // end if !empty
}


//////////////////////////////////////////////////////////////////////////////
// WorldPoly Implementation
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
Sint32 WorldPoly::GetNumPts() const
{
	return (Sint32)(polySize - offsetof(WorldPoly, polyPoints[0])) / sizeof(WorldPt);
}

//----------------------------------------------------------------------------
void WorldPoly::CalcBBox()
{
	Sint32 numPoints = this->GetNumPts();

	if (numPoints > 0) {
		polyBBox.Set(polyPoints[0], polyPoints[0]);

		for (int i=1; i<numPoints; i++) {
			polyBBox.UniteNoCheck(polyPoints[i]);
		}
	}
	else {
		polyBBox.MakeEmpty();
	}
}

//----------------------------------------------------------------------------
Sint32 WorldPoly::CalcSize(Sint32 inNumPts)
// static
{
	Sint32 outSize = 0;

	if (VERIFYN(kEveryone, inNumPts >= 0 && inNumPts <= kMaxWorldPolyVertices)) {
		outSize = inNumPts * sizeof(WorldPt) + offsetof(WorldPoly, polyPoints[0]);
	}

	return outSize;
}

////////////////////////////////////////////////////////////////////////////////
bool GS_API TransformMatrix::IsOrthogonal() const
//
// This function checks to see if the upper left 3x3 submatrix is orthogonal. 
// An orthogonal matrix does rigid body transformations (no scaling or skewing)
// and has nice properties like M inverse == M transpose. VectorWorks objects 
// should all have orthogonal matrices. 
//
/////// John Williams, 2 October 1999 //////////////////////////////////////////
{
	Vector	row1(v2.i);
	Vector	row2(v2.j);
	Vector	row3(v2.k);

	if (row1.IsNormalized() && 
		row2.IsNormalized() && 
		row3.IsNormalized() &&
		NormalizedValueIsNearlyOne(Abs(DotProduct(CrossProduct(row1, row2),  row3)))
	)
		return true;
	else
		return false;
}


// Optimizing SetToIdentity functions
// Profiler says that SetToIdentity can be up to 10% of rendering time!  -DLD 8/16/2001
// I am creating a constant identity matrix to use for SetToIdentity; rather than 
// nested for loops it becomes a mem copy operation.
static bool gIdentityTransformDefined = false;
static TransformMatrix kIdentityTransform;

static bool gIdentityTransformXDefined = false;
static TransformXMatrix kIdentityTransformX;



////////////////////////////////////////////////////////////////////////////////
void GS_API TransformMatrix::SetToIdentity()
// Sets the matrix to the identity matrix.
/////// John Williams, 4 October 1999 //////////////////////////////////////////
// Optimized out for loops.  -DLD 8/15/2001
{
	#if 0
		// Old Code
		for (Sint32 i = 0; i <= 3; i++)
			for (Sint32 j = 0; j <= 2; j++)
				mat[i][j] = (j == i) ? 1.0 : 0.0;
	#endif 	// 0

	if (!gIdentityTransformDefined) {

		Sint32 j;

		for (Sint32 i = 0; i <= 3; i++) {
			for (j = 0; j <= 2; j++)
				kIdentityTransform.mat[i][j] = (j == i) ? 1.0 : 0.0;
		}
		
		gIdentityTransformDefined = true;
	}

	// On the Mac anyway, changing from = to memcpy is way faster.  -DLD 8/16/2001
	//*this = kIdentityTransform;

	memcpy(this, &kIdentityTransform, sizeof(TransformMatrix));
}


////////////////////////////////////////////////////////////////////////////////
bool GS_API TransformMatrix::IsIdentity() const
// Checks to see if the matrix is an identity matrix.
/////// John Williams, 4 October 1999 //////////////////////////////////////////
{
	bool isIdentity = true;
	for (Sint32 i = 0; i <= 3 && isIdentity; i++)
		for (Sint32 j = 0; j <= 2 && isIdentity; j++)
			if (mat[i][j] != ((j == i) ? 1.0 : 0.0))
				isIdentity = false;
	return isIdentity;
}

////////////////////////////////////////////////////////////////////////////////
bool GS_API TransformMatrix::HasNoRotation() const
// Checks to see if the rotation part of a matrix is an identity matrix.
/////// Hernan Stamati, 14 April 2016 //////////////////////////////////////////
{
	for (Sint32 i = 0; i <= 2; i++)
		for (Sint32 j = 0; j <= 2; j++)
			if (mat[i][j] != ((j == i) ? 1.0 : 0.0))
				return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
int	GS_API TransformMatrix::Compare(const TransformMatrix& inRight) const
// Returns
//  1	- we are greater than inRight
//  0	- we are equal to inRight
// -1	- we are less than inRight
////////////////////////////////////////////////////////////////////////////////
{
	int outResult = 0;

	for (int i = 0; i < 4 && outResult==0; i++) {

		for (int j = 0; j < 3 && outResult==0; j++) {

			if (mat[i][j] < inRight.mat[i][j])
				outResult = -1;
			else if (mat[i][j] > inRight.mat[i][j])
				outResult = 1;
		}
	}

	return outResult;
}

////////////////////////////////////////////////////////////////////////////////
void GS_API TransformXMatrix::SetToIdentity()
// Sets the matrix to the identity matrix.
/////// John Williams, 5 October 1999 //////////////////////////////////////////
// Optimized out for loops.  -DLD 8/15/2001
{
	#if 0
		// Old code
		for (Sint32 i = 0; i <= 3; i++)
			for (Sint32 j = 0; j <= 3; j++)
				mat[i][j] = (j == i) ? 1.0 : 0.0;
	#endif 	// 0
	
	if (!gIdentityTransformXDefined) {

		Sint32 j;

		for (Sint32 i = 0; i <= 3; i++) {
			for (j = 0; j <= 3; j++)
				kIdentityTransformX.mat[i][j] = (j == i) ? 1.0 : 0.0;
		}
		
		gIdentityTransformXDefined = true;
	}

	// On the Mac anyway, changing from = to memcpy is way faster.  -DLD 8/16/2001
	//*this = kIdentityTransformX;

	memcpy(this, &kIdentityTransformX, sizeof(TransformXMatrix));
}


TRGBColor ColorVectorToRGBColor(const ColorVector& xPt)
{
	TRGBColor	color;
	
	double red = min((double_gs) 65535.0, xPt.x * 65535.0);
	red = max((double) 0.0, red);
	color.red = (unsigned short) red;
	double green = min((double_gs) 65535.0, xPt.y * 65535.0);
	green = max((double) 0.0, green);
	color.green = (unsigned short) green;
	double blue = min((double_gs) 65535.0, xPt.z * 65535.0);
	blue = max((double) 0.0, blue);
	color.blue = (unsigned short) blue;
	
	return color;
}
ColorVector RGBColorToColorVector(const TRGBColor& color)
{
	return ColorVector(color.red / 65535.0, color.green / 65535.0, color.blue / 65535.0);
}


///////////////////////////////////
// Byte Swapping & FP Conversion
///////////////////////////////////

void GS_API _WorldPt::ByteSwap()
{
	ByteSwapDouble(&y);
	ByteSwapDouble(&x);
}

void GS_API WorldPt3::ByteSwap()
{
	ByteSwapDouble(&x);
	ByteSwapDouble(&y);
	ByteSwapDouble(&z);
}

void GS_API FloatPt3::ByteSwap()
{
	ByteSwapFloat(&x);
	ByteSwapFloat(&y);
	ByteSwapFloat(&z);
}

void GS_API _WorldCube::ByteSwap()
{
	ByteSwapDouble(&right);
	ByteSwapDouble(&top);
	ByteSwapDouble(&front);
	ByteSwapDouble(&left);
	ByteSwapDouble(&bottom);
	ByteSwapDouble(&back);
}

void GS_API WorldRect::ByteSwap()
{
	ByteSwapDouble(&top);
	ByteSwapDouble(&left);
	ByteSwapDouble(&bottom);
	ByteSwapDouble(&right);
}


void GS_API Axis::ByteSwap(EByteSwapFPMode UNUSED(fpFormat))
{
	vertex.ByteSwap();	// XXX_JDW_FLOATINGPOINT
	i.ByteSwap();
	j.ByteSwap();
	k.ByteSwap();
}

void GS_API TransformMatrix::ByteSwap()
{
	// All 3 structures in the union consist of 12 longs.
	for (Sint32 i=0; i<4; ++i)
		for (Sint32 j=0; j<3; ++j)
			ByteSwapDouble(&mat[i][j]);		// XXX_JDW_FLOATINGPOINT
}

// Checking whether any of the values is NaN or IND
// NaN = Not A Number. i.e. double dNAN = sqrt( -1.00 )
// IND = Indeterminate Number. i.e. double dIND1 = ( 0.0 / 0.0 ) or (INF/INF); 
bool GS_API TransformMatrix::IsNaNorIND(void)
{
	return
		v1.a00 != v1.a00 || v1.a01 != v1.a01 || v1.a02 != v1.a02 ||
		v1.a00 != v1.a00 || v1.a01 != v1.a01 || v1.a02 != v1.a02 ||
		v1.a00 != v1.a00 || v1.a01 != v1.a01 || v1.a02 != v1.a02 ||
		v1.xOff != v1.xOff || v1.yOff != v1.yOff || v1.zOff != v1.zOff;
}

// Set to zero for the NaN or IND offsets and Set to identity in the matrix
// NaN = Not A Number. i.e. double dNaN = sqrt( -1.00 )
// IND = Indeterminate Number. i.e. double dIND1 = ( 0.0 / 0.0 ) or (INF/INF); 
bool GS_API TransformMatrix::SetToZeroNaNorIND(void)
{
	bool found = false;

	if (v1.a00 != v1.a00 || v1.a01 != v1.a01 || v1.a02 != v1.a02 ||
		v1.a10 != v1.a10 || v1.a11 != v1.a11 || v1.a12 != v1.a12 ||
		v1.a20 != v1.a20 || v1.a21 != v1.a21 || v1.a22 != v1.a22) {
		v1.a00 = 1.0; v1.a01 = 0.0; v1.a02 = 0.0;
		v1.a10 = 0.0; v1.a11 = 1.0; v1.a12 = 0.0;
		v1.a20 = 0.0; v1.a21 = 0.0; v1.a22 = 1.0;
		found = true;
	}

	if (v1.xOff != v1.xOff) { v1.xOff = 0.0; found = true; }
	if (v1.yOff != v1.yOff) { v1.yOff = 0.0; found = true; }
	if (v1.zOff != v1.zOff) { v1.zOff = 0.0; found = true; }

	return found;
}
