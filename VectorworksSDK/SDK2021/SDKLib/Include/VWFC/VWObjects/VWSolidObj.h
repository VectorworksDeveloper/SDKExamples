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
		// ------------------------------------------------------------------------------------
		enum EVWSolidObjOperation
		{
			kVWSolidObjOperation_Add,
			kVWSolidObjOperation_Intersect,
			kVWSolidObjOperation_Subtract,
		};

		// ------------------------------------------------------------------------------------
		class VWSolidObj : public VWObject
		{
		public:
							// operations between two objects
							VWSolidObj(EVWSolidObjOperation operation, MCObjectHandle hObject1, MCObjectHandle hObject2);
							// extrusion constructors
							VWSolidObj(const VWPolygon2D& base, const VWPoint3D& dir);
							VWSolidObj(const VWPolygon3D& base, const VWPoint3D& dir);
							VWSolidObj(const VWPolygon2D& base, const TSTLPolygons2DArray& arrOpenings, const VWPoint3D& dir);
							VWSolidObj(const VWPolygon3D& base, const TSTLPolygons3DArray& arrOpenings, const VWPoint3D& dir);
							// wrapper constructor
							VWSolidObj(MCObjectHandle hSolid);
							// copy constructor
							VWSolidObj(const VWSolidObj& src);
			virtual			~VWSolidObj();

			VWSolidObj&	operator=(const VWSolidObj& src);

		public:

		// tool
		public:
			// Return true if the specified object handle is 2D solid
			static bool		IsSolidObject(MCObjectHandle hObj);

			static void		RunSelfTest();

		protected:
			MCObjectHandle	CreateObject(const VWPolygon2D& base, const TSTLPolygons2DArray& arrOpenings, const VWPoint3D& dir);
		};
	}
}