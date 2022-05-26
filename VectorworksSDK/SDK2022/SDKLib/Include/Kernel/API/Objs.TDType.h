//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// VectorWorks node types--the TDType constants and the associated property constants.
//
// 

#pragma once

typedef Sint8 TDType;


/****************************************************************************/
/* IMPORTANT:  Be sure to read the notes about adding support for new nodes */
/*  and new node properties that are included above the kMaxNodes #define!  */
/****************************************************************************/


/////////////////////////////////////////////////////////////////////////////////////////
// Property bits; flag properties of Objects.  Keep in Sync with PropertyTypes Type.

const short prOpacity			=16384; // Object can have an opacity assigned to it.
const short prConstrain			= 8192; // Object can have a parametric constraint assigned to it.
const short prVectorFill		= 4096; // Object can be imaged with a vector fill. It can reference a Hatch Definition
const short prSubscribe			= 2048; // Object can be subscribed to
const short prSysNameRefs		= 1024; // Object stores a SysName (besides hatch and class)
const short prHandler			=  512; // Object uses a handler object interface
const short prColor				=  256; // Object has a color
const short prStroke			=  128; // Object has a line style
const short prFill				=	64; // Object has a pattern, gradient or image fill.
const short prDash				=	32; // Object can be dashed
const short pr3D				=	16; // Always has at least some 3D properties
const short pr2D				=	 8; // Always has at least some 2D properties
const short prGroup				=	 4; // Standard firstObject, lastObject structure
const short prBox				=	 2; // Contains a box field
const short prGraphicObject		=	 1; // Has meaningful BlankType fields


/////////////////////////////////////////////////////////////////////////////////////////
// Very special node which serves as a marker for deletion
//
// Currently, this is only used during filing operations to allow a node to be written to
// disk so the list would not be corrupted by its removal, yet still have that node
// deleted the next time the file is read by VectorWorks.
//
// In the future, certain internal algorithms might make use of this tdType as a marker
// with which an object can be tagged for later removal. Be aware that our internal
// object manipulation routines might have to be slightly modified before we can do this.
// Currently (as of VW 8.0.0), the only place it is legal to use this tdType is in the
// filing code.
//
// While there are no assumptions about the size of objects with this type, for
// efficiency's sake they should be the size of NGNodeType. 
//
// PCP 7-14-98

const short kMarkedForRemoval = -128;	const short kMarkedForRemovalProp = 0;


/////////////////////////////////////////////////////////////////////////////////////////
// Node type codes and their properties 

const short kTermNode			= 0;	const short kTermProp			= 0;	// Type is 'TermType'.		
const short kUnusedNode1		= 1;	const short kUnusedNode1Prop	= 0;
const short kLineNode			= 2;	const short kLineProp			= prDash+prGraphicObject+pr2D+prStroke+prColor+prConstrain+prOpacity; // Type is 'SegType'.
const short kBoxNode			= 3;	const short kBoxProp			= prBox+prVectorFill+prDash+prGraphicObject+pr2D+prStroke+prFill+prColor+prConstrain+prHandler+prOpacity;	// Type is 'BoxType'.
const short kOvalNode			= 4;	const short kOvalProp			= prBox+prVectorFill+prDash+prGraphicObject+pr2D+prStroke+prFill+prColor+prConstrain+prHandler+prOpacity;	// Type is 'OvalType'.
const short kPolygonNode		= 5;	const short kPolygonProp		= prBox+prVectorFill+prDash+prGraphicObject+pr2D+prStroke+prFill+prColor+prConstrain+prOpacity;	// Type is 'TDPolyType'.
const short kArcNode			= 6;	const short kArcProp			= prBox+prVectorFill+prDash+prGraphicObject+pr2D+prStroke+prFill+prColor+prConstrain+prOpacity;	// Type is 'ArcType'.
const short kUnusedNode7		= 7;	const short kUnusedNode7Prop	= 0;	// prBox+prGraphicObject+pr2D;	// 3.1 & prior
const short kFreehandPolygonNode= 8;	const short kFreehandPolygonProp= prBox+prVectorFill+prDash+prGraphicObject+pr2D+prStroke+prFill+prColor+prConstrain+prOpacity;	// Type is 'TDPolyType'.
const short kLocus3DNode		= 9;	const short kLocus3DProp		= pr3D+prGraphicObject+prColor; // Type is 'Locus3DType'. 
const short kTextNode			= 10;	const short kTextProp			= prBox+prVectorFill+prGraphicObject+pr2D+prFill+prColor+prConstrain+prOpacity;	// Type is 'TextObjType'.
const short kGroupNode			= 11;	const short kGroupProp			= prBox+prGraphicObject+pr2D+prGroup+prColor+prConstrain+prOpacity;	// Type is 'GroupType'.
const short kQuarterArcNode		= 12;	const short kQuarterArcNodeProp	= 0;	// used to be qArcNode
const short rBoxNode			= 13;	const short kRoundBoxProp		= prBox+prVectorFill+prGraphicObject+pr2D+prDash+prStroke+prFill+prColor+prConstrain+prHandler+prOpacity;	// Type is 'RBoxType'.
const short kPaintNode			= 14;	const short kPaintProp			= prBox+prGraphicObject+pr2D+prFill+prColor+prOpacity+prSubscribe;	// Type is 'PaintType'.
const short kSymbolNode			= 15;	const short kSymbolProp			= prBox+prGraphicObject+prSysNameRefs+prColor+prConstrain+prOpacity;	// Type is 'SymbolType'.
const short kSymDefNode			= 16;	const short kSymbolDefProp		= prBox+prGroup+prSubscribe;	// Type is 'SymDefType'.
const short kLocusNode			= 17;	const short kLocusProp			= prGraphicObject+pr2D+prColor+prConstrain; // Type is 'LocType'.
const short kWorksheetNode		= 18;	const short kWorksheetProp		= 0;	// Type is 'WorksheetType'. Was EstmType
const short kBuildingMaterialNode	= 19;	const short kBuildingMaterialProp = prSubscribe+prSysNameRefs;	// Type is 'BuildingMaterialType'.
const short rot3Node			= 20;	const short rot3Prop			= 0;	//no longer used.  Type is 'Rot3Type' in NETWORK.H
const short kPolylineNode		= 21;	const short kPolylineProp		= prBox+prVectorFill+prDash+prGraphicObject+pr2D+prStroke+prFill+prColor+prConstrain+prOpacity;	// Type is 'PolylineType'.
const short picTDNode			= 22;	const short picTDProp			= prBox+prGraphicObject+pr2D+prFill+prColor+prOpacity;	// Type is 'PicTDType'.
const short kUnusedNode23		= 23;	const short rotProp				= 0;	// prBox+prGroup+prGraphicObject;	// No longer used directly, although it is an abstract base class.  Type is 'RotType'.
const short kExtrudeNode		= 24;	const short kExtrudeProp		= prBox+prGraphicObject+prGroup+pr3D+prStroke+prFill+prColor+prSysNameRefs; // Type is 'Xtrd3Type'.
const short qPolyNode			= 25;	const short qPolyProp			= prBox+prGraphicObject+pr3D+prStroke+prFill+prColor+prSysNameRefs; // Type is 'QPolyType'.
const short kSlabDrainNode			= 26;	const short kSlabDrainProp			= 0;	// Type is 'SlabDrainType'
const short kSlabDrainValleyNode	= 27;	const short kSlabDrainValleyProp	= 0;	// Type is 'SlabDrainValleyType'
const short kSlabSlopeValleyNode	= 28;	const short kSlabSlopeValleyProp	= 0;	// Type is 'SlabSlopeValleyType'
const short kLayerRefNode		= 29;	const short layerRefProp		= prBox+pr3D+prSysNameRefs; // Links to another layer's objects.  Type is 'LayerRefType'.
const short dashPatsNode		= 30;	const short dashPatsProp		= 0;	// Type is 'DashPatsType'.
const short kLayerNode			= 31;	const short layerProp			= prBox+prGroup+prColor+prSubscribe+prSysNameRefs;	// Type is 'LayerType'.
const short kHeaderNode			= 32;	const short kHeaderProp			= prGroup;	// Type is 'HdrRec'.
const short kRefListNode		= 33;	const short refListProp			= 0;	// Type is 'RefNumberTableType'.
const short kSweepNode			= 34;	const short kSweepProp			= prBox+prGraphicObject+prGroup+pr3D+prFill+prStroke+prColor+prSysNameRefs; // Type is 'SweepType'.
const short classListNode		= 35;	const short classListProp		= 0;	// Type is 'ClassListType'.
const short kUnusedNode36		= 36;	const short kUnused36Prop		= 0;	// Never used; was seg3Node
const short kUnusedNode37		= 37;	const short kUnused37Prop		= 0;	// Never used; was poly3Node
const short kMultiExtrudeNode	= 38;	const short kMultiExtrudeProp	= prBox+prGraphicObject+prGroup+pr3D+prFill+prStroke+prColor+prSysNameRefs; // Type is 'Xtrd3Type'.
const short dimStandardNode		= 39;	const short dimStandardProp		= 0;	// Holds an array of DimStandardType.  Type is 'DimArrayType'.
const short kMeshNode			= 40;	const short kMeshProp			= prBox+prGraphicObject+prGroup+pr3D+prFill+prStroke+prColor+prSysNameRefs+prHandler; // Type is 'MeshType'.
const short vRefNode			= 41;	const short vRefProp			= prBox+prGraphicObject+pr3D+prFill+prColor;	// Type is 'VRefType'. Has an array of indices of the vertices of one of the faces of a mesh. MeshType holds the actual vertices.
const short d33Node				= 42;	const short d33Prop				= pr3D; // mesh for storage of extrusions and sweeps.  Type is 'D33Array'.
const short saveViewNode		= 43;	const short saveViewProp		= prSysNameRefs;	// Type is 'ViewType'.
const short kRenderSpecNode		= 44;	const short kRenderSpecProp		= 0;	// Type is 'RenderSpecType'.
const short kEpsNode			= 45;	const short kEpsProp				= 0;	// Type is 'EPSType'.
const short kUnusedNode46		= 46;	const short kUnused46Prop		= 0;	// Obsolete. Type is 'HatchContainerType'.
const short kFormatNode			= 47;	const short formatProp			= prSubscribe+prSysNameRefs;	// Type is 'FormatType'.
const short kRecordNode			= 48;	const short kRecordProp			= prSysNameRefs;	// Type is 'RecordType'.
const short comToolNode			= 49;	const short comToolProp			= 0;	// tool command item.  Type is 'ToolType'.
const short kUnusedNode50		= 50;	const short kUnused50Prop		= 0;	// view command item
const short comPalNode			= 51;	const short comPalProp			= prGroup;	// command palette header.	Type is 'ComPalType'.
const short kUnusedNode52		= 52;	const short kUnused52Prop		= 0;	// obsolete - was worksheetNode from Sint32 ago.
const short kUnusedNode53		= 53;	const short kUnused53Prop		= 0;	// obsolete
const short symListNode			= 54;	const short symListProp			= prGroup;	// Type is 'ContainerType'.
const short refNameNode			= 55;	const short refNameProp			= 0;	// Type is 'RefNameTableType'.
const short kWorksheetImageNode	= 56;	const short kWorksheetImageProp	= prBox+pr2D+prGraphicObject+prStroke+prFill+prColor+prSysNameRefs+prOpacity; // Type is 'WorksheetImageType'.
const short kDataNode			= 57;	const short kDataProp			= prGroup;	// Header for list of data items.  Type is 'ContainerType'.
const short linkNode			= 58;	const short linkProp			= prSysNameRefs;	// Links text in symbol to field in record format.	Type is 'LinkType'.
const short macroNode			= 59;	const short macroProp			= 0;		// node which stores macro data.  Type is 'MacroType'.
const short kWorksheetDatabaseNode= 60;	const short kWorksheetDatabaseProp = 0;		// Worksheet answer node.  Type is 'WorksheetDatabaseType'.
const short indexNode			= 61;	const short indexProp			= 0;		// for quicksorting.  Type is 'WSIndexType'.
const short leaderListNode		= 62;	const short leaderListProp		= 0;		// for holds leaders in worksheet.	Type is 'WSIndexType'.
const short dimHeaderNode		= 63;	const short dimHeaderProp		= prBox+prGraphicObject+prGroup+prDash+pr2D+prColor+prStroke+prFill+prConstrain+prOpacity;	// Type is 'DimHeaderType'.
const short stringTDNode		= 64;	const short stringTDProp		= 0;		// StringTD type for copying/cutting of mNames.	 Type is 'StringTD'.
const short kHatchContainerNode	= 65;	const short kHatchContainerProp	= prGroup;	// Type is obsolete.
const short kHatchDefNode		= 66;	const short kHatchDefProp		= prSubscribe;	// Type is 'HatchDefNodeType'.
const short kBspNode			= 67;	const short bspProp				= prBox+prGraphicObject+prFill+prOpacity;	//Warning, not always in tdlist format, spends part of its life in bsp list format.	 Type is 'BSPType'.
const short kWallNode			= 68;	const short kWallProp			= prBox+prVectorFill+prGraphicObject+prDash+prGroup+pr2D+pr3D+prStroke+prFill+prColor+prSysNameRefs+prConstrain+prOpacity;	// Type is 'WallType'.
const short kInnerLinesNode		= 69;	const short kInnerLinesProp		= 0;	// Type is 'InnerLinesType'.
const short kSlabDrainageSettingsNode	= 70;	const short kSlabDrainageSettingsProp	= 0;	// Type is 'SlabDrainageSettingsType'
const short kSlabNode			= 71;	const short kSlabProp			= prBox+prGraphicObject+prGroup+pr3D+pr2D+prStroke+prFill+prColor+prSysNameRefs+prOpacity;	// Type is 'SlabType'.
const short lineColNode			= 72;	const short lineColProp			= 0;	// Type is 'LineColType'.
const short kPenSpaceNode		= 73;	const short kPenSpaceProp		= 0;	// Type is 'PenSpaceType'.
const short fontTableNode		= 74;	const short fontTableProp		= 0;	// This is to create a font lookup table.  Type is 'FontTableType'.
const short styleRunNode		= 75;	const short styleRunProp		= 0;	// Obsolete. Type was 'StyleRunType'.
const short kUserDataNode		= 76;	const short userDataProp		= 0;	// Type is 'UserDataType'.
const short kWorkingPlaneNode	= 77;	const short workingPlaneProp	= 0;	// Type is 'WorkingPlaneType'.
const short kWPlaneListNode		= 78;	const short wpListProp			= prGroup;	// Header for list of working planes. Type is 'ContainerType'.
const short pixPatListNode		= 79;	const short pixPatListProp		= 0;	// Used to store editable pattern definitions; type is PixPatListType.
const short kColorPaletteNode	= 80;	const short kColorPaletteProp	= 0;	// For drawing's color palette. Type is 'ColorPaletteNGNode'.
const short kLightNode			= 81;	const short kLightProp			= prBox+prGraphicObject+pr3D+prColor; // Type is 'LightType'.
const short kRoofEdgeNode		= 82;	const short kRoofEdgeProp		= prBox+prGraphicObject+pr2D+pr3D+prDash+prStroke+prFill+prColor+prHandler+prOpacity;	// Type is 'TRoofEdgeType'.
const short kRoofContainerNode	= 83;	const short kRoofContainerProp	= prBox+prGraphicObject+pr2D+pr3D+prDash+prStroke+prFill+prColor+prGroup+prSysNameRefs+prHandler+prOpacity;	// Type is 'RoofContainerType'.
const short kCSGTreeNode		= 84;	const short kCSGTreeProp		= prBox+prGraphicObject+pr3D+prGroup+prSysNameRefs+prHandler+prColor+prFill+prStroke;	// Type is 'CSGTreeType'.
const short kBoundaryRepNode	= 85;	const short kBoundaryRepProp	= prBox+prGraphicObject+pr3D+prHandler;	// Type is 'BoundaryRepType'.
const short kParametricNode		= 86;	const short kParametricProp		= prBox+prGraphicObject+pr2D+pr3D+prDash+prGroup+prSysNameRefs+prHandler+prStroke+prFill+prVectorFill+prColor+prConstrain+prSubscribe+prOpacity;	// Type is 'ParametricType'.
const short kRoofAdornerNode	= 87;	const short kRoofAdornerProp	= pr3D+pr2D+prHandler;	// Type is 'TRoofAdornerArray'.
const short kSubscribeNode		= 88;	const short kSubscribeProp		= 0;	// Type is 'SubscribeType'
const short kObsoleteRoundWallNode	= 89;	const short kObsoleteRoundWallProp	= prBox+prVectorFill+prGraphicObject+prDash+prGroup+pr2D+pr3D+prStroke+prFill+prColor+prSysNameRefs+prConstrain+prOpacity;	// Obsolete - Was kRoundWallNode - This is only used for file translation. Filetran needs some of the old properties.
const short kUndoPlaceholderNode= 90;	const short kUndoPlaceholderProp= 0;	// Type is 'UndoPlaceholderType'
const short kTextureSpaceNode	= 91;	const short kTextureSpaceProp	= 0;	// Type is 'TextureSpaceType'
const short kFolderNode			= 92;	const short kFolderProp	= prGroup;	// Type is 'ResourceFolderType', used to be ContainerType
const short kTextureBitmapNode	= 93;	const short kTextureBitmapProp	= 0;	// Type is TextureBitmapType
const short kClassDefNode		= 94;	const short kClassDefProp		= prSysNameRefs;	// Type is ClassDefType
const short kSolidNode			= 95;	const short kSolidProp			= prBox+prGraphicObject+pr3D+prSysNameRefs+prHandler+prColor+prStroke+prFill;	// Type is SolidType
const short kLineTypeDefNode	= 96;	const short kLineTypeProp		= prSubscribe;	// Type is 'LineTypeDefNodeType'.
const short kTextureNode		= 97;	const short kTextureProp		= prSubscribe;	// Type is 'TextureType'; tdTYpe used to be kMaterialNode [9/11/2020]
const short kADSymDefHandlerNode= 98;	const short kADSymDefHandlerProp= 0;	// Type is ADSymDefHandlerType - temporary object used in dxf import [JDW, 6/16/98]
const short kADSymbolHandlerNode= 99;	const short kADSymbolHandlerProp= 0;	// Type is ADSymbolHandlerType - temporary object used in dxf import [JDW, 6/16/98]
const short kSlabEdgeNode		= 100;	const short kSlabEdgeProp	= 0;	// Type is 'SlabEdgeType'
const short kDropShadowNode		= 101;	const short kDropShadowProp	= 0;	// Type is 'DropShadowType'
const short kRoofStyleNode			= 102; 	const short kRoofStyleProp			= prSubscribe+prSysNameRefs;  // Type is 'RoofStyleNodeType'
const short kCurtainWallFrameNode	= 103;	const short kCurtainWallFrameProp	= 0;	// Type is 'CurtainWallFrameType'
const short kCurtainWallPanelNode	= 104;	const short kCurtainWallPanelProp	= 0;	// Type is 'CurtainWallPanelType'
const short kCurtainWallGridNode	= 105;	const short kCurtainWallGridProp	= 0;	// Type is 'CurtainWallGridType'
const short kRenderStyleNode	= 106; 	const short kRenderStyleProp	= prSubscribe;	// Type is 'RenderStyleType'.
const short kSlabStyleNode		= 107;	const short kSlabStyleProp		= prSubscribe+prSysNameRefs;  // Type is 'SlabStyleNodeType'
const short kTileDefNode		= 108; 	const short kTileProp			= prSubscribe;	// Type is 'TileDefNodeType'.
const short kTextStyleNode      = 109;	const short kTextStyleProp      = prSubscribe;	// Type is 'TextStyleNodeType'.  Was kPlugInObject10Node, which went unused.
const short kConstraintNode		= 110;	const short kConstraintProp		= prSysNameRefs;	// Type is 'ConstraintType'
const short kPieceWiseNurbsCurveNode= 111;	const short kPieceWiseNurbsCurveProp= prBox+prGraphicObject+pr3D+prHandler+prColor+prStroke;	// Type is 'PieceWiseNurbsCurveType'.
const short kCorePrintInfoNode		= 112;	const short kCorePrintInfoProp		= 0;		// Type is 'CorePrintInfoType'
const short kNurbsSurfaceNode		= 113;	const short kNurbsSurfaceProp		= prBox+prGraphicObject+pr3D+prSysNameRefs+prHandler+prColor+prFill+prStroke;	// Type is 'NurbsSurfaceType'
const short kCompositeSurfaceNode	= 114;  const short kCompositeSurfaceProp	= pr3D+prHandler;	// Type is 'CompositeSurfaceType'. This object goes in the aux fields of things like CSGTreeNode and gets displayed using the parent node's graphic attributes.
const short kRenderBackgroundNode	= 115;	const short kRenderBackgroundProp	= prSubscribe;	// Type is 'RenderBackgroundType'
const short kPolyBreakNode			= 116;	const short kPolyBreakProp			= 0; // Type is 'PolyBreakType'.
const short kBatchRenderJobNode		= 117;	const short kBatchRenderJobProp		= 0; // Type is 'BatchRenderJobType' 
const short kBatchRenderJobListNode	= 118;	const short kBatchRenderJobListProp	= prGroup;	// Type is 'ContainerType'
const short kImageDefNode			= 119; 	const short kImageProp				= prSubscribe;	// Type is 'ImageDefNodeType'. 
const short kGradientDefNode		= 120; 	const short kGradientProp			= prSubscribe;	// Type is 'GradientDefNodeType'.
const short kFillSpaceNode			= 121;	const short kFillSpaceProp			= 0;			// Type is 'FillSpaceType'
const short kViewportNode			= 122;	const short kViewportProp			= prBox+prVectorFill+prGraphicObject+pr2D+prColor+prFill+prConstrain+prHandler+prSysNameRefs;	// Type is 'ViewportType'.
const short kArtRWStyleNode			= 123;	const short kArtRWStyleProp			= 0;	// Type is 'ArtRWStyleType'
const short	kAssociationNode		= 124;  const short kAssociationProp		= prSysNameRefs;	// Type is 'AssociationType'
const short kAuxMarkerNode			= 125;  const short kAuxMarkerProp			= 0;	// Type is 'AuxMarkerType'
const short kGeoReferenceNode 		= 126;  const short kGeoReferenceProp		= prSysNameRefs;	// Type is 'GeoReferenceType'
const short kWallStyleNode			= 127; 	const short kWallStyleProp			= prSubscribe+prSysNameRefs;  // Type is 'WallStyleNodeType'


/////////////////////////////////////////////////////////////////////////////////////////
// When you change maxTDTypeNodes, a number of files will not compile until you add support for
// the new TDType.	Do not put off adding proper support, do it now.
//
// You will need to modify these files:
//	CheckObject.cpp
//	Export.AD.Entities.cpp
//	MemoryMaintenance.cpp
//	NewTD.cpp
//	SParser.cpp
//
// If you add a field containing a SysName to a node type, you must add the prSysNameRefs
// property to the TDType properties constant (if not already present).  If the type has
// the prHandler property, you must implement (or add support for the new field to) the
// following methods in its TGraphicObjectHandler-derived class:
//
//	ModifiedSysName
//	DeletedSysName
//	AddSysNamesToML
//	MapSysNames
//
// If the type does not have the prHandler property, you must add support for the added
// SysName-containing field to the following routines:
//
//	PushRelatedItems (in UMapList.cpp)
//	TMapList::MatchEntity (in UMapList.cpp)
//	InnerClean (used by FreeRef in MObject.Lists.cpp)
//	DoInvalRef (used by InvalRef in MObject.Lists.cpp)
//	FlagUsedRsrcs (in Subscriptions.cpp)
//
// If a SysName reference contains the SysName of a drawing object, special additional
// handling is required in the Duplicate/CopyNode code.  See Mike Hartman, or whoever
// is maintaining the UMapList code. 
//
// If you are saving your object to disk, you need to change kCurrentFileVersion in 
// FileVersionInfo.h and add a comment there. Changing the version will make existing
// files unusable so check with others before doing so.
//
// NOTE: Max nodes can never go above 127 because tdType is an Sint8, if you need to add a new type find an
// unused one in the list above and claim it.  SlabStyle and RenderStyle claimed the reserved and never used plugin object IDs, for example.  -DLD 1/18/2011


// This is a #define because it is checked by the preprocessor

#define maxTDTypeNodes	127
const short kMaxNodes  = maxTDTypeNodes;


/////////////////////////////////////////////////////////////////////////////////////////
// The following macro allows you to conveniently check for legal TDTypes at the
// beginning of your functions.

#define ASSERTLEGALTYPE(toWhom, type) \
			DSTOPIF((type)!=kMarkedForRemoval && ((type)<0 || (type)>maxTDTypeNodes), (toWhom,\
				  "Illegal tdType (%d) encountered! Legal range: [0, %d]", type, maxTDTypeNodes));


/////////////////////////////////////////////////////////////////////////////////////////
//
// Objects subtype constants - Use to get the localized subtype names. Also use by the parser to get the subtype criteria strings
// HOT 03/15/06
// Maintained in sync with STR#4505

const short kDirLightSubT		= 500;
const short kSpotLightSubT		= 501;
const short	kPointLightSubT		= 502;
const short kCustLightSubT		= 503;
const short kAreaLightSubT		= 504;
const short kLineLightSubT		= 505;
const short kRegViewportSubT	= 506;
const short kSectViewportSubT	= 507;
const short kFloorSubT			= 508;
const short kRoofSubT			= 509;
const short kPillarSubT			= 510;
const short	kConeSubT			= 511;
const short	kSphereSubT			= 512;
const short kHemisphereSubT		= 513;
const short kCircleSubT			= 514;	
const short kOpenedArcSubT		= 515;
const short kCSGSubtractSubT	= 516;
const short kCSGAdditionSubT	= 517;
const short kCSGIntersectionSubT	= 518;
const short	kCSGSectionSubT		= 519;
const short kCSGShellSubT		= 520;
const short kCSGChamferSubT		= 521;
const short kCSGFilletSubT		= 522;
const short kNURBSsurfCtrlPtSubT	= 523;
const short kNURBSsurfInterpSubT	= 524;

// Init the first and last subtype constants
const short kFirstSubType = kDirLightSubT ;
const short kLastSubType = kNURBSsurfInterpSubT;

/////////////////////////////////////////////////////////////////////////////////////////
// OBSOLETE NAMES - left here for people searching for a name. Also search for 
// the string 'Object type codes' without the quotes in MiniCadCallBacks.h
// XXX_JDW_MISC - for VW9 this file should be included in the SDK and the defines should be replaced by 
// these constants

// XXX_JDW_ALTURA CLEANUP [2003-08-23]
#if 1 //GS_SDK_VW8_COMPATIBLE 

#if defined(_MINICAD_)
// These are required only in the main application
const short bspNode					= kBspNode;
const short comListNode				= kUnusedNode53;
const short d3Node					= kLocus3DNode;
const short dNode					= kWorksheetDatabaseNode;
const short estmDumNode				= kWorksheetImageNode;
const short estmNode				= kWorksheetNode;	// NOTE: this is not the same as the old worksheetNode constant!
const short hatchListNode			= kUnusedNode46;
const short innerLinesNode			= kInnerLinesNode;
const short kCurveNode				= kFreehandPolygonNode;
const short kPolyNode				= kPolygonNode;
const short kSymNode				= kSymbolNode;
const short kWpListNode				= kWPlaneListNode;
const short lineListNode			= kPenSpaceNode;
const short locNode					= kLocusNode;
const short oldDimNode				= kUnusedNode7;
const short oldGrpTrmNode			= kUnusedNode1;
const short refListNode				= kRefListNode;
const short segNode					= kLineNode;
const short workingPlaneNode		= kWorkingPlaneNode;
const short wpListNode				= kWPlaneListNode;
const short renderSpecNode			= kRenderSpecNode;
const short epsNode					= kEpsNode;
const short headerNode				= kHeaderNode;
#endif


// These are required in both the main application and the plug-ins
const short termNode				= kTermNode;
const short boxNode					= kBoxNode;			// (should probably be kRectangleNode)
const short arcNode					= kArcNode;
const short polyNode				= kPolygonNode;
const short ovalNode				= kOvalNode;		// (should probably be kEllipseNode; SteveJ tells me we treat them as ellipses for everything but drawing...)
const short curveNode				= kFreehandPolygonNode;
const short textNode				= kTextNode;
const short groupNode				= kGroupNode;
const short paintNode				= kPaintNode;
const short symNode					= kSymbolNode;
const short symDefNode				= kSymDefNode;
const short buildingMaterialNode	= kBuildingMaterialNode;
const short polylineNode			= kPolylineNode;
const short mxtrdNode				= kMultiExtrudeNode;
const short xtrdNode				= kExtrudeNode;
const short layerNode				= kLayerNode;
const short layerRefNode			= kLayerRefNode;
const short sweepNode				= kSweepNode;
const short meshNode				= kMeshNode;
const short formatNode				= kFormatNode;
const short recordNode				= kRecordNode;
const short hatchDefNode			= kHatchDefNode;
const short hatchContainerNode		= kHatchContainerNode;
const short dataNode				= kDataNode;
const short wallNode				= kWallNode;
const short slabNode				= kSlabNode;
const short userDataNode			= kUserDataNode;
const short wallStyleNode			= kWallStyleNode;
const short slabStyleNode			= kSlabStyleNode;
const short roofStyleNode			= kRoofStyleNode;
const short textStyleNode			= kTextStyleNode;


#if !defined(_MINICAD_)
// These were defined differently for the SDK through VW8.x.x,
// so we'll allow them for compatibility

const short lineNode				= kLineNode;
const short loc3DNode				= kLocus3DNode;
const short worksheetNode			= kWorksheetNode;
const short worksheetDummyNode		= kWorksheetImageNode;
const short cavityNode				= kInnerLinesNode;
#endif

#endif // GS_SDK_VW8_COMPATIBLE



//////////////////////////////////////////////////////////////////////////////////////////
// ProjectionType

//--------------------------------------------------------------------
#pragma pack(push, 2) // BEGIN 2 BYTE STRUCTURE ALIGNMENT (.vwx file format)

struct ProjectionType {
	const TransformMatrix&  ScreenMatrix() const { return screenMatrix; }
	short RenderMode() const { return render; }
	short Projection() const { return projection; }

	void SetTransformMatrix(const TransformMatrix&  matrix)
		{ screenMatrix = matrix; }
	void SetRenderMode(short newMode) { render = newMode; }
	void SetProjection(short newProjection) { projection = newProjection; }

	ProjectionType& operator=(const ProjectionType& inProj)	{ memcpy(this, &inProj, sizeof(ProjectionType)); return *this; }

	int Compare(const ProjectionType& inRight, bool inbIncludeRenderMode) const
	// Returns
	//  1	- we are greater than inRight
	//  0	- we are equal to inRight
	// -1	- we are less than inRight
	{
		int outResult = 1;

		int matResult = screenMatrix.Compare(inRight.screenMatrix);

		if (matResult != 0)
			outResult = matResult;
		else {

			if (projection < inRight.projection)
				outResult = -1;
			else if (projection == inRight.projection) {

				if (clipDistance < inRight.clipDistance)
					outResult = -1;
				else if (clipDistance == inRight.clipDistance) {

					if (crsPersDistance < inRight.crsPersDistance)
						outResult = -1;
					else if (crsPersDistance == inRight.crsPersDistance) {
						int clipResult = projClipRect.Compare(inRight.projClipRect);

						if ( ! inbIncludeRenderMode)
							outResult = clipResult;
						else {

							if (clipResult != 0)
								outResult = clipResult;
							else {

								if (render < inRight.render)
									outResult = -1;
								else if (render == inRight.render)
									outResult = 0;
							}
						}
					}
				}
			}
		}

		return outResult;
	}

	TransformMatrix			screenMatrix;
	short					projection;
	short					render;
	WorldCoord				crsPersDistance;
	WorldCoord				clipDistance;
	WorldRect				projClipRect;
	
	void ByteSwap();
	/**
		Translates old Lightworks modes of rendering to the new Maxon modes of rendering.
	 
		@created Lyndsey Ferguson
		@date 04/23/2010
	*/
	void TranslateToRenderModeVW2011();
};
#pragma pack(pop)	// END 2 BYTE STUCTURE AIGNMENT <.vwx file format>

//////////////////////////////////////////////////////////////////////////////////////////

enum class ELevelsOfDetail {
	NotSet = 0,
	Low = 1,
	Medium = 2,
	High = 4,
	All = 7
};

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

};
