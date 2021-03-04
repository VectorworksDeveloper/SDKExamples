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
		class VWPolygonOperation
		{
		public:
							VWPolygonOperation(const VWPolygon2D& clipPoly);
			virtual			~VWPolygonOperation();

			bool			BooleanOR(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons);
			bool			BooleanOR(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons, bool& outNoCommonArea, bool& outInnerClipper);
			bool			BooleanAND(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons);
			bool			BooleanAND(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons, bool& outNoCommonArea);
			bool			BooleanEXOR(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons);
			bool			BooleanPoly_SUB_Clip(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons);
			bool			BooleanPoly_SUB_Clip(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons, bool& outNoCommonArea);
			bool			BooleanClip_SUB_Poly(const VWPolygon2D& polygon, TSTLPolygons2DArray&/*out*/ resultPolygons);

			// cut the specified polygon by cutter
			// the result are those parts of the polygon that lie inside the cutter
			// NOTE! the cut preserve the vertex types inside the cutter. New points are corners
			bool			CutPolygon(const VWPolygon2D& inPoly, TSTLPolygons2DArray&/*out*/ resultPolygons);
			// a faster version. NOTE! as it might work a little bit differently, preferably use it in new functionalities and test well!
			bool			CutPolygon_Fast(const VWPolygon2D& inPoly, TSTLPolygons2DArray&/*out*/ resultPolygons);

			// clip the specified polygon by clipper.
			// the result are those parts of the polygon that lie outside the clipper.
			// NOTE! the cut preserve the vertex types outside the clipper. New points are corners !
			bool			ClipPolygon(const VWPolygon2D& inPoly, TSTLPolygons2DArray&/*out*/ resultPolygons);
			// a faster version. NOTE! as it might work a little bit differently, preferably use it in new functionalities and test well!
			bool			ClipPolygon_Fast(const VWPolygon2D& inPoly, TSTLPolygons2DArray&/*out*/ resultPolygons);

			// tools
		public:
			// clip the 'poly' using 'clipper' polygon as clipping object
			static bool		ClipToPoly(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly, const VWPolygon2D& inClipper);
			static bool		CombinePolygons(VWPolygon2D&/*out*/ resultPolygon, const VWPolygon2D& inPoly1, const VWPolygon2D& inPoly2);
			// result = poly1 - poly2
			static bool		SubtractPolygons(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly1, const VWPolygon2D& inPoly2);
			// cut the specified polygon by cutter
			// the result are those parts of the polygon that lie inside the cutter
			// NOTE! the cut preserve the vertex types inside the cutter. New points are corners
			static bool		CutPolygon(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly, const VWPolygon2D& inCutter);

			// removes vertices of a polygogon causing it to smooth
			// 'smoothAber' is used within the smooth algorithm to define how much
			// the smoothed curve may deviate from the original
			static bool		SmoothPolygon(VWPolygon2D&/*out*/ resultPolygon, const VWPolygon2D& polygon, double smoothAber=10.0);

			// add points when segments polygon intersect with source polyg
			// and hide those segments that are inside the specified segment polygons
			static void		HideSetmentsBeloPolygon(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& arrSegmentPolys);

			// clips polygon by the specified clipper polygons.
			// result are those parts of clipped polygon which lie outside the clipper polygons.
			static void		ClipByPolygons(TSTLPolygons2DArray&/*out*/ outResultPolys, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& clipPolys);

			// clips polygon by the specified clipper polygons. returns whether polygon is clipped by clippers.
			// result are closed polygons representing the parts of the polygon which lie outside the clippers.
			static bool		Polygon_SUB_Clippers(TSTLPolygons2DArray&/*out*/ outResultPolys, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& clipPolys);

			// clips polygon by the specified clipper polygons. returns whether polygon is clipped by clippers.
			// result are closed polygons representing the parts of the polygon which lie inside all of the clippers.
			static bool		Polygon_AND_Clippers(TSTLPolygons2DArray&/*out*/ outResultPolys, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& clipPolys);

			// unites polygon with the specified polygons. returns if there is at least one union.
			static bool		Polygon_OR_Polygons(TSTLPolygons2DArray&/*out*/ outResultPolys, const VWPolygon2D& inPoly, const TSTLPolygons2DArray& inPolys);

			// an algorithm for partitioning of a complex (self-intersecting) polygon.
			// NOTE: 1. The input polygon must be closed.
			//		 2. Works only for complex (self-intersecting) polygons that have only corner vertices.
			static void		PartitionComplexPolygon(TSTLPolygons2DArray&/*out*/ resultPolygons, const VWPolygon2D& inPoly);

			// having a set of polygons, concatenates those which have touching endpoints.
			static void		ConnectAdjoiningPolygons(TSTLPolygons2DArray& inOutPolygons, bool checkVertexTypes = false);

		protected:
			void*				m_pBooleanEngine;
			const VWPolygon2D&	m_clipPoly;

			// return true if the two polygons are overlapping -- meaning will make sense clipping
			static bool			AreOverlapping(const VWPolygon2D& a, const VWPolygon2D& b);

			// data for the 'CutPolygon' routine
			struct SVertex {
				SVertex();

				size_t		index;
				bool		bInters;
				bool		bOnCutter;
				bool		bInCutter;
				SVertex*	pNextVertex;
				VWPoint2D	pt;
				double		z;
				VectorWorks::Math::EVertexType	type;			// type of this vertex (corner, bezier, cubic, arc)
				double		radius;			// radius for arc vertex
				bool		bVisible;
			};
			static void		AddIntersectionVerticesForCut(SVertex* pFirstVertex, size_t& vertsCnt, const VWPolygon2D& cutter);
			static void		AddIntersectionVertices(SVertex* pFirstVertex, size_t& vertsCnt, const VWPolygon2D& cutter);

			// collects inner parts (inside the cutter).
			virtual void	WalkValidVertexsForCut(SVertex* pFirstVertex);
			// collects the outer parts (outside the clipper).
			virtual void	WalkValidVertexsForClip(SVertex* pFirstVertex);
			virtual void	AddValidVertex(SVertex* pVertex);
			virtual void	FinishValidVerticesForPoly(bool bClosed);

			// creates vertices list from 2D polygon.
			static bool		InitVerticesListFromPoly(const VWPolygon2D& inPoly, SVertex*& outFirstVert, SVertex*& outLastVert);
			// creates vertices list from 3D polygon.
			static bool		InitVerticesListFromPoly(const VWPolygon3D& inPoly, SVertex*& outFirstVert, SVertex*& outLastVert);
			// clears vertices list.
			static void		ClearVerticesList(SVertex*& firstVert, SVertex*& lastVert);

			// having intersection vertices added (using cutter/clipper), searches for the beginning of an inner segment (inside cutter/clipper).
			static void		SearchStartOfInnerSegment(SVertex* inFirstVertex, SVertex*& outVertex);
			// having intersection vertices added (using cutter/clipper), searches for the ending of an inner segment (outside cutter/clipper).
			static void		SearchFinishOfInnerSegment(SVertex* inFirstVertex, SVertex*& outVertex);

			// data structures for the 'PartitionComplexPolygon' routine.
			// an algorithm for partitioning of a complex (self-intersecting) polygon.
			struct SIntersPt				// intersection point.
			{
							SIntersPt();
							~SIntersPt();

				VWPoint2D	fPt;			// intersection point.

				size_t		fSegIndex0;		// index of first intersecting segment.
				size_t		fSegIndex1;		// index of second intersecting segment.
			};

			typedef	SIntersPt				TIntersPt;
			typedef	std::vector<TIntersPt>	TSTLIntersPtArray;

			// Poly segment.
			struct SPolySegment
			{
									SPolySegment();
									~SPolySegment();

				size_t				fIndex;			// index of segment.
				VWPoint2D			fBegPt;			// begin segment point.
				VWPoint2D			fEndPt;			// end segment point.

				TSTLIntersPtArray	farrIntersPts;	// sorted array of the points that intersect the segment.
			};

			typedef	SPolySegment				TPolySegment;
			typedef	std::vector<TPolySegment>	TSTLPolySegmentArray;

			static bool		CollectSelfIntersData(const VWPolygon2D& polygon, TSTLPolySegmentArray& outArrPolySegments);
			static void		GetSimplePolygon(const TSTLPolySegmentArray& arrPolySegments, size_t segIndex, const VWPoint2D& fromPt, bool reversedDir, bool goToRight, VWPolygon2D& resPoly);

			TSTLPolygons2DArray*	m_pSTLCutResultArray;
			VWPolygon2D				m_cutResutPoly;
		};
	}
}