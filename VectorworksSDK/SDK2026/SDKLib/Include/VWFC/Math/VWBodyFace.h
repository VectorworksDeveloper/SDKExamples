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
		class VWBodyFace
		{
			friend class VWBody;
		public:
			// construction
							VWBodyFace();
							VWBodyFace(const VWBodyFace& src);
			virtual			~VWBodyFace();

			VWBodyFace&		operator=(const VWBodyFace& src);

			bool			IsValid() const;

		public:
			bool			GetPlanarSurface(VWPoint3D& outPlaneLocation, VWPoint3D& outPlaneNormal);
			bool			GetPlanarSurface(VWPlane& out);

			void			GetUVBox(VWPoint2D& UVMin, VWPoint2D& UVMax);

			VWNURBSCurve	GetIsoCurveU(double param);
			VWNURBSCurve	GetIsoCurveV(double param);

			VWNURBSSurface	GetSurface();
			VWBody			GetBody() const;

			Sint32			GetBodyFaceID() const;

		protected:
							VWBodyFace(Sint32 faceID);

			
			void			SetBodyFaceID(Sint32 id);

		private:
			IVWUnknown*	fp;
			Sint32			fBodyFaceID;
		};
	}
}