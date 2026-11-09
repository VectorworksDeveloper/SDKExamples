//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		struct SImportSketchupOptions
		{
			// in headless mode, creates geometry in groups on the current layer so the caller can easily create a symbol at the end
			// in the options dialog context, also creates a symbol at the end
			bool	fImportAsSingleSymbol;

			// set to false to import raw geometry
			bool 	fImportSimpleArchitecturalElements;
	
			// these values are used when fImportSimpleArchitecturalElements is true
			double	fWallWidth;
			double	fSlabThickness;
			double	fRoofSlapThickness;
	
			// texturing
			bool	fImportMaterials;
			bool	fImportTraspAndImage;		// only trasparency and image materials create RenderWorks resources
			bool	fImporAllRW;				// all materials create RenderWorks resources
			bool	fImportGeometryAsMesh;
			bool	f3DPolyUseTextureMaterials;

			SImportSketchupOptions()
			{
				fImportAsSingleSymbol	= false;

				fImportSimpleArchitecturalElements	= false;	// import as raw geometry
				fWallWidth			= 1*2.54;
				fSlabThickness		= 1*2.54;
				fRoofSlapThickness	= 1*2.54;

				fImportMaterials			= true;
				fImportTraspAndImage		= true;		// import materials
				fImporAllRW					= false;	// but only textures and transparency
				fImportGeometryAsMesh		= true;		// create meshes by default
				f3DPolyUseTextureMaterials	= true;		// default for 3D polys (not meshes import)
			}
		};

		// ----------------------------------------------------------------------------------------------------
		// {58F756CD-903E-4d9e-9C92-3C844BEAEE7E}
		static const VWIID IID_IImportExportSketchup = { 0x58f756cd, 0x903e, 0x4d9e, { 0x9c, 0x92, 0x3c, 0x84, 0x4b, 0xea, 0xee, 0x7e } };

		class DYNAMIC_ATTRIBUTE IImportExportSketchup : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError	VCOM_CALLTYPE	Import(IFileIdentifier* fileID) = 0;
			virtual VCOMError	VCOM_CALLTYPE	Import(IFileIdentifier* fileID, const SImportSketchupOptions& options, bool useProgressBar = false) = 0; // no UI
			virtual VCOMError	VCOM_CALLTYPE	Import(IFileIdentifier* fileID, const SImportSketchupOptions& options, const TXString& strProgressTitle, const TXString& strProgressBar ) = 0;
			virtual VCOMError	VCOM_CALLTYPE	Export() = 0;
			virtual VCOMError	VCOM_CALLTYPE	Export(IFileIdentifier* fileID) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportSketchup>		IImportExportSketchupPtr;
	}
}
