#pragma once


namespace TesterModule
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObj_EventSink : public VWParametric_EventSink
	{
	public:
					CObj_EventSink(IVWUnknown* parent);
		virtual		~CObj_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObj : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObj(CallBackPtr cbp);
		virtual							~CExtObj();
	};

}