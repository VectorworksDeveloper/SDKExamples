//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IPolyDef.h"
#include "IPolyDefArray.h"

namespace VectorWorks
{
	namespace Math
	{
		// ---------------------------------------------------------------------------------------------------
		// // {A489DFA7-547E-4c0f-B21F-9297324BE9E2}
		static const VWIID IID_Poly2DOperations	= { 0xa489dfa7, 0x547e, 0x4c0f, { 0xb2, 0x1f, 0x92, 0x97, 0x32, 0x4b, 0xe9, 0xe2 } };

		class DYNAMIC_ATTRIBUTE IPoly2DOperations : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE AddSurface(IPolyDef* pPoly1, IPolyDef* pPoly2, IPolyDefArray** ppOutResult) = 0;
			virtual VCOMError VCOM_CALLTYPE ClipSurface(IPolyDef* pPoly1, IPolyDef* pPoly2, IPolyDefArray** ppOutResult) = 0;
			virtual VCOMError VCOM_CALLTYPE IntersectSurface(IPolyDef* pPoly1, IPolyDef* pPoly2, IPolyDefArray** ppOutResult) = 0;
			virtual VCOMError VCOM_CALLTYPE CombineIntoSurface(IPolyDefArray* pPolys, const WorldPt& pt, IPolyDefArray** ppOutResult) = 0;

			virtual VCOMError VCOM_CALLTYPE Offset(IPolyDef* pPoly, double dOffset, bool bSmoothConers, IPolyDefArray** ppOutResult) = 0;
			
			virtual VCOMError VCOM_CALLTYPE Reserved(Sint32, MCObjectHandle, MCObjectHandle, MCObjectHandle&) = 0;

			virtual VCOMError VCOM_CALLTYPE	AddSurfaceMultiple(IPolyDefArray* polysArray, IPolyDefArray** ppOutResult) = 0;

			virtual VCOMError VCOM_CALLTYPE GetClosestProjectedPoint( IPolyDef* poly, const WorldPt& pickPt, double &distance, WorldPt& closestPoint ) = 0;
			virtual VCOMError VCOM_CALLTYPE Intersect2Objects( IPolyDef* pPoly1, IPolyDef* pPoly2, Boolean onlyOnObjs, std::vector<WorldPt>& intersections ) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IPoly2DOperations>	IPoly2DOperationsPtr;
	}
}
