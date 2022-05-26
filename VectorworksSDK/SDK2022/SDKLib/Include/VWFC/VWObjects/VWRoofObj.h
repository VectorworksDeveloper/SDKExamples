//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		// --------------------------------------------------------------------------------
		class VWRoofObj : public VWObject
		{
		public:
								VWRoofObj(MCObjectHandle hRoof);
			virtual				~VWRoofObj();

								VWRoofObj(const VWRoofObj& );
								VWRoofObj& operator=(const VWRoofObj&);

		public:
			const VWPolygon2D&	GetRoofPoly() const;
		
			size_t				GetFacesCount() const;
			MCObjectHandle		GetFaceAt(size_t at);
			bool				GetIsFaceDormer(size_t at);
			bool				IsRoofFaceDormer(MCObjectHandle hRoofFace);

			bool				GetGableWall() const;
			double				GetBearingInset() const;
			double				GetRoofThick() const;
			ERoofMiterType		GetMiterType() const;
			double				GetVertMiter() const;
			ERoofMiterType		GetSkylightMiterType() const;

		// tool
		public:
			// Return true if the specified object handle is roof object
			static bool			IsRoofObject(MCObjectHandle hObj);

		private:
			// VW handle to the roof
			TMCObjectHandlesSTLArray	fArrFaces;
			VWPolygon2D					fEdgesPolygon;

			// fbGenGableWall: Set to true to have a wall created at gable ends of the roof.
			//                 Otherwise no object will be inserted.
			Boolean					fbGenGableWall;
			// fdBearingInset: is where the weight of the roof rests on the wall.
			//				   This is an inset from the defining edge of the roof plan.
			double					fdBearingInset;
			double					fdRoofThick;
			ERoofMiterType			fMiterType;
			ERoofMiterType			fSkylightMiterType;
			// fdVertMiter: This is used only with the double miter type;
			//				it specifies the vertical length of the miter cut.
			double					fdVertMiter;
		};
	}
}
