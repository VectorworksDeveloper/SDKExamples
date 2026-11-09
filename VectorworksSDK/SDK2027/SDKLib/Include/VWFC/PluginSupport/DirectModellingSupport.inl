#pragma once

namespace VWFC
{
	namespace PluginSupport
	{
		template<class T>
		CParametricHotSpotArray<T>::CParametricHotSpotArray()
		{
		}

		template<class T>
		CParametricHotSpotArray<T>::~CParametricHotSpotArray()
		{
		}

		template<class T>
		size_t CParametricHotSpotArray<T>::AddHotSpot(HotSpotType type, const WorldPt3& location, const TXString& tipText, const T& data)
		{
			CParametricHotSpot	hotSpot( type, location, tipText, Sint32(farrHotSpots.size()) );
			hotSpot.Add();
			farrHotSpots.push_back( hotSpot );
			farrHotSpotsData.push_back( data );
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			return farrHotSpots.size() - 1;
		}

		template<class T>
		size_t CParametricHotSpotArray<T>::AddHotSpot(HotSpotType type, const WorldPt3& location, const TXString& cursorID, const TXString& tipText, const T& data)
		{
			CParametricHotSpot	hotSpot( type, location, cursorID, tipText, Sint32(farrHotSpots.size()) );
			hotSpot.Add();
			farrHotSpots.push_back( hotSpot );
			farrHotSpotsData.push_back( data );
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			return farrHotSpots.size() - 1;
		}

		template<class T>
		size_t CParametricHotSpotArray<T>::AddHotSpot(const CParametricHotSpot& inHotSpot, const T& data)
		{			
			CParametricHotSpot	hotSpot( inHotSpot.GetType(), inHotSpot.GetLocation(), inHotSpot.GetCursorSpec(), inHotSpot.GetTipText(), Sint32(farrHotSpots.size()) );			
			hotSpot.Add();
			farrHotSpots.push_back( hotSpot );
			farrHotSpotsData.push_back( data );
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			return farrHotSpots.size() - 1;
		}

		template<class T>
		void CParametricHotSpotArray<T>::RemoveAll()
		{
			size_t	cnt	= farrHotSpots.size();
			for(size_t i=0; i<cnt; i++) {
				farrHotSpots[i].Remove();
			}

			farrHotSpots.clear();
			farrHotSpotsData.clear();
		}

		template<class T>
		CParametricHotSpot* CParametricHotSpotArray<T>::GetHotSpotAt(size_t index)
		{
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			if ( index < farrHotSpots.size() )	return & farrHotSpots[ index ];
			else								return NULL;
		}

		template<class T>
		T* CParametricHotSpotArray<T>::GetHotSpotDataAt(size_t index)
		{
			ASSERTN( kVStanev, farrHotSpots.size() == farrHotSpotsData.size() );
			if ( index < farrHotSpotsData.size() )	return & farrHotSpotsData[ index ];
			else									return NULL;
		}

		template<class T>
		CParametricHotSpot* CParametricHotSpotArray<T>::TrackHotSpot()
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

		template<class T>
		T* CParametricHotSpotArray<T>::TrackHotSpotData()
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

		template<class T>
		T* CParametricHotSpotArray<T>::TrackHotSpotData(CParametricHotSpot& outHotSpot)
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

		// ------------------------------------------------------------------------------------------------------
		// CHotSpotsManager
		// ------------------------------------------------------------------------------------------------------

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		CHotSpotsManager<THotSpotData>::~CHotSpotsManager()
		{
			this->RemoveAll();
		}

		// ------------------------------------------------------------------------------------------------------
		// track for hot spot and change the active hot spot.
		template<typename THotSpotData>
		THotSpotData* CHotSpotsManager<THotSpotData>::TrackHotSpotData()
		{
			fpActiveHotSpotData		= fHotSpots.TrackHotSpotData( fActiveHotSpot );

			// result.
			return fpActiveHotSpotData;
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		THotSpotData* CHotSpotsManager<THotSpotData>::AddHotSpot(const WorldPt& atPt2D, const THotSpotData& hotSpotData, bool trackHotSpots/*= true*/)
		{
			// prepare new hot spot data.
			THotSpotData		newHotSpotData		= hotSpotData;

			if ( trackHotSpots )
			{
				THotSpotData*	actHotSpotData		= this->TrackHotSpotData();	// track existing hot spots.
				if ( actHotSpotData != nullptr )
				{
					newHotSpotData					= *actHotSpotData;
				}
			}

			// add the new hot spot.
			WorldPt3		atPt3D( atPt2D, 0.0 );
			size_t			newHotSpotIndex		= fHotSpots.AddHotSpot( kModel3DSelBox, atPt3D, "", newHotSpotData );

			// update the active hot spot and the active hot spot data.
			fActiveHotSpot						= *fHotSpots.GetHotSpotAt( newHotSpotIndex );
			fpActiveHotSpotData					= fHotSpots.GetHotSpotDataAt( newHotSpotIndex );

			// result.
			return fpActiveHotSpotData;
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		THotSpotData* CHotSpotsManager<THotSpotData>::AddHotSpot3D(const WorldPt3& atPt3D, const THotSpotData& hotSpotData, bool trackHotSpots/*= true*/)
		{
			// prepare new hot spot data.
			THotSpotData		newHotSpotData		= hotSpotData;

			if ( trackHotSpots )
			{
				THotSpotData*	actHotSpotData		= this->TrackHotSpotData();	// track existing hot spots.
				if ( actHotSpotData != nullptr )
				{
					newHotSpotData					= *actHotSpotData;
				}
			}

			// add the new hot spot.
			size_t			newHotSpotIndex		= fHotSpots.AddHotSpot( kModel3DSelBox, atPt3D, "", newHotSpotData );

			// update the active hot spot and the active hot spot data.
			fActiveHotSpot						= *fHotSpots.GetHotSpotAt( newHotSpotIndex );
			fpActiveHotSpotData					= fHotSpots.GetHotSpotDataAt( newHotSpotIndex );

			// result.
			return fpActiveHotSpotData;
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		CParametricHotSpot*	CHotSpotsManager<THotSpotData>::GetActiveHotSpot()
		{
			return &fActiveHotSpot;
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		THotSpotData* CHotSpotsManager<THotSpotData>::GetActiveHotSpotData() const
		{
			return fpActiveHotSpotData;
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		void CHotSpotsManager<THotSpotData>::SetActiveHotSpotData(THotSpotData* hotSpotData)
		{
			fpActiveHotSpotData			= hotSpotData;
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		WorldPt CHotSpotsManager<THotSpotData>::GetActHotSpotLocation() const
		{
			const WorldPt3&		loc3D	= fActiveHotSpot.GetLocation();

			// result.
			return	( WorldPt( loc3D.x, loc3D.y ) );
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		WorldPt3 CHotSpotsManager<THotSpotData>::GetActHotSpotLocation3D() const
		{
			return fActiveHotSpot.GetLocation();
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		void CHotSpotsManager<THotSpotData>::SetActHotSpotLocation(const WorldPt& loc2D)
		{
			WorldPt3		loc3D( loc2D, 0.0 );
			fActiveHotSpot.SetLocation( loc3D );
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		void CHotSpotsManager<THotSpotData>::SetActHotSpotLocation3D(const WorldPt3& loc3D)
		{
			fActiveHotSpot.SetLocation( loc3D );
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		void CHotSpotsManager<THotSpotData>::RemoveActHotSpot()
		{
			fActiveHotSpot.Remove();

			fpActiveHotSpotData	= nullptr;
		}

		// ------------------------------------------------------------------------------------------------------
		template<typename THotSpotData>
		void CHotSpotsManager<THotSpotData>::RemoveAll()
		{
			this->RemoveActHotSpot();
			fHotSpots.RemoveAll();
		}
	}
}