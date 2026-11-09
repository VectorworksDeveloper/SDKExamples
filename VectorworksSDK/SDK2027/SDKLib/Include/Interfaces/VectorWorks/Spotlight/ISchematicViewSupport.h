#pragma once

// Forward declaration note: updated to use SDK types instead of VWFC wrapper types

namespace VectorWorks
{
	namespace SchematicView
	{
		enum class E2DComponentViewType
		{
			Automatic,
			Projection,
			Top,
			Front,
			Back,
			Left,
			Right,
			Bottom,
			PointDown
		};

		enum class ESchematicOrientation
		{
			Horizontal,
			Vertical,
			KeepOrientation
		};

		enum class EFillStyleType : short
		{
			None,
			Solid,
			Pattern,
			Hatch,
			KeepExisting
		};

		struct SSchematicViewOptions
		{
			bool					fIsUsed;
			TXString				fMarkerSymbolName;
			TXString				fViewType;
			TransformMatrix			fViewMatrix;
			TXString				fLayerName;
			bool					fLayerIsDesignLayer;
			ESchematicOrientation	fOrientation;
			EFillStyleType			fFillStyle;
			ColorRef				fFillColorRef;
			TXString				fFillPatternName;
			TXString				fFillHatchName;
			int						fLoadOffset;
			TXString				fClassName;
			E2DComponentViewType	f2DComponentViewType;
			bool					fLoadsOnTop;

			SSchematicViewOptions()
				: fIsUsed( true )
				, fMarkerSymbolName()
				, fViewType( "Top" )
				, fViewMatrix()
				, fLayerName()
				, fLayerIsDesignLayer( true )
				, fOrientation( ESchematicOrientation::KeepOrientation )
				, fFillStyle( EFillStyleType::KeepExisting )
				, fFillColorRef( 0 )
				, fFillPatternName()
				, fFillHatchName()
				, fLoadOffset( 0 )
				, fClassName()
				, f2DComponentViewType( E2DComponentViewType::Automatic )
				, fLoadsOnTop( false )
			{}
		};

		// ---------------------------------------------------------------------------------------------------	   
		// {99EC167D-414F-47DF-88F0-DB5472A8E867}
		static const VWIID IID_SchematicViewSupport = { 0x99ec167d, 0x414f, 0x47df, { 0x88, 0xf0, 0xdb, 0x54, 0x72, 0xa8, 0xe8, 0x67 } };

		class DYNAMIC_ATTRIBUTE ISchematicViewSupport : public IVWSingletonUnknown
		{
		public:

			virtual MCObjectHandle				GetModelParent( MCObjectHandle schematicObj ) = 0;
			virtual TMCObjectHandlesSTLArray	GetSchematicInstances( MCObjectHandle parent ) = 0;
			virtual TMCObjectHandlesSTLArray	GetSchematicLoads( MCObjectHandle parent ) = 0;
			virtual MCObjectHandle				GetSchematicMaster( MCObjectHandle schematicObj ) = 0;
			virtual MCObjectHandle				CreateSchematicViewObject( MCObjectHandle parentObj, const SSchematicViewOptions& options, Sint32 loadIndex ) = 0;
			virtual MCObjectHandle				CreateRiggingSchematic( MCObjectHandle riggingObj, const SSchematicViewOptions& options, TransformMatrix newSchemObjTransf ) = 0;
			virtual TransformMatrix				GetModelToSchematicTransform( MCObjectHandle schematicObj ) = 0;
			virtual TransformMatrix				GetModelToSchematicDimensionTransform( MCObjectHandle schematicObj ) = 0;
			virtual bool						IsSchematicLoad( MCObjectHandle schematicObj ) = 0;
			virtual TXString					GetSchematicViewLabel( MCObjectHandle schematicObj, bool isSingleSel ) = 0;
			virtual TransformMatrix				GetViewMatrix( MCObjectHandle schematicObj ) = 0;
			virtual EViewTypes					Get2DComponentView( MCObjectHandle schematicObj ) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<ISchematicViewSupport>			ISchematicViewSupportPtr;
	}
}
