//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	// ----------------------------------------------------------------------------------------------------
	enum EAdornerType
	{
		kAdornerType_5pxEmptyBox	= 101,					// kLocusNode
		kAdornerType_5pxFilledBox	= 102,					// kLocusNode - Filled box.
		kAdornerType_SolidLine,								// kLineNode
		kAdornerType_DashedLine,							// kLineNode
		kAdornerType_SolidPolygon,							// kPolylineNode
		kAdornerType_DashedPolygon,							// kPolylineNode
		kAdornerType_FixedSizeImageInWorldSpaceCentered,	// kPaintNode
		kAdornerType_FixedSizeImageInViewSpace,				// kPaintNode
	};
	
	

	// ----------------------------------------------------------------------------------------------------
	// {906D5596-DA51-4804-B275-EC4C76908ABA}
	static const VWIID IID_ToolInteractiveDraw = { 0x906d5596, 0xda51, 0x4804, { 0xb2, 0x75, 0xec, 0x4c, 0x76, 0x90, 0x8a, 0xba } };

	class DYNAMIC_ATTRIBUTE IToolInteractiveDraw : public IVWUnknown
	{
	public:
		enum EUpdateType
		{
			eMove,		 // Rotation/Translation only
			eVisibility, // Update visibility only
			ePositions,  // Update vertex positions only (for meshes)
			eFull		 // Re-tessellation
		};

		virtual MCObjectHandle	VCOM_CALLTYPE GetObject(short objType, Sint32 id=0) = 0;
		// AddNewOrGetExistingObject is deprecated. Use GetObject instead.
		virtual MCObjectHandle	VCOM_CALLTYPE deprecated001( MCObjectHandle inObject, Sint32 id=0 ) = 0;
		virtual void			VCOM_CALLTYPE SetObjectTransform( short objType, Sint32 id, const TransformMatrix& mat ) = 0;
		virtual void			VCOM_CALLTYPE SetObjectOptions( short objType, Sint32 id, bool doWires, bool doSolid, bool autoRotate = false, double autoScaleSizePixels = 0.0 ) = 0;
		virtual void			VCOM_CALLTYPE UpdateObject( short objType, Sint32 id=0, EUpdateType updateType = eFull ) = 0;
		virtual void			VCOM_CALLTYPE RemoveObject(short objType, Sint32 id=0) = 0;
		virtual void			VCOM_CALLTYPE ClearObjects( ) = 0;
		virtual MCObjectHandle  VCOM_CALLTYPE SetObject( short objType, Sint32 id, MCObjectHandle h ) = 0;


		virtual MCObjectHandle	VCOM_CALLTYPE GetAdorner(EAdornerType adornerType, Sint32 id=0) = 0;
		virtual void			VCOM_CALLTYPE RemoveAdorner(EAdornerType adornerType, Sint32 id=0) = 0;
		virtual void			VCOM_CALLTYPE ClearAdorners( ) = 0;

		virtual void			VCOM_CALLTYPE Setup(bool bRestore) = 0;
	};

	// ----------------------------------------------------------------------------------------------------
	typedef VCOMPtr<IToolInteractiveDraw>		IToolInteractiveDrawPtr;
}
