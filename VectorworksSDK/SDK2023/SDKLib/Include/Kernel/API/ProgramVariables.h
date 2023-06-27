//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

//////////////////////////////////////////////////////////////////////////////////////////
// Selectors for GetProgramVariable and SetProgramVariable
enum {

	// -------------------------------------------------------------------------
	// Boolean selectors - All public for VS use
	varClickDrag          =  0,	
	varOffsetDups         =  1,
	varFullCursor         =  2,
	varShowHints          =  3,
	varFloatDatum         =  4,
	varSnapToLoci         =  5,
	varShowRulers         =  6,
	varShowScrollBars     =  7,
	varNoFillText         =  8,
	varZoomLineThick      =  9,
	varBWOnly             = 10,
	varUseLayerColor      = 11,
	varTimeLog            = 12,
	varAdjustTextFlip     = 13,
	varShowOthersInGroup  = 14,
	varShow3DAxisLabels   = 15,
	varBlackBackground    = 16,
	varEightSelHandles    = 17,
	varUseSounds          = 18,
	varShowUndoWarnings   = 19,
	varOpaqueHints        = 20,
	varStopVSOnWarnings	  = 21,
	varLeftPaletteMargin  = 22,
	varRightPaletteMargin = 23,
	varSaveReminder		  = 24,
	varShowConstraints	  = 25,          
	varCombineUndoViews	  = 26,     // Sint8        
	varShowAlertsOnModeBar= 27,
	varAssociateDims	  = 28,
	varSpellCheckCapitalizedWords = 29,
	varSpellCheckWordsInAllCaps   = 30,
	varSpellCheckMixedCaseWords   = 31,
	varSpellCheckWordsWithNumbers = 32,
	varWallAutoJoin      = 33,
	varShowPageBreaks    = 34,
	varShowGrid          = 35,
	varPrintGrid         = 36,
	varSnapToGrid        = 37,
	varSnapToObject      = 38,
	varSaveByTime		 = 39,
	varSaveConfirm		 = 40,
	varSaveToBackup		 = 41,
	varExtendedAutoscroll = 42,
	varPaletteDocking	 = 43,
	varCreateDimsInDimClass = 44,
	varUseAcceleratedNavigation	 = 45,
	varUseVectorCaching	 = 46,
	varSketchHiddenLine  = 47,
	varSnapToEdgePoints  = 48,
	varShowPageBoundary  = 49,
	

	// -------------------------------------------------------------------------
	// Numeric selectors
	
	varLineWeightUnit     = 50,     // short - Public for VS
	varLineWeightArray    = 51,     // 6 bytes - For internal use only
	var3DResponse         = 52,     // byte   (1-detailed ... 5-responsive) - Public for VS
	varAltCoordSystemAngle = 53,     // double - Public for VS
	varSnapRad            = 54,     // short - Public for VS
	var2DConvertRes       = 55,     // short - Public for VS
	var3DConvertRes       = 56,     // short - Public for VS
	varTextSize           = 57,     // double (page inches) - Public for VS
	varTextStyle          = 58,     // byte (bit field: bold=1, italic=2, underline=4, outline=8, shadow=16) - Public for VS
	varMaxUndos           = 59,     // short - Public for VS
	varSaveInterval		  = 60,		// short  (number of minutes) - Public for VS
	varDisplayLightObjs	  = 61,		// short  (0-always, 1-wireframe only, 2-never) - Public for VS
	varRetainQD3DModel	  = 62,		// short  (1-never .. 5-always) - Public for VS
	varRotTextDisplay	  = 63,		// short  (0-box, 1-normal, 2-highest quality) - Public for VS
	varDisplayBitMaps	  = 64,		// short  (0-box, 1-low res, 2-full res) - Public for VS
	varDimSlashThick	  = 65,		// byte   (mils) - Public for VS
	// varHiddenLineDashStylE= 66,		// OBSOLETE, was byte (dash style index) - Public for VS. Replaced by varHiddenLineDashType, below. Line type reengineering changed variable to Sint32. 
	varHiddenLineShade	  = 67,		// short  (1-darkest .. 4-lightest) - Public for VS
	varPageOriginX        = 68,     // double - For internal use only
	varPageOriginY        = 69,     // double - For internal use only
	varPhotographicScale  = 70,     // double - Public for VS
	varDimStandard        = 71,     // short - Public for VS
	varDefacetAngle		  = 72,		// double (0-90, for hidden line render) - Public for VS
	varGridAngle          = 73,     // double - Public for VS
	varMoveObjArrow		  = 74,		// short (1-arrow, 2-cmd+arrow, 3-shift+arrow, 4-shift+cmd+arrow, 5-alt+arrow, 0-disabled) - Public for VS
	varNudgeObjArrow	  = 75,		// short (1-arrow, 2-cmd+arrow, 3-shift+arrow, 4-shift+cmd+arrow, 5-alt+arrow, 0-disabled) - Public for VS
	varPanArrow		  	  = 76,		// short (1-arrow, 2-cmd+arrow, 3-shift+arrow, 4-shift+cmd+arrow, 5-alt+arrow, 0-disabled) - Public for VS
	varSwitchSavedView	  = 603,	// short (1-arrow, 2-cmd+arrow, 3-shift+arrow, 4-shift+cmd+arrow, 5-alt+arrow, 0-disabled) - Public for VS
	varSwitchActLCArrow	  = 77,		// short (1-arrow, 2-cmd+arrow, 3-shift+arrow, 4-shift+cmd+arrow, 5-alt+arrow, 0-disabled) - Public for VS
	varGridX			  = 78,		// double, - For internal use only
	varGridY			  = 79,		// double, - For internal use only
	varPageOriginXInCurrUnits = 80,	// double, current units - Public for VS
	varPageOriginYInCurrUnits = 81, // double, current uniits - Public for VS
	varTextJustification  = 82,		// short (1-left, 2-center, 3-right) - Public for VS
	varTextVerticalAlignment = 83,	// short (1-TopBox, 2-TopBaseline, 3-CenterBox, 4-BottomBaseline, 5-BottomBox) - Public for VS
	varTextVerticalSpacing   = 84,	// short (0-CustomLeading, 2-Single, 3-ThreeHalves, 4-Double) - Public for VS
	varTextLeading		     = 85,		// double - Public for VS - Public for VS
	varDefaultCompression    = 86,		// byte (1-JPEG, 2-PNG)  - Public for VS
	varLineWeightArrayCount  = 87,		// byte - Public for VS
	varSoundVolume			 = 88,		// short - Public for VS
	varCustomMoveDistance	 = 89,	// double, the custom distance to move objects, see varUseCustomMoveDistance above - Public for VS
	 
	// -------------------------------------------------------------------------
	varSheetIndividualZoomPan = 90,			// Boolean (whether sheet layers have their own zoom pan) - For internal use only
	varDisplay3DLoci = 91,					// short  (0-always, 1-wireframe only, 2-never) - Public for VS
	varPlanRotated = 92,					// Boolean read only (whether the plan view is rotated) - Public for VS
	varPlanRotationAngle = 93,				// Real : What is the current Plan rotation angle. - Public for VS
	varStackLayers = 94,					// Boolean read-write (gets/sets the stack layers status) - Public for VS
	varStackLayersCreate2DObjects = 95,		// Boolean read-write (gets and sets stack layers option to create 2D objects) - Public for VS
	varStackLayersIgnoreOtherScales = 96,	// Boolean read-write (gets and sets stack layers option to ignore layers with scales different than active layer) - Public for VS
	varStackLayersRestoreViews = 97,		// Boolean read-write (gets and sets stack layers option to restore the original views after unstacking) - Public for VS
	varUseOpenMPMultithreading = 98,		// short (0-no, 1-yes, 2-partial) - Public for VS
	varStackLayersCenterView = 99,			// Boolean read-write (gets and sets stack layers option to center view on active layer) - Public for VS

	// -------------------------------------------------------------------------
	// String selectors
	
	varTextFontName	      = 100,    // TXString - Public for VS

	// -------------------------------------------------------------------------
	varStackLayersShowPageBoundary = 101,			// Boolean read-write (gets and sets stack layers option to display the page boundary) - Public for VS
	varStackLayersOnlyActiveLayer2DObjects = 102,	// Boolean read-write (gets and sets stack layers option to display only active layer 2D objects) - Public for VS
	varStackLayersOnlyStoryLayers = 103,			// Boolean read-write (gets and sets stack layers option to display only story layers) - Public for VS
	varStackLayersStoriesEnabled = 104,				// Boolean read (whether Stories are enabled in the current application) - For internal use only

	varUseOccludedPickingAndSnapping		= 105,	// 
	varEnableXRayMode						= 106,	// Boolean read-write (gets and sets X-Ray mode) - Public for VS
	
	//
	varScaleLayersText						= 107,	// Boolean read-only (gets the Scale text option for layers) - Public for VS
	varHierarchicalClassesInPopups			= 108,	// Boolean read-write (gets and sets hierarchical display for class pop-up menus) - Public for VS
    varSuspendTransactionController         = 109,  // Boolean write-only (suspends or resumes the transaction controller) - For internal use only
    varStandardNamingPermission             = 110,  // Boolean read-only (gets whether the user has permission to edit standard naming, if not puts up alert) - For internal use only
	varSaveExpandStateOfClassesInPopups		= 111,  // Boolean read-only (gets and sets saving expanded/collapsed state for classes in pop-up menus) - Public for VS
	varUndoViewChanges						= 112,	// Boolean read-write (gets and sets whether view changes are undone) - Public for VS
	
	// -------------------------------------------------------------------------
	// Miscellaneous Unit Selectors

	varAngularPrecision	      = 120,   // short - Public for VS
	varAngularUnit		      = 121,   // short (EAngularUnits: kDegrees, kRadians, kGradians) - Public for VS


	// -------------------------------------------------------------------------
	// More Boolean Selectors
	varPerspectiveCropped				= 127,	// Public for VS -- document preference for cropped perspective views
	varNeedPanZoom2D					= 128,	// Public for VS -- runtime preference allowing tools to get old style 2D Pan Zoom when in uncropped perspective views
	varIsResettingPlugInsDuringFileRead	= 129,	// For internal use only
    varEnableVWLibs                     = 130,  // Boolean read/write - Public for VS - Enable Vectorworks Libraries (name change for VW 23)
	varAutoFileExtensionsOnMac			= 131,	// Public for VS
	varUseAdvancedImaging				= 132,	// Public for VS
	varUseAntiAliasing					= 133,	// Public for VS
	varAutoAssociateDims				= 134,	// Public for VS
	varMouseWheelZoom					= 135,	// Public for VS
	varUseCustomMoveDistance			= 136,	// whether or not to use the custom distance when moving objects, see varCustomMoveDistance below - For internal use only
	varPrintPSwithBinary				= 137,	// Some printers fail when sending straight binary data with post script. 1 = true = send binary = default - For internal use only
	varNewDocOnStartup					= 138,	// Public for VS
	varChangeLayerForCreateSimilar		= 139,	// Public for VS
	varDoInvalsDuringSurfaceOperations	= 140,	// For internal use only
	varDoImprintingForMultipleUnion		= 141,  // Get sheets from 2d objects then imprint those sheest on a big sheet
	varShowWatermarks					= 142,	// Public for VS
	varAllowParasolidRollMarkCreation	= 143,  // For internal use only - This should be set to true for performance enhancements involving parasolid operations
	varDoHiddenLineIntersections		= 144,	// Public for VS -- set to have hidden line compute intersections
	varStoryUsingPrefix					= 145,	// Public for VS -- tells whether stories should use prefix or suffix notations for new layers
    varAutoRestoreDoc                   = 146,  // tells whether the Auto restore option for OS Lion is on/off 
	varEnhancedOpenGLPrefsComputed		= 147,  // The enhanced OpenGL prefs are computed when the saved settings have been reset
	varEnhancedOpenGLShadows			= 148,  // This determines which OpenGL Shadows implementation is in use
	varCreatingDetailSectionVP			= 149,	// For internal use

	// -------------------------------------------------------------------------
	// Primary Unit Selectors
	
	varUnit1Fraction          = 150,	// double (WorldCoordsPerDrawing unit [get only]) - Public for VS
	varUnit1Format            = 151,	// short	    ufFeetAndInches, ufDecimal - For internal use only
	varUnit1UnitsPerInch      = 152,	// double - Public for VS - Public for VS
	varUnit1UnitName          = 153,	// TXString - Public for VS
	varUnit1UnitMark          = 154,	// TXString - Public for VS
	varUnit1SUnitMark         = 155,	// TXString - Public for VS
	varUnit1SUnitDivider      = 156,	// TXString - Public for VS
	varUnit1SMultiplier       = 157,	// short - Public for VS
	varUnit1SquareUnitMark    = 158,	// TXString - Public for VS
	varUnit1SquareUnitDiv     = 159,	// Sint32 - Public for VS
	varUnit1CubeUnitMark      = 160,	// TXString - Public for VS
	varUnit1CubeUnitDiv       = 161,	// Sint32 - Public for VS

//	varUnit1DisplayFrac         = 162,	// Sint32   (old name kept for compatibility below this enum)
	varUnit1DecDisplayPrecision = 162,	// Sint32 - Public for VS
	
	varUnit1FlagShowUnits     = 163,	// Boolean - Public for VS
	varUnit1FlagLeading0      = 164,	// Boolean - Public for VS
	varUnit1FlagTrailing0     = 165,	// Boolean - Public for VS
	varUnit1FlagUseMinUnit    = 166,	// Boolean - Public for VS
	varUnit1FlagCustomUnit    = 167,	// Boolean - Public for VS

//	varUnit1FlagShowDecAsFrac = 168,	// Boolean   (old name kept for compatibility below this enum) - Public for VS
	varUnit1FlagDisplayAsFrac = 168,	// Boolean - Public for VS

//	varUnit1DimPrecision      = 169,	// Sint32   (old name kept for compatibility below this enum) - Public for VS
	varUnit1DecDimPrecision   = 169,	// Sint32 - Public for VS
	
	varUnit1Style             = 170,	// short - built-in unit (1 thru 7 based on standard unit pop-up order) - Public for VS

	varUnit1FracDisplayPrecision = 171,	// Sint32 - Public for VS
	varUnit1FracDimPrecision     = 172,	// Sint32 - Public for VS
	varUnit1FlagIsMetric         = 173,	// Boolean - Public for VS
	varUnit1AngularUnit          = 174,	// short (EAngularUnits: kDegrees, kRadians, kGradians) - Public for VS
	varUnit1RoundFracToDecimal   = 175, // Boolean - Public for VS

	varUnit1AreaUnitsPerSquareInch = 176, // double - Public for VS
	varUnit1AreaUnitName		= 177,	// TXString - Public for VS
	varUnit1AreaUnitMark		= 178,	// TXString - Public for VS
	varUnit1AreaDecPrecision	= 179,	// Sint32 - Public for VS
	varUnit1VolumeUnitsPerCubicInch = 180, // double - Public for VS
	varUnit1VolumeUnitName		= 181,	// TXString - Public for VS
	varUnit1VolumeUnitMark		= 182,	// TXString - Public for VS
	varUnit1VolumeDecPrecision	= 183,	// Sint32 - Public for VS
	varUnit1FlagCustomAreaUnit	= 184,	// Boolean - Public for VS
	varUnit1FlagCustomVolumeUnit = 185,	// Boolean - Public for VS
	varUnit1AreaFraction		= 186,	// double	(WorldCoordsSquaredPerDrawing unit [get only]) - Public for VS
	varUnit1VolumeFraction		= 187,	// double	(WorldCoordsCubedPerDrawing unit [get only]) - Public for VS
	varUnit1DisplayRoundingBase	= 188,	// short	(0 = 1, 1 = 2.5, 2 = 5) - Public for VS
	varUnit1DimRoundingBase		= 189,	// short	(0 = 1, 1 = 2.5, 2 = 5) - Public for VS
	varUnit1DimFractionDisplayStyle = 190, //short  (0 = regular style, 1 = diagonal style, 2 = horizontal style)
	varUnit1ShowThousandsSep	= 191,	// Boolean - Public for VS
	varSaveAndRestoreUnit1		= 192,	// Boolean, write only, save or restore DimFormat.

	varUnit1FracDimPrecision_NoDimReset = 193, // Sint32 - Public for VS, write-only
	varUnit1FracDisplayPrecision_NoDimReset = 194, // Sint32 - Public for VS, write-only
	varUnit2UnitsPerInch_NoDimReset = 195, // Extended80  (returned as double!) - Public for VS, write-only
	varUnit2Style_NoDimReset = 196, // short - built-in unit (1 thru 7 based on standard unit pop-up order) - Public for VS, write-only

	// -------------------------------------------------------------------------
	// Belongs in Numeric selectors group but had to assign a new number to it.
	varHiddenLineDashType = 197,     // Sint32 - Public for VS  
	// -------------------------------------------------------------------------
	// Secondary Unit Selectors
	
	varUnit2Fraction          = 200,	// Sint32 - Public for VS
	varUnit2Format            = 201,	// short	   ufFeetAndInches, ufDecimal  - For internal use only
	varUnit2UnitsPerInch      = 202,	// Extended80  (returned as double!) - Public for VS
	varUnit2UnitName          = 203,	// TXString - Public for VS
	varUnit2UnitMark          = 204,	// TXString - Public for VS
	varUnit2SUnitMark         = 205,	// TXString - Public for VS
	varUnit2SUnitDivider      = 206,	// TXString - Public for VS
	varUnit2SMultiplier       = 207,	// short - Public for VS
	varUnit2SquareUnitMark    = 208,	// TXString - Public for VS
	varUnit2SquareUnitDiv     = 209,	// Sint32 - Public for VS
	varUnit2CubeUnitMark      = 210,	// TXString - Public for VS
	varUnit2CubeUnitDiv       = 211,	// Sint32 - Public for VS

//	varUnit2DisplayFrac       = 212,	// Sint32   (old name kept for compatibility below this enum)
	varUnit2DecDisplayPrecision       = 212,	// Sint32 - Public for VS
	
	varUnit2FlagShowUnits     = 213,	// Boolean - Public for VS
	varUnit2FlagLeading0      = 214,	// Boolean - Public for VS
	varUnit2FlagTrailing0     = 215,	// Boolean - Public for VS
	varUnit2FlagUseMinUnit    = 216,	// Boolean - Public for VS
	varUnit2FlagCustomUnit    = 217,	// Boolean - Public for VS

//	varUnit2FlagShowDecAsFrac = 218,	// Boolean   (old name kept for compatibility below this enum)
	varUnit2FlagDisplayAsFrac = 218,	// Boolean - Public for VS

//	varUnit2DimPrecision      = 219,	// Sint32   (old name kept for compatibility below this enum)
	varUnit2DecDimPrecision      = 219,	// Sint32 - Public for VS
	
	varUnit2Style             = 220,	// short - built-in unit (1 thru 7 based on standard unit pop-up order) - Public for VS

	varUnit2FracDisplayPrecision = 221,	// Sint32 - Public for VS
	varUnit2FracDimPrecision     = 222,	// Sint32 - Public for VS
	varUnit2FlagIsMetric         = 223,	// Boolean - Public for VS
	varUnit2AngularUnit          = 224,	// short  (EAngularUnits: kDegrees, kRadians, kGradians) - Public for VS
	varUnit2RoundFracToDecimal   = 225, // Boolean - Public for VS
	varUnit2DimRoundingBase		 = 226,	// short	(0 = 1, 1 = 2.5, 2 = 5) - Public for VS
	varUnit2ShowThousandsSep	 = 227, // Boolean - Public for VS

	// -------------------------------------------------------------------------
	// Product state settings
	
	varRenderWorksEnabled	  = 240,	// Boolean, read only - Public for VS
	varDisableRenderWorks	  = 241,	// Boolean, if TRUE, RenderWorks is disabled for the life of the application - Public for VS
	varBuildingMaterialsEnabled = 242,	// Boolean, if TRUE, building materials is enabled - Public for VS 

	// -------------------------------------------------------------------------
	// Tools:
	
	varToolPenPattern	  		= 250,	// short, pattern index - For internal use only
	varToolPenSize	 	  		= 251,	// short, pixels at one to one - Zoom line pref observed	 - For internal use only
	varAddToolObject	  	  	= 252,	// MCObjectHandle, write only, add Obejct - For internal use only
	varRemoveToolObjects	 	= 253,	// ignored,  - For internal use only
	varAutoScroll	  			= 254,	// Boolean, write only, DisableAutoScroll - For internal use only
	varToolBlitDrawing	  		= 255,	// Boolean, write only, UseToolBlitDrawing - For internal use only
	varToolOptionKeyDown	  	= 256,	// Boolean - For internal use only
	varToolShiftKeyDown	  		= 257,	// Boolean - For internal use only
	varToolPenFGColor			= 258,	// Uint8, foreground color, deprecated use varToolPenFGColor16 - For internal use only
	varToolPenBGColor			= 259,	// Uint8, background color, deprecated use varToolPenBGColor16 - For internal use only
	varToolPenSizeConstPixels	= 260,	// short, pixels Zoom line pref NOT observed - For internal use only
	varToolCtrlCmdKeyDown		= 261,  // Boolean - For internal use only
	varToolPenFGColor16			= 262,	// ColorRef, foreground color, write only - For internal use only
	varToolPenBGColor16			= 263,	// ColorRef, background color, write only - For internal use only

	// -------------------------------------------------------------------------
	// PDF Import setting
	//		Resolution setting for PDFPage Paint Node Creation
	varPDFPageObjPaintNodeRes	= 270,	// Sint32 - Public for VS

	//--------------------------------------------------------------------------
	// More render flags
	varShowHiddenLineSurfaceHatches = 280,
	varShowHiddenLineTextAndMarkers = 281,
	varPrepareDocumentForRenderMode = 290, // short - Public for VS

	// -------------------------------------------------------------------------
	// DXF Import settings. 
	//		Initial VectorWorks values in [brackets].
	//		Some variables are handled automatically by the internal DXF import
	//		command. You can turn off this automatic handling with the 
	//		"Auto..." variables below. For example, to set ModelSpaceScale
	//		to be 1:100, you would first need to set AutoModelSpaceScale to
	//		false and then set ModelSpaceScale to 100.0. 
	
	varDXF_AutoUnits					= 300,	// Boolean	[true] - Public for VS
	varDXF_Units						= 301,	// short	[kDU_Inches] - Public for VS
	varDXF_DXFUnitsPerInch				= 302,	// double	[1.0] - Public for VS
		// Auto Units does this: if the DXF file is set to "Engineering"
		// or "Architectural", then "feet and inches" is assumed because 
		// AutoCAD 14 displays these values as feet and inches; Units 
		// is set to kDU_Inches and units per inch is set to 1.0. Otherwise,
		// it is assumed that the document is already set to the correct units
		// and units and units per inch are set according to the current 
		// document units.
		//	If Auto Units is off, then you can set either Units or UnitsPerInch
		// (setting one results in the other one automatically being set).
		// Units is an enum EDXFUnits listing all the units specified by
		// AutoCAD, from inches to parsecs. Normally you should set only
		// the units variable. You should not set the units to kDU_Unitless,
		// as this will return an error. If you have a custom unit that 
		// is not in AutoCAD's list, then set units per inch instead, and
		// units will be set to kDU_Unitless.

	varDXF_AutoModelSpaceScale			= 303,	// Boolean	[true] - Public for VS
	varDXF_ModelSpaceScale				= 304,	// double	[1.0] - Public for VS
		// Auto ModelSpaceScale chooses a scale that fits model space to 
		// the current page. If false, set your own scale as 1:<your scale>
			
	varDXF_2D3DImportHandling			= 305,	// short	[k23D_2Dand3D] - Public for VS
		// k23D_All2D, k23D_2Dand3D, k23D_All3D.
	
	varDXF_MapLayersToClasses			= 306,	// Boolean	[true] - Public for VS
	varDXF_ConvertMLinesToWalls			= 307,	// Boolean	[false] - Public for VS
	//varDXF_ConvertRaysAndXLines		= 308,	// Boolean	[false]  removed for VW12 - Public for VS
	
	varDXF_ScaleDashLengths				= 309,	// Boolean	[false] - Public for VS
	varDXF_DashLengthScale				= 310,	// double	[1.0] - Public for VS
	
	varDXF_AutoBlockAttributeHandling	= 311,	// Boolean 	[true] - Public for VS
	varDXF_BlockAttributeHandling		= 312,	// short 	[kBAH_PreserveLook] - Public for VS
		// Value chosen from enum EDXFBlockAttributeHandling:
		//	kBAH_PreserveLook, kBAH_ListBelow, kBAH_Hide.
		// Auto BlockAttributeHandling checks the DXF header variable $ATTMODE to 
		// decide which VW import mode most closely matches the behavior in AutoCAD:
		//	$ATTMODE: 0 = "don't show attributes" -> Hide
		//			  1 = "normal"				  -> Preserve Look
		//			  2	= "show all attributes"   -> List Below
		// NOTE: "list below" is currently unimplemented and results in "preserve look"
											
	varDXF_AutoPointHandling			= 313,	// Boolean	[true] - Public for VS
	varDXF_ConvertPointsToLoci			= 314,	// Boolean	[false] - Public for VS
	varDXF_PointSymbolsAreGuides		= 315,	// Boolean	[true] - Public for VS
		// If Auto PointHandling is true, we check the DXF header variable
		// $PDSIZE. If > 0, it's a "real" size and we import as a symbol
		// in the Guides class. Else, if $PDSIZE <= 0, the size of the point 
		// is relative to the size of the screen indicating it's not a true 
		// part of the drawing and we import it as a locus.
			
	varDXF_MapColorsToLineWeights		= 316,	// Boolean	[true] - Public for VS
	varDXF_SetLineColorsBlack			= 317,	// Boolean	[false] - Public for VS
		// *NOTE: this may change with AC2000 to be auto-chosen
		
		// New variables for VW9...
	varDXF_PaperSpaceUnits				= 318,	// short	[kDPU_Inches]	(EDXFPlotUnits) - Public for VS
	varDXF_AutoScaleDashLengths			= 319,	// Boolean	[true] - Public for VS
	varDXF_GroupRecordFields			= 320,	// Boolean	[true] - Public for VS
	varDXF_AutoLineWeightHandling		= 321,	// Boolean	[true] - Public for VS
	
		// New variables for VW12 (from earlier versions)...
	varDXF_ConvertDimensionsToGroups	= 322,	// Boolean	[false] - Public for VS
	varDXF_RaysAndXLinesToGuides		= 323,	// Boolean	[false] - Public for VS

		// New variables for VW12...
	varDXF_AutoCenterAfterImport		= 324,	// Boolean	[true] - Public for VS
	varDXF_CenterAfterImport			= 325,	// Boolean	[true] - Public for VS
	varDXF_UseWorldOrigin				= 326,	// Boolean	[false] - Public for VS

	varDXF_SetVectorWorksUnitsToMatch	= 327,	// Boolean	[false] - Public for VS
		
		// New variables for VW14 (from earlier version)...
	varDXF_AddPrefixToDXFLayers			= 328,	// Boolean	[false] - Public for VS
	varDXF_PrefixToDXFEdit				= 329,	// TXString	[empty string] - Public for VS
		// prefix text is set if AddPrefixToDXFLayers, else it is skipped; 
		// if AddPrefixToDXFLayers is set to false, prefix text is deleted

		// New variables for VW14...
	varDXF_ExternalRefsHandling			= 330,	// short	[kBindExternalRefs] - Public for VS
		// 	kBindExternalRefs, kIgnoreExternalRefs,	kCreateVWRefs, kUseLayerImport
	
		// New variables for VW15...
	varDXF_ADTObjects2DView				= 331,	// Boolean	[true] - Public for VS

	varDXF_ExplodeBlocksOnImport		= 332,	// Boolean	[false] - Internal use only! CW Vitra project specific
	varDXF_BlockNameToExplode			= 333,	// TXString	[empty string] - - Internal use only! CW Vitra project specific

		// New variables for VW17...
	varDXF_IgnoreBlockClipping			= 334,	// Boolean	[true] - Public for VS

		// New variables for VW18...
	varDXF_ConversionRes				= 335,	// short	[kCR_VWConversionRes] (EDXFConversionRes) - Public for VS
		// kCR_VWConversionRes, kCR_Low, kCR_Medium, kCR_High, kCR_VeryHigh

		// New variables for VW19...
	varDXF_RegenarateDrawingAfterImport	= 336,	// Boolean	[true] - Internal use only! CW Vitra project specific
	varDXF_CreateReference				= 337,	// Boolean	[false]

		// New variables for VW20...
	varDXF_ConvertTablesToWorksheets    = 338,	// Boolean  [true] - Public for VS
	varDXF_ImportAsSolidLine			= 339,	// Boolean	[true] - Public for VS
	varDXF_SmallestGap					= 340,	// double	[1.0]  - Public for VS

		// New variables for VW22...
	varDXF_ImportTextures				= 341,	// Boolean	[true] - Public for VS
	varDXF_UpdateTextureResPreview		= 342,	// Boolean	[true] - Internal use only! CW Vitra project specific
	varDXF_CreateFolderForSymbols		= 343,	// Boolean	[true] - Internal use only! BIM Object task specific; Could be used by CW Vitra project.

		// New variables for VW24...
	varDXF_PurgeUnusedBlocks			= 344,	// Boolean	[true] - Public for VS
	varDXF_PurgeUnusedLayers			= 345,	// Boolean	[true] - Public for VS
	varDXF_PurgeUnusedDimStyles			= 346,	// Boolean	[true] - Public for VS
	varDXF_PurgeUnusedLineTypes			= 347,	// Boolean	[true] - Public for VS
	varDXF_PurgeUnusedMaterials			= 348,	// Boolean	[true] - Public for VS
	varDXF_CLMappingName				= 349,	// TXString	[empty string] - Public for VS		
		
		// New variables for VW25...
	varDXF_GeoRefImportType				= 350,  // short	[kNone]	(EGeoRefImportType) - Public for VS
	varDXF_GeoRefImportText				= 351,  // TXString	[empty string] - Public for VS

		// New variables for VW27...
	varDXF_ImportAsSymbol				= 352,

		// New variables for VW28...
	varDXF_BlocksHandlingType			= 353,	// short	[kDXFBlocksHandling_Normal] (EDXFBlocksHandlingType) - Public for VS
	varDXF_LayersHandlingType			= 354,	// short	[kDXFLayersHandling_AllLayers] (EDXFLayersHandlingType) - Public for VS
	varDXF_ImportSelectedObjects		= 355,	// Boolean	[false] - Public for VS

	// -------------------------------------------------------------------------
	// DXF Export settings. Initial VectorWorks values in [brackets].
	
	// RESERVED BY JDW: 300-399.


	// -------------------------------------------------------------------------
	// SmartCursor . 
	varSmartCursorStartPt2D				= 400,	// WorldPt read/write - For internal use only
	varSmartCursorStartPt3D				= 401,	// WorldPt3 read/write - For internal use only
	varSmartCursorShiftConstrain		= 402,	// Shift Constrain Mode write - For internal use only
	varSmartCursorConstrainMode			= 403,	// Constrain Mode write - For internal use only
	varSmartCursorGridOptions			= 404,	// Grid Options - read/write - For internal use only
	varSmartCursorSpecialAngle2D		= 405,	// WorldPt write - For internal use only
	varDataBar							= 406,	// Set Databar by ID - For internal use only
	
	
	varImmediateVSMode					= 407,	// Immediate Vector Script Mode - Public for VS
	
	varRunPickLoop						= 408,	// Run The Pick Loop - For internal use only
	varUse3DCursor						= 409,	// Boolean True -> Use the 3D cursor Fale -> use the 2D Cursor Maps to TDEF flag "uses3DCursor - For internal use only

	// Standard Advanced Selection Dialog Settings
	varUseFramedSelectionIndication		= 410,	// Boolean	True -> Used framed highlighting for selection indication.  FALSE uses classic VW 12 selection indication - Public for VS
	varSmartCursorShowInteractiveSegment= 411,	// Boolean	[false] TRUE -> Dashed line from startPt to currentPt is drawn by smart cursor.  FALSE not shown - Public for VS

	varPersistentPythonEngine			= 412,	// Boolean --	when True the Python engine is the same for the execution of all scripts
												//				this solves some issues with Py_Initialize and Py_Finalize
												//				For example, when debugging externally python leaves threas that cause crash if Py_Initialize and Py_Finalize is used for each script call
												//				So, this allows the engine to be preserved between calls, 
												//				however Vectorworks will delete all custom modules and objects defined in the engine prior each execution

	varShowImagingTiming				= 415,
	varShowImagingDebug					= 416,
	
	varShowSnapFPS						= 417,
	varShowPreselectionFPS				= 418,
	varShowRedrawFPS					= 419,
	varShowMiscFPS						= 420,

	// Optional Advanced Selection Dialog Settings
	varFramedSelectionAllowReshapeGrips	= 424,	//	Boolean	True -> Turns reshape grips on/off when using multiple selections - For internal use only
	varEnableSmartCursorFeedback		= 430,
	varSmartCursorLockSpecialAngle2D	= 435,	// WorldPt write - For internal use only
	varSmartCursorStartPt2DEx			= 436,	// WorldPt write - For internal use only
	varSmartCursorLockSpecialLength		= 437,	// double  write - For internal use only
	varSmartCursorEnableStart			= 438,	// Boolean write - For internal use only

	varAPIInval							= 450,	//	maps to GS_GetCallBackInval and GS_SetCallBackInval for VectorScript Access. - Public for VS
	varSnapToToolSnapGeometryOnly		= 460,  // Boolean True-> snap to tool snap geometry only. False ->snap normaly. Used by the attribute mappig tool now to restrict snapping 
	varSnapToSelectionOnly				= 461,  // Boolean True-> snap to selected objects only.  False->snap normaly.
	varSnapAngle						= 470,	// Boolean - Public for VS
	varSnapIntersect					= 471,	// Boolean - Public for VS
	varSnapSmartPoints					= 472,	// Boolean - Public for VS
	varSnapDistance						= 473,	// Boolean - Public for VS
	varSnapSmartEdge					= 474,	// Boolean - Public for VS
	varSnapConstrainTangent				= 475,	// Boolean - Public for VS
	varSnapConstrainToWorkingPlane		= 476,	// Boolean - Public for VS
	varSnapConstrainWorkingPlaneNormal	= 477,	// Boolean - Public for VS.  We still support WPPerp internally for tools.  There's no UI button for it.

	varRunFacePickLoop					= 478,	// Run The Face Pick Loop - For internal use only
	varResetRender						= 479,  // Boolean - Public for VS - Write only - support for issuing re-render 
	varSnapConstrainTo3DVector			= 480,	// Boolean read/write - Public for VS
	varSnapConstrainTo3DVectorOrigin	= 481,	// WorldPt3 read/write - For internal use only
	varSnapConstrainTo3DVectorDirection	= 482,	// WorldPt3 read/write - For internal use only
	varSmartCursorAddToolAngle			= 483,	// WorldPt write
	varSmartCursorOnlyUseToolAngles		= 484,	// Boolean read/write
	varSmartCursorClearToolAngles		= 485,	// void write
	varSmartCursorAddSmartPoint2D		= 486,	// WorldPt write
	varSmartCursorAddDatum2D			= 487,	// WorldPt write
	varSmartCursorAddSmartPoint3D		= 488,	// WorldPt3 write
	varSmartCursorAddDatum3D			= 489,	// WorldPt3 write
	varSmartCursorRemoveSmartPoint2D	= 490,	// WorldPt write
	varSmartCursorRemoveSmartPoint3D	= 491,	// WorldPt3 write
	varSmartCursorClearSmartPoints		= 492,	// void write
	varSmartCursorGetNumSmartPoints		= 493,	// short read
	varSmartCursorObserveWPInPlan		= 494,	// Boolean read write

	// -------------------------------------------------------------------------
	// Header and miscellaneous - JDW, 9/18/01
	varWindowZoomFactor					= 500,	// double	read/write - For internal use only
	
//	varColumnPages						= 501,		UNIMPLEMENTED	XXX_JDW_SDK
//	varRowPages							= 502,
//	varSheetWidth						= 503,
//	varSheetHeight						= 504,
//	varOnePage							= 505,		from pageOrSheet

	varLayerOptions						= 506,	// short	read/write	(ELayerOptions) - Public for VS
	varClassOptions						= 507,	// short	read/write	(EClassOptions) - Public for VS

	varDefaultGradientFill				= 508,	// Sint32		read/write - default gradient fill. - Public for VS
//	varDefaultGradientFillXOffset		= 509,	// double	read/write - UNIMPLEMENTED. X offset of gradient fill from center of object's bounding box.
//	varDefaultGradientFillYOffset		= 510,	// double	read/write - UNIMPLEMENTED. Y offset of gradient fill from center of object's bounding box.
//	varDefaultGradientFillLength		= 511,	// double	read/write - UNIMPLEMENTED. Distance over which a single instance of gradient fill is drawn.
	varDefaultGradientFillAngle			= 512,	// double	read/write - angle of gradient fill relative to object. - Public for VS
	varDefaultGradientFillRepeat		= 513,	// bool		read/write - indicates if gradient is repeated. - Public for VS
//	varDefaultGradientFillTessellate	= 514,	// bool		read/write - UNIMPLEMENTED. Indicates if gradient is tessellated.
	varDefaultGradientFillGeometricType	= 515,	// short	read/write - geometric type of gradient fill. - Public for VS
	varDefaultGradientFillMirror		= 516,	// bool		read/write - indicates if gradient is mirrored. - Public for VS

	varDefaultImageFillMaintainAspectRatio	= 517,	// bool		read/write - indicates if aspect ratio is maintained for image fill. - Public for VS
	varDefaultImageFill					= 518,	// Sint32		read/write - default image fill. - Public for VS
//	varDefaultImageFillXOffset			= 519,	// double	read/write - UNIMPLEMENTED. X offset of image fill from center of object's bounding box.
//	varDefaultImageFillYOffset			= 520,	// double	read/write - UNIMPLEMENTED. Y offset of image fill from center of object's bounding box.
	varDefaultImageFillILength			= 521,	// double	read/write - x distance over which a single instance of image fill is drawn. - For internal use only
	varDefaultImageFillJLength			= 522,	// double	read/write - y distance over which a single instance of image fill is drawn. - For internal use only
	varDefaultImageFillAngle			= 523,	// double	read/write - angle of image fill relative to object. - Public for VS
	varDefaultImageFillRepeat			= 524,	// bool		read/write - indicates if image fill is repeated. - Public for VS
//	varDefaultImageFillTessellate		= 525,	// bool		read/write - UNIMPLEMENTED. Indicates if image fill is tessellated.
	varDefaultImageFillMirror			= 526,	// bool		read/write - indicates if image fill is mirrored. - Public for VS
	varDefaultImageFillFlip				= 527,	// bool		read/write - indicates if image fill is flipped. - Public for VS

	varDefaultFillStyle					= 528,	// Sint32		read/write - default fill style. - Public for VS
	varDefaultFillType					= 529,	// short	read only  - default fill type. - Public for VS

	varDefaultHatchFill					= 530,   // Sint32		read/write - default hatch fill. - Public for VS

	varDefaultImageFillILengthInCurrUnits = 532, // double	read/write - x distance (current units) over which a single instance of image fill is drawn. - Public for VS
	varDefaultImageFillJLengthInCurrUnits = 533, // double	read/write - y distance (current units) over which a single instance of image fill is drawn. - Public for VS

	varFillStyleByClass					= 534,   // bool	read/write - indicates if the fill style is by class or not

	varLowDetailFactor					= 538,	// double	read/write - layer scales >= varLowDetailFactor will only show low detail and will hide wall cavities - Public for VS
	varMediumDetailFactor				= 539,	// double	read/write - layer scales >= varMediumDetailFactor will show medium detail, <= varMediumDetailFactor will show high detail - Public for VS

	varHideCavityFactor					= 540,	// short	read/write - layer scales >= varHideCavityFactor will hide wall cavities (Architect Only) - Public for VS

	varSaveViewportCache				= 541, 	// bool		read/write - document preference to save/not save viewport caches. - Public for VS

	varSmoothMesh						= 542,  // bool     read/write - document preference to turn smoothing on for mesh rendering - Public for VS
	varMeshCreaseAngle					= 543,  // double   read/write - crease angle for mesh smoothing to define hard edges - Public for VS
	varUseAutoDrawCoord					= 544,	// bool		read/write - whether to coordinate sheet and drawing numbers for various items - Public for VS
	varInteractiveSymScaling			= 545,	// byte		read/write - whether to allow interactive scaling of 2D symbols (1-never,2-always with warning,3-always no warning) - Public for VS
	varDefaultDimensionClassID          = 546,  // Sint32   read/write - default dimension class RefNumber

	varTreatSubsequentObjectOperationsTemporary			= 550,  //bool	read/write - Treat Subsequent Object Operations as Temporary or not	[False] - For internal use only
	varTreatSubsequentGlobalSettingsChangesTemporary	= 551,	//bool	read/write - Treat Subsequent Global Settings Changes as Temporary or not [False] - For internal use only

	// Improved autosave
	varAutosaveToCustomLocation							= 552, // Boolean	read/write	- Public for VS
	varKeepBackupsByTime								= 553, // Public for VS
	varAutosaveCustomLocation							= 554, // TXString	read/write	- Public for VS
	varKeepBackupsByNumberValue							= 555, // short		read/write	= Public for VS
	varKeepBackupsByTimeValue							= 556, // Public for VS
	varKeepBackupsByTimeUnit							= 557, // Public for VS

	varCenterView						= 558,					// bool		read/write		default is false.  Performs a Fit-To-Objects after a view change
	varAllowCopyOnOptionClick			= 559,					// bool		read/write		default is true.  Prevents objects being copied repeatedlu upon option click

	varShowTextFilesInPluginEditor		= 560,					// bool		read/write		default is true.   When cleared, text files will not be shown in Plug-In Editor List.

	varCompactDocumentPlanes			= 565,					// bool		write			command to compact the planes.
	varNumDocumentPlanes				= 566,					// Sint32		read			retrieves the number of used planes.
	varMaxNumDocumentPlanes				= 567,					// Sint32		read			retrieves the maximum number of planes that can be created.

	varReleaseVersionInteger			= 570,					// short	read/write		The release version integer defaults to 0, in which case it is not displayed. If this

	varSymbolToolInsertMode				= 580,	// short	read/write - public for vs - get/set the insertion mode of the symbol tool
	varSymbolToolWallInsertion			= 581,	// bool		read/write - public for vs - get/set the wall insertion mode of the symbol tool
	varSymbolToolAlignementMode			= 582,	// short	read/write - public for vs - get/set the alignment mode of the symbol tool

	varParametricEnableStateEventing	= 590,	// char write - [TParametricStateFlags] - Public for VS
												//				parametrics should receive kParametricAddState event
												//				flags control the type of events to be sent, can be ORed
	varParametricRegenPausedPlanRotation		= 591,	//	Boolean	read only.  Was Plan rotation paused (turned off) for parametric rgenration.
	varParametricRegenPausedPlanRotationAngle	= 592,	//	double	read only.  Paused Plan rotation angleexp.
	varOpenGLAntiAliasingCapability				= 593,	// To get anti-aliasing OpenGL option.
	varOpenGLDrawEdgesCapability				= 594,	// To get Draw-edges OpenGL option.
	varOpenGLUseShadowsCapability				= 595,	// To get Use-shadows OpenGL option.
	varBlockUntilDoneRendering					= 596,	// Only for SetProgramVariable(). Wait until the background rendering is finished. Then return the function.
	varAllowDropShadows							= 597,	// to get Drop Shadows option.
	varOpenGLEnvironmentLightingCapability      = 598,  // To get environment lighting OpenGL option.
	varOpenGLEnvironmentReflectionCapability    = 599,   //  To get environment reflection OpenGL option.
	varOpenGLScreenSpaceReflectionCapability    = 601,  // To get screen space reflection OpenGL option.

	varDidCancelScriptMenuCommand				= 996, // Boolean - write only - For internal use only - Set to true to notify that script menu command was closed with Cancel.

	varShowSelectionBox					= 1000,	// Boolean 
	varShowSnapBox						= 1001,	// Boolean 
	varAnimationMode					= 1003, // short	
	varCursorPreselectionHighlighting	= 1004,	// Boolean 
	varMarqueePreselectionHighlighting	= 1005,	// Boolean 
	varSnappedObjectHighlighting		= 1006,	// Boolean 
	varToolHighlighting					= 1007,	// Boolean 
	varHighlightingTimer				= 1008, // double  
	varSelectionRadius					= 1009,	// double
	varSnapBoxRadius					= 1010,	// double
	varDisplayHorizontalDPI				= 1011,	// double
	varDisplayVerticalDPI				= 1012,	// double
	varShowSnapPoints					= 1013, // Boolean
	varZoomLineThicknessInSnapLoupe		= 1014, // Boolean
	varOffsetFromSource					= 1015,	// Boolean
	varShowAcquisitionHints				= 1016, // Boolean
	varReferenceGridX					= 1019, // double
	varReferenceGridY					= 1020, // double
	varGridAngleY						= 1021, // double
	varSheetLayerSnapGridX				= 1022, // double
	varSheetLayerSnapGridY				= 1023, // double
	varSheetLayerReferenceGridX			= 1024, // double
	varSheetLayerReferenceGridY			= 1025, // double
	varSheetLayerGridAngleY				= 1026, // double
	varSnapEnd							= 1027,	// Boolean
	varSnapMid							= 1028,	// Boolean
	varSnapCenter						= 1029, // Boolean		
	varSnapQuad							= 1030,	// Boolean							
	varSnapInsertion					= 1031,	// Boolean										
	varSnapVertex						= 1032,	// Boolean														
	varSnapEdge							= 1033,	// Boolean		
	varSnapAnglesDegrees				= 1034, // String
	varPlanRotation						= 1035, // Boolean
	varAltCoordSystemExtensionLines		= 1036, // Boolean
	varHorizontalVerticalExtensions		= 1037, // Boolean
	varUseAngularExtensions				= 1038, // Boolean
	varUseFloatingSmartPt				= 1039, // Boolean
	varFloatingSmartPtTimeSeconds		= 1040, // double
	varFloatingDatumTimeSeconds			= 1041, // double	
	varUseDatumOffset					= 1042,	// Boolean
	varDatumOffset						= 1043, // double
	varDoFloatingEdges					= 1044, // Boolean
	varFloatingEdgeTimeSeconds			= 1045, // double
	varUseAngleBisector					= 1046, // Boolean
	varDoOffset							= 1047, // Boolean
	varOffsetDistance					= 1048, // double
	varDoCurveExtensions				= 1049, // Boolean
	varDoProportional					= 1050, // Boolean
	varPercent							= 1051, // double
	varDistance							= 1052, // double
	varMultipleDivisions				= 1053, // Boolean
	varAutoUpdateFrequency				= 1054, // short
	varShowOthersInGroupGray			= 1055, // Boolean
	varErrorReportingMode				= 1056, // short
	varOmpParallelTexture				= 1057, // Boolean					
	varOmpParallelImage					= 1058, // Boolean
	varOmpParallelRender				= 1059, // Boolean
	varOmpParallelGeometry				= 1060, // Boolean
	varOmpParallelDTM					= 1061, // Boolean
	varOmpParallelMisc					= 1062, // Boolean
	varShow3DZAxis						= 1063,	// Boolean
	varShow3DAxesGrp					= 1064,	// Boolean
	
	varDefaultTileFill					= 1065,	// Sint32		read/write - default tile fill. - Public for VS

	varSnapFaceHighlight				= 1066,	// Boolean, Internal
	varSnapMaster						= 1067,	// Boolean		
	
	varHorizontalTextEditByDefault		= 1085,	// Boolean
	varSnapToRelativeAngles				= 1086,	// Boolean	read/write - true if relative angles are used in the smart cursor and the databar
	varSnapRelativeAngle				= 1087,	// double	read/write - angle, clockwise from horizontal, for relative angles
	varSnapRelativeAngleHint			= 1088,	// Boolean	read/write - true for Tangent, false for Parallel hint
	varSnapRelativeAngleClear			= 1089,	// Clear the relative angle and hint
	varSnapToCombinedPageArea			= 1090,
	varSnapToIndividualPages			= 1091,
	varSnapToAnglesFromAxes				= 1092,
	varSnapToAltCoordSystem				= 1093,
	varSnapToLineBetweenSmartPts		= 1094,
	varSnapAllowExtensionsFromNearbySmartPts	= 1095,
	varSnapDisableAll					= 1096,
	varSaveDTMCache						= 1097,	// Boolean	read/write - true if the Site Model caches are to be saved in the document
	varShowWPAxesInPlan					= 1098, // Boolean

	varScreenPlaneMode					= 1099, // Boolean read/write - true if screen plane mode is active

	varIsWindowsOS64Bit					= 1100, // Boolean read - true if Vectorworks is running on a 64 Windows OS.
	varAutomaticPlane					= 1101, // Boolean read/write - true if autoplane pref is active
	
	varOnTheFlyScreenPlaneMode			= 1102, // Boolean read/write - true if plane mode is set to ScreenOrWorkingPlane
	varCreatingReplaceRenameUseDlg		= 1103, // Boolean, Internal
    varEnableOnlineVWLibs               = 1104, // Boolean read/write - Public for VS - Enable online content
    varEnableSubscriptionLibs           = 1105, // Boolean read/write - Public for VS - Enable Subscription Libraries
    varIsVSSLicensed                    = 1106, // Boolean, Internal
	varSameVisAllPanes					= 1107, // Boolean read/write - Public for VS - Use Same Visibilities in All Panes

	varPrefsInter_Store								= 1200,		// Boolean	read/write - Public for VS - Get this value to save the current prefereces, Set it to restore the last saved. Value doesn't matter.

	// Cursor group
	varPrefsInter_FullScreenCursor					= 1210,	// Boolean	read/write - Public for VS -  (false)
	varPrefsInter_ShowSelectionBox					= 1211,	// Boolean	read/write - Public for VS -  (true)
	varPrefsInter_ShowSnapBox						= 1212,	// Boolean	read/write - Public for VS -  (true)
	varPrefsInter_ShowAcquisitionHints				= 1213,	// Boolean	read/write - Public for VS -  (true)
	varPrefsInter_SelectionRadius					= 1214,	// double	read/write - Public for VS -  TScreenInches default: 0.08
	varPrefsInter_SnapRadius						= 1215,	// double	read/write - Public for VS -  TScreenInches default: 0.30
	varPrefsInter_GripRadius						= 1216,	// double	read/write - Public for VS -  TScreenInches default: 0.30

	// Highlighting Group
	varPrefsInter_SelectionHighlightingMode			= 1220,	// Sint32		read/write - Public for VS - 
	varPrefsInter_AnimationMode						= 1221,	// short	read/write - Public for VS - 
	varPrefsInter_CursorPreselectionHighlighting	= 1222,	// Boolean	read/write - Public for VS - 
	varPrefsInter_MarqueePreselectionHighlighting	= 1223,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnappedObjectHighlighting			= 1224,	// Boolean	read/write - Public for VS - 
	varPrefsInter_ToolHighlighting					= 1225,	// Boolean	read/write - Public for VS - 
	varPrefsInter_HighlightingTimer					= 1226,	// double	read/write - Public for VS - 

	varViewTransitionAnimation						= 1227,	// double	read/write
	varViewTransitionAnimationEnabled				= 1228, // double	read/write

	// Smart Cursor Dialog Preferences - General
	varPrefsInter_ShowSmartCursorCues				= 1230,	// Boolean	read/write - Public for VS - 
	varPrefsInter_ShowSnapPoints					= 1231,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapToLoci						= 1232,	// Boolean	read/write - Public for VS - 
	varPrefsInter_ZoomLineThicknessInSnapLoupe		= 1233,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapToCombinedPageArea			= 1234,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapToIndividualPages				= 1235,	// Boolean	read/write - Public for VS - 
	varPrefsInter_OffsetFromSource					= 1236,	// Boolean	read/write - Public for VS - 
	varPrefsInter_IgnoreNonPlanarSnaps				= 1237,	// Boolean	read/write - Public for VS - 
		
	// Smart Cursor Dialog Preferences - Grid
	varPrefsInter_NotDoShowGrid						= 1240,	// Boolean	read/write - Public for VS - 
	varPrefsInter_DoPrintGrid						= 1241,	// Boolean	read/write - Public for VS - 
	varPrefsInter_GridShow3DZAxis					= 1242,	// Boolean	read/write - Public for VS - 
	varPrefsInter_GridShow3DAxisLabels				= 1243,	// Boolean	read/write - Public for VS - 
	varPrefsInter_GridShow3DAxesGrp					= 1299,	// Boolean	read/write - Public for VS - 

	// Smart Cursor Dialog Preferences - Object
	varPrefsInter_SnapEnd							= 1250,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapMid							= 1251,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapCenter						= 1252,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapQuad							= 1253,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapInsertion						= 1254,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapVertex						= 1255,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapEdge							= 1256,	// Boolean	read/write - Public for VS - (true) 3D edge is existing document setting, superceeded by this which does both 2D and 3D
	varPrefsInter_SnapMaster						= 1257,	// Boolean	read/write - Public for VS -

	// Smart Cursor Dialog Preferences - Angle
	varPrefsInter_SnapToUserAngles					= 1260,	// Boolean	read/write - Public for VS - 
	varPrefsInter_UserAngleCount					= 1261,	// Sint32		read/write - Public for VS - the number of valid angles (see varPrefsInter_UserAnglesDegreesX);
	varPrefsInter_UserAnglesDegrees1				= 1262,	// double	read/write - Public for VS - >= 0 && < 360		
	varPrefsInter_UserAnglesDegrees2				= 1263,	// double	read/write - Public for VS - >= 0 && < 360		
	varPrefsInter_UserAnglesDegrees3				= 1264,	// double	read/write - Public for VS - >= 0 && < 360		
	varPrefsInter_UserAnglesDegrees4				= 1265,	// double	read/write - Public for VS - >= 0 && < 360		
	varPrefsInter_UserAnglesDegrees5				= 1266,	// double	read/write - Public for VS - >= 0 && < 360		
	varPrefsInter_UserAnglesDegrees6				= 1267,	// double	read/write - Public for VS - >= 0 && < 360		
	varPrefsInter_UserAnglesDegrees7				= 1268,	// double	read/write - Public for VS - >= 0 && < 360		
	varPrefsInter_UserAnglesDegrees8				= 1269,	// double	read/write - Public for VS - >= 0 && < 360		
	varPrefsInter_SnapToRelativeAngles				= 1280,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapToPlanRotationAngle			= 1281,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapToAlternateCoordinateSystem	= 1282,	// Boolean	read/write - Public for VS - 
	varPrefsInter_AlternateCoordinateSystemAngle	= 1283,	// double	read/write - Public for VS - 

	// Smart Cursor Dialog Preferences - Smart Point
	varPrefsInter_HorizontalVerticalExtensions		= 1290,	// Boolean	read/write - Public for VS - 
	varPrefsInter_UseAngularExtensions				= 1291,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapToLineBetweenSmartPts			= 1292,	// Boolean	read/write - Public for VS - 
	varPrefsInter_AllowExtensionsFromNearbySmartPts	= 1293,	// Boolean	read/write - Public for VS - 
	varPrefsInter_UseFloatingSmartPt				= 1294,	// Boolean	read/write - Public for VS - 
	varPrefsInter_FloatingSmartPtTimeSeconds		= 1295,	// double	read/write - Public for VS -  (0.5, 0, 5)
	varPrefsInter_UseFloatingDatum					= 1296,	// Boolean	read/write - Public for VS - 
	varPrefsInter_FloatingDatumTimeSeconds			= 1297,	// double	read/write - Public for VS - (2.0, 0, 5)
			
	// Smart Cursor Dialog Preferences - Smart Edge
	varPrefsInter_DoFloatingEdges					= 1300,	// Boolean	read/write - Public for VS - 
	varPrefsInter_FloatingEdgeTimeSeconds			= 1301,	// double	read/write - Public for VS -  (0.5, 0, 5)
	varPrefsInter_UseAngleBisector					= 1302,	// Boolean	read/write - Public for VS - 
	varPrefsInter_DoCurveExtensions					= 1303,	// Boolean	read/write - Public for VS - 

	// Smart Cursor Dialog Preferences - Constraint Button State
	varPrefsInter_SnapToObject						= 1310,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapToGrid						= 1311,	// Boolean	read/write - Public for VS - 
	varPrefsInter_ConstrainAngle					= 1312,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapToIntersection				= 1313,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SmartPoints						= 1314,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SnapToDistance					= 1315,	// Boolean	read/write - Public for VS - 
	varPrefsInter_SmartEdge							= 1316,	// Boolean	read/write - Public for VS - 
	varPrefsInter_ConstrainTangent					= 1317,	// Boolean	read/write - Public for VS - 
	varDefaultRenderModeRenderMode					= 1318, // Default Render Mode settings in Preferences(3D Pane) - short	read/write
	varDefaultRenderModeProjMode					= 1319, // Default Render Mode settings in Preferences(3D Pane) - short	read/write

	// offset based appearance settings
	// in order to use these you have to offset them with
	varPrefsInter_AppearanceProps					= 1325 + 0 + 0,	// this is used in combination with the offsets below
																	// the actual selector used with Get/SetProgramVariable is:
																	//
																	//	selector = (varPrefsInter_AppearanceProps + offset_group_AppearanceProps_* +  offset_AppearanceProps_*)
																	//
																	//	the types for each repeating property are denoted in the offset_AppearanceProps_*

			// AppearanceProperties offset constants from varPrefsInter_AppearanceProperties
			offset_AppearanceProps_available							= 0,	// Boolean	read/write - Public for VS - 
			offset_AppearanceProps_hasDifferentBackgroundColor			= 1,	// Boolean	read/write - Public for VS - 
			offset_AppearanceProps_pattern								= 2,	// Sint32		read/write - Public for VS - 
			offset_AppearanceProps_foreColor							= 4,	// TRGBColorread/write - Public for VS - 
			offset_AppearanceProps_backColor							= 5,	// TRGBColorread/write - Public for VS - 
			offset_AppearanceProps_opacity								= 6,	// Sint32		read/write - Public for VS - [0..100]
			offset_AppearanceProps_size									= 7,	// double	read/write - Public for VS - 
			offset_AppearanceProps_minSize								= 8,	// double	read/write - Public for VS - 
			offset_AppearanceProps_maxSize								= 9,	// double	read/write - Public for VS - 
			offset_AppearanceProps_opacity1								= 10,	// Sint32		read/write - Public for VS - [0..100]
			offset_AppearanceProps_size1								= 11,	// double	read/write - Public for VS - 
			offset_AppearanceProps_minSize1								= 12,	// double	read/write - Public for VS - 
			offset_AppearanceProps_maxSize1								= 13,	// double	read/write - Public for VS - 
			offset_AppearanceProps_opacity2								= 14,	// Sint32		read/write - Public for VS - [0..100]

				offset_group_AppearanceProps_SmartCursorSelectionBox						= 0 * 30,	// note, these are sequential in 30th system
				offset_group_AppearanceProps_SmartCursorSnapBox								= 1 * 30,
				offset_group_AppearanceProps_SmartCursorDatumIndicator						= 2 * 30,
				offset_group_AppearanceProps_SmartCursorPoints								= 3 * 30,
				offset_group_AppearanceProps_SmartCursorEdges								= 4 * 30,
				offset_group_AppearanceProps_SmartCursorVectorLocks							= 5 * 30,
				offset_group_AppearanceProps_SmartCursorAcquisitionHints					= 6 * 30,
				offset_group_AppearanceProps_SnapPointsAvailable							= 7 * 30,
				offset_group_AppearanceProps_SnapPointsCurrent								= 8 * 30,
				offset_group_AppearanceProps_SnapPointsObtained								= 9 * 30,
				offset_group_AppearanceProps_SnapPointsCongestionIndicator					= 10 * 30,
				offset_group_AppearanceProps_ObjectHighlightingPreSelectionActiveLayer		= 11 * 30,
				offset_group_AppearanceProps_ObjectHighlightingSelectionActiveLayer			= 12 * 30,
				offset_group_AppearanceProps_ObjectHighlightingSelectionInactiveLayer		= 13 * 30,
				offset_group_AppearanceProps_ObjectHighlightingSelectionLocked				= 14 * 30,
				offset_group_AppearanceProps_ObjectHighlightingSnapObject					= 15 * 30,
				offset_group_AppearanceProps_ObjectHighlightingToolHighlighting				= 16 * 30,
				offset_group_AppearanceProps_ObjectHighlightingAction						= 17 * 30,
				offset_group_AppearanceProps_GeneralExitEditContextFrame					= 18 * 30,
				offset_group_AppearanceProps_GeneralExitEditContextShowOthers				= 19 * 30,
				offset_group_AppearanceProps_GeneralPageBoundary							= 20 * 30,
				offset_group_AppearanceProps_GeneralGrid									= 21 * 30,
				offset_group_AppearanceProps_GeneralWorkingPlane							= 22 * 30,
				offset_group_AppearanceProps_GeneralGroundPlane								= 23 * 30,
				offset_group_AppearanceProps_GeneralHintText								= 24 * 30,
				offset_group_AppearanceProps_GeneralHintBackground							= 25 * 30,
				offset_group_AppearanceProps_GeneralReshapeHandlesActiveLayer				= 26 * 30,
				offset_group_AppearanceProps_GeneralReshapeHandlesInactiveLayer				= 27 * 30,
				offset_group_AppearanceProps_ObjectHighlightingPreSelectionInactiveLayer	= 28 * 30,
				offset_group_AppearanceProps_ObjectHighlightingPreSelectionLocked			= 29 * 30,
				offset_group_AppearanceProps_SnapPointsObjectOriented						= 30 * 30,
				offset_group_AppearanceProps_SmartCursorPlanes								= 31 * 30,
				offset_group_AppearanceProps_SmartCursorSmartPtLines						= 32 * 30,
				offset_group_AppearanceProps_GeneralRepetitionOpacity						= 33 * 30,
				offset_group_AppearanceProps_SmartCursorAngleLines							= 34 * 30,
				offset_group_AppearanceProps_ObjectHighlightingAutomaticPlaneSource			= 35 * 30,
				offset_group_AppearanceProps_GeneralXRayEdgeSelection						= 36 * 30,
				offset_group_AppearanceProps_GeneralTopPlanBkgndColor						= 37 * 30,
				offset_group_AppearanceProps_GeneralSheetLayerBkgndColor					= 38 * 30,
				offset_group_AppearanceProps_General3DViewBkgndColor						= 39 * 30,
				offset_group_AppearanceProps_GeneralBkgndPerspectiveHorizonSky				= 40 * 30,
				offset_group_AppearanceProps_GeneralBkgndPerspectiveHorizonGround			= 41 * 30,
				offset_group_AppearanceProps_ObjectHighlightingOccludedFeedback				= 42 * 30,
				offset_group_AppearanceProps_ClipCubeSolidCut								= 43 * 30,
				offset_group_AppearanceProps_ClipCubeHollowCut								= 44 * 30,
				offset_group_AppearanceProps_SnapPointsMaster								= 45 * 30,
				offset_group_AppearanceProps_ObjectHighlightingCheckedOut					= 46 * 30,
				offset_group_AppearanceProps_SubdivisionCreaseHighlighting					= 47 * 30,
				offset_group_AppearanceProps_RulersCursorPositionIndicators					= 48 * 30,
				offset_group_AppearanceProps_RulersBackground								= 49 * 30,
				offset_group_AppearanceProps_RulersMarksAndText								= 50 * 30,
				offset_group_AppearanceProps_FloatingDataBarBackground						= 51 * 30,
				offset_group_AppearanceProps_FloatingDataBarOutlineAndText					= 52 * 30,


	varPrefsInter_AppearanceProps_LastSelector				= 3999,	// this is to mark the end of the appearance properties selectors

	varCurrentBkgndColor				= 4003,

	// offset based appearance settings for BLACK BACKGROUND
	// in order to use these you have to offset them with
	varPrefsInter_BlackBkgndAProps						= 4025 + 0 + 0,	// this is used in combination with the offsets
			// Referenced in "varPrefsInter_AppearanceProps"
	varPrefsInter_BlackBkgndAProps_LastSelector			= 6699,	// this is to mark the end of the appearance properties selectors
	
	varHighShadowMapResolution = 6700,					// short - to test various shadow map configurations at runtime
	varHighShadowNumFrustumSplits = 6701,				// short
	varUserOriginX = 6702,								// double	- Public for VS - The user origin of the document
	varUserOriginY = 6703,								// double	- Public for VS

	varPasteSourceGISProjection = 6705,					// TXString	- SDK Only - Read Only - get the source GIS projection after copy
	varHeliodonInteractiveRender = 6706,				// Boolean  - Public for VS. 

	varShowClipCube	= 6707,								// read/write  turns on/off Clip Cube

	varVSWriteBinaryMode = 6708,						// read/write	truns on/off the binary mode of the VS Write function allowing doing Write(Char(0)) and Write(Char(10))

	varCreateCustomObjectDontInsertInWall = 6709,		// read/write	prevents the ISDK::CreateCustomObject function from inserting the newly object into an existing wall

	varSpaceParasolidProcessing	= 6710,					// For internal use only - read/write - used for caching the imprinted sheet - should be false initially then true for subsequent calls
	varDisplayVPOutOfDateIndicator = 6711,				// read/write turns out-of-date border of viewports ON or OFF
	varShowNudgeMessage = 6712,							// Boolean

	varUsingVGM = 6715,									// To communicate to the OpenGL options dialog whether the VGM is in use.

	varSaveDepthBufferImage			= 6716,             // Writes snapshot of OpenGL depth buffer to tempfile directory
	varSaveMovieImage				= 6717,				// Writes snapshot of OpenGL offscreen image to tempfile directory
	varForceFallbackMovieFormat     = 6718,				// Force usage of fallback movie format

	varShowLinearDirectionMarker	= 6719,				// read/write	Controles if the linear direction marker is visible or not (for line, poly, nurbs, and parametric objects)


	varGetFeedbackScaleFactor		= 6720,				// double	read	- Public for VS - The pixel scale factor used for document window feedback on high resolution displays (usually Retina displays).
	varGetFeedbackResolution		= 6721,				// double	read	- Public for VS - (Superfluous) The PPI currently being used to draw feedback in the active document window.
	varGetDocumentWindowResolution	= 6722,				// double	read	- Public for VS - (Superfluous) The PPI used to convert true screen inches to pixels in the active document window.

	
	varShowInternalOriginMarker		= 6723,				// Boolean - read/write turns on/off the Internal Origin Marker	
	
	varUseLocalHelpSystem		    = 6724,             // Boolean	read/write turns on/off the use of local help system

	varViewTransitionSpeed			= 6725,				// double  read/write

	varShowFinalFrame				= 6726,				// Boolean	read/write	- Internal - Draws the final GDI+/Quartz frame in Plan (When disabled the VGM provides the final frame)
	varUsePseudoHiddenLine			= 6727,				// Boolean	read/write	- Internal - Provides a fast hiddenline working environment when in wireframe rendering mode.
	varUsingVGMforNavGraphics		= 6728,				// Boolean	read/write	- Internal - Toggles the VGM on/off for the interactive frames.
	varUseThreadedDrawing			= 6729,				// Boolean	read/write	- Internal - Toggles multi threaded drawing on/off for the final frame.
	varShowDrawTime					= 6730,				// Boolean	read/write	- Internal - Debug information that show the amount of time required to draw.

	varPrebuildPSTessellations		= 6731,				// Boolean	read/write	- Internal - To avoid Parasolid on background threads we prebuild nonCurvy tessellations, unless this options is false.
	varSavePSTessellations			= 6732,				// Boolean	read/write	- Internal - To avoid Parasolid we save nonCurvy tessellation unless this options is true.
	varShowPSTessellationsUsage		= 6733,				// Boolean	read/write	- Internal - Display the count of Composite Surfaces that have cached data.

	varDWGExportLineTypeClipping 	= 6750, 			// For internal use only - read/write - If this is set to true then complex line types will be clipped during DWG export, defaults to true.
    varCenteringDrawingOnInternalOrigin = 6751,         // For internal use only - read only - Gets whether or not we are currently centering the drawing on the internal origin.  This allows SDK
                                                        // developers to respond to the move of their PIO. See VB-120361 for details
    
	varAllowDockingToDrawing		= 6752,
	varAllowInterPaletteDocking		= 6753,
    varShowDockedDocumentTabs       = 6754,             // Boolean  read/write  - Controls the visibility of titled tabs associated with docked documents

	varGetEnteredGroupHandle		= 6755,				// Handle	read	- Get the Handle of the current opened for edit group in VW document

	varCycleSavedViews				= 6760,				// Int		read/write	- Internal - set index of the sorted list of saved views to start cycling from (-1 to terminate cycling)

	varToolModebarTrapsShift		= 6770,				// Boolean	write - Only used during tool DoSetup event. It will force the tool to trap the shift key for when it is used with the short keys for modebar.
														//					this is used when the tool needs to use the short keys to go backward in the list of a popup
    
    varAlwaysUsePaletteAutoUnshade  = 6775,				// Boolean  read/write   - Controls the state in which windowshaded palettes automaticaly unshade based on mouse proximity
	varAlwaysUsePaletteAutoHiding   = 6776,				// Boolean  read/write   - Controls the state in which docked palettes automaticaly hides based on mouse proximity


	varTrashGlobalVariables			= 6780,				// Boolean	read/write	 - Internal - JLoy - Trash globals.
	varEnableODTThreads				= 6781,				// Boolean	read/write	 - Internal - JLoy - Enable ODT Threads.

	varProgressiveVGMFrames			= 6785,				// Boolean read/write	- Internal

    varPostponeInvalRef             = 6786,				// Boolean read/write	- Internal - When true, this causes all calls to InvalRef calls to be aggregated and defered for efficiency until it is set back to false
    varDisableInvalRef              = 6787,				// Boolean read/write	- Internal - When true, this causes all calls to InvalRef calls to be completely ignored until it is set back to false

	varPointCloudImportLimit		= 6790,				// Int read/write	- Internal - FZafar.

	varMaxConvertToPolyResolution	= 6791,				// short read/write - For internal use only - BStanchev.

	varDXXXFBoundsSettingDisable	= 6792,				// Boolean read/write - Internal - For control of bounds resets when a DXF import/export is done 

	varTestWebPalette				= 6793,				// Boolean write - Internal - DaveD
	
	varSDFText						= 6794,				// Boolean read/write - Internal - whether to generate SDF meshes to represent text for VGM

	varWSReportDialogType			= 6795,				// short read/write	- Internal - sets type of worksheet report dialog. See CreateReport.vs/CreateDatabaseWorksheet.cpp

	varWSRerportWSDisplayType		= 6796,				// Boolean read/write - Internal - sets whether worksheet report dialog is displayed from worksheet or not. See CreateReport.vs/CreateDatabaseWorksheet.cpp

	varSimplifyMeshQuadricErrorEnabled = 6797,          // Boolean read/write - Internal - sets the algorithm for Simplify Mesh to be the Quadric Metric

	varWSParamDelimiter				= 6798,				// TXString read - Get the Worksheet parameter delimiter. It will be ',' for locales that use '.' as real-number delimiter; and ';' for locales that use ',' for real-number delimiter
	
	varDisableScreenRefreshState	= 6799,				// Boolean write - Turns screen redraws on/off

	varGetCurrentVGM				= 6800,				// VGM::IGraphicsEngine* read - Internal - get the current vgm
	
	varSetLMMacTextViewSubstState	= 6801,				// Boolean read/write - Internal - sets whether the layout manager multiline edit control has text substitutions enabled/disabled for OSX. No-op on Windows.

	varEnableMultipleViews			= 6802,				// Boolean read/Write - Enable Multiview

	varLinkMultiViewVisibilities	= 6803,				// Boolean read/write - Multiview visibilities

	varDuplicateTagsWithObjects		= 6804,             // Boolean	read/write turns on/off the Duplicate Tags With Objects

	varEnableMeshCachedOctree       = 6805,

    varDrawTheVrefPickedUpFromOctree = 6806,            // Boolean	read/write turns on/off the drawing of the ray+octree intersected mesh vrefs
    
	varAlwaysShowCurrentToolOnFDBSelector		= 9999,

	varProfileVSExecution			= 6807,				// Boolean - Enable profile VectorScript execution. Outputs in a txt file in the plugins user folder- Public for VS
	
	varEnableOnDemandLevelOfDetail  = 6808,				// Boolean	read/write turns on/off on demand level of detail (LOD) 

	varHideGPUDisplayAlertDialog	= 6809,				// Boolean - Set to "true" to prevent the error dialog found in VGMProxy.cpp from showing

	varHideGraphicsAdaptersAlertDialog = 6810,			// Boolean - Set to "true" to prevent the error dialog found in VGMProxy.cpp from showing
    
    varEnableOnDemandLevelOfDetail2D = 6811,            // Boolean    read/write turns on/off on demand level of detail (LOD) for planar graphics

	varSmartCursorLockSpecialX		= 6812,				// double  write - cursor lock for tool databar value entry
	varSmartCursorLockSpecialY		= 6813,				// double  write - cursor lock for tool databar value entry
	
	varEnableVGSCineRender			= 6814,
	varUseVGSForArtRW				= 6815,
	varUseOpenGLBackgroundContext   = 6816,				// Boolean - Set to "true" to turn on the OpenGL background context
	varUseDuplicatesForRasterVPs	= 6817,				// Boolean - Set to "true" to send duplicates to the FlatScene.
	varEnableCorePerformanceOptimization = 6818,		// Boolean - Set to "true" to turn on performance enhancements in core drawing code

	varClassificationDescriptionMaximumLength = 6819,	// Int 		read only - Internal - get the Classification Lookup dialog Description maximum length
	varUpdateFilletRadius			= 6820,				// Force update the fillet radius value for tools using it. Relies on user saved settings.

	// Mass unit selectors
	varMassUnitIndex			= 6821,		// short	read/write - current Mass unit value based on VectorWorks::TrussAnalysis::EMassUnit
	varMassUnitPrecision		= 6822,		// short	read/write - current Mass unit precision
	varMassUnitShowUnitMark		= 6823,		// Boolean	read/write - display current Mass unit with unit mark
	varMassUnitMark				= 6824,		// TXString	read only - get current Mass unit mark
	varMassUnitName				= 6825,		// TXString	read only - get current Mass unit name
	varMassUnitScale			= 6826,		// double	read only - get current Mass units per gram
	
	// Force unit selectors
	varForceUnitIndex			= 6827,		// short	read/write - current Force unit value based on VectorWorks::TrussAnalysis::EForceUnit
	varForceUnitPrecision		= 6828,		// short	read/write - current Force unit precision
	varForceUnitShowUnitMark	= 6829,		// Boolean	read/write - display current Force unit with unit mark
	varForceUnitMark			= 6830,		// TXString	read only - get current Force unit mark
	varForceUnitName			= 6831,		// TXString	read only - get current Force unit name
	varForceUnitScale			= 6832,		// double	read only - get current Force units per neutin
		
	// Distributed Mass unit selectors
	varDistributedMassUnitIndex			= 6833,		// short	read/write - current Distributed Mass unit value based on VectorWorks::TrussAnalysis::EMassDistributedUnit
	varDistributedMassUnitPrecision		= 6834,		// short	read/write - current Distributed Mass unit precision
	varDistributedMassUnitShowUnitMark	= 6835,		// Boolean	read/write - display current Distributed Mass unit with unit mark
	varDistributedMassUnitMark			= 6836,		// TXString	read only - get current Distributed Mass unit mark
	varDistributedMassUnitName			= 6837,		// TXString	read only - get current Distributed Mass unit name
	varDistributedMassUnitScale			= 6838,		// double	read only - get current Distributed Mass units per gram/mm(kg/m)

	varEnableLegacy2DMode		= 6839,		// Boolean - Set to "true" to enable legacy 2D mode - // T02121 — Deprecate Screen Plane and Non-unified View

	// On-Demand Menu (ODM) Preferences variables
	varODMUse							= 6900,
	varODMShowAfterMouseIdles			= 6901,
	varODMMouseIdleTimer				= 6902,
	varODMShowWithSpacebar				= 6903,
	varODMShowWithMiddleMouseBtn		= 6904,
	varODMInitialLayout					= 6905,
	varODMSectionParams					= 6906,
	//End of ODM Preferences variables

	// On-Demand Menu (ODM) Preferences variables
	varShowSearchFilters				= 7000,
	varShowCommandContext				= 7001,
	//End of ODM Preferences variables

	varEnableLODForCachedObjects				 = 7005,
	varEnableLODForCachedObjects_FlushAll		 = 7006,
	varDisableAllLODForCachedObjectsExceptLowest = 7007,
	varHiddenLineHardwareOcclusion = 7008,

	varDisplayHomeScreenAtStartUp = 7009,
	varDisplayHomeScreenOnClosingLastDoc = 7010,

	varHideWireframeOnCachelessRasterViewport = 7011,

	varTessellationLimit = 7012,

	varEnableLegacyEightLights = 7100,

	varViewTransitionFlow = 7200,	// short read/write

	varDirectLink = 7300,

	varDisplayNonPrintableIndicators = 7301,	// Boolean	read/write turns on/off the Display Non-Printable Indicators option.

	varVGSVersion = 8278, // int read/write - events are send differently in different versions
};

typedef Sint32 SystemVarType;


// Old GetProgramVariable/SetProgramVariable names kept arounbd for SDK compatibility. [MAF 10/2/00]
#define	varUnit1DisplayFrac   162	// Sint32
#define	varUnit1DimPrecision  169	// Sint32
#define	varUnit2DisplayFrac   212	// Sint32
#define	varUnit2DimPrecision  219	// Sint32

#define varUnit1FlagShowDecAsFrac 168	// bitFlag
#define varUnit2FlagShowDecAsFrac 218	// bitFlag

#define	varDisplayDefaultContent  130	// Boolean
