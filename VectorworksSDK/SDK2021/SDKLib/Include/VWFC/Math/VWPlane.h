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
		class VWPlane
		{
		public:
			// construction
						VWPlane();
						VWPlane(const VWPoint3D& planeLocation, const VWPoint3D& planeNormal);
						VWPlane(const VWPlane& src);
			virtual		~VWPlane();

			VWPlane&	operator=(const VWPlane& src);

		public:
			void		SetPlane(const VWPoint3D& planeLocation, const VWPoint3D& planeNormal);
			VWPoint3D	GetLocation();
			VWPoint3D	GetNormal();

			bool		IntersectPWithVector(const VWPoint3D& pt, const VWPoint3D& dir, VWPoint3D& outInters);

		private:
			IVWUnknown*	fp;
			VWPoint3D	fPlaneLocation;
			VWPoint3D	fPlaneNormal;
		};
	}
}