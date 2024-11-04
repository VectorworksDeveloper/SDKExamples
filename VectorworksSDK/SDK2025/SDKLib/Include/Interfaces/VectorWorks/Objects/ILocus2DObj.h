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
		static const VWIID IID_Locus2DObj		= { 0xBC150D54, 0x05E6, 0x11DB, { 0x95, 0x92, 0x00, 0x05, 0x9A, 0x3C, 0x78, 0x00 } };
	
		class DYNAMIC_ATTRIBUTE ILocus2DObj : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Create(MCObjectHandle& outObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsType(MCObjectHandle hObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	ResetObject(MCObjectHandle hObject) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetPoint(MCObjectHandle hObject, _WorldPt& outPt) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetPoint(MCObjectHandle hObject, const _WorldPt& pt) = 0;
		};
	}
}