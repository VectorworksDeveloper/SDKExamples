

#pragma once

#include "../../../../../ThirdPartySource/VGX/include/vgx/VGXSDK.h"
#include "glm/glm.hpp"

namespace VectorWorks {

    namespace GraphicsConnect {
        
        enum ESVisibilitySpec { eVisible, eBlackWhite, eGray, eInvisible };
        
        
        class IMeshData
        {
        public:
            enum EMeshFlags {
                eNone = 0x0,
                eTwoSidedLighting = 0x80,
                eAutoRotateGround = 0x400
           };
            
            enum EMeshType {
                eSolidMesh = 0x0
            };
            
            virtual ~IMeshData() { }
            
            virtual EMeshType MeshType() const = 0;
            
            virtual Uint32 NumVertices() const = 0;
            virtual Uint32 NumFaces() const = 0;
            virtual Uint32 NumVertexNormals() const = 0;
            virtual Uint32 NumUVCoords() const = 0;
            
            virtual glm::dvec3 Vertex(Uint32 index) const = 0;
            virtual Uint32 FaceIndex(Uint32 index) const = 0;
            virtual glm::dvec3 VertexNormal(Uint32 index) const = 0;
            virtual glm::dvec2 VertexUV(Uint32 index) const = 0;
            
            virtual bool Material(glm::vec4& objFillColor, Sint32& materialID, bool& repeatH, bool& repeatV) const = 0;
            
            virtual EMeshFlags Flags() const { return eNone; } //< Used to flag special meshes
        };
        
        class ISceneHandler
        {
        public:
            //  This API is subject to Change.  We are using this to see if the AddInstance API can be used to provide
            //  All the Info needed to implement the Export 3D PDF.
            //
            //
            virtual ~ISceneHandler() {}
            
            //  New Object provides a hObject handle so you can querry the object's document properties.  Use exosting SDK to access
            //  properties such as Parent and Class visibity
            virtual void NewObject(  void* id, size_t numMeshes ) = 0; //< numMeshes to resize/reserve containers in advance
            virtual void AddMesh( const IMeshData& meshData ) = 0;
            
            //  hReferenceObject is not NULL sometimes.
            //  When? If NewObject above has no layer parent. hReferenceObject is not nil for Symbol Instances and Design Layer Viewports and Layer Links. Use this hReferenceObject when hObject has no layer parent.
            virtual void AddInstance( ESVisibilitySpec Visibility, glm::dmat4* transform) = 0;

			// This is just an updating method to update the user progress bar for every iteration of the objects in VGM.
			//virtual void NumObjects(size_t numObjects) = 0;
        };
        
        class ISceneHandler2
        {
        public:
            virtual ~ISceneHandler2() {}
            virtual void NewObject( MCObjectHandle h, size_t numMeshes ) = 0; //< numMeshes to resize/reserve containers in advance
            virtual void AddMesh( const IMeshData& meshData ) = 0;
            virtual void AddInstance( MCObjectHandle h, ESVisibilitySpec Visibility, glm::dmat4* transform) = 0;
            virtual void NumObjects(size_t numObjects) = 0;
            
        };
        
        class IMaterialProvider
        {
        public:
            virtual ~IMaterialProvider() {}
            
            virtual bool Set(Sint32 coreMaterialID) = 0;
            // outPixels ownership is transferred to caller, i.e. implementor will new memory, caller will delete.
            virtual bool GetColorImage(VGM::ColorImageArgs& args) = 0;
            virtual bool GetMaskImage(unsigned char *& outPixels, int& outWidth, int& outHeight, int& outBytesPerPixel, int& outBytesPerRow, bool &outIsMaskTransparent, Sint32 & outAlphaValue, bool & outRequiresAlphaSorting) = 0;
            virtual bool GetFilterColor(int& outIsFiltered, glm::vec3& outFilterColor) = 0;
            virtual bool GetColor(glm::vec3& color) = 0;
            virtual float GetOpacity() = 0;
            virtual bool RenderOptionUseColor() = 0;
            virtual bool MaterialRequiresMap() = 0;
        };
        
    
        class IMaterialsHandler
        {
        public:
            virtual ~IMaterialsHandler() {}
            // Match the materialID with that returned by IMeshData.Material();
            virtual void CreateMaterial( Sint32 materialID, glm::vec4 diffuseColor, IMaterialProvider& matProvider ) = 0;

			// This is similiar to OnUpdateObjects, but updates for materials.
			virtual void NumMaterials(size_t numMaterials) = 0;
        };
        
        class IMaterialsHandler2
        {
        public:
            virtual ~IMaterialsHandler2() {}
            // Match the materialID with that returned by IMeshData.Material();
            virtual void CreateMaterial( Sint32 materialID, glm::vec4 diffuseColor, IMaterialProvider& matProvider ) = 0;
            virtual void NumMaterials(size_t numMaterials) = 0;
        };

		class IVGXDataExchange
		{
		public:
			virtual ~IVGXDataExchange() {}
			virtual void CustomObjectData(void* objectID, MCObjectHandle inVWObject, size_t inNumInstances, VGM::ICustomStreamWriter* inStreamWriter = nullptr) = 0;
			virtual void CustomInstanceData(void* instanceID, MCObjectHandle inVWObject, MCObjectHandle inRefObject, short inVis, short inNumInst, VGM::ICustomStreamWriter* inStreamWriter = nullptr) = 0;
			virtual void UniqueObjectList(const std::vector<MCObjectHandle>& inParentChain, const UuidStorage& inObjectId) = 0;
		};

        

        // ---------------------------------------------------------------------------------------------------
        // {872ba345-361c-43b8-aee7-09e7cd7f4352}
        static const VWIID IID_DocumentScenes =
        { 0x872ba345, 0x361c, 0x43b8, { 0xae, 0xe7, 0x09, 0xe7, 0xcd, 0x7f, 0x43, 0x52 } };

        class DYNAMIC_ATTRIBUTE IDocumentScenes : public IVWSingletonUnknown
        {
        public:
            
            enum ESceneSpec { ESceneSpec_AllVisible, ESceneSpec_ActiveLayer, ESceneSpec_Selected };
            enum EFacettingQuality { EFacettingQuality_Low, EFacettingQuality_Medium, EFacettingQuality_High, EFacettingQuality_VeryHigh };
            
            virtual bool VCOM_CALLTYPE GetScene(ESceneSpec inSceneSpec, EFacettingQuality inQuality, IMaterialsHandler* ioMaterialsHandler, ISceneHandler* ioSceneHandler) = 0;
        };
        
        // ---------------------------------------------------------------------------------------------------
        // {30bb31fb-91fe-4038-947a-e1136d7fd6c2}
        static const VWIID IID_DocumentScenes2 =
        { 0x30bb31fb, 0x91fe, 0x4038, { 0x94, 0x7a, 0xe1, 0x13, 0x6d, 0x7f, 0xd6, 0xc2 } };
        
        class DYNAMIC_ATTRIBUTE IDocumentScenes2 : public IVWSingletonUnknown
        {
        public:
            
            virtual bool VCOM_CALLTYPE GetScene(IDocumentScenes::ESceneSpec inSceneSpec, IDocumentScenes::EFacettingQuality inQuality, IMaterialsHandler2* ioMaterialsHandler, ISceneHandler2* ioSceneHandler) = 0;
        };
		
		static const VWIID IID_DocumentScenes3 = 
		{ 0xe76615c6, 0xb94e, 0x4725, {0xb6, 0x4d, 0xf2, 0x72, 0xff, 0xdc, 0x7a, 0x21}};
		
		class DYNAMIC_ATTRIBUTE IDocumentScenes3 : public IVWSingletonUnknown
		{
		public:
			virtual bool VCOM_CALLTYPE GetScene(IDocumentScenes::ESceneSpec inSceneSpec, IDocumentScenes::EFacettingQuality inQuality, VGM::IVGXReader* inReader) = 0;
			virtual bool VCOM_CALLTYPE WriteScene(IDocumentScenes::ESceneSpec inSceneSpec, IDocumentScenes::EFacettingQuality inQuality, const std::string& inFilePath) = 0;
		};

		static const VWIID IID_DocumentScenes4 =
		{ 0x3f043a48, 0xb383, 0x419f, {0x87, 0xe4, 0x1d, 0x2c, 0x50, 0x43, 0x81, 0x1f}};
		class DYNAMIC_ATTRIBUTE IDocumentScenes4 : public IVWSingletonUnknown
		{
		public:
			struct VGXSceneExportOptions {
				VGXSceneExportOptions() : sceneSpec(IDocumentScenes::ESceneSpec::ESceneSpec_AllVisible), quality(IDocumentScenes::EFacettingQuality::EFacettingQuality_Low),
					bExportNormals(false), bExportWireframeMeshes(false), bExportHatchMesh(false), bExportFullColor(false), bExportTextTextures(false), bExportClipCube(false), bUseVWCamera(true) {}
				IDocumentScenes::ESceneSpec sceneSpec;
				IDocumentScenes::EFacettingQuality quality;
				bool bExportNormals;
				bool bExportWireframeMeshes;
				bool bExportClipCube;
				bool bExportHatchMesh;
				bool bExportFullColor;
				bool bExportTextTextures;
				bool bUseVWCamera;
			};

			struct VGXOtherOptions {
				VGXOtherOptions() : bExportAmbientOcclusion(false),ambientStrength(0.0),ambientSize(0.0),bDrawEdges(false),edgesCreaseAngle(0), edgeThickness(0),
					customImage(nullptr) {auxFiles.clear();}
				bool bExportAmbientOcclusion;
				double ambientStrength;
				double ambientSize;
				bool bDrawEdges;
				short edgesCreaseAngle;
				int edgeThickness;
				MCObjectHandle customImage;
				std::vector<TXString> auxFiles;
			};
			virtual bool VCOM_CALLTYPE GetScene(VGXSceneExportOptions &inExportOptions, VGXOtherOptions &inOtherOptions, VGM::IVGXReader* inReader) = 0;
			virtual bool VCOM_CALLTYPE WriteScene(VGXSceneExportOptions &inExportOptions, VGXOtherOptions &inOtherOptions, const std::string& inFilePath) = 0;
			virtual void VCOM_CALLTYPE RegisterDataExchangeInterface(IVGXDataExchange* pDataEx) = 0;
		};
    }
}
