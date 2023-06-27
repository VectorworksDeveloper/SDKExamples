//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Cloud
	{
		// ----------------------------------------------------------------------------------------------------
		// {49B6B482-153F-494C-881C-00588018D634}
		static const VWIID IID_CloudMenuSupport = { 0x49b6b482, 0x153f, 0x494c, { 0x88, 0x1c, 0x0, 0x58, 0x80, 0x18, 0xd6, 0x34 } };
	
		class DYNAMIC_ATTRIBUTE ICloudMenuSupport : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE AddMenu(const VWIID& menuAppIID) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetMenuCount(Uint32& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE GetMenuAt(Uint32 index, VWIID& outMenuAppIID) = 0;
		};

		typedef VCOMPtr<ICloudMenuSupport>		ICloudMenuSupportPtr;
	}

}


