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
		class VWCircle2D
		{
		public:
			// construction
						VWCircle2D();
						VWCircle2D(const VWPoint2D& center, double radius);
						VWCircle2D(const VWPoint2D& a, const VWPoint2D& b, const VWPoint2D& c);
						VWCircle2D(const VWCircle2D& src);
			virtual		~VWCircle2D();

			VWCircle2D&	operator=(const VWCircle2D& src);

			void		SetCircle(const VWPoint2D& center, double radius);
			void		SetCircle(const VWPoint2D& center);
			void		SetCircle(double radius);
			void		SetCircle(const VWPoint2D& a, const VWPoint2D& b, const VWPoint2D& c);

			VWPoint2D	GetCenter() const;
			double		GetRadius() const;
			void		GetCircle(VWPoint2D& outCenter, double& outRadius);

		// Mathematics
		public:
			// rotate this point at specified angle in degrees and center point
			void		RotateAtDeg(const VWPoint2D& centerPt, double_gs dDegAngle);
			// rotate this point at specified angle in radians and center point
			void		RotateAtRad(const VWPoint2D& centerPt, double_gs dRadAngle);
			// move the center of the cirle with specified values
			void		Move(double cx, double cy);
			// intersect this circle with a line
			bool		Intersect(const VWLine2D& line, double dEpsilon, WorldPt&/*out*/ outPt1, WorldPt&/*out*/ outPt2) const;
			// intersect this circle with another circle
			bool		Intersect(const VWCircle2D& circle, double dEpsilon, WorldPt&/*out*/ outPt1, WorldPt&/*out*/ outPt2) const;

		protected:
			VWPoint2D			m_ptCenter;
			double			m_dRadius;
		};
	}
}