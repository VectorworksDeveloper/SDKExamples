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
		// {B9E1E261-B7CB-4a0e-8170-6E26F2663CF5}
		static const TSinkIID IID_ProviderReshape3D = { 0xb9e1e261, 0xb7cb, 0x4a0e, { 0x81, 0x70, 0x6e, 0x26, 0xf2, 0x66, 0x3c, 0xf5 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderReshape3D : public IEventSink
		{
		public:
			virtual bool VCOM_CALLTYPE		UseStandardReshape(MCObjectHandle h)						{ return false; }

			virtual void VCOM_CALLTYPE		SelectionPrepare(bool bRestore, MCObjectHandle hObj)		{  }
			virtual void VCOM_CALLTYPE		SelectionUnPrepare(bool bRestore)							{  }
			virtual void VCOM_CALLTYPE		Cancel() = 0;

			virtual void VCOM_CALLTYPE		GetStatus(Sint32& outStatus)								{  }
			virtual Sint32 VCOM_CALLTYPE	GetCursorID() = 0;
			virtual void VCOM_CALLTYPE		UpdateHightlightStatus(Sint16 pickIndex)					{  }

			virtual void VCOM_CALLTYPE		SetupModeBar()												{  }
			virtual void VCOM_CALLTYPE		ModeEvent(Sint32 modeGroup, Sint16 newMode, Sint16 oldMode)	{  }
			virtual void VCOM_CALLTYPE		SecondModeEvent(Sint16 mode)								{  }
			virtual void VCOM_CALLTYPE		HandleCustomBarEvent(const CustomBarEventData& eventData)	{  }

			virtual void VCOM_CALLTYPE		MouseDown(Sint16 pickIndex)									{  }
			virtual void VCOM_CALLTYPE		MouseMove()													{  }
			virtual void VCOM_CALLTYPE		Draw() = 0;
			virtual void VCOM_CALLTYPE		Complete() = 0;

			virtual void VCOM_CALLTYPE		HandleScreenModUndraw()										{  }
			virtual void VCOM_CALLTYPE		HandleScreenModRedraw()										{  }

			virtual bool VCOM_CALLTYPE		AllowMarqueeReshape(MCObjectHandle h)						{ return false; }
			virtual void VCOM_CALLTYPE		SetMarqueeReshapeIndices(std::vector<Sint16> arrPickIndices){  }
			virtual bool VCOM_CALLTYPE		GetReshapePoints(std::vector<WorldPt3>& outReshapePoints)	{ return false; }

			virtual void VCOM_CALLTYPE		CustomModeEvent(Sint32 modeGroup, Sint16 newMode, Sint16 oldMode)	{  }
		};
	}
}