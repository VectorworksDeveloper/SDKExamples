#pragma once

namespace TesterModule
{
	using namespace VectorWorks::Extension;

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE CProviderShapePane : public VCOMImpl<IProviderShapePane>
	{
	public:
						CProviderShapePane(IVWUnknown* parent);
		virtual			~CProviderShapePane();

	// IProviderShapePane
	public:
		virtual void VCOM_CALLTYPE		Init(CodeRefID objectID, IExtendedProps* extProps);
		virtual void VCOM_CALLTYPE		Activate(MCObjectHandle hObject, const SSelectionContext& selContext);
		virtual void VCOM_CALLTYPE		Deactivate();
		virtual void VCOM_CALLTYPE		Update(IWidgetsProvider* widgetProvider);
		virtual bool VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk);
	};
}
