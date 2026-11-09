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
		// ----------------------------------------------------------------------------------------------------
		// {13DA0E82-3AD0-45FD-B948-9438F8FAE6AD}
		static const VWIID IID_EnergyBuildingMaterial = { 0x13da0e82, 0x3ad0, 0x45fd, { 0xb9, 0x48, 0x94, 0x38, 0xf8, 0xfa, 0xe6, 0xad } };

		class DYNAMIC_ATTRIBUTE IEnergyBuildingMaterial : public IVWUnknown
		{
		
		public:
			
			virtual bool				VCOM_CALLTYPE GetLambdaFromMaterial(double& inOutLambda,const TXString&  sOverrideUnitSystem, double thickness = 304.8) = 0;	// W/(mK)
					
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyBuildingMaterial>		IEnergyBuildingMaterialPtr;
	}
}
