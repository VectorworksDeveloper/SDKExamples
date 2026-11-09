//
//	Copyright Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Data
	{
		class CStyledClassData
		{
		public:
									CStyledClassData();
			virtual					~CStyledClassData();

			void					LoadClassData(MCObjectHandle hObject);
			void					SaveClassData(MCObjectHandle hObject);

			static InternalIndex	GetClassFromStyle(MCObjectHandle hSymDef);
			static void				GetClassParamsFromSymDef(const TXString& styleName, bool& isClassByStyle, InternalIndex& classID);

		public:
			InternalIndex			fClassID;
			bool					fIsClassByStyle;
		};
	}
}