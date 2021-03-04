#pragma once


namespace Updater
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjUpdater_EventSink : public VWParametric_EventSink
	{
	public:
					CObjUpdater_EventSink(IVWUnknown* parent);
		virtual		~CObjUpdater_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjUpdater : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObjUpdater(CallBackPtr cbp);
		virtual							~CExtObjUpdater();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjUpdater
	class CExtObjUpdaterDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtObjUpdaterDefTool(CallBackPtr cbp);
		virtual							~CExtObjUpdaterDefTool();

	};
}
