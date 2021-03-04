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
		typedef std::vector<size_t> TKeysArray;

		// ----------------------------------------------------------------------------------------------------
		struct SGlazingElement
		{
			IExternalSystemDataPtr	fGlazingSystem;
			double					fArea;						// sq m
		};
		
		// ----------------------------------------------------------------------------------------------------
		struct SFrameElement
		{
			IExternalSystemDataPtr	fFrameSystem;
			double					fArea;						// sq m
			double					fGlazingEdgeLength;			// m
			double					fInstallationEdgeLength;	// m
		};

		// ----------------------------------------------------------------------------------------------------
		struct SAdditionalElement
		{
			double					fUValue;					// W/sq m K
			double					fArea;						// sq m
		};

		// ----------------------------------------------------------------------------------------------------
		struct SAdditionalPSIElement
		{
			double					fPSI;						// W/m K
			double					fLength;					// m
		};
		
		// ----------------------------------------------------------------------------------------------------
		struct SXICGGlassCarrierElement
		{
			double					fXI;						// W/K
		};
		
		// ----------------------------------------------------------------------------------------------------
		struct SXIAdditionalElement
		{
			double					fXI;						// W/K
		};
		
		// ----------------------------------------------------------------------------------------------------
		// {B5A39453-78CE-4E2E-94DD-2DF776B54C0C}
		static const VWIID IID_EnergyBuildingElementWinDoorEx = { 0xb5a39453, 0x78ce, 0x4e2e, { 0x94, 0xdd, 0x2d, 0xf7, 0x76, 0xb5, 0x4c, 0x0c } };

		class DYNAMIC_ATTRIBUTE IEnergyBuildingElementWinDoorEx : public IVWUnknown
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
			virtual void				VCOM_CALLTYPE CopyInterfaceDataFrom(IEnergyBuildingElementWinDoorEx* interfaceData) = 0;

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
			
			//Glazing Element
			virtual void				VCOM_CALLTYPE GetKeysOfGlazingElements(TKeysArray& keyArray) = 0;;
			virtual void				VCOM_CALLTYPE ClearGlazingElements() = 0;
			virtual void				VCOM_CALLTYPE GenerateGlazingElement(SGlazingElement& element, size_t& key) = 0;
			virtual void				VCOM_CALLTYPE SetGlazingElementAt(size_t key, const SGlazingElement& element) = 0; // If it does not exist, it will be created.
			virtual bool				VCOM_CALLTYPE RemoveGlazingElement(size_t key) = 0;
			virtual SGlazingElement		VCOM_CALLTYPE GetGlazingElement(size_t key) = 0; // If it does not exist, it will be created.
			
			//Frame Element
			virtual void				VCOM_CALLTYPE GetKeysOfFrameElements(TKeysArray& keyArray) = 0;;
			virtual void				VCOM_CALLTYPE ClearFrameElements() = 0;
			virtual void				VCOM_CALLTYPE GenerateFrameElement(SFrameElement& element, size_t& key) = 0;
			virtual void				VCOM_CALLTYPE SetFrameElementAt(size_t key, const SFrameElement& element) = 0; // If it does not exist, it will be created.
			virtual bool				VCOM_CALLTYPE RemoveFrameElement(size_t key) = 0;
			virtual SFrameElement		VCOM_CALLTYPE GetFrameElement(size_t key) = 0; // If it does not exist, it will be created.
			
			//Additional Element
			virtual void				VCOM_CALLTYPE GetKeysOfAdditionalElements(TKeysArray& keyArray) = 0;;
			virtual void				VCOM_CALLTYPE ClearAdditionalElements() = 0;
			virtual void				VCOM_CALLTYPE GenerateAdditionalElement(SAdditionalElement& element, size_t& key) = 0;
			virtual void				VCOM_CALLTYPE SetAdditionalElementAt(size_t key, const SAdditionalElement& element) = 0; // If it does not exist, it will be created.
			virtual bool				VCOM_CALLTYPE RemoveAdditionalElement(size_t key) = 0;
			virtual SAdditionalElement	VCOM_CALLTYPE GetAdditionalElement(size_t key) = 0; // If it does not exist, it will be created.
			
			//Additional PSI Element
			virtual void					VCOM_CALLTYPE GetKeysOfAdditionalPSIElements(TKeysArray& keyArray) = 0;;
			virtual void					VCOM_CALLTYPE ClearAdditionalPSIElements() = 0;
			virtual void					VCOM_CALLTYPE GenerateAdditionalPSIElement(SAdditionalPSIElement& element, size_t& key) = 0;
			virtual void					VCOM_CALLTYPE SetAdditionalPSIElementAt(size_t key, const SAdditionalPSIElement& element) = 0; // If it does not exist, it will be created.
			virtual bool					VCOM_CALLTYPE RemoveAdditionalPSIElement(size_t key) = 0;
			virtual SAdditionalPSIElement	VCOM_CALLTYPE GetAdditionalPSIElement(size_t key) = 0; // If it does not exist, it will be created.
			
			//XI CG Glass Carrier Element
			virtual void						VCOM_CALLTYPE GetKeysOfXICGGlassCarrierElements(TKeysArray& keyArray) = 0;;
			virtual void						VCOM_CALLTYPE ClearXICGGlassCarrierElements() = 0;
			virtual void						VCOM_CALLTYPE GenerateXICGGlassCarrierElement(SXICGGlassCarrierElement& element, size_t& key) = 0;
			virtual void						VCOM_CALLTYPE SetXICGGlassCarrierElementAt(size_t key, const SXICGGlassCarrierElement& element) = 0; // If it does not exist, it will be created.
			virtual bool						VCOM_CALLTYPE RemoveXICGGlassCarrierElement(size_t key) = 0;
			virtual SXICGGlassCarrierElement	VCOM_CALLTYPE GetXICGGlassCarrierElement(size_t key) = 0; // If it does not exist, it will be created.
			
			//XI Additional Element
			virtual void					VCOM_CALLTYPE GetKeysOfXIAdditionalElements(TKeysArray& keyArray) = 0;
			virtual void					VCOM_CALLTYPE ClearXIAdditionalElements() = 0;
			virtual void					VCOM_CALLTYPE GenerateXIAdditionalElement(SXIAdditionalElement& element, size_t& key) = 0;
			virtual void					VCOM_CALLTYPE SetXIAdditionalElementAt(size_t key, const SXIAdditionalElement& element) = 0; // If it does not exist, it will be created.
			virtual bool					VCOM_CALLTYPE RemoveXIAdditionalElement(size_t key) = 0;
			virtual SXIAdditionalElement	VCOM_CALLTYPE GetXIAdditionalElement(size_t key) = 0; // If it does not exist, it will be created.

			virtual bool				VCOM_CALLTYPE GetBooleanValue(const TXString& nameOfParameter, bool& value) = 0; // Gets boolean value of < nameOfParameter >. value is value of parameter. Function returns true if parameter exists
			virtual void				VCOM_CALLTYPE SetBooleanValue(const TXString& nameOfParameter, bool value) = 0; // Sets boolean value of < nameOfParameter >

			virtual bool				VCOM_CALLTYPE GetDoubleValue(const TXString& nameOfParameter, double& value) = 0; // Gets double value of < nameOfParameter >. value is value of parameter. Function returns true if parameter exists
			virtual void				VCOM_CALLTYPE SetDoubleValue(const TXString& nameOfParameter, double value) = 0; // Sets double value of < nameOfParameter >


			virtual double				VCOM_CALLTYPE GetLightTransmissionGlazing() = 0;					// %
			virtual void				VCOM_CALLTYPE SetLightTransmissionGlazing(double value) = 0;		// %

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
		typedef VCOMPtr<IEnergyBuildingElementWinDoorEx>		IEnergyBuildingElementWinDoorExPtr;
	}
}
