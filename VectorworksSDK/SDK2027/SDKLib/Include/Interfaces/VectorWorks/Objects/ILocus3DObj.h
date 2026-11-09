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
		static const VWIID IID_Locus3DObj		= { 0xA8548484, 0x05E6, 0x11DB, { 0x95, 0x92, 0x00, 0x05, 0x9A, 0x3C, 0x78, 0x00 } };
	
		class DYNAMIC_ATTRIBUTE ILocus3DObj : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Create(MCObjectHandle& outObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsType(MCObjectHandle hObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	ResetObject(MCObjectHandle hObject) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetPoint(MCObjectHandle hObject, _WorldPt3& outPt) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetPoint(MCObjectHandle hObject, const _WorldPt3& pt) = 0;
		};
	}
}