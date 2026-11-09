//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Math
	{
		// ---------------------------------------------------------------------------------------------------
		enum EVertexType {
			eVertexType_Corner		= 0,
			eVertexType_Bezier		= 1,
			eVertexType_Cubic		= 2,
			eVertexType_Arc			= 3,
			eVertexType_Radius		= 4,
		};

		// ---------------------------------------------------------------------------------------------------
		class IPolyDefArray;

		// ---------------------------------------------------------------------------------------------------
		// {450A730D-81B2-47c2-8656-0C3859E1C3D7}
		static const VWIID IID_PolyDef	= { 0x450a730d, 0x81b2, 0x47c2, { 0x86, 0x56, 0xc, 0x38, 0x59, 0xe1, 0xc3, 0xd7 } };

		class DYNAMIC_ATTRIBUTE IPolyDef : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE ClearVertices() = 0;
			virtual VCOMError VCOM_CALLTYPE AddVertex(const WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE AddVertex(const WorldPt3& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE AddVertex(const WorldPt& pt, EVertexType type) = 0;
			virtual VCOMError VCOM_CALLTYPE AddVertex(const WorldPt3& pt, EVertexType type) = 0;
			virtual VCOMError VCOM_CALLTYPE AddVertex(const WorldPt& pt, double dArcRadius) = 0;
			virtual VCOMError VCOM_CALLTYPE AddVertex(const WorldPt3& pt, double dArcRadius) = 0;
			virtual VCOMError VCOM_CALLTYPE InsertVertex(Uint32 index, const WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE InsertVertex(Uint32 index, const WorldPt3& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE InsertVertex(Uint32 index, const WorldPt& pt, EVertexType type) = 0;
			virtual VCOMError VCOM_CALLTYPE InsertVertex(Uint32 index, const WorldPt3& pt, EVertexType type) = 0;
			virtual VCOMError VCOM_CALLTYPE InsertVertex(Uint32 index, const WorldPt& pt, double dArcRadius) = 0;
			virtual VCOMError VCOM_CALLTYPE InsertVertex(Uint32 index, const WorldPt3& pt, double dArcRadius) = 0;

			virtual VCOMError VCOM_CALLTYPE GetVertexCount(Uint32& outCount) const = 0;
			virtual VCOMError VCOM_CALLTYPE IsEmpty(bool& outValue) const = 0;
			virtual VCOMError VCOM_CALLTYPE IsClosed(bool& outValue) const = 0;
			virtual VCOMError VCOM_CALLTYPE SetClosed(bool bClosed) = 0;

			virtual VCOMError VCOM_CALLTYPE GetVertexAt(Sint32 index, WorldPt& outPt) const = 0;
			virtual VCOMError VCOM_CALLTYPE GetVertexAt(Sint32 index, WorldPt3& outPt) const = 0;
			virtual VCOMError VCOM_CALLTYPE SetVertexAt(Sint32 index, const WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE SetVertexAt(Sint32 index, const WorldPt3& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE GetVertexType(Sint32 index, EVertexType& outType) const = 0;
			virtual VCOMError VCOM_CALLTYPE SetVertexType(Sint32 index, EVertexType type) = 0;
			virtual VCOMError VCOM_CALLTYPE GetArcVertexRadius(Sint32 index, double& outRadius) const = 0;
			virtual VCOMError VCOM_CALLTYPE SetArcVertexRadius(Sint32 index, double dRadius) = 0;
			virtual VCOMError VCOM_CALLTYPE GetVertexVisible(Sint32 index) const = 0;
			virtual VCOMError VCOM_CALLTYPE SetVertexVisible(Sint32 index, bool bVisible) = 0;

			virtual VCOMError VCOM_CALLTYPE Set(IPolyDef* pPoly) = 0;

			virtual VCOMError VCOM_CALLTYPE HasHoles() const = 0;
			virtual VCOMError VCOM_CALLTYPE GetHoles(IPolyDefArray** ppOutArrHoles) const = 0;
			virtual VCOMError VCOM_CALLTYPE SetHoles(IPolyDefArray* pArrHoles) = 0;
			virtual VCOMError VCOM_CALLTYPE ClearHoles() = 0;
			virtual VCOMError VCOM_CALLTYPE AddHole(IPolyDef* pHolePoly) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IPolyDef>	IPolyDefPtr;
	}
}
