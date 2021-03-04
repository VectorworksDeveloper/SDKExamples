//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::VWObjects;
using namespace VWFC::Math;

VWBitmapObj::VWBitmapObj(VectorWorks::IDrawPad* drawPad)
{
	fhObject	= gSDK->CreatePaintNode( drawPad );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create bitmap" );
}

VWBitmapObj::VWBitmapObj(InternalIndex imageResource)
{
	MCObjectHandle hImage = gSDK->InternalIndexToHandle( imageResource );
	fhObject	= gSDK->CreatePaintFromImage( hImage );
	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create bitmap" );
}

VWBitmapObj::VWBitmapObj(MCObjectHandle hBitmap)
{
	VWFC_ASSERT( VWBitmapObj::IsBitmapObject( hBitmap ) );
	if ( ! VWBitmapObj::IsBitmapObject( hBitmap ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject		= hBitmap;
	VWFC_ASSERT( fhObject != nil );
}

VWBitmapObj::VWBitmapObj(const VWBitmapObj& src)
{
	fhObject		= src.fhObject;
}

VWBitmapObj::~VWBitmapObj()
{
}

VWBitmapObj& VWBitmapObj::operator=(const VWBitmapObj& src)
{
	fhObject = src.fhObject;
	return *this;
}

/*static*/ bool VWBitmapObj::IsBitmapObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN(hObj );
	return type == kPaintNode;
}

Sint32 VWBitmapObj::GetWidthPixels() const
{
	TVariableBlock	varValue;
	gSDK->GetObjectVariable( fhObject, ovPaintWidthPixels, varValue );

	Sint32	data;
	return varValue.GetSint32( data ) ? data : 0;
}

void VWBitmapObj::SetWidthPixels(Sint32 value) const
{
	TVariableBlock	varValue( value );
	gSDK->SetObjectVariable( fhObject, ovPaintWidthPixels, varValue );
}

Sint32 VWBitmapObj::GetHeightPixels() const
{
	TVariableBlock	varValue;
	gSDK->GetObjectVariable( fhObject, ovPaintHeightPixels, varValue );

	Sint32	data;
	return varValue.GetSint32( data ) ? data : 0;
}

void VWBitmapObj::SetHeightPixels(Sint32 value) const
{
	TVariableBlock	varValue( value );
	gSDK->SetObjectVariable( fhObject, ovPaintHeightPixels, varValue );
}

VWBitmapObj::ECompression VWBitmapObj::GetCompression() const
{
	TVariableBlock	varValue;
	gSDK->GetObjectVariable( fhObject, ovPaintCompression, varValue );

	Sint32	data;
	return varValue.GetSint32( data ) ? (ECompression) data : eCompression_None;
}

void VWBitmapObj::SetCompression(ECompression value)
{
	TVariableBlock	varValue( (Sint32) value );
	gSDK->SetObjectVariable( fhObject, ovPaintCompression, varValue );
}

WorldCoord VWBitmapObj::GetWidth() const
{
	TVariableBlock	varValue;
	gSDK->GetObjectVariable( fhObject, ovPaintTDWidth, varValue );

	Real64	data;
	return varValue.GetReal64( data ) ? data : 0;
}

void VWBitmapObj::SetWidth(WorldCoord value)
{
	TVariableBlock	varValue( value );
	gSDK->SetObjectVariable( fhObject, ovPaintTDWidth, varValue );
}

WorldCoord VWBitmapObj::GetHeight() const
{
	TVariableBlock	varValue;
	gSDK->GetObjectVariable( fhObject, ovPaintTDHeight, varValue );

	Real64	data;
	return varValue.GetReal64( data ) ? data : 0;
}

void VWBitmapObj::SetHeight(WorldCoord value)
{
	TVariableBlock	varValue( value );
	gSDK->SetObjectVariable( fhObject, ovPaintTDHeight, varValue );
}

WorldCoord VWBitmapObj::GetX() const
{
	TVariableBlock	varValue;
	gSDK->GetObjectVariable( fhObject, ovPaintTDOriginX, varValue );

	Real64	data;
	return varValue.GetReal64( data ) ? data : 0;
}

void VWBitmapObj::SetX(WorldCoord value)
{
	TVariableBlock	varValue( value );
	gSDK->SetObjectVariable( fhObject, ovPaintTDOriginX, varValue );
}

WorldCoord VWBitmapObj::GetY() const
{
	TVariableBlock	varValue;
	gSDK->GetObjectVariable( fhObject, ovPaintTDOriginY, varValue );

	Real64	data;
	return varValue.GetReal64( data ) ? data : 0;
}

void VWBitmapObj::SetY(WorldCoord value)
{
	TVariableBlock	varValue( value );
	gSDK->SetObjectVariable( fhObject, ovPaintTDOriginY, varValue );
}

WorldRect VWBitmapObj::GetRect() const
{
	WorldRect	result;
	result.left		= this->GetX();
	result.top		= this->GetY();
	result.right	= result.left + this->GetWidth();
	result.bottom	= result.top + this->GetHeight();
	return result;
}

void VWBitmapObj::SetRect(const WorldRect& rect)
{
	this->SetX( rect.left );
	this->SetY( rect.top );
	this->SetWidth( rect.Width() );
	this->SetHeight( rect.Height() );
}

MCObjectHandle VWBitmapObj::CreateImageResource(const TXString& imageName) const
{
	return gSDK->CreateImageFromPaint( fhObject, imageName );
}

// adjusts to the given bounds and transformation.
bool VWBitmapObj::AdjustTo(const VWRectangle2D& bounds, const VWTransformMatrix& transform)
{
	return	VWBitmapObj::AdjustBitmapTo( fhObject, bounds, transform );
}

// checks whether the bitmap has alpha channel transparency mask.
bool VWBitmapObj::HasAlphaChannel()
{
	// init.
	bool		hasAlpha		= false;

	if ( fhObject != nullptr )
	{
		// check if the image is compressed or not.
		ICompressedImagePtr	compressedImage( IID_CompressedImage );

		if ( VCOM_SUCCEEDED( compressedImage->CreateFromObject( fhObject ) ) )
		{
			CompressedImageDesc	imageDesc;
			// get the image description.
			if ( VCOM_SUCCEEDED( compressedImage->GetCompressedImageDesc( imageDesc ) ) )
			{
				hasAlpha		= imageDesc.fbHasAlpha;
			}
		}
	}

	// result.
	return	( hasAlpha );
}

bool VWBitmapObj::ConvertToColorDepth(ConvertToDepth inDepth, MCObjectHandle& outConverted)
{
	// init.
	outConverted			= nullptr;
	bool		isDone		= false;

	if ( fhObject != nullptr )
	{
		VWObject			paintObj( fhObject );

		VWRectangle2D		paintObjBounds;
		paintObj.GetObjectBounds( paintObjBounds );	// get paint object bounds.

		VWTransformMatrix	paintObjMatrix;
		paintObj.GetObjectMatrix( paintObjMatrix );	// get paint object matrix.

		bool				isRawCreated	= false;
		bool				isCompressed	= false;
		CompressionType		compressType	= eUnsupported;

		IRawImagePtr		rawImage( IID_RawImage );

		// check if the image is compressed or not.
		ICompressedImagePtr	compressedImage( IID_CompressedImage );

		if ( VCOM_SUCCEEDED( compressedImage->CreateFromObject( fhObject ) ) &&	// compressed image.
			 VCOM_SUCCEEDED( compressedImage->GetCompressionType( compressType ) ) )
		{
			isCompressed	= true;

			isRawCreated	= VCOM_SUCCEEDED( rawImage->CreateFromCompressedImage( compressedImage ) );
		}
		else				// not compressed image.
		{
			isRawCreated	= VCOM_SUCCEEDED( rawImage->CreateFromObject( fhObject,
																		  this->GetWidth()	/* dpi H res */,
																		  this->GetHeight()	/* dpi V res */,
																		  true /* has alpha */ ) );
		}

		if ( isRawCreated )	// raw image provider is created.
		{
			// convert to color depth.
			if ( VCOM_SUCCEEDED( rawImage->ConvertColorDepth( inDepth ) ) )
			{
				if ( isCompressed )
				{
					ICompressedImagePtr	compressed8bppImage( IID_CompressedImage );

					// create compressed using the same compressed type.
					if ( VCOM_SUCCEEDED( compressed8bppImage->CreateFromRAWImage( rawImage, compressType ) ) )
					{
						// create the new paint object.
						isDone	= VCOM_SUCCEEDED( compressed8bppImage->CreateBitmapObject( outConverted ) );
					}
				}
				else
				{
					// create a new paint object (not compressed).
					isDone		= VCOM_SUCCEEDED( rawImage->CreateBitmapObject( outConverted ) );
				}
			}
		}

		isDone		 			= ( isDone && ( outConverted != nullptr ) );

		if ( isDone )			// OK, use converted.
		{
			// adjust the resulted bitmap to the bounds and matrix of the original.
			VWBitmapObj::AdjustBitmapTo( outConverted, paintObjBounds, paintObjMatrix );
		}
	}

	// result.
	return	( isDone );
}

// converts image to monochrome negative (inverts black and white to create a negative).
bool VWBitmapObj::ConvertToInvertedMonochrome(MCObjectHandle& outConverted)
{
	// init.
	outConverted			= nullptr;
	bool		isDone		= false;

	if ( fhObject != nullptr )
	{
		VWObject			paintObj( fhObject );

		VWRectangle2D		paintObjBounds;
		paintObj.GetObjectBounds( paintObjBounds );	// get paint object bounds.

		VWTransformMatrix	paintObjMatrix;
		paintObj.GetObjectMatrix( paintObjMatrix );	// get paint object matrix.

		bool				isRawCreated	= false;
		bool				isCompressed	= false;
		CompressionType		compressType	= eUnsupported;

		IRawImagePtr		rawImage( IID_RawImage );

		// check if the image is compressed or not.
		ICompressedImagePtr	compressedImage( IID_CompressedImage );

		if ( VCOM_SUCCEEDED( compressedImage->CreateFromObject( fhObject ) ) &&	// compressed image.
			 VCOM_SUCCEEDED( compressedImage->GetCompressionType( compressType ) ) )
		{
			isCompressed	= true;

			isRawCreated	= VCOM_SUCCEEDED( rawImage->CreateFromCompressedImage( compressedImage ) );
		}
		else				// not compressed image.
		{
			isRawCreated	= VCOM_SUCCEEDED( rawImage->CreateFromObject( fhObject,
																		  this->GetWidth()	/* dpi H res */,
																		  this->GetHeight()	/* dpi V res */,
																		  true /* has alpha */ ) );
		}

		if ( isRawCreated )	// raw image provider is created.
		{
			if ( VCOM_SUCCEEDED( rawImage->ConvertColorDepth( kConvertTo1bpp ) ) &&	// convert to monochrome.
				 VCOM_SUCCEEDED( rawImage->InvertMonochrome() ) )					// convert to monochrome negative.
			{
				if ( isCompressed )
				{
					ICompressedImagePtr	monochNegImage( IID_CompressedImage );

					// create compressed using the same compressed type.
					if ( VCOM_SUCCEEDED( monochNegImage->CreateFromRAWImage( rawImage, compressType ) ) )
					{
						// create the new paint object.
						isDone	= VCOM_SUCCEEDED( monochNegImage->CreateBitmapObject( outConverted ) );
					}
				}
				else
				{
					// create a new paint object (not compressed).
					isDone		= VCOM_SUCCEEDED( rawImage->CreateBitmapObject( outConverted ) );
				}
			}
		}

		isDone		 			= ( isDone && ( outConverted != nullptr ) );

		if ( isDone )			// OK, use converted.
		{
			// adjust the resulted bitmap to the bounds and matrix of the original.
			VWBitmapObj::AdjustBitmapTo( outConverted, paintObjBounds, paintObjMatrix );
		}
	}

	// result.
	return	( isDone );
}

// adjusts the bitmap object to the given bounds and transformation.
/*static*/ bool VWBitmapObj::AdjustBitmapTo(MCObjectHandle hBitmap, const VWRectangle2D& bounds, const VWTransformMatrix& transform)
{
	// init.
	bool				isAdjusted	= false;

	VWFC_ASSERT( VWBitmapObj::IsBitmapObject( hBitmap ) );	// bad input.

	if ( VWBitmapObj::IsBitmapObject( hBitmap ) )
	{
		VWObject		paintObj( hBitmap );

		VWRectangle2D	objBounds;
		paintObj.GetObjectBounds( objBounds );	// get converted paint object bounds.

		double			wNew		= objBounds.GetWidth();
		double			hNew		= objBounds.GetHeight();

		// validate.
		VWFC_ASSERT( Double1_GT_Double2( wNew, 0.0 ) && Double1_GT_Double2( hNew, 0.0 ) );	// not expected. check !

		if ( Double1_GT_Double2( wNew, 0.0 ) &&
			 Double1_GT_Double2( hNew, 0.0 ) )	// non-zero width.
		{
			double		scaleCoeffX	= ( bounds.GetWidth()	/ wNew );
			double		scaleCoeffY	= ( bounds.GetHeight()	/ hNew );

			// scale (to even sizes).
			paintObj.ScaleObject( VWPoint2D( 0.0, 0.0 ), scaleCoeffX, scaleCoeffY );

			// set the matrix.
			paintObj.SetObjectMatrix( transform );

			isAdjusted	= true;
		}
	}

	// result.
	return	( isAdjusted );
}

MCObjectHandle VWBitmapObj::GetImageCropObject() const
{
	return gSDK->GetImageCropObject( fhObject );
}

bool VWBitmapObj::IsImageCropped() const
{
	return gSDK->IsImageCropped( fhObject );
}

bool VWBitmapObj::IsImageCropVisible() const
{
	return gSDK->IsImageCropVisible( fhObject );
}

void VWBitmapObj::SetImageCropVisible(bool isVisible)
{
	gSDK->SetImageCropVisible( fhObject, isVisible );
}

bool VWBitmapObj::SetImageCropObject(MCObjectHandle cropObject)
{
	return gSDK->SetImageCropObject( fhObject, cropObject );
}

