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
		enum class ESiteModelLabelUnit {
			DocUnits,
			FeetAndInches,
			Inches,
			Feet,
			Yards,
			Miles,
			Micrometres,
			Millimetres,
			Centimetres,
			Metres,
			Kilometres,
			Degrees
		};

		// ------------------------------------------------------------------------
		struct SDTMCommColor
		{
			Uint8		red = 0;
			Uint8		green = 0;
			Uint8		blue = 0;
		};

		// ------------------------------------------------------------------------
		struct SDTMLineAttributes
		{
			Sint32		lineStyle = 0;
			Uint16		lineWeight = 0;
		};

		// ---------------------------------------------------------------
		struct SDTMMarkerAttributes {
			MarkerType		style = 0;
			Sint8			nAngle = 0;
			double			dSize = 0;
			double			dWidth = 0;
			Sint8			nThicknessBasis = 0;
			double			dThickness = 0;
		};

		// ------------------------------------------------------------------------
		struct SDTMContourData
		{
			SDTMContourData() {};

			Uint32					fnSize = sizeof(SDTMContourData);

			double					fdContourInterval = 0;	// contour interval
			Uint16					fnMajMultiple = 0;		// major multiple
			double					fdDatumElevation = 0;	// datum elevation
			double					fdBaseElevation = 0;	// base elevation
			double					fdMinElevation = 0;		// minimum elevation
			double					fdMaxElevation = 0;		// maximum elevation
			bool					fbExtendMinMax = false;	// Extend Min Max elevation
			double					fdSmoothInterval = 0;	// smoothing of contours
			double					fdSegmentationLength = 0;//segmentation length
		};

		// ------------------------------------------------------------------------
		struct SDTMVisualData
		{
			SDTMVisualData() {};

			Uint32					fnSize = sizeof(SDTMVisualData);

			ETINDisplay					fnDisplay2D = ETINDisplay::kTINDisplayNothing;
			E2DTINStyle					fnStyle2D = E2DTINStyle::k2DTINStyle2DContour;
			bool						fbDrawSiteBorder = false;
			bool						fbShowFlowArrows = false;
			bool						fbFlowArrowsScaledToSlope = false;
			double						fdFlowArrowsSpacing = 0;
			bool						fbShowLabes = false;
			bool						fLabelMinorCountours = false;
			bool						fbShowLabesAlongLine = false;

			ETINDisplay					fnDisplay3D = ETINDisplay::kTINDisplayNothing;;
			E3DTINStyle					fnStyle3D = E3DTINStyle::k3DTINStyleMesh;
			bool						fbShowSkirt = false;
			bool						fbShow3DContour = false;
			bool						fbMeshSmoothing = false;
			double						fdCreaseAngle = 0;
			bool						fbShow3DGrid = false;
			bool						fb3DGridByDivision = false;
			double						fd3DGridXSpacing = 0;
			double						fd3DGridYSpacing = 0;
			bool						fb3DGridApproximateSquares = false;
			bool						fbEnableComponents = false;
		};

		// ------------------------------------------------------------------------
		struct SDTMGraphicData
		{
			SDTMGraphicData() {};

			Uint32					fnSize = sizeof(SDTMGraphicData);

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

			// new in VW2023.
			SDTMCommColor			f2DContoursMajorPropColor;
			SDTMCommColor			f2DContoursMinorPropColor;
			SDTMCommColor			f2DFlowArrowsPropColor;
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
