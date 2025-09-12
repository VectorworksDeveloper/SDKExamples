#pragma once

namespace Updater
{
	// {702697C0-9A0F-4E36-9B41-4F3CA7FB80AD}
	static const VWIID IID_UpdateSupport = { 0x702697c0, 0x9a0f, 0x4e36, { 0x9b, 0x41, 0x4f, 0x3c, 0xa7, 0xfb, 0x80, 0xad } };

	using namespace VectorWorks::Extension;

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

	private:
		TParametricFileIndex	fOnState_WallObjIndex;
		TParametricFileIndex	fOnState_RWallObjIndex;
		TParametricFileIndex	fOnState_SlabObjIndex;
		TParametricFileIndex	fOnState_Slab2ObjIndex;
		TParametricFileIndex	fOnState_LayerObjIndex;
		TParametricFileIndex	fOnState_MyObjIndex;
	};
}