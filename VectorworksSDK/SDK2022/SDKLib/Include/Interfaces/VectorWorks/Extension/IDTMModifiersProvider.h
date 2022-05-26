//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "../Math/IPolyDef.h"
#include "IExtension.h"
#include "IDTMTIN.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		enum EDTMModifierType
		{
			eDTMModifierType_Boundary,
			eDTMModifierType_Pad,
			eDTMModifierType_DataPoints,
			eDTMModifierType_Grader,
			eDTMModifierType_TextureBed,
			eDTMModifierType_AreaGrading,
			eDTMModifierType_AreaPadding
		};

		// ----------------------------------------------------------------------------------------------------
		// {6B397D06-A98B-4eaa-85FE-228E30C13CED}
		static const Extension::TSinkIID IID_DTMModifiersProvider = { 0x6b397d06, 0xa98b, 0x4eaa, { 0x85, 0xfe, 0x22, 0x8e, 0x30, 0xc1, 0x3c, 0xed } };

		class DYNAMIC_ATTRIBUTE IDTMModifiersProvider : public Extension::IEventSink
		{
		public:
			virtual Uint32				VCOM_CALLTYPE GetCount(MCObjectHandle hParametric) = 0;
			virtual EDTMModifierType	VCOM_CALLTYPE GetType(Uint32 index) = 0;
			virtual ETINType			VCOM_CALLTYPE GetApplyTo(Uint32 index) = 0;
			virtual void				VCOM_CALLTYPE GetPolygon(Uint32 index, VectorWorks::Math::IPolyDef* polygon) = 0;
			virtual WorldCoord			VCOM_CALLTYPE GetRise(Uint32 index)				{ return 0; }
			virtual InternalIndex		VCOM_CALLTYPE GetTextureIndex(Uint32 index)		{ return 0; }
		};
	}
}

