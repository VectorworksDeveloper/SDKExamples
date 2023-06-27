//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace DemoSpace
{
	using namespace VectorWorks::Extension;
	using namespace VectorWorks::EnergyAnalysis;

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE CExtObjSpacesEnergy_ShapePane : public VCOMImpl<IProviderShapePane>
	{
	public:
						CExtObjSpacesEnergy_ShapePane(IVWUnknown* parent);
		virtual			~CExtObjSpacesEnergy_ShapePane();
	
	// IProviderShapePane
	public:
		virtual void VCOM_CALLTYPE		Init(CodeRefID objectID, IExtendedProps* extProps);
		virtual void VCOM_CALLTYPE		Activate(MCObjectHandle hObject, const SSelectionContext& selContext);
		virtual void VCOM_CALLTYPE		Deactivate();
		virtual void VCOM_CALLTYPE		Update(IWidgetsProvider* widgetProvider);
		virtual bool VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk);
		virtual bool VCOM_CALLTYPE		TransferValue(SShapePaneWidgetTransferValue& data);

	private:
		MCObjectHandle		fhObject;
		SSelectionContext	fSelectionContext;

		IEnergySpacePtr		fEnergyData;
		IEnergyUnitsPtr		fEnergyUnits;
	};
}
