#pragma once

#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		struct SImportFBXOptions
		{
			bool	fImportAsSingleSymbol	= false;
			bool	fImportMaterials		= true;
			bool	fImportTraspAndImage	= true;		// only trasparency and image materials create RenderWorks resources
			bool	fImportAllRW			= false;	// all materials create RenderWorks resources
			
			VectorWorks::MeshSmoothing::EMeshSmoothing	fMeshSmoothing	= VectorWorks::MeshSmoothing::EMeshSmoothing::eCustomCrease;	// Mesh smoothing options
			double										fSmoothingAngle = 50;															// Crease angle setting
			double										fScale			= 1;  															// Scale
		};

		// {13B5E84D-22E9-4FB2-85DC-7BD0A8F50180}
		static const VWIID IID_IImportFBX = { 0x13b5e84d, 0x22e9, 0x4fb2, { 0x85, 0xdc, 0x7b, 0xd0, 0xa8, 0xf5, 0x1, 0x80 }  };

		class DYNAMIC_ATTRIBUTE IImportFBX : public IVWSingletonUnknown
		{	
		public:
			virtual VCOMError VCOM_CALLTYPE	Import() = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifierPtr fileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID, const SImportFBXOptions& options, bool silent = false) = 0;
		};

		typedef VCOMPtr<IImportFBX>	IImportFBXPtr;
	}
}