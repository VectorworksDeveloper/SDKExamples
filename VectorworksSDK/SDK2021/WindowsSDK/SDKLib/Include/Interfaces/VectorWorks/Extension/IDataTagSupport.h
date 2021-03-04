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
		using TXStringSTLPairArray = std::vector<std::pair<TXString, TXString>>;

		// ---------------------------------------------------------------------------
		// {94FEF6A6-8F6E-4E84-88AD-F256FD537980}
		static const VWIID IID_DataTagSupport = { 0x94fef6a6, 0x8f6e, 0x4e84, { 0x88, 0xad, 0xf2, 0x56, 0xfd, 0x53, 0x79, 0x80 } };

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IDataTagSupport : public IVWSingletonUnknown
		{
		public:
			virtual void VCOM_CALLTYPE	UpdateDataTag(MCObjectHandle hDataTag, bool isForMoving = false, WorldPt3 offset = WorldPt3( 0.0, 0.0, 0.0 ), bool isDuplicated = false) = 0;

			virtual void VCOM_CALLTYPE	BeginMultipleMove() = 0;
			virtual void VCOM_CALLTYPE	EndMultipleMove() = 0;
			virtual bool VCOM_CALLTYPE	IsDataTagsMovingSuspended() = 0;

			// tagged object
			virtual bool VCOM_CALLTYPE	CanBeTaggedObject(MCObjectHandle hObj) = 0;

			// Use the function from core, if you can, because it is faster.
			virtual void VCOM_CALLTYPE	UpdateTagsOfTaggedObject(MCObjectHandle hObj) = 0;

			virtual bool VCOM_CALLTYPE	GetDataTagExtractedData(MCObjectHandle hDataTag, TXStringSTLPairArray& outArrExtractedData) = 0;

			// Gets the handles of all Data Tags attached to hObj
			virtual bool VCOM_CALLTYPE	GetAssociatedDataTags(MCObjectHandle hObj, TMCObjectHandlesSTLArray& outArrDataTags) = 0;

			virtual bool VCOM_CALLTYPE	AssociateWithObject(MCObjectHandle hDataTag, MCObjectHandle hAssociated) = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<IDataTagSupport>			IDataTagSupportPtr;

		// ---------------------------------------------------------------------------
		// {B78547E0-FB92-4C2A-AEAF-4FC86825281D}
		static const VWIID IID_DataTagTextLinkSupport = { 0xb78547e0, 0xfb92, 0x4c2a, { 0xae, 0xaf, 0x4f, 0xc8, 0x68, 0x25, 0x28, 0x1d } };

		// ---------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IDataTagTextLinkSupport : public IVWSingletonUnknown
		{
		public:
			virtual void		VCOM_CALLTYPE GetLinkPromptString(TXString& outSeparator, TXString& outCheckBox, TXString& outButton) = 0;
			virtual TXString	VCOM_CALLTYPE GetTitleOverride(bool isPlural) = 0;
			virtual bool		VCOM_CALLTYPE GetIsLinked(MCObjectHandle hTextObj) = 0;
			virtual void		VCOM_CALLTYPE SetIsLinked(MCObjectHandle hTextObj, bool value) = 0;
			virtual bool		VCOM_CALLTYPE IsSupported(MCObjectHandle hTextObj) = 0;
			virtual void		VCOM_CALLTYPE ShowDefineTagFieldDlg() = 0;
			virtual TXString	VCOM_CALLTYPE GetFormula(MCObjectHandle hTextObj) = 0;
			virtual void		VCOM_CALLTYPE SetFormula(MCObjectHandle hTextObj, const TXString& formula) = 0;
			virtual TXString	VCOM_CALLTYPE GetDefaultValue(MCObjectHandle hTextObj) = 0;
			virtual void		VCOM_CALLTYPE SetDefaultValue(MCObjectHandle hTextObj, const TXString& defaultValue) = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<IDataTagTextLinkSupport>	IDataTagTextLinkSupportPtr;
	}
}
