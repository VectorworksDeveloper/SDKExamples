//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IDTMTIN.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {406550B4-6D3F-4d88-B2B6-87EA0CD21590}
		static const TSinkIID IID_DTMNotificationListener = { 0x406550b4, 0x6d3f, 0x4d88, { 0xb2, 0xb6, 0x87, 0xea, 0xc, 0xd2, 0x15, 0x90 } };

		// ----------------------------------------------------------------------------------------------------
		enum EDTMResetModel
		{
			eDTMResetModel_Base,
			eDTMResetModel_TINModel,
			eDTMResetModel_Contours
		};

		// ----------------------------------------------------------------------------------------------------
		// Base class for Site Model notification listeners
		class DYNAMIC_ATTRIBUTE IDTMNotificationListener : public IVWUnknown
		{
		public:
			virtual void VCOM_CALLTYPE	OnModifiersBeforeCollect(MCObjectHandle hDTMObject)			{}
			virtual void VCOM_CALLTYPE	OnResetModel(MCObjectHandle hDTMObject, EDTMResetModel whatResets, IDTMTIN* existTIN, IDTMTIN* propTIN)	{}
			virtual void VCOM_CALLTYPE	OnResetVisual(MCObjectHandle hDTMObject)					{}
		};
	}
}