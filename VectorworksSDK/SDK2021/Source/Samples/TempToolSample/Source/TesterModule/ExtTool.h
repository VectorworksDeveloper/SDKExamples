//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace TesterModule
{
	using namespace VWFC::PluginSupport;

	// ------------------------------------------------------------------------------------------------------
	class CTool_EventSink : public VWToolDefaultLine_EventSink
	{
	public:
							CTool_EventSink(IVWUnknown* parent);
		virtual				~CTool_EventSink();

	public:
		// When tool is selected or resumed.
		virtual bool		DoSetUp(bool bRestore, const IToolModeBarInitProvider* modeBarInitProvider);
		// When tool is done getting points.
		virtual void		HandleComplete();

	private:
		VWRecordFormatObj	fToolRecFormat;
		bool				fDoStretch;
	};

	// ------------------------------------------------------------------------------------------------------
	class CExtTool : public VWExtensionTool
	{
		DEFINE_VWToolExtension;
	public:
							CExtTool(CallBackPtr cbp);
		virtual				~CExtTool();

	};
}
