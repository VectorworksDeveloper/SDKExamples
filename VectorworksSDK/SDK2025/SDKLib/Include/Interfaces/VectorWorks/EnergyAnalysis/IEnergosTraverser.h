//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace EnergyAnalysis
	{
		struct SEnergosBuildingElements
		{
			TMCObjectHandlesSTLArray farrRoofsHandles;
			TMCObjectHandlesSTLArray farrWallsHandles;
			TMCObjectHandlesSTLArray farrWinDoorsHandles;
			TMCObjectHandlesSTLArray farrFloorsSlabsHandles;
			TMCObjectHandlesSTLArray farrOthersHandles;
		};

		struct SEnergosData
		{
			TXString	fProjectLocation;
			TXString	fProjectName;
			TXString	fProjectDescription;
			double		fAltitude;				// m
			TXString	fArchitectInfo;
			TXString	fServicesEngineerInfo;
			Uint32		fYearOfConstruction;
			TXString	fBuildingType;
			TXString	fUtilizationPattern;
			Uint32		fNumOccupantsValue;
			double		fInteriorTemperature;	// C
			Uint32		fNumberOfUnits;
			double		fTotalRelevantArea;		// sq m
			double		fTotalRelevantVolume;	// cu m
		};

		// ----------------------------------------------------------------------------------------------------
		// {8FE28A4F-7F35-4305-B797-67895B179946}
		static const VWIID IID_EnergosTraverser = { 0x8fe28a4f, 0x7f35, 0x4305, { 0xb7, 0x97, 0x67, 0x89, 0x5b, 0x17, 0x99, 0x46 } };

		class DYNAMIC_ATTRIBUTE IEnergosTraverser : public IVWUnknown
		{
			public:
				// Returns arrays of the energos building elements
				// If onlyIncluded is true, return only the building elements included in the energos calculations
				// If the building element is in a symbol, returns the symbol object handle, which has the energos data attached to it
				virtual void		VCOM_CALLTYPE CollectBuildingElements(bool onlyIncluded, SEnergosBuildingElements& outEnergosBuildingElements) = 0;

				virtual void		VCOM_CALLTYPE GetEnergosData(SEnergosData& outData) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergosTraverser>		IEnergosTraverserPtr;
	}
}
