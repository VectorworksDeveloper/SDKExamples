//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Objects
	{
		// ---------------------------------------------------------------------------------------------------
		static const VWIID IID_Polygon2DObj		= { 0x0C3B1D54, 0x05E8, 0x11DB, { 0x95, 0x92, 0x00, 0x05, 0x9A, 0x3C, 0x78, 0x00 } };
	
		class DYNAMIC_ATTRIBUTE IPolygon2DObj : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Create(MCObjectHandle& outObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsType(MCObjectHandle hObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	ResetObject(MCObjectHandle hObject) = 0;

			virtual VCOMError VCOM_CALLTYPE	AddCornerVertex(MCObjectHandle hObject, const _WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	AddBezierVertex(MCObjectHandle hObject, const _WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	AddCubicVertex(MCObjectHandle hObject, const _WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	AddArcVertex(MCObjectHandle hObject, const _WorldPt& pt, WorldCoord dRadius) = 0;

			virtual VCOMError VCOM_CALLTYPE	InsertCornerVertex(MCObjectHandle hObject, Uint32 beforeIndex, const _WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	InsertBezierVertex(MCObjectHandle hObject, Uint32 beforeIndex, const _WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	InsertCubicVertex(MCObjectHandle hObject, Uint32 beforeIndex, const _WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	InsertArcVertex(MCObjectHandle hObject, Uint32 beforeIndex, const _WorldPt& pt, WorldCoord dRadius) = 0;

			virtual VCOMError VCOM_CALLTYPE	SetCornerVertex(MCObjectHandle hObject, Uint32 index, const _WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetBezierVertex(MCObjectHandle hObject, Uint32 index, const _WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetCubicVertex(MCObjectHandle hObject, Uint32 index, const _WorldPt& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetArcVertex(MCObjectHandle hObject, Uint32 index, const _WorldPt& pt, WorldCoord dRadius) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetVertexCount(MCObjectHandle hObject, Uint32& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteVertex(MCObjectHandle hObject, Uint32 vertIndex) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteVertices(MCObjectHandle hObject) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetVertexPoint(MCObjectHandle hObject, Uint32 index, _WorldPt& outPt) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetVertexRadius(MCObjectHandle hObject, Uint32 index, WorldCoord& outRadius) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetControlVertex(MCObjectHandle hObject, Uint32 index, _WorldPt& outCtrlPt) = 0;

			virtual VCOMError VCOM_CALLTYPE	IsVertexCorner(MCObjectHandle hObject, Uint32 index, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsVertexBezier(MCObjectHandle hObject, Uint32 index, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsVertexCubic(MCObjectHandle hObject, Uint32 index, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsVertexArc(MCObjectHandle hObject, Uint32 index, bool& outValue) = 0;

			virtual VCOMError VCOM_CALLTYPE	IsVertexVisible(MCObjectHandle hObject, Uint32 index, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetVertexVisible(MCObjectHandle hObject, Uint32 index, bool bVisible) = 0;

			virtual VCOMError VCOM_CALLTYPE	IsClosed(MCObjectHandle hObject, bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetClosed(MCObjectHandle hObject, bool bClosed) = 0;

			// conversion
			virtual VCOMError VCOM_CALLTYPE	ConvertToPolyline(MCObjectHandle hObject, MCObjectHandle& outPolyline, bool bPreserveOriginal) = 0;
			virtual VCOMError VCOM_CALLTYPE	ConvertToPolygon(MCObjectHandle hObject, MCObjectHandle& outPolygon, Uint16 res) = 0;
		};
	}
}
