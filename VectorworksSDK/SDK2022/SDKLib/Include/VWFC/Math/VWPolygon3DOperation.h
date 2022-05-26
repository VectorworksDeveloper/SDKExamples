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
		class VWPolygon3DOperation : public VWPolygonOperation
		{
		public:
							VWPolygon3DOperation(const VWPolygon2D& clipPoly);
			virtual			~VWPolygon3DOperation();

		public:
			bool			BooleanOR(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons);
			bool			BooleanAND(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons, bool forceOperation = false);
			bool			BooleanAND(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons, bool& outPolysOverlap, bool forceOperation = false);
			bool			BooleanEXOR(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons);
			bool			BooleanPoly_SUB_Clip(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons, bool forceOperation = false);
			bool			BooleanClip_SUB_Poly(const VWPolygon3D& polygon, TSTLPolygons3DArray&/*out*/ resultPolygons);
			// cut the specified polygon by cutter
			// the result are those parts of the polygon that lie inside the cutter
			bool			CutPolygon(const VWPolygon3D& inPoly, TSTLPolygons3DArray&/*out*/ resultPolygons);

		// tools
		public:
			// clip the 'poly' using 'clipper' polygon as clipping object
			static bool		ClipToPoly(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly, const VWPolygon2D& inClipper);
			static bool		ClipToPoly(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly, const VWPolygon2D& inClipper, bool& outPolysOverlap, bool forceOperation = false);
			static bool		CombinePolygons(VWPolygon3D&/*out*/ resultPolygon, const VWPolygon3D& inPoly1, const VWPolygon2D& inPoly2);
			// result = poly1 - poly2
			static bool		SubtractPolygons(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly1, const VWPolygon2D& inPoly2);
			// cut the specified polygon by cutter
			// the result are those parts of the polygon that lie inside the cutter
			static bool		CutPolygon(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly, const VWPolygon2D& inCutter);
			// split the specified polygon by splitter.
			// the result are all split parts of the polygon (their union will be the polygon itself).
			static bool		SplitByPoly(TSTLPolygons3DArray&/*out*/ resultPolygons, const VWPolygon3D& inPoly, const VWPolygon2D& inSplitter);

		protected:
			// collects inner parts (inside the cutter).
			virtual void	WalkValidVertexsForCut(SVertex* pFirstVertex);
			// collects the outer parts (outside the clipper).
			virtual void	WalkValidVertexsForClip(SVertex* pFirstVertex);
			virtual void	AddValidVertex(SVertex* pVertex);
			virtual void	FinishValidVerticesForPoly(bool bClosed);

			TSTLPolygons3DArray*	m_pSTLCutResultArray;
			VWPolygon3D				m_cutResutPoly;

			// return true if the two polygons are overlapping -- meaning will make sense clipping
			static bool			AreOverlapping(const VWPolygon2D& a, const VWPolygon3D& b);
		};
	}
}