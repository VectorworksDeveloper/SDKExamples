#pragma once
#include "../Data/WindowEnergyData.h"

namespace DemoWindow
{
	namespace UI
	{
		// --------------------------------------------------------------------------------------------------------
		class CDlgWindowSettings : public VWDialog
		{
		public:
								CDlgWindowSettings(const Data::CWindowEnergyData& data, VectorWorks::EnergyAnalysis::IEnergyBuildingElementWinDoorPtr winDoorData);
			virtual				~CDlgWindowSettings();

			void				GetData(Data::CWindowEnergyData& outdata, VectorWorks::EnergyAnalysis::IEnergyBuildingElementWinDoorPtr& outWinDoorData) const;

		// virtuals
		protected:
			virtual bool		CreateDialogLayout();
			virtual void		OnInitializeContent();
			virtual void		OnDDXInitialize();
			virtual void		OnUpdateUI();


		// dispatch map
		protected:
			DEFINE_EVENT_DISPATH_MAP;
			void				OnDimensionChange(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnBtnAdvanced(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnPopupFrame(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnPopupGlazing(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnPopupShadingGeneral(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnPopupShadingSurround(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnPopupShadingSummerShading(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnPopupShadingAddShading(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnChangeUValue(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnRadioBtn(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnChckBoxIncludeToEA(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnChckBoxTilting(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnPopupType(Sint32 controlID, VWDialogEventArgs& eventArgs);
			void				OnPopupDoorType(Sint32 controlID, VWDialogEventArgs& eventArgs);

		protected:
			void				UpdateEnergyData();
			void				UpdateAutoUValueCtrl();
		
		// DDX
		protected:
			short                     fPopupType;
			double                    fEditWidth;
			double                    fEditHeight;
			bool                      fChkHasTilting;
			bool                      fChkIncludeToEA;
			bool                      fRadioAutoCalc;
			bool                      fRadioManCalc;
			double					  fEditUvalue;

		// Inner data
		private:
			VectorWorks::EnergyAnalysis::IEnergyBuildingElementWinDoorPtr	fEAWinDoor;
			VectorWorks::EnergyAnalysis::IEnergyUnitsPtr					fEAUnits;
			VectorWorks::EnergyAnalysis::IExternalSystemDataPtr				fEAFrame;	// this is for Frame popup
			VectorWorks::EnergyAnalysis::IExternalSystemDataPtr				fEAGlazing;	// this is for Glazing popup
			VectorWorks::EnergyAnalysis::IExternalSystemDataPtr				fEADoorType;// this is for DoorType popup
		};
	};
};
