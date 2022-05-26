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
		struct SReshapeData
		{
			short	fReshapeType;
			short	fVertexType;
			short	fMarqueeType;
		};

		// ----------------------------------------------------------------------------------------------------
		// {D88CAFE4-C4A2-47DD-AE71-75708C6C6FEF}
		static const TSinkIID IID_ProviderReshape = { 0xd88cafe4, 0xc4a2, 0x47dd, { 0xae, 0x71, 0x75, 0x70, 0x8c, 0x6c, 0x6f, 0xef } };

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IProviderReshape : public IEventSink
		{
		public:
			virtual void	VCOM_CALLTYPE	SetupModes(TXStringArray& outIcons, TVWModeBarButtonHelpArray& outHelps)	= 0;
			virtual void	VCOM_CALLTYPE	ModeChanged(Sint32 modeGroup, short newMode, short oldMode, SReshapeData& ioReshapeData)									= 0;
			virtual void	VCOM_CALLTYPE	ActivateMode(short mode, short reshapeType, bool hasMarquee, short& currentGroupIndex, TVWModeBarButtonHelpArray& outHelps)	= 0;
			virtual void	VCOM_CALLTYPE	Deactivate()																= 0;
			virtual Sint32	VCOM_CALLTYPE	GetStatus(short mode)														= 0;
			virtual Sint32	VCOM_CALLTYPE	GetCursor(short mode, short reshapeType)									= 0;
			virtual bool	VCOM_CALLTYPE	OnPointAdded(short mode)													= 0;
			virtual void	VCOM_CALLTYPE	OnPointRemoved(short mode)													= 0;
			virtual bool	VCOM_CALLTYPE	OnMouseMove(short mode)														= 0;
			virtual void	VCOM_CALLTYPE	OnSelectionChanged(short mode)												= 0;
			virtual bool	VCOM_CALLTYPE	OnDelete( short mode )														{ return false; }
			virtual bool	VCOM_CALLTYPE	OnComplete( short mode )													{ return false; }
			virtual void	VCOM_CALLTYPE	SetMultipleReshapePoly( MCObjectHandle hMultipleReshape )					{}

		// VW2021
		public:
			virtual bool	VCOM_CALLTYPE	IsCustomized()																{ return true; }

		// VW2022
		public:
			virtual bool	VCOM_CALLTYPE	IsModeCustomized(short mode)												{ return true; };
		};
	}
}