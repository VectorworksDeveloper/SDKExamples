//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

namespace VWFC
{
	namespace PluginSupport
	{
		// ------------------------------------------------------------------------------------------------------
		class CParametricHotSpot
		{
		public:
								CParametricHotSpot();
								CParametricHotSpot(HotSpotType type, const WorldPt3& location, const TXString& tipText, Sint32 data = 0);
								CParametricHotSpot(HotSpotType type, const WorldPt3& location, const TXString& cursorSpec, const TXString& tipText, Sint32 data = 0);
			virtual				~CParametricHotSpot();

		public:
			void				Add();
			void				Remove();
			bool				IsAdded() const;

			void				Set(HotSpotType type, const WorldPt3& location, const TXString& tipText);

			void				Set(HotSpotType type, const WorldPt3& location, const TXString& cursorSpec, const TXString& tipText);

			void				SetLocation(const WorldPt3& location);

			HotSpotRefID				GetHotspotID() const;
			const WorldPt3&		GetLocation() const;

			SintptrT			GetUserData() const;
			void				SetUserData(SintptrT userData);

			const HotSpotType&	GetType() const;
			const TXString&		GetCursorSpec() const;
			const TXString&		GetTipText() const;


		private:
			HotSpotRefID			fHotspotID;
			HotSpotType		fType;
			WorldPt3		fLocation;
			TXString		fCursorSpec;
			TXString		fTipText;
			SintptrT		fUserData;
		};

		// ------------------------------------------------------------------------------------------------------
		template<class T> class CParametricHotSpotArray
		{
		public:
										CParametricHotSpotArray();
			virtual						~CParametricHotSpotArray();

			size_t						AddHotSpot(HotSpotType type, const WorldPt3& location, const TXString& tipText, const T& data);
			size_t						AddHotSpot(HotSpotType type, const WorldPt3& location, const TXString& cursorID, const TXString& tipText, const T& data);
			size_t						AddHotSpot(const CParametricHotSpot& hotSpot, const T& data);
			void						RemoveAll();

			CParametricHotSpot*			GetHotSpotAt(size_t index);
			T*							GetHotSpotDataAt(size_t index);

			CParametricHotSpot*			TrackHotSpot();
			T*							TrackHotSpotData();
			T*							TrackHotSpotData(CParametricHotSpot& outHotSpot);

		private:
			typedef std::vector<CParametricHotSpot>		THotSpotsArray;
			typedef std::vector<T>						THotSpotsDataArray;

			THotSpotsArray				farrHotSpots;
			THotSpotsDataArray			farrHotSpotsData;
		};

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		class CHotSpotsManager
		{
		public:
			virtual				~CHotSpotsManager();

			THotSpotData*		TrackHotSpotData();
			THotSpotData* 		AddHotSpot(const WorldPt& atPt2D, const THotSpotData& hotSpotData, bool trackHotSpots = true);
			THotSpotData* 		AddHotSpot3D(const WorldPt3& atPt3D, const THotSpotData& hotSpotData, bool trackHotSpots = true);

			CParametricHotSpot*	GetActiveHotSpot();
			THotSpotData*		GetActiveHotSpotData() const;
			void				SetActiveHotSpotData(THotSpotData* hotSpotData);

			WorldPt				GetActHotSpotLocation() const;
			WorldPt3			GetActHotSpotLocation3D() const;
			void				SetActHotSpotLocation(const WorldPt& loc2D);
			void				SetActHotSpotLocation3D(const WorldPt3& loc3D);

			virtual void		RemoveActHotSpot();
			void				RemoveAll();

		protected:
			// hot spots mechanism.
			CParametricHotSpotArray<THotSpotData>	fHotSpots;

			CParametricHotSpot						fActiveHotSpot;
			THotSpotData*							fpActiveHotSpotData	= nullptr;
		};

		// ------------------------------------------------------------------------------------------------------
		class CParametricCustomBar
		{
		public:
						CParametricCustomBar();
			virtual		~CParametricCustomBar();

		public:
			bool		IsValid() const;
			CustomBarRefID		GetCustomBarID() const;

			bool		Create();
			void		Release();
			void		Install();
			void		Pause(bool beginPause);

			void		SetUp();
			void		SetDown();

			void		SetFieldWorldCoord(size_t fieldIndex, WorldCoord value);
			void 		SetFieldAngle(size_t fieldIndex, WorldCoord value);
			void		SetFieldText(size_t fieldIndex, const TXString& value);

			void		SetFieldLock(size_t fieldIndex, bool isLocked);

			void		GetFieldDef(size_t fieldIndex, CustomBarFieldInfo& outInfo);
			void		SetFieldDef(size_t fieldIndex, const CustomBarFieldInfo& info);

		// fields support
		public:
			void		ClearFields();
			void		AddField(const TXString& field);

		// tools
		public:
			static void	SetSmartCursorLockX(double value);
			static void	SetSmartCursorLockY(double value);
			static void	SetSmartCursorLockLength(double value);
			static void	SetSmartCursorLockAngle(double value);

			static void ClearSmartCursorLockX();
			static void ClearSmartCursorLockY();
			static void ClearSmartCursorLockLength();
			static void ClearSmartCursorLockAngle();

		private:
			CustomBarRefID		fCustomBarID;

			typedef std::vector<CustomBarFieldInfo>	TBarFields;
			TBarFields	farrFields;
		};
	}
}

#include "DirectModellingSupport.inl"
