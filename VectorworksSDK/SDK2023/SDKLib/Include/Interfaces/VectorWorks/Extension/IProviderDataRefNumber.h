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
		// {FEF60941-E08B-45D1-8009-361705E19C8A}
		static const TSinkIID IID_ProviderDataRefNumber = { 0xfef60941, 0xe08b, 0x45d1, { 0x80, 0x9, 0x36, 0x17, 0x5, 0xe1, 0x9c, 0x8a } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderDataRefNumber : public IEventSink
		{
		public:
			virtual void	VCOM_CALLTYPE		OnTraverseConn(		MCObjectHandle h,
																	std::function<void(Sint32 numElements, RefNumber* data)> callback
																) = 0;

			virtual void	VCOM_CALLTYPE		OnTraverseConn(		MCObjectHandle srcObj,
																	MCObjectHandle destObj,
																	std::function<void(Sint32 numElements, RefNumber* srcData, RefNumber* destData)> callback
																) = 0;
		};
	}
}

