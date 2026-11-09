//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace UI
	{
		// ----------------------------------------------------------------------------------------------------
		// {7E8C933D-CC09-4202-B14F-EFFB04FA4220}

		static const VWIID IID_ProgressDialog = { 0x7E8C933D, 0xCC09, 0x4202, { 0xB1, 0x4F, 0xEF, 0xFB, 0x04, 0xFA, 0x42, 0x20 } };

		class DYNAMIC_ATTRIBUTE IProgressDialog : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Open(const TXString& title)						= 0;
            virtual VCOMError VCOM_CALLTYPE SetLayoutType(int type)                         = 0;
			virtual VCOMError VCOM_CALLTYPE Close()											= 0;

			virtual VCOMError VCOM_CALLTYPE	AllowUserCancel(bool bAllow)					= 0;
			virtual VCOMError VCOM_CALLTYPE	ResetMeter(Uint16 meter)						= 0;
			virtual VCOMError VCOM_CALLTYPE	SetTopText(const TXString& szTopText)			= 0;
			virtual VCOMError VCOM_CALLTYPE	SetBottomText(const TXString& szBottomText)		= 0;
			virtual VCOMError VCOM_CALLTYPE	SetMeterText(const TXString& szMeterText)		= 0;

			virtual VCOMError VCOM_CALLTYPE	HasUserCanceled(bool& bUserCanceled)			= 0;
			virtual VCOMError VCOM_CALLTYPE	DoYield()										= 0;
			virtual VCOMError VCOM_CALLTYPE	IncrementMeter(Uint16 step)						= 0;

			virtual VCOMError VCOM_CALLTYPE	SetTitle(const TXString& title)					= 0;
			virtual VCOMError VCOM_CALLTYPE	DoPause(bool pausing)							= 0;
		};

		typedef VCOMPtr<IProgressDialog>		IProgressDialogPtr;
	}
}