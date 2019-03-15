//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//  Created by Lyndsey Ferguson on 6/28/13.
//
//

#pragma once

#include "Interfaces/VectorWorks/ISDK.h"

namespace MockUp
{
	// ------------------------------------------------------------------------------------------------------------
	typedef Sint32 (*ToolDefProcPtr)(ToolMessage* message, void*& localData, CallBackPtr defData);
	typedef TXString TXStringMock;

	using namespace VectorWorks;

	class MockSDK : public VCOMImmediateImpl<ISDK>
	{
	public:
		MockSDK();
		virtual ~MockSDK();

		//  pre VW2009
	public:
		virtual Boolean VCOM_CALLTYPE GetClassBeginningMarker(InternalIndex index, SMarkerStyle& mstyle);
		virtual Boolean VCOM_CALLTYPE GetClassEndMarker(InternalIndex index, SMarkerStyle& mstyle);
		virtual void VCOM_CALLTYPE GetClColor(InternalIndex index, ObjectColorType& color);
		virtual InternalIndex VCOM_CALLTYPE GetClFillPat(InternalIndex index);
		virtual short VCOM_CALLTYPE GetClLineWeight(InternalIndex index);
		virtual void VCOM_CALLTYPE GetClMarker(InternalIndex index, MarkerType& style, short& size, short& angle);
		virtual Boolean VCOM_CALLTYPE GetClUseGraphic(InternalIndex index);
		virtual short VCOM_CALLTYPE GetClVisibility(InternalIndex index);
		virtual InternalIndex VCOM_CALLTYPE GetVPClassFillStyle(MCObjectHandle viewport, InternalIndex classIndex);
		virtual Boolean VCOM_CALLTYPE SetClassBeginningMarker(InternalIndex index, SMarkerStyle mstyle);
		virtual Boolean VCOM_CALLTYPE SetClassEndMarker(InternalIndex index, SMarkerStyle mstyle);
		virtual void VCOM_CALLTYPE SetClColor(InternalIndex index, ObjectColorType color);
		virtual void VCOM_CALLTYPE SetClFillPat(InternalIndex index, InternalIndex fill);
		virtual void VCOM_CALLTYPE SetClLineWeight(InternalIndex index, short mils);
		virtual void VCOM_CALLTYPE SetClMarker(InternalIndex index, MarkerType style, short size, short angle);
		virtual void VCOM_CALLTYPE SetClUseGraphic(InternalIndex index, Boolean use);
		virtual void VCOM_CALLTYPE SetClVisibility(InternalIndex index, short vis);
		virtual Boolean VCOM_CALLTYPE VPClassHasOverride(MCObjectHandle viewport, InternalIndex classIndex);
		virtual Boolean VCOM_CALLTYPE DeleteAllDLComponents();
		virtual Boolean VCOM_CALLTYPE DeleteDLComponent(Sint16 index);
		virtual Boolean VCOM_CALLTYPE GetDefaultArrowByClass();
		virtual void VCOM_CALLTYPE GetDefaultArrowHeads(Boolean& starting, Boolean& ending, ArrowType& style, short& size);
		virtual void VCOM_CALLTYPE GetDefaultArrowHeadsN(Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size);
		virtual Boolean VCOM_CALLTYPE GetDefaultBeginningMarker(SMarkerStyle& mstyle, Boolean& visibility);
		virtual InternalIndex VCOM_CALLTYPE GetDefaultClass();
		virtual void VCOM_CALLTYPE GetDefaultColors(ObjectColorType& colors);
		virtual Boolean VCOM_CALLTYPE GetDefaultEndMarker(SMarkerStyle& mstyle, Boolean& visibility);
		virtual Boolean VCOM_CALLTYPE GetDefaultFColorsByClass();
		virtual InternalIndex VCOM_CALLTYPE GetDefaultFillPat();
		virtual Boolean VCOM_CALLTYPE GetDefaultFPatByClass();
		virtual MCObjectHandle VCOM_CALLTYPE GetDefaultHatch();
		virtual short VCOM_CALLTYPE GetDefaultLineWeight();
		virtual Boolean VCOM_CALLTYPE GetDefaultLWByClass();
		virtual Boolean VCOM_CALLTYPE GetDefaultPColorsByClass();
		virtual Boolean VCOM_CALLTYPE GetDefaultPPatByClass();
		virtual Boolean VCOM_CALLTYPE GetDLComponentClass(Sint16 index, Sint32 &componentClass);
		virtual Boolean VCOM_CALLTYPE GetDLComponentFill(Sint16 index, Sint32 &fill);
		virtual Boolean VCOM_CALLTYPE GetDLComponentFillColors(Sint16 index, ColorRef &fillForeColor, ColorRef &fillBackColor);
		virtual Boolean VCOM_CALLTYPE GetDLComponentName(Sint16 index, TXString& outComponentName);
		virtual Boolean VCOM_CALLTYPE GetDLComponentPenColors(Sint16 index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor);
		virtual Boolean VCOM_CALLTYPE GetDLComponentPenWeights(Sint16 index, Uint8 &penWeightLeft, Uint8 &penWeightRight);
		virtual Boolean VCOM_CALLTYPE GetDLComponentUseFillClassAttr(Sint16 index, Boolean &useClassAttr);
		virtual Boolean VCOM_CALLTYPE GetDLComponentUsePenClassAttr(Sint16 index, Boolean &leftPenUseClassAttr, Boolean &rightPenUseClassAttr);
		virtual Boolean VCOM_CALLTYPE GetDLComponentWidth(Sint16 index, WorldCoord &width);
		virtual WorldCoord VCOM_CALLTYPE GetDLControlOffset();
		virtual Sint16 VCOM_CALLTYPE GetDLOptions();
		virtual WorldCoord VCOM_CALLTYPE GetDLSeparation();
		virtual InternalIndex VCOM_CALLTYPE GetDocumentDefaultSketchStyle();
		virtual Boolean VCOM_CALLTYPE GetNumberOfDLComponents(short& numComponents);
		virtual InternalIndex VCOM_CALLTYPE GetObjectInternalIndex(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE GetProgramVariable(short variableSelector, void* result);
		virtual Boolean VCOM_CALLTYPE GetWallPrefStyle(InternalIndex& wallStyleNum);
		virtual Boolean VCOM_CALLTYPE GetWallStyle(MCObjectHandle theWall, InternalIndex& wallStyle);
		virtual void VCOM_CALLTYPE SetDefaultArrowByClass();
		virtual void VCOM_CALLTYPE SetDefaultArrowHeads(Boolean starting, Boolean ending, ArrowType style, short size);
		virtual void VCOM_CALLTYPE SetDefaultArrowHeadsN(Boolean starting, Boolean ending, ArrowType style, double_param size);
		virtual Boolean VCOM_CALLTYPE SetDefaultBeginningMarker(SMarkerStyle mstyle, Boolean visibility);
		virtual void VCOM_CALLTYPE SetDefaultClass(InternalIndex classID);
		virtual void VCOM_CALLTYPE SetDefaultColors(ObjectColorType colors);
		virtual Boolean VCOM_CALLTYPE SetDefaultEndMarker(SMarkerStyle mstyle, Boolean visibility);
		virtual void VCOM_CALLTYPE SetDefaultFColorsByClass();
		virtual void VCOM_CALLTYPE SetDefaultFillPat(InternalIndex theFill);
		virtual void VCOM_CALLTYPE SetDefaultFPatByClass();
		virtual Boolean VCOM_CALLTYPE SetDefaultHatch(MCObjectHandle inHatchDef);
		virtual void VCOM_CALLTYPE SetDefaultLineWeight(short mils);
		virtual void VCOM_CALLTYPE SetDefaultLWByClass();
		virtual void VCOM_CALLTYPE SetDefaultPColorsByClass();
		virtual void VCOM_CALLTYPE SetDefaultPPatByClass();
		virtual void VCOM_CALLTYPE SetDefaultWallThickness(WorldCoord thickness);
		virtual Boolean VCOM_CALLTYPE SetDLComponentClass(Sint16 index, Sint32 componentClass);
		virtual Boolean VCOM_CALLTYPE SetDLComponentFill(Sint16 index, Sint32 fill);
		virtual Boolean VCOM_CALLTYPE SetDLComponentFillColors(Sint16 index, ColorRef fillForeColor, ColorRef fillBackColor);
		virtual Boolean VCOM_CALLTYPE SetDLComponentName(Sint16 index, const TXString& componentName);
		virtual Boolean VCOM_CALLTYPE SetDLComponentPenColors(Sint16 index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor);
		virtual Boolean VCOM_CALLTYPE SetDLComponentPenWeights(Sint16 index, Uint8 penWeightLeft, Uint8 penWeightRight);
		virtual Boolean VCOM_CALLTYPE SetDLComponentUseFillClassAttr(Sint16 index, Boolean useClassAttr);
		virtual Boolean VCOM_CALLTYPE SetDLComponentUsePenClassAttr(Sint16 index, Boolean leftPenUseClassAttr, Boolean rightPenUseClassAttr);
		virtual Boolean VCOM_CALLTYPE SetDLComponentWidth(Sint16 index, WorldCoord width);
		virtual void VCOM_CALLTYPE SetDLControlOffset(WorldCoord controlOffset);
		virtual void VCOM_CALLTYPE SetDLOptions(Sint16 options);
		virtual void VCOM_CALLTYPE SetDLSeparation(WorldCoord separation);
		virtual Boolean VCOM_CALLTYPE SetDocumentDefaultSketchStyle(InternalIndex sketchIndex);
		virtual Boolean VCOM_CALLTYPE SetProgramVariable(short variableSelector, const void* value);
		virtual Boolean VCOM_CALLTYPE SetWallPrefStyle(InternalIndex wallStyleNum);
		virtual void VCOM_CALLTYPE WrapGetDefaultWallThickness(double_gs& outCoordLen);
		virtual void VCOM_CALLTYPE Add3DVertex(MCObjectHandle h, const WorldPt3& v, Boolean recalcBounds = true);
		virtual void VCOM_CALLTYPE AddVertex(MCObjectHandle h, const WorldPt& p, VertexType t = vtCorner, WorldCoord arcRadius = 1.0, Boolean recalcBounds = true);
		virtual void VCOM_CALLTYPE CalcAreaN(MCObjectHandle h, double_gs& area);
		virtual void VCOM_CALLTYPE CalcPerimN(MCObjectHandle h, double_gs& perim);
		virtual double_gs VCOM_CALLTYPE CalcSurfaceArea(MCObjectHandle h);
		virtual double_gs VCOM_CALLTYPE CalcVolume(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE Centroid3D(MCObjectHandle h, double_gs &xCG, double_gs &yCG, double_gs &zCG);
		virtual short VCOM_CALLTYPE CountVertices(MCObjectHandle h);
		virtual short VCOM_CALLTYPE CreateSkylight(MCObjectHandle object);
		virtual void VCOM_CALLTYPE DeleteVertex(MCObjectHandle h, short vertexNum);
		virtual void VCOM_CALLTYPE ForEach3DPointInObject(MCObjectHandle h, GS_3DPointIteratorProcPtr proc, void* env);
		virtual void VCOM_CALLTYPE ForEachPolyEdge( MCObjectHandle inPolyH, GS_ForEachPolyEdgeProcPtr inProc, void* inEnv);
		virtual void VCOM_CALLTYPE Get3DVertex(MCObjectHandle h, short vertexNum, WorldPt3& vertex);
		virtual void VCOM_CALLTYPE GetArcInfoN(MCObjectHandle h, double_gs& startAngle, double_gs& sweepAngle, WorldPt& center, WorldCoord& radiusX, WorldCoord& radiusY);
		virtual Boolean VCOM_CALLTYPE GetBatAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, WorldCoord& topWidth, WorldCoord& baseHeight, double_gs& topSlope, WorldCoord& controlPoint);
		virtual void VCOM_CALLTYPE GetControlVertex(MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius);
		virtual Boolean VCOM_CALLTYPE GetDormerAttributes(MCObjectHandle object, const short dormerID, short& edgeIndex, WorldCoord& cornerOffset, Boolean& isPerpOffset, WorldCoord& perpOrHeightOffset, InternalIndex& symName, Boolean& centerSymbol, WorldCoord& symOffset);
		virtual void VCOM_CALLTYPE GetEndPoints(MCObjectHandle h, WorldPt& startPt, WorldPt& endPt);
		virtual void VCOM_CALLTYPE GetEntityMatrix(MCObjectHandle h, TransformMatrix& theMat);
		virtual void VCOM_CALLTYPE GetExtrudeValues(MCObjectHandle h, WorldCoord& bottom, WorldCoord& top);
		virtual Boolean VCOM_CALLTYPE GetGableAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, WorldCoord& overhang);
		virtual Boolean VCOM_CALLTYPE GetHipAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& frontSlope, WorldCoord& overhang);
		virtual void VCOM_CALLTYPE GetLocus3DPosition(MCObjectHandle h, WorldPt3& locPos);
		virtual void VCOM_CALLTYPE GetLocusPosition(MCObjectHandle h, WorldPt& locPos);
		virtual void VCOM_CALLTYPE GetMarkerPolys(MCObjectHandle object, MCObjectHandle& startMarkerPoly, MCObjectHandle& endMarkerPoly);
		virtual short VCOM_CALLTYPE GetNumRoofElements(MCObjectHandle object);
		virtual Boolean VCOM_CALLTYPE GetObjectBoundingBoxVerts(MCObjectHandle h, WorldRectVerts &outBoxVerts);
		virtual Boolean VCOM_CALLTYPE GetObjectBounds(MCObjectHandle h, WorldRect& bounds);
		virtual void VCOM_CALLTYPE GetObjectCube(MCObjectHandle h, WorldCube& boundsCube);
		virtual short VCOM_CALLTYPE GetPolyDirection(MCObjectHandle polyToCheck);
		virtual Boolean VCOM_CALLTYPE GetPolyShapeClose(MCObjectHandle h);
		virtual short VCOM_CALLTYPE GetQArcQuadrant(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE GetRoofAttributes(MCObjectHandle object, Boolean& genGableWall, WorldCoord& bearingInset, WorldCoord& roofThick, short& miterType, WorldCoord& vertMiter);
		virtual Boolean VCOM_CALLTYPE GetRoofElementType(MCObjectHandle object, const short dormerID, short& edgeIndex, Boolean& isDormer, short& dormerType);
		virtual void VCOM_CALLTYPE GetRRectDiameters(MCObjectHandle h, WorldCoord& xDiam, WorldCoord& yDiam);
		virtual Boolean VCOM_CALLTYPE GetShedAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& topSlope, WorldCoord& overhang);
		virtual Boolean VCOM_CALLTYPE GetSkylight(MCObjectHandle object, const short skylightID, short& edgeIndex, WorldCoord& cornerOffset, WorldCoord& perpOffset, InternalIndex& symName);
		virtual void VCOM_CALLTYPE GetSweepAnglesN(MCObjectHandle theSweep, double_gs& startAngle, double_gs& arcAngle, double_gs& incrAngle);
		virtual Boolean VCOM_CALLTYPE GetTrapeziumAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, Boolean& useTopWidth, WorldCoord& topWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& topSlope);
		virtual void VCOM_CALLTYPE GetVertex(MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius);
		virtual void VCOM_CALLTYPE Insert3DVertex(MCObjectHandle h, const WorldPt3& p, short beforeVertex, Boolean recalcBounds = true);
		virtual void VCOM_CALLTYPE InsertVertex(MCObjectHandle h, const WorldPt& p, short beforeVertex, VertexType t = vtCorner, WorldCoord arcRadius = 1.0, Boolean recalcBounds = true);
		virtual Boolean VCOM_CALLTYPE Moments3D(MCObjectHandle h, double_gs &Ixx, double_gs &Iyy, double_gs &Izz);
		virtual Boolean VCOM_CALLTYPE NurbsCurveEvaluatePoint(MCObjectHandle nurbsHandle, Sint32 index, double u, WorldPt3& pt);
		virtual Sint32 VCOM_CALLTYPE NurbsCurveGetNumPieces(MCObjectHandle nHandle);
		virtual Boolean VCOM_CALLTYPE NurbsCurveType(MCObjectHandle nHandle, Sint32 index, bool& isByWeight);
		virtual short VCOM_CALLTYPE NurbsDegree(MCObjectHandle nHandle, Sint32 index);
		virtual Boolean VCOM_CALLTYPE NurbsDelVertex(MCObjectHandle nHandle, Sint32 index1, Sint32 index2);
		virtual Sint32 VCOM_CALLTYPE NurbsGetNumPts(MCObjectHandle nHandle, Sint32 index);
		virtual Boolean VCOM_CALLTYPE NurbsGetPt3D(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3& pt);
		virtual Boolean VCOM_CALLTYPE NurbsGetWeight(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& weight);
		virtual Boolean VCOM_CALLTYPE NurbsKnot(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& knot);
		virtual Sint32 VCOM_CALLTYPE NurbsNumKnots(MCObjectHandle nHandle, Sint32 index);
		virtual Boolean VCOM_CALLTYPE NurbsSetKnot(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double knot);
		virtual Boolean VCOM_CALLTYPE NurbsSetPt3D(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3 pt);
		virtual Boolean VCOM_CALLTYPE NurbsSetWeight(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double weight);
		virtual Boolean VCOM_CALLTYPE NurbsSurfaceEvaluatePoint(MCObjectHandle nurbsHandle, double u, double v, WorldPt3& pt);
		virtual double_gs VCOM_CALLTYPE ObjArea(MCObjectHandle h);
		virtual double_gs VCOM_CALLTYPE ObjSurfaceArea(MCObjectHandle h);
		virtual double_gs VCOM_CALLTYPE ObjVolume(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE Products3D(MCObjectHandle h, double_gs &Ixy, double_gs &Iyz, double_gs &Izx);
		virtual void VCOM_CALLTYPE RemoveRoofElement(MCObjectHandle object, short id);
		virtual void VCOM_CALLTYPE Set3DVertex(MCObjectHandle h, short vertexNum, const WorldPt3& vertex, Boolean recalcBounds = true);
		virtual void VCOM_CALLTYPE SetArcAnglesN(MCObjectHandle h, double_param startAngle, double_param sweepAngle);
		virtual Boolean VCOM_CALLTYPE SetBatAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, WorldCoord topWidth, WorldCoord baseHeight, double_param topSlope, WorldCoord controlPoint);
		virtual Boolean VCOM_CALLTYPE SetDormerAttributes(MCObjectHandle object, const short dormerID, short edgeIndex, WorldCoord cornerOffset, Boolean isPerpOffset, WorldCoord perpOrHeightOffset, InternalIndex symName, Boolean centerSymbol, WorldCoord symOffset);
		virtual void VCOM_CALLTYPE SetDormerThick(MCObjectHandle object, WorldCoord wallThick, WorldCoord roofThick);
		virtual void VCOM_CALLTYPE SetEndPoints(MCObjectHandle h, const WorldPt& startPt, const WorldPt& endPt);
		virtual void VCOM_CALLTYPE SetEntityMatrix(MCObjectHandle h, const TransformMatrix& theMat);
		virtual void VCOM_CALLTYPE SetExtrudeValues(MCObjectHandle h, WorldCoord bottom, WorldCoord top);
		virtual Boolean VCOM_CALLTYPE SetGableAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, WorldCoord overhang);
		virtual Boolean VCOM_CALLTYPE SetHipAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, double_param frontSlope, WorldCoord overhang);
		virtual void VCOM_CALLTYPE SetLocus3DPosition(MCObjectHandle h, const WorldPt3& locPos);
		virtual void VCOM_CALLTYPE SetLocusPosition(MCObjectHandle h, const WorldPt& locPos);
		virtual void VCOM_CALLTYPE SetObjectBounds(MCObjectHandle h, const WorldRect& bounds);
		virtual void VCOM_CALLTYPE SetPolyShapeClose(MCObjectHandle h, Boolean closed);
		virtual void VCOM_CALLTYPE SetQArcQuadrant(MCObjectHandle h, short quadrant);
		virtual void VCOM_CALLTYPE SetRoofAccessoriesParameters(MCObjectHandle roof, Boolean insertAttic, Boolean insertSoffit, Boolean insertFascia, WorldCoord fasciaWidth, WorldCoord fasciaHeight, WorldCoord atticHeight, WorldCoord recess, WorldCoord rakeThick, WorldCoord trimDepth);
		virtual void VCOM_CALLTYPE SetRoofAttributes(MCObjectHandle object, Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter);
		virtual void VCOM_CALLTYPE SetRRectDiameters(MCObjectHandle h, WorldCoord xDiam, WorldCoord yDiam);
		virtual Boolean VCOM_CALLTYPE SetShedAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param topSlope, WorldCoord overhang);
		virtual Boolean VCOM_CALLTYPE SetSkylight(MCObjectHandle object, const short skylightID, short edgeIndex, WorldCoord cornerOffset, WorldCoord perpOffset, InternalIndex symName);
		virtual void VCOM_CALLTYPE SetSweepAnglesN(MCObjectHandle theSweep, double_param startAngle, double_param arcAngle, double_param incrAngle);
		virtual void VCOM_CALLTYPE SetSweepScrew(MCObjectHandle theSweep, WorldCoord dist);
		virtual Boolean VCOM_CALLTYPE SetTrapeziumAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, Boolean useTopWidth, WorldCoord topWidth, double_param leftSlope, double_param rightSlope, double_param topSlope);
		virtual void VCOM_CALLTYPE SetVertex(MCObjectHandle h, short vertexNum, const WorldPt& vertex, VertexType vType, WorldCoord arcRadius, Boolean recalcBounds = true);
		virtual void VCOM_CALLTYPE WrapGetSweepScrew(MCObjectHandle theSweep, double_gs& outCoordLen);
		virtual MCObjectHandle VCOM_CALLTYPE CreateCircularDimension(const WorldPt& center, const WorldPt& end, WorldCoord startOffset, WorldCoord textOffset, const WorldRect& box, Boolean isRadius);
		virtual Boolean VCOM_CALLTYPE GetArrowByClass(MCObjectHandle h);
		virtual void VCOM_CALLTYPE GetArrowHeads(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, short& size);
		virtual void VCOM_CALLTYPE GetArrowHeadsN(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size);
		virtual Boolean VCOM_CALLTYPE GetColor(MCObjectHandle h, ObjectColorType& colors);
		virtual OpacityRef VCOM_CALLTYPE GetDefaultOpacity();
		virtual Boolean VCOM_CALLTYPE GetDefaultOpacityByClass();
		virtual Boolean VCOM_CALLTYPE GetFColorsByClass(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE GetFillIAxisEndPoint(MCObjectHandle objectHandle, WorldPt& iAxisEndPoint);
		virtual Boolean VCOM_CALLTYPE GetFillJAxisEndPoint(MCObjectHandle objectHandle, WorldPt& jAxisEndPoint);
		virtual Boolean VCOM_CALLTYPE GetFillOriginPoint(MCObjectHandle objectHandle, WorldPt& originPoint);
		virtual InternalIndex VCOM_CALLTYPE GetFillPat(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE GetFillPoints(MCObjectHandle objectHandle, WorldPt& originPoint, WorldPt& iAxisEndPoint, WorldPt& jAxisEndPoint);
		virtual Boolean VCOM_CALLTYPE GetFPatByClass(MCObjectHandle h);
		virtual short VCOM_CALLTYPE GetLineWeight(MCObjectHandle h);
		virtual short VCOM_CALLTYPE GetLineWeightDisplayMM(short mils);
		virtual short VCOM_CALLTYPE GetLineWeightDisplayPt(short mils);
		virtual Boolean VCOM_CALLTYPE GetLWByClass(MCObjectHandle h);
		virtual void VCOM_CALLTYPE GetMarker(MCObjectHandle obj, MarkerType& style, short& size, short& angle, Boolean& start, Boolean& end);
		virtual Boolean VCOM_CALLTYPE GetObjBeginningMarker(MCObjectHandle h, SMarkerStyle& mstyle, Boolean& visibility);
		virtual Boolean VCOM_CALLTYPE GetObjEndMarker(MCObjectHandle h, SMarkerStyle& mstyle, Boolean& visibility);
		virtual OpacityRef VCOM_CALLTYPE GetOpacity(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE GetOpacityByClass(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE GetPColorsByClass(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE GetPPatByClass(MCObjectHandle h);
		virtual void VCOM_CALLTYPE GetVertexVis(MCObjectHandle h, short vertNum, Boolean& vis);
		virtual void VCOM_CALLTYPE SetArrowByClass(MCObjectHandle h);
		virtual void VCOM_CALLTYPE SetArrowHeads(MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, short size);
		virtual void VCOM_CALLTYPE SetArrowHeadsN(MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, double_param size);
		virtual void VCOM_CALLTYPE SetColor(MCObjectHandle h, ObjectColorType colors);
		virtual void VCOM_CALLTYPE SetDefaultOpacity(OpacityRef inOpacity);
		virtual void VCOM_CALLTYPE SetDefaultOpacityByClass();
		virtual void VCOM_CALLTYPE SetFColorsByClass(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE SetFillIAxisEndPoint(MCObjectHandle objectHandle, const WorldPt& iAxisEndPoint);
		virtual Boolean VCOM_CALLTYPE SetFillJAxisEndPoint(MCObjectHandle objectHandle, const WorldPt& jAxisEndPoint);
		virtual Boolean VCOM_CALLTYPE SetFillOriginPoint(MCObjectHandle objectHandle, const WorldPt& originPoint);
		virtual void VCOM_CALLTYPE SetFillPat(MCObjectHandle h, InternalIndex theFill);
		virtual void VCOM_CALLTYPE SetFPatByClass(MCObjectHandle h);
		virtual void VCOM_CALLTYPE SetLineWeight(MCObjectHandle h, short mils);
		virtual Boolean VCOM_CALLTYPE SetLineWeightDisplayMM(short hundredths);
		virtual Boolean VCOM_CALLTYPE SetLineWeightDisplayPt(short sixteenths);
		virtual void VCOM_CALLTYPE SetLWByClass(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE SetObjBeginningMarker(MCObjectHandle h, SMarkerStyle mstyle, Boolean visibility);
		virtual Boolean VCOM_CALLTYPE SetObjEndMarker(MCObjectHandle h, SMarkerStyle mstyle, Boolean visibility);
		virtual void VCOM_CALLTYPE SetOpacity(MCObjectHandle h, OpacityRef  inNewOpacity);
		virtual void VCOM_CALLTYPE SetOpacityByClass(MCObjectHandle h);
		virtual void VCOM_CALLTYPE SetPColorsByClass(MCObjectHandle h);
		virtual void VCOM_CALLTYPE SetPPatByClass(MCObjectHandle h);
		virtual void VCOM_CALLTYPE SetVertexVis(MCObjectHandle h, short vertNum, Boolean vis);
		virtual MCObjectHandle VCOM_CALLTYPE GetDefinition(MCObjectHandle h);
		virtual short VCOM_CALLTYPE GetDXFColorToLineWeight(const short inDXFColorIndex);
		virtual MCObjectHandle VCOM_CALLTYPE GetNamedObject(const TXString& objName);
		virtual InternalIndex VCOM_CALLTYPE GetObjectClass(MCObjectHandle h);
		virtual void VCOM_CALLTYPE GetObjectName(MCObjectHandle h, TXString& outName);
		virtual short VCOM_CALLTYPE GetObjectType(MCObjectHandle h);
		virtual void VCOM_CALLTYPE GetSymbolDefinitionIcon(MCObjectHandle theSymDef, Sint32 icon[32] );
		virtual short VCOM_CALLTYPE GetSymbolDefinitionType(MCObjectHandle theSymDef);
		virtual Boolean VCOM_CALLTYPE IsLocked(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE IsSelected(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE IsVisible(MCObjectHandle h);
		virtual void VCOM_CALLTYPE LockObject(MCObjectHandle h, Boolean lock = true);
		virtual void VCOM_CALLTYPE SelectObject(MCObjectHandle h, Boolean select = true);
		virtual void VCOM_CALLTYPE SetDXFColorToLineWeight(const short inDXFColorIndex, const short inLineWeight);
		virtual void VCOM_CALLTYPE SetObjectClass(MCObjectHandle h, InternalIndex classID);
		virtual GSError VCOM_CALLTYPE SetObjectName(MCObjectHandle h, const TXString& name);
		virtual void VCOM_CALLTYPE SetSymbolDefinitionIcon(MCObjectHandle theSymDef, const Sint32 icon[32] );
		virtual void VCOM_CALLTYPE SetVisibility(MCObjectHandle h, Boolean visible);
		virtual void VCOM_CALLTYPE AttachAuxObject(MCObjectHandle h, MCObjectHandle newOwner);
		virtual void VCOM_CALLTYPE DeleteAuxObject(MCObjectHandle h, MCObjectHandle owner);
		virtual MCObjectHandle VCOM_CALLTYPE FindAuxObject(MCObjectHandle owner, short objectType);
		virtual MCObjectHandle VCOM_CALLTYPE FindDataObject(MCObjectHandle owner, OSType tag);
		virtual MCObjectHandle VCOM_CALLTYPE FirstAuxObject(MCObjectHandle h);
		virtual OSType VCOM_CALLTYPE GetDataTag(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE GetPluginType(const TXString& name, EVSPluginType& type);
		virtual Boolean VCOM_CALLTYPE IsPluginFormat(MCObjectHandle h);
		virtual MCObjectHandle VCOM_CALLTYPE NewDataObject(MCObjectHandle attachTo, OSType tag, size_t objectSize);
		virtual MCObjectHandle VCOM_CALLTYPE NextAuxObject(MCObjectHandle start, short objectType);
		virtual MCObjectHandle VCOM_CALLTYPE NextDataObject(MCObjectHandle start, OSType tag);
		virtual void VCOM_CALLTYPE RemoveAuxObject(MCObjectHandle h, MCObjectHandle owner);
		virtual Boolean VCOM_CALLTYPE TaggedDataCreate(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,int numDataElements);
		virtual Boolean VCOM_CALLTYPE TaggedDataGet(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,int dataIndex, void* getData);
		virtual Boolean VCOM_CALLTYPE TaggedDataGetNumElements(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,Sint32* getData);
		virtual Boolean VCOM_CALLTYPE TaggedDataRemoveContainer(MCObjectHandle inOwnerObj,OSType dataContainer);
		virtual Boolean VCOM_CALLTYPE TaggedDataRemoveTag(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag);
		virtual Boolean VCOM_CALLTYPE TaggedDataSet(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,int dataIndex, const void* data);
		virtual double_gs VCOM_CALLTYPE CoordLengthToPageLengthN(WorldCoord len);
		virtual double_gs VCOM_CALLTYPE CoordLengthToPagePoints(WorldCoord len);
		virtual Boolean VCOM_CALLTYPE CoordLengthToPixelLength(WorldCoord numCoords, short& numPixels);
		virtual double_gs VCOM_CALLTYPE CoordLengthToUnitsLengthN(WorldCoord len);
		virtual MCObjectHandle VCOM_CALLTYPE CreateOvalN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height);
		virtual Boolean VCOM_CALLTYPE DimStringToCoord(const TXString& s, WorldCoord& c);
		virtual void VCOM_CALLTYPE FPCoordLengthToPageLength(double_param coordLen, double_gs& pageLen);
		virtual void VCOM_CALLTYPE FPCoordLengthToUnitsLength(double_param coordLen, double_gs& unitsLen);
		virtual void VCOM_CALLTYPE ModelPt2DToScreenPt(WorldPt& vertex);
		virtual void VCOM_CALLTYPE ModelVecToScreenVec(WorldPt& vertex);
		virtual void VCOM_CALLTYPE PageLengthToFPCoordLength(double_param pageLen, double_gs& coordLen);
		virtual WorldCoord VCOM_CALLTYPE PagePointsToCoordLength(double_gs& points);
		virtual void VCOM_CALLTYPE PixelLengthToCoordLength(short numPixels, WorldCoord& numCoords);
		virtual void VCOM_CALLTYPE ScreenPtToModelPt2D(WorldPt& vertex);
		virtual void VCOM_CALLTYPE ScreenVecToModelVec(WorldPt& vertex);
		virtual void VCOM_CALLTYPE UnitsLengthToFPCoordLength(double_param unitsLen, double_gs& coordLen);
		virtual WorldCoord VCOM_CALLTYPE WorldCoordsPerDrawingUnit();
		virtual void VCOM_CALLTYPE WrapPageLengthToCoordLengthN(double_param len, double_gs& outCoordLen);
		virtual void VCOM_CALLTYPE WrapUnitsLengthToCoordLengthN(double_param len, double_gs& outCoordLen);
		virtual short VCOM_CALLTYPE AddSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid);
		virtual Boolean VCOM_CALLTYPE AppendRoofEdge(MCObjectHandle object, const WorldPt& edgePt, double_param slope, WorldCoord projection, WorldCoord eaveHeight);
		virtual MCObjectHandle VCOM_CALLTYPE Create3DPoly();
		virtual MCObjectHandle VCOM_CALLTYPE CreateAngleDimension(const WorldPt& center, const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset);
		virtual MCObjectHandle VCOM_CALLTYPE CreateArcN(const WorldRect& bounds, double_param startAngle, double_param sweepAngle);
		virtual short VCOM_CALLTYPE CreateBatDormer(MCObjectHandle object);
		virtual MCObjectHandle VCOM_CALLTYPE CreateChainDimension(MCObjectHandle h1, MCObjectHandle h2);
		virtual MCObjectHandle VCOM_CALLTYPE CreateCombineIntoSurface(const WorldPt& inPoint);
		virtual MCObjectHandle VCOM_CALLTYPE CreateCone(const WorldPt3& center, const WorldPt3 &tip, WorldCoord radius);
		virtual MCObjectHandle VCOM_CALLTYPE CreateContourCurves(MCObjectHandle h, double_param delta, WorldPt3 pointOnPlane, WorldPt3 planeNormal);
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomDimensionStandard(const TXString& name);
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObject(const TXString& name, const WorldPt& location, double_param angle=0.0, bool bInsert = true);
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectByMatrix(const TXString& name, const TransformMatrix& matrix);
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectDoubleClick(const TXString& name);
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectPath(const TXString& name, MCObjectHandle pathHand = NULL, MCObjectHandle profileGroupHand = NULL);
		virtual MCObjectHandle VCOM_CALLTYPE CreateExtrude(WorldCoord bottom, WorldCoord top);
		virtual MCObjectHandle VCOM_CALLTYPE CreateExtrudeAlongPath(MCObjectHandle pathHandle, MCObjectHandle profileHandle);
		virtual short VCOM_CALLTYPE CreateGableDormer(MCObjectHandle object);
		virtual MCObjectHandle VCOM_CALLTYPE CreateGroup();
		virtual MCObjectHandle VCOM_CALLTYPE CreateHemisphere(const WorldPt3& center, const WorldPt3 &topPoint);
		virtual short VCOM_CALLTYPE CreateHipDormer(MCObjectHandle object);
		virtual MCObjectHandle VCOM_CALLTYPE CreateImageProp(TXString& propName, InternalIndex textureRef, WorldCoord height, WorldCoord width, Boolean enforceImageAspectRatio, Boolean crossedPlanes, Boolean createPlugin, Boolean autoRotate, Boolean createSymbol);
		virtual MCObjectHandle VCOM_CALLTYPE CreateInterpolatedSurface(MCObjectHandle surfaceHandle, Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree);
		virtual MCObjectHandle VCOM_CALLTYPE CreateLayer(const TXString& layerName, short layerType);
		virtual MCObjectHandle VCOM_CALLTYPE CreateLayerN(const TXString& name, double_param scale);
		virtual MCObjectHandle VCOM_CALLTYPE CreateLightN(const WorldPt3& pos, short kind, Boolean isOn, double_param brightness, const WorldPt3& color, Boolean castShadows);
		virtual MCObjectHandle VCOM_CALLTYPE CreateLine(const WorldPt& startPt, const WorldPt& endPt);
		virtual MCObjectHandle VCOM_CALLTYPE CreateLinearDimension(const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset, WorldCoord textOffset, const Vector2& dir, short dimType);
		virtual MCObjectHandle VCOM_CALLTYPE CreateLocus(const WorldPt& location);
		virtual MCObjectHandle VCOM_CALLTYPE CreateLocus3D(const WorldPt3& location);
		virtual MCObjectHandle VCOM_CALLTYPE CreateLoftSurfaces(MCObjectHandle groupCurvesH, Boolean bRule, Boolean  bClose, Boolean bSolid);
		virtual MCObjectHandle VCOM_CALLTYPE CreateNurbsCurve(WorldPt3 firstPt, bool byCtrlPts, short degree);
		virtual MCObjectHandle VCOM_CALLTYPE CreateNurbsSurface(Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree);
		virtual MCObjectHandle VCOM_CALLTYPE CreateOval(const WorldRect& bounds);
		virtual MCObjectHandle VCOM_CALLTYPE CreatePolyshape();
		virtual MCObjectHandle VCOM_CALLTYPE CreateQArc(const WorldRect& bounds, short quadrant);
		virtual MCObjectHandle VCOM_CALLTYPE CreateRectangle(const WorldRect& bounds);
		virtual MCObjectHandle VCOM_CALLTYPE CreateRectangleN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height);
		virtual MCObjectHandle VCOM_CALLTYPE CreateRoof(Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter);
		virtual MCObjectHandle VCOM_CALLTYPE CreateRoundWall(const WorldPt& startPt, const WorldPt& ptOnArc, const WorldPt& endPt, WorldCoord wallThickness);
		virtual MCObjectHandle VCOM_CALLTYPE CreateRRectangle(const WorldRect& bounds, WorldCoord xDiam, WorldCoord yDiam);
		virtual MCObjectHandle VCOM_CALLTYPE CreateRRectangleN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height, CBWorldCoord_param xDiam, CBWorldCoord_param yDiam, Boolean isProportional);
		virtual short VCOM_CALLTYPE CreateShedDormer(MCObjectHandle object);
		virtual MCObjectHandle VCOM_CALLTYPE CreateBasicSlab(short slabKind);
		virtual MCObjectHandle VCOM_CALLTYPE CreateSphere(const WorldPt3& center, WorldCoord radius);
		virtual MCObjectHandle VCOM_CALLTYPE CreateStaticHatch(const TXString& name, const WorldPt& inOriginPoint, double_param inRotationAngle);
		virtual MCObjectHandle VCOM_CALLTYPE CreateStaticHatchFromObject(MCObjectHandle inObj, const TXString& name, const WorldPt& inOriginPoint, double_param inRotationAngle);
		virtual Boolean VCOM_CALLTYPE CreateSurfacefromCurvesNetwork();
		virtual MCObjectHandle VCOM_CALLTYPE CreateSweepN(double_param startAngle, double_param arcAngle, double_param incrAngle, WorldCoord screwDist);
		virtual MCObjectHandle VCOM_CALLTYPE CreateSymbolDefinition(TXString& inoutName);
		virtual MCObjectHandle VCOM_CALLTYPE CreateSymbolFolder(const TXString& name);
		virtual MCObjectHandle VCOM_CALLTYPE CreateTaperedExtrude(MCObjectHandle profileH, const double_param angle = 1.0, const double_param height = 1.0 );
		virtual short VCOM_CALLTYPE CreateTrapeziumDormer(MCObjectHandle object);
		virtual MCObjectHandle VCOM_CALLTYPE CreateViewport(MCObjectHandle parentHandle);
		virtual MCObjectHandle VCOM_CALLTYPE CreateWall(const WorldPt& startPt, const WorldPt& endPt, WorldCoord thickness);
		virtual MCObjectHandle VCOM_CALLTYPE DefineCustomObject(const TXString& name, Byte prefWhen = kCustomObjectPrefAlways);
		virtual void VCOM_CALLTYPE DuplicateSelection(WorldCoord dx, WorldCoord dy);
		virtual MCObjectHandle VCOM_CALLTYPE ExtendNurbsCurve(MCObjectHandle curveHandle, double_param distance, Boolean bStart, Boolean bLinear);
		virtual MCObjectHandle VCOM_CALLTYPE ExtendNurbsSurface(MCObjectHandle surfaceHandle, double_param distance, Boolean bStart, Boolean bLinear, Boolean bUDir);
		virtual MCObjectHandle VCOM_CALLTYPE GenerateBezierApproximationFromPolygon(MCObjectHandle hPolygonHandle, const WorldCoord approximationTolerance, const double discontinuityAngleTolerance, const unsigned short quadraticsPerCubic);
		virtual MCObjectHandle VCOM_CALLTYPE GroupSelection();
		virtual short VCOM_CALLTYPE IntersectSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid);
		virtual MCObjectHandle VCOM_CALLTYPE PlaceSymbolByNameN(const TXString& symName, const WorldPt& location, double_param rotation=0.0);
		virtual MCObjectHandle VCOM_CALLTYPE PlaceSymbolN(MCObjectHandle definition, const WorldPt& location, double_param rotation=0.0);
		virtual MCObjectHandle VCOM_CALLTYPE RevolveWithRail(MCObjectHandle profileH, MCObjectHandle railH, MCObjectHandle axisH);
		virtual void VCOM_CALLTYPE Split2DObjectByLine(MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, MCObjectHandle& listHandles);
		virtual short VCOM_CALLTYPE SubtractSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid);
		virtual void VCOM_CALLTYPE AddChoice(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short nItemIndex);
		virtual void VCOM_CALLTYPE AddListBoxTabStop(Sint32 dialogID, Sint32 componentID, int tabStop);
	
		virtual short VCOM_CALLTYPE Deprecated354(Sint32, Sint32, short, short, short i);
	
		virtual Boolean VCOM_CALLTYPE AdjustComponentPixelPos(Sint32 nDialogID, Sint32 nComponentID, int nHorizontalPixels, int nVerticalPixels);
		virtual void VCOM_CALLTYPE AlertCritical(const TXString& text, const TXString& advice = "");
		virtual void VCOM_CALLTYPE AlertInform(const TXString& text, const TXString& advice = "", bool minorAlert = false, const TXString& category = "", const TXString& item = "", const TXString& checkboxOverrideText = "");
		virtual short VCOM_CALLTYPE AlertQuestion(const TXString& question, const TXString& advice = "", short defaultButton = 1, const TXString& OKOverrideText = "", const TXString& CancelOverrideText = "", const TXString& customButtonAText = "", const TXString& customButtonBText = "", const TXString& category = "", const TXString& item = "", const TXString& checkboxOverrideText = "");
		virtual bool VCOM_CALLTYPE AlignBottomEdge(Sint32 dialogID, Sint32 srcItemID, short bottomID, short alignMode = 1);
		virtual bool VCOM_CALLTYPE AlignLeftEdge(Sint32 dialogID, Sint32 srcItemID, short leftID, short alignMode = 1);
		virtual bool VCOM_CALLTYPE AlignRightEdge(Sint32 dialogID, Sint32 srcItemID, short rightID, short alignMode = 1);
		virtual Boolean VCOM_CALLTYPE AreListBrowserColumnLinesEnabled(Sint32 dialogID, Sint32 componentID);
		virtual Boolean VCOM_CALLTYPE AreListBrowserRadioColumnLinesEnabled(Sint32 dialogID, Sint32 componentID, short columnIndex);
		virtual Boolean VCOM_CALLTYPE ClearGradientSliderSegments(Sint32 dialogID, Sint32 componentID);
		virtual Boolean VCOM_CALLTYPE Confirm(const TXString & strNode, Boolean yesOrNo);
		virtual void VCOM_CALLTYPE CreateCenteredStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar);
		virtual void VCOM_CALLTYPE CreateCheckBox(Sint32 dialogID, Sint32 itemID, const TXString& name);
		virtual void VCOM_CALLTYPE CreateCheckBoxGroupBox(Sint32 dialogID, short itemID, const TXString& name, bool hasFrame);
		virtual Boolean VCOM_CALLTYPE CreateClassPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar);
		virtual void VCOM_CALLTYPE CreateCMYKColorSwatch(Sint32 dialogID, Sint32 itemID);
		virtual void VCOM_CALLTYPE CreateColorPopup(Sint32 dialogID, Sint32 itemID, short widthInStdChar = -1);
		virtual void VCOM_CALLTYPE CreateControl(Sint32 dialogID, Sint32 itemID, Sint32 controlKind, const TXString& name, SintptrT data);
		virtual void VCOM_CALLTYPE CreateCustomControl(Sint32 dlogID, Sint32 controlID, short widthInPixels, short heightInPixels);
		virtual Boolean VCOM_CALLTYPE CreateDesignLayerPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar);
		virtual void VCOM_CALLTYPE CreateEditInteger(Sint32 dialogID, Sint32 itemID, Sint32 defaultValue, short widthInStdChar);
		virtual void VCOM_CALLTYPE CreateEditReal(Sint32 dialogID, Sint32 itemID, Sint32 editRealType, double value, short widthInStdChar);
		virtual void VCOM_CALLTYPE CreateEditText(Sint32 dialogID, Sint32 itemID, const TXString& defaultText, short widthInStdChar, short heightInLines = 1);
		virtual Boolean VCOM_CALLTYPE CreateEnhancedPullDownMenu(Sint32 liDialogID, Sint32 liComponentID, int widthInStdChar, Boolean bShowIconInMainWindow);
		virtual void VCOM_CALLTYPE CreateGroupBox(Sint32 dialogID, Sint32 itemID, const TXString& name, Boolean hasFrame);
		virtual Boolean VCOM_CALLTYPE CreateIconPushButton(Sint32 nDialogID, Sint32 nComponentID, int nIconID, int widthInStdChar);
		virtual Boolean VCOM_CALLTYPE CreateImageControl(Sint32 liDialogID, Sint32 liComponentID, int iWidthPixels, int iHeightPixels, MCObjectHandle hImage);
		virtual Sint32 VCOM_CALLTYPE CreateLayout(const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName);
		virtual void VCOM_CALLTYPE CreateLineAttributePopup(Sint32 dialogID, Sint32 itemID);
		virtual void VCOM_CALLTYPE CreateLineStylePopup(Sint32 dialogID, Sint32 itemID);
		virtual void VCOM_CALLTYPE CreateLineWeightPopup(Sint32 dialogID, Sint32 itemID);
		virtual void VCOM_CALLTYPE CreateListBox(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines);
		virtual void VCOM_CALLTYPE CreateListBoxN(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines, Boolean isMultiSel);
		virtual void VCOM_CALLTYPE CreateListBrowser(Sint32 dialogID, Sint32 componentID, Sint16 widthInStdChar, Sint16 heightInLines);
		virtual void VCOM_CALLTYPE CreateMarkerPopup(Sint32 dialogID, Sint32 itemID);
		virtual void VCOM_CALLTYPE CreatePatternPopup(Sint32 dialogID, Sint32 itemID);
		virtual void VCOM_CALLTYPE CreatePullDownMenu(Sint32 dialogID, Sint32 itemID, short widthInStdChar);
		virtual Boolean VCOM_CALLTYPE CreatePullDownMenuGroupBox(Sint32 liDialogID, Sint32 liComponentID, int widthInStdChar, const TXString& strLabel, Boolean bHasFrame);
		virtual void VCOM_CALLTYPE CreatePushButton(Sint32 dialogID, Sint32 itemID, const TXString& buttonName);
		virtual void VCOM_CALLTYPE CreateRadioButton(Sint32 dialogID, Sint32 itemID, const TXString& buttonName);
		virtual void VCOM_CALLTYPE CreateRadioButtonGroupBox(Sint32 dialogID, short itemID, const TXString& name, bool hasFrame);
		virtual Sint32 VCOM_CALLTYPE CreateResizableLayout(const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName, Boolean widthResizable, Boolean heightResizable);
		virtual void VCOM_CALLTYPE CreateRightStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar);
		virtual Boolean VCOM_CALLTYPE CreateSeparator(Sint32 liDialogID, Sint32 liComponentID, int widthInPixels);
		virtual Boolean VCOM_CALLTYPE CreateSheetLayerPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar);
		virtual void VCOM_CALLTYPE CreateStandardIconControl(Sint32 dialogID, Sint32 iconControlID, int iconNumber);
		virtual void VCOM_CALLTYPE CreateStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar);
		virtual void VCOM_CALLTYPE CreateSwapControl(Sint32 dialogID, Sint32 itemID);
		virtual void VCOM_CALLTYPE CreateSwapPane(Sint32 dialogID, Sint32 swapControlID, Sint32 newGroupID);
		virtual void VCOM_CALLTYPE CreateSymbolDisplayControl(Sint32 dialogIDIn, Sint32 itemIDIn, const TXString& symbolRefIn, SymbolImgInfo& imgInfoInOut);
		virtual void VCOM_CALLTYPE CreateTabControl(Sint32 dialogID, short itemID);
		virtual void VCOM_CALLTYPE CreateTabPane(Sint32 dialogID, short itemID, short groupID);
		virtual Boolean VCOM_CALLTYPE CreateThreeStateCheckBox(Sint32 liDialogID, Sint32 liComponentID, const TXString& strName);
		virtual Boolean VCOM_CALLTYPE CreateTreeControl(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar, int heightInLines);
		virtual void VCOM_CALLTYPE DeleteAllItems(Sint32 dialogID, Sint32 itemID);
		virtual Boolean VCOM_CALLTYPE DeleteAllListBrowserItems(Sint32 dialogID, Sint32 componentID);
		virtual Boolean VCOM_CALLTYPE DeleteListBrowserColumn(Sint32 dialogID, Sint32 componentID, short columnIndex);
		virtual Boolean VCOM_CALLTYPE DeleteListBrowserItem(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual void VCOM_CALLTYPE DeselectEditText(Sint32 dialogID, Sint32 controlID);
		virtual Boolean VCOM_CALLTYPE DisplayColorPopup(int top, int left, int bottom, int right, Boolean inDisplayByClassOption, ColorRef& ioColorRef, Boolean& ioIsByClass);
		virtual void VCOM_CALLTYPE DisplaySwapPane(Sint32 dialogID, Sint32 swapControlID, Sint32 groupNumber);
		virtual void VCOM_CALLTYPE DisplayTabPane(Sint32 dialogID, Sint32 controlID, Sint32 groupNumber);
		virtual void VCOM_CALLTYPE EnableItem(Sint32 dialogID, Sint32 itemID, Boolean bEnable);
		virtual Boolean VCOM_CALLTYPE EnableListBrowser(Sint32 dialogID, Sint32 componentID, Boolean enable);
		virtual Boolean VCOM_CALLTYPE EnableListBrowserClickAllDataChange(Sint32 dialogID, Sint32 componentID, Boolean enable);
		virtual void VCOM_CALLTYPE EnableListBrowserColumnLines(Sint32 dialogID, Sint32 componentID, Boolean enableColumnLines);
		virtual void VCOM_CALLTYPE EnableListBrowserColumnTracking(Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableColumnTracking);
		virtual Boolean VCOM_CALLTYPE EnableListBrowserDragAndDrop(Sint32 dialogID, Sint32 componentID, Boolean bEnable);
		virtual Boolean VCOM_CALLTYPE EnableListBrowserDropOnIndices(Sint32 liDialogID, Sint32 liComponentID, int iStartIndex, int iEndIndex, Boolean bEnable);
		virtual void VCOM_CALLTYPE EnableListBrowserRadioColumnLines(Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableRadioColumnLines);
		virtual Boolean VCOM_CALLTYPE EnableListBrowserSingleLineSelection(Sint32 dialogID, Sint32 componentID, Boolean enable);
		virtual void VCOM_CALLTYPE EnableListBrowserSorting(Sint32 dialogID, Sint32 componentID, Boolean enableSorting);
		virtual Boolean VCOM_CALLTYPE EnableListBrowserUpdates(Sint32 liDialogID, Sint32 liComponentID, Boolean bEnableUpdates);
		virtual Boolean VCOM_CALLTYPE EnsureListBrowserItemIsVisible(Sint32 dialogID, Sint32 componentID, int iIndex);
		virtual Boolean VCOM_CALLTYPE ExpandTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID, Boolean bExpand);
		virtual Boolean VCOM_CALLTYPE FindListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& columnDataItemIndex);
		virtual Boolean VCOM_CALLTYPE FindListBrowserColumnItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& itemIndex);
		virtual Boolean VCOM_CALLTYPE FormatTextDialog(FormatTextType& formatTextRec);
		virtual Sint32 VCOM_CALLTYPE GetActiveEditItem(Sint32 dialogID);
		virtual Sint32 VCOM_CALLTYPE GetActivePane(Sint32 dialogID, Sint32 controlID);
		virtual void VCOM_CALLTYPE GetBooleanItem(Sint32 dialogID, Sint32 itemID, Boolean& state);
		virtual void VCOM_CALLTYPE GetChoiceCount(Sint32 dialogID, Sint32 itemID, short& numItems);
		virtual void VCOM_CALLTYPE GetChoiceIndex(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short& nItemIndex);
		virtual void VCOM_CALLTYPE GetChoiceText(Sint32 dialogID, Sint32 itemID, short nItemIndex, TXString& outItemText);
		virtual void VCOM_CALLTYPE GetCMYKColor(Sint32 dialogID, Sint32 itemID, TGSColorV2 &outColor);
		virtual void VCOM_CALLTYPE GetColorButton(Sint32 dialogID, Sint32 itemID, RGBColor& rgb);
		virtual void VCOM_CALLTYPE GetColorChoice(Sint32 dialogID, Sint32 itemID, short& colorIndex);
		virtual Boolean VCOM_CALLTYPE GetComponentRect(Sint32 nDialogID, Sint32 nComponentID, int& nLeft, int& nTop, int& nRight, int& nBottom, ELayoutCoordinateSpace cooredinateSpace = eLayoutCoordinateSpacePoints);
		virtual Boolean VCOM_CALLTYPE GetComponentTextWidth(Sint32 nDialogID, Sint32 nComponentID, int& nWidthInLMUnits);
		virtual void VCOM_CALLTYPE GetControlData(Sint32 dialogID, Sint32 itemID, SControlDataBase& data);
		virtual void VCOM_CALLTYPE GetCustomControlScrollArea(Sint32 dialogID, Sint32 component, int *leftStart, int *topStart);
		virtual bool VCOM_CALLTYPE GetEditInteger(Sint32 dialogID, Sint32 componentID, Sint32& value);
		virtual bool VCOM_CALLTYPE GetEditReal(Sint32 dialogID, Sint32 componentID, short editRealType, double& value);
		virtual Boolean VCOM_CALLTYPE GetGradientSliderData(Sint32 dialogID, Sint32 componentID, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color);
		virtual Boolean VCOM_CALLTYPE GetGradientSliderSelectedMarker(Sint32 dialogID, Sint32 componentID, short& segmentIndex, short& markerType);
		virtual Boolean VCOM_CALLTYPE GetIconPushButtonState(Sint32 nDialogID, Sint32 nComponentID, Boolean& bPressed);
		virtual InternalIndex VCOM_CALLTYPE GetImagePopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual short VCOM_CALLTYPE GetImagePopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex);
		virtual short VCOM_CALLTYPE GetImagePopupSelectedItem(Sint32 dialogID, Sint32 componentID);
		virtual void VCOM_CALLTYPE GetItemText(Sint32 dialogID, Sint32 itemID, TXString& outCurrentText);
		virtual Boolean VCOM_CALLTYPE GetLayoutDialogPosition(Sint32 dialogID, short& left, short& top, short& right, short& bottom);
		virtual void VCOM_CALLTYPE GetLayoutDialogSize(Sint32 dialogID, short& width, short& height);
		virtual Sint32 VCOM_CALLTYPE DEPRECATED_608(short textRsrcID);
		inline Sint32 GS_HIDDEN_VISIBILITY GetLayoutFromRsrc(short textRsrcID)
		{
			const char *vwr = DEFAULTVWRIDENTIFIER;
			gSDK->Kludge(3602, (void *)vwr, NULL);
			char resID[128];
	#if GS_WIN
			sprintf_s(resID, sizeof(resID), "%s/DialogLayout/%d *", vwr, textRsrcID);
	#else
			sprintf(resID, "%s/DialogLayout/%d *", vwr, textRsrcID);
	#endif
			return gSDK->CreateLayoutDialogFromVWResource(resID);
		}
		virtual void VCOM_CALLTYPE GetLineWeightChoice(Sint32 dialogID, Sint32 itemID, short& lineWeight);
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnWidth(Sint32 dialogID, Sint32 componentID, short columnIndex, short& width);
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnDataItemInfo(Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex, TXString& itemString, short &imageOn, short &imageOff, Sint32 &itemData);
		virtual int VCOM_CALLTYPE GetListBrowserColumnSortState(Sint32 dialogID, Sint32 componentID, int columnIndex);
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnOwnerDrawnType(Sint32 dialogID, Sint32 componentID, int iIndex, int iSubIndex, int &iOwnerDrawnType);
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnHeaderToolTip(Sint32 dialogID, Sint32 componentID, int iColumnIndex, TXString& strToolTipPrimaryText, TXString& strToolTipSubText);
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnHeaderJust(Sint32 dialogID, Sint32 componentID, int iColumnIndex, int &iJustification);
		virtual short VCOM_CALLTYPE GetListBrowserControlType(Sint32 dialogID, Sint32 componentID, short columnIndex);
		virtual short VCOM_CALLTYPE GetListBrowserEditDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex);
		virtual Boolean VCOM_CALLTYPE GetListBrowserEventInfo(Sint32 dialogID, Sint32 componentID, int& iEventType, int& iRowIndex, int& iColumnIndex);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemIndex, int nSubItemIndex, Sint32& nUserData);
		virtual short VCOM_CALLTYPE GetListBrowserItemDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemGradientOrImageRefNumber(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 &liRefNumber);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString& itemString, short& imageIndex);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPenForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPenBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextJust(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int &justification);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextStyle(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, unsigned char &textStyle);
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextColor(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int &redIndex, int &greenIndex, int &blueIndex);
	
		virtual Boolean VCOM_CALLTYPE Deprecated481(Sint32, Sint32, int, int, int&, int&, int&);
	
		virtual int VCOM_CALLTYPE GetListBrowserSortColumn(Sint32 dialogID, Sint32 componentID);
		virtual void VCOM_CALLTYPE GetMarkerChoice(Sint32 dialogID, Sint32 itemID, MarkerType& style, Sint8& angle, double& size, double& width, Uint8& thicknessBasis, double& thickness);
		virtual short VCOM_CALLTYPE GetMarkerPopupSelectedItem(Sint32 dialogID, Sint32 componentID, char& style, char& angle, short& size);
		virtual GSHandle VCOM_CALLTYPE GetMultilineText(Sint32 dialogID, Sint32 itemID);
		virtual short VCOM_CALLTYPE GetNumGradientSliderSegments(Sint32 dialogID, Sint32 componentID);
		virtual short VCOM_CALLTYPE GetNumImagePopupItems(Sint32 dialogID, Sint32 componentID);
		virtual short VCOM_CALLTYPE GetNumListBrowserColumns(Sint32 dialogID, Sint32 componentID);
		virtual short VCOM_CALLTYPE GetNumListBrowserColumnDataItems(Sint32 dialogID, Sint32 componentID, short columnIndex);
		virtual short VCOM_CALLTYPE GetNumListBrowserItems(Sint32 dialogID, Sint32 componentID);
		virtual int VCOM_CALLTYPE GetNumSelectedListBrowserItems(Sint32 dialogID, Sint32 componentID);
		virtual void VCOM_CALLTYPE GetPatternData(Sint32 dialogID, Sint32 itemID, short& patternIndex, short& foreColor, short& backColor);
		virtual void VCOM_CALLTYPE GetSelChoiceIndex(Sint32 dialogID, Sint32 itemID, short inStartIndex, short& outSelectedIndex);
		virtual void VCOM_CALLTYPE GetSelectedChoiceIndex(Sint32 dialogID, Sint32 itemID, short& nItemIndex);
		virtual void VCOM_CALLTYPE GetSelectionRange(Sint32 dialogID, Sint32 controlID, int& startPos, int& endPos);
		virtual Boolean VCOM_CALLTYPE GetThreeStateCheckBoxState(Sint32 liDialogID, Sint32 liComponentID, int& iState);
		virtual Boolean VCOM_CALLTYPE GetTreeControlItemData(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, SintptrT& nItemData);
		virtual Boolean VCOM_CALLTYPE GetTreeControlSelectedItem(Sint32 nDialogID, Sint32 nComponentID, int& nItemID);
	
		virtual int VCOM_CALLTYPE Deprecated545(Sint32 liDialogID, Sint32 liComponentID, const TXString& strName, int iIconID);
	
		virtual short VCOM_CALLTYPE InsertGradientSliderSegment(Sint32 dialogID, Sint32 componentID, double_param spotPosition, const WorldPt3& color);
		virtual short VCOM_CALLTYPE InsertImagePopupObjectItem(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex);
		virtual Sint32 VCOM_CALLTYPE InsertImagePopupResource(Sint32 dialogID, Sint32 componentID, Sint32 listID, Sint32 index);
		virtual int VCOM_CALLTYPE InsertImagePopupSeparator(Sint32 liDialogID, Sint32 liComponentID, const TXString& strLabel);
		virtual short VCOM_CALLTYPE InsertListBrowserColumn(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& headerString, short width);
		virtual short VCOM_CALLTYPE InsertListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short imageOn, short imageOff, Sint32 itemData);
		virtual short VCOM_CALLTYPE InsertListBrowserItem(Sint32 dialogID, Sint32 componentID, short itemIndex, const TXString& itemString);
	
		virtual Boolean VCOM_CALLTYPE Deprecated557(Sint32 nDialogID, Sint32 nComponentID, const TXString& strLabel, int nIconIndex);
	
		virtual int VCOM_CALLTYPE InsertTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, const TXString& strItemLabel, int nParentID, int nAfterID);
		virtual Boolean VCOM_CALLTYPE IsItemEnabled(Sint32 nDialogID, Sint32 nComponentID);
		virtual Boolean VCOM_CALLTYPE IsItemVisible(Sint32 nDialogID, Sint32 nComponentID);
		virtual Boolean VCOM_CALLTYPE IsListBrowserColumnTrackingEnabled(Sint32 dialogID, Sint32 componentID, short columnIndex);
		virtual Boolean VCOM_CALLTYPE IsListBrowserItemSelected(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual Boolean VCOM_CALLTYPE IsListBrowserSortingEnabled(Sint32 dialogID, Sint32 componentID);
		virtual Boolean VCOM_CALLTYPE NotifyPullDownClicked(Sint32 nDialogID, Sint32 nComponentID);
		virtual TOSWndPtr VCOM_CALLTYPE OverrideControl(Sint32 dlogID, Sint32 controlID, void* pCallbackOSFunction);
		virtual void VCOM_CALLTYPE PostMinorNoteAlert(const TXString& msgStr);
		virtual void VCOM_CALLTYPE PostMinorStopAlert(const TXString& msgStr);
		virtual void VCOM_CALLTYPE PostNoteAlert(const TXString& msgStr);
		virtual void VCOM_CALLTYPE PostStopAlert(const TXString& msgStr);
		virtual Boolean VCOM_CALLTYPE RefreshItem(Sint32 liDialogID, Sint32 liComponentID);
		virtual Boolean VCOM_CALLTYPE RefreshListBrowser(Sint32 dialogID, Sint32 componentID);
		virtual Boolean VCOM_CALLTYPE RemoveAllImagePopupItems(Sint32 dialogID, Sint32 componentID);
		virtual void VCOM_CALLTYPE RemoveAllListBrowserColumnDataItems(Sint32 dialogID, Sint32 componentID, short columnIndex);
		virtual void VCOM_CALLTYPE RemoveChoice(Sint32 dialogID, Sint32 itemID, short itemIndexToRemove);
		virtual Boolean VCOM_CALLTYPE RemoveEnhancedPullDownMenuItemRange(Sint32 liDialogID, Sint32 liComponentID, int iStartItemIndexToRemove, int iEndItemIndexToRemove);
		virtual Boolean VCOM_CALLTYPE RemoveGradientSliderSegment(Sint32 dialogID, Sint32 componentID, short segmentIndex);
		virtual Boolean VCOM_CALLTYPE RemoveImagePopupItem(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual void VCOM_CALLTYPE RemoveListBoxTabStop(Sint32 dialogID, Sint32 componentID);
		virtual Boolean VCOM_CALLTYPE RemoveListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex);
		virtual Boolean VCOM_CALLTYPE RemoveTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID);
		virtual Sint32 VCOM_CALLTYPE RunLayoutDialog(Sint32 dialogID, GS_EventHandlerProcPtr handleEvent, void* env, const TXString& contextualHelpID, const bool bEnableContextualHelp = true);
		virtual void VCOM_CALLTYPE SelectChoice(Sint32 dialogID, Sint32 itemID, short nItemIndex, Boolean bSelect = true);
		virtual void VCOM_CALLTYPE SelectEditText(Sint32 dialogID, Sint32 itemID);
		virtual Boolean VCOM_CALLTYPE SelectTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID);
		virtual bool VCOM_CALLTYPE SetBelowItem(Sint32 dialogID, Sint32 srcItemID, Sint32  belowItemID, short indentStdCh, short lineSpacing);
		virtual void VCOM_CALLTYPE SetBooleanItem(Sint32 dialogID, Sint32 itemID, Boolean bSelect);
		virtual void VCOM_CALLTYPE SetCMYKColor(Sint32 dialogID, Sint32 itemID, TGSColorV2 &inColor);
		virtual void VCOM_CALLTYPE SetColorButton(Sint32 dialogID, Sint32 itemID, const RGBColor& rgb);
		virtual void VCOM_CALLTYPE SetColorChoice(Sint32 dialogID, Sint32 itemID, short colorIndex);
		virtual Boolean VCOM_CALLTYPE SetComponentIndeterminate(Sint32 nDialogID, Sint32 nComponentID, Boolean bIndeterminateState);
		virtual Boolean VCOM_CALLTYPE SetComponentSize(Sint32 nDialogID, Sint32 nComponentID, int nWidthPixels, int nHeightPixels);
		virtual void VCOM_CALLTYPE SetControlData(Sint32 dialogID, Sint32 itemID, const SControlDataBase& data);
		virtual void VCOM_CALLTYPE SetEdgeBinding(Sint32 dialogID, Sint32 itemID, Boolean boundToLeft, Boolean boundToRight, Boolean boundToTop, Boolean boundToBottom);
		virtual void VCOM_CALLTYPE SetEditInteger(Sint32 dialogID, Sint32 componentID, Sint32 value);
		virtual void VCOM_CALLTYPE SetEditReal(Sint32 dialogID, Sint32 componentID, short editRealType, double value);
		virtual bool VCOM_CALLTYPE SetFirstGroupItem(Sint32 dialogID, Sint32 groupID, Sint32 firstItemID);
		virtual bool VCOM_CALLTYPE SetFirstLayoutItem(Sint32 dialogID, Sint32 firstItemID);
		virtual Boolean VCOM_CALLTYPE SetFocusOnItem(Sint32 liDialogID, Sint32 liComponentID);
		virtual Boolean VCOM_CALLTYPE SetFocusOnListBrowser(Sint32 dialogID, Sint32 componentID);
		virtual Boolean VCOM_CALLTYPE SetGradientSliderData(Sint32 dialogID, Sint32 componentID, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color);
		virtual Boolean VCOM_CALLTYPE SetGradientSliderSelectedMarker(Sint32 dialogID, Sint32 componentID, short segmentIndex, short markerType);
		virtual void VCOM_CALLTYPE SetHelpText(Sint32 dialogID, Sint32 itemID, const TXString& helpText);
		virtual Boolean VCOM_CALLTYPE SetIconPushButtonState(Sint32 nDialogID, Sint32 nComponentID, Boolean bPressed);
		virtual Boolean VCOM_CALLTYPE SetImageControlHandle(Sint32 liDialogID, Sint32 liComponentID, MCObjectHandle hImage);
		virtual Boolean VCOM_CALLTYPE SetImageControlPath(Sint32 nDialogID, Sint32 nComponentID, const TXString& strPath);
		virtual Boolean VCOM_CALLTYPE SetImagePopupSelectedItem(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual void VCOM_CALLTYPE SetItemText(Sint32 dialogID, Sint32 itemID, const TXString& strNewText);
		virtual Boolean VCOM_CALLTYPE SetItemToolTipText(Sint32 nDialogID, Sint32 nComponentID, const TXString& strToolTip, const TXString& strSubToolTip, int nIndex, int nSubIndex);
		virtual Boolean VCOM_CALLTYPE SetLayoutDialogPosition(Sint32 dialogID, short left, short top);
		virtual void VCOM_CALLTYPE SetLayoutDialogSize(Sint32 dialogID, short width, short height);
		virtual Boolean VCOM_CALLTYPE SetLayoutOption(Sint32 dialogID, short option, Sint32 value);
		virtual void VCOM_CALLTYPE SetLineWeightChoice(Sint32 dialogID, Sint32 itemID, short lineWeight);
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnWidth(Sint32 dialogID, Sint32 componentID, short fromColumn, short toColumn, short width);
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnOwnerDrawnType(Sint32 dialogID, Sint32 componentID, int iIndex, int iSubIndex, int iOwnerDrawnType);
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnHeaderToolTip(Sint32 dialogID, Sint32 componentID, int iColumnIndex, const TXString& strToolTipPrimaryText, const TXString& strToolTipSubText);
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnHeaderJust(Sint32 dialogID, Sint32 componentID, int iColumnIndex, int iJustification);
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnImage(Sint32 nDialogID, Sint32 nComponentID, int nColumnIndex, int nImageIndex);
		virtual Boolean VCOM_CALLTYPE SetListBrowserControlType(Sint32 dialogID, Sint32 componentID, short columnIndex, short controlType);
		virtual Boolean VCOM_CALLTYPE SetListBrowserDragAndDropColumn(Sint32 dialogID, Sint32 componentID, int iColumnIndex);
		virtual Boolean VCOM_CALLTYPE SetListBrowserEditDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemIndex, int nSubItemIndex, Sint32 nUserData);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemGradientOrImageRefNumber(Sint32 dialogID, Sint32 componentID, int itemIndex, int iSubItemIndex, Sint32 liRefNumber);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, short imageIndex);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPenForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPenBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextJust(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int justification);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextStyle(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, unsigned char textStyle);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextColor(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int redIndex, int greenIndex, int blueIndex);
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemUsingColumnDataItem(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short columnDataItemIndex);
	
		virtual Boolean VCOM_CALLTYPE Deprecated590(Sint32, Sint32, int, int, int, int, int);
	
		virtual Boolean VCOM_CALLTYPE SetListBrowserSelection(Sint32 dialogID, Sint32 componentID, short firstItemIndex, short lastItemIndex, Boolean select);
		virtual void VCOM_CALLTYPE SetListBrowserSortColumn(Sint32 dialogID, Sint32 componentID, int columnIndex, Boolean isAscending);
		virtual void VCOM_CALLTYPE SetMarkerChoice(Sint32 dialogID, Sint32 itemID, MarkerType style, Sint8 angle, double size, double width, Uint8 thicknessBasis, double thickness);
		virtual void VCOM_CALLTYPE SetMultilineText(Sint32 dialogID, Sint32 itemID, GSHandle text);
		virtual void VCOM_CALLTYPE SetPatternData(Sint32 dialogID, Sint32 itemID, short patternIndex, short foreColor, short backColor);
		virtual void VCOM_CALLTYPE SetProportionalBinding(Sint32 dialogID, Sint32 itemID, Boolean leftProportional, Boolean rightProportional, Boolean topProportional, Boolean bottomProportional);
		virtual bool VCOM_CALLTYPE SetRightItem(Sint32 dialogID, Sint32 srcItemID, Sint32 rightItemID, short indentStdCh, short lineSpacing);
		virtual void VCOM_CALLTYPE SetSelectionRange(Sint32 dialogID, Sint32 controlID, int startPos, int endPos);
		virtual void VCOM_CALLTYPE SetTextEditable(Sint32 dialogID, Sint32 itemID, Boolean editable);
		virtual Boolean VCOM_CALLTYPE SetThreeStateCheckBoxState(Sint32 liDialogID, Sint32 liComponentID, int iState);
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemID, SintptrT nItemData);
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemData2(Sint32 nDialogID, Sint32 nComponentID, int nItemID, const TXString & itemData);
		virtual Boolean VCOM_CALLTYPE ShowEnhancedPullDownMenuGroupIcon(Sint32 liDialogID, Sint32 liComponentID, Boolean bShowGroupIcon);
		virtual void VCOM_CALLTYPE ShowItem(Sint32 dialogID, Sint32 itemID, Boolean bShow);
		virtual void VCOM_CALLTYPE UpdateCustomControlScrollArea(Sint32 dialogID, Sint32 component, int width, int height, int leftStart, int topStart, int stepSize, bool liveUpdate, bool alwaysShowHoriz = false, bool alwaysShowVert = false );
		virtual void VCOM_CALLTYPE UpdateSymbolDisplayControl(Sint32 dialogIDIn, Sint32 itemIDIn, const TXString& symbolRefIn, SymbolImgInfo& imgInfoInOut);
		virtual bool VCOM_CALLTYPE VerifyLayout(Sint32 dialogID);
		virtual InternalIndex VCOM_CALLTYPE AddClass(const TXString& className);
		virtual InternalIndex VCOM_CALLTYPE AddGuidesClass();
		virtual void VCOM_CALLTYPE ColorIndexToName(const ColorRef& inColorRef, TXString& outColorName);
		virtual void VCOM_CALLTYPE ColorIndexToRGB(ColorRef colorIndex, RGBColor& rgb);
		virtual Boolean VCOM_CALLTYPE CopySymbol(const TXString& inFilePath, const TXString& symName);
		virtual MCObjectHandle VCOM_CALLTYPE CreateGradient(const TXString& name);
		virtual MCObjectHandle VCOM_CALLTYPE CreateHatch(const TXString& inName, Boolean inUsePageUnits, Boolean inRotateInWalls, Boolean inRotateInSymbols, Boolean inTransparent,  ColorRef inFillColorIndex);
		virtual MCObjectHandle VCOM_CALLTYPE CreateImageFromPaint(MCObjectHandle paint, const TXString& imageName);
		virtual MCObjectHandle VCOM_CALLTYPE CreatePaintFromImage(MCObjectHandle image);
		virtual MCObjectHandle VCOM_CALLTYPE CreateWallStyle(const TXString& wallStyleName);
		virtual void VCOM_CALLTYPE DeleteClass(const TXString& className);
		virtual void VCOM_CALLTYPE DeselectAll();
		virtual MCObjectHandle VCOM_CALLTYPE GetActiveSymbolDef();
		virtual Boolean VCOM_CALLTYPE GetClassVisibility(InternalIndex index);
		virtual MCObjectHandle VCOM_CALLTYPE GetCurrentLayer();
		virtual short VCOM_CALLTYPE GetCurrentView();
		virtual InternalIndex VCOM_CALLTYPE GetDimensionClassID();
		virtual Boolean VCOM_CALLTYPE GetGradientData(MCObjectHandle gradient, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color);
		virtual Boolean VCOM_CALLTYPE GetGradientMidpointPosition(MCObjectHandle gradient, short segmentIndex, double& position);
		virtual void VCOM_CALLTYPE GetGradientSpotColor(MCObjectHandle gradient, short segmentIndex, WorldPt3& color);
		virtual Boolean VCOM_CALLTYPE GetGradientSpotPosition(MCObjectHandle gradient, short segmentIndex, double& position);
		virtual void VCOM_CALLTYPE GetGridUnits(WorldCoord& x, WorldCoord& y);
		virtual Boolean VCOM_CALLTYPE GetHatchLevel(MCObjectHandle inHatchDef, short inLevel, WorldPt& outStartPt, WorldPt& outRepeatVec, double& outDashFactor, WorldPt& outOffsetVec, ColorRef& outColorIndex, short& outMilsLineWeight);
		virtual void VCOM_CALLTYPE GetLayerScaleN(MCObjectHandle h, double_gs& scale);
		virtual MCObjectHandle VCOM_CALLTYPE GetNamedLayer(const TXString& layerName);
		virtual InternalIndex VCOM_CALLTYPE GetNoneClassID();
		virtual short VCOM_CALLTYPE GetNumGradientSegments(MCObjectHandle gradient);
		virtual void VCOM_CALLTYPE GetPageBounds(WorldRect& bounds);
		virtual Boolean VCOM_CALLTYPE GetPatternBits(short inIndex, Uint8 outPattern[8]);
		virtual Boolean VCOM_CALLTYPE GetSheetLayerUserOrigin(MCObjectHandle layerHandle, WorldPt& origin);
		virtual void VCOM_CALLTYPE GetUnits(UnitsType& currentUnits);
		virtual void VCOM_CALLTYPE GetUserOrigin(WorldPt& origin);
		virtual Boolean VCOM_CALLTYPE GetUserOriginFP(WorldPt& outOrigin);
		virtual short VCOM_CALLTYPE InsertGradientSegment(MCObjectHandle gradient, double_param spotPosition, double_param midpointPosition, const WorldPt3& color);
		virtual void VCOM_CALLTYPE MarkCurrentDocChanged();
		virtual Sint32 VCOM_CALLTYPE NumSelectedObjects();
		virtual Boolean VCOM_CALLTYPE RemoveGradientSegment(MCObjectHandle gradient, short segmentIndex);
		virtual void VCOM_CALLTYPE ResetAllObjectsVisibility();
		virtual void VCOM_CALLTYPE RGBToColorIndex(const RGBColor& rgb, ColorRef& colorIndex);
		virtual void VCOM_CALLTYPE SelectAll();
		virtual void VCOM_CALLTYPE SetActiveSymbolDef(MCObjectHandle aSymDef);
		virtual void VCOM_CALLTYPE SetClassVisibility(InternalIndex index, Boolean visible);
		virtual void VCOM_CALLTYPE SetCurrentLayer(MCObjectHandle theLayer);
		virtual Boolean VCOM_CALLTYPE SetGradientData(MCObjectHandle gradient, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color);
		virtual Boolean VCOM_CALLTYPE SetGradientMidpointPosition(MCObjectHandle gradient, short segmentIndex, double_param position);
		virtual Boolean VCOM_CALLTYPE SetGradientSpotColor(MCObjectHandle gradient, short segmentIndex, const WorldPt3& color);
		virtual Boolean VCOM_CALLTYPE SetGradientSpotPosition(MCObjectHandle gradient, short& segmentIndex, double_param position);
		virtual Boolean VCOM_CALLTYPE SetHatchLevel(MCObjectHandle inHatchDef, short inLevel, const WorldPt& inStartPt, const WorldPt& inRepeatVec, double_param inDashFactor, const WorldPt& inOffsetVec, ColorRef inColorIndex, short inMilsLineWeight);
		virtual void VCOM_CALLTYPE SetLayerScaleN(MCObjectHandle theLayer, double_param newScale);
		virtual void VCOM_CALLTYPE SetMarker(MCObjectHandle obj, MarkerType style, short size, short angle, Boolean start, Boolean end);
		virtual void VCOM_CALLTYPE SetProjection(MCObjectHandle theLayer, short newProj, Boolean confirmWithUser, Boolean doProgress);
		virtual Boolean VCOM_CALLTYPE SetRenderMode(MCObjectHandle theLayer, short newRenderMode, Boolean immediate, Boolean doProgress);
		virtual Boolean VCOM_CALLTYPE SetSheetLayerUserOrigin(MCObjectHandle layerHandle, const WorldPt& origin);
		virtual void VCOM_CALLTYPE SetUserOrigin(const WorldPt& origin);
		virtual Boolean VCOM_CALLTYPE SetUserOriginFP(const WorldPt& inOrigin);
		virtual MCObjectHandle VCOM_CALLTYPE ShowCreateImageDialog();
		virtual Boolean VCOM_CALLTYPE ShowGradientEditorDialog(MCObjectHandle& gradient);
		virtual Boolean VCOM_CALLTYPE ValidClass(InternalIndex classID);
		virtual TTesselator VCOM_CALLTYPE CreateTessellator(short convertRes3D);
		virtual void VCOM_CALLTYPE DeleteTessellator(TTesselator pTess);
		virtual bool VCOM_CALLTYPE TesselateObject(TTesselator pTess, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv);
		virtual Boolean VCOM_CALLTYPE UpdateThumbnailPreview(InternalIndex inIndex);
		virtual void VCOM_CALLTYPE CloseXCode(Sint32 extCodeInfoID);
		virtual GenericFunctionPtr VCOM_CALLTYPE OpenXCode(Sint32 extCodeInfoID, Boolean needsResourceFileOpen);
		virtual void VCOM_CALLTYPE GSDisposeHandle(GSHandle handle);
		virtual void VCOM_CALLTYPE GSDisposePtr(void* p);
		virtual void VCOM_CALLTYPE GSGetHandleSize(GSHandle handle, size_t& size);
		virtual void VCOM_CALLTYPE GSGetHandleState(GSHandle handle, Boolean& isLocked);
		virtual void VCOM_CALLTYPE GSHLock(GSHandle handle);
		virtual void VCOM_CALLTYPE GSHUnlock(GSHandle handle);
		virtual GSHandle VCOM_CALLTYPE GSNewHandle(size_t size);
		virtual VoidPtr VCOM_CALLTYPE GSNewPtr(size_t size);
		virtual void VCOM_CALLTYPE GSReduceHandleSize(GSHandle handle, size_t size);
		virtual Boolean VCOM_CALLTYPE GSSetHandleSize(GSHandle handle, size_t size);
		virtual void VCOM_CALLTYPE GSSetHandleState(GSHandle handle, Boolean isLocked);
		virtual VoidPtr VCOM_CALLTYPE GSSetPtrSize(void* p, size_t size);
		virtual Sint32 VCOM_CALLTYPE AddResourceToList(Sint32 listID, MCObjectHandle resource);
		virtual Sint32 VCOM_CALLTYPE BuildResourceList(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems);
		virtual void VCOM_CALLTYPE DeleteResourceFromList(Sint32 listID, Sint32 index);
		virtual void VCOM_CALLTYPE DisposeResourceList(Sint32 listID);
		virtual void VCOM_CALLTYPE GetActualNameFromResourceList(Sint32 listID, Sint32 index, TXString& name);
		virtual short VCOM_CALLTYPE GetMyMenuCommandIndex();
		virtual void VCOM_CALLTYPE GetNameFromResourceList(Sint32 listID, Sint32 index, TXString& name);
		virtual MCObjectHandle VCOM_CALLTYPE GetResourceFromList(Sint32 listID, Sint32 index);
		virtual MCObjectHandle VCOM_CALLTYPE ImportResourceToCurrentFile(Sint32 listID, Sint32 index);
		virtual Boolean VCOM_CALLTYPE RegisterMenuForCallback(short menuIndex, OSType whichChange);
		virtual Sint32 VCOM_CALLTYPE ResourceListSize(Sint32 listID);
		virtual void VCOM_CALLTYPE UnregisterMenuForCallback(short menuIndex, OSType whichChange);
	
		virtual void VCOM_CALLTYPE Deprecated747(short iconID);
		virtual void VCOM_CALLTYPE Deprecated748(short initialSetting, short iconID);
	
		virtual void VCOM_CALLTYPE AddPullDownMenuItem(short group, const TXString& item);
		virtual void VCOM_CALLTYPE AddPullDownMenuMode(const TXString& label);
	
		virtual void VCOM_CALLTYPE Deprecated751(short initialSetting, short numButtons, short id1, short id2, short id3, short id4, short id5, short id6);
	
		virtual void VCOM_CALLTYPE AddTxtBtnMode(const TXString& theText);
		virtual void VCOM_CALLTYPE EnableMode(short modeNum, Boolean enable);
		virtual short VCOM_CALLTYPE GetModeValue(short modeNum);
		virtual void VCOM_CALLTYPE SetHelpString(const TXString& helpMessage);
		virtual void VCOM_CALLTYPE SetModeValue(short modeNum, short theValue);
		virtual void VCOM_CALLTYPE SetPullDownMenuSelection(short group, short selectedItem);
		virtual void VCOM_CALLTYPE ClassIDToName(InternalIndex classID, TXString& outClassName);
		virtual InternalIndex VCOM_CALLTYPE ClassNameToID(const TXString& className);
		virtual MCObjectHandle VCOM_CALLTYPE InternalIndexToHandle(InternalIndex index);
		virtual void VCOM_CALLTYPE InternalIndexToNameN(InternalIndex index, TXString& outName);
		virtual InternalIndex VCOM_CALLTYPE MaxClassID();
		virtual Boolean VCOM_CALLTYPE NameToInternalIndexN(const TXString& name, InternalIndex& index);
		virtual Boolean VCOM_CALLTYPE SetPolyVertexLoopDirection(MCObjectHandle ioPolyToSet, PolyDirectionSpecType inPolyDirectionSpec);
		virtual void VCOM_CALLTYPE AddToConstraintModel(MCObjectHandle obj);
		virtual Boolean VCOM_CALLTYPE AddViewportAnnotationObject(MCObjectHandle viewportHandle, MCObjectHandle annotationHandle);
		virtual Boolean VCOM_CALLTYPE AppendParameterWidget(Sint32 ObjectID, int parameterID, const TXString& text, Sint32 data);
		virtual Boolean VCOM_CALLTYPE AppendWidget(Sint32 ObjectID, int widgetType, int eventID, const TXString& text, Sint32 data);
		virtual MCObjectHandle VCOM_CALLTYPE ConvertTo3DPolygons(MCObjectHandle h, Boolean preserveOriginal = false);
		virtual MCObjectHandle  VCOM_CALLTYPE ConvertToNURBS(MCObjectHandle h, Boolean keepOrig = false);
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolygon(MCObjectHandle h, Boolean preserveOriginal = false);
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolygonN(MCObjectHandle h, Boolean preserveOriginal , short conversionResolution);
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolyline(MCObjectHandle h, Boolean preserveOriginal = false);
		virtual Boolean VCOM_CALLTYPE ConvertToUnstyledWall(MCObjectHandle theWall);
		virtual void VCOM_CALLTYPE CreateConstraintModel(MCObjectHandle obj, Boolean useSelection);
		virtual MCObjectHandle VCOM_CALLTYPE CreateOffsetNurbsObjectHandle(MCObjectHandle h,   double offset);
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtsCreate( MCObjectHandle inOwnerObj, int numDataElements, GS_CustomObjectControlPtsInitProcPtr initProc,void* env);
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtsRemove(MCObjectHandle inOwnerObj);
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtSet(MCObjectHandle inOwnerObj,int dataIndex, const WorldPt3& pt,Boolean is2DOnly,Boolean isHidden,int inClientID);
		virtual MCObjectHandle VCOM_CALLTYPE CustomObjectGetSurfaceProxy(MCObjectHandle inPathObject);
		virtual Boolean VCOM_CALLTYPE CustomObjectReplacePath(MCObjectHandle inPathObject, MCObjectHandle pathPolyline);
		virtual Boolean VCOM_CALLTYPE DeleteAllComponents(MCObjectHandle object);
		virtual Boolean VCOM_CALLTYPE DeleteComponent(MCObjectHandle object, short componentIndex);
		virtual void VCOM_CALLTYPE DeleteConstraint(MCObjectHandle obj, MCObjectHandle constraint);
		virtual MCObjectHandle VCOM_CALLTYPE DuplicateObject(MCObjectHandle h);
		virtual void VCOM_CALLTYPE EnableParameter(MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetEnabled);
		virtual Boolean VCOM_CALLTYPE EvaluateNurbsSurfacePointAndNormal(MCObjectHandle surfaceHandle, double u, double v, WorldPt3& point,  WorldPt3& normal);
		virtual void VCOM_CALLTYPE ForEachLayer( GS_ForEachObjectProcPtr action, void *actionEnv);
		virtual void VCOM_CALLTYPE ForEachObject( short traverseWhat, GS_ForEachObjectProcPtr action, void *actionEnv);
		virtual void VCOM_CALLTYPE Get2DPt(MCObjectHandle obj, short index, WorldPt& loc);
		virtual MCObjectHandle VCOM_CALLTYPE GetBinaryConstraint(short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2);
		virtual void VCOM_CALLTYPE GetClosestPt(MCObjectHandle& obj, const WorldPt& pt, short& index, Sint32& containedObj);
		virtual void VCOM_CALLTYPE GetClosestSide(MCObjectHandle obj, const WorldPt& pt, short& indexA, short& indexB);
		virtual Boolean VCOM_CALLTYPE GetComponentClass(MCObjectHandle object, short componentIndex, Sint32 &componentClass);
		virtual Boolean VCOM_CALLTYPE GetComponentFill(MCObjectHandle object, short componentIndex, Sint32 &fill);
		virtual Boolean VCOM_CALLTYPE GetComponentFillColors(MCObjectHandle object, short componentIndex, ColorRef &fillForeColor, ColorRef &fillBackColor);
		virtual Boolean VCOM_CALLTYPE GetComponentName(MCObjectHandle object, short componentIndex, TXString &componentName);
		virtual Boolean VCOM_CALLTYPE GetComponentPenColors(MCObjectHandle object, short componentIndex, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor);
		virtual Boolean VCOM_CALLTYPE GetComponentPenWeights(MCObjectHandle object, short componentIndex, Uint8 &leftPenWeight, Uint8 &rightPenWeight);
		virtual Boolean VCOM_CALLTYPE GetComponentUseFillClassAttr(MCObjectHandle object, short componentIndex, Boolean &useFillClassAttributes);
		virtual Boolean VCOM_CALLTYPE GetComponentUsePenClassAttr(MCObjectHandle object, short componentIndex, Boolean &useLeftPenClassAttributes, Boolean &useRightPenClassAttributes);
		virtual Boolean VCOM_CALLTYPE GetComponentWidth(MCObjectHandle object, short componentIndex, WorldCoord &width);
		virtual Boolean VCOM_CALLTYPE GetCustomObjectColor(MCObjectHandle objectHand, int iTagID, ColorRef& ioColorRef);
		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectPath(MCObjectHandle objectHand);
		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectProfileGroup(MCObjectHandle objectHand);
		virtual Boolean VCOM_CALLTYPE GetDimensionStandardVariable(short dimensionIndex, short fieldSelector, TVariableBlock& value);
		virtual Boolean VCOM_CALLTYPE GetDistanceAlongNurbsCurve(MCObjectHandle inNurbsCurve, double_param inParameter1, Sint32 inParameter1CurveIndex,  double_param inParameter2, Sint32 inParameter2CurveIndex, double_gs& outDistance);
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginChoice(const TXString& pluginName, const TXString& parameterName, int choiceIndex, TXString& localizedChoice);
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginName(const TXString& pluginName, TXString& outLocalizedName);
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginParameter(const TXString& pluginName, const TXString& parameterName, TXString& localizedParameterName);
		virtual Boolean VCOM_CALLTYPE GetNumberOfComponents(MCObjectHandle object, short &numComponents);
		virtual Boolean VCOM_CALLTYPE GetNurbsObjectDistanceFromPoint(MCObjectHandle h, const WorldPt&  point,  double& distance);
		virtual Boolean VCOM_CALLTYPE GetObjectProperty(MCObjectHandle hObject, Sint32 inPropID, Boolean& outValue);
		virtual Boolean VCOM_CALLTYPE GetObjectPropertyChar(MCObjectHandle hObject, Sint32 inPropID, unsigned char& outValue);
		virtual Boolean VCOM_CALLTYPE GetObjectVariable(MCObjectHandle theObject, short setSelector, TVariableBlock& value);
		virtual Boolean VCOM_CALLTYPE GetParameterOnNurbsCurve(MCObjectHandle h, const WorldPt3&  point,  double& parameter, Sint32& index);
		virtual Boolean VCOM_CALLTYPE GetPointAndParameterOnNurbsCurveAtGivenLength(MCObjectHandle inNurbCurve, double_param inPercentOfLength, WorldPt3& outPointOnCurve,  double_gs& outParametricParameter, Sint32& outPiecewiseCurveIndex);
		virtual Boolean VCOM_CALLTYPE GetRoofEdge(MCObjectHandle object, short index, WorldPt& vertexPt, double_gs& slope, WorldCoord& projection, WorldCoord& eaveHeight);
		virtual MCObjectHandle VCOM_CALLTYPE GetSingularConstraint(short type, MCObjectHandle obj, short vertexA, short vertexB);
		virtual Boolean VCOM_CALLTYPE GetViewportClassVisibility(MCObjectHandle viewportHandle, InternalIndex classIndex, short& visibilityType);
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportCropObject(MCObjectHandle viewportHandle);
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportGroup(MCObjectHandle viewportHandle, short groupType);
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportGroupParent(MCObjectHandle groupHandle);
		virtual Boolean VCOM_CALLTYPE GetViewportLayerVisibility(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short& visibilityType);
		virtual MeshErrorType VCOM_CALLTYPE GroupToMesh(MCObjectHandle theMesh);
		virtual Boolean VCOM_CALLTYPE HasConstraint(MCObjectHandle obj);
		virtual Boolean VCOM_CALLTYPE InsertAllParametersAsWidgets(Sint32 inObjectID);
		virtual Boolean VCOM_CALLTYPE InsertParameterWidget(Sint32 ObjectID, int position, int parameterID, const TXString& text, Sint32 data);
		virtual Boolean VCOM_CALLTYPE InsertWidget(Sint32 ObjectID, int position, int widgetType, int eventID, const TXString& text, Sint32 data);
		virtual Boolean VCOM_CALLTYPE IsObjectFromReferencedFile(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE IsViewportGroupContainedObject(MCObjectHandle objectHandle,  short groupType);
		virtual void VCOM_CALLTYPE MakePolyshapeValid(MCObjectHandle thePoly);
		virtual MeshErrorType VCOM_CALLTYPE MeshToGroup(MCObjectHandle theMesh);
		virtual void VCOM_CALLTYPE MoveObject(MCObjectHandle h, WorldCoord dx, WorldCoord dy);
		virtual void VCOM_CALLTYPE MoveObject3D(MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz);
		virtual void VCOM_CALLTYPE NotifyLayerChange(StatusData liAdditionalData = 0);
		virtual Boolean VCOM_CALLTYPE RemoveCustomObjectColor(MCObjectHandle objectHand, int iTagID);
		virtual Boolean VCOM_CALLTYPE RemoveRoofEdge(MCObjectHandle object, short index);
		virtual Boolean VCOM_CALLTYPE ResetObject(MCObjectHandle h);
		virtual void VCOM_CALLTYPE RotateObjectN(MCObjectHandle& h, const WorldPt& rotCenter, double_param angle);
		virtual Boolean VCOM_CALLTYPE ScaleObject3D(MCObjectHandle ioObject, const WorldPt3& scaleCen, const Vector& scaleVector);
		virtual void VCOM_CALLTYPE ScaleObjectN(MCObjectHandle h, const WorldPt& scaleCen, double_param scaleX, double_param scaleY);
		virtual Boolean VCOM_CALLTYPE SetBinaryConstraint(short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2);
		virtual Boolean VCOM_CALLTYPE SetComponentClass(MCObjectHandle object, short componentIndex, Sint32 componentClass);
		virtual Boolean VCOM_CALLTYPE SetComponentFill(MCObjectHandle object, short componentIndex, Sint32 fill);
		virtual Boolean VCOM_CALLTYPE SetComponentFillColors(MCObjectHandle object, short componentIndex, ColorRef fillForeColor, ColorRef fillBackColor);
		virtual Boolean VCOM_CALLTYPE SetComponentName(MCObjectHandle object, short componentIndex, const TXString &componentName);
		virtual Boolean VCOM_CALLTYPE SetComponentPenColors(MCObjectHandle object, short componentIndex, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor);
		virtual Boolean VCOM_CALLTYPE SetComponentPenWeights(MCObjectHandle object, short componentIndex, Uint8 leftPenWeight, Uint8 rightPenWeight);
		virtual Boolean VCOM_CALLTYPE SetComponentUseFillClassAttr(MCObjectHandle object, short componentIndex, Boolean useFillClassAttributes);
		virtual Boolean VCOM_CALLTYPE SetComponentUsePenClassAttr(MCObjectHandle object, short componentIndex, Boolean useLeftPenClassAttributes, Boolean useRightPenClassAttributes);
		virtual Boolean VCOM_CALLTYPE SetComponentWidth(MCObjectHandle object, short componentIndex, WorldCoord width);
		virtual void VCOM_CALLTYPE SetConstraintValue(MCObjectHandle constraint, double_param value);
		virtual Boolean VCOM_CALLTYPE SetCustomDimensionStandardVariable(short dimensionIndex, short fieldSelector, const TVariableBlock& value);
		virtual Boolean VCOM_CALLTYPE SetCustomObjectColor(MCObjectHandle objectHand, int iTagID, ColorRef inColorRef);
		virtual Boolean VCOM_CALLTYPE SetCustomObjectControlPointVisibility(MCObjectHandle objectHand, short controlPtIndex, Boolean setVisible);
		virtual Boolean VCOM_CALLTYPE SetCustomObjectPath(MCObjectHandle objectHand, MCObjectHandle pathHand);
		virtual Boolean VCOM_CALLTYPE SetCustomObjectProfileGroup(MCObjectHandle objectHand, MCObjectHandle profileGroupHand);
		virtual void VCOM_CALLTYPE SetDefinition(MCObjectHandle h, MCObjectHandle newDef);
		virtual Boolean VCOM_CALLTYPE SetObjectProperty(Sint32 inCodeRefID, Sint32 inPropID, Boolean inValue);
		virtual Boolean VCOM_CALLTYPE SetObjectPropertyChar(Sint32 inCodeRefID, Sint32 inPropID, unsigned char inValue);
		virtual Boolean VCOM_CALLTYPE SetObjectVariable(MCObjectHandle theObject, short setSelector, const TVariableBlock& value);
		virtual void VCOM_CALLTYPE SetParameterVisibility(MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetVisible);
		virtual void VCOM_CALLTYPE SetRoofEdge(MCObjectHandle object, short index, const WorldPt& vertexPt, double_param slope, WorldCoord projection, WorldCoord eaveHeight);
		virtual Boolean VCOM_CALLTYPE SetSingularConstraint(short type, MCObjectHandle obj, short vertexA, short vertexB);
		virtual Boolean VCOM_CALLTYPE SetViewportClassVisibility(MCObjectHandle viewportHandle, InternalIndex classIndex, short visibilityType);
		virtual Boolean VCOM_CALLTYPE SetViewportCropObject(MCObjectHandle viewportHandle, MCObjectHandle cropHandle);
		virtual Boolean VCOM_CALLTYPE SetViewportLayerVisibility(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short visibilityType);
		virtual Boolean VCOM_CALLTYPE TrimToSelectedObjects(MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2);
		virtual Boolean VCOM_CALLTYPE UpdateConstraintModel();
		virtual void VCOM_CALLTYPE UpdateViewport(MCObjectHandle viewportHandle);
		virtual Boolean VCOM_CALLTYPE ViewportHasCropObject(MCObjectHandle viewportHandle);
		virtual short VCOM_CALLTYPE GSCountResources(OSType inType, Boolean lookOnlyInCurrentFile = true);
		virtual short VCOM_CALLTYPE GSGetApplicationResFile(short selector);
		virtual short VCOM_CALLTYPE GSGetCurrentResFile();
		virtual GSHandle VCOM_CALLTYPE GSGetIndResource(OSType inType, short inIndex, short& outID, Boolean lookOnlyInCurrentFile = true);
		inline GSHandle	GS_HIDDEN_VISIBILITY GSGetResource(OSType type, short id, Boolean unused=true) {  const char *vwr = DEFAULTVWRIDENTIFIER; GSHandle h; void *in[] = { &type, &id, (void*)vwr }; gSDK->Kludge(3607, in, &h); return h; }
		virtual GSHandle VCOM_CALLTYPE DEPRECATED_1001(OSType type, short id, Boolean lookOnlyInCurrentFile = true);
		virtual void VCOM_CALLTYPE GSGetResourceName(OSType inType, short inID, TXString& outName, Boolean lookOnlyInCurrentFile = true);
		virtual void VCOM_CALLTYPE GSReleaseResource(GSHandle theResource);
		virtual void VCOM_CALLTYPE GSRemoveResource(OSType inType, short inID);
		virtual void VCOM_CALLTYPE GSSetResourceName(OSType inType, short inID, const TXString& inName, Boolean lookOnlyInCurrentFile = true);
		virtual void VCOM_CALLTYPE GSUseResFile(short inFileID);
		virtual Boolean VCOM_CALLTYPE GSWriteResource(GSHandle inResource, OSType inType, short inID);
		virtual MCObjectHandle VCOM_CALLTYPE FirstSelectedObject();
		virtual void VCOM_CALLTYPE GetSelectionBounds(WorldRect& bounds, BoundsType type = kRefreshBounds);
		virtual Sint32 VCOM_CALLTYPE GetSelectionBoundsCube(WorldCube &theCube);
		virtual void VCOM_CALLTYPE MoveSelection(WorldCoord dx, WorldCoord dy);
		virtual void VCOM_CALLTYPE MoveSelection3D(WorldCoord dx, WorldCoord dy, WorldCoord dz);
		virtual void VCOM_CALLTYPE RotateSelectionN(const WorldPt& rotCen, double_param rotAngle);
		virtual void VCOM_CALLTYPE ScaleSelectionN(const WorldPt& scaleCen, double_param scaleX, double_param scaleY);
		virtual Boolean VCOM_CALLTYPE AddText(MCObjectHandle textBlock, Sint32 beforeChar, Handle newText);
		virtual Boolean VCOM_CALLTYPE AddTextFromBuffer(MCObjectHandle textBlock, Sint32 beforeChar, const UCChar* buffer, Sint32 bufferSize);
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextBlock(const TXString& textStr, const WorldPt& textOrigin, Boolean fixedSize, WorldCoord width);
		virtual void VCOM_CALLTYPE DeleteText(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars);
		virtual Sint32 VCOM_CALLTYPE GetCharNumFromPoint(MCObjectHandle textBlock, const WorldPt& pt);
		virtual TXString VCOM_CALLTYPE GetTextChars(MCObjectHandle textBlock);
		virtual Boolean VCOM_CALLTYPE GetTextCharsToBuffer(MCObjectHandle textBlock, void* buffer, Sint32& bufferSize);
		virtual void VCOM_CALLTYPE GetTextColor(MCObjectHandle textBlock, Sint32 charNum, ColorRef& charColor);
		virtual void VCOM_CALLTYPE GetTextFontIndex(MCObjectHandle textBlock, Sint32 charNum, short& fontIndex);
		virtual void VCOM_CALLTYPE GetTextJustification(MCObjectHandle textBlock, short& justification);
		virtual Sint32 VCOM_CALLTYPE GetTextLength(MCObjectHandle textBlock);
		virtual void VCOM_CALLTYPE GetTextLineHeight(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& height);
		virtual void VCOM_CALLTYPE GetTextOrientationN(MCObjectHandle h, double_gs& angle, short& flipState);
		virtual void VCOM_CALLTYPE GetTextSize(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& charSize);
		virtual void VCOM_CALLTYPE GetTextStyle(MCObjectHandle textBlock, Sint32 charNum, unsigned char& charStyle);
		virtual void VCOM_CALLTYPE GetTextVerticalAlignment(MCObjectHandle textBlock, short& verticalAlignment);
		virtual void VCOM_CALLTYPE GetTextVerticalSpacing(MCObjectHandle textBlock, short& spacing, WorldCoord& height);
		virtual Boolean VCOM_CALLTYPE GetTextWidth(MCObjectHandle textBlock, WorldCoord& width);
		virtual Boolean VCOM_CALLTYPE GetTextWrap(MCObjectHandle textBlock, Boolean& wrapped);
		virtual void VCOM_CALLTYPE SetTextColor(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, ColorRef charColor);
		virtual void VCOM_CALLTYPE SetTextFontIndex(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, short fontIndex);
		virtual void VCOM_CALLTYPE SetTextJustification(MCObjectHandle textBlock, short justification);
		virtual void VCOM_CALLTYPE SetTextOrientationN(MCObjectHandle h, double_param angle, short flipState);
		virtual void VCOM_CALLTYPE SetTextSize(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, WorldCoord charSize);
		virtual void VCOM_CALLTYPE SetTextStyle(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char charStyle);
		virtual void VCOM_CALLTYPE SetTextVerticalAlignment(MCObjectHandle textBlock, short verticalAlignment);
		virtual void VCOM_CALLTYPE SetTextVerticalSpacing(MCObjectHandle textBlock, short spacing, WorldCoord height);
		virtual void VCOM_CALLTYPE SetTextWidth(MCObjectHandle textBlock, WorldCoord width);
		virtual void VCOM_CALLTYPE SetTextWrap(MCObjectHandle textBlock, Boolean wrapped);
		virtual void VCOM_CALLTYPE SpellCheckTextBuffer(GSHandle charsHandle, Boolean textChanged);
		virtual void VCOM_CALLTYPE AttachDefaultTextureSpace(MCObjectHandle object, short multiPartID);
		virtual MCObjectHandle VCOM_CALLTYPE CreateShaderRecord(MCObjectHandle texture, Sint32 family, Sint32 prototype);
		virtual MCObjectHandle VCOM_CALLTYPE CreateTexture();
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextureBitmap();
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextureBitmapFromPaintNode(MCObjectHandle paintNodeObject);
		virtual void VCOM_CALLTYPE DeleteTextureSpace(MCObjectHandle object, short multiPartID);
		virtual Boolean VCOM_CALLTYPE EditShaderRecord(MCObjectHandle shaderRecord);
		virtual Boolean VCOM_CALLTYPE EditTexture(MCObjectHandle texture);
		virtual void VCOM_CALLTYPE Deprecated883(); // EditTextureBitmap
		virtual Boolean VCOM_CALLTYPE EditTextureSpace(MCObjectHandle texturedObject, short multiPartID);
		virtual InternalIndex VCOM_CALLTYPE GetClGenTexture(InternalIndex index);
		virtual void VCOM_CALLTYPE GetClRoofTextures(InternalIndex index, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer);
		virtual Boolean VCOM_CALLTYPE GetClUseTexture(InternalIndex index);
		virtual void VCOM_CALLTYPE GetClWallTextures(InternalIndex index, InternalIndex& right, InternalIndex& left, InternalIndex& center);
		virtual MCObjectHandle VCOM_CALLTYPE GetShaderRecord(MCObjectHandle parentNode, Sint32 family);
		virtual InternalIndex VCOM_CALLTYPE GetTextureRef(MCObjectHandle object, short multiPartID, Boolean resolveByClass);
		virtual void VCOM_CALLTYPE GetTextures(MCObjectHandle h, InternalIndex& primaryTexture, InternalIndex& secondaryTexture, InternalIndex& tertiaryTexture);
		virtual MCObjectHandle VCOM_CALLTYPE GetTextureSpace(MCObjectHandle object, short multiPartID);
		virtual InternalIndex VCOM_CALLTYPE GetVPClassGenTexture(MCObjectHandle viewport, InternalIndex classIndex);
		virtual void VCOM_CALLTYPE GetVPClassRoofTextures(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer);
		virtual void VCOM_CALLTYPE GetVPClassWallTextures(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& right, InternalIndex& left, InternalIndex& center);
		virtual void VCOM_CALLTYPE SetClGenTexture(InternalIndex index, InternalIndex texture);
		virtual void VCOM_CALLTYPE SetClRoofTextures(InternalIndex index, InternalIndex top, InternalIndex edge, InternalIndex dormer);
		virtual void VCOM_CALLTYPE SetClUseTexture(InternalIndex index, Boolean use);
		virtual void VCOM_CALLTYPE SetClWallTextures(InternalIndex index, InternalIndex right, InternalIndex left, InternalIndex center);
		virtual void VCOM_CALLTYPE SetDefaultTextureSpace(MCObjectHandle object, MCObjectHandle space, short multiPartID);
		virtual void VCOM_CALLTYPE SetTextureRef(MCObjectHandle object, InternalIndex textureRef, short multiPartID);
	
		virtual Sint32 VCOM_CALLTYPE Deprecated943(short inHotSpotType, const WorldPt3& inLocation, Sint32 inCursorID, const TXString& inTip);
	
		virtual MCObjectHandleID VCOM_CALLTYPE AddToolPersistentDraw(GS_PersistentDrawProcPtr drawProcPtr, void *drawEnv);
		virtual MCObjectHandleID VCOM_CALLTYPE AddToolSnapGeometry(MCObjectHandle inSnapGeometry);
		virtual void VCOM_CALLTYPE BoxToolDraw();
		virtual Boolean VCOM_CALLTYPE ClearAllToolPts();
		virtual void VCOM_CALLTYPE ClearDataDisplayBar();
		virtual Sint32 VCOM_CALLTYPE ClickDragToolStatus();
		virtual Boolean VCOM_CALLTYPE CustomBarCreate(short inNumFields, CustomBarRefID& outCustomBarRefID);
		virtual Boolean VCOM_CALLTYPE CustomBarGetFieldInfo(CustomBarRefID inCustomBarID, short inFieldIndex, CustomBarFieldInfo& inFieldInfo);
		virtual Boolean VCOM_CALLTYPE CustomBarInstall(CustomBarRefID inCustomBarID);
		virtual Boolean VCOM_CALLTYPE CustomBarRelease(CustomBarRefID inCustomBarRefID);
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldAngle(CustomBarRefID inCustomBarID, short inFieldIndex, const double& inDegrees);
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldInfo(CustomBarRefID inCustomBarID, short inFieldIndex, const CustomBarFieldInfo& inFieldInfo);
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldWorldCoord(CustomBarRefID inCustomBarID, short inFieldIndex, const WorldCoord& inCoordVal);
		virtual void VCOM_CALLTYPE Default2DToolDraw();
		virtual void VCOM_CALLTYPE Default3DToolDraw();
		virtual void VCOM_CALLTYPE DrawCoordArcN(const WorldRect& theBox, double_param startAngle, double_param sweepAngle);
		virtual void VCOM_CALLTYPE DrawCoordEllipse(WorldRect& theBox);
		virtual void VCOM_CALLTYPE DrawCoordLine(const WorldPt& p1, const WorldPt& p2);
		virtual void VCOM_CALLTYPE DrawCoordLine3D(const WorldPt3& p1, const WorldPt3& p2);
		virtual void VCOM_CALLTYPE DrawCoordRect(const WorldRect& theBox);
		virtual void VCOM_CALLTYPE DrawDataDisplayBar(Boolean drawFramesFirst = false);
		virtual void VCOM_CALLTYPE DrawNurbsObject(MCObjectHandle h);
		virtual void VCOM_CALLTYPE DrawObject(MCObjectHandle h, Boolean doSelect);
		virtual void VCOM_CALLTYPE GetCoords(WorldPt& p, ViewPt& m);
		virtual Sint32 VCOM_CALLTYPE GetNumToolPts();
		virtual const ICoreToolAccess* VCOM_CALLTYPE GetToolCoreInterface();
		virtual Boolean VCOM_CALLTYPE GetToolPt2D(Sint32 inIndex, WorldPt& outToolPoint);
		virtual Boolean VCOM_CALLTYPE GetToolPt3D(Sint32 inIndex, WorldPt3& outToolPoint);
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrent2D(WorldPt& outToolPoint);
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrent3D(WorldPt3& outToolPt);
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrentViewPt(ViewPt& outToolPt);
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrentWorkingPlane(WorldPt3& outToolPt);
		virtual Boolean VCOM_CALLTYPE GetToolPtViewPoint(Sint32 inIndex, ViewPt& outToolPoint);
		virtual Boolean VCOM_CALLTYPE GetToolPtWorkingPlane(Sint32 inIndex, WorldPt3& outToolPoint);
		virtual void VCOM_CALLTYPE InstallConstraintAlong3DLine(const Ray& inConstraintDescription);
		virtual void VCOM_CALLTYPE Interactive2DDraw( short options, short shiftConsMode, GS_I2DDrawProcPtr drawProc, void *env);
		virtual Sint32 VCOM_CALLTYPE OnePointToolStatus();
		virtual Sint32 VCOM_CALLTYPE PolyToolStatus();
		virtual Boolean VCOM_CALLTYPE PopLastToolPt();
		virtual void VCOM_CALLTYPE RemoveHotSpot(HotSpotRefID inHotSpotID);
		virtual void VCOM_CALLTYPE RemoveToolPersistentDraw(MCObjectHandleID persistentDrawRefID);
		virtual void VCOM_CALLTYPE RemoveToolSnapGeometry(MCObjectHandleID inSnapGeometryID);
		virtual Boolean VCOM_CALLTYPE RunTemporary2DTool( Sint32& ioUserData, ToolDefProcPtr inToolProc);
		virtual Boolean VCOM_CALLTYPE RunTemporary3DTool( Sint32& ioUserData, ToolDefProcPtr inToolProc);
		virtual void VCOM_CALLTYPE SetCursorMode();
		virtual void VCOM_CALLTYPE SetDataDisplayBarField(short fieldNum, BarNumberType barType, const TXString& inBarLabel);
		virtual void VCOM_CALLTYPE SetDimUserBarValue(short fieldNum, WorldCoord dimVal);
		virtual void VCOM_CALLTYPE SetFloatUserBarValueN(short fieldNum, double_param floatVal, short numPlaces);
		virtual void VCOM_CALLTYPE SetTextUserBarValue(short fieldNum, const TXString& textVal);
		virtual Boolean VCOM_CALLTYPE SetToolProperty(Sint32 inCodeRefID, Sint32 inToolPropID, Boolean inValue);
		virtual Boolean VCOM_CALLTYPE SetToolPropertyChar(Sint32 inCodeRefID, Sint32 inToolPropID, char inValue);
		virtual Sint32 VCOM_CALLTYPE ThreePointToolStatus();
		virtual HotSpotRefID VCOM_CALLTYPE TrackHotSpot(Boolean& outIs3d, WorldPt3& outLocation);
		virtual void VCOM_CALLTYPE TrackTool(MCObjectHandle& overObject, short& overPart, SintptrT& code);
		virtual Sint32 VCOM_CALLTYPE TwoPointToolStatus();
		virtual void VCOM_CALLTYPE AddObjectToContainer(MCObjectHandle h, MCObjectHandle container);
		virtual MCObjectHandle VCOM_CALLTYPE AuxOwner(MCObjectHandle h);
		virtual void VCOM_CALLTYPE DeleteObject(MCObjectHandle h, Boolean useUndo = true);
		virtual Boolean VCOM_CALLTYPE FindHandleDeep(MCObjectHandle handleToFind, MCObjectHandle firstObjectInSearchList, MCObjectHandle& unused);
		virtual MCObjectHandle VCOM_CALLTYPE FirstMemberObj(MCObjectHandle h);
		virtual MCObjectHandle VCOM_CALLTYPE GetDefaultContainer();
		virtual MCObjectHandle VCOM_CALLTYPE GetDrawingHeader();
		virtual MCObjectHandle VCOM_CALLTYPE GetHatchListHeader();
		virtual MCObjectHandle VCOM_CALLTYPE GetSymbolLibraryHeader();
		virtual void VCOM_CALLTYPE InsertObjectAfter(MCObjectHandle h, MCObjectHandle afterObject);
		virtual void VCOM_CALLTYPE InsertObjectBefore(MCObjectHandle h, MCObjectHandle beforeObject);
		virtual MCObjectHandle VCOM_CALLTYPE LastMemberObj(MCObjectHandle h);
		virtual MCObjectHandle VCOM_CALLTYPE NextObject(MCObjectHandle h);
		virtual MCObjectHandle VCOM_CALLTYPE ParentObject(MCObjectHandle h);
		virtual MCObjectHandle VCOM_CALLTYPE PrevObject(MCObjectHandle h);
		virtual MCObjectHandle VCOM_CALLTYPE SearchForAncestorType(Sint16 objectType, MCObjectHandle h);
		virtual void VCOM_CALLTYPE SetPageBounds(const WorldRect& bounds);
		virtual Boolean VCOM_CALLTYPE AcquireExportPDFSettingsAndLocation(Boolean inbSeparateDocuments);
		virtual void VCOM_CALLTYPE ClosePDFDocument();
		virtual short VCOM_CALLTYPE ExportPDFPages(const TXString& inSavedViewNameStr);
		virtual Boolean VCOM_CALLTYPE OpenPDFDocument(const TXString& inFileNameStr);
		virtual Boolean VCOM_CALLTYPE AddAfterMoveObject(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE AddAfterSwapObject(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE AddBeforeMoveObject(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE AddBeforeSwapObject(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE AddBothSwapObject(MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE AddCoordMoveObject2D(MCObjectHandle h, WorldCoord dx, WorldCoord dy);
		virtual Boolean VCOM_CALLTYPE AddCoordMoveObject3D(MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz);
		virtual Boolean VCOM_CALLTYPE EndUndoEvent();
		virtual void VCOM_CALLTYPE NameUndoEvent(const TXString& name);
		virtual Boolean VCOM_CALLTYPE NonUndoableActionOK();
		virtual void VCOM_CALLTYPE SetUndoMethod(short undoType);
		virtual void VCOM_CALLTYPE SupportUndoAndRemove();
		virtual void VCOM_CALLTYPE UndoAndRemove();
		virtual void VCOM_CALLTYPE AngleToStringN(double_param angle, TXString& s);
		virtual void VCOM_CALLTYPE AssociateLinearDimension(MCObjectHandle h, Boolean selectedObjectsMode);
		virtual Boolean VCOM_CALLTYPE CallPluginLibrary(const TXString& routineName, PluginLibraryArgTable* argumentTable, Sint32 status);
		virtual void VCOM_CALLTYPE ClipSurface(MCObjectHandle h1, MCObjectHandle h2);
		virtual MCObjectHandle VCOM_CALLTYPE CombineIntoSurface(const WorldPt& insidePt);
		virtual void VCOM_CALLTYPE CoordToDimString(WorldCoord c, TXString& s);
		virtual Sint16 VCOM_CALLTYPE CStringCompare(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags);
		virtual Boolean VCOM_CALLTYPE CStringEqual(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags);
		virtual void VCOM_CALLTYPE DisableModules(Sint32 modules);
		virtual void VCOM_CALLTYPE DisplayContextHelpOfCurrentPlugin();
		virtual Boolean VCOM_CALLTYPE DisplayContextualHelp(const TXString& helpIdentifier);
		virtual void VCOM_CALLTYPE DisplayOrganizationDialog(short tabToSelect);
		virtual short VCOM_CALLTYPE DoMenuName(const TXString& name, short chunkIndex);
		virtual Sint32 VCOM_CALLTYPE DoProgramAction(short actionSelector, void* actionEnv);
		virtual void VCOM_CALLTYPE DoubleToString(TNumStyleClass inNumStyle,  Byte inAccuracy, Byte inFormat, double_param inDouble, TXString& outString);
		virtual void VCOM_CALLTYPE DrawScreen(const ViewRect& clipRect, Boolean isLastFrame = true);
		virtual void VCOM_CALLTYPE EllipseEllipseIntersect(const WorldRect& e1, const WorldRect& e2, Sect4Struct& sects);
		virtual Sint32 VCOM_CALLTYPE ExternalNameToID(const TXString& fnName);
		virtual short VCOM_CALLTYPE FontIndexFromName(const TXString& fontName);
		virtual void VCOM_CALLTYPE FontNameFromIndex(short fontIndex, TXString& fontName, Boolean useMappingTable);
		virtual void VCOM_CALLTYPE GetActiveSerialNumber(TXString& outSerialNumber);
		virtual Boolean VCOM_CALLTYPE GetCallBackInval();
		virtual short VCOM_CALLTYPE GetCurrentMode();
		virtual int VCOM_CALLTYPE GetDataBarCursorVisState();
		virtual Sint32 VCOM_CALLTYPE GetEnabledModules();
		virtual void VCOM_CALLTYPE GetHostInfo(short& hostID, Byte& version, Byte& majorRev, Byte& minorRev, TXString& outProductName, TXString& outProductVersion);
		virtual void VCOM_CALLTYPE GetModifierFlags(Boolean& optionFlag, Boolean& cmdFlag, Boolean& shiftFlag);
		virtual void VCOM_CALLTYPE GetProduct(short& product, Sint32& modules);
		virtual Boolean VCOM_CALLTYPE GetSavedSetting(const TXString& category, const TXString& setting, TXString& value);
		virtual void VCOM_CALLTYPE HandlePendingUpdatesAndActivates();
		virtual void VCOM_CALLTYPE HilitePalettesAndTopDocument(Boolean doHilite);
		virtual MCObjectHandle VCOM_CALLTYPE IntersectObjects(MCObjectHandle obj1, MCObjectHandle obj2, Boolean onlyOnObjs);
		virtual Boolean VCOM_CALLTYPE Kludge(short selector, void* in, void* out);
		virtual void VCOM_CALLTYPE LineEllipseIntersect(const WorldPt& a1, const WorldPt& a2, const WorldRect& r, Sect2Struct& sects);
		virtual void VCOM_CALLTYPE LineLineIntersect(const WorldPt& a1, const WorldPt& a2, const WorldPt& b1, const WorldPt& b2, Boolean& parallel, Boolean& intOnLines, WorldPt& sect);
		virtual MCObjectHandle VCOM_CALLTYPE ObjectNearCoordPt(const WorldPt& p);
		virtual Boolean VCOM_CALLTYPE PlaySoundResource(Handle soundResource, Boolean async, Boolean forcePlay);
		virtual Boolean VCOM_CALLTYPE PointInsidePoly(const WorldPt& checkPt, MCObjectHandle h);
		virtual Boolean VCOM_CALLTYPE PointOnPolyEdge(const WorldPt& checkPt, MCObjectHandle h, WorldCoord checkRadius);
		virtual Sint32 VCOM_CALLTYPE RegisterExternal(const TXString& fileName, short codeResID, OSType codeResType);
		virtual Boolean VCOM_CALLTYPE RegisterNotificationProcedure(StatusProcPtr proc, OSType whichChange);
		virtual void VCOM_CALLTYPE SetCallBackInval(Boolean turnInvalOn);
		virtual void VCOM_CALLTYPE SetPersistentHighlight(MCObjectHandle theObject, Boolean highlightState);
		virtual void VCOM_CALLTYPE SetSavedSetting(const TXString& category, const TXString& setting, const TXString& value);
		virtual Boolean VCOM_CALLTYPE StringToAngleN(const TXString& s, double_gs& angle);
		virtual Boolean VCOM_CALLTYPE StringToDouble(TNumStyleClass inNumStyle, const TXString& inString, double_gs& outDouble);
		virtual Boolean VCOM_CALLTYPE SymbolContainsLight(MCObjectHandle symbol);
		virtual void VCOM_CALLTYPE ToggleObjectHighlight(MCObjectHandle theObject);
		virtual void VCOM_CALLTYPE UnregisterNotificationProcedure(StatusProcPtr proc, OSType whichChange);
		virtual Boolean VCOM_CALLTYPE VerifyPluginLibrary(const TXString& routineName);
		virtual void VCOM_CALLTYPE GetPerspectiveInfo(MCObjectHandle theLayer, WorldCoord& perspectiveDistance, WorldCoord& clipDistance, WorldRect& clipRect);
		virtual short VCOM_CALLTYPE GetProjection(MCObjectHandle theLayer);
		virtual short VCOM_CALLTYPE GetRenderMode(MCObjectHandle theLayer);
		virtual short VCOM_CALLTYPE GetScreenDPI();
		virtual void VCOM_CALLTYPE GetViewCenter(WorldPt& center);
		virtual void VCOM_CALLTYPE GetViewMatrix(MCObjectHandle theLayer, TransformMatrix& theMat);
		virtual void VCOM_CALLTYPE GetWorkingPlane(Axis &theAxis);
		virtual void VCOM_CALLTYPE NewCurrentViewMatrix(const TransformMatrix& theMat, Boolean interactive);
		virtual void VCOM_CALLTYPE NewWorkingPlane(const Axis &theAxis);
		virtual void VCOM_CALLTYPE PreviewDrawFrame(Handle thisPreview, Boolean selectedOnly = false);
		virtual void VCOM_CALLTYPE PreviewFinish(Handle& thisPreview);
		virtual Handle VCOM_CALLTYPE PreviewSetup(Boolean doDynamicSpeedups = true, double_param targetFPS = 30.0, Boolean drawGroundPlane = true, Boolean drawPage = true, Boolean drawCropRect = true);
		virtual void VCOM_CALLTYPE RedrawRect(const WorldRect& redrawR);
		virtual void VCOM_CALLTYPE SetViewCenter(const WorldPt& center);
		virtual void VCOM_CALLTYPE SetViewMatrix(MCObjectHandle theLayer, const TransformMatrix& theMatrix);
		virtual void VCOM_CALLTYPE SetWorkingPlaneAxis(const Vector &si, const Vector &sj, const Vector &sk);
		virtual void VCOM_CALLTYPE SetWorkingPlaneVertex(const WorldPt3 &v);
		virtual void VCOM_CALLTYPE SetZoomFactorN(double_param zoomFac);
		virtual void VCOM_CALLTYPE ViewRotWorldZN(double_param angle, Boolean interactive);
		virtual Boolean VCOM_CALLTYPE WorldRect2ViewRect(const WorldRect& wRect, ViewRect& vRect);
		virtual short VCOM_CALLTYPE AddBreak(MCObjectHandle theWall, WorldCoord off, short breakType, void* breakData);
		virtual void VCOM_CALLTYPE DeleteBreak(MCObjectHandle theWall, short index);
		virtual void VCOM_CALLTYPE ForEachBreak( MCObjectHandle theWall, GS_ForEachBreakProcPtr action, void* actionEnv);
		virtual void VCOM_CALLTYPE Deprecated1065(); // GetLayerDeltaZOffset
		virtual void VCOM_CALLTYPE Deprecated1066(); // GetLinkHeightToLayerDeltaZ
		virtual void VCOM_CALLTYPE GetPolyBreakGeometry(MCObjectHandle theWall, short breakIndex, MCObjectHandle& polyline);
		virtual void VCOM_CALLTYPE GetWallCaps(MCObjectHandle theWall, Boolean &leftCap, Boolean &rightCap, Boolean &round);
		virtual void VCOM_CALLTYPE GetWallCapsOffsets(MCObjectHandle theWall, WorldCoord &leftCapLeftOffset, WorldCoord &leftCapRightOffset, WorldCoord &rightCapLeftOffset, WorldCoord &rightCapRightOffset);
		virtual void VCOM_CALLTYPE GetWallCornerHeights(MCObjectHandle theWall, WorldCoord& startHeightTop, WorldCoord& startHeightBottom, WorldCoord& endHeightTop, WorldCoord& endHeightBottom);
		virtual Boolean VCOM_CALLTYPE JoinWalls(MCObjectHandle firstWall, MCObjectHandle secondWall,  const WorldPt& firstWallPt, const WorldPt& secondWallPt, JoinModifierType joinModifier, Boolean capped, Boolean showAlerts);
		virtual void VCOM_CALLTYPE MoveWallByOffset(MCObjectHandle theWall, WorldCoord& offset);
		virtual void VCOM_CALLTYPE ReverseWallSides(MCObjectHandle theWall);
		virtual void VCOM_CALLTYPE SetAsPolyBreak(MCObjectHandle& thePolyline, MCObjectHandle theWall, short breakIndex);
		virtual void VCOM_CALLTYPE SetBreak(MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData);
		virtual void VCOM_CALLTYPE Deprecated1076(); // SetLayerDeltaZOffset
		virtual void VCOM_CALLTYPE Deprecated1077(); // SetLinkHeightToLayerDeltaZ
		virtual Boolean VCOM_CALLTYPE SetWallCaps(MCObjectHandle theWall, const Boolean &leftCap, const Boolean &rightCap, const Boolean &round);
		virtual Boolean VCOM_CALLTYPE SetWallCapsOffsets(MCObjectHandle theWall, WorldCoord leftCapLeftOffset, WorldCoord leftCapRightOffset, WorldCoord rightCapLeftOffset, WorldCoord rightCapRightOffset);
		virtual Boolean VCOM_CALLTYPE SetWallCornerHeights(MCObjectHandle theWall, WorldCoord startHeightTop, WorldCoord startHeightBottom, WorldCoord endHeightTop, WorldCoord endHeightBottom);
		virtual Boolean VCOM_CALLTYPE SetWallStyle(MCObjectHandle theWall, InternalIndex wallStyle, WorldCoord selectedOffset, WorldCoord replacingOffset);
		virtual Boolean VCOM_CALLTYPE SetWallWidth(MCObjectHandle theWall, WorldCoord newWidth);
		virtual void VCOM_CALLTYPE WrapGetWallWidth(MCObjectHandle theWall, double_gs& outCoordLen);
		virtual Boolean VCOM_CALLTYPE GetScreenSize(ViewRect& screenRect);
		virtual void VCOM_CALLTYPE AutoFitWorksheetRowHeights(MCObjectHandle worksheet, short fromRow, short toRow);
		virtual void VCOM_CALLTYPE ClearWorksheetCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		virtual MCObjectHandle VCOM_CALLTYPE CreateWorksheet(const TXString& name, short rows, short columns);
		virtual MCObjectHandle VCOM_CALLTYPE CreateWorksheetImage(MCObjectHandle worksheet, const WorldPt& topLeftCorner);
		virtual void VCOM_CALLTYPE DeleteWorksheetColumns(MCObjectHandle worksheet, short startColumn, short numColumns);
		virtual void VCOM_CALLTYPE DeleteWorksheetRows(MCObjectHandle worksheet, short startRow, short numRows);
		virtual MCObjectHandle VCOM_CALLTYPE GetTopVisibleWorksheet();
		virtual void VCOM_CALLTYPE GetWkSheetSubrowCellActualString(MCObjectHandle worksheet, const ViewPt& cell, Sint16 subrow, TXString& cellString);
		virtual void VCOM_CALLTYPE GetWorksheetCellAlignment(MCObjectHandle worksheet, const ViewPt& cell, short& cellAlignment);
		virtual void VCOM_CALLTYPE GetWorksheetCellBorder(MCObjectHandle worksheet, const ViewPt& cell, Boolean& top, Boolean& left, Boolean& bottom, Boolean& right);
		virtual void VCOM_CALLTYPE GetWorksheetCellFill(MCObjectHandle worksheet, const ViewPt& cell, short& style, ColorRef& bgcolor, ColorRef& fgcolor, short& fillpattern);
		virtual void VCOM_CALLTYPE GetWorksheetCellFormula(MCObjectHandle worksheet, const ViewPt& cell, TXString& formula);
		virtual void VCOM_CALLTYPE GetWorksheetCellNumberFormat(MCObjectHandle worksheet, const ViewPt& cell, short& style, short& accuracy, TXString& leaderString, TXString& trailerString);
		virtual void VCOM_CALLTYPE GetWorksheetCellString(MCObjectHandle worksheet, const ViewPt& cell, TXString& cellString);
		virtual void VCOM_CALLTYPE GetWorksheetCellTextFormat(MCObjectHandle worksheet, const ViewPt& cell, short& fontIndex, short& size, short& style);
		virtual void VCOM_CALLTYPE GetWorksheetCellTextAngle(MCObjectHandle worksheet, const ViewPt& cell, short& angle);
		virtual void VCOM_CALLTYPE GetWorksheetCellTextColor(MCObjectHandle worksheet, const ViewPt& cell, ColorRef& color);
		virtual void VCOM_CALLTYPE GetWorksheetCellValue(MCObjectHandle worksheet, const ViewPt& cell, double& cellValue);
		virtual void VCOM_CALLTYPE GetWorksheetCellVertAlignment(MCObjectHandle worksheet, const ViewPt& cell, short& vAlignment);
		virtual void VCOM_CALLTYPE GetWorksheetCellWrapTextFlag(MCObjectHandle worksheet, const ViewPt& cell, Boolean& wrapTextFlag);
		virtual void VCOM_CALLTYPE GetWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, short& sort1, short& sort2, short& sort3, short& sum1, short& sum2, short& sum3);
		virtual void VCOM_CALLTYPE GetWorksheetColumnWidth(MCObjectHandle worksheet, short column, short& width);
		virtual MCObjectHandle VCOM_CALLTYPE GetWorksheetFromImage(MCObjectHandle worksheetImage);
		virtual MCObjectHandle VCOM_CALLTYPE GetWorksheetImage(MCObjectHandle worksheet);
		virtual Boolean VCOM_CALLTYPE GetWorksheetMergedCellRange(MCObjectHandle worksheet, const ViewPt& cell, ViewPt& topLeftCell, ViewPt& bottomRightCell);
		virtual void VCOM_CALLTYPE GetWorksheetPlacement(MCObjectHandle worksheet, ViewRect& windowPosition);
		virtual void VCOM_CALLTYPE GetWorksheetRowColumnCount(MCObjectHandle worksheet, short& numRows, short& numColumns);
		virtual void VCOM_CALLTYPE GetWorksheetRowHeight(MCObjectHandle worksheet, short row, short& height);
		virtual void VCOM_CALLTYPE GetWorksheetRowHLockState(MCObjectHandle worksheet, short row, Boolean& lockState);
		virtual void VCOM_CALLTYPE GetWorksheetSelection(MCObjectHandle worksheet, ViewPt& currentCell, ViewPt& topLeftRangeCell, short& topRangeSubrow, ViewPt& bottomRightRangeCell, short& bottomRangeSubrow);
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCellString(MCObjectHandle worksheet, const ViewPt& cell, short subrow, TXString& cellString);
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCellValue(MCObjectHandle worksheet, const ViewPt& cell, short subrow, double& cellValue);
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCount(MCObjectHandle worksheet, short databaseRow, short& numSubrows);
		virtual void VCOM_CALLTYPE InsertWorksheetColumns(MCObjectHandle worksheet, short beforeColumn, short numColumns);
		virtual void VCOM_CALLTYPE InsertWorksheetRows(MCObjectHandle worksheet, short beforeRow, short numRows);
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetCell(MCObjectHandle worksheet, const ViewPt& cell);
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetRange(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetSubrowCell(MCObjectHandle worksheet, const ViewPt& cell, short subrow);
		virtual Boolean VCOM_CALLTYPE IsWorksheetCellNumber(MCObjectHandle worksheet, const ViewPt& cell);
		virtual Boolean VCOM_CALLTYPE IsWorksheetCellString(MCObjectHandle worksheet, const ViewPt& cell);
		virtual Boolean VCOM_CALLTYPE IsWorksheetDatabaseRow(MCObjectHandle worksheet, short databaseRow);
		virtual Boolean VCOM_CALLTYPE IsWorksheetSubrowCellNumber(MCObjectHandle worksheet, const ViewPt& cell, short subrow);
		virtual Boolean VCOM_CALLTYPE IsWorksheetSubrowCellString(MCObjectHandle worksheet, const ViewPt& cell, short subrow);
		virtual Boolean VCOM_CALLTYPE IsWorksheetVisible(MCObjectHandle worksheet);
		virtual void VCOM_CALLTYPE RecalculateWorksheet(MCObjectHandle worksheet);
		virtual void VCOM_CALLTYPE SetTopVisibleWorksheet(MCObjectHandle worksheet);
		virtual void VCOM_CALLTYPE SetWorksheetCellAlignment(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short cellAlignment);
		virtual void VCOM_CALLTYPE SetWorksheetCellBorder(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline);
		virtual void VCOM_CALLTYPE SetWorksheetCellBorders(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline, Boolean insideHorz, Boolean insideVert);
		virtual void VCOM_CALLTYPE SetWorksheetCellFill(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, ColorRef bgcolor, ColorRef fgcolor, short fillpattern);
		virtual void VCOM_CALLTYPE SetWorksheetCellFormula(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, const TXString& formula);
		virtual void VCOM_CALLTYPE SetWorksheetCellNumberFormat(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, short accuracy, const TXString& leaderString, const TXString& trailerString);
		virtual void VCOM_CALLTYPE SetWorksheetCellTextFormat(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short fontIndex, short size, short style);
		virtual void VCOM_CALLTYPE SetWorksheetCellTextAngle(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short angle);
		virtual void VCOM_CALLTYPE SetWorksheetCellTextColor(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, ColorRef color);
		virtual void VCOM_CALLTYPE SetWorksheetCellVertAlignment(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short vAlignment);
		virtual void VCOM_CALLTYPE SetWorksheetCellWrapTextFlag(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean wrapTextFlag);
		virtual void VCOM_CALLTYPE SetWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, short sort1, short sort2, short sort3, short sum1, short sum2, short sum3);
		virtual void VCOM_CALLTYPE SetWorksheetColumnWidth(MCObjectHandle worksheet, short fromColumn, short toColumn, short width);
		virtual void VCOM_CALLTYPE SetWorksheetCurrentCell(MCObjectHandle worksheet, const ViewPt& currentCell);
		virtual void VCOM_CALLTYPE SetWorksheetPlacement(MCObjectHandle worksheet, const ViewRect& windowPosition);
		virtual void VCOM_CALLTYPE SetWorksheetRowsHeight(MCObjectHandle worksheet, short fromRow, short toRow, short height, Boolean updatePalette, Boolean lockHeight);
		virtual void VCOM_CALLTYPE SetWorksheetSelection(MCObjectHandle worksheet, const ViewPt& currentCell, const ViewPt& topLeftRangeCell, short topRangeSubrow, const ViewPt& bottomRightRangeCell, short bottomRangeSubrow);
		virtual void VCOM_CALLTYPE ShowWorksheet(MCObjectHandle worksheet, Boolean show);
		virtual void VCOM_CALLTYPE ShowWorksheetDialog(short dialogType);
		virtual Boolean VCOM_CALLTYPE WorksheetMergeCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		virtual Boolean VCOM_CALLTYPE WorksheetSplitCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		virtual void VCOM_CALLTYPE GSCloseResFile(short inFileID);
		virtual void VCOM_CALLTYPE GetCurrentWorkspaceFile(TXString& outFileName);
		virtual short VCOM_CALLTYPE OpenExternalResFile(const TXString& inFileName, Byte fileAccessPerm = kFileReadWrite);
		virtual short VCOM_CALLTYPE OpenWorkspaceResFile(const TXString& inFileName, Boolean createNewFile = false, Byte fileAccessPerm = kFileReadWrite);
		virtual void VCOM_CALLTYPE SetWorkspaceFileToReload(const TXString& inFileName);
		virtual Boolean VCOM_CALLTYPE WSAddMenu(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuName);
		virtual Boolean VCOM_CALLTYPE WSAddMenuItem(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName, char inShortcutKey, Uint32 inShortcutKeyModifiers, const TXString& inSubMenuIdentifier);
		virtual Boolean VCOM_CALLTYPE WSAddTool(Sint32 inWorkspaceReference, const TXString& inToolIdentifier, char inShortcutKey, Uint32 inKeyModifiers);
		virtual Boolean VCOM_CALLTYPE WSAddToolPalette(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier);
		virtual Boolean VCOM_CALLTYPE WSAddToolSet(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize);
		virtual Boolean VCOM_CALLTYPE WSGetVersion(Sint32 inWorkspaceReference, Sint32* outWorkspaceVersion);
		virtual Boolean VCOM_CALLTYPE WSMenuAddMenuItem(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName);
		virtual Boolean VCOM_CALLTYPE WSMenuBarAddMenu(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier);
		virtual Boolean VCOM_CALLTYPE WSOpen(const TXString& inWorkspaceFileToOpen, Sint32 inFilePermissions, Sint32* outWorkspaceReference);
		virtual Boolean VCOM_CALLTYPE WSPaletteGetHomeCorner(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, short* outWindowHomeCorner);
		virtual Boolean VCOM_CALLTYPE WSPaletteSetHomeCorner(Sint32 inWorkspaceReference, const TXString& inPaletteIdentifier, short inWindowHomeCorner);
		virtual Boolean VCOM_CALLTYPE WSSetVersion(Sint32 inWorkspaceReference, Sint32 inWorkspaceVersion);
		virtual Boolean VCOM_CALLTYPE WSToolPaletteAddToolSet(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, const TXString& inToolSetIdentifier);
		virtual Boolean VCOM_CALLTYPE WSToolSetAddTool(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize);
		virtual Boolean VCOM_CALLTYPE WSToolSetAddToolChildToTool(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, const TXString& inParentToolIdentifier, const TXString& inChildToolIdentifier);
	
		// pre VW2009 - OS dependent
	public:
		//if _WINDOWS
		//		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iPatternIndex);
		//endif
		//if !_WIN_EXTERNAL_ && !_GSWINSDK_
		//		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPattern(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Pattern* &pPattern);
		//endif
		//if _WINDOWS
		//		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iPatternIndex);
		//endif
		//if !_WIN_EXTERNAL_ && !_GSWINSDK_
		//		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPattern(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Pattern* pPattern);
		//#endif
	
		//  Image Manipulation
		//if _WINDOWS
		//		virtual HBITMAP VCOM_CALLTYPE CreateDIBFromPaintNode(MCObjectHandle h);
		//endif
		//if _WINDOWS
		//		virtual HBITMAP VCOM_CALLTYPE CreateDIBFromPreview(InternalIndex &inIndex, short pixelWidth, short pixelHeight);
		//endif
		//if _WINDOWS
		//		virtual MCObjectHandle VCOM_CALLTYPE CreatePaintNodeFromDIB(HBITMAP hBitmap);
		//endif
		//if _WINDOWS
		//		virtual void VCOM_CALLTYPE DisposeDIB(HBITMAP hBitmap);
		//endif
		//if !_WIN_EXTERNAL_ && !_GSWINSDK_
		//		virtual void VCOM_CALLTYPE DoUpdateOrActivate(EventRecord& theEvent);
		//endif
		//if _WINDOWS
		//		virtual void VCOM_CALLTYPE EnterMoveableWindow(HWND hDialog);
		//		virtual void VCOM_CALLTYPE ExitMoveableWindow(HWND hDialog);
		//endif
		//if !_WIN_EXTERNAL_ && !_GSWINSDK_
		//		virtual void VCOM_CALLTYPE FPDisposeDialog(DialogPtr theDialog);
		//		virtual void VCOM_CALLTYPE FPShowWindow(WindowPtr theWindow);
		//		virtual HWND VCOM_CALLTYPE GetMainHWND();
		//endif
	
		// VW2009
	public:
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFileInStandardFolder(GS_ForEachFilePathProcPtr processFile, EFolderSpecifier folderSpec, void* env);
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInStandardFolder(GS_ForEachFilePathProcPtr processFile, FolderSpecifier folderSpec, void* env);
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInFolder(GS_ForEachFilePathNProcPtr processFile, IFolderIdentifier* pStartFolderID, bool doRecursive, void* pEnv);
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInPluginFolder(GS_ForEachFilePathNProcPtr processFile, void* pEnv);
		virtual bool			VCOM_CALLTYPE GetActiveDocument(IFileIdentifier** ppOutFileID, bool& outSaved);
		virtual bool			VCOM_CALLTYPE OpenDocumentPath(IFileIdentifier* pFileID, bool bShowErrorMessages);
		virtual GSError			VCOM_CALLTYPE SaveActiveDocumentPath(IFileIdentifier* pFileID);
		virtual bool			VCOM_CALLTYPE EncryptVSPluginFile(IFileIdentifier* pPluginFileID, bool doObfuscation = true);
		virtual bool			VCOM_CALLTYPE ReadVSExternalFile(IFileIdentifier* pFileID, TMPExternalDataForWorkspace& outData);
		virtual short			VCOM_CALLTYPE ImportDXF(IFileIdentifier* pFileID);
		virtual bool			VCOM_CALLTYPE WriteMaterialImageFile(IFileIdentifier* pFileID, MCObjectHandle hMaterial, Sint32 type, Sint32 shaderFamily);
		virtual MCObjectHandle	VCOM_CALLTYPE ReadMaterialImageFile(IFileIdentifier* pFileID);
	
		virtual void			VCOM_CALLTYPE ClearComponentInstances(MCObjectHandle hContainer, TComponentTypeID componentTypeID = (TComponentTypeID)-1);
		virtual MCObjectHandle	VCOM_CALLTYPE FindFirstComponentInstance(MCObjectHandle hContainer, TComponentTypeID componentTypeID);
		virtual MCObjectHandle	VCOM_CALLTYPE FindNextComponentInstance(TComponentTypeID componentTypeID, MCObjectHandle hComponent);
		virtual bool			VCOM_CALLTYPE AssignAsComponentInstance(MCObjectHandle hParentContainer, TComponentTypeID componentTypeID, MCObjectHandle hComponent);
		virtual bool			VCOM_CALLTYPE EnableComponentInstance(MCObjectHandle hComponent, bool bEnable);
		virtual bool			VCOM_CALLTYPE IsEnabledComponentInstance(MCObjectHandle hComponent);
		virtual bool			VCOM_CALLTYPE GetComponentInstanceTypeID(MCObjectHandle hComponent, TComponentTypeID& outComponentTypeID);
		virtual bool			VCOM_CALLTYPE SetComponentInstanceName(MCObjectHandle hComponent, const TXString& localizedName);
		virtual bool			VCOM_CALLTYPE GetComponentInstanceName(MCObjectHandle hComponent, TXString& outLocalizedName);
		virtual bool			VCOM_CALLTYPE EmptyToolHighlightingList();
		virtual bool			VCOM_CALLTYPE AddToolHighlightingObject(MCObjectHandle hHighlightObject);
		virtual bool			VCOM_CALLTYPE AddToolHighlightingSegment( const WorldPt& startPt,  const WorldPt& endPt);
		virtual MCObjectHandle	VCOM_CALLTYPE AddToolHighlightingPolyCreate();
		virtual bool			VCOM_CALLTYPE AddToolHighlightingPoly(MCObjectHandle polyID, bool bClosed);
		virtual bool			VCOM_CALLTYPE AddToolHighlightingPolyAddVertex(MCObjectHandle polyID, const WorldPt& pt, VertexType type = vtCorner, WorldCoord arcRadius = 0);
		virtual bool			VCOM_CALLTYPE AddToolHighlightingSegment3D( const WorldPt3& startPt,  const WorldPt3& endPt);
		virtual MCObjectHandle	VCOM_CALLTYPE AddToolHighlightingPoly3DCreate();
		virtual bool			VCOM_CALLTYPE AddToolHighlightingPoly3D(MCObjectHandle polyID, bool bClosed);
		virtual bool			VCOM_CALLTYPE AddToolHighlightingPoly3DAddVertex(MCObjectHandle polyID, const WorldPt3& pt);
		virtual bool			VCOM_CALLTYPE OpenURL(const TXString& url);
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertNurbsToPolylineArcs(MCObjectHandle hNurbs, double precision, bool insert = false);
		virtual MCObjectHandle  VCOM_CALLTYPE CreateOffsetObjectHandle(MCObjectHandle h, double offset, bool smoothConers = false);
		virtual MCObjectHandle  VCOM_CALLTYPE UnfoldSurface(MCObjectHandle surfaceToUnfold, short conversionRes);
		virtual MCObjectHandle  VCOM_CALLTYPE CreateWallHoleGroup(MCObjectHandle h);
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallHoleGroup(MCObjectHandle h);
		virtual void			VCOM_CALLTYPE SetDefaultTextureMapping(MCObjectHandle h, TexturePartSDK partID);
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfo(MCObjectHandle h, TexturePartSDK partID);
		virtual void			VCOM_CALLTYPE SetTextureMappingInfo(MCObjectHandle h, TexturePartSDK partID, const TextureMappingInfoSDK& mappingInfo);
		virtual MCObjectHandle  VCOM_CALLTYPE PerformMultipleUnion(int numberOf2dObjsToAdd, MCObjectHandle h, bool insert);
		virtual void			VCOM_CALLTYPE GetWorksheetSubrowHeight(MCObjectHandle worksheet, short databaserow, short subrow, short& height);
		virtual bool			VCOM_CALLTYPE SetCustomObjectWallHoleGroup(MCObjectHandle objectHand, MCObjectHandle hGeomGroup);
		virtual MCObjectHandle	VCOM_CALLTYPE GetCustomObjectSelectionGroup(MCObjectHandle objectHand);
		virtual bool			VCOM_CALLTYPE SetCustomObjectSelectionGroup(MCObjectHandle objectHand, MCObjectHandle hSelGroup);
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWallFootPrint(MCObjectHandle hWall);
		virtual bool            VCOM_CALLTYPE ExportResource(MCObjectHandle resource, IFileIdentifier* pFileID = nil, bool suppressDialogs = false);
		virtual Sint32			VCOM_CALLTYPE CallDefaultTool(ToolMessage* message, void*& messageContext);
		virtual void			VCOM_CALLTYPE EnableDrawingWorksheetPalette(bool enable, MCObjectHandle worksheet = nil);
		virtual bool			VCOM_CALLTYPE GetWorksheetAutoRecalcState(MCObjectHandle worksheet);
		virtual void			VCOM_CALLTYPE SetWorksheetAutoRecalcState(MCObjectHandle worksheet, bool state);
	
		// VW2010
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWorkingPlane(const Axis &theAxis, const TXString& name);
		virtual Axis			VCOM_CALLTYPE SetWPHybridTool(bool bRestore);
		virtual void			VCOM_CALLTYPE RestoreWPHybridTool(bool bRestore);
		virtual void			VCOM_CALLTYPE ClearWPHybridTool();
		virtual void			VCOM_CALLTYPE SetCursorByView();
		virtual bool			VCOM_CALLTYPE AddUndoDeselectObj(MCObjectHandle hObject);
		virtual bool			VCOM_CALLTYPE AddUndoSelectObj(MCObjectHandle hObject);
		virtual TOSWndPtr		VCOM_CALLTYPE GetLayoutDialogOSHandle(Sint32 dialogID);
		virtual TOSWndPtr		VCOM_CALLTYPE GetLayoutControlOSHandle(Sint32 dialogID, Sint32 itemID);
		virtual void			VCOM_CALLTYPE SetTextureRef(MCObjectHandle object, InternalIndex textureRef, TexturePartSDK texPartID, Sint32 texLayerID);
		virtual InternalIndex	VCOM_CALLTYPE GetTextureRef(MCObjectHandle object, TexturePartSDK texPartID, Sint32 texLayerID, Boolean resolveByClass);
		virtual void			VCOM_CALLTYPE SetDefaultTextureMapping(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID);
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfo(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID);
		virtual void			VCOM_CALLTYPE SetTextureMappingInfo(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID, const TextureMappingInfoSDK& mappingInfo);
		virtual Sint32			VCOM_CALLTYPE GetNumTextureLayers(MCObjectHandle h, TexturePartSDK texPartID);
		virtual bool			VCOM_CALLTYPE SetStaticTextStyle(Sint32 dialogID, Sint32 itemID, int style);
		virtual bool			VCOM_CALLTYPE SetStaticTextColor(Sint32 dialogID, Sint32 itemID, int red, int green, int blue);
		virtual bool			VCOM_CALLTYPE SetItemClickable(Sint32 dialogID, Sint32 itemID, bool clickable);
		virtual bool			VCOM_CALLTYPE SetSliderLiveUpdate(Sint32 dialogID, Sint32 itemID, bool liveUpdate);
		virtual MCObjectHandle	VCOM_CALLTYPE CreatePaintNode(IDrawPad* pDrawPad);
		virtual bool			VCOM_CALLTYPE DrawSymbolPreview(IDrawPad* pDrawPad, InternalIndex resourceRefNum, const ViewRect& destRect, short viewMode=1, short renderMode=0, ViewRect* outDrawBounds=NULL);
		virtual void			VCOM_CALLTYPE NotifyClassChange(StatusData liAdditionalData = 0);
		virtual bool		   	VCOM_CALLTYPE RegisterDialogForTimerEvents(Sint32 dialogID, Uint32 numberOfMilliseconds);
		virtual void		   	VCOM_CALLTYPE DeregisterDialogFromTimerEvents(Sint32 dialogID);
		virtual bool		   	VCOM_CALLTYPE SetImageControlData(Sint32 nDialogID, Sint32 nComponentID, void *imageData, size_t imageDataByteSize);
		virtual void			VCOM_CALLTYPE SetListItemEnabled(Sint32 dialogID, Sint32 componentID, short itemIndex, bool enabled = true);
		virtual void			VCOM_CALLTYPE SetFullBreakRecord(MCObjectHandle theWall, short index, WorldCoord off, SymbolBreakType* breakData);
		virtual bool			VCOM_CALLTYPE SetObjectAsCornerBreak(MCObjectHandle objectHandle, MCObjectHandle wallHandle, bool CornerBreak);
		virtual bool			VCOM_CALLTYPE SetObjectWallOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord offset);
		virtual EWallCapAttributesType VCOM_CALLTYPE GetWallCapAttributesType(MCObjectHandle wall);
		virtual void			VCOM_CALLTYPE SetWallCapAttributesType(MCObjectHandle wall, EWallCapAttributesType wallCapAttributesType);
		virtual short			VCOM_CALLTYPE GetCoreWallComponent(MCObjectHandle object);
		virtual void			VCOM_CALLTYPE SetCoreWallComponent(MCObjectHandle object, short componentIndex);
		virtual EWallHoleTexturePart VCOM_CALLTYPE GetWallHoleTexturePart(MCObjectHandle object);
		virtual void			VCOM_CALLTYPE SetWallHoleTexturePart(MCObjectHandle object, EWallHoleTexturePart part);
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWallFeature(MCObjectHandle wall, MCObjectHandle profile, EWallFeatureType wallFeatureType);
		virtual MCObjectHandle	VCOM_CALLTYPE GetActiveLayer();
		virtual MCObjectHandle	VCOM_CALLTYPE CreateCustomObjectByMatrixEx(const TXString& name, const TransformMatrix& matrix, bool bInsert);
		virtual void			VCOM_CALLTYPE SetHighlightedHelpString(const TXString& helpMessage);
		virtual void			VCOM_CALLTYPE GetCurrentLocalization(TXString& outLanguage, TXString& outSubLanguage);
		virtual void			VCOM_CALLTYPE RGBToColorIndexN(const RGBColor& rgb, ColorRef& colorIndex, Boolean bIgnoreBlackBackground);
		virtual void			VCOM_CALLTYPE ColorIndexToRGBN(ColorRef colorIndex, RGBColor& rgb, Boolean bIgnoreBlackBackground);
		virtual void			VCOM_CALLTYPE RefreshRenderingForSelectedObjects();
		virtual void			VCOM_CALLTYPE RefreshResourceBrowserResourcesList(bool immediate);
		virtual bool			VCOM_CALLTYPE GetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short& outPatternIndex);
		virtual bool			VCOM_CALLTYPE SetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short patternIndex);
		virtual InternalIndex	VCOM_CALLTYPE SetDashStyle(const TXString& name, bool scaleWithThick, const std::vector<double>& inVectors);
		virtual bool			VCOM_CALLTYPE PointInsideAnEnclosedRegionOfTheGroup(MCObjectHandle h, WorldPt &pickPt);
	
		// VW2011
	public:
		virtual MCObjectHandle  VCOM_CALLTYPE CreateArcLengthDimension(const WorldPt& dimStartPt, const WorldPt& dimEndPt, const WorldPt& arcCenterPt, const WorldCoord& startOffset, const bool clockwiseArc, bool witnessPerpChord, const bool arcIndicator);
		virtual void			VCOM_CALLTYPE GetTextCustomStyle(MCObjectHandle textBlock, Sint32 charNum, unsigned char& customStyle);
		virtual void			VCOM_CALLTYPE SetTextCustomStyle(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char customStyle);
		virtual bool			VCOM_CALLTYPE GetRoofRunRise(Sint32 dialogID, Sint32 componentID, double& run, double& rise, double& value);
		virtual Sint32			VCOM_CALLTYPE CallDefaultToolN(EDefaultToolType type, bool isStandard, ToolMessage* message, void*& messageContext);
		virtual bool			VCOM_CALLTYPE SetModeBarButtonsHelpText(const TXStringArray& arrHelpText);
	
		virtual Sint32			VCOM_CALLTYPE Deprecated1340(short inHotSpotType, const WorldPt3& inLocation, Sint32 inCursorID, const TXString& inTip, Sint32 data);
	
		virtual HotSpotRefID	VCOM_CALLTYPE TrackHotSpotN(Boolean& outIs3d, WorldPt3& outLocation, Sint32& outData);
		virtual void			VCOM_CALLTYPE ShowRecFormatResourceDialog(MCObjectHandle& hFormat, Boolean isNewResource, bool hideInvisibleParameters = false);
		virtual bool			VCOM_CALLTYPE AlignColumnEdge(Sint32 dialogID, Sint32 srcItemID, short columnID, short alignMode );
		virtual void			VCOM_CALLTYPE DeleteSymbolDefinition(MCObjectHandle hSymDef, Boolean bCompletely, Boolean useUndo = true);
		virtual InternalIndex	VCOM_CALLTYPE GetTilePopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual short			VCOM_CALLTYPE GetTilePopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex);
		virtual short			VCOM_CALLTYPE GetTilePopupSelectedItem(Sint32 dialogID, Sint32 componentID);
		virtual InternalIndex	VCOM_CALLTYPE GetHatchPopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual short			VCOM_CALLTYPE GetHatchPopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex);
		virtual short			VCOM_CALLTYPE GetHatchPopupSelectedItem(Sint32 dialogID, Sint32 componentID);
		virtual MCObjectHandle	VCOM_CALLTYPE CreateTile(const TXString& name);
		virtual bool			VCOM_CALLTYPE ShowEditTileDialog(MCObjectHandle& tileHandle);
		virtual bool			VCOM_CALLTYPE ShowEditTileSettingsDialog(MCObjectHandle& tileHandle);
		virtual MCObjectHandle	VCOM_CALLTYPE ShowNewTileDialog ();
		virtual bool			VCOM_CALLTYPE GetTileBackgroundColor(MCObjectHandle tile, ColorRef& backgroundColor);
		virtual bool			VCOM_CALLTYPE SetTileBackgroundColor(MCObjectHandle tile , const ColorRef& backgroundColor);
		virtual MCObjectHandle	VCOM_CALLTYPE GetTileGeometryGroup (MCObjectHandle tileHandle);
		virtual bool	 		VCOM_CALLTYPE GetListBrowserItemTileRefNumber(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 &liRefNumber);
		virtual bool	 		VCOM_CALLTYPE SetListBrowserItemTileRefNumber(Sint32 dialogID, Sint32 componentID, int itemIndex, int iSubItemIndex, Sint32 liRefNumber);
		virtual void	        VCOM_CALLTYPE AddToolEditTextMethod(const TXString & label, const TXString& value);
		virtual void			VCOM_CALLTYPE SetToolEditTextMethodValue(short group, const TXString& value);
		virtual TXString        VCOM_CALLTYPE GetToolEditTextMethodValue(short group);
		virtual void            VCOM_CALLTYPE EditRealConvertToStringUtility(short editRealType, double value, TXString& valueText);
		virtual MCObjectHandle	VCOM_CALLTYPE GSNewObjectHandle(short objectType);
		virtual void			VCOM_CALLTYPE InvalObj(MCObjectHandle h);
		virtual bool			VCOM_CALLTYPE SetTextAdorner(MCObjectHandle textBlock, MCObjectHandle textAdorner, const WorldPt& scalePt);
		virtual Boolean			VCOM_CALLTYPE GetTreeControlItemText(Sint32 dialogID, Sint32 componentID, int nItemID, TXString& itemText);
		virtual Boolean			VCOM_CALLTYPE GetTreeControlSelectedItemText(Sint32 dialogID, Sint32 componentID, TXString& itemText);
		virtual bool			VCOM_CALLTYPE AddTileGeometryObject(MCObjectHandle tileHandle, MCObjectHandle objectHandle);
		virtual MCObjectHandle  VCOM_CALLTYPE GetTileGroupParent(MCObjectHandle objectHandle);
		virtual bool			VCOM_CALLTYPE IsTileGroupContainedObject(MCObjectHandle objectHandle);
		virtual Boolean VCOM_CALLTYPE GetObjectPlanarBounds(MCObjectHandle h, WorldRectVerts& outBoxVerts);
		virtual void			VCOM_CALLTYPE GetCurrToolInteractiveDraw(IToolInteractiveDraw** outInteractiveDraw);
		virtual bool			VCOM_CALLTYPE ArePlanarMatricesCoplanar(TransformMatrix & inMat1, TransformMatrix & inMat2, TransformMatrix& outTransformFrom2To1);
		virtual void			VCOM_CALLTYPE DrawCoordLineOnPlane( const WorldPt& pt1, const WorldPt& pt2, TPlanarRefID refID );
		virtual void			VCOM_CALLTYPE DrawCoordLineOnPlane3D( const WorldPt& pt1, const WorldPt& pt2, TPlanarRefID refID );
		virtual bool			VCOM_CALLTYPE GetPlanarMatrix(const TPlanarRefID& planarRefID, TransformMatrix& outMatrix);
		virtual void			VCOM_CALLTYPE GetPlanarRefID( MCObjectHandle objectHandle, TPlanarRefID& outRefID );
		virtual bool			VCOM_CALLTYPE IsScreenPlanarRefID(const TPlanarRefID& planarRefID);
		virtual bool			VCOM_CALLTYPE IsPlanarObject( MCObjectHandle objectHandle, TPlanarRefID& outPlanarRefID );
		virtual bool			VCOM_CALLTYPE IsPlanarObjectIn3DView( MCObjectHandle objectHandle );
		virtual bool			VCOM_CALLTYPE PlanarPtTo3DModelPt( const TPlanarRefID& refID, const WorldPt& inPt, WorldPt3& outPt );
		virtual bool			VCOM_CALLTYPE PlanarPtToScreenPlanePt( const TPlanarRefID& refID, WorldPt& outPt);
		virtual void			VCOM_CALLTYPE ScreenPlanePtToPlanarPt( const TPlanarRefID& refID, WorldPt& outPt );
		virtual void			VCOM_CALLTYPE SetPlanarRefID( MCObjectHandle objectHandle, const TPlanarRefID& refID );
		virtual void			VCOM_CALLTYPE SetPlanarRefIDToGround( MCObjectHandle objectHandle );
		virtual TPlanarRefID	VCOM_CALLTYPE GetCurrentPlanarRefID( );
		virtual short			VCOM_CALLTYPE GetObjectTypeN(MCObjectHandle h);
		virtual void			VCOM_CALLTYPE ResizeSelectedDims( MCObjectHandle origH, const WorldCoord valueChange, const Sint32 dimCount, const Boolean onDraw, const Boolean dimLineResize, const Boolean fixedLengthWitLines );
		virtual TXString		VCOM_CALLTYPE GetImageFileName(TXString &resourceFileName, Sint32 family, MCObjectHandle imageNode);
		virtual MCObjectHandle	VCOM_CALLTYPE CreateImageDefNodeFromPNGData(void* pngData, size_t pngDataSize);
		virtual void			VCOM_CALLTYPE CompressTextureImage(MCObjectHandle image);
		virtual MCObjectHandle	VCOM_CALLTYPE CreateTextureBitmapNoDialog(MCObjectHandle parentShaderRecord);
		virtual Boolean			VCOM_CALLTYPE ShowListBrowserRadioToolTips(Sint32 dialogID, Sint32 componentID);
		virtual void            VCOM_CALLTYPE Default2DToolDrawNew(const TPlanarRefID& planarRefID);
		virtual void			VCOM_CALLTYPE SetTextStyleRef(MCObjectHandle object, InternalIndex styleRef);
		virtual InternalIndex	VCOM_CALLTYPE GetTextStyleRef(MCObjectHandle object);
		virtual short			VCOM_CALLTYPE AlertQuestionDefault(const TXString& question, const TXString& advice = "", short defaultButton=1, const TXString& OKOverrideText = "", const TXString& CancelOverrideText = "", const TXString& customButtonAText = "", const TXString& customButtonBText = "", const TXString& category = "", const TXString& item = "", const TXString& checkboxOverrideText = "", short defaultAnswer = -1);
		virtual Boolean			VCOM_CALLTYPE SetColorName(ColorRef colorIndex, const TXString& colorName);
		virtual TXString		VCOM_CALLTYPE GetColorName(ColorRef colorIndex);
		virtual bool			VCOM_CALLTYPE IsScreenObject( MCObjectHandle objectHandle );
		virtual bool	        VCOM_CALLTYPE PieceWiseNurbsCurveReverseInPlace( MCObjectHandle objectHandle );
		virtual MCObjectHandle	VCOM_CALLTYPE CreatePieceWiseNurbsCurveReverse( MCObjectHandle objectHandle );
		virtual MCObjectHandle	VCOM_CALLTYPE CreateSlab(MCObjectHandle profile);
		virtual bool			VCOM_CALLTYPE ModifySlab(MCObjectHandle slab, MCObjectHandle modifier, bool isClipObject, Uint32 componentFlags);
		virtual InternalIndex	VCOM_CALLTYPE GetSlabStyle(MCObjectHandle slab);
		virtual void			VCOM_CALLTYPE SetSlabStyle(MCObjectHandle slab, InternalIndex slabStyle);
		virtual void			VCOM_CALLTYPE ConvertToUnstyledSlab(MCObjectHandle slab);
		virtual InternalIndex	VCOM_CALLTYPE GetSlabPreferencesStyle();
		virtual void			VCOM_CALLTYPE SetSlabPreferencesStyle(InternalIndex slabStyle);
		virtual void			VCOM_CALLTYPE BeginMultipleDuplicate();
		virtual void			VCOM_CALLTYPE EndMultipleDuplicate();
		virtual void			VCOM_CALLTYPE BuildConstraintModelForObject(MCObjectHandle objectHandle, bool traverseContainers);
		virtual void			VCOM_CALLTYPE RecordModifiedObjectInConstraintModel(MCObjectHandle objectHandle, bool useSelection);
		virtual Boolean	        VCOM_CALLTYPE GetCurveEndsAndTangents( MCObjectHandle objectHandle, WorldPt3& startPt, WorldPt3& endPt, WorldPt3& startTangent, WorldPt3& endTangent );
		virtual Boolean			VCOM_CALLTYPE AreWorksheetGridLinesVisible( MCObjectHandle worksheet);
		virtual void			VCOM_CALLTYPE SetWorksheetGridLinesVisibility( MCObjectHandle worksheet, Boolean bVisible);
		virtual bool			VCOM_CALLTYPE AreUpdateChecksEnabled(void);	// returns true if update checking is supported
		virtual void			VCOM_CALLTYPE CheckForUpdates(void);
		virtual MCObjectHandle	VCOM_CALLTYPE CreateCustomObjectPathNoOffset(const TXString& name, MCObjectHandle pathHand = NULL, MCObjectHandle profileGroupHand = NULL);
		virtual short			VCOM_CALLTYPE NumberCustomDimensionStandards(void);
		virtual Boolean			VCOM_CALLTYPE ConsolidatePlanarObjects(const MCObjectHandle objectHandle, MCObjectHandle& objectHandleToBeTransformed);
		virtual Boolean         VCOM_CALLTYPE FindClosestPointOnNURBSObjectFrom3DPoint(MCObjectHandle h, const WorldPt3& point3D, WorldPt3 &outClosestPoint);
		virtual WorldCoord		VCOM_CALLTYPE GetSlabHeight(MCObjectHandle slab);
		virtual void			VCOM_CALLTYPE SetSlabHeight(MCObjectHandle slab, WorldCoord height);
		virtual MCObjectHandle	VCOM_CALLTYPE CreateSlabStyle(const TXString &slabStyleName);
		virtual MCObjectHandle	VCOM_CALLTYPE GetWallPreferences();
		virtual MCObjectHandle	VCOM_CALLTYPE GetSlabPreferences();
		virtual ETextureSet		VCOM_CALLTYPE GetTextureSet(MCObjectHandle object);
		virtual void			VCOM_CALLTYPE SetTextureSet(MCObjectHandle object, ETextureSet textureSet);
		virtual short			VCOM_CALLTYPE GetDatumSlabComponent(MCObjectHandle object);
		virtual void			VCOM_CALLTYPE SetDatumSlabComponent(MCObjectHandle object, short componentIndex);
		virtual Boolean			VCOM_CALLTYPE GetComponentOffsetFromWallTop(MCObjectHandle object, short componentIndex, WorldCoord &offsetFromWallTop);
		virtual Boolean			VCOM_CALLTYPE SetComponentOffsetFromWallTop(MCObjectHandle object, short componentIndex, WorldCoord offsetFromWallTop);
		virtual Boolean			VCOM_CALLTYPE GetComponentOffsetFromWallBottom(MCObjectHandle object, short componentIndex, WorldCoord &offsetFromWallBottom);
		virtual Boolean			VCOM_CALLTYPE SetComponentOffsetFromWallBottom(MCObjectHandle object, short componentIndex, WorldCoord offsetFromWallBottom);
		virtual Boolean			VCOM_CALLTYPE GetComponentFollowTopWallPeaks(MCObjectHandle object, short componentIndex, Boolean &followTopWallPeaks);
		virtual Boolean			VCOM_CALLTYPE SetComponentFollowTopWallPeaks(MCObjectHandle object, short componentIndex, Boolean followTopWallPeaks);
		virtual Boolean			VCOM_CALLTYPE GetComponentFollowBottomWallPeaks(MCObjectHandle object, short componentIndex, Boolean &followBottomWallPeaks);
		virtual Boolean			VCOM_CALLTYPE SetComponentFollowBottomWallPeaks(MCObjectHandle object, short componentIndex, Boolean followBottomWallPeaks);
		virtual Boolean			VCOM_CALLTYPE GetComponentAutoBoundEdgeOffset(MCObjectHandle object, short componentIndex, EWallBound &autoBoundEdgeOffset);
		virtual Boolean			VCOM_CALLTYPE SetComponentAutoBoundEdgeOffset(MCObjectHandle object, short componentIndex, EWallBound autoBoundEdgeOffset);
		virtual Boolean			VCOM_CALLTYPE GetComponentManualEdgeOffset(MCObjectHandle object, short componentIndex, WorldCoord &manualEdgeOffset);
		virtual Boolean			VCOM_CALLTYPE SetComponentManualEdgeOffset(MCObjectHandle object, short componentIndex, WorldCoord manualEdgeOffset);
		virtual Boolean			VCOM_CALLTYPE GetComponentTexture(MCObjectHandle object, short componentIndex, InternalIndex &texture);
		virtual Boolean			VCOM_CALLTYPE SetComponentTexture(MCObjectHandle object, short componentIndex, InternalIndex texture);
		virtual WorldCoord		VCOM_CALLTYPE GetComponentNetArea(MCObjectHandle object, short componentIndex);
		virtual WorldCoord		VCOM_CALLTYPE GetComponentNetVolume(MCObjectHandle object, short componentIndex);
		virtual void			VCOM_CALLTYPE FontMapReplace(const TXStringArray& arrFonts, bool doUserInterface);
		virtual void			VCOM_CALLTYPE FontMapGetReplacement(const TXString& orgFont, TXString& outReplFont);
		virtual short			VCOM_CALLTYPE ConvertFontIDToIndex(short fontID);
		virtual short			VCOM_CALLTYPE ConvertIndexToFontID(short fontIndex);
		virtual void            VCOM_CALLTYPE Get2DPolyAreaAndPerimeter(MCObjectHandle h, double &area, double &perimeter);
		virtual void			VCOM_CALLTYPE IFC_ResetGUID(MCObjectHandle hRecord);
		virtual bool			VCOM_CALLTYPE IFC_IsIFCRecord(MCObjectHandle hRecord);
		virtual MCObjectHandle	VCOM_CALLTYPE GetWallComponentPoly(MCObjectHandle hWall, short componentIndex);
	
	
		// VW2012
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE GetObjectHiddenLine(MCObjectHandle hGeometry3D, double cuttingHeight, bool bottomOfCuttingPlane);
		virtual Boolean			VCOM_CALLTYPE AddBeforeModifyWorkingPlane();
		virtual bool			VCOM_CALLTYPE ModelPtToPlanarPt(const TPlanarRefID& refID, const WorldPt3& inModelPt, WorldPt& outPlanarPt);
		virtual MCObjectHandle	VCOM_CALLTYPE ImportResourceToCurrentFileN(Sint32 listID, Sint32 index, TImportResourceConflictCallbackProcPtr conflictCallback, void* env);
		virtual TXString		VCOM_CALLTYPE CoordToPrimaryDimensionString(WorldCoord coord);
		virtual TXString		VCOM_CALLTYPE CoordToSecondaryDimensionString(WorldCoord coord);
		virtual void			VCOM_CALLTYPE GetWallOverallHeights(MCObjectHandle theWall, WorldCoord& overallHeightTop, WorldCoord& overallHeightBottom);
		virtual bool			VCOM_CALLTYPE SetWallOverallHeights(MCObjectHandle theWall, const SStoryObjectData &bottomData, const SStoryObjectData &topData);
		virtual bool			VCOM_CALLTYPE CheckParametricNameConflictWithUI(const TXString& name);
		virtual void			VCOM_CALLTYPE ShowByClassChoice(Sint32 dialogID, Sint32 componentID);
		virtual Boolean			VCOM_CALLTYPE IsClassChoiceSelected(Sint32 dialogID, Sint32 componentID);
		virtual void			VCOM_CALLTYPE SelectClassChoice(Sint32 dialogID, Sint32 componentID, Boolean select);
		virtual Sint32			VCOM_CALLTYPE GetMeshVertexCount(MCObjectHandle hMesh);
		virtual WorldPt3		VCOM_CALLTYPE GetMeshVertexAt(MCObjectHandle hMesh, size_t at);
		virtual void			VCOM_CALLTYPE SetMeshVertexAt(MCObjectHandle hMesh, size_t at, const WorldPt3& pt);
		virtual void			VCOM_CALLTYPE RunTempTool(const VWIID& iidToolExt);
		virtual bool			VCOM_CALLTYPE RenderPoly(MCObjectHandle hPoly, IVertexListener* listener, short convRes);
		virtual MCObjectHandle  VCOM_CALLTYPE NewCreateCombineIntoSurface(const WorldPt& inPoint, short columnsAndPilastersEnum, bool goThrougLayre, MCObjectHandle listOfObjs);
	
		virtual void			VCOM_CALLTYPE PushPullPlanarGetInternalProcPtrAndUserData(PushPullHandleCompletionRoutinePtr& outProcPtr, void*& outUserData);
		virtual void			VCOM_CALLTYPE PushPullPlanarBegin(PushPullHandleCompletionRoutinePtr inCompletionProcPtr, void* inUserData);
		virtual void			VCOM_CALLTYPE PushPullPlanarAddObjectID(MCObjectHandle inHandleIDOfPlanarObjectToPushPull);
		virtual void			VCOM_CALLTYPE PushPullPlanarEnd();
		virtual bool			VCOM_CALLTYPE PushPullPlanarIsEnabled();
		virtual void			VCOM_CALLTYPE PushPullPlanarSetEnabled(bool inSetVal);
		virtual bool			VCOM_CALLTYPE PushPullPlanarNeedsPickLoop();
		virtual void			VCOM_CALLTYPE PushPullPlanarActionHandler(ToolMessage* message, Sint32& outPushPullReturn, bool& outHandledExclusively);
		virtual void			VCOM_CALLTYPE PushPullPlanarAddPrefButton();
	
		virtual MCObjectHandle	VCOM_CALLTYPE CreateProxyObjOnLayer(MCObjectHandle hParametric, MCObjectHandle hLayer);
		virtual MCObjectHandle	VCOM_CALLTYPE GetProxyParent(MCObjectHandle hProxyObj);
	
		virtual InternalIndex	VCOM_CALLTYPE AddClassWithUI(TXString& inOutName);
		virtual bool			VCOM_CALLTYPE EditClassWithUI(InternalIndex classIndex);
		virtual bool			VCOM_CALLTYPE EditClassWithUI(InternalIndex* arrClassIndex, size_t len);
	
		virtual void			VCOM_CALLTYPE ViewPt2WorldPt(const ViewPt& viewPt, WorldPt& outWorldPt);
		virtual bool			VCOM_CALLTYPE WorldPt2ViewPt(const WorldPt& worldPt, ViewPt& outViewPt);
	
		virtual bool			VCOM_CALLTYPE CloseDocument();
		virtual short			VCOM_CALLTYPE GetNumStories();
		virtual short			VCOM_CALLTYPE GetNumLayerLevelTypes();
		virtual short			VCOM_CALLTYPE GetNumStoryLayerTemplates();
		virtual TXString		VCOM_CALLTYPE GetLayerLevelType(MCObjectHandle layer);
		virtual bool			VCOM_CALLTYPE SetLayerLevelType(MCObjectHandle layer, TXString& layerLevelType);
		virtual TXString		VCOM_CALLTYPE GetStoryLayerTemplateName(short index);
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryOfLayer(MCObjectHandle layer);
		virtual MCObjectHandle	VCOM_CALLTYPE GetLayerForStory(MCObjectHandle story, const TXString &layerLevelType);
		virtual bool			VCOM_CALLTYPE CreateStory(TXString& name, TXString& suffix);
		virtual bool			VCOM_CALLTYPE CreateLayerLevelType(TXString& name);
		virtual bool			VCOM_CALLTYPE CreateStoryLayerTemplate(TXString& name, double scaleFactor, TXString& layerLevelType, WorldCoord elevationOffset, WorldCoord defaultWallHeight, short& index);
		virtual bool			VCOM_CALLTYPE DeleteStoryLayerTemplate(short index);
		virtual bool			VCOM_CALLTYPE AssociateLayerWithStory(MCObjectHandle layer, MCObjectHandle story);
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryAbove(MCObjectHandle story);
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryBelow(MCObjectHandle story);
		virtual WorldCoord		VCOM_CALLTYPE GetStoryElevation(MCObjectHandle story);
		virtual bool			VCOM_CALLTYPE SetStoryElevation(MCObjectHandle story, WorldCoord elevation);
		virtual TXString		VCOM_CALLTYPE GetStorySuffix(MCObjectHandle story);
		virtual bool			VCOM_CALLTYPE SetStorySuffix(MCObjectHandle story, const TXString & suffix);
		virtual bool			VCOM_CALLTYPE HasObjectStoryBounds(MCObjectHandle hObject);
		virtual bool			VCOM_CALLTYPE HasObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id);
		virtual bool			VCOM_CALLTYPE GetObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id, SStoryObjectData& outData);
		virtual bool			VCOM_CALLTYPE SetObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id, const SStoryObjectData& data);
		virtual bool			VCOM_CALLTYPE DelObjectStoryBounds(MCObjectHandle hObject);
		virtual bool			VCOM_CALLTYPE DelObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id);
		virtual size_t			VCOM_CALLTYPE GetObjectStoryBoundsCount(MCObjectHandle hObject);
		virtual TObjectBoundID	VCOM_CALLTYPE GetObjectStoryBoundsAt(MCObjectHandle hObject, size_t index);
		virtual WorldCoord		VCOM_CALLTYPE GetObjectBoundElevation(MCObjectHandle hObject, TObjectBoundID id);
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertToPolylineWithTangentVertices(MCObjectHandle hNonPoly);
	
	
		virtual HotSpotRefID	VCOM_CALLTYPE AddHotSpotN(short inHotSpotType, const WorldPt3& inLocation, const TXString& cursorSpec, const TXString& inTip, Sint32 data);
	
		virtual bool			VCOM_CALLTYPE CreateImageControl2(Sint32 dialogID, Sint32 controlID, int widthInPixels, int heightInPixels, const TXString& imageSpecifier);
		virtual bool			VCOM_CALLTYPE UpdateImageControl2(Sint32 dialogID, Sint32 controlID, const TXString& imageSpecifier);
		virtual bool			VCOM_CALLTYPE CreateImageButton(Sint32 dialogID, Sint32 controlID, int widthInStdChar, const TXString& imageSpecifier);
		virtual bool			VCOM_CALLTYPE UpdateImageButton(Sint32 dialogID, Sint32 controlID, const TXString& imageSpecifier);
		virtual bool			VCOM_CALLTYPE CreateThumbnailPopup(Sint32 dialogID, Sint32 controlID);
	
		virtual void			VCOM_CALLTYPE AddButtonMode(const TXString& iconSpec);
		virtual void			VCOM_CALLTYPE AddCheckMode(short initialSetting, const TXString& iconSpec);
		virtual void			VCOM_CALLTYPE AddRadioMode(short initialSetting, const TXStringArray& imageSpecs);
	
		virtual short			VCOM_CALLTYPE AddListBrowserImage(Sint32 dialogID, Sint32 componentID, const TXString& imageSpecifier, const TXString& selectedImageSpecifier = "");
		virtual Boolean			VCOM_CALLTYPE GetListBrowserMultImageIndexes(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TXString& imageSpec0, TXString& imageSpec1, TXString& imageSpec2);
		virtual Boolean			VCOM_CALLTYPE SetListBrowserMultImageIndexes(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, const TXString& imageSpec0, const TXString& imageSpec1, const TXString& imageSpec2);
		virtual int				VCOM_CALLTYPE InsertEnhancedPullDownMenuItem(Sint32 dialogID, Sint32 componentID, const TXString& strName, const TXString& imageSpecifier);
		virtual Boolean			VCOM_CALLTYPE InsertProposedClassOrLayerItem(Sint32 nDialogID, Sint32 nComponentID, const TXString& strLabel, const TXString& iconSpec);
	
		virtual bool			VCOM_CALLTYPE AreAlertsAllowed();
	
		virtual bool  			VCOM_CALLTYPE HasWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType);
		virtual EWSColumnDatabaseSortType VCOM_CALLTYPE GetWorksheetColumnSortType(MCObjectHandle worksheet, short databaseRow, short column);
		virtual void			VCOM_CALLTYPE SetWorksheetColumnSortType(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseSortType sortType);
		virtual short  			VCOM_CALLTYPE GetWorksheetColumnSortPrecedence(MCObjectHandle worksheet, short databaseRow, short column);
		virtual void 			VCOM_CALLTYPE MoveWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short fromColumn, short toColumn, EWSColumnDatabaseOperatorType operatorType);
		virtual void 			VCOM_CALLTYPE AddWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType);
		virtual void 			VCOM_CALLTYPE RemoveAllWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, EWSColumnDatabaseOperatorType operatorType);
		virtual void 			VCOM_CALLTYPE RemoveWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType);
		virtual void			VCOM_CALLTYPE GetStoryBoundChoiceStrings(MCObjectHandle story, bool topBound, TXStringArray& strings);
		virtual void			VCOM_CALLTYPE GetStoryBoundDataFromChoiceString(const TXString& string, SStoryObjectData& data);
		virtual void			VCOM_CALLTYPE GetChoiceStringFromStoryBoundData(const SStoryObjectData& data, TXString& string);
		virtual MCObjectHandle	VCOM_CALLTYPE CreateRenderworksStyle();
		virtual Boolean			VCOM_CALLTYPE Get3DObjEdgeData(const ViewPt& viewPt, MCObjectHandle objectH, WorldPt3& edgeStart, WorldPt3& edgeEnd);
		virtual bool			VCOM_CALLTYPE GetStoryLayerTemplateInfo(short index, TXString& name, double& scaleFactor, TXString& layerLevelType, double& elevationOffset, double& defaultWallHeight);
	
		virtual MCObjectHandle	VCOM_CALLTYPE GetObjectGeneratingAutoPlane();
	
		virtual WorldCoord		VCOM_CALLTYPE GetVertexMaxRadius(MCObjectHandle h, short vertexNum);
	
		virtual void			VCOM_CALLTYPE AlertSetAlwaysDoValue(const TXString& category, const TXString& item, short value);
	
		virtual int				VCOM_CALLTYPE GetCSGAction(MCObjectHandle hCSG);
	
		virtual Boolean			VCOM_CALLTYPE BeginInteractiveFrames();
		virtual void			VCOM_CALLTYPE DrawInteractiveFrame();
		virtual void			VCOM_CALLTYPE EndInteractiveFrames();
		virtual void			VCOM_CALLTYPE CreateInteractiveLightGroup();
		virtual MCObjectHandle	VCOM_CALLTYPE CreateRenderBackground(BackgroundType backgroundType);
	
		virtual bool            VCOM_CALLTYPE ExportResourceN(MCObjectHandle resource, IFileIdentifier* pFileID = nil, TImportResourceConflictCallbackProcPtr conflictCallback = nil);
	
		// VW2013
	public:
		virtual void			VCOM_CALLTYPE CustomBatchConvert(ICustomBatchConvertParams* params);
		virtual void			VCOM_CALLTYPE GetAllObjectNames(TXStringArray& names);
		virtual void			VCOM_CALLTYPE GetAllLayerNames(TXStringArray& names);
		virtual void			VCOM_CALLTYPE SetListBoxTabStops( Sint32 dialogID, Sint32 componentID, int numTabStops, int* tabStops );
		virtual void			VCOM_CALLTYPE SupportCustomControlKeyEvents( Sint32 dialogID, Sint32 componentID);
		virtual void			VCOM_CALLTYPE SetTextJustificationN( MCObjectHandle textBlock, short justification);
		virtual void			VCOM_CALLTYPE SetTextVerticalAlignmentN( MCObjectHandle textBlock, short verticalAlignment);
		virtual TXString		VCOM_CALLTYPE GetLayerLevelTypeName(short index);
		virtual bool			VCOM_CALLTYPE SetLayerLevelTypeName(short index, const TXString& name);
		virtual bool			VCOM_CALLTYPE SetStoryLayerTemplateName(short index, const TXString& name);
		virtual bool			VCOM_CALLTYPE GetUserOriginGlobal(WorldPt& outOrigin);
		virtual bool			VCOM_CALLTYPE CreateSolid(MCObjectHandle blank, const TVWArray_MCObjectHandle &toolList, bool add, MCObjectHandle& newSolid);
		virtual TXString		VCOM_CALLTYPE GetVectorworksSessionID();
		virtual void			VCOM_CALLTYPE EnableListBrowserHierarchicalDisplay(Sint32 dialogID, Sint32 componentID, Boolean enableHierarchicalDisplay);
		virtual void			VCOM_CALLTYPE SetListBrowserHierarchicalDisplayColumn(Sint32 dialogID, Sint32 componentID, short columnID);
		virtual Boolean			VCOM_CALLTYPE SetListBrowserNumericItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, double itemVal, short imageIndex);
	
		virtual TXString		VCOM_CALLTYPE MilsToString(Sint32 value, EThicknessUnitsType unitType);
		virtual Boolean			VCOM_CALLTYPE StringToMils(const TXString& str, EThicknessUnitsType unitType, Sint32& outValue);
		virtual Boolean			VCOM_CALLTYPE StringToArea(const TXString& str, double& outArea);
		virtual Boolean			VCOM_CALLTYPE StringToVolume(const TXString& str, double& outVolume);
	
		virtual Boolean			VCOM_CALLTYPE IsListBrowserDisplayHierarchical(Sint32 dialogID, Sint32 componentID);
		virtual void			VCOM_CALLTYPE HierarchicalListBrowserItemOpened(Sint32 dialogID, Sint32 componentID, short itemIndex, Boolean recursive, short& outNumbRedisplayedItems);
		virtual void			VCOM_CALLTYPE HierarchicalListBrowserItemClosed(Sint32 dialogID, Sint32 componentID, short itemIndex, Boolean recursive);
		virtual Boolean			VCOM_CALLTYPE HierarchicalListBrowserItemIsClosed(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual Boolean			VCOM_CALLTYPE HierarchicalListBrowserItemIsContainer(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual void			VCOM_CALLTYPE GetDisplayedItemsCountInHierarchicalContainer(Sint32 dialogID, Sint32 componentID, short itemIndex, short& outDisplayedItemsCount);
		virtual TXString		VCOM_CALLTYPE GetListBrowserItemOriginalName(Sint32 dialogID, Sint32 componentID, short itemIndex);
		virtual void			VCOM_CALLTYPE AddListBrowserOriginalName(Sint32 dialogID, Sint32 componentID, const TXString& originalName);
		virtual void			VCOM_CALLTYPE GetListBrowserOriginalNameCloseLevels(Sint32 dialogID, Sint32 componentID, const TXString& originalName, Boolean& outLeve1Closed, Boolean& outLevel2Closed, Boolean& outLevel3Closed);
		virtual void			VCOM_CALLTYPE SetListBrowserOriginalNameCloseLevels(Sint32 dialogID, Sint32 componentID, const TXString& originalName, Boolean level1Closed, Boolean level2Closed, Boolean level3Closed);
		virtual void			VCOM_CALLTYPE CollapseAllListBrowserItems(Sint32 dialogID, Sint32 componentID);
		virtual void			VCOM_CALLTYPE ExpandAllListBrowserItems(Sint32 dialogID, Sint32 componentID);
		virtual Boolean			VCOM_CALLTYPE CreateStyledStaticText(Sint32 dialogID, Sint32 componentID, const TXString & strText, short widthInStdChar, EStaticTextType enumType);
	
		virtual bool			VCOM_CALLTYPE SetModeBarButtonsText( const TVWModeBarButtonHelpArray& arrModeBarButtonsHelp );
		virtual bool			VCOM_CALLTYPE SetToolHelpMessage( const TXString& modeText, const TXString& descriptionText );
        virtual bool            VCOM_CALLTYPE SetToolHelpMessageAndTitle( const TXString& titleText, const TXString& modeText, const TXString& descriptionText );
		virtual MCObjectHandle	VCOM_CALLTYPE FindWallsSurroundingPoint(MCObjectHandle inBoundedObject, const WorldPt& inPoint, short inColumnsAndPilastersEnum,
																		MCObjectHandle inListOfObjects, bool ignoreClassVisibility);
		virtual short			VCOM_CALLTYPE GetNumAssociations(MCObjectHandle handle);
		virtual MCObjectHandle	VCOM_CALLTYPE GetAssociation(MCObjectHandle handle, short index, Sint16& associationKind, Sint16& value);
		virtual void			VCOM_CALLTYPE AdjustPathForWrapping(TXString& path, short maxWidth);
	
		virtual void			VCOM_CALLTYPE DoBatchPrintOrExport(short inBatchOperationType);
	
		virtual void 			VCOM_CALLTYPE DeleteObjectNoNotify(MCObjectHandle h);
	
		virtual void			VCOM_CALLTYPE EditObjectSpecial(MCObjectHandle h, TObjSpecialEdit editMode);
	
		virtual short			VCOM_CALLTYPE GetNumSavedViews();
		virtual bool			VCOM_CALLTYPE GetSavedView(short index, TXString& view);
		virtual void			VCOM_CALLTYPE RestoreSavedView(const TXString& savedView);
	
		virtual bool			VCOM_CALLTYPE CreateCustomThumbnailPopup(Sint32 dialogID, Sint32 controlID, ThumbnailSizeType sizeKind);
		virtual InternalIndex	VCOM_CALLTYPE GetClPenPatN(InternalIndex classIndex);
		virtual void			VCOM_CALLTYPE SetClPenPatN(InternalIndex classIndex, InternalIndex penPat);
		virtual InternalIndex	VCOM_CALLTYPE GetDefaultPenPatN();
		virtual void			VCOM_CALLTYPE SetDefaultPenPatN(InternalIndex penPat);
		virtual InternalIndex	VCOM_CALLTYPE GetPenPatN(MCObjectHandle h);
		virtual void			VCOM_CALLTYPE SetPenPatN(MCObjectHandle h, InternalIndex penPat);
	
		virtual void			VCOM_CALLTYPE GetLineTypeAttributeData(Sint32 dialogID, Sint32 itemID, InternalIndex& lineStyle, short& lineWeight);
		virtual void			VCOM_CALLTYPE SetLineTypeAttributeData(Sint32 dialogID, Sint32 itemID, InternalIndex lineStyle, short lineWeight);
		virtual void			VCOM_CALLTYPE GetLineTypeChoice(Sint32 dialogID, Sint32 itemID, Sint32& lineTypeRefNumber);
		virtual void			VCOM_CALLTYPE SetLineTypeChoice(Sint32 dialogID, Sint32 itemID, Sint32 lineTypeRefNumber);
		virtual void			VCOM_CALLTYPE ShowComplexLineTypesInLineAttributePopup(Sint32 dialogID, Sint32 itemID);
		virtual Boolean			VCOM_CALLTYPE GetListBrowserItemLineTypeRef(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 &iLineRef, int &iLineWeight);
		virtual Boolean			VCOM_CALLTYPE SetListBrowserItemLineTypeRef(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 iStyleIndex, int iLineWeight);
	
		virtual Boolean			VCOM_CALLTYPE IsWorksheetCellImage (MCObjectHandle worksheet, short row, short column);
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageType (MCObjectHandle worksheet, short row, short column, short& type);
		virtual short			VCOM_CALLTYPE GetWorksheetCellImageSizeType (MCObjectHandle worksheet, short row, short column);
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageSize (MCObjectHandle worksheet, short row, short column, short& height, short& width);
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageAngle (MCObjectHandle worksheet, short row, short column, double& angle);
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageView (MCObjectHandle worksheet, short row, short column, short& view);
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageRenderMode (MCObjectHandle worksheet, short row, short column, short& renderMode);
		virtual Boolean			VCOM_CALLTYPE GetWorksheetCellImageUseLayerScale (MCObjectHandle worksheet, short row, short column);
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageScale (MCObjectHandle worksheet, short row, short column, double& scale);
		virtual Boolean			VCOM_CALLTYPE GetWorksheetCellImageUseObjectImage (MCObjectHandle worksheet, short row, short column);
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageMarginSize (MCObjectHandle worksheet, short row, short column, unsigned char& marginSize);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageType (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short type);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageSizeType (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short imageSizeType);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageSize (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short height, short width);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageAngle (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, double angle);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageView (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short view);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageRenderMode (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short renderMode);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageUseLayerScale (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean useLayerScale);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageScale (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, double scale);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageUseObjectImage (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean useObjectImage);
		virtual void			VCOM_CALLTYPE SetWorksheetCellImageMarginSize (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, unsigned char marginSize);
		virtual MCObjectHandle	VCOM_CALLTYPE DoPolylineRadiusSmoothing(MCObjectHandle hPoly);
		virtual Boolean			VCOM_CALLTYPE SetImageControlDataN(Sint32 dialogID, Sint32 componentID, VectorWorks::UI::IIcon* icon);
		virtual MCObjectHandle	VCOM_CALLTYPE AssociateBoundedObjectWithWalls(MCObjectHandle inBoundedObject, TVWArray_MCObjectHandle& wallList, short inColumnsAndPilastersEnum);
	
		virtual Sint32 VCOM_CALLTYPE BuildResourceListN(short objectType, IFileIdentifier* fileID, Sint32& numItems);
	
		virtual Boolean			VCOM_CALLTYPE TrimNurbsSurface(MCObjectHandle iNurbsSurface, MCObjectHandle iNurbsCurve);
	
		virtual void			VCOM_CALLTYPE InteractiveViewOperation_Begin(EInteractiveMode type, const ViewPt& viewPt);
		virtual void			VCOM_CALLTYPE InteractiveViewOperation_End();
		virtual void			VCOM_CALLTYPE InteractiveViewOperation_Move(const ViewPt& viewPt);
	
		virtual Boolean			VCOM_CALLTYPE SetToolByName(const TXString& toolUnivName);
		virtual Boolean			VCOM_CALLTYPE SetToolByName(const TXString& toolUnivName, size_t modebarGroupID, size_t modebarButtonID);
		virtual void			VCOM_CALLTYPE SetToolByIndex(short index);
	
		virtual MCObjectHandle	VCOM_CALLTYPE CreateLayerWithUI(TXString& name);
		virtual bool			VCOM_CALLTYPE EditLayerWithUI(MCObjectHandle layer);
	
		virtual bool			VCOM_CALLTYPE CreateSavedViewWithUI(TXString& outName);
		virtual bool			VCOM_CALLTYPE EditSavedViewWithUI(TXString& inOutName);
	
		virtual MCObjectHandle	VCOM_CALLTYPE CreateExtrudeAlongPath2(MCObjectHandle pathHandle, MCObjectHandle profileHandle, Boolean bExponentialScale, double scale, Boolean bLockProfilePlane, Boolean bFixProfile);
		virtual short			VCOM_CALLTYPE SectionSolid(MCObjectHandle obj1, MCObjectHandle obj2, Boolean useSectionColor, Boolean flipSection, MCObjectHandle& newSolid);
		virtual bool			VCOM_CALLTYPE IsGBXMLExportAllowed();
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertToGenericSolid(MCObjectHandle objectHandle );
	
		virtual void			VCOM_CALLTYPE AddWallToContainer(MCObjectHandle wallHandle, MCObjectHandle container);
		virtual void			VCOM_CALLTYPE SyncMatrixToStoryBound(MCObjectHandle h, TObjectBoundID id);
		virtual void            VCOM_CALLTYPE SplitPolylineByMultiple2DLoci(MCObjectHandle h, TVWArray_WorldPt loci, bool killOriginal, bool insert, TVWArray_MCObjectHandle & arrayHandle);
	
		virtual bool			VCOM_CALLTYPE ExportDocumentPreviewImageFile(IFileIdentifier* pFileID, Sint32 compressionType);
	
		virtual void			VCOM_CALLTYPE DeleteAssociations(MCObjectHandle h, Sint16 associationKind);
		virtual MCObjectHandle  VCOM_CALLTYPE CreateTaperedExtrude2(MCObjectHandle profileH, const double_param angle=0.0, const double_param height = 1.0 );
	
		// VW 2014
	public:
		virtual Boolean			VCOM_CALLTYPE EnableTreeControlDragAndDrop(Sint32 dialogID, Sint32 componentID, Boolean bEnable);
		virtual void			VCOM_CALLTYPE EnableDragBetweenControls( Sint32 dialogID, Sint32 source, Sint32 destination );
		virtual Boolean			VCOM_CALLTYPE GetTreeControlItemParent( Sint32 dialogID, Sint32 componentID, Sint32 itemID, Sint32 & parentID );
		virtual int				VCOM_CALLTYPE CopyTreeControlSubtree( Sint32 dialogID, Sint32 sourceTree, Sint32 targetTree, Sint32 sourceItem, Sint32 destinationItem, Sint32 destinationItemParent );
		virtual Boolean			VCOM_CALLTYPE SetTreeControlItemImage( Sint32 dialogID, Sint32 componentID, Sint32 itemID, const TXString & imageSpecifier );
		virtual Boolean			VCOM_CALLTYPE SetTreeControlItemImageFromIcon( Sint32 dialogID, Sint32 componentID, Sint32 itemID, VectorWorks::UI::IIcon* icon );
	
		virtual Boolean         VCOM_CALLTYPE TrimToSelectedObjectsN(MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2, const Boolean bTrimToSelectedObjects = false);
	
		virtual MCObjectHandle	VCOM_CALLTYPE CreateComplexLineType(const TXString& name);
		virtual MCObjectHandle	VCOM_CALLTYPE GetComplexLineTypeGeometryGroup (MCObjectHandle lineTypeH);
		virtual bool			VCOM_CALLTYPE AddComplexLineTypeGeometryObject(MCObjectHandle lineTypeH, MCObjectHandle objectH);
		virtual MCObjectHandle  VCOM_CALLTYPE GetComplexLineTypeGroupParent(MCObjectHandle groupH);
		virtual bool			VCOM_CALLTYPE IsComplexLineTypeGroupContainedObject(MCObjectHandle objectH);
		virtual bool			VCOM_CALLTYPE SetComplexLineTypePageSpace(MCObjectHandle lineTypeH, Boolean isPageSpace);
		virtual bool			VCOM_CALLTYPE IsComplexLineTypeInPageSpace(MCObjectHandle lineTypeH);
		virtual bool			VCOM_CALLTYPE SetComplexLineTypeGapSize(MCObjectHandle lineTypeH, const WorldCoord newGapSize);
		virtual WorldCoord		VCOM_CALLTYPE GetComplexLineTypeGapSize(MCObjectHandle lineTypeH);

		virtual void			VCOM_CALLTYPE GetVWResourceString(TXString& outValue, const char* resourceIdentifier, const char* resourceStringIdentifier, EEmptyHandling allowEmpty);
		virtual GSHandle		VCOM_CALLTYPE GetVWResource(const char* resourceIdentifier);
		virtual Sint32			VCOM_CALLTYPE CreateLayoutDialogFromVWResource(const char* resIdentifier);
		virtual void			VCOM_CALLTYPE RemoveAllTreeControlItems( Sint32 dialogID, Sint32 componentID );

		virtual MCObjectHandle	VCOM_CALLTYPE CreateGroupOutline( MCObjectHandle objectHandle );
	
		virtual void			VCOM_CALLTYPE SetViewMatrixByVector(const WorldPt3& lookFrom, const WorldPt3& lookTo, const WorldPt3& upVector, TransformMatrix& outMatrix, MCObjectHandle activeViewport = NULL);
	
		virtual bool			VCOM_CALLTYPE IsCurtainWall( MCObjectHandle hWall );
		virtual bool			VCOM_CALLTYPE GetCurtainWallPanelInfo( MCObjectHandle hWall, const WorldPt&  inCenterPt, bool includeBottomFrame, WorldPt & outCenterPt, WorldCoord & outWidth, WorldCoord & outHeight );
	
		virtual short			VCOM_CALLTYPE GetNumberOfLineTypesItems(Sint32 dialogID, Sint32 itemID);
		virtual void			VCOM_CALLTYPE GetLineTypeAtIndex(Sint32 dialogID, Sint32 itemID, short index, InternalIndex& outLineTypeRefNumber);
		virtual bool			VCOM_CALLTYPE GetSimpleLineTypeData(MCObjectHandle lineTypeH, bool& outScaleWithThick, std::vector<double>& outData);
	
		virtual MCObjectHandle	VCOM_CALLTYPE Create2DObjectShadow(MCObjectHandle h2DObject, const WorldPt & offsetPt);
	
		virtual Boolean			VCOM_CALLTYPE GetToolPtCurrentIsSnapped();
		virtual Boolean			VCOM_CALLTYPE Project3DModelPtToScreen(const WorldPt3& inwpt3Model, WorldPt& outwptScreen);
	
		virtual MCObjectHandle	VCOM_CALLTYPE GetImageCropObject(MCObjectHandle object);
		virtual bool			VCOM_CALLTYPE IsImageCropped(MCObjectHandle object);
		virtual bool			VCOM_CALLTYPE IsImageCropVisible(MCObjectHandle object);
		virtual void			VCOM_CALLTYPE SetImageCropVisible(MCObjectHandle object, bool isVisible);
		virtual bool			VCOM_CALLTYPE SetImageCropObject(MCObjectHandle imageObject, MCObjectHandle cropObject);
	
		virtual void			VCOM_CALLTYPE TransformGraphicObject(MCObjectHandle object, TransformMatrix& inMatrix);
	
		virtual size_t			VCOM_CALLTYPE GetNumViewportClassOverrides(MCObjectHandle viewportHandle);
		virtual InternalIndex	VCOM_CALLTYPE GetViewportClassOverrideClass(MCObjectHandle viewportHandle, size_t index);
		virtual Boolean			VCOM_CALLTYPE CreateViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex);
		virtual Boolean			VCOM_CALLTYPE GetViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex, SViewportClassOverride& outOverride);
		virtual Boolean			VCOM_CALLTYPE SetViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex, const SViewportClassOverride& inOverride);
		virtual Boolean			VCOM_CALLTYPE RemoveViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex);
	
		virtual size_t			VCOM_CALLTYPE GetNumViewportLightOverrides(MCObjectHandle viewportHandle);
		virtual InternalIndex	VCOM_CALLTYPE GetViewportLightOverrideLight(MCObjectHandle viewportHandle, size_t index);
		virtual Boolean			VCOM_CALLTYPE CreateViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex);
		virtual Boolean			VCOM_CALLTYPE GetViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex, SViewportLightOverride& outOverride);
		virtual Boolean			VCOM_CALLTYPE SetViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex, const SViewportLightOverride& inOverride);
		virtual Boolean			VCOM_CALLTYPE RemoveViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex);
	
		virtual size_t			VCOM_CALLTYPE GetNumViewportLayerOverrides(MCObjectHandle viewportHandle);
		virtual InternalIndex	VCOM_CALLTYPE GetViewportLayerOverrideLayer(MCObjectHandle viewportHandle, size_t index);
		virtual Boolean			VCOM_CALLTYPE CreateViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex);
		virtual Boolean			VCOM_CALLTYPE GetViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, SViewportLayerOverride& outOverride);
		virtual Boolean			VCOM_CALLTYPE SetViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const SViewportLayerOverride& inOverride);
		virtual Boolean			VCOM_CALLTYPE RemoveViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex);
	
		virtual size_t			VCOM_CALLTYPE GetNumViewportLayerPropertiesOverrides(MCObjectHandle viewportHandle);
		virtual InternalIndex	VCOM_CALLTYPE GetViewportLayerPropertiesOverrideLayer(MCObjectHandle viewportHandle, size_t index);
		virtual Boolean			VCOM_CALLTYPE CreateViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex);
		virtual Boolean			VCOM_CALLTYPE GetViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, SViewportLayerPropertiesOverride& outOverride);
		virtual Boolean			VCOM_CALLTYPE SetViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const SViewportLayerPropertiesOverride& inOverride);
		virtual Boolean			VCOM_CALLTYPE RemoveViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex);
	
		virtual size_t			VCOM_CALLTYPE GetNumViewportLayerStackingOverrides(MCObjectHandle viewportHandle);
		virtual InternalIndex	VCOM_CALLTYPE GetViewportLayerStackingOverrideLayer(MCObjectHandle viewportHandle, size_t index);
		virtual Boolean			VCOM_CALLTYPE GetViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, Sint32& outStackingPosition);
		virtual Boolean			VCOM_CALLTYPE SetViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const Sint32& inStackingPosition);
		virtual Boolean			VCOM_CALLTYPE RemoveViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex);
	
		virtual Boolean			VCOM_CALLTYPE IsDesignLayerViewport(MCObjectHandle hObj);
	
		virtual Boolean 		VCOM_CALLTYPE DeleteSavedSetting(const TXString& category);
		virtual Boolean 		VCOM_CALLTYPE DeleteSavedSetting(const TXString& category, const TXString& setting);
	
		virtual MCObjectHandle	VCOM_CALLTYPE TrackToolViewport(Boolean trackDLVP);
	
		virtual void VCOM_CALLTYPE ForEachObjectInList(MCObjectHandle hFirst, GS_ForEachObjectProcPtr action, void *actionEnv);
	
		virtual OpacityRef		VCOM_CALLTYPE GetClOpacity(InternalIndex classIndex);
		virtual void			VCOM_CALLTYPE SetCLOpacity(InternalIndex classIndex, OpacityRef opacity);
		virtual TPlanarRefID	VCOM_CALLTYPE GetWorkingPlanePlanarRefID( );
	
		virtual Boolean			VCOM_CALLTYPE CreateScriptResource(const TXString& scriptName, const TXString& paletteName, bool paletteOpen, const TXString& script, bool python);
		virtual Boolean			VCOM_CALLTYPE GetScriptResource(const TXString& scriptName, TXString& outScript, bool& outPython);
		virtual Boolean			VCOM_CALLTYPE SetScriptResource(const TXString& scriptName, const TXString& script, bool python);
		virtual Boolean			VCOM_CALLTYPE OpenScriptResPalette(const TXString& paletteName, bool paletteOpen);

		virtual MCObjectHandle  VCOM_CALLTYPE GetWallHoleGroupDeep(MCObjectHandle h);

		virtual MCObjectHandle  VCOM_CALLTYPE CreateTextStyleResource(const TXString &name);
		// VW 2015
	public:
		virtual void			VCOM_CALLTYPE GetListOfWorkingPlanes( TVWArray_MCObjectHandle& planesList );
		virtual Boolean			VCOM_CALLTYPE GetWorkingPlaneInfo( MCObjectHandle planeH, TXString& outName, Axis& outAxis );
		virtual Boolean			VCOM_CALLTYPE SetWorkingPlaneInfo( MCObjectHandle planeH, const TXString & name, const Axis axis );
		virtual MCObjectHandle	VCOM_CALLTYPE DuplicateWorkingPlane( MCObjectHandle planeH );
		virtual void			VCOM_CALLTYPE DeleteWorkingPlane( MCObjectHandle planeH );

		virtual void            VCOM_CALLTYPE SysBeep(short duration);
		virtual Uint32			VCOM_CALLTYPE TickCount();
	
		virtual bool            VCOM_CALLTYPE IsFontAvailable(short fontID);
		virtual void			VCOM_CALLTYPE ResetVisibilityForSymbol(MCObjectHandle symDef);

        virtual void            VCOM_CALLTYPE GetStandardFontList (TXStringArray& fontList);
		virtual bool			VCOM_CALLTYPE CanSymbolBeAddedLegal(MCObjectHandle container, MCObjectHandle symDef);

		virtual MCObjectHandle	VCOM_CALLTYPE CreateMesh();
		virtual MCObjectHandle	VCOM_CALLTYPE CreateMesh(IMeshData** outMeshData);
		virtual bool			VCOM_CALLTYPE GetMesh(MCObjectHandle hMesh, IMeshData** outMeshData);
		virtual MCObjectHandle	VCOM_CALLTYPE AddMeshFace(MCObjectHandle hMesh, const TVWArray_SizeT& arrVertexIndices);
        virtual  bool           VCOM_CALLTYPE GetPointInsidePoly(MCObjectHandle poly, WorldPt &insideWorldPt);

		virtual bool			VCOM_CALLTYPE GetGradientDataN(MCObjectHandle gradient, Sint16 segmentIndex, Real64& spotPosition, Real64& midpointPosition, WorldPt3& color, OpacityRef& opacity);
		virtual bool			VCOM_CALLTYPE GetGradientSliderDataN(Sint32 dialogID, Sint32 componentID, Sint16 segmentIndex, Real64& spotPosition, Real64& midpointPosition, WorldPt3& color, OpacityRef& opacity);
		virtual bool			VCOM_CALLTYPE GetGradientSpotOpacity(MCObjectHandle gradient, Sint16 segmentIndex, OpacityRef& opacity);
		virtual Sint16			VCOM_CALLTYPE InsertGradientSegmentN(MCObjectHandle gradient, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity);
		virtual Sint16			VCOM_CALLTYPE InsertGradientSliderSegmentN(Sint32 dialogID, Sint32 componentID, Real64 spotPosition, const WorldPt3& color, const OpacityRef& opacity);
		virtual bool			VCOM_CALLTYPE SetGradientDataN(MCObjectHandle gradient, Sint16& segmentIndex, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity);
		virtual bool			VCOM_CALLTYPE SetGradientSliderDataN(Sint32 dialogID, Sint32 componentID, Sint16& segmentIndex, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity);
		virtual bool			VCOM_CALLTYPE SetGradientSpotOpacity(MCObjectHandle gradient, Sint16 segmentIndex, const OpacityRef& opacity);
        virtual short           VCOM_CALLTYPE GetStandardFontListSize();

		virtual void			VCOM_CALLTYPE SetTreeControlItemAsDivider(Sint32 dialogID, Sint32 componentID, Sint32 itemID, bool isDivider);
		virtual size_t			VCOM_CALLTYPE GetTreeControlItemNumberOfChildren(Sint32 dialogID, Sint32 componentID, Sint32 itemID);
		virtual Sint32			VCOM_CALLTYPE GetTreeControlItemChildID(Sint32 dialogID, Sint32 componentID, Sint32 parentID, Sint32 index);
		virtual void			VCOM_CALLTYPE SetTreeControlItemSelectionState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, bool select);

		virtual MCObjectHandle	VCOM_CALLTYPE GetVerticesFromSolid(MCObjectHandle handle);
		virtual MCObjectHandle	VCOM_CALLTYPE GetNurbsCurvesFromSolid(MCObjectHandle handle);
		virtual MCObjectHandle	VCOM_CALLTYPE GetNurbsSurfacesFromSolid(MCObjectHandle handle);
	    virtual MCObjectHandle	VCOM_CALLTYPE GetNurbsCurvesOnCuttingPlane(MCObjectHandle handle, const WorldPt3& pointOnPlane, const WorldPt3& planeNormal);
		virtual Boolean			VCOM_CALLTYPE CustomObjectControlPtGet(MCObjectHandle inOwnerObj, Sint32 dataIndex, WorldPt3& outPt, Boolean* outIs2DOnly=NULL, Boolean* outIsHidden=NULL, Sint32* outClientID=NULL);
		virtual MCObjectHandle	VCOM_CALLTYPE CreateImageMaskFromAlphaChannel(MCObjectHandle inImage, bool useAlpha=true );
		virtual MCObjectHandle VCOM_CALLTYPE ConvertPolylineToPolylineWithOnlyArcVertices(MCObjectHandle handle, bool insert = false);
		virtual bool			VCOM_CALLTYPE GetTextTabStopCount(MCObjectHandle textBlock, Sint32& count);
		virtual bool			VCOM_CALLTYPE GetTextTabStopLocation(MCObjectHandle textBlock, Sint32 index, WorldCoord& location);
		virtual bool			VCOM_CALLTYPE MoveTextTabStopLocation(MCObjectHandle textBlock, Sint32 index, WorldCoord location);
		virtual bool			VCOM_CALLTYPE AddTextTabStop(MCObjectHandle textBlock, WorldCoord location);
		virtual bool			VCOM_CALLTYPE RemoveTextTabStop(MCObjectHandle textBlock, Sint32 index);
		virtual bool			VCOM_CALLTYPE GetTextTrackingValue(MCObjectHandle textBlock, Sint32 index, float& trackingValue);
		virtual bool			VCOM_CALLTYPE SetTextTrackingValue(MCObjectHandle textBlock, Sint32 index, Sint32 numChars, float trackingValue);

		virtual bool			VCOM_CALLTYPE GetTextStyleByClass(MCObjectHandle handle);
		virtual void			VCOM_CALLTYPE SetTextStyleByClass(MCObjectHandle handle);
		virtual bool			VCOM_CALLTYPE GetClUseTextStyle(InternalIndex classId);
		virtual void			VCOM_CALLTYPE SetClUseTextStyle(InternalIndex classId, bool use);
		virtual InternalIndex	VCOM_CALLTYPE GetClTextStyleRef(InternalIndex classId);
		virtual void			VCOM_CALLTYPE SetClTextStyleRef(InternalIndex classId, InternalIndex textStyleRef);
 		virtual bool			VCOM_CALLTYPE GetObjectWallOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord& offset);
		virtual bool			VCOM_CALLTYPE SetObjectWallHeight(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord height);
		virtual bool			VCOM_CALLTYPE GetObjectWallHeight(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord& height);
		virtual void			VCOM_CALLTYPE SetHatchReferenceForMaterialNode(MCObjectHandle inMaterial, RefNumber inHatchReference);
		virtual void			VCOM_CALLTYPE ClearHatchReferenceForMaterialNode(MCObjectHandle inMaterial);
		virtual RefNumber		VCOM_CALLTYPE GetHatchReferenceForMaterialNode(MCObjectHandle inMaterial);

		virtual TXString		VCOM_CALLTYPE GetDescriptionText(MCObjectHandle hObj);
		virtual bool			VCOM_CALLTYPE SetDescriptionText(MCObjectHandle hObj, const TXString& descriptionText);

		virtual void			VCOM_CALLTYPE RefreshModeBar();
		virtual void			VCOM_CALLTYPE ClearClearPullDownMenu(short group);

		virtual Boolean			VCOM_CALLTYPE RefreshClassPopup(Sint32 dialogID, Sint32 componentID);

		virtual short			VCOM_CALLTYPE GetListBrowserHierarchicalDisplayColumn(Sint32 dialogID, Sint32 componentID);

		virtual MCObjectHandle	VCOM_CALLTYPE GetPDFPageCropObject(MCObjectHandle object);
		virtual bool			VCOM_CALLTYPE IsPDFPageCropped(MCObjectHandle object);
		virtual bool			VCOM_CALLTYPE IsPDFPageCropVisible(MCObjectHandle object);
		virtual void			VCOM_CALLTYPE SetPDFPageCropVisible(MCObjectHandle object, bool isVisible);
		virtual bool			VCOM_CALLTYPE SetPDFPageCropObject(MCObjectHandle pdfPageObject, MCObjectHandle cropObject);
		virtual bool			VCOM_CALLTYPE SetPDFPageWidthAndHeight(MCObjectHandle pdfPageObject, WorldCoord width, WorldCoord height);

		virtual void			VCOM_CALLTYPE SetPerspectiveInfo(short projKind, short renderMode, WorldCoord persDistance, const WorldPt &pt1, const WorldPt &pt2);
		virtual void			VCOM_CALLTYPE SetCurrentView(TStandardView view, bool direct);

		virtual void			VCOM_CALLTYPE CreateSymbolFolderN(const TXString& folderPath, TVWArray_MCObjectHandle & outFolderPath);
		virtual bool			VCOM_CALLTYPE IsCurrentlyBuildingAnUndoEvent();
		virtual bool			VCOM_CALLTYPE ShowCustomDimensionStandardsDialog();
		virtual bool			VCOM_CALLTYPE SetTextStyleRefN(MCObjectHandle textBlock, short firstChar, short numChars, InternalIndex styleRef);
		virtual InternalIndex	VCOM_CALLTYPE GetTextStyleRefN(MCObjectHandle h, short atChar);
		virtual bool			VCOM_CALLTYPE SetTextStyleByClassN(MCObjectHandle textBlock, short firstChar, short numChars);
		virtual bool			VCOM_CALLTYPE GetTextStyleByClassN(MCObjectHandle h, short atChar);

		virtual short			VCOM_CALLTYPE GetNumStoryLevelTemplates();
		virtual TXString		VCOM_CALLTYPE GetStoryLevelTemplateName(short index);
		virtual bool			VCOM_CALLTYPE SetStoryLevelTemplateName(short index, const TXString& name);
		virtual bool			VCOM_CALLTYPE CreateStoryLevelTemplate(TXString& layerName, double scaleFactor, TXString& layerLevelType, WorldCoord elevationOffset, WorldCoord defaultWallHeight, short& index);
		virtual bool			VCOM_CALLTYPE DeleteStoryLevelTemplate(short index);
		virtual bool			VCOM_CALLTYPE GetStoryLevelTemplateInfo(short index, TXString& layerName, double& scaleFactor, TXString& levelType, double& elevation, double& defaultWallHeight);
		virtual bool			VCOM_CALLTYPE AddStoryLevel(MCObjectHandle storyHandle, const TXString& levelType, WorldCoord elevation, const TXString& layerName);
		virtual bool			VCOM_CALLTYPE AddStoryLevelFromTemplate(MCObjectHandle storyHandle, short index);
		virtual bool			VCOM_CALLTYPE RemoveStoryLevel(MCObjectHandle storyHandle, const TXString& levelType, bool bDeleteLayer);
		virtual bool			VCOM_CALLTYPE SetStoryLevelElevation(MCObjectHandle storyHandle, const TXString& levelType, WorldCoord newElevation);
		virtual WorldCoord		VCOM_CALLTYPE GetStoryLevelElevation(MCObjectHandle storyHandle, const TXString& levelType);
		virtual bool			VCOM_CALLTYPE ResetDefaultStoryLevels(bool bDeleteExisting);
		
		virtual MCObjectHandle	VCOM_CALLTYPE TrackToolInViewportAnnotatons(MCObjectHandle &proxyObj, Boolean &worldObjInVP, bool createProxy);

		virtual Boolean			VCOM_CALLTYPE GetComponentTopIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean &topIsRelativeToStory);
		virtual Boolean			VCOM_CALLTYPE SetComponentTopIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean topIsRelativeToStory);
		virtual Boolean			VCOM_CALLTYPE GetComponentBottomIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean &bottomIsRelativeToStory);
		virtual Boolean			VCOM_CALLTYPE SetComponentBottomIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean bottomIsRelativeToStory);

		virtual void			VCOM_CALLTYPE ShowListBrowserHeader(Sint32 dialogID, Sint32 componentID, bool show);

		virtual Boolean			VCOM_CALLTYPE GetListBrowserNumericItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString& itemString, double& itemVal, short& imageIndex);

	// 2015 SP1
	public:	
		virtual bool			VCOM_CALLTYPE GetCurtainWallPanelInfoExtended( MCObjectHandle hWall, const WorldPt & inCenterPt, bool includeBottomFrame, WorldPt & outCenterPt, WorldCoord & outWidth, WorldCoord & outHeight, 
													WorldCoord& panelThickness,   //This is the thickness of the panel as it subtracts from the frames. It is a property of the panel
													WorldCoord& panelOffset,         // This is the dimension from the center of the panel to the center of the wall
													WorldCoord& frameInsetTop,   // The frame inset is the distance the panel extends into and subtracts from the frame. 
													WorldCoord& frameInsetBottom, 
													WorldCoord& frameInsetRight, 
													WorldCoord& frameInsetLeft);
        virtual void  VCOM_CALLTYPE Trim2DObjectWithLine(MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, bool insert, TVWArray_MCObjectHandle & hResultArray);


	// VW 2016
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE GetOtherObjectFromBinaryConstraint(CBSignedShort type, MCObjectHandle obj, CBSignedShort objVertexA, CBSignedShort objVertexB, InternalIndex containedObj, MCObjectHandle& outContraint);
		virtual MCObjectHandle	VCOM_CALLTYPE FindBinbaryConstraintToObject(CBSignedShort type, MCObjectHandle obj, MCObjectHandle toObject, CBSignedShort& outToObjectVertexA, CBSignedShort& outToObjectVertexB, InternalIndex& outToObjectContainedObj);

		// ForEach lambda support
		virtual void				VCOM_CALLTYPE ForEach3DPointInObjectN(MCObjectHandle h, std::function<bool(const WorldPt3& point3D)> callbackLambda);
		virtual void				VCOM_CALLTYPE ForEachPolyEdgeN( MCObjectHandle inPolyH, std::function<void(const SPolyEdge& edge)> callbackLambda);
		virtual void				VCOM_CALLTYPE ForEachLayerN( std::function<void(MCObjectHandle h)> callbackLambda);
		virtual void				VCOM_CALLTYPE ForEachObjectN( short traverseWhat, std::function<void(MCObjectHandle h)> callbackLambda);
		virtual void				VCOM_CALLTYPE ForEachBreakN( MCObjectHandle theWall, std::function<bool(MCObjectHandle h, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData)> callbackLambda);
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFileInStandardFolderN(EFolderSpecifier folderSpec, std::function<bool(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda);
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInStandardFolderN(FolderSpecifier folderSpec, std::function<bool(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda);
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInFolderN(IFolderIdentifier* pStartFolderID, bool doRecursive, std::function<EForEachFileResult(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda);
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInPluginFolderN(std::function<EForEachFileResult(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda);
		virtual void				VCOM_CALLTYPE ForEachObjectInListN(MCObjectHandle hFirst, std::function<void(MCObjectHandle h)> callbackLambda);

		virtual Sint32				VCOM_CALLTYPE SendActiveToolMessage(ToolMessage& message);

		virtual void				VCOM_CALLTYPE AddPullDownResourceMethod(const TXString& label, const TXString& value);
		virtual void				VCOM_CALLTYPE SetPullDownResourceValue(short group, const TXString& value);
		virtual Sint32				VCOM_CALLTYPE ShowPullDownResourcePopup(short group, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize = kStandardSize);
		virtual void				VCOM_CALLTYPE SetImagePopupResourceAdvanced(Sint32 dialogID, Sint32 componentID);
		virtual void				VCOM_CALLTYPE SetImagePopupResourceCategories(Sint32 dialogID, Sint32 componentID, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex);

		virtual bool				VCOM_CALLTYPE GetClassSharedAndUpdateReference (MCObjectHandle hDLVPort, InternalIndex classIndex, bool& outSharedRef, bool& outUpdateRef);
		
		virtual bool				VCOM_CALLTYPE SetObjectAsSpanWallBreak(MCObjectHandle objectHandle, MCObjectHandle wallHandle, bool spanWallBreak);

		virtual bool				VCOM_CALLTYPE GetTreeControlItemCheckBoxState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, Sint32& outState);
		virtual bool				VCOM_CALLTYPE SetTreeControlItemCheckBoxState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, Sint32 state);
		virtual OSType				VCOM_CALLTYPE GetDataMapDataClientID(MCObjectHandle h);
		virtual MCObjectHandle		VCOM_CALLTYPE CreateShellSolid(MCObjectHandle surface, double thickness);
		virtual bool				VCOM_CALLTYPE CreateSlabModifier(MCObjectHandle slab, MCObjectHandle profile, bool isSubtract, Sint16 componentID, bool clipToBoundary);

		virtual bool				VCOM_CALLTYPE ExportImage(IFileIdentifier* fileID, const SExportImageOptions& options);
		virtual bool				VCOM_CALLTYPE ExportSTL(IFileIdentifier* fileID, bool exportBinary, double percentTess, Sint16 exportObjectsOptions);
		virtual bool				VCOM_CALLTYPE ExportSTEP(IFileIdentifier* fileID, bool exportSolidAsSurface);

		virtual void				VCOM_CALLTYPE ForEachClass( Boolean doGuestClasses, std::function<void(MCObjectHandle h)> callbackLambda);

		virtual void				VCOM_CALLTYPE GetParentFolderNameFromResourceList(Sint32 listID, Sint32 index, TXString& name);
		virtual bool				VCOM_CALLTYPE ExportSymbolResource(MCObjectHandle symbolresource, const TXString& symbolFolderDest, IFileIdentifier* pFileID = nil, bool suppressDialogs = false, TImportResourceConflictCallbackProcPtr conflictCallback = nil);
        virtual InternalIndex       VCOM_CALLTYPE GetRoofStyle(MCObjectHandle roof);
        virtual void                VCOM_CALLTYPE SetRoofStyle(MCObjectHandle roof, InternalIndex roofStyle);
        virtual void                VCOM_CALLTYPE ConvertToUnstyledRoof(MCObjectHandle roof);
        virtual InternalIndex       VCOM_CALLTYPE GetRoofPreferencesStyle();
        virtual void                VCOM_CALLTYPE SetRoofPreferencesStyle(InternalIndex roofStyle);
        virtual MCObjectHandle      VCOM_CALLTYPE CreateRoofStyle(const TXString &roofStyleName);
        virtual MCObjectHandle      VCOM_CALLTYPE GetRoofPreferences();
        virtual short               VCOM_CALLTYPE GetDatumRoofComponent(MCObjectHandle object);
        virtual void                VCOM_CALLTYPE SetDatumRoofComponent(MCObjectHandle object, short componentIndex);

		virtual bool				VCOM_CALLTYPE ExportDocument(IFileIdentifier* fileID, short version);
		
       virtual Sint32				VCOM_CALLTYPE BuildResourceListFromOpenFile(const short objectType, const size_t fileRef, Sint32& numItems);
        virtual void                VCOM_CALLTYPE GetFavoritesList (TVWArray_IFileIdentifierPtr& outFavorites);
        virtual void                VCOM_CALLTYPE GetOpenFilesList (TVWArray_OpenFileInformation& outInformation);
		virtual bool				VCOM_CALLTYPE SwitchToOpenFile (Sint32 fileRef);

		virtual bool                VCOM_CALLTYPE TranslateToCurrentVersion (IFileIdentifier* pSrcFileID, IFileIdentifier* pDstFileID);

		virtual void                VCOM_CALLTYPE CalcRoofTopArea(MCObjectHandle object, double& outArea);
		virtual void				VCOM_CALLTYPE SwitchFromPlanTo3DView();

		virtual void				VCOM_CALLTYPE UngroupObject(MCObjectHandle object);
		virtual void				VCOM_CALLTYPE ConvertToGroup(MCObjectHandle object, short convertAction);
		virtual void				VCOM_CALLTYPE ConvertObjectToLines(MCObjectHandle objectH, bool suspendDialog, ConvertModeEnum convertMode);
		virtual void				VCOM_CALLTYPE ConvertObjectToPolygons(MCObjectHandle objectH, bool suspendDialog, ConvertModeEnum convertMode);
		virtual void				VCOM_CALLTYPE SymbolToGroup(MCObjectHandle &theSymbol);
		virtual void				VCOM_CALLTYPE SymbolsInGroupToGroups(MCObjectHandle inObject);

		virtual	GSHandle			VCOM_CALLTYPE ViewCreateCurrent();
		virtual void				VCOM_CALLTYPE ViewDelete(GSHandle hView);
		virtual	GSHandle			VCOM_CALLTYPE ViewDuplicate(GSHandle hView);
		virtual size_t				VCOM_CALLTYPE ViewGetNumLayers(GSHandle hView);
		virtual void				VCOM_CALLTYPE ViewGetLayerVisibility(GSHandle hView, size_t index, InternalIndex& outName, short& outVisibility);
		virtual size_t				VCOM_CALLTYPE ViewGetNumClasses(GSHandle hView);
		virtual void				VCOM_CALLTYPE ViewGetClassVisibility(GSHandle hView, size_t index, InternalIndex& outClassID, short& outVisibility);
		virtual void				VCOM_CALLTYPE ViewStore(GSHandle hView);
		virtual void				VCOM_CALLTYPE ViewRestore(GSHandle hView);

        virtual bool                VCOM_CALLTYPE GetCheckoutsComment(TXString& comment);
        virtual bool                VCOM_CALLTYPE SetCheckoutsComment(const TXString& comment);
        virtual bool                VCOM_CALLTYPE GetCurrentUserId(TXString& userid);
        virtual bool                VCOM_CALLTYPE GetProjectFullPath(IFileIdentifier** ppOutFileID);
        virtual bool                VCOM_CALLTYPE GetWorkingFileId(TXString& uuid);
        virtual bool                VCOM_CALLTYPE IsAWorkingFile();
        virtual bool                VCOM_CALLTYPE IsProjectOffline();
        virtual bool                VCOM_CALLTYPE GetProjectUserNames(TXStringArray& users);
        virtual bool                VCOM_CALLTYPE GetProjectUser(const TXString& userId, TXStringMock fullName, EUserProjectPermission& permission);
        virtual bool                VCOM_CALLTYPE GetLayerProjectInfo(MCObjectHandle layer, LayerProjectInfo& layerInfo);

		virtual MCObjectHandle		VCOM_CALLTYPE GetCustomScreenFeedbackGroup(MCObjectHandle hObject);
		virtual bool				VCOM_CALLTYPE SetCustomScreenFeedbackGroup(MCObjectHandle hObject, MCObjectHandle hFeedbackGroup);
		
        virtual void                VCOM_CALLTYPE SetCurrentLayerN(MCObjectHandle theLayer, Boolean bAllowUnifiedViewMaintenance = false);
		virtual bool				VCOM_CALLTYPE GetViewFromAndToPoints(WorldPt3& fromPt, WorldPt3& toPt);
        virtual void                VCOM_CALLTYPE UpdateBreak(MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData);

		virtual Boolean				VCOM_CALLTYPE GetComponentDatumIsTopOfComponent(MCObjectHandle object, short componentIndex, Boolean &datumIsTopOfComponent);
		virtual Boolean				VCOM_CALLTYPE SetComponentDatumIsTopOfComponent(MCObjectHandle object, short componentIndex, Boolean datumIsTopOfComponent);
		virtual Boolean				VCOM_CALLTYPE GetComponentWallAssociatedBound(MCObjectHandle object, short componentIndex, ERoofWallAssociatedBound &wallAssociatedBound);
		virtual Boolean				VCOM_CALLTYPE SetComponentWallAssociatedBound(MCObjectHandle object, short componentIndex, ERoofWallAssociatedBound wallAssociatedBound);
		virtual Boolean				VCOM_CALLTYPE GetComponentWallAssociatedSectionFillChangePoint(MCObjectHandle object, short componentIndex, ERoofChangePoint &wallAssociatedSectionFillChangePoint);
		virtual Boolean				VCOM_CALLTYPE SetComponentWallAssociatedSectionFillChangePoint(MCObjectHandle object, short componentIndex, ERoofChangePoint wallAssociatedSectionFillChangePoint);
		virtual Boolean				VCOM_CALLTYPE GetComponentWallAssociatedModification(MCObjectHandle object, short componentIndex, ERoofModification &wallAssociatedModification);
		virtual Boolean				VCOM_CALLTYPE SetComponentWallAssociatedModification(MCObjectHandle object, short componentIndex, ERoofModification wallAssociatedModification);
		virtual Boolean				VCOM_CALLTYPE GetComponentManualBound(MCObjectHandle object, short componentIndex, ERoofManualBound &manualBound);
		virtual Boolean				VCOM_CALLTYPE SetComponentManualBound(MCObjectHandle object, short componentIndex, ERoofManualBound manualBound);
		virtual Boolean				VCOM_CALLTYPE GetComponentBoundOffset(MCObjectHandle object, short componentIndex, WorldCoord &boundOffset);
		virtual Boolean				VCOM_CALLTYPE SetComponentBoundOffset(MCObjectHandle object, short componentIndex, WorldCoord boundOffset);
		virtual Boolean				VCOM_CALLTYPE GetComponentAlwaysAutoJoinInCappedJoinMode(MCObjectHandle object, short componentIndex, Boolean &alwaysAutoJoinInCappedJoinMode);
		virtual Boolean				VCOM_CALLTYPE SetComponentAlwaysAutoJoinInCappedJoinMode(MCObjectHandle object, short componentIndex, Boolean alwaysAutoJoinInCappedJoinMode);
		virtual Boolean				VCOM_CALLTYPE GetComponentAlternateSectionFill(MCObjectHandle object, short componentIndex, Sint32 &alternateSectionFill);
		virtual Boolean				VCOM_CALLTYPE SetComponentAlternateSectionFill(MCObjectHandle object, short componentIndex, Sint32 alternateSectionFill);
		virtual Boolean				VCOM_CALLTYPE GetComponentPenStylesN(MCObjectHandle object, short componentIndex, InternalIndex &leftPenStyle, InternalIndex &rightPenStyle);
		virtual Boolean				VCOM_CALLTYPE SetComponentPenStylesN(MCObjectHandle object, short componentIndex, InternalIndex leftPenStyle, InternalIndex rightPenStyle);
		virtual Boolean				VCOM_CALLTYPE GetComponentAlternateSectionFillColors(MCObjectHandle object, short componentIndex, ColorRef &alternateSectionFillForeColor, ColorRef &alternateSectionFillBackColor);
		virtual Boolean				VCOM_CALLTYPE SetComponentAlternateSectionFillColors(MCObjectHandle object, short componentIndex, ColorRef alternateSectionFillForeColor, ColorRef alternateSectionFillBackColor);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassFillStyleForFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillStyleForFill);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassFillStyleForFill(MCObjectHandle object, short componentIndex, Boolean useClassFillStyleForFill);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassFillColorsForFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillColorsForFill);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassFillColorsForFill(MCObjectHandle object, short componentIndex, Boolean useClassFillColorsForFill);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassFillStyleForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillStyleForAlternateSectionFill);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassFillStyleForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean useClassFillStyleForAlternateSectionFill);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassFillColorsForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillColorsForAlternateSectionFill);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassFillColorsForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean useClassFillColorsForAlternateSectionFill);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenStyleForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenStyleForLeftPen);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenStyleForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenStyleForLeftPen);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenWeightForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenWeightForLeftPen);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenWeightForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenWeightForLeftPen);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenColorsForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenColorsForLeftPen);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenColorsForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenColorsForLeftPen);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenStyleForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenStyleForRightPen);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenStyleForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenStyleForRightPen);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenWeightForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenWeightForRightPen);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenWeightForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenWeightForRightPen);
		virtual Boolean				VCOM_CALLTYPE GetComponentUseClassPenColorsForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenColorsForRightPen);
		virtual Boolean				VCOM_CALLTYPE SetComponentUseClassPenColorsForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenColorsForRightPen);

		virtual void				VCOM_CALLTYPE SetIsCurtainWall(MCObjectHandle wall, bool isCurtainWall);
		virtual WorldCoord			VCOM_CALLTYPE GetCurtainWallCutPlane(MCObjectHandle wall);
		virtual void				VCOM_CALLTYPE SetCurtainWallCutPlane(MCObjectHandle wall, WorldCoord curtainWallCutPlane);
		virtual MCObjectHandle		VCOM_CALLTYPE MirrorObject(MCObjectHandle h, bool dup, const WorldPt& p1, const WorldPt& p2);

	// VW 2017
	public:
		virtual Sint32				VCOM_CALLTYPE ShowPullDownResourcePopupN(const ViewPt& pt, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize = kStandardSize);
		virtual Boolean             VCOM_CALLTYPE ResetNurbsCurve(MCObjectHandle curveHandle, const WorldPt3& firstPt, bool byCtrlPts, short degree);
		virtual Boolean				VCOM_CALLTYPE SetArc(MCObjectHandle hArc, const WorldPt& center, double radius, double startAngle, double sweepAngle);

		virtual void				VCOM_CALLTYPE GetOpacityN( MCObjectHandle h, OpacityRef& outPenOpacity,	 OpacityRef& outFillOpacity );
		virtual void				VCOM_CALLTYPE SetOpacityN( MCObjectHandle h, OpacityRef inNewPenOpacity, OpacityRef inNewFillOpacity );
		virtual void				VCOM_CALLTYPE GetOpacityByClassN( MCObjectHandle h, Boolean& outPenOpacityByClass,	Boolean& outFillOpacityByClass );
		virtual void				VCOM_CALLTYPE SetOpacityByClassN( MCObjectHandle h, Boolean inPenOpacityByClass,	Boolean inFillOpacityByClass );
		virtual void				VCOM_CALLTYPE GetDefaultOpacityN( OpacityRef& outPenOpacity, OpacityRef& outFillOpacity );
		virtual void				VCOM_CALLTYPE SetDefaultOpacityN( OpacityRef outPenOpacity,  OpacityRef outFillOpacity );
		virtual void				VCOM_CALLTYPE GetDefaultOpacityByClassN( Boolean& outPenOpacityByClass, Boolean& outFillOpacityByClass );
		virtual void				VCOM_CALLTYPE SetDefaultOpacityByClassN( Boolean inPenOpacityByClass,	Boolean inFillOpacityByClass );
		virtual void				VCOM_CALLTYPE GetClOpacityN( InternalIndex classIndex, OpacityRef& penOpacity,	OpacityRef& fillOpacity );
		virtual void				VCOM_CALLTYPE SetCLOpacityN( InternalIndex classIndex, OpacityRef penOpacity,	OpacityRef fillOpacity );
        
        //For PointTools_Isolating points
        virtual Boolean             VCOM_CALLTYPE MarqueeEmptyList();
        virtual Boolean             VCOM_CALLTYPE MarqueeAddObject(MCObjectHandle hInObject);
        virtual MCObjectHandle      VCOM_CALLTYPE GetFreehandInteractivePoly();
        virtual void                VCOM_CALLTYPE BeginFreehandInteractive();
        virtual void                VCOM_CALLTYPE UpdateFreehandInteractive();
        virtual MCObjectHandle      VCOM_CALLTYPE EndFreehandInteractive();

		virtual Boolean				VCOM_CALLTYPE IsPlanRotationView();

		virtual MCObjectHandle	    VCOM_CALLTYPE CreateHelicalAlongCurve(MCObjectHandle curveHandle, double radius1, double radius2, double startAngle, double& pitch, double& numTurns, bool bPitch, bool bReverseTwist, bool bFlat);

		virtual void				VCOM_CALLTYPE ViewRestoreN(MCObjectHandle hView, Boolean bDontRegen3DBounds);
		virtual void				VCOM_CALLTYPE RestoreSavedViewN(const TXString& savedView, Boolean bDontRegen3DBounds);
        virtual void                VCOM_CALLTYPE PerformMultipleUnion_2(TVWArray_MCObjectHandle  hArray, TVWArray_MCObjectHandle & hArrayResult, bool insert);
		virtual Boolean	            VCOM_CALLTYPE CreateDuplicateAlongPath(TVWArray_MCObjectHandle hProfileArray, MCObjectHandle inPathH, Boolean bUseNumber, Sint32 inNumber, double inDistance, double inStartOffset, Boolean bCenterObject, Boolean bTangent, Boolean bKeepOrienation, TVWArray_MCObjectHandle &outDuplicateArray);
 

		virtual void				VCOM_CALLTYPE RemoveCustomTextureParts(MCObjectHandle h);
		virtual void				VCOM_CALLTYPE AddCustomTexturePart(MCObjectHandle h, Sint32 partID, const TXString& partName);
		virtual Boolean				VCOM_CALLTYPE CustomTexturePartExists(MCObjectHandle h, Sint32 partID);
		virtual void				VCOM_CALLTYPE ApplyCustomTexturePart(MCObjectHandle srcObj, MCObjectHandle destObj, Sint32 partID);
 
		virtual Boolean				VCOM_CALLTYPE GetPluginObjectStyle( MCObjectHandle h, RefNumber& styleRefNumber );
		virtual Boolean				VCOM_CALLTYPE SetPluginObjectStyle( MCObjectHandle h, RefNumber styleRefNumber );
		virtual void				VCOM_CALLTYPE UpdatePIOFromStyle( MCObjectHandle h );
		virtual bool				VCOM_CALLTYPE GetPluginStyleForTool( const TXString & toolUnivName, RefNumber& styleRefNumber );
		virtual bool				VCOM_CALLTYPE SetPluginStyleForTool( const TXString & toolUnivName, const RefNumber styleRefNumber );
		virtual bool				VCOM_CALLTYPE GetObjectWallInsertMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, InsertModeType& insertMode );
		virtual bool				VCOM_CALLTYPE SetObjectWallInsertMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, InsertModeType insertMode );
		virtual bool				VCOM_CALLTYPE GetObjectWallBreakMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, BreakModeType& breakMode );
		virtual bool				VCOM_CALLTYPE SetObjectWallBreakMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, BreakModeType breakMode );

		virtual void				VCOM_CALLTYPE ViewRect2WorldRect(const ViewRect& vRect, WorldRect& wRect);

        virtual MCObjectHandle      VCOM_CALLTYPE GetObjectByUuid(const TXString& uuid);
        virtual bool                VCOM_CALLTYPE GetObjectUuid(MCObjectHandle h, TXString& uuid);

		
		// Drop Shadow changes
		virtual bool	VCOM_CALLTYPE IsDropShadowEnabled(MCObjectHandle h);
		virtual void	VCOM_CALLTYPE EnableDropShadow (MCObjectHandle h, bool enable);
 
		virtual bool	VCOM_CALLTYPE GetDropShadowData(MCObjectHandle h, SDropShadowData & outDropShadowData);
		virtual void	VCOM_CALLTYPE SetDropShadowData(MCObjectHandle h, const SDropShadowData& inDropShadowData);
		virtual void	VCOM_CALLTYPE DeleteDropShadowData(MCObjectHandle h);
 
		virtual void	VCOM_CALLTYPE ShowDropShadowDialog(SDropShadowData& ioSDropShadowData, bool& ioByClass);
 
		virtual bool	VCOM_CALLTYPE IsDropShadowByClass(MCObjectHandle h);
		virtual void	VCOM_CALLTYPE SetDropShadowByClass(MCObjectHandle h, bool inSetByClass); 
 
		virtual void	VCOM_CALLTYPE GetClDropShadowData(InternalIndex classIndex, SDropShadowData& outDropShadowData);
		virtual void	VCOM_CALLTYPE SetClDropShadowData(InternalIndex classIndex, SDropShadowData& inDropShadowData);
 
		virtual bool	VCOM_CALLTYPE IsDropShadowEnabledInDocument();
		virtual void	VCOM_CALLTYPE SetDropShadowByClassInDocument(bool inSetByClass); 
 
		virtual void	VCOM_CALLTYPE GetDocumentDropShadowData( SDropShadowData& outDropShadowData);
		virtual void	VCOM_CALLTYPE SetDocumentDropShadowData( const SDropShadowData& inDropShadowData);

		virtual bool	VCOM_CALLTYPE DropShadowDataAreEqual(const SDropShadowData& inDropShadowData1, const SDropShadowData& inDropShadowData2);

		virtual bool	VCOM_CALLTYPE GetAllCombinedsurfaces(MCObjectHandle baseObject, const TVWArray_MCObjectHandle& arrClipObjects, TXGenericArray< std::pair<MCObjectHandle, TVWArray_SizeT> >& arrResult, std::function<bool(size_t,size_t)> progressCallback=nullptr);


		// For Slab drainage (Flat Roofs)
		virtual short				VCOM_CALLTYPE AddDrain(MCObjectHandle slab, WorldPt location, WorldCoord height, double angle);
		virtual short				VCOM_CALLTYPE ConnectDrains(MCObjectHandle slab, short index1, short index2, short connectionType, double slopeAngle, double splitSlopeAngle);
		virtual short				VCOM_CALLTYPE AddSlopeValley(MCObjectHandle slab, short index, WorldPt controlPt, double slope, double edgeHeight);
		virtual short				VCOM_CALLTYPE GetNumDrains(MCObjectHandle slab);
		virtual short				VCOM_CALLTYPE GetNumDrainConnections(MCObjectHandle slab);
		virtual bool				VCOM_CALLTYPE SetDrainHeight(MCObjectHandle slab, short index, double height);
		virtual double				VCOM_CALLTYPE GetDrainHeight(MCObjectHandle slab, short index);
		virtual WorldPt				VCOM_CALLTYPE GetDrainLocation(MCObjectHandle slab, short index);
		virtual bool				VCOM_CALLTYPE SetDrainLocation(MCObjectHandle slab, short index, const WorldPt& location);
		virtual void                VCOM_CALLTYPE RotateDrain(MCObjectHandle slab, short index, double angle);
		virtual double				VCOM_CALLTYPE GetDrainDrainageArea(MCObjectHandle slab, short index);
		virtual MCObjectHandle		VCOM_CALLTYPE GetDrainSymbol(MCObjectHandle slab, short index);
		virtual bool				VCOM_CALLTYPE SetDrainSymbol(MCObjectHandle slab, short index, MCObjectHandle symbol);
		virtual short				VCOM_CALLTYPE GetNumDrainSlopeValleys(MCObjectHandle slab, short index);
		virtual bool				VCOM_CALLTYPE GetDrainSlopeValley(MCObjectHandle slab, short drain, short valley, WorldPt& controlPt, double& slope, double& edgeHeight, bool& heightLocked);
		virtual void                VCOM_CALLTYPE SetDrainSlopeValley (MCObjectHandle slab, short drain, short valley, WorldPt controlPt, double slope, double edgeHeight, bool lockHeight);
		virtual short				VCOM_CALLTYPE GetNumDrainConnections(MCObjectHandle slab, short drain);
		virtual short				VCOM_CALLTYPE GetDrainConnectionIndex(MCObjectHandle slab, short drain, short index);
		virtual bool				VCOM_CALLTYPE GetDrainConnection(MCObjectHandle slab, short index, short& drain1, short& drain2, short& style, double& angle1, double& angle2);
		virtual bool				VCOM_CALLTYPE SetDrainConnection(MCObjectHandle slab, short index, short style, double angle1, double angle2);
		virtual bool				VCOM_CALLTYPE DeleteDrainConnection(MCObjectHandle slab, short index);
		virtual bool				VCOM_CALLTYPE DeleteSlopeValley(MCObjectHandle, short drain, short index, bool forceDelete);
		virtual bool				VCOM_CALLTYPE DeleteDrain(MCObjectHandle slab, short index);

		virtual RefNumber	VCOM_CALLTYPE ChoosePluginStyleForTool( TInternalID internalToolID, RefNumber excludeRefNumber, const TXString & title = "", const TXString & message = ""  );
		virtual void		VCOM_CALLTYPE ChoosePluginStyleForReplace( MCObjectHandle hObj );
		virtual Sint32		VCOM_CALLTYPE GetSymbolDefSubType( MCObjectHandle hObj );
		virtual void		VCOM_CALLTYPE SetSymbolDefSubType( MCObjectHandle hObj, Sint32 subType );
		virtual bool		VCOM_CALLTYPE GetPluginStyleSymbol( MCObjectHandle hObj, MCObjectHandle & hSymbolDefinition );

		virtual bool			VCOM_CALLTYPE GetLayerEnableCutPlane(MCObjectHandle layer);
		virtual void			VCOM_CALLTYPE SetLayerEnableCutPlane(MCObjectHandle layer, bool enableCutPlane);
		virtual WorldCoord		VCOM_CALLTYPE GetLayerCutPlane(MCObjectHandle layer);
		virtual void			VCOM_CALLTYPE SetLayerCutPlane(MCObjectHandle layer, WorldCoord cutPlane);
		virtual InternalIndex	VCOM_CALLTYPE GetWallBelowCutPlaneClass(MCObjectHandle wall);
		virtual void			VCOM_CALLTYPE SetWallBelowCutPlaneClass(MCObjectHandle wall, InternalIndex belowCutPlaneClass);
		virtual short			VCOM_CALLTYPE GetTaperedComponent(MCObjectHandle object);
		virtual void			VCOM_CALLTYPE SetTaperedComponent(MCObjectHandle object, short componentIndex);
		virtual Boolean			VCOM_CALLTYPE GetComponentAutoBoundEdgeOffsetOffset(MCObjectHandle object, short componentIndex, WorldCoord &autoBoundEdgeOffsetOffset);
		virtual Boolean			VCOM_CALLTYPE SetComponentAutoBoundEdgeOffsetOffset(MCObjectHandle object, short componentIndex, WorldCoord autoBoundEdgeOffsetOffset);
		virtual Boolean			VCOM_CALLTYPE GetComponentMasterSnaps(MCObjectHandle object, short componentIndex, Boolean &masterSnapOnLeft, Boolean &masterSnapOnRight);
		virtual Boolean			VCOM_CALLTYPE SetComponentMasterSnaps(MCObjectHandle object, short componentIndex, Boolean masterSnapOnLeft, Boolean masterSnapOnRight);
		virtual EPluginStyleParameter		VCOM_CALLTYPE GetPluginStyleParameterType( MCObjectHandle object, const TXString& paramName );
		virtual void						VCOM_CALLTYPE SetPluginStyleParameterType( MCObjectHandle hSymbol, const TXString& paramName, EPluginStyleParameter styleType );
		virtual void						VCOM_CALLTYPE SetAllPluginStyleParameters( MCObjectHandle hSymbol, EPluginStyleParameter styleType );

		virtual void		VCOM_CALLTYPE InteractiveViewOperation_GetFlyOverOrigin( ViewPt& curFlyOverOrigin ); 

		// Resource Manager support
		virtual void			VCOM_CALLTYPE PullDownResourceSetToolBarPopup(short group, VectorWorks::Extension::IResourceManagerContent* content);
		virtual TXString		VCOM_CALLTYPE PullDownResourceGetSelectedResourceName(short group);
		virtual void			VCOM_CALLTYPE PullDownResourceSetSelectedResourceName(short group, const TXString& name);
		virtual void			VCOM_CALLTYPE PullDownResourceLayoutInit(Sint32 dialogID, Sint32 itemID, VectorWorks::Extension::IResourceManagerContent* content);
		virtual TXString		VCOM_CALLTYPE PullDownResourceLayoutGetSelectedResourceName(Sint32 dialogID, Sint32 itemID);
		virtual void			VCOM_CALLTYPE PullDownResourceLayoutSetSelectedResourceName(Sint32 dialogID, Sint32 itemID, const TXString& name);
		virtual bool			VCOM_CALLTYPE RebuildFileInResourceManager(IFileIdentifier*   pFileID);
		virtual bool			VCOM_CALLTYPE RefreshLibrariesInResourceManager(SRefreshLibrariesOptions&);

		virtual double			VCOM_CALLTYPE GetWorksheetImageScaleFactor(MCObjectHandle hWorksheetImage);
		virtual bool			VCOM_CALLTYPE SetWorksheetImageScaleFactor(MCObjectHandle hWorksheetImage, double scale, bool redrawImage);
		virtual void			VCOM_CALLTYPE SetWorksheetCellsImageResolution(MCObjectHandle hWorksheet, Sint16 dpiResolution);
		virtual Sint16			VCOM_CALLTYPE GetWorksheetCellsImageResolution(MCObjectHandle hWorksheet);

		virtual MCObjectHandle  VCOM_CALLTYPE CreateResourceFolder(const TXString& name, Sint16 resourceType);
		virtual void			VCOM_CALLTYPE CreateResourceFolderN(const TXString& folderPath, Sint16 resourceType, TVWArray_MCObjectHandle & outFolderPath);
		virtual bool			VCOM_CALLTYPE AddResourceTags(MCObjectHandle h, const TXStringArray& arrTags);
		virtual bool			VCOM_CALLTYPE GetResourceTags(MCObjectHandle h, TXStringArray& arrTags);

		virtual bool			VCOM_CALLTYPE IsPluginStyle( MCObjectHandle h );

        virtual bool            VCOM_CALLTYPE IsActiveSymbolInCurrentDocument() ;

		virtual bool			VCOM_CALLTYPE AddItemToPluginStyle( MCObjectHandle hSymDef, const TXString & itemName, EPluginStyleParameter styleType );
		virtual bool			VCOM_CALLTYPE RemoveItemFromPluginStyle( MCObjectHandle hSymDef, const TXString & itemName );

		virtual bool			VCOM_CALLTYPE GetDimensionsAssociatedToPlugin( MCObjectHandle hPlugin, TVWArray_MCObjectHandle &dimHandles );
		virtual bool			VCOM_CALLTYPE GetChainThatContainsDimension( MCObjectHandle hDim, MCObjectHandle &hChain );

		virtual MCObjectHandle	VCOM_CALLTYPE CreateVWObjectFromSplineData(const TVWArray_WorldPt3& controlPoints, const TVWArray_Double& weights, const TVWArray_Double& knots, Sint32 degree, bool isRational, bool isClosed, bool create2D);

        virtual bool            VCOM_CALLTYPE SetDefaultGenericStoryLevelBound( MCObjectHandle hFormat, const SStoryObjectData& data );
		virtual bool            VCOM_CALLTYPE GetDefaultGenericStoryLevelBound( MCObjectHandle hFormat, SStoryObjectData& data );

		virtual void            VCOM_CALLTYPE GetStoryBoundChoiceStringsN( MCObjectHandle story, TXStringArray& outStrings, EStoryLevelPopupBoundType boundType);

		virtual Sint32			VCOM_CALLTYPE AddResourceToListUnsorted(Sint32 listID, MCObjectHandle obj);
		virtual Sint32			VCOM_CALLTYPE BuildResourceListUnsorted(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems);

		virtual bool			VCOM_CALLTYPE CreateReference( IFileIdentifier* pFileID );
		
	// VW 2017 SP 2
	public:
		virtual void			VCOM_CALLTYPE UpdateStyledObjects( RefNumber styleRefNumber );
		virtual void			VCOM_CALLTYPE GetStoryLevels( MCObjectHandle story, TXStringArray& outStrings);

	// VW 2017 SP3
	public:
		virtual void			VCOM_CALLTYPE InitClassOverrideData(InternalIndex classIndex, SViewportClassOverride& outData);
		virtual void			VCOM_CALLTYPE InitLayerOverrideData(InternalIndex layerIndex, SViewportLayerOverride& outData);
		virtual void			VCOM_CALLTYPE InitLightOverrideData(InternalIndex lightIndex, SViewportLightOverride& outData);

	// VW 2018
	public:
		//Exposes STEP export
		virtual void			VCOM_CALLTYPE GetCurrentWorkspace(VectorWorks::Workspaces::IWorkspaceFile** outWorkspace);
		virtual bool 			VCOM_CALLTYPE InstallConstraintPlane(TPlanarRefID constrainPlanarRefID, const WorldPt& wptStartPt);
		
		// Paremetric Style Edit List
		virtual bool			VCOM_CALLTYPE AddItemToPluginStyleEditList( MCObjectHandle hObj, const TXString & itemName, EPluginStyleEditList editListType, const TXString & displayName = "" );
		virtual bool			VCOM_CALLTYPE RemoveItemFromPluginStyleEditList( MCObjectHandle hObj, const TXString & itemName );
		virtual bool			VCOM_CALLTYPE GetPluginStyleEditListType( MCObjectHandle hObj, const TXString& paramName, EPluginStyleEditList & editListTyle, TXString & displayName );

        virtual MCObjectHandle  VCOM_CALLTYPE OffsetPolyClosed(MCObjectHandle h, double offset, bool smoothConers);

		virtual MCObjectHandle  VCOM_CALLTYPE CreateImgFromSymbol( const TXString & symbolName, SymbolImgInfo& imgInfoInOut);
		virtual MCObjectHandle  VCOM_CALLTYPE CreateFillSpace(MCObjectHandle owner);
		virtual short		    VCOM_CALLTYPE CountFillSpaces(MCObjectHandle h);
		virtual MCObjectHandle  VCOM_CALLTYPE GetFillSpace(MCObjectHandle h, short index);		

        virtual void            VCOM_CALLTYPE GetSelInsertsInWall( MCObjectHandle hObj, TVWArray_MCObjectHandle& selInserts);

		//Adds proxy information to cURL handle
		virtual bool 			VCOM_CALLTYPE GetCurlProxyInfo(TXString& outProxyType, TXString& outAddress, Sint32& outPort, TXString& outUsername, TXString& outPassword);

		virtual TXString		VCOM_CALLTYPE GetFormattedDateTimeString(EDateTimeFormat dateTimeFormat);
		virtual TXString		VCOM_CALLTYPE GetFormattedDateTimeString(EDateTimeFormat dateTimeFormat, const SDateTimeData& dateTimeData);
		virtual TXString		VCOM_CALLTYPE GetLocalSystemDateTimeString(EDateFormat dateFormat, EInfoFormat infoFormat);
		virtual bool			VCOM_CALLTYPE GetDateTimeIntlData(TDateTimeIntlData& outDateTimeIntlData);
	
		virtual void			VCOM_CALLTYPE SetHotSpotColor(HotSpotRefID inHotSpotID, GSColor color);
		virtual void			VCOM_CALLTYPE DrawHotSpots();

		virtual void			VCOM_CALLTYPE EnterObjectGroup(MCObjectHandle hGroup);

		virtual bool			VCOM_CALLTYPE IsSymDefUsedInEditContext(MCObjectHandle hSymDef);
		virtual bool			VCOM_CALLTYPE GetCatalogPath( MCObjectHandle hObj, EFolderSpecifier & folderSpec, TXString & relativePath );
		virtual bool			VCOM_CALLTYPE SelectPluginCatalog( MCObjectHandle hSymDef );
		virtual bool			VCOM_CALLTYPE SelectItemFromPluginCatalog( MCObjectHandle hObj, const TXString & catName = "", std::function<TXString(const TXString & id, EEmptyHandling opt)> columnNamesLocalizer = nullptr );
		virtual bool			VCOM_CALLTYPE AplyFirstCatalogItem( MCObjectHandle hObj, const TXString & catName = "" );

		virtual Boolean			VCOM_CALLTYPE GetComponentFunction(MCObjectHandle object, short componentIndex, EComponentFunction &function);
		virtual Boolean			VCOM_CALLTYPE SetComponentFunction(MCObjectHandle object, short componentIndex, EComponentFunction function);
		virtual bool			VCOM_CALLTYPE IsCatalogParameter( MCObjectHandle hObj, const TXString & paramName );
		virtual void			VCOM_CALLTYPE SetUseCatalogItem( MCObjectHandle hObj, const bool & useCatItem );
		virtual bool			VCOM_CALLTYPE GetUseCatalogItem( MCObjectHandle hObj );
		virtual void			VCOM_CALLTYPE SetCatalogItemByStyle( MCObjectHandle hObj, const bool & byStyle );
		virtual bool			VCOM_CALLTYPE GetCatalogItemByStyle( MCObjectHandle hObj );

		virtual MCObjectHandle	VCOM_CALLTYPE FitExtrudeToObjects(MCObjectHandle hExtrude, bool isTopFit, EFitExtrudeToObjectsOption boundOption, double defaultHeight, TVWArray_MCObjectHandle clippingHandleArray, EFitExtrudeToObjectsRoofAndSlabOption roofSlabOption);

		// Resource Manager support
		// folderPath - input - path relative to Libraries folder; path separators are '\' 
		// example, Defaults\folder1\folder2
		// pOutFileID - output in case of success - downloaded file on the local drive
		virtual EDownloadErrors VCOM_CALLTYPE DownloadLibraryFile(ELibrariesID libraryID, const TXString& folderPath, const TXString& fileName, IFileIdentifier** ppOutFileID, SDownloadParams& params);
		virtual EDownloadErrors VCOM_CALLTYPE DownloadLibraryFile(ELibrariesID libraryID, EFolderSpecifier folderID, const TXString& fileName, IFileIdentifier** ppOutFileID, SDownloadParams& params);
        virtual MCObjectHandle	VCOM_CALLTYPE GetWallEndCapFootPrint(MCObjectHandle theWall, bool atStart);

		virtual bool			VCOM_CALLTYPE SimplifyMesh(MCObjectHandle meshHandle, float quality);

		virtual bool			VCOM_CALLTYPE SetToolPt2D(Sint32 inIndex, const WorldPt& inToolPoint);
		virtual bool			VCOM_CALLTYPE SetToolPt3D(Sint32 inIndex, const WorldPt3& inToolPoint);
		virtual short			VCOM_CALLTYPE GetObjTypeProperties(short objectType);

		virtual bool			VCOM_CALLTYPE GetWorksheetImageShowDBHeaders(MCObjectHandle hWorksheetImage);
		virtual void			VCOM_CALLTYPE SetWorksheetImageShowDBHeaders(MCObjectHandle hWorksheetImage, bool show, bool redrawImage);

		virtual void			VCOM_CALLTYPE DisplayDocumentPreferences(EDocumentPrefsTab tabToSelect);

		virtual size_t			VCOM_CALLTYPE GetResourceStringTableSize(const char* resIdentifier);

		virtual bool			VCOM_CALLTYPE UpdateImageControlUsingFullFilePath(Sint32 dialogID, Sint32 controlID, IFileIdentifier* imgFileID);
		virtual void			VCOM_CALLTYPE GetReferencedFilesInfo(TVWArray_ReferencedFileInfo& outRefFilesInfo);
		virtual void			VCOM_CALLTYPE DeleteReferencedFiles(TVWArray_ReferencedFileInfo& outRefFilesInfo, const SDeleteFileOptions fileOptions); 

		// For Multiview
		virtual void			VCOM_CALLTYPE SetFocusOnSelectedViewPane(bool bMakeItActive = true, bool bUpdateUI = false);

		virtual void			VCOM_CALLTYPE GetPageBoundsN(MCObjectHandle hLayer, WorldRect& bounds);
		virtual void			VCOM_CALLTYPE TrackToolN(MCObjectHandle& overObject, MCObjectHandle& overSubObject, short& overPart, SintptrT& code);
	
	// VW 2018 SP 1
	public:
		virtual void			VCOM_CALLTYPE SetWorksheetCellCOBieValue(MCObjectHandle worksheet, const ViewPt& cell, const TXString& formula);
        
    // VW 2018 SP 3
    public:
        virtual void            VCOM_CALLTYPE GetSlabHolesAndTheirMiters(MCObjectHandle hSlab, TVWArray_MCObjectHandle& outHolesArray, TVWArray_SizeT& outMitersArray);

	// VW2019
	public:
		virtual short			VCOM_CALLTYPE GetDlgCtrlWidthStdChar(const TXString& str);

		virtual bool            VCOM_CALLTYPE ExportResourceList(const TVWArray_MCObjectHandle& inResourceList, IFileIdentifier* pFileID = nullptr, bool suppressDialogs = false);
		virtual bool            VCOM_CALLTYPE ExportResourceListN(const TVWArray_MCObjectHandle& inResourceList, IFileIdentifier* pFileID = nullptr, TImportResourceConflictCallbackProcPtr conflictCallback = nullptr);

		virtual TXString		VCOM_CALLTYPE GetHierarchicalListBrowserRowContainerPath(Sint32 dialogID, Sint32 componentID, Sint32 rowIndex);
		virtual void			VCOM_CALLTYPE SelectInResourceManager(MCObjectHandle requestedResource);

		virtual bool            VCOM_CALLTYPE BeginMultipleMove();
		virtual bool            VCOM_CALLTYPE EndMultipleMove();

		virtual bool			VCOM_CALLTYPE GetWallAngleVector(const MCObjectHandle& wallHandle, const WorldPt& rotationCenter, WorldPt& wallVector);

		virtual void			VCOM_CALLTYPE CoordToDimStringInUnits(WorldCoord value, VectorWorks::Units::IVWUnits* dimUnit, TXString& str);
		virtual void			VCOM_CALLTYPE DoubleToStringInUnits(TNumStyleClass inNumStyle, Byte inAccuracy, Byte inFormat, double_param inDouble, VectorWorks::Units::IVWUnits* dimUnit, TXString& outString);

		virtual size_t			VCOM_CALLTYPE GetPDFAnnotationsCount(MCObjectHandle object);
		//For line type re-engineering
		virtual Boolean			VCOM_CALLTYPE GetCumulativeDashPat(InternalIndex dashLineType, DashPatType& outDashPat);
		virtual Boolean			VCOM_CALLTYPE GetSimpleLineTypeDefinition(const InternalIndex lineTypeRef, DashPatDef& outDashPat);
		virtual InternalIndex	VCOM_CALLTYPE CreateOrFindSimpleLineTypeDefinition(const DashPatDef& inDashPat);
		virtual InternalIndex	VCOM_CALLTYPE GetDashLineStyle(bool scaleWithThick, const std::vector<double>& theVectors);
		virtual Boolean			VCOM_CALLTYPE SetDashLineTypeName(InternalIndex dashLineType, const TXString& dashStyleName);
		virtual TXString		VCOM_CALLTYPE GetDashLineTypeName(InternalIndex dashLineType);
		virtual Boolean			VCOM_CALLTYPE GetDLComponentPenStylesN(Sint16 index, InternalIndex& outPenStyleLeft, InternalIndex& outPenStyleRight);
		virtual Boolean			VCOM_CALLTYPE SetDLComponentPenStylesN(Sint16 index, InternalIndex penStyleLeft, InternalIndex penStyleRight);
		virtual Boolean			VCOM_CALLTYPE InsertNewDLComponentN(Sint16 beforeIndex, WorldCoord width, Sint32 fill, Uint8 penWeightLeft, Uint8 penWeightRight, InternalIndex penStyleLeft, InternalIndex penStyleRight);
		virtual Boolean			VCOM_CALLTYPE InsertNewComponentN(MCObjectHandle object, short beforeComponentIndex, WorldCoord width, Sint32 fill, Uint8 leftPenWeight, Uint8 rightPenWeight, InternalIndex leftPenStyle, InternalIndex rightPenStyle);
		virtual Boolean			VCOM_CALLTYPE IsDashLineStyle(InternalIndex dashLineType);

		// Line type reengineering new functions for worksheet cell borders. Instead of using dash index for cell border style, these use InternalIndex. 
		virtual void			VCOM_CALLTYPE GetWSCellAllBordersN(MCObjectHandle worksheet, const ViewPt& cell, TCellBorderRefNum& top, TCellBorderRefNum& left, TCellBorderRefNum& bottom, TCellBorderRefNum& right);
		virtual void			VCOM_CALLTYPE SetWSCellAllBordersN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, TCellBorderRefNum top, TCellBorderRefNum left, TCellBorderRefNum bottom, TCellBorderRefNum right, TCellBorderRefNum insideVert, TCellBorderRefNum insideHorz);
		virtual void			VCOM_CALLTYPE SetWSCellBottomBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color);
		virtual void			VCOM_CALLTYPE SetWSCellInsideHorizBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color);
		virtual void			VCOM_CALLTYPE SetWSCellInsideVertBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color);
		virtual void			VCOM_CALLTYPE SetWSCellLeftBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color);
		virtual void			VCOM_CALLTYPE SetWSCellOutlineBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color);
		virtual void			VCOM_CALLTYPE SetWSCellRightBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color);
		virtual void			VCOM_CALLTYPE SetWSCellTopBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color);

		// Line type reengineering new functions for pseudo dash index to ref number conversion
		virtual bool			VCOM_CALLTYPE GetPseudoDashIndexFromDashLineType(const InternalIndex dashLineType, Sint16& pseudoIndex);
		virtual bool			VCOM_CALLTYPE GetDashLineTypeFromPseudoDashIndex(const Sint16 pseudoIndex, InternalIndex& dashLineType);
		virtual void			VCOM_CALLTYPE BeginMultiplePseudoDashIndexConvert();
		virtual void			VCOM_CALLTYPE EndMultiplePseudoDashIndexConvert();

		virtual void			VCOM_CALLTYPE CreateSearchEditBox(Sint32 dialogID, Sint32 itemID, const TXString& promptText, short widthInStdChar);

        virtual MCObjectHandle  VCOM_CALLTYPE CreateSymbolDefinitionForDisplayControl(TXString& inoutName);
        virtual MCObjectHandle  VCOM_CALLTYPE GetObjectByUuidN(const UuidStorage& uuid);
        virtual bool            VCOM_CALLTYPE GetObjectUuidN(MCObjectHandle h, UuidStorage& uuid);

		virtual TXString		VCOM_CALLTYPE GetActiveSymbolName();
		virtual bool			VCOM_CALLTYPE GetFilePathForActiveSymbolInOpenDocument(IFileIdentifier** ppOutFileID, bool& outFolderSet);

		virtual bool			VCOM_CALLTYPE AssignUuidToHandle(MCObjectHandle h, const UuidStorage& uuid, TDocumentUuidsCheckTable& checkTable);

		virtual void			VCOM_CALLTYPE CreateEditPassword(Sint32 dialogID, Sint32 itemID, short widthInStdChar);
		//This lets the user assign text tags to an object
		virtual bool			VCOM_CALLTYPE AddObjectTags(MCObjectHandle h, const TXStringArray& arrTags);
		virtual bool			VCOM_CALLTYPE GetObjectTags(MCObjectHandle h, TXStringArray& arrTags);

		virtual bool			VCOM_CALLTYPE ShowChooseDateFormatDialog(EDateTimeFormat& inOutDateFormat);

		virtual ESetSpecialGroupErrors	VCOM_CALLTYPE Set2DComponentGroup(MCObjectHandle hObject, MCObjectHandle hGroup, EViewTypes component);
		virtual MCObjectHandle	VCOM_CALLTYPE Get2DComponentGroup(MCObjectHandle hObject, EViewTypes component);

		virtual ESetSpecialGroupErrors	VCOM_CALLTYPE AddObjectTo2DComponentGroup(MCObjectHandle hObject, MCObjectHandle hObjectToAdd, EViewTypes component);

		virtual bool			VCOM_CALLTYPE SetTopPlan2DComponent(MCObjectHandle hObject, ETopPlanViewComponent component);
		virtual ETopPlanViewComponent VCOM_CALLTYPE GetTopPlan2DComponent(MCObjectHandle hObject);

		virtual void			VCOM_CALLTYPE SetWorksheetCellImageComponent(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, EImageViewComponent component);
		virtual void			VCOM_CALLTYPE GetWorksheetCellImageComponent(MCObjectHandle worksheet, short row, short column, EImageViewComponent& outComponent);

		virtual bool			VCOM_CALLTYPE SetDisplayWith2DComponent(MCObjectHandle hObject, EViewTypes component, bool isVisible);
		virtual bool			VCOM_CALLTYPE GetDisplayWith2DComponent(MCObjectHandle hObject, EViewTypes component);

		virtual bool			VCOM_CALLTYPE SetMirrorEmpty2DComponents(MCObjectHandle hObject, bool doMirror);
		virtual bool			VCOM_CALLTYPE GetMirrorEmpty2DComponents(MCObjectHandle hObject);

		virtual bool			VCOM_CALLTYPE Generate2DFrom3DComponent(MCObjectHandle hObject, EViewTypes component, TRenderMode renderMode, ELevelsOfDetail levelOfDetails);
        
        virtual MCObjectHandle  VCOM_CALLTYPE CreateTemporaryCustomObject(const TXString& name, const WorldPt& location, double_param angle = 0.0);
        virtual MCObjectHandle  VCOM_CALLTYPE CreateTemporaryCustomObjectByMatrix(const TXString& name, const TransformMatrix& matrix);
        virtual MCObjectHandle  VCOM_CALLTYPE CreateTemporaryCustomObjectByMatrixEx(const TXString& name, const TransformMatrix& matrix);

		virtual void			VCOM_CALLTYPE GetPageMargins(MCObjectHandle hLayer, double& left, double& right, double& bottom, double& top);

		virtual Boolean			VCOM_CALLTYPE CreateLayerPullDownMenu(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar);
        
        //SP2 VW2019
        virtual WorldPt3        VCOM_CALLTYPE Project3DPointOnPlane(const WorldPt3& given3DPoint, const WorldPt3& pointOnPlane, const WorldPt3& planeNormal, const WorldPt3& projectionDir);
	};
}
