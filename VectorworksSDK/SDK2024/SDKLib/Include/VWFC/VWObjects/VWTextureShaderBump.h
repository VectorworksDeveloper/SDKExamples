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
		class VWTextureShaderBumpImage : public VWTextureShaderBase
		{
		public:
							VWTextureShaderBumpImage(VWTextureObj& textureObj);
							VWTextureShaderBumpImage(MCObjectHandle hShaderRecord);
							VWTextureShaderBumpImage(const VWTextureShaderBumpImage& src);
			virtual			~VWTextureShaderBumpImage();

			VWTextureShaderBumpImage&	operator=(const VWTextureShaderBumpImage& src);

		public:
			MCObjectHandle		GetImage() const;
			void				SetImage(MCObjectHandle& hBitmapObj) const;
			double				GetBumpStrength() const;
			void				SetBumpStrength(double value);
			double				GetDisplacementMaxHeight() const;
			void				SetDisplacementMaxHeight(double value);
			Sint32				GetDisplacementDetail() const;
			void				SetDisplacementDetail(Sint32 value);
			bool				GetDisplacementSelfShadow() const;
			void				SetDisplacementSelfShadow(bool value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpImage& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderBumpImage& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// --------------------------------------------------------------------------------
		class VWTextureShaderBumpNoise : public VWTextureShaderBase
		{
		public:
							VWTextureShaderBumpNoise(VWTextureObj& textureObj);
							VWTextureShaderBumpNoise(MCObjectHandle hShaderRecord);
							VWTextureShaderBumpNoise(const VWTextureShaderBumpNoise& src);
			virtual			~VWTextureShaderBumpNoise();

			VWTextureShaderBumpNoise&	operator=(const VWTextureShaderBumpNoise& src);

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
			double				GetBumpStrength() const;
			void				SetBumpStrength(double value);
			double				GetDisplacementMaxHeight() const;
			void				SetDisplacementMaxHeight(double value);
			Sint32				GetDisplacementDetail() const;
			void				SetDisplacementDetail(Sint32 value);
			bool				GetDisplacementSelfShadow() const;
			void				SetDisplacementSelfShadow(bool value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpNoise& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderBumpNoise& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// --------------------------------------------------------------------------------
		class VWTextureShaderBumpTiles : public VWTextureShaderBase
		{
		public:
							VWTextureShaderBumpTiles(VWTextureObj& textureObj);
							VWTextureShaderBumpTiles(MCObjectHandle hShaderRecord);
							VWTextureShaderBumpTiles(const VWTextureShaderBumpTiles& src);
			virtual			~VWTextureShaderBumpTiles();

			VWTextureShaderBumpTiles&	operator=(const VWTextureShaderBumpTiles& src);

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
			double				GetBumpStrength() const;
			void				SetBumpStrength(double value);
			double				GetDisplacementMaxHeight() const;
			void				SetDisplacementMaxHeight(double value);
			Sint32				GetDisplacementDetail() const;
			void				SetDisplacementDetail(Sint32 value);
			bool				GetDisplacementSelfShadow() const;
			void				SetDisplacementSelfShadow(bool value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpTiles& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderBumpTiles& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// --------------------------------------------------------------------------------
		class VWTextureShaderBumpBricks : public VWTextureShaderBase
		{
		public:
							VWTextureShaderBumpBricks(VWTextureObj& textureObj);
							VWTextureShaderBumpBricks(MCObjectHandle hShaderRecord);
							VWTextureShaderBumpBricks(const VWTextureShaderBumpBricks& src);
			virtual			~VWTextureShaderBumpBricks();

			VWTextureShaderBumpBricks&	operator=(const VWTextureShaderBumpBricks& src);

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
			double				GetBrickHeight1() const;
			void				SetBrickHeight1(double value);
			double				GetBrickHeight2() const;
			void				SetBrickHeight2(double value);
			double				GetAltHeight1() const;
			void				SetAltHeight1(double value);
			double				GetAltHeight2() const;
			void				SetAltHeight2(double value);
			double				GetGapHeight1() const;
			void				SetGapHeight1(double value);
			double				GetGapHeight2() const;
			void				SetGapHeight2(double value);
			double				GetContrast() const;
			void				SetContrast(double value);
			Sint32				GetAltColorRow() const;
			void				SetAltColorRow(Sint32 value);
			Sint32				GetAltColorColumn() const;
			void				SetAltColorColumn(Sint32 value);
			double				GetBumpStrength() const;
			void				SetBumpStrength(double value);
			double				GetDisplacementMaxHeight() const;
			void				SetDisplacementMaxHeight(double value);
			Sint32				GetDisplacementDetail() const;
			void				SetDisplacementDetail(Sint32 value);
			bool				GetDisplacementSelfShadow() const;
			void				SetDisplacementSelfShadow(bool value);
			double				GetBricksImageBlend() const;
			void				SetBricksImageBlend(double value);
			double				GetGapImageBlend() const;
			void				SetGapImageBlend(double value);
			double				GetAltBricksImageBlend() const;
			void				SetAltBricksImageBlend(double value);

		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpBricks& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderBumpBricks& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};

		// --------------------------------------------------------------------------------
		class VWTextureShaderBumpPavement : public VWTextureShaderBase
		{
		public:
							VWTextureShaderBumpPavement(VWTextureObj& textureObj);
							VWTextureShaderBumpPavement(MCObjectHandle hShaderRecord);
							VWTextureShaderBumpPavement(const VWTextureShaderBumpPavement& src);
			virtual			~VWTextureShaderBumpPavement();

			VWTextureShaderBumpPavement&	operator=(const VWTextureShaderBumpPavement& src);

		public:
			double				GetScale() const;
			void				SetScale(double value);
			double				GetGapWidth() const;
			void				SetGapWidth(double value);
			double				GetSoftness() const;
			void				SetSoftness(double value);
			double				GetStoneHeight1() const;
			void				SetStoneHeight1(double value);
			double				GetStoneHeight2() const;
			void				SetStoneHeight2(double value);
			double				GetCoarseMarbling() const;
			void				SetCoarseMarbling(double value);
			double				GetFineMarbling() const;
			void				SetFineMarbling(double value);
			double				GetGapHeight1() const;
			void				SetGapHeight1(double value);
			double				GetGapHeight2() const;
			void				SetGapHeight2(double value);
			double				GetGapGrain() const;
			void				SetGapGrain(double value);
			double				GetSmudgeHeight1() const;
			void				SetSmudgeHeight1(double value);
			double				GetSmudgeHeight2() const;
			void				SetSmudgeHeight2(double value);
			double				GetSmudgeAmount() const;
			void				SetSmudgeAmount(double value);
			double				GetSmudgeSize() const;
			void				SetSmudgeSize(double value);
			double				GetBumpStrength() const;
			void				SetBumpStrength(double value);
			double				GetDisplacementMaxHeight() const;
			void				SetDisplacementMaxHeight(double value);
			Sint32				GetDisplacementDetail() const;
			void				SetDisplacementDetail(Sint32 value);
			bool				GetDisplacementSelfShadow() const;
			void				SetDisplacementSelfShadow(bool value);


		// tool
		public:
			static bool		CreateShader(MCObjectHandle hTexture, VWTextureShaderBumpPavement& outValue);
			static bool		GetShader(MCObjectHandle hTexture, VWTextureShaderBumpPavement& outValue);

			static bool		IsShaderRecordObject(MCObjectHandle hObj);
		};
	}
}
