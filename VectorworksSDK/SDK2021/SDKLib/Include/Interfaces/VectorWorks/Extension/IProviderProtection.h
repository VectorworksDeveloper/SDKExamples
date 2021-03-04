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
		enum EProtectionProduct
		{
			eProtectionProduct_Foundation		= 0x00000000,
			eProtectionProduct_RenderWorks		= 0x00000001,
			eProtectionProduct_Architect		= 0x00000002,
			eProtectionProduct_Landmark			= 0x00000004,
			eProtectionProduct_Spotlight		= 0x00000008,
			eProtectionProduct_Mechanical		= 0x00000010,
			eProtectionProduct_Europe			= 0x00000020,
			eProtectionProduct_HomeBuilder		= 0x00000040,
			eProtectionProduct_NNAAll			= 0x0000003F,
			eProtectionProduct_All				= 0xFFFFFFFF,
		};

		// ----------------------------------------------------------------------------------------------------
		enum EProtectionMode
		{
			eProtectionMode_AllExceptViewer			= 0x0000,
			eProtectionMode_Full					= 0x0001,
			eProtectionMode_Demo					= 0x0002,
			eProtectionMode_Education				= 0x0004,
			eProtectionMode_Student					= 0x0008,
			eProtectionMode_Viewer					= 0x0010,
			eProtectionMode_Unlicensed				= 0x0020,
			eProtectionMode_Banner					= 0x0040,
			eProtectionMode_WatermarkNewFiles		= 0x0080,
			eProtectionMode_PrintWatermark			= 0x0100,
			eProtectionMode_SaveEducationalFileFmt	= 0x0200,
			eProtectionMode_OpenEducationalFileFmt	= 0x0400,
			eProtectionMode_VectorScriptExport		= 0x0800,
			eProtectionMode_BetaSN					= 0x1000,
		};

		// ----------------------------------------------------------------------------------------------------
		// {EC158212-E80C-4680-B05B-569914FC29E5}
		static const TSinkIID IID_ProviderProtection = { 0xec158212, 0xe80c, 0x4680, { 0xb0, 0x5b, 0x56, 0x99, 0x14, 0xfc, 0x29, 0xe5 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderProtection : public IEventSink
		{
		public:
			virtual Uint16	VCOM_CALLTYPE		GetMagicNumber()		{ return 0; }	// For internal use
			virtual Uint32	VCOM_CALLTYPE		GetProducts() = 0;	/*bit combination of EProtectionProduct*/
			virtual Uint16	VCOM_CALLTYPE		GetModes() = 0;		/*bit combination of EProtectionMode*/
		};

		typedef VCOMSinkPtr<IProviderProtection>		IProviderProtectionPtr;

		// ----------------------------------------------------------------------------------------------------
		// For internal use ONLY!
		// {A8361C3F-9480-4e03-8BC3-A4B66E7C708C}
		static const TSinkIID IID_ProviderProtectionInternal = { 0xa8361c3f, 0x9480, 0x4e03, { 0x8b, 0xc3, 0xa4, 0xb6, 0x6e, 0x7c, 0x70, 0x8c } };
	}
}
