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
		class VWExtrudeObj : public VWObject
		{
		public:
							VWExtrudeObj(const VWPolygon2D& base, double dThickness);
							VWExtrudeObj(const VWPolygon2D& base, double dBaseElevation, double dThickness);
							VWExtrudeObj(const VWPolygon3D& base, double dThickness);
							VWExtrudeObj(MCObjectHandle hBasePoly2D, double dBaseElevation, double dThickness); // hBasePoly2D will be inserted inside the extrude
							VWExtrudeObj(MCObjectHandle hBasePoly2D, const VWPoint3D& start, const VWPoint3D& end); 
							VWExtrudeObj(MCObjectHandle hBasePoly2D, const VWPoint3D& start, const VWPoint3D& end, const VWPoint3D& up); 
							VWExtrudeObj(MCObjectHandle hExtrude);
							VWExtrudeObj(const VWExtrudeObj& src);
			virtual			~VWExtrudeObj();

			VWExtrudeObj&	operator=(const VWExtrudeObj& src);

		public:
			void			GetExtrudeValues(double& outBaseElev, double& outThickness) const;
			void			SetExtrudeValues(double baseElev, double thickness);
			double			GetBaseElevation() const;
			void			SetBaseElevation(double baseElev);
			double			GetThickness() const;
			void			SetThickness(double thickness);

			void			AddHoleObject(const VWPolygon2D& poly);
			void			AddHoleObject(MCObjectHandle hObject);
			MCObjectHandle	GetBaseObject() const;

		// tool
		public:
			// Return true if the specified object handle is 2D line
			static bool		IsExtrudeObject(MCObjectHandle hObj);

		protected:
			bool				fbDeleteBasePoly;
			VWPolygon2DObj*		fpBasePolyObj;
		};
	}
}