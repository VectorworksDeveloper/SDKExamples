//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VectorWorks;
using namespace VWFC::VWObjects;

const OSType kDesignLayerViewportDataTypeTag = 'DLVT'; // Design Layer viewport data

// ---------------------------------------------------------------------------------
VWViewportObj::VWViewportObj(MCObjectHandle hViewport)
{
	VWFC_ASSERT( VWViewportObj::IsViewportObject(hViewport) || VWViewportObj::IsDesignLayerViewportObject(hViewport) );
//	if (!VWViewportObj::IsViewportObject(hViewport) && !VWViewportObj::IsDesignLayerViewportObject(hViewport))
//		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "bad handle type when creating" );
	fhObject = hViewport;
}

VWViewportObj::VWViewportObj(MCObjectHandle parentHandle, bool)
{
	MCObjectHandle hViewport = gSDK->CreateViewport( parentHandle );
	fhObject = hViewport;
	VWFC_ASSERT( VWViewportObj::IsViewportObject(hViewport) || VWViewportObj::IsDesignLayerViewportObject(hViewport) );
}

VWViewportObj::~VWViewportObj()
{
	fhObject		= nil;
}

VWViewportObj& VWViewportObj::operator=(const VWViewportObj& src)
{
	fhObject = src.fhObject;
	return *this;
}

void VWViewportObj::Update()
{
	gSDK->UpdateViewport(fhObject);
}

bool VWViewportObj::GetGroup(EViewportGroupType groupType, MCObjectHandle& outGroupHandle) const
{
	outGroupHandle = gSDK->GetViewportGroup(fhObject, groupType);
	return (outGroupHandle != nil);
}

bool VWViewportObj::AddAnnotationObject(MCObjectHandle annotationHandle)
{
	return gSDK->AddViewportAnnotationObject(fhObject, annotationHandle);
}

bool VWViewportObj::HasCropObject() const
{
	return gSDK->ViewportHasCropObject(fhObject);
}

bool VWViewportObj::GetCropObject(MCObjectHandle& outCropHandle) const
{
	outCropHandle = gSDK->GetViewportCropObject(fhObject);
	return (outCropHandle != nil);
}

bool VWViewportObj::SetCropObject(MCObjectHandle inCropHandle)
{
	return gSDK->SetViewportCropObject(fhObject, inCropHandle);
}

bool VWViewportObj::GetCropVisible() const
{
	Boolean cropVisible;
	TVariableBlock block(cropVisible);
	gSDK->GetObjectVariable(fhObject, ovViewportCropVisible, block);
	block.GetBoolean(cropVisible);
	
	return cropVisible;
}

void VWViewportObj::SetCropVisible(bool cropVisible)
{
	TVariableBlock block((Boolean) cropVisible);
	gSDK->SetObjectVariable(fhObject, ovViewportCropVisible, block);
}

WorldPt VWViewportObj::GetPosition() const
{
	double posX, posY;
	TVariableBlock block(posX);
	gSDK->GetObjectVariable(fhObject, ovViewportXPosition, block);
	block.GetReal64(posX);
	gSDK->GetObjectVariable(fhObject, ovViewportYPosition, block);
	block.GetReal64(posY);
	
	return WorldPt(posX, posY);
}

double VWViewportObj::GetAngleToX() const
{
	double angleX;
	TVariableBlock block(angleX);
	gSDK->GetObjectVariable(fhObject, ovViewportAngleWithXAxis, block);
	block.GetReal64(angleX);
	
	return angleX;
}

TXString VWViewportObj::GetDescription() const
{
	TXString description;
	TVariableBlock block(description);
	gSDK->GetObjectVariable(fhObject, ovViewportDescription, block);
	block.GetTXString(description);

	return description;
}

void VWViewportObj::SetDescription(const TXString & description)
{
	TVariableBlock block(description);
	gSDK->SetObjectVariable(fhObject, ovViewportDescription, block);
}

TXString VWViewportObj::GetLocator() const
{
	TXString locator;
	TVariableBlock block(locator);
	gSDK->GetObjectVariable(fhObject, ovViewportLocator, block);
	block.GetTXString(locator);

	return locator;
}

void VWViewportObj::SetLocator(const TXString & locator)
{
	TVariableBlock block(locator);
	gSDK->SetObjectVariable(fhObject, ovViewportLocator, block);
}

bool VWViewportObj::IsLinked() const
{
	Boolean isLinked;
	TVariableBlock block(isLinked);
	gSDK->GetObjectVariable(fhObject, ovViewportIsLinked, block);
	block.GetBoolean(isLinked);

	return isLinked;
}

bool VWViewportObj::GetLayerHeightIgnored() const
{
	Boolean layerHeightIgnored;
	TVariableBlock block(layerHeightIgnored);
	gSDK->GetObjectVariable(fhObject, ovViewportLayerHeightIgnored, block);
	block.GetBoolean(layerHeightIgnored);

	return layerHeightIgnored;
}

bool VWViewportObj::IsHorizontalSection() const
{
	Boolean			isHorizontalSection;
	TVariableBlock	block( isHorizontalSection );
	gSDK->GetObjectVariable( fhObject, ovViewportIsHorizontalSection, block );
	block.GetBoolean( isHorizontalSection );

	return isHorizontalSection;
}

TProjection VWViewportObj::GetProjectionType() const
{
	Sint16 projectionType;
	TVariableBlock block(projectionType);
	gSDK->GetObjectVariable(fhObject, ovViewportProjectionType, block);
	block.GetSint16(projectionType);
	
	return (TProjection) projectionType;
}

void VWViewportObj::SetProjectionType(TProjection projectionType)
{
	TVariableBlock block((Sint16) projectionType);
	gSDK->SetObjectVariable(fhObject, ovViewportProjectionType, block);
}

double VWViewportObj::GetPerspectiveDistance() const
{
	double distance;
	TVariableBlock block(distance);
	gSDK->GetObjectVariable(fhObject, ovViewportPerspectiveDistance, block);
	block.GetReal64(distance);

	return distance;
}

void VWViewportObj::SetPerspectiveDistance(double distance)
{
	TVariableBlock block(distance);
	gSDK->SetObjectVariable(fhObject, ovViewportPerspectiveDistance, block);
}

bool VWViewportObj::GetProject2D() const
{
	Boolean project2D;
	TVariableBlock block(project2D);
	gSDK->GetObjectVariable(fhObject, ovViewportProject2D, block);
	block.GetBoolean(project2D);
	return project2D;
}

void VWViewportObj::SetProject2D(bool project2D)
{
	TVariableBlock block((Boolean) project2D);
	gSDK->SetObjectVariable(fhObject, ovViewportProject2D, block);
}

TStandardView VWViewportObj::GetViewType() const
{
	short viewType;
	TVariableBlock block(viewType);
	gSDK->GetObjectVariable(fhObject, ovViewportViewType, block);
	block.GetSint16(viewType);
	return (TStandardView) viewType;
}

void VWViewportObj::SetViewType(TStandardView viewType)
{
	TVariableBlock block((short) viewType);
	gSDK->SetObjectVariable(fhObject, ovViewportViewType, block);
}

bool VWViewportObj::HasCamera() const
{
	Boolean hasCamera;
	TVariableBlock block(hasCamera);
	gSDK->GetObjectVariable(fhObject, ovViewportHasCamera, block);
	block.GetBoolean(hasCamera);
	return hasCamera;
}

TRenderMode VWViewportObj::GetRenderType() const
{
	Sint16 renderType;
	TVariableBlock block(renderType);
	gSDK->GetObjectVariable(fhObject, ovViewportRenderType, block);
	block.GetSint16(renderType);

	return (TRenderMode) renderType;
}

void VWViewportObj::SetRenderType(TRenderMode renderType)
{
	TVariableBlock block((Sint16) renderType);
	gSDK->SetObjectVariable(fhObject, ovViewportRenderType, block);
}

TRenderMode VWViewportObj::GetForegroundRenderType() const
{
	Sint16 renderType;
	TVariableBlock block(renderType);
	gSDK->GetObjectVariable(fhObject, ovViewportForegroundRenderType, block);
	block.GetSint16(renderType);

	return (TRenderMode) renderType;
}

void VWViewportObj::SetForegroundRenderType(TRenderMode renderType)
{
	TVariableBlock block((Sint16) renderType);
	gSDK->SetObjectVariable(fhObject, ovViewportForegroundRenderType, block);
}

bool VWViewportObj::IsDirty() const
{
	Boolean isDirty;
	TVariableBlock block(isDirty);
	gSDK->GetObjectVariable(fhObject, ovViewportDirty, block);
	block.GetBoolean(isDirty);
	return isDirty;
}

void VWViewportObj::SetDirty(bool dirty)
{
	TVariableBlock block((Boolean) dirty);
	gSDK->SetObjectVariable(fhObject, ovViewportDirty, block);
}


InternalIndex VWViewportObj::GetRenderBackground() const
{
	InternalIndex background = 0;
	TVariableBlock block((Sint32) background);
	gSDK->GetObjectVariable(fhObject, ovViewportRenderBackground, block);
	block.GetSint32(background);
	return background;
}

void VWViewportObj::SetRenderBackground(InternalIndex background)
{
	TVariableBlock block((Sint32) background);
	gSDK->SetObjectVariable(fhObject, ovViewportRenderBackground, block);
}

bool VWViewportObj::GetAmbientIsOn() const
{
	Boolean isOn;
	TVariableBlock block(isOn);
	gSDK->GetObjectVariable(fhObject, ovViewportAmbientIsOn, block);
	block.GetBoolean(isOn);
	return isOn;
}

void VWViewportObj::SetAmbientIsOn(bool isOn)
{
	TVariableBlock block((Boolean) isOn);
	gSDK->SetObjectVariable(fhObject, ovViewportAmbientIsOn, block);
}

double VWViewportObj::GetAmbientBrightness() const
{
	double brightness;
	TVariableBlock block(brightness);
	gSDK->GetObjectVariable(fhObject, ovViewportAmbientBrightness, block);
	block.GetReal64(brightness);
	return brightness;
}

void VWViewportObj::SetAmbientBrightness(double brightness)
{
	TVariableBlock block(brightness);
	gSDK->SetObjectVariable(fhObject, ovViewportAmbientBrightness, block);
}

WorldPt3 VWViewportObj::GetAmbientColor() const
{
	WorldPt3 color;
	TVariableBlock block(color);
	gSDK->GetObjectVariable(fhObject, ovViewportAmbientColor, block);
	block.GetWorldPt3(color);
	return color;
}

void VWViewportObj::SetAmbientColor(WorldPt3 color)
{
	TVariableBlock block(color);
	gSDK->SetObjectVariable(fhObject, ovViewportAmbientColor, block);
}

InternalIndex VWViewportObj::GetHDRIBackground() const
{
	InternalIndex background = 0;
	TVariableBlock block((Sint32) background);
	gSDK->GetObjectVariable(fhObject, ovViewportHDRIBackground, block);
	block.GetSint32(background);
	return background;
}

bool VWViewportObj::GetGrayAsTransparent() const
{
	Boolean grayAsTransparent;
	TVariableBlock block(grayAsTransparent);
	gSDK->GetObjectVariable(fhObject, ovViewportGrayTransparent, block);
	block.GetBoolean(grayAsTransparent);
	return grayAsTransparent;
}

void VWViewportObj::SetGrayAsTransparent(bool grayAsTransparent)
{
	TVariableBlock block((Boolean) grayAsTransparent);
	gSDK->SetObjectVariable(fhObject, ovViewportGrayTransparent, block);
}

bool VWViewportObj::GetFlipText() const
{
	Boolean flipText;
	TVariableBlock block(flipText);
	gSDK->GetObjectVariable(fhObject, ovViewportFlipText, block);
	block.GetBoolean(flipText);
	return flipText;
}

void VWViewportObj::SetFlipText(bool flipText)
{
	TVariableBlock block((Boolean) flipText);
	gSDK->SetObjectVariable(fhObject, ovViewportFlipText, block);
}

bool VWViewportObj::GetBlackAndWhite() const
{
	Boolean blackAndWhite;
	TVariableBlock block(blackAndWhite);
	gSDK->GetObjectVariable(fhObject, ovViewportBlackAndWhite, block);
	block.GetBoolean(blackAndWhite);
	return blackAndWhite;
}

void VWViewportObj::SetBlackAndWhite(bool blackAndWhite)
{
	TVariableBlock block((Boolean) blackAndWhite);
	gSDK->SetObjectVariable(fhObject, ovViewportBlackAndWhite, block);
}

bool VWViewportObj::GetDisplayPlanar() const
{
	Boolean displayPlanar;
	TVariableBlock block(displayPlanar);
	gSDK->GetObjectVariable(fhObject, ovViewportDisplayPlanar, block);
	block.GetBoolean(displayPlanar);
	return displayPlanar;
}

void VWViewportObj::SetDisplayPlanar(bool displayPlanar)
{
	TVariableBlock block((Boolean) displayPlanar);
	gSDK->SetObjectVariable(fhObject, ovViewportDisplayPlanar, block);
}

InternalIndex VWViewportObj::GetSection2DClass() const
{
	InternalIndex classIndex = 0;
	TVariableBlock block((Sint32) classIndex);
	gSDK->GetObjectVariable(fhObject, ovSectionVP2DAttributeClass, block);
	block.GetSint32(classIndex);
	return classIndex;
}

InternalIndex VWViewportObj::GetSection2DOtherClass() const
{
	InternalIndex classIndex = 0;
	TVariableBlock block((Sint32) classIndex);
	gSDK->GetObjectVariable(fhObject, ovSectionVP2DOtherAttribClass, block);
	block.GetSint32(classIndex);
	return classIndex;
}

InternalIndex VWViewportObj::GetSection3DFillClass() const
{
	InternalIndex classIndex = 0;
	TVariableBlock block((Sint32) classIndex);
	gSDK->GetObjectVariable(fhObject, ovSectionVP3DFillStyleClass, block);
	block.GetSint32(classIndex);
	return classIndex;
}

InternalIndex VWViewportObj::GetSection3DLineClass() const
{
	InternalIndex classIndex = 0;
	TVariableBlock block((Sint32) classIndex);
	gSDK->GetObjectVariable(fhObject, ovSectionVP3DLineStyleClass, block);
	block.GetSint32(classIndex);
	return classIndex;
}

double VWViewportObj::GetScale() const
{
	double scale;
	TVariableBlock block(scale);
	gSDK->GetObjectVariable(fhObject, ovViewportScale, block);
	block.GetReal64(scale);

	return scale;
}

void VWViewportObj::SetScale(double scale)
{
	TVariableBlock block(scale);
	gSDK->SetObjectVariable(fhObject, ovViewportScale, block);
}

double VWViewportObj::GetLineWeightScale() const
{
	double scale;
	TVariableBlock block(scale);
	gSDK->GetObjectVariable(fhObject, ovViewportLineWeightScale, block);
	block.GetReal64(scale);

	return scale;
}

void VWViewportObj::SetLineWeightScale(double scale)
{
	TVariableBlock block(scale);
	gSDK->SetObjectVariable(fhObject, ovViewportLineWeightScale, block);
}

double VWViewportObj::GetArrowheadScale() const
{
	double scale;
	TVariableBlock block(scale);
	gSDK->GetObjectVariable(fhObject, ovViewportArrowheadScale, block);
	block.GetReal64(scale);

	return scale;
}

void VWViewportObj::SetArrowheadScale(double scale)
{
	TVariableBlock block(scale);
	gSDK->SetObjectVariable(fhObject, ovViewportArrowheadScale, block);
}

double VWViewportObj::GetDashedLineScale() const
{
	double scale;
	TVariableBlock block(scale);
	gSDK->GetObjectVariable(fhObject, ovViewportDashedLineScale, block);
	block.GetReal64(scale);

	return scale;
}

void VWViewportObj::SetDashedLineScale(double scale)
{
	TVariableBlock block(scale);
	gSDK->SetObjectVariable(fhObject, ovViewportDashedLineScale, block);
}

double VWViewportObj::GetHatchLineScale() const
{
	double scale;
	TVariableBlock block(scale);
	gSDK->GetObjectVariable(fhObject, ovViewportHatchLineScale, block);
	block.GetReal64(scale);

	return scale;
}

void VWViewportObj::SetHatchLineScale(double scale)
{
	TVariableBlock block(scale);
	gSDK->SetObjectVariable(fhObject, ovViewportHatchLineScale, block);
}

double VWViewportObj::GetDesignTextScale() const
{
	double scale;
	TVariableBlock block(scale);
	gSDK->GetObjectVariable(fhObject, ovViewportDesignTextScale, block);
	block.GetReal64(scale);

	return scale;
}

void VWViewportObj::SetDesignTextScale(double scale)
{
	TVariableBlock block(scale);
	gSDK->SetObjectVariable(fhObject, ovViewportDesignTextScale, block);
}

double VWViewportObj::GetSlashThicknessScale() const
{
	double scale;
	TVariableBlock block(scale);
	gSDK->GetObjectVariable(fhObject, ovViewportSlashThicknessScale, block);
	block.GetReal64(scale);

	return scale;
}

void VWViewportObj::SetSlashThicknessScale(double scale)
{
	TVariableBlock block(scale);
	gSDK->SetObjectVariable(fhObject, ovViewportSlashThicknessScale, block);
}

double VWViewportObj::GetPageSymbolScale() const
{
	double scale;
	TVariableBlock block(scale);
	gSDK->GetObjectVariable(fhObject, ovViewportPageSymbolScale, block);
	block.GetReal64(scale);

	return scale;
}

void VWViewportObj::SetPageSymbolScale( double scale )
{
	TVariableBlock block(scale);
	gSDK->SetObjectVariable(fhObject, ovViewportPageSymbolScale, block);
}

bool VWViewportObj::GetUseDocumentClassVis() const
{
	Boolean useDocumentClassVis;
	TVariableBlock block(useDocumentClassVis);
	gSDK->GetObjectVariable(fhObject, ovViewportUseDocumentClassVis, block);
	block.GetBoolean(useDocumentClassVis);

	return useDocumentClassVis;
}

void VWViewportObj::SetUseDocumentClassVis(bool useDocumentClassVis)
{
	TVariableBlock block((Boolean) useDocumentClassVis);
	gSDK->SetObjectVariable(fhObject, ovViewportUseDocumentClassVis, block);
}

bool VWViewportObj::GetClassVisibility(InternalIndex classIndex, EClassVisibility& outVisibilityType) const
{
	short vis = 0;
	bool result = gSDK->GetViewportClassVisibility(fhObject, classIndex, vis);
	outVisibilityType = (EClassVisibility) vis;
	return result;
}

bool VWViewportObj::SetClassVisibility(InternalIndex classIndex, EClassVisibility inVisibilityType)
{
	return gSDK->SetViewportClassVisibility(fhObject, classIndex, inVisibilityType);
}

size_t VWViewportObj::GetNumClassOverrides() const
{
	return gSDK->GetNumViewportClassOverrides(fhObject);
}

InternalIndex VWViewportObj::GetClassOverrideClass(size_t index) const
{
	return gSDK->GetViewportClassOverrideClass(fhObject, index);
}

bool VWViewportObj::CreateClassOverride(InternalIndex classIndex)
{
	return gSDK->CreateViewportClassOverride(fhObject, classIndex);
}

bool VWViewportObj::GetClassOverride(InternalIndex classIndex, SViewportClassOverride& outOverride) const
{
	return gSDK->GetViewportClassOverride(fhObject, classIndex, outOverride);
}

bool VWViewportObj::SetClassOverride(InternalIndex classIndex, const SViewportClassOverride& inOverride)
{
	return gSDK->SetViewportClassOverride(fhObject, classIndex, inOverride);
}

bool VWViewportObj::RemoveClassOverride(InternalIndex classIndex)
{
	return gSDK->RemoveViewportClassOverride(fhObject, classIndex);
}

size_t VWViewportObj::GetNumLightOverrides() const
{
	return gSDK->GetNumViewportLightOverrides(fhObject);
}

InternalIndex VWViewportObj::GetLightOverrideLight(size_t index) const
{
	return gSDK->GetViewportLightOverrideLight(fhObject, index);
}

bool VWViewportObj::CreateLightOverride(InternalIndex lightIndex)
{
	return gSDK->CreateViewportLightOverride(fhObject, lightIndex);
}

bool VWViewportObj::GetLightOverride(InternalIndex lightIndex, SViewportLightOverride& outOverride) const
{
	return gSDK->GetViewportLightOverride(fhObject, lightIndex, outOverride);
}

bool VWViewportObj::SetLightOverride(InternalIndex lightIndex, const SViewportLightOverride& inOverride)
{
	return gSDK->SetViewportLightOverride(fhObject, lightIndex, inOverride);
}

bool VWViewportObj::RemoveLightOverride(InternalIndex lightIndex)
{
	return gSDK->RemoveViewportLightOverride(fhObject, lightIndex);
}

bool VWViewportObj::GetLayerVisibility(InternalIndex layerIndex, ELayerVisibility& outVisibilityType) const
{
	MCObjectHandle layerHandle = gSDK->InternalIndexToHandle(layerIndex);
	short vis = 0;
	bool result = gSDK->GetViewportLayerVisibility(fhObject, layerHandle, vis);
	outVisibilityType	= (ELayerVisibility)vis;
	return result;
}

bool VWViewportObj::SetLayerVisibility(InternalIndex layerIndex, ELayerVisibility inVisibilityType)
{
	MCObjectHandle layerHandle = gSDK->InternalIndexToHandle(layerIndex);
	return gSDK->SetViewportLayerVisibility(fhObject, layerHandle, inVisibilityType);
}

size_t VWViewportObj::GetNumLayerOverrides() const
{
	return gSDK->GetNumViewportLayerOverrides(fhObject);
}

InternalIndex VWViewportObj::GetLayerOverrideLayer(size_t index) const
{
	return gSDK->GetViewportLayerOverrideLayer(fhObject, index);
}

bool VWViewportObj::CreateLayerOverride(InternalIndex layerIndex)
{
	return gSDK->CreateViewportLayerOverride(fhObject, layerIndex);
}

bool VWViewportObj::GetLayerOverride(InternalIndex layerIndex, SViewportLayerOverride& outOverride) const
{
	return gSDK->GetViewportLayerOverride(fhObject, layerIndex, outOverride);
}

bool VWViewportObj::SetLayerOverride(InternalIndex layerIndex, const SViewportLayerOverride& inOverride)
{
	return gSDK->SetViewportLayerOverride(fhObject, layerIndex, inOverride);
}

bool VWViewportObj::RemoveLayerOverride(InternalIndex layerIndex)
{
	return gSDK->RemoveViewportLayerOverride(fhObject, layerIndex);
}

size_t VWViewportObj::GetNumLayerPropertiesOverrides() const
{
	return gSDK->GetNumViewportLayerPropertiesOverrides(fhObject);
}

InternalIndex VWViewportObj::GetLayerPropertiesOverrideLayer(size_t index) const
{
	return gSDK->GetViewportLayerPropertiesOverrideLayer(fhObject, index);
}

bool VWViewportObj::CreateLayerPropertiesOverride(InternalIndex layerIndex)
{
	return gSDK->CreateViewportLayerPropertiesOverride(fhObject, layerIndex);
}

bool VWViewportObj::GetLayerPropertiesOverride(InternalIndex layerIndex, SViewportLayerPropertiesOverride& outOverride) const
{
	return gSDK->GetViewportLayerPropertiesOverride(fhObject, layerIndex, outOverride);
}

bool VWViewportObj::SetLayerPropertiesOverride(InternalIndex layerIndex, const SViewportLayerPropertiesOverride& inOverride)
{
	return gSDK->SetViewportLayerPropertiesOverride(fhObject, layerIndex, inOverride);
}

bool VWViewportObj::RemoveLayerPropertiesOverride(InternalIndex layerIndex)
{
	return gSDK->RemoveViewportLayerPropertiesOverride(fhObject, layerIndex);
}

size_t VWViewportObj::GetNumLayerStackingOverrides() const
{
	return gSDK->GetNumViewportLayerStackingOverrides(fhObject);
}

InternalIndex VWViewportObj::GetLayerStackingOverrideLayer(size_t index) const
{
	return gSDK->GetViewportLayerStackingOverrideLayer(fhObject, index);
}

bool VWViewportObj::GetLayerStackingOverride(InternalIndex layerIndex, Sint32& outStackingPosition) const
{
	return gSDK->GetViewportLayerStackingOverride(fhObject, layerIndex, outStackingPosition);
}

bool VWViewportObj::SetLayerStackingOverride(InternalIndex layerIndex, Sint32 inStackingPosition)
{
	return gSDK->SetViewportLayerStackingOverride(fhObject, layerIndex, inStackingPosition);
}

bool VWViewportObj::RemoveLayerStackingOverride(InternalIndex layerIndex)
{
	return gSDK->RemoveViewportLayerStackingOverride(fhObject, layerIndex);
}

/*static*/ bool VWViewportObj::IsViewportObject(MCObjectHandle hObj)
{
	return gSDK->GetObjectTypeN(hObj) == kViewportNode;
}

/*static*/ bool VWViewportObj::IsDesignLayerViewportObject(MCObjectHandle hObj)
{
	return gSDK->IsDesignLayerViewport(hObj);
}

/*static*/ bool VWViewportObj::IsDesignLayerSectionViewportObject(MCObjectHandle hObj)
{
	return gSDK->IsDesignLayerSectionViewport(hObj);
}

/*static*/ bool VWViewportObj::IsViewportGroupContainedObject(MCObjectHandle hObj, EViewportGroupType groupType)
{
	return gSDK->IsViewportGroupContainedObject( hObj, groupType );
}

bool VWViewportObj::GetIsDesignLayerSectionViewport(bool& isDesignLayerSVP) const
{
	isDesignLayerSVP = false;
	
	TVariableBlock	block(isDesignLayerSVP);
	bool			res = gSDK->GetObjectVariable(fhObject, ovIsDesignLayerSectionViewport, block);
	
	if(res)
	{
		block.GetBoolean(isDesignLayerSVP);
	}

	return res;
}

//----------------------------------------------------------------------------
bool VWViewportObj::GetTransformMatrix(TransformMatrix& outMat) const
{
	bool outbSuccess = false;
	TVariableBlock varBlock;

	if (gSDK->GetObjectVariable(fhObject, ovViewportTransformMatrix, varBlock)) {
		varBlock.GetTransformMatrix(outMat);
		outbSuccess = true;
	}
	return outbSuccess;
}

//----------------------------------------------------------------------------
bool VWViewportObj::SetTransformMatrix(const TransformMatrix& inMat)
{
	TVariableBlock varBlock(inMat);
	return gSDK->SetObjectVariable(fhObject, ovViewportTransformMatrix, varBlock);
}

//----------------------------------------------------------------------------
bool VWViewportObj::GetViewMatrix(TransformMatrix& outMat) const
{
	bool outbSuccess = false;
	TVariableBlock varBlock;

	if (gSDK->GetObjectVariable(fhObject, ovViewportViewMatrix, varBlock)) {
		varBlock.GetTransformMatrix(outMat);
		outbSuccess = true;
	}
	return outbSuccess;
}

//----------------------------------------------------------------------------
bool VWViewportObj::SetViewMatrix(const TransformMatrix& inMat)
{
	TVariableBlock varBlock(inMat);
	return gSDK->SetObjectVariable(fhObject, ovViewportViewMatrix, varBlock);
}

//----------------------------------------------------------------------------
bool VWViewportObj::GetOperatingTransform(TransformMatrix& outMat) const
{
	bool outbSuccess = false;
	TVariableBlock varBlock;

	if (gSDK->GetObjectVariable(fhObject, ovViewportOperatingTransform, varBlock)) {
		varBlock.GetTransformMatrix(outMat);
		outbSuccess = true;
	}
	return outbSuccess;
}
