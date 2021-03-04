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
		static const VWIID IID_OvalObj		= { 0x6B037822, 0x05C7, 0x11DB, { 0x95, 0x92, 0x00, 0x05, 0x9A, 0x3C, 0x78, 0x00 } };
	
		class DYNAMIC_ATTRIBUTE IOvalObj : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Create(MCObjectHandle& outObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsType(MCObjectHandle hObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	ResetObject(MCObjectHandle hObject) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetOrigin(MCObjectHandle hObject, _WorldPt& outPt) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetOrigin(MCObjectHandle hObject, const _WorldPt& pt) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetOrientation(MCObjectHandle hObject, _WorldPt& outDirVector) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetOrientation(MCObjectHandle hObject, const _WorldPt& dirVector) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetHeight(MCObjectHandle hObject, WorldCoord& outHeight) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetHeight(MCObjectHandle hObject, const WorldCoord& height) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetWidth(MCObjectHandle hObject, WorldCoord& outWidth) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetWidth(MCObjectHandle hObject, const WorldCoord& width) = 0;


		};
	}
}