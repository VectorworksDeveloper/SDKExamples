//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


namespace DemoWindow
{
	using namespace VectorWorks::Extension;

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE CExtObjDemoWindow_ShapePane : public VCOMImpl<IProviderShapePane>
	{
	public:
						CExtObjDemoWindow_ShapePane(IVWUnknown* parent);
		virtual			~CExtObjDemoWindow_ShapePane();
	
	// IProviderShapePane
	public:
		virtual void VCOM_CALLTYPE		Init(CodeRefID objectID, IExtendedProps* extProps);
		virtual void VCOM_CALLTYPE		Activate(MCObjectHandle hObject, const SSelectionContext& selContext);
		virtual void VCOM_CALLTYPE		Deactivate();
		virtual void VCOM_CALLTYPE		Update(IWidgetsProvider* widgetProvider);
		virtual bool VCOM_CALLTYPE		OnWidgetChange(SShapePaneWidgetOnWidgetChange& data, bool& outNeedReset, bool& outChangeOk);
		virtual bool VCOM_CALLTYPE		TransferValue(SShapePaneWidgetTransferValue& data);

	protected:
		bool							OnSettingsButton();
		bool							OnIncludeToEACalc(bool value);
		bool							OnUValueManual(const TXString& value);
		bool							OnTilting(bool value);
		bool							OnTypeChange(Sint32 value);

	private:
		MCObjectHandle		fhObject;
		SSelectionContext	fSelectionContext;

		VectorWorks::EnergyAnalysis::IEnergyBuildingElementWinDoorPtr	fEAWinDoor;
		VectorWorks::EnergyAnalysis::IEnergyUnitsPtr					fEAUnits;
	};
}

