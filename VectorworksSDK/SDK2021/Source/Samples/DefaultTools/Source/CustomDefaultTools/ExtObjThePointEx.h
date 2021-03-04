#pragma once


namespace CustomDefaultTools
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjThePoint_EventSink : public VWParametric_EventSink
	{
	public:
					CObjThePoint_EventSink(IVWUnknown* parent);
		virtual		~CObjThePoint_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjThePoint : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObjThePoint(CallBackPtr cbp);
		virtual							~CExtObjThePoint();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjThePoint
	class CExtObjThePointDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtObjThePointDefTool(CallBackPtr cbp);
		virtual							~CExtObjThePointDefTool();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool event skink
	class CExtObjThePointDefTool_EventSink : public VWToolDefaultPoint_EventSink
	{
	public:
										CExtObjThePointDefTool_EventSink(IVWUnknown* parent);
		virtual							~CExtObjThePointDefTool_EventSink();

		virtual void					Init(const TXString& universalName);

	public:
		// When tool is selected or resumed
		virtual bool			DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider);
		
		// When mouse is clicked in mode bar
		virtual void			DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID);

	private:
		size_t		fBarState[ 20 ];
	};
}
