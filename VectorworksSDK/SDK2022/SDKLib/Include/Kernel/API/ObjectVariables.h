//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


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

		EVariableBlockType GetType() const { return eType; }

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
		} fData ;
		
		TXString	uStr;

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
	
	//const InsertModeType kSymInsertOnEdge						= -1;	// Insert on the nearest edge of the wall
	//const InsertModeType kSymInsertOnCenter					= 0;	// Insert on the center of the wall
	//const InsertModeType kSymInsertOnLeftEdge					= 1;	// Insert on the left edge of the wall
	//const InsertModeType kSymInsertOnRightEdge				= 2;	// Insert on the right edge of the wall
	//const InsertModeType kSymInsertOnCoreComponentCenter		= 3;	// Insert on the center of the wall core component
	//const InsertModeType kSymInsertOnCoreComponentLeftEdge	= 4;	// Insert on the left edge of the wall core component
	//const InsertModeType kSymInsertOnCoreComponentRightEdge	= 5;	// Insert on the right edge of the wall core component
		
const short ovPluginBreakMode			= 124 ; 	// short, specifies how the wall is broken where the symbol is inserted - Public for VS

	//const BreakModeType kPluginFullBreakWithCaps = 1;	standard for most symbol insertions
	//const BreakModeType kPluginFullBreakNoCaps	= 2;	no cap lines, but the wall is broken
	//const BreakModeType kPluginHalfBreak			= 3; 	for edge insertion only;
	//const BreakModeType kPluginNoBreak			= 4;	no break in the wall		



// Symbol definiton selectors
// ----------------													
const short ovSymDefInsertMode			= 125 ; 	// short - where to insert the symbol in the wall - Public for VS
	
	//const InsertModeType kSymInsertOnEdge						= -1;	// Insert on the nearest edge of the wall
	//const InsertModeType kSymInsertOnCenter					= 0;	// Insert on the center of the wall
	//const InsertModeType kSymInsertOnLeftEdge					= 1;	// Insert on the left edge of the wall
	//const InsertModeType kSymInsertOnRightEdge				= 2;	// Insert on the right edge of the wall
	//const InsertModeType kSymInsertOnCoreComponentCenter		= 3;	// Insert on the center of the wall core component
	//const InsertModeType kSymInsertOnCoreComponentLeftEdge	= 4;	// Insert on the left edge of the wall core component
	//const InsertModeType kSymInsertOnCoreComponentRightEdge	= 5;	// Insert on the right edge of the wall core component
		
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
const short ovLayerPhotoScale			= 149;		//	double 100.0/VWScaleFactor; layer photographic scale (for example, photographicScale == .5, scaling is 200% )

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


// Texture selectors (kTextureNode)
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
	const short	ovTextureBitmapOrigin 		= 520;		// WorldPt, in - Not for public use
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


// Arc path wall selectors (kWallNode)
// --------------
const short ovRoundWallCounterClockwise	= 570;		// Boolean, read only, TRUE == counterclockwise, FALSE == clockwise - Public for VS
const short ovRoundWallRadius			= 571;		// DOUBLE, round wall thickness, read/write - Public for VS

const short ovLayerCropRect				= 590;		// WorldRect, read only, - Not for public use
const short	ovLayerRWBackground			= 591;		// Sint32 (SysName), read/write - Public for VS
const short ovLayerHDRIBackground		= 592;      // Sint32 RefNumber of the HDRI background associated with a layer, read only - Public for VS

// Wall selectors (kWallNode)
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
const short ovTextIsRightToLeft			= 688;		// Boolean, read only - Not for public use
const short ovTextNumLines				= 689;		// Boolean, read only - Not for public use

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

const short ovPositionLocked			= 709;		// Boolean, read - Public for VS : DLVPs can be position locked. GridAxisInstances are always position locked. Groups are position locked if they contain any.

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
const short ovViewportTransformMatrix		= 1049;		// TransformMatrix	read/write
const short ovViewportViewMatrix			= 1050;		// TransformMatrix	read/write
const short ovViewportOperatingTransform	= 1051;		// TransformMatrix	read
const short ovViewportUnscaledBoundsWithoutAnnotations	= 1052;		// WorldRect  read
const short ovViewportResetForOnlyAnnotationsChange = 1053; // void write
const short ovIsSectionViewport				= 1054;		// Boolean read only - indicates whether the viewport is a section viewport - Public for VS
const short ovSheetLayerSectionViewportViewMatrix	= 1055;		// TransformMatrix	read
const short ovSectionViewportSectionViewMatrix = 1056;		// TransformMatrix	read/write
const short ovViewportAttachDefaultRenderOptions = 1057;	// Boolean(ignored) write
const short ovViewportAttachDefaultCustomRenderWorksRenderOptions = 1058;	// Boolean(ignored) write
const short ovViewportDisplay2DComponents	= 1059;	// Boolean read/write
const short ovViewportHiddenLineDisplay2DFills		= 1060;	// Boolean read/write
const short ovViewportAttachDefaultLightingOptions	= 1061;	// void write
const short ovViewportCreateDefaultEditableGroups	= 1062;	// void write
const short ovViewportPrivateLayer					= 1063;	// MCObjectHandle read
const short ovSectionViewportDisplayObjectsBeyondCutPlane	= 1064;	// Boolean read/write
const short ovSectionViewportDisplayObjectsBeforeCutPlane	= 1065;	// Boolean read/write
const short ovViewportHiddenLineDisplay2DFillsAllowed		= 1066; // Boolean read
const short ovSectionViewportCastShadowsFromRemovedPortion	= 1077;	// Boolean read/write
const short ovSectionViewport2DResultsMerged				= 1078;	// Boolean read/write
const short ovSectionViewport2DAttributesUseClass			= 1079;	// Boolean read/write - must be set true before you set class with ovSectionViewport2DAttributesClass
const short ovSectionViewport2DAttributesClass				= 1080;	// RefNumber read/write
const short ovSectionViewport2DOtherAttribsUseClass			= 1081;	// Boolean read/write - must be set true before you set class with ovSectionViewport2DOtherAttribsClass
const short ovSectionViewport2DOtherAttribsClass			= 1082;	// RefNumber read/write

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
const short ovArchStyleCurtainWallNumGridRows			= 1382; // short		read	- (Wall Style only) - Public for VS
const short ovArchStyleCurtainWallNumGridColumns		= 1383; // short		read	- (Wall Style only) - Public for VS
const short ovArchStyleCurtainWallGridOffset			= 1384; // WorldPt		read	- (Wall Style only) - Public for VS
const short ovArchStyleCurtainWallGridRowSpacing		= 1385; // WorldCoord	read	- (Wall Style only) - Public for VS
const short ovArchStyleCurtainWallGridColumnSpacing		= 1386; // WorldCoord	read	- (Wall Style only) - Public for VS

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

const short ovRenderStyleRedshift				= 1289; //Boolean	read only

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
const short ovTextStyleFontID					= 1370;		// short			- the font id in the text style resource

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

const short ovClipCube_Enable						= 1560;
const short ovClipCube_Transform					= 1561;
const short ovClipCube_RotationAngle				= 1564;
const short ovClipCube_Size							= 1565;
const short ovClipCube_Fit							= 1568;

// Building material node data selector constants: Construction
const short ovMaterialIsVolumetric						= 1569;
const short ovMaterialCategory							= 1570;
const short ovMaterialStandard							= 1571;
const short ovMaterialReferenceID						= 1572;
const short ovMaterialClassificationDescription			= 1573;
const short ovMaterialManufacturer						= 1574;
const short ovMaterialProductModel						= 1575;
const short ovMaterialProductName						= 1576;
const short ovMaterialProductDescription				= 1577;
const short ovMaterialProductURL						= 1578;
// Building material node data selector constants: Physical
const short ovMaterialSpecificGravity					= 1579;
const short ovMaterialModulusOfElasticity				= 1580;
const short ovMaterialYieldStrength						= 1581;
const short ovMaterialTensileStrength					= 1582;
const short ovMaterialSpecificHeat						= 1583;
const short ovMaterialEmissivity						= 1584;
const short ovMaterialAlbedo							= 1585;
const short ovMaterialThermalExpansionCoefficient		= 1586;
const short ovMaterialLambda							= 1587;
const short ovMaterialEmbodiedCarbon					= 1588;
const short ovMaterialSoundVelocity						= 1589;
const short ovMaterialDensity							= 1590;
const short ovMaterialAcousticImpedance					= 1591;
const short ovMaterialUsesSpecificGravity				= 1592;
const short ovMaterialUsesModulusOfElasticity			= 1593;
const short ovMaterialUsesYieldStrength					= 1594;
const short ovMaterialUsesTensileStrength				= 1595;
const short ovMaterialUsesSpecificHeat					= 1596;
const short ovMaterialUsesEmissivity					= 1597;
const short ovMaterialUsesAlbedo						= 1598;
const short ovMaterialUsesThermalExpansionCoefficient	= 1599;
const short ovMaterialUsesLambda						= 1600;
const short ovMaterialUsesEmbodiedCarbon				= 1601;
const short ovMaterialUsesSoundVelocity					= 1602;
const short ovMaterialUsesDensity						= 1603;
const short ovMaterialUsesAcousticImpedance				= 1604;

const short ovMaterialIsSurfaceAreaMeasure				= 1605;

const short ovMaterialDescription						= 1606;
const short ovMaterialMark								= 1607;
const short ovMaterialKeynote							= 1608;

// Building material node data selector constants: Construction
const short ovMaterialCost								= 1609;
const short ovMaterialSource							= 1610;
const short ovMaterialFinish							= 1611;
// Building material node data selector constants: Physical
const short ovMaterialSlipResistance				    = 1612;
const short ovMaterialUsesSlipResistance				= 1613;
// Building material, so IFC can know custom record name
const short ovMaterialCustomRecordName					= 1614; // string read

// Additional Light selectors
const short ovLightUseEmitter							= 1620;	// Boolean
const short ovLightEmitterBrightness					= 1621;	// double_gs - >= 0 values
const short ovLightBrightnessUnit						= 1622;	// short - 0..3 - eLumens, eCandelas, eLux, eFootcandels
const short ovLightUseTemperature						= 1623;	// Boolean
const short ovLightTemperature							= 1624; // double_gs - >= 0 values
const short ovLightCausticPhotons						= 1625; // Uint32 - kLightCausticNone = 0, kLightCausticLow = 10000, kLightCausticMedium = 100000, kLightCausticHigh = 1000000, kLightCausticVeryHigh = 10000000 
const short ovLightCausticOnly							= 1626; // Boolean

const short ovResourceFolderResourceType				= 1630; // TDType read,write

const short ovArchObjectStyle							= 1635; // InternalIndex read,write

const short ovApplyMaterial								= 1640; // InternalIndex write

