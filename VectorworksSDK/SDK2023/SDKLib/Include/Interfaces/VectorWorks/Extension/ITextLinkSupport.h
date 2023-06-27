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
		// {C49B70D4-791A-4983-82AC-2CB90632E168}
		static const VWGroupID GROUPID_TextLinkProvides = { 0xc49b70d4, 0x791a, 0x4983, { 0x82, 0xac, 0x2c, 0xb9, 0x6, 0x32, 0xe1, 0x68 } };

		// ---------------------------------------------------------------------------
		// {A18C5E50-3F29-434B-AF5F-9FD65D77E7D2}
		static const VWIID IID_TextLinkSupport = { 0xa18c5e50, 0x3f29, 0x434b, { 0xaf, 0x5f, 0x9f, 0xd6, 0x5d, 0x77, 0xe7, 0xd2 } };

		// ---------------------------------------------------------------------------
		// {6606FD01-D28E-4090-83E7-3593F76EDC44}
		static const VWIID IID_TitleBlockDataProvider = { 0x6606fd01, 0xd28e, 0x4090, { 0x83, 0xe7, 0x35, 0x93, 0xf7, 0x6e, 0xdc, 0x44 } };

		// {6DE7E1CA-09C1-4112-9A5C-504682E2C788}
		static const VWIID IID_UpdateTitleBlock = { 0x6de7e1ca, 0x9c1, 0x4112, { 0x9a, 0x5c, 0x50, 0x46, 0x82, 0xe2, 0xc7, 0x88 } };

		// {588BBED5-AD90-4AD4-A595-80A03CF8ECDD}
		static const VWIID IID_LocusSupport = { 0x588bbed5, 0xad90, 0x4ad4, { 0xa5, 0x95, 0x80, 0xa0, 0x3c, 0xf8, 0xec, 0xdd } };

		// ---------------------------------------------------------------------------
		typedef std::unordered_map<TXString, TXString> TXString2TXStringUnorderedMap;

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ITextLinkProvider : public IVWUnknown
		{
		public:
			virtual bool			VCOM_CALLTYPE IsSupported(MCObjectHandle hTextObj) = 0;

			virtual TXString		VCOM_CALLTYPE GetTitleOverride(bool plural) = 0;
			virtual TXString		VCOM_CALLTYPE GetLinkSeparator() = 0;

			virtual size_t			VCOM_CALLTYPE GetAvaiableLinkParamsCnt() = 0;
			virtual TXString		VCOM_CALLTYPE GetAvaiableLinkParamUnivNameAt(size_t index) = 0;
			virtual TXString		VCOM_CALLTYPE GetAvaiableLinkParamLocalNameAt(size_t index) = 0;
			virtual size_t			VCOM_CALLTYPE GetAvaiableCustomLinkParamsCnt() = 0;
			virtual TXString		VCOM_CALLTYPE GetAvaiableCustomLinkParamUnivNameAt(size_t index) = 0;
			virtual TXString		VCOM_CALLTYPE GetAvaiableCustomLinkParamLocalNameAt(size_t index) = 0;
			virtual TXString		VCOM_CALLTYPE GetLinkValue(MCObjectHandle hTextObj) = 0;
			virtual TXString		VCOM_CALLTYPE GetLinkValue(MCObjectHandle hTextObj, const TXString& formula, bool getActualPlotDate = false) = 0;
			virtual TXString		VCOM_CALLTYPE GetDrawingStamp(MCObjectHandle hTextObj) = 0;

			virtual void			VCOM_CALLTYPE GetNotForFundamentalsParams(TXString2TXStringUnorderedMap& outParamsMap) = 0;

			// Get only project data link value, if there is project data in the document
			virtual TXString		VCOM_CALLTYPE GetLinkValueNoTitleBlock(const TXString& formula) = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<ITextLinkProvider>	ITextLinkProviderPtr;

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ITextLinkSupport : public IVWSingletonUnknown
		{
		public:
			virtual ITextLinkProviderPtr	VCOM_CALLTYPE GetProvider(MCObjectHandle hTextObj) = 0;

			virtual bool		VCOM_CALLTYPE ShowEditCustomLinkTextDlg(MCObjectHandle hTextObj) = 0;

			virtual bool		VCOM_CALLTYPE GetIsLinked(MCObjectHandle hTextObj) = 0;
			virtual void		VCOM_CALLTYPE SetIsLinked(MCObjectHandle hTextObj, bool value) = 0;
			virtual TXString	VCOM_CALLTYPE GetLinkFormula(MCObjectHandle hTextObj) = 0;
			virtual void		VCOM_CALLTYPE SetLinkFormula(MCObjectHandle hTextObj, const TXString& formula) = 0;
			virtual bool		VCOM_CALLTYPE GetIsCustomFormula(MCObjectHandle hTextObj) = 0;
			virtual void		VCOM_CALLTYPE SetIsCustomFormula(MCObjectHandle hTextObj, bool value) = 0;
			virtual bool		VCOM_CALLTYPE GetIsIssueOrRevision(MCObjectHandle hTextObj) = 0;
			virtual bool		VCOM_CALLTYPE GetIsTextAlignTop(MCObjectHandle hTextObj) = 0;
			virtual void		VCOM_CALLTYPE SetIsTextAlignTop(MCObjectHandle hTextObj, bool value) = 0;
			virtual bool		VCOM_CALLTYPE GetIsDrawingStamp(MCObjectHandle hTextObj) = 0;
			virtual void		VCOM_CALLTYPE SetIsDrawingStamp(MCObjectHandle hTextObj, bool value) = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<ITextLinkSupport>	ITextLinkSupportPtr;

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ITitleBlockDataProvider : public IVWSingletonUnknown
		{
		public:
			virtual void		VCOM_CALLTYPE	SetTitleBlock(MCObjectHandle hTitleBlock) = 0;

			// Revision Data
			virtual size_t			VCOM_CALLTYPE	GetRevValuesCount() = 0;
			virtual TXString		VCOM_CALLTYPE	GetRevisionNumber(size_t index) = 0;
			virtual TXString		VCOM_CALLTYPE	GetRevisionDate(size_t index) = 0;
			virtual TXString		VCOM_CALLTYPE	GetRevisionNote(size_t index) = 0;
			virtual TXString		VCOM_CALLTYPE	GetRevisionPublishDate(size_t index) = 0;
			virtual TXString		VCOM_CALLTYPE	GetRevisionRecipients(size_t index) = 0;

			// Issue Data
			virtual MCObjectHandle	VCOM_CALLTYPE	CreateNewIssue(const TXString& date, const TXString& note, const TXString& approval, const TXString& recipients) = 0;
			virtual void			VCOM_CALLTYPE	AttachIssueToTBB(MCObjectHandle hIssueFormat, MCObjectHandle hTitleBlockBorder) = 0;
			virtual TXString		VCOM_CALLTYPE	GetIssueDate(size_t index) = 0;
			virtual TXString		VCOM_CALLTYPE	GetLatestIssueDate() = 0;
			virtual TXString		VCOM_CALLTYPE	GetIssueFormatName() = 0;
			virtual void			VCOM_CALLTYPE	UpdateIssueFromFormat(const TXString& issueFormatName, bool resetTBBs = false) = 0;

			// Sheet Data
			virtual TXString		VCOM_CALLTYPE	GetSheetID() = 0;
			virtual TXString		VCOM_CALLTYPE	GetSheetTitle() = 0;
			virtual TXString		VCOM_CALLTYPE	GetSheetDate() = 0;
			virtual void			VCOM_CALLTYPE	UpdatePageNumber() = 0;

			virtual void			VCOM_CALLTYPE	UpdateTBMSelectedSheets(const TXString& oldLayerName, const TXString& layerName, const TXString& sheetTitle) = 0;

			// Project Data
			virtual void			VCOM_CALLTYPE	UpdateTotalNoOfSheets() = 0;

			// Record Info
			virtual bool			VCOM_CALLTYPE	IsSpecialRecordFormat(const TXString& formatName) = 0;
			virtual TXString		VCOM_CALLTYPE	GetDisplayNameOfRecordFormat(const TXString& formatName) = 0;
			virtual TXString		VCOM_CALLTYPE	GetFieldDisplayString(const TXString& formatName, const TXString& fieldName) = 0;
			virtual bool			VCOM_CALLTYPE	AlertRecordNoMerge(const TXString& formatName) = 0;

			// VW2022
			virtual TXString		VCOM_CALLTYPE	GetLatestIssueDate(MCObjectHandle hTitleBlock) = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<ITitleBlockDataProvider>	ITitleBlockDataProviderPtr;

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IUpdateTitleBlock : public IVWUnknown
		{
		public:
			virtual void			VCOM_CALLTYPE	UpdateTitleBlock() = 0;
			virtual	void			VCOM_CALLTYPE	CheckForDiffTypesTBAndUpdate() = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<IUpdateTitleBlock>	IUpdateTitleBlockPtr;

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ILocusSupport : public IVWUnknown
		{
		public:
			virtual TXString	VCOM_CALLTYPE GetTitleOverride(bool plural) = 0;
			virtual void		VCOM_CALLTYPE GetLinkPromptString(TXString& outSeparatorStr, TXString& outPointTypePopupStr) = 0;
			virtual void		VCOM_CALLTYPE GetPointTypePopupString(TXString& outNonePopupStr, TXString& outBoundingPointPopupStr, TXString& outNorthPointPopupStr) = 0;
			virtual bool		VCOM_CALLTYPE IsSupported(MCObjectHandle hLocusObj) = 0;
			virtual bool		VCOM_CALLTYPE GetIsBoundingBoxPoint(MCObjectHandle hLocusObj) = 0;
			virtual void		VCOM_CALLTYPE SetIsBoundingBoxPoint(MCObjectHandle hLocusObj, bool value) = 0;
			virtual bool		VCOM_CALLTYPE GetIsNorthPoint(MCObjectHandle hLocusObj) = 0;
			virtual void		VCOM_CALLTYPE SetIsNorthPoint(MCObjectHandle hLocusObj, bool value) = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<ILocusSupport>	ILocusSupportPtr;
	}
}