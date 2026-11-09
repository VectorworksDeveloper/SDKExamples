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
		// This class is used to facilitate the temporary stoppage of Change Tracking and Project Sharing reporting for the passed in
		// MCObjectHandle.  When a TSkipChangesState object is constructed, the passed in handle will no longer be processed by
		// the Change Tracking System and its observers (Project Sharing) for the duration of the TSkipChangesState object's
		// existence.  When a TSkipChangesState object destructs, the handle that was passed in to the constructor will then
		// begin to be recognized by the Change Tracking System and its observers (Project Sharing).
		class TSkipChangesState
		{
		public:
			[[nodiscard]] TSkipChangesState(MCObjectHandle h);
			~TSkipChangesState();

		private:
			ISkipChangesContextPtr context = nullptr;
		};
	}
}
