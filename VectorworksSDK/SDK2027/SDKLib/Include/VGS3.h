#pragma once
#include <string>
#include <vector>
#include <optional>
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "vgs3Handle.h"
#include "vgs3Standalone.h"
#include "vgs.h" // empty file in _CONSOLE build
#include <optional>

namespace vgs3 {

template<typename T>
bool HasFlag(T flags, const T flag) {
	return int(flags) & int(flag);
}

enum NodeType {
	NT_Unknown,
	NT_Generic,				// root, layers, containers (groups/walls/etc.), meshes/geometry, and saved views/backgrounds.
							// Call gSDK->GetObjectType(GetMCObjectHandle(n)) for the specific VW type:
							// kHeaderNode = root, kLayerNode = layer, saveViewNode = saved view, etc.
	NT_Definition,			// a kSymDefNode or kLayerNode node that lives under the root and can be instanced via NT_Instance nodes
	NT_TextureDefinition,	// a kTextureNode referenced by NT_TextureInstance nodes
	NT_Instance,			// a kSymbolNode or kLayerRefNode node that is an instance of an NT_Definition node
	NT_TextureInstance,		// a vgs3 only node that references a NT_TextureDefinition
	NT_MeshPart,			// a vgs3 only node created in the aux of a tessellated NT_Generic node
	NT_TextureDefinitionContainer,	// a vgs3 only node under the root's aux that holds all NT_TextureDefinition nodes
	NT_SavedViewContainer,	// a vgs3 only node under the root's aux that holds all saved view (savedViewNode) NT_Generic nodes
	NT_LayerContainer,		// a vgs3 only node under the root's aux taht holds all design layers (kLayerNode) NT_Generic nodes
};

enum DirtyFlag {
	DF_None = 0,						// node is not dirty
	DF_NodeAdded = 1 << 0,				// node was added to the scenegraph (it became visible)
	DF_NodeRemoved = 1 << 1,			// node is about to be removed from the scenegraph (it went invisible or was deleted)
	DF_TransformModified = 1 << 2,		// node's local transform has been modified (use gSDK->GetEntityMatrix())
	DF_Any = 1 << 3,					// assume anything could be dirty
	DF_TessellationModified = 1 << 4,	// node's tessellation is dirty (use Tessellate())
	DF_CameraModified = 1 << 5,			// camera has changed (root flag; use GetCamera())
	DF_ClipCubeModified = 1 << 6,		// clip cube has changed (root flag; use GetCliCube())
	DF_BackgroundModified = 1 << 7,		// background has changed (root flag; use GetBackground())
	DF_DefinitionSwitched = 1 << 9,		// NT_Instance was changed to point to a different NT_Definition
	DF_VisibilityModified = 1 << 10,	// one or more mesh instances had its visibility changed (use VisibilityModifiedArgs())
	DF_LayerModified = 1 << 11,			// design layer visibility changed, or layer was created (layer node flag; use GetMCObjectHandle() + gSDK)
	DF_ActiveLayerModified = 1 << 12,	// active layer changed (root flag; use gSDK->GetActiveLayer())
	DF_LayerOptionsModified = 1 << 13,	// layer options changed (root flag; use gSDK->GetLayerOptions())
	DF_ObjectRenamed = 1 << 14,			// node's object name (RefName) was added, changed, or removed (use GetMCObjectHandle() + gSDK->GetObjectName())
};

enum VisFlag {
	VF_Normal = 1 << 0,
	VF_Invisible = 1 << 1,
	VF_Gray = 1 << 2,
	VF_Ghost = 1 << 3,
};

struct NodeHandle : public handle::Handle { explicit operator bool() const; };

typedef std::vector<NodeHandle> VGSInstanceBranch;

// Node queries functions
NodeHandle					Next(NodeHandle n);
NodeHandle					FirstChild(NodeHandle n);
NodeHandle					FirstAux(NodeHandle n);
NodeHandle					Parent(NodeHandle n);
NodeType					Type(NodeHandle n);
NodeHandle					InstanceOf(NodeHandle n);
DirtyFlag					DirtyFlags(NodeHandle n);
UuidStorage					Uuid(NodeHandle n);
MCObjectHandle				GetMCObjectHandle(NodeHandle n);
VGSInstanceBranch			InstanceReferencers(NodeHandle n);
bool						DirtyChildrenBranch(NodeHandle n);
bool						DirtyAuxBranch(NodeHandle n);
std::vector<std::pair<VGSInstanceBranch, VisFlag>> VisibilityModifiedArgs(NodeHandle n);

// Returns every unique path (root -> start node -> ... -> n) through the scenegraph that reaches n,
// expanding through instanceReferencers wherever a definition is shared by multiple NT_Instance nodes.
// Matches the branch format returned by VisibilityModifiedArgs.
std::vector<VGSInstanceBranch> GetInstancePaths(NodeHandle n);

// Root functions
NodeHandle									GetScenegraphRoot();
VGSInstanceBranch							GetStartNodes(NodeHandle root);
::VGS::CameraModifyArgs						GetCamera(NodeHandle root);
std::optional<::VGS::ClipCubeModifyArgs>	GetClipCube(NodeHandle root);
MCObjectHandle								GetBackground(NodeHandle root);
int											GetScenegraphDirtyCount(NodeHandle root);

// Tessellation function
// Call this on a node with DF_TessellationModified to clear the flag and retrieve the tessellation and texture data.
// new texture definition nodes may be created (as a child of the root) as a result of tessellation.
void Tessellate(NodeHandle h, ::VGS::Tessellation& tessellation, VGSInstanceBranch& meshParts, ::VGS::TessellationQuality quality = ::VGS::TessellationQuality_Unspecified);

// Texture functions
MCObjectHandle GetTextureShaderRecord(NodeHandle texDef, ShaderFamily family, bool* isOverrideData = nullptr);
glm::ivec2 GetTextureRepeats(NodeHandle tex, bool* isOverrideData = nullptr); // .x is repeats in u direction, .y is in v direction

// Utility functions
std::string NodeTypeToString(NodeType nt);
std::string DirtyFlagsToString(DirtyFlag f);
NodeHandle	SavedViewContainer();
NodeHandle	TextureDefinitionContainer();
NodeHandle	LayerContainer();

// Logging
void SetLogFolderPath(std::string_view logFolderPath = "");
std::string_view GetLogFolderPath();
std::ostream& Log();


}
