#pragma once

namespace CollectResourceInfo
{
	using namespace VWFC::PluginSupport;

	// ---------------------------------------------------------------------------------------------------
	class CExtMenuCollectResourceInfo_EventSink : public VWMenu_EventSink
	{
	public:
		CExtMenuCollectResourceInfo_EventSink(IVWUnknown* parent);
		virtual								~CExtMenuCollectResourceInfo_EventSink();

		virtual void						DoInterface();

	private:
	};

	// ---------------------------------------------------------------------------------------------------
	class CExtMenuCollectResourceInfo : public VWExtensionMenu
	{
		DEFINE_VWMenuExtension;
	public:
		CExtMenuCollectResourceInfo(CallBackPtr cbp);
		virtual							~CExtMenuCollectResourceInfo();

	};
}