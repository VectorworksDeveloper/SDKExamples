//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// This file defines constants for the interface between the VectorWorks application and the SDK Plug-ins.
// This file is shared between the VectorWorks application and SDK Plug-ins code.
//

#ifndef _MINICADHOOKINTF_
#define _MINICADHOOKINTF_

#pragma once

#if TARGET_RT_MAC_CFM
	#include <MixedMode.h>
#endif

#include "GSDebug.h"

#if defined(_MINICAD_EXTERNAL_) && !defined(__EXTERNDEFINES__) && __MWERKS__
	#error GSBUG.h, GSTEST.h, or GSRELEASE.h MUST be included in your C/C++ compiler preferences when compiling under Metrowerks.
#endif

////////////////////////
// MCObjectHandle
//   In VectorWorks, this allows access to BlankHandle
//   In externals, this provides opaque access
//   The VectorWorks internal version is in InitGlobals.h
////////////////////////

#ifndef _MINICAD_
	typedef GSHandle MCObjectHandle;
#endif

/////////////	-----------------------------------------------
///////////		BEGIN MENU DEFINITION PROCEDURE PARAMETERS DESCRIPTIONS -------------------------------------------------
/////////		-----------------------------------------------
///////
/////
///
//
//

typedef Sint32 ToolPropID;


/////////////////////////////
//	Extended Tool Properties
const ToolPropID kToolXPropSelectionChange = 1;		// tool wants selection change events.
const ToolPropID kToolXPropSendModeBarEventOnEnterEscKeys = 2;			// sends (0, 0, 0) ti the CTool_EventSink::DoModeEvent
const ToolPropID kToolXPropWantsMoveSelection2D = 3;		// tool wants ToolMoveSel2DMessage::kAction event with nudge and move 2D commands.
const ToolPropID k2DToolEnabledInStackedLayerMode = 4;		// 2D tool wants to be enabled in Unified View.
const ToolPropID kShortCutKeyCompletesToolAction = 5;		// pressing a shortcut key completes the tool action for path-based tools
const ToolPropID kToolEnablePickDeepInViewportAnnotatonsMode = 6;		// the tool wants to pick deep inside viewport annotations.
const ToolPropID kToolSupportPreviewMatrixUpdate = 7;					// the tool wants to update the preview matrix before draw
const ToolPropID kToolXPropBoomerangSelection = 7;					// the tool wants alt/option key to boomerang into the cursor tool to allow selection

/////////////////////////////

//	Force the imaging flags for release build

#define ENHANCED_IMAGING	1
#define UPDATED_SELECTION	1
#define ANIMATED_SELECTION	1
#define ANIMATED_SEL_SPEC	0


//----------------------------------------------------------------------------
// Default tool informatoin
// ISDK::CallStandardDefaultTool type
enum EDefaultToolType
{
	eDefaultToolType_Point,
	eDefaultToolType_Line,
	eDefaultToolType_Rect,
	eDefaultToolType_Poly2D,
	eDefaultToolType_Poly3D,
};
											
													
//////////////////////////
//
// Tool message1 constants.
const Sint32 kSetupSetdownPauseRestoreFlag = 1;		//	Sent in the Message1 parameter with ToolSetupMessage::kAction_SetUp and ToolSetupMessage::kAction_SetDown action calls.
													//	This message allows action handling to distinguish the Setup and SetDown action calls.
													//	When tools are being paused and restored they are sent this value in the message1 
													//	parameter.
													  
const Sint32 kToolGenericStateChangeKey = 1;			//	Sent in the Message1 parameter with ToolGenericStateChangeMessage::kAction action call.
													//	A key has been pressed. See ToolGenericStateChangeMessage::kAction description above.
const Sint32 kToolGenericStateChangeView = 2;			//	Sent in the Message1 parameter with ToolGenericStateChangeMessage::kAction action call.
													//	The current view has been changed. See ToolGenericStateChangeMessage::kAction description above.

const Sint32 kClearingAllToolPoints = 1;				// ToolDef's message1 parameter when action==ToolPointRemovedMessage::kAction.

// Tool return constants

const Sint32 kToolDidNotChangeDoc			= 1L;		//	observed after ToolCompleteMessage::kAction action handler call.  It prevents 
													//	the "dirty"flag for the document from being set. 
const Sint32 kToolCouldNotInitialize		= -1L;		//	Observed after ToolInitXPropsMessage::kAction action handler.  Return this if the tool
													//	failed to initialize. 
const Sint32 kToolCouldNotSetUp			= -1L;		//	Observed after ToolSetupMessage::kAction_SetUp action handler.  Return this if the tool fails to set up.
const Sint32 kToolSwitchToCursor			= 2L;		//	cancel, remove all tool points, and switch to cusor tool
const Sint32 kHandledDocumentDoubleClick 	= 4L;		// 	Observed after ToolMessage::kAction_DrawingDoubleClick action handler.  Return this if the tool's
													//	ToolMessage::kAction_DrawingDoubleClick action handler wants the second click entered as a tool point.
const Sint32 kToolWaitingForFirstPoint	= 5L;		// 	Observed after ToolMessage::kAction_GetStatus action handler.  Return this if tool is 
													//	waiting for first point.
const Sint32 kToolCollectingPoints		= 6L;		// 	Observed after ToolMessage::kAction_GetStatus action handler.  Return this if tool is still
													//	collecting points.
const Sint32 kToolWaitingForMouseUp		= 7L;		// 	Observed after ToolMessage::kAction_GetStatus action handler.  Tool returns this if it 
													//	wants the next mouse up as a tool point.  
const Sint32 kToolCompleted				= 8L;		// 	Observed after ToolMessage::kAction_GetStatus action handler.  Will cause VW to call 
													//	the plug-in with ToolCompleteMessage::kAction action
const Sint32 kToolCancel					= 9L;		// 	removes all tool points

const Sint32 kToolSpecialKeyEventHandled   = 1; 	// 	observed by:
													//		ToolMessage::kAction_OnDeleteKeyWithNoToolPts
													//		ToolMessage::kAction_OnEscapeKeyWithNoToolPts

const Sint32 kToolMoveSel2DlEventHandled   = 1; 	// 	observed by:
													//		ToolMoveSel2DMessage::kAction
const Sint32 kToolHandledViewChange = 1;

const Sint32 kToolHasContextualHelp		= 10L;

const Sint32 kToolDoesNotHandleOnUpdate2D3DCursor   = 0; 	// 	observed by ToolMessage::kAction_OnUpdate2D3DCursor event caller.

// The non-zero return constants need to be unique
const Sint32 kToolWants2DCursor   = 11L;					// 	observed by ToolMessage::kAction_OnUpdate2D3DCursor event caller.
const Sint32 kToolWants3DCursor   = 12L;					// 	observed by ToolMessage::kAction_OnUpdate2D3DCursor event caller.
const Sint32 kToolHandles2D3DCursor   = 13L;				// 	observed by ToolMessage::kAction_OnUpdate2D3DCursor event caller.

#if UPDATED_SELECTION
	//	SUPPORT_OBJECT_GRIPS goes along with UPDATED_SELECTION.  When defined
	#define SUPPORT_OBJECT_GRIPS
#endif

#ifdef SUPPORT_OBJECT_GRIPS
const Sint32 kToolProvideObjectGripsNO		= 0L;	// observed by the ToolProvideObjGripsMessage::kAction action caller.  THe reshape Handles/Grips WILL NOT be drawn.
const Sint32 kToolProvideObjectGripsYES		= 1L;	// observed by the ToolProvideObjGripsMessage::kAction action caller.  THe reshape Handles/Grips WILL not be drawn.
#endif

const Sint32 kToolWantsAutoPlane			= 11L;	// Returning zero gives default behavior which is defined to be true for Tools that are using planar snapping.
const Sint32 kToolDoesNotWantAutoPlane		= 12L;
const Sint32 kToolNeedsAutoPlane			= 13L;

const Sint32 kToolPlanarSnapFiltering		= 13L;	// Returning zero gives default behavior which is defined to be true for Tools that are using planar snapping.
const Sint32 kToolDoesNotWantPlanarSnapFiltering	= 14L;

const Sint32 kToolSupportsScreenPlaneNo		= 16L;          // The active Plane control WILL NOT provide the screen plane item
const Sint32 kToolSupportsScreenPlaneYes    = 17L;              //  The active Plane control WILL provide the screen plane item

const Sint32 kToolReadyToCompleteWithEnterReturnKey = 18L;		// Observed by kAction_OnToolCompletesOnEnterReturnKey by the temporary tool: TGetIntersectingWalls.

const Sint32 kToolCanWorkIn3DViews		= 19L;		// Observed by kAction_OnScreenPlaneToolCanWorkWith3DView by Zoom tool to allow in 3D views.
const Sint32 kToolCanNotWorkIn3DViews	= 20L;		// Observed by kAction_OnScreenPlaneToolCanWorkWith3DView by Zoom tool to allow in 3D views.

//
///
/////
///////
/////////       ---------------------------------------------
///////////		END TOOL DEFINITION PROCEDURE PARAMETERS DESCRIPTIONS -------------------------------------------------
/////////////	---------------------------------------------







/////////////	-----------------------------------------------
///////////		BEGIN MENU DEFINITION PROCEDURE PARAMETERS DESCRIPTIONS -------------------------------------------------
/////////		-----------------------------------------------
///////
/////
///
//
//	
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Menu messages
struct MenuNotifyMessage;
struct MenuItemEnabledMessage;
struct MenuDoInterfaceMessage;
struct MenuAddItemsMessage;
struct MenuCheckHiliteMessage;
struct MenuItemDisplayContextualHelpMessage;
struct MenuItemSpec;
struct MenuToolActionHandlerParams;

// Menu return constants
const Sint32 kMenuDidNotChangeDoc		= 1L;
const Sint32 kMenuHandledEvent			= 2L;
const Sint32 kMenuItemIsEnabled			= 3L;
const Sint32 kMenuItemIsDisabled		= 4L;
const Sint32 kMenuNoSuchItem			= 5L;
const Sint32 kMenuItemSecurity			= 6L;
const Sint32 kMenuRunTemp2DTool			= 7L;		//	Returned when Menu wants to get Interactive 2D points from the 
													//	documnet.  See MenuToolActionHandlerParams::kAction for more.
const Sint32 kMenuRunTemp3DTool			= 8L;		//	Returned when Menu wants to get Interactive 2D points from the 
													//	documnet
const Sint32 kMenuItemHasContextualHelp	= 9L;
//
///
/////
///////
/////////       ---------------------------------------------
///////////		END MENU DEFINITION PROCEDURE PARAMETERS DESCRIPTIONS -------------------------------------------------
/////////////	---------------------------------------------

const Sint32 kGUIItemWillHaveHelpUponRelease = 0xFFFFFF;







/////////////	-----------------------------------------------
///////////		BEGIN OBJECT DEFINITION PROCEDURE PARAMETERS DESCRIPTIONS -------------------------------------------------
/////////		-----------------------------------------------
///////
/////
///
//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 	Object Definition Procedure (ODP) action/Event descriptions:
//
//															Message:					Result:
//	Action						Task							Gets						Returns
//	------------------------------------------------------------------------------------------------------------------------------
//	ParametricRecalculate::kAction		Regenerate objects					0								0
//	ParametricPreferencesMessage::kAction		maybe pose preference dialog		0 or parmFormat					0 or kParametricNotImplemented, kParametricPrefOK, kParametricPrefCancel
//	
//	
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef Sint32 ObjectPropID;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Plug-in Object Extended Properties descriptions:
//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
//                         Property ID               //  Has Associated     //  Description:
//                                                   //     Event(s)        //
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropEditGroup = 1;           //        NO           //  Object has non-default "Enter Group" behavior.  PIO objects can enter the profile or path group 	
//                                                   //                     //  directly.  See kObjectEditGroupPropertyID property values below for more.
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHasLayerScaleDeps = 2;   //        NO           //  Object wants to be reset with when its layer scale changes.
//                                                   //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropSpecialEdit = 3;	     //  DEPENDS on         //
//                                                   //  property value.    // Object has non-default behavior when "Edit..." command is invoked.
//                                                   //                     // Cursor double-click also invokes this "Edit..." behavior.
//                                                   //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropPreference = 4;		     //        YES          // Object Definition Procedure (ODP) handles ParametricPreferencesMessage::kAction event.
//                                                   //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDirectModeling = 5;		 //        YES          // Object Definition Procedure (ODP) handles handles Direct Modeling events.
//                                                   //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropAttributeTool = 6;		 //        YES          // Object Definition Procedure (ODP) handles handles Attribute Mapping events.
//                                                   //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropPreventWallInsertion = 7;//        NO           // Object does NOT want to be inserted into walls.  Observed by the 2D cursor tool
//                                                   //                     // to prevent dragging into a wall.
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHasUIOverride = 8;		 //  DEPENDS on         //
//                                                   //  property value.    // Object Definition Procedure (ODP) adds widgets to Object Info Palette in kObjXPropInitXProperties event handler
//                                                   //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropCustomCursorResize = 9;	 //       YES           //
//       // boolean value                            //                     // The O
//      NNA under development                        //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropAcceptsMarkers = 10;     //                     //
//       // unsigned char                            //                     // 
//                                                   //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDefaultPropertyUI = 11;	 //         NO          //
//       // unsigned char                            //                     // The bits in this property describe the UI displayed
//       // NNA under development                    //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXHasCustomWidgetVisibilities = 12;//      YES        // OnObjectWidgetPrepCall::kAction
//       // boolean                                  //                     // 
//       NNA under development                       //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXHandlesCommand = 13;	     //                     // Set to TRUE to receive events from Rotate menu commands (Rotate 2D/3D, Rotate Left/Right, Flip),
//       // boolean                                  //                     // from Rotate tool and Mirror tool. The object accepts OnModifyObjectCommand event.
//                                                   //                     // Return kObjectEventNoErr if the transformation is applied. If the event is not overriden
//                                                   //                     // or to handle different subtypes from the legacy ObjectCommand structure, use OnDefaultEvent.
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXIs2DSurfaceEligable = 14;    //                     //
//       // boolean                                  //                     // 
//       Weiler operations operate on 2D path        //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropRotatesWithVCS = 15;	 //                     //
//       // boolean                                  //                     // 
//       Plug-in objects rotates with plan rotation  //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropCustomHideFactor = 16;	 //         NO          // The parametric object provides custom scale threshold to be used to hide inner objects
//       // double                                   //                     // when displaying the object in a layer or VP
//		 Plug-in provides custom hide factor		 //                     // See documentation for more info.
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXHasCustomWidgetValues = 17;  //         YES         // OnObjectWidgetValueCall::kAction
//       // boolean                                  //                     // 
//       Plug-in object has custom widget values     //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropAcceptStates = 18;		 //         YES         // The parametric accpets ObjectState::kAction event
//       // Boolean                                  //                     // event value is TParametricStateFlags
//		 Plug-in accepts states						 //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropAcceptStatesInternal = 19;//        NO          // The plug-in will receive about to be delete and duplicate (internal) states through kObjXPropAcceptStates
//       // Boolean                                  //                     // Mush have kObjXPropAcceptStates enabled
//		 Plug-in accepts about to be deleted state	 //                     // Note! This is isoleted option to improve speed of plug-ins that are not interested in delte events
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropPreserveContents = 20;	 //         NO          // VectorWorks will not delete the contents of the parametric
//       // Boolean                                  //                     // before reset
//		 VW wont delete contents before reset		 //                     // 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHasContextMenu = 21;     //         YES         // Sends ObjectContextMenuEvent::kAction_Init and ObjectContextMenuEvent::kAction_Event
//       // Boolean                                  //                     // The parametric can build up context menu and respont to context menu items selection
//		 Parametric has custom context menu			 //                     // 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHasComponents = 22;		 //                     // The parametric defines components
//       // boolean                                  //                     // 
//		 Plug-in has components						 //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropResetBeforeExport = 23;  //         NO          // This plugin will be reset before Print or Export
//       // boolean                                  //                     // 
//		 Reset before Printing or Export			 //                     //
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropShowOthersEditGroup = 24;//         NO          // Show others when editing the selected special group.
//       // Sint8 (kObjectEditGroupPropertyID)		 //                     // - kObjXPropEditGroupProfile - editing only the profile group shows the others;
//		 Reset before Printing or Export			 //                     // - kObjXPropEditGroupPath - editing only the path profile group shows the others;
//													 //						// - kObjXPropEditGroupCustom - editing any special group shows the others;
//													 //						// - kObjXPropEditGroupDefault - undefined (doesnt show anything)
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropRedSymbolIsStyle = 25;	 //         NO          // Red Symbol of this object can be used to drag&drop
//													 //						// over existing instances to copy the attributes
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHasAttrMappingGeom = 26; //         YES         // Sends ObjectGetSpecificGeometryCall::kAction with message is (OnObjectGetSpecificGeometry*)
//       // Boolean                                  //                     // The parametric can provide geometry for attribute mapping tool (use ISDK::GSNewObjectHandle to create the geometry handle)
//		 Parametric has attribute mapping geometry   //                     // 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHasSectionVPGeom = 27;   //         YES         // Sends ObjectGetSpecificGeometryCall::kAction with message is (OnObjectGetSpecificGeometry*)
//       // Boolean                                  //                     // The parametric can provide geometry for the section viewport (use ISDK::GSNewObjectHandle to create the geometry handle)
//		 Parametric has section viewport geometry    //                     // 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHasLayerElevDeps = 28;	 //         NO          // Resets the parametric if the layer elevation changes
//       // Boolean                                  //                     // 
//		 Parametric is dependent on the layer elev	 //                     // 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHasLayerHeightDeps = 29; //         NO          // Resets the parametric if the layer height changes
//       // Boolean                                  //                     // 
//		 Parametric is dependent on the layer height //                     // 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropSupportProxyObjects = 30;//         NO          // The parametric can define proxy objects. Additional resets will be called for each proxy passing the proxy parametric handle.
//       // Boolean                                  //                     // Also, the object will aways reset on move, rotate, and paste
//		 The parametric can define proxy objects     //                     // 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropResetOnMoveInViewport = 31;//        NO         // The parametric can reset on move or rotate in viewports
//       // Boolean                                  //                     // 
//		 The parametric can reset                    //                     //
//				on move or rotate in viewports       //                     // 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropShowPrefDialogWhen = 32;//			NO			// Controls whether how and a paremetric will show its preferences dialog when objects are created
//		// Sint8 (kObjectEditGroupPropertyID)		//						// - kCustomObjectPrefNever - never show the preferences dialog when creating the object
//													//						// - kCustomObjectPrefAlways - always show the preferences dialog when creating the object
//													//						// - kCustomObjectPrefNew - only show the prefs dialog the first time creating the object
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropLeaderLinePtIndex = 33;	 //			NO			// Controls whether how and a paremetric will be recognized by the align leader line menu command
//		// Sint8									 //						//   the provided value is the index of the control point parameter's X value. Y value should be the parameter with the next numeric index
//													 //						//   for more advanded support see VCOM interface VectorWorks::Extension::ILeaderLineProvider
//													 //						// 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropLabelPtIndex = 34;	 	 //			NO			// Controls whether how and a paremetric will be recognized by the align leader line menu command
//		// Sint8									 //						//   the provided value is the index of the label control point parameter's X value. Y value should be the parameter with the next numeric index
//													 //						//   for more advanded support see VCOM interface VectorWorks::Extension::ILeaderLineProvider
//													 //						// 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDataNameDisabled = 35;	 //			NO			// Controls whether the name field on the data pane should be disabled
//		// Boolean									 //						//   Set TRUE if the field needs to be disabled
//													 //						//   
//													 //						// 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropSpecialCtrlClickEdit = 36;//		YES  		// Send ParametricSpecialEditMessage::kAction with kObjectEdit_CtrlClick reason
//		// Boolean									 //						//   Sent when the cursor tool is used to control+click on the parametric object
//													 //						//   
//													 //						// 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDocumentShadowIndex = 37;//			NO			// Controls whether and how a parametric will be recognized when document shadow is changed
//		// Sint8									 //						//   the provided value is the index of the boolean parameter for whether object uses document shadow
//													 //						//   for more advanced support see VCOM interface VectorWorks::Extension::IDocumentShadowProvider
//													 //						// 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropGetCurtainWallEvents = 38;//		NO			// Controls whether a parametric will be recieved Curtain Wall related events
//		// Boolean									 //						//   
//													 //						// 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDirectionArrow = 39;     //			NO			// Controls whether the direction arrow should be displaied
//		// Sint8									 //						//   Set TRUE if the arrow should be displaied
//													 //						//   
//													 //						// 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropIsSymbolBased = 40;      //			NO			// Controls whether the object is symbol based and to show context menu "Locate Symbol In Resource Browser"
//		// Boolean									 //						//   Set TRUE if the context menu should be displaied
//													 //						//   
//													 //						// 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropShowLinearDirection = 41;//			NO			// Controls whether the a linear parametric object supports display of the line direction similar to the line object
//		// Boolean									 //						//   Set TRUE if the context menu should be displaied
//													 //						//   The actual display is controlled by varShowLinearDirectionMarker
//													 //						//   e.g. the line object OIP will display a check box that get/set the varShowLinearDirectionMarker
//													 //						//        the parametric must to the same in order to replicate this behavior
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropTextStyleSupport = 42;   //			NO			// Controls whether parametric objects can use class text style attribute and get Text Style on OIP 
//		// Boolean									 //						//   Set TRUE if the object supports this
//													 //						//   e.g. Almost all text-related PIOs set this yes, for support by default. North Arrow does not; it doesn't
//													 //						//         support style at all.  General Notes does not because it privately handles title vs note styling.
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropUnused = 43;			//						// Formally kObjXPropResetObjectInWall but now is no longer available. 
//		// Boolean									 //						//  
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontApplyAttrChangesToSpGroup= 44;// NO		    // When set to true this will cause attribute changes on this parametric to be skipped for this parametric
//		// Boolean									 //						//   object's special groups.
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontShowZLocation = 45;  //			NO			// When set to true will remove the Z coordinate for the location widget in the OIP for the parametric
//		// Boolean									 //						//  
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropUpdateAfterDocUnitsChange = 46;//	NO			//	Mark the object to be notified when the document units are changed
//		// Sint8									 //						//   See applicable constants defined below 
//													 //						//   e.g. kObjXPropResetWhenChangedLinearDim + kObjXPropResetWhenChangedAreaDim
//													 //						//			would notify reset the parametric when linear and area dimentions change
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropGetDragEvents = 47;      //		NO				// Controls whether a parametric will recieve Drag events allowing it to draw custom geometry
//		// Boolean									 //						//   
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropOIPNameHidden = 48;      //			NO			// Controls whether the name field on the OIP should be hidden
//		// Boolean									 //						//   Set TRUE if the field needs to be hidden
//													 //						//   
//													 //						// 

//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------												 //						// 
const ObjectPropID kObjXSupportsStyles = 49;		//		NO				// Controls whether a parametric type support plug-in styles
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------												 //						// 

const ObjectPropID kObjXPropSupportGenericStoryLevel = 50;//		NO		// Controls whether a parametric object supports the generic story level.
//													 //						//   Generic story level support allows the Z coordinate of the parametric object to be linked to a story level. 
//		// Boolean									 //						//   Set TRUE if the parametric object should support this.
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------			
const ObjectPropID kObjXPropUseLayerCutPlane  = 51; //	0				// Controls whether a parametric object supports Layer Cut Plane values.
//													//						// See below for supported values
//		// Sint8									//						//

//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------												 //						// 
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropAllowFreeHybrid2DPath = 52;	//		NO			// Controls whether a Hybrid 2D Path parametric can have a path on a different plane than the object 
//		// Boolean									 //						//   
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------	//						// 
const ObjectPropID kObjXPropSupportResourcePopup = 53;//		NO			// Controls whether the default tool of a parametric will show the resource popup
//		// Boolean									 //						//   Set TRUE if the the resource popup should be used
//													 //						//
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropSupportSaveOipButton = 54;//		NO			// Controls whether the OIP of a parametric object will show the "Save *..." button
//		// Boolean									 //						//   Set TRUE if the button should be shown
//													 //						//
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropSupportReplaceOipButton = 55;//		NO		// Controls whether the OIP of a parametric object will show the "Replace *..." button
//		// Boolean									 //						//   Set TRUE if the button should be shown
//													 //						//
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHideHeightBreakInWall = 56;//		NO			// Set to True to hide the height value for objects in walls
//		// Boolean									 //						//
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropGetWorksheetEvents = 57;//		NO			// Set to True to recieve worksheet events
//		// Boolean									 //						//
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontShowHideStyleParam = 58;//		NO			// Set to True to hide the Hide Style Parameters checkbox for objects supporting styles
//		// Boolean									 //						//
//													 //						//
//--------------------------------------------------//--------------------//---------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropRscPopupUseActiveSymDef = 59;//		NO			// Controls whether the default tool of a parametric will use the active symbol as current selection in 
//		// Boolean									 //						// the resource popup. Suitable place to set this property is OnResourceBrowserDoubleClickOnSymbol event. 
//													 //						// Set TRUE if the active symbol should be applied as current selection.
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropSupport2DAttributeTool = 60;//		YES			// Object supports Attribute Mapping Tool use in Top/Plan. Currently only used for parametric objects.
//		// Boolean									 //						//
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontResetViewOnGroupEnter = 61;//	NO			// It will not reset view orientation when group (profile or path) enter and exist
//		// Boolean									 //						//
//													 //						//
//--------------------------------------------------//--------------------//---------------------------------------------------------------------------------------------------
const ObjectPropID kObjXProp2DAttributeToolNames = 62;//		NO			// Stores names for the different 2D components used by the attribute mapping tool
//		// String									 //						//
//													 //						//
//--------------------------------------------------//--------------------//---------------------------------------------------------------------------------------------------
const ObjectPropID kObjXCatalogSupport	 = 63;		//		NO				// Controls whether a parametric type supports catalogs
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontShowTextureWidgets = 64;  //	NO			// When set to true will remove the texture widgets in the Render pane of OIP for the parametric object
//		// Boolean									 //						//  
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontResetProfileGroupFill = 65;//   NO		    // When set to true will forbid resetting fill space of Profile group.
//		// Boolean									 //						//  
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropResetAssObjOnRecordChange = 66;//   NO		    // When set to true will reset associated object when record data is changeed
//		// Boolean									 //						//  
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropResetObjOnPathGrpSymChange	= 67;//  NO			// When set to true the object will reset when containing geometry has been changed from RM
//
//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropUnused2 = 68;			 //						// Formally kObjXPropSwapGraphicsSupport but now is no longer used. Feel free to reuse this value. 
//		// Boolean									 //						//  
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHideStyleSettingsButton = 69;//	NO				// When set to TRUE the default Plug-in Style Settings button used for default editing
//													 //						// will not be shown
//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropResetOnViewportSymbolScale = 70;// NO			//  When set to true will reset the object when the viewport page symbol scale changes.
//		// Boolean									 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHidePlanarDropDown = 71;  //			NO		// When set to true will hide planar dropdown for the widget in the OIP for the parametric
//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropShowDetailWidgetsInProfileGroup = 72;//   NO	// When set to true will show detail level widgets in profile group
//		// Boolean									 //						//  
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropCustomTexturePartIDs = 73;//			YES			// Stores extra custom parametric texture part IDs for the mapping tool
//		// String									 //						//  
//													 //						//
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHybridSupports3DTransforms = 74;//		NO	    // Hybrid object can be manipulated using 3D rotate and mirror tools. Parametric must properly handle 
//		// Boolean									 //						// these transformations using kObjXHandlesCommand, ObjectCommand::kOnMatrixTransform
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropCopySelectionAsProfile = 75;//		NO			//  When set to true, Path objects will get a copy of the selecition as Profile Group when created.
//		// Boolean									 //						//	The propery works only when creating objects using Default Path Insertion tools.
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDefaultTopPlanViewComponent = 76;				// Controls the default Top/Plan view component for newly created unstyled PIOs
//		// Sint8									 //						
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDefaultHorizontalSectionCutPlane = 77;			// controls the default horizontal section cut plane for newly created unstyled PIOs
//		// Sint8									 //						
//---------------------------------------------------//---------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDefaultVerticalSectionCutPlane = 78;			// controls the default vertical section cut plane for newly created unstyled PIOs
//		// Sint8									 //						
//---------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDisablesAttributes = 79;//			YES			// When set to true, Attributes palette will send this object a message of type
//		// Boolean									//						// ParametricCanEditAttrMessage whenever it is selected.
//												    //						//
//													//						// VectorScript objects can respond via SDK call vsoDisableAttrs(long bf). If bf == -1, all
//													//						// controls will be disabled. If first bit true fill controls will be disabled, if second true pen
//													//						// controls will be disabled.
//													//						//
//													//						// SDK objects can respond by overriding virtual method OnAttributeQuery and manipulating argument.
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropUnused3 = 80;			//			NO			// SAFE TO USE - USE THIS FOR YOUR XPROP
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropWidgetGroupMode = 81;	//			NO			//  kObjXPropWidgetGroupDisabled = 1;
//		// Sint8									//						//	kObjXPropWidgetGroupAutomatic = 2;
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontShowCoordinates = 82;//			NO			// When set to true will remove the X, Y, Z coordinates for the location widget in the OIP for the parametric
//		// Boolean									//						//  
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontShowZRotation = 83; //			NO			// When set to true will remove the Z rotation for the location widget in the OIP for the parametric
//		// Boolean									//						//  
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontAllowDelayedEnterGroup = 84;//  NO			// When set to true will forbid the functionality for delayed entering group.
//		// Boolean									//						//
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropPageBaseProfileGroup = 85; //		NO			// Object with page-base profile group. 
//		// Boolean									//						// The geometry and the text in some object are always drawn in Page Units in their edit layout context.
//													//						// Without setting the paperScale value to 1.0 the text is being displayed in world scale points.
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropSupportBuildingMaterialInOIP = 86;// NO			// Controls whether parametric objects directly support setting of a BuildingMaterial in the OIP 
//		// Boolean									//						//   Set TRUE if the object supports this
//													//						//   
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDontFlipText = 87;		//			NO			// Dont flip text 
													//						// 
													//						//					
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHideVertexWidgets = 88; //			NO			// When set to true will remove the Polyline vertex widgets in the OIP for the parametric
//		// Boolean									//						//  
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropHideVertexTypeFlags = 89; //		NO			// The set of flags identifying the VertexTypes to remove from the Polyline vertex type widget in the OIP for the parametric
//		// Sint8									//						//  e.g. (1 << vtBezier)
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropDoesNotSupport3DTransforms = 90;//	NO			// When set to true, will protect non-hybrid objects from 3D manipulation by rotate and mirror tools.
//		// Boolean									//						//
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropGetPathProxyFor_DupAlongPath = 91;//	NO		// When set to true, gSDK->CustomObjectGetPathProxy(h, purpose) will return a path for callers that
//		// Boolean									//						// specify this XProp as the purpose.
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------
const ObjectPropID kObjXPropGetPathProxyFor_Offset = 92;//	NO				// When set to true, gSDK->CustomObjectGetPathProxy(h, purpose) will return a path for callers that
//		// Boolean									//						// specify this XProp as the purpose.
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------


const ObjectPropID kLastObjXProp = kObjXPropGetPathProxyFor_Offset;// last property ID
//
//                         Property ID				//	Has Associated		//  Description:
//													//		Event(s)		//
//--------------------------------------------------//----------------------//-------------------------------------------------------------------------------------------------


//
//
//////////////////////////////////////////////////////////////////////
//Property Values:
//

// kObjectEditGroupPropertyID property values:
const unsigned char kObjXPropEditGroupDefault = 0;
const unsigned char kObjXPropEditGroupProfile = 1;
const unsigned char kObjXPropEditGroupPath = 2;
const unsigned char kObjXPropEditGroupCustom = 3;
const unsigned char kObjXPropEditGroupManualEdges = 4;
const unsigned char kObjXPropEditGroupDrainage = 5;
const unsigned char kObjXPropEditGroupReshape = 6;


// kObjectSpecialEditPropertyID property values:
typedef unsigned char TObjSpecialEdit;
const TObjSpecialEdit kObjXPropSpecialEditDefault = 0;
const TObjSpecialEdit kObjXPropSpecialEditCustom = 1;
const TObjSpecialEdit kObjXPropSpecialEditProperties = 2;
const TObjSpecialEdit kObjXPropSpecialEditReshape = 3;
const TObjSpecialEdit kObjXPropSpecialEditEditGroup = 4;
const TObjSpecialEdit kObjXPropSpecialEditSpecial = 5;	// like kObjXPropSpecialEditDefault but allows ParametricSpecialEditMessage event from IProviderSpecialGroups::ChoosePluginComponentToEdit

// messages of ParametricSpecialEditMessage::kAction when property kObjectSpecialEditPropertyID is set to kObjXPropSpecialEditCustom
typedef Sint32 TObjectEdiReason;
const TObjectEdiReason kObjectEdit_ExplicitEdit = 0;
const TObjectEdiReason kObjectEdit_DoubleClick = 1;
const TObjectEdiReason kObjectEdit_CtrlClick = 2;

typedef Sint32 TObjectEditResult;
const TObjectEditResult	kObjectEditResult_DoNothing = 0;
const TObjectEditResult kObjectEditResult_Default = 1;
const TObjectEditResult kObjectEditResult_Properties = 2;
const TObjectEditResult kObjectEditResult_Reshape = 3;
const TObjectEditResult kObjectEditResult_EditPath = 4;
const TObjectEditResult kObjectEditResult_EditProfile = 5;

//	kObjXPropDefaultPropertyUI property values:
// NNA under development   
const unsigned char kHideSymbolWidget = 1;
const unsigned char kHidePolyWidget = 2;
const unsigned char kHidePolyAndSymbolRotationWidget = 4;
const unsigned char kUseAppropriateLocationWidget = 8; // use linear location widget for linear parametrics etc
const unsigned char kUsePolyDirectionWidget = 16;
//kHideStoryLevelWidget allows control of the story level widgets for story-aware symbols and PIOs in the OIP.
//For story-aware PIOs that use the default preference dialog, kHideStoryLevelWidget also determines whether
//the level widgets are shown in the preference dialog.
const unsigned char kHideStoryLevelWidget = 32;  


//  kObjXPropCustomHideFactor property values:
		// Uses document low level of detail threshold value (varHideCavityFactor) to determine visibility
const double        kCustomHideFactor_DocumentThreshold = (double) -1.0;
		// Uses document low level of detail threshold value (varHideCavityFactor) to determine visibility
		// VW 2019 viewports do not respect this setting - they have their own level of detail
const double        kCustomHideFactor_ViewportDocumentThreshold = (double) -2.0;

//	kObjXPropUpdateAfterDocUnitsChange property values:
const TObjSpecialEdit kObjXPropResetWhenChangedLinearDim	= 1;
const TObjSpecialEdit kObjXPropResetWhenChangedAreaDim		= 2;
const TObjSpecialEdit kObjXPropResetWhenChangedVolumeDim	= 4;
const TObjSpecialEdit kObjXPropResetWhenChangedEnergosDim	= 8;
const TObjSpecialEdit kObjXPropResetWhenChangedMassForceDim	= 16;
const TObjSpecialEdit kObjXPropResetWhenChangedAngularDim	= 32;

//kObjXPropUseLayerCutPlane  values
const unsigned char kObjXPropDoesNotUseLayerCutPlane      = 0;
const unsigned char kObjXPropAlwaysUsesLayerCutPlane      = 1;
const unsigned char kObjXPropObjectCanUseLayerCutPlane    = 2;

//kObjXPropHybridSupports3DTransforms property values:
const Sint8	kObjXPropHybridDoesNotSupport3DTransforms	= 0;
const Sint8	kObjXPropHybridSupport3DRotate2DByX			= 1;
const Sint8	kObjXPropHybridSupport3DRotate2DByY			= 2;
const Sint8	kObjXPropHybridSupport3DRotate2DByZ			= 3;
const Sint8	kObjXPropHybridSupport3DCustomTransform2D	= 4;

// kObjXPropDefaultTopPlanViewComponent property values:
const Sint8 kObjXPropTopComponent				= 0;
const Sint8 kObjXPropTopAndBottomCutComponent	= 1;      

// kObjXPropDefaultHorizontalSectionCutPlane & kObjXPropDefaultVerticalSectionCutPlane values
const Sint8 kObjXPropViewAsCutWhenCutInViewport			= 1;
const Sint8 kObjXPropViewAsUncutBeyondWhenCutInViewport	= 3;       // below (for horizontal sections), beyond (for vertical sections)
const Sint8 kObjXPropViewAsUncutBeforeWhenCutInViewport	= 4;       // above (for horizontal sections), before (for vertical sections)

// kObjXPropWidgetGroupMode
const Sint8 kObjXPropWidgetGroupDisabled		= 1;
const Sint8 kObjXPropWidgetGroupAutomatic		= 2;

/////////////////////////////
// kObjXPropHasUIOverride Widget constants:
enum EWidgetType {
	kWidgetLongInt			= 1,
	kWidgetBoolean			= 2,
	kWidgetReal				= 3,
	kWidgetText				= 4,
	kWidget_UNUSED_5		= 5,
	kWidget_UNUSED_6		= 6,
	kWidgetCoordDisp		= 7,
	kWidgetPopUp			= 8,
	kWidgetRadio			= 9,
	kWidgetCoordLocX		= 10,
	kWidgetCoordLocY		= 11,
	kWidgetButton			= 12,
	kWidgetStaticText		= 13,
	kWidgetStaticTextParam	= 14,
	kWidgetDimStdPopUp		= 16,
	kWidgetPrecisionPopUp	= 17,
	kWidgetClassesPopup		= 18,
	kWidgetLayersPopup		= 19,
	kWidgetAngleDisp		= 20,
	kWidgetAreaDisp			= 21,
	kWidgetVolumeDisp		= 22,
	kWidgetSeparator		= 100,
	kWidgetSubSelection		= 101,
	kWidgetBoundPopup		= 102,
	kWidgetBoundOffset		= 103,
    kWidgetSliderWithEdit	= 104,
	kWidgetButtonResourcePopup= 105,
	kWidgetBoxPosition		= 106, 
	kWidgetResourceThumbnailPopup = 107, 
	kWidgetSearchablePopup  = 108,
};
/////////////////////////////

// kObjXPropAcceptsMarkers constants:
const unsigned char kObjXPropAcceptsMarkersNone = 0;
const unsigned char kObjXPropAcceptsMarkersBeginningOnly = 1;
const unsigned char kObjXPropAcceptsMarkersEndOnly = 2;
const unsigned char kObjXPropAcceptsMarkersBoth = 3;


// Plug-in Object return constants
const Sint32 kParametricNoErr					= 0;		// 
const Sint32 kParametricSetupFailed			= -1;
const Sint32 kParametricError					= -2;
const Sint32 kParametricNotImplemented		= -3;		// The Plug-in did not present its own preference dialog, it is up to the VW application to do it.
const Sint32 kParametricPrefOK				= -4;		// The Plug-in presented its own preferences dialog, and the user hit OK.
const Sint32 kParametricPrefCancel			= -5;		// The Plug-in presented its own preferences dialog, and the user hit Cancel.
const Sint32 kParametricHadError				= -6;		// The Plug-in compiled but had an error during execution.
const Sint32 kParametricHadWarning			= -7;		// The Plug-in compiled but had a warning during execution.

const Sint32 kParametricAttrMove2DEventHandled = 1;		// observed by:
														//	ParametricAtributeMove2DMessage::kAction

const Sint32 kObjectEventHandled			  	 = -8;		//
const Sint32 kObjectEventFinalized            = -9;       // The event was handled by the plug-in, and the parametric code should not make further changes to the object parameters 
const Sint32 kObjectEventNotHandled		    = 0;		// 

const Sint32 kObjectOnSpecialOK			   	= 0;		// observed by ParametricUIButtonHitMessage::kAction caller - Undo event is ended
const Sint32 kObjectOnSpecialCancel		    = -5;		// observed by ParametricUIButtonHitMessage::kAction caller - Undo event is removed

const Sint32 kObjectUIButtonHitOK			   	= 0;		// observed by ParametricUIButtonHitMessage::kAction caller - Undo event is ended
const Sint32 kObjectUIButtonHitCancel		    = -5;		// observed by ParametricUIButtonHitMessage::kAction caller - Undo event is removed
const Sint32 kObjectUIButtonHitPreventReset		= -11;		// observed by ParametricUIButtonHitMessage::kAction caller - reset of the parametric will not be performed

const Sint32 kObjectEditPluginStyleByDefault	= -10;	// This is event response constant
														// When plugin style edit message replies with this constant, it does default OIP dialog to edit the style parametric
														// See struct ParametricEditPluginStyle.


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//	BEGIN Custom Editable DataBar types and constants:
//  

////////////////////////////////////////
//
//	CustomBarEventData::kAction come with message1 data of type CustomBarEventData.
//	CustomBarEventData::fCustomBarEventSelectors:
//  
const Sint32 kCustomBarSetup = 1;			// sent when a CustomBar is installed with GS_CustomBarInstall
const Sint32 kCustomBarSetdown = 2;		// sent when a CustomBar is replaced with another databar
const Sint32 kCustomBarUpdateValues = 3;	// sent with each new cursor/mouse position so CustomBar client and provide new field values.
const Sint32 kCustomBarLockValue = 4;		// sent when a user lockes a field of a custom bar	
const Sint32 kCustomBarUnlockValue = 5;	// sent when a user unlockes a field of a custom bar	

const short kModeBarOptionsIconID = 5010;

//	END Custom Editable DataBar types and constants:
//  
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


///
/////
///////
/////////       -------------------------------------------------------
///////////		END OBJECT DEFINITION PROCEDURE PARAMETERS DESCRIPTIONS -------------------------------------------------
/////////////	------------------------------------------------------




/////////////	-----------------------------------------------------------------
///////////		BEGIN PLUGIN LIBRARY DEFINITION PROCEDURE PARAMETERS DESCRIPTIONS -------------------------------------------------
/////////		-----------------------------------------------------------------
///////
/////
///
//
//	Action constants
//	Actions >= 0 are reserved for the Plug-in routine implementation calls.
//
const Sint32 kPluginModuleInit = -1;
const Sint32 kPluginModuleDeinit = -2;
const Sint32 kVCOMRegisterInterfaces = -3;
const Sint32 kVCOMQueryInterface = -4;
const Sint32 kVCOMReleaseInterface = -5;
const Sint32 kVCOMQueryInterfaceRTTI = -6;

//	Return Flags for kPluginModuleInit action returns
//
enum PluginLibraryInitFlags { 			
	kDoNotCache = 32,	// does not cache the plug-in VCOM modules. it will initialize the plug-in on each launch
};

//
///
/////
///////
/////////       ---------------------------------------------------------------
///////////		END PLUGIN LIBRARY DEFINITION PROCEDURE PARAMETERS DESCRIPTIONS -------------------------------------------------
/////////////	---------------------------------------------------------------






/////////////	-----------------------------------------------------------------
///////////		BEGIN PLUGIN LIBRARY VCOM SUPPORT -------------------------------------------------
/////////		-----------------------------------------------------------------
///////
/////
///
//

// ---------------------------------------------------------------------------------------------------
#ifdef _WINDOWS
# define VCOM_CALLTYPE			__stdcall
#else
# define VCOM_CALLTYPE
#endif

// ---------------------------------------------------------------------------------------------------
struct VWIID
{
    Uint32  data1;
    unsigned short data2;
    unsigned short data3;
    unsigned char  data4[8];

	VWIID& operator = (const VWIID& iid) {
		memcpy( this, &iid, sizeof(VWIID) );
		return *this;
	}

	bool operator == (const VWIID& iid) const {
		return memcmp( this, &iid, sizeof(VWIID) ) == 0;
	}

	bool operator != ( const VWIID& iid ) const
	{
		return !( this->operator==( iid ) );
	}

	bool operator < (const VWIID& iid) const {
		bool	isLess	= true;
		bool	isEqual	= true;

		// data1
		if ( isEqual ) {
			isEqual		= isEqual && data1 == iid.data1;
			if ( ! isEqual ) { isLess	= (data1 < iid.data1); }

			// data2
			if ( isEqual ) {
				isEqual		= isEqual && data2 == iid.data2;
				if ( ! isEqual ) { isLess	= (data2 < iid.data2); }

				// data3
				if ( isEqual ) {
					isEqual		= isEqual && data3 == iid.data3;
					if ( ! isEqual ) { isLess	= (data3 < iid.data3); }

					// data4
					for(Sint32 i=0; i<8 && isEqual; i++) {
						isEqual		= isEqual && data4[i] == iid.data4[i];
						if ( ! isEqual ) { isLess	= (data4[i] < iid.data4[i]); }
					}
				}
			}
		}

		return isLess && ! isEqual;
	}
	void SetToNULL(void) { memset(this, 0, sizeof(VWIID)); }
	bool IsNULL(void) const { VWIID compare; compare.SetToNULL(); return(*this == compare);}
};

// ---------------------------------------------------------------------------------------------------
typedef	VWIID	VWGroupID;

// ---------------------------------------------------------------------------------------------------
// We define Dynamic Attribute modificator so VCOM and other C++ interfaces
//		could participate in dynamic_cast operator on Mac.
// This is a bug (or issue) in Mac compiler that causes dynamic_cast operator to fail
//		if the interface instance is from local memory of a DLL!
#ifdef _WINDOWS
# define DYNAMIC_ATTRIBUTE
#else
# define DYNAMIC_ATTRIBUTE __attribute__((visibility("default")))
#endif

// ---------------------------------------------------------------------------------------------------
// Base interface for all interfaces in VCOM
class DYNAMIC_ATTRIBUTE IVWUnknown
{
public:
	virtual							~IVWUnknown( void )		{}
	virtual Sint32 VCOM_CALLTYPE		AddRef() = 0;
	virtual Sint32 VCOM_CALLTYPE		Release() = 0;
	
};

// ---------------------------------------------------------------------------------------------------
// Base interface for single instance interfaces in VCOM
class DYNAMIC_ATTRIBUTE IVWSingletonUnknown : public IVWUnknown
{
public:
};

// ---------------------------------------------------------------------------------------------------
// VCOM errors
typedef	Sint32		VCOMError;

const VCOMError		kVCOMError_NoError			= 0;
const VCOMError		kVCOMError_Failed			= 1;
const VCOMError		kVCOMError_False			= 2;
const VCOMError		kVCOMError_OutOfMemory		= 3;
const VCOMError		kVCOMError_NotInitialized	= 4;
const VCOMError		kVCOMError_NoInterface		= 5;
const VCOMError		kVCOMError_NotImplemented	= 6;
const VCOMError		kVCOMError_DuplicateIID		= 10;
const VCOMError		kVCOMError_NoModule			= 11;
const VCOMError		kVCOMError_NoInstance		= 12;
const VCOMError		kVCOMError_Unexpected		= 13;
const VCOMError		kVCOMError_InvalidArg		= 15;
const VCOMError		kVCOMError_Canceled			= 16;
const VCOMError		kVCOMError_NotLicensed		= 17;


#define		VCOM_SUCCEEDED(x)		(x == kVCOMError_NoError)
#define		VCOM_FAILED(x)			(x != kVCOMError_NoError)

// ---------------------------------------------------------------------------------------------------
class VWVariant;

// ---------------------------------------------------------------------------------------------------
class DYNAMIC_ATTRIBUTE IVWUnknownRTTI : public IVWUnknown
{
public:
	virtual size_t		GetFunctionsCount() = 0;
	virtual bool		GetFunction(size_t functionIndex, size_t& outParamsCnt, char* outNameBuffer, size_t& inOutBufferSize) = 0;
	virtual bool		GetFunctionParameter(size_t functionIndex, size_t paramIndex, VWVariant& outDefValue) = 0;
	virtual size_t		FindFunctionIndex(const char* szFunctionName, size_t paramsCnt) = 0;

	virtual VCOMError	PrepareForCall() = 0;
	virtual VCOMError	AddParameter(const VWVariant& value) = 0;
	virtual VCOMError	ExecuteCall(IVWUnknown* instance, size_t functionIndex, VWVariant& outResult) = 0;
};

//---------------------------------------------------------------------------------------
typedef std::function<IVWUnknown*()>		TRegisterAllocateCallback;
typedef std::function<void(IVWUnknown*)>	TRegisterFreeCallback;
typedef std::function<void()>				TRegisterSetdownCallback;

// ---------------------------------------------------------------------------------------------------
// working with interfaces
VCOMError	GS_InitializeVCOM(void* cbpParam);
VCOMError	GS_VWRegisterInterface(const VWIID& iid, void* argTable, bool cacheIt=true);
VCOMError	GS_VWRegisterInterface(const VWIID& iid, const VWIID& iidContainer, void* argTable, bool cacheIt=true);
VCOMError	GS_VWQueryInterface(const VWIID& iid, IVWUnknown** ppInterface);
void		GS_VWNotifyDeleteInterface(IVWUnknown* pInterface);
size_t		GS_VWGetContainerInterfacesCount(const VWIID& iidContainer);
VWIID		GS_VWGetContainerInterface(const VWIID& iidContainer, size_t index);
bool		GS_VWQueryInterfaceRTTI(const VWIID& iid, IVWUnknownRTTI** ppInterfaceRTTI);
void		GS_VWReleaseInterfaces(bool takeYourTime);
size_t		GS_VWGetInterfaceModulePath(const VWIID& iid, char* buffer, size_t bufferSize);
VCOMError	GS_VWRegisterInterface(const VWIID& iid, TRegisterAllocateCallback allocateCallback, TRegisterFreeCallback freeCallback);
VCOMError	GS_VWRegisterInterface(const VWIID& iid, const VWIID& iidContainer, TRegisterAllocateCallback allocateCallback, TRegisterFreeCallback freeCallback);
void		GS_ReleaseStandardVCOMGlobals(Sint32 action);

// ---------------------------------------------------------------------------------------------------
// tools
template<class T> class VCOMPtr
{
public:
				VCOMPtr()						{ fPtr = NULL; }
				VCOMPtr(T* ptr)					{ fPtr = ptr;						if ( fPtr ) { fPtr->AddRef(); } }
				VCOMPtr(const VWIID& iid)		{ fPtr = NULL;						this->Query( iid ); }
				VCOMPtr(const VCOMPtr& p)		{ fPtr = p.fPtr;					if ( fPtr ) { fPtr->AddRef(); } }
				~VCOMPtr()						{ this->Release(); }

	VCOMError	Query(const VWIID& iid)			{ 
													this->Release();
													IVWUnknown*	pInterface		= NULL;
													VCOMError err = ::GS_VWQueryInterface( iid, & pInterface );
													if ( VCOM_SUCCEEDED( err ) ) {
														// Vlado: Temporally removed 'dynamic_cast'
														// because on new Mac OS it is failing to cast properly
														//fPtr = dynamic_cast<T*>( pInterface );
														fPtr = (T*)( pInterface );
														if ( fPtr == NULL ) {
															if ( pInterface ) {
																pInterface->Release();
																pInterface	= NULL;
															}
															// the passed 'iid' is not from the extected type 'T'
															err			= kVCOMError_InvalidArg;
														}
													}
													return err;
												}
	void		AddRef()						{ if ( fPtr ) { fPtr->AddRef(); } }
	Sint32		Release()						{ Sint32 res = 0; if ( fPtr ) { res = fPtr->Release(); } fPtr = NULL; return res; }

	VCOMPtr&	operator=(T* ptr)				{ T* pOld = fPtr; fPtr = ptr;						if ( fPtr ) { fPtr->AddRef(); } if ( pOld ) { pOld->Release(); } return *this; }
	VCOMPtr&	operator=(const VCOMPtr& p)		{ T* pOld = fPtr; fPtr = p.fPtr;					if ( fPtr ) { fPtr->AddRef(); } if ( pOld ) { pOld->Release(); } return *this; }

	T*			operator->() const				{ return fPtr; }
	T**			operator&()						{ return & fPtr; }
				operator T*() const 			{ return fPtr; }

protected:
	T*			Get() const	{ return fPtr; }
	void		Set(T* p)	{ fPtr = p; }

private:
	T*		fPtr;
};

typedef VCOMPtr<IVWUnknown>		IVWUnknownPtr;

// thread safety model for the template parameter of VCOMImpl and VCOMImplImmediate
typedef Sint32						RefNumPrec;
typedef std::atomic<RefNumPrec>		RefNumType;

// VCOM interface implementation with late destruction
template<class Interface> class VCOMImpl : public Interface
{
public:
				VCOMImpl()						{ fRefCnt = 0; fParent = NULL; }
				VCOMImpl(IVWUnknown* parent)	{ fRefCnt = 0; fParent = parent; if ( fParent ) { fParent->AddRef(); } }
				VCOMImpl(const VCOMImpl&)				= delete;	// DO NOT COPY
				VCOMImpl& operator=(const VCOMImpl&)	= delete;	// DO NOT COPY
					virtual		~VCOMImpl()		{ }

// IVWUnknown
public:
	virtual RefNumPrec VCOM_CALLTYPE	AddRef()	{ fRefCnt++; return fRefCnt; }
	virtual RefNumPrec VCOM_CALLTYPE	Release()
										{
											RefNumPrec localRefCnt = --fRefCnt;

											if (localRefCnt < 0) {
												fRefCnt = 0;
												DSTOP((kEveryone, "fRefCnt < 0"));
												return 0;
											}
											else if (localRefCnt == 0 ) {
												this->OnRefCountZero();
												// exit immediatelly. 'this' may no longer be valid
												return 0;
											}
											return localRefCnt;
										}

protected:
	// notification when this instance ref count goes down to zero
	virtual void						OnRefCountZero() { if ( fParent ) { fParent->Release(); } fParent = NULL; }

protected:
	RefNumType	fRefCnt;
	IVWUnknown* fParent;
};

// VCOM interface implementation with immediate destruction
template<class Interface> class VCOMImmediateImpl : public Interface
{
public:
				VCOMImmediateImpl()							{ fRefCnt = 0; fParent = NULL; }
				VCOMImmediateImpl(IVWUnknown* parent)		{ fRefCnt = 0; fParent = parent; if ( fParent ) { fParent->AddRef(); } }
				VCOMImmediateImpl(const VCOMImmediateImpl&)				 = delete;	// DO NOT COPY
				VCOMImmediateImpl& operator=(const VCOMImmediateImpl&)	 = delete;	// DO NOT COPY
					virtual		~VCOMImmediateImpl()		{ }

// IVWUnknown
public:
	virtual RefNumPrec VCOM_CALLTYPE	AddRef()	{ fRefCnt++; return fRefCnt; }
	virtual RefNumPrec VCOM_CALLTYPE	Release()
										{
											RefNumPrec localRefCnt = --fRefCnt;

											if (localRefCnt < 0) {
												fRefCnt = 0;
												DSTOP((kEveryone, "fRefCnt < 0"));
												return 0;
											}
											else if (localRefCnt == 0) {
												// mechanizm for immediate delete of the interface instance
												this->OnRefCountZero();
												::GS_VWNotifyDeleteInterface( this );
												// EXIT IMMEDIATELY! 'this' no longer exist!!!
												return 0;
											}
											return localRefCnt;
										}

protected:
	// notification when this instance ref count goes down to zero
	virtual void						OnRefCountZero() { if ( fParent ) { fParent->Release(); } fParent = NULL; }

protected:
	RefNumType	fRefCnt;
	IVWUnknown* fParent;
};


//
///
/////
///////
/////////       ---------------------------------------------------------------
///////////		END PLUGIN LIBRARY LIBRARY VCOM SUPPORT -------------------------------------------------
/////////////	---------------------------------------------------------------

/////////////	---------------------------------------------------------------
// Parametric plug type accessed via ovParametricInternalID


typedef short		TInternalID;


// This is the list of plugin Internal ID constants which are mapped to the matching names below
// If you are adding a plugin object, add it to the bottom of the list and make sure the number increments by 1.
const TInternalID kInternalID_AcornNutInch				=	1;
const TInternalID kInternalID_AcornNutInch3D			=	2;
const TInternalID kInternalID_AdjacencyMatrix			=	3;
const TInternalID kInternalID_AdjacencyScore			=	4;
const TInternalID kInternalID_Angle						=	5;
const TInternalID kInternalID_AngleInch					=	6;
const TInternalID kInternalID_AngleMetric				=	7;
const TInternalID kInternalID_Angle3D					=	8;
const TInternalID kInternalID_AreaPlant					=	9;
const TInternalID kInternalID_BallBearing				=	10;
const TInternalID kInternalID_BallBearing3D				=	11;
const TInternalID kInternalID_BaseCabinet				=	12;
const TInternalID kInternalID_BathShower				=	13;
const TInternalID kInternalID_BattInsulation			=	14;
const TInternalID kInternalID_BearingLockNut			=	15;
const TInternalID kInternalID_BearingLockNut3D			=	16;
const TInternalID kInternalID_BellevilleSpring			=	17;
const TInternalID kInternalID_BellevilleSpring3D		=	18;
const TInternalID kInternalID_BevelGears				=	19;
const TInternalID kInternalID_BevelGears3D				=	20;
const TInternalID kInternalID_BlendedProjector			=	21;
const TInternalID kInternalID_BlendedScreen				=	22;
const TInternalID kInternalID_Board						=	23;
const TInternalID kInternalID_BoltandNutInch			=	24;
const TInternalID kInternalID_BoltandNutmm				=	25;
const TInternalID kInternalID_BoxObject					=	26;
const TInternalID kInternalID_BreakLine					=	27;
const TInternalID kInternalID_Bridgeline				=	28;
const TInternalID kInternalID_BulbFlat					=	29;
const TInternalID kInternalID_BulbFlat3D				=	30;
const TInternalID kInternalID_Callout					=	31;
const TInternalID kInternalID_Cam						=	32;
const TInternalID kInternalID_Campanile					=	33;
const TInternalID kInternalID_CapScrewDIN				=	34;
const TInternalID kInternalID_CapScrewDIN3D				=	35;
const TInternalID kInternalID_CapScrewInch				=	36;
const TInternalID kInternalID_CapScrewInch3D			=	37;
const TInternalID kInternalID_CapScrewISO				=	38;
const TInternalID kInternalID_CapScrewISO3D				=	39;
const TInternalID kInternalID_CapScrewMetric			=	40;
const TInternalID kInternalID_CapScrewMetric3D			=	41;
const TInternalID kInternalID_CarriageBolt				=	42;
const TInternalID kInternalID_CarriageBolt3D			=	43;
const TInternalID kInternalID_CeilingGrid				=	44;
const TInternalID kInternalID_CenterDrill				=	45;
const TInternalID kInternalID_CenterDrill3D				=	46;
const TInternalID kInternalID_CenterLineMarker			=	47;
const TInternalID kInternalID_ChainExtrude				=	48;
const TInternalID kInternalID_Channel					=	49;
const TInternalID kInternalID_ChannelInch				=	50;
const TInternalID kInternalID_ChannelMetric				=	51;
const TInternalID kInternalID_Channel3D					=	52;
const TInternalID kInternalID_CircularStair				=	53;
const TInternalID kInternalID_ClevisPinDIN				=	54;
const TInternalID kInternalID_ClevisPinDIN3D			=	55;
const TInternalID kInternalID_ClevisPinInch				=	56;
const TInternalID kInternalID_ClevisPinInch3D			=	57;
const TInternalID kInternalID_ClevisPinMetric			=	58;
const TInternalID kInternalID_ClevisPinMetric3D			=	59;
const TInternalID kInternalID_ClothesRod				=	60;
const TInternalID kInternalID_Column2					=	61;
const TInternalID kInternalID_CommDevice				=	62;
const TInternalID kInternalID_CompartmentSink			=	63;
const TInternalID kInternalID_CompressionSpring1		=	64;
const TInternalID kInternalID_CompressionSpring13D		=	65;
const TInternalID kInternalID_CompressionSpring2		=	66;
const TInternalID kInternalID_CompressionSpring23D		=	67;
const TInternalID kInternalID_ConeObject				=	68;
const TInternalID kInternalID_ConicalCompSpring3D		=	69;
const TInternalID kInternalID_ConicalCompressionSpring	=	70;
const TInternalID kInternalID_Coordinate				=	71;
const TInternalID kInternalID_CotterPinInch				=	72;
const TInternalID kInternalID_CotterPinInch3D			=	73;
const TInternalID kInternalID_CounterTop				=	74;
const TInternalID kInternalID_CurtainObject				=	75;
const TInternalID kInternalID_CurvedTruss				=	76;
const TInternalID kInternalID_CustomStair				=	77;
const TInternalID kInternalID_CuttingPlane				=	78;
const TInternalID kInternalID_CuttingPlane1				=	79;
const TInternalID kInternalID_CuttingPlane2				=	80;
const TInternalID kInternalID_CylinderObject			=	81;
const TInternalID kInternalID_DataStamp					=	82;
const TInternalID kInternalID_DatumFeatureSymbol		=	83;
const TInternalID kInternalID_DatumTargetSymbol			=	84;
const TInternalID kInternalID_Desk						=	85;
const TInternalID kInternalID_DetailBubble				=	86;
const TInternalID kInternalID_DetailCutWood				=	87;
const TInternalID kInternalID_DialogBuilderLink			=	88;
const TInternalID kInternalID_DialogBuilderControl		=	89;
const TInternalID kInternalID_DieSpring					=	90;
const TInternalID kInternalID_DieSpring3D				=	91;
const TInternalID kInternalID_Door						=	92;
const TInternalID kInternalID_DowelPinInch				=	93;
const TInternalID kInternalID_DowelPinInch3D			=	94;
const TInternalID kInternalID_DrawingBorderUniversal	=	95;
const TInternalID kInternalID_DrawingLabel				=	96;
const TInternalID kInternalID_DrilledFooting			=	97;
const TInternalID kInternalID_DripEmitter				=	98;
const TInternalID kInternalID_DTM6						=	99;
const TInternalID kInternalID_DTM6Snapshot				=	100;
const TInternalID kInternalID_DwgLabelSimple			=	101;
const TInternalID kInternalID_ElevationBenchmark		=	102;
const TInternalID kInternalID_EllipsoidObject			=	103;
const TInternalID kInternalID_Escalator					=	104;
const TInternalID kInternalID_ExtensionSpring3D			=	105;
const TInternalID kInternalID_ExtensionSpringEnd		=	106;
const TInternalID kInternalID_ExtensionSpringFront		=	107;
const TInternalID kInternalID_ExtrudeAlongPath			=	108;
const TInternalID kInternalID_EyeBolt					=	109;
const TInternalID kInternalID_EyeBolt3D					=	110;
const TInternalID kInternalID_FeatureControlFrame		=	111;
const TInternalID kInternalID_Fireplace					=	112;
const TInternalID kInternalID_FlangedBearing2Hole		=	113;
const TInternalID kInternalID_FlangedBearing2Hole3D		=	114;
const TInternalID kInternalID_FlangedBearing4Hole		=	115;
const TInternalID kInternalID_FlangedBearing4Hole3D		=	116;
const TInternalID kInternalID_FlowchartLink				=	117;
const TInternalID kInternalID_FlowchartNode				=	118;
const TInternalID kInternalID_FocusPointObject			=	119;
const TInternalID kInternalID_FramingMember				=	120;
const TInternalID kInternalID_GeneralNotes				=	121;
const TInternalID kInternalID_GenevaMechanism			=	122;
const TInternalID kInternalID_GeomDimandTolNote			=	123;
const TInternalID kInternalID_GrabBars					=	124;
const TInternalID kInternalID_GridPolar					=	125;
const TInternalID kInternalID_GridRectangular			=	126;
const TInternalID kInternalID_GridBubble				=	127;
const TInternalID kInternalID_GuardrailCurved			=	128;
const TInternalID kInternalID_GuardrailStraight			=	129;
const TInternalID kInternalID_HandrailCurved			=	130;
const TInternalID kInternalID_HandrailStraight			=	131;
const TInternalID kInternalID_Hardscape					=	132;
const TInternalID kInternalID_HardscapeVS				=	133;
const TInternalID kInternalID_HelixSpiral				=	134;
const TInternalID kInternalID_HexBoltDIN				=	135;
const TInternalID kInternalID_HexBoltDIN3D				=	136;
const TInternalID kInternalID_HexBoltInch				=	137;
const TInternalID kInternalID_HexBoltInch3D				=	138;
const TInternalID kInternalID_HexBoltISO				=	139;
const TInternalID kInternalID_HexBoltISO3D				=	140;
const TInternalID kInternalID_HexBoltMetric				=	141;
const TInternalID kInternalID_HexBoltMetric3D			=	142;
const TInternalID kInternalID_HexBoltFineDIN			=	143;
const TInternalID kInternalID_HexBoltFineDIN3D			=	144;
const TInternalID kInternalID_HexBoltFlangeHeadDIN		=	145;
const TInternalID kInternalID_HexBoltFlgeHeadDIN3D		=	146;
const TInternalID kInternalID_HexCapNutDIN				=	147;
const TInternalID kInternalID_HexCapNutDIN3D			=	148;
const TInternalID kInternalID_HoleDrilled				=	149;
const TInternalID kInternalID_HoleDrilled3D				=	150;
const TInternalID kInternalID_HoleTappedInch			=	151;
const TInternalID kInternalID_HoleTappedInch3D			=	152;
const TInternalID kInternalID_HoleTappedMetric			=	153;
const TInternalID kInternalID_HoleTappedMetric3D		=	154;
const TInternalID kInternalID_HolePattern				=	155;
const TInternalID kInternalID_Hub3D						=	156;
const TInternalID kInternalID_HumanFigure				=	157;
const TInternalID kInternalID_HVACDamper				=	158;
const TInternalID kInternalID_HVACDiffuser				=	159;
const TInternalID kInternalID_HVACElbowDuct				=	160;
const TInternalID kInternalID_HVACFlexDuct				=	161;
const TInternalID kInternalID_HVACOutlet				=	162;
const TInternalID kInternalID_HVACSplitter				=	163;
const TInternalID kInternalID_HVACStraightDuct			=	164;
const TInternalID kInternalID_HVACTransition			=	165;
const TInternalID kInternalID_HVACVerticalDuct			=	166;
const TInternalID kInternalID_HVACVerticalElbow			=	167;
const TInternalID kInternalID_IBeam						=	168;
const TInternalID kInternalID_IBeamInch					=	169;
const TInternalID kInternalID_IBeamMetric				=	170;
const TInternalID kInternalID_IBeam3D					=	171;
const TInternalID kInternalID_IDLeader					=	172;
const TInternalID kInternalID_IFCEntity					=	173;
const TInternalID kInternalID_ImageProp					=	174;
const TInternalID kInternalID_IncandescentFixture		=	175;
const TInternalID kInternalID_IrrigationHead			=	176;
const TInternalID kInternalID_IrrigationLine			=	177;
const TInternalID kInternalID_JBolt						=	178;
const TInternalID kInternalID_JBolt3D					=	179;
const TInternalID kInternalID_Joist						=	180;
const TInternalID kInternalID_Key						=	181;
const TInternalID kInternalID_Key3D						=	182;
const TInternalID kInternalID_KeynoteLegend				=	183;
const TInternalID kInternalID_Keyway					=	184;
const TInternalID kInternalID_KnurledThumbNutDIN		=	185;
const TInternalID kInternalID_KnurledThumbNutDIN3D		=	186;
const TInternalID kInternalID_KnurledThumbNutInch		=	187;
const TInternalID kInternalID_KnurledThumbNutInch3D		=	188;
const TInternalID kInternalID_LagScrew					=	189;
const TInternalID kInternalID_LagScrew3D				=	190;
const TInternalID kInternalID_LandscapeArea				=	191;
const TInternalID kInternalID_LandscapeWall				=	192;
const TInternalID kInternalID_LandscapeWallArc			=	193;
const TInternalID kInternalID_LandscapeWallBez			=	194;
const TInternalID kInternalID_LeaderLine				=	195;
const TInternalID kInternalID_LightPositionObj			=	196;
const TInternalID kInternalID_LightingDevice			=	197;
const TInternalID kInternalID_LinearMaterial			=	198;
const TInternalID kInternalID_LinkedMarker				=	199;
const TInternalID kInternalID_LockWasherDIN				=	200;
const TInternalID kInternalID_LockWasherDIN3D			=	201;
const TInternalID kInternalID_LockWasherInch			=	202;
const TInternalID kInternalID_LockWasherInch3D			=	203;
const TInternalID kInternalID_LockWasherISO				=	204;
const TInternalID kInternalID_LockWasherISO3D			=	205;
const TInternalID kInternalID_LockWasherMetric			=	206;
const TInternalID kInternalID_LockWasherMetric3D		=	207;
const TInternalID kInternalID_MachineScrewDIN			=	208;
const TInternalID kInternalID_MachineScrewDIN3D			=	209;
const TInternalID kInternalID_MachineScrewInch			=	210;
const TInternalID kInternalID_MachineScrewInch3D		=	211;
const TInternalID kInternalID_MachineScrewISO			=	212;
const TInternalID kInternalID_MachineScrewISO3D			=	213;
const TInternalID kInternalID_MachineScrewMetric		=	214;
const TInternalID kInternalID_MachineScrewMetric3D		=	215;
const TInternalID kInternalID_MassingModel				=	216;
const TInternalID kInternalID_MaterialNote				=	217;
const TInternalID kInternalID_Mullion					=	218;
const TInternalID kInternalID_NeedleBearing				=	219;
const TInternalID kInternalID_NeedleBearing3D			=	220;
const TInternalID kInternalID_NNA_ArchSection			=	221;
const TInternalID kInternalID_NNA_ChainDim				=	222;
const TInternalID kInternalID_NNA_DesignLayerViewport	=	223;
const TInternalID kInternalID_NorthArrow				=	224;
const TInternalID kInternalID_NutDIN					=	225;
const TInternalID kInternalID_NutDIN3D					=	226;
const TInternalID kInternalID_NutInch					=	227;
const TInternalID kInternalID_NutInch3D					=	228;
const TInternalID kInternalID_NutISO					=	229;
const TInternalID kInternalID_NutISO3D					=	230;
const TInternalID kInternalID_NutMetric					=	231;
const TInternalID kInternalID_NutMetric3D				=	232;
const TInternalID kInternalID_ParabaloidObject			=	233;
const TInternalID kInternalID_ParallelPinDIN			=	234;
const TInternalID kInternalID_ParallelPinDIN3D			=	235;
const TInternalID kInternalID_ParkingAlongPath			=	236;
const TInternalID kInternalID_ParkingArea				=	237;
const TInternalID kInternalID_ParkingSpaces				=	238;
const TInternalID kInternalID_PartsList					=	239;
const TInternalID kInternalID_PhotoGrid					=	240;
const TInternalID kInternalID_Photometer				=	241;
const TInternalID kInternalID_Pilaster2					=	242;
const TInternalID kInternalID_PillowBlock				=	243;
const TInternalID kInternalID_PillowBlock3D				=	244;
const TInternalID kInternalID_PipeFitting				=	245;
const TInternalID kInternalID_Piping					=	246;
const TInternalID kInternalID_PipingConnection			=	247;
const TInternalID kInternalID_PipingRun					=	248;
const TInternalID kInternalID_PlainWasherDIN			=	249;
const TInternalID kInternalID_PlainWasherDIN3D			=	250;
const TInternalID kInternalID_PlainWasherInch			=	251;
const TInternalID kInternalID_PlainWasherInch3D			=	252;
const TInternalID kInternalID_PlainWasherISO			=	253;
const TInternalID kInternalID_PlainWasherISO3D			=	254;
const TInternalID kInternalID_PlainWasherMetric			=	255;
const TInternalID kInternalID_PlainWasherMetric3D		=	256;
const TInternalID kInternalID_Plant						=	257;
const TInternalID kInternalID_PropertyLine				=	258;
const TInternalID kInternalID_Pulley					=	259;
const TInternalID kInternalID_Pulley3D					=	260;
const TInternalID kInternalID_PyramidObject				=	261;
const TInternalID kInternalID_QuarterArc				=	262;
const TInternalID kInternalID_Rafter					=	263;
const TInternalID kInternalID_Ramp						=	264;
const TInternalID kInternalID_Receptacle				=	265;
const TInternalID kInternalID_RectangularTubing			=	266;
const TInternalID kInternalID_RectangularTubingInch		=	267;
const TInternalID kInternalID_RectangularTubingMetric	=	268;
const TInternalID kInternalID_RectangularTubing3D		=	269;
const TInternalID kInternalID_RedlineObject				=	270;
const TInternalID kInternalID_ReferenceMarker			=	271;
const TInternalID kInternalID_RepetitiveUnit			=	272;
const TInternalID kInternalID_RetainingRingASME			=	273;
const TInternalID kInternalID_RetainingRingASME3D		=	274;
const TInternalID kInternalID_RetainingRingDIN			=	275;
const TInternalID kInternalID_RetainingRingDIN3D		=	276;
const TInternalID kInternalID_RetainingWasherDIN		=	277;
const TInternalID kInternalID_RetainingWasherDIN3D		=	278;
const TInternalID kInternalID_RevisionBubble			=	279;
const TInternalID kInternalID_RevisionCloud				=	280;
const TInternalID kInternalID_RevisionMarker			=	281;
const TInternalID kInternalID_RivetDIN					=	282;
const TInternalID kInternalID_RivetDIN3D				=	283;
const TInternalID kInternalID_RivetLargeInch			=	284;
const TInternalID kInternalID_RivetLargeInch3D			=	285;
const TInternalID kInternalID_RivetSmallInch			=	286;
const TInternalID kInternalID_RivetSmallInch3D			=	287;
const TInternalID kInternalID_RoadwayBezier				=	288;
const TInternalID kInternalID_RoadwayCurved				=	289;
const TInternalID kInternalID_RoadwayNURBS				=	290;
const TInternalID kInternalID_RoadwayStraight			=	291;
const TInternalID kInternalID_RoadwayTee				=	292;
const TInternalID kInternalID_RollerBearing				=	293;
const TInternalID kInternalID_RollerBearing3D			=	294;
const TInternalID kInternalID_RollerChainCircular		=	295;
const TInternalID kInternalID_RollerChainCircular3D		=	296;
const TInternalID kInternalID_RollerChainLinear			=	297;
const TInternalID kInternalID_RollerChainLinear3D		=	298;
const TInternalID kInternalID_RollerChainOffsetLink		=	299;
const TInternalID kInternalID_RollerChainContinuous		=	300;
const TInternalID kInternalID_RollerChainContinuous3D	=	301;
const TInternalID kInternalID_RollerChainOffsetLink3D	=	302;
const TInternalID kInternalID_RoomName					=	303;
const TInternalID kInternalID_RoomNameSimple			=	304;
const TInternalID kInternalID_RoundTubing				=	305;
const TInternalID kInternalID_RoundTubingInch			=	306;
const TInternalID kInternalID_RoundTubingMetric			=	307;
const TInternalID kInternalID_RoundTubing3D				=	308;
const TInternalID kInternalID_ScaleBar					=	309;
const TInternalID kInternalID_ScrewandNutDIN			=	310;
const TInternalID kInternalID_ScrewandNutDIN3D			=	311;
const TInternalID kInternalID_ScrewandNutInch			=	312;
const TInternalID kInternalID_ScrewandNutInch3D			=	313;
const TInternalID kInternalID_ScrewandNutISO			=	314;
const TInternalID kInternalID_ScrewandNutISO3D			=	315;
const TInternalID kInternalID_ScrewandNutMetric			=	316;
const TInternalID kInternalID_ScrewandNutMetric3D		=	317;
const TInternalID kInternalID_ScrewThreads				=	318;
const TInternalID kInternalID_SeatingLayout				=	319;
const TInternalID kInternalID_SectionNote				=	320;
const TInternalID kInternalID_SectionElevationMarker	=	321;
const TInternalID kInternalID_SetScrewDIN				=	322;
const TInternalID kInternalID_SetScrewDIN3D				=	323;
const TInternalID kInternalID_SetScrewInch				=	324;
const TInternalID kInternalID_SetScrewInch3D			=	325;
const TInternalID kInternalID_SetScrewISO				=	326;
const TInternalID kInternalID_SetScrewISO3D				=	327;
const TInternalID kInternalID_SetScrewMetric			=	328;
const TInternalID kInternalID_SetScrewMetric3D			=	329;
const TInternalID kInternalID_Shaft						=	330;
const TInternalID kInternalID_Shaft3D					=	331;
const TInternalID kInternalID_ShaftBreak				=	332;
const TInternalID kInternalID_ShaftBreak2				=	333;
const TInternalID kInternalID_ShaftSegmentStraight		=	334;
const TInternalID kInternalID_ShaftSegmentStraight3D	=	335;
const TInternalID kInternalID_ShaftSegmentTapered		=	336;
const TInternalID kInternalID_ShaftSegmentTapered3D		=	337;
const TInternalID kInternalID_SheetMetalScrew			=	338;
const TInternalID kInternalID_SheetMetalScrew3D			=	339;
const TInternalID kInternalID_ShelvingUnit				=	340;
const TInternalID kInternalID_ShoulderScrewDIN			=	341;
const TInternalID kInternalID_ShoulderScrewDIN3D		=	342;
const TInternalID kInternalID_ShoulderScrewInch			=	343;
const TInternalID kInternalID_ShoulderScrewInch3D		=	344;
const TInternalID kInternalID_ShoulderScrewISO			=	345;
const TInternalID kInternalID_ShoulderScrewISO3D		=	346;
const TInternalID kInternalID_ShoulderScrewMetric		=	347;
const TInternalID kInternalID_ShoulderScrewMetric3D		=	348;
const TInternalID kInternalID_SimpleElevator			=	349;
const TInternalID kInternalID_SimpleStair				=	350;
const TInternalID kInternalID_SiteModifiers				=	351;
const TInternalID kInternalID_SlopeDimension			=	352;
const TInternalID kInternalID_Slot						=	353;
const TInternalID kInternalID_Space						=	354;
const TInternalID kInternalID_SpaceLink					=	355;
const TInternalID kInternalID_SphereObject				=	356;
const TInternalID kInternalID_Spiral					=	357;
const TInternalID kInternalID_Sprocket					=	358;
const TInternalID kInternalID_Sprocket3D				=	359;
const TInternalID kInternalID_SpurGear					=	360;
const TInternalID kInternalID_SpurGearRack				=	361;
const TInternalID kInternalID_SpurGearRack3D			=	362;
const TInternalID kInternalID_SpurGear3D				=	363;
const TInternalID kInternalID_SquareTubing				=	364;
const TInternalID kInternalID_SquareTubingInch			=	365;
const TInternalID kInternalID_SquareTubingMetric		=	366;
const TInternalID kInternalID_SquareTubing3D			=	367;
const TInternalID kInternalID_StackingDiagram			=	368;
const TInternalID kInternalID_Stage						=	369;
const TInternalID kInternalID_StakeObject				=	370;
const TInternalID kInternalID_Stipple					=	371;
const TInternalID kInternalID_Storypole					=	372;
const TInternalID kInternalID_StraightTruss				=	373;
const TInternalID kInternalID_SurfaceTextureSymbol		=	374;
const TInternalID kInternalID_SwingBolt					=	375;
const TInternalID kInternalID_SwingBolt3D				=	376;
const TInternalID kInternalID_SwingEyeBolt				=	377;
const TInternalID kInternalID_SwingEyeBolt3D			=	378;
const TInternalID kInternalID_Switch					=	379;
const TInternalID kInternalID_TBolt						=	380;
const TInternalID kInternalID_TBolt3D					=	381;
const TInternalID kInternalID_Table						=	382;
const TInternalID kInternalID_TableandChairs			=	383;
const TInternalID kInternalID_TaperPinDIN				=	384;
const TInternalID kInternalID_TaperPinDIN3D				=	385;
const TInternalID kInternalID_TaperPinInch				=	386;
const TInternalID kInternalID_TaperPinInch3D			=	387;
const TInternalID kInternalID_TaperedExtrude			=	388;
const TInternalID kInternalID_TaperedRollerBearing		=	389;
const TInternalID kInternalID_TaperedRollerBearing3D	=	390;
const TInternalID kInternalID_Tee						=	391;
const TInternalID kInternalID_TeeInch					=	392;
const TInternalID kInternalID_TeeMetric					=	393;
const TInternalID kInternalID_Tee3D						=	394;
const TInternalID kInternalID_Television				=	395;
const TInternalID kInternalID_TextAlongPath				=	396;
const TInternalID kInternalID_ThreadedShaft				=	397;
const TInternalID kInternalID_ThreadedShaft3D			=	398;
const TInternalID kInternalID_ThrustBearing				=	399;
const TInternalID kInternalID_ThrustBearing3D			=	400;
const TInternalID kInternalID_ThumbScrewInch			=	401;
const TInternalID kInternalID_ThumbScrewInch3D			=	402;
const TInternalID kInternalID_ToiletStall				=	403;
const TInternalID kInternalID_TorsionSpring3D			=	404;
const TInternalID kInternalID_TorsionSpringEnd			=	405;
const TInternalID kInternalID_TorsionSpringFront		=	406;
const TInternalID kInternalID_TorusObject				=	407;
const TInternalID kInternalID_TubularRivetDIN			=	408;
const TInternalID kInternalID_TubularRivetDIN3D			=	409;
const TInternalID kInternalID_TwoFerObject				=	410;
const TInternalID kInternalID_UBolt						=	411;
const TInternalID kInternalID_UBolt3D					=	412;
const TInternalID kInternalID_UtilityCabinet			=	413;
const TInternalID kInternalID_VideoScreen				=	414;
const TInternalID kInternalID_WallCabinet				=	415;
const TInternalID kInternalID_WallFeature				=	416;
const TInternalID kInternalID_WeldingSymFilletAWS		=	417;
const TInternalID kInternalID_WeldingSymFilletISO		=	418;
const TInternalID kInternalID_WeldingSymFlangeAWS		=	419;
const TInternalID kInternalID_WeldingSymFlangeISO		=	420;
const TInternalID kInternalID_WeldingSymGrooveAWS		=	421;
const TInternalID kInternalID_WeldingSymGrooveISO		=	422;
const TInternalID kInternalID_WeldingSymMiscAWS			=	423;
const TInternalID kInternalID_WeldingSymMiscISO			=	424;
const TInternalID kInternalID_WeldingSymSlotPlugAWS		=	425;
const TInternalID kInternalID_WeldingSymSlotPlugISO		=	426;
const TInternalID kInternalID_WideFlange				=	427;
const TInternalID kInternalID_WideFlangeInch			=	428;
const TInternalID kInternalID_WideFlangeMetric			=	429;
const TInternalID kInternalID_WideFlange3D				=	430;
const TInternalID kInternalID_Window					=	431;
const TInternalID kInternalID_WindowWallCurved			=	432;
const TInternalID kInternalID_WindowWallStraight		=	433;
const TInternalID kInternalID_WingNutDIN				=	434;
const TInternalID kInternalID_WingNutDIN3D				=	435;
const TInternalID kInternalID_WingNutTypeAInch			=	436;
const TInternalID kInternalID_WingNutTypeAInch3D		=	437;
const TInternalID kInternalID_WingNutTypeBInch			=	438;
const TInternalID kInternalID_WingNutTypeBInch3D		=	439;
const TInternalID kInternalID_WingNutTypeCInch			=	440;
const TInternalID kInternalID_WingNutTypeCInch3D		=	441;
const TInternalID kInternalID_WingNutTypeDInch			=	442;
const TInternalID kInternalID_WingNutTypeDInch3D		=	443;
const TInternalID kInternalID_WoodScrew					=	444;
const TInternalID kInternalID_WoodScrew3D				=	445;
const TInternalID kInternalID_WoodruffKey				=	446;
const TInternalID kInternalID_WoodruffKey3D				=	447;
const TInternalID kInternalID_WorkstationCounter		=	448;
const TInternalID kInternalID_WorkstationOverhead		=	449;
const TInternalID kInternalID_WorkstationPanel			=	450;
const TInternalID kInternalID_WorkstationPedestal		=	451;
const TInternalID kInternalID_Worm						=	452;
const TInternalID kInternalID_Worm3D					=	453;
const TInternalID kInternalID_WormGear					=	454;
const TInternalID kInternalID_WormGear3D				=	455;
const TInternalID kInternalID_ZSection					=	456;
const TInternalID kInternalID_ZSection3D				=	457;
const TInternalID kInternalID___PDF						=	458;
const TInternalID kInternalID_Slab						=	459;
const TInternalID kInternalID_RenderWorks_Camera		=	460;
const TInternalID kInternalID_InteriorCAD_XGKMPIO		=	461;
const TInternalID kInternalID_Heliodon					=	462;
const TInternalID kInternalID_NNA_ArchDetail			=	463;
const TInternalID kInternalID_AutoHybrid				=	464;
const TInternalID kInternalID_SurfaceArray				=	465;
const TInternalID kInternalID_Hyperlink					=	466;
const TInternalID kInternalID_LEDScreen					=	467;
const TInternalID kInternalID_Speaker					=	468;
const TInternalID kInternalID_SpeakerArray				=	469;
const TInternalID kInternalID_VS4Television				=	470;
const TInternalID kInternalID_VS4Projection				=	471;
const TInternalID kInternalID_VS4BlendedScreen			=	472;
const TInternalID kInternalID_VS4BlendedProjector		=	473;
const TInternalID kInternalID_VS4LED					=	474;
const TInternalID kInternalID_AudioBox2					=	475;
const TInternalID kInternalID_AudioArray2				=	476;
const TInternalID kInternalID_LightingPipe				=	477;
const TInternalID kInternalID_LightingPipeLadder		=	478;
const TInternalID kInternalID_InstrumentSummary			=	479;
const TInternalID kInternalID_StairsCW					=	480;
const TInternalID kInternalID_BaugrubeAufschuttungCW	=	481;
const TInternalID kInternalID_ExcavationCW              =	kInternalID_BaugrubeAufschuttungCW;
const TInternalID kInternalID_EinzelstempelCW			=	482;
const TInternalID kInternalID_SingleStampCW             =	kInternalID_EinzelstempelCW;
const TInternalID kInternalID_ExtentionlineCW			=	483;
const TInternalID kInternalID_GuideLineCW               =	kInternalID_ExtentionlineCW;
const TInternalID kInternalID_FensterCW					=	484;
const TInternalID kInternalID_WindowCW					=	kInternalID_FensterCW;
const TInternalID kInternalID_FurnitureSet				=	485;
const TInternalID kInternalID_GebaudeCW					=	486;
const TInternalID kInternalID_BuildingCW				=	kInternalID_GebaudeCW;
const TInternalID kInternalID_GebaudeeigeneFormCW		=	487;
const TInternalID kInternalID_CustomBuildingCW          =	kInternalID_GebaudeeigeneFormCW;
const TInternalID kInternalID_GefalleGrundrissCW		=	488;
const TInternalID kInternalID_GradeCW                   =   kInternalID_GefalleGrundrissCW;
const TInternalID kInternalID_GridCW					=	489;
const TInternalID kInternalID_KantenausbildungCW		=	490;
const TInternalID kInternalID_EdgeDetailCW              =	kInternalID_KantenausbildungCW;
const TInternalID kInternalID_LegendeCW					=	491;
const TInternalID kInternalID_LegendCW					=	kInternalID_LegendeCW;
const TInternalID kInternalID_LichtschachtCW			=	492;
const TInternalID kInternalID_LightWellCW               =	kInternalID_LichtschachtCW;
const TInternalID kInternalID_OrdinateDimensionCW		=	493;
const TInternalID kInternalID_PerpendicularDimensionCW	=	494;
const TInternalID kInternalID_PflanzeVBvisual			=	495;
const TInternalID kInternalID_VbvisualPlantCW			=	kInternalID_PflanzeVBvisual;
const TInternalID kInternalID_PflanzenDBCW				=	496;
const TInternalID kInternalID_PflanzenDBPfadCW			=	497;
const TInternalID kInternalID_PictureFrameCW			=	498;
const TInternalID kInternalID_Railing					=	499;
const TInternalID kInternalID_RailingCW					=	kInternalID_Railing;
const TInternalID kInternalID_ReihenpflanzungRegenCW	=	500;
const TInternalID kInternalID_SchlitzeDurchbrCW			=	501;
const TInternalID kInternalID_BreakOpeningCW			=	kInternalID_SchlitzeDurchbrCW;
const TInternalID kInternalID_StampCW					=	502;
const TInternalID kInternalID_TurenCW					=	503;
const TInternalID kInternalID_DoorCW					=	kInternalID_TurenCW;
const TInternalID kInternalID_VerbandspflanzungRegenCW	=	504;
const TInternalID kInternalID_WinDoor60					=	505;
const TInternalID kIntrenalID_DetailCalloutMarker		=   507;
const TInternalID kIntrenalID_Graticule					=   508;
const TInternalID kIntrenalID_GreatCircle				=   509;
const TInternalID kIntrenalID_SoftGoods					=   510;
const TInternalID kIntrenalID_WallEndCap				=   511;
const TInternalID kInternalID_VS5Television				=	512;
const TInternalID kInternalID_VS5Projection				=	513;
const TInternalID kInternalID_VS5BlendedScreen			=	514;
const TInternalID kInternalID_VS5BlendedProjector		=	515;
const TInternalID kInternalID_VS5LED					=	516;
const TInternalID kInternalID_StageDeck					=	517;
const TInternalID kInternalID_StageLift					=	518;
const TInternalID kInternalID_StagePlug					=	519;
const TInternalID kInternalID_StageRamp					=	520;
const TInternalID kInternalID_StageSteps				=	521;
const TInternalID kInternalID_RoadwayCustomCurb			=	522;
const TInternalID kInternalID_RoadwayPoly				=	523;
const TInternalID kInternalID_RetainingWallModifier		=	524;
const TInternalID kInternalID_PointCloud				=	525;
const TInternalID kInternalID_Subdivision				=	526;
const TInternalID kInternalID_MarionetteNode			=	527;
const TInternalID kInternalID_MarionetteObject2D		=	528;
const TInternalID kInternalID_MarionetteObject3D		=	529;
const TInternalID kInternalID_IrrigationController		=	530;
const TInternalID kInternalID_IrrigationConnectionPoint	=	531;
const TInternalID kInternalID_IrrigationControllerWire	=	532;
const TInternalID kInternalID_IrrigationOutlet			=	533;
const TInternalID kInternalID_IrrigationPipe			=	534;
const TInternalID kInternalID_IrrigationSystemComponent	=	535;
const TInternalID kInternalID_IrrigationDesignZone		=	536;
const TInternalID kInternalID_StructuralMember			=	537;
const TInternalID kInternalID_StructuralComponent		=	538;
const TInternalID kInternalID_IrrigationOutletDrip		=	539;
const TInternalID kInternalID_IrrigationValve			=	540;
const TInternalID kInternalID_IrrigationHydroZone		=	541;
const TInternalID kInternalID_TagLabel					=	542;
const TInternalID kInternalID_NNA_ArchInteriorElevation	=	543;
const TInternalID kInternalID_RopeAndStanchion			=	544;
const TInternalID kInternalID_ProofOfMassesCW           =   545;
const TInternalID kInternalID_SiteModelSectionLineCW	=   546;
const TInternalID kInternalID_SiteModelSectionCW        =   547;
const TInternalID kInternalID_InsulationSlopedCW        =   548;
const TInternalID kInternalID_Mullion2					=	549;
const TInternalID kInternalID_RevitEntity		        =   550;
const TInternalID kInternalID_Foliage					=	551;
const TInternalID kInternalID_TitleBlockBorder			=	552;
const TInternalID kInternalID_Ouverture					=	553;
const TInternalID kInternalID_SavvyPositionLabel		=	554;
const TInternalID kInternalID_SourceFourSavvySection	=	555;
const TInternalID kInternalID_SavvySymbolSection		=	556;
const TInternalID kInternalID_BeamDraw					=	557;
const TInternalID kInternalID_BeamDrawPAR				=	558;
const TInternalID kInternalID_BeamDrawSection			=	559;
const TInternalID kInternalID_BeamDrawMagic				=	560;
const TInternalID kInternalID_SavvyLSSched				=	561;
const TInternalID kInternalID_SavvyLSItem				=	562;
const TInternalID kInternalID_SavvyLSSection			=	563;
const TInternalID kInternalID_ProjectorViz				=	564;
const TInternalID kInternalID_Porta						=	565;			
const TInternalID kInternalID_Finestra					=	566;	
const TInternalID kInternalID_Basculante				=	567;
const TInternalID kInternalID_Capriata					=	568;
const TInternalID kInternalID_Infissosutracciato		=	569;
const TInternalID kInteralID_VMElectricalSwitch			=	570;
const TInternalID kInteralID_VMCommunicationDevice      =	571;
const TInternalID kInteralID_VMDataDevice               =	572;
const TInternalID kInteralID_VMElectricalFixture        =	573;
const TInternalID kInteralID_VMElectricalDevice			=	574;
const TInternalID kInteralID_VMFireAlarmDevice          =	575;
const TInternalID kInteralID_VMLightingFixture			=	576;
const TInternalID kInteralID_VMNurseCallDevice			=	577;
const TInternalID kInteralID_VMSecurityDevice			=	578;
const TInternalID kInteralID_VMTelephoneDevice			=	579;
const TInternalID kInteralID_VMJunctionBox				=	580;
const TInternalID kInteralID_VMDataSwitch				=	581;
const TInternalID kInteralID_VMBranchPanel				=	582;
const TInternalID kInteralID_VMSwitchBoard				=	583;
const TInternalID kInteralID_VMDataPanel				=	584;
const TInternalID kInteralID_VMDuctConnector            =	585;
const TInternalID kInteralID_VMPipeConnector            =	586;
const TInternalID kInteralID_VMElectricalConnector      =	587;
const TInternalID kInteralID_VMCableCarrierConnector    =	588;
const TInternalID kInteralID_VMDuctAccessory            =	589;
const TInternalID kInteralID_VMPipeAccessory			=	590;
const TInternalID kInteralID_VMPlumbingFixture			=	591;
const TInternalID kInteralID_VMMechanicalEquipment		=	592;
const TInternalID kInteralID_VMClassLegend              =	593;
const TInternalID kInteralID_VMGuideline                =	594;
const TInternalID kInteralID_VMRadiator                 =	595;
const TInternalID kInteralID_VMSymbolObject             =	596;
const TInternalID kInteralID_VMDuctAirTerminal          =	597;
const TInternalID kInteralID_VMMEPSegmentLabel          =	598;
const TInternalID kInternalID_DataTag			        =	599;
const TInternalID kInternalID_JA_PillarsStuds			=   600;
const TInternalID kInternalID_JA_BeamGirder				=   601;
const TInternalID kInternalID_JA_Brace					=   602;
const TInternalID kInternalID_JA_WindowTableLintel		=   603;
const TInternalID kInternalID_JA_FlingBeam				=   604;
const TInternalID kInternalID_JA_Rafters				=   605;
const TInternalID kInternalID_JA_SteelBunch				=   606;
const TInternalID kInternalID_JA_VehicleLocus			=   607;
const TInternalID kInternalID_JA_SwitchOutlet			=   608;
const TInternalID kInternalID_BIMobject					=   609;
const TInternalID kInternalID_HoistVW					=   610;
const TInternalID kInternalID_VideoCamera				=   611;
const TInternalID kInternalID_SeatingSection			=	612;
const TInternalID kInternalID_AnimatePath				=	613;
const TInternalID kInternalID_Aisle						=	614;
const TInternalID kInternalID_DataVisualizationLegend	=	615;
const TInternalID kInternalID_NNA_TransformGroup		=	616;
const TInternalID kInternalID_SchematicViewObject		=	617;
const TInternalID kInternalID_GeoimageService			=	618;
const TInternalID kInternalID_CCDevice					=	619;
const TInternalID kInternalID_CCExternal				=	620;
const TInternalID kInternalID_CCSocket					=	621;
const TInternalID kInternalID_CCCircuit					=	622;
const TInternalID kInternalID_CCLink					=	623;
const TInternalID kInternalID_CCRoom2D					=	624;
const TInternalID kInternalID_CCEquipRack				=	625;
const TInternalID kInternalID_CCRackFrame				=	626;
const TInternalID kInternalID_CCEquipItem				=	627;
const TInternalID kInternalID_CCLegend					=	628;
const TInternalID kInternalID_CCRackRuler				=	629;
const TInternalID kInternalID_CC3DEquipRack				=	630;
const TInternalID kInternalID_BridleObj					=	631;
const TInternalID kInternalID_BrxTrussResult			=	632;
const TInternalID kInternalID_BridleAssembleInformation =	633;
const TInternalID kInternalID_BrxLabel					=	634;
const TInternalID kInternalID_BrxLoadingPoint			=	635;
const TInternalID kInternalID_BrxCustomTrussCross		=	636;
const TInternalID KInternalID_BrxDistributedWeight		=	637;
const TInternalID kInternalID_VWFemObject				=	638;
const TInternalID KInternalID_BrxGenericWeight			=	639;
const TInternalID kInternalID_HouseRiggingPoint			=	640;
const TInternalID kInternalID_TrussItem					=	641;

const TInternalID kInternalID_DrawingLabel2				=	642;
const TInternalID kInternalID_ReferenceMarker2			=	643;
const TInternalID kInternalID_InteriorElevation2		=	644;
const TInternalID kInternalID_SectionLine2				=	645;
const TInternalID kInternalID_DetailCallout2			=	646;
const TInternalID kInternalID_GridAxis					=	647;
const TInternalID kInternalID_Roadway					=	648;
const TInternalID kInternalID_CableObject				=	649;

const TInternalID kInternalID_ElectricalObject			=	650;
const TInternalID kInternalID_ElectricalComponent		=	651;
const TInternalID kInternalID_ElectricalItem			=	652;

/////////////	---------------------------------------------------------------
/////////////	---------------------------------------------------------------
/////////////	---------------------------------------------------------------
/////////////	---------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
	typedef void GS_API_PTR(GenericFunctionPtr)(void);
	typedef GenericFunctionPtr GS_API_PTR(RetrieverPtr)(Sint32 id);
#ifdef __cplusplus
}
#endif

	typedef RetrieverPtr RetrieverProcUPP;

	#define CallRetrieverProc(userRoutine, id)		\
			(*(userRoutine))((id))
	#define NewRetrieverProc(userRoutine)		\
			(RetrieverProcUPP) (userRoutine)

#ifdef _MINICAD_
	extern "C" GenericFunctionPtr GS_API FIDToPtr(Sint32 id);
	extern RetrieverProcUPP gFIDToPtrUPP;
#endif

	struct GS_API CallBackBlock {
		RetrieverProcUPP	rPtr;
		#ifndef _WINDOWS
		Sint32				a4store;	// *** JAK *** We dont need this. Remove it soon.
		#endif
		
		#ifdef _MINICAD_
		CallBackBlock()
			{ rPtr = gFIDToPtrUPP; }
		#endif
		CallBackBlock(const CallBackBlock *cbp)
			{ this->rPtr = cbp ? cbp->rPtr : NULL; }
	};
	typedef CallBackBlock *CallBackPtr;


////////////////////////
// GLOBAL CallBackPtr
//   In VectorWorks, this should be passed to all GS_ calls and does nothing.
//   In externals, this should be used as the global callback pointer.
////////////////////////

extern CallBackPtr gCBP;

////////////////////////
// GLOBAL pointer to the SDK VCOM funtion interface
//   In VectorWorks, this is initialized during start up
//   In externals, this should be queried in the main.
////////////////////////
namespace VectorWorks { class ISDK; }

extern VectorWorks::ISDK*	gSDK;

////////////////////////
// This retrieves a pointer to a gVWMM->Partition which is the top level for memory allocation using
// VWMM. If you want to allocate memory using NewHandle, pooling, or VWMM's Allocate/Deallocate, you have
// to have a Partition.
// This is guaranteed to return a valid pointer to a partition.
////////////////////////
extern VWMM::Partition* gVWMM;

////////////////////////
// GLOBAL pointer to the IFC support interface
////////////////////////
namespace VectorWorks { namespace IFCLib { class IIFCSupport; } }

namespace VectorWorks
{
	namespace IFCLib
	{
		class IIFCSupportAccessor
		{
		public:
						 operator IIFCSupport*();
			IIFCSupport* operator->();

			void		Release();

		private:
			VCOMPtr<IIFCSupport>	fPtr;
		};
	}
}

extern VectorWorks::IFCLib::IIFCSupportAccessor gIFC;

////////////////////////
// GLOBAL pointer to the DataTag support interface
////////////////////////
namespace VectorWorks { namespace Extension { class IDataTagSupport; } }

namespace VectorWorks
{
	namespace Extension
	{
		class IDataTagSupportAccessor
		{
		public:
								operator IDataTagSupport*();
			IDataTagSupport*	operator->();

			void				Release();

		private:
			VCOMPtr<IDataTagSupport> fPtr;
		};
	}
}

extern VectorWorks::Extension::IDataTagSupportAccessor gDataTagSupport;

////////////////////////
// GLOBAL pointer to the Record/Format support interface
////////////////////////
class IFormatHandlerSupport;

class IFormatHandlerSupportAccessor
{
public:
							operator IFormatHandlerSupport*();
	IFormatHandlerSupport*	operator->();

	void				Release();

private:
	VCOMPtr<IFormatHandlerSupport> fPtr;
};

extern IFormatHandlerSupportAccessor gFormatHandlerSupport;

////////////////////////
// GSCharsHandle
//   Used in VectorWorks objects which maintain a handle to characters
////////////////////////

typedef char **GSCharsHandle;


//-----------------------------------------------------------------
// GS_SDKPPC_JAK
// GS_SDKPPC_JAK2


#ifndef GSEBUILDTYPES
	#define GSEBUILDTYPES
	const short kMiniCad = 1;
	const short kBlueprint = 2;
#endif

#if defined(_WINDOWS) && !defined(_MINICAD_)
	#if !defined(UNDEF_PASCAL) || (UNDEF_PASCAL != 0)
		#ifdef pascal
			#undef pascal
		#endif
		#define pascal
	#endif
#endif



// these are the most commonly used list size constants
// See LDef.h for additional size constants
#if _WINDOWS

	const short kSmallListElementHeight=	14;
	const short kLargeListElementHeight=	14;
	const short kIconListElementHeight=		32;
	const short kSICNListElementHeight=		16;
	
#else

	const short kSmallListElementHeight=	12;
	const short kLargeListElementHeight=	16;
	const short kIconListElementHeight=		32;
	const short kSICNListElementHeight=		16;

#endif

// DrawRefCon constants
typedef short TListType;
const TListType 
	refNormal = -50,
	refLayers = -49,		// obsolete.
	refMoveSymbols = -48,
	refRecFld = -47,
	refTmp= -46,			// obsolete.
	refCheck = -45,		// obsolete.
	refSICN = -44,		// obsolete.
	refTiny = -43,
	
	refLarge = -42,
	refSmall = -41,
	refLargeCheck = -40,
	refSmallCheck = -39
;


typedef short ItemStatus;
const ItemStatus
	kActive = 2,
	kCheckOn = 4;

#endif
