//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ---------------------------------------------------------------------------------------------------
		// {EC5AEC68-5202-4BD1-81B0-C8F497D0DCEF}
		static const VWIID IID_RenderworksCameraDataProvider = { 0xec5aec68, 0x5202, 0x4bd1, { 0x81, 0xb0, 0xc8, 0xf4, 0x97, 0xd0, 0xdc, 0xef } };
		struct CameraParameters{
			TXString   name;
			
			TransformMatrix viewMatrix;
			WorldPt3  viewMatrix_iVec; // this is Column 0 of the matrix, for more convenience
			WorldPt3  viewMatrix_jVec; // this is Column 1 of the matrix,
			WorldPt3  viewMatrix_kVec; // this is Column 2 of the matrix,
			WorldPt3  viewMatrix_offset;
			
			WorldPt3   position;
			WorldPt3   lookToPos;
			
			double	   roll;

			// these are interlinked
			double     focalLenght; 
			double     aperture; //a.k.a Film Size /Sensor Size/ Film Gate
			double     fov;
			
			/*************************
			   Physical Camera properties
			***************************/			
			// depth of field
			bool       dof;
			double     focusDistance;
			double     fStop;
			Uint8      bokehShapeBlades;
			//bool       bokehEffect;
			double     bokehBias; // we set this internally not the user
			
			// exposure
			bool       exposure;
			double     ISO_FilmSpeed;
			double     shutterSpeed;

			double     bloomIntensity; //Glow
			double     chromaticAberration;
			double     vignettingIntensity;
			double     vignettingOffset;
			
			Sint32		fPaneID;	// bind this camera to a viewpane


		};

		class DYNAMIC_ATTRIBUTE IRenderworksCameraDataProvider : public IEventSink
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE    Init(MCObjectHandle cameraHandle) = 0;

			virtual VCOMError	VCOM_CALLTYPE    GetCameraProperties(CameraParameters& prop) =0;

			virtual void    	VCOM_CALLTYPE    SetCameraViewRect( MCObjectHandle cameraHandle, const ViewRect& cameraViewRect) = 0;

			virtual void    	VCOM_CALLTYPE    GetCameraViewRect( MCObjectHandle cameraHandle, ViewRect& cameraViewRect) = 0;

			virtual double		VCOM_CALLTYPE	 GetPerspectiveDistance( MCObjectHandle cameraHandle ) = 0;

			virtual VCOMError	VCOM_CALLTYPE	 BindToViewPane(MCObjectHandle cameraHandle, int selPaneID) = 0;

			virtual VCOMError	VCOM_CALLTYPE	 GetBoundViewPane(MCObjectHandle cameraHandle, int& selPaneID) = 0;

		};
		
		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IRenderworksCameraDataProvider> IRenderworksCameraDataProviderPtr;
	}
}