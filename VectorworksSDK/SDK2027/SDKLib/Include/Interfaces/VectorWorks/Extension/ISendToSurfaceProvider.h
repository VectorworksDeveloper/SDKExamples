//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IDTMTIN.h"
#include <unordered_map>

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		typedef std::unordered_map<TXString, TXString>	TSendToSurfaceContextMap;

		// ----------------------------------------------------------------------------------------------------
		// {F9720118-3F1E-4E45-9982-35FDA8A4F269}
		static const Extension::TSinkIID IID_SendToSurfaceProvider = { 0xf9720118, 0x3f1e, 0x4e45, { 0x99, 0x82, 0x35, 0xfd, 0xa8, 0xa4, 0xf2, 0x69 } };

		class DYNAMIC_ATTRIBUTE ISendToSurfaceProvider : public Extension::IEventSink
		{
		public:
			virtual VCOMError		VCOM_CALLTYPE SendToSurface(MCObjectHandle hObject, MCObjectHandle hDTMObject, IDTMTIN* theTIN, TSendToSurfaceContextMap& mapContext) = 0;
		};
	}
}
