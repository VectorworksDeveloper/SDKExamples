//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace TrussAnalysis
	{
		enum class EAutoConnectTo
		{
			MiddlePoint	= 0,
			TopPoint	= 1,
			BottomPoint	= 2,
		};

		// ----------------------------------------------------------------------------------------------------
		// {FED39F49-915B-41CA-A428-3C008C4A50B7}
		static const VWIID IID_TrussAnalysis	= { 0xfed39f49, 0x915b, 0x41ca, { 0xa4, 0x28, 0x3c, 0x0, 0x8c, 0x4a, 0x50, 0xb7 } };

		class DYNAMIC_ATTRIBUTE ITrussAnalysis : public IVWSingletonUnknown
		{
		public:
			virtual void			VCOM_CALLTYPE GetLoadGroupName(const TXString & loadGroup, TXString& outLocalizedName) = 0;
									
			virtual bool			VCOM_CALLTYPE ShowTrussCrossSectionDialog(TXString& crossSection, double& height, double& width, Sint16& design, double& chordDiameter) = 0;
			virtual bool			VCOM_CALLTYPE ShowHoistCrossSectionDialog(TXString& crossSection) = 0;
									
			virtual void			VCOM_CALLTYPE GetConstructionMaterialsList(TXStringArray& universalNames, TXStringArray& localizedNames) = 0;
			virtual double			VCOM_CALLTYPE GetConstructionMaterialDensity(const TXString& materialUniName) = 0;
									
			virtual bool			VCOM_CALLTYPE GetTrussSnappingPoint(WorldPt3& inOutSnapPoint, bool highlight = false) = 0;
			virtual size_t			VCOM_CALLTYPE GetHangPositionsByHangPoint
					(const WorldPt3& hangPoint, double pickRadius, TVWArray_MCObjectHandle& outFoundPositions, TVWArray_WorldPt3& outSnapPoints) = 0;
			
			virtual void			VCOM_CALLTYPE SelectTrussSystem(MCObjectHandle handleInSystem, bool onlyTrusses = false) = 0;
			virtual void			VCOM_CALLTYPE SelectHangPosition(MCObjectHandle handleOfHangPosition) = 0;
			virtual bool			VCOM_CALLTYPE GetHoistWorkloadColoring(double currentForce, double maxForce, ColorRef& outColor) = 0;

			// Vectorworks 2018 SP3
			virtual bool			VCOM_CALLTYPE MoveTrussSystemInHangPosition(MCObjectHandle handleOfHangPosition) = 0;

			// Vectorworks 2019
			virtual bool			VCOM_CALLTYPE GetTrussSnappingPointAutoElevation(WorldPt3& outPointOnTruss, EAutoConnectTo trussElevation, bool hightlight = false) const = 0;

			typedef std::pair<MCObjectHandle, size_t>	TLoadObjectData;
			typedef	std::vector<TLoadObjectData>		TLoadObjectDataArray;
			virtual TLoadObjectDataArray	VCOM_CALLTYPE GetSystemObjectLoads(MCObjectHandle objectHandle) const = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<ITrussAnalysis>		ITrussAnalysisPtr;
	}
}
