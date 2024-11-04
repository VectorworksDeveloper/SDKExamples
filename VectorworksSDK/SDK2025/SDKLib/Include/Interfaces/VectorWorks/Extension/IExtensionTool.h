//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IExtension.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		enum EExtensionToolType
		{
			eExtensionToolType_Normal,
			eExtensionToolType_DefaultPoint,
			eExtensionToolType_DefaultLine,
			eExtensionToolType_DefaultBox,
			eExtensionToolType_Default2DPath,
			eExtensionToolType_Default3DPath,
		};

		// ----------------------------------------------------------------------------------------------------
		enum EToolBarDisplay
		{
			kToolBarDisplay_NoDataBar,          // barDisplay mode
			kToolBarDisplay_XYClLaZo=1,
			kToolBarDisplay_XY,
			kToolBarDisplay_SaAaLAXY,
			kToolBarDisplay_DxDyRaAXY,
			kToolBarDisplay_DxDyTlAXY,
			kToolBarDisplay_DxDyRXY,
			kToolBarDisplay_DxDyLAXY,
			kToolBarDisplay_DxDyArPeXY,
			kToolBarDisplay_A=9,
			kToolBarDisplay_DxDyLOXY,
			kToolBarDisplay_DxDySxSyXY,
			kToolBarDisplay_XYZClLaZo,
			kToolBarDisplay_VxVyVzYaPi=13,
			kToolBarDisplay_Vz,
			kToolBarDisplay_Da,
			kToolBarDisplay_AzEl,
			kToolBarDisplay_AzElRo,
			kToolBarDisplay_VxVyVzLrUdIo,
			kToolBarDisplay_U1Aw,
			kToolBarDisplay_ThXYZ,
			kToolBarDisplay_O1O2WrWhZ,
			kToolBarDisplay_WbWtDz,
			kToolBarDisplay_XYU1,
			kToolBarDisplay_RaRrRuXYZ,
			kToolBarDisplay_ClLaZo,
			kToolBarDisplay_LADxDyXY,
			kToolBarDisplay_kDxDyLAXYForRect = 38,
		};

		// ----------------------------------------------------------------------------------------------------
		// {A90DECBC-4893-48ee-A1B2-CE20E371972C}
		static const VWGroupID GROUPID_ExtensionTool = { 0xa90decbc, 0x4893, 0x48ee, { 0xa1, 0xb2, 0xce, 0x20, 0xe3, 0x71, 0x97, 0x2c } };
		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IExtensionTool : public IExtension
		{
		public:
			virtual EExtensionToolType				GetType() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetTitle() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetCategory() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetHelpText() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetMessageText() = 0;
			virtual const TXString& VCOM_CALLTYPE	GetOverrideHelpID() = 0;
			virtual const TXString&	VCOM_CALLTYPE	GetParametricName() = 0;
			virtual bool VCOM_CALLTYPE				GetPickAndUpdate() = 0;
			virtual bool VCOM_CALLTYPE				GetNeedScreenPlane() = 0;
			virtual bool VCOM_CALLTYPE				GetNeed3DProjection() = 0;
			virtual bool VCOM_CALLTYPE				GetUse2DCursor() = 0;
			virtual bool VCOM_CALLTYPE				GetConstrainCursor() = 0;
			virtual bool VCOM_CALLTYPE				GetNeedPerspective() = 0;
			virtual bool VCOM_CALLTYPE				GetShowScreenHints() = 0;
			virtual bool VCOM_CALLTYPE				GetNeedsPlanarContext() = 0;
			virtual void VCOM_CALLTYPE				GetIconSpec(TXString& outIconSpec) = 0;
			virtual void VCOM_CALLTYPE				GetDefaultCursorImageSpec(TXString& outImageSpec) = 0;
			virtual Sint16 VCOM_CALLTYPE			GetWaitMoveDistance() = 0;
			virtual Sint16 VCOM_CALLTYPE			GetConstraintFlags() = 0;
			virtual EToolBarDisplay VCOM_CALLTYPE	GetBarDisplay() = 0;
			virtual	Sint16 VCOM_CALLTYPE			GetMinimumCompatibleVersion() = 0;
			virtual	void VCOM_CALLTYPE				GetVersionInfo(Uint16& outCreated, Uint16& outModified, Uint16& outRetired) = 0;
		};
	}
}
