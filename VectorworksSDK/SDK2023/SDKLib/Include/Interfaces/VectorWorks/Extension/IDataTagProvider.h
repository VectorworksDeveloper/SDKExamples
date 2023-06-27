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
		// {CF5D9AD0-4C5F-4166-A0FA-7F788A615605}
		static const Extension::TSinkIID IID_DataTagProvider = { 0xcf5d9ad0, 0x4c5f, 0x4166, { 0xa0, 0xfa, 0x7f, 0x78, 0x8a, 0x61, 0x56, 0x5 } };

		class DYNAMIC_ATTRIBUTE IDataTagProvider : public Extension::IEventSink
		{
		public:
			virtual VCOMError		VCOM_CALLTYPE GetObjectUID(MCObjectHandle hObject, size_t& outUID) = 0;
		};
	}
}