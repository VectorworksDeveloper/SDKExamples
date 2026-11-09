//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IPolyDefArray.h"

namespace VectorWorks
{
	namespace Math
	{
		// ---------------------------------------------------------------------------------------------------
		const VCOMError		kVCOMError_TrueTypeConv_OnlyWhiteSpacePresent			= 100;
		const VCOMError		kVCOMError_TrueTypeConv_NoTextNodeObjectsFound			= 101;
		const VCOMError		kVCOMError_TrueTypeConv_UndefinedConversionError		= 102;

		// ---------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ITrueTypeConvListener
		{
		public:
			virtual						~ITrueTypeConvListener()	{}
			virtual	void VCOM_CALLTYPE	BeginPolyline() = 0;
			virtual	void VCOM_CALLTYPE	EndPolyline() = 0;
			virtual	void VCOM_CALLTYPE	BeginOpening() = 0;
			virtual	void VCOM_CALLTYPE	EndOpening() = 0;
			virtual	void VCOM_CALLTYPE	AddVertex(const WorldPt& pt, VertexType vertType, double dRadius) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		// {B8A77AB5-1505-4780-A9F9-2083FE94E9E5}
		static const VWIID IID_TrueTypeConv	= { 0xb8a77ab5, 0x1505, 0x4780, { 0xa9, 0xf9, 0x20, 0x83, 0xfe, 0x94, 0xe9, 0xe5 } };

		class DYNAMIC_ATTRIBUTE ITrueTypeConv : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE Convert(MCObjectHandle hText, MCObjectHandle& outResultGroup) = 0;
			virtual VCOMError VCOM_CALLTYPE Convert(MCObjectHandle hText, IPolyDefArray* pResultArray) = 0;
			virtual VCOMError VCOM_CALLTYPE Convert(MCObjectHandle hText, ITrueTypeConvListener* pResultListener) = 0;
		};
	}
}
