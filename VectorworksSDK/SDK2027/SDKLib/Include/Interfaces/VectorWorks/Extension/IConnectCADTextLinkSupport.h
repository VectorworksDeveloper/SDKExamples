//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {77C7D47C-8577-42E1-B77F-47F2F9C709CD}
		static const VWIID IID_ConnectCADTextLinkSupport = { 0x77c7d47c, 0x8577, 0x42e1, { 0xb7, 0x7f, 0x47, 0xf2, 0xf9, 0xc7, 0x9, 0xcd } };

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IConnectCADTextLinkSupport : public IVWUnknown
		{
			public:
				virtual bool			VCOM_CALLTYPE IsSupported(MCObjectHandle hTextObj) = 0;

				virtual TXString		VCOM_CALLTYPE GetTitleOverride(MCObjectHandle hTextObj, bool plural) = 0;
				virtual void			VCOM_CALLTYPE GetPromptStrings(TXString& outSeparator, TXString& outCheck, TXString& outPopup) = 0; // Not used anymore

				virtual bool			VCOM_CALLTYPE IsLinked(MCObjectHandle hObj) = 0;
				virtual void			VCOM_CALLTYPE SetIsLinked(MCObjectHandle hObj, bool isLinked) = 0;

				virtual void			VCOM_CALLTYPE GetLinkChoices(MCObjectHandle hTextObj, std::vector<TXString>& outArrUnivChoices, std::vector<TXString>& outArrLocChoices) = 0; // Not used anymore
				virtual TXString		VCOM_CALLTYPE GetLinkFormula(MCObjectHandle hTextObj) = 0;
				virtual void			VCOM_CALLTYPE SetLinkFormula(MCObjectHandle hTextObj, const TXString& linkFormula) = 0;
				virtual TXString		VCOM_CALLTYPE GetLinkFormulaByIndex(MCObjectHandle hTextObj, size_t index) = 0; // Not used anymore

				// VW 2022
				virtual bool			VCOM_CALLTYPE IsCustomFormula(MCObjectHandle hObj) = 0;
				virtual void			VCOM_CALLTYPE SetCustomFormulaName(MCObjectHandle hObj, const TXString& customFormulaName) = 0;
				virtual TXString		VCOM_CALLTYPE GetCustomFormulaName(MCObjectHandle hTextObj) = 0;

				virtual TXString		VCOM_CALLTYPE GetLinkFormulaValue(MCObjectHandle hObj) = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<IConnectCADTextLinkSupport>	IConnectCADTextLinkSupportPtr;
	}
}