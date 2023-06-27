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
		enum class EFloorSlabType
		{
			HeatedBasementOrUndergroundFloorSlab,
			SlabOnGrade,
			UnheatedBasement,
			SuspendedFloor,
			Other,
		};

		// ---------------------------------------------------------------------------
		struct SFloorSlabData
		{
			double	fBasementDepth;								// m
			double	fUValueBelowgroundWall;						// W/((m^2)K)
			double	fAirChangeUnheatedBasement;					// 1/h
			double	fBasementVolume;							// m^3
			double	fHeightAbovegroundWall;						// m
			double	fUValueAbovegroundWall;						// W/((m^2)K)
			double	fPerimeterInsulationWidth;					// m
			double	fPerimeterInsulationThickness;				// m
			bool	fHasConductivityPerimeterInsulation;
			double	fConductivityPerimeterInsulation;			// W/(mK)
			bool	fIsLocationOfPerimeterInsulationHorizontal;
			double	fHeightOfCrawlSpaceWall;					// m
			double	fUValueOfCrawlSpaceWall;					// W/((m^2)K)
			double	fAreaOfVentilationOpenings;					// m^2
			double	fWindVelocityAt10MHeight;					// m/s;
			double	fWindShieldFactor;

			SFloorSlabData()
			{
				fBasementDepth								= 0.0;
				fUValueBelowgroundWall						= 0.0;
				fAirChangeUnheatedBasement					= 0.2;
				fBasementVolume								= 0.0;
				fHeightAbovegroundWall						= 0.0;
				fUValueAbovegroundWall						= 0.0;
				fPerimeterInsulationWidth					= 0.0;
				fPerimeterInsulationThickness				= 0.0;
				fHasConductivityPerimeterInsulation			= false;
				fConductivityPerimeterInsulation			= 0.0;
				fIsLocationOfPerimeterInsulationHorizontal	= false;
				fHeightOfCrawlSpaceWall						= 0.0;
				fUValueOfCrawlSpaceWall						= 0.0;
				fAreaOfVentilationOpenings					= 0.0;
				fWindVelocityAt10MHeight					= 4.0;
				fWindShieldFactor							= 0.05;
			}
		};

		// ----------------------------------------------------------------------------------------------------
		// {4C6B0138-3D17-42DD-B7CD-EDE8B23C3A37}
		static const VWIID IID_EnergyBuildingElementSlab = { 0x4c6b0138, 0x3d17, 0x42dd, { 0xb7, 0xcd, 0xed, 0xe8, 0xb2, 0x3c, 0x3a, 0x37 } };

		class DYNAMIC_ATTRIBUTE IEnergyBuildingElementSlab : public IVWUnknown
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
			virtual void				VCOM_CALLTYPE CopyInterfaceDataFrom(IEnergyBuildingElementSlab* interfaceData) = 0;

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

			virtual EFloorSlabType		VCOM_CALLTYPE GetFloorType() = 0;
			virtual void				VCOM_CALLTYPE SetFloorType(EFloorSlabType value) = 0;

			virtual SBuildingElemComponent	VCOM_CALLTYPE GetComponent(size_t index) = 0;
			virtual void					VCOM_CALLTYPE SetComponents(const TSCompArray& components) = 0;

			virtual SFloorSlabData		VCOM_CALLTYPE GetFloorSlabData() = 0;
			virtual void				VCOM_CALLTYPE SetFloorSlabData(const SFloorSlabData& data) = 0;

			virtual IExternalSystemDataPtr	VCOM_CALLTYPE GetBoundaryType() = 0;
			virtual void					VCOM_CALLTYPE CopyBoundaryType(IExternalSystemDataPtr boundaryType) = 0;

			virtual bool				VCOM_CALLTYPE GetLambdaFromMaterial(double& inOutLambda, double thickness = 304.8) = 0;	// W/(mK)

			// Slab settings dialog support
			virtual bool				VCOM_CALLTYPE DialogUI_EditAdvancedOptionsDlg() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyBuildingElementSlab>		IEnergyBuildingElementSlabPtr;
	}
}
