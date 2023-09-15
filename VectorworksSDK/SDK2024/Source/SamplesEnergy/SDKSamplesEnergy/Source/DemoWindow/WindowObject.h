#pragma once

#include "Data/WindowEnergyData.h"

namespace DemoWindow
{
	// --------------------------------------------------------------------------------------------------------
	class CWindowObject : public VWParametricObj
	{
	public:
					CWindowObject(MCObjectHandle hObject);
		virtual		~CWindowObject();

		void		DrawObject();
		void		SaveObjectData();
		void		UpdateData();

	protected:
		void		InitNewObject();
		void		DrawDoor(VWPoint3D origin);
		void		DrawWindow(VWPoint3D origin);
		void		DrawWinDoor(VWPoint3D origin);

	private:
		Data::CWindowEnergyData											fEAData;
		VectorWorks::EnergyAnalysis::IEnergyBuildingElementWinDoorPtr	fEAWinDoor;
	};
};
