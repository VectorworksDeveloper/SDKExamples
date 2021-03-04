//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	using namespace Math;
	namespace VWObjects
	{
		// constant for the maximum allowed number of vertices in a 2D poly object.
		const size_t		kMaxNum2DPolyVertices		= std::numeric_limits<short>::max();

		class VWPolygon2DObj : public VWObject
		{
		public:
							VWPolygon2DObj();
							VWPolygon2DObj(std::initializer_list<VWPoint2D> src);
							VWPolygon2DObj(const VWPolygon2D& poly);
							VWPolygon2DObj(const VWPolygon3D& poly);
							VWPolygon2DObj(MCObjectHandle hPoly2D);
							VWPolygon2DObj(const VWPolygon2DObj& src);
							VWPolygon2DObj(const VWRectangle2D& srcRect);
			virtual			~VWPolygon2DObj();

			VWPolygon2DObj&	operator=(const VWPolygon2DObj& src);

		public:
			void			AddVertex(double x, double y, bool bRecalcBounds=true);
			void			AddVertex(const VWPoint2D& pt, bool bRecalcBounds=true);

			void			AddCornerVertex(double x, double y, bool bRecalcBounds=true);
			void			AddCornerVertex(const VWPoint2D& pt, bool bRecalcBounds=true);
			void			InsertCornerVertex(size_t beforeIndex, const VWPoint2D& pt, bool bRecalcBounds=true);
			void			SetCornerVertex(size_t index, const VWPoint2D& pt, bool bRecalcBounds=true);

			void			AddBezierVertex(const VWPoint2D& pt, bool bRecalcBounds=true);
			void			InsertBezierVertex(size_t beforeIndex, const VWPoint2D& pt, bool bRecalcBounds=true);
			void			SetBezierVertex(size_t index, const VWPoint2D& pt, bool bRecalcBounds=true);

			void			AddCubicVertex(const VWPoint2D& pt, bool bRecalcBounds=true);
			void			InsertCubicVertex(size_t beforeIndex, const VWPoint2D& pt, bool bRecalcBounds=true);
			void			SetCubicVertex(size_t index, const VWPoint2D& pt, bool bRecalcBounds=true);

			void			AddArcVertex(const VWPoint2D& pt, double dRadius, bool bRecalcBounds=true);
			void			InsertArcVertex(size_t beforeIndex, const VWPoint2D& pt, double dRadius, bool bRecalcBounds=true);
			void			SetArcVertex(size_t index, const VWPoint2D& pt, double dRadius, bool bRecalcBounds=true);

			void			AddRadiusVertex(const VWPoint2D& pt, bool bRecalcBounds=true);
			void			InsertRadiusVertex(size_t beforeIndex, const VWPoint2D& pt, bool bRecalcBounds=true);
			void			SetRadiusVertex(size_t index, const VWPoint2D& pt, bool bRecalcBounds=true);

			void			GetPolygon(VWPolygon2D& outPoly) const;
			void			GetPolygon(VWPolygon3D& outPoly) const;
			void			SetPolygon(const VWPolygon2D& poly);			

			double			GetArea() const;
			double			GetPerimeter() const;

			size_t			GetVertexCount() const;
			void			DeleteAllVertices();
			void			DeleteVertex(size_t vertIndex);

			VWPoint2D		GetVertexPoint(size_t index) const;
			void			SetVertexPoint(size_t index, const VWPoint2D& pt);
			double			GetVertexRadius(size_t index) const;
			double			GetVertexMaxRadius(size_t index) const;
			bool			IsVertexCorner(size_t index) const;
			bool			IsVertexBezier(size_t index) const;
			bool			IsVertexCubic(size_t index) const;
			bool			IsVertexArc(size_t index) const;
			bool			IsVertexRadius(size_t index) const;
			// Identical to GetVertex except that it returns the Bezier control point for cubic spline sections.
			VWPoint2D		GetControlVertex(size_t index) const;

			bool			IsVertexVisible(size_t index) const;
			void			SetVertexVisible(size_t index, bool bVisible);
			void			SetAllVertexVisible(bool bVisible);
			void			ApplyVertexVisible(const VWPolygon2D& poly);

			bool			IsClosed() const;
			void			SetClosed(bool bClosed);

			// conversion
			void			ConvertToPolyline();
			void			ConvertToPolygon(short res=0);

			// hole managment
			void			AddHoleObject(const VWPolygon2D& poly);
			void			AddHoleObject(const VWPolygon2DObj& poly);
			size_t			GetHoleObjectsCount() const;
			MCObjectHandle	GetHoleObjectAt(size_t at);
            void            GetHoles(TMCObjectHandlesSTLArray& arrOpenings);
            void            GetHoles(TSTLPolygons2DArray& arrOpenings);
            void            GetHoles(TSTLPolygons3DArray& arrOpenings);
		
		// tool
		public:
			// Return true if the specified object handle is 2D locus
			static bool		IsPoly2DObject(MCObjectHandle hObj);
			static bool		IsPolygon2DObject(MCObjectHandle hObj);
			static bool		IsPolyline2DObject(MCObjectHandle hObj);
		};
	}
}