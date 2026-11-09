#pragma once

#include "Data/SpaceEnergyData.h"

namespace DemoSpace
{
	using namespace DemoSpace::Data;
	using namespace VectorWorks::EnergyAnalysis;

	class CDemoSpaceObject : public VWParametricObj
	{
	public:
				CDemoSpaceObject(MCObjectHandle hObject);
		virtual ~CDemoSpaceObject();

	public:
		void	DrawObject() const;
		void	SaveObjectData();

	protected:
		void	InitNewObject();

	private:
		CSpaceEnergyData	fObjectData;
		IEnergySpacePtr		fSpaceEnergyData;
	};
}
