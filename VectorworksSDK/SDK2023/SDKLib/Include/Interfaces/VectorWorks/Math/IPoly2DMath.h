//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IPolyDef.h"
#include "IPolyDefArray.h"
#include <vector>

namespace VectorWorks
{
	namespace Math
	{
		// ---------------------------------------------------------------------------------------------------
		// {05F22431-C1BB-47a5-8E74-EBD025C3194F}
		static const VWIID IID_Poly2DMath	= { 0x5f22431, 0xc1bb, 0x47a5, { 0x8e, 0x74, 0xeb, 0xd0, 0x25, 0xc3, 0x19, 0x4f } };

		class DYNAMIC_ATTRIBUTE IPoly2DMath : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError		VCOM_CALLTYPE CreateHandle(IPolyDef* pPoly, MCObjectHandle& outHandle) = 0;
			virtual VCOMError		VCOM_CALLTYPE CreatePoly(MCObjectHandle hObject, IPolyDef** ppOutPolygon) = 0;
			virtual MCObjectHandle	VCOM_CALLTYPE CreateOffsetPoly(MCObjectHandle polyHandle, double offset, bool smoothCorner = false, bool doUndo = true)=0;

			virtual bool				VCOM_CALLTYPE FiniteLine3DIntersectPoly(MCObjectHandle poly, const WorldPt3& lineStart, const WorldPt3& lineEnd, WorldPt3& outClosestToStart, WorldPt3& outClosestToEnd) = 0;
			virtual bool				VCOM_CALLTYPE Line3DIntersectPoly(MCObjectHandle poly, WorldPt3& posInOut, WorldPt3& dir, bool testAsRay, bool useTol = true) = 0;
			virtual bool				VCOM_CALLTYPE GetClosestProjectedPoint(MCObjectHandle h, const WorldPt &pickPt, double &distance, WorldPt& closestPoint) = 0;
			virtual bool				VCOM_CALLTYPE GetClosestProjectedPointEx(MCObjectHandle h, const WorldPt &pickPt, double &distance, WorldPt& closestPoint, WorldPt& tangent) = 0;
			virtual bool				VCOM_CALLTYPE Intersect2Objects(MCObjectHandle obj1, MCObjectHandle obj2, Boolean onlyOnObjs, std::vector<WorldPt>& intersections)=0;
			virtual bool				VCOM_CALLTYPE Intersect2Objects(MCObjectHandle obj1, MCObjectHandle obj2, Boolean onlyOnObjs, Boolean isPolylineHolesIncluded, std::vector<WorldPt>& intersections) = 0;
			virtual bool				VCOM_CALLTYPE SplitPolyline(MCObjectHandle inhObject, const WorldPt& inwptPick, MCObjectHandle& outhObject1, MCObjectHandle& outhObject2) = 0; // killsOriginal, insertsResults
			virtual bool				VCOM_CALLTYPE SplitPolyline(MCObjectHandle inhObject, const WorldPt& inwptPick, bool inbKillOriginal, MCObjectHandle& outhObject1, MCObjectHandle& outhObject2) = 0;
			
			enum class EClipPolylineMode {
				eClip,
				eUnion,
				eIntersect
			};
			virtual MCObjectHandle		VCOM_CALLTYPE ClipPolyline(EClipPolylineMode inMode, MCObjectHandle inhBlank, MCObjectHandle inhTool)=0;
			//virtual bool				VCOM_CALLTYPE ExtendPolyline( MCObjectHandle poly, WorldPt pt1, WorldPt pt2 ) = 0;
			virtual bool				VCOM_CALLTYPE JoinPolylines( MCObjectHandle poly, MCObjectHandle toPoly ) = 0;
			virtual void				VCOM_CALLTYPE GetPK_CurvesFromPoly( MCObjectHandle poly, std::vector<Sint32>& curves, std::vector<std::pair<double, double>>& intervals, std::vector<Boolean> &visibilities, std::vector<short> &arcTypes) = 0;
			virtual double				VCOM_CALLTYPE GetPolyLength( MCObjectHandle poly ) = 0;

			virtual void				VCOM_CALLTYPE ForEachPolylineCurve(MCObjectHandle inPolyH, std::function<void(const SPolyEdge& edge)> callbackLambda) = 0; // like ForEachPolyEdgeN, but corrects arc direction
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IPoly2DMath>	IPoly2DMathPtr;
	}
}
