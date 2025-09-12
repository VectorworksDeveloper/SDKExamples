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
		// {F8BC3FE2-8A87-4CCD-8195-A34A8CDCE7D1}
		static const TSinkIID IID_SubpartRepresentationMapping =
		{ 0xf8bc3fe2, 0x8a87, 0x4ccd, { 0x81, 0x95, 0xa3, 0x4a, 0x8c, 0xdc, 0xe7, 0xd1 } };

		// ----------------------------------------------------------------------------------------------------
		//
		// The purpose of this interface is enabling PIOs to serve as "views" for a collection of defining Objects.
		//
		// The immediate motivation is for Door and Window Assembly objects to support Data Tags. In order to control how DWA
		// objects display in Top/Plan, they do not contain any actual Door or Window objects in their child lists, but users
		// must be able to attach Data Tags to the Door and Window objects comprising the Assembly.
		//
		// By implementing this Sink, the DWA and similar plug-ins can accept a piece of "View" geometry selected by the Data
		// Tag Tool and provide a different, "Model" object used to generate that presentation geometry.
		class DYNAMIC_ATTRIBUTE ISubpartRepresentationMapping : public IEventSink
		{
		public:
			virtual MCObjectHandle MapSubpart( MCObjectHandle hObject, MCObjectHandle hPickedGeometry ) = 0;
			virtual std::vector<MCObjectHandle> GetTaggableSubparts( MCObjectHandle hObject ) = 0;
		};
	}
}
