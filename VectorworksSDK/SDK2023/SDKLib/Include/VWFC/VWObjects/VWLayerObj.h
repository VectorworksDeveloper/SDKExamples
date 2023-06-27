//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//



#ifndef VECTORWORKS_LAYER_OBJECT__H
#define VECTORWORKS_LAYER_OBJECT__H


#pragma once

namespace VWFC
{
	using namespace Math;
	using namespace Tools;
	namespace VWObjects
	{
		enum ELayerVisibility {
			kLayerVisibilityInvisible			= -1,
			kLayerVisibilityNormal				= 0,
			kLayerVisibilityGrayed				= 2
		};

		enum ELayerProjection {
			kLayerProjOrthogonal				= projectionOrthogonal,
			kLayerProjPerspective				= projectionPerspective,
			kLayerProjCavalierOblique45			= projectionCavalierOblique45,
			kLayerProjCavalierOblique30			= projectionCavalierOblique30,
			kLayerProjCabinetOblique45			= projectionCabinetOblique45,
			kLayerProjCabinetOblique30			= projectionCabinetOblique30,
			kLayerProjPlan						= projectionPlan
		};

		enum ELayerRender {
			kLayerRenderWireFrame				= renderWireFrame,
			kLayerRenderQuick					= renderQuick,
			kLayerRenderSolid					= renderSolid,
			kLayerRenderShadedSolid				= renderShadedSolid,
			kLayerRenderShadedNoLines			= renderShadedNoLines,
			kLayerRenderFinalShaded				= renderFinalShaded,
			kLayerRenderFinalHiddenLine			= renderFinalHiddenLine,
			kLayerRenderDashedHiddenLine		= renderDashedHiddenLine
		};

		// ---------------------------------------------------------------------------------
		class VWLayerObj : public VWGroupObj
		{
		public:
									VWLayerObj(const TXString& layerName);
									VWLayerObj(const TXString& layerName, ELayerType type);
									VWLayerObj(MCObjectHandle hLayer);
									VWLayerObj(const VWLayerObj& src);
			VWLayerObj&				operator=(const VWLayerObj& src);

			virtual					~VWLayerObj();

		public:
			ELayerType				GetLayerType() const;
			double_gs				GetScale() const;
			void					SetScale(double_gs scale);
			Boolean					IsAmbientLightOn() const;
			void					SetAmbientLightOn(Boolean on);
			double_gs				GetAmbientBrightness() const;
			void					SetAmbientBrightness(double_gs brightness);
			CRGBColor				GetAmbientColor() const;
			void					SetAmbientColor(const CRGBColor& rgb);
			ELayerVisibility		GetVisibility() const;
			void					SetVisibility(ELayerVisibility vis);
			VWRectangle2D			GetCropRectangle();

			ELayerProjection		GetProjection() const;
			void					SetProjection(ELayerProjection proj, Boolean bConfirmWithUser, Boolean bDoProgress);
			void					GetPerspectiveInfo(WorldCoord& perspectiveDistance, WorldCoord& clipDistance, VWRectangle2D& clipRect) const;
			ELayerRender			GetRenderMode() const;
			void					SetRenderMode(ELayerRender mode, Boolean bImmediate, Boolean bDoProgress);
			void					GetViewMatrix(VWTransformMatrix& matrix);
			void					SetViewMatrix(const VWTransformMatrix& matrix);

			Sint32					GetSheetPrintDPI() const;
			void					SetSheetPrintDPI(Sint32 dpi);
			VWPoint2D				GetSheetOrigin() const;
			void					SetSheetOrigin(const VWPoint2D& pt);
			double					GetSheetWidht() const;			// value in inches. Use (result * 25.4) to get mm
			void					SetSheetWidht(double value);	// value in inches. Use (mm / 25.4) for value if you have mm
			double					GetSheetHeight() const;			// value in inches. Use (result * 25.4) to get mm
			void					SetSheetHeight(double value);	// value in inches. Use (mm / 25.4) for value if you have mm
			TXString				GetSheetExpandedName();

			WorldCoord				GetElevation() const;
			void					SetElevation(WorldCoord value);
			WorldCoord				GetHeight() const;
			void					SetHeight(WorldCoord height);
			InternalIndex			GetStory() const;

			TXString				GetName();
			TXString				GetDescription();
			void					SetDescription(const TXString& desc);
			TXString				GetNameExpanded();	// name + description

			void					SetThisLayerAsCurrent() const;

			// Tools
		public:
			// Return true if the specified object handle is layer
			static bool				IsLayerObject(MCObjectHandle hObj);

			// Get currenly layer
			static MCObjectHandle	GetCurrentLayer();

			// program variables for layers
			static Boolean			GetProgramVar_UseLayerColor();
			static void				SetProgramVar_UseLayerColor(Boolean use);
			static ELayerOptions	GetProgramVar_LayerOptions();
			static void				SetProgramVar_LayerOptions(ELayerOptions options);
		};
	}
}

#endif // VECTORWORKS_LAYER_OBJECT__H