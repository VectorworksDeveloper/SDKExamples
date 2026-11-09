#pragma once

#include "../Data/SpaceEnergyData.h"

namespace DemoSpace
{
	namespace UI
	{
		using namespace DemoSpace::Data;
		using namespace VectorWorks::EnergyAnalysis;

		class CDlgSpaceSettings : public VWDialog
		{
		public:
								CDlgSpaceSettings(const CSpaceEnergyData& data, IEnergySpacePtr energyData);
			virtual				~CDlgSpaceSettings();

		public:
			void				GetData(CSpaceEnergyData& data);

		// virtuals
		protected:
			virtual bool		CreateDialogLayout();
			virtual void		OnInitializeContent();
			virtual void		OnDDXInitialize();
			virtual void		OnUpdateUI();

		// events
		protected:

		// dispatch map
		protected:
			DEFINE_EVENT_DISPATH_MAP;
			void				OnAdvancedBtn(Sint32 controlID, VWDialogEventArgs& eventArgs);

		// DDX
		protected:
			double                    fHeightVal;
			bool                      fIncludeChechBox;
			bool                      fManualCheckBox;
			double                    fAreaVal;
			double                    fAreaFactorVal;

		// Inner data
		private:
			IEnergySpacePtr	fEnergyData;
			IEnergyUnitsPtr	fEnergyUnits;
		};
	}
}
