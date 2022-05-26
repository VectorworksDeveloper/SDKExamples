#pragma once

namespace VectorWorks
{
	namespace SchematicView
	{

		// ---------------------------------------------------------------------------------------------------	   
		// {99EC167D-414F-47DF-88F0-DB5472A8E867}
		static const VWIID IID_SchematicViewSupport = { 0x99ec167d, 0x414f, 0x47df, { 0x88, 0xf0, 0xdb, 0x54, 0x72, 0xa8, 0xe8, 0x67 } };


		class DYNAMIC_ATTRIBUTE ISchematicViewSupport : public IVWSingletonUnknown
		{
		public:

			virtual MCObjectHandle				GetModelParent( MCObjectHandle schematicObj ) = 0;
			virtual TMCObjectHandlesSTLArray	GetSchematicInstances( MCObjectHandle parent ) = 0;
			virtual MCObjectHandle				GetSchematicMaster( MCObjectHandle schematicObj ) = 0;
			virtual MCObjectHandle				CreateSchematicViewObject( MCObjectHandle parentObj, MCObjectHandle layer, EViewTypes view, Sint32 loadIndex ) = 0;
			virtual MCObjectHandle				CreateRiggingSchematic( MCObjectHandle riggingObj, MCObjectHandle layer, EViewTypes view, TransformMatrix insertion ) = 0;
			virtual TransformMatrix				GetModelToSchematicTransform( MCObjectHandle schematicObj ) = 0;
			virtual bool						IsSchematicLoad( MCObjectHandle schematicObj ) = 0;
			virtual TransformMatrix				GetViewMatrix( MCObjectHandle schematicObj ) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<ISchematicViewSupport>			ISchematicViewSupportPtr;
	}
}
