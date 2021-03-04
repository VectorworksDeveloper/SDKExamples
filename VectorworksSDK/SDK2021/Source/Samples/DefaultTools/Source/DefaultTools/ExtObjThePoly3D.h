#pragma once


namespace DefaultTools
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CObjThePoly3D_EventSink : public VWParametric_EventSink
	{
	public:
					CObjThePoly3D_EventSink(IVWUnknown* parent);
		virtual		~CObjThePoly3D_EventSink();

	// Plug-in Object action/events constants 
	public:
		virtual EObjectEvent	OnInitXProperties(CodeRefID objectID);
		virtual EObjectEvent	Recalculate();
	};


	// ------------------------------------------------------------------------------------------------------
	class CExtObjThePoly3D : public VWExtensionParametric
	{
		DEFINE_VWParametricExtension;
	public:
										CExtObjThePoly3D(CallBackPtr cbp);
		virtual							~CExtObjThePoly3D();
	};

	// ------------------------------------------------------------------------------------------------------
	// default tool for ExtObjThePoly3D
	class CExtObjThePoly3DDefTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
										CExtObjThePoly3DDefTool(CallBackPtr cbp);
		virtual							~CExtObjThePoly3DDefTool();

	};

	// ------------------------------------------------------------------------------------------------------
	// default tool event skink
	class CExtObjThePoly3DDefTool_EventSink : public VWToolDefault3DPoly_EventSink
	{
	public:
										CExtObjThePoly3DDefTool_EventSink(IVWUnknown* parent);
		virtual							~CExtObjThePoly3DDefTool_EventSink();
	};
}
