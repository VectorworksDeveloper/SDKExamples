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
		// {49A9B78A-9227-4E06-84AD-B8B76F544B70}
		static const TSinkIID IID_ProviderPathGroups = { 0x49a9b78a, 0x9227, 0x4e06, { 0x84, 0xad, 0xb8, 0xb7, 0x6f, 0x54, 0x4b, 0x70 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderPathGroups : public IEventSink
		{
		public:
			virtual bool			VCOM_CALLTYPE	IsCustomPathActive(MCObjectHandle hObject, bool isForReshape = true) = 0;

			virtual	MCObjectHandle	VCOM_CALLTYPE	GetCustomGroup(MCObjectHandle hObject) = 0;
			virtual MCObjectHandle	VCOM_CALLTYPE	GetCustomPath(MCObjectHandle hObject, bool bAuxTransformed = false) = 0;
			virtual void			VCOM_CALLTYPE	SetCustomPath(MCObjectHandle hObject, MCObjectHandle hPath, bool isInGlobalCoordinates = true) = 0;
			virtual void			VCOM_CALLTYPE	DeleteTransformedPath(MCObjectHandle hObject) = 0;

			virtual void			VCOM_CALLTYPE	VerifyReshapePath(MCObjectHandle hObject, MCObjectHandle hPath, short vertexID = 0) {}
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IProviderPathGroups> IProviderPathGroupsPtr;
	}
}
