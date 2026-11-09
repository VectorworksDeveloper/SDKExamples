#pragma once

namespace TesterModule
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CTool_EventSink : public VWTool_EventSink
	{
	public:
							CTool_EventSink(IVWUnknown* parent);
		virtual				~CTool_EventSink();

	public:
		virtual bool			DoSetUp(bool bRestore, const IToolModeBarInitProvider* pModeBarInitProvider);
		virtual void			DoSetDown(bool bRestore, const IToolModeBarInitProvider* pModeBarInitProvider);
		virtual void			MouseMove();
		virtual void			HandleComplete();

	protected:
		void			ClearAllToolInteractiveObjects();
		void			UpdateToolInteractiveObjects();
	};

	// ------------------------------------------------------------------------------------------------------
	class CExtTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtTool(CallBackPtr cbp);
		virtual							~CExtTool();

	};
}
