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
		class VWArc2D
		{
		public:
			// construction
						VWArc2D();
						VWArc2D(const VWPoint2D& center, double radius);
						// Constructs an arc with the given center, radius, start and sweep angles in degrees.
						// startAngleDeg - The angular position in degrees where the arc begins, measured CCW from the positive x-axis.
						// sweepAngleDeg - The angular sweep of the arc in degrees, measured CCW from the start of the arc.
						// Positive sweep angles will yield a CCW arc, while negative ones will yield a CW arc.
						VWArc2D(const VWPoint2D& center, double radius, double startAngleDeg, double sweepAngleDeg);
						VWArc2D(const VWPoint2D& a, const VWPoint2D& ptOnArc, const VWPoint2D& b);
						VWArc2D(const VWArc2D& src);
			virtual		~VWArc2D();

			VWArc2D&	operator=(const VWArc2D& src);

			void		SetArc(const VWPoint2D& center, double radius);
			void		SetArc(const VWPoint2D& center, double radius, double startAngleDeg, double sweepAngleDeg);
			void		SetArc(const VWPoint2D& startPt, const VWPoint2D& ptOnArc, const VWPoint2D& endPt);

			void		GetArc(VWPoint2D& outCenter, double& outRadius) const;
			void		GetArc(VWPoint2D& outCenter, double& outRadius, double& outStartAngleDeg, double& outSweepAngleDeg) const;
			void		GetArc(VWPoint2D& outStartPt, VWPoint2D& outPtOnArc, VWPoint2D& outEndPt) const;

			const VWPoint2D&	GetCenterPt() const;
			VWPoint2D&			GetCenterPt();
			const VWPoint2D&	GetStartPt() const;
			VWPoint2D&			GetStartPt();
			const VWPoint2D&	GetEndPt() const;
			VWPoint2D&			GetEndPt();

			double		GetRadius() const;

			// Returns the start angle in degrees, measured CCW from the positive x-axis.
			double		GetStartAngle() const;

			// Returns the sweep angle in degrees. Will be positive for CCW arcs and negative for CW arcs.
			double		GetSweepAngle() const;

		// Mathematics
		public:
			// Returns the signed length of the arc. Will be positive for CCW arcs and negative for CW arcs.
			double		GetLength() const;

			// Returns the distance along the arc up to the given point. The result is always non-negative.
			double		GetLength(const VWPoint2D& pt) const;

			// calculate sweep angle from the arc start to the specified point
			// returns angle in degrees
			double		CalcSweepAngle(const VWPoint2D& pt) const;

			// return point on the center of the arc
			VWPoint2D	GetPtOnArc() const;
			// return point on the arc at specified offset from the start of the arc
			VWPoint2D	GetPtOnArc(double offset) const;

			// return point on the arc at specified angree in degree from the start of the arc
			VWPoint2D	GetPtOnArcAngle(double angDeg) const;

			// teturns a point on this arc which is closest to the input point.
			VWPoint2D	PtPerpArc(const VWPoint2D& pt) const;

			// returns the closest point to the arc segment or the closest arc segment end.
			VWPoint2D	PtPerpArcSeg(const VWPoint2D& pt) const;

			// return the distance from the specified point to the arc
			double		Distance(const VWPoint2D& pt) const;

			bool		IsPtOnArc(const VWPoint2D& pt, double dEpsilon) const;

			bool		IsPtInOrOnArc(const VWPoint2D& pt, double dEpsilon) const;
			//debug
			bool		IsPtOnArc(const VWPoint2D& ptOnArc, double dEpsilon, double& outOffset) const;

			// return 2D polygon containing <180 arcs represetning this arc
			void		GetPolygon(VWPolygon2D& outPoly, double stepAngleDeg=90, bool allowArcVerts=true) const;

			// adds arc sample points (ordered to form polygon) to the poly.
			// note: the 'resolution' is defined by the 'stepAngDeg'.
			void		AddArcPolygonizationToPoly(VWPolygon2D& inOutPoly, bool addArcEnds, double stepAngDeg = 5.0) const;

			// returns two intersection points if possible or one point if the line is tangent
			bool		GetLineArcIntersection(const VWPoint2D& pt1, const VWPoint2D& pt2, VWPoint2D& ptSec1, VWPoint2D& ptSec2);

		protected:
#ifdef _DEBUG
			void		CheckInnerDataConsistency();
#endif
		private:
			VWPoint2D	fCenterPt;
			VWPoint2D	fStartPt;
			VWPoint2D	fEndPt;

			// keep these also for faster functionallity
			double		fRadius;
			double		fStartAngleDeg;
			double		fSweepAngleDeg;
		};
	}
}