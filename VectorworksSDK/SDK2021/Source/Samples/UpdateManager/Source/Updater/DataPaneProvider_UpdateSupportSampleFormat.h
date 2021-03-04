#pragma once


namespace Updater
{
	// {77B16EFC-9779-43DF-AA0D-453A344EF9F0}
	const VWIID IID_DataPaneProvider_UpdateSupportSampleFormat = { 0x77b16efc, 0x9779, 0x43df, { 0xaa, 0xd, 0x45, 0x3a, 0x34, 0x4e, 0xf9, 0xf0 } };

	using namespace VectorWorks::Extension;

	class CDataPaneProvider_UpdateSupportSampleFormat : public VCOMImpl<IProviderDataPane>
	{
	public:
						CDataPaneProvider_UpdateSupportSampleFormat(CallBackPtr);
		virtual			~CDataPaneProvider_UpdateSupportSampleFormat();

	// IProviderDataPane
	public:
		virtual void VCOM_CALLTYPE		Init(const TXString& recordFormatName, IExtendedProps* extProps);
		virtual void VCOM_CALLTYPE		Activate(MCObjectHandle hObject, MCObjectHandle hRecord, const SSelectionContext& selContext);
		virtual void VCOM_CALLTYPE		Deactivate();
		virtual void VCOM_CALLTYPE		Update(IWidgetsProvider* widgetProvider);
		virtual bool VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk);
		virtual bool VCOM_CALLTYPE		TransferValue(SShapePaneWidgetTransferValue& data);

	private:
		MCObjectHandle	fhObject;
		MCObjectHandle	fhRecord;

		IWidgetsProvider*	fWidgetsProvider;

		bool		fUpdateCustomPopup;
	};
}
