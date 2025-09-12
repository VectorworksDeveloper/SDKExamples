#pragma once


namespace CustomDefaultTools
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjTheRect_EventSink : public VWParametric_EventSink
	{
	public:
					CObjTheRect_EventSink(IVWUnknown* parent);
		virtual		~CObjTheRect_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjTheRect : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObjTheRect(CallBackPtr cbp);
		virtual							~CExtObjTheRect();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjTheRect
	class CExtObjTheRectDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtObjTheRectDefTool(CallBackPtr cbp);
		virtual							~CExtObjTheRectDefTool();

	};

	// ------------------------------------------------------------------------------------------------------
	// default tool event skink
	class CExtObjTheRectDefTool_EventSink : public VWToolDefaultRect_EventSink
	{
	public:
										CExtObjTheRectDefTool_EventSink(IVWUnknown* parent);
		virtual							~CExtObjTheRectDefTool_EventSink();

		virtual void					Init(const TXString& universalName);

	public:
		// When tool is selected or resumed
		virtual bool			DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider);
	};
}
