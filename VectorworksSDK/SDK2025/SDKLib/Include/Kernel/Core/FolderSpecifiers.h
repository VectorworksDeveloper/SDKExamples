//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

typedef Sint32 FolderSpecifier;

// The name of these constants used to reflect their folder hierarchy but content was
// rearranged in 2023 and since constants are already in use, they were not changed
// except where necessary (e.g. when one folder was split into several).

enum EFolderSpecifier {
	kRootFolderSpecifier	= 0,
	kApplicationFolder		= 1,
	kExternalsFolder		= 2,
	kExternalDataFolder		= 3,
	kWorkspacesFolder		= 4,
	kOverlaysFolder			= kWorkspacesFolder,
	kParametricsFolder		= 5,
	kDebugtoolsFolder		= 6,
	kTemplatesFolder		= 7,
	kStandardsFolder		= 8,
	kHelpFolder				= 9,
	kDictionariesFolder		= 10,
	kObjectLibrariesFolder  = 11,
	kAppDataFolder			= 12,
	kLibrariesFolder		= 13,
	kDefaultsFolder			= 14,
	kSettingsFolder			= 15,
	// New top-level folders added at end
	kObjectsImperialFolder	= 16,
	kObjectsMetricFolder	= 17,
	kPDFResourcesFolder		= 18,
	kCommonFolder			= 19,
	kCommonDataFolder		= 20,
	kCommonIncludesFolder   = 21,
	kCommonInterfacesFolder = 22,
	kFavoritesFolder		= 23,
	kIconsFolder			= 24,
	kTemplatesArchitectFolder = 25,
	kTemplatesLandmarkFolder = 26,
	kTemplatesSpotlightFolder = 27,
	kTemplatesMachineDesignFolder = 28,
	kTemplatesConnectCADFolder = 29,
	
	k_RESERVED_INTERNAL_OLDTemp = 68,		// not for use by SDK developers
	k_RESERVED_INTERNAL_OLDStan = 69,		// not for use by SDK developers
	k_RESERVED_INTERNAL_OLDEvntLyt = 139, // not for use by SDK developers

	kDefaultTexturesFolder			= 100, 
	kDefaultCabinetHandlesFolder	= 101,
	kDefaultDoorHardwareFolder		= 102,
	kDefaultGradientsFolder			= 103, 
	kDefaultHardscapeHatchesFolder	= 104,
	kDefaultHatchesFolder			= 105, 
	kDefaultImageFillsFolder		= 106, 
	kDefaultPlantsFolder			= 107, 
	kDefaultToiletsFolder			= 108,
	kDefaultRWBackgroundsFolder		= 109,	
	kDefaultSeatingLayoutFolder		= 110,
	kDefaultTileSymbolsFolder		= 111,
	kDefaultHumanFigTexturesFolder	= 112,
	kDefaultStairsFolder			= 114,
	kDefaultTitleBlocksFolder		= 115,
	kDefaultSectionMarkersFolder	= 116,
	kDefaultRepetitiveUnitFolder	= 117,
	kDefaultDoorCustomLeavesFolder	= 118,
	kDefaultLightingGobosFolder		= 119,
	kDefaultReportsFolder			= 120,
	kDefaultPlants2DSymbolsFolder	= 122,
	kDefaultPlants3DSymbolsFolder	= 123,
	kDefaultPlantsHatchesFolder		= 124,
	kDefaultRepetitiveFlooringFolder = 125,
	kDefaultRepetitiveFramingFolder = 126,
	kDefaultRepetitiveMasonryFolder	= 127,
	kDefaultRepetitiveMiscFolder	= 128,
	kDefaultRepetitiveRoofingFolder = 129,
	kDefaultRepetitiveSidingFolder	= 130,
	kDefaultWallSlabRoofHatchesFolder	= 131,
	kDefaultWallSlabRoofTexturesFolder	= 132,
	kDefaultWindowCustomShuttersFolder = 133,
	kDefaultSketchStylesFolder		= 134,
	kDefaultPlantListFolder			= 135,
	kDefaultPlantDatabaseFolder		= 136,
	kDefaultColorPalettesFolder		= 137,
	kDefaultFramingMemberProfileFolder = 138,
	kDefaultSpacesOccupantOrgFolder = 140,
	kDefaultSpacesNameListsFolder	= 141,
	kDefaultStructuralShapesFolder	= 142,
	kDefaultLandmarkSchedules		= 143,
	kDefaultVideoScreenFolder		= 144,
	kDefaultVSCasingsCRT43			= 145,
	kDefaultVSCasingsCRT169			= 146,
	kDefaultVSCasingsFlat43			= 147,
	kDefaultVSCasingsFlat169		= 148,
	kDefaultVSCasingsCRTCurved43	= 149,
	kDefaultVSScreenImages			= 150,
	kDefaultVSProjectorModels		= 151,
	kDefaultVSStandModels			= 152,

	kDefaultEventPlanningFolder		= 154,
	kDefaultEPRoom					= 155,
	kDefaultEPStage					= 156,
	kDefaultEPLectern				= 157,
	kDefaultEPScreen				= 158,
	kDefaultEPSeating				= 159,
	kDefaultEPStep					= 160,
	kDefaultCustomStair				= 161,
	kDefaultCustomStairStringers	= 162,
	kDefaultTilesFolder				= 163,		
	kDefaultTextStylesFolder    	= 164,
	kDefaultFocusPointGraphics		= 165,
	kRenderworksFolder				= 166,
	kDefaultExistingTreeFolder		= 167,
	kDefaultHeliodonFolder			= 168,
	kDefaultHeliodonSymbolsFolder	= 169,
	kDefaultHeliodonCitiesFolder	= 170,
	kDefaultRenderStylesFolder		= 171,		
	kDefaultStorySupportFolder		= 172,
	kDefaultDetailMarkersFolder		= 173,
	kDefaultLineTypesFolder			= 174,		
	kDefaultAudioToolsFolder		= 175,
	kAudioBumpersFolder				= 176,		
	kAudioSpeakersFolder			= 177,		
	kExtrasFolder					= 178,
	kSamplesFolder					= 179,
	kDefaultParkingSpaceFolder		= 180,
	kDefaultSpotlightSchedules		= 181,
    kDefaultWorkspacesFolder        = 182,
	kDefaultNotesFolder				= 183,
	kDefaultEnergyAnalysisFolder			= 187,
	kHoistToolsFolder				        = 188,
	kAccessorySymbolsFolder					= 189, 
	kEntertainmentLightingFolder			= 190,
	kDefaultMarionetteFolder				= 191,
	kDefaultMarionetteAttributesFolder		= 192,
	kDefaultMarionetteMathFolder			= 193,
	kDefaultMarionetteObjectsFolder			= 194,
	kDefaultMarionetteObjectsNurbsFolder	= 195,
	kDefaultMarionetteTexturesFolder		= 196,
	kDefaultRecordFormatsFolder				= 197,
	kDefaultIrrigationFolder				= 198,
	kDefaultTagLabelFolder					= 199,
	kDefaultSpotlightStageFolder			= 200,

	kDefaultInteriorElevationMarkersFolder	= 202,
	kDefaultSoftGoodsTexturesFolder			= 203,
	kDefaultRailingFenceFolder				= 204,
	kDefaultRailingFenceProfilePostFolder	= 205,
	kDefaultRailingFenceProfileTopRailFolder = 206,
	kDefaultRailingFenceRailingFenceFolder	= 207,
	kDefaultRailingFenceRFFenceFolder		= 208,
	kDefaultRailingFenceRFRailingFolder		= 209,
	kDefaultRailingFenceSymbolPostFolder	= 210,
	kDefaultSlabDrainSymbolsFolder			= 211,
	kDefaultBIMobjectFolder					= 212,
	
	kDefaultCableToolsFolder				= 214,
	kDefaultCableToolsBreakOutLabelsFolder	= 215,
	kDefaultCableToolsMultiHeadSymbolsFolder = 216,

	kObjectStylesFolder						= 217,
	kObjectStylesBathShowerFolder			= 218,		
	kObjectStylesCabinetBaseFolder			= 219,		
	kObjectStylesCabinetUtilityFolder		= 220,		
	kObjectStylesCabinetWallFolder			= 221,		
	kObjectStylesCampanileFolder			= 222, 
	kObjectStylesColumnFolder				= 223, 
	kObjectStylesCommDeviceFolder			= 224,		
	kObjectStylesCompartmentSinkFolder		= 225,		
	kObjectStylesCustomCabinetFolder		= 226,		
	kObjectStylesDeskFolder					= 227,		
	kObjectStylesDoorFolder					= 228,
	kObjectStylesEscalatorFolder			= 229,
	kObjectStylesFireplaceFolder = 230,
	kObjectStylesGrabBarFolder = 231,					
	kObjectStylesHardscapeFolder = 232,					
	kObjectStylesHVACDamperFolder = 233,				
	kObjectStylesHVACDiffuserFolder = 234,				
	kObjectStylesHVACElbowDuctFolder = 235,				
	kObjectStylesHVACFlexDuctFolder = 236,				
	kObjectStylesHVACOutletFolder = 237,				
	kObjectStylesHVACSplitterFolder = 238,				
	kObjectStylesHVACStraightDuctFolder = 239,			
	kObjectStylesHVACTransitionFolder = 240,			
	kObjectStylesHVACVerticalDuctFolder = 241,			
	kObjectStylesHVACVerticalElbowFolder = 242,			
	kObjectStylesIncandescentFixtureFolder = 243,		
	kObjectStylesLandscapeAreaFolder = 244,				
	//lighting accessory and instrument have IDs in default, even though folder was moved to object styles
	kObjectStylesPilasterFolder = 247,
	//plants constant is in defaults even though folder is object styles
	kObjectStylesRampFolder = 248,
	kObjectStylesReceptacleFolder = 249,		
	kObjectStylesShelvingUnitFolder = 250,		
	kObjectStylesSimpleElevatorFolder = 251,
	
	kObjectStylesSwitchFolder = 254,			
	kObjectStylesTablesAndChairsFolder = 255,	
	kObjectStylesToiletStallFolder = 256,
	//walls, roof, slab styles constant is in defaults even though folder is object styles
	kObjectStylesWindowFolder = 257,
	kObjectStylesWorkstationCounterFolder = 258,		
	kObjectStylesWorkstationOverheadFolder = 259,		
	kObjectStylesWorkstationPanelFolder = 260,			
	kObjectStylesWorkstationPedestalFolder = 261,		

	//leaving a numbering gap to allow for more object styles entries; not really necessary, 
	//but it's nice to have same directories together.

	kObjectsEntertainmentStage_EventFolder = 272,		
	kObjectsEntertainmentTrussFolder = 273,				
	// kObjectsLandscapePlantsFolder = 274,				 //Removing this completely. It's content got moved to plant styles and any content that specifies both will have double folder.
	kObjectsLandscapeSiteFolder = 275,					

	kDefaultIrrigationCatalogsFolder = 277,

	kDefaultIrrigationContentControllersFolder = 278,
	kDefaultIrrigationContentOutletsFolder = 279,
	kDefaultIrrigationContentOutletsDripFolder = 280,
	kDefaultIrrigationContentPipesFolder = 281,
	kDefaultIrrigationContentPOCsFolder = 282,
	kDefaultIrrigationContentSysCompsFolder = 283,
	kDefaultIrrigationContentValvesFolder = 284,

	kDefaultIrrigationSymbolsControllersFolder = 285,
	kDefaultIrrigationSymbolsOutletsFolder = 286,
	kDefaultIrrigationSymbolsPOCsFolder = 287,
	kDefaultIrrigationSymbolsSysCompsFolder = 288,
	kDefaultIrrigationSymbolsValvesFolder = 289,

	kDefaultCableToolsMarkerSymbolsFolder = 290,

	kObjectsLandscapeSiteStipplesFolder = 291, 

	kDefaultFoliageFolder = 292,
	kDefaultSpacePlanningFolder = 293,
	kDefaultNorthArrowsFolder = 294,

	kObjectStylesTitleBlockBorderFolder = 300, 

	kSpotlightFolder = 302,
	kSpotlightDataFolder = 303,
	kSpotlightDataBraceworksFolder = 304,
	kSpotlightDataBrackworksCrossSectionFolder = 305,

	kObjectsEntertainmentEventFolder = 306,

	kDefaultHyperlinkFolder = 307,
	kObjectsEntLightingGobos = 308,
	kObjectsLandscapeFurnishings = 309,  

	kObjectStylesDataTagFolder = 310, 

	kDefaultsDeadHangFolder = 311,
	kDefaultsHouseRiggingPointsFolder = 312,
	kDefaultsBridleMaterialsFolder = 313,

	kDefaultCameraSymbolsFolder = 314,
	kDefaultCameraLensSymbolsFolder = 315,
	kDefaultCameraBodySymbolsFolder = 316,
	kDefaultCameraStandSymbolsFolder = 317,

	kDefaultColorSchemesFolder = 318,

	kObjectStylesSeatingSectionFolder = 319,	

	kSpotlightDataGDTFFolder = 320,
	kObjectStylesLightingPipeFolder = 321,	
	kObjectStylesLightingPipeLadderFolder = 322, 
	kObjectsEntertainmentVideoFolder = 323, 

	kObjectsConnectCADFolder = 324, 

	kObjectStylesDrawingLabelFolder = 325,      
	kObjectStylesReferenceMarkerFolder = 326,   
	kObjectStylesInteriorElevationFolder = 327, 
	kObjectStylesSectionElevationLineFolder = 328, 
	kObjectStylesDetailCalloutFolder = 329,    

	kDefaultInventoriesFolder = 330,

	kDefaultMarkersFolder = 331,
	kObjectStylesGridAxisFolder = 332, 
	kObjectStylesRoadway = 333,

	kDefaultConnectCADFolder				= 334,
	kDefaultConnectCADDeviceFolder			= 335,
	kDefaultConnectCADTerminatorFolder		= 336,
	kDefaultConnectCADExternalFolder		= 337,
	kDefaultConnectCADDistributionFolder	= 338,
	kDefaultConnectCADJacksFolder			= 339,
	kDefaultConnectCADPanelsFolder			= 340,
	kDefaultConnectCADSocketFolder			= 341,
	kDefaultConnectCADPanelConnsFolder		= 342, 
	kDefaultConnectCADDataFolder			= 343,
	kDefaultConnectCADReportsFolder			= 344,

	kDefaultMaterialsFolder					= 345, 

	kRenderworksCamerasFolder				= 346,	

	kObjectStylesCableToolsFolder			= 349,	

	kDefaultsHoistOriginFolder				= 351,

	kClassificationsFolder					= 352,

	kDefaultConnectCADDropPointFolder		= 353,
	kObjectStylesDropPointFolder			= 354,	

	kObjectStylesElectricsFolder			= 355,
	kObjectStylesSoftGoodsFolder			= 356,	

	kObjectStylesGraphicLegendFolder		= 357, 

	kDefaultConnectCADAdaptorFolder			= 358,  //Now in Libraries, 2023

	kObjectStylesElevationBenchmarkFolder	= 359, 

	kObjectStylesDataTagSpaceFolder			= 360,
	kDaultTrussCrossFolder					= 361,

	kObjectStylesStructuralMemberFolder		= 362,

   // New folders from content re-organization 2023
   kAnnotationsFolder						= 363,
   kAttributesFolder						= 364,
   kBuildingFolder						    = 365,
   // ConnectCAD already exists as kObjectsConnectCADFolder
   kEntertainmentFolder					    = 366,
   kInteriorFolder							= 367,
   kMEPfolder						        = 368,
   kSiteFolder								= 369,
   kVisualizationFolder					    = 370,

   // For now, we're not adding the black symbol folders (e.g. Fixtures Exterior, Foundations, Roof Access, etc.)

	kAudioControlsFolder					= 377,
	kLightingControlsFolder					= 378,
	kSFXEffectsFolder						= 379,
	kVideoControlsFolder					= 380,
	kVideoEquipFolder						= 381,

	kCabinetStylesFolder					= 382,

	kSpaceStylesFolder						= 384,
	kFurnitureConceptFolder					= 385,

	kHVACFolder								= 386,

	k2DImageryElevArtisitc					= 387,
	k2DImageryElevPhotorealistic			= 388,
	k2DImageryTopPlanArtistic				= 389,
	k2DImageryTopPlanPhotorealistic			= 390,
	k3DImagePropsArtistic					= 391,
	k3DImagePropsPhotorealistic				= 392,

	kWallStylesFolder						= 393,
	kRoofStylesFolder						= 394,
	kSlabStylesFolder						= 395,

	kConnectCADEquipmentItemFolder			= 396, //new for 2023 content reorg
	kLaserFolder                            = 397,
	kSFXFolder                              = 398,
	kPlantLibrariesFolder					= 399,  //this is the libraries/plants folder. The styles folder is the kDefaultPlantsFolder; it was in use prior to 2023 reorg and it pointed to ObjectStyles/Plant
	kDefaultDistributorsFolder			    = 400,	// 2025 this is now the same as kEntertainmentPowerFolder
	kEntertainmentPowerFolder			    = 401,

	kObjectStylesFenceFolder				= 402,
	kObjectStylesRailingFolder				= 403,

	kDefaultRailingFolder					= 404,
	kDefaultRailingBracket3DFolder			= 405,
	kDefaultRailingBracketProfilesFolder	= 406,
	kDefaultRailingPost3DFolder				= 407,
	kDefaultRailingPostProfilesFolder		= 408,
	kDefaultRailingTopRailProfilesFolder	= 409,

	kDefaultFenceFolder						= 410,
	kDefaultFenceGatesFolder				= 411,
	kDefaultFenceInfill3DVerticalFolder		= 412,
	kDefaultFenceInfillPanelsFolder			= 413,
	kDefaultFenceInfillProfilesFolder		= 414,
	kDefaultFencePost3DFolder				= 415,
	kDefaultFencePostCapping3DFolder		= 416,
	kDefaultFencePostProfilesFolder			= 417,
	kDefaultFenceRail3DFolder				= 418,
	kDefaultFenceRailCapping3DFolder		= 419,
	kDefaultFenceRailCappingProfilesFolder	= 420,
	kDefaultFenceRailProfilesFolder			= 421,

	kDefaultFenceInfill3DHorizontalFolder	= 422,
	kDefaultHoistToolsPickupsFolder			= 423,

	kObjectStylesConnectCADPanelLayoutFolder= 424,
	kAnnotationsViewportStylesFolder		= 425,

	kCabinetLegacyStylesFolder				= 426,

	kObjectStylesCurbFolder					= 427,

	kCountertopStylesFolder					= 428,

	kDefaultCountertopFolder						= 429,
	kDefaultCountertopEdgeTreatmentProfilesFolder	= 430,
	kDefaultCountertopTrimProfilesFolder			= 431,
	kDefaultCountertopBacksplashProfilesFolder		= 432,

	kMEPSanitaryFolder							= 433,

	kObjectStylesLabelFormatFolder				= 434,
	kDefaultDoorAndWindowAssemblyFolder			= 435,
	
	// T02470 - Room Finish Improvements
	kDefaultReportsRoomFinishLegendsFolder		= 436,
	kObjectStylesDataTagRoomFinishFolder		= 437,
	
	kDefaultSurveyPointFolder					= 438,
	kDefaultSurveyPointSymbolsFolder			= 439,
	kDefaultSurveyReferencePointSymbolsFolder	= 440,

	kDefaultCurbFolder							= 441,
	kDefaultCurbCurbsAndBordersFolder			= 442,
	kDefaultCurbProfilesFolder					= 443,
	kDefaultCurbCornersFolder					= 444,
	kDefaultCurbInsertionsFolder				= 445,

	kArchitectSchedules							= 446,

};

