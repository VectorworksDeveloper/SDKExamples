//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

typedef Sint16  ViewCoord;
typedef Sint32  ViewCoordLong;

ViewCoord SafeAdd(ViewCoord v1, ViewCoord v2);

#ifdef __cplusplus

	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------
	//
	// ViewPt
	//
	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------


	// WorldSpace and ViewSpace conversion functions are in TDQuickDraw.h.
	//
	// Mac and Win conversion functions are in MCCoordTypes.h:
	// 
	//     ViewPt   MacToViewPt(const Point&  p);
	//     Point    ViewToMacPt(const ViewPt& p);
	//
	//     POINT    ViewToWinPt  (const ViewPt& p);
	//     ViewPt   WinToViewPt  (const POINT&  p);


	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	class ViewPt;

	class ViewPt_ {
	public:
		ViewCoord y; 
		ViewCoord x; 

		operator const ViewPt&() const  { return *((const ViewPt*) this); }
		operator       ViewPt&()		{ return       *((ViewPt*) this); }

		ViewPt* operator&(void)	 			    { return (ViewPt *) this; }
		const ViewPt* operator&(void) const 	{ return (const ViewPt *) this; }

		Boolean operator==(const ViewPt_& p) const { return y == p.y && x == p.x; }
		Boolean operator!=(const ViewPt_& p) const { return y != p.y || x != p.x; }
	};

	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------


	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	class ViewPt : public ViewPt_ {
	public:
		ViewPt() { x = y = 0;}
		ViewPt(ViewCoord xIn, ViewCoord yIn) { x = xIn; y = yIn; }
		
		ViewPt&	operator=(const ViewPt& p) { x = p.x; y = p.y; return *this; }

		Bool8 operator==(const ViewPt& pt) const { return ((pt.x == x) && (pt.y == y)); }
		Bool8 operator!=(const ViewPt& pt) const { return !(*this == pt); }

		ViewPt operator+(const ViewPt& p) const	{ return ViewPt(x + p.x, y + p.y); }
		ViewPt operator-(const ViewPt& p) const	{ return ViewPt(x - p.x, y - p.y); }

		void Set(ViewCoord X, ViewCoord Y) { x = X; y = Y; }

		void Offset(ViewCoord dx, ViewCoord dy) { x += dx; y += dy; }
		void SafeOffset(ViewCoord dx,  ViewCoord dy)
		{
			x = SafeAdd(x, dx);
			y = SafeAdd(y, dy);
		}

		// Note! These use longs because we know ViewCoords are shorts. If/when ViewCoords become something 
		// else (doubles, say), these longs need to become doubles. [MAF 3/3/00]

		Sint32 Magnitude(void)        const; /* { return (Sint32) sqrt(double((Sint32) x * (Sint32) x + (Sint32) y * (Sint32) y)); } */
		Sint32 MagnitudeSquared(void) const { return (Sint32) x * (Sint32) x + (Sint32) y * (Sint32) y; }

		Sint32 DistanceFrom(const ViewPt& otherPoint) const 
		{ 
			Sint32 distance = (Sint32)sqrt(SquaredDistanceFrom(otherPoint));
			return distance;
		}

 		double SquaredDistanceFrom(const ViewPt& otherPoint) const { 
			double sqDist = (((double)x - (double)otherPoint.x) * ((double)x - (double)otherPoint.x)) +
							(((double)y - (double)otherPoint.y) * ((double)y - (double)otherPoint.y));
			return sqDist;
		}

		void ByteSwap();
	};
	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------

	// This is a dup of the regular Num2Short that's in MCFloat.h, which apparently can't be included in this file. [MAF 12/8/05]
	inline short Num2ShortLocal(double x)
	{
		return (x >  32767) ? (short)  32767     :
			(x < -32767) ? (short) -32767     :
			(x >  0)     ? (short)  (x + 0.5000000001) :
			(x <  0)     ? (short)  (x - 0.5000000001) :
							(short)  0;
	}


	inline ViewPt operator*(const double scalar, const ViewPt thePt)	{ return ViewPt(Num2ShortLocal(thePt.x * scalar), Num2ShortLocal(thePt.y * scalar)); }
	inline ViewPt operator/(const ViewPt thePt, const double scalar)	{ return ViewPt(Num2ShortLocal(thePt.x / scalar), Num2ShortLocal(thePt.y / scalar)); }

	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------
	// TCellID
	//
	// replaces Cell structure defined by Quicktime
	//
	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------
	typedef ViewPt TCellID;
	
	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------
	//
	// XViewCoord / XViewPt / XViewRect
	//
	// double versions of ViewCoord, ViewPt and ViewRect
	//
	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------

	typedef double XViewCoord;

	inline bool FloatConversionWillBePrecise(double in)	{ return in >= (double)kGSMinPreciseFloat && in <= (double)kGSMaxPreciseFloat; }

	class GSPoint32; // forward declaration

	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	class XViewPt {
	public:
		XViewCoord y; 
		XViewCoord x; 

		XViewPt() { x = y = 0;}
		XViewPt(const ViewPt& v) { x = v.x; y = v.y; }
		XViewPt(const GSPoint32& v);
		XViewPt(XViewCoord xIn, XViewCoord yIn) { x = xIn; y = yIn; }

		XViewPt& operator=(const XViewPt& p) { x = p.x; y = p.y; return *this; }

		Bool8 operator==(const XViewPt& pt) const;
		Bool8 operator!=(const XViewPt& pt) const { return !(*this == pt); }

		XViewPt operator+(const XViewPt& p) const	{ return XViewPt(x + p.x, y + p.y); }
		XViewPt operator-(const XViewPt& p) const	{ return XViewPt(x - p.x, y - p.y); }

		XViewPt	operator*(XViewCoord scalar) const	{ return XViewPt((x * scalar), (y * scalar)); }
		XViewPt	operator/(XViewCoord scalar) const	{ return XViewPt((x / scalar), (y / scalar)); }

		XViewPt operator-(void) const				{ return XViewPt(-x, -y); }

		XViewPt& operator+=(const XViewPt& p)	{ x += p.x;    y += p.y;    return *this; }
		XViewPt& operator-=(const XViewPt& p)	{ x -= p.x;    y -= p.y;    return *this; }
		XViewPt& operator*=(XViewCoord scalar)	{ x *= scalar; y *= scalar; return *this; }
		XViewPt& operator/=(XViewCoord scalar)	{ x /= scalar; y /= scalar; return *this; }

		void Set(XViewCoord X, XViewCoord Y) { x = X; y = Y; }

		XViewCoord MagnitudeSquared(void) const     { return x*x + y*y; }
		XViewCoord SquaredDistanceFrom(XViewPt otherPoint) const 
		{ 
			XViewCoord magSq = (*this - otherPoint).MagnitudeSquared();
			return (magSq > 0) ? magSq : -magSq;
		}

		XViewCoord Magnitude(void) const; /* { return sqrt(x*x + y*y); } */

		XViewCoord DistanceFrom(XViewPt otherPoint) const
		{ 
			XViewCoord mag = (*this - otherPoint).Magnitude();
			return (mag > 0) ? mag : -mag;
		}

		void Scale(const double f, const XViewPt* pAboutPt/*=NULL*/);
	};
	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------

	



	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------
	//
	// ViewRect
	//
	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------




	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	class ViewRect_ {
	public:
	//protected:
		ViewCoord			top, left, bottom, right;

		friend class ViewRect;
	};
	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------


	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	class ViewRect : public ViewRect_ {
	public:
		ViewRect&	operator=(const ViewRect& r)  { top = r.top; left = r.left; bottom = r.bottom; right = r.right; return *this; }
		ViewRect&	operator=(const ViewRect_& r) { top = r.top; left = r.left; bottom = r.bottom; right = r.right; return *this; }

		ViewRect() { top = left = bottom = right = 0;}
		ViewRect(ViewCoord leftIn, ViewCoord topIn, ViewCoord rightIn, ViewCoord bottomIn) { top = topIn; left = leftIn; bottom = bottomIn; right = rightIn; }
		ViewRect(const ViewPt& pt1, const ViewPt& pt2) {SetRect(pt1, pt2);}

		ViewCoord Top()    const { return top;    }   
		ViewCoord Left()   const { return left;   }  
		ViewCoord Bottom() const { return bottom; } 
		ViewCoord Right()  const { return right;  }

		void SetTop   (ViewCoord topIn)    { top    = topIn;    }  
		void SetLeft  (ViewCoord leftIn)   { left   = leftIn;   }  
		void SetBottom(ViewCoord bottomIn) { bottom = bottomIn; } 
		void SetRight (ViewCoord rightIn)  { right  = rightIn;  }  

		void SetRect(const ViewPt& pt1, const ViewPt& pt2);

		Bool8 operator==(const ViewRect& r) const {	return (top == r.top && left == r.left && bottom == r.bottom && right == r.right); }
		Bool8 operator!=(const ViewRect& r) const { return !(*this == r); }

		inline ViewPt TopLeft()     const { return ViewPt(left, top); }
		inline ViewPt TopRight()	const { return ViewPt(right, top); }
		inline ViewPt BottomLeft()	const { return ViewPt(left, bottom); }
		inline ViewPt BottomRight() const { return ViewPt(right, bottom); }

		ViewCoord	Width() const;
		ViewCoord	Height() const;

		Sint32		WidthL()  const { return (Sint32)right - (Sint32)left; }
		Sint32		HeightL() const { return (Sint32)bottom - (Sint32)top; }

		ViewPt		Center() const;
		
		Bool8 IsEmpty() const { return top >= bottom || left >= right; }  // Note > OR equal for ViewRect. WorldRects are different.
		Bool8 IsNotEmpty() const { return !IsEmpty(); }

		void MakeEmpty() { top = bottom = left = right = 0; }          // Note just 0,0,0,0 for now.
		
		void SetLTRB   (ViewCoord l, ViewCoord t, ViewCoord r, ViewCoord b) { left  = l; top  = t; right  = r; bottom  = b; }
		void AdjustLTRB(ViewCoord l, ViewCoord t, ViewCoord r, ViewCoord b) { left += l; top += t; right += r; bottom += b; }
		
		Bool8 Intersect(const ViewRect& src2, ViewRect& dest) const;
		Boolean Overlaps(const ViewRect& r) const      // True if the two rects share more than a point or a line.
		{ 
			if (this->IsEmpty() || r.IsEmpty())
				return false;
			else
				return (bottom > r.top
		     		&& right > r.left
			 		&& left < r.right 
			 		&& top < r.bottom); 
		}

		void Inset(ViewCoord dx,  ViewCoord dy)	{ left += dx; right -= dx; top += dy; bottom -= dy; }
		void Outset(ViewCoord dx, ViewCoord dy)	{ this->Inset(-dx, -dy); }
		void Offset(ViewCoord dx, ViewCoord dy)	{ left += dx; right += dx; top += dy; bottom += dy; }

		void SafeInset(ViewCoord dx,  ViewCoord dy)
		{
			left	= SafeAdd(left, dx);
			right	= SafeAdd(right, -dx);
			top		= SafeAdd(top, dy);
			bottom	= SafeAdd(bottom, -dy);
		}
		void SafeOutset(ViewCoord dx, ViewCoord dy)	{ this->SafeInset(-dx, -dy); }
		void SafeOffset(ViewCoord dx,  ViewCoord dy)
		{
			left	= SafeAdd(left, dx);
			right	= SafeAdd(right, dx);
			top		= SafeAdd(top, dy);
			bottom	= SafeAdd(bottom, dy);
		}

		void Union(const ViewRect& src2, ViewRect& dest) const
		{
			dest.top = top < src2.top ? top : src2.top; 
			dest.bottom = bottom > src2.bottom ? bottom : src2.bottom; 
			dest.left = left < src2.left ? left : src2.left; 
			dest.right = right > src2.right ? right : src2.right;
		}

		Bool8 PtInRect(const ViewPt& pt) const;

		void ByteSwap();
	};

	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------

	class GSRect32; // forward declaration

	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	class XViewRect {

	public:
		XViewCoord top, left, bottom, right; 

		XViewRect()                  { top = 0;     left = 0;      bottom = 0;        right = 0; }
		XViewRect(XViewCoord leftIn, XViewCoord topIn, XViewCoord rightIn, XViewCoord bottomIn) { top = topIn; left = leftIn; right = rightIn; bottom = bottomIn; }
		XViewRect(const XViewPt& inxvpt1, const XViewPt& inxvpt2) { this->SetRect(inxvpt1, inxvpt2); }
		XViewRect(const ViewRect& v) { top = v.top; left = v.left; bottom = v.bottom; right = v.right; }
		XViewRect(const GSRect32& v);

		XViewCoord Top()    const { return top;    }   
		XViewCoord Left()   const { return left;   }  
		XViewCoord Bottom() const { return bottom; } 
		XViewCoord Right()  const { return right;  }

		void SetRect(const XViewPt& inxvpt1, const XViewPt& inxvpt2);

		Bool8 operator==(const XViewRect& r) const;
		Bool8 operator!=(const XViewRect& r) const { return !(*this == r); }

		XViewRect	operator*(XViewCoord scalar) const	{ return XViewRect(left * scalar, top * scalar, right * scalar, bottom * scalar); }
		XViewRect	operator/(XViewCoord scalar) const	{ return XViewRect(left / scalar, top / scalar, right / scalar, bottom / scalar); }
		XViewRect& operator*=(XViewCoord scalar) { left *= scalar; top *= scalar; right *= scalar; bottom *= scalar; return *this; }
		XViewRect& operator/=(XViewCoord scalar) { left /= scalar; top /= scalar; right /= scalar; bottom /= scalar; return *this; }

		inline XViewPt TopLeft() const		{ return XViewPt(left, top); }
		inline XViewPt TopRight() const		{ return XViewPt(right, top); }
		inline XViewPt BottomLeft() const	{ return XViewPt(left, bottom); }
		inline XViewPt BottomRight() const	{ return XViewPt(right, bottom); }

		XViewCoord	Width() const	{ return right - left; }   
		XViewCoord	Height() const	{ return bottom - top; }   

		XViewPt		Center() const;

		Bool8 IsEmpty() const { return top >= bottom || left >= right; }  // Note > OR equal for XViewRect. WorldRects are different.
		Bool8 IsNotEmpty() const { return !IsEmpty(); }

		void MakeEmpty() { top = bottom = left = right = 0; }

		void SetLTRB(XViewCoord l, XViewCoord t, XViewCoord r, XViewCoord b) { left  = l; top  = t; right  = r; bottom  = b; }
		void AdjustLTRB(XViewCoord l, XViewCoord t, XViewCoord r, XViewCoord b) { left += l; top += t; right += r; bottom += b; }

		Bool8 Intersects(const XViewRect& inxvr) const;
		Bool8 Intersect(const XViewRect& inxvr, XViewRect& outxvrIntersection) const;
		void Intersect(const XViewRect& inxvr);
		XViewRect Intersection(const XViewRect& inxvr) const;
		Boolean Overlaps(const XViewRect& inxvr) const      // True if the two rects share more than a point or a line.
		{ 
			if (this->IsEmpty() || inxvr.IsEmpty())
				return false;
			else
				return (bottom > inxvr.top
		     		&& right > inxvr.left
			 		&& left < inxvr.right 
			 		&& top < inxvr.bottom); 
		}

		void Inset(XViewCoord dx, XViewCoord dy)	{ left += dx; right -= dx; top += dy; bottom -= dy; }
		void Outset(XViewCoord dx, XViewCoord dy)	{ this->Inset(-dx, -dy); }
		void Offset(XViewCoord dx, XViewCoord dy)	{ left += dx; right += dx; top += dy; bottom += dy; }

		void Union(const XViewRect& src2, XViewRect& dest) const
		{
			dest.top = top < src2.top ? top : src2.top; 
			dest.bottom = bottom > src2.bottom ? bottom : src2.bottom; 
			dest.left = left < src2.left ? left : src2.left; 
			dest.right = right > src2.right ? right : src2.right;
		}
        
        Bool8 PtInRect(const XViewPt& queryPoint) const;

		void Scale(const double f, const XViewPt* pAboutPt=NULL);
	};
	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------
	enum EXVRToVRMode { eXVRToVR_Round, eXVRToVR_Expand };

	double XRound(double x); // To be consistent with WorldToView rounding, we do something like Num2Short.

	bool XViewRectToViewRect(const XViewRect& inxvr, ViewRect& outvr, EXVRToVRMode inMode = eXVRToVR_Round);
	bool XViewPtToViewPt(const XViewPt& inxvpt, ViewPt& outvpt);
	bool XViewLengthToViewLength(XViewCoord inxv, ViewCoord& outv, EXVRToVRMode inMode = eXVRToVR_Round);

	// use this when you know the conversion will work, or you accept pinned results
	inline ViewRect XViewRectToViewRect(const XViewRect& inxvr, EXVRToVRMode inMode = eXVRToVR_Round)
	{
		ViewRect outvr;
		XViewRectToViewRect(inxvr, outvr, inMode);
		return outvr;
	}

	// use this when you know the conversion will work, or you accept pinned results
	inline ViewPt XViewPtToViewPt(const XViewPt& inxvpt)
	{
		ViewPt outvpt;
		XViewPtToViewPt(inxvpt, outvpt);
		return outvpt;
	}

	// use this when you know the conversion will work, or you accept pinned results
	inline ViewCoord XViewLengthToViewLength(XViewCoord inxv, EXVRToVRMode inMode = eXVRToVR_Round)
	{
		ViewCoord outv;
		XViewLengthToViewLength(inxv, outv, inMode);
		return outv;
	}

	//--------------------------------------------------------------------
	// I think these get obsoleted. [MAF 10/11/99]
	//
	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------

	//**  ViewPt manipulation functions  **
	inline void SetGSPt(ViewPt &pt, Sint16 x_in, Sint16 y_in) {pt.x = x_in; pt.y = y_in;}
	inline void AddGSPt(ViewPt const &srcPt, ViewPt &dstPt) {dstPt.x += srcPt.x; dstPt.y += srcPt.y;}
	inline void SubGSPt(ViewPt const &srcPt, ViewPt &dstPt) {dstPt.x -= srcPt.x; dstPt.y -= srcPt.y;}
	
	//**  ViewRect manipulation functions  **
	Bool8 SectViewRect(const ViewRect& src1, const ViewRect& src2, ViewRect& dest);
	Bool8 EqualViewRect(const ViewRect& rect1, const ViewRect& rect2);
	void InsetViewRect(ViewRect& rect, Sint16 dx, Sint16 dy);
	Bool8 IsEmptyViewRect(const ViewRect& rect);
	void OffsetViewRect(ViewRect& rect, Sint16 dx, Sint16 dy);
	void UnionViewRect(const ViewRect& src1, const ViewRect& src2, ViewRect& dest);
	void GSPt2ViewRect(const ViewPt& pt1, const ViewPt& pt2, ViewRect& rect);
	Bool8 GSPtInViewRect(const ViewPt& pt, const ViewRect& rect);
	Bool8 GSPtToAngle(const ViewRect& rect, const ViewPt& pt, Sint16 angle);
	void SetViewRect(ViewRect& rect, Sint16 left, Sint16 top, Sint16 right, Sint16 bottom);


	inline ViewCoord Dx(const ViewRect& rc) { return rc.Width(); }
	inline ViewCoord Dy(const ViewRect& rc) { return rc.Height(); }
	
	// WorldSpace and ViewSpace conversion functions are in TDQuickDraw.h.
	//
	// Mac and Win conversion functions are in MCCoordTypes.h:
	// 
	//     ViewRect MacToViewRect(const Rect&     r);
	//     Rect     ViewToMacRect(const ViewRect& r);
	//
	//     RECT     ViewToWinRect(const ViewRect& r);
	//     ViewRect WinToViewRect(const RECT&     r);
	//


	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------
	//
	// PageCoord / PagePt / PageRect
	//
	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------

	typedef double  PageCoord;

	class PagePt;

	//
	//----------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------

	typedef double  PageCoord;

	class PagePt;

	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	class PagePt_ {
	public:
		PageCoord			x;
		PageCoord			y;
	};

	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------



	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	class PagePt : public PagePt_ {
	public:
		PagePt() { x = y = 0;}
		PagePt(PageCoord xIn, PageCoord yIn) { x = xIn; y = yIn; }

		void Set(PageCoord xIn, PageCoord yIn) { x = xIn; y = yIn; }

		bool operator==(const PagePt& pt) const { return ((pt.x == x) && (pt.y == y)); }
		bool operator!=(const PagePt& pt) const { return ((pt.x != x) || (pt.y != y)); }

		PagePt operator/(double scalar)   const	{ return PagePt(x / scalar, y / scalar); }
		PagePt operator*(double scalar)   const	{ return PagePt(x * scalar, y * scalar); }
		PagePt operator+(const PagePt& p) const	{ return PagePt(x + p.x, y + p.y); }
		PagePt operator-(const PagePt& p) const	{ return PagePt(x - p.x, y - p.y); }
		PagePt operator-(void) const			{ return PagePt(-x, -y); }

		void ByteSwap();
	};

	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	class PageRect_ {
	public:
		PageCoord			top;
		PageCoord			left;
		PageCoord			bottom;
		PageCoord			right;
	};
	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	class PageRect : public PageRect_ {
	public:
		PageRect() { top = left = bottom = right = 0;}
		PageRect(PageCoord leftIn, PageCoord topIn, PageCoord rightIn, PageCoord bottomIn) { top = topIn; left = leftIn; right = rightIn; bottom = bottomIn; }

		PageRect&	operator=(const PageRect& r)  { top = r.top; left = r.left; bottom = r.bottom; right = r.right; return *this; }

		const PageCoord Top()    const { return top;    }   
		const PageCoord Left()   const { return left;   } 
		const PageCoord Bottom() const { return bottom; } 
		const PageCoord Right()  const { return right;  }   

		void SetTop   (PageCoord t)    { this->top    = t; }
		void SetLeft  (PageCoord l)    { this->left   = l; }        
		void SetBottom(PageCoord b)    { this->bottom = b; }     
		void SetRight (PageCoord r)    { this->right  = r; }           

		Bool8 operator==(const PageRect& r) const {
				return (top == r.top && left == r.left && bottom == r.bottom && right == r.right);
		}

		Bool8 operator!=(const PageRect& r) const { return !(*this == r); }
		
		inline PagePt TopLeft()     const { return PagePt(left, top); }
		inline PagePt BottomRight() const { return PagePt(right, bottom); }
			
		PageCoord Width()  const { return right - left; }
		PageCoord Height() const { return bottom - top; }
		PagePt    Center() const { return PagePt((left + right) / 2, (bottom + top) / 2); }
		
		Bool8 IsEmpty() const { return top >= bottom || left >= right; }  // Note > OR equal for PageRect. WorldRects are different.
		Bool8 IsNotEmpty() const { return !IsEmpty(); }

		void MakeEmpty() { top = bottom = left = right = 0; }          // Note just 0,0,0,0 for now.
		
		void Set(PageCoord l, PageCoord t, PageCoord r, PageCoord b) { left = l; top = t; right = r; bottom = b; }
		
		Bool8 Intersect(const PageRect& src2, PageRect& dest) const;

		void Inset(PageCoord dx, PageCoord dy)  { left += dx; right -= dx; top += dy; bottom -= dy; }
		void Offset(PageCoord dx, PageCoord dy) { left += dx; right += dx; top += dy; bottom += dy; }
		void Union(const PageRect& src2, PageRect& dest) const { dest.top = top < src2.top ? top : src2.top; 
														dest.bottom = bottom > src2.bottom ? bottom : src2.bottom; 
														dest.left = left < src2.left ? left : src2.left; 
														dest.right = right > src2.right ? right : src2.right; }

	};
	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------

	//----------------------------------------------------------------------------------------


	typedef Sint32 GSCoord32;

	GSCoord32 SafeAdd(GSCoord32 v1, GSCoord32 v2);

	class GSPoint32 {
	public:
		GSCoord32	x;
		GSCoord32	y;
		
		GSPoint32() : x(0), y(0) {}
		GSPoint32(GSCoord32 inx, GSCoord32 iny) : x(inx), y(iny) {}
		GSPoint32(const GSPoint32& gp) : x(gp.x), y(gp.y) {}
		GSPoint32(const ViewPt& vp) : x(vp.x), y(vp.y) {}

		Bool8 operator==(const GSPoint32& r) const { return (x == r.x && y == r.y); }
		Bool8 operator!=(const GSPoint32& r) const { return !(*this == r); }

		GSPoint32 operator+(const GSPoint32& p) const	{ return GSPoint32(x + p.x, y + p.y); }
		GSPoint32 operator-(const GSPoint32& p) const	{ return GSPoint32(x - p.x, y - p.y); }
		
		void Set(GSCoord32 inx, GSCoord32 iny)	{ x = inx; y = iny; }

		void Offset(GSCoord32 dx, GSCoord32 dy) { x += dx; y += dy; }
		void SafeOffset(GSCoord32 dx,  GSCoord32 dy)
		{
			x = SafeAdd(x, dx);
			y = SafeAdd(y, dy);
		}

		Bool8 ScaleRound(const double f, const GSPoint32* pAboutPt=NULL);
		Bool8 ScaleTrunc(const double f, const GSPoint32* pAboutPt=NULL);
	};

	class GSRect32 {
	public:
		GSCoord32	top;
		GSCoord32	left;
		GSCoord32	bottom;
		GSCoord32	right;

		GSRect32() : top(0), left(0), bottom(0), right(0){}
		GSRect32(GSCoord32 l, GSCoord32 t, GSCoord32 r, GSCoord32 b) : top(t), left(l), bottom(b), right(r) {}
		GSRect32(const GSRect32& gr) : top(gr.top), left(gr.left), bottom(gr.bottom), right(gr.right) {}
		GSRect32(const ViewRect& vr) : top(vr.top), left(vr.left), bottom(vr.bottom), right(vr.right) {}

		Bool8 operator==(const GSRect32& r) const {
				return (top == r.top && left == r.left && bottom == r.bottom && right == r.right);
		}
		Bool8 operator!=(const GSRect32& r) const { return !(*this == r); }

		GSCoord32 Top()    const { return top;    }   
		GSCoord32 Left()   const { return left;   }  
		GSCoord32 Bottom() const { return bottom; } 
		GSCoord32 Right()  const { return right;  }

		GSCoord32 Width() const		{ return right - left; }
		GSCoord32 Height() const	{ return bottom - top; }

		void SetTop   (GSCoord32 topIn)    { top    = topIn;    }  
		void SetLeft  (GSCoord32 leftIn)   { left   = leftIn;   }  
		void SetBottom(GSCoord32 bottomIn) { bottom = bottomIn; } 
		void SetRight (GSCoord32 rightIn)  { right  = rightIn;  }  

		void Set(GSCoord32 l, GSCoord32 t, GSCoord32 r, GSCoord32 b) { left = l; top = t; right = r; bottom = b; }

		Bool8 IsEmpty() const { return top >= bottom || left >= right; }  // Note > OR equal for GSRect32. WorldRects are different.
		Bool8 IsNotEmpty() const { return !IsEmpty(); }

		void MakeEmpty() { top = bottom = left = right = 0; }

		Bool8		Intersects(const GSRect32& r) const;
		void		Intersect(const GSRect32& r);
		GSRect32	Intersection(const GSRect32& r) const;

		void Inset(GSCoord32 dx, GSCoord32 dy)  { left += dx; right -= dx; top += dy; bottom -= dy; }
		void Outset(GSCoord32 dx, GSCoord32 dy)	{ this->Inset(-dx, -dy); }
		void Offset(GSCoord32 dx, GSCoord32 dy) { left += dx; right += dx; top += dy; bottom += dy; }

		void SafeInset(GSCoord32 dx,  GSCoord32 dy)
		{
			left	= SafeAdd(left, dx);
			right	= SafeAdd(right, -dx);
			top		= SafeAdd(top, dy);
			bottom	= SafeAdd(bottom, -dy);
		}
		void SafeOutset(GSCoord32 dx, GSCoord32 dy)	{ this->SafeInset(-dx, -dy); }
		void SafeOffset(GSCoord32 dx,  GSCoord32 dy)
		{
			left	= SafeAdd(left, dx);
			right	= SafeAdd(right, dx);
			top		= SafeAdd(top, dy);
			bottom	= SafeAdd(bottom, dy);
		}

		void Union(const GSRect32& src2, GSRect32& dest) const { dest.top = top < src2.top ? top : src2.top; 
														dest.bottom = bottom > src2.bottom ? bottom : src2.bottom; 
														dest.left = left < src2.left ? left : src2.left; 
														dest.right = right > src2.right ? right : src2.right; }


		Bool8 ScaleRound(const double f, const GSPoint32* pAboutPt=NULL);
		Bool8 ScaleTrunc(const double f, const GSPoint32* pAboutPt=NULL);
	};
	
	inline GSCoord32 Dx(const GSRect32& rc) { return rc.Width(); }
	inline GSCoord32 Dy(const GSRect32& rc) { return rc.Height(); }

	ViewRect	GSRect32ToViewRect(const GSRect32& inRect32);
	ViewPt		GSPoint32ToViewPt(const GSPoint32& inPoint32);


	bool XViewRectToGSRect32(const XViewRect& inxvr, GSRect32& outrc32, EXVRToVRMode inMode = eXVRToVR_Round);
	bool XViewPtToGSPoint32(const XViewPt& inxvpt, GSPoint32& outpt32);
	bool XViewLengthToGSCoord32Length(XViewCoord inxv, GSCoord32& outv32, EXVRToVRMode inMode = eXVRToVR_Round);

	// use this when you know the conversion will work, or you accept pinned results
	inline GSRect32 XViewRectToGSRect32(const XViewRect& inxvr, EXVRToVRMode inMode = eXVRToVR_Round)
	{
		GSRect32 outrc32;
		XViewRectToGSRect32(inxvr, outrc32, inMode);
		return outrc32;
	}

	// use this when you know the conversion will work, or you accept pinned results
	inline GSPoint32 XViewPtToGSPoint32(const XViewPt& inxvpt)
	{
		GSPoint32 outpt32;
		XViewPtToGSPoint32(inxvpt, outpt32);
		return outpt32;
	}

	// use this when you know the conversion will work, or you accept pinned results
	inline GSCoord32 XViewLengthToGSCoord32Length(XViewCoord inxv, EXVRToVRMode inMode = eXVRToVR_Round)
	{
		GSCoord32 outv32;
		XViewLengthToGSCoord32Length(inxv, outv32, inMode);
		return outv32;
	}



	typedef Uint16 ColorCoord;

	//
	// Cross platform color
	// Even though the members are 16 bits, usually only 8 bits of color resolution are used. -DLD 2/22/99
	//
	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	struct GSColor {
		ColorCoord	red;
		ColorCoord	green;
		ColorCoord	blue;

		void Set16(ColorCoord r, ColorCoord g, ColorCoord b)			{ red = r; green = g; blue = b; }
		void Get16(ColorCoord& r, ColorCoord& g, ColorCoord& b) const	{ r = red; g = green; b = blue; }
			
		void Set8(Uint8 r, Uint8 g, Uint8 b)				{ red = (((ColorCoord)r)<<8) + r; green	= (((ColorCoord)g)<<8) + g;	blue = (((ColorCoord)b)<<8) + b; }
		void Get8(Uint8& r, Uint8& g, Uint8& b) const		{ r = (Uint8)(red>>8); g = (Uint8)(green>>8); b = (Uint8)(blue>>8); }
		void GetFloat(float& r, float& g, float& b)			{ r = red/255.0f; g = green/255.0f; b = blue/255.0f; }
			
		Bool8 operator==(const GSColor& color) const {
			return (color.red == red && color.green == green && color.blue == blue);
		}
		Bool8 operator!=(const GSColor& color) const {
			return !((*this) == color);
		}

		void AssignFrom(const GSColor& src) {
			red = src.red;
			green = src.green;
			blue = src.blue;
		}
	};

	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------

	typedef struct GSColor GSColor, *PGSColor;
	typedef GSColor GSColorTable[256];

	Bool8 IsGrayscaleColorTable(const GSColor* pColors, Uint16 numColors);
	void SetGrayscaleColorTable(GSColor* pColors, Uint16 inNumColors, bool inbIncreasing=true);

	template<typename T> inline double CalcLuminance(const T inRed, const T inGreen, const T inBlue)
	// Uses formula for luminance Y'601. https://en.wikipedia.org/wiki/HSL_and_HSV
	{ return inRed * 0.299 + inGreen * 0.587 + inBlue * 0.114; }

	//--------------------------------------------------------------------
	// TGSColorV2 begin
	//--------------------------------------------------------------------
	typedef float THueColorComponent;
	const THueColorComponent kUndefinedHueColorComponent	= -1.0;		// For pure grays, Hue will be Undefined.  This is ok.
	const THueColorComponent kMinHueColorComponent			= 0.0;		// Hue >= Min
	const THueColorComponent kMaxHueColorComponent			= 360.0;	// Hue < Max, (note Hue != Max)

	typedef float TUnitColorComponent;
	const TUnitColorComponent kMinUnitColorComponent		= 0.0;
	const TUnitColorComponent kMaxUnitColorComponent		= 1.0;

	typedef float TColorShadeFactor;
	const TColorShadeFactor kMinColorShadeFactor			= -1.0;
	const TColorShadeFactor kMaxColorShadeFactor			= 1.0;
	const TColorShadeFactor kInvalidShadeFactor				= -100;

	typedef float TColorBlendFactor;
	const TColorBlendFactor kMinColorBlendFactor			= 0.0;
	const TColorBlendFactor kMaxColorBlendFactor			= 1.0;
	const TColorBlendFactor kInvalidBlendFactor				= -100;


	//----------------------------------------------------------------------------
	class TGSColorV2
	{
	public:
		enum TColorType {
			eCMYK,
			eRGB,
			eHSV,
			eRGB16,
			eRGB8
		};
		
		TGSColorV2( void )								{ /*k=0 just to initialize all float values*/fCMYK.k = 0; this->SetRGB( 0, 0, 0 ); }
		TGSColorV2(const TGSColorV2& in)				{ *this = in; }

		TGSColorV2(TColorType inType, float c1, float c2, float c3, float c4=0);
		TGSColorV2(TUnitColorComponent c, TUnitColorComponent m, TUnitColorComponent y, TUnitColorComponent k)	{ this->SetCMYK(c,m,y,k); }
		TGSColorV2(TUnitColorComponent r, TUnitColorComponent g, TUnitColorComponent b)							{ this->SetRGB(r,g,b); }
		TGSColorV2(Uint16 r, Uint16 g, Uint16 b)		{ this->SetRGB16(r,g,b); }
		TGSColorV2(Uint8 r, Uint8 g, Uint8 b)			{ this->SetRGB8(r,g,b); }
		TGSColorV2(const GSColor& in)					{ this->SetGSColor(in); }

		TGSColorV2(TColorType inNewType, const TGSColorV2& inColor)	{ this->Set(inNewType, inColor); }
		
		TGSColorV2 &operator = ( const TGSColorV2 &inCopy );
		
		TColorType	GetType() const						{ return fType; }

		void GetCMYK(TUnitColorComponent& c, TUnitColorComponent& m, TUnitColorComponent& y, TUnitColorComponent& k) const;
		void GetHSV(THueColorComponent& h, TUnitColorComponent& s, TUnitColorComponent& v) const;
		void GetLuminance(TUnitColorComponent& outLuma) const; // gray level
		void GetRGB(TUnitColorComponent& r, TUnitColorComponent& g, TUnitColorComponent& b) const;
		void GetRGB16(Uint16& r, Uint16& g, Uint16& b) const;
		void GetRGB8(Uint8& r, Uint8& g, Uint8& b) const;
		void GetGSColor(GSColor& out) const;
		GSColor GetGSColor() const						{ GSColor theColor; this->GetGSColor(theColor); return theColor; }

		void SetCMYK(TUnitColorComponent c, TUnitColorComponent m, TUnitColorComponent y, TUnitColorComponent k);
		void SetHSV(THueColorComponent h, TUnitColorComponent s, TUnitColorComponent v);
		void SetRGB(TUnitColorComponent r, TUnitColorComponent g, TUnitColorComponent b);
		void SetRGB16(Uint16 r, Uint16 g, Uint16 b)		{ fType = eRGB16;	fRGB16.r = r;	fRGB16.g = g;	fRGB16.b = b; }
		void SetRGB8(Uint8 r, Uint8 g, Uint8 b)			{ fType = eRGB8;	fRGB8.r = r;	fRGB8.g = g;	fRGB8.b = b; }
		void SetGSColor(const GSColor& in);
		void Set(TColorType& inNewType, const TGSColorV2& inColor);
		void ConvertTo(TColorType inNewType)			{ if (inNewType != fType)	this->Set(inNewType, *this); }
		
		void BlendAlphaWithColor( OpacityRef inOpacity, TGSColorV2 color );
		
		float Compare(const TGSColorV2& right, TGSColorV2::TColorType inCompareType, float epsilon=0) const;
		bool LessThan(const TGSColorV2& right, TGSColorV2::TColorType inCompareType, float epsilon=0) const;
		bool EqualTo(const TGSColorV2& right, TGSColorV2::TColorType inCompareType, float epsilon=0) const;
		double DistanceSquared(const TGSColorV2& right, TGSColorV2::TColorType inCompareType) const;

		bool operator<(const TGSColorV2& right) const;
		bool operator==(const TGSColorV2& right) const;
		bool operator!=(const TGSColorV2& right) const	{ return !(*this == right); }

		// statics
		static void CMYKToRGBVW26AndEarlier(TUnitColorComponent c, TUnitColorComponent m, TUnitColorComponent y, TUnitColorComponent k,
								TUnitColorComponent& r, TUnitColorComponent& g, TUnitColorComponent& b);
		static void RGBToCMYKVW26AndEarlier(TUnitColorComponent r, TUnitColorComponent g, TUnitColorComponent b,
								TUnitColorComponent& c, TUnitColorComponent& m, TUnitColorComponent& y, TUnitColorComponent& k);
		static void CMYKToRGB(TUnitColorComponent c, TUnitColorComponent m, TUnitColorComponent y, TUnitColorComponent k,
								TUnitColorComponent& r, TUnitColorComponent& g, TUnitColorComponent& b);
		static void RGBToCMYK(TUnitColorComponent r, TUnitColorComponent g, TUnitColorComponent b,
								TUnitColorComponent& c, TUnitColorComponent& m, TUnitColorComponent& y, TUnitColorComponent& k);
		void TranslateCMYK();
		static void HSVToRGB(THueColorComponent h, TUnitColorComponent s, TUnitColorComponent v,
								TUnitColorComponent& r, TUnitColorComponent& g, TUnitColorComponent& b);
		static void RGBToHSV(TUnitColorComponent r, TUnitColorComponent g, TUnitColorComponent b,
								THueColorComponent& h, TUnitColorComponent& s, TUnitColorComponent& v);

		static THueColorComponent	PinHueComponentInRange(THueColorComponent c, Bool8 bAssert = true);
		static TUnitColorComponent	PinUnitComponentInRange(TUnitColorComponent c, Bool8 bAssert = true);
		static Uint16				PinGSColorComponentInRange(Uint16 c, Bool8 bAssert = true);
		static TColorShadeFactor	PinShadeFactorInRange(TColorShadeFactor inShadeFactor);
		static TColorBlendFactor	PinBlendFactorInRange(TColorBlendFactor inBlendFactor);

		static TUnitColorComponent	ShadeRGBComponent(TUnitColorComponent inComp, TColorShadeFactor inShadeFactor);
		static void					ShadeColor(const TGSColorV2& in, TColorShadeFactor inShadeFactor, TGSColorV2& out);
		static void					BlendColors(const TGSColorV2& inC1, const TGSColorV2& inC0, TColorBlendFactor inBlendFactor, TGSColorV2& out);

	protected:
		TColorType	fType;
		
		union {
			struct {
				TUnitColorComponent	c, m, y, k;
			} fCMYK;
			struct {
				THueColorComponent	h;
				TUnitColorComponent s, v;
			} fHSV;
			struct {
				TUnitColorComponent	r, g, b;
			} fRGB;
			struct {
				Uint16	r, g, b;
			} fRGB16;
			struct {
				Uint8	r, g, b;
			} fRGB8;
		};
	};
	//--------------------------------------------------------------------
	// TGSColorV2 end
	//--------------------------------------------------------------------

	// The maximum number of poly vertices allowed in a GSPoly
	const Sint32 kMaxPolyVertices = (SHRT_MAX - sizeof(Sint16) - sizeof(ViewRect))/sizeof(ViewPt); 

	struct GSPoly {
	// Cross platform polygon
		Sint16		polySize;
		ViewRect	polyBBox;
		ViewPt		polyPoints[1];

		Sint16	GetNumPts() const;
		void	CalcBBox();

		static Sint16 CalcSize(Sint16 numPts);
	};
	typedef struct GSPoly GSPoly, *PGSPoly, **PPGSPoly;

	// WorldPoly is the WorldCoord version of GSPoly (See MCCoordTypes.h for WorldPoly)


	//----------------------------------------------------------------------------
	// class ViewRectVerts
	//----------------------------------------------------------------------------
	class ViewRectVerts {
	public:
		ViewRectVerts()
		{
			(this->GetPolyPtr())->polySize = sizeof(GSPoly) + sizeof(ViewPt)*4;  
		}
		ViewRectVerts(const ViewRect& in)
		{
			(this->GetPolyPtr())->polySize = sizeof(GSPoly) + sizeof(ViewPt)*4;  
			this->SetTopLeft()		= in.TopLeft();
			this->SetTopRight()		= in.TopRight();
			this->SetBottomRight()	= in.BottomRight();
			this->SetBottomLeft()	= in.BottomLeft();
		}
		const ViewPt& operator[](ptrdiff_t i) const
		{
			return (this->GetPolyPtr())->polyPoints[i]; // ASSERTN(i>=0, i<=3);
		}

		ViewPt& operator[](ptrdiff_t i)
		{
			return (this->GetPolyPtr())->polyPoints[i]; // ASSERTN(i>=0, i<=3);
		}

		// note that the verts are clockwise in order
		const ViewPt& TopLeft(void)		const	{ return (this->GetPolyPtr())->polyPoints[0]; }
		const ViewPt& TopRight(void)	const	{ return (this->GetPolyPtr())->polyPoints[1]; }
		const ViewPt& BottomRight(void)	const	{ return (this->GetPolyPtr())->polyPoints[2]; }
		const ViewPt& BottomLeft(void)	const	{ return (this->GetPolyPtr())->polyPoints[3]; }

		ViewPt&   SetTopLeft()					{ return (this->GetPolyPtr())->polyPoints[0]; }
		ViewPt&   SetTopRight()					{ return (this->GetPolyPtr())->polyPoints[1]; }
		ViewPt&   SetBottomRight()				{ return (this->GetPolyPtr())->polyPoints[2]; }
		ViewPt&   SetBottomLeft()				{ return (this->GetPolyPtr())->polyPoints[3]; }

		void OutSet(ViewCoord invDistance);
		void GetBoundingBox(ViewRect& outBounds) const;
		Boolean	IsNotRotatedMuch() const;

		const PGSPoly GetPoly() const
		{
			// make sure we close the poly
			(this->GetPolyPtr())->polyPoints[4] = (this->GetPolyPtr())->polyPoints[0];
			
			// Mac needs poly bbox to be set correctly
			this->GetBoundingBox((this->GetPolyPtr())->polyBBox);
			
			return this->GetPolyPtr();
		}

	protected:
		// The poly contains a point for each corner of the rectangle
		// and an extra one to close the poly.
		char buf[sizeof(GSPoly) + sizeof(ViewPt)*4]; 

	//	PGSPoly GetPolyPtr() { return (PGSPoly)&buf; }
		const PGSPoly GetPolyPtr() const { return (PGSPoly)&buf; }
	};

	//----------------------------------------------------------------------------
	// class GSRect32Verts
	//----------------------------------------------------------------------------
	class GSRect32Verts {
	public:
		GSRect32Verts() {}
		GSRect32Verts(const GSRect32& inRect);
		GSRect32Verts(const ViewRectVerts& inVrv);
		GSRect32Verts(const GSRect32Verts& inVrv);

		const GSPoint32& operator[](ptrdiff_t i) const	{ return fVerts[i < 0 ? 0 : (i > 3 ? 3 : i)]; }
		GSPoint32& operator[](ptrdiff_t i)				{ return fVerts[i < 0 ? 0 : (i > 3 ? 3 : i)]; }

		// note that the verts are clockwise in order
		const GSPoint32& TopLeft(void)		const	{ return fVerts[0]; }
		const GSPoint32& TopRight(void)	const		{ return fVerts[1]; }
		const GSPoint32& BottomRight(void)	const	{ return fVerts[2]; }
		const GSPoint32& BottomLeft(void)	const	{ return fVerts[3]; }

		GSPoint32&   SetTopLeft()					{ return fVerts[0]; }
		GSPoint32&   SetTopRight()					{ return fVerts[1]; }
		GSPoint32&   SetBottomRight()				{ return fVerts[2]; }
		GSPoint32&   SetBottomLeft()				{ return fVerts[3]; }

		void	GetBoundingBox(GSRect32& outBounds) const;
		Boolean	IsNotRotatedMuch() const;

		void ScaleRound(const double f, const GSPoint32* pAboutPt=NULL);
		void ScaleTrunc(const double f, const GSPoint32* pAboutPt=NULL);

	protected:
		GSPoint32	fVerts[4];
	};

	ViewRectVerts GSRect32VertsToViewRectVerts(const GSRect32Verts& inVrv32);

	//----------------------------------------------------------------------------
	// class XViewRectVerts
	//----------------------------------------------------------------------------
	class XViewRectVerts {
	public:
		XViewRectVerts() {}
		XViewRectVerts(const XViewRect& inRect);
		XViewRectVerts(const ViewRectVerts& inVrv);
		XViewRectVerts(const GSRect32Verts& inVrv);
		XViewRectVerts(const XViewRectVerts& inVrv);

		const XViewPt& operator[](ptrdiff_t i) const	{ return fVerts[i < 0 ? 0 : (i > 3 ? 3 : i)]; }
		XViewPt& operator[](ptrdiff_t i)				{ return fVerts[i < 0 ? 0 : (i > 3 ? 3 : i)]; }

		// note that the verts are clockwise in order
		const XViewPt& TopLeft(void) const		{ return fVerts[0]; }
		const XViewPt& TopRight(void) const		{ return fVerts[1]; }
		const XViewPt& BottomRight(void) const	{ return fVerts[2]; }
		const XViewPt& BottomLeft(void) const	{ return fVerts[3]; }

		XViewPt&   SetTopLeft()					{ return fVerts[0]; }
		XViewPt&   SetTopRight()				{ return fVerts[1]; }
		XViewPt&   SetBottomRight()				{ return fVerts[2]; }
		XViewPt&   SetBottomLeft()				{ return fVerts[3]; }

		void	GetBoundingBox(XViewRect& outBounds) const;
		Boolean	IsNotRotatedMuch() const;

		void Scale(const double f, const XViewPt* pAboutPt=NULL);

	protected:
		XViewPt	fVerts[4];
	};

	bool XViewRectVertsToGSRect32Verts(const XViewRectVerts& inxvrv, GSRect32Verts& outvrv32);
	bool XViewRectVertsToViewRectVerts(const XViewRectVerts& inxvrv, ViewRectVerts& outvrv);

	enum EXViewLimits { eXVL_None, eXVL_ViewCoord, eXVL_AccurateFloat, eXVL_GSCoord32 };
	XViewPt GetXViewLimitRange(EXViewLimits in);
	bool XViewCoordWithinLimits(XViewCoord inxv, EXViewLimits inLimits);
	bool XViewPtWithinLimits(const XViewPt& inxvpt, EXViewLimits inLimits);
	bool XViewRectWithinLimits(const XViewRect& inxvr, EXViewLimits inLimits);
	bool XViewRectVertsWithinLimits(const XViewRectVerts& inxvrv, EXViewLimits inLimits);

	//
	//	TBitMap - Replacement for QuickDraw BitMap structure
	//
	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	struct TBitMap {
		char *		baseAddr;
		short		rowBytes;
		ViewRect	bounds;
	};
	typedef struct TBitMap TBitMap, *TBitMapPtr;
	
	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------

	//
	//	TRGBColor - Replacement for QuickDraw RGBColor structure
	//
	//--------------------------------------------------------------------
	#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

	struct TRGBColor {
		unsigned short red;
		unsigned short green; 
		unsigned short blue;
	};
	typedef struct TRGBColor TRGBColor;
	
	#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
	//--------------------------------------------------------------------

	//***************  Cross Platform Font Geometry stuff  ***************

	// The number of characters allowed in a font name
	//const Uint8 kMaxFontNameSize = 64;

	// Don't change the ordering.  Mappings rely on this order.
	enum EFontFamily
	{
		kNoFamily,	
		kRoman,		//i.e. Times New Roman
		kSwiss,		//i.e. Arial
		kModern,	//i.e. Courier New
		kScript,	//i.e. Cursive
		kDecor,		//i.e. Old English
		kTech,		//i.e. Symbol
		kBidi		//i.e. Miriam
	};

	// Don't change the order of these, the mappinG in DrwPadWin.cpp
	// relies on this order!
	enum EAlignment
	{
		kAlignTextRight		= 0,
		kAlignTextLeft		= 1,
		kAlignTextCenter	= 2,
		kJustifiedText		= 3
	};

	// The following three enums are used in calls to SetFontStyle
	// Don't change the ordering!!!!!
	enum EBold
	{
		kBoldOff			= 0,
		kBoldOn				= 1,
		kBoldDontCare		= 2
	};

	enum EItalic
	{
		kItalicOff			= 0,
		kItalicOn			= 1,
		kItalicDontCare		= 2
	};

	enum EUnderline
	{
		kUnderlineOff		= 0,
		kUnderlineOn		= 1,
		kUnderlineDontCare	= 2
	};

	// Mac only. Windows ignores.
	enum EOutline
	{
		kOutlineOff			= 0,
		kOutlineOn			= 1,
		kOutlineDontCare	= 2
	};

	// Mac only. Windows ignores.
	enum EShadow					
	{
		kShadowOff			= 0,
		kShadowOn			= 1,
		kShadowDontCare		= 2
	};

	// Mac only, text from other apps. Windows ignores.
	enum ECondense		
	{
		kCondenseOff		= 0,
		kCondenseOn			= 1,
		kCondenseDontCare	= 2
	};

	// Mac only, text from other apps. Windows ignores.
	enum EExtend
	{
		kExtendOff			= 0,
		kExtendOn			= 1,
		kExtendDontCare		= 2
	};

	//The following type is used to specify the rotation angle of any
	//integral rotation (90, 180, 270), only used for non true type text.
	enum ETextTransform {
		k90DegreesClockWise,
		k180DegreesClockWise,
		k270DegreesClockWise,
		kXAxisMirror
	};

	struct DPFont {
	// Cross platform font structure
        TXString	nameStr;            // Null terminated
		EFontFamily	family;				// This is not the same as the Mac "family" of GetFNum().
		Uint32		ptSize; 
		unsigned	italic:		1;
		unsigned	bold:		1;
		unsigned	underline:	1;
		unsigned	outline:	1;		// Mac only.
		unsigned	shadow:		1;		// Mac only.
		unsigned	condense:	1;		// Mac only, text pasted from other apps.
		unsigned	extend:		1;		// Mac only, text pasted from other apps.
		unsigned	_pad:		1;

		inline DPFont();
		~DPFont() {}; 

		inline friend bool operator==(const DPFont& lhs, const DPFont& rhs);
		inline friend bool operator!=(const DPFont& lhs, const DPFont& rhs);
	};
	typedef struct DPFont DPFont, *PDPFont;

	inline DPFont::DPFont()
	{
		nameStr		= "Arial";
		family		= kSwiss;
		ptSize		= 9;

		italic		= 0;
		bold		= 0;
		underline	= 0;
		outline		= 0;
		shadow		= 0;
		condense	= 0;
		extend		= 0;
		_pad		= 0;
	}

	inline bool operator==(const DPFont& font1, const DPFont& font2)
	{
		return (font1.nameStr.Compare(font2.nameStr) == 0
			&& font1.family		== font2.family
			&& font1.ptSize		== font2.ptSize
			&& font1.italic		== font2.italic
			&& font1.bold		== font2.bold
			&& font1.underline	== font2.underline
			&& font1.outline	== font2.outline
			&& font1.shadow		== font2.shadow
			&& font1.condense	== font2.condense
			&& font1.extend		== font2.extend);
	}

	inline bool operator!=(const DPFont& lhs, const DPFont& rhs)
	{
		return !(lhs == rhs);
	}

	struct DPFontMetrics {
	// Cross platform structure for font metrics
		Sint32	ascent;
		Sint32	descent;
		Sint32	maxWidth;
		Sint32	leading;
		//The following is only for windows.  RWM
		Bool8	vectorFont;
		Sint32	charSet; //This is the character set as defined by windows
	};


	typedef Uint32 GSPolyRef;
			

#endif //__cplusplus  // ??
