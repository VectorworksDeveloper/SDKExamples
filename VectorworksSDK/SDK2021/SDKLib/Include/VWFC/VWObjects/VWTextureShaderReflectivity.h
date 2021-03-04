//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "VWTextureShaderBase.h"

namespace VWFC
{
	namespace VWObjects
	{
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityImage : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityImage(VWTextureObj& textureObj);
							VWTextureShaderReflectivityImage(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityImage(const VWTextureShaderReflectivityImage& src);
			virtual			~VWTextureShaderReflectivityImage();

			VWTextureShaderReflectivityImage&	operator=(const VWTextureShaderReflectivityImage& src);

		public:
			MCObjectHandle		GetImage() const;
			void				SetImage(MCObjectHandle& hBitmapObj) const;
			double				GetReflection() const;
			void				SetReflection(double value);
			double				GetBlurriness() const;
			void				SetBlurriness(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityImage& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityImage& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

				// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityMirror : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityMirror(VWTextureObj& textureObj);
							VWTextureShaderReflectivityMirror(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityMirror(const VWTextureShaderReflectivityMirror& src);
			virtual			~VWTextureShaderReflectivityMirror();

			VWTextureShaderReflectivityMirror&	operator=(const VWTextureShaderReflectivityMirror& src);

		public:
			Tools::CRGBColor	GetColor() const;
			void				SetColor(const Tools::CRGBColor& value);
			double				GetReflection() const;
			void				SetReflection(double value);
			double				GetBlurriness() const;
			void				SetBlurriness(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityMirror& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityMirror& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
				
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityFresnel : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityFresnel(VWTextureObj& textureObj);
							VWTextureShaderReflectivityFresnel(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityFresnel(const VWTextureShaderReflectivityFresnel& src);
			virtual			~VWTextureShaderReflectivityFresnel();

			VWTextureShaderReflectivityFresnel&	operator=(const VWTextureShaderReflectivityFresnel& src);

		public:
			Tools::CRGBColor	GetEdgeColor() const;
			void				SetEdgeColor(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetCenterColor() const;
			void				SetCenterColor(const Tools::CRGBColor& value);
			double				GetBlurriness() const;
			void				SetBlurriness(double value);
			
		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityFresnel& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityFresnel& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
		
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityNoise : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityNoise(VWTextureObj& textureObj);
							VWTextureShaderReflectivityNoise(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityNoise(const VWTextureShaderReflectivityNoise& src);
			virtual			~VWTextureShaderReflectivityNoise();

			VWTextureShaderReflectivityNoise&	operator=(const VWTextureShaderReflectivityNoise& src);

		public:
			ShaderNoiseType		GetPattern() const;
			void				SetPattern(ShaderNoiseType value);
			Tools::CRGBColor	GetColor1() const;
			void				SetColor1(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetColor2() const;
			void				SetColor2(const Tools::CRGBColor& value);
			bool				GetNoiseSolid() const;
			void				SetNoiseSolid(bool value);
			double				GetGlobalScale() const;
			void				SetGlobalScale(double value);
			double				GetRelativeUScale() const;
			void				SetRelativeUScale(double value);
			double				GetRelativeVScale() const;
			void				SetRelativeVScale(double value);
			double				GetRelativeWScale() const;
			void				SetRelativeWScale(double value);
			double				GetLowClip() const;
			void				SetLowClip(double value);
			double				GetHighClip() const;
			void				SetHighClip(double value);
			double				GetDetail() const;					
			void				SetDetail(double value);
			double				GetCycles() const;
			void				SetCycles(double value);
			double				GetBlurriness() const;
			void				SetBlurriness(double value);
			
		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityNoise& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityNoise& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
		
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityTiles : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityTiles(VWTextureObj& textureObj);
							VWTextureShaderReflectivityTiles(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityTiles(const VWTextureShaderReflectivityTiles& src);
			virtual			~VWTextureShaderReflectivityTiles();

			VWTextureShaderReflectivityTiles&	operator=(const VWTextureShaderReflectivityTiles& src);

		public:
			ShaderTilesType		GetPattern() const;
			void				SetPattern(ShaderTilesType value);
			Tools::CRGBColor	GetGroutColor() const;		
			void				SetGroutColor(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetColor1() const;		
			void				SetColor1(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetColor2() const;		
			void				SetColor2(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetColor3() const;		
			void				SetColor3(const Tools::CRGBColor& value);
			bool				GetRandomizeColor() const;
			void				SetRandomizeColor(bool value);
			double				GetGroutWidth() const;
			void				SetGroutWidth(double value);
			double				GetBevelWidth() const;
			void				SetBevelWidth(double value);
			bool				GetBevel() const;
			void				SetBevel(bool value);
			bool				GetHorizontalOrientation() const;
			void				SetHorizontalOrientation(bool value);
			double				GetGlobalScale() const;
			void				SetGlobalScale(double value);
			double				GetRelativeScaleU() const;
			void				SetRelativeScaleU(double value);
			double				GetRelativeScaleV() const;
			void				SetRelativeScaleV(double value);
			double				GetBlurriness() const;
			void				SetBlurriness(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityTiles& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityTiles& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
		
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityPlastic : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityPlastic(VWTextureObj& textureObj);
							VWTextureShaderReflectivityPlastic(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityPlastic(const VWTextureShaderReflectivityPlastic& src);
			virtual			~VWTextureShaderReflectivityPlastic();

			VWTextureShaderReflectivityPlastic&	operator=(const VWTextureShaderReflectivityPlastic& src);

		public:
			Tools::CRGBColor	GetColor() const;		
			void				SetColor(const Tools::CRGBColor& value);
			double				GetBrightness() const;
			void				SetBrightness(double value);
			double				GetRoughness() const;
			void				SetRoughness(double value);
			double				GetReflection() const;
			void				SetReflection(double value);
			double				GetBlurriness() const;
			void				SetBlurriness(double value);
			
		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityPlastic& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityPlastic& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
		
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityBricks : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityBricks(VWTextureObj& textureObj);
							VWTextureShaderReflectivityBricks(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityBricks(const VWTextureShaderReflectivityBricks& src);
			virtual			~VWTextureShaderReflectivityBricks();

			VWTextureShaderReflectivityBricks&	operator=(const VWTextureShaderReflectivityBricks& src);

		public:
			double				GetScale() const;
			void				SetScale(double value);
			double				GetBrickWidth() const;
			void				SetBrickWidth(double value);
			double				GetBrickHeight() const;
			void				SetBrickHeight(double value);
			double				GetShift() const;
			void				SetShift(double value);
			Sint32				GetHalfBrickRow() const;
			void				SetHalfBrickRow(Sint32 value);
			double				GetHalfBrickShift() const;
			void				SetHalfBrickShift(double value);
			double				GetGapSize() const;
			void				SetGapSize(double value);
			double				GetGapNoise() const;
			void				SetGapNoise(double value);
			Tools::CRGBColor	GetBrickColor1() const;
			void				SetBrickColor1(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetBrickColor2() const;
			void				SetBrickColor2(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetAltColor1() const;
			void				SetAltColor1(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetAltColor2() const;
			void				SetAltColor2(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetGapColor1() const;
			void				SetGapColor1(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetGapColor2() const;
			void				SetGapColor2(const Tools::CRGBColor& value);
			double				GetContrast() const;
			void				SetContrast(double value);
			Sint32				GetAltColorRow() const;
			void				SetAltColorRow(Sint32 value);
			Sint32				GetAltColorColumn() const;
			void				SetAltColorColumn(Sint32 value);
			double				GetBlurriness() const;
			void				SetBlurriness(double value);
			double				GetBricksImageBlend() const;
			void				SetBricksImageBlend(double value);
			double				GetGapImageBlend() const;
			void				SetGapImageBlend(double value);
			double				GetAltBricksImageBlend() const;
			void				SetAltBricksImageBlend(double value);
			
		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityBricks& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityBricks& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
		
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityPavement : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityPavement(VWTextureObj& textureObj);
							VWTextureShaderReflectivityPavement(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityPavement(const VWTextureShaderReflectivityPavement& src);
			virtual			~VWTextureShaderReflectivityPavement();

			VWTextureShaderReflectivityPavement&	operator=(const VWTextureShaderReflectivityPavement& src);

		public:
			double				GetScale() const;
			void				SetScale(double value);
			double				GetGapWidth() const;
			void				SetGapWidth(double value);
			double				GetSoftness() const;
			void				SetSoftness(double value);
			Tools::CRGBColor	GetStoneColor1() const;
			void				SetStoneColor1(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetStoneColor2() const;
			void				SetStoneColor2(const Tools::CRGBColor& value);
			double				GetCoarseMarbling() const;
			void				SetCoarseMarbling(double value);
			double				GetFineMarbling() const;
			void				SetFineMarbling(double value);
			Tools::CRGBColor	GetGapColor1() const;
			void				SetGapColor1(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetGapColor2() const;
			void				SetGapColor2(const Tools::CRGBColor& value);
			double				GetGapGrain() const;
			void				SetGapGrain(double value);
			Tools::CRGBColor	GetSmudgeColor1() const;
			void				SetSmudgeColor1(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetSmudgeColor2() const;
			void				SetSmudgeColor2(const Tools::CRGBColor& value);
			double				GetSmudgeAmount() const;
			void				SetSmudgeAmount(double value);
			double				GetSmudgeSize() const;
			void				SetSmudgeSize(double value);
			double				GetBlurriness() const;
			void				SetBlurriness(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityPavement& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityPavement& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
		
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityGlow : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityGlow(VWTextureObj& textureObj);
							VWTextureShaderReflectivityGlow(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityGlow(const VWTextureShaderReflectivityGlow& src);
			virtual			~VWTextureShaderReflectivityGlow();

			VWTextureShaderReflectivityGlow&	operator=(const VWTextureShaderReflectivityGlow& src);

		public:
			double			GetGlowBrightness() const;
			void			SetGlowBrightness(double value);
			bool			GetEmitLight() const;
			void			SetEmitLight(bool value);
			bool			GetAddMatteReflectivity() const;
			void			SetAddMatteReflectivity(bool value);
			double			GetReflection() const;
			void			SetReflection(double value);
			double			GetBlurriness() const;
			void			SetBlurriness(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityGlow& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityGlow& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
		
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityBacklit : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityBacklit(VWTextureObj& textureObj);
							VWTextureShaderReflectivityBacklit(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityBacklit(const VWTextureShaderReflectivityBacklit& src);
			virtual			~VWTextureShaderReflectivityBacklit();

			VWTextureShaderReflectivityBacklit&	operator=(const VWTextureShaderReflectivityBacklit& src);

		public:
			Tools::CRGBColor		GetColor() const;
			void					SetColor(const Tools::CRGBColor& value);
			double					GetBrightness() const;
			void					SetBrightness(double value);
			double					GetReflection() const;
			void					SetReflection(double value);
			double					GetBlurriness() const;
			void					SetBlurriness(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityBacklit& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityBacklit& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
		
		// --------------------------------------------------------------------------------
		class VWTextureShaderReflectivityAnisotropic : public VWTextureShaderBase
		{
		public:
							VWTextureShaderReflectivityAnisotropic(VWTextureObj& textureObj);
							VWTextureShaderReflectivityAnisotropic(MCObjectHandle hShaderRecord);
							VWTextureShaderReflectivityAnisotropic(const VWTextureShaderReflectivityAnisotropic& src);
			virtual			~VWTextureShaderReflectivityAnisotropic();

			VWTextureShaderReflectivityAnisotropic&	operator=(const VWTextureShaderReflectivityAnisotropic& src);

		public:
			enum EPattern
			{
				ePattern_NoAnisotropy = 1,
				ePattern_Brushed,
				ePattern_Turned
			};

			Tools::CRGBColor		GetColor() const;
			void					SetColor(const Tools::CRGBColor& value);
			EPattern				GetPattern() const;
			void					SetPattern(EPattern value);
			double					GetReflection() const;
			void					SetReflection(double value);
			double					GetBlurriness() const;
			void					SetBlurriness(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderReflectivityAnisotropic& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderReflectivityAnisotropic& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
	}
}
