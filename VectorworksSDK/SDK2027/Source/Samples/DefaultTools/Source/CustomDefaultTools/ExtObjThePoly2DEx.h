#pragma once


namespace CustomDefaultTools
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjThePoly2D_EventSink : public VWParametric_EventSink
	{
	public:
					CObjThePoly2D_EventSink(IVWUnknown* parent);
		virtual		~CObjThePoly2D_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjThePoly2D : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObjThePoly2D(CallBackPtr cbp);
		virtual							~CExtObjThePoly2D();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjThePoly2D
	class CExtObjThePoly2DDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtObjThePoly2DDefTool(CallBackPtr cbp);
		virtual							~CExtObjThePoly2DDefTool();

	};

	// ------------------------------------------------------------------------------------------------------
	// default tool event skink
	class CExtObjThePoly2DDefTool_EventSink : public VWToolDefault2DPoly_EventSink
	{
	public:
										CExtObjThePoly2DDefTool_EventSink(IVWUnknown* parent);
		virtual							~CExtObjThePoly2DDefTool_EventSink();

		virtual void					Init(const TXString& universalName);

	public:
		// When tool is selected or resumed
		virtual bool			DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider);

		// When mouse is clicked in mode bar
		virtual void			DoModeEvent(size_t modeGroupID, size_t newButtonID, size_t oldButtonID);

		virtual void			HandleComplete();

	private:
		size_t		fBarState[ 20 ];
	};
}
