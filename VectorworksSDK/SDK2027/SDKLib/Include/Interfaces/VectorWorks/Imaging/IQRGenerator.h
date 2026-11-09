//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Imaging
	{
		// ------------------------------------------------------------------------------------------------------------------------------------
		// {4A8BC4F8-42E9-4BD5-B9D8-7658E53BD32E}
		static const VWIID IID_QRGenerator = { 0x4a8bc4f8, 0x42e9, 0x4bd5, { 0xb9, 0xd8, 0x76, 0x58, 0xe5, 0x3b, 0xd3, 0x2e } };

		class DYNAMIC_ATTRIBUTE IQRGenerator : public IVWUnknown
		{
		public:
			virtual void	VCOM_CALLTYPE GenerateQR(const TXString& text) = 0;

			// Access the pixels of the QR
			virtual size_t	VCOM_CALLTYPE GetWidth() = 0;
			virtual bool	VCOM_CALLTYPE GetPixel(size_t ix, size_t iy) = 0;	// 0 <= ix < width and 0 <= iy < width

			// Create a Vectorworks group with the given boxWidth (in mm) dimensions
			virtual MCObjectHandle	VCOM_CALLTYPE CreateGroup(const WorldPt& atPt, WorldCoord boxWidth, ColorRef color=0) = 0;

			// Draw as image
			// return false if there is not enough pixels in the 'boxWidth' to draw the QR
			virtual bool	VCOM_CALLTYPE	Draw(VectorWorks::IDrawPad* drawPad, const ViewPt& atPt, ViewCoord boxWidth) = 0;
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IQRGenerator>			IQRGeneratorPtr;
	}
}
