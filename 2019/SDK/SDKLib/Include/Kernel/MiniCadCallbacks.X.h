//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// This file defines all platform-independant information related to
//	or used by the SDK.
//



#ifndef _MINICADCALLBACKS_X_H_
#define _MINICADCALLBACKS_X_H_ 1

#pragma once

#include "GSTypes.h"
#include "GSString.X.h"
#include "GSLogging.h"
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

// this is a generic structure that can be used to confirm per-item operations with the List Browser, Tree Control, etc.
struct TItemMessageData
{
	Sint32 fControl;
	Sint32 fItemId;
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
	Sint32 fSourceControlID;
	Sint32 fSourceItemID;
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
	TTreeControlDropMessageData() { memset(this, 0, sizeof(TTreeControlDropMessageData)); }
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

const Uint32 kRotatedCoordStrColor = GenerateRGB(0, 0, 202);
const Uint32 kPageBasedSymStrColor = GenerateRGB(0, 120, 0);
const Uint32 kDefaultStringColor   = GenerateRGB(0, 0, 0);
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
	kListBrowserTile			= 9
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


//------------------------------------------------------------------------------------

#endif // _MINICADCALLBACKS_X_H_
