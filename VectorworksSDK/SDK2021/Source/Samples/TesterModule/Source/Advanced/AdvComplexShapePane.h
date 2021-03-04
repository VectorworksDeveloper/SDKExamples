#pragma once

namespace Advanced
{
	using namespace VectorWorks::Extension;

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE CAdvComplexShapePane : public VCOMImpl<IProviderShapePane>
	{
	public:
						CAdvComplexShapePane(IVWUnknown* parent);
		virtual			~CAdvComplexShapePane();

	// IProviderShapePane
	public:
		virtual void VCOM_CALLTYPE		Init(CodeRefID objectID, IExtendedProps* extProps);
		virtual void VCOM_CALLTYPE		Activate(MCObjectHandle hObject, const SSelectionContext& selContext);
		virtual void VCOM_CALLTYPE		Deactivate();
		virtual void VCOM_CALLTYPE		Update(IWidgetsProvider* widgetProvider);
	};
}
