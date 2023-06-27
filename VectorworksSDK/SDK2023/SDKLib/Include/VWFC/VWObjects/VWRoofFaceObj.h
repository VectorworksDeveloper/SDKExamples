//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_ROOF_FACE_OBJECT__H
#define VECTORWORKS_ROOF_FACE_OBJECT__H

#pragma once

namespace VWFC
{
	using namespace Math;

	namespace VWObjects
	{
		// --------------------------------------------------------------------------------
		enum ERoofFaceType
		{
			kRoofFaceType_Unknown		= 0,
			kRoofFaceType_Roof			= 1,
			kRoofFaceType_Floor			= 2,
			kRoofFaceType_Column		= 3
		};

		// --------------------------------------------------------------------------------
		enum ERoofMiterType
		{
			kRoofMiterTypeNone			= 0,
			kRoofMiterTypeVertical		= 1,
			kRoofMiterTypeHorizontal	= 2,
			kRoofMiterTypeDouble		= 3,
			kRoofMiterTypeSquare		= 4
		};

		class VWRoofObj;
		// --------------------------------------------------------------------------------
		class VWRoofFaceObj : public VWObject
		{
		public:
									VWRoofFaceObj(ERoofFaceType newFaceType, const VWPolygon2D& poly);
									VWRoofFaceObj(ERoofFaceType newFaceType, const VWPolygon2D& poly, double z, const VWPoint2D& upSlopeDir, double rise, double run);
									VWRoofFaceObj(ERoofFaceType newFaceType, const VWPolygon2D& poly, const VWTransformMatrix& transform);
									VWRoofFaceObj(MCObjectHandle hRoofFace);
			virtual					~VWRoofFaceObj();

									VWRoofFaceObj(const VWRoofFaceObj& );
			VWRoofFaceObj&			operator=(const VWRoofFaceObj& );

			MCObjectHandle			GetParentRoof() const;
			const VWPolygon2D&		GetPolygon() const;
			void					SetPolygon(const VWPolygon2D& poly);
			const VWPolygon3D&		GetPolygon3D() const;
			void					SetAsDormerRoofFace(bool isDormerFace);
			void					ModifyForDormer(const VWPoint2D& pt1, const VWPoint2D& pt2);

			VWPoint3D				GetBearingStartPos() const;
			VWPoint3D				GetBearingEndPos() const;
			void					GetRotationTransform(VWTransformMatrix& mat) const;
			void					SetRotationTransform(const VWTransformMatrix& mat);

			double					GetThickness() const;
			void					SetThickness(double value);

		public:

			// each two points make one segment
			void					GetIntersectionSegments(const VWPoint2D& pt, const VWPoint2D& dir, TSTLPoints2DArray& /*out*/ arrPts) const;

			const TSTLPolygons2DArray&	GetOpeningPolygons() const;
			void						AddOpeningPolygon(const VWPolygon2D& poly);
			void						ClearOpeningPolygons();

			// return true if the given line (pt1, pt2) lies on a side of this roof face
			// side of roof face are those lines which intersect with slab line
			bool					IsLyingOnSide(const VWPoint2D& pt1, const VWPoint2D& pt2) const;
			// return true if the given roof face is touching this on it's edge line
			// side of roof face are those lines which intersect with slab line
			bool					IsLyingOnSide(const VWRoofFaceObj* pFace) const;

			// return true if the specified point lies on a gable end
			bool					IsOnGableEnd(const VWPoint2D& pt);

		// tool
		public:
			// Return true if the specified object handle is roof face object
			static bool				IsRoofFaceObject(MCObjectHandle hObj);
			static bool				IsRoofFaceObjectN(MCObjectHandle hRoofFace);

		protected:
			void					InitGeometry();
			void					CreateOpening(MCObjectHandle hPoly, VWPolygon2D* pPoly);
			void					CheckAndCollectOpenings(MCObjectHandle hPolyGroup);
			void					CalculateOverhang();
			void					CalculateSlabAndBearingPoints();
			void					EnsureDirectionOfReferencePoints();

		private:
			MCObjectHandle			fhParentRoof;
			// the roof face polygon
			VWPolygon2D				fRoofFacePolygon;
			VWPolygon3D				fRoofFacePolygon3D;
			// cutting openings in the poly
			// these are modified openings as rectangular secions used when creating the rafters
			// these are the bounding box of the openings
			TSTLPolygons2DArray		farrOpenings;

			VWLine2D				fSlabRoofLine;

		public:
			ERoofFaceType						fSlabType;
			// the thickness
			double								fSlabThickness;
			// the z elevation
			double								fSlabHeigh;
			// bearing point (the point on the referenced poly)
			// point on the outside of the walls on which the roof is standing
			// these are the reference points for the roof (these doesn't move when the roof thickness is changed)
			VWLine2D							fBearingLine;
			// points of the roof axis (bearing point + bearing inset)
			VWLine2D							fInsetLine;
			// upslope director vector
			VWPoint2D							fUpSlopeDir;
			// a point on the upslope side of the roof
			VWPoint2D							fSlabRoofUpslopePt;
			// the rise over a given distance.  Use with the run to calculate a slope
			double								fSlabRoofRise;
			// the run over a given distance.  Use with the rise to calculate a slope
			double								fSlabRoofRun;
			// mitter type
			ERoofMiterType						fSlabRoofMiterType;
			// the percentage of a double miter which is vertical (1 is a vertical miter and 0 is a horizontal)
			double								fSlabRoofDoubleMiterRatio;
			// calculated overhang
			double								fdOverhang;
			bool								fbIsCCW;
		};
	}
}

#endif // VECTORWORKS_ROOF_FACE_OBJECT__H