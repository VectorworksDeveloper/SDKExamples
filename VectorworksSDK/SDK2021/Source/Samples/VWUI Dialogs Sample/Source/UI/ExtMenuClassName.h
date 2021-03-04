#pragma once


namespace UI
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CMenuClassName_EventSink : public VWMenu_EventSink
	{
	public:
							CMenuClassName_EventSink(IVWUnknown* parent);
		virtual				~CMenuClassName_EventSink();

	public:
		virtual TXString	GetOverrideHelpID() const;
		virtual void		DoInterface();
	};

	// ------------------------------------------------------------------------------------------------------
	class CExtMenuClassName : public VWExtensionMenu
	{
		DEFINE_VWMenuExtension;
	public:
										CExtMenuClassName(CallBackPtr cbp);
		virtual							~CExtMenuClassName();

	};
}
