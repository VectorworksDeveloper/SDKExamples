//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IDrawPad.h"

namespace VectorWorks
{
	// ----------------------------------------------------------------------------------------------------
	// {5DB83A55-7B33-4D51-9B4A-3E31B8861383}
	static const VWIID IID_ScreenDrawPad = { 0x5db83a55, 0x7b33, 0x4d51, { 0x9b, 0x4a, 0x3e, 0x31, 0xb8, 0x86, 0x13, 0x83 } };
	
	class DYNAMIC_ATTRIBUTE IScreenDrawPad : public IDrawPad
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		Initialize() = 0;	// a corresponding Deinitialize must be called
		virtual VCOMError VCOM_CALLTYPE		Initialize(const ViewRect& rect) = 0;
		virtual VCOMError VCOM_CALLTYPE		Deinitialize() = 0;

		virtual VCOMError VCOM_CALLTYPE		SaveView(MCObjectHandle hLayer) = 0;
		virtual VCOMError VCOM_CALLTYPE		RestoreView(MCObjectHandle hLayer) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetScreenSize(ViewRect& outRect) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetViewCenter(WorldPt& outScreenPt) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetViewCenter(const WorldPt& screenPt) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetViewZoom(double& outZoom) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetViewZoom(double zoom) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetViewMatrix(MCObjectHandle hLayer, TransformMatrix& outMatrix) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetViewMatrix(MCObjectHandle hLayer, const TransformMatrix& matrix) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetViewProjection(MCObjectHandle hLayer, TProjection& outProjection) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetViewProjection(MCObjectHandle hLayer, TProjection projection) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetPerspective(TProjection projection, TRenderMode renderMode, WorldCoord persDistance, const WorldPt &pt1, const WorldPt &pt2) = 0;
	
		virtual VCOMError VCOM_CALLTYPE		SetView(MCObjectHandle hLayer, const WorldPt3& lookVector, const WorldPt3& viewPoint, const WorldPt3& upVector) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetView(MCObjectHandle hLayer, const TransformMatrix& viewMatrix) = 0;
			
		virtual VCOMError VCOM_CALLTYPE		DrawScreen(bool lastFrame) = 0;
		virtual VCOMError VCOM_CALLTYPE		DrawScreen(const ViewRect& rect, bool lastFrame) = 0;
	};

	// ----------------------------------------------------------------------------------------------------
	typedef VCOMPtr<IScreenDrawPad>		IScreenDrawPadPtr;
}
