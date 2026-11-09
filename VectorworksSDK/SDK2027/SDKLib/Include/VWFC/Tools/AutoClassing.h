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
		class VWAutoClassing
		{
		public:
			static bool			IsAutoClassingTurnedOn();
			static bool			GetUserClassName(const TXString& defaultClassName, TXString& outUserClassName);
			static void			CreateUserClass(const TXString& userClassName);
			static void			SetAttrsByClass(MCObjectHandle hObject);
			static bool			AutoClass(MCObjectHandle hPlugin, const TXString& defaultClassName);
			static bool			AutoClassByObject(MCObjectHandle hObject, const TXString& defaultClassName);
			static bool			GetRefClassName(const TXString& userClassName, TXString& defaultClassName);
			static TXString		GetUserClass(const TXString& refClass);
			static TXString		GetRefClass(const TXString& userClass);

			// this is the 'LoadAutoClassPopup' VS equivalent
			static void			GetAutoClassList(const TXString& standardClass, const TXString& selectedClass, TXStringSTLArray& outArrStrings, size_t& outSelectedIndex);
			// default value for divider index is 2.
			// But one could change the position by adding new popup elements at the beginning of a list popup.
			static TXString		GetAutoClassListSelection(size_t& inOutSelIndex, const TXString& selText, size_t dividerIndex = 2);

		protected:
			static TXString		GetLocStr(short tableID, short stringID);
			static TXString		GetRRield(MCObjectHandle hRec, const TXString& fieldName);
			static bool			GetRField(MCObjectHandle hRec, const TXString& fieldName);
		};
	}
}


