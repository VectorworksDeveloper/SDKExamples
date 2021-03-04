//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IEnergyUnits.h"
#include "IExternalSystemData.h"

namespace VectorWorks
{
	namespace EnergyAnalysis
	{
		enum class EValueType
		{
			Window,
			Door,
			HybridWindow,
			HybridDoor,
		};

		// ----------------------------------------------------------------------------------------------------
		// {11AA3330-35A7-4787-8E46-FA2EB29409D5}
		static const VWIID IID_EnergyBuildingElementWinDoor = { 0x11aa3330, 0x35a7, 0x4787, { 0x8e, 0x46, 0xfa, 0x2e, 0xb2, 0x94, 0x9, 0xd5 } };

		class DYNAMIC_ATTRIBUTE IEnergyBuildingElementWinDoor : public IVWUnknown
		{
		public:
			// tools
			// This function will return true, if the handle has a property energy data.
			virtual bool    VCOM_CALLTYPE IsHandleContainingData(MCObjectHandle h) = 0;
			// This function will delete the energy data from the handle.
			virtual void    VCOM_CALLTYPE DeleteDataFromHandle(MCObjectHandle h) = 0;

		public:
			virtual MCObjectHandle		VCOM_CALLTYPE Get() = 0;

			//This function will load energy data from the handle, if it has data,
			//or this function will load default energy data, if the handle does not have energy data.
			virtual void				VCOM_CALLTYPE LoadCreate(MCObjectHandle h) = 0;

			virtual bool				VCOM_CALLTYPE Save() = 0;	// Must be called after Set operations

			virtual void				VCOM_CALLTYPE CopyDataTo(MCObjectHandle h) = 0;
			virtual void				VCOM_CALLTYPE CopyInterfaceDataFrom(IEnergyBuildingElementWinDoor* interfaceData) = 0;

			virtual EWinDoorType		VCOM_CALLTYPE GetType() = 0;
			virtual void				VCOM_CALLTYPE SetType(EWinDoorType type) = 0;

			virtual bool				VCOM_CALLTYPE GetIsModified() = 0;
			virtual void				VCOM_CALLTYPE SetIsModified(bool value) = 0;

			virtual bool				VCOM_CALLTYPE GetSupportEdit() = 0;
			virtual void				VCOM_CALLTYPE SetSupportEdit(bool value) = 0;

			virtual TXString			VCOM_CALLTYPE GetName(bool useOriginal) = 0;
			virtual void				VCOM_CALLTYPE SetName(const TXString & value, bool toOriginal) = 0;

			virtual double				VCOM_CALLTYPE GetArea(bool useOriginal) = 0;				// sq m
			virtual void				VCOM_CALLTYPE SetArea(double value, bool toOriginal) = 0;	// sq m

			virtual double				VCOM_CALLTYPE GetWidth() = 0;						// m
			virtual void				VCOM_CALLTYPE SetWidth(double value) = 0;			// m

			virtual double				VCOM_CALLTYPE GetGlazingArea() = 0;					// sq m
			virtual void				VCOM_CALLTYPE SetGlazingArea(double value, EValueType valueType = EValueType::Window) = 0;		// sq m

			virtual double				VCOM_CALLTYPE GetGlazingLength() = 0;				// m
			virtual void				VCOM_CALLTYPE SetGlazingLength(double value, EValueType valueType = EValueType::Window) = 0;	// m

			virtual double				VCOM_CALLTYPE GetFrameArea() = 0;					// sq m
			virtual void				VCOM_CALLTYPE SetFrameArea(double value, EValueType valueType = EValueType::Window) = 0;		// sq m

			virtual double				VCOM_CALLTYPE GetFrameLength() = 0;					// m
			virtual void				VCOM_CALLTYPE SetFrameLength(double value, EValueType valueType = EValueType::Window) = 0;		// m

			virtual TXString			VCOM_CALLTYPE GetAreaAdjustment(bool useOriginal) = 0;
			virtual void				VCOM_CALLTYPE SetAreaAdjustment(const TXString & value, bool toOriginal) = 0;

			virtual size_t				VCOM_CALLTYPE GetSortIndex() = 0;
			virtual void				VCOM_CALLTYPE SetSortIndex(size_t value) = 0;

			virtual bool				VCOM_CALLTYPE GetIncludeInEnergyAnalysis() = 0;
			virtual void				VCOM_CALLTYPE SetIncludeInEnergyAnalysis(bool value) = 0;

			virtual ECalculationMode	VCOM_CALLTYPE GetUValueCalculationMode() = 0;
			virtual void				VCOM_CALLTYPE SetUValueCalculationMode(ECalculationMode value) = 0;

			virtual double				VCOM_CALLTYPE GetUValue(bool useOriginal) = 0;				// W/(m^2 K)
			virtual void				VCOM_CALLTYPE SetUValue(double value, bool toOriginal) = 0;	// W/(m^2 K)
			virtual double				VCOM_CALLTYPE GetUValueAutoCalculated() = 0;				// W/(m^2 K)

			virtual double				VCOM_CALLTYPE GetLightTransmissionGlazing() = 0;					// %
			virtual void				VCOM_CALLTYPE SetLightTransmissionGlazing(double value) = 0;		// %

			virtual IExternalSystemDataPtr	VCOM_CALLTYPE GetFrame() = 0;
			virtual void					VCOM_CALLTYPE CopyFrame(IExternalSystemDataPtr frame) = 0;
			virtual IExternalSystemDataPtr	VCOM_CALLTYPE GetGlazing() = 0;
			virtual void					VCOM_CALLTYPE CopyGlazing(IExternalSystemDataPtr glazing) = 0;
			virtual IExternalSystemDataPtr	VCOM_CALLTYPE GetDoorType() = 0;
			virtual void					VCOM_CALLTYPE CopyDoorType(IExternalSystemDataPtr doorType) = 0;

			virtual SShading			VCOM_CALLTYPE GetShadingGeneral() = 0;
			virtual void				VCOM_CALLTYPE SetShadingGeneral(const SShading& value) = 0;
			virtual SShading			VCOM_CALLTYPE GetShadingSurrounding() = 0;
			virtual void				VCOM_CALLTYPE SetShadingSurrounding(const SShading& value) = 0;
			virtual SShading			VCOM_CALLTYPE GetShadingSummer() = 0;
			virtual void				VCOM_CALLTYPE SetShadingSummer(const SShading& value) = 0;
			virtual SAdditionalShading	VCOM_CALLTYPE GetShadingAdditional() = 0;
			virtual void				VCOM_CALLTYPE SetShadingAdditional(const SAdditionalShading& value) = 0;

			virtual void				VCOM_CALLTYPE GetSummerVentilation(EWinDoorSummerVentilationType type, SWinDoorSummerVentilationData& outData) = 0;
			virtual void				VCOM_CALLTYPE SetSummerVentilation(EWinDoorSummerVentilationType type, const SWinDoorSummerVentilationData& data) = 0;

			virtual void				VCOM_CALLTYPE SetIsDoorTypeUsed(bool value) = 0;

			// Window/Door settings dialog support
			virtual void				VCOM_CALLTYPE DialogUI_Fill_ShadingGeneral(short dialogID, short systemCtrlID) = 0;
			virtual void				VCOM_CALLTYPE DialogUI_Select_ShadingGeneral(short dialogID, short systemCtrlID) = 0;
			virtual void				VCOM_CALLTYPE DialogUI_Fill_ShadingSurrounding(short dialogID, short systemCtrlID) = 0;
			virtual void				VCOM_CALLTYPE DialogUI_Select_ShadingSurrounding(short dialogID, short systemCtrlID) = 0;
			virtual void				VCOM_CALLTYPE DialogUI_Fill_ShadingSummer(short dialogID, short systemCtrlID) = 0;
			virtual void				VCOM_CALLTYPE DialogUI_Select_ShadingSummer(short dialogID, short systemCtrlID) = 0;
			virtual void				VCOM_CALLTYPE DialogUI_Fill_ShadingAdditional(short dialogID, short systemCtrlID) = 0;
			virtual void				VCOM_CALLTYPE DialogUI_Select_ShadingAdditional(short dialogID, short systemCtrlID) = 0;
			virtual bool				VCOM_CALLTYPE DialogUI_EditAdvancedOptionsDlg() = 0;

			// Window/Door widgets support
			virtual void				VCOM_CALLTYPE WidgetUI_Fill_UValueCalculation(VectorWorks::Extension::SShapePaneWidgetTransferValue& data) = 0;
			virtual void				VCOM_CALLTYPE WidgetUI_Select_UValueCalculation(VectorWorks::Extension::SShapePaneWidgetOnWidgetChange& data) = 0;
			virtual void				VCOM_CALLTYPE WidgetUI_Fill_ShadingGeneral(VectorWorks::Extension::SShapePaneWidgetTransferValue& data) = 0;
			virtual void				VCOM_CALLTYPE WidgetUI_Select_ShadingGeneral(VectorWorks::Extension::SShapePaneWidgetOnWidgetChange& data) = 0;
			virtual void				VCOM_CALLTYPE WidgetUI_Fill_ShadingSurrounding(VectorWorks::Extension::SShapePaneWidgetTransferValue& data) = 0;
			virtual void				VCOM_CALLTYPE WidgetUI_Select_ShadingSurrounding(VectorWorks::Extension::SShapePaneWidgetOnWidgetChange& data) = 0;
			virtual void				VCOM_CALLTYPE WidgetUI_Fill_ShadingSummer(VectorWorks::Extension::SShapePaneWidgetTransferValue& data) = 0;
			virtual void				VCOM_CALLTYPE WidgetUI_Select_ShadingSummer(VectorWorks::Extension::SShapePaneWidgetOnWidgetChange& data) = 0;
			virtual void				VCOM_CALLTYPE WidgetUI_Fill_ShadingAdditional(VectorWorks::Extension::SShapePaneWidgetTransferValue& data) = 0;
			virtual void				VCOM_CALLTYPE WidgetUI_Select_ShadingAdditional(VectorWorks::Extension::SShapePaneWidgetOnWidgetChange& data) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyBuildingElementWinDoor>		IEnergyBuildingElementWinDoorPtr;
	}
}
