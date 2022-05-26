//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Debug
	{
		// ----------------------------------------------------------------------------------------------------
		// {31DE6910-562E-41f1-8682-D25251CE5C1C}
		static const VWIID IID_DebugSupport = { 0x31de6910, 0x562e, 0x41f1, { 0x86, 0x82, 0xd2, 0x52, 0x51, 0xce, 0x5c, 0x1c } };

		class DYNAMIC_ATTRIBUTE IDebugSupport : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE ShowAlertDialog(const char* szQuestion, const char* szAdvice, short defaultButton, const char* szOKOverrideText, const char* szCancelOverrideText, const char* szCustomButtonAText, const char* szCustomButtonBText, short& outRes) = 0;
			virtual VCOMError VCOM_CALLTYPE ShouldBreak(const char* szFileName, Uint32 fileLine, bool& outDoStop) = 0;
			virtual VCOMError VCOM_CALLTYPE StopBreaks(const char* szFileName, Uint32 fileLine) = 0;
			virtual VCOMError VCOM_CALLTYPE ShowOptionsDialog() = 0;
			virtual VCOMError VCOM_CALLTYPE GetStopAtBreaks(bool& outStopBreaks) = 0;
			virtual VCOMError VCOM_CALLTYPE SetStopAtBreaks(bool bStopBreaks) = 0;
            
            virtual bool VCOM_CALLTYPE ShowingAlertDialog() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {67858021-A721-4ef8-B27A-3B061FBAC2F4}
		static const VWIID IID_DebugOutputLog = { 0x67858021, 0xa721, 0x4ef8, { 0xb2, 0x7a, 0x3b, 0x6, 0x1f, 0xba, 0xc2, 0xf4 } };

		class DYNAMIC_ATTRIBUTE IDebugOutputLog : public IVWSingletonUnknown
		{
		public:
			virtual void VCOM_CALLTYPE	LocalLogStr(Uint16 level, bool doDebugWindow, const char *description) = 0;
			virtual void VCOM_CALLTYPE	SendToLogWriter(Uint16 level, const TJsonLogDataMap& logFields) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {C3ACCA61-4DAB-49e6-A08C-C44AA70DF048}
		static const VWIID IID_DebugMenuSupport = { 0xc3acca61, 0x4dab, 0x49e6, { 0xa0, 0x8c, 0xc4, 0x4a, 0xa7, 0xd, 0xf0, 0x48 } };

		class DYNAMIC_ATTRIBUTE IDebugMenuSupport : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE AddMenu(const VWIID& menuAppIID) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetMenuCount(Uint32& outCount) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetMenuAt(Uint32 index, VWIID& outMenuAppIID) = 0;
			virtual bool		VCOM_CALLTYPE IsAvailable() = 0;
			virtual void		VCOM_CALLTYPE SetAvailable(bool value) = 0;
		};

		typedef VCOMPtr<IDebugMenuSupport>		IDebugMenuSupportPtr;
	}
}
