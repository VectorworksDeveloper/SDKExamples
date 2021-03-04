//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

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
		virtual TXString	GetOverrideHelpID() const;
		virtual void		DoInterface();
	};

	// ------------------------------------------------------------------------------------------------------
	class CExtMenu : public VWExtensionMenu
	{
		DEFINE_VWMenuExtension;
	public:
							CExtMenu(CallBackPtr cbp);
		virtual				~CExtMenu();

	};
}