//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


namespace DemoWindow
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjDemoWindow_EventSink : public VWParametric_EventSink
	{
	public:
					CObjDemoWindow_EventSink(IVWUnknown* parent);
		virtual		~CObjDemoWindow_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
		virtual EObjectEvent	Preference();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjDemoWindow : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
					CExtObjDemoWindow(CallBackPtr cbp);
		virtual		~CExtObjDemoWindow();

	public:
		virtual void		DefineSinks();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjDemoWindow
	class CExtObjDemoWindowDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
						CExtObjDemoWindowDefTool(CallBackPtr cbp);
		virtual			~CExtObjDemoWindowDefTool();

	};
}
