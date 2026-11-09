#pragma once

using namespace VectorWorks::Extension;

namespace TesterModule
{
	// {99882619-E31D-4cef-8040-AA5E47F458AE}
	static const VWIID IID_UpdateSupport = { 0x99882619, 0xe31d, 0x4cef, { 0x80, 0x40, 0xaa, 0x5e, 0x47, 0xf4, 0x58, 0xae } };

	class CUpdateSupport : public VCOMImmediateImpl<IObjUpdateSupport>
	{
	public:
					CUpdateSupport(CallBackPtr);
		virtual		~CUpdateSupport();

	// IObjUpdateSupport
	public:
		virtual void VCOM_CALLTYPE	Init(IObjUpdateSupportContext* pContext);
		virtual void VCOM_CALLTYPE	OnState(IObjUpdateSupportContext* pContext, const ObjectState& state);
		virtual void VCOM_CALLTYPE	OnNotification(IObjUpdateSupportContext* pContext);
		virtual EWeilerOperationResult 	VCOM_CALLTYPE OnWeilerOperation(IObjUpdateSupportContext* pContext);

	private:
		TParametricFileIndex	fOnState_MyObjIndex;
		TParametricFileIndex	fOnWeiler_MyObjIndex;
	};
}