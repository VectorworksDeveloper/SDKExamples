//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

//////////////////////////////////////////////////////////////////////////////////////////
// Host information about which program is currently running

#ifndef GSEBUILDTYPES
#define GSEBUILDTYPES
const short kMiniCad 			= 1;
const short kBlueprint 			= 2;
#endif

//////////////////////////////////////////////////////////////////////////////////////////

#define MUST_PROMOTE_SCALARS 0


typedef Sint8				lbyte_t;
typedef Uint8				lubyte_t;
typedef Sint16				lshort_t;
typedef Uint16				lushort_t;
	

typedef lbyte_t				lboolean_t;

#if _WINDOWS
	typedef Real64			callback_double_param;
	typedef Real64			CBDouble_param;
	typedef const Real64  &CBWorldCoord_param;	// JAK 10/15/99 еееееееееееееееееееееееееееееееееееееееее
#else
	// Callbacks always take FP params by reference because
	// Mixed Mode can't convert stack based to register based.
	typedef const Real64  &callback_double_param;
	typedef const Real64  &CBDouble_param;
	typedef const Real64  &CBWorldCoord_param;	// JAK 10/15/99 еееееееееееееееееееееееееееееееееееееееее
#endif



typedef Sint8				CBSignedByte;
typedef Uint8				CBUnsignedByte;
typedef Sint16				CBSignedShort;
typedef Uint16				CBUnsignedShort;
typedef CBSignedByte		CBBoolean;
typedef Real64				CBDouble;

// ##################################################################################
// These constants are part of the GS_ API vtable implementation
// made obsolete by VCOM and still here for legacy support

// kcbMaximumCallbackDispatchID is the maximum ID contained in the database
// some slots in the array may be empty because functions
// have been defined and assigned an ID, but not implemented
// 
// the dispatch array is indexed by these constants, which range
// from 0 to 1468. The array must be sized to acommodate
// at least kcbMaximumCallbackDispatchID + 1 function pointers.
// 
// there are currently 1244 SDK functions implemented

#define kcbMaximumCallbackDispatchID 1468L



///////////////////////////////////////////
//  Attributes (Class)
///////////////////////////////////////////


	#define kcbGetClassBeginningMarker 1215L
	#define kcbGetClassEndMarker 1216L
	#define kcbGetClColor 400L
	#define kcbGetClFillPat 401L
	#define kcbGetClLineWeight 403L
	#define kcbGetClMarker 404L
	#define kcbGetClPenPat 405L
	#define kcbGetClUseGraphic 408L
	#define kcbGetClVisibility 963L
	#define kcbGetVPClassFillStyle 1240L
	#define kcbSetClassBeginningMarker 1213L
	#define kcbSetClassEndMarker 1214L
	#define kcbSetClColor 410L
	#define kcbSetClFillPat 411L
	#define kcbSetClLineWeight 413L
	#define kcbSetClMarker 414L
	#define kcbSetClPenPat 415L
	#define kcbSetClUseGraphic 418L
	#define kcbSetClVisibility 964L
	#define kcbVPClassHasOverride 1239L


///////////////////////////////////////////
//  Attributes (Default)
///////////////////////////////////////////


	#define kcbDeleteAllDLComponents 1296L
	#define kcbDeleteDLComponent 1284L
	#define kcbGetDefaultArrowByClass 388L
	#define kcbGetDefaultArrowHeads 114L
	#define kcbGetDefaultArrowHeadsN 656L
	#define kcbGetDefaultBeginningMarker 1205L
	#define kcbGetDefaultClass 98L
	#define kcbGetDefaultColors 90L
	#define kcbGetDefaultEndMarker 1207L
	#define kcbGetDefaultFColorsByClass 389L
	#define kcbGetDefaultFillPat 92L
	#define kcbGetDefaultFPatByClass 390L
	#define kcbGetDefaultHatch 763L
	#define kcbGetDefaultLineWeight 94L
	#define kcbGetDefaultLWByClass 391L
	#define kcbGetDefaultPColorsByClass 392L
	#define kcbGetDefaultPenPat 96L
	#define kcbGetDefaultPPatByClass 393L
	#define kcbGetDLComponentClass 1413L
	#define kcbGetDLComponentFill 1292L
	#define kcbGetDLComponentFillColors 1415L
	#define kcbGetDLComponentName 1411L
	#define kcbGetDLComponentPenColors 1417L
	#define kcbGetDLComponentPenStyles 1290L
	#define kcbGetDLComponentPenWeights 1288L
	#define kcbGetDLComponentUseFillClassAttr 1423L
	#define kcbGetDLComponentUsePenClassAttr 1425L
	#define kcbGetDLComponentWidth 1285L
	#define kcbGetDLControlOffset 1297L
	#define kcbGetDLOptions 1301L
	#define kcbGetDLSeparation 1299L
	#define kcbGetDocumentDefaultSketchStyle 976L
	#define kcbGetNumberOfDLComponents 1294L
	#define kcbGetObjectInternalIndex 1267L
	#define kcbGetProgramVariable 290L
	#define kcbGetWallPrefStyle 1095L
	#define kcbGetWallStyle 1096L
	#define kcbInsertNewDLComponent 1282L
	#define kcbSetDefaultArrowByClass 394L
	#define kcbSetDefaultArrowHeads 115L
	#define kcbSetDefaultArrowHeadsN 657L
	#define kcbSetDefaultBeginningMarker 1206L
	#define kcbSetDefaultClass 99L
	#define kcbSetDefaultColors 91L
	#define kcbSetDefaultEndMarker 1208L
	#define kcbSetDefaultFColorsByClass 395L
	#define kcbSetDefaultFillPat 93L
	#define kcbSetDefaultFPatByClass 396L
	#define kcbSetDefaultHatch 764L
	#define kcbSetDefaultLineWeight 95L
	#define kcbSetDefaultLWByClass 397L
	#define kcbSetDefaultPColorsByClass 398L
	#define kcbSetDefaultPenPat 97L
	#define kcbSetDefaultPPatByClass 399L
	#define kcbSetDefaultWallThickness 117L
	#define kcbSetDLComponentClass 1414L
	#define kcbSetDLComponentFill 1293L
	#define kcbSetDLComponentFillColors 1416L
	#define kcbSetDLComponentName 1412L
	#define kcbSetDLComponentPenColors 1418L
	#define kcbSetDLComponentPenStyles 1291L
	#define kcbSetDLComponentPenWeights 1289L
	#define kcbSetDLComponentUseFillClassAttr 1424L
	#define kcbSetDLComponentUsePenClassAttr 1426L
	#define kcbSetDLComponentWidth 1286L
	#define kcbSetDLControlOffset 1298L
	#define kcbSetDLOptions 1302L
	#define kcbSetDLSeparation 1300L
	#define kcbSetDocumentDefaultSketchStyle 975L
	#define kcbSetProgramVariable 291L
	#define kcbSetWallPrefStyle 1087L
	#define kcbWrapGetDefaultWallThickness 572L


///////////////////////////////////////////
//  Attributes (Geometric)
///////////////////////////////////////////


	#define kcbAdd3DVertex 66L
	#define kcbAddVertex 12L
	#define kcbCalcAreaN 282L
	#define kcbCalcPerimN 283L
	#define kcbCalcSurfaceArea 475L
	#define kcbCalcVolume 474L
	#define kcbCentroid3D 847L
	#define kcbCountVertices 72L
	#define kcbCreateSkylight 519L
	#define kcbDeleteVertex 89L
	#define kcbForEach3DPointInObject 677L
	#define kcbForEachPolyEdge 769L
	#define kcbGet3DVertex 65L
	#define kcbGetArcInfoN 224L
	#define kcbGetBatAttributes 533L
	#define kcbGetControlVertex 217L
	#define kcbGetDormerAttributes 547L
	#define kcbGetEndPoints 120L
	#define kcbGetEntityMatrix 297L
	#define kcbGetExtrudeValues 299L
	#define kcbGetGableAttributes 524L
	#define kcbGetHipAttributes 530L
	#define kcbGetLocus3DPosition 316L
	#define kcbGetLocusPosition 315L
	#define kcbGetMarkerPolys 1459L
	#define kcbGetNumRoofElements 540L
	#define kcbGetObjectBoundingBoxVerts 1254L
	#define kcbGetObjectBounds 0L
	#define kcbGetObjectCube 327L
	#define kcbGetPolyDirection 1237L
	#define kcbGetPolyShapeClose 14L
	#define kcbGetQArcQuadrant 222L
	#define kcbGetRoofAttributes 512L
	#define kcbGetRoofElementType 675L
	#define kcbGetRRectDiameters 218L
	#define kcbGetShedAttributes 527L
	#define kcbGetSkylight 545L
	#define kcbGetSweepAnglesN 302L
	#define kcbGetTrapeziumAttributes 521L
	#define kcbGetVertex 68L
	#define kcbInsert3DVertex 88L
	#define kcbInsertVertex 25L
	#define kcbMoments3D 848L
	#define kcbNurbsCurveEvaluatePoint 709L
	#define kcbNurbsCurveGetNumPieces 681L
	#define kcbNurbsCurveType 688L
	#define kcbNurbsDegree 690L
	#define kcbNurbsDelVertex 685L
	#define kcbNurbsGetNumPts 682L
	#define kcbNurbsGetPt3D 683L
	#define kcbNurbsGetWeight 686L
	#define kcbNurbsKnot 691L
	#define kcbNurbsNumKnots 689L
	#define kcbNurbsSetKnot 692L
	#define kcbNurbsSetPt3D 684L
	#define kcbNurbsSetWeight 687L
	#define kcbNurbsSurfaceEvaluatePoint 710L
	#define kcbObjArea 1248L
	#define kcbObjSurfaceArea 1249L
	#define kcbObjVolume 1250L
	#define kcbProducts3D 849L
	#define kcbRemoveRoofElement 535L
	#define kcbSet3DVertex 86L
	#define kcbSetArcAnglesN 225L
	#define kcbSetBatAttributes 534L
	#define kcbSetDormerAttributes 548L
	#define kcbSetDormerThick 549L
	#define kcbSetEndPoints 121L
	#define kcbSetEntityMatrix 298L
	#define kcbSetExtrudeValues 300L
	#define kcbSetGableAttributes 525L
	#define kcbSetHipAttributes 531L
	#define kcbSetLocus3DPosition 317L
	#define kcbSetLocusPosition 318L
	#define kcbSetObjectBounds 8L
	#define kcbSetPolyShapeClose 190L
	#define kcbSetQArcQuadrant 223L
	#define kcbSetRoofAccessoriesParameters 1056L
	#define kcbSetRoofAttributes 513L
	#define kcbSetRRectDiameters 219L
	#define kcbSetShedAttributes 528L
	#define kcbSetSkylight 546L
	#define kcbSetSweepAnglesN 301L
	#define kcbSetSweepScrew 304L
	#define kcbSetTrapeziumAttributes 522L
	#define kcbSetVertex 85L
	#define kcbWrapGetSweepScrew 574L


///////////////////////////////////////////
//  Attributes (Graphic)
///////////////////////////////////////////


	#define kcbCreateCircularDimension 336L
	#define kcbGetArrowByClass 420L
	#define kcbGetArrowHeads 104L
	#define kcbGetArrowHeadsN 655L
	#define kcbGetColor 62L
	#define kcbGetDefaultOpacity 1400L
	#define kcbGetDefaultOpacityByClass 1401L
	#define kcbGetFColorsByClass 421L
	#define kcbGetFillIAxisEndPoint 800L
	#define kcbGetFillJAxisEndPoint 801L
	#define kcbGetFillOriginPoint 799L
	#define kcbGetFillPat 1L
	#define kcbGetFillPoints 798L
	#define kcbGetFPatByClass 422L
	#define kcbGetLineWeight 2L
	#define kcbGetLineWeightDisplayMM 556L
	#define kcbGetLineWeightDisplayPt 558L
	#define kcbGetLWByClass 423L
	#define kcbGetMarker 33L
	#define kcbGetObjBeginningMarker 1209L
	#define kcbGetObjEndMarker 1211L
	#define kcbGetOpacity 1392L
	#define kcbGetOpacityByClass 1396L
	#define kcbGetPColorsByClass 424L
	#define kcbGetPenPat 3L
	#define kcbGetPPatByClass 425L
	#define kcbGetVertexVis 330L
	#define kcbSetArrowByClass 426L
	#define kcbSetArrowHeads 105L
	#define kcbSetArrowHeadsN 654L
	#define kcbSetColor 63L
	#define kcbSetDefaultOpacity 1427L
	#define kcbSetDefaultOpacityByClass 1399L
	#define kcbSetFColorsByClass 427L
	#define kcbSetFillIAxisEndPoint 803L
	#define kcbSetFillJAxisEndPoint 804L
	#define kcbSetFillOriginPoint 802L
	#define kcbSetFillPat 9L
	#define kcbSetFPatByClass 428L
	#define kcbSetLineWeight 10L
	#define kcbSetLineWeightDisplayMM 554L
	#define kcbSetLineWeightDisplayPt 555L
	#define kcbSetLWByClass 429L
	#define kcbSetObjBeginningMarker 1210L
	#define kcbSetObjEndMarker 1212L
	#define kcbSetOpacity 1397L
	#define kcbSetOpacityByClass 1398L
	#define kcbSetPColorsByClass 430L
	#define kcbSetPenPat 11L
	#define kcbSetPPatByClass 431L
	#define kcbSetVertexVis 329L


///////////////////////////////////////////
//  Attributes (System)
///////////////////////////////////////////


	#define kcbGetDefinition 127L
	#define kcbGetDXFColorToLineWeight 577L
	#define kcbGetNamedObject 201L
	#define kcbGetObjectClass 70L
	#define kcbGetObjectName 108L
	#define kcbGetObjectType 60L
	#define kcbGetSymbolDefinitionIcon 292L
	#define kcbGetSymbolDefinitionType 312L
	#define kcbIsLocked 4L
	#define kcbIsSelected 5L
	#define kcbIsVisible 69L
	#define kcbLockObject 6L
	#define kcbSelectObject 7L
	#define kcbSetDXFColorToLineWeight 578L
	#define kcbSetObjectClass 71L
	#define kcbSetObjectName 109L
	#define kcbSetSymbolDefinitionIcon 293L
	#define kcbSetVisibility 87L


///////////////////////////////////////////
//  Auxiliary and Data Objects
///////////////////////////////////////////


	#define kcbAttachAuxObject 130L
	#define kcbDeleteAuxObject 131L
	#define kcbFindAuxObject 136L
	#define kcbFindDataObject 133L
	#define kcbFirstAuxObject 135L
	#define kcbGetDataTag 138L
	#define kcbGetPluginType 569L
	#define kcbIsPluginFormat 568L
	#define kcbNewDataObject 128L
	#define kcbNextAuxObject 137L
	#define kcbNextDataObject 134L
	#define kcbRemoveAuxObject 132L
	#define kcbTaggedDataCreate 1244L
	#define kcbTaggedDataGet 1247L
	#define kcbTaggedDataGetNumElements 1264L
	#define kcbTaggedDataRemoveContainer 1263L
	#define kcbTaggedDataRemoveTag 1246L
	#define kcbTaggedDataSet 1245L


///////////////////////////////////////////
//  Coordinate Transformation
///////////////////////////////////////////


	#define kcbCoordLengthToPageLengthN 102L
	#define kcbCoordLengthToPagePoints 699L
	#define kcbCoordLengthToPixelLength 189L
	#define kcbCoordLengthToUnitsLengthN 82L
	#define kcbCreateOvalN 1382L
	#define kcbDimStringToCoord 58L
	#define kcbFPCoordLengthToPageLength 552L
	#define kcbFPCoordLengthToUnitsLength 550L
	#define kcbModelPt2DToScreenPt 1371L
	#define kcbModelVecToScreenVec 1377L
	#define kcbPageLengthToFPCoordLength 553L
	#define kcbPagePointsToCoordLength 700L
	#define kcbPixelLengthToCoordLength 188L
	#define kcbScreenPtToModelPt2D 1372L
	#define kcbScreenVecToModelVec 1378L
	#define kcbUnitsLengthToFPCoordLength 551L
	#define kcbWorldCoordsPerDrawingUnit 698L
	#define kcbWrapPageLengthToCoordLengthN 570L
	#define kcbWrapUnitsLengthToCoordLengthN 571L


///////////////////////////////////////////
//  Creation
///////////////////////////////////////////


	#define kcbAddSolid 340L
	#define kcbAppendRoofEdge 514L
	#define kcbCreate3DPoly 64L
	#define kcbCreateAngleDimension 337L
	#define kcbCreateArcN 15L
	#define kcbCreateBatDormer 532L
	#define kcbCreateChainDimension 1287L
	#define kcbCreateCombineIntoSurface 853L
	#define kcbCreateCone 435L
	#define kcbCreateContourCurves 846L
	#define kcbCreateCustomDimensionStandard 488L
	#define kcbCreateCustomObject 371L
	#define kcbCreateCustomObjectByMatrix 384L
	#define kcbCreateCustomObjectDoubleClick 483L
	#define kcbCreateCustomObjectPath 658L
	#define kcbCreateExtrude 320L
	#define kcbCreateExtrudeAlongPath 665L
	#define kcbCreateGableDormer 523L
	#define kcbCreateGroup 13L
	#define kcbCreateHemisphere 436L
	#define kcbCreateHipDormer 529L
	#define kcbCreateImageProp 978L
	#define kcbCreateInterpolatedSurface 947L
	#define kcbCreateLayer 886L
	#define kcbCreateLayerN 314L
	#define kcbCreateLightN 334L
	#define kcbCreateLine 17L
	#define kcbCreateLinearDimension 335L
	#define kcbCreateLocus 18L
	#define kcbCreateLocus3D 313L
	#define kcbCreateLoftSurfaces 823L
	#define kcbCreateNurbsCurve 680L
	#define kcbCreateNurbsSurface 679L
	#define kcbCreateOval 19L
	#define kcbCreatePolyshape 20L
	#define kcbCreateQArc 118L
	#define kcbCreateRectangle 1379L
	#define kcbCreateRectangleN 1380L
	#define kcbCreateRoof 511L
	#define kcbCreateRoundWall 563L
	#define kcbCreateRRectangle 21L
	#define kcbCreateRRectangleN 1381L
	#define kcbCreateShedDormer 526L
	#define kcbCreateBasicSlab 343L
	#define kcbCreateSphere 434L
	#define kcbCreateStaticHatch 854L
	#define kcbCreateStaticHatchFromObject 874L
	#define kcbCreateSurfacefromCurvesNetwork 822L
	#define kcbCreateSweepN 321L
	#define kcbCreateSymbolDefinition 226L
	#define kcbCreateSymbolFolder 564L
	#define kcbCreateTaperedExtrude 678L
	#define kcbCreateTrapeziumDormer 520L
	#define kcbCreateViewport 876L
	#define kcbCreateWall 22L
	#define kcbDefineCustomObject 372L
	#define kcbDuplicateSelection 51L
	#define kcbExtendNurbsCurve 949L
	#define kcbExtendNurbsSurface 950L
	#define kcbGenerateBezierApproximationFromPolygon 980L
	#define kcbGroupSelection 24L
	#define kcbIntersectSolid 342L
	#define kcbPlaceSymbolByNameN 107L
	#define kcbPlaceSymbolN 106L
	#define kcbRevolveWithRail 951L
	#define kcbSplit2DObjectByLine 1255L
	#define kcbSubtractSolid 341L


///////////////////////////////////////////
//  Dialogs
///////////////////////////////////////////


	#define kcbAddChoice 603L
	#define kcbAddListBoxTabStop 775L
	#define kcbAddListBrowserImage 933L
	#define kcbAdjustComponentPixelPos 1360L
	#define kcbAlertCritical 995L
	#define kcbAlertInform 991L
	#define kcbAlertQuestion 993L
	#define kcbAlignBottomEdge 595L
	#define kcbAlignLeftEdge 596L
	#define kcbAlignRightEdge 594L
	#define kcbAreListBrowserColumnLinesEnabled 938L
	#define kcbAreListBrowserRadioColumnLinesEnabled 936L
	#define kcbClearGradientSliderSegments 809L
	#define kcbConfirm 26L
	#define kcbCreateCenteredStaticText 1226L
	#define kcbCreateCheckBox 580L
	#define kcbCreateCheckBoxGroupBox 889L
	#define kcbCreateClassPullDownMenu 1347L
	#define kcbCreateCMYKColorSwatch 1443L
	#define kcbCreateColorPopup 1069L
	#define kcbCreateControl 597L
	#define kcbCreateCustomControl 1317L
	#define kcbCreateDesignLayerPullDownMenu 1348L
	#define kcbCreateEditInteger 702L
	#define kcbCreateEditReal 703L
	#define kcbCreateEditText 581L
	#define kcbCreateEnhancedPullDownMenu 1200L
	#define kcbCreateGroupBox 582L
	#define kcbCreateIconPushButton 1195L
	#define kcbCreateImageControl 1228L
	#define kcbCreateLayout 579L
	#define kcbCreateLineAttributePopup 1063L
	#define kcbCreateLineStylePopup 1058L
	#define kcbCreateLineWeightPopup 1061L
	#define kcbCreateListBox 583L
	#define kcbCreateListBoxN 864L
	#define kcbCreateListBrowser 912L
	#define kcbCreateMarkerPopup 1072L
	#define kcbCreatePatternPopup 1066L
	#define kcbCreatePullDownMenu 584L
	#define kcbCreatePullDownMenuGroupBox 1235L
	#define kcbCreatePushButton 585L
	#define kcbCreateRadioButton 586L
	#define kcbCreateRadioButtonGroupBox 890L
	#define kcbCreateResizableLayout 986L
	#define kcbCreateRightStaticText 1225L
	#define kcbCreateSeparator 1227L
	#define kcbCreateSheetLayerPullDownMenu 1349L
	#define kcbCreateStandardIconControl 977L
	#define kcbCreateStaticText 587L
	#define kcbCreateSwapControl 966L
	#define kcbCreateSwapPane 967L
	#define kcbCreateSymbolDisplayControl 1007L
	#define kcbCreateTabControl 891L
	#define kcbCreateTabPane 892L
	#define kcbCreateThreeStateCheckBox 1197L
	#define kcbCreateTreeControl 1351L
	#define kcbDeleteAllItems 838L
	#define kcbDeleteAllListBrowserItems 1090L
	#define kcbDeleteListBrowserColumn 914L
	#define kcbDeleteListBrowserItem 919L
	#define kcbDeselectEditText 1223L
	#define kcbDisplayColorPopup 1451L
	#define kcbDisplaySwapPane 968L
	#define kcbDisplayTabPane 1049L
	#define kcbEnableItem 601L
	#define kcbEnableListBrowser 1094L
	#define kcbEnableListBrowserClickAllDataChange 1091L
	#define kcbEnableListBrowserColumnLines 939L
	#define kcbEnableListBrowserColumnTracking 942L
	#define kcbEnableListBrowserDragAndDrop 1075L
	#define kcbEnableListBrowserDropOnIndices 1203L
	#define kcbEnableListBrowserRadioColumnLines 937L
	#define kcbEnableListBrowserSingleLineSelection 1093L
	#define kcbEnableListBrowserSorting 934L
	#define kcbEnableListBrowserUpdates 1266L
	#define kcbEnsureListBrowserItemIsVisible 1051L
	#define kcbExpandTreeControlItem 1390L
	#define kcbFindListBrowserColumnDataItem 929L
	#define kcbFindListBrowserColumnItem 930L
	#define kcbFormatTextDialog 711L
	#define kcbGetActiveEditItem 1224L
	#define kcbGetActivePane 1048L
	#define kcbGetBooleanItem 602L
	#define kcbGetChoiceCount 609L
	#define kcbGetChoiceIndex 605L
	#define kcbGetChoiceText 608L
	#define kcbGetCMYKColor 1444L
	#define kcbGetColorButton 831L
	#define kcbGetColorChoice 1071L
	#define kcbGetComponentRect 1358L
	#define kcbGetComponentTextWidth 1345L
	#define kcbGetControlData 613L
	#define kcbGetCustomControlScrollArea 1375L
	#define kcbGetEditInteger 704L
	#define kcbGetEditReal 705L
	#define kcbGetGradientSliderData 806L
	#define kcbGetGradientSliderSelectedMarker 812L
	#define kcbGetIconPushButtonState 1357L
	#define kcbGetImagePopupObject 815L
	#define kcbGetImagePopupObjectItemIndex 817L
	#define kcbGetImagePopupSelectedItem 820L
	#define kcbGetItemText 599L
	#define kcbGetLayoutDialogPosition 960L
	#define kcbGetLayoutDialogSize 989L
	#define kcbGetLayoutFromRsrc 611L
	#define kcbGetLBHeaderTextWidth 1460L
	#define kcbGetLineAttributeData 1065L
	#define kcbGetLineStyleChoice 1060L
	#define kcbGetLineWeightChoice 1057L
	#define kcbGetListBrowserColumnWidth 916L
	#define kcbGetListBrowserColumnDataItemInfo 924L
	#define kcbGetListBrowserColumnSortState 996L
	#define kcbGetListBrowserColumnOwnerDrawnType 1012L
	#define kcbGetListBrowserColumnHeaderToolTip 1037L
	#define kcbGetListBrowserColumnHeaderJust 1039L
	#define kcbGetListBrowserControlType 932L
	#define kcbGetListBrowserEditDisplayType 946L
	#define kcbGetListBrowserEventInfo 1115L
	#define kcbGetListBrowserItemDashStyle 1024L
	#define kcbGetListBrowserItemData 1386L
	#define kcbGetListBrowserItemDisplayType 944L
	#define kcbGetListBrowserItemFillForeColor 1014L
	#define kcbGetListBrowserItemFillBackColor 1016L
	#define kcbGetListBrowserItemGradientOrImageRefNumber 1022L
	#define kcbGetListBrowserItemInfo 922L
#if _WINDOWS
	#define kcbGetListBrowserItemPatternIndex 1026L
#endif
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbGetListBrowserItemPattern 1028L
#endif
	#define kcbGetListBrowserItemPenForeColor 1018L
	#define kcbGetListBrowserItemPenBackColor 1020L
	#define kcbGetListBrowserItemTextJust 1002L
	#define kcbGetListBrowserItemTextStyle 1003L
	#define kcbGetListBrowserItemTextColor 1004L
	#define kcbDeprecated481 1053L
	#define kcbGetListBrowserSortColumn 998L
	#define kcbGetMarkerChoice 1074L
	#define kcbGetMarkerPopupSelectedItem 894L
	#define kcbGetMultilineText 840L
	#define kcbGetNumGradientSliderSegments 810L
	#define kcbGetNumImagePopupItems 818L
	#define kcbGetNumListBrowserColumns 917L
	#define kcbGetNumListBrowserColumnDataItems 926L
	#define kcbGetNumListBrowserItems 920L
	#define kcbGetNumSelectedListBrowserItems 1092L
	#define kcbGetPatternData 1068L
	#define kcbGetSelChoiceIndex 861L
	#define kcbGetSelectedChoiceIndex 607L
	#define kcbGetSelectionRange 1221L
	#define kcbGetThreeStateCheckBoxState 1199L
	#define kcbGetTreeControlItemData 1388L
	#define kcbGetTreeControlSelectedItem 1354L
	#define kcbInsertEnhancedPullDownMenuItem 1201L
	#define kcbInsertGradientSliderSegment 807L
	#define kcbInsertImagePopupObjectItem 813L
	#define kcbInsertImagePopupResource 1046L
	#define kcbInsertImagePopupSeparator 1236L
	#define kcbInsertListBrowserColumn 913L
	#define kcbInsertListBrowserColumnDataItem 923L
	#define kcbInsertListBrowserItem 918L
	#define kcbInsertProposedClassOrLayerItem 1350L
	#define kcbInsertTreeControlItem 1352L
	#define kcbIsItemEnabled 1383L
	#define kcbIsItemVisible 1384L
	#define kcbIsListBrowserColumnTrackingEnabled 941L
	#define kcbIsListBrowserItemSelected 940L
	#define kcbIsListBrowserSortingEnabled 935L
	#define kcbNotifyPullDownClicked 1448L
	#define kcbOverrideControl 1318L
	#define kcbPostMinorNoteAlert 663L
	#define kcbPostMinorStopAlert 664L
	#define kcbPostNoteAlert 27L
	#define kcbPostStopAlert 28L
	#define kcbRefreshItem 1269L
	#define kcbRefreshListBrowser 1050L
	#define kcbRemoveAllImagePopupItems 816L
	#define kcbRemoveAllListBrowserColumnDataItems 928L
	#define kcbRemoveChoice 604L
	#define kcbRemoveEnhancedPullDownMenuItemRange 1202L
	#define kcbRemoveGradientSliderSegment 808L
	#define kcbRemoveImagePopupItem 814L
	#define kcbRemoveListBoxTabStop 776L
	#define kcbRemoveListBrowserColumnDataItem 927L
	#define kcbRemoveTreeControlItem 1353L
	#define kcbRunLayoutDialog 620L
	#define kcbSelectChoice 606L
	#define kcbSelectEditText 610L
	#define kcbSelectTreeControlItem 1389L
	#define kcbSetBelowItem 593L
	#define kcbSetBooleanItem 600L
	#define kcbSetCMYKColor 1445L
	#define kcbSetColorButton 832L
	#define kcbSetColorChoice 1070L
	#define kcbSetComponentIndeterminate 1361L
	#define kcbSetComponentSize 1359L
	#define kcbSetControlData 612L
	#define kcbSetEdgeBinding 987L
	#define kcbSetEditInteger 706L
	#define kcbSetEditReal 707L
	#define kcbSetFirstGroupItem 591L
	#define kcbSetFirstLayoutItem 590L
	#define kcbSetFocusOnItem 1268L
	#define kcbSetFocusOnListBrowser 1054L
	#define kcbSetGradientSliderData 805L
	#define kcbSetGradientSliderSelectedMarker 811L
	#define kcbSetHelpText 588L
	#define kcbSetIconPushButtonState 1356L
	#define kcbSetImageControlHandle 1229L
	#define kcbSetImageControlPath 1344L
	#define kcbSetImagePopupSelectedItem 819L
	#define kcbSetItemText 598L
	#define kcbSetItemToolTipText 1355L
	#define kcbSetLayoutDialogPosition 959L
	#define kcbSetLayoutDialogSize 990L
	#define kcbSetLayoutOption 985L
	#define kcbSetLineAttributeData 1064L
	#define kcbSetLineStyleChoice 1059L
	#define kcbSetLineWeightChoice 1062L
	#define kcbSetListBrowserColumnWidth 915L
	#define kcbSetListBrowserColumnOwnerDrawnType 1011L
	#define kcbSetListBrowserColumnHeaderToolTip 1036L
	#define kcbSetListBrowserColumnHeaderJust 1038L
	#define kcbSetListBrowserColumnImage 1346L
	#define kcbSetListBrowserControlType 931L
	#define kcbSetListBrowserDragAndDropColumn 1116L
	#define kcbSetListBrowserEditDisplayType 945L
	#define kcbSetListBrowserItemDashStyle 1023L
	#define kcbSetListBrowserItemData 1385L
	#define kcbSetListBrowserItemDisplayType 943L
	#define kcbSetListBrowserItemFillForeColor 1013L
	#define kcbSetListBrowserItemFillBackColor 1015L
	#define kcbSetListBrowserItemGradientOrImageRefNumber 1021L
	#define kcbSetListBrowserItemInfo 921L
#if _WINDOWS
	#define kcbSetListBrowserItemPatternIndex 1025L
#endif
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbSetListBrowserItemPattern 1027L
#endif
	#define kcbSetListBrowserItemPenForeColor 1017L
	#define kcbSetListBrowserItemPenBackColor 1019L
	#define kcbSetListBrowserItemTextJust 999L
	#define kcbSetListBrowserItemTextStyle 1000L
	#define kcbSetListBrowserItemTextColor 1001L
	#define kcbSetListBrowserItemUsingColumnDataItem 925L
	#define kcbDeprecated590 1052L
	#define kcbSetListBrowserSelection 958L
	#define kcbSetListBrowserSortColumn 997L
	#define kcbSetMarkerChoice 1073L
	#define kcbSetMultilineText 845L
	#define kcbSetPatternData 1067L
	#define kcbSetProportionalBinding 988L
	#define kcbSetRightItem 592L
	#define kcbSetSelectionRange 1222L
	#define kcbSetTextEditable 979L
	#define kcbSetThreeStateCheckBoxState 1198L
	#define kcbSetTreeControlItemData 1387L
	#define kcbShowEnhancedPullDownMenuGroupIcon 1265L
	#define kcbShowItem 981L
	#define kcbUpdateCustomControlScrollArea 1374L
	#define kcbUpdateSymbolDisplayControl 1008L
	#define kcbVerifyLayout 589L


///////////////////////////////////////////
//  Document
///////////////////////////////////////////


	#define kcbAddClass 168L
	#define kcbAddDashPat 309L
	#define kcbAddGuidesClass 508L
	#define kcbColorIndexToName 1452L
	#define kcbColorIndexToRGB 322L
	#define kcbCopySymbol 839L
	#define kcbCreateGradient 778L
	#define kcbCreateHatch 759L
	#define kcbCreateImageFromPaint 791L
	#define kcbCreatePaintFromImage 792L
	#define kcbCreateWallStyle 1311L
	#define kcbDeleteClass 169L
	#define kcbDeleteDashPat 310L
	#define kcbDeselectAll 29L
	#define kcbGetActiveSymbolDef 273L
	#define kcbGetClassVisibility 266L
	#define kcbGetCurrentLayer 203L
	#define kcbGetCurrentView 1450L
	#define kcbGetDashPat 284L
	#define kcbGetDimensionClassID 694L
	#define kcbGetGradientData 783L
	#define kcbGetGradientMidpointPosition 787L
	#define kcbGetGradientSpotColor 789L
	#define kcbGetGradientSpotPosition 785L
	#define kcbGetGridUnits 155L
	#define kcbGetHatchLevel 761L
	#define kcbGetLayerScaleN 173L
	#define kcbGetNamedLayer 965L
	#define kcbGetNoneClassID 693L
	#define kcbGetNumDashPats 286L
	#define kcbGetNumGradientSegments 780L
	#define kcbGetPageBounds 171L
	#define kcbGetPatternBits 767L
	#define kcbGetSheetLayerUserOrigin 887L
	#define kcbGetUnits 269L
	#define kcbGetUserOrigin 204L
	#define kcbGetUserOriginFP 369L
	#define kcbInsertGradientSegment 781L
	#define kcbMarkCurrentDocChanged 325L
	#define kcbNumSelectedObjects 30L
	#define kcbRemoveGradientSegment 782L
	#define kcbResetAllObjectsVisibility 268L
	#define kcbRGBToColorIndex 323L
	#define kcbSelectAll 31L
	#define kcbSetActiveSymbolDef 274L
	#define kcbSetClassVisibility 267L
	#define kcbSetCurrentLayer 294L
	#define kcbSetDashPat 285L
	#define kcbSetGradientData 784L
	#define kcbSetGradientMidpointPosition 788L
	#define kcbSetGradientSpotColor 790L
	#define kcbSetGradientSpotPosition 786L
	#define kcbSetHatchLevel 760L
	#define kcbSetLayerScaleN 200L
	#define kcbSetMarker 272L
	#define kcbSetProjection 307L
	#define kcbSetRenderMode 276L
	#define kcbSetSheetLayerUserOrigin 888L
	#define kcbSetUserOrigin 205L
	#define kcbSetUserOriginFP 370L
	#define kcbShowCreateImageDialog 793L
	#define kcbShowGradientEditorDialog 779L
	#define kcbValidClass 202L


///////////////////////////////////////////
//  Files and Directories
///////////////////////////////////////////


	#define kcbCreateTessellator 1121L
	#define kcbDeleteTessellator 1122L
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbEncryptVSPluginFile 770L
#endif
	#define kcbEncryptVSPluginFilePath 855L
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbFindFileInPluginFolder 1029L
#endif
	#define kcbFindFileInPluginFolderN 1461L
#if _WINDOWS
	#define kcbFindFilePathInPluginFolder 1030L
#endif
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbForEachFileInFolder 147L
#endif
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbForEachFileInFolderN 1031L
#endif
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbForEachFileInPluginFolder 1005L
#endif
	#define kcbForEachFileInStandardFolder 1337L
#if _WINDOWS
	#define kcbForEachFilePathInFolder 456L
#endif
	#define kcbForEachFilePathInFolderN 1032L
	#define kcbForEachFilePathInPluginFolder 1006L
	#define kcbForEachFilePathInStandardFolder 1338L
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbGetActiveDocument 484L
#endif
	#define kcbGetActiveDocumentN 1462L
#if _WINDOWS
	#define kcbGetActiveDocumentPath 485L
#endif
	#define kcbGetFilePathInStandardFolder 1339L
	#define kcbGetFilePathInStandardFolderN 1465L
	#define kcbGetFilePathInUserRoot 1341L
	#define kcbGetFilePathInUserRootN 1466L
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbGetFolder 452L
#endif
	#define kcbGetFolderN 1463L
#if _WINDOWS
	#define kcbGetFolderPath 453L
#endif
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbGetNamedSubFolder 146L
#endif
	#define kcbGetNamedSubFolderN 1468L
	#define kcbGetNumFilesInStandardFolder 1343L
	#define kcbImportDXF 1464L
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbImportDXFMac 575L
#endif
#if _WINDOWS
	#define kcbImportDXFWin 576L
#endif
	#define kcbIsInStandardFolder 1342L
	#define kcbIsInStandardFolderN 1467L
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbOpenDocument 765L
#endif
	#define kcbOpenDocumentPath 766L
	#define kcbReadVSExternalFilePath 458L
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbSaveActiveDocument 560L
#endif
	#define kcbSaveActiveDocumentPath 561L
	#define kcbTesselateObject 1123L
	#define kcbWriteMaterialImageFile 1124L


///////////////////////////////////////////
//  Image Manipulation
///////////////////////////////////////////


#if _WINDOWS
	#define kcbCreateDIBFromPaintNode 496L
#endif
#if _WINDOWS
	#define kcbCreateDIBFromPreview 773L
#endif
#if _WINDOWS
	#define kcbCreatePaintNodeFromDIB 494L
#endif
#if _WINDOWS
	#define kcbDisposeDIB 498L
#endif
	#define kcbUpdateThumbnailPreview 954L


///////////////////////////////////////////
//  Internal use
///////////////////////////////////////////


	#define kcbCloseXCode 59L
	#define kcbOpenXCode 32L


///////////////////////////////////////////
//  Memory Allocation
///////////////////////////////////////////


	#define kcbDisposeHandle 376L
	#define kcbDisposePtr 504L
	#define kcbGetHandleSize 383L
	#define kcbGetHandleState 381L
	#define kcbNewHandle 375L
	#define kcbNewPtr 503L
	#define kcbReduceHandleSize 380L
	#define kcbSetHandleSize 379L
	#define kcbSetHandleState 382L
	#define kcbSetPtrSize 505L


///////////////////////////////////////////
//  Menus
///////////////////////////////////////////


	#define kcbAddResourceToList 1055L
	#define kcbBuildResourceList 1040L
	#define kcbDeleteResourceFromList 1042L
	#define kcbDisposeResourceList 1043L
	#define kcbGetActualNameFromResourceList 1118L
	#define kcbGetMyMenuCommandIndex 277L
	#define kcbGetNameFromResourceList 1045L
	#define kcbGetResourceFromList 1041L
	#define kcbImportResourceToCurrentFile 1047L
	#define kcbRegisterMenuForCallback 278L
	#define kcbResourceListSize 1044L
	#define kcbUnregisterMenuForCallback 279L


///////////////////////////////////////////
//  Mode Bar
///////////////////////////////////////////


	#define kcbDeprecated35L 35L
	#define kcbDeprecated36L 36L
	#define kcbAddPullDownMenuItem 1252L
	#define kcbAddPullDownMenuMode 1251L
	#define kcbDeprecated37L 37L
	#define kcbAddTxtBtnMode 38L
	#define kcbEnableMode 39L
	#define kcbGetModeValue 40L
	#define kcbSetHelpString 61L
	#define kcbSetModeValue 41L
	#define kcbSetPullDownMenuSelection 1253L


///////////////////////////////////////////
//  Name Translation
///////////////////////////////////////////


	#define kcbClassIDToName 74L
	#define kcbClassNameToID 76L
	#define kcbInternalIndexToHandle 565L
	#define kcbInternalIndexToNameN 510L
	#define kcbMaxClassID 75L
	#define kcbNameToInternalIndexN 509L
	#define kcbSetPolyVertexLoopDirection 1238L


///////////////////////////////////////////
//  Object Manipulation
///////////////////////////////////////////


	#define kcbAddToConstraintModel 615L
	#define kcbAddViewportAnnotationObject 882L
	#define kcbAppendParameterWidget 961L
	#define kcbAppendWidget 908L
	#define kcbConvertTo3DPolygons 344L
	#define kcbConvertToNURBS 821L
	#define kcbConvertToPolygon 83L
	#define kcbConvertToPolygonN 862L
	#define kcbConvertToPolyline 119L
	#define kcbConvertToUnstyledWall 1120L
	#define kcbCreateConstraintModel 616L
	#define kcbCreateOffsetNurbsObjectHandle 830L
	#define kcbCustomObjectControlPtsCreate 1230L
	#define kcbCustomObjectControlPtsRemove 1231L
	#define kcbCustomObjectControlPtSet 1232L
	#define kcbCustomObjectGetSurfaceProxy 1233L
	#define kcbCustomObjectReplacePath 1234L
	#define kcbDeleteAllComponents 1295L
	#define kcbDeleteComponent 1078L
	#define kcbDeleteConstraint 635L
	#define kcbDuplicateObject 157L
	#define kcbEnableParameter 772L
	#define kcbEvaluateNurbsSurfacePointAndNormal 952L
	#define kcbForEachLayer 122L
	#define kcbForEachObject 34L
	#define kcbGet2DPt 634L
	#define kcbGetBinaryConstraint 637L
	#define kcbGetClosestPt 641L
	#define kcbGetClosestSide 640L
	#define kcbGetComponentClass 1405L
	#define kcbGetComponentFill 1084L
	#define kcbGetComponentFillColors 1407L
	#define kcbGetComponentName 1403L
	#define kcbGetComponentPenColors 1409L
	#define kcbGetComponentPenStyles 1086L
	#define kcbGetComponentPenWeights 1085L
	#define kcbGetComponentUseFillClassAttr 1419L
	#define kcbGetComponentUsePenClassAttr 1422L
	#define kcbGetComponentWidth 1083L
	#define kcbGetCustomObjectColor 1456L
	#define kcbGetCustomObjectPath 659L
	#define kcbGetCustomObjectProfileGroup 660L
	#define kcbGetDimensionStandardVariable 486L
	#define kcbGetDistanceAlongNurbsCurve 863L
	#define kcbGetLocalizedPluginChoice 1257L
	#define kcbGetLocalizedPluginName 1256L
	#define kcbGetLocalizedPluginParameter 1258L
	#define kcbGetNumberOfComponents 1079L
	#define kcbGetNurbsObjectDistanceFromPoint 829L
	#define kcbGetObjectProperty 897L
	#define kcbGetObjectPropertyChar 898L
	#define kcbGetObjectVariable 361L
	#define kcbGetParameterOnNurbsCurve 834L
	#define kcbGetPointAndParameterOnNurbsCurveAtGivenLength 852L
	#define kcbGetRoofEdge 516L
	#define kcbGetSingularConstraint 636L
	#define kcbGetViewportClassVisibility 879L
	#define kcbGetViewportCropObject 883L
	#define kcbGetViewportGroup 881L
	#define kcbGetViewportGroupParent 955L
	#define kcbGetViewportLayerVisibility 877L
	#define kcbGroupToMesh 305L
	#define kcbHasConstraint 697L
	#define kcbInsertAllParametersAsWidgets 896L
	#define kcbInsertNewComponent 1076L
	#define kcbInsertParameterWidget 962L
	#define kcbInsertWidget 895L
	#define kcbIsObjectFromReferencedFile 562L
	#define kcbIsViewportGroupContainedObject 956L
	#define kcbMakePolyshapeValid 319L
	#define kcbMeshToGroup 306L
	#define kcbMoveObject 151L
	#define kcbMoveObject3D 152L
	#define kcbNotifyLayerChange 1088L
	#define kcbRemoveCustomObjectColor 1458L
	#define kcbRemoveRoofEdge 518L
	#define kcbResetObject 153L
	#define kcbRotateObjectN 156L
	#define kcbScaleObject3D 899L
	#define kcbScaleObjectN 158L
	#define kcbSetBinaryConstraint 639L
	#define kcbSetComponentClass 1406L
	#define kcbSetComponentFill 1080L
	#define kcbSetComponentFillColors 1408L
	#define kcbSetComponentName 1404L
	#define kcbSetComponentPenColors 1410L
	#define kcbSetComponentPenStyles 1082L
	#define kcbSetComponentPenWeights 1081L
	#define kcbSetComponentUseFillClassAttr 1420L
	#define kcbSetComponentUsePenClassAttr 1421L
	#define kcbSetComponentWidth 1077L
	#define kcbSetConstraintValue 642L
	#define kcbSetCustomDimensionStandardVariable 487L
	#define kcbSetCustomObjectColor 1455L
	#define kcbSetCustomObjectControlPointVisibility 1097L
	#define kcbSetCustomObjectPath 661L
	#define kcbSetCustomObjectProfileGroup 662L
	#define kcbSetDefinition 154L
	#define kcbSetObjectProperty 872L
	#define kcbSetObjectPropertyChar 873L
	#define kcbSetObjectVariable 360L
	#define kcbSetParameterVisibility 771L
	#define kcbSetRoofEdge 517L
	#define kcbSetSingularConstraint 638L
	#define kcbSetViewportClassVisibility 880L
	#define kcbSetViewportCropObject 884L
	#define kcbSetViewportLayerVisibility 878L
	#define kcbTrimToSelectedObjects 328L
	#define kcbUpdateConstraintModel 617L
	#define kcbUpdateViewport 893L
	#define kcbViewportHasCropObject 885L


///////////////////////////////////////////
//  Resources
///////////////////////////////////////////


	#define kcbCountResources 440L
	#define kcbGetApplicationResFile 443L
	#define kcbGetCurrentResFile 444L
	#define kcbGetIndResource 441L
	#define kcbGetResource 385L
	#define kcbGetResourceName 442L
	#define kcbGetResourceString 387L
	#define kcbReleaseResource 386L
	#define kcbRemoveResource 439L
	#define kcbSetResourceName 450L
	#define kcbUseResFile 445L
	#define kcbWriteResource 438L


///////////////////////////////////////////
//  Selection Manipulation
///////////////////////////////////////////


	#define kcbFirstSelectedObject 206L
	#define kcbGetSelectionBounds 170L
	#define kcbGetSelectionBoundsCube 186L
	#define kcbMoveSelection 159L
	#define kcbMoveSelection3D 160L
	#define kcbRotateSelectionN 161L
	#define kcbScaleSelectionN 162L


///////////////////////////////////////////
//  Text Block Objects
///////////////////////////////////////////


	#define kcbAddText 250L
	#define kcbAddTextFromBuffer 373L
	#define kcbCreateTextBlock 265L
	#define kcbDeleteText 251L
	#define kcbGetCharNumFromPoint 907L
	#define kcbGetTextColor 256L
	#define kcbGetTextFontIndex 255L
	#define kcbGetTextJustification 264L
	#define kcbGetTextLength 493L
	#define kcbGetTextLineHeight 257L
	#define kcbGetTextOrientationN 287L
	#define kcbGetTextSize 254L
	#define kcbGetTextStyle 253L
	#define kcbGetTextVerticalAlignment 491L
	#define kcbGetTextVerticalSpacing 507L
	#define kcbGetTextWidth 542L
	#define kcbGetTextWrap 544L
	#define kcbSetTextColor 259L
	#define kcbSetTextFontIndex 260L
	#define kcbSetTextJustification 263L
	#define kcbSetTextOrientationN 288L
	#define kcbSetTextSize 261L
	#define kcbSetTextStyle 262L
	#define kcbSetTextVerticalAlignment 492L
	#define kcbSetTextVerticalSpacing 258L
	#define kcbSetTextWidth 541L
	#define kcbSetTextWrap 543L
	#define kcbSpellCheckTextBuffer 673L


///////////////////////////////////////////
//  Textures
///////////////////////////////////////////


	#define kcbAttachDefaultTextureSpace 471L
	#define kcbCreateShaderRecord 856L
	#define kcbCreateTexture 461L
	#define kcbCreateTextureBitmap 466L
	#define kcbCreateTextureBitmapFromPaintNode 506L
	#define kcbDeleteTextureSpace 469L
	#define kcbEditShaderRecord 859L
	#define kcbEditTexture 462L
	#define kcbEditTextureBitmap 467L
	#define kcbEditTextureSpace 472L
	#define kcbGetClGenTexture 402L
	#define kcbGetClRoofTextures 406L
	#define kcbGetClUseTexture 409L
	#define kcbGetClWallTextures 407L
	#define kcbGetShaderRecord 857L
	#define kcbGetTextureRef 463L
	#define kcbGetTextures 490L
	#define kcbGetTextureSpace 468L
	#define kcbGetVPClassGenTexture 1241L
	#define kcbGetVPClassRoofTextures 1242L
	#define kcbGetVPClassWallTextures 1243L
	#define kcbSetClGenTexture 412L
	#define kcbSetClRoofTextures 416L
	#define kcbSetClUseTexture 419L
	#define kcbSetClWallTextures 417L
	#define kcbSetDefaultTextureSpace 470L
	#define kcbSetTextureRef 464L


///////////////////////////////////////////
//  Tool Utilities
///////////////////////////////////////////


	#define kcbAddToolPersistentDraw 865L
	#define kcbAddToolSnapGeometry 909L
	#define kcbBoxToolDraw 652L
	#define kcbClearAllToolPts 630L
	#define kcbClearDataDisplayBar 209L
	#define kcbClickDragToolStatus 647L
	#define kcbCustomBarCreate 900L
	#define kcbCustomBarGetFieldInfo 904L
	#define kcbCustomBarInstall 902L
	#define kcbCustomBarRelease 901L
	#define kcbCustomBarSetFieldAngle 906L
	#define kcbCustomBarSetFieldInfo 903L
	#define kcbCustomBarSetFieldWorldCoord 905L
	#define kcbDefault2DToolDraw 650L
	#define kcbDefault3DToolDraw 651L
	#define kcbDrawCoordArcN 129L
	#define kcbDrawCoordEllipse 187L
	#define kcbDrawCoordLine 42L
	#define kcbDrawCoordLine3D 875L
	#define kcbDrawCoordRect 44L
	#define kcbDrawDataDisplayBar 216L
	#define kcbDrawNurbsObject 833L
	#define kcbDrawObject 43L
	#define kcbGetCoords 45L
	#define kcbGetNumToolPts 621L
	#define kcbGetToolCoreInterface 646L
	#define kcbGetToolPt2D 622L
	#define kcbGetToolPt3D 626L
	#define kcbGetToolPtCurrent2D 623L
	#define kcbGetToolPtCurrent3D 631L
	#define kcbGetToolPtCurrentViewPt 633L
	#define kcbGetToolPtCurrentWorkingPlane 632L
	#define kcbGetToolPtViewPoint 628L
	#define kcbGetToolPtWorkingPlane 627L
	#define kcbInstallConstraintAlong3DLine 911L
	#define kcbInteractive2DDraw 48L
	#define kcbOnePointToolStatus 644L
	#define kcbPolyToolStatus 649L
	#define kcbPopLastToolPt 629L
	#define kcbRemoveHotSpot 869L
	#define kcbRemoveToolPersistentDraw 866L
	#define kcbRemoveToolSnapGeometry 910L
	#define kcbRunTemporary2DTool 695L
	#define kcbRunTemporary3DTool 696L
	#define kcbSetCursorMode 49L
	#define kcbSetDataDisplayBarField 210L
	#define kcbSetDimUserBarValue 214L
	#define kcbSetFloatUserBarValueN 211L
	#define kcbSetTextUserBarValue 215L
	#define kcbSetToolProperty 870L
	#define kcbSetToolPropertyChar 871L
	#define kcbThreePointToolStatus 648L
	#define kcbTrackHotSpot 868L
	#define kcbTrackTool 46L
	#define kcbTwoPointToolStatus 645L


///////////////////////////////////////////
//  Tree Walking & Manipulation
///////////////////////////////////////////


	#define kcbAddObjectToContainer 113L
	#define kcbAuxOwner 835L
	#define kcbDeleteObject 81L
	#define kcbFindHandleDeep 676L
	#define kcbFirstMemberObj 79L
	#define kcbGetDefaultContainer 311L
	#define kcbGetDrawingHeader 123L
	#define kcbGetHatchListHeader 762L
	#define kcbGetSymbolLibraryHeader 126L
	#define kcbInsertObjectAfter 111L
	#define kcbInsertObjectBefore 110L
	#define kcbLastMemberObj 80L
	#define kcbNextObject 77L
	#define kcbParentObject 112L
	#define kcbPrevObject 78L
	#define kcbSearchForAncestorType 836L
	#define kcbSetPageBounds 1449L


///////////////////////////////////////////
//  <Unclassified>
///////////////////////////////////////////


	#define kcbAcquireExportPDFSettingsAndLocation 1259L
	#define kcbClosePDFDocument 1262L
	#define kcbExportPDFPages 1261L
	#define kcbOpenPDFDocument 1260L


///////////////////////////////////////////
//  Undo
///////////////////////////////////////////


	#define kcbAddAfterMoveObject 482L
	#define kcbAddAfterSwapObject 164L
	#define kcbAddBeforeMoveObject 481L
	#define kcbAddBeforeSwapObject 163L
	#define kcbAddBothSwapObject 165L
	#define kcbAddCoordMoveObject2D 566L
	#define kcbAddCoordMoveObject3D 567L
	#define kcbEndUndoEvent 460L
	#define kcbNameUndoEvent 459L
	#define kcbNonUndoableActionOK 480L
	#define kcbSetUndoMethod 73L
	#define kcbSupportUndoAndRemove 618L
	#define kcbUndoAndRemove 619L


///////////////////////////////////////////
//  Utility
///////////////////////////////////////////


	#define kcbAngleToStringN 125L
	#define kcbAssociateLinearDimension 1283L
	#define kcbCallPluginLibrary 667L
	#define kcbClipSurface 860L
	#define kcbCombineIntoSurface 289L
	#define kcbCoordToDimString 57L
	#define kcbCStringCompare 970L
	#define kcbCStringEqual 969L
	#define kcbDisableModules 844L
	#define kcbDisplayContextHelpOfCurrentPlugin 1117L
	#define kcbDisplayContextualHelp 1376L
	#define kcbDisplayOrganizationDialog 1089L
	#define kcbDoMenuName 199L
	#define kcbDoProgramAction 653L
	#define kcbDoubleToString 308L
#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#define kcbDoUpdateOrActivate 149L
#endif
	#define kcbDrawScreen 50L
	#define kcbEllipseEllipseIntersect 220L
	#define kcbExternalNameToID 177L
	#define kcbFontIndexFromName 502L
	#define kcbFontNameFromIndex 501L
	#define kcbGetActiveClassicSerialNumber 850L
	#define kcbGetActiveSerialNumber 841L
	#define kcbGetCallBackInval 175L
	#define kcbGetCurrentMode 842L
	#define kcbGetDataBarCursorVisState 1391L
	#define kcbGetEnabledModules 843L
	#define kcbGetHostInfo 280L
	#define kcbGetModifierFlags 197L
	#define kcbGetProduct 758L
	#define kcbGetSavedSetting 1010L
	#define kcbHandlePendingUpdatesAndActivates 148L
	#define kcbHilitePalettesAndTopDocument 150L
	#define kcbIntersectObjects 221L
	#define kcbKludge 326L
	#define kcbLineEllipseIntersect 213L
	#define kcbLineLineIntersect 212L
	#define kcbObjectNearCoordPt 275L
	#define kcbPlaySoundResource 1204L
	#define kcbPointInsidePoly 363L
	#define kcbPointOnPolyEdge 362L
	#define kcbRegisterExternal 178L
	#define kcbRegisterNotificationProcedure 669L
	#define kcbSetCallBackInval 174L
	#define kcbSetPersistentHighlight 671L
	#define kcbSetSavedSetting 1009L
	#define kcbStringToAngleN 124L
	#define kcbStringToDouble 367L
	#define kcbSymbolContainsLight 355L
	#define kcbToggleObjectHighlight 672L
	#define kcbUnregisterNotificationProcedure 670L
	#define kcbVerifyPluginLibrary 668L


///////////////////////////////////////////
//  View Manipulation
///////////////////////////////////////////


	#define kcbGetPerspectiveInfo 179L
	#define kcbGetProjection 180L
	#define kcbGetRenderMode 181L
	#define kcbGetScreenDPI 368L
	#define kcbGetViewCenter 172L
	#define kcbGetViewMatrix 53L
	#define kcbGetWorkingPlane 185L
	#define kcbNewCurrentViewMatrix 54L
	#define kcbNewWorkingPlane 184L
	#define kcbPreviewDrawFrame 140L
	#define kcbPreviewFinish 141L
	#define kcbPreviewSetup 139L
	#define kcbRedrawRect 176L
	#define kcbSetViewCenter 101L
	#define kcbSetViewMatrix 142L
	#define kcbSetWorkingPlaneAxis 182L
	#define kcbSetWorkingPlaneVertex 183L
	#define kcbSetZoomFactorN 100L
	#define kcbViewRotWorldZN 55L
	#define kcbWorldRect2ViewRect 837L


///////////////////////////////////////////
//  Walls
///////////////////////////////////////////


	#define kcbAddBreak 193L
	#define kcbDeleteBreak 192L
	#define kcbForEachBreak 191L
	#define kcbGetLayerDeltaZOffset 1305L
	#define kcbGetLinkHeightToLayerDeltaZ 1303L
	#define kcbGetPolyBreakGeometry 824L
	#define kcbGetWallCaps 1307L
	#define kcbGetWallCapsOffsets 1309L
	#define kcbGetWallHeights 295L
	#define kcbJoinWalls 827L
	#define kcbMoveWallByOffset 826L
	#define kcbReverseWallSides 828L
	#define kcbSetAsPolyBreak 825L
	#define kcbSetBreak 194L
	#define kcbSetLayerDeltaZOffset 1306L
	#define kcbSetLinkHeightToLayerDeltaZ 1304L
	#define kcbSetWallCaps 1308L
	#define kcbSetWallCapsOffsets 1310L
	#define kcbSetWallHeights 296L
	#define kcbSetWallStyle 1119L
	#define kcbSetWallWidth 196L
	#define kcbWrapGetWallWidth 573L


///////////////////////////////////////////
//  Windows
///////////////////////////////////////////


#if _WINDOWS
	#define kcbEnterMoveableWindow 331L
#endif
#if _WINDOWS
	#define kcbExitMoveableWindow 332L
#endif
#if _WINDOWS
	#define kcbGetMainHWND 333L
#endif
	#define kcbGetScreenSize 52L


///////////////////////////////////////////
//  Worksheets
///////////////////////////////////////////


	#define kcbAutoFitWorksheetRowHeights 1100L
	#define kcbClearWorksheetCells 757L
	#define kcbCreateWorksheet 47L
	#define kcbCreateWorksheetImage 56L
	#define kcbDeleteWorksheetColumns 742L
	#define kcbDeleteWorksheetRows 740L
	#define kcbGetTopVisibleWorksheet 718L
	#define kcbGetWkSheetSubrowCellActualString 1373L
	#define kcbGetWorksheetCellAlignment 726L
	#define kcbGetWorksheetCellBorder 738L
	#define kcbGetWorksheetCellFill 1110L
	#define kcbGetWorksheetCellFormula 724L
	#define kcbGetWorksheetCellNumberFormat 728L
	#define kcbGetWorksheetCellString 722L
	#define kcbGetWorksheetCellTextFormat 736L
	#define kcbGetWorksheetCellTextAngle 1106L
	#define kcbGetWorksheetCellTextColor 1108L
	#define kcbGetWorksheetCellValue 723L
	#define kcbGetWorksheetCellVertAlignment 1102L
	#define kcbGetWorksheetCellWrapTextFlag 1104L
	#define kcbGetWorksheetColumnOperators 734L
	#define kcbGetWorksheetColumnWidth 732L
	#define kcbGetWorksheetFromImage 730L
	#define kcbGetWorksheetImage 712L
	#define kcbGetWorksheetMergedCellRange 1272L
	#define kcbGetWorksheetPlacement 715L
	#define kcbGetWorksheetRowColumnCount 717L
	#define kcbGetWorksheetRowHeight 731L
	#define kcbGetWorksheetRowHLockState 1099L
	#define kcbGetWorksheetSelection 744L
	#define kcbGetWorksheetSubrowCellString 754L
	#define kcbGetWorksheetSubrowCellValue 755L
	#define kcbGetWorksheetSubrowCount 751L
	#define kcbGetWSCellAllBorders 1281L
	#define kcbInsertWorksheetColumns 743L
	#define kcbInsertWorksheetRows 741L
	#define kcbIsValidWorksheetCell 747L
	#define kcbIsValidWorksheetRange 748L
	#define kcbIsValidWorksheetSubrowCell 750L
	#define kcbIsWorksheetCellNumber 720L
	#define kcbIsWorksheetCellString 721L
	#define kcbIsWorksheetDatabaseRow 749L
	#define kcbIsWorksheetSubrowCellNumber 752L
	#define kcbIsWorksheetSubrowCellString 753L
	#define kcbIsWorksheetVisible 714L
	#define kcbRecalculateWorksheet 227L
	#define kcbSetTopVisibleWorksheet 719L
	#define kcbSetWorksheetCellAlignment 727L
	#define kcbSetWorksheetCellBorder 739L
	#define kcbSetWorksheetCellBorders 1111L
	#define kcbSetWorksheetCellFill 1109L
	#define kcbSetWorksheetCellFormula 725L
	#define kcbSetWorksheetCellNumberFormat 729L
	#define kcbSetWorksheetCellTextFormat 737L
	#define kcbSetWorksheetCellTextAngle 1105L
	#define kcbSetWorksheetCellTextColor 1107L
	#define kcbSetWorksheetCellVertAlignment 1101L
	#define kcbSetWorksheetCellWrapTextFlag 1103L
	#define kcbSetWorksheetColumnOperators 735L
	#define kcbSetWorksheetColumnWidth 733L
	#define kcbSetWorksheetCurrentCell 746L
	#define kcbSetWorksheetPlacement 716L
	#define kcbSetWorksheetRowsHeight 1098L
	#define kcbSetWorksheetSelection 745L
	#define kcbSetWSCellAllBorders 1280L
	#define kcbSetWSCellBottomBorder 1275L
	#define kcbSetWSCellInsideHorizBorder 1277L
	#define kcbSetWSCellInsideVertBorder 1278L
	#define kcbSetWSCellLeftBorder 1274L
	#define kcbSetWSCellOutlineBorder 1279L
	#define kcbSetWSCellRightBorder 1276L
	#define kcbSetWSCellTopBorder 1273L
	#define kcbShowWorksheet 713L
	#define kcbShowWorksheetDialog 756L
	#define kcbWorksheetMergeCells 1270L
	#define kcbWorksheetSplitCells 1271L


///////////////////////////////////////////
//  Workspaces
///////////////////////////////////////////


	#define kcbCloseResFile 449L
	#define kcbGetCurrentWorkspaceFile 447L
	#define kcbOpenExternalResFile 451L
	#define kcbOpenWorkspaceResFile 448L
	#define kcbSetWorkspaceFileToReload 446L
	#define kcbWSAddMenu 1324L
	#define kcbWSAddMenuItem 1323L
	#define kcbWSAddTool 1327L
	#define kcbWSAddToolPalette 1331L
	#define kcbWSAddToolSet 1328L
	#define kcbWSGetVersion 1322L
	#define kcbWSMenuAddMenuItem 1325L
	#define kcbWSMenuBarAddMenu 1326L
	#define kcbWSOpen 1320L
	#define kcbWSPaletteGetHomeCorner 1334L
	#define kcbWSPaletteSetHomeCorner 1333L
	#define kcbWSSetVersion 1321L
	#define kcbWSToolPaletteAddToolSet 1332L
	#define kcbWSToolSetAddTool 1329L
	#define kcbWSToolSetAddToolChildToTool 1330L




//////////////////////////////////////////////////////////////////////////////////////////
#if GS_SDK_VW8_COMPATIBLE
// Inlined obsolete version 8.* callbacks.

inline void GS_COMPATIBILITY GS_GetWorksheetSize(CallBackPtr cbp, MCObjectHandle worksheet, short& rows, short& cols)
{
	GS_GetWorksheetRowColumnCount (cbp, worksheet, rows, cols);
}

inline void GS_COMPATIBILITY GS_GetCellFormula(CallBackPtr cbp, MCObjectHandle worksheet, ViewPt c, Str255 formula)
{
	GS_GetWorksheetCellFormula (cbp, worksheet, c, formula);
}

inline void GS_COMPATIBILITY GS_SetCellFormat(CallBackPtr cbp, MCObjectHandle worksheet, ViewPt c, 
	CBSignedShort numForm, CBSignedShort numAcc, CBSignedShort align, const unsigned char * leader, 
	const unsigned char * trailer)
{
	if (align == 2) align = kTextRightJustify;
	else if (align == 3) align = kTextCenterJustify;

	GS_SetWorksheetCellNumberFormat (cbp, worksheet, c, c, numForm, numAcc, leader, trailer);
	GS_SetWorksheetCellAlignment (cbp, worksheet, c, c, align);
}

inline void GS_COMPATIBILITY GS_GetCellFormat(CallBackPtr cbp, MCObjectHandle worksheet, ViewPt c, 
	short& numForm, short& numAcc, short& align, TXString & leader, TXString & trailer)
{
	GS_GetWorksheetCellNumberFormat (cbp, worksheet, c, numForm, numAcc, leader, trailer);
	GS_GetWorksheetCellAlignment (cbp, worksheet, c, align);

	if (align == kTextRightJustify) align = 2;
	else if (align == kTextCenterJustify) align = 3;
}

inline void GS_COMPATIBILITY GS_SetCellBorder(CallBackPtr cbp, MCObjectHandle worksheet, ViewPt c, CBBoolean left, CBBoolean top, CBBoolean right, CBBoolean bottom)
{
	GS_SetWorksheetCellBorder (cbp, worksheet, c, c, top, left, bottom , right, false);
}

inline void GS_COMPATIBILITY GS_GetCellBorder(CallBackPtr cbp, MCObjectHandle worksheet, ViewPt c, Boolean& left, Boolean& top, Boolean& right, Boolean& bottom)
{
	GS_GetWorksheetCellBorder (cbp, worksheet, c, top, left, bottom, right);
}

inline void GS_COMPATIBILITY GS_SetColumnWidth(CallBackPtr cbp, MCObjectHandle worksheet, CBSignedShort column, CBSignedShort colWidth)
{
	GS_SetWorksheetColumnWidth (cbp, worksheet, column, column, colWidth);
}

inline void GS_COMPATIBILITY GS_GetColumnWidth(CallBackPtr cbp, MCObjectHandle worksheet, CBSignedShort column, short& colWidth)
{
	GS_GetWorksheetColumnWidth (cbp, worksheet, column, colWidth);
}

inline void GS_COMPATIBILITY GS_SetCellTextFormatN(CallBackPtr cbp, MCObjectHandle worksheet, ViewPt c, CBSignedShort fontIndex, CBSignedShort size, CBSignedShort style)
{
	GS_SetWorksheetCellTextFormat (cbp, worksheet, c, c, fontIndex, size, style);
}

inline void GS_COMPATIBILITY GS_GetCellTextFormatN(CallBackPtr cbp, MCObjectHandle worksheet, ViewPt c, short& fontIndex, short& size, short& style)
{
	GS_GetWorksheetCellTextFormat (cbp, worksheet, c, fontIndex, size, style);
}

inline void GS_COMPATIBILITY GS_SetWorksheetWindow(CallBackPtr cbp, MCObjectHandle worksheet, CBBoolean open, const ViewRect& windowPos)
{
	bool bVisible = GS_IsWorksheetVisible (cbp, worksheet);
	
	if ((bVisible && open) || (!bVisible && !open)) {
		GS_SetWorksheetPlacement (cbp, worksheet, windowPos);
	}
	else if (bVisible && !open) {
		GS_ShowWorksheet (cbp, worksheet, false);
		GS_SetWorksheetPlacement (cbp, worksheet, windowPos);
	}
 	else if (!bVisible && open) {
		GS_SetWorksheetPlacement (cbp, worksheet, windowPos);
		GS_ShowWorksheet (cbp, worksheet, false);
	}
}

inline void GS_COMPATIBILITY GS_GetWorksheetWindow(CallBackPtr cbp, MCObjectHandle worksheet, Boolean& open, ViewRect& windowPos)
{
	GS_GetWorksheetPlacement (cbp, worksheet, windowPos);
	open = GS_IsWorksheetVisible (cbp, worksheet);
}

inline void GS_COMPATIBILITY GS_SetColumnOperators(CallBackPtr cbp, MCObjectHandle worksheet, CBSignedShort row, CBSignedShort sort1, CBSignedShort sort2, CBSignedShort sort3, CBSignedShort sum1,  CBSignedShort sum2,  CBSignedShort sum3)
{
	GS_SetWorksheetColumnOperators (cbp, worksheet, row, sort1, sort2, sort3, sum1, sum2, sum3);
}

inline void GS_COMPATIBILITY GS_GetColumnOperators(CallBackPtr cbp, MCObjectHandle worksheet, CBSignedShort row, short& sort1, short& sort2, short& sort3, short& sum1, short& sum2, short& sum3)
{
	GS_GetWorksheetColumnOperators (cbp, worksheet, row, sort1, sort2, sort3, sum1, sum2, sum3);
}

inline void GS_COMPATIBILITY GS_DeleteRows(CallBackPtr cbp, MCObjectHandle w, CBSignedShort startRow, CBSignedShort numRows)
{
	GS_DeleteWorksheetRows (cbp, w, startRow, numRows);
}

inline void GS_COMPATIBILITY GS_AddRows(CallBackPtr cbp, MCObjectHandle w, CBSignedShort beforeRow, CBSignedShort numRows)
{
	GS_InsertWorksheetRows (cbp, w, beforeRow, numRows);
}

inline void GS_COMPATIBILITY GS_DeleteColumns(CallBackPtr cbp, MCObjectHandle w, CBSignedShort startColumn, CBSignedShort numColumns)
{
	GS_DeleteWorksheetColumns (cbp, w, startColumn, numColumns);
}

inline void GS_COMPATIBILITY GS_AddColumns(CallBackPtr cbp, MCObjectHandle w, CBSignedShort beforeColumn, CBSignedShort numColumns)
{
	GS_InsertWorksheetColumns (cbp, w, beforeColumn, numColumns);
}

inline CBBoolean GS_COMPATIBILITY GS_GetCellValueN(CallBackPtr cbp, MCObjectHandle worksheet, ViewPt c, double_gs& cellValue)
{
	GS_GetWorksheetCellValue (cbp, worksheet, c, cellValue);
	return GS_IsWorksheetCellNumber (cbp, worksheet, c);
}


inline CBBoolean GS_COMPATIBILITY GS_GetCellString(CallBackPtr cbp, MCObjectHandle worksheet, ViewPt c, Str255 cellStr)
{
	GS_GetWorksheetCellString (cbp, worksheet, c, cellStr);
	return GS_IsWorksheetCellString (cbp, worksheet, c);
}

inline MCObjectHandle GS_COMPATIBILITY GS_GetActiveWorksheet(CallBackPtr cbp)
{
	return GS_GetTopVisibleWorksheet (cbp);
}

#endif // GS_SDK_VW8_COMPATIBLE
//////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//	VW 12 APIs using Color Table indices of type BYTE produce link errors and must be changed to use 
//	new ColorRef type.
void GS_ColorIndexToRGB(CallBackPtr cbp, Byte colorIndex, RGBColor& rgb);
MCObjectHandle GS_CreateHatch(CallBackPtr cbp, const InternalName& inName, CBBoolean inUsePageUnits, CBBoolean inRotateInWalls, CBBoolean inRotateInSymbols, CBBoolean inTransparent, Byte inFillColorIndex);
CBBoolean GS_GetHatchLevel(CallBackPtr cbp, MCObjectHandle inHatchDef, CBSignedShort inLevel, WorldPt& outStartPt, WorldPt& outRepeatVec, double& outDashFactor, WorldPt& outOffsetVec, Byte& outColorIndex, short& outMilsLineWeight);
void GS_RGBToColorIndex(CallBackPtr cbp, const RGBColor& rgb, Byte& colorIndex);
CBBoolean GS_SetHatchLevel(CallBackPtr cbp, MCObjectHandle inHatchDef, CBSignedShort inLevel, const WorldPt& inStartPt, const WorldPt& inRepeatVec, CBDouble_param inDashFactor, const WorldPt& inOffsetVec, Byte inColorIndex, CBSignedShort inMilsLineWeight);
void GS_GetTextColor(CallBackPtr cbp, MCObjectHandle textBlock, Sint32 charNum, Byte& charColor);
void GS_SetTextColor(CallBackPtr cbp, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, Byte charColor);
void GS_GetWorksheetCellFill(CallBackPtr cbp, MCObjectHandle worksheet, const ViewPt& cell, short& style, Byte& bgcolor, Byte& fgcolor, short& fillpattern);
void GS_GetWorksheetCellTextColor(CallBackPtr cbp, MCObjectHandle worksheet, const ViewPt& cell, Byte& color);
void GS_SetWorksheetCellFill(CallBackPtr cbp, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBSignedShort style, Byte bgcolor, Byte fgcolor, CBSignedShort fillpattern);
void GS_SetWorksheetCellTextColor(CallBackPtr cbp, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Byte color);



////////////////////////////////////////////////////////////////////////////////////////
//
//	
//	APP_API is provided to encourage the development of VectorWorks SDK APIs.  
//
//	Internal developers can use APP_API_## to declare APIs without the need to commit to 
//	an officail/published SDK API.  I


//	Use APP_API_FUNCTION for APIs with a return value
#define APP_API_FUNCTION(returnType,_GS_declare_, _CB_declare_, _CB_call_) \
														\
	extern "C" { returnType _CB_declare_; }\
	inline returnType _GS_declare_ { return _CB_call_; }

//	Use APP_API_PROCEDURE for void APIs
#define APP_API_PROCEDURE(GS_declare_, CB_declare_, CB_call_) \
														\
	extern "C" { void CB_declare_; }\
	inline void GS_declare_ { CB_call_; }
//
////////////////////////////////////////////////////////////////////////////////////////

//
//	SDK APIs waiting to be published for external use.

//	The FreehandInteractive APIs below are used to produce the interactive behavior of the lasso
//	selection of the cursor tools.  It is also used by the multiple reshape tool and Revision cloud
//	tool.

APP_API_FUNCTION(MCObjectHandle,
		GS_CreateSectionLineInstance(CallBackPtr, MCObjectHandle inSectionView),
	 	CB_CreateSectionLineInstance(MCObjectHandle inSectionView), 
	 	CB_CreateSectionLineInstance(inSectionView))	
	//	Call CreateSectionLineInstance to create a the section line instance.  The instance is NOT inserted into the drawing

APP_API_FUNCTION(Boolean,
		GS_IsSectionLineLinkedToViewport(CallBackPtr, MCObjectHandle inSectionLine),
	 	CB_IsSectionLineLinkedToViewport(MCObjectHandle inSectionLine), 
	 	CB_IsSectionLineLinkedToViewport(inSectionLine))	
	//	Call IsSectionLineLinkedToViewport returns true if the specified object is a section line linked to a viewport

APP_API_FUNCTION(Boolean,
		GS_IsDetailCalloutLinkedToViewport(CallBackPtr, MCObjectHandle inDetailCallout),
	 	CB_IsDetailCalloutLinkedToViewport(MCObjectHandle inDetailCallout), 
	 	CB_IsDetailCalloutLinkedToViewport(inDetailCallout))	
	//	Call IsDetailCalloutLinkedToViewport returns true if the specified object is a section line linked to a viewport

// FREEHAND INTERACTIVE
APP_API_PROCEDURE( 
		GS_BeginFreehandInteractive(CallBackPtr),
	 	CB_BeginFreehandInteractive(), 
	 	CB_BeginFreehandInteractive())	
	//	Call BeginFreehandInteractive to switch the current tool state to follow freehand interactive behaviors
	//	This global state forced the tool to observe two point tool status while accumulating the mouse motion in
	//	a kPolyGon object returned by GS_EndFreehandInteractive.

APP_API_PROCEDURE( 
		GS_CancelFreehandInteractive(CallBackPtr),
	 	CB_CancelFreehandInteractive(), 
	 	CB_CancelFreehandInteractive())
	 //	Tool must call GS_CancelFreehandInteractive to return the tool system back to its normal state.

APP_API_PROCEDURE( 
		GS_UpdateFreehandInteractive(CallBackPtr),
	 	CB_UpdateFreehandInteractive(), 
	 	CB_UpdateFreehandInteractive())
	//	Call from ToolMessage::kAction_MouseMove handler to update FreehandInteractive state

APP_API_PROCEDURE( 
		GS_SetFreehandInteractivePenStyle(CallBackPtr, short inStyle),
	 	CB_SetFreehandInteractivePenStyle(short inStyle), 
	 	CB_SetFreehandInteractivePenStyle(inStyle))
	
APP_API_PROCEDURE( 
		GS_SetFreehandInteractivePen(CallBackPtr, short inStyle, short inPenSize, GSColor foreColor, GSColor backColor),
	 	CB_SetFreehandInteractivePen(short inStyle, short inPenSize, GSColor foreColor, GSColor backColor), 
	 	CB_SetFreehandInteractivePen(inStyle, inPenSize, foreColor, backColor))
	
APP_API_PROCEDURE( 
		GS_DrawFreehandInteractive(CallBackPtr),
	 	CB_DrawFreehandInteractive(), 
	 	CB_DrawFreehandInteractive())
	//	Call from ToolMessage::kAction_Draw handler to draw FreehandInteractive sample polygon.  

APP_API_FUNCTION(MCObjectHandle,
		GS_GetFreehandInteractivePoly(CallBackPtr),
	 	CB_GetFreehandInteractivePoly(), 
	 	CB_GetFreehandInteractivePoly())

APP_API_FUNCTION(MCObjectHandle,
		GS_EndFreehandInteractive(CallBackPtr),
	 	CB_EndFreehandInteractive(), 

	 	CB_EndFreehandInteractive())
	//	Call GS_EndFreehandInteractive from the tool's ToolCompleteMessage::kAction handler.  The MCObjectHandle will
	//	contain a polygon holding the points sampled as the user moved the mouse.



//	---------------------------------------------------------------------------------------
//	---------------------------------------------------------------------------------------

//	DisplayImagePopup parameter
struct TDisplayImageListInfo {
	TDisplayImageListInfo(){ fSizeType = kStandardSize; fImageSpecArray = nullptr; }
	Sint32				fNumItems;
	Sint32*				fIndexArray;
	short*				fFileRefArray;
	Boolean*			fIsSeparatorArray;
	TXStringArray		fNameArray;
	TXString*			fImageSpecArray;
	Sint32				fSelectedItem;
	ThumbnailSizeType	fSizeType;
	TXString			fCategoryTitle;
	TXStringArray		fCategoryArray;
	size_t				fCategorySelIndex;
};

//Sint32 DisplayImagePopup (TDisplayImageListInfo& imageInfo, Sint32 top, Sint32 left, Sint32 bottom, Sint32 right);
APP_API_FUNCTION(Sint32, 
		GS_DisplayImagePopup(CallBackPtr, TDisplayImageListInfo& imageInfo, Sint32 top, Sint32 left, Sint32 bottom, Sint32 right),
	 	CB_DisplayImagePopup(TDisplayImageListInfo& imageInfo, Sint32 top, Sint32 left, Sint32 bottom, Sint32 right), 
	 	CB_DisplayImagePopup(imageInfo, top, left, bottom, right))

//====================================================================================================
//	STRUCTS
//
//	Structure definitions that coorespond to custom resource templates in GSTMPL.rsrc
//
//====================================================================================================

//--------------------------------------------------
//	'Prm#'	Parameter resource.
//--------------------------------------------------
#define OST_Prm							'Prm#'
const short kUnivParmResID				= 128;

// UnivParmSpec is the repeating part of the 'Prm#' resource in memory.
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
struct UnivParmSpec {
	Str63	fUniversalName;		// Universal Name of a Parameter.  Limited to 20 characters as of VW 10.
	Str63	fLocalizedName;		// Localized Name of a Parameter.  Supports up to 63 characters.
	Str255	fDefaultValue;		// Default value for this parameter.  If text, it is Localized.
	Byte	fPad;				// pad byte
	Byte	fType;				// Type of this parameter.  Constants define in MiniCadCallBacks.h
	short 	fChoices;			// For parameters of type Popup or Radio, this is the resource ID of possible choices.
};
#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
//--------------------------------------------------------------------

typedef struct UnivParmSpec UnivParmSpec, *UnivParmSpecPtr;
typedef UnivParmSpec UnivParmSpecArray[1];

// UnivParmTable is an entire 'Prm#' resource in memory.  Call GetResource and assign resulting handle to a UnivParmTabHandle.
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
struct UnivParmTable {
	short 				numParms;		// number of entries in the following array.
	UnivParmSpecArray	parms;			// array of UnivParmSpec structs
};
#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
//--------------------------------------------------------------------

typedef struct UnivParmTable *UnivParmTabPtr, **UnivParmTabHandle;


//--------------------------------------------------
//	'Chc#'	Choice resource stores choices for popup and radio button parameter.
//--------------------------------------------------
#define OST_Chc								'Chc#'
// The resource id of the Chc# resource is specified in the fChoices field of a Prm# resource for a specific parameter.

// The "ParmChoice" structure describes one entry in a 'Chc#' resource.  It contains a pair of names.
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
struct ParmChoice {
	Str255	fUniversalChoiceName;		// Universal Name of a Popup or Radio choice.
	Str255	fLocalizedChoiceName;		// Localized Name of a Popup or Radio choice.
};
#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
//--------------------------------------------------------------------

typedef struct ParmChoice ParmChoice, *ParmChoicePtr;
typedef ParmChoice ParmChoiceArray[1]; 

// The "ParmChoiceTable" structure describes the entire 'Chc#' resource in memory.   Call GetResource and assign resulting handle to a ParmChoiceTabHandle.
//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
struct ParmChoiceTable {
	short 				numChoices;		// number of entries in the following array.
	ParmChoiceArray		choices;		// array of ParmChoice structs.
};
#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (RESOURCES)
//--------------------------------------------------------------------

typedef struct ParmChoiceTable *ParmChoiceTabPtr, **ParmChoiceTabHandle;
