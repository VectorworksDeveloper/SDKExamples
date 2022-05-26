#pragma once

#include "UI/DlgSysObjEditParam.h"

namespace DemoSystem
{
	using namespace VectorWorks::Extension;

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE CExtObjDemoSystem_ShapePane : public VCOMImpl<IProviderShapePane>
	{
	public:
						CExtObjDemoSystem_ShapePane(IVWUnknown* parent);
		virtual			~CExtObjDemoSystem_ShapePane();
	
	// IProviderShapePane
	public:
		virtual void VCOM_CALLTYPE		Init(CodeRefID objectID, IExtendedProps* extProps);
		virtual void VCOM_CALLTYPE		Activate(MCObjectHandle hObject, const SSelectionContext& selContext);
		virtual void VCOM_CALLTYPE		Deactivate();
		virtual void VCOM_CALLTYPE		Update(IWidgetsProvider* widgetProvider);
		virtual bool VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk);
		virtual bool VCOM_CALLTYPE		TransferValue(SShapePaneWidgetTransferValue& data);

	protected:
		bool							OnEditParamButton();
		bool							OnParamNamePopup(const TXString& selParamName, IWidgetDataPopup* paramNameData);

		void							FillParamNamePopup(SShapePaneWidgetTransferValue& data);

	private:
		MCObjectHandle		fhObject;
		UI::SParamInfo		fParamInfo;
		SSelectionContext	fSelContext;
		TXString			fSystemName;

		VectorWorks::EnergyAnalysis::IEnergySystemObjectPtr	fEASystem;
	};
}

