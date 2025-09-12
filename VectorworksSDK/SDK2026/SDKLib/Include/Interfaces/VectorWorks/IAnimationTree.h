#pragma once

#include "glm/glm.hpp"

namespace VectorWorks
{
namespace Animation 
{

typedef int Id; // Id refers to a node in the animation tree. see IAnimation::IsValidId()
const Id kUninitializedId = Id(-1);

typedef size_t ImageId; // ImageId refers to an image (e.g., can be used to animate the color image of a RW texture)
const ImageId kUninitializedImageId = ImageId(-1);

// InstanceBranch is a pathway from gSDK->GetDocumentHeader() down to a primitive graphical object or light
// in the Vectorworks document graph with 1 exception: when referring to an object in a symbol definition,
// the path should lead to the symbol instance and then jump to a node under the referring definition.
// The same path can be used multiple times under different nodes which has the effect of showing the referring geometry 
// multiple times in the animation.
typedef std::vector<MCObjectHandle> InstanceBranch; 

// identify object by uuid instance chain starting at DL. This UUID branch
// is special: if a handle has a persistant id tagdata ('p_id') then UUID is taken
// from it instead of the handle
typedef std::vector<UuidStorage> InstanceBranchUUID;

 
enum ChannelDataType
{
	ChannelDataType_Byte,	// 1 byte per channel - LDR
	ChannelDataType_Float,	// 4 bytes per channel - HDR

	__ChannelDataType_Count
};

enum CompressionType
{
	Uncompressed,
};

// all images must be 4 channel, 32bpp, with no padding
struct Image
{
	CompressionType compression = Uncompressed;
	int width = 0;
	int height = 0;
	bool dynamic = false;
	ChannelDataType dataType = ChannelDataType_Byte;
	std::shared_ptr<std::vector<unsigned char>> pixels = nullptr; // <-- uncompressed pixel data
};

enum LightBrightnessUnit
{
	Intensity,
	Lumens,
	Candelas,
	Lux,
	Footcandels,
};

struct LightTrainArgs {
	float beamAngle;
	float fieldAngle;
	float colorTemperature;
	float focus;
	float iris;
	float theta;
	ImageId lightmapImage;
	ImageId irisImage;
	struct MaskData
	{
		ImageId imgId;
		double rotation;
		bool hFlip;
		bool vFlip;
	};
	std::vector<MaskData> masks;

	ImageId outputImage = kUninitializedImageId; // optionally, outputImage is AllocateTempImage'd earlier and used in OverrideTexture for camera lens geometry

	struct ColorWheel
	{
		float position;

		struct ColorSlot
		{
			glm::vec3 color;
		};
		std::vector<ColorSlot> colorSlots;
	};
	std::vector<ColorWheel> colorWheels;

	struct GoboWheel
	{
		float gap;
		float position;
		float focus;
		float slotOrientation; ///@todo why isn't this per slot?

		struct GoboSlot
		{
			ImageId image;
		};
		std::vector<GoboSlot> goboSlots;
	};
	std::vector<GoboWheel> goboWheels;

	struct ColorFlag
	{
		float rotation;
		float orientation;
		float window;
		ImageId image;
		bool enabled;
	};
	std::vector<ColorFlag> colorFlags;

	struct PrismFacet
	{
		glm::mat4 transform;
		float prismRotation; ///@note rotation around the center of the beam
		float individualRotation; ///@note rotation around the center of the facet
		bool enabled;
	};
	std::vector<PrismFacet> prismFacets;
};

enum class ImageMap
{
	Color,
	Normal,
	Reflection,

	NumImageMaps
};

class IAnimationTreeBuilder
{
public:
	virtual Id GetRootNodeId() = 0;
	virtual bool IsValidId(Id id) = 0;

	// AttachChild creates and initializes a 'newChild' node under 'parent'
	virtual void AttachChild(Id parent, Id& newChild) = 0;

	// Attach geometry and lights to a node by supplying the branch (see SampleUsage())
	virtual void AttachGeometry(Id node, const InstanceBranch& geometryH, glm::dmat4* transform = nullptr, bool lensUVMapping = false) = 0;
	virtual void AttachLight(Id node, const InstanceBranch& lightH, glm::dmat4* transform = nullptr) = 0;

	virtual void AttachGeometry(Id node, const InstanceBranchUUID& geometryH, glm::dmat4* transform = nullptr, bool lensUVMapping = false) = 0;
	virtual void AttachLight(Id node, const InstanceBranchUUID& lightH, glm::dmat4* transform = nullptr) = 0;

	virtual ImageId OverrideTexture(const InstanceBranch& object, 
		const TXString& part = "3",					// <-- can be the string name of a texture part such as "3" for kTexturePart_Overall. can be face moniker such as "FACE.19.18.4.0.0.0.Extrude:0,0:0,0:29"
		int textureLayer = 0,						// <-- texture layers are for decals. 0 is base layer
		ImageMap imageMap = ImageMap::Color,		// <-- which map is being overridden
		ImageId overrideId = kUninitializedImageId	// <-- previously allocated ImageId (with AllocTempImage)
	) = 0;
};

enum Event
{
	Event_Unknown,

	Event_Start,
	Event_Stop,
	Event_DocumentModified,
	Event_Pause,
	Event_Resume,
};

struct StartArgs
{
	MCObjectHandle startHandle; // could be header for design environment, or a temp layer created by viewport update containing layer refs
	IAnimationTreeBuilder* treeBuilder;

	std::function<void()> safeStartAnimationThreadCB; // output from event
};

struct StopArgs
{
};

struct DocumentModifiedArgs
{
	std::vector<MCObjectHandle> handles;
	bool rebuildAnimationTree = false;  // output from event
};

struct PauseArgs
{
};

struct ResumeArgs
{
};

struct Operation
{
	Event event;
	union {
		void* extensionArgs = nullptr;
		StartArgs* startArgs;
		StopArgs* stopArgs;
		DocumentModifiedArgs* documentModifiedArgs;
		PauseArgs* pauseArgs;
		ResumeArgs* resumeArgs;
	};
};

static const VWIID IID_Animation = { 0xb6146833, 0x2ef6, 0x485b, { 0x82, 0xfc, 0x65, 0xa7, 0x27, 0xe, 0x5a, 0x2b } };

// Use IAnimation to build a scene graph for animation in VW.
// To use, call StartAnimation and provide the event handler callback. Build a hirerarchy of nodes that refer to MCObjectHandles in the 
// Start event an spawn your animation thread.  For each iteration, modify the 
// node transforms and other parameters and then call CommitChanges (see SampleUsage())
class DYNAMIC_ATTRIBUTE IAnimation : public VectorWorks::Extension::IEventSink
{
public:
	virtual void VCOM_CALLTYPE SampleUsage() = 0; // <-- learn how to use IAnimation
	
	virtual Id VCOM_CALLTYPE GetRootNodeId() = 0;
	virtual bool VCOM_CALLTYPE IsValidId(Id id) = 0;

	virtual void VCOM_CALLTYPE StartAnimation(std::function<void(Operation&)> eventHandler, 
		MCObjectHandle startHandle = nullptr) = 0;  // eventHandler is invoked to notify client of something important
	virtual void VCOM_CALLTYPE StopAnimation() = 0;
	
	virtual bool VCOM_CALLTYPE IsInAnimationTree(MCObjectHandle h) = 0;

	virtual size_t VCOM_CALLTYPE StartRecording() = 0;
	virtual bool VCOM_CALLTYPE StopRecording() = 0;
	virtual bool VCOM_CALLTYPE PlayRecording(size_t id) = 0;
	virtual bool VCOM_CALLTYPE DeleteRecording(size_t id) = 0;
	virtual bool VCOM_CALLTYPE IsValidRecording(size_t id) = 0;
	virtual size_t VCOM_CALLTYPE ImportRecording(const TXString& filename) = 0;
	virtual bool VCOM_CALLTYPE ExportRecording(size_t id, const TXString& filename) = 0;

	// Allocate an image for use with SetImage. They are automatically deallocated when animation stops
	virtual ImageId AllocateTempImage() = 0;
		
	// mark changes to the animation tree while the animation is running.
	// These ought be used from a background thread (see SampleUsage()).
	// Transform is applied to the geometry and lights attached to 'node'
	virtual void VCOM_CALLTYPE SetTransform(Id node, const glm::dmat4& transform) = 0;
	
	// set properties of all lights attached to node
	virtual void VCOM_CALLTYPE SetLightPosition(Id node, const glm::dvec3& position) = 0;
	virtual void VCOM_CALLTYPE SetLightDirection(Id node, const glm::dvec3& direction) = 0;
	virtual void VCOM_CALLTYPE SetLightColor(Id node, const glm::dvec3& color) = 0;
	virtual void VCOM_CALLTYPE SetLightSpread(Id node, double innerAngle, double outerAngle) = 0;
	virtual void VCOM_CALLTYPE SetLightBrightness(Id node, double brightness, LightBrightnessUnit unit) = 0;
	virtual void VCOM_CALLTYPE SetLightTrainArgs(Id node, const LightTrainArgs& args) = 0;
	virtual void VCOM_CALLTYPE SetLightNearClip(Id node, double distance) = 0;
	
	// experiment v1
	// these parameters are temporary and are restored when animation stops
	virtual void VCOM_CALLTYPE SetCameraAperature(double aperature) = 0; // <-- for use wih DOF and Exposure
	virtual void VCOM_CALLTYPE SetCameraDOF(bool enable, double focusDistance) = 0;
	virtual void VCOM_CALLTYPE SetCameraExposure(bool enable, double iso, double shutter) = 0;
	virtual void VCOM_CALLTYPE SetCameraBloom(bool enable, double percentage) = 0;
	virtual void VCOM_CALLTYPE SetCameraPosition(const glm::dvec3& pos, const glm::dvec3& forward, const glm::dvec3& up) = 0;
	virtual void VCOM_CALLTYPE SetCameraFOV(double fov) = 0;

	// v2 experiments
	// concurrent IAnimation usage from multiple plugins
	// virtual void VCOM_CALLTYPE SetHazeArgs( HaceArgs& haze) = 0;

	// Update pixel data of 'imageId'. This can be used to project a movie from a light, or play a movie on geometry
	virtual void VCOM_CALLTYPE SetImage(ImageId id, Image& textureImage) = 0;

	// Gets?

	// animation changes are all applied together when CommitChangesis called (see SampleUsage())
	virtual void VCOM_CALLTYPE CommitChanges() = 0;
};

}
}
