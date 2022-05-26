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

// Notification constants to be used with the IObjUpdateSupportContext interface
// See the 'UpdateManager' sample in the SDK

const Sint32 kNotifyBeforePendingUpdate		= 'BEFO';	// Notification listeners can use NotificationHandler object to
const Sint32 kNotifyAfterPendingUpdate		= 'AFTE';	//	help optimize pending notifications.  Many notifications
														//	are handed out in a loop (From OnIdle) NotificationHandler
														//	allows listeners to wait until the after all pending notifications
														//	to consolodate listener behavior.  The shape pane is able to 
														//	consolodate kNotifySelChange and kNotifyEditChange into one response 
														//	rather than two.


const Sint32 kNotifyDocChanging			= 'DOCG';		// Send before a document becomes frontmost or closes
const Sint32 kNotifyDocChange			= 'DOCC';		// Send when a different document becomes the frontmost one
const Sint32 kNotifyDocClose			= 'DCLS';		// Send when a document closes.
const Sint32 kNotifyDocCloseDone		= 'DCLD';		// Send when a document is done closing.
const Sint32 kNotifySelChange			= 'SELC';
const Sint32 kNotifyLockObjectChange	= 'Lock';		// Object(s) have had their Lock flag changed.
const Sint32 kNotifyMenuDone			= 'DONE';

const Sint32 kNotifyDocPreSaved			= 'dcrs';		// Send just before a file is saved (immediate send)
const Sint32 kNotifyDocPostSaved		= 'dcps';		// Send just after a file has been saved (immediate send)
const Sint32 kNotifyDocPreOpen			= 'dc0p';		// Send just before a file is opened (immediate send)
const Sint32 kNotifyDocOpen				= 'dcop';		// Send after a file was opened (immediate send)

const Sint32 kNotifyWPChange			= 'wpch';
const Sint32 kNotifyWPListChange		= 'wpxx';
const Sint32 kNotifyDimStdChange		= 'DIMS';
const Sint32 kNotifyLayerChange			= 'LAYR';
const Sint32 kNotifyClassChange			= 'CLAS';
const Sint32 kNotifyBuildingMaterialChange = 'BMAT';    // Sent when a Building material created, deleted or edited
const Sint32 kNotifyPlaneChange			= 'PLNE';
const Sint32 kNotifySubscripAddDel		= 'SbAD';		// Send when a subscription [reference] has been added or deleted
const Sint32 kNotify3DViewChange		= '3DVC';
const Sint32 kNotifyViewChange			= 'VIEW';
const Sint32 kNotifyTextChange			= 'TEXT';		// Send when text menus or att palette is changed on a VW text object
										  
const Sint32 kNotifyTextEditChange		= 'TXED';		// Send when a change occurs while editing text in TextEdit.
const Sint32 kNotifyEditChange			= 'Edit';
										  
const Sint32 kNotifySymFldrAddDel		= 'SFCh';		// Send when a symbol folder has been added or deleted
const Sint32 kNotifySymChange			= 'RcCh';		// Send when a symbol def has been added, deleted, or edited; mName of symbol can be passed[?]
										 				//  (does not force drawing object redraw--must call InvalRef or general InvalDrawing)
const Sint32 kNotifyHatchChange			= 'htch';		// Send when a hatch has been added, deleted, or edited; does not force object redraw
										 				//  (must call InvalObjectsWithVectorFillReference or InvalRef or general InvalDrawing)
const Sint32 kNotifyGradientChange		= 'GRCh';		// Send when a gradient has been added, deleted, or edited;
const Sint32 kNotifyImageChange			= 'IMCh';		// Send when an image has been added, deleted, or edited;
const Sint32 kNotifyTileChange			= 'TICh';		// Send when an tile has been added, deleted, or edited;
const Sint32 kNotifyLineTypeChange		= 'LTCh';		// Send when a line type has been added, deleted, or edited;
const Sint32 kNotifyMarkerChange		= 'MkCh';		// Send when a marker has been added, deleted or edited

const Sint32 kNotifyTextureChange		= 'TxCh';		// Send when a texture node has been added, deleted, or edited
const Sint32 kNotifyRecordChange		= 'RFCh';		// Send when a record format is added, deleted, or edited; mName of format can be passed[?]
const Sint32 kNotifySketchChange		= 'SkCh';		// Send when a sketch has been added, deleted or edited
const Sint32 kNotifyDelayTileChange     = 'DTIC';       // Send when a tile change should be delayed until resource previews are generated
const Sint32 kNotifyDelayLineTypeChange = 'DLTC';       // Send when a line type change should be delayed until resource previews are generated

const Sint32 kNotifyRecordAttached		= 'Ratt';		// Send when a record is attached to object
const Sint32 kNotifyRecordDetached		= 'Rdet';		// Send when a record is removed from object

const Sint32 kNotifyWSAddDelChange		= 'WSCh';		// Send when a worksheet is added or deleted (the worksheetNode itself, not object on drawing)
const Sint32 kNotifyWallStyleChange		= 'WaCh';		// Send when a Wall Style has been added, deleted, or edited
const Sint32 kNotifySlabStyleChange		= 'SlCh';		// Send when a Slab Style has been added, deleted, or edited
const Sint32 kNotifyRoofStyleChange		= 'RlCh';		// Send when a Roof Style has been added, deleted, or edited

const Sint32 kNotifyWallAdd				= 'WAdd';		// Send when a wall or round wall has been added
const Sint32 kNotifyWallDelete			= 'WDel';		// Send when a wall or round wall has been deleted
const Sint32 kNotifyWallEdit			= 'WEdt';		// Send when a wall or round wall has been edited
const Sint32 kNotifyTextStyleChange		= 'TSCh';		// Send when a Text Style has been added, deleted, or edited
const Sint32 kNotifyComPalChange		= 'CCha';		// Send on a VS command-related change--added, deleted or renamed palette, or added, deleted
														// or renamed tool; if change was to a tool, will pass negative RefNumber of the palette, which
														// will be used to get its open window updated; if change was to a palette, will pass RefNumber of
														// the palette, which will be used to update the File View in the Resource Manager
const Sint32 kNotifyRenderBackgroundChange	= 'RBCh';	// Send when a render background node has been added, deleted, or edited
const Sint32 kNotifyRenderStyleChange		= 'RWSt';	// Send when a render style node has been added, deleted, or edited
const Sint32 kNotifyPlugInObjectUpdate		= 'PObj';	// Version-update a Plug-in Object; add, remove, or modify a parameter
const Sint32 kNotifyVectorScriptResume		= 'VSRs';	//	Sent when a paused vectorScript should be resumed.

const Sint32 kNotifyUserOriginChange	='Orgn';		// Sent when user resets the user Origin
const Sint32 kNotifyPush3DView			='P3DV';		// Sent when a view change is completed so it can be saved in the view stack
const Sint32 kNotifyPush2DView			='P2DV';
const Sint32 kNotifyPushVisibility		='PVIS';		// Sent when a layer or class visibility is changed so it can be saved on the view stack
const Sint32 kNotifyPushRenderMode		='PRMD';		// Send when the render mode is changed so it can be saved on the view stack
const Sint32 kNotifyUndrawScrMods		='UScm';		// Sent before the screen is changed so tools can clean up
const Sint32 kNotifyDrawScrMods			='DScm';		// Sent after kNotifyUndrawScrMods, when the screen changes are done
const Sint32 kNotifyDisplayPrecision	='Prec';		// Sent the display precision has changed.
const Sint32 kNotifyGridAngleChange		='GAng';		// Sent the when the grid angle changes.
const Sint32 kNotifyRemoveToolPt		='rtpt';		// Sent the when the user invokes a remove last tool point action.

const Sint32 kNotifyToolChange			='TLCh';		// Sent when the current tool has changed.

const Sint32 kNotifyBeginToolMode		='BTOO';		//	Sent when the current tool begins collecting points
const Sint32 kNotifyEndToolMode			='ETOO';		//	Sent when the current tool finishes collecting points

const Sint32 kDrawDataBar				='dBar';		//	Sent when the dataBar needs to be redrawn.  This screems for a more generalized name
const Sint32 kNotifyDataBarValEntered	='dBCh';		// Sent when a value has been entered in the dataBar

const Sint32 kNotifyEnableTextureChange	='ETXT';		//	The value of gSysEnv.enableTexture has changed.
const Sint32 kNotifyUpdate				='updt';		// Generic message used to notify receiver to update itself

const Sint32 kNotifyNewWrkSpace			='NWKS';		// Tell client to load in new workspace
const Sint32 kNotifyNewWrkSpaceLoaded	='WKSL';		// Tell client that workspace has finished loading (preceded by kNotifyNewWrkSpace)
const Sint32 kNotifyWorkspaceEditorRequested = 'WKEd';	// Tell client that the user has requested to use the workspace editor.

const Sint32 kNotifyPrefsReset			='PrfR';		// Send when preferences have been reset
const Sint32 kNotifyPrefsChanged		='PrCh';		// Send when preferences change (after user preses OK in TMCPrefsDlg)

const Sint32 kNotifyAutosaveDone			='AsDn';	// Send when autosave is done
const Sint32 kNotifyBackupDone				='BkDn';	// Send when autosave to backup copy is done
const Sint32 kNotifyAutosaveTimerReset		='AsTR';	// Send when user cancelled autosave and interval based on minutes
const Sint32 kNotifyAutosaveCounterReset	='AsCR';	// Send when user cancelled autosave and interval based on operations
const Sint32 kNotifyAutosaveDisabled		='AsDb';	// Send when autosave is disabled
const Sint32 kNotifyAutosaveSuspended		='AsSu';	// Send when autosave is suspended for the active document

const Sint32 kNotifyEscExitDone		= 'EsEx';			// Send when EscEsc is done to exit an editing mode

const Sint32 kNotifyProtectionSystemEvent	= 'Pevt';
const Sint32 kNotifyDongleProtectionEvent	= 'DPet';	// The dongle or network dongle protection system has alerted the system of new license check results.

const Sint32 kNotifyNavPalViewportChange	= 'NPVP';	// Send to update the Navigation Palette when a viewport has been modified.
const Sint32 kNotifyNavPalReferenceChange	= 'NPVP';	// Send to update the Navigation Palette when a reference has been modified.

const Sint32 kNotifyStackLayerChange		= 'STLC';	// Send when immediate notifications are processed while in stack layer mode. Do not use it outside stack layer context.

const Sint32 kNotifyOIPFontMenuUpdate		= 'OIPF';	// Send to update the OIP font pulldown.

const Sint32 kNotifyExecuteSystemTests		= 'ExUT';	// Send to run the pending unit tests.

const Sint32 kNotifyRecordFieldDataChange		= 'RfdC';	// Send when record field data changed and the data pane of the OIP need to be updated. 
const Sint32 kNotifyRecordFieldDataOIPChaged	= 'RfvC';	// Send when record field data changed in the OIP. 

const Sint32 kNotifyVisPalLightChange	= 'VPLP';	// Send to update the Visualization Palette when the light pane needs to be refreshed.
const Sint32 kNotifyVisPalCameraChange	= 'VPCP';	// Send to update the Visualization Palette when the camera pane needs to be refreshed.

//----------
// For the Classes, layers and planes menu item in the databar.
	const Sint32 kNotifyDisplayClassesDialog	= 'DBCl';	// Send when the classes dialog needs to be dsiplayed.
	const Sint32 kNotifyDisplayLayersDialog		= 'DBLy';	// Send when the layers dialog needs to be dsiplayed.
	const Sint32 kNotifyDataBarChooseClass		= 'DBCC';	// Sent when the selected class in the databar is changed by the user (additionalData is newly selected class sysname)
	const Sint32 kNotifyDataBarChooseLayer		= 'DBCL';	// Sent when the selected layer in the databar is chagned by the user (additionalData is newly selected layer sysname)
	const Sint32 kNotifyDataBarChoosePlane		= 'DBPL';	// Sent when the selected plane in the databar is chagned by the user (additionalData is newly selected planar ref id)
//----------

const Sint32 kNotifyClearOIPControlCache		= 'COIP'; // Send to clear the OIP controller cache.

const Sint32 kNotifyInvalidateSelectionIndication ='InvS';	// Send to get Idle time selection indiation to update the selection indication.
															// Used to service selection invalidation as provided in VW 2008 and prior
															//	Idle time Selection updates are no longer provided for all 
															//	Selection change notifications.  THis notification is here to 
															// provide updates for clients that still require idle time updates.
															//	Call InvalidateCurrentSelectionSelectionIndication or
															//	InvalidateSelectionIndication(const ViewRect& vr) to provide a rect that is 
															//	Not the entire window rect.  In VW 2008 the application invalidated the entire screen
															//	with every kNotifySelChange
															//	

const Sint32 kNotifyApplicationActivate	= 'AppA';	// Send to notify the application has received the focus (additional data = 0)
													// or has lost the focus (additional data = 1)

const Sint32 kNotifyRenderModeAboutToChange	= 'RndC';	// Send immediatelly before a render mode changes. additional adata is the new render mode
const Sint32 kNotifyProjectionAboutToChange	= 'PrjC';	// Send immediatelly before a projection  changes. additional adata is the new projection
const Sint32 kNotifyViewAboutToChange		= 'VATC';	// Send immediatelly before a view        changes. additional adata is the new view if standard

const Sint32 kNotifyCopyOrCut			= 'CyCt';	// Send immediatelly before cutting or copying objects. Additional data: 0 - Copy; 1 - Cut
const Sint32 kNotifyPasteObject			= 'Pste';	// Send immediately after pasting objects. First object passed as additional data, traverse next pasted objects until type=0

const Sint32 kNotifyUndoEndEvent		= 'Udee';	// Send immediatelly before ending an undo event

const Sint32 kNotifyQuickPrefModeBarControlsChange = 'QMBC';   // Sent to rebuild the quick pref modeBar controls.

const Sint32 kNotifyBlackBackgroundChanged		= 'BkgC';	// Send immediatelly when the black background value is changed
const Sint32 kNotifyBlackWhiteOnlyChanged		= 'BWoC';   // Send immediatelly when the black and white only value is changed

const Sint32 kNotifyDocumentUnitsChanged	= 'DcUC';	// Send immediately after the Document Units dialog exits with a change

const Sint32 kNotifyHiddenLineCacheChanged	= 'HLCC';	// Send when some object in Hidden Line Cache jhas changed.  A Re-rennder will be called.

const Sint32 kNotifyProjectSharingOutOfDate     = 'PSup';   // Send when Working File need/not Refresh
const Sint32 kNotifyProjectSharingLayerCheckout = 'PSco';   // Send when NavPal and DataBar need redraw grayed layernames
const Sint32 kNotifyDocReverted                 = 'PSun';   // Send just after a working file is reverted (immediate send)
const Sint32 kNotifyDocPreRefreshed             = 'PSr0';   // Send just before a working file is refreshed (immediate send).
const Sint32 kNotifyDocPostRefreshed            = 'PSr1';   // Send just after a working file is refreshed (immediate send).  Additional data is true if refresh, false if cancel/not done.

const Sint32 kNotifyFindInRsrcManager           = 'FRsM';   // Send after the Find in Resource Manager is pressed on a resource popup.

const Sint32 kNotifyUpdateLibsInRsrcManager     = 'ULRM';   // Send after an update of libraries. Updated libraries tree should be rebuilt in the Resource manager. Info which libs were updated is stored in additional data
const Sint32 kNotifyUpdateLibsStateInRsrcManager     = 'DLRM';   // Send after a change of libraries visibility preferences. Up-to-date state of libs will be checked, libraries tree will be rebuilt in the Resource manager. Info which libs were updated and how they changes their visibility is stored in additional data
const Sint32 kNotifyUpdateOnlineFlagsInRsrcManager     = 'UORM';   // Send after an update download of libraries. Online icons for downloaded files should be removed in the Resource manager.

const Sint32 kNotifyApplicationShutdown			= 'APSD';	// Send when the application is shutting down

const Sint32 kNotifyMultiViewChanged			= 'MVCh';	// Send when multiview state changes
const Sint32 kNotifyMultiViewSelectedPaneChanged	= 'MVCs';	// Send when multiview selected pane changed
const Sint32 kNotifyMultiViewActivePaneChanged = 'MVCa';	// Send when multiview active pane changed

const Sint32 kNotifyMultiViewChangedImmediate				= 'MVIh';	// Send when multiview state changes
const Sint32 kNotifyMultiViewSelectedPaneChangedImmediate	= 'MVIs';	// Send when multiview selected pane changed
const Sint32 kNotifyMultiViewActivePaneChangedImmediate		= 'MVIa';	// Send when multiview active pane changed


const Sint32 kNotifyVisChanged					= 'ViCh';	// Send if any visibility rules changed (FlatScene needs full traversal)
const Sint32 kNotifyPlanRotationChanged			= 'PRot';   // Send if plan rotation state changes
const Sint32 kNotifySelectionUpdate				= 'SeUp';   // Send if selection indication may require resync

const Sint32 kNotifyInvalidateResPreviewWithInfo	= 'RePI';		// use this if you want to invalidate previews of a resource; if you want to change the view of the preview,
																	// std::shared_ptr<SymbolPreviewBuildSettings>* should be provided as data with specified rendering parameters; otherwise set data = 0

const Sint32 kNotifyPlugInUpdate					= 'PlUp';	// Send from plug-in and plug-in needs to process the notification according additionalData

const Sint32 kNotifyLayerActivated					= 'LaAc'; //Send notification of a layer being made the active layer
const Sint32 kNotifyObjAssignLayer					= 'ObLa'; //Send Notification of an object being assigned to a layer

const Sint32 kNotifyClassActivated					= 'ClAc'; //Send notification of a class being made the active class
const Sint32 kNotifyObjAssignClass					= 'ObCl'; //Send Notification of an object being assigned to a class
const Sint32 kNotifyFiltersChanged					= 'FiCh'; //Send notification that the document's filters have changed
const Sint32 kNotifyFilterBookMarkChanged			= 'FbCh'; //Send notification that the documents filter bookmarks have changed
const Sint32 kNotifyRecentlyUsedObjChange			= 'Ruoc'; //Send notification that the recently used objects list was updated
const Sint32 kNotifyAssignTagsToObject				= 'AttO'; //Send notification that tags were assigned (or modified) to an Object
const Sint32 kNotifyModifyDefaultTags				= 'ModT'; //Send notification that the document default tags were modified

const Sint32 kNotifyCompEditPalBegin				= 'CEPB'; //Send notification that the Component Edit Palette needs to open
const Sint32 kNotifyCompEditPalUpdate				= 'CEPU'; //Send notification that the Component Edit Palette needs to update its values
const Sint32 kNotifyCompEditPalEnd					= 'CEPE'; //Send notification that the Component Edit Palette needs to close

const Sint32 kNotifyClassLayerOptionChanged         = 'OPCH'; // Sent when a layer or class option has changed so that Nav Palette can update

const Sint32 kNotifyColorSchemesChanged				= 'CLSC'; // Sent when the AttributesByDataOverrideManager serializes to or from the kColorOverrideDataTag node
const Sint32 kNotifyActiveColorSchemeChange 		= 'ACLS'; // Sent when the Active Color Scheme is changed in the AttributesbyDataOverrideManager

const Sint32 kNotifyDataMappingIsChanged			= 'DMch'; // Sent when Data mapping is changed for an object. That must cause regeneration of data pane in the OIP
const Sint32 kNotifyDialogDisplayImminent			= 'DlgO'; // Sent when a dialog display/"open" operation is in progress.
const Sint32 kNotifyToolModeChanged					= 'TmCh'; // Sent when the current mode tool has changed.
const Sint32 kNotifySmartCursorReset				= 'SCRe'; // Sent when the smart cursor is reset to a default state
const Sint32 kNotifyConstraintStateChanged          = 'CnCh'; // Sent when an interaction constraint mode changes
