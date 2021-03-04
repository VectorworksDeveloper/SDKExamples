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
		class VWTextureShaderTransparencyPlain : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyPlain(VWTextureObj& textureObj);
							VWTextureShaderTransparencyPlain(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyPlain(const VWTextureShaderTransparencyPlain& src);
			virtual			~VWTextureShaderTransparencyPlain();

			VWTextureShaderTransparencyPlain&	operator=(const VWTextureShaderTransparencyPlain& src);

		public:
			double				GetOpacity() const;
			void				SetOpacity(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyPlain& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyPlain& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// --------------------------------------------------------------------------------
		class VWTextureShaderTransparencyColor : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyColor(VWTextureObj& textureObj);
							VWTextureShaderTransparencyColor(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyColor(const VWTextureShaderTransparencyColor& src);
			virtual			~VWTextureShaderTransparencyColor();

			VWTextureShaderTransparencyColor&	operator=(const VWTextureShaderTransparencyColor& src);

		public:
			Tools::CRGBColor	GetColor() const;
			void				SetColor(const Tools::CRGBColor& value);

			double				GetBrightness() const;
			void				SetBrightness(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyColor& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyColor& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderTransparencyImage : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyImage(VWTextureObj& textureObj);
							VWTextureShaderTransparencyImage(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyImage(const VWTextureShaderTransparencyImage& src);
			virtual			~VWTextureShaderTransparencyImage();

			VWTextureShaderTransparencyImage&	operator=(const VWTextureShaderTransparencyImage& src);

		public:
			MCObjectHandle		GetImage() const;
			void				SetImage(MCObjectHandle& hBitmapObj) const;
			double				GetRefraction() const;
			void				SetRefraction(double value);
			double				GetTransparencyBlurriness() const;
			void				SetTransparencyBlurriness(double value);
			Tools::CRGBColor	GetAbsorptionColor() const;
			void				SetAbsorptionColor(const Tools::CRGBColor& value);
			double				GetAbsorptionDistance() const;
			void				SetAbsorptionDistance(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyImage& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyImage& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderTransparencyGlass : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyGlass(VWTextureObj& textureObj);
							VWTextureShaderTransparencyGlass(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyGlass(const VWTextureShaderTransparencyGlass& src);
			virtual			~VWTextureShaderTransparencyGlass();

			VWTextureShaderTransparencyGlass&	operator=(const VWTextureShaderTransparencyGlass& src);

		public:
			double				GetTransmission() const;
			void				SetTransmission(double value);
			double				GetRefraction() const;
			void				SetRefraction(double value);
			Tools::CRGBColor	GetColor() const;
			void				SetColor(const Tools::CRGBColor& value);
			double				GetTransparencyBlurriness() const;
			void				SetTransparencyBlurriness(double value);
			Tools::CRGBColor	GetAbsorptionColor() const;
			void				SetAbsorptionColor(const Tools::CRGBColor& value);
			double				GetAbsorptionDistance() const;
			void				SetAbsorptionDistance(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyGlass& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyGlass& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderTransparencyNoise : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyNoise(VWTextureObj& textureObj);
							VWTextureShaderTransparencyNoise(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyNoise(const VWTextureShaderTransparencyNoise& src);
			virtual			~VWTextureShaderTransparencyNoise();

			VWTextureShaderTransparencyNoise&	operator=(const VWTextureShaderTransparencyNoise& src);

		public:
			ShaderNoiseType			GetPattern() const;
			void					SetPattern(ShaderNoiseType value);
			Tools::CRGBColor		GetColor1() const;
			void					SetColor1(const Tools::CRGBColor& value);
			Tools::CRGBColor		GetColor2() const;
			void					SetColor2(const Tools::CRGBColor& value);
			bool					GetNoiseSolid() const;
			void					SetNoiseSolid(bool value);
			double					GetGlobalScale() const;
			void					SetGlobalScale(double value);
			double					GetRelativeUScale() const;
			void					SetRelativeUScale(double value);
			double					GetRelativeVScale() const;
			void					SetRelativeVScale(double value);
			double					GetRelativeWScale() const;
			void					SetRelativeWScale(double value);
			double					GetLowClip() const;
			void					SetLowClip(double value);
			double					GetHighClip() const;
			void					SetHighClip(double value);
			double					GetDetail() const;					
			void					SetDetail(double value);
			double					GetCycles() const;
			void					SetCycles(double value);
			double					GetRefraction() const;
			void					SetRefraction(double value);
			double					GetTransparencyBlurriness() const;
			void					SetTransparencyBlurriness(double value);
			Tools::CRGBColor		GetAbsorptionColor() const;
			void					SetAbsorptionColor(const Tools::CRGBColor& value);
			double					GetAbsorptionDistance() const;
			void					SetAbsorptionDistance(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyNoise& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyNoise& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderTransparencyTiles : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyTiles(VWTextureObj& textureObj);
							VWTextureShaderTransparencyTiles(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyTiles(const VWTextureShaderTransparencyTiles& src);
			virtual			~VWTextureShaderTransparencyTiles();

			VWTextureShaderTransparencyTiles&	operator=(const VWTextureShaderTransparencyTiles& src);
		
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
			double				GetRefraction() const;
			void				SetRefraction(double value);
			double				GetTransparencyBlurriness() const;
			void				SetTransparencyBlurriness(double value);
			Tools::CRGBColor	GetAbsorptionColor() const;		
			void				SetAbsorptionColor(const Tools::CRGBColor& value);
			double				GetAbsorptionDistance() const;
			void				SetAbsorptionDistance(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyTiles& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyTiles& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderTransparencyBricks : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyBricks(VWTextureObj& textureObj);
							VWTextureShaderTransparencyBricks(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyBricks(const VWTextureShaderTransparencyBricks& src);
			virtual			~VWTextureShaderTransparencyBricks();

			VWTextureShaderTransparencyBricks&	operator=(const VWTextureShaderTransparencyBricks& src);
		
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
			double				GetRefraction() const;
			void				SetRefraction(double value);
			double				GetTransparencyBlurriness() const;
			void				SetTransparencyBlurriness(double value);
			Tools::CRGBColor	GetAbsorptionColor() const;
			void				SetAbsorptionColor(const Tools::CRGBColor& value);
			double				GetAbsorptionDistance() const;
			void				SetAbsorptionDistance(double value);
			double				GetBricksImageBlend() const;
			void				SetBricksImageBlend(double value);
			double				GetGapImageBlend() const;
			void				SetGapImageBlend(double value);
			double				GetAltBricksImageBlend() const;
			void				SetAltBricksImageBlend(double value);
		
		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyBricks& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyBricks& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderTransparencyPavement : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyPavement(VWTextureObj& textureObj);
							VWTextureShaderTransparencyPavement(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyPavement(const VWTextureShaderTransparencyPavement& src);
			virtual			~VWTextureShaderTransparencyPavement();

			VWTextureShaderTransparencyPavement&	operator=(const VWTextureShaderTransparencyPavement& src);
		
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
			double				GetRefraction() const;
			void				SetRefraction(double value);
			double				GetTransparencyBlurriness() const;
			void				SetTransparencyBlurriness(double value);
			Tools::CRGBColor	GetAbsorptionColor() const;
			void				SetAbsorptionColor(const Tools::CRGBColor& value);
			double				GetAbsorptionDistance() const;
			void				SetAbsorptionDistance(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyPavement& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyPavement& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderTransparencyRectangularMask : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyRectangularMask(VWTextureObj& textureObj);
							VWTextureShaderTransparencyRectangularMask(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyRectangularMask(const VWTextureShaderTransparencyRectangularMask& src);
			virtual			~VWTextureShaderTransparencyRectangularMask();

			VWTextureShaderTransparencyRectangularMask&	operator=(const VWTextureShaderTransparencyRectangularMask& src);
		
		public:
			Sint32			GetRepeatH() const;
			void			SetRepeatH(Sint32 value);
			Sint32			GetRepeatV() const;
			void			SetRepeatV(Sint32 value);
		
		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyRectangularMask& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyRectangularMask& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderTransparencyImageMask : public VWTextureShaderBase
		{
		public:
							VWTextureShaderTransparencyImageMask(VWTextureObj& textureObj);
							VWTextureShaderTransparencyImageMask(MCObjectHandle hShaderRecord);
							VWTextureShaderTransparencyImageMask(const VWTextureShaderTransparencyImageMask& src);
			virtual			~VWTextureShaderTransparencyImageMask();

			VWTextureShaderTransparencyImageMask&	operator=(const VWTextureShaderTransparencyImageMask& src);
		
		public:
			MCObjectHandle		GetMask() const;
			void				SetMaskImage(MCObjectHandle& hBitmapObj) const;
			void				SetMaskImageFromAlphaChannel( MCObjectHandle hImageMask, bool bUseAlpha = true );
			Sint32				GetRepeatH() const;
			void				SetRepeatH(Sint32 value);
			Sint32				GetRepeatV() const;
			void				SetRepeatV(Sint32 value);
			bool				GetAntiAliased() const;
			void				SetAntiAliased(bool value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderTransparencyImageMask& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderTransparencyImageMask& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
	}
}
