//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once


namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {722371A4-4B98-4067-B2CF-FCADD10A5BBE}
		static const Extension::TSinkIID IID_LeaderLineProvider = { 0x722371a4, 0x4b98, 0x4067, { 0xb2, 0xcf, 0xfc, 0xad, 0xd1, 0xa, 0x5b, 0xbe } };

		class DYNAMIC_ATTRIBUTE ILeaderLineProvider : public Extension::IEventSink
		{
		public:
			virtual VCOMError		VCOM_CALLTYPE GetLeaderLinePt(MCObjectHandle hObject, WorldPt& outPt) = 0;
			virtual VCOMError		VCOM_CALLTYPE SetLeaderLinePt(MCObjectHandle hObject, const WorldPt& pt) = 0;
			virtual VCOMError		VCOM_CALLTYPE GetLabelPt(MCObjectHandle hObject, WorldPt& outPt) = 0;
			virtual VCOMError		VCOM_CALLTYPE SetLabelPt(MCObjectHandle hObject, const WorldPt& pt) = 0;
			virtual VCOMError		VCOM_CALLTYPE GetLeaderEndPt(MCObjectHandle hObject, WorldPt& outPt) = 0;
		};
	}
}