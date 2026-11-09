//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace DemoSpace
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjDemoSpace_EventSink : public VWParametric_EventSink
	{
	public:
					CObjDemoSpace_EventSink(IVWUnknown* parent);
		virtual		~CObjDemoSpace_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
		virtual EObjectEvent	Preference();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjDemoSpace : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
					CExtObjDemoSpace(CallBackPtr cbp);
		virtual		~CExtObjDemoSpace();

	public:
		virtual void		DefineSinks();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjSpacesEnergy
	class CExtObjDemoSpaceDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
						CExtObjDemoSpaceDefTool(CallBackPtr cbp);
		virtual			~CExtObjDemoSpaceDefTool();

	};
}
