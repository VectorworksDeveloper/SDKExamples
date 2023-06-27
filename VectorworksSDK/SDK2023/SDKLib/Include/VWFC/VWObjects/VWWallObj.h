//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		// --------------------------------------------------------------------------------------------------
		// wall Component definition structure
		struct SWallComponentInfo {
			InternalName	componentName;
			WorldCoord				width;
			Sint32					componentClass;

			// fill
			CBBoolean				fillUseClass;
			Sint32					fillPat;
			CRGBColor				fillColorFore;
			CRGBColor				fillColorBack;

			// left line
			CBBoolean				penLeftUseClass;
			CBUnsignedByte			penLeftWeight;
			InternalIndex			penLeftStyle;
			CRGBColor				penLeftColorFore;
			CRGBColor				penLeftColorBack;

			// right line
			CBBoolean				penRightUseClass;
			CBUnsignedByte			penRightWeight;
			InternalIndex			penRightStyle;
			CRGBColor				penRightColorFore;
			CRGBColor				penRightColorBack;
		};

		// --------------------------------------------------------------------------------------------------
		// symbol break
		struct SWallSymbolBreak {
			size_t				index;
			double				offset;
			SymbolBreakType		symBreak;
		};

		// --------------------------------------------------------------------------------------------------
		// half break
		struct SWallHalfBreak {
			size_t				index;
			double				offset;
			HalfBreakType		halfBreak;
		};

		// --------------------------------------------------------------------------------------------------
		// cap break
		struct SWallCapBreak {
			size_t				index;
			double				offset;
			CapBreakType		capBreak;
		};

		// --------------------------------------------------------------------------------------------------
		// peak break
		struct SWallPeakBreak {
			size_t				index;
			double				offset;
			PeakBreakType		peakBreak;
		};

		// --------------------------------------------------------------------------------------------------
		typedef std::vector<SWallSymbolBreak>		TWallSymbolBreaksArray;
		typedef std::vector<SWallHalfBreak>			TWallHalfBreaksArray;
		typedef std::vector<SWallCapBreak>			TWallCapBreaksArray;
		typedef std::vector<SWallPeakBreak>			TWallPeakBreaksArray;

		// --------------------------------------------------------------------------------------------------
		// interface for wall break listeners
		// use with VWWall::EnumerateWallBreaks(IWallBreakListener*)
		class IWallBreakListener {
		public:
							IWallBreakListener()								{}
			virtual			~IWallBreakListener()								{}
			virtual void	NotifySymbolBreak(const SWallSymbolBreak& )			{}
			virtual void	NotifyHalfBreak(const SWallHalfBreak& )				{}
			virtual void	NotifyCapBreak(const SWallCapBreak& )				{}
			virtual void	NotifyPeakBreak(const SWallPeakBreak& )				{}
		};

		// --------------------------------------------------------------------------------------------------
		class VWWallObj : public VWObject
		{
		public:
								VWWallObj(const VWPoint2D& startPt, const VWPoint2D& endPt, double thickness=0);
								VWWallObj(const VWPoint2D& startPt, const VWPoint2D& ptOnArc, const VWPoint2D& endPt, double thickness=0);
								VWWallObj(const VWLine2D& line, double thickness=0);
								VWWallObj(const VWArc2D& arc, double thickness=0);
								VWWallObj(MCObjectHandle h);
								VWWallObj(const VWWallObj& src);
			virtual				~VWWallObj();

			VWWallObj&			operator=(const VWWallObj& src);

		public:
			VWPoint2D			GetStartPoint() const;
			VWPoint2D			GetEndPoint() const;
			void				GetPoints(VWPoint2D& startPt, VWPoint2D& endPt) const;
			void				SetPoints(const VWPoint2D& startPt, const VWPoint2D& endPt);
			bool				IsRound() const;
			VWArc2D				GetRoundWall(bool negativeSweepForCWWall = false) const;
			VWLine2D			GetWall() const;
			bool				IsRoundCCW() const;

			// get composite polygons of the wall. also the polygons of the built-in objects.
			TSTLPolygons2DArray	GetWall2DPolygons_() const;

			// Get a polygon representing the shape of the wall in elevation view (including peaks)
			// only for straight walls, otherwise returns false
			bool                GetPolyFromWallElevation( VWPolygon2D& polyOut, bool removeCaps = false );

			// XXX Bobi: causes memory leaks. Should be fixed!!! Use previous function instead 
			// Creates polygon object that is a footprint of the wall. Delete object after using!
			MCObjectHandle		GetWallFootPrint() const;

			// get exact wall footprint - without removing breaks, no object(s) created/modified
			// NB: Straight walls only
			void				GetWallFootPrintEx(VWPolygon2D& footPoly) const;

			// get wall's underlying 2D path polygon.
			// a line for a straight wall and a polygon (polygonized arc) for a round wall.
			void				GetWall2DPath(VWPolygon2D& pathPoly) const;

			// Switch the left and right side of a wall by reversing the direction of the wall.
			// This is an interface to the button with the same name on the Object Info palette.
			void				ReverseSides();

			// Gets/Sets the heights of the start and end of the specified wall.
			// The distances are measured from the ground plane on the layer in which the wall exists.
			void				GetHeights(double& startHeightTop, double& startHeightBottom, double& endHeightTop, double& endHeightBottom) const;
			void				SetHeights(double startHeightTop, double startHeightBottom, double endHeightTop, double endHeightBottom);
			double				GetStartHeightTop() const;
			double				GetStartHeightBottom() const;

			// The width of the wall.
			double				GetWidth() const;
			void				SetWidth(double width);

			// Available in VW Architect only. Moves the wall perpendiclar to its definition line by the specified offset,
			// and maintains all wall connections Offsets to the left hand side of the wall are positive, and to the right hand side are negative.
			void				MoveByOffset(double& offset);

			// COMPONENTS
			size_t				GetComponentCount() const;
			SWallComponentInfo	GetComponentInfo(size_t index) const;
			void				SetComponentInfo(size_t index, const SWallComponentInfo& info);
			bool				InsertNewComponent(size_t beforeIndex, const SWallComponentInfo& info);
			bool				DeleteComponent(size_t index);

			// BREAKS
			void				EnumerateBreaks(IWallBreakListener* pBreakListener) const;
			void				EnumerateBreaks(TWallSymbolBreaksArray& outArrSymbolBreaks) const;
			void				EnumerateBreaks(TWallHalfBreaksArray& outArrHalfBreaks) const;
			void				EnumerateBreaks(TWallCapBreaksArray& outArrCapBreaks) const;
			void				EnumerateBreaks(TWallPeakBreaksArray& outArrPeakBreaks) const;
			size_t				AddBreak(const SWallSymbolBreak& brk);
			size_t				AddBreak(const SWallHalfBreak& brk);
			size_t				AddBreak(const SWallCapBreak& brk);
			size_t				AddBreak(const SWallPeakBreak& brk);
			void				SetBreak(const SWallSymbolBreak& brk);
			void				SetBreak(const SWallHalfBreak& brk);
			void				SetBreak(const SWallCapBreak& brk);
			void				SetBreak(const SWallPeakBreak& brk);
			void				DeleteBreak(size_t index);

			bool				FindBreak(MCObjectHandle hSymbol, SWallSymbolBreak& brk);

			// SEND TO SURFACE.
			// Having an underlying wall 3D path, send the wall bottom (or top) to this 3D path (using wall breaks).
			// The projection of the 3D path in 2D has to coincide with the wall's 2D path (validation).
			// Whole wall is risen with the projection of bottom (or top) wall start point to the 3D path.
			void				SendBotTo3DPath(const VWPolygon3D& path3D, bool bUpdateOveallHeight = true);
			void				SendTopTo3DPath(const VWPolygon3D& path3D);

			// Checks if a 3D polygon is a valid wall's 3D path (its projection coincides with the wall's 2D path).
			bool				IsValidWall3DPath(const VWPolygon3D& path3D, double dEpsilon) const;
			// Tries to fix an invalid 3D wall path.
			bool				FixWall3DPath(VWPolygon3D& path3D, double dEpsilon) const;

		// tool
		public:
			// Return true if the specified object handle is wall
			static bool			IsWallObject(MCObjectHandle hObj);
			static bool			IsRoundWallObject(MCObjectHandle hObj);

		private:
			static Boolean		GetAllBreaksCallback(MCObjectHandle, Sint32 index, double off, Sint32 breakType, void* breakData, CallBackPtr , void* env);
			void				GetWall2DPolygons(const VWTransformMatrix& theMat, MCObjectHandle hGroup, TSTLPolygons2DArray& polygonArr) const;

		private:
			// Check if proposed bottom peak is correct.
			void				IsCorrectBotPeak(const SWallPeakBreak& botPeak, const TWallPeakBreaksArray& peaksArr,
												 double minOffset, double maxOffset,
												 bool& outBadOffset, bool& outBadElev, double& outMaxElev) const;
			// Check if proposed top peak is correct.
			void				IsCorrectTopPeak(const SWallPeakBreak& topPeak, const TWallPeakBreaksArray& peaksArr,
												 double minOffset, double maxOffset,
												 bool& outBadOffset, bool& outBadElev, double& outMinElev) const;
		};
	}
}