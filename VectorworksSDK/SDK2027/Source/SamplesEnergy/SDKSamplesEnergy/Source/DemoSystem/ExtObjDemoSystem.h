#pragma once


namespace DemoSystem
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjDemoSystem_EventSink : public VWParametric_EventSink
	{
	public:
					CObjDemoSystem_EventSink(IVWUnknown* parent);
		virtual		~CObjDemoSystem_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
		virtual EObjectEvent	Preference();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjDemoSystem : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
					CExtObjDemoSystem(CallBackPtr cbp);
		virtual		~CExtObjDemoSystem();

	public:
		virtual void		DefineSinks();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjDemoSystem
	class CExtObjDemoSystemDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
						CExtObjDemoSystemDefTool(CallBackPtr cbp);
		virtual			~CExtObjDemoSystemDefTool();

	};
}
