//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		// {9D139CCF-88E7-45A2-B805-2BDB275BD70C}
		static const Extension::TSinkIID IID_ProviderAlignObject = { 0x9d139ccf, 0x88e7, 0x45a2, { 0xb8, 0x5, 0x2b, 0xdb, 0x27, 0x5b, 0xd7, 0xc } };

		class DYNAMIC_ATTRIBUTE IProviderAlignObject : public Extension::IEventSink
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE GetObjectBounds(MCObjectHandle hObject, WorldRect& outBounds) = 0;
		};
	}
}
