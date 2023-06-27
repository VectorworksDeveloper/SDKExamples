#pragma once


namespace TesterModule
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjClassName_EventSink : public VWParametric_EventSink
	{
	public:
					CObjClassName_EventSink(IVWUnknown* parent);
		virtual		~CObjClassName_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	// 
	class CExtObjClassName : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObjClassName(CallBackPtr cbp);
		virtual							~CExtObjClassName();

	// IExtensionApp
	public:
		virtual void	DefineSinks();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjClassName
	class CExtObjClassNameDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtObjClassNameDefTool(CallBackPtr cbp);
		virtual							~CExtObjClassNameDefTool();

	};
}