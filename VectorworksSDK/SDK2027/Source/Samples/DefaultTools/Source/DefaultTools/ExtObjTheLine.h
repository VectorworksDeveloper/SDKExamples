#pragma once

// This sample demonstrates use the a linear default tool to create linear parametric object
namespace DefaultTools
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjTheLine_EventSink : public VWParametric_EventSink
	{
	public:
					CObjTheLine_EventSink(IVWUnknown* parent);
		virtual		~CObjTheLine_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjTheLine : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObjTheLine(CallBackPtr cbp);
		virtual							~CExtObjTheLine();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjTheLine
	class CExtObjTheLineDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtObjTheLineDefTool(CallBackPtr cbp);
		virtual							~CExtObjTheLineDefTool();

	};

	// ------------------------------------------------------------------------------------------------------
	// default tool event skink
	class CExtObjTheLineDefTool_EventSink : public VWToolDefaultLine_EventSink
	{
	public:
										CExtObjTheLineDefTool_EventSink(IVWUnknown* parent);
		virtual							~CExtObjTheLineDefTool_EventSink();
	};
}
