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
		class VWArcObj : public VWObject
		{
		public:
							VWArcObj(const VWPoint2D& center, double dRadius);
							VWArcObj(const VWArc2D& arc);
							VWArcObj(MCObjectHandle hArc);
							VWArcObj(const VWArcObj& src);
			virtual			~VWArcObj();

			VWArcObj&		operator=(const VWArcObj& src);

		public:
			void			SetArc(const VWArc2D& arc);

			void			SetAngles(double dStartAngleDeg, double dSweepAngleDeg);
			VWPoint2D		GetCenter() const;
			void			GetAngles(double& outStartAngleDeg, double& outSweepAngleDeg) const;
			double			GetRadius() const;
			void			GetRadius(double& outRadiusX, double& outRadiusY) const;
			void			GetInfo(VWPoint2D& outCenter, double& outStartAngleDeg, double& outSweepAngleDeg, double& outRadiusX, double& outRadiusY) const;

		// tool
		public:
			// Return true if the specified object handle is 2D locus
			static bool		IsArcObject(MCObjectHandle hObj);
		};
	}
}