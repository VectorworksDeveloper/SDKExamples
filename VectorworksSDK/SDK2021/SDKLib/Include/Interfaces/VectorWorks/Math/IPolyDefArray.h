//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IPolyDef.h"

namespace VectorWorks
{
	namespace Math
	{
		// ---------------------------------------------------------------------------------------------------
		// {2B35BC1B-44E0-41fc-AF8D-BC8F43CE04DB}
		static const VWIID IID_PolyDefArray	= { 0x2b35bc1b, 0x44e0, 0x41fc, { 0xaf, 0x8d, 0xbc, 0x8f, 0x43, 0xce, 0x4, 0xdb } };

		class DYNAMIC_ATTRIBUTE IPolyDefArray : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE Size(Uint32& outCount) const = 0;
			virtual VCOMError VCOM_CALLTYPE PushBack(IPolyDef* pPolygon) = 0;
			virtual VCOMError VCOM_CALLTYPE Get(Uint32 index, IPolyDef** ppOutPolygon) const = 0;
			virtual VCOMError VCOM_CALLTYPE Insert(Uint32 index, IPolyDef* pPolygon) = 0;
			virtual VCOMError VCOM_CALLTYPE Erase(Uint32 index) = 0;
			virtual VCOMError VCOM_CALLTYPE Clear() = 0;

			virtual VCOMError VCOM_CALLTYPE Set(IPolyDefArray* pArray) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IPolyDefArray>	IPolyDefArrayPtr;
	}
}
