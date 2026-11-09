#pragma once

namespace TesterModule
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CMenu_EventSink : public VWMenu_EventSink
	{
	public:
							CMenu_EventSink(IVWUnknown* parent);
		virtual				~CMenu_EventSink();

	public:
		virtual void		DoInterface();
	};

	// ------------------------------------------------------------------------------------------------------
	class CExtMenu : public VWExtensionMenu
	{
		DEFINE_VWMenuExtension;
	public:
										CExtMenu(CallBackPtr cbp);
		virtual							~CExtMenu();

	};
}