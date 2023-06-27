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
		class VWPluginToolApp;
		// ---------------------------------------------------------------------------
		struct SCustomBarFieldInfo
		{
			TXString 		fstrFieldLabel;
			TXString	 	fstrFieldValue;
			bool			fIsEditable;
			bool			fIsLocked;

							SCustomBarFieldInfo();
							SCustomBarFieldInfo(const char* szLabel);
		};

		// ---------------------------------------------------------------------------
		class VWPluginToolCustomBar
		{
			friend class VWPluginToolApp;
		public:
									VWPluginToolCustomBar(size_t id);
			virtual					~VWPluginToolCustomBar();

		protected:
									VWPluginToolCustomBar(const VWPluginToolCustomBar& src);
			VWPluginToolCustomBar&	operator=(const VWPluginToolCustomBar& src);

		public:
			bool					Create(size_t fieldsCount);
			void					Install();
			void					Release();
			bool					IsValid() const;

			SCustomBarFieldInfo		GetFieldInfo(size_t fieldIndex);
			void					SetFieldInfo(size_t fieldIndex, const SCustomBarFieldInfo& info);

			void					SetFieldAngle(size_t fieldIndex, double angle);
			void					SetFieldWorldCoord(size_t fieldIndex, double value);

		// User bar tools
		public:
			static void				DataDisplayBar_SetField(size_t fieldIndex, BarNumberType type, const TXString& label);
			static void				DataDisplayBar_Clear();
			static void				UserBar_SetDimValue(size_t fieldIndex, double dimValue);
			static void				UserBar_SetFloatValueGeneral(size_t fieldIndex, double value);
			static void				UserBar_SetFloatValueAngle(size_t fieldIndex, double value);
			static void				UserBar_SetFloatValue(size_t fieldIndex, double value, Uint8 numPlaces);
			static void				UserBar_SetTextValue(size_t fieldIndex, const TXString& text);

		// cutom bar support
		public:
			static void				SetCustomBars(CustomBarRefID* pArrBarRefIDs, size_t count);

		private:
			CustomBarRefID*							fpCustomBarRefID;

			static CustomBarRefID*					fpArrCustomBarRefIDs;
			static size_t					fnCustomBarsRefIDsCount;
		};
	}
}
