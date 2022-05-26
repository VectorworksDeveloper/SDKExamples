//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		using namespace VectorWorks::Imaging;

		// --------------------------------------------------------------------------------
		class VWBitmapObj : public VWObject
		{
		public:
							VWBitmapObj(IDrawPad* drawPad);
							VWBitmapObj(InternalIndex imageResource);
							VWBitmapObj(MCObjectHandle hBitmap);
							VWBitmapObj(const VWBitmapObj& src);
			virtual			~VWBitmapObj();

			VWBitmapObj&	operator=(const VWBitmapObj& src);

		public:
			enum ECompression
			{
				eCompression_None = 0,
				eCompression_JPEG = 1,
				eCompression_PNG = 2,
				eCompression_PNGMono = 3,
			};

			Sint32			GetWidthPixels() const;
			void			SetWidthPixels(Sint32 value) const;

			Sint32			GetHeightPixels() const;
			void			SetHeightPixels(Sint32 value) const;

			ECompression	GetCompression() const;
			void			SetCompression(ECompression value);

			WorldCoord		GetWidth() const;	
			void			SetWidth(WorldCoord value);
			
			WorldCoord		GetHeight() const;
			void			SetHeight(WorldCoord value);

			WorldCoord		GetX() const;
			void			SetX(WorldCoord value);

			WorldCoord		GetY() const;
			void			SetY(WorldCoord value);

			WorldRect		GetRect() const;
			void			SetRect(const WorldRect& rect);

			MCObjectHandle	CreateImageResource(const TXString& imageName) const;

			bool			AdjustTo(const VWRectangle2D& bounds, const VWTransformMatrix& transform);

			bool			HasAlphaChannel();

			bool			ConvertToColorDepth(ConvertToDepth inDepth, MCObjectHandle& outConverted);

			bool			ConvertToInvertedMonochrome(MCObjectHandle& outConverted);

			MCObjectHandle	GetImageCropObject() const;
			bool			IsImageCropped() const;
			bool			IsImageCropVisible() const;
			void			SetImageCropVisible(bool isVisible);
			bool			SetImageCropObject(MCObjectHandle cropObject);

		// tool
		public:
			static bool		IsBitmapObject(MCObjectHandle hObj);
			static bool		AdjustBitmapTo(MCObjectHandle hBitmap, const VWRectangle2D& bounds, const VWTransformMatrix& transform);
		};
	}
}
