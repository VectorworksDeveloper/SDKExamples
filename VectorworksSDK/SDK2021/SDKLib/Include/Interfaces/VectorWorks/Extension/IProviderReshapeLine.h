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
		// {EBFE9BC4-B9B1-40F8-AC5A-4AA356CACE72}
		static const TSinkIID IID_ProviderReshapeLine = { 0xebfe9bc4, 0xb9b1, 0x40f8, { 0xac, 0x5a, 0x4a, 0xa3, 0x56, 0xca, 0xce, 0x72 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderReshapeLine : public IEventSink
		{
		public:
			virtual void VCOM_CALLTYPE		Activate(MCObjectHandle h, bool moveEnd) = 0;
			virtual void VCOM_CALLTYPE		Deactivate() = 0;

			virtual void VCOM_CALLTYPE		Setup() = 0;
			virtual void VCOM_CALLTYPE		OnMouseMove(WorldPt& startPt, WorldPt& endPt, bool moveEnd) = 0;
			virtual void VCOM_CALLTYPE		OnComplete(const WorldPt& oldPt, const WorldPt& newPt) = 0;
		};
	}
}