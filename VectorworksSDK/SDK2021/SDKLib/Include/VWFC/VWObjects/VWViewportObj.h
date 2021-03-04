//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "VWLayerObj.h"
#include "VWClass.h"

namespace VWFC
{
	using namespace VectorWorks;

	namespace VWObjects
	{
		// ---------------------------------------------------------------------------------
		class VWViewportObj : public VWObject
		{
		public:
								VWViewportObj(MCObjectHandle hViewport);			// wrap an existing viewport

								VWViewportObj(MCObjectHandle parentHandle, bool);	// create a new viewport
																					// the 'bool' is dummy just to differentiate from the other constructor
			virtual				~VWViewportObj();

			VWViewportObj&		operator=(const VWViewportObj& src);

		public:
			void				Update();

			bool				GetGroup(EViewportGroupType groupType, MCObjectHandle& outGroupHandle) const;

			bool				AddAnnotationObject(MCObjectHandle annotationHandle);

			bool				HasCropObject() const;
			bool				GetCropObject(MCObjectHandle& outCropHandle) const;
			bool				SetCropObject(MCObjectHandle inCropHandle);
			bool				GetCropVisible() const;
			void				SetCropVisible(bool cropVisible);

			WorldPt				GetPosition() const;
			double				GetAngleToX() const;	// The angle the viewport subtends with the X-axis in degrees

			TXString			GetDescription() const;
			void				SetDescription(const TXString & description);
			TXString			GetLocator() const;
			void				SetLocator(const TXString & locator);

			bool				IsLinked() const;
			bool				GetLayerHeightIgnored() const;
			bool				IsHorizontalSection() const;

			TProjection			GetProjectionType() const;
			void				SetProjectionType(TProjection projectionType);
			double				GetPerspectiveDistance() const;
			void				SetPerspectiveDistance(double distance);
			bool				GetProject2D() const;
			void				SetProject2D(bool project2D);
			TStandardView		GetViewType() const;
			void				SetViewType(TStandardView viewType);
			bool				HasCamera() const;

			TRenderMode			GetRenderType() const;
			void				SetRenderType(TRenderMode renderType);
			TRenderMode			GetForegroundRenderType() const;
			void				SetForegroundRenderType(TRenderMode renderType);
			bool				IsDirty() const;
			void				SetDirty(bool dirty);

			InternalIndex		GetRenderBackground() const;
			void				SetRenderBackground(InternalIndex background);
			bool				GetAmbientIsOn() const;
			void				SetAmbientIsOn(bool isOn);
			double				GetAmbientBrightness() const;
			void				SetAmbientBrightness(double brightness);
			WorldPt3			GetAmbientColor() const;
			void				SetAmbientColor(WorldPt3 color);
			InternalIndex		GetHDRIBackground() const;
			bool				GetGrayAsTransparent() const;
			void				SetGrayAsTransparent(bool grayAsTransparent);
			bool				GetFlipText() const;
			void				SetFlipText(bool flipText);
			bool				GetBlackAndWhite() const;
			void				SetBlackAndWhite(bool blackAndWhite);
			bool				GetDisplayPlanar() const;
			void				SetDisplayPlanar(bool displayPlanar);

			InternalIndex		GetSection2DClass() const;		// Gets the class which provides attributes for the overall 2D cross-section, 
																// or just the cross-section of structural elements (see GetSection2DOtherClass below)

			InternalIndex		GetSection2DOtherClass() const;	// Gets the class which provides attributes for the 2D cross-sections
																// of non-structural elements

			InternalIndex		GetSection3DFillClass() const;	// Gets the class which provides the fill style of objects beyond the section plane

			InternalIndex		GetSection3DLineClass() const;	// Gets the class which provides the line style of objects beyond the section plane

			double				GetScale() const;
			void				SetScale(double scale);
			double				GetLineWeightScale() const;
			void				SetLineWeightScale(double scale);
			double				GetArrowheadScale() const;
			void				SetArrowheadScale(double scale);
			double				GetDashedLineScale() const;
			void				SetDashedLineScale(double scale);
			double				GetHatchLineScale() const;
			void				SetHatchLineScale(double scale);
			double				GetDesignTextScale() const;
			void				SetDesignTextScale(double scale);
			double				GetSlashThicknessScale() const;
			void				SetSlashThicknessScale(double scale);
			double				GetPageSymbolScale() const;
			void				SetPageSymbolScale(double scale);

			bool				GetUseDocumentClassVis() const;
			void				SetUseDocumentClassVis(bool useDocumentClassVis);
			bool				GetClassVisibility(InternalIndex classIndex, EClassVisibility& outVisibilityType) const;
			bool				SetClassVisibility(InternalIndex classIndex, EClassVisibility inVisibilityType);

			size_t				GetNumClassOverrides() const;
			InternalIndex		GetClassOverrideClass(size_t index) const;
			bool				CreateClassOverride(InternalIndex classIndex);
			bool				GetClassOverride(InternalIndex classIndex, SViewportClassOverride& outOverride) const;
			bool				SetClassOverride(InternalIndex classIndex, const SViewportClassOverride& inOverride);
			bool				RemoveClassOverride(InternalIndex classIndex);

			size_t				GetNumLightOverrides() const;
			InternalIndex		GetLightOverrideLight(size_t index) const;
			bool				CreateLightOverride(InternalIndex lightIndex);
			bool				GetLightOverride(InternalIndex lightIndex, SViewportLightOverride& outOverride) const;
			bool				SetLightOverride(InternalIndex lightIndex, const SViewportLightOverride& inOverride);
			bool				RemoveLightOverride(InternalIndex lightIndex);

			bool				GetLayerVisibility(InternalIndex layerIndex, ELayerVisibility& outVisibilityType) const;
			bool				SetLayerVisibility(InternalIndex layerIndex, ELayerVisibility inVisibilityType);

			size_t				GetNumLayerOverrides() const;
			InternalIndex		GetLayerOverrideLayer(size_t index) const;
			bool				CreateLayerOverride(InternalIndex layerIndex);
			bool				GetLayerOverride(InternalIndex layerIndex, SViewportLayerOverride& outOverride) const;
			bool				SetLayerOverride(InternalIndex layerIndex, const SViewportLayerOverride& inOverride);
			bool				RemoveLayerOverride(InternalIndex layerIndex);

			size_t				GetNumLayerPropertiesOverrides() const;
			InternalIndex		GetLayerPropertiesOverrideLayer(size_t index) const;
			bool				CreateLayerPropertiesOverride(InternalIndex layerIndex);
			bool				GetLayerPropertiesOverride(InternalIndex layerIndex, SViewportLayerPropertiesOverride& outOverride) const;
			bool				SetLayerPropertiesOverride(InternalIndex layerIndex, const SViewportLayerPropertiesOverride& inOverride);
			bool				RemoveLayerPropertiesOverride(InternalIndex layerIndex);

			size_t				GetNumLayerStackingOverrides() const;
			InternalIndex		GetLayerStackingOverrideLayer(size_t index) const;
			bool				GetLayerStackingOverride(InternalIndex layerIndex, Sint32& outStackingPosition) const;
			bool				SetLayerStackingOverride(InternalIndex layerIndex, Sint32 inStackingPosition);
			bool				RemoveLayerStackingOverride(InternalIndex layerIndex);

			bool				GetIsDesignLayerSectionViewport(bool& isDesignLayerSVP) const;

			bool				GetTransformMatrix(TransformMatrix& outMat) const;
			bool				SetTransformMatrix(const TransformMatrix& inMat);

			bool				GetViewMatrix(TransformMatrix& outMat) const;
			bool				SetViewMatrix(const TransformMatrix& inMat);

			bool				GetOperatingTransform(TransformMatrix& outMat) const;
			
		public:
			static bool			IsViewportObject(MCObjectHandle hObj);
			static bool			IsDesignLayerViewportObject(MCObjectHandle hObj);
			static bool			IsDesignLayerSectionViewportObject(MCObjectHandle hObj);
			static bool			IsViewportGroupContainedObject(MCObjectHandle hObj, EViewportGroupType groupType);
		};
	}
}
