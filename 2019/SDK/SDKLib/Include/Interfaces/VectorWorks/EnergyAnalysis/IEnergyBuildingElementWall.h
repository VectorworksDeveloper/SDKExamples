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
		// ---------------------------------------------------------------------------
		enum class EWallType
		{
			ExteriorAmbient,
			ExteriorGround,
			PartitionToNeighbour,
		};

		// ----------------------------------------------------------------------------------------------------
		// {0CEF861B-C4C7-440E-ADA4-DD54837AA3AC}
		static const VWIID IID_EnergyBuildingElementWall = { 0xcef861b, 0xc4c7, 0x440e, { 0xad, 0xa4, 0xdd, 0x54, 0x83, 0x7a, 0xa3, 0xac } };

		class DYNAMIC_ATTRIBUTE IEnergyBuildingElementWall : public IVWUnknown
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
			virtual void				VCOM_CALLTYPE CopyInterfaceDataFrom(IEnergyBuildingElementWall* interfaceData) = 0;

			virtual bool				VCOM_CALLTYPE GetIsModified() = 0;
			virtual void				VCOM_CALLTYPE SetIsModified(bool value) = 0;

			virtual bool				VCOM_CALLTYPE GetSupportEdit() = 0;
			virtual void				VCOM_CALLTYPE SetSupportEdit(bool value) = 0;

			virtual TXString			VCOM_CALLTYPE GetName(bool useOriginal) = 0;
			virtual void				VCOM_CALLTYPE SetName(const TXString & value, bool toOriginal) = 0;

			virtual double				VCOM_CALLTYPE GetArea(bool useOriginal) = 0;				// sq m
			virtual void				VCOM_CALLTYPE SetArea(double value, bool toOriginal) = 0;	// sq m

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

			virtual EWallType			VCOM_CALLTYPE GetWallType() = 0;
			virtual void				VCOM_CALLTYPE SetWallType(EWallType value) = 0;

			virtual double				VCOM_CALLTYPE GetExteriorAbsorptivity() = 0;

			virtual double				VCOM_CALLTYPE GetExteriorEmissivity() = 0;

			virtual double				VCOM_CALLTYPE GetReductionFactorShading() = 0;
			virtual void				VCOM_CALLTYPE SetReductionFactorShading(double value) = 0;

			virtual SBuildingElemComponent	VCOM_CALLTYPE GetComponent(size_t index) = 0;
			virtual void					VCOM_CALLTYPE SetComponents(const TSCompArray& components) = 0;

			virtual IExternalSystemDataPtr	VCOM_CALLTYPE GetBoundaryType() = 0;
			virtual void					VCOM_CALLTYPE CopyBoundaryType(IExternalSystemDataPtr boundaryType) = 0;

			virtual IExternalSystemDataPtr	VCOM_CALLTYPE GetExteriorMaterial() = 0;
			virtual void					VCOM_CALLTYPE CopyExteriorMaterial(IExternalSystemDataPtr externalMaterial) = 0;

			virtual bool				VCOM_CALLTYPE GetLambdaFromMaterial(double& inOutLambda, double thickness = 304.8) = 0;	// W/(mK)
			
			virtual bool				VCOM_CALLTYPE DialogUI_EditAdvancedOptionsDlg() = 0;

			virtual bool				VCOM_CALLTYPE UpdateIncludeOfRelevantElements(bool showQuestion, bool &questionWasShown, bool &answerToQuestionWasYes) = 0; // This function shows dialog with question for confirmation.
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyBuildingElementWall>		IEnergyBuildingElementWallPtr;
	}
}
