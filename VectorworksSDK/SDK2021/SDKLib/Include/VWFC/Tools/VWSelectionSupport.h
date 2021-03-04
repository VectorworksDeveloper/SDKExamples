//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		typedef Uint32						TValueFlags;
		typedef std::vector<TValueFlags>	TFlagsArray;
		// --------------------------------------------------------------------------------------------------------
		class VWSelectionSupport
		{
		public:
						VWSelectionSupport();
			virtual		~VWSelectionSupport();

		// parametric support
		//	use these functions for context that encapsulates one or several parametric objects
		public:
			bool		InitFromParametricObject( MCObjectHandle hObject );
			bool		CompareToParametricObject( MCObjectHandle hObject );
			bool		UpdateValuesFromParametricObject( MCObjectHandle hObject );
			bool		UpdateParametric( MCObjectHandle hObject );
			bool		SetFlagsParameter( MCObjectHandle hObject, const TXString& key, const TFlagsArray& flags );
			MCObjectHandle GetHostObject();

		// raw data support
		//	use these functions for context that works on raw data
		public:
			void		Clear();
			
			void		AddRawDataKey(const TXString& key, bool determinate);	// determinate should be true if all values are the same
			void		SetRawDataKey(const TXString& key, const TXString& compareValue);
			void		SetRawDataKey(const TXString& key, const Sint32& compareValue);
			void		SetRawDataKey(const TXString& key, const Uint32& compareValue);
			void		SetRawDataKey(const TXString& key, const double& compareValue);
			template<class T>
			void		SetRawDataKey(const TXString& key, const T& compareValue);
			bool		GetRawDataModifed(const TXString& key);

		// generic
		public:
			bool		AddItem( const TXString& key, const TXString& value, bool determinate, bool edited );

			bool		GetValue( const TXString& key, TXString & value );
			bool		SetValue( const TXString& key, const TXString& value );
		
			bool		KeyExists( const TXString& key );
			Sint32		GetItemCount();

		public:
			bool		IsDeterminate( const TXString& key, bool & determinate, TValueFlags flag = 0 );
			bool		SetDeterminate( const TXString& key, bool determinate, TValueFlags flag = 0 );

			bool		IsEdited( const TXString& key, bool & edited, TValueFlags flag = 0 );
			bool		SetEdited( const TXString& key, bool edited, TValueFlags flag = 0 );

		protected:
			struct SSelectionInfo {
				TXString		key;
				bool			determinate;
				bool			edited;
				TXString		value;
				bool			fIsFlagsParameter;
				Sint32			fFlagsValue;
				Sint32			fDeterminateFlags;
				Sint32			fEditedFlags;
				TFlagsArray		fFlags;

				SSelectionInfo();
				~SSelectionInfo();
			};

			typedef std::map<TXString, SSelectionInfo>	TSelectionInfoMap;
			typedef std::pair<TXString, SSelectionInfo> TSelectionInfo_Pair;	
			typedef std::map <TXString, SSelectionInfo> :: iterator TSelectionInfo_Iterator;

		private:
			TSelectionInfoMap		fmapSelectionInfo;
			MCObjectHandle			fhHostObject;
		};

	}
}


namespace VWFC
{
	namespace Tools
	{
		template<class T> void VWSelectionSupport::SetRawDataKey(const TXString& key, const T& compareValue)
		{
			this->SetRawDataKey( key, (Sint32) compareValue );
		}
	}
}

