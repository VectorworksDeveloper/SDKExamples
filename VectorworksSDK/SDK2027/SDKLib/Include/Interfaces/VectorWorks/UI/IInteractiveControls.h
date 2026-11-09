//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "Interfaces/VectorWorks/Imaging/ICompressedImage.h"

namespace VectorWorks
{
	namespace UI
	{
		// ----------------------------------------------------------------------------------------------------
		// A base class for interactive on-drawing controls
		class DYNAMIC_ATTRIBUTE IInteractiveControl : public IVWUnknown
		{
		public:
			virtual bool		VCOM_CALLTYPE	IsInitialized() = 0;

			virtual ViewPt		VCOM_CALLTYPE	GetOffset() = 0;
			virtual void		VCOM_CALLTYPE	SetOffset(const ViewPt& offset) = 0;

			virtual VCOMError	VCOM_CALLTYPE	GetPosition(ViewPt& position) = 0;
			virtual VCOMError	VCOM_CALLTYPE	GetPosition(WorldPt3& position) = 0;
			virtual VCOMError	VCOM_CALLTYPE	SetPosition(const ViewPt& position) = 0;
			virtual VCOMError	VCOM_CALLTYPE	SetPosition(const WorldPt3& position) = 0;

			virtual VCOMError	VCOM_CALLTYPE	GetVisibility(bool& isVisible) = 0;
			virtual VCOMError	VCOM_CALLTYPE	SetVisibility(bool isVisible) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {BF1604BA-65CD-4CD3-A5B4-518A6D284435}
		static const VWIID IID_InteractiveButton = { 0xbf1604ba, 0x65cd, 0x4cd3, { 0xa5, 0xb4, 0x51, 0x8a, 0x6d, 0x28, 0x44, 0x35 } };

		class DYNAMIC_ATTRIBUTE IInteractiveButton : public IInteractiveControl
		{
		public:
			typedef std::function<void()> TClickHandler;
			virtual bool		VCOM_CALLTYPE	Create(const ViewPt& position,		TClickHandler clickHandler, Imaging::ICompressedImage* image, Imaging::ICompressedImage* mouseDownImage = nullptr, Imaging::ICompressedImage* mouseOverImage = nullptr) = 0;
			virtual bool		VCOM_CALLTYPE	Create(const WorldPt3& position,	TClickHandler clickHandler, Imaging::ICompressedImage* image, Imaging::ICompressedImage* mouseDownImage = nullptr, Imaging::ICompressedImage* mouseOverImage = nullptr) = 0;

			virtual VCOMError	VCOM_CALLTYPE	SetClickHandler(TClickHandler clickHandler) = 0;

			virtual VCOMError	VCOM_CALLTYPE	SetImage(Imaging::ICompressedImage* image) = 0;
			virtual VCOMError	VCOM_CALLTYPE	SetMouseDownImage(Imaging::ICompressedImage* image) = 0;
			virtual VCOMError	VCOM_CALLTYPE	SetMouseOverImage(Imaging::ICompressedImage* image) = 0;
		};

		typedef VCOMPtr<IInteractiveButton>		IInteractiveButtonPtr;

		// ----------------------------------------------------------------------------------------------------
		// {7A3D9C21-E8F4-4B6A-9D12-5E8C3A7F6B04}
		static const VWIID IID_OnscreenDisplay = { 0x7a3d9c21, 0xe8f4, 0x4b6a, { 0x9d, 0x12, 0x5e, 0x8c, 0x3a, 0x7f, 0x6b, 0x04 } };

		struct OnscreenTextData
		{
			TXString	string;
			DPFont		font;
			GSColor		color			= kGSColorBlack;
			OpacityRef	opacity			= kMaxOpacity;
			Sint16		edgePadding		= 2;
		};

		class DYNAMIC_ATTRIBUTE IOnscreenDisplay : public IInteractiveControl
		{
		public:
			virtual bool		VCOM_CALLTYPE	Create(const ViewPt& position,		const OnscreenTextData& textData) = 0;
			virtual bool		VCOM_CALLTYPE	Create(const WorldPt3& position,	const OnscreenTextData& textData) = 0;

			virtual bool		VCOM_CALLTYPE	SetDisplay(const OnscreenTextData& textData) = 0;

			virtual ViewRect	VCOM_CALLTYPE	GetDisplayBounds() = 0;
		};

		typedef VCOMPtr<IOnscreenDisplay>	IOnscreenDisplayPtr;
	}
}
