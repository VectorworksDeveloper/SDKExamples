#pragma once


namespace CustomDefaultTools
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjTheLine_EventSink : public VWParametric_EventSink
	{
	public:
					CObjTheLine_EventSink(IVWUnknown* parent);
		virtual		~CObjTheLine_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjTheLine : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObjTheLine(CallBackPtr cbp);
		virtual							~CExtObjTheLine();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjTheLine
	class CExtObjTheLineDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtObjTheLineDefTool(CallBackPtr cbp);
		virtual							~CExtObjTheLineDefTool();

	};

	// ------------------------------------------------------------------------------------------------------
	// default tool event skink
	class CExtObjTheLineDefTool_EventSink : public VWToolDefaultLine_EventSink
	{
	public:
										CExtObjTheLineDefTool_EventSink(IVWUnknown* parent);
		virtual							~CExtObjTheLineDefTool_EventSink();

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
