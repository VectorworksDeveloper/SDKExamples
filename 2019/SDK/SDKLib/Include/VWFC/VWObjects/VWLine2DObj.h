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
		class VWLine2DObj : public VWObject
		{
		public:
							VWLine2DObj(double x1, double y1, double x2, double y2);
							VWLine2DObj(const VWPoint2D& startPt, const VWPoint2D& endPt);
							VWLine2DObj(const VWLine2D& line2DMath);
							VWLine2DObj(MCObjectHandle hLine2D);
							VWLine2DObj(const VWLine2DObj& src);
			virtual			~VWLine2DObj();

			VWLine2DObj&	operator=(const VWLine2DObj& src);

		public:
			void			SetStartPoint(const VWPoint2D& pt);
			void			SetEndPoint(const VWPoint2D& pt);
			void			SetLine(const VWPoint2D& startPt, const VWPoint2D& endPt);
			void			SetLine(const VWLine2D& line2DMath);
			void			SetLine(const VWLine2DObj& line2D);
			VWPoint2D		GetStartPoint() const;
			VWPoint2D		GetEndPoint() const;
			void			GetLine(VWPoint2D& outStartPt, VWPoint2D& outEndPt);
			void			GetLine(VWLine2D& outLine2DMath);

		// tool
		public:
			// Return true if the specified object handle is 2D line
			static bool		IsLine2DObject(MCObjectHandle hObj);
		};
	}
}