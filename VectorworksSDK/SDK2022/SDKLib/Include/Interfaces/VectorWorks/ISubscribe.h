

#pragma once

namespace VectorWorks
{
	// ---------------------------------------------------------------------------------------------------
	// {be1697fc-b15c-4914-bab6-b4a081f8054f}
	static const VWIID IID_Subscribe =
	{ 0xbe1697fc, 0xb15c, 0x4914, { 0xba, 0xb6, 0xb4, 0xa0, 0x81, 0xf8, 0x05, 0x4f } };

	class DYNAMIC_ATTRIBUTE ISubscribe : public IVWSingletonUnknown
	{
	public:
		
        enum EType { kIsImageFile = 1, kIsPDFFile = 2, kIsPointCloudFile = 4 }; // Must match Objs.NGNodeType.Objects.h
        

		virtual bool VCOM_CALLTYPE AttachFileSubscrbeToObject(MCObjectHandle h, IFileIdentifier* fileID, EType inSubscribeType,
                                                              bool bRefAbsolute = false, bool bRefAutoUpd = false, bool bRefCacheSaved = false) = 0;
        
        virtual bool VCOM_CALLTYPE GetFileNameFromObject(MCObjectHandle h, TXString& outFullPathName) = 0;
	};
}
