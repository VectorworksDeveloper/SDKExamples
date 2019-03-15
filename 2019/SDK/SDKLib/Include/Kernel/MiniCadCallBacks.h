//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Declares most of the types specific to the SDK.
//	Includes the file which declares the entire set of SDK functions.
//



#ifndef _MINICADCALLBACKS_
#define _MINICADCALLBACKS_

#pragma once

#if _WIN_EXTERNAL_
#include <Windows.h>
#endif


#if (!_WIN_EXTERNAL_ && !_GSWINSDK_) && !defined(__FILES__)
	struct FSSpec;	// For MiniCadCallBacks.Defs.h
#endif

#include "Objs.TDType.h"

#if _MINICAD_ && !defined(_OBJS_BLANKTYPE_H_)
	// Need the definition of 'MCObjectHandle' from "Objs.BlankType.h".
	#include "Objs.BlankType.h"
#endif

#include "MiniCadHookIntf.h"
#include "MCCoordTypes.h"
#include "CallbackParamTypes.h"
#include "MiniCadCallbacks.X.h"
#include "GSGeometry.h"
#include "GSString.X.h"
#include "GSLogging.h"
#include "MCNotification.h"
#include "Misc.Graphics.h"
#include "UuidStorage.h"

class TToolHandler;
struct ICoreToolAccess;


#if _MINICAD_
	// These are here so that code can be copied from externals
	// into the application without modification.
	#define GSCalledRoutineSetup(cbp)
	#define GSExternalSetup(cbp)
	#define	GSExternalSetdown(val)
#endif



void GS_API SetupGlobalCBP(CallBackPtr cbp);



//////////////////////////////////////////////////////////////////////////////////////////
// Notification types


typedef Sint32 StatusID;
typedef SintptrT StatusData;
typedef void (*StatusProcPtr)(StatusID, StatusData);


//////////////////////////////////////////////////////////////////////////////////////////
// Part codes for TrackTool

const short cursOnNothing		= 1;
const short cursOnObject		= 2;
const short cursOnHandle		= 3;
const short cursOnSpecialPart	= 6;	// Dimension, symbol in wall, etc.


//////////////////////////////////////////////////////////////////////////////////////////
// Undo Method Selectors

const short kUndoNone				=  0;
const short kUndoReplaceSelection	= 17;
const short kUndoSwapObjects		= 21;
const short kUndoCustom				= 26;
const short kUndoOnlyViewChange		= 30;
//const short kUndoEndEvent			= 50;  // obsolete [MAF 6/29/98]



//////////////////////////////////////////////////////////////////////////////////////////
// DXF import or export.

enum EDXFError {
	kDXFErr_UnknownError 					= -1,
	kDXFErr_NoError							= 0, 
	kDXFErr_Cancelled						= 1, 
	kDXFErr_BadInput						= 2, 
	kDXFErr_DocumentNotEmpty				= 3,
	kDXFErr_OutOfMemory						= 4,
	kDXFErr_InvalidOrExtremeUnitsOrScale	= 5,
	kDXFErr_InitADFailed					= 6,
	kDXFErr_ReferenceCreated				= 7
};

const short /*DXFColorIndex*/	kUnmappedDXFColor	= -1;
const short /*Mils*/ 			kUnmappedLineWeight = -1;

// Constants for standard DXF colors (DXFColorIndex == short). OpenDWG constant to the right.
// kDXFColorByBlock should not be used in export unless you know what you are doing.
const short kDXFColorByBlock		= 0;	// AD_COLOR_BYBLOCK
const short kDXFRed					= 1;	// AD_COLOR_RED
const short kDXFYellow				= 2;	// AD_COLOR_YELLOW
const short kDXFGreen				= 3;	// AD_COLOR_GREEN
const short kDXFCyan				= 4;	// AD_COLOR_CYAN
const short kDXFBlue				= 5;	// AD_COLOR_BLUE
const short kDXFMagenta				= 6;	// AD_COLOR_MAGENTA
const short kDXFBlackOrWhite		= 7;	// AD_COLOR_WHITE
const short kDXFDarkGray			= 8;
const short kDXFLightGray			= 9;	
const short kDXFColorByLayer		= 256;	// AD_COLOR_BYLAYER

// Constants for default compression
// Should stay in sync with items in 'MENU' 455
const short kPrefDefaultRenderCompressionJPEG	= 1;
const short kPrefDefaultRenderCompressionPNG	= 2;

// Constants for allowing interactive symbol scaling
const short kInteractiveScalingNever = 1;
const short kInteractiveScalingAlwaysWarn = 2;
const short kInteractiveScalingAlwaysNoWarn = 3;


//////////////////////////////////////////////////////////////////////////////////////////
// Layer and class options 
// Internal: ELayerOptionsFlag Short2LayerOptionsFlag(short val); etc.

enum ELayerOptions {
	kLayersActive					= 1,
	kLayersGrayOthers				= 2,
	kLayersShowOthers				= 3,
	kLayersShowSnapOthers			= 4,
	kLayersShowSnapModifyOthers		= 5,
	kLayersGraySnapOthers			= 6,
};

enum EClassOptions {
	kClassesActive					= 1,
	kClassesGrayOthers				= 2,
	kClassesShowOthers				= 3,
	kClassesShowSnapOthers			= 4,
	kClassesShowSnapModifyOthers	= 5,
	kClassesGraySnapOthers			= 6,	
};


//////////////////////////////////////////////////////////////////////////////////////////
// Wall Join Options - used with GS_WallJoin

typedef short JoinModifierType;

const JoinModifierType kTWallJoin 		= 1; 
const JoinModifierType kLWallJoin 		= 2;
const JoinModifierType kXWallJoin 		= 3;
const JoinModifierType kAutoWallJoin 	= 4; // ignores input points and automatically determines the kind of join (T or L or X)
const JoinModifierType kAutoLWallJoin 	= 5; // ignores input points and automatically creates L join using the longest portion of the walls




//////////////////////////////////////////////////////////////////////////////////////////
// Constants for selectors for GetProgramVariable and SetProgramVariable

// XXX_JDW_MISC - i might have seen a duplicate enum somewhere...
enum EAngularUnits {
	kDegrees	= 0,
	kRadians	= 1,
	kGradians	= 2
};

// The values below indicate menu index.
enum EDXFBlockAttributeHandling	{
	kBAH_MinimumLegalValue		= 1,
	kBAH_PreserveLookAndLinks	= 1,
	kBAH_PreserveLook			= 2, 
	kBAH_LinkVisible			= 3, 
	kBAH_LinkAll				= 4,
	kBAH_Hide					= 5,
	kBAH_MaximumLegalValue		= 5
};

enum EDXF2D3DImportHandling {
	k23D_MinimumLegalValue	= 1,
	k23D_All2D				= 1,
	k23D_2Dand3D			= 2, 
	k23D_All3D				= 3,
	k23D_MaximumLegalValue	= 3
};

enum EDXFUnits
// These are the values AutoCAD 2000 defines for units for scaling of inserted blocks.
{
	kDU_MinimumLegalValue	= 0,
	kDU_Unitless			= 0,	// valid coming in from AutoCAD file; not valid to set; but currently used to mean "custom"
	kDU_Inches				= 1,
	kDU_Feet				= 2,
	kDU_Miles				= 3,
	kDU_Millimeters			= 4,
	kDU_Centimeters			= 5,
	kDU_Meters				= 6,
	kDU_Kilometers			= 7,
	kDU_Microinches			= 8,
	kDU_Mils				= 9,
	kDU_Yards				= 10,
	kDU_Angstroms			= 11,
	kDU_Nanometers			= 12,
	kDU_Microns				= 13,
	kDU_Decimeters			= 14,
	kDU_Dekameters			= 15,
	kDU_Hectometers			= 16,
	kDU_Gigameters			= 17,
	kDU_AstronomicalUnits	= 18,
	kDU_LightYears			= 19,
	kDU_Parsecs				= 20,
	kDU_MaximumLegalValue	= 20
};

enum EDXFPlotUnits { 
	kDPU_MinimumLegalValue	= -1,
	kDPU_ByLayout			= -1,	// defined by us as flag
	kDPU_Inches				= 0, 	// defined by AutoCAD
	kDPU_Millimeters		= 1, 	//
	kDPU_Pixels				= 2,	//
	kDPU_MaximumLegalValue	= 2
};

enum EDXFExternalRefsHandling {
	kERH_MinimumLegalValue	= 0,
	kBindExternalRefs		= 0,
	kIgnoreExternalRefs		= 1,
	kCreateVWRefs			= 2,
	kUseLayerImport			= 3,
	kERH_MaximumLegalValue	= 3
};

enum EDXFConversionRes {
	kCR_MinimumLegalValue	= 0,
	kCR_VWConversionRes		= 0,
	kCR_Low					= 1,
	kCR_Medium				= 2,
	kCR_High				= 3,
	kCR_VeryHigh			= 4,
	kCR_MaximumLegalValue	= 4
};

//////////////////////////////////////////////////////////////////////////////////////////
// Parametric state event sending flags
// Note! You can OR those flags

typedef short TParametricStateFlags;

const TParametricStateFlags kParametricStateEvent_NoStateEvents 		= 0; 
const TParametricStateFlags kParametricStateEvent_ResetStatesEvent		= 1;
const TParametricStateFlags kParametricStateEvent_InternalStatesEvent	= 2;

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
	varMoveObjArrow		  = 74,		// short (1-arrow, 2-cmd+arrow, 3-shift+arrow, 4-shift+cmd+arrow, 5-disabled) - Public for VS
	varNudgeObjArrow	  = 75,		// short (1-arrow, 2-cmd+arrow, 3-shift+arrow, 4-shift+cmd+arrow, 5-disabled) - Public for VS
	varPanArrow		  	  = 76,		// short (1-arrow, 2-cmd+arrow, 3-shift+arrow, 4-shift+cmd+arrow, 5-disabled) - Public for VS
	varSwitchActLCArrow	  = 77,		// short (1-arrow, 2-cmd+arrow, 3-shift+arrow, 4-shift+cmd+arrow, 5-disabled) - Public for VS
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

	varViewTransitionAnimation						= 1227, // double	read/write

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
				offset_group_AppearanceProps_GeneralCursorPositionHighlightingOnRuler		= 48 * 30,


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
	
	varHideGPUDisplayAlertDialog	= 6809,				// Boolean - Set to "true" to prevent the error dialog found in VGMProxy.cpp from showing
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


//////////////////////////////////////////////////////////////////////////////////////////
// Tool Objects
enum EToolObjectType {

	kSnapObject,	//	an invisible object is added to the drawing
	kInternalUse1,
	kInternalUse2
};

struct TAddToolObjectData
{
	MCObjectHandle 	fAddObject;
	EToolObjectType	fType;
};

struct MultipleReshapeEventData
{
	MCObjectHandle	fMarqueePoly;
	WorldPt			fMarqueeMoveDistance;
};

//////////////////////////////////////////////////////////////////////////////////////////
// SmartCursor Grid options

//////////////////////////////////////////////////////////////////////////////////////////
// SmartCursor Grid options
enum EGridOptions {
	kGridNone				= 0,
	kGridNormal				= 1,	
	kGridDisableAll			= 2,	
	kGridDisableFloating	= 4		
	//kGridDisableZoom		= 8,
	//kGridPalAlreadySetUp	= 16
};

//////////////////////////////////////////////////////////////////////////////////////////
//	SmartCursor constaint options
enum EConstrainModes {
	eNoConsModes,
	ePointConsModes,
	eLineConsModes,
	eBoxConsModes,
	eLineConsModesSpec,
	eBoxConsModesSpec,
	eHorVerModes,
	eUnlockSpecialAngle,
};

enum EConstrainType {
	kConsNone			= 0,	//defaults to kConsAngle
	kConsSnapToGrid		= 1,
	kConsSnapToObject	= 2,
	kConsAngle			= 3,	//standard vector constrain mode
	kConsIntersect		= 4,	
	kConsSmartSearch	= 5,	
	kConsFraction		= 6,
	kConsSurface 		= 7,	
#ifdef USE_VW2009_LOGIC_WPCONS_COVERSEDGE
	kConsWP3D			= 7,
#endif
	kConsTangent 		= 8,	
#ifdef USE_VW2009_LOGIC_WPCONS_COVERSEDGE
	kConsWPNormal3D		= 8,
#else
	kConsWP3D			= 8,
#endif
	kConsHorVer			= 9,	//alternate vector constrain mode
	kConsHor 			= 10,	//alternate vector constrain mode
	kConsVer 			= 11,	//alternate vector constrain mode
	kConsSpecialAngle 	= 12,	//alternate vector constrain mode
	kConsSymmetry		= 13,	//alternate vector constrain mode
	kConsParallel		= 14,	//in here for it's old use in tdlist.cpp
#ifdef USE_VW2009_LOGIC_WPCONS_COVERSEDGE
	kConsLockAngle		= 15	//alternate vector constrain mode,always in locked angle mode
#else
	kConsLockAngle		= 15,	//alternate vector constrain mode,always in locked angle mode
	kConsWPNormal3D		= 16
#endif
};

//////////////////////////////////////////////////////////////////////////////////////////
//	DataBar specifiers
enum TDBarModes {
	kVWInternalCustomBar = -2,
	kStandardCustomBar = -1,
	kBlankDataDisplayBar = 0,
	kXYClLaZo = 1,
	kXY = 2,
	kSaAaLAXY = 3,
	kDxDyRaAXY = 4,
	kDxDyTlAXY = 5,
	kDxDyRXY = 6,
	kDxDyLAXY = 7,
	kDxDyArPeXY = 8,
	kA = 9,
	kDxDyLOXY = 10,
	kDxDySxSyXY = 11,

	kXYZClLaZo = 12,
	kVxVyVzYaPi = 13,     // Walkthough Tool pre-VW2013
	kDK = 14,             // formerly kVz (but wasn't really Vz)
	kDa = 15,
	kAzEl = 16,
	kAzElRo = 17,
	kVxVyVzLrUdIo = 18,
	kU1Aw = 19,
	kThXYZ = 20,
	kO1O2WrWhZ = 21,
	kWbWtDz = 22,
	kXYU1 = 23,
	kRaRrRuXYZ = 24,
	kClLaZo = 25,
	
	kLADxDyXY = 26,

	kDzZ = 27,
	kDxDyDzXYZ	= 28,
	k3DDxDyXY = 29,

	kAw = 30,
	kXYZDxDyDz	= 31,
	kXYZ		= 32,
	kDxDyDz		= 33,

	kVzIo		= 34,

	kYaVxVy     = 35,       // Yaw, ViewerX, ViewerY:  Walkthrough Tool VW2013
	kYaPi       = 36,       // Yaw, Pitch:             Walkthrough Tool VW2013
	kVz         = 37,       // ViewerZ:                Walkthrough Tool VW2013
	
	kDxDyLAXYForRect = 38,

	kLastBarMode
};


//////////////////////////////////////////////////////////////////////////////////////////
// Selectors for DoProgramAction

enum {

	doSelector0 = 0,
	doSelector1 = 1,
	doSelector2 = 2,
	doSelector3 = 3,
	doSelector4 = 4,
	doSelector5 = 5,
	doSelector6 = 6,
	doSelector7 = 7,
	doSelector8 = 8,
	doSelector9 = 9
};

//////////////////////////////////////////////////////////////////////////////////////////
#include "FolderSpecifiers.h"

typedef Sint32 FolderSpecifier;

typedef void* VoidPtr;

///////////////////////////////////////////////////////////////////////////////////////////
// File Permissions. Use these to open resource files for reading or writing

// Changed by JDW, [2004-08-02] - See permission comments in ResHandler.X.cpp
//const Byte kFileReadPermission = 1;
const Byte kFileReadPermission = 0;					// RsrcMgr::kReadPermission		= 0		// fsCurPerm	= 0x00,   
//const Byte kFileWritePermission = 2;
const Byte kFileReadWritePermission = 3;			// RsrcMgr::kWritePermission	= 3		// fsRdWrPerm	= 0x03
//const Byte kFileReadWriteSharePermission = 4;	
const Byte kFileReadWrite = kFileReadWritePermission;


//////////////////////////////////////////////////////////////////////////////////////////
// GSErrors

typedef Uint32 GSError;

typedef GSError MCErr;

// No error occurred.
const GSError noError =				0x00000000;

// general errors
const GSError badParameterErr =		0x01000001;	// One or more of the parameters passed to the
												// SDK function are illegal. This can include nil handles.

// general MiniCAD Object errore
const GSError illegalObjectErr =	0x02000004;	// Can't do the requested operation on this object.

// Operating system related errors
const GSError otherOSErr =			0x03000001;	// Unspecified operating system error
const GSError fileNotFoundErr =		0x03000002;	// No such file
const GSError dirNotFoundErr =		0x03000003;	// No such directory
const GSError illegalNameErr =		0x03000004;	// bad filename
const GSError diskFullErr =			0x03000005;	// disk or directory full
const GSError duplicateFilenameErr =0x03000006;	// filename already exists
const GSError lockedErr =			0x03000007;	// file or volume locked
const GSError fileInUseErr =		0x03000008;	// file is already open

// other errors
const GSError nameNotUniqueErr =	0x04000001;	// Object name not unique
const GSError nameTableFullErr =	0x04000002;	// Name table is full -- can't add any more names.


//////////////////////////////////////////////////////////////////////////////////////////
// Type definitions

// JAK 10/17/97
// I don't know why Str20 is defined as 22 bytes instead of 21 bytes.  
// Apple's convention (in Types.h) is to defined it one byte bigger than name because of length byte.
// Perhaps this definition includes a byte of padding, so it is an even size.
// I cannot change its size now because of dependencies (both internal and external), 
// and don't have time to rename it to Str21.
	
//  yes str20                             

typedef unsigned char Str63[64];
typedef unsigned char Str20[22];


typedef Sint32  InternalIndex;  // represents a SysName

//=======================================================================================
// typedef of InternalName
typedef TXString InternalName;	// InternalName is TXString.

typedef void* MCObjectHandleID;	//  A few APIs use this type to provide a reference ID for a MCObjectHandle
typedef void* CustomBarRefID;		//	Custom Bar APIs use this type to provide a reference ID for a (opaque) CustomBar
typedef void* HotSpotRefID;		//	HotSpot APIs use this type to provide a reference ID for a (opaque) HotSpot.

// XXX_64BIT_VML This is sort of kind of evil...why is this required? And is there a better way to get this info?
#define kUserDataTypeSize 76

#ifndef _MINICAD_
	struct ObjectColorType {
		ColorRef fillFore, fillBack, penFore, penBack;
	};

inline bool operator==(const ObjectColorType& o1, const ObjectColorType& o2)
	{ return o1.fillBack == o2.fillBack && o1.fillFore == o2.fillFore && o1.penBack == o2.penBack && o1.penFore == o2.penFore; }
inline bool operator!=(const ObjectColorType& o1, const ObjectColorType& o2)
	{ return !(o1 == o2); }


	struct UserDataType {
		char      reserved[kUserDataTypeSize];
		/*  User data goes here
		*/
	};
#endif


//////////////////////////////////////////////////////////////////////////////////////////
// Text


// kTextError is returned in place of vertical, horizontal, flip, or spacing constants
// or text length in case there is a parameter error in the SDK call

const short kTextError = -1;

// text flip
enum {
	kTextNoFlip = 0,
	//kTextHorizontalFlip = 1,		- equivalent to kTextVerticalFlip and 180 degree rotation.
	kTextVerticalFlip = 2
};

// text style
// NOTE - Outline and Shadow text styles are only displayed on the Mac.
enum {
	kTextStylePlain		= 0,
	kTextStyleBold		= 1,
	kTextStyleItalic	= 2,
	kTextStyleUnderline	= 4,
	kTextStyleOutline	= 8,
	kTextStyleShadow	= 16
};
typedef short TStyle;

// text vertical alignment
enum {
	kTextGeneralJustifyVertical = 0,			// only used by the Worksheet
	kTextTopBox = 1,
	kTextTopBaseline = 2,
	kTextCenterBox = 3,
	kTextBottomBaseline = 4,
	kTextBottomBox = 5
};
typedef short TVAlignment;


// text horizontal alignment
enum {
	kTextGeneralJustify = 0,			// only used by the Worksheet
	kTextLeftJustify = 1,
	kTextCenterJustify = 2,
	kTextRightJustify = 3,
	kTextJustify = 4
};
typedef short THAlignment;



// text vertical spacing
enum {
	kTextCustomLeading = 0,
	kTextSingle = 2,
	kTextThreeHalves = 3,
	kTextDouble = 4
};
typedef short TSpacing;


const short kTextNoSelection = -1;	// use this constant when there is more than one selection

// flags for disabling controls in the format text dialog
// ABZ: These flags should be either recalculated or used by a NAND bitwise operatot rather than an AND bitwise operator.
typedef Byte TDisableMask;

const Byte kFontFlag 		= 0x01;
const Byte kSizeFlag 		= 0x02;	
const Byte kSpacingFlag 	= 0x04;
const Byte kStyleFlag		= 0x08;
const Byte kHAlignFlag		= 0x10;
const Byte kVAlignFlag		= 0x20;
const Byte kWorksheetFlag	= 0x40;


struct FormatTextType { 
	
	// all fields but the disable mask are input and output fields
	// input values indicate the dialog defaults
	// ouput values indicate the user selection

    FormatTextType();

	TXString		ioFontName; 	// empty for no selection
	Byte			ioStyle;		// uses the Mac style constants, 0xff for no selection	
	Byte			ioCustomStyle;	// none = 0; superscript = 32; subscript = 64
	WorldCoord		ioSize;    		// the font size in WorldCoord's
	TSpacing		ioSpacing;		// see TSpacing constants above
	WorldCoord		ioLeading;		// custom leading in WorldCoord's, -1 for no selection
	THAlignment		ioHAlignment;
	TVAlignment		ioVAlignment;
    Sint32          ioTextStyle;    // text style ref number.  -1 for no selection
    Byte            ioStyleMask;     // Add style mask value for indeterminate font style states (multi selection)
	TDisableMask	iDisableMask;	// pass 0 to enable all controls    
	bool 			cFlag;          // Control status of FormatTextDialog Ok/Cancel button
};


// There will likely be more flags here later - JDW
enum EStringCompare 
// Used for GS_CStringEqual() and GS_CStringCompare()
// VW names use kIgnoreCase and kIgnoreDiacritics for GS_CStringEqual():  
//		'foo' and 'Fo<umlaut>o<acute>' are equal strings
// VW normally uses kIncludeCase for sorting strings with GS_CStringCompare()
{
	kIncludeCase			= 0x0001,	// A != a
	kIgnoreCase				= 0x0002	// A == a
//	kIncludeDiacritics		= 0x0004,	// A != A<umlaut>
//	kIgnoreDiacritics		= 0x0008,	// A == A<umlaut>	Currently diacritics are always ignored 
};

enum EStringCompareResult 
// Used only for GS_CStringCompare (GS_CStringEqual returns a boolean)
{
	kEqualStrings			= 0,
	kFirstStringSmaller		= -1,
	kFirstStringBigger		= 1
};

//////////////////////////////////////////////////////////////////////////////////////////
// VertexType - for specifying polyline vertices

enum {
	vtCorner		= 0,
	vtBezier		= 1,
	vtCubic			= 2,
	vtArc			= 3,
	vtRadius		= 4
};
typedef Sint32 VertexType;


//	
enum {
	kPolyDirectionClockwise				= -1,
	kPolyDirectionCounterClockwise		= 0,
	kPolyDirectionError					= 1
};
typedef Sint32 PolyDirectionSpecType;

enum {
	kLowConvertToPolyResolution	= 16,
	kMedConvertToPolyResolution	= 64,
	kHighConvertToPolyResolution	= 128,
	kVeryHighConvertToPolyResolution = 512
};
typedef short TConvertToPolyResolution;

struct SPolyEdge
{
	WorldPt		fStartPt;
	WorldPt		fControlPt;
	WorldPt		fEndPt;
	WorldCoord	fRadius;
	VertexType	fType;
	bool		fVisible;
};

//////////////////////////////////////////////////////////////////////////////////////////
// ArrowType - for specifying arrowheads using the old style calls

enum {
	arArrow			= 0,
	arTightArrow	= 1,
	arBall			= 2,
	arSlash			= 3,
	arCross			= 4
};
typedef Sint32 ArrowType;


//////////////////////////////////////////////////////////////////////////////////////////
// MarkerType - for specifying marker styles using the new marker calls

enum {
// Simple Constants
	// Tail
	kTailMarker					= 32768,  // Meaningless for kCircleMarker, kDimCrossMarker, kLassoMarker, kHexagonMarker, kConeMarker and kRectangleMarker
	// Half Tick
	kLeftHalfTickMarker			= 16384,  // Half-Tick Constants Meaningless for kLassoMarker and kConeMarker
	kRightHalfTickMarker		= 24576,
	// Base
	kFlatBaseMarker				= 0,
	kOpenBaseMarker				= 1024,   // Base Constants only Meaningful for kArrowMarker and kConcaveCurvedArrowMarker
	kAngleBaseMarker			= 2048,
	kArcBaseMarker				= 3072,
	// Fill
	kLineColorFillMarker		= 0,
	kWhiteFillMarker			= 128,    
	kNoFillMarker				= 256,	  // kNoFillMarker is the only valid setting for kLassoMarker, kDimSlashMarker, kDimCrossMarker, 
	// Root Type
	kArrowMarker				= 0,
	kConcaveCurvedArrowMarker	= 1,
	kCircleMarker				= 2,
	kDimSlashMarker				= 3,
	kDimCrossMarker				= 4,
	kLassoMarker				= 5,
	kHexagonMarker				= 6,
	kVShapedMarker				= 7,
	kConeMarker					= 8,
	kTaperedVShapedMarker		= 9,
	kSShapedMarker				= 10,
	kRectangleMarker			= 11,
	kDoubleLineMarker			= 12,
	
// More Useful Composite Constants. Use these instead of certain Simple Constants.
	kOpenBaseNoFillMarker		= 1280,	// Use this for any Open Base marker instead of just kOpenBaseMarker. You don't want it to have a fill.
	kNoFillLassoMarker			= 261,  // Use this for any Lasso Marker instead of kLassoMarker
	kNoFillDimSlashMarker		= 259,  // Use this for any Lasso Marker instead of kLassoMarker
	kNoFillDimCrossMarker		= 260,  // Use this for any Cross Marker instead of kDimCrossMarker
	kNoFillConeMarker			= 264,  // Use these for Cone Markers as appropriate instead of kConeMarker
	kWhiteFillConeMarker		= 136
};

const CBUnsignedShort kMarkerRootTypeMask = 127;	// && with a MarkerType to get just the RootType ( example: if((myMarkerType && kMarkerRootTypeMask) == kArrowMarker) { doSomething(); } )
const CBUnsignedShort kMarkerFillMask = 896;		// && with a MarkerType to get just the Fill
const CBUnsignedShort kMarkerBaseMask = 7168;		// && with a MarkerType to get just the Base
const CBUnsignedShort kMarkerHalfTickMask = 24576;	// && with a MarkerType to get just the Half-Tick value (0 is a Full marker)
const CBUnsignedShort kMarkerTailMask = 32768;		// && with a MarkerType to get just the Tail value (0 is "not tail")

typedef signed char MarkerVisibility;
const MarkerVisibility  kMarkerVisibilityUndefined = -1;		
const MarkerVisibility	kMarkerVisibilityMarkerNotVisible = 0;		
const MarkerVisibility	kMarkerVisibilityMarkerVisible = 1 ;  	

typedef signed char MarkerThicknessBasis;
const MarkerThicknessBasis	kMarkerThicknessLineThickness = 0;
const MarkerThicknessBasis	kMarkerThicknessDimThickness = 1;
const MarkerThicknessBasis	kMarkerThicknessCustomThickness = 2;

const MarkerThicknessBasis	kMarkerThicknessUnitsMils = 0;
const MarkerThicknessBasis	kMarkerThicknessUnitsPoints = 16;
const MarkerThicknessBasis	kMarkerThicknessUnitsMillimeters = 32;

const MarkerThicknessBasis	kMarkerThicknessBasisMask = 15;
const MarkerThicknessBasis	kMarkerThicknessUnitsMask = -16;

typedef CBUnsignedShort MarkerType;

//////////////////////////////////////////////////////////////////////////////////////////
// SMarkerStyle - structure for setting markers using the SDK calls

struct SMarkerStyle {
	MarkerType	style;
	Sint8		nAngle;
	double		dSize;
	double		dWidth;
	Uint8		nThicknessBasis;
	double		dThickness;
	
};

// Example of how to use the marker constants:
//
// SMarkerStyle marker;
// marker.style =  kArrowMarker + kOpenBaseNoFillMarker;											/* MarkerType */
// marker.nAngle = 15;																				/* Angle */
// marker.dSize = 0.125;																			/* Length */
// marker.dWidth = 0.125;																			/* Width */
// marker.nThicknessBasis = kMarkerThicknessCustomThickness + kMarkerThicknessUnitsMillimeters;		/* Thickness Basis & Units */
// marker.dThickness = 2.0;																			/* Thickness Value */
//
//	GS_SetObjBeginningMarker(	object /* theObject */ , marker /* The marker */, kMarkerVisibilityMarkerVisible /* Visibility */);									
//
//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
// SDropShadowData - Structure for getting and setting Drop Shadow data using the SDK calls

// Drop Shadow data units constants
const short kDropShadowDataUnitsPage	= 0;
const short kDropShadowDataUnitsWorld	= 1;

struct SDropShadowData
{
	Boolean		fUseDropShadow;	// Whether or not to use a Drop Shadow
	short		fUnits;			// The units - Possible values are Drop Shadow data units constants
	double		fOffset;		// The offset
	double		fBlurRadius;	// The blur radius
	double		fAngle;			// The angle in degrees
	ColorRef	fColor;			// The color
	OpacityRef	fOpacity;		// The opacity
};

//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
// Text style descriptoin
struct STextStyle {
	Sint16			fontIndex;
	Sint32			nFontSize;
	bool			bBold;
	bool			bItalic;
	bool			bUnderlined;
};

//////////////////////////////////////////////////////////////////////////////////////////
// BoundsType - for what kind of bounds to retrieve

enum {
	kGeometricBounds			= 0,	// for an object like a locus, just gives the point the locus is at
	kRefreshBounds				= 1		// for an object like a locus, gives a rectangle that encloses what
										// is drawn on screen to represent the locus
};
typedef CBSignedShort BoundsType;



//////////////////////////////////////////////////////////////////////////////////////////
// Selectors for ForEachObject

enum {
	allSelected					= 0,
	allEditable					= 1,
	allVisible					= 2,
	allDrawing					= 3,
	allSymbolDefs				= 4,
	allSelectedAndEditable		= 5,
	allObjects					= 6,
	
	descendIntoGroups = 32,
	descendIntoAll = 64,
	descendIntoViewports = 128,
	descendIntoAuxLists = 256
};


//////////////////////////////////////////////////////////////////////////////////////////
// TNumStyle - for worksheets & records

typedef unsigned char			TNumStyleClass;

const TNumStyleClass
// XXX_JDW_ALTURA [2003-02-24] - Check this - might be wrong
	// The first four are treated the same by GS_StringToDouble,
	// allowing international formats like "1.300,24", 
	// and can do math, but do not allow fractions like
	// 1 5/8  (just 5/8 will work). One of the international 
	//	thousands separators is a space, so "1 234/500" is ambiguous.
	nsGeneral				= 0,
	nsFixDecimal			= 1,
	nsDecwCommas			= 2,
	nsScientific			= 3,	// Exponential: 1.567e+56, 2.678e-94, etc.

	nsFractional			= 4,	// Numbers like 1/2, 34 7/64. Denominator is power of 2 up to 64.
	nsDimension				= 5,	// in WorldCoords / drawing units
	nsAngle					= 6,	// Degrees 
	nsDate					= 7,
	nsConditional			= 8,	// Boolean - don't use unless you know what it's for.
	nsGeneralFrac			= 9,	// Fraction with unreduced denominator that is (currently, 2/22/00)
									//	105840000 == 128 * 27 * 625 * 49  (2^7 * 3^3 * 5^4 * 7^2 
									//  for components of nice typical denominators)
	nsDimensionWithDivider	= 10,	// Same as nsDimension but for use in output-only situations where the 
									//	current units format is feet and inches
									//	and you want a feet and inch divider. ie, 10'-5" vs 10'5".
									//	Do not use in any edit text fields because the divider dash will be 
									//	mistaken for a minus sign. 
	nsDimensionArea			= 11,
	nsDimensionVolume		= 12,
	nsText					= 13,	//Text Format For Worksheets
	nsPercentage			= 14,	//Percentage format: 0.2 would display as 20%


	nsUseDefault			= 127;	// Special case for telling conversion routine to use format's style.
									//	Don't use it unless you know what it's for.


//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

struct TNumStyle {
	TNumStyleClass				numStyleClass;	// Number style.
	Sint8						accuracy;		// see comment below
	
	void ByteSwap() { }	// Nothing to swap.
};

#pragma pack(pop) // END 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)
//--------------------------------------------------------------------


/* The accuracy field represents:
		for general: May be ignored by some routines; overrides default max # of decimal places.
		for fixDecimal, decwCommas, and scientific: The # of decimal places.
		for fractional: Denominator to round to minus 2. (e.g. to round to nearest 1/2, store 0.)
		for dimension: Ignored.
		for angle: 1 = , 2 = ', 3 = '".
		for date : Date format.
*/

typedef TNumStyle				TNumStyleRef;

//////////////////////////////////////////////////////////////////////////////////////////
// TCellBorderRefNum for worksheet cell borders - version for SDK/VS callers.
// This is not the structure stored in the file, nor is it used internally in worksheet processing.
//--------------------------------------------------------------------
struct TCellBorderRefNum {
	Uint8		Weight;		// border line weight
	InternalIndex	Style;	// border line style
	ColorRef	Color;		// border color
	Bool8		Enable;		// Is this border visible?

};

//--------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------------
// Export 3DS Render types and enums.

struct STessVertex {
	WorldPt3	pt;			// coordinate of vertex
	WorldPt3	normal;		// normal of this vertex
	double		u;			// texture U coordinate for vertex
	double		v;			// texture V coordinate for vertex
};

struct STessMaterial {
	Sint32			materialRef;
	GSColor			objColor;
	MCObjectHandle	hMaterial;
	float			transparency;	// 0.0 - no transparency; 1.0 - fully transparent
};

struct STessTraingle {
	STessVertex		A;
	STessVertex		B;
	STessVertex		C;
	size_t			indexA;				// index of vertex A
	size_t			indexB;				// index of vertex B
	size_t			indexC;				// index of vertex C

	STessMaterial	material;
	WorldCube		totalBoundingCube;	// total bounding cube untill this triangle

	size_t			totalVertexCount;	// total count of vertices in this mesh
	size_t			totalFacesCount;	// total count of faces in this mesh
	MCObjectHandle	objectHandle;		// the object when reason == kTessProcObject
};

enum ETessProcReason {
	kTessProcBeginFace,
	kTessProcAddTriangle,
	kTessProcEndFace,
	kTessProcObjectBegin,
	kTessProcObjectEnd,
};

typedef void*	TTesselator;
typedef void (*GS_TessellateIteratorProcPtr)(ETessProcReason reason, STessTraingle triangle, CallBackPtr cbp, void* pEnv);


//////////////////////////////////////////////////////////////////////////////////////////
//	Field Types
//
//	Used by RecordHandler, RecordNode, FormatNode, Plug-ins (formerlay known as Externals), Plug-in Objects,
//	both internally and externally.
//	Constants kFieldCoordDisp through kFieldCoordLocY were added 10/7/97 for new Plug-in Object fields.
//
//	JAK 9/1/98
//	These constants were moved here from both RecordHandler.x and MObject.h.
//	They are easier to maintain if there is one set of constants defined in one place.


enum EFieldStyle {
	kFieldLongInt		= 1,
	kFieldBoolean		= 2,
	kFieldReal			= 3,
	kFieldText			= 4,
	kFieldCalculation	= 5,
	kFieldHandle 		= 6,
	kFieldCoordDisp		= 7,
	kFieldPopUp			= 8,
	kFieldRadio			= 9,
	kFieldCoordLocX		= 10,	
	kFieldCoordLocY		= 11,
	kFieldStaticText	= 14,
	kFieldControlPoint	= 15,
	kFieldDimStdPopUp	= 16,
	kFieldPrecisionPopUp = 17,
	kFieldClassesPopup	= 18,
	kFieldLayersPopup	= 19,
	kFieldAngle			= 20,
	kFieldArea			= 21,
	kFieldVolume		= 22,
};

//
// EPluginObjectSubType indicates the subtype of the Plug-in Object.
// 		kHybridSymbolLike is a point-based object, introduced in VW 8.0.0
// 		kLineLike and kBoxLike objects behave similar to lines and rotated rectangles, introduced in VW 8.5
//		k2DPathLike and k3DPathLike were introduced in VW 9.0.0
//
// 4/7/2000, JAG:
// Moved this enum here from ParametricObj.h, renamed the type, and added kPathLike.


#define GS_CustomSubtype_SAJ 

enum EPluginObjectSubType {kHybridSymbolLike = 0, kLineLike = 10, kBoxLike = 20, k2DPathLike = 30, k3DPathLike = 40
#ifdef GS_CustomSubtype_SAJ
, kCustomSubtype = 50	//	Object definition handles custom insertion eventss
#endif	//	GS_CustomSubtype_SAJ
};
const Sint32 kPathPlugin = 0xa0a0b0b0;		// Special message value to indicate that a path plugin is calling the tool.


//////////////////////////////////////////////////////////////////////////////////////////
//	SDK Plug-in Library Routine Argument Types
//
//	Used by SDK Plug-in Library Routines to describe the types of their arguments.
//	Enter these numbers into the 'VLIB' resource's "Argument Type" field.
//
typedef short	EPluginLibraryArgType;
const EPluginLibraryArgType 	kNullArgType 			= 0;
const EPluginLibraryArgType 	kIntegerArgType			= 1;		// use intValue field of PluginLibraryArg structure below...
const EPluginLibraryArgType 	kIntegerVarArgType		= 2;		// use intValue - output
const EPluginLibraryArgType 	kLongArgType			= 3;		// use longValue
const EPluginLibraryArgType 	kLongVarArgType			= 4;		// use longValue - output
const EPluginLibraryArgType 	kRealArgType			= 5;		// use realValue
const EPluginLibraryArgType 	kRealVarArgType			= 6;		// use realValue - output
const EPluginLibraryArgType 	kAngleArgType			= 7;		// use realValue
const EPluginLibraryArgType 	kDistanceArgType		= 8;		// use realValue
const EPluginLibraryArgType 	kPointArgType			= 9;		// use ptValue in SDK.  Use 2 REAL variables in VS.
const EPluginLibraryArgType 	kGlobalPointArgType		= 10;		// use ptValue in SDK.  Use 2 REAL variables in VS.
const EPluginLibraryArgType 	kGlobalPointVarArgType	= 11;		// use ptValue in SDK.  Use 2 REAL variables in VS. - output
const EPluginLibraryArgType 	k3DPointArgType			= 12;		// use pt3Value in SDK.  Use 3 REAL variables in VS.
const EPluginLibraryArgType 	k3DPointVarArgType		= 13;		// use pt3Value in SDK.  Use 3 REAL variables in VS. - output
const EPluginLibraryArgType 	kVectorArgType			= 14;		// use vec.vecValue
const EPluginLibraryArgType 	kVectorVarArgType		= 15;		// use vec.vecValue - output
const EPluginLibraryArgType 	kBooleanArgType			= 16;		// use boolValue
const EPluginLibraryArgType 	kBooleanVarArgType		= 17;		// use boolValue - output
const EPluginLibraryArgType 	kStringArgType			= 18;		// use strValue (UTF16)
const EPluginLibraryArgType 	kStringVarArgType		= 19;		// use strValue (UTF16) - output
const EPluginLibraryArgType 	kCharArgType			= 20;		// use charValue (UTF16)
const EPluginLibraryArgType 	kCharVarArgType			= 21;		// use charValue (UTF16) - output
const EPluginLibraryArgType 	kCharDynarrayArgType	= 22;		// use strValue (UTF16)
const EPluginLibraryArgType 	kCharDynarrayVarArgType	= 23;		// use strValue (UTF16) - output
const EPluginLibraryArgType 	kCharArrayVarArgType	= 24;		// use strValue (UTF16) - output
const EPluginLibraryArgType 	kHandleArgType			= 25;		// use handleValue
const EPluginLibraryArgType 	kHandleVarArgType		= 26;		// use handleValue - output
const EPluginLibraryArgType 	kColorArgType			= 27;		// use intValue
const EPluginLibraryArgType 	kColorVarArgType		= 28;		// use intValue - output
const EPluginLibraryArgType 	kStyleArgType			= 29;		// use styleValue

const EPluginLibraryArgType		kPointRecArgType		= 30;		// use ptValue in SDK.  Use new "POINT" data structure in VS.  New for VW 10.
const EPluginLibraryArgType		kPointRecVarArgType		= 31;		// use ptValue in SDK.  Use new "POINT" data structure in VS. New for VW 10. - output
const EPluginLibraryArgType		kPoint3DRecArgType		= 32;		// use pt3Value in SDK. Use new "POINT3D" data structure in VS. New for VW 10.
const EPluginLibraryArgType		kPoint3DRecVarArgType	= 33;		// use pt3Value in SDK. Use new "POINT3D" data structure in VS. New for VW 10.  - output
const EPluginLibraryArgType		kRGBColorRecArgType		= 34;		// use colorVar in SDK. Use new "RGBCOLOR" data structure in VS. New for VW 10.
const EPluginLibraryArgType		kRGBColorRecVarArgType	= 35;		// use colorVar in SDK. Use new "RGBCOLOR" data structure in VS. New for VW 10. - output
const EPluginLibraryArgType		kVoidPtr				= 36;					// 
const EPluginLibraryArgType		kProcedureArgType		= 36;		// use voidData for ProcedureRef
const EPluginLibraryArgType		kFunctionkArgType		= 37;		// use voidData for FunctionRef
const EPluginLibraryArgType 	kPointerArgType			= 38;		// use ptrValue.  New for x64 since kVoidPtr seemed muddled and had no var type.
const EPluginLibraryArgType 	kPointerVarArgType		= 39;		// use ptrValue.  New for x64 since kVoidPtr seemed muddled and had no var type.

const EPluginLibraryArgType		kIntegerInOutArgType		= 40;	// use intValue - input/output
const EPluginLibraryArgType		kLongInOutArgType			= 41;	// use longValue - input/output
const EPluginLibraryArgType		kBooleanInOutArgType		= 42;	// use boolValue - input/output
const EPluginLibraryArgType		kRealInOutArgType			= 43;	// use realValue - input/output
const EPluginLibraryArgType		kHandleInOutArgType			= 44;	// use handleValue - input/output
const EPluginLibraryArgType		kStringInOutArgType			= 45;	// use strValue (UTF16) - input/output
const EPluginLibraryArgType		kCharDynarrayInOutArgType	= 46;	// use strValue (UTF16) - input/output
const EPluginLibraryArgType		kGlobalPointInOutArgType	= 47;	// use ptValue in SDK.  Use 2 REAL variables in VS. - input/output
const EPluginLibraryArgType		kVectorInOutArgType			= 48;	// use vec.vecValue - input/output

const EPluginLibraryArgType 	kDynarrayArgType		= 49;	// use arrayVar - input

struct PluginLibraryArg {
	EPluginLibraryArgType argType;			// type of this argument
	
	union {
		double_gs				realValue;	// for kRealArgType, kRealVarArgType, kAngleArgType, kDistanceArgType
		Boolean 				boolValue;	// for kBooleanArgType, kBooleanVarArgType
		UCChar					charValue;	// for kCharArgType, kCharVarArgType (UTF16)
		short					intValue;	// for kIntegerArgType, kIntegerArgVarType, kColorArgType
		Sint32					longValue;	// for kLongArgType, kLongVarArgType
		GSHandle 				handleValue;// for kHandleArgType, kHandleVarArgType //-V117
		_WorldPt				ptValue;	// for kPointArgType, kGlobalPointArgType, kGlobalPointVarArgType
		_WorldPt3				pt3Value;	// for k3DPointArgType, k3DPointVarArgType
		_WorldPt3				vecValue;	// for kVectorArgType, kVectorVarArgType
		unsigned char			styleValue;	// for kStyleArgType
		void*					voidData;	// for kVoidPtr //-V117
		void*					ptrValue;	// for kPointerArgType,kPointerVarArgType //-V117

		struct {							// for kColorVarArgType
			Sint32				redValue;
			Sint32				greenValue;
			Sint32				blueValue;
		} colorVar;

		struct {							// for kDynarrayArgType
			EPluginLibraryArgType	valueType;
			Sint32					cntRows;
			Sint32					cntCols;
			void*					buffer;
			size_t					bufferSize;
		} arrayVar;
	};

	// for kStringArgType, kStringVarArgType
	// for kCharDynarrayArgType, kCharArrayVarArgType
	// for kCharDynarrayVarArgType
	TXString		strValue;

	void SetStr(const TXString& input) { strValue = input; }
};

const short kMaxPluginLibraryArgs = 11;
struct PluginLibraryArgTable {
	PluginLibraryArg args[kMaxPluginLibraryArgs];
	PluginLibraryArg functionResult;
};
	
// SDK Plug-in Library Routine constants for "Scope" field of VLIB resource.
const Uint8 kVLIBScopeUniversal				= 0;		// Call from anywhere: VS, SDK, VW.
const Uint8 kVLIBScopeVSOnly 				= 1;		// Only VS can call this library routine.
const Uint8 kVLIBScopeSDKOnly				= 2;		// Only SDK Plug-ins can call this library routine.
const Uint8 kVLIBScopeNemetschekOnly		= 255; 		// prevents calling from VectorScript and SDK.  Only from within VectorWorks application.


//////////////////////////////////////////////////////////////////////////////////////////
// Units

const short unitsTooPrecise	= 1;
const short unitsNotPreciseEnough = 2;

struct UnitFlagsType {
	unsigned short				showUnits:1;			// Should the unit mark be displayed with numbers
	unsigned short				leading0:1;				// Leading 0's
	unsigned short				trailing0:1;			// Trailing 0's
	unsigned short				useMinUnit:1;			// Round dimensions to displayAccuracy
	unsigned short				customUnit:1;			// Was this specified as a custom unit
	unsigned short				showDecAsFractions:1;	// Show base-10 accuracies as fractions
	unsigned short				f6:1;
	unsigned short				f7:1;
	unsigned short				f8:1;
	unsigned short				f9:1;
	unsigned short				f10:1;
	unsigned short				f11:1;
	unsigned short				f12:1;
	unsigned short				f13:1;
	unsigned short				f14:1;
	unsigned short				f15:1;
};

const short 	ufDecimal			= 0;	// anything but feet and inches
//const short	ufFractional		= 1;	obsolete
const short		ufFeetAndInches		= 2;
//const short	ufFracFeetAndInches	= 3;	obsolete
const short 	ufDegrees			= 3;
struct UnitsType {
	WorldCoord					storedAccuracy;		// Coords/unit
	short						format;				// Display format
	double_gs					unitsPerInch;		// units/inch
	TXString					unitMark;			// Unit string at end of each dimension
	Sint32						displayAccuracy;	// Largest denominator displayed
	UnitFlagsType				unitFlags;			// Various flags
};


//////////////////////////////////////////////////////////////////////////////////////////
// Mesh Errors

#ifndef _MINICAD_
enum {
	kMeshNoError = 0,
	kMeshMemoryError = -1,
	kMeshSizeLimitError = -2,
	kMeshOtherError = -3
};
typedef short MeshErrorType;
#else
enum MeshErrorType {
	kMeshNoError = 0,
	kMeshMemoryError = -1,
	kMeshSizeLimitError = -2,
	kMeshOtherError = -3
};

#endif


//////////////////////////////////////////////////////////////////////////////////////////
// Dash Styles

const short kMaxDashPats		= 32767;	// Maximum number of dash patterns (was 16 until 7.0) (was 128 until 2013)
const short kMaxDashSegs		= 10;	// Maximum # of segments per pattern

struct DashPatType {
	Boolean		scaleThick;
	Sint8 		numSegs;
	double_gs	cumLengths[kMaxDashSegs];
};

struct DashPatDef {
	Boolean		scaleThick;
	Sint8 		numSegs;
	double_gs	segs[kMaxDashSegs];  //These are the lengths and gaps, not the cumulative lengths
};
//////////////////////////////////////////////////////////////////////////////////////////
// Symbol Tool
//
// If additional modes or alingment types are added, update the corresponding Count constant
//
typedef short SymbolToolModeType;
const SymbolToolModeType	kSymbolToolRegularInsert	= 1;
const SymbolToolModeType	kSymbolToolOffsetInsert		= 2;
const SymbolToolModeType	kSymbolToolPickup			= 3;

const SymbolToolModeType	kSymbolToolModeFirst	= kSymbolToolRegularInsert;
const SymbolToolModeType	kSymbolToolModeCount	= kSymbolToolPickup;

typedef short SymbolToolAlignType;
const SymbolToolAlignType	kSymbolToolAlignLeft	= 1;
const SymbolToolAlignType	kSymbolToolAlignCenter	= 2;
const SymbolToolAlignType	kSymbolToolAlignRight	= 3;
const SymbolToolAlignType	kSymbolToolAlignNatural	= 4;

const SymbolToolAlignType kSymbolToolAlignFirst	= kSymbolToolAlignLeft;
const SymbolToolAlignType kSymbolToolAlignCount	= kSymbolToolAlignNatural;


typedef short EPluginStyleParameter ;
const EPluginStyleParameter	kPluginStyleParameter_ByInstance = 0;
const EPluginStyleParameter	kPluginStyleParameter_ByStyle    = 1;
const EPluginStyleParameter kPluginStyleParameter_AllwaysByInstance = 2;
const EPluginStyleParameter kPluginStyleParameter_ByCatalog = 3;

typedef short EPluginStyleGroup;
const EPluginStyleGroup kPluginStyleGroup_ByInstance	= 0;
const EPluginStyleGroup kPluginStyleGroup_ByStyle		= 1;
const EPluginStyleGroup kPluginStyleGroup_Mixed			= 2;

typedef size_t EPluginStyleMapPosition;
const EPluginStyleMapPosition kPluginStyleMapPosition_ParameterName = 0;
const EPluginStyleMapPosition kPluginStyleMapPosition_StyleType		= 1;

typedef short EPluginStyleEditList;
const EPluginStyleEditList kPluginStyleEditList_Unused = 0;
const EPluginStyleEditList kPluginStyleEditList_AddToEdit = 1;
const EPluginStyleEditList kPluginStyleEditList_RemoveFromEdit = 2;
const EPluginStyleEditList kPluginSytleEditList_NewDisplayName = 3;

typedef size_t EPluginStyleEditListPosition;
const EPluginStyleEditListPosition kPluginStyleMapEditListPosition_ParameterName = 0;
const EPluginStyleEditListPosition kPluginStyleMapEditListPosition_EditListType  = 1;
const EPluginStyleEditListPosition kPluginStyleMapEditListPosition_DisplayName	 = 2;

typedef size_t EPluginStyleAttachedCatalogPosition;
const EPluginStyleAttachedCatalogPosition kPluginStyleAttachedCatalogPosition_CatalogName = 0;

typedef size_t EPluginCatalogListPosition;
const EPluginCatalogListPosition kPluginCatalogListPosition_ParameterName = 0;



//////////////////////////////////////////////////////////////////////////////////////////
// Walls

const short kFullBreak			= 1;		// standard symbol break
const short kSymbolBreak		= kFullBreak;
const short kHalfBreak			= 2;
const short kPeakBreak			= 3;
const short kCapBreak			= 4;

//---------------------------------
typedef short InsertModeType;

// The InsertModeType specifies where the symbol is inserted. It is used for in both the 
// SymbolBreakType structure and the Get/Set object variable functions for Symbol definitions.

const InsertModeType kSymInsertOnCenter		= 0;			// insert at the center of the wall
const InsertModeType kSymInsertOnEdge		= 1; 			// Symbol Defs do not distinguish between left and right.

const InsertModeType kSymInsertOnLeftEdge	= 1; 			// insert on the edge of the wall
const InsertModeType kSymInsertOnRightEdge	= 2; 			// 


//---------------------------------
typedef short BreakModeType;

// The BreakModeType specifies the kind of break the symbol creates. It is used for in both the 
// SymbolBreakType structure and the Get/Set object variable functions for Symbol definitions.

const BreakModeType kSymFullBreakWithCaps 	= 1;			// lines are drawn over the ends of the wall where broken
const BreakModeType kSymFullBreakNoCaps		= 2;			// no lines to cap the symbol break
const BreakModeType kSymHalfBreak			= 3; 			// for edge insertion only - only one line is broken for the symbol
const BreakModeType kSymNoBreak				= 4;			// wall does not break for the inserted symbol


struct SymbolBreakType {
	MCObjectHandle		theSymbol;		/* Handle to the symbol inserted */
	Boolean				rightSide;		/* Is the symbol oriented to the right side of the wall */
	Boolean				flipH;			/* Is the symbol flipped toward the first point of the wall */
	WorldCoord			height;			/* Height of the bottom of the symbol from the ground plane */
//	Boolean				capBreakEnds - removed: this functionality has been repleaced by the breakMode field
										
	InsertModeType		insertMode; 	// which edge is the symbol inserted on
	BreakModeType		breakMode;		// break style for the symbol
	Boolean				cornerBreak;	// the symbol will move to the corner
	Boolean				spanBreak;		// the symbol will move to the center of the wall. The symbol itself is responsible for settings the parameters to span the wall
										// span and corner are mutually exclusive.
	
	SymbolBreakType(): 					/* constructor sets options for standard center insertion */
		theSymbol(NULL), rightSide(false), flipH(false), height(0),  
		insertMode(kSymInsertOnCenter), breakMode(kSymFullBreakWithCaps),
		cornerBreak(false), spanBreak(false) {}
};

struct HalfBreakType {
	Boolean			rightSide;		/* Is the break on the right side of the wall */
	WorldCoord		gapWidth;		/* GSSize of gap opening */
	MCObjectHandle	polyBreakObject;/* optional break geometry*/
	
	HalfBreakType(): polyBreakObject(NULL) {}
};

struct CapBreakType {
	WorldCoord		rightOff;		/* Distance that the right cap end is from the normal end */
	WorldCoord		leftOff;		/* Distance that the left cap end is from the normal end */
	Boolean			closed;			/* Is the end of the wall closed */
	Boolean			round;			/* Is the cap rounded or flat */
	MCObjectHandle	polyBreakObject;/* optional break geometry */
	
	CapBreakType(): polyBreakObject(NULL) {}
};

struct PeakBreakType {
	WorldCoord		peakHeight;		/* Height of the peak from the ground plane */
	Boolean		topPeak;		/* Is the peak on the top face of the wall */
};

// The wall cap attributes type
enum EWallCapAttributesType
{
	eWallCapAttributesType_wallLine,
	eWallCapAttributesType_componentLines
};

// The wall texture part assigned to the faces created in a wall by a cutting object in the 3D Wall Hole group of a symbol or plug-in object
enum EWallHoleTexturePart
{
	eWallHoleTexturePart_holes,
	eWallHoleTexturePart_left,
	eWallHoleTexturePart_right
};

// The type of a Wall Feature
enum EWallFeatureType
{
	eWallFeatureType_projection,
	eWallFeatureType_recess
};

// The wall bound
enum EWallBound
{
	eWallBound_innerFace,
	eWallBound_outerFaceOfInnerComponent,
	eWallBound_innerFaceOfCore,
	eWallBound_centerOfCore,
	eWallBound_outerFaceOfCore,
	eWallBound_innerFaceOfOuterComponent,
	eWallBound_outerFace
};
// The roof wall associated bound

enum ERoofWallAssociatedBound
{
	eRoofWallAssociatedBound_innerFace,
	eRoofWallAssociatedBound_outerFaceOfInnerComponent,
	eRoofWallAssociatedBound_innerFaceOfCore,
	eRoofWallAssociatedBound_centerOfCore,
	eRoofWallAssociatedBound_outerFaceOfCore,
	eRoofWallAssociatedBound_innerFaceOfOuterComponent,
	eRoofWallAssociatedBound_outerFace,
	eRoofWallAssociatedBound_roofEdge,
	eRoofWallAssociatedBound_roofAxisLine
};

// The roof change point
enum ERoofChangePoint
{
	eRoofChangePoint_innerFace,
	eRoofChangePoint_outerFaceOfInnerComponent,
	eRoofChangePoint_innerFaceOfCore,
	eRoofChangePoint_centerOfCore,
	eRoofChangePoint_outerFaceOfCore,
	eRoofChangePoint_innerFaceOfOuterComponent,
	eRoofChangePoint_outerFace,
	eRoofChangePoint_none
};

// The roof modification
enum ERoofModification
{
	eRoofModification_none,
	eRoofModification_clipWalls,
	eRoofModification_clippedByWalls
};

// The roof manual bound
enum ERoofManualBound
{
	eRoofManualBound_roofEdge,
	eRoofManualBound_roofAxisLine
};
// The component function
enum EComponentFunction
{
	eComponentFunction_Other,
	eComponentFunction_LoadBearing,
	eComponentFunction_Insulation,
	eComponentFunction_InnerFinish,
	eComponentFunction_OuterFinish,
	eComponentFunction_AirGap
};

// The texture set
enum ETextureSet
{
	eTextureSet_objectTextures,
	eTextureSet_componentTextures
};

//////////////////////////////////////////////////////////////////////////////////////////
// NurbsCurve plannar info for extrude along path plug in  -- Charlene Mao
struct CurveInfo{
	MCObjectHandle inHandle;
	double         tol;       
};

struct ConvertToNurbs{
	MCObjectHandle inHandle;
	MCObjectHandle outHandle;
};

struct CurvePlanarInfo{
    bool           isPlanar;        
};

struct ExtrudeAlongPathInfo{
	MCObjectHandle pathHandle;
	MCObjectHandle profileHandle;
	MCObjectHandle outHandle;
	bool bExponential;
	double scale;
	bool bLockDirection;
	bool bFixProfile;
};

struct CreateClosedShapeForNurbsInfo{
	MCObjectHandle sourceHandle;
	MCObjectHandle offsetHandle;
	MCObjectHandle composeHandle;
};

struct CreateLinkedViewportInfo{
	MCObjectHandle linkedMarkerHandle;
	MCObjectHandle unSectionedViewportHandle;
};

struct UpdateLinkedMarkerDefInfo{
	MCObjectHandle linkedMarkerHandle;
};

struct TextAlongPathInfo{
	MCObjectHandle pathHandle;
	MCObjectHandle textHandle;
	MCObjectHandle outHandle;
	short iHowToPlaceText;
	short iTextType;
	double height;
	bool   bAbove;
	double rotateAngle;
	bool   bDoPolyline;
};

struct HelicalAlongCurveInfo{
	MCObjectHandle pathHandle;
	MCObjectHandle outHandle;
	double	radius1;
	double	radius2;
    double	startAng;
	double*	pitch;
	double*	numTurns;
	bool	bPitch;
	bool	bReverseTwist;
	bool	bFlat;
};


struct IsNurbsCurveG1Cont{
	MCObjectHandle inHandle;
	bool           isG1Continuous;
};


struct CreateRoofLayerInfo {
	MCObjectHandle	outSelectLayerhandle;
	Sint32			outError;
};

struct TransferViewportAttributes {
	MCObjectHandle	sourceHandle;
	MCObjectHandle	targetHandle;
	bool			copySource;
	bool			differentDocument;
	bool			transferClassVis;
	bool			transferLayerVis;
	bool			transferClassOverride;
	bool			transferLayerOverride;
	bool            transferDataVisualization;
	bool			transferRenderProperties;
    bool            transferImageEffects;
	bool			transferOtherProperties;
	bool			deleteTemporaryData;
	bool			classDoesNotExist;
	bool			layerDoesNotExist;
	bool			resourceDoesNotExist;
	bool			usingDocClassVisibility;

	TransferViewportAttributes() {
		sourceHandle = NULL;
		targetHandle = NULL;
	}
};

//------------------------------------------------------------------------------
// Object used for Kludge(6035) regarding ImageEffects eyedropper support
// 
// For querying if 'sourceHandle' has image effects inside,
//  set 'sourceHandle' and 'checkImageEffects = true'
//
// For transferring image effects from 'sourceHandle' to 'targetHandle'
//  set both handle accordingly along with transfer flags from user settings
//------------------------------------------------------------------------------
struct TransferImageEffects {

    MCObjectHandle sourceHandle;
    MCObjectHandle targetHandle;

    bool checkImageEffects;
    bool sourceHasEffects;
    bool transferImageEffects;
    bool transferViewportImageEffects;

    TransferImageEffects() = default;
};

struct MoveAllObjectsByLayerHeightInfo{
	MoveAllObjectsByLayerHeightInfo()
	{
		addUndoMovePrimitive = false;
		addHeight = true;
		adjustLinkedWallHeight = true;
		doNotMoveBoundedObjects = false;
		bDoNotMovePlanarObjects = true;
		bDoNotMoveLayerPlanarObjects = true;
		bMoveGuestLayerObjects = false;
	}

	bool	addUndoMovePrimitive;
	bool	addHeight;
	bool	adjustLinkedWallHeight;
	bool	doNotMoveBoundedObjects;
	bool	bDoNotMovePlanarObjects;
	bool	bDoNotMoveLayerPlanarObjects;
	bool	bMoveGuestLayerObjects;
};
//////////////////////////////////////////////////////////////////////////////////////////
// Textures

struct TransferTexture {
	MCObjectHandle	objHandle;
	bool			useResolveMaterials;
	bool			dropTexture;
};

#ifndef _MINICAD_
const short kPrimary			= 0; // All parts (for single-textured objects), or wall right, or roof top - OLD, see TexturePartSDK below for 2009 texture parts.  -DLD 6/17/2008
const short kSecondary			= 1; // Wall left, or roof dormer - OLD, see TexturePartSDK below for 2009 texture parts.  -DLD 6/17/2008
const short kTertiary			= 2; // Wall center - OLD, see TexturePartSDK below for 2009 texture parts.  -DLD 6/17/2008
const Boolean kResolveByClass	= true; 
const Boolean kNoResolveByClass	= false; 
#endif	// !_MINICAD_


//////////////////////////////////////////////////////////////////////////////////////////
// ObjectVariable Types

// The TVariableBlock structure holds a value of some type
//	unspecified at compile time.  It is used to pass values
//	to functions such as GetObjectVariable and SetObjectVariable
//	that access and set functions of various types using a
//	selector-value pattern.

enum { 
	t_Boolean = 0, 
	t_Sint16 = 1, 
	t_WorldPt = 2,
	t_Real64 = 3, 
	t_TransformMatrix = 4, 
	t_WorldRect = 5,
	t_WorldPt3 = 6,
	t_Sint32 = 7, 
	t_Str255 = 8, 
	t_str256 = 9,      // this was never used and improperly implemented -- Removed 9/1/98 - PCP
	t_ViewRect = 10,
	t_Sint8 = 11, 
	t_Uint8 = 12, 
	t_FracPt = 13,		// XXX_JDW_FLOATINGPOINT
	t_Fract = 14,		//
	t_XCoordPt3 = 15,
	t_XCoordPt = 16,
	t_Uint32 = 17,
	t_MCObjectHandle = 18,
    t_TXString = 19
};
typedef Sint32  EVariableBlockType;



#define DEFINE_TYPE(Type) 								\
TVariableBlock(const Type &value)						\
	{ *this = value; }									\
Boolean Get##Type(Type & data) const					\
{ if (eType == t_##Type) {								\
    data = fData.u##Type ;								\
    return true ;										\
  } 													\
  else return false ;									\
}														\
TVariableBlock &	operator=(const Type & data)		\
{   fData.u##Type = data ;								\
	eType = t_##Type ;									\
	return *this ;										\
}

//----------------------------------------------------------------------------------------



class TVariableBlock {

	public:
		TVariableBlock()								{ *this = 0; }
	
		// Core types
		///////////////////////////////////////////

		DEFINE_TYPE(Boolean)
		DEFINE_TYPE(Sint16)
		DEFINE_TYPE(WorldPt)
		DEFINE_TYPE(Real64)
		DEFINE_TYPE(TransformMatrix)
		DEFINE_TYPE(WorldRect)
		DEFINE_TYPE(WorldPt3)
		DEFINE_TYPE(Sint32)
		DEFINE_TYPE(ViewRect)
		DEFINE_TYPE(Sint8)
		DEFINE_TYPE(Uint32)
		DEFINE_TYPE(MCObjectHandle)


		// To resolve type conflicts
		////////////////////////////////////////////
		// We cannot rely on the compiler to assign these types because they
		// are identical to core types.

		Boolean GetUint8(Uint8 &value) const
		{ 
			if (eType == t_Uint8) {
				value = fData.uUint8;
				return true ;
			} 
			else return false ;
		}
	
		void SetUint8(Uint8 value)
		{ 
			eType = t_Uint8;
			fData.uUint8 = value;
		}

		Boolean GetBoolean(bool& value) const
		{
			if (eType == t_Boolean)
			{
				value = fData.uBoolean ? true : false ;
				return true ;
			}
			else return false ;
		}
	

		// string types
		///////////////////////////////////////////

        TVariableBlock(const TXString& value)		{ *this = value; }
		Boolean	GetTXString(TXString& data) const;
		TVariableBlock& operator=(const TXString& data);


	private:
		union {
			Boolean			uBoolean ;				// Mac Specific
			Sint16			uSint16 ;
			_WorldPt		uWorldPt;
			Real64			uReal64 ;
			_TransformMatrix uTransformMatrix ;
			_WorldRect		uWorldRect ;
			_WorldPt3		uWorldPt3 ;
			Sint32			uSint32 ;
//			ViewRect		uRect ;					// Mac Specific
			ViewRect_		uViewRect ;	
			Sint8			uSint8 ;
			Uint8			uUint8 ;
			_WorldPt		uFracPt ;				// XXX_JDW_FLOATINGPOINT
			_WorldPt3		uXCoordPt3 ;
			_WorldPt		uXCoordPt;
			Uint32			uUint32;
			MCObjectHandle	uMCObjectHandle; //-V117


			TXChar          uStr[256] ;
		} fData ;
		
		EVariableBlockType	eType ;

#undef DEFINE_TYPE
};





//////////////////////////////////////////////////////////////////////////////////////////
// SetObjectVariable and GetObjectVariable selectors
//
//		These selectors let you get properties
//		specific objects.  They have the return/passed
//		type as a comment following the selector

typedef enum { kAlign = 0, kHorOnly = 1, kHorVert = 2 } EDimTextRotateType ; 

// Dimension Selectors
// -------------------
const short ovDimStandard			=  0 ;	// char - Public for VS
		// The dimension standard index. A value greater than zero indicates a builtin standard (from
		// the resources). A value less than zero indicates a custom standard (user-defined). For 
		// SetObjectVariable, the result for an invalid value (zero, greater the the number of 
		// builtin standards, less than the number of custom standards) is undefined.

const short ovDimTextRotate_OBSOLETE = 1;	// don't reuse this index - Not for public use

#if GS_SDK_VW10_COMPATIBLE
		// Use the new ovDimTextRotation instead of ovDimTextRotate.
		// The new one uses shorts; ovDimTextRotate uses Sint32 to get and char to set.
		// This is being left in for compatibility with existing SDK plugins. - JDW [2003-1-9]
const short ovDimTextRotate			=  ovDimTextRotate_OBSOLETE ; // Not for public use
#endif // GS_SDK_VW10_COMPATIBLE


const short ovDimTextAboveLine		=  2 ;	// double - Not for public use
		// The distance of the text from the dimension line.

const short ovDimArrowInside		=  3 ;	// Boolean - Public for VS
		// The dimension arrow inside flag.

const short ovDimLeaderToLeft		=  4 ;	// double - Public for VS
		// The distance of the text from the startpoint (<0) or the endpoint (>0).

const short ovDimBoxText			=  5 ;	// Boolean - Public for VS
		// The box text flag for the primary unit.

const short ovDimShowValue			=  6 ;	// Boolean - Public for VS
		// The show value flag for the primary unit.

const short ovDimStartingWitness	=  7 ;	// Boolean - Public for VS
		// The starting witness flag.

const short ovDimEndingWitness		=  8 ;	// Boolean - Public for VS
		// The ending witness flag.

const short ovDimLeaderText			=  9 ;	// TXString - Public for VS
		// The leader text for the primary unit (31 chars max).

const short ovDimTrailerText		= 10 ;	// TXString - Public for VS
		// The trailer text for the primary unit (31 chars max).

const short ovDimTolerance			= 11 ;	// char - Public for VS
		// The tolerance type. Valid values are:
		//   - 0 (kNoTol):	  None
		//   - 1 (kOneTol):   Single
		//   - 2 (kTwoTol):   Double
		//   - 3 (kLimitTol): Limit

const short ovDimDirection			= 12 ;	// FracPt; Vector2 in VW9 - Not for public use
		//  Direction (for dimensions with fixed angles).

const short ovDimStartPt			= 13 ;	// WorldPt - Not for public use
		// The dimension starting point.

const short ovDimEndPt				= 14 ;	// WorldPt - Not for public use
		// The dimension ending point.

const short ovDimStartOffset		= 15 ;	// double - Public for VS
		// The distance of the dimension from the starting point.

const short ovDimBox				= 16 ;	// WorldRect - Not for public use
		// The box of the oval that is being dimensioned (angular, diametral).

const short ovDimFontSize			= 17 ;	// double - Public for VS
		// The dimension text font size.
const short ovObjectFontSize		= ovDimFontSize ;	// double - Not for public use
		// Now ParametricTypes have the same Font API as DimHeaderTypes

const short ovDimFontType_OBSOLETE	= 18 ;	// don't reuse this index - Not for public use
		// You should use ovDimFontIndex instead.

const short ovDimFontStyle			= 19 ;	// char - Public for VS
		// The dimension font style. Values may be summed and set simultaneously. 
		// For example, a value of 5 makes the text underlined and bold.
		// Valid values are:
		//   -  0  Clear
		//   -  1  Bold
		//   -  2  Italic
		//   -  4  Underline
		//   -  8  Outline (Mac only)
		//	 - 16  Shadow  (Mac only)
const short ovObjectFontStyle			= ovDimFontStyle ;	// char - Not for public use


const short ovDimPrec               = 20 ;  // Sint32 - Public for VS     
		// The dimension precision for the primary unit. For decimal precision,
		// the value represents how many digits are displayed to the right of the decimal
		// point (0 thru 10). For fractional precision the value represents a power of 2
		// for the fractional denominator (0 for 1/1 [no fractions], 1 for 1/2, 2 for 1/4,
		// 3 for 1/8, 4 for 1/16, 5 for 1/32, or 6 for 1/64.
		// For angular precision, the value must be 1 (only whole numbers), 2 (degrees mins), 
		// 3 (degrees mins secs), 5 (x.x angular units), 6 (x.xx angular units), 
		// 7 (x.xxx angular units), 8 (x.xxxx angular units), 9 (x.xxxxx angular units),
		// 10 (x.xxxxxx angular units), 11 (x.xxxxxxx angular units) or 12 
		// (x.xxxxxxxx angular units). 
		// (For angular precision a value of 4 is invalid.)

const short ovDimPrec2              = 21 ;  // Sint32 - Public for VS
		// The dimension precision for the secondary unit. For decimal precision,
		// the value represents how many digits are displayed to the right of the decimal
		// point (0 thru 10). For fractional precision the value represents a power of 2
		// for the fractional denominator (0 for 1/1 [no fractions], 1 for 1/2, 2 for 1/4,
		// 3 for 1/8, 4 for 1/16, 5 for 1/32, or 6 for 1/64.
		// For angular precision, the value is not used.


const short ovDimBoxText2			= 22 ;	// Boolean - Public for VS 
		// The box text flag for the secondary unit.

const short ovDimShowValue2			= 23 ;	// Boolean - Public for VS	  
		// The show value flag for the secondary unit.

const short ovDimLeaderText2		= 24 ;	// TXString - Public for VS
		// The leader text for the secondary unit (31 chars max).

const short ovDimTrailerText2		= 25 ;	// TXString - Public for VS  
		// The trailer text for the secondary unit (31 chars max).



const short ovDimClass				= 26 ;	// unsigned char - Public for VS	  
		//	(fix_ang)		= 0,
		//	(sloped)		= 1,
		//	(ordinate)		= 2,
		//	(radial)		= 3,
		//	(diametrical)	= 4,
		//	(ang)			= 5;

const short ovDimStandardName		= 27 ;	// TXString - Public for VS
		// The dimension standard name.

const short ovDimFontIndex			= 28 ;	// short - Public for VS
		// The font index of the dimension's font.
const short ovObjectFontIndex		= ovDimFontIndex ;	// short
		// Now ParametricTypes have the same Font API as DimHeaderTypes

const short ovDimTextPosCalculated  = 29 ;	// Boolean - Public for VS
		// The dimension text automatically calculated flag.

const short ovDimTextPosInside  = 30 ;	// Boolean - Public for VS
		// The dimension text position inside flag.

const short ovDimReferenceAngle  = 31 ;	// Boolean - Public for VS
		// The angular dimension is a reference angle.

const short ovDimShowPrimaryDual		= 32; // Boolean - Public for VS
		// display only the primary  part of a dual dimension if true

const short ovDimShowSecondaryDual		= 33; // Boolean - Public for VS
		// display only the secondary  part of a dual dimension if true

const short ovDimTopToleranceValue		= 34; // WorldCoord - Public for VS
		// the top tolerance value

const short ovDimBottomToleranceValue	= 35; // WorldCoord - Public for VS
		// the bottom tolerance value

const short ovDimTopToleranceString		= 36;	// TXString - Public for VS
		// the top tolerance string

const short ovDimBottomToleranceString	= 37;	// TXString - Public for VS
		// the bottom tolerance string

const short ovDimUseToleranceStrings	= 38;	// Boolean - Public for VS
		// if true, use the strings instead of the values for tolerances - primary units only
		
const short ovDimFlippedText			= 39;	// Boolean - Public for VS
		// whether or not to flip the text to the other side of the dimension line for some dimensions
		
const short ovDimTextSizeInPoints		= 40;	// double - Public for VS
		// The dimension text font size in points.
		// XXX_JDW_MISC - Mark: should this be ovObjectTextSizeInPoints ? (see ovObjectFontSize)
		// [MAF VW10 Revisit, 1/9/03]

const short ovDimTextRotation			= 41;	// short - Public for VS
		// The text rotation type. Valid values are from EDimTextRotateType:
		//   - 0 (kAlign):   Aligned 	
		//   - 1 (kHorOnly): Horizontal Only
		//   - 2 (kHorVert): Horizontal/Vertical

const short ovDim2ReferenceLinesAngle	= 42;	// Boolean - Not for public use
		// The angular dimension has two reference lines.	
	
const short ovDimTextAboveLineInCurrUnits	=  43;	// double - Public for VS
		// The distance of the text from the dimension line in current units.

const short ovDimTextOffsetInCurrUnits		=  44;	// double - Public for VS
		// If the text is inside the witness lines, the ratio of the distance between the startpoint
		// and the text to the distance between the startpoint and the endpoint.  If the text is 
		// outside the witness lines, the distance in current units of the text from the nearer of the 
		// startpoint (<0) or the endpoint (>0).

const short ovDimStartOffsetInCurrUnits		= 45 ;	// double - Public for VS
		// The distance of the dimension from the starting point in current units.
	
const short ovDimShowElevText 				= 46;   // Boolean - Public for VS
		// Display the optional elevation dimension used in the SIA dimensioning standard
		
const short ovDimElevTextValue				= 47;   // WorldCoord - Public for VS
		// The value to be displayed as the optional SIA elevation dimension

const short ovDimElevTextLeader				= 48;   // TXString - Public for VS
		// The leader text for the optional SIA elevation dimension
		
const short ovDimElevTextTrailer			= 49;   // TXString - Public for VS
		// The trailer text for the optional SIA elevation dimension   

const short ovDimNoteText					= 1233;	// TXString - Public for VS
		// The note text (text under dimension line or value)

const short ovDimWitnessPerpChord			= 1250;   // Boolean - Public for VS, read only
		// The WitnessPerpChord flag for Arc Length dimensions

const short ovDimArcIndicator				= 1251;   // Boolean - Public for VS, read only
		// The Arc Indicator flag for Arc Length dimensions

const short ovDimClockwiseArc				= 1252;   // Boolean - Public for VS, read only
		// The Clockwise Arc flag for Arc Length dimensions  

const short ovDimTranslateInVP				= 1234; // MCObjectHandle - Not for public use
		// Used to move a dimension that is created in a viewport annotation by the exterior wall dimensioner only.
		// This object variable should not be published and is for internal use only.

const short ovDimWitnessOverride			= 1235; // short - Public for VS
		// The witness override settings.  Valid values are from EWitnessSetting:
		// - 0: standard witness line settings, this will use whatever is in the dimension standard of the dimension
		// - 1: single custom witness line length, this will use a single custom length for both witness lines
		// - 2: multiple custom witness line lengths, this will use a different custom length for each witness line
		// - 3: single custom witness offset, this will use a single custom offset for both witness lines
		// - 4: multiple custom witness offsets, this will use a different custom offset for each witness line

const short ovDimCustStartWitLength			= 1236; // double - Public for VS
		// The custom length for both witness lines if a single custom length is being used, the custom length for the starting
		// witness line if multiple custom lengths are being used.

const short ovDimCustEndWitLength			= 1237; // double - Public for VS
		// The custom length for the ending witness line if multiple custom lengths are being used.

const short ovDimCustStartWitOffset			= 1238; // double - Public for VS
		// The custom offset for both witness lines if a single custom offset is being used, the custom offset for the starting
		// witness line if multiple custom offsets are being used.

const short ovDimCustEndWitOffset			= 1239; // double - Public for VS
		// The custom offset for the ending witness line if multiple custom offsets are being used.

const short ovDimLeaderLine					= 1240; // Boolean - Public for VS
		// The leader line visibility flag for linear and arc length dimensions

const short ovDimLeaderLineArrowType		= 1241; // UInt8 - Public for VS
		// The type of marker for the leader line

const short ovDimLeaderLineArrowSize		= 1242; // Sint16 - Public for VS
		// the size of the marker for the leader line

const short ovDimLeaderLineArrowAngle		= 1243; // UInt8 - Public for VS
		// the angle of the marker for the leader line

const short ovDimLeaderLineArrowThickBase	= 1244; // Sint8 - Public for VS
		// the thickness basis of the marker for the leader line

const short ovDimLeaderLineArrowThickness	= 1245; // UInt8 - Public for VS
		// the thickness of the marker for the leader line

const short ovDimLeaderLineArrowVis			= 1246; // UInt8 - Public for VS
		// the visibility of the marker for the leader line

const short ovDimLeaderLineArrowWidth		= 1247; // Sint16 - Public for VS
		// the width of the marker for the leader line

const short ovDimTextStyle					= 1248; // Sint32 - Public for VS
		// the ref number of the text style that the dimension is linked to

const short ovObjectTextStyle				= ovDimTextStyle;  // char - Not for public use
								
const short ovDimCustomElevText 			= 1249;   // Boolean - Public for VS
		// Use a custom elevation dimension to be displayed with dimensions in the SIA standard

const short ovDimCompactRadial				= 1750; // Boolean - Public for VS
		// The compact mode flag for radial dimensions

// Light Selectors  (lightNode)
// ---------------
const short ovLightIsOn					= 50 ;  // Boolean - Public for VS
const short ovLightBrightness			= 51 ; 	// double_gs		0..1; > 1 for overlighting - Public for VS - Not for public use
const short ovLightColor				= 52 ; 	// WorldPt3	x, y, z = 0..1 - Not for public use
const short ovLightCastShadows			= 53 ; 	// Boolean - Public for VS
const short ovLightPosition				= 54 ;	// WorldPt3 - Public for VS
const short ovLightKind					= 55 ; 	// short		(kDirectionalLight | kPointLight | kSpotLight) - Public for VS
const short ovLightDirectionVector		= 56 ; 	// WorldPt3	This vector points _away from_ the light source. - Not for public use

const short ovLightDirectionHorizAngle	= 57 ; 	// double_gs - Public for VS
		// Angle about the z axis for spot and directional light direction vectors.  
		// The positive y axis is 0 horizontal degrees, counterclockwise about the positive z axis 
		// is the positive direction for this angle.  I.e.: negative x axis is +90.0 degrees, 
		// positive x axis is -90.0 degrees.  This angle is also called the pan or azimuth angle.  

const short ovLightDirectionVertAngle	= 58 ; 	// double_gs - Public for VS
		// Angle above or below the ground plane for spot and directional light direction vectors.  
		// Positive angles aim the light downward.  This angle is also called the tilt or 
		// elevation angle.
				
const short ovLightDistanceFalloff		= 59 ; 	// short - Public for VS
		// Distance falloff function (kLightNoFalloff | kLightInverseDistance | kLightInverseDistanceSquared) 
		// for point and spot lights.  These are called None, Smooth, and Sharp in the user interface.
				
const short ovLightAngularFalloff		= 60 ; 	// short - Public for VS
		// Angular falloff function (kLightNoFalloff | kLightLinear | kLightExponential | kLightCosine) 
		// for spot lights.  These are called None, Normal, Smooth, and Sharp in the user interface.  
		// The angular falloff function determines how fast the light intensity falls off from the 
		// spot beam angle to the spot spread angle.
		
const short ovLightSpread				= 61 ; 	// double_gs - Public for VS
		// For spot lights.  This is the maximum cone angle for the spot.  The angular 
		// falloff function determines the intensity at this angle.
		
const short ovLightBeam					= 62 ; 	// double_gs - Public for VS
		// For spot lights.  From zero degrees to the beam angle the intensity is constant.  
		// After the beam angle the angular falloff function determines the intensity 
		// (up to the spread angle).

const short ovLightLitFog				= 63 ;	// Boolean - Public for VS
		// Lit fog for creating volumetric effects. Currently for RW rendering modes only.
		// Uses the settings of the applied Background Shader (weather shader)

const short ovLightSoftShadows			= 64;	// Boolean - Public for VS
		// Soft shadows will be used when cast shadows is enabled. Currently for RW rendering modes only.

// Fill Space selectors
// ----------------
const short ovFillOriginPt				= 69;		// WorldPt	 - the Origin point for a gradient, image or tile fill - Not for public use.
const short ovFillXOffset				= 70;		// real		 - the X-offset for a gradient, image or tile fill- Not for public use.
const short ovFillYOffset				= 71;		// real		 - the y-offset for a gradient, image or tile fill - Not for public use
const short ovFillIAxisLength			= 72;		// real		 - the X-scale for a gradient, image or tile fill - Not for public use
const short ovFillJAxisLength			= 73;		// real		 - the Y-scale for an image fill. - Not for public use
const short ovFillAngle					= 74;		// real		 - the angle for a gradient, image or tile fill - Public for VS
const short ovFillRepeat				= 75;		// Boolean	 - the repeat-state for a gradient, image or tile fill - Public for VS
const short ovFillMirror				= 76;		// Boolean	 - the mirror-state for a gradient, image or tile fill - Public for VS
const short ovFillFlip					= 77;		// Boolean	 - the flip-state for an image fill. - Public for VS
const short ovFillGeometryType			= 78;		// longint	 - the geometry type for a gradient fill. - Public for VS
const short ovFillMaintainAspectRatio	= 79;		// Boolean	 - indicates if aspect ratio is maintained for an image fill. - Public for VS



// Worksheet selectors
// ----------------
const short ovWSHeader					= 80;		// TXString	 - worksheet header string, limited to 81 characters. - Public for VS
const short ovWSFooter					= 81;		// TXString	 - worksheet footer string, limited to 81 characters. - Public for VS
const short ovWSShowDatabaseHeaders		= 82;		// Boolean	 - worksheet database rows (headers) visibility. - Public for VS
const short ovWSShowGridlines			= 83;		// Boolean	 - worksheet gridlines preference. - Public for VS
const short ovWSShowTabs				= 84;		// Boolean	 - worksheet show tabs prefrerence. - Public for VS
const short ovWSAutoRecalculation		= 85;		// Boolean	 - worksheet auto recalculation preference. - Public for VS
const short ovWSDefaultFontIndex		= 86;		// short	 - worksheet default font index preference. - Public for VS
const short ovWSDefaultFontSize			= 87;		// short	 - worksheet default font size preference. - Public for VS
const short ovWSTopPrintMargin			= 88;		// double_gs - worksheet top print margin preference. - Public for VS
const short ovWSLeftPrintMargin			= 89;		// double_gs - worksheet left print margin preference. - Public for VS
const short ovWSBottomPrintMargin		= 90;		// double_gs - worksheet bottom print margin preference. - Public for VS
const short ovWSRightPrintMargin		= 91;		// double_gs - worksheet right print margin preference. - Public for VS

// Worksheet Image selectors
// ----------------
const short ovWSImageShowDBHeaders		= 99;		// Boolean	 - read only - worksheet on drawing database row headers visibility. - Public for VS

// Symbol selectors
// ----------------
const short ovSymbolLightMultiplier		= 100 ; 	// double_gs		Instance brightness equals definition brightness times multiplier. - Public for VS
const short ovSymbolScaleType			= 101;		// short - specifies what type of scaling the symbol has - Public for VS
													// ESymScaleType: kScaleTypeNone = 1, kScaleTypeSymmetric = 2, kScaleTypeAsymmetric	= 3
const short ovSymbolXScaleFactor		= 102;		// double_gs - the scaling of the symbol in the x-direction (1.0 is no scaling) - Public for VS
const short ovSymbolYScaleFactor		= 103;		// double_gs - the scaling of the symbol in the y-direction (1.0 is no scaling) - Public for VS
const short ovSymbolZScaleFactor		= 104;		// double_gs - the scaling of the symbol in the z-direction (1.0 is no scaling) - Public for VS



// More Fill Space selectors
// --------------------
const short ovFillXOffsetInCurrUnits	= 110;		// real (current units) - the X-offset for a gradient, image or tile fill- Public for VS
const short ovFillYOffsetInCurrUnits	= 111;		// real (current units) - the Y-offset for a gradient, image or tile fill- Public for VS
const short ovFillIAxisLengthInCurrUnits = 112;		// real (current units) - the X-scale for a gradient, image or tile fill- Public for VS
const short ovFillJAxisLengthInCurrUnits = 113;		// real (current units) - the Y-scale for a gradient, image or tile fill- Public for VS


// Plugin insert selectors
// ----------------													
const short ovPluginInsertMode			= 123 ; 	// short - where to insert the symbol in the wall - Public for VS
	
	//const InsertModeType kPluginnsertOnCenter	= 0;	insert at the center of the wall
	//const InsertModeType kPluginInsertOnEdge	= 1; 	Symbol Defs do not distinguish between left and right.
		
const short ovPluginBreakMode			= 124 ; 	// short, specifies how the wall is broken where the symbol is inserted - Public for VS

	//const BreakModeType kPluginFullBreakWithCaps = 1;	standard for most symbol insertions
	//const BreakModeType kPluginFullBreakNoCaps	= 2;	no cap lines, but the wall is broken
	//const BreakModeType kPluginHalfBreak			= 3; 	for edge insertion only;
	//const BreakModeType kPluginNoBreak			= 4;	no break in the wall		



// Symbol definiton selectors
// ----------------													
const short ovSymDefInsertMode			= 125 ; 	// short - where to insert the symbol in the wall - Public for VS
	
	//const InsertModeType kSymInsertOnCenter	= 0;	insert at the center of the wall
	//const InsertModeType kSymInsertOnEdge		= 1; 	Symbol Defs do not distinguish between left and right.
		
const short ovSymDefBreakMode			= 126 ; 	// short, specifies how the wall is broken where the symbol is inserted - Public for VS

	//const BreakModeType kSymFullBreakWithCaps = 1;	standard for most symbol insertions
	//const BreakModeType kSymFullBreakNoCaps	= 2;	no cap lines, but the wall is broken
	//const BreakModeType kSymHalfBreak			= 3; 	for edge insertion only;
	//const BreakModeType kSymNoBreak			= 4;	no break in the wall		

const short ovSymbolInsertAsGroup		= 127 ;		// Boolean, whether to perform a Shallow Symbol to Group after insertion - Public for VS

const short ovSymDefUseClass			= 128 ;     // Boolean, use the class of the symbol definition as the class for the new insert

const short ovSymDefInsertIntoWalls		= 129 ;		// Boolean, allow or prevent wall insertion of symbols

const short ovSymDefPageBased			= 130;		// Boolean - whether the symbol will have a constant page size, meaning it will have the same size
													// on screen for different layer scales, and its world size will be different for different
													// layer scales - Public for VS

const short ovSymDefStoryAware			= 131;		// Boolean - whether the symbol's height will be bound by story levels.

// Layer selectors (kLayerNode)
// ---------------
const short ovLayerAmbientIsOn			= 150;		// Boolean - Public for VS
const short ovLayerAmbientBrightness	= 151;		// double_gs - Public for VS
const short ovLayerAmbientColor			= 152;		// WorldPt3 - Public for VS
const short ovLayerVisibility			= 153;		// short, -1 = invisible, 0 = normal, 2 = grayed - Public for VS
const short ovLayerType					= 154;		// short - the layer type; read only - Public for VS
const short ovLayerDPI					= 155;		// short - the printing dpi; only for presentation layers; read/write. - Public for VS

const short ovLayerRepaginate			= 156;		// Public for VS
// ovLayerRepaginate (Boolean)
// Set() causes the pagination to be recalculated for the given Sheet Layer or Design Layer (useful after manipulating the PrintInfo).
// true = set drawing size to one page, false = divide drawing size into multiple pages;
// Get() determines how the drawing is currently paginated
// true = one page, false = multiple pages

const short ovLayerHeightInCurrUnits	= 157;		// current units, the base elevation height of the layer - Public for VS
const short ovLayerThicknessInCurrUnits	= 158;		// current units, the thickness of the layer - Public for VS
const short ovLayerDescription			= 159;		// TXString, the description of the layer (only used for sheet layers) - Public for VS

// Layer Link selectors (layerRefNode)
// ---------------
const short ovLayerLinkSourceName 		= 160;		//	TXString - Public for VS
const short ovLayerLinkProject2D 		= 161;		//	Boolean - Public for VS
const short ovLayerExpandedSheetName	= 162;		//	TXString, the sheet number followed by the sheet title in brackets (only for sheet layers); read only - Public for VS

// Sheet Layer specific
// ---------------
const short ovLayerSheetWidth			= 165;		//	double_gs - in inches; sheet layer width
const short ovLayerSheetHeight			= 166;		//	double_gs - in inches; sheet layer height

const short ovLayerSheetPaperWidth		= 167;		//	double_gs - in inches; layer page/paper width
const short ovLayerSheetPaperHeight		= 168;		//	double_gs - in inches; layer page/paper height

// Slab selectors (slabNode)
// --------------
const short ovSlabThickness				= 170;		// WorldCoord, the thickness of the roof, floor, or column - Not for public use
const short ovSlabHeight				= 171;		// WorldCoord, the z elevation for the bottom of floors and columns, - Not for public use
													//	 the height of the roof axis
const short ovSlabKind					= 172;		// short, 1 = roof, 2 = floor, 3 = column - Public for VS
const short ovSlabThicknessInCurrUnits	= 173;		// current units, the thickness of the roof, floor or column - Public for VS
const short ovSlabHeightInCurrUnits		= 174;		// current units, the z elevation for the bottom of floors and columns, - Public for VS
													//	 the height of the roof axis
const short ovSlabRoofPt1				= 175;		// WorldPt, first point of the roof axis, only set when slab kind = roof - Not for public use
const short ovSlabRoofPt2				= 176;		// WorldPt, second point of the roof axis, only set when slab kind = roof - Not for public use
const short ovSlabRoofUpslopePt			= 177;		// WorldPt, a point on the upslope side of the roof, only set when slab kind = roof - Not for public use
const short ovSlabRoofRise				= 178;		// WorldCoord, the rise over a given distance.  Use with the run to calculate a slope, only set when slab kind = roof - Not for public use
const short ovSlabRoofRun				= 179;		// WorldCoord, the run over a given distance.  Use with the rise to calculate a slope, only set when slab kind = roof - Not for public use
const short ovSlabRoofMiterType			= 180;		// short, 1 = vertical, 2 = horizontal, 3 = double, only set when slab kind = roof - Public for VS
const short ovSlabRoofDoubleMiterRatio	= 181;		// double, the percentage of a double miter which is vertical (1 is a vertical miter and 0 is a horizontal), only set when slab kind = roof - Public for VS
const short ovSlabRoofRiseInCurrUnits	= 182;		// current units, the rise over a given distance.  Use with the run  - Public for VS
													// to calculate a slope, only set when slab kind = roof
const short ovSlabRoofRunInCurrUnits	= 183;		// current units, the run over a given distance.  Use with the rise - Public for VS
													// to calculate a slope, only set when slab kind = roof
// Cavity selectors (cavityNode)
// ----------------
// NOTE: pass nil to these to get and set the default cavity information
const short ovCavityCount_OBSOLETE		= 199;		// short, the number of cavities in the handle, works only with GetObjectVariable - Public for VS
const short ovCavityOffLeft_OBSOLETE	= 200;		// WorldCoord, offset from center-line to the left edge of cavity - Not for public use
													//   add the cavity index to get successive values (for example, the seventh cavity = ovCavityOffLeft + 6)
const short	ovCavityOffRight_OBSOLETE	= 220;		// WorldCoord, offset from center-line to the right edge of the cavity - Not for public use												
													//	 add the cavity index to get successive values
const short ovCavityIsPair_OBSOLETE		= 240;		// Boolean, true if the cavity is a pair of lines, otherwise it is a single line and the right offset - Public for VS
													// 	 and the fill pattern for this cavity is meaningless
													//	 add the cavity index to get successive values
const short ovCavityFill_OBSOLETE		= 260;		// Sint32, the fill pattern/hatch to be used between a pair of cavity lines - Public for VS
													//	 add the cavity index to get successive values
const short ovCavityPenWeight_OBSOLETE	= 280;		// short, the pen weight of the cavity line(s), in mils - Public for VS
													//	 add the cavity index to get successive values
const short ovCavityPenStyle_OBSOLETE	= 300;		// short, the pen pattern/dash style of the cavity line(s) - Public for VS
													//	 add the cavity index to get successive values
const short ovCavityOffLeftInCurrUnits_OBSOLETE		= 320;		// current units, offset from center-line to the left edge of cavity - Public for VS
													//   add the cavity index to get successive values
const short	ovCavityOffRightInCurrUnits_OBSOLETE	= 340;		// current units, offset from center-line to the right edge of the cavity - Public for VS											
													//	 add the cavity index to get successive values


const short	ovCavityMain_OBSOLETE		= 690;		// short, the index of the main cavity - Public for VS
													// pass NULL for the object handle to use the default cavity settings

// Sweep selectors (cavityNode)
// ----------------
const short ovSweepZOffset				= 400;		// see the document for GS_CreateSweep for more information on how to use - Not for public use
													//	 this value.
const short ovSweepZOffsetInCurrUnits	= 401;		// current units, the z-value for the sweep - Public for VS

// Saved sheet selectors
// ---------------------
const short ovSheetSaveView				= 450;		// Boolean, true if the sheet saves the view orientation factors, which includes the orientation and projection - Public for VS
const short ovSheetSavePage				= 451;		// Boolean, true if the sheet saves the page location - Public for VS
const short ovSheetSaveClass			= 452;		// Boolean, true if the sheet saves the class options, active class and class visibilities - Public for VS
const short ovSheetSaveLayer			= 453;		// Boolean, true if the sheet saves the layer options, active layer and layer visibilities - Not for public use
const short ovSheetSaveZoomPan			= 456;		// Boolean, true if the sheet saves the zoom and pan settings - Public for VS
const short ovSheetSaveStackLayers		= 457;		// Boolean, true if the sheet saves the stack layers settings - Not for public use
const short ovSheetStackLayersStatus	= 458;		// Boolean, true if the sheet has layer stacking on - Not for public use
const short ovSheetSaveActiveLayer		= 459;		// Sint32, read-only, the active layer internalIndex of the saved view
const short ovSheetSaveActiveClass		= 460;		// Sint32, read-only, the active class internalIndex of the saved view
const short ovSheetProjection			= 461;		// Sint16, read-only, the saved projectsion when ovSheetSaveView is on
const short ovSheetSaveLayerOptions		= 462;		// Sint16, read-only, bit flag values for layer and class options:
const short ovSheetSaveClassOptions		= 463;		// Sint16, read-only,			0x01 - showOther
													//								0x02 - grayOther
													//								0x04 - snapOnly
													//								0x08 - doSingle
													//
													//	if		( NOT showOther )			THEN (1) "Active Only"
													//	else if	( grayOther && snapOnly)	THEN (3) "Gray/Snap Others"
													//	else if	( grayOther )				THEN (2) "Gray Others";
													//	else if	( snapOnly)					THEN (5) "Show/Snap Others";
													//	else if	( doSingle)					THEN (4) "Show Others";
													//	else								     (6) "Show/Snap/Modify Others";
													//
													//				1 - Active Only
													//				2 - Gray Others
													//				3 - Gray/Snap Others
													//				4 - Show Others
													//				5 - Show/Snap Others
													//				6 - Show/Snap/Modify Others


// Saved View (formerly Sheet) Related
// These change the visibility setting for the given Class/Layer in all existing Saved Views.
// The ovSetDesignLayerVisibilityInAllSavedViews selector only works when given a Design Layer, and only changes Saved Views of Design Layers.
// ---------------------
const short ovSetDesignLayerVisibilityInAllSavedViews	= 454;	// short, -1 = invisible, 0 = normal, 2 = grayed, 3 = don't save - Public for VS
const short ovSetClassVisibilityInAllSavedViews			= 455;	// short, -1 = invisible, 0 = normal, 2 = grayed, 3 = don't save - Public for VS


// Texture selectors (kMaterialNode)
// -----------------
const short	ovIsTextureableObject		= 500;		// Boolean "Get" only - Public for VS

const short	ovMaterialIsExpanded		= 501;		// Boolean, sets whether three or just  - Public for VS
													// a single material is applied to
													// this object (can be up to three for
													// walls or two for roofs).

#if 0
	// These object variables are obsolete in VW/RW 9. -DLD 4/6/2000
	const short	ovMaterialShininess 		= 502;		// Sint32 (percentage value - 0 == dull) - Not for public use
	const short	ovMaterialTransparency 		= 503;		// Sint32 (percentage value - 0 == opaque) - Not for public use
	const short	ovMaterialTextureShader 	= 504;		// Sint32 (LightWorks property ref) - Not for public use
	const short	ovMaterialTextureBitmap 	= 505;		// MCObjectHandle - Not for public use
#endif 	// 0

const short ovMaterialColorShaderRecord 		= 506; 	// MCObjectHandle (record) - Not for public use
const short ovMaterialReflectivityShaderRecord 	= 507; 	// MCObjectHandle (record) - Not for public use
const short ovMaterialTransparencyShaderRecord 	= 508; 	// MCObjectHandle (record) - Not for public use
const short ovMaterialBumpShaderRecord 			= 509; 	// MCObjectHandle (record) - Not for public use
const short ovMaterialSize 						= 510; 	// Real64, in real-world inches - Not for public use
const short ovMaterialSizeInCurrUnits			= 511;  // double, in current units - Public for VS
const short ovResetTextureThumbnail				= 512;	// MCObjectHandle - Not for public use

// TextureBitmap selectors (kTextureBitmapNode)
// -----------------------
#if 0
	// This selector is obsolete in VW/RW 9.  -DLD 2/1/2001
	const short	ovTextureBitmapOrigin 		= 520;		// WorldPt, in pixels - Not for public use
#endif
const short	ovTextureBitmapFeatureStart = 521;		// WorldPt, in pixels - Not for public use
const short	ovTextureBitmapFeatureEnd 	= 522;		// WorldPt, in pixels - Not for public use
const short	ovTextureBitmapFeatureSize 	= 523;		// double_gs, in real-world inches - Not for public use
const short	ovTextureBitmapRepeatHoriz 	= 524;		// Boolean - Public for VS - Not for public use
const short	ovTextureBitmapRepeatVert 	= 525;		// Boolean - Not for public use
#if 0
	// This selector is obsolete in RW 12.  -DLD 12/9/2004
	const short	ovTextureBitmaptagged = 526;		// MCObjectHandle - Not for public use
#endif
const short ovTextureBitmapFeatureSizeInCurrUnits = 527; // double, in current units - Public for VS
const short ovTextureBitmapImageDefNode = 528; 		// MCObjectHandle - Not for public use

const short ovShaderRecordTextureBitmap = 529;		// MCObjectHandle (texture bitmap) - Get only

// Paint selectors
const short ovPaintWidthPixels 			= 530; 		// Sint32 - Public for VS
const short ovPaintHeightPixels 		= 531; 		// Sint32 - Public for VS
const short ovPaintCompression			= 532;		// Sint32, 0=None, 1=JPEG, 2=PNG, 3=PNGMono - Public for VS
const short ovImageCompression			= 533;		// Sint32, 0=None, 1=JPEG, 2=PNG, 3=PNGMono - Public for VS
const short ovImageWidthPixels 			= 534; 		// Sint32 - Public for VS
const short ovImageHeightPixels 		= 535; 		// Sint32 - Public for VS

const short ovPaintTDWidth				= 536;		// WorldCoord - Not for public use
const short ovPaintTDHeight				= 537;		// WorldCoord - Not for public use
const short ovPaintTDOriginX			= 538;		// WorldCoord - Not for public use
const short ovPaintTDOriginY			= 539;		// WorldCoord - Not for public use

// TextureSpace selectors (kTextureSpaceNode)
//
// *** OLD *** Use gSDK->GetTextureMappingInfo and gSDK->SetTextureMappingInfo instead as of 2009.  -DLD 6/17/2008
//
// ----------------------
const short	ovTextureSpaceKind 			= 540;		// Sint32 (kPlane, etc.) - Public for VS - Not for public use
const short	ovTextureSpaceOriginOrientation = 541;	// TransformMatrix, from world 	space to texture space - Not for public use
const short	ovTextureSpace2DOffset 		= 542;		// WorldPt, in Coords - Not for public use
const short	ovTextureSpace2DScale 		= 543;		// double, scale factor - Public for VS
const short	ovTextureSpace2DRotation	= 544;		// double_gs radians - Public for VS
const short	ovTextureSpaceRadius 		= 545;		// Sint32 (WorldCoord) valid only for spherical & cylindrical texture spaces - Not for public use
const short	ovTextureSpaceStartCap 		= 546;		// Boolean, extrude & sweep only  - Public for VS
const short	ovTextureSpaceEndCap 		= 547;		// Boolean, extrude & sweep only  - Public for VS
const short	ovTextureSpaceMultiPartID 	= 548;		// byte, for walls and roofs (kPrimary, etc.) - Public for VS
const short ovTextureSpaceRadiusInCurrUnits = 549;	// double (current units) valid only for spherical & cylindrical texture spaces - Public for VS

const short ovShaderRecordImageDefNode = 550;		// MCObjectHandle (image node) - Get only
const short ovShaderRecordGrayscaleImageDefNode = 551; // MCObjectHandle (8-bit image node) - Get only
const short ovShaderRecordNonGrayscaleImageDefNode = 552; // MCObjectHandle (non 8-bit image node) - Get only
const short ovShaderRecordBrickImageDefNode = 553;		// MCObjectHandle (Bricks(prototype) Shader -> return Bricks(group) image node) - Get only
const short ovShaderRecordGapImageDefNode = 554;		// MCObjectHandle (Bricks(prototype) Shader -> return Gap(group) image node) - Get only
const short ovShaderRecordAltBrickImageDefNode = 555;	// MCObjectHandle (Bricks(prototype) Shader -> return Alt Bricks(group) image node) - Get only
#define GRASS_SHADER_ENABLED
#if defined GRASS_SHADER_ENABLED
const short ovShaderRecordGrassImageDefNode = 556;
const short ovShaderRecordMaterialIsGrass   = 559;		// To tell if the material has a grass shader. - Get only.
#endif	// #if defined GRASS_SHADER_ENABLED
const short ovShaderRecordDisplacementOnOrOff = 557;	// RWRenderOptions.fDisplacement.
const short ovShaderRecordDisplacementQuality = 558;	// RWRenderOptions.fDisplacementQuality.


// RoundWall selectors (kRoundWallNode)
// --------------
const short ovRoundWallCounterClockwise	= 570;		// Boolean, read only, TRUE == counterclockwise, FALSE == clockwise - Public for VS
const short ovRoundWallRadius			= 571;		// DOUBLE, round wall thickness, read/write - Public for VS

const short ovLayerCropRect				= 590;		// WorldRect, read only, - Not for public use
const short	ovLayerRWBackground			= 591;		// Sint32 (SysName), read/write - Public for VS
const short ovLayerHDRIBackground		= 592;      // Sint32 RefNumber of the HDRI background associated with a layer, read only - Public for VS

// Wall selectors (wall Nodes)
// --------------
const short ovWallStartCapLeftPoint		= 600;		// WorldPt, read/write - Not for public use
const short ovWallStartCapRightPoint	= 601;		// WorldPt, read/write  - Not for public use
const short ovWallEndCapLeftPoint		= 602;		// WorldPt, read/write  - Not for public use
const short ovWallEndCapRightPoint		= 603;		// WorldPt, read/write  - Not for public use

const short ovWallStartHeightTop		= 604;		// WorldCoord, read/write - Not for public use
const short ovWallStartHeightBottom		= 605;		// WorldCoord, read/write  - Not for public use
const short ovWallEndHeightTop			= 606;		// WorldCoord, read/write - Not for public use
const short ovWallEndHeightBottom		= 607;		// WorldCoord, read/write  - Not for public use

const short ovWallLeftGrossArea			= 608;		// WorldCoord, read only : area of the wall's left side including windows - Public for VS
const short ovWallRightGrossArea		= 609;		// WorldCoord, read only : area of the wall's right side including windows - Public for VS
const short	ovWallGrossArea				= 610;		// WorldCoord, read only : average of left and right area including windows - Public for VS
const short ovWallLeftNetArea			= 611;		// WorldCoord, read only : area of the wall's left side with window holes subtracted - Public for VS
const short ovWallRightNetArea			= 612;		// WorldCoord, read only : area of the wall's right side with window holes subtracted - Public for VS
const short	ovWallNetArea				= 613;		// WorldCoord, read only : average of left and right area with window holes subtracted - Public for VS
const short ovWallLeftAverageHeight		= 614;		// WorldCoord, read only : average height of the wall's left side - Public for VS
const short ovWallRightAverageHeight	= 615;		// WorldCoord, read only : average height of the wall's right side - Public for VS
const short ovWallAverageHeight			= 616;		// WorldCoord, read only : average height of the wall - Public for VS
const short ovSetRoundWallArc			= 617;		// WorldCoord, read only : returns the defining height of the wall - Not for public use
const short ovSetWallWidth			    = 618;		// WorldCoord, write only : sets the wall's width - Not for public use
const short ovSetWallWigth			    = 618;		// WorldCoord, write only : sets the wall's width (typo retained for compatibility - Not for public use
const short ovSetPolyArcRadius			= 619;		// WorldCoord, read only - Not for public use
const short ovTempPreviewDrawingWall	= 620;		// NNA INTERNAL USE ONLY : BlankHandle, read only : temporary preview drawing wall - Not for public use

const short ovWallOverallHeightTop		= 621;		// WorldCoord, read/write - Not for public use
const short ovWallOverallHeightBottom	= 622;		// WorldCoord, read/write  - Not for public use

// Solids selectors (csg tree nodes)
// --------------
const short ovSolidHistory				= 630;		// Boolean, read/write - Public for VS
const short ovSolidXScale				= 631;		// scaling in X - Public for VS
const short ovSolidYScale				= 632;		// scaling in Y - Public for VS
const short ovSolidZScale				= 633;		// scaling in Z - Public for VS

const short ovIs3D						= 650;		// Boolean, read only  - Public for VS
const short ovIs2D						= 651;		// Boolean, read only  - Public for VS
const short ovIsPoly2DClockwise			= 652;		// Boolean, read only - Public for VS


// Hatch selectors (kHatchDefNode) - JDW, 9/17/01
// --------------
const short ovHatchNumLevels			= 660;		// short,	read only - Not for public use
const short ovHatchIsTransparent		= 661;		// Boolean,	read/write - Not for public use
const short ovHatchHasPageUnits			= 662;		// Boolean,	read/write - Not for public use
const short ovHatchRotateInWall			= 663;		// Boolean,	read/write - Not for public use
const short ovHatchRotateInSymbol		= 664;		// Boolean,	read/write - Not for public use


// Text selectors (kTextNode) - JDW, 9/18/01
// --------------
const short ovTextIsLinkedToRecord		= 680;		// Boolean, read only - Public for VS
const short ovTextRepeatingTab          = 681;      // WorldCoord - Not for public use
const short ovTextRepeatingTabInCurrUnits = 682;	// current units - Public for VS
const short ovTextIsSiaElevText			= 683;		// Boolean, read only - Not for public use
const short ovTextTightFill				= 684;		// Boolean, read/write - Public for VS
const short ovTextUpdateTextStyleSize	= 685;		// Boolean, read/write - Puglic for VS : value doesn't matter. accessing this variable will update the size of text with text style to match the layer scale
const short ovUnlinkTextFromRecord		= 686;		// Boolean, write only - 
const short ovTextIsDimNoteText			= 687;		// Boolean, read only - Not for public use

// Fill style/type selectors
// --------------
const short ovFillStyle					= 695;		// Sint32,	read/write - Public for VS
const short ovFillType					= 696;		// short,	read only - Public for VS
const short ovFillLocalMapping			= 697;		// Boolean - Not for public use
const short ovIsFillSpaceExisting		= 698;		// Boolean, read only - Public for VS


//	NGNodeType accessors from 700 -> 800 
const short ovLocked					= 700;		// Boolean, read/write - Public for VS
const short ovHideDetail				= 701;		// Boolean, read/write : used to hide wall cavity lines or complex objects content at small scales - Public for VS
const short ovIsStructural				= 702;		// Boolean, read/write : used to mark an object as structural - Public for VS
const short ovFirstAuxObject			= 703;		// MCObjectHandle, read/write : used to manipulate the Aux list - Public for VS
const short ovInheritParentMapping		= 704;		// Boolean, read/write : Used for PIOs to have same texture as parent walls.  -DLD 3/29/2006 - Public for VS
const short ovHideNonDetail				= 705;		// Boolean, read/write : used to hide complex objects content at big scales - Public for VS
const short ovTextureWorldToObjectMatrix= 706;		// TransformMatrix, read : Used for getting the default texturing world to object matrix for objects without local coord systems (3D poly, mesh)

//	NGNodeType stores PlanarRefID which is only valid for certain planr types.
const short ovHasAssociatedPlane		= 710;		// The PlanarRefID property can be called for Extrudes and other objects that do not have a plane.  THis tells caller if the object has a plane.  Extrudes will always return false.

// BlankType stores visibilities of the object at different levels of detail
const short ovHighDetailVisible			= 750;		// Boolean, read/write - Public for VS : visible at high level of detail
const short ovMidDetailVisible			= 751;		// Boolean, read/write - Public for VS : visible at medium level of detail
const short ovLowDetailVisible			= 752;		// Boolean, read/write - Public for VS : visible at low level of detail

const short ovPluginHasFontStyle		= 800;		// Boolean, write : gives Object a font style property - Public for VS
const short ovCustomObjectFontStyle		= ovPluginHasFontStyle; // Public for VS
const short ovCustomObjectArea			= 801;		// Real, Used to hold the area of a custom object - Public for VS
const short ovCustomObjectPerimeter		= 802;		// Real, Used to hold the perimeter of a custom object - Public for VS


//	Symbol type constants used to set a custom object subtype while the object is being created.  SenEntityMatrix, for example, needs this to be set in order to be called.  
//	Use this API to set the symType if the object has yet to be regenerated.
//	NOTE: the symType is determined by the objects it has regenerated.   As such, you can't force an object to be a certain subtype with this API.
#define kCustomObjectSymType2DSym			0
#define kCustomObjectSymType3DSym			1
#define kCustomObjectSymTypeHybridSym		2
const short ovCustomObjectSymType		= 803;		//	short, Used to set the symType of a custom object - SymType is determined in 2011 by the contents of the object.  Before the regeneration the 
													//	symType may be set using this API.  SetEntityMatrix need the symType to be kCustomObjectSymType2DSym

//
const short ovSetTimeStamp				= 870;		// Boolean, write : used to set the timestamp of an object. Not for public use
//	
const short ovFormatVisibility			= 900;		// Boolean, read/write : gives Format user interface visibility - Public for VS

// Viewport type selectors
// --------------
const short ovViewportProjectionType		= 1000;    	// short	read/write - the viewport projection type. - Public for VS
const short ovViewportRenderType			= 1001;		// short	read/write - the viewport render type. - Public for VS
const short ovViewportPerspectiveDistance	= 1002;		// real		read/write - the viewport perspective distance (used with custom perspective). - Public for VS
const short ovViewportScale					= 1003;		// real		read/write - the viewport scale. - Public for VS
const short ovViewportDirty					= 1004;		// Boolean  read/write - the viewport out-of-date (dirty) state. - Public for VS
const short ovViewportProject2D				= 1005;		// Boolean  read/write - the viewport project 2D state. - Public for VS
const short ovViewportRenderBackground		= 1006;		// Sint32		read/write - the viewport render background. - Public for VS
const short ovViewportViewType				= 1007;		// short	read/write - the viewport view type. - Public for VS
const short ovViewportLineWeightScale		= 1008;		// double	read/write - the viewport line weight scale. - Public for VS
const short ovViewportArrowheadScale		= 1009;		// double	read/write - the viewport arrowhead scale. - Public for VS
const short ovViewportDashedLineScale		= 1010;		// double	read/write - the viewport dashed line length/spacing scale. - Public for VS
const short ovViewportHatchLineScale		= 1011;		// double	read/write - the viewport hatch line spacing scale. - Public for VS
const short ovViewportDesignTextScale		= 1012;		// double	read/write - the viewport design layer referenced text size scale. - Public for VS
const short ovViewportSlashThicknessScale	= 1013;		// double	read/write - the viewport slash thcikness scale. - Public for VS
const short ovViewportAmbientIsOn			= 1014;		// Boolean  read/write - the viewport ambient light is ON or OFF. - Public for VS
const short ovViewportAmbientBrightness		= 1015;		// double	read/write - the viewport ambient light brightness. - Public for VS
const short ovViewportAmbientColor			= 1016;		// WorldPt3 read/write - the viewport ambient light color. - Public for VS
const short ovSetDesignLayerVisibilityInAllViewports	= 1017;	// short, -1 = invisible, 0 = normal, 2 = grayed - Public for VS
const short ovSetClassVisibilityInAllViewports			= 1018;	// short, -1 = invisible, 0 = normal, 2 = grayed - Public for VS
const short ovViewportHDRIBackground		= 1019;		// Sint32		read only  - the background for environment lighting - Public for VS
const short ovSectionVP2DAttributeClass		= 1020;		// Sint32		read only - the RefNumber of the class responsible for attributes of overall cross-section or just the x-section of structural elements. - Public for VS
const short ovSectionVP2DOtherAttribClass	= 1021;		// Sint32		read only - the RefNumber of the class responsible for attributes of cross-section generated from non-structural elements - Public for VS
const short ovSectionVP3DFillStyleClass		= 1022;		// Sint32     read only - the RefNumber of the class reposnsible for fill style of the objects beyond section plane - Public for VS
const short ovSectionVP3DLineStyleClass		= 1023;		// Sint32     read only - the RefNumber of the class responsible for line style of the objects beyond section plane - Public for VS
const short ovViewportXPosition				= 1024;		// double   read only - the X coordinate of the viewport on the sheet layer - Public for VS
const short ovViewportYPosition				= 1025;		// double   read only - the Y coordinate of the viewport on the sheet layer - Public for VS
const short ovViewportAngleWithXAxis		= 1026;		// double	read only - the angle that the viewport subtends with the X axis on the sheet layer in degrees - Public for VS
const short ovViewportShowWallComponents_OBSOLETE	= 1027;
const short ovViewportGrayTransparent		= 1028;		// Boolean  read/write - the viewport renders gray layers transparent - Public for VS
const short ovViewportFlipText				= 1029;		// Boolean  read/write - the viewport/dlvp adjusts for flipped text - Public for VS
const short ovViewportBlackAndWhite			= 1030;		// Boolean  read/write - the viewport/dlvp draws in black and white only - Public for VS
const short ovViewportUseDocumentClassVis	= 1031;		// Boolean  read/write - set/reads the Use Document Class visibilities settings for dlvps - Public for VS
const short ovViewportDescription			= 1032;		// TXString	read/write - a description for the viewport, which corresponds to the Dwg Title field for a corresponding Drawing Label. - Public for VS
const short ovViewportLocator				= 1033;		// TXString	read/write - the locator for the viewport, which corresponds to the Item field for a corresponding Drawing Label. - Public for VS
const short ovViewportIsLinked				= 1034;		// Boolean	read - indicates whether the viewport is a linked viewport
const short ovViewportDisplayPlanar			= 1035;		// Boolean	read/write - the flag to indicate if planar and 2D objects are to be displayed
const short ovViewportForegroundRenderType	= 1036;		// short	read/write - the viewport render type. - Public for VS
const short ovViewportHasCamera				= 1037;		// Boolean  read only  - whether there is a camera attached to the viewport or not
const short ovCameraAttachedToViewport		= 1038;		// Boolean  read only  - whether the camera is attached to a viewport or not
const short	ovViewportCropVisible			= 1039;		// Boolean  read/write - get/set the Crop Visible state of a viewport - Public for VS
const short	ovViewportLayerHeightIgnored	= 1040;		// Boolean  read only -  whether the viewport ignored layer height for single layer case
const short ovViewportLightingDevice		= 1041;		// read/write - make an association between a lighting device light and an overriden light object for the viewport.
const short ovViewportRePositionDimensionText	= 1042;	// Boolean  read/write - the viewport/dlvp re-positions dimension text to other side of dimension line - Public for VS
const short ovIsDesignLayerSectionViewport	= 1043;		// Boolean read only - indicates whether the linked viewport is a sheet layer or a design layer viewport - Public fo VS
const short ovFDLSVPHiddenLineInWireframe_OBSOLETE	= 1044;
const short ovViewportPageSymbolScale		= 1045;		// double	read/write - the viewport page symbol scale. - Public for VS
const short ovViewportNavigateToFromSectMarker = 1046;	// Boolean	write only - selects the viewport and makes it visible - Not for public use
const short ovViewportDetailLevel			= 1047;		// short read/write - low detail = 0, medium detail = 1, high detail = 2 - Public for VS
const short ovViewportIsHorizontalSection	= 1048;		// Boolean	read - indicates whether the viewport is horizontal section

// Sketch selectors
const short ovSketchStyle					= 1100;		// Sint32 read/write, -2 = no sketch, 0 = default, > 0 = refNum of the sketch style - Public for VS

// Georeference Node Selectors
const short ovGeoRefProjection				= 1110;		// short		read/write - the projection type lambert conic = 0, utm = 1 - Public for VS
const short ovGeoRefFlag					= 1111;		// Boolean		read/write - the lat/Sint32 vs XY flag if lat/Sint32 file true else false - Public for VS
const short ovGeoRefFirstFlag				= 1112;		// Boolean		read/write - the first import flag true until a shapefile has been imported - Public for VS
const short ovGeoRefLayerFlag				= 1113;		// Boolean		read/write - the new layer/class flag if user chose new layer option true  - Public for VS - Public for VS
const short ovGeoRefScale					= 1114;		// double		read/write - the model space scale - Public for VS
const short ovGeoRefPoint					= 1115; 	// WorldPt		read/write - the georeference point to use when projection algorithms are called - Public for VS
const short ovGeoRefOffset					= 1116;		// WorldPt		read/write - the georeference offset to use when projection algorithms are called - Public for VS
const short ovGeoRefLayer					= 1117;		// RefNumber	read/write - the layer of the first import to class if user selected import to new class - Public for VS


// Wall Style selectors - These are obsolete - See "Wall Style and Slab Style selectors" below for equivilent functionality
const short ovWallStyleThickness_OBSOLETE						= 1118;
const short ovWallStylePenWeight_OBSOLETE						= 1119;
const short ovWallStylePenStyle_OBSOLETE						= 1120;
const short ovWallStyleFill_OBSOLETE							= 1121;
const short ovWallStylePenForeColor_OBSOLETE					= 1122;
const short ovWallStylePenBackColor_OBSOLETE					= 1123;
const short ovWallStyleFillForeColor_OBSOLETE					= 1124;
const short ovWallStyleFillBackColor_OBSOLETE					= 1125;
const short ovWallStyleUseClassAttributes_OBSOLETE				= 1126;
const short ovWallStyleHeight_OBSOLETE							= 1127;
const short ovWallStyleLinkHeightToLayerDeltaZ_OBSOLETE			= 1128;
const short ovWallStyleLayerDeltaZOffset_OBSOLETE				= 1129;
const short ovWallStyleClass_OBSOLETE							= 1130;
const short ovWallStyleCaps_OBSOLETE							= 1131;
const short ovWallStyleControlOffset_OBSOLETE					= 1132;
const short ovWallStyleUseTexturesAtWallCreation_OBSOLETE		= 1133;
const short ovWallStyleUseLeftTextureForTheEntireWall_OBSOLETE	= 1134;
const short ovWallStyleLeftTexture_OBSOLETE						= 1135;
const short ovWallStyleCenterTexture_OBSOLETE					= 1136;
const short ovWallStyleRightTexture_OBSOLETE					= 1137;
const short ovWallStyleMark_OBSOLETE							= 1138;
const short ovWallStyleDescription_OBSOLETE						= 1139;
const short ovWallStyleWallFunction_OBSOLETE					= 1140;
const short ovWallStyleCostIndexCode_OBSOLETE					= 1141;
const short ovWallStyleFireRating_OBSOLETE						= 1142;
const short ovWallStyleSTCRating_OBSOLETE						= 1143;
const short ovWallStyleThermalResistance_OBSOLETE				= 1144;
const short ovWallStyleModel_OBSOLETE							= 1145;
const short ovWallStyleManufacturer_OBSOLETE					= 1146;
const short ovWallStyleURL_OBSOLETE								= 1147;
const short ovWallStyleUseFillClassAttributes_OBSOLETE			= 1148;
const short ovWallStyleUsePenClassAttributes_OBSOLETE			= 1149;
const short ovWallStyleOpacity_OBSOLETE							= 1150;
const short ovWallStyleUseClassOpacity_OBSOLETE					= 1151;
const short ovWallStyleCapAttributesType_OBSOLETE				= 1157;

// Symbol Definition Resource Browser Preview Selectors
// --------------
const short ovThumbnailView								= 1152;	// short		write only - The Resource Manager's thumbnail view for a symbol - Public for VS
const short ovThumbnailRender							= 1153;	// short		write only - The Resource Manager's thumbnail render for a symbol - Public for VS
const short ovThumbnailImageComponent					= 1156; // short		write only - The Resource Manager's thumbnail image component for a symbol - Public for VS (not implemented yet)

// RenderWorks Background
const short ovRWBackgroundWidth							= 1154; // WorldCoord	read/write - RenderWorks image background width - Public for VS
const short ovRWBackgroundHeight						= 1155; // WorldCoord	read/write - RenderWorks image background height - Public for VS

// Planar Objects
const short ovPlanarObjIsSrceen							= 1160;	// Boolean		read/write - Checks if an object is 2D screen object.
const short ovIsPlanarObject							= 1161; // Boolean		read only  - Checks if an object is planar.
const short ovIsLayerPlane								= 1162; // Boolean		read only  - Checks if an object is in layer plane.
const short	ovIsHybrid									= 1163; // Boolean		read only  - Checks if an object is hybrid.

// Parametric 
const short ovParametricInternalID						= 1165;	// short		read - 
const short	ovParametricLocalizedName					= 1166;	// TXString		read - Return the localized name of a parametric object, record, or format - Public for VS
const short	ovParametricImmediateReset					= 1167;	// Boolean		write only - Useful only for Scripts. Similar to the 'ResetObject' call but causes immediate reset.
																//								Note! This can only be called to reset SDK parametrics, otherwise it might cause corruption in the Scripting engine
const short ovParametricHideStyleParameters				= 1168;	// Boolean		read - Return whether a style supported object has its Hide Style Parameters option checked

// Tile Fills
const short ovTilePageSpace								= 1170;	// Boolean	 - the page/world state of the tile - Public for VS
const short ovTileTransparentBackground					= 1171;	// Boolean	 - the transparent background state of the tile - Public for VS
const short ovTileOffsetPoint							= 1172;	// WorldPt	 - the offset point of the tile - Public for VS
const short ovTileRepetitionPoint						= 1173;	// WorldPt	 - the repetition point of the tile - Public for VS
const short ovTileRotateInWall							= 1174;	// Boolean	 - the rotate in wall state of the tile - Public for VS
const short ovTileRotateInSymbol						= 1175;	// Boolean	 - the rotate in symbol state of the tile - Public for VS

const short ovLegacyZShift								= 1176; // Double	 - read - gets the zshift for the input object (or active container if input nil)

// Wall Style, Slab Style, and Roof Style selectors
const short ovArchStyleThickness						= 1177; // WorldCoord	read/write - The thickness, read-only for Slab Styles and Roof Styles - Public for VS
const short ovArchStyleFill								= 1178; // Sint32		read/write - The fill pattern index or negative ref number of the fill - Public for VS
const short ovArchStylePenStyle							= 1179; // Sint32		read/write - The pen style - Public for VS
const short ovArchStylePenWeight						= 1180; // short		read/write - The pen weight - Public for VS
const short ovArchStyleFillForeColor					= 1181; // short		read/write - The color index of the fill fore color - Public for VS
const short ovArchStyleFillBackColor					= 1182; // short		read/write - The color index of the fill back color - Public for VS
const short ovArchStylePenForeColor						= 1183; // short		read/write - The color index of the pen fore color - Public for VS
const short ovArchStylePenBackColor						= 1184; // short		read/write - The color index of the pen back color - Public for VS
const short ovArchStyleOpacity_OBSOLETE					= 1185; // Obsolete
const short ovArchStyleUseFillClassAttributes			= 1186; // Boolean		read/write - Whether or not the fill attributes are by class - Public for VS
const short ovArchStyleUsePenClassAttributes			= 1187; // Boolean		read/write - Whether or not the pen attributes are by class - Public for VS
const short ovArchStyleUseClassOpacity_OBSOLETE			= 1188; // Obsolete
const short ovArchStyleCapAttributesType				= 1189; // short		read/write - The cap attributes type (Wall Style only) - 0 = Wall line, 1 = Component lines - Public for VS
const short ovArchStyleBaseHeight_OBSOLETE				= 1190; // Obsolete
const short ovArchStyleHeight_OBSOLETE					= 1191; // Obsolete
const short ovArchStyleLinkTopToLayerDeltaZ_OBSOLETE	= 1192; // Obsolete
const short ovArchStyleOffsetFromLayerDeltaZ_OBSOLETE	= 1193; // Obsolete
const short ovArchStyleCaps								= 1194; // short		read/write - The caps (insertion option) (Wall Style only) - 0 = None, 1 = Start, 2 = End, 3 = Both - Public for VS
const short ovArchStyleClass							= 1195; // RefNumber	read/write - The ref number of the class (insertion option) - Public for VS
const short ovArchStyleControlOffset					= 1196; // WorldCoord	read/write - The control offset for the Wall tool or Round Wall tool (insertion option) (Wall Style only) - Public for VS
const short ovArchStyleTextureSet						= 1197; // short		read/write - The texture set (insertion option) - 0 = Object textures, 1 = Component textures - Public for VS
const short ovArchStyleOverallTexture					= 1198; // RefNumber	read/write - The ref number of the overall texture (insertion option) - 0 = No texture, -1 = Class texture - Public for VS
const short ovArchStyleLeftTexture						= 1199; // RefNumber	read/write - The ref number of the left texture (insertion option) (Wall Style only) - 0 = No texture, -1 = Class texture, -2 = Part does not exist - Public for VS
const short ovArchStyleRightTexture						= 1200; // RefNumber	read/write - The ref number of the right texture (insertion option) (Wall Style only) - 0 = No texture, -1 = Class texture, -2 = Part does not exist - Public for VS
const short ovArchStyleStartCapTexture					= 1201; // RefNumber	read/write - The ref number of the start cap texture (insertion option) (Wall Style only) - 0 = No texture, -1 = Class texture, -2 = Part does not exist - Public for VS
const short ovArchStyleEndCapTexture					= 1202; // RefNumber	read/write - The ref number of the end cap texture (insertion option) (Wall Style only) - 0 = No texture, -1 = Class texture, -2 = Part does not exist - Public for VS
const short ovArchStyleTopTexture						= 1203; // RefNumber	read/write - The ref number of the top texture (insertion option) - 0 = No texture, -1 = Class texture, -2 = Part does not exist - Public for VS
const short ovArchStyleBottomTexture					= 1204; // RefNumber	read/write - The ref number of the bottom texture (insertion option) - 0 = No texture, -1 = Class texture, -2 = Part does not exist - Public for VS
const short ovArchStyleHolesTexture						= 1205; // RefNumber	read/write - The ref number of the holes texture (insertion option) (Wall Style only) - 0 = No texture, -1 = Class texture, -2 = Part does not exist - Public for VS
const short ovArchStyleSidesTexture						= 1206; // RefNumber	read/write - The ref number of the sides texture (insertion option) (Slab Style and Roof Style only) - 0 = No texture, -1 = Class texture, -2 = Part does not exist - Public for VS
const short ovArchStyleMark_OBSOLETE					= 1207; // Obsolete
const short ovArchStyleDescription_OBSOLETE				= 1208; // Obsolete
const short ovArchStyleFunction_OBSOLETE				= 1209; // Obsolete
const short ovArchStyleExterior_OBSOLETE				= 1210; // Obsolete
const short ovArchStyleLoadBearing_OBSOLETE				= 1211; // Obsolete
const short ovArchStyleFireRating_OBSOLETE				= 1212; // Obsolete
const short ovArchStyleCombustibleConstruction_OBSOLETE	= 1213; // Obsolete
const short ovArchStyleCompartmentation_OBSOLETE		= 1214; // Obsolete
const short ovArchStyleUValue_OBSOLETE					= 1215; // Obsolete
const short ovArchStyleRValue_OBSOLETE					= 1216; // Obsolete
const short ovArchStyleAcousticRating_OBSOLETE			= 1217; // Obsolete
const short ovArchStyleCostIndexSystem_OBSOLETE			= 1218; // Obsolete
const short ovArchStyleCostIndexCode_OBSOLETE			= 1219; // Obsolete
const short ovArchStyleModel_OBSOLETE					= 1220; // Obsolete
const short ovArchStyleManufacturer_OBSOLETE			= 1221; // Obsolete
const short ovArchStyleURL_OBSOLETE						= 1222; // Obsolete
const short ovArchStyleIsCurtainWall					= 1378; // Boolean		read/write - Whether or not the wall is a curtain wall (Wall Style only) - Public for VS
const short ovArchStyleCurtainWallCutPlane				= 1379; // WorldCoord	read/write - The curtain wall cut plane (insertion option) (Wall Style only) - Public for VS
const short ovArchStyleUseClassDropShadow_OBSOLETE		= 1380; // Obsolete
const short ovArchStyleBelowCutPlaneClass				= 1381; // RefNumber	read/write - The ref number of the below cut plane class (Wall Style only) - Public for VS

const short ovParametricDirtyIndicator			= 1223; // Boolean		read/write - Show/Hide the dirty indicator for parametric handle

const short ovTileFitToWalls					= 1224; // Boolean		read/write - the fit to walls state of the tile - Public for VS	

//RenderWorks Styles Constants.  Starting at 1253

const short ovRenderStyleMode					= 1253; //Short 15 Custom, 17 Artistic
const short ovRenderStyleBackground				= 1254; //Handle
const short ovRenderStyleEnableAntiAliasing		= 1255; //Boolean
const short ovRenderStyleEnableShadows			= 1256; //Boolean
const short ovRenderStyleEnableBlurriness		= 1257; //Boolean
const short ovRenderStyleEnableTextures			= 1258; //Boolean
const short ovRenderStyleEnableColors			= 1259; //Boolean
const short ovRenderStyleImageExposure			= 1260; //Short

const short ovRenderStyleQualityGeometry		= 1261; //Short
const short ovRenderStyleQualityAntiAliasing	= 1262; //Short
const short ovRenderStyleQualityIndirectLighting = 1263; //Short
const short ovRenderStyleQualitySoftShadows		= 1264; //Short
const short ovRenderStyleQualityBlurriness		= 1265; //Short
const short ovRenderStyleQualityEnvLighting		= 1266; //Short
const short ovRenderStyleMaxReflections			= 1267; //Short
const short ovRenderStyleApplyLighting			= 1268; //Boolean
const short ovRenderStyleIndirectLighting		= 1269; //Long
const short ovRenderStyleHDRIRefNumber			= 1270; //Long
const short ovRenderStyleHDRIOption				= 1271; //Long
const short ovRenderStyleHasHDRIOption			= 1272; //Boolean
const short ovRenderStyleEnableAmbient			= 1273; //Boolean
const short ovRenderStyleAmbientBrightness		= 1274; //Real
const short ovRenderStyleAmbientColorR			= 1275; //Real
const short ovRenderStyleAmbientColorG			= 1276; //Real
const short ovRenderStyleAmbientColorB			= 1277; //Real
const short ovRenderStyleEmitterBrightness		= 1278; //Long
const short ovRenderStyleWhiteColorTemp			= 1279; //Long
const short ovRenderStyleApplyBackground		= 1280; //Boolean

const short ovRenderStyle						= 1281; //Handle
const short ovRenderStyleArtShader				= 1282; //Handle
const short ovArtShaderImage					= 1283; //Handle

const short ovProxyParentObject					= 1284; //Handle	read only - get a parametric's proxy parent

// Pen Space selectors
// ----------------
const short ovPenLocalMapping					= 1285;		// Boolean	- Not for public use
const short ovPenFlipHoriz						= 1286;		// Boolean	- the horizontal flip-state for a line type pen - Not for public use
const short ovPenFlipVert						= 1287;		// Boolean	- the vertical flip-state for a line type pen - Not for public use
const short ovPenScale							= 1288;		// real		 - the scale for a line type - Not for public use.

const short ovLineTypeIsSimple					= 1295;		// Boolean - Read only, return TRUE if the line type resource is a simple line type

const short ovRWImageBackgroundOffset			= 1300;		// WorldPt	Offset for RW image backgrounds (CameraMatch)

const short ovRenderStyleApplyEdges				= 1301;		// Boolean
const short ovRenderStyleAmbientOcclusionOn		= 1302;		// Boolean
const short ovRenderStyleAmbientOcclusionStrength	= 1303;		// real
const short ovRenderStyleAmbientOcclusionSize	= 1304;		// real


// Text link object (linkNode == 58 : Links text in symbol to field in record format.)
// ----------------
const short ovLinkFormatUsed					= 1350;		// InternalIndex	- the RefNumber of the format this links to
const short ovLinkFieldIndex					= 1351;		// short			- the index of the field of the format used

// Text Style Resources, For Public Use
const short ovTextStyleFontIndex				= 1360;		// short			- the index of the font in the text style resource
const short ovTextStyleSize						= 1361;		// double			- the size of the text in the text style resource
const short ovTextStyleLeading					= 1362;		// double			- the text leading in the text style resource, this is the vertical spacing when custom is used
const short ovTextStyleVertSpacing				= 1363;		// Uint8			- the vertical spacing of the text style resource, 1 = single, 2 = three halves, 2 = double, 4 = custom
const short ovTextStyleStyle					= 1364;		// Uint8			- the style of a text style resource (bold, italic, underline, etc), see TStyle above
const short ovTextStyleHorizAlignment			= 1365;		// Uint8			- the horizontal alignment in the text style resource
const short ovTextStyleVertAlignment			= 1366;		// Uint8			- the vertical alignment in the text style resource
const short ovTextStyleTextColor				= 1367;		// short			- the color of the text in the text style resource
const short ovTextStyleBackgroundColor			= 1368;		// short			- the color of the background in the text style resource
const short ovTextStyleNoBackgroundColor		= 1369;		// Boolean			- turns off the fill of the text in the text style resource

const short ovClearVGMCache						= 1375;		// short			- clears the object cache 0:clearAll,; 1:MoveOnly; 5:VisibilityOnly

const short ovMeshSmoothKind						= 1376;		// short			- Set/Get mesh smoothing kind(none, use_document, custom_angle, import).
const short ovMeshSmoothAngle						= 1377;		// double			- Set/Get (only) custom mesh smoothing angle.

//Master Snap point
const short ovMasterSnapPoint						= 1400;
const short ovShowMasterSnapOutsideSnapbox			= 1401;
const short ovMasterSnapPoint3D						= 1402;
const short ovShowMasterSnapOutsideSnapbox3D		= 1403;

const short ovTextureColorShaderImported			= 1450;
const short ovTextureReflectivityShaderImported		= 1451;
const short ovTextureTransparencyShaderImported		= 1452;
const short ovTextureBumpShaderImported				= 1453;

const short ovImageDefNodeTag						= 1554;	// Uint8		- access the tag number of an kImageDefNode (119)


//////////////////////////////////////////////////////////////////////////////////////////
// GetDimensionStandardVariable and SetCustomDimensionStandardVariable selectors
//
//		These selectors let you get properties of
//		specific dimension standards.  They have the return/passed
//		type as a comment following the selector

const short dimStdWitGap		  =  1;	  // (double_gs)	the gap between the witness line and the object being dimensioned (-2.0 to 2.0 page inches)
const short dimStdWitExtend		  =  2;	  // (double_gs)	the length that the witness line extends above the dimension line (-2.0 to 2.0 page inches)
const short dimStdMinALength	  =  3;	  // (double_gs)	the minimum length of the dimension arrow lines when they are inside (between the witness lines) (-2.0 to 2.0 page inches)
const short dimStdExtALength	  =  4;   // (double_gs)	the length of the dimension arrow lines when they are outside (not between the witness lines) (-2.0 to 2.0 page inches)
const short dimStdStackGap		  =  5;	  // (double_gs)	the distance between dimension lines for stacked (base-line) dimensions (-2.0 to 2.0 page inches)
const short dimStdAboveGap		  =  6;   // (double_gs)	the distance that the text sits above the dimension line (-2.0 to 2.0 page inches)
const short dimStdLeaderLength	  =  7;   // (double_gs)	the length of the leader line for radial and diametral dimensions (-2.0 to 2.0 page inches)
const short dimStdOverHang		  =	 8;   // (double_gs)	the amount that the dimension line extends beyond the witness lines (-2.0 to 2.0 page inches)
const short dimStdMarkLength	  =	 9;   // (double_gs)	the length of one spoke of the center cross for centermarks (-2.0 to 2.0 page inches)
const short dimStdExtendLength	  = 10;   // (double_gs)	the amount that the extension line extends beyond the circle for centermarks (-2.0 to 2.0 page inches)
const short dimStdMarkGap		  =	11;	  // (double_gs)	the gap between the center cross and the extension lines for centermarks (-2.0 to 2.0 page inches)
const short dimStdAlignDimText	  = 12;   // (UInt8)		the text alignment for linear dimensions (0: horiz, 1: horiz/vert, 2: aligned)
const short dimStdAlignInsideRad  = 13;   // (UInt8)		the text alignment for interior radial dimensions (0: horiz, 1: horiz/vert, 2: aligned)
const short dimStdAlignAngText	  = 14;   // (UInt8)		the text alignment for angular dimensions (0: horiz, 1: horiz/vert, 2: aligned)
const short dimStdOptions		  =	15;   // (UInt8)		a set of 5 bit flags: (128: witness lines, 64: text left, 32: dim in/out, 16: SIA format, 8: arrows inside only) 	
const short dimStdLinearArrowType = 16;	  // (UInt8)		the type of the linear dimension arrowheads (see MarkerStyleType)
const short dimStdAlignRadText	  = 17;   // (UInt8)		the text alignment for exterior radial dimensions (0: horiz, 1: horiz/vert, 2: aligned)
const short dimStdSlashThickness  = 18;	  // (UInt8)		the thickness of the dimension slash tick marks in mils
const short dimStdRadArrowType	  = 19;   // (UInt8)		the type of the radial dimension arrowheads
const short dimStdAngArrowType	  = 20;   // (UInt8)		the type of the angular dimension arrowheads
const short dimStdWitnessFixed	  = 21;   // (UInt8)		the state of the fixed witness line flag (0: off, 1: on)
const short dimStdLinearASize	  =	22;	  // (Sint16)		the size of the linear dimension arrowheads
const short dimStdRadASize		  =	23;	  // (Sint16)		the size of the radial dimension arrowheads
const short dimStdAngASize		  =	24;	  // (Sint16)		the size of the angular dimension arrowheads
const short dimStdstandardName	  = 25;   // (Str255)		the name of the dimension standard
const short dimStdTolSizeFac	  =	26;   // (UInt8)		the size of the tolerance text (as a percentage of the dimension text)
const short dimStdLinearAAngle	  = 27;	  // (UInt8)		the angle of the linear dimension arrowheads
const short dimStdRadAAngle		  =	28;	  // (UInt8)		the angle of the radial dimension arrowheads
const short dimStdAngAAngle		  =	29;	  // (UInt8)		the angle of the angular dimension arrowheads
const short dimStdDualUnitsInd	  = 30;   // (Sint16)		the dual units indicator (1: single, 2: side-by-side, 3: stacked)
const short dimStdFixedWitLength  = 31;   // (double_gs)	the length ofthe fixed witness lines (-2.0 to 2.0 page inches)
const short dimStdDialUnitsView   = 32;	  // (UInt8)		the dual units view selector: kDualViewPrimaryOnly(1):primary only, kDualViewSecondaryOnly(2):secondary only, kDualViewBoth(0): both
const short dimStdLinearArrowVis  = 33;   // (UInt8)		visibility of the linear dimension arrowheads
const short dimStdRadArrowVis     = 34;   // (UInt8)		visibility of the radial dimension arrowheads
const short dimStdAngArrowVis     = 35;   // (UInt8)		visibility of the angular dimension arrowheads
const short dimStdLinearAWidth	  = 36;	  // (Sint16)		the width of the linear dimension arrowheads (zero value also allowed)
const short dimStdRadAWidth		  = 37;	  // (Sint16)		the width of the radial dimension arrowheads (zero value also allowed)
const short dimStdAngAWidth		  = 38;	  // (Sint16)		the width of the angular dimension arrowheads (zero value also allowed)
const short dimStdLArrThickBasis  = 39;	  // (Sint8)		linear marker thickness basis dimLinearMarkerThicknessBasis - values are MarkerThicknessBasis type
const short dimStdAArrThickBasis  = 40;	  // (Sint8)		angular marker thickness basis dimOtherMarkerThicknessBasis - values are MarkerThicknessBasis type
const short dimStdRArrThickBasis  = 41;	  // (Sint8)		radial marker thickness basis dimOtherMarkerThicknessBasis - values are MarkerThicknessBasis type
const short dimStdLArrThickness   = 42;	  // (UInt8)		linear marker thickness value dimLinearMarkerThickness
const short dimStdAArrThickness   = 43;	  // (UInt8)		angular marker thickness value dimOtherMarkerThickness
const short dimStdRArrThickness   = 44;	  // (UInt8)		radial marker thickness value dimOtherMarkerThickness
const short dimStdLeadArrowType	  = 45;	  // (UInt8)		the type of the leader line arrowheads
const short dimStdLeadArrowSize   = 46;	  // (Sint16)		the size of the leader line arrowheads
const short dimStdLeadArrowAngle  = 47;	  // (UInt8)		the angle of the leader line arrowheads
const short dimStdLeadArrowThickBase = 48;// (Sint8)		leader line marker thickness basis - values are MarkerThicknessBasis type
const short dimStdLeadArrowThick  = 49;   // (UInt8)		leader line marker thickness value
const short dimStdLeadArrowWidth  = 50;   // (Sint16)       the width of the leader line arrowheads (zero value also allowed)
const short dimStdTextStyle		  = 51;	  // (Sint32)		the ref number of the text style that the dimension standard is linked to
const short dimStdTextPos		  = 52;	  // (UInt8)		the text position option (0: above/left, 1: above/right, 2: outside)
												


//////////////////////////////////////////////////////////////////////////////////////////
// GetApplicationResFile selectors
//

const short kTopmostApplicationResFile	= 1;	// pass this to get the resource file topmost in the chain. If you use the
												// normal resource search progression with this constant, you will always
												// find any resource in the core application. Otherwise, you can use a more
												// specific selector below.
const short kMainAppResFile				= 2;
const short kVWResourcesResFile			= 3;
const short kVWHelpResFile				= 4;
const short kVWLocaleResFile			= 5;





//////////////////////////////////////////////////////////////////////////////////////////
// Intersection types

struct Sect2Struct {
	WorldPt		int1;
	Boolean			legal1;		/* Is int1 a real intersection */
	WorldPt		int2;
	Boolean			legal2;		/* Is int2 a real intersection */
};

struct Sect4Struct {
	WorldPt		int1;
	Boolean			legal1;		/* Is int1 a real intersection */
	WorldPt		int2;
	Boolean			legal2;		/* Is int2 a real intersection */
	WorldPt		int3;
	Boolean			legal3;		/* Is int3 a real intersection */
	WorldPt		int4;
	Boolean			legal4;		/* Is int4 a real intersection */
};


//////////////////////////////////////////////////////////////////////////////////////////
// CustomObject (Parametric) callback argument constants
// Renamed the "parametric" constants with "customobject". JAK 5/4/98

const Sint8 kCustomObjectPrefNever 		= 0;
const Sint8 kCustomObjectPrefAlways 	= 1;
const Sint8 kCustomObjectPrefNew 		= 2;


//////////////////////////////////////////////////////////////////////////////////////////
// LightType constants

enum {
	// Light kind
	kDirectionalLight = 0,
	kPointLight,
	kSpotLight,
	
	// Distance and angular falloff
	kLightNoFalloff	= 0,

	// Distance falloff
	kLightInverseDistance = 1,
	kLightInverseDistanceSquared,

	// Angular falloff
	kLightLinear = 1,
	kLightExponential,
	kLightCosine
};

// Constants for standard views
typedef short TStandardView;
const short standardViewUserDefined			= 0;
const short standardViewFront				= 3;
const short standardViewBack				= 4;
const short standardViewLeft				= 5;
const short standardViewRight				= 6;
const short standardViewTop 				= 7;
const short standardViewBottom				= 8;
const short standardViewRightIso			= 9;
const short standardViewLeftIso 			= 10;
const short standardViewRightRearIso		= 11;
const short standardViewLeftRearIso 		= 12;
const short standardViewBottomRightIso		= 13;
const short standardViewBottomLeftIso		= 14;
const short standardViewBottomRightRearIso	= 15;
const short standardViewBottomLeftRearIso	= 16;

enum class EImageViewComponent : uint8_t {
	StandardView3D = 0,
	StandartView2D = 1,
	CutView2D = 2,
	NotSet = 4
};

//////////////////////////////////////////////////////////////////////////////////////////
// projection types (from XGraf3d.h)
typedef short TProjection;
const short projectionOrthogonal		= 0;
const short projectionPerspective 		= 1;
const short projectionCavalierOblique45	= 2;	// parallel oblique projection at angle
const short projectionCavalierOblique30	= 3;	// parallel oblique projection at angle
const short projectionCabinetOblique45	= 4;	// parallel oblique projection at angle
const short projectionCabinetOblique30	= 5;	// parallel oblique projection at angle
const short projectionPlan				= 6;



//////////////////////////////////////////////////////////////////////////////////////////
//Render Constants (from MObject.h)
typedef short TRenderMode;
const short renderWireFrame 			= 0;
const short renderQuick 				= 1;
const short renderSolid 				= 2;
const short renderShadedSolid			= 3;
const short renderShadedNoLines			= 4;
const short renderFinalShaded 			= 5;
const short renderFinalHiddenLine		= 6;
const short renderDashedHiddenLine		= 7;
const short render2DSection				= 8;
const short render3DSection				= 9;
const short renderOpenGL				= 11;
const short renderFastRenderWorks		= 12;
const short renderFastShadowRenderWorks = 13;
const short renderFinalRenderWorks		= 14;
const short renderCustomRenderWorks		= 15;
const short renderOutputVRML			= 16;
const short renderArtisticRenderWorks 	= 17;
const short renderSketch				= 18;

//////////////////////////////////////////////////////////////////////////////////////////

struct SymbolImgInfo
{
	Sint32			fWidth;
	Sint32			fHeight;
	Sint32			fMargin;
	TStandardView	fStandardView;
	TRenderMode		fRenderMode;
	EImageViewComponent			fImgComponent;
	bool			fScaleByZoom;

	SymbolImgInfo(Sint32	width, Sint32 height, Sint32 margin, TStandardView	view, TRenderMode renderMode, EImageViewComponent imgComponent, bool scaleByZoom)
		:fWidth(width), fHeight(height), fMargin(margin), fStandardView(view), fRenderMode(renderMode), fImgComponent(imgComponent), fScaleByZoom(scaleByZoom) {};
	SymbolImgInfo(TStandardView	view, TRenderMode renderMode, EImageViewComponent imgComponent, bool scaleByZoom) : SymbolImgInfo(-1, -1, -1, view, renderMode, imgComponent, scaleByZoom) {};
	SymbolImgInfo() : SymbolImgInfo(-1, -1, -1, 2/*TopPlan*/, 0/*Wireframe*/, EImageViewComponent::StandartView2D, false /*sizing is done by layer scale*/) {};
};

enum class EDateTimeFormat
{
	MDY							= 1,
	MDY_H_MM					= 2,
	DMY							= 3,
	DMY_H_MM					= 4,
	YMD							= 5,
	YMD_H_MM					= 6,
	D_MMM_Y						= 7,
	D_MMM						= 8,
	MMM_Y						= 9,
	H_MM						= 10,
	H_MM_S						= 11,
	H_MM_AM_PM					= 12,
	H_MM_S_AM_PM				= 13,
	MDY_H_MM_S_AM_PM			= 14,
	DAYOFWEEK_MONTH_D_Y			= 15,
	DAYOFWEEK_MONTH_D_Y_TIME	= 16,	// TIME is the full h_mm_s_AM_PM
	DOW_MMM_D_Y					= 17,
	DOW_MMM_D_Y_TIME			= 18,	// TIME is the full h_mm_s_AM_PM
	DAYOFWEEK_D_MONTH_Y			= 19,	// the following are new for VW 11.5.1, fix regression in VS client
	DAYOFWEEK_D_MONTH_Y_TIME	= 20,
	DOW_D_MMM_Y					= 21,
	DOW_D_MMM_Y_TIME			= 22,
	DMY_TIME					= 23,
	DAYOFWEEK_Y_MONTH_D			= 24,
	DAYOFWEEK_Y_MONTH_D_TIME	= 25,
	DOW_Y_MMM_D					= 26,
	DOW_Y_MMM_D_TIME			= 27,
	YMD_TIME					= 28,
	YYYYMMDD					= 29,	//year month day format for .DBF dates
	MMDDYYYY					= 30,	//month day full year format for file creation date
	YYYY_MM_DD					= 31,	// year month day format for ifcdate
    TIMESTAMP                   = 32,   //yyyymmddhhmmss
	DDMMYY						= 33,
	DDMMYY_TIME					= 34,
	DDMMYYYY					= 35,
	DDMMYYYY_TIME				= 36
};

//////////////////////////////////////////////////////////////////////////////////////////
enum EDateFormat
{
	eFullDate,
	eAbbreviatedDate,
	eShortDate
};

//////////////////////////////////////////////////////////////////////////////////////////
enum EInfoFormat
{
	eDateOnly,
	eDateAndTime,
	eTimeOnly
};

//////////////////////////////////////////////////////////////////////////////////////////
struct TDateTimeIntlData
{
	TXString		fDateSeparator;			// In US this is slash "/" for short date format
	TXString		fTimeSeparator;			// In US this is colon ":" for time format
    bool            f24HourFormat;          // false = AM/PM 12-hour format, true = 24-hour format
	TXString		fMorningStr;
	TXString		fEveningStr;
	TXStringArray	fMonths;
	TXStringArray	fMonthAbbreviations;
	Sint16			fShortDateOrder;
	Sint16			fLongDateOrder;
	TXStringArray	fDaysOfWeek;				
	TXStringArray	fDaysOfWeekAbbreviations;	
	TXString		fDaysOfWeekSeparator;	// In US this is comma and space ", " following day of week
	TXString		fDateYearSeparator;		// In US this is comma and space ", " between date and year
	TXString        fDateMonthSeparator;
};

#ifndef _MINICAD_

//////////////////////////////////////////////////////////////////////////////////////////
// sym def types

const short k2DSym				= 0;
const short k3DSym				= 1;
const short kHybridSym			= 2;

#endif // _MINICAD_


//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
struct CustomBarFieldInfo
//
//	CustomBarFieldInfo is used for the Custom Editable DataBar APIs
//	
//		GS_CustomBarGetFieldInfo and GS_CustomBarSetFieldInfo
{	
	CustomBarFieldInfo() :
		fIsEditable(false),
		fIsLocked(false)
	{}
	
	TXString 	fFieldLabel;
	TXString 	fFieldValue;
	Boolean		fIsEditable;
	Boolean		fIsLocked;
};

const Sint32 kDataBarCursorVisStateUndefined			= -1;
const Sint32 kDataBarCursorVisStatePrimary				= 0;
const Sint32 kDataBarCursorVisStatePrimaryAndSecondary	= 1;
const Sint32 kDataBarCursorVisStateAll					= 2;


//////////////////////////////////////////////////////////////////////////////////////////
// Host information about which program is currently running

#ifndef GSEBUILDTYPES
#define GSEBUILDTYPES
const short kMiniCad 			= 1;
const short kBlueprint 			= 2;
#endif


//////////////////////////////////////////////////////////////////////////////////////////



#define GS_COMPATIBILITY
#define GS_LIBRARY


//////////////////////////////////////////////////////////////////////////////////////////

extern "C" {
	typedef Boolean (*GS_ForEachBreakProcPtr)(MCObjectHandle h, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData, CallBackPtr cbp, void* env);
	typedef void (*GS_I2DDrawProcPtr)(const WorldPt& startPt, const WorldPt& drawPt, CallBackPtr cbp, void *env);
	typedef void (*GS_ForEachObjectProcPtr)(MCObjectHandle h, CallBackPtr cbp, void *env);
	typedef bool (*GS_3DPointIteratorProcPtr)(WorldPt3 point3D, CallBackPtr cbp, void* env);	// XXX_JDW_MISC - i think bool is illegal in SDK, and also unused in these functions
	typedef void (*GS_ForEachPolyEdgeProcPtr)(const WorldPt& inStartPt, const WorldPt& inControlPt, const WorldPt& inEndPt, WorldCoord inRadius, VertexType inType, CBBoolean inVisible, CallBackPtr inCBP, void* inEnv);
	typedef void (*GS_PersistentDrawProcPtr)(CallBackPtr cbp, void *env); 
	
	typedef void (*GS_CustomObjectControlPtsInitProcPtr)(CallBackPtr cbp, Sint32 inIndex, WorldPt3& outPt, Boolean& outIs2DOnly, Boolean& outIsHidden, short& outClientID, void* env);	
	
	
	//	Under construction
	typedef void (*PushPullHandleCompletionRoutinePtr)(const WorldCoord& inPushPullDistance, void* inUserData);
	


// XXX_JDW_ALTURA CLEANUP cross platform SDK based file identifier for
// ForEachFileProcPtr - we have a mix of Boolean, OSErr, and GSError
// This was Boolean but seems to need to be OSErr...
// JDW  [2003-01-12] - added  && !_GSWINSDK_ to build GSWinSDK	
// JDW  [2003-05-12] - changing all to EForEachFileResult enum to get rid of wackyness
// JDW  [2005-01-19] - changed order to have true/false correspond to stop/continue (as before with Boolean results)
//						and restored the Boolean versions of the proc ptrs and callbacks in compatibility mode in 
//						case existing 3rd party SDK code hasn't been updated.  This may or may not make one or more people happy.

#ifndef EForEachFileResult_DEFINED
#define EForEachFileResult_DEFINED
enum EForEachFileResult 
// THIS IS ALSO DEFINED IN APPLICATIONFOLDERS.H - keep in sync
{
	kContinueForEachFile		= 0,	// Keep traversing - Returned by callback to tell ForEachFile to keep going
	kStopForEachFile_NoError	= 1,	// Stop traversal for non-error reason - This is the normal return value when you are only looking for one file
	kStopForEachFile_Error		= 2,	// Abnormal abort of traversal due to some error
	kFolderNotFoundError		= 3,	// You may get this if you pass in invalid folder info
	kOSFinishedTraversingSubDir	= 4,	// No more files available - This is the normal successful return value for ForEachFile

	kDummyForceEnumToBeLong		= 0xFFFFFFFF
};
#endif

#if !_WIN_EXTERNAL_ && !_GSWINSDK_
	#if GS_SDK_VW11_COMPATIBLE
	typedef Boolean			   (*GS_ForEachFileProcPtr )(Sint32 vRefNum, Sint32 dirID, StringPtr fileName, OSType fileType, CallBackPtr cbp, void* env);
	#endif
	typedef EForEachFileResult (*GS_ForEachFileNProcPtr)(Sint32 vRefNum, Sint32 dirID, StringPtr fileName, OSType fileType, CallBackPtr cbp, void* env);
	typedef Boolean			   (*GS_ForEachFilePathProcPtr )(const char* fullPath, const char* fileName, const char* fileExtension, CallBackPtr cbp, void* env);
#endif

	#if GS_SDK_VW11_COMPATIBLE
	typedef Boolean			   (*GS_ForEachFilePathProcPtr )(const char* fullPath, const char* fileName, const char* fileExtension, CallBackPtr cbp, void* env);
	#endif
	typedef EForEachFileResult (*GS_ForEachFilePathNProcPtr)(const char* fullPath, const char* fileName, const char* fileExtension, CallBackPtr cbp, void* env);



	//------------------------------------------------------------------------------------
	// Kludge so 
	
	const CBSignedShort kKludgeHandleIncomingFilePath = 3650;
	struct TKludgeHandleIncomingFilePath {
		Boolean		fForWrite;
		TXString	fPath;
		Boolean		fHadError;
	};


	// 
	// --------------------------------------------------------
	// kludge used for the addsurface function in plant object
	// --------------------------------------------------------
	//    

	const CBSignedShort kAddSurfaceKludge = 5555;
	struct AddSurfaceInformation {
		MCObjectHandle h1;
		MCObjectHandle h2;
		MCObjectHandle result;
	};

	//
	// --------------------------------------------------------
	// kludge used for the entering 2d and 3d groups
	// in the plant object editing
	// --------------------------------------------------------
	//

	const CBSignedShort kEnterGroups = 5556;

	//
	// --------------------------------------------------------
	// kludge used for initializing and setting the
	// hidden plant record
	// --------------------------------------------------------
	//

	const CBSignedShort kSetAndGetHiddenPlantRecord = 5557;
	struct SetAndGetHiddenPlantRecord{
		Boolean isDoubleClick;
		Boolean isSetting;
		Boolean result;
	};

	//
	// --------------------------------------------------------
	// kludge used when creating the default
	// plant record
	// --------------------------------------------------------
	//

	const CBSignedShort kCreatePlantRecord = 5558;

	//
	// --------------------------------------------------------
	// kludge used from the plugin to tell if object is 
	// a plant object or not
	// --------------------------------------------------------
	//

	const CBSignedShort kIsPlantObject = 5559;
	struct isPlantObject{
		MCObjectHandle objectInQuestion;
		Boolean isPlantOrNot;
	};

	//
	// --------------------------------------------------------
	// kludge used from the plant plugin to rename a plant
	// resource if the user edits the plant ID in the 
	// definition of the plant
	// --------------------------------------------------------
	//

	const CBSignedShort kIsEditingPlantID = 5560;
	struct isEditingPlantID{
		TXString oldName;
		TXString newName;
	};

	// 
	// --------------------------------------------------------
	// kludge used from the plant plugin to change the view
	// to specific angles for the 3d scaling portion of the
	// plant object
	// --------------------------------------------------------
	//

	const CBSignedShort kChange3DViewForPlant = 5561;

	// 
	// --------------------------------------------------------
	// kludge used to set the height/width of the image prop
	// from inside the plant object
	// --------------------------------------------------------
	//

	const CBSignedShort kSetImagePropStuff = 5562;
	struct isSettingImagePropStuff{
		MCObjectHandle imageProp;
		double spread;
		double height;
	};

	//
	// --------------------------------------------------------
	// kludge used to set the tool in reshape mode from the
	// plant special edit dialog
	// --------------------------------------------------------
	//

	const CBSignedShort kEditPlantPath = 5563;

	//
	// --------------------------------------------------------
	// kludge used for setting the symbol type of the plant
	// --------------------------------------------------------
	//

	const CBSignedShort kSetPlantSymbolType = 5564;
	struct plantSymbolTypeStuff{
		MCObjectHandle plant;
		short symbolType;
	};

	//
	// --------------------------------------------------------
	// kludge used for setting timestamp of plant symbols
	// --------------------------------------------------------
	//

	const CBSignedShort kSetPlantSymbolTimeStamp = 5565;

	//
	// --------------------------------------------------------
	// kludge used for refreshing the resource browser
	// --------------------------------------------------------
	// 

	const CBSignedShort kRefreshResourceBrowser = 5566;

	// 
	// --------------------------------------------------------
	// kludge used for the plant object when creating a new
	// image prop for the 3d symbol portion of a plant
	// --------------------------------------------------------
	//    

	const CBSignedShort kCreatePlantImageProp = 5567;
	struct PlantImagePropStuff {
		TXString imagePropName;
		InternalIndex textureRef;
		double spread;
		double height;
		MCObjectHandle imagePropHandle;
	};

	//
	// --------------------------------------------------------
	// kludge used when verifying/fixing the plant price
	// display style in the plant record
	// --------------------------------------------------------
	// 

	const CBSignedShort kUpdatePriceInPlantRecord = 5568;

	//
	// --------------------------------------------------------
	// kludge used when the dtm modifier record has to be 
	// attached to a poly so that the landscape area can 
	// be a texture bed on the dtm
	// --------------------------------------------------------
	//

	const CBSignedShort kCreateDTMModifierRecord = 5569;
	const Sint32 kDTMModifierRecordStringIndex		= 259;
	const Sint32 kDTMModifierRecord_recordName		= 1;
	const Sint32 kDTMModifierRecord_type			= 2;
	const Sint32 kDTMModifierRecord_deltaz			= 3;
	const Sint32 kDTMModifierRecord_riseOverRun	= 4;
	const Sint32 kDTMModifierRecord_className		= 5;
	const Sint32 kDTMModifierRecord_errMessage		= 6;
	const Sint32 kDTMModifierRecord_value1			= 7;
	const Sint32 kDTMModifierRecord_value2			= 8;

	//
	// --------------------------------------------------------
	// kludge used for correcting Plant Definition,
	// if the parametric object's name is wrong.
	// --------------------------------------------------------
	// 

	const CBSignedShort kCorrectPlantDefinition = 5574;

	// 
	// --------------------------------------------------------
	// kludge that checks for a "New" or "Window" menu command
	// inside the plant tool
	// --------------------------------------------------------
	//

	const CBSignedShort kCheckMenuForPlantTool = 5575;

	//
	// --------------------------------------------------------
	// kludge that sets it so the image popup in the plant tool
	// will unpopup when there is a resource conflict when
	// importing from default content
	// --------------------------------------------------------
	//

	const CBSignedShort kSetUnpopupValueForPlantTool = 5576;

	// 
	// --------------------------------------------------------
	// kludge used to get the unpopup global variable
	// for the plant tool image popup issue
	// --------------------------------------------------------
	//

	const CBSignedShort kGetUnpopupValueForPlantTool = 5577;

	//
	// --------------------------------------------------------
	// kludge used to transfer attributes from one dimension
	// to another dimension
	// --------------------------------------------------------
	
	const CBSignedShort kCopyDimensions	= 5578;
	struct CopyDimensionStuff {
		MCObjectHandle dimFrom;
		MCObjectHandle dimTo;
	};
	
	//
	// --------------------------------------------------------
	
	// kludge used to get the width of the selection box
	// in the world coord values
	// --------------------------------------------------------
	//

	const CBSignedShort kGetSelectionBoxSize = 5579;

	//
	// --------------------------------------------------------
	// kludge used to remove all the "all by class" flags
	// --------------------------------------------------------
	//

	const CBSignedShort kClearAllByClassFlags = 5570;

    const CBSignedShort kIntersectSurfaceKludge = 5571;
	struct IntersectSurfaceInformation {
		MCObjectHandle h1;
		MCObjectHandle h2;
		MCObjectHandle result;
	};

 	//
	// --------------------------------------------------------
	// kludge used to raise a notitifcation
	// --------------------------------------------------------
	//
    const CBSignedShort kKludgeNotifyAny = 5573;
    struct NotifyAnyStuff {
        NotifyAnyStuff(StatusID selector) { notifySelector = selector;  additionalData = 0;}
        StatusID notifySelector;
        StatusData additionalData;
    };

	//
	// --------------------------------------------------------
	// kludge used to draw a gray dashed 2D line
	// --------------------------------------------------------
	//

	const CBSignedShort kKludgeDrawGrayDashed2DLine = 4007;
	struct DrawGrayDashed2DLineStuff  {
		WorldPt pt1;
		WorldPt pt2;
	};

	const CBSignedShort kKludgeCalcWitLineEndPts = 4008;
	struct CalcWitLineEndPtsStuff  {
		MCObjectHandle dimH;
		WorldPt startWitEndPt;
		WorldPt endWitEndPt;
	};

	//
	// -------------------------------------------------------
	// kludge used to make a temporary graphical copy, this is for internal use only
	//--------------------------------------------------------
	//

	const CBSignedShort kKludgeMakeTempGraphicalCopy = 4010;
	struct MakeTempGraphicalCopyInformation {
		MCObjectHandle handleToCopy;
		MCObjectHandle result;
	};

	//
	//---------------------------------------------------------
	// kludge used to get and set the frac mat of a parametric object, this is for internal use only
	//---------------------------------------------------------
	//

	const CBSignedShort kKludgeGetAndSetParametricFracMat = 4011;
	struct GetAndSetParametricFracMatInfo  {
		Boolean getFracMat;
		MCObjectHandle paramH;
		TransformMatrix paramFracMat;
	};
	

	//
	//---------------------------------------------------------
	// kludge used to get a line type resource from and old dash style index, this is for internal use only
	//  These were:
	//		kKludgeGetLineTypeFromDashIndex = 4012
	//		kKludgeGetDashStyleIndexFromLineType = 4013
	//	These have been removed as part of the line type re-engineering task, since there is no
	//	dash index anymore. The validation these provided (checking that the line type is a valid
	//	line type in the document and is a simple line type) is now available with SDK call IsDashLineStyle
	//---------------------------------------------------------
	//

	//
	//---------------------------------------------------------
	// kludge used to send key events, this is for internal use only
	//---------------------------------------------------------
	//

	const CBSignedShort kKludgeSendDataForKeyEvent = 4014;
	struct TDialogKeyDownEvent {
		Uint32 keyCode; // platform-specific virtual keycode
		Uint32 keyFlags;
		unsigned short activeControlID;
		unsigned short handledEvent; // 0: this event is forwarded to the OS (default), else the callback handled this event (don't forward)
		void * data; // platform-specific data sent along with the event
	};
	
	//
	//----------------------------------------------------------------------------------
	// kludge used to get the tight fill poly of text, this is used for CalloutTool plug-in
	// It also can be used for other text in object
	//---------------------------------------------------------------------------------
	//
	
	const CBSignedShort kKludgeGetTextTightFillPoly = 5604;
	struct STextPolyInfo 
	{
		MCObjectHandle	fHandle;
		bool			fIsMirrored;
		double			fTextAngle;
	};



	//
	//----------------------------------------------------------------------------------
	// This Kludge is used when you want to enter or exit in a group from the code. It is implemented
	// for Seating Section /Spotlight/ used, however it can be used from every project that needs such functionality
	//---------------------------------------------------------------------------------
	//
	const CBSignedShort kKludgeEnterAndExitFromGroup = 5614;
	struct SGroupEnterExit
	{
		enum class EAction
		{
			Enter,
			Exit
		};

		SGroupEnterExit(const EAction& action = EAction::Enter, 
						MCObjectHandle hGroup = nullptr, 
						bool suspendUndo = false, 
						bool showIndicators = true)
			: fAction(action)
			, fhGroup(hGroup)
			, fbSuspendUndo(suspendUndo)
			, fbShowEditGroupIndicators(showIndicators)
		{}

		EAction			fAction;
		MCObjectHandle	fhGroup;
		bool			fbSuspendUndo;
		bool			fbShowEditGroupIndicators;
	};

	//----------------------------------------------------------------------------------
	// Data for the Kludge call used for the Resource Library Catalog Builder dialog
	//----------------------------------------------------------------------------------
	const CBSignedShort kRunCatalogBuilderDialog = 5621;
	struct SLibraryTypeMenu
	{
		TXString defaultContent_menuitem;
		TXString vss_menuitem;
		TXString packLib_menuitem;
	};
	struct SCatalogBuilderDialogData
	{
		TXString title;
		TXString ok_label;
		TXString cancel_label;
		TXString root_label;
		TXString choose_button;
		TXString libtype_label;
		TXString root_chooserDlg_label;
		SLibraryTypeMenu libMenu;

		// these are direct acceess to the functionality in: int GenerateLibraryDatabase(const SCatalogBuilderDialogData& data)
		// these apply when title is Empty
		Sint16		fLibraryGroup;	// kVWLibraryGroupDefaultContent or kVWLibraryGroupVSSOnlineContent or kVWLibraryGroupVWLibrary
		TXString	fRootLibFolder;
	};

	//----------------------------------------------------------------------------------
	// This Kludge call is used to check whether Create Solid returned Failed Addition 
	//----------------------------------------------------------------------------------
	const CBSignedShort kKludgeIsFailedCSGAction = 5625;

	//-------------------------------------------------------------------------------------
	// kludge that checks if a string is Vectorworks reserved word
	//-------------------------------------------------------------------------------------

	const CBSignedShort kIsRefNameSystemReserved = 5626;

	//----------------------------------------------------------------------------------
	// kludge that inverts an image.
	//----------------------------------------------------------------------------------

	const CBSignedShort kInvertImage = 5631;

	//
	// -------------------------------------------------------
	// kludge used to highlight/ unhighlight a Callout leader line
	//--------------------------------------------------------
	//

	const CBSignedShort kKludgeActionHighlightingObject = 5632;

	struct ActionHighlightingObjectInformation {
		Boolean				bAddObject;
		MCObjectHandle		handleToObject;
	};
    
    //-------------------------------------------------------------------------------------
    // kludge that generates ImageDefNode for enlarged QR code
    //-------------------------------------------------------------------------------------
    
    const CBSignedShort kDrawEnlargedQRFromArray = 6021;
    
    struct QRCodeInfo {
        std::vector<int> fBitArray;
        int fSize;
    };
    
    
    //-------------------------------------------------------------------------------------
    // kludge that generates an image from the incoming QR code info and copy to clipboard
    //-------------------------------------------------------------------------------------
    
    const CBSignedShort kCopyQRImageToClipboard = 6022;

	//
	enum ConvertModeEnum { ConvertWireframeMode,ConvertHiddenMode,ConvertDashedMode };
	
	//------------------------------------------------------------------------------------
	#if _WINDOWS
	
	// These are fake callbacks.  They are implemented in the DLL not the EXE.

	void GS_CALLBACK GS_Mac2WinString(CallBackPtr cbp, const unsigned char *ps, char *sz, Sint32 max);
	// Convert from Mac Pascal string to Windows C-string.

	void GS_CALLBACK GS_Win2MacString(CallBackPtr cbp, const char *sz, unsigned char *ps, Sint32 max);
	// Convert from Windows C-string to Mac Pascal string.

	void GS_CALLBACK GS_AngleToCString(CallBackPtr cbp, double_param angle, char *sz, Sint32 max);
	void GS_CALLBACK GS_CoordToDimCString(CallBackPtr cbp, const WorldCoord &c, char *sz, Sint32 max);
	Boolean GS_CALLBACK GS_CStringToAngle(CallBackPtr cbp, const char *sz, double_gs &angle);
	Boolean GS_CALLBACK GS_DimCStringToCoord(CallBackPtr cbp, const char *sz, WorldCoord& c);

	#endif // _WINDOWS
}


//	NNA TaggedData contaner IDs:
//	NNA reserves all "lowercase" OSTypes.
//	The Tagged Data APIs are reserved at this point for internal NNA usage.
const OSType kTaggedDataContainerNNA_Internal1 = 'rwrs';
const OSType kTaggedDataContainerNNA_Internal2 = 'rwlo';
const OSType kTaggedDataContainerNNA_Internal3 = 'rwvs';
const OSType kTaggedDataContainerNNA_Internal4 = 'pxpm';
const OSType kTaggedDataContainerNNA_Internal5 = 'seli';
const OSType kTaggedDataContainerNNA_Internal6 = 'ptd_';
const OSType kTaggedDataContainerNNA_Internal7 = 'pdf_';
const OSType kTaggedDataContainerNNA_Internal8 = 'mshs';
const OSType kTaggedDataContainerNNA_Internal9 = 'vcs_';
const OSType kTaggedDataContainerNNA_Internal10 = 'dlvp';
const OSType kTaggedDataContainerNNA_Internal11 = 'stlo';
const OSType kTaggedDataContainerNNA_Internal12 = 'gdlt';
const OSType kTaggedDataContainerNNA_Internal13 = 'rwtt';
const OSType kTaggedDataContainerNNA_Internal14 = 'ptag';
const OSType kTaggedDataContainerNNA_Internal15 = 'sbnt';
const OSType kTaggedDataContainerNNA_Internal16 = 'rdnt';
const OSType kTaggedDataContainerNNA_Internal17 = 'iobj';
const OSType kTaggedDataContainerNNA_Internal18 = 'rwbl';
const OSType kTaggedDataContainerNNA_Internal19 = 'vpcm';
const OSType kTaggedDataContainerNNA_Internal20 = 'txst';
const OSType kTaggedDataContainerNNA_Internal21 = 'rwsa';
const OSType kTaggedDataContainerNNA_Internal22 = 'c4di';
const OSType kTaggedDataContainerNNA_Internal23 = 'ccst'; // clip cube state
const OSType kTaggedDataContainerNNA_Internal24 = 'rrco';
const OSType kTaggedDataContainerNNA_Internal25 = 'txim';
const OSType kTaggedDataContainerNNA_Internal26 = 'imbr'; // image brick data
const OSType kTaggedDataContainerNNA_Internal27 = 'disp'; // displacement mapping data
const OSType kTaggedDataContainerNNA_Internal28 = 'svi_'; // selected vertex index
const OSType kTaggedDataContainerNNA_Internal29 = 'pstq'; // parasolid tessellation quality
const OSType kTaggedDataContainerNNA_Internal30 = 'cmsh'; // closed mesh
const OSType kTaggedDataContainerNNA_Internal31 = 'scmd'; // Sub-division Control Mesh Data
const OSType kTaggedDataContainerNNA_Internal32 = 'rwov'; // indirect lighting (radiosity) overrides
const OSType kTaggedDataContainerNNA_Internal33 = 'rwpt'; // glass portal setting
const OSType kTaggedDataContainerNNA_Internal34 = 'pcps'; // Point cloud data
const OSType kTaggedDataContainerNNA_Internal35 = 'smmd'; // Subdivision Mirror Modeling Data
const OSType kTaggedDataContainerNNA_Internal36 = 'rwct'; // RW custom texture parts
const OSType kTaggedDataContainerNNA_Internal37 = 'rwce'; // C4D export options
const OSType kTaggedDataContainerNNA_Internal38 = 'rwib'; // RW image background offset
const OSType kTaggedDataContainerNNA_Internal39 = 'c4mi'; // Imported C4D textures
const OSType kTaggedDataContainerNNA_Internal40 = 'rwfb'; // FBX export options
const OSType kTaggedDataContainerNNA_Internal41 = 'rwcl'; // COLLADA export options
const OSType kTaggedDataContainerNNA_Internal42 = 'scav'; // Slab plugin component area and volume
const OSType kTaggedDataContainerNNA_Internal43 = 'sdfi'; // SDF image



//	TaggedData data type IDs used in GS_TagggedData## APIs:
const Sint32 kTaggedDataByteArrayTypeID = 1;		
const Sint32 kTaggedDataFlagsContainerTypeID = 2;	
const Sint32 kTaggedDataDoubleArrayTypeID = 6;		
const Sint32 kTaggedDataTramsformMatrixTypeID = 7;
const Sint32 kTaggedDataUint32ArrayTypeID = 8;	
const Sint32 kTaggedDataColorRefArrayTypeID = 13;	
const Sint32 kTaggedDataObjectRefArrayTypeID = 15;
const Sint32 kTaggedDataPlanarRefArrayTypeID = 17;
const Sint32 kTaggedDataTransformMatrixArrayTypeID = 18;
const Sint32 kTaggedDataWorldPt3ArrayTypeID = 20;
const Sint32 kTaggedDataFloatPt3ArrayTypeID = 21;
const Sint32 kTaggedDataWallComponentJoinElevationsArrayTypeID = 22;


const Sint32 kNNA_InternalTag1 = 1;	// Tag Used by NNA Plugin
const Sint32 kNNA_InternalTag2 = 2;	// Tag Used by NNA Plugin


//////////////////////////////////////////////////////////////////////////////////////////
// =======================================================================================
//	"Private" Callback information
//
//	The following definitions are only needed by "Private" callbacks, 
//	(called by those externals for which Diehl Graphsoft does not ship source code).
//	This information should be moved to some new private header file which we 
//	do not ship with SDK releases, but is available in house for our externals.
//	JAK 4/23/98

//	Define my own structure that is similar but not identical to the ones in Overlay.h.
//	I'm doing this for two reasons.  Attempting to use Overlay.h caused this not to 
//	compile in externals because MiniCadCallBacks is included in GCL files which have
//	different string achitecture, so the PStr31 below would not work.  Cannot successfully
//	include GSString.h here either.  Would have to cut-n-paste the TFlag stuff into here
//	for externals also which is ugly.
//	Also...by using the existing structs in Overlay.h I am unnecessarily tying my callback 
//	to that file. If it changes, it would break my callback and require a separate definition
//	so I might as well do it now.
//
//	We don't need binary compatibililty with the structures defined in Overlay.h, 
//	we only need similar data. 
//

//	enum MPEType {	kMPMenu = 0, 
//				kMPTool = 1, 
//				kMPParametricTool = 2,
//				kMPTextFile = 3 };
// JAK 4/26/99 Rename type and enum constants using appropriate terminology.
enum EVSPluginType	{	kVSPluginMenu	= 0, 
						kVSPluginTool	= 1, 
						kVSPluginObject	= 2,
						kVSTextFile 	= 3 };

// =======================================================================================
// ObjectState struct information data

//----------------------------------------------------------
struct ObjectStateData_Position
// StateData for position changes
// data reflect the offsets of the change
//	matrix contains offset of translation
//	matrix contains angle difference for rotation
{
	Boolean			fbIs3DMove;
	TransformMatrix	fTransformOffset;
};

//----------------------------------------------------------
struct ObjectStateData_ParamChanged
// StateData for parameter changes
//	data reflects the parameter index and old data of the format record parameter
{
	Sint32			fWidgetID;
	Sint32			fParameterIndex;
	Boolean			fParameterValidOldValue;
	TVariableBlock	fParameterOldValue;
};

//----------------------------------------------------------
struct ObjectStateData_ObjectChanged
// StateData for object changes
//	this is sent for attributes object change
{
	Sint32			fChangeID;
	SintptrT		fParameterID;
}; 

//----------------------------------------------------------
struct ObjectStateData_LayerChanged
// StateData for scale changes of the parent layer or viewport
{
	double			fdOldLayerScale;
	double			fdLayerScale;
	Boolean			fbScaleText;
	double			fdOldLayerElevation;
	double			fdLayerElevation;
	double			fdOldLayerHeight;
	double			fdLayerHeight;
	GSStr255		fOldLayerName;
	GSStr255		fLayerName;

					ObjectStateData_LayerChanged() {
						fdOldLayerScale = fdLayerScale = fdOldLayerElevation = fdLayerElevation = fdOldLayerHeight = fdLayerHeight = 0;
						fOldLayerName[0] = fLayerName[0] = 0;
						fbScaleText = false;
					}
};

//----------------------------------------------------------
struct ObjectStateData_ExitFromEditGroup
// StateData for exit edit group
//	fGroupType is one of the 'kObjectEditGroupPropertyID' property values
{
	unsigned char		fGroupType;
};

//----------------------------------------------------------
struct ObjectStateData_ObjectNameChanged
// StateData for object name change
{
	GSStr63		fOldName;
	GSStr63		fNewName;
};

//----------------------------------------------------------
struct ObjectStateData_ObjectPlanarRefChanged
// StateData for object planar ref change
{
	bool		fbIsScreenObject;
};

//----------------------------------------------------------
enum EStateObjectCreationContext
{
    eContext_Unknown = 0,
    eContext_Duplicated = 1,
    eContext_NewlyCreated = 2
};

//----------------------------------------------------------
struct ObjectStateData_ObjectCreated
// StateData for object creation
{
    ObjectStateData_ObjectCreated(){ fContext = eContext_Unknown;}
    ObjectStateData_ObjectCreated(const EStateObjectCreationContext inContext){ fContext = inContext;}
    
    EStateObjectCreationContext fContext;
};

struct ObjectStateData_ObjectIsGeneratedBy
// State Data for generation of object from another object of same type.
{
	typedef TXGenericArray<Sint32>	TRefNumArray;
	TRefNumArray					farrRefNumbers;
};
//----------------------------------------------------------
struct ObjectStateData_ObjectScalingInfo
// StateData for object scale factors
{
	double		fScaleX;
	double		fScaleY;
	double		fScaleZ;
	WorldPt3	fScaleCubeCenter;
};

// =======================================================================================

#ifndef _MENUENABLEACCESS_
	#define _MENUENABLEACCESS_ 1

	// From MMenu.h
	struct MenuEnableAccess
	{
		Uint16 needs;
		Uint16 needsNot;
	};
#endif


// =======================================================================================
// similar to ToolFlagsType as defined in Overlay.h

struct MPToolFlags {
	Boolean			disablePickUpdate;		// Selects whether UpdateToolInfo is called when the mouse is moved
	Boolean			needsScreenPlane;		// Does the tool require screen plane
	Boolean			needs3DView;			// Does the tool require a non-plan projection
	Boolean			uses3DCursor;			// Does the tool use 3D grid/snap points
	Boolean			screenBasedCursor;		// Does the tool use only screen pos. without gridding
	Boolean			needsPerspective;
	Boolean			dontShowScreenHints;	// Turn off screen hints
};


// =======================================================================================
// similar to PalToolDataType as defined in Overlay.h (and 'TDef' resources)

struct MPToolData {
	MPToolFlags		toolFlags;
	short			unused1;
	short			unused2;
	GSStr255		messageStr;
	short			waitMoveDist;
	Sint32			constraintFlags;
	short			barDisplayMode;
	short			minCompatibleVers;		// 500 for 5.0.0
};
typedef	MPToolData *MPToolDataPtr, **MPToolDataHandle;


//=======================================================================================
class TMPExternalDataForWorkspace
{
public:
	
	TMPExternalDataForWorkspace():
		fType(kVSPluginMenu), fIconDataSize(0), fIconDataSizeRetina(0), fVersionCreated(0),
		fVersionModified(0), fVersionRetired(0),fProtectionProducts(0),fProtectionModules(0)
	{
		fUniversalName[0] = 0;
		fLocalizedName[0] = 0;
		fCategory[0] = 0;
		fEnableFlags.needs = 0;
		fEnableFlags.needsNot = 0;
		fToolDataHand = 0;
	}
	
	EVSPluginType			fType;
	
	GSStr63                 fUniversalName;		// Universal Name
	GSStr63                 fLocalizedName;		// Localized Name
	GSStr63					fCategory;			// Localized category
	
	MenuEnableAccess		fEnableFlags;
	MPToolDataHandle		fToolDataHand;
	Uint8					fIconData[40 * 40 * 4];
	Uint8					fIconDataRetina[80 * 80 * 4];
	size_t					fIconDataSize;
	size_t					fIconDataSizeRetina;
	short					fVersionCreated;
	short					fVersionModified;
	short					fVersionRetired;
	Uint32					fProtectionProducts;
	Uint16					fProtectionModules;
};


// End "Private" Callback section
//=====================================================================================
//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
// include the automatically generated portion of this file

#if _MINICAD_ && !BUG
	// inline these calls if we are compiling inside MiniCAD except for the BUG version.
	// we won't get duplicate function name checks if we inline these functions
	// because the inlined functions use C++ calling conventions - PCP
	#define GS_INLINE_SDK_CALLS 1
#else
	#define GS_INLINE_SDK_CALLS 0
#endif

#if GS_INTERFACE_FACTORING && !GS_CORE_BUILD
	// This is skipped for now in Bernini because some of the functions are implemented as macros. [DMB 4/7/99]
#else
	#if GS_INLINE_SDK_CALLS
		#include "MiniCadCallBacks.InlineDefs.h"	
	#else
		#include "MiniCadCallBacks.Defs.h"
	#endif

#endif


//////////////////////////////////////////////////////////////////////////////////////////
//#if defined(_supply_new_)
//
//	#if _MINICAD_
//		#error "_supply_new_ is unsupported in MiniCAD - PCP"
//	#endif
//
//	// supply new for altura based windows externals
//	// this must be in the header because if it is in the library, then MFC
//	// based externals will not link - PCP
//
//	static void*	operator new(size_t size)		{ return GS_NewPtr(gCBP, size); }
//	static void		operator delete(void* p)		{ GS_DisposePtr(gCBP, p); }
//
//#endif // _supply_new_


// for these inlines, we don't need to export them as they are generated
// in the client code

// these are also C++ functions and can be overloaded



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





//----------------------------------
//----------------------------------
//	Hot Spot API:
//
typedef short HotSpotType;

const HotSpotType kScreenPlanarSelBox = 0; 	// A 2D location with selection box like the VectorWorks selection handles 
const HotSpotType kModel3DSelBox = 1;		// A 3D location with selection box like the VectorWorks selection handles
const HotSpotType kUnderConstruction = 2;	// internal use




//---------------------------------------------------------------
//---------------------------------------------------------------
struct CustomBarLockValueData
//
//	CustomBarEventData::fCustomBarEventSelector == kCustomBarLockValue contains a pointer to
//	this structure.
{
	short 		fFieldIndex;
	TXString	fUserLockString;
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//
//
//		BEGIN NNA DECLARATION SPACE:
//	
//	Declarations below should be considered as internal NNA and subject to change. 


// See Kludge 3652, 3653 for documentation on this structure.
struct KSS
{
	TXString	str1;
	TXString	str2;
	TXString	str3;
};


///////////////////////////////////////////////////////////////////////////////
// 	NNA plugins are registered to be reset for file tranlation using the code below.
//	The code below is called from the NNA plug-in Library VS_SharedLibrary from its
//	kPluginModuleInit action/event:
//	
//
//		case kPluginModuleInit: {
//			
//			//	Here is where we specify the IP plugins for reset at file translate time
//			RegisterPluginForFileTranslationReset();
//			break;
//		}
//	Third Party Developers can use the GS_Kludge(gCBP, 3654 	
//	to specify their plugins for reset at file translation.
//	
//	The call to GS_Kludge(gCBP, 3654 ...) can go in the object's interface registration (the main function of the plug-in module)
//	action handler or in some plugin library as is the case with VS_SharedLibrary 
//
//	You may use GS_Kludge(gCBP, 3663 ...) instead of 3654 if you want to additionally
//	specify a bugFix revision number.
	
/*
static void AddResetSpec(const TXString & inUniversalObjectName, short inFileVersion)
//
//	Called from RegisterPluginForFileTranslationReset below
{
	//	See MiniCadCallBacks.h below
	KludgeObjectResetAfterTranslate callParams;
	
	inUniversalObjectName.CopyInto(callParams.objectNameUniversal);
	callParams.oldVersionNum = inFileVersion;
	
	(void) GS_Kludge(gCBP, 3654, &callParams, nil);
}

//--------------------------------------------------------------------------------------------
void RegisterPluginForFileTranslationReset()
//	
//	This code is called from VS_SharedLibrary's kPluginModuleInit event.
//	Here is how NNA plugins are registered for Reset on file translation.
//	
{
	#define kVectorWorks11FileVersion	122
	#define kVectorWorks10FileVersion	111
	#define kMiniCad9FileVersion		101

	AddResetSpec("Callout", 			kMiniCad9FileVersion);
	AddResetSpec("Base Cabinet", 		kVectorWorks11FileVersion);
	AddResetSpec("Door", 				kVectorWorks11FileVersion);
	AddResetSpec("Drawing Label", 		kVectorWorks11FileVersion);
	AddResetSpec("Feature Control Frame",kVectorWorks11FileVersion);
	AddResetSpec("Focus Point Object", 	kVectorWorks11FileVersion);
	AddResetSpec("Lighting Device", 	kVectorWorks11FileVersion);
	AddResetSpec("PhotoGrid", 			kVectorWorks11FileVersion);
	AddResetSpec("Photometer", 			kVectorWorks11FileVersion);
	AddResetSpec("Utility Cabinet", 	kVectorWorks11FileVersion);
	AddResetSpec("Wall Cabinet", 		kVectorWorks11FileVersion);
	AddResetSpec("Window", 				kVectorWorks11FileVersion);
	AddResetSpec("Property Line", 		kVectorWorks11FileVersion);
	
	#undef kVectorWorks11FileVersion
	#undef kVectorWorks10FileVersion
	#undef kMiniCad9FileVersion	
}
*/

struct KludgeObjectResetAfterTranslate
{
	TXString objectNameUniversal;
	short	oldVersionNum;
};

struct KludgeObjectResetAfterTranslateExt
{
	TXString objectNameUniversal;
	short	oldVersionNum;
	short	oldBugFixVersionNum;
};


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
	Sint32		fNumItems;
	Sint32*		fIndexArray;
	short*		fFileRefArray;
	Boolean*	fIsSeparatorArray;
	TXStringArray	fNameArray;
	TXString*	fImageSpecArray;
	Sint32		fSelectedItem;
	ThumbnailSizeType fSizeType;
	TXString			fCategoryTitle;
	TXStringArray		fCategoryArray;
	size_t				fCategorySelIndex;
};

//Sint32 DisplayImagePopup (TDisplayImageListInfo& imageInfo, Sint32 top, Sint32 left, Sint32 bottom, Sint32 right);
APP_API_FUNCTION(Sint32, 
		GS_DisplayImagePopup(CallBackPtr, TDisplayImageListInfo& imageInfo, Sint32 top, Sint32 left, Sint32 bottom, Sint32 right),
	 	CB_DisplayImagePopup(TDisplayImageListInfo& imageInfo, Sint32 top, Sint32 left, Sint32 bottom, Sint32 right), 
	 	CB_DisplayImagePopup(imageInfo, top, left, bottom, right))

//	---------------------------------------------------------------------------------------
//	---------------------------------------------------------------------------------------

	
	#if !(_WIN_EXTERNAL_ || _GSWINSDK_)

	inline const ViewPt   MacToViewPt(const Point& p)   { return ViewPt(p.h, p.v); }
	inline const ViewRect MacToViewRect(const Rect& r)  { return ViewRect(r.left, r.top, r.right, r.bottom); }

	inline const Point ViewToMacPt(const ViewPt& p)     { Point macPoint = {p.y, p.x}; return macPoint;}
	inline const Rect  ViewToMacRect(const ViewRect& r) { Rect  macRect  = {r.Top(), r.Left(), r.Bottom(), r.Right()}; return macRect;}

	#if WINVER

	inline const POINT ViewToWinPt  (const ViewPt   &p) { POINT winPoint = {p.x, p.y}; return winPoint; }
	inline const RECT  ViewToWinRect(const ViewRect &r) { RECT  winRect  = {r.Left(), r.Top(), r.Right(), r.Bottom()}; return winRect; }

	// these go from longs to shorts
	inline const ViewPt   WinToViewPt  (const POINT& p) { return ViewPt(LongToShort(p.x), LongToShort(p.y)); }
	inline const ViewRect WinToViewRect(const RECT&  r) { return ViewRect(LongToShort(r.left), 
																		  LongToShort(r.top), 
																		  LongToShort(r.right), 
																		  LongToShort(r.bottom)); }
	#endif

	#endif // !(_WIN_EXTERNAL_ || _GSWINSDK_)

// Event messaging

/////////////	-----------------------------------------------
///////////		DEFAULT TOOL SUPPORT
/////////		-----------------------------------------------
///////
/////
///
//
//	
	
// Default point tool
// Allow us to use the default insertion tool as base for all point like tools
struct SDefaultPointToolInfo
{
	short fModeGroup;			// radio group
	short fAllowInsertGroup;	// button group (single button)
	short fAlignmentGroup;		// radio group
	short fSymbolResourceGroup;	// resource thumbnail list group

	// ---------
	// fModeGroup:
	//		insertModeGroup choice indices
	short fRegularInsChoiceIndex;
	short fOffsetInsChoiceIndex;
	short fPickUpChoiceIndex;

	// ---------
	// fAlignmentGroup:
	//		alignmentGroup choice indices
	short fLeftChoiceIndex;
	short fCenterChoiceIndex;
	short fRightChoiceIndex;
	short fNaturalChoiceIndex;

	// ---------
	// additional options for the default tool
	double		fInsertRotateAngleAddition;

	// This matrix will be used after a default point tool is added to a wall
	// when the mouse is used to orient the object in the wall
	TransformMatrix		fWallPreviewOrientationAfterMatrix;

	SDefaultPointToolInfo() {
		fModeGroup = fAllowInsertGroup = fAlignmentGroup = -1;
		fSymbolResourceGroup = -1;
		fRegularInsChoiceIndex = fOffsetInsChoiceIndex = fPickUpChoiceIndex = -1;
		fLeftChoiceIndex = fCenterChoiceIndex = fRightChoiceIndex = fNaturalChoiceIndex = -1;
		fInsertRotateAngleAddition = 0;
		for (Sint32 i = 0; i <= 3; i++)
			for (Sint32 a = 0; a <= 2; a++)
				fWallPreviewOrientationAfterMatrix.mat[i][a] = (a == i) ? 1.0 : 0.0;
	}
};

// Default line tool
// Allow us to use the default insertion tool as base for all line like tools
struct SDefaultLineToolInfo
{
	short	fModeGroup;	// radio group

	// ---------
	// fModeGroup:
	//		line mode choice indices
	short fConstrainedChoiceIndex;
	short fUnconstrainedChoiceIndex;

	SDefaultLineToolInfo() {
		fModeGroup = fConstrainedChoiceIndex = fUnconstrainedChoiceIndex = -1;
	}
};

// Default rect tool
// Allow us to use the default insertion tool as base for all rect like tools
struct SDefaultRectToolInfo
{
	short	fModeGroup;			// radio group

	// ---------
	// fModeGroup:
	//		rect mode choice indices
	short fCenterLineChoiceIndex;
	short fEdgePlacementChoiceIndex;

	SDefaultRectToolInfo() {
		fModeGroup = fCenterLineChoiceIndex = fEdgePlacementChoiceIndex = -1;
	}
};

// Default 2D poly tool
// Allow us to use the default insertion tool as base for all 2D poly like tools
struct SDefault2DPolyToolInfo
{
	short	fModeGroup;			// radio group
	short	fFiletRadiusGroup;	// button group (single button)

	// ---------
	// fModeGroup:
	//		2D poly mode choice indices
	short fCornerVertChoiceIndex;
	short fBezierVertChoiceIndex;
	short fCubicVertChoiceIndex;
	short fTangetChoiceIndex;
	short fPointOnArcChoiceIndex;
	short fArcVertChoiceIndex;

	SDefault2DPolyToolInfo() {
		fModeGroup = fFiletRadiusGroup = -1;
		fCornerVertChoiceIndex = fBezierVertChoiceIndex = fCubicVertChoiceIndex = -1;
		fTangetChoiceIndex = fPointOnArcChoiceIndex = fArcVertChoiceIndex = -1;
	}
};

// Default 3D poly tool
// Allow us to use the default insertion tool as base for all 3D poly like tools
struct SDefault3DPolyToolInfo
{
	short	fModeGroup;			// radio group
	short	fNURBSDegSetGroup;	// button group (single button)

	// ---------
	// fModeGroup:
	//		3D poly mode choice indices
	short fNURBSByInterpChoiceIndex;
	short fNURBSByCtrlPtChoiceIndex;

	SDefault3DPolyToolInfo() {
		fModeGroup = fNURBSDegSetGroup = -1;
		fNURBSByInterpChoiceIndex = fNURBSByCtrlPtChoiceIndex = -1;
	}
};

/////////////	-----------------------------------------------
///////////		BEGIN MENU MESSAGING
/////////		-----------------------------------------------
///////
/////
///
//
//	

struct MenuMessage
{
	virtual ~MenuMessage() {}

	Sint32		fAction;

protected:
	MenuMessage() { /*fAction is not initialized here*/ }
};

struct MenuNotifyMessage : public MenuMessage
{
	enum { kAction = 6 };

	MenuNotifyMessage(Sint32 statusID) { fAction = MenuNotifyMessage::kAction; fStatusID = statusID; }

	Sint32		fStatusID;

protected:
	MenuNotifyMessage() { /*fAction is not initialized here*/ }
};

// MenuChunkInfo structure
struct MenuChunkInfo : public MenuMessage 		// used by menu definition functions
{	
	short menuID;
	short itemID;
	short modifiers;
	union {
		short chunkIndex;		// used by MenuDoInterfaceMessage::kAction and MenuItemDisplayContextualHelpMessage::kAction
		short chunkSize;		// used by MenuCheckHiliteMessage::kAction

		#ifdef GS_INTERFACE_FACTORING
		short commandID;        // used by MenuAddItemsMessage::kAction
		#endif

	};

protected:
	MenuChunkInfo() { menuID = 0; itemID = 0; modifiers = 0; chunkIndex = 0; }
};

struct MenuItemEnabledMessage : public MenuChunkInfo
{
	enum { kAction = 7 };

	MenuItemEnabledMessage(short inChunkIndex) { fAction = MenuItemEnabledMessage::kAction; chunkIndex = inChunkIndex; }
};

struct MenuDoInterfaceMessage : public MenuChunkInfo
{
	enum { kAction = 3 };

	MenuDoInterfaceMessage()					{ fAction = MenuDoInterfaceMessage::kAction; chunkIndex = 0; }
	MenuDoInterfaceMessage(short inChunkIndex)	{ fAction = MenuDoInterfaceMessage::kAction; chunkIndex = inChunkIndex; }
};

struct MenuAddItemsMessage : public MenuChunkInfo
{
	enum { kAction = 4 };

	MenuAddItemsMessage() { fAction = MenuAddItemsMessage::kAction; }
};

struct MenuCheckHiliteMessage : public MenuChunkInfo
{
	enum { kAction = 5 };

	MenuCheckHiliteMessage() { fAction = MenuCheckHiliteMessage::kAction; fCommandID = 0; }

	short fCommandID;
};

struct MenuItemDisplayContextualHelpMessage : public MenuChunkInfo
{
	enum { kAction = 11 };

	MenuItemDisplayContextualHelpMessage() { fAction = MenuItemDisplayContextualHelpMessage::kAction; }
};

struct MenuItemSpec : public MenuChunkInfo
	// 0 is returned to allow execution of item
	// kMenuItemSecurity is returned to disallow execution
{
	enum { kAction = 9 };

	MenuItemSpec() { fAction = MenuItemSpec::kAction; }

	short			commandID;			// if commandID < 0 then it's internal & externalName is nil
	TXString		externalName;		// if commandID == 1 then it's plug-in binary & externalName points to the name (no extension)
										// if commandID == 2 then it's plug-in VectorScript & externalName points to the name (no extension)
};

struct ToolMessage;

struct MenuToolActionHandlerParams : public MenuMessage
	//	If a Menu wants to get points from the document it needs to return kMenuRunTempTool
	//	from its MenuDoInterfaceMessage::kAction Menu action handler.  The menu will then be called with 
	//	kMenuHandleToolActions actions with message1 containing a pointer to a MenuToolActionHandlerParams
	//	structure.  MenuToolActionHandlerParams contains data defining standard tool actions.
	//	The menu command must handle these tool actions as if it were a tool definition procedure.
	//	See tool action handling above for more.
{
	enum { kAction = 10 };

	MenuToolActionHandlerParams(ToolMessage* message) :
		fToolMessage(message)
	{
		fAction = MenuToolActionHandlerParams::kAction;
	}

	ToolMessage*	fToolMessage;

protected:
	MenuToolActionHandlerParams() { /*fAction is not initialized here*/ }
};


/////////////	-----------------------------------------------
///////////		BEGIN PARAMETRIC OBJECT MESSAGING
/////////		-----------------------------------------------
///////
/////
///
//

//typedef Sint32 ObjectEventID;

struct ParametricMessage
{
	virtual ~ParametricMessage() {}

	Sint32			fAction;
	MCObjectHandle	fParametricHandle;

protected:
	ParametricMessage() { fAction = 0; fParametricHandle = NULL; }
};

struct ParametricRecalculate : public ParametricMessage
	// The Plug-in Object code should re-create all its component objects using current parameter values.
{
	enum { kAction = 3 };

	ParametricRecalculate(MCObjectHandle wall) { fAction = ParametricRecalculate::kAction; fWallHandle = wall; }

	MCObjectHandle		fWallHandle;
};

struct ParametricPreferencesMessage : public ParametricMessage
	// Object Definition Procedure (ODP) may optionally present its own preferences dialog, or let VW pose the default dialog.
{
	enum { kAction = 4 };

	ParametricPreferencesMessage(MCObjectHandle format) { fAction = ParametricPreferencesMessage::kAction; fFormatHandle = format; }

	MCObjectHandle		fFormatHandle;
};

struct ParametricSpecialEditMessage : public ParametricMessage
	// The Plug-in Object called with kParametricOnMove when kHasMoveDependancy extended property set 
{
	enum { kAction = 7 };

	ParametricSpecialEditMessage(TObjectEdiReason editReason) { fAction = ParametricSpecialEditMessage::kAction; fEditReason = editReason; fEditResult = kObjectEditResult_Default; }

	TObjectEdiReason	fEditReason;

	// the value of this variable determines what Vectorworks will do after the special event message
	TObjectEditResult	fEditResult;
};

struct ParametricOnDM_GetCursorMessage : public ParametricMessage
{
	enum { kAction = 15 };

	ParametricOnDM_GetCursorMessage(Sint32 pickIndex) { fAction = ParametricOnDM_GetCursorMessage::kAction; fPickIndex = pickIndex; }

	Sint32		fPickIndex;
};

struct ParametricOnDM_ModeEvent : public ParametricMessage
{
	enum { kAction = 16 };

	ParametricOnDM_ModeEvent(Sint32 modeGroup) { fAction = ParametricOnDM_ModeEvent::kAction; fModeGroup = modeGroup; }

	Sint32		fModeGroup;
};

namespace VectorWorks
{
	namespace Extension
	{
		class DYNAMIC_ATTRIBUTE IShapePaneWidgetAccess;
	}
}

struct ParametricUIButtonHitMessage : public ParametricMessage
	// The user has pressed a button in the Properties UI of an object
{
	enum { kAction = 35 };

	ParametricUIButtonHitMessage(Sint32 buttonID,
								 VectorWorks::Extension::IShapePaneWidgetAccess* access,
								 SintptrT viewWidget,
								 bool needReset)
	{
		fAction = ParametricUIButtonHitMessage::kAction;
		fButtonID = buttonID;
		fWidgetAccess = access;
		fViewWidget = viewWidget;
		fNeedReset = needReset;
	}

	Sint32		fButtonID;

	VectorWorks::Extension::IShapePaneWidgetAccess*		fWidgetAccess;
	SintptrT					fViewWidget;
	bool						fNeedReset;
};

struct ParametricCurosrMessage : public ParametricMessage
{
	enum EAction
	{
		kAction_MouseDown 		= 36,
		kAction_Complete 		= 37,
		kAction_MouseMove 		= 38,
		kAction_Draw 			= 39,
		kAction_Cancel 			= 40,
	};

	ParametricCurosrMessage(ParametricCurosrMessage::EAction action, Sint32 pickIndex) { fAction = action; fPickIndex = pickIndex; }

	Sint32		fPickIndex;
};

struct ParametricDragMessage : public ParametricMessage
{
	enum { kAction = 69 };

	ParametricDragMessage(bool is3D) { fAction = ParametricDragMessage::kAction; fIs3D = is3D; }

	bool	fIs3D;
};

struct ParametricGetToolNameMessage : public ParametricMessage
{
	enum { kAction = 43 };

	ParametricGetToolNameMessage() { fAction = ParametricGetToolNameMessage::kAction; }

	TXString	fToolName;
};

struct ParametricEyeDropperMessage : public ParametricMessage
{
	enum EAction
	{
		kAction_PrepareCopy		= 48,
		kAction_AfterCopy		= 51,
	};

	ParametricEyeDropperMessage(ParametricEyeDropperMessage::EAction action) { fAction = action; fRecordHandle = NULL; fSourceObjHandle = NULL; }

	MCObjectHandle	fRecordHandle;		// when prepare copy
	MCObjectHandle	fSourceObjHandle;	// when after copy
};

//----------------------------------------------------------
struct ObjectEventCall : public ParametricMessage
	//
	//	Many events use a ObjectEventCall to supply event data.  For these events the message parameter
	//	is a pointer to a  ObjectEventCall structure.
	//
	//	return kParametricHandledEvent if ODP handled the event, kParametricEventNotHandled if not
{	
	Sint32 	fSpecifier;
	void* 	fData;

protected:
	ObjectEventCall() { fSpecifier = 0; fData = NULL; }
};

//----------------------------------------------------------
struct OnObjectWidgetPrepCall : public ObjectEventCall
	//
	//	Objects with the kObjXHasCustomWidgetVisibilities property have their Object definition procedure called with
	//	the OnObjectWidgetPrepCall::kAction event.  The message parameter is a pointer to this structure.  
	//
	//	fData is a pointer to an array of WidgetInfoType (s)
	//	fSpecifier contains the number of WidgetInfoType (s) in the fData
	//	fpWidgetProvider is (IWidgetsProvider*) for widget update
	//
	//	return kParametricHandledEvent if ODP handled the event, kParametricEventNotHandled if not.
{	
	enum { kAction = 41 };

	OnObjectWidgetPrepCall() { fAction = OnObjectWidgetPrepCall::kAction; fpWidgetProvider = NULL; }

	void*	fpWidgetProvider;
};

struct OnObjectStyleWidgetPrepCall : ObjectEventCall
{
	enum { kAction = 70 };

	OnObjectStyleWidgetPrepCall() { fAction = OnObjectStyleWidgetPrepCall::kAction; fpWidgetProvider = NULL; fHideStyleParameters = FALSE; }

	void*	fpWidgetProvider;
	bool	fHideStyleParameters;
};


//----------------------------------------------------------
struct OnObjectWidgetValueCall : public ObjectEventCall
	//
	//	Objects with the kObjXHasCustomWidgetValues property have their Object definition procedure called with
	//	the OnObjectWidgetValueCall::kAction event.  The message parameter is a pointer to this structure. 
	//
	//	fData - is (IWidgetsProvider*) 
	//	fSpecifier - 0
	//	fChangedWidgetID - the ID of the widget that has cahged if it is kOnTranslateToData, otherwise = 0
	//	fTranslateType - determine the reason of call
	//	fResult - is the result of the event; determine if VW should execute the default translating of the values
{
	enum { kAction = 47 };

	OnObjectWidgetValueCall() { fAction = OnObjectWidgetValueCall::kAction; fChangedWidgetID = 0; }

	enum ETranslateype {
		kOnTranslateToView,		// values are moved from data to the view
		kOnTranslateToData,		// values are moved from view to the data
	};

	Sint32			fChangedWidgetID;
	ETranslateype	fTranslateType;
};

//----------------------------------------------------------
struct ObjectCommand : public ObjectEventCall
	//
	//	Objects with the kObjXHandlesCommand property have their Object definition procedure called with
	//	the ObjectCommand::kAction event.  The message parameter is a pointer to this ObjectCommand structure.  
	//	Use the fSubtype to determine the type of data in  fData.
	//
	//	return kParametricHandledEvent if ODP handled the event, kParametricEventNotHandled if not
{	
	enum { kAction = 42 };

	ObjectCommand() { fAction = ObjectCommand::kAction; }

	enum ECommandType { 	
	
		//  never called, use EStateType::kObjectScaleReset to handle scaling.
		kOnSymetricScale = 0, 	//	for this fSubtype fData is a double* that is the scale
								// 	being applied to the object.
								
		//  Same as overriding VWParametric_EventSink::OnModifyObjectCommand(const TransformMatrix&)
		kOnMatrixTransform = 1, //	for this fSubtype fData is a TransformMatrix* that is the
								//	transform being applied to the object
		
		//  The object is selected and has Selection Control Poitns to show.
		//  To control the Cursor Hadles, implement IProviderCursorHandles instead.
		kOnDrawSelected = 2,	// for this fSubtype fData is null
		
		//	The object is selected and the multiple reshape tool has completed the 
		//	marquee drag. Use IProviderReshape to implement advanced object reshaping.
		kOnMultipleReshapeComplete = 3,	// for this fSubtype fData is a pointer to
								// a MultipleReshapeEventData strucutre

		//	The object is selected and the multiple reshape tool is in the middle of
		//	a marquee drag. Use IProviderReshape to implement advanced object reshaping.
		kOnMultipleReshapeDraw = 4	// for this fSubtype fData is a pointer to
								// a MultipleReshapeEventData strucutre
	};
};

//----------------------------------------------------------
struct ObjectState : public ObjectEventCall
	// 
	//	Objects with the kObjXPropAcceptStates property have their Object definition procedure called with
	//	the ObjectState::kAction event.  The message parameter is a pointer to this ObjectState structure.  
	//	Use the fSpecifier to determine the type of data in  fData.
	//
{
	enum { kAction = 44 };

	ObjectState() { fAction = ObjectState::kAction; }

	enum EStateType {
		kFirstRegenReset,			// fData => NULL
		kMovedReset,				// fData => (const ObjectStateData_Position*)
		kRotatedReset,				// fData => (const ObjectStateData_Position*)
		kParameterChangedReset,		// fData => (const ObjectStateData_ParamChanged*)
		kObjectChangedReset,		// fData => (const ObjectStateData_ObjectChanged*)
		kLayerChangedReset,			// fData => (const ObjectStateData_LayerChanged*)
		kExitFromEditGroup,			// fData => (const ObjectStateData_ExitFromEditGroup*)
		kNameChanged,				// fData => (const ObjectStateData_ObjectNameChanged*)
		kObjectUndoRestore,			// fData => NULL
		kObjectUndoRemove,			// fData => NULL
		kPlanarRefChanged,			// fData => (const ObjectStateData_ObjectPlanarRefChanged*)
		kBeforeExportReset,			// fData => NULL
		kObjectUndoModify,			// fData => NULL

		// Vectorworks 2012
		kObjectCreated,				// fData => NULL
		kObjectDeleteBefore,		// fData => NULL
		kObjectUngroupBefore,		// fData => NULL

		// Vectorworks 2014
		kObjectExternalReset,		// fData => NULL

		// Vectorworks 2016
		kObjectConnectionsRemapped,	// fData => NULL

		// Vectorworks 2017
		kObjectReshaped,			// fData => NULL
		kObjectLockStatusChanged,	// fData => NULL
		kObjectPathReversed,		// fData => NULL
		kObjectIsGeneratedBy,		// fData => (const ObjectStateData_ObjectIsGeneratedBy*)
		// Vectorworks 2018
		kObjectScaleReset			// fData => (const ObjectStateData_ObjectScalingInfo*)
	};
};

//----------------------------------------------------------
struct ObjectContextMenuEvent : public ObjectEventCall
// 
//	Objects with the kObjXPropHasContextMenu property have their Object definition procedure called with
//	ObjectContextMenuEvent::kAction_Init  or ObjectContextMenuEvent::kAction_Event event.  The message parameter is a pointer to this ObjectContextMenuEvent structure.  
//
//	fData => (IContextMenuProvider*)
//	fSpecifier = 0;
//	fActiveMenuID is the active menu identifier when the menu item is selected
//
{
	enum EAction
	{
		kAction_Init		= 45,
		kAction_Event		= 46,
	};

	ObjectContextMenuEvent(ObjectContextMenuEvent::EAction action) { fAction = action; }

	Sint32 	fActiveMenuID;
};

//----------------------------------------------------------
struct ObjectGetSpecificGeometryCall : public ObjectEventCall
// ObjectGetSpecificGeometryCall::kAction event
//
// requests specific reometry from the parametric
// OnObjectGetSpecificGeometry::ESpecifier	type	= (OnObjectGetSpecificGeometry::ESpecifier) fSpecifier;
{
	enum { kAction = 49 };

	ObjectGetSpecificGeometryCall() { fAction = ObjectGetSpecificGeometryCall::kAction; }

	enum ESpecifier {
		eSpecifier_MappingGeometry,
		eSpecifier_SectionVPGeometry,
	};

	MCObjectHandle	fhGeometry;	// return a handle to the geometry here use (ISDK::GSNewObjectHandle to create the geometry handle)
};

struct ParametricCustomToolMessage : public ParametricMessage
	//	Object has declared itself in the "PExt" resource to have EPluginObjectSubType 
	//	equal to kCustomSubtype.  kCustomSubtype objects are provided a tool that calls 
	//	the object definition procedure main with ParametricCustomToolMessage::kAction events.  
	//	ParametricCustomToolMessage::kAction events wrap tool events in a ToolActionHandlerParams structure.  
	//	The message paramameter is a pointer to this structure.
{
	enum { kAction = 111 };

	ParametricCustomToolMessage(ToolMessage* toolMessage) { fAction = ParametricCustomToolMessage::kAction; fToolMessage = toolMessage; }

	ToolMessage*	fToolMessage;
};

struct CustomBarEventData;

struct ParametricCustomBarMessage : public ParametricMessage
{
	enum EAction
	{ 
		kAction_OnDM		= 18,
		kAction_OnCursor	= 50,
	};

	ParametricCustomBarMessage(ParametricCustomBarMessage::EAction action, CustomBarEventData* data) { fAction = action; fData = data; }

	CustomBarEventData*	fData;
};

struct ParametricAtributeMessage : public ParametricMessage
{
	enum EAction
	{
		kAction_Select 					= 26,	
		kAction_Cancel 					= 27,	
		kAction_MouseDown 				= 28,	
		kAction_Draw 					= 29,	
		kAction_MouseMove 				= 29,		// Meaning has changed for Vw 2011. See T00617
		kAction_Complete 				= 30,	
		kAction_GetCursor 				= 31,	
		kAction_GetStatus 				= 33,	
		kAction_ToolSetDown				= 54,
		kAction_ToolSelectionChange		= 56,
		kAction_ToolPlanarSnapFiltering	= 57,
	};

	ParametricAtributeMessage(ParametricAtributeMessage::EAction action)	{ fAction = action; }
};

struct ParametricAtributeMove2DMessage : public ParametricMessage
{
	enum { kAction = 32 };

	ParametricAtributeMove2DMessage(const WorldPt& offset, Boolean nudging) { fAction = ParametricAtributeMove2DMessage::kAction; fOffset = offset; fNudging = nudging; }

	WorldPt		fOffset;
	Boolean		fNudging;
};

struct ParametricAtributeModeMessage : public ParametricMessage
{
	enum { kAction = 34 };

	ParametricAtributeModeMessage(Sint32 mode) { fAction = ParametricAtributeModeMessage::kAction; fMode = mode; }

	Sint32		fMode;
};

struct ParametricDMMessage : public ParametricMessage
{
	enum EAction
	{
		kAction_Select 				= 10,	
		kAction_Cancel 				= 11,	
		kAction_MouseDown 			= 12,	
		kAction_Draw 				= 13,	
		kAction_Complete 			= 14,	
		kAction_GetStatus 			= 17,	
		kAction_BeginPauseEvent		= 19,
		kAction_EndPauseEvent		= 20,
		kAction_MouseMove 			= 21,
	};

	ParametricDMMessage(ParametricDMMessage::EAction action)	{ fAction = action; }
};

struct ParametricGetInCurtainWallMessage : public ParametricMessage
{
	enum { kAction = 52 };

	ParametricGetInCurtainWallMessage()	{ fAction = ParametricGetInCurtainWallMessage::kAction; fInCurtainWall = false; }

	bool fInCurtainWall;
};

struct ParametricSetObjectInCurtainWallMessage : public ParametricMessage
{
	enum { kAction = 53 };

	ParametricSetObjectInCurtainWallMessage( double width, double height, const WorldPt& center, Sint32 index ) { fAction = ParametricSetObjectInCurtainWallMessage::kAction; fWidth = width; fHeight = height; fCenter = center ; fIndex = index; }

	double fWidth;
	double fHeight;
	WorldPt fCenter;
	Sint32 fIndex;

};

struct ParametricSubtractPanelFromFrames : public ParametricMessage
{
	enum { kAction = 58 };

	ParametricSubtractPanelFromFrames()	{ fAction = ParametricSubtractPanelFromFrames::kAction; fSubtractPanelFromFrames = false; }

	bool fSubtractPanelFromFrames;
};

struct ParametricStyleMessage : public ParametricMessage
{
	enum EAction {
		kAction_FinalizeCreateStyle = 63,
		kAction_FinalizeUpdateStyledObject = 64,
		kAciton_ForwardTranslateStyleToVW22 = 72,
	};

	ParametricStyleMessage(   ParametricStyleMessage::EAction action, MCObjectHandle hSymDef ) { fAction = action; fSymDefHandle = hSymDef;  }

	MCObjectHandle fSymDefHandle;
};

struct ParametricEditPluginStyle : public ParametricMessage
{
	enum { kAction = 60 };

	ParametricEditPluginStyle( MCObjectHandle hSymDef) { fAction = ParametricEditPluginStyle::kAction; fSymDefHandle = hSymDef;  }

	MCObjectHandle fSymDefHandle;
};

struct ParametricCreatePluginStyle : public ParametricMessage
{
	enum { kAction = 61 };

	ParametricCreatePluginStyle( MCObjectHandle hSymDef) { fAction = ParametricCreatePluginStyle::kAction; fSymDefHandle = hSymDef;  }

	MCObjectHandle fSymDefHandle;
};

struct ParametricUpdatePluginStyleObject : public ParametricMessage
{
	enum { kAction = 62 };

	ParametricUpdatePluginStyleObject( MCObjectHandle hSymDef) { fAction = ParametricUpdatePluginStyleObject::kAction; fSymDefHandle = hSymDef;  }

	MCObjectHandle fSymDefHandle;
};

struct ParametricStyleWidgetChosen : public ParametricMessage
{
	enum { kAction = 65 };	

	ParametricStyleWidgetChosen( int itemChosen ) { fAction = kAction; fItemChosen = itemChosen; }

	int fItemChosen;
};

struct ParametricGetUsingLayerCutPlane : public ParametricMessage
{
	enum { kAction = 71 };

	ParametricGetUsingLayerCutPlane() { fAction = ParametricGetUsingLayerCutPlane::kAction; fUsingLayerCutPlane = false; }

	bool fUsingLayerCutPlane;
};

struct ParametricAllowWorksheetEdit : public ParametricMessage
{
	enum { kAction = 73 };

	ParametricAllowWorksheetEdit(const TXString & fieldName ) { fAction = ParametricAllowWorksheetEdit::kAction; fFieldName = fieldName; fAllowEdit = true; }

	TXString fFieldName;
	bool fAllowEdit;
};

struct ParametricGetCatalogPath : public ParametricMessage
{
	enum { kAction = 74 };

	ParametricGetCatalogPath( EFolderSpecifier folderSpecifier, const TXString & relativePath ) { fAction = ParametricGetCatalogPath::kAction; fFolderSpecifier = folderSpecifier ; fRelativePath = relativePath; }

	EFolderSpecifier fFolderSpecifier;
	TXString fRelativePath;


};

struct ParametricValidateReplacePluginStyle : public ParametricMessage
{
	enum { kAction = 75 };

	ParametricValidateReplacePluginStyle( MCObjectHandle hSymDef ) { fAction = ParametricValidateReplacePluginStyle::kAction; fSymDefHandle = hSymDef; }

	MCObjectHandle fSymDefHandle;
};

struct ParametricGenerateViewGraphic : public ParametricMessage
{
	enum { kAction = 80 };

	ParametricGenerateViewGraphic(EViewTypes viewType) { fAction = ParametricGenerateViewGraphic::kAction; fViewType = viewType; }

	EViewTypes fViewType;


};


/////////////	-----------------------------------------------
///////////		BEGIN TOOL OBJECT MESSAGING
/////////		-----------------------------------------------
///////
/////
///
//


//	When adding a new Tool action make sure to verify that the action is handled in TToolActionHandlerBase

struct ToolMessage
{
	enum EAction
	{ 
		kAction_DoDoubleClick			= 8,
		kAction_DoDrawScrMod			= 9,
		kAction_DoUndrawScrMod			= 10,
		kAction_MouseMove				= 101,
		kAction_DrawingDoubleClick		= 102,
		kAction_Draw 					= 103,
		kAction_GetStatus 				= 105,
		kAction_OnSelectionChange   	= 109,
		kAction_OnIdle					= 112,

#ifdef GS_USE_NEW_SELECTION_TOOL
		kAction_OnViewChange			= 117,		// NNA Internal USE
#endif

		kAction_OnUpdate2D3DCursor				= 118,		// ToolDef Decides which cursor to use action was handled by a ToolDef
		kAction_OnGetWantsAutoPlane				= 119,		// ToolDef Decides if it wants Autoplane behavior.  THe default is yes for Planar tools.  The rotate tool would like this and will return a non-zero value to get it
		kAction_OnGetWantsPlanarSnapFiltering	= 120,		// ToolDef Decides if it wants Planar snap filtering.  The default is true for planar tools.  The ATtribute Mapping tool may want this for certain contexts.
		kAction_PreventsSnapLoupe				= 122,
		kAction_SupportsScreenPlane				= 123,		// New tool action to allow Active Plane to query the current tool to see if it
															//		wants the screen plane item returning zero will provide screen plane if
															//		tool flags are (! (needsPlanarContext == false && needsScreenPlane == false && needs3DView == false))
		kAction_OnDeleteKeyWithNoToolPts		= 124,		// The delete key is pressed with no tool points.  Return kToolSpecialKeyEventHandled if tool handles it
		kAction_OnEscapeKeyWithNoToolPts		= 125,		// The escape key is pressed with no tool points.  Return kToolSpecialKeyEventHandled if tool
		kAction_OnSpecialKeyWithNoToolPts		= 126,		// Special key handling for Walkthrough Preferences for Gamer mode task. Return kToolSpecialKeyEventHandled if tool handles it.
		kAction_OnEnterReturnKeyForToolCompletion	= 127,		// Special key handling for Enter/Return key. Return kToolReadyToCompleteWithEnterReturnKey if tool can complete it.
		kAction_OnScreenPlaneToolCanWorkWith3DView = 128,		// New tool action to allow ScreenPlane tools (like Zoom tool) work in 3D views also.
		kAction_OnBlackBackgroundChange			= 129,  // We llow tool to register for kNotifyBlackBackgroundChanged.  If it does, it will be called with this action.

		kAction_Draw_ActivePane				= 130,		// This is called in addition to kAction_Draw for the active view pane only. Used for tool that only want to draw on the active pane.
	};

	ToolMessage(ToolMessage::EAction action) { fAction = action; }
	virtual ~ToolMessage() {}

	Sint32		fAction;

	MCObjectHandle	fhInteractiveObj;	// this is initialized after kAction_MouseMove, ToolPointAddedMessage, ToolPointRemovedMessage from the polyline tool,
										// to let overriders know what the interactive preview object is

protected:
	ToolMessage()		{ fAction = 0; fhInteractiveObj = nullptr; }
};

struct ToolInitMessage : public ToolMessage
{
	enum EAction
	{ 
		kAction_Init		= -1,	// special event to allow custom special tools to initalize for a specific named VS/Default tool
		kAction_Destroy		= -2,
	};

	ToolInitMessage(ToolInitMessage::EAction action, const TXString& name)
	{ 
		fAction					= action;
		fObjectName				= name;
		fDefaultPointToolInfo	= NULL;
		fDefaultLineToolInfo	= NULL;
		fDefaultRectToolInfo	= NULL;
		fDefault2DPolyToolInfo	= NULL;
		fDefault3DPolyToolInfo	= NULL;
	}

	TXString				fObjectName;
	SDefaultPointToolInfo*	fDefaultPointToolInfo;
	SDefaultLineToolInfo*	fDefaultLineToolInfo;
	SDefaultRectToolInfo*	fDefaultRectToolInfo;
	SDefault2DPolyToolInfo*	fDefault2DPolyToolInfo;
	SDefault3DPolyToolInfo*	fDefault3DPolyToolInfo;

protected:
	ToolInitMessage()
	{
		fDefaultPointToolInfo	= NULL;
		fDefaultLineToolInfo	= NULL;
		fDefaultRectToolInfo	= NULL;
		fDefault2DPolyToolInfo	= NULL;
		fDefault3DPolyToolInfo	= NULL;
	}
};

struct ToolSetupMessage : public ToolInitMessage
{
	enum EAction
	{ 
		kAction_SetUp			= 3,
		kAction_SetDown			= 4,
	};

	ToolSetupMessage(ToolSetupMessage::EAction action, Sint32 flag)
	{ 
		fAction					= action;
		fFlag					= flag;
		fDefaultPointToolInfo	= NULL;
		fDefaultLineToolInfo	= NULL;
		fDefaultRectToolInfo	= NULL;
		fDefault2DPolyToolInfo	= NULL;
		fDefault3DPolyToolInfo	= NULL;
	}	

	Sint32					fFlag;
};

struct ToolGetCursorMessage : public ToolMessage
	// Vectorworks is requesting the cursor image resource specifier using a TXString* passed in the message1 parameter.
	// Use a resource specifier such as "RESOURCE_FILE_NAME_WITHOUT_EXTENSION/Cursors/MY_CURSOR_NAME.png".
{
	enum EAction
	{ 
		kAction_GetCursorLegacy	= 5,		// legacy cursor -- return the cursor id number of resource
		kAction_GetCursor		= 121		// modern imageSpec based cursor
	};

	ToolGetCursorMessage(ToolGetCursorMessage::EAction action) { fAction = action; }

	TXString	fCursorImageSpec;
};

struct ToolModeMessage : public ToolMessage
{
	enum { kAction = 7 };

	// group - this is group index that is 1-based
	// button - is a combination of the old and new button indices - 1-based
	//			0xAAAABBBB where AAAA is the old button index; BBBB is the new button index
	ToolModeMessage(Sint32 group, Sint32 button) { fAction = ToolModeMessage::kAction; message1 = group; message2 = button; }

	Sint32		message1;	// fModeGroup;
	Sint32		message2;	// fModeButton;
};

struct ToolPointAddedMessage : public ToolMessage
{
	enum { kAction = 100 };

	ToolPointAddedMessage(const WorldPt& wpt, const ViewPt& vpt) { fAction = ToolPointAddedMessage::kAction; fWorldPt = wpt; fViewPt = vpt; }

	WorldPt		fWorldPt;
	ViewPt		fViewPt;
};

struct ToolPointRemovedMessage : public ToolMessage
{
	enum { kAction = 106 };

	explicit ToolPointRemovedMessage(Boolean clearAllPoints) { fAction = ToolPointRemovedMessage::kAction; fClearingAllPoints = clearAllPoints; }

	Boolean		fClearingAllPoints;
};

struct ToolGenericStateChangeMessage : public ToolMessage
	// 	Action called when any program state change
	//	occurs that might affect a tool.  Tools that store cached 
	//	data might listen for this message to update their cache.
	//	Newly written tools should not find any need for this 
	//	action as cached data is usually not required - it is provided 
	//	to ease tool modernization.  An example where this action is
	//	observed is the Wall tool.  It is a very complicated tool
	//	that maintains a cache representing the current walls.  After a 
	//	key is pressed to lock a value in the data bar ToolGenericStateChangeMessage::kAction
	//	is called and the wall tool updates its cache so it can be redrawn 
	//	correctly.  This would not be necessary if the tool's ToolMessage::kAction_Draw message
	//	was able, like most tools, to draw itself with the tool points.
	//	GENERAL RULE:  Avoid using cached data to handle ToolMessage::kAction_Draw action calls.
	//	Use the current tool point data.
{
	enum { kAction = 107 };

	ToolGenericStateChangeMessage(Sint32 flags) { fAction = ToolGenericStateChangeMessage::kAction; fFlags = flags; }

	Sint32		fFlags;
};

struct ToolMoveSel2DMessage : public ToolMessage
{
	enum { kAction = 110 };

	ToolMoveSel2DMessage(WorldPt& offset, Boolean nudging) : fOffset( offset ) { fAction = ToolMoveSel2DMessage::kAction; fNudging = nudging; }

	WorldPt&	fOffset;
	Boolean		fNudging;
};

#ifdef SUPPORT_OBJECT_GRIPS
struct ToolProvideObjGripsMessage : public ToolMessage
	// The Tool wants the application to draw grips for the current selected objects.
{
	enum { kAction = 114 };

	ToolProvideObjGripsMessage(bool isMultiSel) { fAction = ToolProvideObjGripsMessage::kAction; fIsMultiSelect = isMultiSel; }

	bool	fIsMultiSelect;
};
#endif

struct ToolInitByObjectMessage : public ToolMessage
	// Send to the tool with MCObjectHandle as message1.
	// This notifies the tool that is activated from the specified parametric object
	// allowing the tool to initialize itself for creating objects of this type
{
	enum { kAction = 116 };

	ToolInitByObjectMessage(MCObjectHandle object) { fAction = ToolInitByObjectMessage::kAction; fObject = object; }

	MCObjectHandle	fObject;
};

struct ToolCompleteMessage : public ToolMessage
{
	enum EAction
	{
		kAction			= 104,
		kAction_Create	= -104,
	};

	ToolCompleteMessage(ToolCompleteMessage::EAction action) { fAction = action; fResultObject = NULL; }

	MCObjectHandle		fResultObject;
};

struct ToolDefaultPreviewUpdateMessage : ToolMessage
	// call back message for ISDK::CallDefaultTool for notifying the default tool
	// the message expects (message1 = MCObjectHandle) to the new object preview
{
	enum { kAction = -100 };

	ToolDefaultPreviewUpdateMessage(MCObjectHandle object) { fAction = ToolDefaultPreviewUpdateMessage::kAction; fObjectHandle = object; }

	MCObjectHandle		fObjectHandle;
};

struct ToolDefaultPreviewGetMessage : ToolMessage
	// the message is set to the custom tool to ask for an object to be created for preview display
	// this only happens for the wall-offset mode of the point-default-tool before the display of the Enter Offset dialog on the third click.
{
	enum { kAction = -101 };

	ToolDefaultPreviewGetMessage(MCObjectHandle hWall) { fAction = ToolDefaultPreviewGetMessage::kAction; fWallHandle = hWall; fResultHandle = NULL; }

	MCObjectHandle		fWallHandle;
	MCObjectHandle		fResultHandle;
};

struct CustomBarEventData : public ToolMessage
	// The Tool has installed a Custom Editable data bar.  	CustomBarEventData is supplied in the message1 parameter.			
{
	enum { kAction = 113 };

	CustomBarEventData() { fAction = CustomBarEventData::kAction; }

	Sint32 						fCustomBarEventSelector;	// see kCustomBarSetup
	CustomBarLockValueData* 	fData;
};

/////////////	-----------------------------------------------
///////////		BEGIN CONTROL DATA
/////////		-----------------------------------------------
///////
/////
///
//

struct SControlDataBase
{
	Sint32	fItemID;		// [get] - dialog item (control) id
	Sint32	fType;			// [get] - dialog item (control) type
	bool	fDataValid;		// [get] - is data valid when getting

	SControlDataBase()			{ fDataValid = false; }
	virtual ~SControlDataBase() {}

	void	SetValid(bool value=true) { fDataValid = value; }
};

struct SControlData_StaticText : public SControlDataBase
{
	Uint8	fColorRed;		// [set]
	Uint8	fColorGreen;	// [set]
	Uint8	fColorBlue;		// [set]

	SControlData_StaticText()							{}
	SControlData_StaticText(Uint8 r, Uint8 g, Uint8 b) { fDataValid = true; fColorRed = r; fColorGreen = g; fColorBlue = b; }
};

struct SControlData_ColorButton : public SControlDataBase
{
	Uint8	fColorRed;		// [set/get]
	Uint8	fColorGreen;	// [set/get]
	Uint8	fColorBlue;		// [set/get]

	SControlData_ColorButton()							{}
	SControlData_ColorButton(Uint8 r, Uint8 g, Uint8 b) { fDataValid = true; fColorRed = r; fColorGreen = g; fColorBlue = b; }
};

struct SControlData_Slider : public SControlDataBase
{
	Sint32	fSliderPos;		// [set/get]

	SControlData_Slider()			{}
	SControlData_Slider(Sint32 pos)	{ fDataValid = true; fSliderPos = pos; }
};

struct SControlData_Image : public SControlDataBase
{
	Sint16	fImageResID_Deprecated;		// [set]
	
	SControlData_Image()			{}
	SControlData_Image(Sint16 resId)	{ fDataValid = true; fImageResID_Deprecated = resId; }
};

struct SControlData_EditablePatternsDropDown : public SControlDataBase // kEditablePatternsDropDown
{
	SintptrT	fData;		// [set] -- Pointer to a cross platform 8 pixel x 8 pixel pattern
							//			Uint8 line[8]; //each bit is a pixel


	SControlData_EditablePatternsDropDown()			{}
};

struct SControlData_DashPopup : public SControlDataBase
{
	Sint16	fStyle;			// [set/get]
	Sint16	fWeight;		// [set/get]

	SControlData_DashPopup()				{}
	SControlData_DashPopup(Sint16 style, Sint16 weight)	{ fDataValid = true; fStyle = style; fWeight = weight; }
};

struct SControlData_LinePopup : public SControlDataBase
{
	Sint16	fLineWeight;	// [set/get]

	SControlData_LinePopup()			{}
	SControlData_LinePopup(Sint16 lw)	{ fDataValid = true; fLineWeight = lw; }
};


struct SControlData_EditText : public SControlDataBase
{
	TXString	fText;		// [set/get]

	SControlData_EditText()			{}
	SControlData_EditText(const TXString& str)	{ fDataValid = true; fText = str; }
};

struct SControlData_SymbolDisplay : public SControlDataBase
{
	short			fHeight;				// [get]
	short			fWidth;					// [get]
	short			fMargin;				// [get]
	InternalIndex	fPaintNodeRefNumber;	// [set/get]
};

struct SControlData_ThreeStateCheckbox : public SControlDataBase
{
	bool			fTextItalic;		// [set]

	SControlData_ThreeStateCheckbox()				{}
	SControlData_ThreeStateCheckbox(bool italic)	{ fDataValid = true; fTextItalic = italic; }
}
;

struct SListBrowserDragDropInfo
{
	TXGenericArray<Sint32>	farrIndicesDragged;
	Sint32					fDragIndex;
	Sint32					fDropIndex;
	Sint32					fSortState;

	SListBrowserDragDropInfo() { fDragIndex = -1; fDropIndex = -1; fSortState = 0; };
};

struct SImagePopupAdvancedMsgData
{
	enum EReason
	{
		Opened,
		CategoryChanged,
	};

	EReason		fReason;
	size_t		fCategoryIndex;
};

struct SDupObjInfo
{
    InternalIndex* wallFakeName;

	SDupObjInfo(InternalIndex* pWallFakeName) { wallFakeName = pWallFakeName; }
};

/////////////	-----------------------------------------------
///////////		BEGIN DASH STYLE PSEUDOINDEX TO LINE TYPE INTERNALINDEX CONVERTER
/////////		-----------------------------------------------
///////
/////
///
//

// This class is a wrapper around BeginMultiplePseudoDashIndexConvert and EndMultiplePseudoDashIndexConvert. It simply
// calls the BeginMultiplePseudoDashIndexConvert in its constructor, and EndMultiplePseudoDashIndexConvert in its
// descrtuctor. The goal of the wrapper class is to eliminate the likelihood of calling
// BeginMultiplePseudoDashIndexConvert without ever calling EndMultiplePseudoDashIndexConvert. This wrapper class
// also provides accessors to gSDK->GetPseudoDashIndexFromDashLineType and gSDK->GetDashLineTypeFromPseudoDashIndex.
//
//
class TMultiplePseudoDashIndexConverter {
public:
    TMultiplePseudoDashIndexConverter();
    ~TMultiplePseudoDashIndexConverter();
        
    Sint32 GetPseudoDashIndexFromDashLineType(Sint32 lineTypeInternalIndex) const;
    Sint32 GetDashLineTypeFromPseudoDashIndex(Sint16 pseudoLineStyleIndex) const;
};

#endif
