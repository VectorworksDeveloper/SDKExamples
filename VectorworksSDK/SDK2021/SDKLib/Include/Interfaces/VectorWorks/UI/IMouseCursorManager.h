//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Use this VCOM interface to change the cursor.


#pragma once

namespace VectorWorks
{
	namespace UI
	{
		static const VWIID IID_MouseCursorManager = { 0x6414660A, 0xE398, 0x11DF, { 0x87, 0xCC, 0x07, 0x1C, 0xDF, 0xD7, 0x20, 0x85} };

		class DYNAMIC_ATTRIBUTE IMouseCursorManager : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE SetCursor(const TXString& cursorImageSpecifier) = 0;
		};

		typedef VCOMPtr<IMouseCursorManager> IMouseCursorManagerPtr;
	}
}