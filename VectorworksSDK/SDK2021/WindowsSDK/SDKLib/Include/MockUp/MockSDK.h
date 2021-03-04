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
		virtual Boolean VCOM_CALLTYPE GetClassBeginningMarker(InternalIndex index, SMarkerStyle& mstyle)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetClassEndMarker(InternalIndex index, SMarkerStyle& mstyle)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetClColor(InternalIndex index, ObjectColorType& color)
		{
			return;
		}
		virtual InternalIndex VCOM_CALLTYPE GetClFillPat(InternalIndex index)
		{
			return -1;
		}
		virtual short VCOM_CALLTYPE GetClLineWeight(InternalIndex index)
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetClMarker(InternalIndex index, MarkerType& style, short& size, short& angle)
		{
	
		}

		virtual Boolean VCOM_CALLTYPE GetClUseGraphic(InternalIndex index)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetClVisibility(InternalIndex index)
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE GetVPClassFillStyle(MCObjectHandle viewport, InternalIndex classIndex)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE SetClassBeginningMarker(InternalIndex index, SMarkerStyle mstyle)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE SetClassEndMarker(InternalIndex index, SMarkerStyle mstyle)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetClColor(InternalIndex index, ObjectColorType color)
		{
	
		}
		virtual void VCOM_CALLTYPE SetClFillPat(InternalIndex index, InternalIndex fill)
		{
	
		}
		virtual void VCOM_CALLTYPE SetClLineWeight(InternalIndex index, short mils)
		{
	
		}
		virtual void VCOM_CALLTYPE SetClMarker(InternalIndex index, MarkerType style, short size, short angle)
		{
	
		}

		virtual void VCOM_CALLTYPE SetClUseGraphic(InternalIndex index, Boolean use)
		{
	
		}
		virtual void VCOM_CALLTYPE SetClVisibility(InternalIndex index, short vis)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE VPClassHasOverride(MCObjectHandle viewport, InternalIndex classIndex)
		{
			return false;	
		}
		virtual Boolean VCOM_CALLTYPE DeleteAllDLComponents()
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteDLComponent(Sint16 index)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultArrowByClass()
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetDefaultArrowHeads(Boolean& starting, Boolean& ending, ArrowType& style, short& size)
		{
	
		}
		virtual void VCOM_CALLTYPE GetDefaultArrowHeadsN(Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultBeginningMarker(SMarkerStyle& mstyle, Boolean& visibility)
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetDefaultClass()
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetDefaultColors(ObjectColorType& colors)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultEndMarker(SMarkerStyle& mstyle, Boolean& visibility)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultFColorsByClass()
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetDefaultFillPat()
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultFPatByClass()
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetDefaultHatch()
		{
			return NULL;
		}
		virtual short VCOM_CALLTYPE GetDefaultLineWeight()
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultLWByClass()
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultPColorsByClass()
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetDefaultPPatByClass()
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentClass(Sint16 index, Sint32 &componentClass)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentFill(Sint16 index, Sint32 &fill)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentFillColors(Sint16 index, ColorRef &fillForeColor, ColorRef &fillBackColor)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentName(Sint16 index, TXString& outComponentName)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentPenColors(Sint16 index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetDLComponentPenWeights(Sint16 index, Uint8 &penWeightLeft, Uint8 &penWeightRight)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentUseFillClassAttr(Sint16 index, Boolean &useClassAttr)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentUsePenClassAttr(Sint16 index, Boolean &leftPenUseClassAttr, Boolean &rightPenUseClassAttr)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDLComponentWidth(Sint16 index, WorldCoord &width)
		{
			return false;
		}
		virtual WorldCoord VCOM_CALLTYPE GetDLControlOffset()
		{
			return 0.0;
		}
		virtual Sint16 VCOM_CALLTYPE GetDLOptions()
		{
			return -1;
		}
		virtual WorldCoord VCOM_CALLTYPE GetDLSeparation()
		{
			return 0.0;
		}
		virtual InternalIndex VCOM_CALLTYPE GetDocumentDefaultSketchStyle()
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetNumberOfDLComponents(short& numComponents)
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetObjectInternalIndex(MCObjectHandle h)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetProgramVariable(short variableSelector, void* result)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetWallPrefStyle(InternalIndex& wallStyleNum)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetWallStyle(MCObjectHandle theWall, InternalIndex& wallStyle)
		{
			return false;
		}

		virtual void VCOM_CALLTYPE SetDefaultArrowByClass()
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultArrowHeads(Boolean starting, Boolean ending, ArrowType style, short size)
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultArrowHeadsN(Boolean starting, Boolean ending, ArrowType style, double_param size)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDefaultBeginningMarker(SMarkerStyle mstyle, Boolean visibility)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDefaultClass(InternalIndex classID)
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultColors(ObjectColorType colors)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDefaultEndMarker(SMarkerStyle mstyle, Boolean visibility)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDefaultFColorsByClass()
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultFillPat(InternalIndex theFill)
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultFPatByClass()
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDefaultHatch(MCObjectHandle inHatchDef)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDefaultLineWeight(short mils)
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultLWByClass()
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultPColorsByClass()
		{
	
		}

		virtual void VCOM_CALLTYPE SetDefaultPPatByClass()
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultWallThickness(WorldCoord thickness)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentClass(Sint16 index, Sint32 componentClass)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentFill(Sint16 index, Sint32 fill)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentFillColors(Sint16 index, ColorRef fillForeColor, ColorRef fillBackColor)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentName(Sint16 index, const TXString& componentName)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentPenColors(Sint16 index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE SetDLComponentPenWeights(Sint16 index, Uint8 penWeightLeft, Uint8 penWeightRight)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentUseFillClassAttr(Sint16 index, Boolean useClassAttr)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentUsePenClassAttr(Sint16 index, Boolean leftPenUseClassAttr, Boolean rightPenUseClassAttr)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDLComponentWidth(Sint16 index, WorldCoord width)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDLControlOffset(WorldCoord controlOffset)
		{

		}
		virtual void VCOM_CALLTYPE SetDLOptions(Sint16 options)
		{
	
		}
		virtual void VCOM_CALLTYPE SetDLSeparation(WorldCoord separation)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetDocumentDefaultSketchStyle(InternalIndex sketchIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetProgramVariable(short variableSelector, const void* value)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallPrefStyle(InternalIndex wallStyleNum)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE WrapGetDefaultWallThickness(double_gs& outCoordLen)
		{
	
		}
		virtual void VCOM_CALLTYPE Add3DVertex(MCObjectHandle h, const WorldPt3& v, Boolean recalcBounds)
		{
	
		}
		virtual void VCOM_CALLTYPE AddVertex(MCObjectHandle h, const WorldPt& p, VertexType t, WorldCoord arcRadius, Boolean recalcBounds)
		{
	
		}
		virtual void VCOM_CALLTYPE CalcAreaN(MCObjectHandle h, double_gs& area)
		{
	
		}
		virtual void VCOM_CALLTYPE CalcPerimN(MCObjectHandle h, double_gs& perim)
		{
	
		}
		virtual double_gs VCOM_CALLTYPE CalcSurfaceArea(MCObjectHandle h)
		{
			return 0.0;

		}
		virtual double_gs VCOM_CALLTYPE CalcVolume(MCObjectHandle h)
		{
			return 0.0;
		}
		virtual Boolean VCOM_CALLTYPE Centroid3D(MCObjectHandle h, double_gs &xCG, double_gs &yCG, double_gs &zCG)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE CountVertices(MCObjectHandle h)
		{
			return 0;
	
		}
		virtual short VCOM_CALLTYPE CreateSkylight(MCObjectHandle object)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE DeleteVertex(MCObjectHandle h, short vertexNum)
		{
	
		}
		virtual void VCOM_CALLTYPE ForEach3DPointInObject(MCObjectHandle h, GS_3DPointIteratorProcPtr proc, void* env)
		{
	
		}
		virtual void VCOM_CALLTYPE ForEachPolyEdge( MCObjectHandle inPolyH, GS_ForEachPolyEdgeProcPtr inProc, void* inEnv)
		{
	
		}
		virtual void VCOM_CALLTYPE Get3DVertex(MCObjectHandle h, short vertexNum, WorldPt3& vertex)
		{
	
		}
		virtual void VCOM_CALLTYPE GetArcInfoN(MCObjectHandle h, double_gs& startAngle, double_gs& sweepAngle, WorldPt& center, WorldCoord& radiusX, WorldCoord& radiusY)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetBatAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, WorldCoord& topWidth, WorldCoord& baseHeight, double_gs& topSlope, WorldCoord& controlPoint)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetControlVertex(MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetDormerAttributes(MCObjectHandle object, const short dormerID, short& edgeIndex, WorldCoord& cornerOffset, Boolean& isPerpOffset, WorldCoord& perpOrHeightOffset, InternalIndex& symName, Boolean& centerSymbol, WorldCoord& symOffset)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetEndPoints(MCObjectHandle h, WorldPt& startPt, WorldPt& endPt)
		{
	
		}
		virtual void VCOM_CALLTYPE GetEntityMatrix(MCObjectHandle h, TransformMatrix& theMat)
		{
	
		}
		virtual void VCOM_CALLTYPE GetExtrudeValues(MCObjectHandle h, WorldCoord& bottom, WorldCoord& top)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetGableAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, WorldCoord& overhang)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetHipAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& frontSlope, WorldCoord& overhang)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetLocus3DPosition(MCObjectHandle h, WorldPt3& locPos)
		{
	
		}
		virtual void VCOM_CALLTYPE GetLocusPosition(MCObjectHandle h, WorldPt& locPos)
		{
	
		}
		virtual void VCOM_CALLTYPE GetMarkerPolys(MCObjectHandle object, MCObjectHandle& startMarkerPoly, MCObjectHandle& endMarkerPoly)
		{
	
		}
		virtual short VCOM_CALLTYPE GetNumRoofElements(MCObjectHandle object)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectBoundingBoxVerts(MCObjectHandle h, WorldRectVerts &outBoxVerts)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectBounds(MCObjectHandle h, WorldRect& bounds)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetObjectCube(MCObjectHandle h, WorldCube& boundsCube)
		{
	
		}
		virtual short VCOM_CALLTYPE GetPolyDirection(MCObjectHandle polyToCheck)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetPolyShapeClose(MCObjectHandle h)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetQArcQuadrant(MCObjectHandle h)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetRoofAttributes(MCObjectHandle object, Boolean& genGableWall, WorldCoord& bearingInset, WorldCoord& roofThick, short& miterType, WorldCoord& vertMiter)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetRoofElementType(MCObjectHandle object, const short dormerID, short& edgeIndex, Boolean& isDormer, short& dormerType)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetRRectDiameters(MCObjectHandle h, WorldCoord& xDiam, WorldCoord& yDiam)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetShedAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& topSlope, WorldCoord& overhang)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetSkylight(MCObjectHandle object, const short skylightID, short& edgeIndex, WorldCoord& cornerOffset, WorldCoord& perpOffset, InternalIndex& symName)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetSweepAnglesN(MCObjectHandle theSweep, double_gs& startAngle, double_gs& arcAngle, double_gs& incrAngle)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetTrapeziumAttributes(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, Boolean& useTopWidth, WorldCoord& topWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& topSlope)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetVertex(MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius)
		{
		}
		virtual void VCOM_CALLTYPE Insert3DVertex(MCObjectHandle h, const WorldPt3& p, short beforeVertex, Boolean recalcBounds)
		{
		}
		virtual void VCOM_CALLTYPE InsertVertex(MCObjectHandle h, const WorldPt& p, short beforeVertex, VertexType t, WorldCoord arcRadius, Boolean recalcBounds)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE Moments3D(MCObjectHandle h, double_gs &Ixx, double_gs &Iyy, double_gs &Izz)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsCurveEvaluatePoint(MCObjectHandle nurbsHandle, Sint32 index, double u, WorldPt3& pt)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE NurbsCurveGetNumPieces(MCObjectHandle nHandle)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE NurbsCurveType(MCObjectHandle nHandle, Sint32 index, bool& isByWeight)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE NurbsDegree(MCObjectHandle nHandle, Sint32 index)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE NurbsDelVertex(MCObjectHandle nHandle, Sint32 index1, Sint32 index2)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE NurbsGetNumPts(MCObjectHandle nHandle, Sint32 index)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE NurbsGetPt3D(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3& pt)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsGetWeight(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& weight)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsKnot(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& knot)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE NurbsNumKnots(MCObjectHandle nHandle, Sint32 index)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE NurbsSetKnot(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double knot)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsSetPt3D(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3 pt)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsSetWeight(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double weight)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NurbsSurfaceEvaluatePoint(MCObjectHandle nurbsHandle, double u, double v, WorldPt3& pt)
		{
			return false;
		}
		virtual double_gs VCOM_CALLTYPE ObjArea(MCObjectHandle h)
		{
			return 0.0;
		}
		virtual double_gs VCOM_CALLTYPE ObjSurfaceArea(MCObjectHandle h)
		{
			return 0.0;
		}
		virtual double_gs VCOM_CALLTYPE ObjVolume(MCObjectHandle h)
		{
			return 0.0;
		}
		virtual Boolean VCOM_CALLTYPE Products3D(MCObjectHandle h, double_gs &Ixy, double_gs &Iyz, double_gs &Izx)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RemoveRoofElement(MCObjectHandle object, short id)
		{
	
		}
		virtual void VCOM_CALLTYPE Set3DVertex(MCObjectHandle h, short vertexNum, const WorldPt3& vertex, Boolean recalcBounds)
		{
	
		}
		virtual void VCOM_CALLTYPE SetArcAnglesN(MCObjectHandle h, double_param startAngle, double_param sweepAngle)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetBatAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, WorldCoord topWidth, WorldCoord baseHeight, double_param topSlope, WorldCoord controlPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetDormerAttributes(MCObjectHandle object, const short dormerID, short edgeIndex, WorldCoord cornerOffset, Boolean isPerpOffset, WorldCoord perpOrHeightOffset, InternalIndex symName, Boolean centerSymbol, WorldCoord symOffset)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDormerThick(MCObjectHandle object, WorldCoord wallThick, WorldCoord roofThick)
		{
	
		}
		virtual void VCOM_CALLTYPE SetEndPoints(MCObjectHandle h, const WorldPt& startPt, const WorldPt& endPt)
		{
	
		}
		virtual void VCOM_CALLTYPE SetEntityMatrix(MCObjectHandle h, const TransformMatrix& theMat)
		{
	
		}
		virtual void VCOM_CALLTYPE SetExtrudeValues(MCObjectHandle h, WorldCoord bottom, WorldCoord top)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetGableAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, WorldCoord overhang)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetHipAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, double_param frontSlope, WorldCoord overhang)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetLocus3DPosition(MCObjectHandle h, const WorldPt3& locPos)
		{
	
		}
		virtual void VCOM_CALLTYPE SetLocusPosition(MCObjectHandle h, const WorldPt& locPos)
		{
	
		}
		virtual void VCOM_CALLTYPE SetObjectBounds(MCObjectHandle h, const WorldRect& bounds)
		{
	
		}
		virtual void VCOM_CALLTYPE SetPolyShapeClose(MCObjectHandle h, Boolean closed)
		{
	
		}
		virtual void VCOM_CALLTYPE SetQArcQuadrant(MCObjectHandle h, short quadrant)
		{
	
		}
		virtual void VCOM_CALLTYPE SetRoofAccessoriesParameters(MCObjectHandle roof, Boolean insertAttic, Boolean insertSoffit, Boolean insertFascia, WorldCoord fasciaWidth, WorldCoord fasciaHeight, WorldCoord atticHeight, WorldCoord recess, WorldCoord rakeThick, WorldCoord trimDepth)
		{
	
		}
		virtual void VCOM_CALLTYPE SetRoofAttributes(MCObjectHandle object, Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter)
		{
	
		}
		virtual void VCOM_CALLTYPE SetRRectDiameters(MCObjectHandle h, WorldCoord xDiam, WorldCoord yDiam)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetShedAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param topSlope, WorldCoord overhang)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetSkylight(MCObjectHandle object, const short skylightID, short edgeIndex, WorldCoord cornerOffset, WorldCoord perpOffset, InternalIndex symName)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetSweepAnglesN(MCObjectHandle theSweep, double_param startAngle, double_param arcAngle, double_param incrAngle)
		{
	
		}
		virtual void VCOM_CALLTYPE SetSweepScrew(MCObjectHandle theSweep, WorldCoord dist)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetTrapeziumAttributes(MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, Boolean useTopWidth, WorldCoord topWidth, double_param leftSlope, double_param rightSlope, double_param topSlope)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetVertex(MCObjectHandle h, short vertexNum, const WorldPt& vertex, VertexType vType, WorldCoord arcRadius, Boolean recalcBounds)
		{
	
		}
		virtual void VCOM_CALLTYPE WrapGetSweepScrew(MCObjectHandle theSweep, double_gs& outCoordLen)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCircularDimension(const WorldPt& center, const WorldPt& end, WorldCoord startOffset, WorldCoord textOffset, const WorldRect& box, Boolean isRadius)
		{
			return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetArrowByClass(MCObjectHandle h)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetArrowHeads(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, short& size)
		{
	
		}
		virtual void VCOM_CALLTYPE GetArrowHeadsN(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetColor(MCObjectHandle h, ObjectColorType& colors)
		{
			return false;
		}
		virtual OpacityRef VCOM_CALLTYPE GetDefaultOpacity()
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetDefaultOpacityByClass()
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFColorsByClass(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFillIAxisEndPoint(MCObjectHandle objectHandle, WorldPt& iAxisEndPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFillJAxisEndPoint(MCObjectHandle objectHandle, WorldPt& jAxisEndPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFillOriginPoint(MCObjectHandle objectHandle, WorldPt& originPoint)
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetFillPat(MCObjectHandle h)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetFillPoints(MCObjectHandle objectHandle, WorldPt& originPoint, WorldPt& iAxisEndPoint, WorldPt& jAxisEndPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetFPatByClass(MCObjectHandle h)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetLineWeight(MCObjectHandle h)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetLineWeightDisplayMM(short mils)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetLineWeightDisplayPt(short mils)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetLWByClass(MCObjectHandle h)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetMarker(MCObjectHandle obj, MarkerType& style, short& size, short& angle, Boolean& start, Boolean& end)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetObjBeginningMarker(MCObjectHandle h, SMarkerStyle& mstyle, Boolean& visibility)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjEndMarker(MCObjectHandle h, SMarkerStyle& mstyle, Boolean& visibility)
		{
			return false;
		}
		virtual OpacityRef VCOM_CALLTYPE GetOpacity(MCObjectHandle h)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetOpacityByClass(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetPColorsByClass(MCObjectHandle h)
		{
			return false;

		}

		virtual Boolean VCOM_CALLTYPE GetPPatByClass(MCObjectHandle h)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetVertexVis(MCObjectHandle h, short vertNum, Boolean& vis)
		{
	
		}
		virtual void VCOM_CALLTYPE SetArrowByClass(MCObjectHandle h)
		{
	
		}
		virtual void VCOM_CALLTYPE SetArrowHeads(MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, short size)
		{
	
		}
		virtual void VCOM_CALLTYPE SetArrowHeadsN(MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, double_param size)
		{
	
		}
		virtual void VCOM_CALLTYPE SetColor(MCObjectHandle h, ObjectColorType colors)
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultOpacity(OpacityRef inOpacity)
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultOpacityByClass()
		{
	
		}
		virtual void VCOM_CALLTYPE SetFColorsByClass(MCObjectHandle h)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetFillIAxisEndPoint(MCObjectHandle objectHandle, const WorldPt& iAxisEndPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetFillJAxisEndPoint(MCObjectHandle objectHandle, const WorldPt& jAxisEndPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetFillOriginPoint(MCObjectHandle objectHandle, const WorldPt& originPoint)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetFillPat(MCObjectHandle h, InternalIndex theFill)
		{
	
		}
		virtual void VCOM_CALLTYPE SetFPatByClass(MCObjectHandle h)
		{
	
		}
		virtual void VCOM_CALLTYPE SetLineWeight(MCObjectHandle h, short mils)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetLineWeightDisplayMM(short hundredths)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetLineWeightDisplayPt(short sixteenths)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetLWByClass(MCObjectHandle h)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetObjBeginningMarker(MCObjectHandle h, SMarkerStyle mstyle, Boolean visibility)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE SetObjEndMarker(MCObjectHandle h, SMarkerStyle mstyle, Boolean visibility)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetOpacity(MCObjectHandle h, OpacityRef  inNewOpacity)
		{
	
		}
		virtual void VCOM_CALLTYPE SetOpacityByClass(MCObjectHandle h)
		{
	
		}
		virtual void VCOM_CALLTYPE SetPColorsByClass(MCObjectHandle h)
		{
	
		}

		virtual void VCOM_CALLTYPE SetPPatByClass(MCObjectHandle h)
		{
	
		}
		virtual void VCOM_CALLTYPE SetVertexVis(MCObjectHandle h, short vertNum, Boolean vis)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateFillSpace(MCObjectHandle owner)
		{
			return NULL;
		}
		virtual short VCOM_CALLTYPE CountFillSpaces(MCObjectHandle h)
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetFillSpace(MCObjectHandle h, short index)
		{
			return NULL;
		}		
		virtual MCObjectHandle VCOM_CALLTYPE GetDefinition(MCObjectHandle h)
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE GetDXFColorToLineWeight(const short inDXFColorIndex)
		{
			return -1;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetNamedObject(const TXString& objName)
		{
				return NULL;
		}
		virtual InternalIndex VCOM_CALLTYPE GetObjectClass(MCObjectHandle h)
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetObjectName(MCObjectHandle h, TXString& outName)
		{
	
		}
		virtual short VCOM_CALLTYPE GetObjectType(MCObjectHandle h)
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetSymbolDefinitionIcon(MCObjectHandle theSymDef, Sint32 icon[32] )
		{
	
		}
		virtual short VCOM_CALLTYPE GetSymbolDefinitionType(MCObjectHandle theSymDef)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE IsLocked(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsSelected(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsVisible(MCObjectHandle h)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE LockObject(MCObjectHandle h, Boolean lock)
		{
	
		}
		virtual void VCOM_CALLTYPE SelectObject(MCObjectHandle h, Boolean select)
		{
	
		}
		virtual void VCOM_CALLTYPE SetDXFColorToLineWeight(const short inDXFColorIndex, const short inLineWeight)
		{
	
		}
		virtual void VCOM_CALLTYPE SetObjectClass(MCObjectHandle h, InternalIndex classID)
		{
	
		}
		virtual GSError VCOM_CALLTYPE SetObjectName(MCObjectHandle h, const TXString& name)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SetSymbolDefinitionIcon(MCObjectHandle theSymDef, const Sint32 icon[32] )
		{
	
		}
		virtual void VCOM_CALLTYPE SetVisibility(MCObjectHandle h, Boolean visible)
		{
	
		}
		virtual void VCOM_CALLTYPE AttachAuxObject(MCObjectHandle h, MCObjectHandle newOwner)
		{
	
		}
		virtual void VCOM_CALLTYPE DeleteAuxObject(MCObjectHandle h, MCObjectHandle owner)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE FindAuxObject(MCObjectHandle owner, short objectType)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE FindDataObject(MCObjectHandle owner, OSType tag)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE FirstAuxObject(MCObjectHandle h)
		{
				return NULL;
		}
		virtual OSType VCOM_CALLTYPE GetDataTag(MCObjectHandle h)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetPluginType(const TXString& name, EVSPluginType& type)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsPluginFormat(MCObjectHandle h)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE NewDataObject(MCObjectHandle attachTo, OSType tag, size_t objectSize)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE NextAuxObject(MCObjectHandle start, short objectType)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE NextDataObject(MCObjectHandle start, OSType tag)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE RemoveAuxObject(MCObjectHandle h, MCObjectHandle owner)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataCreate(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,int numDataElements)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataGet(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,int dataIndex, void* getData)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataGetNumElements(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,Sint32* getData)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataRemoveContainer(MCObjectHandle inOwnerObj,OSType dataContainer)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataRemoveTag(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TaggedDataSet(MCObjectHandle inOwnerObj,OSType dataContainer,int dataType,int dataTag,int dataIndex, const void* data)
		{
			return false;
		}
		virtual double_gs VCOM_CALLTYPE CoordLengthToPageLengthN(WorldCoord len)
		{
			return 0.0;
		}
		virtual double_gs VCOM_CALLTYPE CoordLengthToPagePoints(WorldCoord len)
		{
			return 0.0;
		}
		virtual Boolean VCOM_CALLTYPE CoordLengthToPixelLength(WorldCoord numCoords, short& numPixels)
		{
			return false;
		}
		virtual double_gs VCOM_CALLTYPE CoordLengthToUnitsLengthN(WorldCoord len)
		{
			return 0.0;
		}
		virtual double	VCOM_CALLTYPE CoordLenToPageLenScale(WorldCoord coordLength, double paperScale, double photographicScale)
		{
			return 0.0;
		}
		virtual double	VCOM_CALLTYPE CoordLenToPagePtsScale(WorldCoord coordLength, double paperScale, double photographicScale)
		{
			return 0.0;
		}
		virtual double	VCOM_CALLTYPE PageLenToCoordLenScale(double pageLength, double paperScale, double photographicScale)
		{
			return 0.0;
		}
		virtual double	VCOM_CALLTYPE PagePtsToCoordLenScale(double pagePoints, double paperScale, double photographicScale)
		{
			return 0.0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateOvalN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE DimStringToCoord(const TXString& s, WorldCoord& c)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE FPCoordLengthToPageLength(double_param coordLen, double_gs& pageLen)
		{
	
		}
		virtual void VCOM_CALLTYPE FPCoordLengthToUnitsLength(double_param coordLen, double_gs& unitsLen)
		{
	
		}
		virtual void VCOM_CALLTYPE ModelPt2DToScreenPt(WorldPt& vertex)
		{
	
		}
		virtual void VCOM_CALLTYPE ModelVecToScreenVec(WorldPt& vertex)
		{
	
		}
		virtual void VCOM_CALLTYPE PageLengthToFPCoordLength(double_param pageLen, double_gs& coordLen)
		{
	
		}
		virtual WorldCoord VCOM_CALLTYPE PagePointsToCoordLength(double_gs& points)
		{
			return 0.0;
		}
		virtual void VCOM_CALLTYPE PixelLengthToCoordLength(short numPixels, WorldCoord& numCoords)
		{
	
		}
		virtual void VCOM_CALLTYPE ScreenPtToModelPt2D(WorldPt& vertex)
		{
	
		}
		virtual void VCOM_CALLTYPE ScreenVecToModelVec(WorldPt& vertex)
		{
	
		}
		virtual void VCOM_CALLTYPE UnitsLengthToFPCoordLength(double_param unitsLen, double_gs& coordLen)
		{
	
		}
		virtual WorldCoord VCOM_CALLTYPE WorldCoordsPerDrawingUnit()
		{
			return 0.0;
		}
		virtual void VCOM_CALLTYPE WrapPageLengthToCoordLengthN(double_param len, double_gs& outCoordLen)
		{
	
		}
		virtual void VCOM_CALLTYPE WrapUnitsLengthToCoordLengthN(double_param len, double_gs& outCoordLen)
		{
	
		}
		virtual short VCOM_CALLTYPE AddSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE AppendRoofEdge(MCObjectHandle object, const WorldPt& edgePt, double_param slope, WorldCoord projection, WorldCoord eaveHeight)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE Create3DPoly()
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateAngleDimension(const WorldPt& center, const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateArcN(const WorldRect& bounds, double_param startAngle, double_param sweepAngle)
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateBatDormer(MCObjectHandle object)
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateChainDimension(MCObjectHandle h1, MCObjectHandle h2)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCombineIntoSurface(const WorldPt& inPoint)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCone(const WorldPt3& center, const WorldPt3 &tip, WorldCoord radius)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateContourCurves(MCObjectHandle h, double_param delta, WorldPt3 pointOnPlane, WorldPt3 planeNormal)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomDimensionStandard(const TXString& name)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObject(const TXString& name, const WorldPt& location, double_param angle, bool bInsert)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectByMatrix(const TXString& name, const TransformMatrix& matrix)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectDoubleClick(const TXString& name)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateCustomObjectPath(const TXString& name, MCObjectHandle pathHand, MCObjectHandle profileGroupHand)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateExtrude(WorldCoord bottom, WorldCoord top)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateExtrudeAlongPath(MCObjectHandle pathHandle, MCObjectHandle profileHandle)
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateGableDormer(MCObjectHandle object)
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateGroup()
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateHemisphere(const WorldPt3& center, const WorldPt3 &topPoint)
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateHipDormer(MCObjectHandle object)
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateImageProp(TXString& propName, InternalIndex textureRef, WorldCoord height, WorldCoord width, Boolean enforceImageAspectRatio, Boolean crossedPlanes, Boolean createPlugin, Boolean autoRotate, Boolean createSymbol)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateInterpolatedSurface(MCObjectHandle surfaceHandle, Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLayer(const TXString& layerName, short layerType)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLayerN(const TXString& name, double_param scale)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLightN(const WorldPt3& pos, short kind, Boolean isOn, double_param brightness, const WorldPt3& color, Boolean castShadows)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLine(const WorldPt& startPt, const WorldPt& endPt)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLinearDimension(const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset, WorldCoord textOffset, const Vector2& dir, short dimType)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLocus(const WorldPt& location)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLocus3D(const WorldPt3& location)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateLoftSurfaces(MCObjectHandle groupCurvesH, Boolean bRule, Boolean  bClose, Boolean bSolid)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateNurbsCurve(WorldPt3 firstPt, bool byCtrlPts, short degree)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateNurbsSurface(Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateOval(const WorldRect& bounds)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreatePolyshape()
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateQArc(const WorldRect& bounds, short quadrant)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRectangle(const WorldRect& bounds)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRectangleN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRoof(Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRoundWall(const WorldPt& startPt, const WorldPt& ptOnArc, const WorldPt& endPt, WorldCoord wallThickness)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRRectangle(const WorldRect& bounds, WorldCoord xDiam, WorldCoord yDiam)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateRRectangleN(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height, CBWorldCoord_param xDiam, CBWorldCoord_param yDiam, Boolean isProportional)
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateShedDormer(MCObjectHandle object)
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateBasicSlab(short slabKind)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateSphere(const WorldPt3& center, WorldCoord radius)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateStaticHatch(const TXString& name, const WorldPt& inOriginPoint, double_param inRotationAngle)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateStaticHatchFromObject(MCObjectHandle inObj, const TXString& name, const WorldPt& inOriginPoint, double_param inRotationAngle)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE CreateSurfacefromCurvesNetwork()
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateSweepN(double_param startAngle, double_param arcAngle, double_param incrAngle, WorldCoord screwDist)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateSymbolDefinition(TXString& inoutName)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateSymbolFolder(const TXString& name)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTaperedExtrude(MCObjectHandle profileH, const double_param angle, const double_param height)
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE CreateTrapeziumDormer(MCObjectHandle object)
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateViewport(MCObjectHandle parentHandle)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateWall(const WorldPt& startPt, const WorldPt& endPt, WorldCoord thickness)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE DefineCustomObject(const TXString& name, Byte prefWhen)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DuplicateSelection(WorldCoord dx, WorldCoord dy)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE ExtendNurbsCurve(MCObjectHandle curveHandle, double_param distance, Boolean bStart, Boolean bLinear)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ExtendNurbsSurface(MCObjectHandle surfaceHandle, double_param distance, Boolean bStart, Boolean bLinear, Boolean bUDir)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GenerateBezierApproximationFromPolygon(MCObjectHandle hPolygonHandle, const WorldCoord approximationTolerance, const double discontinuityAngleTolerance, const unsigned short quadraticsPerCubic)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GroupSelection()
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE IntersectSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid)
		{
			return 0;
		}
		virtual MCObjectHandle VCOM_CALLTYPE PlaceSymbolByNameN(const TXString& symName, const WorldPt& location, double_param rotation)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE PlaceSymbolN(MCObjectHandle definition, const WorldPt& location, double_param rotation)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE RevolveWithRail(MCObjectHandle profileH, MCObjectHandle railH, MCObjectHandle axisH)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE Split2DObjectByLine(MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, MCObjectHandle& listHandles)
		{
	
		}
		virtual short VCOM_CALLTYPE SubtractSolid(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE AddChoice(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short nItemIndex)
		{
	
		}
		virtual void VCOM_CALLTYPE AddListBoxTabStop(Sint32 dialogID, Sint32 componentID, int tabStop)
		{
	
		}

		virtual short VCOM_CALLTYPE Deprecated354(Sint32, Sint32, short, short, short i)
		{
			return 0;
		}

		virtual Boolean VCOM_CALLTYPE AdjustComponentPixelPos(Sint32 nDialogID, Sint32 nComponentID, int nHorizontalPixels, int nVerticalPixels)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE AlertCritical(const TXString& text, const TXString& advice)
		{
	
		}
		virtual void VCOM_CALLTYPE AlertInform(const TXString& text, const TXString& advice, bool minorAlert, const TXString& category, const TXString& item, const TXString& checkboxOverrideText)
		{
	
		}
		virtual short VCOM_CALLTYPE AlertQuestion(const TXString& question, const TXString& advice, short defaultButton, const TXString& OKOverrideText, const TXString& CancelOverrideText, const TXString& customButtonAText, const TXString& customButtonBText, const TXString& category, const TXString& item, const TXString& checkboxOverrideText)
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE AlignBottomEdge(Sint32 dialogID, Sint32 srcItemID, short bottomID, short alignMode)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AlignLeftEdge(Sint32 dialogID, Sint32 srcItemID, short leftID, short alignMode)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AlignRightEdge(Sint32 dialogID, Sint32 srcItemID, short rightID, short alignMode)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AreListBrowserColumnLinesEnabled(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AreListBrowserRadioColumnLinesEnabled(Sint32 dialogID, Sint32 componentID, short columnIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ClearGradientSliderSegments(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE Confirm(const TXString & strNode, Boolean yesOrNo)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateCenteredStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateCheckBox(Sint32 dialogID, Sint32 itemID, const TXString& name)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateCheckBoxGroupBox(Sint32 dialogID, short itemID, const TXString& name, bool hasFrame)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateClassPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateCMYKColorSwatch(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateColorPopup(Sint32 dialogID, Sint32 itemID, short widthInStdChar)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateControl(Sint32 dialogID, Sint32 itemID, Sint32 controlKind, const TXString& name, SintptrT data)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateCustomControl(Sint32 dlogID, Sint32 controlID, short widthInPixels, short heightInPixels)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateDesignLayerPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateEditInteger(Sint32 dialogID, Sint32 itemID, Sint32 defaultValue, short widthInStdChar)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateEditReal(Sint32 dialogID, Sint32 itemID, Sint32 editRealType, double value, short widthInStdChar)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateEditText(Sint32 dialogID, Sint32 itemID, const TXString& defaultText, short widthInStdChar, short heightInLines)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateEnhancedPullDownMenu(Sint32 liDialogID, Sint32 liComponentID, int widthInStdChar, Boolean bShowIconInMainWindow)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateGroupBox(Sint32 dialogID, Sint32 itemID, const TXString& name, Boolean hasFrame)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateIconPushButton(Sint32 nDialogID, Sint32 nComponentID, int nIconID, int widthInStdChar)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CreateImageControl(Sint32 liDialogID, Sint32 liComponentID, int iWidthPixels, int iHeightPixels, MCObjectHandle hImage)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE CreateLayout(const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName)
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE CreateLineAttributePopup(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateLineStylePopup(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateLineWeightPopup(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateListBox(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateListBoxN(Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines, Boolean isMultiSel)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateListBrowser(Sint32 dialogID, Sint32 componentID, Sint16 widthInStdChar, Sint16 heightInLines)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateMarkerPopup(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual void VCOM_CALLTYPE CreatePatternPopup(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual void VCOM_CALLTYPE CreatePullDownMenu(Sint32 dialogID, Sint32 itemID, short widthInStdChar)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreatePullDownMenuGroupBox(Sint32 liDialogID, Sint32 liComponentID, int widthInStdChar, const TXString& strLabel, Boolean bHasFrame)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreatePushButton(Sint32 dialogID, Sint32 itemID, const TXString& buttonName)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateRadioButton(Sint32 dialogID, Sint32 itemID, const TXString& buttonName)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateRadioButtonGroupBox(Sint32 dialogID, short itemID, const TXString& name, bool hasFrame)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE CreateResizableLayout(const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName, Boolean widthResizable, Boolean heightResizable)
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE CreateRightStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateSeparator(Sint32 liDialogID, Sint32 liComponentID, int widthInPixels)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CreateSheetLayerPullDownMenu(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateStandardIconControl(Sint32 dialogID, Sint32 iconControlID, int iconNumber)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateStaticText(Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateSwapControl(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateSwapPane(Sint32 dialogID, Sint32 swapControlID, Sint32 newGroupID)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateSymbolDisplayControl(Sint32 dialogIDIn, Sint32 itemIDIn, const TXString& symbolRefIn, SymbolImgInfo& imgInfoInOut)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateTabControl(Sint32 dialogID, short itemID)
		{
	
		}
		virtual void VCOM_CALLTYPE CreateTabPane(Sint32 dialogID, short itemID, short groupID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateThreeStateCheckBox(Sint32 liDialogID, Sint32 liComponentID, const TXString& strName)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CreateTreeControl(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar, int heightInLines)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeleteAllItems(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE DeleteAllListBrowserItems(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteListBrowserColumn(Sint32 dialogID, Sint32 componentID, short columnIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteListBrowserItem(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeselectEditText(Sint32 dialogID, Sint32 controlID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE DisplayColorPopup(int top, int left, int bottom, int right, Boolean inDisplayByClassOption, ColorRef& ioColorRef, Boolean& ioIsByClass)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DisplaySwapPane(Sint32 dialogID, Sint32 swapControlID, Sint32 groupNumber)
		{
	
		}
		virtual void VCOM_CALLTYPE DisplayTabPane(Sint32 dialogID, Sint32 controlID, Sint32 groupNumber)
		{
	
		}
		virtual void VCOM_CALLTYPE EnableItem(Sint32 dialogID, Sint32 itemID, Boolean bEnable)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowser(Sint32 dialogID, Sint32 componentID, Boolean enable)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserClickAllDataChange(Sint32 dialogID, Sint32 componentID, Boolean enable)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE EnableListBrowserColumnLines(Sint32 dialogID, Sint32 componentID, Boolean enableColumnLines)
		{
	
		}
		virtual void VCOM_CALLTYPE EnableListBrowserColumnTracking(Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableColumnTracking)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserDragAndDrop(Sint32 dialogID, Sint32 componentID, Boolean bEnable)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserDropOnIndices(Sint32 liDialogID, Sint32 liComponentID, int iStartIndex, int iEndIndex, Boolean bEnable)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE EnableListBrowserRadioColumnLines(Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableRadioColumnLines)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserSingleLineSelection(Sint32 dialogID, Sint32 componentID, Boolean enable)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE EnableListBrowserSorting(Sint32 dialogID, Sint32 componentID, Boolean enableSorting)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EnableListBrowserUpdates(Sint32 liDialogID, Sint32 liComponentID, Boolean bEnableUpdates)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE EnsureListBrowserItemIsVisible(Sint32 dialogID, Sint32 componentID, int iIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ExpandTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID, Boolean bExpand)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE FindListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& columnDataItemIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE FindListBrowserColumnItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& itemIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE FormatTextDialog(FormatTextType& formatTextRec)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE GetActiveEditItem(Sint32 dialogID)
		{
			return -1;
		}
		virtual Sint32 VCOM_CALLTYPE GetActivePane(Sint32 dialogID, Sint32 controlID)
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetBooleanItem(Sint32 dialogID, Sint32 itemID, Boolean& state)
		{
	
		}
		virtual void VCOM_CALLTYPE GetChoiceCount(Sint32 dialogID, Sint32 itemID, short& numItems)
		{
	
		}
		virtual void VCOM_CALLTYPE GetChoiceIndex(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short& nItemIndex)
		{
	
		}
		virtual void VCOM_CALLTYPE GetChoiceText(Sint32 dialogID, Sint32 itemID, short nItemIndex, TXString& outItemText)
		{
	
		}
		virtual void VCOM_CALLTYPE GetCMYKColor(Sint32 dialogID, Sint32 itemID, TGSColorV2 &outColor)
		{
	
		}
		virtual void VCOM_CALLTYPE GetColorButton(Sint32 dialogID, Sint32 itemID, RGBColor& rgb)
		{
	
		}
		virtual void VCOM_CALLTYPE GetColorChoice(Sint32 dialogID, Sint32 itemID, short& colorIndex)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetComponentRect(Sint32 nDialogID, Sint32 nComponentID, int& nLeft, int& nTop, int& nRight, int& nBottom, ELayoutCoordinateSpace cooredinateSpace)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentTextWidth(Sint32 nDialogID, Sint32 nComponentID, int& nWidthInLMUnits)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetControlData(Sint32 dialogID, Sint32 itemID, SControlDataBase& data)
		{
	
		}
		virtual void VCOM_CALLTYPE GetCustomControlScrollArea(Sint32 dialogID, Sint32 component, int *leftStart, int *topStart)
		{
	
		}
		virtual bool VCOM_CALLTYPE GetEditInteger(Sint32 dialogID, Sint32 componentID, Sint32& value)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetEditReal(Sint32 dialogID, Sint32 componentID, short editRealType, double& value)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetGradientSliderData(Sint32 dialogID, Sint32 componentID, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetGradientSliderSelectedMarker(Sint32 dialogID, Sint32 componentID, short& segmentIndex, short& markerType)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetIconPushButtonState(Sint32 nDialogID, Sint32 nComponentID, Boolean& bPressed)
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE GetImagePopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return -1;
		}
		virtual short VCOM_CALLTYPE GetImagePopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetImagePopupSelectedItem(Sint32 dialogID, Sint32 componentID)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetItemText(Sint32 dialogID, Sint32 itemID, TXString& outCurrentText)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetLayoutDialogPosition(Sint32 dialogID, short& left, short& top, short& right, short& bottom)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetLayoutDialogSize(Sint32 dialogID, short& width, short& height)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE DEPRECATED_608(short textRsrcID)
		{
			return -1;
		}


		virtual void VCOM_CALLTYPE GetLineWeightChoice(Sint32 dialogID, Sint32 itemID, short& lineWeight)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnWidth(Sint32 dialogID, Sint32 componentID, short columnIndex, short& width)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnDataItemInfo(Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex, TXString& itemString, short &imageOn, short &imageOff, Sint32 &itemData)
		{
			return false;
		}
		virtual int VCOM_CALLTYPE GetListBrowserColumnSortState(Sint32 dialogID, Sint32 componentID, int columnIndex)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnOwnerDrawnType(Sint32 dialogID, Sint32 componentID, int iIndex, int iSubIndex, int &iOwnerDrawnType)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnHeaderToolTip(Sint32 dialogID, Sint32 componentID, int iColumnIndex, TXString& strToolTipPrimaryText, TXString& strToolTipSubText)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserColumnHeaderJust(Sint32 dialogID, Sint32 componentID, int iColumnIndex, int &iJustification)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetListBrowserControlType(Sint32 dialogID, Sint32 componentID, short columnIndex)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetListBrowserEditDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserEventInfo(Sint32 dialogID, Sint32 componentID, int& iEventType, int& iRowIndex, int& iColumnIndex)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetListBrowserItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemIndex, int nSubItemIndex, Sint32& nUserData)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetListBrowserItemDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemGradientOrImageRefNumber(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 &liRefNumber)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString& itemString, short& imageIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPenForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemPenBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int &iRedIndex, int &iGreenIndex, int &iBlueIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextJust(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int &justification)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextStyle(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, unsigned char &textStyle)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemTextColor(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int &redIndex, int &greenIndex, int &blueIndex)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE Deprecated481(Sint32, Sint32, int, int, int&, int&, int&)
		{
			return false;
		}

		virtual int VCOM_CALLTYPE GetListBrowserSortColumn(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetMarkerChoice(Sint32 dialogID, Sint32 itemID, MarkerType& style, Sint8& angle, double& size, double& width, Uint8& thicknessBasis, double& thickness)
		{
	
		}
		virtual short VCOM_CALLTYPE GetMarkerPopupSelectedItem(Sint32 dialogID, Sint32 componentID, char& style, char& angle, short& size)
		{
			return 0;
		}
		virtual GSHandle VCOM_CALLTYPE GetMultilineText(Sint32 dialogID, Sint32 itemID)
		{
			return NULL;
		}
		virtual short VCOM_CALLTYPE GetNumGradientSliderSegments(Sint32 dialogID, Sint32 componentID)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumImagePopupItems(Sint32 dialogID, Sint32 componentID)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumListBrowserColumns(Sint32 dialogID, Sint32 componentID)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumListBrowserColumnDataItems(Sint32 dialogID, Sint32 componentID, short columnIndex)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumListBrowserItems(Sint32 dialogID, Sint32 componentID)
		{
			return 0;
		}
		virtual int VCOM_CALLTYPE GetNumSelectedListBrowserItems(Sint32 dialogID, Sint32 componentID)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetPatternData(Sint32 dialogID, Sint32 itemID, short& patternIndex, short& foreColor, short& backColor)
		{
	
		}
		virtual void VCOM_CALLTYPE GetSelChoiceIndex(Sint32 dialogID, Sint32 itemID, short inStartIndex, short& outSelectedIndex)
		{
	
		}
		virtual void VCOM_CALLTYPE GetSelectedChoiceIndex(Sint32 dialogID, Sint32 itemID, short& nItemIndex)
		{
	
		}
		virtual void VCOM_CALLTYPE GetSelectionRange(Sint32 dialogID, Sint32 controlID, int& startPos, int& endPos)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetThreeStateCheckBoxState(Sint32 liDialogID, Sint32 liComponentID, int& iState)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlItemData(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, SintptrT& nItemData)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlSelectedItem(Sint32 nDialogID, Sint32 nComponentID, int& nItemID)
		{
			return false;
		}

		virtual int VCOM_CALLTYPE Deprecated545(Sint32 liDialogID, Sint32 liComponentID, const TXString& strName, int iIconID)
		{
			return 0;
		}

		virtual short VCOM_CALLTYPE InsertGradientSliderSegment(Sint32 dialogID, Sint32 componentID, double_param spotPosition, const WorldPt3& color)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE InsertImagePopupObjectItem(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex)
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE InsertImagePopupResource(Sint32 dialogID, Sint32 componentID, Sint32 listID, Sint32 index)
		{
			return 0;
		}
		virtual int VCOM_CALLTYPE InsertImagePopupSeparator(Sint32 liDialogID, Sint32 liComponentID, const TXString& strLabel)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE InsertListBrowserColumn(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& headerString, short width)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE InsertListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short imageOn, short imageOff, Sint32 itemData)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE InsertListBrowserItem(Sint32 dialogID, Sint32 componentID, short itemIndex, const TXString& itemString)
		{
			return 0;
		}

		virtual Boolean VCOM_CALLTYPE Deprecated557(Sint32 nDialogID, Sint32 nComponentID, const TXString& strLabel, int nIconIndex)
		{
			return false;
		}

		virtual int VCOM_CALLTYPE InsertTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, const TXString& strItemLabel, int nParentID, int nAfterID)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE IsItemEnabled(Sint32 nDialogID, Sint32 nComponentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsItemVisible(Sint32 nDialogID, Sint32 nComponentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserColumnTrackingEnabled(Sint32 dialogID, Sint32 componentID, short columnIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserItemSelected(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemInteractionType(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, EListBrowserItemInteractionType interactionType)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserSortingEnabled(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemCheckState(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, int& iState)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemCheckState(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const int iState)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE EnableListBrowserItem3StateCheckBox(Sint32 /*dialogID*/, Sint32 /*componentID*/, short /*itemIndex*/, short /*subItemIndex*/, bool /*bEnable*/ /*= true*/)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE IsListBrowserItem3StateCheckBoxEnabled(Sint32 /*dialogID*/, Sint32 /*componentID*/, short /*itemIndex*/, short /*subItemIndex*/)
		{
			return false;
		}

		virtual void VCOM_CALLTYPE SetListBrowserReadOnly(Sint32 dialogID, Sint32 componentID, bool bReadOnly)
		{
    
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserReadOnly(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetListBrowserItemReadOnly(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex, bool bReadOnly)
		{
    
		}
		virtual Boolean VCOM_CALLTYPE IsListBrowserItemReadOnly(Sint32 dialogID, Sint32 componentID, int nItemIndex, int nSubItemIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE NotifyPullDownClicked(Sint32 nDialogID, Sint32 nComponentID)
		{
			return false;
		}
		virtual TOSWndPtr VCOM_CALLTYPE OverrideControl(Sint32 dlogID, Sint32 controlID, void* pCallbackOSFunction)
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE PostMinorNoteAlert(const TXString& msgStr)
		{
	
		}
		virtual void VCOM_CALLTYPE PostMinorStopAlert(const TXString& msgStr)
		{
	
		}
		virtual void VCOM_CALLTYPE PostNoteAlert(const TXString& msgStr)
		{
	
		}
		virtual void VCOM_CALLTYPE PostStopAlert(const TXString& msgStr)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE RefreshItem(Sint32 liDialogID, Sint32 liComponentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RefreshListBrowser(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveAllImagePopupItems(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RemoveAllListBrowserColumnDataItems(Sint32 dialogID, Sint32 componentID, short columnIndex)
		{
	
		}
		virtual void VCOM_CALLTYPE RemoveChoice(Sint32 dialogID, Sint32 itemID, short itemIndexToRemove)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE RemoveEnhancedPullDownMenuItemRange(Sint32 liDialogID, Sint32 liComponentID, int iStartItemIndexToRemove, int iEndItemIndexToRemove)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveGradientSliderSegment(Sint32 dialogID, Sint32 componentID, short segmentIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveImagePopupItem(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RemoveListBoxTabStop(Sint32 dialogID, Sint32 componentID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE RemoveListBrowserColumnDataItem(Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE RunLayoutDialog(Sint32 dialogID, GS_EventHandlerProcPtr handleEvent, void* env, const TXString& contextualHelpID, const bool bEnableContextualHelp)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SelectChoice(Sint32 dialogID, Sint32 itemID, short nItemIndex, Boolean bSelect)
		{
	
		}
		virtual void VCOM_CALLTYPE SelectEditText(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SelectTreeControlItem(Sint32 nDialogID, Sint32 nComponentID, int nItemID)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetBelowItem(Sint32 dialogID, Sint32 srcItemID, Sint32  belowItemID, short indentStdCh, short lineSpacing)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetBooleanItem(Sint32 dialogID, Sint32 itemID, Boolean bSelect)
		{
	
		}
		virtual void VCOM_CALLTYPE SetCMYKColor(Sint32 dialogID, Sint32 itemID, TGSColorV2 &inColor)
		{
	
		}
		virtual void VCOM_CALLTYPE SetColorButton(Sint32 dialogID, Sint32 itemID, const RGBColor& rgb)
		{
	
		}
		virtual void VCOM_CALLTYPE SetColorChoice(Sint32 dialogID, Sint32 itemID, short colorIndex)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetComponentIndeterminate(Sint32 nDialogID, Sint32 nComponentID, Boolean bIndeterminateState)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentSize(Sint32 nDialogID, Sint32 nComponentID, int nWidthPixels, int nHeightPixels)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetControlData(Sint32 dialogID, Sint32 itemID, const SControlDataBase& data)
		{
	
		}
		virtual void VCOM_CALLTYPE SetEdgeBinding(Sint32 dialogID, Sint32 itemID, Boolean boundToLeft, Boolean boundToRight, Boolean boundToTop, Boolean boundToBottom)
		{
	
		}
		virtual void VCOM_CALLTYPE SetEditInteger(Sint32 dialogID, Sint32 componentID, Sint32 value)
		{
	
		}
		virtual void VCOM_CALLTYPE SetEditReal(Sint32 dialogID, Sint32 componentID, short editRealType, double value)
		{
	
		}
		virtual bool VCOM_CALLTYPE SetFirstGroupItem(Sint32 dialogID, Sint32 groupID, Sint32 firstItemID)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetFirstLayoutItem(Sint32 dialogID, Sint32 firstItemID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetFocusOnItem(Sint32 liDialogID, Sint32 liComponentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetFocusOnListBrowser(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientSliderData(Sint32 dialogID, Sint32 componentID, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientSliderSelectedMarker(Sint32 dialogID, Sint32 componentID, short segmentIndex, short markerType)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetHelpText(Sint32 dialogID, Sint32 itemID, const TXString& helpText)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetIconPushButtonState(Sint32 nDialogID, Sint32 nComponentID, Boolean bPressed)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetImageControlHandle(Sint32 liDialogID, Sint32 liComponentID, MCObjectHandle hImage)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetImageControlPath(Sint32 nDialogID, Sint32 nComponentID, const TXString& strPath)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetImagePopupSelectedItem(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetItemText(Sint32 dialogID, Sint32 itemID, const TXString& strNewText)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetItemToolTipText(Sint32 nDialogID, Sint32 nComponentID, const TXString& strToolTip, const TXString& strSubToolTip, int nIndex, int nSubIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetLayoutDialogPosition(Sint32 dialogID, short left, short top)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetLayoutDialogSize(Sint32 dialogID, short width, short height)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetLayoutOption(Sint32 dialogID, short option, Sint32 value)
		{
			return false;
		}


		virtual void VCOM_CALLTYPE SetLineWeightChoice(Sint32 dialogID, Sint32 itemID, short lineWeight)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnWidth(Sint32 dialogID, Sint32 componentID, short fromColumn, short toColumn, short width)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnOwnerDrawnType(Sint32 dialogID, Sint32 componentID, int iIndex, int iSubIndex, int iOwnerDrawnType)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnHeaderToolTip(Sint32 dialogID, Sint32 componentID, int iColumnIndex, const TXString& strToolTipPrimaryText, const TXString& strToolTipSubText)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnHeaderJust(Sint32 dialogID, Sint32 componentID, int iColumnIndex, int iJustification)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserColumnImage(Sint32 nDialogID, Sint32 nComponentID, int nColumnIndex, int nImageIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserControlType(Sint32 dialogID, Sint32 componentID, short columnIndex, short controlType)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserDragAndDropColumn(Sint32 dialogID, Sint32 componentID, int iColumnIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserEditDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE SetListBrowserItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemIndex, int nSubItemIndex, Sint32 nUserData)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemDisplayType(Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemFillForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemFillBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemGradientOrImageRefNumber(Sint32 dialogID, Sint32 componentID, int itemIndex, int iSubItemIndex, Sint32 liRefNumber)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, short imageIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPenForeColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemPenBackColor(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, int iRedIndex, int iGreenIndex, int iBlueIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextJust(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int justification)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextStyle(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, unsigned char textStyle)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemTextColor(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, int redIndex, int greenIndex, int blueIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemUsingColumnDataItem(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short columnDataItemIndex)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE Deprecated590(Sint32, Sint32, int, int, int, int, int)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE SetListBrowserSelection(Sint32 dialogID, Sint32 componentID, short firstItemIndex, short lastItemIndex, Boolean select)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetListBrowserSortColumn(Sint32 dialogID, Sint32 componentID, int columnIndex, Boolean isAscending)
		{
	
		}
		virtual void VCOM_CALLTYPE SetMarkerChoice(Sint32 dialogID, Sint32 itemID, MarkerType style, Sint8 angle, double size, double width, Uint8 thicknessBasis, double thickness)
		{
	
		}
		virtual void VCOM_CALLTYPE SetMultilineText(Sint32 dialogID, Sint32 itemID, GSHandle text)
		{
	
		}
		virtual void VCOM_CALLTYPE SetPatternData(Sint32 dialogID, Sint32 itemID, short patternIndex, short foreColor, short backColor)
		{
	
		}
		virtual void VCOM_CALLTYPE SetProportionalBinding(Sint32 dialogID, Sint32 itemID, Boolean leftProportional, Boolean rightProportional, Boolean topProportional, Boolean bottomProportional)
		{
	
		}
		virtual bool VCOM_CALLTYPE SetRightItem(Sint32 dialogID, Sint32 srcItemID, Sint32 rightItemID, short indentStdCh, short lineSpacing)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetSelectionRange(Sint32 dialogID, Sint32 controlID, int startPos, int endPos)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextEditable(Sint32 dialogID, Sint32 itemID, Boolean editable)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetThreeStateCheckBoxState(Sint32 liDialogID, Sint32 liComponentID, int iState)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemData(Sint32 nDialogID, Sint32 nComponentID, int nItemID, SintptrT nItemData)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemData2(Sint32 nDialogID, Sint32 nComponentID, int nItemID, const TXString & itemData)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ShowEnhancedPullDownMenuGroupIcon(Sint32 liDialogID, Sint32 liComponentID, Boolean bShowGroupIcon)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ShowItem(Sint32 dialogID, Sint32 itemID, Boolean bShow)
		{
	
		}
		virtual void VCOM_CALLTYPE UpdateCustomControlScrollArea(Sint32 dialogID, Sint32 component, int width, int height, int leftStart, int topStart, int stepSize, bool liveUpdate, bool alwaysShowHoriz, bool alwaysShowVert)
		{
	
		}
		virtual void VCOM_CALLTYPE UpdateSymbolDisplayControl(Sint32 dialogIDIn, Sint32 itemIDIn, const TXString& symbolRefIn, SymbolImgInfo& imgInfoInOut)
		{
	
		}
		virtual bool VCOM_CALLTYPE VerifyLayout(Sint32 dialogID)
		{
			return false;
		}
		virtual InternalIndex VCOM_CALLTYPE AddClass(const TXString& className)
		{
			return -1;
		}

		virtual InternalIndex VCOM_CALLTYPE AddGuidesClass()
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE ColorIndexToName(const ColorRef& inColorRef, TXString& outColorName)
		{
	
		}
		virtual void VCOM_CALLTYPE ColorIndexToRGB(ColorRef colorIndex, RGBColor& rgb)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CopySymbol(const TXString& inFilePath, const TXString& symName)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateGradient(const TXString& name)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateHatch(const TXString& inName, Boolean inUsePageUnits, Boolean inRotateInWalls, Boolean inRotateInSymbols, Boolean inTransparent,  ColorRef inFillColorIndex)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateImageFromPaint(MCObjectHandle paint, const TXString& imageName)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreatePaintFromImage(MCObjectHandle image)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateWallStyle(const TXString& wallStyleName)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteClass(const TXString& className)
		{
	
		}

		virtual void VCOM_CALLTYPE DeselectAll()
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetActiveSymbolDef()
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetClassVisibility(InternalIndex index)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetCurrentLayer()
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE GetCurrentView()
		{
			return 0;
		}

		virtual InternalIndex VCOM_CALLTYPE GetDimensionClassID()
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE GetGradientData(MCObjectHandle gradient, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetGradientMidpointPosition(MCObjectHandle gradient, short segmentIndex, double& position)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetGradientSpotColor(MCObjectHandle gradient, short segmentIndex, WorldPt3& color)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetGradientSpotPosition(MCObjectHandle gradient, short segmentIndex, double& position)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetGridUnits(WorldCoord& x, WorldCoord& y)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetHatchLevel(MCObjectHandle inHatchDef, short inLevel, WorldPt& outStartPt, WorldPt& outRepeatVec, double& outDashFactor, WorldPt& outOffsetVec, ColorRef& outColorIndex, short& outMilsLineWeight)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetLayerScaleN(MCObjectHandle h, double_gs& scale)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetNamedLayer(const TXString& layerName)
		{
				return NULL;
		}
		virtual InternalIndex VCOM_CALLTYPE GetNoneClassID()
		{
			return -1;
		}

		virtual short VCOM_CALLTYPE GetNumGradientSegments(MCObjectHandle gradient)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetPageBounds(WorldRect& bounds)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetPatternBits(short inIndex, Uint8 outPattern[8])
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetSheetLayerUserOrigin(MCObjectHandle layerHandle, WorldPt& origin)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetUnits(UnitsType& currentUnits)
		{
	
		}
		virtual void VCOM_CALLTYPE GetUserOrigin(WorldPt& origin)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetUserOriginFP(WorldPt& outOrigin)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE InsertGradientSegment(MCObjectHandle gradient, double_param spotPosition, double_param midpointPosition, const WorldPt3& color)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE MarkCurrentDocChanged()
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE NumSelectedObjects()
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE RemoveGradientSegment(MCObjectHandle gradient, short segmentIndex)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ResetAllObjectsVisibility()
		{
	
		}
		virtual void VCOM_CALLTYPE RGBToColorIndex(const RGBColor& rgb, ColorRef& colorIndex)
		{
	
		}
		virtual void VCOM_CALLTYPE SelectAll()
		{
	
		}
		virtual void VCOM_CALLTYPE SetActiveSymbolDef(MCObjectHandle aSymDef)
		{
	
		}
		virtual void VCOM_CALLTYPE SetClassVisibility(InternalIndex index, Boolean visible)
		{
	
		}
		virtual void VCOM_CALLTYPE SetCurrentLayer(MCObjectHandle theLayer)
		{
	
		}
		virtual void VCOM_CALLTYPE SetCurrentLayerN(MCObjectHandle theLayer, Boolean bAllowUnifiedViewMaintenance /* = false by default */)
		{
	
		}

		virtual Boolean VCOM_CALLTYPE SetGradientData(MCObjectHandle gradient, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientMidpointPosition(MCObjectHandle gradient, short segmentIndex, double_param position)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientSpotColor(MCObjectHandle gradient, short segmentIndex, const WorldPt3& color)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetGradientSpotPosition(MCObjectHandle gradient, short& segmentIndex, double_param position)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetHatchLevel(MCObjectHandle inHatchDef, short inLevel, const WorldPt& inStartPt, const WorldPt& inRepeatVec, double_param inDashFactor, const WorldPt& inOffsetVec, ColorRef inColorIndex, short inMilsLineWeight)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetLayerScaleN(MCObjectHandle theLayer, double_param newScale)
		{
	
		}
		virtual void VCOM_CALLTYPE SetMarker(MCObjectHandle obj, MarkerType style, short size, short angle, Boolean start, Boolean end)
		{
	
		}
		virtual void VCOM_CALLTYPE SetProjection(MCObjectHandle theLayer, short newProj, Boolean confirmWithUser, Boolean doProgress)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetRenderMode(MCObjectHandle theLayer, short newRenderMode, Boolean immediate, Boolean doProgress)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetSheetLayerUserOrigin(MCObjectHandle layerHandle, const WorldPt& origin)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetUserOrigin(const WorldPt& origin)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetUserOriginFP(const WorldPt& inOrigin)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ShowCreateImageDialog()
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE ShowGradientEditorDialog(MCObjectHandle& gradient)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ValidClass(InternalIndex classID)
		{
			return false;
		}
		virtual TTesselator VCOM_CALLTYPE CreateTessellator(short convertRes3D)
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteTessellator(TTesselator pTess)
		{
	
		}
		virtual bool VCOM_CALLTYPE TesselateObject(TTesselator pTess, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE UpdateThumbnailPreview(InternalIndex inIndex)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CloseXCode(Sint32 extCodeInfoID)
		{
	
		}
		virtual GenericFunctionPtr VCOM_CALLTYPE OpenXCode(Sint32 extCodeInfoID, Boolean needsResourceFileOpen)
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE GSDisposeHandle(GSHandle handle)
		{
	
		}
		virtual void VCOM_CALLTYPE GSDisposePtr(void* p)
		{
	
		}
		virtual void VCOM_CALLTYPE GSGetHandleSize(GSHandle handle, size_t& size)
		{
	
		}
		virtual void VCOM_CALLTYPE GSGetHandleState(GSHandle handle, Boolean& isLocked)
		{
	
		}
		virtual void VCOM_CALLTYPE GSHLock(GSHandle handle)
		{
	
		}
		virtual void VCOM_CALLTYPE GSHUnlock(GSHandle handle)
		{
	
		}
		virtual GSHandle VCOM_CALLTYPE GSNewHandle(size_t size)
		{
			return NULL;
		}
		virtual VoidPtr VCOM_CALLTYPE GSNewPtr(size_t size)
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE GSReduceHandleSize(GSHandle handle, size_t size)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GSSetHandleSize(GSHandle handle, size_t size)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GSSetHandleState(GSHandle handle, Boolean isLocked)
		{
	
		}
		virtual VoidPtr VCOM_CALLTYPE GSSetPtrSize(void* p, size_t size)
		{
			return NULL;
		}
		virtual Sint32 VCOM_CALLTYPE AddResourceToList(Sint32 listID, MCObjectHandle resource)
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE BuildResourceList(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE DeleteResourceFromList(Sint32 listID, Sint32 index)
		{
	
		}
		virtual void VCOM_CALLTYPE DisposeResourceList(Sint32 listID)
		{
	
		}
		virtual void VCOM_CALLTYPE GetActualNameFromResourceList(Sint32 listID, Sint32 index, TXString& name)
		{
	
		}
		virtual short VCOM_CALLTYPE GetMyMenuCommandIndex()
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetNameFromResourceList(Sint32 listID, Sint32 index, TXString& name)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetResourceFromList(Sint32 listID, Sint32 index)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ImportResourceToCurrentFile(Sint32 listID, Sint32 index)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE RegisterMenuForCallback(short menuIndex, OSType whichChange)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE ResourceListSize(Sint32 listID)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE UnregisterMenuForCallback(short menuIndex, OSType whichChange)
		{
	
		}

		virtual void VCOM_CALLTYPE Deprecated747(short iconID)
		{
	
		}
		virtual void VCOM_CALLTYPE Deprecated748(short initialSetting, short iconID)
		{
	
		}

		virtual void VCOM_CALLTYPE AddPullDownMenuItem(short group, const TXString& item)
		{
	
		}
		virtual void VCOM_CALLTYPE AddPullDownMenuMode(const TXString& label)
		{
	
		}

		virtual void VCOM_CALLTYPE Deprecated751(short initialSetting, short numButtons, short id1, short id2, short id3, short id4, short id5, short id6)
		{
	
		}

		virtual void VCOM_CALLTYPE AddTxtBtnMode(const TXString& theText)
		{
	
		}
		virtual void VCOM_CALLTYPE EnableMode(short modeNum, Boolean enable)
		{
	
		}
		virtual short VCOM_CALLTYPE GetModeValue(short modeNum)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SetHelpString(const TXString& helpMessage)
		{
	
		}
		virtual void VCOM_CALLTYPE SetModeValue(short modeNum, short theValue)
		{
	
		}
		virtual void VCOM_CALLTYPE SetPullDownMenuSelection(short group, short selectedItem)
		{
	
		}
		virtual void VCOM_CALLTYPE ClassIDToName(InternalIndex classID, TXString& outClassName)
		{
	
		}
		virtual InternalIndex VCOM_CALLTYPE ClassNameToID(const TXString& className)
		{
			return -1;
		}
		virtual MCObjectHandle VCOM_CALLTYPE InternalIndexToHandle(InternalIndex index)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE InternalIndexToNameN(InternalIndex index, TXString& outName)
		{
	
		}
		virtual InternalIndex VCOM_CALLTYPE MaxClassID()
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE NameToInternalIndexN(const TXString& name, InternalIndex& index)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetPolyVertexLoopDirection(MCObjectHandle ioPolyToSet, PolyDirectionSpecType inPolyDirectionSpec)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE AddToConstraintModel(MCObjectHandle obj)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE AddViewportAnnotationObject(MCObjectHandle viewportHandle, MCObjectHandle annotationHandle)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AppendParameterWidget(Sint32 ObjectID, int parameterID, const TXString& text, Sint32 data)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AppendWidget(Sint32 ObjectID, int widgetType, int eventID, const TXString& text, Sint32 data)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ConvertTo3DPolygons(MCObjectHandle h, Boolean preserveOriginal)
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE ConvertToNURBS(MCObjectHandle h, Boolean keepOrig)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolygon(MCObjectHandle h, Boolean preserveOriginal)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolygonN(MCObjectHandle h, Boolean preserveOriginal , short conversionResolution)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ConvertToPolyline(MCObjectHandle h, Boolean preserveOriginal)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE ConvertToUnstyledWall(MCObjectHandle theWall)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE CreateConstraintModel(MCObjectHandle obj, Boolean useSelection)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateOffsetNurbsObjectHandle(MCObjectHandle h,   double offset)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtsCreate( MCObjectHandle inOwnerObj, int numDataElements, GS_CustomObjectControlPtsInitProcPtr initProc,void* env)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtsRemove(MCObjectHandle inOwnerObj)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE CustomObjectControlPtSet(MCObjectHandle inOwnerObj,int dataIndex, const WorldPt3& pt,Boolean is2DOnly,Boolean isHidden,int inClientID)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CustomObjectGetSurfaceProxy(MCObjectHandle inPathObject)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE CustomObjectReplacePath(MCObjectHandle inPathObject, MCObjectHandle pathPolyline)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteAllComponents(MCObjectHandle object)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteComponent(MCObjectHandle object, short componentIndex)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeleteConstraint(MCObjectHandle obj, MCObjectHandle constraint)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE DuplicateObject(MCObjectHandle h)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE DuplicateObjectWithNotification(MCObjectHandle h)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE EnableParameter(MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetEnabled)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EvaluateNurbsSurfacePointAndNormal(MCObjectHandle surfaceHandle, double u, double v, WorldPt3& point,  WorldPt3& normal)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ForEachLayer( GS_ForEachObjectProcPtr action, void *actionEnv)
		{
	
		}
		virtual void VCOM_CALLTYPE ForEachObject( short traverseWhat, GS_ForEachObjectProcPtr action, void *actionEnv)
		{
	
		}
		virtual void VCOM_CALLTYPE Get2DPt(MCObjectHandle obj, short index, WorldPt& loc)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetBinaryConstraint(short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetClosestPt(MCObjectHandle& obj, const WorldPt& pt, short& index, Sint32& containedObj)
		{
	
		}
		virtual void VCOM_CALLTYPE GetClosestSide(MCObjectHandle obj, const WorldPt& pt, short& indexA, short& indexB)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetComponentClass(MCObjectHandle object, short componentIndex, Sint32 &componentClass)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentFill(MCObjectHandle object, short componentIndex, Sint32 &fill)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentFillColors(MCObjectHandle object, short componentIndex, ColorRef &fillForeColor, ColorRef &fillBackColor)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentName(MCObjectHandle object, short componentIndex, TXString &componentName)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentPenColors(MCObjectHandle object, short componentIndex, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE GetComponentPenWeights(MCObjectHandle object, short componentIndex, Uint8 &leftPenWeight, Uint8 &rightPenWeight)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentUseFillClassAttr(MCObjectHandle object, short componentIndex, Boolean &useFillClassAttributes)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentUsePenClassAttr(MCObjectHandle object, short componentIndex, Boolean &useLeftPenClassAttributes, Boolean &useRightPenClassAttributes)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentWidth(MCObjectHandle object, short componentIndex, WorldCoord &width)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetCustomObjectColor(MCObjectHandle objectHand, int iTagID, ColorRef& ioColorRef)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectPath(MCObjectHandle objectHand)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetCustomObjectProfileGroup(MCObjectHandle objectHand)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetDimensionStandardVariable(short dimensionIndex, short fieldSelector, TVariableBlock& value)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetDistanceAlongNurbsCurve(MCObjectHandle inNurbsCurve, double_param inParameter1, Sint32 inParameter1CurveIndex,  double_param inParameter2, Sint32 inParameter2CurveIndex, double_gs& outDistance)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginChoice(const TXString& pluginName, const TXString& parameterName, int choiceIndex, TXString& localizedChoice)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginName(const TXString& pluginName, TXString& outLocalizedName)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetLocalizedPluginParameter(const TXString& pluginName, const TXString& parameterName, TXString& localizedParameterName)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetNumberOfComponents(MCObjectHandle object, short &numComponents)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetNurbsObjectDistanceFromPoint(MCObjectHandle h, const WorldPt&  point,  double& distance)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectProperty(MCObjectHandle hObject, Sint32 inPropID, Boolean& outValue)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectPropertyChar(MCObjectHandle hObject, Sint32 inPropID, unsigned char& outValue)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectVariable(MCObjectHandle theObject, short setSelector, TVariableBlock& value)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetParameterOnNurbsCurve(MCObjectHandle h, const WorldPt3&  point,  double& parameter, Sint32& index)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetPointAndParameterOnNurbsCurveAtGivenLength(MCObjectHandle inNurbCurve, double_param inPercentOfLength, WorldPt3& outPointOnCurve,  double_gs& outParametricParameter, Sint32& outPiecewiseCurveIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetRoofEdge(MCObjectHandle object, short index, WorldPt& vertexPt, double_gs& slope, WorldCoord& projection, WorldCoord& eaveHeight)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetSingularConstraint(short type, MCObjectHandle obj, short vertexA, short vertexB)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetViewportClassVisibility(MCObjectHandle viewportHandle, InternalIndex classIndex, short& visibilityType)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportCropObject(MCObjectHandle viewportHandle)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportGroup(MCObjectHandle viewportHandle, short groupType)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetViewportGroupParent(MCObjectHandle groupHandle)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetViewportLayerVisibility(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short& visibilityType)
		{
			return false;
		}
		virtual MeshErrorType VCOM_CALLTYPE GroupToMesh(MCObjectHandle theMesh)
		{
			return MeshErrorType(0);
		}
		virtual Boolean VCOM_CALLTYPE HasConstraint(MCObjectHandle obj)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE InsertAllParametersAsWidgets(Sint32 inObjectID)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE InsertParameterWidget(Sint32 ObjectID, int position, int parameterID, const TXString& text, Sint32 data)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE InsertWidget(Sint32 ObjectID, int position, int widgetType, int eventID, const TXString& text, Sint32 data)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsObjectFromReferencedFile(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsViewportGroupContainedObject(MCObjectHandle objectHandle,  short groupType)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE MakePolyshapeValid(MCObjectHandle thePoly)
		{
	
		}
		virtual MeshErrorType VCOM_CALLTYPE MeshToGroup(MCObjectHandle theMesh)
		{
			return MeshErrorType(0);
		}
		virtual void VCOM_CALLTYPE MoveObject(MCObjectHandle h, WorldCoord dx, WorldCoord dy)
		{
	
		}
		virtual void VCOM_CALLTYPE MoveObject3D(MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz, bool inMoveScreenObjectsWith3D = false)
		{
	
		}
		virtual void VCOM_CALLTYPE NotifyLayerChange(StatusData liAdditionalData)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE RemoveCustomObjectColor(MCObjectHandle objectHand, int iTagID)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RemoveRoofEdge(MCObjectHandle object, short index)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE ResetObject(MCObjectHandle h)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RotateObjectN(MCObjectHandle& h, const WorldPt& rotCenter, double_param angle)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE ScaleObject3D(MCObjectHandle ioObject, const WorldPt3& scaleCen, const Vector& scaleVector)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ScaleObjectN(MCObjectHandle h, const WorldPt& scaleCen, double_param scaleX, double_param scaleY)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetBinaryConstraint(short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetHorizontalDimensionConstraint(MCObjectHandle obj1, const WorldPt& pt1, const WorldPt& pt2, WorldCoord distance, ViewCoord offset)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE DeleteHorizontalDimensionConstraints(MCObjectHandle obj1)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentClass(MCObjectHandle object, short componentIndex, Sint32 componentClass)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentFill(MCObjectHandle object, short componentIndex, Sint32 fill)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentFillColors(MCObjectHandle object, short componentIndex, ColorRef fillForeColor, ColorRef fillBackColor)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentName(MCObjectHandle object, short componentIndex, const TXString &componentName)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentPenColors(MCObjectHandle object, short componentIndex, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE SetComponentPenWeights(MCObjectHandle object, short componentIndex, Uint8 leftPenWeight, Uint8 rightPenWeight)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentUseFillClassAttr(MCObjectHandle object, short componentIndex, Boolean useFillClassAttributes)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentUsePenClassAttr(MCObjectHandle object, short componentIndex, Boolean useLeftPenClassAttributes, Boolean useRightPenClassAttributes)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentWidth(MCObjectHandle object, short componentIndex, WorldCoord width)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetConstraintValue(MCObjectHandle constraint, double_param value)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetCustomDimensionStandardVariable(short dimensionIndex, short fieldSelector, const TVariableBlock& value)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE SetCustomObjectColor(MCObjectHandle objectHand, int iTagID, ColorRef inColorRef)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetCustomObjectControlPointVisibility(MCObjectHandle objectHand, short controlPtIndex, Boolean setVisible)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetCustomObjectPath(MCObjectHandle objectHand, MCObjectHandle pathHand)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetCustomObjectProfileGroup(MCObjectHandle objectHand, MCObjectHandle profileGroupHand)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetDefinition(MCObjectHandle h, MCObjectHandle newDef)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetObjectProperty(Sint32 inCodeRefID, Sint32 inPropID, Boolean inValue)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetObjectPropertyChar(Sint32 inCodeRefID, Sint32 inPropID, unsigned char inValue)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetObjectVariable(MCObjectHandle theObject, short setSelector, const TVariableBlock& value)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetParameterVisibility(MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetVisible)
		{
	
		}
		virtual void VCOM_CALLTYPE SetRoofEdge(MCObjectHandle object, short index, const WorldPt& vertexPt, double_param slope, WorldCoord projection, WorldCoord eaveHeight)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetSingularConstraint(short type, MCObjectHandle obj, short vertexA, short vertexB)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetViewportClassVisibility(MCObjectHandle viewportHandle, InternalIndex classIndex, short visibilityType)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetViewportCropObject(MCObjectHandle viewportHandle, MCObjectHandle cropHandle)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetViewportLayerVisibility(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short visibilityType)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE TrimToSelectedObjects(MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE UpdateConstraintModel()
		{
			return false;
		}
		virtual void VCOM_CALLTYPE UpdateViewport(MCObjectHandle viewportHandle)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE ViewportHasCropObject(MCObjectHandle viewportHandle)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GSCountResources(OSType inType, Boolean lookOnlyInCurrentFile)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GSGetApplicationResFile(short selector)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GSGetCurrentResFile()
		{
			return 0;
		}
		virtual GSHandle VCOM_CALLTYPE GSGetIndResource(OSType inType, short inIndex, short& outID, Boolean lookOnlyInCurrentFile)
		{
			return NULL;
		}

		virtual GSHandle VCOM_CALLTYPE DEPRECATED_1001(OSType type, short id, Boolean lookOnlyInCurrentFile)
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE GSGetResourceName(OSType inType, short inID, TXString& outName, Boolean lookOnlyInCurrentFile)
		{
	
		}
		virtual void VCOM_CALLTYPE GetVWResourceString(TXString& outValue, const char* resourceIdentifier, const char* resourceStringIdentifier, EEmptyHandling allowEmpty)
		{
	
		}
		virtual GSHandle VCOM_CALLTYPE GetVWResource(const char* resourceIdentifier)
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE GSReleaseResource(GSHandle theResource)
		{
	
		}
		virtual void VCOM_CALLTYPE GSRemoveResource(OSType inType, short inID)
		{
	
		}
		virtual void VCOM_CALLTYPE GSSetResourceName(OSType inType, short inID, const TXString& inName, Boolean lookOnlyInCurrentFile)
		{
	
		}
		virtual void VCOM_CALLTYPE GSUseResFile(short inFileID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GSWriteResource(GSHandle inResource, OSType inType, short inID)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE FirstSelectedObject()
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetSelectionBounds(WorldRect& bounds, BoundsType type)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetSelectionBoundsCube(WorldCube &theCube)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE MoveSelection(WorldCoord dx, WorldCoord dy)
		{
	
		}
		virtual void VCOM_CALLTYPE MoveSelection3D(WorldCoord dx, WorldCoord dy, WorldCoord dz)
		{
	
		}
		virtual void VCOM_CALLTYPE RotateSelectionN(const WorldPt& rotCen, double_param rotAngle)
		{
	
		}
		virtual void VCOM_CALLTYPE ScaleSelectionN(const WorldPt& scaleCen, double_param scaleX, double_param scaleY)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE AddText(MCObjectHandle textBlock, Sint32 beforeChar, Handle newText)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddTextFromBuffer(MCObjectHandle textBlock, Sint32 beforeChar, const UCChar* buffer, Sint32 bufferSize)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextBlock(const TXString& textStr, const WorldPt& textOrigin, Boolean fixedSize, WorldCoord width)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteText(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetCharNumFromPoint(MCObjectHandle textBlock, const WorldPt& pt)
		{
			return 0;
		}
		virtual TXString VCOM_CALLTYPE GetTextChars(MCObjectHandle textBlock)
		{
			return "";
		}
		virtual Boolean VCOM_CALLTYPE GetTextCharsToBuffer(MCObjectHandle textBlock, void* buffer, Sint32& bufferSize)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetTextColor(MCObjectHandle textBlock, Sint32 charNum, ColorRef& charColor)
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextFontIndex(MCObjectHandle textBlock, Sint32 charNum, short& fontIndex)
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextJustification(MCObjectHandle textBlock, short& justification)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetTextLength(MCObjectHandle textBlock)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetTextLineHeight(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& height)
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextOrientationN(MCObjectHandle h, double_gs& angle, short& flipState)
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextSize(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& charSize)
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextStyle(MCObjectHandle textBlock, Sint32 charNum, unsigned char& charStyle)
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextVerticalAlignment(MCObjectHandle textBlock, short& verticalAlignment)
		{
	
		}
		virtual void VCOM_CALLTYPE GetTextVerticalSpacing(MCObjectHandle textBlock, short& spacing, WorldCoord& height)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetTextWidth(MCObjectHandle textBlock, WorldCoord& width)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE GetTextWrap(MCObjectHandle textBlock, Boolean& wrapped)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetTextColor(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, ColorRef charColor)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextFontIndex(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, short fontIndex)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextJustification(MCObjectHandle textBlock, short justification)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextOrientationN(MCObjectHandle h, double_param angle, short flipState)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextSize(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, WorldCoord charSize)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextStyle(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char charStyle)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextVerticalAlignment(MCObjectHandle textBlock, short verticalAlignment)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextVerticalSpacing(MCObjectHandle textBlock, short spacing, WorldCoord height)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextWidth(MCObjectHandle textBlock, WorldCoord width)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextWrap(MCObjectHandle textBlock, Boolean wrapped)
		{
	
		}
		virtual void VCOM_CALLTYPE SpellCheckTextBuffer(GSHandle charsHandle, Boolean textChanged)
		{
	
		}
		virtual void VCOM_CALLTYPE AttachDefaultTextureSpace(MCObjectHandle object, short multiPartID)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateShaderRecord(MCObjectHandle texture, Sint32 family, Sint32 prototype)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTexture()
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextureBitmap()
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateTextureBitmapFromPaintNode(MCObjectHandle paintNodeObject)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteTextureSpace(MCObjectHandle object, short multiPartID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE EditShaderRecord(MCObjectHandle shaderRecord)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE EditTexture(MCObjectHandle texture)
		{
			return false;

		}
		virtual void VCOM_CALLTYPE Deprecated883()
		{
	
		} // EditTextureBitmap
		virtual Boolean VCOM_CALLTYPE EditTextureSpace(MCObjectHandle texturedObject, short multiPartID)
		{
			return false;

		}
		virtual InternalIndex VCOM_CALLTYPE GetClGenTexture(InternalIndex index)
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetClRoofTextures(InternalIndex index, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetClUseTexture(InternalIndex index)
		{
			return false;

		}
		virtual void VCOM_CALLTYPE GetClWallTextures(InternalIndex index, InternalIndex& right, InternalIndex& left, InternalIndex& center)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetShaderRecord(MCObjectHandle parentNode, Sint32 family)
		{
				return NULL;
		}
		virtual InternalIndex VCOM_CALLTYPE GetTextureRef(MCObjectHandle object, short multiPartID, Boolean resolveByClass)
		{
			return -1;
		}
		virtual void VCOM_CALLTYPE GetTextures(MCObjectHandle h, InternalIndex& primaryTexture, InternalIndex& secondaryTexture, InternalIndex& tertiaryTexture)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetTextureSpace(MCObjectHandle object, short multiPartID)
		{
				return NULL;
		}
		virtual InternalIndex VCOM_CALLTYPE GetVPClassGenTexture(MCObjectHandle viewport, InternalIndex classIndex)
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE GetVPClassRoofTextures(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer)
		{
	
		}
		virtual void VCOM_CALLTYPE GetVPClassWallTextures(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& right, InternalIndex& left, InternalIndex& center)
		{
	
		}
		virtual void VCOM_CALLTYPE SetClGenTexture(InternalIndex index, InternalIndex texture)
		{
	
		}
		virtual void VCOM_CALLTYPE SetClRoofTextures(InternalIndex index, InternalIndex top, InternalIndex edge, InternalIndex dormer)
		{
	
		}
		virtual void VCOM_CALLTYPE SetClUseTexture(InternalIndex index, Boolean use)
		{
	
		}
		virtual void VCOM_CALLTYPE SetClWallTextures(InternalIndex index, InternalIndex right, InternalIndex left, InternalIndex center)
		{
	
		}
		virtual void VCOM_CALLTYPE SetDefaultTextureSpace(MCObjectHandle object, MCObjectHandle space, short multiPartID)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextureRef(MCObjectHandle object, InternalIndex textureRef, short multiPartID)
		{
	
		}

		virtual Sint32 VCOM_CALLTYPE Deprecated943(short inHotSpotType, const WorldPt3& inLocation, Sint32 inCursorID, const TXString& inTip)
		{
			return 0;
		}

		virtual MCObjectHandleID VCOM_CALLTYPE AddToolPersistentDraw(GS_PersistentDrawProcPtr drawProcPtr, void *drawEnv)
		{
			return 0;
		}
		virtual MCObjectHandleID VCOM_CALLTYPE AddToolSnapGeometry(MCObjectHandle inSnapGeometry)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE BoxToolDraw()
		{
	
		}
		virtual Boolean VCOM_CALLTYPE ClearAllToolPts()
		{
			return false;

		}
		virtual void VCOM_CALLTYPE ClearDataDisplayBar()
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE ClickDragToolStatus()
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE CustomBarCreate(short inNumFields, CustomBarRefID& outCustomBarRefID)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarGetFieldInfo(CustomBarRefID inCustomBarID, short inFieldIndex, CustomBarFieldInfo& inFieldInfo)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarInstall(CustomBarRefID inCustomBarID)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarRelease(CustomBarRefID inCustomBarRefID)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldAngle(CustomBarRefID inCustomBarID, short inFieldIndex, const double& inDegrees)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldInfo(CustomBarRefID inCustomBarID, short inFieldIndex, const CustomBarFieldInfo& inFieldInfo)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE CustomBarSetFieldWorldCoord(CustomBarRefID inCustomBarID, short inFieldIndex, const WorldCoord& inCoordVal)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE Default2DToolDraw()
		{
	
		}
		virtual void VCOM_CALLTYPE Default3DToolDraw()
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordArcN(const WorldRect& theBox, double_param startAngle, double_param sweepAngle)
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordEllipse(WorldRect& theBox)
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordLine(const WorldPt& p1, const WorldPt& p2)
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordLine3D(const WorldPt3& p1, const WorldPt3& p2)
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordRect(const WorldRect& theBox)
		{
	
		}
		virtual void VCOM_CALLTYPE DrawDataDisplayBar(Boolean drawFramesFirst)
		{
	
		}
		virtual void VCOM_CALLTYPE DrawNurbsObject(MCObjectHandle h)
		{
	
		}
		virtual void VCOM_CALLTYPE DrawObject(MCObjectHandle h, Boolean doSelect)
		{
	
		}
		virtual void VCOM_CALLTYPE GetCoords(WorldPt& p, ViewPt& m)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetNumToolPts()
		{
			return 0;
		}
		virtual const ICoreToolAccess* VCOM_CALLTYPE GetToolCoreInterface()
		{
			return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPt2D(Sint32 inIndex, WorldPt& outToolPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPt3D(Sint32 inIndex, WorldPt3& outToolPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrent2D(WorldPt& outToolPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrent3D(WorldPt3& outToolPt)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrentViewPt(ViewPt& outToolPt)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtCurrentWorkingPlane(WorldPt3& outToolPt)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtViewPoint(Sint32 inIndex, ViewPt& outToolPoint)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetToolPtWorkingPlane(Sint32 inIndex, WorldPt3& outToolPoint)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE InstallConstraintAlong3DLine(const Ray& inConstraintDescription)
		{
	
		}
		virtual void VCOM_CALLTYPE Interactive2DDraw( short options, short shiftConsMode, GS_I2DDrawProcPtr drawProc, void *env)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE OnePointToolStatus()
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE PolyToolStatus()
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE PopLastToolPt()
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RemoveHotSpot(HotSpotRefID inHotSpotID)
		{
	
		}
		virtual void VCOM_CALLTYPE RemoveToolPersistentDraw(MCObjectHandleID persistentDrawRefID)
		{
	
		}
		virtual void VCOM_CALLTYPE RemoveToolSnapGeometry(MCObjectHandleID inSnapGeometryID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE RunTemporary2DTool( Sint32& ioUserData, ToolDefProcPtr inToolProc)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE RunTemporary3DTool( Sint32& ioUserData, ToolDefProcPtr inToolProc)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetCursorMode()
		{
	
		}
		virtual void VCOM_CALLTYPE SetDataDisplayBarField(short fieldNum, BarNumberType barType, const TXString& inBarLabel)
		{
	
		}

		virtual void VCOM_CALLTYPE SetDimUserBarValue(short fieldNum, WorldCoord dimVal)
		{
	
		}
		virtual void VCOM_CALLTYPE SetFloatUserBarValueN(short fieldNum, double_param floatVal, short numPlaces)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextUserBarValue(short fieldNum, const TXString& textVal)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetToolProperty(Sint32 inCodeRefID, Sint32 inToolPropID, Boolean inValue)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetToolPropertyChar(Sint32 inCodeRefID, Sint32 inToolPropID, char inValue)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE ThreePointToolStatus()
		{
			return 0;
		}
		virtual HotSpotRefID VCOM_CALLTYPE TrackHotSpot(Boolean& outIs3d, WorldPt3& outLocation)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE TrackTool(MCObjectHandle& overObject, short& overPart, SintptrT& code)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE TwoPointToolStatus()
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE AddObjectToContainer(MCObjectHandle h, MCObjectHandle container)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE AuxOwner(MCObjectHandle h)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteObject(MCObjectHandle h, Boolean useUndo)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE FindHandleDeep(MCObjectHandle handleToFind, MCObjectHandle firstObjectInSearchList, MCObjectHandle& unused)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE FirstMemberObj(MCObjectHandle h)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetDefaultContainer()
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetDrawingHeader()
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetHatchListHeader()
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetSymbolLibraryHeader()
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE InsertObjectAfter(MCObjectHandle h, MCObjectHandle afterObject)
		{
	
		}
		virtual void VCOM_CALLTYPE InsertObjectBefore(MCObjectHandle h, MCObjectHandle beforeObject)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE LastMemberObj(MCObjectHandle h)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE NextObject(MCObjectHandle h)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE ParentObject(MCObjectHandle h)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE PrevObject(MCObjectHandle h)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE SearchForAncestorType(Sint16 objectType, MCObjectHandle h)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE SetPageBounds(const WorldRect& bounds)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE AcquireExportPDFSettingsAndLocation(Boolean inbSeparateDocuments)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ClosePDFDocument()
		{
	
		}
		virtual short VCOM_CALLTYPE ExportPDFPages(const TXString& inSavedViewNameStr)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE OpenPDFDocument(const TXString& inFileNameStr)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddAfterMoveObject(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddAfterSwapObject(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddBeforeMoveObject(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddBeforeSwapObject(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddBothSwapObject(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddBothSwapLayerProperties(MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddCoordMoveObject2D(MCObjectHandle h, WorldCoord dx, WorldCoord dy)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AddCoordMoveObject3D(MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE EndUndoEvent()
		{
			return false;
		}
		virtual void VCOM_CALLTYPE NameUndoEvent(const TXString& name)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE NonUndoableActionOK()
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetUndoMethod(short undoType)
		{
	
		}
		virtual void VCOM_CALLTYPE SupportUndoAndRemove()
		{
	
		}
		virtual void VCOM_CALLTYPE UndoAndRemove()
		{
	
		}
		virtual void VCOM_CALLTYPE AngleToStringN(double_param angle, TXString& s)
		{
	
		}
		virtual void VCOM_CALLTYPE AssociateLinearDimension(MCObjectHandle h, Boolean selectedObjectsMode)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CallPluginLibrary(const TXString& routineName, PluginLibraryArgTable* argumentTable, Sint32 status)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ClipSurface(MCObjectHandle h1, MCObjectHandle h2)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CombineIntoSurface(const WorldPt& insidePt)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE CoordToDimString(WorldCoord c, TXString& s)
		{
	
		}
		virtual Sint16 VCOM_CALLTYPE CStringCompare(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE CStringEqual(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DisableModules(Sint32 modules)
		{
	
		}
		virtual void VCOM_CALLTYPE DisplayContextHelpOfCurrentPlugin()
		{
	
		}
		virtual Boolean VCOM_CALLTYPE DisplayContextualHelp(const TXString& helpIdentifier)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DisplayOrganizationDialog(short tabToSelect)
		{
	
		}
		virtual short VCOM_CALLTYPE DoMenuName(const TXString& name, short chunkIndex)
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE DoProgramAction(short actionSelector, void* actionEnv)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE DoubleToString(TNumStyleClass inNumStyle,  Byte inAccuracy, Byte inFormat, double_param inDouble, TXString& outString)
		{
	
		}
		virtual void VCOM_CALLTYPE DrawScreen(const ViewRect& clipRect, Boolean isLastFrame)
		{
	
		}
		virtual void VCOM_CALLTYPE EllipseEllipseIntersect(const WorldRect& e1, const WorldRect& e2, Sect4Struct& sects)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE ExternalNameToID(const TXString& fnName)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE FontIndexFromName(const TXString& fontName)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE FontNameFromIndex(short fontIndex, TXString& fontName, Boolean useMappingTable)
		{
	
		}
		virtual void VCOM_CALLTYPE GetActiveSerialNumber(TXString& outSerialNumber)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetCallBackInval()
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetCurrentMode()
		{
			return 0;
		}
		virtual int VCOM_CALLTYPE GetDataBarCursorVisState()
		{
			return 0;
		}
		virtual Sint32 VCOM_CALLTYPE GetEnabledModules()
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetHostInfo(short& hostID, Byte& version, Byte& majorRev, Byte& minorRev, TXString& outProductName, TXString& outProductVersion)
		{
	
		}
		virtual void VCOM_CALLTYPE GetModifierFlags(Boolean& optionFlag, Boolean& cmdFlag, Boolean& shiftFlag)
		{
	
		}
		virtual void VCOM_CALLTYPE GetProduct(short& product, Sint32& modules)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetSavedSetting(const TXString& category, const TXString& setting, TXString& value)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE HandlePendingUpdatesAndActivates()
		{
	
		}
		virtual void VCOM_CALLTYPE HilitePalettesAndTopDocument(Boolean doHilite)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE IntersectObjects(MCObjectHandle obj1, MCObjectHandle obj2, Boolean onlyOnObjs)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE Kludge(short selector, void* in, void* out)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE LineEllipseIntersect(const WorldPt& a1, const WorldPt& a2, const WorldRect& r, Sect2Struct& sects)
		{
	
		}
		virtual void VCOM_CALLTYPE LineLineIntersect(const WorldPt& a1, const WorldPt& a2, const WorldPt& b1, const WorldPt& b2, Boolean& parallel, Boolean& intOnLines, WorldPt& sect)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE ObjectNearCoordPt(const WorldPt& p)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE PlaySoundResource(Handle soundResource, Boolean async, Boolean forcePlay)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE PointInsidePoly(const WorldPt& checkPt, MCObjectHandle h)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE PointOnPolyEdge(const WorldPt& checkPt, MCObjectHandle h, WorldCoord checkRadius)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE RegisterExternal(const TXString& fileName, short codeResID, OSType codeResType)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE RegisterNotificationProcedure(StatusProcPtr proc, OSType whichChange)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetCallBackInval(Boolean turnInvalOn)
		{
	
		}
		virtual void VCOM_CALLTYPE SetPersistentHighlight(MCObjectHandle theObject, Boolean highlightState)
		{
	
		}
		virtual void VCOM_CALLTYPE SetSavedSetting(const TXString& category, const TXString& setting, const TXString& value)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE StringToAngleN(const TXString& s, double_gs& angle)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE StringToDouble(TNumStyleClass inNumStyle, const TXString& inString, double_gs& outDouble)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SymbolContainsLight(MCObjectHandle symbol)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ToggleObjectHighlight(MCObjectHandle theObject)
		{
	
		}
		virtual void VCOM_CALLTYPE UnregisterNotificationProcedure(StatusProcPtr proc, OSType whichChange)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE VerifyPluginLibrary(const TXString& routineName)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetPerspectiveInfo(MCObjectHandle theLayer, WorldCoord& perspectiveDistance, WorldCoord& clipDistance, WorldRect& clipRect)
		{
	
		}
		virtual short VCOM_CALLTYPE GetProjection(MCObjectHandle theLayer)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetRenderMode(MCObjectHandle theLayer)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetScreenDPI()
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetViewCenter(WorldPt& center)
		{
	
		}
		virtual void VCOM_CALLTYPE GetViewMatrix(MCObjectHandle theLayer, TransformMatrix& theMat)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorkingPlane(Axis &theAxis)
		{
	
		}
		virtual void VCOM_CALLTYPE NewCurrentViewMatrix(const TransformMatrix& theMat, Boolean interactive)
		{
	
		}
		virtual void VCOM_CALLTYPE NewWorkingPlane(const Axis &theAxis)
		{
	
		}
		virtual void VCOM_CALLTYPE PreviewDrawFrame(Handle thisPreview, Boolean selectedOnly)
		{
	
		}
		virtual void VCOM_CALLTYPE PreviewFinish(Handle& thisPreview)
		{
	
		}
		virtual Handle VCOM_CALLTYPE PreviewSetup(Boolean doDynamicSpeedups, double_param targetFPS, Boolean drawGroundPlane, Boolean drawPage, Boolean drawCropRect)
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE RedrawRect(const WorldRect& redrawR)
		{
	
		}
		virtual void VCOM_CALLTYPE SetViewCenter(const WorldPt& center)
		{
	
		}
		virtual void VCOM_CALLTYPE SetViewMatrix(MCObjectHandle theLayer, const TransformMatrix& theMatrix)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorkingPlaneAxis(const Vector &si, const Vector &sj, const Vector &sk)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorkingPlaneVertex(const WorldPt3 &v)
		{
	
		}
		virtual void VCOM_CALLTYPE SetZoomFactorN(double_param zoomFac)
		{
	
		}
		virtual void VCOM_CALLTYPE ViewRotWorldZN(double_param angle, Boolean interactive)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE WorldRect2ViewRect(const WorldRect& wRect, ViewRect& vRect)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE AddBreak(MCObjectHandle theWall, WorldCoord off, short breakType, void* breakData)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE DeleteBreak(MCObjectHandle theWall, short index)
		{
	
		}
		virtual void VCOM_CALLTYPE ForEachBreak( MCObjectHandle theWall, GS_ForEachBreakProcPtr action, void* actionEnv)
		{
	
		}
		virtual void VCOM_CALLTYPE Deprecated1065()
		{
	
		} // GetLayerDeltaZOffset
		virtual void VCOM_CALLTYPE Deprecated1066()
		{
	
		} // GetLinkHeightToLayerDeltaZ
		virtual void VCOM_CALLTYPE GetPolyBreakGeometry(MCObjectHandle theWall, short breakIndex, MCObjectHandle& polyline)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWallCaps(MCObjectHandle theWall, Boolean &leftCap, Boolean &rightCap, Boolean &round)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWallCapsOffsets(MCObjectHandle theWall, WorldCoord &leftCapLeftOffset, WorldCoord &leftCapRightOffset, WorldCoord &rightCapLeftOffset, WorldCoord &rightCapRightOffset)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWallCornerHeights(MCObjectHandle theWall, WorldCoord& startHeightTop, WorldCoord& startHeightBottom, WorldCoord& endHeightTop, WorldCoord& endHeightBottom)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE JoinWalls(MCObjectHandle firstWall, MCObjectHandle secondWall,  const WorldPt& firstWallPt, const WorldPt& secondWallPt, JoinModifierType joinModifier, Boolean capped, Boolean showAlerts)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE MoveWallByOffset(MCObjectHandle theWall, WorldCoord& offset)
		{
	
		}
		virtual void VCOM_CALLTYPE ReverseWallSides(MCObjectHandle theWall)
		{
	
		}
		virtual void VCOM_CALLTYPE SetAsPolyBreak(MCObjectHandle& thePolyline, MCObjectHandle theWall, short breakIndex)
		{
	
		}
		virtual void VCOM_CALLTYPE SetBreak(MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData)
		{
	
		}
		virtual void VCOM_CALLTYPE Deprecated1076()
		{
	
		} // SetLayerDeltaZOffset
		virtual void VCOM_CALLTYPE Deprecated1077()
		{
	
		} // SetLinkHeightToLayerDeltaZ
		virtual Boolean VCOM_CALLTYPE SetWallCaps(MCObjectHandle theWall, const Boolean &leftCap, const Boolean &rightCap, const Boolean &round)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallCapsOffsets(MCObjectHandle theWall, WorldCoord leftCapLeftOffset, WorldCoord leftCapRightOffset, WorldCoord rightCapLeftOffset, WorldCoord rightCapRightOffset)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallCornerHeights(MCObjectHandle theWall, WorldCoord startHeightTop, WorldCoord startHeightBottom, WorldCoord endHeightTop, WorldCoord endHeightBottom)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallStyle(MCObjectHandle theWall, InternalIndex wallStyle, WorldCoord selectedOffset, WorldCoord replacingOffset)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWallWidth(MCObjectHandle theWall, WorldCoord newWidth)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE WrapGetWallWidth(MCObjectHandle theWall, double_gs& outCoordLen)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetScreenSize(ViewRect& screenRect)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE AutoFitWorksheetRowHeights(MCObjectHandle worksheet, short fromRow, short toRow)
		{
	
		}
		virtual void VCOM_CALLTYPE ClearWorksheetCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateWorksheet(const TXString& name, short rows, short columns)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE CreateWorksheetImage(MCObjectHandle worksheet, const WorldPt& topLeftCorner)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteWorksheetColumns(MCObjectHandle worksheet, short startColumn, short numColumns)
		{
	
		}
		virtual void VCOM_CALLTYPE DeleteWorksheetRows(MCObjectHandle worksheet, short startRow, short numRows)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetTopVisibleWorksheet()
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetWkSheetSubrowCellActualString(MCObjectHandle worksheet, const ViewPt& cell, Sint16 subrow, TXString& cellString)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellAlignment(MCObjectHandle worksheet, const ViewPt& cell, short& cellAlignment)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellBorder(MCObjectHandle worksheet, const ViewPt& cell, Boolean& top, Boolean& left, Boolean& bottom, Boolean& right)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellFill(MCObjectHandle worksheet, const ViewPt& cell, short& style, ColorRef& bgcolor, ColorRef& fgcolor, short& fillpattern)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellFormula(MCObjectHandle worksheet, const ViewPt& cell, TXString& formula)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellNumberFormat(MCObjectHandle worksheet, const ViewPt& cell, short& style, short& accuracy, TXString& leaderString, TXString& trailerString)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellString(MCObjectHandle worksheet, const ViewPt& cell, TXString& cellString)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellTextFormat(MCObjectHandle worksheet, const ViewPt& cell, short& fontIndex, short& size, short& style)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellTextAngle(MCObjectHandle worksheet, const ViewPt& cell, short& angle)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellTextColor(MCObjectHandle worksheet, const ViewPt& cell, ColorRef& color)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellValue(MCObjectHandle worksheet, const ViewPt& cell, double& cellValue)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellVertAlignment(MCObjectHandle worksheet, const ViewPt& cell, short& vAlignment)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellWrapTextFlag(MCObjectHandle worksheet, const ViewPt& cell, Boolean& wrapTextFlag)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, short& sort1, short& sort2, short& sort3, short& sum1, short& sum2, short& sum3)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetColumnWidth(MCObjectHandle worksheet, short column, short& width)
		{
	
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetWorksheetFromImage(MCObjectHandle worksheetImage)
		{
				return NULL;
		}
		virtual MCObjectHandle VCOM_CALLTYPE GetWorksheetImage(MCObjectHandle worksheet)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE GetWorksheetMergedCellRange(MCObjectHandle worksheet, const ViewPt& cell, ViewPt& topLeftCell, ViewPt& bottomRightCell)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetWorksheetPlacement(MCObjectHandle worksheet, ViewRect& windowPosition)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetRowColumnCount(MCObjectHandle worksheet, short& numRows, short& numColumns)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetRowHeight(MCObjectHandle worksheet, short row, short& height)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetRowHLockState(MCObjectHandle worksheet, short row, Boolean& lockState)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetSelection(MCObjectHandle worksheet, ViewPt& currentCell, ViewPt& topLeftRangeCell, short& topRangeSubrow, ViewPt& bottomRightRangeCell, short& bottomRangeSubrow)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCellString(MCObjectHandle worksheet, const ViewPt& cell, short subrow, TXString& cellString)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCellValue(MCObjectHandle worksheet, const ViewPt& cell, short subrow, double& cellValue)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetSubrowCount(MCObjectHandle worksheet, short databaseRow, short& numSubrows)
		{
	
		}

		virtual void VCOM_CALLTYPE InsertWorksheetColumns(MCObjectHandle worksheet, short beforeColumn, short numColumns)
		{
	
		}
		virtual void VCOM_CALLTYPE InsertWorksheetRows(MCObjectHandle worksheet, short beforeRow, short numRows)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetCell(MCObjectHandle worksheet, const ViewPt& cell)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetRange(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsValidWorksheetSubrowCell(MCObjectHandle worksheet, const ViewPt& cell, short subrow)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetCellNumber(MCObjectHandle worksheet, const ViewPt& cell)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetCellString(MCObjectHandle worksheet, const ViewPt& cell)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetDatabaseRow(MCObjectHandle worksheet, short databaseRow)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetSubrowCellNumber(MCObjectHandle worksheet, const ViewPt& cell, short subrow)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetSubrowCellString(MCObjectHandle worksheet, const ViewPt& cell, short subrow)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE IsWorksheetVisible(MCObjectHandle worksheet)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RecalculateWorksheet(MCObjectHandle worksheet)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTopVisibleWorksheet(MCObjectHandle worksheet)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellAlignment(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short cellAlignment)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellBorder(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellBorders(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline, Boolean insideHorz, Boolean insideVert)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellFill(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, ColorRef bgcolor, ColorRef fgcolor, short fillpattern)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellFormula(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, const TXString& formula)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellNumberFormat(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, short accuracy, const TXString& leaderString, const TXString& trailerString)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellTextFormat(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short fontIndex, short size, short style)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellTextAngle(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short angle)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellTextColor(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, ColorRef color)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellVertAlignment(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short vAlignment)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellWrapTextFlag(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean wrapTextFlag)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, short sort1, short sort2, short sort3, short sum1, short sum2, short sum3)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetColumnWidth(MCObjectHandle worksheet, short fromColumn, short toColumn, short width)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCurrentCell(MCObjectHandle worksheet, const ViewPt& currentCell)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetPlacement(MCObjectHandle worksheet, const ViewRect& windowPosition)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetRowsHeight(MCObjectHandle worksheet, short fromRow, short toRow, short height, Boolean updatePalette, Boolean lockHeight)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetSelection(MCObjectHandle worksheet, const ViewPt& currentCell, const ViewPt& topLeftRangeCell, short topRangeSubrow, const ViewPt& bottomRightRangeCell, short bottomRangeSubrow)
		{
	
		}


		virtual void VCOM_CALLTYPE ShowWorksheet(MCObjectHandle worksheet, Boolean show)
		{
	
		}
		virtual void VCOM_CALLTYPE ShowWorksheetDialog(short dialogType)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE WorksheetMergeCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WorksheetSplitCells(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GSCloseResFile(short inFileID)
		{
	
		}
		virtual void VCOM_CALLTYPE GetCurrentWorkspaceFile(TXString& outFileName)
		{
	
		}
		virtual short VCOM_CALLTYPE OpenExternalResFile(const TXString& inFileName, Byte fileAccessPerm)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE OpenWorkspaceResFile(const TXString& inFileName, Boolean createNewFile, Byte fileAccessPerm)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SetWorkspaceFileToReload(const TXString& inFileName)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE WSAddMenu(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuName)
		{
			return false;

		}
		virtual Boolean VCOM_CALLTYPE WSAddMenuItem(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName, char inShortcutKey, Uint32 inShortcutKeyModifiers, const TXString& inSubMenuIdentifier)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSAddTool(Sint32 inWorkspaceReference, const TXString& inToolIdentifier, char inShortcutKey, Uint32 inKeyModifiers)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSAddToolPalette(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSAddToolSet(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSGetVersion(Sint32 inWorkspaceReference, Sint32* outWorkspaceVersion)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSMenuAddMenuItem(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSMenuBarAddMenu(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSOpen(const TXString& inWorkspaceFileToOpen, Sint32 inFilePermissions, Sint32* outWorkspaceReference)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSPaletteGetHomeCorner(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, short* outWindowHomeCorner)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSPaletteSetHomeCorner(Sint32 inWorkspaceReference, const TXString& inPaletteIdentifier, short inWindowHomeCorner)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSSetVersion(Sint32 inWorkspaceReference, Sint32 inWorkspaceVersion)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSToolPaletteAddToolSet(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, const TXString& inToolSetIdentifier)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSToolSetAddTool(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE WSToolSetAddToolChildToTool(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, const TXString& inParentToolIdentifier, const TXString& inChildToolIdentifier)
		{
			return false;
		}

	// VW2009
	public:
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFileInStandardFolder(GS_ForEachFilePathProcPtr processFile, EFolderSpecifier folderSpec, void* env)
		{
			return kStopForEachFile_NoError;
		}

		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInStandardFolder(GS_ForEachFilePathProcPtr processFile, FolderSpecifier folderSpec, void* env)
		{
			return kStopForEachFile_NoError;
		}
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInFolder(GS_ForEachFilePathNProcPtr processFile, IFolderIdentifier* pStartFolderID, bool doRecursive, void* pEnv)
		{
			return kStopForEachFile_NoError;
		}
		virtual EForEachFileResult	VCOM_CALLTYPE ForEachFilePathInPluginFolder(GS_ForEachFilePathNProcPtr processFile, void* pEnv)
		{
			return kStopForEachFile_NoError;
		}
		virtual bool VCOM_CALLTYPE GetActiveDocument(IFileIdentifier** ppOutFileID, bool& outSaved)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE OpenDocumentPath(IFileIdentifier* pFileID, bool bShowErrorMessages)
		{
			return false;
		}
		virtual GSError VCOM_CALLTYPE SaveActiveDocumentPath(IFileIdentifier* pFileID)
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE EncryptVSPluginFile(IFileIdentifier* pPluginFileID, bool doObfuscation)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE ReadVSExternalFile(IFileIdentifier* pFileID, TMPExternalDataForWorkspace& outData)
		{
			return false;
		}
		virtual short VCOM_CALLTYPE ImportDXF(IFileIdentifier* pFileID)
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE WriteMaterialImageFile(IFileIdentifier* pFileID, MCObjectHandle hMaterial, Sint32 type, Sint32 shaderFamily)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ReadMaterialImageFile(IFileIdentifier* pFileID)
		{
				return NULL;
		}

		virtual void VCOM_CALLTYPE ClearComponentInstances(MCObjectHandle hContainer, TComponentTypeID componentTypeID)
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE FindFirstComponentInstance(MCObjectHandle hContainer, TComponentTypeID componentTypeID)
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE FindNextComponentInstance(TComponentTypeID componentTypeID, MCObjectHandle hComponent)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE AssignAsComponentInstance(MCObjectHandle hParentContainer, TComponentTypeID componentTypeID, MCObjectHandle hComponent)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE EnableComponentInstance(MCObjectHandle hComponent, bool bEnable)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE IsEnabledComponentInstance(MCObjectHandle hComponent)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetComponentInstanceTypeID(MCObjectHandle hComponent, TComponentTypeID& outComponentTypeID)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetComponentInstanceName(MCObjectHandle hComponent, const TXString& localizedName)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetComponentInstanceName(MCObjectHandle hComponent, TXString& outLocalizedName)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE EmptyToolHighlightingList()
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingObject(MCObjectHandle hHighlightObject)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingSegment( const WorldPt& startPt,  const WorldPt& endPt)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE AddToolHighlightingPolyCreate()
		{
			return NULL;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingPoly(MCObjectHandle polyID, bool bClosed)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingPolyAddVertex(MCObjectHandle polyID, const WorldPt& pt, VertexType type, WorldCoord arcRadius)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingSegment3D( const WorldPt3& startPt,  const WorldPt3& endPt)
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE AddToolHighlightingPoly3DCreate()
		{
			return NULL;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingPoly3D(MCObjectHandle polyID, bool bClosed)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddToolHighlightingPoly3DAddVertex(MCObjectHandle polyID, const WorldPt3& pt)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE OpenURL(const TXString& url)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertNurbsToPolylineArcs(MCObjectHandle hNurbs, double precision, bool insert)
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE CreateOffsetObjectHandle(MCObjectHandle h, double offset, bool smoothConers)
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE UnfoldSurface(MCObjectHandle surfaceToUnfold, short conversionRes)
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE CreateWallHoleGroup(MCObjectHandle h)
		{
				return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallHoleGroup(MCObjectHandle h)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE SetDefaultTextureMapping(MCObjectHandle h, TexturePartSDK partID)
		{
	
		}
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfo(MCObjectHandle h, TexturePartSDK partID)
		{
			TextureMappingInfoSDK infoSDK;
			memset(&infoSDK, 0, sizeof(TextureMappingInfoSDK));
	
			return infoSDK;
		}
		virtual void VCOM_CALLTYPE SetTextureMappingInfo(MCObjectHandle h, TexturePartSDK partID, const TextureMappingInfoSDK& mappingInfo)
		{
	
		}
		virtual MCObjectHandle  VCOM_CALLTYPE PerformMultipleUnion(int numberOf2dObjsToAdd, MCObjectHandle h, bool insert)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetWorksheetSubrowHeight(MCObjectHandle worksheet, short databaserow, short subrow, short& height)
		{
	
		}
		virtual bool VCOM_CALLTYPE SetCustomObjectWallHoleGroup(MCObjectHandle objectHand, MCObjectHandle hGeomGroup)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetCustomObjectSelectionGroup(MCObjectHandle objectHand)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE SetCustomObjectSelectionGroup(MCObjectHandle objectHand, MCObjectHandle hSelGroup)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWallFootPrint(MCObjectHandle hWall)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE ExportResource(MCObjectHandle resource, IFileIdentifier* pFileID , bool suppressDialogs)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE CallDefaultTool(ToolMessage* message, std::shared_ptr<void>& messageContext)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE EnableDrawingWorksheetPalette(bool enable, MCObjectHandle worksheet)
		{
	
		}
		virtual bool VCOM_CALLTYPE GetWorksheetAutoRecalcState(MCObjectHandle worksheet)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetWorksheetAutoRecalcState(MCObjectHandle worksheet, bool state)
		{
	
		}

	// VW2010
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWorkingPlane(const Axis &theAxis, const TXString& name)
		{
				return NULL;
		}
		virtual Axis VCOM_CALLTYPE SetWPHybridTool(bool bRestore)
		{
			Axis axis;
	
			memset(&axis, 0, sizeof(Axis));
	
			return axis;
		}
		virtual void VCOM_CALLTYPE RestoreWPHybridTool(bool bRestore)
		{
	
		}
		virtual void VCOM_CALLTYPE ClearWPHybridTool()
		{
	
		}
		virtual void VCOM_CALLTYPE SetCursorByView()
		{
	
		}
		virtual bool VCOM_CALLTYPE AddUndoDeselectObj(MCObjectHandle hObject)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddUndoSelectObj(MCObjectHandle hObject)
		{
			return false;
		}
		virtual TOSWndPtr VCOM_CALLTYPE GetLayoutDialogOSHandle(Sint32 dialogID)
		{
			return NULL;
		}
		virtual TOSWndPtr VCOM_CALLTYPE GetLayoutControlOSHandle(Sint32 dialogID, Sint32 itemID)
		{
			return NULL;
		}
		virtual void VCOM_CALLTYPE SetTextureRef(MCObjectHandle object, InternalIndex textureRef, TexturePartSDK texPartID, Sint32 texLayerID)
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetTextureRef(MCObjectHandle object, TexturePartSDK texPartID, Sint32 texLayerID, Boolean resolveByClass)
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetDefaultTextureMapping(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID)
		{
	
		}
		virtual TextureMappingInfoSDK VCOM_CALLTYPE GetTextureMappingInfo(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID)
		{
			TextureMappingInfoSDK infoSDK;
			memset(&infoSDK, 0, sizeof(TextureMappingInfoSDK));
	
			return infoSDK;
		}
		virtual void VCOM_CALLTYPE SetTextureMappingInfo(MCObjectHandle h, TexturePartSDK texPartID, Sint32 texLayerID, const TextureMappingInfoSDK& mappingInfo)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetNumTextureLayers(MCObjectHandle h, TexturePartSDK texPartID)
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE SetStaticTextStyle(Sint32 dialogID, Sint32 itemID, int style)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetStaticTextColor(Sint32 dialogID, Sint32 itemID, int red, int green, int blue)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetItemClickable(Sint32 dialogID, Sint32 itemID, bool clickable)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetSliderLiveUpdate(Sint32 dialogID, Sint32 itemID, bool liveUpdate)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreatePaintNode(IDrawPad* pDrawPad)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE DrawSymbolPreview(IDrawPad* pDrawPad, InternalIndex resourceRefNum, const ViewRect& destRect, short viewMode, short renderMode, ViewRect* outDrawBounds)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE NotifyClassChange(StatusData liAdditionalData)
		{
	
		}
		virtual bool VCOM_CALLTYPE RegisterDialogForTimerEvents(Sint32 dialogID, Uint32 numberOfMilliseconds)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeregisterDialogFromTimerEvents(Sint32 dialogID)
		{
	
		}
		virtual bool VCOM_CALLTYPE SetImageControlData(Sint32 nDialogID, Sint32 nComponentID, void *imageData, size_t imageDataByteSize)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetListItemEnabled(Sint32 dialogID, Sint32 componentID, short itemIndex, bool enabled)
		{
	
		}
		virtual void VCOM_CALLTYPE SetFullBreakRecord(MCObjectHandle theWall, short index, WorldCoord off, SymbolBreakType* breakData)
		{
		}
		virtual bool VCOM_CALLTYPE SetObjectAsCornerBreak(MCObjectHandle objectHandle, MCObjectHandle wallHandle, bool CornerBreak)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetObjectWallOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord offset)
		{
			return false;
		}
		virtual EWallCapAttributesType VCOM_CALLTYPE GetWallCapAttributesType(MCObjectHandle wall)
		{
			return eWallCapAttributesType_wallLine;
		}
		virtual void VCOM_CALLTYPE SetWallCapAttributesType(MCObjectHandle wall, EWallCapAttributesType wallCapAttributesType)
		{
	
		}
		virtual short VCOM_CALLTYPE GetCoreWallComponent(MCObjectHandle object)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SetCoreWallComponent(MCObjectHandle object, short componentIndex)
		{
	
		}
		virtual EWallHoleTexturePart VCOM_CALLTYPE GetWallHoleTexturePart(MCObjectHandle object)
		{
			return eWallHoleTexturePart_holes;
		}
		virtual void VCOM_CALLTYPE SetWallHoleTexturePart(MCObjectHandle object, EWallHoleTexturePart part)
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateWallFeature(MCObjectHandle wall, MCObjectHandle profile, EWallFeatureType wallFeatureType)
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetActiveLayer()
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateCustomObjectByMatrixEx(const TXString& name, const TransformMatrix& matrix, bool bInsert)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE SetHighlightedHelpString(const TXString& helpMessage)
		{
	
		}
		virtual void VCOM_CALLTYPE GetCurrentLocalization(TXString& outLanguage, TXString& outSubLanguage)
		{
	
		}
		virtual void VCOM_CALLTYPE RGBToColorIndexN(const RGBColor& rgb, ColorRef& colorIndex, Boolean bIgnoreBlackBackground)
		{
	
		}
		virtual void VCOM_CALLTYPE ColorIndexToRGBN(ColorRef colorIndex, RGBColor& rgb, Boolean bIgnoreBlackBackground)
		{
	
		}
		virtual void VCOM_CALLTYPE RefreshRenderingForSelectedObjects()
		{
	
		}
		virtual void VCOM_CALLTYPE RefreshResourceBrowserResourcesList(bool immediate)
		{
	
		}
		virtual bool VCOM_CALLTYPE GetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short& outPatternIndex)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetListBrowserItemPatternIndex(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short patternIndex)
		{
			return false;
		}

		virtual InternalIndex VCOM_CALLTYPE SetDashStyle(const TXString& name, bool scaleWithThick, const std::vector<double>& inVectors)
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE PointInsideAnEnclosedRegionOfTheGroup(MCObjectHandle h, WorldPt &pickPt)
		{
			return false;
		}

	// VW2011
	public:
		virtual MCObjectHandle  VCOM_CALLTYPE CreateArcLengthDimension(const WorldPt& dimStartPt, const WorldPt& dimEndPt, const WorldPt& arcCenterPt, const WorldCoord& startOffset, const bool clockwiseArc, bool witnessPerpChord, const bool arcIndicator)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE GetTextCustomStyle(MCObjectHandle textBlock, Sint32 charNum, unsigned char& customStyle)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextCustomStyle(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char customStyle)
		{
	
		}
		virtual bool VCOM_CALLTYPE GetRoofRunRise(Sint32 dialogID, Sint32 componentID, double& run, double& rise, double& value)
		{
			return false;
		}
		virtual Sint32 VCOM_CALLTYPE CallDefaultToolN(EDefaultToolType type, bool isStandard, ToolMessage* message, std::shared_ptr<void>& messageContext)
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE SetModeBarButtonsHelpText(const TXStringArray& arrHelpText)
		{
			return false;
		}

		virtual Sint32 VCOM_CALLTYPE Deprecated1340(short inHotSpotType, const WorldPt3& inLocation, Sint32 inCursorID, const TXString& inTip, Sint32 data)
		{
			return 0;
		}

		virtual HotSpotRefID VCOM_CALLTYPE TrackHotSpotN(Boolean& outIs3d, WorldPt3& outLocation, Sint32& outData)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE ShowRecFormatResourceDialog(MCObjectHandle& hFormat, Boolean isNewResource, bool hideInvisibleParameters)
		{
	
		}
		virtual bool VCOM_CALLTYPE AlignColumnEdge(Sint32 dialogID, Sint32 srcItemID, short columnID, short alignMode )
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DeleteSymbolDefinition(MCObjectHandle hSymDef, Boolean bCompletely, Boolean useUndo)
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetTilePopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return -1;

		}
		virtual short VCOM_CALLTYPE GetTilePopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetTilePopupSelectedItem(Sint32 dialogID, Sint32 componentID)
		{
			return 0;
		}
		virtual InternalIndex	VCOM_CALLTYPE GetHatchPopupObject(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return -1;

		}
		virtual short VCOM_CALLTYPE GetHatchPopupObjectItemIndex(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetHatchPopupSelectedItem(Sint32 dialogID, Sint32 componentID)
		{
			return 0;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateTile(const TXString& name)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE ShowEditTileDialog(MCObjectHandle& tileHandle)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE ShowEditTileSettingsDialog(MCObjectHandle& tileHandle)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ShowNewTileDialog ()
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE GetTileBackgroundColor(MCObjectHandle tile, ColorRef& backgroundColor)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetTileBackgroundColor(MCObjectHandle tile , const ColorRef& backgroundColor)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetTileGeometryGroup (MCObjectHandle tileHandle)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE GetListBrowserItemTileRefNumber(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 &liRefNumber)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetListBrowserItemTileRefNumber(Sint32 dialogID, Sint32 componentID, int itemIndex, int iSubItemIndex, Sint32 liRefNumber)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE AddToolEditTextMethod(const TXString & label, const TXString & value)
		{
	
		}
		virtual void VCOM_CALLTYPE SetToolEditTextMethodValue(short group, const TXString& value)
		{
	
		}
		virtual TXString VCOM_CALLTYPE GetToolEditTextMethodValue(short group)
		{
			return TXString("error");
		}
		virtual void VCOM_CALLTYPE EditRealConvertToStringUtility(short editRealType, double value, TXString& valueText)
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GSNewObjectHandle(short objectType)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE InvalObj(MCObjectHandle h)
		{
	
		}
		virtual bool VCOM_CALLTYPE SetTextAdorner(MCObjectHandle textBlock, MCObjectHandle textAdorner, const WorldPt& scalePt)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlItemText(Sint32 dialogID, Sint32 componentID, int nItemID, TXString& itemText)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlSelectedItemText(Sint32 dialogID, Sint32 componentID, TXString& itemText)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AddTileGeometryObject(MCObjectHandle tileHandle, MCObjectHandle objectHandle)
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE GetTileGroupParent(MCObjectHandle objectHandle)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE IsTileGroupContainedObject(MCObjectHandle objectHandle)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetObjectPlanarBounds(MCObjectHandle h, WorldRectVerts& outBoxVerts)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetCurrToolInteractiveDraw(IToolInteractiveDraw** outInteractiveDraw)
		{
	
		}
		virtual bool VCOM_CALLTYPE ArePlanarMatricesCoplanar(TransformMatrix & inMat1, TransformMatrix & inMat2, TransformMatrix& outTransformFrom2To1)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DrawCoordLineOnPlane( const WorldPt& pt1, const WorldPt& pt2, TPlanarRefID refID )
		{
	
		}
		virtual void VCOM_CALLTYPE DrawCoordLineOnPlane3D( const WorldPt& pt1, const WorldPt& pt2, TPlanarRefID refID )
		{
	
		}
		virtual bool VCOM_CALLTYPE GetPlanarMatrix(const TPlanarRefID& planarRefID, TransformMatrix& outMatrix)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetPlanarRefID( MCObjectHandle objectHandle, TPlanarRefID& outRefID )
		{
	
		}
		virtual bool VCOM_CALLTYPE IsScreenPlanarRefID(const TPlanarRefID& planarRefID)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE IsPlanarObject( MCObjectHandle objectHandle, TPlanarRefID& outPlanarRefID )
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE IsPlanarObjectIn3DView( MCObjectHandle objectHandle )
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE PlanarPtTo3DModelPt( const TPlanarRefID& refID, const WorldPt& inPt, WorldPt3& outPt )
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE PlanarPtToScreenPlanePt( const TPlanarRefID& refID, WorldPt& outPt)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ScreenPlanePtToPlanarPt( const TPlanarRefID& refID, WorldPt& outPt )
		{
	
		}
		virtual void VCOM_CALLTYPE SetPlanarRefID( MCObjectHandle objectHandle, const TPlanarRefID& refID )
		{
	
		}
		virtual void VCOM_CALLTYPE SetPlanarRefIDToGround( MCObjectHandle objectHandle )
		{
	
		}
		virtual TPlanarRefID VCOM_CALLTYPE GetCurrentPlanarRefID( )
		{
			return kPlanarRefID_ScreenPlane;
		}
		virtual short VCOM_CALLTYPE GetObjectTypeN(MCObjectHandle h)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE ResizeSelectedDims( MCObjectHandle origH, const WorldCoord valueChange, const Sint32 dimCount, const Boolean onDraw, const Boolean dimLineResize, const Boolean fixedLengthWitLines )
		{
	
		}
		virtual TXString VCOM_CALLTYPE GetImageFileName(TXString &resourceFileName, Sint32 family, MCObjectHandle imageNode)
		{
			return TXString("error");
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateImageDefNodeFromPNGData(void* pngData, size_t pngDataSize)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE CompressTextureImage(MCObjectHandle image)
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateTextureBitmapNoDialog(MCObjectHandle parentShaderRecord)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE ShowListBrowserRadioToolTips(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE Default2DToolDrawNew(const TPlanarRefID& planarRefID)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextStyleRef(MCObjectHandle object, InternalIndex styleRef)
		{
	
		}
		virtual InternalIndex VCOM_CALLTYPE GetTextStyleRef(MCObjectHandle object)
		{
			return -1;

		}
		virtual short VCOM_CALLTYPE AlertQuestionDefault(const TXString& question, const TXString& advice, short defaultButton, const TXString& OKOverrideText, const TXString& CancelOverrideText, const TXString& customButtonAText, const TXString& customButtonBText, const TXString& category, const TXString& item, const TXString& checkboxOverrideText, short defaultAnswer)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE SetColorName(ColorRef colorIndex, const TXString& colorName)
		{
			return false;
		}
		virtual TXString		VCOM_CALLTYPE GetColorName(ColorRef colorIndex)
		{
			return "error";
		}

		virtual bool VCOM_CALLTYPE IsScreenObject( MCObjectHandle objectHandle )
		{
			return false;
		}
		virtual bool	        VCOM_CALLTYPE PieceWiseNurbsCurveReverseInPlace( MCObjectHandle objectHandle )
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreatePieceWiseNurbsCurveReverse( MCObjectHandle objectHandle )
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateSlab(MCObjectHandle profile)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE ModifySlab(MCObjectHandle slab, MCObjectHandle modifier, bool isClipObject, Uint32 componentFlags)
		{
			return false;
		}
		virtual InternalIndex	VCOM_CALLTYPE GetSlabStyle(MCObjectHandle slab)
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetSlabStyle(MCObjectHandle slab, InternalIndex slabStyle)
		{
	
		}
		virtual void VCOM_CALLTYPE ConvertToUnstyledSlab(MCObjectHandle slab)
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetSlabPreferencesStyle()
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetSlabPreferencesStyle(InternalIndex slabStyle)
		{
	
		}
		virtual void VCOM_CALLTYPE BeginMultipleDuplicate()
		{
	
		}
		virtual void VCOM_CALLTYPE EndMultipleDuplicate()
		{
	
		}
		virtual void VCOM_CALLTYPE BuildConstraintModelForObject(MCObjectHandle objectHandle, bool traverseContainers)
		{
	
		}
		virtual void VCOM_CALLTYPE RecordModifiedObjectInConstraintModel(MCObjectHandle objectHandle, bool useSelection)
		{
	
		}
		virtual Boolean	        VCOM_CALLTYPE GetCurveEndsAndTangents( MCObjectHandle objectHandle, WorldPt3& startPt, WorldPt3& endPt, WorldPt3& startTangent, WorldPt3& endTangent )
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE AreWorksheetGridLinesVisible( MCObjectHandle worksheet)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetWorksheetGridLinesVisibility( MCObjectHandle worksheet, Boolean bVisible)
		{
	
		}
		virtual bool VCOM_CALLTYPE AreUpdateChecksEnabled(void)
		{
			return false;
		}	// returns true if update checking is supported
		virtual void VCOM_CALLTYPE CheckForUpdates(void)
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateCustomObjectPathNoOffset(const TXString& name, MCObjectHandle pathHand, MCObjectHandle profileGroupHand)
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE NumberCustomDimensionStandards(void)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE ConsolidatePlanarObjects(const MCObjectHandle objectHandle, MCObjectHandle& objectHandleToBeTransformed)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE FindClosestPointOnNURBSObjectFrom3DPoint(MCObjectHandle h, const WorldPt3& point3D, WorldPt3 &outClosestPoint)
		{
			return false;
		}
		virtual WorldCoord VCOM_CALLTYPE GetSlabHeight(MCObjectHandle slab)
		{
			return 0.0;
		}
		virtual void VCOM_CALLTYPE SetSlabHeight(MCObjectHandle slab, WorldCoord height)
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateSlabStyle(const TXString &slabStyleName)
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetWallPreferences()
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetSlabPreferences()
		{
				return NULL;
		}
		virtual ETextureSet VCOM_CALLTYPE GetTextureSet(MCObjectHandle object)
		{
			return eTextureSet_objectTextures;
		}
		virtual void VCOM_CALLTYPE SetTextureSet(MCObjectHandle object, ETextureSet textureSet)
		{
	
		}
		virtual short VCOM_CALLTYPE GetDatumSlabComponent(MCObjectHandle object)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE SetDatumSlabComponent(MCObjectHandle object, short componentIndex)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetComponentOffsetFromWallTop(MCObjectHandle object, short componentIndex, WorldCoord &offsetFromWallTop)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentOffsetFromWallTop(MCObjectHandle object, short componentIndex, WorldCoord offsetFromWallTop)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentOffsetFromWallBottom(MCObjectHandle object, short componentIndex, WorldCoord &offsetFromWallBottom)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentOffsetFromWallBottom(MCObjectHandle object, short componentIndex, WorldCoord offsetFromWallBottom)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentFollowTopWallPeaks(MCObjectHandle object, short componentIndex, Boolean &followTopWallPeaks)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentFollowTopWallPeaks(MCObjectHandle object, short componentIndex, Boolean followTopWallPeaks)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentFollowBottomWallPeaks(MCObjectHandle object, short componentIndex, Boolean &followBottomWallPeaks)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentFollowBottomWallPeaks(MCObjectHandle object, short componentIndex, Boolean followBottomWallPeaks)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentAutoBoundEdgeOffset(MCObjectHandle object, short componentIndex, EWallBound &autoBoundEdgeOffset)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentAutoBoundEdgeOffset(MCObjectHandle object, short componentIndex, EWallBound autoBoundEdgeOffset)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentManualEdgeOffset(MCObjectHandle object, short componentIndex, WorldCoord &manualEdgeOffset)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentManualEdgeOffset(MCObjectHandle object, short componentIndex, WorldCoord manualEdgeOffset)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE GetComponentTexture(MCObjectHandle object, short componentIndex, InternalIndex &texture)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetComponentTexture(MCObjectHandle object, short componentIndex, InternalIndex texture)
		{
			return false;
		}
		virtual WorldCoord VCOM_CALLTYPE GetComponentNetArea(MCObjectHandle object, short componentIndex)
		{
			return 0.0;
		}
		virtual WorldCoord VCOM_CALLTYPE GetComponentNetVolume(MCObjectHandle object, short componentIndex)
		{
			return 0.0;
		}
		virtual void VCOM_CALLTYPE FontMapReplace(const TXStringArray& arrFonts, bool doUserInterface)
		{
	
		}
		virtual void VCOM_CALLTYPE FontMapGetReplacement(const TXString& orgFont, TXString& outReplFont)
		{
	
		}
		virtual short VCOM_CALLTYPE ConvertFontIDToIndex(short fontID)
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE ConvertIndexToFontID(short fontIndex)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE Get2DPolyAreaAndPerimeter(MCObjectHandle h, double &area, double &perimeter)
		{
	
		}
		virtual void VCOM_CALLTYPE IFC_ResetGUID(MCObjectHandle hRecord)
		{
	
		}
		virtual bool VCOM_CALLTYPE IFC_IsIFCRecord(MCObjectHandle hRecord)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetWallComponentPoly(MCObjectHandle hWall, short componentIndex)
		{
				return NULL;
		}


	// VW2012
	public:
		virtual MCObjectHandle	VCOM_CALLTYPE GetObjectHiddenLine(MCObjectHandle hGeometry3D, double cuttingHeight, bool bottomOfCuttingPlane)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE AddBeforeModifyWorkingPlane()
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE ModelPtToPlanarPt(const TPlanarRefID& refID, const WorldPt3& inModelPt, WorldPt& outPlanarPt)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ImportResourceToCurrentFileN(Sint32 listID, Sint32 index, TImportResourceConflictCallbackProcPtr conflictCallback, void* env)
		{
				return NULL;
		}
		virtual TXString VCOM_CALLTYPE CoordToPrimaryDimensionString(WorldCoord coord)
		{
			return "error";
		}
		virtual TXString VCOM_CALLTYPE CoordToSecondaryDimensionString(WorldCoord coord)
		{
			return "error";
		}
		virtual void VCOM_CALLTYPE GetWallOverallHeights(MCObjectHandle theWall, WorldCoord& overallHeightTop, WorldCoord& overallHeightBottom)
		{
	
		}
		virtual bool VCOM_CALLTYPE SetWallOverallHeights(MCObjectHandle theWall, const SStoryObjectData &bottomData, const SStoryObjectData &topData)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CheckParametricNameConflictWithUI(const TXString& name)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE ShowByClassChoice(Sint32 dialogID, Sint32 componentID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE IsClassChoiceSelected(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SelectClassChoice(Sint32 dialogID, Sint32 componentID, Boolean select)
		{
	
		}
		virtual Sint32 VCOM_CALLTYPE GetMeshVertexCount(MCObjectHandle hMesh)
		{
			return 0;
		}
		virtual WorldPt3 VCOM_CALLTYPE GetMeshVertexAt(MCObjectHandle hMesh, size_t at)
		{
			return WorldPt3(0.0, 0.0, 0.0);
		}
		virtual void VCOM_CALLTYPE SetMeshVertexAt(MCObjectHandle hMesh, size_t at, const WorldPt3& pt)
		{
	
		}
		virtual void VCOM_CALLTYPE RunTempTool(const VWIID& iidToolExt)
		{
	
		}
		virtual bool VCOM_CALLTYPE RenderPoly(MCObjectHandle hPoly, IVertexListener* listener, short convRes)
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE NewCreateCombineIntoSurface(const WorldPt& inPoint, short columnsAndPilastersEnum, bool goThrougLayre, MCObjectHandle listOfObjs)
		{
				return NULL;
		}

		virtual void VCOM_CALLTYPE PushPullPlanarGetInternalProcPtrAndUserData(PushPullHandleCompletionRoutinePtr& outProcPtr, void*& outUserData)
		{
	
		}
		virtual void VCOM_CALLTYPE PushPullPlanarBegin(PushPullHandleCompletionRoutinePtr inCompletionProcPtr, void* inUserData)
		{
	
		}
		virtual void VCOM_CALLTYPE PushPullPlanarAddObjectID(MCObjectHandle inHandleIDOfPlanarObjectToPushPull)
		{
	
		}
		virtual void VCOM_CALLTYPE PushPullPlanarEnd()
		{
	
		}
		virtual bool VCOM_CALLTYPE PushPullPlanarIsEnabled()
		{
			return false;
		}
		virtual void VCOM_CALLTYPE PushPullPlanarSetEnabled(bool inSetVal)
		{
	
		}
		virtual bool VCOM_CALLTYPE PushPullPlanarNeedsPickLoop()
		{
			return false;
		}
		virtual void VCOM_CALLTYPE PushPullPlanarActionHandler(ToolMessage* message, Sint32& outPushPullReturn, bool& outHandledExclusively)
		{
	
		}
		virtual void VCOM_CALLTYPE PushPullPlanarAddPrefButton()
		{
	
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateProxyObjOnLayer(MCObjectHandle hParametric, MCObjectHandle hLayer)
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetProxyParent(MCObjectHandle hProxyObj)
		{
				return NULL;
		}

		virtual InternalIndex	VCOM_CALLTYPE AddClassWithUI(TXString& inOutName)
		{
			return -1;

		}
		virtual bool VCOM_CALLTYPE EditClassWithUI(InternalIndex classIndex)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE EditClassWithUI(InternalIndex* arrClassIndex, size_t len)
		{
			return false;
		}

		virtual void VCOM_CALLTYPE ViewPt2WorldPt(const ViewPt& viewPt, WorldPt& outWorldPt)
		{
	
		}
		virtual bool VCOM_CALLTYPE WorldPt2ViewPt(const WorldPt& worldPt, ViewPt& outViewPt)
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE CloseDocument()
		{
			return false;
		}
		virtual short VCOM_CALLTYPE GetNumStories()
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumLayerLevelTypes()
		{
			return 0;
		}
		virtual short VCOM_CALLTYPE GetNumStoryLayerTemplates()
		{
			return 0;
		}
		virtual TXString		VCOM_CALLTYPE GetLayerLevelType(MCObjectHandle layer)
		{
			return "error";
		}
		virtual bool VCOM_CALLTYPE SetLayerLevelType(MCObjectHandle layer, TXString& layerLevelType)
		{
			return false;
		}
		virtual TXString		VCOM_CALLTYPE GetStoryLayerTemplateName(short index)
		{
			return "error";
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryOfLayer(MCObjectHandle layer)
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetLayerForStory(MCObjectHandle story, const TXString &layerLevelType)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE CreateStory(TXString& name, TXString& suffix)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateLayerLevelType(TXString& name)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateStoryLayerTemplate(TXString& name, double scaleFactor, TXString& layerLevelType, WorldCoord elevationOffset, WorldCoord defaultWallHeight, short& index)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE DeleteStoryLayerTemplate(short index)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE AssociateLayerWithStory(MCObjectHandle layer, MCObjectHandle story)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryAbove(MCObjectHandle story)
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetStoryBelow(MCObjectHandle story)
		{
				return NULL;
		}
		virtual WorldCoord		VCOM_CALLTYPE GetStoryElevation(MCObjectHandle story)
		{
			return 0.0;
		}
		virtual bool VCOM_CALLTYPE SetStoryElevation(MCObjectHandle story, WorldCoord elevation)
		{
			return false;
		}
		virtual TXString		VCOM_CALLTYPE GetStorySuffix(MCObjectHandle story)
		{
			return "error";
		}
		virtual bool VCOM_CALLTYPE SetStorySuffix(MCObjectHandle story, const TXString & suffix)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE HasObjectStoryBounds(MCObjectHandle hObject)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE HasObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id, SStoryObjectData& outData)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id, const SStoryObjectData& data)
		{
			return false;	
		}
		virtual bool VCOM_CALLTYPE DelObjectStoryBounds(MCObjectHandle hObject)
		{
			return false;	
		}
		virtual bool VCOM_CALLTYPE DelObjectStoryBound(MCObjectHandle hObject, TObjectBoundID id)
		{
			return false;	
		}
		virtual size_t VCOM_CALLTYPE GetObjectStoryBoundsCount(MCObjectHandle hObject)
		{
			return 0;
		}
		virtual TObjectBoundID	VCOM_CALLTYPE GetObjectStoryBoundsAt(MCObjectHandle hObject, size_t index)
		{
			return 0;
		}
		virtual WorldCoord		VCOM_CALLTYPE GetObjectBoundElevation(MCObjectHandle hObject, TObjectBoundID id)
		{
			return 0.0;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertToPolylineWithTangentVertices(MCObjectHandle hNonPoly)
		{
				return NULL;
		}


		virtual HotSpotRefID VCOM_CALLTYPE AddHotSpotN(short inHotSpotType, const WorldPt3& inLocation, const TXString& cursorSpec, const TXString& inTip, Sint32 data)
		{
			return 0;
		}

		virtual bool VCOM_CALLTYPE CreateImageControl2(Sint32 dialogID, Sint32 controlID, int widthInPixels, int heightInPixels, const TXString& imageSpecifier)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE UpdateImageControl2(Sint32 dialogID, Sint32 controlID, const TXString& imageSpecifier)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE UpdateImageControlUsingFullFilePath(Sint32 dialogID, Sint32 controlID, IFileIdentifier* imgFileID)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateImageButton(Sint32 dialogID, Sint32 controlID, int widthInStdChar, const TXString& imageSpecifier)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE UpdateImageButton(Sint32 dialogID, Sint32 controlID, const TXString& imageSpecifier)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateThumbnailPopup(Sint32 dialogID, Sint32 controlID)
		{
			return false;
		}

		virtual void VCOM_CALLTYPE AddButtonMode(const TXString& iconSpec)
		{
	
		}
		virtual void VCOM_CALLTYPE AddCheckMode(short initialSetting, const TXString& iconSpec)
		{
	
		}
		virtual void VCOM_CALLTYPE AddRadioMode(short initialSetting, const TXStringArray& imageSpecs)
		{
	
		}

		virtual short VCOM_CALLTYPE AddListBrowserImage(Sint32 dialogID, Sint32 componentID, const TXString& imageSpecifier, const TXString& selectedImageSpecifier)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserMultImageIndexes(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, TXString& imageSpec0, TXString& imageSpec1, TXString& imageSpec2)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserMultImageIndexes(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, const TXString& imageSpec0, const TXString& imageSpec1, const TXString& imageSpec2)
		{
			return false;
		}
		virtual int	 VCOM_CALLTYPE InsertEnhancedPullDownMenuItem(Sint32 dialogID, Sint32 componentID, const TXString& strName, const TXString& imageSpecifier)
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE InsertProposedClassOrLayerItem(Sint32 nDialogID, Sint32 nComponentID, const TXString& strLabel, const TXString& iconSpec)
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE AreAlertsAllowed()
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE HasWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType)
		{
			return false;
		}
		virtual EWSColumnDatabaseSortType VCOM_CALLTYPE GetWorksheetColumnSortType(MCObjectHandle worksheet, short databaseRow, short column)
		{
			return kWSSortAscending;
		}
		virtual void VCOM_CALLTYPE SetWorksheetColumnSortType(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseSortType sortType)
		{
	
		}
		virtual short   VCOM_CALLTYPE GetWorksheetColumnSortPrecedence(MCObjectHandle worksheet, short databaseRow, short column)
		{
			return 0;
		}
		virtual void  VCOM_CALLTYPE MoveWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short fromColumn, short toColumn, EWSColumnDatabaseOperatorType operatorType)
		{
	
		}
		virtual void  VCOM_CALLTYPE AddWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType)
		{
	
		}
		virtual void  VCOM_CALLTYPE RemoveAllWorksheetColumnOperators(MCObjectHandle worksheet, short databaseRow, EWSColumnDatabaseOperatorType operatorType)
		{
	
		}
		virtual void  VCOM_CALLTYPE RemoveWorksheetColumnOperator(MCObjectHandle worksheet, short databaseRow, short column, EWSColumnDatabaseOperatorType operatorType)
		{
	
		}
		virtual void VCOM_CALLTYPE GetStoryBoundChoiceStrings(MCObjectHandle story, bool topBound, TXStringArray& strings)
		{
	
		}
		virtual void VCOM_CALLTYPE GetStoryBoundDataFromChoiceString(const TXString& string, SStoryObjectData& data)
		{
	
		}
		virtual void VCOM_CALLTYPE GetChoiceStringFromStoryBoundData(const SStoryObjectData& data, TXString& string)
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateRenderworksStyle()
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE Get3DObjEdgeData(const ViewPt& viewPt, MCObjectHandle objectH, WorldPt3& edgeStart, WorldPt3& edgeEnd)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetStoryLayerTemplateInfo(short index, TXString& name, double& scaleFactor, TXString& layerLevelType, double& elevationOffset, double& defaultWallHeight)
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE GetObjectGeneratingAutoPlane()
		{
				return NULL;
		}

		virtual WorldCoord		VCOM_CALLTYPE GetVertexMaxRadius(MCObjectHandle h, short vertexNum)
		{
			return 0.0;
		}

		virtual void VCOM_CALLTYPE AlertSetAlwaysDoValue(const TXString& category, const TXString& item, short value)
		{
	
		}

		virtual int	 VCOM_CALLTYPE GetCSGAction(MCObjectHandle hCSG)
		{
			return 0;
		}

		virtual Boolean VCOM_CALLTYPE BeginInteractiveFrames()
		{
			return false;
		}
		virtual void VCOM_CALLTYPE DrawInteractiveFrame()
		{
	
		}
		virtual void VCOM_CALLTYPE EndInteractiveFrames()
		{
	
		}
		virtual void VCOM_CALLTYPE CreateInteractiveLightGroup()
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE CreateRenderBackground(BackgroundType backgroundType)
		{
				return NULL;
		}

		virtual bool VCOM_CALLTYPE ExportResourceN(MCObjectHandle resource, IFileIdentifier* pFileID, TImportResourceConflictCallbackProcPtr conflictCallback)
		{
			return false;
		}

	// VW2013
	public:
		virtual void VCOM_CALLTYPE CustomBatchConvert(ICustomBatchConvertParams* params)
		{
	
		}
		virtual void VCOM_CALLTYPE GetAllObjectNames(TXStringArray& names)
		{
	
		}
		virtual void VCOM_CALLTYPE GetAllLayerNames(TXStringArray& names)
		{
	
		}
		virtual void VCOM_CALLTYPE SetListBoxTabStops( Sint32 dialogID, Sint32 componentID, int numTabStops, int* tabStops )
		{
	
		}
		virtual void VCOM_CALLTYPE SupportCustomControlKeyEvents( Sint32 dialogID, Sint32 componentID)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextJustificationN( MCObjectHandle textBlock, short justification)
		{
	
		}
		virtual void VCOM_CALLTYPE SetTextVerticalAlignmentN( MCObjectHandle textBlock, short verticalAlignment)
		{
	
		}
		virtual TXString		VCOM_CALLTYPE GetLayerLevelTypeName(short index)
		{
			return "error";
		}
		virtual bool VCOM_CALLTYPE SetLayerLevelTypeName(short index, const TXString& name)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetStoryLayerTemplateName(short index, const TXString& name)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetUserOriginGlobal(WorldPt& outOrigin)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE CreateSolid(MCObjectHandle blank, const TVWArray_MCObjectHandle &toolList, bool add, MCObjectHandle& newSolid)
		{
			return false;
		}
		virtual TXString VCOM_CALLTYPE GetVectorworksSessionID()
		{
			return "error";
		}
		virtual void VCOM_CALLTYPE EnableListBrowserHierarchicalDisplay(Sint32 dialogID, Sint32 componentID, Boolean enableHierarchicalDisplay)
		{
	
		}
		virtual void VCOM_CALLTYPE SetListBrowserHierarchicalDisplayColumn(Sint32 dialogID, Sint32 componentID, short columnID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserNumericItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, double itemVal, short imageIndex)
		{
			return false;
		}

		virtual TXString		VCOM_CALLTYPE MilsToString(Sint32 value, EThicknessUnitsType unitType)
		{
			return "error";
		}
		virtual Boolean VCOM_CALLTYPE StringToMils(const TXString& str, EThicknessUnitsType unitType, Sint32& outValue)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE StringToArea(const TXString& str, double& outArea)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE StringToVolume(const TXString& str, double& outVolume)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE IsListBrowserDisplayHierarchical(Sint32 dialogID, Sint32 componentID)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE HierarchicalListBrowserItemOpened(Sint32 dialogID, Sint32 componentID, short itemIndex, Boolean recursive, short& outNumbRedisplayedItems)
		{
	
		}
		virtual void VCOM_CALLTYPE HierarchicalListBrowserItemClosed(Sint32 dialogID, Sint32 componentID, short itemIndex, Boolean recursive)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE HierarchicalListBrowserItemIsClosed(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE HierarchicalListBrowserItemIsContainer(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetDisplayedItemsCountInHierarchicalContainer(Sint32 dialogID, Sint32 componentID, short itemIndex, short& outDisplayedItemsCount)
		{

		}
		virtual TXString		VCOM_CALLTYPE GetListBrowserItemOriginalName(Sint32 dialogID, Sint32 componentID, short itemIndex)
		{
			return "error";
		}
		virtual void VCOM_CALLTYPE AddListBrowserOriginalName(Sint32 dialogID, Sint32 componentID, const TXString& originalName)
		{
	
		}
		virtual void VCOM_CALLTYPE GetListBrowserOriginalNameCloseLevels(Sint32 dialogID, Sint32 componentID, const TXString& originalName, Boolean& outLeve1Closed, Boolean& outLevel2Closed, Boolean& outLevel3Closed)
		{
	
		}
		virtual void VCOM_CALLTYPE SetListBrowserOriginalNameCloseLevels(Sint32 dialogID, Sint32 componentID, const TXString& originalName, Boolean level1Closed, Boolean level2Closed, Boolean level3Closed)
		{
	
		}
		virtual void VCOM_CALLTYPE CollapseAllListBrowserItems(Sint32 dialogID, Sint32 componentID)
		{
	
		}
		virtual void VCOM_CALLTYPE ExpandAllListBrowserItems(Sint32 dialogID, Sint32 componentID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE CreateStyledStaticText(Sint32 dialogID, Sint32 componentID, const TXString & strText, short widthInStdChar, EStaticTextType enumType)
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE SetModeBarButtonsText( const TVWModeBarButtonHelpArray& arrModeBarButtonsHelp )
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetToolHelpMessage( const TXString& modeText, const TXString& descriptionText )
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetToolHelpMessageAndTitle( const TXString& titleText, const TXString& modeText, const TXString& descriptionText )
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE FindWallsSurroundingPoint(MCObjectHandle inBoundedObject, const WorldPt& inPoint, short inColumnsAndPilastersEnum,
																		 MCObjectHandle inListOfObjects, bool ignoreClassVisibility, bool bExcludePiosNiches)
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE GetNumAssociations(MCObjectHandle handle)
		{
			return 0;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetAssociation(MCObjectHandle handle, short index, Sint16& associationKind, Sint16& value)
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE AdjustPathForWrapping(TXString& path, short maxWidth)
		{
	
		}

		virtual void VCOM_CALLTYPE DoBatchPrintOrExport(short inBatchOperationType)
		{
	
		}

		virtual void  VCOM_CALLTYPE DeleteObjectNoNotify(MCObjectHandle h)
		{
	
		}

		virtual void VCOM_CALLTYPE EditObjectSpecial(MCObjectHandle h, TObjSpecialEdit editMode)
		{
	
		}

		virtual short VCOM_CALLTYPE GetNumSavedViews()
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE GetSavedView(short index, TXString& view)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE RestoreSavedView(const TXString& savedView)
		{
	
		}

		virtual bool VCOM_CALLTYPE CreateCustomThumbnailPopup(Sint32 dialogID, Sint32 controlID, ThumbnailSizeType sizeKind)
		{
			return false;
		}
		virtual InternalIndex	VCOM_CALLTYPE GetClPenPatN(InternalIndex classIndex)
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetClPenPatN(InternalIndex classIndex, InternalIndex penPat)
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetDefaultPenPatN()
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetDefaultPenPatN(InternalIndex penPat)
		{
	
		}
		virtual InternalIndex	VCOM_CALLTYPE GetPenPatN(MCObjectHandle h)
		{
			return -1;

		}
		virtual void VCOM_CALLTYPE SetPenPatN(MCObjectHandle h, InternalIndex penPat)
		{
	
		}

		virtual void VCOM_CALLTYPE GetLineTypeAttributeData(Sint32 dialogID, Sint32 itemID, InternalIndex& lineStyle, short& lineWeight)
		{
	
		}
		virtual void VCOM_CALLTYPE SetLineTypeAttributeData(Sint32 dialogID, Sint32 itemID, InternalIndex lineStyle, short lineWeight)
		{
	
		}
		virtual void VCOM_CALLTYPE GetLineTypeChoice(Sint32 dialogID, Sint32 itemID, Sint32& lineTypeRefNumber)
		{
	
		}
		virtual void VCOM_CALLTYPE SetLineTypeChoice(Sint32 dialogID, Sint32 itemID, Sint32 lineTypeRefNumber)
		{
	
		}
		virtual void VCOM_CALLTYPE ShowComplexLineTypesInLineAttributePopup(Sint32 dialogID, Sint32 itemID)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetListBrowserItemLineTypeRef(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 &iLineRef, int &iLineWeight)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetListBrowserItemLineTypeRef(Sint32 dialogID, Sint32 componentID, int iItemIndex, int iSubItemIndex, Sint32 iStyleIndex, int iLineWeight)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE IsWorksheetCellImage (MCObjectHandle worksheet, short row, short column, short subrow)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageType (MCObjectHandle worksheet, short row, short column, short& type)
		{
	
		}
		virtual short VCOM_CALLTYPE GetWorksheetCellImageSizeType (MCObjectHandle worksheet, short row, short column)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageSize (MCObjectHandle worksheet, short row, short column, short& height, short& width)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageAngle (MCObjectHandle worksheet, short row, short column, double& angle)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageView (MCObjectHandle worksheet, short row, short column, short& view)
		{
	
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageComponent(MCObjectHandle worksheet, short row, short column, EImageViewComponent& outComponent)
		{

		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageRenderMode (MCObjectHandle worksheet, short row, short column, short& renderMode)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetWorksheetCellImageUseLayerScale (MCObjectHandle worksheet, short row, short column)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageScale (MCObjectHandle worksheet, short row, short column, double& scale)
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetWorksheetCellImageUseObjectImage (MCObjectHandle worksheet, short row, short column)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE GetWorksheetCellImageMarginSize (MCObjectHandle worksheet, short row, short column, unsigned char& marginSize)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageType (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short type)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageSizeType (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short imageSizeType)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageSize (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short height, short width)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageAngle (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, double angle)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageView (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short view)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageComponent(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, EImageViewComponent component)
		{

		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageRenderMode (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short renderMode)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageUseLayerScale (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean useLayerScale)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageScale (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, double scale)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageUseObjectImage (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean useObjectImage)
		{
	
		}
		virtual void VCOM_CALLTYPE SetWorksheetCellImageMarginSize (MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, unsigned char marginSize)
		{
	
		}
		virtual MCObjectHandle	VCOM_CALLTYPE DoPolylineRadiusSmoothing(MCObjectHandle hPoly)
		{
				return NULL;
		}
		virtual Boolean VCOM_CALLTYPE SetImageControlDataN(Sint32 dialogID, Sint32 componentID, VectorWorks::UI::IIcon* icon)
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE AssociateBoundedObjectWithWalls(MCObjectHandle inBoundedObject, TVWArray_MCObjectHandle& wallList, short inColumnsAndPilastersEnum, bool bExcludePiosNiches)
		{
				return NULL;
		}

		virtual Sint32 VCOM_CALLTYPE BuildResourceListN(short objectType, IFileIdentifier* fileID, Sint32& numItems)
		{
			return 0;
		}

		virtual Boolean VCOM_CALLTYPE TrimNurbsSurface(MCObjectHandle iNurbsSurface, MCObjectHandle iNurbsCurve)
		{
			return false;
		}

		virtual void VCOM_CALLTYPE InteractiveViewOperation_Begin(EInteractiveMode type, const ViewPt& viewPt)
		{
	
		}
		virtual void VCOM_CALLTYPE InteractiveViewOperation_End()
		{
	
		}
		virtual void VCOM_CALLTYPE InteractiveViewOperation_Move(const ViewPt& viewPt)
		{
	
		}

		virtual Boolean VCOM_CALLTYPE SetToolByName(const TXString& toolUnivName)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetToolByName(const TXString& toolUnivName, size_t modebarGroupID, size_t modebarButtonID)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE SetToolByIndex(short index)
		{
	
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateLayerWithUI(TXString& name)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE EditLayerWithUI(MCObjectHandle layer)
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE CreateSavedViewWithUI(TXString& outName)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE EditSavedViewWithUI(TXString& inOutName)
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateExtrudeAlongPath2(MCObjectHandle pathHandle, MCObjectHandle profileHandle, Boolean bExponentialScale, double scale, Boolean bLockProfilePlane, Boolean bFixProfile)
		{
				return NULL;
		}
		virtual short VCOM_CALLTYPE SectionSolid(MCObjectHandle obj1, MCObjectHandle obj2, Boolean useSectionColor, Boolean flipSection, MCObjectHandle& newSolid)
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE IsGBXMLExportAllowed()
		{
			return false;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE ConvertToGenericSolid(MCObjectHandle objectHandle )
		{
				return NULL;
		}

		virtual void VCOM_CALLTYPE AddWallToContainer(MCObjectHandle wallHandle, MCObjectHandle container)
		{
	
		}
		virtual void VCOM_CALLTYPE SyncMatrixToStoryBound(MCObjectHandle h, TObjectBoundID id)
		{
	
		}
		virtual void            VCOM_CALLTYPE SplitPolylineByMultiple2DLoci(MCObjectHandle h, TVWArray_WorldPt loci, bool killOriginal, bool insert, TVWArray_MCObjectHandle & arrayHandle)
		{
	
		}

		virtual bool VCOM_CALLTYPE ExportDocumentPreviewImageFile(IFileIdentifier* pFileID, Sint32 compressionType)
		{
			return false;
		}

		virtual void VCOM_CALLTYPE DeleteAssociations(MCObjectHandle h, Sint16 associationKind)
		{
	
		}
		virtual MCObjectHandle  VCOM_CALLTYPE CreateTaperedExtrude2(MCObjectHandle profileH, const double_param angle, const double_param height)
		{
				return NULL;
		}

	// VW 2014
	public:
		virtual Boolean VCOM_CALLTYPE EnableTreeControlDragAndDrop(Sint32 dialogID, Sint32 componentID, Boolean bEnable)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE EnableDragBetweenControls( Sint32 dialogID, Sint32 source, Sint32 destination )
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetTreeControlItemParent( Sint32 dialogID, Sint32 componentID, Sint32 itemID, Sint32 & parentID )
		{
			return false;
		}
		virtual int	 VCOM_CALLTYPE CopyTreeControlSubtree( Sint32 dialogID, Sint32 sourceTree, Sint32 targetTree, Sint32 sourceItem, Sint32 destinationItem, Sint32 destinationItemParent )
		{
			return 0;
		}
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemImage( Sint32 dialogID, Sint32 componentID, Sint32 itemID, const TXString & imageSpecifier )
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetTreeControlItemImageFromIcon( Sint32 dialogID, Sint32 componentID, Sint32 itemID, VectorWorks::UI::IIcon* icon )
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE TrimToSelectedObjectsN(MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2, const Boolean bTrimToSelectedObjects)
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateComplexLineType(const TXString& name)
		{
				return NULL;
		}
		virtual MCObjectHandle	VCOM_CALLTYPE GetComplexLineTypeGeometryGroup (MCObjectHandle lineTypeH)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE AddComplexLineTypeGeometryObject(MCObjectHandle lineTypeH, MCObjectHandle objectH)
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE GetComplexLineTypeGroupParent(MCObjectHandle groupH)
		{
				return NULL;
		}
		virtual bool VCOM_CALLTYPE IsComplexLineTypeGroupContainedObject(MCObjectHandle objectH)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetComplexLineTypePageSpace(MCObjectHandle lineTypeH, Boolean isPageSpace)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE IsComplexLineTypeInPageSpace(MCObjectHandle lineTypeH)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE SetComplexLineTypeGapSize(MCObjectHandle lineTypeH, const WorldCoord newGapSize)
		{
			return false;
		}
		virtual WorldCoord		VCOM_CALLTYPE GetComplexLineTypeGapSize(MCObjectHandle lineTypeH)
		{
			return 0.0;
		}
		virtual Sint32 VCOM_CALLTYPE CreateLayoutDialogFromVWResource(const char* resIdentifier)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE RemoveAllTreeControlItems( Sint32 dialogID, Sint32 componentID )
		{
	
		}

		virtual MCObjectHandle	VCOM_CALLTYPE CreateGroupOutline( MCObjectHandle objectHandle )
		{
				return NULL;
		}

		virtual void VCOM_CALLTYPE SetViewMatrixByVector(const WorldPt3& lookFrom, const WorldPt3& lookTo, const WorldPt3& upVector, TransformMatrix& outMatrix, MCObjectHandle activeViewport)
		{
	
		}

		virtual bool VCOM_CALLTYPE IsCurtainWall( MCObjectHandle hWall )
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE GetCurtainWallPanelInfo( MCObjectHandle hWall, const WorldPt&  inCenterPt, bool includeBottomFrame, WorldPt & outCenterPt, WorldCoord & outWidth, WorldCoord & outHeight )
		{
			return false;
		}

		virtual short VCOM_CALLTYPE GetNumberOfLineTypesItems(Sint32 dialogID, Sint32 itemID)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE GetLineTypeAtIndex(Sint32 dialogID, Sint32 itemID, short index, InternalIndex& outLineTypeRefNumber)
		{
	
		}
		virtual bool VCOM_CALLTYPE GetSimpleLineTypeData(MCObjectHandle lineTypeH, bool& outScaleWithThick, std::vector<double>& outData)
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE Create2DObjectShadow(MCObjectHandle h2DObject, const WorldPt & offsetPt)
		{
				return NULL;
		}

	// VW 2015
	public:
		virtual void VCOM_CALLTYPE GetListOfWorkingPlanes( TVWArray_MCObjectHandle& planesList )
		{
	
		}
		virtual Boolean VCOM_CALLTYPE GetWorkingPlaneInfo( MCObjectHandle planeH, TXString& outName, Axis& outAxis )
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE SetWorkingPlaneInfo( MCObjectHandle planeH, const TXString & name, const Axis axis )
		{
			return false;
		}
		virtual MCObjectHandle VCOM_CALLTYPE DuplicateWorkingPlane( MCObjectHandle planeH )
		{
				return NULL;
		}
		virtual void VCOM_CALLTYPE DeleteWorkingPlane( MCObjectHandle planeH )
		{
	
		}

		virtual void VCOM_CALLTYPE SetTreeControlItemAsDivider(Sint32 dialogID, Sint32 componentID, Sint32 itemID, bool isDivider)
		{
	
		}

		virtual void VCOM_CALLTYPE SysBeep(short duration)
		{
	
		}

		virtual Boolean VCOM_CALLTYPE  GetToolPtCurrentIsSnapped()
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  Project3DModelPtToScreen(const WorldPt3& inwpt3Model, WorldPt& outwptScreen)
		{
			return false;
		}

		virtual MCObjectHandle VCOM_CALLTYPE  GetImageCropObject(MCObjectHandle object)
		{
			return NULL;
		}
		virtual bool VCOM_CALLTYPE  IsImageCropped(MCObjectHandle object)
		{
			return false;
		}
		virtual bool VCOM_CALLTYPE  IsImageCropVisible(MCObjectHandle object)
		{
			return false;
		}
		virtual void VCOM_CALLTYPE  SetImageCropVisible(MCObjectHandle object, bool isVisible)
		{

		}
		virtual bool VCOM_CALLTYPE  SetImageCropObject(MCObjectHandle imageObject, MCObjectHandle cropObject)
		{
			return false;
		}

		virtual void VCOM_CALLTYPE  TransformGraphicObject(MCObjectHandle object, TransformMatrix& inMatrix)
		{
	
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportClassOverrides(MCObjectHandle viewportHandle)
		{
			return 0;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportClassOverrideClass(MCObjectHandle viewportHandle, size_t index)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  CreateViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex, SViewportClassOverride& outOverride)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex, const SViewportClassOverride& inOverride)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportClassOverride(MCObjectHandle viewportHandle, InternalIndex classIndex)
		{
			return false;
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportLightOverrides(MCObjectHandle viewportHandle)
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportLightOverrideLight(MCObjectHandle viewportHandle, size_t index)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  CreateViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex, SViewportLightOverride& outOverride)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex, const SViewportLightOverride& inOverride)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportLightOverride(MCObjectHandle viewportHandle, InternalIndex lightIndex)
		{
			return false;
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportLayerOverrides(MCObjectHandle viewportHandle)
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportLayerOverrideLayer(MCObjectHandle viewportHandle, size_t index)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  CreateViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, SViewportLayerOverride& outOverride)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const SViewportLayerOverride& inOverride)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportLayerOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex)
		{
			return false;
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportLayerPropertiesOverrides(MCObjectHandle viewportHandle)
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportLayerPropertiesOverrideLayer(MCObjectHandle viewportHandle, size_t index)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  CreateViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, SViewportLayerPropertiesOverride& outOverride)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const SViewportLayerPropertiesOverride& inOverride)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportLayerPropertiesOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex)
		{
			return false;
		}

		virtual size_t VCOM_CALLTYPE  GetNumViewportLayerStackingOverrides(MCObjectHandle viewportHandle)
		{
			return -1;
		}
		virtual InternalIndex VCOM_CALLTYPE  GetViewportLayerStackingOverrideLayer(MCObjectHandle viewportHandle, size_t index)
		{
			return -1;
		}
		virtual Boolean VCOM_CALLTYPE  GetViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, Sint32& outStackingPosition)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex, const Sint32& inStackingPosition)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  RemoveViewportLayerStackingOverride(MCObjectHandle viewportHandle, InternalIndex layerIndex)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE  IsDesignLayerViewport(MCObjectHandle hObj)
		{
			return false;
		}

		virtual Boolean VCOM_CALLTYPE  DeleteSavedSetting(const TXString& category)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  DeleteSavedSetting(const TXString& category, const TXString& setting)
		{
			return false;
		}

		virtual MCObjectHandle	VCOM_CALLTYPE  TrackToolViewport(Boolean trackDLVP)
		{
			return NULL;
		}

		virtual void VCOM_CALLTYPE  ForEachObjectInList(MCObjectHandle hFirst, GS_ForEachObjectProcPtr action, void *actionEnv)
		{
	
		}

		virtual OpacityRef VCOM_CALLTYPE  GetClOpacity(InternalIndex classIndex)
		{
			return 0;
		}
		virtual void VCOM_CALLTYPE  SetCLOpacity(InternalIndex classIndex, OpacityRef opacity)
		{
	
		}
		virtual TPlanarRefID VCOM_CALLTYPE  GetWorkingPlanePlanarRefID( )
		{
			return 0;
		}

		virtual Boolean VCOM_CALLTYPE  CreateScriptResource(const TXString& scriptName, const TXString& paletteName, bool paletteOpen, const TXString& script, bool python)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  GetScriptResource(const TXString& scriptName, TXString& outScript, bool& outPython)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  SetScriptResource(const TXString& scriptName, const TXString& script, bool python)
		{
			return false;
		}
		virtual Boolean VCOM_CALLTYPE  OpenScriptResPalette(const TXString& paletteName, bool paletteOpen)
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE GetWallHoleGroupDeep(MCObjectHandle h)
		{
			return NULL;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE CreateTextStyleResource(const TXString &name)
		{
			return NULL;
		}
		virtual Uint32 VCOM_CALLTYPE TickCount()
		{
			return 0;
		}
		virtual bool VCOM_CALLTYPE IsFontAvailable(short fontID)
		{
			return true;
		}
		virtual void VCOM_CALLTYPE ResetVisibilityForSymbol(MCObjectHandle symDef)
		{
	
		}
		virtual void VCOM_CALLTYPE GetStandardFontList (TXStringArray& fontList)
		{
	
		}
		virtual bool VCOM_CALLTYPE CanSymbolBeAddedLegal(MCObjectHandle container, MCObjectHandle symDef)
		{
			return true;
		}
		virtual MCObjectHandle CreateMesh()
		{
			return NULL;
		}
		virtual MCObjectHandle CreateMesh(IMeshData** outMeshData)
		{
			return NULL;
		}
		virtual bool GetMesh(MCObjectHandle hMesh, IMeshData** outMeshData)
		{
			return false;
		}
		virtual MCObjectHandle AddMeshFace(MCObjectHandle hMesh, const TVWArray_SizeT& arrVertexIndices)
		{
			return NULL;
		}
		virtual bool GetPointInsidePoly(MCObjectHandle poly, WorldPt &insideWorldPt)
		{
			return false;
		}

		// Opacity for Gradients added in VW2015
		virtual bool GetGradientDataN(MCObjectHandle gradient, Sint16 segmentIndex, Real64& spotPosition, Real64& midpointPosition, WorldPt3& color, OpacityRef& opacity)
		{
			return false;
		}

		virtual bool GetGradientSliderDataN(Sint32 dialogID, Sint32 componentID, Sint16 segmentIndex, Real64& spotPosition, Real64& midpointPosition, WorldPt3& color, OpacityRef& opacity)
		{
			return false;
		}

		virtual bool GetGradientSpotOpacity(MCObjectHandle gradient, Sint16 segmentIndex, OpacityRef& opacity)
		{
			return false;
		}

		virtual Sint16 InsertGradientSegmentN(MCObjectHandle gradient, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity)
		{
			return 0;
		}

		virtual Sint16 InsertGradientSliderSegmentN(Sint32 dialogID, Sint32 componentID, Real64 spotPosition, const WorldPt3& color, const OpacityRef& opacity)
		{
			return 0;
		}

		virtual bool SetGradientDataN(MCObjectHandle gradient, Sint16& segmentIndex, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity)
		{
			return false;
		}

		virtual bool SetGradientSliderDataN(Sint32 dialogID, Sint32 componentID, Sint16& segmentIndex, Real64 spotPosition, Real64 midpointPosition, const WorldPt3& color, const OpacityRef& opacity)
		{
			return false;
		}

		virtual bool SetGradientSpotOpacity(MCObjectHandle gradient, Sint16 segmentIndex, const OpacityRef& opacity)
		{
			return false;
		}

		virtual size_t GetTreeControlItemNumberOfChildren(Sint32 dialogID, Sint32 componentID, Sint32 itemID)
		{
			return 0;
		}

		virtual Sint32 GetTreeControlItemChildID(Sint32 dialogID, Sint32 componentID, Sint32 parentID, Sint32 index)
		{
			return 0;
		}

		virtual short GetStandardFontListSize()
		{
			return 0;
		}

		virtual MCObjectHandle GetVerticesFromSolid(MCObjectHandle handle)
		{
			return NULL;
		}

		virtual MCObjectHandle GetNurbsCurvesFromSolid(MCObjectHandle handle)
		{
			return NULL;
		}

		virtual MCObjectHandle GetNurbsSurfacesFromSolid(MCObjectHandle handle)
		{
			return NULL;
		}

		virtual MCObjectHandle GetNurbsCurvesOnCuttingPlane(MCObjectHandle handle, const WorldPt3& pointOnPlane, const WorldPt3& planeNormal)
		{
			return NULL;
		}

		virtual Boolean	CustomObjectControlPtGet(MCObjectHandle inOwnerObj, Sint32 dataIndex, WorldPt3& outPt, Boolean* outIs2DOnly, Boolean* outIsHidden, Sint32* outClientID)
		{
			return false;
		}

		virtual MCObjectHandle	CreateImageMaskFromAlphaChannel(MCObjectHandle inImage, bool useAlpha)
		{
			return NULL;
		}

		virtual void SetTreeControlItemSelectionState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, bool select)
		{
		}

		virtual MCObjectHandle VCOM_CALLTYPE ConvertPolylineToPolylineWithOnlyArcVertices(MCObjectHandle handle, bool insert)
		{
			return NULL;
		}

		virtual bool VCOM_CALLTYPE GetTextStyleByClass(MCObjectHandle handle)
		{
			return false;
		}

		virtual void VCOM_CALLTYPE SetTextStyleByClass(MCObjectHandle handle)
		{
		}

		virtual bool VCOM_CALLTYPE GetClUseTextStyle(InternalIndex classId)
		{
			return false;
		}

		virtual void VCOM_CALLTYPE SetClUseTextStyle(InternalIndex classId, bool use)
		{
		}

		virtual InternalIndex VCOM_CALLTYPE GetClTextStyleRef(InternalIndex classId)
		{
			return -1;
		}

		virtual void VCOM_CALLTYPE SetClTextStyleRef(InternalIndex classId, InternalIndex textStyleRef)
		{
		}

		virtual bool VCOM_CALLTYPE SetTextStyleRefN(MCObjectHandle textBlock, short firstChar, short numChars, InternalIndex styleRef)
		{
			return false;
		}

		virtual InternalIndex VCOM_CALLTYPE GetTextStyleRefN(MCObjectHandle h, short atChar)
		{
			return -1;
		}

		virtual bool VCOM_CALLTYPE SetTextStyleByClassN(MCObjectHandle textBlock, short firstChar, short numChars)
		{
			return false;
		}

		virtual bool VCOM_CALLTYPE GetTextStyleByClassN(MCObjectHandle h, short atChar)
		{
			return false;
		}

		virtual bool GetTextTabStopCount(MCObjectHandle textBlock, Sint32& count)
		{
			return false;
		}

		virtual bool GetTextTabStopLocation(MCObjectHandle textBlock, Sint32 index, WorldCoord& location)
		{
			return false;
		}

		virtual bool MoveTextTabStopLocation(MCObjectHandle textBlock, Sint32 index, WorldCoord location)
		{
			return false;
		}

		virtual bool AddTextTabStop(MCObjectHandle textBlock, WorldCoord location)
		{
			return false;
		}
		
		virtual bool RemoveTextTabStop(MCObjectHandle textBlock, Sint32 index)
		{
			return false;
		}

		virtual bool GetTextTrackingValue(MCObjectHandle textBlock, Sint32 index, float& trackingValue)
		{
			return false;
		}

		virtual bool SetTextTrackingValue(MCObjectHandle textBlock, Sint32 index, Sint32 numChars, float trackingValue)
		{
			return false;
		}

		virtual bool GetObjectWallOffset(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord& offset)
		{
			return false;
		}

		virtual bool SetObjectWallHeight(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord height)
		{
			return false;
		}

		virtual bool GetObjectWallHeight(MCObjectHandle objectHandle, MCObjectHandle wallHandle, WorldCoord& height)
		{
			return false;
		}

		virtual void SetHatchReferenceForMaterialNode(MCObjectHandle inMaterial, RefNumber inHatchReference)
		{
		}

		virtual void ClearHatchReferenceForMaterialNode(MCObjectHandle inMaterial)
		{
		}

		virtual RefNumber GetHatchReferenceForMaterialNode(MCObjectHandle inMaterial)
		{
			return 0;
		}

		virtual TXString GetDescriptionText(MCObjectHandle hObj)
		{
			TXString descriptionText;
			return descriptionText;
		}

		virtual bool SetDescriptionText(MCObjectHandle hObj, const TXString& inText)
		{
			return false;
		}

		virtual void RefreshModeBar()
		{
		}

		virtual void ClearClearPullDownMenu(short group)
		{
		}

		virtual Boolean RefreshClassPopup(Sint32 dialogID, Sint32 componentID) 
		{
			return false;
		}


		virtual short GetListBrowserHierarchicalDisplayColumn(Sint32 dialogID, Sint32 componentID)
		{
			return 0;
		}


		virtual MCObjectHandle	VCOM_CALLTYPE GetPDFPageCropObject(MCObjectHandle object)
		{

			MCObjectHandle	hResult		= NULL;

			return hResult;
		}


		virtual bool VCOM_CALLTYPE IsPDFPageCropped(MCObjectHandle object)
		{
	
			return false;
		}


		virtual bool VCOM_CALLTYPE IsPDFPageCropVisible(MCObjectHandle object)
		{

			return false;
		}


		virtual void VCOM_CALLTYPE SetPDFPageCropVisible(MCObjectHandle object, bool isVisible)
		{
	
		}


		virtual bool VCOM_CALLTYPE SetPDFPageCropObject(MCObjectHandle pdfPageObject, MCObjectHandle cropObject)
		{

			return false;
		}


		virtual bool VCOM_CALLTYPE SetPDFPageWidthAndHeight(MCObjectHandle hObject, WorldCoord newWidth, WorldCoord newHeight)
		{

			return false;
		}

		virtual void SetPerspectiveInfo(short projKind, short renderMode, WorldCoord persDistance, const WorldPt &pt1, const WorldPt &pt2)
		{
		}

		virtual void SetCurrentView(TStandardView view, bool direct)
		{
		}

		virtual void CreateSymbolFolderN(const TXString& folderPath, TVWArray_MCObjectHandle & outFolderPath)
		{
	
		}

		virtual bool IsCurrentlyBuildingAnUndoEvent()
		{
			return false;
		}

		virtual bool ShowCustomDimensionStandardsDialog()
		{
			return false;
		}


		virtual short GetNumStoryLevelTemplates()
		{
			return 0;
		}

		virtual TXString GetStoryLevelTemplateName(short index)
		{
			return TXString();
		}

		virtual bool SetStoryLevelTemplateName(short index, const TXString& name)
		{
			return false;
		}

		virtual bool CreateStoryLevelTemplate(TXString& layerName, double scaleFactor, TXString& layerLevelType, WorldCoord elevationOffset, WorldCoord defaultWallHeight, short& index)
		{
			return false;
		}

		virtual bool DeleteStoryLevelTemplate(short index)
		{
			return false;
		}

		virtual bool GetStoryLevelTemplateInfo(short index, TXString& layerName, double& scaleFactor, TXString& levelType, double& elevation, double& defaultWallHeight)
		{
			return false;
		}

		virtual bool AddStoryLevel(MCObjectHandle storyHandle, const TXString& levelType, WorldCoord elevation, const TXString& layerName)
		{
			return false;
		}

		virtual bool AddStoryLevelFromTemplate(MCObjectHandle storyHandle, short index)
		{
			return false;
		}

		virtual bool RemoveStoryLevel(MCObjectHandle storyHandle, const TXString& levelType, bool bDeleteLayer)
		{
			return false;
		}

		virtual bool SetStoryLevelElevation(MCObjectHandle storyHandle, const TXString& levelType, WorldCoord newElevation)
		{
			return false;
		}

		virtual WorldCoord GetStoryLevelElevation(MCObjectHandle storyHandle, const TXString& levelType)
		{
			return 0.0;
		}

		virtual bool ResetDefaultStoryLevels(bool bDeleteExisting)
		{
			return false;
		}

		virtual MCObjectHandle TrackToolInViewportAnnotatons(MCObjectHandle &proxyObj, Boolean &worldObjInVP, bool createProxy)
		{
			return nil;
		}
		virtual Boolean GetComponentTopIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean &topIsRelativeToStory)
		{
			return false;
		}
		virtual Boolean SetComponentTopIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean topIsRelativeToStory)
		{
			return false;
		}
		virtual Boolean GetComponentBottomIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean &bottomIsRelativeToStory)
		{
			return false;
		}
		virtual Boolean SetComponentBottomIsRelativeToStory(MCObjectHandle object, short componentIndex, Boolean bottomIsRelativeToStory)
		{
			return false;
		}
		virtual void ShowListBrowserHeader(Sint32 dialogID, Sint32 componentID, bool show)
		{
			return;
		}

		virtual Boolean GetListBrowserNumericItemInfo(Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString& itemString, double& itemVal, short& imageIndex)
		{
			return false;
		}

		virtual bool GetCurtainWallPanelInfoExtended( MCObjectHandle hWall, const WorldPt & inCenterPt, bool includeBottomFrame, WorldPt & outCenterPt, WorldCoord & outWidth, WorldCoord & outHeight, 
										WorldCoord& panelThickness, WorldCoord& panelOffset,  WorldCoord& frameInsetTop,  WorldCoord& frameInsetBottom,  WorldCoord& frameInsetRight, WorldCoord& frameInsetLeft)
		{
			return false;
		}
		virtual MCObjectHandle GetOtherObjectFromBinaryConstraint(CBSignedShort type, MCObjectHandle obj, CBSignedShort objVertexA, CBSignedShort objVertexB, InternalIndex containedObj, MCObjectHandle& outContraint)
		{
			return NULL;
		}

		virtual MCObjectHandle FindBinbaryConstraintToObject(CBSignedShort type, MCObjectHandle obj, MCObjectHandle toObject, CBSignedShort& outToObjectVertexA, CBSignedShort& outToObjectVertexB, InternalIndex& outToObjectContainedObj)
		{
			return NULL;
		}

		virtual void Trim2DObjectWithLine(MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, bool insert, TVWArray_MCObjectHandle & hResultArray)
		{
			return;
		}

		virtual void ForEach3DPointInObjectN(MCObjectHandle h, std::function<bool(const WorldPt3& point3D)> callbackLambda)
		{
		}

		virtual void ForEachPolyEdgeN( MCObjectHandle inPolyH, std::function<void(const SPolyEdge& edge)> callbackLambda)
		{
		}

		virtual void ForEachLayerN( std::function<void(MCObjectHandle h)> callbackLambda)
		{
		}

		virtual void ForEachObjectN( short traverseWhat, std::function<void(MCObjectHandle h)> callbackLambda)
		{
		}

		virtual void ForEachBreakN( MCObjectHandle theWall, std::function<bool(MCObjectHandle h, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData)> callbackLambda)
		{
		}

		virtual EForEachFileResult ForEachFileInStandardFolderN(EFolderSpecifier folderSpec, std::function<bool(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda)
		{
			return kStopForEachFile_NoError;
		}

		virtual EForEachFileResult ForEachFilePathInStandardFolderN(FolderSpecifier folderSpec, std::function<bool(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda)
		{
			return kStopForEachFile_NoError;
		}

		virtual EForEachFileResult ForEachFilePathInFolderN(IFolderIdentifier* pStartFolderID, bool doRecursive, std::function<EForEachFileResult(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda)
		{
			return kStopForEachFile_NoError;
		}

		virtual EForEachFileResult ForEachFilePathInPluginFolderN(std::function<EForEachFileResult(const char* fullPath, const char* fileName, const char* fileExtension)> callbackLambda)
		{
			return kStopForEachFile_NoError;
		}

		virtual void ForEachObjectInListN(MCObjectHandle hFirst, std::function<void(MCObjectHandle h)> callbackLambda)
		{
		}

		virtual Sint32 SendActiveToolMessage(ToolMessage& message)
		{
			return 0;
		}

		virtual void AddPullDownResourceMethod(const TXString& label, const TXString& value)
		{
		}

		virtual void SetPullDownResourceValue(short group, const TXString& value)
		{
		}

		virtual Sint32 ShowPullDownResourcePopup(short group, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize)
		{
			return 0;
		}

		virtual void SetImagePopupResourceAdvanced(Sint32 dialogID, Sint32 componentID)
		{
		}

		virtual void SetImagePopupResourceCategories(Sint32 dialogID, Sint32 componentID, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex)
		{
		}

		virtual bool GetClassSharedAndUpdateReference (MCObjectHandle hDLVPort, InternalIndex classIndex, bool& outSharedRef, bool& outUpdateRef)
		{
			return false;
		}
		virtual bool SetObjectAsSpanWallBreak(MCObjectHandle objectHandle, MCObjectHandle wallHandle, bool spanWallBreak)
		{
			return false;
		}

		virtual bool GetTreeControlItemCheckBoxState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, Sint32& outState)
		{
			return false;
		}

		virtual bool SetTreeControlItemCheckBoxState(Sint32 nDialogID, Sint32 nComponentID, int nItemID, Sint32 state)
		{
			return false;
		}
		virtual OSType VCOM_CALLTYPE GetDataMapDataClientID(MCObjectHandle h)
		{
			return 0;
		}

		virtual MCObjectHandle CreateShellSolid(MCObjectHandle surface, double thickness)
		{
			return 0;
		}

		virtual bool CreateSlabModifier(MCObjectHandle slab, MCObjectHandle profile, bool isSubtract, Sint16 componentID, bool clipToBoundary)
		{
			return false;
		}

		virtual bool ExportImage(IFileIdentifier* fileID, const SExportImageOptions& options)
		{
			return false;
		}

		virtual bool ExportSTL(IFileIdentifier* fileID, bool exportBinary, double percentTess, Sint16 exportObjectsOptions)
		{
			return false;
		}

		virtual bool ExportSTEP(IFileIdentifier* fileID, bool exportSolidAsSurface)
		{
			return false;
		}

		virtual void ForEachClass( Boolean doGuestClasses, std::function<void(MCObjectHandle h)> callbackLambda)
		{
		}

		virtual void GetParentFolderNameFromResourceList(Sint32 listID, Sint32 index, TXString& name)
		{
		}

		virtual bool ExportSymbolResource(MCObjectHandle symbolresource, const TXString& symbolFolderDestName, IFileIdentifier* pFileID, bool suppressDialogs, TImportResourceConflictCallbackProcPtr conflictCallback)
		{
			return false;
		}

		virtual InternalIndex GetRoofStyle(MCObjectHandle roof)
		{
			return -1;
		}

		virtual void SetRoofStyle(MCObjectHandle roof, InternalIndex roofStyle)
		{
    
		}

		virtual void ConvertToUnstyledRoof(MCObjectHandle roof)
		{
    
		}

		virtual InternalIndex GetRoofPreferencesStyle()
		{
			return -1;
		}

		virtual void SetRoofPreferencesStyle(InternalIndex roofStyle)
		{
    
		}

		virtual MCObjectHandle CreateRoofStyle(const TXString &roofStyleName)
		{
			return NULL;
		}

		virtual MCObjectHandle GetRoofPreferences()
		{
			return NULL;
		}

		virtual short GetDatumRoofComponent(MCObjectHandle object)
		{
			return 0;
		}

		virtual void SetDatumRoofComponent(MCObjectHandle object, short componentIndex)
		{
    
		}

		virtual bool ExportDocument(IFileIdentifier* fileID, short version)
		{
			return false;
		}

		virtual Sint32	BuildResourceListFromOpenFile(const short objectType, const size_t fileRef, Sint32& numItems)
		{
			return 0;
		}

		virtual void   GetOpenFilesList (TVWArray_OpenFileInformation& outInformation)
		{
		}

		virtual void   GetFavoritesList (TVWArray_IFileIdentifierPtr& outFavorites)
		{
		}

		virtual bool   SwitchToOpenFile (Sint32 fileRef)
		{
			return true;
		}

		virtual bool   TranslateToCurrentVersion (IFileIdentifier* pSrcFileID, IFileIdentifier* pDstFileID)
		{
			return true;
		}

		virtual void VCOM_CALLTYPE CalcRoofTopArea(MCObjectHandle object, double& outArea)
		{
		}

		virtual void SwitchFromPlanTo3DView()
		{
		}

		virtual void UngroupObject(MCObjectHandle object)
		{
		}

		virtual MCObjectHandle ConvertToGroup(MCObjectHandle object, short convertAction)
		{
			return 0;
		}

		virtual void ConvertObjectToLines(MCObjectHandle objectH, bool suspendDialog, ConvertModeEnum convertMode)
		{
		}

		virtual void ConvertObjectToPolygons(MCObjectHandle objectH, bool suspendDialog, ConvertModeEnum convertMode)
		{
		}

		virtual void SymbolToGroup(MCObjectHandle &theSymbol)
		{
		}

		virtual void SymbolsInGroupToGroups(MCObjectHandle inObject)
		{
		}

		virtual GSHandle ViewCreateCurrent()
		{
			return NULL;
		}

		virtual void ViewDelete(GSHandle hView)
		{
		}

		virtual GSHandle ViewDuplicate(GSHandle hView)
		{
			return NULL;
		}

		virtual size_t ViewGetNumLayers(GSHandle hView)
		{
			return 0;
		}

		virtual void ViewGetLayerVisibility(GSHandle hView, size_t index, InternalIndex& outName, short& outVisibility)
		{
		}

		virtual size_t ViewGetNumClasses(GSHandle hView)
		{
			return 0;
		}

		virtual void ViewGetClassVisibility(GSHandle hView, size_t index, InternalIndex& outClassID, short& outVisibility)
		{
		}

		virtual void ViewStore(GSHandle hView)
		{
		}

		virtual void ViewRestore(GSHandle hView)
		{
		}

		virtual bool GetCheckoutsComment(TXString& comment)
		{
			return false;
		}

		virtual bool SetCheckoutsComment(const TXString& comment)
		{
			return false;
		}

		virtual bool GetCurrentUserId(TXString& userid)
		{
			return false;
		}

		virtual bool GetProjectFullPath(TXString& outFilePath)
		{
			return false;
		}

		virtual bool GetProjectName(TXString& outName){
			return false;
		}

		virtual bool GetWorkingFileId(TXString& uuid)
		{
			return false;
		}

		virtual bool IsAWorkingFile()
		{
			return false;
		}

		virtual bool IsProjectOffline()
		{
			return false;
		}

		virtual bool GetProjectUserNames(TXStringArray& users)
		{
			return false;
		}

		virtual bool GetProjectUser(const TXString & userId, TXStringMock fullName, EUserProjectPermission& permission)
		{
			return false;
		}

		virtual bool GetLayerProjectInfo(MCObjectHandle layer, LayerProjectInfo& layerInfo)
		{
			return false;
		}

		virtual MCObjectHandle GetCustomScreenFeedbackGroup(MCObjectHandle hObject)
		{
			return NULL;
		}

		virtual bool SetCustomScreenFeedbackGroup(MCObjectHandle hObject, MCObjectHandle hFeedbackGroup)
		{
			return false;
		}

		virtual bool GetViewFromAndToPoints(WorldPt3& fromPt, WorldPt3& toPt)
		{
			return false;
		}
		virtual void UpdateBreak(MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData)
		{
		}

		virtual Boolean GetComponentDatumIsTopOfComponent(MCObjectHandle object, short componentIndex, Boolean &datumIsTopOfComponent)
		{
			return false;
		}

		virtual Boolean SetComponentDatumIsTopOfComponent(MCObjectHandle object, short componentIndex, Boolean datumIsTopOfComponent)
		{
			return false;
		}

		virtual Boolean GetComponentWallAssociatedBound(MCObjectHandle object, short componentIndex, ERoofWallAssociatedBound &wallAssociatedBound)
		{
			return false;
		}

		virtual Boolean SetComponentWallAssociatedBound(MCObjectHandle object, short componentIndex, ERoofWallAssociatedBound wallAssociatedBound)
		{
			return false;
		}

		virtual Boolean GetComponentWallAssociatedSectionFillChangePoint(MCObjectHandle object, short componentIndex, ERoofChangePoint &wallAssociatedSectionFillChangePoint)
		{
			return false;
		}

		virtual Boolean SetComponentWallAssociatedSectionFillChangePoint(MCObjectHandle object, short componentIndex, ERoofChangePoint wallAssociatedSectionFillChangePoint)
		{
			return false;
		}

		virtual Boolean GetComponentWallAssociatedModification(MCObjectHandle object, short componentIndex, ERoofModification &wallAssociatedModification)
		{
			return false;
		}

		virtual Boolean SetComponentWallAssociatedModification(MCObjectHandle object, short componentIndex, ERoofModification wallAssociatedModification)
		{
			return false;
		}

		virtual Boolean GetComponentManualBound(MCObjectHandle object, short componentIndex, ERoofManualBound &manualBound)
		{
			return false;
		}

		virtual Boolean SetComponentManualBound(MCObjectHandle object, short componentIndex, ERoofManualBound manualBound)
		{
			return false;
		}

		virtual Boolean GetComponentBoundOffset(MCObjectHandle object, short componentIndex, WorldCoord &boundOffset)
		{
			return false;
		}

		virtual Boolean SetComponentBoundOffset(MCObjectHandle object, short componentIndex, WorldCoord boundOffset)
		{
			return false;
		}

		virtual Boolean GetComponentAlwaysAutoJoinInCappedJoinMode(MCObjectHandle object, short componentIndex, Boolean &alwaysAutoJoinInCappedJoinMode)
		{
			return false;
		}

		virtual Boolean SetComponentAlwaysAutoJoinInCappedJoinMode(MCObjectHandle object, short componentIndex, Boolean alwaysAutoJoinInCappedJoinMode)
		{
			return false;
		}

		virtual Boolean GetComponentAlternateSectionFill(MCObjectHandle object, short componentIndex, Sint32 &alternateSectionFill)
		{
			return false;
		}

		virtual Boolean SetComponentAlternateSectionFill(MCObjectHandle object, short componentIndex, Sint32 alternateSectionFill)
		{
			return false;
		}

		virtual Boolean GetComponentPenStylesN(MCObjectHandle object, short componentIndex, InternalIndex &leftPenStyle, InternalIndex &rightPenStyle)
		{
			return false;
		}

		virtual Boolean SetComponentPenStylesN(MCObjectHandle object, short componentIndex, InternalIndex leftPenStyle, InternalIndex rightPenStyle)
		{
			return false;
		}

		virtual Boolean GetComponentAlternateSectionFillColors(MCObjectHandle object, short componentIndex, ColorRef &alternateSectionFillForeColor, ColorRef &alternateSectionFillBackColor)
		{
			return false;
		}

		virtual Boolean SetComponentAlternateSectionFillColors(MCObjectHandle object, short componentIndex, ColorRef alternateSectionFillForeColor, ColorRef alternateSectionFillBackColor)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassFillStyleForFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillStyleForFill)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassFillStyleForFill(MCObjectHandle object, short componentIndex, Boolean useClassFillStyleForFill)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassFillColorsForFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillColorsForFill)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassFillColorsForFill(MCObjectHandle object, short componentIndex, Boolean useClassFillColorsForFill)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassFillStyleForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillStyleForAlternateSectionFill)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassFillStyleForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean useClassFillStyleForAlternateSectionFill)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassFillColorsForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean &useClassFillColorsForAlternateSectionFill)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassFillColorsForAlternateSectionFill(MCObjectHandle object, short componentIndex, Boolean useClassFillColorsForAlternateSectionFill)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenStyleForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenStyleForLeftPen)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenStyleForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenStyleForLeftPen)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenWeightForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenWeightForLeftPen)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenWeightForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenWeightForLeftPen)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenColorsForLeftPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenColorsForLeftPen)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenColorsForLeftPen(MCObjectHandle object, short componentIndex, Boolean useClassPenColorsForLeftPen)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenStyleForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenStyleForRightPen)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenStyleForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenStyleForRightPen)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenWeightForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenWeightForRightPen)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenWeightForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenWeightForRightPen)
		{
			return false;
		}

		virtual Boolean GetComponentUseClassPenColorsForRightPen(MCObjectHandle object, short componentIndex, Boolean &useClassPenColorsForRightPen)
		{
			return false;
		}

		virtual Boolean SetComponentUseClassPenColorsForRightPen(MCObjectHandle object, short componentIndex, Boolean useClassPenColorsForRightPen)
		{
			return false;
		}

		virtual void SetIsCurtainWall(MCObjectHandle wall, bool isCurtainWall)
		{
			return;
		}

		virtual WorldCoord GetCurtainWallCutPlane(MCObjectHandle wall)
		{
			return 0.0;
		}

		virtual void SetCurtainWallCutPlane(MCObjectHandle wall, WorldCoord curtainWallCutPlane)
		{
			return;
		}

		virtual MCObjectHandle MirrorObject(MCObjectHandle h, bool dup, const WorldPt& p1, const WorldPt& p2)
		{
			return 0;
		}

	// VW 2017
	public:
		virtual Sint32 ShowPullDownResourcePopupN(const ViewPt& pt, const SShowPullDownResourcePopup& data, const TXString& selectedName, const TXString& categoryTitle, const TXStringArray& categoryArray, size_t categorySelIndex, ThumbnailSizeType thumbSize)
		{
			return 0;
		}


		virtual Boolean ResetNurbsCurve(MCObjectHandle curveHandle, const WorldPt3& firstPt, bool byCtrlPts, short degree) 
		{
			return false;
		}

		virtual Boolean SetArc(MCObjectHandle hArc, const WorldPt& center, double radius, double startAngle, double sweepAngle)
		{
			return false;
		}

		virtual void GetDefaultOpacityN( OpacityRef& outPenOpacity, OpacityRef& outFillOpacity)
		{
	
		}


		virtual void GetDefaultOpacityByClassN(Boolean& outPenOpacityByClass, Boolean& outFillOpacityByClass)
		{
	
		}


		virtual void SetDefaultOpacityN( OpacityRef inPenOpacity, OpacityRef inFillOpacity )
		{
	
		}

		virtual void SetDefaultOpacityByClassN( Boolean inPenOpacityByClass, Boolean inFillOpacityByClass )
		{
	
		}


		virtual void GetOpacityN( MCObjectHandle h, OpacityRef& outPenOpacity, OpacityRef& outFillOpacity)
		{
	
		}


		virtual void GetOpacityByClassN( MCObjectHandle h, Boolean& outPenOpacityByClass, Boolean& outFillOpacityByClass)
		{

		}


		virtual void SetOpacityN( MCObjectHandle h, OpacityRef inNewPenOpacity, OpacityRef inNewFillOpacity)
		{
	
		}


		virtual void SetOpacityByClassN( MCObjectHandle h, Boolean inPenOpacityByClass, Boolean inFillOpacityByClass)
		{
	
		}

		virtual void GetClOpacityN( InternalIndex classIndex, OpacityRef& penOpacity, OpacityRef& fillOpacity )
		{

		}

		virtual void SetCLOpacityN( InternalIndex classIndex, OpacityRef penOpacity, OpacityRef fillOpacity )
		{

		}

		virtual Boolean MarqueeEmptyList()
		{
			return false;
		}

		virtual Boolean MarqueeAddObject(MCObjectHandle hInObject)
		{
			return false;
		}

		virtual MCObjectHandle GetFreehandInteractivePoly()
		{
			return 0;
		}

		virtual void BeginFreehandInteractive()
		{
    
		}

		virtual void UpdateFreehandInteractive()
		{
    
		}

		virtual MCObjectHandle EndFreehandInteractive()
		{
			return 0;
		}

		virtual Boolean IsPlanRotationView()
		{
			return false;
		}

		virtual MCObjectHandle CreateHelicalAlongCurve(MCObjectHandle curveHandle, double radius1, double radius2, double startAngle, double& pitch, double& numTurns, bool bPitch, bool bReverseTwist, bool bFlat)
		{
			return NULL;
		}

		virtual void ViewRestoreN(MCObjectHandle hView, Boolean bDontRegen3DBounds)
		{
		}

		virtual void RestoreSavedViewN(const TXString& savedView, Boolean bDontRegen3DBounds)
		{
		}

		virtual void PerformMultipleUnion_2(TVWArray_MCObjectHandle  hArray, TVWArray_MCObjectHandle & hArrayResult, bool insert)
		{
		}

		virtual Boolean	CreateDuplicateAlongPath(TVWArray_MCObjectHandle hProfileArray, MCObjectHandle inPathH, Boolean bUseNumber, Sint32 inNumber, double inDistance, double inStartOffset, Boolean bCenterObject, Boolean bTangent, Boolean bKeepOrienation, TVWArray_MCObjectHandle &outDuplicateArray)
		{
			return false;
		}
 
		virtual void PullDownResourceSetToolBarPopup(short group, VectorWorks::Extension::IResourceManagerContent* content)
		{
		}

		virtual TXString PullDownResourceGetSelectedResourceName(short group)
		{
			return "";
		}

		virtual void PullDownResourceSetSelectedResourceName(short group, const TXString& name)
		{
		}

		virtual void PullDownResourceLayoutInit(Sint32 dialogID, Sint32 itemID, VectorWorks::Extension::IResourceManagerContent* content)
		{
		}

		virtual TXString PullDownResourceLayoutGetSelectedResourceName(Sint32 dialogID, Sint32 itemID)
		{
			return "";
		}

		virtual void PullDownResourceLayoutSetSelectedResourceName(Sint32 dialogID, Sint32 itemID, const TXString& name)
		{
		}

		virtual bool RebuildFileInResourceManager(IFileIdentifier*   pFileID)
		{
			return false;
		}

		virtual bool RefreshLibrariesInResourceManager(SRefreshLibrariesOptions& options)
		{
			return false;
		}


		virtual EDownloadErrors DownloadLibraryFile(ELibrariesID libraryID, const TXString& folderPath, const TXString& fileName, IFileIdentifier** ppOutFileID, SDownloadParams& params)
		{
			return EDownloadErrors::errUnknownError;
		}

		virtual EDownloadErrors DownloadLibraryFile(ELibrariesID libraryID, EFolderSpecifier folderID, const TXString& fileName, IFileIdentifier** ppOutFileID, SDownloadParams& params)
		{
			return EDownloadErrors::errUnknownError;
		}

		virtual void RemoveCustomTextureParts(MCObjectHandle /*h*/)
		{

		}
 
		// For Slab drainage (Flat Roofs)
		virtual short AddDrain(MCObjectHandle slab, WorldPt location, WorldCoord height, double angle)
		{

			// Unimplemented!!!!
			return -1;
		}
		virtual void AddCustomTexturePart(MCObjectHandle /*h*/, Sint32 /*partID*/, const TXString& /*partName*/)
		{

		}

		virtual Boolean	CustomTexturePartExists(MCObjectHandle h, Sint32 partID)
		{
			return false;
		}


		virtual void ApplyCustomTexturePart(MCObjectHandle srcObj, MCObjectHandle destObj, Sint32 partID)
		{
		}


		virtual Boolean GetPluginObjectStyle( MCObjectHandle h, RefNumber& styleRefNumber )
		{
			return false;
		}

		virtual Boolean SetPluginObjectStyle( MCObjectHandle h, RefNumber styleRefNumber )
		{
			return false;
		}

		virtual void UpdatePIOFromStyle( MCObjectHandle h )
		{
		}

		virtual bool GetPluginStyleForTool( const TXString & toolUnivName, RefNumber& styleRefNumber )
		{
			return false;
		}

		virtual bool SetPluginStyleForTool( const TXString & toolUnivName, const RefNumber styleRefNumber )
		{
			return false;
		}

		virtual bool IsPluginStyle( MCObjectHandle h )
		{
			return false;
		}

		virtual RefNumber ChoosePluginStyleForTool( TInternalID internalToolID, RefNumber excludeRefNumber, const TXString & title,  const TXString & message  )
		{
			return 0;
		}

		virtual void ChoosePluginStyleForReplace( MCObjectHandle hObj )
		{
		}

		virtual Sint32 GetSymbolDefSubType( MCObjectHandle hObj )
		{
			return 0;
		}

		virtual void SetSymbolDefSubType( MCObjectHandle hObj, Sint32 subType )
		{
		}

		virtual bool GetPluginStyleSymbol( MCObjectHandle hObj, MCObjectHandle & hSymbolDefinition )
		{
			return false;
		}

		virtual EPluginStyleParameter GetPluginStyleParameterType( MCObjectHandle object, const TXString& paramName )
		{
			return 0;
		}

		virtual void SetPluginStyleParameterType( MCObjectHandle hSymbol, const TXString& paramName, EPluginStyleParameter styleType )
		{
		}

		virtual void SetAllPluginStyleParameters( MCObjectHandle hSymbol, EPluginStyleParameter styleType )
		{
		}

		virtual bool GetObjectWallInsertMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, InsertModeType& insertMode )
		{
			return false;
		}

		virtual bool SetObjectWallInsertMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, InsertModeType insertMode )
		{
			return false;
		}

		virtual bool GetObjectWallBreakMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, BreakModeType& breakMode ) 
		{
			return false;
		}

		virtual bool SetObjectWallBreakMode(MCObjectHandle objectHandle, MCObjectHandle wallHandle, BreakModeType breakMode ) 
		{
			return false;
		}

		virtual void ViewRect2WorldRect(const ViewRect& vRect, WorldRect& wRect)
		{

		}

		virtual MCObjectHandle GetObjectByUuid(const TXString& uuid) { return NULL; }
		virtual bool GetObjectUuid(MCObjectHandle h, TXString& uuid) { return false; }
		virtual MCObjectHandle GetObjectByUuidN(const UuidStorage& uuid) { return NULL; }
		virtual bool GetObjectUuidN(MCObjectHandle h, UuidStorage& uuid) { return false; }

		//////////////////////////////////////////////////////////////////
		//  Drop Shadow related
		//////////////////////////////////////////////////////////////////
		virtual bool IsDropShadowEnabled(MCObjectHandle h)
		{
			return false;	
		}

		virtual void EnableDropShadow (MCObjectHandle h, bool enable)
		{
		
		}
 
		virtual bool GetDropShadowData(MCObjectHandle h, SDropShadowData & outDropShadowData)
		{
			return false;	
		}

		virtual void SetDropShadowData(MCObjectHandle h, const SDropShadowData& inDropShadowData)
		{
		
		}

		virtual void DeleteDropShadowData(MCObjectHandle h)
		{
		
		}
 
		virtual void ShowDropShadowDialog(SDropShadowData& ioSDropShadowData, bool& ioByClass)
		{
		
		}
 
		virtual bool IsDropShadowByClass(MCObjectHandle h)
		{
			return false;	
		}

		virtual void SetDropShadowByClass(MCObjectHandle h, bool inSetByClass)
		{
		
		
		} 
 
		virtual void GetClDropShadowData(InternalIndex classIndex, SDropShadowData& outDropShadowData)
		{
		
		}
		virtual void SetClDropShadowData(InternalIndex classIndex, SDropShadowData& inDropShadowData)
		{
		
		}
 
		virtual bool IsDropShadowEnabledInDocument()
		{
			return false;
		}
		virtual void SetDropShadowByClassInDocument(bool inSetByClass)
		{
	
		} 
 
		virtual void GetDocumentDropShadowData( SDropShadowData& outDropShadowData)
		{
		
		}
		virtual void SetDocumentDropShadowData( const SDropShadowData& inDropShadowData)
		{
		
		}

		virtual bool DropShadowDataAreEqual(const SDropShadowData& inDropShadowData1, const SDropShadowData& inDropShadowData2)
		{
			return false;	
		}


		virtual bool GetAllCombinedsurfaces(MCObjectHandle baseObject, const TVWArray_MCObjectHandle& arrClipObjects, TXGenericArray< std::pair<MCObjectHandle, TVWArray_SizeT> >& arrResult, std::function<bool(size_t,size_t)> progressCallback)
		{
			return false;
		}



		virtual short ConnectDrains(MCObjectHandle slab, short index1, short index2, short connectionType, double slopeAngle, double splitSlopeAngle)
		{
			// Unimplemented!!!!
			return -1;
		}

		virtual short AddSlopeValley(MCObjectHandle slab, short index, WorldPt controlPt, double slope, double edgeHeight)
		{
			// Unimplemented!!!!
			return -1;
		}

		virtual short GetNumDrains(MCObjectHandle slab)
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual short GetNumDrainConnections(MCObjectHandle slab)
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual bool SetDrainHeight(MCObjectHandle slab, short index, double height)
		{
			// Unimplemented!!!!
			return false;
		}

		virtual double GetDrainHeight(MCObjectHandle slab, short index)
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual WorldPt GetDrainLocation(MCObjectHandle slab, short index)
		{
			// Unimplemented!!!!
			return WorldPt(0, 0);
		}

		virtual bool SetDrainLocation(MCObjectHandle slab, short index, const WorldPt& location)
		{
			return false;
		}

		virtual void RotateDrain(MCObjectHandle slab, short index, double angle)
		{
			// Unimplemented!!!!
		}

		virtual double GetDrainDrainageArea(MCObjectHandle slab, short index)
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual MCObjectHandle GetDrainSymbol(MCObjectHandle slab, short index)
		{
			// Unimplemented!!!!
			return nullptr;
		}

		virtual bool SetDrainSymbol(MCObjectHandle slab, short index, MCObjectHandle symbol)
		{
			// Unimplemented!!!!
			return false;
		}

		virtual short GetNumDrainSlopeValleys(MCObjectHandle slab, short index)
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual bool GetDrainSlopeValley(MCObjectHandle slab, short drain, short valley, WorldPt& controlPt, double& slope, double& edgeHeight, bool& heightLocked)
		{
			// Unimplemented!!!!
			return false;
		}

		virtual void SetDrainSlopeValley (MCObjectHandle slab, short drain, short valley, WorldPt controlPt, double slope, double edgeHeight, bool lockHeight)
		{
			// Unimplemented!!!!
		}

		virtual short GetNumDrainConnections(MCObjectHandle slab, short drain)
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual short GetDrainConnectionIndex(MCObjectHandle slab, short drain, short index)
		{
			// Unimplemented!!!!
			return 0;
		}

		virtual bool GetDrainConnection(MCObjectHandle slab, short index, short& drain1, short& drain2, short& style, double& angle1, double& angle2)
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool SetDrainConnection(MCObjectHandle slab, short index, short style, double angle1, double angle2)
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool DeleteDrainConnection(MCObjectHandle slab, short index)
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool DeleteSlopeValley(MCObjectHandle, short drain, short index, bool forceDelete)
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool DeleteDrain(MCObjectHandle slab, short index)
		{
			// Unimplemented!!!!
			return false;
		}

		virtual bool GetLayerEnableCutPlane(MCObjectHandle layer)
		{
			return false;
		}

		virtual void SetLayerEnableCutPlane(MCObjectHandle layer, bool enableCutPlane)
		{
			return;
		}

		virtual WorldCoord GetLayerCutPlane(MCObjectHandle layer)
		{
			return 0.0;
		}

		virtual void SetLayerCutPlane(MCObjectHandle layer, WorldCoord cutPlane)
		{
			return;
		}

		virtual InternalIndex GetWallBelowCutPlaneClass(MCObjectHandle wall)
		{
			return 0;
		}

		virtual void SetWallBelowCutPlaneClass(MCObjectHandle wall, InternalIndex belowCutPlaneClass)
		{
			return;
		}

		virtual short GetTaperedComponent(MCObjectHandle object)
		{
			return 0;
		}

		virtual void SetTaperedComponent(MCObjectHandle object, short componentIndex)
		{
			return;
		}

		virtual Boolean GetComponentAutoBoundEdgeOffsetOffset(MCObjectHandle object, short componentIndex, WorldCoord &autoBoundEdgeOffsetOffset)
		{
			return false;
		}

		virtual Boolean SetComponentAutoBoundEdgeOffsetOffset(MCObjectHandle object, short componentIndex, WorldCoord autoBoundEdgeOffsetOffset)
		{
			return false;
		}

		virtual Boolean GetComponentMasterSnaps(MCObjectHandle object, short componentIndex, Boolean &masterSnapOnLeft, Boolean &masterSnapOnRight)
		{
			return false;
		}

		virtual Boolean SetComponentMasterSnaps(MCObjectHandle object, short componentIndex, Boolean masterSnapOnLeft, Boolean masterSnapOnRight)
		{
			return false;
		}

		virtual void InteractiveViewOperation_GetFlyOverOrigin( ViewPt& curFlyOverOrigin )
		{

		}


		virtual double GetWorksheetImageScaleFactor(MCObjectHandle hWorksheetImage)
		{
			return 1.0;
		}

		virtual bool SetWorksheetImageScaleFactor(MCObjectHandle hWorksheetImage, double scale, bool redrawImage)
		{
			return false;
		}

		virtual void SetWorksheetCellsImageResolution(MCObjectHandle hWorksheet, Sint16 dpiResolution)
		{
			return;
		}

		virtual Sint16 GetWorksheetCellsImageResolution(MCObjectHandle hWorksheet)
		{
			return 150;
		}

		virtual MCObjectHandle CreateResourceFolder(const TXString& name, Sint16 resourceType)
		{
			return nil;
		}

		virtual void CreateResourceFolderN(const TXString& folderPath, Sint16 resourceType, TVWArray_MCObjectHandle & outFolderPath)
		{
			return;
		}

		virtual bool AddResourceTags(MCObjectHandle h, const TXStringArray& arrTags)
		{
			return false;
		}

		virtual bool GetResourceTags(MCObjectHandle h, TXStringArray& arrTags)
		{
			return false;
		}

		virtual bool  IsActiveSymbolInCurrentDocument()
		{
			return 0;
		}

		virtual bool AddItemToPluginStyle( MCObjectHandle hSymDef, const TXString & itemName, EPluginStyleParameter styleType )
		{
			return false;
		}

		virtual bool RemoveItemFromPluginStyle( MCObjectHandle hSymDef, const TXString & itemName )
		{
			return false;
		}

		virtual bool GetDimensionsAssociatedToPlugin( MCObjectHandle hPlugin, TVWArray_MCObjectHandle &dimHandles )
		{
			return false;
		}

		virtual bool GetChainThatContainsDimension( MCObjectHandle hDim, MCObjectHandle &hChain )
		{
			return false;
		}

		virtual MCObjectHandle CreateVWObjectFromSplineData(const TVWArray_WorldPt3& controlPoints, const TVWArray_Double& weights, const TVWArray_Double& knots, Sint32 degree, bool isRational, bool isClosed, bool create2D)
		{
			return NULL;
		}

		virtual bool SetDefaultGenericStoryLevelBound( MCObjectHandle hFormat, const SStoryObjectData& data )
		{
			return false;
		}

		virtual bool GetDefaultGenericStoryLevelBound( MCObjectHandle hFormat,  SStoryObjectData& data )
		{
			return false;
		}

		virtual void GetStoryBoundChoiceStringsN( MCObjectHandle story, TXStringArray& outStrings, EStoryLevelPopupBoundType boundType)
		{
			return;
		}

		virtual Sint32 AddResourceToListUnsorted(Sint32 listID, MCObjectHandle obj)
		{
			return -1;
		}

		virtual Sint32 VCOM_CALLTYPE BuildResourceListUnsorted(short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems)
		{
			return 0;
		}

		virtual bool CreateReference( IFileIdentifier* pFileID )
		{
			return false;
		}

		virtual void UpdateStyledObjects( RefNumber styleRefNumber )
		{
			return;
		}
		virtual void GetStoryLevels( MCObjectHandle story, TXStringArray& outStrings)
		{
			return;
		}

		virtual void InitClassOverrideData(InternalIndex classIndex, SViewportClassOverride& outData)
		{
			return;
		}

		virtual void InitLayerOverrideData(InternalIndex layerIndex, SViewportLayerOverride& outData)
		{
			return;
		}
		
		virtual void InitLightOverrideData(InternalIndex lightIndex, SViewportLightOverride& outData)
		{
			return;
		}

		virtual void GetCurrentWorkspace(VectorWorks::Workspaces::IWorkspaceFile** outWorkspace)
		{
		}

		virtual bool InstallConstraintPlane(TPlanarRefID inContextPlanarRefID, const WorldPt& inwptStartPt)
		{
			return false;
		}

		virtual bool AddItemToPluginStyleEditList( MCObjectHandle hSymDef, const TXString & itemName, EPluginStyleEditList editListType, const TXString & displayName )
		{
			return false;
		}

		virtual bool RemoveItemFromPluginStyleEditList( MCObjectHandle hObj, const TXString & itemName )
		{
			return false;
		}

		virtual bool GetPluginStyleEditListType( MCObjectHandle hObj, const TXString& paramName, EPluginStyleEditList & editListTyle, TXString & displayName )
		{
			return false;
		}
		virtual MCObjectHandle  VCOM_CALLTYPE OffsetPolyClosed(MCObjectHandle h, double offset, bool smoothConers)
		{
			return NULL;
		}

		virtual MCObjectHandle VCOM_CALLTYPE CreateImgFromSymbol( const TXString & symbolName, SymbolImgInfo& imgInfoInOut)
		{											   
			return NULL;							   
		}											   
											 
		virtual void  VCOM_CALLTYPE GetSelInsertsInWall( MCObjectHandle hObj, TVWArray_MCObjectHandle& selInserts)
		{
		}
											 
		virtual bool VCOM_CALLTYPE GetCurlProxyInfo(TXString& outProxyType, TXString& outAddress, Sint32& outPort, TXString& outUsername, TXString& outPassword)
		{
			return false;
		}
					
		virtual TXString  VCOM_CALLTYPE GetFormattedDateTimeString(EDateTimeFormat dateTimeFormat)
		{
			return ""; 
		}

		virtual TXString VCOM_CALLTYPE GetFormattedDateTimeString(EDateTimeFormat dateTimeFormat, const SDateTimeData& dateTimeData)
		{
			return "";
		}

		virtual TXString  VCOM_CALLTYPE GetLocalSystemDateTimeString(EDateFormat dateFormat, EInfoFormat infoFormat)
		{
			return ""; 
		}

		virtual bool VCOM_CALLTYPE GetDateTimeIntlData(TDateTimeIntlData& outDateTimeIntlData)
		{
			return false;
		}

		virtual void SetHotSpotColor(HotSpotRefID inHotSpotID, GSColor color)
		{
		}

		virtual void DrawHotSpots()
		{
		}

		virtual void EnterObjectGroup(MCObjectHandle hGroup)
		{
		}

		virtual bool IsSymDefUsedInEditContext(MCObjectHandle hSymDef)
		{
			return false;
		}


		virtual bool GetCatalogPath( MCObjectHandle hObj, EFolderSpecifier & folderSpec, TXString & relativePath )
		{
			return false;
		}


		virtual bool SelectPluginCatalog( MCObjectHandle hSymDef )
		{
			return false;
		}
		virtual bool SelectItemFromPluginCatalog( MCObjectHandle hObj, const TXString & catName, 
			std::function<TXString(const TXString & id, EEmptyHandling opt)> columnNamesLocalizer  )
		{
			return false;
		}

		virtual bool AplyFirstCatalogItem( MCObjectHandle hObj, const TXString & catName )
		{
			return false;
		}

		virtual Boolean GetComponentFunction(MCObjectHandle object, short componentIndex, EComponentFunction &function)
		{
			return false;
		}

		virtual Boolean SetComponentFunction(MCObjectHandle object, short componentIndex, EComponentFunction function)
		{
			return false;
		}
		virtual bool IsCatalogParameter( MCObjectHandle hObj, const TXString & paramName )
		{
			return false;
		}

		virtual void SetUseCatalogItem( MCObjectHandle hObj, const bool & useCatItem )
		{
		}

		virtual bool GetUseCatalogItem( MCObjectHandle hObj )
		{
			return false;
		}

		virtual void SetCatalogItemByStyle( MCObjectHandle hObj, const bool & byStyle )
		{
		}

		virtual bool GetCatalogItemByStyle( MCObjectHandle hObj )
		{
			return false;
		}

		virtual MCObjectHandle	FitExtrudeToObjects(MCObjectHandle hExtrude, bool isTopFit, EFitExtrudeToObjectsOption boundOption, double defaultHeight, TVWArray_MCObjectHandle clippingHandleArray, EFitExtrudeToObjectsRoofAndSlabOption roofSlabOption)
		{
			return NULL;
		}

		virtual MCObjectHandle GetWallEndCapFootPrint(MCObjectHandle theWall, bool atStart)
		{
			return NULL;
		}
		virtual bool SimplifyMesh(MCObjectHandle meshHandle, float quality)
		{
			return NULL;
		}


		virtual bool SetToolPt2D(Sint32 inIndex, const WorldPt& inToolPoint)
		{
			return false;
		}

		virtual bool SetToolPt3D(Sint32 inIndex, const WorldPt3& inToolPoint)
		{
			return false;
		}
		virtual short GetObjTypeProperties(short objectType)
		{
			return -1;
		}

		virtual bool GetWorksheetImageShowDBHeaders(MCObjectHandle hWorksheetImage)
		{
			return false;
		}

		virtual void SetWorksheetImageShowDBHeaders(MCObjectHandle hWorksheetImage, bool show, bool redrawImage)
		{
		}

		virtual void DisplayDocumentPreferences(EDocumentPrefsTab tabToSelect)
		{
		}

		virtual size_t GetResourceStringTableSize(const char* resIdentifier)
		{
			return 0;
		}

		virtual void GetReferencedFilesInfo(TVWArray_ReferencedFileInfo& outRefFilesInfo)
		{

		}

		virtual void DeleteReferencedFiles(TVWArray_ReferencedFileInfo& outRefFilesInfo, const SDeleteFileOptions fileOptions) 
		{

		}

		// For Multiview
		virtual void SetFocusOnSelectedViewPane(bool bMakeItActive, bool bUpdateUI)
		{

		}

		virtual void GetPageBoundsN(MCObjectHandle hLayer,WorldRect& bounds)
		{

		}

		virtual void TrackToolN(MCObjectHandle& overObject, MCObjectHandle& overSubObject, short& overPart, SintptrT& code)
		{

		}

		virtual void SetWorksheetCellCOBieValue(MCObjectHandle worksheet, const ViewPt& cell, const TXString& formula)
		{

		}

		virtual void GetSlabHolesAndTheirMiters(MCObjectHandle hSlab, TVWArray_MCObjectHandle& outHolesArray, TVWArray_SizeT& outMitersArray)
		{
    
		}
	// VW 2019
	public:
		virtual short GetDlgCtrlWidthStdChar(const TXString& str)
		{
			return 0;
		}

		virtual bool ExportResourceList(const TVWArray_MCObjectHandle& inResourceList, IFileIdentifier* pFileID, bool suppressDialogs)
		{
			return false;
		}

		virtual bool ExportResourceListN(const TVWArray_MCObjectHandle& inResourceList, IFileIdentifier* pFileID, TImportResourceConflictCallbackProcPtr conflictCallback) 
		{
			return false;
		}

		virtual TXString GetHierarchicalListBrowserRowContainerPath(Sint32 dialogID, Sint32 componentID, Sint32 rowIndex)
		{
			return "";
		}

		virtual void SelectInResourceManager(MCObjectHandle requestedResource) {}

		virtual bool BeginMultipleMove()
		{
			return false;
		}

		virtual bool EndMultipleMove()
		{
			return false;
		}

		virtual bool GetWallAngleVector(const MCObjectHandle& wallHandle, const WorldPt& rotationCenter, WorldPt& wallVector)
		{
			return false;
		}

		virtual void CoordToDimStringInUnits(WorldCoord value, VectorWorks::Units::IVWUnits* dimUnit, TXString& str)
		{

		}

		virtual void DoubleToStringInUnits(TNumStyleClass inNumStyle, Byte inAccuracy, Byte inFormat, double_param inDouble, VectorWorks::Units::IVWUnits* dimUnit, TXString& outString)
		{

		}

		virtual size_t GetPDFAnnotationsCount(MCObjectHandle object)
		{
			return 0;
		}

		// For Line type re-engineering
		virtual Boolean	GetCumulativeDashPat(InternalIndex dashLineType, DashPatType& outDashPat)
		{
			return false;
		}

		virtual Boolean	GetSimpleLineTypeDefinition(const InternalIndex lineTypeRef, DashPatDef& outDashPat)
		{
			return false;
		}

		virtual InternalIndex	CreateOrFindSimpleLineTypeDefinition(const DashPatDef& inDashPat)
		{
			return 0;
		}
		virtual InternalIndex GetDashLineStyle(bool scaleWithThick, const std::vector<double>& theVectors)
		{
			return 0;
		}

		virtual Boolean	SetDashLineTypeName(InternalIndex dashLineType, const TXString& dashStyleName)
		{
			return false;
		}
		virtual TXString GetDashLineTypeName(InternalIndex dashLineType)
		{
			return "";
		}
		virtual Boolean	GetDLComponentPenStylesN(Sint16 index, InternalIndex& outPenStyleLeft, InternalIndex& outPenStyleRight)
		{
			return false;
		}
		virtual Boolean	SetDLComponentPenStylesN(Sint16 index, InternalIndex penStyleLeft, InternalIndex penStyleRight)
		{
			return false;
		}
		virtual Boolean InsertNewDLComponentN(Sint16 beforeIndex, WorldCoord width, Sint32 fill, Uint8 penWeightLeft, Uint8 penWeightRight, InternalIndex penStyleLeft, InternalIndex penStyleRight)
		{
			return false;
		}
		virtual Boolean InsertNewComponentN(MCObjectHandle object, short beforeComponentIndex, WorldCoord width, Sint32 fill, Uint8 leftPenWeight, Uint8 rightPenWeight, InternalIndex leftPenStyle, InternalIndex rightPenStyle)
		{
			return false;
		}

		virtual Boolean IsDashLineStyle(InternalIndex dashLineType)
		{
			return false;
		}
		virtual void GetWSCellAllBordersN(MCObjectHandle worksheet, const ViewPt& cell, TCellBorderRefNum& top, TCellBorderRefNum& left, TCellBorderRefNum& bottom, TCellBorderRefNum& right)
		{
		}
		virtual void SetWSCellAllBordersN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, TCellBorderRefNum top, TCellBorderRefNum left, TCellBorderRefNum bottom, TCellBorderRefNum right, TCellBorderRefNum insideVert, TCellBorderRefNum insideHorz)
		{

		}
		virtual void SetWSCellBottomBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color)
		{

		}
		virtual void SetWSCellInsideHorizBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color)
		{

		}
		virtual void SetWSCellInsideVertBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color)
		{

		}
		virtual void SetWSCellLeftBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color)
		{

		}
		virtual void SetWSCellOutlineBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color)
		{

		}
		virtual void SetWSCellRightBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color)
		{

		}
		virtual void SetWSCellTopBorderN(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, InternalIndex style, Uint8 weight, ColorRef color)
		{

		}
		virtual bool GetPseudoDashIndexFromDashLineType(const InternalIndex dashLineType, Sint16& pseudoIndex)
		{
			return false;
		}
		virtual bool GetDashLineTypeFromPseudoDashIndex(const Sint16 pseudoIndex, InternalIndex& dashLineType)
		{
			return false;
		}
		virtual void BeginMultiplePseudoDashIndexConvert()
		{
		}
		virtual void EndMultiplePseudoDashIndexConvert()
		{
		}

		virtual void CreateSearchEditBox(Sint32 dialogID, Sint32 itemID, const TXString& promptText, short widthInStdChar)
		{
		}

		virtual MCObjectHandle CreateSymbolDefinitionForDisplayControl(TXString& inoutName)
		{
			return NULL;
		}

		virtual TXString	GetActiveSymbolName()
		{
			return "";
		};

		virtual bool	GetFilePathForActiveSymbolInOpenDocument(IFileIdentifier** ppOutFileID, bool& outFolderSet)
		{
			return false;
		};

		virtual bool AssignUuidToHandle(MCObjectHandle h, const UuidStorage& uuid, TDocumentUuidsCheckTable& checkTable)
		{
			return false;
		}

		virtual void CreateEditPassword(Sint32 dialogID, Sint32 itemID, short widthInStdChar)
		{
		}

		//This lets the user assign text tags to an object
		virtual bool AddObjectTags(MCObjectHandle h, const TXStringArray& arrTags)
		{
			return false;
		}

		virtual bool GetObjectTags(MCObjectHandle h, TXStringArray& arrTags)
		{
			return false;
		}

		virtual bool ShowChooseDateFormatDialog(EDateTimeFormat& inOutDateFormat)
		{
			return false;
		}

		virtual ESetSpecialGroupErrors Set2DComponentGroup(MCObjectHandle hObject, MCObjectHandle hGroup, EViewTypes component)
		{
			return ESetSpecialGroupErrors::CannotSet_BadData;
		}

		virtual MCObjectHandle	Get2DComponentGroup(MCObjectHandle hObject, EViewTypes component)
		{
			return nullptr;
		}

		virtual ESetSpecialGroupErrors AddObjectTo2DComponentGroup(MCObjectHandle hObject, MCObjectHandle hObjectToAdd, EViewTypes component)
		{
			return ESetSpecialGroupErrors::CannotSet_BadData;
		}

		virtual bool SetTopPlan2DComponent(MCObjectHandle hObject, ETopPlanViewComponent component)
		{
			return false;
		}

		virtual ETopPlanViewComponent GetTopPlan2DComponent(MCObjectHandle hObject)
		{
			return ETopPlanViewComponent::Top;
		}

		virtual bool SetDisplayWith2DComponent(MCObjectHandle hObject, EViewTypes component, bool isVisible)
		{
			return false;
		}

		virtual bool GetDisplayWith2DComponent(MCObjectHandle hObject, EViewTypes component)
		{
			return false;
		}

		virtual bool SetMirrorEmpty2DComponents(MCObjectHandle hObject, bool doMirror)
		{
			return false;
		}

		virtual bool GetMirrorEmpty2DComponents(MCObjectHandle hObject)
		{
			return false;
		}

		virtual bool Generate2DFrom3DComponent(MCObjectHandle hObject, EViewTypes component, TRenderMode renderMode, ELevelsOfDetail levelOfDetails)
		{
			return false;
		}

		virtual MCObjectHandle CreateTemporaryCustomObject(const TXString& name, const WorldPt& location, double_param angle)
		{
			return NULL;
		}

		virtual MCObjectHandle CreateTemporaryCustomObjectByMatrix(const TXString& name, const TransformMatrix& matrix)
		{
			return NULL;
		}

		virtual MCObjectHandle CreateTemporaryCustomObjectByMatrixEx(const TXString& name, const TransformMatrix& matrix)
		{
			return NULL;
		}

		virtual void GetPageMargins(MCObjectHandle hLayer, double& left, double& right, double& bottom, double& top)
		{
		}

		virtual Boolean CreateLayerPullDownMenu(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar)
		{
			return false;
		}

		virtual WorldPt3 Project3DPointOnPlane(const WorldPt3& given3DPoint, const WorldPt3& pointOnPlane, const WorldPt3& planeNormal, const WorldPt3& projectionDir)
		{
			return WorldPt3(0.0, 0.0, 0.0);
		}
	
	// VW 2020
	public:

		virtual void ShowDetailedMemoryInfoDlg()
		{

		}

		virtual MCObjectHandle GetCustomObjectProfileGroupInAux(MCObjectHandle objectHand)
		{
			return nullptr;
		}

		virtual bool EditSymbolMarkersDialog(const TXString& dialogTitle, const TXString& contextHelpID, TXString& inOutStartMarkerSymName, TXString& inOutEndMarkerSymName)
		{
			return false;
		}

		virtual bool ImportParasolidXT(IFileIdentifier* pFileID, ViewPt* position)
		{
			return false;
		}

		virtual bool CreateSearchablePulldownMenu(Sint32 dialogID, Sint32 controlID, Sint32 widthInStdChar)
		{
			return false;
		}

		virtual bool InsertStaticItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, const TXString& itemImageSpec)
		{
			return false;
		}

		virtual bool InsertItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, const TXString& itemImageSpec)
		{
			return false;
		}

		virtual bool InsertChildItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& parentIDStr, const TXString& itemToolTip,
			const TXString& itemImageSpec)
		{
			return false;
		}

		virtual void ClearChoicesFromSearchablePulldown(Sint32 dialogID, Sint32 controlID, bool clearStaticItems)
		{

		}

		virtual TXString GetActiveIDStrFromSearchablePulldown(Sint32 dialogID, Sint32 controlID)
		{
			return "";
		}

		virtual bool SetActiveIDStrInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& activeIDStr)
		{
			return false;
		}

		virtual bool GetDisplayNameFromIDStrInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& idStrToFind, TXString& outName)
		{
			return false;
		}

		virtual bool GetIDStrFromDisplayNameInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& nameToFind, TXString& outIDStr)
		{
			return false;
		}

		virtual MCObjectHandle GetWallRecessGeometryGroup(MCObjectHandle objectHand)
		{
			return 0;
		}

		virtual bool SetWallRecessGeometryGroup(MCObjectHandle objectHand, MCObjectHandle hNewGroup)
		{
			return false;
		}


		virtual Boolean EndAndRemoveUndoEvent() { return false; }

		virtual void ClearUndoTableDueToUnsupportedAction() {  }

		virtual void AlertDialogWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink) { }

		virtual Boolean SetListBrowserItemTextColorN(Sint32 dialogID, Sint32 componentID, int itemIndex, int subItemIndex, EUiControlTextTint colorTint) { return true; }

		virtual bool  GetSpaceWallInserts(MCObjectHandle space, bool includeExteriorWallInserts, bool includeInteriorWallInserts, std::vector<InternalIndex> &wallInserts) { return false; }

		virtual bool IsListBrowserExternalSortEnabled(Sint32 dialogID, Sint32 controlID) const { return false; }

		virtual void EnableListBrowserExternalSort(Sint32 dialogID, Sint32 controlID, bool bEnable/* = true*/) { }

		virtual bool TesselateObjectN(TTesselator pTess, const STesselateOptions& options, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv) { return false; }
		virtual void Get2DComponentLocation(MCObjectHandle hObject, EViewTypes component, bool &onBoundsCube, double &offset) { }

		virtual bool Set2DComponentLocation(MCObjectHandle hObject, EViewTypes component, bool onBoundsCube, double offset) { return false; }

		virtual EObjectCutPlane GetHorizontalSectionCutPlane(MCObjectHandle hObject) { return EObjectCutPlane::kViewAsCutWhenCutInViewport; }

		virtual bool SetHorizontalSectionCutPlane(MCObjectHandle hObject, EObjectCutPlane objectCutPlane) { return false; }

		virtual EObjectCutPlane GetVerticalSectionCutPlane(MCObjectHandle hObject) { return EObjectCutPlane::kViewAsCutWhenCutInViewport; }

		virtual bool SetVerticalSectionCutPlane(MCObjectHandle hObject, EObjectCutPlane objectCutPlane) { return false; }

		virtual bool Get2DComponentsByStyle(MCObjectHandle hObject) { return false; }
		virtual bool Set2DComponentsByStyle(MCObjectHandle hObject, bool byStyle) { return false; }
		virtual bool GetMirrorEmpty2DComponentsByStyle(MCObjectHandle hObject) { return false;	}
		virtual bool SetMirrorEmpty2DComponentsByStyle(MCObjectHandle hObject, bool byStyle) { return false; }
		virtual bool GetTopPlan2DComponentByStyle(MCObjectHandle hObject) { return false; }
		virtual bool SetTopPlan2DComponentByStyle(MCObjectHandle hObject, bool byStyle) { return false; }
		virtual bool GetHorizontalSectionCutPlaneByStyle(MCObjectHandle hObject) { return false; }
		virtual bool SetHorizontalSectionCutPlaneByStyle(MCObjectHandle hObject, bool byStyle) { return false; }
		virtual bool GetVerticalSectionCutPlaneByStyle(MCObjectHandle hObject) { return false; }
		virtual bool SetVerticalSectionCutPlaneByStyle(MCObjectHandle hObject, bool byStyle) { return false; }

		virtual bool	VCOM_CALLTYPE SetLayerName(MCObjectHandle hLayer, const TXString& layerName, bool updateLayerDependencies) { return false; }
		virtual bool	VCOM_CALLTYPE SetSheetLayerTitle(MCObjectHandle hLayer, const TXString& sheetTitle) { return false; }

		virtual void	VCOM_CALLTYPE AlertCriticalWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink) { }
		virtual void	VCOM_CALLTYPE AlertInformWithHyperlink(const TXString& text, const TXString& adviceBeforeLink, const TXString& linkTitle, const TXString& linkURL, const TXString& adviceAfterLink, bool minorAlert = false, const TXString& category = "", const TXString& item = "", const TXString& checkboxOverrideText = "") { }

		// VW 2021
	public:
		virtual InternalName	CheckAndResolveDuplicateInternalName(const InternalName& inName) { return ""; }
		virtual bool			VCOM_CALLTYPE GetVWResourceStringKeys(const char* resourceIdentifier, std::vector<TXString>& outvecKeys) { return false; }

		virtual bool			CreateClassPullDownMenuN(Sint32 nDialogID, Sint32 nComponentID, int widthInStdChar, bool bShowDefaultStaticItems = true) { return false; }
		virtual bool			CreateLayerPullDownMenuN(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar, bool bShowDefaultStaticItems = true) { return false; }
		virtual bool			CreateSheetLayerPullDownMenuN(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar, bool bShowDefaultStaticItems = true) { return false; }
		virtual bool			CreateDesignLayerPullDownMenuN(Sint32 dialogID, Sint32 itemID, Sint32 widthInStdChar, bool bShowDefaultStaticItems = true) { return false; }

		virtual bool			InsertHeaderItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemDisplayName, const TXString& itemToolTip) { return false; }
		virtual void			VCOM_CALLTYPE PixelLengthToLineWeight(short inPixels, short& outLineWeightMils) {}
		virtual void			VCOM_CALLTYPE LineWeightToPixelLength(short inLineWeightMils, short& outPixels) {}
		virtual bool			VCOM_CALLTYPE ShowFloatingDataBar(bool bShow) { return false; }
		virtual Boolean			VCOM_CALLTYPE IsDesignLayerSectionViewport(MCObjectHandle hObj) { return false; }
		virtual void			VCOM_CALLTYPE UpdateSLVPForOnlyAnnotationsChange(MCObjectHandle inhSLVP, const WorldRect& inwrBoxBefore_SLVP, const WorldRect& inwrBoxBefore_Annots) {}

		virtual bool			VCOM_CALLTYPE InsertHeaderItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemDisplayName, const TXString& itemToolTip, const TXString& itemImageSpec);
		virtual bool			VCOM_CALLTYPE InsertHeaderItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemDisplayName, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon);

		virtual bool			VCOM_CALLTYPE InsertStaticItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon);
		virtual bool			VCOM_CALLTYPE InsertItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon);
		virtual bool			VCOM_CALLTYPE InsertChildItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, const TXString& itemDisplayName, const TXString& parentIDStr, const TXString& itemToolTip, VectorWorks::UI::IIcon* icon);

		virtual void			VCOM_CALLTYPE EnableItemInSearchablePulldown(Sint32 dialogID, Sint32 controlID, const TXString& itemIDStr, bool enableItem);
		virtual MCObjectHandle  GetBoundFromWalls(TVWArray_MCObjectHandle & wallList, const TXString& UUID, int columnsAndPilastersEnum, MCObjectHandle existingProfile) { return NULL; }
		
		virtual void			ForEachObjectAtPoint( short traverseWhat, const WorldPt& pt, WorldCoord dRadius, std::function<bool(MCObjectHandle h)> callbackLambda) { }

		virtual MCObjectHandle  CreateMaterial(const TXString& name, bool isSimpleMaterial) { return nullptr; }
		virtual bool			GetObjectMaterialName(MCObjectHandle objectHandle, TXString& outMaterialName) { return false; }
		virtual MCObjectHandle	GetObjectMaterialHandle(MCObjectHandle objectHandle) { return nullptr; }
		virtual bool			SetObjectMaterialHandle(MCObjectHandle objectHandle, MCObjectHandle materialHandle) { return nullptr;  }
		virtual bool			IsMaterialSimple(MCObjectHandle materialHandle) { return false; }
		virtual InternalIndex   GetMaterialTexture(MCObjectHandle materialHandle) { return 0; }
		virtual bool			SetMaterialTexture(MCObjectHandle materialHandle, InternalIndex textureIndex) { return false; }
		virtual InternalIndex	GetMaterialFillStyle(MCObjectHandle materialHandle) { return 0; }
		virtual bool			SetMaterialFillStyle(MCObjectHandle materialHandle, InternalIndex fillStyle) { return false; }
		virtual bool			IsMaterialFillStyleByClass(MCObjectHandle materialHandle) { return false; }
		virtual bool			SetMaterialFillStyleByClass(MCObjectHandle materialHandle, bool isByClass) { return false; }
		virtual bool			GetMaterialFillColor(MCObjectHandle materialHandle, ObjectColorType& fillColors) { return false; }
		virtual bool			SetMaterialFillColor(MCObjectHandle materialHandle, const ObjectColorType& fillColors) { return false; }
		virtual bool			SetSubmaterialsInMaterial(MCObjectHandle materialHandle, const CompoundSubmaterialDataVector& dataVector) { return false; }
		virtual bool			GetSubmaterialsFromMaterial(MCObjectHandle materialHandle, CompoundSubmaterialDataVector& dataVector) { return false; }
		virtual bool			AddSubmaterialToMaterial(MCObjectHandle materialHandle, const TXString&	submaterialName, double fraction = 1.0, bool makePrimary = false) { return false; }
		virtual bool			RemoveSubmaterialFromMaterial(MCObjectHandle materialHandle, const TXString& submaterialName) { return false; }
		virtual bool			UpdateSubmaterialInMaterial(MCObjectHandle materialHandle, const TXString&	submaterialName, double fraction = 1.0, bool makePrimary = false) { return false; }
        
		virtual void			SetExcludeObjectFromDataVisualization(MCObjectHandle objectHandle, Boolean exclude) {}

		// this function must be used during the Regenerate event when kObjXPropPreserveContents Is defined
		// it will delete the regenerable sub objects from child list of the parametric, emulating the standard behaviour
		virtual void			DeleteRegenerableSubObjects ( MCObjectHandle hParametric ){}

		virtual Boolean			GetComponentMaterial(MCObjectHandle object, short componentIndex, InternalIndex &material) { return false; }
		virtual Boolean			SetComponentMaterial(MCObjectHandle object, short componentIndex, InternalIndex material) { return false; }

		virtual MCObjectHandle	VCOM_CALLTYPE CustomObjectGetPathProxy(MCObjectHandle inPathObject, ObjectPropID inPurpose) { return nullptr; }

	// VW 2021
	public:
		virtual void			VCOM_CALLTYPE EditPluginStyle(MCObjectHandle hStyle) { };

		virtual bool			VCOM_CALLTYPE GetWorksheetCellFlagChanged(MCObjectHandle worksheet, const ViewPt& cell) { return true; }
		virtual bool			VCOM_CALLTYPE GetWorksheetCellFlagInvalid(MCObjectHandle worksheet, const ViewPt& cell) { return true; }

		virtual bool			VCOM_CALLTYPE CreateResourceTextPopup(Sint32 dialogID, Sint32 controlID, Sint32 widthInStdChar) { return false; }

		virtual double			VCOM_CALLTYPE GetRotationAroundAxis(MCObjectHandle hObject, MajorAxisSpec aroundAxis) { return 0.0; }
		virtual void			VCOM_CALLTYPE TransformObject(MCObjectHandle hObject, const TransformMatrix& transformMatrix) {}
		virtual MCObjectHandle	VCOM_CALLTYPE AssociateBoundedObjectWithWallsAndApplyOffset(MCObjectHandle inBoundedObject, TVWArray_MCObjectHandle& wallList, short inColumnsAndPilastersEnum, double offsetDistance, bool bExcludePiosNiches)
		{
			return NULL;
		}

		virtual bool			VCOM_CALLTYPE GetClassByStyle(MCObjectHandle h) { return false; }
		virtual bool			VCOM_CALLTYPE SetClassByStyle(MCObjectHandle h, bool byStyle) { return false; }

		virtual double			VCOM_CALLTYPE GetMaterialArea(MCObjectHandle hObject, const TXString& materialName) { return 0.0; }
		virtual double			VCOM_CALLTYPE GetMaterialVolume(MCObjectHandle hObject, const TXString& materialName) { return 0.0; }
		virtual void            VCOM_CALLTYPE ComposeObjectHandles(TVWArray_MCObjectHandle& objsToComposeArray, bool bInsert, TVWArray_MCObjectHandle& composedObjsArray){}

		virtual MCObjectHandle	VCOM_CALLTYPE DuplicateObjectIgnoreConstraints(MCObjectHandle h) { return NULL; }
 		virtual WorldCoord      VCOM_CALLTYPE GetStoryObjectDataBoundHeight(const SStoryObjectData& storyData, MCObjectHandle hContainer) { return 0.0; }
		virtual void			VCOM_CALLTYPE ForEachMaterial(bool onlyUsed, std::function<void(MCObjectHandle h)> callbackLambda) {};

	};
}
