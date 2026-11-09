//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace UI
	{
		// ------------------------------------------------------------------------------
		enum EInfoMsgBackColor {
			eInfoMsgBackColor_Standard,
			eInfoMsgBackColor_Blue,
			eInfoMsgBackColor_Red
		};

		// ----------------------------------------------------------------------------------------------------
		// {46A01702-34B4-41b5-B434-AC92D807731E}
		static const VWIID IID_InfoBar = { 0x46A01702, 0x34B4, 0x41b5, { 0xB4, 0x34, 0xAC, 0x92, 0xD8, 0x07, 0x73, 0x1E } };

		class DYNAMIC_ATTRIBUTE IInfoBar : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	SetMinorAlert(const TXString& strAlert, EInfoMsgBackColor backClr)	= 0;

			virtual VCOMError VCOM_CALLTYPE StartProgressIndicator(const TXString& strProgressLabel, Uint16 nMaxProgress)	= 0;
			virtual VCOMError VCOM_CALLTYPE	SetProgressIndicator(Uint16 nProgress)											= 0;
			virtual VCOMError VCOM_CALLTYPE	SetProgressIndicator(Uint16 nProgress, const TXString& strProgressLabel)		= 0;
			virtual VCOMError VCOM_CALLTYPE	IncrementProgressIndicator(Uint16 nProgress)									= 0;
			virtual VCOMError VCOM_CALLTYPE	IncrementProgressIndicator(Uint16 nProgress, const TXString& strProgressLabel)	= 0;
			virtual VCOMError VCOM_CALLTYPE	EndProgressIndicator()	= 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IInfoBar>		IInfoBarPtr;
	}
}