//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IExtension.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {87EEE0BA-FC89-4704-ADA3-95EECF022590}
		static const TSinkIID IID_ProviderSplit = { 0x87eee0ba, 0xfc89, 0x4704, { 0xad, 0xa3, 0x95, 0xee, 0xcf, 0x2, 0x25, 0x90 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderSplit : public IEventSink
		{
			public:
				virtual bool VCOM_CALLTYPE		UseStandardSplit(MCObjectHandle h)			{ return false; }

				// The input parameter arrSplitParts contains the parts of the path left after the split was done.
				// They should be used as the paths of the result objects.
				// If any of these objects is not used, it should be deleted.
				// If you do not want to handle this, return false and the objects in arrSplitParts will be deleted automatically.
				virtual bool VCOM_CALLTYPE		DoSplit(MCObjectHandle h, const TMCObjectHandlesSTLArray& arrSplitParts)			{ return false; }
		};
	}
}