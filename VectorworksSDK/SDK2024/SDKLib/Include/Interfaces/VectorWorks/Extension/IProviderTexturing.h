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
		// {F771248D-8A8A-4663-89EF-0ED6A3FF0849}
		static const TSinkIID IID_ProviderTexturing = { 0xf771248d, 0x8a8a, 0x4663, { 0x89, 0xef, 0x0e, 0xd6, 0xa3, 0xff, 0x08, 0x49 } };

		enum class ETexturingModes {
			ObjectTextures = 0,
			ComponentTextures,
			BothModes,
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderTexturing : public IEventSink
		{
		public:
			// Sint32 partCategoryID == 0 means for the object as a whole
			virtual MCObjectHandle VCOM_CALLTYPE		GetPartCategoryComponents(MCObjectHandle hObj, Sint32 partCategoryID) const	{ return nullptr; }
			
			virtual short VCOM_CALLTYPE	GetPartCategoryTexturingMode(MCObjectHandle hObj, Sint32 partCategoryID = 0) const { return 0; }
			virtual void VCOM_CALLTYPE		SetPartCategoryTexturingMode(MCObjectHandle hObj, short textureMode, Sint32 partCategoryID = 0) {  }

			virtual ETexturingModes	VCOM_CALLTYPE GetCanUseTexturingModes(MCObjectHandle h, Sint32 partCategoryID = 0) const { return ETexturingModes::ObjectTextures; }

			virtual MCObjectHandle VCOM_CALLTYPE  GetTexturableObjectInsideParametric(MCObjectHandle hObj, Sint32 partID, Sint32 partCategoryID) const { return nullptr; }

			virtual bool VCOM_CALLTYPE SetDefaultMapping(MCObjectHandle hObj, Sint32 partID, Sint32 partCategoryID, TextureMappingInfoSDK& mappingInfo) { return false; }

			// this should return maximum possible number of a part for the given category;
			// components will be added to the Texture table with indices = maximum_part_number + 1 + component_index
			virtual Uint32 VCOM_CALLTYPE	GetMaximumPartID(MCObjectHandle hObj, Sint32 partCategoryID = 0) const { return 1; }

			virtual bool VCOM_CALLTYPE IsCategoryComponentsByStyle(MCObjectHandle hObj, Sint32 partCategoryID) const { return false; }

		};
	}
}