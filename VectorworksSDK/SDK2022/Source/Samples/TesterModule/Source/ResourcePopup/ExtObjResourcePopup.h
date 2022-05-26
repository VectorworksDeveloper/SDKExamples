//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


namespace ResourcePopup
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjResourcePopup_EventSink : public VWParametric_EventSink
	{
	public:
					CObjResourcePopup_EventSink(IVWUnknown* parent);
		virtual		~CObjResourcePopup_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjResourcePopup : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
					CExtObjResourcePopup(CallBackPtr cbp);
		virtual		~CExtObjResourcePopup();

	public:
		virtual void		DefineSinks();
	};
}
