// This file, and code under compile flag VGS3_CONSOLE exists to support testing vgs3 outside of vectorworks.
//
// Prompt for Claude to create the standalone test project and open it in Visual Studio:
//   "At the top of VGS3Standalone.h there is a block comment with instructions to build a new
//    testing project. Follow those steps and open the solution file with Visual Studio.
//    Create the project at AppSource/ThirdPartySource/VGM/source/VGS3ConsoleTest/.
//    The project is a console application (x64, C++20, VS 2022 toolset v143).
//    The only source file is ../SyncEngine/vgs3.cpp -- do not create a main.cpp, main() is
//    already defined in this file (VGS3Standalone.h) under the VGS3_CONSOLE flag.
//    vgs3.cpp unconditionally includes stdafx.h, so create a minimal stdafx.h and stdafx.cpp
//    in the project directory for the precompiled header.
//    Set these preprocessor definitions: VGS3_CONSOLE, _CONSOLE, WIN32, _WIN64.
//    Set these additional include paths:
//      .                                 (project dir, for stdafx.h)
//      ../SyncEngine                     (for vgs3Internal.h)
//      ../../../../Source/SDKLib/Include (for VGS3.h, VGS.h, VGS3Handle.h, VGS3Standalone.h, glm/)
//    Do not check the new folder into Perforce."

#pragma once

#ifdef VGS3_CONSOLE
// simulate VW API in standalone build
struct UuidStorage;
typedef glm::dvec3 WorldPt3;
typedef glm::dvec2 WorldPt;
typedef std::string TXString;
typedef UuidStorage InternalIndex;
typedef bool Boolean;
typedef int Sint32;

namespace vgs3 {
struct NodeHandle;
void Test(int);
}

enum ShaderFamily {
	kShaderFamily_Undefined = 0,
	kShaderFamily_Color = 1,
	kShaderFamily_Reflectivity = 2,
	kShaderFamily_Transparency = 3,
	kShaderFamily_Bump = 4,
	kShaderFamily_Background = 5,
	kShaderFamily_Foreground = 6,
	kShaderFamily_Sketch = 7,
	kShaderFamily_MaterialOption = 8,
	kShaderFamily_Mask = 9,
	kShaderFamily_Luminance = 10
};

struct MCObjectType : public handle::Handle {
	MCObjectType() {}
	template<typename T> operator T() { return T((handle::Handle&)(*this)); }
};

typedef MCObjectType* MCObjectHandle;

struct UuidStorage : public handle::Handle {
	UuidStorage() {}
	UuidStorage(handle::Handle h) { (handle::Handle&)*this = h; }
	UuidStorage(const TXString& str) {};
	bool IsEmpty() { return *this == handle::Handle{}; }
	void Reset() { *this = handle::Handle{}; }
	MCObjectHandle h = nullptr;
};

typedef void* CallBackPtr;
typedef void (*GS_ForEachObjectProcPtr)(MCObjectHandle h, CallBackPtr cbp, void *env);

struct TransformMatrix {
	double mat[4][3];
	void SetToIdentity();
};

enum TexturePartSDK
{
	kTexturePart_Overall = 0,

	kTexturePart_ExtrudeSweep_Top = 1,
	kTexturePart_ExtrudeSweep_Bottom = 2,
	kTexturePart_ExtrudeSweep_Sides = 3,
};

class CSDK {
public:
	MCObjectHandle GetObjectByUuidN(UuidStorage uuid);
	bool GetObjectUuidN(MCObjectHandle h, UuidStorage& uuid);
	MCObjectHandle GetDefinition(MCObjectHandle h);
	void GetEntityMatrix(MCObjectHandle h, TransformMatrix& m);
	void SetEntityMatrix(MCObjectHandle h, const TransformMatrix& m);
	short GetObjectTypeN(MCObjectHandle h);
	MCObjectHandle CreateLayer();
	MCObjectHandle GetActiveLayer();
	MCObjectHandle CreateSphere(const WorldPt3, double radius);// create / attach under active design layer
	MCObjectHandle GetDrawingHeader(); // create / get root
	MCObjectHandle CreateSymbolDefinition(TXString& name); // create / attach def node under root
	MCObjectHandle CreateGroup(); // create container node and attach under active design layer
	void AddObjectToContainer(MCObjectHandle child, MCObjectHandle parent); // detach and then attach 1st to 2nd parameter
	void DeleteObject(MCObjectHandle h, bool useUndo = true);
	MCObjectHandle PlaceSymbolN(MCObjectHandle def, const WorldPt& position, double angle); // create instance node to d1 with give translation/z-rotation
	MCObjectHandle FirstMemberObj(MCObjectHandle h);
	MCObjectHandle NextObject(MCObjectHandle h);
	MCObjectHandle ParentObject(MCObjectHandle h);
	void ForEachObject(short traverseWhat, GS_ForEachObjectProcPtr action, void *actionEnv);
	MCObjectHandle CreateTexture();
	InternalIndex GetTextureRef(MCObjectHandle object, short multiPartID, Boolean resolveByClass);
	void SetTextureRef(MCObjectHandle object, InternalIndex textureRef, short multiPartID);
	InternalIndex GetTextureRef(MCObjectHandle object, TexturePartSDK texPartID, Sint32 texLayerID, Boolean resolveByClass);
	InternalIndex GetObjectInternalIndex(MCObjectHandle h);
	bool Kludge(short selector, void* in, void* out);
	short GetObjectType(MCObjectHandle h);
	MCObjectHandle FindAuxObject(MCObjectHandle owner, short objectType);

};
extern CSDK* gSDK;

typedef Sint32 TInternalID;
const TInternalID kInternalID_TaperedExtrude = 388;
const TInternalID kInternalID_ExtrudeAlongPath = 108;
const TInternalID kInternalID_Subdivision = 526;

namespace VWFC::VWObjects {
class VWParametricObj {
public:
	static bool IsParametricObject(MCObjectHandle);
	static bool IsParametricObject(MCObjectHandle, const TXString&);
	static bool IsParametricObject(MCObjectHandle, TInternalID);
	template<typename... TInternalIDs>
	static inline bool IsParametricObject(MCObjectHandle hObj, TInternalID ID, TInternalIDs... IDs)
	{
		return IsParametricObject(hObj) && setmember(GetInternalID(hObj), ID, IDs...);
	}
	static TInternalID GetInternalID(MCObjectHandle);
};

}

int main(int, char**) {
	vgs3::Test(1);
	return 0;
}

#endif