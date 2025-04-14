#pragma once

#include "../Data/DataWeb.h"

namespace Extensions
{
	using namespace VWFC::PluginSupport;
	using namespace Data;

	// ------------------------------------------------------------------------------------------------------
	class CMenuDownload_EventSink : public VWMenu_EventSink
	{
	public:
							CMenuDownload_EventSink(IVWUnknown* parent);
		virtual				~CMenuDownload_EventSink();

	public:
		virtual void		DoInterface();

	private:
		CWebContext		fWebContext;
	};

	// ------------------------------------------------------------------------------------------------------
	class CMenuDownload : public VWExtensionMenu
	{
		DEFINE_VWMenuExtension;
	public:
										CMenuDownload(CallBackPtr cbp);
		virtual							~CMenuDownload();

	};
}