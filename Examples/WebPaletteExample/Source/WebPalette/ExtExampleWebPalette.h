#pragma once


namespace WebPalette
{
	using namespace VectorWorks::Extension;
	using namespace VWFC::PluginSupport;

	// --------------------------------------------------------------------------------------------------------
	class CPaletteJSProvider : public VCOMImmediateImpl<IWebJavaScriptProvider>
	{
	public:
		CPaletteJSProvider();
		virtual ~CPaletteJSProvider();

		virtual void OnInit(IInitContext* context);

		virtual void		OnFunction(const TXString& name, const std::vector<VWVariant>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);

	private:
		void			UpdateLocalizedJSON();
		VWVariant		OnGetLocalStringsInner();
		VWVariant		OnGetAllPlantStyles();
		VWVariant		OnGetAllPlantData();
		void			OnUpdatePlantAssociations(const std::vector<VWVariant>& args);

	private:
		IWebPaletteFrame*	fWebFrame;
		TXString			fLocalizedJSON;
	};

	// --------------------------------------------------------------------------------------------------------
	// {1F64C562-D45E-4B5D-8587-A99A31FE3B2F}
	static const VWIID IID_UpdateSupport = { 0x1f64c562, 0xd45e, 0x4b5d, { 0x85, 0x87, 0xa9, 0x9a, 0x31, 0xfe, 0x3b, 0x2f } };

	// --------------------------------------------------------------------------------------------------------
	class CUpdateSupport : public VCOMImmediateImpl<IObjUpdateSupport>
	{
	public:
				CUpdateSupport(CallBackPtr);
		virtual ~CUpdateSupport();

	public:
		virtual void VCOM_CALLTYPE	Init(IObjUpdateSupportContext* context);
		virtual void VCOM_CALLTYPE	OnNotification(IObjUpdateSupportContext* context);
	};

	// --------------------------------------------------------------------------------------------------------
	class CExtWebPaletteExample : public VCOMImmediateImpl<IExtensionWebPalette>
	{
		DEFINE_VWPaletteExtension;
	public:
		CExtWebPaletteExample(CallBackPtr);
		virtual ~CExtWebPaletteExample();

		virtual IEventSink* VCOM_CALLTYPE	QueryEventSink(const TSinkIID& iid);

		virtual TXString	VCOM_CALLTYPE GetTitle();
		virtual bool		VCOM_CALLTYPE GetInitialSize(ViewCoord& outCX, ViewCoord& outCY);
		virtual TXString	VCOM_CALLTYPE GetInitialURL();

	private:
		CPaletteJSProvider			fJSProvider;
	};
}

