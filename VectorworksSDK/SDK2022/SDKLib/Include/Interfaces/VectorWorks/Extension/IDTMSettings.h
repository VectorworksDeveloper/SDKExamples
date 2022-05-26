//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ------------------------------------------------------------------------
		enum ETINDisplay {
			kTINDisplayNothing,
			kTINDisplayExistingOnly,
			kTINDisplayProposedOnly,
			kTINDisplayExistingAndProposed,
			kTINDisplayCutAndFill
		};

		// ------------------------------------------------------------------------
		enum E2DTINStyle {
			k2DTINStyle2DContour,
			k2DTINStyle2DContourSmoothed,
			k2DTINStyle2DContourColoredElevations,
			k2DTINStyle2DTriangles,
			k2DTINStyle2DTrianglesColoredSlopes,
			k2DTINStyle2DTriangulatedContours,
			k2DTINStyle2DTriangulatedContoursColoredSlopes
		};

		// ------------------------------------------------------------------------
		enum E3DTINStyle {
			k3DTINStyleMesh,
			k3DTINStyleMeshColoredElev,
			k3DTINStyleMeshColoredSlopes,
			k3DTINStyleGrid,
			k3DTINStyleGridColoredElev,
			k3DTINStyleGridColoredSlope,
			k3DTINStyleVerticalGrid,
			k3DTINStyleContour,
			k3DTINStyleExtrudedContour,
			k3DTINStyleExtContColoredElev,
		};

		// ------------------------------------------------------------------------
		enum EModifiersSource {
			kModifiersSourceAllLayers,
			kModifiersSourceVisibleLayers,
			kModifiersSourceObjectLayer,
			kModifiersSourceSpecifiedLayers
		};

		// ------------------------------------------------------------------------
		struct SDTMCommColor
		{
			Uint8		red;
			Uint8		green;
			Uint8		blue;
		};

		// ------------------------------------------------------------------------
		struct SDTMLineAttributes
		{
			Sint32		lineStyle;
			Uint16		lineWeight;
		};

		// ---------------------------------------------------------------
		struct SDTMMarkerAttributes {
			MarkerType		style;
			Sint8			nAngle;
			double			dSize;
			double			dWidth;
			Sint8			nThicknessBasis;
			double			dThickness;
		};

		// ------------------------------------------------------------------------
		struct SDTMContourData
		{
			SDTMContourData() : fnSize( sizeof( SDTMContourData ) ) {};

			Uint32					fnSize;

			double					fdContourInterval;	// contour interval
			Uint16					fnMajMultiple;		// major multiple
			double					fdDatumElevation;	// datum elevation
			double					fdBaseElevation;	// base elevation
			double					fdMinElevation;		// minimum elevation
			double					fdMaxElevation;		// maximum elevation
			bool					fbExtendMinMax;		// Extend Min Max elevation
			double					fdSmoothInterval;	// smoothing of contours
			double					fdSegmentationLength;//segmentation length
		};

		// ------------------------------------------------------------------------
		struct SDTMVisualData
		{
			SDTMVisualData() : fnSize( sizeof( SDTMVisualData ) ) {};

			Uint32					fnSize;

			ETINDisplay					fnDisplay2D;
			E2DTINStyle					fnStyle2D;
			bool						fbDrawSiteBorder;
			bool						fbShowFlowArrows;
			bool						fbFlowArrowsScaledToSlope;
			double						fdFlowArrowsSpacing;
			bool						fbShowLabes;
			bool						fLabelMinorCountours;
			bool						fbShowLabesAlongLine;

			ETINDisplay					fnDisplay3D;
			E3DTINStyle					fnStyle3D;
			bool						fbShowSkirt;
			bool						fbShow3DContour;
			bool						fbMeshSmoothing;
			double						fdCreaseAngle;
			bool						fbShow3DGrid;
			bool						fb3DGridByDivision;
			double						fd3DGridXSpacing;
			double						fd3DGridYSpacing;
			bool						fb3DGridApproximateSquares;
			bool						fbEnableComponents;
		};

		// ------------------------------------------------------------------------
		struct SDTMGraphicData
		{
			SDTMGraphicData() : fnSize( sizeof( SDTMGraphicData ) ) {};

			Uint32					fnSize;

			TXString				f2DContoursMajorExstClass;
			TXString				f2DContoursMajorPropClass;
			SDTMCommColor			f2DContoursMajorColor;
			SDTMLineAttributes		f2DContoursMajorExstAttr;
			SDTMLineAttributes		f2DContoursMajorPropAttr;

			TXString				f2DContoursMinorExstClass;
			TXString				f2DContoursMinorPropClass;
			SDTMCommColor			f2DContoursMinorColor;
			SDTMLineAttributes		f2DContoursMinorExstAttr;
			SDTMLineAttributes		f2DContoursMinorPropAttr;

			TXString				f2DFlowArrowsExstClass;
			TXString				f2DFlowArrowsPropClass;
			SDTMCommColor			f2DFlowArrowsColor;
			SDTMLineAttributes		f2DFlowArrowsExstAttr;
			SDTMLineAttributes		f2DFlowArrowsPropAttr;
			SDTMMarkerAttributes	f2DFlowArrowsExstMarker;
			SDTMMarkerAttributes	f2DFlowArrowsPropMarker;

			TXString				f2DHullClass;
			SDTMCommColor			f2DHullColor;
			SDTMLineAttributes		f2DHullAttr;

			TXString				f2DTrianglesClass;
			SDTMCommColor			f2DTrianglesColor;
			SDTMLineAttributes		f2DTrianglesAttr;

			TXString				f2DContourLabelsClass;
			SDTMCommColor			f2DContourLabelsColor;

			TXString				f3DContoursMajorClass;
			SDTMCommColor			f3DContoursMajorColor;
			SDTMLineAttributes		f3DContoursMajorAttr;

			TXString				f3DContoursMinorClass;
			SDTMCommColor			f3DContoursMinorColor;
			SDTMLineAttributes		f3DContoursMinorAttr;

			TXString				f3DTrianglesClass;
			SDTMCommColor			f3DTrianglesColor;
			SDTMLineAttributes		f3DTrianglesAttr;

			TXString				f3DGridClass;
			SDTMCommColor			f3DGridColor;
			SDTMLineAttributes		f3DGridAttr;

			TXString				f3DFillClass;
			SDTMCommColor			f3DFillColor;

			TXString				f3DSidesBottomClass;
			SDTMCommColor			f3DSidesBottomColor;

			TXString				f3DCutVolumeClass;
			SDTMCommColor			f3DCutVolumeColor;

			TXString				f3DFillVolumeClass;
			SDTMCommColor			f3DFillVolumeColor;
		};

		// ------------------------------------------------------------------------
		struct SDTMSiteSlopeAnalysis
		{
			SDTMSiteSlopeAnalysis() : fnSize( sizeof( SDTMSiteSlopeAnalysis ) ) {};

			Uint32					fnSize;

			Uint8					fnNumSlopeCategories;
			double					farrSlopes[ 10 ];
			SDTMCommColor			farrSlopeColors[ 10 ];

			SDTMCommColor			fExceedingSlopeColor;
			SDTMCommColor			fMinElevationColor;
			SDTMCommColor			fMaxElevationColor;
		};

		// ------------------------------------------------------------------------
		struct SDTMTexturing
		{
			SDTMTexturing() : fnSize( sizeof( SDTMTexturing ) ) {};

			Uint32					fnSize;

			// texturing
			Uint32					fSurfaceTextureRef;
		};

		// ---------------------------------------------------------------------------
		// {361A3F29-E180-4dde-9544-D84C96086B1A}
		static const VWIID IID_DTMSettings = { 0x361a3f29, 0xe180, 0x4dde, { 0x95, 0x44, 0xd8, 0x4c, 0x96, 0x8, 0x6b, 0x1a } };

		class DYNAMIC_ATTRIBUTE IDTMSettings : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE GetContourData(SDTMContourData& outData) = 0;
			virtual VCOMError VCOM_CALLTYPE SetContourData(const SDTMContourData& data) = 0;
			virtual VCOMError VCOM_CALLTYPE GetVisualData(SDTMVisualData& outData) = 0;
			virtual VCOMError VCOM_CALLTYPE SetVisualData(const SDTMVisualData& data) = 0;
			virtual VCOMError VCOM_CALLTYPE GetGraphicData(SDTMGraphicData& outData) = 0;
			virtual VCOMError VCOM_CALLTYPE SetGraphicData(const SDTMGraphicData& data) = 0;
			virtual VCOMError VCOM_CALLTYPE GetSlopeAnalysisData(SDTMSiteSlopeAnalysis& outData) = 0;
			virtual VCOMError VCOM_CALLTYPE SetSlopeAnalysisData(const SDTMSiteSlopeAnalysis& data) = 0;
			virtual VCOMError VCOM_CALLTYPE GetTexturingData(SDTMTexturing& outData) = 0;
			virtual VCOMError VCOM_CALLTYPE SetTexturingData(const SDTMTexturing& data) = 0;
		};
	}
}
