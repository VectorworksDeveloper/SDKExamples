//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

// VectorWorks
#include "VectorWorks/ISDK.h"
#include "VectorWorks/IApplication.h"
#include "VectorWorks/IDocument.h"
#include "VectorWorks/IDocumentColorTable.h"
#include "VectorWorks/IDrawPad.h"
#include "VectorWorks/IScreenDrawPad.h"
#include "VectorWorks/IToolInteractiveDraw.h"
#include "VectorWorks/ISubscribe.h"
#include "VectorWorks/IJSONParser.h"


// VectorWorks::Debug
#include "VectorWorks/Debug/IDebugSupport.h"
#include "VectorWorks/Debug/ISystemTest.h"

// VectorWorks::Filing
#include "VectorWorks/Filing/IFileIdentifier.h"
#include "VectorWorks/Filing/IFolderIdentifier.h"
#include "VectorWorks/Filing/IFileChooserDialog.h"
#include "VectorWorks/Filing/IFolderChooserDialog.h"
#include "VectorWorks/Filing/IRawOSFile.h"
#include "VectorWorks/Filing/IStdFile.h"
#include "VectorWorks/Filing/IXMLFile.h"
#include "VectorWorks/Filing/IXMLFileValidator.h"
#include "VectorWorks/Filing/IXMLSAXFile.h"
#include "VectorWorks/Filing/IApplicationFolders.h"
#include "VectorWorks/Filing/IImportExport3DS.h"
#include "VectorWorks/Filing/IImportExportSketchup.h"
#include "VectorWorks/Filing/IPathResolver.h"
#include "VectorWorks/Filing/IImportExportDWG.h"
#include "VectorWorks/Filing/IExportPDF.h"
#include "VectorWorks/Filing/IPublish.h"
#include "VectorWorks/Filing/IZIPFile.h"
#include "VectorWorks/Filing/IImportExportSAT.h"
#include "VectorWorks/Filing/IFileTools.h"
#include "VectorWorks/Filing/INotifyChangesMadeDialog.h"
#include "VectorWorks/Filing/IResourceFile.h"
#include "VectorWorks/Filing/IImportExportOBJ.h"
#include "VectorWorks/Filing/IExportSTL.h"
#include "VectorWorks/Filing/IImportExportRevit.h"
#include "VectorWorks/Filing/IImportExportGDTF.h"
#include "VectorWorks/Filing/IImportExportExcel.h"
#include "VectorWorks/Filing/IExcelFile.h"

// Vectorworks::Animation
#include "VectorWorks/Animation/IMovieWriter.h"

// VectorWorks::Imaging
#include "VectorWorks/Imaging/ICompressedImage.h"
#include "VectorWorks/Imaging/IRawImage.h"
#include "VectorWorks/Imaging/IQRGenerator.h"

// VectorWorks::Objects
#include "VectorWorks/Objects/IVWObject.h"
#include "VectorWorks/Objects/ILine2DObj.h"
#include "VectorWorks/Objects/ILocus2DObj.h"
#include "VectorWorks/Objects/ILocus3DObj.h"
#include "VectorWorks/Objects/IOvalObj.h"
#include "VectorWorks/Objects/IPolygon2DObj.h"
#include "VectorWorks/Objects/IPolygon3DObj.h"
#include "VectorWorks/Objects/IRectangleObj.h"
#include "VectorWorks/Objects/IRoundRectObj.h"

// VectorWorks::Math
#include "VectorWorks/Math/IPolyDef.h"
#include "VectorWorks/Math/IPolyDefArray.h"
#include "VectorWorks/Math/IPoly2DMath.h"
#include "VectorWorks/Math/IPoly2DOperations.h"
#include "VectorWorks/Math/ITrueTypeConv.h"

// VectorWorks::Workspaces
#include "VectorWorks/Workspaces/IWorkspaces.h"

// VectorWorks::Preferences
#include "VectorWorks/Preferences/IUserPreferences.h"

// VectorWorks::UI
#include "VectorWorks/UI/IProgressDialog.h"
#include "VectorWorks/UI/IInfoBar.h"
#include "VectorWorks/UI/IColorMenu.h"
#include "VectorWorks/UI/IMouseCursorManager.h"
#include "VectorWorks/UI/IWebBrowserDlg.h"

// VectorWorks::Extension
#include "VectorWorks/Extension/IDBConnectionString.h"
#include "VectorWorks/Extension/IDBDatabase.h"
#include "VectorWorks/Extension/IDBErrorContext.h"
#include "VectorWorks/Extension/IDBResultSet.h"
#include "VectorWorks/Extension/IDBResultSetMetaData.h"
#include "VectorWorks/Extension/IDBSupport.h"
#include "VectorWorks/Extension/IDBVariant.h"
#include "VectorWorks/Extension/IDocumentShadowSupport.h"
#include "VectorWorks/Extension/IDTMLibrary.h"
#include "VectorWorks/Extension/IDTMModifiersProvider.h"
#include "VectorWorks/Extension/IDTMNotificationListener.h"
#include "VectorWorks/Extension/IDTMSettings.h"
#include "VectorWorks/Extension/IDTMTIN.h"
#include "VectorWorks/Extension/IExtendedProps.h"
#include "VectorWorks/Extension/IExtension.h"
#include "VectorWorks/Extension/IExtensionAnimation.h"
#include "VectorWorks/Extension/IExtensionMenu.h"
#include "VectorWorks/Extension/IExtensionParametric.h"
#include "VectorWorks/Extension/IExtensionTool.h"
#include "VectorWorks/Extension/IExtensionVSFunctions.h"
#include "VectorWorks/Extension/IExtensionChangeSubscriber.h"
#include "VectorWorks/Extension/IExtensionWebPalette.h"
#include "VectorWorks/Extension/IGISSupport.h"
#include "VectorWorks/Extension/IHeliodonDataProvider.h"
#include "VectorWorks/Extension/IIFCSupport.h"
#include "VectorWorks/Extension/ILeaderLineProvider.h"
#include "VectorWorks/Extension/IObjUpdateSupport.h"
#include "VectorWorks/Extension/IProviderProtection.h"
#include "VectorWorks/Extension/IProviderReshape.h"
#include "VectorWorks/Extension/IProviderReshapeLine.h"
#include "VectorWorks/Extension/IProviderReshape3D.h"
#include "VectorWorks/Extension/IProviderCursorHandles.h"
#include "VectorWorks/Extension/IProviderShapePane.h"
#include "VectorWorks/Extension/IProviderSpecialGroups.h"
#include "VectorWorks/Extension/ISendToSurfaceProvider.h"
#include "VectorWorks/Extension/ISpaceObjectSupport.h"
#include "VectorWorks/Extension/IHyperlinkObjectSupport.h"
#include "VectorWorks/Extension/IWorkspaceSupport.h"
#include "VectorWorks/Extension/IProviderSaveCleaner.h"
#include "VectorWorks/Extension/IProviderVisualizationPaletteCamera.h"
#include "VectorWorks/Extension/IRenderworksCameraDataProvider.h"
#include "VectorWorks/Extension/ICloudMenuSupport.h"
#include "VectorWorks/Extension/ISelectSimilarProvider.h"
#include "VectorWorks/Extension/IWorksheetEvalProvider.h"
#include "VectorWorks/Extension/IViewportVisualizationOverride.h"
#include "VectorWorks/Extension/IProviderDataPane.h"
#include "VectorWorks/Extension/IProviderDataRefNumber.h"
#include "VectorWorks/Extension/IIrrigationUnits.h"
#include "VectorWorks/Extension/IResourceManagerContent.h"
#include "VectorWorks/Extension/ITextLinkSupport.h"
#include "VectorWorks/Extension/IDataTagSupport.h"
#include "VectorWorks/Extension/ITitleBlockBorderSupport.h"
#include "VectorWorks/Extension/IProviderAlignObject.h"
#include "VectorWorks/Extension/IProviderCustomReshape.h"
#include "VectorWorks/Extension/IDataTagProvider.h"
#include "VectorWorks/Extension/IConnectCADTextLinkSupport.h"
#include "VectorWorks/Extension/IProviderPDFHyperlink.h"
#include "VectorWorks/Extension/IObjectShapePaneProvider.h"
#include "VectorWorks/Extension/IProviderMaterialValues.h"

// VectorWorks::VectorScript
#include "VectorWorks/Scripting/IScriptEditor.h"
#include "VectorWorks/Scripting/IVectorScriptEngine.h"
#include "VectorWorks/Scripting/IPythonWrapper.h"
#include "VectorWorks/Scripting/IPythonScriptEngine.h"

// VectorWorks::EnergyAnalysis
#include "VectorWorks/EnergyAnalysis/IEnergyUnits.h"
#include "VectorWorks/EnergyAnalysis/IEnergyBuildingElementRoof.h"
#include "VectorWorks/EnergyAnalysis/IEnergyBuildingElementSlab.h"
#include "VectorWorks/EnergyAnalysis/IEnergyBuildingElementWall.h"
#include "VectorWorks/EnergyAnalysis/IEnergyBuildingElementWinDoor.h"
#include "VectorWorks/EnergyAnalysis/IEnergyBuildingElementWinDoorEx.h"
#include "VectorWorks/EnergyAnalysis/IEnergyBuildingElementCurtainWall.h"
#include "VectorWorks/EnergyAnalysis/IEnergySpace.h"
#include "VectorWorks/EnergyAnalysis/IEnergyThermalBridges.h"
#include "VectorWorks/EnergyAnalysis/IExternalSystemData.h"
#include "VectorWorks/EnergyAnalysis/IEnergySystemObject.h"
#include "VectorWorks/EnergyAnalysis/IEnergyBuildingElementOther.h"
#include "VectorWorks/EnergyAnalysis/IEnergosTraverser.h"
#include "VectorWorks/EnergyAnalysis/IEnergyBuildingMaterial.h"

// VectorWorks::MigrationManager
#include "VectorWorks/MigrationManager/IMigrationManagerSupport.h"

// VectorWorks::TrussAnalysis
#include "VectorWorks/TrussAnalysis/ITrussAnalysis.h"
#include "VectorWorks/TrussAnalysis/ILoadInfoDataSupport.h"
#include "VectorWorks/TrussAnalysis/IMassForceUnits.h"
#include "VectorWorks/TrussAnalysis/IProviderRiggingObject.h"
#include "VectorWorks/TrussAnalysis/ICableInterface.h"

// ComputerWorks Plug-Ins that are not part of Vectorworks International version [SB Sep 29, 2017]

#include "VectorWorks/Extension/IWindowCWSupport.h" /* Must be included BEFORE IDoorCWSupport.h. */
#include "VectorWorks/Extension/IDoorCWSupport.h"

#include "VectorWorks/Extension/ICustomUnitsCWSupport.h"

// VectorWorks::Units
#include "VectorWorks/Units/IUnits.h"
