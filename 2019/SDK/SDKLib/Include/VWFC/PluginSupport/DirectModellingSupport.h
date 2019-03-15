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
			void		SetFieldLock(size_t fieldIndex, bool isLocked);

			void		GetFieldDef(size_t fieldIndex, CustomBarFieldInfo& outInfo);
			void		SetFieldDef(size_t fieldIndex, const CustomBarFieldInfo& info);

		// fields support
		public:
			void		ClearFields();
			void		AddField(const TXString& field);

		private:
			CustomBarRefID		fCustomBarID;

			typedef std::vector<CustomBarFieldInfo>	TBarFields;
			TBarFields	farrFields;
		};
	}

	// ------------------------------------------------------------------------------------------------------
	namespace PluginSupport
	{
		template<class T> CParametricHotSpotArray<T>::CParametricHotSpotArray()
		{
		}

		template<class T> CParametricHotSpotArray<T>::~CParametricHotSpotArray()
		{
		}

		template<class T> size_t CParametricHotSpotArray<T>::AddHotSpot(HotSpotType type, const WorldPt3& location, const TXString& tipText, const T& data)
		{
			CParametricHotSpot	hotSpot( type, location, tipText, Sint32(farrHotSpots.size()) );
			hotSpot.Add();
			farrHotSpots.push_back( hotSpot );
			farrHotSpotsData.push_back( data );
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			return farrHotSpots.size() - 1;
		}

		template<class T> size_t CParametricHotSpotArray<T>::AddHotSpot(HotSpotType type, const WorldPt3& location, const TXString& cursorID, const TXString& tipText, const T& data)
		{
			CParametricHotSpot	hotSpot( type, location, cursorID, tipText, Sint32(farrHotSpots.size()) );
			hotSpot.Add();
			farrHotSpots.push_back( hotSpot );
			farrHotSpotsData.push_back( data );
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			return farrHotSpots.size() - 1;
		}

		template<class T> size_t CParametricHotSpotArray<T>::AddHotSpot(const CParametricHotSpot& inHotSpot, const T& data)
		{			
			CParametricHotSpot	hotSpot( inHotSpot.GetType(), inHotSpot.GetLocation(), inHotSpot.GetCursorSpec(), inHotSpot.GetTipText(), Sint32(farrHotSpots.size()) );			
			hotSpot.Add();
			farrHotSpots.push_back( hotSpot );
			farrHotSpotsData.push_back( data );
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			return farrHotSpots.size() - 1;
		}

		template<class T> void CParametricHotSpotArray<T>::RemoveAll()
		{
			size_t	cnt	= farrHotSpots.size();
			for(size_t i=0; i<cnt; i++) {
				farrHotSpots[i].Remove();
			}

			farrHotSpots.clear();
			farrHotSpotsData.clear();
		}

		template<class T> CParametricHotSpot* CParametricHotSpotArray<T>::GetHotSpotAt(size_t index)
		{
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			if ( index < farrHotSpots.size() )	return & farrHotSpots[ index ];
			else								return NULL;
		}

		template<class T> T* CParametricHotSpotArray<T>::GetHotSpotDataAt(size_t index)
		{
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			if ( index < farrHotSpotsData.size() )	return & farrHotSpotsData[ index ];
			else									return NULL;
		}

		template<class T> CParametricHotSpot* CParametricHotSpotArray<T>::TrackHotSpot()
		{
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			CParametricHotSpot*	result	= NULL;
			Boolean				is3D;
			WorldPt3			location;
			Sint32				data;
			HotSpotRefID			hotSpotID = gSDK->TrackHotSpotN( is3D, location, data );
			if ( hotSpotID ) {
				if ( VERIFYN( kVStanev, data >= 0 && size_t(data) < farrHotSpots.size() ) ) { //-V201
					ASSERTN( kVStanev, farrHotSpots[ data ].GetHotspotID() == hotSpotID );
					result	=  & farrHotSpots[ data ];
				}
			}

			return result;
		}

		template<class T> T* CParametricHotSpotArray<T>::TrackHotSpotData()
		{
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );

			T*					result	= NULL;
			Boolean				is3D;
			WorldPt3			location;
			Sint32				data;
			HotSpotRefID			hotSpotID = gSDK->TrackHotSpotN( is3D, location, data );
			if ( hotSpotID ) {
				if ( VERIFYN( kVStanev, data >= 0 && size_t(data) < farrHotSpotsData.size() ) ) { //-V201
					ASSERTN( kVStanev, farrHotSpots[ data ].GetHotspotID() == hotSpotID );
					T&	theData	= farrHotSpotsData[ data ];
					result		= & theData;
				}
			}

			return result;
		}

		template<class T> T* CParametricHotSpotArray<T>::TrackHotSpotData(CParametricHotSpot& outHotSpot)
		{
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );

			T*					result	= NULL;
			Boolean				is3D;
			WorldPt3			location;
			Sint32				data;
			HotSpotRefID			hotSpotID = gSDK->TrackHotSpotN( is3D, location, data );
			if ( hotSpotID ) {
				if ( VERIFYN( kVStanev, data >= 0 && size_t(data) < farrHotSpotsData.size() ) ) { //-V201
					ASSERTN( kVStanev, farrHotSpots[ data ].GetHotspotID() == hotSpotID );
					outHotSpot	= farrHotSpots[ data ];
					T&	theData	= farrHotSpotsData[ data ];
					result		= & theData;
				}
			}

			return result;
		}
	}
}