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
		class VWTextureShaderColorPlain : public VWTextureShaderBase
		{
		public:
							VWTextureShaderColorPlain(VWTextureObj& textureObj);
							VWTextureShaderColorPlain(MCObjectHandle hShaderRecord);
							VWTextureShaderColorPlain(const VWTextureShaderColorPlain& src);
			virtual			~VWTextureShaderColorPlain();

			VWTextureShaderColorPlain&	operator=(const VWTextureShaderColorPlain& src);

		public:
			Tools::CRGBColor	GetColor() const;
			void				SetColor(const Tools::CRGBColor& value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderColorPlain& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderColorPlain& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// --------------------------------------------------------------------------------
		class VWTextureShaderColorImage : public VWTextureShaderBase
		{
		public:
							VWTextureShaderColorImage(VWTextureObj& textureObj);
							VWTextureShaderColorImage(MCObjectHandle hShaderRecord);
							VWTextureShaderColorImage(const VWTextureShaderColorImage& src);
			virtual			~VWTextureShaderColorImage();

			VWTextureShaderColorImage&	operator=(const VWTextureShaderColorImage& src);

		public:
			enum EColorFilter
			{
				eColorFilter_None,
				eColorFilter_ObjectColor,
				eColorFilter_CustomColor,
			};

			MCObjectHandle		GetImage() const;
			void				SetImage(MCObjectHandle& hBitmapObj) const;
			EColorFilter		GetColorFilter() const;
			void				SetColorFilter(EColorFilter value);
			Tools::CRGBColor	GetFilterColor() const;
			void				SetFilterColor(const Tools::CRGBColor& value);
			bool				GetAntiAliased() const;
			void				SetAntiAliased(bool value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderColorImage& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderColorImage& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderColorFresnel : public VWTextureShaderBase
		{
		public:
							VWTextureShaderColorFresnel(VWTextureObj& textureObj);
							VWTextureShaderColorFresnel(MCObjectHandle hShaderRecord);
							VWTextureShaderColorFresnel(const VWTextureShaderColorFresnel& src);
			virtual			~VWTextureShaderColorFresnel();

			VWTextureShaderColorFresnel&	operator=(const VWTextureShaderColorFresnel& src);

		public:
			Tools::CRGBColor	GetEdgeColor() const;
			void				SetEdgeColor(const Tools::CRGBColor& value);
			Tools::CRGBColor	GetCenterColor() const;
			void				SetCenterColor(const Tools::CRGBColor& value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderColorFresnel& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderColorFresnel& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);

		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderColorNoise : public VWTextureShaderBase
		{
		public:
							VWTextureShaderColorNoise(VWTextureObj& textureObj);
							VWTextureShaderColorNoise(MCObjectHandle hShaderRecord);
							VWTextureShaderColorNoise(const VWTextureShaderColorNoise& src);
			virtual			~VWTextureShaderColorNoise();

			VWTextureShaderColorNoise&	operator=(const VWTextureShaderColorNoise& src);

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

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderColorNoise& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderColorNoise& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderColorTiles : public VWTextureShaderBase
		{
			public:
							VWTextureShaderColorTiles(VWTextureObj& textureObj);
							VWTextureShaderColorTiles(MCObjectHandle hShaderRecord);
							VWTextureShaderColorTiles(const VWTextureShaderColorTiles& src);
			virtual			~VWTextureShaderColorTiles();

			VWTextureShaderColorTiles&	operator=(const VWTextureShaderColorTiles& src);

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

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderColorTiles& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderColorTiles& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderColorBricks : public VWTextureShaderBase
		{
			public:
							VWTextureShaderColorBricks(VWTextureObj& textureObj);
							VWTextureShaderColorBricks(MCObjectHandle hShaderRecord);
							VWTextureShaderColorBricks(const VWTextureShaderColorBricks& src);
			virtual			~VWTextureShaderColorBricks();

			VWTextureShaderColorBricks&	operator=(const VWTextureShaderColorBricks& src);

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
			double				GetBricksImageBlend() const;
			void				SetBricksImageBlend(double value);
			double				GetGapImageBlend() const;
			void				SetGapImageBlend(double value);
			double				GetAltBricksImageBlend() const;
			void				SetAltBricksImageBlend(double value);
		
		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderColorBricks& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderColorBricks& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// ------------------------------------------------------------------------------
		class VWTextureShaderColorPavement : public VWTextureShaderBase
		{
			public:
							VWTextureShaderColorPavement(VWTextureObj& textureObj);
							VWTextureShaderColorPavement(MCObjectHandle hShaderRecord);
							VWTextureShaderColorPavement(const VWTextureShaderColorPavement& src);
			virtual			~VWTextureShaderColorPavement();

			VWTextureShaderColorPavement&	operator=(const VWTextureShaderColorPavement& src);

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

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderColorPavement& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderColorPavement& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
	}
}
