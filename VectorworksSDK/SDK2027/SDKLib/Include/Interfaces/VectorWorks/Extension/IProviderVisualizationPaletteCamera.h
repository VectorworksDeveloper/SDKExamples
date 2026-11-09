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
		static const TSinkIID IID_ProviderVisualizationPaletteCamera = { 0x13efaf6e, 0x7710, 0x4a19, { 0xad, 0xa5, 0x4, 0x5f, 0xe6, 0x54, 0xdf, 0xae } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderVisualizationPaletteCamera : public IEventSink
		{
		public:
			virtual void VCOM_CALLTYPE DisplayCameraView( MCObjectHandle hObject )= 0;
            virtual void VCOM_CALLTYPE MatchCurrentView( MCObjectHandle hObject ) = 0;
			virtual void VCOM_CALLTYPE ActivateCamera( MCObjectHandle hObject, Sint32 selPaneID = -1 )   = 0;
			virtual void VCOM_CALLTYPE DeactivateAllCamerasAssocWithLayers( MCObjectHandle hObject ) = 0;
			virtual void VCOM_CALLTYPE DeactivateCamera( MCObjectHandle hObject ) = 0;
			virtual bool VCOM_CALLTYPE IsActiveCamera( MCObjectHandle hObject )   = 0;
			virtual Sint32 VCOM_CALLTYPE GetCameraActivatedOnPane(MCObjectHandle hObject) = 0;
			virtual bool VCOM_CALLTYPE IsValidCameraHandle( MCObjectHandle hObject )	{ return false; };
		};
	}
}
