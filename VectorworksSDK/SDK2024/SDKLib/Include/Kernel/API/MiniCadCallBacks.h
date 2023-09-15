//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Declares most of the types specific to the SDK.
//	Includes the file which declares the entire set of SDK functions.
//


#pragma once

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

//const short kUndoNone				=  0;  // obsolete [TTF 04/29/19]
const short kUndoReplaceSelection	= 17;
const short kUndoSwapObjects		= 21;
const short kUndoCustom				= 26;
const short kUndoOnlyViewChange		= 30;
const short kUndoTempPreview		= 31;
//const short kUndoEndEvent			= 50;  // obsolete [MAF 6/29/98]

//////////////////////////////////////////////////////////////////////////////////////////
extern const GSColor kGSColorBlack;
extern const GSColor kGSColorWhite;
extern const GSColor kGSColorRed;
extern const GSColor kGSColorBrightRed;
extern const GSColor kGSColorGreen;
extern const GSColor kGSColorLtGreen;
extern const GSColor kGSColorBlue;
extern const GSColor kGSColorMedBlue;
extern const GSColor kGSColorLtBlue;
extern const GSColor kGSColorLighterBlue;
extern const GSColor kGSColorViolet;
extern const GSColor kGSColorYellow;
extern const GSColor kGSColorLtGray;
extern const GSColor kGSColorLighterGray;


extern const GSColor kGSColor16Black;
extern const GSColor kGSColor16White;


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

enum EDXFGeoRefImportType
{
	kDXFGeoRef_MinimumLegalValue= 0,
	kDXFGeoRef_None				= 0,
	kDXFGeoRef_UseDocument		= 1,
	kDXFGeoRef_User				= 2,
	kDXFGeoRef_UserAndAplly		= 3,	
}; 

enum EDXFBlocksHandlingType
{
	kDXFBlocksHandling_MinimumLegalValue	= 0,
	kDXFBlocksHandling_Normal				= 0,
	kDXFBlocksHandling_GroupsOnly			= 1,
	kDXFBlocksHandling_ExplodeAll			= 2,
	kDXFBlocksHandling_MaximumLegalValue	= 2,
};

enum EDXFLayersHandlingType
{
	kDXFLayersHandling_MinimumLegalValue	= 0,
	kDXFLayersHandling_AllLayers			= 0,
	kDXFLayersHandling_VisibleLayers		= 1,
	kDXFLayersHandling_SelectedLayers		= 2,
	kDXFLayersHandling_MaximumLegalValue	= 2,
};

//////////////////////////////////////////////////////////////////////////////////////////
// Parametric state event sending flags
// Note! You can OR those flags

typedef short TParametricStateFlags;

const TParametricStateFlags kParametricStateEvent_NoStateEvents 		= 0; 
const TParametricStateFlags kParametricStateEvent_ResetStatesEvent		= 1;
const TParametricStateFlags kParametricStateEvent_InternalStatesEvent	= 2;



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
	kConsWP3D			= 9,
#endif
	kConsHorVer			= 10,	//alternate vector constrain mode
	kConsHor 			= 11,	//alternate vector constrain mode
	kConsVer 			= 12,	//alternate vector constrain mode
	kConsSpecialAngle 	= 13,	//alternate vector constrain mode
	kConsSymmetry		= 14,	//alternate vector constrain mode
	kConsParallel		= 15,	//in here for it's old use in tdlist.cpp
#ifdef USE_VW2009_LOGIC_WPCONS_COVERSEDGE
	kConsLockAngle		= 16	//alternate vector constrain mode,always in locked angle mode
#else
	kConsLockAngle		= 16,	//alternate vector constrain mode,always in locked angle mode
	kConsWPNormal3D		= 17
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

	kLAArDxDyXY		= 39,

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
#define kUserDataTypeSize 84
#define kNGNodeTypeSize   80
#define kClassDefTypeSize 188

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

    struct NGNodeType {
        char      reserved[kNGNodeTypeSize];
    };

    struct ClassDefType {
        char      reserved[kClassDefTypeSize];
    };
#endif

// Used in the SDK GetActivePenFont() call
struct ObjectLineType {
	Sint32 	style;
	Uint32 	weight;
};


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

enum {
	kTextCustStyleDiagFraction = 1,
	kTextCustStyleVerticalFraction = 2,
	kTextCustStyleSuperscript = 32,
	kTextCustStyleSubscript = 64
};

struct TextStyleRec {
	double					fHeight;
	double					fAscent;
	short					fFont;
	TStyle					fFace;
	Byte					fCustomStyle;
	ColorRef				fColor;
	WorldCoord				fSize;
	InternalIndex           fTextStyleRef;
	float					fTrackingAdjustment;
};

struct TextRunRec {
	short		stChar;
	short		stIndex;
};

struct TextTabStop {
    WorldCoord  fOffset;
    Byte        fTabAlignment;
};

// text tab alignment
enum {
    kTextLeftTab = 1,
    kTextRightTab = 2,
    kTextCenterTab = 3,
    kTextDecimalTab = 4
};

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

	// Adding new tolerances for use in OnDemandLevelOf Detail - used ONLY by Level Of Detail Support 2020
	kLOD0ConvertToPolyResolution = 1,   // USE ONLY for On Demand LevelOfDetail
	kLOD1ConvertToPolyResolution = 2,   // USE ONLY for On Demand LevelOfDetail
	kLOD2ConvertToPolyResolution = 4,   // USE ONLY for On Demand LevelOfDetail
	kLOD3ConvertToPolyResolution = 8,   // USE ONLY for On Demand LevelOfDetail

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

const Uint16	 kMarkerRootTypeMask = 127;		// && with a MarkerType to get just the RootType ( example: if((myMarkerType && kMarkerRootTypeMask) == kArrowMarker) { doSomething(); } )
const Uint16	 kMarkerFillMask = 896;			// && with a MarkerType to get just the Fill
const Uint16	 kMarkerBaseMask = 7168;		// && with a MarkerType to get just the Base
const Uint16	 kMarkerHalfTickMask = 24576;	// && with a MarkerType to get just the Half-Tick value (0 is a Full marker)
const Uint16	 kMarkerTailMask = 32768;		// && with a MarkerType to get just the Tail value (0 is "not tail")

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

typedef Uint16	 MarkerType;

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
typedef Sint16	 BoundsType;



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
	kFieldLongInt			= 1,
	kFieldBoolean			= 2,
	kFieldReal				= 3,
	kFieldText				= 4,
	kField_UNUSED_5			= 5,
	kField_UNUSED_6 		= 6,
	kFieldCoordDisp			= 7,
	kFieldPopUp				= 8,
	kFieldRadio				= 9,
	kFieldCoordLocX			= 10,	
	kFieldCoordLocY			= 11,
	kFieldStaticText		= 14,
	kFieldControlPoint		= 15,
	kFieldDimStdPopUp		= 16,
	kFieldPrecisionPopUp	= 17,
	kFieldClassesPopup		= 18,
	kFieldLayersPopup		= 19,
	kFieldAngle				= 20,
	kFieldArea				= 21,
	kFieldVolume			= 22,
	kFieldClass				= 23,
	kFieldBuildingMaterial	= 24,
	kFieldFill				= 25,
	kFieldPenStyle			= 26,
	kFieldPenWeight			= 27,
	kFieldColor				= 28,
	kFieldTexture			= 29,
	kFieldSymDef			= 30,
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

// Interctive sizing
const SymbolToolModeType	kSymbolToolInteractiveSizingInsert		= 3;
const SymbolToolModeType	kSymbolToolInteractiveSizingGroup		= 2;	
const SymbolToolModeType	kSymbolToolIntSizingCornerToCornerIndex = 1;
const SymbolToolModeType	kSymbolToolIntSizingCenterToCornerIndex = 2;

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

// The InsertModeType specifies where the symbol is inserted. It is used in both the 
// SymbolBreakType structure and the Get/Set object variable functions for Symbol definitions.

const InsertModeType kSymInsertOnEdge						= -1;	// Insert on the nearest edge of the wall - This is not a valid option for the SymbolBreakType structure
const InsertModeType kSymInsertOnCenter						= 0;	// Insert on the center of the wall
const InsertModeType kSymInsertOnLeftEdge					= 1;	// Insert on the left edge of the wall
const InsertModeType kSymInsertOnRightEdge					= 2;	// Insert on the right edge of the wall
const InsertModeType kSymInsertOnCoreComponentCenter		= 3;	// Insert on the center of the wall core component
const InsertModeType kSymInsertOnCoreComponentLeftEdge		= 4;	// Insert on the left edge of the wall core component
const InsertModeType kSymInsertOnCoreComponentRightEdge		= 5;	// Insert on the right edge of the wall core component
const InsertModeType kSymInsertOnWallInsertLocation			= 6;	// Insert on the wall insert location
const InsertModeType kSymInsertOnWallClosureInsertLocation	= 7;	// Insert on the wall closure insert location


//---------------------------------
typedef short BreakModeType;

// The BreakModeType specifies the kind of break the symbol creates. It is used for in both the 
// SymbolBreakType structure and the Get/Set object variable functions for Symbol definitions.

const BreakModeType kSymFullBreakWithCaps 	= 1;			// lines are drawn over the ends of the wall where broken
const BreakModeType kSymFullBreakNoCaps		= 2;			// no lines to cap the symbol break
const BreakModeType kSymHalfBreak			= 3; 			// for edge insertion only - only one line is broken for the symbol
const BreakModeType kSymNoBreak				= 4;			// wall does not break for the inserted symbol


struct SymbolBreakType {
	MCObjectHandle		theSymbol;		// Handle to the symbol inserted
	Boolean				rightSide;		// Is the symbol oriented to the right side of the wall
	Boolean				flipH;			// Is the symbol flipped toward the first point of the wall
	WorldCoord			height;			// Height of the bottom of the symbol from the ground plane
//	Boolean				capBreakEnds - removed: this functionality has been repleaced by the breakMode field
										
	InsertModeType		insertMode; 	// Which edge is the symbol inserted on
	WorldCoord			locationOffset;	// The offset from the insert location
	BreakModeType		breakMode;		// Break style for the symbol
	Boolean				cornerBreak;	// The symbol will move to the corner
	Boolean				spanBreak;		// The symbol will move to the center of the wall. The symbol itself is responsible for settings the parameters to span the wall
										// span and corner are mutually exclusive
	
	SymbolBreakType(): 					/* constructor sets options for standard center insertion */
		theSymbol(NULL), rightSide(false), flipH(false), height(0.0),  
		insertMode(kSymInsertOnCenter), locationOffset(0.0), breakMode(kSymFullBreakWithCaps),
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
	WorldCoord	peakHeight;		/* Height of the peak from the ground plane */
	Boolean		topPeak;		/* Is the peak on the top face of the wall */
};

// The wall path type
enum EWallPathType
{
	eWallPathType_line,
	eWallPathType_arc
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

// The component insert location
enum EComponentInsertLocation
{
	eComponentInsertLocation_none,
	eComponentInsertLocation_left,
	eComponentInsertLocation_center,
	eComponentInsertLocation_right
};

// The wall closure edge profile shape type
enum EWallClosureEdgeProfileShapeType
{
	eWallClosureEdgeProfileShapeType_straight,
	eWallClosureEdgeProfileShapeType_splay,
	eWallClosureEdgeProfileShapeType_round
};

// The wall closure edge profile shapes info
struct WallClosureEdgeProfileShapesInfo
{
	EWallClosureEdgeProfileShapeType	fExteriorShapeType;
	WorldCoord							fExteriorShapeSplayWidth;
	WorldCoord							fExteriorShapeSplayDepth;
	WorldCoord							fExteriorShapeRoundRadius;
	EWallClosureEdgeProfileShapeType	fInteriorShapeType;
	WorldCoord							fInteriorShapeSplayWidth;
	WorldCoord							fInteriorShapeSplayDepth;
	WorldCoord							fInteriorShapeRoundRadius;
};

// The wall closure edge profile offsets info
struct WallClosureEdgeProfileOffsetsInfo
{
	WorldCoord	fGap;
	WorldCoord	fExteriorOverlap;
	WorldCoord	fExteriorOffset;
	WorldCoord	fInteriorOverlap;
	WorldCoord	fInteriorOffset;
};

// The wall closure edge wrappings info
struct WallClosureEdgeWrappingInfo
{
	WorldCoord	fExteriorWrappedComponentsThicknessOutsideProfile;
	WorldCoord	fExteriorWrappedComponentsThicknessInsideProfile;
	WorldCoord	fInteriorWrappedComponentsThicknessOutsideProfile;
	WorldCoord	fInteriorWrappedComponentsThicknessInsideProfile;
};

// The wall closure info
struct WallClosureInfo
{
	WallClosureEdgeProfileShapesInfo	fLeftEdgeProfileShapesInfo;
	WallClosureEdgeProfileShapesInfo	fRightEdgeProfileShapesInfo;
	WallClosureEdgeProfileShapesInfo	fTopEdgeProfileShapesInfo;
	WallClosureEdgeProfileShapesInfo	fBottomEdgeProfileShapesInfo;
	WallClosureEdgeProfileOffsetsInfo	fLeftEdgeProfileOffsetsInfo;
	WallClosureEdgeProfileOffsetsInfo	fRightEdgeProfileOffsetsInfo;
	WallClosureEdgeProfileOffsetsInfo	fTopEdgeProfileOffsetsInfo;
	WallClosureEdgeProfileOffsetsInfo	fBottomEdgeProfileOffsetsInfo;
	WallClosureEdgeWrappingInfo			fLeftEdgeWrappingInfo;
	WallClosureEdgeWrappingInfo			fRightEdgeWrappingInfo;
	WallClosureEdgeWrappingInfo			fTopEdgeWrappingInfo;
	WallClosureEdgeWrappingInfo			fBottomEdgeWrappingInfo;
};

struct WallClosureGeometryInfo
{
	struct Interval { WorldCoord fMinX, fMaxX; };
	struct FaceInfo { Interval fInterval; WorldCoord fCentroidY; WorldCoord fCentroidHeight;};

	// Generic Solid, can be used for solid additions, subtractions
	MCObjectHandle fCutWallEnvelope;
	// Extent of hole in fCutWallEnvelope, in PIO-local x coordinates,
	// restricted to plane at client-supplied height, specified by PIO-local
	// z-coordinate
	Interval fFullInteriorHoleIntervalAtHeight;
	Interval fFullExteriorHoleIntervalAtHeight;

	// Extents of all top/bottom-tagged faces in hole, in PIO-local
	// x-coordinates, along with the heights, in PIO-local z-coordinates, of
	// each face's center of mass (included to help resolve possible
	// ambiguities)
	std::vector<FaceInfo> fExteriorBottomFaceIntervals;
	std::vector<FaceInfo> fExteriorTopFaceIntervals;
	std::vector<FaceInfo> fInteriorBottomFaceIntervals;
	std::vector<FaceInfo> fInteriorTopFaceIntervals;
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
	MCObjectHandle	sourceHandle = nullptr;
	MCObjectHandle	targetHandle = nullptr;
	bool			copySource = false;
	bool			differentDocument = false;
	bool			transferClassVis = false;
	bool			transferLayerVis = false;
	bool			transferClassOverride = false;
	bool			transferLayerOverride = false;
	bool            transferDataVisualization = false;
	bool			transferRenderProperties = false;
    bool            transferImageEffects = false;
	bool			transferOtherProperties = false;
	bool			deleteTemporaryData = false;
	bool			classDoesNotExist = false;
	bool			layerDoesNotExist = false;
	bool			resourceDoesNotExist = false;
	bool			usingDocClassVisibility =false;
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
	kLightCosine,

	// Caustic Photons
	kLightCausticNone		= 0,
	kLightCausticLow		= 10000,
	kLightCausticMedium		= 100000,
	kLightCausticHigh		= 1000000,
	kLightCausticVeryHigh	= 10000000 
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
	StandardView2D = 1,
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


enum class ESetSpecialGroupErrors {
    NoError,
    CannotSet_BadData,
    CannotSet_UserSpecified,
};

enum class ETopPlanViewComponent {
	Top,
	TopBottomCut
};

//////////////////////////////////////////////////////////////////////////////////////////

const short kShaderMenuItemTextSize = 64;


////// ShaderWidgetType

typedef enum {
	kNoWidget = 0,
	kColorWidget,
	kScaleWidget,
	kPopupWidget,
	kImageWidget,
	kBooleanWidget,
	kCoordLengthWidget,
	kFloatNormalizedEdit,
	kFloatRange0To10Edit,
	kFloatRange0To100Edit,
	kFloatRangeNeg10To10Edit,
	kLongRange0To10Edit,
	kLongRange0To1000Edit,
	kRefractionSlider, 	// 1..3
	kFloatNormalizedSlider,
	kFloatNormalizedNegativeSlider,
	kFloatRange0ToPoint2Slider,
	kFloatRange0ToPoint5Slider,
	kFloatRange0To5Slider,
	kFloatRange0To10Slider,
	kFloatRange0To100Slider,
	kLongRange0To10Slider,
	kLongRange0To20Slider,
	kLongRange1To6Slider,
	kFloatNormalizedPercentEdit,
	kRefractionEdit // 1...3

} EShaderWidgetType;


typedef union
{
	GSColor fColor;
	float fFloat;
	Sint32 fLong;
	bool fBool;
	WorldCoord fCoord;
	
} ShaderParamValue;


class ShaderParameter
{
	public:
		ShaderParameter(const TXString& prompt, const TXString& help, EShaderWidgetType type, ShaderParamValue value)
			:fPrompt(prompt), fHelp(help), fType(type), fValue(value) {}
		ShaderParameter() { fType = kNoWidget; }
		
		TXString GetPrompt() { return fPrompt; }
		TXString GetHelp() { return fHelp; }
		EShaderWidgetType GetType() { return fType; }
		ShaderParamValue GetValue() { return fValue; }
		
		void SetValue(const GSColor& color) { fValue.fColor = color; }
		void SetValue(float floatValue) { fValue.fFloat = floatValue; }
		void SetValue(Sint32 longValue) { fValue.fLong = longValue; }
		void SetValue(bool boolValue) { fValue.fBool = boolValue; }
		void SetValue(WorldCoord coordValue) { fValue.fCoord = coordValue; }
		
	protected:
		TXString fPrompt;
		TXString fHelp;
		EShaderWidgetType fType;
		ShaderParamValue fValue;
};

typedef ShaderParameter* ShaderParameterList;


struct ShaderParams
{
	short fNumParams;
	ShaderParameterList fParam;

	ShaderParams() { fNumParams = 0; fParam = nil; }
	ShaderParams(short numParams, ShaderParameterList param) 
				{ fNumParams = numParams; fParam = param; }
};

//////////////////////////////////////////////////////////////////////////////////////////

struct SymbolImgInfo
{
	Sint32					fWidth;
	Sint32					fHeight;
	Sint32					fMargin;
	TStandardView			fStandardView;
	TRenderMode				fRenderMode;
	EImageViewComponent		fImgComponent;
	ELevelsOfDetail			fLevelsOfDetail;
	bool					fScaleByZoom;
    bool                    fTransparentBackground;

	SymbolImgInfo(Sint32 width, Sint32 height, Sint32 margin, TStandardView	view, TRenderMode renderMode, EImageViewComponent imgComponent, ELevelsOfDetail levelsOfDetail, bool scaleByZoom, bool transparentBg = false)
		: fWidth(width), fHeight(height), fMargin(margin), fStandardView(view), fRenderMode(renderMode), fImgComponent(imgComponent), fLevelsOfDetail(levelsOfDetail), fScaleByZoom(scaleByZoom),
            fTransparentBackground(transparentBg) {};
    
	SymbolImgInfo(TStandardView	view, TRenderMode renderMode, EImageViewComponent imgComponent, ELevelsOfDetail levelsOfDetail, bool scaleByZoom, bool transparentBg = false) : SymbolImgInfo(-1, -1, -1, view, renderMode, imgComponent, levelsOfDetail, scaleByZoom, transparentBg) {};

	SymbolImgInfo() : SymbolImgInfo(-1, -1, -1, 2/*TopPlan*/, 0/*Wireframe*/, EImageViewComponent::StandardView2D, ELevelsOfDetail::Medium, false /*sizing is done by layer scale*/, false) {};
    
};

struct SymbolImgTransformInfo
{
	TransformMatrix			fScreenMatrix;

	double					fWorldToViewFactor;
	XViewCoord				fWorldToViewXOffset;
	XViewCoord				fWorldToViewYOffset;

	SymbolImgTransformInfo(TransformMatrix screenMatrix, double worldToViewFactor, XViewCoord worldToViewXOffset, XViewCoord worldToViewYOffset) 
		: fScreenMatrix(screenMatrix), fWorldToViewFactor(worldToViewFactor), fWorldToViewXOffset(worldToViewXOffset), fWorldToViewYOffset(worldToViewYOffset) {};
	SymbolImgTransformInfo() : fWorldToViewFactor(1), fWorldToViewXOffset(0), fWorldToViewYOffset(0) { fScreenMatrix.SetToIdentity(); };
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
	DDMMYYYY_TIME				= 36,
    YYMMDD						= 37,
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
struct TDateTimeData
{
	Uint32	fYear;
	Uint32	fMonth;
	Uint32	fDay;
	Uint32	fHour;
	Uint32	fMinute;
	Uint32	fSecond;
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



#define GS_COMPATIBILITY
#define GS_LIBRARY


//////////////////////////////////////////////////////////////////////////////////////////

extern "C" {
	typedef Boolean (*GS_ForEachBreakProcPtr)(MCObjectHandle h, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData, CallBackPtr cbp, void* env);
	typedef void (*GS_I2DDrawProcPtr)(const WorldPt& startPt, const WorldPt& drawPt, CallBackPtr cbp, void *env);
	typedef void (*GS_ForEachObjectProcPtr)(MCObjectHandle h, CallBackPtr cbp, void *env);
	typedef bool (*GS_3DPointIteratorProcPtr)(WorldPt3 point3D, CallBackPtr cbp, void* env);	// XXX_JDW_MISC - i think bool is illegal in SDK, and also unused in these functions
	typedef void (*GS_ForEachPolyEdgeProcPtr)(const WorldPt& inStartPt, const WorldPt& inControlPt, const WorldPt& inEndPt, WorldCoord inRadius, VertexType inType, Sint8 inVisible, CallBackPtr inCBP, void* inEnv);
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
	
	const Sint16 kKludgeHandleIncomingFilePath = 3650;
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

	const Sint16 kAddSurfaceKludge = 5555;
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

	const Sint16 kEnterGroups = 5556;

	//
	// --------------------------------------------------------
	// kludge used for initializing and setting the
	// hidden plant record
	// --------------------------------------------------------
	//

	const Sint16 kSetAndGetHiddenPlantRecord = 5557;
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

	const Sint16 kCreatePlantRecord = 5558;

	//
	// --------------------------------------------------------
	// kludge used from the plugin to tell if object is 
	// a plant object or not
	// --------------------------------------------------------
	//

	const Sint16 kIsPlantObject = 5559;
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

	const Sint16 kIsEditingPlantID = 5560;
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

	const Sint16 kChange3DViewForPlant = 5561;

	// 
	// --------------------------------------------------------
	// kludge used to set the height/width of the image prop
	// from inside the plant object
	// --------------------------------------------------------
	//

	const Sint16 kSetImagePropStuff = 5562;
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

	const Sint16 kEditPlantPath = 5563;

	//
	// --------------------------------------------------------
	// kludge used for setting the symbol type of the plant
	// --------------------------------------------------------
	//

	const Sint16 kSetPlantSymbolType = 5564;
	struct plantSymbolTypeStuff{
		MCObjectHandle plant;
		short symbolType;
	};

	//
	// --------------------------------------------------------
	// kludge used for setting timestamp of plant symbols
	// --------------------------------------------------------
	//

	const Sint16 kSetPlantSymbolTimeStamp = 5565;

	//
	// --------------------------------------------------------
	// kludge used for refreshing the resource browser
	// --------------------------------------------------------
	// 

	const Sint16 kRefreshResourceBrowser = 5566;

	// 
	// --------------------------------------------------------
	// kludge used for the plant object when creating a new
	// image prop for the 3d symbol portion of a plant
	// --------------------------------------------------------
	//    

	const Sint16 kCreatePlantImageProp = 5567;
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

	const Sint16 kUpdatePriceInPlantRecord = 5568;

	//
	// --------------------------------------------------------
	// kludge used when the dtm modifier record has to be 
	// attached to a poly so that the landscape area can 
	// be a texture bed on the dtm
	// --------------------------------------------------------
	//

	const Sint16 kCreateDTMModifierRecord			= 5569;
	const Sint32 kDTMModifierRecordStringIndex		= 259;
	const Sint32 kDTMModifierRecord_recordName		= 1;
	const Sint32 kDTMModifierRecord_type			= 2;
	const Sint32 kDTMModifierRecord_deltaz			= 3;
	const Sint32 kDTMModifierRecord_riseOverRun		= 4;
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

	const Sint16 kCorrectPlantDefinition = 5574;

	// 
	// --------------------------------------------------------
	// kludge that checks for a "New" or "Window" menu command
	// inside the plant tool
	// --------------------------------------------------------
	//

	const Sint16 kCheckMenuForPlantTool = 5575;

	//
	// --------------------------------------------------------
	// kludge that sets it so the image popup in the plant tool
	// will unpopup when there is a resource conflict when
	// importing from default content
	// --------------------------------------------------------
	//

	const Sint16 kSetUnpopupValueForPlantTool = 5576;

	// 
	// --------------------------------------------------------
	// kludge used to get the unpopup global variable
	// for the plant tool image popup issue
	// --------------------------------------------------------
	//

	const Sint16 kGetUnpopupValueForPlantTool = 5577;

	//
	// --------------------------------------------------------
	// kludge used to transfer attributes from one dimension
	// to another dimension
	// --------------------------------------------------------
	
	const Sint16 kCopyDimensions	= 5578;
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

	const Sint16 kGetSelectionBoxSize = 5579;

	//
	// --------------------------------------------------------
	// kludge used to remove all the "all by class" flags
	// --------------------------------------------------------
	//

	const Sint16 kClearAllByClassFlags = 5570;

    const Sint16 kIntersectSurfaceKludge = 5571;
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
    const Sint16 kKludgeNotifyAny = 5573;
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

	const Sint16 kKludgeDrawGrayDashed2DLine = 4007;
	struct DrawGrayDashed2DLineStuff  {
		WorldPt pt1;
		WorldPt pt2;
	};

	const Sint16 kKludgeCalcWitLineEndPts = 4008;
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

	const Sint16 kKludgeMakeTempGraphicalCopy = 4010;
	struct MakeTempGraphicalCopyInformation {
		MCObjectHandle handleToCopy;
		MCObjectHandle result;
	};

	//
	//---------------------------------------------------------
	// kludge used to get and set the frac mat of a parametric object, this is for internal use only
	//---------------------------------------------------------
	//

	const Sint16 kKludgeGetAndSetParametricFracMat = 4011;
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
	
	enum EKeyCode	// key codes by OS
	{
	#ifdef _WINDOWS
		KeyCode_Return	= 0x0D,
		KeyCode_Escape	= 0x1B,
		KeyCode_Back	= 0x08,
		KeyCode_Tab		= 0x09,
	#else
		KeyCode_Return	= 0x24,
		KeyCode_Escape	= 0x35,
		KeyCode_Tab		= 0x30,
	#endif
	};

	const Sint16 kKludgeSendDataForKeyEvent = 4014;
	struct TDialogKeyDownEvent {
		Uint32 keyCode; // platform-specific virtual keycode. See EKeyCode
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
	
	const Sint16 kKludgeGetTextTightFillPoly = 5604;
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
	const Sint16 kKludgeEnterAndExitFromGroup = 5614;
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
	const Sint16 kRunCatalogBuilderDialog = 5621;
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
	const Sint16 kKludgeIsFailedCSGAction = 5625;

	//-------------------------------------------------------------------------------------
	// kludge that checks if a string is Vectorworks reserved word
	//-------------------------------------------------------------------------------------

	const Sint16 kIsRefNameSystemReserved = 5626;

	//----------------------------------------------------------------------------------
	// kludge that inverts an image.
	//----------------------------------------------------------------------------------

	const Sint16 kInvertImage = 5631;

	//
	// -------------------------------------------------------
	// kludge used to highlight/ unhighlight a Callout leader line
	//--------------------------------------------------------
	//

	const Sint16 kKludgeActionHighlightingObject = 5632;

	struct ActionHighlightingObjectInformation {
		Boolean				bAddObject;
		MCObjectHandle		handleToObject;
	};
    
    //-------------------------------------------------------------------------------------
    // kludge that generates ImageDefNode for enlarged QR code
    //-------------------------------------------------------------------------------------
    
    const Sint16 kDrawEnlargedQRFromArray = 6021;
    
    struct QRCodeInfo {
        std::vector<int> fBitArray;
        int fSize;
    };
    
    
    //-------------------------------------------------------------------------------------
    // kludge that generates an image from the incoming QR code info and copy to clipboard
    //-------------------------------------------------------------------------------------
    
    const Sint16 kCopyQRImageToClipboard = 6022;

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
const OSType kTaggedDataContainerNNA_Internal44 = 'iesd'; // IES file data stream
const OSType kTaggedDataContainerNNA_Internal45 = 'cvym'; // curvy mesh
const OSType kTaggedDataContainerNNA_Internal46 = 'pksf'; // composite surface parasolid data, see CachedCompositeSurfaceBodyInfo.
const OSType kTaggedDataContainerNNA_Internal47 = 'glst'; // OpenGL options for render style data
const OSType kTaggedDataContainerNNA_Internal48 = 'prst'; // plugin renderer options for render style data
const OSType kTaggedDataContainerNNA_Internal49 = 'rwft'; // Face Texture Map (Render Works Face Texture = rwft)
const OSType kTaggedDataContainerNNA_Internal50 = 'rdxo'; // Render Data Extra Options


//	TaggedData data type IDs used in GS_TagggedData## APIs:
const Sint32 kTaggedDataByteArrayTypeID = 1;		
const Sint32 kTaggedDataFlagsContainerTypeID = 2;	
const Sint32 kTaggedDataDoubleArrayTypeID = 6;		
const Sint32 kTaggedDataTramsformMatrixTypeID = 7;
const Sint32 kTaggedDataUint32ArrayTypeID = 8;	
const Sint32 kTaggedDataColorRefArrayTypeID = 13;	
const Sint32 kTaggedDataObjectRefArrayTypeID = 15;	// The maplist will take care of mapping these RefNumbers when the TaggedData is moved to
													// another document, unless the auxOwner of the TaggedData node is a parametric node that
													// has implemented the IProviderDataRefNumber extension. The IProviderDataRefNumber extension
													// is needed if the reference is "two-way", such as an association between two objects.
const Sint32 kTaggedDataPlanarRefArrayTypeID = 17;
const Sint32 kTaggedDataTransformMatrixArrayTypeID = 18;
const Sint32 kTaggedDataWorldPt3ArrayTypeID = 20;
const Sint32 kTaggedDataFloatPt3ArrayTypeID = 21;
const Sint32 kTaggedDataWallComponentJoinElevationsArrayTypeID = 22;
const Sint32 kTaggedDataRefNumberArrayTypeID = 23;


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
// *fOriginalSelectedObjs contains the original selected objects
{
	Boolean						fbIs3DMove;
	TransformMatrix				fTransformOffset;
	std::unordered_set<MCObjectHandle> fOriginalSelectedObjs = {};
	bool						fIsAllObjectMoving;
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
	bool			fObjectNeedsReset;
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
struct ObjectStateData_BuildingMaterialChanged {
	InternalIndex	fMaterialRef;
	bool			fDeleted;
	InternalIndex	fPreviousFillIndex;
	ObjectColorType	fPreviousFillColors;
	bool			fPreviousFillByClass;
	InternalIndex	fPreviousTexture;
};

//----------------------------------------------------------
struct ObjectStateData_Undo
// StateData for kObjectUndoRestore, kObjectUndoRemove, kObjectUndoModify
{
	bool		fbConstructingPrimitive;
};

//----------------------------------------------------------
struct ObjectStateData_ObjectPlanarRefChanged
// StateData for object planar ref change
{
	bool		fbIsScreenObject;
};

//----------------------------------------------------------
struct ObjectStateData_Delete
// StateData for kObjectDeleteBefore
{
	bool		fbJustMovingToAnotherLayer;
};

//----------------------------------------------------------
enum EStateObjectCreationContext
{
    eContext_Unknown = 0,
    eContext_Duplicated = 1,
    eContext_NewlyCreated = 2
};

//----------------------------------------------------------
enum EStateObjectDuplicationContext
{
	eContext_DupUnknown		= 0,
	eContext_DupRefUpdate	= 1,
	eContext_DupShareUpdate	= 2,
	eContext_DupImport		= 3,
};

//----------------------------------------------------------
struct ObjectStateData_ObjectCreated
// StateData for object creation
{
    ObjectStateData_ObjectCreated(){ fContext = eContext_Unknown; fDupContext = eContext_DupUnknown;}
    ObjectStateData_ObjectCreated(const EStateObjectCreationContext inContext){ fContext = inContext; fDupContext = eContext_DupUnknown;}
    ObjectStateData_ObjectCreated(const EStateObjectCreationContext inContext,  EStateObjectDuplicationContext inDupContext)
    { fContext = inContext; fDupContext = inDupContext;}
    
    EStateObjectCreationContext fContext;
    EStateObjectDuplicationContext fDupContext;
};

struct ObjectStateData_ObjectIsGeneratedBy
// State Data for generation of object from another object of same type.
{
	typedef TXGenericArray<Sint32>	TRefNumArray;

	enum class EOperationType
	{
		Unknown,
		Add,
		Clip,
		Split,
	};

	ObjectStateData_ObjectIsGeneratedBy(EOperationType opType = {}, const TRefNumArray &arr = {}) : fOperationType(opType), farrRefNumbers(arr) {};

	EOperationType					fOperationType;
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

// End "Private" Callback section
//=====================================================================================
//////////////////////////////////////////////////////////////////////////////////////////







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
	CustomBarRefID	fCustomBarID;
	short 			fFieldIndex;
	TXString		fUserLockString;
};

#include "VWVariant.h"

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
	TXString	fObjectNameUniversal;
	short		fOldVersionNum;					// this is a Vectorworks version, e.g. 24, 25, 26, etc. (FYI 26 = Vectorworks 2020)
};

struct KludgeObjectResetAfterTranslateExt
{
	TXString	fObjectNameUniversal;
	short		fOldVersionNum;				// this is a Vectorworks version, e.g. 24, 25, 26, etc. (FYI 25 = Vectorworks 2020)
	short		fOldBugFixVersionNum;
};

//	---------------------------------------------------------------------------------------
//	---------------------------------------------------------------------------------------

/*!
 *  Generic class from which all data containers
 *   that are employed to transmit data between
 *   application/SDK/UI components are to be
 *   derived
 */
class CGSBaseDataContainer
{
public:
	using DocumentId = short;

    CGSBaseDataContainer();
	virtual ~CGSBaseDataContainer() = 0;

	DocumentId GetDocumentId() const { return m_documentId; }

protected:
	DocumentId m_documentId;
};

/*!
 *  Class that encapsulates a string
 *   value change (specification of
 *   the original string value may
 *   be necessary for some clients)
 */
class CGSStringValueChange : public CGSBaseDataContainer
{
public:
    CGSStringValueChange();
    CGSStringValueChange(const TXString& oldStringValue, const TXString& newStringValue);
    virtual ~CGSStringValueChange();
    
    TXString fOldStringValue;
    TXString fNewStringValue;
};

/*!
 *  Class that encapsulates an integral
 *   value change
 */
class CGSIntValueChange : public CGSBaseDataContainer
{
public:
    CGSIntValueChange();
    CGSIntValueChange(const Sint32 value);
    virtual ~CGSIntValueChange();
    
    Sint32 fValue;
};

/*!
 *  Class that encapsulates a multi-state
 *   value change between attribute
 *   existence states (applicable to
 *   mutli-state checkbox-type interfaces,
 *   etc.)
 */
class CGSMultiStateValueChange : public CGSBaseDataContainer
{
public:
    
    typedef enum
    {
        eStateValueOff = 0,
        eStateValueOn,
		eStateValueIndeterminate
	}
    EStateValue;
    
    CGSMultiStateValueChange();
    CGSMultiStateValueChange(const EStateValue stateValue);
    virtual ~CGSMultiStateValueChange();
    
    EStateValue fStateValue;
};

/*!
 *  Class that represents a value change
 *   for a value that is clamped to a
 *   specific, inclusive integral range
 */
class CGSRangedValueChange : public CGSIntValueChange
{
public:
    CGSRangedValueChange();
    CGSRangedValueChange(const Sint32 value, const Sint32 minValue, const Sint32 maxValue);
    virtual ~CGSRangedValueChange();
    
    Sint32 fMinimumValue;
    Sint32 fMaximumValue;
};

/*!
 *  Class that encapsulates a color
 *   attribute value change
 */
class CGSColorValueChange : public CGSBaseDataContainer
{
public:
    CGSColorValueChange();
    CGSColorValueChange(const ColorRef newColor, const ColorRef specialIndex);
    virtual ~CGSColorValueChange();
    
    ColorRef            fNewColor;
    ColorRef            fSpecialIndex;
};

/*!
 *  Class that encapsulates a pattern
 *   attribute value change
 */
class CGSPatternValueChange : public CGSBaseDataContainer
{
public:
    CGSPatternValueChange();
    CGSPatternValueChange(const Sint32 newPattern, const bool bLocalMapping = false);
    virtual ~CGSPatternValueChange();
    
    Sint32  fNewPattern;
    bool    fbLocalMapping;             //True if the instance for the selected object is locally mapped.
};

/*!
 *  Class that encapsulates a pattern
 *   attribute change, with
 *   accompanying foreground/background
 *   color specification
 */
class CGSPatternWithColorValueChange : public CGSBaseDataContainer
{
public:
    CGSPatternWithColorValueChange();
    CGSPatternWithColorValueChange(const CGSColorValueChange& newForegroundColor,
        const CGSColorValueChange& newBackgroundColor,
        const CGSPatternValueChange& newPattern);
    virtual ~CGSPatternWithColorValueChange();
    
    CGSColorValueChange fForegroundColor;
    CGSColorValueChange fBackgroundColor;
    CGSPatternValueChange fPatternValueChange;
};

/*!
 *  Class that encapsulates a hatch
 *   attribute value change (specification
 *   of the original hatch value may
 *   be necessary for some clients)
 */
class CGSHatchStyleValueChange : public CGSBaseDataContainer
{
public:
    CGSHatchStyleValueChange();
    CGSHatchStyleValueChange(const InternalIndex newHatchStyle, const InternalIndex oldHatchStyle);
    virtual ~CGSHatchStyleValueChange();
	InternalIndex    fNewHatchStyle;           //New hatch pattern index.
	InternalIndex    fOldHatchStyle;           //Old hatch pattern index.
};

/*!
 *  Class that encaspulates a gradient
 *   attribute value change
 */
class CGSGradientValueChange : public CGSBaseDataContainer
{
public:
    CGSGradientValueChange();
    CGSGradientValueChange(const InternalIndex newGradient);
    virtual ~CGSGradientValueChange();
    InternalIndex    fNewGradient;
};

/*!
 *  Class that encaspulates an image
 *   resource attribute value change
 */
class CGSImageResourceValueChange : public CGSBaseDataContainer
{
public:
    CGSImageResourceValueChange();
    CGSImageResourceValueChange(const InternalIndex newImageResource);
    virtual ~CGSImageResourceValueChange();
	InternalIndex fNewImageResource;
};

/*!
 *  Class that encaspulates a tile
 *   resource attribute value change
 */
class CGSTileResourceValueChange : public CGSBaseDataContainer
{
public:
    CGSTileResourceValueChange();
    CGSTileResourceValueChange(const InternalIndex newTileResource);
    virtual ~CGSTileResourceValueChange();
	InternalIndex fNewTileResource;
};

/*!
 *  Class that encaspulates a resource
 *   attribute value change
 */
class CGSResourceValueChange : public CGSBaseDataContainer
{
public:
	CGSResourceValueChange();
	virtual ~CGSResourceValueChange();
	//InternalIndex fNewResource;	// Not needed, use resource manager content pointer to get/modify selected item
									// This cell type will not automatically import the selected resource, so import it if needed
};

/*!
 *  Class that encapsulates a line type
 *   change value
 */
class CGSLineTypeValueChange : public CGSBaseDataContainer
{
public:
    CGSLineTypeValueChange();
    CGSLineTypeValueChange(const InternalIndex newLineType);
    virtual ~CGSLineTypeValueChange();
	InternalIndex fNewLineType;
};

/*!
 *  Class that encapsulates a line weight/
 *   thickness change value
 */
class CGSLineWeightValueChange : public CGSBaseDataContainer
{
public:
    CGSLineWeightValueChange();
    CGSLineWeightValueChange(const short newLineWeight, const bool bWeightByClass = false);
    virtual ~CGSLineWeightValueChange();
    short fNewLineWeightValue;
    bool fbWeightByClass;
};

/*!
 *  Class that encapsulates a line end/
 *   change value
 */
class CGSLineEndValueChange : public CGSBaseDataContainer
{
public:
	CGSLineEndValueChange();
	CGSLineEndValueChange(const SMarkerStyle newMarkerStyle, const bool bMarkerByClass = false);
	virtual ~CGSLineEndValueChange();
	SMarkerStyle fNewMarkerStyle;
	bool fbMarkerByClass;
};

class CGSMenuItemValue;
/*!
 *  Class that encapsulates a collection of
 *   items that constitute a menu or a
 *   submenu
 */
class CGSMenuItemCollection : public CGSBaseDataContainer
{
public:

    CGSMenuItemCollection();
    CGSMenuItemCollection(const CGSMenuItemCollection& menuItemCollection);
    virtual ~CGSMenuItemCollection();
    bool AddMenuItem(const CGSMenuItemValue& menuItemValue);
    unsigned int GetMenuItemCount() const;
    const CGSMenuItemValue* GetMenuItemAtIndex(
        const unsigned int menuItemIndex) const;
	bool RemoveMenuItemAtIndex(const unsigned int menuItemIndex);
    
    void operator=(const CGSMenuItemCollection& sourceMenuItemValue);
    bool operator==(const CGSMenuItemCollection& referenceItemValue);
    
protected:
    void RemoveAllMenuItems();
    
    std::vector<CGSMenuItemValue*> fMenuItemCollection;
};

/*!
 *  Class that encapsulates a single menu item
 */
class CGSMenuItemValue : public CGSBaseDataContainer
{
public:
    CGSMenuItemValue();
    CGSMenuItemValue(const CGSMenuItemValue& menuItemValue);
    CGSMenuItemValue(const TXString& menuItemName, const Sint64 menuItemId);
    CGSMenuItemValue(const TXString& menuItemName, const TXString& menuItemIdStr);
    CGSMenuItemValue(const TXString& menuItemName, const Sint64 menuItemId, const TXString& menuItemIdStr, const double menuItemIdDbl);
	CGSMenuItemValue(const TXString& menuItemName, const Sint64 menuItemId, const TXString& menuItemImageSpec);
    CGSMenuItemValue(const bool bIsSeparator);
    virtual ~CGSMenuItemValue();

    void AddSubMenu(const CGSMenuItemCollection& subMenu);
    
    bool IsItemEnabled() const;
    bool IsItemChecked() const;
    void SetEnabledState(const bool bEnabledState);
    void SetCheckedState(const bool bCheckedState);
    
    TXString fMenuItemName;
    TXString fMenuItemImageSpec;
    // Numeric and string identifiers - these values exist
    // in order to accommodate either numeric or string
    // identifiers. However, they are not mutually exclusive
    Sint64 fMenuItemId;
    double fMenuItemIdDbl;
    TXString fMenuItemIdStr;
    bool fbIsSeparator;
    
    void operator=(const CGSMenuItemValue& sourceMenuItemValue);
    bool operator==(const CGSMenuItemValue& referenceItemValue);
    
protected:
    
    typedef enum
    {
        eStateDisabled,
        eStateChecked
    }
    EMenuItemStates;
    
    std::set<EMenuItemStates> fMenuItemState;
    CGSMenuItemCollection fSubMenu;
};

/*!
 *  Class that encapsulates a single item
 *   within a list-type collection
 */
class CGSListItemValue : public CGSBaseDataContainer
{
public:
    CGSListItemValue();
    CGSListItemValue(const TXString& itemName, const Sint64 itemIdentifier,
        const Uint32 itemIndex);
    CGSListItemValue(const TXString& itemName, const TXString& itemIdentifierStr,
        const Uint32 itemIndex);
    CGSListItemValue(const TXString& itemName, const Sint64 itemIdentifierNum,
        const TXString& itemIdentifierStr, const Uint32 itemIndex);
    CGSListItemValue(const TXString& itemName, const Sint64 itemIdentifierNum,
                     const TXString& itemIdentifierStr, const double itemIdentifierDbl, const Uint32 itemIndex);
    virtual ~CGSListItemValue();
    
    TXString fItemName;
    // Numeric and string identifiers - these values exist
    // in order to accommodate either numeric or string
    // identifiers. However, they are not mutually exclusive
    Sint64 fItemIdentifier;
    double fItemIdentifierDbl;
    TXString fItemIdentifierStr;
    Uint32 fItemIndex;
};


/*!
*  Class that encapsulates a data source for the class pulldown to provide all the data in the pulldown and 
*  allows developers to select an item and add proposed items to the pulldown.
*/

// Forwward declarations
class ICGSClassAndLayerPulldownCollection;
class IVWUnknown;

class CGSClassAndLayerPulldownCollection : public CGSBaseDataContainer
{
public:
	CGSClassAndLayerPulldownCollection(VCOMPtr<ICGSClassAndLayerPulldownCollection> data);
	
	virtual ~CGSClassAndLayerPulldownCollection();

	VCOMPtr<ICGSClassAndLayerPulldownCollection> fpPulldownInterface;
};

/*!
*  Class that defines the interface for developers to add proposed items and set the active item.  Developers will 
*  talk to this interface through the fpPulldownInterface pointer in class CGSClassAndLayerPulldownCollection;
*/
class ICGSClassAndLayerPulldownCollection : public IVWUnknown
{
public:
	virtual bool AddProposedItem(const TXString& itemIDStr, const TXString& strName, const TXString& toolTip, const TXString& imageSpec) = 0;

	virtual bool SetActiveItem(bool isStaticItem, const TXString& staticItemIDStr, const Sint64 itemIDNum) = 0;

	virtual void ShowStaticPane(bool bShow) = 0;
};

/*!
*  Class that encapsulates a data source for the class pulldown to provide all the data in the pulldown
*/
class CGSClassAndLayerPulldownItemValue : public CGSBaseDataContainer
{
public:
    CGSClassAndLayerPulldownItemValue();
	CGSClassAndLayerPulldownItemValue(const TXString& itemName, bool itemIsProposed, const TXString& proposedItemIDStr, Sint32 itemInternalIndex, bool itemIsNew);
    virtual ~CGSClassAndLayerPulldownItemValue();

	TXString		fItemName;				// This is the name of the class or layer that was selected in the pulldown.  This will always be a valid string.  This is the same as 
											// an InternalName.
    
	bool			fItemIsProposed;		// The class and layer pulldowns have regular items in the list and proposed items that appear at the top of the list,
											// such as <Object Class>.  If a proposed item is selected then this flag will be TRUE and you should use the fProposedItemIDStr to
											// identify which proposed item was selected.

    TXString		fProposedItemIDStr;		// If fItemIsProposed is TRUE, use this to identify which proposed item was selected.

    Sint32			fItemInternalIndex;		// If fItemIsProposed is FALSE, use this to identify the index of the selected class or layer.  This is the same as an InternalIndex.

	bool			fItemIsNew;				// This flag is set to TRUE if the internal index of the selected class or layer was just created as part of the user's action.
											// If the user selects the New Class... or New Design Layer... or New Sheet Layer... items, the control will take care of creation, and
											// the internal index that is passed back will be that of the new item.  In that case this flag is used to alert the dialog handler that 
											// the item is new in case they need to do any extra work.
};

// Forwward declarations
class ICGSSearchablePulldownCollection;
class IVWUnknown;

class CGSSearchablePulldownCollection : public CGSBaseDataContainer
{
public:
	CGSSearchablePulldownCollection(VCOMPtr<ICGSSearchablePulldownCollection> data);

	virtual ~CGSSearchablePulldownCollection();

	VCOMPtr<ICGSSearchablePulldownCollection> fpPulldownInterface;
};

/*!
*  Class that defines the interface for developers to add proposed items and set the active item.  Developers will
*  Class that defines the interface for developers to add proposed items and set the active item.  Developers will
*  talk to this interface through the fpPulldownInterface pointer in class CGSClassAndLayerPulldownCollection;
*/
class ICGSSearchablePulldownCollection : public IVWUnknown
{
public:
	virtual bool SetActiveItemWithIndex(const Sint64& inIndex) = 0;
	virtual bool SetActiveItemWithName(const TXString& inName) = 0;
	virtual bool SetActiveItemWithID(const TXString& inStringID) = 0;

	virtual bool AddItem(const TXString& itemIDStr, const TXString& itemName, const TXString& toolTip, const TXString& imageSpec) = 0;
	virtual bool AddChildItem(const TXString& itemIDStr, const TXString& itemName, const TXString& parentIDStr, const TXString& toolTip, const TXString& imageSpec) = 0;
	virtual bool AddHeaderItem(const TXString& itemName, const TXString& toolTip, const TXString& imageSpec) = 0;
	virtual bool AddStaticItem(const TXString& itemIDStr, const TXString& itemName, const TXString& toolTip, const TXString& imageSpec) = 0;

	virtual void EnableItemWithIndex(const Sint64& inIndex, bool enableItem) = 0;
	virtual void EnableItemWithName(const TXString& inName, bool enableItem) = 0;
	virtual void EnableItemWithID(const TXString& inStringID, bool enableItem) = 0;

	virtual void RemoveAllItems() = 0;
};

/*!
*  Class that encapsulates a data source for the class pulldown to provide all the data in the pulldown
*/
class CGSSearchablePulldownItemValue : public CGSBaseDataContainer
{
public:
	CGSSearchablePulldownItemValue();
    CGSSearchablePulldownItemValue(const TXString& itemName, const TXString& itemStringID, Sint32 itemIndex);
	virtual ~CGSSearchablePulldownItemValue();

	TXString		fItemName;				// This is the name of the item selected in the pulldown.
	TXString		fItemStringID;			// This is the string ID of the item selected in the pulldown.
	Sint32			fItemIndex;				// This is the numerical index of the item selected in the pulldown.
};


////////////////////////////////////////////////////////////////////////////////////////
// LayoutManager Proc Ptrs and constants
////////////////////////////////////////////////////////////////////////////////////////

typedef void (*GS_EventHandlerProcPtr)(Sint32 dlogID, Sint32& itemHit, void* data, void* env);


const Sint16 kSingleLine 		= -1;
const Sint16 kAlignModeResize 	= 0;
const Sint16 kAlignModeShift	= 1;
const Sint32 kDefaultButtonID	= 1;
const Sint32 kCancelButtonID	= 2;
const Sint32 kLeftButtonID		= 12605; // kHelpTextID + 1		 // kHelpTextID = kMaxControlID+2604;
const Sint32 kBackButtonID      = 12606; // kLeftButtonID + 1
const Sint32 kNextButtonID      = 12607; // kBackButtonID + 1
const Sint32 kSetupMessage 		= -12605;
const Sint32 kSetdownMessage 	= -12607;
const Sint32 kResizeMessage		= -12608;	// Sent whenever LM dialog has been resized by user
const Sint32 kDoubleClickInMLEdit = -12611;
const Sint32 kDialogTimerEventMessage = -12612;
const Sint32 kThumbnailPopupClose = -12613;
const Sint32 kEditLostFocusMessage = -12614;

const Sint32 kBeginDragMessage			= -12624;			// data param for this is Sint32* pointing to controlID that started drag - set to 0 to disallow
const Sint32 kDragCanBeginMessage		= -12627;			// parameter to determine if a drag can begin
const Sint32 kDragOverMessage			= -12625;			// data param for this is DragMessageData*
const Sint32 kDropMessage				= -12626;			// data param for this is control-dependent; *(Sint32*)data should always be control being dropped on

const Sint32 kCanEditLabelMessage		= -12629;			// determine if an item's label can be edited
const Sint32 kEditLabelCompleteMessage	= -12630;			// called when editing of a label completed
const Sint32 kCanDeleteItemMessage		= -12631;			// determine if an item in a tree/list browser can be deleted
const Sint32 kDeletedItemMessage		= -12632;			// an item was deleted

const Sint32 kBeforeResizeMessage		= -12640;
const Sint32 kAfterResizeMessage		= -12641;

const Sint32 kKeyDownEventMessage		= -12745;

const Sint32 kGenericLbItemMessage        = -12760;           // Data being transmitted is a TItemMessageData structure (List Browser)

// this is a generic structure that can be used to confirm per-item operations with the List Browser, Tree Control, etc.
struct TItemMessageData
{
    TItemMessageData() :
        fMessageDataId(0),
        fControl(0),
        fItemId(0),
        fAuxiliaryItemData(0),
        fpLegacyItemData(nullptr),
		fReturnCode(0)
	{}
    
    TItemMessageData(const Sint32 control, const Sint32 itemId, const Sint32 auxiliaryItemData, std::unique_ptr<CGSBaseDataContainer>&& itemChangeData, Sint32 fReturnCode = 0)
		: fMessageDataId(0)
        , fControl(control)
		, fItemId(itemId)
		, fAuxiliaryItemData(auxiliaryItemData)
		, fItemChangeData(std::move(itemChangeData))
        , fpLegacyItemData(nullptr)
		, fReturnCode(fReturnCode)
	{}

    // Message type identifier
    Sint32 fMessageDataId;
	Sint32 fControl;
	Sint32 fItemId;
	std::vector<Sint32> fItemIds;	// for multiselection
    Sint32 fAuxiliaryItemData;
    std::set<Sint32> fIntItemDataCollection;
	std::unique_ptr<CGSBaseDataContainer> fItemChangeData;
    // "Legacy" item information (typically a pointer to
    // a single integral value)
    Sint32* fpLegacyItemData;
	Sint32 fReturnCode;
};

// control being dragged over generates kDragOverMessage with pointer to this struct as data param
//  and sends to dialog handler of control being dragged over.  Dialog handler sets value of fShowPreview
struct TDragMessageData
{
	Sint32	fControl;		// this is the control being dragged over.  (The control that originated drag is handled by kBeginDragMessage)
	void*	fData;			// control-dependent
	bool	fShowPreview;	// updated by dialog handler
};

// some notes on naming -- fTargetAboveItemID means that the target is to be placed above the item ID.  
//  it DOES NOT mean the item ID will be above the target.  Drop point should be inbetween fTargetBelowItemID
//   and fTargetAboveItemID
struct TTreeControlDropMessageData
{
	TTreeControlDropMessageData() :
		fSourceControlID(0),
		fSourceItemID(0),
		fTargetControlID(0),
		fTargetParentItemID(0),
		fTargetBelowItemID(0),
		fTargetAboveItemID(0),
		fAllow(false),
		fDropPtX(0),
		fDropPtY(0),
		fItemOriginX(0),
		fItemOriginY(0),
		fItemOriginXForTargetBelowItemID(0)
	{}

	void ResetDropMessageData()
	{
		fSourceControlID = 0;
		fSourceItemID = 0;
		fSourceItemsIDs.clear();
		fTargetControlID = 0;
		fTargetParentItemID = 0;
		fTargetBelowItemID = 0;
		fTargetAboveItemID = 0;
		fAllow = false;
		fDropPtX = 0;
		fDropPtY = 0;
		fItemOriginX = 0;
		fItemOriginY = 0;
		fItemOriginXForTargetBelowItemID = 0;
	}

	Sint32 fSourceControlID;
	Sint32 fSourceItemID;
	std::vector<Sint32> fSourceItemsIDs; // for when multiselection is enabled
	Sint32 fTargetControlID;
	Sint32 fTargetParentItemID;	// this can be updated (with fTargetAboveItemID) during kDragOverMessage to adjust preview
	Sint32 fTargetBelowItemID;	// this cannot be updated -- it is only reported -- fTargetParentItemID may not be fTargetBelowItemID's parent
	Sint32 fTargetAboveItemID;	// -1 is used here for drag/drop as last item under parent -- can be updated
	bool fAllow;				// value meant to be changed by dialog client handler
	Sint32 fDropPtX;
	Sint32 fDropPtY;
	int  fItemOriginX;			// only reported during drag -- to give an idea where the mouse is in relation to the item
	int  fItemOriginY;
	int  fItemOriginXForTargetBelowItemID;  // fItemOriginX is for fTargetAboveItemID
};

struct TreeControlClickMessageData
	// send when for tree control event message
{
	Sint32  fItemClickedOn;	// tree itemID

	// mouse clicks
	bool	fIsSelectionChanged;
	bool	fIsDoubleClick;
	bool	fIsClickOnIcon;
	bool	fIsCLickOnCheckBox;

	// keyboard
	bool	fIsKeyClick;
	Uint32	fKeyClickCode;

	// modifiers
	bool 	fShiftKeyDown;
	bool 	fControlKeyDown;
	bool	fAltKeyDown;
};

typedef bool (*ShowButtonInTreeForRowProcPtr)(Sint32 dlogID, Sint32 itemHit, int item);
typedef void (*HandleTreeButtonProcPtr)(Sint32 dlogID, Sint32 itemHit, int item);

struct AllowButtonColumnInTreeInput
{
    int dialogID;
    int treeID;
    TXString buttonCaption;
    ShowButtonInTreeForRowProcPtr showButtonForRow;
    HandleTreeButtonProcPtr buttonHandler;
    
    AllowButtonColumnInTreeInput(int d, int t, const TXString& c, ShowButtonInTreeForRowProcPtr s, HandleTreeButtonProcPtr b)
    {
        dialogID = d;
        treeID = t;
        buttonCaption = c;
        showButtonForRow = s;
        buttonHandler = b;
    }
};

////////////////////////////////////////////////////////////////////////////////////////
// List Browser message constants
////////////////////////////////////////////////////////////////////////////////////////
const Sint32	kMessageDataChangeClick					= -2;
const Sint32	kMessageDataChangeAllClick				= -3;
const Sint32	kMessageSelectionChangeClick			= -4;
const Sint32	kMessageDoubleClick						= -5;
const Sint32	kMessageDeleteKeyPressed				= -6;
const Sint32	kMessageUpKeyPressed					= -7;
const Sint32	kMessageDownKeyPressed					= -8;
const Sint32	kMessageAlphaNumericKeyPressed			= -9;
const Sint32	kMessageSortOccurred					= -10;
const Sint32	kMessageSelectionMultChangeClick		= -11;
const Sint32	kMessageEnterKeyPressed					= -12;
const Sint32	kMessageDataChangeRecursiveClick		= -13;
const Sint32	kMessageDoubleAllClick					= -14;
const Sint32	kMessageDoubleRecursiveClick			= -15;
//  Query is associated with a TItemMessageData, where
//  TItemMessageData.fItemId indicates a row index
//  TItemMessageData.fAuxiliaryItemData indicates a column
//  index. The return value for this query,
//  TItemMessageData.fReturnCode, is an
//  EListBrowserItemInteractionType value.
const Sint32    kMessageQueryInteractionHandlingType    = -16;
//  Query that provides the immediate value of the referenced,
//  interaction-enabled item upon invocation.
const Sint32    kMessageQueryItemValue                  = -17;
//  Query that is employed to retrieve a collection of
//  elements required to populate a list to be presented for
//  item selection.
const Sint32    kMessageQueryItemListRetrieval          = -18;
//  Message is transmitted after a successfully-invoked
//  edit operation, where TItemMessageData.fItemId indicates
//  a row index, and TItemMessageData.fAuxiliaryItemData indicates
//  a column index. TItemMessageData.fItemChangeData is a
//  pointer to a CGSBaseDataContainer-derived structure that
//  contains information pertaining to the item change.
//  TItemMessageData.fIntItemDataCollection specifies a
//  collection of additional items when populated, referenced
//  by row index, to which the item change should be applied.
const Sint32    kMessageItemEditCompletionData          = -19;
//	VB-192439 - Used for drag and drop in the ColorPaletteManager Dialog.
const Sint32	kMessageItemDragAndDrop		= -20;



struct EditDoubleClickData {
	Sint32 fStructIdentifier;
	Sint32 fLineNumberClickedOn;
	wchar_t *fTextOnLine;
};

inline bool IsMLDoubleClickMessage(void *msg) { 
	return (msg && ((EditDoubleClickData*) msg)->fStructIdentifier == kDoubleClickInMLEdit);
}	// LayoutManager messages should at least point to 4 bytes if non-nil, and the first 4 bytes of a EditDoubleClickData struct are kDoubleClickInMLEdit

typedef void* (*GetImageCallBackProc) (Uint64 userData, short fileRef, Sint32 imageWidth, Sint32 imageHeight);
typedef void (*GetCompressedImageCallBackProc) (Uint64 userData, short fileRef, Sint32 imageWidth, Sint32 imageHeight, char* &outpCompressedData, Uint32& outCompressedDataSize);

#define GS_ENABLE_NEW_LAYOUT_MANAGER_CONTROLS 1

#if Tolu
#define GLOBAL_COORDS_ON_OIP		1
#define COLORED_EDIT_TEXT_ON_OIP	1
#else
#define GLOBAL_COORDS_ON_OIP		1
#define COLORED_EDIT_TEXT_ON_OIP	1
#endif

#if COLORED_EDIT_TEXT_ON_OIP	
typedef unsigned char   BYTE;
typedef unsigned short  WORD;

#if GS_MAC
typedef Uint32 COLORREF; //X64PRJ_REVISIT Miriam - Halycon HSIPORT.H no longer needs this, but it's needed on Mac (something
                         //     that previously defined it on Mac went away).
#endif

#if GS_LITTLE_ENDIAN
	#define GenerateRGB(r,g,b)	((Uint32)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((Uint32)(BYTE)(b))<<16)))
	#define GetRedValue(rgb)	((BYTE)(rgb))
	#define GetGreenValue(rgb)	((BYTE)(((WORD)(rgb)) >> 8))
	#define GetBlueValue(rgb)	((BYTE)((rgb)>>16))
#else	
	#define GenerateRGB(r,g,b)	((Uint32)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((Uint32)(BYTE)(r))<<16)))
	#define GetBlueValue(rgb)	((BYTE)(rgb))
	#define GetGreenValue(rgb)	((BYTE)(((WORD)(rgb)) >> 8))
	#define GetRedValue(rgb)	((BYTE)((rgb)>>16))
#endif

#endif //COLORED_EDIT_TEXT_ON_OIP

// Control Indexes for GS_CreateControl 

//	The indices less than zero map to controls available through explict LayoutNS APIs
//
#if GS_ENABLE_NEW_LAYOUT_MANAGER_CONTROLS
const short kTemp2ControlID						= -18;
const short kTemp1ControlID						= -17;
const short kUnused1ControlID					= -16;
const short kEditableEnhancedComboBoxControlID	= -15;
const short kEnhancedComboBoxControlID			= -14;
const short kThreeStateCheckboxControlID		= -13;
const short kIconPushButtonControlID			= -12;
#endif
const short kTreeControlID						= -11;
const short kStaticTextControlID				= -10;
const short kRadioButtonControlID				= -9;
const short kPushButtonControlID				= -8;
const short kPullDownMenuControlID				= -7;
const short kListBoxControlID					= -6;
const short kIconControlID						= -5;
const short kGroupBoxControlID					= -4;
const short kEditRealControlID					= -3;
const short kEditTextControlID					= -2;
const short kCheckBoxControlID					= -1;

const short kReservedCreateControlID_1		= 1;

const short	kReservedCreateControlID_2		= 26;

const short kEditablePatternsDropDown		= 27;	// Displays the drop down just containing the
													// list of editable patterns.
									
const short kColorButtonControl 			= 2;	// push button that opens the system color palette dialog, the button is painted in the selected color
													// name is not used, data specifies the default color wher the three 8-bit color values are packed into a 
													// Sint32 in the following format: 0x00RR GGBB
													// Event hanlding: data is equal to the selected color 
					
const short kSliderControl					= 3;	// Slider Control 
													// name is not used, at creation time data is used to specify the maximum slider value, after that
													// data is used to get and set the current value of the slider
													// Event handling: data is the current value of the slider

// ----------------- These are the layout manager attribute controls. --------------------------|
const short kColorPopup						= 4;	// Color Popup								|
const short kPatternPopup					= 5;	// Pattern Popup							|
const short kDashPopup						= 6;	// Line Style Popup 						|
const short kLinePopup						= 7;	// Line weight Popup 	     				|
const short kLineComboPopup					= 18;   // Combines Line weight and dash 			|
const short kMarkerPopup					= 8;	// Marker Popup                             | 
// ---------------------------------------------------------------------------------------------| (All Controls are in combobox form of popup. AD)



const short kEditMultilineText				= 9;	// JAK 10F-077
const short kReservedCreateControlID_3		= 10;
const short kGradientSliderControl			= 11;	// Multiple marker gradient slider control.
const short kCheckBoxGroupBox				= 12;	// Group box w/ checkbox as title
const short kRadioButtonGroupBox			= 13;	// Group box w/ radio button as title
const short kTabPane						= 14;	// Tab control
const short kListBrowserControl				= 15;   // Multiple-list column control.
const short kSwapControl					= 16;	// Swap control
const short kSymbolDisplayControl			= 17;	// Symbol Display control.
#if GS_ENABLE_NEW_LAYOUT_MANAGER_CONTROLS
const short kThreeStateCheckbox				= 19;	// Three state checkbox
const short kIconPushButton					= 20;	// Icon push button
const short kEnhancedComboBoxControl		= 21;
const short kEditableEnhancedComboBoxControl= 22;
const short	kUnused1Control 				= 23;
const short kTemp1Control 					= 24;
const short kTemp2Control 					= 25;
#endif


typedef short EditRealType;
const EditRealType 		kEditReal	 		= 1;
const EditRealType 		kEditAngle			= 2;
const EditRealType		kEditDimension		= 3;
const EditRealType		kEditCoordinateX	= 4;
const EditRealType		kEditCoordinateY	= 5;
 
typedef short ThumbnailSizeType;
const ThumbnailSizeType kStandardSize	= 0;
const ThumbnailSizeType kLineTypeSize	= 1;

//	------------------------------------------------------------------------------ 
//	GS_GetIndexedControlData  and GS_SetIndexedControlData Data Types:
//
typedef Sint32		ComponentDataIndex;

//--------------
//	ListBox Data:
const short kListBoxGetNextSelected = 100;	// 


struct CreateControlData
{
public:
	Sint16 width;
	Sint16 height;
	union 
	{
		struct {
			
			EditRealType editRealType;
			double value;
		} editRealData;
		
		struct {
			
			Boolean hasFrame;
		} groupBoxData;

		struct {
			Sint32  iconNumber;
		} iconData;
		
		struct {
			
			Boolean isMultiSel;
		} listBoxData;
		
		struct {
			
			Sint32 data;
		} genericControlData;
		
		struct {
			
			Sint32 data;
			void* getImageProc;
		} thumbnailData;
		
		struct {
			
			Sint32 pictID;
		} pictureData;

		struct {
			
			Sint32 resID;
		} PNGData;

		struct {

			Sint32 data;
		} treeControlData;
	};
};

/////////////////////////////////////////////////////////////////////////////////////////
// Data Display Bar Field Types
/////////////////////////////////////////////////////////////////////////////////////////

#define kBarArrayMax 20

enum {
	barNone						=  0,
	barX						=  1,	// current x cursor location
	barY						=  2,	// current y cursor location
	barH						=  3,	// current x distance between cursor and startPt
	barV						=  4,	// current y distance between cursor and startPt
	barLength					=  5,	// Current distance between cursor and startPt
	barAngle					=  6,	// angle made from startPt to cursor
	barScaleX					=  7,	// barH / (width of original item or group)
	barScaleY					=  8,	// barV / (height of original item or group)
	barRadius					=  9,	// barLength / 2
	barRatio					= 10,	// barV/barH
	barText						= 11,	// static text
	barArea						= 12,	// area of item
	barPerim					= 13,	// perimeter of item
	barLayer					= 14,	// layer
	barClass					= 15,	// class
	barU1TotalLength			= 16,
	barFracRatio				= 17,
	barFracDist					= 18,
	barOff						= 19,
	bar1StartAngle				= 20,
	bar2ArcAngle				= 21,
	barUser1Angle				= 22,	// user area 1 in angle format
	barUser1Float				= 23,	// user area 1 in extended format
	barUser1Int					= 24,	// user area 1 in integer format
	barUser1Dim					= 25,	// user area 1 in dimension format
	barUser2Angle				= 26,	// user area 2 in angle format
	barUser2Float				= 27,	// user area 2 in extended format
	barUser2Int					= 28,	// user area 2 in integer format
	barUser2Dim					= 29,	// user area 2 in dimension format
	barRotAngle					= 30,	// onscreen rotation
	barOffH						= 31,	// current x distance between cursor and startPt
	barOffV						= 32,	// current y distance between cursor and startPt
	barZoomFactor				= 33,
	bar3DX						= 34,	// current location in world space
	bar3DY						= 35,
	bar3DZ						= 36,
	bar3DDX						= 37,	// current distance between cursor and startPt in world space
	bar3DDY						= 38,
	bar3DDZ						= 39,
	bar3DWPAngle				= 40, 
	bar3DWorldAngle				= 41,
	bar3DLength					= 42,
	bar3DScrMatAzimuth			= 43,	// these are origin-centric using world axes
	bar3DScrMatElevation		= 44,
	bar3DScrMatPitch			= 45,	// these are viewer-centric
	bar3DScrMatYaw				= 46,
	bar3DScrMatRoll				= 47,
	bar3DScrMatViewerX			= 48,	// these are viewer positions
	bar3DScrMatViewerY			= 49,
	bar3DScrMatViewerZ			= 50,
	bar3DScrMatViewerDK			= 51,	// delta WP k axis for trans along wp norm
	bar3DScrMatViewerLeftRight	= 52,	// delta view space
	bar3DScrMatViewerUpDown		= 53,
	bar3DScrMatViewerInOut		= 54,
	bar3DScrMatWPDAzimuth		= 55,
	bar3DWallBottom				= 56,
	bar3DWallTop				= 57,
	bar3DWallOff1				= 58,
	bar3DWallOff2				= 59,
	bar3DWallRatio				= 60,
	bar3DWallBase				= 61,
	bar3DRoofRise				= 62,
	bar3DRoofRun				= 63,
	bar3DRoofAngle				= 64,
	barUserStr					= 65,
	bar3DI						= 66,	// current location in WP space
	bar3DJ						= 67,
	bar3DK						= 68,
	bar3DDI						= 69,	// current distance between cursor and startPt in WP space
	bar3DDJ						= 70,
	bar3DDK						= 71,
	bar3DScrMatViewerI			= 72,	// these are viewer positions in WP Space
	bar3DScrMatViewerJ			= 73,
	bar3DScrMatViewerK			= 74,
	barPlane					= 75,
	barCustom					= 255
};

const short barStr = barUserStr;
typedef Sint32 BarNumberType;

//---------------------------------------------------------------------------------------
// EWSColumnDatabaseOperatorType - worksheet database column operator types.
enum EWSColumnDatabaseOperatorType 
{ 
	kWSAllOperators = -1,
	kWSSortOperator = 0, 
	kWSSummarizeOperator = 1,
	kWSSumValuesOperator = 2
};

//---------------------------------------------------------------------------------------
// EWSColumnDatabaseSortType - worksheet database column sort operator types.
enum EWSColumnDatabaseSortType 
{ 
	kWSSortAscending = 0,
	kWSSortDescending = 1
};

//---------------------------------------------------------------------------------------
// EWSDialogType - worksheet dialog constants.
//
enum EWSDialogType {
	kWSColumnWidthDialog			= 0,
	kWSRowHeightDialog				= 1,
	kWSFormatWorksheetDialog		= 2,
	kWSPreferencesDialog			= 3,
	kWSPageSetupDialog				= 4,
	kWSPrintDialog					= 5,
	kWSFunctionDialog				= 6,
	kWSCriteriaDialog				= 7,
	kWSSetRowCriteriaDialog			= 8,
	kWSEditRowCriteriaDialog		= 9,
	kWSCreateReportDialog			= 10,
	kWSEditReportDialog				= 11,
	kWSSetFieldDialog				= 12
};

//---------------------------------------------------------------------------------------
// EFillType - types of 2D object fills.
//
enum EAttributeFillType {

	/* Note that internal systems use this enum as a signed char, and use -1 to represent 'unknown' -
	   So changes to this enum should only include new positive values less than 128 */
	kFillNone		= 1,
	kFillSolid		= 2,
	kFillPattern	= 3,
	kFillHatch		= 4,
	kFillTile		= 5,
	kFillGradient	= 6,
	kFillImage		= 7,
	kFillClass		= 8
};

//---------------------------------------------------------------------------------------
// EThumbnailType - types of image popup control thumbnails.
//
enum EThumbnailType {

	kThumbnailHatch		= 1,
	kThumbnailTile		= 2,
	kThumbnailGradient	= 3,
	kThumbnailImage		= 4,
	kThumbnailLineType	= 5
};

//---------------------------------------------------------------------------------------
// EGradientGeometryType - types of gradient fill geometry.
//
enum EGradientGeometryType {
	kGradientGeometryLinear			= 1,
	kGradientGeometryRadial			= 2,
	kGradientGeometryRectangular	= 3,
	kGradientGeometryAngle			= 4
};

//---------------------------------------------------------------------------------------
// EGradientSliderMarkerType - gradient slider marker types.
//
enum EGradientSliderMarkerType {
	kGradientSliderMarkerSpot		= 1,
	kGradientSliderMarkerMidpoint	= 2
};

//---------------------------------------------------------------------------------------
// EViewportGroupType - viewport group types.
//
enum EViewportGroupType {
	kViewportGroupCrop						= 1,	// Tag of the user data node attached to the aux list of the group holding the crop of a viewport, 
													// group object being attached to the aux list of the viewport node.

	kViewportGroupAnnotation				= 2,    // Tag of the user data node attached to the aux list of the group holding the annotation objects of a viewport, 
													// group object being attached to the aux list of the viewport node.

	kViewportGroupCache						= 3,	// Tag of the user data node attached to the aux list of the group holding the render cache (polys for polygon 
													// rendering mode, lines of line rendering modes, paint nodes for raster render modes) of a viewport, 
													// group object being attached to the aux list of the viewport node.

	kViewportGroupSection					= 4,	// Tag of the user data node attached to the aux list of the group holding the master definition of the section 
													// line object in a section viewport, group object being attached to the aux list of the viewport node.

	kViewportGroup3DSectionCache			= 5,	// Tag of the user data node attached to the aux list of the group holding the 3D polys that represnt objects beyond
													// the cutting plane (3D section result - bspPolys in kViewportGroup3DSectionExCache converted to 3D Polys) of a 
													// section viewport, group object being attached to the aux list of the viewport node.

	kViewportGroup2DSectionCache			= 6,	// Tag of the user data node attached to the aux list of the group holding the polygons generated on the cutting plane 
													// (2D section result) of a section viewport, group object being attached to the aux list of the viewport node.

	kViewportGroup3DSectionExCache			= 7,	// Tag of the user data node attached to the aux list of the group holding the bsp polys that represnt objects beyond
													// the cutting plane (3D section result) of a section viewport, group object being attached to the aux list of the viewport node.
	
	kViewportGroup3DReversedSectionCache	= 8,	// Tag of the user data node attached to the aux list of the group holding the 3D polys that represnt objects on the reversed side of 
													// the cutting plane (3D section result - converted to 3D Polys) of a section viewport, group object being attached to the aux list 
													// of the viewport node.
	
	kViewportGroupSecondaryCache			= 9,	// Tag of the user data node attached to the aux list of the group holding the secondary render cache (polys for polygon 
													// rendering mode, lines of line rendering modes, paint nodes for raster render modes) of a viewport, 
													// group object being attached to the aux list of the viewport node.
	
	kViewportGroupCamera					= 10,	// Tag of the user data node attached to the aux list of the group holding the camera object 
													// in a viewport, group object being attached to the aux list of the viewport node.

	kViewportGroupDetail					= 11,	// Tag of the user data node attached to the aux list of the group holding the master definition of the detail 
													// callout object in a detail viewport, group object being attached to the aux list of the viewport node.

	kViewportGroupInteriorElevation			= 12,	// Tag of the user data node attached to the aux list of the group holding the master definition of the interior 
													// elevation object in a section viewport, group object being attached to the aux list of the viewport node.

	kViewportGroupCutPlaneOverride			= 13,	// Tag of the user data node attached to the aux list of the group holding the cut plane override regions of a viewport,
													// group object being attached to the aux list of the viewport node.
	kViewportGroupSectionAboveCache			= 14,	// Tag of the user data node attached to the aux list of the group holding the any above/before rendering from sections

	kViewportGroup2DSectionPenCache			= 15	// Tag of the user data node attached to the aux list of the group holding the lines for the section polygons, which draw
													// above the fills and above any above/before rendering from sections
};

//---------------------------------------------------------------------------------------
// ELayerType - layer types.
//
enum ELayerType {
	kLayerDesign		= 1,
	kLayerPresentation	= 2, //obsolete name -- included only for backward compatibility
	kLayerSheet			= 2,
	kGuestLayerDesign   = 3
};

//---------------------------------------------------------------------------------------
// EDesignLayerVPLayerSource - Design layer viewport layer source.
//
enum EDesignLayerVPLayerSource {
	kHostFile	= 0,
	kGuestFile	= 1
};

//---------------------------------------------------------------------------------------
// EListBrowserHeaderColumnType - column header types.
//
enum EListBrowserControlType {
	kListBrowserControlNone				= 1,
	kListBrowserControlRadio			= 2,
	kListBrowserControlMultiState		= 3,
	kListBrowserControlSingleInstance	= 4,
	kListBrowserControlNoClick			= 5, 
	kListBrowserControlNumber			= 6,
	kListBrowserControlMultipleImages	= 7,		// Use with kListBrowserDisplayImageOnly
	kListBrowserControlDiscTriangle		= 8
};

//---------------------------------------------------------------------------------------
// EListBrowserDisplayType - display types.
//
enum EListBrowserDisplayType {
	kListBrowserDisplayTextOnlyOld	= 0,
	kListBrowserDisplayImageOnly	= 1,
	kListBrowserDisplayTextOnly		= 2,
	kListBrowserDisplayImageAndText	= 3
};

//---------------------------------------------------------------------------------------
// EListBrowserOwnerDrawnType - owner drawn display types.
//
enum EListBrowserOwnerDrawnType {
	kListBrowserNotOwnerDrawn	= 0,
	kListBrowserSolidRect		= 1,
	kListBrowserDualSolidRect	= 2,
	kListBrowserPatternRect		= 3,
	kListBrowserDualPatternRect	= 4,
	kListBrowserGradientOrImage	= 5,
	kListBrowserBlankOwnerDrawn	= 6,
	kListBrowserTextOwnerDrawn	= 7,
	kListBrowserDashedLine		= 8,
	kListBrowserTile			= 9,
	kListBrowserHatch			= 10,
	kListBrowserLineWeight		= 11,
	kListBrowserLineEnd			= 12,
	kListBrowserResource		= 13
};

//------------------------------------------------------------------------------------
// EListBrowserItemInteractionType - list browser item edit operation types
//
enum EListBrowserItemInteractionType {
    kListBrowserItemInteractionNone                     = 0,
    
    // Initialization -                 CGSStringValueChange
    // Interaction Result -             CGSStringValueChange
    kListBrowserItemInteractionEditText                 = 1,
    
    // Initialization -                 CGSStringValueChange
    // Interaction Result -             CGSStringValueChange
    kListBrowserItemInteractionEditNumerical            = 2,
    
    // Initialization -                 CGSMultiStateValueChange
    // Interaction Result -             CGSMultiStateValueChange
    kListBrowserItemInteractionEditCheckState           = 3,
    
    // Initialization -					CGSClassAndLayerPulldownCollection
    // Interaction Result -				CGSClassAndLayerPulldownItemValue
    kListBrowserItemInteractionEditClass                = 4,
    
	// Initialization -					CGSClassAndLayerPulldownCollection
	// Interaction Result -				CGSClassAndLayerPulldownItemValue
    kListBrowserItemInteractionEditAllLayers            = 5,

	// Initialization -					CGSClassAndLayerPulldownCollection
	// Interaction Result -				CGSClassAndLayerPulldownItemValue
	kListBrowserItemInteractionEditDesignLayers			= 6,

	// Initialization -					CGSClassAndLayerPulldownCollection
	// Interaction Result -				CGSClassAndLayerPulldownItemValue
	kListBrowserItemInteractionEditSheetLayers			= 7,
    
    // Initialization -                 CGSColorValueChange
    // Interaction Result -             CGSColorValueChange
    kListBrowserItemInteractionEditColor                = 8,
    
    // Initialization -                 CGSPatternWithColorValueChange
    // Interaction Result -             CGSPatternValueChange
    kListBrowserItemInteractionEditPattern              = 9,
    
    // Initialization -                 CGSGradientValueChange
    // Interaction Result -             CGSGradientValueChange
    kListBrowserItemInteractionEditGradient             = 10,
    
    // Initialization -                 CGSHatchStyleValueChange
    // Interaction Result -             CGSHatchStyleValueChange
    kListBrowserItemInteractionEditHatchStyle           = 11,
    
    // Initialization -                 CGSImageResourceValueChange
    // Interaction Result -             CGSImageResourceValueChange
    kListBrowserItemInteractionEditImage                = 12,
    
    // Initialization -                 CGSTileResourceValueChange
    // Interaction Result -             CGSTileResourceValueChange
    kListBrowserItemInteractionEditTile                 = 13,
    
    // Initialization -                 CGSLineTypeValueChange
    // Interaction Result -             CGSLineTypeValueChange
    kListBrowserItemInteractionEditLineStyle            = 14,
    
    // Initialization -                 CGSLineWeightValueChange
    // Interaction Result -             CGSLineWeightValueChange
    kListBrowserItemInteractionEditLineThickness        = 15,
    
    // Initialization -					CGSLineEndValueChange
    // Interaction Result -				CGSLineEndValueChange
    kListBrowserItemInteractionEditLineEnd				= 16,
    
    // Initialization -                 CGSRangedValueChange
    // Interaction Result -             CGSIntValueChange
    kListBrowserItemInteractionEditQuantitative         = 17,
    
    // Initialization -                 CGSMenuItemCollection
    // Interaction Result -             CGSListItemValue
    kListBrowserItemInteractionEditGenericList          = 18,

	// Initialization -                 CGSSearchablePulldownCollection
	// Interaction Result -             CGSSearchablePulldownItemValue
	kListBrowserItemInteractionEditSearchableList		= 19,

	// Initialization -                 CGSResourceValueChange
	// Interaction Result -             CGSResourceValueChange
	kListBrowserItemInteractionEditResource				= 20
};

//------------------------------------------------------------------------------------
// EStaticTextType - GSStaticText types.
//
enum EStaticTextType {
	eStaticTextTypeRegular,					// Normal
	eStaticTextTypeCaption,					// Seems unsupported
	eStaticTextTypeBold,					// Bold
	eStaticTextTypeReduced,					// Supported on Mac (uses "small system font" size. Used normal size on Windows.
	eStaticTextTypeCustomSize = 100,		// Normal: Specify size (in points) explicitly. eg 12 point would be 112.
	eStaticTextTypeMaxCustomSize = 116,		// Normal: Maximum value for a custom font size.
	eStaticTextTypeBoldCustomSize = 200,	// Bold: Specify size (in points) explicitly. eg 12 point would be 112.
	eStaticTextTypeBoldMaxCustomSize = 216	// Bold: Maximum value for a custom font size.

};

//---------------------------------------------------------------------------------------
// EButtonImagePos - position of image in relation to text for a button.
//
enum EButtonImagePos {
	kImageAbove,
	kImageLeft
};

//---------------------------------------------------------------------------------------
// EResourceType - resource types.
//
enum EResourceType {
	kResourceSmallIcon	= 1 // 16x16 icon.
};

//---------------------------------------------------------------------------------------
// ESymScaleType - type of scaling for a symbol.
//
enum ESymScaleType {
	kScaleTypeNone			= 1,
	kScaleTypeSymmetric		= 2,
	kScaleTypeAsymmetric	= 3
};


// SDK tools store their mode bar help in a sequential list in a TEXT resource
// 20 is the max number of help strings and serves as the separator between
// different tools
const short kSDKToolModeBarHelpMax = 20; 

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
	short fInteractiveSizingGroup;	// radio group

	// ---------
	// fModeGroup:
	//		insertModeGroup choice indices
	short fRegularInsChoiceIndex;
	short fOffsetInsChoiceIndex;
	short fPickUpChoiceIndex;
	short fInteractiveSizingIndex;

	// ---------
	// fAlignmentGroup:
	//		alignmentGroup choice indices
	short fLeftChoiceIndex;
	short fCenterChoiceIndex;
	short fRightChoiceIndex;
	short fNaturalChoiceIndex;

	// fInteractiveSizingGroup
	//		Interactive Sizing choice indices
	short fIntSizingCornerToCornerIndex;
	short fIntSizingCenterToCornerIndex;

	// ---------
	// additional options for the default tool
	double		fInsertRotateAngleAddition;

	// This matrix will be used after a default point tool is added to a wall
	// when the mouse is used to orient the object in the wall
	TransformMatrix		fWallPreviewOrientationAfterMatrix;

	SDefaultPointToolInfo() {
		fModeGroup = fAllowInsertGroup = fAlignmentGroup = fInteractiveSizingGroup = -1;
		fSymbolResourceGroup = -1;
		fRegularInsChoiceIndex = fOffsetInsChoiceIndex = fPickUpChoiceIndex = fInteractiveSizingIndex = -1;
		fLeftChoiceIndex = fCenterChoiceIndex = fRightChoiceIndex = fNaturalChoiceIndex = -1;
		fIntSizingCornerToCornerIndex = fIntSizingCenterToCornerIndex = -1;
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
	virtual	~ParametricMessage() {}

	Sint32			fAction				= 0;
	MCObjectHandle	fParametricHandle	= nullptr;

protected:
			ParametricMessage()					= default;
			ParametricMessage(Sint32 action)	: fAction( action ) {}
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

struct ParametricCursorMessage : public ParametricMessage
{
	enum EAction
	{
		kAction_MouseDown 		= 36,
		kAction_Complete 		= 37,
		kAction_MouseMove 		= 38,
		kAction_Draw 			= 39,
		kAction_Cancel 			= 40,
	};

	ParametricCursorMessage(ParametricCursorMessage::EAction action, Sint32 pickIndex) { fAction = action; fPickIndex = pickIndex; }

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
/* Standard views used to query the object for auto-dimensions, objects should support
//   at least Top, Front, Left. (Back, Right, and Bottom may be repurposed from the others.)
//   This list is found in "Objs.TDType.h"
enum class EViewTypes {
	NotSet,
	Top,
	Bottom,
	TopBottomCut,
	Front,
	Back,
	FrontBackCut,
	Left,
	Right,
	LeftRightCut,
	TopPlan,		// use this to add objects into the main drawing list of a symbol or plug-in and ensure 2D components synchronization
	ViewTypesNumber = TopPlan,
*/


/*	The auto-dimension identifiers for Plug-in objects, found in the file /Vectorworks.vwr/Strings/AutoDimensionIdentifiers.vwstrings
	They are values intended to be used by Plug-ins to populate the names in SAutoDimensionTypeInfo returned by GetSupportedDimensionIdentifiers.
	The name on the left is the universal name, and the name on the right is the localized name that is visible in the UI.
	These are known IDs provided to coordinate use across more than one Plug-in object.
	They are currently specific to Door and Window, but Distributors can add their own IDs to the file.
	Also, all Plug-In developers can return their own defined IDs from GetSupportedDimensionIdentifiers,
	and/or request they be added to AutoDimensionIdentifiers.vwstrings.
"Sash" = "Sash";
"Unit" = "Unit";
"Leaf" = "Leaf";
"RoughOpening" = "Rough Opening";
*/
const char kAutoDim_WinDoorDefaultCategory[] = "NNA_DefaultAutoDimWinDoorCategory";


namespace VectorWorks
{
	namespace Extension
	{
		// ------------------------------------------------
		enum class EAutoDimensionPlacement
		{
			eHorizontalTop,
			eHorizontalBottom,
			eVerticalLeft,
			eVerticalRight
		};

		// ------------------------------------------------
		// SAutoDimensionTypeInfo is populated by the Plug-in and returned in the
		// outvecTypes parameter of the GetSupportedTypes function.
		// The Plug-in should return info for all of the dimensions it is capable
		// of providing in the specified view (e.g. Front).
		class TAutoDimensionTypeInfo
		{
		public:
			TAutoDimensionTypeInfo() {}
			TAutoDimensionTypeInfo(const TXString& instrUni, const TXString& instrLoc)		{ this->SetID(instrUni, instrLoc); }

			void SetID(const TXString& instrUni, const TXString& instrLoc)					{ fstrID_UniversalName = instrUni; fstrID_LocalizedName = instrLoc; }

			TXString fstrID_UniversalName;	// The auto-dimension identifier e.g. "Sash"
			TXString fstrID_LocalizedName;
			std::vector<EAutoDimensionPlacement>	fvecPlaces;
		};

		// ------------------------------------------------
		// SAutoDimensionDefinition is populated by the Plug-in and returned in the
		// outvecDimensions parameter of the GetDimensionDefinitions function.
		// The Plug-in should return definitions for all of the dimensions for the
		// given inhObj, in the specified view (e.g. Front),
		// for the given dimension ID (e.g."RoughOpening"), and dimension type (e.g. eHorizontalTop).
		// fwOffset will normally be (0) and is used to offset the dimension line
		// and is useful for aligning multiple dimensions.
		class TAutoDimensionDefinition
		{
		public:
			TAutoDimensionDefinition() {}
			TAutoDimensionDefinition(const WorldPt3& inwpt3Start, const WorldPt3& inwpt3End, short inOffset = 0)
			{ this->Set(inwpt3Start, inwpt3End, inOffset); }

			void Set(const WorldPt3& inwpt3Start, const WorldPt3& inwpt3End, short inOffset = 0)
			{ fwpt3Start = inwpt3Start; fwpt3End = inwpt3End; fnOffset = inOffset; }

			WorldPt3		fwpt3Start;
			WorldPt3		fwpt3End;
			short			fnOffset;		// Stacked dimmension offset. (To help line up multiple dimensions)
		};
	}
}

struct ParametricAutoDimMessage_GetLocalizedTypeName : public ParametricMessage
{
	enum { kAction = 76 };

	ParametricAutoDimMessage_GetLocalizedTypeName(const TXString& instrDimID_UniversalName)
		: finstrDimID_UniversalName(instrDimID_UniversalName)	{ fAction = kAction;  }

	const TXString	finstrDimID_UniversalName;		// input
	TXString		foutstrDimID_LocalizedName;		// result from the message
};

struct ParametricAutoDimMessage_GetSupportedTypes : public ParametricMessage
{
	enum { kAction = 77 };

	ParametricAutoDimMessage_GetSupportedTypes(EViewTypes inView)
		: finView(inView) { fAction = kAction; }

	const EViewTypes											finView;		// input
	std::vector<VectorWorks::Extension::TAutoDimensionTypeInfo>	foutvecTypes;	// result from the message
};

struct ParametricAutoDimMessage_GetDimensionDefinitions : public ParametricMessage
{
	enum { kAction = 78 };

	ParametricAutoDimMessage_GetDimensionDefinitions(EViewTypes inView, const TXString& instrDimID_UniversalName, VectorWorks::Extension::EAutoDimensionPlacement inPlace)
		: finView(inView), finstrDimID_UniversalName(instrDimID_UniversalName), finPlace(inPlace) 	{ fAction = kAction; }

	const EViewTypes												finView;					// input
	const TXString													finstrDimID_UniversalName;	// input
	const VectorWorks::Extension::EAutoDimensionPlacement			finPlace;					// input
	std::vector<VectorWorks::Extension::TAutoDimensionDefinition>	foutvecDimensions;			// result from the message
};

struct ParametricAutoDimMessage_GetDisplayCategoryName : public ParametricMessage
{
	enum { kAction = 79 };

	ParametricAutoDimMessage_GetDisplayCategoryName() {
		fAction = kAction;
	}

	TXString		foutstrCategory_UniversalName;		// result from the message
	TXString		foutstrCategory_LocalizedName;		// result from the message
};

namespace VectorWorks
{
	namespace Extension
	{
		// ------------------------------------------------
		enum class EParametricContext
		{
			eGraphicLegend
		};
	}
}

struct ParametricPrepareForContextMessage : public ParametricMessage
// This message asks a parametric to prepare its settings for a context in which it will appear.
// In a Graphic Legend context, doors and windows should be closed.
{
	enum { kAction = 80 };

	ParametricPrepareForContextMessage(VectorWorks::Extension::EParametricContext inContext, EViewTypes inView, short inBgRenderMode, short inFgRenderMode)
		: finContext(inContext), finView(inView), finBgRenderMode(inBgRenderMode), finFgRenderMode(inFgRenderMode), foutbChanged(false)	{ fAction = kAction; }

	const VectorWorks::Extension::EParametricContext	finContext;			// input
	const EViewTypes									finView;			// input
	short												finBgRenderMode;	// input
	short												finFgRenderMode;	// input
	bool												foutbChanged;		// result from the message
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

	OnObjectStyleWidgetPrepCall() { fAction = OnObjectStyleWidgetPrepCall::kAction; fpWidgetProvider = NULL; fHideStyleParameters = false; }

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
		kOnMultipleReshapeDraw = 4,	// for this fSubtype fData is a pointer to
								// a MultipleReshapeEventData strucutre


		//	The object is selected and the multiple reshape tool has the marquee drawn already. 
		//  Use IProviderReshape to implement advanced object Marquee reshape delete.
		kOnMultipleReshapeDelete = 5	// for this fSubtype fData is a pointer to
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
		kObjectUndoRestore,			// fData => (const ObjectStateData_Undo*)
		kObjectUndoRemove,			// fData => (const ObjectStateData_Undo*)
		kPlanarRefChanged,			// fData => (const ObjectStateData_ObjectPlanarRefChanged*)
		kBeforeExportReset,			// fData => NULL
		kObjectUndoModify,			// fData => (const ObjectStateData_Undo*)

		// Vectorworks 2012
		kObjectCreated,				// fData => NULL
		kObjectDeleteBefore,		// fData => (const ObjectStateData_Delete*)
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
		kObjectScaleReset,			// fData => (const ObjectStateData_ObjectScalingInfo*)
		// Vectorworks 2020
		kObjectConvertingToUnstyled,	// fData => NULL
		kBuildingMaterialChangedReset,	// fData => ( const ObjectStateData_MaterialResourceChanged*)
		// Vectorworks 2021
		kObjectConvertedToUnstyled	// fData => NULL
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
		kAction_BeginStyledObjectsUpdate = 81,
		kAction_EndStyledObjectsUpdate = 82,
		kAction_FinalizeUpdateStyle = 85
	};

	ParametricStyleMessage(ParametricStyleMessage::EAction action, MCObjectHandle hSymDef, bool inbFromPluginStyleChoice=false)
		{ fAction = action; fSymDefHandle = hSymDef; fbFromPluginStyleChoice = inbFromPluginStyleChoice; }

	MCObjectHandle	fSymDefHandle;
	bool			fbFromPluginStyleChoice;
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

struct ParametricGetStyleFolder : public ParametricMessage
{
	enum { kAction = 67 };	

	ParametricGetStyleFolder(TXString styleFolderName) { fAction = kAction; fStyleFolderName = styleFolderName; }

	TXString fStyleFolderName;
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

struct AttributeQuery {
	AttributeQuery(bool inAllDisabled=false,
				   bool inFillDisabled=false,
				   bool inPenDisabled=false,
				   bool inFillMappingDisabled=false) :
			penDisabled(inPenDisabled),
			fillDisabled(inFillDisabled),
			allDisabled(inAllDisabled),
			fillMappingDisabled(inFillMappingDisabled){}
	bool allDisabled, fillDisabled, penDisabled, fillMappingDisabled;
};

struct ParametricCanEditAttrMessage : public ParametricMessage {
	enum { kAction = 83 };

	ParametricCanEditAttrMessage() { fAction = kAction; }

	AttributeQuery query;
};

enum class EQTOFunction
{
	Angle,
	Count,
	Length,
	Perimeter,
	Width,
	Height,
	Depth,
	Weight,
	Area,
	SurfaceArea,
	ProjectedArea,
	FootPrintArea,
	CrossSectionArea,
	SpecialArea,
	Volume,
	ObjectData,
};

struct ParametricGetQTOValue : public ParametricMessage {
	enum { kAction = 84 };

	ParametricGetQTOValue() { fAction = kAction; }

	EQTOFunction			fFunction	= EQTOFunction::Count;
	TXString				fOption;
	std::vector<VWVariant>	farrArguments;
	VWVariant				fValue;
	bool					fIsEditing	= false;
	MCObjectHandle			fSubpart	= nullptr;
};

struct ParametricGetCustomBounds : public ParametricMessage
{
	enum { kAction = 86 };	

	ParametricGetCustomBounds(const WorldRect& bounds) { fAction = kAction; fBounds = bounds; }

	WorldRect fBounds;
};

enum class EPageBasedProfileGroupCheckingContext
{
	eUnspecified,
	eObjectScaling,
	eSymbolPreviewRegeneration,
};

struct ParametricIsProfileGroupPageBasedMessage : public ParametricMessage
{
	enum
	{
		kAction	= 87
	};

	ParametricIsProfileGroupPageBasedMessage(EPageBasedProfileGroupCheckingContext context)
		: ParametricMessage( kAction )
		, fContext( context )
	{}

	EPageBasedProfileGroupCheckingContext	fContext;
	bool									fIsPageBased	= false;
};

// enum { kAction = 88 }; is available.

// The Core will send this message to PIOs inserted in Walls to query whether
// the PIO would like to control its Wall Closure offsets
struct ParametricProvidesClosureGapsMessage : public ParametricMessage
{
	enum { kAction = 89 };

	ParametricProvidesClosureGapsMessage() : ParametricMessage( kAction ) {}

	bool fProvidesGaps = false;
	WorldCoord fLeftGap = 0.0;
	WorldCoord fRightGap = 0.0;
	WorldCoord fTopGap = 0.0;
	WorldCoord fBottomGap = 0.0;
};

//====================================
enum EInteractiveSizingType
{
	eISZ_Width					= 0,
	eISZ_Height					= 1,
	eISZ_Elevation				= 2,
	eISZ_ElevationSetAt			= 3,
	eISZ_ObjSupportsCornerCnfg	= 4,
	eISZ_CornerConfig			= 5,
	eISZ_BottomCenterPointX		= 6,
	eISZ_BottomCenterPointY		= 7,
	eISZ_BottomCenterPointZ		= 8,
	eISZ_ResizeHandleLocation	= 9,
	eISZ_ResizeHandleOffset		= 10,
	eISZ_ShowZValueOnDatabar	= 11,
	eISZ_OperativeHandDirection	= 12,
	eISZ_OperativeSideOfWall	= 13,
	eISZ_InteriorSide			= 14,
	eISZ_InteractiveSizingLast // Keep this as the last element
};

struct SInteractiveSizingParameterInfo
{
	TXString fDisplayName;
	WorldCoord fCurrentValue;
	WorldCoord fDefaultValue;
	bool fReadOnly;
	bool fSupported;

	SInteractiveSizingParameterInfo()
	{
		fDisplayName.Clear();
		fReadOnly = false;
		fSupported = false;
		fReadOnly = false;
		fCurrentValue = 0.0;
		fDefaultValue = 0.0;
	}

	SInteractiveSizingParameterInfo(TXString sDisplayName, bool bSupported, bool bReadOnly, WorldCoord paramDefaultValue, WorldCoord paramNewValue)
	{
		fDisplayName	= sDisplayName;
		fSupported		= bSupported;
		fReadOnly		= bReadOnly;
		fCurrentValue	= paramNewValue;
		fDefaultValue	= paramDefaultValue;
	}

	SInteractiveSizingParameterInfo(const SInteractiveSizingParameterInfo & inParam)
	{
		fDisplayName	= inParam.fDisplayName;
		fSupported		= inParam.fSupported;
		fReadOnly		= inParam.fReadOnly;
		fCurrentValue	= inParam.fCurrentValue;
		fDefaultValue	= inParam.fDefaultValue;
	}

	SInteractiveSizingParameterInfo& operator=(const SInteractiveSizingParameterInfo& inParam)
	{
		fDisplayName	= inParam.fDisplayName;
		fSupported		= inParam.fSupported;
		fReadOnly		= inParam.fReadOnly;
		fCurrentValue	= inParam.fCurrentValue;
		fDefaultValue	= inParam.fDefaultValue;

		return *this;
	}

	void reset() {
		fDisplayName.Clear();
		fSupported = false;
		fReadOnly = false;
		fCurrentValue = 0.0;
		fDefaultValue = 0.0;
	}
};

typedef std::vector<SInteractiveSizingParameterInfo> InteractiveSizingInformation;


enum EHandingType
{
	eHanding_OperativeHandDirection	= 0,
	eHanding_OperativeSideOfWall	= 1,
	eHanding_InteriorSide			= 2,
	eHanding_Last // Keep this as the last element
};
typedef std::vector<SInteractiveSizingParameterInfo> HandingInformation;


enum EISZ_ElevationSetAt {
	eISZ_ElevationSetAtHead = 0, // ElevationSetAt Head of the window
	eISZ_ElevationSetAtSill = 1, // ElevationSetAt Sill/Bottom of the Window(Default)
};

enum EISZ_ObjSupportCornerCnfg {
	eISZ_ObjDoesNotSupportCorner = 0,// Does not support corner (Default)
	eISZ_ObjSupportsCorner		 = 1	// Does support corner
};

enum EISZ_ObjectCornerConfig {
	eISZ_ObjCornerCnfgNotCorner		= 0, // Not corner (Default)
	eISZ_ObjCornerCnfgAtWallStart	= 1, // Corner window at wall start
	eISZ_ObjCornerCnfgAtWallEnd		= 2, // Corner window at wall end
	eISZ_ObjCornerCnfgAtWallEnds	= 3	 // Corner window at start and end(Span Wall)
};

enum EISZ_ResizeHandleLocation {
	eISZ_ResizeHandleAtWallCenterline 	= 0, // Align to insertion point of insert. (Default)
	eISZ_ResizeHandleAtLeftWallEdge	 	= 1, // Align to left wall edge
	eISZ_ResizeHandleAtRightWallEdge 	= 2	 // Align to right wall edge
};

enum EISZ_ShowZValueOnDatabar { 	// Hides the display of the Z value in the floating data bar.
	eISZ_ShowZValueOnDatabarHide = 0,	// Hide on Databar
	eISZ_ShowZValueOnDatabarShow = 1	// Show In Databar (Default)
};

enum EHandingOperativeHandDirection {  // eHanding_OperativeHandDirection
	eOperativeHandDirectionLeft		= 1,
	eOperativeHandDirectionRight	= 2
};

enum EHandingOperativeSideOfWall {		// eHanding_OperativeSideOfWall
	eOperativeSideOfWallIn	= 1,
	eOperativeSideOfWallOut	= 2
};

enum EHandingInteriorSide {
	eInteriorSideLeftSideOfWall		= 1,
	eInteriorSideRightSideOfWall	= 2
};


//================ New Parametric Message - Get Interactive Sizing Information ================
struct ParametricGetInteractiveSizingInformation : public ParametricMessage
{
	enum { kAction = 90 };
	ParametricGetInteractiveSizingInformation()
	{
		fAction = kAction;
		fInteractiveSizingInfo.clear();
	}
	InteractiveSizingInformation fInteractiveSizingInfo;
};

//================ New Parametric message - Set Interactive Sizing Information ================
struct ParametricSetInteractiveSizing : public ParametricMessage
{
	enum { kAction = 91 };
	ParametricSetInteractiveSizing(InteractiveSizingInformation sizingInfo)
	{
		fAction = kAction;
		fInteractiveSizingInfo = sizingInfo;
	}
	InteractiveSizingInformation fInteractiveSizingInfo;
};
//================================================

enum class EEquipmentItemDataContext
{
	Read,
	Write,
};

enum class EEquipmentItemField
{
	Make,
	Model,
	WidthMM,
	HeightMM,
	DepthMM,
	PowerW,
	WeightKG,
};

using TStringToEquipItemFieldMap = std::map<EEquipmentItemField, TXString>;

struct ParametricEquipmentItemDataMessage : public ParametricMessage
{
	enum { kAction = 92 };

	ParametricEquipmentItemDataMessage(EEquipmentItemDataContext context)
		: ParametricMessage( kAction )
		, fContext( context )
	{}

	EEquipmentItemDataContext	fContext = EEquipmentItemDataContext::Read;
	TStringToEquipItemFieldMap	fmapEquipItemFields;
};


//================ New Parametric message - Set Interactive Sizing Information ================

enum class EParamModification
{
	FlipOnObjectInfo,
	FlipHorizontal,
	FlipVertical,
	Mirror,
	Rotate,  //required? 
	ReverseWall,
	// Repeat Along Wall tool(symbols and PIOs) - No flip/mirror involved?
	// Repetitive Unit object - No flip/mirror involved? 
};

struct ParametricPreModificationMessage : public ParametricMessage
{
	enum { kAction = 93 };
	ParametricPreModificationMessage(EParamModification modificationID)
	{
		fAction = kAction;
		fModificationID = modificationID;
	}
	EParamModification fModificationID;
};
//================================================
// 
// //================ New Parametric Message - Get Interactive Sizing Information ================
struct ParametricGetHandingInformation : public ParametricMessage
{
	enum { kAction = 94 };
	ParametricGetHandingInformation()
	{
		fAction = kAction;
		fHandingInfo.clear();
	}
	HandingInformation fHandingInfo;
};

//================ New Parametric message - Set Interactive Sizing Information ================
struct ParametricSetHandingInformation : public ParametricMessage
{
	enum { kAction = 95 };
	ParametricSetHandingInformation(HandingInformation handingInfo)
	{
		fAction = kAction;
		fHandingInfo = handingInfo;
	}
	HandingInformation fHandingInfo;
};
//================================================
//====================================

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
		kAction_DoDoubleClick						=   8,
		kAction_DoDrawScrMod						=   9,
		kAction_DoUndrawScrMod						=  10,
		kAction_MouseMove							= 101,
		kAction_DrawingDoubleClick					= 102,
		kAction_Draw								= 103,
		kAction_GetStatus							= 105,
		kAction_OnSelectionChange					= 109,
		kAction_OnIdle								= 112,

#ifdef GS_USE_NEW_SELECTION_TOOL
		kAction_OnViewChange						= 117,		// NNA Internal USE
#endif

		kAction_OnUpdate2D3DCursor					= 118,		// ToolDef decides which cursor to use if action was handled by a ToolDef.
		kAction_OnGetWantsAutoPlane					= 119,		// ToolDef decides if it wants Autoplane behavior. The default is yes for Planar tools. The Rotate tool would like this and will return a non-zero value to get it.
		kAction_OnGetWantsPlanarSnapFiltering		= 120,		// ToolDef decides if it wants Planar snap filtering. The default is true for planar tools. The Attribute Mapping tool may want this for certain contexts.
		kAction_PreventsSnapLoupe					= 122,
		kAction_SupportsScreenPlane					= 123,		// New tool action to allow Active Plane to query the current tool to see if it
																// wants the screen plane item returning zero. Will provide screen plane if
																// tool flags are: (! (needsPlanarContext == false && needsScreenPlane == false && needs3DView == false)).
		kAction_OnDeleteKeyWithNoToolPts			= 124,		// The delete key is pressed with no tool points. Return kToolSpecialKeyEventHandled if tool handles it.
		kAction_OnEscapeKeyWithNoToolPts			= 125,		// The escape key is pressed with no tool points. Return kToolSpecialKeyEventHandled if tool handles it.
		kAction_OnSpecialKeyWithNoToolPts			= 126,		// Special key handling for Walkthrough Preferences for Gamer mode task. Return kToolSpecialKeyEventHandled if tool handles it.
		kAction_OnEnterReturnKeyForToolCompletion	= 127,		// Special key handling for Enter/Return key. Return kToolReadyToCompleteWithEnterReturnKey if tool can complete it.
		kAction_OnScreenPlaneToolCanWorkWith3DView	= 128,		// New tool action to allow ScreenPlane tools (like Zoom tool) to work in 3D views also.
		kAction_OnBlackBackgroundChange				= 129,		// We allow tool to register for kNotifyBlackBackgroundChanged. If it does, it will be called with this action.

		kAction_Draw_ActivePane						= 130,		// This is called in addition to kAction_Draw for the active view pane only. Used for tool that only wants to draw on the active pane.

		kAction_OnLayerChange						= 131,		// This is called when you change the layer scale. Used to update the preview of a default tool.
		kAction_UpdatePreviewOnParamChange			= 132,		// This is called when you change parameters for a PIO tool. Used to update the preview of the tool.
		kAction_SetFlyoverCenter					= 133,		// This is called when the user Ctrl Middle Mouse clicks while in Mouse Flyover tool.
		kAction_OnGetToolWantsWPConstrainedToView	= 134,		// This is called from CurrentToolAllowsWorkingPlaneConstraint() when view is flat like Front, Back.

#define ENABLE_RIGHT_MOUSE_DOWN_TOOL_MESSAGE 0
#if ENABLE_RIGHT_MOUSE_DOWN_TOOL_MESSAGE
		kAction_RightMouseDown						= 135		// The right mouse button is pressed down. Return kToolOverrodeRightMouseDownContext if tool handles it rather than displaying context menu.
#endif
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

struct ToolUpdatePrevewMatrixMessage : public ToolMessage
	// The Tool has requested to update the preview matrix with kToolSupportPreviewMatrixUpdate
{
	enum { kAction = 115 };

	ToolUpdatePrevewMatrixMessage() { fAction = ToolUpdatePrevewMatrixMessage::kAction; }

	TransformMatrix	fMatrix;		 // in/out -- current matrix; will use modified matrix after event
};

/////////////	-----------------------------------------------
///////////		BEGIN CONTROL DATA
/////////		-----------------------------------------------
///////
/////
///
//

/*!
 *  Text color tints - UI text colors
 *   cannot be directly specified from
 *   outside of UI code, as the colors
 *   may conflict with the color associated
 *   with a specific usage context, as
 *   imposed by the active UI appearance.
 *   Color tints are not guaranteed to
 *   appear as expected.
 */
enum class EUiControlTextTint: Uint8
{
    // Context-specific tints
    eDefaultTint = 0,
    eDisabledTint = 1,
    eRotatedCoordTint = 2,
    ePageBasedSymTint = 3,
    ePluginSymTint = 4,
    eGroupSymTint = 5,
    eAllLayersTint = 6,
    eCustomItem1Tint = 7,
    eAccentTint = 8,
    
    // Approximate color tints
    // (only present for compatibility
    // with legacy, user-selected
    // color reproduction behavior -
    // context-specific tints should
    // be used when possible, or amended
    // if a specific tint is absent)
    eGenericRedTint = 200,
    eGenericGreenTint = 201,
    eGenericBlueTint = 203,
    eGenericOrangeTint = 204,
    eGenericYellowTint = 205,
    eGenericBrownTint = 206,
    eGenericPurpleTint = 207,
    eGenericPinkTint = 208,
    eGenericGrayTint = 209,
	eGenericBlackTint = 210,
	eGenericWhiteTint = 211
};


/*!
 *  Classes and functions that support the
 *   usage of UI color tints (generalized
 *   application/modification of UI color
 *   tones that permit the UI to apply the
 *   appropriate contextual modifications
 *   required to promote element visibility /
 *   legibility).
 *
 *  @see EUiControlTextTint
 */
namespace CoreUiTintSupport
{
    /*!
     *  Converts a specific RGB color specification
     *   into a generalized UI tint
     *
     *  @param queryColor Specific RGB color specification
     *
     *  @return A color tint value that roughly corresponds to
     *          the provided RGB color specification
     *
     *  @author Ayodeji Oshinnaiye, August 9, 2018
     */
#if GS_MAC || (defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H))
    EUiControlTextTint ExpressColorAsTint(const COLORREF& queryColor);
#endif

    EUiControlTextTint ExpressColorAsTint(const GSColor& queryColor);
    
    /*!
     *  Expresses a tint as an approximate RGB
     *   color specification. This color specification
     *   should not be considered as the specific UI
     *   intepretation of the tint.
     *   (Primarily included for compatibility with
     *   legacy code)
     *
     *  @param queryTint A color tint specification
     *
     *  @return A color that corresponds to the color tint
     *          specification
     *
     *  @author Ayodeji Oshinnaiye, August 20, 2018
     */
#if GS_MAC || (defined(_INC_WINDOWS) && !defined(_EXCLUDE_WINDOWS_H))
	COLORREF ExpressTintAsColor(const EUiControlTextTint queryTint);
#endif
}

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
    EUiControlTextTint fTextTint;

	SControlData_StaticText()							{}
	SControlData_StaticText(const EUiControlTextTint textTint) { fDataValid = true; fTextTint = textTint; }
};

struct SControlData_ColorButton : public SControlDataBase
{
	Uint8	fColorRed;		// [set/get]
	Uint8	fColorGreen;	// [set/get]
	Uint8	fColorBlue;		// [set/get]
	float	fColorCyan;
	float	fColorMagenta;
	float	fColorYellow;
	float	fColorKey;

	enum ColorMode
	{
		ModeRGB = 0,
		ModeCMYK
	};
		
	ColorMode	fMode;
		
	SControlData_ColorButton()							{}
	SControlData_ColorButton(Uint8 r, Uint8 g, Uint8 b) { fDataValid = true; fColorRed = r; fColorGreen = g; fColorBlue = b; InitializeColors(ColorMode::ModeRGB);}
	SControlData_ColorButton(float c, float m, float y, float k) { fDataValid = true; fColorCyan = c; fColorMagenta = m; fColorYellow = y; fColorKey = k; InitializeColors(ColorMode::ModeCMYK);}
	
	SControlData_ColorButton(const TGSColorV2& color)
	{
		if(color.GetType() == TGSColorV2::TColorType::eRGB)
		{
			color.GetRGB8( fColorRed, fColorGreen , fColorBlue );
			InitializeColors(ColorMode::ModeRGB);
		}
		else
		{
			color.GetCMYK(  fColorCyan, fColorMagenta, fColorYellow, fColorKey );
			InitializeColors(ColorMode::ModeCMYK);
		}
	}
	
	void InitializeColors(ColorMode mode)
	{
		fMode = mode;
		
		if(fMode == ColorMode::ModeRGB)
		{
			TGSColorV2 color( fColorRed, fColorGreen, fColorBlue );
			color.GetCMYK( fColorCyan, fColorMagenta, fColorYellow, fColorKey );
		}
		else
		{
			TGSColorV2 color( fColorCyan, fColorMagenta, fColorYellow, fColorKey );
			color.GetRGB8( fColorRed, fColorGreen, fColorBlue );
		}
	}
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

struct SControlData_EditReal : public SControlDataBase
{
	EUiControlTextTint	fTextTint;

	SControlData_EditReal()										{}
	SControlData_EditReal(const EUiControlTextTint textTint)	{ fDataValid = true; fTextTint = textTint; }
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

// EObjectCutPlane is used by both SymDefType and ParametricType
enum class EObjectCutPlane : short
{
	kViewAsCutWhenCutInViewport = 1,
	kViewAsUncutBeyondWhenCutInViewport = 3,	// below (for horizontal sections), beyond (for vertical sections)
	kViewAsUncutBeforeWhenCutInViewport = 4		// above (for horizontal sections), before (for vertical sections)
};

// EMaterialsConstructionStandards contains the valid constants that represent
// the Materials' Construction Standards choices.
enum EMaterialsConstructionStandards
{
	kMaterialsStdOmniClass	= 0,
	kMaterialsStdUniClass	= 1,
	kMaterialsStdNone		= 2,
	kMaterialsStdTxtClass	= 3,
};

// Building materials supporting struct.
struct SCompoundSubmaterialData
{
	SCompoundSubmaterialData() {}
	SCompoundSubmaterialData(const TXString& inSubmaterialName, double inFraction)
	{
		fSubmaterialName = inSubmaterialName;
		fFraction = inFraction;
	}

	TXString	fSubmaterialName;
	double		fFraction = 0.0;
};
typedef std::vector<SCompoundSubmaterialData> CompoundSubmaterialDataVector;

enum class EEditPartContext
{
    Generically2d = 0,    ///< old school EnterLayer(..., edit3D=false,...)
    Generically3d,        ///< old school EnterLayer(..., edit3D=true,...)

    Top,            ///< list of 6 swap graphic faces, plus 3 swap cutplanes
    Bottom,
    TopBottomCut,
    Front,
    Back,
    FrontBackCut,
    Left,
    Right,
    LeftRightCut,

    WallHole,            ///< other edit contexts for symbols, etc
    WallClosure
};

// Hidden record format which will be added if a material was imported by the Imported by mtextur command - 
// using the new 2022 feature to create a Material resource.
#define kMTexturMaterialRecord "MTexturMaterialRecord"
