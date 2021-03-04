//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	using namespace Math;
	using namespace Tools;
	namespace VWObjects
	{
		class VWObject;

		class VWObjectAttr
		{
			friend class VWObject;
		protected:
								VWObjectAttr();
		public:
								VWObjectAttr(MCObjectHandle h);
								VWObjectAttr(const VWObjectAttr& src);
			virtual				~VWObjectAttr();

			VWObjectAttr&		operator=(const VWObjectAttr& src);

			void				ApplyToObject(MCObjectHandle h) const;

		public:
			void				SetPenNone();
			bool				GetPenNone() const;
			void				SetPenSolid();
			CRGBColor			GetPenForeColor() const;
			CRGBColor			GetPenBackColor() const;
			void				SetPenForeColor(const CRGBColor& color);
			void				SetPenBackColor(const CRGBColor& color);
			bool				GetPenColorByClass() const;
			void				SetPenColorByClass();

			VWPattern			GetPenPattern() const;
			void				SetPenPattern(const VWPattern& pattern);
			void				SetPenPattern(const InternalIndex& dashIndex); // Legacy - Was for use with dash index, changed to use internal index but using VWPattern version is better
			bool				GetPenPatternByClass() const;
			void				SetPenPatternByClass();

			void				SetFillNone();
			bool				GetFillNone() const;
			void				SetFillSolid();
			CRGBColor			GetFillForeColor() const;
			CRGBColor			GetFillBackColor() const;
			void				SetFillForeColor(const CRGBColor& color);
			void				SetFillBackColor(const CRGBColor& color);
			bool				GetFillColorByClass() const;
			void				SetFillColorByClass();

			VWPattern			GetFillPattern() const;
			void				SetFillPattern(const VWPattern& pattern);
			bool				GetFillPatternByClass() const;
			void				SetFillPatternByClass();

			short				GetLineWeightInMils() const;
			void				SetLineWeightInMils(short mils);
			bool				GetLineWeightByClass() const;
			void				SetLineWeightByClass();

			MarkerType			GetMarker(short& size, short& angle, bool& start, bool& end) const;
			void				SetMarker(MarkerType marker,short size, short angle, bool start, bool end);

			ArrowType			GetArrowHeads(bool& starting, bool& ending, short& sizeInPoints);
			ArrowType			GetArrowHeads(bool& starting, bool& ending, double_gs& sizeInMilimeters);
			void				SetArrowHeads(ArrowType type, bool starting, bool ending, short sizeInPoints);
			void				SetArrowHeads(ArrowType type, bool starting, bool ending, double_gs sizeInMilimeters);
			bool				GetArrowByClass() const;
			void				SetArrowByClass();

			//	The functions SetFillOriginPoint, SetFillIAxisEndPoint, and SetFillJAxisEndPoint manipulate the local mapping of the object. If there
			//	is no mapping that has been created for the object, these functions will create it before setting the values.

			VWPoint2D			GetFillOriginPoint() const;
			void				SetFillOriginPoint(const VWPoint2D& pt);

			VWPoint2D			GetFillIAxisEndPoint() const;
			void				SetFillIAxisEndPoint(const VWPoint2D& pt);
			VWPoint2D			GetFillJAxisEndPoint() const;
			void				SetFillJAxisEndPoint(const VWPoint2D& pt);

			void				GetFillPoints(VWPoint2D& originPoint, VWPoint2D& iAxisEndPoint, VWPoint2D& jAxisEndPoint);

			OpacityRef			GetOpacity() const;
			void				SetOpacity(OpacityRef ref);
			bool				GetOpacityByClass() const;
			void				SetOpacityByClass();

			bool				FillSpaceMappingExists() const;

		protected:
			MCObjectHandle		fhObject;
		};
	}
}