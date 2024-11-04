//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Math
	{
		// --------------------------------------------------------------------------------------------------
		
		struct SFitPointData
		{
			WorldPt fPoint{};
			double	fElevationZ{};
			double	fBottomOffset{};

			SFitPointData(WorldPt point, double elevationZ, double bottomOffset)
				: fPoint(point)
				, fElevationZ(elevationZ)
				, fBottomOffset(bottomOffset)
			{
			}
		};

		typedef std::vector <MCObjectHandle> TObjectsArray;
		typedef std::vector <TInternalID> TFilterInternalIDArray;
		typedef std::vector <InternalIndex> TFilterClassArray;
		typedef std::vector <SFitPointData> TFitPointDataArray;

		// {6E4D776B-4E2F-40CF-80CC-8C270CE4C7C4}
		static const VWIID IID_Gravity = { 0x6e4d776b, 0x4e2f, 0x40cf, { 0x80, 0xcc, 0x8c, 0x27, 0xc, 0xe4, 0xc7, 0xc4 } };
	
		class DYNAMIC_ATTRIBUTE IGravity : public IVWSingletonUnknown
		{
			public:
				// If inObjects array contains a Layer, it will fit to all objects in the layer except those set in the filter array.
				// Will not fit to objects whose class is in inFilterClassArray.
				virtual void VCOM_CALLTYPE FitPointsToObjects(TObjectsArray inObjects, const TFilterInternalIDArray& inFilterArray, const TFilterClassArray& inFilterClassArray, TFitPointDataArray& inOutPointDataArray, const bool& inLimitMaxZ, const bool& inUsePathInterpolation, const double& inEpsilon) = 0;
		};

		// ---------------------------------------------------------------------------
		typedef VCOMPtr<IGravity> IGravityPtr;
	}
}
