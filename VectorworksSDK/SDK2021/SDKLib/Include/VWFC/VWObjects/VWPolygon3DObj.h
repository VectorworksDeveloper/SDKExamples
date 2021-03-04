//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_POLYGON_3D_OBJECT__H
#define VECTORWORKS_POLYGON_3D_OBJECT__H

#pragma once

namespace VWFC
{
	using namespace Math;
	namespace VWObjects
	{
		// constant for the maximum allowed number of vertices in a 3D poly object.
		const size_t		kMaxNum3DPolyVertices		= std::numeric_limits<short>::max();

		class VWPolygon3DObj : public VWObject
		{
		public:
							VWPolygon3DObj();
							VWPolygon3DObj(std::initializer_list<VWPoint3D> src);
							VWPolygon3DObj(const VWPolygon3D& poly);
							VWPolygon3DObj(const VWPolygon2D& poly, double z=0);
							VWPolygon3DObj(MCObjectHandle hPolygon3D);
							VWPolygon3DObj(const VWPolygon3DObj& src);
			virtual			~VWPolygon3DObj();

			VWPolygon3DObj&	operator=(const VWPolygon3DObj& src);

		public:
			void			AddVertex(double x, double y, double z, bool bRecalcBounds=true);
			void			AddVertex(const VWPoint3D& pt, bool bRecalcBounds=true);
			void			AddVertex(const TSTLPoints3DArray& arrPts, bool reverse, bool bRecalcBounds=true);
			void			InsertVertex(size_t beforeIndex, const VWPoint3D& pt, bool bRecalcBounds=true);
			void			SetVertex(size_t index, const VWPoint3D& pt, bool bRecalcBounds=true);
			VWPoint3D		GetVertex(size_t index) const;

			void			GetPolygon(VWPolygon2D& outPoly) const;
			void			GetPolygon(VWPolygon3D& outPoly) const;
			void			SetPolygon(const VWPolygon3D& poly);

			size_t			GetVertexCount() const;
			void			DeleteVertex(size_t index);

			void			SetClosed(bool bClosed);
			bool			GetClosed() const;

			virtual void	GetObjectMatrix(VWTransformMatrix& outMatrix) const;
			virtual void	SetObjectMatrix(const VWTransformMatrix& matrix);

		// tool
		public:
			// Return true if the specified object handle is 2D locus
			static bool		IsPolygon3DObject(MCObjectHandle hObj);
		};
	}
}

#endif // VECTORWORKS_POLYGON_3D_OBJECT__H