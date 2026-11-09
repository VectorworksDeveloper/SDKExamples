
#pragma once

#ifndef _I_OPENPBR_MATERIAL_
#define _I_OPENPBR_MATERIAL_

namespace OpenPBR {

enum OpenPBRIndex
{
	// Base
	kBase = 0,
	kBaseWeight,
	kBaseColor,
	kBaseMetalness,
	kBaseRoughness,
	
	// Specular
	kSpecular,
	kSpecularWeight,
	kSpecularColor,
	kSpecularRoughness,
	kSpecularAnisotropy,
	kSpecularIor,
	
	// Transmission
	kTransmission,
	kTransmissionWeight,
	kTransmissionColor,
	kTransmissionDepth,
	kTransmissionScatter,
	kTransmissionScatterAniso,
	kTransmissionDispersion,
	kTransmissionAbbeNumber,
	
	// Subsurface
	kSubsurface,
	kSubsurfaceWeight,
	kSubsurfaceColor,
	kSubsurfaceRadius,
	kSubsurfaceRadiusScale,
	kSubsurfaceScatterAniso,
	
	// Coat
	kCoat,
	kCoatWeight,
	kCoatColor,
	kCoatRoughness,
	kCoatAnisotropy,
	kCoatIor,
	kCoatDarkening,
	
	// Fuzz
	kFuzz,
	kFuzzWeight,
	kFuzzColor,
	kFuzzRoughness,
	
	// Emission
	kEmission,
	kEmissionLuminance,
	kEmissionColor,
	
	// Thin-film
	kThinFilm,
	kThinFilmWeight,
	kThinFilmThickness,
	kThinFilmIor,
	
	// Geometry
	kGeometry,
	kGeometryOpacity,
	kGeometryThinWalled,
	kGeometryNormal,
	kGeometryTangent,
	kGeometryCoatNormal,
	kGeometryCoatTangent,
	kGeometryDisplacement,
	kGeometryBevelEdges,        // Redshift only: Round Corners node

	kOpenPBRIndex_NumElts
};

}

// Per-render resolved values derived at draw time (object fill color, etc.).
// NOT persisted to JSON and NOT compared in operator==.
struct ResolvedPbrData
{
	ColorVector fBaseTintColor;    // effective tint multiplier: (1,1,1) = no tint
	ColorVector fResolvedBaseColor; // resolved base color for "by parameter" mode
	ResolvedPbrData() {
		fBaseTintColor.Set(1.0f, 1.0f, 1.0f);
		fResolvedBaseColor.Set(0.8f, 0.8f, 0.8f); // matches OpenPbrData::fBaseColor default
	}
};

struct OpenPbrData
{
	// Base
	float       fBaseWeight;              	// base_weight
	ColorVector fBaseColor;					// base_color
	bool        fBaseColorUseObjectFill;	// true = use object fill color at render time
	float       fBaseMetalness;           	// base_metalness
	float       fBaseRoughness;           	// base_diffuse_roughness
	
	// Specular
	float       fSpecularWeight;          // specular_weight
	ColorVector fSpecularColor;           // specular_color
	float       fSpecularRoughness;       // specular_roughness
	float       fSpecularAnisotropy;      // specular_roughness_anisotropy
	float       fSpecularIor;             // specular_ior
	
	// Transmission
	float       fTransmissionWeight;      // transmission_weight
	ColorVector fTransmissionColor;       // transmission_color
	float       fTransmissionDepth;       // transmission_depth
	ColorVector fTransmissionScatter;     // transmission_scatter
	float       fTransmissionScatterAniso;// transmission_scatter_anisotropy
	float       fTransmissionDispersion;  // transmission_dispersion_scale
	float       fTransmissionAbbeNumber;  // transmission_dispersion_abbe_number
	
	// Subsurface
	float       fSubsurfaceWeight;        // subsurface_weight
	ColorVector fSubsurfaceColor;         // subsurface_color
	float       fSubsurfaceRadius;        // subsurface_radius
	ColorVector fSubsurfaceRadiusScale;   // subsurface_radius_scale
	float       fSubsurfaceScatterAniso;  // subsurface_scatter_anisotropy
	
	// Coat
	float       fCoatWeight;              // coat_weight
	ColorVector fCoatColor;               // coat_color
	float       fCoatRoughness;           // coat_roughness
	float       fCoatAnisotropy;          // coat_roughness_anisotropy
	float       fCoatIor;                 // coat_ior
	float       fCoatDarkening;           // coat_darkening
	
	// Fuzz
	float       fFuzzWeight;              // fuzz_weight
	ColorVector fFuzzColor;               // fuzz_color
	float       fFuzzRoughness;           // fuzz_roughness
	
	// Emission
	float       fEmissionLuminance;       // emission_luminance
	ColorVector fEmissionColor;           // emission_color
	
	// Thin-film
	float       fThinFilmWeight;          // thin_film_weight
	float       fThinFilmThickness;       // thin_film_thickness
	float       fThinFilmIor;             // thin_film_ior
	
	// Geometry
	float       fGeometryOpacity;         // geometry_opacity
	bool        fGeometryThinWalled;      // geometry_thin_walled
	ColorVector fGeometryNormal;          // geometry_normal
	ColorVector fGeometryTangent;         // geometry_tangent
	ColorVector fGeometryCoatNormal;      // geometry_coat_normal
	ColorVector fGeometryCoatTangent;     // geometry_coat_tangent
	float       fGeometryDisplacementScale;	// geometry_displacement_scale (Redshift only)
	WorldCoord	fGeometryDisplacementMax;         // geometry_displacement_max in WorldCoords (0 = unset; dialog defaults to 2 inches)
	WorldCoord  fGeometryBevelRadius;        // geometry_bevel_radius (Redshift only)
	Sint32      fGeometryBevelSubdivisions;  // geometry_bevel_subdivisions (Redshift only)
	// Height Scale of the Redshift Bump Map node used for height-map-mode geometry_normal
	// images (see WireTexToBumpToOpenPBRNode). No dialog control yet -- wired through now
	// (data model, script API, node-graph) so a UI can bind to it later. Redshift only.
	float       fGeometryNormalBumpHeightScale;

	ResolvedPbrData fResolved;  // per-render resolved values; not persisted, not compared

	std::vector<RefNumber> fImageRefNumberVector;

	OpenPbrData() {
		// Base
		fBaseWeight = 1.0;              // base_weight
		fBaseColor.Set(0.8f, 0.8f, 0.8f);	// base_color
		fBaseColorUseObjectFill = false; // base_color_use_object_fill
		fBaseMetalness = 0.0f;           // base_metalness
		fBaseRoughness = 0.0f;           // base_diffuse_roughness
		
		// Specular
		fSpecularWeight = 1.0f;          // specular_weight
		fSpecularColor.Set(1.0f, 1.0f, 1.0f);           // specular_color
		fSpecularRoughness = 0.3f;       // specular_roughness
		fSpecularAnisotropy = 0.0f;      // specular_roughness_anisotropy
		fSpecularIor = 1.5f;             // specular_ior
		
		// Transmission
		fTransmissionWeight = 0.0f;      // transmission_weight
		fTransmissionColor.Set(1.0f, 1.0f, 1.0f);       // transmission_color
		fTransmissionDepth = 0.0f;       // transmission_depth
		fTransmissionScatter.Set(0.0f, 0.0f, 0.0f);     // transmission_scatter
		fTransmissionScatterAniso = 0.0f;// transmission_scatter_anisotropy
		fTransmissionDispersion = 0.0f;  // transmission_dispersion_scale
		fTransmissionAbbeNumber = 20.0f;  // transmission_dispersion_abbe_number
		
		// Subsurface
		fSubsurfaceWeight = 0.0f;        					// subsurface_weight
		fSubsurfaceColor.Set(0.8f, 0.8f, 0.8f);         	// subsurface_color
		fSubsurfaceRadius = 1.0f;        					// subsurface_radius
		fSubsurfaceRadiusScale.Set(1.0f, 0.5f, 0.25f);   	// subsurface_radius_scale
		fSubsurfaceScatterAniso = 0.0f;  					// subsurface_scatter_anisotropy
		
		// Coat
		fCoatWeight = 0.0f;              // coat_weight
		fCoatColor.Set(1.0f, 1.0f, 1.0f);               // coat_color
		fCoatRoughness = 0.0f;           // coat_roughness
		fCoatAnisotropy = 0.0f;          // coat_roughness_anisotropy
		fCoatIor = 1.6f;                 // coat_ior
		fCoatDarkening = 1.0f;           // coat_darkening
		
		// Fuzz
		fFuzzWeight = 0.0f;              // fuzz_weight
		fFuzzColor.Set(1.0f, 1.0f, 1.0f);               // fuzz_color
		fFuzzRoughness = 0.5f;           // fuzz_roughness
		
		// Emission
		fEmissionLuminance = 0.0f;       // emission_luminance
		fEmissionColor.Set(1.0f, 1.0f, 1.0f);           // emission_color
		
		// Thin-film
		fThinFilmWeight = 0.0f;          // thin_film_weight
		fThinFilmThickness = 0.5f;       // thin_film_thickness
		fThinFilmIor = 1.4f;             // thin_film_ior
		
		// Geometry
		fGeometryOpacity = 1.0f;         // geometry_opacity
		fGeometryThinWalled = false;      // geometry_thin_walled
		fGeometryNormal.Set(0.0f, 0.0f, 0.0f);          // geometry_normal
		fGeometryTangent.Set(0.0f, 0.0f, 0.0f);         // geometry_tangent
		fGeometryCoatNormal.Set(0.0f, 0.0f, 0.0f);      // geometry_coat_normal
		fGeometryCoatTangent.Set(0.0f, 0.0f, 0.0f);     // geometry_coat_tangent
		fGeometryDisplacementScale = 10.0f;			// geometry_displacement_scale
		fGeometryDisplacementMax   = 2.0 * kWorldCoordsPerInch;	// geometry_displacement_max
		fGeometryBevelRadius       = 0.0;
		fGeometryBevelSubdivisions = 4;
		fGeometryNormalBumpHeightScale = 1.0f;			// geometry_normal_bump_height_scale (Redshift node default: unscaled)

		fImageRefNumberVector.assign(OpenPBR::kOpenPBRIndex_NumElts, 0);
	};
	
	virtual ~OpenPbrData() { }
};

// Pixel-perfect comparison for two image slots in fImageRefNumberVector.
// Both zero => equal. One zero => not equal. Both non-zero => decode and compare bytes.
inline bool OpenPbrImagesEqual(RefNumber refA, RefNumber refB)
{
	if (refA == 0 && refB == 0) return true;
	if (refA == 0 || refB == 0) return false;

	MCObjectHandle hA = gSDK->InternalIndexToHandle(refA);
	MCObjectHandle hB = gSDK->InternalIndexToHandle(refB);
	if (!hA || !hB) return false;

	using namespace VectorWorks::Imaging;

	ICompressedImagePtr imgA(IID_CompressedImage);
	ICompressedImagePtr imgB(IID_CompressedImage);
	if (!imgA || !imgB) return false;
	if (imgA->CreateFromObject(hA) != kVCOMError_NoError) return false;
	if (imgB->CreateFromObject(hB) != kVCOMError_NoError) return false;

	IRawImagePtr rawA(IID_RawImage);
	IRawImagePtr rawB(IID_RawImage);
	if (!rawA || !rawB) return false;
	if (rawA->CreateFromCompressedImage(imgA) != kVCOMError_NoError) return false;
	if (rawB->CreateFromCompressedImage(imgB) != kVCOMError_NoError) return false;

	RawImageDesc descA = {}, descB = {};
	if (rawA->GetImageDesc(descA) != kVCOMError_NoError) return false;
	if (rawB->GetImageDesc(descB) != kVCOMError_NoError) return false;

	if (descA.width != descB.width || descA.height != descB.height) return false;
	if (descA.bitsPerPixel != descB.bitsPerPixel) return false;
	if (!descA.bufferPtr || !descB.bufferPtr) return false;

	Uint32 Bpp = descA.bitsPerPixel / 8;
	if (Bpp == 0) return false;

	const unsigned char* pA = static_cast<const unsigned char*>(descA.bufferPtr);
	const unsigned char* pB = static_cast<const unsigned char*>(descB.bufferPtr);
	for (Uint32 y = 0; y < descA.height; ++y)
	{
		const unsigned char* rowA = pA + y * descA.bytesPerRow;
		const unsigned char* rowB = pB + y * descB.bytesPerRow;
		for (Uint32 x = 0; x < descA.width * Bpp; ++x)
			if (rowA[x] != rowB[x]) return false;
	}
	return true;
}

// Field-wise equality for OpenPbrData (floats use a small epsilon; bools are exact).
// Image slots: both 0 => equal, one 0 => not equal, both non-zero => pixel-perfect compare.
inline bool operator==(const OpenPbrData& a, const OpenPbrData& b)
{
	const float kEps = 1e-4f;
	auto fEq = [kEps](float x, float y) { return (x - y < kEps) && (y - x < kEps); };
	auto cvEq = [&fEq](const ColorVector& x, const ColorVector& y) {
		return fEq((float)x.x, (float)y.x) && fEq((float)x.y, (float)y.y) && fEq((float)x.z, (float)y.z);
	};
	return fEq(a.fBaseWeight,              b.fBaseWeight)
		&& cvEq(a.fBaseColor,              b.fBaseColor)
		&& (a.fBaseColorUseObjectFill   == b.fBaseColorUseObjectFill)
		&& fEq(a.fBaseMetalness,           b.fBaseMetalness)
		&& fEq(a.fBaseRoughness,           b.fBaseRoughness)
		&& fEq(a.fSpecularWeight,          b.fSpecularWeight)
		&& cvEq(a.fSpecularColor,          b.fSpecularColor)
		&& fEq(a.fSpecularRoughness,       b.fSpecularRoughness)
		&& fEq(a.fSpecularAnisotropy,      b.fSpecularAnisotropy)
		&& fEq(a.fSpecularIor,             b.fSpecularIor)
		&& fEq(a.fTransmissionWeight,      b.fTransmissionWeight)
		&& cvEq(a.fTransmissionColor,      b.fTransmissionColor)
		&& fEq(a.fTransmissionDepth,       b.fTransmissionDepth)
		&& cvEq(a.fTransmissionScatter,    b.fTransmissionScatter)
		&& fEq(a.fTransmissionScatterAniso,b.fTransmissionScatterAniso)
		&& fEq(a.fTransmissionDispersion,  b.fTransmissionDispersion)
		&& fEq(a.fTransmissionAbbeNumber,  b.fTransmissionAbbeNumber)
		&& fEq(a.fSubsurfaceWeight,        b.fSubsurfaceWeight)
		&& cvEq(a.fSubsurfaceColor,        b.fSubsurfaceColor)
		&& fEq(a.fSubsurfaceRadius,        b.fSubsurfaceRadius)
		&& cvEq(a.fSubsurfaceRadiusScale,  b.fSubsurfaceRadiusScale)
		&& fEq(a.fSubsurfaceScatterAniso,  b.fSubsurfaceScatterAniso)
		&& fEq(a.fCoatWeight,              b.fCoatWeight)
		&& cvEq(a.fCoatColor,              b.fCoatColor)
		&& fEq(a.fCoatRoughness,           b.fCoatRoughness)
		&& fEq(a.fCoatAnisotropy,          b.fCoatAnisotropy)
		&& fEq(a.fCoatIor,                 b.fCoatIor)
		&& fEq(a.fCoatDarkening,           b.fCoatDarkening)
		&& fEq(a.fFuzzWeight,              b.fFuzzWeight)
		&& cvEq(a.fFuzzColor,              b.fFuzzColor)
		&& fEq(a.fFuzzRoughness,           b.fFuzzRoughness)
		&& fEq(a.fEmissionLuminance,       b.fEmissionLuminance)
		&& cvEq(a.fEmissionColor,          b.fEmissionColor)
		&& fEq(a.fThinFilmWeight,          b.fThinFilmWeight)
		&& fEq(a.fThinFilmThickness,       b.fThinFilmThickness)
		&& fEq(a.fThinFilmIor,             b.fThinFilmIor)
		&& fEq(a.fGeometryOpacity,         b.fGeometryOpacity)
		&& (a.fGeometryThinWalled       == b.fGeometryThinWalled)
		&& cvEq(a.fGeometryNormal,         b.fGeometryNormal)
		&& cvEq(a.fGeometryTangent,        b.fGeometryTangent)
		&& cvEq(a.fGeometryCoatNormal,     b.fGeometryCoatNormal)
		&& cvEq(a.fGeometryCoatTangent,    b.fGeometryCoatTangent)
		&& fEq(a.fGeometryDisplacementScale,       b.fGeometryDisplacementScale)
		&& fEq((float)a.fGeometryDisplacementMax,  (float)b.fGeometryDisplacementMax)
		&& fEq((float)a.fGeometryBevelRadius,      (float)b.fGeometryBevelRadius)
		&& (a.fGeometryBevelSubdivisions        == b.fGeometryBevelSubdivisions)
		&& fEq(a.fGeometryNormalBumpHeightScale,  b.fGeometryNormalBumpHeightScale)
		&& [&]() -> bool {
			if (a.fImageRefNumberVector.size() != b.fImageRefNumberVector.size()) return false;
			for (size_t i = 0; i < a.fImageRefNumberVector.size(); ++i)
				if (!OpenPbrImagesEqual(a.fImageRefNumberVector[i], b.fImageRefNumberVector[i]))
					return false;
			return true;
		}();
}

inline bool operator!=(const OpenPbrData& a, const OpenPbrData& b)
{
	return !(a == b);
}

// Returns true if the given PBR image slot is in bounds and has a non-zero image ref.
// outRef receives the RefNumber when the function returns true.
inline bool HasPbrImage(const OpenPbrData& data, OpenPBR::OpenPBRIndex index, RefNumber& outRef)
{
	if ((int)index >= (int)data.fImageRefNumberVector.size()) return false;
	outRef = data.fImageRefNumberVector[index];
	return outRef != 0;
}

inline bool HasPbrImage(const OpenPbrData& data, OpenPBR::OpenPBRIndex index)
{
	RefNumber ref = 0;
	return HasPbrImage(data, index, ref);
}

// Specifies which fields of OpenPbrData to resync onto a material in ModifyPbrMaterial.
// Primitive (scalar/color) changes are applied in-place via a fast graph port-value update.
// If a flagged field has a non-zero image ref, the full material graph is rebuilt instead.
struct PbrDataModFlags
{
	// Base
	bool modBaseWeight          : 1;
	bool modBaseColor           : 1;
	bool modBaseMetalness       : 1;
	bool modBaseRoughness       : 1;
	// Specular
	bool modSpecularWeight      : 1;
	bool modSpecularColor       : 1;
	bool modSpecularRoughness   : 1;
	bool modSpecularAnisotropy  : 1;
	bool modSpecularIor         : 1;
	// Transmission
	bool modTransmissionWeight      : 1;
	bool modTransmissionColor       : 1;
	bool modTransmissionDepth       : 1;
	bool modTransmissionScatter     : 1;
	bool modTransmissionScatterAniso: 1;
	bool modTransmissionDispersion  : 1;
	bool modTransmissionAbbeNumber  : 1;
	// Subsurface
	bool modSubsurfaceWeight        : 1;
	bool modSubsurfaceColor         : 1;
	bool modSubsurfaceRadius        : 1;
	bool modSubsurfaceRadiusScale   : 1;
	bool modSubsurfaceScatterAniso  : 1;
	// Coat
	bool modCoatWeight          : 1;
	bool modCoatColor           : 1;
	bool modCoatRoughness       : 1;
	bool modCoatAnisotropy      : 1;
	bool modCoatIor             : 1;
	bool modCoatDarkening       : 1;
	// Fuzz
	bool modFuzzWeight          : 1;
	bool modFuzzColor           : 1;
	bool modFuzzRoughness       : 1;
	// Emission
	bool modEmissionLuminance   : 1;
	bool modEmissionColor       : 1;
	// Thin-film
	bool modThinFilmWeight      : 1;
	bool modThinFilmThickness   : 1;
	bool modThinFilmIor         : 1;
	// Geometry
	bool modGeometryOpacity      : 1;
	bool modGeometryThinWalled   : 1;
	bool modGeometryNormal       : 1;
	bool modGeometryTangent      : 1;
	bool modGeometryCoatNormal   : 1;
	bool modGeometryCoatTangent  : 1;
	bool modGeometryDisplacement : 1;
	bool modGeometryBevelEdges   : 1;
	bool modGeometryNormalBumpHeightScale : 1;

	PbrDataModFlags() { memset(this, 0, sizeof(*this)); }
};

// Read base-color tint mode and chosen color from an ImageDefNode's per-image tagged data.
// outMode: 0=no filter, 1=obj fill, 2=chosen color.
// outColor: the stored chosen color (meaningful only when outMode==2).
// Returns false if the node has no tint tagged data; outMode and outColor are then left unchanged.
inline bool GetPbrBaseTintInfo(MCObjectHandle baseColorNode, Uint32& outMode, ColorVector& outColor)
{
	constexpr Uint32 kTag      = 'PbIt'; // kPBRTextureImageTag
	constexpr Sint32 kModeIdx  = 1;      // kPbrMaterial_ImageUint32ArrayTag
	constexpr Sint32 kColorIdx = 3;      // kPbrMaterial_ImageFloatArrayTag

	if (!baseColorNode) return false;
	Sint32 n = 0;
	if (!gSDK->TaggedDataGetNumElements(baseColorNode, kTag, kTaggedDataUint32ArrayTypeID, kModeIdx, &n) || n == 0)
		return false;

	Uint32* pMode = nullptr;
	gSDK->TaggedDataGet(baseColorNode, kTag, kTaggedDataUint32ArrayTypeID, kModeIdx, 0, &pMode);
	if (!pMode) return false;
	outMode = *pMode;

	if (outMode == 2)
	{
		Sint32 nc = 0;
		if (gSDK->TaggedDataGetNumElements(baseColorNode, kTag, kTaggedDataDoubleArrayTypeID, kColorIdx, &nc) && nc >= 3)
		{
			const double* pColor = nullptr;
			gSDK->TaggedDataGet(baseColorNode, kTag, kTaggedDataDoubleArrayTypeID, kColorIdx, 0, &pColor);
			if (pColor)
			{
				outColor.x = (float)pColor[0];
				outColor.y = (float)pColor[1];
				outColor.z = (float)pColor[2];
			}
		}
	}
	return true;
}

// Convenience: resolve the base_color ImageDefNode from a PBR texture's image-ref table,
// then delegate to GetPbrBaseTintInfo.
inline bool GetPbrBaseTintInfoFromTexture(MCObjectHandle texture, Uint32& outMode, ColorVector& outColor)
{
	constexpr Uint32 kImgRefTag = 'PRef'; // kPBRTextureImgRefTag
	int n = 0;
	if (!gSDK->TaggedDataGetNumElements(texture, kImgRefTag, kTaggedDataObjectRefArrayTypeID, 0, &n)
		|| n <= (int)OpenPBR::kBaseColor)
		return false;

	RefNumber* pRefs = nullptr;
	gSDK->TaggedDataGet(texture, kImgRefTag, kTaggedDataObjectRefArrayTypeID, 0, 0, &pRefs);
	if (!pRefs) return false;

	MCObjectHandle baseColorNode = gSDK->InternalIndexToHandle(pRefs[OpenPBR::kBaseColor]);
	return GetPbrBaseTintInfo(baseColorNode, outMode, outColor);
}


static const VWIID IID_OpenPbrTexture = { 0xe25099ed, 0x34a6, 0x4a91, { 0x91, 0xe0, 0xa, 0x8f, 0xe6, 0x99, 0x59, 0xf1 } };


class IOpenPbrTextureData : public IVWSingletonUnknown
{
public:
	virtual bool VCOM_CALLTYPE RetrievePbrData(MCObjectHandle parent, OpenPbrData& data) = 0;
	virtual bool VCOM_CALLTYPE SavePbrData(OpenPbrData data, MCObjectHandle parent) = 0;
	virtual bool VCOM_CALLTYPE IsOpenPbrMaterial(MCObjectHandle parent) = 0;
	virtual bool VCOM_CALLTYPE ConvertOpenPBRToLegacy(MCObjectHandle parent, const OpenPbrData& pbrTextureData) = 0;
	// silent=true skips the "Convert the texture to PBR?" confirmation alert -- used by the
	// scriptable VS API (PbrConvertLegacyToOpenPBR) so automation never blocks on an unscripted dialog.
	virtual bool VCOM_CALLTYPE ConvertLegacyToOpenPBR(MCObjectHandle parent, bool silent = false) = 0;
	virtual bool VCOM_CALLTYPE GetChannelName(Sint32 index, TXString& channelName) = 0;
};
typedef VCOMPtr<IOpenPbrTextureData> IOpenPbrTextureDataPtr;

#endif	//_I_OPENPBR_MATERIAL_
