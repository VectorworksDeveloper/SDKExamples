#pragma once

namespace DemoSystem
{
	// --------------------------------------------------------------------------------------------------------
	class CSystemObject : public VWParametricObj
	{
	public:
					CSystemObject(MCObjectHandle hObject, short systemType);
		virtual		~CSystemObject();

		void		DrawObject();
		bool		Save();

	private:
		VectorWorks::EnergyAnalysis::IEnergySystemObjectPtr	fEASystems;
	};
};
