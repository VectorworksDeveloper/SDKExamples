#pragma once

namespace Advanced
{
	using namespace VectorWorks::Extension;

	// ------------------------------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE CAdvComplexReshape3D : public VCOMImpl<IProviderReshape3D>
	{
	public:
						CAdvComplexReshape3D(IVWUnknown* parent);
		virtual			~CAdvComplexReshape3D();

	// IProviderReshape3D
	public:
		virtual void VCOM_CALLTYPE		SelectionPrepare(bool bRestore, MCObjectHandle hObj);
		virtual void VCOM_CALLTYPE		SelectionUnPrepare(bool bRestore);
		virtual void VCOM_CALLTYPE		Cancel();

		virtual void VCOM_CALLTYPE		GetStatus(Sint32& outStatus);
		virtual Sint32 VCOM_CALLTYPE	GetCursorID();
		virtual void VCOM_CALLTYPE		UpdateHightlightStatus(Sint16 pickIndex);

		virtual void VCOM_CALLTYPE		SetupModeBar();
		virtual void VCOM_CALLTYPE		ModeEvent(Sint32 modeGroup, Sint16 newMode, Sint16 oldMode);
		virtual void VCOM_CALLTYPE		HandleCustomBarEvent(const CustomBarEventData& eventData);

		virtual void VCOM_CALLTYPE		MouseDown(Sint16 pickIndex);
		virtual void VCOM_CALLTYPE		MouseMove();
		virtual void VCOM_CALLTYPE		Draw();
		virtual void VCOM_CALLTYPE		Complete();
	};
}
