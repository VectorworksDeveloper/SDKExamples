//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "../Math/IPolyDef.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ------------------------------------------------------------------------
		enum ETINType {
			eTINType_Existing		= 1,
			eTINType_Proposed		= 2
		};

		// ------------------------------------------------------------------------
		struct STINPt
		{
			double		fdX;
			double		fdY;
			double		fdZ;

			Sint32		fTriIndex;
		};

		// ------------------------------------------------------------------------
		struct STINLabel
		{
			double		fX;
			double		fY;
			double		fElevation;
			double		fAngle;

			Sint32		fContourIndex;
			bool		fOnMajorContour;
		};

		// ------------------------------------------------------------------------
		struct STINTri
		{
			// the points are oriented CW
			Sint32			fAPtIndex;
			Sint32			fBPtIndex;
			Sint32			fCPtIndex;

			// each tri is at the tri's point CW oriented
			Sint32			fNabrTri1;
			Sint32			fNabrTri2;
			Sint32			fNabrTri3;

			// store the indexes to 'fPts' for the sorted vertices by Z
			Sint32			fLowTINVertexIndex;
			Sint32			fMidTINVertexIndex;
			Sint32			fHighTINVertexIndex;
		};

		// ------------------------------------------------------------------------
		struct STINContour
		{
								STINContour() : fContourPolygon( VectorWorks::Math::IID_PolyDef ) {}
			virtual				~STINContour() {}

			Math::IPolyDefPtr	fContourPolygon;
			size_t				fContourIndex;
			double				fContourElevation;
			bool				fIsMajor;
		};

		typedef	TXGenericArray< STINContour >	TVWArray_TINContour;

		// ------------------------------------------------------------------------
		typedef	TXGenericArray< double >		TVWArray_Slope;

		struct SPolyAndSlopes
		{
								SPolyAndSlopes() : fPoly( VectorWorks::Math::IID_PolyDef ) {}
			virtual				~SPolyAndSlopes() {}

			Math::IPolyDefPtr	fPoly;
			TVWArray_Slope		fSlopes;
		};

		// ---------------------------------------------------------------------------
		// {7ACCEC1A-0387-4b01-A8A2-DE03C6B01747}
		static const VWIID IID_DTMTIN = { 0x7accec1a, 0x387, 0x4b01, { 0xa8, 0xa2, 0xde, 0x3, 0xc6, 0xb0, 0x17, 0x47 } };
		class DYNAMIC_ATTRIBUTE IDTMTIN : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE GetPointsCount(size_t& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetPoints(STINPt* outArrPoints, size_t& inOutCount) = 0;

			virtual VCOMError VCOM_CALLTYPE GetTrianglesCount(size_t& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetTriangles(STINTri* outArrTris, size_t& inOutCount) = 0;

			virtual VCOMError VCOM_CALLTYPE GetHullPolyPtsCount(size_t& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetHullPolyPts(WorldPt3* outArrPoints, size_t& inOutCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetRisenHullPoly(Math::IPolyDef* pOutRisenHullPoly) = 0;

			virtual VCOMError VCOM_CALLTYPE GetClipPolyPtsCount(size_t& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetClipPolyPts(WorldPt* outArrPoints, size_t& inOutCount) = 0;

			virtual VCOMError VCOM_CALLTYPE GetVisibleContourPolygons(Math::IPolyDefArray** ppOutArrContourPolygons) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetMinElevation(double& outMinElevation) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetZatXY(WorldPt3& inOutPt) const = 0;
			virtual VCOMError VCOM_CALLTYPE	GetZatXY(WorldPt3* outArrPoints, size_t& inOutCount) const = 0;
			virtual VCOMError VCOM_CALLTYPE	RisePolygon(Math::IPolyDef* poly) = 0;

			virtual VCOMError VCOM_CALLTYPE GetRisenClipPoly(Math::IPolyDef* pOutRisenClipPoly) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetBalancingPadPoly(Math::IPolyDef* inPoly2D, Math::IPolyDef** ppOutPoly3D, double batterSlope) = 0;

			virtual VCOMError VCOM_CALLTYPE GetVisibleContourPolygonAt(size_t contourIndex, Math::IPolyDef* pOutContourPoly2D, double& outContourElevation) = 0;

			virtual VCOMError VCOM_CALLTYPE GetLabelsCount(size_t& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetLabels(STINLabel* outArrLabels, size_t& inOutCount) = 0;
			virtual VCOMError VCOM_CALLTYPE SetLabels(STINLabel* inArrLabels, size_t inCount) = 0;

			virtual VCOMError VCOM_CALLTYPE GetVisibleContoursCount(size_t& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE IsMajorVisibleContour(size_t contourIndex, bool& outIsMajor) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetBoundedSurfaceInfo(Math::IPolyDef* inBoundPoly2D, double& outProjArea, double& outExisSurfArea, double& outPropSurfArea) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetBoundedVolumeInfo(Math::IPolyDef* inBoundPoly2D, double& outVolumeExisting, double& outVolumeProposed) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetBoundedVolumeCutNFillInfo(Math::IPolyDef* inBoundPoly2D, double& outVolumeCut, double& outVolumeFill) = 0;

			virtual VCOMError VCOM_CALLTYPE GetVisibleContours(TVWArray_TINContour& outArrContours) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetBalancingPadPoly(const SPolyAndSlopes& inPolyAndSlopes, Math::IPolyDef** ppOutPoly3D) = 0;

			virtual VCOMError VCOM_CALLTYPE	FindPointAtSlope(const WorldPt3& inPt3D, const WorldPt& inDir, double inBatterSlope, double inStep, WorldPt3& outPt3D) const = 0;
			virtual VCOMError VCOM_CALLTYPE	FindPolygonAtSlope(Math::IPolyDef* inPoly3D, double inBatterSlope, double inStep, Math::IPolyDef** ppOutPoly3D) const = 0;
		};
	}
}