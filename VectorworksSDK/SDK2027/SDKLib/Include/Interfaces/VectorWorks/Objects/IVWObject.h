//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Objects
	{
		// ---------------------------------------------------------------------------------------------------
		static const VWIID IID_VWObject		= { 0xdb6eb172, 0x7cd5, 0x40cc, { 0xa5, 0xd0, 0x28, 0x70, 0xc7, 0x8f, 0x7b, 0x9c } };

		class DYNAMIC_ATTRIBUTE IVWObject : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	ResetObject(MCObjectHandle hObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteObject(MCObjectHandle hObject, bool bUseUndo) = 0;

			// hierarchy
			virtual VCOMError VCOM_CALLTYPE	AddObjectToContainer(MCObjectHandle hObject, MCObjectHandle hContainer) = 0;
			virtual VCOMError VCOM_CALLTYPE	InsertAfterObject(MCObjectHandle hObject, MCObjectHandle hAfterObj) = 0;
			virtual VCOMError VCOM_CALLTYPE	InsertBeforeObject(MCObjectHandle hObject, MCObjectHandle hBeforeObj) = 0;

			// traversing
			virtual VCOMError VCOM_CALLTYPE	GetNextObject(MCObjectHandle hObject, MCObjectHandle& outHandle) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetPrevObject(MCObjectHandle hObject, MCObjectHandle& outHandle) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetParentObject(MCObjectHandle hObject, MCObjectHandle& outHandle) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetParentLayer(MCObjectHandle hObject, MCObjectHandle& outHandle) = 0;

			virtual VCOMError VCOM_CALLTYPE	IsVisible(MCObjectHandle hObject, bool& outVisible) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetVisible(MCObjectHandle hObject, bool bVisible) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsLocked(MCObjectHandle hObject, bool& outLocked) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetLock(MCObjectHandle hObject, bool bLock) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsSelected(MCObjectHandle hObject, bool& outSelected) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetSelected(MCObjectHandle hObject, bool bSelect) = 0;

			// aux list managment
			virtual VCOMError VCOM_CALLTYPE	AttachAuxObject(MCObjectHandle hObject, MCObjectHandle hAuxObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteAuxObject(MCObjectHandle hObject, MCObjectHandle hAuxObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFirstAuxObject(MCObjectHandle hObject, MCObjectHandle& outHandle) = 0;

			// ...
		};
	}
}