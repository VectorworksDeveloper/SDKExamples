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
		class VWNURBSCurveObj : public VWObject
		{
		public:
								VWNURBSCurveObj();
								VWNURBSCurveObj(const VWNURBSCurve& curve);
								VWNURBSCurveObj(MCObjectHandle hObj);
								VWNURBSCurveObj(const VWNURBSCurveObj& src);
			virtual				~VWNURBSCurveObj();

			VWNURBSCurveObj&	operator=(const VWNURBSCurveObj& src);

		public:
			bool				GetNURBSCurve(VWNURBSCurve& outCurve);


		// tool
		public:
			// Return true if the specified object handle is Nurbs curve
			static bool		IsNURBSCurveObject(MCObjectHandle hObj);

		private:
			IVWUnknown*			fpAPI;
		};
	}
}