#pragma once


namespace WebPalette
{
	using namespace VectorWorks::Extension;
	using namespace VWFC::PluginSupport;

	// --------------------------------------------------------------------------------------------------------
#if 0
	// Prior Vectorworks SDK 2025:
	//	- used VWVariant as argument type
	//
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
#else
	// After Vectorworks SDK 2025:
	//	use the built-in the SDK nlohmann::json library (https://github.com/nlohmann/json
	//  use SDK base class instead of interface that provides convenience functions and dispatch map
	//      note: it also provides the frame (IWebPaletteFrame*	fWebFrame)
	class CPaletteJSProvider : public VWExtensionPaletteJSProvider
	{
	public:
		CPaletteJSProvider(IVWUnknown* parent);
		virtual ~CPaletteJSProvider();

		virtual void OnInit(IInitContext* context);

		DEFINE_WebPalette_DISPATCH_MAP;

	private:
		void	OnGetAllPlantStyles(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);
		void	OnGetAllPlantData(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);
		void	OnUpdatePlantAssociations(const TXString& objName, const TXString& functionName, const std::vector<nlohmann::json>& args, VectorWorks::UI::IJSFunctionCallbackContext* context);

	private:
	};

#endif

	// --------------------------------------------------------------------------------------------------------
	// /*YOU MUST CHANGE THIS UUID if you copy this code*/	{1F64C562-D45E-4B5D-8587-A99A31FE3B2F}
	static const VWIID IID_UpdateSupport = /*YOU MUST CHANGE THIS UUID if you copy this code*/	{ 0x1f64c562, 0xd45e, 0x4b5d, { 0x85, 0x87, 0xa9, 0x9a, 0x31, 0xfe, 0x3b, 0x2f } };

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
#if 0
	// Prior Vectorworks SDK 2025:
	//
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
#else
	// After Vectorworks SDK 2025:
	//	- it will automatically load the page from the resources html/index.html
	//	  this can be overriden, see the constructors of VWExtensionWebPalette
	//	  also see the comment for the "VWFC::PluginSupport::GetStandardURL" function
	//
	class CExtWebPaletteExample : public VWExtensionWebPalette
	{
		DEFINE_VWPaletteExtension;
	public:
		CExtWebPaletteExample(CallBackPtr);
		virtual ~CExtWebPaletteExample();

		virtual void		DefineSinks() override;

		virtual TXString	GetTitle() override;
		virtual bool		GetInitialSize(ViewCoord& outCX, ViewCoord& outCY) override;
		virtual bool		GetMinimalSize(ViewCoord& outCX, ViewCoord& outCY) override;
	};
#endif
}

