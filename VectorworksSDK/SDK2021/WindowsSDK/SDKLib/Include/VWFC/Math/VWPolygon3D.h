//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_POLYGON_3D__H
#define VECTORWORKS_POLYGON_3D__H

#pragma once

namespace VWFC
{
	namespace Math
	{
		class VWCube;

		class VWPolygon3D
		{
		public:
								VWPolygon3D();
								VWPolygon3D(std::initializer_list<VWPoint3D> src);
								VWPolygon3D(const VWPolygon3D& src);
								VWPolygon3D(const VWPolygon2D& src, double z =0);
								VWPolygon3D(const TSTLPoints3DArray& src);
								VWPolygon3D(const TSTLPoints3DVWArray& src);
								VWPolygon3D(IPolyDefPtr pPolygonDef);
								// create 3d polygon by three points (a plane)
								VWPolygon3D(const VWPoint3D& a, const VWPoint3D& b, const VWPoint3D& c);
								VWPolygon3D(const VWTransformMatrix& plane);
			virtual				~VWPolygon3D();

			bool				operator==(const VWPolygon3D& poly) const;
			bool				operator!=(const VWPolygon3D& poly) const;

			VWPolygon3D&		operator=(const VWPolygon3D& src);
			VWPolygon3D&		operator=(const VWPolygon2D& src);
			VWPolygon3D&		operator=(const TSTLPoints3DArray& src);
			VWPolygon3D&		operator=(const TSTLPoints3DVWArray& src);
			VWPolygon3D&		operator=(IPolyDefPtr pPolygonDef);

		public:
			// setting polygon
			void				SetPolygon(const TSTLPoints3DArray& src);
			void				SetPolygon(const TSTLPoints3DVWArray& src);
			void				SetPolygon(IPolyDefPtr pPolygonDef);
			void				GetPolygon(TSTLPoints3DArray& out) const;
			void				GetPolygon(TSTLPoints3DVWArray& out) const;
			void				GetPolygon(IPolyDefPtr pPolygonDef) const;

			// create 3d polygon by three points (a plane)
			void				SetPolygon(const VWPoint3D& a, const VWPoint3D& b, const VWPoint3D& c);
			void				SetPolygon(const VWTransformMatrix& plane);

			void				ClearVertices();
			void				ClearVertex(size_t at);
			void				AddVertex(double x, double y, double z);
			void				AddVertex(const VWPoint3D& pt);
			void				AddVertex(const VWPolygon3D& poly);
			void				AddVertex(const TSTLPoints3DArray& arrPts, bool reverse);
			void				InsertVertex(size_t at, double x, double y, double z);
			void				InsertVertex(size_t at, const VWPoint3D& pt);
			void				InsertVertex(size_t at, const VWPolygon3D& poly);

			bool				IsEmpty() const;
			size_t				GetVertexCount() const;

			VWPoint3D&			operator[](size_t at);
			const VWPoint3D&	operator[](size_t at) const;

			const VWPoint3D&	GetVertexAt(size_t at, bool bLoopVerts=false) const;
			VWPoint3D&			GetVertexAt(size_t at, bool bLoopVerts=false);
			void				SetVertexAt(size_t at, const VWPoint3D& pt, bool bLoopVerts=false);
			VWLine3D			GetLineAt(size_t at) const;

			bool				IsClosed() const;
			void				SetClosed(bool bClosed);
			
			// reverse the order of the points (if CW to CCW or CCW to CW)
			void				ReversePoints();

			// determine if the polygon is Clock Wise oriented
			bool				IsClockWise() const;

			// return true if the passed polygon has more than 3 different vertices
			bool				IsValidPolygon(double dEpsilon) const;

			// check if all polygon vertices lie on a 3D plane.
			bool				IsFlatPolygon(double dEpsilon) const;

			// removed all same points in the polygon
			void				CleanUpPolygon(double dEpsilon);

			// gets a polygon where all same ('duplicate') points are removed.
			void				GetCleanedUpPolygon(VWPolygon3D& outCleanPoly, double epsilon) const;

			// this function works as follows depending on 'doClosenessCheck':
			// ( doClosenessCheck == false ) - clean up all polygon vertices which are collinear with their neighbors.
			// ( doClosenessCheck == true  ) - clean up all polygon vertices which are collinear with their neighbors and are too close to their neighbors.
			void				CleanUp_FeaturePreserving(bool doClosenessCheck, double epsCollinear, double epsCloseness);

			void				GetPlanarPolygon(VWPolygon2D& out) const;

			// given a 3D polygon, segments it (subdivides it) into segments of 'segmentation length' by introducing ...
			// ... new vertices while preserving the original ones (thus, there might be produced shorter segments as well).
			// note: shape of the original 3D polygon will be fully preserved.
			void				GetSegmentedPolygon(VWPolygon3D& outPolygon3D, double segmentationLength) const;

			void				GetXBounds(double& outMinX, double& outMaxX) const;
			void				GetYBounds(double& outMinY, double& outMaxY) const;
			void				GetZBounds(double& outMinZ, double& outMaxZ) const;

			// get bounds cube.
			VWCube				GetBoundsCube() const;
			// gets the bounds rectangle of the planar (projected) polygon.
			VWRectangle2D		GetPlanarBoundsRect() const;

		// mathematics
		public:
			// find index of next 'apposite' polygon point (not too close).
			bool				GetNextAppositePtIndex(size_t inPtIndex, size_t& outNextPtIndex, double dEpsilon) const;
			// find next 'apposite' polygon point (not too close).
			bool				GetNextAppositePt(size_t inPtIndex, VWPoint3D& outNextPt, double dEpsilon) const;
			// find index of previous 'apposite' polygon point (not too close).
			bool				GetPrevAppositePtIndex(size_t inPtIndex, size_t& outPrevPtIndex, double dEpsilon) const;
			// find previous 'apposite' polygon point (not too close).
			bool				GetPrevAppositePt(size_t inPtIndex, VWPoint3D& outPrevPt, double dEpsilon) const;

			// find indices of the first 3 'apposite' polygon points (not too close and not collinear).
			// their corresponding polygon points define a reasonable plane.
			bool				GetPlanePtIndices(size_t& ptIndex0, size_t& ptIndex1, size_t& ptIndex2) const;
			// find the first 3 'apposite' polygon points (not too close and not collinear).
			// they define a reasonable plane.
			bool				GetThreePlanePoints(VWPoint3D& pt0, VWPoint3D& pt1, VWPoint3D& pt2) const;
			// return the plane equation of the plane made by the first 3 'apposite' vertices (not too close and not collinear).
			// A*x + B*y + C*z + D
			bool				GetPlaneEquation(double& A, double& B, double& C, double& D) const;
			// return the plane equation of the plane made by the specified 3 vertices.
			// A*x + B*y + C*z + D
			bool				GetPlaneEquation(size_t ptIndex0, size_t ptIndex1, size_t ptIndex2, double& A, double& B, double& C, double& D) const;
			// set the object to a plane by given equation A*x + B*y + C*z + D = 0
			void				SetPlaneEquation(double A, double B, double C, double D);
			
			// return transformation which describes this plane
			VWTransformMatrix	GetTransformMatrix() const;
			
			// perpendicular distance from the point to the plane made by the first 3 points
			// the distance is reversed if the polygon is CCW
			double				GetDistance(const VWPoint3D& pt) const;
			// the vertical distance -- what z for the point to be on the plane
			double				GetVerticalDistance(const VWPoint3D& pt) const;
			
			// normal of the plane made by the first 3 points
			VWPoint3D			Normal() const;

			// average normal to the "average" plane which best fits to arbitrary polygon (Newell's Method).
			VWPoint3D			AveragedNormal() const;

			// get geometry center of the polygon
			VWPoint3D			GetCenter() const;

			// get a point at a given distance from the beginning
			bool				GetPtOnPoly( double offset, VWPoint3D& outPt ) const;

			// get closest 3d point to poly from other 3d point
			VWPoint3D			GetClosestPtOnPoly3d( const VWPoint3D& pt, double& outDist, Sint32& outOnSegIndex ) const;
			
			// calculate the area of the polygon
			// positive if polygon is CCW -- negative if CW
			double				GetArea() const;

			double				GetPerim() const;

			// check if it is an equalish polygon.
			bool				EqualishTo(const VWPolygon3D& poly, bool doReverseCheck = false) const;
			
			// intersect the plane made by the first 3 points with a specified line
			//  return false if line is parallel to plane
			bool				Intersect(const VWLine3D& line, VWPoint3D& outIntersPt, double dEpsilon) const;
			// intersect the plane made by the first 3 points with a specified line given by points and direction
			//  return false if line is parallel to plane
			bool				Intersect(const VWPoint3D& startPt, const VWPoint3D& dir, VWPoint3D& outIntersPt, double dEpsilon) const;
			// intersect this plane made by the first 3 points
			// with the specified plane (first 3 points)
			//  return false is planes are parallel
			bool				Intersect(const VWPolygon3D& plane, VWLine3D& outIntersLine, double dEpsilon) const;

			// determines if a point is in the area of the projected polygon (the 2D projection)
			bool				IsPtInProjPoly2D(double ptX, double ptY, double dEpsilon) const;
			bool				IsPtInProjPoly2D(const VWPoint2D& pt, double dEpsilon) const;

			bool				IsPtInOrOnProjPoly2D(double ptX, double ptY, double dEpsilon) const;

			// transform polygon's points
			void				PointsTransform(const VWTransformMatrix& matrix);
			void				InversePointsTransform(const VWTransformMatrix& matrix);
			void				MovePoints(double dx, double dy, double dz);
			void				MovePoints(const VWPoint3D& amount);

		// Local tools.
		private:

			// checks whether the two polygons have common volume.
			static bool			DoPolygonsHaveCommonCubeVolume(const VWPolygon3D& poly0, const VWPolygon3D& poly1, double coordEpsilon);

			// checks whether the two triangles have common volume.
			static bool			DoTrianglesHaveCommonCubeVolume(const VWPoint3D& tri0Pt0, const VWPoint3D& tri0Pt1, const VWPoint3D& tri0Pt2,
																const VWPoint3D& tri1Pt0, const VWPoint3D& tri1Pt1, const VWPoint3D& tri1Pt2,
																double coordEpsilon);

		// Tools.
		public:

			// checks whether two 3D triangles intersect.
			// returns the intersection line/point.
			static bool			DoTrianglesIntersect(const VWPoint3D& tri0Pt0, const VWPoint3D& tri0Pt1, const VWPoint3D& tri0Pt2,
													 const VWPoint3D& tri1Pt0, const VWPoint3D& tri1Pt1, const VWPoint3D& tri1Pt2,
													 VWLine3D& outIntersLine, double coordEpsilon, double radEpsilon);
			// checks whether two 3D triangles intersect.
			static bool			DoTrianglesIntersect(const VWPoint3D& tri0Pt0, const VWPoint3D& tri0Pt1, const VWPoint3D& tri0Pt2,
													 const VWPoint3D& tri1Pt0, const VWPoint3D& tri1Pt1, const VWPoint3D& tri1Pt2,
													 double coordEpsilon, double radEpsilon);

		protected:
			TSTLPoints3DArray						farrVertices;
			bool									fbIsClosed;
		};

		// array of polygon defintion
		typedef		std::vector<VWPolygon3D>									TSTLPolygons3DArray;
		typedef		std::vector<VWPolygon3D, std::vwallocator<VWPolygon3D> >	TSTLPolygons3DVWArray;
	}
}

#endif // VECTORWORKS_POLYGON_3D__H