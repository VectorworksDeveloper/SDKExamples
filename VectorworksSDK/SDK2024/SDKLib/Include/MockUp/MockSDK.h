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
		MockSDK() {}
		virtual ~MockSDK() {}


	//  pre VW2009
	public:
		virtual Boolean VCOM_CALLTYPE GetClassBeginningMarker(InternalIndex index, SMarkerStyle& mstyle) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetClassEndMarker(InternalIndex index, SMarkerStyle& mstyle) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetClColor(InternalIndex index, ObjectColorType& color) override
		{
			return;
		}
		virtual InternalIndex VCOM_CALLTYPE GetClFillPat(InternalIndex index) override
		{
			return -1;
		}
		virtual short VCOM_CALLTYPE GetClLineWeight(InternalIndex index) override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetClMarker(InternalIndex index, MarkerType& style, short& size, short& angle) override
		{
	
		}

		virtual Boolean VCOM_CALLTYPE GetClUseGraphic(InternalIndex index) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetClVisibility(InternalIndex index) override
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE GetVPClassFillStyle(MCObjectHandle viewport, InternalIndex classIndex) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE SetClassBeginningMarker(InternalIndex index, SMarkerStyle mstyle) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE SetClassEndMarker(InternalIndex index, SMarkerStyle mstyle) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetClColor(InternalIndex index, ObjectColorType color) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetClFillPat(InternalIndex index, InternalIndex fill) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetClLineWeight(InternalIndex index, short mils) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetClMarker(InternalIndex index, MarkerType style, short size, short angle) override
		{
	
		}

		virtual void VCOM_CALLTYPE SetClUseGraphic(InternalIndex index, Boolean use) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetClVisibility(InternalIndex index, short vis) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE VPClassHasOverride(MCObjectHandle viewport, InternalIndex classIndex) override
		{
			return false;	
		}
		virtual Boolean VCOM_CALLTYPE DeleteAllDLComponents() override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteDLComponent(Sint16 index) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultArrowByClass() override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetDefaultArrowHeads(Boolean& starting, Boolean& ending, ArrowType& style, short& size) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetDefaultArrowHeadsN(Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultBeginningMarker(SMarkerStyle& mstyle, Boolean& visibility) override
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetDefaultClass() override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetDefaultColors(ObjectColorType& colors) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultEndMarker(SMarkerStyle& mstyle, Boolean& visibility) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultFColorsByClass() override
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetDefaultFillPat() override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultFPatByClass() override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetDefaultHatch() override
		{
			return NULL;
		}
		virtual short VCOM_CALLTYPE GetDefaultLineWeight() override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultLWByClass() override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultPColorsByClass() override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetDefaultPPatByClass() override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentClass(Sint16 index, Sint32 &componentClass) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentFill(Sint16 index, Sint32 &fill) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentFillColors(Sint16 index, ColorRef &fillForeColor, ColorRef &fillBackColor) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentName(Sint16 index, TXString& outComponentName) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentPenColors(Sint16 index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetDLComponentPenWeights(Sint16 index, Uint8 &penWeightLeft, Uint8 &penWeightRight) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentUseFillClassAttr(Sint16 index, Boolean &useClassAttr) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentUsePenClassAttr(Sint16 index, Boolean &leftPenUseClassAttr, Boolean &rightPenUseClassAttr) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentWidth(Sint16 index, WorldCoord &width) override
		{
			return false;
		}
		virtual WorldCoord VCOM_CALLTYPE GetDLControlOffset() override
		{
			return 0.0;
		}
		virtual Sint16 VCOM_CALLTYPE GetDLOptions() override
		{
			return -1;
		}
		virtual WorldCoord VCOM_CALLTYPE GetDLSeparation() override
		{
			return 0.0;
		}
		virtual InternalIndex VCOM_CALLTYPE GetDocumentDefaultSketchStyle() override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetNumberOfDLComponents(short& numComponents) override
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetObjectInternalIndex(MCObjectHandle h) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetProgramVariable(short variableSelector, void* result) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetWallPrefStyle(InternalIndex& wallStyleNum) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetWallStyle(MCObjectHandle theWall, InternalIndex& wallStyle) override
		{
			return false;
		}

		virtual void VCOM_CALLTYPE SetDefaultArrowByClass() override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultArrowHeads(Boolean starting, Boolean ending, ArrowType style, short size) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultArrowHeadsN(Boolean starting, Boolean ending, ArrowType style, double_param size) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDefaultBeginningMarker(SMarkerStyle mstyle, Boolean visibility) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDefaultClass(InternalIndex classID) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultColors(ObjectColorType colors) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDefaultEndMarker(SMarkerStyle mstyle, Boolean visibility) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDefaultFColorsByClass() override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultFillPat(InternalIndex theFill) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultFPatByClass() override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDefaultHatch(MCObjectHandle inHatchDef) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDefaultLineWeight(short mils) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultLWByClass() override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultPColorsByClass() override
		{
	
		}

		virtual void VCOM_CALLTYPE SetDefaultPPatByClass() override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultWallThickness(WorldCoord thickness) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentClass(Sint16 index, Sint32 componentClass) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentFill(Sint16 index, Sint32 fill) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentFillColors(Sint16 index, ColorRef fillForeColor, ColorRef fillBackColor) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentName(Sint16 index, const TXString& componentName) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentPenColors(Sint16 index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE SetDLComponentPenWeights(Sint16 index, Uint8 penWeightLeft, Uint8 penWeightRight) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentUseFillClassAttr(Sint16 index, Boolean useClassAttr) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentUsePenClassAttr(Sint16 index, Boolean leftPenUseClassAttr, Boolean rightPenUseClassAttr) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentWidth(Sint16 index, WorldCoord width) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDLControlOffset(WorldCoord controlOffset) override
		{

		}
		virtual void VCOM_CALLTYPE SetDLOptions(Sint16 options) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDLSeparation(WorldCoord separation) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDocumentDefaultSketchStyle(InternalIndex sketchIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetProgramVariable(short variableSelector, const void* value) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallPrefStyle(InternalIndex wallStyleNum) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE WrapGetDefaultWallThickness(double_gs& outCoordLen) override
		{
	
		}
		virtual void VCOM_CALLTYPE Add3DVertex(MCObjectHandle h, const WorldPt3& v, Boolean recalcBounds) override
		{
	
		}
		virtual void VCOM_CALLTYPE AddVertex(MCObjectHandle h, const WorldPt& p, VectorWorks::TEditContext editContext, VertexType t, WorldCoord arcRadius, Boolean recalcBounds) override
		{
	
		}
		virtual void VCOM_CALLTYPE CalcAreaN(MCObjectHandle h, double_gs& area) override
		{
	
		}
		virtual void VCOM_CALLTYPE CalcPerimN(MCObjectHandle h, double_gs& perim) override
		{
	
		}
		virtual double_gs VCOM_CALLTYPE CalcSurfaceArea(MCObjectHandle h) override
		// returns squared document LENGTH units. For area units use ObjSurfaceArea
		{
			return 0.0;

		}
		virtual double_gs VCOM_CALLTYPE CalcVolume(MCObjectHandle h) override
		{
			return 0.0;
		}
		virtual Boolean VCOM_CALLTYPE Centroid3D(MCObjectHandle h, double_gs &xCG, double_gs &yCG, double_gs &zCG) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE CountVertices(MCObjectHandle h) override
		{
			return 0;
	
		}
		virtual short VCOM_CALLTYPE CreateSkylight(MCObjectHandle object) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE DeleteVertex(MCObjectHandle h, short vertexNum) override
		{
	
		}
		virtual void VCOM_CALLTYPE ForEach3DPointInObject(MCObjectHandle h, GS_3DPointIteratorProcPtr proc, void* env) override
		{
	
		}
		virtual void VCOM_CALLTYPE ForEachPolyEdge( MCObjectHandle inPolyH, GS_ForEachPolyEdgeProcPtr inProc, void* inEnv) override
		{
	
		}
		virtual void VCOM_CALLTYPE Get3DVertex(MCObjectHandle h, short vertexNum, WorldPt3& vertex) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetArcInfoN(MCObjectHandle h, double_gs& startAngle, double_gs& sweepAngle, WorldPt& center, WorldCoord& radiusX, WorldCoord& radiusY) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetBatAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, WorldCoord& topWidth, WorldCoord& baseHeight, double_gs& topSlope, WorldCoord& controlPoint) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetControlVertex(MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetDormerAttributes(MCObjectHandle object, const short dormerID, short& edgeIndex, WorldCoord& cornerOffset, Boolean& isPerpOffset, WorldCoord& perpOrHeightOffset, InternalIndex& symName, Boolean& centerSymbol, WorldCoord& symOffset) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetEndPoints(MCObjectHandle h, WorldPt& startPt, WorldPt& endPt) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetEntityMatrix(MCObjectHandle h, TransformMatrix& theMat) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetExtrudeValues(MCObjectHandle h, WorldCoord& bottom, WorldCoord& top) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetGableAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, WorldCoord& overhang) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetHipAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& frontSlope, WorldCoord& overhang) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetLocus3DPosition(MCObjectHandle h, WorldPt3& locPos) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetLocusPosition(MCObjectHandle h, WorldPt& locPos) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetMarkerPolys(MCObjectHandle object, MCObjectHandle& startMarkerPoly, MCObjectHandle& endMarkerPoly) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetNumRoofElements(MCObjectHandle object) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectBoundingBoxVerts(MCObjectHandle h, WorldRectVerts &outBoxVerts) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectBounds(MCObjectHandle h, WorldRect& bounds) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetObjectCube(MCObjectHandle h, WorldCube& boundsCube) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetPolyDirection(MCObjectHandle polyToCheck) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetPolyShapeClose(MCObjectHandle h) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetQArcQuadrant(MCObjectHandle h) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetRoofAttributes(MCObjectHandle object, Boolean& genGableWall, WorldCoord& bearingInset, WorldCoord& roofThick, short& miterType, WorldCoord& vertMiter) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetRoofElementType(MCObjectHandle object, const short dormerID, short& edgeIndex, Boolean& isDormer, short& dormerType) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetRRectDiameters(MCObjectHandle h, WorldCoord& xDiam, WorldCoord& yDiam) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetShedAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& topSlope, WorldCoord& overhang) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetSkylight(MCObjectHandle object, const short skylightID, short& edgeIndex, WorldCoord& cornerOffset, WorldCoord& perpOffset, InternalIndex& symName) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetSweepAnglesN(MCObjectHandle theSweep, double_gs& startAngle, double_gs& arcAngle, double_gs& incrAngle) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetTrapeziumAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, Boolean& useTopWidth, WorldCoord& topWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& topSlope) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetVertex(MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius) override
		{
		}
		virtual void VCOM_CALLTYPE Insert3DVertex(MCObjectHandle h, const WorldPt3& p, short beforeVertex, Boolean recalcBounds) override
		{
		}
		virtual void VCOM_CALLTYPE InsertVertex(MCObjectHandle h, const WorldPt& p, short beforeVertex, VertexType t, WorldCoord arcRadius, Boolean recalcBounds) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE Moments3D(MCObjectHandle h, double_gs &Ixx, double_gs &Iyy, double_gs &Izz) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsCurveEvaluatePoint(MCObjectHandle nurbsHandle, Sint32 index, double u, WorldPt3& pt) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE NurbsCurveGetNumPieces(MCObjectHandle nHandle) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE NurbsCurveType(MCObjectHandle nHandle, Sint32 index, bool& isByWeight) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE NurbsDegree(MCObjectHandle nHandle, Sint32 index) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE NurbsDelVertex(MCObjectHandle nHandle, Sint32 index1, Sint32 index2) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE NurbsGetNumPts(MCObjectHandle nHandle, Sint32 index) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE NurbsGetPt3D(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3& pt) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsGetWeight(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& weight) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsKnot(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& knot) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE NurbsNumKnots(MCObjectHandle nHandle, Sint32 index) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE NurbsSetKnot(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double knot) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsSetPt3D(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3 pt) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsSetWeight(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double weight) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsSurfaceEvaluatePoint(MCObjectHandle nurbsHandle, double u, double v, WorldPt3& pt) override
		{
			return false;
		}
		virtual double_gs VCOM_CALLTYPE ObjArea(MCObjectHandle h) override
		{
			return 0.0;
		}
		virtual double_gs VCOM_CALLTYPE ObjSurfaceArea(MCObjectHandle h) override 	// return document area units
		{
			return 0.0;
		}
		virtual double_gs VCOM_CALLTYPE ObjVolume(MCObjectHandle h) override
		{
			return 0.0;
		}
		virtual Boolean VCOM_CALLTYPE Products3D(MCObjectHandle h, double_gs &Ixy, double_gs &Iyz, double_gs &Izx) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RemoveRoofElement(MCObjectHandle object, short id) override
		{
	
		}
		virtual void VCOM_CALLTYPE Set3DVertex(MCObjectHandle h, short vertexNum, const WorldPt3& vertex, Boolean recalcBounds) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetArcAnglesN(MCObjectHandle h, double_param startAngle, double_param sweepAngle) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetBatAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, WorldCoord topWidth, WorldCoord baseHeight, double_param topSlope, WorldCoord controlPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDormerAttributes(MCObjectHandle object, const short dormerID, short edgeIndex, WorldCoord cornerOffset, Boolean isPerpOffset, WorldCoord perpOrHeightOffset, InternalIndex symName, Boolean centerSymbol, WorldCoord symOffset) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDormerThick(MCObjectHandle object, WorldCoord wallThick, WorldCoord roofThick) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetEndPoints(MCObjectHandle h, const WorldPt& startPt, const WorldPt& endPt) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetEntityMatrix(MCObjectHandle h, const TransformMatrix& theMat) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetExtrudeValues(MCObjectHandle h, WorldCoord bottom, WorldCoord top) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetGableAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, WorldCoord overhang) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetHipAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, double_param frontSlope, WorldCoord overhang) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetLocus3DPosition(MCObjectHandle h, const WorldPt3& locPos) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetLocusPosition(MCObjectHandle h, const WorldPt& locPos) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetObjectBounds(MCObjectHandle h, const WorldRect& bounds) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetPolyShapeClose(MCObjectHandle h, Boolean closed) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetQArcQuadrant(MCObjectHandle h, short quadrant) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetRoofAccessoriesParameters(MCObjectHandle roof, Boolean insertAttic, Boolean insertSoffit, Boolean insertFascia, WorldCoord fasciaWidth, WorldCoord fasciaHeight, WorldCoord atticHeight, WorldCoord recess, WorldCoord rakeThick, WorldCoord trimDepth) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetRoofAttributes(MCObjectHandle object, Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetRRectDiameters(MCObjectHandle h, WorldCoord xDiam, WorldCoord yDiam) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetShedAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param topSlope, WorldCoord overhang) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetSkylight(MCObjectHandle object, const short skylightID, short edgeIndex, WorldCoord cornerOffset, WorldCoord perpOffset, InternalIndex symName) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetSweepAnglesN(MCObjectHandle theSweep, double_param startAngle, double_param arcAngle, double_param incrAngle) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetSweepScrew(MCObjectHandle theSweep, WorldCoord dist) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetTrapeziumAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, Boolean useTopWidth, WorldCoord topWidth, double_param leftSlope, double_param rightSlope, double_param topSlope) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetVertex(MCObjectHandle h, short vertexNum, const WorldPt& vertex, VertexType vType, WorldCoord arcRadius, VectorWorks::TEditContext editContext, Boolean recalcBounds) override
		{
	
		}
		virtual void VCOM_CALLTYPE WrapGetSweepScrew(MCObjectHandle theSweep, double_gs& outCoordLen) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCircularDimension(const WorldPt& center, const WorldPt& end, WorldCoord startOffset, WorldCoord textOffset, const WorldRect& box, Boolean isRadius) override
		{
			return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetArrowByClass(MCObjectHandle h) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetArrowHeads(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, short& size) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetArrowHeadsN(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetColor(MCObjectHandle h, ObjectColorType& colors) override
		{
			return false;
		}
		virtual OpacityRef VCOM_CALLTYPE GetDefaultOpacity() override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultOpacityByClass() override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFColorsByClass(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFillIAxisEndPoint(MCObjectHandle objectHandle, WorldPt& iAxisEndPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFillJAxisEndPoint(MCObjectHandle objectHandle, WorldPt& jAxisEndPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFillOriginPoint(MCObjectHandle objectHandle, WorldPt& originPoint) override
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetFillPat(MCObjectHandle h) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetFillPoints(MCObjectHandle objectHandle, WorldPt& originPoint, WorldPt& iAxisEndPoint, WorldPt& jAxisEndPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFPatByClass(MCObjectHandle h) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetLineWeight(MCObjectHandle h) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetLineWeightDisplayMM(short mils) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetLineWeightDisplayPt(short mils) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetLWByClass(MCObjectHandle h) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetMarker(MCObjectHandle obj, MarkerType& style, short& size, short& angle, Boolean& start, Boolean& end) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetObjBeginningMarker(MCObjectHandle h, SMarkerStyle& mstyle, Boolean& visibility) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjEndMarker(MCObjectHandle h, SMarkerStyle& mstyle, Boolean& visibility) override
		{
			return false;
		}
		virtual OpacityRef VCOM_CALLTYPE GetOpacity(MCObjectHandle h) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetOpacityByClass(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetPColorsByClass(MCObjectHandle h) override
		{
			return false;

		}

		virtual Boolean VCOM_CALLTYPE GetPPatByClass(MCObjectHandle h) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetVertexVis(MCObjectHandle h, short vertNum, Boolean& vis) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetArrowByClass(MCObjectHandle h) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetArrowHeads(MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, short size) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetArrowHeadsN(MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, double_param size) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetColor(MCObjectHandle h, ObjectColorType colors) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultOpacity(OpacityRef inOpacity) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultOpacityByClass() override
		{
	
		}
		virtual void VCOM_CALLTYPE SetFColorsByClass(MCObjectHandle h) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetFillIAxisEndPoint(MCObjectHandle objectHandle, const WorldPt& iAxisEndPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetFillJAxisEndPoint(MCObjectHandle objectHandle, const WorldPt& jAxisEndPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetFillOriginPoint(MCObjectHandle objectHandle, const WorldPt& originPoint) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetFillPat(MCObjectHandle h, InternalIndex theFill) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetFPatByClass(MCObjectHandle h) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetLineWeight(MCObjectHandle h, short mils) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetLineWeightDisplayMM(short hundredths) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetLineWeightDisplayPt(short sixteenths) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetLWByClass(MCObjectHandle h) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetObjBeginningMarker(MCObjectHandle h, SMarkerStyle mstyle, Boolean visibility) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE SetObjEndMarker(MCObjectHandle h, SMarkerStyle mstyle, Boolean visibility) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetOpacity(MCObjectHandle h, OpacityRef  inNewOpacity) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetOpacityByClass(MCObjectHandle h) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetPColorsByClass(MCObjectHandle h) override
		{
	
		}

		virtual void VCOM_CALLTYPE SetPPatByClass(MCObjectHandle h) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetVertexVis(MCObjectHandle h, short vertNum, Boolean vis) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateFillSpace(MCObjectHandle owner) override
		{
			return NULL;
		}
		virtual short VCOM_CALLTYPE CountFillSpaces(MCObjectHandle h) override
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetFillSpace(MCObjectHandle h, short index) override
		{
			return NULL;
		}		
		virtual MCObjectHandle VCOM_CALLTYPE GetDefinition(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE GetDXFColorToLineWeight(const short inDXFColorIndex) override
		{
			return -1;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetNamedObject(const TXString& objName) override
		{
				return NULL;
		}
		virtual InternalIndex VCOM_CALLTYPE GetObjectClass(MCObjectHandle h) override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetObjectName(MCObjectHandle h, TXString& outName) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetObjectType(MCObjectConstHandle h) const override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetSymbolDefinitionIcon(MCObjectHandle theSymDef, Sint32 icon[32] ) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetSymbolDefinitionType(MCObjectHandle theSymDef) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE IsLocked(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsSelected(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsVisible(MCObjectHandle h) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE LockObject(MCObjectHandle h, Boolean lock) override
		{
	
		}
		virtual void VCOM_CALLTYPE SelectObject(MCObjectHandle h, Boolean select) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDXFColorToLineWeight(const short inDXFColorIndex, const short inLineWeight) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetObjectClass(MCObjectHandle h, InternalIndex classID) override
		{
	
		}
		virtual GSError VCOM_CALLTYPE SetObjectName(MCObjectHandle h, const TXString& name) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SetSymbolDefinitionIcon(MCObjectHandle theSymDef, const Sint32 icon[32] ) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetVisibility(MCObjectHandle h, Boolean visible) override
		{
	
		}
		virtual void VCOM_CALLTYPE AttachAuxObject(MCObjectHandle h, MCObjectHandle newOwner) override
		{
	
		}
		virtual void VCOM_CALLTYPE DeleteAuxObject(MCObjectHandle h, MCObjectHandle owner) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE FindAuxObject(MCObjectHandle owner, short objectType) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE FindDataObject(MCObjectConstHandle owner, OSType tag) const override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE FirstAuxObject(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual OSType VCOM_CALLTYPE GetDataTag(MCObjectHandle h) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetPluginType(const TXString& name, EVSPluginType& type) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsPluginFormat(MCObjectHandle h) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE NewDataObject(MCObjectHandle attachTo, OSType tag, size_t objectSize) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE NextAuxObject(MCObjectHandle start, short objectType) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE NextDataObject(MCObjectHandle start, OSType tag) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE RemoveAuxObject(MCObjectHandle h, MCObjectHandle owner) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataCreate(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,int numDataElements) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataGet(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,int dataIndex, void* getData) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataGetNumElements(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,Sint32* getData) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataRemoveContainer(MCObjectHandle inOwnerObj,OSType dataContainer) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataRemoveTag(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataSet(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,int dataIndex, const void* data) override
		{
			return false;
		}
		virtual double_gs VCOM_CALLTYPE CoordLengthToPageLengthN(WorldCoord len) override
		{
			return 0.0;
		}
		virtual double_gs VCOM_CALLTYPE CoordLengthToPagePoints(WorldCoord len) override
		{
			return 0.0;
		}
		virtual Boolean VCOM_CALLTYPE CoordLengthToPixelLength(WorldCoord numCoords, short& numPixels) override
		{
			return false;
		}
		virtual double_gs VCOM_CALLTYPE CoordLengthToUnitsLengthN(WorldCoord len) override
		{
			return 0.0;
		}
		virtual double	VCOM_CALLTYPE CoordLenToPageLenScale(WorldCoord coordLength, double paperScale, double photographicScale) override
		{
			return 0.0;
		}
		virtual double	VCOM_CALLTYPE CoordLenToPagePtsScale(WorldCoord coordLength, double paperScale, double photographicScale) override
		{
			return 0.0;
		}
		virtual double	VCOM_CALLTYPE PageLenToCoordLenScale(double pageLength, double paperScale, double photographicScale) override
		{
			return 0.0;
		}
		virtual double	VCOM_CALLTYPE PagePtsToCoordLenScale(double pagePoints, double paperScale, double photographicScale) override
		{
			return 0.0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateOvalN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE DimStringToCoord(const TXString& s, WorldCoord& c) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE FPCoordLengthToPageLength(double_param coordLen, double_gs& pageLen) override
		{
	
		}
		virtual void VCOM_CALLTYPE FPCoordLengthToUnitsLength(double_param coordLen, double_gs& unitsLen) override
		{
	
		}
		virtual void VCOM_CALLTYPE ModelPt2DToScreenPt(WorldPt& vertex) override
		{
	
		}
		virtual void VCOM_CALLTYPE ModelVecToScreenVec(WorldPt& vertex) override
		{
	
		}
		virtual void VCOM_CALLTYPE PageLengthToFPCoordLength(double_param pageLen, double_gs& coordLen) override
		{
	
		}
		virtual WorldCoord VCOM_CALLTYPE PagePointsToCoordLength(double_gs& points) override
		{
			return 0.0;
		}
		virtual void VCOM_CALLTYPE PixelLengthToCoordLength(short numPixels, WorldCoord& numCoords) override
		{
	
		}
		virtual void VCOM_CALLTYPE ScreenPtToModelPt2D(WorldPt& vertex) override
		{
	
		}
		virtual void VCOM_CALLTYPE ScreenVecToModelVec(WorldPt& vertex) override
		{
	
		}
		virtual void VCOM_CALLTYPE UnitsLengthToFPCoordLength(double_param unitsLen, double_gs& coordLen) override
		{
	
		}
		virtual WorldCoord VCOM_CALLTYPE WorldCoordsPerDrawingUnit() override
		{
			return 0.0;
		}
		virtual void VCOM_CALLTYPE WrapPageLengthToCoordLengthN(double_param len, double_gs& outCoordLen) override
		{
	
		}
		virtual void VCOM_CALLTYPE WrapUnitsLengthToCoordLengthN(double_param len, double_gs& outCoordLen) override
		{
	
		}
		virtual short VCOM_CALLTYPE AddSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE AppendRoofEdge(MCObjectHandle object, const WorldPt& edgePt, double_param slope, WorldCoord projection, WorldCoord eaveHeight) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE Create3DPoly() override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateAngleDimension(const WorldPt& center, const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateArcN(const WorldRect& bounds, double_param startAngle, double_param sweepAngle) override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateBatDormer(MCObjectHandle object) override
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateChainDimension(MCObjectHandle h1, MCObjectHandle h2) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCombineIntoSurface(const WorldPt& inPoint) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCone(const WorldPt3& center, const WorldPt3 &tip, WorldCoord radius) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateContourCurves(MCObjectHandle h, double_param delta, WorldPt3 pointOnPlane, WorldPt3 planeNormal) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomDimensionStandard(const TXString& name) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObject(const TXString& name, const WorldPt& location, double_param angle, bool bInsert) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectByMatrix(const TXString& name, const TransformMatrix& matrix) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectDoubleClick(const TXString& name) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectPath(const TXString& name, MCObjectHandle pathHand, MCObjectHandle profileGroupHand) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateExtrude(WorldCoord bottom, WorldCoord top) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateExtrudeAlongPath(MCObjectHandle pathHandle, MCObjectHandle profileHandle) override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateGableDormer(MCObjectHandle object) override
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateGroup(bool isTemporary /* = false */) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateHemisphere(const WorldPt3& center, const WorldPt3 &topPoint) override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateHipDormer(MCObjectHandle object) override
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateImageProp(TXString& propName, InternalIndex textureRef, WorldCoord height, WorldCoord width, Boolean enforceImageAspectRatio, Boolean crossedPlanes, Boolean createPlugin, Boolean autoRotate, Boolean createSymbol) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateInterpolatedSurface(MCObjectHandle surfaceHandle, Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLayer(const TXString& layerName, short layerType) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLayerN(const TXString& name, double_param scale) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLightN(const WorldPt3& pos, short kind, Boolean isOn, double_param brightness, const WorldPt3& color, Boolean castShadows) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLine(const WorldPt& startPt, const WorldPt& endPt) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLinearDimension(const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset, WorldCoord textOffset, const Vector2& dir, short dimType) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLocus(const WorldPt& location, bool isTemporary = false) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLocus3D(const WorldPt3& location) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLoftSurfaces(MCObjectHandle groupCurvesH, Boolean bRule, Boolean  bClose, Boolean bSolid) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateNurbsCurve(WorldPt3 firstPt, bool byCtrlPts, short degree) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateNurbsSurface(Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateOval(const WorldRect& bounds) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreatePolyshape() override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateQArc(const WorldRect& bounds, short quadrant) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRectangle(const WorldRect& bounds) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRectangleN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRoof(Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRoundWall(const WorldPt& startPt, const WorldPt& ptOnArc, const WorldPt& endPt, WorldCoord wallThickness) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRRectangle(const WorldRect& bounds, WorldCoord xDiam, WorldCoord yDiam) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRRectangleN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height, CBWorldCoord_param xDiam, CBWorldCoord_param yDiam, Boolean isProportional) override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateShedDormer(MCObjectHandle object) override
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateBasicSlab(short slabKind) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateSphere(const WorldPt3& center, WorldCoord radius) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateStaticHatch(const TXString& name, const WorldPt& inOriginPoint, double_param inRotationAngle) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateStaticHatchFromObject(MCObjectHandle inObj, const TXString& name, const WorldPt& inOriginPoint, double_param inRotationAngle) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE CreateSurfacefromCurvesNetwork() override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateSweepN(double_param startAngle, double_param arcAngle, double_param incrAngle, WorldCoord screwDist) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateSymbolDefinition(TXString& inoutName) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateSymbolFolder(const TXString& name) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTaperedExtrude(MCObjectHandle profileH, const double_param angle, const double_param height) override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateTrapeziumDormer(MCObjectHandle object) override
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateViewport(MCObjectHandle parentHandle) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateWall(const WorldPt& startPt, const WorldPt& endPt, WorldCoord thickness) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE DefineCustomObject(const TXString& name, Byte prefWhen) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DuplicateSelection(WorldCoord dx, WorldCoord dy) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE ExtendNurbsCurve(MCObjectHandle curveHandle, double_param distance, Boolean bStart, Boolean bLinear) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ExtendNurbsSurface(MCObjectHandle surfaceHandle, double_param distance, Boolean bStart, Boolean bLinear, Boolean bUDir) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GenerateBezierApproximationFromPolygon(MCObjectHandle hPolygonHandle, const WorldCoord approximationTolerance, const double discontinuityAngleTolerance, const unsigned short quadraticsPerCubic) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GroupSelection() override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE IntersectSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid) override
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE PlaceSymbolByNameN(const TXString& symName, const WorldPt& location, double_param rotation) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE PlaceSymbolN(MCObjectHandle definition, const WorldPt& location, double_param rotation) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE RevolveWithRail(MCObjectHandle profileH, MCObjectHandle railH, MCObjectHandle axisH) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE Split2DObjectByLine(MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, MCObjectHandle& listHandles) override
		{
	
		}
		virtual short VCOM_CALLTYPE SubtractSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE AddChoice(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short nItemIndex) override
		{
	
		}
		virtual void VCOM_CALLTYPE AddListBoxTabStop(Sint32 dialogID, Sint32 componentID, int tabStop) override
		{
	
		}

		virtual Boolean VCOM_CALLTYPE AdjustComponentPixelPos(Sint32 nDialogID, Sint32 nComponentID, int nHorizontalPixels, int nVerticalPixels) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE AlertCritical(const TXString& text, const TXString& advice) override
		{
	
		}
		virtual void VCOM_CALLTYPE AlertInform(const TXString& text, const TXString& advice, bool minorAlert, const TXString& category, const TXString& item, const TXString& checkboxOverrideText) override
		{
	
		}
		virtual short VCOM_CALLTYPE AlertQuestion(const TXString& question, const TXString& advice, short defaultButton, const TXString& OKOverrideText, const TXString& CancelOverrideText, const TXString& customButtonAText, const TXString& customButtonBText, const TXString& category, const TXString& item, const TXString& checkboxOverrideText) override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE AlignBottomEdge(Sint32 dialogID, Sint32 srcItemID, short bottomID, short alignMode) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AlignLeftEdge(Sint32 dialogID, Sint32 srcItemID, short leftID, short alignMode) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AlignRightEdge(Sint32 dialogID, Sint32 srcItemID, short rightID, short alignMode) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AreListBrowserColumnLinesEnabled(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AreListBrowserRadioColumnLinesEnabled(Sint32 dialogID, Sint32 componentID, short columnIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ClearGradientSliderSegments(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE Confirm(const TXString & strNode, Boolean yesOrNo) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateCenteredStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateCheckBox(Sint32 dialogID, Sint32 itemID, const TXString& name) override
		{
	
		}
        virtual void VCOM_CALLTYPE CreateCheckBoxWithIcon(Sint32 dialogID, Sint32 itemID, const TXString& name, const TXString& iconRecPath) override
        {
            
        }
		virtual void VCOM_CALLTYPE CreateCheckBoxGroupBox(Sint32 dialogID, short itemID, const TXString& name, bool hasFrame) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateClassPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateCMYKColorSwatch(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateColorPopup(Sint32 dialogID, Sint32 itemID, short widthInStdChar) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateControl(Sint32 dialogID, Sint32 itemID, Sint32 controlKind, const TXString& name, SintptrT data) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateCustomControl(Sint32 dlogID, Sint32 controlID, short widthInPixels, short heightInPixels) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateDesignLayerPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateEditInteger(Sint32 dialogID, Sint32 itemID, Sint32 defaultValue, short widthInStdChar) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateEditReal(Sint32 dialogID, Sint32 itemID, Sint32 editRealType, double value, short widthInStdChar) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateEditText(Sint32 dialogID, Sint32 itemID, const TXString& defaultText, short widthInStdChar, short heightInLines) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateEnhancedPullDownMenu(Sint32 liDialogID, Sint32 liComponentID, int widthInStdChar, Boolean bShowIconInMainWindow) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateGroupBox(Sint32 dialogID, Sint32 itemID, const TXString& name, Boolean hasFrame) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateIconPushButton(Sint32 nDialogID, Sint32 nComponentID, int nIconID, int widthInStdChar) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CreateImageControl(Sint32 liDialogID, Sint32 liComponentID, int iWidthPixels, int iHeightPixels, MCObjectHandle hImage) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE CreateLayout(const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName) override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE CreateLineAttributePopup(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateLineStylePopup(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateLineWeightPopup(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateListBox(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateListBoxN(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines, Boolean isMultiSel) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateListBrowser(Sint32 dialogID, Sint32 componentID, Sint16 widthInStdChar, Sint16 heightInLines) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateMarkerPopup(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreatePatternPopup(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreatePullDownMenu(Sint32 dialogID, Sint32 itemID, short widthInStdChar) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreatePullDownMenuGroupBox(Sint32 liDialogID, Sint32 liComponentID, int widthInStdChar, const TXString& strLabel, Boolean bHasFrame) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreatePushButton(Sint32 dialogID, Sint32 itemID, const TXString& buttonName) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateRadioButton(Sint32 dialogID, Sint32 itemID, const TXString& buttonName) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateRadioButtonWithIcon(Sint32 dialogID, Sint32 itemID, const TXString& buttonName, const TXString& iconResPath) override
		{
			
		}
		virtual void VCOM_CALLTYPE CreateRadioButtonGroupBox(Sint32 dialogID, short itemID, const TXString& name, bool hasFrame) override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE CreateResizableLayout(const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName, Boolean widthResizable, Boolean heightResizable) override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE CreateRightStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateSeparator(Sint32 liDialogID, Sint32 liComponentID, int widthInPixels) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CreateSheetLayerPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateStandardIconControl(Sint32 dialogID, Sint32 iconControlID, int iconNumber) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateSwapControl(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateSwapPane(Sint32 dialogID, Sint32 swapControlID, Sint32 newGroupID) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateSymbolDisplayControl(Sint32 dialogIDIn, Sint32 itemIDIn, const TXString& symbolRefIn, SymbolImgInfo& imgInfoInOut) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateTabControl(Sint32 dialogID, short itemID) override
		{
	
		}
		virtual void VCOM_CALLTYPE CreateTabPane(Sint32 dialogID, short itemID, short groupID) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateThreeStateCheckBox(Sint32 liDialogID, Sint32 liComponentID, const TXString& strName) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CreateTreeControl(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar, int heightInLines) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeleteAllItems(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE DeleteAllListBrowserItems(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteListBrowserColumn(Sint32 dialogID, Sint32 componentID, short columnIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteListBrowserItem(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeselectEditText(Sint32 dialogID, Sint32 controlID) override
		{
	
		}
		virtual void VCOM_CALLTYPE DisplaySwapPane(Sint32 dialogID, Sint32 swapControlID, Sint32 groupNumber) override
		{
	
		}
		virtual void VCOM_CALLTYPE DisplayTabPane(Sint32 dialogID, Sint32 controlID, Sint32 groupNumber) override
		{
	
		}
		virtual void VCOM_CALLTYPE EnableItem(Sint32 dialogID, Sint32 itemID, Boolean bEnable) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowser(Sint32 dialogID, Sint32 componentID, Boolean enable) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserClickAllDataChange(Sint32 dialogID, Sint32 componentID, Boolean enable) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE EnableListBrowserColumnLines(Sint32 dialogID, Sint32 componentID, Boolean enableColumnLines) override
		{
	
		}
		virtual void VCOM_CALLTYPE EnableListBrowserColumnTracking(Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableColumnTracking) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserDragAndDrop(Sint32 dialogID, Sint32 componentID, Boolean bEnable) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserDropOnIndices(Sint32 liDialogID, Sint32 liComponentID, int iStartIndex, int iEndIndex, Boolean bEnable) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE EnableListBrowserRadioColumnLines(Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableRadioColumnLines) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserSingleLineSelection(Sint32 dialogID, Sint32 componentID, Boolean enable) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE EnableListBrowserSorting(Sint32 dialogID, Sint32 componentID, Boolean enableSorting) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserUpdates(Sint32 liDialogID, Sint32 liComponentID, Boolean bEnableUpdates) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE EnsureListBrowserItemIsVisible(Sint32 dialogID, Sint32 componentID, int iIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ExpandTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID, Boolean bExpand) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE FindListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& columnDataItemIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE FindListBrowserColumnItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& itemIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE FormatTextDialog(FormatTextType& formatTextRec) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE GetActiveEditItem(Sint32 dialogID) override
		{
			return -1;
		}
		virtual Sint32 VCOM_CALLTYPE GetActivePane(Sint32 dialogID, Sint32 controlID) override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetBooleanItem(Sint32 dialogID, Sint32 itemID, Boolean& state) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetChoiceCount(Sint32 dialogID, Sint32 itemID, short& numItems) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetChoiceIndex(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short& nItemIndex) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetChoiceText(Sint32 dialogID, Sint32 itemID, short nItemIndex, TXString& outItemText) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetCMYKColor(Sint32 dialogID, Sint32 itemID, TGSColorV2 &outColor) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetColorButton(Sint32 dialogID, Sint32 itemID, RGBColor& rgb) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetColorChoice(Sint32 dialogID, Sint32 itemID, short& colorIndex) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetComponentRect(Sint32 nDialogID, Sint32 nComponentID, int& nLeft, int& nTop, int& nRight, int& nBottom, ELayoutCoordinateSpace cooredinateSpace) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentTextWidth(Sint32 nDialogID, Sint32 nComponentID, int& nWidthInLMUnits) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetControlData(Sint32 dialogID, Sint32 itemID, SControlDataBase& data) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetCustomControlScrollArea(Sint32 dialogID, Sint32 component, int *leftStart, int *topStart) override
		{
	
		}
		virtual bool VCOM_CALLTYPE GetEditInteger(Sint32 dialogID, Sint32 componentID, Sint32& value) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetEditReal(Sint32 dialogID, Sint32 componentID, short editRealType, double& value) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetGradientSliderData(Sint32 dialogID, Sint32 componentID, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetGradientSliderSelectedMarker(Sint32 dialogID, Sint32 componentID, short& segmentIndex, short& markerType) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetIconPushButtonState(Sint32 nDialogID, Sint32 nComponentID, Boolean& bPressed) override
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetImagePopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return -1;
		}
		virtual short VCOM_CALLTYPE GetImagePopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetImagePopupSelectedItem(Sint32 dialogID, Sint32 componentID) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetItemText(Sint32 dialogID, Sint32 itemID, TXString& outCurrentText) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetLayoutDialogPosition(Sint32 dialogID, short& left, short& top, short& right, short& bottom) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetLayoutDialogSize(Sint32 dialogID, short& width, short& height) override
		{
	
		}

		virtual void VCOM_CALLTYPE GetLineWeightChoice(Sint32 dialogID, Sint32 itemID, short& lineWeight) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnWidth(Sint32 dialogID, Sint32 componentID, short columnIndex, short& width) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnDataItemInfo(Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex, TXString& itemString, short &imageOn, short &imageOff, Sint32 &itemData) override
		{
			return false;
		}
		virtual int VCOM_CALLTYPE GetListBrowserColumnSortState(Sint32 dialogID, Sint32 componentID, int columnIndex) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnOwnerDrawnType(Sint32 dialogID, Sint32 componentID, int iIndex, int iSubIndex, int &iOwnerDrawnType) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnHeaderToolTip(Sint32 dialogID, Sint32 componentID, int iColumnIndex, TXString& strToolTipPrimaryText, TXString& strToolTipSubText) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnHeaderJust(Sint32 dialogID, Sint32 componentID, int iColumnIndex, int &iJustification) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetListBrowserControlType(Sint32 dialogID, Sint32 componentID, short columnIndex) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetListBrowserEditDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserEventInfo(Sint32 dialogID, Sint32 componentID, int& iEventType, int& iRowIndex, int& iColumnIndex) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetListBrowserItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemIndex, int nSubItemIndex, Sint32& nUserData) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetListBrowserItemDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE HasListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool& hasColor) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE HasListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool& hasColor) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemGradientOrImageRefNumber(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 &liRefNumber) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString& itemString, short& imageIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE HasListBrowserItemPenForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool& hasColor) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPenForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE HasListBrowserItemPenBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool& hasColor) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPenBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextJust(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int &justification) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextStyle(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, unsigned char &textStyle) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE HasListBrowserItemTextColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool& hasColor) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextColor(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int &redIndex, int &greenIndex, int &blueIndex) override
		{
			return false;
		}


		virtual int VCOM_CALLTYPE GetListBrowserSortColumn(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetMarkerChoice(Sint32 dialogID, Sint32 itemID, MarkerType& style, Sint8& angle, double& size, double& width, Uint8& thicknessBasis, double& thickness) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetMarkerPopupSelectedItem(Sint32 dialogID, Sint32 componentID, char& style, char& angle, short& size) override
		{
			return 0;
		}
		virtual GSHandle VCOM_CALLTYPE GetMultilineText(Sint32 dialogID, Sint32 itemID) override
		{
			return NULL;
		}
		virtual short VCOM_CALLTYPE GetNumGradientSliderSegments(Sint32 dialogID, Sint32 componentID) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumImagePopupItems(Sint32 dialogID, Sint32 componentID) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumListBrowserColumns(Sint32 dialogID, Sint32 componentID) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumListBrowserColumnDataItems(Sint32 dialogID, Sint32 componentID, short columnIndex) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumListBrowserItems(Sint32 dialogID, Sint32 componentID) override
		{
			return 0;
		}
		virtual int VCOM_CALLTYPE GetNumSelectedListBrowserItems(Sint32 dialogID, Sint32 componentID) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetPatternData(Sint32 dialogID, Sint32 itemID, short& patternIndex, short& foreColor, short& backColor) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetSelChoiceIndex(Sint32 dialogID, Sint32 itemID, short inStartIndex, short& outSelectedIndex) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetSelectedChoiceIndex(Sint32 dialogID, Sint32 itemID, short& nItemIndex) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetSelectionRange(Sint32 dialogID, Sint32 controlID, int& startPos, int& endPos) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetThreeStateCheckBoxState(Sint32 liDialogID, Sint32 liComponentID, int& iState) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlItemData(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, SintptrT& nItemData) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlSelectedItem(Sint32 nDialogID, Sint32 nComponentID, int& nItemID) override
		{
			return false;
		}

		virtual short VCOM_CALLTYPE InsertGradientSliderSegment(Sint32 dialogID, Sint32 componentID, double_param spotPosition, const WorldPt3& color) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE InsertImagePopupObjectItem(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex) override
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE InsertImagePopupResource(Sint32 dialogID, Sint32 componentID, Sint32 listID, Sint32 index) override
		{
			return 0;
		}
		virtual int VCOM_CALLTYPE InsertImagePopupSeparator(Sint32 liDialogID, Sint32 liComponentID, const TXString& strLabel) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE InsertListBrowserColumn(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& headerString, short width) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE InsertListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short imageOn, short imageOff, Sint32 itemData) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE InsertListBrowserItem(Sint32 dialogID, Sint32 componentID, short itemIndex, const TXString& itemString) override
		{
			return 0;
		}

		virtual int VCOM_CALLTYPE InsertTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, const TXString& strItemLabel, int nParentID, int nAfterID) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE IsItemEnabled(Sint32 nDialogID, Sint32 nComponentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsItemVisible(Sint32 nDialogID, Sint32 nComponentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserColumnTrackingEnabled(Sint32 dialogID, Sint32 componentID, short columnIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserItemSelected(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemInteractionType(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, EListBrowserItemInteractionType& interactionType) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemInteractionType(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, EListBrowserItemInteractionType interactionType) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserSortingEnabled(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemCheckState(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, int& iState) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemCheckState(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const int iState) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE EnableListBrowserItem3StateCheckBox(Sint32 /*dialogID*/, Sint32 /*componentID*/, short /*itemIndex*/, short /*subItemIndex*/, bool /*bEnable*/ /*= true*/) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE IsListBrowserItem3StateCheckBoxEnabled(Sint32 /*dialogID*/, Sint32 /*componentID*/, short /*itemIndex*/, short /*subItemIndex*/) override
		{
			return false;
		}

		virtual void VCOM_CALLTYPE SetListBrowserReadOnly(Sint32 dialogID, Sint32 componentID, bool bReadOnly) override
		{
    
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserReadOnly(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetListBrowserItemReadOnly(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex, bool bReadOnly) override
		{
    
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserItemReadOnly(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetListBrowserItemResourceOnlyCurrentDocument(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex, bool bCurrentDocOnly) override
		{

		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserItemResourceOnlyCurrentDocument(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NotifyPullDownClicked(Sint32 nDialogID, Sint32 nComponentID) override
		{
			return false;
		}
		virtual TOSWndPtr VCOM_CALLTYPE OverrideControl(Sint32 dlogID, Sint32 controlID, void* pCallbackOSFunction) override
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE PostMinorNoteAlert(const TXString& msgStr) override
		{
	
		}
		virtual void VCOM_CALLTYPE PostMinorStopAlert(const TXString& msgStr) override
		{
	
		}
		virtual void VCOM_CALLTYPE PostNoteAlert(const TXString& msgStr) override
		{
	
		}
		virtual void VCOM_CALLTYPE PostStopAlert(const TXString& msgStr) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE RefreshItem(Sint32 liDialogID, Sint32 liComponentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RefreshListBrowser(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveAllImagePopupItems(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RemoveAllListBrowserColumnDataItems(Sint32 dialogID, Sint32 componentID, short columnIndex) override
		{
	
		}
		virtual void VCOM_CALLTYPE RemoveChoice(Sint32 dialogID, Sint32 itemID, short itemIndexToRemove) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE RemoveEnhancedPullDownMenuItemRange(Sint32 liDialogID, Sint32 liComponentID, int iStartItemIndexToRemove, int iEndItemIndexToRemove) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveGradientSliderSegment(Sint32 dialogID, Sint32 componentID, short segmentIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveImagePopupItem(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RemoveListBoxTabStop(Sint32 dialogID, Sint32 componentID) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE RemoveListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE RunLayoutDialog(Sint32 dialogID, GS_EventHandlerProcPtr handleEvent, void* env, const TXString& contextualHelpID, const bool bEnableContextualHelp) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SelectChoice(Sint32 dialogID, Sint32 itemID, short nItemIndex, Boolean bSelect) override
		{
	
		}
		virtual void VCOM_CALLTYPE SelectEditText(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SelectTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetBelowItem(Sint32 dialogID, Sint32 srcItemID, Sint32  belowItemID, short indentStdCh, short lineSpacing) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetBooleanItem(Sint32 dialogID, Sint32 itemID, Boolean bSelect) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetCMYKColor(Sint32 dialogID, Sint32 itemID, TGSColorV2 &inColor) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetColorButton(Sint32 dialogID, Sint32 itemID, const RGBColor& rgb) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetColorChoice(Sint32 dialogID, Sint32 itemID, short colorIndex) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetComponentIndeterminate(Sint32 nDialogID, Sint32 nComponentID, Boolean bIndeterminateState) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentSize(Sint32 nDialogID, Sint32 nComponentID, int nWidthPixels, int nHeightPixels) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetControlData(Sint32 dialogID, Sint32 itemID, const SControlDataBase& data) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetEdgeBinding(Sint32 dialogID, Sint32 itemID, Boolean boundToLeft, Boolean boundToRight, Boolean boundToTop, Boolean boundToBottom) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetEditInteger(Sint32 dialogID, Sint32 componentID, Sint32 value) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetEditReal(Sint32 dialogID, Sint32 componentID, short editRealType, double value) override
		{
	
		}
		virtual bool VCOM_CALLTYPE SetFirstGroupItem(Sint32 dialogID, Sint32 groupID, Sint32 firstItemID) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetFirstLayoutItem(Sint32 dialogID, Sint32 firstItemID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetFocusOnItem(Sint32 liDialogID, Sint32 liComponentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetFocusOnListBrowser(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientSliderData(Sint32 dialogID, Sint32 componentID, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientSliderSelectedMarker(Sint32 dialogID, Sint32 componentID, short segmentIndex, short markerType) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetHelpText(Sint32 dialogID, Sint32 itemID, const TXString& helpText) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetIconPushButtonState(Sint32 nDialogID, Sint32 nComponentID, Boolean bPressed) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetImageControlHandle(Sint32 liDialogID, Sint32 liComponentID, MCObjectHandle hImage) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetImageControlPath(Sint32 nDialogID, Sint32 nComponentID, const TXString& strPath) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetImagePopupSelectedItem(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetItemText(Sint32 dialogID, Sint32 itemID, const TXString& strNewText) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetItemToolTipText(Sint32 nDialogID, Sint32 nComponentID, const TXString& strToolTip, const TXString& strSubToolTip, int nIndex, int nSubIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetLayoutDialogPosition(Sint32 dialogID, short left, short top) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetLayoutDialogSize(Sint32 dialogID, short width, short height) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetLayoutOption(Sint32 dialogID, short option, Sint32 value) override
		{
			return false;
		}


		virtual void VCOM_CALLTYPE SetLineWeightChoice(Sint32 dialogID, Sint32 itemID, short lineWeight) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnWidth(Sint32 dialogID, Sint32 componentID, short fromColumn, short toColumn, short width) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnOwnerDrawnType(Sint32 dialogID, Sint32 componentID, int iIndex, int iSubIndex, int iOwnerDrawnType) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnHeaderToolTip(Sint32 dialogID, Sint32 componentID, int iColumnIndex, const TXString& strToolTipPrimaryText, const TXString& strToolTipSubText) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnHeaderJust(Sint32 dialogID, Sint32 componentID, int iColumnIndex, int iJustification) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnImage(Sint32 nDialogID, Sint32 nComponentID, int nColumnIndex, int nImageIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserControlType(Sint32 dialogID, Sint32 componentID, short columnIndex, short controlType) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserDragAndDropColumn(Sint32 dialogID, Sint32 componentID, int iColumnIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserEditDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE SetListBrowserItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemIndex, int nSubItemIndex, Sint32 nUserData) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemGradientOrImageRefNumber(Sint32 dialogID, Sint32 componentID, int itemIndex, int iSubItemIndex, Sint32 liRefNumber) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, short imageIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPenForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPenBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextJust(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int justification) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextStyle(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, unsigned char textStyle) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextColor(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int redIndex, int greenIndex, int blueIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemUsingColumnDataItem(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short columnDataItemIndex) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE SetListBrowserSelection(Sint32 dialogID, Sint32 componentID, short firstItemIndex, short lastItemIndex, Boolean select) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetListBrowserSortColumn(Sint32 dialogID, Sint32 componentID, int columnIndex, Boolean isAscending) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetMarkerChoice(Sint32 dialogID, Sint32 itemID, MarkerType style, Sint8 angle, double size, double width, Uint8 thicknessBasis, double thickness) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetMultilineText(Sint32 dialogID, Sint32 itemID, GSHandle text) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetPatternData(Sint32 dialogID, Sint32 itemID, short patternIndex, short foreColor, short backColor) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetProportionalBinding(Sint32 dialogID, Sint32 itemID, Boolean leftProportional, Boolean rightProportional, Boolean topProportional, Boolean bottomProportional) override
		{
	
		}
		virtual bool VCOM_CALLTYPE SetRightItem(Sint32 dialogID, Sint32 srcItemID, Sint32 rightItemID, short indentStdCh, short lineSpacing) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetSelectionRange(Sint32 dialogID, Sint32 controlID, int startPos, int endPos) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextEditable(Sint32 dialogID, Sint32 itemID, Boolean editable) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetThreeStateCheckBoxState(Sint32 liDialogID, Sint32 liComponentID, int iState) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemID, SintptrT nItemData) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemData2(Sint32 nDialogID, Sint32 nComponentID, int nItemID, const TXString & itemData) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ShowEnhancedPullDownMenuGroupIcon(Sint32 liDialogID, Sint32 liComponentID, Boolean bShowGroupIcon) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ShowItem(Sint32 dialogID, Sint32 itemID, Boolean bShow) override
		{
	
		}
		virtual void VCOM_CALLTYPE UpdateCustomControlScrollArea(Sint32 dialogID, Sint32 component, int width, int height, int leftStart, int topStart, int stepSize, bool liveUpdate, bool alwaysShowHoriz, bool alwaysShowVert) override
		{
	
		}
		virtual void VCOM_CALLTYPE UpdateSymbolDisplayControl(Sint32 dialogIDIn, Sint32 itemIDIn, const TXString& symbolRefIn, SymbolImgInfo& imgInfoInOut) override
		{
	
		}
		virtual bool VCOM_CALLTYPE VerifyLayout(Sint32 dialogID) override
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE AddClass(const TXString& className) override
		{
			return -1;
		}

		virtual InternalIndex VCOM_CALLTYPE AddGuidesClass() override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE ColorIndexToName(const ColorRef& inColorRef, TXString& outColorName) override
		{
	
		}
		virtual void VCOM_CALLTYPE ColorIndexToRGB(ColorRef colorIndex, RGBColor& rgb) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CopySymbol(const TXString& inFilePath, const TXString& symName) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateGradient(const TXString& name) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateHatch(const TXString& inName, Boolean inUsePageUnits, Boolean inRotateInWalls, Boolean inRotateInSymbols, Boolean inTransparent,  ColorRef inFillColorIndex) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateImageFromPaint(MCObjectHandle paint, const TXString& imageName) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreatePaintFromImage(MCObjectHandle image) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateWallStyle(const TXString& wallStyleName) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteClass(const TXString& className) override
		{
	
		}

		virtual void VCOM_CALLTYPE DeselectAll() override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetActiveSymbolDef() override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetClassVisibility(InternalIndex index) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetCurrentLayer() override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE GetCurrentView() override
		{
			return 0;
		}

		virtual InternalIndex VCOM_CALLTYPE GetDimensionClassID() override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetGradientData(MCObjectHandle gradient, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetGradientMidpointPosition(MCObjectHandle gradient, short segmentIndex, double& position) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetGradientSpotColor(MCObjectHandle gradient, short segmentIndex, WorldPt3& color) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetGradientSpotPosition(MCObjectHandle gradient, short segmentIndex, double& position) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetGridUnits(WorldCoord& x, WorldCoord& y) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetHatchLevel(MCObjectHandle inHatchDef, short inLevel, WorldPt& outStartPt, WorldPt& outRepeatVec, double& outDashFactor, WorldPt& outOffsetVec, ColorRef& outColorIndex, short& outMilsLineWeight) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetLayerScaleN(MCObjectHandle h, double_gs& scale) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetNamedLayer(const TXString& layerName) override
		{
				return NULL;
		}
		virtual InternalIndex VCOM_CALLTYPE GetNoneClassID() override
		{
			return -1;
		}

		virtual short VCOM_CALLTYPE GetNumGradientSegments(MCObjectHandle gradient) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetPageBounds(WorldRect& bounds) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetPatternBits(short inIndex, Uint8 outPattern[8]) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetSheetLayerUserOrigin(MCObjectHandle layerHandle, WorldPt& origin) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetUnits(UnitsType& currentUnits) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetUserOrigin(WorldPt& origin) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetUserOriginFP(WorldPt& outOrigin) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE InsertGradientSegment(MCObjectHandle gradient, double_param spotPosition, double_param midpointPosition, const WorldPt3& color) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE MarkCurrentDocChanged() override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE NumSelectedObjects() override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE RemoveGradientSegment(MCObjectHandle gradient, short segmentIndex) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ResetAllObjectsVisibility() override
		{
	
		}
		virtual void VCOM_CALLTYPE RGBToColorIndex(const RGBColor& rgb, ColorRef& colorIndex) override
		{
	
		}
		virtual void VCOM_CALLTYPE SelectAll() override
		{
	
		}
		virtual void VCOM_CALLTYPE SetActiveSymbolDef(MCObjectHandle aSymDef) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetClassVisibility(InternalIndex index, Boolean visible) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetCurrentLayer(MCObjectHandle theLayer) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetCurrentLayerN(MCObjectHandle theLayer, Boolean bAllowUnifiedViewMaintenance /* = false by default */) override
		{
	
		}

		virtual Boolean VCOM_CALLTYPE SetGradientData(MCObjectHandle gradient, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientMidpointPosition(MCObjectHandle gradient, short segmentIndex, double_param position) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientSpotColor(MCObjectHandle gradient, short segmentIndex, const WorldPt3& color) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientSpotPosition(MCObjectHandle gradient, short& segmentIndex, double_param position) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetHatchLevel(MCObjectHandle inHatchDef, short inLevel, const WorldPt& inStartPt, const WorldPt& inRepeatVec, double_param inDashFactor, const WorldPt& inOffsetVec, ColorRef inColorIndex, short inMilsLineWeight) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetLayerScaleN(MCObjectHandle theLayer, double_param newScale) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetMarker(MCObjectHandle obj, MarkerType style, short size, short angle, Boolean start, Boolean end) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetProjection(MCObjectHandle theLayer, short newProj, Boolean confirmWithUser, Boolean doProgress) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetRenderMode(MCObjectHandle theLayer, short newRenderMode, Boolean immediate, Boolean doProgress) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetSheetLayerUserOrigin(MCObjectHandle layerHandle, const WorldPt& origin) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetUserOrigin(const WorldPt& origin) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetUserOriginFP(const WorldPt& inOrigin) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ShowCreateImageDialog() override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE ShowGradientEditorDialog(MCObjectHandle& gradient) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ValidClass(InternalIndex classID) override
		{
			return false;
		}
		virtual TTesselator VCOM_CALLTYPE CreateTessellator(short convertRes3D) override
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteTessellator(TTesselator pTess) override
		{
	
		}
		virtual bool VCOM_CALLTYPE TesselateObject(TTesselator pTess, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE UpdateThumbnailPreview(InternalIndex inIndex) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CloseXCode(Sint32 extCodeInfoID) override
		{
	
		}
		virtual GenericFunctionPtr VCOM_CALLTYPE OpenXCode(Sint32 extCodeInfoID, Boolean needsResourceFileOpen) override
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE GSDisposeHandle(GSHandle handle) override
		{
	
		}
		virtual void VCOM_CALLTYPE GSDisposePtr(void* p) override
		{
	
		}
		virtual void VCOM_CALLTYPE GSGetHandleSize(GSHandle handle, size_t& size) override
		{
	
		}
		virtual GSHandle VCOM_CALLTYPE GSNewHandle(size_t size) override
		{
			return NULL;
		}
		virtual VoidPtr VCOM_CALLTYPE GSNewPtr(size_t size) override
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE GSReduceHandleSize(GSHandle handle, size_t size) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GSSetHandleSize(GSHandle handle, size_t size) override
		{
			return false;
		}
		virtual VoidPtr VCOM_CALLTYPE GSSetPtrSize(void* p, size_t size) override
		{
			return NULL;
		}
		virtual Sint32 VCOM_CALLTYPE AddResourceToList(Sint32 listID, MCObjectHandle resource) override
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE BuildResourceList(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE DeleteResourceFromList(Sint32 listID, Sint32 index) override
		{
	
		}
		virtual void VCOM_CALLTYPE DisposeResourceList(Sint32 listID) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetActualNameFromResourceList(Sint32 listID, Sint32 index, TXString& name) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetMyMenuCommandIndex() override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetNameFromResourceList(Sint32 listID, Sint32 index, TXString& name) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetResourceFromList(Sint32 listID, Sint32 index) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ImportResourceToCurrentFile(Sint32 listID, Sint32 index) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE RegisterMenuForCallback(short menuIndex, OSType whichChange) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE ResourceListSize(Sint32 listID) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE UnregisterMenuForCallback(short menuIndex, OSType whichChange) override
		{
	
		}

		virtual void VCOM_CALLTYPE AddPullDownMenuItem(short group, const TXString& item) override
		{
	
		}
		virtual void VCOM_CALLTYPE AddPullDownMenuMode(const TXString& label) override
		{
	
		}

		virtual void VCOM_CALLTYPE AddTxtBtnMode(const TXString& theText) override
		{
	
		}
		virtual void VCOM_CALLTYPE EnableMode(short modeNum, Boolean enable) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetModeValue(short modeNum) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SetHelpString(const TXString& helpMessage) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetModeValue(short modeNum, short theValue) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetPullDownMenuSelection(short group, short selectedItem) override
		{
	
		}
		virtual void VCOM_CALLTYPE ClassIDToName(InternalIndex classID, TXString& outClassName) override
		{
	
		}
		virtual InternalIndex VCOM_CALLTYPE ClassNameToID(const TXString& className) override
		{
			return -1;
		}
		virtual MCObjectHandle VCOM_CALLTYPE InternalIndexToHandle(InternalIndex index) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE InternalIndexToNameN(InternalIndex index, TXString& outName) override
		{
	
		}
		virtual InternalIndex VCOM_CALLTYPE MaxClassID() override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE NameToInternalIndexN(const TXString& name, InternalIndex& index) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetPolyVertexLoopDirection(MCObjectHandle ioPolyToSet, PolyDirectionSpecType inPolyDirectionSpec) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE AddToConstraintModel(MCObjectHandle obj) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE AddViewportAnnotationObject(MCObjectHandle viewportHandle, MCObjectHandle annotationHandle) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AppendParameterWidget(Sint32 ObjectID, int parameterID, const TXString& text, Sint32 data) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AppendWidget(Sint32 ObjectID, int widgetType, int eventID, const TXString& text, Sint32 data) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ConvertTo3DPolygons(MCObjectHandle h, Boolean preserveOriginal) override
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE ConvertToNURBS(MCObjectHandle h, Boolean keepOrig) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolygon(MCObjectHandle h, Boolean preserveOriginal) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolygonN(MCObjectHandle h, Boolean preserveOriginal , short conversionResolution) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolyline(MCObjectHandle h, Boolean preserveOriginal) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE ConvertToUnstyledWall(MCObjectHandle theWall) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateConstraintModel(MCObjectHandle obj, Boolean useSelection) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateOffsetNurbsObjectHandle(MCObjectHandle h,   double offset) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtsCreate( MCObjectHandle inOwnerObj, int numDataElements, GS_CustomObjectControlPtsInitProcPtr initProc,void* env) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtsRemove(MCObjectHandle inOwnerObj) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtSet(MCObjectHandle inOwnerObj,int dataIndex, const WorldPt3& pt,Boolean is2DOnly,Boolean isHidden,int inClientID) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CustomObjectGetSurfaceProxy(MCObjectHandle inPathObject) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE CustomObjectReplacePath(MCObjectHandle inPathObject, MCObjectHandle pathPolyline) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteAllComponents(MCObjectHandle object) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteComponent(MCObjectHandle object, short componentIndex) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeleteConstraint(MCObjectHandle obj, MCObjectHandle constraint) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE DuplicateObject(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE DuplicateObjectWithNotification(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE EnableParameter(MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetEnabled) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EvaluateNurbsSurfacePointAndNormal(MCObjectHandle surfaceHandle, double u, double v, WorldPt3& point,  WorldPt3& normal) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ForEachLayer( GS_ForEachObjectProcPtr action, void *actionEnv) override
		{
	
		}
		virtual void VCOM_CALLTYPE ForEachObject( short traverseWhat, GS_ForEachObjectProcPtr action, void *actionEnv) override
		{
	
		}
		virtual void VCOM_CALLTYPE Get2DPt(MCObjectHandle obj, short index, WorldPt& loc) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetBinaryConstraint(short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetClosestPt(MCObjectHandle& obj, const WorldPt& pt, short& index, Sint32& containedObj) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetClosestSide(MCObjectHandle obj, const WorldPt& pt, short& indexA, short& indexB) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetComponentClass(MCObjectHandle object, short componentIndex, Sint32 &componentClass) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentFill(MCObjectHandle object, short componentIndex, Sint32 &fill) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentFillColors(MCObjectHandle object, short componentIndex, ColorRef &fillForeColor, ColorRef &fillBackColor) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentName(MCObjectHandle object, short componentIndex, TXString &componentName) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentPenColors(MCObjectHandle object, short componentIndex, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetComponentPenWeights(MCObjectHandle object, short componentIndex, Uint8 &leftPenWeight, Uint8 &rightPenWeight) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentUseFillClassAttr(MCObjectHandle object, short componentIndex, Boolean &useFillClassAttributes) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentUsePenClassAttr(MCObjectHandle object, short componentIndex, Boolean &useLeftPenClassAttributes, Boolean &useRightPenClassAttributes) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentWidth(MCObjectHandle object, short componentIndex, WorldCoord &width) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetCustomObjectColor(MCObjectHandle objectHand, int iTagID, ColorRef& ioColorRef) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectPath(MCObjectHandle objectHand) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectProfileGroup(MCObjectHandle objectHand) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetDimensionStandardVariable(short dimensionIndex, short fieldSelector, TVariableBlock& value) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDistanceAlongNurbsCurve(MCObjectHandle inNurbsCurve, double_param inParameter1, Sint32 inParameter1CurveIndex,  double_param inParameter2, Sint32 inParameter2CurveIndex, double_gs& outDistance) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginChoice(const TXString& pluginName, const TXString& parameterName, int choiceIndex, TXString& localizedChoice) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginName(const TXString& pluginName, TXString& outLocalizedName) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginParameter(const TXString& pluginName, const TXString& parameterName, TXString& localizedParameterName) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetNumberOfComponents(MCObjectHandle object, short &numComponents) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetNurbsObjectDistanceFromPoint(MCObjectHandle h, const WorldPt&  point,  double& distance) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectProperty(MCObjectHandle hObject, Sint32 inPropID, Boolean& outValue) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectPropertyChar(MCObjectHandle hObject, Sint32 inPropID, unsigned char& outValue) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectVariable(MCObjectHandle theObject, short setSelector, TVariableBlock& value) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetParameterOnNurbsCurve(MCObjectHandle h, const WorldPt3&  point,  double& parameter, Sint32& index) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetPointAndParameterOnNurbsCurveAtGivenLength(MCObjectHandle inNurbCurve, double_param inPercentOfLength, WorldPt3& outPointOnCurve,  double_gs& outParametricParameter, Sint32& outPiecewiseCurveIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetRoofEdge(MCObjectHandle object, short index, WorldPt& vertexPt, double_gs& slope, WorldCoord& projection, WorldCoord& eaveHeight) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetSingularConstraint(short type, MCObjectHandle obj, short vertexA, short vertexB) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetViewportClassVisibility(MCObjectHandle viewportHandle, InternalIndex classIndex, short& visibilityType) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportCropObject(MCObjectHandle viewportHandle) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportGroup(MCObjectHandle viewportHandle, short groupType) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportGroupParent(MCObjectHandle groupHandle) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetViewportLayerVisibility(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short& visibilityType) override
		{
			return false;
		}
		virtual MeshErrorType VCOM_CALLTYPE GroupToMesh(MCObjectHandle theMesh) override
		{
			return MeshErrorType(0);
		}
		virtual Boolean VCOM_CALLTYPE HasConstraint(MCObjectHandle obj) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE InsertAllParametersAsWidgets(Sint32 inObjectID) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE InsertParameterWidget(Sint32 ObjectID, int position, int parameterID, const TXString& text, Sint32 data) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE InsertWidget(Sint32 ObjectID, int position, int widgetType, int eventID, const TXString& text, Sint32 data) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsObjectFromReferencedFile(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsViewportGroupContainedObject(MCObjectHandle objectHandle,  short groupType) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE MakePolyshapeValid(MCObjectHandle thePoly) override
		{
	
		}
		virtual MeshErrorType VCOM_CALLTYPE MeshToGroup(MCObjectHandle theMesh) override
		{
			return MeshErrorType(0);
		}
		virtual void VCOM_CALLTYPE MoveObject(MCObjectHandle h, WorldCoord dx, WorldCoord dy) override
		{
	
		}
		virtual void VCOM_CALLTYPE MoveObject3D(MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz, bool inMoveScreenObjectsWith3D = false) override
		{
	
		}
		virtual void VCOM_CALLTYPE NotifyLayerChange(StatusData liAdditionalData) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE RemoveCustomObjectColor(MCObjectHandle objectHand, int iTagID) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveRoofEdge(MCObjectHandle object, short index) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ResetObject(MCObjectHandle h) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RotateObjectN(MCObjectHandle& h, const WorldPt& rotCenter, double_param angle) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE ScaleObject3D(MCObjectHandle ioObject, const WorldPt3& scaleCen, const Vector& scaleVector) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ScaleObjectN(MCObjectHandle h, const WorldPt& scaleCen, double_param scaleX, double_param scaleY) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetBinaryConstraint(short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetHorizontalDimensionConstraint(MCObjectHandle obj1, const WorldPt& pt1, const WorldPt& pt2, WorldCoord distance, ViewCoord offset) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetVerticalDimensionConstraint(MCObjectHandle hObj, const WorldPt& pt1, const WorldPt& pt2, WorldCoord distance, ViewCoord offset) override { return false; }
		virtual Boolean VCOM_CALLTYPE DeleteDimensionConstraints(MCObjectHandle obj1) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentClass(MCObjectHandle object, short componentIndex, Sint32 componentClass) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentFill(MCObjectHandle object, short componentIndex, Sint32 fill) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentFillColors(MCObjectHandle object, short componentIndex, ColorRef fillForeColor, ColorRef fillBackColor) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentName(MCObjectHandle object, short componentIndex, const TXString &componentName) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentPenColors(MCObjectHandle object, short componentIndex, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE SetComponentPenWeights(MCObjectHandle object, short componentIndex, Uint8 leftPenWeight, Uint8 rightPenWeight) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentUseFillClassAttr(MCObjectHandle object, short componentIndex, Boolean useFillClassAttributes) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentUsePenClassAttr(MCObjectHandle object, short componentIndex, Boolean useLeftPenClassAttributes, Boolean useRightPenClassAttributes) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentWidth(MCObjectHandle object, short componentIndex, WorldCoord width) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetConstraintValue(MCObjectHandle constraint, double_param value) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetCustomDimensionStandardVariable(short dimensionIndex, short fieldSelector, const TVariableBlock& value) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE SetCustomObjectColor(MCObjectHandle objectHand, int iTagID, ColorRef inColorRef) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetCustomObjectControlPointVisibility(MCObjectHandle objectHand, short controlPtIndex, Boolean setVisible) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetCustomObjectPath(MCObjectHandle objectHand, MCObjectHandle pathHand) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetCustomObjectProfileGroup(MCObjectHandle objectHand, MCObjectHandle profileGroupHand) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDefinition(MCObjectHandle h, MCObjectHandle newDef) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetObjectProperty(Sint32 inCodeRefID, Sint32 inPropID, Boolean inValue) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetObjectPropertyChar(Sint32 inCodeRefID, Sint32 inPropID, unsigned char inValue) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetObjectVariable(MCObjectHandle theObject, short setSelector, const TVariableBlock& value) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetParameterVisibility(MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetVisible) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetRoofEdge(MCObjectHandle object, short index, const WorldPt& vertexPt, double_param slope, WorldCoord projection, WorldCoord eaveHeight) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetSingularConstraint(short type, MCObjectHandle obj, short vertexA, short vertexB) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetViewportClassVisibility(MCObjectHandle viewportHandle, InternalIndex classIndex, short visibilityType) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetViewportCropObject(MCObjectHandle viewportHandle, MCObjectHandle cropHandle) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetViewportLayerVisibility(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short visibilityType) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TrimToSelectedObjects(MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE UpdateConstraintModel() override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE UpdateViewport(MCObjectHandle viewportHandle) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE ViewportHasCropObject(MCObjectHandle viewportHandle) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GSCountResources(OSType inType, Boolean lookOnlyInCurrentFile)
		{
			return 0;
		}
		virtual GSHandle VCOM_CALLTYPE GSGetIndResource(OSType inType, short inIndex, short& outID, Boolean lookOnlyInCurrentFile)
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE GetVWResourceString(TXString& outValue, const char* resourceIdentifier, const char* resourceStringIdentifier, EEmptyHandling allowEmpty) override
		{
	
		}
		virtual GSHandle VCOM_CALLTYPE GetVWResource(const char* resourceIdentifier) override
		{
			return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE FirstSelectedObject() override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetSelectionBounds(WorldRect& bounds, BoundsType type) override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetSelectionBoundsCube(WorldCube &theCube) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE MoveSelection(WorldCoord dx, WorldCoord dy) override
		{
	
		}
		virtual void VCOM_CALLTYPE MoveSelection3D(WorldCoord dx, WorldCoord dy, WorldCoord dz) override
		{
	
		}
		virtual void VCOM_CALLTYPE RotateSelectionN(const WorldPt& rotCen, double_param rotAngle) override
		{
	
		}
		virtual void VCOM_CALLTYPE ScaleSelectionN(const WorldPt& scaleCen, double_param scaleX, double_param scaleY) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE AddText(MCObjectHandle textBlock, Sint32 beforeChar, Handle newText) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddTextFromBuffer(MCObjectHandle textBlock, Sint32 beforeChar, const UCChar* buffer, Sint32 bufferSize) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextBlock(const TXString& textStr, const WorldPt& textOrigin, Boolean fixedSize, WorldCoord width) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteText(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars) override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetCharNumFromPoint(MCObjectHandle textBlock, const WorldPt& pt) override
		{
			return 0;
		}
		virtual TXString VCOM_CALLTYPE GetTextChars(MCObjectHandle textBlock) override
		{
			return "";
		}
		virtual void VCOM_CALLTYPE GetTextColor(MCObjectHandle textBlock, Sint32 charNum, ColorRef& charColor) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextFontIndex(MCObjectHandle textBlock, Sint32 charNum, short& fontIndex) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextJustification(MCObjectHandle textBlock, short& justification) override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetTextLength(MCObjectHandle textBlock) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetTextLineHeight(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& height) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextOrientationN(MCObjectHandle h, double_gs& angle, short& flipState) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextSize(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& charSize) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextStyle(MCObjectHandle textBlock, Sint32 charNum, unsigned char& charStyle) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextVerticalAlignment(MCObjectHandle textBlock, short& verticalAlignment) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextVerticalSpacing(MCObjectHandle textBlock, short& spacing, WorldCoord& height) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetTextWidth(MCObjectHandle textBlock, WorldCoord& width) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE GetTextWrap(MCObjectHandle textBlock, Boolean& wrapped) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetTextColor(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, ColorRef charColor) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextFontIndex(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, short fontIndex) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextJustification(MCObjectHandle textBlock, short justification) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextOrientationN(MCObjectHandle h, double_param angle, short flipState) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextSize(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, WorldCoord charSize) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextStyle(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char charStyle) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextVerticalAlignment(MCObjectHandle textBlock, short verticalAlignment) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextVerticalSpacing(MCObjectHandle textBlock, short spacing, WorldCoord height) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextWidth(MCObjectHandle textBlock, WorldCoord width) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextWrap(MCObjectHandle textBlock, Boolean wrapped) override
		{
	
		}
		virtual void VCOM_CALLTYPE SpellCheckTextBuffer(GSHandle charsHandle, Boolean textChanged) override
		{
	
		}
		virtual void VCOM_CALLTYPE AttachDefaultTextureSpace(MCObjectHandle object, short multiPartID, Sint32 partCategoryID = 0) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateShaderRecord(MCObjectHandle texture, Sint32 family, Sint32 prototype) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTexture() override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextureBitmap() override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextureBitmapFromPaintNode(MCObjectHandle paintNodeObject) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteTextureSpace(MCObjectHandle object, short multiPartID) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EditShaderRecord(MCObjectHandle shaderRecord) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE EditTexture(MCObjectHandle texture) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE EditTextureSpace(MCObjectHandle texturedObject, short multiPartID) override
		{
			return false;

		}
		virtual InternalIndex VCOM_CALLTYPE GetClGenTexture(InternalIndex index) override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetClRoofTextures(InternalIndex index, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetClUseTexture(InternalIndex index) override
		{
			return false;

		}
		virtual void VCOM_CALLTYPE GetClWallTextures(InternalIndex index, InternalIndex& right, InternalIndex& left, InternalIndex& center) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetShaderRecord(MCObjectHandle parentNode, Sint32 family) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE ResetOldTextures(MCObjectHandle object, Boolean bClear2009Texture) override
		{

		}
		virtual InternalIndex VCOM_CALLTYPE GetTextureRef(MCObjectHandle object, short multiPartID, Boolean resolveByClass) override
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE GetTextureRefN(MCObjectHandle object, short multiPartID, short partCategoryID, Boolean resolveByClass) override
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetTextures(MCObjectHandle h, InternalIndex& primaryTexture, InternalIndex& secondaryTexture, InternalIndex& tertiaryTexture) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetTextureSpace(MCObjectHandle object, short multiPartID) override
		{
				return NULL;
		}
		virtual InternalIndex VCOM_CALLTYPE GetVPClassGenTexture(MCObjectHandle viewport, InternalIndex classIndex) override
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE GetVPClassRoofTextures(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetVPClassWallTextures(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& right, InternalIndex& left, InternalIndex& center) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetClGenTexture(InternalIndex index, InternalIndex texture) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetClRoofTextures(InternalIndex index, InternalIndex top, InternalIndex edge, InternalIndex dormer) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetClUseTexture(InternalIndex index, Boolean use) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetClWallTextures(InternalIndex index, InternalIndex right, InternalIndex left, InternalIndex center) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultTextureSpace(MCObjectHandle object, MCObjectHandle space, short multiPartID) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextureRef(MCObjectHandle object, InternalIndex textureRef, short multiPartID) override
		{

		}
		virtual void VCOM_CALLTYPE SetTextureRefN(MCObjectHandle object, InternalIndex textureRef, short multiPartID, short partCategoryID) override
		{}

		virtual MCObjectHandleID VCOM_CALLTYPE AddToolPersistentDraw(GS_PersistentDrawProcPtr drawProcPtr, void *drawEnv) override
		{
			return 0;
		}
		virtual MCObjectHandleID VCOM_CALLTYPE AddToolSnapGeometry(MCObjectHandle inSnapGeometry) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE BoxToolDraw() override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE ClearAllToolPts() override
		{
			return false;

		}
		virtual void VCOM_CALLTYPE ClearDataDisplayBar() override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE ClickDragToolStatus() override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE CustomBarCreate(short inNumFields, CustomBarRefID& outCustomBarRefID) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarGetFieldInfo(CustomBarRefID inCustomBarID, short inFieldIndex, CustomBarFieldInfo& inFieldInfo) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarInstall(CustomBarRefID inCustomBarID) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarRelease(CustomBarRefID inCustomBarRefID) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldAngle(CustomBarRefID inCustomBarID, short inFieldIndex, const double& inDegrees) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldInfo(CustomBarRefID inCustomBarID, short inFieldIndex, const CustomBarFieldInfo& inFieldInfo) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldWorldCoord(CustomBarRefID inCustomBarID, short inFieldIndex, const WorldCoord& inCoordVal) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE Default2DToolDraw() override
		{
	
		}
		virtual void VCOM_CALLTYPE Default3DToolDraw() override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordArcN(const WorldRect& theBox, double_param startAngle, double_param sweepAngle) override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordEllipse(WorldRect& theBox) override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordLine(const WorldPt& p1, const WorldPt& p2) override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordLine3D(const WorldPt3& p1, const WorldPt3& p2) override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordRect(const WorldRect& theBox) override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawDataDisplayBar(Boolean drawFramesFirst) override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawNurbsObject(MCObjectHandle h) override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawObject(MCObjectHandle h, Boolean doSelect) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetCoords(WorldPt& p, ViewPt& m) override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetNumToolPts() override
		{
			return 0;
		}
		virtual const ICoreToolAccess* VCOM_CALLTYPE GetToolCoreInterface() override
		{
			return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPt2D(Sint32 inIndex, WorldPt& outToolPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPt3D(Sint32 inIndex, WorldPt3& outToolPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrent2D(WorldPt& outToolPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrent3D(WorldPt3& outToolPt) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrentViewPt(ViewPt& outToolPt) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrentWorkingPlane(WorldPt3& outToolPt) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtViewPoint(Sint32 inIndex, ViewPt& outToolPoint) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtWorkingPlane(Sint32 inIndex, WorldPt3& outToolPoint) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE InstallConstraintAlong3DLine(const Ray& inConstraintDescription) override
		{
	
		}
		virtual void VCOM_CALLTYPE Interactive2DDraw( short options, short shiftConsMode, GS_I2DDrawProcPtr drawProc, void *env) override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE OnePointToolStatus() override
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE PolyToolStatus() override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE PopLastToolPt() override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RemoveHotSpot(HotSpotRefID inHotSpotID) override
		{
	
		}
		virtual void VCOM_CALLTYPE RemoveToolPersistentDraw(MCObjectHandleID persistentDrawRefID) override
		{
	
		}
		virtual void VCOM_CALLTYPE RemoveToolSnapGeometry(MCObjectHandleID inSnapGeometryID) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetCursorMode() override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDataDisplayBarField(short fieldNum, BarNumberType barType, const TXString& inBarLabel) override
		{
	
		}

		virtual void VCOM_CALLTYPE SetDimUserBarValue(short fieldNum, WorldCoord dimVal) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetFloatUserBarValueN(short fieldNum, double_param floatVal, short numPlaces) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextUserBarValue(short fieldNum, const TXString& textVal) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetToolProperty(Sint32 inCodeRefID, Sint32 inToolPropID, Boolean inValue) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetToolPropertyChar(Sint32 inCodeRefID, Sint32 inToolPropID, char inValue) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE ThreePointToolStatus() override
		{
			return 0;
		}
		virtual HotSpotRefID VCOM_CALLTYPE TrackHotSpot(Boolean& outIs3d, WorldPt3& outLocation) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE TrackTool(MCObjectHandle& overObject, short& overPart, SintptrT& code) override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE TwoPointToolStatus() override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE AddObjectToContainer(MCObjectHandle h, MCObjectHandle container) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE AuxOwner(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteObject(MCObjectHandle h, Boolean useUndo) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE FindHandleDeep(MCObjectHandle handleToFind, MCObjectHandle firstObjectInSearchList, MCObjectHandle& unused) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE FirstMemberObj(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetDefaultContainer() override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetDrawingHeader() override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetHatchListHeader() override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetSymbolLibraryHeader() override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE InsertObjectAfter(MCObjectHandle h, MCObjectHandle afterObject) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE InsertObjectBefore(MCObjectHandle h, MCObjectHandle beforeObject) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE LastMemberObj(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE NextObject(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ParentObject(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE PrevObject(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE SearchForAncestorType(Sint16 objectType, MCObjectHandle h) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE SetPageBounds(const WorldRect& bounds) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE AcquireExportPDFSettingsAndLocation(Boolean inbSeparateDocuments) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ClosePDFDocument() override
		{
	
		}
		virtual short VCOM_CALLTYPE ExportPDFPages(const TXString& inSavedViewNameStr) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE OpenPDFDocument(const TXString& inFileNameStr) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddAfterMoveObject(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddAfterSwapObject(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddBeforeMoveObject(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddBeforeSwapObject(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddBothSwapObject(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddBothSwapLayerProperties(MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddCoordMoveObject2D(MCObjectHandle h, WorldCoord dx, WorldCoord dy) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddCoordMoveObject3D(MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE EndUndoEvent() override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE NameUndoEvent(const TXString& name) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE NonUndoableActionOK() override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetUndoMethod(short undoType) override
		{
	
		}
		virtual void VCOM_CALLTYPE SupportUndoAndRemove() override
		{
	
		}
		virtual void VCOM_CALLTYPE UndoAndRemove() override
		{
	
		}
		virtual void VCOM_CALLTYPE AngleToStringN(double_param angle, TXString& s) override
		{
	
		}
		virtual void VCOM_CALLTYPE AssociateLinearDimension(MCObjectHandle h, Boolean selectedObjectsMode) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CallPluginLibrary(const TXString& routineName, PluginLibraryArgTable* argumentTable, Sint32 status) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ClipSurface(MCObjectHandle h1, MCObjectHandle h2) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CombineIntoSurface(const WorldPt& insidePt) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE CoordToDimString(WorldCoord c, TXString& s) override
		{
	
		}
		virtual Sint16 VCOM_CALLTYPE CStringCompare(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE CStringEqual(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DisableModules(Sint32 modules) override
		{
	
		}
		virtual void VCOM_CALLTYPE DisplayContextHelpOfCurrentPlugin() override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE DisplayContextualHelp(const TXString& helpIdentifier) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DisplayOrganizationDialog(short tabToSelect) override
		{
	
		}
		virtual short VCOM_CALLTYPE DoMenuName(const TXString& name, short chunkIndex) override
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE DoProgramAction(short actionSelector, void* actionEnv) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE DoubleToString(TNumStyleClass inNumStyle,  Byte inAccuracy, Byte inFormat, double_param inDouble, TXString& outString) override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawScreen(const ViewRect& clipRect, Boolean isLastFrame) override
		{
	
		}
		virtual void VCOM_CALLTYPE EllipseEllipseIntersect(const WorldRect& e1, const WorldRect& e2, Sect4Struct& sects) override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE ExternalNameToID(const TXString& fnName) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE FontIndexFromName(const TXString& fontName) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE FontNameFromIndex(short fontIndex, TXString& fontName, Boolean useMappingTable) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetActiveSerialNumber(TXString& outSerialNumber) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetCallBackInval() override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetCurrentMode() override
		{
			return 0;
		}
		virtual int VCOM_CALLTYPE GetDataBarCursorVisState() override
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE GetEnabledModules() override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetHostInfo(short& hostID, Byte& version, Byte& majorRev, Byte& minorRev, TXString& outProductName, TXString& outProductVersion) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetModifierFlags(Boolean& optionFlag, Boolean& cmdFlag, Boolean& shiftFlag) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetProduct(short& product, Sint32& modules) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetSavedSetting(const TXString& category, const TXString& setting, TXString& value) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE HandlePendingUpdatesAndActivates() override
		{
	
		}
		virtual void VCOM_CALLTYPE HilitePalettesAndTopDocument(Boolean doHilite) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE IntersectObjects(MCObjectHandle obj1, MCObjectHandle obj2, Boolean onlyOnObjs) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE Kludge(short selector, void* in, void* out) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE LineEllipseIntersect(const WorldPt& a1, const WorldPt& a2, const WorldRect& r, Sect2Struct& sects) override
		{
	
		}
		virtual void VCOM_CALLTYPE LineLineIntersect(const WorldPt& a1, const WorldPt& a2, const WorldPt& b1, const WorldPt& b2, Boolean& parallel, Boolean& intOnLines, WorldPt& sect) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE ObjectNearCoordPt(const WorldPt& p) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE PlaySoundResource(Handle soundResource, Boolean async, Boolean forcePlay) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE PointInsidePoly(const WorldPt& checkPt, MCObjectHandle h) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE PointOnPolyEdge(const WorldPt& checkPt, MCObjectHandle h, WorldCoord checkRadius) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE RegisterExternal(const TXString& fileName, short codeResID, OSType codeResType) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE RegisterNotificationProcedure(StatusProcPtr proc, OSType whichChange) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetCallBackInval(Boolean turnInvalOn) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetPersistentHighlight(MCObjectHandle theObject, Boolean highlightState) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetSavedSetting(const TXString& category, const TXString& setting, const TXString& value) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE StringToAngleN(const TXString& s, double_gs& angle) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE StringToDouble(TNumStyleClass inNumStyle, const TXString& inString, double_gs& outDouble) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SymbolContainsLight(MCObjectHandle symbol) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ToggleObjectHighlight(MCObjectHandle theObject) override
		{
	
		}
		virtual void VCOM_CALLTYPE UnregisterNotificationProcedure(StatusProcPtr proc, OSType whichChange) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE VerifyPluginLibrary(const TXString& routineName) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetPerspectiveInfo(MCObjectHandle theLayer, WorldCoord& perspectiveDistance, WorldCoord& clipDistance, WorldRect& clipRect) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetProjection(MCObjectHandle theLayer) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetRenderMode(MCObjectHandle theLayer) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetScreenDPI() override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetViewCenter(WorldPt& center) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetViewMatrix(MCObjectHandle theLayer, TransformMatrix& theMat) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorkingPlane(Axis &theAxis) override
		{
	
		}
		virtual void VCOM_CALLTYPE NewCurrentViewMatrix(const TransformMatrix& theMat, Boolean interactive) override
		{
	
		}
		virtual void VCOM_CALLTYPE NewWorkingPlane(const Axis &theAxis) override
		{
	
		}
		virtual void VCOM_CALLTYPE PreviewDrawFrame(Handle thisPreview, Boolean selectedOnly) override
		{
	
		}
		virtual void VCOM_CALLTYPE PreviewFinish(Handle& thisPreview) override
		{
	
		}
		virtual Handle VCOM_CALLTYPE PreviewSetup(Boolean doDynamicSpeedups, double_param targetFPS, Boolean drawGroundPlane, Boolean drawPage, Boolean drawCropRect) override
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE RedrawRect(const WorldRect& redrawR) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetViewCenter(const WorldPt& center) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetViewMatrix(MCObjectHandle theLayer, const TransformMatrix& theMatrix) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorkingPlaneAxis(const Vector &si, const Vector &sj, const Vector &sk) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorkingPlaneVertex(const WorldPt3 &v) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetZoomFactorN(double_param zoomFac) override
		{
	
		}
		virtual void VCOM_CALLTYPE ViewRotWorldZN(double_param angle, Boolean interactive) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE WorldRect2ViewRect(const WorldRect& wRect, ViewRect& vRect) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE AddBreak(MCObjectHandle theWall, WorldCoord off, short breakType, void* breakData) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE DeleteBreak(MCObjectHandle theWall, short index) override
		{
	
		}
		virtual void VCOM_CALLTYPE ForEachBreak( MCObjectHandle theWall, GS_ForEachBreakProcPtr action, void* actionEnv) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetPolyBreakGeometry(MCObjectHandle theWall, short breakIndex, MCObjectHandle& polyline) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWallCaps(MCObjectHandle theWall, Boolean &leftCap, Boolean &rightCap, Boolean &round) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWallCapsOffsets(MCObjectHandle theWall, WorldCoord &leftCapLeftOffset, WorldCoord &leftCapRightOffset, WorldCoord &rightCapLeftOffset, WorldCoord &rightCapRightOffset) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWallCornerHeights(MCObjectHandle theWall, WorldCoord& startHeightTop, WorldCoord& startHeightBottom, WorldCoord& endHeightTop, WorldCoord& endHeightBottom) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE JoinWalls(MCObjectHandle firstWall, MCObjectHandle secondWall,  const WorldPt& firstWallPt, const WorldPt& secondWallPt, JoinModifierType joinModifier, Boolean capped, Boolean showAlerts) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE MoveWallByOffset(MCObjectHandle theWall, WorldCoord& offset) override
		{
	
		}
		virtual void VCOM_CALLTYPE ReverseWallSides(MCObjectHandle theWall) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetAsPolyBreak(MCObjectHandle& thePolyline, MCObjectHandle theWall, short breakIndex) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetBreak(MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetWallCaps(MCObjectHandle theWall, const Boolean &leftCap, const Boolean &rightCap, const Boolean &round) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallCapsOffsets(MCObjectHandle theWall, WorldCoord leftCapLeftOffset, WorldCoord leftCapRightOffset, WorldCoord rightCapLeftOffset, WorldCoord rightCapRightOffset) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallCornerHeights(MCObjectHandle theWall, WorldCoord startHeightTop, WorldCoord startHeightBottom, WorldCoord endHeightTop, WorldCoord endHeightBottom) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallStyle(MCObjectHandle theWall, InternalIndex wallStyle, WorldCoord selectedOffset, WorldCoord replacingOffset) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallWidth(MCObjectHandle theWall, WorldCoord newWidth) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE WrapGetWallWidth(MCObjectHandle theWall, double_gs& outCoordLen) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetScreenSize(ViewRect& screenRect) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE AutoFitWorksheetRowHeights(MCObjectHandle worksheet, short fromRow, short toRow) override
		{
	
		}
		virtual void VCOM_CALLTYPE ClearWorksheetCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateWorksheet(const TXString& name, short rows, short columns) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateWorksheetImage(MCObjectHandle worksheet, const WorldPt& topLeftCorner) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteWorksheetColumns(MCObjectHandle worksheet, short startColumn, short numColumns) override
		{
	
		}
		virtual void VCOM_CALLTYPE DeleteWorksheetRows(MCObjectHandle worksheet, short startRow, short numRows) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetTopVisibleWorksheet() override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetWkSheetSubrowCellActualString(MCObjectHandle worksheet, const ViewPt& cell, Sint16 subrow, TXString& cellString) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellAlignment(MCObjectHandle worksheet, const ViewPt& cell, short& cellAlignment) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellBorder(MCObjectHandle worksheet, const ViewPt& cell, Boolean& top, Boolean& left, Boolean& bottom, Boolean& right) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellFill(MCObjectHandle worksheet, const ViewPt& cell, short& style, ColorRef& bgcolor, ColorRef& fgcolor, short& fillpattern) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellFormula(MCObjectHandle worksheet, const ViewPt& cell, TXString& formula) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellNumberFormat(MCObjectHandle worksheet, const ViewPt& cell, short& style, short& accuracy, TXString& leaderString, TXString& trailerString) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellString(MCObjectHandle worksheet, const ViewPt& cell, TXString& cellString) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellTextFormat(MCObjectHandle worksheet, const ViewPt& cell, short& fontIndex, short& size, short& style) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellTextAngle(MCObjectHandle worksheet, const ViewPt& cell, short& angle) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellTextColor(MCObjectHandle worksheet, const ViewPt& cell, ColorRef& color) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellValue(MCObjectHandle worksheet, const ViewPt& cell, double& cellValue) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellVertAlignment(MCObjectHandle worksheet, const ViewPt& cell, short& vAlignment) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellWrapTextFlag(MCObjectHandle worksheet, const ViewPt& cell, Boolean& wrapTextFlag) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, short& sort1, short& sort2, short& sort3, short& sum1, short& sum2, short& sum3) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetColumnWidth(MCObjectHandle worksheet, short column, short& width) override
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetWorksheetFromImage(MCObjectHandle worksheetImage) override
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetWorksheetImage(MCObjectHandle worksheet) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetWorksheetMergedCellRange(MCObjectHandle worksheet, const ViewPt& cell, ViewPt& topLeftCell, ViewPt& bottomRightCell) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetWorksheetPlacement(MCObjectHandle worksheet, ViewRect& windowPosition) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetRowColumnCount(MCObjectHandle worksheet, short& numRows, short& numColumns) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetRowHeight(MCObjectHandle worksheet, short row, short& height) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetRowHLockState(MCObjectHandle worksheet, short row, Boolean& lockState) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetSelection(MCObjectHandle worksheet, ViewPt& currentCell, ViewPt& topLeftRangeCell, short& topRangeSubrow, ViewPt& bottomRightRangeCell, short& bottomRangeSubrow) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCellString(MCObjectHandle worksheet, const ViewPt& cell, short subrow, TXString& cellString) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCellValue(MCObjectHandle worksheet, const ViewPt& cell, short subrow, double& cellValue) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCount(MCObjectHandle worksheet, short databaseRow, short& numSubrows) override
		{
	
		}

		virtual void VCOM_CALLTYPE InsertWorksheetColumns(MCObjectHandle worksheet, short beforeColumn, short numColumns) override
		{
	
		}
		virtual void VCOM_CALLTYPE InsertWorksheetRows(MCObjectHandle worksheet, short beforeRow, short numRows) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetCell(MCObjectHandle worksheet, const ViewPt& cell) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetRange(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetSubrowCell(MCObjectHandle worksheet, const ViewPt& cell, short subrow) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetCellNumber(MCObjectHandle worksheet, const ViewPt& cell) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetCellString(MCObjectHandle worksheet, const ViewPt& cell) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetDatabaseRow(MCObjectHandle worksheet, short databaseRow) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetSubrowCellNumber(MCObjectHandle worksheet, const ViewPt& cell, short subrow) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetSubrowCellString(MCObjectHandle worksheet, const ViewPt& cell, short subrow) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetVisible(MCObjectHandle worksheet) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RecalculateWorksheet(MCObjectHandle worksheet) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTopVisibleWorksheet(MCObjectHandle worksheet) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellAlignment(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short cellAlignment) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellBorder(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellBorders(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline, Boolean insideHorz, Boolean insideVert) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellFill(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, ColorRef bgcolor, ColorRef fgcolor, short fillpattern) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellFormula(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, const TXString& formula) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellNumberFormat(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, short accuracy, const TXString& leaderString, const TXString& trailerString) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellTextFormat(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short fontIndex, short size, short style) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellTextAngle(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short angle) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellTextColor(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, ColorRef color) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellVertAlignment(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short vAlignment) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellWrapTextFlag(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean wrapTextFlag) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, short sort1, short sort2, short sort3, short sum1, short sum2, short sum3) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetColumnWidth(MCObjectHandle worksheet, short fromColumn, short toColumn, short width) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCurrentCell(MCObjectHandle worksheet, const ViewPt& currentCell) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetPlacement(MCObjectHandle worksheet, const ViewRect& windowPosition) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetRowsHeight(MCObjectHandle worksheet, short fromRow, short toRow, short height, Boolean updatePalette, Boolean lockHeight) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetSelection(MCObjectHandle worksheet, const ViewPt& currentCell, const ViewPt& topLeftRangeCell, short topRangeSubrow, const ViewPt& bottomRightRangeCell, short bottomRangeSubrow) override
		{
	
		}


		virtual void VCOM_CALLTYPE ShowWorksheet(MCObjectHandle worksheet, Boolean show) override
		{
	
		}
		virtual void VCOM_CALLTYPE ShowWorksheetDialog(short dialogType) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE WorksheetMergeCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WorksheetSplitCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetCurrentWorkspaceFile(TXString& outFileName) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorkspaceFileToReload(const TXString& inFileName) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE WSAddMenu(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuName) override
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE WSAddMenuItem(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName, char inShortcutKey, Uint32 inShortcutKeyModifiers, const TXString& inSubMenuIdentifier) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSAddTool(Sint32 inWorkspaceReference, const TXString& inToolIdentifier, char inShortcutKey, Uint32 inKeyModifiers) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSAddToolPalette(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSAddToolSet(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSGetVersion(Sint32 inWorkspaceReference, Sint32* outWorkspaceVersion) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSMenuAddMenuItem(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSMenuBarAddMenu(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSOpen(const TXString& inWorkspaceFileToOpen, Sint32 inFilePermissions, Sint32* outWorkspaceReference) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSPaletteGetHomeCorner(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, short* outWindowHomeCorner) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSPaletteSetHomeCorner(Sint32 inWorkspaceReference, const TXString& inPaletteIdentifier, short inWindowHomeCorner) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSSetVersion(Sint32 inWorkspaceReference, Sint32 inWorkspaceVersion) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSToolPaletteAddToolSet(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, const TXString& inToolSetIdentifier) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSToolSetAddTool(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSToolSetAddToolChildToTool(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, const TXString& inParentToolIdentifier, const TXString& inChildToolIdentifier) override
		{
			return false;
		}

	// VW2009
	public:
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFileInStandardFolder(GS_ForEachFilePathProcPtr processFile, EFolderSpecifier folderSpec, void* env) override
		{
			return kStopForEachFile_NoError;
		}

		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInStandardFolder(GS_ForEachFilePathProcPtr processFile, FolderSpecifier folderSpec, void* env) override
		{
			return kStopForEachFile_NoError;
		}
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInFolder(GS_ForEachFilePathNProcPtr processFile, IFolderIdentifier* pStartFolderID, bool doRecursive, void* pEnv) override
		{
			return kStopForEachFile_NoError;
		}
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInPluginFolder(GS_ForEachFilePathNProcPtr processFile, void* pEnv) override
		{
			return kStopForEachFile_NoError;
		}
		virtual bool VCOM_CALLTYPE GetActiveDocument(IFileIdentifier** ppOutFileID, bool& outSaved) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE OpenDocumentPath(IFileIdentifier* pFileID, bool bShowErrorMessages) override
		{
			return false;
		}
		virtual GSError VCOM_CALLTYPE SaveActiveDocumentPath(IFileIdentifier* pFileID) override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE EncryptVSPluginFile(IFileIdentifier* pPluginFileID, bool doObfuscation) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE ReadVSExternalFile(IFileIdentifier* pFileID, TMPExternalDataForWorkspace& outData) override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE ImportDXF(IFileIdentifier* pFileID) override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE WriteMaterialImageFile(IFileIdentifier* pFileID, MCObjectHandle hMaterial, Sint32 type, Sint32 shaderFamily) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ReadMaterialImageFile(IFileIdentifier* pFileID) override
		{
				return NULL;
		}

		virtual void VCOM_CALLTYPE ClearComponentInstances(MCObjectHandle hContainer, TComponentTypeID componentTypeID) override
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE FindFirstComponentInstance(MCObjectHandle hContainer, TComponentTypeID componentTypeID) override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE FindNextComponentInstance(TComponentTypeID componentTypeID, MCObjectHandle hComponent) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE AssignAsComponentInstance(MCObjectHandle hParentContainer, TComponentTypeID componentTypeID, MCObjectHandle hComponent) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE EnableComponentInstance(MCObjectHandle hComponent, bool bEnable) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE IsEnabledComponentInstance(MCObjectHandle hComponent) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetComponentInstanceTypeID(MCObjectHandle hComponent, TComponentTypeID& outComponentTypeID) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetComponentInstanceName(MCObjectHandle hComponent, const TXString& localizedName) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetComponentInstanceName(MCObjectHandle hComponent, TXString& outLocalizedName) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE EmptyToolHighlightingList() override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingObject(MCObjectHandle hHighlightObject) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingSegment( const WorldPt& startPt,  const WorldPt& endPt) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE AddToolHighlightingPolyCreate() override
		{
			return NULL;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingPoly(MCObjectHandle polyID, bool bClosed) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingPolyAddVertex(MCObjectHandle polyID, const WorldPt& pt, VertexType type, WorldCoord arcRadius) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingSegment3D( const WorldPt3& startPt,  const WorldPt3& endPt) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE AddToolHighlightingPoly3DCreate() override
		{
			return NULL;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingPoly3D(MCObjectHandle polyID, bool bClosed) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingPoly3DAddVertex(MCObjectHandle polyID, const WorldPt3& pt) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE OpenURL(const TXString& url) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertNurbsToPolylineArcs(MCObjectHandle hNurbs, double precision, bool insert) override
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE CreateOffsetObjectHandle(MCObjectHandle h, double offset, bool smoothConers) override
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE UnfoldSurface(MCObjectHandle surfaceToUnfold, short conversionRes) override
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE CreateWallHoleGroup(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallHoleGroup(MCObjectHandle h) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE SetDefaultTextureMapping(MCObjectHandle h, TexturePartSDK partID) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultTextureMappingN(MCObjectHandle h, short texPartID, short partCategoryID) override
		{}
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfo(MCObjectHandle h, TexturePartSDK partID) override
		{
			TextureMappingInfoSDK infoSDK;
			memset(&infoSDK, 0, sizeof(TextureMappingInfoSDK));
	
			return infoSDK;
		}
		virtual void VCOM_CALLTYPE SetTextureMappingInfo(MCObjectHandle h, TexturePartSDK partID, const TextureMappingInfoSDK& mappingInfo) override
		{
	
		}
		virtual bool			VCOM_CALLTYPE IsPartTexturedFromOveral(MCObjectHandle h, short multiPartID, short partCategoryID = 0) override
		{
			return false;
		}
		virtual bool			VCOM_CALLTYPE RevertPartTextureToOveral(MCObjectHandle h, short multiPartID, short partCategoryID = 0) override
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE PerformMultipleUnion(int numberOf2dObjsToAdd, MCObjectHandle h, bool insert) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetWorksheetSubrowHeight(MCObjectHandle worksheet, short databaserow, short subrow, short& height) override
		{
	
		}
		virtual bool VCOM_CALLTYPE SetCustomObjectWallHoleGroup(MCObjectHandle objectHand, MCObjectHandle hGeomGroup) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetCustomObjectSelectionGroup(MCObjectHandle objectHand) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE SetCustomObjectSelectionGroup(MCObjectHandle objectHand, MCObjectHandle hSelGroup) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWallFootPrint(MCObjectHandle hWall) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE ExportResource(MCObjectHandle resource, IFileIdentifier* pFileID , bool suppressDialogs) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE CallDefaultTool(ToolMessage* message, std::shared_ptr<void>& messageContext) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE EnableDrawingWorksheetPalette(bool enable, MCObjectHandle worksheet) override
		{
	
		}
		virtual bool VCOM_CALLTYPE GetWorksheetAutoRecalcState(MCObjectHandle worksheet) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetWorksheetAutoRecalcState(MCObjectHandle worksheet, bool state) override
		{
	
		}

	// VW2010
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWorkingPlane(const Axis &theAxis, const TXString& name) override
		{
				return NULL;
		}
		virtual Axis VCOM_CALLTYPE SetWPHybridTool(bool bRestore) override
		{
			Axis axis;
	
			memset(&axis, 0, sizeof(Axis));
	
			return axis;
		}
		virtual void VCOM_CALLTYPE RestoreWPHybridTool(bool bRestore) override
		{
	
		}
		virtual void VCOM_CALLTYPE ClearWPHybridTool() override
		{
	
		}
		virtual void VCOM_CALLTYPE SetCursorByView() override
		{
	
		}
		virtual bool VCOM_CALLTYPE AddUndoDeselectObj(MCObjectHandle hObject) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddUndoSelectObj(MCObjectHandle hObject) override
		{
			return false;
		}
		virtual TOSWndPtr VCOM_CALLTYPE GetLayoutDialogOSHandle(Sint32 dialogID) override
		{
			return NULL;
		}
		virtual TOSWndPtr VCOM_CALLTYPE GetLayoutControlOSHandle(Sint32 dialogID, Sint32 itemID) override
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE SetTextureRef(MCObjectHandle object, InternalIndex textureRef, TexturePartSDK texPartID, Sint32 texLayerID) override
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetTextureRef(MCObjectHandle object, TexturePartSDK texPartID, Sint32 texLayerID, Boolean resolveByClass) override
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetDefaultTextureMapping(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID) override
		{
	
		}
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfo(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID) override
		{
			TextureMappingInfoSDK infoSDK;
			memset(&infoSDK, 0, sizeof(TextureMappingInfoSDK));
	
			return infoSDK;
		}
		virtual void VCOM_CALLTYPE SetTextureMappingInfo(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID, const TextureMappingInfoSDK& mappingInfo) override
		{
	
		}
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfoN(MCObjectHandle h, short multiPartID, short partCategoryID) override
		{
			TextureMappingInfoSDK infoSDK;
			memset(&infoSDK, 0, sizeof(TextureMappingInfoSDK));

			return infoSDK;
		}
		virtual void			VCOM_CALLTYPE SetTextureMappingInfoN(MCObjectHandle h, short multiPartID, short partCategoryID, const TextureMappingInfoSDK& mappingInfo) override
		{}
		virtual Sint32 VCOM_CALLTYPE GetNumTextureLayers(MCObjectHandle h, TexturePartSDK texPartID) override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE SetStaticTextStyle(Sint32 dialogID, Sint32 itemID, int style) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetStaticTextColor(Sint32 dialogID, Sint32 itemID, int red, int green, int blue) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetItemClickable(Sint32 dialogID, Sint32 itemID, bool clickable) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetSliderLiveUpdate(Sint32 dialogID, Sint32 itemID, bool liveUpdate) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreatePaintNode(IDrawPad* pDrawPad) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE DrawSymbolPreview(IDrawPad* pDrawPad, InternalIndex resourceRefNum, const ViewRect& destRect, short viewMode, short renderMode, ViewRect* outDrawBounds) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE NotifyClassChange(StatusData liAdditionalData) override
		{
	
		}
		virtual bool VCOM_CALLTYPE RegisterDialogForTimerEvents(Sint32 dialogID, Uint32 numberOfMilliseconds) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeregisterDialogFromTimerEvents(Sint32 dialogID) override
		{
	
		}
		virtual bool VCOM_CALLTYPE SetImageControlData(Sint32 nDialogID, Sint32 nComponentID, void *imageData, size_t imageDataByteSize) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetListItemEnabled(Sint32 dialogID, Sint32 componentID, short itemIndex, bool enabled) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetFullBreakRecord(MCObjectHandle theWall, short index, WorldCoord off, SymbolBreakType* breakData) override
		{
		}
		virtual bool VCOM_CALLTYPE SetObjectAsCornerBreak(MCObjectHandle objectHandle, MCObjectHandle wallHandle, bool CornerBreak) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetObjectWallOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord offset) override
		{
			return false;
		}
		virtual EWallCapAttributesType VCOM_CALLTYPE GetWallCapAttributesType(MCObjectHandle wall) override
		{
			return eWallCapAttributesType_wallLine;
		}
		virtual void VCOM_CALLTYPE SetWallCapAttributesType(MCObjectHandle wall, EWallCapAttributesType wallCapAttributesType) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetCoreWallComponent(MCObjectHandle object) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SetCoreWallComponent(MCObjectHandle object, short componentIndex) override
		{
	
		}
		virtual EWallHoleTexturePart VCOM_CALLTYPE GetWallHoleTexturePart(MCObjectHandle object) override
		{
			return eWallHoleTexturePart_holes;
		}
		virtual void VCOM_CALLTYPE SetWallHoleTexturePart(MCObjectHandle object, EWallHoleTexturePart part) override
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWallFeature(MCObjectHandle wall, MCObjectHandle profile, EWallFeatureType wallFeatureType) override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetActiveLayer() override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateCustomObjectByMatrixEx(const TXString& name, const TransformMatrix& matrix, bool bInsert) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE SetHighlightedHelpString(const TXString& helpMessage) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetCurrentLocalization(TXString& outLanguage, TXString& outSubLanguage) override
		{
	
		}
		virtual void VCOM_CALLTYPE RGBToColorIndexN(const RGBColor& rgb, ColorRef& colorIndex, Boolean bIgnoreBlackBackground) override
		{
	
		}
		virtual void VCOM_CALLTYPE ColorIndexToRGBN(ColorRef colorIndex, RGBColor& rgb, Boolean bIgnoreBlackBackground) override
		{
	
		}
		virtual void VCOM_CALLTYPE RefreshRenderingForSelectedObjects() override
		{
	
		}
		virtual void VCOM_CALLTYPE RefreshResourceBrowserResourcesList(bool immediate) override
		{
	
		}
		virtual bool VCOM_CALLTYPE GetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short& outPatternIndex) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short patternIndex) override
		{
			return false;
		}

		virtual InternalIndex VCOM_CALLTYPE SetDashStyle(const TXString& name, bool scaleWithThick, const std::vector<double>& inVectors) override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE PointInsideAnEnclosedRegionOfTheGroup(MCObjectHandle h, WorldPt &pickPt) override
		{
			return false;
		}

	// VW2011
	public:
		virtual MCObjectHandle  VCOM_CALLTYPE CreateArcLengthDimension(const WorldPt& dimStartPt, const WorldPt& dimEndPt, const WorldPt& arcCenterPt, const WorldCoord& startOffset, const bool clockwiseArc, bool witnessPerpChord, const bool arcIndicator) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetTextCustomStyle(MCObjectHandle textBlock, Sint32 charNum, unsigned char& customStyle) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextCustomStyle(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char customStyle) override
		{
	
		}
		virtual bool VCOM_CALLTYPE GetRoofRunRise(Sint32 dialogID, Sint32 componentID, double& run, double& rise, double& value) override
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE CallDefaultToolN(EDefaultToolType type, bool isStandard, ToolMessage* message, std::shared_ptr<void>& messageContext) override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE SetModeBarButtonsHelpText(const TXStringArray& arrHelpText) override
		{
			return false;
		}

		virtual HotSpotRefID VCOM_CALLTYPE TrackHotSpotN(Boolean& outIs3d, WorldPt3& outLocation, Sint32& outData) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE ShowRecFormatResourceDialog(MCObjectHandle& hFormat, Boolean isNewResource, bool hideInvisibleParameters) override
		{
	
		}
		virtual bool VCOM_CALLTYPE AlignColumnEdge(Sint32 dialogID, Sint32 srcItemID, short columnID, short alignMode ) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeleteSymbolDefinition(MCObjectHandle hSymDef, Boolean bCompletely, Boolean useUndo) override
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetTilePopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return -1;

		}
		virtual short VCOM_CALLTYPE GetTilePopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetTilePopupSelectedItem(Sint32 dialogID, Sint32 componentID) override
		{
			return 0;
		}
		virtual InternalIndex	VCOM_CALLTYPE GetHatchPopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return -1;

		}
		virtual short VCOM_CALLTYPE GetHatchPopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetHatchPopupSelectedItem(Sint32 dialogID, Sint32 componentID) override
		{
			return 0;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateTile(const TXString& name) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE ShowEditTileDialog(MCObjectHandle& tileHandle) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE ShowEditTileSettingsDialog(MCObjectHandle& tileHandle) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ShowNewTileDialog () override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE GetTileBackgroundColor(MCObjectHandle tile, ColorRef& backgroundColor) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetTileBackgroundColor(MCObjectHandle tile , const ColorRef& backgroundColor) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetTileGeometryGroup (MCObjectHandle tileHandle) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE GetListBrowserItemTileRefNumber(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 &liRefNumber) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetListBrowserItemTileRefNumber(Sint32 dialogID, Sint32 componentID, int itemIndex, int iSubItemIndex, Sint32 liRefNumber) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE AddToolEditTextMethod(const TXString & label, const TXString & value) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetToolEditTextMethodValue(short group, const TXString& value) override
		{
	
		}
		virtual TXString VCOM_CALLTYPE GetToolEditTextMethodValue(short group) override
		{
			return TXString("error");
		}
		virtual void VCOM_CALLTYPE EditRealConvertToStringUtility(short editRealType, double value, TXString& valueText) override
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GSNewObjectHandle(short objectType) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE InvalObj(MCObjectHandle h) override
		{
	
		}
		virtual bool VCOM_CALLTYPE SetTextAdorner(MCObjectHandle textBlock, MCObjectHandle textAdorner, const WorldPt& scalePt) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlItemText(Sint32 dialogID, Sint32 componentID, int nItemID, TXString& itemText) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlSelectedItemText(Sint32 dialogID, Sint32 componentID, TXString& itemText) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddTileGeometryObject(MCObjectHandle tileHandle, MCObjectHandle objectHandle) override
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE GetTileGroupParent(MCObjectHandle objectHandle) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE IsTileGroupContainedObject(MCObjectHandle objectHandle) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectPlanarBounds(MCObjectHandle h, WorldRectVerts& outBoxVerts) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetCurrToolInteractiveDraw(IToolInteractiveDraw** outInteractiveDraw) override
		{
	
		}
		virtual bool VCOM_CALLTYPE ArePlanarMatricesCoplanar(TransformMatrix & inMat1, TransformMatrix & inMat2, TransformMatrix& outTransformFrom2To1) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DrawCoordLineOnPlane( const WorldPt& pt1, const WorldPt& pt2, TPlanarRefID refID ) override
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordLineOnPlane3D( const WorldPt& pt1, const WorldPt& pt2, TPlanarRefID refID ) override
		{
	
		}
		virtual bool VCOM_CALLTYPE GetPlanarMatrix(const TPlanarRefID& planarRefID, TransformMatrix& outMatrix) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetPlanarRefID( MCObjectHandle objectHandle, TPlanarRefID& outRefID ) override
		{
	
		}
		virtual bool VCOM_CALLTYPE IsScreenPlanarRefID(const TPlanarRefID& planarRefID) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE IsPlanarObject( MCObjectHandle objectHandle, TPlanarRefID& outPlanarRefID ) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE IsPlanarObjectIn3DView( MCObjectHandle objectHandle ) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE PlanarPtTo3DModelPt( const TPlanarRefID& refID, const WorldPt& inPt, WorldPt3& outPt ) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE PlanarPtToScreenPlanePt( const TPlanarRefID& refID, WorldPt& outPt) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ScreenPlanePtToPlanarPt( const TPlanarRefID& refID, WorldPt& outPt ) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetPlanarRefID( MCObjectHandle objectHandle, const TPlanarRefID& refID ) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetPlanarRefIDToGround( MCObjectHandle objectHandle ) override
		{
	
		}
		virtual TPlanarRefID VCOM_CALLTYPE GetCurrentPlanarRefID( ) override
		{
			return kPlanarRefID_ScreenPlane;
		}
		virtual short VCOM_CALLTYPE GetObjectTypeN(MCObjectConstHandle h) const override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE ResizeSelectedDims( MCObjectHandle origH, const WorldCoord valueChange, const Sint32 dimCount, const Boolean onDraw, const Boolean dimLineResize, const Boolean fixedLengthWitLines ) override
		{
	
		}
		virtual TXString VCOM_CALLTYPE GetImageFileName(TXString &resourceFileName, Sint32 family, MCObjectHandle imageNode) override
		{
			return TXString("error");
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateImageDefNodeFromPNGData(void* pngData, size_t pngDataSize) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE CompressTextureImage(MCObjectHandle image) override
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateTextureBitmapNoDialog(MCObjectHandle parentShaderRecord) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE ShowListBrowserRadioToolTips(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE Default2DToolDrawNew(const TPlanarRefID& planarRefID) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextStyleRef(MCObjectHandle object, InternalIndex styleRef) override
		{
	
		}
		virtual InternalIndex VCOM_CALLTYPE GetTextStyleRef(MCObjectHandle object) override
		{
			return -1;

		}
		virtual short VCOM_CALLTYPE AlertQuestionDefault(const TXString& question, const TXString& advice, short defaultButton, const TXString& OKOverrideText, const TXString& CancelOverrideText, const TXString& customButtonAText, const TXString& customButtonBText, const TXString& category, const TXString& item, const TXString& checkboxOverrideText, short defaultAnswer) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE SetColorName(ColorRef colorIndex, const TXString& colorName) override
		{
			return false;
		}
		virtual TXString		VCOM_CALLTYPE GetColorName(ColorRef colorIndex) override
		{
			return "error";
		}

		virtual bool VCOM_CALLTYPE IsScreenObject( MCObjectHandle objectHandle ) override
		{
			return false;
		}
		virtual bool	        VCOM_CALLTYPE PieceWiseNurbsCurveReverseInPlace( MCObjectHandle objectHandle ) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreatePieceWiseNurbsCurveReverse( MCObjectHandle objectHandle ) override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateSlab(MCObjectHandle profile) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE ModifySlab(MCObjectHandle slab, MCObjectHandle modifier, bool isClipObject, Uint32 componentFlags) override
		{
			return false;
		}
		virtual InternalIndex	VCOM_CALLTYPE GetSlabStyle(MCObjectHandle slab) override
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetSlabStyle(MCObjectHandle slab, InternalIndex slabStyle) override
		{
	
		}
		virtual void VCOM_CALLTYPE ConvertToUnstyledSlab(MCObjectHandle slab) override
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetSlabPreferencesStyle() override
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetSlabPreferencesStyle(InternalIndex slabStyle) override
		{
	
		}
		virtual void VCOM_CALLTYPE BeginMultipleDuplicate() override
		{
	
		}
		virtual void VCOM_CALLTYPE EndMultipleDuplicate() override
		{
	
		}
		virtual void VCOM_CALLTYPE BuildConstraintModelForObject(MCObjectHandle objectHandle, bool traverseContainers) override
		{
	
		}
		virtual void VCOM_CALLTYPE RecordModifiedObjectInConstraintModel(MCObjectHandle objectHandle, bool useSelection) override
		{
	
		}
		virtual Boolean	        VCOM_CALLTYPE GetCurveEndsAndTangents( MCObjectHandle objectHandle, WorldPt3& startPt, WorldPt3& endPt, WorldPt3& startTangent, WorldPt3& endTangent ) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AreWorksheetGridLinesVisible( MCObjectHandle worksheet) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetWorksheetGridLinesVisibility( MCObjectHandle worksheet, Boolean bVisible) override
		{
	
		}
		virtual bool VCOM_CALLTYPE AreUpdateChecksEnabled(void) override
		{
			return false;
		}	// returns true if update checking is supported
		virtual void VCOM_CALLTYPE CheckForUpdates(void) override
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateCustomObjectPathNoOffset(const TXString& name, MCObjectHandle pathHand, MCObjectHandle profileGroupHand) override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE NumberCustomDimensionStandards(void) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE ConsolidatePlanarObjects(const MCObjectHandle objectHandle, MCObjectHandle& objectHandleToBeTransformed) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE FindClosestPointOnNURBSObjectFrom3DPoint(MCObjectHandle h, const WorldPt3& point3D, WorldPt3 &outClosestPoint) override
		{
			return false;
		}
		virtual WorldCoord VCOM_CALLTYPE GetSlabHeight(MCObjectHandle slab) override
		{
			return 0.0;
		}
		virtual void VCOM_CALLTYPE SetSlabHeight(MCObjectHandle slab, WorldCoord height) override
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateSlabStyle(const TXString &slabStyleName) override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetWallPreferences() override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetSlabPreferences() override
		{
				return NULL;
		}
		virtual ETextureSet VCOM_CALLTYPE GetTextureSet(MCObjectHandle object) override
		{
			return eTextureSet_objectTextures;
		}
		virtual void VCOM_CALLTYPE SetTextureSet(MCObjectHandle object, ETextureSet textureSet) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetDatumSlabComponent(MCObjectHandle object) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SetDatumSlabComponent(MCObjectHandle object, short componentIndex) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetComponentOffsetFromWallTop(MCObjectHandle object, short componentIndex, WorldCoord &offsetFromWallTop) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentOffsetFromWallTop(MCObjectHandle object, short componentIndex, WorldCoord offsetFromWallTop) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentOffsetFromWallBottom(MCObjectHandle object, short componentIndex, WorldCoord &offsetFromWallBottom) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentOffsetFromWallBottom(MCObjectHandle object, short componentIndex, WorldCoord offsetFromWallBottom) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentFollowTopWallPeaks(MCObjectHandle object, short componentIndex, Boolean &followTopWallPeaks) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentFollowTopWallPeaks(MCObjectHandle object, short componentIndex, Boolean followTopWallPeaks) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentFollowBottomWallPeaks(MCObjectHandle object, short componentIndex, Boolean &followBottomWallPeaks) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentFollowBottomWallPeaks(MCObjectHandle object, short componentIndex, Boolean followBottomWallPeaks) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentAutoBoundEdgeOffset(MCObjectHandle object, short componentIndex, EWallBound &autoBoundEdgeOffset) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentAutoBoundEdgeOffset(MCObjectHandle object, short componentIndex, EWallBound autoBoundEdgeOffset) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentManualEdgeOffset(MCObjectHandle object, short componentIndex, WorldCoord &manualEdgeOffset) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentManualEdgeOffset(MCObjectHandle object, short componentIndex, WorldCoord manualEdgeOffset) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentTexture(MCObjectHandle object, short componentIndex, InternalIndex &texture) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentTexture(MCObjectHandle object, short componentIndex, InternalIndex texture) override
		{
			return false;
		}
		virtual WorldCoord VCOM_CALLTYPE GetComponentNetArea(MCObjectHandle object, short componentIndex) override
		{
			return 0.0;
		}
		virtual WorldCoord VCOM_CALLTYPE GetComponentNetVolume(MCObjectHandle object, short componentIndex) override
		{
			return 0.0;
		}
		virtual void VCOM_CALLTYPE FontMapReplace(const TXStringArray& arrFonts, bool doUserInterface) override
		{
	
		}
		virtual void VCOM_CALLTYPE FontMapGetReplacement(const TXString& orgFont, TXString& outReplFont) override
		{
	
		}
		virtual short VCOM_CALLTYPE ConvertFontIDToIndex(short fontID) override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE ConvertIndexToFontID(short fontIndex) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE Get2DPolyAreaAndPerimeter(MCObjectHandle h, double &area, double &perimeter) override
		{
	
		}
		virtual void VCOM_CALLTYPE IFC_ResetGUID(MCObjectHandle hRecord) override
		{
	
		}
		virtual bool VCOM_CALLTYPE IFC_IsIFCRecord(MCObjectHandle hRecord) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetWallComponentPoly(MCObjectHandle hWall, short componentIndex) override
		{
				return NULL;
		}


	// VW2012
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE GetObjectHiddenLine(MCObjectHandle hGeometry3D, double cuttingHeight, bool bottomOfCuttingPlane) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE AddBeforeModifyWorkingPlane() override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE ModelPtToPlanarPt(const TPlanarRefID& refID, const WorldPt3& inModelPt, WorldPt& outPlanarPt) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ImportResourceToCurrentFileN(Sint32 listID, Sint32 index, TImportResourceConflictCallbackProcPtr conflictCallback, void* env) override
		{
				return NULL;
		}
		virtual TXString VCOM_CALLTYPE CoordToPrimaryDimensionString(WorldCoord coord) override
		{
			return "error";
		}
		virtual TXString VCOM_CALLTYPE CoordToSecondaryDimensionString(WorldCoord coord) override
		{
			return "error";
		}
		virtual void VCOM_CALLTYPE GetWallOverallHeights(MCObjectHandle theWall, WorldCoord& overallHeightTop, WorldCoord& overallHeightBottom) override
		{
	
		}
		virtual bool VCOM_CALLTYPE SetWallOverallHeights(MCObjectHandle theWall, const SStoryObjectData &bottomData, const SStoryObjectData &topData) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CheckParametricNameConflictWithUI(const TXString& name) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ShowByClassChoice(Sint32 dialogID, Sint32 componentID) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE IsClassChoiceSelected(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SelectClassChoice(Sint32 dialogID, Sint32 componentID, Boolean select) override
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetMeshVertexCount(MCObjectHandle hMesh) override
		{
			return 0;
		}
		virtual WorldPt3 VCOM_CALLTYPE GetMeshVertexAt(MCObjectHandle hMesh, size_t at) override
		{
			return WorldPt3(0.0, 0.0, 0.0);
		}
		virtual void VCOM_CALLTYPE SetMeshVertexAt(MCObjectHandle hMesh, size_t at, const WorldPt3& pt) override
		{
	
		}
		virtual void VCOM_CALLTYPE RunTempTool(const VWIID& iidToolExt) override
		{
	
		}
		virtual bool VCOM_CALLTYPE RenderPoly(MCObjectHandle hPoly, IVertexListener* listener, short convRes) override
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE NewCreateCombineIntoSurface(const WorldPt& inPoint, short columnsAndPilastersEnum, bool goThrougLayre, MCObjectHandle listOfObjs) override
		{
				return NULL;
		}

		virtual void VCOM_CALLTYPE PushPullPlanarGetInternalProcPtrAndUserData(PushPullHandleCompletionRoutinePtr& outProcPtr, void*& outUserData) override
		{
	
		}
		virtual void VCOM_CALLTYPE PushPullPlanarBegin(PushPullHandleCompletionRoutinePtr inCompletionProcPtr, void* inUserData) override
		{
	
		}
		virtual void VCOM_CALLTYPE PushPullPlanarAddObjectID(MCObjectHandle inHandleIDOfPlanarObjectToPushPull) override
		{
	
		}
		virtual void VCOM_CALLTYPE PushPullPlanarEnd() override
		{
	
		}
		virtual bool VCOM_CALLTYPE PushPullPlanarIsEnabled() override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE PushPullPlanarSetEnabled(bool inSetVal) override
		{
	
		}
		virtual bool VCOM_CALLTYPE PushPullPlanarNeedsPickLoop() override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE PushPullPlanarActionHandler(ToolMessage* message, Sint32& outPushPullReturn, bool& outHandledExclusively) override
		{
	
		}
		virtual void VCOM_CALLTYPE PushPullPlanarAddPrefButton() override
		{
	
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateProxyObjOnLayer(MCObjectHandle hParametric, MCObjectHandle hLayer) override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetProxyParent(MCObjectHandle hProxyObj) override
		{
				return NULL;
		}

		virtual InternalIndex	VCOM_CALLTYPE AddClassWithUI(TXString& inOutName) override
		{
			return -1;

		}
		virtual bool VCOM_CALLTYPE EditClassWithUI(InternalIndex classIndex) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE EditClassWithUI(InternalIndex* arrClassIndex, size_t len) override
		{
			return false;
		}

		virtual void VCOM_CALLTYPE ViewPt2WorldPt(const ViewPt& viewPt, WorldPt& outWorldPt) override
		{
	
		}
		virtual bool VCOM_CALLTYPE WorldPt2ViewPt(const WorldPt& worldPt, ViewPt& outViewPt) override
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE CloseDocument() override
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetNumStories() override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumLayerLevelTypes() override
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumStoryLayerTemplates() override
		{
			return 0;
		}
		virtual TXString		VCOM_CALLTYPE GetLayerLevelType(MCObjectHandle layer) override
		{
			return "error";
		}
		virtual bool VCOM_CALLTYPE SetLayerLevelType(MCObjectHandle layer, TXString& layerLevelType) override
		{
			return false;
		}
		virtual TXString		VCOM_CALLTYPE GetStoryLayerTemplateName(short index) override
		{
			return "error";
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryOfLayer(MCObjectHandle layer) override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetLayerForStory(MCObjectHandle story, const TXString &layerLevelType) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE CreateStory(TXString& name, TXString& suffix) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateLayerLevelType(TXString& name) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateStoryLayerTemplate(TXString& name, double scaleFactor, TXString& layerLevelType, WorldCoord elevationOffset, WorldCoord defaultWallHeight, short& index) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE DeleteStoryLayerTemplate(short index) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AssociateLayerWithStory(MCObjectHandle layer, MCObjectHandle story) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryAbove(MCObjectHandle story) override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryBelow(MCObjectHandle story) override
		{
				return NULL;
		}
		virtual WorldCoord		VCOM_CALLTYPE GetStoryElevation(MCObjectHandle story) override
		{
			return 0.0;
		}
		virtual bool VCOM_CALLTYPE SetStoryElevation(MCObjectHandle story, WorldCoord elevation) override
		{
			return false;
		}
		virtual TXString		VCOM_CALLTYPE GetStorySuffix(MCObjectHandle story) override
		{
			return "error";
		}
		virtual bool VCOM_CALLTYPE SetStorySuffix(MCObjectHandle story, const TXString & suffix) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE HasObjectStoryBounds(MCObjectHandle hObject) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE HasObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id, SStoryObjectData& outData) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id, const SStoryObjectData& data) override
		{
			return false;	
		}
		virtual bool VCOM_CALLTYPE DelObjectStoryBounds(MCObjectHandle hObject) override
		{
			return false;	
		}
		virtual bool VCOM_CALLTYPE DelObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id) override
		{
			return false;	
		}
		virtual size_t VCOM_CALLTYPE GetObjectStoryBoundsCount(MCObjectHandle hObject) override
		{
			return 0;
		}
		virtual TObjectBoundID	VCOM_CALLTYPE GetObjectStoryBoundsAt(MCObjectHandle hObject, size_t index) override
		{
			return 0;
		}
		virtual WorldCoord		VCOM_CALLTYPE GetObjectBoundElevation(MCObjectHandle hObject, TObjectBoundID id) override
		{
			return 0.0;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertToPolylineWithTangentVertices(MCObjectHandle hNonPoly) override
		{
				return NULL;
		}


		virtual HotSpotRefID VCOM_CALLTYPE AddHotSpotN(short inHotSpotType, const WorldPt3& inLocation, const TXString& cursorSpec, const TXString& inTip, Sint32 data) override
		{
			return 0;
		}

		virtual bool VCOM_CALLTYPE CreateImageControl2(Sint32 dialogID, Sint32 controlID, int widthInPixels, int heightInPixels, const TXString& imageSpecifier) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE UpdateImageControl2(Sint32 dialogID, Sint32 controlID, const TXString& imageSpecifier) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE UpdateImageControlUsingFullFilePath(Sint32 dialogID, Sint32 controlID, IFileIdentifier* imgFileID) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateImageButton(Sint32 dialogID, Sint32 controlID, int widthInStdChar, const TXString& imageSpecifier) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE UpdateImageButton(Sint32 dialogID, Sint32 controlID, const TXString& imageSpecifier) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateThumbnailPopup(Sint32 dialogID, Sint32 controlID) override
		{
			return false;
		}

		virtual void VCOM_CALLTYPE AddButtonMode(const TXString& iconSpec) override
		{
	
		}
		virtual void VCOM_CALLTYPE AddCheckMode(short initialSetting, const TXString& iconSpec) override
		{
	
		}
		virtual void VCOM_CALLTYPE AddRadioMode(short initialSetting, const TXStringArray& imageSpecs) override
		{
	
		}

		virtual short VCOM_CALLTYPE AddListBrowserImage(Sint32 dialogID, Sint32 componentID, const TXString& imageSpecifier) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserMultImageIndexes(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TXString& imageSpec0, TXString& imageSpec1, TXString& imageSpec2) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserMultImageIndexes(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, const TXString& imageSpec0, const TXString& imageSpec1, const TXString& imageSpec2) override
		{
			return false;
		}
		virtual int	 VCOM_CALLTYPE InsertEnhancedPullDownMenuItem(Sint32 dialogID, Sint32 componentID, const TXString& strName, const TXString& imageSpecifier) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE InsertProposedClassOrLayerItem(Sint32 nDialogID, Sint32 nComponentID, const TXString& strLabel, const TXString& iconSpec) override
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE AreAlertsAllowed() override
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE HasWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType) override
		{
			return false;
		}
		virtual EWSColumnDatabaseSortType VCOM_CALLTYPE GetWorksheetColumnSortType(MCObjectHandle worksheet, short databaseRow, short column) override
		{
			return kWSSortAscending;
		}
		virtual void VCOM_CALLTYPE SetWorksheetColumnSortType(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseSortType sortType) override
		{
	
		}
		virtual short   VCOM_CALLTYPE GetWorksheetColumnSortPrecedence(MCObjectHandle worksheet, short databaseRow, short column) override
		{
			return 0;
		}
		virtual void  VCOM_CALLTYPE MoveWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short fromColumn, short toColumn, EWSColumnDatabaseOperatorType operatorType) override
		{
	
		}
		virtual void  VCOM_CALLTYPE AddWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType) override
		{
	
		}
		virtual void  VCOM_CALLTYPE RemoveAllWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, EWSColumnDatabaseOperatorType operatorType) override
		{
	
		}
		virtual void  VCOM_CALLTYPE RemoveWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetStoryBoundChoiceStrings(MCObjectHandle story, bool topBound, TXStringArray& strings) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetStoryBoundDataFromChoiceString(const TXString& string, SStoryObjectData& data) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetChoiceStringFromStoryBoundData(const SStoryObjectData& data, TXString& string) override
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateRenderworksStyle() override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE Get3DObjEdgeData(const ViewPt& viewPt, MCObjectHandle objectH, WorldPt3& edgeStart, WorldPt3& edgeEnd) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetStoryLayerTemplateInfo(short index, TXString& name, double& scaleFactor, TXString& layerLevelType, double& elevationOffset, double& defaultWallHeight) override
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE GetObjectGeneratingAutoPlane() override
		{
				return NULL;
		}

		virtual WorldCoord		VCOM_CALLTYPE GetVertexMaxRadius(MCObjectHandle h, short vertexNum) override
		{
			return 0.0;
		}

		virtual void VCOM_CALLTYPE AlertSetAlwaysDoValue(const TXString& category, const TXString& item, short value) override
		{
	
		}

		virtual int	 VCOM_CALLTYPE GetCSGAction(MCObjectHandle hCSG) override
		{
			return 0;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateRenderBackground(BackgroundType backgroundType) override
		{
				return NULL;
		}

		virtual bool VCOM_CALLTYPE ExportResourceN(MCObjectHandle resource, IFileIdentifier* pFileID, TImportResourceConflictCallbackProcPtr conflictCallback) override
		{
			return false;
		}

	// VW2013
	public:
		virtual void VCOM_CALLTYPE CustomBatchConvert(ICustomBatchConvertParams* params) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetAllObjectNames(TXStringArray& names) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetAllLayerNames(TXStringArray& names) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetListBoxTabStops( Sint32 dialogID, Sint32 componentID, int numTabStops, int* tabStops ) override
		{
	
		}
		virtual void VCOM_CALLTYPE SupportCustomControlKeyEvents( Sint32 dialogID, Sint32 componentID) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextJustificationN( MCObjectHandle textBlock, short justification) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextVerticalAlignmentN( MCObjectHandle textBlock, short verticalAlignment) override
		{
	
		}
		virtual TXString		VCOM_CALLTYPE GetLayerLevelTypeName(short index) override
		{
			return "error";
		}
		virtual bool VCOM_CALLTYPE SetLayerLevelTypeName(short index, const TXString& name) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetStoryLayerTemplateName(short index, const TXString& name) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetUserOriginGlobal(WorldPt& outOrigin) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateSolid(MCObjectHandle blank, const TVWArray_MCObjectHandle &toolList, bool add, MCObjectHandle& newSolid) override
		{
			return false;
		}
		virtual TXString VCOM_CALLTYPE GetVectorworksSessionID() override
		{
			return "error";
		}
		virtual void VCOM_CALLTYPE EnableListBrowserHierarchicalDisplay(Sint32 dialogID, Sint32 componentID, Boolean enableHierarchicalDisplay) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetListBrowserHierarchicalDisplayColumn(Sint32 dialogID, Sint32 componentID, short columnID) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserNumericItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, double itemVal, short imageIndex) override
		{
			return false;
		}

		virtual TXString		VCOM_CALLTYPE MilsToString(Sint32 value, EThicknessUnitsType unitType) override
		{
			return "error";
		}
		virtual Boolean VCOM_CALLTYPE StringToMils(const TXString& str, EThicknessUnitsType unitType, Sint32& outValue) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE StringToArea(const TXString& str, double& outArea) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE StringToVolume(const TXString& str, double& outVolume) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE IsListBrowserDisplayHierarchical(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE HierarchicalListBrowserItemOpened(Sint32 dialogID, Sint32 componentID, short itemIndex, Boolean recursive, short& outNumbRedisplayedItems) override
		{
	
		}
		virtual void VCOM_CALLTYPE HierarchicalListBrowserItemClosed(Sint32 dialogID, Sint32 componentID, short itemIndex, Boolean recursive) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE HierarchicalListBrowserItemIsClosed(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE HierarchicalListBrowserItemIsContainer(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetDisplayedItemsCountInHierarchicalContainer(Sint32 dialogID, Sint32 componentID, short itemIndex, short& outDisplayedItemsCount) override
		{

		}
		virtual TXString		VCOM_CALLTYPE GetListBrowserItemOriginalName(Sint32 dialogID, Sint32 componentID, short itemIndex) override
		{
			return "error";
		}
		virtual void VCOM_CALLTYPE AddListBrowserOriginalName(Sint32 dialogID, Sint32 componentID, const TXString& originalName) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetListBrowserOriginalNameCloseLevels(Sint32 dialogID, Sint32 componentID, const TXString& originalName, Boolean& outLeve1Closed, Boolean& outLevel2Closed, Boolean& outLevel3Closed) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetListBrowserOriginalNameCloseLevels(Sint32 dialogID, Sint32 componentID, const TXString& originalName, Boolean level1Closed, Boolean level2Closed, Boolean level3Closed) override
		{
	
		}
		virtual void VCOM_CALLTYPE CollapseAllListBrowserItems(Sint32 dialogID, Sint32 componentID) override
		{
	
		}
		virtual void VCOM_CALLTYPE ExpandAllListBrowserItems(Sint32 dialogID, Sint32 componentID) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateStyledStaticText(Sint32 dialogID, Sint32 componentID, const TXString & strText, short widthInStdChar, EStaticTextType enumType) override
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE SetModeBarButtonsText( const TVWModeBarButtonHelpArray& arrModeBarButtonsHelp ) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetToolHelpMessage( const TXString& modeText, const TXString& descriptionText ) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetToolHelpMessageAndTitle( const TXString& titleText, const TXString& modeText, const TXString& descriptionText ) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE FindWallsSurroundingPoint(MCObjectHandle inBoundedObject, const WorldPt& inPoint, short inColumnsAndPilastersEnum,
																		 MCObjectHandle inListOfObjects, bool ignoreClassVisibility, bool bExcludePiosNiches) override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE GetNumAssociations(MCObjectHandle handle) override
		{
			return 0;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetAssociation(MCObjectHandle handle, short index, Sint16& associationKind, Sint16& value) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE AdjustPathForWrapping(TXString& path, short maxWidth) override
		{
	
		}

		virtual void VCOM_CALLTYPE DoBatchPrintOrExport(short inBatchOperationType) override
		{
	
		}

		virtual void  VCOM_CALLTYPE DeleteObjectNoNotify(MCObjectHandle h) override
		{
	
		}

		virtual void VCOM_CALLTYPE EditObjectSpecial(MCObjectHandle h, TObjSpecialEdit editMode) override
		{
	
		}

		virtual short VCOM_CALLTYPE GetNumSavedViews() override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE GetSavedView(short index, TXString& view) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RestoreSavedView(const TXString& savedView) override
		{
	
		}

		virtual bool VCOM_CALLTYPE CreateCustomThumbnailPopup(Sint32 dialogID, Sint32 controlID, ThumbnailSizeType sizeKind) override
		{
			return false;
		}
		virtual InternalIndex	VCOM_CALLTYPE GetClPenPatN(InternalIndex classIndex) override
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetClPenPatN(InternalIndex classIndex, InternalIndex penPat) override
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetDefaultPenPatN() override
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetDefaultPenPatN(InternalIndex penPat) override
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetPenPatN(MCObjectHandle h) override
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetPenPatN(MCObjectHandle h, InternalIndex penPat) override
		{
	
		}

		virtual void VCOM_CALLTYPE GetLineTypeAttributeData(Sint32 dialogID, Sint32 itemID, InternalIndex& lineStyle, short& lineWeight) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetLineTypeAttributeData(Sint32 dialogID, Sint32 itemID, InternalIndex lineStyle, short lineWeight) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetLineTypeChoice(Sint32 dialogID, Sint32 itemID, Sint32& lineTypeRefNumber) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetLineTypeChoice(Sint32 dialogID, Sint32 itemID, Sint32 lineTypeRefNumber) override
		{
	
		}
		virtual void VCOM_CALLTYPE ShowComplexLineTypesInLineAttributePopup(Sint32 dialogID, Sint32 itemID) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemLineTypeRef(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 &iLineRef, int &iLineWeight) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemLineTypeRef(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 iStyleIndex, int iLineWeight) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE IsWorksheetCellImage (MCObjectHandle worksheet, short row, short column, short subrow) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageType (MCObjectHandle worksheet, short row, short column, short& type) override
		{
	
		}
		virtual short VCOM_CALLTYPE GetWorksheetCellImageSizeType (MCObjectHandle worksheet, short row, short column) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageSize (MCObjectHandle worksheet, short row, short column, short& height, short& width) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageAngle (MCObjectHandle worksheet, short row, short column, double& angle) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageView (MCObjectHandle worksheet, short row, short column, short& view) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageComponent(MCObjectHandle worksheet, short row, short column, EImageViewComponent& outComponent) override
		{

		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageRenderMode (MCObjectHandle worksheet, short row, short column, short& renderMode) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetWorksheetCellImageUseLayerScale (MCObjectHandle worksheet, short row, short column) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageScale (MCObjectHandle worksheet, short row, short column, double& scale) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetWorksheetCellImageUseObjectImage (MCObjectHandle worksheet, short row, short column) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageMarginSize (MCObjectHandle worksheet, short row, short column, unsigned char& marginSize) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageType (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short type) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageSizeType (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short imageSizeType) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageSize (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short height, short width) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageAngle (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, double angle) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageView (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short view) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageComponent(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, EImageViewComponent component) override
		{

		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageRenderMode (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short renderMode) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageUseLayerScale (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean useLayerScale) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageScale (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, double scale) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageUseObjectImage (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean useObjectImage) override
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageMarginSize (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, unsigned char marginSize) override
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE DoPolylineRadiusSmoothing(MCObjectHandle hPoly) override
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE SetImageControlDataN(Sint32 dialogID, Sint32 componentID, VectorWorks::UI::IIcon* icon) override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE AssociateBoundedObjectWithWalls(MCObjectHandle inBoundedObject, TVWArray_MCObjectHandle& wallList, short inColumnsAndPilastersEnum, bool bExcludePiosNiches) override
		{
				return NULL;
		}

		virtual Sint32 VCOM_CALLTYPE BuildResourceListN(short objectType, IFileIdentifier* fileID, Sint32& numItems) override
		{
			return 0;
		}

		virtual Boolean VCOM_CALLTYPE TrimNurbsSurface(MCObjectHandle iNurbsSurface, MCObjectHandle iNurbsCurve) override
		{
			return false;
		}

		virtual void VCOM_CALLTYPE InteractiveViewOperation_Begin(EInteractiveMode type, const ViewPt& viewPt) override
		{
	
		}
		virtual void VCOM_CALLTYPE InteractiveViewOperation_End() override
		{
	
		}
		virtual void VCOM_CALLTYPE InteractiveViewOperation_Move(const ViewPt& viewPt) override
		{
	
		}

		virtual Boolean VCOM_CALLTYPE SetToolByName(const TXString& toolUnivName) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetToolByName(const TXString& toolUnivName, size_t modebarGroupID, size_t modebarButtonID) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetToolByIndex(short index) override
		{
	
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateLayerWithUI(TXString& name) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE EditLayerWithUI(MCObjectHandle layer) override
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE CreateSavedViewWithUI(TXString& outName) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE EditSavedViewWithUI(TXString& inOutName) override
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateExtrudeAlongPath2(MCObjectHandle pathHandle, MCObjectHandle profileHandle, Boolean bExponentialScale, double scale, Boolean bLockProfilePlane, Boolean bFixProfile) override
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE SectionSolid(MCObjectHandle obj1, MCObjectHandle obj2, Boolean useSectionColor, Boolean flipSection, MCObjectHandle& newSolid) override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE IsGBXMLExportAllowed() override
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertToGenericSolid(MCObjectHandle objectHandle ) override
		{
				return NULL;
		}

		virtual void VCOM_CALLTYPE AddWallToContainer(MCObjectHandle wallHandle, MCObjectHandle container) override
		{
	
		}
		virtual void VCOM_CALLTYPE SyncMatrixToStoryBound(MCObjectHandle h, TObjectBoundID id) override
		{
	
		}
		virtual void            VCOM_CALLTYPE SplitPolylineByMultiple2DLoci(MCObjectHandle h, TVWArray_WorldPt loci, bool killOriginal, bool insert, TVWArray_MCObjectHandle & arrayHandle) override
		{
	
		}

		virtual bool VCOM_CALLTYPE ExportDocumentPreviewImageFile(IFileIdentifier* pFileID, Sint32 compressionType) override
		{
			return false;
		}

		virtual void VCOM_CALLTYPE DeleteAssociations(MCObjectHandle h, Sint16 associationKind) override
		{
	
		}
		virtual MCObjectHandle  VCOM_CALLTYPE CreateTaperedExtrude2(MCObjectHandle profileH, const double_param angle, const double_param height) override
		{
				return NULL;
		}

	// VW 2014
	public:
		virtual Boolean VCOM_CALLTYPE EnableTreeControlDragAndDrop(Sint32 dialogID, Sint32 componentID, Boolean bEnable) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE EnableDragBetweenControls( Sint32 dialogID, Sint32 source, Sint32 destination ) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlItemParent( Sint32 dialogID, Sint32 componentID, Sint32 itemID, Sint32 & parentID ) override
		{
			return false;
		}
		virtual int	 VCOM_CALLTYPE CopyTreeControlSubtree( Sint32 dialogID, Sint32 sourceTree, Sint32 targetTree, Sint32 sourceItem, Sint32 destinationItem, Sint32 destinationItemParent ) override
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemImage( Sint32 dialogID, Sint32 componentID, Sint32 itemID, const TXString & imageSpecifier ) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemImageFromIcon( Sint32 dialogID, Sint32 componentID, Sint32 itemID, VectorWorks::UI::IIcon* icon ) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE TrimToSelectedObjectsN(MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2, const Boolean bTrimToSelectedObjects) override
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateComplexLineType(const TXString& name) override
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetComplexLineTypeGeometryGroup (MCObjectHandle lineTypeH) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE AddComplexLineTypeGeometryObject(MCObjectHandle lineTypeH, MCObjectHandle objectH) override
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE GetComplexLineTypeGroupParent(MCObjectHandle groupH) override
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE IsComplexLineTypeGroupContainedObject(MCObjectHandle objectH) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetComplexLineTypePageSpace(MCObjectHandle lineTypeH, Boolean isPageSpace) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE IsComplexLineTypeInPageSpace(MCObjectHandle lineTypeH) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetComplexLineTypeGapSize(MCObjectHandle lineTypeH, const WorldCoord newGapSize) override
		{
			return false;
		}
		virtual WorldCoord		VCOM_CALLTYPE GetComplexLineTypeGapSize(MCObjectHandle lineTypeH) override
		{
			return 0.0;
		}
		virtual Sint32 VCOM_CALLTYPE CreateLayoutDialogFromVWResource(const char* resIdentifier) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE RemoveAllTreeControlItems( Sint32 dialogID, Sint32 componentID ) override
		{
	
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateGroupOutline( MCObjectHandle objectHandle ) override
		{
				return NULL;
		}

		virtual void VCOM_CALLTYPE SetViewMatrixByVector(const WorldPt3& lookFrom, const WorldPt3& lookTo, const WorldPt3& upVector, TransformMatrix& outMatrix, MCObjectHandle activeViewport) override
		{
	
		}

		virtual bool VCOM_CALLTYPE IsCurtainWall( MCObjectHandle hWall ) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetCurtainWallPanelInfo( MCObjectHandle hWall, const WorldPt&  inCenterPt, bool includeBottomFrame, WorldPt & outCenterPt, WorldCoord & outWidth, WorldCoord & outHeight ) override
		{
			return false;
		}

		virtual short VCOM_CALLTYPE GetNumberOfLineTypesItems(Sint32 dialogID, Sint32 itemID) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetLineTypeAtIndex(Sint32 dialogID, Sint32 itemID, short index, InternalIndex& outLineTypeRefNumber) override
		{
	
		}
		virtual bool VCOM_CALLTYPE GetSimpleLineTypeData(MCObjectHandle lineTypeH, bool& outScaleWithThick, std::vector<double>& outData) override
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE Create2DObjectShadow(MCObjectHandle h2DObject, const WorldPt & offsetPt) override
		{
				return NULL;
		}

	// VW 2015
	public:
		virtual void VCOM_CALLTYPE GetListOfWorkingPlanes( TVWArray_MCObjectHandle& planesList ) override
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetWorkingPlaneInfo( MCObjectHandle planeH, TXString& outName, Axis& outAxis ) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWorkingPlaneInfo( MCObjectHandle planeH, const TXString & name, const Axis axis ) override
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE DuplicateWorkingPlane( MCObjectHandle planeH ) override
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteWorkingPlane( MCObjectHandle planeH ) override
		{
	
		}

		virtual void VCOM_CALLTYPE SetTreeControlItemAsDivider(Sint32 dialogID, Sint32 componentID, Sint32 itemID, bool isDivider) override
		{
	
		}

		virtual void VCOM_CALLTYPE SysBeep(short duration) override
		{
	
		}

		virtual Boolean VCOM_CALLTYPE  GetToolPtCurrentIsSnapped() override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  Project3DModelPtToScreen(const WorldPt3& inwpt3Model, WorldPt& outwptScreen) override
		{
			return false;
		}

		virtual MCObjectHandle VCOM_CALLTYPE  GetImageCropObject(MCObjectHandle object) override
		{
			return NULL;
		}
		virtual bool VCOM_CALLTYPE  IsImageCropped(MCObjectHandle object) override
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE  IsImageCropVisible(MCObjectHandle object) override
		{
			return false;
		}
		virtual void VCOM_CALLTYPE  SetImageCropVisible(MCObjectHandle object, bool isVisible) override
		{

		}
		virtual bool VCOM_CALLTYPE  SetImageCropObject(MCObjectHandle imageObject, MCObjectHandle cropObject) override
		{
			return false;
		}

		virtual void VCOM_CALLTYPE  TransformGraphicObject(MCObjectHandle object, TransformMatrix& inMatrix) override
		{
	
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportClassOverrides(MCObjectHandle viewportHandle) override
		{
			return 0;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportClassOverrideClass(MCObjectHandle viewportHandle, size_t index) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  CreateViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex, SViewportClassOverride& outOverride) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex, const SViewportClassOverride& inOverride) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex) override
		{
			return false;
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportLightOverrides(MCObjectHandle viewportHandle) override
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportLightOverrideLight(MCObjectHandle viewportHandle, size_t index) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  CreateViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex, SViewportLightOverride& outOverride) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex, const SViewportLightOverride& inOverride) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex) override
		{
			return false;
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportLayerOverrides(MCObjectHandle viewportHandle) override
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportLayerOverrideLayer(MCObjectHandle viewportHandle, size_t index) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  CreateViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, SViewportLayerOverride& outOverride) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const SViewportLayerOverride& inOverride) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) override
		{
			return false;
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportLayerPropertiesOverrides(MCObjectHandle viewportHandle) override
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportLayerPropertiesOverrideLayer(MCObjectHandle viewportHandle, size_t index) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  CreateViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, SViewportLayerPropertiesOverride& outOverride) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const SViewportLayerPropertiesOverride& inOverride) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) override
		{
			return false;
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportLayerStackingOverrides(MCObjectHandle viewportHandle) override
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportLayerStackingOverrideLayer(MCObjectHandle viewportHandle, size_t index) override
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, Sint32& outStackingPosition) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const Sint32& inStackingPosition) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE  IsDesignLayerViewport(MCObjectHandle hObj) override
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE  DeleteSavedSetting(const TXString& category) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  DeleteSavedSetting(const TXString& category, const TXString& setting) override
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE  TrackToolViewport(Boolean trackDLVP) override
		{
			return NULL;
		}

		virtual void VCOM_CALLTYPE  ForEachObjectInList(MCObjectHandle hFirst, GS_ForEachObjectProcPtr action, void *actionEnv) override
		{
	
		}

		virtual OpacityRef VCOM_CALLTYPE  GetClOpacity(InternalIndex classIndex) override
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE  SetCLOpacity(InternalIndex classIndex, OpacityRef opacity) override
		{
	
		}
		virtual TPlanarRefID VCOM_CALLTYPE  GetWorkingPlanePlanarRefID( ) override
		{
			return 0;
		}

		virtual Boolean VCOM_CALLTYPE  CreateScriptResource(const TXString& scriptName, const TXString& paletteName, bool paletteOpen, const TXString& script, bool python) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetScriptResource(const TXString& scriptName, TXString& outScript, bool& outPython) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetScriptResource(const TXString& scriptName, const TXString& script, bool python) override
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  OpenScriptResPalette(const TXString& paletteName, bool paletteOpen) override
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallHoleGroupDeep(MCObjectHandle h) override
		{
			return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE CreateTextStyleResource(const TXString &name) override
		{
			return NULL;
		}
		virtual Uint32 VCOM_CALLTYPE TickCount() override
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE IsFontAvailable(short fontID) override
		{
			return true;
		}
		virtual void VCOM_CALLTYPE ResetVisibilityForSymbol(MCObjectHandle symDef) override
		{
	
		}
		virtual void VCOM_CALLTYPE GetStandardFontList (TXStringArray& fontList) override
		{
	
		}
		virtual bool VCOM_CALLTYPE CanSymbolBeAddedLegal(MCObjectHandle container, MCObjectHandle symDef) override
		{
			return true;
		}
		virtual MCObjectHandle CreateMesh() override
		{
			return NULL;
		}
		virtual MCObjectHandle CreateMesh(IMeshData** outMeshData) override
		{
			return NULL;
		}
		virtual bool GetMesh(MCObjectHandle hMesh, IMeshData** outMeshData) override
		{
			return false;
		}
		virtual MCObjectHandle AddMeshFace(MCObjectHandle hMesh, const TVWArray_SizeT& arrVertexIndices) override
		{
			return NULL;
		}
		virtual bool GetPointInsidePoly(MCObjectHandle poly, WorldPt &insideWorldPt) override
		{
			return false;
		}

		// Opacity for Gradients added in VW2015
		virtual bool GetGradientDataN(MCObjectHandle gradient, Sint16 segmentIndex, Real64& spotPosition, Real64& midpointPosition, WorldPt3& color, OpacityRef& opacity) override
		{
			return false;
		}

		virtual bool GetGradientSliderDataN(Sint32 dialogID, Sint32 componentID, Sint16 segmentIndex, Real64& spotPosition, Real64& midpointPosition, WorldPt3& color, OpacityRef& opacity) override
		{
			return false;
		}

		virtual bool GetGradientSpotOpacity(MCObjectHandle gradient, Sint16 segmentIndex, OpacityRef& opacity) override
		{
			return false;
		}

		virtual Sint16 InsertGradientSegmentN(MCObjectHandle gradient, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity) override
		{
			return 0;
		}

		virtual Sint16 InsertGradientSliderSegmentN(Sint32 dialogID, Sint32 componentID, Real64 spotPosition, const WorldPt3& color, const OpacityRef& opacity) override
		{
			return 0;
		}

		virtual bool SetGradientDataN(MCObjectHandle gradient, Sint16& segmentIndex, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity) override
		{
			return false;
		}

		virtual bool SetGradientSliderDataN(Sint32 dialogID, Sint32 componentID, Sint16& segmentIndex, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity) override
		{
			return false;
		}

		virtual bool SetGradientSpotOpacity(MCObjectHandle gradient, Sint16 segmentIndex, const OpacityRef& opacity) override
		{
			return false;
		}

		virtual size_t GetTreeControlItemNumberOfChildren(Sint32 dialogID, Sint32 componentID, Sint32 itemID) override
		{
			return 0;
		}

		virtual Sint32 GetTreeControlItemChildID(Sint32 dialogID, Sint32 componentID, Sint32 parentID, Sint32 index) override
		{
			return 0;
		}

		virtual short GetStandardFontListSize() override
		{
			return 0;
		}

		virtual MCObjectHandle GetVerticesFromSolid(MCObjectHandle handle) override
		{
			return NULL;
		}

		virtual MCObjectHandle GetNurbsCurvesFromSolid(MCObjectHandle handle) override
		{
			return NULL;
		}

		virtual MCObjectHandle GetNurbsSurfacesFromSolid(MCObjectHandle handle) override
		{
			return NULL;
		}

		virtual MCObjectHandle GetNurbsCurvesOnCuttingPlane(MCObjectHandle handle, const WorldPt3& pointOnPlane, const WorldPt3& planeNormal) override
		{
			return NULL;
		}

		virtual Boolean	CustomObjectControlPtGet(MCObjectHandle inOwnerObj, Sint32 dataIndex, WorldPt3& outPt, Boolean* outIs2DOnly, Boolean* outIsHidden, Sint32* outClientID) override
		{
			return false;
		}

		virtual MCObjectHandle	CreateImageMaskFromAlphaChannel(MCObjectHandle inImage, bool useAlpha) override
		{
			return NULL;
		}

		virtual void SetTreeControlItemSelectionState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, bool select) override
		{
		}

		virtual MCObjectHandle VCOM_CALLTYPE ConvertPolylineToPolylineWithOnlyArcVertices(MCObjectHandle handle, bool insert) override
		{
			return NULL;
		}

		virtual bool VCOM_CALLTYPE GetTextStyleByClass(MCObjectHandle handle) override
		{
			return false;
		}

		virtual void VCOM_CALLTYPE SetTextStyleByClass(MCObjectHandle handle) override
		{
		}

		virtual bool VCOM_CALLTYPE GetClUseTextStyle(InternalIndex classId) override
		{
			return false;
		}

		virtual void VCOM_CALLTYPE SetClUseTextStyle(InternalIndex classId, bool use) override
		{
		}

		virtual InternalIndex VCOM_CALLTYPE GetClTextStyleRef(InternalIndex classId) override
		{
			return -1;
		}

		virtual void VCOM_CALLTYPE SetClTextStyleRef(InternalIndex classId, InternalIndex textStyleRef) override
		{
		}

		virtual bool VCOM_CALLTYPE SetTextStyleRefN(MCObjectHandle textBlock, short firstChar, short numChars, InternalIndex styleRef) override
		{
			return false;
		}

		virtual InternalIndex VCOM_CALLTYPE GetTextStyleRefN(MCObjectHandle h, short atChar) override
		{
			return -1;
		}

		virtual bool VCOM_CALLTYPE SetTextStyleByClassN(MCObjectHandle textBlock, short firstChar, short numChars) override
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE GetTextStyleByClassN(MCObjectHandle h, short atChar) override
		{
			return false;
		}

		virtual bool GetTextTabStopCount(MCObjectHandle textBlock, Sint32& count) override
		{
			return false;
		}

		virtual bool GetTextTabStopLocation(MCObjectHandle textBlock, Sint32 index, WorldCoord& location) override
		{
			return false;
		}

		virtual bool MoveTextTabStopLocation(MCObjectHandle textBlock, Sint32 index, WorldCoord location) override
		{
			return false;
		}

		virtual bool AddTextTabStop(MCObjectHandle textBlock, WorldCoord location) override
		{
			return false;
		}
		
		virtual bool RemoveTextTabStop(MCObjectHandle textBlock, Sint32 index) override
		{
			return false;
		}

		virtual bool GetTextTrackingValue(MCObjectHandle textBlock, Sint32 index, float& trackingValue) override
		{
			return false;
		}

		virtual bool SetTextTrackingValue(MCObjectHandle textBlock, Sint32 index, Sint32 numChars, float trackingValue) override
		{
			return false;
		}

		virtual bool GetObjectWallOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord& offset) override
		{
			return false;
		}

		virtual bool SetObjectWallHeight(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord height) override
		{
			return false;
		}

		virtual bool GetObjectWallHeight(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord& height) override
		{
			return false;
		}

		virtual void SetHatchReferenceForMaterialNode(MCObjectHandle inMaterial, RefNumber inHatchReference) override
		{
		}

		virtual void ClearHatchReferenceForMaterialNode(MCObjectHandle inMaterial) override
		{
		}

		virtual RefNumber GetHatchReferenceForMaterialNode(MCObjectHandle inMaterial) override
		{
			return 0;
		}

		virtual TXString GetDescriptionText(MCObjectHandle hObj) override
		{
			TXString descriptionText;
			return descriptionText;
		}

		virtual bool SetDescriptionText(MCObjectHandle hObj, const TXString& inText) override
		{
			return false;
		}

		virtual void RefreshModeBar() override
		{
		}

		virtual void ClearClearPullDownMenu(short group) override
		{
		}

		virtual Boolean RefreshClassPopup(Sint32 dialogID, Sint32 componentID) override
		{
			return false;
		}


		virtual short GetListBrowserHierarchicalDisplayColumn(Sint32 dialogID, Sint32 componentID) override
		{
			return 0;
		}


		virtual MCObjectHandle	VCOM_CALLTYPE GetPDFPageCropObject(MCObjectHandle object) override
		{

			MCObjectHandle	hResult		= NULL;

			return hResult;
		}


		virtual bool VCOM_CALLTYPE IsPDFPageCropped(MCObjectHandle object) override
		{
	
			return false;
		}


		virtual bool VCOM_CALLTYPE IsPDFPageCropVisible(MCObjectHandle object) override
		{

			return false;
		}


		virtual void VCOM_CALLTYPE SetPDFPageCropVisible(MCObjectHandle object, bool isVisible) override
		{
	
		}


		virtual bool VCOM_CALLTYPE SetPDFPageCropObject(MCObjectHandle pdfPageObject, MCObjectHandle cropObject) override
		{

			return false;
		}


		virtual bool VCOM_CALLTYPE SetPDFPageWidthAndHeight(MCObjectHandle hObject, WorldCoord newWidth, WorldCoord newHeight) override
		{

			return false;
		}

		virtual void SetPerspectiveInfo(short projKind, short renderMode, WorldCoord persDistance, const WorldPt &pt1, const WorldPt &pt2) override
		{
		}

		virtual void SetCurrentView(TStandardView view, bool direct) override
		{
		}

		virtual void CreateSymbolFolderN(const TXString& folderPath, TVWArray_MCObjectHandle & outFolderPath) override
		{
	
		}

		virtual bool IsCurrentlyBuildingAnUndoEvent() override
		{
			return false;
		}

		virtual bool ShowCustomDimensionStandardsDialog() override
		{
			return false;
		}


		virtual short GetNumStoryLevelTemplates() override
		{
			return 0;
		}

		virtual TXString GetStoryLevelTemplateName(short index) override
		{
			return TXString();
		}

		virtual bool SetStoryLevelTemplateName(short index, const TXString& name) override
		{
			return false;
		}

		virtual bool CreateStoryLevelTemplate(TXString& layerName, double scaleFactor, TXString& layerLevelType, WorldCoord elevationOffset, WorldCoord defaultWallHeight, short& index) override
		{
			return false;
		}

		virtual bool DeleteStoryLevelTemplate(short index) override
		{
			return false;
		}

		virtual bool GetStoryLevelTemplateInfo(short index, TXString& layerName, double& scaleFactor, TXString& levelType, double& elevation, double& defaultWallHeight) override
		{
			return false;
		}

		virtual bool AddStoryLevel(MCObjectHandle storyHandle, const TXString& levelType, WorldCoord elevation, const TXString& layerName) override
		{
			return false;
		}

		virtual bool AddStoryLevelFromTemplate(MCObjectHandle storyHandle, short index) override
		{
			return false;
		}

		virtual bool RemoveStoryLevel(MCObjectHandle storyHandle, const TXString& levelType, bool bDeleteLayer) override
		{
			return false;
		}

		virtual bool SetStoryLevelElevation(MCObjectHandle storyHandle, const TXString& levelType, WorldCoord newElevation) override
		{
			return false;
		}

		virtual WorldCoord GetStoryLevelElevation(MCObjectHandle storyHandle, const TXString& levelType) override
		{
			return 0.0;
		}

		virtual bool ResetDefaultStoryLevels(bool bDeleteExisting) override
		{
			return false;
		}

		virtual MCObjectHandle TrackToolInViewportAnnotatons(MCObjectHandle &proxyObj, Boolean &worldObjInVP, bool createProxy) override
		{
			return nil;
		}
		virtual Boolean GetComponentTopIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean &topIsRelativeToStory) override
		{
			return false;
		}
		virtual Boolean SetComponentTopIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean topIsRelativeToStory) override
		{
			return false;
		}
		virtual Boolean GetComponentBottomIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean &bottomIsRelativeToStory) override
		{
			return false;
		}
		virtual Boolean SetComponentBottomIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean bottomIsRelativeToStory) override
		{
			return false;
		}
		virtual void ShowListBrowserHeader(Sint32 dialogID, Sint32 componentID, bool show) override
		{
			return;
		}

		virtual Boolean GetListBrowserNumericItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString& itemString, double& itemVal, short& imageIndex) override
		{
			return false;
		}

		virtual bool GetCurtainWallPanelInfoExtended( MCObjectHandle hWall, const WorldPt & inCenterPt, bool includeBottomFrame, WorldPt & outCenterPt, WorldCoord & outWidth, WorldCoord & outHeight, 
										WorldCoord& panelThickness, WorldCoord& panelOffset,  WorldCoord& frameInsetTop,  WorldCoord& frameInsetBottom,  WorldCoord& frameInsetRight, WorldCoord& frameInsetLeft) override
		{
			return false;
		}
		virtual MCObjectHandle GetOtherObjectFromBinaryConstraint(CBSignedShort type, MCObjectHandle obj, CBSignedShort objVertexA, CBSignedShort objVertexB, InternalIndex containedObj, MCObjectHandle& outContraint) override
		{
			return NULL;
		}

		virtual MCObjectHandle FindBinbaryConstraintToObject(CBSignedShort type, MCObjectHandle obj, MCObjectHandle toObject, CBSignedShort& outToObjectVertexA, CBSignedShort& outToObjectVertexB, InternalIndex& outToObjectContainedObj) override
		{
			return NULL;
		}

		virtual void Trim2DObjectWithLine(MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, bool insert, TVWArray_MCObjectHandle & hResultArray) override
		{
			return;
		}

		virtual void ForEach3DPointInObjectN(MCObjectHandle h, std::function<bool(const WorldPt3& point3D)> callbackLambda) override
		{
		}

		virtual void ForEachPolyEdgeN( MCObjectHandle inPolyH, std::function<void(const SPolyEdge& edge)> callbackLambda) override
		{
		}

		virtual void ForEachLayerN( std::function<void(MCObjectHandle h)> callbackLambda) override
		{
		}

		virtual void ForEachObjectN( short traverseWhat, std::function<void(MCObjectHandle h)> callbackLambda) override
		{
		}

		virtual void ForEachBreakN( MCObjectHandle theWall, std::function<bool(MCObjectHandle h, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData)> callbackLambda) override
		{
		}

		virtual EForEachFileResult ForEachFileInStandardFolderN(EFolderSpecifier folderSpec, std::function<bool(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda) override
		{
			return kStopForEachFile_NoError;
		}

		virtual EForEachFileResult ForEachFilePathInStandardFolderN(FolderSpecifier folderSpec, std::function<bool(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda) override
		{
			return kStopForEachFile_NoError;
		}

		virtual EForEachFileResult ForEachFilePathInFolderN(IFolderIdentifier* pStartFolderID, bool doRecursive, std::function<EForEachFileResult(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda) override
		{
			return kStopForEachFile_NoError;
		}

		virtual EForEachFileResult ForEachFilePathInPluginFolderN(std::function<EForEachFileResult(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda) override
		{
			return kStopForEachFile_NoError;
		}

		virtual void ForEachObjectInListN(MCObjectHandle hFirst, std::function<void(MCObjectHandle h)> callbackLambda) override
		{
		}

		virtual Sint32 SendActiveToolMessage(ToolMessage& message) override
		{
			return 0;
		}

		virtual void AddPullDownResourceMethod(const TXString& label, const TXString& value) override
		{
		}

		virtual void SetPullDownResourceValue(short group, const TXString& value) override
		{
		}

		virtual Sint32 ShowPullDownResourcePopup(short group, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize) override
		{
			return 0;
		}

		virtual void SetImagePopupResourceAdvanced(Sint32 dialogID, Sint32 componentID) override
		{
		}

		virtual void SetImagePopupResourceCategories(Sint32 dialogID, Sint32 componentID, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex) override
		{
		}

		virtual bool GetClassSharedAndUpdateReference (MCObjectHandle hDLVPort, InternalIndex classIndex, bool& outSharedRef, bool& outUpdateRef) override
		{
			return false;
		}
		virtual bool SetObjectAsSpanWallBreak(MCObjectHandle objectHandle, MCObjectHandle wallHandle, bool spanWallBreak) override
		{
			return false;
		}

		virtual bool GetTreeControlItemCheckBoxState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, Sint32& outState) override
		{
			return false;
		}

		virtual bool SetTreeControlItemCheckBoxState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, Sint32 state) override
		{
			return false;
		}
		virtual OSType VCOM_CALLTYPE GetDataMapDataClientID(MCObjectHandle h) override
		{
			return 0;
		}

		virtual MCObjectHandle CreateShellSolid(MCObjectHandle surface, double thickness) override
		{
			return 0;
		}

		virtual bool CreateSlabModifier(MCObjectHandle slab, MCObjectHandle profile, bool isSubtract, Sint16 componentID, bool clipToBoundary) override
		{
			return false;
		}

		virtual bool ExportImage(IFileIdentifier* fileID, const SExportImageOptions& options) override
		{
			return false;
		}

		virtual bool ExportSTL(IFileIdentifier* fileID, bool exportBinary, double percentTess, Sint16 exportObjectsOptions) override
		{
			return false;
		}

		virtual bool ExportSTEP(IFileIdentifier* fileID, bool exportSolidAsSurface) override
		{
			return false;
		}

		virtual void ForEachClass( Boolean doGuestClasses, std::function<void(MCObjectHandle h)> callbackLambda) override
		{
		}

		virtual void GetParentFolderNameFromResourceList(Sint32 listID, Sint32 index, TXString& name) override
		{
		}

		virtual bool ExportSymbolResource(MCObjectHandle symbolresource, const TXString& symbolFolderDestName, IFileIdentifier* pFileID, bool suppressDialogs, TImportResourceConflictCallbackProcPtr conflictCallback) override
		{
			return false;
		}

		virtual InternalIndex GetRoofStyle(MCObjectHandle roof) override
		{
			return -1;
		}

		virtual void SetRoofStyle(MCObjectHandle roof, InternalIndex roofStyle) override
		{
    
		}

		virtual void ConvertToUnstyledRoof(MCObjectHandle roof) override
		{
    
		}

		virtual InternalIndex GetRoofPreferencesStyle() override
		{
			return -1;
		}

		virtual void SetRoofPreferencesStyle(InternalIndex roofStyle) override
		{
    
		}

		virtual MCObjectHandle CreateRoofStyle(const TXString &roofStyleName) override
		{
			return NULL;
		}

		virtual MCObjectHandle GetRoofPreferences() override
		{
			return NULL;
		}

		virtual short GetDatumRoofComponent(MCObjectHandle object) override
		{
			return 0;
		}

		virtual void SetDatumRoofComponent(MCObjectHandle object, short componentIndex) override
		{
    
		}

		virtual bool ExportDocument(IFileIdentifier* fileID, short version) override
		{
			return false;
		}

		virtual Sint32	BuildResourceListFromOpenFile(const short objectType, const size_t fileRef, Sint32& numItems) override
		{
			return 0;
		}

		virtual void   GetOpenFilesList (TVWArray_OpenFileInformation& outInformation) override
		{
		}

		virtual void   GetFavoritesList (TVWArray_IFileIdentifierPtr& outFavorites) override
		{
		}

		virtual bool   SwitchToOpenFile (Sint32 fileRef) override
		{
			return true;
		}

		virtual bool   TranslateToCurrentVersion (IFileIdentifier* pSrcFileID, IFileIdentifier* pDstFileID) override
		{
			return true;
		}

		virtual void VCOM_CALLTYPE CalcRoofTopArea(MCObjectHandle object, double& outArea) override
		{
		}

		virtual void SwitchFromPlanTo3DView() override
		{
		}

		virtual void UngroupObject(MCObjectHandle object) override
		{
		}

		virtual MCObjectHandle ConvertToGroup(MCObjectHandle object, short convertAction) override
		{
			return 0;
		}

		virtual void ConvertObjectToLines(MCObjectHandle objectH, bool suspendDialog, ConvertModeEnum convertMode) override
		{
		}

		virtual void ConvertObjectToPolygons(MCObjectHandle objectH, bool suspendDialog, ConvertModeEnum convertMode) override
		{
		}

		virtual void SymbolToGroup(MCObjectHandle &theSymbol) override
		{
		}

		virtual void SymbolsInGroupToGroups(MCObjectHandle inObject) override
		{
		}

		virtual GSHandle ViewCreateCurrent() override
		{
			return NULL;
		}

		virtual void ViewDelete(GSHandle hView) override
		{
		}

		virtual GSHandle ViewDuplicate(GSHandle hView) override
		{
			return NULL;
		}

		virtual size_t ViewGetNumLayers(GSHandle hView) override
		{
			return 0;
		}

		virtual void ViewGetLayerVisibility(GSHandle hView, size_t index, InternalIndex& outName, short& outVisibility) override
		{
		}

		virtual size_t ViewGetNumClasses(GSHandle hView) override
		{
			return 0;
		}

		virtual void ViewGetClassVisibility(GSHandle hView, size_t index, InternalIndex& outClassID, short& outVisibility) override
		{
		}

		virtual void ViewStore(GSHandle hView) override
		{
		}

		virtual void ViewRestore(GSHandle hView) override
		{
		}

		virtual bool GetCheckoutsComment(TXString& comment) override
		{
			return false;
		}

		virtual bool SetCheckoutsComment(const TXString& comment) override
		{
			return false;
		}

		virtual bool GetCurrentUserId(TXString& userid) override
		{
			return false;
		}

		virtual bool GetProjectFullPath(TXString& outFilePath) override
		{
			return false;
		}

		virtual bool GetProjectName(TXString& outName) override {
			return false;
		}

		virtual bool GetWorkingFileId(TXString& uuid) override
		{
			return false;
		}

		virtual bool IsAWorkingFile() override
		{
			return false;
		}

		virtual bool IsProjectOffline() override
		{
			return false;
		}

		virtual bool GetProjectUserNames(TXStringArray& users) override
		{
			return false;
		}

		virtual bool GetProjectUser(const TXString & userId, TXStringMock fullName, EUserProjectPermission& permission) override
		{
			return false;
		}

		virtual bool GetLayerProjectInfo(MCObjectHandle layer, LayerProjectInfo& layerInfo) override
		{
			return false;
		}

		virtual MCObjectHandle GetCustomScreenFeedbackGroup(MCObjectHandle hObject) override
		{
			return NULL;
		}

		virtual bool SetCustomScreenFeedbackGroup(MCObjectHandle hObject, MCObjectHandle hFeedbackGroup) override
		{
			return false;
		}

		virtual bool GetViewFromAndToPoints(WorldPt3& fromPt, WorldPt3& toPt) override
		{
			return false;
		}
		virtual void UpdateBreak(MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData) override
		{
		}

		virtual Boolean GetComponentDatumIsTopOfComponent(MCObjectHandle object, short componentIndex, Boolean &datumIsTopOfComponent) override
		{
			return false;
		}

		virtual Boolean SetComponentDatumIsTopOfComponent(MCObjectHandle object, short componentIndex, Boolean datumIsTopOfComponent) override
		{
			return false;
		}

		virtual Boolean GetComponentWallAssociatedBound(MCObjectHandle object, short componentIndex, ERoofWallAssociatedBound &wallAssociatedBound) override
		{
			return false;
		}

		virtual Boolean SetComponentWallAssociatedBound(MCObjectHandle object, short componentIndex, ERoofWallAssociatedBound wallAssociatedBound) override
		{
			return false;
		}

		virtual Boolean GetComponentWallAssociatedSectionFillChangePoint(MCObjectHandle object, short componentIndex, ERoofChangePoint &wallAssociatedSectionFillChangePoint) override
		{
			return false;
		}

		virtual Boolean SetComponentWallAssociatedSectionFillChangePoint(MCObjectHandle object, short componentIndex, ERoofChangePoint wallAssociatedSectionFillChangePoint) override
		{
			return false;
		}

		virtual Boolean GetComponentWallAssociatedModification(MCObjectHandle object, short componentIndex, ERoofModification &wallAssociatedModification) override
		{
			return false;
		}

		virtual Boolean SetComponentWallAssociatedModification(MCObjectHandle object, short componentIndex, ERoofModification wallAssociatedModification) override
		{
			return false;
		}

		virtual Boolean GetComponentManualBound(MCObjectHandle object, short componentIndex, ERoofManualBound &manualBound) override
		{
			return false;
		}

		virtual Boolean SetComponentManualBound(MCObjectHandle object, short componentIndex, ERoofManualBound manualBound) override
		{
			return false;
		}

		virtual Boolean GetComponentBoundOffset(MCObjectHandle object, short componentIndex, WorldCoord &boundOffset) override
		{
			return false;
		}

		virtual Boolean SetComponentBoundOffset(MCObjectHandle object, short componentIndex, WorldCoord boundOffset) override
		{
			return false;
		}

		virtual Boolean GetComponentAlwaysAutoJoinInCappedJoinMode(MCObjectHandle object, short componentIndex, Boolean &alwaysAutoJoinInCappedJoinMode) override
		{
			return false;
		}

		virtual Boolean SetComponentAlwaysAutoJoinInCappedJoinMode(MCObjectHandle object, short componentIndex, Boolean alwaysAutoJoinInCappedJoinMode) override
		{
			return false;
		}

		virtual Boolean GetComponentAlternateSectionFill(MCObjectHandle object, short componentIndex, Sint32 &alternateSectionFill) override
		{
			return false;
		}

		virtual Boolean SetComponentAlternateSectionFill(MCObjectHandle object, short componentIndex, Sint32 alternateSectionFill) override
		{
			return false;
		}

		virtual Boolean GetComponentPenStylesN(MCObjectHandle object, short componentIndex, InternalIndex &leftPenStyle, InternalIndex &rightPenStyle) override
		{
			return false;
		}

		virtual Boolean SetComponentPenStylesN(MCObjectHandle object, short componentIndex, InternalIndex leftPenStyle, InternalIndex rightPenStyle) override
		{
			return false;
		}

		virtual Boolean GetComponentAlternateSectionFillColors(MCObjectHandle object, short componentIndex, ColorRef &alternateSectionFillForeColor, ColorRef &alternateSectionFillBackColor) override
		{
			return false;
		}

		virtual Boolean SetComponentAlternateSectionFillColors(MCObjectHandle object, short componentIndex, ColorRef alternateSectionFillForeColor, ColorRef alternateSectionFillBackColor) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassFillStyleForFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillStyleForFill) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassFillStyleForFill(MCObjectHandle object, short componentIndex, Boolean useClassFillStyleForFill) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassFillColorsForFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillColorsForFill) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassFillColorsForFill(MCObjectHandle object, short componentIndex, Boolean useClassFillColorsForFill) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassFillStyleForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillStyleForAlternateSectionFill) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassFillStyleForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean useClassFillStyleForAlternateSectionFill) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassFillColorsForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillColorsForAlternateSectionFill) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassFillColorsForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean useClassFillColorsForAlternateSectionFill) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenStyleForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenStyleForLeftPen) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenStyleForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenStyleForLeftPen) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenWeightForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenWeightForLeftPen) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenWeightForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenWeightForLeftPen) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenColorsForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenColorsForLeftPen) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenColorsForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenColorsForLeftPen) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenStyleForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenStyleForRightPen) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenStyleForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenStyleForRightPen) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenWeightForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenWeightForRightPen) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenWeightForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenWeightForRightPen) override
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenColorsForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenColorsForRightPen) override
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenColorsForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenColorsForRightPen) override
		{
			return false;
		}

		virtual void SetIsCurtainWall(MCObjectHandle wall, bool isCurtainWall) override
		{
			return;
		}

		virtual WorldCoord GetCurtainWallCutPlane(MCObjectHandle wall) override
		{
			return 0.0;
		}

		virtual void SetCurtainWallCutPlane(MCObjectHandle wall, WorldCoord curtainWallCutPlane) override
		{
			return;
		}

		virtual MCObjectHandle MirrorObject(MCObjectHandle h, bool dup, const WorldPt& p1, const WorldPt& p2) override
		{
			return 0;
		}

	// VW 2017
	public:
		virtual Sint32 ShowPullDownResourcePopupN(const ViewPt& pt, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize) override
		{
			return 0;
		}


		virtual Boolean ResetNurbsCurve(MCObjectHandle curveHandle, const WorldPt3& firstPt, bool byCtrlPts, short degree) override
		{
			return false;
		}

		virtual Boolean SetArc(MCObjectHandle hArc, const WorldPt& center, double radius, double startAngle, double sweepAngle) override
		{
			return false;
		}

		virtual void GetDefaultOpacityN( OpacityRef& outPenOpacity, OpacityRef& outFillOpacity) override
		{
	
		}


		virtual void GetDefaultOpacityByClassN(Boolean& outPenOpacityByClass, Boolean& outFillOpacityByClass) override
		{
	
		}


		virtual void SetDefaultOpacityN( OpacityRef inPenOpacity, OpacityRef inFillOpacity ) override
		{
	
		}

		virtual void SetDefaultOpacityByClassN( Boolean inPenOpacityByClass, Boolean inFillOpacityByClass ) override
		{
	
		}


		virtual void GetOpacityN( MCObjectHandle h, OpacityRef& outPenOpacity, OpacityRef& outFillOpacity) override
		{
	
		}


		virtual void GetOpacityByClassN( MCObjectHandle h, Boolean& outPenOpacityByClass, Boolean& outFillOpacityByClass) override
		{

		}


		virtual void SetOpacityN( MCObjectHandle h, OpacityRef inNewPenOpacity, OpacityRef inNewFillOpacity) override
		{
	
		}


		virtual void SetOpacityByClassN( MCObjectHandle h, Boolean inPenOpacityByClass, Boolean inFillOpacityByClass) override
		{
	
		}

		virtual void GetClOpacityN( InternalIndex classIndex, OpacityRef& penOpacity, OpacityRef& fillOpacity ) override
		{

		}

		virtual void SetCLOpacityN( InternalIndex classIndex, OpacityRef penOpacity, OpacityRef fillOpacity ) override
		{

		}

		virtual Boolean MarqueeEmptyList() override
		{
			return false;
		}

		virtual Boolean MarqueeAddObject(MCObjectHandle hInObject) override
		{
			return false;
		}

		virtual MCObjectHandle GetFreehandInteractivePoly() override
		{
			return 0;
		}

		virtual void BeginFreehandInteractive() override
		{
    
		}

		virtual void UpdateFreehandInteractive() override
		{
    
		}

		virtual MCObjectHandle EndFreehandInteractive() override
		{
			return 0;
		}

		virtual Boolean IsPlanRotationView() override
		{
			return false;
		}

		virtual MCObjectHandle CreateHelicalAlongCurve(MCObjectHandle curveHandle, double radius1, double radius2, double startAngle, double& pitch, double& numTurns, bool bPitch, bool bReverseTwist, bool bFlat) override
		{
			return NULL;
		}

		virtual void ViewRestoreN(MCObjectHandle hView, Boolean bDontRegen3DBounds) override
		{
		}

		virtual void RestoreSavedViewN(const TXString& savedView, Boolean bDontRegen3DBounds) override
		{
		}

		virtual void PerformMultipleUnion_2(TVWArray_MCObjectHandle  hArray, TVWArray_MCObjectHandle & hArrayResult, bool insert) override
		{
		}

		virtual Boolean	CreateDuplicateAlongPath(TVWArray_MCObjectHandle hProfileArray, MCObjectHandle inPathH, Boolean bUseNumber, Sint32 inNumber, double inDistance, double inStartOffset, Boolean bCenterObject, Boolean bTangent, Boolean bKeepOrienation, TVWArray_MCObjectHandle &outDuplicateArray) override
		{
			return false;
		}
 
		virtual void PullDownResourceSetToolBarPopup(short group, VectorWorks::Extension::IResourceManagerContent* content) override
		{
		}

		virtual TXString PullDownResourceGetSelectedResourceName(short group) override
		{
			return "";
		}

		virtual void PullDownResourceSetSelectedResourceName(short group, const TXString& name) override
		{
		}

		virtual void PullDownResourceLayoutInit(Sint32 dialogID, Sint32 itemID, VectorWorks::Extension::IResourceManagerContent* content) override
		{
		}

		virtual TXString PullDownResourceLayoutGetSelectedResourceName(Sint32 dialogID, Sint32 itemID) override
		{
			return "";
		}

		virtual void PullDownResourceLayoutSetSelectedResourceName(Sint32 dialogID, Sint32 itemID, const TXString& name) override
		{
		}

		virtual bool RebuildFileInResourceManager(IFileIdentifier*   pFileID) override
		{
			return false;
		}

		virtual bool RefreshLibrariesInResourceManager(SRefreshLibrariesOptions& options) override
		{
			return false;
		}


		virtual EDownloadErrors DownloadLibraryFile(ELibrariesID libraryID, const TXString& folderPath, const TXString& fileName, IFileIdentifier** ppOutFileID, SDownloadParams& params) override
		{
			return EDownloadErrors::errUnknownError;
		}

		virtual EDownloadErrors DownloadLibraryFile(ELibrariesID libraryID, EFolderSpecifier folderID, const TXString& fileName, IFileIdentifier** ppOutFileID, SDownloadParams& params) override
		{
			return EDownloadErrors::errUnknownError;
		}

		virtual void RemoveCustomTextureParts(MCObjectHandle /*h*/, Sint32  /*partCategoryID*/) override
		{

		}
 
		// For Slab drainage (Flat Roofs)
		virtual short AddDrain(MCObjectHandle slab, WorldPt location, WorldCoord height, double angle) override
		{

			// Unimplemented!!!!
			return -1;
		}
		virtual void AddCustomTexturePart(MCObjectHandle /*h*/, Sint32 /*partID*/, const TXString& /*partName*/, Sint32 /*partCategoryID = 0*/) override
		{

		}

		virtual Boolean	CustomTexturePartExists(MCObjectHandle h, Sint32 partID, Sint32 partCategoryID = 0) override
		{
			return false;
		}


		virtual void ApplyCustomTexturePart(MCObjectHandle srcObj, MCObjectHandle destObj, Sint32 partID, Sint32 partCategoryID = 0) override
		{
		}

		virtual void AddCustomTexturePartCategory(MCObjectHandle h, short partCategoryID, const TXString& categoryName) override
		{}

		virtual void RemoveCustomTexturePartCategory(MCObjectHandle h, short partCategoryID) override
		{}

		virtual bool HasCustomTexturePartCategory(MCObjectHandle h, short partCategoryID) override
		{
			return false;
		}

		virtual Boolean GetPluginObjectStyle( MCObjectHandle h, RefNumber& styleRefNumber ) override
		{
			return false;
		}

		virtual Boolean SetPluginObjectStyle( MCObjectHandle h, RefNumber styleRefNumber ) override
		{
			return false;
		}

		virtual void UpdatePIOFromStyle( MCObjectHandle h ) override
		{
		}

		virtual bool GetPluginStyleForTool( const TXString & toolUnivName, RefNumber& styleRefNumber ) override
		{
			return false;
		}

		virtual bool SetPluginStyleForTool( const TXString & toolUnivName, const RefNumber styleRefNumber ) override
		{
			return false;
		}

		virtual bool IsPluginStyle( MCObjectHandle h ) override
		{
			return false;
		}

		virtual RefNumber ChoosePluginStyleForTool( TInternalID internalToolID, RefNumber excludeRefNumber, const TXString & title,  const TXString & message  ) override
		{
			return 0;
		}

		virtual void ChoosePluginStyleForReplace( MCObjectHandle hObj ) override
		{
		}

		virtual Sint32 GetSymbolDefSubType( MCObjectHandle hObj ) override
		{
			return 0;
		}

		virtual void SetSymbolDefSubType( MCObjectHandle hObj, Sint32 subType ) override
		{
		}

		virtual bool GetPluginStyleSymbol( MCObjectHandle hObj, MCObjectHandle & hSymbolDefinition ) override
		{
			return false;
		}

		virtual EPluginStyleParameter GetPluginStyleParameterType( MCObjectHandle object, const TXString& paramName ) override
		{
			return 0;
		}

		virtual void SetPluginStyleParameterType( MCObjectHandle hSymbol, const TXString& paramName, EPluginStyleParameter styleType ) override
		{
		}

		virtual void SetAllPluginStyleParameters( MCObjectHandle hSymbol, EPluginStyleParameter styleType ) override
		{
		}

		virtual bool GetObjectWallInsertMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, InsertModeType& insertMode ) override
		{
			return false;
		}

		virtual bool SetObjectWallInsertMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, InsertModeType insertMode ) override
		{
			return false;
		}

		virtual bool GetObjectWallBreakMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, BreakModeType& breakMode ) override
		{
			return false;
		}

		virtual bool SetObjectWallBreakMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, BreakModeType breakMode ) override
		{
			return false;
		}

		virtual void ViewRect2WorldRect(const ViewRect& vRect, WorldRect& wRect) override
		{

		}

		virtual MCObjectHandle GetObjectByUuid(const TXString& uuid) override { return NULL; }
		virtual bool GetObjectUuid(MCObjectHandle h, TXString& uuid) override { return false; }
		virtual MCObjectHandle GetObjectByUuidN(const UuidStorage& uuid) override { return NULL; }
		virtual bool GetObjectUuidN(MCObjectHandle h, UuidStorage& uuid) override { return false; }

		//////////////////////////////////////////////////////////////////
		//  Drop Shadow related
		//////////////////////////////////////////////////////////////////
		virtual bool IsDropShadowEnabled(MCObjectHandle h) override
		{
			return false;	
		}

		virtual void EnableDropShadow (MCObjectHandle h, bool enable) override
		{
		
		}
 
		virtual bool GetDropShadowData(MCObjectHandle h, SDropShadowData & outDropShadowData) override
		{
			return false;	
		}

		virtual void SetDropShadowData(MCObjectHandle h, const SDropShadowData& inDropShadowData) override
		{
		
		}

		virtual void DeleteDropShadowData(MCObjectHandle h) override
		{
		
		}
 
		virtual void ShowDropShadowDialog(SDropShadowData& ioSDropShadowData, bool& ioByClass) override
		{
		
		}
 
		virtual bool IsDropShadowByClass(MCObjectHandle h) override
		{
			return false;	
		}

		virtual void SetDropShadowByClass(MCObjectHandle h, bool inSetByClass) override
		{
		
		
		} 
 
		virtual void GetClDropShadowData(InternalIndex classIndex, SDropShadowData& outDropShadowData) override
		{
		
		}
		virtual void SetClDropShadowData(InternalIndex classIndex, SDropShadowData& inDropShadowData) override
		{
		
		}
 
		virtual bool IsDropShadowEnabledInDocument() override
		{
			return false;
		}
		virtual void SetDropShadowByClassInDocument(bool inSetByClass) override
		{
	
		} 
 
		virtual void GetDocumentDropShadowData( SDropShadowData& outDropShadowData) override
		{
		
		}
		virtual void SetDocumentDropShadowData( const SDropShadowData& inDropShadowData) override
		{
		
		}

		virtual bool DropShadowDataAreEqual(const SDropShadowData& inDropShadowData1, const SDropShadowData& inDropShadowData2) override
		{
			return false;	
		}


		virtual bool GetAllCombinedsurfaces(MCObjectHandle baseObject, const TVWArray_MCObjectHandle& arrClipObjects, TXGenericArray< std::pair<MCObjectHandle, TVWArray_SizeT> >& arrResult, std::function<bool(size_t,size_t)> progressCallback) override
		{
			return false;
		}



		virtual short ConnectDrains(MCObjectHandle slab, short index1, short index2, short connectionType, double slopeAngle, double splitSlopeAngle) override
		{
			// Unimplemented!!!!
			return -1;
		}

		virtual short AddSlopeValley(MCObjectHandle slab, short index, WorldPt controlPt, double slope, double edgeHeight) override
		{
			// Unimplemented!!!!
			return -1;
		}

		virtual short GetNumDrains(MCObjectHandle slab) override
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual short GetNumDrainConnections(MCObjectHandle slab) override
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual bool SetDrainHeight(MCObjectHandle slab, short index, double height) override
		{
			// Unimplemented!!!!
			return false;
		}

		virtual double GetDrainHeight(MCObjectHandle slab, short index) override
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual WorldPt GetDrainLocation(MCObjectHandle slab, short index) override
		{
			// Unimplemented!!!!
			return WorldPt(0, 0);
		}

		virtual bool SetDrainLocation(MCObjectHandle slab, short index, const WorldPt& location) override
		{
			return false;
		}

		virtual void RotateDrain(MCObjectHandle slab, short index, double angle) override
		{
			// Unimplemented!!!!
		}

		virtual double GetDrainDrainageArea(MCObjectHandle slab, short index) override
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual MCObjectHandle GetDrainSymbol(MCObjectHandle slab, short index) override
		{
			// Unimplemented!!!!
			return nullptr;
		}

		virtual bool SetDrainSymbol(MCObjectHandle slab, short index, MCObjectHandle symbol) override
		{
			// Unimplemented!!!!
			return false;
		}

		virtual short GetNumDrainSlopeValleys(MCObjectHandle slab, short index) override
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual bool GetDrainSlopeValley(MCObjectHandle slab, short drain, short valley, WorldPt& controlPt, double& slope, double& edgeHeight, bool& heightLocked) override
		{
			// Unimplemented!!!!
			return false;
		}

		virtual void SetDrainSlopeValley (MCObjectHandle slab, short drain, short valley, WorldPt controlPt, double slope, double edgeHeight, bool lockHeight) override
		{
			// Unimplemented!!!!
		}

		virtual short GetNumDrainConnections(MCObjectHandle slab, short drain) override
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual short GetDrainConnectionIndex(MCObjectHandle slab, short drain, short index) override
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual bool GetDrainConnection(MCObjectHandle slab, short index, short& drain1, short& drain2, short& style, double& angle1, double& angle2) override
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool SetDrainConnection(MCObjectHandle slab, short index, short style, double angle1, double angle2) override
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool DeleteDrainConnection(MCObjectHandle slab, short index) override
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool DeleteSlopeValley(MCObjectHandle, short drain, short index, bool forceDelete) override
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool DeleteDrain(MCObjectHandle slab, short index) override
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool GetLayerEnableCutPlane(MCObjectHandle layer) override
		{
			return false;
		}

		virtual void SetLayerEnableCutPlane(MCObjectHandle layer, bool enableCutPlane) override
		{
			return;
		}

		virtual WorldCoord GetLayerCutPlane(MCObjectHandle layer) override
		{
			return 0.0;
		}

		virtual void SetLayerCutPlane(MCObjectHandle layer, WorldCoord cutPlane) override
		{
			return;
		}

		virtual InternalIndex GetWallBelowCutPlaneClass(MCObjectHandle wall) override
		{
			return 0;
		}

		virtual void SetWallBelowCutPlaneClass(MCObjectHandle wall, InternalIndex belowCutPlaneClass) override
		{
			return;
		}

		virtual short GetTaperedComponent(MCObjectHandle object) override
		{
			return 0;
		}

		virtual void SetTaperedComponent(MCObjectHandle object, short componentIndex) override
		{
			return;
		}

		virtual Boolean GetComponentAutoBoundEdgeOffsetOffset(MCObjectHandle object, short componentIndex, WorldCoord &autoBoundEdgeOffsetOffset) override
		{
			return false;
		}

		virtual Boolean SetComponentAutoBoundEdgeOffsetOffset(MCObjectHandle object, short componentIndex, WorldCoord autoBoundEdgeOffsetOffset) override
		{
			return false;
		}

		virtual Boolean GetComponentMasterSnaps(MCObjectHandle object, short componentIndex, Boolean &masterSnapOnLeft, Boolean &masterSnapOnRight) override
		{
			return false;
		}

		virtual Boolean SetComponentMasterSnaps(MCObjectHandle object, short componentIndex, Boolean masterSnapOnLeft, Boolean masterSnapOnRight) override
		{
			return false;
		}

		virtual void InteractiveViewOperation_GetFlyOverOrigin( ViewPt& curFlyOverOrigin ) override
		{

		}


		virtual double GetWorksheetImageScaleFactor(MCObjectHandle hWorksheetImage) override
		{
			return 1.0;
		}

		virtual bool SetWorksheetImageScaleFactor(MCObjectHandle hWorksheetImage, double scale, bool redrawImage) override
		{
			return false;
		}

		virtual void SetWorksheetCellsImageResolution(MCObjectHandle hWorksheet, Sint16 dpiResolution) override
		{
			return;
		}

		virtual Sint16 GetWorksheetCellsImageResolution(MCObjectHandle hWorksheet) override
		{
			return 150;
		}

		virtual MCObjectHandle CreateResourceFolder(const TXString& name, Sint16 resourceType) override
		{
			return nil;
		}

		virtual void CreateResourceFolderN(const TXString& folderPath, Sint16 resourceType, TVWArray_MCObjectHandle & outFolderPath) override
		{
			return;
		}

		virtual bool AddResourceTags(MCObjectHandle h, const TXStringArray& arrTags) override
		{
			return false;
		}

		virtual bool GetResourceTags(MCObjectHandle h, TXStringArray& arrTags) override
		{
			return false;
		}

		virtual bool  IsActiveSymbolInCurrentDocument() override
		{
			return 0;
		}

		virtual bool AddItemToPluginStyle( MCObjectHandle hSymDef, const TXString & itemName, EPluginStyleParameter styleType ) override
		{
			return false;
		}

		virtual bool RemoveItemFromPluginStyle( MCObjectHandle hSymDef, const TXString & itemName ) override
		{
			return false;
		}

		virtual bool GetDimensionsAssociatedToPlugin( MCObjectHandle hPlugin, TVWArray_MCObjectHandle &dimHandles ) override
		{
			return false;
		}

		virtual bool GetChainThatContainsDimension( MCObjectHandle hDim, MCObjectHandle &hChain ) override
		{
			return false;
		}

		virtual MCObjectHandle CreateVWObjectFromSplineData(const TVWArray_WorldPt3& controlPoints, const TVWArray_Double& weights, const TVWArray_Double& knots, Sint32 degree, bool isRational, bool isClosed, bool create2D) override
		{
			return NULL;
		}

		virtual bool SetDefaultGenericStoryLevelBound( MCObjectHandle hFormat, const SStoryObjectData& data ) override
		{
			return false;
		}

		virtual bool GetDefaultGenericStoryLevelBound( MCObjectHandle hFormat,  SStoryObjectData& data ) override
		{
			return false;
		}

		virtual void GetStoryBoundChoiceStringsN( MCObjectHandle story, TXStringArray& outStrings, EStoryLevelPopupBoundType boundType) override
		{
			return;
		}

		virtual Sint32 AddResourceToListUnsorted(Sint32 listID, MCObjectHandle obj) override
		{
			return -1;
		}

		virtual Sint32 VCOM_CALLTYPE BuildResourceListUnsorted(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems) override
		{
			return 0;
		}

		virtual bool CreateReference( IFileIdentifier* pFileID ) override
		{
			return false;
		}

		virtual void UpdateStyledObjects( RefNumber styleRefNumber ) override
		{
			return;
		}
		virtual void GetStoryLevels( MCObjectHandle story, TXStringArray& outStrings) override
		{
			return;
		}

		virtual void InitClassOverrideData(InternalIndex classIndex, SViewportClassOverride& outData) override
		{
			return;
		}

		virtual void InitLayerOverrideData(InternalIndex layerIndex, SViewportLayerOverride& outData) override
		{
			return;
		}
		
		virtual void InitLightOverrideData(InternalIndex lightIndex, SViewportLightOverride& outData) override
		{
			return;
		}

		virtual void GetCurrentWorkspace(VectorWorks::Workspaces::IWorkspaceFile** outWorkspace) override
		{
		}

		virtual bool InstallConstraintPlane(TPlanarRefID inContextPlanarRefID, const WorldPt& inwptStartPt) override
		{
			return false;
		}

		virtual bool AddItemToPluginStyleEditList( MCObjectHandle hSymDef, const TXString & itemName, EPluginStyleEditList editListType, const TXString & displayName ) override
		{
			return false;
		}

		virtual bool RemoveItemFromPluginStyleEditList( MCObjectHandle hObj, const TXString & itemName ) override
		{
			return false;
		}

		virtual bool GetPluginStyleEditListType( MCObjectHandle hObj, const TXString& paramName, EPluginStyleEditList & editListTyle, TXString & displayName ) override
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE OffsetPolyClosed(MCObjectHandle h, double offset, bool smoothConers) override
		{
			return NULL;
		}

		virtual MCObjectHandle VCOM_CALLTYPE CreateImgFromSymbol( const TXString & symbolName, SymbolImgInfo& imgInfoInOut) override
		{											   
			return NULL;							   
		}											   
											 
		virtual void  VCOM_CALLTYPE GetSelInsertsInWall( MCObjectHandle hObj, TVWArray_MCObjectHandle& selInserts) override
		{
		}
											 
		virtual bool VCOM_CALLTYPE GetCurlProxyInfo(TXString& outProxyType, TXString& outAddress, Sint32& outPort, TXString& outUsername, TXString& outPassword) override
		{
			return false;
		}
					
		virtual TXString  VCOM_CALLTYPE GetFormattedDateTimeString(EDateTimeFormat dateTimeFormat) override
		{
			return ""; 
		}

		virtual TXString VCOM_CALLTYPE GetFormattedDateTimeString(EDateTimeFormat dateTimeFormat, const SDateTimeData& dateTimeData) override
		{
			return "";
		}

		virtual TXString  VCOM_CALLTYPE GetLocalSystemDateTimeString(EDateFormat dateFormat, EInfoFormat infoFormat) override
		{
			return ""; 
		}

		virtual bool VCOM_CALLTYPE GetDateTimeIntlData(TDateTimeIntlData& outDateTimeIntlData) override
		{
			return false;
		}

		virtual void SetHotSpotColor(HotSpotRefID inHotSpotID, GSColor color) override
		{
		}

		virtual void DrawHotSpots() override
		{
		}

		virtual void EnterObjectGroup(MCObjectHandle hGroup, const EEditPartContext& context = EEditPartContext::Generically2d) override
		{
		}

		virtual bool IsSymDefUsedInEditContext(MCObjectHandle hSymDef) override
		{
			return false;
		}


		virtual bool GetCatalogPath( MCObjectHandle hObj, EFolderSpecifier & folderSpec, TXString & relativePath ) override
		{
			return false;
		}


		virtual bool SelectPluginCatalog( MCObjectHandle hSymDef ) override
		{
			return false;
		}
		virtual bool SelectItemFromPluginCatalog( MCObjectHandle hObj, const TXString & catName, 
			std::function<TXString(const TXString & id, EEmptyHandling opt)> columnNamesLocalizer  ) override
		{
			return false;
		}

		virtual bool AplyFirstCatalogItem( MCObjectHandle hObj, const TXString & catName ) override
		{
			return false;
		}

		virtual Boolean GetComponentFunction(MCObjectHandle object, short componentIndex, EComponentFunction &function) override
		{
			return false;
		}

		virtual Boolean SetComponentFunction(MCObjectHandle object, short componentIndex, EComponentFunction function) override
		{
			return false;
		}
		virtual bool IsCatalogParameter( MCObjectHandle hObj, const TXString & paramName ) override
		{
			return false;
		}

		virtual void SetUseCatalogItem( MCObjectHandle hObj, const bool & useCatItem ) override
		{
		}

		virtual bool GetUseCatalogItem( MCObjectHandle hObj ) override
		{
			return false;
		}

		virtual void SetCatalogItemByStyle( MCObjectHandle hObj, const bool & byStyle ) override
		{
		}

		virtual bool GetCatalogItemByStyle( MCObjectHandle hObj ) override
		{
			return false;
		}

		virtual MCObjectHandle	FitExtrudeToObjects(MCObjectHandle hExtrude, bool isTopFit, EFitExtrudeToObjectsOption boundOption, double defaultHeight, TVWArray_MCObjectHandle clippingHandleArray, EFitExtrudeToObjectsRoofAndSlabOption roofSlabOption) override
		{
			return NULL;
		}

		virtual MCObjectHandle GetWallEndCapFootPrint(MCObjectHandle theWall, bool atStart) override
		{
			return NULL;
		}
		virtual bool SimplifyMesh(MCObjectHandle meshHandle, float quality) override
		{
			return NULL;
		}


		virtual bool SetToolPt2D(Sint32 inIndex, const WorldPt& inToolPoint) override
		{
			return false;
		}

		virtual bool SetToolPt3D(Sint32 inIndex, const WorldPt3& inToolPoint) override
		{
			return false;
		}
		virtual short GetObjTypeProperties(short objectType) override
		{
			return -1;
		}

		virtual bool GetWorksheetImageShowDBHeaders(MCObjectHandle hWorksheetImage) override
		{
			return false;
		}

		virtual void SetWorksheetImageShowDBHeaders(MCObjectHandle hWorksheetImage, bool show, bool redrawImage) override
		{
		}

		virtual void DisplayDocumentPreferences(EDocumentPrefsTab tabToSelect) override
		{
		}

		virtual size_t GetResourceStringTableSize(const char* resIdentifier) override
		{
			return 0;
		}

		virtual void GetReferencedFilesInfo(TVWArray_ReferencedFileInfo& outRefFilesInfo) override
		{

		}

		virtual void DeleteReferencedFiles(TVWArray_ReferencedFileInfo& outRefFilesInfo, const SDeleteFileOptions fileOptions) override
		{

		}

		// For Multiview
		virtual void SetFocusOnSelectedViewPane(bool bMakeItActive, bool bUpdateUI) override
		{

		}

		virtual void GetPageBoundsN(MCObjectHandle hLayer,WorldRect& bounds) override
		{

		}

		virtual void TrackToolN(MCObjectHandle& overObject, MCObjectHandle& overSubObject, short& overPart, SintptrT& code) override
		{

		}

		virtual void SetWorksheetCellCOBieValue(MCObjectHandle worksheet, const ViewPt& cell, const TXString& formula) override
		{

		}

		virtual void GetSlabHolesAndTheirMiters(MCObjectHandle hSlab, TVWArray_MCObjectHandle& outHolesArray, TVWArray_SizeT& outMitersArray) override
		{
    
		}
	// VW 2019
	public:
		virtual short GetDlgCtrlWidthStdChar(const TXString& str) override
		{
			return 0;
		}

		virtual bool ExportResourceList(const TVWArray_MCObjectHandle& inResourceList, IFileIdentifier* pFileID, bool suppressDialogs) override
		{
			return false;
		}

		virtual bool ExportResourceListN(const TVWArray_MCObjectHandle& inResourceList, IFileIdentifier* pFileID, TImportResourceConflictCallbackProcPtr conflictCallback) override
		{
			return false;
		}

		virtual TXString GetHierarchicalListBrowserRowContainerPath(Sint32 dialogID, Sint32 componentID, Sint32 rowIndex) override
		{
			return "";
		}

		virtual bool SelectInResourceManager( MCObjectHandle requestedResource ) override
		{
			return false; 
		}

		virtual bool BeginMultipleMove() override
		{
			return false;
		}

		virtual bool EndMultipleMove() override
		{
			return false;
		}

		virtual bool GetWallAngleVector(const MCObjectHandle& wallHandle, const WorldPt& rotationCenter, WorldPt& wallVector) override
		{
			return false;
		}

		virtual void CoordToDimStringInUnits(WorldCoord value, VectorWorks::Units::IVWUnits* dimUnit, TXString& str) override
		{

		}

		virtual void DoubleToStringInUnits(TNumStyleClass inNumStyle, Byte inAccuracy, Byte inFormat, double_param inDouble, VectorWorks::Units::IVWUnits* dimUnit, TXString& outString) override
		{

		}

		virtual size_t GetPDFAnnotationsCount(MCObjectHandle object) override
		{
			return 0;
		}

		// For Line type re-engineering
		virtual Boolean	GetCumulativeDashPat(InternalIndex dashLineType, DashPatType& outDashPat) override
		{
			return false;
		}

		virtual Boolean	GetSimpleLineTypeDefinition(const InternalIndex lineTypeRef, DashPatDef& outDashPat) override
		{
			return false;
		}

		virtual InternalIndex	CreateOrFindSimpleLineTypeDefinition(const DashPatDef& inDashPat) override
		{
			return 0;
		}
		virtual InternalIndex GetDashLineStyle(bool scaleWithThick, const std::vector<double>& theVectors) override
		{
			return 0;
		}

		virtual Boolean	SetDashLineTypeName(InternalIndex dashLineType, const TXString& dashStyleName) override
		{
			return false;
		}
		virtual TXString GetDashLineTypeName(InternalIndex dashLineType) override
		{
			return "";
		}
		virtual Boolean	GetDLComponentPenStylesN(Sint16 index, InternalIndex& outPenStyleLeft, InternalIndex& outPenStyleRight) override
		{
			return false;
		}
		virtual Boolean	SetDLComponentPenStylesN(Sint16 index, InternalIndex penStyleLeft, InternalIndex penStyleRight) override
		{
			return false;
		}
		virtual Boolean InsertNewDLComponentN(Sint16 beforeIndex, WorldCoord width, Sint32 fill, Uint8 penWeightLeft, Uint8 penWeightRight, InternalIndex penStyleLeft, InternalIndex penStyleRight) override
		{
			return false;
		}
		virtual Boolean InsertNewComponentN(MCObjectHandle object, short beforeComponentIndex, WorldCoord width, Sint32 fill, Uint8 leftPenWeight, Uint8 rightPenWeight, InternalIndex leftPenStyle, InternalIndex rightPenStyle) override
		{
			return false;
		}

		virtual Boolean IsDashLineStyle(InternalIndex dashLineType) override
		{
			return false;
		}
		virtual void GetWSCellAllBordersN(MCObjectHandle worksheet, const ViewPt& cell, TCellBorderRefNum& top, TCellBorderRefNum& left, TCellBorderRefNum& bottom, TCellBorderRefNum& right) override
		{
		}
		virtual void SetWSCellAllBordersN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, TCellBorderRefNum top, TCellBorderRefNum left, TCellBorderRefNum bottom, TCellBorderRefNum right, TCellBorderRefNum insideVert, TCellBorderRefNum insideHorz) override
		{

		}
		virtual void SetWSCellBottomBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) override
		{

		}
		virtual void SetWSCellInsideHorizBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) override
		{

		}
		virtual void SetWSCellInsideVertBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) override
		{

		}
		virtual void SetWSCellLeftBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) override
		{

		}
		virtual void SetWSCellOutlineBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) override
		{

		}
		virtual void SetWSCellRightBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) override
		{

		}
		virtual void SetWSCellTopBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color) override
		{

		}
		virtual bool GetPseudoDashIndexFromDashLineType(const InternalIndex dashLineType, Sint16& pseudoIndex) override
		{
			return false;
		}
		virtual bool GetDashLineTypeFromPseudoDashIndex(const Sint16 pseudoIndex, InternalIndex& dashLineType) override
		{
			return false;
		}
		virtual void BeginMultiplePseudoDashIndexConvert() override
		{
		}
		virtual void EndMultiplePseudoDashIndexConvert() override
		{
		}

		virtual void CreateSearchEditBox(Sint32 dialogID, Sint32 itemID, const TXString& promptText, short widthInStdChar) override
		{
		}

		virtual MCObjectHandle CreateSymbolDefinitionForDisplayControl(TXString& inoutName) override
		{
			return NULL;
		}

		virtual TXString	GetActiveSymbolName() override
		{
			return "";
		};

		virtual bool	GetFilePathForActiveSymbolInOpenDocument(IFileIdentifier** ppOutFileID, bool& outFolderSet) override
		{
			return false;
		};

		virtual bool AssignUuidToHandle(MCObjectHandle h, const UuidStorage& uuid, TDocumentUuidsCheckTable& checkTable) override
		{
			return false;
		}

		virtual void CreateEditPassword(Sint32 dialogID, Sint32 itemID, short widthInStdChar) override
		{
		}

		//This lets the user assign text tags to an object
		virtual bool AddObjectTags(MCObjectHandle h, const TXStringArray& arrTags) override
		{
			return false;
		}

		virtual bool GetObjectTags(MCObjectHandle h, TXStringArray& arrTags) override
		{
			return false;
		}

		virtual bool ShowChooseDateFormatDialog(EDateTimeFormat& inOutDateFormat) override
		{
			return false;
		}

		virtual ESetSpecialGroupErrors Set2DComponentGroup(MCObjectHandle hObject, MCObjectHandle hGroup, EViewTypes component) override
		{
			return ESetSpecialGroupErrors::CannotSet_BadData;
		}

		virtual MCObjectHandle	Get2DComponentGroup(MCObjectHandle hObject, EViewTypes component) override
		{
			return nullptr;
		}

		virtual ESetSpecialGroupErrors AddObjectTo2DComponentGroup(MCObjectHandle hObject, MCObjectHandle hObjectToAdd, EViewTypes component) override
		{
			return ESetSpecialGroupErrors::CannotSet_BadData;
		}

		virtual bool SetTopPlan2DComponent(MCObjectHandle hObject, ETopPlanViewComponent component) override
		{
			return false;
		}

		virtual ETopPlanViewComponent GetTopPlan2DComponent(MCObjectHandle hObject) override
		{
			return ETopPlanViewComponent::Top;
		}

		virtual bool SetDisplayWith2DComponent(MCObjectHandle hObject, EViewTypes component, bool isVisible) override
		{
			return false;
		}

		virtual bool GetDisplayWith2DComponent(MCObjectHandle hObject, EViewTypes component) override
		{
			return false;
		}

		virtual bool SetMirrorEmpty2DComponents(MCObjectHandle hObject, bool doMirror) override
		{
			return false;
		}

		virtual bool GetMirrorEmpty2DComponents(MCObjectHandle hObject) override
		{
			return false;
		}

		virtual bool Generate2DFrom3DComponent(MCObjectHandle hObject, EViewTypes component, TRenderMode renderMode, ELevelsOfDetail levelOfDetails) override
		{
			return false;
		}

		virtual MCObjectHandle CreateTemporaryCustomObject(const TXString& name, const WorldPt& location, double_param angle) override
		{
			return NULL;
		}

		virtual MCObjectHandle CreateTemporaryCustomObjectByMatrix(const TXString& name, const TransformMatrix& matrix) override
		{
			return NULL;
		}

		virtual MCObjectHandle CreateTemporaryCustomObjectByMatrixEx(const TXString& name, const TransformMatrix& matrix) override
		{
			return NULL;
		}

		virtual void GetPageMargins(MCObjectHandle hLayer, double& left, double& right, double& bottom, double& top) override
		{
		}

		virtual Boolean CreateLayerPullDownMenu(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar) override
		{
			return false;
		}

		virtual WorldPt3 Project3DPointOnPlane(const WorldPt3& given3DPoint, const WorldPt3& pointOnPlane, const WorldPt3& planeNormal, const WorldPt3& projectionDir) override
		{
			return WorldPt3(0.0, 0.0, 0.0);
		}
	
	// VW 2020
	public:

		virtual void ShowDetailedMemoryInfoDlg() override
		{

		}

		virtual MCObjectHandle GetCustomObjectProfileGroupInAux(MCObjectHandle objectHand) override
		{
			return nullptr;
		}

		virtual bool EditSymbolMarkersDialog(const TXString& dialogTitle, const TXString& contextHelpID, TXString& inOutStartMarkerSymName, TXString& inOutEndMarkerSymName) override
		{
			return false;
		}

		virtual bool ImportParasolidXT(IFileIdentifier* pFileID, ViewPt* position) override
		{
			return false;
		}

		virtual bool CreateSearchablePulldownMenu(Sint32 dialogID, Sint32 controlID, Sint32 widthInStdChar) override
		{
			return false;
		}

		virtual bool InsertStaticItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, const TXString& itemImageSpec, bool shouldUpdate) override
		{
			return false;
		}

		virtual bool InsertItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, const TXString& itemImageSpec, bool shouldUpdate) override
		{
			return false;
		}

		virtual bool InsertChildItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& parentIDStr, const TXString& itemToolTip,
			const TXString& itemImageSpec, bool shouldUpdate) override
		{
			return false;
		}

		virtual void ClearChoicesFromSearchablePulldown(Sint32 dialogID, Sint32 controlID, bool clearStaticItems) override
		{

		}

		virtual TXString GetActiveIDStrFromSearchablePulldown(Sint32 dialogID, Sint32 controlID) override
		{
			return "";
		}

		virtual bool SetActiveIDStrInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& activeIDStr) override
		{
			return false;
		}

		virtual bool GetDisplayNameFromIDStrInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& idStrToFind, TXString& outName) override
		{
			return false;
		}

		virtual bool GetIDStrFromDisplayNameInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& nameToFind, TXString& outIDStr) override
		{
			return false;
		}

		virtual MCObjectHandle GetWallRecessGeometryGroup(MCObjectHandle objectHand) override
		{
			return 0;
		}

		virtual bool SetWallRecessGeometryGroup(MCObjectHandle objectHand, MCObjectHandle hNewGroup) override
		{
			return false;
		}


		virtual Boolean EndAndRemoveUndoEvent() override { return false; }

		virtual void ClearUndoTableDueToUnsupportedAction() override {  }

		virtual void AlertDialogWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink) override { }

		virtual Boolean SetListBrowserItemTextColorN(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, EUiControlTextTint colorTint) override { return true; }

		virtual bool  GetSpaceWallInserts(MCObjectHandle space, bool includeExteriorWallInserts, bool includeInteriorWallInserts, std::vector<InternalIndex> &wallInserts) override { return false; }

		virtual bool IsListBrowserExternalSortEnabled(Sint32 dialogID, Sint32 controlID) const override { return false; }

		virtual void EnableListBrowserExternalSort(Sint32 dialogID, Sint32 controlID, bool bEnable/* = true*/) override { }

		virtual bool TesselateObjectN(TTesselator pTess, const STesselateOptions& options, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv) override { return false; }
		virtual void Get2DComponentLocation(MCObjectHandle hObject, EViewTypes component, bool &onBoundsCube, double &offset) override { }

		virtual bool Set2DComponentLocation(MCObjectHandle hObject, EViewTypes component, bool onBoundsCube, double offset) override { return false; }

		virtual EObjectCutPlane GetHorizontalSectionCutPlane(MCObjectHandle hObject) override { return EObjectCutPlane::kViewAsCutWhenCutInViewport; }

		virtual bool SetHorizontalSectionCutPlane(MCObjectHandle hObject, EObjectCutPlane objectCutPlane) override { return false; }

		virtual EObjectCutPlane GetVerticalSectionCutPlane(MCObjectHandle hObject) override { return EObjectCutPlane::kViewAsCutWhenCutInViewport; }

		virtual bool SetVerticalSectionCutPlane(MCObjectHandle hObject, EObjectCutPlane objectCutPlane) override { return false; }

		virtual bool Get2DComponentsByStyle(MCObjectHandle hObject) override { return false; }
		virtual bool Set2DComponentsByStyle(MCObjectHandle hObject, bool byStyle) override { return false; }
		virtual bool GetMirrorEmpty2DComponentsByStyle(MCObjectHandle hObject) override { return false;	}
		virtual bool SetMirrorEmpty2DComponentsByStyle(MCObjectHandle hObject, bool byStyle) override { return false; }
		virtual bool GetTopPlan2DComponentByStyle(MCObjectHandle hObject) override { return false; }
		virtual bool SetTopPlan2DComponentByStyle(MCObjectHandle hObject, bool byStyle) override { return false; }
		virtual bool GetHorizontalSectionCutPlaneByStyle(MCObjectHandle hObject) override { return false; }
		virtual bool SetHorizontalSectionCutPlaneByStyle(MCObjectHandle hObject, bool byStyle) override { return false; }
		virtual bool GetVerticalSectionCutPlaneByStyle(MCObjectHandle hObject) override { return false; }
		virtual bool SetVerticalSectionCutPlaneByStyle(MCObjectHandle hObject, bool byStyle) override { return false; }

		virtual bool	VCOM_CALLTYPE SetLayerName(MCObjectHandle hLayer, const TXString& layerName, bool updateLayerDependencies) override { return false; }
		virtual bool	VCOM_CALLTYPE SetSheetLayerTitle(MCObjectHandle hLayer, const TXString& sheetTitle) override { return false; }

		virtual void	VCOM_CALLTYPE AlertCriticalWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink) override { }
		virtual void	VCOM_CALLTYPE AlertInformWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink, bool minorAlert = false, const TXString& category = "", const TXString& item = "", const TXString& checkboxOverrideText = "") override { }

		// VW 2021
	public:
		virtual InternalName	CheckAndResolveDuplicateInternalName(const InternalName& inName) override { return ""; }
		virtual bool			VCOM_CALLTYPE GetVWResourceStringKeys(const char* resourceIdentifier, std::vector<TXString>& outvecKeys) override { return false; }

		virtual bool			CreateClassPullDownMenuN(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar, bool bShowDefaultStaticItems = true) override { return false; }
		virtual bool			CreateLayerPullDownMenuN(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar, bool bShowDefaultStaticItems = true) override { return false; }
		virtual bool			CreateSheetLayerPullDownMenuN(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar, bool bShowDefaultStaticItems = true) override { return false; }
		virtual bool			CreateDesignLayerPullDownMenuN(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar, bool bShowDefaultStaticItems = true) override { return false; }

		virtual bool			InsertHeaderItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemDisplayName, const TXString& itemToolTip) override { return false; }
		virtual void			VCOM_CALLTYPE PixelLengthToLineWeight(short inPixels, short& outLineWeightMils) override {}
		virtual void			VCOM_CALLTYPE LineWeightToPixelLength(short inLineWeightMils, short& outPixels) override {}
		virtual bool			VCOM_CALLTYPE ShowFloatingDataBar(bool bShow) override { return false; }
		virtual Boolean			VCOM_CALLTYPE IsDesignLayerSectionViewport(MCObjectHandle hObj) override { return false; }
		virtual void			VCOM_CALLTYPE UpdateSLVPForOnlyAnnotationsChange(MCObjectHandle inhSLVP, const WorldRect& inwrBoxBefore_SLVP, const WorldRect& inwrBoxBefore_Annots) override {}

		virtual bool			VCOM_CALLTYPE InsertHeaderItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemDisplayName, const TXString& itemToolTip, const TXString& itemImageSpec) override { return false; }
		virtual bool			VCOM_CALLTYPE InsertHeaderItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemDisplayName, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon) override { return false; }

		virtual bool			VCOM_CALLTYPE InsertStaticItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon, bool shouldUpdate) override { return false; }
		virtual bool			VCOM_CALLTYPE InsertItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon, bool shouldUpdate) override { return false; }
		virtual bool			VCOM_CALLTYPE InsertChildItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& parentIDStr, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon, bool shouldUpdate) override { return false; }

		virtual void			VCOM_CALLTYPE EnableItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, bool enableItem) override {}
		virtual MCObjectHandle  GetBoundFromWalls(TVWArray_MCObjectHandle & wallList, const TXString& UUID, int columnsAndPilastersEnum, MCObjectHandle existingProfile) override { return NULL; }
		
		virtual void			ForEachObjectAtPoint( short traverseWhat, const WorldPt& pt, WorldCoord dRadius, std::function<bool(MCObjectHandle h)> callbackLambda) override { }

		virtual MCObjectHandle  CreateMaterial(const TXString& name, bool isSimpleMaterial) override { return nullptr; }
		virtual bool			GetObjectMaterialName(MCObjectHandle objectHandle, TXString& outMaterialName) override { return false; }
		virtual MCObjectHandle	GetObjectMaterialHandle(MCObjectHandle objectHandle) override { return nullptr; }
		virtual bool			SetObjectMaterialHandle(MCObjectHandle objectHandle, MCObjectHandle materialHandle) override { return false;  }
		virtual bool			IsMaterialSimple(MCObjectHandle materialHandle) override { return false; }
		virtual InternalIndex   GetMaterialTexture(MCObjectHandle materialHandle) override { return 0; }
		virtual bool			SetMaterialTexture(MCObjectHandle materialHandle, InternalIndex textureIndex) override { return false; }
		virtual InternalIndex	GetMaterialFillStyle(MCObjectHandle materialHandle) override { return 0; }
		virtual bool			SetMaterialFillStyle(MCObjectHandle materialHandle, InternalIndex fillStyle) override { return false; }
		virtual bool			IsMaterialFillStyleByClass(MCObjectHandle materialHandle) override { return false; }
		virtual bool			SetMaterialFillStyleByClass(MCObjectHandle materialHandle, bool isByClass) override { return false; }
		virtual bool			GetMaterialFillColor(MCObjectHandle materialHandle, ObjectColorType& fillColors) override { return false; }
		virtual bool			SetMaterialFillColor(MCObjectHandle materialHandle, const ObjectColorType& fillColors) override { return false; }
		virtual bool			SetSubmaterialsInMaterial(MCObjectHandle materialHandle, const CompoundSubmaterialDataVector& dataVector) override { return false; }
		virtual bool			GetSubmaterialsFromMaterial(MCObjectHandle materialHandle, CompoundSubmaterialDataVector& dataVector) override { return false; }
		virtual bool			AddSubmaterialToMaterial(MCObjectHandle materialHandle, const TXString&	submaterialName, double fraction = 1.0, bool makePrimary = false) override { return false; }
		virtual bool			RemoveSubmaterialFromMaterial(MCObjectHandle materialHandle, const TXString& submaterialName) override { return false; }
		virtual bool			UpdateSubmaterialInMaterial(MCObjectHandle materialHandle, const TXString&	submaterialName, double fraction = 1.0, bool makePrimary = false) override { return false; }
        
		virtual void			SetExcludeObjectFromDataVisualization(MCObjectHandle objectHandle, Boolean exclude) override {}

		// this function must be used during the Regenerate event when kObjXPropPreserveContents Is defined
		// it will delete the regenerable sub objects from child list of the parametric, emulating the standard behaviour
		virtual void			DeleteRegenerableSubObjects ( MCObjectHandle hParametric ) override {}

		virtual Boolean			GetComponentMaterial(MCObjectHandle object, short componentIndex, InternalIndex &material) override { return false; }
		virtual Boolean			SetComponentMaterial(MCObjectHandle object, short componentIndex, InternalIndex material) override { return false; }

		virtual MCObjectHandle	VCOM_CALLTYPE CustomObjectGetPathProxy(MCObjectHandle inPathObject, ObjectPropID inPurpose) override { return nullptr; }

	// VW 2021
	public:
		virtual void			VCOM_CALLTYPE EditPluginStyle(MCObjectHandle hStyle) override { };

		virtual bool			VCOM_CALLTYPE GetWorksheetCellFlagChanged(MCObjectHandle worksheet, const ViewPt& cell) override { return true; }
		virtual bool			VCOM_CALLTYPE GetWorksheetCellFlagInvalid(MCObjectHandle worksheet, const ViewPt& cell) override { return true; }

		virtual bool			VCOM_CALLTYPE CreateResourceTextPopup(Sint32 dialogID, Sint32 controlID, Sint32 widthInStdChar) override { return false; }

		virtual double			VCOM_CALLTYPE GetRotationAroundAxis(MCObjectHandle hObject, MajorAxisSpec aroundAxis) override { return 0.0; }
		virtual void			VCOM_CALLTYPE TransformObject(MCObjectHandle hObject, const TransformMatrix& transformMatrix) override {}
		virtual MCObjectHandle	VCOM_CALLTYPE AssociateBoundedObjectWithWallsAndApplyOffset(MCObjectHandle inBoundedObject, TVWArray_MCObjectHandle& wallList, short inColumnsAndPilastersEnum, double offsetDistance, bool bExcludePiosNiches) override
		{
			return NULL;
		}

		virtual bool			VCOM_CALLTYPE GetClassByStyle(MCObjectHandle h) override { return false; }
		virtual bool			VCOM_CALLTYPE SetClassByStyle(MCObjectHandle h, bool byStyle) override { return false; }

		virtual double			VCOM_CALLTYPE GetMaterialArea(MCObjectHandle hObject, const TXString& materialName) override { return 0.0; }
		virtual double			VCOM_CALLTYPE GetMaterialVolume(MCObjectHandle hObject, const TXString& materialName) override { return 0.0; }
		virtual void            VCOM_CALLTYPE ComposeObjectHandles(TVWArray_MCObjectHandle& objsToComposeArray, bool bInsert, TVWArray_MCObjectHandle& composedObjsArray) override {}

		virtual MCObjectHandle	VCOM_CALLTYPE DuplicateObjectIgnoreConstraints(MCObjectHandle h) override { return NULL; }
 		virtual WorldCoord      VCOM_CALLTYPE GetStoryObjectDataBoundHeight(const SStoryObjectData& storyData, MCObjectHandle hContainer) override { return 0.0; }
		virtual void			VCOM_CALLTYPE ForEachMaterial(bool onlyUsed, std::function<void(MCObjectHandle h)> callbackLambda) override {};

	// VW 2022
	public:
		virtual void VCOM_CALLTYPE CreateEditColorText(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines) override {}
		virtual bool VCOM_CALLTYPE SetEditColorTextStyle(Sint32 dialogID, Sint32 itemID, const TXString& strConfig, VWVariant* outResult = nullptr, VWVariant* outParam2 = nullptr) override { return false; }

		virtual EWallPathType	VCOM_CALLTYPE GetWallPathType(MCObjectHandle wall) override {return eWallPathType_line;}

		virtual void			VCOM_CALLTYPE AddToolEditTextMethodN(const TXString& label, const TXString& value, Sint32 textWidth) override {}

		virtual bool			VCOM_CALLTYPE RunWorksheetSelectFunctionLayout(bool forUseInDatabase, TXString& inoutSelection, EWorksheetSelectFunctionLayoutMode mode) override { return false; }

		virtual Handle			VCOM_CALLTYPE CompileCriteriaExpression(const TXString& criteria, std::function<void(ECriteriaExpressionError err, size_t errOffset)> onErrorCallback, EExpressionContext context) override { return nullptr; }
		virtual bool			VCOM_CALLTYPE DecompileCriteriaExpression(Handle compiledCriteria, TXString& outCriteria) override { return false; }
		virtual bool			VCOM_CALLTYPE ExecWSExpression(MCObjectHandle h, Handle compiledExpression, VWVariant& outResult) override { return false; }

		virtual bool			VCOM_CALLTYPE ExecQTOFunction(MCObjectHandle h, EQTOFunction function, const TXString& option, VWVariant& outResult) override { return false; }
		virtual bool			VCOM_CALLTYPE ExecQTOFunction(MCObjectHandle h, EQTOFunction function, const TXString& option, std::vector<VWVariant>& args, VWVariant& outResult) override { return false; }

		virtual void			VCOM_CALLTYPE ForEachObjectInCriteria(const TXString& criteria, std::function<void(MCObjectHandle h)> callback) override { }

		virtual void			VCOM_CALLTYPE SplitNurbsCurveByPoint(MCObjectHandle h, const WorldPt3& pt3, bool killOriginal, bool insert, TVWArray_MCObjectHandle & hResultArray) override {}
		
		//This function shows the MoveSymbolDlg dialog with the input folder preset. If the input is null ActSymbolLayer will be used.
		virtual void			VCOM_CALLTYPE ShowCreateSymbolSelectFolderDlg(MCObjectHandle& hInOutFolder) override {}
        
        virtual bool            VCOM_CALLTYPE TagSubObjectAsPart(MCObjectHandle h, const TXString& partTypeName, const Sint32 dataID = 0, const TXString& instanceUniqueName = "") override { return false;};
        virtual bool            VCOM_CALLTYPE SetPartInstanceUniqueName(MCObjectHandle h, const TXString& instanceUniqueName) override { return false;};
        virtual bool            VCOM_CALLTYPE SetPartDataID(MCObjectHandle h, const Sint32 dataID) override { return false;};
        virtual bool            VCOM_CALLTYPE RemovePartTag(MCObjectHandle h) override { return false;};
        virtual bool            VCOM_CALLTYPE IsSubObjectTaggedAsPart(MCObjectHandle h) override { return false;};
        virtual bool            VCOM_CALLTYPE GetPartTypeName(MCObjectHandle h, TXString& partTypeName) override { return false;};
        virtual bool            VCOM_CALLTYPE GetPartInstanceUniqueName(MCObjectHandle h, TXString& instanceUniqueName) override { return false;};
        virtual bool            VCOM_CALLTYPE GetPartDataID(MCObjectHandle h, Sint32& dataID) override { return false;};
        virtual bool            VCOM_CALLTYPE GetPartInfo(MCObjectHandle h, TXString& partTypeName, Sint32& dataID, TXString& instanceUniqueName) override { return false;};

		// Appends hSourceNurbs to hDestNurbs
		virtual void			VCOM_CALLTYPE AppendNurbsCurves(MCObjectHandle hSourceNurbs, MCObjectHandle hDestNurbs) override {}

		// Checks if two PieceWiseNurbsCurves are intersecting and returns the intersection points as output parameter
		virtual bool			VCOM_CALLTYPE AreNurbsIntersecting(MCObjectHandle hNurbs1, MCObjectHandle hNurbs2, TVWArray_WorldPt3& outIntersPts) override { return false; }


		virtual MCObjectHandle	VCOM_CALLTYPE GetCustomObjectSecondProfileGroup(MCObjectHandle inhObject) override { return nullptr; }
		virtual Boolean			VCOM_CALLTYPE SetCustomObjectSecondProfileGroup(MCObjectHandle inhObject, MCObjectHandle inhSecondProfileGroup) override { return false; }

		virtual bool			VCOM_CALLTYPE EvalWithCriteria(MCObjectHandle hObj, Handle compiledCriteria) override { return false; }
		virtual void			VCOM_CALLTYPE EvalWithCriteria(const std::vector<MCObjectHandle>& arrInputObjs, Handle compiledCriteria, std::vector<MCObjectHandle>& outMatchedObjects) override {}
		
		virtual Boolean 		VCOM_CALLTYPE SetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TGSColorV2 color) override { return false; };
		virtual Boolean 		VCOM_CALLTYPE SetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TGSColorV2 color) override { return false; };
		virtual Boolean 		VCOM_CALLTYPE GetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TGSColorV2& color) override { return false; };
		virtual Boolean 		VCOM_CALLTYPE GetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TGSColorV2& color) override { return false; };
		
		virtual void 			VCOM_CALLTYPE SetColorButton(Sint32 dialogID, Sint32 itemID, const TGSColorV2& color) override {};
		virtual void 			VCOM_CALLTYPE GetColorButton(Sint32 dialogID, Sint32 itemID, TGSColorV2& color) override {};

		virtual bool			VCOM_CALLTYPE AddToolFaceHighlightingPoly3D(MCObjectHandle polyID) override { return false; }

		virtual void			SetRadioButtonModeValue(Sint32 modeGroupID, Sint32 value, const TXStringArray& imageSpecs) override {}
		
		virtual bool			VCOM_CALLTYPE SetCustomObjectWallClosureGroup( MCObjectHandle objectHand, MCObjectHandle hGeomGroup ) override { return false; };
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallClosureGroup( MCObjectHandle h ) override { return nullptr; };
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallClosureGroupDeep( MCObjectHandle h ) override { return nullptr; };

		// Applying texture to faces of primitive objects like Extrude, Sweep, Solid, Tapered Extrude and Extrude Along Path
		virtual void			VCOM_CALLTYPE SetFaceTextureForPrimitiveObject(MCObjectHandle hObject, const SFaceTextureInfo& faceTextureInfo) override {}
		// Getting face texture for primitive objects like Extrude, Sweep, Solid, Tapered Extrude and Extrude Along Path
		virtual bool			VCOM_CALLTYPE GetFaceTextureForPrimitiveObject(MCObjectHandle hObject, SFaceTextureInfo& faceTextureInfo) override { return false; }

		virtual void 			VCOM_CALLTYPE CreatePluginStyle(MCObjectHandle hObj) override {};

		//Reset bounds of symbol with calculated linked texts
		virtual void			VCOM_CALLTYPE ClearLinkedTextBounds(MCObjectHandle hSymbol) override {}
		
		virtual bool			VCOM_CALLTYPE GetListBrowserItemHatchRefNumber(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, InternalIndex &liRefNumber) override { return false; }
		virtual bool			VCOM_CALLTYPE SetListBrowserItemHatchRefNumber(Sint32 dialogID, Sint32 componentID, int itemIndex, int iSubItemIndex, InternalIndex liRefNumber) override { return false; }

		virtual bool			VCOM_CALLTYPE GetListBrowserItemMarkerChoice(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, MarkerType& style, Sint8& angle, double& size, double& width, Uint8& thicknessBasis, double& thickness) override { return false; }
		virtual bool			VCOM_CALLTYPE SetListBrowserItemMarkerChoice(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, MarkerType style, Sint8 angle, double size, double width, Uint8 thicknessBasis, double thickness) override { return false; }
		virtual bool			VCOM_CALLTYPE GetListBrowserItemMarkerByClass(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool& bByClass) override { return false; }
		virtual bool			VCOM_CALLTYPE SetListBrowserItemMarkerByClass(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool bByClass) override { return false; }

		// Returns true if h supports 3D rotation. 
		virtual bool			VCOM_CALLTYPE CanFreelyTransformObject( MCObjectHandle h ) override { return false; };

		// Changes nurbs point from smooth to corner or from corner to smooth
		virtual void			VCOM_CALLTYPE ChangeNurbsPointType(MCObjectHandle hNurbs, Sint16 pointIndex) override {}

		virtual void			VCOM_CALLTYPE NurbsInsertPtAtIndex(MCObjectHandle hNurbs, Sint16 atIndex, const WorldPt3& point) override {}
		virtual double			VCOM_CALLTYPE GetNurbsLength(MCObjectHandle hNurbs) override { return 0; }

		virtual bool			VCOM_CALLTYPE GetShowListBrowserItemMarkerByClass(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool& bShowByClass) override { return false; }
		virtual bool			VCOM_CALLTYPE ShowListBrowserItemMarkerByClass(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool bShowByClass) override { return false; }
		virtual bool			VCOM_CALLTYPE GetShowListBrowserItemMarkerEditList(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool& bShowEditList) override { return false; }
		virtual bool			VCOM_CALLTYPE ShowListBrowserItemMarkerEditList(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, bool bShowEditList) override { return false; }

		virtual bool			VCOM_CALLTYPE GetWebPaletteVisibility(const VWIID& iidWebPalette) override { return false; }
		virtual bool			VCOM_CALLTYPE SetWebPaletteVisibility(const VWIID& iidWebPalette, bool visible) override { return false; }

		virtual MCObjectHandle	VCOM_CALLTYPE GetWallAtPoint( const WorldPt& point ) override { return nullptr; }

		virtual void			VCOM_CALLTYPE GetSimpleMaterialsRefNumbers(MCObjectHandle hMaterial, std::vector<RefNumber>& outData) override {}

		virtual InsertModeType	VCOM_CALLTYPE GetWallInsertLocation(MCObjectHandle hObject) override { return kSymInsertOnCenter; }
		virtual bool			VCOM_CALLTYPE SetWallInsertLocation(MCObjectHandle hObject, InsertModeType insertLocation) override { return false; }
		virtual WorldCoord		VCOM_CALLTYPE GetWallInsertLocationOffset(MCObjectHandle hObject) override { return 0.0; }
		virtual bool			VCOM_CALLTYPE SetWallInsertLocationOffset(MCObjectHandle hObject, WorldCoord insertLocationOffset) override { return false; }
		virtual bool			VCOM_CALLTYPE GetUseWallClosure(MCObjectHandle hObject) override { return false; }
		virtual bool			VCOM_CALLTYPE SetUseWallClosure(MCObjectHandle hObject, bool useWallClosure) override { return false; }
		virtual bool			VCOM_CALLTYPE GetWallInsertLocationByStyle(MCObjectHandle hObject) override { return false; }
		virtual bool			VCOM_CALLTYPE SetWallInsertLocationByStyle(MCObjectHandle hObject, bool byStyle) override { return false; }
		virtual bool			VCOM_CALLTYPE GetWallInsertLocationOffsetByStyle(MCObjectHandle hObject) override { return false; }
		virtual bool			VCOM_CALLTYPE SetWallInsertLocationOffsetByStyle(MCObjectHandle hObject, bool byStyle) override { return false; }
		virtual bool			VCOM_CALLTYPE GetUseWallClosureByStyle(MCObjectHandle hObject) override { return false; }
		virtual bool			VCOM_CALLTYPE SetUseWallClosureByStyle(MCObjectHandle hObject, bool byStyle) override { return false; }

		virtual bool			VCOM_CALLTYPE GetObjectWallInsertLocationOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord &insertLocationOffset) override { return false; }
		virtual bool			VCOM_CALLTYPE SetObjectWallInsertLocationOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord insertLocationOffset) override { return false; }

		virtual bool			VCOM_CALLTYPE GetWallHoleObjectIgnoreClosure(MCObjectHandle object) override { return false; }
		virtual void			VCOM_CALLTYPE SetWallHoleObjectIgnoreClosure(MCObjectHandle object, bool ignoreClosure) override {}
		
		virtual void			VCOM_CALLTYPE SetObjectClassN(MCObjectHandle h, InternalIndex classID, bool descendIntoGroup) override {}

		virtual bool			VCOM_CALLTYPE ShowCriteriaDialog(TXString& inOutCriteria, bool showObjectsCount) override { return false; }

		// For BuildResourceListFromOpenFileN, the fileRef can be obtained from GetOpenFilesList. The fileRef will always be non-negative for open files.
		virtual Sint32			VCOM_CALLTYPE BuildResourceListFromOpenFileN(short objectType, size_t fileRef, bool sort, Sint32& numItems) override { return 0; }

		// VW 2023
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE MirrorObjectN(MCObjectHandle h, bool dup, const WorldPt& axisStart, const WorldPt& axisEnd, bool preserveMatrix = true) override { return nullptr; }

		virtual void			VCOM_CALLTYPE AddToolSearchablePullDownMenuMethod(const TXString& label) override {}
		virtual void			VCOM_CALLTYPE AddSearchablePullDownMenuStaticChoice(short group, const TXString& idName, const TXString& text, const TXString& toolTip, const TXString& iconSpec) override {}
		virtual void			VCOM_CALLTYPE AddSearchablePullDownMenuItem(short group, const TXString& idName, const TXString& text, const TXString& toolTip, const TXString& iconSpec) override {}
		virtual void			VCOM_CALLTYPE AddSearchablePullDownMenuChildItem(short group, const TXString& idName, const TXString& text, const TXString& parentIdName, const TXString& toolTip, const TXString& iconSpec) override {}
		virtual void			VCOM_CALLTYPE SetSearchablePullDownMenuSelection(short group, const TXString& id) override {}
		virtual TXString		VCOM_CALLTYPE GetSearchablePullDownMenuSelectedID(short group) override { return ""; }
		virtual void			VCOM_CALLTYPE ClearSearchablePullDownMenu(short group) override {}
		virtual void			VCOM_CALLTYPE ClearSearchablePullDownMenuStaticChoices(short group) override {}
		virtual bool			VCOM_CALLTYPE CoordToSIAString(WorldCoord value, VectorWorks::Units::IVWUnits* dimUnit, bool alwaysMeters, TXString& outCentimeters, TXString& outMillimeters) override { return false; }
		virtual bool			VCOM_CALLTYPE CoordToSIAString(WorldCoord value, bool alwaysMeters, TXString& outCentimeters, TXString& outMillimeters) override { return false; }
		virtual bool			VCOM_CALLTYPE FormatTextObjectInSIA(MCObjectHandle hText, const TXString& centimeters, const TXString& millimeters) override { return false; }
		virtual bool			VCOM_CALLTYPE FormatTextObjectSegmentInSIA(MCObjectHandle hText, size_t startIndex, size_t countChars) override { return false; }

		virtual bool			VCOM_CALLTYPE SetStaticTextColorN(Sint32 dialogID, Sint32 itemID, EUiControlTextTint tint) override { return false; }
		virtual void			VCOM_CALLTYPE HierarchicalListBrowserItemOpened(Sint32 dialogID, Sint32 componentID, short itemIndex, Boolean recursive, short& outNumbRedisplayedItems, TXStringArray& redisplayedItemNames) override {}

		virtual VWIID			VCOM_CALLTYPE GetImporterIID(const TXString& fileExt) override { VWIID compare; compare.SetToNULL(); return compare; }
		virtual void			VCOM_CALLTYPE SetPIOTextStyle( MCObjectHandle ioParametricObj, const RefNumber textStyleRef, bool copyStyleSettings = true) override {}
		virtual void			VCOM_CALLTYPE SetIsRunningLongActivity(bool isRunningLongActivity) override {}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateStoryWithUI() override { return nullptr; }

		virtual TVWArray_InternalIndex	VCOM_CALLTYPE GetWorksheetSubrowObjects(MCObjectHandle hWorksheet, Sint16 row, Sint16 subrow) override { return TVWArray_InternalIndex(); }
		virtual void			VCOM_CALLTYPE SelectWorksheetSubrow(MCObjectHandle hWorksheet, Sint16 row, Sint16 subrow) override {}

		virtual bool			VCOM_CALLTYPE GetObjectTopPlanBounds(MCObjectHandle h, WorldRectVerts& outBoxVerts) override { return false; }

		virtual short						VCOM_CALLTYPE GetInsertLocationComponent(MCObjectHandle object) override { return 0; }
		virtual void						VCOM_CALLTYPE SetInsertLocationComponent(MCObjectHandle object, short componentIndex) override {}
		virtual EComponentInsertLocation	VCOM_CALLTYPE GetComponentInsertLocation(MCObjectHandle object) override { return eComponentInsertLocation_none; }
		virtual void						VCOM_CALLTYPE SetComponentInsertLocation(MCObjectHandle object, EComponentInsertLocation insertLocation) override {}
		virtual WorldCoord					VCOM_CALLTYPE GetComponentInsertLocationOffset(MCObjectHandle object) override { return 0.0; }
		virtual void						VCOM_CALLTYPE SetComponentInsertLocationOffset(MCObjectHandle object, WorldCoord insertLocationOffset) override {}

		virtual WorldCoord		VCOM_CALLTYPE GetWallPerpendicularOffsetFromInsertData(MCObjectHandle wall, InsertModeType insertLocation, WorldCoord insertLocationOffset) override { return 0.0; }
		virtual bool			VCOM_CALLTYPE GetObjectWallPerpendicularOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord &perpendicularOffset) override { return false; }

		virtual void			VCOM_CALLTYPE GetWallClosureInfo(MCObjectHandle wall, WallClosureInfo &wallClosureInfo) override {}
		virtual bool			VCOM_CALLTYPE GetObjectWallClosureInfo(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WallClosureInfo &wallClosureInfo) override { return false; }

		virtual void			VCOM_CALLTYPE GetExcludeWallClosureFromSettings(MCObjectHandle hObject, bool &left, bool &right, bool &top, bool &bottom) override {}
		virtual bool			VCOM_CALLTYPE SetExcludeWallClosureFromSettings(MCObjectHandle hObject, bool left, bool right, bool top, bool bottom) override { return false; }
		virtual bool			VCOM_CALLTYPE GetExcludeWallClosureFromSettingsByStyle(MCObjectHandle hObject) override { return false; }
		virtual bool			VCOM_CALLTYPE SetExcludeWallClosureFromSettingsByStyle(MCObjectHandle hObject, bool byStyle) override { return false; }

		virtual WallClosureGeometryInfo		VCOM_CALLTYPE GetWallClosureGeometryInfo(MCObjectHandle hObject, WorldCoord planHeight, bool usePlugInObjectOptionsPlanCutHeight=false) override { return {}; };

		virtual bool			VCOM_CALLTYPE GetIsObjectGimbalLocked(MCObjectConstHandle hObject) override { return false; };
		virtual void			VCOM_CALLTYPE SetIsObjectGimbalLocked(MCObjectHandle hObject, bool gimbalLocked) override {};
        virtual MCObjectHandle    VCOM_CALLTYPE CreatePolylineWithCornerVerticesAddedToArcCurves(MCObjectHandle polyline)  override { return nullptr; }
		
		virtual WorldCoord VCOM_CALLTYPE ObjSurfaceAreaInWorldCoords(MCObjectHandle h) override { return 0.0; }
		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectSecondPath(MCObjectHandle objectHand) override { return nullptr; }
		virtual void			VCOM_CALLTYPE GenerateSourceTracked2DRepresentation(const std::vector<MCObjectHandle>& solids, TStandardView view, WorldCoord cutPlaneCoordinate, std::unordered_map<MCObjectHandle, MCObjectHandle>& outCrossSectionFills, std::unordered_multimap<MCObjectHandle, MCObjectHandle>& outCrossSectionLinework, std::unordered_map<MCObjectHandle, MCObjectHandle>& outHiddenLineFills, std::unordered_multimap<MCObjectHandle, MCObjectHandle>& outHiddenLineLinework) override {}
	
		// VW 2024
	public:
		virtual void			VCOM_CALLTYPE CreateBorderlessButton(Sint32 dialogID, Sint32 itemID, const TXString& name, const TXString& iconRecPath, const bool isToggleButton = false, const EButtonImagePos imagePos = EButtonImagePos::kImageAbove) override {}
		virtual void			VCOM_CALLTYPE CreateBorderlessMenuButton(Sint32 dialogID, Sint32 itemID, const TXString& name, const TXString& iconResPath) override {}

		virtual void			VCOM_CALLTYPE EnableTreeControlMultiSelection(Sint32 nDialogID, Sint32 nComponentID, bool enabled = true) override {}
		virtual void			VCOM_CALLTYPE TrackNodeChange(MCObjectHandle handle, const TXString& changeName /*= NULLSTR*/) override {};
		virtual bool			VCOM_CALLTYPE GetCurrentWorldSpaceToolPoint(WorldPt3& locPos) override { return false; };
		
		// This call assumes an Undo Event has been started
		// If object belongs to Referenced Layer, it assumes user is okay to make it active
		virtual bool 			VCOM_CALLTYPE ShowAndSelectObject( MCObjectHandle hObj ) override { return false; }

	// VW2024
	public:
		virtual TEditContext	VCOM_CALLTYPE CreateEditContext(MCObjectHandle h) override { return nullptr; }
		virtual Boolean			VCOM_CALLTYPE SetListBrowserItemResourceContent(Sint32 dialogID, Sint32 componentID, int itemIndex, int iSubItemIndex, VectorWorks::Extension::IResourceManagerContent* content) override { return false; }


		virtual Boolean			VCOM_CALLTYPE GetViewportStyle(MCObjectHandle h, InternalIndex &viewportStyle) override { return false; }
		virtual Boolean			VCOM_CALLTYPE SetViewportStyle(MCObjectHandle h, InternalIndex viewportStyle) override { return false; }



		virtual Boolean			VCOM_CALLTYPE GetListBrowserItemIndentLevel(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 iSubItemIndex, short& indentLevel) override { return false; }
		virtual Boolean			VCOM_CALLTYPE SetListBrowserItemIndentLevel(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 iSubItemIndex, short indentLevel) override { return false; }

		virtual void			VCOM_CALLTYPE GetScreenFullSize(ViewRect& out) {  }
		
		virtual InternalIndex		VCOM_CALLTYPE GetActiveClass() override { return 0; }
		virtual ObjectColorType		VCOM_CALLTYPE GetActiveColors() override { return ObjectColorType(); };
		virtual InternalIndex		VCOM_CALLTYPE GetActiveFillPat() override { return 0; }
		virtual OpacityRef			VCOM_CALLTYPE GetActiveOpacity() override { return 0; }
		virtual ObjectLineType		VCOM_CALLTYPE GetActivePenFont() override { return ObjectLineType(); };
		virtual Boolean				VCOM_CALLTYPE GetActiveArrowByClass() override { return false; };
		virtual Boolean				VCOM_CALLTYPE GetActiveFColorsByClass() override { return false; };
		virtual Boolean				VCOM_CALLTYPE GetActiveFPatByClass() override { return false; };
		virtual Boolean				VCOM_CALLTYPE GetActiveLWByClass() override { return false; };
		virtual Boolean				VCOM_CALLTYPE GetActivePColorsByClass() override { return false; };
		virtual Boolean				VCOM_CALLTYPE GetActivePPatByClass() override { return false; };
		virtual Boolean				VCOM_CALLTYPE GetActiveOpacityByClass() override { return false; };
		virtual Boolean				VCOM_CALLTYPE GetActiveDropShadowByClass() override { return false; };
		virtual Boolean				VCOM_CALLTYPE GetActivePenOpacityByClass() override { return false; };
		virtual Boolean				VCOM_CALLTYPE GetActiveFillOpacityByClass() override { return false; };

		virtual bool			VCOM_CALLTYPE CoordToSIAStringN(WorldCoord value, VectorWorks::Units::IVWUnits* dimUnit, bool alwaysMeters, TXString& outCentimeters, TXString& outMillimeters) { return false; }
		virtual void			VCOM_CALLTYPE DoubleToStringN(TNumStyleClass inNumStyle,  Byte inAccuracy, Byte inFormat, double_param inDouble, TXString& outString) {}
		virtual void			VCOM_CALLTYPE DoubleToStringInUnitsN(TNumStyleClass inNumStyle, Byte inAccuracy, Byte inFormat, double_param inDouble, VectorWorks::Units::IVWUnits* dimUnit, TXString& outString) {}

		virtual	Boolean 		VCOM_CALLTYPE CreateDataVisualizationPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar, bool bShowDefaultStaticItems /*= true*/) { return false; };
        
        virtual void            VCOM_CALLTYPE CreateSortedContourCurves(MCObjectHandle h, const WorldPt3 & pointOnPlane, const WorldPt3 & planeNormal, TMCObjectHandlesSTLArray    & outBoundariesArray, TMCObjectHandlesSTLArray    & outHolesArray) {}


		virtual MCObjectHandle	VCOM_CALLTYPE CreateSectionViewport(const WorldPt& sectionLinePt1, const WorldPt& sectionLinePt2, const WorldPt& sectionLinePt3, double depth, double startHeight, double endHeight, MCObjectHandle hVPLayer) { return nullptr; }

		virtual bool			VCOM_CALLTYPE GetAppParameter(size_t paramIndex, TXString& outValue) override { return false; }

		virtual bool			VCOM_CALLTYPE EnableListBrowserDragOnIndices(Sint32 liDialogID, Sint32 liComponentID, const std::vector<bool>& arrIndicesDragEnableState) { return false; }

		virtual MCObjectHandle	VCOM_CALLTYPE CreateSingleOffsetPoly(MCObjectHandle hPoly, double offset) override { return nullptr; }

		virtual GSColor			VCOM_CALLTYPE GetControlTextColorByTint(EUiControlTextTint tint) { return GSColor(); }

		virtual bool	VCOM_CALLTYPE IsActiveFileChangedAfterLastSave() override { return false; }
		// Saves the active file. If the file was not saved before this will show a file chooser dialog to let the user select the file location and name.
		virtual bool	VCOM_CALLTYPE SaveActiveFile() override { return false; }
	};
}
