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
		class VWPolygon2D;

		class VWRectangle2D
		{
		public:
			// construction
						VWRectangle2D();
						VWRectangle2D(const VWPoint2D& topleft, const VWPoint2D& botRight);
						VWRectangle2D(const VWPoint2D& topleft, double cx, double cy);
						VWRectangle2D(double left, double right, double top, double bottom);
						VWRectangle2D(const VWRectangle2D& src);
						~VWRectangle2D();

			VWRectangle2D& operator=(const VWRectangle2D& src);

			void		SetRect(const VWPoint2D& topleft, const VWPoint2D& botRight);
			void		SetRect(const VWPoint2D& topleft, double cx, double cy);
			void		SetRect(double left, double right, double top, double bottom);

			VWPoint2D	GetCenterLeft() const;
			VWPoint2D	GetCenterRight() const;
			VWPoint2D	GetTopCenter() const;
			VWPoint2D	GetBottomCenter() const;

			VWPoint2D	GetTopLeft() const;
			VWPoint2D	GetTopRight() const;
			VWPoint2D	GetBottomLeft() const;
			VWPoint2D	GetBottomRight() const;
			VWPoint2D	GetCenter() const;

			double		GetLeft() const;
			double		GetRight() const;
			double		GetTop() const;
			double		GetBottom() const;

			double		GetWidth() const;
			double		GetHeight() const;
			double		GetDiagonal() const;
			double		GetDiagonalSquared() const;

			bool		IsPtInside(double x, double y) const;
			bool		IsPtInside(const VWPoint2D& pt) const;
			bool		Intersect(const VWRectangle2D& rc) const;

			bool		IsPtInside(double x, double y, double epsilon) const;
			bool		IsPtInside(const VWPoint2D& pt, double epsilon) const;

			bool		IsInside(const VWRectangle2D& rc) const;
			bool		IsInside(const VWRectangle2D& rc, double epsilon) const;

			bool		IsOutside(const VWRectangle2D& rc) const;
			bool		IsOutside(const VWRectangle2D& rc, double epsilon) const;

			void		Unite(double x, double y);
			void		Unite(const VWPoint2D& pt);
			void		Unite(const VWPolygon2D& poly);
			void		Unite(const VWRectangle2D& rect);

			VWPolygon2D	AsPolygon() const;

		protected:
			bool			m_bIsEmpty;
			VWPoint2D		m_topLeft;
			VWPoint2D		m_bottomRight;
		};
	}
}