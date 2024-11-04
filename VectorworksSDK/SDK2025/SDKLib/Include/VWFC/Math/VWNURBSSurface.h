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
		class VWBodyEdge;
		class VWNURBSSurface
		{
			friend class VWBodyFace;
		public:
			// construction
								VWNURBSSurface();
								VWNURBSSurface(const VWNURBSSurface& src);
			virtual				~VWNURBSSurface();

			VWNURBSSurface&		operator=(const VWNURBSSurface& src);

			bool				IsValid() const;

		public:
			void				GetUVBox(VWPoint2D& UVMin, VWPoint2D& UVMax);

			VWNURBSCurve		GetIsoCurveU(double param);
			VWNURBSCurve		GetIsoCurveV(double param);

			bool				GetPointsOnUVGrid(TDoubleArray& Uparams, TDoubleArray& Vparams, TVWPoint3DArray& points);
			bool				GetPointsOnUVGrid(Sint32 UDivs, Sint32 VDivs, double UOffsetParam, double VOffsetParam, TVWPoint3DArray& points);
			bool				GetEvenlySpacedPointsArc(Sint32 UDivs, Sint32 VDivs, double UOffsetDist, double VOffsetDist, TVWPoint3DArray& points);
			bool				GetEvenlySpacedPointsChord(Sint32 UDivs, Sint32 VDivs, double UOffsetDist, double VOffsetDist, TVWPoint3DArray& points);


			Sint32					GetVWNURBSSurfaceID();


		protected:
								VWNURBSSurface(Sint32 surfaceID);
		private:
			IVWUnknown*	fp;
			IVWUnknown* fpAPI;
			Sint32			fNURBSSurfaceID;
			VWPoint2D	fUVBoundsMin;
			VWPoint2D	fUVBoundsMax;
		};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}
		
	

