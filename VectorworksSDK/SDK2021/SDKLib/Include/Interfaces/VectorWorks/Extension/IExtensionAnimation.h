//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

#include "IExtension.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {EB0154A1-A4C1-4A1F-ABE9-D05E3D1EB8AB}
		static const VWGroupID GROUPID_ExtensionAnimation = { 0xeb0154a1, 0xa4c1, 0x4a1f, { 0xab, 0xe9, 0xd0, 0x5e, 0x3d, 0x1e, 0xb8, 0xab } };

		// ----------------------------------------------------------------------------------------------------
		// Abstract class base for menu extension application
		class DYNAMIC_ATTRIBUTE IExtensionAnimation : public IExtension
		{
		public:
			virtual Sint32			VCOM_CALLTYPE	GetID() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetName() = 0;
			virtual void			VCOM_CALLTYPE	GetAnimationVersion(short& outMajor, short& outMinor) = 0;
		};

	}
}
