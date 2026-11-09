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
		enum EParametricSubType
		{
			kParametricSubType_Point		= 0,	// for Point Plug-in Objects that insert like symbols 
			kParametricSubType_Linear		= 10,	// for Linear Plug-in Objects 
			kParametricSubType_Rectangular	= 20,	// for Rectangular Plug-in Objects 
			kParametricSubType_2DPath		= 30,	// for 2D Path Plug-in Objects 
			kParametricSubType_3DPath		= 40,	// for 3D Path Plug-in Objects
			kParametricSubType_Custom		= 50,	// for Custom control points based object
		};

		// ----------------------------------------------------------------------------------------------------
		// {E522A21B-4351-4e67-8858-3689F443A92F}
		static const VWGroupID GROUPID_ExtensionParametric = { 0xe522a21b, 0x4351, 0x4e67, { 0x88, 0x58, 0x36, 0x89, 0xf4, 0x43, 0xa9, 0x2f } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IExtensionParametric : public IExtension
		{
		public:
			virtual const TXString& VCOM_CALLTYPE		GetLocalizedName() = 0;
			virtual EParametricSubType VCOM_CALLTYPE	GetObjectType() = 0;
			virtual void VCOM_CALLTYPE					GetResetModeOnMove(bool& outOnMove, bool& outOnRotate) = 0;
			virtual void VCOM_CALLTYPE					GetWallInsertMode(bool& outOnEdge, bool& outNoBreak, bool& outHalfBreak, bool& outHideCaps) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {F12F673D-4BCD-419c-923F-1BD6EE4E5D46}
		static const TSinkIID IID_ParametricParamsProvider = { 0xf12f673d, 0x4bcd, 0x419c, { 0x92, 0x3f, 0x1b, 0xd6, 0xee, 0x4e, 0x5d, 0x46 } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IParametricParamsProvider : public IEventSink
		{
		public:
			virtual size_t VCOM_CALLTYPE			GetParamsCount() = 0;
			virtual void VCOM_CALLTYPE				GetParamAt(size_t paramIndex, TXString& outUniversalName, EFieldStyle& outType) = 0;
			virtual const TXString& VCOM_CALLTYPE	GetParamNameAt(size_t paramIndex) = 0;
			virtual void VCOM_CALLTYPE				GetParamDefValueImperial(size_t paramIndex, TXString& outValue) = 0;
			virtual void VCOM_CALLTYPE				GetParamDefValueMetric(size_t paramIndex, TXString& outValue) = 0;
			virtual void VCOM_CALLTYPE				GetParamChoices(size_t paramIndex, TXStringArray& outArrUniversalNames, TXStringArray& outArrDisplayNames) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {BA3085CD-AA5D-4615-8B84-107A89CC7188}
		static const TSinkIID IID_ParametricParams2Provider = { 0xba3085cd, 0xaa5d, 0x4615, { 0x8b, 0x84, 0x10, 0x7a, 0x89, 0xcc, 0x71, 0x88 } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IParametricParams2Provider : public IEventSink
		{
		public:
			virtual size_t VCOM_CALLTYPE			GetParamsCount() = 0;
			virtual void VCOM_CALLTYPE				GetParamAt(size_t paramIndex, TXString& outUniversalName, EFieldStyle& outType) = 0;
			virtual const TXString& VCOM_CALLTYPE	GetParamNameAt(size_t paramIndex) = 0;
			virtual void VCOM_CALLTYPE				GetParamDefValueImperial(size_t paramIndex, IRecordItem* outValue) = 0;
			virtual void VCOM_CALLTYPE				GetParamDefValueMetric(size_t paramIndex, IRecordItem* outValue) = 0;
			virtual void VCOM_CALLTYPE				GetParamChoices(size_t paramIndex, TXStringArray& outArrUniversalNames, TXStringArray& outArrDisplayNames) = 0;
		};
	}
}
