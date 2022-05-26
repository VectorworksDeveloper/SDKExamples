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
		using namespace VectorWorks::Math;

		// ------------------------------------------------------------------------------------
		// polygonization default (recommended) values.
		const short			kPolygonize_MaxRecursLevel		= 8;
		const double		kPolygonize_ArcResolution		= 0.5;		// 0.5 degrees.
		const size_t		kPolygonize_MaxIterCount		= 5;
		const double		kPolygonize_IntersEpsilon		= 0.0001;

		// ------------------------------------------------------------------------------------
		class VWPolygon2D;

		// array of polygon defintion
		typedef				std::vector<VWPolygon2D>									TSTLPolygons2DArray;
		typedef				std::vector<VWPolygon2D, std::vwallocator<VWPolygon2D> >	TSTLPolygons2DVWArray;

		// ------------------------------------------------------------------------------------
		class VWPolygon2D
		{
		public:
							VWPolygon2D();
							VWPolygon2D(std::initializer_list<VWPoint2D> src);
							VWPolygon2D(const TSTLPoints2DArray& src);
							VWPolygon2D(const TSTLPoints2DVWArray& src);
							VWPolygon2D(IPolyDefPtr pPolygonDef);
							VWPolygon2D(const VWPolygon2D& src);
			virtual			~VWPolygon2D();

			bool			operator==(const VWPolygon2D& poly) const;
			bool			operator!=(const VWPolygon2D& poly) const;

			VWPolygon2D&	operator=(const TSTLPoints2DArray& src);
			VWPolygon2D&	operator=(const TSTLPoints2DVWArray& src);
			VWPolygon2D&	operator=(const VWPolygon2D& src);
			VWPolygon2D&	operator=(IPolyDefPtr pPolygonDef);

		// operations
		public:
			// setting polygon
			void			SetPolygon(const TSTLPoints2DArray& src);
			void			SetPolygon(const TSTLPoints2DVWArray& src);
			void			SetPolygon(IPolyDefPtr pPolygonDef);
			void			GetPolygon(TSTLPoints2DArray& out) const;
			void			GetPolygon(TSTLPoints2DVWArray& out) const;
			void			GetPolygon(IPolyDefPtr& pPolygonDef) const;

			// vertex operations
			void			ClearVertices();
			void			ClearVertex(size_t at);
			void			PopBack();
			void			AddVertex(double x, double y, EVertexType type=eVertexType_Corner, double dArcRadius=0);
			void			AddVertex(const VWPoint2D& pt, EVertexType type=eVertexType_Corner, double dArcRadius=0);
			void			AddVertex(const VWPolygon2D& poly);
			void			InsertVertex(size_t at, double x, double y, EVertexType type=eVertexType_Corner, double dArcRadius=0);
			void			InsertVertex(size_t at, const VWPoint2D& pt, EVertexType type=eVertexType_Corner, double dArcRadius=0);
			void			InsertVertex(size_t at, const VWPolygon2D& poly);

			size_t			GetVertexCount() const;
			bool			IsEmpty() const;

			VWPoint2D&		operator[](size_t at);
			const VWPoint2D& operator[](size_t at) const;

			VWPoint2D&		Back();
			const VWPoint2D& Back() const;

			VWPoint2D&		GetVertexAt(size_t at, bool bLoopVerts=false);
			const VWPoint2D& GetVertexAt(size_t at, bool bLoopVerts=false) const;
			EVertexType		GetVertexType(size_t at) const;
			void			SetVertexType(size_t at, EVertexType type);
			double			GetArcVertexRadius(size_t at) const;
			void			SetArcVertexRadius(size_t at, double dRadius);
			bool			GetVertexVisible(size_t at) const;
			void			SetVertexVisible(size_t at, bool bVisible);
			// return a line from (at, at+1) vertex (at the end the line is (len-1, 0)
			VWLine2D		GetLineAt(size_t at) const;

			// checks whether the vertex is collinear in the polygon context (i.e. is collinear with respect to its neighboring vertices).
			bool			IsVertexCollinear(size_t at, double epsCollinear = VWPoint2D::sEpsilonCollinear) const;

			// checks if the polygon has at least one non-corner vertex.
			bool			HasNonCornerVertices() const;

			// modify closed flag
			void			SetClosed(bool isClosed);
			bool			IsClosed() const;
			void			SetAllVertexVisible(bool bVisible);

			// correctly opens an polyline.
			// the challenging case is when first or last poly vertex is non-corner.
			// in this case a part of the resulting open polyline will polygonized but the shape will be preserved.
			void			OpenPolyline();
			
			// get bounding box of this polygon
			void			GetPolygonBounds(double& outMinX, double& outMaxX, double& outMinY, double& outMaxY) const;
			VWRectangle2D	GetPolygonBounds() const;
			VWPoint2D		GetPolygonBoundsCenter() const;
			// get the bouding box which is parallel to given line
			// the result polygon contains 4 vertices of the bounding box
			void			GetPolygonBounds(const VWLine2D& line, VWPolygon2D& outBounds) const;
			void			GetPolygonBounds(const VWLine2D& line, VWRectangle2D& outBounds) const;

			// this is a must function to call after using the non-const GetVertexAt as it will change vertices wihtout updating the bounding box
			void			RecalculateBoundingBox();

			// gets the bounding box which is parallel to the given direction (a similar approach).
			// the result is 4 vertices (UL, UR, LL, LR) of the bounding box.
			// 'doPolygonize' controls whether the poly to be polygonized or not.
			void			GetPolygonBounds(const VWPoint2D& vDirection, VWPoint2D& vUL, VWPoint2D& vUR, VWPoint2D& vLL, VWPoint2D& vLR, bool doPolygonize = true) const;

			// reverse the order of the points (if CW to CCW or CCW to CW)
			void			ReversePoints(const bool& kbDoFullReversion = false);

			// determine if the polygon is Clock Wise oriented
			bool			IsClockWise() const;

			// return true if the passed polygon has more than 3 different vertices
			bool			IsValidPolygon(double dEpsilon) const;

			// removed all same points in the polygon
			void			CleanUpPolygon(double dEpsilon);

			// This function works as follows depending on 'doClosenessCheck':
			// ( doClosenessCheck == false )	- clean up all polygon vertices which are collinear with their neighbors.
			// ( doClosenessCheck == true  )	- clean up all polygon vertices which are collinear with their neighbors and are too close to their neighbors.
			// Note: works on polygon with only corner vertices.
			void			CleanUp_FeaturePreserving(bool doClosenessCheck, double epsCollinear, double epsCloseness);

			// This function removes polygon "jags" (such "jags" can be result from cutting, clipping, offsetting, etc.).
			// It also removes all polygon vertices which are collinear with their neighbors.
			// 'maxJagAngle'	- a threshold for recognizing of a "jag"		(Note: this must be an acute angle !).
			// Note: works on polygon with corner vertices only.
			void			CleanUp_RemoveJags(double maxJagAngle, double epsCollinear, double epsCloseness);

			// check polygon for self intersections. return true is so.
			// 'doConsiderTouching' tells if touching will be considered as intersection.
			bool			IsSelfIntersecting(bool doConsiderTouching = true) const;

			// check polygon for self intersections. return true is so.
			// in 'outArrIntersPts' returns all intersection points.
			// 'doConsiderTouching' tells if touching will be considered as intersection.
			bool			IsSelfIntersecting(TSTLPoints2DArray& outArrIntersPts, bool doConsiderTouching = true) const;

			// checks if there are arc vertices with degenerate (zero) radii and recalculates them.
			void			RecalcDegenerateArcVerticesRadii();

			// provided the input polygon has only arc and corner vertices, returns the polyginization of the segment with given index.
			bool			GetSegment(size_t segIndex, VWLine2D& outSegLine, VWArc2D& outSegArc, bool& outIsArc, bool& outIsLine, bool recursion = true) const;

		// mathematics
		public:
			// join this polygon to the given polygon only if both polygons are not closed and have touching endpoints (within epsilon).
			bool			AddAdjoiningPolygon(const VWPolygon2D& adjoiningPoly, double epsilon, bool checkTypes = false);

			// find indices of the first 3 'apposite' polygon points (not too close and not collinear).
			bool			GetAppositePtIndices(size_t& ptIndex0, size_t& ptIndex1, size_t& ptIndex2) const;
			// find the first 3 'apposite' polygon points (not too close and not collinear).
			bool			GetThreeAppositePoints(VWPoint2D& pt0, VWPoint2D& pt1, VWPoint2D& pt2) const;

			// find indices of next two 'apposite' polygon points (not too close and not collinear).
			bool			GetNextAppositePtIndices(size_t ptIndex, size_t& outPtIndex0, size_t& outPtIndex1) const;
			// find next two 'apposite' polygon points (not too close and not collinear).
			bool			GetNextAppositePoints(size_t ptIndex, VWPoint2D& outPt0, VWPoint2D& outPt1) const;
			// find indices of previous two 'apposite' polygon points (not too close and not collinear).
			bool			GetPrevAppositePtIndices(size_t ptIndex, size_t& outPtIndex0, size_t& outPtIndex1) const;
			// find previous two 'apposite' polygon points (not too close and not collinear).
			bool			GetPrevAppositePoints(size_t ptIndex, VWPoint2D& outPt0, VWPoint2D& outPt1) const;

			// find index of next 'apposite' polygon point (not too close).
			bool			GetNextAppositePtIndex(size_t inPtIndex, size_t& outNextPtIndex, double dEpsilon) const;
			// find next 'apposite' polygon point (not too close).
			bool			GetNextAppositePt(size_t inPtIndex, VWPoint2D& outNextPt, double dEpsilon) const;
			// find index of previous 'apposite' polygon point (not too close).
			bool			GetPrevAppositePtIndex(size_t inPtIndex, size_t& outPrevPtIndex, double dEpsilon) const;
			// find previous 'apposite' polygon point (not too close).
			bool			GetPrevAppositePt(size_t inPtIndex, VWPoint2D& outPrevPt, double dEpsilon) const;

			// transform the polygon with specified matrix
			void			Transform(const VWTransformMatrix& mat);
			// move the polygon by the given values
			void			MovePolygon(double cx, double cy);
			// rotate the polygon by the center of the bounding box
			void			Rotate(double degAngle);
			// rotate by specified center
			void			Rotate(const VWPoint2D& pt, double degAngle);

			// calculate the area of the polygon
			// positive if polygon is CCW -- negative if CW
			double			GetArea() const;
			// calculate the perimeter of the polygon (sum of distances between the vertices)
			double			GetPerimeter() const;
			// calculate the length of the curve formed by the polyline
			// Does not include visibility or closed state!
			double			GetLength() const;
			// calculate the length of the curve formed by the polyline up to the specified point
			// if the point is not on the poly 
			// Does not include visibility or closed state!
			double			GetLength(const VWPoint2D& pt, double dEpsilon) const;
			double			GetLength(size_t fromVert, size_t toVert) const;
			
			// returns -1 if not found
			Sint32			GetIndexOf( const VWPoint2D& pt ) const;
			// result is a point along the poly on the specified offset
			bool			GetPtOnPoly(double offset, VWPoint2D& outPt) const;
			bool			GetPtOnPoly(double offset, VWPoint2D& outPt, size_t& outOnSegIndex) const;
			bool			GetPtOnPoly(double offset, VWPoint2D& outPt, VWPoint2D& outNormal, size_t* outOnSegIndex=nullptr) const;

			// calculates point along the polygon at given offset starting from given vertex index.
			// returns the index of the segment where calculated point lies. note: works on polygonized data only (corner vertices only).
			bool			GetPtOnPolyOffsetFrom(size_t vertInx, double offset, VWPoint2D& outPt, size_t& outSegInx) const;
			bool			GetPtOnPolyOffsetFrom(size_t vertInx, double offset, VWPoint2D& outPt,
												  size_t& outSegInx, double& outOnSegOff, double& outSegLen) const;

			// finds the closest point on poly of the given point.
			VWPoint2D		GetClosestPtOnPoly(const VWPoint2D& pt, double& outDist, Sint32& outOnSegIndex) const;
			bool			GetClosestPtOnPolygon(const VWPoint2D& pt, double& outSqrDist, Sint32& outOnSegIndex, VWPoint2D& outProjPt) const;
			// returns the index of the closest poly vertex and the squared distance to it.
			size_t			GetClosestPolyVertex(const VWPoint2D& pt, double& outSqrDist) const;
			// finds the closest projection point on the polygon of the given point (if exists). Note: works on polygon with only corner vertices.
			// returns closest projection point, squared distance to the projection point and index of the segment where the projection point lies.
			bool			GetClosestProjPtOnPoly_Fast(const VWPoint2D& pt, double& outSqrDist, Sint32& outOnSegIndex, VWPoint2D& outProjPt) const;
			bool			GetClosestProjPtOnPoly(const VWPoint2D& pt, double& outSqrDist, Sint32& outOnSegIndex, VWPoint2D& outProjPt) const;
			// finds the projection point on the polygon of the given point which is closest to the check point. Note: works on polygon with only corner vertices.
			// returns projection point, squared distance to the check point and index of the segment where the projection point lies.
			bool			GetProjPtOnPolyClosestTo(const VWPoint2D& inPt, const VWPoint2D& inCheckPt, double& outSqrDist, Sint32& outOnSegIndex, VWPoint2D& outProjPt) const;

			// checks if point lies on the polygon part (specified by 'from' and 'to' vertex indices).
			// returns: segment index on which the point lies and the offset of the point along the polygon part (from the 'from' vertex).
			// note: works on polygonized data only (corner vertices only).
			bool			IsPtOnPolygonPart(const VWPoint2D& pt, size_t fromVertInx, size_t toVertInx, double epsilon,
											  size_t& outOnSegInx, double& outPtOffset) const;

			// calculates an offset ring poly ouside or inside of this poly.
			void			GetOffsetRingPoly(double offset, bool doOutsideOffset, VWPolygon2D& offsetRingPoly) const;

			void			GetPolygonized(VWPolygon2D& outPolygon, double segmentationLength, bool areStraightForPolygonizing) const;

			// The last vertex may not be part of the result.
			void			GetSegmentedPoly(VWPolygon2D& outPolygon, double segmentationLength) const;

			// given a polygon (corner vertices only), segments it (subdivides it) into segments of 'segmentation length' by introducing ...
			// ... new vertices while preserving the original ones (thus, there might be produced shorter segments as well).
			// note: shape of the original polygon will be fully preserved.
			void			GetSegmentedPolygon(VWPolygon2D& outPolygon, double segmentationLength) const;

			// get polygonization:
			// has parameters to control the density of the resulting polygon. recommended to use defaults !
			// if 'interpolate' is true, then bezier and cubic segments will be interpolated by adding cubic vertices, ...
			// ... so result will be interpolation poly with only corner and cubic vertices.
			void			GetPolygonized(	VWPolygon2D& outPolygon,
											bool	interpolate		= false,
											short	splineRecusLevel= kPolygonize_MaxRecursLevel,
											double	arcDegRes		= kPolygonize_ArcResolution,
											size_t	iterationCount	= kPolygonize_MaxIterCount,
											std::function<void(size_t inpuIndex, size_t outputIndexStart, size_t outputIndexEnd)> callbackAddSegment = nullptr,
											short	arcRecursLevel	= kPolygonize_MaxRecursLevel) const;

			// check if it is an equalish polygon.
			bool			EqualishTo(const VWPolygon2D& poly, bool doReverseCheck = false) const;

			// is specified point on the edge of the specified polygon
			bool			IsPtOnPoly2D(double ptX, double ptY, double dEpsilon) const;
			bool			IsPtOnPoly2D(const VWPoint2D& pt, double dEpsilon) const;
			bool			IsPtOnPoly2D_Fast(const VWPoint2D& inPt, Sint32& outOnSegIndex, double epsilon) const;
			bool			IsPtOnPolyStraightSegment(const VWPoint2D& pt, size_t& outOnStraightSegIndex, double epsilon) const;
			// fast check if point is near (within tolerance) to the polygon.
			bool			IsPtNearPoly2D(const VWPoint2D& inPt, Sint32& outOnSegIndex, VWPoint2D& outClosestPtOnPoly, double tolerance) const;
			// fast check if point is within or near (within tolerance) to the polygon. Note: works on polygon with only corner vertices.
			bool			IsPtWithinOrNearPoly2D(const VWPoint2D& inPt, bool& outNearPoly, bool& outWithinPoly, Sint32& outOnSegIndex, VWPoint2D& outClosestPtOnPoly, double tolerance) const;
			bool			IsPtWithinOrNearPoly2D(const VWPoint2D& inPt, Sint32& outOnSegIndex, VWPoint2D& outClosestPtOnPoly, double tolerance) const;
			// check if point is within the polygon. Note: no epsilon/tolerance is used here.
			bool			IsPtWithinPoly2D(const VWPoint2D& inPt) const;

			// determines if a point is in the area of a given polygon (the 2D projection)
			bool			IsPtInPoly2D(double ptX, double ptY, double dEpsilon) const;
			bool			IsPtInPoly2D(const VWPoint2D& pt, double dEpsilon) const;
			bool			IsPtInPoly2D_Fast(double ptX, double ptY, double dEpsilon) const;

			// combined operations
			bool			IsPtInOrOnPoly2D(double ptX, double ptY, double dEpsilon) const;
			bool			IsPtInOrOnPoly2D(const VWPoint2D& pt, double dEpsilon) const;

			// determines if a points is inside and if it is on the poly
			void			IsPtOnPoly2D(double ptX, double ptY, bool& outOnPoly, bool& outInPoly, double dEpsilon) const;
			void			IsPtOnPoly2D(const VWPoint2D& pt, bool& outOnPoly, bool& outInPoly, double dEpsilon) const;

			// return true if the specified line intersects the poly
			bool			IsIntersecting(const VWLine2D& line, double dEpsilon, VWPoint2D* /*out*/ pInsertPt=NULL ) const;
			bool			IsIntersecting(const VWLine2D& line, double dEpsilon, TSTLPoints2DArray& outArrIntersectPts ) const;
			bool			IsIntersecting(const VWLine2D& line, double epsilon, TSTLPoints2DArray& outIntersPts, TSizeTArray& outIntersSegs) const;
			bool			IsIntersecting(const VWPoint2D& a, const VWPoint2D& b, double dEpsilon, VWPoint2D* /*out*/ pInsertPt=NULL ) const;
			bool			IsIntersecting(const VWPoint2D& a, const VWPoint2D& b, double dEpsilon, TSTLPoints2DArray& outArrIntersectPts ) const;

			// return true if the specified line intersects the poly.
			// NOTE: The function returns intersection lines, not points.
			// 1. If start and end points of the line are equal, this line represent one intersection point.
			// 2. If start and end points of the line are NOT equal, this line overlaps some edge of the poly.
			bool			IsIntersecting(const VWLine2D& line, double epsilon, TSTLLines2DArray& outIntersectLines ) const;

			// checks whether the line segment (specified by its ending points 'lnPt0' and 'lnPt1') intersects the polygon.
			// note 1: it doesn't calculate the intersection point (for faster checking).
			// note 2: requires polygonized poly (corner vertices only).
			bool			IsIntersectingLine(const VWPoint2D& lnPt0, const VWPoint2D& lnPt1, double epsilon) const;

			bool			IsRayIntersecting(const VWLine2D& line, double dEpsilon, TSTLPoints2DArray& outArrIntersectPts ) const;

			// return true if the given polygon and this polygon intersects each other (including touching)
			// intersect 'true' means that they have intersection points or same points
			// 'outHaveFullyOutsideVerts' true when the specified 'poly' have fully outside vertices from this poly
			bool			IsIntersecting(const VWPolygon2D& poly, double dEpsilon) const;

			// returns 'true' if the given polygon and this polygon intersect each other (including touching).
			// this means that they have intersection points or same points.
			// in 'outArrIntersPts' returns all intersection points.
			// NOTE: this function will be slower as it will search for all intersection points.
			bool			IsIntersecting(const VWPolygon2D& poly, double epsilon, TSTLPoints2DArray& outArrIntersPts) const;

			// return true if part of a polygon is inside a vicinity of this polygon.
			// this means that polygons intersect or close enough.
			bool			IsInVicinity(const VWPolygon2D& poly, double dVicinity) const;

			// retun true if the given polygon and this polygon intersects each other (including touching)
			// outIsTouching returns if they are tourching
			bool			IsIntersecting(const VWPolygon2D& poly, bool& outIsTouching, double epsilon) const;
			bool			IsIntersecting(const VWPolygon2D& poly, bool& outIsTouching, VWPoint2D& outIntersPt, double epsilon) const;

			// retuns 'true' if the given polygon and this polygon intersects each other (including touching).
			// 'outIsTouching' returns if they are touching. 'outArrIntersPts' returns all intersection points.
			// NOTE: this function will be slower as it will search for all intersection points.
			bool			IsIntersecting(const VWPolygon2D& poly, bool& outIsTouching, TSTLPoints2DArray& outArrIntersPts, double epsilon) const;

			// returns 'true' if the given polygon and this polygon intersects each other (including touching).
			// 'outIsTouching' returns if they are touching. 'outArrIntersPts' returns all intersection points. 'outArrTouchPts' returns all touching points.
			// NOTE: this function will be slower as it will search for all intersection and touching points.
			bool			IsIntersecting(const VWPolygon2D& poly, bool& outIsTouching, TSTLPoints2DArray& outArrIntersPts, TSTLPoints2DArray& outArrTouchPts, double epsilon) const;

			// returns true if the given polygon is fully within this polygon
			bool			IsFullyInside(const VWPolygon2D& poly, double dEpsilon) const;
			// returns true if the given polygon is fully outside this polygon
			bool			IsFullyOutside(const VWPolygon2D& poly, double dEpsilon) const;

			// returns true if the given polygon is within this polygon, including having common points
			bool			IsInside(const VWPolygon2D& poly, double dEpsilon) const;
			// returns true if the given polygon is fully within this polygon, including having common points (using tolerance). faster.
			bool			IsWithin(const VWPolygon2D& poly, double tolerance) const;
			// returns true if the given polygon is fully outside this polygon, including having common points
			bool			IsOutside(const VWPolygon2D& poly, double dEpsilon) const;
			
			// get geometry center of the polygon
			VWPoint2D		GetCenter() const;
			// get mass center (centroid) of the polygon.
			VWPoint2D		GetMassCenter() const;
			// get an inside point: prefer points that are not too close to the polygon boundary.
			bool			GetPtInsidePoly(VWPoint2D& insidePt, double dEpsilon) const;
			// get random point that lies in the poly
			// XXX Bobi: not advisable to use: for polygon with small area it could take very Sint32 time to finish !
			VWPoint2D		GetRandomPtInPoly(double dEpsilon) const;

			// get bounding points along line
			// the result points are projection on the line of the two points from the poly wich are bound points along the line
			void			GetBoundingProjOnLine(VWPoint2D&/*in-out*/ minProjPt, VWPoint2D&/*in-out*/ maxProjPt, double dEpsilon) const;

			// get an inside point near the vertex at
			VWPoint2D		GetInsidePtNearVertexAt(size_t at);
			// get set of inside points near polygon's vertices
			TSTLPoints2DArray	GetInsideNearPts();

			// compares 'this' polygon against the given polygon. collects the parts of 'this' polygon that do not overlap with the given polygon.
			// Note: both polygons ('this' and given) must be polygonized (must have only corner vertices).
			void			GetDifferencesAgainstPolygon(const VWPolygon2D& polygon, TSTLPolygons2DArray& outDifferences, double epsilon) const;

			// compares 'this' polygon against the given polygon. collects the parts of 'this' polygon that do not overlap with the given polygon.
			// also, 'outNoOverlap' returns whether there is some overlapping (at all) or not between 'this' and the given polygon.
			// Note: both polygons ('this' and given) must be polygonized (must have only corner vertices).
			void			GetDifferencesAgainstPolygon(const VWPolygon2D& polygon, TSTLPolygons2DArray& outDifferences, bool& outNoOverlap, double epsilon) const;

			// compares 'this' polygon against the given polygon. collects the parts of 'this' polygon that overlap with the given polygon.
			// Note: both polygons ('this' and given) must be polygonized (must have only corner vertices).
			void			GetOverlapAgainstPolygon(const VWPolygon2D& polygon, TSTLPolygons2DArray& outOverlaps, double epsilon) const;

			// transform polygon's points
			void			PointsTransform(const VWTransformMatrix& matrix);
			void			InversePointsTransform(const VWTransformMatrix& matrix);

		// Math tools
		public:
			// is pt (x0,y0) is inside or/and on the specified triangle (x1,y1):(x2,y2):(x3,y3)
			static void		IsPtInTriangle( double x0, double y0,
											double x1, double y1,
											double x2, double y2,
											double x3, double y3,
											bool& outInTri, bool& outOnTri);
			static void		IsPtInTriangle(	double x0, double y0,
											double x1, double y1,
											double x2, double y2,
											double x3, double y3,
											bool& outInTri,
											bool& outOnTri,
											double epsilon);
			static void		IsPtInTriangle(	double x0, double y0,
											double x1, double y1,
											double x2, double y2,
											double x3, double y3,
											bool& outInTri,
											Sint32& outOnSegIndex,
											Sint32& outOnPtIndex,
											double epsilon);
			// is pt (x0,y0) on the border of the specified triangle (x1,y1):(x2,y2):(x3,y3)
			static void		IsPtOnTriangleBorder( double x0, double y0,
												  double x1, double y1,
												  double x2, double y2,
												  double x3, double y3,
												  Sint32& outOnSegIndex,
												  Sint32& outOnPtIndex,
												  double epsilon);
			// faster check if two polygons intersect each other. NOTE: no epsilon is used.
			static bool		ArePolygonsIntersecting_Fast(const VWPolygon2D& polyA, const VWPolygon2D& polyB, bool& outNoCommonArea);

			// checks if two polygons intersect each other (similar to the previous function). NOTE: it uses epsilon, ...
			// ... hence, it is a little bit slower than the previous one, but catches the suspicious boundary cases.
			static bool		ArePolygonsIntersecting(const VWPolygon2D& polyA, const VWPolygon2D& polyB, bool& outNoCommonArea, double epsilon);

			// checks whether given polygons overlap. note: works with polygon with corner vertices only. it is a fast check.
			static bool		ArePolygonsOverlapping(const VWPolygon2D& polygonA, const VWPolygon2D& polygonB, double tolerance);
			

		public:
			class CLockForEdit
			{
			public:
							CLockForEdit(VWPolygon2D& poly);
				virtual		~CLockForEdit();

			private:
				VWPolygon2D&	fPoly;
			};

		protected:
			struct SVertex
			{
									SVertex();
									SVertex(const SVertex& src);
				virtual				~SVertex();

				// operators.
				SVertex&			operator=(const SVertex& src);
				bool				operator==(const SVertex& that) const;
				bool				operator!=(const SVertex& that) const;

				// data.
				EVertexType			type;
				VWPoint2D			pt;
				double				dArcRadius;
				bool				bVisible;
			};
			typedef	std::vector<SVertex>	TVertexArray;

			struct SExtVertex : public SVertex
			{
									SExtVertex();
									SExtVertex(const SExtVertex& src);
									SExtVertex(const SVertex& src);
				virtual				~SExtVertex();

				// operators.
				SExtVertex&			operator=(const SExtVertex& src);
				SExtVertex&			operator=(const SVertex& src);
				bool				operator==(const SExtVertex& that) const;
				bool				operator!=(const SExtVertex& that) const;

				// data.
				VWPoint2D			controlPt;
			};
			typedef	std::vector<SExtVertex>	TExtVertexArray;

		protected:
			bool		GetArcFromArcPolyAt(size_t at, VWArc2D& outArc) const;

		// utilities for opening of polyline.
		protected:
			bool		GetPolygonizedPartOfClosedPoly(size_t inIndex, VWPolygon2D& outPolygon, size_t& outBegIndex, size_t& outEndIndex) const;
			bool		GetPartOfClosedPolyFromTo(size_t fromIndex, size_t toIndex, VWPolygon2D& outPolyPart) const;

			bool		GetPrevCornerVertexInClosedPoly(size_t inIndex, size_t& outPrevIndex) const;
			bool		GetNextCornerVertexInClosedPoly(size_t inIndex, size_t& outNextIndex) const;

		// polygonization utilities.
		protected:
			void			CalculatePolyline(	TExtVertexArray& arrVertices,
												size_t iterationCount = kPolygonize_MaxIterCount) const;

			void			SwapControlPts(TExtVertexArray& arrVertices) const;

			void			PolygonizeSection(	const SExtVertex& lastVert, const SExtVertex& thisVert, const SExtVertex& nextVert,
												VWPolygon2D& outPolygon,
												bool	interpolate		= false,
												short	splineRecusLevel= kPolygonize_MaxRecursLevel,
												double	arcDegRes		= kPolygonize_ArcResolution,
												short	arcRecursLevel	= kPolygonize_MaxRecursLevel) const;
			void			PolygonizeSplineSubSection(const VWPoint2D& v1, const VWPoint2D& v2, const VWPoint2D& v3, short level, bool interpolate, VWPolygon2D& outPolygon) const;

			// arc polygonization utilities.
			bool			CalcChamfer(const VWPoint2D& pt1, const VWPoint2D& int0Value, const VWPoint2D& pt4, VWPoint2D& lastCam, VWPoint2D& thisCam, VWPoint2D& center, double& radius, double& lastAngle, double& thisAngle) const;
			VWPoint2D		NextLoc(double a, const VWPoint2D& cen, double radius) const;

			void			PolygonizeArc(const VWPoint2D& lastPt, const VWPoint2D& thisPt, const VWPoint2D& nextPt, double radius, VWPolygon2D& outPolygon, short arcRecursLevel) const;
			void			PolygonizeArc(const VWPoint2D &lastPt, const VWPoint2D& nextPt, double radius, VWPoint2D& lastCam, VWPoint2D& thisCam, VWPoint2D& center, double theStart, double theArc, VWPolygon2D& outPolygon, short arcRecursLevel) const;
			void			PolygonizeArcSegment(double inStart, double inArc, const VWPoint2D& cen, double radius, VWPolygon2D& outPolygon, short arcRecursLevel) const;
			void			PolygonizeArcSegment(double arcStart, double arcEnd, short currentLevel, const VWPoint2D& cen, double radius, VWPolygon2D& outPolygon) const;

			// checks if the radius of arc vertex ('thisVert') is degenerate (zero) and recalculates it.
			void			RecalcDegenerateArcVertexRadius(SVertex* lastVert, SVertex* thisVert, SVertex* nextVert);

			// utilities for removing polygon "jags".

			// Checks if the four points define a 'S' shape.
			// Searches if the point 'pt' can be removed or moved in order to "smooth" the 'S' shape.
			// Note: vectors 'vecPtP1' and 'vecPtP3' have to be normalized.
			static bool		CheckForSShape(	const VWPoint2D& p0, const VWPoint2D& p1, const VWPoint2D& pt, const VWPoint2D& p3,
											const VWPoint2D& vecPtP1, const VWPoint2D& vecPtP3, double epsilon,
											VWPoint2D& outIntersPt, bool& outCanMove);

			// having a vertex of 'this poly' lying on a line (segment) from the 'given poly', checks whether the 'given poly' intersects 'this poly' at that vertex or just touches it.
			bool			IsPolyIntersectingPolyAt(size_t at, const VWPolygon2D& poly, size_t segIndex, double epsilon) const;
		
		// Get the convex hull using Graham scan algorithm 
		private:
			class CPointWithPolarAngle
			{
			public:
				CPointWithPolarAngle() : fThePoint( VWPoint2D( 0, 0 ) ), fTheAngle( 0.0 ) {}
				CPointWithPolarAngle( const VWPoint2D& pt, const VWPoint2D& angleAccordingTo = VWPoint2D( 1, 0 ), const VWPoint2D& ctr = VWPoint2D( 0, 0 ) );


				bool operator<( const CPointWithPolarAngle& other ) const;

				inline VWPoint2D GetPoint() const { return fThePoint; }

				private:
					VWPoint2D	fThePoint;
					double		fTheAngle;
			};
		public:
			// Utility function that gets the convex hull using Graham scan algorithm from an array of points. Note that the order of points is random. 
			static bool			GetBoundingPoly (const std::vector<VWPoint2D>& allPoints, VWPolygon2D& outPoly);

		protected:
			bool									fLockedForEdit;
			double									fdMinX;
			double									fdMaxX;
			double									fdMinY;
			double									fdMaxY;
			TVertexArray							farrVertices;
			bool									fbIsClosed;
		};
	}
}