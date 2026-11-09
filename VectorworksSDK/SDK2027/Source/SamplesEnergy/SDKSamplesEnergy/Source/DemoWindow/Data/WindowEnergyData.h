#pragma once

namespace DemoWindow
{
	const double kFrameThickness	= 10;

	namespace Data
	{
		// --------------------------------------------------------------------------------------------------------
		enum class EType
		{
			Window,
			Door,
			WinDoor,
		};

		// --------------------------------------------------------------------------------------------------------
		struct SEnergyData
		{
			bool		fIsNew;
			
			EType		fType;
			double		fHeight;
			double		fWidth;
			bool		fHasTilting;
			bool		fIncludeToEA;

			SEnergyData()
			: fIsNew ( false )
			, fType ( EType::Window )
			, fHeight ( 100.0 )
			, fWidth ( 300.0 )
			, fHasTilting ( false )
			, fIncludeToEA ( false )
			{};
		};

		// --------------------------------------------------------------------------------------------------------
		class CWindowEnergyData : public SEnergyData
		{
		public:
							CWindowEnergyData();
			virtual 		~CWindowEnergyData();

			void			LoadObjectData(MCObjectHandle hObject);
			void			SaveObjectData(MCObjectHandle hObject) const;

			void			LoadCurrentSettings();
			void			SaveCurrentSettings() const;
		};
	};
};
