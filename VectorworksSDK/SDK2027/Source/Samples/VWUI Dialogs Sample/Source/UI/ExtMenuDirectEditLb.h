#pragma once

namespace UI
{
	using namespace VWFC::PluginSupport;
	//using namespace DirectEditListBrowser;

	// ------------------------------------------------------------------------------------------------------
	class CMenuDirectEditLb_EventSink : public VWMenu_EventSink
	{
	public:
							CMenuDirectEditLb_EventSink(IVWUnknown* parent);
		virtual				~CMenuDirectEditLb_EventSink();

	public:
		virtual void		DoInterface();
	};

	// ------------------------------------------------------------------------------------------------------
	class CExtMenuDirectEditLb : public VWExtensionMenu
	{
		DEFINE_VWMenuExtension;
	public:
										CExtMenuDirectEditLb(CallBackPtr cbp);
		virtual							~CExtMenuDirectEditLb();

	};
}