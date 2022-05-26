//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Contains definitions of values allowing communication between the main VW
// application and the Render Options plug-in.
//


#pragma once

// render preferences enumerations

enum RWShadowStyle {
	kRWShadowMapped = 1,
	kRWShadowRayTraced = 2
};

enum {
	kDetailLow = 1,
	kDetailMedium = 2,
	kDetailHigh = 3,
	kDetailVeryHigh = 4
};

enum {
	kTessellationDetailLow = 1,
	kTessellationDetailMedium = 2,
	kTessellationDetailHigh = 3,
	kTessellationDetailVeryHigh = 4
};
enum {
	kGLShadowSoftnessLow = 1,
	kGLShadowSoftnessMedium = 2,
	kGLShadowSoftnessHigh = 3
};

// API constants for calling the Render Settings library

const short kRWOptionsStructPtr		= 0;

const short kRWUseTextures			= 0;
const short kRWUseTransparency		= 1;
const short kRWUseShadows			= 2;
const short kRWUseRayTracing		= 3;
const short kRWUseAntiAliasing		= 4;
const short kRWUseNURBS				= 5;
const short kRWTessellationDetail	= 6;
const short kRWShadowStyle			= 7;
const short kRWRayTracingRecursion	= 8;

const short kOpenGLOptionsStructPtr = 0;

const short kHLSmoothingAngle		= 0;
const short kHLLineStyle			= 1;
const short kHLShadeFactorIndex		= 2;
const short kHLSketchHiddenLine		= 3;
const short kHLDoIntersections		= 4;
const short kHLDoSurfaceHatches		= 5;
const short kHLDoTextAndMarkers		= 6;

const short kRWUpdateRender			= 0;


const short kGLUpdateRender			= 0;
const short kGLDisposeGeometry		= 1;  
const short kGLUpdateTexturing		= 2;
const short kGLAllowGraphicsRebuild = 3;

const short kHLUpdateRender			= 0;

const short kGLHandle				= 0;

const short kHLHandle				= 0;

const short kTranHLHandle			= 0;
const short kTranHLLineStyle		= 1;

// Struct passed back an forth between Core and RenderSettings
struct RWCustomOptions
{
	bool	fUseTextures;
	bool	fUseTransparency;
	bool	fUseShadows;
	bool	fUseRayTracing;
	bool	fUseAntiAliasing;
	bool	fUseNURBS;
	short	fTessellationDetail;
	short	fShadowStyle;
	short	fRayTracingRecursion;
	short 	fAreaLightDetail;
	short 	fShadowMapDetail;
	bool 	fTransparentShadows;
	bool 	fAutoExposure;
};

// Struct passed back and forth between Core and OpenGL Settings
struct OpenGLCustomOptions
{
	bool		fUseTextures;
	short		fTessellationDetail;
	bool		fUseAntiAliasing;
	bool		fUseShadows;
	bool     	fDrawEdges;
	bool		fOnGroundOnly;
	short		fShadowSoftness;
	bool		fUseColors;
	short		fCreaseAngle;
	int			fEdgeThickness;
};

// Shader families and prototypes constants

typedef enum {
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
} ShaderFamily;

#define GRASS_SHADER_ENABLED

enum ShaderPrototypeColor {
	kShaderPrototypeColor_Plain = 40,
	kShaderPrototypeColor_Image = 41,
	kShaderPrototypeColor_Fresnel = 42,
	kShaderPrototypeColor_Noise = 43,
	kShaderPrototypeColor_Tiles = 44,
	kShaderPrototypeColor_Bricks = 45,
	kShaderPrototypeColor_Pavement = 46
#if defined GRASS_SHADER_ENABLED
	, kShaderPrototypeColor_Grass = 47
#endif	// #if defined GRASS_SHADER_ENABLED
};

enum ShaderPrototypeReflectivity {
	kShaderPrototypeReflectivity_Image = 30,
	kShaderPrototypeReflectivity_Mirror = 31,
	kShaderPrototypeReflectivity_Fresnel = 32,
	kShaderPrototypeReflectivity_Noise = 33,
	kShaderPrototypeReflectivity_Tiles = 34,
	kShaderPrototypeReflectivity_Plastic = 35,
	kShaderPrototypeReflectivity_Bricks = 36,
	kShaderPrototypeReflectivity_Pavement = 37,
	kShaderPrototypeReflectivity_Glow = 38,
	kShaderPrototypeReflectivity_Backlit = 39,
	kShaderPrototypeReflectivity_Anisotropic = 40,
    kShaderPrototypeReflectivity_Cloth = 41
};

enum ShaderPrototypeTransparency {
	kShaderPrototypeTransparency_Plain = 10,
	kShaderPrototypeTransparency_Color = 11,
	kShaderPrototypeTransparency_Image = 12,
	kShaderPrototypeTransparency_Glass = 13,
	kShaderPrototypeTransparency_Noise = 14,
	kShaderPrototypeTransparency_Tiles = 15,
	kShaderPrototypeTransparency_Bricks = 16,
	kShaderPrototypeTransparency_Pavement = 17,
	kShaderPrototypeTransparency_RectangularMask = 18,
	kShaderPrototypeTransparency_ImageMask = 19,
	kShaderPrototypeTransparency_ShadowCatcher = 20
};

enum ShaderPrototypeBump {
	kShaderPrototypeBump_Image = 41,
	kShaderPrototypeBump_Noise = 42,
	kShaderPrototypeBump_Tiles = 43,
	kShaderPrototypeBump_Bricks = 44,
	kShaderPrototypeBump_Pavement = 45
};


const short kNumPrototypeSketchShaders = 30;

enum ShaderPrototypeSketch {
	kShaderPrototypeSketch_Sketch_1 = 13,
	kShaderPrototypeSketch_Sketch_2 = 14,
	kShaderPrototypeSketch_Sketch_3 = 15,
	kShaderPrototypeSketch_Sketch_4 = 16,
	kShaderPrototypeSketch_Sketch_5 = 17,
	kShaderPrototypeSketch_Sketch_6 = 18,
	kShaderPrototypeSketch_Sketch_7 = 19,
	kShaderPrototypeSketch_Sketch_8 = 20,
	kShaderPrototypeSketch_Sketch_9 = 21,
	kShaderPrototypeSketch_Sketch_10 = 22,
	kShaderPrototypeSketch_Sketch_11 = 23,
	kShaderPrototypeSketch_Sketch_12 = 24,
	kShaderPrototypeSketch_Sketch_13 = 25,
	kShaderPrototypeSketch_Sketch_Hatch = 26,
	kShaderPrototypeSketch_Sketch_Art = 27,
	kShaderPrototypeSketch_Sketch_Cartoon = 28,
	kShaderPrototypeSketch_Sketch_Shadow = 29,
	kShaderPrototypeSketch_Sketch_18 = 30,	// Plain edge-only style
	kShaderPrototypeSketch_Sketch_19 = 31,
	kShaderPrototypeSketch_Sketch_20 = 32,
	kShaderPrototypeSketch_Sketch_21 = 33,
	kShaderPrototypeSketch_Sketch_22 = 34,
	kShaderPrototypeSketch_Sketch_23 = 35,
	kShaderPrototypeSketch_Sketch_24 = 36,
	kShaderPrototypeSketch_Sketch_25 = 37,
	kShaderPrototypeSketch_Sketch_26 = 38,
	kShaderPrototypeSketch_Sketch_27 = 39,
	kShaderPrototypeSketch_Sketch_28 = 40,
	kShaderPrototypeSketch_Sketch_29 = 41,
	kShaderPrototypeSketch_Sketch_30 = 42,
	kShaderPrototypeSketch_Sketch_31 = 43
};

enum ShaderPrototypeForeground {
	kShaderPrototypeForeground_LitFog = 5
};

// shader types
enum ShaderNoiseType {
	kShaderNoiseType_Box = 0,
	kShaderNoiseType_BlisteredTurbulence = 1,
	kShaderNoiseType_Buya = 2,
	kShaderNoiseType_CellNoise = 3,
	kShaderNoiseType_Cranal = 4,
	kShaderNoiseType_Dents = 5,
	kShaderNoiseType_DisplacedTurbulence = 6,
	kShaderNoiseType_FBM = 7,
	kShaderNoiseType_Hama = 8,
	kShaderNoiseType_Luka = 9,
	kShaderNoiseType_ModNoise = 10,
	kShaderNoiseType_Naki = 11,
	kShaderNoiseType_Noise = 12,
	kShaderNoiseType_Nutous = 13,
	kShaderNoiseType_Ober = 14,
	kShaderNoiseType_Pezo = 15,
	kShaderNoiseType_Poxo = 16,
	kShaderNoiseType_RandomNoise = 17,
	kShaderNoiseType_Sema = 18,
	kShaderNoiseType_Stupl = 19,
	kShaderNoiseType_Turbulence = 20,
	kShaderNoiseType_VLNoise = 21,
	kShaderNoiseType_WavyTurbulence = 22,
	kShaderNoiseType_CellVoronoi = 23,
	kShaderNoiseType_DisplacedVoronoi = 24,
	kShaderNoiseType_SparseConvolution = 25,
	kShaderNoiseType_Voronoi1 = 26,
	kShaderNoiseType_Voronoi2 = 27,
	kShaderNoiseType_Voronoi3 = 28,
	kShaderNoiseType_Zada = 29,
	kShaderNoiseType_WoodNoise = 100,
	kShaderNoiseType_MarbleNoise = 101
};

enum ShaderTilesType {
	kShaderTilesType_Bricks1 = 0,
	kShaderTilesType_Bricks2 = 1,
	kShaderTilesType_Circles1 = 2,
	kShaderTilesType_Circles2 = 3,
	kShaderTilesType_Circles3 = 4,
	kShaderTilesType_Hexagons = 5,
	kShaderTilesType_Lines1 = 6,
	kShaderTilesType_Lines2 = 7,
	kShaderTilesType_Parquet = 8,
	kShaderTilesType_Planks = 9,
	kShaderTilesType_RadialLines1 = 10,
	kShaderTilesType_RadialLines2 = 11,
	kShaderTilesType_RandomTiles = 12,
	kShaderTilesType_Rings1 = 13,
	kShaderTilesType_Rings2 = 14,
	kShaderTilesType_Sawtooth1 = 15,
	kShaderTilesType_Sawtooth2 = 16,
	kShaderTilesType_Scales1 = 17,
	kShaderTilesType_Scales2 = 18,
	kShaderTilesType_Spiral1 = 19,
	kShaderTilesType_Spiral2 = 20,
	kShaderTilesType_Squares = 21,
	kShaderTilesType_Triangles1 = 22,
	kShaderTilesType_Triangles2 = 23,
	kShaderTilesType_Triangles3 = 24,
	kShaderTilesType_Waves1 = 25,
	kShaderTilesType_Waves2 = 26,
	kShaderTilesType_Weave = 27
};

////// Texture mapping info		-DLD 6/17/2008


// GetTextureRef and SetTextureRef functions can be more specific in 2009 about which class texture 
// to use for an object.  For example, calling SetTextureRef with -3 for the texture ref will texture the object 
// using the object's class' wall right texture.  -DLD 6/19/2008
enum {
	kTextureByClass_ByObjectType	= -1L,
	kTextureByClass_OtherType		= -2L,
	kTextureByClass_WallRight		= -3L,
	kTextureByClass_WallLeft		= -4L,
	kTextureByClass_WallCenter		= -5L,
	kTextureByClass_RoofTop			= -6L,
	kTextureByClass_RoofDormer		= -7L
};

enum TexturePartSDK
{
	kTexturePart_Overall				= 3,
			
	kTexturePart_ExtrudeSweep_Top		= 4,
	kTexturePart_ExtrudeSweep_Bottom	= 5,
	kTexturePart_ExtrudeSweep_Sides		= 6,
	
	kTexturePart_Wall_Left				= 7,
	kTexturePart_Wall_Right				= 8,
	kTexturePart_Wall_StartCap			= 9,
	kTexturePart_Wall_EndCap			= 10,
	kTexturePart_Wall_Top				= 11,
	kTexturePart_Wall_Bottom			= 12,
	kTexturePart_Wall_Holes				= 13,
	
	kTexturePart_Slab_Top				= 14,
	kTexturePart_Slab_Bottom			= 15,
	kTexturePart_Slab_Sides				= 16,
	
	kTexturePart_Roof_Top				= 17,
	kTexturePart_Roof_Bottom			= 18,
	kTexturePart_Roof_Sides				= 19,
	kTexturePart_Roof_Gable_Walls		= 20,
	kTexturePart_Roof_Fascia			= 21,
	kTexturePart_Roof_Attic				= 22,
	kTexturePart_Roof_Soffit			= 23,
	kTexturePart_Roof_Dutch_Walls		= 24,
    kTexturePart_Roof_Dormer_Walls		= 25,	
	
	kTexturePart_CurtainWallFrame_Cap	= 26,
	kTexturePart_CurtainWallPanel_Face	= 27,

	kTexturePart_Maximum = 27	// keep this constant the same as the last entry in the enumeration
};

// Old, mainly for file translation purposes.  -DLD 3/10/2008
const TexturePartSDK	kAllTextureParts_Old = TexturePartSDK(-1);	// Any textured part (e.g. to delete texturing of all parts)
const TexturePartSDK	kPrimaryPart_Old = TexturePartSDK(0);	// All parts (for single-textured objects), or wall right, or roof top
const TexturePartSDK	kSecondaryPart_Old = TexturePartSDK(1);	// Wall left, or roof dormer
const TexturePartSDK	kTertiaryPart_Old = TexturePartSDK(2);	// Wall center

// Different kinds of texture space geometry
enum EParamSpaceKind
{
	kParamSpaceKind_Undefined	= -1,
	kParamSpaceKind_Plane		= 0,
	kParamSpaceKind_Sphere		= 1,
	kParamSpaceKind_Cylinder	= 2,
	kParamSpaceKind_Algorithmic = 3,	// Space that wraps around the object most
										// naturally.  Perimeter type space for extrudes
										// and sweeps, roof type for roof container nodes.
										// These space types are algorithmic in nature.
	kParamSpaceKind_Shader		= 4,
	kParamSpaceKind_Imported	= 5,
	kParamSpaceKind_Default		= 6,	// Default map type depending on obj type
	kParamSpaceKind_SurfaceUV	= 7		// may type for face texture
};


struct TextureMappingInfoSDK
{
	// Normalized 3D axis vectors and 3D offset from parameter space's 
	// default center (bottom center for cylinder, front bottom left for planar, etc.).
	// Transforms from object space to texture space.
	TransformMatrix fOriginOrient;

	bool			fInitialized;	// True if the the values have been set in a meaningful way
	
	// EParamSpaceKind: planar, spherical, cylindrical, or algorithmic
	EParamSpaceKind	fParamSpaceKind;

	// Texture bitmap modifiers
	WorldPt			f2DOffset;
	double			f2DScale;
	double			f2DRotation;	// radians

	// Spherical and cylindrical space only 
	// The feature length of the texture bitmap is true size on the sphere or
	// cylinder surface.  The radius value lets the user shrink or expand this surface.
	WorldCoord		fRadius;
	
	bool			fFlipTexture;		// This is to indicate whether texture gets fliped horizontally or vertically. 
										// with combination of rotation angle and offset, it achieves flipping -Shirley 3/24/03  
	bool			fRepeatH;			// Repeat texture along horizontal direction 
	bool			fRepeatV;			// Repeat texture along vertical direction
	
	bool			fUseWorldZ;
	bool			fAutoAlignPlanar;
	bool			fAutoAlignPlanarLongestEdge;

	TextureMappingInfoSDK()
		{
			// those defaults are very important
			// plug-ins rely on them being these values
			// and changing them might have unpredictable negative consequences to some plug-ins
			// Vlado [2013]
			fInitialized				= false;
			fOriginOrient				= IdentityMatrix();
			fParamSpaceKind				= kParamSpaceKind_Plane;
			f2DOffset.Set(0.0, 0.0);
			f2DScale					= 1.0;
			f2DRotation					= 0.0;
			fRadius						= 1000.0 * kWorldCoordsPerMM;
			fFlipTexture				= false;
			fRepeatH					= true;
			fRepeatV					= true;
			fUseWorldZ					= false;
			fAutoAlignPlanar			= false;
			fAutoAlignPlanarLongestEdge	= false;
		}

};

//////////////////////////////////////////////////////////////////////////////////////////
// Render Options 

const Sint32 kRenderWorksDataType		= 'rdrw';
const Sint32 kOpenGLDataType			= 'rdgl';
const Sint32 kHiddenLineDataType		= 'rdhl';



