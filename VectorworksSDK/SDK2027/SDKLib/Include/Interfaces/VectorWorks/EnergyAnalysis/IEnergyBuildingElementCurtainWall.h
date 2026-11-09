//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace EnergyAnalysis
	{
		// ----------------------------------------------------------------------------------------------------
		// {3E89AE10-4BAE-4546-81E2-1F59361A9F15}
		static const VWIID IID_EnergyCurtainWallFrame = { 0x3e89ae10, 0x4bae, 0x4546, { 0x81, 0xe2, 0x1f, 0x59, 0x36, 0x1a, 0x9f, 0x15 } };

		class DYNAMIC_ATTRIBUTE IEnergyCurtainWallFrame : public IVWUnknown
		{
		public:
			// tools
			// This function will return true, if the handle has a property energy data.
			virtual bool    VCOM_CALLTYPE IsHandleContainingData(MCObjectHandle h) = 0;
			// This function will delete the energy data from the handle.
			virtual void    VCOM_CALLTYPE DeleteDataFromHandle(MCObjectHandle h) = 0;

		public:
			virtual MCObjectHandle		VCOM_CALLTYPE Get() = 0;

			//This function will load energy data from the handle, if it has data,
			//or this function will load default energy data, if the handle does not have energy data.
			virtual void				VCOM_CALLTYPE LoadCreate(MCObjectHandle h) = 0;

			virtual bool				VCOM_CALLTYPE Save() = 0;	// Must be called after Set operations

			virtual void				VCOM_CALLTYPE CopyDataTo(MCObjectHandle h) = 0;
			virtual void				VCOM_CALLTYPE CopyInterfaceDataFrom(IEnergyCurtainWallFrame* interfaceData) = 0;

			virtual double				VCOM_CALLTYPE GetArea() = 0;				// sq m
			virtual void				VCOM_CALLTYPE SetArea(double value) = 0;	// sq m

			// This is total length of frame that is connected with panel.
			virtual double				VCOM_CALLTYPE GetConnectedPanelLength() = 0;				// m
			virtual void				VCOM_CALLTYPE SetConnectedPanelLength(double value) = 0;	// m

			// This is total length of frame that is not connected with anything in this wall.
			// For example: if it is start frame, this is left part(length) of the frame.
			virtual double				VCOM_CALLTYPE GetNotConnectedLength() = 0;					// m
			virtual void				VCOM_CALLTYPE SetNotConnectedLength(double value) = 0;		// m

			virtual bool				VCOM_CALLTYPE DialogUI_EditEnergyAnalysisDlg() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyCurtainWallFrame>		IEnergyCurtainWallFramePtr;

		// ----------------------------------------------------------------------------------------------------
		// {4B4F66D1-717E-41D3-A2F2-BAC2432E7550}
		static const VWIID IID_EnergyCurtainWallPanel = { 0x4b4f66d1, 0x717e, 0x41d3, { 0xa2, 0xf2, 0xba, 0xc2, 0x43, 0x2e, 0x75, 0x50 } };

		class DYNAMIC_ATTRIBUTE IEnergyCurtainWallPanel : public IVWUnknown
		{
		public:
			// tools
			// This function will return true, if the handle has a property energy data.
			virtual bool    VCOM_CALLTYPE IsHandleContainingData(MCObjectHandle h) = 0;
			// This function will delete the energy data from the handle.
			virtual void    VCOM_CALLTYPE DeleteDataFromHandle(MCObjectHandle h) = 0;

		public:
			virtual MCObjectHandle		VCOM_CALLTYPE Get() = 0;

			//This function will load energy data from the handle, if it has data,
			//or this function will load default energy data, if the handle does not have energy data.
			virtual void				VCOM_CALLTYPE LoadCreate(MCObjectHandle h) = 0;

			virtual bool				VCOM_CALLTYPE Save() = 0;	// Must be called after Set operations

			virtual void				VCOM_CALLTYPE CopyDataTo(MCObjectHandle h) = 0;
			virtual void				VCOM_CALLTYPE CopyInterfaceDataFrom(IEnergyCurtainWallPanel* interfaceData) = 0;

			virtual double				VCOM_CALLTYPE GetArea() = 0;				// sq m
			virtual void				VCOM_CALLTYPE SetArea(double value) = 0;	// sq m

			virtual bool				VCOM_CALLTYPE DialogUI_EditEnergyAnalysisDlg() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyCurtainWallPanel>		IEnergyCurtainWallPanelPtr;

		// ----------------------------------------------------------------------------------------------------
		// {52C7E978-9D52-4B5E-B120-95D7DC03E256}
		static const VWIID IID_EnergyBuildingElementCurtainWall = { 0x52c7e978, 0x9d52, 0x4b5e, { 0xb1, 0x20, 0x95, 0xd7, 0xdc, 0x03, 0xe2, 0x56 } };

		class DYNAMIC_ATTRIBUTE IEnergyBuildingElementCurtainWall : public IVWUnknown
		{
		public:
			// tools
			// This function will return true, if the handle has a property energy data.
			virtual bool    VCOM_CALLTYPE IsHandleContainingData(MCObjectHandle h) = 0;
			// This function will delete the energy data from the handle.
			virtual void    VCOM_CALLTYPE DeleteDataFromHandle(MCObjectHandle h) = 0;

		public:
			virtual MCObjectHandle		VCOM_CALLTYPE Get() = 0;

			//This function will load energy data from the handle, if it has data,
			//or this function will load default energy data, if the handle does not have energy data.
			virtual void				VCOM_CALLTYPE LoadCreate(MCObjectHandle h) = 0;

			virtual bool				VCOM_CALLTYPE Save() = 0;	// Must be called after Set operations

			virtual void				VCOM_CALLTYPE CopyDataTo(MCObjectHandle h) = 0;
			virtual void				VCOM_CALLTYPE CopyInterfaceDataFrom(IEnergyBuildingElementCurtainWall* interfaceData) = 0;

			virtual TXString			VCOM_CALLTYPE GetName(bool useOriginal) = 0;
			virtual void				VCOM_CALLTYPE SetName(const TXString & value, bool toOriginal) = 0;

			virtual double				VCOM_CALLTYPE GetArea(bool useOriginal) = 0;				// sq m
			virtual void				VCOM_CALLTYPE SetArea(double value, bool toOriginal) = 0;	// sq m

			virtual double				VCOM_CALLTYPE GetUValue(bool useOriginal) = 0;				// W/(m^2 K)
			virtual bool				VCOM_CALLTYPE GetIncludeInEnergyAnalysis() = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IEnergyBuildingElementCurtainWall>		IEnergyBuildingElementCurtainWallPtr;
	}
}
