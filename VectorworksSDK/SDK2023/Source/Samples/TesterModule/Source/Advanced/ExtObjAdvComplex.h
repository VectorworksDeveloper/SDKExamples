#pragma once


namespace Advanced
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjAdvComplex_EventSink : public VWParametric_EventSink
	{
	public:
					CObjAdvComplex_EventSink(IVWUnknown* parent);
		virtual		~CObjAdvComplex_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjAdvComplex : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObjAdvComplex(CallBackPtr cbp);
		virtual							~CExtObjAdvComplex();

	public:
		virtual void					DefineSinks();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjAdvComplex
	class CExtObjAdvComplexDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtObjAdvComplexDefTool(CallBackPtr cbp);
		virtual							~CExtObjAdvComplexDefTool();

	};
}
