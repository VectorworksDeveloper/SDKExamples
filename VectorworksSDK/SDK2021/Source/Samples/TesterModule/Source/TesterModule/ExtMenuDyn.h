#pragma once


namespace TesterModule
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CExtMenuDyn;

	// ------------------------------------------------------------------------------------------------------
	class CMenuDyn_EventSink : public VWMenu_EventSink
	{
	public:
							CMenuDyn_EventSink(IVWUnknown* parent);
		virtual				~CMenuDyn_EventSink();

	public:
		virtual void		OnDynamicVariableChunkUpdate();
		virtual void		DoInterface();

	private:
		CExtMenuDyn*		fpParent;
	};

	// ------------------------------------------------------------------------------------------------------
	class CExtMenuDyn : public VWExtensionMenu
	{
		DEFINE_VWMenuExtension;
	public:
										CExtMenuDyn(CallBackPtr cbp);
		virtual							~CExtMenuDyn();

	public:
		void		AddMenu(const TXString& newMenu);

	};
}
