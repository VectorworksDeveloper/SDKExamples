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
		class VWCube
		{
		public:
			// construction
								VWCube();
								VWCube(const VWPoint3D& minPoint, const VWPoint3D& maxPoint);
								VWCube(const VWPoint3D& minPt, double cx, double cy, double cz);
								VWCube(const VWCube& src);
								~VWCube();

			VWCube&				operator=(const VWCube& src);
			bool				operator==(const VWCube& that) const;

			void				Clear();
			void				SetCube(const VWPoint3D& minPoint, const VWPoint3D& maxPoint);
			void				SetCube(const VWPoint3D& minPt, double cx, double cy, double cz);

			bool				IsEmpty() const;
			double				GetWidth() const;
			double				GetDepth() const;
			double				GetHeight() const;
			const VWPoint3D&	GetMinPoint() const;
			const VWPoint3D&	GetMaxPoint() const;

			void				Unite(double x, double y, double z);
			void				Unite(const VWPoint3D& pt);
			void				Unite(const VWPolygon2D& poly, double z = 0.0);
			void				Unite(const TSTLPoints2DArray& points, double z = 0.0);
			void				Unite(const VWPolygon3D& poly);
			void				Unite(const TSTLPoints3DArray& points);
			void				Unite(const VWCube& cube);

			bool				IsPtInside(double x, double y, double z) const;
			bool				IsPtInside(const VWPoint3D& pt) const;

			bool				IsPtInside(double x, double y, double z, double epsilon) const;
			bool				IsPtInside(const VWPoint3D& pt, double epsilon) const;

			bool				IsOutside(const VWCube& that) const;
			bool				IsOutside(const VWCube& that, double epsilon) const;

			bool				IsInside(const VWCube& that) const;
			bool				IsInside(const VWCube& that, double epsilon) const;

		protected:
			bool			bEmpty;
			VWPoint3D		m_maxPoint;
			VWPoint3D		m_minPoint;
		};
	}
}