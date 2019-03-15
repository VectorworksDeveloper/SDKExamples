#pragma once

namespace TesterModule
{
	using namespace VWFC::PluginSupport;

	//-------------------------------------------------------------------------------
	class CExtMenuWebBrowser;

	//-------------------------------------------------------------------------------
	class CMenuWebBrowser_EventSink : public VWMenu_EventSink
	{
	public:
							CMenuWebBrowser_EventSink( IVWUnknown* parent );
		virtual				~CMenuWebBrowser_EventSink();

	public:
		virtual void		DoInterface();
	};

	//-------------------------------------------------------------------------------
	class CExtMenuWebBrowser : public VWExtensionMenu
	{
		DEFINE_VWMenuExtension;
	public:
							CExtMenuWebBrowser( CallBackPtr cbp );
		virtual				~CExtMenuWebBrowser();

	};

}