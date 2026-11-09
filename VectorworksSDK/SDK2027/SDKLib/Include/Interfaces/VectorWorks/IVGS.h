#pragma once

#include "../../VGS.h"
#include "../../VGS3.h"

#include <unordered_map>

namespace VectorWorks
{
	namespace Extension
	{
		namespace VGS
		{
			class IVGS3
			{
			public:
				virtual ~IVGS3() {};
				virtual bool IsValid(vgs3::NodeHandle n) = 0;
				virtual vgs3::NodeHandle GetNext(vgs3::NodeHandle parent) = 0;
				virtual vgs3::NodeHandle GetFirstChild(vgs3::NodeHandle h) = 0;
				virtual vgs3::NodeHandle GetFirstAux(vgs3::NodeHandle h) = 0;
				virtual vgs3::NodeHandle GetParent(vgs3::NodeHandle h) = 0;
				virtual vgs3::NodeType GetType(vgs3::NodeHandle h) = 0;
				virtual vgs3::NodeHandle GetInstanceOf(vgs3::NodeHandle h) = 0;
				virtual vgs3::DirtyFlag GetDirtyFlags(vgs3::NodeHandle h) = 0;
				virtual UuidStorage GetUuid(vgs3::NodeHandle h) = 0;
				virtual MCObjectHandle GetMCObjectHandle(vgs3::NodeHandle n) = 0;
				virtual std::vector<vgs3::NodeHandle> GetInstanceReferencers(vgs3::NodeHandle h) = 0;
				virtual std::vector<vgs3::VGSInstanceBranch> GetInstancePaths(vgs3::NodeHandle n) = 0;
				virtual bool GetDirtyChildrenBranch(vgs3::NodeHandle n) = 0;
				virtual bool GetDirtyAuxBranch(vgs3::NodeHandle n) = 0;
				virtual std::vector<std::pair<vgs3::VGSInstanceBranch, vgs3::VisFlag>> GetVisibilityModifiedArgs(vgs3::NodeHandle n) = 0;
				virtual void Tessellate(vgs3::NodeHandle h, ::VGS::Tessellation& tessellation, std::vector<vgs3::NodeHandle>& meshParts, ::VGS::TessellationQuality quality = ::VGS::TessellationQuality_Unspecified) = 0;
				virtual void SetLogFolderPath(std::string_view logFolderPath) = 0;
				virtual std::string_view GetLogFolderPath() = 0;
				virtual vgs3::NodeHandle GetScenegraphRoot() = 0;
				virtual std::vector<vgs3::NodeHandle> GetStartNodes(vgs3::NodeHandle root) = 0;
				virtual ::VGS::CameraModifyArgs GetCamera(vgs3::NodeHandle root) = 0;
				virtual std::optional<::VGS::ClipCubeModifyArgs> GetClipCube(vgs3::NodeHandle root) = 0;
				virtual vgs3::NodeHandle GetSavedViewContainer() = 0;
				virtual vgs3::NodeHandle GetTextureDefinitionContainer() = 0;
				virtual vgs3::NodeHandle GetLayerContainer() = 0;
				virtual MCObjectHandle GetTextureShaderRecord(vgs3::NodeHandle texDef, ShaderFamily family, bool* isOverrideData = nullptr) = 0;
				virtual glm::ivec2 GetTextureRepeats(vgs3::NodeHandle tex, bool* isOverrideData = nullptr) = 0; // .x is repeats in u direction, .y is in v direction
				virtual bool IsShuttingDown() = 0;
				virtual MCObjectHandle GetBackground(vgs3::NodeHandle root) = 0;
				virtual int GetScenegraphDirtyCount(vgs3::NodeHandle root) = 0;
			};

			// ---------------------------------------------------------------------------------------------------
			// {C15C61EF-3A7C-4637-B095-77B1C97F154D}
			static const VWIID IID_VGS = { 0xc15c61ef, 0x3a7c, 0x4637,{ 0xb0, 0x95, 0x77, 0xb1, 0xc9, 0x7f, 0x15, 0x4d } };

			struct ProxyObjectArgs;
			struct ProxyMaterialArgs;

			class DYNAMIC_ATTRIBUTE IVGS : public IEventSink
			{
			public:
				virtual	bool VCOM_CALLTYPE IsRegistered(const TXString& inRenderEngineID) = 0;
				virtual bool VCOM_CALLTYPE Register(const TXString& inRenderEngineID, std::function<void(::VGS::Operation&)> inRenderPluginCallback, uintptr_t inSceneID = 0) = 0;
				virtual bool VCOM_CALLTYPE Register(const TXString& inRenderEngineID, std::function<void(IVGS3*)> inRenderPluginCallback,
					::VGS::ListenerSetupArgs setupArgs, uintptr_t inSceneID = 0, int vgsVersion = 3) = 0;
				virtual bool VCOM_CALLTYPE Unregister(const TXString& inRenderEngineID) = 0;
				virtual bool VCOM_CALLTYPE GetActiveSceneId(uint64_t& outSceneId) = 0;
				virtual bool VCOM_CALLTYPE GetActiveViewPaneId(Sint32& outPaneId) = 0;
				virtual bool VCOM_CALLTYPE RegisterN(const TXString& inRenderEngineID, std::function<void(::VGS::Operation&)> inRenderPluginCallback, uintptr_t inSceneID = 0,
					std::function<void(ProxyObjectArgs&)> proxyCallback = nullptr,
					std::function<bool(ProxyMaterialArgs&)> materialEditorCallback = nullptr,
					bool alwaysReturnParentChains = false, bool registerAsOneTimeSync = false) = 0;
				virtual bool VCOM_CALLTYPE DumpScenegraph(TXString& outJson) = 0;
				// Builds an acceleration structure for repeated UUID -> handle lookups.
				// gSDK->GetObjectByUuidN() does a full deep+aux scenegraph traversal per call,
				// which is slow when resolving many UUIDs in sequence. This performs that
				// traversal once and returns a map for O(1) repeated lookups. Intended to be
				// called once and reused; the returned handles are valid only as long as the
				// document is not structurally modified.
				virtual std::unordered_map<UuidStorage, MCObjectHandle> VCOM_CALLTYPE BuildDocumentUuidMap() = 0;
			};

			struct ProxyObjectArgs
			{
				std::pair<MCObjectHandle/*client sets this handle when they find a handle of interest*/, std::vector<unsigned char>> fBlob;
				std::vector<MCObjectHandle> fParentChain;	// [0] is root
				bool fRequestTessellation = true;
				uint64_t fSceneID;
			};

			struct ProxyMaterialArgs
			{
				std::vector<unsigned char> fBlob;
				MCObjectHandle fMaterialH;
				uint64_t fSceneID;
			};
		}
		
		namespace RenderPlugin
		{
			struct Operation;
			struct Image;
			struct CompositeLayers;

			typedef uint64_t Scene;


			static const VWIID IID_RenderPlugin = { 0x549868e, 0x7475, 0x4b28, { 0x9e, 0xb0, 0xdb, 0xc, 0xa8, 0x26, 0x23, 0xb7 } };

			class DYNAMIC_ATTRIBUTE IRenderPlugin : public IEventSink
			{
			public:
				virtual bool VCOM_CALLTYPE IsRegistered(const TXString& rendererName) = 0;
				virtual bool VCOM_CALLTYPE Register(const TXString& rendererName, std::function<void(Operation&)> renderPluginCallback,
													const TXString& description,
                                                    const TXString& unableToActivateMessage) = 0;
				virtual bool VCOM_CALLTYPE Unregister(const TXString& rendererName) = 0;
				virtual bool VCOM_CALLTYPE UpdatePixels(Scene scene, const Image& image, const TXString& status, double progress) = 0;
				virtual bool VCOM_CALLTYPE GetCompositeImage(Scene scene, const CompositeLayers& layers, VectorWorks::Extension::RenderPlugin::Image& outImage) = 0;
			};

			enum Event
			{
				Event_Activate,
				Event_Deactivate,
				Event_Reactivate,
				Event_FramebufferResize,
				Event_CancelRender,
				Event_ShowOptions,
			};

			enum ChannelDataType
			{
				ChannelDataType_Byte,	// 1 byte per channel - LDR
				ChannelDataType_Float,	// 4 bytes per channel - HDR

				__ChannelDataType_Count
			};

			struct FramebufferResizeArgs
			{
				Sint32 fWidth;
				Sint32 fHeight;
			};

			typedef std::vector<unsigned char> StyleBlob;

			struct ActivateArgs
			{
				StyleBlob fStyleBlob;
			};

			struct DeactivateArgs
			{
			};

			struct ReactivateArgs
			{
				StyleBlob fStyleBlob;
			};

			struct CancelRenderArgs
			{
			};

			struct ShowOptionsArgs
			{
				Sint32 fDialogID;
				Sint32 fStartingItemID;
				StyleBlob fStyleBlob;
				std::function<void(Sint32/*itemHit*/, ShowOptionsArgs&)> fDialogCallback = nullptr;
			};

			struct Operation
			{
				Event fEvent;
				Scene fScene;

				union
				{
					void* fExtensionArgs = nullptr;
					ActivateArgs* fActivateArgs;
					DeactivateArgs* fDeactivateArgs;
					ReactivateArgs* fReactivateArgs;
					FramebufferResizeArgs* fFramebufferResizeArgs;
					CancelRenderArgs* fCancelRenderArgs;
					ShowOptionsArgs* fShowOptionsArgs;
				};
			};

			// Image data has no padding at end of rows, its format has R before B, as in RGBA and not BGRA.
			// The number of bytes allocated in pixels (if non-null) is w*h*channels*(dataType==Byte ? 1 : 4);
			struct Image
			{
				Sint32 fWidth = 0;
				Sint32 fHeight = 0;
				Sint32 fChannels = 0;
				ChannelDataType fDataType = ChannelDataType_Byte;
				unsigned char* fPixels = nullptr;
			};

			struct CompositeLayers
			{
				bool fBackground = false;
				bool fPlanar = true;
				bool fUnfilled = true;
				bool fTriangles = true;
				bool fWireframe = true;
				bool fClipCubeCaps = true;
				bool fPoints = true;
				bool fEdges = false;
			};

		}
	}
}
