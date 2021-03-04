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
		static const VWIID IID_Polygon3DObj		= { 0x01A215B4, 0x05E8, 0x11DB, { 0x95, 0x92, 0x00, 0x05, 0x9A, 0x3C, 0x78, 0x00 } };
	
		class DYNAMIC_ATTRIBUTE IPolygon3DObj : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Create(MCObjectHandle& outObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsType(MCObjectHandle hObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	ResetObject(MCObjectHandle hObject) = 0;

			virtual VCOMError VCOM_CALLTYPE	AddVertex(MCObjectHandle hObject, const _WorldPt3& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	InsertVertex(MCObjectHandle hObject, Uint32 beforeIndex, const _WorldPt3& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetVertex(MCObjectHandle hObject, Uint32 index, const _WorldPt3& pt) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetVertex(MCObjectHandle hObject, Uint32 index, _WorldPt3& outPt) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetVertexCount(MCObjectHandle hObject, Uint32& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteVertex(MCObjectHandle hObject, Uint32 index) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteVertices(MCObjectHandle hObject) = 0;

			virtual VCOMError VCOM_CALLTYPE	SetClosed(MCObjectHandle hObject, bool bClosed) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetClosed(MCObjectHandle hObject, bool& outClosed) = 0;
		};
	}
}
