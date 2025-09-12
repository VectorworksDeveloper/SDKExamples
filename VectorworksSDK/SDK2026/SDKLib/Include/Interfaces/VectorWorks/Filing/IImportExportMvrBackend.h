//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		enum EImportCameraOption
		{
			kImportCameraOneOnly,
			kImportCameraAll
		};

		enum EImportMeshOption
		{
			kImportMeshAsVWMesh,
			kImportMeshAs3DPolys
		};

		struct SMvrBackendImportOptions
		{
			Sint32				fSize;
			bool				fbImportMeshes;
			EImportMeshOption	fImportMeshOptions;
			bool				fbTexture3DPolys;
			bool				fbImportMaterials;
			bool				fbImportTextureMaterials;
			bool				fbImportLights;
			bool				fbImportSpotLights;
			bool				fbImportOmniLights;
			bool				fbImportCameras;
			EImportCameraOption	fImportCameraOptions;
			TXString			fCameraName;
			WorldPt3			fScaleVector;
			WorldPt3			fScaleCenter;
			bool				fImporAllRW;
			bool				fbProgressStrCustom;

											SMvrBackendImportOptions() { fSize = sizeof(SMvrBackendImportOptions); }
		};

		// ----------------------------------------------------------------------------------------------------
		enum EExportObjectsOption
		{
			kExportObjectsOption_All,
			kExportObjectsOption_SelectedOnly,
			kExportObjectsOption_AllLayers,
		};

		enum EExportTexturesOption
		{
			kExportTexturesOption_None,
			kExportTexturesOption_AsJPEGFiles,
			kExportTexturesOption_AsPNGFiles,
		};

		struct SMvrBackendExporterOptions
		{
			Sint32							fSize;
			EExportObjectsOption			fExportObjectsOption;
			bool							fExportVWObjects;
			Sint32							fObjectPolygonConvRes;	// [0..7]
			bool							fExport3DLocuses;
			bool							fExportWalls;
			bool							fExport3DSymbols;
			bool							fExportParametrics;
			bool							fExportLights;
			bool							fExportCurrentViewAsCamera;
			bool							fExportMaterials;
			EExportTexturesOption			fExportMatTextures;
			WorldPt3						fScaleVector;
			WorldPt3						fScaleCenter;

											SMvrBackendExporterOptions() { fSize = sizeof(SMvrBackendExporterOptions); }
		};

		//-------------------------------------------------------------------------------------------------------------
		enum class EGeometryFaceInfo
		{
			LineABVisible		= 0x04,
			LineBCVisible		= 0x02,
			LineCAVisible		= 0x01,
			LineAllVisible		= 0x07
		};

		//-------------------------------------------------------------------------------------------------------------
		typedef size_t(*TImportBufferCallback)(Uint16 fileID, void* inBuffer, size_t readBytesCnt, void* userData);		// return bytes read < readBytesCnt; readBytesCnt is the max bytes that can be read from inBuffer
		typedef size_t(*TExportBufferCallback)(Uint16 fileID, void* outBuffer, size_t writeBytesCnt, void* userData);	// return bytes written < writeBytesCnt; writeBytesCnt is the max bytes that can be written to outBuffer

		//-------------------------------------------------------------------------------------------------------------
		struct GeometryTexture
		{
			TImportBufferCallback	fFileCallback_Import;	// A callback that will be called when importing/exporting the texture file
			TExportBufferCallback	fFileCallback_Export;	//   providing or requesting the bytes in chunks
			Uint16					fFileCallbackID;		// The ID that will be provided to the callback.
															//   this can be utilized when the same callback will be used for several texture files
			void*					fFileCallbackUserData;	// The user data passed it to the callback

			TXString	fName;		// The texture 8.3 file name including extension
			Uint16		fTilingFlags;
			float		fBlurring;
			float		fUOffset;
			float		fUTiling;
			float		fVOffset;
			float		fVTiling;
			float		fRotation;

			GeometryTexture() { fTilingFlags = 0; fBlurring = fUOffset = fUTiling = fVOffset = fVTiling = fRotation = 0; fFileCallback_Import = nullptr; fFileCallback_Export = nullptr; fFileCallbackID = 0; fFileCallbackUserData = nullptr; }
		};

		//-------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IGeometryReceiverMvrBackend
		{
		public:
			virtual	~IGeometryReceiverMvrBackend() {}

			class Material
			{
			public:
				virtual ~Material() {}

				virtual const TXString&			GetMaterialName() const = 0;

				virtual float					GetTransparencyPercentage() const = 0;

				virtual const RGBColor&			GetAmbientColor() const = 0;
				virtual const RGBColor&			GetDiffuseColor() const = 0;
				virtual const RGBColor&			GetSpecularColor() const = 0;

				virtual bool					HasTexture() const = 0;
				virtual void					GetTexture(GeometryTexture& outTexture) const = 0;
				virtual void					GetTextureMask(GeometryTexture& outTexture) const = 0;
			};

			virtual void BeginObject(Sint16 objectID, Sint16 parentObjectID) = 0;	// parentObjectID = Uint64(-1) when object at root
			virtual void SetVerticesCount(size_t cnt) = 0;
			virtual void SetVertex(size_t vertexIndex, double x, double y, double z, double u, double v) = 0;
			virtual void SetFacesCount(size_t cnt) = 0;
			virtual void SetFace(size_t faceIndex, size_t vertexAIndex, size_t vertexBIndex, size_t vertexCIndex, EGeometryFaceInfo info) = 0;
			virtual void SetFaceMaterial(size_t faceIndex, const IGeometryReceiverMvrBackend::Material* material) = 0;
			virtual void EndObject() = 0;
		};

		//-------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IGeometryProviderMvrBackend
		{
		public:
			virtual	~IGeometryProviderMvrBackend() {}

			class Material
			{
			public:
				virtual ~Material() {}

				virtual void	SetMaterialName(const TXString& name) = 0;

				virtual void	SetTransparencyPercentage(float value) = 0;

				virtual void	SetAmbientColor(const RGBColor& clr) = 0;
				virtual void	SetDiffuseColor(const RGBColor& clr) = 0;
				virtual void	SetSpecularColor(const RGBColor& clr) = 0;

				virtual void	SetTexture(const GeometryTexture& texture) = 0;
				virtual void	SetTextureMask(const GeometryTexture& texture) = 0;
			};

			virtual void GetObjects(std::vector<Sint16>& outObjectIDs, Sint16 parentObjectID=-1) = 0;

			virtual void BeginObject(Sint16 id) = 0;
			virtual void GetVerticesCount(size_t& outCnt) = 0;
			virtual void GetVertex(size_t vertexIndex, double& outX, double& outY, double& outZ, double& outU, double& outV) = 0;
			virtual void GetFacesCount(size_t& outCnt) = 0;
			virtual void GetFace(size_t faceIndex, size_t& outVertexAIndex, size_t& outVertexBIndex, size_t& outVertexCIndex, EGeometryFaceInfo& outInfo) = 0;
			virtual void GetFaceMaterial(size_t faceIndex, IGeometryProviderMvrBackend::Material* material) = 0;
			virtual void EndObject() = 0;
		};

		class DYNAMIC_ATTRIBUTE IImportExportObjectMvrBackend : public IVWUnknown
		{
		public:
			virtual ~IImportExportObjectMvrBackend() {}
			virtual VCOMError VCOM_CALLTYPE	BeginExport(IFolderIdentifier* pExportFolder, short quality) = 0;
			virtual VCOMError VCOM_CALLTYPE	BeginImport() = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID, MCObjectHandle& outHandle) = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID, IGeometryReceiverMvrBackend* receiver) = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(MCObjectHandle hObject, const TXString& fileName, bool exportWithIdentity) = 0;
			virtual VCOMError VCOM_CALLTYPE	Export(IGeometryProviderMvrBackend* provider, const TXString& fileName, bool exportWithIdentity) = 0;
			virtual VCOMError VCOM_CALLTYPE	End() = 0;
            // Vectorworks 2019 SP3
            virtual VCOMError VCOM_CALLTYPE	SetOptions(const SMvrBackendImportOptions& options) = 0;
            virtual VCOMError VCOM_CALLTYPE	GetOptions(SMvrBackendImportOptions& outOptions) = 0;
            virtual VCOMError VCOM_CALLTYPE	SetOptions(const SMvrBackendExporterOptions& options) = 0;
            virtual VCOMError VCOM_CALLTYPE	GetOptions(SMvrBackendExporterOptions& outOptions) = 0;
			// Vectorworks 2024 SP2
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID, MCObjectHandle& outHandle, const bool isForMVR) = 0;
			virtual VCOMError VCOM_CALLTYPE	Import(IFileIdentifier* pFileID, IGeometryReceiverMvrBackend* receiver, const bool isForMVR) = 0;
            // Vectorworks 2024 SP4
			virtual VCOMError VCOM_CALLTYPE	Export(MCObjectHandle hObject, const TXString& fileName, bool exportWithIdentity, bool forceWhiteColor) = 0;

		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportObjectMvrBackend>		IImportExportObjectMvrBackendPtr;
	}
}
