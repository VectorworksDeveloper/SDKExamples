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
		struct SStandardReshapeGroup
		{
			short	fEditModeIndex		= 0;
			short	fVertexTypeIndex	= 0;
			short	fMarqueeIndex		= 0;
			short	fOptionsIndex		= 0;
		};

		// ----------------------------------------------------------------------------------------------------
		struct SStandardReshapeFunctionality
		{
			void	Init()
			{
				fIsStandardObjGripsUsed		= false;
				fIsStandardCursorUsed		= false;
				fIsStandardPointAddedUsed	= false;
				fIsStandardMouseMoveUsed	= false;
				fIsStandardPointRemovedUsed	= false;
				fIsStandardStatusUsed		= false;
				fIsStandardModeChangedUsed	= false;
				fIsStandardCompleteUsed		= false;
				fIsStandartHelpTextUsed		= false;
				fIsStandardDeleteUsed		= false;
				fIsStandardModeGroupsUsed	= true;
			};

			bool	fIsStandardObjGripsUsed		= false;
			bool	fIsStandardCursorUsed		= false;
			bool	fIsStandardPointAddedUsed	= false;
			bool	fIsStandardMouseMoveUsed	= false;
			bool	fIsStandardPointRemovedUsed	= false;
			bool	fIsStandardStatusUsed		= false;
			bool	fIsStandardModeChangedUsed	= false;
			bool	fIsStandardCompleteUsed		= false;
			bool	fIsStandartHelpTextUsed		= false;
			bool	fIsStandardDeleteUsed		= false;
			bool	fIsStandardModeGroupsUsed	= false;
		};

		// ----------------------------------------------------------------------------------------------------
		// {D17B2474-EB30-4B43-B9E3-C6B5223E76F8}
		static const TSinkIID IID_ProviderCustomReshape = { 0xd17b2474, 0xeb30, 0x4b43, { 0xb9, 0xe3, 0xc6, 0xb5, 0x22, 0x3e, 0x76, 0xf8 } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderCustomReshape : public IEventSink
		{
		public:
			virtual bool	VCOM_CALLTYPE IsCustomised() = 0;
			virtual void	VCOM_CALLTYPE SetupModes(short reshapeType, short vertexType, short marqueeType) = 0;
			virtual void	VCOM_CALLTYPE ModeChanged(Sint32 modeGroup, short newMode, short oldMode, SReshapeData& ioReshapeData) = 0;
			virtual void	VCOM_CALLTYPE OnSelectionChanged() = 0;
			virtual void	VCOM_CALLTYPE Deactivate() = 0;
			virtual void	VCOM_CALLTYPE OnComplete() = 0;	
			virtual void	VCOM_CALLTYPE OnDelete() {}

			virtual bool	VCOM_CALLTYPE HasObjGrips(bool isMultiSel){ return false; }
			virtual Sint32	VCOM_CALLTYPE GetCursor(){ return 0; }
			virtual bool	VCOM_CALLTYPE OnPointAdded(){ return false; }
			virtual bool	VCOM_CALLTYPE OnMouseMove(){ return false; }
			virtual void	VCOM_CALLTYPE OnPointRemoved(){}
			virtual Sint32	VCOM_CALLTYPE GetStatus(){ return 0; }
			virtual void	VCOM_CALLTYPE Init(SStandardReshapeGroup& outGroups, SStandardReshapeFunctionality& outFunctionality){ outFunctionality.Init(); }
			virtual void	VCOM_CALLTYPE HandleCustomBarEvent(const CustomBarEventData& eventData){}
			virtual void	VCOM_CALLTYPE SetMarqeeSelectionPoly( MCObjectHandle hMarqeeSelection ) {}
		};
	}
}
