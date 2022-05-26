//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//  This file contains geometry manipulation functions for the
//	GSCore.  Include only those functions that rely on nothing
//	but GSTypes and standard C++ types, no MiniCad types.
//

#include "StdHeaders.h"

#include <math.h>
#if GS_WIN
	#include <Windows.h>
#else
	#include <memory>
	using std::memset;  // Windows does not put Standard C library in std namespace
#endif

#if GS_WIN
	//#include <MinMax.h>
#endif


/////////////////////////

// TEMPORARY RELOCATION of color constants with aggregate initializers
// from GSGlobals.h


////////////////////////////////////////////////////////////////////////////////
// GSColors only use the low byte. This gets duplicated for both bytes
// of Mac colors. (GS 0x003C -> Mac 0x3C3C).  Also see blackColor etc. 
// in Quickdraw.h - older non RGB* Quickdraw constants, and Mac constants
// in Builtins.h; and kWhiteIndx and kBlackIndx and kMaxColor; kBlack;
// and kGray0 through kGrayF.


const extern GSColor kGSColorBlack			=	{0x0000, 0x0000, 0x0000};
const extern GSColor kGSColorWhite			=	{0x00FF, 0x00FF, 0x00FF};
const extern GSColor kGSColorRed			=	{0x00EE, 0x0000, 0x0000};
const extern GSColor kGSColorBrightRed		=	{0x00FF, 0x0033, 0x0033};
const extern GSColor kGSColorGreen			=	{0x0000, 0x00FF, 0x0000};
const extern GSColor kGSColorLtGreen		=	{0x0033, 0x00FF, 0x0033};
const extern GSColor kGSColorBlue			=	{0x0000, 0x0000, 0x00FF};
const extern GSColor kGSColorMedBlue		=	{0x0033, 0x0066, 0x00FF};
const extern GSColor kGSColorLtBlue			=	{0x0066, 0x00CC, 0x00FF};
const extern GSColor kGSColorLighterBlue	=	{0x0066, 0x00AA, 0x00FF};
const extern GSColor kGSColorViolet			=	{0x00FF, 0x0099, 0x00FF};
const extern GSColor kGSColorYellow			=	{0x00FF, 0x00FF, 0x0000};
const extern GSColor kGSColorLtGray			=	{0x0077, 0x0077, 0x0077};
const extern GSColor kGSColorLighterGray	=	{0x00AA, 0x00AA, 0x00AA};


const extern GSColor kGSColor16Black		=	{0x0000, 0x0000, 0x0000};
const extern GSColor kGSColor16White		=	{0xFFFF, 0xFFFF, 0xFFFF};

/////////////////////////

ViewCoord SafeAdd(ViewCoord v1, ViewCoord v2)
{
	Sint32 r = v1 + v2;
	return DemoteTo<ViewCoord>(kEveryone, PinTo<ViewCoord>(kEveryone, r));
}

/************************************************************************/
/************************************************************************/
//	Implementation of ViewRect manipulation functions follows
/************************************************************************/
/************************************************************************/

// Sets the rect from two points
void ViewRect::SetRect(const ViewPt& pt1, const ViewPt& pt2)
{
	if (pt1.x < pt2.x) {
		left	= pt1.x;
		right	= pt2.x;
	}
	else {
		left	= pt2.x;
		right	= pt1.x;
	}

	// View Rects are for screen coords, as opposed to World Rects
	//  which are for Geometry.  Y increases in View Rects as you go down.
	if (pt1.y < pt2.y) {
		top		= pt1.y;
		bottom	= pt2.y;
	}
	else {
		top		= pt2.y;
		bottom	= pt1.y;
	}
}

ViewCoord ViewRect::Width()  const
{
	// If this is asserting, the coordinates are overflowing a short.
	// You should probably call the WidthL() function instead.
	// We'd like to phase out the use of this function.
	ASSERTN(kEveryone, inrange((Sint32)right-(Sint32)left, (Sint32)kGSMinSint16, (Sint32)kGSMaxSint16));
	return right - left;
}

ViewCoord ViewRect::Height() const
{
	// If this is asserting, the coordinates are overflowing a short.
	// You should probably call the HeightL() function instead.
	// We'd like to phase out the use of this function.
	ASSERTN(kEveryone, inrange((Sint32)bottom-(Sint32)top, (Sint32)kGSMinSint16, (Sint32)kGSMaxSint16));
	return bottom - top;
}

ViewPt ViewRect::Center() const
{
	ASSERTN(kEveryone, inrange(((Sint32) left + (Sint32) right) / 2, (Sint32)kGSMinSint16, (Sint32)kGSMaxSint16));
	ASSERTN(kEveryone, inrange(((Sint32) bottom + (Sint32) top) / 2, (Sint32)kGSMinSint16, (Sint32)kGSMaxSint16));

	return ViewPt((Sint16)(((Sint32) left + (Sint32) right) / 2), (Sint16)(((Sint32) bottom + (Sint32) top) / 2));
}

// Make this like WorldRect::Intersect() [MAF 9/25/00]
Bool8 ViewRect::Intersect(const ViewRect& invr, ViewRect& outvrIntersection) const
// See also XViewRect::Intersect
{
	Bool8 outbSuccess = false;

	// This allows a ViewRect with zero width, or zero height (like for a horizontal or vertical line)
	// to successfully intersect with others. (Rects like this are generated in AcceleratedFilter::IsVisible)
	// Technically, these rects are empty and shouldn't intersect with anything, and clients should be generating non-empty rects.
	if (bottom > invr.top
		&& right > invr.left
		&& left < invr.right 
		&& top < invr.bottom) { // this is like this->Overlaps without the this->IsEmpty checks

		outvrIntersection.SetLTRB(	max(left, invr.left),
									max(top, invr.top),
									min(right, invr.right),
									min(bottom, invr.bottom));

		if (outvrIntersection.top  > outvrIntersection.bottom 
			|| outvrIntersection.left > outvrIntersection.right) {

			// ViewRect is inverted, set data to zero and return false
			outvrIntersection.MakeEmpty();
		}
		else {
			outbSuccess = true;
		}
	}
	else { // Rects don't intersect, set data to zero and return false
		outvrIntersection.MakeEmpty();
	}

	return outbSuccess;
}

Bool8 ViewRect::PtInRect(const ViewPt& pt) const
{
	if (left < pt.x && right > pt.x && top < pt.y && bottom > pt.y)
		return true;
	else
		return false;
}

void PagePt::ByteSwap()
{
	ByteSwapDouble(&x);
	ByteSwapDouble(&y);
}


void ViewPt::ByteSwap()
{
	ByteSwapSHORT(&x);
	ByteSwapSHORT(&y);
}

void ViewRect::ByteSwap()
{
	ByteSwapSHORT(&top);
	ByteSwapSHORT(&left);
	ByteSwapSHORT(&bottom);
	ByteSwapSHORT(&right);
}


//////////////////////////////////////////////////////////////////////////////
// XViewRect Implementation
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
XViewRect::XViewRect(const GSRect32& v)
{
	top = v.top;
	left = v.left;
	bottom = v.bottom;
	right = v.right;
}

//----------------------------------------------------------------------------
void XViewRect::SetRect(const XViewPt& inxvpt1, const XViewPt& inxvpt2)
{
	if (inxvpt1.x < inxvpt2.x) {
		left	= inxvpt1.x;
		right	= inxvpt2.x;
	}
	else {
		left	= inxvpt2.x;
		right	= inxvpt1.x;
	}

	// XViewRects are for screen coords, as opposed to World Rects
	// which are for Geometry.  Y increases in XViewRects as you go down.
	if (inxvpt1.y < inxvpt2.y) {
		top		= inxvpt1.y;
		bottom	= inxvpt2.y;
	}
	else {
		top		= inxvpt2.y;
		bottom	= inxvpt1.y;
	}
}

//----------------------------------------------------------------------------
Bool8 XViewRect::operator==(const XViewRect& inxvr) const
{
	return DoublesAreNearlyEqual(top, inxvr.top, kNearlyEqualEpsilonForDoubles)
			&& DoublesAreNearlyEqual(left, inxvr.left, kNearlyEqualEpsilonForDoubles)
			&& DoublesAreNearlyEqual(bottom, inxvr.bottom, kNearlyEqualEpsilonForDoubles)
			&& DoublesAreNearlyEqual(right, inxvr.right, kNearlyEqualEpsilonForDoubles);
}

//----------------------------------------------------------------------------
XViewPt	XViewRect::Center() const
{
	return XViewPt((left + right)/2, (bottom + top)/2);
}


/////////////////////////////////////////////////////////////////////////
Bool8 XViewRect::Intersects(const XViewRect& r) const
{
	XViewRect xvrInt;
	return this->Intersect(r, xvrInt);
}

// Make this like WorldRect::Intersect() [MAF 9/25/00]
//----------------------------------------------------------------------------
Bool8 XViewRect::Intersect(const XViewRect& inxvr, XViewRect& outxvrIntersection) const
// See also ViewRect::Intersect
{
	Bool8 outbSuccess = false;

	// This allows a Rect with zero width, or zero height (like for a horizontal or vertical line)
	// to successfully intersect with others. (Rects like this are generated in AcceleratedFilter::IsVisible)
	// Technically, these rects are empty and shouldn't intersect with anything, and clients should be generating non-empty rects.
	if (bottom > inxvr.top
		&& right > inxvr.left
		&& left < inxvr.right 
		&& top < inxvr.bottom) { // this is like this->Overlaps without the this->IsEmpty checks

		outxvrIntersection.SetLTRB(	max(left, inxvr.left),
									max(top, inxvr.top),
									min(right, inxvr.right),
									min(bottom, inxvr.bottom));

		if (outxvrIntersection.top  > outxvrIntersection.bottom 
			|| outxvrIntersection.left > outxvrIntersection.right) {

			// XViewRect is inverted, set data to zero and return false
			outxvrIntersection.MakeEmpty();
		}
		else {
			outbSuccess = true;
		}
	}
	else { // Rects don't intersect, set data to zero and return false
		outxvrIntersection.MakeEmpty();
	}

	return outbSuccess;
}

/////////////////////////////////////////////////////////////////////////
void XViewRect::Intersect(const XViewRect& r)
{
	XViewRect xvrInt;
	this->Intersect(r, xvrInt);
	*this = xvrInt;
}

/////////////////////////////////////////////////////////////////////////
XViewRect XViewRect::Intersection(const XViewRect& r) const
{
	XViewRect xvrInt;
	this->Intersect(r, xvrInt);
	return xvrInt;
}

//----------------------------------------------------------------------------
Bool8 XViewRect::PtInRect(const XViewPt& queryPoint) const
{
    // Use WorldCoord_GT_WorldCoord(...) and WorldCoord_LT_WorldCoord(...) here? [AAO, 1-28-2015]
	return (left < queryPoint.x && right > queryPoint.x && top < queryPoint.y && bottom > queryPoint.y);
}

//----------------------------------------------------------------------------
void XViewRect::Scale(const double f, const XViewPt* pAboutPt/*=NULL*/)
{
	XViewPt ptLT(left, top);
	ptLT.Scale(f, pAboutPt);
	left	= ptLT.x;
	top		= ptLT.y;

	XViewPt ptRB(right, bottom);
	ptRB.Scale(f, pAboutPt);
	right	= ptRB.x;
	bottom	= ptRB.y;
}

/////////////////////////////////////////////////////////////////////////
Bool8 SectViewRect(const ViewRect& src1, const ViewRect& src2, ViewRect& dest)
//
//	Calculate the intersection of the two source rects and return
//	it in the destination rect.  If the two rects don't intersect
//	return false, otherwise return true.
//
/////////////////////////////////////////////////////////////////////////
{
	return src1.Intersect(src2, dest);
} // SectViewRect


/////////////////////////////////////////////////////////////////////////
Bool8 EqualViewRect(const ViewRect& src1, const ViewRect& src2)
//
//	Compare the two rects.  If they are equal, return true otherwise false.
//
/////////////////////////////////////////////////////////////////////////
{
	return src1 == src2;
} // EqualViewRect


/////////////////////////////////////////////////////////////////////////
inline ViewCoord ClippedAdd(ViewCoord value, ViewCoord offset)
//
// helper for InsetViewRect
//
/////////////////////////////////////////////////////////////////////////
{
	Sint32 newVal = Sint32(value) + Sint32(offset);
	ClipNum(newVal, kGSMinSint16, kGSMaxSint16);
	return ViewCoord(newVal);
}

/////////////////////////////////////////////////////////////////////////
void InsetViewRect(ViewRect& rect, ViewCoord dx, ViewCoord dy)
//
//	Grow or shrink the rectangle by the given dx and dy values.
//  This function also makes sure the view coordinates don't overflow.
//
/////////////////////////////////////////////////////////////////////////
{
	rect.SetLeft  (ClippedAdd(rect.Left(),    dx));
	rect.SetRight (ClippedAdd(rect.Right(),  -dx));
	rect.SetTop   (ClippedAdd(rect.Top(),     dy));
	rect.SetBottom(ClippedAdd(rect.Bottom(), -dy));
}


/////////////////////////////////////////////////////////////////////////
Bool8 IsEmptyViewRect(const ViewRect& rect)
//
//	Test if the rectangle is empty.. one dimension (width or height) is
//	zero.  An inverted rect is an empty rect.
//
/////////////////////////////////////////////////////////////////////////
{
	return rect.IsEmpty();
} // IsEmptyViewRect


/////////////////////////////////////////////////////////////////////////
void OffsetViewRect(ViewRect& rect, Sint16 dx, Sint16 dy)
//
//	Offset the rect by the given dx, dy values.
//
/////////////////////////////////////////////////////////////////////////
{
	rect.Offset(dx, dy);
}


/////////////////////////////////////////////////////////////////////////
void UnionViewRect(const ViewRect& src1, const ViewRect& src2, ViewRect& dest)
//
//	Calculate the smallest rectangle that will encompass the two
//	source rectangles even if they are not touching.
//
/////////////////////////////////////////////////////////////////////////
{
	src1.Union(src2, dest);
}


/////////////////////////////////////////////////////////////////////////
void GSPt2ViewRect(const ViewPt& pt1, const ViewPt& pt2, ViewRect& rect)
//
//	Calculate the smallest rectangle that will encompass the two
//	points.
//
/////////////////////////////////////////////////////////////////////////
{
	rect.SetRect(pt1, pt2);
} //endof GSPt2GSRect()


/////////////////////////////////////////////////////////////////////////
Bool8 GSPtInViewRect(const ViewPt& pt, const ViewRect& rect)
//
//	Return true if the point is in the rectangle, otherwise false.
//
/////////////////////////////////////////////////////////////////////////
{
	return rect.PtInRect(pt);
} //endof GSPtInGSRect()


/////////////////////////////////////////////////////////////////////////
Bool8 GSPtToAngle(const ViewRect& UNUSED(rect), const ViewPt& UNUSED(pt), Sint16 UNUSED(angle))
//
//	Calculate the angle that is described by the horizontal line starting
//	at the center of the rectangle and a the line that joins the center
//	of the rectangle and the given point.  If you need more clarification
//	refer to the Inside the Mac manual because this function is supposed
//	to mimic it.
//
/////////////////////////////////////////////////////////////////////////
{
	//This will be implemented when the arrow drawing routines need it.

	return false;
} //endof GSPtToAngle()


 void SetViewRect(ViewRect& rect, Sint16 left, Sint16 top, Sint16 right, Sint16 bottom)
//
//	Create a ViewRect with the given values.
//
/////////////////////////////////////////////////////////////////////////
{
	rect.SetLTRB(left, top, right, bottom);
} 

/////////////////////////////////////////////////////////////////////////
ViewRect GSRect32ToViewRect(const GSRect32& inRect32)
/////////////////////////////////////////////////////////////////////////
{
	ViewRect outvr(DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, inRect32.left)),
					DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, inRect32.top)),
					DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, inRect32.right)),
					DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, inRect32.bottom)));
	return outvr;
}

/////////////////////////////////////////////////////////////////////////
ViewPt GSPoint32ToViewPt(const GSPoint32& inPoint32)
/////////////////////////////////////////////////////////////////////////
{
	ViewPt outvpt(DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, inPoint32.x)),
				DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, inPoint32.y)));
	return outvpt;
}

// To be consistent with WorldToView rounding, we do something like Num2Short.
inline double _XRound(double x)	{ return (x < 0) ? ceil(x - 0.5000000001) : floor(x + 0.5000000001); /*return Round(in);*/ }

double XRound(double in) { return _XRound(in); }

/////////////////////////////////////////////////////////////////////////
bool XViewRectToViewRect(const XViewRect& inxvr, ViewRect& outvr, EXVRToVRMode inMode/*=eXVRToVR_Round*/)
/////////////////////////////////////////////////////////////////////////
{
	bool bR = inMode==eXVRToVR_Round;
	outvr.SetLTRB(	DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, bR ? _XRound(inxvr.left) : floor(inxvr.left))),
					DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, bR ? _XRound(inxvr.top) : floor(inxvr.top))),
					DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, bR ? _XRound(inxvr.right) : ceil(inxvr.right))),
					DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, bR ? _XRound(inxvr.bottom) : ceil(inxvr.bottom))));
	return XViewRectWithinLimits(inxvr, eXVL_ViewCoord);
}

/////////////////////////////////////////////////////////////////////////
bool XViewPtToViewPt(const XViewPt& inxvpt, ViewPt& outvpt)
/////////////////////////////////////////////////////////////////////////
{
	outvpt.Set(	DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, _XRound(inxvpt.x))),
				DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, _XRound(inxvpt.y))));
	return XViewPtWithinLimits(inxvpt, eXVL_ViewCoord);
}

/////////////////////////////////////////////////////////////////////////
bool XViewLengthToViewLength(XViewCoord inxv, ViewCoord& outv, EXVRToVRMode inMode/*=eXVRToVR_Round*/)
/////////////////////////////////////////////////////////////////////////
{
	outv = DemoteTo<ViewCoord>(kEJKerr, PinTo<ViewCoord>(kEJKerr, inMode==eXVRToVR_Round ? _XRound(inxv) : (inxv < 0 ? floor(inxv) : ceil(inxv))));
	return XViewCoordWithinLimits(inxv, eXVL_ViewCoord);
}

/////////////////////////////////////////////////////////////////////////
bool XViewRectToGSRect32(const XViewRect& inxvr, GSRect32& outrc32, EXVRToVRMode inMode/*=eXVRToVR_Round*/)
/////////////////////////////////////////////////////////////////////////
{
	bool bR = inMode==eXVRToVR_Round;
	outrc32.Set(DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, bR ? _XRound(inxvr.left) : floor(inxvr.left))),
				DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, bR ? _XRound(inxvr.top) : floor(inxvr.top))),
				DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, bR ? _XRound(inxvr.right) : ceil(inxvr.right))),
				DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, bR ? _XRound(inxvr.bottom) : ceil(inxvr.bottom))));
	return XViewRectWithinLimits(inxvr, eXVL_GSCoord32);
}

/////////////////////////////////////////////////////////////////////////
bool XViewPtToGSPoint32(const XViewPt& inxvpt, GSPoint32& outpt32)
/////////////////////////////////////////////////////////////////////////
{
	outpt32.Set(DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, _XRound(inxvpt.x))),
				DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, _XRound(inxvpt.y))));
	return XViewPtWithinLimits(inxvpt, eXVL_GSCoord32);
}

/////////////////////////////////////////////////////////////////////////
bool XViewLengthToGSCoord32Length(XViewCoord inxv, GSCoord32& outv32, EXVRToVRMode inMode/*=eXVRToVR_Round*/)
/////////////////////////////////////////////////////////////////////////
{
	outv32 = DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, inMode==eXVRToVR_Round ? _XRound(inxv) : (inxv < 0 ? floor(inxv) : ceil(inxv))));
	return XViewCoordWithinLimits(inxv, eXVL_GSCoord32);
}

#ifdef __cplusplus
/////////////////////////////////////////////////////////////////////////
ViewRectVerts GSRect32VertsToViewRectVerts(const GSRect32Verts& inVrv32)
/////////////////////////////////////////////////////////////////////////
{
	ViewRectVerts outVrv;
	
	outVrv.SetTopLeft()		= GSPoint32ToViewPt(inVrv32.TopLeft());
	outVrv.SetTopRight()	= GSPoint32ToViewPt(inVrv32.TopRight());
	outVrv.SetBottomLeft()	= GSPoint32ToViewPt(inVrv32.BottomLeft());
	outVrv.SetBottomRight()	= GSPoint32ToViewPt(inVrv32.BottomRight());
	
	return outVrv;
}
#endif

GSCoord32 SafeAdd(GSCoord32 v1, GSCoord32 v2)
{
	Sint64 r = v1 + v2;
	return DemoteTo<GSCoord32>(kEveryone, PinTo<GSCoord32>(kEveryone, r));
}

/************************************************************************/
/************************************************************************/
//	Implementation for the GSPoint32 class follows
/************************************************************************/
/************************************************************************/
Bool8 GSPoint32::ScaleRound(const double f, const GSPoint32* pAboutPt/*=NULL*/)
{
	Bool8 bSuccess = true;

	double temp;

	if (pAboutPt) {
		temp = Round((x-pAboutPt->x)*f + pAboutPt->x);
		x = DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, temp));
		bSuccess = bSuccess && (temp == x);

		temp = Round((y-pAboutPt->y)*f + pAboutPt->y);
		y = DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, temp));
		bSuccess = bSuccess && (temp == y);
	}
	else {
		temp = Round(x*f);
		x = DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, temp));
		bSuccess = bSuccess && (temp == x);

		temp = Round(y*f);
		y = DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, temp));
		bSuccess = bSuccess && (temp == y);
	}

	return 	bSuccess;
}
Bool8 GSPoint32::ScaleTrunc(const double f, const GSPoint32* pAboutPt/*=NULL*/)
{
	Bool8 bSuccess = true;

	double temp;

	if (pAboutPt) {
		temp = Truncate((x-pAboutPt->x)*f + pAboutPt->x);
		x = DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, temp));
		bSuccess = bSuccess && (temp == x);

		temp = Truncate((y-pAboutPt->y)*f + pAboutPt->y);
		y = DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, temp));
		bSuccess = bSuccess && (temp == y);
	}
	else {
		temp = Truncate(x*f);
		x = DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, temp));
		bSuccess = bSuccess && (temp == x);

		temp = Truncate(y*f);
		y = DemoteTo<GSCoord32>(kEJKerr, PinTo<GSCoord32>(kEJKerr, temp));
		bSuccess = bSuccess && (temp == y);
	}

	return 	bSuccess;
}

/************************************************************************/
/************************************************************************/
//	Implementation for the GSRect32 class follows
/************************************************************************/
/************************************************************************/
/////////////////////////////////////////////////////////////////////////
Bool8 GSRect32::Intersects(const GSRect32& r) const
{ 
	if (this->IsEmpty() || r.IsEmpty())
		return false;
	else
		return (bottom > r.top && right > r.left
				&& left < r.right && top < r.bottom); 
}

/////////////////////////////////////////////////////////////////////////
void GSRect32::Intersect(const GSRect32& r)
{
	if (this->Intersects(r)) {
		left	= max(left,   r.left);
		top		= max(top,    r.top);	
		right	= min(right,  r.right);
		bottom	= min(bottom, r.bottom);
	}
	else
		this->MakeEmpty();
}

/////////////////////////////////////////////////////////////////////////
GSRect32 GSRect32::Intersection(const GSRect32& r) const
{
	GSRect32 ret = *this; ret.Intersect(r); return ret;
}

/////////////////////////////////////////////////////////////////////////
Bool8 GSRect32::ScaleRound(const double f, const GSPoint32* pAboutPt/*=NULL*/)
{
	Bool8 bSuccess = true;

	Bool8 temp;

	GSPoint32 ptLT(left, top);
	temp = ptLT.ScaleRound(f, pAboutPt);
	left	= ptLT.x;
	top		= ptLT.y;
	bSuccess = bSuccess && temp;

	GSPoint32 ptRB(right, bottom);
	temp = ptRB.ScaleRound(f, pAboutPt);
	right	= ptRB.x;
	bottom	= ptRB.y;
	bSuccess = bSuccess && temp;

	return 	bSuccess;
}

/////////////////////////////////////////////////////////////////////////
Bool8 GSRect32::ScaleTrunc(const double f, const GSPoint32* pAboutPt/*=NULL*/)
{
	Bool8 bSuccess = true;

	Bool8 temp;

	GSPoint32 ptLT(left, top);
	temp = ptLT.ScaleTrunc(f, pAboutPt);
	left	= ptLT.x;
	top		= ptLT.y;
	bSuccess = bSuccess && temp;

	GSPoint32 ptRB(right, bottom);
	temp = ptRB.ScaleTrunc(f, pAboutPt);
	right	= ptRB.x;
	bottom	= ptRB.y;
	bSuccess = bSuccess && temp;

	return 	bSuccess;
}

/************************************************************************/
/************************************************************************/
//	Implementation for the ViewRectVerts class follows
/************************************************************************/
/************************************************************************/
/////////////////////////////////////////////////////////////////////////
void ViewRectVerts::OutSet(ViewCoord invDistance)
{
	ViewPt tmpVP;
	double tmpX = 0.0;
	double tmpY = 0.0;
	double tmpM = 0.0;

	tmpVP = this->TopLeft() - this->BottomLeft();
	tmpX = tmpVP.x;
	tmpY = tmpVP.y;
	tmpM = max(sqrt( tmpX * tmpX + tmpY * tmpY), 1.0);
	tmpX /= tmpM;
	tmpX *= invDistance;
	tmpY /= tmpM;
	tmpY *= invDistance;
	tmpVP.Set(	DemoteTo<ViewCoord, double>( kJLoy, floor( tmpX)), 
				DemoteTo<ViewCoord, double>( kJLoy, floor( tmpY)));

	this->SetTopLeft()		= this->TopLeft() + tmpVP;
	this->SetTopRight()		= this->TopRight() + tmpVP;
	this->SetBottomLeft()	= this->BottomLeft() - tmpVP;
	this->SetBottomRight()	= this->BottomRight() - tmpVP;

	tmpVP = this->TopLeft() - this->TopRight();
	tmpX = tmpVP.x;
	tmpY = tmpVP.y;
	tmpM = max(sqrt( tmpX * tmpX + tmpY * tmpY), 1.0);
	tmpX /= tmpM;
	tmpX *= invDistance;
	tmpY /= tmpM;
	tmpY *= invDistance;
	tmpVP.Set(	DemoteTo<ViewCoord, double>( kJLoy, floor( tmpX)), 
				DemoteTo<ViewCoord, double>( kJLoy, floor( tmpY)));

	this->SetTopLeft()		= this->TopLeft() + tmpVP;
	this->SetTopRight()		= this->TopRight() - tmpVP;
	this->SetBottomLeft()	= this->BottomLeft() + tmpVP;
	this->SetBottomRight()	= this->BottomRight() - tmpVP;
}

/////////////////////////////////////////////////////////////////////////
void ViewRectVerts::GetBoundingBox(ViewRect& vr) const
{
	vr.left		= min(min(this->TopLeft().x, this->TopRight().x), min(this->BottomLeft().x, this->BottomRight().x));
	vr.top		= min(min(this->TopLeft().y, this->TopRight().y), min(this->BottomLeft().y, this->BottomRight().y));
	vr.right	= max(max(this->TopLeft().x, this->TopRight().x), max(this->BottomLeft().x, this->BottomRight().x));
	vr.bottom	= max(max(this->TopLeft().y, this->TopRight().y), max(this->BottomLeft().y, this->BottomRight().y));
}

/////////////////////////////////////////////////////////////////////////
Boolean ViewRectVerts::IsNotRotatedMuch() const
{
	return (this->TopLeft().y == this->TopRight().y && this->TopLeft().x == this->BottomLeft().x
		&& this->TopLeft().y < this->BottomLeft().y && this->TopLeft().x < this->TopRight().x);
}

/************************************************************************/
/************************************************************************/
//	Implementation for the GSRect32Verts class follows
/************************************************************************/
/************************************************************************/
/////////////////////////////////////////////////////////////////////////
GSRect32Verts::GSRect32Verts(const GSRect32& inRect)
{
	fVerts[0].Set(inRect.left, inRect.top);
	fVerts[1].Set(inRect.right, inRect.top);
	fVerts[2].Set(inRect.right, inRect.bottom);
	fVerts[3].Set(inRect.left, inRect.bottom);
}

/////////////////////////////////////////////////////////////////////////
GSRect32Verts::GSRect32Verts(const ViewRectVerts& inVrv)
{
	for (Sint32 i=0; i<4; i++)
		fVerts[i] = inVrv[i];
}

/////////////////////////////////////////////////////////////////////////
GSRect32Verts::GSRect32Verts(const GSRect32Verts& inVrv)
{
	fVerts[0] = inVrv.fVerts[0];
	fVerts[1] = inVrv.fVerts[1];
	fVerts[2] = inVrv.fVerts[2];
	fVerts[3] = inVrv.fVerts[3];
}

/////////////////////////////////////////////////////////////////////////
void GSRect32Verts::GetBoundingBox(GSRect32& outBounds) const
{
	outBounds.left		= min(min(this->TopLeft().x, this->TopRight().x), min(this->BottomLeft().x, this->BottomRight().x));
	outBounds.top		= min(min(this->TopLeft().y, this->TopRight().y), min(this->BottomLeft().y, this->BottomRight().y));
	outBounds.right		= max(max(this->TopLeft().x, this->TopRight().x), max(this->BottomLeft().x, this->BottomRight().x));
	outBounds.bottom	= max(max(this->TopLeft().y, this->TopRight().y), max(this->BottomLeft().y, this->BottomRight().y));
}

/////////////////////////////////////////////////////////////////////////
Boolean GSRect32Verts::IsNotRotatedMuch() const
{
	return (this->TopLeft().y == this->TopRight().y && this->TopLeft().x == this->BottomLeft().x
		&& this->TopLeft().y < this->BottomLeft().y && this->TopLeft().x < this->TopRight().x);
}

/////////////////////////////////////////////////////////////////////////
void GSRect32Verts::ScaleRound(const double f, const GSPoint32* pAboutPt/*=NULL*/)
{
	fVerts[0].ScaleRound(f, pAboutPt);
	fVerts[1].ScaleRound(f, pAboutPt);
	fVerts[2].ScaleRound(f, pAboutPt);
	fVerts[3].ScaleRound(f, pAboutPt);
}

/////////////////////////////////////////////////////////////////////////
void GSRect32Verts::ScaleTrunc(const double f, const GSPoint32* pAboutPt/*=NULL*/)
{
	fVerts[0].ScaleTrunc(f, pAboutPt);
	fVerts[1].ScaleTrunc(f, pAboutPt);
	fVerts[2].ScaleTrunc(f, pAboutPt);
	fVerts[3].ScaleTrunc(f, pAboutPt);
}

/************************************************************************/
/************************************************************************/
//	Implementation for the XViewRectVerts class follows
/************************************************************************/
/************************************************************************/
/////////////////////////////////////////////////////////////////////////
XViewRectVerts::XViewRectVerts(const XViewRect& inRect)
{
	fVerts[0].Set(inRect.left, inRect.top);
	fVerts[1].Set(inRect.right, inRect.top);
	fVerts[2].Set(inRect.right, inRect.bottom);
	fVerts[3].Set(inRect.left, inRect.bottom);
}

/////////////////////////////////////////////////////////////////////////
XViewRectVerts::XViewRectVerts(const ViewRectVerts& inVrv)
{
	for (Sint32 i=0; i<4; i++)
		fVerts[i] = inVrv[i];
}

/////////////////////////////////////////////////////////////////////////
XViewRectVerts::XViewRectVerts(const GSRect32Verts& inVrv)
{
	for (Sint32 i=0; i<4; i++)
		fVerts[i] = inVrv[i];
}

/////////////////////////////////////////////////////////////////////////
XViewRectVerts::XViewRectVerts(const XViewRectVerts& inVrv)
{
	fVerts[0] = inVrv.fVerts[0];
	fVerts[1] = inVrv.fVerts[1];
	fVerts[2] = inVrv.fVerts[2];
	fVerts[3] = inVrv.fVerts[3];
}

/////////////////////////////////////////////////////////////////////////
void XViewRectVerts::GetBoundingBox(XViewRect& outBounds) const
{
	outBounds.left		= min(min(this->TopLeft().x, this->TopRight().x), min(this->BottomLeft().x, this->BottomRight().x));
	outBounds.top		= min(min(this->TopLeft().y, this->TopRight().y), min(this->BottomLeft().y, this->BottomRight().y));
	outBounds.right		= max(max(this->TopLeft().x, this->TopRight().x), max(this->BottomLeft().x, this->BottomRight().x));
	outBounds.bottom	= max(max(this->TopLeft().y, this->TopRight().y), max(this->BottomLeft().y, this->BottomRight().y));
}

/////////////////////////////////////////////////////////////////////////
Boolean XViewRectVerts::IsNotRotatedMuch() const
{
	return (this->TopLeft().y == this->TopRight().y && this->TopLeft().x == this->BottomLeft().x
		&& this->TopLeft().y < this->BottomLeft().y && this->TopLeft().x < this->TopRight().x);
}

/////////////////////////////////////////////////////////////////////////
void XViewRectVerts::Scale(const double f, const XViewPt* pAboutPt/*=NULL*/)
{
	fVerts[0].Scale(f, pAboutPt);
	fVerts[1].Scale(f, pAboutPt);
	fVerts[2].Scale(f, pAboutPt);
	fVerts[3].Scale(f, pAboutPt);
}

#ifdef __cplusplus
/////////////////////////////////////////////////////////////////////////
bool XViewRectVertsToGSRect32Verts(const XViewRectVerts& inxvrv, GSRect32Verts& outvrv)
/////////////////////////////////////////////////////////////////////////
{
	bool b0 = XViewPtToGSPoint32(inxvrv.TopLeft(), outvrv.SetTopLeft());
	bool b1 = XViewPtToGSPoint32(inxvrv.TopRight(), outvrv.SetTopRight());
	bool b2 = XViewPtToGSPoint32(inxvrv.BottomLeft(), outvrv.SetBottomLeft());
	bool b3 = XViewPtToGSPoint32(inxvrv.BottomRight(), outvrv.SetBottomRight());
	
	return b0 && b1 && b2 && b3;
}

/////////////////////////////////////////////////////////////////////////
bool XViewRectVertsToViewRectVerts(const XViewRectVerts& inxvrv, ViewRectVerts& outvrv)
/////////////////////////////////////////////////////////////////////////
{
	bool b0 = XViewPtToViewPt(inxvrv.TopLeft(), outvrv.SetTopLeft());
	bool b1 = XViewPtToViewPt(inxvrv.TopRight(), outvrv.SetTopRight());
	bool b2 = XViewPtToViewPt(inxvrv.BottomLeft(), outvrv.SetBottomLeft());
	bool b3 = XViewPtToViewPt(inxvrv.BottomRight(), outvrv.SetBottomRight());
	
	return b0 && b1 && b2 && b3;
}

/////////////////////////////////////////////////////////////////////////
XViewPt GetXViewLimitRange(EXViewLimits in)
{
	XViewPt outxvptRange(0, 0);

	switch (in) {
		case eXVL_None:				break;
		case eXVL_ViewCoord:		outxvptRange.Set(kGSMinSint16, kGSMaxSint16);	break;
		case eXVL_AccurateFloat:	outxvptRange.Set(kGSMinPreciseFloat, kGSMaxPreciseFloat);	break;
		case eXVL_GSCoord32:		outxvptRange.Set(kGSMinSint32, kGSMaxSint32);	break;
		default: DSTOP((kEveryone, "Unexpected"));
	}

	return outxvptRange;
}

/////////////////////////////////////////////////////////////////////////
bool XViewCoordWithinLimits(XViewCoord inxv, EXViewLimits inLimits)
{
	bool outbWithin = false;
	
	if (inLimits == eXVL_None) {
		 outbWithin = true;
	}
	else {
		XViewPt xvptRange = GetXViewLimitRange(inLimits);

		if (inxv >= xvptRange.x && inxv <= xvptRange.y)
			outbWithin = true;
	}

	return outbWithin;
}

/////////////////////////////////////////////////////////////////////////
bool XViewPtWithinLimits(const XViewPt& inxvpt, EXViewLimits inLimits)
{
	return XViewCoordWithinLimits(inxvpt.x, inLimits)
			&& XViewCoordWithinLimits(inxvpt.y, inLimits);
}

/////////////////////////////////////////////////////////////////////////
bool XViewRectWithinLimits(const XViewRect& inxvr, EXViewLimits inLimits)
{
	return XViewCoordWithinLimits(inxvr.left, inLimits)
			&& XViewCoordWithinLimits(inxvr.top, inLimits)
			&& XViewCoordWithinLimits(inxvr.right, inLimits)
			&& XViewCoordWithinLimits(inxvr.bottom, inLimits);
}

/////////////////////////////////////////////////////////////////////////
bool XViewRectVertsWithinLimits(const XViewRectVerts& inxvrv, EXViewLimits inLimits)
{
	return XViewPtWithinLimits(inxvrv.TopLeft(), inLimits)
			&& XViewPtWithinLimits(inxvrv.TopRight(), inLimits)
			&& XViewPtWithinLimits(inxvrv.BottomLeft(), inLimits)
			&& XViewPtWithinLimits(inxvrv.BottomRight(), inLimits);
}
#endif

/////////////////////////////////////////////////////////////////////////
Bool8 IsGrayscaleColorTable(const GSColor* inpColors, Uint16 inNumColors)
{
	Bool8 outbIsGray = false;
	
	if (VERIFYN(kEJKerr, inpColors)
		&& VERIFYN(kEJKerr, inNumColors > 0 && inNumColors <= 256)
		&& VERIFYPOINTER(kEJKerr, inpColors, inNumColors * sizeof(GSColor))) {
		
		outbIsGray = true;
		
		bool bIncreasing = (inpColors[0] == kGSColor16Black);
		Uint16 adjIndex;
		ColorCoord g;
		GSColor grayColor;
		
		for (Uint16 i=0; i<inNumColors; i++) {
			adjIndex = bIncreasing ? i : (inNumColors-1-i);
			g = (ColorCoord) Round(255.0 * (double)adjIndex / (inNumColors-1));
			g = (g << 8) | g;
			grayColor.Set16(g, g, g);
			
			if (inpColors[i] != grayColor) {
				outbIsGray = false;
				break;
			}
		}
	}
	
	return outbIsGray;
}

/////////////////////////////////////////////////////////////////////////
void SetGrayscaleColorTable(GSColor* pColors, Uint16 inNumColors, bool inbIncreasing/*=true*/)
{
	if (inNumColors == 256) { // faster special case for 256 color, which is common
		ColorCoord g;

		for (Uint16 i=0; i<256; i++) {
			g = inbIncreasing ? i : 255-i;
			g = (g<<8) | g;
			pColors[i].Set16(g, g, g);
		}
	}
	else {
		Uint16 adjIndex;
		ColorCoord g;

		for (Uint16 i=0; i<inNumColors; i++) {
			adjIndex = inbIncreasing ? i : (inNumColors-1-i);
			g = (ColorCoord) Round(255.0 * (double)adjIndex / (inNumColors-1));
			g = (g<<8) | g;
			pColors[i].Set16(g, g, g);
		}
	}
}

/************************************************************************/
/************************************************************************/
//	Implementation for the TGSColorV2 class follows
/************************************************************************/
/************************************************************************/

//----------------------------------------------------------------------------
TGSColorV2::TGSColorV2(TColorType inType, float c1, float c2, float c3, float c4/*=0*/)
{
	switch (inType) {
		case eCMYK:		this->SetCMYK(c1,c2,c3,c4);	break;
		case eRGB:		this->SetRGB(c1,c2,c3);		break;
		case eHSV:		this->SetHSV(c1,c2,c3);		break;

		case eRGB16:	this->SetRGB16(	DemoteTo<Uint16>(kEJKerr, Round(c1)),
										DemoteTo<Uint16>(kEJKerr, Round(c2)),
										DemoteTo<Uint16>(kEJKerr, Round(c3)));	break;

		case eRGB8:		this->SetRGB8(	DemoteTo<Uint8>(kEJKerr, Round(c1)),
										DemoteTo<Uint8>(kEJKerr, Round(c2)),
										DemoteTo<Uint8>(kEJKerr, Round(c3)));	break;

		default:
			DSTOP((kEJKerr, "Unexpected color type."));
			break;
	}
}

TGSColorV2 &TGSColorV2::operator = ( const TGSColorV2 &inCopy )
{
	fType = inCopy.fType;
	
	switch (fType) {
		case eCMYK: {
			fCMYK.c = inCopy.fCMYK.c;
			fCMYK.m = inCopy.fCMYK.m;
			fCMYK.y = inCopy.fCMYK.y;
			fCMYK.k = inCopy.fCMYK.k;
			break;
		}
		case eHSV: {
			fHSV.h = inCopy.fHSV.h;
			fHSV.s = inCopy.fHSV.s;
			fHSV.v = inCopy.fHSV.v;
			break;
		}
		case eRGB: {
			fRGB.r = inCopy.fRGB.r;
			fRGB.g = inCopy.fRGB.g;
			fRGB.b = inCopy.fRGB.b;
			break;
		}
		case eRGB16: {
			fRGB16.r = inCopy.fRGB16.r;
			fRGB16.g = inCopy.fRGB16.g;
			fRGB16.b = inCopy.fRGB16.b;
			break;
		}
		case eRGB8: {
			fRGB8.r = inCopy.fRGB8.r;
			fRGB8.g = inCopy.fRGB8.g;
			fRGB8.b = inCopy.fRGB8.b;
			break;
		}
		default:
			DSTOP((kEJKerr, "Unexpected TColorType"));
	}
	
	return *this;
}


//----------------------------------------------------------------------------
void TGSColorV2::GetCMYK(TUnitColorComponent& c, TUnitColorComponent& m, TUnitColorComponent& y, TUnitColorComponent& k) const
{
	if (fType == eCMYK) {
		c = fCMYK.c;
		m = fCMYK.m;
		y = fCMYK.y;
		k = fCMYK.k;
	}
	else {
		TUnitColorComponent r,g,b;
		this->GetRGB(r,g,b);
		RGBToCMYK(r,g,b, c,m,y,k);
	}
}

//----------------------------------------------------------------------------
void TGSColorV2::GetHSV(THueColorComponent& h, TUnitColorComponent& s, TUnitColorComponent& v) const
{
	if (fType == eHSV) {
		h = fHSV.h;
		s = fHSV.s;
		v = fHSV.v;
	}
	else {
		TUnitColorComponent r,g,b;
		this->GetRGB(r,g,b);
		RGBToHSV(r,g,b, h,s,v);
	}
}

//----------------------------------------------------------------------------
void TGSColorV2::GetLuminance(TUnitColorComponent& outLuma) const
{
	TUnitColorComponent r,g,b;
	this->GetRGB(r,g,b);

	outLuma = PinUnitComponentInRange((TUnitColorComponent)CalcLuminance(r, g, b), false/*inbAssert*/);
}

//----------------------------------------------------------------------------
void TGSColorV2::GetRGB(TUnitColorComponent& r, TUnitColorComponent& g, TUnitColorComponent& b) const
{
	switch (fType) {
		case eCMYK: {
			CMYKToRGB(fCMYK.c,fCMYK.m,fCMYK.y,fCMYK.k, r,g,b);
			break;
		}
		case eHSV: {
			HSVToRGB(fHSV.h,fHSV.s,fHSV.v, r,g,b);
			break;
		}
		case eRGB: {
			r = fRGB.r;
			g = fRGB.g;
			b = fRGB.b;
			break;
		}
		case eRGB16: {
			r = fRGB16.r / (TUnitColorComponent)kGSMaxUint16;
			g = fRGB16.g / (TUnitColorComponent)kGSMaxUint16;
			b = fRGB16.b / (TUnitColorComponent)kGSMaxUint16;
			break;
		}
		case eRGB8: {
			r = fRGB8.r / (TUnitColorComponent)kGSMaxUint8;
			g = fRGB8.g / (TUnitColorComponent)kGSMaxUint8;
			b = fRGB8.b / (TUnitColorComponent)kGSMaxUint8;
			break;
		}
		default:
			DSTOP((kEJKerr, "Unexpected TColorType"));
	}
}
	
//----------------------------------------------------------------------------
void TGSColorV2::GetRGB16(Uint16& r, Uint16& g, Uint16& b) const
{
	switch (fType) {
		case eCMYK:
		case eHSV: {
			TUnitColorComponent rf=0,gf=0,bf=0;
			this->GetRGB(rf,gf,bf);
			r = DemoteTo<Uint16>(kEJKerr, Round(rf * kGSMaxUint16));
			g = DemoteTo<Uint16>(kEJKerr, Round(gf * kGSMaxUint16));
			b = DemoteTo<Uint16>(kEJKerr, Round(bf * kGSMaxUint16));
			break;
		}
		case eRGB: {
			r = DemoteTo<Uint16>(kEJKerr, Round(fRGB.r * kGSMaxUint16));
			g = DemoteTo<Uint16>(kEJKerr, Round(fRGB.g * kGSMaxUint16));
			b = DemoteTo<Uint16>(kEJKerr, Round(fRGB.b * kGSMaxUint16));
			break;
		}
		case eRGB16: {
			r = fRGB16.r;
			g = fRGB16.g;
			b = fRGB16.b;
			break;
		}
		case eRGB8: {
			r = ((Uint16)fRGB8.r << 8) + fRGB8.r;
			g = ((Uint16)fRGB8.g << 8) + fRGB8.g;
			b = ((Uint16)fRGB8.b << 8) + fRGB8.b;
			break;
		}
		default:
			DSTOP((kEJKerr, "Unexpected TColorType"));
	}
}
	
//----------------------------------------------------------------------------
void TGSColorV2::GetRGB8(Uint8& r, Uint8& g, Uint8& b) const
{
	switch (fType) {
		case eCMYK:
		case eHSV: {
			TUnitColorComponent rf=0,gf=0,bf=0;
			this->GetRGB(rf,gf,bf);
			r = DemoteTo<Uint8>(kEJKerr, Round(rf * kGSMaxUint8));
			g = DemoteTo<Uint8>(kEJKerr, Round(gf * kGSMaxUint8));
			b = DemoteTo<Uint8>(kEJKerr, Round(bf * kGSMaxUint8));
			break;
		}
		case eRGB: {
			r = DemoteTo<Uint8>(kEJKerr, Round(fRGB.r * kGSMaxUint8));
			g = DemoteTo<Uint8>(kEJKerr, Round(fRGB.g * kGSMaxUint8));
			b = DemoteTo<Uint8>(kEJKerr, Round(fRGB.b * kGSMaxUint8));
			break;
		}
		case eRGB16: {
			r = DemoteTo<Uint8>(kEJKerr, fRGB16.r >> 8);
			g = DemoteTo<Uint8>(kEJKerr, fRGB16.g >> 8);
			b = DemoteTo<Uint8>(kEJKerr, fRGB16.b >> 8);
			break;
		}
		case eRGB8: {
			r = fRGB8.r;
			g = fRGB8.g;
			b = fRGB8.b;
			break;
		}
		default:
			DSTOP((kEJKerr, "Unexpected TColorType"));
	}
}

//----------------------------------------------------------------------------
void TGSColorV2::GetGSColor(GSColor& out) const
{
	Uint8 r=0, g=0, b=0;
	
	this->GetRGB8(r, g, b);
	
	out.red		= r;
	out.green	= g;
	out.blue	= b;
}

//----------------------------------------------------------------------------
void TGSColorV2::SetCMYK(TUnitColorComponent c, TUnitColorComponent m, TUnitColorComponent y, TUnitColorComponent k)
{
	fType = eCMYK;
	fCMYK.c = PinUnitComponentInRange(c);
	fCMYK.m = PinUnitComponentInRange(m);
	fCMYK.y = PinUnitComponentInRange(y);
	fCMYK.k = PinUnitComponentInRange(k);
}

//----------------------------------------------------------------------------
void TGSColorV2::SetHSV(THueColorComponent h, TUnitColorComponent s, TUnitColorComponent v)
{
	fType = eHSV;
	fHSV.h = PinHueComponentInRange(h);
	fHSV.s = PinUnitComponentInRange(s);
	fHSV.v = PinUnitComponentInRange(v);
}

//----------------------------------------------------------------------------
void TGSColorV2::SetRGB(TUnitColorComponent r, TUnitColorComponent g, TUnitColorComponent b)
{
	fType = eRGB;
	fRGB.r = PinUnitComponentInRange(r);
	fRGB.g = PinUnitComponentInRange(g);
	fRGB.b = PinUnitComponentInRange(b);
}

//----------------------------------------------------------------------------
void TGSColorV2::SetGSColor(const GSColor& in)
{
	this->SetRGB8(DemoteTo<Uint8>(kEJKerr, PinGSColorComponentInRange(in.red)),
				DemoteTo<Uint8>(kEJKerr, PinGSColorComponentInRange(in.green)),
				DemoteTo<Uint8>(kEJKerr, PinGSColorComponentInRange(in.blue)));
}

//----------------------------------------------------------------------------
void TGSColorV2::Set(TColorType& inNewType, const TGSColorV2& inColor)
{
	// inColor could be *this, so we need to make a temp copy
	TGSColorV2 tempColor(inColor);

	fType = inNewType;
	
	switch (inNewType) {
		case eCMYK:		tempColor.GetCMYK(fCMYK.c, fCMYK.m, fCMYK.y, fCMYK.k);	break;
		case eHSV:		tempColor.GetHSV(fHSV.h, fHSV.s, fHSV.v);					break;
		case eRGB:		tempColor.GetRGB(fRGB.r, fRGB.g, fRGB.b);					break;
		case eRGB16:	tempColor.GetRGB16(fRGB16.r, fRGB16.g, fRGB16.b);			break;
		case eRGB8:		tempColor.GetRGB8(fRGB8.r, fRGB8.g, fRGB8.b);				break;
		default:
			DSTOP((kEJKerr, "Unexpected TColorType"));
	}
}


void TGSColorV2::BlendAlphaWithColor( OpacityRef inOpacity, TGSColorV2 color )
{
	double opacity = (double)inOpacity / (double)100;
	
	this->ConvertTo( eRGB16 );
	color.ConvertTo( eRGB16 );
	
	//
	// The formula used was found at
	//
	// http://en.wikipedia.org/wiki/Alpha_compositing
	//
	// and is Value = ( 1 - a ) * Value0 + a * Value1
	// where all variables are between 0 - 1.0
	//
	double V0Red	= (double)color.fRGB16.r / (double)65535.0;
	double V0Green	= (double)color.fRGB16.g / (double)65535.0;
	double V0Blue	= (double)color.fRGB16.b / (double)65535.0;

	double V1Red	= (double)fRGB16.r / (double)65535.0;
	double V1Green	= (double)fRGB16.g / (double)65535.0;
	double V1Blue	= (double)fRGB16.b / (double)65535.0;
	
	double red		= ( ( 1.0 - opacity ) * V0Red ) + ( opacity * V1Red );
	double green	= ( ( 1.0 - opacity ) * V0Green ) + ( opacity * V1Green );
	double blue		= ( ( 1.0 - opacity ) * V0Blue ) + ( opacity * V1Blue );
	
	fRGB16.r = DemoteTo<Uint16>(kEGorr, floor( ( red * 65535.0 ) + 0.5 ) );
	fRGB16.g = DemoteTo<Uint16>(kEGorr, floor( ( green * 65535.0 ) + 0.5 ) );
	fRGB16.b = DemoteTo<Uint16>(kEGorr, floor( ( blue * 65535.0 ) + 0.5 ) );
}



inline float fastAbsf(float in) { return in > 0 ? in : -in; }

//----------------------------------------------------------------------------
float TGSColorV2::Compare(const TGSColorV2& right, TGSColorV2::TColorType inCompareType, float epsilon/*=0*/) const
// returns result<0 if we are < right, result>0 if we are > right.  Magnitude depends on comparison.
// returns result=0 if we are equal right
{
	float result = 0;

	switch (inCompareType) {
		case TGSColorV2::eCMYK: {
			TUnitColorComponent c,m,y,k;
			this->GetCMYK(c,m,y,k);

			TUnitColorComponent rc,rm,ry,rk;
			right.GetCMYK(rc,rm,ry,rk);

			result = c - rc;

			if (epsilon == 0) {
				if (result == 0) {
					result = m - rm;

					if (result == 0) {
						result =  y - ry;

						if (result == 0) {
							result = k - rk;
						}
					}
				}
			}
			else {
				if (fastAbsf(result) < epsilon) {
					result = m - rm;

					if (fastAbsf(result) < epsilon) {
						result =  y - ry;

						if (fastAbsf(result) < epsilon) {
							result = k - rk;

							if (fastAbsf(result) < epsilon) {
								result = 0;
							}
						}
					}
				}
			}
			break;
		}

		case TGSColorV2::eRGB: {
			TUnitColorComponent r,g,b;
			this->GetRGB(r,g,b);

			TUnitColorComponent rr,rg,rb;
			right.GetRGB(rr,rg,rb);

			result = r - rr;

			if (epsilon == 0) {
				if (result == 0) {
					result = g - rg;

					if (result == 0) {
						result = b - rb;
					}
				}
			}
			else {
				if (fastAbsf(result) < epsilon) {
					result = g - rg;

					if (fastAbsf(result) < epsilon) {
						result = b - rb;

						if (fastAbsf(result) < epsilon) {
							result = 0;
						}
					}
				}
			}
			break;
		}

		case TGSColorV2::eHSV: {
			TUnitColorComponent h,s,v;
			this->GetHSV(h,s,v);

			TUnitColorComponent rh,rs,rv;
			right.GetHSV(rh,rs,rv);

			result = h - rh;

			if (epsilon == 0) {
				if (result == 0) {
					result = s - rs;

					if (result == 0) {
						result = v - rv;
					}
				}
			}
			else {
				if (fastAbsf(result) < epsilon) {
					result = s - rs;

					if (fastAbsf(result) < epsilon) {
						result = v - rv;

						if (fastAbsf(result) < epsilon) {
							result = 0;
						}
					}
				}
			}
			break;
		}

		case TGSColorV2::eRGB16: {
			Uint16 r,g,b;
			this->GetRGB16(r,g,b);

			Uint16 rr,rg,rb;
			right.GetRGB16(rr,rg,rb);

			Sint32 nResult32 = (Sint32)r - (Sint32)rr;

			if (nResult32 == 0) {
				nResult32 = (Sint32)g - (Sint32)rg;

				if (nResult32 == 0) {
					nResult32 = (Sint32)b - (Sint32)rb;
				}
			}

			result = (float) nResult32;
			break;
		}

		case TGSColorV2::eRGB8: {
			Uint8 r,g,b;
			this->GetRGB8(r,g,b);

			Uint8 rr,rg,rb;
			right.GetRGB8(rr,rg,rb);

			Sint16 nResult16 = (Sint16)r - (Sint16)rr;

			if (nResult16 == 0) {
				 nResult16 = (Sint16)g - (Sint16)rg;

				if (nResult16 == 0) {
					nResult16 = (Sint16)b - (Sint16)rb;
				}
			}

			result = (float) nResult16;
			break;
		}

		default: {
			DSTOP((kEJKerr, "Unexpected"));
			break;
		}
	}

	return result;
}

//----------------------------------------------------------------------------
bool TGSColorV2::LessThan(const TGSColorV2& right, TGSColorV2::TColorType inCompareType, float epsilon/*=0*/) const
{
	return this->Compare(right, inCompareType, epsilon) < 0;
}

//----------------------------------------------------------------------------
bool TGSColorV2::EqualTo(const TGSColorV2& right, TGSColorV2::TColorType inCompareType, float epsilon/*=0*/) const
{
	return this->Compare(right, inCompareType, epsilon) == 0;
}

//----------------------------------------------------------------------------
inline double	MyDiffSqrd(const double v1, const double v2) { const double v = v1-v2; return v*v; }

//----------------------------------------------------------------------------
double TGSColorV2::DistanceSquared(const TGSColorV2& right, TGSColorV2::TColorType inCompareType) const
{
	double d2 = 0;

	switch (inCompareType) {
		case TGSColorV2::eCMYK: {
			TUnitColorComponent c,m,y,k;
			this->GetCMYK(c,m,y,k);

			TUnitColorComponent rc,rm,ry,rk;
			right.GetCMYK(rc,rm,ry,rk);

			d2 = MyDiffSqrd(c,rc) + MyDiffSqrd(m,rm) + MyDiffSqrd(y,ry) + MyDiffSqrd(k,rk);
			break;
		}

		case TGSColorV2::eRGB: {
			TUnitColorComponent r,g,b;
			this->GetRGB(r,g,b);

			TUnitColorComponent rr,rg,rb;
			right.GetRGB(rr,rg,rb);

			d2 = MyDiffSqrd(r,rr) + MyDiffSqrd(g,rg) + MyDiffSqrd(b,rb);
			break;
		}

		case TGSColorV2::eHSV: {
			TUnitColorComponent h,s,v;
			this->GetHSV(h,s,v);

			TUnitColorComponent rh,rs,rv;
			right.GetHSV(rh,rs,rv);

			d2 = MyDiffSqrd(s,rs) + MyDiffSqrd(v,rv);

			if (h != kUndefinedHueColorComponent && rh != kUndefinedHueColorComponent)
				d2 += MyDiffSqrd(h,rh);
			break;
		}

		case TGSColorV2::eRGB16: {
			Uint16 r,g,b;
			this->GetRGB16(r,g,b);

			Uint16 rr,rg,rb;
			right.GetRGB16(rr,rg,rb);

			d2 = MyDiffSqrd(r,rr) + MyDiffSqrd(g,rg) + MyDiffSqrd(b,rb);
			break;
		}

		case TGSColorV2::eRGB8: {
			Uint8 r,g,b;
			this->GetRGB8(r,g,b);

			Uint8 rr,rg,rb;
			right.GetRGB8(rr,rg,rb);

			d2 = MyDiffSqrd(r,rr) + MyDiffSqrd(g,rg) + MyDiffSqrd(b,rb);
			break;
		}

		default: {
			DSTOP((kEJKerr, "Unexpected"));
			break;
		}
	}

	return d2;
}

//----------------------------------------------------------------------------
bool TGSColorV2::operator<(const TGSColorV2& right) const
// This operator just compares based on the format of the left (this) item.
// You can use the LessThan function to make comparisons in other formats.
{
	return this->LessThan(right, fType);
}

//----------------------------------------------------------------------------
bool TGSColorV2::operator==(const TGSColorV2& right) const
// This operator just compares based on the format of the left (this) item.
// You can use the EqualTo function to make comparisons in other formats.
{
	return this->EqualTo(right, fType);
}

///////////////////////////////////////////////////////////////////////////////
// statics
///////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
// T02217: CMYK Improvement.
// Keep previous version for forward and backward translation.
void TGSColorV2::CMYKToRGBVW26AndEarlier(TUnitColorComponent c, TUnitColorComponent m, TUnitColorComponent y, TUnitColorComponent k,
						TUnitColorComponent& r, TUnitColorComponent& g, TUnitColorComponent& b)
// static
{
	c = PinUnitComponentInRange(c);
	m = PinUnitComponentInRange(m);
	y = PinUnitComponentInRange(y);
	k = PinUnitComponentInRange(k);

	r = kMaxUnitColorComponent - PinUnitComponentInRange(c + k, false);
	g = kMaxUnitColorComponent - PinUnitComponentInRange(m + k, false);
	b = kMaxUnitColorComponent - PinUnitComponentInRange(y + k, false);
}

//----------------------------------------------------------------------------
// T02217: CMYK Improvement.
// Keep previous version for forward and backward translation.
void TGSColorV2::RGBToCMYKVW26AndEarlier(TUnitColorComponent r, TUnitColorComponent g, TUnitColorComponent b,
						TUnitColorComponent& c, TUnitColorComponent& m, TUnitColorComponent& y, TUnitColorComponent& k)
{
	r = PinUnitComponentInRange(r);
	g = PinUnitComponentInRange(g);
	b = PinUnitComponentInRange(b);

	c = kMaxUnitColorComponent - r;
	m = kMaxUnitColorComponent - g;
	y = kMaxUnitColorComponent - b;
		
	k = min(min(c,m), min(m,y));
		
	c -= k;
	m -= k;
	y -= k;
}

//----------------------------------------------------------------------------
// T02217: CMYK Improvement.
// Apply Wikipedia formula.
void TGSColorV2::CMYKToRGB(TUnitColorComponent c, TUnitColorComponent m, TUnitColorComponent y, TUnitColorComponent k,
						TUnitColorComponent& r, TUnitColorComponent& g, TUnitColorComponent& b)
// static
{
	c = PinUnitComponentInRange(c);
	m = PinUnitComponentInRange(m);
	y = PinUnitComponentInRange(y);
	k = PinUnitComponentInRange(k);

	//
	// from http://en.wikipedia.org/wiki/CMYK_color_model
	//
	// {R,G,B} = {(1-C)*(1-K), (1-M)*(1-K), (1-Y)*(1-K)}
	//

	TUnitColorComponent omk = kMaxUnitColorComponent-k;

	r = (kMaxUnitColorComponent-c)*omk;
	g = (kMaxUnitColorComponent-m)*omk;
	b = (kMaxUnitColorComponent-y)*omk;
}

//----------------------------------------------------------------------------
// T02217: CMYK Improvement.
// Apply Wikipedia formula.
void TGSColorV2::RGBToCMYK(TUnitColorComponent r, TUnitColorComponent g, TUnitColorComponent b,
						TUnitColorComponent& c, TUnitColorComponent& m, TUnitColorComponent& y, TUnitColorComponent& k)
// static
{
	r = PinUnitComponentInRange(r);
	g = PinUnitComponentInRange(g);
	b = PinUnitComponentInRange(b);

	//
	// from http://en.wikipedia.org/wiki/CMYK_color_model
	//
	// {c1,m1,y1} = {1-R, 1-G, 1-B}
	// K = min{c1,m1,y1}
	//
	// if K == 1 then
	//		{C,M,Y,K} = {0,0,0,1}
	// else 
	//		{C,M,Y,K} = {(c1-K)/(1-K), (m1-K)/(1-K), (y1-K)/(1-K)}
	//

	c = kMaxUnitColorComponent - r;
	m = kMaxUnitColorComponent - g;
	y = kMaxUnitColorComponent - b;
	
	k = min(min(c,m), min(m,y));
	
	if (k == kMaxUnitColorComponent) {
		c = m = y = 0;
	}
	else {
		TUnitColorComponent omk = kMaxUnitColorComponent-k;

		c = (c-k)/omk;
		m = (m-k)/omk;
		y = (y-k)/omk;
	}
}

//----------------------------------------------------------------------------
// T02217: CMYK Improvement.
// Apply Wikipedia formula. Keep this funtion for perference CMYK translate and future use.
void TGSColorV2::TranslateCMYK()
{
	TUnitColorComponent r, g, b;

	if (fType == eCMYK)
	{
		CMYKToRGBVW26AndEarlier(fCMYK.c, fCMYK.m, fCMYK.y, fCMYK.k, r, g, b);
		RGBToCMYK(r, g, b, fCMYK.c, fCMYK.m, fCMYK.y, fCMYK.k);
	}
}

//----------------------------------------------------------------------------
void TGSColorV2::HSVToRGB(THueColorComponent h, TUnitColorComponent s, TUnitColorComponent v,
						TUnitColorComponent& r, TUnitColorComponent& g, TUnitColorComponent& b)
// static
{
	h = PinHueComponentInRange(h);
	s = PinUnitComponentInRange(s);
	v = PinUnitComponentInRange(v);

	if (h == kUndefinedHueColorComponent) {
		if ( ! VERIFYN(kEJKerr, s == kMinUnitColorComponent)) {
			s = kMinUnitColorComponent;
		}
	}

	if (s == kMinUnitColorComponent) {
		if ( ! VERIFYN(kEJKerr, h == kUndefinedHueColorComponent)) {
			h = kUndefinedHueColorComponent;
		}
	}

	if (s == kMinUnitColorComponent) { // grey
		r = g = b = v;
	}
	else {
		const float kSectorSize = kMaxHueColorComponent / 6;
		float	sectorH = h / kSectorSize;		// sector (0.0 to <6.0)
		Sint32		isectorH = DemoteTo<Sint32>(kEJKerr, Truncate(sectorH));	// integer part of sector (0 to 5)
		float	fsectorH = sectorH - isectorH;	// fractional part of sector (0.0 to <1.0)

		TUnitColorComponent p = v * ( 1 - s );
		TUnitColorComponent q = v * ( 1 - s * fsectorH );
		TUnitColorComponent t = v * ( 1 - s * ( 1 - fsectorH ) );

		switch (isectorH) {
			case 0:	r = v;	g = t;	b = p; break;
			case 1:	r = q;	g = v;	b = p; break;
			case 2:	r = p;	g = v;	b = t; break;
			case 3:	r = p;	g = q;	b = v; break;
			case 4:	r = t;	g = p;	b = v; break;
			case 5:	r = v;	g = p;	b = q; break;
			default:
				DSTOP((kEJKerr, "Impossible"));
		}
	}
}

//----------------------------------------------------------------------------
void TGSColorV2::RGBToHSV(TUnitColorComponent r, TUnitColorComponent g, TUnitColorComponent b,
						THueColorComponent& h, TUnitColorComponent& s, TUnitColorComponent& v)
// static
{
	r = PinUnitComponentInRange(r);
	g = PinUnitComponentInRange(g);
	b = PinUnitComponentInRange(b);

	TUnitColorComponent theMin	= min(min(r,g),b);
	TUnitColorComponent theMax	= max(max(r,g),b);
	TUnitColorComponent delta	= theMax - theMin;

	v = theMax;

	if (delta == 0) { // r == g == b (gray),  s = 0, h is undefined
		s = kMinUnitColorComponent;
		h = kUndefinedHueColorComponent;
	}
	else {
		s = delta / theMax;

		// In the Hue range, Hue==0 is red, and color varies from 
		// Red->Yellow->Green->Cyan->Blue->Magenta->Red
		// as Hue goes from 0 to 360.
		if (r == theMax)
			h = (g - b) / delta;		// between yellow & magenta
		else if (g == theMax)
			h = 2 + (b - r) / delta;	// between cyan & yellow
		else
			h = 4 + (r - g) / delta;	// between magenta & cyan

		// The above calculations produce an h between -1.0 and 5.0.
		// We just need to normalize this to the standard hue range.
		h *= (kMaxHueColorComponent / 6);
		if (h < kMinHueColorComponent)
			h += kMaxHueColorComponent;
	}
}

//----------------------------------------------------------------------------
THueColorComponent TGSColorV2::PinHueComponentInRange(THueColorComponent inHue, Bool8 bAssert/*= true*/)
// static
{
	if (bAssert) {
		ASSERTN(kEJKerr, inHue == kUndefinedHueColorComponent || (inHue >= kMinHueColorComponent && inHue < kMaxHueColorComponent));
	}

	THueColorComponent outHue = inHue;

	if (inHue != kUndefinedHueColorComponent) {
		outHue = PIN(inHue, kMinHueColorComponent, kMaxHueColorComponent);

		// 0 <= hue < 360
		if (outHue == kMaxHueColorComponent)
			outHue = kMinHueColorComponent;
	}

	return outHue;
}

//----------------------------------------------------------------------------
TUnitColorComponent TGSColorV2::PinUnitComponentInRange(TUnitColorComponent c, Bool8 bAssert/*= true*/)
// static
{
	if (bAssert) {
		ASSERTN(kEJKerr, c >= kMinUnitColorComponent && c <= kMaxUnitColorComponent);
	}
	
	return PIN(c, kMinUnitColorComponent, kMaxUnitColorComponent);
}

//----------------------------------------------------------------------------
Uint16 TGSColorV2::PinGSColorComponentInRange(Uint16 c, Bool8 bAssert/*= true*/)
// static
//
// We expect GSColors that use only the lower 8bits.
// The upper 8 bits are only used in bitmap color tables.
{
	if (bAssert) {
		ASSERTN(kEJKerr, c <= kGSMaxUint8);
	}
	
	return PIN(c, 0, kGSMaxUint8);
}

//----------------------------------------------------------------------------
TColorShadeFactor TGSColorV2::PinShadeFactorInRange(TColorShadeFactor inShadeFactor)
// static
{
	ASSERTN(kEJKerr, inShadeFactor >= kMinColorShadeFactor && inShadeFactor <= kMaxColorShadeFactor);
	return PIN(inShadeFactor, kMinColorShadeFactor, kMaxColorShadeFactor);
}

//----------------------------------------------------------------------------
TColorBlendFactor TGSColorV2::PinBlendFactorInRange(TColorBlendFactor inBlendFactor)
// static
{
	ASSERTN(kEJKerr, inBlendFactor >= kMinColorBlendFactor && inBlendFactor <= kMaxColorBlendFactor);
	return PIN(inBlendFactor, kMinColorBlendFactor, kMaxColorBlendFactor);
}

//----------------------------------------------------------------------------
TUnitColorComponent TGSColorV2::ShadeRGBComponent(TUnitColorComponent inComp, TColorShadeFactor inShadeFactor)
// static
{
	TUnitColorComponent outComp;

	inComp = PinUnitComponentInRange(inComp);

	if (inShadeFactor > 0) {
		outComp = inComp + (1 - inComp) * inShadeFactor;
	}
	else {
		outComp = inComp + inComp * inShadeFactor;
	}

	return outComp;
}

//----------------------------------------------------------------------------
void TGSColorV2::ShadeColor(const TGSColorV2& in, TColorShadeFactor inShadeFactor, TGSColorV2& out)
// static
{
	TColorShadeFactor shadeFactor = PinShadeFactorInRange(inShadeFactor);

	TUnitColorComponent r,g,b;
	in.GetRGB(r,g,b);

	r = ShadeRGBComponent(r, shadeFactor);
	g = ShadeRGBComponent(g, shadeFactor);
	b = ShadeRGBComponent(b, shadeFactor);

	out.SetRGB(r,g,b);
}

//---------------------------------------------------------------------------------------
void TGSColorV2::BlendColors(const TGSColorV2& inC1, const TGSColorV2& inC0, TColorBlendFactor inBlendFactor, TGSColorV2& out)
// static 
{
	TColorBlendFactor fact = PinBlendFactorInRange(inBlendFactor);

	Uint8 r1, g1, b1, r0, g0, b0, r, g, b;

	inC1.GetRGB8(r1, g1, b1);
	inC0.GetRGB8(r0, g0, b0);

	float notfact = (float)1-fact;

	r = (Uint8)(fact*r1 + notfact*r0);
	g = (Uint8)(fact*g1 + notfact*g0);
	b = (Uint8)(fact*b1 + notfact*b0);

	out.SetRGB8(r, g, b);
}

//////////////////////////////////////////////////////////////////////////////
// GSPoly Implementation
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
Sint16	GSPoly::GetNumPts() const
{
	return (Sint16)(polySize - offsetof(GSPoly, polyPoints[0])) / sizeof(ViewPt);
}

//----------------------------------------------------------------------------
void GSPoly::CalcBBox()
{
	Sint32 numPoints = this->GetNumPts();
	
	if (numPoints > 0) {
		polyBBox.left	= polyBBox.right	= polyPoints[0].x;
		polyBBox.top	= polyBBox.bottom	= polyPoints[0].y;
		
		for (Sint32 i=1; i<numPoints; i++) {
			if (polyPoints[i].x < polyBBox.left)
				polyBBox.left = polyPoints[i].x;
			else if (polyPoints[i].x > polyBBox.right)
				polyBBox.right = polyPoints[i].x;
				
			if (polyPoints[i].y < polyBBox.top)
				polyBBox.top = polyPoints[i].y;
			else if (polyPoints[i].y > polyBBox.bottom)
				polyBBox.bottom = polyPoints[i].y;
		}
	}
	else {
		polyBBox.MakeEmpty();
	}
}

//----------------------------------------------------------------------------
Sint16 GSPoly::CalcSize(Sint16 numPts)
// static
{
	return sizeof(GSPoly) + (numPts-1)*sizeof(ViewPt); 
}


//////////////////////////////////////////////////////////////////////////////
// XViewPt Implementation
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
XViewPt::XViewPt(const GSPoint32& v)
{
	x = v.x;
	y = v.y;
}

//----------------------------------------------------------------------------
Bool8 XViewPt::operator==(const XViewPt& inxvpt) const
{
	return DoublesAreNearlyEqual(y, inxvpt.y, kNearlyEqualEpsilonForDoubles)
			&& DoublesAreNearlyEqual(x, inxvpt.x, kNearlyEqualEpsilonForDoubles);
}

//----------------------------------------------------------------------------
XViewCoord XViewPt::Magnitude(void) const
{ 
	return sqrt(x*x + y*y); 
}

//----------------------------------------------------------------------------
void XViewPt::Scale(const double f, const XViewPt* pAboutPt/*=NULL*/)
{
	if (pAboutPt) {
		x = (x-pAboutPt->x)*f + pAboutPt->x;
		y = (y-pAboutPt->y)*f + pAboutPt->y;
	}
	else {
		x *= f;
		y *= f;
	}
}


//////////////////////////////////////////////////////////////////////////////
// ViewPt Implementation
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
Sint32 ViewPt::Magnitude(void) const 
{ 
	return (Sint32) sqrt(double((Sint32) x * (Sint32) x + (Sint32) y * (Sint32) y)); 
}

