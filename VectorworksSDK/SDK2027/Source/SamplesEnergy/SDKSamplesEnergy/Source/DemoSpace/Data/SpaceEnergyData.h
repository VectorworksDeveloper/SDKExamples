#pragma once

namespace DemoSpace
{
	namespace Data
	{
		struct SSpaceEnergyObjectData
		{
			double	fHeight;			// mm
			bool	fIsManualArea;
			double	fArea;				// sq m
			bool	fIsNew;
		};

		class CSpaceEnergyData : public SSpaceEnergyObjectData
		{
		public:
					CSpaceEnergyData();
			virtual ~CSpaceEnergyData();

		public:
			void	LoadObjectData(MCObjectHandle hObject);
			void	SaveObjectData(MCObjectHandle hObject) const;

			void	LoadCurrentSettings();
			void	SaveCurrentSettings() const;
		};
	}
}
