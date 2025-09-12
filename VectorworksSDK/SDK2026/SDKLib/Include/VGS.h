//
// Vectorworks Graphics Sync (VGS) API
// VGS is an API for communicating grpahics changes from Vectorworks to plugins as they 
// occur.  The render plugin callback is invoked on a background thread.
//
// Dependencies
//		glm
//		standard c++ libraries
//

#ifndef VGS_h
#define VGS_h

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <glm/glm.hpp>

struct uint128
{
public:
	uint64_t lhs;
	uint64_t rhs;

	uint128() : lhs(0), rhs(0) {}
	uint128(const uint128 & inInt) : lhs(inInt.lhs), rhs(inInt.rhs) {}
	uint128(const uint64_t& inInt) : lhs(0), rhs(inInt) {}
	uint128(const uint64_t& inLHS, const uint64_t& inRHS) : lhs(inLHS), rhs(inRHS) {}
	uint128(void* inInt) : lhs(0), rhs(uintptr_t(inInt)) {}

	bool operator<(const uint128& inInt) const
	{
		if( inInt.lhs == lhs )
			return rhs < inInt.rhs;
		else
			return lhs < inInt.lhs;
	}

	bool operator>(const uint128& inInt) const
	{
		if( lhs == inInt.lhs )
			return rhs > inInt.rhs;
		else
			return lhs > inInt.lhs;
	}

	bool operator==(const uint128& inInt) const
	{
		return inInt.lhs == lhs && inInt.rhs == rhs;
	}

	bool operator!=(const uint128& inInt) const
	{
		return inInt.lhs != lhs || inInt.rhs != rhs;
	}

	uint128 & operator=(const uint128 & inInt) {
		lhs = inInt.lhs;
		rhs = inInt.rhs;
		return *this;
	}

	uint128 & operator=(uint128 && inInt) {
		if( this != &inInt ) {
			lhs = std::move(inInt.lhs);
			rhs = std::move(inInt.rhs);
			inInt.lhs = 0;
			inInt.rhs = 0;
		}
		return *this;
	}

};

typedef uint128 VGS_ID;
typedef std::vector<std::vector<glm::dvec2>> UVSetList;
typedef std::vector<std::vector<VGS_ID>> MaterialIDList;

namespace VGS
{

enum Event
{
	Event_Unknown,

	Event_ChangeBlockBegin,
	Event_ChangeBlockEnd,

	Event_ListenerSetup,
	Event_ListenerSetdown,

	Event_TessellationAdd,
	Event_TessellationRemove,
	Event_TessellationModify,

	Event_ObjectAdd,
	Event_ObjectRemove,
	Event_ObjectModifyTransform,
	Event_ObjectModifyMaterial,

	Event_MaterialAdd,
	Event_MaterialRemove,
	Event_MaterialModify,

	Event_CameraModify,

	Event_LightAdd,
	Event_LightRemove,
	Event_LightModify,

	Event_ProxyObjectAdd,
	Event_ProxyObjectModify,
	Event_ProxyObjectRemove,

	Event_ClipCubeAdd,
	Event_ClipCubeModify,
	Event_ClipCubeRemove,

	Event_ClipShadows,

	Event_BackgroundAdd,
	Event_BackgroundRemove,
	Event_BackgroundModify,

	__Event_Count
};

enum LightType
{
	Directional,
	Point,
	Spot,
	Mesh,
	IES,
	Ambient,

	__LightType_Count
};

enum LightBrightnessUnit
{
	Intensity,
	Lumens,
	Candelas,
	Lux,
	Footcandels,

	__LightBrightnessUnit_Count
};

enum LightAttenuation
{
	None,
	Linear,
	Quadratic,
	
	__LightAttenuation_Count
};

enum ChannelDataType
{
	ChannelDataType_Byte,	// 1 byte per channel - LDR
	ChannelDataType_Float,	// 4 bytes per channel - HDR

	__ChannelDataType_Count
};

enum TessellationQuality
{
	TessellationQuality_Low,
	TessellationQuality_Medium,
	TessellationQuality_High,
	TessellationQuality_VeryHigh,
	TessellationQuality_Unspecified
};


// Image data has no padding at end of rows, its format has R before B, as in RGBA and not BGRA.
// The number of bytes allocated in pixels (if non-null) is w*h*channels*(dataType==Byte ? 1 : 4);
struct Image
{
	int width = 0;
	int height = 0;
	int channels = 0;
	ChannelDataType dataType = ChannelDataType_Byte;
	unsigned char* pixels = nullptr;
};

struct TessellationSubpart
{
	std::vector<glm::dvec3> positions;
	std::vector<glm::dvec3> normals;
	UVSetList uvs;
	std::vector<glm::ivec3> triangleIndices;
};

struct Tessellation
{
	std::vector<TessellationSubpart> subparts;
	bool isVolumetric;
};

struct TessellationAddArgs
{
	VGS_ID tessellationID;
};

struct TessellationModifyArgs
{
	VGS_ID tessellationID;
	Tessellation tessellation;
};

struct TessellationRemoveArgs
{
	VGS_ID tessellationID;
};

struct ObjectAddArgs
{
	VGS_ID objectID;
	VGS_ID tessellationID;
	VGS_ID proxyID;
};

struct ObjectRemoveArgs
{
	VGS_ID objectID;
};

struct ObjectModifyTransformArgs
{
	VGS_ID objectID;
	glm::dmat4 transform;
};

struct ObjectModifyMaterialArgs
{
	VGS_ID objectID;
	MaterialIDList materialIDs;
};

struct ProxyObjectAddArgs
{
	VGS_ID proxyID;
};

struct ProxyObjectRemoveArgs
{
	VGS_ID proxyID;
};

struct ProxyObjectModifyArgs
{
	VGS_ID proxyID;
	std::vector<unsigned char> parameters;
};

struct MaterialAddArgs
{
	VGS_ID materialID;
	VGS_ID proxyID;
	std::string materialName;
};

struct MaterialRemoveArgs
{
	VGS_ID materialID;
};

//  uv=0.2,-1              uv=4.3,-1
//  +-------------------------+
//  |                         |       <--- A quad shape
//  |                         |
//  |----+-----+-----+-----+--|       diffuseImage is of a half smily face
//  |. . | . . | . . | . . | .|       
//  |__/ | __/ | __/ | __/ | _|       repeatHorizontal = true
//  |----+-----+-----+-----+--|		  repeatVertical = false
//  |                         |
//  |                         |
//  |     color               |       outside the repeat area is 'color'
//  |                         |          repeat area is uv 0,0 to 1,1
//  +-------------------------+
//  uv=0.3,3.2             uv=4.3,3.2
struct MaterialModifyArgs
{
	VGS_ID materialID;
	glm::dvec4 color;
	bool repeatHorizontal;
	bool repeatVertical;
	Image diffuseImage;		// <-- grayscale, RGB, or RGBA surface color
	Image maskImage;        // <-- single channel surface transparency

	Image bumpImage;
	double bumpAmplitude;

	Image reflectionImage;
	double reflectionAmplitude;
	double reflectionRoughness;

	bool castShadows;
	bool receiveShadows;
};

struct ChangeBlockBeginArgs
{
	VGS_ID changeID;
};

struct ChangeBlockEndArgs
{
	VGS_ID changeID;
};

struct CameraModifyArgs
{
	glm::dvec3 position;
	glm::dvec3 forward;
	glm::dvec3 up;

	//       p       position
	//     / d \     viewPlaneDistance
	//    /	 d	\
	//   /wwwdwww\   viewPlane width
	//  /         \
	//
	glm::dvec2 viewPlane;			// [0] = width, [1] = height
	double viewPlaneDistance = 0;	// 0 means orthographic projection, otherwise when combine with viewPlane defines perspective fov
	bool isPanoramic = false; // for renders that can perform panoramic renderings
};

struct LightAddArgs
{
	VGS_ID lightID;
	VGS_ID proxyID;
};

struct LightRemoveArgs
{
	VGS_ID lightID;
};

struct LightPoint
{
	glm::dvec3 position;
	glm::dvec3 color;
	double brightness;
	LightBrightnessUnit unit;
	LightAttenuation attenuation;
};

struct LightSpot
{
	glm::dvec3 position;
	glm::dvec3 direction;
	glm::dvec3 color;

	//           p			position
	//         / | \
	//        /  |  \
	//       /  | |  \
	//      /   | |   \
	//     /    | |    \
	//    /    |-i-|    \	innerAngle - full light
	//   /     |   |     \
	//  /------outer------\ outerAngle - fading light
	// /      |     |      \
	//
	double innerAngle;
	double outerAngle;
	double brightness;
	LightBrightnessUnit unit;
	LightAttenuation attenuation;
	Image projectedImage; 
	glm::dvec3 up; // projectedImage y axis aligns with up vec
};

struct LightDirectional
{
	glm::dvec3 direction;
	glm::dvec3 color;
	double brightness;
	LightBrightnessUnit unit;
};

struct LightMesh
{
	// NOTE: This event is an atomic operation, containing all necessary information except for the tessellation itself.
	glm::dvec3 color;
	VGS_ID tessellationID;
	glm::dmat4 transform;
	MaterialIDList materialIDs;
	double brightness;
	LightBrightnessUnit unit;
};

struct LightIES
{
	// NOTE: This event is an atomic operation, containing all necessary information in one event.
	glm::dvec3 color;
	glm::dmat4 transform;
	std::vector<unsigned char> iesFile; // Corresponds to a file following the IES standard. Visit https://www.ies.org/standards/ies-lighting-library/ for more information.
	double brightness;
	LightBrightnessUnit unit;
	LightAttenuation attenuation;
};

struct LightAmbient
{
	glm::dvec3 color;
	double brightness;
	LightBrightnessUnit unit;
};

struct LightModifyArgs
{
	VGS_ID lightID;

	LightType lightType;
	union
	{
		LightPoint* point = nullptr;
		LightSpot* spot;	
		LightDirectional* directional;
		LightMesh* mesh;
		LightIES* ies;
		LightAmbient* ambient;
	};
};

struct ClipCubeAddArgs
{
	VGS_ID clipCubeID;
	std::uint32_t setID; // visible triangles must be in one of the cubes from each set
};

struct ClipCubeModifyArgs
{
	VGS_ID clipCubeID;
	std::array<glm::dvec4, 6> clipPlanes; // Represents plane equation (Ax + By + Cz = D), where vec4 is (A,B,C,D)
};

struct ClipCubeRemoveArgs
{
	VGS_ID clipCubeID;
};

struct ClipShadowsArgs
{
	bool clipShadows; // if true then clipped objects won't cast shadows and vice versa
};

struct BackgroundAddArgs
{
	VGS_ID backgroundID;
};

struct BackgroundRemoveArgs
{
	VGS_ID backgroundID;
};

struct BackgroundModifyArgs
{
	VGS_ID   backgroundID;
};

/*Clients can modify these values to tell VGS to behave differently with regards to the current VGS listener.*/
struct ListenerSetupArgs
{
	TessellationQuality tessellationQuality; // specifies tessellation quality for all objects targeting this listener
	bool autoRotateObjects; // auto rotates objects targeting this listeneer towards the camera when applicable
	bool flipNormals; // flips all normals specifically for this listener
	bool flipTriangleWinding; // flips the winding for all triangles for this listener
	std::pair<uint64_t, void*> hostData; // provide hostData for VGS to process
	bool useTextureColor;	// sets to pick the color from either the texture or tessellation based on renderer settings
};

struct ListenerSetdownArgs
{
};

struct Operation
{
	Event event;
	VGS_ID scene;
	void* hostData = nullptr;

	// use completedOperations/totalOperations to calculate the progress of the VGS stream
	size_t completedOperations;
	size_t totalOperations;

	union
	{
		void* extensionArgs = nullptr;
		TessellationAddArgs* tessellationAddArgs;
		TessellationRemoveArgs* tessellationRemoveArgs;
		TessellationModifyArgs* tessellationModifyArgs;
		ObjectAddArgs* objectAddArgs;
		ObjectRemoveArgs* objectRemoveArgs;
		ObjectModifyTransformArgs* objectModifyTransformArgs;
		ObjectModifyMaterialArgs* objectModifyMaterialArgs;
		ProxyObjectAddArgs* proxyObjectAddArgs;
		ProxyObjectRemoveArgs* proxyObjectRemoveArgs;
		ProxyObjectModifyArgs* proxyObjectModifyArgs;
		ClipCubeAddArgs* clipCubeAddArgs;
		ClipCubeModifyArgs* clipCubeModifyArgs;
		ClipCubeRemoveArgs* clipCubeRemoveArgs;
		ClipShadowsArgs* clipShadowsArgs;
		MaterialAddArgs* materialAddArgs;
		MaterialRemoveArgs* materialRemoveArgs;
		MaterialModifyArgs* materialModifyArgs;
		ChangeBlockBeginArgs* changeBlockBeginArgs;
		ChangeBlockEndArgs* changeBlockEndArgs;
		CameraModifyArgs* cameraModifyArgs;
		LightAddArgs* lightAddArgs;
		LightRemoveArgs* lightRemoveArgs;
		LightModifyArgs* lightModifyArgs;
		BackgroundAddArgs* backgroundAddArgs;
		BackgroundRemoveArgs* backgroundRemoveArgs;
		BackgroundModifyArgs* backgroundModifyArgs;
		ListenerSetupArgs* listenerSetupArgs;
		ListenerSetdownArgs* listenerSetdownArgs;
	};
	void* internalData  = nullptr;
};

}

#endif
