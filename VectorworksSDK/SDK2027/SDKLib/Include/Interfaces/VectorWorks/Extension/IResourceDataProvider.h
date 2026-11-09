//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		struct SResourceData
		{
			InternalIndex	fRefNum;
			TDType			fType;
		};
		typedef std::vector<SResourceData>							TResourceDataArray;
		typedef std::function<InternalIndex(InternalIndex refNum)>	TMapperCallback;

		// ----------------------------------------------------------------------------------------------------
		// {01AF4140-E518-4322-A691-32D71584DE71}
		static const Extension::TSinkIID IID_ResourceDataProvider = { 0x1af4140, 0xe518, 0x4322, { 0xa6, 0x91, 0x32, 0xd7, 0x15, 0x84, 0xde, 0x71 } };

		class DYNAMIC_ATTRIBUTE IResourceDataProvider : public Extension::IEventSink
		{
		public:
			virtual VCOMError VCOM_CALLTYPE GetReferencedResources(MCObjectHandle hObject, TResourceDataArray& outResourceDataArray) const = 0;
			virtual VCOMError VCOM_CALLTYPE	MapReferencedResources(MCObjectHandle hObject, TMapperCallback mapper) = 0;
			virtual VCOMError VCOM_CALLTYPE UpdateReferencedResource(MCObjectHandle hObject, TDType type, InternalIndex oldIndex, InternalIndex newIndex) = 0;
		};
	}
}
